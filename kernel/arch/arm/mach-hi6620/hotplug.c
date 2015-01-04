
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/smp.h>
#include <linux/notifier.h>
#include <linux/cpu.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <asm/cacheflush.h>
#include <asm/irq.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <soc_baseaddr_interface.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include "drv_ipcm.h"
#include "soc_pmctrl_interface.h"

#include <mach/pwrctrl/pwrctrl_common.h>
#include <asm/cacheflush.h>
#include <mach/pwrctrl/pwrctrl_arm_pmu.h>
#include "pwrctrl_multi_memcfg.h"
#include "pwrctrl_multi_dfs_asm.h"
#include "../include/asm/hardware/gic.h"

#define platform_cpu_id() \
({ \
    unsigned int cpunum; \
    __asm__("mrc p15, 0, %0, c0, c0, 5" \
        : "=r" (cpunum)); \
    cpunum &= 0x0F; \
})

#define APCU_PLL0 0
#define APCU_PLL1 1
#define ACPU_RESET_TIMES 5
#define ACPU_DVFS_WAIT_READY_TIME 5000/*100us*/

/*acpu ipc sem id */
IPC_SEM_ID_E acpu_ipc_sem_id[ARM_ACPU_CORE_NUM] =
{
    IPC_SEM_SMP_CPU0,
    IPC_SEM_SMP_CPU1,
    IPC_SEM_SMP_CPU2,
    IPC_SEM_SMP_CPU3,
};

unsigned int acpu_load_res[ARM_ACPU_CORE_NUM] =
{0,0,0,0};

extern volatile int pen_release;
extern void __iomem *gic_dist_base_addr;

/*include pwctrl_sleep.h will make us lots of troubles*/
extern void pwrctrl_asm_deep_sleep_entry(void);
extern void l2x0_flush_all(void);
extern  void  secondary_start_kernel(void);

static DECLARE_COMPLETION(cpu_killed);

static inline void cpu_enter_lowpower(void)
{
	unsigned int v;

    l2x0_flush_all();
	flush_cache_all();

	asm volatile(
	"	mcr	p15, 0, %1, c7, c5, 0\n"
	"	mcr	p15, 0, %1, c7, c10, 4\n"
	/*
	 * Turn off coherency
	 */
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, %3\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	"	mrc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	  : "=&r" (v)
	  : "r" (0), "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}

static inline void cpu_leave_lowpower(void)
{
	unsigned int v;

	asm volatile(
	"mrc	p15, 0, %0, c1, c0, 0\n"
	"	orr	%0, %0, %1\n"
	"	mcr	p15, 0, %0, c1, c0, 0\n"
	"	mrc	p15, 0, %0, c1, c0, 1\n"
	"	orr	%0, %0, %2\n"
	"	mcr	p15, 0, %0, c1, c0, 1\n"
	  : "=&r" (v)
	  : "Ir" (CR_C), "Ir" (0x40)
	  : "cc");
}
void secondary_jump(void)
{
    unsigned int cpu = platform_cpu_id();

    //mdelay(10);
    *((volatile unsigned int *)IO_ADDRESS(MEMORY_AXI_CORE_BOOT_STAGE_ADDR)) = 0x4;

	if (pen_release != cpu) {
		for (;;) {
			/*
			 * here's the WFI
			 */
			asm("WFI\n"
			 :
			 :
			 : "memory", "cc");

    		if (pen_release == cpu) {
    			/*
    			 * OK, proper wakeup, we're done
    			 */
    			break;
    		}

    		/*
    		 * getting here, means that we have come out of WFI without
    		 * having been woken up - this shouldn't happen
    		 *
    		 * The trouble is, letting people know about this is not really
    		 * possible, since we are currently running incoherently, and
    		 * therefore cannot safely call printk() or anything else
    		 */
    		//printk(KERN_ERR"CPU%d : cpu %d should not be here!.pen_release:%d .\n", this_cpu, cpu,pen_release);
    	}

	}

    *((volatile unsigned int *)IO_ADDRESS(MEMORY_AXI_CORE_BOOT_STAGE_ADDR)) = 0x5;

    __asm__("mov	sp, %0\n"
	"	mov	fp, #0\n"
	"	b	secondary_start_kernel"
		:
		: "r" (task_stack_page(current) + THREAD_SIZE - 8));
}
void  platform_cpu_die(unsigned int cpu)
{
    unsigned int this_cpu = platform_cpu_id();

    if (cpu != this_cpu) {
        printk(KERN_ERR"%s : cpu id %d error , %d expected.\n", __FUNCTION__,
                this_cpu, cpu);
        return;
    }

    complete(&cpu_killed);
#if 0
    cpu_enter_lowpower();
#endif

    pwrctrl_asm_deep_sleep_entry();
#if 0
    cpu_leave_lowpower();
#endif

	if (pen_release != cpu) {
		for (;;) {
			/*
			 * here's the WFI
			 */
			asm("WFI\n"
			 :
			 :
			 : "memory", "cc");

    		if (pen_release == cpu) {
    			/*
    			 * OK, proper wakeup, we're done
    			 */
    			break;
    		}

    		/*
    		 * getting here, means that we have come out of WFI without
    		 * having been woken up - this shouldn't happen
    		 *
    		 * The trouble is, letting people know about this is not really
    		 * possible, since we are currently running incoherently, and
    		 * therefore cannot safely call printk() or anything else
    		 */
    		printk(KERN_ERR"CPU%d : cpu %d should not be here!.pen_release:%d .\n", this_cpu, cpu,pen_release);
    	}

	}


    return;
}

int platform_cpu_kill(unsigned int cpu)
{
    return wait_for_completion_timeout(&cpu_killed, 5000);
}

int platform_cpu_disable(unsigned int cpu)
{
    return cpu == 0 ? -1 : 0;
}
/*ACPU复位规避*/
void clear_dvfs_info(void)
{
    int i;

    for(i = 0; i < 6; i++)
    {
        pwrctrl_write_reg32(IO_ADDRESS(MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR) + i * 4, 0x0);
    }
}
void set_reset_complete_flag(void)
{
    pwrctrl_write_reg32(IO_ADDRESS(MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR) + 0x14, ACPU_DVFS_COMPLETE_FLAG);
}

int stop_online_cpu(int online_cpu)
{
    unsigned int value = 0;
    unsigned int ready_cpu = 0;
    int i = 0;
    unsigned int cnt = 0;
    int ret = 0;

    online_cpu = (online_cpu & 0xF);
    if(0 == online_cpu)
    {
        return -1;
    }

    clear_dvfs_info();
    /*sent stop cpu msg*/
    /*writel(((online_cpu << 16) + SLAVE_CORE_FIQ_NUM), (gic_dist_base_addr + GIC_DIST_SOFTINT));*/
    (void)pwrctrl_write_reg32((unsigned int)(gic_dist_base_addr + GIC_DIST_SOFTINT),(unsigned int)((online_cpu << 16) + SLAVE_CORE_FIQ_NUM));
    /*check online cpu ready flag*/
    while(cnt++ < ACPU_DVFS_WAIT_READY_TIME)
    {
        ready_cpu = 0;
        for(i = 0; i < 4; i++)
        {
            value = pwrctrl_read_reg32(IO_ADDRESS(MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR) + 4 + i * 4);
            if(ACPU_IDLE_READY_FLAG == value)
                ready_cpu |= (1 << i);
        }

        if(online_cpu == ready_cpu)
        {
            break;
        }
    }

    if(cnt > ACPU_DVFS_WAIT_READY_TIME)
    {
        printk("stop cpu failed!!!\n");
        /*systemError()*/
        ret = -1;
    }

    return ret;
}

/*balong v9r1 soc related function, to enable slave power down*/
void platform_cpu_power_down(int cpu)
{
    unsigned int reg, cnt = 0;
    SOC_SCTRL_SC_ACPU_CTRL0_UNION *ctrl0;
    /*spinlock_t lock = SPIN_LOCK_UNLOCKED;*/
    unsigned long flags;
    /*spin_lock_init(&lock);*/

    /*make sure cpu in wfi status*/
    do {
        reg = readl(SOC_SCTRL_SCCPUCORESTAT_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
        if (reg & BIT(SOC_SCTRL_SCCPUCORESTAT_core0standywfi_START + cpu)) {
            break;
        }

        msleep(1);
        if (cnt++ > 5000) {
            printk(KERN_ERR"%s : cpu %d not in wfi state.\n", __FUNCTION__, cpu);
            return;
        }
    }while(1);

    /*spin_lock_irqsave(&lock, flags);*/
    local_irq_save(flags);

    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg |= (1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    if ((ctrl0->reg.cpu_wfi_mask_cfg & (1 << cpu)) == 0) {
        printk(KERN_ERR"%s : cpu %d fail to set wfi mask.\n", __FUNCTION__, cpu);
    }

    /*
    在启动ACPU从核的下电流程（含时钟复位ISO电源等控制）前，应先按下述配置关闭监控该从核的HPM模块，随后才可以启动ACPU该从核的下电流程。
    步骤 1	配置寄存器ACPUHPMMASKEN，屏蔽监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKEN_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));

    /*configure cpu power down*/
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_ISOEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_CLKDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    udelay(5);
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_DIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));

    *((volatile unsigned int *)IO_ADDRESS(MEMORY_AXI_CORE_BOOT_STAGE_ADDR)) = 0x8;

    /*spin_unlock_irqrestore(&lock, flags);*/
    local_irq_restore(flags);
    return;
}

/*balong v9r1 soc related function, to enable slave power on*/
void platform_cpu_power_on(int cpu)
{
    volatile unsigned int reg,tmp;
    volatile SOC_SCTRL_SC_ACPU_CTRL0_UNION *ctrl0;
    volatile unsigned int target_pll = 0;
    volatile unsigned int i = 0;
    /*spinlock_t lock = SPIN_LOCK_UNLOCKED;*/
    unsigned long flags;
    unsigned int this_cpu = platform_cpu_id();
    /*spin_lock_init(&lock);*/

    /*spin_lock_irqsave(&lock, flags);*/
    local_irq_save(flags);
    *((volatile unsigned int *)IO_ADDRESS(MEMORY_AXI_CORE_BOOT_STAGE_ADDR)) = 0x0;
#if 0
    /*configure cpu wfi mask*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg &= ~(1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
#endif
    /*
    在启动ACPU从核的上电流程（含时钟复位ISO电源等控制）前，应先按下述配置打开监控该从核的HPM模块，随后才可以启动ACPU该从核的上电流程。
    步骤 1	配置寄存器ACPUHPMMASKDIS，打开监控该从核的HPM模块。
    */
    writel(BIT(cpu), SOC_PMCTRL_ACPUHPMMASKDIS_ADDR(IO_ADDRESS(REG_BASE_PMCTRL)));

    /*power on cpu*/
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_EN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    do{
        tmp = readl(SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_ADDR(SOC_SC_ON_BASE_ADDR)) & BIT(cpu);
     } while (BIT(cpu) != tmp);

    BSP_IPC_SpinLock(IPC_SEM_DFS_HOTPLUG);

    /*判断当前选择的PLL*/
    if(pwrctrl_is_bits_set(SOC_PMCTRL_ACPUPLLSEL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)),BIT(1)))
    {
        target_pll = APCU_PLL1;
    }
    else
    {
        target_pll = APCU_PLL0;
    }
    /*配置另一个PLL运行并等待稳定*/
    if(APCU_PLL0 == target_pll)
    {
        pwrctrl_set_bits(SOC_PMCTRL_ACPUPLL1CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));
        for(;;)
        {
            if(pwrctrl_is_bits_set(SOC_PMCTRL_ACPUPLL1CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(28)))
            {
                break;
            }
        }
        /*切换到另一个PLL运行*/
        pwrctrl_set_bits(SOC_PMCTRL_ACPUPLLSEL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));

    }
    else
    {
        pwrctrl_set_bits(SOC_PMCTRL_ACPUPLL0CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));
        for(;;)
        {
            if(pwrctrl_is_bits_set(SOC_PMCTRL_ACPUPLL0CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(28)))
            {
                break;
            }
        }
        /*切换到另一个PLL运行*/
        pwrctrl_clr_bits(SOC_PMCTRL_ACPUPLLSEL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));

    }

    /*##配置ACPU进行反复复位*/
    /*wfi_mask=1*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg |= (1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    /*clk_off=0*/
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_CLKEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    /*循环解复位*/
    for(i=0;i<ACPU_RESET_TIMES;i++)
    {
        isb();
        dsb();
        writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
        isb();
        dsb();
        for(tmp=0;tmp<64;tmp++);
        isb();
        dsb();
        writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
        isb();
        dsb();
        for(tmp=0;tmp<32;tmp++);
    }
    isb();
    /*wfi_mask=0*/
    reg = readl(SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));
    ctrl0 = (SOC_SCTRL_SC_ACPU_CTRL0_UNION *)&reg;
    ctrl0->reg.cpu_wfi_mask_cfg &= ~(1 << cpu);
    writel(reg, SOC_SCTRL_SC_ACPU_CTRL0_ADDR(IO_ADDRESS(REG_BASE_SC_OFF)));

    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_ISODIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
    dsb();
    for(tmp=0;tmp<8;tmp++);
    isb();
    writel(BIT(cpu) , SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));

    /*触发从核锁定流程*/
    stop_online_cpu((num_online_cpus() & (~(BIT(this_cpu) | (BIT(cpu))))));
    /*切回原来的PLL，并将另一个PLL去使能*/
    if(APCU_PLL0 == target_pll)
    {
        pwrctrl_clr_bits(SOC_PMCTRL_ACPUPLLSEL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));

        /*reg = readl(SOC_PMCTRL_ACPUPLLSEL_ADDR(SOC_PMCTRL_BASE_ADDR));*/
        reg = pwrctrl_read_reg32(SOC_PMCTRL_ACPUPLLSEL_ADDR(SOC_PMCTRL_BASE_ADDR));
        while( (reg&BIT(SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_stat_START)));

        pwrctrl_clr_bits(SOC_PMCTRL_ACPUPLL1CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));
    }
    else
    {
        pwrctrl_set_bits(SOC_PMCTRL_ACPUPLLSEL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));

        /*reg = readl(SOC_PMCTRL_ACPUPLLSEL_ADDR(SOC_PMCTRL_BASE_ADDR));*/
        reg = pwrctrl_read_reg32(SOC_PMCTRL_ACPUPLLSEL_ADDR(SOC_PMCTRL_BASE_ADDR));
        while( !(reg&BIT(SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_stat_START)));

        pwrctrl_clr_bits(SOC_PMCTRL_ACPUPLL0CTRL_ADDR(IO_ADDRESS(SOC_PMCTRL_BASE_ADDR)), BIT(0));
    }

    /*释放从核锁定*/
    set_reset_complete_flag();
    BSP_IPC_SpinUnLock(IPC_SEM_DFS_HOTPLUG);

    /*spin_unlock_irqrestore(&lock, flags);*/
    local_irq_restore(flags);
    return;
}

static int platform_cpu_up_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;
    /*unsigned int this_cpu = platform_cpu_id(); */

    /*printk(KERN_INFO"[CPU %d] %s : cpu %d change to status %ld.\n", this_cpu, __FUNCTION__, cpu, status);*/

    switch(status){
        case CPU_UP_PREPARE:
        case CPU_UP_PREPARE_FROZEN:
            platform_cpu_power_on(cpu);
            break;
        case CPU_ONLINE:
        case CPU_ONLINE_FROZEN:
#if 0
            /* enalbe arm pmu cpu_load function */
            printk(KERN_INFO"enable cpuload function...\n");
            arm_cpuload_init(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);
            arm_cpuload_enable(acpu_load_res[cpu]);
            BSP_IPC_SpinUnLock(acpu_ipc_sem_id[cpu]);
			printk(KERN_INFO"up,enable cpuload function end.\n");
 #endif
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}

static int platform_cpu_down_notify (struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
    unsigned int cpu = (unsigned int)cpuid;
    /*unsigned int this_cpu = platform_cpu_id();*/

    /*printk(KERN_INFO"[CPU %d] %s : cpu %d change to status %ld.\n", this_cpu, __FUNCTION__, cpu, status);*/

    switch(status){
        case CPU_DOWN_PREPARE:
        case CPU_DOWN_PREPARE_FROZEN:
            /* Disalbe arm pmu cpu_load function */
            printk(KERN_INFO"disable cpuload function...\n");
            BSP_IPC_SpinLock(acpu_ipc_sem_id[cpu]);
            arm_cpuload_disable(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);
			printk(KERN_INFO"down,disable cpuload function end.\n");
            break;

        case CPU_DEAD:
        case CPU_DEAD_FROZEN:
            platform_cpu_power_down(cpu);
            break;
        case CPU_ONLINE:
        case CPU_ONLINE_FROZEN:
			printk(KERN_INFO"enable cpuload function...\n");
            /* enalbe arm pmu cpu_load function */
            arm_cpuload_init(acpu_load_res[cpu]);
            arm_cpuload_reset(acpu_load_res[cpu]);
            arm_cpuload_enable(acpu_load_res[cpu]);
            BSP_IPC_SpinUnLock(acpu_ipc_sem_id[cpu]);
			printk(KERN_INFO"up,enable cpuload function end.\n");
            break;
        default:
            /*just pass other event*/
            break;

    }
    return NOTIFY_DONE;
}


static struct notifier_block __refdata platform_cpu_up_notifier = {
    .notifier_call = platform_cpu_up_notify,
    .priority = CPU_PRI_SCHED_ACTIVE,
};

static struct notifier_block __refdata platform_cpu_down_notifier = {
    .notifier_call = platform_cpu_down_notify,
    .priority = CPU_PRI_CPUSET_INACTIVE,
};

static int __init platform_hotplug_init(void)
{

    unsigned int i;

#if 0
    /*fastboot: 软件模式*/
    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        platform_cpu_power_on(i);
    }
    /*congigure cpu1/2/3 power control mode, by software*/
    writel(BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_msk_START) \
          |BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_msk_START) \
          |BIT(SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_msk_START) \
           , SOC_AO_SCTRL_SC_PW_CTRL_ADDR(IO_ADDRESS(SOC_SC_ON_BASE_ADDR)));
#endif

    register_hotcpu_notifier(&platform_cpu_up_notifier);
    register_hotcpu_notifier(&platform_cpu_down_notifier);

    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        acpu_load_res[i] = (unsigned int)ioremap((ARM_PMU_ACPU0_ADDR + i*ARM_PMU_ACPU_SIZE), ARM_PMU_ACPU_SIZE);
    }

    return 0;
}

static void __exit platform_hotplug_exit(void)
{

    unsigned int i;

    unregister_hotcpu_notifier(&platform_cpu_up_notifier);
    unregister_hotcpu_notifier(&platform_cpu_down_notifier);

    for(i=0;i<ARM_ACPU_CORE_NUM;i++)
    {
        iounmap((void *)acpu_load_res[i]);
    }

    return;
}

module_init(platform_hotplug_init);
module_exit(platform_hotplug_exit);



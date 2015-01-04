/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  reset.c    hisi watchdog v100 kernel device driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/module.h>           /* For module specific items */
#include <linux/moduleparam.h>      /* For new moduleparam's */
#include <linux/types.h>            /* For standard types (like size_t) */
#include <linux/errno.h>            /* For the -ENODEV/... values */
#include <linux/kernel.h>           /* For printk/... */
#include <linux/init.h>             /* For __init/__exit/... */
#include <linux/fs.h>               /* For file operations */
#include <linux/wakelock.h>         /* For file operations */
#include <linux/ioport.h>           /* For io-port access */
#include <linux/spinlock.h>         /* For spin_lock/spin_unlock/... */
#include <linux/suspend.h>
#include <linux/completion.h>
#include <linux/uaccess.h>          /* For copy_to_user/put_user/... */
#include <linux/workqueue.h>        /* For workqueue... */
#include <linux/notifier.h>         /* For notifier... */
#include <linux/interrupt.h>        /* For request_irq*/
#include <linux/io.h>               /* For writel */
#include <linux/reboot.h>               /* For writel */
#include <general_sram_map.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include <DrvInterface.h>
#include <mach/platform.h>
#include <mach/reset.h>
#include <soc_wdt_interface.h>
#include <soc_edmac_interface.h>
#include <mach/hisi_cortex-a9.h>

static int in_suspend_state = 0;
static struct workqueue_struct *reset_wq = NULL;
static struct wake_lock reset_wake_lock;
static DECLARE_COMPLETION(reset_suspend_completed);
static struct notifier_block reset_pm_notifier;
static struct notifier_block modem_reboot_cpu_notifier;
static struct notifier_block modem_panic_cpu_notifier;
static struct notifier_block modem_freeze_cpu_notifier;
static unsigned long ap_dmac_base = 0;
static unsigned long hifi_wdt_addr = 0;
static unsigned int ccpu_wdt_addr = 0;

unsigned int g_modem_panic_dummy_cnt = 0;

void modem_panic_give_semaphone(void);
void modem_reboot_give_semaphone(void);
void modem_freeze_give_semaphone(void);
void hifi_freeze_give_semaphone(void);
void android_freeze_give_semaphone(void);
void mcu_freeze_give_semaphone(void);
void mcu_panic_give_semaphone(void);
void android_reboot_give_semaphone(void);
void wdg_rstlog_save_give_semaphone(void);
void acpuwdg_historylog_write_give_semaphone(void);
void mculocalwdg_historylog_write_give_semaphone(void);
void mcuglbwdg_historylog_write_give_semaphone(void);
void mcu_puzzle_give_semaphone(void);
int platform_ddr_protect_init(int flag);
int ccorereset_notify_other_cpu(struct notifier_block *cb, unsigned long code, void *p);
extern unsigned int omTimerGet(void);

#define RESET_WORK_DECLARE(name, type)\
\
static BLOCKING_NOTIFIER_HEAD(name ## _notifier_list);\
\
static struct type name ## _work;\
\
static void name ## _do_work(struct work_struct *work)\
{\
    if (1 == in_suspend_state){\
        if (!wait_for_completion_timeout(&reset_suspend_completed, HZ*10))\
            goto fail;\
    }\
\
    blocking_notifier_call_chain(&name ## _notifier_list, 0, NULL);\
    name ## _give_semaphone();\
    return;\
\
fail:\
    machine_restart("system halt");\
    return;\
}\
\
int name ## _regsister_notifier(struct notifier_block *n)\
{\
    return  blocking_notifier_chain_register(&name ## _notifier_list, n);\
}\
EXPORT_SYMBOL(name ## _regsister_notifier);\
\
int name ## _unregsister_notifier(struct notifier_block *n)\
{\
    return  blocking_notifier_chain_unregister(&name ## _notifier_list, n);\
}\
EXPORT_SYMBOL(name ## _unregsister_notifier);


#define RESET_WORK_INIT(name)\
INIT_WORK(&name ## _work, name ## _do_work)

/*declare reset work*/
RESET_WORK_DECLARE(mcu_panic, work_struct)
RESET_WORK_DECLARE(modem_panic, work_struct)
RESET_WORK_DECLARE(modem_reboot, work_struct)
RESET_WORK_DECLARE(modem_freeze, work_struct)
RESET_WORK_DECLARE(hifi_freeze, work_struct)
RESET_WORK_DECLARE(android_freeze, delayed_work)
RESET_WORK_DECLARE(android_reboot, delayed_work)
RESET_WORK_DECLARE(mcu_puzzle, work_struct)

#if 1 /*Modify_for_c_reset, l00212112,20130511*/
RESET_WORK_DECLARE(mcu_freeze, work_struct)
#else
RESET_WORK_DECLARE(mcu_freeze, delayed_work)
#endif
RESET_WORK_DECLARE(wdg_rstlog_save, delayed_work)
RESET_WORK_DECLARE(acpuwdg_historylog_write, delayed_work)
RESET_WORK_DECLARE(mculocalwdg_historylog_write, delayed_work)
RESET_WORK_DECLARE(mcuglbwdg_historylog_write, delayed_work)

static int reset_pm_notify(struct notifier_block *notify_block,
                    unsigned long mode, void *unused)
{
    switch (mode) {
    case PM_HIBERNATION_PREPARE:
    case PM_SUSPEND_PREPARE:
        in_suspend_state = 1;
        break;

    case PM_POST_SUSPEND:
    case PM_POST_HIBERNATION:
    case PM_POST_RESTORE:
        complete(&reset_suspend_completed);
        in_suspend_state = 0;
        break;
    }

    return 0;
}


static void print_banner(char *info)
{
    printk(KERN_ERR "############################\n");
    printk(KERN_ERR "timestamp: %d\n", omTimerGet());
    printk(KERN_ERR " %s\n", info);
    printk(KERN_ERR "############################\n");
}


static void prepare_reset(void)
{
    wake_lock(&reset_wake_lock);

    BSP_IPC_IntDisable(IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT);

    BSP_IPC_IntDisable(IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT);

    BSP_IPC_IntDisable(IPC_ACPU_INI_SRC_MCU_EXC_REBOOT);

    disable_irq_nosync(IRQ_WD3);

    disable_irq_nosync(IRQ_WD1);

    disable_irq_nosync(IRQ_CM3WD0);

    platform_ddr_protect_init(0);

    return;
}


void stop_watchdog1(void)
{
    if(!hifi_wdt_addr){
        printk(KERN_ERR "Bad WatchDog1 address\n");
        return;
    }

    printk(KERN_INFO "RESET LOG: stop_watchdog1_begin!\n");

    /* First, Unlock Wd1 to allow modifying registers */
    writel(DRV_WATCHDOG_UNLOCK_NUM, SOC_WDT_WDG_LOCK_ADDR(hifi_wdt_addr));
    /* Clear  Wd1 Interrupt register */
    writel(DRV_WATCHDOG_INTCLR_NUM, SOC_WDT_WDG_INTCLR_ADDR(hifi_wdt_addr));
    /* Disable Wd1  */
    writel(DRV_WATCHDOG_CONTROL_DISABLE, SOC_WDT_WDG_CONTROL_ADDR(hifi_wdt_addr));
    /* Finally, Lock Wd1 */
    writel(DRV_WATCHDOG_LOCK_NUM, SOC_WDT_WDG_LOCK_ADDR(hifi_wdt_addr));

    printk(KERN_INFO "RESET LOG: stop_watchdog1_end!\n");

}

static irqreturn_t hifi_freeze_irq(int irqno, void *param)
{
    SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_UNION runstall_val;
    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);

    if(!ap_dmac_base){
           printk(KERN_ERR "Bad ap_dmac_base address\n");
           return IRQ_NONE;
    }

    print_banner("oops : hifi freeze ...");

    /* Stop WD1 */
    stop_watchdog1();

    /* runstall hifi */
    runstall_val.value             = 0x0;
    runstall_val.reg.hifi_runstall = 0x1;

    writel(runstall_val.value, SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_ADDR(sctrl_off));

    /* close dma, channel 1 - audio pcm play
        channel 2 - audio pcm capture
        channel 3 - voice pcm mic
        channel 4 - voice pcm spk
        channel 5 - voice pcm smart PA */
    writel(0, SOC_EDMAC_CX_CONFIG_ADDR(ap_dmac_base, 1));
    writel(0, SOC_EDMAC_CX_CONFIG_ADDR(ap_dmac_base, 2));
    writel(0, SOC_EDMAC_CX_CONFIG_ADDR(ap_dmac_base, 3));
    writel(0, SOC_EDMAC_CX_CONFIG_ADDR(ap_dmac_base, 4));
    writel(0, SOC_EDMAC_CX_CONFIG_ADDR(ap_dmac_base, 5));


/*Modify_for_c_reset, l00212112,20130511 ,starts*/
    /*clean hifi's wdt int*/
    reset_clean_wdt_int(BSP_RESET_MODULE_HIFI);
/*Modify_for_c_reset, l00212112,20130511 ,ends*/

    prepare_reset();

    queue_work(reset_wq, &hifi_freeze_work);

    return IRQ_HANDLED;
}
static int regsister_modem_rst_notifier(void)
{
    modem_reboot_cpu_notifier.notifier_call = ccorereset_notify_other_cpu;
    modem_reboot_cpu_notifier.priority = INT_MAX;/*优先级最高*/
    modem_panic_cpu_notifier.notifier_call = ccorereset_notify_other_cpu;
    modem_panic_cpu_notifier.priority = INT_MAX;
    modem_freeze_cpu_notifier.notifier_call = ccorereset_notify_other_cpu;
    modem_freeze_cpu_notifier.priority = INT_MAX;
    modem_reboot_regsister_notifier(&modem_reboot_cpu_notifier);
    modem_panic_regsister_notifier(&modem_panic_cpu_notifier);
    modem_freeze_regsister_notifier(&modem_freeze_cpu_notifier);

    return 0;
}

static irqreturn_t modem_freeze_irq(int irqno, void *param)
{
    print_banner("oops : modem freeze ...");

    if(!ccpu_wdt_addr){
        printk(KERN_ERR "bad ccpu_wdt_addr address\n");
        return IRQ_HANDLED;
    }

    writel(DRV_WATCHDOG_UNLOCK_NUM,SOC_WDT_WDG_LOCK_ADDR(ccpu_wdt_addr));

    writel(0x0,SOC_WDT_WDG_CONTROL_ADDR(ccpu_wdt_addr));

    writel(0x0,SOC_WDT_WDG_LOCK_ADDR(ccpu_wdt_addr));

/*Modify_for_c_reset, l00212112,20130511 ,starts*/
    /*clean c core's wdt int*/
    reset_clean_wdt_int(BSP_RESET_MODULE_CCORE);
/*Modify_for_c_reset, l00212112,20130511 ,ends*/

    prepare_reset();

    queue_work(reset_wq, &modem_freeze_work);
    return IRQ_HANDLED;
}
/*Modify_for_c_reset, l00212112,20130511 ,starts*/

static irqreturn_t mcu_freeze_irq(int irqno, void *param)
{
    printk(KERN_ERR "oops : mcu freeze ....\n");

    prepare_reset();

    /*do as panic*/
    queue_work(reset_wq, &mcu_panic_work);

    return IRQ_HANDLED;
}
void modem_panic_give_semaphone(void)
{
    reset_ccore_up_semaphone();
}

void modem_reboot_give_semaphone(void)
{
    reset_ccore_up_semaphone();
}

void modem_reboot_himself(void)
{
    reset_ccore_up_byhimself();
}
void modem_freeze_give_semaphone(void)
{
    reset_ccore_up_semaphone();
}
void hifi_freeze_give_semaphone(void)
{
    reset_hifi_up_semaphone();
}

void android_freeze_give_semaphone(void)
{
    /*do nothing*/
}
void mcu_freeze_give_semaphone(void)
{
    /*do nothing*/
}
void mcu_panic_give_semaphone(void)
{
    /*do nothing*/
}

void android_reboot_give_semaphone(void)
{
    /*do nothing*/
}

void wdg_rstlog_save_give_semaphone(void)
{
    /*do nothing*/
}

void acpuwdg_historylog_write_give_semaphone(void)
{
    /*do nothing*/
}

void mculocalwdg_historylog_write_give_semaphone(void)
{
    /*do nothing*/
}

void mcuglbwdg_historylog_write_give_semaphone(void)
{
    /*do nothing*/
}
void mcu_puzzle_give_semaphone(void)
{
    /*do nothing*/
}


void finish_reset_sub(void)
{
    platform_ddr_protect_init(1);
    BSP_IPC_IntEnable(IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT);

    BSP_IPC_IntEnable(IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT);

    BSP_IPC_IntEnable(IPC_ACPU_INI_SRC_MCU_EXC_REBOOT);

    enable_irq(IRQ_CM3WD0);

    enable_irq(IRQ_WD1);
    enable_irq(IRQ_WD3);
    wake_unlock(&reset_wake_lock);
    return;
}
/*Modify_for_c_reset, l00212112,20130511, ends*/

static void modem_panic_irq(unsigned int param)
{
    int gic_dist_pendclr_addr = 0;

    /*检查SRAM中的modem异常复位标志*/
    if(AXI_MODEM_PANIC_FLAG != *(volatile unsigned int *)IO_ADDRESS(AXI_MODEM_PANIC_FLAG_ADDR)) {
        g_modem_panic_dummy_cnt++;
        print_banner("oops : modem panic dummy");
        printk(KERN_ERR "total count is %d\n", g_modem_panic_dummy_cnt);
        return;
    }
    else {
        *(volatile unsigned int *)IO_ADDRESS(AXI_MODEM_PANIC_FLAG_ADDR) = 0;
    }

    print_banner("oops : modem panic ...");

    if(!ccpu_wdt_addr){
        printk(KERN_ERR "bad ccpu_wdt_addr address\n");
        return;
    }

    writel(DRV_WATCHDOG_UNLOCK_NUM,SOC_WDT_WDG_LOCK_ADDR(ccpu_wdt_addr));

    writel(0x0,SOC_WDT_WDG_CONTROL_ADDR(ccpu_wdt_addr));

    writel(0x0,SOC_WDT_WDG_LOCK_ADDR(ccpu_wdt_addr));

    reset_clean_wdt_int(BSP_RESET_MODULE_CCORE);

    /* clear modem wdt int pending */
    gic_dist_pendclr_addr = IO_ADDRESS(REG_CPU_A9GICDIST_BASE) + 0x280 + 4*(IRQ_WD3/32);
    *(volatile int *)gic_dist_pendclr_addr = (1 << (IRQ_WD3%32));

    prepare_reset();

    queue_work(reset_wq, &modem_panic_work);

    return;
}


static void modem_reboot_irq(unsigned int param)
{
    print_banner("info : acore reboot modem ...");

    prepare_reset();

    queue_work(reset_wq, &modem_reboot_work);

    return;
}


static void mcu_panic_irq(unsigned int param)
{
    print_banner("oops : mcu panic ...");

    prepare_reset();

    queue_work(reset_wq, &mcu_panic_work);

    return;
}


static void init_reset_irq_do_work(struct work_struct *work)
{
    int ret;

    ccpu_wdt_addr  = (unsigned int)(ioremap(SOC_MWatchDog_BASE_ADDR, 4096));
    hifi_wdt_addr = (unsigned int)(ioremap_nocache(SOC_Watchdog1_BASE_ADDR, 4096));
    ap_dmac_base = (unsigned int)(ioremap_nocache(SOC_AP_DMAC_BASE_ADDR, 4096));


    wake_lock_init(&reset_wake_lock, WAKE_LOCK_SUSPEND, "reset_wake_lock");

    reset_pm_notifier.notifier_call = reset_pm_notify;
    reset_pm_notifier.priority = INT_MIN;
    register_pm_notifier(&reset_pm_notifier);
    /*modem单独复位注册notifier*/
    regsister_modem_rst_notifier();
    RESET_WORK_INIT(mcu_panic);
    RESET_WORK_INIT(hifi_freeze);
    RESET_WORK_INIT(modem_panic);
    RESET_WORK_INIT(modem_freeze);
    RESET_WORK_INIT(modem_reboot);
/*Modify_for_c_reset, l00212112,20130511, starts*/
    RESET_WORK_INIT(mcu_freeze);
/*Modify_for_c_reset, l00212112,20130511, ends*/

    /*register exception irq handles */
    ret = request_irq(IRQ_WD1, hifi_freeze_irq, 0, "hifi_freeze",  NULL);
    if (0 != ret) {
        printk(KERN_ERR "failed to install hifi freezing irq handle (%d)\n", ret);
    }

    ret = request_irq(IRQ_WD3, modem_freeze_irq, 0, "modem_freeze",  NULL);
    if (0 != ret) {
        printk(KERN_ERR "failed to install modem freezing irq handle (%d)\n", ret);
    }
/*Modify_for_c_reset, l00212112,20130511, starts*/
    ret = request_irq(IRQ_CM3WD0, mcu_freeze_irq, 0, "mcu_freeze",  NULL);
    if (0 != ret) {
        printk(KERN_ERR "failed to install mcu freezing irq handle (%d)\n", ret);
    }
/*Modify_for_c_reset, l00212112,20130511, ends*/

    ret = BSP_IPC_IntConnect(IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT, modem_panic_irq, 0);
    if (BSP_OK != ret){
        printk(KERN_ERR "failed to connect IPC irq handle (%d)\n", IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT);
    }
    BSP_IPC_IntEnable(IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT);

    ret = BSP_IPC_IntConnect(IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT, modem_reboot_irq, 0);
    if (BSP_OK != ret){
        printk(KERN_ERR "failed to connect IPC irq handle (%d)\n", IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT);
    }
    BSP_IPC_IntEnable(IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT);

    ret = BSP_IPC_IntConnect(IPC_ACPU_INI_SRC_MCU_EXC_REBOOT, mcu_panic_irq, 0);
    if (BSP_OK != ret){
        printk(KERN_ERR "failed to connect IPC irq handle (%d)\n", IPC_ACPU_INI_SRC_MCU_EXC_REBOOT);
    }
    BSP_IPC_IntEnable(IPC_ACPU_INI_SRC_MCU_EXC_REBOOT);

    return;
}

/*declare delayed work*/
static struct delayed_work init_reset_irq_work;

static int reset_module_init(void)
{
    BUG_ON(!reset_wq);

    /*init delayed work*/
    INIT_DELAYED_WORK(&init_reset_irq_work, init_reset_irq_do_work);


    /*delay 10 second*/
    queue_delayed_work(reset_wq, &init_reset_irq_work, 10*HZ);

    return 0;
}
module_init(reset_module_init);
static void __exit reset_device_module_exit(void)
{
    BSP_IPC_IntDisonnect(IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT, modem_panic_irq, 0);

    BSP_IPC_IntDisonnect(IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT, modem_reboot_irq, 0);

    BSP_IPC_IntDisonnect(IPC_ACPU_INI_SRC_MCU_EXC_REBOOT, mcu_panic_irq, 0);

    free_irq(IRQ_CM3WD0, NULL);

    free_irq(IRQ_WD1, NULL);
    free_irq(IRQ_WD3, NULL);


    iounmap((void*)ccpu_wdt_addr);
    iounmap((void*)ap_dmac_base);
    iounmap((void*)hifi_wdt_addr);

    unregister_pm_notifier(&reset_pm_notifier);

    return;
}
module_exit(reset_device_module_exit);



static int __init system_freeze_flag_init(void)
{
    /*unsigned long sctrl_base = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);*/
    /*SOC_AO_SCTRL_SC_SYS_STAT0_UNION *stat0 = (SOC_AO_SCTRL_SC_SYS_STAT0_UNION *)SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(sctrl_base);*/

    reset_wq = create_singlethread_workqueue("reset_wq");
    BUG_ON(!reset_wq);

    return 0;
}
arch_initcall(system_freeze_flag_init);


static void __exit system_freeze_flag_exit(void)
{
    /*to some code when module exit*/

    return;
}
module_exit(system_freeze_flag_exit);
#ifdef BSP_C_HIFI_RESET_ALONE_TESET_VALID
/*These functions are used for testing!!!only!!!, starts*/
int simulate_irq_c_freeze(void)
{
    modem_freeze_irq(0,0);
    return 0;
}
int simulate_irq_c_panic(void)
{
    modem_panic_irq(0);
    return 0;
}
int simulate_irq_c_reset(void)
{
    modem_reboot_himself();

    return 0;
}

int simulate_irq_hifi_reset(void)
{
    hifi_freeze_irq(0,0);
    return 0;
}
int simulate_irq_mcuwdt_reset(void)
{
    mcu_freeze_irq(0, 0);
    return 0;
}

/*ends*/
#endif
void save_mcu_log_info(void)
{
    blocking_notifier_call_chain(&mcu_puzzle_notifier_list, 0, NULL);
    printk("save_mcu_log_info over\n");
}

#define ANDROID_REBOOT_MAGIC 0xe8c7b756
static char *reboot_reason[] = {"modem_panic", "modem_freeze", "modem_reboot", \
                                "hifi_freeze", "mcu_panic" };
static int android_reboot_notify(struct notifier_block *this,
            unsigned long code, void *reason)
{
    unsigned long addr = (unsigned long) IO_ADDRESS(MEMORY_AXI_ANDROID_REBOOT_FLAG_ADDR);
    unsigned int val = ANDROID_REBOOT_MAGIC;
    char *cmd = (char *)reason;
    int i;

    /*skip none SYS_RESTART*/
    if (code != SYS_RESTART){
        goto out;
    }

    /*normal reboot*/
    if (NULL == cmd){
        goto out;
    }

    /*skip this case*/
    for (i = 0; i< ARRAY_SIZE(reboot_reason); i++){
        if (0 == strncmp(cmd, reboot_reason[i], strlen(reboot_reason[i]))){
            val = 0;
            goto out;
        }
    }

out:
    writel(val, addr);

    return NOTIFY_DONE;
}

static struct notifier_block android_reboot_notifier = {
    .notifier_call = android_reboot_notify,
    .priority = INT_MAX,
};



static int __init android_reboot_flag_init(void)
{
    unsigned long addr = (unsigned long) IO_ADDRESS(MEMORY_AXI_ANDROID_REBOOT_FLAG_ADDR);
    int err;

    writel(0, addr);

    err = register_reboot_notifier(&android_reboot_notifier);
    if (err) {
            return -1;
    }

    return 0;
}
module_init(android_reboot_flag_init);


static void __exit android_reboot_flag_exit(void)
{
    /*to some code when module exit*/

    return;
}
module_exit(android_reboot_flag_exit);


MODULE_DESCRIPTION("Hisilicon device RESET Management module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


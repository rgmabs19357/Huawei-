#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <soc_irqs.h>
#include <linux/irq.h>
#include <mach/irqs.h>
#include <linux/interrupt.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/io.h>
#include <asm/io.h>
#include <soc_mddrc_dmc_interface.h>
#include <mach/platform.h>
#include "reg_ops.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#include "BSP.h"
#include <mntn/excDrv.h>
#include <DrvInterface.h>

#include <linux/mtd/nve_interface.h>
#define NVE_HIMNTN_NUM 297
#define NV_READ 1
#define MAX_PROTECT_DDR_24M 0x1800000
#ifdef CONFIG_DEBUG_FS
typedef union
{
    u32 ddrc_his_data[14];
    struct
    {
        u32 ddrc_his_flux_wr;
        u32 ddrc_his_flux_rd;
        u32 ddrc_his_flux_wcmd;
        u32 ddrc_his_flux_rcmd;
        u32 ddrc_his_fluxid_wr;
        u32 ddrc_his_fluxid_rd;
        u32 ddrc_his_fluxid_wcmd;
        u32 ddrc_his_fluxid_rcmd;
        u32 ddrc_his_wlatcnt0;
        u32 ddrc_his_wlatcnt1;
        u32 ddrc_his_rlatcnt0;
        u32 ddrc_his_rlatcnt1;
        u32 ddrc_his_inhere_rlat_cnt;
        u32 ddrc_his_cmd_sum;
    }ddrc_reg;
} DDRC_HIS_DATA_UNION;

struct ddrc_dmc_data {
    u64 ddrc_timer;
    DDRC_HIS_DATA_UNION u_ddrc_his_data;
};

struct ddrc_info_stru
{
    unsigned int count; /* counts */
    unsigned int ddrc_intmask;
    unsigned int ddrc_rint;
    unsigned int ddrc_intstat;
    char error_logger_info[REG_ERROR_LOGGER_0_IOSIZE];
    char ddrc_sec_info[1];
};

unsigned int count;
struct ddrc_dmc_data *ddrc_datas;
struct dentry *ddrc_dmc_root;
unsigned int interval;
unsigned int ddrc_freq;
unsigned int sta_id;
unsigned int sta_id_mask;

static void __iomem *ddrc_dmc0_base_virt = 0;
static void __iomem *ddrc_sec0_base_virt = 0;
static unsigned int ddrc_info_save_addr = 0;

static DEFINE_SPINLOCK(ddrc_sec_lock);

#define DDRC_DMC_ERROR_MASK             ((1<<SOC_MDDRC_DMC_DDRC_RINT_serr_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_merr_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_sref_err_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_dimm_parity_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_rdtimeout_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_aref_alarm_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_sbram_serr_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_sbram_merr_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_rpram_serr_rint_START)| \
                                         (1<<SOC_MDDRC_DMC_DDRC_RINT_rpram_merr_rint_START))

#define MAX_DDRC_DMC_DATA               0x80000 //512
#define DDRC_SEC_LOCK(flags)            spin_lock_irqsave(&ddrc_sec_lock,flags)
#define DDRC_SEC_UNLOCK(flags)          spin_unlock_irqrestore(&ddrc_sec_lock,flags)

#define REG_BASE_DDRC_DMC0_VIRT         ddrc_dmc0_base_virt
#define REG_BASE_DDRC_SEC0_VIRT         ddrc_sec0_base_virt
#define DDRC_INFO_SAVE_ADDR             exch_get_drv_addr()


void platform_ddr_protect_24M(int portnum, int flag)
{
    unsigned long flags;
    int base_addr = (int)REG_BASE_DDRC_SEC0_VIRT;

    DDRC_SEC_LOCK(flags);
    *(volatile unsigned int*)(base_addr + 0x4 + 0x400*portnum)  |= 0x1;/*enable interrupt*/
    
    /*region0*/
    *(volatile unsigned int*)(base_addr + 0x108 + 0x400*portnum) = 0xf0000000;
    
    /*region1,addr start*/
    *(volatile unsigned int*)(base_addr + 0x110 + 0x400*portnum) = 0;
    *(volatile unsigned int*)(base_addr + 0x114 + 0x400*portnum) = 0;  
            
    if (flag)/*start ddr protect*/ 
    {  
        /*region1,addr end*/
        *(volatile unsigned int*)(base_addr + 0x118 + 0x400*portnum) = 0x0000002f;/*16M*/
        
        /*region2,addr start*/
        *(volatile unsigned int*)(base_addr + 0x120 + 0x400*portnum) = 0x1000000;
        *(volatile unsigned int*)(base_addr + 0x124 + 0x400*portnum) = 0x0;
        /*region2,addr end*/
        *(volatile unsigned int*)(base_addr + 0x128 + 0x400*portnum) = 0x0000002d;/*8M*/
    } 
    else/*stop ddr protect*/
    {
        *(volatile unsigned int*)(base_addr + 0x118 + 0x400*portnum) = 0x0;
        *(volatile unsigned int*)(base_addr + 0x120 + 0x400*portnum) = 0x0;  
        *(volatile unsigned int*)(base_addr + 0x124 + 0x400*portnum) = 0x0;              
        *(volatile unsigned int*)(base_addr + 0x128 + 0x400*portnum) = 0x0;
    }
    DDRC_SEC_UNLOCK(flags);
}
#if 0
int  ddr_protect_nv_read()
{
    int ret=0;
    struct nve_info_user nvinfo;
    nvinfo.nv_operation = NV_READ;
    nvinfo.nv_number=NVE_HIMNTN_NUM;
    nvinfo.valid_size=HIMNTN_VALID_SIZE;
    strcpy(nvinfo.nv_name,"HIMNTN");

    ret=nve_direct_access(&nvinfo);
    if (1)
    {
        if(nvinfo.nv_data[HTMNTN_DDR_PROTECT]  == '0')
        {
            pr_info("[bsp_config_ddr_protect_mntn] nve access failed!\n");
	     return 0;
        }
        else if (nvinfo.nv_data[HTMNTN_DDR_PROTECT] == '1')
        {
            pr_info("[bsp_config_ddr_protect_mntn] nve access success!\n");
            return 1;	  
        }
    }

}
#endif

int platform_ddr_protect_init(int flag)
{
    int port = 1;
    int end_port = 8;
    int ret;
#if 0
    ret=ddr_protect_nv_read();

    if(ret)
    {
        pr_info("platform_ddr_protect_24M_init %d\n",flag);
        while (port <= end_port) {
            platform_ddr_protect_24M(port, flag);
            port++;
        }
    }
#endif
     pr_info("platform_ddr_protect_24M_init %d\n",flag);
     while (port <= end_port) {
        platform_ddr_protect_24M(port, flag);
        port++;
     	}
    return 0;
}

static void dump_error_logger(void *base, unsigned int size)
{
    unsigned int offset;
    unsigned int *reg;

    printk(KERN_ERR "ddrc logger dump : \n");

    for(offset = 0 ; offset < size ; offset += 4 * sizeof(unsigned int)){
        reg = (unsigned int *)(base + offset);
        printk(KERN_ERR "[%08x] : %08x %08x %08x %08x\n", offset, *reg, \
            *(reg + 1), *(reg + 2), *(reg + 3));
    }

    return;
}

/* process the ddrc security & other events */
extern void __iomem *error_logger;
void ddrc_events_handler()
{
    int portnum = 1;
    int end_port = 8;
    int base_addr = (int)REG_BASE_DDRC_SEC0_VIRT;
    int first_invader;
    unsigned int fail_addr;
    unsigned int masterval = 0;
    unsigned int accesstype = 0;
    unsigned int ddrc_rint = 0;
    unsigned int ddrc_sec_event = 0;
    struct ddrc_info_stru *p_ddrc_info = DDRC_INFO_SAVE_ADDR;

    p_ddrc_info->count++;

    p_ddrc_info->ddrc_intmask = readl(SOC_MDDRC_DMC_DDRC_INTMSK_ADDR(REG_BASE_DDRC_DMC0_VIRT));
    ddrc_rint = (readl(SOC_MDDRC_DMC_DDRC_RINT_ADDR(REG_BASE_DDRC_DMC0_VIRT)) & DDRC_DMC_ERROR_MASK);
    p_ddrc_info->ddrc_rint = ddrc_rint;
    p_ddrc_info->ddrc_intstat = readl(SOC_MDDRC_DMC_DDRC_INTSTS_ADDR(REG_BASE_DDRC_DMC0_VIRT));


    pr_err("%s:count=%d,ddrc_intmask=0x%x,ddrc_rint=0x%x,ddrc_intstat=0x%x\n",__func__,p_ddrc_info->count, \
            p_ddrc_info->ddrc_intmask,p_ddrc_info->ddrc_rint,p_ddrc_info->ddrc_intstat);

    while (portnum <= end_port) {
        if (*(volatile unsigned int*)(base_addr + 0x10 + 0x400*portnum)) {  /*中断状态有效*/
            fail_addr = *(volatile unsigned int*) (base_addr + 0x20 + 0x400*portnum); /*记录越权地址*/
            masterval = *(volatile unsigned int*) (base_addr + 0x2c + 0x400*portnum); /*越权者*/
            accesstype = *(volatile unsigned int*) (base_addr + 0x28 + 0x400*portnum);/*读/写*/

            dump_error_logger(error_logger, REG_ERROR_LOGGER_0_IOSIZE);
            memcpy(&p_ddrc_info->error_logger_info[0],error_logger,REG_ERROR_LOGGER_0_IOSIZE);

            if (fail_addr < MAX_PROTECT_DDR_24M) {/*platform_ddr_protect_32k 配置为保护32k*/
                first_invader = portnum;
                printk(KERN_ERR "ddr_protect_irq: portnum! (0x%x)\n", portnum);
                dump_error_logger((void *)(base_addr + 0x400*portnum), 0x400);
                memcpy((&p_ddrc_info->ddrc_sec_info[0] + portnum*0x100),(base_addr + 0x400*portnum),0x100);
                ddrc_sec_event++;

            } else {
                printk(KERN_ERR "ddr_protect_irq: invalid! portnum (0x%x),addr(0x%x),master(0x%x), type(0x%x)\n", portnum, fail_addr,masterval,accesstype);
            }

            *(volatile unsigned int*) (base_addr + 0x14 + 0x400*portnum) = 1; /*清除中断和越权失效地址*/
       }
       portnum++;
    }

    if ((ddrc_sec_event || ddrc_rint) && check_himntn(HIMNTN_ACCESS_ERROR_REBOOT)){
        systemError((int)BSP_MODU_MNTN, (int)EXCH_S_DDRC_SEC, 0, 0, 0);
    }

}


void ddrc_flux_irq(void)
{
    if (ddrc_datas != NULL) {
        ddrc_datas[count].ddrc_timer = sched_clock();
        memcpy(ddrc_datas[count].u_ddrc_his_data.ddrc_his_data,
                SOC_MDDRC_DMC_DDRC_HIS_FLUX_WR_ADDR(REG_BASE_DDRC_DMC0_VIRT),14*4);
    }
    if (count < (MAX_DDRC_DMC_DATA - 1))
        count++;

    writel(1<<1, SOC_MDDRC_DMC_DDRC_RINT_ADDR(REG_BASE_DDRC_DMC0_VIRT));
    writel(1, SOC_MDDRC_DMC_DDRC_CTRL_PERF_ADDR(REG_BASE_DDRC_DMC0_VIRT));
}

irqreturn_t ddrc_dmc_handle(int irq, void *dev)
{
    int ddrc_int;

    ddrc_int = readl(SOC_MDDRC_DMC_DDRC_INTSTS_ADDR(REG_BASE_DDRC_DMC0_VIRT));
    if (ddrc_int & 0x00000002) {
        ddrc_flux_irq();
    }

    return IRQ_HANDLED;
}


static void *ddrc_data_seq_start(struct seq_file *m, loff_t *pos)
{
    if (*pos >= count)
        return NULL;
    return pos;
}

static void *ddrc_data_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
    (*pos)++;
    if (*pos >= count)
        return NULL;
    return pos;
}

static void ddrc_data_seq_stop(struct seq_file *m, void *v)
{
}

static int ddrc_data_seq_show(struct seq_file *m, void *v)
{
    int i;
    u64 sBeginTime;
    unsigned long nsBeginTime;
    struct tm tm_rtc;
    i = *(int *)v;

    if (i == 0) {
        seq_printf(m, "sta_id:%d,sta_id_mask:%d,ddrc_freq:%d,interval:%dms\n",
                sta_id, sta_id_mask, ddrc_freq, interval);
        seq_printf(m, "index,time,rtc_time,\
ddrc_his_flux_wr,ddrc_his_flux_rd,\
ddrc_his_flux_wcmd,ddrc_his_flux_wcmd,\
ddrc_his_fluxid_wr,ddrc_his_fluxid_rd,\
ddrc_his_fluxid_wcmd,ddrc_his_fluxid_rcmd,\
ddrc_his_wlatcnt0,ddrc_his_wlatcnt1,\
ddrc_his_rlatcnt0,ddrc_his_rlatcnt1,\
ddrc_his_inhere_rlat_cnt,ddrc_his_cmd_sum\n");
    }

    if (ddrc_datas != NULL) {
        sBeginTime = ddrc_datas[i].ddrc_timer;
        nsBeginTime = do_div(sBeginTime, 1000000000);
        time_to_tm((unsigned long)sBeginTime, 0, &tm_rtc);
        seq_printf(m, "%d,%05lu.%06lu,", i, (unsigned long)sBeginTime, nsBeginTime/1000);
        seq_printf(m, "[%lu:%.2d:%.2d %.2d:%.2d:%.2d],",
            1900 + tm_rtc.tm_year, tm_rtc.tm_mon + 1, tm_rtc.tm_mday,
            tm_rtc.tm_hour, tm_rtc.tm_min, tm_rtc.tm_sec);
        seq_printf(m, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_flux_wr,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_flux_rd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_flux_wcmd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_flux_rcmd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_fluxid_wr,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_fluxid_rd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_fluxid_wcmd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_fluxid_rcmd,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_wlatcnt0,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_wlatcnt1,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_rlatcnt0,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_rlatcnt1,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_inhere_rlat_cnt,
            ddrc_datas[i].u_ddrc_his_data.ddrc_reg.ddrc_his_cmd_sum
        );
    }

    return 0;
}

static struct seq_operations ddrc_data_seq_ops = {
    .start = ddrc_data_seq_start,
    .next  = ddrc_data_seq_next,
    .stop  = ddrc_data_seq_stop,
    .show  = ddrc_data_seq_show
};

static int ddrc_data_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &ddrc_data_seq_ops);
}

static const struct file_operations ddrc_data_fops = {
    .open = ddrc_data_open,
    .read = seq_read,
    .llseek = seq_lseek,
    .release = seq_release,
};

ssize_t ddrc_init_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
    u32 freq_interval;

    if (ddrc_datas == NULL) {
        ddrc_datas = (struct ddrc_dmc_data *)vmalloc(MAX_DDRC_DMC_DATA*sizeof(struct ddrc_dmc_data));
    }
    if (interval == 0) {
        interval = 10;
    }
    if (ddrc_freq == 0) {
        ddrc_freq = 50000;
    };
    freq_interval = ddrc_freq/16;
    freq_interval *= interval; //sft ddr 50M
    printk("%s:freq_interval:%d, interval: %dms, sta_id:%d sta_id_mask:%d\n", __func__,ddrc_freq, interval, sta_id, sta_id_mask);
    count = 0;
    //memset(ddrc_datas, 0, MAX_DDRC_DMC_DATA*sizeof(struct ddrc_dmc_data));
    writel(freq_interval | 0x10000000, SOC_MDDRC_DMC_DDRC_CFG_PERF_ADDR(REG_BASE_DDRC_DMC0_VIRT));

    writel(sta_id, SOC_MDDRC_DMC_DDRC_CFG_STAID_ADDR(REG_BASE_DDRC_DMC0_VIRT));
    writel(sta_id_mask, SOC_MDDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(REG_BASE_DDRC_DMC0_VIRT));

    return cnt;
}


static const struct file_operations ddrc_init_fops = {
    .write = ddrc_init_write,
};

ssize_t ddrc_exit_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
    struct ddrc_dmc_data *tmp;
    tmp = ddrc_datas;
    if (ddrc_datas != NULL) {
        ddrc_datas = 0;
        vfree(tmp);
    }
    printk("%s\n", __func__);

    return cnt;
}


static const struct file_operations ddrc_exit_fops = {
    .write = ddrc_exit_write,
};

/* 0: irq is not setup
   1: irq is enable
   2: irq is disable
   */
static unsigned int irq_setup_flag = 0;

ssize_t on_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{

    SOC_MDDRC_DMC_DDRC_INTMSK_UNION *int_mask;


    pr_info("%s +.\n", __func__);

    /* setup ddrc interrupt for statistic function */
    if (irq_setup_flag == 0)
    {
        request_irq(IRQ_DDRC_INT, ddrc_dmc_handle, IRQF_NO_SUSPEND, "ddrc_dmc", NULL);
        irq_setup_flag = 1; /*irq is enabled*/
    }

    if (irq_setup_flag == 2) {
        enable_irq(IRQ_DDRC_INT);
        irq_setup_flag = 1;
    }

    int_mask = (SOC_MDDRC_DMC_DDRC_INTMSK_UNION *)SOC_MDDRC_DMC_DDRC_INTMSK_ADDR(REG_BASE_DDRC_DMC0_VIRT);
    int_mask->reg.flux_int_mask = 0;
    writel(1, SOC_MDDRC_DMC_DDRC_CTRL_PERF_ADDR(REG_BASE_DDRC_DMC0_VIRT));

    return cnt;
}


static const struct file_operations on_fops = {
    .write = on_write,
};

ssize_t off_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{

    SOC_MDDRC_DMC_DDRC_INTMSK_UNION *int_mask;
    pr_info("%s +.\n", __func__);

    if (irq_setup_flag == 1) {
        disable_irq(IRQ_DDRC_INT);
        irq_setup_flag = 2;
    }

    int_mask = (SOC_MDDRC_DMC_DDRC_INTMSK_UNION *)SOC_MDDRC_DMC_DDRC_INTMSK_ADDR(REG_BASE_DDRC_DMC0_VIRT);
    int_mask->reg.flux_int_mask = 1;

    return cnt;
}


static const struct file_operations off_fops = {
    .write = off_write,
};

void ext_ddrc_dmc_on(void)
{
    on_write(NULL, NULL, 0, NULL);
}

void ext_ddrc_dmc_init(int ext_interval)
{
    interval = ext_interval;
    ddrc_init_write(NULL, NULL, 0, NULL);
}
void ext_ddrc_dmc_off(void)
{
    off_write(NULL, NULL, 0, NULL);
}

/*测试函数，没有Unremap，仅限shell口调用*/
void write_phy_addr(unsigned int addr, unsigned int val)
{
    int addr_virt = (int)(ioremap(addr, 0x1000));

    *(volatile unsigned int*)addr_virt = val;

	/*测试函数，没有Unremap，仅限shell口调用*/
}

/*测试函数，没有Unremap，仅限shell口调用*/
void read_phy_addr(unsigned int addr)
{
    int addr_virt = (int)ioremap(addr, 0x1000);
    printk("read_phy_addr:(0x%x)= 0x%x\n",addr, *(volatile unsigned int*)addr_virt);
}

static int __devinit ddrc_dmc_init(void)
{
    int ret = 0;

    ddrc_dmc0_base_virt = ioremap(SOC_DDRC_DMC0_BASE_ADDR, PAGE_ALIGN(SZ_16K));
    if (0 == ddrc_dmc0_base_virt) {
        pr_err("%s: ioremap failed\n",__func__);
        return -1;
    }

    ddrc_sec0_base_virt = ioremap(SOC_DDRC_SEC0_BASE_ADDR, PAGE_ALIGN(SZ_16K));
    if (0 == ddrc_sec0_base_virt) {
        iounmap(ddrc_dmc0_base_virt);
        ddrc_dmc0_base_virt = 0;
        pr_err("%s: ioremap failed\n",__func__);
        return -1;
    }

    /* setup ddrc security protect */
    platform_ddr_protect_init(1);

    ret = BSP_IPC_IntConnect(IPC_ACPU_INT_SRC_MCU_DDR_EXC, ddrc_events_handler, 0);
    if (ret){
        pr_err("failed to connect IPC irq handle (%d)\n", IPC_ACPU_INT_SRC_MCU_DDR_EXC);
    }
    BSP_IPC_IntEnable(IPC_ACPU_INT_SRC_MCU_DDR_EXC);


    ddrc_datas = NULL;

    ddrc_dmc_root = debugfs_create_dir("ddrc_dmc", NULL);

    debugfs_create_u32("interval", S_IRUGO | S_IWUSR, ddrc_dmc_root, &interval);
    debugfs_create_u32("ddrc_freq", S_IRUGO | S_IWUSR, ddrc_dmc_root, &ddrc_freq);
    debugfs_create_u32("sta_id", S_IRUGO | S_IWUSR, ddrc_dmc_root, &sta_id);
    debugfs_create_u32("sta_id_mask", S_IRUGO | S_IWUSR, ddrc_dmc_root, &sta_id_mask);
    debugfs_create_file("ddrc_init", S_IWUSR|S_IWGRP, ddrc_dmc_root, NULL, &ddrc_init_fops);
    debugfs_create_file("ddrc_exit", S_IWUSR|S_IWGRP, ddrc_dmc_root, NULL, &ddrc_exit_fops);
    debugfs_create_file("on", S_IWUSR, ddrc_dmc_root, NULL, &on_fops);
    debugfs_create_file("off", S_IWUSR, ddrc_dmc_root, NULL, &off_fops);
    debugfs_create_file("ddrc_data", S_IRUGO, ddrc_dmc_root, NULL, &ddrc_data_fops);

    return ret;

}

static void __exit ddrc_dmc_exit(void)
{
    iounmap(REG_BASE_DDRC_DMC0_VIRT);
    iounmap(REG_BASE_DDRC_SEC0_VIRT);
}
#else
static int __devinit ddrc_dmc_init(void)
{
    return 0;
}
static void __exit ddrc_dmc_exit(void)
{

}
#endif
module_init(ddrc_dmc_init);
module_exit(ddrc_dmc_exit);

MODULE_DESCRIPTION("DDRC DMC Driver");
MODULE_LICENSE("GPL");


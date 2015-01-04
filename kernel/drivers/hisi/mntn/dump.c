/*
 *  linux/arch/arm/mach-k3v2/dump.c
 *
 * balong memory/register proc-fs  dump implementation
 *
 * Copyright (C) 2012 Hisilicon, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/stat.h>
#include <linux/sysdev.h>
#include <linux/uaccess.h>
#include <mach/hardware.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <asm/mach/map.h>
#include <mach/ddr_map.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <mach/util.h>
#include <general_sram_map.h>
#include <soc_baseaddr_interface.h>
#include <soc_pmctrl_interface.h>
#include <mach/clock_map_oem.h>
#include <mach/boardid.h>   /*add by y65256 for wdg log save*/
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <mntn/excDrv.h>
#include "MemoryMap.h"
#include <bsp_ao_sctrl.h>

#define MODEM_SYS_MEM_SAVE_SIZE 0x08000000
#define STRINGLEN 9
#define MEM_DUMP_EVENT_FLAG     0x80000000

#define SIZE_OF_MEM_FOR_DUMP_LOW128M (0x08000000)
#define SIZE_OF_MEM_FOR_DUMP_KERN (0x16800000)
unsigned int g_dump_flag = 0;
extern unsigned int g_ddr_size;

extern void  etb_nve_read(unsigned char *config);
extern unsigned long hisi_get_reserve_mem_size(void);

char core_flag[STRINGLEN];
struct proc_dir_entry *core_trace, *core_flag_file;


/*dump file information, set to file->private_data*/
struct dump_info
{
	void  *p;                        /*dump region phy/virtual address*/
	loff_t size;                     /*dump region size*/
};

/*read dump file content*/
static ssize_t dump_phy_mem_proc_file_read(struct file *file, char __user *userbuf, size_t bytes, loff_t *off)
{
	struct dump_info *info = (struct dump_info *)file->private_data;
	void __iomem *p;
	ssize_t copy;

	if (*off > info->size){
		printk(KERN_ERR"read offset error \n");
		return 0;
	}

	if (*off == info->size){
		/*end of file*/
		return 0;
	}

	copy = (ssize_t)min(bytes, (size_t)(info->size - *off));

	p = ioremap((phys_addr_t)(info->p + *off), copy);
	if (NULL == p){
		printk(KERN_ERR"%s ioremap fail \n", __FUNCTION__);
		return -ENOMEM;
	}

	if (copy_to_user(userbuf, p, copy)){
		printk(KERN_ERR"%s copy to user error \n", __FUNCTION__);
		copy = -EFAULT;
		goto copy_err;
	}

	*off += copy;

copy_err:
	iounmap(p);
	return copy;
}

static int dump_phy_mem_proc_file_open(struct inode *inode, struct file *file)
{
	file->private_data = PDE(inode)->data;

	return 0;
}

static int dump_phy_mem_proc_file_release(struct inode *inode, struct file *file)
{
	file->private_data = NULL;

	return 0;

}

static const struct file_operations dump_phy_mem_proc_fops = {
	.open = dump_phy_mem_proc_file_open,
	.read = dump_phy_mem_proc_file_read,
	.release = dump_phy_mem_proc_file_release,
};

/* create memory dump file to dump phy memory */
void create_dump_phy_mem_proc_file(char *name, void *phy_addr, size_t size)
{
    struct dump_info *info;

    /*as a public interface, we should check the parameter*/
    if ((NULL == name ) ||(NULL == phy_addr) || (0 == size)){
        printk(KERN_ERR"%s %d parameter error : name 0x%p phy_addr 0x%p size %d\r\n", __FUNCTION__, __LINE__, name, \
            phy_addr, size);
        return;
    }

    info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);
    if (NULL == info){
        printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
        return;
    }

    info->p = phy_addr;
    info->size= size;

    balong_create_memory_proc_entry(name, S_IRUGO | S_IWUGO, &dump_phy_mem_proc_fops, info);

    return;
}


#define DUMP(name, base, iosize, string, directory, prop)\
static int __init name ## _dump_phy_mem_proc_file_init(void)\
{\
	struct dump_info *info = NULL;\
\
	if (!prop){\
		return 0;\
	}\
\
	info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);\
	if (NULL == info){\
	   	printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);\
		return -ENOMEM;\
	}\
\
	info->p = (void *)base;\
	info->size = iosize;\
\
	balong_create_ ## directory ## _proc_entry(string, S_IRUGO, &dump_phy_mem_proc_fops, info);\
\
	return 0;\
}\
\
static void __exit name ## _dump_phy_mem_proc_file_exit(void)\
{\
	if (!prop){\
		return;\
	}\
\
	balong_remove_ ## directory ## _proc_entry(string);\
\
	return;\
}\
module_init(name ## _dump_phy_mem_proc_file_init);\
module_exit(name ## _dump_phy_mem_proc_file_exit);

/*definition of register/memory dump in ascii mode*/

#define SHOW(name, base, iosize, string, directory, prop)\
static int name ## _proc_file_show(struct seq_file *m, void *v)\
{\
	void __iomem *p;\
	int i = 0;\
\
	unsigned int *n;\
\
	p = ioremap(base, iosize);\
	if (NULL == p){\
	   	seq_printf(m, "%s ioremap fail !\n", __FUNCTION__);\
		return 0;\
	}\
\
	seq_printf(m, "dump %s register:\n", string);\
	seq_printf(m, "0x%p :    0         1         2         3\n", p);\
	seq_printf(m, "----------------------------------------------------\n");\
	for(i = 0 ; i < iosize; i += 16) {\
		n = (unsigned int *)(p + i);\
		seq_printf(m, "0x%08x : %08X  %08X  %08X  %08X\n", i, *(n + 0), *(n + 1), *(n + 2), *(n + 3));\
	}\
	seq_printf(m, "dump %s register end.\n", string);\
\
	iounmap(p);\
\
	return 0;\
}\
\
static int name ## _proc_file_open(struct inode *inode, struct file *file)\
{\
	return single_open(file, name ## _proc_file_show, NULL);\
}\
\
static const struct file_operations name ## _proc_fops = {\
	.open = name ## _proc_file_open,\
	.read = seq_read,\
	.llseek	= seq_lseek,\
	.release = single_release,\
};\
\
static int __init name ## _proc_file_init(void)\
{\
	if (!prop){\
		return 0;\
	}\
\
	balong_create_ ## directory ## _proc_entry(string, S_IRUGO, &name ## _proc_fops, NULL);\
\
	return 0;\
}\
\
static void __exit name ## _proc_file_exit(void)\
{\
	if (!prop){\
		return;\
	}\
\
	balong_remove_ ## directory ## _proc_entry(string);\
\
	return;\
}\
\
module_init(name ## _proc_file_init);\
module_exit(name ## _proc_file_exit);

/*memory/register dump declaration*/
DUMP(mcu_mem, MCU_SYS_MEM_ADDR, MCU_SYS_MEM_SIZE, "mcu", memory, himntn_gobal_resetlog)
DUMP(hifi_mem, HIFI_SYS_MEM_ADDR, HIFI_SYS_MEM_SIZE, "hifi", memory, himntn_hifi_resetlog)
DUMP(sram_off_mem, REG_BASE_SRAM_OFF, REG_SRAM_OFF_IOSIZE, "sram_off", memory, himntn_gobal_resetlog)
DUMP(sram_on_mem, REG_BASE_SRAM_ON, REG_SRAM_ON_IOSIZE, "sram_on", memory, himntn_gobal_resetlog)
DUMP(modem_mem, MODEM_SYS_MEM_ADDR, MODEM_SYS_MEM_SAVE_SIZE, "modem", memory, himntn_gobal_resetlog)
DUMP(error_logger, REG_BASE_ERROR_LOGGER_0, REG_ERROR_LOGGER_0_IOSIZE, "error_logger", memory, himntn_gobal_resetlog)
DUMP(sc_off_mem, REG_BASE_SC_OFF, REG_SC_OFF_IOSIZE, "sc_off", memory, himntn_gobal_resetlog)
DUMP(sc_on_mem, REG_BASE_SC_ON, REG_SC_ON_IOSIZE, "sc_on", memory, himntn_gobal_resetlog)
DUMP(core_trace, ECS_ETB_ADDR, ECS_ETB_SIZE, "trace_mem", memory, HIMNTN_ALWAYS_RESETLOG)
DUMP(bbe16_lcs_mem, GLOBAL_MEM_LCS_ADDR, GLOBAL_MEM_LCS_SIZE, "bbe16_lcs", memory, himntn_gobal_resetlog)
DUMP(bbe16_tds_table_mem, GLOBAL_MEM_TDS_TABLE_ADDR, GLOBAL_MEM_TDS_TABLE_SIZE, "bbe16_tds_table", memory, himntn_gobal_resetlog)
DUMP(bbe16_img_ddr_mem, GLOBAL_MEM_LT_IMAGE_ADDR, GLOBAL_MEM_LT_IMAGE_SIZE, "bbe16_img_ddr", memory, himntn_gobal_resetlog)

/*log dump declaration*/
DUMP(mcu_log, MCU_DUMP_LOG_ADDR, MCU_DUMP_LOG_SIZE, "mcu", log, himntn_gobal_resetlog)
DUMP(modem_log, MODEM_DUMP_LOG_ADDR, MODEM_DUMP_LOG_SIZE, "modem", log, himntn_gobal_resetlog)
DUMP(android_log, ANDROID_DUMP_LOG_ADDR, ANDROID_DUMP_LOG_SIZE, "android", log, himntn_gobal_resetlog)

/*memory/register show declaration*/
SHOW(sc_off, REG_BASE_SC_OFF, REG_SC_OFF_IOSIZE, "sc_off", register, himntn_gobal_resetlog)
SHOW(sc_on, REG_BASE_SC_ON, REG_SC_ON_IOSIZE, "sc_on", register, himntn_gobal_resetlog)
SHOW(pmctrl, REG_BASE_PMCTRL, REG_PMCTRL_IOSIZE, "pmctrl", register, himntn_gobal_resetlog)
SHOW(watchdog0, REG_BASE_WD0, REG_WD0_IOSIZE, "watchdog0", register, himntn_gobal_resetlog)

int mcpu_pll_enable_set(void)
{
	int i = 0;
	int val = 0;
	int ret = 0;

	i = 1000;

	/* enable clock with protecting other enable bits  */
	val = readl(SOC_PMCTRL_MCPUPLLCTRL_ADDR(PMCTRL_BASE_ADDR));
	val |= 1 << 0;
	writel(val, SOC_PMCTRL_MCPUPLLCTRL_ADDR(PMCTRL_BASE_ADDR));

	udelay(100);

	/* check status */
	while (!val && i) {
		val = readl(SOC_PMCTRL_MCPUPLLCTRL_ADDR(PMCTRL_BASE_ADDR)) & (1 << 28);
		udelay(100);
		i--;
	}

	if (i == 0) {
		WARN(1, "mntn:Attempting to write clock enable register 1000 times.\r\n");
		return -1;
	}

	return 0;
}

#define CARM_ACK_TIMEOUT  100
int mcpu_debug_req(void)
{
	unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
	unsigned long uvalue_jedge = 0;
	volatile unsigned long uvalue = 0;
	unsigned int uAckWaitCnt = 0;

	uvalue = readl(SOC_SCTRL_SC_CARM_STAT0_ADDR(sctrl_off));
	//printk(KERN_ERR"RESET LOG: ccorereset_doreset,org value1 = 0x%lx\n", uvalue);
	uvalue = readl(SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
	//printk(KERN_ERR"RESET LOG: ccorereset_doreset,org value2 = 0x%lx\n", uvalue);
	/*mcpu debug req*/
	writel((uvalue | BIT(SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_START)), SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
	uvalue_jedge = (BIT(SOC_SCTRL_SC_CARM_STAT0_carm_dbgack_START)
		| BIT(SOC_SCTRL_SC_CARM_STAT0_carm_dbgcpudone_START));

	/*wait, dbgack & dbgdone*/
	do {
		udelay(100);
		uvalue = readl(SOC_SCTRL_SC_CARM_STAT0_ADDR(sctrl_off));
		uAckWaitCnt ++;
	} while( ((uvalue & uvalue_jedge) != uvalue_jedge) && (uAckWaitCnt < CARM_ACK_TIMEOUT));

	//printk(KERN_ERR"uAckWaitCnt = %d\n", uAckWaitCnt);

	if ((uvalue & uvalue_jedge) != uvalue_jedge) {
		return -1;
	}
	return 0;
}

static int dump_sram_mdm_mem_proc_file_open(struct inode *inode, struct file *file)
{
	struct dump_info *info = NULL;
 	int ret = 0;

	info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);
	if (NULL == info){
		printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
		return -ENOMEM;
	}

	ret = mcpu_debug_req();
	if (ret) {
		printk(KERN_ERR"mcpu debug req no ack after 10ms!\n");
		return -EPERM;
	}
	ret = mcpu_pll_enable_set();
	if (!ret) {
		info->size = REG_SRAM_MDM_IOSIZE;
	} else {
		info->size = 0;
	}
	info->p = (void *)REG_BASE_SRAM_MDM;

	file->private_data = (void *)info;

	return 0;
}

static int dump_sram_mdm_mem_proc_file_release(struct inode *inode, struct file *file)
{
	struct dump_info *info = (struct dump_info *)file->private_data;
	volatile unsigned long uvalue = 0;
	unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);

	uvalue = readl(SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
	//printk(KERN_ERR"RESET LOG: ccorereset_doreset,org value2 = 0x%lx\n", uvalue);
	uvalue &= ~(BIT(SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_START));

	/*mcpu debug req*/
	writel(uvalue, SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
	uvalue = readl(SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
	//printk(KERN_ERR"RESET LOG: ccorereset_doreset,org value2 = 0x%lx\n", uvalue);

	kfree(info);

	file->private_data = NULL;
	return 0;
}

static const struct file_operations sram_mdm_mem_proc_fops = {
	.open = dump_sram_mdm_mem_proc_file_open,
	.read = dump_phy_mem_proc_file_read,
	.release = dump_sram_mdm_mem_proc_file_release,
};

static int __init sram_mdm_mem_dump_proc_init(void)
{
	if (!himntn_gobal_resetlog){
		return 0;
	}
	balong_create_memory_proc_entry("sram_mdm", S_IRUGO, &sram_mdm_mem_proc_fops, NULL);

	return 0;
}

static void __exit sram_mdm_mem_dump_proc_exit(void)
{
	if (!himntn_gobal_resetlog){
		return;
	}
	balong_remove_memory_proc_entry("sram_mdm");

	return;
}
module_init(sram_mdm_mem_dump_proc_init);
module_exit(sram_mdm_mem_dump_proc_exit);

static int dump_sram_mcu_mem_proc_file_open(struct inode *inode, struct file *file)
{
	struct dump_info *info = NULL;
	unsigned int sc_ctrl1;

	info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);
	if (NULL == info){
		printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
		return -ENOMEM;
	}

	info->p = (void *)REG_BASE_SRAM_MCU;
	info->size = REG_SRAM_MCU_IOSIZE;
	file->private_data = (void *)info;

	sc_ctrl1 = readl(AOSCTRL_SC_SYS_CTRL1);
	sc_ctrl1 |= 0xc0000000;
	sc_ctrl1 &= ~0x0000c000;
	writel(sc_ctrl1, AOSCTRL_SC_SYS_CTRL1);

	return 0;
}

static int dump_sram_mcu_mem_proc_file_release(struct inode *inode, struct file *file)
{
	struct dump_info *info = (struct dump_info *)file->private_data;
	unsigned int sc_ctrl1;

	kfree(info);

	sc_ctrl1 = readl(AOSCTRL_SC_SYS_CTRL1);
	sc_ctrl1 |= 0xc000c000;
	writel(sc_ctrl1, AOSCTRL_SC_SYS_CTRL1);

	file->private_data = NULL;
	return 0;
}

static const struct file_operations sram_mcu_mem_proc_fops = {
	.open = dump_sram_mcu_mem_proc_file_open,
	.read = dump_phy_mem_proc_file_read,
	.release = dump_sram_mcu_mem_proc_file_release,
};

static int __init sram_mcu_mem_dump_proc_init(void)
{
	if (!himntn_gobal_resetlog){
		return 0;
	}
	balong_create_memory_proc_entry("sram_mcu", S_IRUGO, &sram_mcu_mem_proc_fops, NULL);

	return 0;
}

static void __exit sram_mcu_mem_dump_proc_exit(void)
{
	if (!himntn_gobal_resetlog){
		return;
	}
	balong_remove_memory_proc_entry("sram_mcu");

	return;
}
module_init(sram_mcu_mem_dump_proc_init);
module_exit(sram_mcu_mem_dump_proc_exit);

/* dump bbe16 dtcm */
static int dump_bbe16_dtcm_mem_proc_file_open(struct inode *inode, struct file *file)
{
	struct dump_info *info = NULL;
	unsigned int sc_on = 0;
 	int ret = 0;

	ret = mcpu_debug_req();
	if (ret) {
		printk(KERN_ERR"mcpu debug req no ack after 10ms!\n");
		return -EPERM;
	}

	/* return, when bbe16 down */
	sc_on = readl(AOSCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0);
	if(0 == (sc_on & (1 << SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_10dspbbe_START)))
	{
		return -EPERM;
	}

	info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);
	if (NULL == info){
		printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
		return -ENOMEM;
	}

	info->p = (void *)REG_BASE_DTCM_BBE16;
	info->size = REG_DTCM_BBE16_IOSIZE;
	file->private_data = (void *)info;

	return 0;
}

static int dump_bbe16_dtcm_mem_proc_file_release(struct inode *inode, struct file *file)
{
	struct dump_info *info = (struct dump_info *)file->private_data;

	if (NULL != info)
	{
		kfree(info);
	}
	file->private_data = NULL;
	return 0;
}

static const struct file_operations bbe16_dtcm_mem_proc_fops = {
	.open = dump_bbe16_dtcm_mem_proc_file_open,
	.read = dump_phy_mem_proc_file_read,
	.release = dump_bbe16_dtcm_mem_proc_file_release,
};

static int __init bbe16_dtcm_mem_dump_proc_init(void)
{
	if (!himntn_gobal_resetlog){
		return 0;
	}
	balong_create_memory_proc_entry("bbe16_dtcm", S_IRUGO, &bbe16_dtcm_mem_proc_fops, NULL);

	return 0;
}

static void __exit bbe16_dtcm_mem_dump_proc_exit(void)
{
	if (!himntn_gobal_resetlog){
		return;
	}
	balong_remove_memory_proc_entry("bbe16_dtcm");

	return;
}
module_init(bbe16_dtcm_mem_dump_proc_init);
module_exit(bbe16_dtcm_mem_dump_proc_exit);

/*read dump file content*/
static ssize_t dump_virt_mem_proc_file_read(struct file *file, char __user *userbuf, size_t bytes, loff_t *off)
{
	struct dump_info *info = (struct dump_info *)file->private_data;
	ssize_t copy;

	if (*off > info->size){
		printk(KERN_ERR"read offset error \n");
		return 0;
	}

	if (*off == info->size){
		/*end of file*/
		return 0;
	}

	copy = (ssize_t)min(bytes, (size_t)(info->size - *off));

	if (copy_to_user(userbuf, info->p + *off, copy)){
		printk(KERN_ERR"%s copy to user error \n", __FUNCTION__);
		copy = -EFAULT;
		goto copy_err;
	}

	*off += copy;

copy_err:

	return copy;
}

static int dump_virt_mem_proc_file_open(struct inode *inode, struct file *file)
{
    file->private_data = PDE(inode)->data;

    return 0;
}

static int dump_virt_mem_proc_file_release(struct inode *inode, struct file *file)
{
	file->private_data = NULL;

	return 0;

}

static const struct file_operations dump_virt_mem_proc_fops = {
	.open = dump_virt_mem_proc_file_open,
	.read = dump_virt_mem_proc_file_read,
	.release = dump_virt_mem_proc_file_release,
};

void create_dump_virt_mem_proc_file(char *name, void *virt_addr, size_t size)
{
    struct dump_info *info;

    /*as a public interface, we should check the parameter*/
    if ((NULL == virt_addr) ||(0 == size)||(NULL == name)){
        printk(KERN_ERR"%s %d parameter error : name 0x%p vir_addr 0x%p size %d\r\n", __FUNCTION__, __LINE__, name, \
	   	virt_addr, size);
        return;
    }

    info = (struct dump_info *)kmalloc(sizeof(struct dump_info), GFP_KERNEL);
    if (NULL == info){
        printk(KERN_ERR"%s kmalloc fail !\r\n", __FUNCTION__);
        return;
    }

    info->p = virt_addr;
    info->size = size;

    balong_create_memory_proc_entry(name,  S_IRUGO,  &dump_virt_mem_proc_fops,  info);

    return;
}



/*Added by y65256 for wdg log save On 2013-6-8 Begin*/
/*全局指针，指向系统内存里保存A核/MCU/modem三块异常文件区*/
char *pbuffer_of_arstlog = NULL;
char *pbuffer_of_mcurstlog = NULL;
char *pbuffer_of_modemrstlog = NULL;
#define SIZE_OF_MEM_FOR_ARSTLOG_KERNEL 2097152 /*保存A核异常信息-2M*/
#define SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL 1048576 /*保存MCU异常信息-1M*/
#define SIZE_OF_SRAM_FOR_MCU_KERNEL    0x20000 /* MCU SRAM 128K */
#define SIZE_OF_MEM_FOR_MCUSYS_KERNEL  0x100000 /* MCU SYS 1M */
#define SIZE_OF_MEM_FOR_MODEMRSTLOG_KERNEL 2097152 /*保存C核异常信息-2M*/

/*保存fastboot传递过来的异常区地址信息*/
unsigned int g_mem_arstlogaddr = 0;
unsigned int g_mem_mcurstlogaddr = 0;
unsigned int g_mem_modemrstlogaddr = 0;
unsigned int g_mem_dump_addr = 0;

#define MAX_LEN_OF_RSTLOGADDR_STR  30
static int __init early_parse_arstlogaddr_cmdline(char *p)
{
	char arstlog_addr[MAX_LEN_OF_RSTLOGADDR_STR];
	char *endptr = NULL;

	memset(arstlog_addr, 0xA, MAX_LEN_OF_RSTLOGADDR_STR);

	memcpy(arstlog_addr, p, strlen(p)+1);

	g_mem_arstlogaddr = simple_strtoul(arstlog_addr, &endptr, TRANSFER_BASE);

	printk("[early_parse_arstlogaddr_cmdline]mem addr of a rstlog p:%s, g_mem_arstlogaddr :0x%x\n", p, g_mem_arstlogaddr);

	return 0;
}
early_param("arstlogaddr", early_parse_arstlogaddr_cmdline);

static int __init early_parse_mcurstlogaddr_cmdline(char *p)
{
	char mcurstlog_addr[MAX_LEN_OF_RSTLOGADDR_STR];
	char *endptr = NULL;

	memset(mcurstlog_addr, 0xA, MAX_LEN_OF_RSTLOGADDR_STR);

	memcpy(mcurstlog_addr, p, strlen(p)+1);

	g_mem_mcurstlogaddr = simple_strtoul(mcurstlog_addr, &endptr, TRANSFER_BASE);

	printk("[early_parse_mcurstlogaddr_cmdline]mem addr of a rstlog p:%s, g_mem_mcurstlogaddr :0x%x\n", p, g_mem_mcurstlogaddr);

	return 0;
}
early_param("mcurstlogaddr", early_parse_mcurstlogaddr_cmdline);

static int __init early_parse_modemrstlogaddr_cmdline(char *p)
{
	char modemrstlog_addr[MAX_LEN_OF_RSTLOGADDR_STR];
	char *endptr = NULL;

	memset(modemrstlog_addr, 0xA, MAX_LEN_OF_RSTLOGADDR_STR);

	memcpy(modemrstlog_addr, p, strlen(p)+1);

	g_mem_modemrstlogaddr = simple_strtoul(modemrstlog_addr, &endptr, TRANSFER_BASE);

	printk("[early_parse_mcurstlogaddr_cmdline]mem addr of a rstlog p:%s, g_mem_mcurstlogaddr :0x%x\n", p, g_mem_modemrstlogaddr);

	return 0;
}
early_param("modemrstlogaddr", early_parse_modemrstlogaddr_cmdline);

unsigned int g_BitMapOfAbnRst = 0;
static int __init early_parse_bitmap_abnrst_cmdline(char *p)
{
	char bitmapabnrst[MAX_LEN_OF_RSTLOGADDR_STR];
	char *endptr = NULL;
	unsigned int ion_reserve_size = 0;

	memset(bitmapabnrst, 0, MAX_LEN_OF_RSTLOGADDR_STR);

	memcpy(bitmapabnrst, p, strlen(p)+1);

	g_BitMapOfAbnRst = simple_strtoul(bitmapabnrst, &endptr, TRANSFER_BASE);

	printk(KERN_ERR "[early_parse_bitmap_abnrst_cmdline]bitmap of abnormal reset flag p:%s, g_BitMapOfAbnRst :0x%x\n", p, g_BitMapOfAbnRst);

	if (g_BitMapOfAbnRst & MEM_DUMP_EVENT_FLAG)
	{
	    g_dump_flag = 0xFACE; /* set flag to reserve 1G~1.5G memory addr */

	    ion_reserve_size = hisi_get_reserve_mem_size();
	    g_mem_dump_addr = g_ddr_size - ion_reserve_size - SYS_DUMP_MEM_SIZE;
	    printk(KERN_ERR "ion_reserve_size is 0x%x, g_mem_dump_addr is 0x%x\n",ion_reserve_size,g_mem_dump_addr);
	}

	return 0;
}
early_param("bitmapofabnrst", early_parse_bitmap_abnrst_cmdline);

static int __init move_dumpfile_to_system(void)
{
	unsigned int dump_phy_mem_addr = 0;

	if (0xFACE != g_dump_flag) {
		return 0;
	}

	printk(KERN_ERR "Begin to create dump file\n");

	/* create dump file */
	/* first, dump low128M(0x0~0x8000000)*/
	dump_phy_mem_addr = g_mem_dump_addr;
	create_dump_phy_mem_proc_file("dump_low128M",  (void *)dump_phy_mem_addr,  SIZE_OF_MEM_FOR_DUMP_LOW128M);

	/* secend, dump kernel360M(0x8600000~0x1EE00000)*/
	dump_phy_mem_addr += SIZE_OF_MEM_FOR_DUMP_LOW128M;
	create_dump_phy_mem_proc_file("dump_kernel360M", (void  *)dump_phy_mem_addr,  SIZE_OF_MEM_FOR_DUMP_KERN);

	/*then ,you could add new dump file here*/

	return 0;
}
arch_initcall(move_dumpfile_to_system);


static ssize_t reboot_proc_read(struct file *file, char __user *userbuf, size_t bytes, loff_t *off)
{
    char buf[12];
    int strlen = 0;
	ssize_t copy;

    strlen = snprintf(buf, sizeof(buf), "0x%x", g_BitMapOfAbnRst);

	if (*off > strlen){
		printk(KERN_ERR"read offset error \n");
		return 0;
	}

	if (*off == strlen){
		/*end of file*/
		return 0;
	}

	copy = (ssize_t)min(bytes, (size_t)(strlen - *off));

	if (copy_to_user(userbuf, buf + *off, copy)){
		printk(KERN_ERR"%s copy to user error \n", __FUNCTION__);
		copy = -EFAULT;
		goto copy_err;
	}

	*off += copy;

copy_err:

	return copy;
}

static const struct file_operations reboot_proc_fops = {
	.read = reboot_proc_read,
};
static int __init create_reboot_proc(void)
{
    balong_create_reboot_proc_entry("reboot", S_IRUGO, &reboot_proc_fops, NULL);
    return 0;
}
arch_initcall(create_reboot_proc);

/*返回a核异常区首地址，供arch_initcall时，转存异常信息使用*/
static int __init move_arstlog2sysmem(void)
{
    void __iomem *arstlog_addr = NULL;
    char *pbuffer;
    char aName[] = "acpu_rstlog";

    if (!himntn_gobal_resetlog){
        return 0;
    }

    if(0 == g_mem_arstlogaddr)
    {
        return 0;
    }
    /*调用get_arstlogaddr获取a核异常记录首地址,并转化成内核可用的虚地址*/
    arstlog_addr = ioremap(g_mem_arstlogaddr, SIZE_OF_MEM_FOR_ARSTLOG_KERNEL);
    pbuffer= (char *)arstlog_addr;
    pbuffer_of_arstlog = (char *)vmalloc(SIZE_OF_MEM_FOR_ARSTLOG_KERNEL);/*此段内存只在硬狗复位异常申请，不影响正常流程，不再free*/
    if(NULL == pbuffer_of_arstlog)
    {
        printk("move_arstlog2sysmem: alloc memory failed!\n");
        /*直接返回，防止空指针访问*/
        return 0;
    }
    /*转存A核异常文件*/
    memcpy(pbuffer_of_arstlog, pbuffer, SIZE_OF_MEM_FOR_ARSTLOG_KERNEL);
    create_dump_virt_mem_proc_file(aName, pbuffer_of_arstlog, SIZE_OF_MEM_FOR_ARSTLOG_KERNEL);
    return 0;
}
arch_initcall(move_arstlog2sysmem);

static int __init move_mcurstlog2sysmem(void)
{
    void __iomem *mcurstlog_addr = NULL;
    char *pbuffer;
    char aName[] = "mcu_rstlog";
    char bName[] = "mcu_rstsys";
    char cName[] = "mcu_rstsram";

    if (!himntn_gobal_resetlog){
        return 0;
    }

    if(0 == g_mem_mcurstlogaddr)
    {
        return 0;
    }

    /*调用get_mcurstlogaddr获取a核异常记录首地址,并转化成内核可用的虚地址*/
    mcurstlog_addr = ioremap(g_mem_mcurstlogaddr,
        SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL+SIZE_OF_SRAM_FOR_MCU_KERNEL+SIZE_OF_MEM_FOR_MCUSYS_KERNEL);
    pbuffer= (char *)mcurstlog_addr;
    pbuffer_of_mcurstlog = (char *)vmalloc(SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL+SIZE_OF_SRAM_FOR_MCU_KERNEL+SIZE_OF_MEM_FOR_MCUSYS_KERNEL);
    if(NULL == pbuffer_of_mcurstlog)
    {
        printk("move_mcurstlog2sysmem: alloc memory failed!\n");
        return 0;
    }

    /*转存MCU异常文件*/
    memcpy(pbuffer_of_mcurstlog, pbuffer, SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL+SIZE_OF_SRAM_FOR_MCU_KERNEL+SIZE_OF_MEM_FOR_MCUSYS_KERNEL);
    create_dump_virt_mem_proc_file(aName, pbuffer_of_mcurstlog, SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL);
    create_dump_virt_mem_proc_file(bName, pbuffer_of_mcurstlog+SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL, SIZE_OF_MEM_FOR_MCUSYS_KERNEL);
    create_dump_virt_mem_proc_file(cName, pbuffer_of_mcurstlog+SIZE_OF_MEM_FOR_MCURSTLOG_KERNEL+SIZE_OF_MEM_FOR_MCUSYS_KERNEL, SIZE_OF_SRAM_FOR_MCU_KERNEL);


    return 0;
}
arch_initcall(move_mcurstlog2sysmem);

static int __init move_modemrstlog2sysmem(void)
{
    void __iomem *modemrstlog_addr = NULL;
    char *pbuffer;
    char aName[] = "modem_rstlog";

    if (!himntn_gobal_resetlog){
        return 0;
    }

    if(0 == g_mem_modemrstlogaddr)
    {
        return 0;
    }
    /*调用get_mcurstlogaddr获取a核异常记录首地址,并转化成内核可用的虚地址*/
    modemrstlog_addr = ioremap(g_mem_modemrstlogaddr, SIZE_OF_MEM_FOR_MODEMRSTLOG_KERNEL);
    pbuffer= (char *)modemrstlog_addr;
    pbuffer_of_modemrstlog = (char *)vmalloc(SIZE_OF_MEM_FOR_MODEMRSTLOG_KERNEL);
    if(NULL == pbuffer_of_modemrstlog)
    {
        printk("move_modemrstlog2sysmem: alloc memory failed!\n");
        return 0;
    }
    /*转存MCU异常文件*/
    memcpy(pbuffer_of_modemrstlog, pbuffer, SIZE_OF_MEM_FOR_MODEMRSTLOG_KERNEL);
    create_dump_virt_mem_proc_file(aName, pbuffer_of_modemrstlog, SIZE_OF_MEM_FOR_MODEMRSTLOG_KERNEL);
    return 0;
}
arch_initcall(move_modemrstlog2sysmem);


int proc_read_core_flag(char *page, char **start, off_t off, int count, int *eof, void *data)
{

	unsigned char result[STRINGLEN] = {0};

#ifdef  DEBUG
	int index = 0;
#endif

	/* read nvme*/
	etb_nve_read( result );

#ifdef  DEBUG
	printk("=========Read result================\n");
	for(index = 0; index < STRINGLEN - 1; index++)
	{
		printk("%#x ", result[index]);
	}
#endif

	memcpy(page, &result[0], STRINGLEN);

#ifdef  DEBUG
	printk("=========after copy================\n");
	for(index = 0; index < STRINGLEN - 1; index++)
	{
		printk("%#x ", page[index]);
	}
	printk("\n=========after copy============\n");
#endif

	return STRINGLEN;
}

int proc_write_core_flag(struct file *file, const char *buffer, unsigned long count, void *data)
{
	return 0;
}


static int __init proc_core_flag_init(void)
{
#ifdef DEBUG
	printk("=======begain proc_core_flag_init=========\n");
#endif
	if (!himntn_gobal_resetlog){
		return 0;
	}

	core_trace = proc_mkdir("core_trace", NULL);
	core_flag_file = create_proc_entry("core_flag", S_IRUGO, core_trace);
	core_flag_file->read_proc = proc_read_core_flag;
	core_flag_file->write_proc = proc_write_core_flag;

#ifdef DEBUG
    printk("=======end proc_core_flag_init=========\n");
#endif

	return 0;
}

static void __exit proc_core_flag_exit(void)
{
	remove_proc_entry("core_flag",core_trace);
	remove_proc_entry("core_trace", NULL);
}

module_init(proc_core_flag_init);
module_exit(proc_core_flag_exit);

static int proc_balong_reset_show(struct seq_file *m, void *v)
{

	seq_printf(m, "%d", !himntn_gobal_resetlog);

	return 0;
}

static int proc_balong_reset_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_balong_reset_show, NULL);
}

static const struct file_operations proc_balong_reset_fops = {
	.open = proc_balong_reset_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init proc_balong_reset_init(void)
{
	balong_create_stats_proc_entry("close", S_IRUGO, &proc_balong_reset_fops, NULL);

	return 0;
}
module_init(proc_balong_reset_init);

/*Added by y65256 for wdg log save On 2013-6-8 End*/
MODULE_DESCRIPTION("Hisilicon Memory/Register Dump Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");



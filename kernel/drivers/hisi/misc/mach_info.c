/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  mach_info.c    hisi machine system information, such as slice, rtc, memory .etc
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
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/workqueue.h>		/* For workqueue... */
#include <linux/notifier.h>			/* For notifier... */
#include <linux/io.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <mach/platform.h>
#include <mach/board.h>
#include <mach/util.h>
#include <soc_ao_sctrl_interface.h> /* For slice reg addr */

/*****************************************************************************
 Description : get slice/rtc value declaration, for example
                    mach_get_slice_value
                    /proc/balong/slice
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
#define MACH_GET_TIME_VALUE_DELCARE(NAME, BASE, SIZE, STRING)	\
\
static int mach_ ## NAME ## _proc_open(struct inode *inode, struct file *file)\
{\
	return single_open(file, mach_ ## NAME ## _proc_show, NULL);\
}\
\
static const struct file_operations mach_ ## NAME ## _proc_fops = {\
	.open = mach_ ## NAME ## _proc_open,\
	.read = seq_read,\
	.llseek = seq_lseek,\
	.release = single_release,\
};\
\
static int __init proc_mach_ ## NAME ## _init(void)\
{\
	mach_ ## NAME ## _base = ioremap(BASE, SIZE);\
	if (NULL == mach_ ## NAME ## _base){\
		printk(KERN_ERR"%s ioremap fail !\n", STRING);\
		return -ENOMEM;\
	}\
	balong_create_stats_proc_entry(STRING, S_IRUGO, &mach_ ## NAME ## _proc_fops, NULL);\
\
	return 0;\
}\
module_init(proc_mach_ ## NAME ## _init);\
\
static void __exit proc_mach_ ## NAME ## _exit(void)\
{\
	balong_remove_stats_proc_entry(STRING);\
\
	if (mach_ ## NAME ## _base){\
		iounmap(mach_ ## NAME ## _base);\
		mach_ ## NAME ##_base = NULL;\
	}\
\
	return;\
}\
module_exit(proc_mach_ ## NAME ## _exit);

#define MACH_GET_TIME_VALUE_32BIT_DEFINE(NAME, OFFSET, STRING)\
/*mapped virtual address*/\
static void __iomem *mach_ ## NAME ## _base = NULL;\
\
static int mach_get_ ## NAME ## _value(unsigned int *val)\
{\
	if (NULL == val){\
		printk(KERN_ERR"%s param error !\n", __FUNCTION__);\
		return -EFAULT;\
	}\
\
	if (NULL == mach_ ## NAME ## _base){\
		printk(KERN_ERR"%s %s not initialized yet !\n",\
				__FUNCTION__,STRING);\
		return -EFAULT;\
	}\
\
	*val = readl(mach_ ## NAME ## _base + OFFSET);\
\
	return 0;\
}\
\
static inline unsigned int get_ ## NAME ## _timer_value(void)\
{\
	unsigned int val;\
	int ret;\
\
	ret = mach_get_ ## NAME ## _value(&val);\
	if (0 != ret) {\
		printk(KERN_ERR"get %s error !\n", STRING);\
		return 0;\
	}\
\
	return val;\
}\
\
static int mach_ ## NAME ## _proc_show(struct seq_file *m, void *v)\
{\
	unsigned int val = get_ ## NAME ## _timer_value();\
\
	seq_printf(m, "%u\n", val);\
\
	return 0;\
}\

#define MACH_GET_TIME_VALUE_64BIT_DEFINE(NAME, OFFSET_LOW, OFFSET_HIGH, STRING)\
/*mapped virtual address*/\
static void __iomem *mach_ ## NAME ## _base = NULL;\
static unsigned int get_ ## NAME ## _timer_value(unsigned int *high_32bit, unsigned int *low_32bit)\
{\
    unsigned int first_low32 = 0;\
    unsigned int first_high32 = 0;\
    unsigned int second_low32 = 0;\
    unsigned int second_high32 = 0;\
\
	if (NULL == mach_ ## NAME ## _base){\
		printk(KERN_ERR"%s %s not initialized yet !\n",\
				__FUNCTION__,STRING);\
		return -EFAULT;\
	}\
\
    if (NULL == low_32bit){\
    	printk(KERN_ERR"%s %s param error !\n", __FUNCTION__,STRING);\
        return -EINVAL; \
    }\
\
    first_low32 = readl(mach_ ## NAME ## _base + OFFSET_LOW);\
    first_high32 = readl(mach_ ## NAME ## _base + OFFSET_HIGH);\
    second_low32 = readl(mach_ ## NAME ## _base + OFFSET_LOW);\
    second_high32 = readl(mach_ ## NAME ## _base + OFFSET_HIGH);\
    if (second_low32 < first_low32){  \
        if (high_32bit != NULL) {  \
            *high_32bit = (second_high32 - 1);  \
        }  \
    }  \
    else {  \
        if (high_32bit != NULL) {  \
            *high_32bit = first_high32;  \
        }  \
    }  \
    *low_32bit = first_low32;  \
    return 0;  \
}\
\
static int mach_ ## NAME ## _proc_show(struct seq_file *m, void *v)\
{\
	unsigned int val_low, val_high;\
	get_ ## NAME ## _timer_value(&val_high, &val_low);\
	seq_printf(m, "high:%u\nlow :%u\n", val_high, val_low);\
	return 0;\
}\

MACH_GET_TIME_VALUE_32BIT_DEFINE(rtc, 0x0, "rtc")
MACH_GET_TIME_VALUE_DELCARE(rtc, REG_BASE_RTC, REG_RTC_IOSIZE, "rtc")
#if 0 /*for udp later*/
MACH_GET_TIME_VALUE_64BIT_DEFINE(slice, \
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_ADDR(REG_BASE_SLICE) - REG_BASE_SLICE,\
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_ADDR(REG_BASE_SLICE) - REG_BASE_SLICE,\
    "slice")
#endif
MACH_GET_TIME_VALUE_32BIT_DEFINE(slice, (SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_ADDR(REG_BASE_SLICE) - REG_BASE_SLICE), "slice")
MACH_GET_TIME_VALUE_DELCARE(slice, REG_BASE_SLICE, REG_SLICE_IOSIZE, "slice")



/*****************************************************************************
 Description : get system rtc value
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
unsigned int BSP_GET_RTC_VALUE(void)
{
	return get_rtc_timer_value();
}
EXPORT_SYMBOL(BSP_GET_RTC_VALUE);

/*****************************************************************************
 Description : get system slice value
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
int DRV_GET_BBP_TIMER_VALUE(unsigned int  *pulHigh32bitValue,  unsigned int  *pulLow32bitValue)
{
#if 0/*for udp later*/
	return get_slice_timer_value(pulHigh32bitValue, pulLow32bitValue);
#else
    *pulLow32bitValue = get_slice_timer_value();
    return 0;
#endif
}
EXPORT_SYMBOL(DRV_GET_BBP_TIMER_VALUE);

/*****************************************************************************
 Description : get free memory size (in KB)
		      get it from sysinfo by si_meminfo
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static inline unsigned long mach_get_free_memory_value(void)
{
	struct sysinfo i;

#define K(x) ((x) << (PAGE_SHIFT - 10))
	si_meminfo(&i);

	return K(i.freeram);
}

/*****************************************************************************
 Description : get system free memory value (in KB)
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
unsigned long DRV_GET_FREE_MEMORY_VALUE(void)
{
	return mach_get_free_memory_value();
}
EXPORT_SYMBOL(DRV_GET_FREE_MEMORY_VALUE);



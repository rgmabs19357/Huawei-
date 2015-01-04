/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  hiwdtv100_wdt.c    hisi watchdog v100 kernel device driver
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
#include <linux/interrupt.h>		/* For request_irq*/
#include <linux/io.h>				/* For writel */
#include <linux/vmalloc.h>			/* For vmalloc */
#include <general_sram_map.h>
#include <mach/util.h>
#include <linux/irq.h>				/* For file operations */
#include <mach/platform.h>
#include <mach/ddr_map.h>
#include <BSP.h>

/*****************************************************************************
 Description : bindary dump delcaration, and proc file system defination
                    we ioremap the register/memory region to user space proc file
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static ssize_t reset_st_read(struct file *file, char __user *userbuf,
			size_t bytes, loff_t *off)
{
	char *buf = "reset st module help: \n"\
				"echo 1 : raise hifi freeze irq \n"\
				"echo 2 : raise modem freeze irq \n"\
				"echo 3 : raise mcu panic irq \n"\
				"echo 4 : raise modem panic irq \n";
	ssize_t size = strlen(buf);

	if (0 != *off){
		return 0;
	}

	if (bytes < size){
		return 0;
	}

	if (copy_to_user(userbuf, buf, size)){
		return 0;
	}

	*off += size;

	return size;
}

static ssize_t reset_st_write(struct file *file, const char __user *userbuf,
		     size_t bytes, loff_t *off)
{
	char buff;

	if (copy_from_user(&buff, userbuf, 1)){
		return 0;
	}

	switch (buff) {
	case '1':
		generic_handle_irq(IRQ_WD1);
		break;
	case '2':
		generic_handle_irq(IRQ_CM3WD0);
		break;
	case '3':

		break;
	case '4':

		break;
	default:

		break;
	}

	return bytes;
}


static const struct file_operations reset_st_proc_fops = {
	.read = reset_st_read,
	.write = reset_st_write,
};

static char __iomem *ombuff = NULL;
static off_t offset = 0;

/*****************************************************************************
 Description :android freeze flag check and initilize, if freeze reset, launch workqueue to record
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static int __init reset_st_init(void)
{
	ombuff = (char __iomem *)vmalloc(32*1024*1024);

	balong_create_base_proc_entry("reset_st", 0, &reset_st_proc_fops, NULL);

	return 0;
}
module_init(reset_st_init);



BSP_S32 BSP_MNTN_OmDrvTraceSend(BSP_U16 usPrimId, BSP_U32 ulModuleId, BSP_U8 *buffer, BSP_U32 ulLength)
{
	memcpy(ombuff + offset, buffer, ulLength);
	*(ombuff + offset + ulLength + 1) = '\n';

	offset += (ulLength + 1);

	return 0;
}


MODULE_DESCRIPTION("Hisilicon device RESET Management ST module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


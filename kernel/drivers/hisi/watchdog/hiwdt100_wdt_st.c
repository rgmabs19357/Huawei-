/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  hiwdt100_wdt.c    hisi watchdog hiwdt100 kernel driver program
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
#include <linux/watchdog.h>		/* For the watchdog specific items */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/platform_device.h>	/* For platform_driver framework */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/io.h>				/* For inb/outb/... */
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <soc_irqs.h>
#include <soc_sctrl_interface.h>
#include <mach/util.h>

#define DEBUG 1

#ifdef DEBUG
#define DBG(args...)	printk(args)
#else
#define DBG(args...)	do { } while(0)
#endif

#define DEFAULT_WDT_PERIOD   5

/*register offset definition*/
#define WDG_LOAD		0x0000
#define WDG_VALUE		0x0004
#define WDG_CONTROL 	0x0008
#define WDG_INTCLR		0x000c
#define WDG_RIS			0x0010
#define WDG_MIS			0x0014
#define WDG_LOCK		0x0018

/*watchdog interval (second)*/
static int wdt_interval = DEFAULT_WDT_PERIOD;

/*****************************************************************************
 Description : watchdog irq handle , write WDT_INTCLR register to keep watchdog alive
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static irqreturn_t hiwdt100_wdt_irq(int irqno, void *param)
{
	return IRQ_HANDLED;
}

static int __init hiwdt100_wdt_init(void)
{
	unsigned long freq;
	void __iomem *wdt_base;
	int ret;

	DBG("probe: hiwdt100 initial\r\n");

	wdt_base = ioremap(REG_BASE_WD0, REG_WD0_IOSIZE);
	if (wdt_base == NULL) {
		DBG("failed to ioremap() region\n");
		ret = -EINVAL;
		goto err_map;
	}
	DBG("probe: mapped wdt_base=%p\n", wdt_base);

	ret = request_irq(IRQ_WD0, hiwdt100_wdt_irq, 0, "hiwdt100", NULL);
	if (ret != 0) {
		DBG("failed to install irq (%d)\n", ret);
		ret = -EINTR;
		goto err_irq;
	}

	freq = 24000000;

    /*set count*/
	writel(freq * wdt_interval, wdt_base + WDG_LOAD);
	/*set enable*/
	writel(((1<<1) | (1<<0)), wdt_base + WDG_CONTROL);

	DBG("probe : watchdog clock active, interval %u second, count %lu\n", wdt_interval, freq * wdt_interval);

	return 0;

 err_irq:
	iounmap(wdt_base);
 err_map:

	return ret;
}


module_init(hiwdt100_wdt_init);

MODULE_DESCRIPTION("Hisilicon WatchDog Timer hiwdt100 ST Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


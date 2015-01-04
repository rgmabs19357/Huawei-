/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  hiwdt100_wdt.c    hisilicon watchdog IP hiwdt100 driver
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
#include <linux/hiwdt100_wdt.h>
#include <mntn/excDrv.h>
#include <multicore/ipcm/bsp_private_ipc.h>
#include "pwrctrl_multi_dfs_asm.h"

#define DEBUG 1

#ifdef DEBUG
#define DBG(args...)	printk(args)
#else
#define DBG(args...)	do { } while(0)
#endif

#define DEFAULT_WDT_PERIOD   5       /*5 second*/
#define EARLY_WDT_PERIOD        30	/* 1min wdt reset */
#define MAX_WDT_PERIOD       86400   /*1 day*/

/*register offset definition*/
#define WDG_LOAD		0x0000
#define WDG_VALUE		0x0004
#define WDG_CONTROL 	0x0008
#define WDG_INTCLR		0x000c
#define WDG_RIS			0x0010
#define WDG_MIS			0x0014
#define WDG_LOCK		0x0018
#define UNLOCK_KEY      0x1acce551
struct hiwdt100_wdt
{
	void __iomem *membase; 	/*io mapped address*/
	struct clk *wdt_clk;    /*clock*/
	unsigned int freq;	    /*watchdog clock frequence ,for caculate countdown value*/
	unsigned int on;
	unsigned int trigger;
	unsigned int interval;  /*time interval (second)*/
	unsigned int count;	    /*countdown value = period*freq, set to WDT_LOAD register*/
	unsigned int irq;       /*irq number*/
	phys_addr_t iobase;     /*watchdog register physical address*/
	size_t size;            /*watchdog register space size*/
};

int early_hiwdt100_init(phys_addr_t membase, char *clk_name)
{
    struct clk *wdt_clk = NULL;
    void __iomem *wdt_base = NULL;
    unsigned long freq;

    if (check_himntn(HIMNTN_CLOSE_ACPU_WDT)){
        return 0;
    }

    wdt_base = IO_ADDRESS(membase);
    if (wdt_base == NULL) {
        pr_err("%s: failed to ioremap() region\n", __func__);
        return -1;
    }

    wdt_clk = clk_get(NULL, clk_name);
    if (IS_ERR(wdt_clk)) {
        pr_err("%s: failed to ioremap() region\n", __func__);
        return -1;
    }
    
    clk_enable(wdt_clk);
    freq = clk_get_rate(wdt_clk);
    pr_info("%s : watchdog clock frequence %ld \n", __func__, freq);

    freq = freq * EARLY_WDT_PERIOD;

    /*set count*/
    writel(UNLOCK_KEY, wdt_base + WDG_LOCK);
    writel(freq, wdt_base + WDG_LOAD);
    /*set enable*/
    writel(((1<<1) | (1<<0)), wdt_base + WDG_CONTROL);

    writel(0, wdt_base + WDG_LOCK);

    BSP_DRV_PRIVATE_IPCIntInit();
    BSP_PRIVATE_IPC_IntEnable(IPC2_NOSEC_ACPUWDT_INT_NUM);

    return 0;
}

static ssize_t attr_get_on(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	return sprintf(buf, "%d\n", wdt_data->on);
}

static ssize_t attr_set_on(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t size)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int on;
	unsigned int val;

	/* only root can play with this */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	if (kstrtouint(buf, 0, &on))
		return -EINVAL;

	if ((0 != on) && (1 != on)) {
		dev_err(dev, "%s: on should be 0 or 1\n", __func__);
		return -EINVAL;
	}

	if (1 == on){
		val = ((1<<1) | (1<<0));  /*11*/
	}else{
		val = (1<<1);  /*10*/
	}

	/*make effective */
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(wdt_data->count, wdt_data->membase + WDG_LOAD);
	writel(val, wdt_data->membase + WDG_CONTROL);
	writel(0, wdt_data->membase + WDG_LOCK);

    wdt_data->on = on;

	return size;
}

static ssize_t attr_get_interval(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	return sprintf(buf, "%d\n", wdt_data->interval);
}

static ssize_t attr_set_interval(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t size)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int interval;

	/* only root can play with this */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	if (kstrtouint(buf, 0, &interval))
		return -EINVAL;

	if ((0 == interval) || (interval > MAX_WDT_PERIOD)) {
		dev_err(dev, "%s: interval should between %d and %d\n", __func__, 0, MAX_WDT_PERIOD);
		return -EINVAL;
	}

	wdt_data->interval = interval;
	wdt_data->count = wdt_data->freq * interval;

	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(wdt_data->count, wdt_data->membase + WDG_LOAD);
	writel(0, wdt_data->membase + WDG_LOCK);

	return size;
}

static ssize_t attr_get_base(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	return sprintf(buf, "0x%p\n", wdt_data->membase);
}

static ssize_t attr_get_value(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int val;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	val = readl(wdt_data->membase + WDG_VALUE);
	return sprintf(buf, "0x%x\n", val);
}

static ssize_t attr_get_load(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int val;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	val = readl(wdt_data->membase + WDG_LOAD);
	return sprintf(buf, "0x%x\n", val);
}

static ssize_t attr_get_ctrl(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int val;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	val = readl(wdt_data->membase + WDG_CONTROL);
	return sprintf(buf, "0x%x\n", val);
}


static ssize_t attr_get_trigger(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct hiwdt100_wdt *wdt_data;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);
	return sprintf(buf, "%d\n", wdt_data->trigger);
}

static ssize_t attr_set_trigger(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t size)
{
	struct hiwdt100_wdt *wdt_data;
	unsigned int trigger;


	/* only root can play with this */
	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	if (kstrtouint(buf, 0, &trigger))
		return -EINVAL;

	if ((0 != trigger) && (1 != trigger)) {
		dev_err(dev, "%s: trigger should be 0 or 1\n", __func__);
        return -EINVAL;
    }

    wdt_data->trigger = trigger;

	return 0;
}


static struct device_attribute attributes[] = {

	__ATTR(on, 0664, attr_get_on, attr_set_on),
	__ATTR(interval, 0664, attr_get_interval, attr_set_interval),
	__ATTR(trigger, 0664, attr_get_trigger, attr_set_trigger),
	__ATTR(base, 0444, attr_get_base, NULL),
	__ATTR(reg_value, 0444, attr_get_value, NULL),
	__ATTR(reg_load, 0444, attr_get_load, NULL),
	__ATTR(reg_ctrl, 0444, attr_get_ctrl, NULL),
};

static int create_sysfs_interfaces(struct device *dev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		if (device_create_file(dev, attributes + i))
			goto error;
	return 0;

error:
	for ( ; i >= 0; i--)
		device_remove_file(dev, attributes + i);
	dev_err(dev, "%s:Unable to create interface\n", __func__);
	return -1;
}

static int remove_sysfs_interfaces(struct device *dev)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(attributes); i++)
		device_remove_file(dev, attributes + i);
	return 0;
}
static irqreturn_t hiwdt100_wdt_irq(int irqno, void *param)
{
	struct device *dev = (struct device *)param;
	struct hiwdt100_wdt *wdt_data;

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

    if (1 == wdt_data->trigger)
        return IRQ_HANDLED;

	/*write any value to WDG_INTCLR to keep watchdog alive*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
    writel(0xffffffff,  wdt_data->membase + WDG_INTCLR);
	writel(0, wdt_data->membase + WDG_LOCK);

	return IRQ_HANDLED;
}
static int __devinit hiwdt100_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct hiwdt100_wdt_platform_data *platform_data;
	struct hiwdt100_wdt *wdt_data;
	struct clk *wdt_clk = NULL;
	void __iomem *wdt_base = NULL;
	unsigned long freq;
	int ret;

	DBG("probe: hiwdt100 probe id %d.\r\n", pdev->id);
	
	wdt_data = (struct hiwdt100_wdt *)kmalloc(sizeof(struct hiwdt100_wdt), GFP_KERNEL);
	if (NULL == wdt_data){
		dev_err(dev, "kmalloc fail\n");
		ret = -EBUSY;
		goto err_out;
	}

	platform_data = (struct hiwdt100_wdt_platform_data *)dev->platform_data;
	if (NULL == platform_data){
		dev_err(dev, "no hiwdt100_wdt_platform_data in platform device\n");
		ret = -EBUSY;
		goto err_free;
	}

	if (!request_mem_region(platform_data->iobase, platform_data->size, pdev->name)) {
		dev_err(dev, "failed to get memory region\n");
		ret = -EBUSY;
		goto err_free;
	}

	wdt_base = ioremap(platform_data->iobase, platform_data->size);
	if (wdt_base == NULL) {
		dev_err(dev, "failed to ioremap() region\n");
		ret = -EINVAL;
		goto err_req;
	}
	DBG("probe: mapped wdt_base=%p\n", wdt_base);

	/*set disable before request_irq*/
	writel(UNLOCK_KEY, wdt_base + WDG_LOCK);
	writel(((0<<1) | (0<<0)), wdt_base + WDG_CONTROL);
	writel(0xffffffff,  wdt_base + WDG_INTCLR);
	writel(0, wdt_base + WDG_LOCK);

	ret = request_irq(platform_data->irq, hiwdt100_wdt_irq, 0, pdev->name, dev);
	if (ret != 0) {
		dev_err(dev, "failed to install irq (%d)\n", ret);
		ret = -EINTR;
		goto err_map;
	}

	/* there must be watchdog clock definition,
	   to caculate watchdog countdown value*/
	wdt_clk = clk_get(NULL, platform_data->clk_name);
	if (IS_ERR(wdt_clk)) {
		dev_err(dev, "failed to find watchdog clock source\n");
		ret = -ENXIO;
		goto err_irq;
	}

	freq = clk_get_rate(wdt_clk);
	dev_info(dev, "probe : watchdog clock frequence %ld \n", freq);

	wdt_data->membase = wdt_base;
	wdt_data->wdt_clk = wdt_clk;
	wdt_data->freq = freq;
	wdt_data->on = 1;
	wdt_data->trigger = 0;
	wdt_data->interval = DEFAULT_WDT_PERIOD;
	wdt_data->count = freq * DEFAULT_WDT_PERIOD;
	wdt_data->irq = platform_data->irq;
	wdt_data->iobase = platform_data->iobase;
	wdt_data->size = platform_data->size;

	dev_set_drvdata(dev, wdt_data);

    /*set count*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(wdt_data->count, wdt_data->membase + WDG_LOAD);
	/*set enable*/
	writel(((1<<1) | (1<<0)), wdt_data->membase + WDG_CONTROL);
	writel(0, wdt_data->membase + WDG_LOCK);

	create_sysfs_interfaces(dev);

	dev_info(dev, "watchdog probe : watchdog clock active, interval %u second, count %u\n", wdt_data->interval, wdt_data->count);

	return 0;

 err_irq:
 	free_irq(wdt_data->irq, dev);
 err_map:
	iounmap(wdt_base);
 err_req:
	release_mem_region(platform_data->iobase, platform_data->size);
 err_free:
 	kfree(wdt_data);
 err_out:
	dev_err(dev, "hiwdt100 probe fail !\n");
	return ret;

}


static void hiwdt100_wdt_turnoff(struct platform_device *pdev)
{
	struct device *dev;
	struct hiwdt100_wdt *wdt_data;

	dev = &pdev->dev;
	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	/*set disable*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(0, wdt_data->membase + WDG_CONTROL);
	writel(0, wdt_data->membase + WDG_LOCK);

	/*set disable clock*/
	clk_disable(wdt_data->wdt_clk);

	return;
}


static void hiwdt100_wdt_shutdown(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "watchdog timer shutdown\n");

	hiwdt100_wdt_turnoff(pdev);

	return;
}


static int hiwdt100_wdt_suspend(struct platform_device *pdev, pm_message_t state)
{
	dev_info(&pdev->dev, "watchdog timer suspend %d \n", state.event);

	hiwdt100_wdt_turnoff(pdev);

	return 0;
}


static int hiwdt100_wdt_resume(struct platform_device *pdev)
{
	struct device *dev;
	struct hiwdt100_wdt *wdt_data;
	unsigned int val;
	int ret = 0;

	dev_info(&pdev->dev, "watchdog timer shutdown \n");

	dev = &pdev->dev;
	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	/*set enable clock*/
	ret = clk_enable(wdt_data->wdt_clk);
	if (ret) {
        dev_err(&pdev->dev, "watchdog clock enable fail \n");
	    return -1;
	}

	/*set cound down value*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(wdt_data->count, wdt_data->membase + WDG_LOAD);
	writel(0, wdt_data->membase + WDG_LOCK);

	if (1 == wdt_data->on){
		val = ((1<<1) | (1<<0));  /*11*/
	} else {
		val = (1<<1);  /*10*/
	}

	/*set enable wdt ip*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(val, wdt_data->membase + WDG_CONTROL);
	writel(0, wdt_data->membase + WDG_LOCK);

	return 0;
}
static int __devexit hiwdt100_wdt_remove(struct platform_device *pdev)
{
	struct device *dev;
	struct hiwdt100_wdt *wdt_data;
	struct clk *wdt_clk;

	dev_info(&pdev->dev, "watchdog timer remove \n");

	dev = &pdev->dev;

	remove_sysfs_interfaces(dev);

	wdt_data = (struct hiwdt100_wdt *)dev_get_drvdata(dev);

	/* disable wdt ip*/
	writel(UNLOCK_KEY, wdt_data->membase + WDG_LOCK);
	writel(0, wdt_data->membase+ WDG_CONTROL);
	writel(0, wdt_data->membase + WDG_LOCK);

	/*disable and release(clk_put) clock*/
	wdt_clk = wdt_data->wdt_clk;
	clk_disable(wdt_clk);
	clk_put(wdt_clk);

	/*clear irq, memmap, region*/
	free_irq(wdt_data->irq, dev);
	iounmap(wdt_data->membase);
	release_mem_region(wdt_data->iobase, wdt_data->size);

    kfree(wdt_data);

	return 0;
}

/* Description : platform driver definition*/
static struct platform_driver platform_hiwdt100_wdt_driver = {
	.probe = hiwdt100_wdt_probe,
	.remove = hiwdt100_wdt_remove,
	.shutdown = hiwdt100_wdt_shutdown,
	.suspend = hiwdt100_wdt_suspend,
 	.resume = hiwdt100_wdt_resume,
 	.driver = {
		.owner = THIS_MODULE,
		.name = "hiwdt100",
	},
};

static int __init hiwdt100_wdt_init(void)
{
	if (check_himntn(HIMNTN_CLOSE_ACPU_WDT)){
		return 0;
	}
	
	return platform_driver_register(&platform_hiwdt100_wdt_driver);
}

static void __exit hiwdt100_wdt_exit(void)
{
	platform_driver_unregister(&platform_hiwdt100_wdt_driver);

	return;
}

late_initcall_sync(hiwdt100_wdt_init);
module_exit(hiwdt100_wdt_exit);

MODULE_DESCRIPTION("Hisilicon WatchDog Timer hiwdt100 Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


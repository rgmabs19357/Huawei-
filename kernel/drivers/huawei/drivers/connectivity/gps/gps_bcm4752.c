/*
 *
 * GPS driver define and register
 *
 * Copyright (C) 2012 Hisilicon, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/amba/bus.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/mux.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/system.h>
#include <asm/pmu.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/lm.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/early-debug.h>
#include <mach/gpio.h>
#include <mach/clk_name_interface.h>
#include <mach/iomux_blocks.h>
#include "dev_gps.h"

typedef struct gps_bcm_info {
	unsigned long       gpioid_en;
	unsigned long       gpioid_refclk;
	struct clk          *clk;
	struct iomux_block  *piomux_block;
	struct block_config *pblock_config;
} GPS_BCM_INFO;


static int __devinit k3_gps_bcm_probe(struct platform_device *pdev)
{
	GPS_BCM_INFO *gps_bcm;
	struct resource *res;
	int ret = 0;

	gps_bcm = kzalloc(sizeof(GPS_BCM_INFO), GFP_KERNEL);
	if (!gps_bcm) {
		dev_err(&pdev->dev, "Alloc memory failed\n");
		return -ENOMEM;
	}

	platform_set_drvdata(pdev, gps_bcm);

	/* Set iomux NORMAL, If set iomux failed, we still go on */
	gps_bcm->piomux_block  = iomux_get_block(BLOCK_GPS);
	if (!gps_bcm->piomux_block)
		dev_err(&pdev->dev, "Get gps iomux_block failed\n");

	gps_bcm->pblock_config = iomux_get_blockconfig(BLOCK_GPS);
	if (!gps_bcm->pblock_config)
		dev_err(&pdev->dev, "Get gps block_config failed\n");

	if ((gps_bcm->piomux_block) && (gps_bcm->pblock_config)) {
		ret = blockmux_set(gps_bcm->piomux_block, gps_bcm->pblock_config, NORMAL);
		if (ret)
			dev_err(&pdev->dev, "Set gps iomux to NORMAL failed, ret=%d\n", ret);
	}

	/* Get enable gpio */
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_GPS_BCM_VBAT_ENABLE_NAME);
	if (!res) {
		dev_err(&pdev->dev, "Get enable gpio resourse failed\n");
		ret = -ENXIO;
		goto err_free;
	}
	gps_bcm->gpioid_en = res->start;

	ret = gpio_request(gps_bcm->gpioid_en, "gps_enbale");
	if (ret < 0) {
		dev_err(&pdev->dev,  "gpio_request failed, gpio=%lu, ret=%d\n", gps_bcm->gpioid_en, ret);
		goto err_free;
	}
	gpio_export(gps_bcm->gpioid_en, false);
	gpio_direction_output(gps_bcm->gpioid_en, 0);
	dev_dbg(&pdev->dev,  "Low enable\n");

	/* Get ref_clk gpio, if failed, we still go on  */
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_GPS_BCM_REFCLK_ENABLE_NAME);
	if (!res) {
		dev_err(&pdev->dev, "Get ref_clk gpio resourse failed\n");
		ret = -ENXIO;
	} else {
		gps_bcm->gpioid_refclk = res->start;

		ret = gpio_request(gps_bcm->gpioid_refclk, "gps_refclk");
		if (ret < 0) {
			dev_err(&pdev->dev,  "gpio_request failed, gpio=%lu, ret=%d\n", gps_bcm->gpioid_en, ret);
			goto err_free_gpio_en;
		}
		gpio_export(gps_bcm->gpioid_refclk, false);
		gpio_direction_output(gps_bcm->gpioid_refclk, 0);
		dev_dbg(&pdev->dev,  "Low gpioid_refclk\n");
	}

	/* Set 32KC clock */
	gps_bcm->clk = clk_get(NULL, CLK_PMU32KC);
	if (IS_ERR(gps_bcm->clk)) {
		dev_err(&pdev->dev, "Get gps clk failed\n");
		ret = PTR_ERR(gps_bcm->clk);
		goto err_free_gpio;
	}
	ret = clk_enable(gps_bcm->clk);
	if (ret) {
		dev_err(&pdev->dev, "Enable clk failed, ret=%d\n", ret);
		goto err_free_clk;
	}

	return 0;

err_free_clk:
	clk_put(gps_bcm->clk);

err_free_gpio:
	if(gps_bcm->gpioid_refclk)
		gpio_free(gps_bcm->gpioid_refclk);

err_free_gpio_en:
	gpio_free(gps_bcm->gpioid_en);

err_free:
	kfree(gps_bcm);
	platform_set_drvdata(pdev, NULL);
	return ret;
}

#ifdef CONFIG_PM
static int  k3_gps_bcm_suspend(struct platform_device *pdev, pm_message_t state)
{
	GPS_BCM_INFO *gps_bcm = platform_get_drvdata(pdev);

	if (!gps_bcm) {
		dev_err(&pdev->dev, "gps_bcm is NULL\n");
		return 0;
	}

	printk("[%s] +\n", __func__);

	gpio_set_value(gps_bcm->gpioid_en, 0);

	printk("[%s] -\n", __func__);
	return 0;
}

static int  k3_gps_bcm_resume()
{
	printk("[%s] called\n", __func__);
	return 0;
}
#else

#define k3_gps_bcm_suspend	NULL

#endif /* CONFIG_PM */

static struct platform_driver k3_gps_bcm_driver = {
	.driver	= {
		.name		= "k3_gps_bcm_4752",
		.owner		= THIS_MODULE,
	},
	.probe			= k3_gps_bcm_probe,
	.suspend		= k3_gps_bcm_suspend,
	.resume			= k3_gps_bcm_resume,
};

static int __init k3_gps_bcm_init(void)
{
	return platform_driver_register(&k3_gps_bcm_driver);
}

static void __exit k3_gps_bcm_exit(void)
{
	platform_driver_unregister(&k3_gps_bcm_driver);
}


module_init(k3_gps_bcm_init);
module_exit(k3_gps_bcm_exit);

MODULE_AUTHOR("DRIVER_AUTHOR");
MODULE_DESCRIPTION("GPS Boardcom 4752 driver");
MODULE_LICENSE("GPL");


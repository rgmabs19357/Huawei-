/*
 * arch/arm/mach-k3v2/dev_bt.c
 *
 * Copyright (C) 2012 Hisilicon Co. Ltd.
 *
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

#include <linux/platform_device.h>
#include <mach/dev_bt.h>
#include <mach/gpio.h>

/****************** K3V2 define ******************/
#define	GPIO_BT_EN					(GPIO_21_1)
#define	GPIO_BT_RST					(GPIO_21_0)
#define	GPIO_HOST_WAKEUP			(GPIO_20_6)
#define	GPIO_DEV_WAKEUP				(GPIO_20_7)

static struct bt_dev_info bt_info = {
    .bt_en = GPIO_BT_EN,
    .bt_rst = GPIO_BT_RST,
    .bt_wake_host = GPIO_HOST_WAKEUP,
    .host_wake_bt = GPIO_DEV_WAKEUP,
    .iomux_pwr = "block_btpwr",
    .iomux_pm = "block_btpm",
    .clock_name = "clk_pmu32kb",
    .regulator_name = "bt-io-vcc",    /*GPIO_3_2 BT/WI-FI 1.8V IO enable pin of SFT broad*/
};


 static struct platform_device blue_power_device = {
	.name =	"bt_power",
	.dev  =	{
		.platform_data = &bt_info,
		.init_name = "bt_power",
	},
	.id	= -1,
};


static struct platform_device blue_sleep_device = {
	.name =	"bluesleep",
	.dev  =	{
		.platform_data = &bt_info,
		.init_name = "bluesleep",
	},
	.id	= -1,
};

/* please add platform device in the struct.*/
static struct platform_device *bt_devices[] __initdata = {
	&blue_power_device,
	&blue_sleep_device,
};

static void __init blue_dev_init(void)
{
    /* platform devices were addded here. */
    platform_add_devices(bt_devices, ARRAY_SIZE(bt_devices));
    printk("blue_dev_init");
    return;
}

arch_initcall(blue_dev_init);


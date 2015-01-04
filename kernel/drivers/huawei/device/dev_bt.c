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

 /*============================================================================
=============================================================================*/

#include <linux/platform_device.h>
#include <mach/gpio.h>
#include <hisi/drv_regulator_user.h>
#include <mach/clk_name_interface.h>
#include <mach/iomux_blocks.h>
#include "hsad_connectivity.h"
#include "dev_bt.h"

static struct bt_dev_info bt_info = {
    .bt_en = 0,
    .bt_wake_host = 0,
    .host_wake_bt = 0,
#ifdef CONFIG_MACH_HI6620OEM
    .iomux_bt = BLOCK_BT,
#else
    .iomux_pwr = BLOCK_BTPWR,
    .iomux_pm = BLOCK_BTPM,
#endif
    .clock_name = CLK_PMU32KB,
    .regulator_name = BT_IO_VDD,    /*GPIO_3_2 BT/WI-FI 1.8V IO enable pin of SFT broad*/
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

static int init_bt_dev_info(struct platform_device * pdev)
{
    int en = 0;
    int wakehost = 0;
    int wakebt = 0;
    
    if(pdev)
    {
        en = hsad_get_bt_en();
        wakehost = hsad_get_bt_wake_host();
        wakebt = hsad_get_host_wake_bt();

        if(en < 0)
        {
            pr_err("%s: hsad get gpio bt_en failed\n", __func__);
            return -1;
        }

        if(wakehost < 0)
        {
            pr_err("%s: hsad get gpio bt_wake_host failed\n", __func__);
            return -1;
        }

        if(wakebt < 0)
        {
            pr_err("%s: hsad get gpio host_wake_bt failed\n", __func__);
            return -1;
        }
        
        ((struct bt_dev_info *)pdev->dev.platform_data)->bt_en = en;
        ((struct bt_dev_info *)pdev->dev.platform_data)->bt_wake_host = wakehost;
        ((struct bt_dev_info *)pdev->dev.platform_data)->host_wake_bt = wakebt;
    }

    return 0;
}

static int __init blue_dev_init(void)
{
    /* platform devices were addded here. */
    int i = 0;
    while(i < ARRAY_SIZE(bt_devices))
    {   
        init_bt_dev_info(bt_devices[i]);
        i++;
    }
	
    return platform_add_devices(bt_devices, ARRAY_SIZE(bt_devices));
    
}

device_initcall(blue_dev_init);


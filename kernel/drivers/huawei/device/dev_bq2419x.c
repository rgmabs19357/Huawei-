/*
 * dev_bq2419x.c
 *
 * Copyright (C) 2013 Hisilicon Co. Ltd.
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

#include <mach/irqs.h>
#include <linux/kernel.h>/*array_size is defined in kernel.h*/
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <dev_bq2419x.h>

#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>

#define BQ2419X_INT    "charger/charger_int"
#define BQ2419X_CD     "charger/charger_cd"
#define BQ2419X_OTG    "charger/charger_otg"


static const char *gpios[] = {
    BQ2419X_INT, BQ2419X_CD, BQ2419X_OTG
};

static struct bq2419x_platform_data bq2419x_data =
{
    .max_charger_currentmA = 1000,
    .max_charger_voltagemV = 4208,
    .max_cin_limit_currentmA = 1200,
    .gpio_cd = GPIO_4_0,
    .gpio_otg = GPIO_4_1,
    .gpio_int = GPIO_1_3,
};

static struct i2c_board_info bq2419x_i2c_bus_devs[]= {
	/* bq24161 charge*/
	[0]	=	{
		.type			= "bq2419x_charger",
		.addr			= I2C_ADDR_BQ24192,
		.platform_data 	= &bq2419x_data,
		//.irq				= GPIO_1_3,
	},
};


static int __init bq2419x_dev_init(void)
{
    int status, gpio, i;
    int enable = 0;

    if (get_hw_config_int(BQ2419X_INT, &gpio, NULL )){
        bq2419x_data.gpio_int = gpio;
    }

    if (get_hw_config_int(BQ2419X_CD, &gpio, NULL )){
        bq2419x_data.gpio_cd = gpio;
    }

    if (get_hw_config_int(BQ2419X_OTG, &gpio, NULL )){
        bq2419x_data.gpio_otg = gpio;
    }

    status = i2c_register_board_info(0,&bq2419x_i2c_bus_devs[0], ARRAY_SIZE(bq2419x_i2c_bus_devs));

    if(status)
    {
        printk(KERN_ERR "register bq2419x hardware device error!\n");
    }

    return status;
}

postcore_initcall(bq2419x_dev_init);


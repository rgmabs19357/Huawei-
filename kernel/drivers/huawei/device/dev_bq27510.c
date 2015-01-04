/*
 * dev_bq27510.c
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
#include <dev_bq27510.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>

#define BQ27510_ENABLE  "gas_gauge/bq27510_enable"
#define BQ27510_LOW_INT "gas_gauge/low_power_int"

static struct i2c_board_info bq27510_i2c_bus_devs[]= {
	/* bq27510 coul*/
	[0]	=	{
		.type          = "bq27510-battery",
		.addr          = I2C_ADDR_BQ27510,
		.platform_data = NULL,
		.irq           = GPIO_1_2,
	},
};

static int __init bq27510_dev_init(void)
{
    int status;
    int gpio = 0, enable = 0;

    if (get_hw_config_int(BQ27510_ENABLE, &enable, NULL )){
        if (!enable){
            printk(KERN_ERR "bq27510 disabled !\n");
            return 0;
        }
    }

    if (get_hw_config_int(BQ27510_LOW_INT, &gpio, NULL )){
        bq27510_i2c_bus_devs[0].irq = gpio;
    }

    status = i2c_register_board_info(0,&bq27510_i2c_bus_devs[0], ARRAY_SIZE(bq27510_i2c_bus_devs));

    if(status)
    {
        printk(KERN_ERR "register BQ27510 hardware device error!\n");
    }

    return status;
}

postcore_initcall(bq27510_dev_init);



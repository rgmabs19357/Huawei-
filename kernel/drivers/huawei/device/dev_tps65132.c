/*
 * dev_tps65132.c
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
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <dev_tps65132.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>

#define TPS65132_ENABLE "lcd/tps65132_enable"

static struct i2c_board_info tps65132_i2c_bus_devs[]= {
	[0]	=	{
		.type			= "tps65132",
		.addr			= I2C_ADDR_TPS65132,
		.platform_data 	= NULL,
	},
};

static int __init tps65132_dev_init(void)
{
	int status;
	int enable = 0;
	bool nRet = false;

	nRet = get_hw_config_int(TPS65132_ENABLE, &enable, NULL );
	if (nRet == false){
		pr_info("no tps65132!\n");
		return 0;
	} else if (!enable) {
		pr_info("tps65132 disabled !\n");
		return 0;
	}

	status = i2c_register_board_info(0,&tps65132_i2c_bus_devs[0], ARRAY_SIZE(tps65132_i2c_bus_devs));
	if (status) {
		pr_err("register tps65132 hardware device error!\n");
	}

	return status;
}

postcore_initcall(tps65132_dev_init);



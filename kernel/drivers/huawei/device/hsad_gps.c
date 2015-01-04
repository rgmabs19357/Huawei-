/*
 *
 * Copyright (C) 2013 HUAWEI Device Corp,Ltd.
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
#include <linux/kernel.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <hsad/configdata.h>
#define HSAD_DEV_NAME_LEN 64

int hsad_gps_get_gpio(char *name)
{
    int gpio = 0;

    if (get_hw_config_int(name, &gpio, NULL ) == false)
        return -1;

    return gpio;
}
int hsad_get_gps_en(void)
{
	return hsad_gps_get_gpio("gps/gpio_gps_en");
}

int hsad_get_gps_refclk(void)
{
	return hsad_gps_get_gpio("gps/gpio_gps_refclk");
}


/*
 *
 * GPS device define and register
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
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include <mach/gpio.h>
#include "dev_gps.h"
#include "hsad_gps.h"

//#define GPIO_GPS_BCM_VBAT_ENABLE     (GPIO_6_1)   /*49*/
//#define GPIO_GPS_BCM_REFCLK_ENABLE   (GPIO_11_3)  /*91*/

static struct resource k3_gps_bcm_resources[] = {
	[0] = {
	.name  = GPIO_GPS_BCM_VBAT_ENABLE_NAME,
	.start = 0,
	.end   = 0,
	.flags = IORESOURCE_IO,
	},
	[1] = {
    .name  = GPIO_GPS_BCM_REFCLK_ENABLE_NAME,
	.start = 0,
	.end   = 0,
	.flags = IORESOURCE_IO,
	},
};

static struct platform_device k3_gps_bcm_device = {
	.name = "k3_gps_bcm_4752",
	.id	= 1,
	.dev = {
		.init_name = "gps_bcm_4752",
	},
	.num_resources = ARRAY_SIZE(k3_gps_bcm_resources),
	.resource = k3_gps_bcm_resources,
};


static int __init k3v2_gps_init(void)
{
	k3_gps_bcm_resources[0].start = (resource_size_t)hsad_get_gps_en();
	k3_gps_bcm_resources[0].end = (resource_size_t)hsad_get_gps_en();
	k3_gps_bcm_resources[1].start = (resource_size_t)hsad_get_gps_refclk();
	k3_gps_bcm_resources[1].end = (resource_size_t)hsad_get_gps_refclk();
		
	return platform_device_register(&k3_gps_bcm_device);
}

device_initcall(k3v2_gps_init);

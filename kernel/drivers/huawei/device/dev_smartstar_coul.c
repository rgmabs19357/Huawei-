/*
 * arch/arm/mach-hi6620/dev_smartstar_coul.c
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
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/gpio.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <dev_smartstar_coul.h>

#define SMARTSTAR_COUL_ENABLE "gas_gauge/ss_coul_enable"

static struct resource  smartstar_coul_resource[] = {
    [0] = {
            .name  = "cl_int",
            .start = CL_INT_I_TYPE,
            .end   = CL_INT_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
    [1] = {
            .name  = "cl_out_D_int",
            .start = CL_OUT_I_TYPE,
            .end   = CL_OUT_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
    [2] = {
            .name  = "cl_in_D_int",
            .start = CL_IN_I_TYPE,
            .end   = CL_IN_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
    [3] = {
            .name  = "chg_timer_D_int",
            .start = CHG_TIMER_I_TYPE,
            .end   = CHG_TIMER_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
    [4] = {
            .name  = "load_timer_D_int",
            .start = LOAD_TIMER_I_TYPE,
            .end   = LOAD_TIMER_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
    [5] = {
            .name  = "vbat_int",
            .start = VBAT_INT_I_TYPE,
            .end   = VBAT_INT_I_TYPE,
            .flags = IORESOURCE_IRQ,
    },
};


static struct platform_device smartstar_coul_device = {
    .name                   = "hisi_smartstar_coul",
    .id                             = -1,
    .resource                       = (struct resource	*)&smartstar_coul_resource,
    .num_resources  = ARRAY_SIZE(smartstar_coul_resource),
};


static int __init smartstar_coul_dev_init(void)
{
    int ret = 0, enable = 0;

    if (get_hw_config_int(SMARTSTAR_COUL_ENABLE, &enable, NULL )){
        if (!enable){
            printk(KERN_ERR "smartstar coul disabled !\n");
            return 0;
        }
    }

    ret = platform_device_register(&smartstar_coul_device);
    return ret;
}

arch_initcall(smartstar_coul_dev_init);

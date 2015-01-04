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
#include <linux/vibrator/k3_vibrator.h>
#include <mach/platform.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>

static struct k3_vibrator_platform_data hi6401_vibrator = {
        .low_freq  = PERIOD,
        .low_power = ISET_POWER,
        .mode  = SET_MODE,
        .high_freq = PERIOD_QUICK,
        .high_power = ISET_POWERSTRONG,
};

static struct resource hi6401_vibrator_resources = {
        .start          = REG_BASE_PMUSPI,
        .end            = REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
        .flags          = IORESOURCE_MEM,

};
static struct platform_device hi6401_vibrator_device = {
        .name           = K3_VIBRATOR,
        .id                     = 0,
        .dev = {
                .platform_data = &hi6401_vibrator,
                .init_name = "hkvibrator",
        },
        .num_resources          = 1,
        .resource       =  &hi6401_vibrator_resources,
};

int __init vibrator_device_init(void)
{
	int ret = 0;
	ret = platform_device_register(&hi6401_vibrator_device);
	return ret;
};

arch_initcall(vibrator_device_init);

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
#include <mach/platform.h>
#include <dev_bq_bci.h>
#include <hsad/config_mgr.h>


static int hi6421_batt_table[] = {
    /* adc code for temperature in degree C */
    929, 925, /* -2 ,-1 */
    920, 917, 912, 908, 904, 899, 895, 890, 885, 880, /* 00 - 09 */
    875, 869, 864, 858, 853, 847, 841, 835, 829, 823, /* 10 - 19 */
    816, 810, 804, 797, 790, 783, 776, 769, 762, 755, /* 20 - 29 */
    748, 740, 732, 725, 718, 710, 703, 695, 687, 679, /* 30 - 39 */
    671, 663, 655, 647, 639, 631, 623, 615, 607, 599, /* 40 - 49 */
    591, 583, 575, 567, 559, 551, 543, 535, 527, 519, /* 50 - 59 */
    511, 504, 496 /* 60 - 62 */
};


static struct bq_bci_platform_data hi6421_bci_data = {
    .termination_currentmA = 100,
    .monitoring_interval   = 10,
    .max_charger_currentmA = 1200,
    .max_charger_voltagemV = 4200,
    .max_bat_voltagemV     = 4200,
    .low_bat_voltagemV     = 3300,
    .battery_tmp_tbl       = hi6421_batt_table,
    .tblsize     = ARRAY_SIZE(hi6421_batt_table),
};

static struct platform_device hisik3_battery_monitor = {
	.name	= "bq_bci_battery",
	.id	= 1,
	.dev = {
		.platform_data	= &hi6421_bci_data,
	},
};

static int __init power_dev_init(void)
{
    int ret = 0;
    int enable = 0;

    ret = platform_device_register(&hisik3_battery_monitor);
    return ret;
}

arch_initcall(power_dev_init);


/*
 *
 * Device check define and register
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

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
static struct platform_device huawei_device_detect = {
    .name = "hw-dev-detect",
    .id     = -1,
    .dev    = {
    .init_name = "hw-dev-detect",
    },
  //  .num_resources = ARRAY_SIZE(k3_gps_bcm_resources),
  //  .resource = k3_gps_bcm_resources,
};

static int __init huawei_device_detect_init(void)
{
    return platform_device_register(&huawei_device_detect);
}


device_initcall(huawei_device_detect_init);
#endif

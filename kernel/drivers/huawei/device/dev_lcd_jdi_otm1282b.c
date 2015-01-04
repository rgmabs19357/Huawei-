/*
 *
 * Copyright (C) 2013 Google, Inc.
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

#include <mach/platform.h>
#include <mach/gpio.h>
#include <linux/platform_device.h>
#include <hsad/config_mgr.h>


#ifdef CONFIG_MACH_HI6620OEM
#define GPIO_LCD_RESET  (GPIO_4_6)
#define GPIO_LCD_POWER  (GPIO_13_3)
#else
#define GPIO_LCD_RESET  (GPIO_9_7)
#define GPIO_LCD_POWER  (GPIO_0_4)
#define GPIO_LCD_ID0	(GPIO_9_5)
#define GPIO_LCD_ID1	(GPIO_9_6)
#endif

#define GPIO_LCD_POWER_NAME "gpio_lcd_power"
#define GPIO_LCD_RESET_NAME "gpio_lcd_reset"

#define PLATFORM_DEVICE_LCD_NAME "mipi_jdi_OTM1282B"
#define REGULATOR_DEV_LCD_NAME  "k3_dev_lcd"
#define LCD_NAME_MAX_LEN         (60)

static struct resource k3_lcd_resources[] = {
	[0] = {
		.name = GPIO_LCD_RESET_NAME,
		.start = GPIO_LCD_RESET,
		.end = GPIO_LCD_RESET,
		.flags = IORESOURCE_IO,
	},
	[1] = {
		.name = GPIO_LCD_POWER_NAME,
		.start = GPIO_LCD_POWER,
		.end = GPIO_LCD_POWER,
		.flags = IORESOURCE_IO,
	},
};

static struct platform_device k3_lcd_device = {
	.name = PLATFORM_DEVICE_LCD_NAME,
	.id	= 1,
	.dev = {
		.init_name = REGULATOR_DEV_LCD_NAME,
	},
	.num_resources = ARRAY_SIZE(k3_lcd_resources),
	.resource = k3_lcd_resources,
};

static bool is_jdi_otm1282b() 
{
	char lcd_chip_name[LCD_NAME_MAX_LEN + 1];
	bool ret = 0;

	ret = get_hw_config_string("lcd/devices", lcd_chip_name, LCD_NAME_MAX_LEN, NULL);
	if(ret) {
        if(!strcmp(lcd_chip_name, "mipi_jdi_OTM1282B")) {
			return true;
        } else {
			return false;
		}
	} else {
		return false;
	}
}

int __init lcd_device_jdi_otm1282b_init(void)
{
	int ret = 0;

	if(is_jdi_otm1282b()) {
		ret = platform_device_register(&k3_lcd_device);		
	}

	return ret;
};

device_initcall(lcd_device_jdi_otm1282b_init);


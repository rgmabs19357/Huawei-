/* Copyright (C) 2013 Huawei
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


#define GPIO_LCD_RESET_NAME     "gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME       "gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME       "gpio_lcd_id1"
#define REGULATOR_DEV_LCD_NAME  "k3_dev_lcd"
#define GPIO_LCD_ENP_NAME       "gpio_lcd_enp"
#define GPIO_LCD_ENN_NAME       "gpio_lcd_enn"
#define GPIO_LCD_PWM_NAME       "gpio_lcd_pwm_en"


#define GPIO_LCD_RESET    (GPIO_4_6)
#define GPIO_LCD_ENN      (GPIO_13_3)
#define GPIO_LCD_ENP      (GPIO_6_6)
#define GPIO_LCD_PWM_EN   (GPIO_8_0)
#define GPIO_LCD_ID0	  (GPIO_4_4)
#define GPIO_LCD_ID1	  (GPIO_4_5)


#define LCD_NAME_MAX_LEN           (60)
#define LCD_PANEL_CONFIG           "lcd/devices"
#define PLATFORM_DEVICE_LCD_NAME   "mipi_jdi_OTM1902B"


static struct resource k3_lcd_resources[] = {
	[0] = {
		.name = GPIO_LCD_RESET_NAME,
		.start = GPIO_LCD_RESET,
		.end = GPIO_LCD_RESET,
		.flags = IORESOURCE_IO,
	},
	[1] = {
		.name = GPIO_LCD_ENP_NAME,
		.start = GPIO_LCD_ENP,
		.end = GPIO_LCD_ENP,
		.flags = IORESOURCE_IO,
	},
	[2] = {
		.name = GPIO_LCD_ENN_NAME,
		.start = GPIO_LCD_ENN,
		.end = GPIO_LCD_ENN,
		.flags = IORESOURCE_IO,
	},
	[3] = {
		.name = GPIO_LCD_PWM_NAME,
		.start = GPIO_LCD_PWM_EN,
		.end = GPIO_LCD_PWM_EN,
		.flags = IORESOURCE_IO,
	},
	[4] = {
		.name = GPIO_LCD_ID0_NAME,
		.start = GPIO_LCD_ID0,
		.end = GPIO_LCD_ID0,
		.flags = IORESOURCE_IO,
	},
	[5] = {
		.name = GPIO_LCD_ID1_NAME,
		.start = GPIO_LCD_ID1,
		.end = GPIO_LCD_ID1,
		.flags = IORESOURCE_IO,
	},
};

static struct platform_device k3_lcd_device = {
	.name = PLATFORM_DEVICE_LCD_NAME,
	.id = 1,
	.dev = {
		.init_name = REGULATOR_DEV_LCD_NAME,
	},
	.num_resources = ARRAY_SIZE(k3_lcd_resources),
	.resource = k3_lcd_resources,
};


static bool is_jdi_otm1902b(void)
{
	char lcd_chip_name[LCD_NAME_MAX_LEN+1];
	bool ret = 0;

	memset(lcd_chip_name, 0, LCD_NAME_MAX_LEN+1);
	ret = get_hw_config_string(LCD_PANEL_CONFIG, lcd_chip_name, LCD_NAME_MAX_LEN, NULL);

	if (ret) {
		if (!strcmp(lcd_chip_name, PLATFORM_DEVICE_LCD_NAME)) {
			ret = true;
		} else {
			ret = false;
		}
	} else {
		ret = false;
	}

	return ret;
}


static int __init lcd_device_jdi_otm1902b_init(void)
{
	int ret = 0;

	if (is_jdi_otm1902b()) {
		ret = platform_device_register(&k3_lcd_device);
	}

	return ret;
};


arch_initcall(lcd_device_jdi_otm1902b_init);



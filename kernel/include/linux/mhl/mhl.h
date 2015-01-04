/*
 * SiIxxxx <Firmware or Driver>
 *
 * Copyright (C) 2011 Silicon Image Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed .as is. WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the
 * GNU General Public License for more details.
*/

#ifndef __MHL_H__
#define __MHL_H__
#include <mach/gpio.h>

/* Added for HI6620 MHL begin */
#define     MHL_IRQ_NAME              "irq_mhl"
#define     MHL_REG_NAME              "reg_mhl"
#define     MHL_DEVICE_NAME           "k3_hdmi"
/* Added for HI6620 MHL end */



/* The section for sii9244 */
#define		MHL_SII9244_PAGE0_ADDR			(0x3B)
#define		MHL_SII9244_PAGE1_ADDR			(0x3F)
#define		MHL_SII9244_PAGE2_ADDR			(0x4B)
#define		MHL_SII9244_CBUS_ADDR			(0x66)

#define		MHL_GPIO_WAKE_UP			(GPIO_9_7)
#define		MHL_GPIO_INT					(GPIO_10_0)
#define		MHL_GPIO_RESET				(GPIO_10_1)
#define     	MHL_NEW_BROAD

#ifdef CONFIG_MHL_USB_SHARE
#define		MHL_GPIO_SWITCH_1			(GPIO_18_0)
#define		MHL_GPIO_SWITCH_2			(GPIO_21_6)
#endif

#define		MHL_GPIO_DCDC_MODE			(GPIO_15_4)

struct mhl_platform_data {
	int gpio_reset;
	int gpio_wake_up;
	int gpio_int;
#ifdef CONFIG_MHL_USB_SHARE
	int gpio_switch_1;
	int gpio_switch_2;
#endif
	int gpio_dcdc;
};

#endif
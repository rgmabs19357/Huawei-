/*
 * arch/arm/mach-k3v2/board-tc45msu3.c
 *
 * Copyright (C) 2010 Google, Inc.
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
#ifndef _DEV_LCD_H_
#define _DEV_LCD_H_

#define GPIO_LCD_POWER_NAME "gpio_lcd_power"
#define GPIO_LCD_RESET_NAME "gpio_lcd_reset"
#define GPIO_TP_RESET_NAME "rmi4_reset"
#define GPIO_LCD_ID0_NAME "gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME "gpio_lcd_id1"
#define GPIO_PWM0_NAME   "gpio_pwm0"
#define GPIO_PWM1_NAME   "gpio_pwm1"
#define REG_BASE_PWM0_NAME  "reg_base_pwm0"
#define REGULATOR_DEV_LCD_NAME  "k3_dev_lcd"
#define REGULATOR_DEV_EDC_NAME  "k3_dev_edc"
#endif

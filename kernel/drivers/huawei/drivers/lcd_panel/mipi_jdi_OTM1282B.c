/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *	 * Redistributions of source code must retain the above copyright
 *	   notice, this list of conditions and the following disclaimer.
 *	 * Redistributions in binary form must reproduce the above
 *	   copyright notice, this list of conditions and the following
 *	   disclaimer in the documentation and/or other materials provided
 *	   with the distribution.
 *	 * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *	   contributors may be used to endorse or promote products derived
 *	   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/pwm.h>
#include <mach/platform.h>
#include <mach/gpio.h>
#include <mach/boardid.h>

#include "k3_fb.h"
#include "k3_fb_def.h"
#include "mipi_dsi.h"
#include "mipi_reg.h"
#include <linux/lcd_tuning.h>
#include <../touchscreen/ts/huawei_touchscreen_chips.h>
#include "drv_regulator_user.h"

#define LCD_IOMUX "block_lcd"

#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_POWER_NAME	"gpio_lcd_power"

struct jdi_otm1282b_panel_data{
	struct iomux_block *lcd_gpio_block;
	struct block_config *lcd_gpio_block_config;
	int lcd_gpio_reset;
	int lcd_gpio_power;
};

static struct jdi_otm1282b_panel_data *g_panel_platform_data;
static volatile bool g_display_on;
static volatile bool backlight_log_once = true;
extern u32 frame_count;
/*******************************************************************************
** DSI Command Sequence
*/

static char bl_level[] = {
	0x51,
	0x00,
};

static char bl_enable[] = {
	0x53,
	0x24,
};

static char te_enable[] = {
	0x35,
	0x00,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};

/*Power Off*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static char orise_shift_0x00[] = {
	0x00,
	0x00,
};

static char orise_sheift_0x80[] = {
	0x00,
	0x80, 
};

/*Enable Orise Mode*/
static char enable_orise_command1[] = {
	0xFF,
	0x12, 0x82, 0x01,
};

static char enable_orise_command2[] = {
	0xFF,
	0x12, 0x82,
};

/*Disable Per-charge*/
static char disable_per_charge [] = {
	0xA5,
	0x0C, 0x04, 0x01, 
};

/* Set VGL*/
static char set_vgl1[] = {
	0x00,
	0xB0, 
};

static char set_vgl2[] = {
	0xC5,
	0x92, 0xD6, 0xAF, 0xAF, 0x82,
	0x88, 0x44, 0x44, 0x40, 0x88,
};

/* Delay TE*/
static char Delay_TE[] = {
	0x44,
	0x01, 0x40,
};

static char all_pixels_off[] = {
	0x22,
};

static char normal_display_on[] = {
	0x13,
};

/*CABC Base Sequence*/
static char enable_orise_mode5[] = {
	0x00,
	0x00,
};

static char enable_orise_mode6[] = {
	0x00,
	0x90,
};

static char CABC_enable_setting[] = {
	0x59,
	0x03,
};

static char CABC_func_setting[] = {
	0xca,
	0xda, 0xff, 0xa6, 0xff, 0x80,
	0xff, 0x05, 0x03, 0x05, 0x03,
	0x05, 0x03,
};

static char CABC_disable_curve[] = {
	0xc6,
	0x00,
};

static char CABC_disable_setting[] = {
	0x59,
	0x00,
};

static char CABC_UI_MODE[] = {
	0x55,
	0x91,
};

static char CABC_UI_curve[] = {
	0xc6,
	0x10,
};

static char CABC_UI_curve_setting[] = {
	0xc7,
	0x90, 0x89, 0x89, 0x88, 0x88,
	0x98, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x87, 0x88, 0x87,
	0x88, 0x87, 0x78,
};

static char CABC_STILL_curve[] = {
	0xc6,
	0x11,
};

static char CABC_STILL_curve_setting[] = {
	0xc7,
	0xa0, 0x9a, 0x99, 0x99, 0x89,
	0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x78, 0x87, 0x78, 0x77,
	0x77, 0x77, 0x77,
};

static char CABC_VID_MODE[] = {
	0x55,
	0x93,
};

static char CABC_VID_curve[] = {
	0xc6,
	0x12,
};

static char CABC_VID_curve_setting[] = {
	0xc7,
	0xb0, 0xab, 0xaa, 0x99, 0x99,
	0x99, 0x89, 0x88, 0x88, 0x88,
	0x77, 0x77, 0x77, 0x77, 0x77,
	0x77, 0x77, 0x56,
};

/*CE Base Sequence*/
static char ce_medium_on[] = {
	0x55,
	0x90,
};

static char ce_init_param1[] = {
    0xD4,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x00,0x40,
	0x00,0x40,0x00,0x41,0x00,0x40,0x00,0x41,0x00,0x40,
	0x00,0x42,0x00,0x40,0x00,0x43,0x00,0x40,0x00,0x44,
	0x00,0x40,0x00,0x45,0x00,0x40,0x00,0x46,0x00,0x40,
	0x00,0x47,0x00,0x40,0x00,0x47,0x00,0x40,0x00,0x48,
	0x00,0x40,0x00,0x49,0x00,0x40,0x00,0x4a,0x00,0x40,
	0x00,0x4b,0x00,0x40,0x00,0x4c,0x00,0x40,0x00,0x4d,
	0x00,0x40,0x00,0x4e,0x00,0x40,0x00,0x4f,0x00,0x40,
	0x00,0x50,0x00,0x40,0x00,0x52,0x00,0x40,0x00,0x53,
	0x00,0x40,0x00,0x54,0x00,0x40,0x00,0x55,0x00,0x40,
};

static char ce_init_param2[] = {
    0xD4,
	0x00,0x57,0x00,0x40,0x00,0x57,0x00,0x40,0x00,0x58,
	0x00,0x40,0x00,0x58,0x00,0x40,0x00,0x59,0x00,0x40,
	0x00,0x5a,0x00,0x40,0x00,0x5a,0x00,0x40,0x00,0x5b,
	0x00,0x40,0x00,0x5c,0x00,0x40,0x00,0x5c,0x00,0x40,
	0x00,0x5d,0x00,0x40,0x00,0x5e,0x00,0x40,0x00,0x5e,
	0x00,0x40,0x00,0x5f,0x00,0x40,0x00,0x60,0x00,0x40,
	0x00,0x60,0x00,0x40,0x00,0x5f,0x00,0x40,0x00,0x5f,
	0x00,0x40,0x00,0x5e,0x00,0x40,0x00,0x5d,0x00,0x40,
	0x00,0x5d,0x00,0x40,0x00,0x5c,0x00,0x40,0x00,0x5b,
	0x00,0x40,0x00,0x5b,0x00,0x40,0x00,0x5a,0x00,0x40,
	0x00,0x59,0x00,0x40,0x00,0x59,0x00,0x40,0x00,0x58,
	0x00,0x40,0x00,0x58,0x00,0x40,0x00,0x57,0x00,0x40,
	0x00,0x56,0x00,0x40,0x00,0x55,0x00,0x40,0x00,0x54,
	0x00,0x40,0x00,0x54,0x00,0x40,0x00,0x53,0x00,0x40,
	0x00,0x52,0x00,0x40,0x00,0x51,0x00,0x40,0x00,0x50,
	0x00,0x40,0x00,0x4f,0x00,0x40,0x00,0x4f,0x00,0x40,
	0x00,0x4e,0x00,0x40,0x00,0x4d,0x00,0x40,0x00,0x4c,
	0x00,0x40,0x00,0x4b,0x00,0x40,0x00,0x4a,0x00,0x40,
};

static char ce_init_param3[] = {
    0xD4,
	0x00,0x4a,0x00,0x40,0x00,0x4b,0x00,0x40,0x00,0x4c,
	0x00,0x40,0x00,0x4c,0x00,0x40,0x00,0x4d,0x00,0x40,
	0x00,0x4e,0x00,0x40,0x00,0x4f,0x00,0x40,0x00,0x50,
	0x00,0x40,0x00,0x51,0x00,0x40,0x00,0x51,0x00,0x40,
	0x00,0x52,0x00,0x40,0x00,0x53,0x00,0x40,0x00,0x54,
	0x00,0x40,0x00,0x55,0x00,0x40,0x00,0x56,0x00,0x40,
	0x00,0x57,0x00,0x40,0x00,0x57,0x00,0x40,0x00,0x58,
	0x00,0x40,0x00,0x58,0x00,0x40,0x00,0x59,0x00,0x40,
	0x00,0x5a,0x00,0x40,0x00,0x5a,0x00,0x40,0x00,0x5b,
	0x00,0x40,0x00,0x5c,0x00,0x40,0x00,0x5c,0x00,0x40,
	0x00,0x5d,0x00,0x40,0x00,0x5e,0x00,0x40,0x00,0x5e,
	0x00,0x40,0x00,0x5f,0x00,0x40,0x00,0x60,0x00,0x40,
	0x00,0x60,0x00,0x40,0x00,0x5f,0x00,0x40,0x00,0x5f,
	0x00,0x40,0x00,0x5e,0x00,0x40,0x00,0x5d,0x00,0x40,
	0x00,0x5d,0x00,0x40,0x00,0x5c,0x00,0x40,0x00,0x5b,
	0x00,0x40,0x00,0x5b,0x00,0x40,0x00,0x5a,0x00,0x40,
	0x00,0x59,0x00,0x40,0x00,0x59,0x00,0x40,0x00,0x58,
	0x00,0x40,0x00,0x58,0x00,0x40,0x00,0x57,0x00,0x40,
};

static char ce_init_param4[] = {
    0xD4,
	0x00,0x56,0x00,0x40,0x00,0x55,0x00,0x40,0x00,0x54,
	0x00,0x40,0x00,0x54,0x00,0x40,0x00,0x53,0x00,0x40,
	0x00,0x52,0x00,0x40,0x00,0x51,0x00,0x40,0x00,0x50,
	0x00,0x40,0x00,0x4f,0x00,0x40,0x00,0x4f,0x00,0x40,
	0x00,0x4e,0x00,0x40,0x00,0x4d,0x00,0x40,0x00,0x4c,
	0x00,0x40,0x00,0x4b,0x00,0x40,0x00,0x4a,0x00,0x40,
	0x00,0x4a,0x00,0x40,0x00,0x4a,0x00,0x40,0x00,0x4b,
	0x00,0x40,0x00,0x4c,0x00,0x40,0x00,0x4c,0x00,0x40,
	0x00,0x4d,0x00,0x40,0x00,0x4e,0x00,0x40,0x00,0x4e,
	0x00,0x40,0x00,0x4f,0x00,0x40,0x00,0x50,0x00,0x40,
	0x00,0x50,0x00,0x40,0x00,0x51,0x00,0x40,0x00,0x51,
	0x00,0x40,0x00,0x52,0x00,0x40,0x00,0x53,0x00,0x40,
	0x00,0x53,0x00,0x40,0x00,0x52,0x00,0x40,0x00,0x50,
	0x00,0x40,0x00,0x4f,0x00,0x40,0x00,0x4e,0x00,0x40,
	0x00,0x4c,0x00,0x40,0x00,0x4b,0x00,0x40,0x00,0x4a,
	0x00,0x40,0x00,0x49,0x00,0x40,0x00,0x47,0x00,0x40,
	0x00,0x46,0x00,0x40,0x00,0x45,0x00,0x40,0x00,0x44,
	0x00,0x40,0x00,0x42,0x00,0x40,0x00,0x41,0x00,0x40,
};

static char ce_init_param5[] = {
    0xD5,
	0x00,0x55,0x00,0x4b,0x00,0x54,0x00,0x4a,0x00,0x52,
	0x00,0x4a,0x00,0x51,0x00,0x4a,0x00,0x4f,0x00,0x49,
	0x00,0x4e,0x00,0x49,0x00,0x4c,0x00,0x49,0x00,0x4b,
	0x00,0x49,0x00,0x4a,0x00,0x48,0x00,0x48,0x00,0x48,
	0x00,0x47,0x00,0x48,0x00,0x45,0x00,0x47,0x00,0x44,
	0x00,0x47,0x00,0x42,0x00,0x47,0x00,0x41,0x00,0x47,
	0x00,0x40,0x00,0x46,0x00,0x40,0x00,0x46,0x00,0x40,
	0x00,0x46,0x00,0x40,0x00,0x46,0x00,0x40,0x00,0x46,
	0x00,0x40,0x00,0x46,0x00,0x40,0x00,0x46,0x00,0x40,
	0x00,0x45,0x00,0x40,0x00,0x45,0x00,0x41,0x00,0x45,
	0x00,0x42,0x00,0x45,0x00,0x42,0x00,0x45,0x00,0x43,
	0x00,0x45,0x00,0x43,0x00,0x45,0x00,0x44,0x00,0x44,
	0x00,0x44,0x00,0x44,0x00,0x45,0x00,0x45,0x00,0x46,
	0x00,0x45,0x00,0x46,0x00,0x45,0x00,0x47,0x00,0x45,
	0x00,0x47,0x00,0x45,0x00,0x48,0x00,0x46,0x00,0x48,
	0x00,0x46,0x00,0x49,0x00,0x46,0x00,0x4a,0x00,0x46,
	0x00,0x4b,0x00,0x46,0x00,0x4c,0x00,0x47,0x00,0x4d,
	0x00,0x47,0x00,0x4d,0x00,0x47,0x00,0x4e,0x00,0x47,
};

static char ce_init_param6[] = {
    0xD5,
	0x00,0x4f,0x00,0x48,0x00,0x4f,0x00,0x48,0x00,0x50,
	0x00,0x48,0x00,0x50,0x00,0x48,0x00,0x51,0x00,0x48,
	0x00,0x51,0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x52,
	0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x53,0x00,0x49,
	0x00,0x53,0x00,0x4a,0x00,0x54,0x00,0x4a,0x00,0x54,
	0x00,0x4a,0x00,0x55,0x00,0x4a,0x00,0x55,0x00,0x4b,
	0x00,0x55,0x00,0x4b,0x00,0x55,0x00,0x4a,0x00,0x54,
	0x00,0x4a,0x00,0x54,0x00,0x4a,0x00,0x54,0x00,0x4a,
	0x00,0x53,0x00,0x4a,0x00,0x53,0x00,0x49,0x00,0x52,
	0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x51,0x00,0x49,
	0x00,0x51,0x00,0x48,0x00,0x51,0x00,0x48,0x00,0x50,
	0x00,0x48,0x00,0x50,0x00,0x48,0x00,0x4f,0x00,0x48,
	0x00,0x4f,0x00,0x47,0x00,0x4e,0x00,0x47,0x00,0x4e,
	0x00,0x47,0x00,0x4d,0x00,0x47,0x00,0x4d,0x00,0x46,
	0x00,0x4c,0x00,0x46,0x00,0x4b,0x00,0x46,0x00,0x4b,
	0x00,0x45,0x00,0x4a,0x00,0x45,0x00,0x4a,0x00,0x45,
	0x00,0x49,0x00,0x45,0x00,0x49,0x00,0x44,0x00,0x48,
	0x00,0x44,0x00,0x47,0x00,0x44,0x00,0x47,0x00,0x43,
};

static char ce_init_param7[] = {
    0xD5,
	0x00,0x47,0x00,0x43,0x00,0x47,0x00,0x44,0x00,0x48,
	0x00,0x44,0x00,0x48,0x00,0x44,0x00,0x49,0x00,0x44,
	0x00,0x49,0x00,0x45,0x00,0x4a,0x00,0x45,0x00,0x4b,
	0x00,0x45,0x00,0x4b,0x00,0x46,0x00,0x4c,0x00,0x46,
	0x00,0x4c,0x00,0x46,0x00,0x4d,0x00,0x46,0x00,0x4d,
	0x00,0x47,0x00,0x4e,0x00,0x47,0x00,0x4f,0x00,0x47,
	0x00,0x4f,0x00,0x48,0x00,0x4f,0x00,0x48,0x00,0x50,
	0x00,0x48,0x00,0x50,0x00,0x48,0x00,0x51,0x00,0x48,
	0x00,0x51,0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x52,
	0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x53,0x00,0x49,
	0x00,0x53,0x00,0x4a,0x00,0x54,0x00,0x4a,0x00,0x54,
	0x00,0x4a,0x00,0x55,0x00,0x4a,0x00,0x55,0x00,0x4b,
	0x00,0x55,0x00,0x4b,0x00,0x55,0x00,0x4a,0x00,0x54,
	0x00,0x4a,0x00,0x54,0x00,0x4a,0x00,0x54,0x00,0x4a,
	0x00,0x53,0x00,0x4a,0x00,0x53,0x00,0x49,0x00,0x52,
	0x00,0x49,0x00,0x52,0x00,0x49,0x00,0x51,0x00,0x49,
	0x00,0x51,0x00,0x48,0x00,0x51,0x00,0x48,0x00,0x50,
	0x00,0x48,0x00,0x50,0x00,0x48,0x00,0x4f,0x00,0x48,
};

static char ce_init_param8[] = {
    0xD5,
	0x00,0x4f,0x00,0x47,0x00,0x4e,0x00,0x47,0x00,0x4e,
	0x00,0x47,0x00,0x4d,0x00,0x47,0x00,0x4d,0x00,0x46,
	0x00,0x4c,0x00,0x46,0x00,0x4b,0x00,0x46,0x00,0x4b,
	0x00,0x45,0x00,0x4a,0x00,0x45,0x00,0x4a,0x00,0x45,
	0x00,0x49,0x00,0x45,0x00,0x49,0x00,0x44,0x00,0x48,
	0x00,0x44,0x00,0x47,0x00,0x44,0x00,0x47,0x00,0x43,
	0x00,0x47,0x00,0x43,0x00,0x47,0x00,0x43,0x00,0x47,
	0x00,0x44,0x00,0x48,0x00,0x44,0x00,0x48,0x00,0x44,
	0x00,0x49,0x00,0x44,0x00,0x49,0x00,0x45,0x00,0x49,
	0x00,0x45,0x00,0x4a,0x00,0x45,0x00,0x4a,0x00,0x45,
	0x00,0x4b,0x00,0x45,0x00,0x4b,0x00,0x46,0x00,0x4c,
	0x00,0x46,0x00,0x4c,0x00,0x46,0x00,0x4c,0x00,0x46,
	0x00,0x4d,0x00,0x46,0x00,0x4e,0x00,0x47,0x00,0x4e,
	0x00,0x47,0x00,0x4f,0x00,0x47,0x00,0x4f,0x00,0x48,
	0x00,0x50,0x00,0x48,0x00,0x50,0x00,0x48,0x00,0x51,
	0x00,0x48,0x00,0x51,0x00,0x49,0x00,0x52,0x00,0x49,
	0x00,0x53,0x00,0x49,0x00,0x53,0x00,0x4a,0x00,0x54,
	0x00,0x4a,0x00,0x54,0x00,0x4a,0x00,0x55,0x00,0x4a,
};

static struct dsi_cmd_desc jdi_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_level), bl_level},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(all_pixels_off), all_pixels_off},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_command1), enable_orise_command1},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(orise_sheift_0x80), orise_sheift_0x80},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_command2), enable_orise_command2},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(orise_shift_0x00), orise_shift_0x00},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param1), ce_init_param1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param2), ce_init_param2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param3), ce_init_param3},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param4), ce_init_param4},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(orise_shift_0x00), orise_shift_0x00},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param5), ce_init_param5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param6), ce_init_param6},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param7), ce_init_param7},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param8), ce_init_param8},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(orise_shift_0x00), orise_shift_0x00},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(ce_medium_on), ce_medium_on},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(orise_sheift_0x80), orise_sheift_0x80},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(disable_per_charge), disable_per_charge},	
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl1), set_vgl1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl2), set_vgl2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(Delay_TE), Delay_TE},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
};

static struct dsi_cmd_desc jdi_display_off_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_level), bl_level},
	{DTYPE_DCS_WRITE, 0, 30, WAIT_TYPE_US,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep},
};

static struct dsi_cmd_desc jdi_cabc_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_enable_setting), CABC_enable_setting},	
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode6), enable_orise_mode6},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CABC_func_setting), CABC_func_setting},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_UI_curve), CABC_UI_curve},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},		
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CABC_UI_curve_setting), CABC_UI_curve_setting},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_STILL_curve), CABC_STILL_curve},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},		
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CABC_STILL_curve_setting), CABC_STILL_curve_setting},	
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_VID_curve), CABC_VID_curve},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},		
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CABC_VID_curve_setting), CABC_VID_curve_setting},	
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_disable_curve), CABC_disable_curve},	
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_disable_setting), CABC_disable_setting},		
};

static struct dsi_cmd_desc jdi_cabc_ui_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_UI_MODE), CABC_UI_MODE},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_UI_curve), CABC_UI_curve},
};

static struct dsi_cmd_desc jdi_cabc_vid_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_VID_MODE), CABC_VID_MODE},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_VID_curve), CABC_VID_curve},		
};



/*******************************************************************************
** LCD VCC
*/

/*******************************************************************************
** LCD IOMUX
*/
static int set_iomux_init(char *block_name, struct iomux_block **gpio_block, struct block_config **gpio_block_config)
{
    int ret = 0;

    BUG_ON(block_name == NULL);
    BUG_ON(gpio_block == NULL);
    BUG_ON(gpio_block_config == NULL);

    /* get gpio block*/
    *gpio_block = iomux_get_block(block_name);
    if (IS_ERR(*gpio_block)) {
        printk("%s: failed to get gpio block,iomux_get_block failed\n", __func__);
        ret = -EINVAL;
        return ret;
    }

    /* get gpio block config*/
    *gpio_block_config = iomux_get_blockconfig(block_name);
    if (IS_ERR(*gpio_block_config)) {
        printk("%s: failed to get gpio block config\n", __func__);
        ret = -EINVAL;
        *gpio_block = NULL;
        return ret;
    }

    return 0;
}

static int set_iomux_normal(struct iomux_block *gpio_block, struct block_config *gpio_block_config)
{
    int ret;

    BUG_ON(gpio_block_config == NULL);
    BUG_ON(gpio_block == NULL);

    ret = blockmux_set(gpio_block, gpio_block_config, NORMAL);
    if (ret < 0) {
        printk(KERN_ERR "%s: failed to config gpio\n", __func__);
        return ret;
    }

    return 0;
}

static int set_iomux_lowpower(struct iomux_block *gpio_block, struct block_config *gpio_block_config)
{
    int ret;

    BUG_ON(gpio_block_config == NULL);
    BUG_ON(gpio_block == NULL);

    ret = blockmux_set(gpio_block, gpio_block_config, LOWPOWER);
    if (ret < 0) {
        printk(KERN_ERR "%s: failed to config gpio\n", __func__);
        return ret;
    }

    return 0;
}

static int lcd_set_iomux_init(void)
{
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

    return set_iomux_init(LCD_IOMUX, &panel_data_ptr->lcd_gpio_block, &panel_data_ptr->lcd_gpio_block_config);
}

static int lcd_set_iomux_normal(void)
{
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

    return set_iomux_normal(panel_data_ptr->lcd_gpio_block, panel_data_ptr->lcd_gpio_block_config);
}

static int lcd_set_iomux_lowpower(void)
{
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

    return set_iomux_lowpower(panel_data_ptr->lcd_gpio_block, panel_data_ptr->lcd_gpio_block_config);
}

/*******************************************************************************
** LCD GPIO
*/
static int get_one_gpio_resource(struct platform_device *pdev, char *name)
{
	struct resource *res =  NULL;
	int gpio = -1;
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, name);
	if (res == NULL) {
		k3fb_loge("failed to get gpio resource:%s!\n", name);
		return -1;
	}

	gpio = res->start;
	if (!gpio_is_valid(gpio)) {
		k3fb_loge("gpio %d for %s is invalid.", gpio, name);
		return -1;
	}

	return gpio;
}

static int lcd_get_resource(struct platform_device *pdev)
{
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;
	BUG_ON(pdev == NULL);

	panel_data_ptr->lcd_gpio_reset = get_one_gpio_resource(pdev, GPIO_LCD_RESET_NAME);
	panel_data_ptr->lcd_gpio_power = get_one_gpio_resource(pdev, GPIO_LCD_POWER_NAME);

	return 0;
}

static int lcd_gpio_request(void)
{
	int retval;
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

	retval = gpio_request(panel_data_ptr->lcd_gpio_reset, "lcd_gpio_reset");
	if (retval) {
		pr_err("%s: Failed to get reset gpio %d. Code: %d.\n",
			__func__, panel_data_ptr->lcd_gpio_reset, retval);
		return -1;
	}

	retval = gpio_request(panel_data_ptr->lcd_gpio_power, "lcd_gpio_power");
	if (retval) {
		pr_err("%s: Failed to get reset gpio %d. Code: %d.\n",
			__func__, panel_data_ptr->lcd_gpio_power, retval);
		return -1;
	}

	return 0;
}

static int lcd_gpio_free(void)
{
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

	if (gpio_is_valid(panel_data_ptr->lcd_gpio_reset)) {
		gpio_free(panel_data_ptr->lcd_gpio_reset);
	}

	if (gpio_is_valid(panel_data_ptr->lcd_gpio_power)) {
		gpio_free(panel_data_ptr->lcd_gpio_power);
	}

	return 0;
}

static void jdi_power_on(struct k3_panel_info *pinfo)
{
	int retval;
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

	retval = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
	if (retval < 0) {
		k3fb_loge("Failed to send TS_RESUME_DEVICE. Code: %d.\n", retval);
	}
	/*LCD GPIO*/
	lcd_set_iomux_normal();

	lcd_gpio_request();

	gpio_direction_output(panel_data_ptr->lcd_gpio_reset, 1);
	mdelay(10);
	gpio_direction_output(panel_data_ptr->lcd_gpio_power, 1);
	mdelay(10);
	gpio_direction_output(panel_data_ptr->lcd_gpio_reset, 0);
	mdelay(10);
	gpio_direction_output(panel_data_ptr->lcd_gpio_reset, 1);
	mdelay(10);
}

static void jdi_power_off(struct k3_panel_info *pinfo)
{
	int retval;
	struct jdi_otm1282b_panel_data *panel_data_ptr = g_panel_platform_data;

	gpio_direction_output(panel_data_ptr->lcd_gpio_reset, 0);
	mdelay(10);
	gpio_direction_output(panel_data_ptr->lcd_gpio_power, 0);
	mdelay(1);
	lcd_gpio_free();
#ifdef CONFIG_MACH_HI6620OEM
	lcd_set_iomux_lowpower();
#endif
	mdelay(1);

	retval = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
	if (retval < 0) {
		k3fb_loge("Failed to send TS_SUSPEND_DEVICE. Code: %d.\n", retval);
	}
}

static struct k3_fb_panel_data jdi_panel_data;

/******************************************************************************/
static struct lcd_tuning_dev *p_tuning_dev = NULL;
static int cabc_mode = 1; /* allow application to set cabc mode to ui mode */

static int jdi_set_gamma(struct lcd_tuning_dev *ltd, enum lcd_gamma gamma)
{
	int ret = 0;
	struct platform_device *pdev = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(ltd == NULL);
	pdev = (struct platform_device *)(ltd->data);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	edc_base = k3fd->edc_base;

	/* Fix me: Implement it */

	return ret;
}

static int jdi_set_cabc(struct lcd_tuning_dev *ltd, enum  tft_cabc cabc)
{
	int ret = 0;
	struct platform_device *pdev = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(ltd == NULL);
	pdev = (struct platform_device *)(ltd->data);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	edc_base = k3fd->edc_base;

	/* Fix me: Implement it */
	switch (cabc)
	{
		case CABC_UI:
			mipi_dsi_cmds_tx(jdi_cabc_ui_on_cmds, \
							ARRAY_SIZE(jdi_cabc_ui_on_cmds));
			break;
		case CABC_VID:
			mipi_dsi_cmds_tx(jdi_cabc_vid_on_cmds, \
							ARRAY_SIZE(jdi_cabc_vid_on_cmds));
			break;
		case CABC_OFF:
			break;
		default:
			ret = -1;
	}

	return ret;
}

static unsigned int g_csc_value[9];
static unsigned int g_is_csc_set;
static struct semaphore ct_sem;

static void jdi_store_ct_cscValue(unsigned int csc_value[])
{
    down(&ct_sem);
    g_csc_value [0] = csc_value[0];
    g_csc_value [1] = csc_value[1];
    g_csc_value [2] = csc_value[2];
    g_csc_value [3] = csc_value[3];
    g_csc_value [4] = csc_value[4];
    g_csc_value [5] = csc_value[5];
    g_csc_value [6] = csc_value[6];
    g_csc_value [7] = csc_value[7];
    g_csc_value [8] = csc_value[8];
    g_is_csc_set = 1;
    up(&ct_sem);

    return;
}

static int jdi_set_ct_cscValue(struct k3_fb_data_type *k3fd)
{
    u32 edc_base = 0;
    edc_base = k3fd->edc_base;
    down(&ct_sem);
    if (1 == g_is_csc_set && g_display_on) {
        set_reg(edc_base + 0x400, 0x1, 1, 27);
        set_reg(edc_base + 0x408, g_csc_value[0], 13, 0);
        set_reg(edc_base + 0x408, g_csc_value[1], 13, 16);
        set_reg(edc_base + 0x40C, g_csc_value[2], 13, 0);
        set_reg(edc_base + 0x40C, g_csc_value[3], 13, 16);
        set_reg(edc_base + 0x410, g_csc_value[4], 13, 0);
        set_reg(edc_base + 0x410, g_csc_value[5], 13, 16);
        set_reg(edc_base + 0x414, g_csc_value[6], 13, 0);
        set_reg(edc_base + 0x414, g_csc_value[7], 13, 16);
        set_reg(edc_base + 0x418, g_csc_value[8], 13, 0);
    }
    up(&ct_sem);

    return 0;
}

static int jdi_set_color_temperature(struct lcd_tuning_dev *ltd, unsigned int csc_value[])
{

    int flag = 0;
    struct platform_device *pdev;
    struct k3_fb_data_type *k3fd;

    if (ltd == NULL) {
        return -1;
    }
    pdev = (struct platform_device *)(ltd->data);
    k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);

    if (k3fd == NULL) {
        return -1;
    }

    jdi_store_ct_cscValue(csc_value);
    flag = jdi_set_ct_cscValue(k3fd);
    return flag;

}

static struct lcd_tuning_ops sp_tuning_ops = {
	.set_gamma = jdi_set_gamma,
	.set_cabc = jdi_set_cabc,
	.set_color_temperature = jdi_set_color_temperature,
};

static ssize_t jdi_lcd_info_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct k3_panel_info *pinfo = NULL;

	pinfo = jdi_panel_data.panel_info;
	sprintf(buf, "jdi_OTM1282B 4.7' CMD TFT %d x %d\n",
		pinfo->xres, pinfo->yres);
	ret = strlen(buf) + 1;

	return ret;
}

static ssize_t show_cabc_mode(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", cabc_mode);
}

static ssize_t store_cabc_mode(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	unsigned long val = 0;

	ret = strict_strtoul(buf, 0, &val);
	if (ret)
		return ret;

	if(val == 1) {
		/* allow application to set cabc mode to ui mode */
		cabc_mode =1;
		jdi_set_cabc(p_tuning_dev, CABC_UI);
	} else if (val == 2) {
		/* force cabc mode to video mode */
		cabc_mode =2;
		jdi_set_cabc(p_tuning_dev, CABC_VID);
	}

	return sprintf((char *)buf, "%d\n", cabc_mode);
}

static ssize_t jdi_frame_count_show(struct device *dev,
       struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%u\n", frame_count);
}

static DEVICE_ATTR(lcd_info, S_IRUGO, jdi_lcd_info_show, NULL);
static DEVICE_ATTR(cabc_mode, 0644, show_cabc_mode, store_cabc_mode);
static DEVICE_ATTR(frame_count, S_IRUGO, jdi_frame_count_show, NULL);

static struct attribute *jdi_attrs[] = {
	&dev_attr_lcd_info.attr,
	&dev_attr_cabc_mode.attr,
	&dev_attr_frame_count.attr,
	NULL,
};

static struct attribute_group jdi_attr_group = {
	.attrs = jdi_attrs,
};

static int jdi_sysfs_init(struct platform_device *pdev)
{
	int ret = 0;
	ret = sysfs_create_group(&pdev->dev.kobj, &jdi_attr_group);
	if (ret) {
		k3fb_loge("create sysfs file failed!\n");
		return ret;
	}
	return 0;
}

static void jdi_sysfs_deinit(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &jdi_attr_group);
}

#ifdef CONFIG_FB_CHECK_MIPI_TR
static int mipi_jdi_check_mipi_tr(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	int err = 0; //ok
	u32 read_value;
	int ret = 0;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	//read 0x0a
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0a << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x9c != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0a success:%d, 0x0a value = 0x%x\n", __func__, ret, read_value);
		goto jdi_check_mipi_tr_error;
	}

	//read 0x0b
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0b << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x00 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0b success:%d, 0x0b value = 0x%x\n", __func__, ret, read_value);
		goto jdi_check_mipi_tr_error;
	}

	//read 0x0c
	read_value = 0;
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0c << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x07 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0c success:%d, 0x0c value = 0x%x\n", __func__, ret, read_value);
		goto jdi_check_mipi_tr_error;
	}

	//read 0x0d
	read_value = 0;
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0d << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x00 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0d success:%d, 0x0d value = 0x%x\n", __func__, ret, read_value);
		goto jdi_check_mipi_tr_error;
	}

jdi_check_mipi_tr_error:
	return err;
}
#endif

#ifdef CONFIG_FB_SET_INVERSION
static char orise_shift_0xb3[] = {
	0x00,
	0xb3,
};

static char inversion_mode_1dot[] = {
	0xc0,
	0x22,
};

static char inversion_mode_column[] = {
	0xc0,
	0x00,
};

static struct dsi_cmd_desc  otm1282b_lcd_inversion_type_1dot[] = {
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(orise_shift_0xb3), orise_shift_0xb3},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(inversion_mode_1dot), inversion_mode_1dot},
};

static struct dsi_cmd_desc  otm1282b_lcd_inversion_type_column[] = {
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(orise_shift_0xb3), orise_shift_0xb3},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(inversion_mode_column), inversion_mode_column},
};

static int mipi_jdi_set_inversion_type(struct platform_device *pdev, unsigned int inversion_mode)
{
	int ret = 0;
	switch (inversion_mode) {
		case INVERSION_TYPE_1DOT:
			mipi_dsi_cmds_tx(otm1282b_lcd_inversion_type_1dot, \
				ARRAY_SIZE(otm1282b_lcd_inversion_type_1dot));
			printk("%s INVERSION_TYPE_1DOT\n", __func__);
			ret = 0;
			break;
		case INVERSION_TYPE_COLUMN:
			mipi_dsi_cmds_tx(otm1282b_lcd_inversion_type_column, \
				ARRAY_SIZE(otm1282b_lcd_inversion_type_column));
			printk("%s INVERSION_TYPE_COLUMN\n", __func__);
			ret = 0;
			break;
		default:
			printk("%s: change LCD inversion type, fail.\n", __func__);
			ret = -EINVAL;
			break;
	}

	return ret;
}
#endif

#ifdef CONFIG_FB_MIPI_DETECT
static int mipi_jdi_panel_mipi_detect(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 err_bit = 0;
	u32 err_num = 0;
	int ret = 0;
	int read_err_flag = 0;

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	outp32(k3fd->dsi_base + MIPIDSI_GEN_HDR_ADDR, (0x0E) << 8 | 0x06);
	ret = mipi_dsi_wait_and_read(k3fd, &err_bit, WAIT_TYPE_MS, 1);
	if (ret) {
		read_err_flag = 1;
		pr_info("%s read 0x0E failed\n", __func__);
	}

	outp32(k3fd->dsi_base + MIPIDSI_GEN_HDR_ADDR, (0x05) << 8 | 0x06);
	ret = mipi_dsi_wait_and_read(k3fd, &err_num, WAIT_TYPE_MS, 1);
	if (ret) {
		read_err_flag = 1;
		pr_info("%s read 0x05 failed\n", __func__);
	}

	if (read_err_flag)
		return -1;

	ret = ((err_bit&0xFF)<<8) | (err_num&0xFF) ;
	pr_info("%s ret_val:0x%x\n", __func__, ret);
	return ret;
}
#endif

static int mipi_jdi_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	u32 edc_base = 0;
	int retval = 0;

	BUG_ON(pdev == NULL);
	pr_info("%s enter succ!\n",__func__);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
    
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);
	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		if (!g_display_on) {
			jdi_power_on(pinfo);
		}
		pinfo->lcd_init_step = LCD_INIT_SEND_SEQUENCE;
  
	} else if (pinfo->lcd_init_step == LCD_INIT_SEND_SEQUENCE) {
		/* lcd display on sequence */
		if (!g_display_on) {
			mipi_dsi_cmds_tx(jdi_display_on_cmds, ARRAY_SIZE(jdi_display_on_cmds));
			mipi_dsi_cmds_tx(jdi_cabc_cmds, ARRAY_SIZE(jdi_cabc_cmds));
			mipi_dsi_cmds_tx(jdi_cabc_ui_on_cmds, ARRAY_SIZE(jdi_cabc_ui_on_cmds));
			g_display_on = true;
			backlight_log_once = true;
			jdi_set_ct_cscValue(k3fd);
			retval = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
			if (retval < 0) {
				k3fb_loge("Failed to send TS_AFTER_RESUME. Code: %d.\n", retval);
			}
		}
	} else {
		k3fb_loge("failed to init lcd!\n");
	}
    
	return 0;
}

static int mipi_jdi_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	u32 edc_base = 0;
	int retval = 0;
	BUG_ON(pdev == NULL);
	pr_info("%s enter succ!\n",__func__);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);

	retval = ts_power_control_notify(TS_BEFORE_SUSPEND, SHORT_SYNC_TIMEOUT);
	if (retval < 0) {
		k3fb_loge("Failed to send TS_BEFORE_SUSPEND. Code: %d.\n", retval);
	}

#ifdef CONFIG_DEBUG_FS
	if ((g_fb_lowpower_debug_flag & DEBUG_LCD_LOWPOWER_DISABLE) == DEBUG_LCD_LOWPOWER_DISABLE) {
		k3fb_logi(" lcd off was disable");
		return 0;
	}
#endif
	if (g_display_on) {
		g_display_on = false;
		mipi_dsi_cmds_tx(jdi_display_off_cmds, ARRAY_SIZE(jdi_display_off_cmds));

		jdi_power_off(pinfo);
	}
	return 0;
}

static int mipi_jdi_panel_remove(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	/*BUG_ON(k3fd == NULL);*/
	if (!k3fd) {
		return 0;
	}

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_CLK_PUT(&(k3fd->panel_info));
	}

	jdi_sysfs_deinit(pdev);
	if (NULL != g_panel_platform_data) {
		kfree(g_panel_platform_data);
	}

	return 0;
}

static int mipi_jdi_panel_set_backlight(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	u32 level = 0;

	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc jdi_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust},
		{DTYPE_DCS_WRITE1, 0, 0, WAIT_TYPE_US,
			sizeof(bl_enable), bl_enable},
	};

	struct dsi_cmd_desc jdi_normal_display_on[] = {
		{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_US,
			sizeof(normal_display_on), normal_display_on},
	};

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

	/*Our eyes are more sensitive to small brightness.
	So we adjust the brightness of lcd following iphone4 */
	level = k3fd->bl_level;

	if (level > 255)
		level = 255;

    //backlight may turn off when bl_level is below 6.
	if (level < 6 && level != 0)
	{
		level = 6;
	}

	bl_level_adjust[1] = level;

	mipi_dsi_cmds_tx(jdi_bl_level_adjust, \
		ARRAY_SIZE(jdi_bl_level_adjust));
	if (backlight_log_once) {
		backlight_log_once = false;
		mipi_dsi_cmds_tx(jdi_normal_display_on, \
			ARRAY_SIZE(jdi_normal_display_on));
		k3fb_loge("----k3fd->bl_level=%d,set backlight to level = %d\n",k3fd->bl_level, level);
	}
	return 0;
}

static int mipi_jdi_panel_set_fastboot(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
    
	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	lcd_set_iomux_normal();
	lcd_gpio_request();

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
		PWM_GPIO_REQUEST(&(k3fd->panel_info));
	}

	g_display_on = true;
	return 0;
}

static int mipi_jdi_panel_set_cabc(struct platform_device *pdev, int value)
{
	u32 edc_base = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

#if 0
	if (value) {
		outp32(edc_base + MIPIDSI_GEN_HDR_ADDR, 0x0dbb23);
	} else {
		outp32(edc_base + MIPIDSI_GEN_HDR_ADDR, 0x0cbb23);
	}
#endif

	return 0;
}

static int mipi_jdi_panel_check_esd(struct platform_device *pdev)
{
	u32 dsi_base = 0;
	u32 tmp = 0;
	u32 delay_count =0;
	bool is_timeout;
	u32 lcd_status = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	dsi_base = k3fd->dsi_base;

	/* read pwm */
	outp32(dsi_base + MIPIDSI_GEN_HDR_ADDR, 0x1 << 8 |0x37);
	outp32(dsi_base + MIPIDSI_GEN_HDR_ADDR, 0xAC << 8 |0x14);

	/* check command fifo empty */
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_CMD_PKT_STATUS_ADDR);
		if (((tmp & 0x00000001) == 0x00000001) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	}	
	
	/* check read command finish */
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_CMD_PKT_STATUS_ADDR);
		if (((tmp & 0x00000040) != 0x00000040) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	}	
	
	if (is_timeout == false) {
		lcd_status = inp32(k3fd->dsi_base + MIPIDSI_GEN_PLD_DATA_ADDR);
	}
	  
	return lcd_status;
}

static struct k3_panel_info jdi_panel_info = {0};
static struct k3_fb_panel_data jdi_panel_data = {
	.panel_info = &jdi_panel_info,
	.on = mipi_jdi_panel_on,
	.off = mipi_jdi_panel_off,
	.remove = mipi_jdi_panel_remove,
	.set_backlight = mipi_jdi_panel_set_backlight,
	.set_fastboot = mipi_jdi_panel_set_fastboot,
	.set_cabc = mipi_jdi_panel_set_cabc,
    .check_esd = mipi_jdi_panel_check_esd,
#ifdef CONFIG_FB_CHECK_MIPI_TR
	.check_mipi_tr = mipi_jdi_check_mipi_tr,
#endif
#ifdef CONFIG_FB_SET_INVERSION
	.set_inversion_type = mipi_jdi_set_inversion_type,
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	.mipi_detect = mipi_jdi_panel_mipi_detect,
#endif
};

static int __devinit jdi_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct platform_device *reg_pdev = NULL;
	struct lcd_properities lcd_props;

	pr_info("%s enter succ!\n",__func__);
	g_panel_platform_data = kzalloc(sizeof(struct jdi_otm1282b_panel_data), GFP_KERNEL);
	if (NULL == g_panel_platform_data) {
		k3fb_loge("alloc driver data error\n");
		return -ENOMEM;
	}
	
	g_display_on = false;
	pinfo = jdi_panel_data.panel_info;
	
	/* init lcd panel info */
	pinfo->xres = 720;
	pinfo->yres = 1280;
	pinfo->width  = 58;  //mm
	pinfo->height = 103; //mm
	pinfo->type = PANEL_MIPI_CMD;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = EDC_OUT_RGB_888;
	pinfo->s3d_frm = EDC_FRM_FMT_2D;
	pinfo->bgr_fmt = EDC_RGB;
	pinfo->bl_set_type = BL_SET_BY_MIPI;
	pinfo->bl_max = 100;
	pinfo->bl_min = 1;

	pinfo->frc_enable = 1;
	if(NULL != strstr(saved_command_line, "androidboot.swtype=factory"))
		pinfo->esd_enable = 0;
	else
		pinfo->esd_enable = 1;
	pr_info("esd_enable =%d\n", pinfo->esd_enable);
	pinfo->sbl_enable = 1;

	pinfo->sbl.bl_max = 0xff;
	pinfo->sbl.cal_a = 0x0f;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;

	pinfo->ldi.h_back_porch = 43;
	pinfo->ldi.h_front_porch = 80;
	pinfo->ldi.h_pulse_width = 57;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 2;

	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 0;
	pinfo->ldi.pixelclk_plr = 1;
	pinfo->ldi.data_en_plr = 0;

	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */	
	pinfo->clk_rate = 75000000;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;

	pinfo->mipi.dsi_bit_clk = 241;
	pinfo->frame_rate = 60;

	lcd_set_iomux_init();
	/* lcd resource */
	lcd_get_resource(pdev);

	/* alloc panel device data */
	if (platform_device_add_data(pdev, &jdi_panel_data,
		sizeof(struct k3_fb_panel_data))) {
		k3fb_loge("platform_device_add_data failed!\n");
		platform_device_put(pdev);
		return -ENOMEM;
	}

	reg_pdev = k3_fb_add_device(pdev);

	sema_init(&ct_sem, 1);
	g_csc_value[0] = 0;
	g_csc_value[1] = 0;
	g_csc_value[2] = 0;
	g_csc_value[3] = 0;
	g_csc_value[4] = 0;
	g_csc_value[5] = 0;
	g_csc_value[6] = 0;
	g_csc_value[7] = 0;
	g_csc_value[8] = 0;
	g_is_csc_set = 0;

	/* for cabc */
	lcd_props.type = TFT;
	lcd_props.default_gamma = GAMMA25;
	p_tuning_dev = lcd_tuning_dev_register(&lcd_props, &sp_tuning_ops, (void *)reg_pdev);
	if (IS_ERR(p_tuning_dev)) {
		k3fb_loge("lcd_tuning_dev_register failed!\n");
		return -1;
	}

	jdi_sysfs_init(pdev);

	pr_info("%s exit succ!\n", __func__);
	return 0;
}

static struct platform_driver this_driver = {
	.probe = jdi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_jdi_OTM1282B",
	},
};

static int __init mipi_jdi_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		k3fb_loge("not able to register the driver\n");
		return ret;
	}

	return ret;
}

module_init(mipi_jdi_panel_init);

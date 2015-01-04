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

#define PWM_LEVEL 100
#define EDC_PIXCEL_CLK_RATE                  (CONFIG_EDC_PIXCEL_CLK_RATE)

#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME   "gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME	"gpio_lcd_id1"
#define GPIO_LCD_ENP_NAME   "gpio_lcd_enp"
#define GPIO_LCD_ENN_NAME   "gpio_lcd_enn"
#define GPIO_LCD_PWM_NAME   "gpio_lcd_pwm_en"
#define DSI_CLK_DEFAULT_VALUE       486

#ifndef CUSTOMIZE_MIPI_CLK
#define CUSTOMIZE_MIPI_CLK
#endif

#ifdef CUSTOMIZE_MIPI_CLK
#define DSI_CLK_BUF_MAX_LEN         10
#define DSI_CLK_CUSTOMIZE_VALUE     480
#endif

struct jdi_otm1902b_panel_data{
	struct regulator *lcd_vddio;
	struct iomux_block *lcd_gpio_block;
	struct block_config *lcd_gpio_block_config;
	int lcd_gpio_reset;
	int lcd_gpio_enp;
	int lcd_gpio_enn;
	int lcd_gpio_id0;
	int lcd_gpio_id1;
	int lcd_gpio_pwm_en;
};

static struct jdi_otm1902b_panel_data *g_panel_platform_data;
static volatile bool g_display_on;
static volatile bool backlight_log_once = true;
extern u32 frame_count;
/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/
/* set backlight pwm clk to 45khz (CAB0->0x02 CAB3->0x50)*/
static char bl_PWM_CTRL1[] = {
	0x00,
	0xB0,
};

static char bl_PWM_CTRL2[] = {
	0xCA,
	0x02,
};

static char bl_PWM_CTRL3[] = {
	0x00,
	0xB3,
};

static char bl_PWM_CTRL4[] = {
	0xCA,
	0x50,
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

static char addr_shift_00[] = {
	0x00,
	0x00,
};

static char cmd2_ena1[] = {
	0xff,
	0x19, 0x02, 0x01, 0x00,
};

static char addr_shift_80[] = {
	0x00,
	0x80,
};

static char cmd2_ena2[] = {
	0xff,
	0x19, 0x02,
};

static char addr_shift_02[] = {
	0x00,
	0x02,
};

static char cmd2_ff03[] = {
	0xff,
	0x03,
};

static char cmd2_c000[] = {
	0xc0,
	0x00,
};

static char cmd2_ff01[] = {
	0xff,
	0x01,
};
//ce
//0x00 0x00
static char orise_clever_mode[] = {
	0x59,
	0x03,
};

static char addr_shift_a0[] = {
	0x00,
	0xa0,
};

static char ce_d6_1[] = {
	0xD6,
	0x03, 0x01, 0x00, 0x00, 0x00,
	0x00, 0xfd, 0x00, 0x03, 0x06,
	0x06, 0x02,
};

static char addr_shift_b0[] = {
	0x00,
	0xb0,
};

static char ce_d6_2[] = {
	0xD6,
	0x00, 0x00, 0x66, 0xb3, 0xcd,
	0xb3, 0xcd, 0xb3, 0xa6, 0xb3,
	0xcd, 0xb3,
};

static char addr_shift_c0[] = {
	0x00,
	0xc0,
};

static char ce_d6_3[] = {
	0xD6,
	0x37, 0x00, 0x89, 0x77, 0x89,
	0x77, 0x89, 0x77, 0x6f, 0x77,
	0x89, 0x77,
};

static char addr_shift_d0[] = {
	0x00,
	0xd0,
};

static char ce_d6_4[] = {
	0xD6,
	0x37, 0x3c, 0x44, 0x3c, 0x44,
	0x3c, 0x44, 0x3c, 0x37, 0x3c,
	0x44, 0x3c,
};

//0x00 0x80
static char ce_cmd[] = {
	0xD6,
	0x3A,
};

//sharpness
//0x00 0x00
static char sp_cmd[] = {
	0x59,
	0x03,
};

static char sp_shift_0x90[] = {
	0x00,
	0x90,
};

static char sp_D7_1[] = {
	0xD7,
	0x83,
};

static char sp_shift_0x92[] = {
	0x00,
	0x92,
};

static char sp_D7_2[] = {
	0xD7,
	0xff,
};

static char sp_shift_0x93[] = {
	0x00,
	0x93,
};

static char sp_D7_3[] = {
	0xD7,
	0x00,
};

//CABC
//0x00 0x00
//0x59 0x03
//0x00 0x80
static char cabc_ca[] = {
	0xCA,
	0x80,0x88,0x90,0x98,0xa0,
	0xa8,0xb0,0xb8,0xc0,0xc7,
	0xcf,0xd7,0xdf,0xe7,0xef,
	0xf7,0xcc,0xff,0xa5,0xff,
	0x80,0xff,0x05,0x03,0x05,
	0x03,0x05,0x03,
};
//0x00 0x00
static char cabc_c6_G1[] = {
	0xc6,
	0x10,
};
static char cabc_c7_G1[] = {
	0xC7,
	0xa0,0xab,0xca,0xab,0x9b,
	0xbc,0xa9,0xbb,0xaa,0xac,
	0xba,0x88,0x78,0x56,0x24,
	0x22,0x22,0x22,
};

//0x00 0x00
static char cabc_c6_G2[] = {
	0xc6,
	0x11,
};
static char cabc_c7_G2[] = {
	0xC7,
	0xa0,0xaa,0xca,0xab,0x99,
	0xcb,0x9a,0xba,0xaa,0xab,
	0xba,0x88,0x78,0x56,0x34,
	0x33,0x33,0x22,
};

//0x00 0x00
static char cabc_c6_G3[] = {
	0xc6,
	0x12,
};
static char cabc_c7_G3[] = {
	0xC7,
	0xa0,0x9a,0x9b,0xab,0x99,
	0xbb,0xaa,0xa9,0x9a,0xba,
	0xaa,0x88,0x88,0x67,0x35,
	0x33,0x33,0x33,
};

//0x00 0x00
static char cabc_c6_G4[] = {
	0xc6,
	0x13,
};
static char cabc_c7_G4[] = {
	0xC7,
	0xa0,0xa9,0x9a,0x9c,0x8a,
	0xbb,0x9a,0xa9,0x9a,0xaa,
	0x9b,0x88,0x88,0x67,0x45,
	0x44,0x34,0x33,
};

//0x00 0x00
static char cabc_c6_G5[] = {
	0xc6,
	0x14,
};
static char cabc_c7_G5[] = {
	0xC7,
	0xa0,0x99,0xaa,0x9b,0x8a,
	0xa9,0xa8,0xa9,0x9a,0xa9,
	0x9a,0x88,0x88,0x78,0x45,
	0x44,0x44,0x44,
};

//0x00 0x00
static char cabc_c6_G6[] = {
	0xc6,
	0x15,
};
static char cabc_c7_G6[] = {
	0xC7,
	0x90,0x8a,0xaa,0x9a,0x8a,
	0xaa,0x87,0x99,0x9a,0xaa,
	0xa9,0x88,0x88,0x78,0x56,
	0x45,0x44,0x44,
};

//0x00 0x00
static char cabc_c6_G7[] = {
	0xc6,
	0x16,
};
static char cabc_c7_G7[] = {
	0xC7,
	0x90,0x99,0x9a,0x9a,0x89,
	0xc9,0x98,0x88,0xa9,0x98,
	0xab,0x88,0x88,0x78,0x56,
	0x55,0x55,0x44,
};

//0x00 0x00
static char cabc_c6_G8[] = {
	0xc6,
	0x17,
};
static char cabc_c7_G8[] = {
	0xC7,
	0x90,0x99,0x99,0x8a,0x8b,
	0xa9,0x98,0x99,0x78,0x89,
	0xab,0x88,0x88,0x88,0x56,
	0x55,0x55,0x55,
};

//0x00 0x00
static char cabc_c6_G9[] = {
	0xc6,
	0x18,
};
static char cabc_c7_G9[] = {
	0xC7,
	0x90,0x89,0x9a,0x89,0x8a,
	0xc8,0x98,0x98,0x89,0x56,
	0xb9,0x88,0x88,0x88,0x67,
	0x56,0x55,0x55,
};

//0x00 0x00
static char cabc_c6_G10[] = {
	0xc6,
	0x19,
};
static char cabc_c7_G10[] = {
	0xC7,
	0x90,0x89,0x99,0x89,0x8a,
	0xb8,0x98,0x98,0x89,0x79,
	0x77,0x88,0x88,0x88,0x67,
	0x66,0x66,0x56,
};

//0x00 0x00
static char cabc_c6_G11[] = {
	0xc6,
	0x1a,
};
static char cabc_c7_G11[] = {
	0xC7,
	0x90,0x98,0x89,0x89,0x99,
	0x98,0x89,0xa8,0x89,0x89,
	0x78,0x77,0x86,0x88,0x78,
	0x66,0x66,0x66,
};

//0x00 0x00
static char cabc_c6_G12[] = {
	0xc6,
	0x1b,
};
static char cabc_c7_G12[] = {
	0xC7,
	0x90,0x88,0x99,0x88,0x89,
	0x99,0x98,0x88,0x89,0x89,
	0x98,0x77,0x68,0x87,0x78,
	0x77,0x77,0x66,
};

//0x00 0x00
static char cabc_c6_G13[] = {
	0xc6,
	0x1c,
};
static char cabc_c7_G13[] = {
	0xC7,
	0x90,0x88,0x89,0x98,0x88,
	0x99,0x88,0x88,0x89,0x89,
	0x88,0x88,0x78,0x78,0x87,
	0x77,0x77,0x77,
};

//0x00 0x00
static char cabc_c6_G14[] = {
	0xc6,
	0x1d,
};
static char cabc_c7_G14[] = {
	0xC7,
	0x90,0x88,0x98,0x88,0x88,
	0x89,0x98,0x88,0x88,0x98,
	0x88,0x88,0x88,0x78,0x78,
	0x86,0x77,0x77,
};

//0x00 0x00
static char cabc_c6_G15[] = {
	0xc6,
	0x1e,
};
static char cabc_c7_G15[] = {
	0xC7,
	0x90,0x88,0x88,0x88,0x98,
	0x88,0x88,0x88,0x88,0x89,
	0x88,0x88,0x88,0x88,0x87,
	0x88,0x87,0x77,
};

//0x00 0x00
static char cabc_c6_G16[] = {
	0xc6,
	0x1f,
};
static char cabc_c7_G16[] = {
	0xC7,
	0x80,0x88,0x88,0x88,0x88,
	0x88,0x88,0x88,0x88,0x88,
	0x88,0x88,0x88,0x88,0x88,
	0x88,0x88,0x88,
};

static char cabc_shift_UI[] = {
	0x00,
	0x90,
};

static char cabc_UI_mode[] = {
	0xCA,
	0xCC, 0xFF,
};

static char cabc_shift_STILL[] = {
	0x00,
	0x92,
};

static char cabc_STILL_mode[] = {
	0xCA,
	0xA5, 0xFF,
};

static char cabc_shift_moving[] = {
	0x00,
	0x94,
};

static char cabc_moving_mode[] = {
	0xCA,
	0x80, 0xFF,
};

//0x00 0x00
static char cabc_disable_curve[] = {
	0xc6,
	0x00,
};

//0x00 0x00
static char cabc_disable_setting[] = {
	0x59,
	0x00,
};

static char cabc_set_pwm_value[] = {
	0x51,
	0xff,
};
static char cabc_53[] = {
	0x53,
	0x2c,
};
static char cabc_set_mode_UI[] = {
	0x55,
	0x91,
};
static char cabc_set_mode_STILL[] = {
	0x55,
	0x92,
};
static char cabc_set_mode_MOVING[] = {
	0x55,
	0x93,
};

#if 0
static char addr_shift_e7[] = {
	0x00,
	0xe7,
};

static char cmd2_temp[] = {
	0xcd,
	0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f, 0x2f,
};
#endif

static char addr_shift_83[] = {
	0x00,
	0x83,
};

static char adjustment_IC_1[] = {
	0xf3,
	0xca,
};

static char addr_shift_90[] = {
	0x00,
	0x90,
};

static char adjustment_IC_2[] = {
	0xc4,
	0x00,
};

static char addr_shift_b4[] = {
	0x00,
	0xb4,
};

static char adjustment_IC_3[] = {
	0xc0,
	0xc0,
};

static char addr_shift_87[] = {
	0x00,
	0x87,
};

static char pixel_eyes_set[] = {
	0xa4,
	0x15,
};

static char display_brightness[] = {
	0x51,
	0x00,
};

static char bl_enable[] = {
	0x53,
	0x24,
};

static char cabc_mode_set[] = {
	0x55,
	0x90,
};

static char cabc_min_brightness[] = {
	0x5e,
	0x00,
};

static char Delay_TE[] = {
	0x44,
	0x02, 0x00,
};

static char normal_display_on[] = {
	0x13,
};

static char all_pixels_off[] = {
	0x22,
};

/*******************************************************************************
** Power OFF Sequence(Normal to power off)
*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};

static char bl_enable_noDimming[] = {
	0x53,
	0x24,
};

static char ca_set[] = {
	0x2a,
	0x00, 0x00, 0x04, 0x37,
};

static char pa_set[] = {
	0x2b,
	0x00, 0x00, 0x07, 0x7f,
};

static struct dsi_cmd_desc jdi_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cmd2_ena1), cmd2_ena1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_80), addr_shift_80},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cmd2_ena2), cmd2_ena2},
#if 0
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_e7), addr_shift_e7},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cmd2_temp), cmd2_temp},
#endif
	//CE
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(orise_clever_mode), orise_clever_mode},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_a0), addr_shift_a0},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(ce_d6_1), ce_d6_1},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_b0), addr_shift_b0},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(ce_d6_2), ce_d6_2},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_c0), addr_shift_c0},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(ce_d6_3), ce_d6_3},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_d0), addr_shift_d0},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(ce_d6_4), ce_d6_4},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_80), addr_shift_80},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(ce_cmd), ce_cmd},
	//sharpness
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_cmd), sp_cmd},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_shift_0x90), sp_shift_0x90},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_D7_1), sp_D7_1},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_shift_0x92), sp_shift_0x92},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_D7_2), sp_D7_2},
	//cabc
#if 0
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_80), addr_shift_80},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_ca), cabc_ca},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G1), cabc_c6_G1},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G1), cabc_c7_G1},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G2), cabc_c6_G2},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G2), cabc_c7_G2},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G3), cabc_c6_G3},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G3), cabc_c7_G3},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G4), cabc_c6_G4},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G4), cabc_c7_G4},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G5), cabc_c6_G5},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G5), cabc_c7_G5},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G6), cabc_c6_G6},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G6), cabc_c7_G6},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G7), cabc_c6_G7},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G7), cabc_c7_G7},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G8), cabc_c6_G8},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G8), cabc_c7_G8},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G9), cabc_c6_G9},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G9), cabc_c7_G9},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G10), cabc_c6_G10},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G10), cabc_c7_G10},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G11), cabc_c6_G11},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G11), cabc_c7_G11},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G12), cabc_c6_G12},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G12), cabc_c7_G12},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G13), cabc_c6_G13},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G13), cabc_c7_G13},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G14), cabc_c6_G14},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G14), cabc_c7_G14},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G15), cabc_c6_G15},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G15), cabc_c7_G15},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c6_G16), cabc_c6_G16},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_c7_G16), cabc_c7_G16},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_shift_UI), cabc_shift_UI},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_UI_mode), cabc_UI_mode},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_shift_STILL), cabc_shift_STILL},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_STILL_mode), cabc_STILL_mode},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_shift_moving), cabc_shift_moving},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_moving_mode), cabc_moving_mode},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_disable_curve), cabc_disable_curve},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_disable_setting), cabc_disable_setting},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_pwm_value), cabc_set_pwm_value},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_53), cabc_53},
#endif
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_83), addr_shift_83},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(adjustment_IC_1), adjustment_IC_1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_90), addr_shift_90},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(adjustment_IC_2), adjustment_IC_2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_b4), addr_shift_b4},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(adjustment_IC_3), adjustment_IC_3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_87), addr_shift_87},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(pixel_eyes_set), pixel_eyes_set},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(addr_shift_00), addr_shift_00},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},
	//{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
	//	sizeof(ca_set), ca_set},
	//{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
	//	sizeof(pa_set), pa_set},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(display_brightness), display_brightness},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(all_pixels_off), all_pixels_off},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_mode_set), cabc_mode_set},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_min_brightness), cabc_min_brightness},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(Delay_TE), Delay_TE},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL1), bl_PWM_CTRL1},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL2), bl_PWM_CTRL2},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL3), bl_PWM_CTRL3},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL4), bl_PWM_CTRL4},
	{DTYPE_DCS_WRITE, 0, 7, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
};

static struct dsi_cmd_desc jdi_cabc_ui_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_UI), cabc_set_mode_UI},
};

static struct dsi_cmd_desc jdi_cabc_still_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_STILL), cabc_set_mode_STILL},
};

static struct dsi_cmd_desc jdi_cabc_moving_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(cabc_set_mode_MOVING), cabc_set_mode_MOVING},
};
static struct dsi_cmd_desc jdi_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 52, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 102, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
};

static char command_2_enable[] = {
	0x00,
	0x00,
};

static char command_2_enable_1_para[] = {
	0xFF,
	0x19, 0x02, 0x01,
};

static char command_2_enable_2[] = {
	0x00,
	0x80,
};

static char command_2_enable_2_para[] = {
	0xFF,
	0x19, 0x02,
};

static char HD720_setting_1_para[] = {
	0x2A,
	0x00, 0x00, 0x02, 0xCF,
};

static char HD1080_setting_1_para[] = {
	0x2a,
	0x00, 0x00, 0x04, 0x37,
};

static char HD720_setting_2_para[] = {
	0x2B,
	0x00, 0x00, 0x04, 0xFF,
};

static char HD1080_setting_2_para[] = {
	0x2b,
	0x00, 0x00, 0x07, 0x7f,
};

static char cleveredge_1_5x_para[] = {
	0x1C,
	0x05,
};

static char cleveredge_disable[] = {
	0x1C,
	0x00,
};

static char cleveredge_P1[] = {
	0x00,
	0x91,
};

static char cleveredge_P1_para[] = {
	0xD7,
	0xC8,
};

static char cleveredge_P2[] = {
	0x00,
	0x93,
};

static char cleveredge_P2_para[] = {
	0xD7,
	0x08,
};

static char cleveredge_use_setting[] = {
	0x00,
	0xAC,
};

static char cleveredge_use_setting_para[] = {
	0xC0,
	0x04,
};

static char command_2_disable_para[] = {
	0xFF,
	0xFF, 0xFF, 0xFF, 0xFF,
};

static char command_clevermode[] = {
	0x59,
	0x03,
};

static struct dsi_cmd_desc cleveredge_inital_720P_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_1_para), command_2_enable_1_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_2), command_2_enable_2},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_2_para), command_2_enable_2_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_clevermode), command_clevermode},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(HD720_setting_1_para), HD720_setting_1_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(HD720_setting_2_para), HD720_setting_2_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_1_5x_para), cleveredge_1_5x_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_P1), cleveredge_P1},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_P1_para), cleveredge_P1_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_P2), cleveredge_P2},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_P2_para), cleveredge_P2_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_use_setting), cleveredge_use_setting},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_use_setting_para), cleveredge_use_setting_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_disable_para), command_2_disable_para}
};

static struct dsi_cmd_desc cleveredge_inital_1080P_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_1_para), command_2_enable_1_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_2), command_2_enable_2},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable_2_para), command_2_enable_2_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(HD1080_setting_1_para), HD1080_setting_1_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(HD1080_setting_2_para), HD1080_setting_2_para},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(command_2_enable), command_2_enable},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(cleveredge_disable), cleveredge_disable},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_shift_0x93), sp_shift_0x93},
	{DTYPE_DCS_LWRITE, 0, 10, WAIT_TYPE_US,
		sizeof(sp_D7_3), sp_D7_3},
};

/*******************************************************************************
** LCD IOMUX
*/

static int lcd_iomux_get(void)
{
	g_panel_platform_data->lcd_gpio_block = iomux_get_block(IOMUX_LCD_NAME);
	if (!g_panel_platform_data->lcd_gpio_block) {
		pr_err("%s failed to get iomux_lcd!\n", __func__);
		return PTR_ERR(g_panel_platform_data->lcd_gpio_block);
	}

	g_panel_platform_data->lcd_gpio_block_config = iomux_get_blockconfig(IOMUX_LCD_NAME);
	if (!g_panel_platform_data->lcd_gpio_block_config) {
		pr_err("%s failed to get iomux_lcd config!\n", __func__);
		return PTR_ERR(g_panel_platform_data->lcd_gpio_block_config);
	}

	return 0;
}

static void lcd_iomux_set(int mode)
{
	if (blockmux_set(g_panel_platform_data->lcd_gpio_block, g_panel_platform_data->lcd_gpio_block_config, mode) != 0) {
		pr_err("%s failed to set iomux_lcd normal mode!\n", __func__);
	}
}

/*******************************************************************************
** LCD GPIO
*/
static int lcd_get_one_gpio_resource(struct platform_device *pdev, char *name)
{
	struct resource *res =	NULL;
	int gpio = -1;
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, name);
	if (res == NULL) {
		pr_err("%s failed to get gpio resource:%s!\n", __func__, name);
		return -1;
	}

	gpio = res->start;
	if (!gpio_is_valid(gpio)) {
		pr_err("%s gpio %d for %s is invalid.", __func__, gpio, name);
		return -1;
	}
	pr_info("%s gpio %d for %s is valid.", __func__, gpio, name);
	return gpio;
}


static void lcd_gpio_request(void)
{

	if (gpio_request(g_panel_platform_data->lcd_gpio_reset, GPIO_LCD_RESET_NAME) != 0) {
		pr_err("%s failed to request gpio reset!\n", __func__);
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_id0, GPIO_LCD_ID0_NAME) != 0) {
		pr_err("%s failed to request gpio_lcd_id0!\n", __func__);
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_id1, GPIO_LCD_ID1_NAME) != 0) {
		pr_err("%s failed to request gpio_lcd_id1!\n", __func__);
	}

	if(gpio_request(g_panel_platform_data->lcd_gpio_enp, GPIO_LCD_ENP_NAME) != 0){
	    pr_err("%s failed to request enp!\n", __func__);
	}

	if(gpio_request(g_panel_platform_data->lcd_gpio_enn, GPIO_LCD_ENN_NAME) != 0){
	    pr_err("%s failed to request enn!\n", __func__);
	}

	if(gpio_request(g_panel_platform_data->lcd_gpio_pwm_en, GPIO_LCD_PWM_NAME) != 0){
	    pr_err("%s failed to request pwm name!\n", __func__);
	}
}


static void lcd_gpio_free(void)
{

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_reset)) {
		gpio_free(g_panel_platform_data->lcd_gpio_reset);
	}

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_id0)) {
		gpio_free(g_panel_platform_data->lcd_gpio_id0);
	}

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_id1)) {
		gpio_free(g_panel_platform_data->lcd_gpio_id1);
	}

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_enp)) {
		gpio_free(g_panel_platform_data->lcd_gpio_enp);
	}

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_enn)) {
		gpio_free(g_panel_platform_data->lcd_gpio_enn);
	}

	if (gpio_is_valid(g_panel_platform_data->lcd_gpio_pwm_en)) {
		gpio_free(g_panel_platform_data->lcd_gpio_pwm_en);
	}
}


static int lcd_resource(struct platform_device *pdev, struct resource *res)
{
	BUG_ON(pdev == NULL);

	g_panel_platform_data->lcd_gpio_reset = lcd_get_one_gpio_resource(pdev, GPIO_LCD_RESET_NAME);
	g_panel_platform_data->lcd_gpio_id0 = lcd_get_one_gpio_resource(pdev, GPIO_LCD_ID0_NAME);
	g_panel_platform_data->lcd_gpio_id1 = lcd_get_one_gpio_resource(pdev, GPIO_LCD_ID1_NAME);
	g_panel_platform_data->lcd_gpio_enp = lcd_get_one_gpio_resource(pdev, GPIO_LCD_ENP_NAME);
	g_panel_platform_data->lcd_gpio_enn = lcd_get_one_gpio_resource(pdev, GPIO_LCD_ENN_NAME);
	g_panel_platform_data->lcd_gpio_pwm_en = lcd_get_one_gpio_resource(pdev, GPIO_LCD_PWM_NAME);

	return 0;
}
 
 
static int set_iomux_init(char *block_name,struct iomux_block **gpio_block,struct block_config **gpio_block_config)
{
	int ret = 0;

	BUG_ON(block_name==NULL);
	BUG_ON(gpio_block==NULL);
	BUG_ON(gpio_block_config==NULL);

	/* get gpio block*/
	*gpio_block = iomux_get_block(block_name);
	if (IS_ERR(*gpio_block)) {
		pr_err("%s: failed to get gpio block,iomux_get_block failed\n", __func__);
		ret = -EINVAL;
		return ret;
	}

    /* get gpio block config*/
	*gpio_block_config = iomux_get_blockconfig(block_name);
	if (IS_ERR(*gpio_block_config)) {
		pr_err("%s: failed to get gpio block config\n", __func__);
		ret = -EINVAL;
		*gpio_block = NULL;
		return ret;
	}

	return 0;

}

static int set_iomux_normal(struct iomux_block *gpio_block,struct block_config *gpio_block_config)
{
	int ret;

	BUG_ON(gpio_block_config==NULL);
	BUG_ON(gpio_block==NULL);

	ret = blockmux_set(gpio_block, gpio_block_config, NORMAL);
	if (ret<0) {
		pr_err("%s: failed to config gpio\n", __func__);
		return ret;
	}

	return 0;
}

static int set_iomux_lowpower(struct iomux_block *gpio_block,struct block_config *gpio_block_config)
{
	int ret;

	BUG_ON(gpio_block_config==NULL);
	BUG_ON(gpio_block==NULL);

	ret = blockmux_set(gpio_block, gpio_block_config, LOWPOWER);
	if (ret<0) {
		pr_err("%s: failed to config gpio\n", __func__);
		return ret;
	}

	return 0;
}  

static struct k3_fb_panel_data jdi_panel_data;

/******************************************************************************/
static struct lcd_tuning_dev *p_tuning_dev = NULL;
static int cabc_mode = 1; /* allow application to set cabc mode to ui mode */

/*y=pow(x,0.6),x=[0,255]*/
static u32 square_point_six(u32 x)
{
	unsigned long t = x * x * x;
	int i = 0, j = 255, k = 0;
	unsigned long t0 = 0;
	while (j - i > 1) {
		k = (i + j) / 2;
			t0 = k * k * k * k * k;
		if(t0 < t)
			i = k;
		else if (t0 > t)
			j = k;
		else
			return k;
	}
	return k;
}

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
#if 0
	switch (cabc)
	{
		case CABC_UI:
			mipi_dsi_cmds_tx(jdi_cabc_ui_on_cmds, \
							ARRAY_SIZE(jdi_cabc_ui_on_cmds));
			break;
		case CABC_VID:
			mipi_dsi_cmds_tx(jdi_cabc_moving_on_cmds, \
							ARRAY_SIZE(jdi_cabc_moving_on_cmds));
			break;
		case CABC_OFF:
			break;
		default:
			ret = -1;
	}
#endif
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
	sprintf(buf, "jdi_otm1902b 5.0' FHD TFT %d x %d\n",
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

	if (val == 1) {
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
		pr_err("%s create sysfs file failed!\n", __func__);
		return ret;
	}
	return 0;
}

static void jdi_sysfs_deinit(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &jdi_attr_group);
}


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
			retval = ts_power_control_notify(TS_RESUME_DEVICE, SHORT_SYNC_TIMEOUT);
			if (retval < 0) {
				pr_err("%s failed to send TS_RESUME_DEVICE. Code: %d.\n", __func__, retval);
			}
			lcd_iomux_set(NORMAL);
			lcd_gpio_request();

			mdelay(4);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_pwm_en, 1);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_enp, 1);
			mdelay(4);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_enn, 1);
			mdelay(2);

			pinfo->lcd_init_step = LCD_INIT_SEND_SEQUENCE;
		}
	} else if (pinfo->lcd_init_step == LCD_INIT_SEND_SEQUENCE) {
		if (!g_display_on) {
			mdelay(12);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 1);
			mdelay(17);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 0);
			mdelay(2);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 1);
			mdelay(12);

			//Multi-Resolution====begin
			if(DISPLAY_LOW_POWER_LEVEL_HD == k3fd->switch_res_flag) {
				mipi_dsi_cmds_tx(cleveredge_inital_720P_cmds, ARRAY_SIZE(cleveredge_inital_720P_cmds));
			} else {
				mipi_dsi_cmds_tx(cleveredge_inital_1080P_cmds, ARRAY_SIZE(cleveredge_inital_1080P_cmds));
			}
			//Multi-Resolution====end

			/* lcd display on sequence */
			mipi_dsi_cmds_tx(jdi_display_on_cmds, ARRAY_SIZE(jdi_display_on_cmds));
			//mipi_dsi_cmds_tx(jdi_cabc_ui_on_cmds, ARRAY_SIZE(jdi_cabc_ui_on_cmds));//jdi_cabc_moving_on_cmds
			//mipi_dsi_cmds_tx(jdi_cabc_cmds, ARRAY_SIZE(jdi_cabc_cmds));
			g_display_on = true;
			backlight_log_once = true;
			jdi_set_ct_cscValue(k3fd);
			retval = ts_power_control_notify(TS_AFTER_RESUME, NO_SYNC_TIMEOUT);
			if (retval < 0) {
				pr_err("%s failed to send TS_AFTER_RESUME. Code: %d.\n", __func__, retval);
			}
		}
	} else {
		pr_err("%s failed to init lcd!\n", __func__);
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
		pr_err("%s failed to send TS_BEFORE_SUSPEND. Code: %d.\n", __func__, retval);
	}
#ifdef CONFIG_DEBUG_FS
	if ((g_fb_lowpower_debug_flag & DEBUG_LCD_LOWPOWER_DISABLE) == DEBUG_LCD_LOWPOWER_DISABLE) {
		pr_err("%s lcd off was disable", __func__);
		return 0;
	}
#endif
	if (g_display_on) {
		g_display_on = false;
		mipi_dsi_cmds_tx(jdi_display_off_cmds, ARRAY_SIZE(jdi_display_off_cmds));

		gpio_direction_output(g_panel_platform_data->lcd_gpio_pwm_en, 0);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_enn, 0);
		mdelay(5);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_enp, 0);
		mdelay(5);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 0);
		mdelay(1);
		lcd_gpio_free();
#ifdef CONFIG_MACH_HI6620OEM	
		lcd_iomux_set(LOWPOWER);
#endif
	    mdelay(1);
		retval = ts_power_control_notify(TS_SUSPEND_DEVICE, SHORT_SYNC_TIMEOUT);
		if (retval < 0) {
			pr_err("%s failed to send TS_SUSPEND_DEVICE. Code: %d.\n", __func__, retval);
		}
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

	struct dsi_cmd_desc  jdi_bl_level_adjust[] = {
		{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
			sizeof(bl_level_adjust), bl_level_adjust},
	};

	struct dsi_cmd_desc jdi_normal_display_on[] = {
		{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_US,
			sizeof(normal_display_on), normal_display_on},
	};

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	level = k3fd->bl_level;

    //backlight may turn off when bl_level is below 6.
    /*Our eyes are more sensitive to small brightness.
	So we adjust the brightness of lcd following iphone4
	---the original description for >248*/
	if (level < 6 && level != 0) {
		level = 6;
	} else if (level >= 29 && level <= 34) {
		level = 35;
	} else if (level >= 59 && level <= 69) {
		level = 70;
	} else if (level >= 123 && level <= 133) {
		level = 134;
	} else if (level > 248) {
		level = 248;
	}

	bl_level_adjust[1] = level;

	mipi_dsi_cmds_tx(jdi_bl_level_adjust, \
		ARRAY_SIZE(jdi_bl_level_adjust));

	if (backlight_log_once) {
		backlight_log_once = false;

		mipi_dsi_cmds_tx(jdi_normal_display_on, \
			ARRAY_SIZE(jdi_normal_display_on));

		pr_info("%s k3fd->bl_level=%d,set backlight to level = %d\n", __func__, k3fd->bl_level, level);
	}
	return 0;
}

static int mipi_jdi_panel_set_fastboot(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	int retval;
    
	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	lcd_iomux_set(NORMAL);
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

	/* Fix me: Implement it */

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

#ifdef CUSTOMIZE_MIPI_CLK
static long jdi_parse_dsi_clk_from_commandline(char *buf)
{
	char *p_str = buf;
	char dsi_clk_buf[DSI_CLK_BUF_MAX_LEN] = {0};
	int i = 0;
	long ret_dsi_clk = DSI_CLK_DEFAULT_VALUE;
	int ret = 0;

	if (NULL == buf) {
		pr_err("%s buf is empty\n", __func__);
		return ret_dsi_clk;
	}

	for (i = 0; i < DSI_CLK_BUF_MAX_LEN-1; i++) {
		if(buf[i] == ' ')
			break;
		dsi_clk_buf[i] = buf[i];
	}

	if (dsi_clk_buf[0] == '\0') {
		pr_err("%s get dsi_clk string fail\n", __func__);
		return ret_dsi_clk;
	}

	ret = strict_strtol(dsi_clk_buf, 10, &ret_dsi_clk);
	if (ret != 0) {
		pr_err("%s convert fail, set default value\n", __func__);
		ret_dsi_clk = DSI_CLK_DEFAULT_VALUE;
	}

	if (ret_dsi_clk != DSI_CLK_CUSTOMIZE_VALUE && ret_dsi_clk != DSI_CLK_DEFAULT_VALUE) {
		pr_err("%s dsi_clk is out of range:%d, set default value\n", __func__, ret_dsi_clk);
		ret_dsi_clk = DSI_CLK_DEFAULT_VALUE;
	}

	return ret_dsi_clk;
}
#endif


static int mipi_jdi_set_disp_resolution(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	int retval = 0;
#ifdef CUSTOMIZE_MIPI_CLK
	char *p_str = NULL;
#endif

	BUG_ON(pdev == NULL);

	pr_info("%s enter succ!\n",__func__);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	pinfo = &(k3fd->panel_info);

	switch (k3fd->switch_res_flag) {
		case DISPLAY_LOW_POWER_LEVEL_HD:
			pinfo->xres = 720;
			pinfo->yres = 1280;
			pinfo->clk_rate = 76000000;
			pinfo->mipi.dsi_bit_clk = 241;
			break;
		case DISPLAY_LOW_POWER_LEVEL_FHD:
			pinfo->xres = 1080;
			pinfo->yres = 1920;
			pinfo->clk_rate = 150000000;
#ifdef CUSTOMIZE_MIPI_CLK
			p_str = strstr(saved_command_line, "dsi_clk=");
			if(NULL != p_str) {
				pinfo->mipi.dsi_bit_clk = (u32)jdi_parse_dsi_clk_from_commandline(p_str+8);
			}
			else
				pinfo->mipi.dsi_bit_clk = DSI_CLK_DEFAULT_VALUE;
#else
			pinfo->mipi.dsi_bit_clk = DSI_CLK_DEFAULT_VALUE;
#endif
			break;
		default:
			return -1;
	}

	return retval;
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
#ifdef CONFIG_FB_MIPI_DETECT
	.mipi_detect = mipi_jdi_panel_mipi_detect,
#endif
	.set_disp_resolution = mipi_jdi_set_disp_resolution,
};


static int __devinit jdi_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;
	struct platform_device *reg_pdev = NULL;
	struct lcd_properities lcd_props;
	int retval = 0;
#ifdef CUSTOMIZE_MIPI_CLK
	char *p_str = NULL;
#endif
	pr_info("%s enter succ!\n", __func__);

	g_panel_platform_data = kzalloc(sizeof(struct jdi_otm1902b_panel_data), GFP_KERNEL);
	if (NULL == g_panel_platform_data) {
		pr_err("%s alloc driver data error\n", __func__);
		return -ENOMEM;
	}
	g_display_on = false;
	pinfo = jdi_panel_data.panel_info;

	/* init lcd panel info */
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->width  = 61;  //mm
	pinfo->height = 109; //mm
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
	pr_info("%s esd_enable =%d\n", __func__, pinfo->esd_enable);
	pinfo->sbl_enable = 1;

	pinfo->sbl.bl_max = 0xff;
	pinfo->sbl.cal_a = 0x0f;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;

	pinfo->ldi.h_back_porch = 23;
	pinfo->ldi.h_front_porch = 50;
	pinfo->ldi.h_pulse_width = 20;
	pinfo->ldi.v_back_porch = 12;
	pinfo->ldi.v_front_porch = 14;
	pinfo->ldi.v_pulse_width = 2;

	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 0;
	pinfo->ldi.pixelclk_plr = 1;
	pinfo->ldi.data_en_plr = 0;

	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */	
	pinfo->frame_rate = 60;
	pinfo->clk_rate = 150000000;

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;

#ifdef CUSTOMIZE_MIPI_CLK
	p_str = strstr(saved_command_line, "dsi_clk=");
	if(NULL != p_str) {
		pinfo->mipi.dsi_bit_clk = (u32)jdi_parse_dsi_clk_from_commandline(p_str+8);
	}
	else
		pinfo->mipi.dsi_bit_clk = DSI_CLK_DEFAULT_VALUE;
#else
	pinfo->mipi.dsi_bit_clk = DSI_CLK_DEFAULT_VALUE;
#endif
	pr_info("%s dsi_bit_clk =%d\n", __func__, pinfo->mipi.dsi_bit_clk);

	lcd_iomux_get();
 
	/* lcd resource */
	lcd_resource(pdev, res);
	/* alloc panel device data */
	if (platform_device_add_data(pdev, &jdi_panel_data,
		sizeof(struct k3_fb_panel_data))) {
		pr_err("%s platform_device_add_data failed!\n", __func__);
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
		pr_err("lcd_tuning_dev_register failed!\n");
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
		.name = "mipi_jdi_OTM1902B",
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

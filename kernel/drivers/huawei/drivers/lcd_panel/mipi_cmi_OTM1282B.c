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
#include "drv_regulator_user.h"

#define PWM_LEVEL 100
#define EDC_PIXCEL_CLK_RATE                  (CONFIG_EDC_PIXCEL_CLK_RATE)

#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_ID0_NAME   "gpio_lcd_id0"
#define GPIO_LCD_ID1_NAME	"gpio_lcd_id1"
#define GPIO_LCD_ENP_NAME   "gpio_lcd_enp"
#define GPIO_LCD_ENN_NAME   "gpio_lcd_enn"
#define GPIO_LCD_PWM_NAME   "gpio_lcd_pwm_en"

#define GPIO_LCD_POWER_NAME	"gpio_lcd_power"

struct cmi_otm1282b_panel_data{
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

static struct cmi_otm1282b_panel_data *g_panel_platform_data;
static volatile bool g_display_on;
static volatile bool backlight_log_once = true;
extern u32 frame_count;
/*******************************************************************************
** Power ON Sequence(sleep mode to Normal mode)
*/

static char bl_level_0[] = {
	0x51,
	0x00,
};

static char bl_level[] = {
	0x51,
	0x00,
};

#if 0
static char bl_enable[] = {
	0x53,
	0x2C,
};

static char get_chip_id[] = {
	0xDA,
};
#endif

static char te_enable[] = {
	0x35,
	0x00,
};


static char exit_sleep[] = {
	0x11,
};

static char normal_display_on[] = {
	0x13,
};

static char all_pixels_off[] = {
	0x22,
};

static char display_on[] = {
	0x29,
};

static char precharge_ref1[] = {
	0x00,
	0x83,
};

static char precharge_ref2[] = {
	0xC4,
	0x02,
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



/*enable orise mode*/
static char enable_orise_mode1[] = {
	0xFF,
	0x12, 0x82,0x01,
};

static char enable_orise_mode2[] = {
	0x00,
	0x80, 
};

static char enable_orise_mode3[] = {
	0xFF,
	0x12, 0x82,
};

static char enable_orise_mode4[] = {
	0x00,
	0x80,
};

/*Disable per-charge*/
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
	0x92, 0xD6,0xAF,0xAF,0x82,0x88,0x44,0x44,0x40,0x88,
};

/* Delay TE*/
static char Delay_TE[] = {
	0x44,
	0x00, 0x80,
};


static char  P_DRV_M1[] = {
	0x00,
	0xB3,
};

static char P_DRV_M2[] = {
	0xC0,
	0x33,
};

static char bl_PWM_CTRL1[] = {
	0x00,
	0xB0,
};

static char bl_PWM_CTRL2[] = {
	0xCA,
	0x02,0x02,0x5F,0x50,
};

static char bl_enable_noDimming[] = {
	0x53,
	0x24,
};

#if 0
static char bl_PWM_CTRL3[] = {
	0xCA,
	0xE3,0xE3,0x5F,0x50,
};
#endif
static char orise_shift_0xb4[] = {
	0x00,
	0xb4,
};

static char display_address[] = {
	0xc0,
	0x10,
};

//#define RGV_INV_ENABLE

#ifdef RGV_INV_ENABLE

static char Gen_write_RGB_INV_ON1[] = {
	0xff,
	0x12,
	0x82,
	0x01,
};

static char Gen_write_RGB_INV_ON2[] = {
	0x00,
	0x80,
};

static char Gen_write_RGB_INV_ON3[] = {
	0xff,
	0x12,
	0x82,
};

static char RGB_INV0[] = {
	0x00,
	0xB3,
};

static char RGB_INV1[] = {
	0xC0,
	0x66,
};

static char Gen_write_RGB_INV_OFF1[] = {
	0x00,
	0x80,
};

static char Gen_write_RGB_INV_OFF2[] = {
	0xff,
	0x00,
	0x00,
};

static char Gen_write_RGB_INV_OFF3[] = {
	0x00,
	0x00,
};

static char Gen_write_RGB_INV_OFF4[] = {
	0xff,
	0x00,
	0x00,
	0x00,
};


#endif

/*----------------CABC Base Sequence---------------------*/
static char enable_orise_mode5[] = {
	0x00,
	0x00,
};

#if 0
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

static char CABC_STILL_curve_setting[] = {
	0xc7,
	0xa0, 0x9a, 0x99, 0x99, 0x89,
	0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x78, 0x87, 0x78, 0x77,
	0x77, 0x77, 0x77,
};

static char CABC_VID_curve_setting[] = {
	0xc7,
	0xb0, 0xab, 0xaa, 0x99, 0x99,
	0x99, 0x89, 0x88, 0x88, 0x88,
	0x77, 0x77, 0x77, 0x77, 0x77,
	0x77, 0x77, 0x56,
};

static char CABC_STILL_MODE[] = {
	0x55,
	0x92,
};

static char CABC_STILL_curve[] = {
	0xc6,
	0x11,
};


static char CABC_VID_MODE[] = {
	0x55,
	0x93,
};

static char CABC_VID_curve[] = {
	0xc6,
	0x12,
};
#endif

/*----------------CE Sequence---------------------*/
static char CE_medium_on[] = {
	0x55,
	0x90,
};

#if 0
static char enable_orise_mode7[] = {
	0x00,
	0xa0,
};

static char CE_param1[] = {
	0xd6,
	0x01,0x00,0x01,0x00,0x01,
	0x33,0x01,0x5a,0x01,0x80,
	0x01,0x5a,
};

static char enable_orise_mode8[] = {
	0x00,
	0xb0,
};

static char CE_param2[] = {
	0xd6,
	0x01,0x26,0x01,0x5a,0x01,
	0x80,0x01,0x5a,0x01,0x26,
	0x01,0x4d,
};

static char enable_orise_mode9[] = {
	0x00,
	0xc0,
};

static char CE_param3[] = {
	0xd6,
	0x55,0x11,0x00,0x22,0x11,
	0x3c,0x55,0x11,0x3c,0x1a,
	0x11,0x3c,
};

static char enable_orise_mode10[] = {
	0x00,
	0xd0,
};

static char CE_param4[] = {
	0xd6,
	0x55,0x11,0x3c,0x1a,0x11,
	0x33,
};

static char enable_orise_mode11[] = {
	0x00,
	0xe0,
};

static char CE_param5[] = {
	0xd6,
	0x2b,0x11,0x1a,0x11,0x11,
	0x1e,0x2b,0x11,0x1e,0x0d,
	0x11,0x1e,
};

static char enable_orise_mode12[] = {
	0x00,
	0xf0,
};

static char CE_param6[] = {
	0xd6,
	0x2b,0x11,0x1e,0x0d,0x11,
	0x1a,
};

#endif
static char enable_orise_mode14[] = {
	0x00, 0x00,
};

#if 0
static char GVDD_setting[] = {
	0xd8,
	0x38, 0x38,
};

static char gamma22_Rp_setting[] = {
	0xe1,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma22_Rn_setting[] = {
	0xe2,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma22_Gp_setting[] = {
	0xe3,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma22_Gn_setting[] = {
	0xe4,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma22_Bp_setting[] = {
	0xe5,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma22_Bn_setting[] = {
	0xe6,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};
#endif
static char gamma23_Rp_setting[] = {
	0xe1,
	0x78,0x79,0x7b,0x7d,0x7f,
	0x81,0x86,0x8f,0x92,0x9a,
	0x9f,0xa3,0x5a,0x56,0x53,
	0x4a,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma23_Rn_setting[] = {
	0xe2,
	0x78,0x79,0x7b,0x7d,0x7f,
	0x81,0x86,0x8f,0x92,0x9a,
	0x9f,0xa3,0x5a,0x56,0x53,
	0x4a,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma23_Gp_setting[] = {
	0xe3,
	0x64,0x66,0x68,0x6a,0x6f,
	0x74,0x7a,0x85,0x8a,0x95,
	0x9c,0xa1,0x5c,0x59,0x56,
	0x4c,0x3c,0x33,0x2a,0x25,
	0x22,0x16,0x13,0x0F,
};

static char gamma23_Gn_setting[] = {
	0xe4,
	0x64,0x66,0x68,0x6a,0x6f,
	0x74,0x7a,0x85,0x8a,0x95,
	0x9c,0xa1,0x5c,0x59,0x56,
	0x4c,0x3c,0x33,0x2a,0x25,
	0x22,0x16,0x13,0x0F,
};

static char gamma23_Bp_setting[] = {
	0xe5,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static char gamma23_Bn_setting[] = {
	0xe6,
	0x01,0x24,0x2d,0x3b,0x45,
	0x4c,0x5a,0x6c,0x78,0x88,
	0x93,0x9a,0x60,0x5b,0x56,
	0x4c,0x3c,0x2f,0x25,0x22,
	0x19,0x16,0x13,0x0F,
};

static struct dsi_cmd_desc write_gamma23_cmds[] = {
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Rp_setting), gamma23_Rp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Rn_setting), gamma23_Rn_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Gp_setting), gamma23_Gp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Gn_setting), gamma23_Gn_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Bp_setting), gamma23_Bp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma23_Bn_setting), gamma23_Bn_setting},
};

#if 0
static char enable_orise_mode15[] = {
	0x00,
	0xC1,
};
#endif
static char enable_orise_mode16[] = {
	0x00,
	0x00,
};

static char enable_orise_mode17[] = {
	0x00,
	0x04,
};

static struct dsi_cmd_desc read_IC_version_cmds1[] = {
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode1), enable_orise_mode1},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode2), enable_orise_mode2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode3), enable_orise_mode3},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode16), enable_orise_mode16},
};

static struct dsi_cmd_desc set_scan_mode[]= {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(orise_shift_0xb4), orise_shift_0xb4},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(display_address), display_address},
};

static struct dsi_cmd_desc read_IC_version_cmds2[] = {
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode17), enable_orise_mode17},
};


static char ce_init_param1[] = {
	0xD4,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40,
	0x00, 0x40, 0x00, 0x40, 0x00, 0x41, 0x00, 0x40, 0x00, 0x42,
	0x00, 0x40, 0x00, 0x43, 0x00, 0x40, 0x00, 0x44, 0x00, 0x40,
	0x00, 0x45, 0x00, 0x40, 0x00, 0x45, 0x00, 0x40, 0x00, 0x46,
	0x00, 0x40, 0x00, 0x47, 0x00, 0x40, 0x00, 0x48, 0x00, 0x40,
	0x00, 0x49, 0x00, 0x40, 0x00, 0x4a, 0x00, 0x40, 0x00, 0x4b,
	0x00, 0x40, 0x00, 0x4b, 0x00, 0x40, 0x00, 0x4c, 0x00, 0x40,
	0x00, 0x4d, 0x00, 0x40, 0x00, 0x4e, 0x00, 0x40, 0x00, 0x4e,
	0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x50, 0x00, 0x40,
	0x00, 0x50, 0x00, 0x40, 0x00, 0x51, 0x00, 0x40, 0x00, 0x52,
	0x00, 0x40, 0x00, 0x52, 0x00, 0x40, 0x00, 0x53, 0x00, 0x40,
	0x00, 0x54, 0x00, 0x40, 0x00, 0x54, 0x00, 0x40, 0x00, 0x55,
	0x00, 0x40, 0x00, 0x55, 0x00, 0x40, 0x00, 0x56, 0x00, 0x40,
};

static char ce_init_param2[] = {
	0xD4,
	0x00, 0x57, 0x00, 0x40, 0x00, 0x57, 0x00, 0x40, 0x00, 0x58,
	0x00, 0x40, 0x00, 0x59, 0x00, 0x40, 0x00, 0x59, 0x00, 0x40,
	0x00, 0x5a, 0x00, 0x40, 0x00, 0x5b, 0x00, 0x40, 0x00, 0x5b,
	0x00, 0x40, 0x00, 0x5c, 0x00, 0x40, 0x00, 0x5c, 0x00, 0x40,
	0x00, 0x5d, 0x00, 0x40, 0x00, 0x5e, 0x00, 0x40, 0x00, 0x5e,
	0x00, 0x40, 0x00, 0x5f, 0x00, 0x40, 0x00, 0x60, 0x00, 0x40,
	0x00, 0x60, 0x00, 0x40, 0x00, 0x5f, 0x00, 0x40, 0x00, 0x5f,
	0x00, 0x40, 0x00, 0x5e, 0x00, 0x40, 0x00, 0x5d, 0x00, 0x40,
	0x00, 0x5d, 0x00, 0x40, 0x00, 0x5c, 0x00, 0x40, 0x00, 0x5c,
	0x00, 0x40, 0x00, 0x5b, 0x00, 0x40, 0x00, 0x5a, 0x00, 0x40,
	0x00, 0x5a, 0x00, 0x40, 0x00, 0x59, 0x00, 0x40, 0x00, 0x58,
	0x00, 0x40, 0x00, 0x58, 0x00, 0x40, 0x00, 0x57, 0x00, 0x40,
	0x00, 0x56, 0x00, 0x40, 0x00, 0x56, 0x00, 0x40, 0x00, 0x55,
	0x00, 0x40, 0x00, 0x54, 0x00, 0x40, 0x00, 0x53, 0x00, 0x40,
	0x00, 0x52, 0x00, 0x40, 0x00, 0x51, 0x00, 0x40, 0x00, 0x50,
	0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x4f, 0x00, 0x40,
	0x00, 0x4e, 0x00, 0x40, 0x00, 0x4d, 0x00, 0x40, 0x00, 0x4c,
	0x00, 0x40, 0x00, 0x4b, 0x00, 0x40, 0x00, 0x4a, 0x00, 0x40,
};

static char ce_init_param3[] = {
	0xD4,
	0x00, 0x4a, 0x00, 0x40, 0x00, 0x4b, 0x00, 0x40, 0x00, 0x4c,
	0x00, 0x40, 0x00, 0x4c, 0x00, 0x40, 0x00, 0x4d, 0x00, 0x40,
	0x00, 0x4e, 0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x50,
	0x00, 0x40, 0x00, 0x51, 0x00, 0x40, 0x00, 0x52, 0x00, 0x40,
	0x00, 0x53, 0x00, 0x40, 0x00, 0x53, 0x00, 0x40, 0x00, 0x54,
	0x00, 0x40, 0x00, 0x55, 0x00, 0x40, 0x00, 0x56, 0x00, 0x40,
	0x00, 0x57, 0x00, 0x40, 0x00, 0x57, 0x00, 0x40, 0x00, 0x58,
	0x00, 0x40, 0x00, 0x59, 0x00, 0x40, 0x00, 0x59, 0x00, 0x40,
	0x00, 0x5a, 0x00, 0x40, 0x00, 0x5b, 0x00, 0x40, 0x00, 0x5b,
	0x00, 0x40, 0x00, 0x5c, 0x00, 0x40, 0x00, 0x5c, 0x00, 0x40,
	0x00, 0x5d, 0x00, 0x40, 0x00, 0x5e, 0x00, 0x40, 0x00, 0x5e,
	0x00, 0x40, 0x00, 0x5f, 0x00, 0x40, 0x00, 0x60, 0x00, 0x40,
	0x00, 0x60, 0x00, 0x40, 0x00, 0x5f, 0x00, 0x40, 0x00, 0x5f,
	0x00, 0x40, 0x00, 0x5e, 0x00, 0x40, 0x00, 0x5d, 0x00, 0x40,
	0x00, 0x5d, 0x00, 0x40, 0x00, 0x5c, 0x00, 0x40, 0x00, 0x5c,
	0x00, 0x40, 0x00, 0x5b, 0x00, 0x40, 0x00, 0x5a, 0x00, 0x40,
	0x00, 0x5a, 0x00, 0x40, 0x00, 0x59, 0x00, 0x40, 0x00, 0x58,
	0x00, 0x40, 0x00, 0x58, 0x00, 0x40, 0x00, 0x57, 0x00, 0x40,
};

static char ce_init_param4[] = {
	0xD4,
	0x00, 0x56, 0x00, 0x40, 0x00, 0x56, 0x00, 0x40, 0x00, 0x55,
	0x00, 0x40, 0x00, 0x54, 0x00, 0x40, 0x00, 0x53, 0x00, 0x40,
	0x00, 0x52, 0x00, 0x40, 0x00, 0x51, 0x00, 0x40, 0x00, 0x50,
	0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x4f, 0x00, 0x40,
	0x00, 0x4e, 0x00, 0x40, 0x00, 0x4d, 0x00, 0x40, 0x00, 0x4c,
	0x00, 0x40, 0x00, 0x4b, 0x00, 0x40, 0x00, 0x4a, 0x00, 0x40,
	0x00, 0x4a, 0x00, 0x40, 0x00, 0x4a, 0x00, 0x40, 0x00, 0x4b,
	0x00, 0x40, 0x00, 0x4c, 0x00, 0x40, 0x00, 0x4c, 0x00, 0x40,
	0x00, 0x4d, 0x00, 0x40, 0x00, 0x4e, 0x00, 0x40, 0x00, 0x4e,
	0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x50, 0x00, 0x40,
	0x00, 0x50, 0x00, 0x40, 0x00, 0x51, 0x00, 0x40, 0x00, 0x52,
	0x00, 0x40, 0x00, 0x52, 0x00, 0x40, 0x00, 0x53, 0x00, 0x40,
	0x00, 0x53, 0x00, 0x40, 0x00, 0x52, 0x00, 0x40, 0x00, 0x51,
	0x00, 0x40, 0x00, 0x4f, 0x00, 0x40, 0x00, 0x4e, 0x00, 0x40,
	0x00, 0x4d, 0x00, 0x40, 0x00, 0x4b, 0x00, 0x40, 0x00, 0x4a,
	0x00, 0x40, 0x00, 0x49, 0x00, 0x40, 0x00, 0x47, 0x00, 0x40,
	0x00, 0x46, 0x00, 0x40, 0x00, 0x45, 0x00, 0x40, 0x00, 0x44,
	0x00, 0x40, 0x00, 0x42, 0x00, 0x40, 0x00, 0x41, 0x00, 0x40,
};

static char ce_init_param5[] = {
	0xD5,
	0x00, 0x55, 0x00, 0x4b, 0x00, 0x54, 0x00, 0x4b, 0x00, 0x52,
	0x00, 0x4a, 0x00, 0x51, 0x00, 0x4a, 0x00, 0x4f, 0x00, 0x4a,
	0x00, 0x4e, 0x00, 0x49, 0x00, 0x4c, 0x00, 0x49, 0x00, 0x4b,
	0x00, 0x49, 0x00, 0x4a, 0x00, 0x49, 0x00, 0x48, 0x00, 0x48,
	0x00, 0x47, 0x00, 0x48, 0x00, 0x45, 0x00, 0x48, 0x00, 0x44,
	0x00, 0x47, 0x00, 0x43, 0x00, 0x47, 0x00, 0x41, 0x00, 0x47,
	0x00, 0x40, 0x00, 0x47, 0x00, 0x41, 0x00, 0x46, 0x00, 0x41,
	0x00, 0x46, 0x00, 0x42, 0x00, 0x46, 0x00, 0x43, 0x00, 0x46,
	0x00, 0x43, 0x00, 0x46, 0x00, 0x44, 0x00, 0x46, 0x00, 0x44,
	0x00, 0x46, 0x00, 0x45, 0x00, 0x45, 0x00, 0x45, 0x00, 0x45,
	0x00, 0x46, 0x00, 0x45, 0x00, 0x47, 0x00, 0x45, 0x00, 0x47,
	0x00, 0x45, 0x00, 0x48, 0x00, 0x45, 0x00, 0x48, 0x00, 0x44,
	0x00, 0x49, 0x00, 0x44, 0x00, 0x49, 0x00, 0x45, 0x00, 0x4a,
	0x00, 0x45, 0x00, 0x4a, 0x00, 0x45, 0x00, 0x4a, 0x00, 0x45,
	0x00, 0x4b, 0x00, 0x46, 0x00, 0x4b, 0x00, 0x46, 0x00, 0x4c,
	0x00, 0x46, 0x00, 0x4c, 0x00, 0x46, 0x00, 0x4d, 0x00, 0x46,
	0x00, 0x4d, 0x00, 0x47, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4e,
	0x00, 0x47, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4f, 0x00, 0x47,
};

static char ce_init_param6[] = {
	0xD5,
	0x00, 0x4f, 0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x50,
	0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x51, 0x00, 0x49,
	0x00, 0x51, 0x00, 0x49, 0x00, 0x52, 0x00, 0x49, 0x00, 0x52,
	0x00, 0x49, 0x00, 0x53, 0x00, 0x49, 0x00, 0x53, 0x00, 0x4a,
	0x00, 0x53, 0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a, 0x00, 0x54,
	0x00, 0x4a, 0x00, 0x55, 0x00, 0x4a, 0x00, 0x55, 0x00, 0x4b,
	0x00, 0x55, 0x00, 0x4b, 0x00, 0x55, 0x00, 0x4b, 0x00, 0x54,
	0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a,
	0x00, 0x53, 0x00, 0x4a, 0x00, 0x53, 0x00, 0x4a, 0x00, 0x52,
	0x00, 0x49, 0x00, 0x52, 0x00, 0x49, 0x00, 0x52, 0x00, 0x49,
	0x00, 0x51, 0x00, 0x49, 0x00, 0x51, 0x00, 0x48, 0x00, 0x50,
	0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x4f, 0x00, 0x48,
	0x00, 0x4f, 0x00, 0x48, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4e,
	0x00, 0x47, 0x00, 0x4d, 0x00, 0x47, 0x00, 0x4d, 0x00, 0x46,
	0x00, 0x4c, 0x00, 0x46, 0x00, 0x4c, 0x00, 0x46, 0x00, 0x4b,
	0x00, 0x46, 0x00, 0x4a, 0x00, 0x45, 0x00, 0x4a, 0x00, 0x45,
	0x00, 0x49, 0x00, 0x45, 0x00, 0x49, 0x00, 0x44, 0x00, 0x48,
	0x00, 0x44, 0x00, 0x48, 0x00, 0x44, 0x00, 0x47, 0x00, 0x44,
};

static char ce_init_param7[] = {
	0xD5,
	0x00, 0x47, 0x00, 0x43, 0x00, 0x47, 0x00, 0x44, 0x00, 0x48,
	0x00, 0x44, 0x00, 0x48, 0x00, 0x44, 0x00, 0x49, 0x00, 0x45,
	0x00, 0x4a, 0x00, 0x45, 0x00, 0x4a, 0x00, 0x45, 0x00, 0x4b,
	0x00, 0x45, 0x00, 0x4b, 0x00, 0x46, 0x00, 0x4c, 0x00, 0x46,
	0x00, 0x4c, 0x00, 0x46, 0x00, 0x4d, 0x00, 0x47, 0x00, 0x4e,
	0x00, 0x47, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4f, 0x00, 0x47,
	0x00, 0x4f, 0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x50,
	0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x51, 0x00, 0x49,
	0x00, 0x51, 0x00, 0x49, 0x00, 0x52, 0x00, 0x49, 0x00, 0x52,
	0x00, 0x49, 0x00, 0x53, 0x00, 0x49, 0x00, 0x53, 0x00, 0x4a,
	0x00, 0x53, 0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a, 0x00, 0x54,
	0x00, 0x4a, 0x00, 0x55, 0x00, 0x4a, 0x00, 0x55, 0x00, 0x4b,
	0x00, 0x55, 0x00, 0x4b, 0x00, 0x55, 0x00, 0x4b, 0x00, 0x54,
	0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a,
	0x00, 0x53, 0x00, 0x4a, 0x00, 0x53, 0x00, 0x4a, 0x00, 0x52,
	0x00, 0x49, 0x00, 0x52, 0x00, 0x49, 0x00, 0x52, 0x00, 0x49,
	0x00, 0x51, 0x00, 0x49, 0x00, 0x51, 0x00, 0x48, 0x00, 0x50,
	0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x4f, 0x00, 0x48,
};

static char ce_init_param8[] = {
	0xD5,
	0x00, 0x4f, 0x00, 0x48, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4e,
	0x00, 0x47, 0x00, 0x4d, 0x00, 0x47, 0x00, 0x4d, 0x00, 0x46,
	0x00, 0x4c, 0x00, 0x46, 0x00, 0x4c, 0x00, 0x46, 0x00, 0x4b,
	0x00, 0x46, 0x00, 0x4a, 0x00, 0x45, 0x00, 0x4a, 0x00, 0x45,
	0x00, 0x49, 0x00, 0x45, 0x00, 0x49, 0x00, 0x44, 0x00, 0x48,
	0x00, 0x44, 0x00, 0x48, 0x00, 0x44, 0x00, 0x47, 0x00, 0x44,
	0x00, 0x47, 0x00, 0x43, 0x00, 0x47, 0x00, 0x44, 0x00, 0x48,
	0x00, 0x44, 0x00, 0x48, 0x00, 0x44, 0x00, 0x48, 0x00, 0x44,
	0x00, 0x49, 0x00, 0x45, 0x00, 0x49, 0x00, 0x45, 0x00, 0x4a,
	0x00, 0x45, 0x00, 0x4a, 0x00, 0x45, 0x00, 0x4a, 0x00, 0x45,
	0x00, 0x4b, 0x00, 0x46, 0x00, 0x4b, 0x00, 0x46, 0x00, 0x4c,
	0x00, 0x46, 0x00, 0x4c, 0x00, 0x46, 0x00, 0x4d, 0x00, 0x46,
	0x00, 0x4d, 0x00, 0x47, 0x00, 0x4e, 0x00, 0x47, 0x00, 0x4e,
	0x00, 0x47, 0x00, 0x4f, 0x00, 0x48, 0x00, 0x4f, 0x00, 0x48,
	0x00, 0x50, 0x00, 0x48, 0x00, 0x50, 0x00, 0x48, 0x00, 0x51,
	0x00, 0x49, 0x00, 0x52, 0x00, 0x49, 0x00, 0x52, 0x00, 0x49,
	0x00, 0x53, 0x00, 0x4a, 0x00, 0x53, 0x00, 0x4a, 0x00, 0x54,
	0x00, 0x4a, 0x00, 0x54, 0x00, 0x4a, 0x00, 0x55, 0x00, 0x4b,
};

#if 0
static struct dsi_cmd_desc cmi_video_on_v3_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_level), bl_level},

	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable_noDimming), bl_enable_noDimming},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(all_pixels_off), all_pixels_off},

	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},

	{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_MS,
		sizeof(normal_display_on), normal_display_on},

	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode1), enable_orise_mode1},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode2), enable_orise_mode2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode3), enable_orise_mode3},

	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param1), ce_init_param1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param2), ce_init_param2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param3), ce_init_param3},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param4), ce_init_param4},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param5), ce_init_param5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param6), ce_init_param6},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param7), ce_init_param7},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param8), ce_init_param8},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CE_medium_on), CE_medium_on},

	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode4), enable_orise_mode4},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(disable_per_charge), disable_per_charge},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl1), set_vgl1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl2), set_vgl2},

	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(P_DRV_M1), P_DRV_M1},

	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(P_DRV_M2), P_DRV_M2},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL1), bl_PWM_CTRL1},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL3), bl_PWM_CTRL3},

	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},

	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(GVDD_setting), GVDD_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Rp_setting), gamma22_Rp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Rn_setting), gamma22_Rn_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Gp_setting), gamma22_Gp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Gn_setting), gamma22_Gn_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Bp_setting), gamma22_Bp_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode14), enable_orise_mode14},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(gamma22_Bn_setting), gamma22_Bn_setting},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(Delay_TE), Delay_TE},

	{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
};
#endif

static struct dsi_cmd_desc cmi_display_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_level), bl_level},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(all_pixels_off), all_pixels_off},
	{DTYPE_DCS_WRITE1, 0, 10, WAIT_TYPE_US,
		sizeof(bl_enable_noDimming), bl_enable_noDimming},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(te_enable), te_enable},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode1), enable_orise_mode1},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode2), enable_orise_mode2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode3), enable_orise_mode3},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param1), ce_init_param1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param2), ce_init_param2},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param3), ce_init_param3},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param4), ce_init_param4},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param5), ce_init_param5},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param6), ce_init_param6},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param7), ce_init_param7},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(ce_init_param8), ce_init_param8},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CE_medium_on), CE_medium_on},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(enable_orise_mode4), enable_orise_mode4},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(disable_per_charge), disable_per_charge},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl1), set_vgl1},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(set_vgl2), set_vgl2},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(P_DRV_M1), P_DRV_M1},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(P_DRV_M2), P_DRV_M2},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL1), bl_PWM_CTRL1},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(bl_PWM_CTRL2), bl_PWM_CTRL2},
	{DTYPE_DCS_WRITE, 0, 150, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},

#ifdef RGV_INV_ENABLE

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_ON1), Gen_write_RGB_INV_ON1},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_ON2), Gen_write_RGB_INV_ON2},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_ON3), Gen_write_RGB_INV_ON3},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(RGB_INV0), RGB_INV0},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(RGB_INV1), RGB_INV1},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_OFF1), Gen_write_RGB_INV_OFF1},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_OFF2), Gen_write_RGB_INV_OFF2},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_OFF3), Gen_write_RGB_INV_OFF3},

	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(Gen_write_RGB_INV_OFF4), Gen_write_RGB_INV_OFF4},

#endif
    {DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(Delay_TE), Delay_TE},
	{DTYPE_DCS_WRITE, 0, 10, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
	/* the precharge_ref1 and precharge_ref2 is used for disable precharge,
	if only use 'disable_per_charge' the function may not take effect,
	and it must add after display_on(0x29) */
    {DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(precharge_ref1), precharge_ref1},
	{DTYPE_GEN_WRITE2, 0, 200, WAIT_TYPE_US,
		sizeof(precharge_ref2), precharge_ref2},
};

static struct dsi_cmd_desc cmi_display_off_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_level_0), bl_level_0},
	{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
		sizeof(all_pixels_off), all_pixels_off},
	{DTYPE_DCS_WRITE, 0, 30, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 80, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
};

#if 0
static struct dsi_cmd_desc cmi_get_chip_id_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(get_chip_id), get_chip_id}
};

static struct dsi_cmd_desc cmi_cabc_cmds[] = {
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

static struct dsi_cmd_desc cmi_cabc_ui_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_UI_MODE), CABC_UI_MODE},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_UI_curve), CABC_UI_curve},
};

static struct dsi_cmd_desc cmi_cabc_still_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_STILL_MODE), CABC_STILL_MODE},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_STILL_curve), CABC_STILL_curve},
};

static struct dsi_cmd_desc cmi_cabc_vid_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_VID_MODE), CABC_VID_MODE},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(CABC_VID_curve), CABC_VID_curve},
};
#endif
/*
static struct dsi_cmd_desc cmi_ce_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode7), enable_orise_mode7},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param1), CE_param1},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode8), enable_orise_mode8},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param2), CE_param2},				
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode9), enable_orise_mode9},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param3), CE_param3},		
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode10), enable_orise_mode10},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param4), CE_param4},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode11), enable_orise_mode11},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param5), CE_param5},				
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode12), enable_orise_mode12},
	{DTYPE_GEN_LWRITE, 0, 200, WAIT_TYPE_US,
		sizeof(CE_param6), CE_param6},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(enable_orise_mode5), enable_orise_mode5},
};

static struct dsi_cmd_desc cmi_ce_on_cmds[] = {
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(CE_medium_on), CE_medium_on},	
};
*/

/*******************************************************************************
** LCD VCC
*/
#define SYNAPTICS_VBUS_LCD LCD_IO_VDD

//lcd vddio
static int lcd_vddio_get(struct platform_device *pdev)
{
	BUG_ON(pdev==NULL);

	g_panel_platform_data->lcd_vddio = regulator_get(&pdev->dev,SYNAPTICS_VBUS_LCD);
	if (IS_ERR(g_panel_platform_data->lcd_vddio)) {
		printk( "%s: failed to get regulator lcd vddio\n", __func__);
		return -EINVAL;
	}
	return 0;
}

static int lcd_vddio_put(void)
{
	if (IS_ERR(g_panel_platform_data->lcd_vddio)) {
		printk( "%s: failed to put regulator lcd vddio\n", __func__);
		return -EINVAL;
	}
	regulator_put(g_panel_platform_data->lcd_vddio);
	return 0;
}

static int lcd_vddio_enable(void)
{
	int error;
	if (IS_ERR(g_panel_platform_data->lcd_vddio)) {
		printk( "%s: failed to enable regulator lcd vddio 1\n", __func__);
		return -EINVAL;
	}
	error = regulator_enable(g_panel_platform_data->lcd_vddio);
	if (error < 0) {
		printk( "%s: failed to enable regulator lcd vddio 2\n", __func__);
		return -EINVAL;
	}
	return 0;
}

static int lcd_vddio_disable(void)
{
	int error;
	if (IS_ERR(g_panel_platform_data->lcd_vddio)) {
		printk( "%s: failed to disable regulator lcd vddio 1\n", __func__);
		return -EINVAL;
	}

	error = regulator_disable(g_panel_platform_data->lcd_vddio);
	if (error < 0) {
		printk( "%s: failed to disable regulator lcd vddio 2\n", __func__);
		return -EINVAL;
	}
	return 0;
}

/*******************************************************************************
** LCD IOMUX
*/
static int lcd_iomux_get(void)
{
	g_panel_platform_data->lcd_gpio_block = iomux_get_block(IOMUX_LCD_NAME);
	if (!g_panel_platform_data->lcd_gpio_block) {
		k3fb_loge("failed to get iomux_lcd!\n");
		return PTR_ERR(g_panel_platform_data->lcd_gpio_block);
	}

	g_panel_platform_data->lcd_gpio_block_config = iomux_get_blockconfig(IOMUX_LCD_NAME);
	if (!g_panel_platform_data->lcd_gpio_block_config) {
		k3fb_loge("failed to get iomux_lcd config!\n");
		return PTR_ERR(g_panel_platform_data->lcd_gpio_block_config);
	}

	return 0;
}

static void lcd_iomux_set(int mode)
{
	if (blockmux_set(g_panel_platform_data->lcd_gpio_block, g_panel_platform_data->lcd_gpio_block_config, mode) != 0) {
		k3fb_loge("failed to set iomux_lcd normal mode!\n");
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
		k3fb_loge("failed to get gpio resource:%s!\n", name);
		return -1;
	}

	gpio = res->start;
	if (!gpio_is_valid(gpio)) {
		k3fb_loge("gpio %d for %s is invalid.", gpio, name);
		return -1;
	}
	k3fb_loge("gpio %d for %s is valid.", gpio, name);
	return gpio;
}

static void lcd_gpio_request(void)
{
	if (gpio_request(g_panel_platform_data->lcd_gpio_reset, GPIO_LCD_RESET_NAME) != 0) {
		k3fb_loge("failed to request gpio reset!\n");
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_id0, GPIO_LCD_ID0_NAME) != 0) {
		k3fb_loge("failed to request gpio_lcd_id0!\n");
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_id1, GPIO_LCD_ID1_NAME) != 0) {
		k3fb_loge("failed to request gpio_lcd_id1!\n");
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_enp, GPIO_LCD_ENP_NAME) != 0){
	    k3fb_loge("failed to request enp!\n");
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_enn, GPIO_LCD_ENN_NAME) != 0){
	    k3fb_loge("failed to request enn!\n");
	}

	if (gpio_request(g_panel_platform_data->lcd_gpio_pwm_en, GPIO_LCD_PWM_NAME) != 0){
	    k3fb_loge("failed to request pwm name!\n");
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

#if 0
static int set_iomux_init(char *block_name,struct iomux_block **gpio_block,struct block_config **gpio_block_config)
{
	int ret = 0;

	BUG_ON(block_name==NULL);
	BUG_ON(gpio_block==NULL);
	BUG_ON(gpio_block_config==NULL);

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


static int set_iomux_normal(struct iomux_block *gpio_block,struct block_config *gpio_block_config)
{
	int ret;

	BUG_ON(gpio_block_config==NULL);
	BUG_ON(gpio_block==NULL);

	ret = blockmux_set(gpio_block, gpio_block_config, NORMAL);
	if (ret<0) {
		printk(KERN_ERR "%s: failed to config gpio\n", __func__);
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
		printk(KERN_ERR "%s: failed to config gpio\n", __func__);
		return ret;
	}

	return 0;
}  
#endif
static struct k3_fb_panel_data cmi_panel_data;

/******************************************************************************/
static struct lcd_tuning_dev *p_tuning_dev = NULL;
static int cabc_mode = 1; /* allow application to set cabc mode to ui mode */

static int cmi_set_gamma(struct lcd_tuning_dev *ltd, enum lcd_gamma gamma)
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

static int cmi_set_cabc(struct lcd_tuning_dev *ltd, enum  tft_cabc cabc)
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

static unsigned int g_csc_value[9];
static unsigned int g_is_csc_set;
static struct semaphore ct_sem;

static void cmi_store_ct_cscValue(unsigned int csc_value[])
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

static int cmi_set_ct_cscValue(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	edc_base = k3fd->edc_base;
	down(&ct_sem);
	if (1 == g_is_csc_set) {
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

static int cmi_set_color_temperature(struct lcd_tuning_dev *ltd, unsigned int csc_value[])
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

	cmi_store_ct_cscValue(csc_value);
	flag = cmi_set_ct_cscValue(k3fd);
	return flag;

}

static struct lcd_tuning_ops sp_tuning_ops = {
	.set_gamma = cmi_set_gamma,
	.set_cabc = cmi_set_cabc,
	.set_color_temperature = cmi_set_color_temperature,
};

static ssize_t cmi_lcd_info_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct k3_panel_info *pinfo = NULL;

	pinfo = cmi_panel_data.panel_info;
	snprintf(buf, PAGE_SIZE, "cmi_OTM1282B 6.1' CMD TFT %d x %d\n",
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
		cmi_set_cabc(p_tuning_dev, CABC_UI);
	} else if (val == 2) {
		/* force cabc mode to video mode */
		cabc_mode =2;
		cmi_set_cabc(p_tuning_dev, CABC_VID);
	}

	return sprintf((char *)buf, "%d\n", cabc_mode);
}

static ssize_t cmi_frame_count_show(struct device *dev,
       struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%u\n", frame_count);
}

static DEVICE_ATTR(lcd_info, S_IRUGO, cmi_lcd_info_show, NULL);
static DEVICE_ATTR(cabc_mode, 0644, show_cabc_mode, store_cabc_mode);
static DEVICE_ATTR(frame_count, S_IRUGO, cmi_frame_count_show, NULL);

static struct attribute *cmi_attrs[] = {
	&dev_attr_lcd_info.attr,
	&dev_attr_cabc_mode.attr,
	&dev_attr_frame_count.attr,
	NULL,
};

static struct attribute_group cmi_attr_group = {
	.attrs = cmi_attrs,
};

static int cmi_sysfs_init(struct platform_device *pdev)
{
	int ret = 0;
	ret = sysfs_create_group(&pdev->dev.kobj, &cmi_attr_group);
	if (ret) {
		k3fb_loge("create sysfs file failed!\n");
		return ret;
	}
	return 0;
}

static void cmi_sysfs_deinit(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &cmi_attr_group);
}

static void cmi_disp_on_send_sequence(struct k3_fb_data_type *k3fd)
{
	int read_loop = 0;
	u32 scan_mode, temp =99;

	mipi_dsi_cmds_tx(read_IC_version_cmds1, ARRAY_SIZE(read_IC_version_cmds1));

	outp32(k3fd->dsi_base+ MIPIDSI_GEN_HDR_ADDR, (0xd1) << 8 | 0x14);
	mdelay(1);
	mipi_dsi_wait_and_read(k3fd, &temp, WAIT_TYPE_US, 10);
	printk("ID2 =%d\n",temp);

	if (temp == 0x00) {
		mipi_dsi_cmds_tx(read_IC_version_cmds2, ARRAY_SIZE(read_IC_version_cmds2));

		outp32(k3fd->dsi_base+ MIPIDSI_GEN_HDR_ADDR, (0xf8) << 8 | 0x14);
		mdelay(1);

		mipi_dsi_wait_and_read(k3fd, &temp, WAIT_TYPE_US, 10);
		printk("ic =%d\n", temp);
		if(temp == 0x01) {
			mipi_dsi_cmds_tx(write_gamma23_cmds, \
			ARRAY_SIZE(write_gamma23_cmds));
		}
	}

	mipi_dsi_cmds_tx(cmi_display_on_cmds, ARRAY_SIZE(cmi_display_on_cmds));

	for (read_loop = 0; read_loop < 3; read_loop++) {
		outp32(k3fd->dsi_base + MIPIDSI_GEN_HDR_ADDR, 0xb40023);
		udelay(200);
		outp32(k3fd->dsi_base + MIPIDSI_GEN_HDR_ADDR, (0xc0) << 8 | 0x06);
		udelay(200);
		mipi_dsi_wait_and_read(k3fd, &scan_mode, WAIT_TYPE_US, 10);
		udelay(200);
		printk("\n\n-----scan_mode =0x%2x-----\n\n", scan_mode);
		if (scan_mode == 0x10)
			break;

		mipi_dsi_cmds_tx(set_scan_mode, ARRAY_SIZE(set_scan_mode));
	}
}

#ifdef CONFIG_FB_CHECK_MIPI_TR
static int mipi_cmi_check_mipi_tr(struct platform_device *pdev)
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
		goto cmi_check_mipi_tr_error;
	}

	//read 0x0b
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0b << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x00 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0b success:%d, 0x0b value = 0x%x\n", __func__, ret, read_value);
		goto cmi_check_mipi_tr_error;
	}

	//read 0x0c
	read_value = 0;
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0c << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x07 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0c success:%d, 0x0c value = 0x%x\n", __func__, ret, read_value);
		goto cmi_check_mipi_tr_error;
	}

	//read 0x0d
	read_value = 0;
	set_MIPIDSI_GEN_HDR((0x1 << 8) | 0x37);
	set_MIPIDSI_GEN_HDR((0x0d << 8) | 0x14);
	ret = mipi_dsi_wait_and_read(k3fd, &read_value, WAIT_TYPE_MS, 1);
	if (ret || (0x00 != (read_value&0xFF))) {
		err = 1;
		pr_info("%s read 0x0d success:%d, 0x0d value = 0x%x\n", __func__, ret, read_value);
		goto cmi_check_mipi_tr_error;
	}

cmi_check_mipi_tr_error:
	return err;
}
#endif

#ifdef CONFIG_FB_MIPI_DETECT
static int mipi_cmi_panel_mipi_detect(struct platform_device *pdev)
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

static int mipi_cmi_set_inversion_type(struct platform_device *pdev, unsigned int inversion_mode)
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

static int mipi_cmi_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	u32 edc_base = 0;

	BUG_ON(pdev == NULL);

	pr_info("%s enter succ!\n",__func__);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
    
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);
	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		if (!g_display_on) {
			lcd_vddio_enable();
			lcd_iomux_set(NORMAL);
			lcd_gpio_request();

			mdelay(4);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_pwm_en, 1);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 1);
			mdelay(10);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_enp, 1);
			mdelay(3);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_enn, 1);
			mdelay(10);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 0);
			mdelay(10);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 1);
			mdelay(20);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 0);
			mdelay(5);
			gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 1);
			mdelay(20);

			pinfo->lcd_init_step = LCD_INIT_SEND_SEQUENCE;
		}
        
	} else if (pinfo->lcd_init_step == LCD_INIT_SEND_SEQUENCE) {
		if (!g_display_on) {
			cmi_set_ct_cscValue(k3fd);
			/* lcd display on sequence */
			cmi_disp_on_send_sequence(k3fd);
			//mipi_dsi_cmds_tx(cmi_cabc_cmds, ARRAY_SIZE(cmi_cabc_cmds));
			g_display_on = true;
			backlight_log_once = true;
		}
	} else {
		k3fb_loge("failed to init lcd!\n");
	}
    
	return 0;
}

static int mipi_cmi_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	u32 edc_base = 0;
    
	BUG_ON(pdev == NULL);
	pr_info("%s enter succ!\n",__func__);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);
    
#ifdef CONFIG_DEBUG_FS
	if ((g_fb_lowpower_debug_flag & DEBUG_LCD_LOWPOWER_DISABLE) == DEBUG_LCD_LOWPOWER_DISABLE) {
		k3fb_logi(" lcd off was disable");
		return 0;
	}
#endif
	if (g_display_on) {
		g_display_on = false;
		mipi_dsi_cmds_tx(cmi_display_off_cmds, ARRAY_SIZE(cmi_display_off_cmds));

		gpio_direction_output(g_panel_platform_data->lcd_gpio_pwm_en, 0);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_enn, 0);
		mdelay(5);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_enp, 0);
		mdelay(1);
		gpio_direction_output(g_panel_platform_data->lcd_gpio_reset, 0);
		mdelay(1);
		lcd_gpio_free();
#ifdef CONFIG_MACH_HI6620OEM	
		lcd_iomux_set(LOWPOWER);
#endif
	    mdelay(1);
		lcd_vddio_disable();
	}

	return 0;
}

static int mipi_cmi_panel_remove(struct platform_device *pdev)
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
	lcd_vddio_put();
	cmi_sysfs_deinit(pdev);
	if (NULL != g_panel_platform_data) {
		kfree(g_panel_platform_data);
	}
	return 0;
}

static int mipi_cmi_panel_set_backlight(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	u32 level = 0;

	char bl_level_adjust[2] = {
		0x51,
		0x00,
	};

	struct dsi_cmd_desc  cmi_bl_level_adjust[] = {
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

	mipi_dsi_cmds_tx(cmi_bl_level_adjust, \
		ARRAY_SIZE(cmi_bl_level_adjust));

	if (backlight_log_once) {
		backlight_log_once = false;

		mipi_dsi_cmds_tx(jdi_normal_display_on, \
			ARRAY_SIZE(jdi_normal_display_on));

		k3fb_loge("----k3fd->bl_level=%d,set backlight to level = %d\n",k3fd->bl_level, level);
	}

	return 0;
}

static int mipi_cmi_panel_set_fastboot(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
    
	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	lcd_vddio_enable();
	lcd_iomux_set(NORMAL);
	lcd_gpio_request();

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
		PWM_GPIO_REQUEST(&(k3fd->panel_info));
	}

	g_display_on = true;

	return 0;
}

static int mipi_cmi_panel_set_cabc(struct platform_device *pdev, int value)
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

static int mipi_cmi_panel_check_esd(struct platform_device *pdev)
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

static struct k3_panel_info cmi_panel_info = {0};
static struct k3_fb_panel_data cmi_panel_data = {
	.panel_info = &cmi_panel_info,
	.on = mipi_cmi_panel_on,
	.off = mipi_cmi_panel_off,
	.remove = mipi_cmi_panel_remove,
	.set_backlight = mipi_cmi_panel_set_backlight,
	.set_fastboot = mipi_cmi_panel_set_fastboot,
	.set_cabc = mipi_cmi_panel_set_cabc,
	.check_esd = mipi_cmi_panel_check_esd,
#ifdef CONFIG_FB_CHECK_MIPI_TR
	.check_mipi_tr = mipi_cmi_check_mipi_tr,
#endif
#ifdef CONFIG_FB_SET_INVERSION
	.set_inversion_type = mipi_cmi_set_inversion_type,
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	.mipi_detect = mipi_cmi_panel_mipi_detect,
#endif
};

static int __devinit cmi_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;
	struct platform_device *reg_pdev = NULL;
	struct lcd_properities lcd_props;
	
	pr_info("%s enter succ!\n",__func__);
	g_panel_platform_data = kzalloc(sizeof(struct cmi_otm1282b_panel_data), GFP_KERNEL);
	if (NULL == g_panel_platform_data) {
		k3fb_loge("alloc driver data error\n");
		return -ENOMEM;
	}
	g_display_on = false;
	pinfo = cmi_panel_data.panel_info;

	/* init lcd panel info */
	pinfo->xres = 720;
	pinfo->yres = 1280;
	pinfo->width  = 76;  //mm
	pinfo->height = 135; //mm
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
	pinfo->sbl.cal_a = 0x08;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;

	pinfo->ldi.h_back_porch = 43;
	pinfo->ldi.h_front_porch = 97;
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
	pinfo->frame_rate = 60;
	pinfo->clk_rate = 76000000; // 72M = 1440M/20

	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;

	pinfo->mipi.dsi_bit_clk = 241;


	lcd_vddio_get(pdev);
	lcd_iomux_get();
 
	/* lcd resource */
	lcd_resource(pdev, res);
	/* alloc panel device data */
	if (platform_device_add_data(pdev, &cmi_panel_data,
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

	cmi_sysfs_init(pdev);

	pr_info("%s exit succ!\n",__func__);
	return 0;
}

static struct platform_driver this_driver = {
	.probe = cmi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_cmi_OTM1282B",
	},
};

static int __init mipi_cmi_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		k3fb_loge("not able to register the driver\n");
		return ret;
	}

	return ret;
}

module_init(mipi_cmi_panel_init);

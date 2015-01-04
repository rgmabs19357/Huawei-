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

#define PWM_LEVEL 100

#define TRUE_MIPI  1
#define FALSE_MIPI 0

static int isCabcVidMode = FALSE_MIPI;

/*----------------Power ON Sequence(sleep mode to Normal mode)---------------------*/

/* set backlight ff */
static char backlight_51[] = {
	0x51,
	0xFF,
};

/* set backlight ff */
static char backlight_53[] = {
	0x53,
	0x24,
};

static char data_ff[] = {
	0xFF,
	0xAA, 0x55, 0x25, 0x01 
};

static char data_f5[] = {
	0xF5,
	0x00, 0x00
};

/* set page0 */
static char data_page0[] = {
	0xF0,
	0x55, 0xAA, 0x52, 0x08, 0x00
};

static char data_page0_c7[] = {
        0xC7,
        0x70
};

static char data_page0_ca[] = {
	0xCA,
	0x00, 0x1B, 0x1B, 0x1B, 0x1B,
	0x1B, 0x1B, 0x02, 0x02, 0x00,
	0x00
};

static char data_page0_ba[] = {
	0xBA,
	0x05
};

static char data_page0_c9[] = {
	0xC9,
	0x41, 0x06, 0x0d, 0x3a, 0x17,
	0x00
};

static char data_page0_b1[] = {
	0xB1,
	0xFC, 0x06, 0x00
};

static char data_page0_bc[] = {
	0xBC,
	0x00, 0x00, 0x00
};

static char data_page0_b7[] = {
	0xB7,
	0x72, 0x22
};

static char data_page0_b8[] = {
	0xB8,
	0x01, 0x02, 0x02, 0x00
};

static char data_page0_bb[] = {
	0xBB,
	0x53, 0x03, 0x53
};

static char data_page0_bd[] = {
	0xBD,
	0x01, 0x69, 0x05, 0x05, 0x01
};

static char data_page0_b6[] = {
	0xB6,
	0x0B
};

static char data_page0_3a[] = {
	0x3A,
	0x77
};

static char data_page0_36[] = {
	0x36,
	0x00
};

/* set page1 */
static char data_page1[] = {
	0xF0,
	0x55, 0xAA, 0x52, 0x08, 0x01
};

static char data_page1_b0[] = {
	0xB0,
	0x0A
};

static char data_page1_b6[] = {
	0xB6,
	0x54
};

static char data_page1_b1[] = {
	0xB1,
	0x0A
};

static char data_page1_b7[] = {
	0xB7,
	0x34
};

static char data_page1_b2[] = {
	0xB2,
	0x00
};

static char data_page1_b8[] = {
	0xB8,
	0x30
};

static char data_page1_b3[] = {
	0xB3,
	0x0D
};

static char data_page1_b9[] = {
	0xB9,
	0x24
};

static char data_page1_b4[] = {
	0xB4,
	0x08
};

static char data_page1_ba[] = {
	0xBA,
	0x14
};

static char data_page1_bc[] = {
	0xBC,
	0x00, 0x78, 0x00
};

static char data_page1_bd[] = {
	0xBD,
	0x00, 0x78, 0x00
};

static char data_page1_36[] = {
	0x36,
	0x00
};

static char data_page1_35[] = {
	0x35,
	0x00
};

static char data_page1_44[] = {
	0x44,
	0x01, 0xE0
};

static char enter_sleep[] = {
	0x10,
};

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};

static char display_off[] = {
	0x28,
};

static struct dsi_cmd_desc cmi_video_on_cmds[] = {

        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_ff), data_ff},
        {DTYPE_GEN_LWRITE, 0, 30, WAIT_TYPE_US,
                sizeof(data_f5), data_f5},

        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0), data_page0},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_c7), data_page0_c7},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_ca), data_page0_ca},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_ba), data_page0_ba},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_c9), data_page0_c9},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_b1), data_page0_b1},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_bc), data_page0_bc},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_b7), data_page0_b7},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_b8), data_page0_b8},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_bb), data_page0_bb},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_bd), data_page0_bd},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_b6), data_page0_b6},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_3a), data_page0_3a},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page0_36), data_page0_36},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1), data_page1},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b0), data_page1_b0},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b6), data_page1_b6},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b1), data_page1_b1},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b7), data_page1_b7},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b2), data_page1_b2},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b8), data_page1_b8},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b3), data_page1_b3},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b9), data_page1_b9},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_b4), data_page1_b4},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_ba), data_page1_ba},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_bc), data_page1_bc},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_bd), data_page1_bd},
        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_36), data_page1_36},

        {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_35), data_page1_35},
        {DTYPE_GEN_LWRITE, 0, 3000, WAIT_TYPE_US,
                sizeof(data_page1_44), data_page1_44},

       {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
                sizeof(backlight_51), backlight_51},

      {DTYPE_GEN_WRITE2, 0, 3000, WAIT_TYPE_US,
              sizeof(backlight_53), backlight_53},

        {DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
                sizeof(exit_sleep), exit_sleep},

        {DTYPE_DCS_WRITE, 0, 5, WAIT_TYPE_MS,
                sizeof(display_on), display_on},
};

/*-------------------Power OFF Sequence(Normal to power off)----------------------*/
static struct dsi_cmd_desc cmi_display_off_cmds[] = {
        {DTYPE_DCS_WRITE, 0, 5, WAIT_TYPE_MS,
                sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 80, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
};

static struct k3_fb_panel_data cmi_panel_data;


/******************************************************************************/
static ssize_t cmi_lcd_info_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct k3_panel_info *pinfo;
	pinfo = cmi_panel_data.panel_info;
	sprintf(buf, "CHIMEI_Innolux 4.5'TFT %d x %d\n",
		pinfo->xres, pinfo->yres);
	ret = strlen(buf) + 1;
	return ret;
}
static struct lcd_tuning_dev *p_tuning_dev = NULL;
static int cabc_mode = 1;	//allow application to set cabc mode to ui mode
static ssize_t show_cabc_mode(struct device *dev,
        struct device_attribute *attr,
        char *buf)
{
	return sprintf(buf, "%d\n", cabc_mode);
}
static int cmi_set_cabc(struct lcd_tuning_dev *ltd, enum tft_cabc cabc);
static ssize_t store_cabc_mode(struct device *dev,
        struct device_attribute *attr,
        char *buf)
{
	return 0;
}

static DEVICE_ATTR(lcd_info, S_IRUGO, cmi_lcd_info_show, NULL);
static DEVICE_ATTR(cabc_mode, 0644, show_cabc_mode, store_cabc_mode);
static struct attribute *cmi_attrs[] = {
	&dev_attr_lcd_info,
	&dev_attr_cabc_mode,
	NULL,
};
static struct attribute_group cmi_attr_group = {
	.attrs = cmi_attrs,
};

static int cmi_sysfs_init(struct platform_device *pdev)
{
	int ret;
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

static int cmi_set_gamma(struct lcd_tuning_dev *ltd, enum lcd_gamma gamma)
{
	/*No implementation*/
	return 0;
}

static int cmi_set_cabc(struct lcd_tuning_dev *ltd, enum  tft_cabc cabc)
{
	/*No implementation*/
	return 0;
}

/******************************************************************************/
static int cmi_pwm_on(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	/* backlight on */
	PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
	PWM_GPIO_REQUEST(&(k3fd->panel_info));
	gpio_direction_input(k3fd->panel_info.gpio_pwm1);
	mdelay(1);
	pwm_set_backlight(k3fd->bl_level, &(k3fd->panel_info));

	return 0;
}

static int cmi_pwm_off(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	/* backlight off */
	pwm_set_backlight(0, &(k3fd->panel_info));
	gpio_direction_output(k3fd->panel_info.gpio_pwm0, 0);
	mdelay(1);
	gpio_direction_input(k3fd->panel_info.gpio_pwm1);
	mdelay(1);
	PWM_GPIO_FREE(&(k3fd->panel_info));
	PWM_IOMUX_SET(&(k3fd->panel_info), LOWPOWER);

	return 0;
}

static void cmi_disp_on(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);
	LCD_IOMUX_SET(pinfo, NORMAL);
	LCD_GPIO_REQUEST(pinfo);
	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(1);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(1);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(15);
	gpio_direction_output(pinfo->gpio_reset, 1);
	mdelay(50);

	mipi_dsi_cmds_tx(cmi_video_on_cmds, \
		ARRAY_SIZE(cmi_video_on_cmds), edc_base);

}

static void cmi_disp_off(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);

	mipi_dsi_cmds_tx(cmi_display_off_cmds,
		ARRAY_SIZE(cmi_display_off_cmds), edc_base);

	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(1);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(1);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(1);
	LCD_GPIO_FREE(pinfo);
	LCD_IOMUX_SET(pinfo, LOWPOWER);
	LCD_VCC_DISABLE(pinfo);
}

static int mipi_cmi_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	pinfo = &(k3fd->panel_info);
	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
		LCD_VCC_ENABLE(pinfo);
		pinfo->lcd_init_step = LCD_INIT_SEND_SEQUENCE;
		return 0;
	}

	if (!k3fd->panel_info.display_on) {
		/* lcd display on */
		cmi_disp_on(k3fd);
		k3fd->panel_info.display_on = true;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight on */
			cmi_pwm_on(k3fd);
		}
	}

	return 0;
}

static int mipi_cmi_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (k3fd->panel_info.display_on) {
		k3fd->panel_info.display_on = false;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight off */
			cmi_pwm_off(k3fd);
		}
		/* lcd display off */
		cmi_disp_off(k3fd);
	}

	return 0;
}

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

static int mipi_cmi_panel_set_backlight(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	u32 level = 0;

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

	/*Our eyes are more sensitive to small brightness.
	So we adjust the brightness of lcd following iphone4 */
	level = (k3fd->bl_level * square_point_six(k3fd->bl_level) * 100) / 2779;  //Y=(X/255)^1.6*255
	if (level > 255)
		level = 255;

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		return pwm_set_backlight(level, &(k3fd->panel_info));
	} else {
		//if (!k3fd->cmd_mode_refresh) {
			outp32(edc_base + MIPIDSI_GEN_HDR_OFFSET, (level << 16) | (0x51 << 8) | 0x15);
		//	k3fd->bl_level_old = k3fd->bl_level;
		//}
		return 0;
	}
}

static int mipi_cmi_panel_set_fastboot(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	LCD_VCC_ENABLE(&(k3fd->panel_info));
	LCD_IOMUX_SET(&(k3fd->panel_info), NORMAL);
	LCD_GPIO_REQUEST(&(k3fd->panel_info));

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
		PWM_GPIO_REQUEST(&(k3fd->panel_info));
	}

	k3fd->panel_info.display_on = true;

	return 0;
}

static int mipi_cmi_panel_set_cabc(struct platform_device *pdev, int value)
{
	return 0;
}

static struct k3_panel_info cmi_panel_info = {0};
static struct k3_fb_panel_data cmi_panel_data = {
	.panel_info = &cmi_panel_info,
	.on = mipi_cmi_panel_on,
	.off = mipi_cmi_panel_off,
	.set_backlight = mipi_cmi_panel_set_backlight,
	.set_fastboot = mipi_cmi_panel_set_fastboot,
	.set_cabc = NULL,//mipi_cmi_panel_set_cabc,
};

static struct lcd_tuning_ops sp_tuning_ops = {
	.set_gamma = NULL,
	.set_cabc = NULL,//cmi_set_cabc
};

static int __devinit cmi_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;
	struct platform_device *reg_pdev;
	struct lcd_tuning_dev *ltd;
	struct lcd_properities lcd_props;

	pinfo = cmi_panel_data.panel_info;
	/* init lcd panel info */
	pinfo->display_on = false;
	pinfo->xres = 540;
	pinfo->yres = 960;
	pinfo->type = PANEL_MIPI_CMD;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = EDC_OUT_RGB_888;
	pinfo->s3d_frm = EDC_FRM_FMT_2D;
	pinfo->bgr_fmt = EDC_RGB;
	pinfo->bl_set_type = BL_SET_BY_MIPI;
	pinfo->bl_max = PWM_LEVEL;
	pinfo->bl_min = 1;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 1;
	pinfo->sbl_enable = 0;

	pinfo->sbl.bl_max = 0xff;
	pinfo->sbl.cal_a = 0x0f;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;

	pinfo->ldi.h_back_porch = 16;
	pinfo->ldi.h_front_porch = 16;
	pinfo->ldi.h_pulse_width = 2;
	pinfo->ldi.v_back_porch = 2;
	pinfo->ldi.v_front_porch = 2;
	pinfo->ldi.v_pulse_width = 2;

	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 0;
	pinfo->ldi.pixelclk_plr = 1;
	pinfo->ldi.data_en_plr = 0;

	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */
	pinfo->frame_rate = 60;
	/*pinfo->clk_rate = LCD_GET_CLK_RATE(pinfo);*/
	pinfo->clk_rate = 32000000;

	pinfo->mipi.lane_nums = DSI_2_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.dsi_bit_clk = 216; /*482; clock lane(p/n) */

	/* lcd vcc */
	LCD_VCC_GET(pdev, pinfo);
	LCDIO_SET_VOLTAGE(pinfo, 1800000, 1800000);
	/* lcd iomux */
	LCD_IOMUX_GET(pinfo);
	/* lcd resource */
	LCD_RESOURCE(pdev, pinfo, res);

	if (pinfo->bl_set_type & BL_SET_BY_PWM) {
		/* pwm clock*/
		PWM_CLK_GET(pinfo);
		/* pwm iomux */
		PWM_IOMUX_GET(pinfo);
		/* pwm resource */
		PWM_RESOUTCE(pdev, pinfo, res);
	}

	/* alloc panel device data */
	if (platform_device_add_data(pdev, &cmi_panel_data,
		sizeof(struct k3_fb_panel_data))) {
		k3fb_loge("platform_device_add_data failed!\n");
		platform_device_put(pdev);
		return -ENOMEM;
	}

	reg_pdev = k3_fb_add_device(pdev);
	lcd_props.type = TFT;
	lcd_props.default_gamma = GAMMA25;

	ltd = lcd_tuning_dev_register(&lcd_props, &sp_tuning_ops, (void *)reg_pdev);
	p_tuning_dev=ltd;
	if (IS_ERR(ltd)) {
		k3fb_loge("lcd_tuning_dev_register failed!\n");
		return -1;
	}

	cmi_sysfs_init(pdev);

	return 0;
}

static int cmi_remove(struct platform_device *pdev)
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
	LCD_VCC_PUT(&(k3fd->panel_info));

	cmi_sysfs_deinit(pdev);

	return 0;
}

static void cmi_shutdown(struct platform_device *pdev)
{
	if (cmi_remove(pdev) != 0) {
		k3fb_loge("failed to shutdown!\n");
	}
}

static struct platform_driver this_driver = {
	.probe = cmi_probe,
	.remove = cmi_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = cmi_shutdown,
	.driver = {
		.name = "mipi_cmi_PT045TN07",
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

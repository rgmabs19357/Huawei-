/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of Code Aurora Forum, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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

#include "k3_fb.h"
#include "k3_fb_def.h"
#include "mipi_dsi.h"
#include "mipi_reg.h"


/*#define BOARD_HI4511MMU1_VER_B*/

#define PWM_LEVEL 100

static struct k3_fb_panel_data panasonic_panel_data;

static ssize_t panasonic_lcd_info_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct k3_panel_info *pinfo;
	pinfo = panasonic_panel_data.panel_info;
	sprintf(buf, "Panasonic_VVX10F002A00 10.1'TFT %d x %d\n",
		pinfo->xres, pinfo->yres);
	ret = strlen(buf) + 1;
	return ret;
}

static DEVICE_ATTR(lcd_info, S_IRUGO, panasonic_lcd_info_show, NULL);

static struct attribute *panasonic_attrs[] = {
	&dev_attr_lcd_info,
	NULL,
};

static struct attribute_group panasonic_attr_group = {
	.attrs = panasonic_attrs,
};

static int panasonic_sysfs_init(struct platform_device *pdev)
{
	int ret;
	ret = sysfs_create_group(&pdev->dev.kobj, &panasonic_attr_group);
	if (ret) {
		k3fb_loge("create sysfs file failed!\n");
		return ret;
	}
	return 0;
}

static void panasonic_sysfs_deinit(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &panasonic_attr_group);
}

static int panasonic_pwm_on(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);
	
	/* backlight on */
	PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
	PWM_GPIO_REQUEST(&(k3fd->panel_info));
	gpio_direction_input(k3fd->panel_info.gpio_pwm1);
	mdelay(10);
	pwm_set_backlight(k3fd->bl_level, &(k3fd->panel_info));

	return 0;
}

static int panasonic_pwm_off(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	/* backlight off */
	pwm_set_backlight(0, &(k3fd->panel_info));
	gpio_direction_output(k3fd->panel_info.gpio_pwm0, 0);
	mdelay(10);
	gpio_direction_input(k3fd->panel_info.gpio_pwm1);
	mdelay(10);
	PWM_GPIO_FREE(&(k3fd->panel_info));
	PWM_IOMUX_SET(&(k3fd->panel_info), LOWPOWER);

	return 0;
}

static void panasonic_disp_on(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);
	/* lcd vcc */
	LCD_VCC_ENABLE(pinfo);

	/* LCD */
	LCD_IOMUX_SET(pinfo, NORMAL);
	LCD_GPIO_REQUEST(pinfo);

	/* lcd gpio */
	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(10);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(10);

	gpio_direction_output(pinfo->gpio_power, 1);
	mdelay(10);


#ifdef BOARD_HI4511MMU1_VER_B
	/* GPIO_RESET (003) Used as LEN_EN  and
	 * GPIO_15_5 (125) Used as LCE_EN on BOARD HI4511MMU1 VER.B
	 */
	gpio_direction_output(pinfo->gpio_reset, 1);
	mdelay(10);

	if (gpio_request(GPIO_15_5, "LCD_EN") != 0) {
		k3fb_loge("failed to request gpio 125.\n");
	}

	gpio_direction_output(GPIO_15_5, 1);
	mdelay(10);
#endif
}

static void panasonic_disp_off(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);

	/* LCD */
	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(10);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_power, 0);
	mdelay(10);


#ifdef BOARD_HI4511MMU1_VER_B
	/* GPIO_RESET (003) Used as LEN_EN  and
	 * GPIO_15_5 (125) Used as LCD_EN on BOARD HI4511MMU1 VER.B
	 */
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(10);

	gpio_direction_output(GPIO_15_5, 0);
	gpio_free(GPIO_15_5);
	mdelay(10);
#endif
	LCD_GPIO_FREE(pinfo);
	LCD_IOMUX_SET(pinfo, LOWPOWER);

	/* lcd vcc */
	LCD_VCC_DISABLE(pinfo);
}

static int mipi_panasonic_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_info.display_on) {
		/* lcd display on */
		panasonic_disp_on(k3fd);
		k3fd->panel_info.display_on = true;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight on */
			panasonic_pwm_on(k3fd);
		}
	}

	return 0;
}

static int mipi_panasonic_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (k3fd->panel_info.display_on) {
		k3fd->panel_info.display_on = false;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight off */
			panasonic_pwm_off(k3fd);
		}
		/* lcd display off */
		panasonic_disp_off(k3fd);
	}

	return 0;
}

static int mipi_panasonic_panel_remove(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	
	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_CLK_PUT(&(k3fd->panel_info));
	}
	LCD_VCC_PUT(&(k3fd->panel_info));

	panasonic_sysfs_deinit(pdev);

	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return 0;
}

static int mipi_panasonic_panel_set_backlight(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		return pwm_set_backlight(k3fd->bl_level, &(k3fd->panel_info));
	} else {
		return 0;
	}
}

static int mipi_panasonic_panel_set_fastboot(struct platform_device *pdev)
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
static u32 g_cm_cabc_status = 0x02;


static char cmd_begin[] = {
	0xF3,
	0xA0,
};

static char cmd_cabc_cm_status[] = {
	0x0E,
	0x02,
};

static struct dsi_cmd_desc panasonic_parameter_begin = {
	.dtype = 	DTYPE_GEN_WRITE2,
	.vc        =  0,
	.wait    =  30,
	.waittype = WAIT_TYPE_US,
	.dlen         = sizeof(cmd_begin),
	.payload    = cmd_begin,
};


static struct dsi_cmd_desc panasonic_parameter = {
	.dtype = 	DTYPE_GEN_WRITE2,
	.vc        =  0,
	.wait    =  30,
	.waittype = WAIT_TYPE_US,
	.dlen         = sizeof(cmd_cabc_cm_status),
	.payload    = cmd_cabc_cm_status,
};

static struct dsi_cmd_desc panasonic_parameter_end = {
	.dtype = 	DTYPE_GEN_WRITE,
	.vc        =  0,
	.wait    =  30,
	.waittype = WAIT_TYPE_US,
	.dlen         = 0,
	.payload    = 0,
};

void  set_value(u32 *value, u32 b_val, u8 bw, u8 bs)
{
	u32 mask = (1 << bw) - 1;
	u32 tmp = *value;
	tmp &= ~(mask << bs);
	*value = tmp | (b_val & mask) << bs;
}

static int set_panasonic_function(u32 status, u32 edc_base)
{
	cmd_cabc_cm_status[1] = status;

	mipi_dsi_swrite(&panasonic_parameter_begin, edc_base);

	mipi_dsi_swrite(&panasonic_parameter, edc_base);

	mipi_dsi_swrite(&panasonic_parameter_end, edc_base);

	return 0;
}

static int mipi_panasonic_panel_set_cabc(struct platform_device *pdev, int value)
{
	u32 edc_base = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

	if (value) {
		set_value(&g_cm_cabc_status, 0x01, 1, 3);
		set_panasonic_function(g_cm_cabc_status, edc_base);
	} else {
		set_value(&g_cm_cabc_status, 0x00, 1, 3);
		set_panasonic_function(g_cm_cabc_status, edc_base);
	}

	return 0;
}

static struct k3_panel_info panasonic_panel_info = {0};
static struct k3_fb_panel_data panasonic_panel_data = {
	.panel_info = &panasonic_panel_info,
	.on = mipi_panasonic_panel_on,
	.off = mipi_panasonic_panel_off,
	.remove = mipi_panasonic_panel_remove,
	.set_backlight = mipi_panasonic_panel_set_backlight,
	.set_fastboot = mipi_panasonic_panel_set_fastboot,
	.set_cabc = mipi_panasonic_panel_set_cabc,
};

static int __devinit panasonic_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;

	pinfo = panasonic_panel_data.panel_info;

	/* init lcd panel info */
	pinfo->display_on = false;
	pinfo->xres = 1920;
	pinfo->yres = 1200;
	pinfo->width = 217;
	pinfo->height = 136;
	pinfo->type = PANEL_MIPI_VIDEO;
	pinfo->orientation = LCD_LANDSCAPE;
	pinfo->bpp = EDC_OUT_RGB_888;
	pinfo->s3d_frm = EDC_FRM_FMT_2D;
	pinfo->bgr_fmt = EDC_RGB;
	pinfo->bl_set_type = BL_SET_BY_PWM;
	pinfo->bl_max = PWM_LEVEL;
	pinfo->bl_min = 1;

	pinfo->sbl.bl_max = 0x64;
	pinfo->sbl.cal_a = 0x18;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x50;
	
	pinfo->ldi.h_back_porch = 49;
	pinfo->ldi.h_front_porch = 89;
	pinfo->ldi.h_pulse_width = 5;
	pinfo->ldi.v_back_porch = 4;
	pinfo->ldi.v_front_porch = 6;
	pinfo->ldi.v_pulse_width = 2;
	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 1;
	pinfo->ldi.pixelclk_plr = 0;
	pinfo->ldi.data_en_plr = 0;
	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */
	pinfo->frame_rate = 60;
	/*pinfo->clk_rate = LCD_GET_CLK_RATE(pinfo);*/
	pinfo->clk_rate = 150000000;
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.dsi_bit_clk = 482;  /* clock lane(p/n) */

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
	if (platform_device_add_data(pdev, &panasonic_panel_data,
			sizeof(struct k3_fb_panel_data))) {
		k3fb_loge("failed to platform_device_add_data!\n");
		platform_device_put(pdev);
		return -ENOMEM;
	}

	k3_fb_add_device(pdev);

	panasonic_sysfs_init(pdev);

	return 0;
}

static struct platform_driver this_driver = {
	.probe = panasonic_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_panasonic_VVX10F002A00",
	},
};

static int __init mipi_panasonic_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		k3fb_loge("not able to register the driver, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(mipi_panasonic_panel_init);

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
#include <linux/lcd_tuning.h>
#include <mach/platform.h>
#include <mach/gpio.h>
#include <mach/boardid.h>

#include "k3_fb.h"
#include "k3_fb_def.h"
#include "mipi_dsi.h"
#include "mipi_reg.h"


#define PWM_LEVEL 100
#define EDC_PIXCEL_CLK_RATE                  (CONFIG_EDC_PIXCEL_CLK_RATE)

/*static int cnt = 0;*/
/*----------------Power ON Sequence(sleep mode to Normal mode)---------------------*/

/*static char soft_reset[] = {
	0x01,
};*/

static char MCAP[] = {
	0xB0,
	0x00,
};

static char set_address[] = {
	0x36,
	0xC0,
};

static char bl_level[] = {
	0x51,
	0x00,
	0x00,
};

static char bl_enable[] = {
	0x53,
	0x24,
};

#if defined(CONFIG_OVERLAY_COMPOSE)
static char display_setting2[] = {
    0xc2,
    0x31, 0xF7, 0x80, 0x10, 0x08, 0x00, 0x00,
};

static char nvm_write[] = {
    0xD6, 0x01,
};
#endif

static char exit_sleep[] = {
	0x11,
};

static char display_on[] = {
	0x29,
};
/*
static char color_enhance[] = {
    0xBD,
    0x90, 0xC0, 0xC0, 0xC0,
    0x90, 0x70, 0x90, 0x90,
    0x20, 0x00, 0x80,
};
*/

/*-------------------Power OFF Sequence(Normal to power off)----------------------*/
static char display_off[] = {
	0x28,
};

static char enter_sleep[] = {
	0x10,
};
/*-------------------GAMMA2.2 Sequence----------------------*/
/*static char gamma22_param1[] = {
	0xc7,
	0x09, 0x1d, 0x21, 0x28, 0x31,
	0x42, 0x37, 0x4e, 0x5d, 0x6e,
	0x73, 0x75, 0x09, 0x1d, 0x21,
	0x28, 0x31, 0x42, 0x37, 0x4e,
	0x5d, 0x6e, 0x73, 0x75,
};

static char gamma22_param2[] = {
	0xc8,
	0x09, 0x1d, 0x21, 0x28, 0x31,
	0x42, 0x37, 0x4e, 0x5d, 0x6e,
	0x73, 0x75, 0x09, 0x1d, 0x21,
	0x28, 0x31, 0x42, 0x37, 0x4e,
	0x5d, 0x6e, 0x73, 0x75,
};

static char gamma22_param3[] = {
	0xc9,
	0x09, 0x1d, 0x21, 0x28, 0x31,
	0x42, 0x37, 0x4e, 0x5d, 0x6e,
	0x73, 0x75, 0x09, 0x1d, 0x21,
	0x28, 0x31, 0x42, 0x37, 0x4e,
	0x5d, 0x6e, 0x73, 0x75,
};

static char power_param[] = {
	0xd5,
	0x06, 0x00, 0x00, 0x01, 0x5c,
	0x01, 0x5c,
};*/

/*-------------------BASE Sequence----------------------*/
static char MCAP_param1[] = {
	0xb0,
	0x04,
};

static char MCAP_param2[] = {
	0xb0,
	0x03,
};
/*-------------------CABC BASE Sequence----------------------*/
/*static char cabc_base_param1[] = {
	0x51,
	0x0f, 0xff,
};*/

static char cabc_base_param2[] = {
	0x53,
	0x2c,
};
/*-------------------R63311 inter setting----------------------*/
static char cabc_vid_inter_param[] = {
	0xb8,
	0x18, 0x80, 0x18, 0x18, 0xcf,
	0x1f, 0x00, 0x0c, 0x12, 0x6c,
	0x11, 0x6c, 0x12, 0x0c, 0x12,
	0xda, 0x6d, 0xff, 0xff, 0x10,
	0x67, 0xa3, 0xdb, 0xfb, 0xff,
};
static char cabc_ui_inter_param[] = {
	0xb8,
	0x18, 0x80, 0x18, 0x18, 0xcf,
	0x1f, 0x00, 0x0c, 0x0c, 0x6c,
	0x0c, 0x6c, 0x0c, 0x0c, 0x0c,
	0xda, 0x6d, 0xff, 0xff, 0x10,
	0xb3, 0xfb, 0xff, 0xff, 0xff,
};
/*-------------------CABC GUI Sequence----------------------*/
static char cabc_ui_param[] = {
	0xba,
	0x00, 0x3f, 0x01, 0x01, 0x9f,
	0x1f, 0x80,
};

static char cabc_ui_on[] = {
	0x55,
	0x01,
};
/*-------------------CABC MOVIE Sequence----------------------*/
static char cabc_video_param[] = {
	0xb9,
#if 0
	0x0f, 0x18, 0x04, 0x40, 0x9f,
	0x1f, 0x80,
#else //use these code
	0x00, 0x30, 0x18, 0x18, 0x9f,
	0x1f, 0x80,
#endif
};
static char cabc_video_on[] = {
	0x55,
	0x03,
};
/*-------------------CABC PWM Sequence----------------------*/
static char cabc_pwm_param[] = {
	0xce,
	0x00, 0x01, 0x00, 0xc1, 0x00,
	0xb2, 0x02,
};

/*-------------------CE Sequence----------------------*/
static char ce_param[] = {
	0xca,
	0x01, 0x80, 0xdc, 0x80, 0xec,
	0x80, 0x90, 0xa0, 0x08, 0x10,
	0x14, 0xab, 0x0a, 0x4a, 0x37,
	0xa0, 0x55, 0xf8, 0x0c, 0x10,
	0x20, 0x10, 0x3f, 0x3f, 0x19,
	0xd6, 0x10, 0x10, 0x3f, 0x3f,
	0x3f, 0x3f,
};
/*-------------------Sharpness Sequence----------------------*/
static char sharpness_param[] = {
	0xdd,
	0x11, 0x93, //ADST 150%->50%, AVST 100%->50%
};

static struct dsi_cmd_desc toshiba_video_on_cmds1[] = {
	//{DTYPE_DCS_WRITE, 0, 5, WAIT_TYPE_MS,
		//sizeof(soft_reset), soft_reset},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP), MCAP},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(set_address), set_address},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(bl_level), bl_level},
	{DTYPE_DCS_WRITE1, 0, 100, WAIT_TYPE_US,
		sizeof(bl_enable), bl_enable},
#if defined(CONFIG_OVERLAY_COMPOSE)
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(display_setting2), display_setting2},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(nvm_write), nvm_write},
#endif

	{DTYPE_DCS_WRITE, 0, 5, WAIT_TYPE_MS,
		sizeof(display_on), display_on},
	//{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
	//	sizeof(exit_sleep), exit_sleep},
};

static struct dsi_cmd_desc toshiba_video_on_cmds2[] = {
	{DTYPE_DCS_WRITE, 0, 120, WAIT_TYPE_MS,
		sizeof(exit_sleep), exit_sleep},

	//{DTYPE_DCS_WRITE, 0, 100, WAIT_TYPE_US,
	//	sizeof(display_on), display_on},
};

static struct dsi_cmd_desc toshiba_display_off_cmds[] = {
	{DTYPE_DCS_WRITE, 0, 20, WAIT_TYPE_MS,
		sizeof(display_off), display_off},
	{DTYPE_DCS_WRITE, 0, 80, WAIT_TYPE_MS,
		sizeof(enter_sleep), enter_sleep}
};
static struct dsi_cmd_desc toshiba_cabc_ui_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param1), MCAP_param1},
//	{DTYPE_DCS_LWRITE, 0, 20, WAIT_TYPE_MS,
//		sizeof(cabc_base_param1), cabc_base_param1},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_base_param2), cabc_base_param2},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_ui_param), cabc_ui_param},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_ui_inter_param), cabc_ui_inter_param},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_pwm_param), cabc_pwm_param},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_ui_on), cabc_ui_on},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param2), MCAP_param2},
};
static struct dsi_cmd_desc toshiba_cabc_video_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param1), MCAP_param1},
//	{DTYPE_DCS_LWRITE, 0, 20, WAIT_TYPE_MS,
//		sizeof(cabc_base_param1), cabc_base_param1},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_base_param2), cabc_base_param2},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_video_param), cabc_video_param},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_vid_inter_param), cabc_vid_inter_param},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_pwm_param), cabc_pwm_param},
	{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(cabc_video_on), cabc_video_on},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param2), MCAP_param2},
};

static struct dsi_cmd_desc toshiba_sharpness_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param1), MCAP_param1},
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(sharpness_param), sharpness_param},
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param2), MCAP_param2},
};

static struct dsi_cmd_desc toshiba_ce_cmds[] = {
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param1), MCAP_param1},	
	{DTYPE_GEN_LWRITE, 0, 100, WAIT_TYPE_US,
		sizeof(ce_param), ce_param},	
	{DTYPE_GEN_WRITE2, 0, 100, WAIT_TYPE_US,
		sizeof(MCAP_param2), MCAP_param2},		
};

static volatile bool g_display_on;
static struct k3_fb_panel_data toshiba_panel_data;

static ssize_t toshiba_lcd_info_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret = 0;
	struct k3_panel_info *pinfo;
	pinfo = toshiba_panel_data.panel_info;
	sprintf(buf, "Toshiba 5.0' FHD TFT %d x %d\n",
		pinfo->xres, pinfo->yres);
	ret = strlen(buf) + 1;
	return ret;
}

static DEVICE_ATTR(lcd_info, S_IRUGO, toshiba_lcd_info_show, NULL);

//print suspend log
u32 gk3fb_edc_base;
bool enable_suspend_log;
bool sbl_low_power_mode = false;

static int Read_Lcd_States(u32 *temp, u32 edc_base){
	int i=0;
	if(!edc_base){
		printk("edc_base is wrong.\n");
		return -1;
	}
	set_dsi_mode(CMD_MODE);
	mdelay(5);
	for(i=0;i<6;i++){
		outp32(edc_base+ MIPIDSI_GEN_HDR_ADDR, (0x0A+i) << 8 | 0x06);
		mdelay(1);
		temp[i] = inp32(edc_base + MIPIDSI_GEN_PLD_DATA_ADDR);
	}
	set_dsi_mode(HSPD_MODE);
	mdelay(10);
	printk("edc_base is 0x%x.\n"
			"0x0A = 0x%x\n"
			"0x0B = 0x%x\n"
			"0x0C = 0x%x\n"
			"0x0D = 0x%x\n"
			"0x0E = 0x%x\n"
			"0x0F = 0x%x\n",
			edc_base,temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
	return 0;
}

static ssize_t toshiba_suspend_log_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret = 0;
	u32 temp[20] = {0};

	if(!gk3fb_edc_base){
		sprintf(buf,"edc_base is wrong. Try again after suspend and resume.\n");
		ret = strlen(buf) + 1;
		return ret;
	}

	if(!enable_suspend_log){
		sprintf(buf, "Toshiba 5.0' FHD TFT suspend log is disable.\n");
		ret = strlen(buf) + 1;
		return ret;
	}

	Read_Lcd_States(temp, gk3fb_edc_base);

	sprintf(buf,"edc_base is 0x%x.\n"
				"0x0A = 0x%x\n"
				"0x0B = 0x%x\n"
				"0x0C = 0x%x\n"
				"0x0D = 0x%x\n"
				"0x0E = 0x%x\n"
				"0x0F = 0x%x\n",
				gk3fb_edc_base,temp[0],temp[1],temp[2],temp[3],temp[4],temp[5]);
	ret = strlen(buf) + 1;
	return ret;
}

static ssize_t toshiba_suspend_log_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	long m_enable_suspend_log = simple_strtol(buf, NULL, 10) != 0;
	enable_suspend_log =(bool)m_enable_suspend_log;
	return count;
}


static DEVICE_ATTR(lcd_suspend_log, 0664,
	toshiba_suspend_log_show, toshiba_suspend_log_store);

static ssize_t toshiba_sbl_low_power_mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int ret = 0;
	if(sbl_low_power_mode)
	{
		sprintf(buf, "Toshiba 5.0' FHD TFT sbl low power mode is enable.\n");
	}
	else
	{
		sprintf(buf, "Toshiba 5.0' FHD TFT sbl low power mode is disable.\n");
	}
	ret = strlen(buf) + 1;
	return ret;
}

static ssize_t toshiba_sbl_low_power_mode_store(struct device *dev,
			     struct device_attribute *devattr,
			     const char *buf, size_t count)
{
	long m_sbl_low_power_mode = simple_strtol(buf, NULL, 10) != 0;
	sbl_low_power_mode =(bool)m_sbl_low_power_mode;
	return count;
}

static DEVICE_ATTR(sbl_low_power_mode, 0664,
	toshiba_sbl_low_power_mode_show, toshiba_sbl_low_power_mode_store);

static struct attribute *toshiba_attrs[] = {
	&dev_attr_lcd_info.attr,
	&dev_attr_lcd_suspend_log.attr,
	&dev_attr_sbl_low_power_mode.attr,
	NULL,
};

static struct attribute_group toshiba_attr_group = {
	.attrs = toshiba_attrs,
};

static int toshiba_sysfs_init(struct platform_device *pdev)
{
	int ret;
	ret = sysfs_create_group(&pdev->dev.kobj, &toshiba_attr_group);
	if (ret) {
		pr_err("k3fb, %s: create sysfs file failed!\n", __func__);
		return ret;
	}
	return 0;
}

#if 0
static void toshiba_sysfs_deinit(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &toshiba_attr_group);
}
static unsigned int g_csc_value[9];
static unsigned int g_is_csc_set;
static struct semaphore ct_sem;

static void toshiba_store_ct_cscValue(unsigned int csc_value[])
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
static int toshiba_set_ct_cscValue(struct k3_fb_data_type *k3fd)
{
     u32 edc_base = 0;
    edc_base = k3fd->edc_base;
    down(&ct_sem);
    if(1 == g_is_csc_set)
    {

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

static int toshiba_set_color_temperature(struct lcd_tuning_dev *ltd, unsigned int csc_value[])
{
    int flag = 0;
    struct platform_device *pdev;
    struct k3_fb_data_type *k3fd;

    if (ltd == NULL)
    {
        return -1;
    }
    pdev  = (struct platform_device *)(ltd->data);
    k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);

    if (k3fd == NULL)
    {
        return -1;
    }

    toshiba_store_ct_cscValue(csc_value);
    flag = toshiba_set_ct_cscValue(k3fd);
    return flag;
}
#endif

static int toshiba_set_gamma(struct lcd_tuning_dev *ltd, enum lcd_gamma gamma)
{
	//Fix me: Implement it
	return 0;
}

static int toshiba_set_cabc(struct lcd_tuning_dev *ltd, enum  tft_cabc cabc)
{
	int r = 0;
	u32 edc_base = 0;
	struct k3_fb_data_type *k3fd;

	BUG_ON(ltd == NULL);
	k3fd = (struct k3_fb_data_type *)platform_get_drvdata((struct platform_device *)(ltd->data));
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	switch (cabc) {
	case CABC_UI:
		mipi_dsi_cmds_tx(toshiba_cabc_ui_cmds, \
			ARRAY_SIZE(toshiba_cabc_ui_cmds));
		break;
	case CABC_VID:
		mipi_dsi_cmds_tx(toshiba_cabc_video_cmds, \
			ARRAY_SIZE(toshiba_cabc_video_cmds));
		break;
	case CABC_OFF:
		break;
	default:
		r = -1;
	}

	return r;
}

#if 0
static int toshiba_pwm_on(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	/* backlight on */
	PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
	PWM_GPIO_REQUEST(&(k3fd->panel_info));
	gpio_direction_input(k3fd->panel_info.gpio_pwm1);
	mdelay(1);
	pwm_set_backlight(k3fd->bl_level, &(k3fd->panel_info));
	pr_info("nzb %s enter!\n",__func__);

	return 0;
}
#endif

static int toshiba_pwm_off(struct k3_fb_data_type *k3fd)
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

static void toshiba_disp_on(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	struct k3_panel_info *pinfo = NULL;

	k3fb_loge("toshiba_disp_on enter!");

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);

#if 1

#ifdef CONFIG_MACH_HI6620OEM
	LCD_IOMUX_SET(pinfo, NORMAL);
#endif	
	LCD_GPIO_REQUEST(pinfo);

	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(1);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(1);

	//gpio_direction_output(pinfo->gpio_reset, 1);
	//mdelay(5);
	gpio_direction_output(pinfo->gpio_power, 1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(5);
	gpio_direction_output(pinfo->gpio_reset, 1);
	mdelay(10);

	
	mipi_dsi_cmds_tx(toshiba_video_on_cmds1, \
		ARRAY_SIZE(toshiba_video_on_cmds1));
	set_dsi_mode(HSPD_MODE);
	mdelay(120);
	mipi_dsi_cmds_tx(toshiba_video_on_cmds2, \
		ARRAY_SIZE(toshiba_video_on_cmds2));

/*nzb*/
	

	mipi_dsi_cmds_tx(toshiba_sharpness_cmds, \
		ARRAY_SIZE(toshiba_sharpness_cmds));

	mipi_dsi_cmds_tx(toshiba_ce_cmds, \
		ARRAY_SIZE(toshiba_ce_cmds));

    mipi_dsi_cmds_tx(toshiba_cabc_ui_cmds, \
        ARRAY_SIZE(toshiba_cabc_ui_cmds));
#endif	
	
/*nzb*/
	pr_info("nzb %s exit!\n",__func__);
	
}

static void toshiba_disp_off(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;
	u32 mTemp[20];
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	pinfo = &(k3fd->panel_info);

	if(enable_suspend_log){
		Read_Lcd_States(mTemp, edc_base);
	}

	mipi_dsi_cmds_tx(toshiba_display_off_cmds,
		ARRAY_SIZE(toshiba_display_off_cmds));

	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(1);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(1);
	gpio_direction_output(pinfo->gpio_power, 0);
	mdelay(1);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(1);
	LCD_GPIO_FREE(pinfo);
#ifdef CONFIG_MACH_HI6620OEM	
	LCD_IOMUX_SET(pinfo, LOWPOWER);
#endif

	LCD_TOSHIBA_VCC_DISABLE(pinfo);
	printk("\ndisplay off\n\n");
}

static int mipi_toshiba_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_panel_info *pinfo = NULL;
	
	k3fb_loge("mipi_toshiba_panel_on enter!");

	
	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	pinfo = &(k3fd->panel_info);


	if (pinfo->lcd_init_step == LCD_INIT_POWER_ON) {
	     
			  
		//LCD_VCC_ENABLE(pinfo);
		LCD_TOSHIBA_VCC_ENABLE(pinfo);

		pinfo->lcd_init_step = LCD_INIT_SEND_SEQUENCE;
		return 0;
	}
	else if (pinfo->lcd_init_step == LCD_INIT_SEND_SEQUENCE) {
	if (!g_display_on) {
			/* lcd display on */
			toshiba_disp_on(k3fd);
			/* backlight on */
			//toshiba_pwm_on(k3fd);
			g_display_on = true;
	} 
	}
	else {
	
	
		k3fb_loge("failed to init lcd!\n");
	}

	gk3fb_edc_base = k3fd->edc_base;

	pr_info("nzb %s exit!\n",__func__);

	return 0;
}

static int mipi_toshiba_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (g_display_on) {
		g_display_on = false;
		/* lcd display off */
		toshiba_disp_off(k3fd);
	}
	return 0;
}

static int mipi_toshiba_panel_set_backlight(struct platform_device *pdev)
{
	
	struct k3_fb_data_type *k3fd = NULL;

	char level[3] = {
		0x51, 0x00,
	};

	struct dsi_cmd_desc cabc_pwm[] = {
		{DTYPE_DCS_LWRITE, 0, 100, WAIT_TYPE_US,
		  sizeof(level), level}
		};

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
	
	//backlight may turn off when bl_level is below 6.
	if(k3fd->bl_level < 6 && k3fd->bl_level !=0)
		k3fd->bl_level = 6;
	
	level[2] = (char)k3fd->bl_level;
	
	mipi_dsi_cmds_tx(cabc_pwm, ARRAY_SIZE(cabc_pwm));
	
	return 0;
	
}

static int mipi_toshiba_panel_set_fastboot(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	LCD_VCC_ENABLE(&(k3fd->panel_info));
#ifdef CONFIG_MACH_HI6620OEM	
	LCD_IOMUX_SET(&(k3fd->panel_info), NORMAL);
#endif
	LCD_GPIO_REQUEST(&(k3fd->panel_info));

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		PWM_IOMUX_SET(&(k3fd->panel_info), NORMAL);
		PWM_GPIO_REQUEST(&(k3fd->panel_info));
	}

	g_display_on = true;

	return 0;
}

static struct k3_panel_info toshiba_panel_info = {0};
static struct k3_fb_panel_data toshiba_panel_data = {
	.panel_info = &toshiba_panel_info,
	.on = mipi_toshiba_panel_on,
	.off = mipi_toshiba_panel_off,
	.set_backlight = mipi_toshiba_panel_set_backlight,
	.set_fastboot = mipi_toshiba_panel_set_fastboot,
};


static struct lcd_tuning_ops sp_tuning_ops = {
	.set_gamma = toshiba_set_gamma,
	.set_cabc = toshiba_set_cabc,
};

static int __devinit toshiba_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;
	struct platform_device *reg_pdev;
	struct lcd_tuning_dev *ltd;
	struct lcd_properities lcd_props;

	k3fb_loge("toshiba_probe enter!");

	g_display_on = false;
	pinfo = toshiba_panel_data.panel_info;
	/* init lcd panel info */
	
	pinfo->xres = 1080;
	pinfo->yres = 1920;
	pinfo->type = PANEL_MIPI_VIDEO;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = EDC_OUT_RGB_888;
	pinfo->s3d_frm = EDC_FRM_FMT_2D;
	pinfo->bgr_fmt = EDC_RGB;
	pinfo->bl_set_type = BL_SET_BY_MIPI;
	pinfo->bl_max = PWM_LEVEL;
	pinfo->bl_min = 1;

	pinfo->frc_enable =  0;   //1;
	pinfo->esd_enable = 0;
	pinfo->sbl_enable = 1;

	/*q00230330 2012-12-13 add for apical begin*/
	pinfo->sbl.bl_max = 0xff;
	pinfo->sbl.cal_a = 0x08;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;
	/*q00230330 2012-12-13 add for apical end*/

	pinfo->ldi.h_back_porch = 40;
#if defined(CONFIG_OVERLAY_COMPOSE)
	pinfo->ldi.h_front_porch = 81;
#else
	pinfo->ldi.h_front_porch = 90;
#endif
	pinfo->ldi.h_pulse_width = 30;
#if defined(CONFIG_OVERLAY_COMPOSE)
	pinfo->ldi.v_back_porch = 12;
#else
	pinfo->ldi.v_back_porch = 4;
#endif
	pinfo->ldi.v_front_porch = 8;
	pinfo->ldi.v_pulse_width = 4;
	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 1;
	pinfo->ldi.pixelclk_plr = 0;
	pinfo->ldi.data_en_plr = 0;
	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */
	pinfo->frame_rate = 60;
	pinfo->clk_rate = 144000000;//144000000;
	pinfo->mipi.lane_nums = DSI_4_LANES;
	pinfo->mipi.color_mode = DSI_24BITS_1;
	pinfo->mipi.vc = 0;
	pinfo->mipi.dsi_bit_clk = 481;

	//enable_print_log
	enable_suspend_log = 0;

	LCD_TOSHIBA_VCC_GET(pdev, pinfo);
	LCDIO_SET_VOLTAGE(pinfo, 1800000, 1800000);
	
#ifdef CONFIG_MACH_HI6620OEM	
	/* lcd iomux */
	LCD_IOMUX_GET(pinfo);
#endif
	/* lcd resource */
	LCD_RESOURCE(pdev, pinfo, res);

	/* alloc panel device data */
	if (platform_device_add_data(pdev, &toshiba_panel_data,
		sizeof(struct k3_fb_panel_data))) {
		pr_err("k3fb, %s: platform_device_add_data failed!\n", __func__);
		platform_device_put(pdev);
		return -ENOMEM;
	}

	k3fb_loge("toshiba_probe 1 enter!");

	reg_pdev = k3_fb_add_device(pdev);

	k3fb_loge("toshiba_probe 2 enter!");

	//Fix me :lcd_props initialize
	lcd_props.type = TFT;
	lcd_props.default_gamma = GAMMA25;

	ltd = lcd_tuning_dev_register(&lcd_props, &sp_tuning_ops, (void *)reg_pdev);
	if (IS_ERR(ltd)) {
		pr_err("k3fb, %s: lcd_tuning_dev_register failed!\n", __func__);
		return -1;
	}

	toshiba_sysfs_init(pdev);

	 pr_info("nzb %s exit!\n",__func__);

	return 0;
}


static struct platform_driver this_driver = {
	.probe = toshiba_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = "mipi_toshiba_MDY90",
	},
};

static int __init mipi_toshiba_panel_init(void)
{
	int ret = 0;

	pr_info("nzb %s enter!\n",__func__);

	ret = platform_driver_register(&this_driver);
	if (ret) {
		pr_err("k3fb, %s not able to register the driver\n", __func__);
		return ret;
	}

	pr_info("nzb %s exit!\n",__func__);


	return ret;
}

module_init(mipi_toshiba_panel_init);

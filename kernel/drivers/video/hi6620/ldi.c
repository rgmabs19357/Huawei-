/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/err.h>

#include "k3_fb.h"
#include "ldi_reg.h"
#include "mipi_reg.h"

int ldi_init(struct k3_fb_data_type *k3fd)
{
	u32 edc_base = 0;

	BUG_ON(k3fd == NULL);

	edc_base = k3fd->edc_base;

    
	set_LDI_HRZ_CTRL0_hfp(edc_base, k3fd->panel_info.ldi.h_front_porch);
	set_LDI_HRZ_CTRL0_hbp(edc_base, k3fd->panel_info.ldi.h_back_porch);
	set_LDI_HRZ_CTRL1_hsw(edc_base, k3fd->panel_info.ldi.h_pulse_width);
	set_LDI_VRT_CTRL0_vfp(edc_base, k3fd->panel_info.ldi.v_front_porch);
	set_LDI_VRT_CTRL0_vbp(edc_base, k3fd->panel_info.ldi.v_back_porch);

	if (k3fd->panel_info.ldi.v_pulse_width > 15)
		k3fd->panel_info.ldi.v_pulse_width = 15;
	set_LDI_VRT_CTRL1_vsw(edc_base, k3fd->panel_info.ldi.v_pulse_width);
	set_LDI_PLR_CTRL_hsync(edc_base, k3fd->panel_info.ldi.hsync_plr);
	set_LDI_PLR_CTRL_vsync(edc_base, k3fd->panel_info.ldi.vsync_plr);
	set_LDI_PLR_CTRL_pixel_clk(edc_base, k3fd->panel_info.ldi.pixelclk_plr);
	set_LDI_PLR_CTRL_data_en(edc_base, k3fd->panel_info.ldi.data_en_plr);

	set_LDI_DSP_SIZE_hsize(edc_base, k3fd->panel_info.xres);
	set_LDI_DSP_SIZE_vsize(edc_base, k3fd->panel_info.yres);

    set_LDI_WORK_MODE_work_mode(edc_base, LDI_WORK);
	set_LDI_WORK_MODE_colorbar_en(edc_base, K3_DISABLE);

#ifdef CONFIG_DEBUG_FS
    if (g_fb_colorbar_mod == 1) {
        set_LDI_WORK_MODE_work_mode(edc_base, LDI_TEST);
	    set_LDI_WORK_MODE_colorbar_en(edc_base, K3_ENABLE);
    }    
#endif
	
	set_LDI_CTRL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
	set_LDI_CTRL_bpp(edc_base, k3fd->panel_info.bpp);
	set_LDI_CTRL_disp_mode(edc_base, k3fd->panel_info.ldi.disp_mode);
	set_LDI_CTRL_corlorbar_width(edc_base, 0x3C);

	if (PANEL_MIPI_CMD == k3fd->panel_info.type) {
		set_reg(edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 0);
		set_reg(edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 7);
		set_reg(edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 12);
	       set_LDI_CTRL_data_gate_en(edc_base, K3_DISABLE);
		/* if panel type is MIPI_CMD,we should enable ldi after pannel init,so it will implement in lid_on() */
		set_LDI_CTRL_ldi_en(edc_base, K3_DISABLE);
	}else{
		set_LDI_CTRL_ldi_en(edc_base, K3_ENABLE);
	}
	set_LDI_INT_CLR(edc_base, 0xFFFFFFFF);
	if (k3fd->panel_info.type == PANEL_HDMI) {
		/* dsi pixel off */
		set_reg(edc_base + LDI_HDMI_DSI_GT + LDI1_OFFSET, 0x1, 1, 0);
	}

	if (!(k3fd->panel_info.bl_set_type & BL_SET_BY_PWM)) {
        /* Modified for EDC1 offset, begin */
        if (k3fd_reg_base_edc0 == edc_base) {
            set_reg(edc_base + LDI_DE_SPACE_LOW, 0x1, 1, 1);
        } else {
            set_reg(edc_base + LDI_DE_SPACE_LOW + LDI1_OFFSET, 0x1, 1, 1);
        }
        /* Modified for EDC1 offset, end */
	}

    
	return 0;
}

int ldi_on(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);  	

	/* ldi clock enable */
	ret = clk_enable(k3fd->ldi_clk);
	if (ret != 0) {
		k3fb_loge("failed to enable ldi_clk, error=%d!\n", ret);
		return ret;
	}

	/* ldi init */
	ldi_init(k3fd);

	ret = panel_next_on(pdev);
	if (PANEL_MIPI_CMD == k3fd->panel_info.type) 
	{
		set_LDI_CTRL_ldi_en(k3fd->edc_base, K3_ENABLE);
	}
   
	return ret;
}

int ldi_off(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(pdev == NULL);

	k3fd = platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

    pr_info("%s enter succ!\n",__func__);
    
	edc_base = k3fd->edc_base;
    
	ret = panel_next_off(pdev);

#ifdef CONFIG_DEBUG_FS
    if (k3fd->index == 0) {
        if ((g_fb_lowpower_debug_flag & DEBUG_EDC_LOWPOWER_DISABLE) == DEBUG_EDC_LOWPOWER_DISABLE) {
            k3fb_logi(" edc ldi off was disable");
            return 0;
        }
    }
#endif
    if (PANEL_MIPI_CMD == k3fd->panel_info.type) {
    	 set_reg(edc_base + LDI_INT_EN_OFFSET, 0x0, 1, 0);
    	 set_reg(edc_base + LDI_INT_EN_OFFSET, 0x0, 1, 7);
    	 set_reg(edc_base + LDI_INT_EN_OFFSET, 0x0, 1, 12);
    }
    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == edc_base) {
        /* dsi pixel off */
        set_reg(edc_base + LDI_HDMI_DSI_GT, 0x1, 1, 0);
        /* disable ldi */
        set_reg(edc_base + LDI_CTRL_OFFSET, 0x0, 1, 0);
    } else {
        /* dsi pixel off */
        set_reg(edc_base + LDI_HDMI_DSI_GT + LDI1_OFFSET, 0x1, 1, 0);
        /* disable ldi */
        set_reg(edc_base + LDI_CTRL_OFFSET + LDI1_OFFSET, 0x0, 1, 0);
    }
    /* Modified for EDC1 offset, end */
    
	/* ldi clock gating */
	clk_disable(k3fd->ldi_clk);
	
    pr_info("%s exit succ!\n",__func__);
	return ret;
}

STATIC int ldi_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);
	k3fd = platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	if (!IS_ERR(k3fd->ldi_clk)) {
		clk_put(k3fd->ldi_clk);
	}

	ret = panel_next_remove(pdev);
	
	k3fb_logi("index=%d, exit!\n", k3fd->index);
	
	return ret;
}

int ldi_set_backlight(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	ret = panel_next_set_backlight(pdev);

	return ret;
}

STATIC int ldi_set_timing(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	edc_base = k3fd->edc_base;
    
	set_LDI_HRZ_CTRL0_hfp(edc_base, k3fd->panel_info.ldi.h_front_porch);
	set_LDI_HRZ_CTRL0_hbp(edc_base, k3fd->panel_info.ldi.h_back_porch);
	set_LDI_HRZ_CTRL1_hsw(edc_base, k3fd->panel_info.ldi.h_pulse_width);
	set_LDI_VRT_CTRL0_vfp(edc_base, k3fd->panel_info.ldi.v_front_porch);
	set_LDI_VRT_CTRL0_vbp(edc_base, k3fd->panel_info.ldi.v_back_porch);
	if (k3fd->panel_info.ldi.v_pulse_width > 15)
		k3fd->panel_info.ldi.v_pulse_width = 15;
	set_LDI_VRT_CTRL1_vsw(edc_base, k3fd->panel_info.ldi.v_pulse_width);

	set_LDI_DSP_SIZE_hsize(edc_base, k3fd->panel_info.xres);
	set_LDI_DSP_SIZE_vsize(edc_base, k3fd->panel_info.yres);

	set_LDI_PLR_CTRL_hsync(edc_base, k3fd->panel_info.ldi.hsync_plr);
	set_LDI_PLR_CTRL_vsync(edc_base, k3fd->panel_info.ldi.vsync_plr);

#ifndef PC_UT_TEST_ON
	if (k3_fb_set_clock_rate(k3fd, k3fd->ldi_clk, k3fd->panel_info.clk_rate) != 0) {
		k3fb_loge("failed to set ldi clk rate(%d).\n", k3fd->panel_info.clk_rate);
	}
#endif
	ret = panel_next_set_timing(pdev);
    pr_info("%s exit succ!\n",__func__);
	return ret;
}

STATIC int ldi_set_frc(struct platform_device *pdev, int target_fps)
{
	int ret = 0;
	BUG_ON(pdev == NULL);

	ret = panel_next_set_frc(pdev, target_fps);

	return 0;
}

STATIC int ldi_check_esd(struct platform_device *pdev)
{
	BUG_ON(pdev == NULL);

	return panel_next_check_esd(pdev);
}
#ifdef CONFIG_FB_CHECK_MIPI_TR
static int ldi_check_mipi_tr(struct platform_device *pdev)
{
	BUG_ON(pdev == NULL);

	return panel_next_check_mipi_tr(pdev);
}
#endif
#ifdef CONFIG_FB_SET_INVERSION
static int ldi_set_inversion_type(struct platform_device *pdev, unsigned int inversion_mode)
{
	BUG_ON(pdev == NULL);

	return panel_next_set_inversion_type(pdev, inversion_mode);
}
#endif

#ifdef CONFIG_FB_MIPI_DETECT
static int ldi_mipi_detect(struct platform_device *pdev)
{
	BUG_ON(pdev == NULL);

	return panel_next_mipi_detect(pdev);
}
#endif

STATIC int ldi_probe(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct fb_info *fbi = NULL;
	struct platform_device *k3_fb_dev = NULL;
	struct k3_fb_panel_data *pdata = NULL;
	int ret = 0;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);
    pr_info("%s enter succ!\n",__func__);

	/* ldi clock */
	if (k3fd->index == 0) {
		k3fd->ldi_clk  = clk_get(NULL, CLK_LDI0_NAME);
        k3fd->dsp_pll  = clk_get(NULL, CLK_DSP_PLL_NAME);
	    k3fd->peri_pll = clk_get(NULL, CLK_PERI_PLL_NAME);
	    
	    if (IS_ERR(k3fd->dsp_pll)) {
    		k3fb_loge("failed to get dsp_pll!\n");
    		return PTR_ERR(k3fd->dsp_pll);
    	}
    	
    	if (IS_ERR(k3fd->peri_pll)) {
    		k3fb_loge("failed to get peri_pll!\n");
    		return PTR_ERR(k3fd->peri_pll);
    	}
		
	} else if (k3fd->index == 1) {
		k3fd->ldi_clk  = clk_get(NULL, CLK_LDI1_NAME);
		k3fd->dsp_pll  = NULL;
	    k3fd->peri_pll = NULL;
	} else {
		k3fb_loge("fb%d not support now!\n", k3fd->index);
		return EINVAL;
	}	

	if (IS_ERR(k3fd->ldi_clk)) {
		k3fb_loge("failed to get ldi_clk!\n");
		return PTR_ERR(k3fd->ldi_clk);
	}	

	/* set ldi clock rate */
	ret = k3_fb_set_clock_rate(k3fd, k3fd->ldi_clk, k3fd->panel_info.clk_rate);
	if (ret != 0) {
		k3fb_loge("failed to set ldi clk rate(%d).\n", k3fd->panel_info.clk_rate);
		return ret;
	}

	/* k3_fb device */
	k3_fb_dev = platform_device_alloc(DEV_NAME_FB, pdev->id);
	if (!k3_fb_dev) {
		k3fb_loge("failed to k3_fb platform_device_alloc!\n");
		return -ENOMEM;
	}

	/* link to the latest pdev */
	k3fd->pdev = k3_fb_dev;

	/* alloc panel device data */
	if (platform_device_add_data(k3_fb_dev, pdev->dev.platform_data,
		sizeof(struct k3_fb_panel_data))) {
		k3fb_loge("failed to platform_device_add_data!\n");
		platform_device_put(k3_fb_dev);
		return -ENOMEM;
	}

	/* data chain */
	pdata = (struct k3_fb_panel_data *)k3_fb_dev->dev.platform_data;
	pdata->on = ldi_on;
	pdata->off = ldi_off;
	pdata->remove = ldi_remove;
	pdata->set_backlight = ldi_set_backlight;
	pdata->set_timing = ldi_set_timing;
	pdata->set_frc = ldi_set_frc;
	pdata->check_esd = ldi_check_esd;
#ifdef CONFIG_FB_CHECK_MIPI_TR
	pdata->check_mipi_tr = ldi_check_mipi_tr;
#endif
#ifdef CONFIG_FB_SET_INVERSION
	pdata->set_inversion_type = ldi_set_inversion_type;
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	pdata->mipi_detect = ldi_mipi_detect;
#endif
	pdata->next = pdev;

	/* get/set panel info */
	memcpy(&k3fd->panel_info, pdata->panel_info, sizeof(struct k3_panel_info));

	fbi = k3fd->fbi;
	/*fbi->var.pixclock = clk_round_rate(pixel_edc_clk, k3fd->panel_info.clk_rate);*/
	fbi->var.pixclock = k3fd->panel_info.clk_rate;
	fbi->var.left_margin = k3fd->panel_info.ldi.h_back_porch;
	fbi->var.right_margin = k3fd->panel_info.ldi.h_front_porch;
	fbi->var.upper_margin = k3fd->panel_info.ldi.v_back_porch;
	fbi->var.lower_margin = k3fd->panel_info.ldi.v_front_porch;
	fbi->var.hsync_len = k3fd->panel_info.ldi.h_pulse_width;
	fbi->var.vsync_len = k3fd->panel_info.ldi.v_pulse_width;

	/* set driver data */
	platform_set_drvdata(k3_fb_dev, k3fd);
	/* register in k3_fb driver */
	ret = platform_device_add(k3_fb_dev);
	if (ret) {
		platform_device_put(k3_fb_dev);
		k3fb_loge("failed to platform_device_add!\n");
		return ret;
	}

    pr_info("%s exit succ!\n",__func__);
	return ret;
}

static struct platform_driver this_driver = {
	.probe = ldi_probe,
	.remove = NULL,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = NULL,
	.driver = {
		.name = DEV_NAME_LDI,
		},
};

STATIC int __init ldi_driver_init(void)
{
	int ret = 0;
    pr_info("%s enter succ!\n",__func__);
	ret = platform_driver_register(&this_driver);
	if (ret) {
		k3fb_loge("not able to register the driver, error=%d!\n", ret);
		return ret;
	}
    pr_info("%s exit succ!\n",__func__);
	return ret;
}

module_init(ldi_driver_init);

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

#include <linux/clk.h>
#include <linux/pwm.h>
#include <mach/gpio.h>

#include "k3_fb_panel.h"
#include "edc_overlay.h"
#include "k3_fb.h"
#include "mipi_dsi.h"
#include "mipi_reg.h"

void set_reg(u32 addr, u32 val, u8 bw, u8 bs)
{
	u32 mask = (1 << bw) - 1;
	u32 tmp = inp32(addr);
	tmp &= ~(mask << bs);
	outp32(addr, tmp | ((val & mask) << bs));
}

int panel_next_on(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
			if(next_pdata){
                if((next_pdata->on)){
                    ret = next_pdata->on(next_pdev);
                }
			}
		}
	}

	return ret;
}

int panel_next_off(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
			if (next_pdata){
			    if(next_pdata->off){
                    ret = next_pdata->off(next_pdev);
			    }
			}
		}
	}

	return ret;
}

int panel_next_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
            if (next_pdata){
                if(next_pdata->remove){
                    ret = next_pdata->remove(next_pdev);
                }
            }
		}
	}

	return ret;
}

int panel_next_set_backlight(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
            if (next_pdata){
                if(next_pdata->set_backlight){
                    ret = next_pdata->set_backlight(next_pdev);
                }
            }
		}
	}

	return ret;
}

int panel_next_set_timing(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
            if (next_pdata){
                if(next_pdata->set_timing){
                    ret = next_pdata->set_timing(next_pdev);
                }
            }
		}
	}

	return ret;
}

int panel_next_set_frc(struct platform_device *pdev, int target_fps)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
            if (next_pdata){
                if(next_pdata->set_frc){
                    ret = next_pdata->set_frc(next_pdev, target_fps);
                }
            }
		}
	}

	return ret;
}

int panel_next_check_esd(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
            if (next_pdata){
                if(next_pdata->check_esd){
                    ret = next_pdata->check_esd(next_pdev);
                }
            }
		}
	}

	return ret;
}
#ifdef CONFIG_FB_CHECK_MIPI_TR
int panel_next_check_mipi_tr(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);
	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
			if ((next_pdata) && (next_pdata->check_mipi_tr))
				ret = next_pdata->check_mipi_tr(next_pdev);
		}
	}
	return ret;
}
#endif
#ifdef CONFIG_FB_SET_INVERSION
int panel_next_set_inversion_type(struct platform_device *pdev, unsigned int inversion_mode)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);

	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
			if ((next_pdata) && (next_pdata->set_inversion_type))
				ret = next_pdata->set_inversion_type(next_pdev, inversion_mode);
		}
	}

	return ret;
}
#endif

#ifdef CONFIG_FB_MIPI_DETECT
int panel_next_mipi_detect(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_panel_data *next_pdata = NULL;
	struct platform_device *next_pdev = NULL;

	BUG_ON(pdev == NULL);
	pdata = (struct k3_fb_panel_data *)pdev->dev.platform_data;
	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct k3_fb_panel_data *)next_pdev->dev.platform_data;
			if ((next_pdata) && (next_pdata->mipi_detect))
				ret = next_pdata->mipi_detect(next_pdev);
		}
	}
	return ret;
}
#endif

struct platform_device *k3_fb_device_alloc(struct k3_fb_panel_data *pdata,
	u32 type, u32 index, u32 *graphic_ch)
{
	struct platform_device *this_dev = NULL;
	char dev_name[16] = {0};

	BUG_ON(pdata == NULL);

	switch (type) {
	case PANEL_HDMI:
		snprintf(dev_name, sizeof(dev_name), DEV_NAME_LDI);
		*graphic_ch = OVERLAY_PIPE_EDC1_CH1;
		break;
	case PANEL_DP:
		snprintf(dev_name, sizeof(dev_name), DEV_NAME_DP);
		*graphic_ch = OVERLAY_PIPE_EDC1_CH1;
		break;
	case PANEL_LDI:
		snprintf(dev_name, sizeof(dev_name), DEV_NAME_LDI);
		*graphic_ch = OVERLAY_PIPE_EDC0_CH2;
		break;
	case PANEL_MIPI_VIDEO:
	case PANEL_MIPI_CMD:
		snprintf(dev_name, sizeof(dev_name), DEV_NAME_MIPIDSI);
		*graphic_ch = OVERLAY_PIPE_EDC0_CH2;
		break;
	default:
		k3fb_loge("invalid panel type = %d!\n", type);
		return NULL;
	}

	pdata->next = NULL;

	this_dev = platform_device_alloc(dev_name, index + 1);
	if (this_dev) {
		if (platform_device_add_data(this_dev, pdata, sizeof(struct k3_fb_panel_data))) {
			k3fb_loge("failed to platform_device_add_data!\n");
			platform_device_put(this_dev);
			return NULL;
		}
	}

	return this_dev;
}

void  k3_fb_device_free(struct platform_device *pdev)
{
	BUG_ON(pdev == NULL);
	platform_device_put(pdev);
}


/******************************************************************************/

int LCD_VCC_GET(struct platform_device *pdev, struct k3_panel_info *pinfo)
{
	BUG_ON(pdev == NULL);
	BUG_ON(pinfo == NULL);

    /*
	pinfo->lcdio_vcc = regulator_get(&pdev->dev, VCC_LCDIO_NAME);
    
	if (IS_ERR(pinfo->lcdio_vcc)) {
		k3fb_loge("failed to get lcdio-vcc regulator!\n");
		return PTR_ERR((pinfo)->lcdio_vcc);
	}
    */
	pinfo->tpio_vcc = regulator_get(&pdev->dev, VCC_TPIO_NAME);
	if (IS_ERR(pinfo->tpio_vcc)) {
		k3fb_loge("failed to get tpio_vcc regulator!\n");
		return PTR_ERR((pinfo)->tpio_vcc);
	}

	pinfo->tpao_vcc = regulator_get(&pdev->dev, VCC_TPANALOG_NAME);
	if (IS_ERR(pinfo->tpao_vcc)) {
		k3fb_loge("failed to get tpao_vcc regulator!\n");
		return PTR_ERR((pinfo)->tpao_vcc);
	}
	return 0;
}

int LCD_TOSHIBA_VCC_GET(struct platform_device *pdev, struct k3_panel_info *pinfo)
{
	BUG_ON(pdev == NULL);
	BUG_ON(pinfo == NULL);

	pinfo->lcdio_vcc = regulator_get(&pdev->dev, VCC_LCDIO_NAME);
	if (IS_ERR(pinfo->lcdio_vcc)) {
		k3fb_loge("failed to get lcdio-vcc regulator!\n");
		return PTR_ERR((pinfo)->lcdio_vcc);
	}

	pinfo->tpio_vcc = regulator_get(&pdev->dev, VCC_TPIO_NAME);
	if (IS_ERR(pinfo->tpio_vcc)) {
		k3fb_loge("failed to get tpio_vcc regulator!\n");
		return PTR_ERR((pinfo)->tpio_vcc);
	}

	pinfo->tpao_vcc = regulator_get(&pdev->dev, VCC_TPANALOG_NAME);
	if (IS_ERR(pinfo->tpao_vcc)) {
		k3fb_loge("failed to get tpao_vcc regulator!\n");
		return PTR_ERR((pinfo)->tpao_vcc);
	}
	return 0;
}
void LCDIO_SET_VOLTAGE(struct k3_panel_info *pinfo, u32 min_uV, u32 max_uV)
{
	BUG_ON(pinfo == NULL);

	if (regulator_set_voltage(pinfo->lcdio_vcc, min_uV, max_uV) != 0) {
		k3fb_loge("failed to set lcdio vcc!\n");
	}
}

void TP_VCI_SET_VOLTAGE(struct k3_panel_info *pinfo, u32 min_uV, u32 max_uV)
{
	BUG_ON(pinfo == NULL);

	if (regulator_set_voltage(pinfo->tpao_vcc, min_uV, max_uV) != 0) {
		k3fb_loge("failed to set tp_vci vcc!\n");
	}
}

void LCD_VCC_PUT(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	/*
	if (!IS_ERR(pinfo->lcdio_vcc)) {
		regulator_put(pinfo->lcdio_vcc);
	}
	*/
	if (!IS_ERR(pinfo->tpio_vcc)) {
		regulator_put(pinfo->tpio_vcc);
	}

	if (!IS_ERR(pinfo->tpao_vcc)) {
		regulator_put(pinfo->tpao_vcc);
	}
}

void LCD_VCC_ENABLE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);
        
	if (!IS_ERR(pinfo->tpao_vcc)) {
		if (regulator_enable(pinfo->tpao_vcc) != 0) {
			k3fb_loge("failed to enable tpao_vcc regulator!\n");
		}
	}
	
	if (!IS_ERR(pinfo->tpio_vcc)) {
		if (regulator_enable(pinfo->tpio_vcc) != 0) {
			k3fb_loge("failed to enable tpio_vcc regulator!\n");
		}
	}
	/*
	if (!IS_ERR(pinfo->lcdio_vcc)) {
		if (regulator_enable(pinfo->lcdio_vcc) != 0) {
			k3fb_loge("failed to enable lcdio-vcc regulator!\n");
		}
	}
	*/
}

void LCD_TOSHIBA_VCC_ENABLE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);
        
	if (!IS_ERR(pinfo->tpao_vcc)) {
		if (regulator_enable(pinfo->tpao_vcc) != 0) {
			k3fb_loge("failed to enable tpao_vcc regulator!\n");
		}
	}
	
	if (!IS_ERR(pinfo->tpio_vcc)) {
		if (regulator_enable(pinfo->tpio_vcc) != 0) {
			k3fb_loge("failed to enable tpio_vcc regulator!\n");
		}
	}
	if (!IS_ERR(pinfo->lcdio_vcc)) {
		if (regulator_enable(pinfo->lcdio_vcc) != 0) {
			k3fb_loge("failed to enable lcdio-vcc regulator!\n");
		}
	}
}

void LCD_VCC_DISABLE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);
	/*
	if (!IS_ERR(pinfo->lcdio_vcc)) {
		if (regulator_disable(pinfo->lcdio_vcc) != 0) {
			k3fb_loge("failed to disable lcdio-vcc regulator!\n");
		}
	}
	*/
	if (!IS_ERR(pinfo->tpio_vcc)) {
		if (regulator_disable(pinfo->tpio_vcc) != 0) {
			k3fb_loge("failed to disable tpio_vcc regulator!\n");
		}
	}

	if (!IS_ERR(pinfo->tpao_vcc)) {
		if (regulator_disable(pinfo->tpao_vcc) != 0) {
			k3fb_loge("failed to disable tpao_vcc regulator!\n");
		}
	}
}

void LCD_TOSHIBA_VCC_DISABLE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (!IS_ERR(pinfo->lcdio_vcc)) {
		if (regulator_disable(pinfo->lcdio_vcc) != 0) {
			k3fb_loge("failed to disable lcdio-vcc regulator!\n");
		}
	}
	if (!IS_ERR(pinfo->tpio_vcc)) {
		if (regulator_disable(pinfo->tpio_vcc) != 0) {
			k3fb_loge("failed to disable tpio_vcc regulator!\n");
		}
	}

	if (!IS_ERR(pinfo->tpao_vcc)) {
		if (regulator_disable(pinfo->tpao_vcc) != 0) {
			k3fb_loge("failed to disable tpao_vcc regulator!\n");
		}
	}
}

int LCD_IOMUX_GET(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);                

	pinfo->tp_block = iomux_get_block(SYNAPTICS_IOMUX);
	if (!pinfo->tp_block) {
		k3fb_loge("failed to get tp_block!\n");
		return PTR_ERR(pinfo->tp_block);
	}
	
	pinfo->tp_block_config = iomux_get_blockconfig(SYNAPTICS_IOMUX);
	if (!pinfo->tp_block_config) {
		k3fb_loge("failed to get tp_block_config !\n");
		return PTR_ERR(pinfo->tp_block_config);
	}
	pinfo->lcd_block = iomux_get_block(IOMUX_LCD_NAME);
	if (!pinfo->lcd_block) {
		k3fb_loge("failed to get iomux_lcd!\n");
		return PTR_ERR(pinfo->lcd_block);
	}
	
	pinfo->lcd_block_config = iomux_get_blockconfig(IOMUX_LCD_NAME);
	if (!pinfo->lcd_block_config) {
		k3fb_loge("failed to get iomux_lcd config!\n");
		return PTR_ERR(pinfo->lcd_block_config);
	}

	return 0;
}

void LCD_IOMUX_SET(struct k3_panel_info *pinfo, int mode)
{
	BUG_ON(pinfo == NULL);
                
	if (blockmux_set(pinfo->tp_block, pinfo->tp_block_config, mode) != 0) {
		k3fb_loge("failed to set iomux_tp normal mode!\n");
	}
	if (blockmux_set(pinfo->lcd_block, pinfo->lcd_block_config, mode) != 0) {
		k3fb_loge("failed to set iomux_lcd normal mode!\n");
	}
}

int LCD_RESOURCE(struct platform_device *pdev, struct k3_panel_info *pinfo, 
	struct resource *res)
{
	BUG_ON(pdev == NULL);
	BUG_ON(pinfo == NULL);

	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_LCD_RESET_NAME);
	if (!res) {
		k3fb_loge("failed to get gpio reset resource!\n");
		return -ENXIO;
	}
	
	pinfo->gpio_reset = res->start;
	if (!gpio_is_valid(pinfo->gpio_reset)) {
		k3fb_loge("failed to get gpio reset resource!\n");
		return -ENXIO;
	}
	
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_LCD_POWER_NAME);
	if (!res) {
		k3fb_loge("failed to get gpio power resource!\n");
		return -ENXIO;
	}
	
	pinfo->gpio_power = res->start;
	if (!gpio_is_valid(pinfo->gpio_power)) {
		k3fb_loge("failed to get gpio power resource!\n");
		return -ENXIO;
	}
	#ifndef PC_UT_TEST_ON
	if(get_resolution_type() == 0 )
	#endif
	{
		res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_TP_RESET_NAME);
		if (!res) {
			k3fb_loge("failed to get gpio_tp_reset resource!\n");
			return -ENXIO;
		}
		
		pinfo->gpio_tp_reset = res->start;
		if (!(gpio_is_valid(pinfo->gpio_tp_reset))) {
			k3fb_loge("gpio_tp_reset is invalid!\n");
			return -ENXIO;
		}
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_LCD_ID1_NAME);
	if (!res) {
		k3fb_loge("failed to get gpio_lcd_id1 resource.\n");
		return -ENXIO;
	}
	
	pinfo->gpio_lcd_id1 = res->start;
	if (!(gpio_is_valid(pinfo->gpio_lcd_id1))) {
		k3fb_loge("gpio_lcd_id1 is invalid!\n");
		return -ENXIO;
	}

	return 0;
}

void LCD_GPIO_REQUEST(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (gpio_request(pinfo->gpio_power, GPIO_LCD_POWER_NAME) != 0) {
		k3fb_loge("failed to request gpio power!\n");
	}

	if (gpio_request(pinfo->gpio_reset, GPIO_LCD_RESET_NAME) != 0) {
		k3fb_loge("failed to request gpio reset!\n");
	}

	if (gpio_request(pinfo->gpio_tp_reset, GPIO_TP_RESET_NAME) != 0) {
		k3fb_loge("failed to request gpio_tp_reset!\n");
	}

	if (gpio_request(pinfo->gpio_lcd_id1, GPIO_LCD_ID1_NAME) != 0) {
		k3fb_loge("failed to request gpio_lcd_id1!\n");
	}
}

void LCD_GPIO_FREE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (gpio_is_valid(pinfo->gpio_reset)) {
		gpio_free(pinfo->gpio_reset);
	}
	
	if (gpio_is_valid(pinfo->gpio_power)) {
		gpio_free(pinfo->gpio_power);
	}
	
	if (gpio_is_valid(pinfo->gpio_tp_reset)) {
		gpio_free(pinfo->gpio_tp_reset);
	}
	
	if (gpio_is_valid(pinfo->gpio_lcd_id1)) {
		gpio_free(pinfo->gpio_lcd_id1);
	}
}

int PWM_CLK_GET(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	pinfo->pwm_clk = clk_get(NULL, CLK_PWM0_NAME);
	if (IS_ERR(pinfo->pwm_clk)) {
		k3fb_loge("failed to get pwm0 clk!\n");
		return PTR_ERR(pinfo->pwm_clk);
	}
	
	if (clk_set_rate(pinfo->pwm_clk, DEFAULT_PWM_CLK_RATE) != 0) {
		k3fb_loge("failed to set pwm clk rate!\n");
	}

	return 0;
}

void PWM_CLK_PUT(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (!IS_ERR(pinfo->pwm_clk)) {
		clk_put(pinfo->pwm_clk);
	}
}

int PWM_IOMUX_GET(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);
                
#if FB_BBIT_TEST_ENABLE	    
    return 0;
#else

	pinfo->pwm_block = iomux_get_block(IOMUX_PWM_NAME);
	if (!pinfo->pwm_block) {
		k3fb_loge("failed to get iomux_pwm!\n");
		return PTR_ERR(pinfo->pwm_block);
	}
	
	pinfo->pwm_block_config = iomux_get_blockconfig(IOMUX_PWM_NAME);
	if (!pinfo->pwm_block_config) {
		k3fb_loge("failed to get iomux_pwm config!\n");
		return PTR_ERR(pinfo->pwm_block_config);
	}

	return 0;
#endif	
}

void PWM_IOMUX_SET(struct k3_panel_info *pinfo, int mode)
{
	BUG_ON(pinfo == NULL);
                
#if FB_BBIT_TEST_ENABLE	    
    return;
#else

	if (blockmux_set(pinfo->pwm_block, pinfo->pwm_block_config, (mode)) != 0) {
		k3fb_loge("failed to set iomux pwm normal mode!\n");
	}

#endif	
}

int PWM_RESOUTCE(struct platform_device *pdev, struct k3_panel_info *pinfo, 
	struct resource *res)
{
	BUG_ON(pdev == NULL);
	BUG_ON(pinfo == NULL);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM,  REG_BASE_PWM0_NAME);
	if (!res) {
		k3fb_loge("failed to get pwm0 resource!\n");
		return -ENXIO;
	}	
	pinfo->pwm_base = (u32)ioremap((res)->start,PAGE_ALIGN(SZ_4K));
	
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_LCD_PWM0_NAME);
	if (!res) {
		k3fb_loge("failed to get gpio pwm0 resource!\n");
		return -ENXIO;
	}
	
	pinfo->gpio_pwm0 = res->start;
	if (!(gpio_is_valid(pinfo->gpio_pwm0))) {
		k3fb_loge("gpio pwm0 is invalid!\n");
		return -ENXIO;
	}
	
	res = platform_get_resource_byname(pdev, IORESOURCE_IO, GPIO_LCD_PWM1_NAME);
	if (!res) {
		k3fb_loge("failed to get gpio pwm1 resource!\n");
		return -ENXIO;
	}
	
	pinfo->gpio_pwm1 = res->start;
	if (!(gpio_is_valid(pinfo->gpio_pwm1))) {
		k3fb_loge("gpio pwm1 is invalid!\n");
		return -ENXIO;
	}

	return 0;
}

void PWM_GPIO_REQUEST(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (gpio_request(pinfo->gpio_pwm0, GPIO_LCD_PWM0_NAME) != 0) {
		k3fb_loge("failed to request gpio pwm0!\n");
	}
	
	if (gpio_request(pinfo->gpio_pwm1, GPIO_LCD_PWM1_NAME) != 0) {
		k3fb_loge("failed to request gpio pwm1!\n");
	}
}

void PWM_GPIO_FREE(struct k3_panel_info *pinfo)
{
	BUG_ON(pinfo == NULL);

	if (gpio_is_valid(pinfo->gpio_pwm0)) {
		gpio_free(pinfo->gpio_pwm0);
	}
	
	if (gpio_is_valid(pinfo->gpio_pwm1)) {
		gpio_free(pinfo->gpio_pwm1);
	}
}

int k3_fb_set_clock_rate(struct k3_fb_data_type *k3fd, struct clk *clk, u32 clk_rate)
{
    struct clk *parent_clk = NULL;
    u32   dsp_ratio  = 0;
    u32   peri_ratio = 0;
    u32   dsp_div  = 0;
    u32   peri_div = 0;
    
    if ((k3fd == NULL) || (clk == NULL)) {
        k3fb_loge(" k3fd is null, or clk is null \n");
        return -EINVAL;
    }

    if (k3fd->dsp_pll == NULL || k3fd->peri_pll == NULL) {
        
        if (clk_set_rate(clk, clk_rate) != 0) {
            k3fb_loge("set rate fail \n");
            return -EINVAL;
        }        

        return 0;
    }

    dsp_div  = k3fd->dsp_pll->rate / clk_rate;
    peri_div = k3fd->peri_pll->rate / clk_rate;

    if ((dsp_div == 0) && (peri_div == 0)) {
        k3fb_loge(" invalid clk_rate = %d\n", clk_rate);
        return -EINVAL;
    } else if (peri_div == 0) {
        parent_clk = k3fd->dsp_pll;
    } else if (dsp_div == 0) {
        parent_clk = k3fd->peri_pll;
    } else {
        dsp_ratio  = ((k3fd->dsp_pll->rate % clk_rate) * 1000) / dsp_div;
        peri_ratio = ((k3fd->peri_pll->rate % clk_rate) * 1000) / peri_div;

        if (dsp_ratio <= peri_ratio) {
            parent_clk = k3fd->dsp_pll;
        } else {
            parent_clk = k3fd->peri_pll;
        }
    }

    /* the parent of pixel clock is pixel gate clock
     * the parent of pixel gate clock is DSP PLL and PERI PLL
     */
    if (clk->parent != NULL) {
        clk_set_parent(clk->parent, parent_clk);
    } else {
        clk_set_parent(clk, parent_clk);    
    }    
    
    if (clk_set_rate(clk, clk_rate) != 0) {
        k3fb_loge("set rate fail \n");
        return -EINVAL;
    }

    return 0;   
}

#ifdef CONFIG_DEBUG_FS
void k3fb_logi_vsync_debugfs (const char* fmt, ...)
{
    va_list args;	
    
    if (g_fb_log_printk_flag.bits.bit_vsync) {
    	va_start(args, fmt);
    	vprintk(fmt, args);
    	va_end(args);
	}
}

void k3fb_logi_display_debugfs(const char* fmt, ...)
{
    va_list args;	
    
    if (g_fb_log_printk_flag.bits.bit_display) {
    	va_start(args, fmt);
    	vprintk(fmt, args);
    	va_end(args);
	}


}

void k3fb_logi_backlight_debugfs(const char* fmt, ...)
{
    va_list args;	
    
    if (g_fb_log_printk_flag.bits.bit_backlight) {
    	va_start(args, fmt);
    	vprintk(fmt, args);
    	va_end(args);
	}
}

#endif

int mipi_dsi_wait_and_read(struct k3_fb_data_type *k3fd, u32 *read_value, int wait_type, int wait_time)
{
	bool is_timeout = 1;
	int delay_count = 0;
	u32 tmp = 0;
	int nRet = 0;

	while(1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_CMD_PKT_STATUS_ADDR);
		if(((tmp&0x00000001) == 0x00000001) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			if (wait_type == WAIT_TYPE_US)
				udelay(wait_time);
			else
				msleep(wait_time);

			++delay_count;
		}
	}
	while(1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_CMD_PKT_STATUS_ADDR);
		if(((tmp&0x00000040) != 0x00000040) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			if (wait_type == WAIT_TYPE_US)
				udelay(wait_time);
			else
				msleep(wait_time);

			++delay_count;
		}
	}
	if (false == is_timeout) {
		*read_value = get_MIPIDSI_GEN_PLD_DATA();
	} else {
		*read_value = 0;
		nRet = -1;
		pr_info("%s: read value error\n", __func__);
	}

	return nRet;
}



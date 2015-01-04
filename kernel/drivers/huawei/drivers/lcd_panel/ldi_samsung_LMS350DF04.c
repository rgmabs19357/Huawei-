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
#include <linux/pwm.h>
#include <linux/gpio.h>
#include <linux/leds.h>

#include <mach/gpio.h>
#include <mach/platform.h>
#include <mach/hisi_spi2.h>

#include "k3_fb.h"
#include "k3_fb_def.h"

#include "spi.h"


#define PWM_LEVEL 100
#define TIME_PER_FRAME	16

#define EDC_PIXCEL_CLK_RATE                  (CONFIG_EDC_PIXCEL_CLK_RATE)

static volatile PSPI_REG g_pSpi0Reg;

BOOL LcmWriteSpi2(u8 * data, UINT length)
{
    UINT16 tmp = 0;
    UINT  i = 0;
	
	while ((INREG32(&g_pSpi0Reg->SSPSR) & CSP_BITFMASK(CSPI_SSPSR_BSY)))
	{
	}
	
	INSREG32(&g_pSpi0Reg->SSPCR1, CSP_BITFMASK(CSPI_SSPCR1_SSE),
				CSP_BITFVAL(CSPI_SSPCR1_SSE, CSPI_SSPCR1_SSE_DISABLE));
   
    for(i = 0; i < length; i++)
    {
        while(!(INREG32(&g_pSpi0Reg->SSPSR) & CSP_BITFMASK(CSPI_SSPSR_TNF)))//TNF TFE
        {
        }

        // put next Tx data into CSPI FIFO
        OUTREG16(&g_pSpi0Reg->SSPDR, data[i]);
    }
    
    INSREG32(&g_pSpi0Reg->SSPCR1, CSP_BITFMASK(CSPI_SSPCR1_SSE),
        CSP_BITFVAL(CSPI_SSPCR1_SSE, CSPI_SSPCR1_SSE_ENABLE));


    for(i = 0; i < length; i++)
    {        
        while (!(INREG32(&g_pSpi0Reg->SSPSR) & CSP_BITFMASK(CSPI_SSPSR_RNE)))
        {
        }
        tmp = INREG16(&g_pSpi0Reg->SSPDR);
    }

    return TRUE;
}

STATIC bool spiSendData(u8 *data, u32 length, u8 bitcount)
{
    UINT i;

    for (i = 0; i < length; i += 3)
    {
        LcmWriteSpi2(data, 3);

        data += 3;
    }

	return true;
}

void InitSpi(int dataSize)
{    
    g_pSpi0Reg = (PSPI_REG)ioremap(SPI0_BASE, sizeof(SPI_REG));

    OUTREG32(&g_pSpi0Reg->SSPCR0,
        CSP_BITFVAL(CSPI_SSPCR0_FRF, CSPI_SSPCR0_FRF_SPI) |
        CSP_BITFVAL(CSPI_SSPCR0_SPO, CSPI_SSPCR0_SPO_ACTIVE_HIGH) |
        CSP_BITFVAL(CSPI_SSPCR0_SPH, CSPI_SSPCR0_SPH_LEADING) |
        CSP_BITFVAL(CSPI_SSPCR0_DSS, dataSize) |
        CSP_BITFVAL(CSPI_SSPCR0_SCR, 9));
    
    OUTREG32(&g_pSpi0Reg->SSPCR1, SPI3CR1);
    
    OUTREG32(&g_pSpi0Reg->SSPCPSR, 2);
}

/*--------------Power ON Sequence(power on to Normal mode)----------------------*/

static u8 powerOnData1[] = {
    0x74, 0x00, 0x07,
    0x76, 0x00, 0x00
};

/* Wait more than 10ms */
static u8 powerOnData2[] = {
    0x74, 0x00, 0x11,
    0x76, 0x22, 0x2F,
    0x74, 0x00, 0x12,
    0x76, 0x0F, 0x00,
    0x74, 0x00, 0x13,
    0x76, 0x7F, 0xD9,
    0x74, 0x00, 0x76,
    0x76, 0x22, 0x13,
    0x74, 0x00, 0x74,
    0x76, 0x00, 0x01,
    0x74, 0x00, 0x76,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x10,
    0x76, 0x56, 0x04
};

/* Wait more than 6frames */
static u8 powerOnData3[] = {
    0x74, 0x00, 0x12,
    0x76, 0x0C, 0x63
};

/* Wait more than 5frames */
static u8 powerOnData4[] = {
    0x74, 0x00, 0x01,
    0x76, 0x08, 0x3B, /* 0x08 or 0x0b */
    0x74, 0x00, 0x02,
    0x76, 0x03, 0x00,
    0x74, 0x00, 0x03,
    0x76, 0xC0, 0x40,
    0x74, 0x00, 0x08,
    0x76, 0x00, 0x0A,
    0x74, 0x00, 0x09,
    0x76, 0x00, 0x0F,
    0x74, 0x00, 0x76,
    0x76, 0x22, 0x13,
    0x74, 0x00, 0x0b,
    0x76, 0x33, 0x40,
    0x74, 0x00, 0x0c,
    0x76, 0x00, 0x20,
    0x74, 0x00, 0x1C,
    0x76, 0x77, 0x70,
    0x74, 0x00, 0x76,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x0D,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x0E,
    0x76, 0x05, 0x00,
    0x74, 0x00, 0x14,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x15,
    0x76, 0x08, 0x03,
    0x74, 0x00, 0x16,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x30,
    0x76, 0x00, 0x03,
    0x74, 0x00, 0x31,
    0x76, 0x07, 0x0F,
    0x74, 0x00, 0x32,
    0x76, 0x0D, 0x05,
    0x74, 0x00, 0x33,
    0x76, 0x04, 0x05,
    0x74, 0x00, 0x34,
    0x76, 0x09, 0x0D,
    0x74, 0x00, 0x35,
    0x76, 0x05, 0x01,
    0x74, 0x00, 0x36,
    0x76, 0x04, 0x00,
    0x74, 0x00, 0x37,
    0x76, 0x05, 0x04,
    0x74, 0x00, 0x38,
    0x76, 0x0C, 0x09,
    0x74, 0x00, 0x39,
    0x76, 0x01, 0x0C
};

/* wait NOTHING  */
static u8 powerOnData5[] = {
    0x74, 0x00, 0x07,
    0x76, 0x00, 0x01
};

/* Wait more than 2frame */
static u8 powerOnData6[] = {
    0x74, 0x00, 0x07,
    0x76, 0x01, 0x01
};

/* Wait more than 2frame */
static u8 powerOnData7[] = {
    0x74, 0x00, 0x07,
    0x76, 0x01, 0x03
};


/* --------------Power Off Sequence(Normal mode to power off)-------------------- */

static u8 powerOffData1[] = {
    0x74, 0x00, 0x0b,
    0x76, 0x30, 0x00,
    0x74, 0x00, 0x07,
    0x76, 0x01, 0x02
};

/* Wait more than 2frame */
static u8 powerOffData2[] = {
    0x74, 0x00, 0x07,
    0x76, 0x00, 0x00
};

/* Wait more than 2frame */
static u8 powerOffData3[] = {
    0x74, 0x00, 0x12,
    0x76, 0x00, 0x00,
    0x74, 0x00, 0x10,
    0x76, 0x06, 0x00
};

/* wait 1s */
static u8 powerOffData4[] = {
    0x74, 0x00, 0x10,
    0x76, 0x06, 0x01
};


STATIC struct k3_fb_panel_data samsung_panel_data;

int samsung_pwm_on(struct k3_fb_data_type *k3fd)
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

int samsung_pwm_off(struct k3_fb_data_type *k3fd)
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

void samsung_disp_on(struct k3_fb_data_type *k3fd)
{
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	pinfo = &(k3fd->panel_info);

	LCD_VCC_ENABLE(pinfo);
	LCD_IOMUX_SET(pinfo, NORMAL);
	LCD_GPIO_REQUEST(pinfo);
	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(10);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_reset, 1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_power, 1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_reset, 1);
	mdelay(10);

    InitSpi(7);
    mdelay(10);

	spiSendData(powerOnData1, sizeof(powerOnData1), 8);
	mdelay(30);
	spiSendData(powerOnData2, sizeof(powerOnData2), 8);
	mdelay(6 * TIME_PER_FRAME);
	spiSendData(powerOnData3, sizeof(powerOnData3), 8);
	mdelay(5 * TIME_PER_FRAME);
	spiSendData(powerOnData4, sizeof(powerOnData4), 8);
	mdelay(30);
	spiSendData(powerOnData5, sizeof(powerOnData5), 8);
	mdelay(2 * TIME_PER_FRAME);
	spiSendData(powerOnData6, sizeof(powerOnData6), 8);
	mdelay(2 * TIME_PER_FRAME);
	spiSendData(powerOnData7, sizeof(powerOnData7), 8);
}

void samsung_disp_off(struct k3_fb_data_type *k3fd)
{
	struct k3_panel_info *pinfo = NULL;

	BUG_ON(k3fd == NULL);
	pinfo = &(k3fd->panel_info);

	spiSendData(powerOffData1, sizeof(powerOffData1), 8);
	mdelay(2 * TIME_PER_FRAME);
	spiSendData(powerOffData2, sizeof(powerOffData2), 8);
	mdelay(2 * TIME_PER_FRAME);
	spiSendData(powerOffData3, sizeof(powerOffData3), 8);
	mdelay(10);
	spiSendData(powerOffData4, sizeof(powerOffData4), 8);
	mdelay(10);

	gpio_direction_input(pinfo->gpio_lcd_id0);
	mdelay(10);
	gpio_direction_input(pinfo->gpio_lcd_id1);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_reset, 0);
	mdelay(10);
	gpio_direction_output(pinfo->gpio_power, 0);
	mdelay(10);
	LCD_GPIO_FREE(pinfo);
	LCD_IOMUX_SET(pinfo, LOWPOWER);
	LCD_VCC_DISABLE(pinfo);
}

int ldi_samsung_panel_on(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_info.display_on) {
		/* lcd display on */
		samsung_disp_on(k3fd);
		k3fd->panel_info.display_on = true;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight on */
			samsung_pwm_on(k3fd);
		}
	}
	return 0;
}

int ldi_samsung_panel_off(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	if (k3fd->panel_info.display_on) {
		k3fd->panel_info.display_on = false;
		if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
			/* backlight off */
			samsung_pwm_off(k3fd);
		}
		/* lcd display off */
		samsung_disp_off(k3fd);
	}

	return 0;
}

int ldi_samsung_panel_set_backlight(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(pdev == NULL);

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	return pwm_set_backlight(k3fd->bl_level, &(k3fd->panel_info));
}

static int ldi_samsung_panel_set_fastboot(struct platform_device *pdev)
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

static struct k3_panel_info samsung_panel_info = {0};
STATIC struct k3_fb_panel_data samsung_panel_data = {
	.panel_info = &samsung_panel_info,
	.on = ldi_samsung_panel_on,
	.off = ldi_samsung_panel_off,
	.set_backlight = ldi_samsung_panel_set_backlight,
	.set_fastboot = ldi_samsung_panel_set_fastboot,
};

STATIC int __devinit samsung_probe(struct platform_device *pdev)
{
	struct k3_panel_info *pinfo = NULL;
	struct resource *res = NULL;

	pinfo = samsung_panel_data.panel_info;
	/* init lcd info */
	pinfo->display_on = false;
	pinfo->xres = 320;
	pinfo->yres = 480;
	pinfo->width = 55;
	pinfo->height = 98;
	pinfo->type = PANEL_LDI;
	pinfo->orientation = LCD_PORTRAIT;
	pinfo->bpp = EDC_OUT_RGB_888;
	pinfo->s3d_frm = EDC_FRM_FMT_2D;
	pinfo->bgr_fmt = EDC_RGB;
	pinfo->bl_set_type = BL_SET_BY_PWM;
	pinfo->bl_max = PWM_LEVEL;
	pinfo->bl_min = 1;

	pinfo->frc_enable = 0;
	pinfo->esd_enable = 0;
	pinfo->sbl_enable = 1;

	pinfo->sbl.bl_max = 0xff;
	pinfo->sbl.cal_a = 0x0f;
	pinfo->sbl.cal_b = 0xd8;
	pinfo->sbl.str_limit = 0x40;

	pinfo->ldi.h_back_porch = 11;
	pinfo->ldi.h_front_porch = 4;
	pinfo->ldi.h_pulse_width = 4;
	pinfo->ldi.v_back_porch = 10;  /* 8 */
	pinfo->ldi.v_front_porch = 4;
	pinfo->ldi.v_pulse_width = 2;
	pinfo->ldi.hsync_plr = 1;
	pinfo->ldi.vsync_plr = 1;
	pinfo->ldi.pixelclk_plr = 1;
	pinfo->ldi.data_en_plr = 1;
	pinfo->ldi.disp_mode = LDI_DISP_MODE_NOT_3D_FBF;

	/* Note: must init here */
	pinfo->frame_rate = 60;
	pinfo->clk_rate = EDC_PIXCEL_CLK_RATE;

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
	if (platform_device_add_data(pdev, &samsung_panel_data,
		sizeof(struct k3_fb_panel_data))) {
		k3fb_loge("failed to platform_device_add_data!\n");
		platform_device_put(pdev);
		return -ENOMEM;
	}

	k3_fb_add_device(pdev);

	return 0;
}

static int samsung_remove(struct platform_device *pdev)
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

	return 0;
}

static void samsung_shutdown(struct platform_device *pdev)
{
	int ret = 0;

	ret = samsung_remove(pdev);
	if (ret != 0) {
		k3fb_loge("failed to shutdown, error=%d!\n", ret);
	}
}

static struct platform_driver this_driver = {
	.probe = samsung_probe,
	.remove = samsung_remove,
	.suspend = NULL,
	.resume = NULL,
	.shutdown = samsung_shutdown,
	.driver = {
		.name = "ldi_samsung_LMS350DF04",
	},
};

static int __init ldi_samsung_panel_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&this_driver);
	if (ret) {
		k3fb_loge("not able to register the driver, error=%d.\n", ret);
		return ret;
	}

	return ret;
}

module_init(ldi_samsung_panel_init);

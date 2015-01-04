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

#ifndef K3_FB_PANEL_H
#define K3_FB_PANEL_H

#include <linux/regulator/consumer.h>
#include <linux/mux.h>
#include <asm/io.h>
#include <mach/clock.h>
#include <mach/clk_name_interface.h>
#include "k3_fb_def.h"

#ifndef PC_UT_TEST_ON
#include "drv_regulator_user.h"
#endif

/* panel type list */
#define PANEL_NO			0xffff	/* No Panel */
#define PANEL_LDI			1	/* internal LCDC type */
#define PANEL_HDMI		2	/* HDMI TV */
#define PANEL_MIPI_VIDEO	3	/* MIPI */
#define PANEL_MIPI_CMD	4	/* MIPI */
#define PANEL_DP			5	/* Display Port */
#define PANEL_MIPI2RGB	6	/* MIPI to RGB */

/* device name */
#define DEV_NAME_LDI				"ldi"
#define DEV_NAME_HDMI			"hdmi"
#define DEV_NAME_DP				"displayport"
#define DEV_NAME_MIPI2RGB		"mipi2rgb"
#define DEV_NAME_MIPIDSI			"mipi_dsi"
#define DEV_NAME_FB				"k3_fb"
#define DEV_NAME_LCD_BKL		"lcd_backlight0"

/* LCD init step */
enum {
	LCD_INIT_POWER_ON = 0,
	LCD_INIT_SEND_SEQUENCE,
};

typedef struct panel_id_s {
	u32 id;
	u32 type;
} panel_id_type;

struct ldi_panel_info {
	u32 h_back_porch;
	u32 h_front_porch;
	u32 h_pulse_width;
	u32 v_back_porch;
	u32 v_front_porch;
	u32 v_pulse_width;

	u8 hsync_plr;
	u8 vsync_plr;
	u8 pixelclk_plr;
	u8 data_en_plr;
	u8 disp_mode;
};

struct mipi_dsi_phy_register {
	u32 lp2hs_time;
	u32 hs2lp_time;
	u32 clk_lp2hs_time;
	u32 clk_hs2lp_time;
	u32 clk_division;
	u32 cp_current;
	u32 lpf_ctrl;
	u32 factors_effective;
	u32 n_pll;
	u32 m_pll_1;
	u32 m_pll_2;
	u32 hsfreqrange;
};
/* DSI PHY configuration */
struct mipi_dsi_phy_ctrl {
	u32 burst_mode;
	u32 lane_byte_clk;
	u32 clk_division;
	u32 lp2hs_time;
	u32 hs2lp_time;
	u32 clk_lp2hs_time;
	u32 clk_hs2lp_time;
	u32 hsfreqrange;
	u32 pll_unlocking_filter;
	u32 cp_current;
	u32 lpf_ctrl;
	u32 n_pll;
	u32 m_pll_1;
	u32 m_pll_2;
	u32 factors_effective;
};

struct dsi_phy_seq_info {
    u32 min_range;
    u32 max_range;
    u16 hsfreqrange;
    u8 cp_current;
    u8 lpf_ctrl;
    u8 clk_lp2hs_time;
    u8 clk_hs2lp_time;
    u8 lp2hs_time;
    u8 hs2lp_time;
};

struct mipi_panel_info {
	u8 vc;
	u8 lane_nums;
	u8 color_mode;
	u32 dsi_bit_clk; /* clock lane(p/n) */
	/*u32 dsi_pclk_rate;*/
};

struct sbl_panel_info{
	u32 bl_max;
	u32 cal_a;
	u32 cal_b;
	u32 str_limit;
};

struct k3_panel_info {
	u32 type;
	u32 xres;
	u32 yres;
	u32 width;
	u32 height;
	u8 bpp;
	u8 orientation;
	u8 s3d_frm;
	u8 bgr_fmt;
	u8 frame_rate;
	u8 bl_set_type;
	u32 clk_rate;

	volatile bool display_on;
	u8 lcd_init_step;

	u8 sbl_enable;
	u8 frc_enable;
	u8 esd_enable;

	struct ldi_panel_info ldi;
	struct mipi_panel_info mipi;
	struct sbl_panel_info sbl;

	u32 gpio_reset;
	u32 gpio_power;
	u32 gpio_tp_reset;
	u32 gpio_lcd_id0;
	u32 gpio_lcd_id1;
	u32 gpio_lcd_enp;
	u32 gpio_lcd_enn;
	u32 gpio_lcd_pwm_en;
	struct regulator *lcdio_vcc;	
	struct iomux_block *lcd_block;
	struct block_config *lcd_block_config;

	struct regulator *tpio_vcc;
	struct regulator *tpao_vcc;
	struct iomux_block *tp_block;
	struct block_config *tp_block_config;
	u32 bl_max;
	u32 bl_min;
	u32 gpio_pwm0;
	u32 gpio_pwm1;
	u32 pwm_base;
	struct clk *pwm_clk;
	struct iomux_block *pwm_block;
	struct block_config *pwm_block_config;
};

struct k3_fb_data_type;

struct k3_fb_panel_data {
	struct k3_panel_info *panel_info;

	/* function entry chain */
	int (*on) (struct platform_device *pdev);
	int (*off) (struct platform_device *pdev);
	int (*remove) (struct platform_device *pdev);
	int (*set_backlight) (struct platform_device *pdev);
	int (*set_timing) (struct platform_device *pdev);
	int (*set_fastboot) (struct platform_device *pdev);
	int (*set_frc)(struct platform_device *pdev, int target_fps);
	int (*set_cabc)(struct platform_device *pdev, int value);
	int (*check_esd) (struct platform_device *pdev);
#ifdef CONFIG_FB_CHECK_MIPI_TR
	int (*check_mipi_tr)(struct platform_device *pdev);
#endif
#ifdef CONFIG_FB_SET_INVERSION
	int (*set_inversion_type)(struct platform_device *pdev, unsigned int inversion_mode);
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	int (*mipi_detect)(struct platform_device *pdev);
#endif
	int (*set_disp_resolution)(struct platform_device *pdev);
	struct platform_device *next;
};


/*******************************************************************************
** FUNCTIONS PROTOTYPES
*/

void set_reg(u32 addr, u32 val, u8 bw, u8 bs);

struct platform_device *k3_fb_device_alloc(struct k3_fb_panel_data *pdata,
	u32 type, u32 index, u32 *graphic_ch);
void k3_fb_device_free(struct platform_device *pdev);

int panel_next_on(struct platform_device *pdev);
int panel_next_off(struct platform_device *pdev);
int panel_next_remove(struct platform_device *pdev);
int panel_next_set_backlight(struct platform_device *pdev);
int panel_next_set_timing(struct platform_device *pdev);
int panel_next_set_frc(struct platform_device *pdev, int target_fps);
int panel_next_check_esd(struct platform_device *pdev);
#ifdef CONFIG_FB_CHECK_MIPI_TR
int panel_next_check_mipi_tr(struct platform_device *pdev);
#endif
#ifdef CONFIG_FB_SET_INVERSION
int panel_next_set_inversion_type(struct platform_device *pdev, unsigned int inversion_mode);
#endif
#ifdef CONFIG_FB_MIPI_DETECT
int panel_next_mipi_detect(struct platform_device *pdev);
#endif
int pwm_set_backlight(int bl_lvl, struct k3_panel_info *pinfo);
int k3_fb_set_clock_rate(struct k3_fb_data_type *k3fd, struct clk *clk, u32 clk_rate);

/******************************************************************************/

#define CLK_PWM0_NAME	        CLK_PWM0
#define CLK_MIPI_DPHY0_CFG_NAME	CLK_DPHY0_CFG
#define CLK_MIPI_DPHY0_REF_NAME CLK_DPHY0_REF
#define CLK_EDC0_NAME	        CLK_EDC0_CORE
#define CLK_LDI0_NAME	        CLK_EDC0_PIX_LDI
#define CLK_EDC0_AXI_NAME       CLK_ACLK_EDC0
#define CLK_EDC0_CFG_NAME       CLK_EDC0_CFG_CLK
#define CLK_DSI0_CFG_NAME       CLK_DSIO_CFG_CLK
#define CLK_DSP_PLL_NAME        CLK_DSPPLL
#define CLK_PERI_PLL_NAME       CLK_PERIPLL
#define CLK_G2D_NAME	        CLK_5G2D_CORE_CLK
#define CLK_EDC0_RST_NAME	    "clk_edc0_rst"

#define CLK_MIPI_DPHY1_NAME	    "clk_dphy2"
#define CLK_LDI1_NAME	        CLK_EDC1_PIX_LDI
#define CLK_EDC1_NAME	        CLK_EDC1_CORE
#define CLK_EDC1_AXI_NAME       CLK_EDC1_AXI
#define CLK_EDC1_CFG_NAME       CLK_EDC1_CFG_CLK

#define IRQ_LDI0_NAME	"irq_ldi0"
#define IRQ_LDI1_NAME	"irq_ldi1"
#define IRQ_EDC0_NAME	"irq_edc0"
#define IRQ_EDC1_NAME	"irq_edc1"

#define REG_BASE_PWM0_NAME	"reg_base_pwm0"
#define REG_BASE_EDC0_NAME	"reg_base_edc0"
#define REG_BASE_EDC1_NAME	"reg_base_edc1"
#define REG_BASE_DSI0_NAME	"reg_base_dsi0"

#ifndef PC_UT_TEST_ON
#define VCC_EDC0_NAME		EDC0_VDD
#define VCC_EDC1_NAME		EDC1_VDD
#define VCC_LCDIO_NAME		LCD_IO_VDD
#define VCC_LCDANALOG_NAME	LCD_ANALOG_VDD
#define VCC_TPIO_NAME      TP_IO_VDD
#define VCC_TPANALOG_NAME       TP_ANALOG_VDD
#endif

#define GPIO_LCD_RESET_NAME	"gpio_lcd_reset"
#define GPIO_LCD_POWER_NAME	"gpio_lcd_power"
#define GPIO_LCD_PWM0_NAME	"gpio_pwm0"
#define GPIO_LCD_PWM1_NAME	"gpio_pwm1"
#define GPIO_TP_RESET_NAME	  "rmi4_reset" 
#define GPIO_LCD_ID1_NAME	"gpio_lcd_id1"
#define GPIO_LCD_ENP_NAME "gpio_lcd_enp"
#define GPIO_LCD_ENN_NAME "gpio_lcd_enn"
#define GPIO_LCD_PWM_NAME "gpio_lcd_pwm_en"


#define SYNAPTICS_IOMUX     "block_tp"
#define IOMUX_LCD_NAME	"block_lcd"
#define IOMUX_PWM_NAME	"block_pwm"

#define DEFAULT_PWM_CLK_RATE	(13 * 1000000)


int LCD_VCC_GET(struct platform_device *pdev, struct k3_panel_info *pinfo);
int LCD_TOSHIBA_VCC_GET(struct platform_device *pdev, struct k3_panel_info *pinfo);
void LCDIO_SET_VOLTAGE(struct k3_panel_info *pinfo, u32 min_uV, u32 max_uV);

void TP_VCI_SET_VOLTAGE(struct k3_panel_info *pinfo, u32 min_uV, u32 max_uV);

void LCD_VCC_PUT(struct k3_panel_info *pinfo);
void LCD_VCC_ENABLE(struct k3_panel_info *pinfo);
void LCD_TOSHIBA_VCC_ENABLE(struct k3_panel_info *pinfo);
void LCD_VCC_DISABLE(struct k3_panel_info *pinfo);
void LCD_TOSHIBA_VCC_DISABLE(struct k3_panel_info *pinfo);

int LCD_IOMUX_GET(struct k3_panel_info *pinfo);
void LCD_IOMUX_SET(struct k3_panel_info *pinfo, int mode);

int LCD_RESOURCE(struct platform_device *pdev, struct k3_panel_info *pinfo, 
	struct resource *res);

void LCD_GPIO_REQUEST(struct k3_panel_info *pinfo);
void 	LCD_GPIO_FREE(struct k3_panel_info *pinfo);
int PWM_CLK_GET(struct k3_panel_info *pinfo);
void PWM_CLK_PUT(struct k3_panel_info *pinfo);

int PWM_IOMUX_GET(struct k3_panel_info *pinfo);
void PWM_IOMUX_SET(struct k3_panel_info *pinfo, int mode);

int PWM_RESOUTCE(struct platform_device *pdev, struct k3_panel_info *pinfo, 
	struct resource *res);

void PWM_GPIO_REQUEST(struct k3_panel_info *pinfo);
void PWM_GPIO_FREE(struct k3_panel_info *pinfo);

int mipi_dsi_wait_and_read(struct k3_fb_data_type *k3fd, u32 *read_value, int wait_type, int wait_time);
#endif /* K3_FB_PANEL_H */

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

#ifndef EDC_OVERLAY_H
#define EDC_OVERLAY_H

#include "k3_edc.h"

#include "reg_ops.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"

enum {
	OVERLAY_PIPE_EDC0_CH1,
	OVERLAY_PIPE_EDC0_CH2,
#if defined(CONFIG_OVERLAY_COMPOSE)
	OVERLAY_PIPE_EDC0_GNEW1,
	OVERLAY_PIPE_EDC0_GNEW2,
	OVERLAY_PIPE_EDC0_CURSOR, //happy
#endif //CONFIG_OVERLAY_COMPOSE
	OVERLAY_PIPE_EDC1_CH1,
	OVERLAY_PIPE_EDC1_CH2,

	OVERLAY_PIPE_MAX
};

enum {
	OVERLAY_SURFACE_1 = 0,
	OVERLAY_SURFACE_2,
#if defined(CONFIG_OVERLAY_COMPOSE)
	OVERLAY_SURFACE_3,
	OVERLAY_SURFACE_4,
	OVERLAY_SURFACE_5,
#endif
	OVERLAY_SURFACE_MAX
};

#define EDC1_OVERLAY_SURFACE_MAX    (2)
#define OVERLAY_TO_CHANELL_MAP_INVALID  (-1)
#define OVERLAY_TYPE_CHCAP_ALL		0x01
#define OVERLAY_TYPE_CHCAP_PARTIAL	0x02

#define OVERLAY_PIPE_GRAPHIC		0x01
#define OVERLAY_PIPE_VIDEO			0x02

/* b051 bbit begin */
#define SOC_AOSCTRL_BASE_ADDR SOC_SC_ON_BASE_ADDR
#define SOC_SCTRL_BASE_ADDR   SOC_SC_OFF_BASE_ADDR

#define soc_ao_sctrl_reg_wr(reg_offset,start_bit,end_bit,val)\
            (phy_reg_writel(SOC_AOSCTRL_BASE_ADDR,reg_offset,start_bit,end_bit,val))


#define soc_sctrl_reg_wr(reg_offset,start_bit,end_bit,val)\
            (phy_reg_writel(SOC_SCTRL_BASE_ADDR,reg_offset,start_bit,end_bit,val))

#define soc_ao_sctrl_reg_rd(reg_offset)\
            (phy_reg_readl(SOC_AOSCTRL_BASE_ADDR,reg_offset,0,31))


#define soc_sctrl_reg_rd(reg_offset)\
            (phy_reg_readl(SOC_SCTRL_BASE_ADDR,reg_offset,0,31))



/************************** edc0 power down district **************************/

/* EDC0 power_on clk enable*/

#define edc0_pwr_down_clk_en()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(0),3,3,1))

/* EDC0 iso disable */
#define edc0_pwr_down_iso_dis()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(0),3,3,1))



/* EDC0 disreset */
#define edc0_pwr_down_clk_disreset()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(0),3,3,1))
            

/* EDC0 reset */
#define edc0_pwr_down_clk_reset()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(0),3,3,1))


/* EDC0 iso able */
#define edc0_pwr_down_iso_en()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(0),3,3,1))

/* EDC0 power_on clk disable*/
#define edc0_pwr_down_clk_dis()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(0),3,3,1))
            

/* EDC0 power_off */
#define edc0_pwr_down_pwr_dis()\
            (soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_DIS0_ADDR(0),3,3,1))

/************************ edc0 clk reset and disreset ************************/
/* SPI0 clk_enable */
#define SPI0_pclk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(0),14,14,1))
#define SPI0_clk_enable()\
                (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(0),15,15,1))

/* pwm0 clk_enable */
#define pwm0_pclk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(0),0,0,1))
#define pwm0_clk_enable()\
                (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(0),1,1,1))

/* EDC0 core_clk_enable */
#define edc0_core_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),3,3,1))
            
/* EDC0 ldi_pixel_clk_enable */
#define edc0_pix_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),2,2,1))

/* EDC0 axi_clk_enable */
#define edc0_axi_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),1,1,1))

/* EDC0 cfg_clk_enable */
#define edc0_cfg_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),0,0,1))

/* dphy0_ref_clk_enable */
#define dphy0_ref_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),26,26,1))

/* dphy0_cfg_clk_enable */
#define dphy0_cfg_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),23,23,1))

/* dsi0_ref_clk_enable */
#define dsi0_cfg_clk_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(0),4,4,1))

/* EDC0 gate_clk_enable */
#define edc0_pix_gate_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(0),22,22,1))
#define edc0_core_gate_enable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(0),23,23,1))
            
/* pwm0/spi0 disreset */
#define SPI0_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS1_ADDR(0),7,7,1))
#define pwm0_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS1_ADDR(0),19,19,1))           


/* EDC0 core clk disreset*/
#define edc0_core_clk_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0),3,3,1))

/* EDC0 pixel ldi clk disreset */
#define edc0_pixel_clk_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0),2,2,1))

/* EDC0 axi clk disreset */
#define edc0_axi_clk_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0),1,1,1))

/* EDC0  cfg clk disreset*/
#define edc0_cfg_clk_disreset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0),0,0,1))

/* EDC0 core clk reset*/
#define edc0_core_clk_reset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(0),3,3,1))

/* EDC0 pixel ldi clk reset */
#define edc0_pixel_clk_reset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(0),2,2,1))

/* EDC0 axi clk reset */
#define edc0_axi_clk_reset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(0),1,1,1))

/* EDC0  cfg clk reset*/
#define edc0_cfg_clk_reset()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(0),0,0,1))

/* EDC0 core_clk_disable */
#define edc0_core_clk_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS11_ADDR(0),3,3,1))
            
/* EDC0 ldi_pixel_clk_disable */
#define edc0_pix_clk_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS11_ADDR(0),2,2,1))

/* EDC0 axi_clk_disable */
#define edc0_axi_clk_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS11_ADDR(0),1,1,1))

/* EDC0 cfg_clk_disable */
#define edc0_cfg_clk_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS11_ADDR(0),0,0,1))

/* EDC0 pix_gate_disable */
#define edc0_pix_gate_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS12_ADDR(0),22,22,1))

/* EDC0 core_gate_disable */
#define edc0_core_gate_disable()\
            (soc_sctrl_reg_wr(SOC_SCTRL_SC_PERIPH_CLKDIS12_ADDR(0),23,23,1))

/* B051 BBIT end */
/* define macro for set each overlay_surf reg */
#define SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, nVal) 	  do { \
                                                                           if (pst_overlay_func->set_overlay_src_blend_en != NULL) { \
																		       pst_overlay_func->set_overlay_src_blend_en(edc_base, nVal); } \
																	  } while(0)


#define SET_OVERLAY_ALPHA_MODE(pst_overlay_func, edc_base, nVal) 	  do { \
                                                                           if (pst_overlay_func->set_overlay_alpha_mode != NULL) { \
																   	           pst_overlay_func->set_overlay_alpha_mode(edc_base, nVal); } \
																   	  } while(0)

#define SET_OVERLAY_UNDER_ALPH_SEL(pst_overlay_func, edc_base, nVal)  do { \
                                                                           if (pst_overlay_func->set_overlay_under_alpha_sel != NULL) {\
																		       pst_overlay_func->set_overlay_under_alpha_sel(edc_base, nVal); } \
																	  } while(0)

#define SET_OVERLAY_ALPHA_SRC(pst_overlay_func, edc_base, nVal)  	  do { \
                                                                           if (pst_overlay_func->set_overlay_alpha_src != NULL) { \
																  	           pst_overlay_func->set_overlay_alpha_src(edc_base, nVal); } \
																  	  } while(0)

#define SET_OVERLAY_ALPHA_SEL(pst_overlay_func, edc_base, nVal)  	  do { \
                                                                           if (pst_overlay_func->set_overlay_alpha_sel != NULL) { \
																  	           pst_overlay_func->set_overlay_alpha_sel(edc_base, nVal);  }\
																  	  } while(0)

#define SET_OVERLAY_GLP_ALPHA(pst_overlay_func, edc_base, alp_value0, alp_value1)		do { \
                                                                                        if (pst_overlay_func->set_overlay_glp_alpha != NULL) { \
																  	    			        pst_overlay_func->set_overlay_glp_alpha(edc_base, alp_value0, alp_value1); } \
																  	    	} while(0)    

#define SET_OVERLAY_TOP(pst_overlay_func, edc_base, nVal)  	  		 do { \
                                                                          if (pst_overlay_func->set_overlay_top != NULL) { \
																  	          pst_overlay_func->set_overlay_top(edc_base, nVal); } \
																  } while(0)
struct edc_capability {
	u32 alpha_enable:1;
	u32 ckey_enable:1;
	u32 filter_enable:1;
	u32 csc_enable:1;
	u32 reserved:28;
};

struct edc_channel_info {
	struct edc_capability cap;

	u8 alp_src;
	u8 alpha0;
	u8 alpha1;
	u32 ckeymin;
	u32 ckeymax;
};

typedef union {
	struct {
		u32  ovly1_sel : 2;
		u32  ovly2_sel : 2;
		u32  ovly3_sel : 2;
		u32  ovly4_sel : 2;
		u32  reserved0 : 24;
	} bits;
	u32 ul32;
}EDC_CROSS_CTL_VALUE;
/**
 * @struct
 * @brief
 */
struct edc_overlay_pipe {
	u32 pipe_type;
	u32 pipe_num;
	u32 edc_base;
	struct overlay_info req_info;
	struct edc_channel_info  edc_ch_info;

	void (*set_EDC_CHL_ADDR)(u32 edc_base, u32 nVal);
	void (*set_EDC_CHR_ADDR)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CTL_ch_en)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CTL_secu_line)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CTL_bgr)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CTL_pix_fmt)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CTL_colork_en)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_COLORK_MIN)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_COLORK_MAX)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_XY)(u32 edc_base, u32 nVal1, u32 nVal2);
	void (*set_EDC_CH_SIZE)(u32 edc_base, u32 nVal1, u32 nVal2);
	void (*set_EDC_CH_STRIDE)(u32 edc_base, u32 nVal);

	void (*set_EDC_CH_CSCIDC_csc_en)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCIDC)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCODC)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCP0)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCP1)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCP2)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCP3)(u32 edc_base, u32 nVal);
	void (*set_EDC_CH_CSCP4)(u32 edc_base, u32 nVal);
#if defined(CONFIG_OVERLAY_COMPOSE)
	void (*set_OVC_CH_CSCIDC)(u32 edc_base, u32 cscidc_y, u32 cscidc_u, u32 cscidc_v);
	void (*set_OVC_CH_CSCODC)(u32 edc_base, u32 cscodc_r, u32 cscodc_g, u32 cscodc_b);
	void (*set_OVC_CH_CSCP0)(u32 edc_base, u32 csc_01p, u32 csc_00p);
	void (*set_OVC_CH_CSCP1)(u32 edc_base, u32 csc_10p, u32 csc_02p);
	void (*set_OVC_CH_CSCP2)(u32 edc_base, u32 csc_12p, u32 csc_11p);
	void (*set_OVC_CH_CSCP3)(u32 edc_base, u32 csc_21p, u32 csc_20p);
	void (*set_OVC_CH_CSCP4)(u32 edc_base, u32 csc_22p);
#endif //CONFIG_OVERLAY_COMPOSE
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)	
	  void (*set_EDC_CH_CLIP_bottom)(u32 edc_base, u32 nVal);
	  void (*set_EDC_CH_CLIP_right)(u32 edc_base, u32 nVal);
	  void (*set_EDC_CH_CLIP_top)(u32 edc_base, u32 nVal);
	  void (*set_EDC_CH_CLIP_left)(u32 edc_base, u32 nVal);
	  
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
    
	

};

struct st_overlay_surf_reg_func
{
	void (*set_overlay_src_blend_en)(u32 edc_base, u32 nval);
	void (*set_overlay_alpha_mode)(u32 edc_base, u32 nval);
	void (*set_overlay_under_alpha_sel)(u32 edc_base, u32 nval);
	void (*set_overlay_alpha_src)(u32 edc_base, u32 nval);
	void (*set_overlay_alpha_sel)(u32 edc_base, u32 nval);
	void (*set_overlay_glp_alpha)(u32 edc_base, u32 alp_value0, u32 alp_value1);
	void (*set_overlay_top)(u32 edc_base, u32 nval);
	void (*set_overlay_cross_switch_sel)(u32 edc_base, u32 nval);
};
struct edc_overlay_ctrl {
	struct edc_overlay_pipe plist[OVERLAY_PIPE_MAX];
	/*u32 panel_mode;*/
};


int edc_fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info, int id);
int fb_pan_display_camera_debug(struct fb_var_screeninfo *var, struct fb_info *info, int id);
int edc_fb_suspend(struct fb_info *info);
int edc_fb_resume(struct fb_info *info);
int edc_fb_disable(struct fb_info *info);
int edc_fb_enable(struct fb_info *info);

void edc_overlay_init(struct edc_overlay_ctrl *ctrl);
int edc_overlay_get(struct fb_info *info, struct overlay_info *req);
int edc_overlay_set(struct fb_info *info, struct overlay_info *req);
int edc_overlay_unset(struct fb_info *info, int ndx);
int edc_overlay_play(struct fb_info *info, struct overlay_data *req);

int sbl_ctrl_resume(struct k3_fb_data_type *k3fd);
int sbl_ctrl_set(struct k3_fb_data_type *k3fd);
int sbl_bkl_set(struct k3_fb_data_type *k3fd, u32 value);

#if defined(CONFIG_OVERLAY_COMPOSE)
volatile u32 edc_overlay_compose_get_cfg_ok(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_reg_get_ch1_rotation(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch1_state(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch1_start_x(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch1_start_y(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch1_width(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch1_height(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_state(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_start_x(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_start_y(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_width(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_height(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew1_state(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew1_start_x(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew1_start_y(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew1_width(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew1_height(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew2_state(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew2_start_x(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew2_start_y(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew2_width(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_gnew2_height(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_ch2_fmt(struct k3_fb_data_type *k3fd);
volatile u32 edc_overlay_compose_get_crs_state(struct k3_fb_data_type *k3fd);
u32 edc_overlay_compose_get_state(struct fb_info *info, u32 pipe_id);
bool edc_overlay_compose_get_overlay_0_ch(struct fb_info *info, u32 pipe_id);
u32 edc_overlay_compose_get_cfg_disable(struct fb_info *info, u32 pipe_id);
u32 edc_overlay_compose_get_ch1_rotation(struct fb_info *info, u32 pipe_id);
int edc_overlay_compose_pipe_unset_previous(struct fb_info *info, u32 previous_type, u32 previous_count);
#if defined(EDC_CH_CHG_SUPPORT)
void overlay_compose_edc1_power_off(void);
int edc_overlay_compose_ch_chg_disable(struct k3_fb_data_type *k3fd, struct fb_info *info);
#endif
int edc_overlay_compose_play(struct fb_info *info, struct overlay_data *req);
int edc_overlay_compose_ch_unset(struct fb_info *info, int ndx);
int edc_overlay_compose_pan_display(struct fb_var_screeninfo *var, struct fb_info *info, int ch_num);
void edc_overlay_compose_pre_unset(struct fb_info *info, int ndx);

#endif //CONFIG_OVERLAY_COMPOSE

#endif  /* EDC_OVERLAY_H  */

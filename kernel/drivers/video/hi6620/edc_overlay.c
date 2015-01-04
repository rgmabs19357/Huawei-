/* Copyright (c) 2008-2010, Hisilicon Tech. Co., Ltd. All rights reserved.
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

#include <linux/fb.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>
#include <mach/boardid.h>
#include <trace/trace_kernel.h>

#include "k3_fb.h"
#include "edc_reg.h"
#include "ldi_reg.h"
#include "mipi_reg.h"
#include "sbl_reg.h"
#include <mach/hisi_mem.h>
#ifdef CONFIG_FOLLOWABILITY
#include "fb_monitor.h"
#endif

#define CAMERA_XRES_TEST 320
#define CAMERA_YRES_TEST 480
#define DDR_FREQ_POWER_ON 533000

/*--------------------VERTICLE--------------------*/
/* enlarge */
static s16 gfxcoefficient4_cubic[16][4] = {
	{0, 511, 0, 0, },
	{-37, 509, 42, -2, },
	{-64, 499, 86, -9, },
	{-82, 484, 129, -19, },
	{-94, 463, 174, -31, },
	{-98, 438, 217, -45, },
	{-98, 409, 260, -59, },
	{-92, 376, 300, -72, },
	{-83, 339, 339, -83, },
	{-72, 300, 376, -92, },
	{-59, 260, 409, -98, },
	{-45, 217, 438, -98, },
	{-31, 174, 463, -94, },
	{-19, 129, 484, -82, },
	{-9, 86, 499, -64, },
	{-2, 42, 509, -37, }
};

/* scaler down below 4/3 times */
static s16 gfxcoefficient4_lanczos2_6M_a15[16][4] = {
	{79, 383, 79, -29},
	{58, 384, 102, -32},
	{40, 380, 127, -35},
	{23, 374, 153, -38},
	{8, 363, 180, -39},
	{-6, 349, 208, -39},
	{-16, 331, 235, -38},
	{-25, 311, 262, -36},
	{-31, 287, 287, -31},
	{-36, 262, 311, -25},
	{-38, 235, 331, -16},
	{-39, 208, 349, -6},
	{-39, 180, 363, 8},
	{-38, 153, 374, 23},
	{-35, 127, 380, 40},
	{-32, 102, 384, 58}
};

/* scaler down below 2 times */
static s16 gfxcoefficient4_lanczos2_5M_a15[16][4] = {
	{103, 328, 103, -22},
	{85, 328, 121, -22},
	{69, 324, 141, -22},
	{53, 319, 161, -21},
	{40, 311, 181, -20},
	{27, 301, 201, -17},
	{16, 288, 221, -13},
	{7, 273, 240, -8},
	{-2, 258, 258, -2},
	{-8, 240, 273, 7},
	{-13, 221, 288, 16},
	{-17, 201, 301, 27},
	{-20, 181, 311, 40},
	{-21, 161, 319, 53},
	{-22, 141, 324, 69},
	{-22, 121, 328, 85}
};

/*--------------------HORIZONTAL--------------------*/
/* enlarge */
static s16 gfxcoefficient8_cubic[8][8] = {
	{0, 0, 0, 511, 0, 0, 0, 0, },
	{-3, 11, -41, 496, 61, -16, 4, 0, },
	{-4, 17, -63, 451, 138, -35, 9, -1, },
	{-4, 18, -70, 386, 222, -52, 14, -2, },
	{-3, 17, -65, 307, 307, -65, 17, -3, },
	{-2, 14, -52, 222, 386, -70, 18, -4, },
	{-1, 9, -35, 138, 451, -63, 17, -4, },
	{0, 4, -16, 61, 496, -41, 11, -3, }
};

/* scaler down */
static s16 gfxcoefficient8_lanczos2_8tap[8][8] = {
	{-16, 0, 145, 254, 145, 0, -16, 0},
	{-13, -9, 123, 252, 167, 11, -19, 0},
	{-10, -15, 101, 245, 188, 25, -21, -1},
	{-7, -19, 80, 236, 206, 41, -22, -3},
	{-5, -21, 60, 222, 222, 60, -21, -5},
	{-3, -22, 41, 206, 236, 80, -19, -7},
	{-1, -21, 25, 188, 245, 101, -15, -10},
	{0, -19, 11, 167, 252, 123, -9, -13}
};

static bool isAlphaRGBType(int format)
{
	switch (format) {
	case EDC_ARGB_1555:
	case EDC_ARGB_8888:
		return true;
	default:
		return false;
	}
	return false;
}

static int get_bytespp(int format)
{
	switch (format) {
	case EDC_ARGB_1555:
	case EDC_RGB_565:
		return 2;
	case EDC_XRGB_8888:
	case EDC_ARGB_8888:
		return 4;
	case EDC_YUYV_I:
	case EDC_UYVY_I:
	case EDC_YVYU_I:
	case EDC_VYUY_I:
	default:
		return 2;
	}
}

static int g_ovly2ch_map[OVERLAY_SURFACE_MAX - 1] = {OVERLAY_TO_CHANELL_MAP_INVALID,
													 OVERLAY_TO_CHANELL_MAP_INVALID,
													 OVERLAY_TO_CHANELL_MAP_INVALID,
													 OVERLAY_TO_CHANELL_MAP_INVALID};

static struct st_overlay_surf_reg_func  g_overlay_surf_func[OVERLAY_SURFACE_MAX] = {
	{NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 set_EDC_CROSS_CTL_ovly_1_sel}, /* ovly_1 */

	{set_EDC_CH12_OVLY_alp_blend_en,
	 set_EDC_CH12_OVLY_alp_src,
	 set_EDC_CH12_OVLY_ch1_alp_sel,
	 set_EDC_CH12_OVLY_pix_alp_src,
	 set_EDC_CH12_OVLY_ch2_alp_sel,
	 set_EDC_CH12_GLB_ALP_VAL,
	 set_EDC_CH12_OVLY_ch2_top,
	 set_EDC_CROSS_CTL_ovly_2_sel}, /* ovly_2 */

	{set_EDC_OVERLAY_3_blend_en,
	 set_EDC_OVERLAY_3_alpha_mode,
	 set_EDC_OVERLAY_3_under_alpha_sel,
	 NULL,							/* alpha_src is null */
	 set_EDC_OVERLAY_3_alpha_sel,
	 set_EDC_OVERLAY_3_glb_alpha,
	 NULL,
	 set_EDC_CROSS_CTL_ovly_3_sel},  /* ovly_3 */

	{set_EDC_OVERLAY_4_blend_en,
	 set_EDC_OVERLAY_4_alpha_mode,
	 set_EDC_OVERLAY_4_under_alpha_sel,
	 NULL,
	 set_EDC_OVERLAY_4_alpha_sel,
	 set_EDC_OVERLAY_4_glb_alpha,
	 NULL,
	 set_EDC_CROSS_CTL_ovly_4_sel},  /* ovly_4 */

	{set_EDC_CRS_CTL_alp_blend_en,
	 set_EDC_CRS_CTL_alp_src,
	 set_EDC_CRS_CTL_under_alp_sel,
	 NULL,
	 set_EDC_CRS_CTL_alp_sel,
	 set_EDC_CRS_GLB_ALP_VAL,
	 NULL,
	 NULL}  /* always,ovly_5 is cursor layer  */

};
static bool is64BytesOddAlign(int type, u32 stride)
{
	if (type == FB_64BYTES_ODD_ALIGN_NONE) {
		return true;
	} else {
		return (((stride / 64) % 2 == 0) ? false : true);
	}
}

static bool isNeedDither(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	if (k3fd->fb_imgType > EDC_ARGB_8888) {
		return false;
	}

	if (((k3fd->panel_info.bpp == EDC_OUT_RGB_565) && (k3fd->fb_imgType == EDC_RGB_565)) ||
		((k3fd->panel_info.bpp == EDC_OUT_RGB_888) && (k3fd->fb_imgType == EDC_ARGB_8888)) ||
		((k3fd->panel_info.bpp == EDC_OUT_RGB_888) && (k3fd->fb_imgType == EDC_XRGB_8888))) {
		return  false;
	}

	return true;
}

static u32 computeDisplayAddr(struct k3fb_img *img,
	u32 rotation, struct k3fb_rect *src)
{
	u32 addr = 0;
	u32 temp = 0;

	BUG_ON(img == NULL || src == NULL);

	switch (rotation) {
	case EDC_ROT_NOP:
		{
			addr = img->phy_addr + img->stride * src->y +
				src->x * get_bytespp(img->format);
		}
		break;
	case EDC_ROT_90:
		{
			addr = img->phy_addr + img->stride * src->y +
				src->x * get_bytespp(img->format);

			temp = src->w;
			src->w = src->h;
			src->h = temp;
		}
		break;
	case EDC_ROT_180:
		{
			addr =  img->phy_addr + img->stride * (src->y + src->h - 1) +
				src->x * get_bytespp(img->format);
		}
		break;
	case EDC_ROT_270:
		{
			addr =  img->phy_addr + img->stride * (src->y + src->h - 1) +
				src->x * get_bytespp(img->format);

			temp = src->w;
			src->w = src->h;
			src->h = temp;
		}
		break;
	default:
		k3fb_loge("Unsupported rotation(%d)!\n", rotation);
		break;
	}

	return addr;
}

#if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
static void resetSizeByClip(u32* w, u32* h, u32 rotation, u32 clip_right, u32 clip_bottom, int rate)
{
    switch(rotation)
    {
        case EDC_ROT_NOP:
        case EDC_ROT_180:
            *w = *w + rate * clip_right;
            *h = *h + rate * clip_bottom;
            break;
        case EDC_ROT_90:
        case EDC_ROT_270:
            *w = *w + rate * clip_bottom;
            *h = *h + rate * clip_right;
            break;
        default:
            break;
    }
}

static int alignCompute(int format, int alignMask)
{
    int i = 1;
    int a = 0;
    int b = 0;
    int bpp = get_bytespp(format);
    if (bpp > alignMask){
        a = bpp;
        b = alignMask;
    }
    else {
        a = alignMask;
        b = bpp;
    }
    while(((a * i) % b) != 0){
        i++;
    }
    return (a * i) / bpp;
}

static void computeAlignSrc(struct k3fb_img *img, struct overlay_info * info, struct k3fb_rect * src, struct k3fb_rect * outSrc)
{
    u32 addr = 0;
    uint32_t height = img->height;
    uint32_t srcW = src->w - info->clip_right;
    int wAlign = alignCompute(img->format, 16);
    int hAlign = 2;
    int leftClip = 0;
    int topClip = 0;
    outSrc->x = src->x;
    outSrc->y = src->y;
    outSrc->w = src->w;
    outSrc->h = src->h;
    //printk("outSrc->h:%d outSrc->y: %d height:%d alignheight: %d", outSrc->h, outSrc->y, height, ALIGN_UP(height, hAlign));
    topClip = (outSrc->h + outSrc->y) - ALIGN_UP(height, hAlign);
    //printk("topClip: %d \n", topClip);
    if (topClip < 0){
        topClip = 0;
    }
    info->clip_bottom -= topClip;
    outSrc->y -= topClip;
    //printk("info->clip_bottom: %d \n", info->clip_bottom);
    addr = computeDisplayAddr(img, EDC_ROT_NOP, outSrc);
    //printk("addr: %X \n", addr);
    //128bit(16byte) align
    if (addr & 0x0f) {
        leftClip = (addr & 0x0f) / get_bytespp(img->format);
        outSrc->x -= leftClip;
		//printk("outSrc->x: %d,srcW: %d \n", outSrc->x, srcW);
        outSrc->w = ALIGN_UP((srcW + leftClip), wAlign);
        //printk("outSrc->w: %d \n", outSrc->w);
        info->clip_right = outSrc->w - (srcW + leftClip);
    }

    return;
}
#endif

int edc_mtcos_enable(u32 fb_index)  
{
    int i = 0;
    u32 pw_en_bit = 3;
    u32 edc_mtcos_state = 0x8;

    if (0 == fb_index) {
        pw_en_bit = 3;
        edc_mtcos_state = 0x8;  /* bit3 */
    } else if (1 == fb_index) {
        pw_en_bit = 4;
        edc_mtcos_state = 0x10;  /* bit4 */
    } else {
        k3fb_loge("fb index is not support index = %d \n", fb_index);
        return -1;
    }
    
    soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_EN0_ADDR(0),pw_en_bit, pw_en_bit, 1); 
    
    (void)udelay(10); 
    
    for (i = 0; i < 200; i++)
    {
        if ((edc_mtcos_state & soc_ao_sctrl_reg_rd(SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(0))) == edc_mtcos_state) {
            break;
        }
    }

    if (200 == i) {
        k3fb_loge("mtcmos status no ready \n");        
        return -1;
    }

    return 0;   
}

int edc_mtcos_disable(u32 fb_index)
{
    u32  pw_dis_bit = 3;

    if (0 == fb_index) {
        pw_dis_bit = 3;  /* bit3 */
    } else if (1 == fb_index) {
        pw_dis_bit = 4;  /* bit4 */
    } else {
        k3fb_loge("fb index is not support index = %d \n", fb_index);
        return -1;
    }
    
    soc_ao_sctrl_reg_wr(SOC_AO_SCTRL_SC_PW_DIS0_ADDR(0),pw_dis_bit, pw_dis_bit, 1);
    udelay(10);

    return 0;
}

static void edc_overlay_pipe_init4ch1(struct edc_overlay_pipe *pipe)
{
	BUG_ON(pipe == NULL);

	pipe->edc_ch_info.cap.ckey_enable = 0;
	pipe->edc_ch_info.ckeymin = 0xffffcc;
	pipe->edc_ch_info.ckeymax = 0xffffec;

	pipe->edc_ch_info.cap.alpha_enable = 1;
	pipe->edc_ch_info.alp_src = EDC_ALP_PIXEL;
	pipe->edc_ch_info.alpha0 = 0x7f;
	pipe->edc_ch_info.alpha1 = 0x7f;

	pipe->edc_ch_info.cap.filter_enable = 1;
	pipe->edc_ch_info.cap.csc_enable = 1;

	pipe->req_info.overlay_num = OVERLAY_SURFACE_1;
	pipe->set_EDC_CHL_ADDR = set_EDC_CH1L_ADDR;
	pipe->set_EDC_CHR_ADDR = set_EDC_CH1R_ADDR;
	pipe->set_EDC_CH_CTL_ch_en = set_EDC_CH1_CTL_ch1_en;
	pipe->set_EDC_CH_CTL_secu_line = set_EDC_CH1_CTL_secu_line;
	pipe->set_EDC_CH_CTL_bgr = set_EDC_CH1_CTL_bgr;
	pipe->set_EDC_CH_CTL_pix_fmt = set_EDC_CH1_CTL_pix_fmt;
	pipe->set_EDC_CH_CTL_colork_en = set_EDC_CH1_CTL_colork_en;
	pipe->set_EDC_CH_COLORK_MIN = set_EDC_CH1_COLORK_MIN;
	pipe->set_EDC_CH_COLORK_MAX = set_EDC_CH1_COLORK_MAX;
	pipe->set_EDC_CH_XY = set_EDC_CH1_XY;
	pipe->set_EDC_CH_SIZE = set_EDC_CH1_SIZE;
	pipe->set_EDC_CH_STRIDE = set_EDC_CH1_STRIDE;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
	 pipe->set_EDC_CH_CLIP_bottom = set_EDC_CH1_CLIP_bottom_clip;
	 pipe->set_EDC_CH_CLIP_right = set_EDC_CH1_CLIP_right_clip;
	 pipe->set_EDC_CH_CLIP_left = set_EDC_CH1_CLIP_left_clip;
	 pipe->set_EDC_CH_CLIP_top = set_EDC_CH1_CLIP_top_clip;
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/


	pipe->set_EDC_CH_CSCIDC_csc_en = set_EDC_CH1_CSCIDC_csc_en;
	pipe->set_EDC_CH_CSCIDC = set_EDC_CH1_CSCIDC;
	pipe->set_EDC_CH_CSCODC = set_EDC_CH1_CSCODC;
	pipe->set_EDC_CH_CSCP0 = set_EDC_CH1_CSCP0;
	pipe->set_EDC_CH_CSCP1 = set_EDC_CH1_CSCP1;
	pipe->set_EDC_CH_CSCP2 = set_EDC_CH1_CSCP2;
	pipe->set_EDC_CH_CSCP3 = set_EDC_CH1_CSCP3;
	pipe->set_EDC_CH_CSCP4 = set_EDC_CH1_CSCP4;

#if defined(CONFIG_OVERLAY_COMPOSE)
	pipe->set_OVC_CH_CSCIDC = set_OVC_CH1_CSCIDC;
	pipe->set_OVC_CH_CSCODC = set_OVC_CH1_CSCODC;
	pipe->set_OVC_CH_CSCP0 = set_OVC_CH1_CSCP0;
	pipe->set_OVC_CH_CSCP1 = set_OVC_CH1_CSCP1;
	pipe->set_OVC_CH_CSCP2 = set_OVC_CH1_CSCP2;
	pipe->set_OVC_CH_CSCP3 = set_OVC_CH1_CSCP3;
	pipe->set_OVC_CH_CSCP4 = set_OVC_CH1_CSCP4;
#endif //CONFIG_OVERLAY_COMPOSE

}

static void edc_overlay_pipe_init4ch2(struct edc_overlay_pipe *pipe)
{
	BUG_ON(pipe == NULL);

	pipe->edc_ch_info.cap.ckey_enable = 0;
	pipe->edc_ch_info.ckeymin = 0xffffcc;
	pipe->edc_ch_info.ckeymax = 0xffffec;

	pipe->edc_ch_info.cap.alpha_enable = 1;
	pipe->edc_ch_info.alp_src = EDC_ALP_PIXEL;
	pipe->edc_ch_info.alpha0 = 0x7f;
	pipe->edc_ch_info.alpha1 = 0x7f;

	pipe->edc_ch_info.cap.filter_enable = 1;
	pipe->edc_ch_info.cap.csc_enable = 1;
	/* added by gongyu for five edc layer compose, this is default config */
	pipe->req_info.overlay_num = OVERLAY_SURFACE_2;

	pipe->set_EDC_CHL_ADDR = set_EDC_CH2L_ADDR;
	pipe->set_EDC_CHR_ADDR = set_EDC_CH2R_ADDR;
	pipe->set_EDC_CH_CTL_ch_en = set_EDC_CH2_CTL_ch2_en;
	pipe->set_EDC_CH_CTL_secu_line = set_EDC_CH2_CTL_secu_line;
	pipe->set_EDC_CH_CTL_bgr = set_EDC_CH2_CTL_bgr;
	pipe->set_EDC_CH_CTL_pix_fmt = set_EDC_CH2_CTL_pix_fmt;
	pipe->set_EDC_CH_CTL_colork_en = set_EDC_CH2_CTL_colork_en;
	pipe->set_EDC_CH_COLORK_MIN = set_EDC_CH2_COLORK_MIN;
	pipe->set_EDC_CH_COLORK_MAX = set_EDC_CH2_COLORK_MAX;
	pipe->set_EDC_CH_XY = set_EDC_CH2_XY;
	pipe->set_EDC_CH_SIZE = set_EDC_CH2_SIZE;
	pipe->set_EDC_CH_STRIDE = set_EDC_CH2_STRIDE;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
	  pipe->set_EDC_CH_CLIP_bottom = set_EDC_CH2_CLIP_bottom_clip;
	  pipe->set_EDC_CH_CLIP_right = set_EDC_CH2_CLIP_right_clip;
	  pipe->set_EDC_CH_CLIP_left = set_EDC_CH2_CLIP_left_clip;
	  pipe->set_EDC_CH_CLIP_top = set_EDC_CH2_CLIP_top_clip;
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
	pipe->set_EDC_CH_CSCIDC_csc_en = set_EDC_CH2_CSCIDC_csc_en;
	pipe->set_EDC_CH_CSCIDC = set_EDC_CH2_CSCIDC;
	pipe->set_EDC_CH_CSCODC = set_EDC_CH2_CSCODC;
	pipe->set_EDC_CH_CSCP0 = set_EDC_CH2_CSCP0;
	pipe->set_EDC_CH_CSCP1 = set_EDC_CH2_CSCP1;
	pipe->set_EDC_CH_CSCP2 = set_EDC_CH2_CSCP2;
	pipe->set_EDC_CH_CSCP3 = set_EDC_CH2_CSCP3;
	pipe->set_EDC_CH_CSCP4 = set_EDC_CH2_CSCP4;

#if defined(CONFIG_OVERLAY_COMPOSE)
	pipe->set_OVC_CH_CSCIDC = set_OVC_CH2_CSCIDC;
	pipe->set_OVC_CH_CSCODC = set_OVC_CH2_CSCODC;
	pipe->set_OVC_CH_CSCP0 = set_OVC_CH2_CSCP0;
	pipe->set_OVC_CH_CSCP1 = set_OVC_CH2_CSCP1;
	pipe->set_OVC_CH_CSCP2 = set_OVC_CH2_CSCP2;
	pipe->set_OVC_CH_CSCP3 = set_OVC_CH2_CSCP3;
	pipe->set_OVC_CH_CSCP4 = set_OVC_CH2_CSCP4;
#endif //CONFIG_OVERLAY_COMPOSE

}

#if defined(CONFIG_OVERLAY_COMPOSE)
static void edc_overlay_pipe_init4crs(struct edc_overlay_pipe *pipe)
{
	BUG_ON(pipe == NULL);

	pipe->edc_ch_info.cap.ckey_enable = 0;
	pipe->edc_ch_info.ckeymin = 0xffffcc;
	pipe->edc_ch_info.ckeymax = 0xffffec;

	pipe->edc_ch_info.cap.alpha_enable = 1;
	pipe->edc_ch_info.alp_src = EDC_ALP_PIXEL;
	pipe->edc_ch_info.alpha0 = 0x7f;
	pipe->edc_ch_info.alpha1 = 0x7f;

	pipe->edc_ch_info.cap.filter_enable = 0;
	pipe->edc_ch_info.cap.csc_enable = 0;

	/* added by gongyu for five edc layer compose, this is default config */
	pipe->req_info.overlay_num = OVERLAY_SURFACE_5;
	pipe->set_EDC_CHL_ADDR = set_EDC_CRSL_ADDR;
	pipe->set_EDC_CHR_ADDR = set_EDC_CRSR_ADDR;
	pipe->set_EDC_CH_CTL_ch_en = set_EDC_CRS_CTL_en;
	pipe->set_EDC_CH_CTL_secu_line = set_EDC_CRS_CTL_secu_line;
	pipe->set_EDC_CH_CTL_bgr = set_EDC_CRS_CTL_bgr;
	pipe->set_EDC_CH_CTL_pix_fmt = set_EDC_CRS_CTL_pix_fmt;
	pipe->set_EDC_CH_CTL_colork_en = set_EDC_CRS_CTL_colork_en;
	pipe->set_EDC_CH_COLORK_MIN = set_EDC_CRS_COLORK_MIN;
	pipe->set_EDC_CH_COLORK_MAX = set_EDC_CRS_COLORK_MAX;
	pipe->set_EDC_CH_XY = set_EDC_CRS_XY;
	pipe->set_EDC_CH_SIZE = set_EDC_CRS_SIZE;
	pipe->set_EDC_CH_STRIDE = set_EDC_CRS_STRIDE;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
	 pipe->set_EDC_CH_CLIP_bottom = set_EDC_CRS_CLIP_bottom_clip;
	 pipe->set_EDC_CH_CLIP_right = set_EDC_CRS_CLIP_right_clip;
	 pipe->set_EDC_CH_CLIP_left = set_EDC_CRS_CLIP_left_clip;
	 pipe->set_EDC_CH_CLIP_top = set_EDC_CRS_CLIP_top_clip;
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
	pipe->set_EDC_CH_CSCIDC_csc_en = NULL;
	pipe->set_EDC_CH_CSCIDC = NULL;
	pipe->set_EDC_CH_CSCODC = NULL;
	pipe->set_EDC_CH_CSCP0 = NULL;
	pipe->set_EDC_CH_CSCP1 = NULL;
	pipe->set_EDC_CH_CSCP2 = NULL;
	pipe->set_EDC_CH_CSCP3 = NULL;
	pipe->set_EDC_CH_CSCP4 = NULL;

	pipe->set_OVC_CH_CSCIDC = NULL;
	pipe->set_OVC_CH_CSCODC = NULL;
	pipe->set_OVC_CH_CSCP0 = NULL;
	pipe->set_OVC_CH_CSCP1 = NULL;
	pipe->set_OVC_CH_CSCP2 = NULL;
	pipe->set_OVC_CH_CSCP3 = NULL;
	pipe->set_OVC_CH_CSCP4 = NULL;

}
static void edc_overlay_pipe_init4gnew1(struct edc_overlay_pipe *pipe)
{
	BUG_ON(pipe == NULL);

	pipe->edc_ch_info.cap.ckey_enable = 0;
	pipe->edc_ch_info.ckeymin = 0xffffcc;
	pipe->edc_ch_info.ckeymax = 0xffffec;

	pipe->edc_ch_info.cap.alpha_enable = 1;
	pipe->edc_ch_info.alp_src = EDC_ALP_PIXEL;
	pipe->edc_ch_info.alpha0 = 0x7f;
	pipe->edc_ch_info.alpha1 = 0x7f;

	pipe->edc_ch_info.cap.filter_enable = 0;
	pipe->edc_ch_info.cap.csc_enable = 0;

	/* added by gongyu for five edc layer compose */
	pipe->req_info.overlay_num = OVERLAY_SURFACE_3;

	pipe->set_EDC_CHL_ADDR = set_EDC_GNEW1_ADDR;
	pipe->set_EDC_CHR_ADDR = NULL;
	pipe->set_EDC_CH_CTL_ch_en = set_EDC_GNEW1_CTL_ch_en;
	pipe->set_EDC_CH_CTL_secu_line = NULL;
	pipe->set_EDC_CH_CTL_bgr = set_EDC_GNEW1_CTL_bgr;
	pipe->set_EDC_CH_CTL_pix_fmt = set_EDC_GNEW1_CTL_pix_fmt;
	pipe->set_EDC_CH_CTL_colork_en = NULL;
	pipe->set_EDC_CH_COLORK_MIN = NULL;
	pipe->set_EDC_CH_COLORK_MAX = NULL;
	pipe->set_EDC_CH_XY = set_EDC_GNEW1_XY;
	pipe->set_EDC_CH_SIZE = set_EDC_GNEW1_SIZE;
	pipe->set_EDC_CH_STRIDE = set_EDC_GNEW1_STRIDE;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
	 pipe->set_EDC_CH_CLIP_bottom = set_EDC_GNEW_CLIP_gnew1_bottom_clip;
	 pipe->set_EDC_CH_CLIP_right = set_EDC_GNEW_CLIP_gnew1_right_clip;
	 pipe->set_EDC_CH_CLIP_left = set_EDC_GNEW_CLIP_gnew1_left_clip;
	 pipe->set_EDC_CH_CLIP_top = set_EDC_GNEW_CLIP_gnew1_top_clip;
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
	pipe->set_EDC_CH_CSCIDC_csc_en = NULL;
	pipe->set_EDC_CH_CSCIDC = NULL;
	pipe->set_EDC_CH_CSCODC = NULL;
	pipe->set_EDC_CH_CSCP0 = NULL;
	pipe->set_EDC_CH_CSCP1 = NULL;
	pipe->set_EDC_CH_CSCP2 = NULL;
	pipe->set_EDC_CH_CSCP3 = NULL;
	pipe->set_EDC_CH_CSCP4 = NULL;

	pipe->set_OVC_CH_CSCIDC = NULL;
	pipe->set_OVC_CH_CSCODC = NULL;
	pipe->set_OVC_CH_CSCP0 = NULL;
	pipe->set_OVC_CH_CSCP1 = NULL;
	pipe->set_OVC_CH_CSCP2 = NULL;
	pipe->set_OVC_CH_CSCP3 = NULL;
	pipe->set_OVC_CH_CSCP4 = NULL;

}

static void edc_overlay_pipe_init4gnew2(struct edc_overlay_pipe *pipe)
{
	BUG_ON(pipe == NULL);

	pipe->edc_ch_info.cap.ckey_enable = 0;
	pipe->edc_ch_info.ckeymin = 0xffffcc;
	pipe->edc_ch_info.ckeymax = 0xffffec;

	pipe->edc_ch_info.cap.alpha_enable = 1;
	pipe->edc_ch_info.alp_src = EDC_ALP_PIXEL;
	pipe->edc_ch_info.alpha0 = 0x7f;
	pipe->edc_ch_info.alpha1 = 0x7f;

	pipe->edc_ch_info.cap.filter_enable = 0;
	pipe->edc_ch_info.cap.csc_enable = 0;

	/* added by gongyu for five edc layer compose */
	pipe->req_info.overlay_num = OVERLAY_SURFACE_4;

	pipe->set_EDC_CHL_ADDR = set_EDC_GNEW2_ADDR;
	pipe->set_EDC_CHR_ADDR = NULL;
	pipe->set_EDC_CH_CTL_ch_en = set_EDC_GNEW2_CTL_ch_en;
	pipe->set_EDC_CH_CTL_secu_line = NULL;
	pipe->set_EDC_CH_CTL_bgr = set_EDC_GNEW2_CTL_bgr;
	pipe->set_EDC_CH_CTL_pix_fmt = set_EDC_GNEW2_CTL_pix_fmt;
	pipe->set_EDC_CH_CTL_colork_en = NULL;
	pipe->set_EDC_CH_COLORK_MIN = NULL;
	pipe->set_EDC_CH_COLORK_MAX = NULL;
	pipe->set_EDC_CH_XY = set_EDC_GNEW2_XY;
	pipe->set_EDC_CH_SIZE = set_EDC_GNEW2_SIZE;
	pipe->set_EDC_CH_STRIDE = set_EDC_GNEW2_STRIDE;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 
      pipe->set_EDC_CH_CLIP_bottom = set_EDC_GNEW_CLIP_gnew2_bottom_clip;
	  pipe->set_EDC_CH_CLIP_right = set_EDC_GNEW_CLIP_gnew2_right_clip;
	pipe->set_EDC_CH_CLIP_left = set_EDC_GNEW_CLIP_gnew2_left_clip;
	pipe->set_EDC_CH_CLIP_top = set_EDC_GNEW_CLIP_gnew2_top_clip;
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/

	pipe->set_EDC_CH_CSCIDC_csc_en = NULL;
	pipe->set_EDC_CH_CSCIDC = NULL;
	pipe->set_EDC_CH_CSCODC = NULL;
	pipe->set_EDC_CH_CSCP0 = NULL;
	pipe->set_EDC_CH_CSCP1 = NULL;
	pipe->set_EDC_CH_CSCP2 = NULL;
	pipe->set_EDC_CH_CSCP3 = NULL;
	pipe->set_EDC_CH_CSCP4 = NULL;

	pipe->set_OVC_CH_CSCIDC = NULL;
	pipe->set_OVC_CH_CSCODC = NULL;
	pipe->set_OVC_CH_CSCP0 = NULL;
	pipe->set_OVC_CH_CSCP1 = NULL;
	pipe->set_OVC_CH_CSCP2 = NULL;
	pipe->set_OVC_CH_CSCP3 = NULL;
	pipe->set_OVC_CH_CSCP4 = NULL;

}
#endif //CONFIG_OVERLAY_COMPOSE

/* initialize infomation for 4 pipes of overlay*/
void edc_overlay_init(struct edc_overlay_ctrl *ctrl)
{
	struct edc_overlay_pipe *pipe = NULL;

	BUG_ON(ctrl == NULL);
    pr_info("%s enter  succ!\n",__func__);
	pipe = &ctrl->plist[OVERLAY_PIPE_EDC0_CH1];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_ALL,
	pipe->pipe_num = OVERLAY_PIPE_EDC0_CH1,
	pipe->edc_base = k3fd_reg_base_edc0,
	edc_overlay_pipe_init4ch1(pipe);

	pipe = &ctrl->plist[OVERLAY_PIPE_EDC0_CH2];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_PARTIAL,
	pipe->pipe_num = OVERLAY_PIPE_EDC0_CH2,
	pipe->edc_base = k3fd_reg_base_edc0,
	edc_overlay_pipe_init4ch2(pipe);

#if defined(CONFIG_OVERLAY_COMPOSE)
	pipe = &ctrl->plist[OVERLAY_PIPE_EDC0_GNEW1];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_PARTIAL,
	pipe->pipe_num = OVERLAY_PIPE_EDC0_GNEW1,
	pipe->edc_base = k3fd_reg_base_edc0,
	edc_overlay_pipe_init4gnew1(pipe);

	pipe = &ctrl->plist[OVERLAY_PIPE_EDC0_GNEW2];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_PARTIAL,
	pipe->pipe_num = OVERLAY_PIPE_EDC0_GNEW2,
	pipe->edc_base = k3fd_reg_base_edc0,
	edc_overlay_pipe_init4gnew2(pipe);

	pipe = &ctrl->plist[OVERLAY_PIPE_EDC0_CURSOR];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_PARTIAL,
	pipe->pipe_num = OVERLAY_PIPE_EDC0_CURSOR,
	pipe->edc_base = k3fd_reg_base_edc0,
	edc_overlay_pipe_init4crs(pipe);
#endif //CONFIG_OVERLAY_COMPOSE
	pipe = &ctrl->plist[OVERLAY_PIPE_EDC1_CH1];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_ALL,
	pipe->pipe_num = OVERLAY_PIPE_EDC1_CH1,
	pipe->edc_base = k3fd_reg_base_edc1,
	edc_overlay_pipe_init4ch1(pipe);

	pipe = &ctrl->plist[OVERLAY_PIPE_EDC1_CH2];
	pipe->pipe_type = OVERLAY_TYPE_CHCAP_PARTIAL,
	pipe->pipe_num = OVERLAY_PIPE_EDC1_CH2,
	pipe->edc_base = k3fd_reg_base_edc1,
	edc_overlay_pipe_init4ch2(pipe);
	pr_info("%s exit  succ!\n",__func__);
}

struct edc_overlay_pipe *edc_overlay_ndx2pipe(struct fb_info *info, int ndx)
{
	struct k3_fb_data_type *k3fd  = NULL;
	struct edc_overlay_ctrl *ctrl = NULL;
	struct edc_overlay_pipe *pipe = NULL;

	BUG_ON(info == NULL || info->par == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;

	if (ndx < 0 || ndx >= OVERLAY_PIPE_MAX)
		return NULL;

	ctrl = &k3fd->ctrl;
	pipe = &ctrl->plist[ndx];

	return pipe;
}

int edc_overlay_get(struct fb_info *info, struct overlay_info *req)
{
	struct edc_overlay_pipe *pipe = NULL;

	BUG_ON(info == NULL || req == NULL);

	pipe = edc_overlay_ndx2pipe(info, req->id);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", req->id);
		return -ENODEV;
	}

	/* *req = pipe->req_info; */
	memcpy(req, &pipe->req_info, sizeof(struct overlay_info));

	return 0;
}

int edc_overlay_set(struct fb_info *info, struct overlay_info *req)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL || req == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	pipe = edc_overlay_ndx2pipe(info, req->id);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", req->id);
		return -ENODEV;
	}

	memcpy(&pipe->req_info, req, sizeof(struct overlay_info));
	pipe->req_info.is_pipe_used = 1;

	return 0;
}

void edc_overlay_ch_unset(struct edc_overlay_pipe *pipe, u32 edc_base)
{
	if (NULL == pipe) {
        k3fb_loge("invalid pipe!");
        return;
    }
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 
	  pipe->set_EDC_CH_CLIP_bottom(edc_base,0x0);
      pipe->set_EDC_CH_CLIP_right(edc_base,0x0);
         pipe->set_EDC_CH_CLIP_left(edc_base,0x0);
         pipe->set_EDC_CH_CLIP_top(edc_base,0x0);
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/


	pipe->set_EDC_CHL_ADDR(edc_base, HISI_FRAME_BUFFER_BASE);
	pipe->set_EDC_CH_XY(edc_base, 0x0, 0x0);
	pipe->set_EDC_CH_SIZE(edc_base, 0x0, 0x0);
	pipe->set_EDC_CH_STRIDE(edc_base, 0x0);
	pipe->set_EDC_CH_CTL_bgr(edc_base, 0x0);
	pipe->set_EDC_CH_CTL_pix_fmt(edc_base, 0x0);
	pipe->set_EDC_CH_CTL_ch_en(edc_base, 0x0);

	if (pipe->set_EDC_CHR_ADDR) {
		pipe->set_EDC_CHR_ADDR(edc_base, 0x0);
	}	

	if (pipe->set_EDC_CH_CTL_colork_en) {
		pipe->set_EDC_CH_CTL_colork_en(edc_base, 0x0);
	}

	if (pipe->set_EDC_CH_COLORK_MIN) {
		pipe->set_EDC_CH_COLORK_MIN(edc_base, 0x0);
	}

	if (pipe->set_EDC_CH_COLORK_MAX) {
		pipe->set_EDC_CH_COLORK_MAX(edc_base, 0x0);
	}

	if (pipe->set_EDC_CH_CSCIDC_csc_en) {
		pipe->set_EDC_CH_CSCIDC_csc_en(edc_base, 0x0);
	}

	if (pipe->set_EDC_CH_CSCIDC) {
		pipe->set_EDC_CH_CSCIDC(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCODC) {
		pipe->set_EDC_CH_CSCODC(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCP0) {
		pipe->set_EDC_CH_CSCP0(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCP1) {
		pipe->set_EDC_CH_CSCP1(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCP2) {
		pipe->set_EDC_CH_CSCP2(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCP3) {
		pipe->set_EDC_CH_CSCP3(edc_base, 0x0);
	}
	if (pipe->set_EDC_CH_CSCP4) {
		pipe->set_EDC_CH_CSCP4(edc_base, 0x0);
	}

	if (pipe->pipe_type == OVERLAY_TYPE_CHCAP_ALL) {
		set_EDC_CH1_CTL_rot(edc_base, 0x0);
		set_EDC_CH1_SCL_IRES(edc_base, 0x0, 0x0);
		set_EDC_CH1_SCL_ORES(edc_base, 0x0, 0x0);

		set_EDC_CH1_SCL_HSP_hsc_en(edc_base, 0x0);
		set_EDC_CH1_SCL_HSP_hratio(edc_base, 0x0);
		set_EDC_CH1_SCL_HSP_hafir_en(edc_base, 0x0);
		set_EDC_CH1_SCL_HSP_hfir_en(edc_base, 0x0);
		
		set_EDC_CH1_SCL_VSP_vsc_en(edc_base, 0x0);
		set_EDC_CH1_SCL_VSR_vratio(edc_base, 0x0);
		set_EDC_CH1_SCL_VSP_vafir_en(edc_base, 0x0);
		set_EDC_CH1_SCL_VSP_vfir_en(edc_base, 0x0);		
	}

}

void edc_overlay_surface_unset(u32 edc_base, int overlay_num)
{
	struct st_overlay_surf_reg_func *ovly_surf = NULL;

	if (overlay_num < 0 || overlay_num > OVERLAY_SURFACE_MAX) {
		k3fb_loge("invalid overlay_num! \n");
        return;
	}
	
	ovly_surf = &(g_overlay_surf_func[overlay_num]);
	if (ovly_surf == NULL) {
		k3fb_loge("ovly_surf is null! \n");
        return;
	}

	if (ovly_surf->set_overlay_src_blend_en) {
		ovly_surf->set_overlay_src_blend_en(edc_base, 0x0);
	}

	if (ovly_surf->set_overlay_alpha_mode) {
		ovly_surf->set_overlay_alpha_mode(edc_base, 0x0);
	}

	if (ovly_surf->set_overlay_under_alpha_sel) {
		ovly_surf->set_overlay_under_alpha_sel(edc_base, 0x0);
	}

	if (ovly_surf->set_overlay_alpha_src) {
		ovly_surf->set_overlay_alpha_src(edc_base, 0x0);
	}

	if (ovly_surf->set_overlay_alpha_sel) {
		ovly_surf->set_overlay_alpha_sel(edc_base, 0x0);
	}

	if (ovly_surf->set_overlay_glp_alpha) {
		ovly_surf->set_overlay_glp_alpha(edc_base, 0x0, 0x0);
	}

	if (ovly_surf->set_overlay_top) {
		ovly_surf->set_overlay_top(edc_base, 0x1);
	}

	if (edc_base == k3fd_reg_base_edc0) {
		set_EDC_CROSS_CTRL_default_val(edc_base);
	}
}

int edc_overlay_unset(struct fb_info *info, int ndx)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	int i = 0;
	uint32_t ovly_surf_max = EDC1_OVERLAY_SURFACE_MAX;
	uint32_t overlay_num;

	BUG_ON(info == NULL || info->par == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	pipe = edc_overlay_ndx2pipe(info, ndx);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", ndx);
		return -ENODEV;
	}

	overlay_num = pipe->req_info.overlay_num;

#if defined(CONFIG_OVERLAY_COMPOSE)
	//unset it in pan display
	if (pipe->req_info.is_overlay_compose) {
	    
		/* pipe->req_info.is_overlay_compose = 0; */
		memset(&pipe->req_info, 0, sizeof(struct overlay_info));
		pipe->req_info.need_unset  = 1;
		pipe->req_info.overlay_num = overlay_num;

		return 0;
	}
#endif

	edc_base = pipe->edc_base;
	down(&k3fd->sem);
	memset(&pipe->req_info, 0, sizeof(struct overlay_info));

	if (!k3fd->panel_power_on) {
		up(&k3fd->sem);
		k3fb_logw("id=%d has power down!\n", ndx);
		return 0;
	}

	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
	#if CLK_SWITCH
		/* enable edc0 clk */
		clk_enable(k3fd->edc_clk);
		/* enable ldi clk */
		clk_enable(k3fd->ldi_clk);
	#endif
	}

	/* clear ch reg */
	edc_overlay_ch_unset(pipe, edc_base);

	if (k3fd_reg_base_edc0 == edc_base) {
 		ovly_surf_max = OVERLAY_SURFACE_MAX;
	}

	/* clear all ovlay_surface */
	for (i = 0; i < ovly_surf_max; i++) {
		edc_overlay_surface_unset(edc_base, i);
	}

    /* new add */
	/* clear the record map to invalid value */
    memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
    
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
	#if CLK_SWITCH
		/* disable edc0 clk */
		clk_disable(k3fd->edc_clk);
		/* disable ldi clk */
		clk_disable(k3fd->ldi_clk);
	#endif
	}

	up(&k3fd->sem);

	return 0;
}


#if defined(CONFIG_OVERLAY_COMPOSE)
#define EDC_BIT_MASK (0x1)
#define EDC_CFG_OK_BIT  (1)
#define CH1_ROTATE_BIT  (21)
#define CH1_EN_BIT  (24)
#define CH2_EN_BIT  (21)
#define CH2_FMT_BIT  (16)
#define CH2_FMT_MASK (0x7)
#define CRS_EN_BIT  (27)
#define GNEW1_EN_BIT  (27)
#define GNEW2_EN_BIT  (27)
#define EDC_CH_X_MASK (0xFFFFFFF)
#define EDC_CH_Y_MASK (0xFFF)
#define EDC_CH_BIT (16)
#define EDC_CH_WIDTH_MASK (0xFFFFFFF)
#define EDC_CH_HEIGHT_MASK (0xFFF)

#if defined(EDC_CH_CHG_SUPPORT)
enum {
    CH_CHG_DISABLE,
    CH_CHG_ENABLE
};
enum {
    CFG_SEL_EDC1,
    CFG_SEL_EDC0
};
#endif //EDC_CH_CHG_SUPPORT
volatile u32 edc_overlay_compose_get_cfg_ok(struct k3_fb_data_type *k3fd)
{
    volatile u32 edc_ctl;
    BUG_ON(k3fd == NULL);
    edc_ctl = inp32(k3fd->edc_base + EDC_DISP_CTL_OFFSET);
    return ((edc_ctl >> EDC_CFG_OK_BIT) & EDC_BIT_MASK);
}

volatile u32 edc_overlay_compose_reg_get_ch1_rotation(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_CTL_OFFSET);
    return ((ch1_ctl >> CH1_ROTATE_BIT) & 0x3);
}

volatile u32 edc_overlay_compose_get_ch1_state(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_CTL_OFFSET);
    return ((ch1_ctl >> CH1_EN_BIT) & EDC_BIT_MASK);
}

volatile u32 edc_overlay_compose_get_ch1_start_x(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_XY_OFFSET);
    return ((ch1_ctl & EDC_CH_X_MASK) >> EDC_CH_BIT);
}

volatile u32 edc_overlay_compose_get_ch1_start_y(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_XY_OFFSET);
    return (ch1_ctl & EDC_CH_Y_MASK);
}

volatile u32 edc_overlay_compose_get_ch1_width(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_SIZE_OFFSET);
    return (((ch1_ctl & EDC_CH_WIDTH_MASK) >> EDC_CH_BIT) +1);
}

volatile u32 edc_overlay_compose_get_ch1_height(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch1_ctl;
    BUG_ON(k3fd == NULL);
    ch1_ctl = inp32(k3fd->edc_base + EDC_CH1_SIZE_OFFSET);
    return ((ch1_ctl & EDC_CH_HEIGHT_MASK) +1);
}
volatile u32 edc_overlay_compose_get_ch2_state(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_CTL_OFFSET);
    return ((ch2_ctl >> CH2_EN_BIT) & EDC_BIT_MASK);
}

volatile u32 edc_overlay_compose_get_ch2_start_x(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_XY_OFFSET);
    return ((ch2_ctl & EDC_CH_X_MASK) >> EDC_CH_BIT);
}

volatile u32 edc_overlay_compose_get_ch2_start_y(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_XY_OFFSET);
    return (ch2_ctl & EDC_CH_Y_MASK);
}

volatile u32 edc_overlay_compose_get_ch2_width(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_SIZE_OFFSET);
    return (((ch2_ctl & EDC_CH_WIDTH_MASK) >> EDC_CH_BIT) +1);
}

volatile u32 edc_overlay_compose_get_ch2_height(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_SIZE_OFFSET);
    return ((ch2_ctl & EDC_CH_HEIGHT_MASK) +1);
}
volatile u32 edc_overlay_compose_get_ch2_fmt(struct k3_fb_data_type *k3fd)
{
    volatile u32 ch2_ctl;
    BUG_ON(k3fd == NULL);
    ch2_ctl = inp32(k3fd->edc_base + EDC_CH2_CTL_OFFSET);
    return ((ch2_ctl >> CH2_FMT_BIT) & CH2_FMT_MASK);
}

volatile u32 edc_overlay_compose_get_crs_state(struct k3_fb_data_type *k3fd)
{
    volatile u32 crs_ctl;
    BUG_ON(k3fd == NULL);
    crs_ctl = inp32(k3fd->edc_base + EDC_CRS_CTL_OFFSET);
    return ((crs_ctl >> CRS_EN_BIT) & EDC_BIT_MASK);
}
volatile u32 edc_overlay_compose_get_gnew1_state(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew1_ctl;
    BUG_ON(k3fd == NULL);
    gnew1_ctl = inp32(k3fd->edc_base + EDC_GNEW1_CTL_OFFSET);
    return ((gnew1_ctl >> GNEW1_EN_BIT) & EDC_BIT_MASK);
}

volatile u32 edc_overlay_compose_get_gnew1_start_x(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew1_ctl;
    BUG_ON(k3fd == NULL);
    gnew1_ctl = inp32(k3fd->edc_base + EDC_GNEW1_XY_OFFSET);
    return ((gnew1_ctl & EDC_CH_X_MASK) >> EDC_CH_BIT);
}

volatile u32 edc_overlay_compose_get_gnew1_start_y(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew1_ctl;
    BUG_ON(k3fd == NULL);
    gnew1_ctl = inp32(k3fd->edc_base + EDC_GNEW1_XY_OFFSET);
    return (gnew1_ctl & EDC_CH_Y_MASK);
}

volatile u32 edc_overlay_compose_get_gnew1_width(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew1_ctl;
    BUG_ON(k3fd == NULL);
    gnew1_ctl = inp32(k3fd->edc_base + EDC_GNEW1_SIZE_OFFSET);
    return (((gnew1_ctl & EDC_CH_WIDTH_MASK) >> EDC_CH_BIT) +1);
}

volatile u32 edc_overlay_compose_get_gnew1_height(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew1_ctl;
    BUG_ON(k3fd == NULL);
    gnew1_ctl = inp32(k3fd->edc_base + EDC_GNEW1_SIZE_OFFSET);
    return ((gnew1_ctl & EDC_CH_HEIGHT_MASK) +1);
}
volatile u32 edc_overlay_compose_get_gnew2_state(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew2_ctl;
    BUG_ON(k3fd == NULL);
    gnew2_ctl = inp32(k3fd->edc_base + EDC_GNEW2_CTL_OFFSET);
    return ((gnew2_ctl >> GNEW2_EN_BIT) & EDC_BIT_MASK);
}


volatile u32 edc_overlay_compose_get_gnew2_start_x(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew2_ctl;
    BUG_ON(k3fd == NULL);
    gnew2_ctl = inp32(k3fd->edc_base + EDC_GNEW2_XY_OFFSET);
    return ((gnew2_ctl & EDC_CH_X_MASK) >> EDC_CH_BIT);
}

volatile u32 edc_overlay_compose_get_gnew2_start_y(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew2_ctl;
    BUG_ON(k3fd == NULL);
    gnew2_ctl = inp32(k3fd->edc_base + EDC_GNEW2_XY_OFFSET);
    return (gnew2_ctl & EDC_CH_Y_MASK);
}

volatile u32 edc_overlay_compose_get_gnew2_width(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew2_ctl;
    BUG_ON(k3fd == NULL);
    gnew2_ctl = inp32(k3fd->edc_base + EDC_GNEW2_SIZE_OFFSET);
    return (((gnew2_ctl & EDC_CH_WIDTH_MASK) >> EDC_CH_BIT) +1);
}

volatile u32 edc_overlay_compose_get_gnew2_height(struct k3_fb_data_type *k3fd)
{
    volatile u32 gnew2_ctl;
    BUG_ON(k3fd == NULL);
    gnew2_ctl = inp32(k3fd->edc_base + EDC_GNEW2_SIZE_OFFSET);
    return ((gnew2_ctl & EDC_CH_HEIGHT_MASK) +1);
}
u32 edc_overlay_compose_get_state(struct fb_info *info, u32 pipe_id)
{
    struct edc_overlay_pipe *pipe = NULL;
    pipe = edc_overlay_ndx2pipe(info, pipe_id);
    if (pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!", pipe_id);
        return 0;
    }
    return pipe->req_info.is_overlay_compose;
}
bool edc_overlay_compose_get_overlay_0_ch(struct fb_info *info, u32 pipe_id)
{
    struct edc_overlay_pipe *pipe = NULL;
    pipe = edc_overlay_ndx2pipe(info, pipe_id);
    if (pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!", pipe_id);
        return 0;
    }
    return pipe->req_info.overlay_num == OVERLAY_SURFACE_1 ? true : false;
}

u32 edc_overlay_compose_get_cfg_disable(struct fb_info *info, u32 pipe_id)
{
    struct edc_overlay_pipe *pipe = NULL;
    pipe = edc_overlay_ndx2pipe(info, pipe_id);
    if (pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!", pipe_id);
        return 1;
    }
    return pipe->req_info.cfg_disable;
}

u32 edc_overlay_compose_get_ch1_rotation(struct fb_info *info, u32 pipe_id)
{
    struct edc_overlay_pipe *pipe = NULL;
    pipe = edc_overlay_ndx2pipe(info, pipe_id);
    if (pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!", pipe_id);
        return 0;
    }
    return pipe->req_info.rotation;
}

int edc_overlay_compose_set_cross(int overlay, int ch)
{
    int i;
    for (i = 0; i < (OVERLAY_SURFACE_MAX - 1); i++) {
        if (g_ovly2ch_map[i] == ch) {
            k3fb_loge("The cross channel[%d] overlay[%d] selected has already been used! at g_ovly2ch_map[%d] \n"
                , ch, overlay,i);
            return -EINVAL;
        }
    }
    if (g_ovly2ch_map[overlay] != OVERLAY_TO_CHANELL_MAP_INVALID) {
        k3fb_loge("Overlay[%d] has already selected channel[%d]"
            , overlay, g_ovly2ch_map[overlay]);
        return -EINVAL;
    }

    g_ovly2ch_map[overlay] = ch;
    return 0;
}

/* check the cross ctl req, make sure don't have same value for ovlys,
 * before display, have clear the cross ctl to 0 in edc_overlay_surface_unset function.
 */
void edc_overlay_compose_check_cross_ctl(u32   edc_base)
{
	int 	i;
	int 	j;
    int     ch_left[OVERLAY_SURFACE_MAX - 1];
    EDC_CROSS_CTL_VALUE     cross_value;
    

	for (i = 0; i < (OVERLAY_SURFACE_MAX - 1); i++) {
        ch_left[i] = i;        
    }

    // Find and record which channel has been not selected, update ch_left[]
    for (i = 0; i < (OVERLAY_SURFACE_MAX - 1); i++) {
        for (j = 0; j < (OVERLAY_SURFACE_MAX - 1); j++) {
            if (g_ovly2ch_map[i] == j) {
                if (ch_left[j] != OVERLAY_TO_CHANELL_MAP_INVALID) {
                    // Mark the channel that has been selected
                    // with OVERLAY_TO_CHANELL_MAP_INVALID
                    ch_left[j] = OVERLAY_TO_CHANELL_MAP_INVALID;                    
                } else {
                    // This channel already has been used,
                    // so clear this element of g_ovly2ch_map[]
                    // to fill with new distinct value later.
                    g_ovly2ch_map[i] = OVERLAY_TO_CHANELL_MAP_INVALID;                    
                }
            }
        }
    }
    
    j = 0;
    for (i = 0; i < (OVERLAY_SURFACE_MAX - 1); i++) {
        if (OVERLAY_TO_CHANELL_MAP_INVALID == g_ovly2ch_map[i]) {
            for (; j < (OVERLAY_SURFACE_MAX - 1); j++) {
                if (ch_left[j] != OVERLAY_TO_CHANELL_MAP_INVALID) {
                    g_ovly2ch_map[i] = ch_left[j++];             
                    break;
                }
            }            
        }                
    }

    cross_value.bits.ovly1_sel = g_ovly2ch_map[0];
    cross_value.bits.ovly2_sel = g_ovly2ch_map[1];
    cross_value.bits.ovly3_sel = g_ovly2ch_map[2];
    cross_value.bits.ovly4_sel = g_ovly2ch_map[3];
    outp32(edc_base + EDC_CROSS_CTL_OFFSET, cross_value.ul32);   
}

static void edc_overlay_compose_graphic_alpha_set(struct overlay_data *req, u32 edc_base, struct st_overlay_surf_reg_func  *pst_overlay_func)
{
    #define HWC_BLENDING_PREMULT (0x0105)
    #define HWC_BLENDING_COVERAGE (0x0405)

    int32_t blending;
    /* Get perpixelAlpha enabling state. */
    bool perpixelAlpha;
    /* Get plane alpha value. */
    u32 planeAlpha;

    if ((NULL == pst_overlay_func) || (NULL == req)) {
    	k3fb_loge("para is null,pst_overlay_func = %x, req = %x \n",(uint32_t)pst_overlay_func, (uint32_t)req);
		return;
    }

    blending =  req->src.blending;
    planeAlpha = blending >> 16;
    perpixelAlpha = isAlphaRGBType(req->src.format);

    k3fb_logi_display_debugfs("req->id = %d, blending = %d, perpixelAlpha = %d \n", req->id, blending, perpixelAlpha);

    switch (blending & 0xFFFF)
    {
		case HWC_BLENDING_PREMULT:
			SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, K3_ENABLE);

			if (perpixelAlpha) {
				SET_OVERLAY_ALPHA_MODE(pst_overlay_func, edc_base, EDC_ALP_PIXEL);				
				SET_OVERLAY_ALPHA_SRC(pst_overlay_func, edc_base, EDC_PIX_ALP_SRC_CH2);
				SET_OVERLAY_UNDER_ALPH_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_1);
				SET_OVERLAY_ALPHA_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_3);
			} else if (planeAlpha < 0xFF) {
				SET_OVERLAY_ALPHA_MODE(pst_overlay_func, edc_base, EDC_ALP_GLOBAL);
				SET_OVERLAY_GLP_ALPHA(pst_overlay_func, edc_base, planeAlpha, 0);
				
				SET_OVERLAY_UNDER_ALPH_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_1);
				SET_OVERLAY_ALPHA_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_0);
			} else {
				SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, K3_DISABLE);
			}
			break;
		case HWC_BLENDING_COVERAGE:
			SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, K3_ENABLE);

			if (perpixelAlpha) {
				SET_OVERLAY_ALPHA_MODE(pst_overlay_func, edc_base, EDC_ALP_PIXEL);				
				SET_OVERLAY_ALPHA_SRC(pst_overlay_func, edc_base, EDC_PIX_ALP_SRC_CH2);
				SET_OVERLAY_UNDER_ALPH_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_1);
				SET_OVERLAY_ALPHA_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_0);
			} else if (planeAlpha < 0xFF) {
				SET_OVERLAY_ALPHA_MODE(pst_overlay_func, edc_base, EDC_ALP_GLOBAL);
				SET_OVERLAY_GLP_ALPHA(pst_overlay_func, edc_base, planeAlpha, 0);

				SET_OVERLAY_UNDER_ALPH_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_1);
				SET_OVERLAY_ALPHA_SEL(pst_overlay_func, edc_base, EDC_ALP_MUL_COEFF_0);
			} else {
				SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, K3_DISABLE);
			}
			break;
		default:
			SET_OVERLAY_SRC_BLEND_EN(pst_overlay_func, edc_base, K3_DISABLE);
			break;
    }    
}

#if 0
static void edc_overlay_compose_partial_graphic_alpha_set(struct overlay_info *req_info, u32 edc_base)
{
    struct st_overlay_surf_reg_func  *pst_overlay_func = NULL;
    struct overlay_data 			  req;

    if (NULL == req_info) {
		k3fb_loge("req_info is null \n");
		return;
    }

    if (req_info->partial_overlay_num >= OVERLAY_SURFACE_MAX) {
		k3fb_loge("req_info overlay_num %d is overflow \n", req_info->partial_overlay_num);
		return;
    }

    pst_overlay_func = &(g_overlay_surf_func[req_info->partial_overlay_num]);

	req.id = req_info->partial_ch_num;
	req.src.blending = req_info->partial_blending;
	req.src.format   = req_info->partial_format;

    edc_overlay_compose_graphic_alpha_set(&req, edc_base, pst_overlay_func);
}


/* compose_pan_display, must be last channel, and this channel will not get overlay_num for cross switch
 * so, must calculate the overlay_num from the other three channel.
 *
 */

int edc_overlay_compose_pan_display_ovly_surf_set(struct overlay_info *req_info, u32 edc_base)
{
	int  ret = 0;
	struct st_overlay_surf_reg_func  *overlay_surf_func = NULL;

	if (NULL == req_info) {
		k3fb_loge("req_info is null \n");
		return -EINVAL;
	}

	/* set pan display ovly_num */
	if (req_info->partial_overlay_num >= OVERLAY_SURFACE_MAX) {
		k3fb_loge("overlay_num %d is overflow \n", req_info->partial_overlay_num);
		return -EOVERFLOW;
	}

	overlay_surf_func = &(g_overlay_surf_func[req_info->partial_overlay_num]);

	if (overlay_surf_func->set_overlay_cross_switch_sel) {

		ret =  edc_overlay_compose_set_cross(req_info->partial_overlay_num, req_info->partial_ch_num);
		if (ret < 0) {
		    /* clear the record map to invalid value */
            memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
			k3fb_loge("edc_overlay_compose_set_cross is error \n");
			return -EINVAL;
		}        
	}

	/* must sure the cross ctl config value don't have conflict */
	edc_overlay_compose_check_cross_ctl(edc_base);

	return ret;
}
#endif

static void edc_overlay_compose_ch_csc_unset(struct edc_overlay_pipe *pipe, u32 edc_base)
{
    if (pipe == NULL) {
        k3fb_loge("invalid pipe!");
        return;
    }

    if (pipe->set_EDC_CH_CSCIDC_csc_en) {
        pipe->set_EDC_CH_CSCIDC_csc_en(edc_base, 0x0);
    }
    if (pipe->set_OVC_CH_CSCIDC) {
        pipe->set_OVC_CH_CSCIDC(edc_base, 0x0, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCODC) {
        pipe->set_OVC_CH_CSCODC(edc_base, 0x0, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCP0) {
        pipe->set_OVC_CH_CSCP0(edc_base, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCP1) {
        pipe->set_OVC_CH_CSCP1(edc_base, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCP2) {
        pipe->set_OVC_CH_CSCP2(edc_base, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCP3) {
        pipe->set_OVC_CH_CSCP3(edc_base, 0x0, 0x0);
    }
    if (pipe->set_OVC_CH_CSCP4) {
        pipe->set_OVC_CH_CSCP4(edc_base, 0x0);
    }
}

void edc_overlay_compose_pre_unset(struct fb_info *info, int ndx)
{
    struct edc_overlay_pipe *pipe = NULL;

    BUG_ON(info == NULL);
    pipe = edc_overlay_ndx2pipe(info, ndx);
    if (pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!\n", ndx);
        return;
    }

    //unset it in cfg ok
    if (pipe->req_info.is_overlay_compose) {
        /* pipe->req_info.is_overlay_compose = 0; */
        memset(&pipe->req_info, 0, sizeof(struct overlay_info));
        pipe->req_info.need_unset = 1;
    }
}

static int edc_overlay_compose_pipe_unset(struct fb_info *info)
{
    struct edc_overlay_pipe *pipe = NULL;
    u32 edc_base = 0;
    int ch_id;
    
    BUG_ON(info == NULL || info->par == NULL);
    for (ch_id = 0; ch_id < OVERLAY_PIPE_MAX; ch_id++) {
        pipe = edc_overlay_ndx2pipe(info, ch_id);
        if (pipe == NULL) {
            k3fb_loge("id=%d not able to get pipe!", ch_id);
            return -ENODEV;
        }
        edc_base = pipe->edc_base;
        if (pipe->req_info.need_unset) {
            pipe->req_info.need_unset = 0;
            /* memset(&pipe->req_info, 0, sizeof(struct overlay_info)); */
			edc_overlay_ch_unset(pipe, edc_base);            

			/* clear overlay surface reg, don't clear pipe->req_info.overlay_num,
			 * because, if clear overlay_num, compose_play will get error overlay_num
			 */
            edc_overlay_surface_unset(edc_base, pipe->req_info.overlay_num);
        }
    }

    return 0;
}

int edc_overlay_compose_ch_unset(struct fb_info *info, int ndx)
{
	struct edc_overlay_pipe *pipe = NULL;
	u32 edc_base = 0;
    
    	BUG_ON(info == NULL || info->par == NULL);

       pipe = edc_overlay_ndx2pipe(info, ndx);
        if (pipe == NULL) {
            	k3fb_loge("id=%d not able to get pipe!", ndx);
            	return -ENODEV;
        }
        edc_base = pipe->edc_base;
        if (pipe->req_info.need_unset) {
            	pipe->req_info.need_unset = 0;
		edc_overlay_ch_unset(pipe, edc_base);            
            	edc_overlay_surface_unset(edc_base, pipe->req_info.overlay_num);
        }
    	return 0;
}
static int edc_overlay_compose_g2d_unset(struct fb_info *info)
{
    struct k3_fb_data_type *k3fd = NULL;
    struct edc_overlay_pipe *pipe = NULL;
    u32 edc_base = 0;
    int ch_id;

    BUG_ON(info == NULL || info->par == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;

    /* reset ovc state */
    for (ch_id = 0; ch_id < OVERLAY_PIPE_MAX; ch_id++) {
        pipe = edc_overlay_ndx2pipe(info, ch_id);
        if (pipe == NULL) {
            k3fb_loge("id=%d not able to get ovc pipe!", ch_id);
            return -ENODEV;
        }
        edc_base = pipe->edc_base;
        if (pipe->req_info.need_unset) {
            pipe->req_info.need_unset = 0;
        }

        if ((OVERLAY_PIPE_EDC0_CURSOR == ch_id) || (k3fd->graphic_ch == ch_id)) {
            edc_base = pipe->edc_base;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 
      pipe->set_EDC_CH_CLIP_bottom(edc_base,0x0);
      pipe->set_EDC_CH_CLIP_right(edc_base,0x0);
      pipe->set_EDC_CH_CLIP_left(edc_base,0x0);
      pipe->set_EDC_CH_CLIP_top(edc_base,0x0);
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/

            pipe->set_EDC_CHL_ADDR(edc_base, HISI_FRAME_BUFFER_BASE);
            pipe->set_EDC_CHR_ADDR(edc_base, HISI_FRAME_BUFFER_BASE);
            pipe->set_EDC_CH_XY(edc_base, 0x0, 0x0);
            pipe->set_EDC_CH_SIZE(edc_base, 0x0, 0x0);
            pipe->set_EDC_CH_STRIDE(edc_base, 0x0);
            pipe->set_EDC_CH_CTL_pix_fmt(edc_base, 0x0);
            pipe->set_EDC_CH_CTL_bgr(edc_base, 0x0);
            pipe->set_EDC_CH_CTL_colork_en(edc_base, 0x0);
            pipe->set_EDC_CH_CTL_ch_en(edc_base, 0x0);
        }
    }    
    return 0;
}

int edc_overlay_compose_pipe_unset_previous(struct fb_info *info, u32 previous_type, u32 previous_count)
{
    struct k3_fb_data_type *k3fd = NULL;

    BUG_ON(info == NULL || info->par == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;

    switch (previous_type) {
        case OVC_FULL:
            edc_overlay_compose_pipe_unset(info);
            break;
        case OVC_PARTIAL:
            edc_overlay_compose_pipe_unset(info);
            edc_overlay_compose_g2d_unset(info);
            break;
        case OVC_NONE:
            edc_overlay_compose_g2d_unset(info);
            break;
        default:
            k3fb_loge("previous_type default!!!");
            break;
    }
	//edc_overlay_compose_pipe_unset(info);
    return 0;
}

#if defined(EDC_CH_CHG_SUPPORT)
static int overlay_compose_get_edc1_hw(struct clk **edc_clk, struct regulator **edc_vcc)
{
    *edc_clk = clk_get(NULL, CLK_EDC1_NAME);
    if (IS_ERR(*edc_clk)) {
        k3fb_loge("failed to get edc1_clk!\n");
        return -EINVAL;
    }

    *edc_vcc = regulator_get(NULL,  VCC_EDC1_NAME);
    if (IS_ERR(*edc_vcc)) {
        k3fb_loge("failed to get edc1-vcc regulator\n");
        return -EINVAL;
    }
    return 0;
}

static void overlay_compose_edc1_power_on(struct k3_fb_data_type *k3fd)
{
    struct clk *edc1_clk;
    struct regulator *edc1_vcc;

    if (overlay_compose_get_edc1_hw(&edc1_clk, &edc1_vcc) < 0) {
        k3fb_loge("failed to get edc1 para.\n");
    }

    /* edc1 vcc */
    if (regulator_enable(edc1_vcc) != 0) {
        k3fb_loge("failed to enable edc-vcc regulator.\n");
    }

    /* edc clock enable */
    if (clk_enable(edc1_clk) != 0) {
        k3fb_loge("failed to enable edc1 clock.\n");
    }
    /* Note: call clk_set_rate after clk_set_rate, set edc clock rate to normal value */
    //edc1 clk uses edc0's rate !
    if (clk_set_rate(edc1_clk, EDC_CORE_CLK_RATE) != 0) {
        k3fb_loge("failed to set edc1 clk rate(%d).\n", EDC_CORE_CLK_RATE);
    }

}

void overlay_compose_edc1_power_off(void)
{
    struct clk *edc1_clk;
    struct regulator *edc1_vcc;

    if (overlay_compose_get_edc1_hw(&edc1_clk, &edc1_vcc) < 0) {
        k3fb_loge("failed to get edc1 para.\n");
    }
    /* edc clock gating */
    clk_disable(edc1_clk);

    /* edc1 vcc */
    if (regulator_disable(edc1_vcc) != 0) {
        k3fb_loge("failed to disable edc-vcc regulator.\n");
    }
}

int edc_overlay_compose_ch_chg_disable(struct k3_fb_data_type *k3fd, struct fb_info *info)
{
    //edc0
    struct edc_overlay_pipe *edc0_pipe = NULL;
    u32 edc0_base = 0;

    //edc1
    struct fb_info* info1 = k3_fb1_get_info();
    struct edc_overlay_pipe *edc1_pipe = NULL;
    u32 edc1_base = 0;


//edc0
    BUG_ON(info == NULL || info->par == NULL);

    if (!k3fd->ch_chg_flag) {
        return 0;
    }
    k3fd->ch_chg_flag = false;
    k3fd->ch_chg_power_off = true;


    edc0_pipe = edc_overlay_ndx2pipe(info, OVERLAY_PIPE_EDC0_CH2);
    if (edc0_pipe == NULL) {
        k3fb_loge("OVERLAY_PIPE_EDC0_CH2 not able to get pipe!");
        return -ENODEV;
    }
    edc0_base = edc0_pipe->edc_base;

//edc1
    BUG_ON(info1 == NULL || info1->par == NULL);
    edc1_pipe = edc_overlay_ndx2pipe(info1, OVERLAY_PIPE_EDC1_CH1);
    if (edc1_pipe == NULL) {
        k3fb_loge("OVERLAY_PIPE_EDC1_CH1 not able to get pipe!");
        return -ENODEV;
    }
    edc1_base = edc1_pipe->edc_base;

    edc1_pipe->set_EDC_CH_CTL_ch_en(edc1_base, K3_DISABLE);
    set_EDC_DISP_CTL_ch_chg(edc0_base, CH_CHG_DISABLE);
    set_EDC_DISP_CTL_cfg_ok_sel(edc0_base, CFG_SEL_EDC1);

    return 0;
}

static int edc_overlay_compose_ch_chg_enable(struct k3_fb_data_type *k3fd)
{
    if (k3fd->ch_chg_flag) {
        return 0;
    }
    k3fd->ch_chg_flag = true;
    overlay_compose_edc1_power_on(k3fd);
    return 0;
}
#endif //EDC_CH_CHG_SUPPORT

int edc_overlay_compose_play(struct fb_info *info, struct overlay_data *req)
{
    struct edc_overlay_pipe *pipe = NULL;
    struct k3_fb_data_type *k3fd = NULL;
    struct overlay_info *ov_info = NULL;
    struct st_overlay_surf_reg_func  *pst_overlay_func = NULL;
    struct k3fb_rect src;
    /*struct k3fb_rect logic_rect;*/
    struct k3fb_rect dst;  /* physic */
    u32 edc0_base = 0;
    struct edc_overlay_pipe *edc0_pipe = NULL;

    u32 edc_base = 0;

    int i = 0;
    int j = 0;
    s16 stSCLHorzCoef[8][8] = {{0},};
    s16 stSCLVertCoef[16][4] = {{0},};
    u32 scl_ratio_w = 0;
    u32 scl_ratio_h = 0;
    u32 addr = 0;

    #define MAX_EDC_W (1920)
    #define MAX_EDC_H (1200)
    u32 max_w;
    u32 max_h;

    bool is_rotate = false;
    u32 cfg_disable;

#if defined(EDC_CH_CHG_SUPPORT)
    //edc1
    struct k3_fb_data_type *k3fd1 = NULL;
    struct fb_info* info1 = k3_fb1_get_info();
    struct edc_overlay_pipe *edc1_pipe = NULL;
    u32 edc1_base = 0;
    bool ch_chg = false;
#endif //EDC_CH_CHG_SUPPORT

#if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
//addr align begin
    uint32_t left_clip = 0;
    uint32_t right_clip = 0;
    uint32_t top_clip = 0;
    uint32_t bottom_clip = 0;
    struct k3fb_rect src_temp;
//end
#endif

    BUG_ON(info == NULL || info->par == NULL || req == NULL);

#ifdef DEBUG_ON
    printk(
       "\nDUMP overlay play:\n"
       "type=%d\n"
       "phy_addr=%x\n"
       "actual_width=%d\n"
       "actual_height=%d\n"
       "format=%d\n"
       "s3d_format=%d\n"
       "stride=%d\n"
       "width=%d\n"
       "height=%d\n"
       "id=%d\n"
       "is_graphic=%d\n",
       req->src.type,
       req->src.phy_addr,
       req->src.actual_width,
       req->src.actual_height,
       req->src.format,
       req->src.s3d_format,
       req->src.stride,
       req->src.width,
       req->src.height,
       req->id,
       req->is_graphic);
#endif

    k3fd = (struct k3_fb_data_type *)info->par;
    edc0_pipe = edc_overlay_ndx2pipe(info, req->id);
    if (edc0_pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!", req->id);
        return -ENODEV;
    }
	
    //set to edc0
    pipe = edc0_pipe;

    /* stride 64byte odd align */
    if (!is64BytesOddAlign(FB_64BYTES_ODD_ALIGN_NONE, req->src.stride)) {
        k3fb_logw("stride NOT 64 bytes odd aligned, %x\n", req->src.stride);
        return -EINVAL;
    }

    if (pipe->req_info.dst_rect.w == 0 ||
        pipe->req_info.dst_rect.h == 0 ||
        pipe->req_info.src_rect.w == 0 ||
        pipe->req_info.src_rect.h == 0) {
        k3fb_logw("invalid width or height! dst(%d,%d), src(%d,%d)",
            pipe->req_info.dst_rect.w, pipe->req_info.dst_rect.h,
            pipe->req_info.src_rect.w, pipe->req_info.src_rect.h);
        return -EINVAL;
    }

    edc0_base = pipe->edc_base;
    //set to edc0
    edc_base = edc0_base;

    ov_info = &pipe->req_info;

    cfg_disable =  pipe->req_info.cfg_disable;
#ifdef DEBUG_ON
    printk("cfg_disable=%d\n",cfg_disable);
#endif

	if (((req->id)!= OVERLAY_PIPE_EDC0_CH1) && ((req->id)!= OVERLAY_PIPE_EDC1_CH1)) {
	    ov_info->rotation = EDC_ROT_NOP;
	}
	
    is_rotate = ((ov_info->rotation == EDC_ROT_90) || (ov_info->rotation == EDC_ROT_270));
    if (k3fd->panel_info.orientation == LCD_LANDSCAPE) {
        max_w = is_rotate ? MAX_EDC_H : MAX_EDC_W;
        max_h = is_rotate ? MAX_EDC_W : MAX_EDC_H;
    }
    else {
        max_w = is_rotate ? MAX_EDC_W : MAX_EDC_H;
        max_h = is_rotate ? MAX_EDC_H : MAX_EDC_W;
    }
    src.x = ov_info->src_rect.x;
    src.y = ov_info->src_rect.y;

    if ((ov_info->src_rect.w  * ov_info->src_rect.h) <= (max_w * max_h)) {
        src.w = ov_info->src_rect.w;
        src.h = ov_info->src_rect.h;
    }
    else {
        src.w = ov_info->src_rect.w = max_w;
        src.h = ov_info->src_rect.h = max_h;
    }

    dst = ov_info->dst_rect;

#ifdef DEBUG_ON
    printk("scr(%d,%d,%d,%d) ==> dst(%d,%d,%d,%d), clip_right=%d, clip_bottom = %d\n",src.x,src.y,src.w,src.h, dst.x,dst.y,dst.w,dst.h, ov_info->clip_right, ov_info->clip_bottom);
#endif

#if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
    computeAlignSrc(&(req->src), ov_info, &src, &src_temp);
    left_clip = src.x - src_temp.x;
    right_clip = ov_info->clip_right;
    top_clip = src.y - src_temp.y;
    bottom_clip = ov_info->clip_bottom;
    //printk("clip(%d,%d,%d,%d)\n", left_clip, top_clip, right_clip, bottom_clip);
    src.x = src_temp.x;
    src.y = src_temp.y;
    src.w = ov_info->src_rect.w = src_temp.w;
    src.h = ov_info->src_rect.h = src_temp.h;
    //printk("scr(%d,%d,%d,%d) ==> dst(%d,%d,%d,%d), clip_right=%d, clip_bottom = %d, left_clip\n",src.x,src.y,src.w,src.h, dst.x,dst.y,dst.w,dst.h, ov_info->clip_right, ov_info->clip_bottom, left_clip);
#endif

    /*computeDisplayRegion(&(req->src), k3fd->panel_info.orientation,
        &(ov_info->dst_rect), &logic_rect);
    logic2physicCoordinate(ov_info->rotation, &logic_rect, &dst);*/
    addr = computeDisplayAddr(&(req->src), ov_info->rotation, &src);
    //128bit(16byte) align
    if (addr & 0x0f) {
        k3fb_logw("addr NOT 64 bytes aligned, %x\n", addr);
        return -EINVAL;
    }

    if (!ov_info->is_pipe_used) {
        return 0;
    }

    if (!k3fd->panel_power_on) {
        return 0;
    }

    /* check edc_afifo_underflow_int interrupt */
    if ((inp32(edc_base + LDI_ORG_INT_OFFSET) & 0x4) == 0x4) {
        set_reg(edc_base + LDI_INT_CLR_OFFSET, 0x1, 1, 2);
        pr_notice("k3fb, %s: edc_afifo_underflow_int !!!\n", __func__);
    }

#if defined(EDC_CH_CHG_SUPPORT)
    //channel change flow
    if (ov_info->rotation) {
        if (!cfg_disable) {
            if (req->id == OVERLAY_PIPE_EDC0_CH2) {
                //replace edc1ch2
                ch_chg = true;
                edc_overlay_compose_ch_chg_enable(k3fd);
            } else {
                edc_overlay_compose_ch_chg_disable(k3fd, info);
            }
        }
    } else {
        edc_overlay_compose_ch_chg_disable(k3fd, info);
    }

    if (ch_chg) {
        pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_DISABLE);
        set_EDC_DISP_CTL_ch_chg(edc_base, CH_CHG_ENABLE);
        set_EDC_DISP_CTL_cfg_ok_sel(edc_base, CFG_SEL_EDC0);

        BUG_ON(info1 == NULL || info1->par == NULL);
        k3fd1 = (struct k3_fb_data_type *)info1->par;
        BUG_ON(k3fd1 == NULL);
        edc1_pipe = edc_overlay_ndx2pipe(info1, OVERLAY_PIPE_EDC1_CH1);
        if (edc1_pipe == NULL) {
            k3fb_loge("OVERLAY_PIPE_EDC1_CH1 not able to get pipe!");
            return -ENODEV;
        }
        edc1_base = edc1_pipe->edc_base;

        //set to edc1
        pipe = edc1_pipe;
        edc_base = edc1_base;

        pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);
    }
#endif //EDC_CH_CHG_SUPPORT

	/* set cross switch for this channel --start */
	pst_overlay_func = &(g_overlay_surf_func[pipe->req_info.overlay_num]);

	if (pst_overlay_func->set_overlay_cross_switch_sel) {
		if (edc_overlay_compose_set_cross(pipe->req_info.overlay_num, pipe->req_info.id) < 0) {
            /* clear the record map to invalid value */
            memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
			k3fb_loge("edc_overlay_compose_set_cross is error! \n");
			return -EINVAL;
		}
	}
	/* set cross switch for this channel --end */

    if (req->src.type != EDC_LEFT_ADDR) {
        if (pipe->set_EDC_CHR_ADDR) {
            pipe->set_EDC_CHR_ADDR(edc_base, addr);
        } else {
            k3fb_logw("ch don't support right buffer addr!!!\n");
        }
    }

    if (req->src.type != EDC_RIGHT_ADDR) {
        pipe->set_EDC_CHL_ADDR(edc_base, addr);
    }
/*begin support edc  pixels algin  modified by weiyi 00175802*/
   #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 
    // k3fb_loge("++++++++++++++++++++(%d)!\n", ov_info->rotation);
	switch (ov_info->rotation) {
	case EDC_ROT_NOP:
        pipe->set_EDC_CH_CLIP_left(edc_base, left_clip);
        pipe->set_EDC_CH_CLIP_top(edc_base, top_clip);
	    pipe->set_EDC_CH_CLIP_bottom(edc_base,ov_info->clip_bottom);
        pipe->set_EDC_CH_CLIP_right(edc_base,ov_info->clip_right);
		break;
	case EDC_ROT_90:
        pipe->set_EDC_CH_CLIP_bottom(edc_base, left_clip);
        pipe->set_EDC_CH_CLIP_left(edc_base, top_clip);
        pipe->set_EDC_CH_CLIP_top(edc_base,ov_info->clip_right);
        pipe->set_EDC_CH_CLIP_right(edc_base,ov_info->clip_bottom);
		break;
	case EDC_ROT_180:
        pipe->set_EDC_CH_CLIP_right(edc_base, left_clip);
        pipe->set_EDC_CH_CLIP_bottom(edc_base, top_clip);
        pipe->set_EDC_CH_CLIP_top(edc_base,ov_info->clip_bottom);
        pipe->set_EDC_CH_CLIP_left(edc_base,ov_info->clip_right);
		break;
	case EDC_ROT_270:
        pipe->set_EDC_CH_CLIP_top(edc_base, left_clip);
        pipe->set_EDC_CH_CLIP_right(edc_base, top_clip);
        pipe->set_EDC_CH_CLIP_left(edc_base,ov_info->clip_bottom);
        pipe->set_EDC_CH_CLIP_bottom(edc_base,ov_info->clip_right);
		break;
	default:
		k3fb_loge("Unsupported rotation(%d)!\n", ov_info->rotation);
		break;
	}
   #endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
   	
    pipe->set_EDC_CH_XY(edc_base, dst.x, dst.y);
    pipe->set_EDC_CH_SIZE(edc_base, ov_info->src_rect.w, ov_info->src_rect.h);
    pipe->set_EDC_CH_STRIDE(edc_base, req->src.stride);
    pipe->set_EDC_CH_CTL_pix_fmt(edc_base, req->src.format);
    pipe->set_EDC_CH_CTL_bgr(edc_base, req->src.bgr_fmt);
    pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);

    if (pipe->set_EDC_CH_CTL_colork_en) {
        pipe->set_EDC_CH_CTL_colork_en(edc_base, pipe->edc_ch_info.cap.ckey_enable);
    }
    if (pipe->edc_ch_info.cap.ckey_enable) {
        pipe->set_EDC_CH_COLORK_MIN(edc_base, pipe->edc_ch_info.ckeymin);
        pipe->set_EDC_CH_COLORK_MAX(edc_base, pipe->edc_ch_info.ckeymax);
    }

    if (pipe->pipe_type == OVERLAY_TYPE_CHCAP_ALL) {
        set_EDC_CH1_CTL_rot(edc_base, ov_info->rotation);
        #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
        /*JXT_ADD Fixed scale bug*/
        resetSizeByClip(&src.w, &src.h , ov_info->rotation, (left_clip + right_clip), (top_clip + bottom_clip), -1);
        /*Fiexed scale bug end*/
        #endif

        if (src.w == dst.w && src.h == dst.h) {
            set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_DISABLE);
            set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_DISABLE);
        } else {
            set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_ENABLE);
            set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_ENABLE);

            set_EDC_CH1_SCL_IRES(edc_base, src.w, src.h);
            set_EDC_CH1_SCL_ORES(edc_base, dst.w, dst.h);

            scl_ratio_w = (src.w << 12) / dst.w;
            scl_ratio_h = (src.h << 12) / dst.h;
            /*
			if ((scl_ratio_w > ((10<<12)/7)) && (scl_ratio_h < (1<<12))) {
				scl_ratio_w = ((10<<12)/7);
			} else if ((scl_ratio_h > ((10<<12)/7)) && (scl_ratio_w < (1<<12))) {
				scl_ratio_h = ((10<<12)/7);
			}
            */
            set_EDC_CH1_SCL_HSP_hratio(edc_base, scl_ratio_w);

            set_EDC_CH1_SCL_HSP_hafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
            set_EDC_CH1_SCL_HSP_hfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
            if (pipe->edc_ch_info.cap.filter_enable) {
                if (dst.w / src.w >= 1) {
                    memcpy(stSCLHorzCoef, gfxcoefficient8_cubic, sizeof(gfxcoefficient8_cubic));
                } else if ((dst.w / src.w == 0) && (((dst.w % src.w) << 12) / src.w) >= 0x800)  {
                    memcpy(stSCLHorzCoef, gfxcoefficient8_lanczos2_8tap, sizeof(gfxcoefficient8_lanczos2_8tap));
                }else {
				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
					return -EINVAL;
                }

                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 4; j++) {
	                    set_EDC_CH1_SCL_HPC(edc_base, i, j, (stSCLHorzCoef[i][j*2+1] << 16) | (stSCLHorzCoef[i][j*2] & 0xFFFF));
                    }
                }
            }

            set_EDC_CH1_SCL_VSR_vratio(edc_base, scl_ratio_h);
            set_EDC_CH1_SCL_VSP_vafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
            set_EDC_CH1_SCL_VSP_vfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
            if (pipe->edc_ch_info.cap.filter_enable) {
                if (dst.h / src.h >= 1) {
                    memcpy(stSCLVertCoef, gfxcoefficient4_cubic, sizeof(gfxcoefficient4_cubic));
                } else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0xC00)) {
                    memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_6M_a15, sizeof(gfxcoefficient4_lanczos2_6M_a15));
                } else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0x800) &&
                    (((dst.h % src.h) << 12) / src.h <= 0xC00)) {
                    memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_5M_a15, sizeof(gfxcoefficient4_lanczos2_5M_a15));
                }else {
				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
					return -EINVAL;
                }

                for (i = 0; i < 16; i++) {
                    for (j = 0; j < 2; j++) {
                        set_EDC_CH1_SCL_VPC(edc_base, i, j, (stSCLVertCoef[i][j*2+1] << 16) |
                        (stSCLVertCoef[i][j*2] & 0xFFFF));
                    }
                }
            }
        }
        #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT)
        /*JXT_ADD Fixed scale bug*/
        resetSizeByClip(&src.w, &src.h , ov_info->rotation, (left_clip + right_clip), (top_clip + bottom_clip), 1);
        /*Fiexed scale bug end*/
        #endif
    }

#if defined(EDC_CH_CHG_SUPPORT)
    if (ch_chg) {
        //set to edc0
        pipe = edc0_pipe;
        edc_base = edc0_base;
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 		
	  pipe->set_EDC_CH_CLIP_bottom(edc_base,ov_info->clip_bottom);
      pipe->set_EDC_CH_CLIP_right(edc_base,ov_info->clip_right);
	#endif
/*end support edc  pixels algin  modified by weiyi 00175802*/
	pipe->set_EDC_CH_XY(edc_base, dst.x, dst.y);
	pipe->set_EDC_CH_SIZE(edc_base, src.w, src.h); //edc0
	pipe->set_EDC_CH_CTL_pix_fmt(edc_base, req->src.format); //edc0
    }
#endif //EDC_CH_CHG_SUPPORT

    if (!req->is_graphic) {
        if (pipe->set_EDC_CH_CSCIDC_csc_en) {
            pipe->set_EDC_CH_CSCIDC_csc_en(edc_base, pipe->edc_ch_info.cap.csc_enable);
        }
        if (pipe->edc_ch_info.cap.csc_enable) {
#if 0
        /* 709 for HD */
            pipe->set_OVC_CH_CSCIDC(edc_base, 0x1f0, 0x180, 0x180);
            pipe->set_OVC_CH_CSCODC(edc_base, 0x0, 0x0, 0x0);
            pipe->set_OVC_CH_CSCP0(edc_base, 0x0, 0x129);
            pipe->set_OVC_CH_CSCP1(edc_base, 0x129, 0x1cb);
            pipe->set_OVC_CH_CSCP2(edc_base, 0x1f78, 0x1fca);
            pipe->set_OVC_CH_CSCP3(edc_base, 0x21c, 0x129);
            pipe->set_OVC_CH_CSCP4(edc_base, 0x0);
#else
            /* 601 for SD */
            pipe->set_OVC_CH_CSCIDC(edc_base, 0x1f0, 0x180, 0x180);
            pipe->set_OVC_CH_CSCODC(edc_base, 0x0, 0x0, 0x0);
            pipe->set_OVC_CH_CSCP0(edc_base, 0x0, 0x129);
            pipe->set_OVC_CH_CSCP1(edc_base, 0x129, 0x198);
            pipe->set_OVC_CH_CSCP2(edc_base, 0x1f30, 0x1f9c);
            pipe->set_OVC_CH_CSCP3(edc_base, 0x204, 0x129);
            pipe->set_OVC_CH_CSCP4(edc_base, 0x0);
#endif
        }
    }else {
        edc_overlay_compose_ch_csc_unset(pipe, edc_base);
    }

    edc_overlay_compose_graphic_alpha_set(req, edc_base, pst_overlay_func);
    k3_fb_gralloc_overlay_save_display_addr(k3fd, req->id, addr);

    if (!cfg_disable) {
    	edc_overlay_compose_check_cross_ctl(edc_base);
    	
#ifdef CONFIG_FOLLOWABILITY
        if (G_FOLLOW_FLAG_START == g_follow_flag)
        {
            long fb_currTime = k3fb_getCurrTime();
            pr_info("k3fb, TAG_Followability, %s: edc compose play current time is %ld ms!\n", __func__,fb_currTime);
            k3fb_listInsert(fb_currTime);
        }
#endif
    
    	/* clear the record map to invalid value */
        memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
    
        set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);
        

    }
    
    return 0;
}

/* partial compose never use to pan_display */
#if 0
int edc_overlay_compose_pan_display(struct fb_var_screeninfo *var, struct fb_info *info, int ch_num)
{
    struct edc_overlay_pipe *pipe = NULL;
    struct edc_overlay_pipe *pan_pipe = NULL;
    struct k3_fb_data_type *k3fd = NULL;
    u32 edc_base = 0;
    u32 display_addr = 0;
    int pipe_id;
    u32 pan_x;
    u32 pan_y;
    u32 pan_w;
    u32 pan_h;
    int pan_pipe_id;

    BUG_ON(var == NULL || info == NULL || info->par == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;

	/*
	 * pan_pipe_id: it is the channel numuber of stored the info of pan display,
	 *             is the channel that its overlay_num = 0.
	 *
	 * pan_pipe: it is the pipe that its pipe overlay_info struct contain the info that pan_display needed.
	 */
    pan_pipe_id = ch_num;
    pan_pipe = edc_overlay_ndx2pipe(info, pan_pipe_id);
    if (pan_pipe == NULL) {
        k3fb_loge("id=%d not able to get pipe!\n", pan_pipe_id);
        return -ENODEV;
    }

    pan_x = pan_pipe->req_info.partial_dst_rect.x;
    pan_y = pan_pipe->req_info.partial_dst_rect.y;
    pan_w = pan_pipe->req_info.partial_dst_rect.w;
    pan_h = pan_pipe->req_info.partial_dst_rect.h;

	/*
	 * pipe_id: it is the real channel for EDC Display, and the channel info is stored by pan_pipe.
	 * pipe: it is th real channel pipe for display, must use it for config the edc channel register.
	 */
    pipe_id = pan_pipe->req_info.partial_ch_num;
    pipe = edc_overlay_ndx2pipe(info, pipe_id);

    edc_base = pipe->edc_base;
    display_addr = info->fix.smem_start + info->fix.line_length * var->yoffset
        + var->xoffset * (var->bits_per_pixel >> 3);

    /* stride 64byte odd align */
    if (!is64BytesOddAlign(FB_64BYTES_ODD_ALIGN_NONE, info->fix.line_length)) {
        k3fb_logw("stride NOT 64 bytes odd aligned, %x!\n", info->fix.line_length);
        return -EINVAL;
    }

    if (!k3fd->panel_power_on) {
        return 0;
    }

    display_addr += pan_y * info->fix.line_length + pan_x * (var->bits_per_pixel >> 3);
    if (display_addr & 0x0F) {
        k3fb_logw("buf addr NOT 16 bytes aligned, %x!\n", display_addr);
        return -EINVAL;
    }

    /* set ovly_surf for pan display */
	if (edc_overlay_compose_pan_display_ovly_surf_set(&(pan_pipe->req_info), edc_base) < 0) {
		k3fb_loge("edc_overlay_compose_pan_display_ovly_surf_set is error,channel is  %s\n", pan_pipe->req_info.id);
        return -EINVAL;
	}
    if (k3fd->panel_info.s3d_frm != EDC_FRM_FMT_2D) {
    	if (pipe->set_EDC_CHR_ADDR) {
        	pipe->set_EDC_CHR_ADDR(edc_base, display_addr);
        }
    }
    pipe->set_EDC_CHL_ADDR(edc_base, display_addr);
    pipe->set_EDC_CH_STRIDE(edc_base, k3_fb_line_length(info->var.xres_virtual, info->var.bits_per_pixel >> 3));
    pipe->set_EDC_CH_XY(edc_base, pan_x, pan_y);
    pipe->set_EDC_CH_SIZE(edc_base, pan_w, pan_h);
    pipe->set_EDC_CH_CTL_pix_fmt(edc_base, k3fd->fb_imgType);
/*begin support edc  pixels algin  modified by weiyi 00175802*/
    #if defined(CONFIG_OVERLAY_PIXEL_ALIGN_SUPPORT) 
      pipe->set_EDC_CH_CLIP_bottom(edc_base,pan_pipe->req_info.clip_bottom_partial);
      pipe->set_EDC_CH_CLIP_right(edc_base, pan_pipe->req_info.clip_right_partial);
	#endif
/*begin support edc  pixels algin  modified by weiyi 00175802*/
   
    if (pipe->set_EDC_CH_CTL_colork_en) {
    	pipe->set_EDC_CH_CTL_colork_en(edc_base, pipe->edc_ch_info.cap.ckey_enable);
    }
    if (pipe->edc_ch_info.cap.ckey_enable) {
        pipe->set_EDC_CH_COLORK_MIN(edc_base, pipe->edc_ch_info.ckeymin);
        pipe->set_EDC_CH_COLORK_MAX(edc_base, pipe->edc_ch_info.ckeymax);
    }
    pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
    pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->fb_bgrFmt);
    pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);
    edc_overlay_compose_partial_graphic_alpha_set(&(pan_pipe->req_info), edc_base);

	/* clear the record map to invalid value */
    memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));

    set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	/* Add for B120 traceDot begin */ 
   #ifndef PC_UT_TEST_ON
    trace_dot(SF, "8", 0);
   #endif
	/* Add for B120 traceDot end */ 

    return 0;
}
#endif
#endif //CONFIG_OVERLAY_COMPOSE

int edc_overlay_play(struct fb_info *info, struct overlay_data *req)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	struct overlay_info *ov_info = NULL;
	struct k3fb_rect src;
	struct k3fb_rect dst;
	u32 edc_base = 0;
	int i = 0;
	int j = 0;
	s16 stSCLHorzCoef[8][8] = {{0},};
	s16 stSCLVertCoef[16][4] = {{0},};
	u32 scl_ratio_w = 0;
	u32 scl_ratio_h = 0;
	u32 addr = 0;

	BUG_ON(info == NULL || info->par == NULL || req == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	pipe = edc_overlay_ndx2pipe(info, req->id);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", req->id);
		return -ENODEV;
	}



	/* stride 64byte odd align */
	if (!is64BytesOddAlign(FB_64BYTES_ODD_ALIGN_NONE, req->src.stride)) {
		k3fb_logw("stride NOT 64 bytes odd aligned, %x.\n", req->src.stride);
		return -EINVAL;
	}

	if (req->src.actual_width == 0 ||
		req->src.actual_height == 0 ||
		pipe->req_info.dst_rect.w == 0 ||
		pipe->req_info.dst_rect.h == 0) {
		k3fb_logw("invalid width or height!img_actual(%d,%d), dst(%d,%d).\n",
			req->src.actual_width, req->src.actual_height,
			pipe->req_info.dst_rect.w, pipe->req_info.dst_rect.h);
		return -EINVAL;
	}

	edc_base = pipe->edc_base;
	ov_info = &pipe->req_info;

	src.x = 0;
	src.y = 0;
	src.w = req->src.actual_width;
	src.h = req->src.actual_height;
	dst = ov_info->dst_rect;

	if (((req->id)!= OVERLAY_PIPE_EDC0_CH1) && ((req->id)!= OVERLAY_PIPE_EDC1_CH1)) {
	    ov_info->rotation = EDC_ROT_NOP;
	}

	addr = computeDisplayAddr(&(req->src), ov_info->rotation, &src);

    	/* 16 byte align */
	if (addr & 0x0F) {
		k3fb_logw("buf NOT 16 bytes aligned, %x.\n", req->src.phy_addr);
		return -EINVAL;
	}
	
	if (!ov_info->is_pipe_used)
		return 0;

	down(&k3fd->sem);
	if (!k3fd->panel_power_on) {
		up(&k3fd->sem);
		return 0;
	}
    
    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == edc_base) {
        /* check edc_afifo_underflow_int interrupt */
        if ((inp32(edc_base + LDI_ORG_INT_OFFSET) & 0x4) == 0x4) {
            set_reg(edc_base + LDI_INT_CLR_OFFSET, 0x1, 1, 2);
		    k3fb_logw("edc_afifo_underflow_int !!!\n");
        }
    } else {
        /* check edc_afifo_underflow_int interrupt */
        if ((inp32(edc_base + LDI_ORG_INT_OFFSET + LDI1_OFFSET) & 0x4) == 0x4) {
            set_reg(edc_base + LDI_INT_CLR_OFFSET + LDI1_OFFSET, 0x1, 1, 2);
            k3fb_logw("edc_afifo_underflow_int !!!\n");
        }
    }
    /* Modified for EDC1 offset, end */

	if(req->src.type != EDC_LEFT_ADDR) {
		if (pipe->set_EDC_CHR_ADDR) {
			pipe->set_EDC_CHR_ADDR(edc_base, addr);
		} else {
			k3fb_logw("ch don't support right buffer addr!!!\n");
		}
	}

	if(req->src.type != EDC_RIGHT_ADDR) {
		pipe->set_EDC_CHL_ADDR(edc_base, addr);
	}
	pipe->set_EDC_CH_XY(edc_base, dst.x, dst.y);
	pipe->set_EDC_CH_SIZE(edc_base, req->src.actual_width, req->src.actual_height);
	pipe->set_EDC_CH_STRIDE(edc_base, req->src.stride);
	pipe->set_EDC_CH_CTL_pix_fmt(edc_base, req->src.format);
	pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
	pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);

	if(pipe->set_EDC_CH_CTL_colork_en) {
		pipe->set_EDC_CH_CTL_colork_en(edc_base, pipe->edc_ch_info.cap.ckey_enable);
	}
	if (pipe->edc_ch_info.cap.ckey_enable) {
		pipe->set_EDC_CH_COLORK_MIN(edc_base, pipe->edc_ch_info.ckeymin);
		pipe->set_EDC_CH_COLORK_MAX(edc_base, pipe->edc_ch_info.ckeymax);
	}

	/* set EDC0 Cross switch to default value */
	if(edc_base == k3fd_reg_base_edc0) {
    
        set_EDC_CROSS_CTRL_default_val(edc_base);
	}

	if (pipe->pipe_type == OVERLAY_TYPE_CHCAP_ALL) {
		set_EDC_CH1_CTL_rot(edc_base, ov_info->rotation);

		if (src.w == dst.w && src.h == dst.h) {
			set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_DISABLE);
			set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_DISABLE);
		} else {
			set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_ENABLE);
			set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_ENABLE);

			set_EDC_CH1_SCL_IRES(edc_base, src.w, src.h);
			set_EDC_CH1_SCL_ORES(edc_base, dst.w, dst.h);

			scl_ratio_w = (src.w << 12) / dst.w;
			scl_ratio_h = (src.h << 12) / dst.h;
            /*
			if ((scl_ratio_w > ((10<<12)/7)) && (scl_ratio_h < (1<<12))) {
				scl_ratio_w = ((10<<12)/7);
			} else if ((scl_ratio_h > ((10<<12)/7)) && (scl_ratio_w < (1<<12))) {
				scl_ratio_h = ((10<<12)/7);
			}
            */
			set_EDC_CH1_SCL_HSP_hratio(edc_base, scl_ratio_w);

			set_EDC_CH1_SCL_HSP_hafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
			set_EDC_CH1_SCL_HSP_hfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
			if (pipe->edc_ch_info.cap.filter_enable) {
				if (dst.w / src.w >= 1) {
					memcpy(stSCLHorzCoef, gfxcoefficient8_cubic, sizeof(gfxcoefficient8_cubic));
				} else if ((dst.w / src.w == 0) && (((dst.w % src.w) << 12) / src.w) >= 0x800)  {
					memcpy(stSCLHorzCoef, gfxcoefficient8_lanczos2_8tap, sizeof(gfxcoefficient8_lanczos2_8tap));
				}else {
				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
                    up(&k3fd->sem);
					return -EINVAL;
				}

				for (i = 0; i < 8; i++) {
					for (j = 0; j < 4; j++) {
						set_EDC_CH1_SCL_HPC(edc_base, i, j, (stSCLHorzCoef[i][j*2+1] << 16) |
							(stSCLHorzCoef[i][j*2] & 0xFFFF));
					}
				}
			}

			set_EDC_CH1_SCL_VSR_vratio(edc_base, scl_ratio_h);
			set_EDC_CH1_SCL_VSP_vafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
			set_EDC_CH1_SCL_VSP_vfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
			if (pipe->edc_ch_info.cap.filter_enable) {
				if (dst.h / src.h >= 1) {
					memcpy(stSCLVertCoef, gfxcoefficient4_cubic, sizeof(gfxcoefficient4_cubic));
				} else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0xC00)) {
					memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_6M_a15, sizeof(gfxcoefficient4_lanczos2_6M_a15));
				} else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0x800) &&
					(((dst.h % src.h) << 12) / src.h <= 0xC00)) {
					memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_5M_a15, sizeof(gfxcoefficient4_lanczos2_5M_a15));
				}else {
				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
                    up(&k3fd->sem);
					return -EINVAL;
				}

				for (i = 0; i < 16; i++) {
					for (j = 0; j < 2; j++) {
						set_EDC_CH1_SCL_VPC(edc_base, i, j, (stSCLVertCoef[i][j*2+1] << 16) |
							(stSCLVertCoef[i][j*2] & 0xFFFF));
					}
				}
			}
		}
	}

	if (!req->is_graphic) {
		pipe->set_EDC_CH_CSCIDC_csc_en(edc_base, pipe->edc_ch_info.cap.csc_enable);
		if (pipe->edc_ch_info.cap.csc_enable) {
		#if 0
			/* 709 for HD */
			pipe->set_EDC_CH_CSCIDC(edc_base, 0x0fc30180);
			pipe->set_EDC_CH_CSCODC(edc_base, 0x00000000);
			pipe->set_EDC_CH_CSCP0(edc_base, 0x00000100);
			pipe->set_EDC_CH_CSCP1(edc_base, 0x0100018a);
			pipe->set_EDC_CH_CSCP2(edc_base, 0x1f8b1fd2);
			pipe->set_EDC_CH_CSCP3(edc_base, 0x01d00100);
			pipe->set_EDC_CH_CSCP4(edc_base, 0x00000000);
		#else
			/* 601 for SD */
			pipe->set_EDC_CH_CSCIDC(edc_base, 0x0fc30180);
			pipe->set_EDC_CH_CSCODC(edc_base, 0x00000000);
			pipe->set_EDC_CH_CSCP0(edc_base, 0x00000100);
			pipe->set_EDC_CH_CSCP1(edc_base, 0x0100015e);
			pipe->set_EDC_CH_CSCP2(edc_base, 0x1faa1f4e);
			pipe->set_EDC_CH_CSCP3(edc_base, 0x01bb0100);
			pipe->set_EDC_CH_CSCP4(edc_base, 0x00000000);
		#endif
		}

		if (isAlphaRGBType(k3fd->fb_imgType)) {
			set_EDC_CH12_OVLY_alp_blend_en(edc_base, pipe->edc_ch_info.cap.alpha_enable);
			if (pipe->edc_ch_info.cap.alpha_enable) {
				set_EDC_CH12_OVLY_alp_src(edc_base, pipe->edc_ch_info.alp_src);
				if (pipe->edc_ch_info.alp_src == EDC_ALP_GLOBAL) {
					set_EDC_CH12_GLB_ALP_VAL(edc_base, pipe->edc_ch_info.alpha0, pipe->edc_ch_info.alpha1);
				} else {
					if (k3fd->graphic_ch == OVERLAY_PIPE_EDC0_CH2 ||
						k3fd->graphic_ch == OVERLAY_PIPE_EDC1_CH2) {
						set_EDC_CH12_OVLY_pix_alp_src(edc_base, EDC_PIX_ALP_SRC_CH2);
						set_EDC_CH12_OVLY_ch1_alp_sel(edc_base, EDC_ALP_MUL_COEFF_1);
						set_EDC_CH12_OVLY_ch2_alp_sel(edc_base, EDC_ALP_MUL_COEFF_0);
					} else {
						set_EDC_CH12_OVLY_pix_alp_src(edc_base, EDC_PIX_ALP_SRC_CH1);
						set_EDC_CH12_OVLY_ch1_alp_sel(edc_base, EDC_ALP_MUL_COEFF_0);
						set_EDC_CH12_OVLY_ch2_alp_sel(edc_base, EDC_ALP_MUL_COEFF_1);
					}
				}
			}
		} else {
			set_EDC_CH12_OVLY_alp_blend_en(edc_base, pipe->edc_ch_info.cap.alpha_enable);
			if (pipe->edc_ch_info.cap.alpha_enable) {
				set_EDC_CH12_OVLY_alp_src(edc_base, EDC_ALP_GLOBAL);
				set_EDC_CH12_GLB_ALP_VAL(edc_base, pipe->edc_ch_info.alpha0, pipe->edc_ch_info.alpha1);
			}
		}
	}

	/* clear the record map to invalid value */
    memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	up(&k3fd->sem);

	return 0;
}

int fb_pan_display_camera_debug(struct fb_var_screeninfo *var, struct fb_info *info, int id)
{   
    struct edc_overlay_pipe *pipe = NULL;
    struct k3_fb_data_type *k3fd = NULL; 
    struct k3fb_rect src;
    struct k3fb_rect dst;

   #if defined(CONFIG_OVERLAY_COMPOSE)
	u32 pre_type;
	u32 pre_count;
   #endif

    u32 edc_base = 0;
    u32 display_addr = 0;
    int i = 0;
    int j = 0;
    s16 stSCLHorzCoef[8][8] = {{0},};
    s16 stSCLVertCoef[16][4] = {{0},};
    u32 scl_ratio_w = 0;
    u32 scl_ratio_h = 0;

    BUG_ON(var == NULL || info == NULL || info->par == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;
    
    src.x = 0;
    src.y = 0;
    src.w = CAMERA_XRES_TEST;//320;
    src.h = CAMERA_YRES_TEST;//480;
    dst.w = k3fd->panel_info.xres;//720;
    dst.h = k3fd->panel_info.yres;//1280;
    #if defined(CONFIG_OVERLAY_COMPOSE)
	pre_type = k3fd->ovc_type;
	k3fd->ovc_type = OVC_NONE;
	pre_count = k3fd->ovc_ch_count;
	k3fd->ovc_ch_count = 1;
    #endif 

    pipe = edc_overlay_ndx2pipe(info, 0);
    if (pipe == NULL) {
       k3fb_loge("id=%d not able to get pipe!\n", id);
       return -ENODEV;
    }                                                                             	

    	edc_base = pipe->edc_base;
    	display_addr = info->fix.smem_start + info->fix.line_length * var->yoffset
    		+ var->xoffset * (var->bits_per_pixel >> 3);

    	if (display_addr & 0x0F) {
    		k3fb_logw("buf addr NOT 16 bytes aligned, %x!\n", display_addr);
    		return -EINVAL;
    	}

    	/* stride 64byte odd align */
    	if (!is64BytesOddAlign(FB_64BYTES_ODD_ALIGN_NONE, info->fix.line_length)) {
    		k3fb_logw("stride NOT 64 bytes odd aligned, %x!\n", info->fix.line_length);
    		return -EINVAL;
    	}

#ifdef DEBUG_ON
        pr_info("k3fb, %s:k3fd->panel_power_on: %d\n",__func__,k3fd->panel_power_on);
        pr_info("k3fb, %s:info->fix.line_length: %d\n",__func__,info->fix.line_length);
        pr_info("k3fb, %s:var->yoffset: %d\n",__func__,var->yoffset);
        pr_info("k3fb, %s:var->xoffset: %d\n",__func__,var->xoffset);
        pr_info("k3fb, %s:var->bits_per_pixel: %d\n",__func__,var->bits_per_pixel);
        pr_info("k3fb, %s:k3fd->fb_imgType: %d\n",__func__,k3fd->fb_imgType);
#endif
    	down(&k3fd->sem);
    	if (!k3fd->panel_power_on) {
    		up(&k3fd->sem);
    		return 0;
    	}

#if defined(CONFIG_OVERLAY_COMPOSE)
    	edc_overlay_compose_pipe_unset_previous(info, pre_type, pre_count);
#if defined(EDC_CH_CHG_SUPPORT)
    	edc_overlay_compose_ch_chg_disable(k3fd, info);
#endif //EDC_CH_CHG_SUPPORT
    	pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
    	set_EDC_CH12_OVLY_ch2_top(edc_base, EDC_CH2_TOP);
#endif //CONFIG_OVERLAY_COMPOSE

    	if (k3fd->panel_info.s3d_frm != EDC_FRM_FMT_2D) {
    		if (pipe->set_EDC_CHR_ADDR) {
    			pipe->set_EDC_CHR_ADDR(edc_base, display_addr);
    		}
    	}
    	pipe->set_EDC_CHL_ADDR(edc_base, display_addr);
    	pipe->set_EDC_CH_STRIDE(edc_base, info->fix.line_length);
    	pipe->set_EDC_CH_XY(edc_base, 0, 0);
    	pipe->set_EDC_CH_SIZE(edc_base, src.w, src.h );
    	pipe->set_EDC_CH_CTL_pix_fmt(edc_base, k3fd->fb_imgType);
        pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->fb_bgrFmt);
    	pipe->set_EDC_CH_CTL_colork_en(edc_base, pipe->edc_ch_info.cap.ckey_enable);
        pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->fb_bgrFmt);
    	if (pipe->edc_ch_info.cap.ckey_enable) {
    		pipe->set_EDC_CH_COLORK_MIN(edc_base, pipe->edc_ch_info.ckeymin);
    		pipe->set_EDC_CH_COLORK_MAX(edc_base, pipe->edc_ch_info.ckeymax);
    	}
    	pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);
    	if (pipe->pipe_type == OVERLAY_TYPE_CHCAP_ALL){
    		

    		if (src.w == dst.w && src.h == dst.h) {
    			set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_DISABLE);
    			set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_DISABLE);
    		} else {
    			set_EDC_CH1_SCL_HSP_hsc_en(edc_base, K3_ENABLE);
    			set_EDC_CH1_SCL_VSP_vsc_en(edc_base, K3_ENABLE);

    			set_EDC_CH1_SCL_IRES(edc_base, src.w, src.h);
    			set_EDC_CH1_SCL_ORES(edc_base, dst.w, dst.h);

    			scl_ratio_w = (src.w << 12) / dst.w;
    			scl_ratio_h = (src.h << 12) / dst.h;

    			set_EDC_CH1_SCL_HSP_hratio(edc_base, scl_ratio_w);

    			set_EDC_CH1_SCL_HSP_hafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
    			set_EDC_CH1_SCL_HSP_hfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
    			if (pipe->edc_ch_info.cap.filter_enable) {
    				if (dst.w / src.w >= 1) {
    					memcpy(stSCLHorzCoef, gfxcoefficient8_cubic, sizeof(gfxcoefficient8_cubic));
    				} else if ((dst.w / src.w == 0) && (((dst.w % src.w) << 12) / src.w) >= 0x800)  {
    					memcpy(stSCLHorzCoef, gfxcoefficient8_lanczos2_8tap, sizeof(gfxcoefficient8_lanczos2_8tap));
    				}else {
    				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
                        up(&k3fd->sem);
    					return -EINVAL;
    				}

    				for (i = 0; i < 8; i++) {
    					for (j = 0; j < 4; j++) {
    						set_EDC_CH1_SCL_HPC(edc_base, i, j, (stSCLHorzCoef[i][j*2+1] << 16) |
    							(stSCLHorzCoef[i][j*2] & 0xFFFF));
    					}
    				}
    			}

    			set_EDC_CH1_SCL_VSR_vratio(edc_base, scl_ratio_h);
    			set_EDC_CH1_SCL_VSP_vafir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
    			set_EDC_CH1_SCL_VSP_vfir_en(edc_base, pipe->edc_ch_info.cap.filter_enable);
    			if (pipe->edc_ch_info.cap.filter_enable) {
    				if (dst.h / src.h >= 1) {
    					memcpy(stSCLVertCoef, gfxcoefficient4_cubic, sizeof(gfxcoefficient4_cubic));
    				} else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0xC00)) {
    					memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_6M_a15, sizeof(gfxcoefficient4_lanczos2_6M_a15));
    				} else if ((dst.h / src.h == 0) && (((dst.h % src.h) << 12) / src.h >= 0x800) &&
    					(((dst.h % src.h) << 12) / src.h <= 0xC00)) {
    					memcpy(stSCLVertCoef, gfxcoefficient4_lanczos2_5M_a15, sizeof(gfxcoefficient4_lanczos2_5M_a15));
    				}else {
    				 	pr_err("k3fb, %s:  scale down ratio can'nt be less than 0.5! ratio = 0x%x\n", __func__, (((dst.w % src.w) << 12) / src.w));
                        up(&k3fd->sem);
    					return -EINVAL;
    				}

    				for (i = 0; i < 16; i++) {
    					for (j = 0; j < 2; j++) {
    						set_EDC_CH1_SCL_VPC(edc_base, i, j, (stSCLVertCoef[i][j*2+1] << 16) |
    							(stSCLVertCoef[i][j*2] & 0xFFFF));
    					}
    				}
    			}
    		}
    	}
    	
    set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);
    up(&k3fd->sem); 
    return 0;
    
}

int edc_fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info, int id)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	u32 display_addr = 0;
#if defined(CONFIG_OVERLAY_COMPOSE)
	u32 pre_type;
	u32 pre_count;
#endif

	BUG_ON(var == NULL || info == NULL || info->par == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;

#if defined(CONFIG_OVERLAY_COMPOSE)
	pre_type = k3fd->ovc_type;
	k3fd->ovc_type = OVC_NONE;
	pre_count = k3fd->ovc_ch_count;
	k3fd->ovc_ch_count = 1;
#endif /* CONFIG_OVERLAY_COMPOSE */
    if (g_debug_camerause == 1) {
    
       return fb_pan_display_camera_debug( var, info, 0 );
       
    }

	pipe = edc_overlay_ndx2pipe(info, id);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", id);
		return -ENODEV;
	}

	edc_base = pipe->edc_base;
	display_addr = info->fix.smem_start + info->fix.line_length * var->yoffset
		+ var->xoffset * (var->bits_per_pixel >> 3);

	if (display_addr & 0x0F) {
		k3fb_logw("buf addr NOT 16 bytes aligned, %x!\n", display_addr);
		return -EINVAL;
	}

	/* stride 64byte odd align */
	if (!is64BytesOddAlign(FB_64BYTES_ODD_ALIGN_NONE, info->fix.line_length)) {
		k3fb_logw("stride NOT 64 bytes odd aligned, %x!\n", info->fix.line_length);
		return -EINVAL;
	}

#ifdef DEBUG_ON
    pr_info("k3fb, %s:k3fd->panel_power_on: %d\n",__func__,k3fd->panel_power_on);
    pr_info("k3fb, %s:info->fix.line_length: %d\n",__func__,info->fix.line_length);
    pr_info("k3fb, %s:var->yoffset: %d\n",__func__,var->yoffset);
    pr_info("k3fb, %s:var->xoffset: %d\n",__func__,var->xoffset);
    pr_info("k3fb, %s:var->bits_per_pixel: %d\n",__func__,var->bits_per_pixel);
    pr_info("k3fb, %s:k3fd->fb_imgType: %d\n",__func__,k3fd->fb_imgType);
#endif

	down(&k3fd->sem);
	if (!k3fd->panel_power_on) {
		up(&k3fd->sem);
		return 0;
	}

#if defined(CONFIG_OVERLAY_COMPOSE)
	if (pre_type != k3fd->ovc_type) edc_overlay_compose_pipe_unset_previous(info, pre_type, pre_count);
#if defined(EDC_CH_CHG_SUPPORT)
	edc_overlay_compose_ch_chg_disable(k3fd, info);
#endif //EDC_CH_CHG_SUPPORT
	pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
	set_EDC_CH12_OVLY_ch2_top(edc_base, EDC_CH2_TOP);
#endif //CONFIG_OVERLAY_COMPOSE

	if (k3fd->panel_info.s3d_frm != EDC_FRM_FMT_2D) {
		if (pipe->set_EDC_CHR_ADDR) {
			pipe->set_EDC_CHR_ADDR(edc_base, display_addr);
		}
	}
	
	if (pipe->set_EDC_CH_CSCIDC_csc_en) {
		pipe->set_EDC_CH_CSCIDC_csc_en(edc_base, 0x0);
	}

	pipe->set_EDC_CHL_ADDR(edc_base, display_addr);
	pipe->set_EDC_CH_STRIDE(edc_base, info->fix.line_length);
	pipe->set_EDC_CH_XY(edc_base, 0, 0);
	pipe->set_EDC_CH_SIZE(edc_base, k3fd->panel_info.xres, k3fd->panel_info.yres);
	pipe->set_EDC_CH_CTL_pix_fmt(edc_base, k3fd->fb_imgType);
    pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->fb_bgrFmt);

	if (pipe->set_EDC_CH_CTL_colork_en) {
	    pipe->set_EDC_CH_CTL_colork_en(edc_base, pipe->edc_ch_info.cap.ckey_enable);
	}
	if (pipe->edc_ch_info.cap.ckey_enable) {
		pipe->set_EDC_CH_COLORK_MIN(edc_base, pipe->edc_ch_info.ckeymin);
		pipe->set_EDC_CH_COLORK_MAX(edc_base, pipe->edc_ch_info.ckeymax);
	}
	pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_ENABLE);

	if (0 == k3fd->index) {
		set_EDC_CROSS_CTRL_default_val(edc_base);
	}

	/* clear the record map to invalid value */
    memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

#if CONFIG_WFD_FBINFO
	/* wifi display begin */
	wfd_fbi.physical = display_addr;
	wfd_fbi.format = k3fd->fb_imgType;
	//save the fb index and the fb shatus
	wfd_fbi.fbslot = var->yoffset/var->yres;
 	wfd_fbi.fbstatus |= 1 << wfd_fbi.fbslot;	
	
	if ((EDC_ARGB_1555 == k3fd->fb_imgType) || (EDC_RGB_565 == k3fd->fb_imgType) ){
       	wfd_fbi.bpp = 2;
	}
	else if ((EDC_XRGB_8888 == k3fd->fb_imgType) || (EDC_ARGB_8888 == k3fd->fb_imgType)){
		wfd_fbi.bpp = 4;
	}
	/* wifi display end */
#endif
	/* Add for B120 traceDot begin */ 
	#ifndef PC_UT_TEST_ON
	trace_dot(SF, "8", 0);
	#endif
	/* Add for B120 traceDot end */ 

	up(&k3fd->sem);
	return 0;
}

int edc_fb_suspend(struct fb_info *info)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
	unsigned long dw_jiffies = 0;
	u32 tmp = 0;

	BUG_ON(info == NULL || info->par == NULL);
	pr_info("k3fb, %s: enter!\n", __func__);

	k3fd = (struct k3_fb_data_type *)info->par;
	pipe = edc_overlay_ndx2pipe(info, k3fd->graphic_ch);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", k3fd->graphic_ch);
		return -ENODEV;
	}

#ifdef CONFIG_DEBUG_FS
    if ((g_fb_lowpower_debug_flag & DEBUG_EDC_LOWPOWER_DISABLE) == DEBUG_EDC_LOWPOWER_DISABLE) {
        k3fb_logi(" edc suspend was disable");
        return 0;
    }

#endif

	edc_base = pipe->edc_base;

	down(&k3fd->sem);
	/* mask edc int and clear int state */
	set_EDC_INTE(edc_base, 0xFFFFFFFF);
	set_EDC_INTS(edc_base, 0x0);
	set_EDC_CH1_CTL_ch1_en(edc_base, K3_DISABLE);
	set_EDC_CH2_CTL_ch2_en(edc_base, K3_DISABLE);
#if defined(CONFIG_OVERLAY_COMPOSE)
	if (0 == k3fd->index) {
		set_EDC_GNEW1_CTL_ch_en(edc_base, K3_DISABLE);
		set_EDC_GNEW2_CTL_ch_en(edc_base, K3_DISABLE);
		set_EDC_CRS_CTL_en(edc_base, K3_DISABLE);
	}
#endif

	/* disable edc */
	set_EDC_DISP_CTL_edc_en(edc_base, K3_DISABLE);
	if (k3fd->panel_info.sbl_enable) {
		/* disable sbl */
		set_EDC_DISP_DPD_sbl_en(edc_base, K3_DISABLE);
	}
	/* edc cfg ok */
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == edc_base) {
        /* check outstanding */
        dw_jiffies = jiffies + HZ / 2;
        do {
            tmp = inp32(edc_base + EDC_STS_OFFSET);
            if ((tmp & 0x80000000) == 0x80000000) {
                break;
            }
        } while (time_after(dw_jiffies, jiffies));
    } else {
        /* check outstanding */
        dw_jiffies = jiffies + HZ / 2;
        do {
            tmp = inp32(edc_base + EDC_STS_OFFSET + EDC1_OFFSET);
            if ((tmp & 0x80000000) == 0x80000000) {
                break;
            }
        } while (time_after(dw_jiffies, jiffies));
    }
    /* Modified for EDC1 offset, end */

	/* edc clock gating */
	clk_disable(k3fd->edc_clk);
	clk_disable(k3fd->edc_axi_clk);	

    /* edc0 vcc */
	if (k3fd->index == 0) {   
	    clk_disable(k3fd->edc_cfg_clk);	
	    
        edc0_pwr_down_clk_dis();
        edc0_pwr_down_iso_en();
        edc0_pwr_down_clk_reset();
		edc_mtcos_disable(0);
	}

	/* edc1 mtcos disable in MHL */
	

#if defined(CONFIG_OVERLAY_COMPOSE)
	k3_fb_overlay_compose_data_clear(k3fd);
#endif

	up(&k3fd->sem);

    pr_info("k3fb, %s: exit!\n", __func__);

	return 0;
}

int edc_fb_resume(struct fb_info *info)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;
    u32 edc_clk = 0;

	BUG_ON(info == NULL || info->par == NULL);

	pr_info("%s enter! \n",__func__);

	k3fd = (struct k3_fb_data_type *)info->par;
	pipe = edc_overlay_ndx2pipe(info, k3fd->graphic_ch);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", k3fd->graphic_ch);
		return -ENODEV;
	}

	edc_base = k3fd->edc_base;

	down(&k3fd->sem);   
    

    if (k3fd->index == 0) {
#ifndef PC_UT_TEST_ON

        	k3fd->ddr_min_freq = DDR_FREQ_POWER_ON;
        	pm_qos_update_request(&k3fd->ovc_ddrminprofile, k3fd->ddr_min_freq);
		 k3fd->ddr_min_freq_saved = k3fd->ddr_min_freq;
#endif

    }
   	
    if (k3fd->index == 0) {
        edc_clk = EDC_CORE_CLK_RATE;		
    } else {
        edc_clk = EDC_CORE_CLK_RATE;//(k3fd->panel_info.yres < 720) ? EDC_CORE_CLK_RATE : ( k3fd->panel_info.clk_rate * 12 / 10);
    }

    /* 1: set clk division, and choose pll source */
	if (clk_set_rate(k3fd->edc_clk, edc_clk) != 0) {
	    k3fb_loge("failed to set edc clk rate(%d).\n", edc_clk);
    }

    /* set ldi clock rate */	
	if (k3_fb_set_clock_rate(k3fd, k3fd->ldi_clk, k3fd->panel_info.clk_rate) != 0) {
		k3fb_loge("failed to set ldi clk rate(%d).\n", k3fd->panel_info.clk_rate);		
	}

    /* 2: enable edc clk */
	if (clk_enable(k3fd->edc_clk) != 0) {
		k3fb_loge("failed to enable edc clock.\n");
	}

    /* 3: enable edc brother clk, pixel clk enable at ldi_on()
     *    dsi_cfg_clk, dphy_cfg_clk, dphy_ref_clk enable at mipi_dsi_on()
     */
	if (clk_enable(k3fd->edc_axi_clk) != 0) {
		k3fb_loge("failed to enable edc axi clock.\n");
	}      
	
    if (k3fd->index == 0) {
    
        if (clk_enable(k3fd->edc_cfg_clk) != 0) {
    		k3fb_loge("failed to enable edc cfg clock.\n");
    	} 
    
        /* 4: edc disreset */
        edc0_core_clk_disreset();
        edc0_pixel_clk_disreset();
        edc0_axi_clk_disreset();
        edc0_cfg_clk_disreset();

        /* 5: vcc enable */
    	if (edc_mtcos_enable(0) != 0) {
    		pr_err("k3fb, %s: failed to enable edc0_mtcos .\n", __func__);
    	}	

    	/* 6: power domain clk disreset */
    	edc0_pwr_down_clk_disreset();

    	/* 7: power domain iso dis */
    	edc0_pwr_down_iso_dis();

    	/* 8: power domain clk enable */
    	edc0_pwr_down_clk_en();
	}  
	
	
	/* edc init */
	if (pipe->set_EDC_CH_CTL_secu_line) {
		pipe->set_EDC_CH_CTL_secu_line(edc_base, EDC_CH_SECU_LINE);
	}
	pipe->set_EDC_CH_CTL_bgr(edc_base, k3fd->panel_info.bgr_fmt);
	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
		set_EDC_INTE(k3fd->edc_base, 0xFFFFFFFF);
	} else {
		set_EDC_INTE(k3fd->edc_base, 0xFFFFFF3F);
	}	
	set_EDC_INTS(edc_base, 0x0);
	set_EDC_DISP_DPD_disp_dpd(edc_base, 0x0);
	set_EDC_DISP_SIZE(edc_base, k3fd->panel_info.xres, k3fd->panel_info.yres);
	set_EDC_DISP_CTL_pix_fmt(edc_base, k3fd->panel_info.bpp);
	set_EDC_DISP_CTL_frm_fmt(edc_base, k3fd->panel_info.s3d_frm);
	set_EDC_DISP_CTL_endian(edc_base, EDC_ENDIAN_LITTLE);
	set_EDC_CH12_OVLY_ch2_top(edc_base, 1);
#if defined(CONFIG_OVERLAY_COMPOSE)
	if (0 == k3fd->index) {
		if ((OVERLAY_PIPE_EDC0_GNEW1 == pipe->pipe_num) || (OVERLAY_PIPE_EDC0_GNEW2 == pipe->pipe_num)) {
			if (k3fd->panel_info.s3d_frm > EDC_FRM_FMT_3D_CBC) {
				k3fb_loge("edc ch %d don't support this 3d format %d.\n", pipe->pipe_num,k3fd->panel_info.s3d_frm);
			}
		}
        /* set Cross switch to default value */		 
        set_EDC_CROSS_CTRL_default_val(edc_base);
	}
#endif
	/* clear the record map to invalid value */
    memset(&g_ovly2ch_map, OVERLAY_TO_CHANELL_MAP_INVALID, sizeof(g_ovly2ch_map));
	if (isNeedDither(k3fd)) {
		set_EDC_DISP_CTL_dither_en(edc_base, 1);
	} else {
		set_EDC_DISP_CTL_dither_en(edc_base, 0);
	}
	set_EDC_DISP_CTL_nrot_burst(edc_base, EDC_BURST8);
	set_EDC_DISP_CTL_crg_gt_en(edc_base, K3_ENABLE);

#if defined(CONFIG_OVERLAY_COMPOSE)
	set_EDC_DISP_CTL_outstding_dep(edc_base, 15);
#else
	set_EDC_DISP_CTL_outstding_dep(edc_base, 8);
#endif

	/*Set unflow_lev = 3072 for edc0 and unflow_lev = 640 for edc1*/
	if (k3fd->index == 0) {
		set_EDC_DISP_CTL_unflow_lev(edc_base, 0xC00);
	} else {
		set_EDC_DISP_CTL_unflow_lev(edc_base, 0x280);
	}

	set_EDC_DISP_CTL_edc_en(edc_base, K3_ENABLE);
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	up(&k3fd->sem);

	/* This spinlock will be UNLOCK in mipi_dsi_on */
	if (k3fd->index == 0) {
		if (k3fd->panel_info.frc_enable) {
			k3fd->panel_info.frame_rate = 60;
			k3fd->frc_threshold_count = 0;
			k3fd->frc_state = K3_FB_FRC_NONE_PLAYING;
			k3fd->frc_timestamp = jiffies;
		}

		if (k3fd->panel_info.esd_enable) {
			k3fd->esd_timestamp = jiffies;
			k3fd->esd_frame_count = 0;
		}
	}
    pr_info("%s exit! \n", __func__);

	return 0;
}

int sbl_bkl_set(struct k3_fb_data_type *k3fd, u32 value)
{
	u32 tmp = 0;

	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on)
		return 0;
		
    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == k3fd->edc_base) {
        tmp = inp32(k3fd->edc_base + EDC_DISP_DPD_OFFSET);
    } else {
        tmp = inp32(k3fd->edc_base + EDC_DISP_DPD_OFFSET + EDC1_OFFSET);
    }
    /* Modified for EDC1 offset, end */

	if ((tmp & REG_SBL_EN) == REG_SBL_EN) {
		k3fd->bl_level =  SBL_REDUCE_VALUE(value);
		set_SBL_BKL_LEVEL_L_bkl_level_l(k3fd->edc_base, k3fd->bl_level);
	}

	return 0;
}

int sbl_ctrl_set(struct k3_fb_data_type *k3fd)
{
	u32 tmp = 0;
	u32 edc_base = 0;
	u32 bkl_value = 0;
	struct k3_fb_panel_data *pdata = NULL;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;

    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == edc_base) {
        tmp = inp32(edc_base + EDC_DISP_DPD_OFFSET);
    } else {
        tmp = inp32(edc_base + EDC_DISP_DPD_OFFSET + EDC1_OFFSET);
    }
    /* Modified for EDC1 offset, end */
    
	if (K3_DISABLE == k3fd->sbl_enable) {
		if ((tmp & REG_SBL_EN) == REG_SBL_EN) {
			set_EDC_DISP_DPD_sbl_en(edc_base, K3_DISABLE);
			set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);
			
			if (pdata && pdata->set_cabc) {
				pdata->set_cabc(k3fd->pdev, K3_ENABLE);
			}
			k3_fb_set_backlight(k3fd, k3fd->bl_level_sbl);
		}
	} else {
		if ((tmp & REG_SBL_EN) != REG_SBL_EN) {
			bkl_value =  SBL_REDUCE_VALUE(k3fd->bl_level_sbl);
			set_SBL_BKL_LEVEL_L_bkl_level_l(edc_base, bkl_value);
			if (((k3fd->panel_info.type != PANEL_MIPI_CMD) || (k3fd->cmd_bl_can_set)) && (0 != k3fd->bl_level_sbl))
			k3_fb_set_backlight(k3fd,  bkl_value);
			set_EDC_DISP_DPD_sbl_en(edc_base, K3_ENABLE);
			set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);
			
			if (pdata && pdata->set_cabc) {
				pdata->set_cabc(k3fd->pdev, K3_DISABLE);
			}
		}
	}
	return 0;
}

static unsigned short apical_reg_table[] = {
	0x20, 0xff, 0x0f,
	0x1f, 0xb3, 0x0f,
	0x1e, 0x64, 0x0f,
	0x1d, 0x13, 0x0f, 
	0x1c, 0xc0, 0x0e,
	0x1b, 0x6b, 0x0e,
	0x1a, 0x13, 0x0e,
	0x19, 0xb9, 0x0d,
	0x18, 0x5c, 0x0d,
	0x17, 0xfd, 0x0c,
	0x16, 0x9b, 0x0c,
	0x15, 0x36, 0x0c,
	0x14, 0xce, 0x0b,
	0x13, 0x63, 0x0b,
	0x12, 0xf4, 0x0a,
	0x11, 0x82, 0x0a,
	0x10, 0x0c, 0x0a,
	0x0f, 0x93, 0x09,
	0x0e, 0x15, 0x09, 
	0x0d, 0x93, 0x08,
	0x0c, 0x0d, 0x08,
	0x0b, 0x82, 0x07,
	0x0a, 0xf3, 0x06,
	0x09, 0x5e, 0x06,
	0x08, 0xc3, 0x05,
	0x07, 0x23, 0x05,
	0x06, 0x7c, 0x04,
	0x05, 0xcf, 0x03,
	0x04, 0x1c, 0x03,
	0x03, 0x61, 0x02,
	0x02, 0x9e, 0x01,
	0x01, 0xd3, 0x00,
	0x00, 0x00, 0x00,
};

extern int apical_flags;
int sbl_ctrl_resume(struct k3_fb_data_type *k3fd)
{
	u32 tmp = 0;
	u32 edc_base = 0;
	u32 frame_width_l = 0;
	u32 frame_width_h = 0;
	u32 frame_height_l = 0;
	u32 frame_height_h = 0;

	unsigned int count = 0;
	unsigned int table_size;
	struct k3_fb_panel_data *pdata = NULL;
    pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;

	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;
	
	frame_width_l = (k3fd->panel_info.xres) & 0xff;
	frame_width_h = (k3fd->panel_info.xres >> 8) & 0xff;
	frame_height_l = (k3fd->panel_info.yres) & 0xff;
	frame_height_h = (k3fd->panel_info.yres >> 8) & 0xff;

	set_SBL_FRAME_WIDTH_L_frame_width_l(edc_base, frame_width_l);
	set_SBL_FRAME_WIDTH_H_frame_width_h(edc_base, frame_width_h);
	set_SBL_FRAME_HEIGHT_L_frame_height_l(edc_base, frame_height_l);
	set_SBL_FRAME_HEIGHT_H_frame_height_h(edc_base, frame_height_h);

	set_reg(edc_base + SBL_CTRL_REG0_OFFSET, 0x0b, 8, 0);
	set_reg(edc_base + SBL_CTRL_REG1_OFFSET, 0x22, 8, 0);
	set_reg(edc_base + SBL_HS_POS_LOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_HS_POS_HOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_VS_POS_LOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_VS_POS_HOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_IRIDIX_CTRL0_OFFSET, 0x07, 8, 0);
	set_reg(edc_base + SBL_IRIDIX_CTRL1_OFFSET, 0x46, 8, 0);
	set_reg(edc_base + SBL_VARIANCE_OFFSET, 0x41, 8, 0);

	set_reg(edc_base + SBL_SLOPE_MAX_OFFSET, 0x3c, 8, 0);
	set_reg(edc_base + SBL_SLOPE_MIN_OFFSET, 0x80, 8, 0);
	set_reg(edc_base + SBL_BLACK_LEVEL_LOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_BLACK_LEVEL_HOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_WHITE_LEVEL_LOFFSET, 0xff, 8, 0);
	set_reg(edc_base + SBL_WHITE_LEVEL_HOFFSET, 0x03, 8, 0);
	set_reg(edc_base + SBL_LIMIT_AMP_OFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_DITHER_OFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_LOGO_LEFT_OFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_LOGO_RIGHT_OFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_DITHER_CTRL_OFFSET, 0x03, 8, 0);
	set_reg(edc_base + SBL_STRENGTH_SEL_OFFSET, 0x01, 8, 0);
	set_reg(edc_base + SBL_STRENGTH_LIMIT_OFFSET, k3fd->panel_info.sbl.str_limit, 8, 0);
	if(apical_flags == 0x80)
		set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x80, 8, 0);
	else if(apical_flags == 0x20)
		set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x20, 8, 0);
	else if(apical_flags == 0x0)
	set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_OPTION_SEL_OFFSET, 0x02, 8, 0);

	set_reg(edc_base + SBL_BKL_MAX_LOFFSET, k3fd->panel_info.sbl.bl_max, 8, 0);
	set_reg(edc_base + SBL_BKL_MAX_HOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_CALIBRATION_A_OFFSET, k3fd->panel_info.sbl.cal_a, 8, 0);
	set_reg(edc_base + SBL_CALIBRATION_B_OFFSET, k3fd->panel_info.sbl.cal_b, 8, 0);
	set_reg(edc_base + SBL_DRC_IN_LOFFSET, 0x87, 8, 0);
	set_reg(edc_base + SBL_DRC_IN_HOFFSET, 0xba, 8, 0);
	set_reg(edc_base + SBL_T_FILT_CTRL_OFFSET, 0x0, 8, 0);

	set_reg(edc_base + SBL_BKL_LEVEL_HOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_AMBIENT_LIGHT_LOFFSET, 0x0, 8, 0);
	set_reg(edc_base + SBL_AMBIENT_LIGHT_HOFFSET, 0x2, 8, 0);
	set_reg(edc_base + SBL_START_CALC_OFFSET, 0x01, 8, 0);

	table_size = sizeof(apical_reg_table)/sizeof(unsigned short);
   	while (count < table_size) {
		set_reg(edc_base + SBL_OFFSET + 0x480, apical_reg_table[count], 8, 0);
		set_reg(edc_base + SBL_OFFSET + 0x484, apical_reg_table[count+1], 8, 0);
		set_reg(edc_base + SBL_OFFSET + 0x488, apical_reg_table[count+2], 8, 0);
		count += 3;
	}
    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == edc_base) {
        tmp = inp32(edc_base + EDC_DISP_DPD_OFFSET);
    } else {
        tmp = inp32(edc_base + EDC_DISP_DPD_OFFSET + EDC1_OFFSET);
    }
    /* Modified for EDC1 offset, end */
	if ((K3_ENABLE == k3fd->sbl_enable) && ((tmp & REG_SBL_EN) != REG_SBL_EN)) {
		k3fd->bl_level = SBL_REDUCE_VALUE(k3fd->bl_level_sbl);
		set_SBL_BKL_LEVEL_L_bkl_level_l(edc_base, k3fd->bl_level);
		set_EDC_DISP_DPD_sbl_en(edc_base, K3_ENABLE);
		set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);
		if (pdata && pdata->set_cabc) {
			pdata->set_cabc(k3fd->pdev, K3_DISABLE);
		}
	}
    else {
       if (pdata && pdata->set_cabc) {
			pdata->set_cabc(k3fd->pdev, K3_ENABLE);
		}
    }
	return 0;
}

int edc_fb_disable(struct fb_info *info)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(info == NULL || info->par == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	pipe = edc_overlay_ndx2pipe(info, k3fd->graphic_ch);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", k3fd->graphic_ch);
		return -ENODEV;
	}

	edc_base = pipe->edc_base;

	down(&k3fd->sem);
	pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_DISABLE);
	/* disable edc */
	set_EDC_DISP_CTL_edc_en(edc_base, K3_DISABLE);
	/* edc cfg ok */
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	up(&k3fd->sem);

	return 0;
}

int edc_fb_enable(struct fb_info *info)
{
	struct edc_overlay_pipe *pipe = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 edc_base = 0;

	BUG_ON(info == NULL || info->par == NULL);
	pr_info("k3fb, %s: enter!\n", __func__);
	k3fd = (struct k3_fb_data_type *)info->par;
	pipe = edc_overlay_ndx2pipe(info, k3fd->graphic_ch);
	if (pipe == NULL) {
		k3fb_loge("id=%d not able to get pipe!\n", k3fd->graphic_ch);
		return -ENODEV;
	}

	edc_base = pipe->edc_base;

	down(&k3fd->sem);

	pipe->set_EDC_CH_CTL_ch_en(edc_base, K3_DISABLE);
	/* disable edc */
	set_EDC_DISP_CTL_edc_en(edc_base, K3_ENABLE);
	/* edc cfg ok */
	set_EDC_DISP_CTL_cfg_ok(edc_base, EDC_CFG_OK_YES);

	up(&k3fd->sem);
    pr_info("k3fb, %s: exit!\n", __func__);
	return 0;
}

/* include/linux/k3_edc.h
 *
 * Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
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

#ifndef _K3_EDC_H_
#define _K3_EDC_H_

#include <linux/types.h>
#include <linux/fb.h>

#define K3FB_IOCTL_MAGIC 'm'
#define K3FB_CURSOR _IOW(K3FB_IOCTL_MAGIC, 130, struct fb_cursor)
#define K3FB_TIMING_SET _IOW(K3FB_IOCTL_MAGIC, 131, struct fb_var_screeninfo)
#define K3FB_VSYNC_INT_SET _IOW(K3FB_IOCTL_MAGIC, 132, unsigned int)

#define K3FB_OVERLAY_GET	_IOR(K3FB_IOCTL_MAGIC, 135, struct overlay_info)
#define K3FB_OVERLAY_SET	_IOWR(K3FB_IOCTL_MAGIC, 136, struct overlay_info)
#define K3FB_OVERLAY_UNSET	_IOW(K3FB_IOCTL_MAGIC, 137, unsigned int)
#define K3FB_OVERLAY_PLAY	_IOW(K3FB_IOCTL_MAGIC, 138, struct overlay_data)

#define K3FB_FRC_SET		_IOW(K3FB_IOCTL_MAGIC, 139, char *)
#define K3FB_G2D_SET_FREQ	_IOW(K3FB_IOCTL_MAGIC, 140, char *)
#define K3FB_SBL_SET_VALUE	_IOW(K3FB_IOCTL_MAGIC, 141, int)

#define K3FB_OVC_CHECK_DDR_FREQ _IOW(K3FB_IOCTL_MAGIC, 142, char *) /* CONFIG_OVERLAY_COMPOSE */
#define K3FB_G2D_LOCK_FREQ	_IOW(K3FB_IOCTL_MAGIC, 143, int)
/* v9r1 bbit test macro  start */
#define FB_BBIT_TEST_ENABLE    1

#define IS_EDC1(edc_base)     (k3fd_reg_base_edc1 == edc_base)

/* for v9r1 bbit test */
#if FB_BBIT_TEST_ENABLE
#define K3FB_WRITE_EDC_REG  _IOWR(K3FB_IOCTL_MAGIC, 201, struct overlay_reg_info)
#define K3FB_READ_EDC_REG  _IOR(K3FB_IOCTL_MAGIC, 202, struct overlay_reg_info)

#endif

//Multi Resolution====begin
/*for mutilresolution switch */
#define K3FB_RESOLUTION_SWITCH _IOWR(K3FB_IOCTL_MAGIC, 301, int)
#define K3FB_RESOLUTION_UPDATE _IOWR(K3FB_IOCTL_MAGIC, 302, int)
//Multi Resolution====end

#ifdef CONFIG_FOLLOWABILITY
#define K3FB_FOLLOW_START           _IOW(K3FB_IOCTL_MAGIC, 500, void *)
#define K3FB_FOLLOW_STOP	        _IOW(K3FB_IOCTL_MAGIC, 501, void *)
#define K3FB_FIRST_DISP_TIME	    _IOR(K3FB_IOCTL_MAGIC, 502, long * )
#define K3FB_GET_EVERY_DISP_TIME    _IOR(K3FB_IOCTL_MAGIC, 503, long *)
#define K3FB_GET_AVE_FRAME_RATE	    _IOR(K3FB_IOCTL_MAGIC, 504, long *)
#define K3FB_CLEAR_FRAME_RECORD	    _IOW(K3FB_IOCTL_MAGIC, 505,  void *)
#endif 

#ifdef CONFIG_FB_CHECK_MIPI_TR
#define K3FB_CHECK_MIPI_TR    _IOR(K3FB_IOCTL_MAGIC, 701, int)
#endif

#ifdef CONFIG_FB_SET_INVERSION
#define K3FB_SET_INVERSION    _IOW(K3FB_IOCTL_MAGIC, 702, void *)
#endif

#ifdef CONFIG_FB_MIPI_DETECT
#define K3FB_MIPI_DETECT      _IOR(K3FB_IOCTL_MAGIC, 703, int)
#endif

/* wifi display begin modified by huangzhouxiang */
#if CONFIG_WFD_FBINFO
#define INVALID_BUFF_SLOT -1

#define K3FB_WIFI_DISP_GET_FBI       _IOR(K3FB_IOCTL_MAGIC, 506,  wfd_fb_info)
#define K3FB_WIFI_DISP_CLEAR_FBSTATUS       _IOR(K3FB_IOCTL_MAGIC, 507,  wfd_fb_info)
#define K3FB_NSD_SET    _IOWR(K3FB_IOCTL_MAGIC, 601, void *)
typedef struct wfd_fb_info_ {
      u32 physical;
      u32 xres;
      u32 yres;
      u32 xstride;
      u32 ystride;
      u32 bpp;
      u32 format;
	  u32 fbslot;
      u32 fbstatus;
}wfd_fb_info;

extern wfd_fb_info wfd_fbi;
/* wifi display end modified by huangzhouxiang*/
#endif
enum {
	K3_DISABLE = 0,
	K3_ENABLE,
};

enum {
	EDC_ARGB_1555 = 0,
	EDC_RGB_565,
	EDC_XRGB_8888,
	EDC_ARGB_8888,
	EDC_YUYV_I,
	EDC_UYVY_I,
	EDC_YVYU_I,
	EDC_VYUY_I,
};

enum {
	EDC_OUT_RGB_565 = 0,
	EDC_OUT_RGB_666,
	EDC_OUT_RGB_888,
};

enum {
	EDC_ROT_NOP = 0,
	EDC_ROT_180,
	EDC_ROT_90,
	EDC_ROT_270,

};

enum {
	EDC_RGB = 0,
	EDC_BGR,
};

enum {
	EDC_ENDIAN_LITTLE = 0,
	EDC_ENDIAN_BIG,
};

enum {
	EDC_BURST8 = 0,
	EDC_BURST16,
};

enum {
	EDC_CFG_OK_NO = 0,
	EDC_CFG_OK_YES,
};

enum {
	EDC_CFG_OK_EDC2 = 0,
	EDC_CFG_OK_EDC1,
};

enum {
	EDC_LINEAR = 0,
	EDC_TILE,
};

enum {
	EDC_TILE_FMT_TITLE = 0,
	EDC_TILE_FMT_SUPPER_TITLE,
	EDC_TILE_FMT_MULTI_TITLE,
	EDC_TILE_FMT_SUPPERMULTI_TITLE,
};

enum {
	EDC_ALP_GLOBAL = 0,
	EDC_ALP_PIXEL,
};

enum {
	EDC_PIX_ALP_SRC_CH2 = 0,
	EDC_PIX_ALP_SRC_CH1,
};

enum {
	EDC_ALP_MUL_COEFF_0 = 0,	/* alpha */
	EDC_ALP_MUL_COEFF_1,		/* 1-alpha */
	EDC_ALP_MUL_COEFF_2,		/* 0 */
	EDC_ALP_MUL_COEFF_3,		/* 1 */
};

enum {
	EDC_CH2_BOTTOM = 0,
	EDC_CH2_TOP,
};

enum {
	EDC_FRM_FMT_2D = 0,
	EDC_FRM_FMT_3D_SBS,
	EDC_FRM_FMT_3D_TTB,
	EDC_FRM_FMT_3D_CBC,
	EDC_FRM_FMT_3D_LBL,
	EDC_FRM_FMT_3D_QUINCUNX,
	EDC_FRM_FMT_3D_FBF,
};

enum {
	LDI_DISP_MODE_NOT_3D_FBF = 0,
	LDI_DISP_MODE_3D_FBF,
};

enum {
	LDI_TEST = 0,
	LDI_WORK,
};


/******************************************************************************/

enum {
	EDC_OVERLAY_ROTATION_DEG = 1,
	EDC_OVERLAY_DITHER = 3,
	EDC_OVERLAY_TRANSFORM = 4,
};

enum {
	EDC_LEFT_ADDR = 0,
	EDC_RIGHT_ADDR,
	EDC_ALL_ADDR,
};

struct k3fb_rect {
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
};

#ifdef CONFIG_FB_SET_INVERSION
enum INVERSION_TYPE {
    INVERSION_TYPE_1DOT = 0,
    INVERSION_TYPE_2DOT,
    INVERSION_TYPE_COLUMN,
    INVERSION_TYPE_ROW,
    INVERSION_TYPE_FRAME,
    INVERSION_TYPE_NUM,
};
#endif

struct k3fb_img {
	uint32_t type;
	uint32_t phy_addr;
	uint32_t actual_width;
	uint32_t actual_height;
	uint32_t format;
	uint32_t s3d_format;
	uint32_t stride;
	uint32_t width;
	uint32_t height;
	uint32_t is_video;
	/* CONFIG_OVERLAY_COMPOSE start */
    uint32_t compose_mode;
	uint32_t bgr_fmt;
	int32_t blending;
	int32_t acquire_fence;
	int32_t release_fence;
	/* CONFIG_OVERLAY_COMPOSE end */
	//wifi display begin
	int32_t buff_slot;
	//wifi display end
};

struct overlay_data {
	uint32_t id;
	uint32_t is_graphic;
	struct k3fb_img src;
};

struct overlay_info {
	struct k3fb_rect src_rect;
	struct k3fb_rect dst_rect;
	uint32_t id;
	uint32_t is_pipe_used;
	uint32_t rotation;
	uint32_t dither;
	uint32_t hd_enable;
	/* CONFIG_OVERLAY_COMPOSE start */
	uint32_t cfg_disable;
	uint32_t is_overlay_compose;
	uint32_t need_unset;
	uint32_t overlay_num;
	/* CONFIG_OVERLAY_COMPOSE end */
	/*begin support edc  pixels algin  modified by weiyi 00175802*/
	uint32_t  clip_right;
	uint32_t  clip_bottom;
	uint32_t  clip_right_partial;
	uint32_t  clip_bottom_partial;
	/*end support edc  pixels algin  modified by weiyi 00175802*/	
};

#if FB_BBIT_TEST_ENABLE
struct overlay_reg_info{
	uint32_t	reg_val;
	uint32_t	reg_offset;
};

#endif

#endif /*_K3_EDC_H_*/

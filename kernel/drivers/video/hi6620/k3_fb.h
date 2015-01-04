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

#ifndef K3_FB_H
#define K3_FB_H

#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/fb.h>
#include <linux/spinlock.h>
#include <mach/platform.h>
#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif
#include <mach/hisi_mem.h>

#include "k3_fb_def.h"
#include "k3_fb_panel.h"
#include "edc_overlay.h"
#include "k3_edc.h"
#if defined(CONFIG_OVERLAY_COMPOSE)
#include <linux/pm_qos_params.h>
#endif

#include <linux/sw_sync.h>
#include <linux/file.h>
#include "SysCtrl_reg.h"

/*G2D clk rate*/
#define G2D_CLK_100MHz	(100 * 1000 * 1000)
#define G2D_CLK_200MHz	(200 * 1000 * 1000)
#define G2D_CLK_300MHz	(300 * 1000 * 1000)
#define G2D_CLK_400MHz	(400 * 1000 * 1000)
#define G2D_CLK_600MHz	(600 * 1000 * 1000)

#define EVT_TEM_LEVEL_MAX	4
/* FRC */
#define EVT_TEM_NORM		40
#define EVT_TEM_ABOVE_NORM	45
#define EVT_TEM_HIGH		50
#define EVT_TEM_THRD		57
#define FAKE_FPS_TEM_NORM_FPS		60
#define FAKE_FPS_TEM_ABOVE_NORM_FPS	45
#define FAKE_FPS_TEM_HIGH			36
#define FAKE_FPS_TEM_THRD			30
#define K3_FB_OVERLAY_USE_BUF 0

#define K3_FB_FRC_ENABLE	0

#define K3_FB_ESD_ENABLE	1

/* v9r1 bbit test macro  end */

/*FRC Frame definition*/
#define K3_FB_FRC_BENCHMARK_FPS	67
#define K3_FB_FRC_NORMAL_FPS	60
#define K3_FB_FRC_IDLE_FPS	30
#define K3_FB_FRC_VIDEO_FPS	60
#define K3_FB_FRC_WEBKIT_FPS	45
#define K3_FB_FRC_BENCHMARK_FPS	67
#define K3_FB_FRC_GAME_FPS		45
#define K3_FB_FRC_SPECIAL_GAME_FPS  60

/* Modified for set frc, begin */
/* FRC for Command Panel */
#define K3_FB_FRC_GAME_FPS_CMD	45
#define CMD_FPS_SPECIAL_GAME 45
/* Modified for set frc, end */

#define K3_FB_FRC_THRESHOLD	6
#define K3_FB_EDC_IDLE_TIMEOUT  60

/* ESD */
#define K3_FB_ESD_THRESHOLD	45

/* SBL */
#define SBL_BKL_STEP	5
#define SBL_REDUCE_VALUE(x)	(x)

/* display resolution limited */
#define K3_FB_MIN_WIDTH	32
#define K3_FB_MIN_HEIGHT	32
#define K3_FB_MAX_WIDTH	1200
#define K3_FB_MAX_HEIGHT	1920

/* frame buffer physical addr */
#define K3_FB_PA	HISI_FRAME_BUFFER_BASE
#define K3_NUM_FRAMEBUFFERS	3
extern u32 k3fd_reg_base_edc0;
extern u32 k3fd_reg_base_edc1;
extern u32 k3fd_reg_base_dsi0;
/* EDC */
#define EDC_CH_SECU_LINE	11
#define EDC_CORE_CLK_RATE	(CONFIG_EDC_CORE_CLK_RATE)

#define K3FB_DEFAULT_BGR_FORMAT	EDC_RGB

/* for MIPI Command LCD */
#define CLK_SWITCH     0      /* 1 */

/* for Vsync*/
#define VSYNC_TIMEOUT_MSEC 100 //50

/* FB width must be 16 pixels aligned in Vivante GPU */
#define USE_VIVANTE_GPU	0

#define BUS_DFS_FREQ  (150000)


extern int g_debug_camerause; 
#if defined(CONFIG_OVERLAY_COMPOSE)
//channel change flow
//#define EDC_CH_CHG_SUPPORT
#endif //CONFIG_OVERLAY_COMPOSE

enum {
	LCD_LANDSCAPE = 0,
	LCD_PORTRAIT,
};

/* set backlight by pwm or mipi ... */
enum {
	BL_SET_BY_NONE = 0,
	BL_SET_BY_PWM = 0x1,
	BL_SET_BY_MIPI = 0x2,
};

enum {
	IMG_PIXEL_FORMAT_RGB_565 = 1,
	IMG_PIXEL_FORMAT_RGBA_5551,
	IMG_PIXEL_FORMAT_RGBX_5551,
	IMG_PIXEL_FORMAT_RGBA_8888,
	IMG_PIXEL_FORMAT_RGBX_8888,
};

enum {
	FB_64BYTES_ODD_ALIGN_NONE = 0,
	FB_64BYTES_ODD_ALIGN_UI,
	FB_64BYTES_ODD_ALIGN_VIDEO,
};

enum {
	FB_LDI_INT_TYPE_NONE = 0x0,
	FB_LDI_INT_TYPE_FRC = 0x1,
	FB_LDI_INT_TYPE_ESD = 0x2,
};

/* frc state definition */
enum {
	K3_FB_FRC_NONE_PLAYING = 0x0,
	K3_FB_FRC_VIDEO_PLAYING = 0x2,
	K3_FB_FRC_GAME_PLAYING = 0x4,
	K3_FB_FRC_VIDEO_IN_GAME = 0x6,
	K3_FB_FRC_BENCHMARK_PLAYING = 0x8,
	K3_FB_FRC_WEBKIT_PLAYING =0x10,
	K3_FB_FRC_SPECIAL_GAME_PLAYING = 0x20,
	K3_FB_FRC_IDLE_PLAYING = 0x40,
};

//Multi-Resolution====begin
enum {
    DISPLAY_LOW_POWER_LEVEL_FHD = 0x0,
    DISPLAY_LOW_POWER_LEVEL_HD = 0x1,
    DISPLAY_LOW_POWER_LEVEL_MAX,
};
//Multi-Resolution====end

#ifdef CONFIG_DEBUG_FS
/* lowpower debugfs IP Flag */
enum {
    DEBUG_CLEAR_LOWPOWER_DISABLE = 0,
    DEBUG_EDC_LOWPOWER_DISABLE  = 0x1,
    DEBUG_MIPI_LOWPOWER_DISABLE = 0x2,
    DEBUG_LCD_LOWPOWER_DISABLE  = 0x4,
    DEBUG_G2D_LOWPOWER_DISABLE  = 0x8,
    DEBUG_ALL_LOWPOWER_DISABLE  = 0xF,
};

typedef union {
    struct {
        u32         bit_vsync     : 1;
        u32         bit_display   : 1; 
        u32         bit_backlight : 1;
        u32         reserved      : 29;
    } bits;
    u32             ul32;
} k3fb_debug_log_info_union;

extern u32 g_fb_lowpower_debug_flag;
extern u32 g_fb_colorbar_mod;
extern k3fb_debug_log_info_union g_fb_log_printk_flag;


#endif
/**
 * struct k3fb_vsync - vsync information+
 * @wait:              a queue for processes waiting for vsync
 * @timestamp:         the time of the last vsync interrupt
 * @active:            whether userspace is requesting vsync uevents
 * @irq_refcount:      reference count for the underlying irq
 * @irq_lock:          mutex protecting the irq refcount and register
 * @thread:            uevent-generating thread
 */
struct k3fb_vsync {
	wait_queue_head_t       wait;
	ktime_t                 timestamp;
	int                     te_refcount;
	bool                    active;
	int                     irq_refcount;
	spinlock_t              irq_lock;
	struct task_struct      *thread;
};


#if defined(CONFIG_OVERLAY_COMPOSE)
#define MAX_EDC_CHANNEL (5)  		/* (3)*/

enum {
    OVC_NONE,
    OVC_PARTIAL,
    OVC_FULL,
};

/* ovc:overlaycompose,
 * ch :channel
 */
struct st_k3_fb_partial_ovc_ch {
	u32	ovc_ch_count;
	u32 ovc_ch_index[MAX_EDC_CHANNEL];
	u32 pan_play_info_ch;
};

#endif /* CONFIG_OVERLAY_COMPOSE */

struct k3_fb_data_type {
	u32 index;
	u32 ref_cnt;
	u32 bl_level;
	u32 bl_level_sbl;
	u32 bl_level_cmd;
	u32 fb_imgType;
	u32 fb_bgrFmt;
	u32 edc_base;
	u32 dsi_base;
	u32 edc_irq;
	u32 ldi_irq;
	s32 ldi_int_type;
	u32 check_esd;

	char edc_irq_name[64];
	char ldi_irq_name[64];

	panel_id_type panel;
	struct k3_panel_info panel_info;
	bool panel_power_on;

	struct fb_info *fbi;
	u32 graphic_ch;

	wait_queue_head_t frame_wq;
	s32 update_frame;
	struct work_struct frame_end_work;
	struct workqueue_struct *frame_end_wq;

	
	bool cmd_mode_refresh;
	bool cmd_bl_can_set;

	struct edc_overlay_ctrl ctrl;
	struct platform_device *pdev;
	struct semaphore sem;
	struct clk *edc_clk;
	struct clk *ldi_clk;
	struct clk *edc_axi_clk;
	struct clk *edc_cfg_clk;
	struct clk *dsi_cfg_clk;
	struct clk *mipi_dphy0_cfg_clk;
	struct clk *mipi_dphy0_ref_clk;
	struct clk *g2d_clk;
	struct clk *dsp_pll;
	struct clk *peri_pll;
	struct regulator *edc_vcc;

	struct k3fb_vsync	vsync_info;
	/* Add for set frc, begin */
	bool use_cmd_vsync;
	/* Add for set frc, end */
	struct hrtimer cmd_vsync_hrtimer;
	int ambient_temperature;

	/* for sbl */
	u32 sbl_enable;
	u32 sbl_lsensor_value;
	struct work_struct sbl_work;
	struct workqueue_struct *sbl_wq;

	/* for temperature obtaining*/
	struct work_struct temp_work;
	struct workqueue_struct *temp_wq;

	/* for frc */
	s32 frc_state;
	s32 frc_threshold_count;
	unsigned long frc_timestamp;

	/* for esd */
	unsigned long esd_timestamp;
	s32 esd_frame_count;
	bool esd_recover;
	bool checkesd_bl_cannot_set;

	struct hrtimer esd_hrtimer;
	bool esd_hrtimer_enable;

#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
#endif

#if defined(CONFIG_OVERLAY_COMPOSE)
	/* type: full/partial/none */
	u32 ovc_type;
	u32 ovc_ch_count;
	//ch chg state
#if defined(EDC_CH_CHG_SUPPORT)
	bool ch_chg_flag;
	bool ch_chg_power_off;
#endif //EDC_CH_CHG_SUPPORT
	//idle switch to g2d
	bool ovc_idle_flag;
	//ovc buffer sync: ch1,ch2,crs
	bool ovc_wait_state[MAX_EDC_CHANNEL];
	bool ovc_wait_flag[MAX_EDC_CHANNEL];
	u32 ovc_lock_addr[MAX_EDC_CHANNEL];
	u32 ovc_lock_size[MAX_EDC_CHANNEL];
	u32 ovc_ch_gonna_display_addr[MAX_EDC_CHANNEL];
	u32 ovc_ch_display_addr[MAX_EDC_CHANNEL];
	//overlay play cfg_ok once
	struct overlay_data ovc_req[MAX_EDC_CHANNEL];
	u32    ddrIdleCount;
	u32 ddr_min_freq;
	u32 ddr_min_freq_saved;
	u32 ddr_curr_freq;
	u32 ovc_ddr_failed;
	struct pm_qos_request_list ovc_ddrminprofile;
	struct work_struct ovc_ddr_work;
	struct workqueue_struct *ovc_ddr_wq;
#endif
	//Multi Resolution====begin
	int switch_res_flag;
	//Multi Resolution====end

    struct sw_sync_timeline *timeline;
    int timeline_max;
    int refresh;
    struct task_struct      *fence_inc_thread;
    wait_queue_head_t       fence_inc_wait;
    spinlock_t refresh_lock;
    u32 dsi_clk_last;
    struct mipi_dsi_phy_register phy_ctrl1;
};


#if K3_FB_OVERLAY_USE_BUF
#define MAX_OVERLAY_BUF_NUM     3
typedef struct overlay_video_data {
	struct overlay_data data;
	bool                is_set;
	u32                 count;
} overlay_video_data;

typedef struct overlay_video_buf_ {
	overlay_video_data      video_data_list[MAX_OVERLAY_BUF_NUM];
	struct work_struct      play_work;
	u32                     write_addr;
	u32                     play_addr;
	u32                     last_addr;
	bool                    exit_work;
	struct workqueue_struct *play_wq;
	struct mutex            overlay_mutex;
	bool                    is_init;
	bool                    is_video;
} overlay_video_buf;

#ifdef PC_UT_TEST_ON
extern STATIC overlay_video_buf     video_buf;
#endif

#endif

#ifdef CONFIG_FB_CHECK_MIPI_TR
enum CHECK_MIPI_TR {
    CHECK_MIPI_TR_FAIL = -1,
    CHECK_MIPI_TR_OK = 0,
};
#endif

/******************************************************************************
** global variable
******************************************************************************/
#ifdef PC_UT_TEST_ON
//#define MAX_FBI_LIST    32
extern STATIC bool                      hdmi_is_connected;
extern STATIC struct fb_info           *fbi_list[32];
extern STATIC struct k3_fb_data_type   *k3fd_list[32];
extern STATIC int                       fbi_list_index;
extern STATIC int                       k3_fb_resource_initialized;
extern STATIC int                       pdev_list_cnt;
extern u32 				                g_g2d_current_freq;
extern int                              g2d_lock_state;
extern int                              g2d_start_freq;

#endif

/******************************************************************************
** FUNCTIONS PROTOTYPES
*/

void k3_fb_set_backlight(struct k3_fb_data_type *k3fd, u32 bkl_lvl);
int get_resolution_type(void);  //add for D2 lcd 
void get_lcd_type(struct k3_fb_data_type *k3fd);
struct platform_device *k3_fb_add_device(struct platform_device *pdev);

u32 k3_fb_line_length(u32 xres, int bpp);
int k3_fb1_blank(int blank_mode);
int k3fb_buf_isfree(int phys);
void k3fb_set_hdmi_state(bool is_connected);
int edc_mtcos_enable(u32 fb_index);
int edc_mtcos_disable(u32 fb_index);


struct fb_var_screeninfo * k3fb_get_fb_var(int index);

#if defined(CONFIG_OVERLAY_COMPOSE)
void k3_fb_gralloc_overlay_save_display_addr(struct k3_fb_data_type *k3fd, int ch, u32 addr);
void k3_fb_gralloc_overlay_restore_display_addr(struct k3_fb_data_type *k3fd);
#if defined(EDC_CH_CHG_SUPPORT)
struct fb_info* k3_fb1_get_info(void);
#endif //EDC_CH_CHG_SUPPORT
void k3_fb_overlay_compose_data_clear(struct k3_fb_data_type *k3fd);


#endif //CONFIG_OVERLAY_COMPOSE
int k3_fb_overlay_fence_create(struct sw_sync_timeline *timeline,const char *fence_name,unsigned value);
int k3_fb_overlay_fence_wait(int fenceFd,long timeout);
#endif /* K3_FB_H */

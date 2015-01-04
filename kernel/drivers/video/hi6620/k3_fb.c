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
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/console.h>
#include <linux/uaccess.h>
#include <linux/clk.h>
#include <linux/leds.h>
#include <linux/regulator/consumer.h>
#include <linux/time.h>
#include <linux/kthread.h>
#include <mach/boardid.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <hsad/config_mgr.h>

#include "k3_fb.h"
#include "edc_reg.h"
#include "ldi_reg.h"
#include "mipi_reg.h"
#include "sbl_reg.h"
#include "edc_overlay.h"
#include <trace/trace_kernel.h>

#ifdef CONFIG_FOLLOWABILITY
#include "fb_monitor.h"
#endif
#ifdef HDMI_DISPLAY
#include "hdmi/k3_hdmi.h"
#endif

#include <linux/pm_qos_params.h>

struct pm_qos_request_list gedc_pm_qos_req;
struct pm_qos_request_list gdfs_pm_qos_req;
struct pm_qos_request_list g_cpunum_qos;

#if defined(CONFIG_OVERLAY_COMPOSE)
#include <linux/proc_fs.h>
#ifndef PC_UT_TEST_ON
#include <linux/ipps.h>
#endif
#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/string.h>

#ifdef CONFIG_MACH_HI6620OEM
u32 g_fb_lowpower_debug_flag = DEBUG_CLEAR_LOWPOWER_DISABLE;  /*  0x0 */
u32 g_fb_colorbar_mod = 0;
#else
u32 g_fb_lowpower_debug_flag = DEBUG_CLEAR_LOWPOWER_DISABLE; /* 0 */
u32 g_fb_colorbar_mod = 0;

#endif


k3fb_debug_log_info_union g_fb_log_printk_flag = {.ul32 = 0};

#endif

#define BUFFER_IS_USED(display_addr, addr, addr_size)  ((display_addr >= addr) && (display_addr < addr + addr_size))
#define OVC_BUFFER_SYNC_FILE "gralloc_overlay_state"
static DEFINE_SPINLOCK(gralloc_overlay_slock);
static DECLARE_WAIT_QUEUE_HEAD(gralloc_overlay_wait_queue);
#endif //CONFIG_OVERLAY_COMPOSE

#define K3_FB_MAX_DEV_LIST 32
#define MAX_FBI_LIST 32
#define CAMERA_XRES 320
#define CAMERA_YRES 480
#define IS_FHD_LCD 1
#define IS_HD_LCD  0

#define DSI_BIT_CLK_473  473
#define DSI_BIT_CLK_480  480
#define DSI_BIT_CLK_486  486
#define DSI_BIT_CLK_492  492
#define DSI_BIT_CLK_499  499
int g_debug_camerause = 0;
static int lcd_check_esd = 1;
u32 frame_count = 0;
static int isFHD = 0;
#define PM_QOS_CPU_MIN_NUMBER (3)

STATIC int k3_fb_resource_initialized;
static struct platform_device *pdev_list[K3_FB_MAX_DEV_LIST] = {0};

STATIC int pdev_list_cnt;
STATIC struct fb_info *fbi_list[MAX_FBI_LIST] = {0};

#if CONFIG_WFD_FBINFO
/* wifi display begin */
wfd_fb_info wfd_fbi;
/* wifi display end */
#endif

int g_ldi_delay_debug = 40;
STATIC int fbi_list_index;

STATIC struct k3_fb_data_type *k3fd_list[MAX_FBI_LIST] = {0};
static int k3fd_list_index;

u32 k3fd_reg_base_edc0;
u32 k3fd_reg_base_edc1;
u32 k3fd_reg_base_dsi0;
static u32 k3fd_irq_edc0;
static u32 k3fd_irq_edc1;
static u32 k3fd_irq_ldi0;
static u32 k3fd_irq_ldi1;
STATIC bool hdmi_is_connected = false;
int g2d_start_freq = (CONFIG_G2D_CLK_RATE);
int g2d_lock_state = 0;
u32 g_g2d_current_freq;

static u32 k3_fb_pseudo_palette[16] = {
	0x00000000, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff,
	0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
};

#define MAX_BACKLIGHT_BRIGHTNESS 255
#define APICAL_INDOOR_UI  0x1
#define APICAL_OUTDOOR_UI  0x2
#define APICAL_CAMERA_UI  0x3

DEFINE_SEMAPHORE(k3_fb_overlay_sem);
DEFINE_SEMAPHORE(k3_fb_backlight_sem);
DEFINE_SEMAPHORE(k3_fb_blank_sem);

#ifdef PC_UT_TEST_ON
volatile unsigned int    g_pc_ut_reg_data[0x2000];          /* used for ut reg test */
#endif


//Multi Resolution====begin
/*added for resolution switch*/
STATIC int k3_fb_switch_resolution_process(struct k3_fb_data_type * k3fd);
STATIC int k3_fb_init_par(struct k3_fb_data_type *k3fd, int pixel_fmt);

//Multi Resolution====end

/******************************************************************************
** FUNCTIONS PROTOTYPES
*/
static void k3_fb_set_backlight_cmd_mode(struct k3_fb_data_type *k3fd, u32 bkl_lvl);
int k3_fb_blank_sub(int blank_mode, struct fb_info *info,bool sem);
static int k3fb_esd_set(struct k3_fb_data_type *k3fd);

static int k3fb_frc_get_fps(struct k3_fb_data_type *k3fd);

static void k3fb_te_inc(struct k3_fb_data_type *k3fd, bool te_should_enable, bool in_isr);
static void k3fb_te_dec(struct k3_fb_data_type *k3fd, bool te_should_disable, bool in_isr);

/******************************************************************************
** for HDMI
*/
STATIC bool should_use_videobuf(struct fb_info *info)
{
    int timing_code = info->var.reserved[3];
    if (timing_code == 32 || timing_code == 33 || timing_code == 34) {
        return true;
    }
    return false;
}

#if K3_FB_OVERLAY_USE_BUF

STATIC overlay_video_buf video_buf;

STATIC void reset_video_buf(void)
{
	memset(&video_buf.video_data_list, 0, sizeof(video_buf.video_data_list));
	video_buf.write_addr = 0;
	video_buf.play_addr  = 0;
	video_buf.last_addr  = 0;
}

STATIC void overlay_play_work_queue(struct work_struct *ws)
{
	struct fb_info *info = fbi_list[1];
	struct k3_fb_data_type *k3fd = NULL;
	overlay_video_data *play_data = NULL;
	u32 play_index = 0;
	int i = 0;
	int free_count = 0;
	int min_count  = 0;
	int null_count = 0;
	int timing_code = 0;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	while (!video_buf.exit_work) {
		if (video_buf.is_video && hdmi_is_connected) {
			if (wait_event_interruptible_timeout(k3fd->frame_wq, k3fd->update_frame, HZ) <= 0) {
				k3fb_logw("wait_event_interruptible_timeout !\n");
				k3fd->update_frame = 0;
				continue;
			}
			k3fd->update_frame = 0;
		} else {
			msleep(80);
			continue;
		}

		mutex_lock(&video_buf.overlay_mutex);

		free_count = 0;
		min_count = 0;

		video_buf.play_addr = video_buf.write_addr;

		if (video_buf.is_video) {
			for (i = 0; i < MAX_OVERLAY_BUF_NUM; i++) {
				play_data = &video_buf.video_data_list[i];
				if (play_data->is_set) {
					if (0 == min_count || play_data->count < min_count) {
						min_count = play_data->count;
						play_index = i;
					}
				} else {
					free_count++;
				}
			}

			if (MAX_OVERLAY_BUF_NUM == free_count) {
				null_count++;
				if (null_count < 20) {
					k3fb_logw("video buff null 00000.\n");
				}
			} else {
				null_count = 0;
				play_data = &video_buf.video_data_list[play_index];

				if ((play_data->count == 1) && (free_count != 0)) {
					/*k3fb_logi("free_count:%d count:%d\n", free_count, play_data->count);*/
                } else {
					/*k3fb_logi("play index:%d count:%d\n", play_index, play_data->count);*/
    				video_buf.write_addr = play_data->data.src.phy_addr;
    				play_data->is_set = false;
				}
				edc_overlay_play(k3fd->fbi, &play_data->data);
			}
		}
		mutex_unlock(&video_buf.overlay_mutex);
	}
	return ;
}

STATIC int overlay_play_work(struct k3_fb_data_type *k3fd)
{
	memset(&video_buf, 0, sizeof(video_buf));

	video_buf.play_wq = create_singlethread_workqueue("overlay_play_work");
	if (!(video_buf.play_wq)) {
		k3fb_loge("workqueue create failed !\n");
		return -1;
	}

	mutex_init(&video_buf.overlay_mutex);
	INIT_WORK(&video_buf.play_work, overlay_play_work_queue);

	video_buf.is_init = true;

	return 0;
}
#endif

int k3_fb1_blank(int blank_mode)
{
	int ret = 0;
	struct fb_info *info = fbi_list[1];
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	ret = k3_fb_blank_sub(blank_mode, info,1);
	if (ret != 0) {
		k3fb_loge("blank mode %d failed!\n", blank_mode);
	}

	if (blank_mode == FB_BLANK_UNBLANK) {
		k3_fb_set_backlight(k3fd, k3fd->bl_level);
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return ret;
}

int k3fb_buf_isfree(int phys)
{
	int ret = 1;

#if K3_FB_OVERLAY_USE_BUF
	int i = 0;
	struct fb_info *info = fbi_list[1];
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on || phys == 0 || !video_buf.is_init || !hdmi_is_connected) {
		return ret;
	}

	mutex_lock(&video_buf.overlay_mutex);

	if (video_buf.write_addr == phys || video_buf.play_addr == phys) {
		/*k3fb_logi("addr:0x%x is playing!", phys); */
		ret = 0;
		goto done;
	}
	for (i = 0; i < MAX_OVERLAY_BUF_NUM; i++) {
		if (video_buf.video_data_list[i].is_set
		   && (video_buf.video_data_list[i].data.src.phy_addr == phys)) {
			/*k3fb_logi("addr:0x%x in buf!", phys); */
			ret = 0;
			goto done;
		}
	}

done:
	mutex_unlock(&video_buf.overlay_mutex);
#endif
	return ret;
}

void k3fb_set_hdmi_state(bool is_connected)
{
	if (hdmi_is_connected == is_connected) {
		return;
	}
	k3fb_logi("hdmi_is_connected: %d is_connected: %d\n", hdmi_is_connected , is_connected);
	hdmi_is_connected = is_connected;
#if K3_FB_OVERLAY_USE_BUF
	if (video_buf.is_init) {
		mutex_lock(&video_buf.overlay_mutex);
		reset_video_buf();
		mutex_unlock(&video_buf.overlay_mutex);

        if (hdmi_is_connected) {
            video_buf.exit_work = 0;
            queue_work(video_buf.play_wq, &video_buf.play_work);
        } else {
            video_buf.exit_work = 1;
        }
	}
#endif
	return;
}

struct fb_var_screeninfo * k3fb_get_fb_var(int index)
{
	struct fb_info *info = fbi_list[index];

	BUG_ON(info == NULL);

	return &info->var;
}

EXPORT_SYMBOL(k3_fb1_blank);
EXPORT_SYMBOL(k3fb_buf_isfree);
EXPORT_SYMBOL(k3fb_set_hdmi_state);
EXPORT_SYMBOL(k3fb_get_fb_var);


/******************************************************************************/
STATIC int k3fb_frc_set_state(struct fb_info *info, unsigned long *argp)
{
	struct k3_fb_data_type *k3fd = NULL;
	char buffer[4];

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (copy_from_user(buffer, argp, sizeof(buffer))) {
		k3fb_loge("copy from user failed \n");
		return -EFAULT;
	}

	/*  Different input values mean different application scenes as follow:
	  *  1) 1:1 or 1:0 mean Video is playing or stop playing;
	  *  2) 2:1 or 2:0 mean Game is playing or stop playing;
	  *  3) 3:1 or 3:0 mean Benchmark is runing or stop running.
	  *  4) 4:1 or 4:0 mean Webkit is running or stop running.
	  *  5) 5:1 or 5:0 mean Special Game is playing or stop playing.
	  *  6) ......
	  */

	switch (buffer[0]-'0') {
	case 1:
	case 2:
	case 3:
	case 4:
        case 5:
		{
			if (buffer[2] == '0') {
				k3fd->frc_state &= ~(1 << (buffer[0] - '0'));
			} else {
				k3fd->frc_state |= (1 << (buffer[0] - '0'));
			}
		}
		break;

	default:
		break;
	}
	return 0;
}

static int k3fd_g2d_clk_rate_off;
STATIC void k3_fb_set_g2d_clk_rate(int level)
{
	struct k3_fb_data_type *k3fd = NULL;
	int ret = 0;
	u32 rate = 0;

	k3fd = k3fd_list[0];
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return;
	}

	switch (level) {
	case 1:
		rate = G2D_CLK_100MHz;
		break;
	case 2:
		rate = G2D_CLK_200MHz;
		break;
	case 3:
		rate = G2D_CLK_300MHz;
		break;
	case 4:
		rate = G2D_CLK_400MHz;
		break;
	case 5:
		rate = G2D_CLK_600MHz;
		break;
	default:
		rate = G2D_CLK_600MHz;
		break;
	}

    if (rate == g_g2d_current_freq)
    {
        return;
    }
    else
    {
        g_g2d_current_freq = rate;
    }

	if (k3fd->g2d_clk) {
		ret = clk_set_rate(k3fd->g2d_clk,  rate);
		if (ret != 0) {
			k3fb_loge("G2D %d, error = %d.\n", rate, ret);
		} else {
			//k3fb_logi("G2D:%d.\n", rate);
		}
	}
}

STATIC int k3fb_g2d_set_freq(struct fb_info *info, unsigned long *argp)
{
	struct k3_fb_data_type *k3fd = NULL;
	char buffer[4];

    if (g2d_lock_state != 0)
    {
        return 0;
    }

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (copy_from_user(buffer, argp, sizeof(buffer))) {
		k3fb_loge("copy from user failed \n");
		return -EFAULT;
	}


	switch (buffer[0]-'0') {
	case 9:
	{
		if (k3fd->frc_state == K3_FB_FRC_BENCHMARK_PLAYING) {
			k3_fb_set_g2d_clk_rate(5);
			break;
		}

		if (buffer[2] == '0') {
			if (k3fd_g2d_clk_rate_off == 0) {
				k3fd_g2d_clk_rate_off = 1;
				k3_fb_set_g2d_clk_rate(5);
			} else {
				k3fd_g2d_clk_rate_off = 0;
			}
		}

		if (k3fd_g2d_clk_rate_off == 0)
			k3_fb_set_g2d_clk_rate(buffer[2]-'0');
	}
		break;
	default:
		break;
	}

	return 0;
}

int apical_flags = 0x0;
STATIC int k3fb_sbl_set_value(struct fb_info *info, unsigned long *argp)
{
	int val = 0;
	int value_flags;
	u32 edc_base = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);
	edc_base = k3fd->edc_base;

	if (copy_from_user(&val, argp, sizeof(val))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	if (k3fd->panel_info.sbl_enable) {
		down(&k3_fb_blank_sem);
		k3fd->sbl_lsensor_value =  val & 0xffff;
		k3fd->sbl_enable = (val >> 16) & 0x1;
		value_flags = (val >> 17) & 0x3;

		if (value_flags && k3fd->sbl_enable) {
			if (value_flags == APICAL_OUTDOOR_UI) {
				set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x80, 8, 0);
				apical_flags = 0x80;
			} else if (value_flags == APICAL_CAMERA_UI) {
				set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x20, 8, 0);
				apical_flags = 0x20;
			} else {
				set_reg(edc_base + SBL_STRENGTH_MANUAL_OFFSET, 0x0, 8, 0);
				apical_flags = 0x0;
			}
		}

		if (!k3fd->panel_power_on) {
			k3fb_logw("panel power is not on.\n");
			up(&k3_fb_blank_sem);
			return -ENODEV;;
		}

		sbl_ctrl_set(k3fd);
		up(&k3_fb_blank_sem);
	}

	return 0;
}
int k3fb_g2d_lock_freq_rate(int rate)
{

    g2d_lock_state = rate;
	switch (rate) {
	case 2:
		g2d_start_freq = G2D_CLK_200MHz;
		break;
	case 3:
		g2d_start_freq = G2D_CLK_300MHz;
		break;
	case 4:
		g2d_start_freq = G2D_CLK_400MHz;
		break;
	case 5:
		g2d_start_freq = G2D_CLK_600MHz;
		break;
	default:
        g2d_start_freq = G2D_CLK_200MHz;
		break;
        }
    if ((rate > 1)&&(rate < 6))
    {
        k3_fb_set_g2d_clk_rate(g2d_lock_state);
        k3fb_logi_display_debugfs("G2D is lock to profile %d.\n", g2d_lock_state);
        k3fb_logi_display_debugfs("G2D Start Freq is set to %dMhz.\n", g2d_start_freq/1000000);
    }
    else if (rate == 0)
    {
        k3fb_logi_display_debugfs("Disable G2D lock freq.\n");
    }
    else
    {
        g2d_lock_state = 0;
        printk("You input an unsupport profile. please input 2~5.\n");
        printk("2 --- 200Mhz\n");
        printk("3 --- 300Mhz\n");
        printk("4 --- 400Mhz\n");
        printk("5 --- 600Mhz\n");
        printk("0 --- Disable\n");
    }

    return 0;

}
STATIC int k3fb_g2d_lock_freq(struct fb_info *info, unsigned long *argp)
{
	int val = 0;
	if (copy_from_user(&val, argp, sizeof(val))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	k3fb_g2d_lock_freq_rate(val);

	return 0;
}

struct mipi_dsi_phy_register phy_ctrl[] = {{102, 34, 124, 47, 8, 11, 8, 0x30, 3, 19, 132, 10},
	                                 {107, 35, 130, 49, 8, 11, 8, 0x30, 1, 17, 129, 26},
									 {107, 35, 130, 49, 8, 11, 8, 0x30, 3, 23, 132, 26},
									 {107, 35, 130, 49, 8, 11, 8, 0x30, 3, 25, 132, 26},
									 {107, 35, 130, 49, 8, 11, 8, 0x30, 1, 19, 129, 26}};

static void k3_fb_mipi_register_reset(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);
	set_MIPIDSI_PHY_TMR_CFG_phy_lp2hs_time(k3fd->phy_ctrl1.lp2hs_time);
    set_MIPIDSI_PHY_TMR_CFG_phy_hs2lp_time(k3fd->phy_ctrl1.hs2lp_time);
    set_MIPIDSI_PHY_TMR_LPCLK_CFG_phy_clklp2hs_time(k3fd->phy_ctrl1.clk_lp2hs_time);
    set_MIPIDSI_PHY_TMR_LPCLK_CFG_phy_clkhs2lp_time(k3fd->phy_ctrl1.clk_hs2lp_time);
	set_MIPIDSI_CLKMGR_CFG_tx_esc_clk_division(k3fd->phy_ctrl1.clk_division);
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010011 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.cp_current );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010012 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.lpf_ctrl );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010019 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.factors_effective );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010017 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.n_pll - 1 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010018 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.m_pll_1 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010018 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( k3fd->phy_ctrl1.m_pll_2 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( 0x00010044 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	set_MIPIDSI_PHY_TST_CTRL1( (k3fd->phy_ctrl1.hsfreqrange << 1) & 0x7E );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
	set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	return;
}
static ssize_t k3_fb_set_dsi_freq_store(struct device *dev, struct device_attribute *attr,
        const char *buf, size_t size)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 dsi_freq_index = 0;
 	k3fd = k3fd_list[0];
       BUG_ON(k3fd == NULL);
	
	if ((!*buf)) {
		k3fb_loge("Input param is error!\n");
		return 0;
	}
	dsi_freq_index = simple_strtoul(buf, NULL, 10);
	if (isFHD) {
		switch(dsi_freq_index) {
			case 1:
				k3fd->phy_ctrl1 = phy_ctrl[0];
				k3fd->panel_info.mipi.dsi_bit_clk = DSI_BIT_CLK_473;
				break;
			case 10:
				k3fd->phy_ctrl1 = phy_ctrl[1];
				k3fd->panel_info.mipi.dsi_bit_clk = DSI_BIT_CLK_480;
				break;
			case 100:
				k3fd->phy_ctrl1 = phy_ctrl[2];
				k3fd->panel_info.mipi.dsi_bit_clk = DSI_BIT_CLK_486;
				break;
			case 1000:
				k3fd->phy_ctrl1 = phy_ctrl[3];
				k3fd->panel_info.mipi.dsi_bit_clk = DSI_BIT_CLK_492;
				break;
			case 10000:
				k3fd->phy_ctrl1 = phy_ctrl[4];
				k3fd->panel_info.mipi.dsi_bit_clk = DSI_BIT_CLK_499;
				break;
			default:
				k3fb_loge("dsi_freq_index = %d is invalid \n", dsi_freq_index);
				break;
		}
	}
	
	return size;
}
/*******************************************************************************
** for overlay compose
*/
#if defined(CONFIG_OVERLAY_COMPOSE)

STATIC void k3_fb_overlay_compose_parse_buffer(char* buf, u32* para_h, u32* para_t)
{
    int length;
    int pos;
    char buf_head[20];
    char buf_tail[20];

    if (buf == NULL) {
        *para_h = 0;
        *para_t = 0;
        return;
    }
    memset(buf_head, 0, sizeof(buf_head));
    memset(buf_tail, 0, sizeof(buf_tail));

    /* buffer format => 12345:12345 */
    length = strlen(buf);
    pos = strstr(buf, ":") - buf;

    memcpy(buf_head, buf, pos);
    buf_head[pos] = '\0';
    memcpy(buf_tail, buf + pos + 1, length - pos);

    *para_h = simple_strtoul(buf_head, NULL, 10); /* decimal */
    *para_t = simple_strtoul(buf_tail, NULL, 10); /* decimal */
}

#if defined(EDC_CH_CHG_SUPPORT)
struct fb_info* k3_fb1_get_info(void)
{
    struct fb_info *info = fbi_list[1];
    BUG_ON(info == NULL);
    return info;
}

STATIC void k3_fb_overlay_compose_edc1_poweroff(struct k3_fb_data_type *k3fd)
{
    if (k3fd->ch_chg_power_off) {
        k3fd->ch_chg_power_off = false;
        overlay_compose_edc1_power_off();
    }
}
#endif //EDC_CH_CHG_SUPPORT


static void k3_fb_ippsclient_add(struct ipps_device *device)
{
}

static void k3_fb_ippsclient_remove(struct ipps_device *device)
{
}

#ifndef PC_UT_TEST_ON
static struct ipps_client k3_fb_ipps_client = {
    .name   = "k3_fb_ddr_ipps",
    .add    = k3_fb_ippsclient_add,
    .remove = k3_fb_ippsclient_remove
};

static u32 k3_fb_get_current_ddr_freq(void)
{
    /*
        return value:
        58000, 120000, 360000,450000
    */
    u32 freq = 0;

    ipps_get_current_freq(&k3_fb_ipps_client, IPPS_OBJ_DDR, &freq);
    k3fb_logi_display_debugfs("get_current_ddr_freq[%d]\n",freq);
    return freq;
}

static void k3_fb_overlay_compose_ddr_workqueue(struct work_struct *ws)
{
    unsigned long flags;
    struct k3_fb_data_type *k3fd = NULL;
    bool need_request = false;
    u32 curr_ddr_freq;

    k3fd  = container_of(ws, struct k3_fb_data_type, ovc_ddr_work);
    BUG_ON(k3fd == NULL);

    curr_ddr_freq = k3_fb_get_current_ddr_freq();

    spin_lock_irqsave(&gralloc_overlay_slock, flags);
    k3fb_logi_display_debugfs("ddr_workqueue: old_min = %d, new_min = %d , curr freq = %d \n", k3fd->ddr_min_freq_saved, k3fd->ddr_min_freq, curr_ddr_freq);
    /* printk("ddr_workqueue: old_min = %d, new_min = %d , curr freq = %d \n", ddr_min_freq_saved, k3fd->ddr_min_freq, curr_ddr_freq); */
    if (k3fd->ddr_min_freq_saved !=  k3fd->ddr_min_freq) {
        if ((k3fd->ddr_min_freq_saved > k3fd->ddr_min_freq)){
            curr_ddr_freq = 0;
        }
        need_request = true;
        k3fd->ddr_min_freq_saved = k3fd->ddr_min_freq;
    }

    k3fd->ddr_curr_freq = curr_ddr_freq;
    spin_unlock_irqrestore(&gralloc_overlay_slock, flags);

    if (need_request) {
        pm_qos_update_request(&k3fd->ovc_ddrminprofile, k3fd->ddr_min_freq_saved);
    }
}

static int k3_fb_overlay_compose_create_ddr_workqueue(struct k3_fb_data_type *k3fd)
{
    k3fd->ovc_ddr_wq = create_singlethread_workqueue("ovc_ddr_freq_workqueue");
    if (!k3fd->ovc_ddr_wq) {
        k3fb_loge("failed to create ovc ddr workqueue!\n");
        return -1;
    }

    INIT_WORK(&k3fd->ovc_ddr_work, k3_fb_overlay_compose_ddr_workqueue);
    return 0;
}
#endif
static int k3_fb_overlay_compose_destroy_ddr_workqueue(struct k3_fb_data_type *k3fd)
{
    if (k3fd->ovc_ddr_wq) {
        destroy_workqueue(k3fd->ovc_ddr_wq);
        k3fd->ovc_ddr_wq = NULL;
    }
    return 0;
}


#define MIN_FULL_OVC_0 (75000)
#define MIN_FULL_OVC_1 (266000)
#define MIN_FULL_OVC_1_ROTATE (360000)
#define MIN_FULL_OVC_2 (360000)
#define MIN_FULL_OVC_2_ROTATE (533000)
#define MIN_FULL_OVC_3 (360000)
#define MIN_FULL_OVC_3_ROTATE (533000)
#define MIN_FULL_OVC_4 (533000)
#define MIN_FULL_OVC_4_ROTATE (533000)
#define MIN_FULL_OVC_5 (533000)
#define MIN_FULL_OVC_5_ROTATE (533000)
#define LAYER_INTERSECT_COUNT_1  (266000)
#define LAYER_INTERSECT_COUNT_2  (360000)
#define LAYER_INTERSECT_COUNT_3  (533000)
#define OVC_EDC_THICK_MAX_LANE  (400)

STATIC u32 k3_fb_overlay_compose_get_target_ddr_min_freq(u32 count, u32 rotate)
{
    u32 min_ddr_freq = 0;
    if (isFHD) {
	switch (count) {
	case 1:
		min_ddr_freq = LAYER_INTERSECT_COUNT_1;
		break;
	case 2:
		min_ddr_freq = LAYER_INTERSECT_COUNT_2;
		break;
	case 3:
		min_ddr_freq = LAYER_INTERSECT_COUNT_3;
		break;
	default:
		min_ddr_freq = MIN_FULL_OVC_0;
		break;	
	}
    } else {
    switch (count) {
        case 1:
            min_ddr_freq = (rotate == 0) ? MIN_FULL_OVC_1 : MIN_FULL_OVC_1_ROTATE;
            break;
        case 2:
            min_ddr_freq = (rotate == 0) ? MIN_FULL_OVC_2 : MIN_FULL_OVC_2_ROTATE;
            break;
        case 3:
            min_ddr_freq = (rotate == 0) ? MIN_FULL_OVC_3 : MIN_FULL_OVC_3_ROTATE;
            break;
	  case 4:
            min_ddr_freq = (rotate == 0) ? MIN_FULL_OVC_4 : MIN_FULL_OVC_4_ROTATE;
            break;
	  case 5:
            min_ddr_freq = (rotate == 0) ? MIN_FULL_OVC_5 : MIN_FULL_OVC_5_ROTATE;
            break;
        default:
            min_ddr_freq = MIN_FULL_OVC_0;
            break;
    }
    }
    return min_ddr_freq;
}

STATIC int k3_fb_overlay_compose_check_ddr_min_freq(struct k3_fb_data_type *k3fd, u32 count, u32 rotate)
{
    /* 0: overlay enable
       -1: overlay disbale
    */
    unsigned long flags;
    u32 min_ddr_freq = 0;
    int ret = -1;
    bool need_qw = false;

    BUG_ON(k3fd->ovc_ddr_wq == NULL);

    min_ddr_freq = k3_fb_overlay_compose_get_target_ddr_min_freq(count, rotate);

    spin_lock_irqsave(&gralloc_overlay_slock, flags);
    k3fb_logi_display_debugfs("INCREASE: target ddr = %d, curr ddr = %d \n", min_ddr_freq, k3fd->ddr_min_freq);	
    /* printk("INCREASE: target ddr = %d, curr ddr = %d \n", min_ddr_freq, k3fd->ddr_min_freq); */
    if (isFHD == 1) {
		 k3fd->ddr_min_freq = min_ddr_freq;
	        queue_work(k3fd->ovc_ddr_wq, &k3fd->ovc_ddr_work);
		  if (k3fd->ddr_curr_freq >= min_ddr_freq) {
	        	ret = 0;
	    	  }
     } else {
	
	    if (min_ddr_freq > k3fd->ddr_min_freq) {
	        need_qw = true;
	        k3fd->ddr_min_freq = min_ddr_freq;
	        queue_work(k3fd->ovc_ddr_wq, &k3fd->ovc_ddr_work);
	    }

	    k3fb_logi_display_debugfs(" k3_fb_get_current_ddr_freq = %d \n",  k3fd->ddr_curr_freq);  
	    /* printk("%s: k3_fb_get_current_ddr_freq = %d \n", __func__, k3fd->ddr_curr_freq); */
	    if (k3fd->ddr_curr_freq >= min_ddr_freq) {
	        ret = 0;
	    } else {
	        if (!need_qw) {
	            queue_work(k3fd->ovc_ddr_wq, &k3fd->ovc_ddr_work);
	        }
	        k3fd->ovc_ddr_failed = 1;
	    }
      }
    spin_unlock_irqrestore(&gralloc_overlay_slock, flags);

    return ret;
}


void k3_fb_overlay_compose_data_clear(struct k3_fb_data_type *k3fd)
{
    int i;

    k3fd->ovc_type = OVC_NONE;
    k3fd->ovc_ch_count = 0;

#if defined(EDC_CH_CHG_SUPPORT)
    k3fd->ch_chg_flag = false;
    k3fd->ch_chg_power_off = false;
#endif /* EDC_CH_CHG_SUPPORT */
    k3fd->ovc_idle_flag = false;

    for (i = 0; i< MAX_EDC_CHANNEL; i++) {
        if (k3fd->ovc_wait_state[i]) {
            /* wake up buffer sync before suspend */
            k3fd->ovc_wait_state[i] = false;
            k3fd->ovc_wait_flag[i] = true;
            wake_up_interruptible(&gralloc_overlay_wait_queue);
        } else {
            k3fd->ovc_wait_flag[i] = false;
            k3fd->ovc_lock_addr[i] = 0;
            k3fd->ovc_lock_size[i] = 0;
        }

        k3fd->ovc_ch_gonna_display_addr[i] = 0;
        k3fd->ovc_ch_display_addr[i] = 0;
        memset(&k3fd->ovc_req[i], 0, sizeof(k3fd->ovc_req[i]));
    }

    if (k3fd->ddr_min_freq > 0) {
        k3fd->ddr_min_freq = 0;
#ifndef PC_UT_TEST_ON
        pm_qos_update_request(&k3fd->ovc_ddrminprofile, k3fd->ddr_min_freq);
#endif
    }
    k3fd->ddr_min_freq_saved = 0;
    k3fd->ddr_curr_freq = 0;
    k3fd->ovc_ddr_failed = 0;
#if defined(CONFIG_OVERLAY_COMPOSE)
    k3fd->ddrIdleCount = 0;
#endif

}

int k3_fb_overlay_fence_create(struct sw_sync_timeline * timeline, const char * fence_name, unsigned value)
{
	int fd;
	struct sync_fence *fence;
	struct sync_pt *pt;

	if(timeline == NULL){
		return -EINVAL;
	}

	fd = get_unused_fd();
	if(fd < 0){
		k3fb_loge("failed to get fd in create fence!\n");
		return fd;
	}

	pt = sw_sync_pt_create(timeline,value);
	if(pt == NULL){
		put_unused_fd(fd);
		k3fb_loge("failed to create pt in create fence!\n");
		return -ENOMEM;
	}

	fence = sync_fence_create(fence_name,pt);
	if(fence == NULL){
		sync_pt_free(pt);
		put_unused_fd(fd);
		k3fb_loge("failed to create fence in create fence!\n");
		return -ENOMEM;
	}

	sync_fence_install(fence,fd);

	return fd;
}

int k3_fb_overlay_fence_wait(int fence_fd, long timeout)
{
	int err;
	struct sync_fence *fence = NULL;

	fence = sync_fence_fdget(fence_fd);
	if(fence == NULL){
		k3fb_loge("failed to get fence!\n");
		return -EINVAL;
	}

	err = sync_fence_wait(fence,timeout);
	if(err == -ETIME)
		err = sync_fence_wait(fence,10 * MSEC_PER_SEC);

	if(err < 0){
		k3fb_loge("failed to wait fence!\n");
	}

	sync_fence_put(fence);
	return 0;
}

static void k3_fb_gralloc_overlay_ch_process(struct k3_fb_data_type *k3fd)
{
    volatile bool cfg_ok;
    volatile u32 ch1_en;
    volatile u32 ch2_en;
    volatile u32 crs_en;
    volatile u32 gnew1_en;
    volatile u32 gnew2_en;
    volatile u32 ch_addr[MAX_EDC_CHANNEL];
    int i;
    volatile u32 ch1_rotate = 0;
    u32 min_ddr_freq = 0;
    bool addr_changed = false;

    spin_lock(&gralloc_overlay_slock);

    cfg_ok = edc_overlay_compose_get_cfg_ok(k3fd);
    /* edc will load data when cfg_ok reset to 0 */
    if (cfg_ok) {
        /* printk("k3_fb_gralloc_overlay_ch_process error----\n"); */
        spin_unlock(&gralloc_overlay_slock);
        return;
    }

    ch1_en = edc_overlay_compose_get_ch1_state(k3fd);
    ch2_en = edc_overlay_compose_get_ch2_state(k3fd);
    crs_en = edc_overlay_compose_get_crs_state(k3fd);
    gnew1_en = edc_overlay_compose_get_gnew1_state(k3fd);
    gnew2_en = edc_overlay_compose_get_gnew2_state(k3fd);

    memset((void*)ch_addr, 0, sizeof(ch_addr));
    if (ch1_en) {
        ch_addr[0] = inp32(k3fd->edc_base + EDC_CH1L_ADDR_OFFSET);
	 ch1_rotate = edc_overlay_compose_reg_get_ch1_rotation(k3fd);
    }

    if (ch2_en) {
        ch_addr[1] = inp32(k3fd->edc_base + EDC_CH2L_ADDR_OFFSET);
    }

    if (crs_en) {
        ch_addr[2] = inp32(k3fd->edc_base + EDC_CRSL_ADDR_OFFSET);
    }

    if (gnew1_en) {
        ch_addr[3] = inp32(k3fd->edc_base + EDC_GNEW1_ADDR_OFFSET);
    }

    if (gnew2_en) {
        ch_addr[4] = inp32(k3fd->edc_base + EDC_GNEW2_ADDR_OFFSET);
    }
	
#if defined(EDC_CH_CHG_SUPPORT)
    k3_fb_overlay_compose_edc1_poweroff(k3fd);
#endif
    k3_fb_gralloc_overlay_restore_display_addr(k3fd);

    for (i=0; i<MAX_EDC_CHANNEL; i++) {
        if (ch_addr[i] != k3fd->ovc_ch_display_addr[i]) {
            addr_changed = true;
            if (k3fd->ovc_ch_display_addr[i] != 0 && k3fd->ovc_lock_addr[i] != 0
                && !BUFFER_IS_USED(ch_addr[i], k3fd->ovc_lock_addr[i], k3fd->ovc_lock_size[i])) {
                k3fd->ovc_wait_flag[i] = true;
                wake_up_interruptible(&gralloc_overlay_wait_queue);
            }
        }
        k3fd->ovc_ch_display_addr[i] = ch_addr[i];
    }

    if (isFHD == 0) {
	    	min_ddr_freq = k3_fb_overlay_compose_get_target_ddr_min_freq(ch1_en + ch2_en + gnew1_en + gnew2_en + crs_en, ch1_rotate);
		if (min_ddr_freq < k3fd->ddr_min_freq) {
		        if (k3fd->ovc_ddr_failed && addr_changed) {
		            k3fd->ovc_ddr_failed = 0;
		        } else if (k3fd->ovc_ddr_failed == 0) {
		            k3fd->ddr_min_freq = min_ddr_freq;
		            if (k3fd->ovc_ddr_wq) {
		                queue_work(k3fd->ovc_ddr_wq, &k3fd->ovc_ddr_work);
		            }
		        }
	    }
    }

    spin_unlock(&gralloc_overlay_slock);

}

static char gBufferUsed = 0;
static int k3_fb_gralloc_overlay_buffer_is_busy(struct k3_fb_data_type *k3fd, u32 addr, u32 size)
{
    int i;
    gBufferUsed = 0;
    for (i=0; i<MAX_EDC_CHANNEL; i++) {
        if (BUFFER_IS_USED(k3fd->ovc_ch_display_addr[i], addr, size) || BUFFER_IS_USED(k3fd->ovc_ch_gonna_display_addr[i], addr, size)) {
            k3fd->ovc_lock_addr[i] = addr;
            k3fd->ovc_lock_size[i] = size;
            gBufferUsed = 1;
            return i;
        }
    }
    return -1;
}

static int k3_fb_gralloc_overlay_read_proc(char* page, char** start, off_t off, int count, int* eof, void* data)
{
    page[off] = gBufferUsed;
    return 1;
}

static int k3_fb_gralloc_overlay_write_proc(struct file *file, const char *buffer, unsigned long count, void *data)
{
    char buf[20] = {0};
    struct k3_fb_data_type *k3fd = NULL;
    unsigned long flags;
    u32 buf_addr;
    u32 buf_size;
    int curr = 0;

    k3fd = k3fd_list[0];
    BUG_ON(k3fd == NULL);

    if (copy_from_user(buf, buffer, count)) {
        printk("%s:copy_from_user Error\n", __func__);
        return 0;
    }

    buf[19] = '\0';
    k3_fb_overlay_compose_parse_buffer(buf, &buf_addr, &buf_size);
    //printk("parse buffer:addr=0x%x, size=%d\n", buf_addr, buf_size);

    spin_lock_irqsave(&gralloc_overlay_slock, flags);
    curr = k3_fb_gralloc_overlay_buffer_is_busy(k3fd, buf_addr, buf_size);
    spin_unlock_irqrestore(&gralloc_overlay_slock, flags);
    return 0;
}

void k3_fb_gralloc_overlay_save_display_addr(struct k3_fb_data_type *k3fd, int ch, u32 addr)
{
    if (ch >= MAX_EDC_CHANNEL) {
    	k3fb_loge("ch = %d is overflow \n", ch);
    	return;
    }

    k3fd->ovc_ch_gonna_display_addr[ch] = addr;
}

void k3_fb_gralloc_overlay_restore_display_addr(struct k3_fb_data_type *k3fd)
{
    int i;
    for (i = 0; i < MAX_EDC_CHANNEL; i++) {
        k3fd->ovc_ch_gonna_display_addr[i] = 0;
    }
}

/* overlay compose ilde will switch to g2d */
static DECLARE_WAIT_QUEUE_HEAD(overlay_idle_wait_queue);

static void k3_fb_overlay_idle_notice(struct k3_fb_data_type *k3fd)
{
    u32 count;
    const u32 idle_ch_count = 1;
    bool need_notice = false;
    volatile u32 ch1_en = edc_overlay_compose_get_ch1_state(k3fd);
    volatile u32 ch1_rotate = edc_overlay_compose_reg_get_ch1_rotation(k3fd);
    volatile u32 ch2_en = edc_overlay_compose_get_ch2_state(k3fd);
    volatile u32 ch2_fmt = edc_overlay_compose_get_ch2_fmt(k3fd);
    volatile u32 crs_en = edc_overlay_compose_get_crs_state(k3fd);
    volatile u32 gnew1_en = edc_overlay_compose_get_gnew1_state(k3fd);
    volatile u32 gnew2_en = edc_overlay_compose_get_gnew2_state(k3fd);

    count = ch1_en + ch2_en + crs_en + gnew1_en + gnew2_en;
    if (count > idle_ch_count) {
        /* 2 or 3 channels working need to notice */
        need_notice = true;
    } else if (count == idle_ch_count && ch1_rotate != 0) {
        /* 1 rotate ch need to notice for ddr */
        need_notice = true;
    }

    /*g2d compose && fb fmt is rgb565*/
    if (ch2_en && (1 == count)  && (ch2_fmt == 0x1)){
        need_notice = true;
    }

    if (need_notice) {
        k3fd->ovc_idle_flag = true;
        wake_up_interruptible(&overlay_idle_wait_queue);
    }
}

static ssize_t k3_fb_overlay_idle_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    struct k3_fb_data_type *k3fd = NULL;
    int ret = 0;

    k3fd = k3fd_list[0];
    BUG_ON(k3fd == NULL);

   ret = wait_event_interruptible(overlay_idle_wait_queue, k3fd->ovc_idle_flag);
   k3fd->ovc_idle_flag = false;
   return 0;
}

static int k3_fb_overlay_compose_wait_event(struct k3_fb_data_type *k3fd)
{
    if (wait_event_interruptible_timeout(k3fd->frame_wq, k3fd->update_frame, HZ / 10) <= 0) {
        k3fb_loge("wait_event_interruptible_timeout\n");
        k3fd->update_frame = 0;
        return -ETIME;
    }
    k3fd->update_frame = 0;
    return 0;
}

/*overlaylib queuebuffer*/
static int k3_fb_overlay_compose_play(struct fb_info *info, struct overlay_data req, unsigned long *argp)
{
    struct k3_fb_data_type *k3fd = NULL;
    int i;
    int ret = 0;
    int fenceId = 0;
    int index = 0;
    uint32_t cfg_disable = 0;
    unsigned long flags;
    int wait_ret = 0;
    bool cmd_mode;
    u32 pre_type;
    u32 pre_count;

    BUG_ON(info == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;
    BUG_ON(k3fd == NULL);

    index = req.id % MAX_EDC_CHANNEL;

    memcpy(&k3fd->ovc_req[index], &req, sizeof(req));
    cfg_disable = edc_overlay_compose_get_cfg_disable(info, req.id);

    if (!cfg_disable) {
        pre_type = k3fd->ovc_type;
        k3fd->ovc_type = k3fd->ovc_req[index].src.compose_mode;
#if CONFIG_WFD_FBINFO
        if (k3fd->ovc_type != OVC_NONE)
        {
            wfd_fbi.bpp = 0;
        }
#endif
        pre_count = k3fd->ovc_ch_count;
		k3fd->ovc_ch_count = 0;
        for (i = 0; i < MAX_EDC_CHANNEL; i++) {
        	if (k3fd->ovc_req[i].src.phy_addr != 0) {
        		k3fd->ovc_ch_count ++;
        	}
        }

        cmd_mode = (k3fd->panel_info.type == PANEL_MIPI_CMD);
        if (cmd_mode) {
        #if CLK_SWITCH
            /* enable edc clk */
            clk_enable(k3fd->edc_clk);
            /* enable ldi clk */
            clk_enable(k3fd->ldi_clk);
        #endif
        } else {
            //normal mode
            wait_ret = k3_fb_overlay_compose_wait_event(k3fd);
            if (wait_ret < 0) {
                return wait_ret;
            }
        }

        down(&k3_fb_blank_sem);
	if (!k3fd->panel_power_on) {
		up(&k3_fb_blank_sem);
		return -ETIME;
	}
     	   	/*down(&k3fd->sem);*/
        	spin_lock_irqsave(&gralloc_overlay_slock, flags);

        for (i = 0; i < MAX_EDC_CHANNEL; i++) {
        	if (k3fd->ovc_req[i].src.phy_addr != 0) {
        		/* new add when the pipe cfg_disable = false ,this pipe must be config at last */
        		if (index == i) {
        			continue;
        		}
            	ret = edc_overlay_compose_play(info, &k3fd->ovc_req[i]);
            }
		if (k3fd->ovc_req[i].src.phy_addr == 0) {
			edc_overlay_compose_ch_unset(info, i);
		}
            memset(&k3fd->ovc_req[i], 0, sizeof(k3fd->ovc_req[i]));
        }

        /* new add */
		ret = edc_overlay_compose_play(info, &k3fd->ovc_req[index]);
		memset(&k3fd->ovc_req[index], 0, sizeof(k3fd->ovc_req[index]));
        spin_unlock_irqrestore(&gralloc_overlay_slock, flags);
        /*up(&k3fd->sem);*/

	#ifndef PC_UT_TEST_ON
	    trace_dot(SF, "8", 0);
	#endif
        if (cmd_mode) {
        #if defined(CONFIG_OVERLAY_COMPOSE)
    	    /* Clear idle count */
	    k3fd->ddrIdleCount = 0;
	    #endif

            k3fb_te_inc(k3fd, true, false);
            set_LDI_CTRL_ldi_en(k3fd->edc_base, K3_ENABLE);

            /* enable fake vsync timer */
            if (k3fd->frc_state != K3_FB_FRC_IDLE_PLAYING) {
                k3fd->use_cmd_vsync = (k3fb_frc_get_fps(k3fd) < K3_FB_FRC_NORMAL_FPS ? true : false);
            }

            k3fb_logi_vsync_debugfs("k3fd->use_cmd_vsync = %d, k3fd->frc_state = %d \n", k3fd->use_cmd_vsync, k3fd->frc_state);

            wait_ret = k3_fb_overlay_compose_wait_event(k3fd);
            if (wait_ret < 0 ||(k3fd->esd_recover == true)) {
					if (k3fd->esd_recover == true) {
                    	k3fb_loge("ESD recover!\n");
			}
				k3fd->esd_recover = false;
                if (k3fd->panel_info.esd_enable) {
                    ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, info,0);
                    if (ret != 0) {
                        k3fb_loge("can't turn off display!\n");
		          up(&k3_fb_blank_sem);
                        return ret;
                    }
                    ret = k3_fb_blank_sub(FB_BLANK_UNBLANK, info,0);
                    if (ret != 0) {
                        k3fb_loge("can't turn on display!\n");
		          up(&k3_fb_blank_sem);
                        return ret;
                    }
		
                }
               	k3fb_te_dec(k3fd, false, false);
		up(&k3_fb_blank_sem);
                return wait_ret;
            }

            k3fb_te_dec(k3fd, false, false);
        }
		if(k3fd->index == 0){
			fenceId = k3_fb_overlay_fence_create(k3fd->timeline, "display", ++k3fd->timeline_max);
			
		 	if(fenceId < 0)
		 	{
		 		k3fb_loge("failed to create fence!\n");
		 	}

			 spin_lock_irqsave(&k3fd->refresh_lock,flags);
		 	 k3fd->refresh ++;
			 spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
		  	req.src.release_fence = fenceId;
		 	if((fenceId>=0)&&copy_to_user((struct overlay_data __user*)argp, &req, sizeof(struct overlay_data)))
		 	{
				fenceId = -EFAULT;
				k3fb_loge("failed to copy fence to user!\n");
				put_unused_fd(req.src.release_fence);
				up(&k3_fb_blank_sem);

				return fenceId;
		 	}
		}
		up(&k3_fb_blank_sem);
    }

    if (k3fd->temp_wq)
        queue_work(k3fd->temp_wq, &k3fd->temp_work);

    return ret;
}

#if 0
/* overlay compose partial */
STATIC int k3_fb_overlay_compose_partial_state(struct fb_info *info, struct st_k3_fb_partial_ovc_ch *ovc_partial_info)
{
    int i;
    u32 is_ovc;
    int index = 0;

    if ((NULL == info) || (NULL == ovc_partial_info)) {
		k3fb_loge("info or ovc_partial_info is null");
    	return -EINVAL;
    }

    memset(ovc_partial_info, 0, sizeof(struct st_k3_fb_partial_ovc_ch));
    ovc_partial_info->pan_play_info_ch = -1;

    for (i = 0; i < MAX_EDC_CHANNEL; i++) {
        is_ovc = edc_overlay_compose_get_state(info, i);
        if (!is_ovc) {
            continue;
        }
        ovc_partial_info->ovc_ch_count ++;
        ovc_partial_info->ovc_ch_index[index] = i;		/* depend on the channel id is ascending and sequential */
        index ++;
		if (ovc_partial_info->pan_play_info_ch != -1) {
			continue;
		}
        if (edc_overlay_compose_get_overlay_0_ch(info, i)) {
			ovc_partial_info->pan_play_info_ch = i;
        }
    }

    return 0;
}
#endif

#if 0
/* partial compose never use to pan_display */
STATIC int k3_fb_overlay_compose_partial_play(struct fb_var_screeninfo *var, struct fb_info *info, struct st_k3_fb_partial_ovc_ch *ovc_partial_info)
{
    struct k3_fb_data_type *k3fd = NULL;
    int ret = 0;
    int wait_ret = 0;
    unsigned long flags;
    int i;
    bool cmd_mode;
    u32 pre_type;
    u32 pre_count;

    BUG_ON(info == NULL);
    BUG_ON(ovc_partial_info == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;
    BUG_ON(k3fd == NULL);

    pre_type = k3fd->ovc_type;
    k3fd->ovc_type = OVC_PARTIAL;
    pre_count = k3fd->ovc_ch_count;
    k3fd->ovc_ch_count = ovc_partial_info->ovc_ch_count + 1;

    cmd_mode = (k3fd->panel_info.type == PANEL_MIPI_CMD);
    if (cmd_mode) {
    #if CLK_SWITCH
        /* enable edc clk */
        clk_enable(k3fd->edc_clk);
        /* enable ldi clk */
        clk_enable(k3fd->ldi_clk);
    #endif
    } else {
        wait_ret = k3_fb_overlay_compose_wait_event(k3fd);
        if (wait_ret < 0) {
            return wait_ret;
        }
    }


    spin_lock_irqsave(&gralloc_overlay_slock, flags);
    /*unset crs overlay if necessary*/
    edc_overlay_compose_pipe_unset_previous(info, pre_type, pre_count);
#if defined(EDC_CH_CHG_SUPPORT)
    edc_overlay_compose_ch_chg_disable(k3fd, info);
#endif /* EDC_CH_CHG_SUPPORT */
    for (i = 0; i < ovc_partial_info->ovc_ch_count; i++) {
		k3fb_logi("ovc_partial_info->ovc_ch_index[%d] = %d \n", i,ovc_partial_info->ovc_ch_index[i]);
        ret = edc_overlay_compose_play(info, &k3fd->ovc_req[ovc_partial_info->ovc_ch_index[i]]);
    }

	/* only k3fd->graphic_ch is not set to overlay compose when ovc_type is OVC_PARTIAL */
    ret = edc_overlay_compose_pan_display(var, info, ovc_partial_info->pan_play_info_ch);
    spin_unlock_irqrestore(&gralloc_overlay_slock, flags);

    if (cmd_mode) {

    #if defined(CONFIG_OVERLAY_COMPOSE)
	// Clear idle count
	k3fd->ovcIdleCount = 0;
    #endif

        k3fb_te_inc(k3fd, true);

        /* enable fake vsync timer */
        if (k3fd->frc_state != K3_FB_FRC_IDLE_PLAYING) {
            k3fd->use_cmd_vsync = (k3fb_frc_get_fps(k3fd) < K3_FB_FRC_NORMAL_FPS ? true : false);
        }

        k3fb_logi_vsync_debugfs("k3fd->use_cmd_vsync = %d, k3fd->frc_state = %d \n", k3fd->use_cmd_vsync, k3fd->frc_state);

        wait_ret = k3_fb_overlay_compose_wait_event(k3fd);
        if (wait_ret < 0) {
            if (k3fd->panel_info.esd_enable) {
                k3_fb_blank_sub(FB_BLANK_POWERDOWN, info,0);
                k3_fb_blank_sub(FB_BLANK_UNBLANK, info,0);
                k3fb_loge("ESD recover!\n");
            }
            k3fb_te_dec(k3fd, false);
            return wait_ret;
        }

        /* report vsync with timer */
        if (k3fd->use_cmd_vsync) {
            hrtimer_restart(&k3fd->cmd_vsync_hrtimer);
            k3fb_te_dec(k3fd, true);
        } else {
            hrtimer_cancel(&k3fd->cmd_vsync_hrtimer);
            k3fb_te_dec(k3fd, false);
        }
    }
    if (k3fd->temp_wq)
        queue_work(k3fd->temp_wq, &k3fd->temp_work);
    return ret;
}

#endif


STATIC int k3fb_ovc_check_ddr_freq(struct fb_info *info, unsigned long *argp)
{
    char buf[8];
    int buf_len;
    int ret = 0;
    struct k3_fb_data_type *k3fd = NULL;
    u32 hwc_count;
    u32 hwc_rotate;

    BUG_ON(info == NULL);
    k3fd = (struct k3_fb_data_type *)info->par;
    BUG_ON(k3fd == NULL);

    if (argp == NULL) {
        return -EFAULT;
    }
    buf_len = min(strlen((char *)argp), sizeof(buf) - 1);
    ret = copy_from_user(buf, argp, buf_len);
    if (ret) {
        k3fb_loge("copy from user failed \n");
        return -EFAULT;
    }

    buf[buf_len] = '\0';
    k3_fb_overlay_compose_parse_buffer(buf, &hwc_count, &hwc_rotate);
    /* printk("%s: count = %d, rotate = %d \n", __func__, hwc_count, hwc_rotate); */
    ret = k3_fb_overlay_compose_check_ddr_min_freq(k3fd, hwc_count, hwc_rotate);
    k3fb_logi_display_debugfs("check_ddr_freq return[%d]\n",ret);
    return ret;
}

#ifdef CONFIG_FB_CHECK_MIPI_TR
static int k3_fb_monitor_lcd_status(struct k3_fb_data_type *k3fd)
{
	int ret = CHECK_MIPI_TR_OK;
	struct k3_fb_panel_data *pdata = NULL;

	pdata = dev_get_platdata(&k3fd->pdev->dev);
	BUG_ON(pdata == NULL);
		if ((pdata) && (pdata->check_mipi_tr)) {
			down(&k3fd->sem);
			ret = pdata->check_mipi_tr(k3fd->pdev);
			if (ret == 0) {
				ret = CHECK_MIPI_TR_OK;
			} else {
				ret = CHECK_MIPI_TR_FAIL;
			}
			up(&k3fd->sem);
		} else {
			k3fb_loge("This panel can not support check mipi tr function");
			ret = CHECK_MIPI_TR_FAIL;
		}

	return ret;
}

static int k3_fb_check_mipi_tr(struct fb_info *info)
{
	int ret = CHECK_MIPI_TR_OK;
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		k3fb_logw("system is now power off !\n");
		ret = CHECK_MIPI_TR_FAIL;
		goto check_mipi_tr_error;
	}
	ret = k3_fb_monitor_lcd_status(k3fd);
#if 0
	if (ret != CHECK_MIPI_TR_OK) {
		k3_fb_blank_sub(FB_BLANK_POWERDOWN, info, 1);
		mdelay(10);
		k3_fb_blank_sub(FB_BLANK_UNBLANK, info, 1);
		mdelay(10);
		ret = k3_fb_monitor_lcd_status(k3fd);
	}
#endif
check_mipi_tr_error:
	return ret;
}
#endif

#ifdef CONFIG_FB_SET_INVERSION
static int k3_fb_set_inversion_type(struct fb_info *info, void *argp)
{
	int ret = 0;
	struct k3_fb_panel_data *pdata = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	unsigned int lcd_display_inversion = 0;

	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);
	ret = copy_from_user(&lcd_display_inversion, argp, sizeof(lcd_display_inversion));
	if (ret){
		printk(KERN_ERR "%s:K3FB_SET_INVERSION copy from user failed \n", __func__);
		return ret;
	}

	pdata = dev_get_platdata(&k3fd->pdev->dev);
	BUG_ON(pdata == NULL);

	if ((pdata) && (pdata->set_inversion_type))
	{
		down(&k3fd->sem);
		ret = pdata->set_inversion_type(k3fd->pdev, lcd_display_inversion);
		up(&k3fd->sem);
	}
	else
	{
		printk("This panel can not support dynamic set inversion type");
		return -EINVAL;
	}

	return ret;
}
#endif

#ifdef CONFIG_FB_MIPI_DETECT
static int k3_fb_mipi_detect(struct fb_info *info)
{
	int ret = -1;
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_fb_panel_data *pdata = NULL;

	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		k3fb_logw("system is now power off !\n");
		ret = -1;
		goto mipi_detect_error;
	}

	pdata = dev_get_platdata(&k3fd->pdev->dev);
	BUG_ON(pdata == NULL);

	if ((pdata) && (pdata->mipi_detect)) {
		down(&k3fd->sem);
		ret = pdata->mipi_detect(k3fd->pdev);
		up(&k3fd->sem);
	} else {
		k3fb_loge("This panel can not support mipi detect function");
		ret = -1;
	}

mipi_detect_error:
	return ret;
}
#endif


static int k3_fb_overlay_compose_init(struct k3_fb_data_type *k3fd)
{
    int err = 0;

    struct proc_dir_entry *ent;
    /* Creating read/write "gralloc overlay" entry, rwx:111 */
    ent = create_proc_entry(OVC_BUFFER_SYNC_FILE, 0666, NULL);
    if (ent == NULL) {
        k3fb_loge("Unable to create /proc/gralloc_overlay_state entry\n");
        err = -1;
        return err;
    }
    ent->read_proc = k3_fb_gralloc_overlay_read_proc;
    ent->write_proc = k3_fb_gralloc_overlay_write_proc;

#ifndef PC_UT_TEST_ON
    pm_qos_add_request(&k3fd->ovc_ddrminprofile, PM_QOS_DDR_MIN_PROFILE, 0);

    err = ipps_register_client(&k3_fb_ipps_client);
    if (err != 0) {
        k3fb_loge("k3_fb_ddr_ipps register client failed, please check!");
        return err;
    }

    k3_fb_overlay_compose_create_ddr_workqueue(k3fd);
#endif

    return err;
}


static void k3_fb_overlay_compose_deinit(struct k3_fb_data_type *k3fd)
{
    remove_proc_entry(OVC_BUFFER_SYNC_FILE, NULL);
#ifndef PC_UT_TEST_ON
    pm_qos_remove_request(&k3fd->ovc_ddrminprofile);
    ipps_unregister_client(&k3_fb_ipps_client);
#endif
    k3_fb_overlay_compose_destroy_ddr_workqueue(k3fd);


}

static void k3_fb_overlay_compose_reset_pipe(struct fb_info *info)
{
    int i;

    for (i = OVERLAY_PIPE_EDC0_CH1; i < OVERLAY_PIPE_MAX; i++) {
        if (i == OVERLAY_PIPE_EDC1_CH1 || i == OVERLAY_PIPE_EDC1_CH2) {
            continue;
        }
        edc_overlay_compose_pre_unset(info, i);
    }
}
#endif //CONFIG_OVERLAY_COMPOSE

#if defined(CONFIG_OVERLAY_COMPOSE)
#ifndef PC_UT_TEST_ON
static DEVICE_ATTR(overlay_idle_state, (S_IRUGO | S_IWUSR | S_IWGRP),
	k3_fb_overlay_idle_show, 0);
static DEVICE_ATTR(lcd_mipi_freq, (S_IRUGO | S_IWUSR | S_IWGRP),
	NULL, k3_fb_set_dsi_freq_store);
#endif
#endif //CONFIG_OVERLAY_COMPOSE

static struct attribute *k3_fb_attrs[] = {
#if defined(CONFIG_OVERLAY_COMPOSE)
#ifndef PC_UT_TEST_ON
	&dev_attr_overlay_idle_state.attr,
	&dev_attr_lcd_mipi_freq.attr,
#endif
#endif //CONFIG_OVERLAY_COMPOSE
	NULL
};


/*******************************************************************************
**
*/

static struct attribute_group k3_fb_attr_group = {
	.attrs = k3_fb_attrs,
};

STATIC int k3_fb_sysfs_create(struct platform_device *pdev)
{
	int ret = 0;

	ret = sysfs_create_group(&pdev->dev.kobj, &k3_fb_attr_group);
	if (ret) {
		k3fb_loge("create sysfs file failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

static void k3_fb_sysfs_remove(struct platform_device *pdev)
{
	sysfs_remove_group(&pdev->dev.kobj, &k3_fb_attr_group);
}

static void sbl_workqueue(struct work_struct *ws)
{
	static unsigned int ALold;
	unsigned int res;
	int m = 3;
	u32 lsensor_h = 0;
	u32 lsensor_l = 0;
	u32 tmp_sbl = 0;
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = container_of(ws, struct k3_fb_data_type, sbl_work);
	BUG_ON(k3fd == NULL);

	down(&k3_fb_blank_sem);
	if (!k3fd->panel_power_on) {
		up(&k3_fb_blank_sem);
		return;
	}

	tmp_sbl = inp32(k3fd->edc_base + EDC_DISP_DPD_OFFSET);
	if ((tmp_sbl & REG_SBL_EN) == REG_SBL_EN) {
		res = ((ALold << m) + ((int)k3fd->sbl_lsensor_value << 14) - ALold) >> m;
		if (res != ALold) {
			ALold = res;
			lsensor_h = ((res >> 14) >> 8) & 0xff;
			lsensor_l = (res >> 14) & 0xff;
			set_SBL_AMBIENT_LIGHT_L_ambient_light_l(k3fd->edc_base, lsensor_l);
			set_SBL_AMBIENT_LIGHT_H_ambient_light_h(k3fd->edc_base, lsensor_h);
		}
	}
	up(&k3_fb_blank_sem);

}

static int init_sbl_workqueue(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	k3fd->sbl_wq = create_singlethread_workqueue("sbl_workqueue");
	if (!k3fd->sbl_wq) {
		k3fb_loge("failed to create sbl workqueue!\n");
		return -1;
	}

	INIT_WORK(&k3fd->sbl_work, sbl_workqueue);

	return 0;
}


static void temp_workqueue(struct work_struct *ws)
{
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = container_of(ws, struct k3_fb_data_type, temp_work);
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return;
	}

#ifdef CONFIG_K3V2_TEMP_GOVERNOR
	k3fd->ambient_temperature = getcalctemperature(ADC_RTMP_FOR_SIM);
#else
/* #error "undefined getcalctemperature \n"  */
/*#warning "undefined getcalctemperature \n" */   /* for compile succ */

#endif

}

static int init_temperature_workqueue(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);

	k3fd->temp_wq = create_singlethread_workqueue("temp_workqueue");
	if (!k3fd->temp_wq) {
		k3fb_loge("failed to create sbl workqueue!\n");
		return -1;
	}

	INIT_WORK(&k3fd->temp_work, temp_workqueue);

	return 0;
}


static int k3fb_wait_for_vsync_thread(void *data)
{
	struct k3_fb_data_type *k3fd = (struct k3_fb_data_type *)data;

	while (!kthread_should_stop()) {
		ktime_t timestamp = k3fd->vsync_info.timestamp;
		int ret = wait_event_interruptible(
						k3fd->vsync_info.wait,
						!ktime_equal(timestamp,k3fd->vsync_info.timestamp) &&
						k3fd->vsync_info.active);
		if (ret == 0) {
			char *envp[2];
			char buf[64];
			snprintf(buf, sizeof(buf), "VSYNC=%llu",
					ktime_to_ns(k3fd->vsync_info.timestamp));
			envp[0] = buf;
			envp[1] = NULL;
			k3fb_logi_vsync_debugfs("gongyu vsync report buf = %s k3fd->use_cmd_vsync = %d \n", buf,k3fd->use_cmd_vsync);
			kobject_uevent_env(&k3fd->pdev->dev.kobj, KOBJ_CHANGE, envp);
		}
	}

	return 0;
}

static int k3fb_fence_inc_thread(void *data)
{
	unsigned long  flag;
	struct k3_fb_data_type *k3fd = (struct k3_fb_data_type *)data;

	while (!kthread_should_stop()) {
		int ret = wait_event_interruptible(k3fd->fence_inc_wait,(k3fd->refresh > 0));
		if (ret == 0) {
			spin_lock_irqsave(&k3fd->refresh_lock, flag);
			sw_sync_timeline_inc(k3fd->timeline, 1);
			k3fd->refresh--;
			spin_unlock_irqrestore(&k3fd->refresh_lock, flag);
		}
	}
	return 0;
	
}
/******************************************************************************/
STATIC void k3fb_te_inc(struct k3_fb_data_type *k3fd, bool te_should_enable,bool in_isr)
{
    unsigned long  flag;

    if (in_isr) {
    	spin_lock(&k3fd->vsync_info.irq_lock);
    } else {
        spin_lock_irqsave(&k3fd->vsync_info.irq_lock, flag);
    }

	k3fd->vsync_info.te_refcount++;

	if (te_should_enable) {
        set_EDC_DSI_TE_CTRL_dsi_te_mask_en(0);
	}

	if (in_isr) {
    	spin_unlock(&k3fd->vsync_info.irq_lock);
    } else {
        spin_unlock_irqrestore(&k3fd->vsync_info.irq_lock, flag);
    }
}

STATIC void k3fb_te_dec(struct k3_fb_data_type *k3fd, bool te_should_disable, bool in_isr)
{
    unsigned long  flag;

    if (in_isr) {
    	spin_lock(&k3fd->vsync_info.irq_lock);
    } else {
        spin_lock_irqsave(&k3fd->vsync_info.irq_lock, flag);
    }

	if (k3fd->vsync_info.te_refcount > 0)
		k3fd->vsync_info.te_refcount--;

	if (k3fd->vsync_info.te_refcount <= 0 && te_should_disable) {
        set_EDC_DSI_TE_CTRL_dsi_te_mask_en(1);
	}

	if (in_isr) {
    	spin_unlock(&k3fd->vsync_info.irq_lock);
    } else {
        spin_unlock_irqrestore(&k3fd->vsync_info.irq_lock, flag);
    }
}


static int k3fb_frc_get_fps(struct k3_fb_data_type *k3fd)
{
	int fps = 0;
	BUG_ON(k3fd == NULL);

	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
		switch (k3fd->frc_state) {
		case K3_FB_FRC_GAME_PLAYING:
		case K3_FB_FRC_GAME_PLAYING | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_GAME_FPS_CMD;
			break;
		case K3_FB_FRC_SPECIAL_GAME_PLAYING:
		case K3_FB_FRC_SPECIAL_GAME_PLAYING | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_SPECIAL_GAME_FPS;
			break;
		/* Modifed for set frc, begin */
		case K3_FB_FRC_WEBKIT_PLAYING:
		case K3_FB_FRC_WEBKIT_PLAYING | K3_FB_FRC_IDLE_PLAYING:
		    fps = K3_FB_FRC_WEBKIT_FPS;
		    break;
		/* Modifed for set frc, end */
		default:
			fps = K3_FB_FRC_NORMAL_FPS;
			break;
		}
	} else {
		switch (k3fd->frc_state) {
		case K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_IDLE_FPS;
			break;
		case K3_FB_FRC_GAME_PLAYING:
		case K3_FB_FRC_GAME_PLAYING | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_GAME_FPS;
		    break;
        case K3_FB_FRC_SPECIAL_GAME_PLAYING:
        case K3_FB_FRC_SPECIAL_GAME_PLAYING | K3_FB_FRC_IDLE_PLAYING:
            fps = K3_FB_FRC_SPECIAL_GAME_FPS;
			break;
		case K3_FB_FRC_VIDEO_IN_GAME:
		case K3_FB_FRC_VIDEO_IN_GAME | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_VIDEO_FPS;
			break;
		case K3_FB_FRC_BENCHMARK_PLAYING:
		case K3_FB_FRC_BENCHMARK_PLAYING | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_BENCHMARK_FPS;
			break;
		case K3_FB_FRC_WEBKIT_PLAYING:
		case K3_FB_FRC_WEBKIT_PLAYING | K3_FB_FRC_IDLE_PLAYING:
			fps = K3_FB_FRC_WEBKIT_FPS;
			break;

	    case K3_FB_FRC_VIDEO_PLAYING:
	        fps = K3_FB_FRC_IDLE_FPS;
			break;

		case K3_FB_FRC_NONE_PLAYING:
		default:
			fps = K3_FB_FRC_NORMAL_FPS;
			break;
		}
	}


	return fps;
}

#if defined(CONFIG_OVERLAY_COMPOSE)
//#define CONFIG_IDLE_SWITCH_FEATURE
#endif

#if defined(CONFIG_IDLE_SWITCH_FEATURE)
static bool k3fb_frc_prepare(struct k3_fb_data_type *k3fd)
{
    int fps = K3_FB_FRC_NORMAL_FPS;
    /* for EDC0 only*/
#define MAXFPS (60)
#define PIPECOUNT (OVERLAY_PIPE_MAX - 2)
    static u32 oldAddr[PIPECOUNT];
    volatile u32 newAddr[PIPECOUNT];
    static u32 oldStatus;
    volatile u32 newStatus;
    static u32 frc_special_count;
    static int value[MAXFPS];
    int newPipeCount = 0;
    int i, j;
    int mThreshold;
    static int sumValue;
    static bool firstTime = true;
    if (time_after((k3fd->frc_timestamp  + HZ * 3), jiffies)) {
        return false;
    }

    fps = k3fb_frc_get_fps(k3fd);

    newAddr[1] = inp32(k3fd->edc_base + EDC_CH2L_ADDR_OFFSET);
    newAddr[0] = inp32(k3fd->edc_base + EDC_CH1L_ADDR_OFFSET);
    newAddr[2] = inp32(k3fd->edc_base + EDC_GNEW1_ADDR_OFFSET);
    newAddr[3] = inp32(k3fd->edc_base + EDC_GNEW2_ADDR_OFFSET);
    newAddr[4] = inp32(k3fd->edc_base + EDC_CRSL_ADDR_OFFSET);

    for(i = 0; i < PIPECOUNT; i++) {
        if(newAddr[i] != oldAddr[i]){
            newStatus |= 1 << i;
            newPipeCount++;
        }
        else{
            newStatus &= ~(1 << i);
        }
    }

    mThreshold = fps / 4 - 1;  //Threshold M = N/4 -1

    if(firstTime) {
        sumValue = mThreshold;
        firstTime = false;
    }

    if (fps > k3fd->panel_info.frame_rate) {
        k3fd->frc_threshold_count = 0;
        for(i = 0; i < PIPECOUNT; i++) {
            oldAddr[i] = newAddr[i];
        }
        oldStatus = newStatus;
        frc_special_count = 0;
        sumValue = mThreshold;
        return true;
    } else if (fps < k3fd->panel_info.frame_rate) {
        frc_special_count = 0;
        sumValue = mThreshold;

        if (newStatus == 0) {
            k3fd->frc_threshold_count++;

            if (k3fd->frc_threshold_count >= K3_FB_FRC_THRESHOLD) {
                k3fd->frc_threshold_count = 0;
                return true;
            }
        } else {
            k3fd->frc_threshold_count = 0;
        }
    }
    else {
        if (frc_special_count > fps || frc_special_count < 0){
            frc_special_count = MAXFPS - fps;
            sumValue -= value[frc_special_count];
        }

        if (newPipeCount == 0) {
            value[frc_special_count] = 0;
        }else if ((newPipeCount > 1) || ((newStatus & oldStatus) > 0)) {
            value[frc_special_count] = mThreshold;
        }else {
            value[frc_special_count] = 1;
        }

        sumValue += value[frc_special_count];
        frc_special_count++;

        if (sumValue < mThreshold){
            //k3_fb_overlay_idle_notice(k3fd);
            k3fd->ovc_idle_flag = true;
            wake_up_interruptible(&overlay_idle_wait_queue);
        }
    }

    for(i = 0; i < PIPECOUNT; i++) {
        oldAddr[i] = newAddr[i];
    }
    oldStatus = newStatus;
    return false;
}
#else
STATIC bool k3fb_frc_prepare(struct k3_fb_data_type *k3fd)
{
	int fps = K3_FB_FRC_NORMAL_FPS;
	static u32 addr_old;
	u32 addr_new;
#if defined(CONFIG_OVERLAY_COMPOSE)
	/* for ch1 */
	static u32 ch1_addr_old;
	volatile u32 ch1_addr_new;
	/* for crs */
	static u32 crs_addr_old;
	volatile u32 crs_addr_new;

	static u32 gnew1_addr_old;
	volatile u32 gnew1_addr_new;

	static u32 gnew2_addr_old;
	volatile u32 gnew2_addr_new;
	static u32 frc_special_count;
#endif /* CONFIG_OVERLAY_COMPOSE */

	if (time_after((k3fd->frc_timestamp  + HZ * 3), jiffies)) {
		return false;
	}

	addr_new = inp32(k3fd->edc_base + EDC_CH2L_ADDR_OFFSET);
#if defined(CONFIG_OVERLAY_COMPOSE)
	ch1_addr_new = inp32(k3fd->edc_base + EDC_CH1L_ADDR_OFFSET);
	crs_addr_new = inp32(k3fd->edc_base + EDC_CRSL_ADDR_OFFSET);

	gnew1_addr_new = inp32(k3fd->edc_base + EDC_GNEW1_ADDR_OFFSET);
	gnew2_addr_new = inp32(k3fd->edc_base + EDC_GNEW2_ADDR_OFFSET);
#endif /* CONFIG_OVERLAY_COMPOSE */

	fps = k3fb_frc_get_fps(k3fd);
	if (fps > k3fd->panel_info.frame_rate) {
		k3fd->frc_threshold_count = 0;
		addr_old = addr_new;
	#if defined(CONFIG_OVERLAY_COMPOSE)
		ch1_addr_old= ch1_addr_new;
		crs_addr_old = crs_addr_new;
        gnew1_addr_old = gnew1_addr_new;
		gnew2_addr_old = gnew2_addr_new;
		frc_special_count = 0;
	#endif /* CONFIG_OVERLAY_COMPOSE */

		return true;
	} else if (fps < k3fd->panel_info.frame_rate) {

	#if defined(CONFIG_OVERLAY_COMPOSE)
		frc_special_count = 0;
	#endif /* CONFIG_OVERLAY_COMPOSE */

		if ((addr_new == addr_old)
	#if defined(CONFIG_OVERLAY_COMPOSE)
		&& (ch1_addr_new == ch1_addr_old) && (crs_addr_new == crs_addr_old)
		&& (gnew1_addr_old == gnew1_addr_new) && (gnew2_addr_old == gnew2_addr_new)
	#endif /* CONFIG_OVERLAY_COMPOSE */
		) {
			k3fd->frc_threshold_count++;

			if (k3fd->frc_threshold_count >= K3_FB_FRC_THRESHOLD) {
				k3fd->frc_threshold_count = 0;
				return true;
			}
		} else {
			k3fd->frc_threshold_count = 0;
		}
	}
#if defined(CONFIG_OVERLAY_COMPOSE)
	else {
		/* for special scene idle to g2d*/
		if (((k3fd->frc_state == K3_FB_FRC_WEBKIT_PLAYING)
			|| (k3fd->frc_state == K3_FB_FRC_GAME_PLAYING)
			|| (k3fd->frc_state == K3_FB_FRC_SPECIAL_GAME_PLAYING))
			&& ((addr_new == addr_old) && (ch1_addr_new == ch1_addr_old) && (crs_addr_new == crs_addr_old)
			    && (gnew1_addr_old == gnew1_addr_new) && (gnew2_addr_old == gnew2_addr_new)))
		{
			frc_special_count ++;

			if (frc_special_count >= K3_FB_FRC_THRESHOLD) {
				k3_fb_overlay_idle_notice(k3fd);
				frc_special_count = 0;
			}
		}
		else
		{
			frc_special_count = 0;
		}
	}
#endif /* CONFIG_OVERLAY_COMPOSE */

	addr_old = addr_new;
#if defined(CONFIG_OVERLAY_COMPOSE)
	ch1_addr_old= ch1_addr_new;
	crs_addr_old = crs_addr_new;
	gnew1_addr_old = gnew1_addr_new;
	gnew2_addr_old = gnew2_addr_new;
#endif /* CONFIG_OVERLAY_COMPOSE */

	return false;
}
#endif /* CONFIG_IDLE_SWITCH_FEATURE */

STATIC int k3fb_frc_set(struct k3_fb_data_type *k3fd)
{
	int delay_count = 0;
	bool is_timeout = false;
	int tmp = 0;
	int fps = K3_FB_FRC_NORMAL_FPS;
	struct k3_fb_panel_data *pdata = NULL;

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->set_frc)) {
		k3fb_loge("no panel operation detected!\n");
		return 0;
	}

	/* wait dsi lane stop for 100us*/
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_PHY_STATUS_ADDR);
		if (((tmp & 0xA90) == 0xA90) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	}

	if (is_timeout) {
		k3fb_loge("wait dsi lane stop timeout.\n");
		return -1;
	}

	fps = k3fb_frc_get_fps(k3fd);
	if (fps == k3fd->panel_info.frame_rate) {
		/*k3fb_logi("no need to set frc.\n");*/
		return 0;
	}

	if (pdata->set_frc(k3fd->pdev,  fps) != 0) {
		k3fb_loge("set frc failed!\n");
		return -1;
	}/*else {
		k3fb_logi("now fps will be %d.\n", fps);
	}*/

#if defined(CONFIG_OVERLAY_COMPOSE)
	if (k3fd->frc_state == K3_FB_FRC_IDLE_PLAYING
		&& (k3fd->panel_info.frame_rate == K3_FB_FRC_IDLE_FPS)) {
		k3_fb_overlay_idle_notice(k3fd);
	}
#endif /* CONFIG_OVERLAY_COMPOSE */
	return 0;
}


/******************************************************************************
** handle ESD
*/

static bool k3fb_esd_prepare(struct k3_fb_data_type *k3fd)
{
	if (time_after((k3fd->esd_timestamp  + HZ * 3), jiffies)) {
		return false;
	}

	if (++k3fd->esd_frame_count >= K3_FB_ESD_THRESHOLD) {
		k3fd->esd_frame_count = 0;
		return true;
	} else {
		return false;
	}
}

static int k3fb_esd_set(struct k3_fb_data_type *k3fd)
{
	bool is_timeout = true;
	int delay_count = 0;
	u32 tmp = 0;

	/* check payload write empty */
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_CMD_PKT_STATUS_ADDR);
		if (((tmp & 0x00000005) == 0x00000005) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	}

	if (is_timeout) {
		k3fb_loge("ESD check payload write empty timeout.\n");
		return -EBUSY;
	}

	/* check dsi stop state */
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_PHY_STATUS_ADDR);
		if (((tmp & 0xA90) == 0xA90) || delay_count > 100) {
			is_timeout = (delay_count > 100) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	};

	if (is_timeout) {
		k3fb_loge("ESD check dsi stop state timeout.\n");
		return -EBUSY;
	}

	/* reset DSI */
	set_MIPIDSI_PWR_UP_shutdownz(0);

	/* check clock lane stop state */
	while (1) {
		tmp = inp32(k3fd->dsi_base + MIPIDSI_PHY_STATUS_ADDR);
		if (((tmp & 0x04) == 0x04) || delay_count > 500) {
			is_timeout = (delay_count > 500) ? true : false;
			delay_count = 0;
			break;
		} else {
			udelay(1);
			++delay_count;
		}
	};

	if (is_timeout) {
		k3fb_loge("ESD check clock lane stop state timeout.\n");
		/* Should't return. MUST power on DSI */
	}

	/* power on DSI */
	set_MIPIDSI_PWR_UP_shutdownz(1);

	return 0;
}

static enum hrtimer_restart k3fb_cmd_esd(struct hrtimer *timer)
{
	struct k3_fb_data_type *k3fd = NULL;

	k3fd  = container_of(timer, struct k3_fb_data_type, esd_hrtimer);
	BUG_ON(k3fd == NULL);
	
	k3fd->esd_hrtimer_enable = true;	
	hrtimer_start(&k3fd->esd_hrtimer, ktime_set(0, NSEC_PER_SEC), HRTIMER_MODE_REL);

	return HRTIMER_NORESTART;
}

static int get_fps_for_temperature(struct k3_fb_data_type *k3fd)
{
	static int last_tem_level = 4;

	static int fps_temp[4] = {
		FAKE_FPS_TEM_NORM_FPS,
		FAKE_FPS_TEM_ABOVE_NORM_FPS,
		FAKE_FPS_TEM_HIGH,
		FAKE_FPS_TEM_THRD,
	};

	int app_fps = 0;
	int temp_fps = 0;
	int temp = 0;

	BUG_ON(k3fd == NULL);

	temp = k3fd->ambient_temperature;
	app_fps = k3fb_frc_get_fps(k3fd);

	/* adjust temperature to LEVEL */
	if (temp <= EVT_TEM_NORM) {
		temp = 0;
	} else if (temp < EVT_TEM_ABOVE_NORM) {
		temp = 1;
	} else if (temp < EVT_TEM_HIGH) {
		temp = 2;
	} else if (temp < EVT_TEM_THRD) {
		temp = 3;
	} else {
		temp = 3;
	}

	temp_fps = fps_temp[temp];

	/* if temperature up/nochange in current app frame rate, slow down the frame rate. */
	if (temp > 0 && temp >= last_tem_level) {
		last_tem_level = temp;
		if (temp_fps >= app_fps) {
			temp++;
			if (temp > 3) {
				temp = 3;
			}
			temp_fps = fps_temp[temp];
		}
	} else {
		last_tem_level = temp;
	}

	/* Benchmark mode */
	if (k3fd->frc_state & K3_FB_FRC_BENCHMARK_PLAYING) {
		temp_fps = K3_FB_FRC_BENCHMARK_FPS;
	} else if (k3fd->frc_state == K3_FB_FRC_NONE_PLAYING) {
		temp_fps = K3_FB_FRC_NORMAL_FPS;
	}

	return temp_fps;
}
static enum hrtimer_restart k3fb_cmd_vsync(struct hrtimer *timer)
{
	struct k3_fb_data_type *k3fd = NULL;
	int fps = 0;
	int fps_for_temp = 60;

	k3fd  = container_of(timer, struct k3_fb_data_type, cmd_vsync_hrtimer);
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return HRTIMER_NORESTART;
	}

	if (k3fd->panel_info.frc_enable) {
		fps = k3fb_frc_get_fps(k3fd);
		/* Modified for set frc ,begin */
		if (k3fd->frc_state & K3_FB_FRC_SPECIAL_GAME_PLAYING){
		    fps = CMD_FPS_SPECIAL_GAME;
		}
		fps_for_temp = get_fps_for_temperature(k3fd);

		/*k3fb_loge("---ambient_temperature=%d, fps=%d, fps_for_temp=%d ---\n",
			k3fd->ambient_temperature, fps, fps_for_temp);*/

		fps = (fps_for_temp >= fps) ? fps : fps_for_temp;
	} else {
		fps = K3_FB_FRC_NORMAL_FPS;
	}

    /* Modified for set frc ,begin */
	if (k3fd->use_cmd_vsync && k3fd->vsync_info.active && k3fd->vsync_info.thread) {
		k3fd->vsync_info.timestamp = ktime_get();
		wake_up_interruptible_all(&k3fd->vsync_info.wait);
	}

#if defined(CONFIG_OVERLAY_COMPOSE)
	/*for overlay idle detect (only cmd display mode)*/
	if(!k3fd->vsync_info.active && k3fd->panel_info.type == PANEL_MIPI_CMD){

		if(k3fd->ddrIdleCount < K3_FB_EDC_IDLE_TIMEOUT){
			k3fd->ddrIdleCount++;
			if( k3fd->ddrIdleCount == K3_FB_EDC_IDLE_TIMEOUT) {
				u32 min_ddr_freq;

				min_ddr_freq = k3_fb_overlay_compose_get_target_ddr_min_freq(0, 0);
				spin_lock(&gralloc_overlay_slock);
				if (min_ddr_freq < k3fd->ddr_min_freq && k3fd->ovc_ddr_wq){
					k3fd->ddr_min_freq = min_ddr_freq;
					queue_work(k3fd->ovc_ddr_wq, &k3fd->ovc_ddr_work);
				}
				spin_unlock(&gralloc_overlay_slock);

			}
		}
	}else{
		k3fd->ddrIdleCount = 0;
	}
#endif

	hrtimer_start(&k3fd->cmd_vsync_hrtimer, ktime_set(0, NSEC_PER_SEC / fps), HRTIMER_MODE_REL);
	return HRTIMER_NORESTART;
}

/******************************************************************************
** handle isr
*/

#if 0
static int edc_isr_cmd_mode(struct k3_fb_data_type *k3fd, u32 ints)
{
	/*
	** check interrupt
	** 0x80 for bas_stat_int
	** 0x40 for bas_end_int
	*/

	if ((ints & 0x80) == 0x80) {
		
	    if (!k3fd->cmd_mode_refresh){
    		k3fd->cmd_mode_refresh = true;

            /* Add for set frc, begin */
    		if(k3fd->index == 0){
#if defined(CONFIG_OVERLAY_COMPOSE)
			k3_fb_gralloc_overlay_ch_process(k3fd);
#endif
    		}
    		/* Add for set frc, end */
		if (k3fd->panel_info.sbl_enable && k3fd->sbl_wq)
			queue_work(k3fd->sbl_wq, &k3fd->sbl_work);		
    	    }				
	}

	return IRQ_HANDLED;
}
#endif

static irqreturn_t edc_isr_video_mode(struct k3_fb_data_type *k3fd, u32 ints)
{
	/*
	** check interrupt
	** 0x80 for bas_stat_int
	** 0x40 for bas_end_int
	*/
	if((ints & 0x40) == 0x40){
	    if(k3fd->refresh && k3fd->fence_inc_thread){			
		  wake_up_interruptible(&k3fd->fence_inc_wait);		      				
	    }
	}
		
	if ((ints & 0x80) == 0x80) {
	#if defined(CONFIG_OVERLAY_COMPOSE)
	        k3_fb_gralloc_overlay_ch_process(k3fd);
	#endif
		k3fd->update_frame = 1;
		wake_up_interruptible(&k3fd->frame_wq);

		if (k3fd->index == 0) {
			if (k3fd->vsync_info.active && k3fd->vsync_info.thread) {
				k3fd->vsync_info.timestamp = ktime_get();
				wake_up_interruptible_all(&k3fd->vsync_info.wait);
			}

			if (k3fd->panel_info.sbl_enable && k3fd->sbl_wq)
				queue_work(k3fd->sbl_wq, &k3fd->sbl_work);

			if (k3fd->panel_info.frc_enable) {
				if (k3fb_frc_prepare(k3fd)) {
					k3fd->ldi_int_type |= FB_LDI_INT_TYPE_FRC;
				}
			}

			if (k3fd->panel_info.esd_enable) {
				if (k3fb_esd_prepare(k3fd)) {
					k3fd->ldi_int_type |= FB_LDI_INT_TYPE_ESD;
				}
			}

			if (k3fd->ldi_int_type != FB_LDI_INT_TYPE_NONE) {
				/* clear ldi interrupt */
				outp32(k3fd->edc_base + LDI_INT_CLR_OFFSET, 0xFFFFFFFF);

				/* enable vfrontporch_end_int */
				set_reg(k3fd->edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 10);
				/* disable ldi */
				set_reg(k3fd->edc_base + LDI_CTRL_OFFSET, 0x0, 1, 0);
			}
		}
	}
	return IRQ_HANDLED;
}

STATIC irqreturn_t edc_isr(int irq, void *data)
{
	struct k3_fb_data_type *k3fd = NULL;
	u32 tmp = 0;
	int ret = IRQ_HANDLED;

	k3fd = (struct k3_fb_data_type *)data;
	BUG_ON(k3fd == NULL);

    /* Modified for EDC1 offset, begin */
    if (k3fd_reg_base_edc0 == k3fd->edc_base) {
        tmp = inp32(k3fd->edc_base + EDC_INTS_OFFSET);
        outp32(k3fd->edc_base + EDC_INTS_OFFSET, 0x0);
    } else {
        tmp = inp32(k3fd->edc_base + LDI_ORG_INT_OFFSET + LDI1_OFFSET);
        if ((tmp & 0x4) == 0x4) {
            set_reg(k3fd->edc_base + LDI_INT_CLR_OFFSET + LDI1_OFFSET, 0x1, 1, 2);
            k3fb_logw("edc_afifo_underflow_int of EDC1!!!\n");
        }

        tmp = inp32(k3fd->edc_base + EDC_INTS_OFFSET + EDC1_OFFSET);
        outp32(k3fd->edc_base + EDC_INTS_OFFSET + EDC1_OFFSET, 0x0);
    }
    /* Modified for EDC1 offset, end */

	if (k3fd->panel_info.type != PANEL_MIPI_CMD)
		ret = edc_isr_video_mode(k3fd, tmp);

	return ret;
}

STATIC irqreturn_t ldi_isr(int irq, void *data)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_fb_panel_data *pdata = NULL;
	int ret = 0;
	int phylock_status = 0;
	u32 ints = 0;
	int temp = 0;
       bool is_timeout = true;
	int delay_count = 0;
	
	k3fd = (struct k3_fb_data_type *)data;
	BUG_ON(k3fd == NULL);
	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	BUG_ON(pdata == NULL);

	if (k3fd->index >= 1) {
		k3fb_loge("fb%d do not use ldi interrupt.\n", k3fd->index);
		return IRQ_HANDLED;
	}
     
	/* ldi interrupt state */
	ints = inp32(k3fd->edc_base + LDI_MSK_INT_OFFSET);
	temp = inp32(k3fd->edc_base + LDI_ORG_INT_OFFSET);
      
	/* clear ldi interrupt */
	outp32(k3fd->edc_base + LDI_INT_CLR_OFFSET, 0xFFFFFFFF);

      if (((ints & 0x1000) == 0x1000) && (k3fd->panel_info.type== PANEL_MIPI_CMD)) {	

		if(k3fd->index == 0){
    		   if(!k3fd->use_cmd_vsync && k3fd->vsync_info.active && k3fd->vsync_info.thread){
			 
    		        k3fd->vsync_info.timestamp = ktime_get();
    		        wake_up_interruptible_all(&k3fd->vsync_info.wait);
    		    }
		  
    		}
		
	      if(k3fd->index == 0 && k3fd->refresh && k3fd->fence_inc_thread){			
		  wake_up_interruptible(&k3fd->fence_inc_wait);		      				
	      }
		
		k3fd->update_frame = 1;
		wake_up_interruptible(&k3fd->frame_wq);
	}
	/* check vactive_end_int interrupt*/
	if (((ints & 0x80) == 0x80) && (k3fd->panel_info.type== PANEL_MIPI_CMD)) {	
			if (k3fd->cmd_mode_refresh){
	        		k3fd->cmd_mode_refresh = false;
				k3fd->cmd_bl_can_set = true;
	    		}
			if (k3fd->bl_level != k3fd->bl_level_cmd) {
	    			k3_fb_set_backlight_cmd_mode(k3fd, k3fd->bl_level);				
	    		}

			if (k3fd->panel_info.esd_enable && k3fd->esd_hrtimer_enable) {
					udelay(g_ldi_delay_debug);
					k3fd->checkesd_bl_cannot_set = true;			         
					ret = pdata->check_esd(k3fd->pdev);

			           
					/* power off PLL*/
					set_MIPIDSI_PHY_TST_CTRL1( 0x00010013 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
					set_MIPIDSI_PHY_TST_CTRL1( 0x00000040 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
                    		if ( k3fd->dsi_clk_last != k3fd->panel_info.mipi.dsi_bit_clk) {
						k3_fb_mipi_register_reset(k3fd);
						k3fd->dsi_clk_last = k3fd->panel_info.mipi.dsi_bit_clk;                             	
                    		}
					/* power on PLL*/
					set_MIPIDSI_PHY_TST_CTRL1( 0x00010013 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
					set_MIPIDSI_PHY_TST_CTRL1( 0x00000070 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
					set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
					while (1) {
						phylock_status = inp32(k3fd->dsi_base + MIPIDSI_PHY_STATUS_ADDR);
						if (((phylock_status & 0x1) == 0x1) || delay_count > 100) {
							is_timeout = (delay_count > 100) ? true : false;
							delay_count = 0;
							break;
					     } else {
							udelay(1);
							++delay_count;
					    }
					}	

					if (is_timeout) {
						k3fb_loge("phy lock is not ready!\n");
					}
					
					if (ret != 0x00) {
						k3fd->esd_recover = true;
					}
					
					k3fd->checkesd_bl_cannot_set = false;
					k3fd->esd_hrtimer_enable = false;
			} else {
					if ( k3fd->dsi_clk_last != k3fd->panel_info.mipi.dsi_bit_clk) {
			            		udelay(g_ldi_delay_debug);
			
				      
						set_MIPIDSI_PHY_TST_CTRL1( 0x00010013 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
						set_MIPIDSI_PHY_TST_CTRL1( 0x00000040 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
	                                 
						k3_fb_mipi_register_reset(k3fd);
						k3fd->dsi_clk_last = k3fd->panel_info.mipi.dsi_bit_clk;                             	
	   
						set_MIPIDSI_PHY_TST_CTRL1( 0x00010013 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
						set_MIPIDSI_PHY_TST_CTRL1( 0x00000070 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000002 );
						set_MIPIDSI_PHY_TST_CTRL0( 0x00000000 );
						
						while (1) {
							phylock_status = inp32(k3fd->dsi_base + MIPIDSI_PHY_STATUS_ADDR);
							if (((phylock_status & 0x1) == 0x1) || delay_count > 100) {
								is_timeout = (delay_count > 100) ? true : false;
								delay_count = 0;
								break;
					     		} else {
								udelay(1);
								++delay_count;
					    		}
						}	
						
					}				
			}
	}

	if (((ints & 0x1) == 0x1) && (k3fd->panel_info.type== PANEL_MIPI_CMD)) {

		set_LDI_CTRL_ldi_en(k3fd->edc_base, K3_DISABLE);
		if (!k3fd->cmd_mode_refresh){
    			k3fd->cmd_mode_refresh = true;

           		 /* Add for set frc, begin */
    			if(k3fd->index == 0){
				#if defined(CONFIG_OVERLAY_COMPOSE)
				k3_fb_gralloc_overlay_ch_process(k3fd);
				#endif
    			}
    			/* Add for set frc, end */
			if (k3fd->panel_info.sbl_enable && k3fd->sbl_wq)
				queue_work(k3fd->sbl_wq, &k3fd->sbl_work);		
    	    }				
	}
	
	/* check edc_afifo_underflow_int interrupt */
	if ((temp & 0x4) == 0x4) {
            k3fb_loge("edc_afifo_underflow_int of EDC0 ldi!!!\n");
        }
	
	if (((temp & 0x400) == 0x400) && (k3fd->panel_info.type != PANEL_MIPI_CMD)) {
		if (k3fd->panel_info.frc_enable && (k3fd->ldi_int_type & FB_LDI_INT_TYPE_FRC)) {
			ret = k3fb_frc_set(k3fd);
			if (ret < 0) {
				k3fb_loge("failed to set frc.\n");
			}


		} else if (k3fd->panel_info.esd_enable && (k3fd->ldi_int_type & FB_LDI_INT_TYPE_ESD)) {
			ret = k3fb_esd_set(k3fd);
			if (ret < 0) {
				k3fb_loge("failed to set esd.\n");
			}
		}

		/* disable vfrontporch_end_int */
    	set_reg(k3fd->edc_base + LDI_INT_EN_OFFSET, 0x0, 1, 10);
    	/* enable ldi */
    	set_reg(k3fd->edc_base + LDI_CTRL_OFFSET, 0x1, 1, 0);

		k3fd->ldi_int_type = FB_LDI_INT_TYPE_NONE;
	}

	return IRQ_HANDLED;
}
#if CONFIG_WFD_FBINFO
/* Wifi display begin modified by huangzhouxiang*/
int k3fb_wifi_disp_clear_fbstatus(void __user *p)
{
	int ret = 0;
	wfd_fb_info req;

	if (copy_from_user(&req, p, sizeof(req))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	wfd_fbi.fbstatus &= ~(1<<req.fbslot);

	return ret;
}

 int k3fb_wifi_disp_get_fbi(void __user *p)
{
	int ret = 0;
	wfd_fb_info req;
	if (copy_from_user(&req, p, sizeof(req))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	req = wfd_fbi;

	if (copy_to_user(p, &req, sizeof(req))) {
		k3fb_loge("copy2user failed!\n");
		return -EFAULT;
	}

	return ret;
}
/* Wifi display end */
#endif


/******************************************************************************/

STATIC int k3fb_overlay_get(struct fb_info *info, void __user *p)
{
	int ret = 0;
	struct overlay_info req;

	BUG_ON(info == NULL);

	if (copy_from_user(&req, p, sizeof(req))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	ret = edc_overlay_get(info, &req);
	if (ret) {
		k3fb_loge("edc_overlay_get ioctl failed!\n");
		return ret;
	}

	if (copy_to_user(p, &req, sizeof(req))) {
		k3fb_loge("copy2user failed!\n");
		return -EFAULT;
	}

	return ret;
}

STATIC int k3fb_overlay_set(struct fb_info *info, void __user *p)
{
	int ret = 0;
	struct overlay_info req;

	BUG_ON(info == NULL);

	if (copy_from_user(&req, p, sizeof(req))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}

	ret = edc_overlay_set(info, &req);
	if (ret) {
		k3fb_loge("k3fb_overlay_set ioctl failed, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

STATIC int k3fb_overlay_unset(struct fb_info *info, unsigned long *argp)
{
	int ret = 0;
	int ndx = 0;
    struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);

    k3fd = (struct k3_fb_data_type *)info->par;
    BUG_ON(k3fd == NULL);

	ret = copy_from_user(&ndx, argp, sizeof(ndx));
	if (ret) {
		k3fb_loge("copy from user failed!\n");
		return ret;
	}

#if K3_FB_OVERLAY_USE_BUF
	if ((k3fd->index == 1) && video_buf.is_init && video_buf.is_video) {
		video_buf.is_video = false;
		mutex_lock(&video_buf.overlay_mutex);
		reset_video_buf();
		mutex_unlock(&video_buf.overlay_mutex);
	}
#endif
	return edc_overlay_unset(info, ndx);
}
struct overlay_data nsd_overlay_data[MAX_EDC_CHANNEL];
struct fb_var_screeninfo nsd_var;
STATIC int k3fb_overlay_play(struct fb_info *info, unsigned long *argp)
{
	int ret = 0;
	int wait_ret = 0;
	struct overlay_data req;
	struct k3_fb_data_type *k3fd = NULL;
    int fenceId = 0;
    unsigned long flags;
    static int edc1videoplayed = 0;
#if K3_FB_OVERLAY_USE_BUF
	static int count = 0;
	overlay_video_data *video_data = NULL;
	u32 video_index = 0;
	int i = 0;
	int min_count = 0;
	int set_count = 0;
#endif

	BUG_ON(info == NULL);

	ret = copy_from_user(&req, argp, sizeof(req));
	if (ret) {
		k3fb_loge("copy from user failed!\n");
		return ret;
	}

	if (req.id < MAX_EDC_CHANNEL){
		memcpy(&nsd_overlay_data[req.id],&req,sizeof(req));
	}
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

		/* wifi display begin modified by huangzhouxiang*/
#if CONFIG_WFD_FBINFO
	wfd_fbi.physical = req.src.phy_addr;
	wfd_fbi.format = req.src.format;
	if (INVALID_BUFF_SLOT != req.src.buff_slot)
	{
		wfd_fbi.fbslot = req.src.buff_slot;
	 	wfd_fbi.fbstatus |= 1 << wfd_fbi.fbslot;
	}
	else
	{
		wfd_fbi.fbslot = 0;
		wfd_fbi.fbstatus = 0;
	}

	if ((EDC_XRGB_8888 == req.src.format) || (EDC_ARGB_8888 == req.src.format))
	{
		wfd_fbi.bpp = 4;
	}
	else
	{
          wfd_fbi.bpp = 2;
	}
#endif
	/* wifi display end */


if((k3fd->index == 1) && hdmi_is_connected){
    if (req.src.is_video == 1){
        
        fenceId = k3_fb_overlay_fence_create(k3fd->timeline, "edc1", ++k3fd->timeline_max);
        
        if(fenceId < 0)
        {
            k3fb_loge("edc1 failed to create fence!\n");
        }

         spin_lock_irqsave(&k3fd->refresh_lock,flags);
         k3fd->refresh ++;
         spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
        req.src.release_fence = fenceId;
        if((fenceId>=0)&&copy_to_user((struct overlay_data __user*)argp, &req, sizeof(struct overlay_data)))
        {
            fenceId = -EFAULT;
            k3fb_loge("edc1 failed to copy fence to user!\n");
            put_unused_fd(req.src.release_fence);
            return fenceId;
        }
        edc1videoplayed = 1;
    }
    if ((req.src.is_video == 0)&&edc1videoplayed){
        spin_lock_irqsave(&k3fd->refresh_lock,flags);
        sw_sync_timeline_inc(k3fd->timeline, 1 + k3fd->refresh);
        k3fd->refresh = 0;
        k3fd->timeline_max++;
        edc1videoplayed = 0;
        spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
       }
}

#if K3_FB_OVERLAY_USE_BUF
	if ((k3fd->index == 1) && hdmi_is_connected && (req.src.is_video == 1) && should_use_videobuf(info)) {

		mutex_lock(&video_buf.overlay_mutex);
		if (!video_buf.is_video) {
			k3fb_logi("begin play video.\n");
		}
		video_buf.is_video = true;
		count ++;

		if (video_buf.last_addr == req.src.phy_addr) {
			mutex_unlock(&video_buf.overlay_mutex);
			k3fb_logi("same buf phys:0x%x.\n", req.src.phy_addr);
			return 0;
		}

		for (i = 0; i < MAX_OVERLAY_BUF_NUM; i++) {
			video_data = &video_buf.video_data_list[i];
			if (video_data->is_set) {
				set_count++;
			}

			if (0 == i || video_data->count < min_count) {
				min_count = video_data->count;
				video_index = i;
			}
		}

		if (MAX_OVERLAY_BUF_NUM == set_count) {
			k3fb_logw("video buff full @@@@@.\n");
		}

		video_data = &video_buf.video_data_list[video_index];
		memcpy(&video_data->data, &req, sizeof(req));
		video_data->is_set = true;
		video_data->count = count;

		video_buf.last_addr = req.src.phy_addr;
		/*k3fb_logi("buf index:%d count:%d\n", video_index, count);*/
		mutex_unlock(&video_buf.overlay_mutex);
		return 0;
	} else if((k3fd->index == 1) && video_buf.is_video){
		k3fb_logi("exit play video req.is_video:%d buf.is_video:%d is_connected:%d\n",req.src.is_video, video_buf.is_video, hdmi_is_connected);
		video_buf.is_video = false;
		mutex_lock(&video_buf.overlay_mutex);
		count = 0;
		reset_video_buf();
		mutex_unlock(&video_buf.overlay_mutex);
	}
#endif

#if defined(CONFIG_OVERLAY_COMPOSE)
	if (edc_overlay_compose_get_state(info, req.id)) {
		return k3_fb_overlay_compose_play(info, req, argp);
	}
#endif //CONFIG_OVERLAY_COMPOSE

	if (k3fd->index == 1 && hdmi_is_connected && (!req.src.is_video || !should_use_videobuf(info))) {
		if (wait_event_interruptible_timeout(k3fd->frame_wq, k3fd->update_frame, HZ / 10) <= 0) {
			k3fb_logw("wait_event_interruptible_timeout !\n");
			k3fd->update_frame = 0;
			return -ETIME;
		}
		k3fd->update_frame = 0;
	}

    ret =  edc_overlay_play(info, &req);

    if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
        set_LDI_CTRL_ldi_en(k3fd->edc_base, K3_ENABLE);
        set_EDC_DSI_TE_CTRL(0x4001);

#if defined(CONFIG_OVERLAY_COMPOSE)
        wait_ret = k3_fb_overlay_compose_wait_event(k3fd);
        if (wait_ret < 0) {
            if (k3fd->panel_info.esd_enable) {
                ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, info,1);
                if (ret != 0) {
                    k3fb_loge("can't turn off display!\n");
                    return ret;
                }
                ret = k3_fb_blank_sub(FB_BLANK_UNBLANK, info,1);
                if (ret != 0) {
                    k3fb_loge("can't turn on display!\n");
                    return ret;
                }
                k3fb_loge("ESD recover!\n");
            }
            return wait_ret;
        }
#endif //CONFIG_OVERLAY_COMPOSE
    }

	return ret;
}

STATIC int k3fb_vsync_int_set(struct fb_info *info, unsigned long *argp)
{
	int ret = 0;
	int vsync = 0;
	bool cur_vsync_event = false;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	ret = copy_from_user(&vsync, argp, sizeof(vsync));
	if (ret) {
		k3fb_loge("copy from user failed!\n");
		return ret;
	}

	cur_vsync_event = (vsync == 1) ? true : false;

	if (k3fd->vsync_info.active != cur_vsync_event) {
		k3fd->vsync_info.active = cur_vsync_event;

		k3fb_logi_vsync_debugfs("[k3fb_vsync_int_set] k3fd->vsync_info.active = %d \n", k3fd->vsync_info.active);
        if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
    		if (!k3fd->vsync_info.active) {
    			k3fb_te_dec(k3fd, false, false);
    		} else {
    			k3fd->use_cmd_vsync = true;

    		#if defined(CONFIG_OVERLAY_COMPOSE)
    			// Clear idle count
			k3fd->ddrIdleCount = 0;
		    #endif
    			k3fb_te_inc(k3fd, false, false);
    		}
        }
		if (k3fd->vsync_info.active) {
			if (k3fd->frc_state == K3_FB_FRC_IDLE_PLAYING) {
				k3fd->frc_state = K3_FB_FRC_NONE_PLAYING;
				k3fd->frc_threshold_count = 0;
			}
		} else {
			if (k3fd->frc_state == K3_FB_FRC_NONE_PLAYING)
				k3fd->frc_state = K3_FB_FRC_IDLE_PLAYING;

		}
	}

	return ret;
}

STATIC int k3fb_set_timing(struct fb_info *info, unsigned long *argp)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_fb_panel_data *pdata = NULL;
	struct fb_var_screeninfo var;
	u32 edc_base = 0;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	edc_base = k3fd->edc_base;

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->set_timing)) {
		k3fb_loge("no panel operation detected!\n");
		return -ENODEV;
	}

	if (!k3fd->panel_power_on) {
		k3fb_loge("panel power off!\n");
		return -EPERM;
	}

	ret = copy_from_user(&var, argp, sizeof(var));
	if (ret) {
		k3fb_loge("copy from user failed!\n");
		return ret;
	}

	memcpy(&info->var, &var, sizeof(var));
	k3fd->panel_info.xres = var.xres;
	k3fd->panel_info.yres = var.yres;

	k3fd->panel_info.clk_rate = (var.pixclock == 0) ? k3fd->panel_info.clk_rate : var.pixclock;
	k3fd->panel_info.ldi.h_front_porch = var.right_margin;
	k3fd->panel_info.ldi.h_back_porch = var.left_margin;
	k3fd->panel_info.ldi.h_pulse_width = var.hsync_len;
	k3fd->panel_info.ldi.v_front_porch = var.lower_margin;
	k3fd->panel_info.ldi.v_back_porch = var.upper_margin;
	k3fd->panel_info.ldi.v_pulse_width = var.vsync_len;
#ifdef HDMI_DISPLAY
	k3fd->panel_info.ldi.vsync_plr = hdmi_get_vsync_bycode(var.reserved[3]);
	k3fd->panel_info.ldi.hsync_plr = hdmi_get_hsync_bycode(var.reserved[3]);
#endif

	/* Note: call clk_set_rate after clk_set_rate, set edc clock rate to normal value */
    if (k3fd->index == 0) {
        if (clk_set_rate(k3fd->edc_clk, EDC_CORE_CLK_RATE) != 0) {
            k3fb_loge("failed to set edc clk rate(%d).\n", EDC_CORE_CLK_RATE);
        }
    } else {
        if (clk_set_rate(k3fd->edc_clk, EDC_CORE_CLK_RATE/*(k3fd->panel_info.yres < 720) ? EDC_CORE_CLK_RATE : ( k3fd->panel_info.clk_rate * 12 / 10)*/) != 0) {
            k3fb_loge("failed to set edc clk rate(%d).\n", k3fd->panel_info.clk_rate * 12 / 10);
        }
    }

	set_EDC_DISP_SIZE(edc_base, k3fd->panel_info.xres, k3fd->panel_info.yres);

	if (pdata->set_timing(k3fd->pdev) != 0) {
		k3fb_loge("set timing failed!\n");
	}

	return 0;
}


/******************************************************************************/

static void k3_fb_set_backlight_cmd_mode(struct k3_fb_data_type *k3fd, u32 bkl_lvl)
{
	struct k3_fb_panel_data *pdata = NULL;
	int ret = 0;

	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return;
	}

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->set_backlight)) {
		k3fb_loge("no panel operation detected!\n");
		return;
	}

	k3fd->bl_level = bkl_lvl;
	ret = pdata->set_backlight(k3fd->pdev);
	if (ret == 0) {
		k3fd->bl_level_cmd = k3fd->bl_level;
	} else {
		k3fb_loge("failed to set backlight.\n");
	}
}

void k3_fb_set_backlight(struct k3_fb_data_type *k3fd, u32 bkl_lvl)
{
	struct k3_fb_panel_data *pdata = NULL;
	int ret = 0;

	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return;
	}

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->set_backlight)) {
		k3fb_loge("no panel operation detected!\n");
		return;
	}

	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
		if (k3fd->cmd_mode_refresh || k3fd->checkesd_bl_cannot_set) {
            k3fb_logi_backlight_debugfs(" set backlight fail  k3fd->cmd_mode_refresh = %d ! \n", k3fd->cmd_mode_refresh);
			return;
	    }
	}

	down(&k3_fb_backlight_sem);
	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
	#if CLK_SWITCH
		/* enable edc clk */
		clk_enable(k3fd->edc_clk);
		/* enable ldi clk */
		clk_enable(k3fd->ldi_clk);
	#endif
	}

	k3fd->bl_level = bkl_lvl;
	ret = pdata->set_backlight(k3fd->pdev);
	if (ret == 0) {
		k3fd->bl_level_cmd = k3fd->bl_level;
	} else {
		k3fb_loge("failed to set backlight.\n");
	}

	if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
	#if CLK_SWITCH
		/* disable ldi clk */
		clk_disable(k3fd->ldi_clk);
		/* disable edc clk */
		clk_disable(k3fd->edc_clk);
	#endif
	}
	up(&k3_fb_backlight_sem);
}

void k3_fb_power_on_vote(struct k3_fb_data_type *k3fd)
{
    if(NULL == k3fd)
    {
        k3fb_logw("k3fd NULL return!\n");
        return;
    }
	       
    if (k3fd->index == 0){
        pm_qos_add_request(&gedc_pm_qos_req, PM_QOS_CPU_INT_LATENCY, 0);
        pm_qos_add_request(&gdfs_pm_qos_req, PM_QOS_BUS_MIN_PROFILE, BUS_DFS_FREQ);
    }
}
void k3_fb_power_off_vote(struct k3_fb_data_type *k3fd)
{
    if(NULL == k3fd)
    {
        k3fb_logw("k3fd NULL return!\n");
        return;
    }
    if (k3fd->index == 0){
        pm_qos_remove_request(&gedc_pm_qos_req);
        pm_qos_remove_request(&gdfs_pm_qos_req);
	 pm_qos_remove_request(&g_cpunum_qos);
    }
}


int k3_fb_blank_sub(int blank_mode, struct fb_info *info,bool sem)
{
	/*
	**input: sem
	** 0: for enable esd without deadlocks
	** 1: for normal mode
	*/

	int ret = 0;
	unsigned long flags;
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_fb_panel_data *pdata = NULL;
       bool curr_pwr_state = false;


	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->on) || (!pdata->off)) {
		k3fb_loge("no panel operation detected!\n");
		return -ENODEV;
	}
	if(sem==1){
		down(&k3_fb_blank_sem);
	}

	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		if (!k3fd->panel_power_on) {
		    k3_fb_power_on_vote(k3fd);
			edc_fb_resume(info);
			ret = pdata->on(k3fd->pdev);
			if (ret != 0) {
				k3fb_loge("failed to turn on sub devices!\n");
			} else {
				if (k3fd->panel_info.sbl_enable)
					sbl_ctrl_resume(k3fd);

				k3fd->panel_power_on = true;
				if (k3fd->panel_info.type != PANEL_MIPI_CMD)
					k3_fb_set_backlight(k3fd, k3fd->bl_level);

				if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
					if (k3fd->panel_info.esd_enable) {
						k3fd->esd_hrtimer_enable = false;
						hrtimer_restart(&k3fd->esd_hrtimer);
					}
				}

				if (k3fd->index == 0) {
				#if defined(CONFIG_OVERLAY_COMPOSE)
				k3fd->ddrIdleCount = 0;
		        k3fd->dsi_clk_last = k3fd->panel_info.mipi.dsi_bit_clk;  
                #endif
            if (k3fd->panel_info.type == PANEL_MIPI_CMD)
					hrtimer_restart(&k3fd->cmd_vsync_hrtimer);
				}

				/* enable edc irq */
				if (k3fd->edc_irq)
					enable_irq(k3fd->edc_irq);
				/* enable ldi irq */
				if (k3fd->ldi_irq)
					enable_irq(k3fd->ldi_irq);
			}
		}
		break;

	case FB_BLANK_VSYNC_SUSPEND:
	case FB_BLANK_HSYNC_SUSPEND:
	case FB_BLANK_NORMAL:
	case FB_BLANK_POWERDOWN:
	default:
		if (k3fd->panel_power_on) {
		    k3fb_logi("enter succ k3fd->panel_power_on = %d", k3fd->panel_power_on);
    #ifdef CONFIG_DEBUG_FS
            if (k3fd->index == 0) {
                if (DEBUG_ALL_LOWPOWER_DISABLE == (g_fb_lowpower_debug_flag & DEBUG_ALL_LOWPOWER_DISABLE)) {
                    k3fb_logi("all power down was disable");
                    break;
                }
            }
    #endif

			curr_pwr_state = k3fd->panel_power_on;
			k3fd->panel_power_on = false;

			/* disable edc irq */
			if (k3fd->edc_irq)
				disable_irq(k3fd->edc_irq);
			/* disable ldi irq*/
			if (k3fd->ldi_irq)
				disable_irq(k3fd->ldi_irq);

			if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
				k3fd->cmd_mode_refresh = false;
				k3fd->cmd_bl_can_set = false;
				k3fd->checkesd_bl_cannot_set = false;
				k3fd->bl_level_cmd = 0;

                k3fd->dsi_clk_last = 0;
                /* Add for set frc, begin */
                k3fd->use_cmd_vsync = false;
				hrtimer_cancel(&k3fd->cmd_vsync_hrtimer);
				k3fd->ambient_temperature = 0;
				/* Add for set frc, end */
				if (k3fd->panel_info.esd_enable) {
					k3fd->esd_hrtimer_enable = false;
					hrtimer_cancel(&k3fd->esd_hrtimer);
				}
			}

            /* Add for set frc, begin */
            /* Set frame rate back to 60 */
			if(k3fd->panel_info.frc_enable){
               k3fd->frc_state = K3_FB_FRC_NONE_PLAYING;
               k3fb_frc_set(k3fd);
			}

			/* Add for set frc, end*/
			ret = pdata->off(k3fd->pdev);
			if (ret != 0) {
				k3fb_loge("failed to turn off sub devices!\n");
				k3fd->panel_power_on = curr_pwr_state;
			} else {
				edc_fb_suspend(info);
				k3_fb_power_off_vote(k3fd);
			}
			
			spin_lock_irqsave(&k3fd->refresh_lock,flags);
			sw_sync_timeline_inc(k3fd->timeline, 1 + k3fd->refresh);
			k3fd->refresh = 0;
	    	  	spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
			k3fd->timeline_max++;

		}
		break;
	}
	if(sem==1){
		up(&k3_fb_blank_sem);
	}
	return ret;
}

u32 k3_fb_line_length(u32 xres, int bpp)
{
#ifdef CONFIG_FB_64BYTES_ODD_ALIGN
	u32 stride = ALIGN_UP(xres * bpp, 64);
	return (((stride / 64) % 2 == 0) ? (stride + 64) : stride);
#else
	return xres * bpp;
#endif
}

int k3_fb_init_varinfo(struct k3_fb_data_type *k3fd, int pixel_fmt)
{
	struct fb_info *fbi = NULL;
	struct fb_var_screeninfo *var = NULL;
	int bpp = 0;

	BUG_ON(k3fd == NULL);

	pr_info("%s enter succ!\n",__func__);

	fbi = k3fd->fbi;
	var = &fbi->var;

	var->xoffset = 0;  /* Offset from virtual to visible */
	var->yoffset = 0;  /* resolution */
	var->grayscale = 0;  /* No graylevels */
	var->nonstd = 0;  /* standard pixel format */
	/*var->activate = FB_ACTIVATE_NOW;*/
	var->activate = FB_ACTIVATE_VBL;  /* activate it at vsync */
	var->height = -1;  /* height of picture in mm */
	var->width = -1;  /* width of picture in mm */
	var->accel_flags = 0;  /* acceleration flags */
	var->sync = 0;	 /* see FB_SYNC_* */
	var->rotate = 0;   /* angle we rotate counter clockwise */
	var->vmode = FB_VMODE_NONINTERLACED;

	switch (pixel_fmt) {
	case IMG_PIXEL_FORMAT_RGBX_5551:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 15;
		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_ARGB_1555;
		break;
	case IMG_PIXEL_FORMAT_RGBA_5551:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 15;
		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 1;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_ARGB_1555;
		break;
	case IMG_PIXEL_FORMAT_RGB_565:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 11;
		var->transp.offset = 0;
		var->blue.length = 5;
		var->green.length = 6;
		var->red.length = 5;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_RGB_565;
		break;
	case IMG_PIXEL_FORMAT_RGBX_8888:
		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;
		var->blue.length = 8;
		var->green.length = 8;
		var->red.length = 8;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 4;
		k3fd->fb_imgType = EDC_XRGB_8888;
		break;
	case IMG_PIXEL_FORMAT_RGBA_8888:
		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;
		var->blue.length = 8;
		var->green.length = 8;
		var->red.length = 8;
		var->transp.length = 8;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 4;
		k3fd->fb_imgType = EDC_ARGB_8888;
		break;
	default:
		pr_err("k3fb, %s: fb %d unkown image type!\n", __func__, k3fd->index);
		return -EINVAL;
	}

	var->xres = k3fd->panel_info.xres;
	var->yres = k3fd->panel_info.yres;
	var->xres_virtual = k3fd->panel_info.xres;
	var->yres_virtual = k3fd->panel_info.yres * K3_NUM_FRAMEBUFFERS;
	var->bits_per_pixel = bpp * 8;

    pr_info("%s,fbi->screen_base:0x%0x \n",__func__,(u32)fbi->screen_base);
    pr_info("%s,fbi->screen_size:0x%0x \n",__func__,(u32)fbi->screen_size);
    pr_info("%s,fbi->fix.smem_start:0x%0x \n",__func__,(u32)fbi->fix.smem_start);
    pr_info("%s,fbi->fix.smem_len:%d \n",__func__,fbi->fix.smem_len);
    pr_info("%s,fbi->fix.line_length:%d \n",__func__,fbi->fix.line_length);

    pr_info("%s,fbi->var.xres_virtual:%d \n",__func__,fbi->var.xres_virtual);
    pr_info("%s,fbi->var.yres_virtual:%d \n",__func__,fbi->var.yres_virtual);
    pr_info("%s,fbi->var.xres:%d \n",__func__,fbi->var.xres);
    pr_info("%s,fbi->var.yres:%d \n",__func__,fbi->var.yres);

    pr_info("%s,fbi->var.bits_per_pixel:%d \n",__func__,fbi->var.bits_per_pixel);

	pr_info("%s exit succ!\n",__func__);

	return 0;
}


/******************************************************************************/

int k3_fb_open(struct fb_info *info, int user)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	struct fb_var_screeninfo *var = NULL;
	var = &info->var;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

#ifdef CONFIG_FASTBOOT_DISP_ENABLE
	if (k3fd->index == 0) {
		if (k3fd->ref_cnt == 1) {
			hisi_memset(info->screen_base, 0x0, info->fix.smem_len);
		}
	}
#endif

	if (!k3fd->ref_cnt) {
		k3fb_logi("index=%d, enter!\n", k3fd->index);
		ret = k3_fb_blank_sub(FB_BLANK_UNBLANK, info,1);
		if (ret != 0) {
			k3fb_loge("can't turn on display!\n");
			return ret;
		}
		k3fb_logi("index=%d, exit!\n", k3fd->index);
	}

	if ( g_debug_camerause == 1 ){

        var->xres = CAMERA_XRES;
        var->yres = CAMERA_YRES;
        var->xres_virtual = ALIGN_UP(var->xres, 16);
        var->yres_virtual = var->yres * K3_NUM_FRAMEBUFFERS;

    }
	k3fd->ref_cnt++;

	return ret;
}

STATIC int k3_fb_release(struct fb_info *info, int user)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (!k3fd->ref_cnt) {
		k3fb_loge("try to close unopened fb %d!\n", k3fd->index);
		return -EINVAL;
	}

	k3fd->ref_cnt--;

	if (!k3fd->ref_cnt) {
		ret = k3_fb_init_varinfo(k3fd, IMG_PIXEL_FORMAT_RGBA_8888);
		if (ret != 0) {
			k3fb_logi("index=%d, enter!\n", k3fd->index);
			return ret;
		}
		ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, info,1);
		if (ret != 0) {
			k3fb_loge("can't turn off display!\n");
			return ret;
		}
		k3fb_logi("index=%d, exit!\n", k3fd->index);
	}

#if defined(CONFIG_OVERLAY_COMPOSE)
	if (k3fd->index == 0) {
		if (k3fd->ref_cnt == 1) {
			k3_fb_overlay_compose_reset_pipe(info);
		}
	}
#endif


	return ret;
}

STATIC int k3_fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	/*u32 max_xres = 0;
	u32 max_yres = 0;*/

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (var->rotate != FB_ROTATE_UR) {
		k3fb_loge("rotate %d!\n", var->rotate);
		return -EINVAL;
	}

	if (var->grayscale != info->var.grayscale) {
		k3fb_loge("grayscale %d!\n", var->grayscale);
		return -EINVAL;
	}

	switch (var->bits_per_pixel) {
	/* RGB565 RGBA5551 RGBX5551*/
	case 16:
		{
			if (var->blue.offset == 0) {
				if (var->red.offset == 10) {
					if ((var->transp.offset != 15) ||
						(var->green.length != 5) ||
						((var->transp.length != 1) && (var->transp.length != 0))) {
						k3fb_loge("not match  RGBA5551 and RGBX5551!\n");
						return -EINVAL;
					}
				} else if (var->red.offset == 11) {
					if ((var->transp.offset != 0) ||
						(var->green.length != 6) ||
						(var->transp.length != 0)) {
						k3fb_loge("not match  RGB565!\n");
						return -EINVAL;
					}
				} else {
					k3fb_loge("not match  RGB565, RGBA5551 or RGBX5551!\n");
					return -EINVAL;
				}
			} else if (var->blue.offset == 10) {
				if ((var->red.offset != 0) ||
					(var->transp.offset != 15) ||
					(var->green.length != 5) ||
					((var->transp.length != 1) && (var->transp.length != 0))) {
					k3fb_loge("1 not match  BGRA5551 and BGRX5551!\n");
					return -EINVAL;
				}
			} else if (var->blue.offset == 11) {
				if ((var->red.offset != 0) ||
					(var->transp.offset != 0) ||
					(var->green.length != 6) ||
					(var->transp.length != 0)) {
					k3fb_loge("not match  BGR565!\n");
					return -EINVAL;
				}
			} else {
				k3fb_loge("2 not match  RGB565, RGBA5551 or RGBX5551!\n");
				return -EINVAL;
			}

			/* Check the common values for RGB565, RGBA5551 and RGBX5551 */
			if ((var->green.offset != 5) ||
				(var->blue.length != 5) ||
				(var->red.length != 5) ||
				(var->blue.msb_right != 0) ||
				(var->green.msb_right != 0) ||
				(var->red.msb_right != 0) ||
				(var->transp.msb_right != 0)) {
				k3fb_loge("3 not match  RGB565, RGBA5551 or RGBX5551!\n");
				return -EINVAL;
			}
		}
		break;
	/* RGBA8888 RGBX8888*/
	case 32:
		{
			if (var->blue.offset == 0) {
				if (var->red.offset != 16) {
					k3fb_loge("not match EDC_RGB, bpp=32!\n");
					return -EINVAL;
				}
			} else if (var->blue.offset == 16) {
				if (var->red.offset != 0) {
					k3fb_loge("not match EDC_BGR, bpp=32!\n");
					return -EINVAL;
				}
			} else {
				k3fb_loge("1 not match RGBA8888 or RGBX8888!\n");
				return -EINVAL;
			}

			/* Check the common values for RGBA8888 and RGBX8888 */
			if ((var->green.offset != 8) ||
				(var->transp.offset != 24) ||
				(var->blue.length != 8) ||
				(var->green.length != 8) ||
				(var->red.length != 8) ||
				((var->transp.length != 8) && (var->transp.length != 0)) ||
				(var->blue.msb_right != 0) ||
				(var->green.msb_right != 0) ||
				(var->red.msb_right != 0) ||
				(var->transp.msb_right != 0)) {
				k3fb_loge("2 not match RGBA8888 or RGBX8888!\n");
				return -EINVAL;
			}
		}
		break;
	default:
		{
			k3fb_loge("bits_per_pixel=%d not supported!\n", var->bits_per_pixel);
			return -EINVAL;
		}
		break;
	}

	if ((var->xres_virtual < K3_FB_MIN_WIDTH) || (var->yres_virtual < K3_FB_MIN_HEIGHT)) {
		k3fb_loge("xres_virtual=%d yres_virtual=%d out of range!", var->xres_virtual, var->yres_virtual);
		return -EINVAL;
	}

	/*max_xres = MIN(var->xres_virtual, K3_FB_MAX_WIDTH);
	max_yres = MIN(var->yres_virtual, K3_FB_MAX_HEIGHT);
	if ((var->xres < K3_FB_MIN_WIDTH) ||
		(var->yres < K3_FB_MIN_HEIGHT) ||
		(var->xres > max_xres) ||
		(var->yres > max_yres)) {
		k3fb_loge("xres=%d yres=%d out of range!\n", var->xres, var->yres);
		return -EINVAL;
	}*/

	if (var->xoffset > (var->xres_virtual - var->xres)) {
		k3fb_loge("xoffset=%d out of range!\n", var->xoffset);
		return -EINVAL;
	}

	if (var->yoffset > (var->yres_virtual - var->yres)) {
		k3fb_loge("yoffset=%d out of range!\n", var->yoffset);
		return -EINVAL;
	}

	if (info->fix.smem_len < (k3_fb_line_length(var->xres_virtual, (var->bits_per_pixel >> 3))  * var->yres_virtual)) {
		k3fb_loge("smem_len=%d out of range!\n", info->fix.smem_len);
		return -EINVAL;
	}

	return ret;
}

STATIC int k3_fb_set_par(struct fb_info *info)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct fb_var_screeninfo *var = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	var = &info->var;
	switch (var->bits_per_pixel) {
	case 16:
		{
			if (var->blue.offset == 0) {
				k3fd->fb_bgrFmt = EDC_RGB;
				if (var->red.offset == 11)
					k3fd->fb_imgType = EDC_RGB_565;
				else
					k3fd->fb_imgType = EDC_ARGB_1555;
			} else {
				k3fd->fb_bgrFmt = EDC_BGR;
				if (var->blue.offset == 11)
					k3fd->fb_imgType = EDC_RGB_565;
				else
					k3fd->fb_imgType = EDC_ARGB_1555;
			}
		}
		break;
	case 32:
		{
			if (var->blue.offset == 0) {
				k3fd->fb_bgrFmt = EDC_RGB;
			} else {
				k3fd->fb_bgrFmt = EDC_BGR;
			}

			if (var->transp.length == 8)
				k3fd->fb_imgType = EDC_ARGB_8888;
			else
				k3fd->fb_imgType = EDC_XRGB_8888;
		}
		break;
	default:
		k3fb_loge("bits_per_pixel=%d not supported!\n", var->bits_per_pixel);
		return -EINVAL;
	}

    /*line_length will not change width when fb_imgType changing. For FB format Change dynamicly*/
	//k3fd->fbi->fix.line_length = k3_fb_line_length(var->xres_virtual, var->bits_per_pixel >> 3);

	if (info->fix.xpanstep)
		info->var.xoffset = (var->xoffset / info->fix.xpanstep) * info->fix.xpanstep;

	if (info->fix.ypanstep)
		info->var.yoffset = (var->yoffset / info->fix.ypanstep) * info->fix.ypanstep;

	return 0;
}

STATIC int k3_fb_pan_display_cmd_mode(struct fb_var_screeninfo *var,
	struct fb_info *info)
{
	int ret = 0;
	unsigned long flags;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

#if CLK_SWITCH
	/* enable edc clk */
	clk_enable(k3fd->edc_clk);
	/* enable ldi clk */
	clk_enable(k3fd->ldi_clk);
#endif
	
	ret = edc_fb_pan_display(var, info, k3fd->graphic_ch);
	if (ret != 0) {
		k3fb_loge("edc_fb_pan_display err!\n");
	}
	down(&k3_fb_blank_sem);
	if (!k3fd->panel_power_on) {
		up(&k3_fb_blank_sem);
		return -ETIME;
	}
#if defined(CONFIG_OVERLAY_COMPOSE)
	/* Clear idle count */
       k3fd->ddrIdleCount = 0;
#endif
	k3fb_te_inc(k3fd, true, false);
      set_LDI_CTRL_ldi_en(k3fd->edc_base, K3_ENABLE);
    /* enable fake vsync timer */
    if (k3fd->frc_state != K3_FB_FRC_IDLE_PLAYING) {
        k3fd->use_cmd_vsync = (k3fb_frc_get_fps(k3fd) < K3_FB_FRC_NORMAL_FPS ? true : false);
    }

    k3fb_logi_vsync_debugfs("k3fd->frc_state = %d \n", k3fd->frc_state);

#if K3_FB_OVERLAY_USE_BUF
	if (!hdmi_is_connected || video_buf.is_video) {
#else
	if (!hdmi_is_connected) {
#endif
		ret = wait_event_interruptible_timeout(k3fd->frame_wq, k3fd->update_frame, HZ / 10);
		if (ret <= 0 || (k3fd->esd_recover == true)) {
			if (k3fd->esd_recover == true) {
                    	k3fb_loge("ESD recover!\n");
			}	
			k3fd->esd_recover = false;
			if (k3fd->panel_info.esd_enable) {
				ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, info,0);
                            if (ret != 0) {
                                k3fb_loge("can't turn off display!\n");
                                up(&k3_fb_blank_sem);
                                return ret;
                            }
				ret = k3_fb_blank_sub(FB_BLANK_UNBLANK, info,0);
                            if (ret != 0) {
                                k3fb_loge("can't turn on display!\n");
                                up(&k3_fb_blank_sem);
                                return ret;
                            }
				
			}
			k3fb_logw("wait_event_interruptible_timeout ! \n");
			k3fd->update_frame = 0;
			k3fb_te_dec(k3fd, false, false);
			up(&k3_fb_blank_sem);
			return -ETIME;
		}
		k3fd->update_frame = 0;
	}
	if(k3fd->index == 0){
		spin_lock_irqsave(&k3fd->refresh_lock,flags);
		k3fd->refresh ++;
		spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
		k3fd->timeline_max++;
	}

    k3fb_te_dec(k3fd, false, false);

	up(&k3_fb_blank_sem);
	return ret;
}

STATIC int k3_fb_pan_display_video_mode(struct fb_var_screeninfo *var,
	struct fb_info *info)
{
	int ret = 0;
	unsigned long flags;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

#if K3_FB_OVERLAY_USE_BUF
	if (!hdmi_is_connected || video_buf.is_video) {
#else
	if (!hdmi_is_connected) {
#endif
		ret = wait_event_interruptible_timeout(k3fd->frame_wq, k3fd->update_frame, HZ / 10);
		if (ret <= 0) {
			k3fb_logw("wait_event_interruptible_timeout !edcfence_refresh=%d\n",k3fd->refresh);
			k3fd->update_frame = 0;
			return -ETIME;
		}
		k3fd->update_frame = 0;
	}
	
	ret = edc_fb_pan_display(var, info, k3fd->graphic_ch);
	if (ret != 0) {
		k3fb_logw("edc_fb_pan_display err!\n");
	}
	if(k3fd->index == 0){
		spin_lock_irqsave(&k3fd->refresh_lock,flags);
		k3fd->refresh ++;
		spin_unlock_irqrestore(&k3fd->refresh_lock,flags);
		k3fd->timeline_max++;
	}
	return ret;
}

int k3_fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	if (!k3fd->panel_power_on) {
		return -EPERM;
	}

/* partial compose never use to pan_display */
#if 0
#if defined(CONFIG_OVERLAY_COMPOSE)
	struct st_k3_fb_partial_ovc_ch ovc_partial_info;
#endif

#if defined(CONFIG_OVERLAY_COMPOSE)
	k3_fb_overlay_compose_partial_state(info, &ovc_partial_info);
	if (ovc_partial_info.ovc_ch_count != 0) {
		k3fb_logi(" ovc_partial_info.ovc_ch_count = %d \n", ovc_partial_info.ovc_ch_count);
#ifdef CONFIG_FOLLOWABILITY
        if (G_FOLLOW_FLAG_START == g_follow_flag)
        {
            long currTime = k3fb_getCurrTime();

            pr_info("k3fb, TAG_Followability, %s: edc partial compose play current time is %ld ms!\n", __func__,currTime);
            k3fb_listInsert(currTime);
        }
#endif

		return k3_fb_overlay_compose_partial_play(var, info, &ovc_partial_info);
	}

#endif /* CONFIG_OVERLAY_COMPOSE */
#endif

#ifdef CONFIG_FOLLOWABILITY
    if (G_FOLLOW_FLAG_START == g_follow_flag)
    {
        long currTime1 = k3fb_getCurrTime();

        pr_info("k3fb, TAG_Followability, %s:gpu compose play current time is %ld ms!\n", __func__,currTime1);
        k3fb_listInsert(currTime1);
    }
#endif
	nsd_var = *var;
	if (k3fd->panel_info.type == PANEL_MIPI_CMD)
		ret = k3_fb_pan_display_cmd_mode(var, info);
	else
		ret = k3_fb_pan_display_video_mode(var, info);

	if (k3fd->temp_wq)
		queue_work(k3fd->temp_wq, &k3fd->temp_work);

	return ret;
}
struct Nsd_info{
	int global_x,global_y;
	int w,h,config;
	int layer_phys_addr;
	int layer_x,layer_y;
	int layer_stride;
};

static void k3_fb_nsd_swapRB(char *p, int len)
{
	int i;
	char tmp;
	for (i=0; i<len;i=i+4){
		tmp = p[i+2];
		p[i+2] = p[i];
		p[i]=tmp;
	}
}

static void k3_fb_nsd_memcpy_debug(char *dst, char *src, int len)
{
	k3fb_logw("dst=0x%p src=0x%p len=%d\n",dst,src,len);
	memcpy(dst,src,len);
}
static void k3_fb_nsd_memcpy_rgb(char *dst, char *src, int len)
{
	memcpy(dst,src,len);
}
static void k3_fb_nsd_memcpy_bgr(char *dst, char *src, int len)
{
	memcpy(dst,src,len);
}

static int k3_fb_nsd_compose_g3d(struct fb_info *info,struct Nsd_info *nsd)
{
	char *target_kaddr;
	int bpp=4;
	int i;
	struct k3_fb_data_type *k3fd = (struct k3_fb_data_type *)info->par;
	if (NULL == k3fd){
		k3fb_loge("NULL k3fd pointer\n");
		return -EFAULT;
	}

	if ((EDC_ARGB_8888 != k3fd->fb_imgType) && (EDC_XRGB_8888 != k3fd->fb_imgType)){
		k3fb_loge("invalid pixel format - fb_imgType=%d\n", k3fd->fb_imgType);
		return -EFAULT;
	}

	if (nsd_var.xres != info->var.xres){
		k3fb_loge("nsd_var invalid\n");
		return -EFAULT;
	}

	target_kaddr=info->screen_base + nsd_var.yoffset * info->fix.line_length;
	if (((nsd->global_y+nsd->h-1)*(info->fix.line_length)+(nsd->global_x+nsd->w)*bpp) > (info->var.yres * info->fix.line_length))
	{
		k3fb_loge("invalid memcpy param\n");
		return -EFAULT;
	}
	k3fb_logw("target_kaddr=0x%p [start,end]=[0x%08X, 0x%08X]\n",target_kaddr,
		target_kaddr+(nsd->global_y)*(info->fix.line_length)+nsd->global_x*bpp,
		target_kaddr+(nsd->global_y+nsd->h-1)*(info->fix.line_length)+nsd->global_x*bpp);

	k3_fb_nsd_memcpy_debug(target_kaddr+(nsd->global_y)*(info->fix.line_length)+nsd->global_x*bpp,
			info->screen_base+(nsd->global_y)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));

	if (EDC_RGB == k3fd->fb_bgrFmt){
		for (i=0; i<nsd->h; i++){
			k3_fb_nsd_swapRB((char *)(info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp),nsd->w*bpp);
			k3_fb_nsd_memcpy_rgb(target_kaddr+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,
				info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));
		}
	} else if (EDC_BGR == k3fd->fb_bgrFmt){
		for (i=0; i<nsd->h; i++){
		k3_fb_nsd_memcpy_bgr(target_kaddr+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,
				info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));
		}
	}else{
		k3fb_loge("invalid RGB format: fb_bgrFmt=%d \n",k3fd->fb_bgrFmt);
		return -EFAULT;
	}

	return 0;
}
static int k3_fb_nsd_compose_edc(struct fb_info *info,struct Nsd_info *nsd, struct overlay_data *odata)
{
	char *target_kaddr;
	int bpp=4;
	int i;
	struct k3_fb_data_type *k3fd = (struct k3_fb_data_type *)info->par;
	if (NULL == k3fd){
		k3fb_loge("NULL k3fd pointer\n");
		return -EFAULT;
	}

	if ((EDC_ARGB_8888 !=odata->src.format) && (EDC_XRGB_8888 != odata->src.format)){
		k3fb_loge("invalid pixel format - src.format=%d\n", odata->src.format);
		return -EFAULT;
	}

	// copy framebuffer to target buffer
	target_kaddr = (char *)ioremap(odata->src.phy_addr, odata->src.stride * odata->src.height);
	if (NULL == target_kaddr){
		k3fb_loge("ioremap error. phy_addr=0x%08X len=0x%08X\n",odata->src.phy_addr,odata->src.stride * odata->src.height);
		return -EFAULT;
	}

	if (((nsd->global_y+nsd->h-1)*(odata->src.stride)+(nsd->global_x+nsd->w)*bpp) > (odata->src.stride * odata->src.height))
	{
		iounmap(target_kaddr);
		k3fb_loge("invalid memcpy param\n");
		return -EFAULT;
	}
	k3fb_logw("target_kaddr=0x%p phy_addr=0x%08X len=0x%08X [phy start,end]=[0x%08X, 0x%08X]\n",target_kaddr,odata->src.phy_addr,odata->src.stride * odata->src.height,
		odata->src.phy_addr+(nsd->global_y)*(odata->src.stride)+nsd->global_x*bpp,
		odata->src.phy_addr+(nsd->global_y+nsd->h-1)*(odata->src.stride)+nsd->global_x*bpp);

	k3_fb_nsd_memcpy_debug(target_kaddr+(nsd->global_y)*(odata->src.stride)+nsd->global_x*bpp,
				info->screen_base+(nsd->global_y)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));

    if (EDC_RGB == odata->src.bgr_fmt){
		for (i=0; i<nsd->h; i++){
			k3_fb_nsd_swapRB((char *)(info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp),nsd->w*bpp);
			k3_fb_nsd_memcpy_rgb(target_kaddr+(nsd->global_y+i)*(odata->src.stride)+nsd->global_x*bpp,
				info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));
		}
	} else if (EDC_BGR == odata->src.bgr_fmt){
		for (i=0; i<nsd->h; i++){
			k3_fb_nsd_memcpy_bgr(target_kaddr+(nsd->global_y+i)*(odata->src.stride)+nsd->global_x*bpp,
				info->screen_base+(nsd->global_y+i)*(info->fix.line_length)+nsd->global_x*bpp,(nsd->w*bpp));
		}
	}else{
		iounmap(target_kaddr);
		k3fb_loge("invalid RGB format: bgr_fmt=%d \n",odata->src.bgr_fmt);
		return -EFAULT;
	}
	iounmap(target_kaddr);

	return 0;
}

STATIC int k3_fb_nsd(struct fb_info *info, void __user *p)
{
	int i;
	struct Nsd_info nsd;
	struct overlay_info req;
	struct overlay_data *odata;
	int use_framebuffer=1;
	struct k3_fb_data_type *k3fd;

	k3fb_logw("enter\n");

	// check parameter: info
	if (NULL == info){
		k3fb_loge("NULL info pointer\n");
		return -EFAULT;
	} else if (info->fix.line_length < (info->var.xres * (info->var.bits_per_pixel>>3))){
		k3fb_loge("invalid fb info: line_length=%d xres=%d bpp=%d\n", info->fix.line_length, info->var.xres, info->var.bits_per_pixel>>3);
		return -EFAULT;
	}

	k3fd = (struct k3_fb_data_type *)info->par;
	if (NULL == k3fd){
		k3fb_loge("NULL k3fd pointer\n");
		return -EFAULT;
	}

	// get nsd info and check
	if (copy_from_user(&nsd, p, sizeof(nsd))) {
		k3fb_loge("copy from user failed!\n");
		return -EFAULT;
	}
	k3fb_logw("x=%d y=%d w=%d h=%d\n",nsd.global_x,nsd.global_y,nsd.w,nsd.h);

	if( (nsd.global_x<0) || (nsd.global_y<0) || (nsd.w < 1) || (nsd.h < 1) ||
		((nsd.global_x+nsd.w) > info->var.xres) || ((nsd.global_y+nsd.h) > info->var.yres) ){
		k3fb_loge("invalid ioctl param.\n");
		return -EFAULT;
	}

	// get current overlay channel
	for (i=0;i<MAX_EDC_CHANNEL;i++){
		if (edc_overlay_compose_get_state(info,i) == 0)
			continue;
		use_framebuffer = 0;
		req.id=i;
		edc_overlay_get(info,&req);
		// if nsd bitmap in dst_rect ?
		if ( (nsd.global_x>=req.dst_rect.x) && (nsd.global_y >= req.dst_rect.y) &&
			((nsd.global_x+nsd.w)<= (req.dst_rect.x+req.dst_rect.w)) &&
			((nsd.global_y+nsd.h)<= (req.dst_rect.y+req.dst_rect.h)) ){
			break;
		}
	}

	// G3D compose, use framebuffer
	if (i >= MAX_EDC_CHANNEL) {
		if (0 == use_framebuffer){
			k3fb_loge("unkown display mode\n");
			return -EFAULT;
		}

		k3fb_logw("use frame buffer\n");
		if (k3_fb_nsd_compose_g3d(info,&nsd))
			return -EFAULT;

		return k3_fb_pan_display(&nsd_var, info);
	}

	// G2D or EDC compose
	k3fb_logw("use edc compose\n");
	odata = &nsd_overlay_data[i];

	if (k3_fb_nsd_compose_edc(info,&nsd,odata) )
		return -EFAULT;

	// refresh
	if (k3fd->vsync_info.active){
		k3fb_loge("userspace is requesting vsync uevents\n");
		return 0;
	}

	req.cfg_disable=0;
	edc_overlay_set(info,&req);
	return k3_fb_overlay_compose_play(info,*odata,p);
}

//Multi Resolution====begin
/*added for resolution switch*/
STATIC int k3_fb_switch_resolution_process(struct k3_fb_data_type * k3fd)
{
	struct k3_panel_info * pInfo = NULL;
	struct fb_info *fbi = NULL;
	struct fb_var_screeninfo *var = NULL;
	struct fb_fix_screeninfo *fix = NULL;
	struct k3_fb_panel_data *pdata = NULL;

	fbi = k3fd->fbi;
	fix = &fbi->fix;
	var = &fbi->var;

	if (NULL == k3fd) {
		k3fb_loge("k3_fb_switch_resolution_process:NULL pointer!\n");
		return -1;
	}
	pInfo = &k3fd->panel_info;

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if ((!pdata) || (!pdata->set_disp_resolution)) {
		k3fb_loge("no panel operation detected!\n");
		return 0;
	}
	if (pdata->set_disp_resolution(k3fd->pdev) != 0) {
		k3fb_loge("set_disp_resolution error!\n");
		return 0;
	}

	fbi->var.pixclock = k3fd->panel_info.clk_rate;
	fbi->var.left_margin = k3fd->panel_info.ldi.h_back_porch;
	fbi->var.right_margin = k3fd->panel_info.ldi.h_front_porch;
	fbi->var.upper_margin = k3fd->panel_info.ldi.v_back_porch;
	fbi->var.lower_margin = k3fd->panel_info.ldi.v_front_porch;
	fbi->var.hsync_len = k3fd->panel_info.ldi.h_pulse_width;
	fbi->var.vsync_len = k3fd->panel_info.ldi.v_pulse_width;

	//We don't re-map the buffer
	if (fbi->screen_base != 0) {
		iounmap((void*)fbi->screen_base);
	}
	var->height = k3fd->panel_info.height;  /* height of picture in mm */
	var->width = k3fd->panel_info.width;  /* width of picture in mm */
	var->xres = k3fd->panel_info.xres;
	var->yres = k3fd->panel_info.yres;
	var->xres_virtual = k3fd->panel_info.xres;
	var->yres_virtual = k3fd->panel_info.yres * K3_NUM_FRAMEBUFFERS;
#if CONFIG_WFD_FBINFO
	if (k3fd->index == 0) {
		/* wifi display begin */
		wfd_fbi.xres = k3fd->panel_info.xres;
		wfd_fbi.yres = k3fd->panel_info.yres;
		wfd_fbi.xstride = var->xres_virtual;
		wfd_fbi.ystride = k3fd->panel_info.yres;
		/* wifi display end */
	}
#endif
	fix->line_length = k3_fb_line_length(var->xres_virtual, (var->bits_per_pixel >> 3));
	fix->smem_len = roundup(fix->line_length * var->yres_virtual, PAGE_SIZE);

	fbi->screen_size = fix->smem_len;
	if(fbi->screen_size > HISI_FRAME_BUFFER_SIZE) {
		k3fb_loge("error fbi->screen_size=%lu is larger than the reserved memory for FB\n", fbi->screen_size);
		return -1;
	}

	fbi->screen_base = ioremap(fbi->fix.smem_start, fbi->fix.smem_len);

	return 0;
}

STATIC int k3fb_resolution_switch(struct fb_info *info, unsigned long *argp)
{
	int ret  = 0;
	int flag = 0;

	BUG_ON(NULL == info);
	if (copy_from_user(&flag, argp, sizeof(flag))){
		k3fb_loge("copy from user failed\n");
		return -1;
	}

	struct k3_fb_data_type * k3fd = (struct k3_fb_data_type*)info->par;
	BUG_ON(k3fd == NULL);

	if (flag >= DISPLAY_LOW_POWER_LEVEL_MAX ) {
		k3fb_loge("Invalid level of Multi Resolution\n");
		return -1;
	}

	if (k3fd->index != 0){
		k3fb_loge("Invalid FB device\n");
		return -1;
	}

	if (k3fd->switch_res_flag == flag) {
		return 1;
	}
	k3fd->switch_res_flag = flag;
	k3_fb_blank_sub(FB_BLANK_POWERDOWN, info, 0);

	ret = k3_fb_switch_resolution_process(k3fd);

	return ret;
}

STATIC int k3fb_resolution_update(struct fb_info *info, unsigned long *argp)
{
	int flag = 0;

	BUG_ON(NULL == info);
	if (copy_from_user(&flag, argp, sizeof(flag))){
		k3fb_loge("copy from user failed\n");
		return -EFAULT;
	}
	struct k3_fb_data_type * k3fd = (struct k3_fb_data_type*)info->par;
	BUG_ON(k3fd == NULL);

	if (k3fd->switch_res_flag == flag) {
		k3_fb_blank_sub(FB_BLANK_UNBLANK, info, 0);
	}
	return 0;
}
//Multi Resolution====end

STATIC int k3_fb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int ret = 0;
#ifdef CONFIG_FB_CHECK_MIPI_TR
	int mipi_tr = -1;
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	int mipi_detect = -1;
#endif
	BUG_ON(info == NULL);

	down(&k3_fb_overlay_sem);
	switch (cmd) {
	case K3FB_OVERLAY_GET:
		ret = k3fb_overlay_get(info, argp);
		break;
	case K3FB_OVERLAY_SET:
		ret = k3fb_overlay_set(info, argp);
		break;
	case K3FB_OVERLAY_UNSET:
		ret = k3fb_overlay_unset(info, argp);
		break;
	case K3FB_OVERLAY_PLAY:
		ret = k3fb_overlay_play(info, argp);
		break;
	case K3FB_VSYNC_INT_SET:
		ret = k3fb_vsync_int_set(info, argp);
		break;
	case K3FB_TIMING_SET:
		ret = k3fb_set_timing(info, argp);
		break;
	case K3FB_FRC_SET:
		ret = k3fb_frc_set_state(info, argp);
		break;
	case K3FB_G2D_SET_FREQ:
		ret = k3fb_g2d_set_freq(info, argp);
		break;
	case K3FB_SBL_SET_VALUE:
		ret = k3fb_sbl_set_value(info, argp);
		break;
	case K3FB_G2D_LOCK_FREQ:
		ret = k3fb_g2d_lock_freq(info, argp);
		break;
#if defined(CONFIG_OVERLAY_COMPOSE)
	case K3FB_OVC_CHECK_DDR_FREQ:
		ret = k3fb_ovc_check_ddr_freq(info, argp);
		break;
#endif /* CONFIG_OVERLAY_COMPOSE */
#ifdef CONFIG_FOLLOWABILITY
        case K3FB_FOLLOW_START:
            k3fb_follow_start();
            break;

        case K3FB_FOLLOW_STOP:
            k3fb_follow_stop(argp);
            break;

        case K3FB_FIRST_DISP_TIME:
            ret = k3fb_first_disp_time(argp);
            break;

        case K3FB_GET_EVERY_DISP_TIME:
           ret = k3fb_every_disp_time(argp);
            break;

        case K3FB_GET_AVE_FRAME_RATE:
           ret = k3fb_average_frame_rate(argp);
            break;

        case K3FB_CLEAR_FRAME_RECORD:
            k3fb_clear_frame_record();
            break;
#endif

#if CONFIG_WFD_FBINFO
      /* wifi display begin */
       case K3FB_WIFI_DISP_GET_FBI:
            k3fb_wifi_disp_get_fbi(argp);
            break;
		case K3FB_WIFI_DISP_CLEAR_FBSTATUS:
			k3fb_wifi_disp_clear_fbstatus(argp);
			break;
	/* wifi display end */
#endif
		case K3FB_NSD_SET:
			k3fb_logd("K3FB_NSD_SET\n");
			k3_fb_nsd(info, argp);
			break;
#ifdef CONFIG_FB_CHECK_MIPI_TR
	case K3FB_CHECK_MIPI_TR:
		mipi_tr = k3_fb_check_mipi_tr(info);
		ret = copy_to_user(argp, &mipi_tr, sizeof(mipi_tr));
		if (ret) {
			printk(KERN_ERR "%s: K3FB_CHECK_MIPI_TR ioctl failed \n", __func__);
			return ret;
		}
		break;
#endif
#ifdef CONFIG_FB_SET_INVERSION
	case K3FB_SET_INVERSION:
		ret = k3_fb_set_inversion_type(info, argp);
		break;
#endif
#ifdef CONFIG_FB_MIPI_DETECT
	case K3FB_MIPI_DETECT:
		mipi_detect = k3_fb_mipi_detect(info);
		ret = copy_to_user(argp, &mipi_detect, sizeof(mipi_detect));
		if (ret) {
			printk(KERN_ERR "%s: K3FB_MIPI_DETECT ioctl failed \n", __func__);
			return ret;
		}
		break;
#endif

       //Multi Resolution====begin
	case K3FB_RESOLUTION_SWITCH:
		ret = k3fb_resolution_switch(info, argp);
		break;
	case K3FB_RESOLUTION_UPDATE:
		ret = k3fb_resolution_update(info, argp);
		break;
       //Multi Resolution====end

	default:
		//k3fb_loge("unknown ioctl (cmd=%d) received!\n", cmd);
		ret = -EINVAL;
		break;
	}

	up(&k3_fb_overlay_sem);
	return ret;
}

STATIC int k3_fb_blank(int blank_mode, struct fb_info *info)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	BUG_ON(info == NULL);
	k3fd = (struct k3_fb_data_type *)info->par;
	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	ret = k3_fb_blank_sub(blank_mode, info,1);
	if (ret != 0) {
		k3fb_loge("blank mode %d failed!\n", blank_mode);
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return ret;
}


/******************************************************************************/

static struct fb_ops k3_fb_ops = {
	.owner = THIS_MODULE,
	.fb_open = k3_fb_open,
	.fb_release = k3_fb_release,
	.fb_read = NULL,
	.fb_write = NULL,
	.fb_cursor = NULL,
	.fb_check_var = k3_fb_check_var,  /* vinfo check */
	.fb_set_par = k3_fb_set_par,  /* set the video mode according to info->var */
	.fb_setcolreg = NULL,  /* set color register */
	.fb_blank = k3_fb_blank, /*blank display */
	.fb_pan_display = k3_fb_pan_display,  /* pan display */
	.fb_fillrect = NULL,  /* Draws a rectangle */
	.fb_copyarea = NULL,  /* Copy data from area to another */
	.fb_imageblit = NULL,  /* Draws a image to the display */
	.fb_rotate = NULL,
	.fb_sync = NULL,  /* wait for blit idle, optional */
	.fb_ioctl = k3_fb_ioctl,  /* perform fb specific ioctl (optional) */
	.fb_mmap = NULL,
};

STATIC void k3_fb_set_bl_brightness(struct led_classdev *led_cdev,
	enum led_brightness value)
{
	struct k3_fb_data_type *k3fd = dev_get_drvdata(led_cdev->dev->parent);
	int bl_lvl;

	if (value > MAX_BACKLIGHT_BRIGHTNESS)
		value = MAX_BACKLIGHT_BRIGHTNESS;

	bl_lvl = value;
	k3fd->bl_level = value;
	k3fd->bl_level_sbl = value;

	if (k3fd->panel_info.bl_set_type & BL_SET_BY_PWM) {
		/*
		** This maps android backlight level 0 to 255 into
		** driver backlight level 0 to bl_max with rounding
		** bl_lvl = (2 * value * k3fd->panel_info.bl_max + MAX_BACKLIGHT_BRIGHTNESS)
		** (2 * MAX_BACKLIGHT_BRIGHTNESS);
		*/
		bl_lvl = (value * k3fd->panel_info.bl_max) / MAX_BACKLIGHT_BRIGHTNESS;
		bl_lvl &= 0xFF;

		if (!bl_lvl && value)
			bl_lvl = 1;

		k3fd->bl_level = bl_lvl;
		k3fd->bl_level_sbl = bl_lvl;
	}

	if ((k3fd->panel_info.type == PANEL_MIPI_CMD)
		&& (!k3fd->cmd_bl_can_set)) {
		    k3fb_logi_backlight_debugfs(" set backlight fail  k3fd->cmd_bl_can_set = %d ! \n", k3fd->cmd_bl_can_set);
			return;
    }

	if (k3fd->panel_info.sbl_enable)
		sbl_bkl_set(k3fd, bl_lvl);
	k3_fb_set_backlight(k3fd, k3fd->bl_level);
}

static struct led_classdev backlight_led = {
	.name = DEV_NAME_LCD_BKL,
	.brightness = MAX_BACKLIGHT_BRIGHTNESS,
	.brightness_set = k3_fb_set_bl_brightness,
};

#ifdef CONFIG_HAS_EARLYSUSPEND
static void k3fb_early_suspend(struct early_suspend *h)
{
	struct k3_fb_data_type *k3fd = container_of(h, struct k3_fb_data_type, early_suspend);

	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	if (k3fd->index == 0) {
		if (k3_fb_blank_sub(FB_BLANK_POWERDOWN, k3fd->fbi,1) != 0) {
			k3fb_loge("failed to early suspend!\n");
		}
	} else if (k3fd->panel_power_on) {
		edc_fb_disable(k3fd->fbi);
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);
}

static void k3fb_late_resume(struct early_suspend *h)
{
	struct k3_fb_data_type *k3fd = container_of(h, struct k3_fb_data_type, early_suspend);

	BUG_ON(k3fd == NULL);

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	if (k3fd->index == 0) {
		pm_qos_add_request(&g_cpunum_qos, PM_QOS_CPU_NUMBER_MIN, 0);
	       pm_qos_update_request(&g_cpunum_qos, PM_QOS_CPU_MIN_NUMBER);
		   
		if (k3_fb_blank_sub(FB_BLANK_UNBLANK, k3fd->fbi,1) != 0) {
			k3fb_loge("failed to late resume!\n");
		}
	} else if (k3fd->panel_power_on) {
		edc_fb_enable(k3fd->fbi);
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);
}
#endif

STATIC int __init cameratag(char *str)
{
    if ( strstr(str, "1") )
    {
	    g_debug_camerause = 1;
	}
	else
	{
	    g_debug_camerause = 0;
	}

	return 0;
}

#ifndef PC_UT_TEST_ON
early_param("cameratag", cameratag);
int get_resolution_type(void)
{
    unsigned int isfhd = 0;
    int ret = 0;

    ret = get_hw_config_int("lcd/resolution_type", &isfhd, NULL);
    if (!ret) {
        isfhd = 0;
         k3fb_logi("get lcd type from hw_config fail\n");
    }

     k3fb_logi("resolution_type is [%d]\n",isfhd);

    return isfhd;
}
#endif

void get_lcd_type(struct k3_fb_data_type *k3fd)
{
	BUG_ON(k3fd == NULL);
	if (k3fd->panel_info.xres >= 1920 || k3fd->panel_info.yres >= 1920) {		 
		isFHD = 1;
	}
	k3fb_loge("lcd_type=%d\n",isFHD);	
}
STATIC int k3_fb_init_par(struct k3_fb_data_type *k3fd, int pixel_fmt)
{
	struct fb_info *fbi = NULL;
	struct fb_var_screeninfo *var = NULL;
	struct fb_fix_screeninfo *fix = NULL;
	int bpp = 0;

	BUG_ON(k3fd == NULL);

	fbi = k3fd->fbi;
	fix = &fbi->fix;
	var = &fbi->var;

	fix->type_aux = 0;	/* if type == FB_TYPE_INTERLEAVED_PLANES */
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->visual = FB_VISUAL_TRUECOLOR;	/* True Color */
	fix->xpanstep = 1;
	fix->ypanstep = 1;
	fix->ywrapstep = 0;  /* No support */
	fix->mmio_start = 0;  /* No MMIO Address */
	fix->mmio_len = 0;	/* No MMIO Address */
	fix->accel = FB_ACCEL_NONE;  /* No hardware accelerator */

	var->xoffset = 0;  /* Offset from virtual to visible */
	var->yoffset = 0;  /* resolution */
	var->grayscale = 0;  /* No graylevels */
	var->nonstd = 0;  /* standard pixel format */
	/*var->activate = FB_ACTIVATE_NOW;*/
	var->activate = FB_ACTIVATE_VBL;  /* activate it at vsync */
	var->height = k3fd->panel_info.height;  /* height of picture in mm */
	var->width = k3fd->panel_info.width;  /* width of picture in mm */
	var->accel_flags = 0;  /* acceleration flags */
	var->sync = 0;	 /* see FB_SYNC_* */
	var->rotate = 0;   /* angle we rotate counter clockwise */
	var->vmode = FB_VMODE_NONINTERLACED;

	switch (pixel_fmt) {
	case IMG_PIXEL_FORMAT_RGBX_5551:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 15;
		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_ARGB_1555;
		break;
	case IMG_PIXEL_FORMAT_RGBA_5551:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 10;
		var->transp.offset = 15;
		var->blue.length = 5;
		var->green.length = 5;
		var->red.length = 5;
		var->transp.length = 1;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_ARGB_1555;
		break;
	case IMG_PIXEL_FORMAT_RGB_565:
		var->blue.offset = 0;
		var->green.offset = 5;
		var->red.offset = 11;
		var->transp.offset = 0;
		var->blue.length = 5;
		var->green.length = 6;
		var->red.length = 5;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 2;
		k3fd->fb_imgType = EDC_RGB_565;
		break;
	case IMG_PIXEL_FORMAT_RGBX_8888:
		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;
		var->blue.length = 8;
		var->green.length = 8;
		var->red.length = 8;
		var->transp.length = 0;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 4;
		k3fd->fb_imgType = EDC_XRGB_8888;
		break;
	case IMG_PIXEL_FORMAT_RGBA_8888:
		var->blue.offset = 0;
		var->green.offset = 8;
		var->red.offset = 16;
		var->transp.offset = 24;
		var->blue.length = 8;
		var->green.length = 8;
		var->red.length = 8;
		var->transp.length = 8;
		var->blue.msb_right = 0;
		var->green.msb_right = 0;
		var->red.msb_right = 0;
		var->transp.msb_right = 0;
		bpp = 4;
		k3fd->fb_imgType = EDC_ARGB_8888;
		break;
	default:
		k3fb_loge("index=%d, unkown image type!\n", k3fd->index);
		return -EINVAL;
	}

	var->xres = k3fd->panel_info.xres;
	var->yres = k3fd->panel_info.yres;
#if USE_VIVANTE_GPU
	if (k3fd->index == 0) {
		var->xres_virtual = ALIGN_UP(k3fd->panel_info.xres, 16);
	} else {
		var->xres_virtual = k3fd->panel_info.xres;
	}
#else
	var->xres_virtual = k3fd->panel_info.xres;
#endif
	var->yres_virtual = k3fd->panel_info.yres * K3_NUM_FRAMEBUFFERS;
	var->bits_per_pixel = bpp * 8;

	fix->line_length = k3_fb_line_length(var->xres_virtual, bpp);
	fix->smem_len = roundup(fix->line_length * var->yres_virtual, PAGE_SIZE);

#if CONFIG_WFD_FBINFO
	if (k3fd->index == 0) {
	/* wifi display begin */
	wfd_fbi.xres = k3fd->panel_info.xres;
	wfd_fbi.yres = k3fd->panel_info.yres;
	wfd_fbi.xstride = var->xres_virtual;
	wfd_fbi.ystride = k3fd->panel_info.yres;
	/* wifi display end */
	}
#endif
	/* id field for fb app */
	snprintf(fix->id, sizeof(fix->id), "k3fb%d", k3fd->index);

	fbi->fbops = &k3_fb_ops;
	fbi->flags = FBINFO_FLAG_DEFAULT; /* FBINFO_HWACCEL_YPAN | FBINFO_HWACCEL_XPAN */
	fbi->pseudo_palette = k3_fb_pseudo_palette;

	if (k3fd->index == 0) {
		fbi->fix.smem_start = (int32_t)K3_FB_PA;
		fbi->screen_size = fix->smem_len;

		if(fbi->screen_size > HISI_FRAME_BUFFER_SIZE )
		{
	        k3fb_loge("error fbi->screen_size=%lu is larger than the reserved memory for FB\n", fbi->screen_size);
	        return -EINVAL;
		}
		
		fbi->screen_base = ioremap(fbi->fix.smem_start, fbi->fix.smem_len);
		/*memset(fbi->screen_base, 0x0, fbi->fix.smem_len);*/
	} else {
		fbi->fix.smem_start = fbi_list[0]->fix.smem_start;
		fbi->screen_size = fbi_list[0]->screen_size;
		fbi->screen_base = fbi_list[0]->screen_base;
	}

	return 0;
}

int k3_fb_register(struct k3_fb_data_type *k3fd)
{
	int ret = 0;
#ifdef CONFIG_FASTBOOT_DISP_ENABLE
	struct k3_fb_panel_data *pdata = NULL;
#endif
	struct fb_info *fbi = NULL;
	struct fb_fix_screeninfo *fix = NULL;

	BUG_ON(k3fd == NULL);

	/* fb info initialization */
	fbi = k3fd->fbi;
	fix = &fbi->fix;

	ret = k3_fb_init_par(k3fd, IMG_PIXEL_FORMAT_RGBA_8888);
	if (ret != 0) {
		k3fb_loge("index=%d, k3_fb_init_par failed!\n", k3fd->index);
		return ret;
	}

	/* init edc overlay, only intialize one time */
	edc_overlay_init(&k3fd->ctrl);
	get_lcd_type(k3fd);
	k3fd->fb_bgrFmt = K3FB_DEFAULT_BGR_FORMAT;
	k3fd->ref_cnt = 0;
	k3fd->panel_power_on = false;
	sema_init(&k3fd->sem, 1);
	if (!(k3fd->panel_info.bl_set_type & BL_SET_BY_PWM)) {
		k3fd->bl_level = 102;
	} else {
		k3fd->bl_level = 40;
	}
	k3fd->ldi_int_type = FB_LDI_INT_TYPE_NONE;
	k3fd->cmd_mode_refresh = false;
	k3fd->cmd_bl_can_set = false;
	k3fd->checkesd_bl_cannot_set = false;
	k3fd->ambient_temperature = 0;
	k3fd->dsi_clk_last = k3fd->panel_info.mipi.dsi_bit_clk;
	k3fd->phy_ctrl1 = phy_ctrl[1];
	/* register framebuffer */
	if (register_framebuffer(fbi) < 0) {
		k3fb_loge("not able to register framebuffer %d!\n", k3fd->index);
		return -EPERM;
	}

	/* request edc irq */
	k3fd->update_frame = 0;
	init_waitqueue_head(&k3fd->frame_wq);
	snprintf(k3fd->edc_irq_name, sizeof(k3fd->edc_irq_name), "%s_edc", fix->id);
	ret = request_irq(k3fd->edc_irq, edc_isr, IRQF_SHARED, k3fd->edc_irq_name, (void *)k3fd);
	if (ret != 0) {
		k3fb_loge("index=%d unable to request edc irq\n", k3fd->index);
	}

	disable_irq(k3fd->edc_irq);

	/* register edc_irq to core 1
     *
     * TODO: to confirm k3v2_irqaffinity_register is OK or not.
	 */
	//k3v2_irqaffinity_register(k3fd->edc_irq, 1);

	/* request ldi irq */
	snprintf(k3fd->ldi_irq_name, sizeof(k3fd->ldi_irq_name), "%s_ldi", fix->id);
	ret = request_irq(k3fd->ldi_irq, ldi_isr, IRQF_SHARED, k3fd->ldi_irq_name, (void *)k3fd);
	if (ret != 0) {
		k3fb_loge("index=%d unable to request ldi irq\n", k3fd->index);
	}

	disable_irq(k3fd->ldi_irq);

	/* register ldi_irq to core 1 */
	//k3v2_irqaffinity_register(k3fd->ldi_irq, 1);

	if (k3fd->index == 0) {
		if (k3fd->panel_info.frc_enable) {
			k3fd->frc_threshold_count = 0;
			k3fd->frc_state = K3_FB_FRC_NONE_PLAYING;
			k3fd->frc_timestamp = jiffies;
		}

		memset(&(k3fd->vsync_info), 0, sizeof(k3fd->vsync_info));
		spin_lock_init(&k3fd->vsync_info.irq_lock);

		if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
		    /* Add for set frc, begin */
		    k3fd->use_cmd_vsync = false;
		    /* Add for set frc ,end */

			/* hrtimer for  vsync timing */
			hrtimer_init(&k3fd->cmd_vsync_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
			k3fd->cmd_vsync_hrtimer.function = k3fb_cmd_vsync;
			hrtimer_start(&k3fd->cmd_vsync_hrtimer, ktime_set(0, NSEC_PER_SEC / 60), HRTIMER_MODE_REL);
		}

		/* for temperature obtaining*/
		init_temperature_workqueue(k3fd);
		if (k3fd->panel_info.esd_enable) {
			if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
				/* hrtimer for ESD timing */
				hrtimer_init(&k3fd->esd_hrtimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
				k3fd->esd_hrtimer.function = k3fb_cmd_esd;
				k3fd->esd_hrtimer_enable = false;
				hrtimer_start(&k3fd->esd_hrtimer, ktime_set(0, NSEC_PER_SEC), HRTIMER_MODE_REL);
			} else {
				k3fd->esd_timestamp = jiffies;
				k3fd->esd_frame_count = 0;
			}
		}

		if (k3fd->panel_info.sbl_enable) {
			init_sbl_workqueue(k3fd);
		}

		/* Vsync */
		init_waitqueue_head(&k3fd->vsync_info.wait);

		/* Create vsync thread */
		k3fd->vsync_info.thread = kthread_run(k3fb_wait_for_vsync_thread, k3fd, "k3fb-vsync");
		if (IS_ERR(k3fd->vsync_info.thread)) {
			k3fb_loge("failed to run vsync thread\n");
			k3fd->vsync_info.thread = NULL;
		}
		
		init_waitqueue_head(&k3fd->fence_inc_wait);
		k3fd->fence_inc_thread = kthread_run(k3fb_fence_inc_thread, k3fd, "k3fb-fenceinc");
		if (IS_ERR(k3fd->fence_inc_thread)) {
			k3fb_loge("failed to run fenceinc thread\n");
			k3fd->fence_inc_thread = NULL;
		}		

	} else if (k3fd->index == 1) {
	
    init_waitqueue_head(&k3fd->fence_inc_wait);
    k3fd->fence_inc_thread = kthread_run(k3fb_fence_inc_thread, k3fd, "k3fb-fenceinc-edc1");
    if (IS_ERR(k3fd->fence_inc_thread)) {
        k3fb_loge("failed to run fenceinc-edc1 thread\n");
        k3fd->fence_inc_thread = NULL;
    }   
	#if K3_FB_OVERLAY_USE_BUF
		overlay_play_work(k3fd);
	#endif
	} else {
		k3fb_loge("fb%d not support now!\n", k3fd->index);
	}

#ifdef CONFIG_HAS_EARLYSUSPEND
	k3fd->early_suspend.suspend = k3fb_early_suspend;
	k3fd->early_suspend.resume = k3fb_late_resume;
	k3fd->early_suspend.level = EARLY_SUSPEND_LEVEL_DISABLE_FB - 2;
	register_early_suspend(&k3fd->early_suspend);
#endif

#ifndef PC_UT_TEST_ON
if(0==get_resolution_type())
#endif
{
#ifdef CONFIG_FASTBOOT_DISP_ENABLE
	if (k3fd->index == 0) {
		pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;

		k3fd->ref_cnt++;
		k3fd->panel_power_on = true;
             
	       k3_fb_power_on_vote(k3fd);
              pm_qos_add_request(&g_cpunum_qos, PM_QOS_CPU_NUMBER_MIN, 0);
	       pm_qos_update_request(&g_cpunum_qos, PM_QOS_CPU_MIN_NUMBER);
		   
		if (pdata && pdata->set_fastboot) {
			pdata->set_fastboot(k3fd->pdev);
		}

		set_EDC_INTE(k3fd->edc_base, 0xFFFFFFFF);
		set_EDC_INTS(k3fd->edc_base, 0x0);

		/* enable edc irq */
		if (k3fd->edc_irq)
			enable_irq(k3fd->edc_irq);
		/* enable ldi irq */
		if (k3fd->ldi_irq)
			enable_irq(k3fd->ldi_irq);

		if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
			set_reg(k3fd->edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 0);
			set_reg(k3fd->edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 7);
	      		set_reg(k3fd->edc_base + LDI_INT_EN_OFFSET, 0x1, 1, 12);
		} else {
			set_EDC_INTE(k3fd->edc_base, 0xFFFFFF3F);
		}

		if (k3fd->panel_info.type == PANEL_MIPI_CMD) {
            	    set_EDC_DSI_TE_CTRL_dsi_te_mask_en(1);
			clk_enable(k3fd->ldi_clk);
			clk_enable(k3fd->edc_clk);
			clk_enable(k3fd->edc_axi_clk);
			clk_enable(k3fd->edc_cfg_clk);
			clk_enable(k3fd->mipi_dphy0_cfg_clk);
			clk_enable(k3fd->mipi_dphy0_ref_clk);
			clk_enable(k3fd->dsi_cfg_clk);

		}
	}
#endif
}
	return ret;
}
#if 0
void EDC_ClkInit(void)
{
    static volatile DWORD*   g_pSysCtrlVirtReg;
    static volatile DWORD*   g_pPmCtrlVirtReg;
    st_SC_Cfg8Bit7              stEdc0ScCfgDiv;
    long                        regvalue;

    printk("%s enter! \n",__func__);


    g_pSysCtrlVirtReg = (DWORD*)ioremap(SYS_CTRL_BASE,SYS_CTRL_REG_SIZE);
    g_pPmCtrlVirtReg = (DWORD*)ioremap(PM_CTRL_BASE,PM_CTRL_REG_SIZE);

    /**********-----start---------------------------*/
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS0_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS1_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS2_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS3_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS4_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS5_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTDIS6_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PW_CLKDIS0_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PW_CLKDIS1_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PW_RSTDIS0_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PW_RSTDIS1_OFFSET, 0xffffffff);
    /******************************end*****************************/

    udelay(10);

    /*************-----start----------------------------*/
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN0_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN1_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN2_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN3_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN4_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN5_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN6_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN7_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN8_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN9_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN10_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKEN11_OFFSET, 0xffffffff);

    OUTREG32(g_pSysCtrlVirtReg + SC_PW_CLKEN0_OFFSET, 0xffffffff);
    OUTREG32(g_pSysCtrlVirtReg + SC_PW_CLKEN1_OFFSET, 0xffffffff);
    /******************************end*****************************/

    /*-------start----------*/
    udelay(10);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKSTAT0_OFFSET);
    printk("SC_PERIPH_CLKSTAT0_OFFSET: 0x%lx \n", regvalue);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKSTAT6_OFFSET);
    printk("SC_PERIPH_CLKSTAT6_OFFSET: 0x%x \n", regvalue);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_CLKSTAT11_OFFSET);
    printk("SC_PERIPH_CLKSTAT11_OFFSET: 0x%x \n", regvalue);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTSTAT0_OFFSET);
    printk("SC_PERIPH_RSTSTAT0_OFFSET: 0x%x \n", regvalue);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTSTAT4_OFFSET);
    printk("SC_PERIPH_RSTSTAT4_OFFSET: 0x%x \n", regvalue);

    regvalue = INREG32(g_pSysCtrlVirtReg + SC_PERIPH_RSTSTAT6_OFFSET);
    printk("SC_PERIPH_RSTSTAT6_OFFSET: 0x%x \n", regvalue);
    /******************************end*****************************/


    printk("g_pSysCtrlVirtReg addr: 0x%x \n", g_pSysCtrlVirtReg);

    stEdc0ScCfgDiv.bitEdc0CoreDiv   = 7;
    stEdc0ScCfgDiv.bitEdc0CoreValid = 1;
    stEdc0ScCfgDiv.bitEdc0PixDiv    = 47;
    stEdc0ScCfgDiv.bitEdc0PixValid  = 1;
    OUTREG32(g_pSysCtrlVirtReg + SC_CLKCFG8BIT7, *(int *)&stEdc0ScCfgDiv);

    printk("stEdc0ScCfgDiv value: 0x%x \n", *(int *)&stEdc0ScCfgDiv);

    printk("%s exit! succ \n",__func__);

    return ;
}
#endif
/******************************************************************************/
STATIC int k3_fb_probe(struct platform_device *pdev)
{
	struct k3_fb_data_type *k3fd = NULL;
	struct resource *res = 0;
	int ret = 0;

	pr_info("%s enter! \n",__func__);

	if ((pdev->id == 0) && (pdev->num_resources > 0)) {
		res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, IRQ_EDC0_NAME);
		if (!res) {
			k3fb_loge("failed to get irq_edc0 resource.\n");
			return -ENXIO;
		}
		k3fd_irq_edc0 = res->start;

		res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, IRQ_EDC1_NAME);
		if (!res) {
			k3fb_loge("failed to get irq_edc1 resource.\n");
			return -ENXIO;
		}
		k3fd_irq_edc1 = res->start;

		res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, IRQ_LDI0_NAME);
		if (!res) {
			k3fb_loge("failed to get irq_ldi0 resource.\n");
			return -ENXIO;
		}
		k3fd_irq_ldi0 = res->start;

		res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, IRQ_LDI1_NAME);
		if (!res) {
			k3fb_loge("failed to get irq_ldi1 resource.\n");
			return -ENXIO;
		}
		k3fd_irq_ldi1 = res->start;

		res = platform_get_resource_byname(pdev, IORESOURCE_MEM, REG_BASE_EDC0_NAME);
		if (!res) {
			k3fb_loge("failed to get reg_base_edc0 resource.\n");
			return -ENXIO;
		}
		k3fd_reg_base_edc0 = (u32)ioremap(res->start,REG_EDC0_IOSIZE);

		res = platform_get_resource_byname(pdev, IORESOURCE_MEM, REG_BASE_EDC1_NAME);
		if (!res) {
			k3fb_loge("failed to get reg_base_edc1 resource.\n");
			return -ENXIO;
		}
		k3fd_reg_base_edc1 = (u32)ioremap(res->start,REG_EDC1_IOSIZE);

		res = platform_get_resource_byname(pdev, IORESOURCE_MEM, REG_BASE_DSI0_NAME);
		if (!res) {
			dev_err(&pdev->dev, "mipi_dsi, %s: failed to get reg_base_dsi resource\n", __func__);
			return -ENXIO;
		}

		k3fd_reg_base_dsi0  = (u32)ioremap(res->start,REG_DSI0_IOSIZE);

		k3_fb_resource_initialized = 1;
		return 0;
	}

	if (!k3_fb_resource_initialized) {
		k3fb_loge("fb resource not initialized!\n");
		return -EPERM;
	}

	if (pdev_list_cnt >= K3_FB_MAX_DEV_LIST) {
		k3fb_loge("too many fb devices!\n");
		return -ENOMEM;
	}

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	BUG_ON(k3fd == NULL);

	/* edc clock */
	if (k3fd->index == 0) {
		/* edc fence init */
		k3fd->timeline = sw_sync_timeline_create("k3-fb");
		k3fd->timeline_max = 1;
		k3fd->refresh = 0;
		spin_lock_init(&k3fd->refresh_lock);

	    k3fd->edc_vcc = regulator_get(NULL,  VCC_EDC0_NAME);
		if (IS_ERR(k3fd->edc_vcc)) {
			pr_err("k3fb, %s: failed to get edc0-vcc regulator\n", __func__);
			return PTR_ERR(k3fd->edc_vcc);
		}

		k3fd->edc_clk     = clk_get(NULL, CLK_EDC0_NAME);
		k3fd->edc_axi_clk = clk_get(NULL, CLK_EDC0_AXI_NAME);
		k3fd->edc_cfg_clk = clk_get(NULL, CLK_EDC0_CFG_NAME);

	#if defined(CONFIG_OVERLAY_COMPOSE)
		k3_fb_overlay_compose_init(k3fd);
	#endif

	} else if (k3fd->index == 1) {
        /* edc1 fence init */
        k3fd->timeline = sw_sync_timeline_create("k3-fb-edc1");
        k3fd->timeline_max = 1;
        k3fd->refresh = 0;
        spin_lock_init(&k3fd->refresh_lock);
        
		/* edc1 vcc */
		k3fd->edc_vcc = regulator_get(NULL,  VCC_EDC1_NAME);
		if (IS_ERR(k3fd->edc_vcc)) {
			k3fb_loge("failed to get edc1-vcc regulator!\n");
			return PTR_ERR(k3fd->edc_vcc);
		}

		k3fd->edc_clk     = clk_get(NULL, CLK_EDC1_NAME);
		k3fd->edc_axi_clk = clk_get(NULL, CLK_EDC1_AXI_NAME);
		k3fd->edc_cfg_clk = clk_get(NULL, CLK_EDC1_CFG_NAME);
	} else {
		k3fb_loge("fb%d not support now!\n", k3fd->index);
		return -ENXIO;
	}

	if (IS_ERR(k3fd->edc_clk)) {
		k3fb_loge("failed to get edc_clk!\n");
		return PTR_ERR(k3fd->edc_clk);
	}

	if (IS_ERR(k3fd->edc_axi_clk)) {
		k3fb_loge("failed to get edc_axi_clk!\n");
		return PTR_ERR(k3fd->edc_axi_clk);
	}

	if (IS_ERR(k3fd->edc_cfg_clk)) {
		k3fb_loge("failed to get edc_cfg_clk!\n");
		return PTR_ERR(k3fd->edc_cfg_clk);
	}

    if (k3fd->index == 0) {
        ret = clk_set_rate(k3fd->edc_clk,  EDC_CORE_CLK_RATE);
    } else {
        ret = clk_set_rate(k3fd->edc_clk,  EDC_CORE_CLK_RATE);//(k3fd->panel_info.yres < 720) ? EDC_CORE_CLK_RATE : ( k3fd->panel_info.clk_rate * 12 / 10));
    }
	if (ret != 0) {
		k3fb_loge("failed to set edc clk rate(%d).\n", EDC_CORE_CLK_RATE);
	#ifndef CONFIG_MACH_TC45MSU3
		return ret;
	#endif
	}

#ifdef CONFIG_G2D
	/*G2D clock*/
	k3fd->g2d_clk = clk_get(NULL, CLK_G2D_NAME);
	if (IS_ERR(k3fd->g2d_clk)) {
		k3fb_loge("failed to get g2d_clk!\n");
		return PTR_ERR(k3fd->g2d_clk);
	}
#endif
	/* fb register */
	ret = k3_fb_register(k3fd);
	if (ret != 0) {
		k3fb_loge("fb register failed!\n");
		return ret;
	}

	if (k3fd->index == 0) {
		/* fb sysfs create */
		k3_fb_sysfs_create(pdev);

		/* android supports only one lcd-backlight/lcd for now */
		if (led_classdev_register(&pdev->dev, &backlight_led))
			k3fb_loge("led_classdev_register failed!\n");
	}

	pdev_list[pdev_list_cnt++] = pdev;

	return 0;
}

STATIC int k3_fb_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;
	struct k3_fb_panel_data *pdata = NULL;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	if (!k3fd) {
		return 0;
	}

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	pdata = (struct k3_fb_panel_data *)k3fd->pdev->dev.platform_data;
	if (!pdata) {
		k3fb_loge("k3_fb_panel_data is null!\n");
		return -ENODEV;
	}

	ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, k3fd->fbi,1);
	if (ret != 0) {
		k3fb_loge("can't stop the device %d!\n", k3fd->index);
	}

	if(k3fd->timeline)
	{
		sw_sync_timeline_destroy(k3fd->timeline);
		k3fd->timeline = NULL;
	}

	if (pdata->remove) {
		ret = pdata->remove(k3fd->pdev);
		if (ret != 0) {
			k3fb_loge("no panel operation remove detected!\n");
		}
	}

	/* put g2d clock*/
	if (!IS_ERR(k3fd->g2d_clk)) {
		clk_put(k3fd->g2d_clk);
	}

	/* put edc clock */
	if (!IS_ERR(k3fd->edc_clk)) {
		clk_put(k3fd->edc_clk);
	}

	/* put edc cfg clock */
    if (!IS_ERR(k3fd->edc_axi_clk)) {
        clk_put(k3fd->edc_axi_clk);
    }

	/* put edc axi clock */
    if (!IS_ERR(k3fd->edc_cfg_clk)) {
        clk_put(k3fd->edc_cfg_clk);
    }

    /* dsp clock */
    if (!IS_ERR(k3fd->dsp_pll)) {
        clk_put(k3fd->dsp_pll);
    }

    /* peri clock */
    if (!IS_ERR(k3fd->peri_pll)) {
        clk_put(k3fd->peri_pll);
    }

	if (k3fd->index == 0) {

	#if defined(CONFIG_OVERLAY_COMPOSE)
		k3_fb_overlay_compose_deinit(k3fd);
	#endif

		/* put g2d clock*/
		if (!IS_ERR(k3fd->g2d_clk)) {
			clk_put(k3fd->g2d_clk);
		}

		if (k3fd->panel_info.sbl_enable && k3fd->sbl_wq) {
			destroy_workqueue(k3fd->sbl_wq);
			k3fd->sbl_wq = NULL;
		}

		if (k3fd->vsync_info.thread)
			kthread_stop(k3fd->vsync_info.thread);

        if (k3fd->fence_inc_thread)
            kthread_stop(k3fd->fence_inc_thread);
		k3_fb_sysfs_remove(pdev);

		led_classdev_unregister(&backlight_led);
	} else if (k3fd->index == 1) {
		/* put edc vcc */
		if (!IS_ERR(k3fd->edc_vcc)) {
			regulator_put(k3fd->edc_vcc);
		}

	#if K3_FB_OVERLAY_USE_BUF
		if (video_buf.play_wq) {
			video_buf.exit_work = 1;
			destroy_workqueue(video_buf.play_wq);
		}
	#endif
	} else {
		k3fb_loge("fb%d not support now!\n", k3fd->index);
		return EINVAL;
	}

	/* remove /dev/fb* */
	ret = unregister_framebuffer(k3fd->fbi);
	if (ret != 0) {
		k3fb_loge("can't unregister framebuffer %d!\n", k3fd->index);
	}

    iounmap((void*)k3fd_reg_base_edc0);
    iounmap((void*)k3fd_reg_base_edc1);
    iounmap((void*)k3fd_reg_base_dsi0);
	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return ret;
}

STATIC void k3_fb_shutdown(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	/* BUG_ON(k3fd == NULL); */
	if (!k3fd) {
		return;
	}

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, k3fd->fbi,1);
	if (ret != 0) {
		k3fb_loge("can't stop the device %d\n", k3fd->index);
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);
}

#if defined(CONFIG_PM) && !defined(CONFIG_HAS_EARLYSUSPEND)
static int k3_fb_suspend(struct platform_device *pdev, pm_message_t state)
{
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	/* BUG_ON(k3fd == NULL); */
	if (!k3fd) {
		return 0;
	}

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	ret = k3_fb_blank_sub(FB_BLANK_POWERDOWN, k3fd->fbi,1);
	if (ret != 0) {
		k3fb_loge("failed to suspend, error=%d!\n", ret);
		fb_set_suspend(k3fd->fbi, FBINFO_STATE_RUNNING);
	} else {
		pdev->dev.power.power_state = state;
	}

	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return ret;
}

static int k3_fb_resume(struct platform_device *pdev)
{
	/* This resume function is called when interrupt is enabled. */
	int ret = 0;
	struct k3_fb_data_type *k3fd = NULL;

	k3fd = (struct k3_fb_data_type *)platform_get_drvdata(pdev);
	/* BUG_ON(k3fd == NULL); */
	if (!k3fd) {
		return 0;
	}

	k3fb_logi("index=%d, enter!\n", k3fd->index);

	ret = k3_fb_blank_sub(FB_BLANK_UNBLANK, k3fd->fbi,1);
	if (ret != 0) {
		k3fb_loge("failed to resume, error=%d!\n", ret);
	}
	pdev->dev.power.power_state = PMSG_ON;
	fb_set_suspend(k3fd->fbi, FBINFO_STATE_RUNNING);

	k3fb_logi("index=%d, exit!\n", k3fd->index);

	return ret;
}
#else
#define k3_fb_suspend NULL
#define k3_fb_resume NULL
#endif


/******************************************************************************/

static struct platform_driver k3_fb_driver = {
	.probe = k3_fb_probe,
	.remove = k3_fb_remove,
	.suspend = k3_fb_suspend,
	.resume = k3_fb_resume,
	.shutdown = k3_fb_shutdown,
	.driver = {
		.name = DEV_NAME_FB,
		},
};

struct platform_device *k3_fb_add_device(struct platform_device *pdev)
{
	struct k3_fb_panel_data *pdata = NULL;
	struct platform_device *this_dev = NULL;
	struct fb_info *fbi = NULL;
	struct k3_fb_data_type *k3fd = NULL;
	u32 type = 0, id = 0, graphic_ch = 0;

	BUG_ON(pdev == NULL);

	pdata = pdev->dev.platform_data;
	BUG_ON(pdata == NULL);

	if (fbi_list_index >= MAX_FBI_LIST) {
		k3fb_loge("no more framebuffer info list!\n");
		return NULL;
	}

	/* alloc panel device data */
	id = pdev->id;
	type = pdata->panel_info->type;
	this_dev = k3_fb_device_alloc(pdata, type, fbi_list_index, &graphic_ch);
	if (!this_dev) {
		k3fb_loge("failed to k3_fb_device_alloc!\n");
		return NULL;
	}

	/* alloc framebuffer info + par data */
	fbi = framebuffer_alloc(sizeof(struct k3_fb_data_type), NULL);
	if (fbi == NULL) {
		k3fb_loge("can't alloca framebuffer info data!\n");
		/*platform_device_put(this_dev);*/
		k3_fb_device_free(this_dev);
		return NULL;
	}

	k3fd = (struct k3_fb_data_type *)fbi->par;
	k3fd->fbi = fbi;
	k3fd->panel.type = type;
	k3fd->panel.id = id;
	k3fd->graphic_ch = graphic_ch;
	k3fd->index = fbi_list_index;
	if (k3fd->index == 0) {
		k3fd->edc_base = k3fd_reg_base_edc0;
		k3fd->edc_irq = k3fd_irq_edc0;
		k3fd->ldi_irq = k3fd_irq_ldi0;
	} else if (k3fd->index == 1) {
		k3fd->edc_base = k3fd_reg_base_edc1;
		k3fd->edc_irq = k3fd_irq_edc1;
		k3fd->ldi_irq = k3fd_irq_ldi1;
	} else {
		k3fb_loge("fb%d not support now!\n", k3fd->index);
		return NULL;
	}

	/* link to the latest pdev */
	k3fd->pdev = this_dev;

	k3fd_list[k3fd_list_index++] = k3fd;
	fbi_list[fbi_list_index++] = fbi;

	 /* get/set panel info */
	memcpy(&k3fd->panel_info, pdata->panel_info, sizeof(struct k3_panel_info));

	/* set driver data */
	platform_set_drvdata(this_dev, k3fd);

	if (platform_device_add(this_dev)) {
		k3fb_loge("failed to platform_device_add!\n");
		/*platform_device_put(this_dev);*/
		framebuffer_release(fbi);
		k3_fb_device_free(this_dev);
		fbi_list_index--;
		return NULL;
	}

	return this_dev;
}
EXPORT_SYMBOL(k3_fb_add_device);

int __init k3_fb_init(void)
{
	int ret = -ENODEV;

	ret = platform_driver_register(&k3_fb_driver);
	if (ret) {
		k3fb_loge("not able to register the driver, error=%d!\n", ret);
		return ret;
	}

	return ret;
}

module_init(k3_fb_init);


#ifdef CONFIG_DEBUG_FS

#define FB_DEBUG_STR_LEN_MAX  100


int k3_fb_debug_read(struct file *file, char __user *user_buf, size_t count, loff_t *ppos)
{
    char  fb_debug_str[FB_DEBUG_STR_LEN_MAX] = {0};
    int   len = 0;

    do {
        if (g_fb_lowpower_debug_flag == 0) {
            strcpy(fb_debug_str, "clear");
            len = 5;
            break;
        }

        if (DEBUG_ALL_LOWPOWER_DISABLE == (g_fb_lowpower_debug_flag & DEBUG_ALL_LOWPOWER_DISABLE)) {
            strcpy(fb_debug_str, "all");
            len = 3;
            break;
        }

        if (g_fb_lowpower_debug_flag & DEBUG_EDC_LOWPOWER_DISABLE) {
            strcpy(fb_debug_str + len, "EDC ");
            len += 4;
        }

        if (g_fb_lowpower_debug_flag & DEBUG_MIPI_LOWPOWER_DISABLE) {
            strcpy(fb_debug_str + len, "MIPI ");
            len += 5;
        }

        if (g_fb_lowpower_debug_flag & DEBUG_LCD_LOWPOWER_DISABLE) {
            strcpy(fb_debug_str + len, "LCD ");
            len += 4;
        }
    } while(0);


    if (g_fb_colorbar_mod == 1) {
        strcpy(fb_debug_str + len, "colorbar on ");
        len += 12;
    } else {
        strcpy(fb_debug_str + len, "colorbar off ");
        len += 13;
    }

    if (g_fb_log_printk_flag.bits.bit_vsync == 1) {
        strcpy(fb_debug_str + len, "vsync log enable ");
        len += 17;
    }
    else{
        strcpy(fb_debug_str + len, "vsync log disable ");
        len += 18;
    }

    if (g_fb_log_printk_flag.bits.bit_display == 1) {
        strcpy(fb_debug_str + len, "display log enable ");
        len += 19;
    }
    else{
        strcpy(fb_debug_str + len, "display log disable ");
        len += 20;
    }

    if (g_fb_log_printk_flag.bits.bit_backlight == 1) {
        strcpy(fb_debug_str + len, "backlight log enable ");
        len += 21;
    }
    else{
        strcpy(fb_debug_str + len, "backlight log disable ");
        len += 22;
    }

    fb_debug_str[len] = 0;

    k3fb_logi("read file fb_debug_str = %s", fb_debug_str);

    return simple_read_from_buffer(user_buf, count, ppos, fb_debug_str, len);
}

int k3_fb_debug_write (struct file *file, const char __user *user_buf, size_t count, loff_t *ppos)
{
    char  fb_debug_str[FB_DEBUG_STR_LEN_MAX] = {0};

    if (count >= FB_DEBUG_STR_LEN_MAX) {
        k3fb_loge("str len error; count > %d",FB_DEBUG_STR_LEN_MAX);
        count = FB_DEBUG_STR_LEN_MAX - 1;
    }

    if (copy_from_user(&fb_debug_str, user_buf, count)) {
        k3fb_loge("copy_from_user fail! \n");
        return -EFAULT;
    }

    fb_debug_str[count] = 0;

    k3fb_logi("echo str: %s", fb_debug_str);

    g_fb_lowpower_debug_flag = 0;

    if (strstr(fb_debug_str, "all") != NULL) {
        g_fb_lowpower_debug_flag |= DEBUG_ALL_LOWPOWER_DISABLE;
    }

    if (strstr(fb_debug_str, "edc") != NULL) {
        g_fb_lowpower_debug_flag |= DEBUG_EDC_LOWPOWER_DISABLE;
    }

    if (strstr(fb_debug_str, "mipi") != NULL) {
        g_fb_lowpower_debug_flag |= DEBUG_MIPI_LOWPOWER_DISABLE;
    }

    if (strstr(fb_debug_str, "lcd") != NULL) {
        g_fb_lowpower_debug_flag |= DEBUG_LCD_LOWPOWER_DISABLE;
    }

    if (strstr(fb_debug_str, "g2d") != NULL) {
        g_fb_lowpower_debug_flag |= DEBUG_G2D_LOWPOWER_DISABLE;
    }

    if (strstr(fb_debug_str, "clear") != NULL) {
        g_fb_lowpower_debug_flag = 0;
    }

    if (strstr(fb_debug_str, "colorbar on") != NULL) {
        g_fb_colorbar_mod = 1;
    } else  if (strstr(fb_debug_str, "colorbar off") != NULL) {
        g_fb_colorbar_mod = 0;
    } else if (strstr(fb_debug_str, "vsync on") != NULL) {
        g_fb_log_printk_flag.bits.bit_vsync = 1;
    } else if (strstr(fb_debug_str, "vsync off") != NULL) {
        g_fb_log_printk_flag.bits.bit_vsync = 0;
    } else if (strstr(fb_debug_str, "display on") != NULL) {
        g_fb_log_printk_flag.bits.bit_display = 1;
    } else if (strstr(fb_debug_str, "display off") != NULL) {
        g_fb_log_printk_flag.bits.bit_display = 0;
    } else if (strstr(fb_debug_str, "all printk off") != NULL) {
        g_fb_log_printk_flag.ul32 = 0;
    } else if (strstr(fb_debug_str, "backlight on") != NULL) {
        g_fb_log_printk_flag.bits.bit_backlight = 1;
    } else if (strstr(fb_debug_str, "backlight off") != NULL) {
        g_fb_log_printk_flag.bits.bit_backlight = 0;
    } else {
        k3fb_loge("nothing to do");
    }

    return count;

}

struct file_operations k3_fb_debugfs_ops = {
    .read = k3_fb_debug_read,
    .write = k3_fb_debug_write,
};


int __init k3_fb_debug_init(void)
{
  debugfs_create_file("mit1_k3fb", 0664, NULL, NULL, &k3_fb_debugfs_ops);
  return 0;
}

late_initcall(k3_fb_debug_init);

#endif


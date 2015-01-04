/*
 *  miniisp camera driver head file
 *
 *  Author: 	Zhoujie (zhou.jie1981@163.com)
 *  Date:  	2013/10/29
 *  Version:	1.0
 *  History:	2013/10/29      Frist add driver for miniisp 
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/************************** END ***************************/

#ifndef __CAMERA_AGENT_H__
#define __CAMERA_AGENT_H__

#include <linux/workqueue.h>
#include "mini_k3_isp.h"
#include "mini_k3_ispv1.h"
#include "mini_k3_ispv1_afae.h"
#include "mini_k3_isp_io.h"
#include "mini_sensor_common.h"
#include "mini_isp.h"

enum stream_state {
	stream_state_off = 0,
	stream_state_on  = 1,
	stream_state_invalid = 2,
};

typedef enum _AE_mode {
	AUTO_MODE = 0,
	AVERAGE_MODE,
	CENTER_WEIGHTING_MODE,
	SPOT_MODE,
	MODE_MAX,
}AE_mode;

#define MINIISP_MAX_FACE_WIN  5
typedef struct _face_rect_s {
	u32 left;
	u32 top;
	u32 width;
	u32 height;
} face_rect_s;
typedef struct _face_win_info_s{
	face_rect_s face_area[MINIISP_MAX_FACE_WIN];
	u16 width; //length of preview size
	u16 height;//length of preview size
	u8   face_number;
	u8   index_max_face;
} face_win_info_s;

int camera_agent_get_test_result(void);
int camera_agent_get_sensormode(sensor_index_t sensor_index,u8 *size_index);
int camera_agent_set_sensormode(sensor_index_t sensor_index,u8 size_index,u8 hv_flip);
int camera_agent_s1_lock(sensor_index_t sensor_index);
int camera_agent_s1_lock_abort(void);
int camera_agent_set_s1_AF_enable(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_s1_AE_enable(sensor_index_t sensor_index,u8 onoff);
int camera_agent_take_pictures(sensor_index_t sensor_index, u8 size_index,u8 hv_flip, u32 exposure,u32 ad_gain,u8 rdn_mode,u8 motion_state);
//int camera_agent_take_pictures(sensor_index_t sensor_index, u8 size_index,u8 hv_flip, u32 exposure,u32 ad_gain);
int camera_agent_streamonoff(sensor_index_t sensor_index, u8 state);
int camera_agent_set_focusarea(mini_focus_win_info_s *win_info);
int camera_agent_set_focusmode(sensor_index_t sensor_index,camera_focus mode);
int camera_agent_set_meteringarea(mini_camera_rect_s *win_info);
int camera_agent_set_facearea(face_win_info_s *win_info);
int camera_agent_set_PreviewAFLock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_PreviewAELock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_PreviewAWBLock(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_GSensorInfo(mini_axis_triple *xyz);
int camera_agent_set_Motion_Detected(u8 global_motion,u8 local_motion);
int camera_agent_set_ANTIFLICKER(sensor_index_t sensor_index,camera_anti_banding banding);
int camera_agent_get_ANTIFLICKER(sensor_index_t sensor_index);
int camera_agent_set_ISOLEVEL(sensor_index_t sensor_index,camera_iso iso);
int camera_agent_set_EV(sensor_index_t sensor_index,int ev);
int camera_agent_set_awb(sensor_index_t sensor_index,camera_white_balance awb_mode);
int camera_agent_set_flash_mode(camera_flash flash_mode);
int camera_agent_set_Preflashon(void);
int camera_agent_set_AFlevel(sensor_index_t sensor_index,u8 level);
int camera_agent_set_scene_mode(sensor_index_t sensor_index,camera_scene scene);
int camera_agent_set_exposuretime(sensor_index_t sensor_index,u32 expotime);
int camera_agent_set_ADgain(sensor_index_t sensor_index,u32 ad_gain);
int camera_agent_set_ae_mode(sensor_index_t sensor_index,AE_mode mode);
int camera_agent_take_ae_image(void);
int camera_agent_set_auto_exposure(sensor_index_t sensor_index,u8 onoff);
int camera_agent_set_burst_shoot(u8 onoff);
int camera_agent_set_ae_over_state(u8 mode);
int camera_agent_set_denoise_mode(u8 onoff);
int camera_agent_hdr_process(int *ev_table);

/* add by zhoutian for mini-ISP meta data begin */
void mini_isp_meta_data_parser(void *viraddr, void *meta_data_ptr, camera_state state);
int mini_isp_meta_data_init(mini_isp_meta_data **meta_data_ptr);
void mini_isp_meta_data_exit(void **meta_data_ptr);
/* add by zhoutian for mini-ISP meta data end */

int mini_ov_get_band_threshold(mini_camera_sensor *sensor, camera_anti_banding banding);

void mini_isp_check_s1_abort_done(void);
bool mini_isp_check_caf_need_trigger_af(void);
camera_flash mini_isp_check_af_flash_mode(void);
camera_flash mini_isp_check_pre_flash_mode(void);
u32 cal_flash_off_drop_frame_num(void);
void mini_isp_flash_handler(struct work_struct *work);
int mini_isp_handler_init(mini_k3_isp_data *ispdata);
void mini_isp_handler_exit(mini_k3_isp_data *ispdata);

void mini_isp_hdr_process(struct work_struct *work);
int camera_agent_set_fast_shot_mode(sensor_index_t sensor_index,u8 mode);
int camera_agent_set_capture_mode(sensor_index_t sensor_index,u8 mode);

void mini_ov_set_wb_value(mini_isp_meta_data *meta_data, camera_state cur_state);
#endif

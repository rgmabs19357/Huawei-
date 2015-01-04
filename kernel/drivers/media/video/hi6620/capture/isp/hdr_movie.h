#ifndef __HDR_MOVIE_H__
#define __HDR_MOVIE_H__
#include "hdr_movie_comm.h"


//void ispv1_hdr_set_analog_gain_exposure(hdr_ae_algo_result * ae_result);

void ispv1_hdr_isp_vc_switch(u8 on);

//void ispv1_hdr_set_ATR_switch(int on);

int 	ispv1_hdr_ae_init(void);

int   	ispv1_hdr_ae_exit(void);

//void ispv1_hdr_parameter_init(void);

//u32 ispv1_hdr_banding_step_change(camera_anti_banding banding);

int ispv1_get_hdr_movie_ae_init_param(hdr_ae_constant_param * hdr_ae_param);

int ispv1_get_hdr_movie_ae_running_param(hdr_ae_volatile_param * output_param);

 int 	ispv1_set_hdr_movie_shutter_gain_to_sensor(hdr_ae_algo_result * ae_result);

//int  ispv1_awb_dynamic_ccm_gain();

#endif /*__HDR_MOVIE_AE_H__ */

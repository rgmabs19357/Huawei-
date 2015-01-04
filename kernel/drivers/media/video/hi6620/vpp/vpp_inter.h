/*
 **************************************************************************************
 *
 *       Filename:   vpp_inter.h
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  2011-07-8 16:20:00
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#ifndef __VPP_INTER_H__
#define __VPP_INTER_H__

#include "vpp_hal.h"

int inter_init(void);
void inter_deinit(void);

void inter_open(HAL_LAYER_E enLayer);
void inter_close(HAL_LAYER_E enLayer);

int inter_start(VPP_CONFIG_S* pVppConfig);

#endif  /* __VPP_INTER_H__ */


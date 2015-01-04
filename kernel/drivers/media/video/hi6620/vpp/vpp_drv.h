/*
 **************************************************************************************
 *
 *       Filename:  vpp_drv.h
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011-07-8 16:20:00
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#ifndef __VPP_DRV_H_
#define __VPP_DRV_H_

#include <linux/ioctl.h>

#include "vpp_inter.h"
#include "vpp_hal.h"
#include "vpp_drv_ext.h"

/* Use 'k' as magic number */
#define VPP_IOC_MAGIC  'k'

#define VPP_STARTCONFIG            _IOWR(VPP_IOC_MAGIC, 1, VPP_CONFIG_S)

#define VPP_GETBUSADDR             _IOWR(VPP_IOC_MAGIC, 2, unsigned long)

#define VPP_IOC_MAXNR 2

int vpp_request_rst(void);
void vpp_force_rst(void);
void vpp_clk_rstdisable(void);
int vpp_clk_get(void);
int vpp_clk_enable(void);
void vpp_clk_disable(void);
void vpp_clk_put(void);
int vpp_regulator_enable(void);
void vpp_regulator_disable(void);



#endif


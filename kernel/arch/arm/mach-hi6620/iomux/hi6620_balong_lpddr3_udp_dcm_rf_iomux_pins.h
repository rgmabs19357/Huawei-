/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_balong_lpddr3_udp_dcm_rf_iomux_pins.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_BALONG_LPDDR3_UDP_DCM_RF_IOMUX_PINS_H__
#define __HI6620_BALONG_LPDDR3_UDP_DCM_RF_IOMUX_PINS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <mach/platform.h>
#include <mach/io.h>
#include <linux/mux.h>
#include "iomux.h"

/*board id can not be used precompile*/
#define V110_VERSION

extern struct iomux_ops iomux_pin_ops;

#define IOMUX_IOMG(_iomg, _iomg_name, _iomg_reg, _func_array)\
static struct iomux_iomg _iomg = {\
    .name = _iomg_name,\
    .iomg_reg = (void __iomem    *)(IO_ADDRESS(REG_BASE_IOC_OFF) + _iomg_reg),\
    .regValue = _func_array,\
};

#define IOMUX_IOCG(_iocg, _iocg_name, _iocg_reg, _iocg_pud_mask, _iocg_drvstrength_mask)    \
static struct iomux_iocg _iocg = {\
    .name = _iocg_name,\
    .iocg_reg = (void __iomem    *)(IO_ADDRESS(REG_BASE_IOC_OFF) + _iocg_reg),\
    .iocg_pullupdown_mask = _iocg_pud_mask,\
    .iocg_drivestrength_mask = _iocg_drvstrength_mask,\
};

#define IOMUX_PIN(_iomux_pin, _iomux_pin_name, _pin_func, _pin_pull_updown, \
_pin_drive_strength, _pin_iomg, _pin_iocg)    \
static struct  iomux_pin _iomux_pin = {\
    .pin_name = _iomux_pin_name,\
    .pin_func  = _pin_func,\
    .pin_pull_updown = _pin_pull_updown,\
    .pin_drive_strength = _pin_drive_strength,\
    .ops  =  &iomux_pin_ops,\
    .pin_iomg = _pin_iomg,\
    .pin_iocg  = _pin_iocg,\
    .init = 0, \
};

#define PIN_TABLE(_pinname, _iomux_pin)    \
{\
    .pinname = _pinname,\
    .iomux_pin = _iomux_pin,\
}

/*define the iomg*/
static int iomg000_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg001_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg002_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg003_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg004_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg005_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg006_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg007_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg008_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg009_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg010_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg011_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg012_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg013_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg014_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg015_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg016_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg017_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg018_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg019_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg020_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg021_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg022_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg023_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg024_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg025_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg026_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg027_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg028_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg029_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg030_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg031_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg032_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg033_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg034_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg035_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg036_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg037_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg038_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg039_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg040_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg041_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg042_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg043_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg044_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg045_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg046_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg047_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg048_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg049_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg050_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg051_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg052_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg053_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg054_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg055_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg056_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg057_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, RESERVE, RESERVE,  };
static int iomg058_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, RESERVE, RESERVE,  };
static int iomg059_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg060_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg061_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg062_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg063_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg064_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg065_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg066_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg067_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg068_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg069_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg070_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg071_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg072_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg073_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg074_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg075_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg076_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg077_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg078_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg079_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg080_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg081_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg082_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg083_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg084_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg085_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg086_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg087_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg088_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg089_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, RESERVE,  };
static int iomg090_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg091_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg092_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg093_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg094_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg095_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg096_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg097_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg098_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg099_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg100_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg101_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg102_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg103_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg104_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg105_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg106_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg107_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg108_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg109_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg110_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg111_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg112_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg113_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg114_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg115_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg116_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg117_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg118_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg119_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg120_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg121_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg122_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg123_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg124_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg125_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg126_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg127_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg128_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg129_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg130_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg131_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg132_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg133_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg134_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg135_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, 7,  };
static int iomg136_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg137_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg138_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg139_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg140_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg141_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg142_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg143_func_array_balong_lpddr3_udp_dcm_rf[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg144_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg145_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg146_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg147_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg148_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg149_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg150_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg151_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg152_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg153_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg154_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg155_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg156_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg157_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg158_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg159_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg160_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg161_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg162_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg163_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg164_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg165_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg166_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg167_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg168_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg169_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg170_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg171_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg172_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg173_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg174_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg175_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg176_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg177_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg178_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg179_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg180_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg181_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg182_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg183_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg184_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg185_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg186_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg187_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg188_func_array_balong_lpddr3_udp_dcm_rf[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };


IOMUX_IOMG(iomg000_balong_lpddr3_udp_dcm_rf, "iomg000", 0x000, iomg000_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg001_balong_lpddr3_udp_dcm_rf, "iomg001", 0x004, iomg001_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg002_balong_lpddr3_udp_dcm_rf, "iomg002", 0x008, iomg002_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg003_balong_lpddr3_udp_dcm_rf, "iomg003", 0x00C, iomg003_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg004_balong_lpddr3_udp_dcm_rf, "iomg004", 0x010, iomg004_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg005_balong_lpddr3_udp_dcm_rf, "iomg005", 0x014, iomg005_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg006_balong_lpddr3_udp_dcm_rf, "iomg006", 0x018, iomg006_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg007_balong_lpddr3_udp_dcm_rf, "iomg007", 0x2F0, iomg007_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg008_balong_lpddr3_udp_dcm_rf, "iomg008", 0x01C, iomg008_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg009_balong_lpddr3_udp_dcm_rf, "iomg009", 0x020, iomg009_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg010_balong_lpddr3_udp_dcm_rf, "iomg010", 0x024, iomg010_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg011_balong_lpddr3_udp_dcm_rf, "iomg011", 0x028, iomg011_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg012_balong_lpddr3_udp_dcm_rf, "iomg012", 0x02C, iomg012_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg013_balong_lpddr3_udp_dcm_rf, "iomg013", 0x030, iomg013_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg014_balong_lpddr3_udp_dcm_rf, "iomg014", 0x034, iomg014_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg015_balong_lpddr3_udp_dcm_rf, "iomg015", 0x038, iomg015_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg016_balong_lpddr3_udp_dcm_rf, "iomg016", 0x03C, iomg016_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg017_balong_lpddr3_udp_dcm_rf, "iomg017", 0x040, iomg017_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg018_balong_lpddr3_udp_dcm_rf, "iomg018", 0x044, iomg018_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg019_balong_lpddr3_udp_dcm_rf, "iomg019", 0x048, iomg019_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg020_balong_lpddr3_udp_dcm_rf, "iomg020", 0x04C, iomg020_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg021_balong_lpddr3_udp_dcm_rf, "iomg021", 0x050, iomg021_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg022_balong_lpddr3_udp_dcm_rf, "iomg022", 0x054, iomg022_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg023_balong_lpddr3_udp_dcm_rf, "iomg023", 0x058, iomg023_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg024_balong_lpddr3_udp_dcm_rf, "iomg024", 0x05C, iomg024_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg025_balong_lpddr3_udp_dcm_rf, "iomg025", 0x060, iomg025_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg026_balong_lpddr3_udp_dcm_rf, "iomg026", 0x064, iomg026_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg027_balong_lpddr3_udp_dcm_rf, "iomg027", 0x068, iomg027_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg028_balong_lpddr3_udp_dcm_rf, "iomg028", 0x06C, iomg028_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg029_balong_lpddr3_udp_dcm_rf, "iomg029", 0x070, iomg029_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg030_balong_lpddr3_udp_dcm_rf, "iomg030", 0x074, iomg030_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg031_balong_lpddr3_udp_dcm_rf, "iomg031", 0x078, iomg031_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg032_balong_lpddr3_udp_dcm_rf, "iomg032", 0x07C, iomg032_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg033_balong_lpddr3_udp_dcm_rf, "iomg033", 0x080, iomg033_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg034_balong_lpddr3_udp_dcm_rf, "iomg034", 0x084, iomg034_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg035_balong_lpddr3_udp_dcm_rf, "iomg035", 0x088, iomg035_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg036_balong_lpddr3_udp_dcm_rf, "iomg036", 0x08C, iomg036_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg037_balong_lpddr3_udp_dcm_rf, "iomg037", 0x090, iomg037_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg038_balong_lpddr3_udp_dcm_rf, "iomg038", 0x094, iomg038_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg039_balong_lpddr3_udp_dcm_rf, "iomg039", 0x098, iomg039_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg040_balong_lpddr3_udp_dcm_rf, "iomg040", 0x09C, iomg040_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg041_balong_lpddr3_udp_dcm_rf, "iomg041", 0x0A0, iomg041_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg042_balong_lpddr3_udp_dcm_rf, "iomg042", 0x0A4, iomg042_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg043_balong_lpddr3_udp_dcm_rf, "iomg043", 0x0A8, iomg043_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg044_balong_lpddr3_udp_dcm_rf, "iomg044", 0x0AC, iomg044_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg045_balong_lpddr3_udp_dcm_rf, "iomg045", 0x0B0, iomg045_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg046_balong_lpddr3_udp_dcm_rf, "iomg046", 0x0B4, iomg046_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg047_balong_lpddr3_udp_dcm_rf, "iomg047", 0x0B8, iomg047_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg048_balong_lpddr3_udp_dcm_rf, "iomg048", 0x0BC, iomg048_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg049_balong_lpddr3_udp_dcm_rf, "iomg049", 0x0C0, iomg049_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg050_balong_lpddr3_udp_dcm_rf, "iomg050", 0x0C4, iomg050_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg051_balong_lpddr3_udp_dcm_rf, "iomg051", 0x0C8, iomg051_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg052_balong_lpddr3_udp_dcm_rf, "iomg052", 0x0CC, iomg052_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg053_balong_lpddr3_udp_dcm_rf, "iomg053", 0x0D0, iomg053_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg054_balong_lpddr3_udp_dcm_rf, "iomg054", 0x0D4, iomg054_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg055_balong_lpddr3_udp_dcm_rf, "iomg055", 0x0D8, iomg055_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg056_balong_lpddr3_udp_dcm_rf, "iomg056", 0x0DC, iomg056_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg057_balong_lpddr3_udp_dcm_rf, "iomg057", 0x0E0, iomg057_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg058_balong_lpddr3_udp_dcm_rf, "iomg058", 0x0E4, iomg058_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg059_balong_lpddr3_udp_dcm_rf, "iomg059", 0x0E8, iomg059_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg060_balong_lpddr3_udp_dcm_rf, "iomg060", 0x0EC, iomg060_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg061_balong_lpddr3_udp_dcm_rf, "iomg061", 0x0F0, iomg061_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg062_balong_lpddr3_udp_dcm_rf, "iomg062", 0x0F4, iomg062_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg063_balong_lpddr3_udp_dcm_rf, "iomg063", 0x0F8, iomg063_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg064_balong_lpddr3_udp_dcm_rf, "iomg064", 0x0FC, iomg064_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg065_balong_lpddr3_udp_dcm_rf, "iomg065", 0x100, iomg065_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg066_balong_lpddr3_udp_dcm_rf, "iomg066", 0x104, iomg066_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg067_balong_lpddr3_udp_dcm_rf, "iomg067", 0x108, iomg067_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg068_balong_lpddr3_udp_dcm_rf, "iomg068", 0x10C, iomg068_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg069_balong_lpddr3_udp_dcm_rf, "iomg069", 0x110, iomg069_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg070_balong_lpddr3_udp_dcm_rf, "iomg070", 0x114, iomg070_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg071_balong_lpddr3_udp_dcm_rf, "iomg071", 0x118, iomg071_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg072_balong_lpddr3_udp_dcm_rf, "iomg072", 0x11C, iomg072_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg073_balong_lpddr3_udp_dcm_rf, "iomg073", 0x120, iomg073_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg074_balong_lpddr3_udp_dcm_rf, "iomg074", 0x124, iomg074_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg075_balong_lpddr3_udp_dcm_rf, "iomg075", 0x128, iomg075_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg076_balong_lpddr3_udp_dcm_rf, "iomg076", 0x12C, iomg076_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg077_balong_lpddr3_udp_dcm_rf, "iomg077", 0x130, iomg077_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg078_balong_lpddr3_udp_dcm_rf, "iomg078", 0x134, iomg078_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg079_balong_lpddr3_udp_dcm_rf, "iomg079", 0x138, iomg079_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg080_balong_lpddr3_udp_dcm_rf, "iomg080", 0x13C, iomg080_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg081_balong_lpddr3_udp_dcm_rf, "iomg081", 0x140, iomg081_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg082_balong_lpddr3_udp_dcm_rf, "iomg082", 0x144, iomg082_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg083_balong_lpddr3_udp_dcm_rf, "iomg083", 0x148, iomg083_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg084_balong_lpddr3_udp_dcm_rf, "iomg084", 0x14C, iomg084_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg085_balong_lpddr3_udp_dcm_rf, "iomg085", 0x150, iomg085_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg086_balong_lpddr3_udp_dcm_rf, "iomg086", 0x154, iomg086_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg087_balong_lpddr3_udp_dcm_rf, "iomg087", 0x158, iomg087_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg088_balong_lpddr3_udp_dcm_rf, "iomg088", 0x15C, iomg088_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg089_balong_lpddr3_udp_dcm_rf, "iomg089", 0x2EC, iomg089_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg090_balong_lpddr3_udp_dcm_rf, "iomg090", 0x160, iomg090_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg091_balong_lpddr3_udp_dcm_rf, "iomg091", 0x164, iomg091_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg092_balong_lpddr3_udp_dcm_rf, "iomg092", 0x168, iomg092_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg093_balong_lpddr3_udp_dcm_rf, "iomg093", 0x16C, iomg093_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg094_balong_lpddr3_udp_dcm_rf, "iomg094", 0x170, iomg094_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg095_balong_lpddr3_udp_dcm_rf, "iomg095", 0x174, iomg095_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg096_balong_lpddr3_udp_dcm_rf, "iomg096", 0x2E8, iomg096_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg097_balong_lpddr3_udp_dcm_rf, "iomg097", 0x178, iomg097_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg098_balong_lpddr3_udp_dcm_rf, "iomg098", 0x17C, iomg098_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg099_balong_lpddr3_udp_dcm_rf, "iomg099", 0x180, iomg099_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg100_balong_lpddr3_udp_dcm_rf, "iomg100", 0x184, iomg100_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg101_balong_lpddr3_udp_dcm_rf, "iomg101", 0x188, iomg101_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg102_balong_lpddr3_udp_dcm_rf, "iomg102", 0x18C, iomg102_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg103_balong_lpddr3_udp_dcm_rf, "iomg103", 0x190, iomg103_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg104_balong_lpddr3_udp_dcm_rf, "iomg104", 0x194, iomg104_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg105_balong_lpddr3_udp_dcm_rf, "iomg105", 0x198, iomg105_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg106_balong_lpddr3_udp_dcm_rf, "iomg106", 0x19C, iomg106_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg107_balong_lpddr3_udp_dcm_rf, "iomg107", 0x1A0, iomg107_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg108_balong_lpddr3_udp_dcm_rf, "iomg108", 0x1A4, iomg108_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg109_balong_lpddr3_udp_dcm_rf, "iomg109", 0x1A8, iomg109_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg110_balong_lpddr3_udp_dcm_rf, "iomg110", 0x1AC, iomg110_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg111_balong_lpddr3_udp_dcm_rf, "iomg111", 0x1B0, iomg111_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg112_balong_lpddr3_udp_dcm_rf, "iomg112", 0x1B4, iomg112_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg113_balong_lpddr3_udp_dcm_rf, "iomg113", 0x1B8, iomg113_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg114_balong_lpddr3_udp_dcm_rf, "iomg114", 0x1BC, iomg114_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg115_balong_lpddr3_udp_dcm_rf, "iomg115", 0x1C0, iomg115_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg116_balong_lpddr3_udp_dcm_rf, "iomg116", 0x1C4, iomg116_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg117_balong_lpddr3_udp_dcm_rf, "iomg117", 0x1C8, iomg117_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg118_balong_lpddr3_udp_dcm_rf, "iomg118", 0x1CC, iomg118_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg119_balong_lpddr3_udp_dcm_rf, "iomg119", 0x1D0, iomg119_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg120_balong_lpddr3_udp_dcm_rf, "iomg120", 0x1D4, iomg120_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg121_balong_lpddr3_udp_dcm_rf, "iomg121", 0x1D8, iomg121_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg122_balong_lpddr3_udp_dcm_rf, "iomg122", 0x1DC, iomg122_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg123_balong_lpddr3_udp_dcm_rf, "iomg123", 0x1E0, iomg123_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg124_balong_lpddr3_udp_dcm_rf, "iomg124", 0x1E4, iomg124_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg125_balong_lpddr3_udp_dcm_rf, "iomg125", 0x1E8, iomg125_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg126_balong_lpddr3_udp_dcm_rf, "iomg126", 0x1EC, iomg126_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg127_balong_lpddr3_udp_dcm_rf, "iomg127", 0x1F0, iomg127_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg128_balong_lpddr3_udp_dcm_rf, "iomg128", 0x1F4, iomg128_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg129_balong_lpddr3_udp_dcm_rf, "iomg129", 0x1F8, iomg129_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg130_balong_lpddr3_udp_dcm_rf, "iomg130", 0x1FC, iomg130_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg131_balong_lpddr3_udp_dcm_rf, "iomg131", 0x200, iomg131_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg132_balong_lpddr3_udp_dcm_rf, "iomg132", 0x204, iomg132_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg133_balong_lpddr3_udp_dcm_rf, "iomg133", 0x208, iomg133_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg134_balong_lpddr3_udp_dcm_rf, "iomg134", 0x20C, iomg134_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg135_balong_lpddr3_udp_dcm_rf, "iomg135", 0x210, iomg135_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg136_balong_lpddr3_udp_dcm_rf, "iomg136", 0x214, iomg136_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg137_balong_lpddr3_udp_dcm_rf, "iomg137", 0x218, iomg137_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg138_balong_lpddr3_udp_dcm_rf, "iomg138", 0x21C, iomg138_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg139_balong_lpddr3_udp_dcm_rf, "iomg139", 0x220, iomg139_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg140_balong_lpddr3_udp_dcm_rf, "iomg140", 0x224, iomg140_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg141_balong_lpddr3_udp_dcm_rf, "iomg141", 0x228, iomg141_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg142_balong_lpddr3_udp_dcm_rf, "iomg142", 0x22C, iomg142_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg143_balong_lpddr3_udp_dcm_rf, "iomg143", 0x230, iomg143_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg144_balong_lpddr3_udp_dcm_rf, "iomg144", 0x234, iomg144_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg145_balong_lpddr3_udp_dcm_rf, "iomg145", 0x238, iomg145_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg146_balong_lpddr3_udp_dcm_rf, "iomg146", 0x23C, iomg146_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg147_balong_lpddr3_udp_dcm_rf, "iomg147", 0x240, iomg147_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg148_balong_lpddr3_udp_dcm_rf, "iomg148", 0x244, iomg148_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg149_balong_lpddr3_udp_dcm_rf, "iomg149", 0x248, iomg149_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg150_balong_lpddr3_udp_dcm_rf, "iomg150", 0x24C, iomg150_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg151_balong_lpddr3_udp_dcm_rf, "iomg151", 0x250, iomg151_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg152_balong_lpddr3_udp_dcm_rf, "iomg152", 0x254, iomg152_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg153_balong_lpddr3_udp_dcm_rf, "iomg153", 0x258, iomg153_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg154_balong_lpddr3_udp_dcm_rf, "iomg154", 0x25C, iomg154_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg155_balong_lpddr3_udp_dcm_rf, "iomg155", 0x260, iomg155_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg156_balong_lpddr3_udp_dcm_rf, "iomg156", 0x264, iomg156_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg157_balong_lpddr3_udp_dcm_rf, "iomg157", 0x268, iomg157_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg158_balong_lpddr3_udp_dcm_rf, "iomg158", 0x26C, iomg158_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg159_balong_lpddr3_udp_dcm_rf, "iomg159", 0x270, iomg159_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg160_balong_lpddr3_udp_dcm_rf, "iomg160", 0x274, iomg160_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg161_balong_lpddr3_udp_dcm_rf, "iomg161", 0x278, iomg161_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg162_balong_lpddr3_udp_dcm_rf, "iomg162", 0x27C, iomg162_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg163_balong_lpddr3_udp_dcm_rf, "iomg163", 0x280, iomg163_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg164_balong_lpddr3_udp_dcm_rf, "iomg164", 0x284, iomg164_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg165_balong_lpddr3_udp_dcm_rf, "iomg165", 0x288, iomg165_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg166_balong_lpddr3_udp_dcm_rf, "iomg166", 0x28C, iomg166_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg167_balong_lpddr3_udp_dcm_rf, "iomg167", 0x290, iomg167_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg168_balong_lpddr3_udp_dcm_rf, "iomg168", 0x294, iomg168_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg169_balong_lpddr3_udp_dcm_rf, "iomg169", 0x298, iomg169_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg170_balong_lpddr3_udp_dcm_rf, "iomg170", 0x29C, iomg170_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg171_balong_lpddr3_udp_dcm_rf, "iomg171", 0x2A0, iomg171_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg172_balong_lpddr3_udp_dcm_rf, "iomg172", 0x2A4, iomg172_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg173_balong_lpddr3_udp_dcm_rf, "iomg173", 0x2A8, iomg173_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg174_balong_lpddr3_udp_dcm_rf, "iomg174", 0x2AC, iomg174_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg175_balong_lpddr3_udp_dcm_rf, "iomg175", 0x2B0, iomg175_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg176_balong_lpddr3_udp_dcm_rf, "iomg176", 0x2B4, iomg176_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg177_balong_lpddr3_udp_dcm_rf, "iomg177", 0x2B8, iomg177_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg178_balong_lpddr3_udp_dcm_rf, "iomg178", 0x2BC, iomg178_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg179_balong_lpddr3_udp_dcm_rf, "iomg179", 0x2C0, iomg179_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg180_balong_lpddr3_udp_dcm_rf, "iomg180", 0x2C4, iomg180_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg181_balong_lpddr3_udp_dcm_rf, "iomg181", 0x2C8, iomg181_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg182_balong_lpddr3_udp_dcm_rf, "iomg182", 0x2CC, iomg182_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg183_balong_lpddr3_udp_dcm_rf, "iomg183", 0x2D0, iomg183_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg184_balong_lpddr3_udp_dcm_rf, "iomg184", 0x2D4, iomg184_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg185_balong_lpddr3_udp_dcm_rf, "iomg185", 0x2D8, iomg185_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg186_balong_lpddr3_udp_dcm_rf, "iomg186", 0x2DC, iomg186_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg187_balong_lpddr3_udp_dcm_rf, "iomg187", 0x2E0, iomg187_func_array_balong_lpddr3_udp_dcm_rf)
IOMUX_IOMG(iomg188_balong_lpddr3_udp_dcm_rf, "iomg188", 0x2E4, iomg188_func_array_balong_lpddr3_udp_dcm_rf)


/*define pins*/
IOMUX_IOCG(iocg000_balong_lpddr3_udp_dcm_rf, "iocg000", 0x800, 0x0003, 0x00F0)
IOMUX_IOCG(iocg001_balong_lpddr3_udp_dcm_rf, "iocg001", 0x804, 0x0003, 0x00F0)
IOMUX_IOCG(iocg002_balong_lpddr3_udp_dcm_rf, "iocg002", 0x808, 0x0003, 0x00F0)
IOMUX_IOCG(iocg003_balong_lpddr3_udp_dcm_rf, "iocg003", 0x80C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg004_balong_lpddr3_udp_dcm_rf, "iocg004", 0x810, 0x0003, 0x00F0)
IOMUX_IOCG(iocg005_balong_lpddr3_udp_dcm_rf, "iocg005", 0x814, 0x0003, 0x00F0)
IOMUX_IOCG(iocg006_balong_lpddr3_udp_dcm_rf, "iocg006", 0x818, 0x0003, 0x00F0)
IOMUX_IOCG(iocg007_balong_lpddr3_udp_dcm_rf, "iocg007", 0x81C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg008_balong_lpddr3_udp_dcm_rf, "iocg008", 0x820, 0x0003, 0x00F0)
IOMUX_IOCG(iocg009_balong_lpddr3_udp_dcm_rf, "iocg009", 0x824, 0x0003, 0x00F0)
IOMUX_IOCG(iocg010_balong_lpddr3_udp_dcm_rf, "iocg010", 0x828, 0x0003, 0x00F0)
IOMUX_IOCG(iocg011_balong_lpddr3_udp_dcm_rf, "iocg011", 0x82C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg012_balong_lpddr3_udp_dcm_rf, "iocg012", 0x830, 0x0003, 0x00F0)
IOMUX_IOCG(iocg013_balong_lpddr3_udp_dcm_rf, "iocg013", 0x834, 0x0003, 0x00F0)
IOMUX_IOCG(iocg014_balong_lpddr3_udp_dcm_rf, "iocg014", 0x838, 0x0003, 0x00F0)
IOMUX_IOCG(iocg015_balong_lpddr3_udp_dcm_rf, "iocg015", 0x83C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg016_balong_lpddr3_udp_dcm_rf, "iocg016", 0x840, 0x0003, 0x00F0)
IOMUX_IOCG(iocg017_balong_lpddr3_udp_dcm_rf, "iocg017", 0x844, 0x0003, 0x00F0)
IOMUX_IOCG(iocg018_balong_lpddr3_udp_dcm_rf, "iocg018", 0x848, 0x0003, 0x00F0)
IOMUX_IOCG(iocg019_balong_lpddr3_udp_dcm_rf, "iocg019", 0x84C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg020_balong_lpddr3_udp_dcm_rf, "iocg020", 0x850, 0x0003, 0x00F0)
IOMUX_IOCG(iocg021_balong_lpddr3_udp_dcm_rf, "iocg021", 0x854, 0x0003, 0x00F0)
IOMUX_IOCG(iocg022_balong_lpddr3_udp_dcm_rf, "iocg022", 0x858, 0x0003, 0x00F0)
IOMUX_IOCG(iocg023_balong_lpddr3_udp_dcm_rf, "iocg023", 0x85C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg024_balong_lpddr3_udp_dcm_rf, "iocg024", 0x860, 0x0003, 0x00F0)
IOMUX_IOCG(iocg025_balong_lpddr3_udp_dcm_rf, "iocg025", 0x864, 0x0003, 0x00F0)
IOMUX_IOCG(iocg026_balong_lpddr3_udp_dcm_rf, "iocg026", 0x868, 0x0003, 0x00F0)
IOMUX_IOCG(iocg027_balong_lpddr3_udp_dcm_rf, "iocg027", 0x86C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg028_balong_lpddr3_udp_dcm_rf, "iocg028", 0x870, 0x0003, 0x00F0)
IOMUX_IOCG(iocg029_balong_lpddr3_udp_dcm_rf, "iocg029", 0x874, 0x0003, 0x00F0)
IOMUX_IOCG(iocg030_balong_lpddr3_udp_dcm_rf, "iocg030", 0x878, 0x0003, 0x00F0)
IOMUX_IOCG(iocg031_balong_lpddr3_udp_dcm_rf, "iocg031", 0x87C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg032_balong_lpddr3_udp_dcm_rf, "iocg032", 0x880, 0x0003, 0x00F0)
IOMUX_IOCG(iocg033_balong_lpddr3_udp_dcm_rf, "iocg033", 0x884, 0x0003, 0x00F0)
IOMUX_IOCG(iocg034_balong_lpddr3_udp_dcm_rf, "iocg034", 0x888, 0x0003, 0x00F0)
IOMUX_IOCG(iocg035_balong_lpddr3_udp_dcm_rf, "iocg035", 0x88C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg036_balong_lpddr3_udp_dcm_rf, "iocg036", 0x890, 0x0003, 0x00F0)
IOMUX_IOCG(iocg037_balong_lpddr3_udp_dcm_rf, "iocg037", 0x894, 0x0003, 0x00F0)
IOMUX_IOCG(iocg038_balong_lpddr3_udp_dcm_rf, "iocg038", 0x898, 0x0003, 0x00F0)
IOMUX_IOCG(iocg039_balong_lpddr3_udp_dcm_rf, "iocg039", 0x89C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg040_balong_lpddr3_udp_dcm_rf, "iocg040", 0x8A0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg041_balong_lpddr3_udp_dcm_rf, "iocg041", 0x8A4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg042_balong_lpddr3_udp_dcm_rf, "iocg042", 0x8A8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg043_balong_lpddr3_udp_dcm_rf, "iocg043", 0x8AC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg044_balong_lpddr3_udp_dcm_rf, "iocg044", 0x8B0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg045_balong_lpddr3_udp_dcm_rf, "iocg045", 0x8B4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg046_balong_lpddr3_udp_dcm_rf, "iocg046", 0x8B8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg047_balong_lpddr3_udp_dcm_rf, "iocg047", 0x8BC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg048_balong_lpddr3_udp_dcm_rf, "iocg048", 0x8C0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg049_balong_lpddr3_udp_dcm_rf, "iocg049", 0x8C4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg050_balong_lpddr3_udp_dcm_rf, "iocg050", 0x8C8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg051_balong_lpddr3_udp_dcm_rf, "iocg051", 0x8CC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg052_balong_lpddr3_udp_dcm_rf, "iocg052", 0x8D0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg053_balong_lpddr3_udp_dcm_rf, "iocg053", 0x8D4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg054_balong_lpddr3_udp_dcm_rf, "iocg054", 0x8D8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg055_balong_lpddr3_udp_dcm_rf, "iocg055", 0x8DC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg056_balong_lpddr3_udp_dcm_rf, "iocg056", 0x8E0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg057_balong_lpddr3_udp_dcm_rf, "iocg057", 0x8E4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg058_balong_lpddr3_udp_dcm_rf, "iocg058", 0x8E8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg059_balong_lpddr3_udp_dcm_rf, "iocg059", 0x8EC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg060_balong_lpddr3_udp_dcm_rf, "iocg060", 0x8F0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg061_balong_lpddr3_udp_dcm_rf, "iocg061", 0x8F4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg062_balong_lpddr3_udp_dcm_rf, "iocg062", 0x8F8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg063_balong_lpddr3_udp_dcm_rf, "iocg063", 0x8FC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg064_balong_lpddr3_udp_dcm_rf, "iocg064", 0x900, 0x0003, 0x00F0)
IOMUX_IOCG(iocg065_balong_lpddr3_udp_dcm_rf, "iocg065", 0x904, 0x0003, 0x00F0)
IOMUX_IOCG(iocg066_balong_lpddr3_udp_dcm_rf, "iocg066", 0x908, 0x0003, 0x00F0)
IOMUX_IOCG(iocg067_balong_lpddr3_udp_dcm_rf, "iocg067", 0x90C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg068_balong_lpddr3_udp_dcm_rf, "iocg068", 0x910, 0x0003, 0x00F0)
IOMUX_IOCG(iocg069_balong_lpddr3_udp_dcm_rf, "iocg069", 0x914, 0x0003, 0x00F0)
IOMUX_IOCG(iocg070_balong_lpddr3_udp_dcm_rf, "iocg070", 0x918, 0x0003, 0x00F0)
IOMUX_IOCG(iocg071_balong_lpddr3_udp_dcm_rf, "iocg071", 0x91C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg072_balong_lpddr3_udp_dcm_rf, "iocg072", 0x920, 0x0003, 0x00F0)
IOMUX_IOCG(iocg073_balong_lpddr3_udp_dcm_rf, "iocg073", 0x924, 0x0003, 0x00F0)
IOMUX_IOCG(iocg074_balong_lpddr3_udp_dcm_rf, "iocg074", 0x928, 0x0003, 0x00F0)
IOMUX_IOCG(iocg075_balong_lpddr3_udp_dcm_rf, "iocg075", 0x92C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg076_balong_lpddr3_udp_dcm_rf, "iocg076", 0x930, 0x0003, 0x00F0)
IOMUX_IOCG(iocg077_balong_lpddr3_udp_dcm_rf, "iocg077", 0x934, 0x0003, 0x00F0)
IOMUX_IOCG(iocg078_balong_lpddr3_udp_dcm_rf, "iocg078", 0x938, 0x0003, 0x00F0)
IOMUX_IOCG(iocg079_balong_lpddr3_udp_dcm_rf, "iocg079", 0x93C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg080_balong_lpddr3_udp_dcm_rf, "iocg080", 0x940, 0x0003, 0x00F0)
IOMUX_IOCG(iocg081_balong_lpddr3_udp_dcm_rf, "iocg081", 0x944, 0x0003, 0x00F0)
IOMUX_IOCG(iocg082_balong_lpddr3_udp_dcm_rf, "iocg082", 0x948, 0x0003, 0x00F0)
IOMUX_IOCG(iocg083_balong_lpddr3_udp_dcm_rf, "iocg083", 0x94C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg084_balong_lpddr3_udp_dcm_rf, "iocg084", 0x950, 0x0003, 0x00F0)
IOMUX_IOCG(iocg085_balong_lpddr3_udp_dcm_rf, "iocg085", 0x954, 0x0003, 0x00F0)
IOMUX_IOCG(iocg086_balong_lpddr3_udp_dcm_rf, "iocg086", 0x958, 0x0003, 0x00F0)
IOMUX_IOCG(iocg087_balong_lpddr3_udp_dcm_rf, "iocg087", 0x95C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg088_balong_lpddr3_udp_dcm_rf, "iocg088", 0x960, 0x0003, 0x00F0)
IOMUX_IOCG(iocg089_balong_lpddr3_udp_dcm_rf, "iocg089", 0x964, 0x0003, 0x00F0)
IOMUX_IOCG(iocg090_balong_lpddr3_udp_dcm_rf, "iocg090", 0x968, 0x0003, 0x00F0)
IOMUX_IOCG(iocg091_balong_lpddr3_udp_dcm_rf, "iocg091", 0x96C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg092_balong_lpddr3_udp_dcm_rf, "iocg092", 0x970, 0x0003, 0x00F0)
IOMUX_IOCG(iocg093_balong_lpddr3_udp_dcm_rf, "iocg093", 0x974, 0x0003, 0x00F0)
IOMUX_IOCG(iocg094_balong_lpddr3_udp_dcm_rf, "iocg094", 0x978, 0x0003, 0x00F0)
IOMUX_IOCG(iocg095_balong_lpddr3_udp_dcm_rf, "iocg095", 0x97C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg096_balong_lpddr3_udp_dcm_rf, "iocg096", 0x980, 0x0003, 0x00F0)
IOMUX_IOCG(iocg097_balong_lpddr3_udp_dcm_rf, "iocg097", 0x984, 0x0003, 0x00F0)
IOMUX_IOCG(iocg098_balong_lpddr3_udp_dcm_rf, "iocg098", 0x988, 0x0003, 0x00F0)
IOMUX_IOCG(iocg099_balong_lpddr3_udp_dcm_rf, "iocg099", 0x98C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg100_balong_lpddr3_udp_dcm_rf, "iocg100", 0x990, 0x0003, 0x00F0)
IOMUX_IOCG(iocg101_balong_lpddr3_udp_dcm_rf, "iocg101", 0x994, 0x0003, 0x00F0)
IOMUX_IOCG(iocg102_balong_lpddr3_udp_dcm_rf, "iocg102", 0x998, 0x0003, 0x00F0)
IOMUX_IOCG(iocg103_balong_lpddr3_udp_dcm_rf, "iocg103", 0x99C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg104_balong_lpddr3_udp_dcm_rf, "iocg104", 0x9A0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg105_balong_lpddr3_udp_dcm_rf, "iocg105", 0x9A4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg106_balong_lpddr3_udp_dcm_rf, "iocg106", 0x9A8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg107_balong_lpddr3_udp_dcm_rf, "iocg107", 0x9AC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg108_balong_lpddr3_udp_dcm_rf, "iocg108", 0x9B0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg109_balong_lpddr3_udp_dcm_rf, "iocg109", 0x9B4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg110_balong_lpddr3_udp_dcm_rf, "iocg110", 0x9B8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg111_balong_lpddr3_udp_dcm_rf, "iocg111", 0x9BC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg112_balong_lpddr3_udp_dcm_rf, "iocg112", 0x9C0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg113_balong_lpddr3_udp_dcm_rf, "iocg113", 0x9C4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg114_balong_lpddr3_udp_dcm_rf, "iocg114", 0x9C8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg115_balong_lpddr3_udp_dcm_rf, "iocg115", 0x9CC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg116_balong_lpddr3_udp_dcm_rf, "iocg116", 0x9D0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg117_balong_lpddr3_udp_dcm_rf, "iocg117", 0x9D4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg118_balong_lpddr3_udp_dcm_rf, "iocg118", 0x9D8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg119_balong_lpddr3_udp_dcm_rf, "iocg119", 0x9DC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg120_balong_lpddr3_udp_dcm_rf, "iocg120", 0x9E0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg121_balong_lpddr3_udp_dcm_rf, "iocg121", 0x9E4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg122_balong_lpddr3_udp_dcm_rf, "iocg122", 0x9E8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg123_balong_lpddr3_udp_dcm_rf, "iocg123", 0x9EC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg124_balong_lpddr3_udp_dcm_rf, "iocg124", 0x9F0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg125_balong_lpddr3_udp_dcm_rf, "iocg125", 0x9F4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg126_balong_lpddr3_udp_dcm_rf, "iocg126", 0x9F8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg127_balong_lpddr3_udp_dcm_rf, "iocg127", 0x9FC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg128_balong_lpddr3_udp_dcm_rf, "iocg128", 0xA00, 0x0003, 0x00F0)
IOMUX_IOCG(iocg129_balong_lpddr3_udp_dcm_rf, "iocg129", 0xA04, 0x0003, 0x00F0)
IOMUX_IOCG(iocg130_balong_lpddr3_udp_dcm_rf, "iocg130", 0xA08, 0x0003, 0x00F0)
IOMUX_IOCG(iocg131_balong_lpddr3_udp_dcm_rf, "iocg131", 0xA0C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg132_balong_lpddr3_udp_dcm_rf, "iocg132", 0xA10, 0x0003, 0x00F0)
IOMUX_IOCG(iocg133_balong_lpddr3_udp_dcm_rf, "iocg133", 0xA14, 0x0003, 0x00F0)
IOMUX_IOCG(iocg134_balong_lpddr3_udp_dcm_rf, "iocg134", 0xA18, 0x0003, 0x00F0)
IOMUX_IOCG(iocg135_balong_lpddr3_udp_dcm_rf, "iocg135", 0xA1C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg136_balong_lpddr3_udp_dcm_rf, "iocg136", 0xA20, 0x0003, 0x00F0)
IOMUX_IOCG(iocg137_balong_lpddr3_udp_dcm_rf, "iocg137", 0xA24, 0x0003, 0x00F0)
IOMUX_IOCG(iocg138_balong_lpddr3_udp_dcm_rf, "iocg138", 0xA28, 0x0003, 0x00F0)
IOMUX_IOCG(iocg139_balong_lpddr3_udp_dcm_rf, "iocg139", 0xA2C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg140_balong_lpddr3_udp_dcm_rf, "iocg140", 0xA30, 0x0003, 0x00F0)
IOMUX_IOCG(iocg141_balong_lpddr3_udp_dcm_rf, "iocg141", 0xA34, 0x0003, 0x00F0)
IOMUX_IOCG(iocg142_balong_lpddr3_udp_dcm_rf, "iocg142", 0xA38, 0x0003, 0x00F0)
IOMUX_IOCG(iocg143_balong_lpddr3_udp_dcm_rf, "iocg143", 0xA3C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg144_balong_lpddr3_udp_dcm_rf, "iocg144", 0xA40, 0x0003, 0x00F0)
IOMUX_IOCG(iocg145_balong_lpddr3_udp_dcm_rf, "iocg145", 0xA44, 0x0003, 0x00F0)
IOMUX_IOCG(iocg146_balong_lpddr3_udp_dcm_rf, "iocg146", 0xA48, 0x0003, 0x00F0)
IOMUX_IOCG(iocg147_balong_lpddr3_udp_dcm_rf, "iocg147", 0xA4C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg148_balong_lpddr3_udp_dcm_rf, "iocg148", 0xA50, 0x0003, 0x00F0)
IOMUX_IOCG(iocg149_balong_lpddr3_udp_dcm_rf, "iocg149", 0xA54, 0x0003, 0x00F0)
IOMUX_IOCG(iocg150_balong_lpddr3_udp_dcm_rf, "iocg150", 0xA58, 0x0003, 0x00F0)
IOMUX_IOCG(iocg151_balong_lpddr3_udp_dcm_rf, "iocg151", 0xA5C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg152_balong_lpddr3_udp_dcm_rf, "iocg152", 0xA60, 0x0003, 0x00F0)
IOMUX_IOCG(iocg153_balong_lpddr3_udp_dcm_rf, "iocg153", 0xA64, 0x0003, 0x00F0)
IOMUX_IOCG(iocg154_balong_lpddr3_udp_dcm_rf, "iocg154", 0xA68, 0x0003, 0x00F0)
IOMUX_IOCG(iocg155_balong_lpddr3_udp_dcm_rf, "iocg155", 0xA6C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg156_balong_lpddr3_udp_dcm_rf, "iocg156", 0xA70, 0x0003, 0x00F0)
IOMUX_IOCG(iocg157_balong_lpddr3_udp_dcm_rf, "iocg157", 0xA74, 0x0003, 0x00F0)
IOMUX_IOCG(iocg158_balong_lpddr3_udp_dcm_rf, "iocg158", 0xA78, 0x0003, 0x00F0)
IOMUX_IOCG(iocg159_balong_lpddr3_udp_dcm_rf, "iocg159", 0xA7C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg160_balong_lpddr3_udp_dcm_rf, "iocg160", 0xA80, 0x0003, 0x00F0)
IOMUX_IOCG(iocg161_balong_lpddr3_udp_dcm_rf, "iocg161", 0xA84, 0x0003, 0x00F0)
IOMUX_IOCG(iocg162_balong_lpddr3_udp_dcm_rf, "iocg162", 0xA88, 0x0003, 0x00F0)
IOMUX_IOCG(iocg163_balong_lpddr3_udp_dcm_rf, "iocg163", 0xA8C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg164_balong_lpddr3_udp_dcm_rf, "iocg164", 0xA90, 0x0003, 0x00F0)
IOMUX_IOCG(iocg165_balong_lpddr3_udp_dcm_rf, "iocg165", 0xA94, 0x0003, 0x00F0)
IOMUX_IOCG(iocg166_balong_lpddr3_udp_dcm_rf, "iocg166", 0xA98, 0x0003, 0x00F0)
IOMUX_IOCG(iocg167_balong_lpddr3_udp_dcm_rf, "iocg167", 0xA9C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg168_balong_lpddr3_udp_dcm_rf, "iocg168", 0xAA0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg169_balong_lpddr3_udp_dcm_rf, "iocg169", 0xAA4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg170_balong_lpddr3_udp_dcm_rf, "iocg170", 0xAA8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg171_balong_lpddr3_udp_dcm_rf, "iocg171", 0xAAC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg172_balong_lpddr3_udp_dcm_rf, "iocg172", 0xAB0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg173_balong_lpddr3_udp_dcm_rf, "iocg173", 0xAB4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg174_balong_lpddr3_udp_dcm_rf, "iocg174", 0xAB8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg175_balong_lpddr3_udp_dcm_rf, "iocg175", 0xABC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg176_balong_lpddr3_udp_dcm_rf, "iocg176", 0xAC0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg177_balong_lpddr3_udp_dcm_rf, "iocg177", 0xAC4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg178_balong_lpddr3_udp_dcm_rf, "iocg178", 0xAC8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg179_balong_lpddr3_udp_dcm_rf, "iocg179", 0xACC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg180_balong_lpddr3_udp_dcm_rf, "iocg180", 0xAD0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg181_balong_lpddr3_udp_dcm_rf, "iocg181", 0xAD4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg182_balong_lpddr3_udp_dcm_rf, "iocg182", 0xAD8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg183_balong_lpddr3_udp_dcm_rf, "iocg183", 0xADC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg184_balong_lpddr3_udp_dcm_rf, "iocg184", 0xAE0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg185_balong_lpddr3_udp_dcm_rf, "iocg185", 0xAE4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg186_balong_lpddr3_udp_dcm_rf, "iocg186", 0xAE8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg187_balong_lpddr3_udp_dcm_rf, "iocg187", 0xAEC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg188_balong_lpddr3_udp_dcm_rf, "iocg188", 0xAF0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg189_balong_lpddr3_udp_dcm_rf, "iocg189", 0xAF4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg190_balong_lpddr3_udp_dcm_rf, "iocg190", 0xAF8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg191_balong_lpddr3_udp_dcm_rf, "iocg191", 0xAFC, 0x0003, 0x00F0)


/*define the iocg*/
IOMUX_PIN(I2C0_SCL_BALONG_LPDDR3_UDP_DCM_RF, "I2C0_SCL", FUNC0, NOPULL, LEVEL0, &iomg071_balong_lpddr3_udp_dcm_rf, &iocg071_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C0_SDA_BALONG_LPDDR3_UDP_DCM_RF, "I2C0_SDA", FUNC0, NOPULL, LEVEL0, &iomg072_balong_lpddr3_udp_dcm_rf, &iocg072_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C1_SCL_BALONG_LPDDR3_UDP_DCM_RF, "I2C1_SCL", FUNC0, NOPULL, LEVEL0, &iomg073_balong_lpddr3_udp_dcm_rf, &iocg073_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C1_SDA_BALONG_LPDDR3_UDP_DCM_RF, "I2C1_SDA", FUNC0, NOPULL, LEVEL0, &iomg074_balong_lpddr3_udp_dcm_rf, &iocg074_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C2_SCL_BALONG_LPDDR3_UDP_DCM_RF, "I2C2_SCL", FUNC0, NOPULL, LEVEL0, &iomg075_balong_lpddr3_udp_dcm_rf, &iocg075_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C2_SDA_BALONG_LPDDR3_UDP_DCM_RF, "I2C2_SDA", FUNC0, NOPULL, LEVEL0, &iomg076_balong_lpddr3_udp_dcm_rf, &iocg076_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C3_SCL_BALONG_LPDDR3_UDP_DCM_RF, "I2C3_SCL", FUNC0, NOPULL, LEVEL0, &iomg077_balong_lpddr3_udp_dcm_rf, &iocg077_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2C3_SDA_BALONG_LPDDR3_UDP_DCM_RF, "I2C3_SDA", FUNC0, NOPULL, LEVEL0, &iomg078_balong_lpddr3_udp_dcm_rf, &iocg078_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO0", FUNC0, NOPULL, LEVEL0, &iomg008_balong_lpddr3_udp_dcm_rf, &iocg008_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO2_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO2", FUNC0, NOPULL, LEVEL0, &iomg010_balong_lpddr3_udp_dcm_rf, &iocg010_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO3_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO3", FUNC2, NOPULL, LEVEL0, &iomg011_balong_lpddr3_udp_dcm_rf, &iocg011_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_RESETB0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_RESETB0", FUNC0, NOPULL, LEVEL0, &iomg016_balong_lpddr3_udp_dcm_rf, &iocg016_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_CCLK0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_CCLK0", FUNC0, NOPULL, LEVEL0, &iomg014_balong_lpddr3_udp_dcm_rf, &iocg014_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_SDA0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_SDA0", FUNC2, PULLDOWN, LEVEL0, &iomg020_balong_lpddr3_udp_dcm_rf, &iocg020_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_SCL0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_SCL0", FUNC2, PULLDOWN, LEVEL0, &iomg021_balong_lpddr3_udp_dcm_rf, &iocg021_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO1", FUNC0, NOPULL, LEVEL0, &iomg009_balong_lpddr3_udp_dcm_rf, &iocg009_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO4_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO4", FUNC2, NOPULL, LEVEL0, &iomg012_balong_lpddr3_udp_dcm_rf, &iocg012_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_RESETB1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_RESETB1", FUNC0, NOPULL, LEVEL0, &iomg017_balong_lpddr3_udp_dcm_rf, &iocg017_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_CCLK1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_CCLK1", FUNC0, NOPULL, LEVEL0, &iomg015_balong_lpddr3_udp_dcm_rf, &iocg015_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_SDA1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_SDA1", FUNC2, PULLDOWN, LEVEL0, &iomg022_balong_lpddr3_udp_dcm_rf, &iocg022_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_SCL1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_SCL1", FUNC2, PULLDOWN, LEVEL0, &iomg023_balong_lpddr3_udp_dcm_rf, &iocg023_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_GPIO5_BALONG_LPDDR3_UDP_DCM_RF, "ISP_GPIO5", FUNC2, NOPULL, LEVEL0, &iomg013_balong_lpddr3_udp_dcm_rf, &iocg013_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_STROBE1_BALONG_LPDDR3_UDP_DCM_RF, "ISP_STROBE1", FUNC2, NOPULL, LEVEL0, &iomg019_balong_lpddr3_udp_dcm_rf, &iocg019_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_0_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_0", FUNC0, NOPULL, LEVEL0, &iomg158_balong_lpddr3_udp_dcm_rf, &iocg158_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(ISP_STROBE0_BALONG_LPDDR3_UDP_DCM_RF, "ISP_STROBE0", FUNC2, PULLDOWN, LEVEL0, &iomg018_balong_lpddr3_udp_dcm_rf, &iocg018_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_2", FUNC0, PULLUP, LEVEL0, &iomg130_balong_lpddr3_udp_dcm_rf, &iocg130_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_3", FUNC0, PULLUP, LEVEL0, &iomg131_balong_lpddr3_udp_dcm_rf, &iocg131_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PWM_OUT1_BALONG_LPDDR3_UDP_DCM_RF, "PWM_OUT1", FUNC2, NOPULL, LEVEL0, &iomg025_balong_lpddr3_udp_dcm_rf, &iocg025_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_6", FUNC0, NOPULL, LEVEL0, &iomg134_balong_lpddr3_udp_dcm_rf, &iocg134_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_7", FUNC4, NOPULL, LEVEL0, &iomg135_balong_lpddr3_udp_dcm_rf, &iocg135_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_4", FUNC0, PULLDOWN, LEVEL0, &iomg132_balong_lpddr3_udp_dcm_rf, &iocg132_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_5", FUNC0, PULLDOWN, LEVEL0, &iomg133_balong_lpddr3_udp_dcm_rf, &iocg133_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_18_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_18_7", FUNC0, NOPULL, LEVEL0, &iomg007_balong_lpddr3_udp_dcm_rf, &iocg191_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART4_CTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART4_CTS_N", FUNC0, NOPULL, LEVEL0, &iomg067_balong_lpddr3_udp_dcm_rf, &iocg067_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART4_RTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART4_RTS_N", FUNC4, PULLUP, LEVEL0, &iomg068_balong_lpddr3_udp_dcm_rf, &iocg068_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART4_RXD_BALONG_LPDDR3_UDP_DCM_RF, "UART4_RXD", FUNC0, NOPULL, LEVEL0, &iomg069_balong_lpddr3_udp_dcm_rf, &iocg069_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART4_TXD_BALONG_LPDDR3_UDP_DCM_RF, "UART4_TXD", FUNC4, PULLUP, LEVEL0, &iomg070_balong_lpddr3_udp_dcm_rf, &iocg070_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_5", FUNC0, NOPULL, LEVEL0, &iomg125_balong_lpddr3_udp_dcm_rf, &iocg125_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_7", FUNC0, NOPULL, LEVEL0, &iomg127_balong_lpddr3_udp_dcm_rf, &iocg127_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_2_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_2_2", FUNC0, NOPULL, LEVEL0, &iomg142_balong_lpddr3_udp_dcm_rf, &iocg142_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_DATA3_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_DATA3", FUNC2, PULLUP, LEVEL0, &iomg095_balong_lpddr3_udp_dcm_rf, &iocg095_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_DATA2_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_DATA2", FUNC2, PULLUP, LEVEL0, &iomg094_balong_lpddr3_udp_dcm_rf, &iocg094_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_DATA1_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_DATA1", FUNC2, PULLUP, LEVEL0, &iomg093_balong_lpddr3_udp_dcm_rf, &iocg093_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_DATA0_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_DATA0", FUNC2, PULLUP, LEVEL0, &iomg092_balong_lpddr3_udp_dcm_rf, &iocg092_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_CMD_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_CMD", FUNC2, PULLUP, LEVEL0, &iomg091_balong_lpddr3_udp_dcm_rf, &iocg091_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SDIO_CLK_BALONG_LPDDR3_UDP_DCM_RF, "SDIO_CLK", FUNC2, NOPULL, LEVEL0, &iomg090_balong_lpddr3_udp_dcm_rf, &iocg090_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_1_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_1_4", FUNC0, PULLDOWN, LEVEL0, &iomg136_balong_lpddr3_udp_dcm_rf, &iocg136_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_1_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_1_5", FUNC0, PULLDOWN, LEVEL0, &iomg137_balong_lpddr3_udp_dcm_rf, &iocg137_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_1_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_1_6", FUNC0, PULLDOWN, LEVEL0, &iomg138_balong_lpddr3_udp_dcm_rf, &iocg138_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_1_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_1_7", FUNC0, PULLDOWN, LEVEL0, &iomg139_balong_lpddr3_udp_dcm_rf, &iocg139_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_2_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_2_0", FUNC0, PULLDOWN, LEVEL0, &iomg140_balong_lpddr3_udp_dcm_rf, &iocg140_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_2_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_2_1", FUNC0, PULLDOWN, LEVEL0, &iomg141_balong_lpddr3_udp_dcm_rf, &iocg141_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_0", FUNC0, PULLDOWN, LEVEL0, &iomg104_balong_lpddr3_udp_dcm_rf, &iocg104_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_1", FUNC0, NOPULL, LEVEL0, &iomg105_balong_lpddr3_udp_dcm_rf, &iocg105_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_1_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_1", FUNC0, NOPULL, LEVEL0, &iomg159_balong_lpddr3_udp_dcm_rf, &iocg159_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART3_CTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART3_CTS_N", FUNC0, NOPULL, LEVEL0, &iomg063_balong_lpddr3_udp_dcm_rf, &iocg063_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART3_RTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART3_RTS_N", FUNC0, NOPULL, LEVEL0, &iomg064_balong_lpddr3_udp_dcm_rf, &iocg064_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART3_RXD_BALONG_LPDDR3_UDP_DCM_RF, "UART3_RXD", FUNC0, NOPULL, LEVEL0, &iomg065_balong_lpddr3_udp_dcm_rf, &iocg065_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART3_TXD_BALONG_LPDDR3_UDP_DCM_RF, "UART3_TXD", FUNC0, NOPULL, LEVEL0, &iomg066_balong_lpddr3_udp_dcm_rf, &iocg066_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPS_CLK_BALONG_LPDDR3_UDP_DCM_RF, "GPS_CLK", FUNC2, NOPULL, LEVEL0, &iomg049_balong_lpddr3_udp_dcm_rf, &iocg049_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_3", FUNC0, NOPULL, LEVEL0, &iomg107_balong_lpddr3_udp_dcm_rf, &iocg107_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_4", FUNC0, NOPULL, LEVEL0, &iomg108_balong_lpddr3_udp_dcm_rf, &iocg108_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(TCXO0_AFC_BALONG_LPDDR3_UDP_DCM_RF, "TCXO0_AFC", FUNC4, PULLDOWN, LEVEL0, &iomg144_balong_lpddr3_udp_dcm_rf, &iocg144_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(TCXO1_AFC_BALONG_LPDDR3_UDP_DCM_RF, "TCXO1_AFC", FUNC4, PULLDOWN, LEVEL0, &iomg145_balong_lpddr3_udp_dcm_rf, &iocg145_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM0_CLK_BALONG_LPDDR3_UDP_DCM_RF, "USIM0_CLK", FUNC0, NOPULL, LEVEL0, &iomg043_balong_lpddr3_udp_dcm_rf, &iocg043_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM0_DATA_BALONG_LPDDR3_UDP_DCM_RF, "USIM0_DATA", FUNC0, NOPULL, LEVEL0, &iomg044_balong_lpddr3_udp_dcm_rf, &iocg044_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM0_RST_BALONG_LPDDR3_UDP_DCM_RF, "USIM0_RST", FUNC0, NOPULL, LEVEL0, &iomg045_balong_lpddr3_udp_dcm_rf, &iocg045_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM1_CLK_BALONG_LPDDR3_UDP_DCM_RF, "USIM1_CLK", FUNC0, NOPULL, LEVEL0, &iomg046_balong_lpddr3_udp_dcm_rf, &iocg046_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM1_DATA_BALONG_LPDDR3_UDP_DCM_RF, "USIM1_DATA", FUNC0, NOPULL, LEVEL0, &iomg047_balong_lpddr3_udp_dcm_rf, &iocg047_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(USIM1_RST_BALONG_LPDDR3_UDP_DCM_RF, "USIM1_RST", FUNC0, NOPULL, LEVEL0, &iomg048_balong_lpddr3_udp_dcm_rf, &iocg048_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_CLK_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_CLK", FUNC0, NOPULL, LEVEL0, &iomg079_balong_lpddr3_udp_dcm_rf, &iocg079_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_CMD_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_CMD", FUNC0, NOPULL, LEVEL0, &iomg080_balong_lpddr3_udp_dcm_rf, &iocg080_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA0_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA0", FUNC0, NOPULL, LEVEL0, &iomg081_balong_lpddr3_udp_dcm_rf, &iocg081_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA1_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA1", FUNC0, NOPULL, LEVEL0, &iomg082_balong_lpddr3_udp_dcm_rf, &iocg082_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA2_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA2", FUNC0, NOPULL, LEVEL0, &iomg083_balong_lpddr3_udp_dcm_rf, &iocg083_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA3_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA3", FUNC0, NOPULL, LEVEL0, &iomg084_balong_lpddr3_udp_dcm_rf, &iocg084_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA4_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA4", FUNC0, NOPULL, LEVEL0, &iomg085_balong_lpddr3_udp_dcm_rf, &iocg085_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA5_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA5", FUNC0, NOPULL, LEVEL0, &iomg086_balong_lpddr3_udp_dcm_rf, &iocg086_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA6_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA6", FUNC0, NOPULL, LEVEL0, &iomg087_balong_lpddr3_udp_dcm_rf, &iocg087_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(EMMC_DATA7_BALONG_LPDDR3_UDP_DCM_RF, "EMMC_DATA7", FUNC0, NOPULL, LEVEL0, &iomg088_balong_lpddr3_udp_dcm_rf, &iocg088_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_2_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_2_3", FUNC4, NOPULL, LEVEL0, &iomg143_balong_lpddr3_udp_dcm_rf, &iocg143_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(BOOT_SEL_BALONG_LPDDR3_UDP_DCM_RF, "BOOT_SEL", FUNC0, PULLUP, LEVEL0, &iomg000_balong_lpddr3_udp_dcm_rf, &iocg000_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_2", FUNC4, PULLDOWN, LEVEL0, &iomg098_balong_lpddr3_udp_dcm_rf, &iocg098_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM1_XCLK_BALONG_LPDDR3_UDP_DCM_RF, "PCM1_XCLK", FUNC0, NOPULL, LEVEL0, &iomg034_balong_lpddr3_udp_dcm_rf, &iocg034_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM1_XFS_BALONG_LPDDR3_UDP_DCM_RF, "PCM1_XFS", FUNC0, NOPULL, LEVEL0, &iomg035_balong_lpddr3_udp_dcm_rf, &iocg035_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM1_DI_BALONG_LPDDR3_UDP_DCM_RF, "PCM1_DI", FUNC0, NOPULL, LEVEL0, &iomg036_balong_lpddr3_udp_dcm_rf, &iocg036_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM1_DO_BALONG_LPDDR3_UDP_DCM_RF, "PCM1_DO", FUNC0, NOPULL, LEVEL0, &iomg037_balong_lpddr3_udp_dcm_rf, &iocg037_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_1", FUNC0, NOPULL, LEVEL0, &iomg097_balong_lpddr3_udp_dcm_rf, &iocg097_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(HKADC_SSI_BALONG_LPDDR3_UDP_DCM_RF, "HKADC_SSI", FUNC0, PULLDOWN, LEVEL0, &iomg050_balong_lpddr3_udp_dcm_rf, &iocg050_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(AUX_SSI0_BALONG_LPDDR3_UDP_DCM_RF, "AUX_SSI0", FUNC0, PULLDOWN, LEVEL0, &iomg051_balong_lpddr3_udp_dcm_rf, &iocg051_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(AUX_SSI1_BALONG_LPDDR3_UDP_DCM_RF, "AUX_SSI1", FUNC0, PULLDOWN, LEVEL0, &iomg052_balong_lpddr3_udp_dcm_rf, &iocg052_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_0", FUNC2, NOPULL, LEVEL0, &iomg096_balong_lpddr3_udp_dcm_rf, &iocg189_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART0_RXD_BALONG_LPDDR3_UDP_DCM_RF, "UART0_RXD", FUNC0, NOPULL, LEVEL0, &iomg053_balong_lpddr3_udp_dcm_rf, &iocg053_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART0_TXD_BALONG_LPDDR3_UDP_DCM_RF, "UART0_TXD", FUNC0, NOPULL, LEVEL0, &iomg054_balong_lpddr3_udp_dcm_rf, &iocg054_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_7", FUNC6, NOPULL, LEVEL0, &iomg119_balong_lpddr3_udp_dcm_rf, &iocg119_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_0", FUNC6, NOPULL, LEVEL0, &iomg120_balong_lpddr3_udp_dcm_rf, &iocg120_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_1", FUNC6, NOPULL, LEVEL0, &iomg121_balong_lpddr3_udp_dcm_rf, &iocg121_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_2", FUNC6, NOPULL, LEVEL0, &iomg122_balong_lpddr3_udp_dcm_rf, &iocg122_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_2", FUNC0, NOPULL, LEVEL0, &iomg106_balong_lpddr3_udp_dcm_rf, &iocg106_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_3", FUNC0, NOPULL, LEVEL0, &iomg099_balong_lpddr3_udp_dcm_rf, &iocg099_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_0", FUNC0, NOPULL, LEVEL0, &iomg128_balong_lpddr3_udp_dcm_rf, &iocg128_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_4_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_4_1", FUNC0, NOPULL, LEVEL0, &iomg129_balong_lpddr3_udp_dcm_rf, &iocg129_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_MIPI_CLK0_BALONG_LPDDR3_UDP_DCM_RF, "RF_MIPI_CLK0", FUNC0, NOPULL, LEVEL0, &iomg154_balong_lpddr3_udp_dcm_rf, &iocg154_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_MIPI_DATA0_BALONG_LPDDR3_UDP_DCM_RF, "RF_MIPI_DATA0", FUNC0, PULLDOWN, LEVEL0, &iomg155_balong_lpddr3_udp_dcm_rf, &iocg155_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(APT_PDM0_BALONG_LPDDR3_UDP_DCM_RF, "APT_PDM0", FUNC0, NOPULL, LEVEL0, &iomg089_balong_lpddr3_udp_dcm_rf, &iocg190_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_5", FUNC0, PULLDOWN, LEVEL0, &iomg117_balong_lpddr3_udp_dcm_rf, &iocg117_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_6", FUNC0, PULLDOWN, LEVEL0, &iomg118_balong_lpddr3_udp_dcm_rf, &iocg118_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_TCVR_ON0_BALONG_LPDDR3_UDP_DCM_RF, "RF_TCVR_ON0", FUNC0, NOPULL, LEVEL0, &iomg150_balong_lpddr3_udp_dcm_rf, &iocg150_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_TCVR_ON1_BALONG_LPDDR3_UDP_DCM_RF, "RF_TCVR_ON1", FUNC0, NOPULL, LEVEL0, &iomg151_balong_lpddr3_udp_dcm_rf, &iocg151_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_TX_EN0_BALONG_LPDDR3_UDP_DCM_RF, "RF_TX_EN0", FUNC0, NOPULL, LEVEL0, &iomg152_balong_lpddr3_udp_dcm_rf, &iocg152_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_TX_EN1_BALONG_LPDDR3_UDP_DCM_RF, "RF_TX_EN1", FUNC0, NOPULL, LEVEL0, &iomg153_balong_lpddr3_udp_dcm_rf, &iocg153_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_MIPI_CLK1_BALONG_LPDDR3_UDP_DCM_RF, "RF_MIPI_CLK1", FUNC0, NOPULL, LEVEL0, &iomg156_balong_lpddr3_udp_dcm_rf, &iocg156_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_MIPI_DATA1_BALONG_LPDDR3_UDP_DCM_RF, "RF_MIPI_DATA1", FUNC0, PULLDOWN, LEVEL0, &iomg157_balong_lpddr3_udp_dcm_rf, &iocg157_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_SSI0_BALONG_LPDDR3_UDP_DCM_RF, "RF_SSI0", FUNC0, PULLDOWN, LEVEL0, &iomg148_balong_lpddr3_udp_dcm_rf, &iocg148_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_SSI1_BALONG_LPDDR3_UDP_DCM_RF, "RF_SSI1", FUNC0, PULLDOWN, LEVEL0, &iomg149_balong_lpddr3_udp_dcm_rf, &iocg149_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_2_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_2", FUNC0, NOPULL, LEVEL0, &iomg160_balong_lpddr3_udp_dcm_rf, &iocg160_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_3_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_3", FUNC0, NOPULL, LEVEL0, &iomg161_balong_lpddr3_udp_dcm_rf, &iocg161_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_4_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_4", FUNC0, NOPULL, LEVEL0, &iomg162_balong_lpddr3_udp_dcm_rf, &iocg162_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_5_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_5", FUNC0, NOPULL, LEVEL0, &iomg163_balong_lpddr3_udp_dcm_rf, &iocg163_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_6_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_6", FUNC0, NOPULL, LEVEL0, &iomg164_balong_lpddr3_udp_dcm_rf, &iocg164_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_7_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_7", FUNC0, NOPULL, LEVEL0, &iomg165_balong_lpddr3_udp_dcm_rf, &iocg165_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_8_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_8", FUNC0, NOPULL, LEVEL0, &iomg166_balong_lpddr3_udp_dcm_rf, &iocg166_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_9_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_9", FUNC0, NOPULL, LEVEL0, &iomg167_balong_lpddr3_udp_dcm_rf, &iocg167_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_10_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_10", FUNC0, NOPULL, LEVEL0, &iomg168_balong_lpddr3_udp_dcm_rf, &iocg168_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_11_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_11", FUNC0, NOPULL, LEVEL0, &iomg169_balong_lpddr3_udp_dcm_rf, &iocg169_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_12_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_12", FUNC0, NOPULL, LEVEL0, &iomg170_balong_lpddr3_udp_dcm_rf, &iocg170_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_13_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_13", FUNC0, NOPULL, LEVEL0, &iomg171_balong_lpddr3_udp_dcm_rf, &iocg171_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_14_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_14", FUNC0, NOPULL, LEVEL0, &iomg172_balong_lpddr3_udp_dcm_rf, &iocg172_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_15_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_15", FUNC0, NOPULL, LEVEL0, &iomg173_balong_lpddr3_udp_dcm_rf, &iocg173_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_16_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_16", FUNC0, NOPULL, LEVEL0, &iomg174_balong_lpddr3_udp_dcm_rf, &iocg184_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_17_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_17", FUNC0, NOPULL, LEVEL0, &iomg175_balong_lpddr3_udp_dcm_rf, &iocg185_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_18_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_18", FUNC0, NOPULL, LEVEL0, &iomg176_balong_lpddr3_udp_dcm_rf, &iocg186_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_19_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_19", FUNC0, NOPULL, LEVEL0, &iomg177_balong_lpddr3_udp_dcm_rf, &iocg187_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_20_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_20", FUNC0, NOPULL, LEVEL0, &iomg178_balong_lpddr3_udp_dcm_rf, &iocg188_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_21_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_21", FUNC0, NOPULL, LEVEL0, &iomg179_balong_lpddr3_udp_dcm_rf, &iocg174_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_22_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_22", FUNC0, NOPULL, LEVEL0, &iomg180_balong_lpddr3_udp_dcm_rf, &iocg175_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_23_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_23", FUNC0, NOPULL, LEVEL0, &iomg181_balong_lpddr3_udp_dcm_rf, &iocg176_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_24_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_24", FUNC0, NOPULL, LEVEL0, &iomg182_balong_lpddr3_udp_dcm_rf, &iocg177_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_25_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_25", FUNC0, NOPULL, LEVEL0, &iomg183_balong_lpddr3_udp_dcm_rf, &iocg178_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_26_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_26", FUNC0, NOPULL, LEVEL0, &iomg184_balong_lpddr3_udp_dcm_rf, &iocg179_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_27_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_27", FUNC0, NOPULL, LEVEL0, &iomg185_balong_lpddr3_udp_dcm_rf, &iocg180_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_28_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_28", FUNC0, NOPULL, LEVEL0, &iomg186_balong_lpddr3_udp_dcm_rf, &iocg181_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_29_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_29", FUNC0, NOPULL, LEVEL0, &iomg187_balong_lpddr3_udp_dcm_rf, &iocg182_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(RF_GPIO_30_BALONG_LPDDR3_UDP_DCM_RF, "RF_GPIO_30", FUNC0, NOPULL, LEVEL0, &iomg188_balong_lpddr3_udp_dcm_rf, &iocg183_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_CLK_BALONG_LPDDR3_UDP_DCM_RF, "SD_CLK", FUNC0, NOPULL, LEVEL0, &iomg001_balong_lpddr3_udp_dcm_rf, &iocg001_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_CMD_BALONG_LPDDR3_UDP_DCM_RF, "SD_CMD", FUNC0, NOPULL, LEVEL0, &iomg002_balong_lpddr3_udp_dcm_rf, &iocg002_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_DATA0_BALONG_LPDDR3_UDP_DCM_RF, "SD_DATA0", FUNC0, NOPULL, LEVEL0, &iomg003_balong_lpddr3_udp_dcm_rf, &iocg003_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_DATA1_BALONG_LPDDR3_UDP_DCM_RF, "SD_DATA1", FUNC0, NOPULL, LEVEL0, &iomg004_balong_lpddr3_udp_dcm_rf, &iocg004_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_DATA2_BALONG_LPDDR3_UDP_DCM_RF, "SD_DATA2", FUNC0, NOPULL, LEVEL0, &iomg005_balong_lpddr3_udp_dcm_rf, &iocg005_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(SD_DATA3_BALONG_LPDDR3_UDP_DCM_RF, "SD_DATA3", FUNC0, NOPULL, LEVEL0, &iomg006_balong_lpddr3_udp_dcm_rf, &iocg006_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART1_RTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART1_RTS_N", FUNC2, NOPULL, LEVEL0, &iomg056_balong_lpddr3_udp_dcm_rf, &iocg056_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART1_RXD_BALONG_LPDDR3_UDP_DCM_RF, "UART1_RXD", FUNC2, NOPULL, LEVEL0, &iomg057_balong_lpddr3_udp_dcm_rf, &iocg057_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_6", FUNC0, NOPULL, LEVEL0, &iomg126_balong_lpddr3_udp_dcm_rf, &iocg126_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_4", FUNC6, NOPULL, LEVEL0, &iomg100_balong_lpddr3_udp_dcm_rf, &iocg100_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_5", FUNC6, NOPULL, LEVEL0, &iomg101_balong_lpddr3_udp_dcm_rf, &iocg101_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_6", FUNC6, NOPULL, LEVEL0, &iomg102_balong_lpddr3_udp_dcm_rf, &iocg102_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_5_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_5_7", FUNC6, NOPULL, LEVEL0, &iomg103_balong_lpddr3_udp_dcm_rf, &iocg103_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART1_CTS_N_BALONG_LPDDR3_UDP_DCM_RF, "UART1_CTS_N", FUNC2, NOPULL, LEVEL0, &iomg055_balong_lpddr3_udp_dcm_rf, &iocg055_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_3", FUNC0, NOPULL, LEVEL0, &iomg123_balong_lpddr3_udp_dcm_rf, &iocg123_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_15_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_15_4", FUNC0, NOPULL, LEVEL0, &iomg124_balong_lpddr3_udp_dcm_rf, &iocg124_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART1_TXD_BALONG_LPDDR3_UDP_DCM_RF, "UART1_TXD", FUNC2, NOPULL, LEVEL0, &iomg058_balong_lpddr3_udp_dcm_rf, &iocg058_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART2_RXD_BALONG_LPDDR3_UDP_DCM_RF, "UART2_RXD", FUNC0, NOPULL, LEVEL0, &iomg061_balong_lpddr3_udp_dcm_rf, &iocg061_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(UART2_TXD_BALONG_LPDDR3_UDP_DCM_RF, "UART2_TXD", FUNC0, NOPULL, LEVEL0, &iomg062_balong_lpddr3_udp_dcm_rf, &iocg062_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2S_XCLK_BALONG_LPDDR3_UDP_DCM_RF, "I2S_XCLK", FUNC0, NOPULL, LEVEL0, &iomg026_balong_lpddr3_udp_dcm_rf, &iocg026_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2S_XFS_BALONG_LPDDR3_UDP_DCM_RF, "I2S_XFS", FUNC0, NOPULL, LEVEL0, &iomg027_balong_lpddr3_udp_dcm_rf, &iocg027_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2S_DI_BALONG_LPDDR3_UDP_DCM_RF, "I2S_DI", FUNC0, NOPULL, LEVEL0, &iomg028_balong_lpddr3_udp_dcm_rf, &iocg028_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(I2S_DO_BALONG_LPDDR3_UDP_DCM_RF, "I2S_DO", FUNC0, NOPULL, LEVEL0, &iomg029_balong_lpddr3_udp_dcm_rf, &iocg029_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM0_XCLK_BALONG_LPDDR3_UDP_DCM_RF, "PCM0_XCLK", FUNC0, NOPULL, LEVEL0, &iomg030_balong_lpddr3_udp_dcm_rf, &iocg030_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM0_XFS_BALONG_LPDDR3_UDP_DCM_RF, "PCM0_XFS", FUNC0, NOPULL, LEVEL0, &iomg031_balong_lpddr3_udp_dcm_rf, &iocg031_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM0_DI_BALONG_LPDDR3_UDP_DCM_RF, "PCM0_DI", FUNC0, NOPULL, LEVEL0, &iomg032_balong_lpddr3_udp_dcm_rf, &iocg032_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(PCM0_DO_BALONG_LPDDR3_UDP_DCM_RF, "PCM0_DO", FUNC0, NOPULL, LEVEL0, &iomg033_balong_lpddr3_udp_dcm_rf, &iocg033_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(TS_ERR_BALONG_LPDDR3_UDP_DCM_RF, "TS_ERR", FUNC1, PULLDOWN, LEVEL0, &iomg042_balong_lpddr3_udp_dcm_rf, &iocg042_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_5_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_5", FUNC0, NOPULL, LEVEL0, &iomg109_balong_lpddr3_udp_dcm_rf, &iocg109_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_6_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_6", FUNC0, PULLDOWN, LEVEL0, &iomg110_balong_lpddr3_udp_dcm_rf, &iocg110_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_3_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_3", FUNC0, NOPULL, LEVEL0, &iomg115_balong_lpddr3_udp_dcm_rf, &iocg115_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_6_7_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_6_7", FUNC0, NOPULL, LEVEL0, &iomg111_balong_lpddr3_udp_dcm_rf, &iocg111_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_0_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_0", FUNC0, NOPULL, LEVEL0, &iomg112_balong_lpddr3_udp_dcm_rf, &iocg112_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_1_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_1", FUNC0, NOPULL, LEVEL0, &iomg113_balong_lpddr3_udp_dcm_rf, &iocg113_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_2_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_2", FUNC0, NOPULL, LEVEL0, &iomg114_balong_lpddr3_udp_dcm_rf, &iocg114_balong_lpddr3_udp_dcm_rf)
IOMUX_PIN(GPIO_7_4_BALONG_LPDDR3_UDP_DCM_RF, "GPIO_7_4", FUNC0, NOPULL, LEVEL0, &iomg116_balong_lpddr3_udp_dcm_rf, &iocg116_balong_lpddr3_udp_dcm_rf)


/*pin table*/
static struct iomux_pin_table pin_config_table_balong_lpddr3_udp_dcm_rf[] = {
    PIN_TABLE("i2c0_scl", &I2C0_SCL_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c0_sda", &I2C0_SDA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c1_scl", &I2C1_SCL_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c1_sda", &I2C1_SDA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c2_scl", &I2C2_SCL_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c2_sda", &I2C2_SDA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c3_scl", &I2C3_SCL_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("i2c3_sda", &I2C3_SDA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_mcam_pwdn", &ISP_GPIO0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_mcam_vcm_pwdn", &ISP_GPIO2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_mcam_id", &ISP_GPIO3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_mcam_reset", &ISP_RESETB0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_isp_mclk", &ISP_CCLK0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_isp_sda0", &ISP_SDA0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("mcamera_isp_scl0", &ISP_SCL0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_scam_pwdn", &ISP_GPIO1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_scam_id", &ISP_GPIO4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_scam_reset", &ISP_RESETB1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_isp_mclk", &ISP_CCLK1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_isp_sda1", &ISP_SDA1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("scamera_isp_scl1", &ISP_SCL1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("flash_strobe", &ISP_GPIO5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("flash_rst_n", &ISP_STROBE1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("flash_mask", &RF_GPIO_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("flash_isp_strobe0", &ISP_STROBE0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("key_up", &GPIO_4_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("key_down", &GPIO_4_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("lcd_drv_en", &PWM_OUT1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("lcd_rst_n", &GPIO_4_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("lcd_te0", &GPIO_4_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("lcd_id0", &GPIO_4_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("lcd_id1", &GPIO_4_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("tp_rst_n", &GPIO_18_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_uart4_cts_n", &UART4_CTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_uart4_rts_n", &UART4_RTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_uart4_rxd", &UART4_RXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_uart4_txd", &UART4_TXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_en", &GPIO_15_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("bt_ap_wakeup_bt", &GPIO_15_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_en", &GPIO_2_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_data3", &SDIO_DATA3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_data2", &SDIO_DATA2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_data1", &SDIO_DATA1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_data0", &SDIO_DATA0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_cmd", &SDIO_CMD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_sdio_clk", &SDIO_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_bt_priority", &GPIO_1_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_bt_tx_active", &GPIO_1_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_lte_frame_sync", &GPIO_1_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_lte_rx_active", &GPIO_1_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_lte_tx_active", &GPIO_2_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_bt_ldo_en", &GPIO_2_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("wifi_lte_mod4_sys_cync", &GPIO_6_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_en", &GPIO_6_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_blanking", &RF_GPIO_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_uart3_cts_n", &UART3_CTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_uart3_rts_n", &UART3_RTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_uart3_rxd", &UART3_RXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_uart3_txd", &UART3_TXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_clk", &GPS_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_pps_out", &GPIO_6_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("gps_reg_clk_out", &GPIO_6_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("tcxo_afc0", &TCXO0_AFC_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("tcxo_afc1", &TCXO1_AFC_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim0_clk", &USIM0_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim0_data", &USIM0_DATA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim0_rst", &USIM0_RST_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim1_clk", &USIM1_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim1_data", &USIM1_DATA_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("usim1_rst", &USIM1_RST_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_clk", &EMMC_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_cmd", &EMMC_CMD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data0", &EMMC_DATA0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data1", &EMMC_DATA1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data2", &EMMC_DATA2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data3", &EMMC_DATA3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data4", &EMMC_DATA4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data5", &EMMC_DATA5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data6", &EMMC_DATA6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_data7", &EMMC_DATA7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("emmc_rst_n", &GPIO_2_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("boot_sel", &BOOT_SEL_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("boot_jtag_sel1", &GPIO_5_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("codec_pcm1_xclk", &PCM1_XCLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("codec_pcm1_xfs", &PCM1_XFS_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("codec_pcm1_di", &PCM1_DI_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("codec_pcm1_do", &PCM1_DO_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("exphp_en", &GPIO_5_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("pmu_hkadc_ssi", &HKADC_SSI_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("pmu_aux_ssi0", &AUX_SSI0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("pmu_aux_ssi1", &AUX_SSI1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("pmu_auxdac_en", &GPIO_5_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart0_rxd", &UART0_RXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart0_txd", &UART0_TXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart7_rxd", &GPIO_7_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart7_txd", &GPIO_15_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart8_rxd", &GPIO_15_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("test_uart8_txd", &GPIO_15_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("switch_usb_sw_sel1", &GPIO_6_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("switch_usb_sw_sel0", &GPIO_5_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("charger_cd", &GPIO_4_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("charger_otg_en", &GPIO_4_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rfpmu_mipi_clk0", &RF_MIPI_CLK0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rfpmu_mipi_data0", &RF_MIPI_DATA0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_pmu_apt_pdm0", &APT_PDM0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rfant_det1", &GPIO_7_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rfant_det2", &GPIO_7_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_tcvr_on0", &RF_TCVR_ON0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_tcvr_on1", &RF_TCVR_ON1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_tx_en0", &RF_TX_EN0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_tx_en1", &RF_TX_EN1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_mipi_clk1", &RF_MIPI_CLK1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_mipi_data1", &RF_MIPI_DATA1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_ssi0", &RF_SSI0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_ssi1", &RF_SSI1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_2", &RF_GPIO_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_3", &RF_GPIO_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_4", &RF_GPIO_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_5", &RF_GPIO_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_6", &RF_GPIO_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_7", &RF_GPIO_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_8", &RF_GPIO_8_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_9", &RF_GPIO_9_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_10", &RF_GPIO_10_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_11", &RF_GPIO_11_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_12", &RF_GPIO_12_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_13", &RF_GPIO_13_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_14", &RF_GPIO_14_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_15", &RF_GPIO_15_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_16", &RF_GPIO_16_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_17", &RF_GPIO_17_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_18", &RF_GPIO_18_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_19", &RF_GPIO_19_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_20", &RF_GPIO_20_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_21", &RF_GPIO_21_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_22", &RF_GPIO_22_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_23", &RF_GPIO_23_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_24", &RF_GPIO_24_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_25", &RF_GPIO_25_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_26", &RF_GPIO_26_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_27", &RF_GPIO_27_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_28", &RF_GPIO_28_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_29", &RF_GPIO_29_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("rf_gpio_30", &RF_GPIO_30_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_clk", &SD_CLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_cmd", &SD_CMD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_data0", &SD_DATA0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_data1", &SD_DATA1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_data2", &SD_DATA2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("sd_data3", &SD_DATA3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_download", &UART1_RTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_ap_wakeup_modem", &UART1_RXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_ap_rst_modem", &GPIO_15_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_uart5_cts_n", &GPIO_5_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_uart5_rts_n", &GPIO_5_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_uart5_rxd", &GPIO_5_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_uart5_txd", &GPIO_5_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_usb_in_det", &UART1_CTS_N_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_ap_pwrhold_m", &GPIO_15_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("cdma_ap_pwron_m", &GPIO_15_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_reset_n", &UART1_TXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_uart2_rxd", &UART2_RXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_uart2_txd", &UART2_TXD_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_i2s_xclk", &I2S_XCLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_i2s_xfs", &I2S_XFS_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_i2s_di", &I2S_DI_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_i2s_do", &I2S_DO_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_pcm0_xclk", &PCM0_XCLK_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_pcm0_xfs", &PCM0_XFS_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_pcm0_di", &PCM0_DI_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_pcm0_do", &PCM0_DO_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("es305_int", &TS_ERR_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("nfc_clk", &GPIO_6_5_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("nfc_vsim_req", &GPIO_6_6_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("nfc_ldo_en", &GPIO_7_3_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("led_gpio_6_7", &GPIO_6_7_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("led_gpio_7_0", &GPIO_7_0_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("led_gpio_7_1", &GPIO_7_1_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("led_gpio_7_2", &GPIO_7_2_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE("spk_en", &GPIO_7_4_BALONG_LPDDR3_UDP_DCM_RF),
    PIN_TABLE(NULL, NULL)
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
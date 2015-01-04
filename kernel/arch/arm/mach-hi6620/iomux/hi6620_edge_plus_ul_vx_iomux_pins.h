/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_edge_plus_ul_vx_iomux_pins.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_EDGE_PLUS_UL_VX_IOMUX_PINS_H__
#define __HI6620_EDGE_PLUS_UL_VX_IOMUX_PINS_H__

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
static int iomg000_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg001_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg002_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg003_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg004_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg005_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg006_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg007_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg008_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg009_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg010_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg011_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg012_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg013_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg014_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg015_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg016_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg017_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg018_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg019_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg020_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg021_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg022_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg023_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg024_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg025_func_array_edge_plus_ul_vx[] = {0, RESERVE, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg026_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg027_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg028_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg029_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg030_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg031_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg032_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg033_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg034_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg035_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg036_func_array_edge_plus_ul_vx[] = {0, RESERVE, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg037_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg038_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg039_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg040_func_array_edge_plus_ul_vx[] = {0, 1, 2, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg041_func_array_edge_plus_ul_vx[] = {0, 1, 2, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg042_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg043_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg044_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg045_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg046_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg047_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg048_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg049_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg050_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg051_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg052_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg053_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg054_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg055_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg056_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg057_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, RESERVE, RESERVE,  };
static int iomg058_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, RESERVE, RESERVE,  };
static int iomg059_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg060_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg061_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg062_func_array_edge_plus_ul_vx[] = {0, RESERVE, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg063_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg064_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg065_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg066_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg067_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg068_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg069_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg070_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg071_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg072_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg073_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg074_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg075_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg076_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg077_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg078_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg079_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg080_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg081_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg082_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg083_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg084_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg085_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg086_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg087_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg088_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg089_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, RESERVE,  };
static int iomg090_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg091_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg092_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg093_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg094_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg095_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg096_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg097_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg098_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg099_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, RESERVE, RESERVE, RESERVE,  };
static int iomg100_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg101_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg102_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg103_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg104_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg105_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg106_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg107_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg108_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg109_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg110_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg111_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg112_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg113_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg114_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, RESERVE, 7,  };
static int iomg115_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg116_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg117_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg118_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg119_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg120_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg121_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg122_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg123_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg124_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg125_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, 7,  };
static int iomg126_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg127_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg128_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg129_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg130_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg131_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg132_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg133_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg134_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, 4, 5, 6, 7,  };
static int iomg135_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, 7,  };
static int iomg136_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg137_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg138_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg139_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg140_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg141_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg142_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg143_func_array_edge_plus_ul_vx[] = {0, RESERVE, RESERVE, 3, 4, RESERVE, RESERVE, RESERVE,  };
static int iomg144_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg145_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg146_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg147_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg148_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg149_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg150_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg151_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg152_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg153_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg154_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg155_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg156_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg157_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, 4, 5, 6, RESERVE,  };
static int iomg158_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg159_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg160_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg161_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg162_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg163_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg164_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg165_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg166_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg167_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg168_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg169_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg170_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg171_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg172_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg173_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg174_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg175_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg176_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg177_func_array_edge_plus_ul_vx[] = {0, 1, RESERVE, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg178_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg179_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg180_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg181_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg182_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg183_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg184_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg185_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg186_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg187_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };
static int iomg188_func_array_edge_plus_ul_vx[] = {0, 1, 2, 3, RESERVE, 5, 6, RESERVE,  };


IOMUX_IOMG(iomg000_edge_plus_ul_vx, "iomg000", 0x000, iomg000_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg001_edge_plus_ul_vx, "iomg001", 0x004, iomg001_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg002_edge_plus_ul_vx, "iomg002", 0x008, iomg002_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg003_edge_plus_ul_vx, "iomg003", 0x00C, iomg003_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg004_edge_plus_ul_vx, "iomg004", 0x010, iomg004_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg005_edge_plus_ul_vx, "iomg005", 0x014, iomg005_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg006_edge_plus_ul_vx, "iomg006", 0x018, iomg006_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg007_edge_plus_ul_vx, "iomg007", 0x2F0, iomg007_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg008_edge_plus_ul_vx, "iomg008", 0x01C, iomg008_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg009_edge_plus_ul_vx, "iomg009", 0x020, iomg009_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg010_edge_plus_ul_vx, "iomg010", 0x024, iomg010_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg011_edge_plus_ul_vx, "iomg011", 0x028, iomg011_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg012_edge_plus_ul_vx, "iomg012", 0x02C, iomg012_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg013_edge_plus_ul_vx, "iomg013", 0x030, iomg013_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg014_edge_plus_ul_vx, "iomg014", 0x034, iomg014_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg015_edge_plus_ul_vx, "iomg015", 0x038, iomg015_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg016_edge_plus_ul_vx, "iomg016", 0x03C, iomg016_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg017_edge_plus_ul_vx, "iomg017", 0x040, iomg017_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg018_edge_plus_ul_vx, "iomg018", 0x044, iomg018_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg019_edge_plus_ul_vx, "iomg019", 0x048, iomg019_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg020_edge_plus_ul_vx, "iomg020", 0x04C, iomg020_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg021_edge_plus_ul_vx, "iomg021", 0x050, iomg021_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg022_edge_plus_ul_vx, "iomg022", 0x054, iomg022_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg023_edge_plus_ul_vx, "iomg023", 0x058, iomg023_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg024_edge_plus_ul_vx, "iomg024", 0x05C, iomg024_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg025_edge_plus_ul_vx, "iomg025", 0x060, iomg025_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg026_edge_plus_ul_vx, "iomg026", 0x064, iomg026_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg027_edge_plus_ul_vx, "iomg027", 0x068, iomg027_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg028_edge_plus_ul_vx, "iomg028", 0x06C, iomg028_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg029_edge_plus_ul_vx, "iomg029", 0x070, iomg029_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg030_edge_plus_ul_vx, "iomg030", 0x074, iomg030_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg031_edge_plus_ul_vx, "iomg031", 0x078, iomg031_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg032_edge_plus_ul_vx, "iomg032", 0x07C, iomg032_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg033_edge_plus_ul_vx, "iomg033", 0x080, iomg033_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg034_edge_plus_ul_vx, "iomg034", 0x084, iomg034_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg035_edge_plus_ul_vx, "iomg035", 0x088, iomg035_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg036_edge_plus_ul_vx, "iomg036", 0x08C, iomg036_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg037_edge_plus_ul_vx, "iomg037", 0x090, iomg037_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg038_edge_plus_ul_vx, "iomg038", 0x094, iomg038_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg039_edge_plus_ul_vx, "iomg039", 0x098, iomg039_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg040_edge_plus_ul_vx, "iomg040", 0x09C, iomg040_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg041_edge_plus_ul_vx, "iomg041", 0x0A0, iomg041_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg042_edge_plus_ul_vx, "iomg042", 0x0A4, iomg042_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg043_edge_plus_ul_vx, "iomg043", 0x0A8, iomg043_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg044_edge_plus_ul_vx, "iomg044", 0x0AC, iomg044_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg045_edge_plus_ul_vx, "iomg045", 0x0B0, iomg045_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg046_edge_plus_ul_vx, "iomg046", 0x0B4, iomg046_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg047_edge_plus_ul_vx, "iomg047", 0x0B8, iomg047_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg048_edge_plus_ul_vx, "iomg048", 0x0BC, iomg048_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg049_edge_plus_ul_vx, "iomg049", 0x0C0, iomg049_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg050_edge_plus_ul_vx, "iomg050", 0x0C4, iomg050_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg051_edge_plus_ul_vx, "iomg051", 0x0C8, iomg051_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg052_edge_plus_ul_vx, "iomg052", 0x0CC, iomg052_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg053_edge_plus_ul_vx, "iomg053", 0x0D0, iomg053_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg054_edge_plus_ul_vx, "iomg054", 0x0D4, iomg054_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg055_edge_plus_ul_vx, "iomg055", 0x0D8, iomg055_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg056_edge_plus_ul_vx, "iomg056", 0x0DC, iomg056_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg057_edge_plus_ul_vx, "iomg057", 0x0E0, iomg057_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg058_edge_plus_ul_vx, "iomg058", 0x0E4, iomg058_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg059_edge_plus_ul_vx, "iomg059", 0x0E8, iomg059_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg060_edge_plus_ul_vx, "iomg060", 0x0EC, iomg060_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg061_edge_plus_ul_vx, "iomg061", 0x0F0, iomg061_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg062_edge_plus_ul_vx, "iomg062", 0x0F4, iomg062_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg063_edge_plus_ul_vx, "iomg063", 0x0F8, iomg063_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg064_edge_plus_ul_vx, "iomg064", 0x0FC, iomg064_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg065_edge_plus_ul_vx, "iomg065", 0x100, iomg065_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg066_edge_plus_ul_vx, "iomg066", 0x104, iomg066_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg067_edge_plus_ul_vx, "iomg067", 0x108, iomg067_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg068_edge_plus_ul_vx, "iomg068", 0x10C, iomg068_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg069_edge_plus_ul_vx, "iomg069", 0x110, iomg069_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg070_edge_plus_ul_vx, "iomg070", 0x114, iomg070_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg071_edge_plus_ul_vx, "iomg071", 0x118, iomg071_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg072_edge_plus_ul_vx, "iomg072", 0x11C, iomg072_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg073_edge_plus_ul_vx, "iomg073", 0x120, iomg073_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg074_edge_plus_ul_vx, "iomg074", 0x124, iomg074_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg075_edge_plus_ul_vx, "iomg075", 0x128, iomg075_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg076_edge_plus_ul_vx, "iomg076", 0x12C, iomg076_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg077_edge_plus_ul_vx, "iomg077", 0x130, iomg077_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg078_edge_plus_ul_vx, "iomg078", 0x134, iomg078_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg079_edge_plus_ul_vx, "iomg079", 0x138, iomg079_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg080_edge_plus_ul_vx, "iomg080", 0x13C, iomg080_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg081_edge_plus_ul_vx, "iomg081", 0x140, iomg081_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg082_edge_plus_ul_vx, "iomg082", 0x144, iomg082_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg083_edge_plus_ul_vx, "iomg083", 0x148, iomg083_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg084_edge_plus_ul_vx, "iomg084", 0x14C, iomg084_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg085_edge_plus_ul_vx, "iomg085", 0x150, iomg085_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg086_edge_plus_ul_vx, "iomg086", 0x154, iomg086_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg087_edge_plus_ul_vx, "iomg087", 0x158, iomg087_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg088_edge_plus_ul_vx, "iomg088", 0x15C, iomg088_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg089_edge_plus_ul_vx, "iomg089", 0x2EC, iomg089_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg090_edge_plus_ul_vx, "iomg090", 0x160, iomg090_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg091_edge_plus_ul_vx, "iomg091", 0x164, iomg091_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg092_edge_plus_ul_vx, "iomg092", 0x168, iomg092_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg093_edge_plus_ul_vx, "iomg093", 0x16C, iomg093_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg094_edge_plus_ul_vx, "iomg094", 0x170, iomg094_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg095_edge_plus_ul_vx, "iomg095", 0x174, iomg095_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg096_edge_plus_ul_vx, "iomg096", 0x2E8, iomg096_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg097_edge_plus_ul_vx, "iomg097", 0x178, iomg097_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg098_edge_plus_ul_vx, "iomg098", 0x17C, iomg098_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg099_edge_plus_ul_vx, "iomg099", 0x180, iomg099_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg100_edge_plus_ul_vx, "iomg100", 0x184, iomg100_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg101_edge_plus_ul_vx, "iomg101", 0x188, iomg101_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg102_edge_plus_ul_vx, "iomg102", 0x18C, iomg102_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg103_edge_plus_ul_vx, "iomg103", 0x190, iomg103_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg104_edge_plus_ul_vx, "iomg104", 0x194, iomg104_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg105_edge_plus_ul_vx, "iomg105", 0x198, iomg105_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg106_edge_plus_ul_vx, "iomg106", 0x19C, iomg106_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg107_edge_plus_ul_vx, "iomg107", 0x1A0, iomg107_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg108_edge_plus_ul_vx, "iomg108", 0x1A4, iomg108_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg109_edge_plus_ul_vx, "iomg109", 0x1A8, iomg109_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg110_edge_plus_ul_vx, "iomg110", 0x1AC, iomg110_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg111_edge_plus_ul_vx, "iomg111", 0x1B0, iomg111_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg112_edge_plus_ul_vx, "iomg112", 0x1B4, iomg112_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg113_edge_plus_ul_vx, "iomg113", 0x1B8, iomg113_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg114_edge_plus_ul_vx, "iomg114", 0x1BC, iomg114_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg115_edge_plus_ul_vx, "iomg115", 0x1C0, iomg115_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg116_edge_plus_ul_vx, "iomg116", 0x1C4, iomg116_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg117_edge_plus_ul_vx, "iomg117", 0x1C8, iomg117_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg118_edge_plus_ul_vx, "iomg118", 0x1CC, iomg118_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg119_edge_plus_ul_vx, "iomg119", 0x1D0, iomg119_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg120_edge_plus_ul_vx, "iomg120", 0x1D4, iomg120_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg121_edge_plus_ul_vx, "iomg121", 0x1D8, iomg121_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg122_edge_plus_ul_vx, "iomg122", 0x1DC, iomg122_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg123_edge_plus_ul_vx, "iomg123", 0x1E0, iomg123_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg124_edge_plus_ul_vx, "iomg124", 0x1E4, iomg124_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg125_edge_plus_ul_vx, "iomg125", 0x1E8, iomg125_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg126_edge_plus_ul_vx, "iomg126", 0x1EC, iomg126_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg127_edge_plus_ul_vx, "iomg127", 0x1F0, iomg127_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg128_edge_plus_ul_vx, "iomg128", 0x1F4, iomg128_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg129_edge_plus_ul_vx, "iomg129", 0x1F8, iomg129_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg130_edge_plus_ul_vx, "iomg130", 0x1FC, iomg130_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg131_edge_plus_ul_vx, "iomg131", 0x200, iomg131_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg132_edge_plus_ul_vx, "iomg132", 0x204, iomg132_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg133_edge_plus_ul_vx, "iomg133", 0x208, iomg133_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg134_edge_plus_ul_vx, "iomg134", 0x20C, iomg134_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg135_edge_plus_ul_vx, "iomg135", 0x210, iomg135_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg136_edge_plus_ul_vx, "iomg136", 0x214, iomg136_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg137_edge_plus_ul_vx, "iomg137", 0x218, iomg137_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg138_edge_plus_ul_vx, "iomg138", 0x21C, iomg138_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg139_edge_plus_ul_vx, "iomg139", 0x220, iomg139_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg140_edge_plus_ul_vx, "iomg140", 0x224, iomg140_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg141_edge_plus_ul_vx, "iomg141", 0x228, iomg141_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg142_edge_plus_ul_vx, "iomg142", 0x22C, iomg142_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg143_edge_plus_ul_vx, "iomg143", 0x230, iomg143_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg144_edge_plus_ul_vx, "iomg144", 0x234, iomg144_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg145_edge_plus_ul_vx, "iomg145", 0x238, iomg145_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg146_edge_plus_ul_vx, "iomg146", 0x23C, iomg146_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg147_edge_plus_ul_vx, "iomg147", 0x240, iomg147_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg148_edge_plus_ul_vx, "iomg148", 0x244, iomg148_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg149_edge_plus_ul_vx, "iomg149", 0x248, iomg149_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg150_edge_plus_ul_vx, "iomg150", 0x24C, iomg150_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg151_edge_plus_ul_vx, "iomg151", 0x250, iomg151_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg152_edge_plus_ul_vx, "iomg152", 0x254, iomg152_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg153_edge_plus_ul_vx, "iomg153", 0x258, iomg153_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg154_edge_plus_ul_vx, "iomg154", 0x25C, iomg154_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg155_edge_plus_ul_vx, "iomg155", 0x260, iomg155_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg156_edge_plus_ul_vx, "iomg156", 0x264, iomg156_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg157_edge_plus_ul_vx, "iomg157", 0x268, iomg157_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg158_edge_plus_ul_vx, "iomg158", 0x26C, iomg158_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg159_edge_plus_ul_vx, "iomg159", 0x270, iomg159_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg160_edge_plus_ul_vx, "iomg160", 0x274, iomg160_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg161_edge_plus_ul_vx, "iomg161", 0x278, iomg161_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg162_edge_plus_ul_vx, "iomg162", 0x27C, iomg162_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg163_edge_plus_ul_vx, "iomg163", 0x280, iomg163_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg164_edge_plus_ul_vx, "iomg164", 0x284, iomg164_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg165_edge_plus_ul_vx, "iomg165", 0x288, iomg165_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg166_edge_plus_ul_vx, "iomg166", 0x28C, iomg166_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg167_edge_plus_ul_vx, "iomg167", 0x290, iomg167_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg168_edge_plus_ul_vx, "iomg168", 0x294, iomg168_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg169_edge_plus_ul_vx, "iomg169", 0x298, iomg169_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg170_edge_plus_ul_vx, "iomg170", 0x29C, iomg170_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg171_edge_plus_ul_vx, "iomg171", 0x2A0, iomg171_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg172_edge_plus_ul_vx, "iomg172", 0x2A4, iomg172_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg173_edge_plus_ul_vx, "iomg173", 0x2A8, iomg173_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg174_edge_plus_ul_vx, "iomg174", 0x2AC, iomg174_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg175_edge_plus_ul_vx, "iomg175", 0x2B0, iomg175_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg176_edge_plus_ul_vx, "iomg176", 0x2B4, iomg176_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg177_edge_plus_ul_vx, "iomg177", 0x2B8, iomg177_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg178_edge_plus_ul_vx, "iomg178", 0x2BC, iomg178_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg179_edge_plus_ul_vx, "iomg179", 0x2C0, iomg179_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg180_edge_plus_ul_vx, "iomg180", 0x2C4, iomg180_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg181_edge_plus_ul_vx, "iomg181", 0x2C8, iomg181_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg182_edge_plus_ul_vx, "iomg182", 0x2CC, iomg182_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg183_edge_plus_ul_vx, "iomg183", 0x2D0, iomg183_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg184_edge_plus_ul_vx, "iomg184", 0x2D4, iomg184_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg185_edge_plus_ul_vx, "iomg185", 0x2D8, iomg185_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg186_edge_plus_ul_vx, "iomg186", 0x2DC, iomg186_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg187_edge_plus_ul_vx, "iomg187", 0x2E0, iomg187_func_array_edge_plus_ul_vx)
IOMUX_IOMG(iomg188_edge_plus_ul_vx, "iomg188", 0x2E4, iomg188_func_array_edge_plus_ul_vx)


/*define pins*/
IOMUX_IOCG(iocg000_edge_plus_ul_vx, "iocg000", 0x800, 0x0003, 0x00F0)
IOMUX_IOCG(iocg001_edge_plus_ul_vx, "iocg001", 0x804, 0x0003, 0x00F0)
IOMUX_IOCG(iocg002_edge_plus_ul_vx, "iocg002", 0x808, 0x0003, 0x00F0)
IOMUX_IOCG(iocg003_edge_plus_ul_vx, "iocg003", 0x80C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg004_edge_plus_ul_vx, "iocg004", 0x810, 0x0003, 0x00F0)
IOMUX_IOCG(iocg005_edge_plus_ul_vx, "iocg005", 0x814, 0x0003, 0x00F0)
IOMUX_IOCG(iocg006_edge_plus_ul_vx, "iocg006", 0x818, 0x0003, 0x00F0)
IOMUX_IOCG(iocg007_edge_plus_ul_vx, "iocg007", 0x81C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg008_edge_plus_ul_vx, "iocg008", 0x820, 0x0003, 0x00F0)
IOMUX_IOCG(iocg009_edge_plus_ul_vx, "iocg009", 0x824, 0x0003, 0x00F0)
IOMUX_IOCG(iocg010_edge_plus_ul_vx, "iocg010", 0x828, 0x0003, 0x00F0)
IOMUX_IOCG(iocg011_edge_plus_ul_vx, "iocg011", 0x82C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg012_edge_plus_ul_vx, "iocg012", 0x830, 0x0003, 0x00F0)
IOMUX_IOCG(iocg013_edge_plus_ul_vx, "iocg013", 0x834, 0x0003, 0x00F0)
IOMUX_IOCG(iocg014_edge_plus_ul_vx, "iocg014", 0x838, 0x0003, 0x00F0)
IOMUX_IOCG(iocg015_edge_plus_ul_vx, "iocg015", 0x83C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg016_edge_plus_ul_vx, "iocg016", 0x840, 0x0003, 0x00F0)
IOMUX_IOCG(iocg017_edge_plus_ul_vx, "iocg017", 0x844, 0x0003, 0x00F0)
IOMUX_IOCG(iocg018_edge_plus_ul_vx, "iocg018", 0x848, 0x0003, 0x00F0)
IOMUX_IOCG(iocg019_edge_plus_ul_vx, "iocg019", 0x84C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg020_edge_plus_ul_vx, "iocg020", 0x850, 0x0003, 0x00F0)
IOMUX_IOCG(iocg021_edge_plus_ul_vx, "iocg021", 0x854, 0x0003, 0x00F0)
IOMUX_IOCG(iocg022_edge_plus_ul_vx, "iocg022", 0x858, 0x0003, 0x00F0)
IOMUX_IOCG(iocg023_edge_plus_ul_vx, "iocg023", 0x85C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg024_edge_plus_ul_vx, "iocg024", 0x860, 0x0003, 0x00F0)
IOMUX_IOCG(iocg025_edge_plus_ul_vx, "iocg025", 0x864, 0x0003, 0x00F0)
IOMUX_IOCG(iocg026_edge_plus_ul_vx, "iocg026", 0x868, 0x0003, 0x00F0)
IOMUX_IOCG(iocg027_edge_plus_ul_vx, "iocg027", 0x86C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg028_edge_plus_ul_vx, "iocg028", 0x870, 0x0003, 0x00F0)
IOMUX_IOCG(iocg029_edge_plus_ul_vx, "iocg029", 0x874, 0x0003, 0x00F0)
IOMUX_IOCG(iocg030_edge_plus_ul_vx, "iocg030", 0x878, 0x0003, 0x00F0)
IOMUX_IOCG(iocg031_edge_plus_ul_vx, "iocg031", 0x87C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg032_edge_plus_ul_vx, "iocg032", 0x880, 0x0003, 0x00F0)
IOMUX_IOCG(iocg033_edge_plus_ul_vx, "iocg033", 0x884, 0x0003, 0x00F0)
IOMUX_IOCG(iocg034_edge_plus_ul_vx, "iocg034", 0x888, 0x0003, 0x00F0)
IOMUX_IOCG(iocg035_edge_plus_ul_vx, "iocg035", 0x88C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg036_edge_plus_ul_vx, "iocg036", 0x890, 0x0003, 0x00F0)
IOMUX_IOCG(iocg037_edge_plus_ul_vx, "iocg037", 0x894, 0x0003, 0x00F0)
IOMUX_IOCG(iocg038_edge_plus_ul_vx, "iocg038", 0x898, 0x0003, 0x00F0)
IOMUX_IOCG(iocg039_edge_plus_ul_vx, "iocg039", 0x89C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg040_edge_plus_ul_vx, "iocg040", 0x8A0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg041_edge_plus_ul_vx, "iocg041", 0x8A4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg042_edge_plus_ul_vx, "iocg042", 0x8A8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg043_edge_plus_ul_vx, "iocg043", 0x8AC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg044_edge_plus_ul_vx, "iocg044", 0x8B0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg045_edge_plus_ul_vx, "iocg045", 0x8B4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg046_edge_plus_ul_vx, "iocg046", 0x8B8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg047_edge_plus_ul_vx, "iocg047", 0x8BC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg048_edge_plus_ul_vx, "iocg048", 0x8C0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg049_edge_plus_ul_vx, "iocg049", 0x8C4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg050_edge_plus_ul_vx, "iocg050", 0x8C8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg051_edge_plus_ul_vx, "iocg051", 0x8CC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg052_edge_plus_ul_vx, "iocg052", 0x8D0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg053_edge_plus_ul_vx, "iocg053", 0x8D4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg054_edge_plus_ul_vx, "iocg054", 0x8D8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg055_edge_plus_ul_vx, "iocg055", 0x8DC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg056_edge_plus_ul_vx, "iocg056", 0x8E0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg057_edge_plus_ul_vx, "iocg057", 0x8E4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg058_edge_plus_ul_vx, "iocg058", 0x8E8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg059_edge_plus_ul_vx, "iocg059", 0x8EC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg060_edge_plus_ul_vx, "iocg060", 0x8F0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg061_edge_plus_ul_vx, "iocg061", 0x8F4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg062_edge_plus_ul_vx, "iocg062", 0x8F8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg063_edge_plus_ul_vx, "iocg063", 0x8FC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg064_edge_plus_ul_vx, "iocg064", 0x900, 0x0003, 0x00F0)
IOMUX_IOCG(iocg065_edge_plus_ul_vx, "iocg065", 0x904, 0x0003, 0x00F0)
IOMUX_IOCG(iocg066_edge_plus_ul_vx, "iocg066", 0x908, 0x0003, 0x00F0)
IOMUX_IOCG(iocg067_edge_plus_ul_vx, "iocg067", 0x90C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg068_edge_plus_ul_vx, "iocg068", 0x910, 0x0003, 0x00F0)
IOMUX_IOCG(iocg069_edge_plus_ul_vx, "iocg069", 0x914, 0x0003, 0x00F0)
IOMUX_IOCG(iocg070_edge_plus_ul_vx, "iocg070", 0x918, 0x0003, 0x00F0)
IOMUX_IOCG(iocg071_edge_plus_ul_vx, "iocg071", 0x91C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg072_edge_plus_ul_vx, "iocg072", 0x920, 0x0003, 0x00F0)
IOMUX_IOCG(iocg073_edge_plus_ul_vx, "iocg073", 0x924, 0x0003, 0x00F0)
IOMUX_IOCG(iocg074_edge_plus_ul_vx, "iocg074", 0x928, 0x0003, 0x00F0)
IOMUX_IOCG(iocg075_edge_plus_ul_vx, "iocg075", 0x92C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg076_edge_plus_ul_vx, "iocg076", 0x930, 0x0003, 0x00F0)
IOMUX_IOCG(iocg077_edge_plus_ul_vx, "iocg077", 0x934, 0x0003, 0x00F0)
IOMUX_IOCG(iocg078_edge_plus_ul_vx, "iocg078", 0x938, 0x0003, 0x00F0)
IOMUX_IOCG(iocg079_edge_plus_ul_vx, "iocg079", 0x93C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg080_edge_plus_ul_vx, "iocg080", 0x940, 0x0003, 0x00F0)
IOMUX_IOCG(iocg081_edge_plus_ul_vx, "iocg081", 0x944, 0x0003, 0x00F0)
IOMUX_IOCG(iocg082_edge_plus_ul_vx, "iocg082", 0x948, 0x0003, 0x00F0)
IOMUX_IOCG(iocg083_edge_plus_ul_vx, "iocg083", 0x94C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg084_edge_plus_ul_vx, "iocg084", 0x950, 0x0003, 0x00F0)
IOMUX_IOCG(iocg085_edge_plus_ul_vx, "iocg085", 0x954, 0x0003, 0x00F0)
IOMUX_IOCG(iocg086_edge_plus_ul_vx, "iocg086", 0x958, 0x0003, 0x00F0)
IOMUX_IOCG(iocg087_edge_plus_ul_vx, "iocg087", 0x95C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg088_edge_plus_ul_vx, "iocg088", 0x960, 0x0003, 0x00F0)
IOMUX_IOCG(iocg089_edge_plus_ul_vx, "iocg089", 0x964, 0x0003, 0x00F0)
IOMUX_IOCG(iocg090_edge_plus_ul_vx, "iocg090", 0x968, 0x0003, 0x00F0)
IOMUX_IOCG(iocg091_edge_plus_ul_vx, "iocg091", 0x96C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg092_edge_plus_ul_vx, "iocg092", 0x970, 0x0003, 0x00F0)
IOMUX_IOCG(iocg093_edge_plus_ul_vx, "iocg093", 0x974, 0x0003, 0x00F0)
IOMUX_IOCG(iocg094_edge_plus_ul_vx, "iocg094", 0x978, 0x0003, 0x00F0)
IOMUX_IOCG(iocg095_edge_plus_ul_vx, "iocg095", 0x97C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg096_edge_plus_ul_vx, "iocg096", 0x980, 0x0003, 0x00F0)
IOMUX_IOCG(iocg097_edge_plus_ul_vx, "iocg097", 0x984, 0x0003, 0x00F0)
IOMUX_IOCG(iocg098_edge_plus_ul_vx, "iocg098", 0x988, 0x0003, 0x00F0)
IOMUX_IOCG(iocg099_edge_plus_ul_vx, "iocg099", 0x98C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg100_edge_plus_ul_vx, "iocg100", 0x990, 0x0003, 0x00F0)
IOMUX_IOCG(iocg101_edge_plus_ul_vx, "iocg101", 0x994, 0x0003, 0x00F0)
IOMUX_IOCG(iocg102_edge_plus_ul_vx, "iocg102", 0x998, 0x0003, 0x00F0)
IOMUX_IOCG(iocg103_edge_plus_ul_vx, "iocg103", 0x99C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg104_edge_plus_ul_vx, "iocg104", 0x9A0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg105_edge_plus_ul_vx, "iocg105", 0x9A4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg106_edge_plus_ul_vx, "iocg106", 0x9A8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg107_edge_plus_ul_vx, "iocg107", 0x9AC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg108_edge_plus_ul_vx, "iocg108", 0x9B0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg109_edge_plus_ul_vx, "iocg109", 0x9B4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg110_edge_plus_ul_vx, "iocg110", 0x9B8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg111_edge_plus_ul_vx, "iocg111", 0x9BC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg112_edge_plus_ul_vx, "iocg112", 0x9C0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg113_edge_plus_ul_vx, "iocg113", 0x9C4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg114_edge_plus_ul_vx, "iocg114", 0x9C8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg115_edge_plus_ul_vx, "iocg115", 0x9CC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg116_edge_plus_ul_vx, "iocg116", 0x9D0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg117_edge_plus_ul_vx, "iocg117", 0x9D4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg118_edge_plus_ul_vx, "iocg118", 0x9D8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg119_edge_plus_ul_vx, "iocg119", 0x9DC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg120_edge_plus_ul_vx, "iocg120", 0x9E0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg121_edge_plus_ul_vx, "iocg121", 0x9E4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg122_edge_plus_ul_vx, "iocg122", 0x9E8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg123_edge_plus_ul_vx, "iocg123", 0x9EC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg124_edge_plus_ul_vx, "iocg124", 0x9F0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg125_edge_plus_ul_vx, "iocg125", 0x9F4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg126_edge_plus_ul_vx, "iocg126", 0x9F8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg127_edge_plus_ul_vx, "iocg127", 0x9FC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg128_edge_plus_ul_vx, "iocg128", 0xA00, 0x0003, 0x00F0)
IOMUX_IOCG(iocg129_edge_plus_ul_vx, "iocg129", 0xA04, 0x0003, 0x00F0)
IOMUX_IOCG(iocg130_edge_plus_ul_vx, "iocg130", 0xA08, 0x0003, 0x00F0)
IOMUX_IOCG(iocg131_edge_plus_ul_vx, "iocg131", 0xA0C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg132_edge_plus_ul_vx, "iocg132", 0xA10, 0x0003, 0x00F0)
IOMUX_IOCG(iocg133_edge_plus_ul_vx, "iocg133", 0xA14, 0x0003, 0x00F0)
IOMUX_IOCG(iocg134_edge_plus_ul_vx, "iocg134", 0xA18, 0x0003, 0x00F0)
IOMUX_IOCG(iocg135_edge_plus_ul_vx, "iocg135", 0xA1C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg136_edge_plus_ul_vx, "iocg136", 0xA20, 0x0003, 0x00F0)
IOMUX_IOCG(iocg137_edge_plus_ul_vx, "iocg137", 0xA24, 0x0003, 0x00F0)
IOMUX_IOCG(iocg138_edge_plus_ul_vx, "iocg138", 0xA28, 0x0003, 0x00F0)
IOMUX_IOCG(iocg139_edge_plus_ul_vx, "iocg139", 0xA2C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg140_edge_plus_ul_vx, "iocg140", 0xA30, 0x0003, 0x00F0)
IOMUX_IOCG(iocg141_edge_plus_ul_vx, "iocg141", 0xA34, 0x0003, 0x00F0)
IOMUX_IOCG(iocg142_edge_plus_ul_vx, "iocg142", 0xA38, 0x0003, 0x00F0)
IOMUX_IOCG(iocg143_edge_plus_ul_vx, "iocg143", 0xA3C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg144_edge_plus_ul_vx, "iocg144", 0xA40, 0x0003, 0x00F0)
IOMUX_IOCG(iocg145_edge_plus_ul_vx, "iocg145", 0xA44, 0x0003, 0x00F0)
IOMUX_IOCG(iocg146_edge_plus_ul_vx, "iocg146", 0xA48, 0x0003, 0x00F0)
IOMUX_IOCG(iocg147_edge_plus_ul_vx, "iocg147", 0xA4C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg148_edge_plus_ul_vx, "iocg148", 0xA50, 0x0003, 0x00F0)
IOMUX_IOCG(iocg149_edge_plus_ul_vx, "iocg149", 0xA54, 0x0003, 0x00F0)
IOMUX_IOCG(iocg150_edge_plus_ul_vx, "iocg150", 0xA58, 0x0003, 0x00F0)
IOMUX_IOCG(iocg151_edge_plus_ul_vx, "iocg151", 0xA5C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg152_edge_plus_ul_vx, "iocg152", 0xA60, 0x0003, 0x00F0)
IOMUX_IOCG(iocg153_edge_plus_ul_vx, "iocg153", 0xA64, 0x0003, 0x00F0)
IOMUX_IOCG(iocg154_edge_plus_ul_vx, "iocg154", 0xA68, 0x0003, 0x00F0)
IOMUX_IOCG(iocg155_edge_plus_ul_vx, "iocg155", 0xA6C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg156_edge_plus_ul_vx, "iocg156", 0xA70, 0x0003, 0x00F0)
IOMUX_IOCG(iocg157_edge_plus_ul_vx, "iocg157", 0xA74, 0x0003, 0x00F0)
IOMUX_IOCG(iocg158_edge_plus_ul_vx, "iocg158", 0xA78, 0x0003, 0x00F0)
IOMUX_IOCG(iocg159_edge_plus_ul_vx, "iocg159", 0xA7C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg160_edge_plus_ul_vx, "iocg160", 0xA80, 0x0003, 0x00F0)
IOMUX_IOCG(iocg161_edge_plus_ul_vx, "iocg161", 0xA84, 0x0003, 0x00F0)
IOMUX_IOCG(iocg162_edge_plus_ul_vx, "iocg162", 0xA88, 0x0003, 0x00F0)
IOMUX_IOCG(iocg163_edge_plus_ul_vx, "iocg163", 0xA8C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg164_edge_plus_ul_vx, "iocg164", 0xA90, 0x0003, 0x00F0)
IOMUX_IOCG(iocg165_edge_plus_ul_vx, "iocg165", 0xA94, 0x0003, 0x00F0)
IOMUX_IOCG(iocg166_edge_plus_ul_vx, "iocg166", 0xA98, 0x0003, 0x00F0)
IOMUX_IOCG(iocg167_edge_plus_ul_vx, "iocg167", 0xA9C, 0x0003, 0x00F0)
IOMUX_IOCG(iocg168_edge_plus_ul_vx, "iocg168", 0xAA0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg169_edge_plus_ul_vx, "iocg169", 0xAA4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg170_edge_plus_ul_vx, "iocg170", 0xAA8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg171_edge_plus_ul_vx, "iocg171", 0xAAC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg172_edge_plus_ul_vx, "iocg172", 0xAB0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg173_edge_plus_ul_vx, "iocg173", 0xAB4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg174_edge_plus_ul_vx, "iocg174", 0xAB8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg175_edge_plus_ul_vx, "iocg175", 0xABC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg176_edge_plus_ul_vx, "iocg176", 0xAC0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg177_edge_plus_ul_vx, "iocg177", 0xAC4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg178_edge_plus_ul_vx, "iocg178", 0xAC8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg179_edge_plus_ul_vx, "iocg179", 0xACC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg180_edge_plus_ul_vx, "iocg180", 0xAD0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg181_edge_plus_ul_vx, "iocg181", 0xAD4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg182_edge_plus_ul_vx, "iocg182", 0xAD8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg183_edge_plus_ul_vx, "iocg183", 0xADC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg184_edge_plus_ul_vx, "iocg184", 0xAE0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg185_edge_plus_ul_vx, "iocg185", 0xAE4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg186_edge_plus_ul_vx, "iocg186", 0xAE8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg187_edge_plus_ul_vx, "iocg187", 0xAEC, 0x0003, 0x00F0)
IOMUX_IOCG(iocg188_edge_plus_ul_vx, "iocg188", 0xAF0, 0x0003, 0x00F0)
IOMUX_IOCG(iocg189_edge_plus_ul_vx, "iocg189", 0xAF4, 0x0003, 0x00F0)
IOMUX_IOCG(iocg190_edge_plus_ul_vx, "iocg190", 0xAF8, 0x0003, 0x00F0)
IOMUX_IOCG(iocg191_edge_plus_ul_vx, "iocg191", 0xAFC, 0x0003, 0x00F0)


/*define the iocg*/
IOMUX_PIN(I2C0_SCL_EDGE_PLUS_UL_VX, "I2C0_SCL", FUNC0, NOPULL, LEVEL0, &iomg071_edge_plus_ul_vx, &iocg071_edge_plus_ul_vx)
IOMUX_PIN(I2C0_SDA_EDGE_PLUS_UL_VX, "I2C0_SDA", FUNC0, NOPULL, LEVEL0, &iomg072_edge_plus_ul_vx, &iocg072_edge_plus_ul_vx)
IOMUX_PIN(I2C1_SCL_EDGE_PLUS_UL_VX, "I2C1_SCL", FUNC0, NOPULL, LEVEL0, &iomg073_edge_plus_ul_vx, &iocg073_edge_plus_ul_vx)
IOMUX_PIN(I2C1_SDA_EDGE_PLUS_UL_VX, "I2C1_SDA", FUNC0, NOPULL, LEVEL0, &iomg074_edge_plus_ul_vx, &iocg074_edge_plus_ul_vx)
IOMUX_PIN(I2C2_SCL_EDGE_PLUS_UL_VX, "I2C2_SCL", FUNC0, NOPULL, LEVEL0, &iomg075_edge_plus_ul_vx, &iocg075_edge_plus_ul_vx)
IOMUX_PIN(I2C2_SDA_EDGE_PLUS_UL_VX, "I2C2_SDA", FUNC0, NOPULL, LEVEL0, &iomg076_edge_plus_ul_vx, &iocg076_edge_plus_ul_vx)
IOMUX_PIN(I2C3_SCL_EDGE_PLUS_UL_VX, "I2C3_SCL", FUNC0, NOPULL, LEVEL0, &iomg077_edge_plus_ul_vx, &iocg077_edge_plus_ul_vx)
IOMUX_PIN(I2C3_SDA_EDGE_PLUS_UL_VX, "I2C3_SDA", FUNC0, NOPULL, LEVEL0, &iomg078_edge_plus_ul_vx, &iocg078_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO0_EDGE_PLUS_UL_VX, "ISP_GPIO0", FUNC0, NOPULL, LEVEL0, &iomg008_edge_plus_ul_vx, &iocg008_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO2_EDGE_PLUS_UL_VX, "ISP_GPIO2", FUNC0, NOPULL, LEVEL0, &iomg010_edge_plus_ul_vx, &iocg010_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO3_EDGE_PLUS_UL_VX, "ISP_GPIO3", FUNC2, NOPULL, LEVEL0, &iomg011_edge_plus_ul_vx, &iocg011_edge_plus_ul_vx)
IOMUX_PIN(ISP_RESETB0_EDGE_PLUS_UL_VX, "ISP_RESETB0", FUNC0, NOPULL, LEVEL0, &iomg016_edge_plus_ul_vx, &iocg016_edge_plus_ul_vx)
IOMUX_PIN(ISP_CCLK0_EDGE_PLUS_UL_VX, "ISP_CCLK0", FUNC0, NOPULL, LEVEL0, &iomg014_edge_plus_ul_vx, &iocg014_edge_plus_ul_vx)
IOMUX_PIN(ISP_SDA0_EDGE_PLUS_UL_VX, "ISP_SDA0", FUNC2, PULLDOWN, LEVEL0, &iomg020_edge_plus_ul_vx, &iocg020_edge_plus_ul_vx)
IOMUX_PIN(ISP_SCL0_EDGE_PLUS_UL_VX, "ISP_SCL0", FUNC2, PULLDOWN, LEVEL0, &iomg021_edge_plus_ul_vx, &iocg021_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO1_EDGE_PLUS_UL_VX, "ISP_GPIO1", FUNC0, NOPULL, LEVEL0, &iomg009_edge_plus_ul_vx, &iocg009_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO4_EDGE_PLUS_UL_VX, "ISP_GPIO4", FUNC2, NOPULL, LEVEL0, &iomg012_edge_plus_ul_vx, &iocg012_edge_plus_ul_vx)
IOMUX_PIN(ISP_RESETB1_EDGE_PLUS_UL_VX, "ISP_RESETB1", FUNC0, NOPULL, LEVEL0, &iomg017_edge_plus_ul_vx, &iocg017_edge_plus_ul_vx)
IOMUX_PIN(ISP_CCLK1_EDGE_PLUS_UL_VX, "ISP_CCLK1", FUNC0, NOPULL, LEVEL0, &iomg015_edge_plus_ul_vx, &iocg015_edge_plus_ul_vx)
IOMUX_PIN(ISP_SDA1_EDGE_PLUS_UL_VX, "ISP_SDA1", FUNC2, PULLDOWN, LEVEL0, &iomg022_edge_plus_ul_vx, &iocg022_edge_plus_ul_vx)
IOMUX_PIN(ISP_SCL1_EDGE_PLUS_UL_VX, "ISP_SCL1", FUNC2, PULLDOWN, LEVEL0, &iomg023_edge_plus_ul_vx, &iocg023_edge_plus_ul_vx)
IOMUX_PIN(ISP_GPIO5_EDGE_PLUS_UL_VX, "ISP_GPIO5", FUNC2, NOPULL, LEVEL0, &iomg013_edge_plus_ul_vx, &iocg013_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_20_EDGE_PLUS_UL_VX, "RF_GPIO_20", FUNC2, NOPULL, LEVEL0, &iomg178_edge_plus_ul_vx, &iocg188_edge_plus_ul_vx)
IOMUX_PIN(GPIO_4_2_EDGE_PLUS_UL_VX, "GPIO_4_2", FUNC0, PULLUP, LEVEL0, &iomg130_edge_plus_ul_vx, &iocg130_edge_plus_ul_vx)
IOMUX_PIN(GPIO_4_3_EDGE_PLUS_UL_VX, "GPIO_4_3", FUNC0, PULLUP, LEVEL0, &iomg131_edge_plus_ul_vx, &iocg131_edge_plus_ul_vx)
IOMUX_PIN(PWM_OUT1_EDGE_PLUS_UL_VX, "PWM_OUT1", FUNC2, NOPULL, LEVEL0, &iomg025_edge_plus_ul_vx, &iocg025_edge_plus_ul_vx)
IOMUX_PIN(GPIO_4_6_EDGE_PLUS_UL_VX, "GPIO_4_6", FUNC0, NOPULL, LEVEL0, &iomg134_edge_plus_ul_vx, &iocg134_edge_plus_ul_vx)
IOMUX_PIN(GPIO_4_7_EDGE_PLUS_UL_VX, "GPIO_4_7", FUNC4, NOPULL, LEVEL0, &iomg135_edge_plus_ul_vx, &iocg135_edge_plus_ul_vx)
IOMUX_PIN(GPIO_18_7_EDGE_PLUS_UL_VX, "GPIO_18_7", FUNC0, NOPULL, LEVEL0, &iomg007_edge_plus_ul_vx, &iocg191_edge_plus_ul_vx)
IOMUX_PIN(UART4_CTS_N_EDGE_PLUS_UL_VX, "UART4_CTS_N", FUNC0, NOPULL, LEVEL0, &iomg067_edge_plus_ul_vx, &iocg067_edge_plus_ul_vx)
IOMUX_PIN(UART4_RTS_N_EDGE_PLUS_UL_VX, "UART4_RTS_N", FUNC4, PULLUP, LEVEL0, &iomg068_edge_plus_ul_vx, &iocg068_edge_plus_ul_vx)
IOMUX_PIN(UART4_RXD_EDGE_PLUS_UL_VX, "UART4_RXD", FUNC0, NOPULL, LEVEL0, &iomg069_edge_plus_ul_vx, &iocg069_edge_plus_ul_vx)
IOMUX_PIN(UART4_TXD_EDGE_PLUS_UL_VX, "UART4_TXD", FUNC4, PULLUP, LEVEL0, &iomg070_edge_plus_ul_vx, &iocg070_edge_plus_ul_vx)
IOMUX_PIN(GPIO_15_7_EDGE_PLUS_UL_VX, "GPIO_15_7", FUNC0, NOPULL, LEVEL0, &iomg127_edge_plus_ul_vx, &iocg127_edge_plus_ul_vx)
IOMUX_PIN(SDIO_DATA3_EDGE_PLUS_UL_VX, "SDIO_DATA3", FUNC2, PULLUP, LEVEL0, &iomg095_edge_plus_ul_vx, &iocg095_edge_plus_ul_vx)
IOMUX_PIN(SDIO_DATA2_EDGE_PLUS_UL_VX, "SDIO_DATA2", FUNC2, PULLUP, LEVEL0, &iomg094_edge_plus_ul_vx, &iocg094_edge_plus_ul_vx)
IOMUX_PIN(SDIO_DATA1_EDGE_PLUS_UL_VX, "SDIO_DATA1", FUNC2, PULLUP, LEVEL0, &iomg093_edge_plus_ul_vx, &iocg093_edge_plus_ul_vx)
IOMUX_PIN(SDIO_DATA0_EDGE_PLUS_UL_VX, "SDIO_DATA0", FUNC2, PULLUP, LEVEL0, &iomg092_edge_plus_ul_vx, &iocg092_edge_plus_ul_vx)
IOMUX_PIN(SDIO_CMD_EDGE_PLUS_UL_VX, "SDIO_CMD", FUNC2, PULLUP, LEVEL0, &iomg091_edge_plus_ul_vx, &iocg091_edge_plus_ul_vx)
IOMUX_PIN(SDIO_CLK_EDGE_PLUS_UL_VX, "SDIO_CLK", FUNC2, NOPULL, LEVEL0, &iomg090_edge_plus_ul_vx, &iocg090_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_1_EDGE_PLUS_UL_VX, "RF_GPIO_1", FUNC0, NOPULL, LEVEL0, &iomg159_edge_plus_ul_vx, &iocg159_edge_plus_ul_vx)
IOMUX_PIN(UART3_CTS_N_EDGE_PLUS_UL_VX, "UART3_CTS_N", FUNC0, NOPULL, LEVEL0, &iomg063_edge_plus_ul_vx, &iocg063_edge_plus_ul_vx)
IOMUX_PIN(UART3_RTS_N_EDGE_PLUS_UL_VX, "UART3_RTS_N", FUNC0, NOPULL, LEVEL0, &iomg064_edge_plus_ul_vx, &iocg064_edge_plus_ul_vx)
IOMUX_PIN(UART3_RXD_EDGE_PLUS_UL_VX, "UART3_RXD", FUNC0, NOPULL, LEVEL0, &iomg065_edge_plus_ul_vx, &iocg065_edge_plus_ul_vx)
IOMUX_PIN(UART3_TXD_EDGE_PLUS_UL_VX, "UART3_TXD", FUNC0, NOPULL, LEVEL0, &iomg066_edge_plus_ul_vx, &iocg066_edge_plus_ul_vx)
IOMUX_PIN(GPS_CLK_EDGE_PLUS_UL_VX, "GPS_CLK", FUNC2, NOPULL, LEVEL0, &iomg049_edge_plus_ul_vx, &iocg049_edge_plus_ul_vx)
IOMUX_PIN(TCXO0_AFC_EDGE_PLUS_UL_VX, "TCXO0_AFC", FUNC4, PULLDOWN, LEVEL0, &iomg144_edge_plus_ul_vx, &iocg144_edge_plus_ul_vx)
IOMUX_PIN(USIM0_CLK_EDGE_PLUS_UL_VX, "USIM0_CLK", FUNC0, NOPULL, LEVEL0, &iomg043_edge_plus_ul_vx, &iocg043_edge_plus_ul_vx)
IOMUX_PIN(USIM0_DATA_EDGE_PLUS_UL_VX, "USIM0_DATA", FUNC0, NOPULL, LEVEL0, &iomg044_edge_plus_ul_vx, &iocg044_edge_plus_ul_vx)
IOMUX_PIN(USIM0_RST_EDGE_PLUS_UL_VX, "USIM0_RST", FUNC0, NOPULL, LEVEL0, &iomg045_edge_plus_ul_vx, &iocg045_edge_plus_ul_vx)
IOMUX_PIN(EMMC_CLK_EDGE_PLUS_UL_VX, "EMMC_CLK", FUNC0, NOPULL, LEVEL1, &iomg079_edge_plus_ul_vx, &iocg079_edge_plus_ul_vx)
IOMUX_PIN(EMMC_CMD_EDGE_PLUS_UL_VX, "EMMC_CMD", FUNC0, NOPULL, LEVEL1, &iomg080_edge_plus_ul_vx, &iocg080_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA0_EDGE_PLUS_UL_VX, "EMMC_DATA0", FUNC0, NOPULL, LEVEL1, &iomg081_edge_plus_ul_vx, &iocg081_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA1_EDGE_PLUS_UL_VX, "EMMC_DATA1", FUNC0, NOPULL, LEVEL1, &iomg082_edge_plus_ul_vx, &iocg082_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA2_EDGE_PLUS_UL_VX, "EMMC_DATA2", FUNC0, NOPULL, LEVEL1, &iomg083_edge_plus_ul_vx, &iocg083_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA3_EDGE_PLUS_UL_VX, "EMMC_DATA3", FUNC0, NOPULL, LEVEL1, &iomg084_edge_plus_ul_vx, &iocg084_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA4_EDGE_PLUS_UL_VX, "EMMC_DATA4", FUNC0, NOPULL, LEVEL1, &iomg085_edge_plus_ul_vx, &iocg085_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA5_EDGE_PLUS_UL_VX, "EMMC_DATA5", FUNC0, NOPULL, LEVEL1, &iomg086_edge_plus_ul_vx, &iocg086_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA6_EDGE_PLUS_UL_VX, "EMMC_DATA6", FUNC0, NOPULL, LEVEL1, &iomg087_edge_plus_ul_vx, &iocg087_edge_plus_ul_vx)
IOMUX_PIN(EMMC_DATA7_EDGE_PLUS_UL_VX, "EMMC_DATA7", FUNC0, NOPULL, LEVEL1, &iomg088_edge_plus_ul_vx, &iocg088_edge_plus_ul_vx)
IOMUX_PIN(GPIO_2_3_EDGE_PLUS_UL_VX, "GPIO_2_3", FUNC4, NOPULL, LEVEL0, &iomg143_edge_plus_ul_vx, &iocg143_edge_plus_ul_vx)
IOMUX_PIN(BOOT_SEL_EDGE_PLUS_UL_VX, "BOOT_SEL", FUNC0, PULLUP, LEVEL0, &iomg000_edge_plus_ul_vx, &iocg000_edge_plus_ul_vx)
IOMUX_PIN(GPIO_5_1_EDGE_PLUS_UL_VX, "GPIO_5_1", FUNC4, PULLDOWN, LEVEL0, &iomg097_edge_plus_ul_vx, &iocg097_edge_plus_ul_vx)
IOMUX_PIN(GPIO_5_2_EDGE_PLUS_UL_VX, "GPIO_5_2", FUNC4, PULLDOWN, LEVEL0, &iomg098_edge_plus_ul_vx, &iocg098_edge_plus_ul_vx)
IOMUX_PIN(PCM1_XCLK_EDGE_PLUS_UL_VX, "PCM1_XCLK", FUNC0, NOPULL, LEVEL0, &iomg034_edge_plus_ul_vx, &iocg034_edge_plus_ul_vx)
IOMUX_PIN(PCM1_XFS_EDGE_PLUS_UL_VX, "PCM1_XFS", FUNC0, NOPULL, LEVEL0, &iomg035_edge_plus_ul_vx, &iocg035_edge_plus_ul_vx)
IOMUX_PIN(PCM1_DI_EDGE_PLUS_UL_VX, "PCM1_DI", FUNC0, NOPULL, LEVEL0, &iomg036_edge_plus_ul_vx, &iocg036_edge_plus_ul_vx)
IOMUX_PIN(PCM1_DO_EDGE_PLUS_UL_VX, "PCM1_DO", FUNC0, NOPULL, LEVEL0, &iomg037_edge_plus_ul_vx, &iocg037_edge_plus_ul_vx)
IOMUX_PIN(I2S_XCLK_EDGE_PLUS_UL_VX, "I2S_XCLK", FUNC0, NOPULL, LEVEL0, &iomg026_edge_plus_ul_vx, &iocg026_edge_plus_ul_vx)
IOMUX_PIN(I2S_XFS_EDGE_PLUS_UL_VX, "I2S_XFS", FUNC0, NOPULL, LEVEL0, &iomg027_edge_plus_ul_vx, &iocg027_edge_plus_ul_vx)
IOMUX_PIN(I2S_DI_EDGE_PLUS_UL_VX, "I2S_DI", FUNC0, PULLDOWN, LEVEL0, &iomg028_edge_plus_ul_vx, &iocg028_edge_plus_ul_vx)
IOMUX_PIN(I2S_DO_EDGE_PLUS_UL_VX, "I2S_DO", FUNC0, NOPULL, LEVEL0, &iomg029_edge_plus_ul_vx, &iocg029_edge_plus_ul_vx)
IOMUX_PIN(PCM0_XCLK_EDGE_PLUS_UL_VX, "PCM0_XCLK", FUNC0, NOPULL, LEVEL0, &iomg030_edge_plus_ul_vx, &iocg030_edge_plus_ul_vx)
IOMUX_PIN(PCM0_XFS_EDGE_PLUS_UL_VX, "PCM0_XFS", FUNC0, NOPULL, LEVEL0, &iomg031_edge_plus_ul_vx, &iocg031_edge_plus_ul_vx)
IOMUX_PIN(PCM0_DI_EDGE_PLUS_UL_VX, "PCM0_DI", FUNC0, PULLDOWN, LEVEL0, &iomg032_edge_plus_ul_vx, &iocg032_edge_plus_ul_vx)
IOMUX_PIN(PCM0_DO_EDGE_PLUS_UL_VX, "PCM0_DO", FUNC0, NOPULL, LEVEL0, &iomg033_edge_plus_ul_vx, &iocg033_edge_plus_ul_vx)
IOMUX_PIN(HKADC_SSI_EDGE_PLUS_UL_VX, "HKADC_SSI", FUNC0, PULLDOWN, LEVEL0, &iomg050_edge_plus_ul_vx, &iocg050_edge_plus_ul_vx)
IOMUX_PIN(AUX_SSI0_EDGE_PLUS_UL_VX, "AUX_SSI0", FUNC0, PULLDOWN, LEVEL0, &iomg051_edge_plus_ul_vx, &iocg051_edge_plus_ul_vx)
IOMUX_PIN(AUX_SSI1_EDGE_PLUS_UL_VX, "AUX_SSI1", FUNC0, PULLDOWN, LEVEL0, &iomg052_edge_plus_ul_vx, &iocg052_edge_plus_ul_vx)
IOMUX_PIN(GPIO_5_0_EDGE_PLUS_UL_VX, "GPIO_5_0", FUNC2, NOPULL, LEVEL0, &iomg096_edge_plus_ul_vx, &iocg189_edge_plus_ul_vx)
IOMUX_PIN(UART0_RXD_EDGE_PLUS_UL_VX, "UART0_RXD", FUNC0, NOPULL, LEVEL0, &iomg053_edge_plus_ul_vx, &iocg053_edge_plus_ul_vx)
IOMUX_PIN(UART0_TXD_EDGE_PLUS_UL_VX, "UART0_TXD", FUNC0, NOPULL, LEVEL0, &iomg054_edge_plus_ul_vx, &iocg054_edge_plus_ul_vx)
IOMUX_PIN(RF_RESET1_EDGE_PLUS_UL_VX, "RF_RESET1", FUNC4, NOPULL, LEVEL0, &iomg147_edge_plus_ul_vx, &iocg147_edge_plus_ul_vx)
IOMUX_PIN(GPIO_6_2_EDGE_PLUS_UL_VX, "GPIO_6_2", FUNC0, NOPULL, LEVEL0, &iomg106_edge_plus_ul_vx, &iocg106_edge_plus_ul_vx)
IOMUX_PIN(GPIO_7_7_EDGE_PLUS_UL_VX, "GPIO_7_7", FUNC0, NOPULL, LEVEL0, &iomg119_edge_plus_ul_vx, &iocg119_edge_plus_ul_vx)
IOMUX_PIN(GPIO_4_0_EDGE_PLUS_UL_VX, "GPIO_4_0", FUNC0, NOPULL, LEVEL0, &iomg128_edge_plus_ul_vx, &iocg128_edge_plus_ul_vx)
IOMUX_PIN(RF_MIPI_CLK0_EDGE_PLUS_UL_VX, "RF_MIPI_CLK0", FUNC0, NOPULL, LEVEL0, &iomg154_edge_plus_ul_vx, &iocg154_edge_plus_ul_vx)
IOMUX_PIN(RF_MIPI_DATA0_EDGE_PLUS_UL_VX, "RF_MIPI_DATA0", FUNC0, PULLDOWN, LEVEL0, &iomg155_edge_plus_ul_vx, &iocg155_edge_plus_ul_vx)
IOMUX_PIN(APT_PDM0_EDGE_PLUS_UL_VX, "APT_PDM0", FUNC0, NOPULL, LEVEL0, &iomg089_edge_plus_ul_vx, &iocg190_edge_plus_ul_vx)
IOMUX_PIN(GPIO_7_5_EDGE_PLUS_UL_VX, "GPIO_7_5", FUNC0, PULLDOWN, LEVEL0, &iomg117_edge_plus_ul_vx, &iocg117_edge_plus_ul_vx)
IOMUX_PIN(RF_TCVR_ON0_EDGE_PLUS_UL_VX, "RF_TCVR_ON0", FUNC0, NOPULL, LEVEL0, &iomg150_edge_plus_ul_vx, &iocg150_edge_plus_ul_vx)
IOMUX_PIN(RF_SSI0_EDGE_PLUS_UL_VX, "RF_SSI0", FUNC0, PULLDOWN, LEVEL0, &iomg148_edge_plus_ul_vx, &iocg148_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_2_EDGE_PLUS_UL_VX, "RF_GPIO_2", FUNC0, NOPULL, LEVEL0, &iomg160_edge_plus_ul_vx, &iocg160_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_3_EDGE_PLUS_UL_VX, "RF_GPIO_3", FUNC0, NOPULL, LEVEL0, &iomg161_edge_plus_ul_vx, &iocg161_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_4_EDGE_PLUS_UL_VX, "RF_GPIO_4", FUNC0, NOPULL, LEVEL0, &iomg162_edge_plus_ul_vx, &iocg162_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_5_EDGE_PLUS_UL_VX, "RF_GPIO_5", FUNC0, NOPULL, LEVEL0, &iomg163_edge_plus_ul_vx, &iocg163_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_10_EDGE_PLUS_UL_VX, "RF_GPIO_10", FUNC0, NOPULL, LEVEL0, &iomg168_edge_plus_ul_vx, &iocg168_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_11_EDGE_PLUS_UL_VX, "RF_GPIO_11", FUNC0, NOPULL, LEVEL0, &iomg169_edge_plus_ul_vx, &iocg169_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_13_EDGE_PLUS_UL_VX, "RF_GPIO_13", FUNC0, NOPULL, LEVEL0, &iomg171_edge_plus_ul_vx, &iocg171_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_14_EDGE_PLUS_UL_VX, "RF_GPIO_14", FUNC0, NOPULL, LEVEL0, &iomg172_edge_plus_ul_vx, &iocg172_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_15_EDGE_PLUS_UL_VX, "RF_GPIO_15", FUNC0, NOPULL, LEVEL0, &iomg173_edge_plus_ul_vx, &iocg173_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_16_EDGE_PLUS_UL_VX, "RF_GPIO_16", FUNC0, NOPULL, LEVEL0, &iomg174_edge_plus_ul_vx, &iocg184_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_17_EDGE_PLUS_UL_VX, "RF_GPIO_17", FUNC0, NOPULL, LEVEL0, &iomg175_edge_plus_ul_vx, &iocg185_edge_plus_ul_vx)
IOMUX_PIN(RF_GPIO_18_EDGE_PLUS_UL_VX, "RF_GPIO_18", FUNC0, NOPULL, LEVEL0, &iomg176_edge_plus_ul_vx, &iocg186_edge_plus_ul_vx)
IOMUX_PIN(SD_CLK_EDGE_PLUS_UL_VX, "SD_CLK", FUNC0, NOPULL, LEVEL0, &iomg001_edge_plus_ul_vx, &iocg001_edge_plus_ul_vx)
IOMUX_PIN(SD_CMD_EDGE_PLUS_UL_VX, "SD_CMD", FUNC0, NOPULL, LEVEL0, &iomg002_edge_plus_ul_vx, &iocg002_edge_plus_ul_vx)
IOMUX_PIN(SD_DATA0_EDGE_PLUS_UL_VX, "SD_DATA0", FUNC0, NOPULL, LEVEL0, &iomg003_edge_plus_ul_vx, &iocg003_edge_plus_ul_vx)
IOMUX_PIN(SD_DATA1_EDGE_PLUS_UL_VX, "SD_DATA1", FUNC0, NOPULL, LEVEL0, &iomg004_edge_plus_ul_vx, &iocg004_edge_plus_ul_vx)
IOMUX_PIN(SD_DATA2_EDGE_PLUS_UL_VX, "SD_DATA2", FUNC0, NOPULL, LEVEL0, &iomg005_edge_plus_ul_vx, &iocg005_edge_plus_ul_vx)
IOMUX_PIN(SD_DATA3_EDGE_PLUS_UL_VX, "SD_DATA3", FUNC0, NOPULL, LEVEL0, &iomg006_edge_plus_ul_vx, &iocg006_edge_plus_ul_vx)


/*pin table*/
static struct iomux_pin_table pin_config_table_edge_plus_ul_vx[] = {
    PIN_TABLE("i2c0_scl", &I2C0_SCL_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c0_sda", &I2C0_SDA_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c1_scl", &I2C1_SCL_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c1_sda", &I2C1_SDA_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c2_scl", &I2C2_SCL_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c2_sda", &I2C2_SDA_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c3_scl", &I2C3_SCL_EDGE_PLUS_UL_VX),
    PIN_TABLE("i2c3_sda", &I2C3_SDA_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_mcam_pwdn", &ISP_GPIO0_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_mcam_vcm_pwdn", &ISP_GPIO2_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_mcam_id", &ISP_GPIO3_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_mcam_reset", &ISP_RESETB0_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_isp_mclk", &ISP_CCLK0_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_isp_sda0", &ISP_SDA0_EDGE_PLUS_UL_VX),
    PIN_TABLE("mcamera_isp_scl0", &ISP_SCL0_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_scam_pwdn", &ISP_GPIO1_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_scam_id", &ISP_GPIO4_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_scam_reset", &ISP_RESETB1_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_isp_mclk", &ISP_CCLK1_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_isp_sda1", &ISP_SDA1_EDGE_PLUS_UL_VX),
    PIN_TABLE("scamera_isp_scl1", &ISP_SCL1_EDGE_PLUS_UL_VX),
    PIN_TABLE("flash_strobe", &ISP_GPIO5_EDGE_PLUS_UL_VX),
    PIN_TABLE("flash_mask", &RF_GPIO_20_EDGE_PLUS_UL_VX),
    PIN_TABLE("key_up", &GPIO_4_2_EDGE_PLUS_UL_VX),
    PIN_TABLE("key_down", &GPIO_4_3_EDGE_PLUS_UL_VX),
    PIN_TABLE("lcd_lcm_en", &PWM_OUT1_EDGE_PLUS_UL_VX),
    PIN_TABLE("lcd_rst_n", &GPIO_4_6_EDGE_PLUS_UL_VX),
    PIN_TABLE("lcd_te0", &GPIO_4_7_EDGE_PLUS_UL_VX),
    PIN_TABLE("tp_rst_n", &GPIO_18_7_EDGE_PLUS_UL_VX),
    PIN_TABLE("bt_uart4_cts_n", &UART4_CTS_N_EDGE_PLUS_UL_VX),
    PIN_TABLE("bt_uart4_rts_n", &UART4_RTS_N_EDGE_PLUS_UL_VX),
    PIN_TABLE("bt_uart4_rxd", &UART4_RXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("bt_uart4_txd", &UART4_TXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("bt_ap_wakeup_bt", &GPIO_15_7_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_data3", &SDIO_DATA3_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_data2", &SDIO_DATA2_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_data1", &SDIO_DATA1_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_data0", &SDIO_DATA0_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_cmd", &SDIO_CMD_EDGE_PLUS_UL_VX),
    PIN_TABLE("wifi_sdio_clk", &SDIO_CLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_blanking", &RF_GPIO_1_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_uart3_cts_n", &UART3_CTS_N_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_uart3_rts_n", &UART3_RTS_N_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_uart3_rxd", &UART3_RXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_uart3_txd", &UART3_TXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("gps_fref_clk", &GPS_CLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("tcxo_afc_gul1", &TCXO0_AFC_EDGE_PLUS_UL_VX),
    PIN_TABLE("usima_clk_raw", &USIM0_CLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("usima_data_raw", &USIM0_DATA_EDGE_PLUS_UL_VX),
    PIN_TABLE("usima_rst_raw", &USIM0_RST_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_clk", &EMMC_CLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_cmd", &EMMC_CMD_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data0", &EMMC_DATA0_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data1", &EMMC_DATA1_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data2", &EMMC_DATA2_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data3", &EMMC_DATA3_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data4", &EMMC_DATA4_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data5", &EMMC_DATA5_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data6", &EMMC_DATA6_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_data7", &EMMC_DATA7_EDGE_PLUS_UL_VX),
    PIN_TABLE("emmc_rst_n", &GPIO_2_3_EDGE_PLUS_UL_VX),
    PIN_TABLE("boot_sel", &BOOT_SEL_EDGE_PLUS_UL_VX),
    PIN_TABLE("boot_jtag_sel0", &GPIO_5_1_EDGE_PLUS_UL_VX),
    PIN_TABLE("boot_jtag_sel1", &GPIO_5_2_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pa_i2s_xclk", &PCM1_XCLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pa_i2s_sync", &PCM1_XFS_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pa_soc_i2s_do", &PCM1_DI_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pcm1_do", &PCM1_DO_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_i2s_xclk", &I2S_XCLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_i2s_xfs", &I2S_XFS_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_i2s_di", &I2S_DI_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_i2s_do", &I2S_DO_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pcm0_xclk", &PCM0_XCLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pcm0_xfs", &PCM0_XFS_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pcm0_di", &PCM0_DI_EDGE_PLUS_UL_VX),
    PIN_TABLE("codec_pcm0_do", &PCM0_DO_EDGE_PLUS_UL_VX),
    PIN_TABLE("pmu_hkadc_ssi", &HKADC_SSI_EDGE_PLUS_UL_VX),
    PIN_TABLE("pmu_aux_ssi0", &AUX_SSI0_EDGE_PLUS_UL_VX),
    PIN_TABLE("pmu_aux_ssi1", &AUX_SSI1_EDGE_PLUS_UL_VX),
    PIN_TABLE("pmu_auxdac_en", &GPIO_5_0_EDGE_PLUS_UL_VX),
    PIN_TABLE("test_uart0_rxd", &UART0_RXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("test_uart0_txd", &UART0_TXD_EDGE_PLUS_UL_VX),
    PIN_TABLE("odt_gpio_9_6", &RF_RESET1_EDGE_PLUS_UL_VX),
    PIN_TABLE("switch_usb_sw_id", &GPIO_6_2_EDGE_PLUS_UL_VX),
    PIN_TABLE("switch_usb_sw_sel1", &GPIO_7_7_EDGE_PLUS_UL_VX),
    PIN_TABLE("charger_cd", &GPIO_4_0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rfpmu_mipi_clk0", &RF_MIPI_CLK0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rfpmu_mipi_data0", &RF_MIPI_DATA0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_pmu_apt_pdm0", &APT_PDM0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rfant_det0", &GPIO_7_5_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_tcvr_on0", &RF_TCVR_ON0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_ssi0", &RF_SSI0_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_2", &RF_GPIO_2_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_3", &RF_GPIO_3_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_4", &RF_GPIO_4_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_5", &RF_GPIO_5_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_10", &RF_GPIO_10_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_11", &RF_GPIO_11_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_13", &RF_GPIO_13_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_14", &RF_GPIO_14_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_15", &RF_GPIO_15_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_16", &RF_GPIO_16_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_17", &RF_GPIO_17_EDGE_PLUS_UL_VX),
    PIN_TABLE("rf_gpio_18", &RF_GPIO_18_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_clk", &SD_CLK_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_cmd", &SD_CMD_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_data0", &SD_DATA0_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_data1", &SD_DATA1_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_data2", &SD_DATA2_EDGE_PLUS_UL_VX),
    PIN_TABLE("sd_data3", &SD_DATA3_EDGE_PLUS_UL_VX),
    PIN_TABLE(NULL, NULL)
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_reg.h
  版 本 号   : 初稿
  作    者   : fansaihua
  生成日期   : 2013年3月15日
  最近修改   :
  功能描述   : pmic_reg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月15日
    作    者   : FANSAIHUA
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PMIC_REG_H__
#define __PMIC_REG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "pmic_common.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifndef BSP_REG
#define BSP_REG(base, reg) (*(volatile unsigned int *)((unsigned int)base + (reg)))
#endif

/* 将var中[pos, pos + bits-1]比特设置为val,  pos从0开始编号
   e.g BDOM_SET_BITS(var, 4, 2, 2) 表示将Bit5~4设置为b'10 */
#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((BSP_U32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((BSP_U32)((val) & (((BSP_U32)1 << (bits)) - 1)) << (pos)))

/* 获取var中[pos, pos + bits-1]比特值,  pos从0开始编号 */
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((unsigned int)1 << (bits)) - 1))

extern BSP_S32 pmic_reg_write(COMMON_REG_CFG* reg_cfg, BSP_U32 value);
extern BSP_S32 pmic_reg_read(COMMON_REG_CFG* reg_cfg, BSP_U32 *value);
extern BSP_S32 pmu_status_reg_read(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id);
extern BSP_S32 pmu_status_reg_clear(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id);
extern BSP_S32 pmic_status_reg_read(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id,BSP_U32* data_buf);
extern PMUIRQ_STAT* pmic_get_pmustat(void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of BSP_SSI.h */

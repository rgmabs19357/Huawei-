/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmicirq_driver.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmicirq_driver.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __PMIC_IRQ_DRIVER_INNER_H__
#define __PMIC_IRQ_DRIVER_INNER_H__

#include <mach/pmussi_drv.h>
#include "../../mntn/excDrv.h"
#include "drv_mailbox.h"
#include "bsp_mailbox.h"

#include "pmic_common.h"
#include "pmic_mntn.h"
#include "pmicirq_driver.h"
#include "pmic_reg.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern long systemErrorCcore(int modId, int arg1, int arg2, char *arg3, int arg3Length, unsigned long timeout);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drvAppInterface.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drvAppInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))
#include "CommAppInterface.h"
#endif
#pragma pack(4)

#include "MODULE/drv_charge.h"
#include "MODULE/drv_dpm.h"
#include "MODULE/drv_hkadc.h"
#include "MODULE/drv_modem_bsp.h"
#include "MODULE/drv_nv.h"
#include "MODULE/drv_oled.h"
#include "MODULE/drv_sd.h"
#include "MODULE/drv_usb.h"
#include "MODULE/drv_wifi.h"
#include "MODULE/drv_mntn.h"

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifndef __DRVAPPINTERFACE_H__
#define __DRVAPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



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












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drvAppInterface.h */


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : FcMacInterface.h
  版 本 号   : 初稿
  生成日期   : 2011年12月2日
  最近修改   :
  功能描述   : FcMacInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月2日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FCMACINTERFACE_H__
#define __FCMACINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "vos.h"
#include  "FcInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 消息头定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/* HSUPA最大速率, 注意约定使用FC_HSUPA_RATE_MAX_BPS表示不流控 */
#define FC_HSUPA_RATE_MAX_KBPS          ((VOS_UINT16)(0xFFFF))
#define FC_HSUPA_RATE_MAX_BPS           (FC_HSUPA_RATE_MAX_KBPS * 1024)


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : FC_UL_GetRate
 功能描述  : 控制HSUPA上行发送速率
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 流控限制比例
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月5日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 FC_UL_GetRate( VOS_VOID );


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of FcCstInterface.h */


/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ScFactory.h
  版 本 号   : 初稿
  生成日期   : 2012年4月16日
  最近修改   :
  功能描述   : SC模块
  函数列表   :
  修改历史   :
  1.日    期   : 2012年4月16日
    修改内容   : V7R1C51 锁网锁卡项目新增

******************************************************************************/

#ifndef __SCFACTORY_H__
#define __SCFACTORY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "ScInterface.h"
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     SC_HUK_LEN                  (16)        /* HUK的长度 */

#define     SC_IMEI_LEN                 (15)        /* IMEI的明文长度 */

#define     SC_IMEI_NV_LEN              (16)        /* IMEI NV明文长度 */

#define     SC_RAND_DATA_LEN            (4)         /* 随机数的字节数 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 枚举名    : SC_AUTH_STATUS_ENUM
 枚举说明  : 指定鉴权状态

  1.日    期   : 2012年04月07日
    修改内容   : AP-Modem锁网锁卡项目新增枚举
*****************************************************************************/
enum SC_AUTH_STATUS_ENUM
{
    SC_AUTH_STATUS_UNDO          = 0x00,             /* 未进行鉴权 */
    SC_AUTH_STATUS_DONE          = 0x01,             /* 已经鉴权 */
    SC_AUTH_STATUS_BUTT
};
typedef VOS_UINT8 SC_AUTH_STATUS_ENUM_UINT8;
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
 函 数 名  : SC_FAC_GetAuthStatus
 功能描述  : 获取产线鉴权状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC_AUTH_STATUS_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年04月07日
    修改内容   : AP-Modem锁网锁卡项目新增函数

*****************************************************************************/
extern SC_AUTH_STATUS_ENUM_UINT8 SC_FAC_GetAuthStatus(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

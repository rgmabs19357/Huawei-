/******************************************************************************

                  版权所有 (C), 2003-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AcpuReset.h
  版 本 号   : 初稿
  生成日期   : 2013年04月13日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2013年04月13日
    修改内容   : C核单独复位新增文件

******************************************************************************/
#ifndef _ACPU_RESET_H_
#define _ACPU_RESET_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "DrvInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define  RNIC_RESET_TIMEOUT_LEN                     (1000)                      /* RNIC复位的时间长度 */
#define  AT_RESET_TIMEOUT_LEN                       (1000)                      /* AT复位的时间长度 */
#define  ADS_RESET_TIMEOUT_LEN                      (1000)                      /* ADS复位的时间长度 */

#define  NAS_ADS_UL_FUNC_PROC_NAME                  "NAS_ADSUL"                 /* ADSUL注册给底软的名称 */
#define  NAS_ADS_DL_FUNC_PROC_NAME                  "NAS_ADSDL"                 /* ADSDL注册给底软的名称 */
#define  NAS_RNIC_FUNC_PROC_NAME                    "NAS_RNIC"                  /* RNIC注册给底软的名称 */
#define  NAS_AT_FUNC_PROC_NAME                      "NAS_AT"                    /* AT注册给底软的名称 */
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : ACPU_RESET_PRIORITY_ENUM
 枚举说明  : C核单独复位后ACPU重置的优先级
 1.日    期   : 2013年04月13日
   修改内容   : 创建
*****************************************************************************/
enum ACPU_RESET_PRIORITY_ENUM
{
    /* NAS ACPU各模块的优先级范围定的是20-29 */
    ACPU_RESET_PRIORITY_ADS_UL          = 20,                                   /* ADS UL复位 */
    ACPU_RESET_PRIORITY_ADS_DL,                                                 /* ADS DL复位 */
    ACPU_RESET_PRIORITY_RNIC,                                                   /* RNIC复位 */
    ACPU_RESET_PRIORITY_AT,                                                     /* AT复位 */
    ACPU_RESET_PRIORITY_BUTT
};
typedef VOS_INT32 ACPU_RESET_PRIORITY_ENUM_INT32;

/*****************************************************************************
 枚举名    : AT_RESET_REPORT_CAUSE_ENUM
 枚举说明  : ^RESET命令:复位原因值
 1.日    期   : 2013年04月17日
   修改内容   : 创建
*****************************************************************************/
enum AT_RESET_REPORT_CMD_ENUM
{
    AT_RESET_REPORT_CAUSE_CCPU_START = 0,
    AT_RESET_REPORT_CAUSE_CCPU_END,
    AT_RESET_REPORT_CAUSE_HIFI_START,
    AT_RESET_REPORT_CAUSE_HIFI_END,
    AT_RESET_REPORT_CMD_BUTT
};
typedef VOS_INT32 AT_RESET_REPORT_CAUSE_ENUM_UINT32;

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
枚举名    : ADS_RESET_MSG_ID_ENUM
枚举说明  : C核复位后通知ADS复位指示

  1.日    期   : 2013年04月12日
    修改内容   : 新建
*****************************************************************************/
enum ADS_RESET_MSG_ID_ENUM
{
    ID_CCPU_ADS_UL_RESET_START_IND          = 0x1001,                           /* CCPU复位前给UL的消息指示 */
    ID_CCPU_ADS_UL_RESET_END_IND            = 0x1002,                           /* CCPU复位后给UL的消息指示 */
    ID_CCPU_ADS_DL_RESET_START_IND          = 0x1003,                           /* CCPU复位前给DL的消息指示 */
    ID_CCPU_ADS_DL_RESET_END_IND            = 0x1004,                           /* CCPU复位后给DL的消息指示 */

    ID_ADS_RESET_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  ADS_RESET_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : RNIC_RESET_MSG_ID_ENUM
 枚举说明  : C核复位后通知RNIC复位消息
  1.日    期   : 2013年04月11日
    修改内容   : 创建
*****************************************************************************/
enum RNIC_RESET_MSG_ID_ENUM
{
    ID_CCPU_RNIC_RESET_START_IND        = 0x1001,                               /* CCPU复位前给RNIC的消息指示 */
    ID_CCPU_RNIC_RESET_END_IND          = 0x1002,                               /* CCPU复位后给RNIC的消息指示 */

    ID_RNIC_RESET_MSG_ID_ENUM_BUTT,
};
typedef VOS_UINT32 RNIC_RESET_MSG_ID_ENUM_UINT32;

/*****************************************************************************
枚举名    : AT_RESET_MSG_ID_ENUM
枚举说明  : CCPU/HIFI复位通知AT复位指示

  1.日    期   : 2013年04月12日
    修改内容   : 新建
*****************************************************************************/
enum AT_RESET_MSG_ID_ENUM
{
    /* 在AT给AT发的消息中，使用(AT_MSG_STRU)ucType来判别是什么消息的处理
       已经使用的是:0x00表示AT命令下发，0x01为结果上报，0x02为缓存命令处理
       本次新添加的AT给AT的消息ID值从0x10开始 */
    ID_CCPU_AT_RESET_START_IND          = 0x10,                                 /* CCPU复位前给AT的消息指示 */
    ID_CCPU_AT_RESET_END_IND            = 0x11,                                 /* CCPU复位后给AT的消息指示 */
    ID_HIFI_AT_RESET_START_IND          = 0x12,                                 /* HIFI复位前给AT的消息指示 */
    ID_HIFI_AT_RESET_END_IND            = 0x13,                                 /* HIFI复位后给AT的消息指示 */

    ID_AT_RESET_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  AT_RESET_MSG_ID_ENUM_UINT8;

/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : RNIC_CCPU_RESET_IND_STRU
 协议表格  :
 结构说明  : C核复位后给RNIC的消息指示
  1.日    期   : 2013年04月11日
    修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    RNIC_RESET_MSG_ID_ENUM_UINT32       enMsgId;                                /* 消息ID */    /* _H2ASN_Skip */
}RNIC_CCPU_RESET_IND_STRU;

/*****************************************************************************
结构名    : ADS_RESET_IND_STRU
结构说明  : CCPU复位后给ADS的消息结构

  1.日    期   : 2013年04月12日
    修改内容   : 创建
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头 */    /* _H2ASN_Skip */
    ADS_RESET_MSG_ID_ENUM_UINT32           enMsgId;                             /* 消息ID */    /* _H2ASN_Skip */
} ADS_CCPU_RESET_IND_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

/*****************************************************************************
  10 函数声明
*****************************************************************************/

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

#endif /* end of AcpuReset.h */



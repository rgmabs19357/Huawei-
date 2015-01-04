/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AdsLog.h
  版 本 号   : 初稿
  生成日期   : 2011年12月17日
  最近修改   :
  功能描述   : ADS LOG 打印
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月17日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __ADS_LOG_H__
#define __ADS_LOG_H__

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
#include "pslog.h"
#include "PsCommonDef.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*================================================*/
/* 数值宏定义 */
/*================================================*/
#define     ADS_MEM_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Mem Operation Failed!");
#define     ADS_MSG_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Msg Opration Failed!");
#define     ADS_TIMER_FAIL()            PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Timer Opration Failed!");

/*================================================*/
/* 功能函数宏定义 */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define ADS_LOG(String)\
    {\
        Print( (String) );\
        Print("\n");\
    }

#define ADS_LOG1(String, Para1)\
    {\
        Print ( (String) );\
        Print1( ",%d\n",(VOS_INT32)(Para1));\
    }

#define ADS_LOG2(String, Para1, Para2)\
    {\
        Print ( (String) );\
        Print2( ",%d,%d\n",(VOS_INT32)(Para1), (VOS_INT32)(Para2));\
    }

#define ADS_LOG3(String, Para1, Para2, Para3)\
    {\
        Print ( (String) );\
        Print3 ( ",%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) );\
    }

#define ADS_LOG4(String, Para1, Para2, Para3, Para4)\
    {\
        Print ( (String) );\
        Print4 ( ",%d,%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) );\
    }

#if 0
#define    ADS_INFO_LOG(Mod, String)                                    ADS_LOG( (String) )
#define    ADS_INFO_LOG1(Mod, String,Para1)                             ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_INFO_LOG2(Mod, String,Para1,Para2)                       ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_NORMAL_LOG(Mod, String)                                  ADS_LOG ( (String) )
#define    ADS_NORMAL_LOG1(Mod, String,Para1)                           ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_NORMAL_LOG2(Mod, String,Para1,Para2)                     ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_WARNING_LOG(Mod, String)                                 ADS_LOG ( (String) )
#define    ADS_WARNING_LOG1(Mod, String,Para1)                          ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_WARNING_LOG2(Mod, String,Para1,Para2)                    ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_ERROR_LOG(Mod, String)                                   ADS_LOG ( (String) )
#define    ADS_ERROR_LOG1(Mod, String,Para1)                            ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_ERROR_LOG2(Mod, String,Para1,Para2)                      ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )
#endif

#if 1
#define    ADS_INFO_LOG(Mod, String)                                    PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_INFO, (String) )
#define    ADS_INFO_LOG1(Mod, String,Para1)                             PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1) )
#define    ADS_INFO_LOG2(Mod, String,Para1,Para2)                       PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_NORMAL_LOG(Mod, String)                                  PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_NORMAL, (String) )
#define    ADS_NORMAL_LOG1(Mod, String,Para1)                           PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1) )
#define    ADS_NORMAL_LOG2(Mod, String,Para1,Para2)                     PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_WARNING_LOG(Mod, String)                                 PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_WARNING, (String) )
#define    ADS_WARNING_LOG1(Mod, String,Para1)                          PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1) )
#define    ADS_WARNING_LOG2(Mod, String,Para1,Para2)                    PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_ERROR_LOG(Mod, String)                                   PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_ERROR, (String) )
#define    ADS_ERROR_LOG1(Mod, String,Para1)                            PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1) )
#define    ADS_ERROR_LOG2(Mod, String,Para1,Para2)                      PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )
#endif

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
/*****************************************************************************
枚举名    : ADS_LOG_MSG_ID_ENUM
枚举说明  : ADS LOG消息类型

  1.日    期   : 2011年12月6日
    修改内容   : 定义ADS LOG消息类型
*****************************************************************************/
enum ADS_LOG_MSG_ID_ENUM
{
    ID_ADS_UL_LOG              = 0x1101,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_DL_LOG              = 0x1102,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_LOG_RPT_STATS_INFO  = 0x1103,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_LOG_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 ADS_LOG_MSG_ID_ENUM_UINT32;


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

typedef struct
{
    VOS_MSG_HEADER                                                              /* 消息头     */    /* _H2ASN_Skip */
    ADS_LOG_MSG_ID_ENUM_UINT32          enMsgId;                                /*  消息类型 */      /*  _H2ASN_Skip */
}ADS_LOG_HEAD_STRU;

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

#endif /* AdsLog.h */




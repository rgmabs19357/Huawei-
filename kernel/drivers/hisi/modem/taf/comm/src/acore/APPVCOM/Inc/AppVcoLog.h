/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AppVcomLog.h
  版 本 号   : 初稿
  生成日期   : 2011年12月17日
  最近修改   :
  功能描述   : APPVCOM LOG 打印
  函数列表   :

  修改历史   :
  1.日    期   : 2011年12月17日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __APPVCOM_LOG_H__
#define __APPVCOM_LOG_H__

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
#define     APPVCOM_MEM_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APPVCOM Mem Operation Failed!");
#define     APPVCOM_MSG_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APPVCOM Msg Opration Failed!");
#define     APPVCOM_TIMER_FAIL()            PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APPVCOM Timer Opration Failed!");

/*================================================*/
/* 功能函数宏定义 */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define APPVCOM_LOG(String)\
    {\
        Print( (String) );\
        Print("\n");\
    }

#define APPVCOM_LOG1(String, Para1)\
    {\
        Print ( (String) );\
        Print1( ",%d\n",(VOS_INT32)(Para1));\
    }

#define APPVCOM_LOG2(String, Para1, Para2)\
    {\
        Print ( (String) );\
        Print2( ",%d,%d\n",(VOS_INT32)(Para1), (VOS_INT32)(Para2));\
    }

#define APPVCOM_LOG3(String, Para1, Para2, Para3)\
    {\
        Print ( (String) );\
        Print3 ( ",%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) );\
    }

#define APPVCOM_LOG4(String, Para1, Para2, Para3, Para4)\
    {\
        Print ( (String) );\
        Print4 ( ",%d,%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) );\
    }


#define    APPVCOM_INFO_LOG(Mod, String)                                    APPVCOM_LOG( (String) )
#define    APPVCOM_INFO_LOG1(Mod, String,Para1)                             APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_INFO_LOG2(Mod, String,Para1,Para2)                       APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_NORMAL_LOG(Mod, String)                                  APPVCOM_LOG ( (String) )
#define    APPVCOM_NORMAL_LOG1(Mod, String,Para1)                           APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_NORMAL_LOG2(Mod, String,Para1,Para2)                     APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_WARNING_LOG(Mod, String)                                 APPVCOM_LOG ( (String) )
#define    APPVCOM_WARNING_LOG1(Mod, String,Para1)                          APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_WARNING_LOG2(Mod, String,Para1,Para2)                    APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    APPVCOM_ERROR_LOG(Mod, String)                                   APPVCOM_LOG ( (String) )
#define    APPVCOM_ERROR_LOG1(Mod, String,Para1)                            APPVCOM_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    APPVCOM_ERROR_LOG2(Mod, String,Para1,Para2)                      APPVCOM_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    APPVCOM_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                APPVCOM_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    APPVCOM_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          APPVCOM_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )


/*******************************************************************************
  3 枚举定义
*******************************************************************************/

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





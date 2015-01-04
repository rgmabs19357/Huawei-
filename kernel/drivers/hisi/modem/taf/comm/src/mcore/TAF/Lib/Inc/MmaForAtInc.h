/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmaForAtInc.h
  Version     : V200R001
  Date        : 2005-12-12
  Description : 该头文件定义了---单独为AT提供的接口与类型定义
  History     :
  1. Date:2005-12-12
     Modification:Create
  2.日    期   : 2006年08月09日
    修改内容   : 问题单A32D03479，在PC机上实现时将#pragma pack(0)和#pragma pack()加编译开关

  3.日    期   : 2006年09月20日
    修改内容   : 问题单A32D06255
************************************************************************/

#ifndef _MMA_FOR_AT_H_
#define _MMA_FOR_AT_H_


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*内部使用的参数查询宏定义*/
#define TAF_MMA_AT_QUERY_PARA_BEGIN (TAF_TELE_PARA_BUTT + 1)/*137*/
/*获取手机漫游状态*/
#define  TAF_PH_ROAM_STATUS_PARA    (TAF_MMA_AT_QUERY_PARA_BEGIN + 1)/*138*/
/*获取手机所处域信息*/
#define  TAF_PH_DOMAIN_PARA         (TAF_PH_ROAM_STATUS_PARA + 1)/*139*/
/*GMR命令，获取mobile software revision, release date, release time*/
#define  TAF_PH_GMR_PARA            (TAF_PH_DOMAIN_PARA + 1)/*140*/
/*产品名称，GMM，CGMM使用*/
#define  TAF_PH_PRODUCT_NAME_PARA   (TAF_PH_GMR_PARA + 1)/*141*/


/*暂时不支持的频带定义*/
/*
  10000（CM_BAND_PREF_GSM_450）                GSM 450
  20000（CM_BAND_PREF_GSM_480）                GSM 480
  40000（CM_BAND_PREF_GSM_750）                GSM 750
  80000（CM_BAND_PREF_GSM_850）                GSM 850
  800000（CM_BAND_PREF_WCDMA_II_PCS_1900）     WCDMA PCS
  1000000（CM_BAND_PREF_WCDMA_III_1700）       WCDMA 1700
*/
#define TAF_PH_BAND_PREF_GSM_450                                  0x10000
#define TAF_PH_BAND_PREF_GSM_480                                  0x20000
#define TAF_PH_BAND_PREF_GSM_750                                  0x40000
#define TAF_PH_BAND_PREF_WCDMA_II_PCS_1900                        0x800000
#define TAF_PH_BAND_PREF_WCDMA_III_1700                           0x1000000



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
  8 OTHERS定义
*****************************************************************************/

TAF_UINT32 Taf_DefPhFreq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId,
                         TAF_UINT32 ulDlFreqHighFreq,
                         TAF_UINT32 ulDlFreqLowFreq,
                         TAF_UINT8  ucRadioAccessMode);

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

#endif /* end of MmaForAtInc.h*/


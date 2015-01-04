/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LNvCommon.h
  Description     : LNvCommon.h header file
  History           :
     1.Name+ID      yyyy-mm-dd  Draft Enact

******************************************************************************/

#ifndef __LNVCOMMON_H__
#define __LNVCOMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "LNvId.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/


/* 非标准频段 begin */
#define LTE_COMM_NONSTANDARD_BAND_BEGIN                     101
#define LTE_COMM_NONSTANDARD_BAND_END                       116

#define LTE_COMM_NONSTANDARD_BAND_MAX_COUNT                 16
/* 非标准频段 end */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/



/*****************************************************************************
 枚举名    : LRRC_LTE_MODE_TYPE_ENUM_UINT16
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE模式类型
*****************************************************************************/
enum LTE_COMM_BAND_MODE_TYPE_ENUM
{
    LTE_COMM_BAND_MODE_TYPE_FDD                = 0,                             /* LTE FDD 制式 */
    LTE_COMM_BAND_MODE_TYPE_TDD                = 1,                             /* LTE TDD 制式 */
    LTE_COMM_BAND_MODE_TYPE_BUTT
};
typedef VOS_UINT8 LTE_COMM_BAND_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名    : LTE_NON_STANDARD_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 非标频段的频点信息相关的数据结构,与36101 talbe 5.7.3-1对应

            RealFreq = usFLow + (RealArfcn - usRangOfNLow),
            其中 RealFreq 真实的频点信息；usRangOfNLow、usFLow从NV项中获取，具体含义
            见数据结构中的说明; RealArfcn实际的arfcn。
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usFLow;                           /* 起始频点，单位是100khz */
    VOS_UINT16                                usFHigh;                          /* 结束频点，单位是100khz */
    VOS_UINT16                                usRangOfNLow;                     /* Nlow,与Noffset一致 */
    VOS_UINT16                                usRangOfNHigh;                    /* Nhigh*/
}LTE_COMM_NON_STANDARD_FREQ_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_NON_STANDARD_POWER_CLASS_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 非标频段power class相关的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 usUEPowerClass;
    VOS_INT16                                  sPowerToleranceHigh;    /* 单位 0.1dBm */
    VOS_INT16                                  sPowerToleranceLow;     /* 单位 0.1dBm */
    VOS_UINT8                                  aucReservered[2];
}LTE_COMM_NON_STANDARD_POWER_CLASS_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_NON_STANDARD_BAND_TEST_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 非标频段的测试信息相关的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucBandWidth;                       /* 带宽，单位0.1MHz，可选值14;30;50;150;200 */
    VOS_UINT8                                   aucReservered[3];
    VOS_UINT16                                  usTestFreqs[3];                    /* 测试低、中、高频点，单位0.1MHz */
    VOS_INT16					                sRxRefSensPower;                   /* 下行测试灵敏度功率，单位0.1dBm */
    VOS_UINT32                                  aulReservered[16];
}LTE_NON_STANDARD_BAND_TEST_INFO_STRU;

/*****************************************************************************
 结构名    : LTE_NON_STANDARD_BAND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 非标频段的频点信息相关的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucBandID;                       /* band iD */
    LTE_COMM_BAND_MODE_TYPE_ENUM_UINT8          enBandMode;
    VOS_INT16                                   sTxRxFreqSepara;
    LTE_COMM_NON_STANDARD_FREQ_INFO_STRU        stUlFreqInfo;
    LTE_COMM_NON_STANDARD_FREQ_INFO_STRU        stDlFreqInfo;
    LTE_COMM_NON_STANDARD_POWER_CLASS_INFO_STRU stUePowerClassInfo;
    LTE_NON_STANDARD_BAND_TEST_INFO_STRU		stTestInfo[6];                 /*1.4MHz；3MHz；5MHz,10MHz,15MHz；20MHz带宽的测试参数 */
    VOS_UINT32                                  aulReservered[16];
}LTE_COMM_NON_STANDARD_BAND_COMM_STRU;




/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of PsNvInterface.h */


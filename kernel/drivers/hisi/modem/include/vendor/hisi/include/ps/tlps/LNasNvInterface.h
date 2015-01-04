/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
  File Name       : LNasNvInterface.h
  Description     : LNasNvInterface.h header file
  History           :
      1.zhengjunyan 00148421 2009.04.17 New Draft
******************************************************************************/

#ifndef __LNASNVINTERFACE_H__
#define __LNASNVINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "AppNasComm.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpPlmnId :1;
    VOS_UINT32                          bitRsv      :31;

    NAS_MM_PLMN_ID_STRU                 stPlmnId;
}LNAS_LMM_NV_PLMNID_STRU;


typedef struct
{
    VOS_UINT32                          bitOpRaMod :1;
    VOS_UINT32                          bitRsv      :31;

    NAS_MM_RAT_TYPE_ENUM_UINT32         enRaMod;
}LNAS_LMM_NV_RAMOD_STRU;


typedef struct
{
    VOS_UINT32                          bitOpUeNetCap   :1;
    VOS_UINT32                          bitRsv          :31;

    NAS_MM_UE_NET_CAP_STRU              stUeNetCap;
}LNAS_LMM_NV_UE_NET_CAP_STRU;


typedef struct
{
    VOS_UINT32                          bitOpMsNetCap   :1;
    VOS_UINT32                          bitRsv          :31;

    NAS_MM_MS_NET_CAP_STRU              stMsNetCap;
}LNAS_LMM_NV_MS_NET_CAP_STRU;


typedef struct
{
    VOS_UINT32                          bitOpNvDrx      :1;
    VOS_UINT32                          bitRsv          :31;

    NAS_MM_DRX_STRU                     stNvDrx;
}LNAS_LMM_NV_DRX_STRU;


typedef struct
{
    VOS_UINT32                          bitOpImsi     :1;
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           aucImsi[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_IMSI_STRU;


typedef struct
{
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           aucImei[NAS_MM_MAX_UEID_BUF_SIZE];
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_IMEI_STRU;

typedef struct
{
    VOS_UINT32                          bitOpGuti     :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpTai      :1;
    VOS_UINT32                          bitOpUpState  :1;
    VOS_UINT32                          bitOpRsv      :29;

    NAS_MM_GUTI_STRU                    stGuti;
    NAS_MM_TA_STRU                      stLastRegTai;
    NAS_MM_UPDATE_STATE_ENUM_UINT32     enUpdateState;
}LNAS_LMM_NV_EPS_LOC_STRU;


typedef struct
{
    VOS_UINT32                          bitOpNvPlmn  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;

    NAS_MM_PLMN_LIST_STRU               stPlmnList;
}LNAS_LMM_NV_PLMN_LIST_STRU;
typedef LNAS_LMM_NV_PLMN_LIST_STRU      LNAS_LMM_NV_EPLMN_LIST_STRU;
typedef LNAS_LMM_NV_PLMN_LIST_STRU      LNAS_LMM_NV_FPLMN_LIST_STRU;
typedef LNAS_LMM_NV_PLMN_LIST_STRU      LNAS_LMM_NV_LPLMN_LIST_STRU;
typedef LNAS_LMM_NV_PLMN_LIST_STRU      LNAS_LMM_NV_UPLMN_LIST_STRU;
typedef LNAS_LMM_NV_PLMN_LIST_STRU      LNAS_LMM_NV_OPLMN_LIST_STRU;

typedef struct
{
    VOS_UINT32                          bitOpNvPlmn  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv     :31;

    NAS_MM_PLMN_ACT_LIST_STRU           stHplmnActList;
}LNAS_LMM_NV_HPLMN_ACT_LIST_STRU;

typedef struct
{
    VOS_UINT32                          bitOpNvLRplmnSI  :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;

    NAS_MM_LRPLMNSI_ENUM_UINT8          enLRplmnSI;
    VOS_UINT8                           aucRsv[3];
}LNAS_LMM_NV_LRPLMNSI_STRU;


typedef struct
{
    VOS_UINT32                          bitOpHplmnPeri :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    VOS_UINT32                          ulHplmnPeriTimerLen;
}LNAS_LMM_NV_HPLMN_PERI_STRU;

typedef struct
{
    VOS_UINT32                          bitOpMncLen :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    VOS_UINT8                           ucMncLen;
    VOS_UINT8                           aucReserved1[3];
}LNAS_LMM_NV_MNC_LEN_STRU;

typedef struct
{
    VOS_UINT32                          bitOpMsClassMark :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    NAS_MM_MS_CLASSMARK_STRU            stMsClassMark;
}LNAS_LMM_NV_MS_CLASSMARK_STRU;

typedef struct
{
    VOS_UINT32                          bitOpPlmnSelMod               :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpAvailablePlmnSelTimerLen :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :30;
    NAS_MM_SEL_MODE_ENUM_UINT32         enPlmnSelMode;
    VOS_UINT32                          ulAvailablePlmnSelTimerLen;
}LNAS_LMM_NV_PLMN_SEL_CONFIG_STRU;


typedef struct
{
    VOS_UINT32                          bitOpAccClassMark :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    VOS_UINT16                          usAccClassMark;
    VOS_UINT8                           aucReserved1[2];
}LNAS_LMM_NV_ACC_CLASSMARK_STRU;

typedef struct
{
    VOS_UINT32                          bitOpAutoStart  :1;
    VOS_UINT32                          bitRsv          :31;

    VOS_UINT32                          ulAutoStartFlag;
}LNAS_LMM_NV_AUTO_START_STRU;


typedef struct
{
    VOS_UINT32                          bitOpUsimFeature :1;
    VOS_UINT32                          bitRsv           :31;

    VOS_UINT32                          ulUsimFeature;
}LNAS_LMM_NV_USIM_FEATURE_STRU;

typedef struct
{
    VOS_UINT32                          bitOpEpsSec   :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;

    VOS_UINT8                           ucKSIsgsn;
    VOS_UINT8                           ucKSIasme;
    VOS_UINT8                           ucSecuAlg;
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucKasme[NAS_MM_AUTH_KEY_ASME_LEN];
    VOS_UINT32                          ulUlNasCount;
    VOS_UINT32                          ulDlNasCount;
}LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU;

typedef struct
{
    VOS_UINT32                          bitOpUsimControl   :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;
    NAS_EMM_USIM_CONTROL_STRU           stUsimControl;
}LNAS_LMM_NV_USIM_CONTROL_STRU;

typedef struct
{
    VOS_UINT32                          bitOpSoftUsimAuthParam :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv               :31;
    NAS_EMM_SOFT_USIM_AUTH_PARAM_STRU   stSoftUsimAuthParam;
}LNAS_LMM_NV_SOFT_USIM_AUTH_PARAM_STRU;

/* modified by lihong00150010 2012-07-31 cs+ps1 begin */
#if 0
typedef struct
{
    VOS_UINT32                          bitOpUeMode         :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;
    /*    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32         enUeMode; H41410 FOR UE MODE */
    NAS_LMM_GU_UE_MODE_ENUM_UINT32      enUeMode;
}LNAS_LMM_NV_UE_OPERATION_MODE_STRU;
#endif
typedef struct
{
    VOS_UINT32                          bitOpUeCenter       :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;

    LNAS_LMM_UE_CENTER_ENUM_UINT32      enUeCenter;
}LNAS_LMM_NV_UE_CENTER_STRU;
/* modified by lihong00150010 2012-07-31 cs+ps1 end */

typedef struct
{
    VOS_UINT32                          bitOpCsService      :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;
    NAS_LMM_CS_SERVICE_ENUM_UINT32      enCsService;
}LNAS_LMM_NV_CS_SERVICE_STRU;


typedef struct
{
    VOS_UINT32                          bitOpVoicDomain     :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32    enVoicDomain;
}LNAS_LMM_NV_VOICE_DOMAIN_STRU;


/*R10 modify begin for leili*/
typedef struct
{
    VOS_UINT32                          bitOpReleaseName    :1;       /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv            :31;

    VOS_UINT32                          ulReleaseName;

}LNAS_LMM_NV_NAS_RELEASE_STRU;
/*R10 modify end for leili*/


/*self-adaption NW cause modify begin for leili*/
typedef LNAS_LMM_CONFIG_NWCAUSE_STRU        LNAS_LMM_NV_CONFIG_NWCAUSE_STRU;

/*self-adaption NW cause modify end for leili*/

typedef struct
{
    VOS_UINT32                          bitOpAttachBearerReest   :1;   /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv                 :31;
    VOS_UINT32                          ulReestTimeLen;
}LNAS_ESM_NV_ATTACH_BEARER_REEST_STRU;


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










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmcEmmInterface.h */





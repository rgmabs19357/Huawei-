/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : che_om_def.h
  版 本 号   : 初稿
  生成日期   : 2011年1月12 日
  最近修改   :
  功能描述   : 定义CHE模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年1月12日
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __CHE_OM_DEF_H__
#define __CHE_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
#define    CHE_LCR_VELOCITY_DECI_FDD    12
#define    CHE_COR_COEF_THRE_NUM        6
#define    CHE_SFLAG_FACTOR_NUM         9




typedef enum __LPHY_REQ_CHE__
{
    LPHY_REQ_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_CHE_PDCCH_EN,
    LPHY_REQ_CHE_PDSCH_EN,
    LPHY_REQ_CHE_SG_EN,
    LPHY_REQ_CHE_RPT_TM_CPE_AGC_EN,          /*0x30380005*/
    LPHY_REQ_CHE_RPT_INTP_PREP_EN,           /*0x30380006*/
    LPHY_REQ_CHE_RPT_ALPHA_FILTER_EN,        /*0x30380007*/
    LPHY_REQ_CHE_STUB_SNR_FLAG_EN,           /*0x30380008*/
    LPHY_REQ_CHE_STUB_VELO_FLAG_EN,          /*0x30380009*/
    LPHY_REQ_CHE_STUB_TRMS_FLAG_EN,          /*0x3038000a*/
    LPHY_REQ_CHE_STUB_INIT_SUBFRM_EN,        /*0x3038000b*/
    LPHY_REQ_CHE_STUB_LAST_SUBFRM_EN,        /*0x3038000c*/
    LPHY_REQ_CHE_STUB_DAGC_GAIN_EN,          /*0x3038000d*/
    LPHY_REQ_CHE_STUB_BF_SCENE_FLAG_EN,      /*0x3038000e*/
    LPHY_REQ_CHE_THRED_DRS_CRS_RSRP_EN,      /*0x3038000f*/
    LPHY_REQ_CHE_THRED_DAGC_STEP_FACTOR_EN,  /*0x30380010*/
    LPHY_REQ_CHE_THRED_VEL_CR_EN,            /*0x30380011*/
    LPHY_REQ_CHE_THRED_VEL_LCR_EN,           /*0x30380012*/
    LPHY_REQ_CHE_THRED_SNR_EN,               /*0x30380013*/
    LPHY_REQ_CHE_IRC_RUU_DIAG_EN,            /*0x30380014*/
    LPHY_REQ_CHE_IRC_FIXED_N1_EN,            /*0x30380015*/
    LPHY_REQ_CHE_MBMS_SG_EN,                 /*0x30380016*/
    LPHY_REQ_CHE_MBMS_RPT_TM_AGC_ALPHA_EN,   /*0x30380017*/
    LPHY_REQ_CHE_MBMS_STUB_SNR_EN,           /*0x30380018*/
    LPHY_REQ_CHE_MBMS_STUB_VELO_EN,          /*0x30380019*/
    LPHY_REQ_CHE_MBMS_STUB_DOPPLER_EN,       /*0x3038001a*/
    LPHY_REQ_CHE_MBMS_STUB_TINTERP_EN,       /*0x3038001b*/
    LPHY_REQ_CHE_MBMS_STUB_ALPHA_EN,         /*0x3038001c*/
    LPHY_REQ_CHE_MBMS_STUB_ALPHA_CLOSE_EN,   /*0x3038001d*/
    LPHY_REQ_CHE_CRS_STUB_ALPHA_CLOSE_EN,    /*0x3038001e*/
    LPHY_REQ_CHE_STUB_BF_SNR_STEP_EN         /*0x3038001f*/

}LPHY_CHE_REQ_ENUM;
/* END: Added by l00174474, 2011/6/8*/

typedef enum
{
    LPHY_REQ_CHE_EN_CLOSE = 0,
    LPHY_REQ_CHE_EN_OPEN
} LPHY_CHE_REQ_ENABLE_ENUM;

typedef  UINT16  LPHY_CHE_REQ_ENABLE_ENUM_UINT16;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPbCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PBCH_EN_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPdcCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PDCCH_EN_STRU;


typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usPdsCheInfoEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_PDSCH_EN_STRU;

typedef struct
{
    LPHY_REQ_CHE_PBCH_EN_STRU     stPbReportSwitch;
    LPHY_REQ_CHE_PDCCH_EN_STRU    stPdcReportSwitch;
    LPHY_REQ_CHE_PDSCH_EN_STRU    stPdsReportSwitch;

} LPHY_REQ_CHE_SWITCH_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheSGEn;          /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_SG_EN_STRU;

/*Timing, CPE, AGC*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheTimingCpeAgcEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_RPT_TM_CPE_AGC_EN_STRU;


/*INTP  and  Preprocessing*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheIntpPrepEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_RPT_INTP_PREP_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheAlphaEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv0;
} LPHY_REQ_CHE_RPT_ALPHA_FILTER_EN_STRU;

/*STUB*/
typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheSnrStubEn;
    INT16                              sSnrFlagRx0;
    INT16                              sSnrFlagRx1;
    INT16                              sRsv0;
} LPHY_REQ_CHE_STUB_SNR_FLAG_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheVelStubEn;
    INT16                              sVeloFlag;
} LPHY_REQ_CHE_STUB_VELO_FLAG_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheTrmsStubEn;
    INT16                              sTrmsFlag;

} LPHY_REQ_CHE_STUB_TRMS_FLAG_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheInitSubFrmStubEn;
    INT16                              sRsv0;
} LPHY_REQ_CHE_STUB_INIT_SUBFRM_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheLastSubFrmStubEn;
    INT16                              sRsv0;
} LPHY_REQ_CHE_STUB_LAST_SUBFRM_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheDAgcGainStubEn;
    UINT16                             usDAgcGain;
} LPHY_REQ_CHE_STUB_DAGC_GAIN_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheBFSceneStubEn;
    UINT16                             usSceneFlag;

} LPHY_REQ_CHE_STUB_BF_SCENE_FLAG_EN_STRU;

/*THRESHOLD CONFIGURATION*/

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheDCrsRsrpThreEn;
    UINT16                           usLimitThre;
} LPHY_REQ_CHE_THRED_DRS_CRS_RSRP_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheDagcFactorEn;
    UINT16                           usDagcFactor;

} LPHY_REQ_CHE_THRED_DAGC_STEP_FACTOR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheCRThreEn;
    UINT16                           ausTrms01[CHE_COR_COEF_THRE_NUM];
    UINT16                           ausTrms2[CHE_COR_COEF_THRE_NUM];
} LPHY_REQ_CHE_THRED_VEL_CR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheLCRThreEn;
    UINT8                            aucLcrVel[CHE_LCR_VELOCITY_DECI_FDD];

} LPHY_REQ_CHE_THRED_VEL_LCR_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16  usCheSNRThreEn;
    UINT32                           aulSFlagThre[CHE_SFLAG_FACTOR_NUM];

} LPHY_REQ_CHE_THRED_SNR_EN_STRU;

/*IRC debug switch*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usDiagSetZeroEn;     /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_IRC_RUU_DIAG_EN_STRU;

typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usFixedN1En;         /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_IRC_FIXED_N1_EN_STRU;

/*MBMS*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCheMbmsSGEn;          /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_MBMS_SG_EN_STRU;

/*MBMS Timing, CPE, AGC*/
typedef struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usTimingAgcAlphaEn;    /*1 使能上报, 0关闭上报*/
    UINT16                             usRsv;
} LPHY_REQ_CHE_MBMS_RPT_TM_AGC_ALPHA_EN_STRU;

/*STUB*/
typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usSnrStubEn;
    UINT16                             sRsv0;
    UINT16                             usTdSnrFlagRx0;
    UINT16                             usTdSnrFlagRx1;
    UINT16                             usFdSnrFlagRx0;
    UINT16                             usFdSnrFlagRx1;
    UINT16                             usAlpSnrFlagRx0;
    UINT16                             usAlpSnrFlagRx1;

} LPHY_REQ_CHE_MBMS_STUB_SNR_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usVelStubEn;
    INT16                              sVeloFlag;
} LPHY_REQ_CHE_MBMS_STUB_VELO_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usDoppStubEn;
    UINT16                             usDoppFlag;
} LPHY_REQ_CHE_MBMS_STUB_DOPPLER_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usTrmsStubEn;
    UINT16                             usTInterpFlag;

} LPHY_REQ_CHE_MBMS_STUB_TINTERP_EN_STRU;

typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usAlphaStubEn;
    UINT16                             Rsv;
    UINT16                             usDemAlpha;
    UINT16                             usRuuAlpha;

} LPHY_REQ_CHE_MBMS_STUB_ALPHA_EN_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usMbmsAlphaCloseStubEn;
    UINT16                             Rsv;

} LPHY_REQ_CHE_MBMS_STUB_ALPHA_CLOSE_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usCrsAlphaCloseStubEn;
    UINT16                             Rsv;
} LPHY_REQ_CHE_CRS_STUB_ALPHA_CLOSE_STRU;


typedef  struct
{
    LPHY_CHE_REQ_ENABLE_ENUM_UINT16    usBfSnrStubEn;
    UINT16                             usStep;

} LPHY_REQ_CHE_STUB_BF_SNR_STEP_STRU;


/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_CHE__
{
    LPHY_CNF_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_CNF, 0x1),
    LPHY_CNF_CHE_PDCCH_EN,
    LPHY_CNF_CHE_PDSCH_EN,
    LPHY_CNF_CHE_SG_EN,
    LPHY_CNF_CHE_RPT_TM_CPE_AGC_EN,
    LPHY_CNF_CHE_RPT_INTP_PREP_EN,
    LPHY_CNF_CHE_RPT_ALPHA_FILTER_EN,
    LPHY_CNF_CHE_STUB_SNR_FLAG_EN,
    LPHY_CNF_CHE_STUB_VELO_FLAG_EN,
    LPHY_CNF_CHE_STUB_TRMS_FLAG_EN,
    LPHY_CNF_CHE_STUB_INIT_SUBFRM_EN,
    LPHY_CNF_CHE_STUB_LAST_SUBFRM_EN,
    LPHY_CNF_CHE_STUB_DAGC_GAIN_EN,
    LPHY_CNF_CHE_STUB_BF_SCENE_FLAG_EN,
    LPHY_CNF_CHE_THRED_DRS_CRS_RSRP_EN,
    LPHY_CNF_CHE_THRED_DAGC_STEP_FACTOR_EN,
    LPHY_CNF_CHE_THRED_VEL_CR_EN,
    LPHY_CNF_CHE_THRED_VEL_LCR_EN,
    LPHY_CNF_CHE_THRED_SNR_EN,
    LPHY_CNF_CHE_IRC_RUU_DIAG_EN,
    LPHY_CNF_CHE_IRC_FIXED_N1_EN,
    LPHY_CNF_CHE_MBMS_SG_EN,
    LPHY_CNF_CHE_MBMS_RPT_TM_AGC_ALPHA_EN,
    LPHY_CNF_CHE_MBMS_STUB_SNR_EN,
    LPHY_CNF_CHE_MBMS_STUB_VELO_EN,
    LPHY_CNF_CHE_MBMS_STUB_DOPPLER_EN,
    LPHY_CNF_CHE_MBMS_STUB_TINTERP_EN,
    LPHY_CNF_CHE_MBMS_STUB_ALPHA_EN

} LPH_CNF_CHE_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_CHE__
{
    LPHY_IND_CHE_PBCH_EN             = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_IND, 0x1),
    LPHY_IND_CHE_PDCCH_EN,
    LPHY_IND_CHE_PDSCH_EN,
    LPHY_IND_CHE_SG_EN,
    LPHY_IND_CHE_RPT_TM_CPE_AGC_EN,      /*0x303f0005*/
    LPHY_IND_CHE_RPT_INTP_PREP_EN,       /*0x303f0006*/
    LPHY_IND_CHE_RPT_ALPHA_FILTER_EN,    /*0x303f0007*/
    LPHY_IND_CHE_MBMS_SG_EN,             /*0x303f0008*/
    LPHY_IND_CHE_MBMS_RPT_TM_AGC_ALPHA   /*0x303f0009*/

} LPHY_IND_CHE_ENUM;


typedef struct __LPHY_CHE_IND_PHY_CHANNEL_REPORT_
{
    UINT8       ucActiveFlag;                 /*激活标志*/
    UINT8       ucRsv0;
    UINT16      usSFN;                        /*系统帧号*/
    UINT16      usSubFN;                      /*子帧号*/
    UINT8       ucRsSelVel;                   /*RS选择的速度*/
    UINT8       ucPdcPreVel;                  /*PDC的预处理速度*/
    UINT32      aCheInfo[20];                 /*总的输入信息*/
    UINT32      aPhChInfo[40];                /*物理信道寄存器信息*/
} LPHY_IND_CHE_PHY_CHANNEL_REPORT_STRU;


typedef struct
{
    UINT16  usDoppler;                    /*多普勒频移               */
    UINT16  usBfSnrRx0;                   /*BF SNR档位Rx0            */
    UINT16  usBfSnrRx1;                   /*BF SNR档位Rx1            */
    UINT16  usTrms;                       /*时延估计档位索引         */
    UINT16  usNonBfSnrRx0;                /*非BF模式SNR档位Rx0       */
    UINT16  usNonBfSnrRx1;                /*非BF模式SNR档位Rx1       */
    UINT16  usVelocityFlag;               /*速度指示                 */
    INT16   sVelofCorr;                   /*相关系数的速度判别结果   */
    INT32   lTDCorrCoef;                  /*相关系数的时域相关系数   */
    INT32   lFDCorrCoef;                  /*相关系数的频域相关系数   */
    INT16   sOutVelocity;                 /*raw outvelocity*/
    UINT16  usLcrPar;
    UINT32  ulDrsRsrpRx0;                 /*DRS RSRP0*/
    UINT32  ulDrsRsrpRx1;
    INT16   sRsv0;
    INT16   sRsv1;
    UINT16  usRsv2;
    UINT16  usRsv3;
    INT32   lRsv4;
    INT32   lRsv5;
} LPHY_IND_CHE_SG_EN_STRU;

typedef struct
{
    UINT8   ucTimeSnrRx0;                 /*TSNR档位Rx0             */
    UINT8   ucTimeSnrRx1;                 /*TSNR档位Rx1             */
    UINT8   ucFreqSnrRx0;                 /*FSNR档位Rx0             */
    UINT8   ucFreqSnrRx1;                 /*FSNR档位Rx1             */

    UINT8   usDoppler;                    /*Doppler指示              */
    UINT8   usTrms;                       /*时延估计档位索引         */
    INT8    Rsv0;
    INT8    Rsv1;

    INT32   lTDCorrCoef;                  /*MRS相关系数的时域相关系数   */
    INT32   lFDCorrCoef;                  /*MRS相关系数的频域相关系数   */

    INT8    cCrvForPmch;                  /*CRS相关系数的速度判别结果  */
    INT8    cMCrv;                        /*MRS相关系数的速度判别结果  */
    INT8    cCfv;                         /*CFV  */
    INT8    cIirVelFlag;                  /*速度估计总档位  */

    INT16   Rsv2;
    INT16   Rsv3;

} LPHY_IND_CHE_EMBMS_SG_EN_STRU;


/*Timing, CPE, AGC*/
typedef  struct
{
    UINT16   usLeftTimingDiff;
    UINT16   usRightTimingDiff;
    UINT16   usAgcLeftAmpgainRx0;
    UINT16   usAgcLeftAmpgainRx1;
    UINT16   usAgcLeftPowGainRx0;
    UINT16   usAgcLeftPowGainRx1;
    UINT16   usCpeLeftGainRx0;
    UINT16   usCpeLeftGainRx1;
    UINT16   usCpeRightGainRx0;
    UINT16   usCpeRightGainRx1;

} LPHY_IND_CHE_RPT_TM_CPE_AGC_EN_STRU;

typedef struct  _LPHY_CHE_INTP_COEF_STRU
{
    UINT8   ucLeft;
    UINT8   ucUp;
} LPHY_CHE_INTP_COEF_STRU;


typedef  struct
{
    LPHY_CHE_INTP_COEF_STRU   stPreSym4;        /*插值系数*/
    LPHY_CHE_INTP_COEF_STRU   stPreSym7;
    LPHY_CHE_INTP_COEF_STRU   stPreSym11;
    LPHY_CHE_INTP_COEF_STRU   stCurSym0;
    LPHY_CHE_INTP_COEF_STRU   stCurSym4p;
    LPHY_CHE_INTP_COEF_STRU   stCurSym4;
    LPHY_CHE_INTP_COEF_STRU   stCurSym7;
    LPHY_CHE_INTP_COEF_STRU   stCurSym11;
    LPHY_CHE_INTP_COEF_STRU   stNxtSym0p;
    UINT8                     ucTx01Sym0Pdc;    /*时域预处理场景索引*/
    UINT8                     ucTx01Sym4Pdc;
    UINT8                     ucTx23Sym1Pdc;
    UINT8                     ucRsv0;
    UINT8                     ucTx01Sym0Pds;
    UINT8                     ucTx01Sym4Pds;
    UINT8                     ucTx01Sym7Pds;
    UINT8                     ucTx01Sym11Pds;
    UINT8                     ucTx23Sym1Pds;
    UINT8                     ucTx23Sym4Pds;
    UINT8                     ucTx23Sym8Pds;
    UINT8                     ucTx23Sym11Pds;

}LPHY_IND_CHE_RPT_INTP_PREP_EN_STRU;

typedef  struct
{
    UINT8  ucAlphaVal;
    UINT8  ucTx01LstValidSymbol;
    UINT8  ucTx23LstValidSymbol;
    UINT8  ucRsv0;
} LPHY_IND_CHE_RPT_ALPHA_FILTER_EN_STRU;

typedef struct
{
    INT16    sLeftTimingDiff;
    INT16    sRightTimingDiff;
    UINT16   usAgcLeftAmpgainRx0;
    UINT16   usAgcLeftAmpgainRx1;
    UINT16   usAgcLeftPowGainRx0;
    UINT16   usAgcLeftPowGainRx1;
    UINT16   usRuuAlphaVal;
    UINT16   usDemAlphaVal;

} LPHY_IND_CHE_MBMS_RPT_TM_AGC_ALPHA_EN_STRU;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/

/************************************************************
                    5. ERROR数据结构定义
************************************************************/

typedef enum
{
    LPHY_CHE_ERR_CELL_ID         = OM_CMD_ID(LPHY_CHE_MID, OM_TYPE_ERROR, 0x1),
    LPHY_CHE_ERR_SUBFRAME_NUM,
    LPHY_CHE_ERR_NOISE_ZERO,
    LPHY_CHE_ERR_SFLAG_OVERFLOW,
    LPHY_CHE_ERR_VEL_OVERFLOW,
    LPHY_CHE_ERR_OM_REQ_ID,
    LPHY_CHE_ERR_MAX_QM_MODE,
    LPHY_CHE_ERR_OM_DUMMY_FUNC,
    LPHY_CHE_ERR_EXTRA_PA_IND,
    LPHY_CHE_ERR_PA_INDEX,
    LPHY_CHE_ERR_QM_VALUE,
    LPHY_CHE_ERR_FREQ_OFFSET,
    LPHY_CHE_ERR_2D_FLAG

}  LPHY_CHE_OM_ERROR_ENUM;

typedef UINT32  LPHY_CHE_OM_ERROR_ENUM_UINT32;

typedef struct
{
    UINT16      usSysFrmNum;    /*系统帧号*/
    UINT16      usSubFrmNum;    /*子帧号*/
    UINT16      usSymbNum;      /*当前符号数*/
    UINT16      usReserved;
    UINT32      ulData0;
    UINT32      ulData1;
    UINT32      ulData2;

} LPHY_CHE_OM_ERROR_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHE_OM_DEF_H__ */

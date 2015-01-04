

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

#ifndef __CORR_OM_DEF_H__
#define __CORR_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CORR__
{
    LPHY_REQ_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR,
    LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T,
    LPHY_REQ_CORR_4T2R_NOISE_FACTOR_4T,
    LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR,
    LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T,
    LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T,
    LPHY_REQ_CORR_1T_OR_1R_THRESH,
    LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH,
    LPHY_REQ_CORR_FDD_CORRFLAG,
    LPHY_REQ_CORR_TDD_CORRFLAG,
    LPHY_REQ_CORR_FDD_WB_ALPHA,
    LPHY_REQ_CORR_TDD_WB_ALPHA,
    LPHY_REQ_CORR_FDD_SB_ALPHA,
    LPHY_REQ_CORR_TDD_SB_ALPHA,
    LPHY_REQ_CORR_APER_WHITE_ALPHA,    
    LPHY_REQ_CORR_NOISE_SEL,    
    LPHY_REQ_CORR_RPT_SG,
    LPHY_REQ_CORR_DRX_PARA
}LPHY_REQ_MSGID_CORR_ENUM;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_4T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_4T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_1T_OR_1R_NOISE_FACTOR_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_2T2R_OR_4T2R_NOISE_FACTOR_2T_STRU;

typedef struct __LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usNoiseFactor;
}LPHY_REQ_CORR_WHITE_4T2R_NOISE_FACTOR_4T_STRU;

typedef struct __LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_1T_OR_1R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usThresh;
}LPHY_REQ_CORR_2T2R_OR_4T2R_THRESH_STRU;

typedef struct __LPHY_REQ_CORR_FDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_FDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_TDD_CORRFLAG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucCorrFlag[6];
}LPHY_REQ_CORR_TDD_CORRFLAG_STRU;

typedef struct __LPHY_REQ_CORR_FDD_WB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_FDD_WB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_TDD_WB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_TDD_WB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_FDD_SB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_FDD_SB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_TDD_SB_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT8                       ucAlpha[6][3];
}LPHY_REQ_CORR_TDD_SB_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_APER_WHITE_ALPHA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usAlpha;
    UINT16                      usLT5MAlpha;
}LPHY_REQ_CORR_APER_WHITE_ALPHA_STRU;

typedef struct __LPHY_REQ_CORR_NOISE_SEL_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usWbNoiseSel;       /*1 选择宽带噪声; 0,选择子带噪声*/
}LPHY_REQ_CORR_NOISE_SEL_STRU;

typedef struct __LPHY_REQ_CORR_RPT_SG_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
}LPHY_REQ_CORR_RPT_SG_STRU;

typedef struct __LPHY_REQ_CORR_DRX_PARA_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16                      usAlphaSbGT5M[2]; /*FDD or TDD*/
    UINT16                      usAlphaSbLT5M[2]; /*FDD or TDD*/
    UINT16                      usAlphaWb;
    UINT16                      usWhtnAlphaWbGT5M[2]; /*FDD or TDD*/
    UINT16                      usWhtnAlphaWbLT5M[2]; /*FDD or TDD*/
    UINT16                      usDrxCycleFilterFlag;
    UINT16                      usAlphaNpCqiPmiForFalse;
    UINT16                      usAlphaNpCqiPmiForTrueEna;
    UINT16                      usAlphaNpCqiPmiForTrueStub;   
}LPHY_REQ_CORR_DRX_PARA_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CORR__
{
    LPHY_CNF_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_CORR_ENUM;


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_IND_MSGID_CORR__
{
    LPHY_IND_CORR_RESERVED            = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_CORR_ENUM;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_CORR_
{
    LPHY_TRACE_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_TRACE, 0x0),
}LPHY_TRACE_CORR_ENUM;


/************************************************************
                           5. SG数据结构定义
************************************************************/
typedef enum __LPHY_SG_CORR_
{
    LPHY_SG_CORR_RESERVED         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_CORR_RESULT,
    LPHY_SG_CORR_STAT    
}LPHY_SG_CORR_ENUM;

typedef struct __LPHY_SG_CORR_RESULT_STRU__
{
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  enRecCorr;      /*0,表示低相关，1，表示中相关，2表示高相关*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  enWhtnCorr;     /*0,表示低相关，1，表示中相关，2表示高相关*/
    LTE_CHAN_SPACE_CORR_ENUM_UINT8  enNonWhtnCorr;  /*0,表示低相关，1，表示中相关，2表示高相关*/
    UINT8                           ucRsv;          /*for 4字节对齐*/
}LPHY_SG_CORR_RESULT_STRU;

typedef struct __LPHY_SG_CORR_STAT_STRU__
{
    UINT16      ulRecCorr[3];                       /*高中低相关所占百分比*/
    UINT16      ulWhtnRecCorr[3];                   /*高中低相关所占百分比*/
    UINT16      ulNonWhtnRecCorr[3];                /*高中低相关所占百分比*/
    UINT16      usRsv;                              /*for 4字节对齐*/
}LPHY_SG_CORR_STAT_STRU;


/* BEGIN: Added by xueqiuyan, 2012/9/10   PN:CMCC_DT*/
/************************************************************
                           5. DT路测数据结构定义
************************************************************/
typedef enum __LPHY_DT_CORR_REQ_
{
    LPHY_DT_CORR_INFO_REQ         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x1),

}LPHY_DT_CORR_REQ_ENUM;

typedef enum __LPHY_DT_CORR_IND_
{
    LPHY_DT_CORR_INFO_IND         = OM_CMD_ID(LPHY_CORR_MID, OM_TYPE_DT, 0x1001),

}LPHY_DT_CORR_IND_ENUM;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16   enEn;
    UINT16          usPeriod;
} LPHY_DT_CORR_INFO_REQ_STRU;

typedef struct __LPHY_DT_CORR_INFO_IND_STRU__
{
    UINT16 usSFN;
    UINT8  ucSubFn;
    LTE_CHAN_SPACE_CORR_ENUM_UINT8 enRecCorr;
} LPHY_DT_CORR_INFO_IND_STRU;


/* END:   Added by xueqiuyan, 2012/9/10 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CORR_OM_DEF_H__ */

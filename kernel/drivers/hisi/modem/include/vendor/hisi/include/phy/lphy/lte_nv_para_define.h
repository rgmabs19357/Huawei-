


#ifndef __LTE_NV_PARA_H__
#define __LTE_NV_PARA_H__
#include "product_config.h"
/*#include "rfe_interface.h"*/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/
#define    LPHY_TX_DUAL_ANTENNA    2
#define    INTERP_COEF_ROW              9
#define    INTERP_COEF_COLUMN           3
#define    PB_TIME_DOMAIN_INTP_NUM     10
#define    PDU_TIME_DOMAIN_INTP_NUM    14
#define    IIR_ALPHA_NUMBER             6
#define    CHE_CPE_ROW                  8
#define    CHE_CPE_COLOUM               8
#define    LPHY_MAX_BANDWIDTH_NUM       6

#define    RF_9361_HW_TYPE              10
#define    RF_6360_HW_TYPE              11
/* BEGIN: Added by luliwu,  2012/1/13  PN: DTS_V210_12345678 */
#define    UL_APT_VBIAS_NUM             16
/*#ifdef CHIP_RFIC_6360V200*/
#if (defined(CHIP_RFIC_6360V210)||(defined(CHIP_RFIC_6361V100)))
#define    AGC_MAX_GAIN_LEVEL    (16)
/*#define    AGC_MAX_GAIN_LEVEL    (8)*/
/* END:   Added by luliwu,  2012/1/13  PN: DTS_V210_12345678 */


#define  RF_TX_FREQ_NUM (32)
#define RF_RX_FREQ_NUM (32)


#elif defined(CHIP_RFIC_9361)
#define    AGC_MAX_GAIN_LEVEL    (128)

#endif
#define  RF_TX_FREQ_NUM (32)
#define RF_RX_FREQ_NUM (32)
#define    AGC_MAX_GAIN_LEVEL    (16)

#define    AGC_MAX_INTERF_TYPE   2
#define    AGC_MAX_GAIN_TYPE     3

/* BEGIN: Added by w00133787,  2011/5/26  PN: 2011052804846 */
#define NV_RFIC_BALONGV7_MULTIBAN_BAND7
/*#define NV_RFIC_BALONGV7_MULTIBAN_BAND38*/
/* END:   Added by w00133787,  2011/5/26   */
/* BEGIN: Added by shijiahong, 2011/12/23   PN:DTS201112302952*/
#define MAX_HI6360_INITIAL_REG_NUM       40
#define MAX_DSP_CFG_REG_RESV_NUM         4
#define MAX_RF_BAND_NUM                  12
/* END:   Added by shijiahong, 2011/12/23   PN:DTS201112302952*/

/* BEGIN: Added by w00180842, 2013/8/29   PN:tuner*/
#define LTE_TUNER_SUPPORT_SENSOR_NUM  	  	 8
#define LTE_TUNER_DAC_MAX                    6
#define LTE_TUNER_CONTROL_MAX                4
#define LTE_TUNER_CMD_MAX      (LTE_TUNER_DAC_MAX + LTE_TUNER_CONTROL_MAX)
/* END:   Added by w00180842, 2013/8/29 */
/*PBCH  噪声白化*/
/************************************************************
                             数据结构定义
************************************************************/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1*/
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2*/
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 WhitenSwitchPBCH;                               /*PBCH噪声白化硬开关*/
    UINT8 Rsv0[2];
}NV_PB_IRC_STRU;

/*PDC  IRC*/

typedef struct
{
    UINT8 WhitenRuuSize1;                                 /*噪声白化的粒度1*/
    UINT8 WhitenRuuSize2;                                 /*噪声白化的粒度2*/
    UINT8 PdcSInd;                                        /*不使用PDS sym4: 0 使用PDS sym4: 1 */
    UINT8 WhitenThreMode;                                 /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
    UINT8 Threshold_A;                                    /*噪声白化自适应开关门限Threshold_A*/
    UINT8 Threshold_B;                                    /*噪声白化自适应开关门限Threshold_B*/
    UINT8 Threshold_C;                                    /*噪声白化自适应开关门限Threshold_C*/
    UINT8 WhitenSwitchPDCCH;                              /*PDCCH噪声白化硬开关*/
    UINT8 WhitenSwitchPCFICH;                             /*PCFICH噪声白化硬开关*/
    UINT8 WhitenSwitchPHICH;                              /*PHICH噪声白化硬开关*/
    UINT8 Rsv0[2];
    UINT16 PHICH_TH_NonWhiten;                            /*PHICH噪声白化硬开关关闭时的门限*/
    UINT16 PHICH_TH_Whiten;                               /*PHICH噪声白化硬开关开启时的门限*/
} NV_PDC_IRC_STRU;

/*PDS  IRC*/
typedef struct
{
     UINT8 WhitenRuuSize1;                                /*噪声白化的粒度1*/
     UINT8 WhitenRuuSize2;                                /*噪声白化的粒度2*/
     UINT8 PdsSInd;                                       /*用一个slot 或两个， 使用与否符号0，1*/
     UINT8 WhitenThreMode;                                /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 Threshold_A;                                   /*噪声白化自适应开关门限Threshold_A */
     UINT8 Threshold_B;                                   /*噪声白化自适应开关门限Threshold_B */
     UINT8 Threshold_C;                                   /*噪声白化自适应开关门限Threshold_C */
     UINT8 WhitenSwitchPDSCH;                             /*PDSCH噪声白化硬开关*/
     UINT8 BfWhitenRuuSize1;                              /*噪声白化的粒度1*/
     UINT8 BfWhitenRuuSize2;                              /*噪声白化的粒度2*/
     UINT8 BfPdsSInd;                                     /*用一个slot 或两个， 使用与否符号0，1*/
     UINT8 BfWhitenThreMode;                              /*0: 使用DSP 查表计算的门限值  1： 使用NV项配置的门限值*/
     UINT8 BfThreshold_A;                                 /*噪声白化自适应开关门限Threshold_A */
     UINT8 BfThreshold_B;                                 /*噪声白化自适应开关门限Threshold_B */
     UINT8 BfThreshold_C;                                 /*噪声白化自适应开关门限Threshold_C */
     UINT8 BfWhitenSwitchPDSCH;                           /*PDSCH噪声白化硬开关*/
} NV_PDS_IRC_STRU;
/* END:   Added by l00174474, 2011/6/8 */

typedef struct
{
    NV_PB_IRC_STRU     stPbIrc;
    NV_PDC_IRC_STRU    stPdcIrc;
    NV_PDS_IRC_STRU    stPdsIrc;

} NV_IRC_PUB_STRU;



typedef struct
{
   UINT8   RsIntpCoef[INTERP_COEF_ROW][INTERP_COEF_COLUMN];         /*加密系数配置*/
   UINT8   Rsv0;
   UINT16  PbchTimeIntCoef[PB_TIME_DOMAIN_INTP_NUM];                /*PB时域插值系数配置*/
   UINT16  PduTimeIntCoef[PDU_TIME_DOMAIN_INTP_NUM];                /*PDU时域插值系数配置*/
   UINT8   AlphaCoef[IIR_ALPHA_NUMBER];                             /*Alpha滤波系数配置*/
   UINT16  Rsv1;
   UINT32  ChanPhaseErrRx0[CHE_CPE_ROW][CHE_CPE_COLOUM];
   UINT32  ChanPhaseErrRx1[CHE_CPE_ROW][CHE_CPE_COLOUM];
} NV_CHE_INTP_STRU;

/*定时NV定义*/
typedef struct{
    VOS_UINT16  T_ParTD[6];         /*default: [48 64 64  96 96 96]时域加密时信道PDP峰均比保护门限，对应1.4M到20M带宽                       */
    VOS_UINT16  T_ParFD[6];         /*default: [64 64 64  96 96 96]频域加密时信道PDP峰均比保护门限，对应1.4M到20M带宽                       */
    VOS_UINT16  TrefShort[6];       /*default: [32 32 11 11 8 8]   DRX预同步 or IDLE解寻呼场景的定时提前量，以0.5Ts为单位,对应1.4M到20M带宽 */
    VOS_UINT16  TrefCommon[6];      /*default: [16 16 11 11 8 8]   其他场景的定时提前量，以0.5Ts为单位,对应1.4M到20M带宽                    */
    VOS_UINT16  FPWLenShort[6];     /*default: [3 6 12 24 48]      DRX预同步 or IDLE解寻呼场景的首径搜索窗长度，对应1.4M到20M带宽           */
    VOS_UINT16  FPWLenCommon[6];    /*default: [10 20 40 80 160]   其他场景的首径搜索窗长度，对应1.4M到20M带宽                              */
    VOS_UINT16  Tb;                 /*default: 384                 窗W1b和W2b的门限因子                                                     */
    VOS_UINT16  EndValue;           /*default: 8                   滤波系数下限索引值                                                      */
    VOS_UINT16  W;                  /*default: 128                 多径搜索窗搜索窗长                                                       */
    VOS_UINT16  FPWindow;           /*default: 20                  多径搜索窗基于峰值向前搜索首径的范围                                     */
    VOS_UINT16  HoldThrsh;          /*default: 32                  多径搜索窗低信噪比保护门限                                               */
    VOS_UINT16  Ncs;                /*default: 5                   连接态DRX用于判断解调定时有效性的小区搜索次数                            */
    VOS_UINT16  ResetThrs;          /*default: 288                 多径搜索窗判断解调定时有效性的门限(0.5Ts)                                */
    VOS_UINT16  Reserved;           /*default: 0                                                                                            */
}NV_TIMING_PARA_STRU;

typedef struct
{
    VOS_UINT8   N_6RB[4];           /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_15RB[4];          /*default: {[40,40,20,20]}*/
    VOS_UINT8   N_Other;            /*default: {10}*/
    VOS_UINT8   Reserverd[3];       /*default: {0}*/
}NV_EMU_FAKECELL_PARA_STRU;

typedef struct{
    VOS_UINT8   RuuAlpha;                       /*default:{{0},             Ruu的滤波因子                                                  */
    VOS_UINT8   WhitenRBStep;                   /*default:{0},              白化开关的频域子带粒度配置                                      */
    VOS_UINT8   CSIWhitenFlag;                  /*default:{0},              CQI计算是否白化的硬开关                                          */
    VOS_UINT8   CSIWhitenSwitchMode;            /*default:{0},              CQI计算是否用全带宽的干扰矩阵来做白化运算                        */
    VOS_UINT8   CSIWhitenKg[6];                 /*default:{1,1,1,1,1,1},    白化开关的频域RB粒度配置                                         */
    VOS_INT8    ESINRRepairFactor1[24];         /*default:{1,1,1,0,0,1,-1,-1,-1,-1,-1,-1,1,1,1,0,0,1,-1,-1,-1,-1,-1,-1},  有效信噪比补偿值1            */
    VOS_INT8    ESINRRepairFactor2[24];         /*default:{-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0},  有效信噪比补偿值2            */
    VOS_INT8    ESINRRepairFactor3[24];         /*default:{0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1},  有效信噪比补偿值3            */
    VOS_INT8    ESINRRepairFactor4[24];         /*default:{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},  有效信噪比补偿值4            */
    VOS_INT8    RuuZeroFlag;                    /*default: 1*/
    VOS_INT8    Reserved;                       /*default: 0*/
}NV_CQI_PARA_STRU;

typedef struct{
    VOS_UINT8   RuuAlpha;                        /*default:{{0},      Ruu的滤波因子                                                  */
    VOS_INT8    RLMWhitenSwitch;                 /*default:{1},       RLM计算是否白化的硬开关                                         */
    VOS_INT8    RLMSwitchMode;                   /*default:{0},       白化开关的粒度是否是全带宽                                      */
    VOS_INT8    RLMWhitenN[2];                   /*default:{10,1},    白化开关的粒度,[0]对应粒度1，[1]对应粒度2                       */
    VOS_INT8    RLM_WhitenThd_FDD[24];           /*default:{0,...,0}, FDD，RLM Whiten判决门限修正值                                  */
    VOS_INT8    RLM_WhitenThd_TDD[24];           /*default:{0,...,0}, TDD，RLM Whiten判决门限修正值   "                              */
    VOS_INT8    RuuZeroFlag;                     /*default: 1*/
    VOS_INT8    Reserved[2];                     /*Reseved: TBD*/
}NV_RLM_PARA_STRU;

typedef struct{
    VOS_INT8    Corr_Tlayer1IRC;                 /*default: 19,       1发射天线或1接收天线时，判断噪声白化后的相关性的门限值         */
    VOS_INT8    Corr_Tlayer2IRC;                 /*default: 4},       2发2收或4发2收时，判断噪声白化后的相关性的门限值              */
    VOS_INT8    Reserved[2];                     /*Reseved: TBD*/
 }NV_ANTCORR_PARA_STRU;

/*VITERBI*/
typedef struct
{
    VOS_UINT16 DciTotalPwrThresh[2][4][4];      /*全体CCE软件度量值判决门限, [噪声白化开关][RSSP区间][DAGC调整量索引]*/
    VOS_UINT16 DciSinglePwrThresh[2][4][4];     /*单CCE软件度量值判决门限, [噪声白化开关][RSSP区间][DAGC调整量索引]*/
    VOS_UINT16 DciBerThresh[2];                 /*BER判决门限, [噪声白化开关]*/
    VOS_UINT32 CcDecTraceSelOrder;              /*加比选中幸存路径选择和回溯时起始状态选择的优先级顺序开关*/
}NV_VITERBI_PARA_STRU;

/*TURBO*/
typedef struct
{
    VOS_UINT32 TurboDecIterFactor;              /*各次迭代可靠因子, 取值范围: 35-48, 默认为45*/
}NV_TURBO_PARA_STRU;

typedef struct
{
    UINT16    ausRsThrd1Fdd[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausRsThrd1TddNCfg0[LPHY_TX_DUAL_ANTENNA][LPHY_MAX_BANDWIDTH_NUM];
#if 0
    UINT16    ausOLHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausOLLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
#endif
    UINT16    ausILHighThrd[2][LPHY_MAX_BANDWIDTH_NUM];
    UINT16    ausILLowThrd[2][LPHY_MAX_BANDWIDTH_NUM];
}AFC_NV_RS_CONFIG_STRU;
typedef struct
{
    UINT16 usVctcxoThdHigh;             /* 动态TCXO高门限 */
    UINT16 usVctcxoDynamic;             /* 动态TCXO值, UE上电时由HPA读取NV并配置DSP,
                                               UE上电开机进入连接态后从DSP获取有效值写入NV */
    UINT16 usVctcxoFlag;                /* 动态TCXO取值是否有效标识, DSP可不用,
                                               0: 有效；其余无效，无效时usDynamicTcxo值无意义 */
    UINT16 usVctcxoFuncSwitch;          /* 动态TCXO功能是否使用开关, DSP可不用,
                                               修改后, 需要下电再上电才会生效
                                               0: 关闭, 关闭时usVctcxoDynamic取值usVctcxoInit
                                               1: 打开 */
}LTE_TCXO_DYNAMIC_CONFIG_STRU;

typedef struct
{
    UINT16    usEnableFlag;
    UINT16    usHSTMode;
    AFC_NV_RS_CONFIG_STRU    stAfcNvCRsConfig;
/*#ifdef CHIP_BB_6920CS*/
    AFC_NV_RS_CONFIG_STRU    stAfcNvMRsConfig;
/*#endif*/
    UINT16    usFreqAdjustLimit;/*usLoopAdjustLimit;*/
    UINT16    usFOHSTCompensation;
    /*UINT16    usInitPDM;*/
    /*UINT16    usDynamicPDM;*/
    UINT16    usVoltageFactor;
    UINT16    usMFreqAdjustLimit;

    UINT16    usPdmHighThreshold;
    UINT16    usFreqOffsetThreLow;
    UINT16    usFreqOffsetThreHigh;
    UINT16    usPdmCcThreshold;
    UINT16    ausPdmParThreshold[LPHY_MAX_BANDWIDTH_NUM];
}AFC_NV_PARA_STRU;

typedef struct {
    UINT8       ucVersion[16];                  /*发布版本年月日*/
    UINT32      ulVersionId;                    /*发布版本标识*/
}NV_VERSION_STRU;

typedef struct
{
    INT16     sPreTargetPowerFdd;
    INT16     sPreTargetPowerTdd;
    INT16     sPostTargetPower;
    INT16     sLeastSNR;

    UINT8     ucDAGCAdjBitForTM1To6;
    UINT8     ucDAGCAdjBitForTM7To8;
    INT8      cMinAntPwr;
    INT8      cMaxAntPwr;

    UINT8     ucACSFilterThreshold[LPHY_MAX_BANDWIDTH_NUM];
    INT8      cACSPowerThreshold0[LPHY_MAX_BANDWIDTH_NUM];
    INT8      cACSPowerThreshold1[LPHY_MAX_BANDWIDTH_NUM];
    UINT8     ucNBFilterThreshold[LPHY_MAX_BANDWIDTH_NUM];
    INT8      cNBPowerThreshold0[LPHY_MAX_BANDWIDTH_NUM];
    INT8      cNBPowerThreshold1[LPHY_MAX_BANDWIDTH_NUM];
}NV_AGC_PARA_STRU;
/*UL NV */
typedef enum
{
    APC_GAIN_LEVEL_0 = 0,
    APC_GAIN_LEVEL_1 ,
    APC_GAIN_LEVEL_2 ,
    APC_GAIN_LEVEL_3,
    APC_GAIN_LEVEL_INVALID
}UL_APC_GAIN_LEVEL_ENUM;


typedef enum
{
    APC_GAIN_NONCROSS = 0,
    APC_GAIN_CROSS
}UL_APC_GAIN_CROSS_FLAG_ENUM;

typedef UINT16 UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16;
typedef UINT16 UL_APC_GAIN_LEVEL_ENUM_UINT16;

typedef struct
{
    INT16 sPwrLow;
    INT16 sPwrHigh;
    UL_APC_GAIN_LEVEL_ENUM_UINT16 enAPcGainLevel;
    UL_APC_GAIN_CROSS_FLAG_ENUM_UINT16 enAgcGainCrossFlag;
}UL_APC_GAIN_CTRL_STRU;

typedef struct
{
    INT16  sPwr;
    UINT16 usVga;
}UL_APC_TABLE_ITEM_STRU;


#define APC_GAIN_AREA_NUM 3
#define APC_TABLE_NUM 2
#define APC_TABLE_LEN 64
/*#define APC_GAIN_LEVEL_NUM 4*/

typedef struct
{
    UINT32 ulUlCfrSwitch;
    INT16  sSrsCfrThred;
    INT16  sPuschCfrThred;
}UL_CFR_CTRl_STRU;

typedef struct
{
    UL_CFR_CTRl_STRU stCfrCtrl;
    UL_APC_GAIN_CTRL_STRU astApcCtrl[APC_GAIN_AREA_NUM];
    UL_APC_TABLE_ITEM_STRU astApcTable[APC_TABLE_NUM][APC_TABLE_LEN];
}NV_UL_PARA_STRU;

/* BEGIN: Added by shijiahong, 2011/12/23   PN:DTS201112302952*/

typedef struct
{
    UINT32 ulRegAddr;
    UINT32 ulValue;
}NV_DSP_RF2BBP_CFG_STRU;

typedef struct
{
    UINT16 usRficRegAddr;
    UINT16 usRficRegValue;
}NV_LPHY_RFIC_CFG_STRU;

/*****************************************************************************
 结构体名  : NV_LPHY_RF_LINECTRL_COMMON_CONFIG
 协议表格  :
 ASN.1描述 :
 枚举说明  : LTE RF线控，取决于硬件形态
*****************************************************************************/
typedef struct
{
    NV_DSP_RF2BBP_CFG_STRU stRficTcvrOn;                               /*6360RF开关*/
    NV_DSP_RF2BBP_CFG_STRU stRficPaPowCtrl;                            /*6360RFPA供电电压控制*/
    NV_DSP_RF2BBP_CFG_STRU stTddTrxSwitchCtrl;                         /*TDD TRX SWITCH 可固定配置为0x24000000*/
    NV_DSP_RF2BBP_CFG_STRU stRficTxIQFmt;                              /*ABB TX通道IQ格式*/
    NV_DSP_RF2BBP_CFG_STRU stRficResetA;                               /*6360RF复位信号A*/
    NV_DSP_RF2BBP_CFG_STRU stRficResetB;                               /*6360RF复位信号B*/
}NV_LPHY_RF_LINECTRL_COMMON_CONFIG;


typedef struct
{
    NV_DSP_RF2BBP_CFG_STRU stTxAntSel;                 /* B38/B40发射天线A,B通道选择,强制拉高或拉低 0:主通道，0x3ffffff :辅通道,0x60000000逻辑自控 */
    NV_DSP_RF2BBP_CFG_STRU stAntennaSwitchIntraRx;    /* 名字是否需要刷新?  INTTRA */
	NV_DSP_RF2BBP_CFG_STRU stAntennaSwitchIntraTx;    /* 名字是否需要刷新?  INTTRA */
    NV_DSP_RF2BBP_CFG_STRU stAntennaSwitchInter;      /* 名字是否需要刷新? INTTER */
    NV_DSP_RF2BBP_CFG_STRU stPaEnBitMap;               /*PA BITMAP配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stPaMode0BitMap;            /*PA MODE0 BITMAP配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stPaMode1BitMap;            /*PA MODE1 BITMAP配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stTRxSwitchBitMap;          /*TDD收发控制信号map配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stTxSwitch0BitMap;          /*TM8/TM9发射天线选择信号map配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stTxSwitch1BitMap;          /*TM8/TM9发射天线选择信号map配置，根据所用GPIO选定对应bit*/
    NV_DSP_RF2BBP_CFG_STRU stPaEnCfg;                   /*PA控制信号配置*/
    NV_DSP_RF2BBP_CFG_STRU stRficPaAtt1;                /*PA MODE0控制信号配置*/
    NV_DSP_RF2BBP_CFG_STRU stRficPaAtt2;                /*PA MODE1控制信号配置*/
}NV_LPHY_RF_LINECTRL_PRIVAT_CONFIG;

typedef struct
{
    UINT32 ulReserveCfgNum;
    NV_DSP_RF2BBP_CFG_STRU stReserveCfgInfo[MAX_DSP_CFG_REG_RESV_NUM];
}NV_LPHY_RF_LINECTRL_RESERVED_CONFIG;

typedef struct
{
    UINT8 ucRfMainRxLnaSel;             /*RF RX 主集使用LNA*/
    UINT8 ucRfDvtyRxLnaSel;             /*RF RX 主集使用LNA*/
    UINT8 ucRfTxLnaSel;                 /*RF RX 主集使用LNA*/
    UINT8 ucRfRxVcoCoreSel;             /*RF RX VcoCore选择*/
    UINT8 ucRfRxDividerSel;             /*RF RX Divider选择*/
    UINT8 ucResv;
    UINT8 ucRfTxVcoCoreSel;             /*RF TX VcoCore选择*/
    UINT8 ucRfTxDividerSel;             /*RF TX Divider选择*/
}NV_LPHY_RFIC_REG_PRIVAT_PARA;

typedef struct
{
    UINT32 ulRficInitalRegNum;
    NV_LPHY_RFIC_CFG_STRU stRficCfgVar[MAX_HI6360_INITIAL_REG_NUM];
}NV_LPHY_RFIC_INITIAL_CFG_STRU;

typedef struct
{
    NV_LPHY_RF_LINECTRL_COMMON_CONFIG   stRFLineCtrlComnVar;                        /*包含寄存器值和Value */
    NV_LPHY_RF_LINECTRL_RESERVED_CONFIG stRFLineCtrlComnRsv;                   /*与Band无关的配置扩展使用 */
}NV_LPHY_LINECTRL_COMN_INFO_STRU;

typedef struct
{
    UINT32 ulHWBoardType;                                                          /*当前的单板类型 */
    UINT32 ulBandNum;                                                              /*当前的Band数目; */
    UINT32 ulInitialBandIndex;                                                     /*当前默认的Band */
    UINT8  ucBandInd[MAX_RF_BAND_NUM];                                             /*支持的Band列表 */
    NV_LPHY_RF_LINECTRL_PRIVAT_CONFIG   stRFLineCtrlPrivatVar[MAX_RF_BAND_NUM];     /*包含寄存器值和Value */
    NV_LPHY_RF_LINECTRL_RESERVED_CONFIG stRFLineCtrlPrivatRsv[MAX_RF_BAND_NUM];/*与Band相关的配置扩展使用 */
    NV_LPHY_RFIC_REG_PRIVAT_PARA        stRficRegPrivatPara[MAX_RF_BAND_NUM];       /*仅涉及到配置的值 */
}NV_LPHY_LINECTRL_PRIV_INFO_STRU;

typedef struct
{
    UINT8 enSingleReceiverChnSel;
    INT8  cRsv[7];
}NV_PHY_FUNC_VERIFY_STUB_STRU;



/* BEGIN: Added by w00180842, 2013/8/29   PN:tuner*/

/*MIPI写命令格式如下
31--29  001  ---->指令类型
28--25  0111 ---->SLAVE ADDRESS
24--22  010  ---->cmd
21--17         ---->addr 例如0x1c,0x00等
16                ---->17--24的校验位
15--8           ---->配置的数据
7                  ---->15---8的校验位
6--0             ---->保留位
 aulControlCfgPara[i] 需按照上述BIT位全部写入
 usDacCmd    15--0依次对应上述 31--16BIT位写入
 ausDacData[j][k]15---0依次对应上述15--0BIT位写入
 */
typedef struct 
{
    UINT16 usDacCmd;
    UINT16 usRev;
    UINT16 ausDacData[MAX_RF_BAND_NUM][LTE_TUNER_SUPPORT_SENSOR_NUM];//BAND顺序与BAND列表相同
}LTE_TUNER_DAC_CFG_PARA_STRU;
typedef struct 
{
    UINT16 usDacCfgNum;//必须与ox00寄存器中DAC使能的个数一致
    UINT16 usRev;
    LTE_TUNER_DAC_CFG_PARA_STRU stDacCfgPara[LTE_TUNER_DAC_MAX];
}LTE_TUNER_DAC_CFG_STRU;
 typedef struct 
 {
     UINT16 usControlCfgNum;//最大值为4，SLEEP MODE 目前默认配置一个(0x1c)，activeMODE 默认配置3个
     UINT16 usRev;
     UINT32 aulControlCfgPara[LTE_TUNER_CONTROL_MAX];//配置时从0--5依次配置，0-->0x1c, 1-->0x10, 2-->0x0，其他依次放置
 }LTE_TUNER_CONTROL_CFG_STRU;
typedef struct 
{
    LTE_TUNER_CONTROL_CFG_STRU stControlCfg;
    LTE_TUNER_DAC_CFG_STRU stDacCfg;
}LTE_TUNER_MIPI_ACTIVE_MODE_CMD_STRU;
typedef struct 
{
    LTE_TUNER_CONTROL_CFG_STRU stControlCfg;
}LTE_TUNER_MIPI_SLEEP_MODE_CMD_STRU;
typedef struct
{
    UINT16 usTunerValidFlag;//1--支持   0--不支持
    UINT16 usCfgTimeAdv;//时间提前量
    UINT16 usRev;
    UINT16 usBandNum;//支持的BAND数
    UINT16 ausBandList[MAX_RF_BAND_NUM];//BAND列表
    LTE_TUNER_MIPI_SLEEP_MODE_CMD_STRU stSleepModeCfg;
    LTE_TUNER_MIPI_ACTIVE_MODE_CMD_STRU stActiveModeCfg;
     
}NV_LPHY_TUNER_NV_PARA_STRU ;
/* END:   Added by w00180842, 2013/8/29 */

/* BEGIN:   Added by x00228734, 2013/9/30 */
typedef struct
{
    UINT16 usLteMasterIdrxEnable;
    UINT16 usLteMasterCdrxEnable;
    UINT16 usLteSlaveSleepEnable;
    UINT16 usLteDrxSwitch32kTime;
    UINT16 usRsvd[4];
}LTE_DRX_NV_PARA_STRU;
/* END:   Added by x00228734, 2013/9/30 */
/*****************************************************************************
 结构体名  : NV_LPHY_DSP_CONFIG
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPHY DSP开机初始化公共参数配置NV结构体定义
*****************************************************************************/
typedef struct{
    LRRC_LPHY_ANTANNA_PORT_ENUM_UINT16  enAntennaPortsCount;                /*LPHY UE的天线中用来接收下行信号的天线数目*/
    LRRC_LPHY_LTE_MODE_TYPE_ENUM_UINT16 enLteMode;                          /*LPHY 初始化时默认的复用模式*/
    UINT32                              aulNvLteAntennaSwitchBand[MAX_RF_BAND_NUM];       /*LTE各Band对应的天线开关值, 比特0:9：FDD天线开关或TDD Rx天线开关值;比特16:25：TDD Tx天线开关值*/
    UINT16                              usNvLteOccaPreTime;                 /*lte构造异系统occasion时预处理中断提前量，单位us*/
    UINT8                               ucPowerOnLoadFlag;                  /*LPHY DSP上电第一次加载标识: "1"上电第一次加载;"0"非上电第一次加载*/
    UINT8                               ucNvLteInitialCfgRfabb;             /*LPHY 初始化时是否配置RF、ABB标识："1"配置;"0"不配置*/
    UINT8                               ucHwVersion;                        /*BalongV7R1硬件版本号*/
    UINT8                               ucNvLteBandNumber;                  /*LTE Band个数,<8*/
    UINT8                               aucNvLteBandInd[MAX_RF_BAND_NUM];                  /*LTE Band号数组，每个值对应LTE Band号*/
    UINT8                               aucNvLtePaEnInd[MAX_RF_BAND_NUM];                  /*LTE各Band对应的PA En比特位,Band指示与aucNvLteBandInd一致*/
    UINT8                               ucNvLteDefaultBandIdx;              /*初始化时缺省BAND序号*/
    UINT8                               ucUeCap;                            /*1表示ue能力1，2标识ue能力2，5表示ue能力5*/
    UINT8                               ucAntSelect;                    /*0:false,1:true */
    UINT8                               ucSupport64Qam;                    /*0:64qam不支持，1:64qcam支持*/
    /* END:   Added by l00131321, 2011/10/15 */
    #if 0
    /*UINT8                               aucDspCfgRsv[2];   */                 /*LPHY 初始化配置预留参数*/
    UINT8                               ucIdleDrxControlFlag;/*IDLE DRX控制标志 */
    UINT8                               aucDspCfgRsv;                    /*LPHY 初始化配置预留参数*/

    #endif
    UINT16                              usLteTxTrxSwitchCfg;                /*LTE的Tx_switch和TRx_switch扩展标志，表示Tx_switch是否要扩展为2根*/
    UINT16                              usLteAbbIfFormat;                   /*LTE ABB接口配置*/
    UINT8                               ucLteC0C1Sel;                       /*双待时lte放在通道c0还是c1上*/
    UINT8                               ucLteSsiReadChSel;                  /*lte SSI回读的通道选择*/
    UINT8                               ucLteRficAd9361Sel;                 /*lte 是否选用AD9361*/
    UINT8                               ucLteAd9361TcvrOnFlag;              /*LTE使用AD9361支持多模单待时LTE的TCVR_ON管脚在通道0输出的状态*/
    UINT8                               ucTxiqFeedbackPath;                 /*Hi6361s 通路A/B选择*/
    /*UINT8                               aucDspCfgRsv;    */                /*LPHY 初始化配置预留参数*/
    UINT8                               ucIdleDrxControlFlag;/*IDLE DRX控制标志 */
}NV_LPHY_DSP_CONFIG;



/*****************************************************************************
 结构体名  : NV_GULPHY_COMMON_PARA_CONFIG
 协议表格  :
 ASN.1描述 :
 枚举说明  : GUL多模公共参数配置NV结构体定义
*****************************************************************************/
typedef struct{
    UINT8                               ucNvSingleDualModeInd;              /*单双待指示，0：单待；1：双待*/
    UINT8                               ucNvSingleDualRficInd;              /*单双RFIC，0：双RFIC；1：单RFIC*/
    UINT8                               ucNvCtuTimingDelayCnt;              /*CTU检测到timing_get_ind后固定延迟nv_ctu_timing_delay_cnt个CTU时钟周期后拉高timing_valid信号。*/
    UINT8                               ucNvPaMuxCtrl;                      /*GUL PA复用控制，3bit*/
}NV_GULPHY_COMMON_PARA_CONFIG;

typedef struct
{
              UINT16 usT1;                  /*T1默认值配置(根据切频配置寄存器数目而定)*/
              UINT16 usT2;                  /*T2默认值配置(RFIC锁频时间)*/
              UINT16 usT3FDD;               /*T3_FDD默认值配置(本频与异频之间的保护时间)*/
              UINT16 usT3TDD;               /*T3_TDD默认值配置(本频与异频之间的保护时间)*/
              UINT16 usT4;                  /*T4默认值配置(FIR滤波器延时)*/
              UINT16 usAGCCfgTime;          /*AGC配置提前量(逻辑配置射频增益的提前量)*/
              UINT16 usFDDADCOpenTime;      /*FDD ABB ADC打开提前量*/
              UINT16 usTDDADCOpenTime;      /*TDD ABB ADC打开提前量*/
              UINT16 usDACOpenTime;         /*ABB DAC打开提前量*/
              UINT16 usT7UL;                /*UL_RFIC_T7(TDD上行模式切换配置提前量)*/
              UINT16 usT7DL;                /*RFIC_T7(TDD下行模式切换配置提前量)*/
              UINT16 usT8ULFDD[6];          /*UL_FDD_T8_COMPENSATE*/
              UINT16 usT8ULTDD[6];          /*UL_TDD_T8_COMPENSATE*/
              UINT16 usT9;                  /*T9(TDD下行模式切换配置提前量)*/
              UINT16 usT10VGASPICfgTime;    /*T10上行VGA的SPI配置时间*/
              UINT16 usT15;                 /*T15*/
              UINT16 usTul[6];              /*上行通道延时*/
              UINT16 usPaOpenTime;          /*PA打开时间，基于PA特性*/
              UINT16 usPaAttTime;           /*PA ATT打开时间，基于PA特性*/
              UINT16 usAntSelTime;          /*ANT打开时间，基于ANT特性*/
              UINT16 usReserve;             /*保留备用*/
}NV_DSP_CONFIG_TIME_STRU;
/*****************************************************************************
 结构体名  : NV_LPHY_AGC_BASE_TABLE_STRU
 协议表格  :
 ASN.1描述 :
 枚举说明  : LPHY DSP AGC基准表NV结构体定义
*****************************************************************************/
typedef struct{
    UINT32 aulRx1AgcBaseTable[128];
    UINT32 aulRx2AgcBaseTable[128];
}NV_LPHY_AGC_BASE_TABLE_STRU;

typedef struct
{

     INT16 usFreqCmpInd;
     INT16 usTempCmpInd;
}NV_BT_CMP_SWITCH_STRU;

typedef struct
{
    UINT16 usDbbAtt;
	UINT16 usAbbAtt;
}NV_APC_ATT_TABLE_STRU;

typedef struct
{
    INT16 sHigh2MidThre;
	INT16 sMid2HighThre;
	INT16 sMid2LowThre;
	INT16 sLow2MidThre;
}NV_PA_LEVEL_THRE_STRU;
typedef struct
{
    UINT32 ulDbbAttRegVal;
    UINT32 ulAbbAttRegVal;
    UINT32 ulAptPdmRegVal;
}UL_PWR_REG_STRU;
typedef struct
{
    UINT16 usEnableFlg;
    UINT16 usTimingAhead;
}UL_APT_PARA_STRU;
typedef struct
{
    INT16  sTxpower;
    UINT16 usPdmVal;
}UL_APT_TX_POWER_PDMVAL_STRU;
typedef struct
{
    UINT32 ulNum;
    UL_APT_TX_POWER_PDMVAL_STRU stPower2PdmVal[UL_APT_VBIAS_NUM];
}UL_APT_GAIN_VS_VBIAS_STRU;

#define PA_LEVEL_NUM  3
#define LNA_LEVEL_NUM 4
#define APC_ATT_MAX_NUM 88

typedef struct __NV_DEM_LIST_STRU__
{
    UINT8    ucInAdjBit;
    UINT8    ucInAdjBitBF;
    UINT8    ucPdschSfbcDemAlg;
    UINT8    ucPdschSdmaDemAlg;
    UINT16   usPHICHDemTHIrcOFF;
    UINT16   usPHICHDemTHIrcON;
}NV_DEM_LIST_STRU;
typedef enum
{
    DCOC_SAMPLE = 0,
    DCOC_SYMBLE,
    DCOC_SUBFRAME,
}DCOC_UPDATECONFIG_ENUM;
typedef UINT16 DCOC_UPDATECONFIG_ENUM_UINT16;
typedef struct
{
    INT16 usPaDiff[4];
}NV_PA_POWER_DIFFERENCE;

typedef struct
{
    UINT16 usCompDCI[32];
    UINT16 usCompDCQ[32];
}RF_DCOC_CAL_STRU;

typedef struct
{
    RF_DCOC_CAL_STRU stDcocComp[2];
}NV_DCOC_CAL_TABLE;


typedef struct
{
    UINT16 usIIP2Comp[24];
}NV_IIP2_CAL_TABLE;

typedef struct
{
    INT16  sAmplitude;
    INT16  sPhase;
    INT16  sDCI;
    INT16  sDCQ;
}RF_TXIQ_CAL_STRU;

typedef struct
{
    INT16 sGainStatus[16];
}NV_TX_APC_GAIN_STRU;

typedef struct
{
    UINT16 usBias[16];
}NV_TX_RF_BIAS_STRU;

typedef struct
{
    UINT16 usBB0DBAllowedFlg;
    INT16 sMaxBBAttVal;
    INT16 sMaxPower;
    INT16 rsd;
}NV_TX_RF_BB_ATT_STRU;

typedef struct
{
    INT16 sFreqComp[RF_TX_FREQ_NUM];
}NV_TX_RF_FREQ_COMP_STRU;
typedef struct
{
    INT16 sPaTempComp[3][32];
}NV_TX_PA_TEMP_COMP;
typedef struct
{
    UINT16 usAttenTable[60];
}NV_TX_ATTEN_TABLE;
typedef struct
{
    UINT16 usPowerVoltage[3];
}NV_TX_POWERDET_VOLTAGE;


typedef struct
{
    /*band related*/

    UINT8     ucAGCAcsMinGainZ;
    UINT8     ucAGCNbMinGainY;
    UINT8     ucReserved;
    UINT8     ucDefaultGain0;

    UINT8     ucDefaultGain1;
    UINT8     ucDefaultGain2;
    DCOC_UPDATECONFIG_ENUM_UINT16    enDcocUpdateConfig;

    /*RF/AGC增益表*/
    UINT32     ulAGCGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCAcsGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulAGCNbGainTable[AGC_MAX_GAIN_LEVEL];
    UINT32     ulRFIdxTable[2][AGC_MAX_GAIN_LEVEL];
    INT16      sRFErrorTable[2][AGC_MAX_GAIN_LEVEL];
}NV_AGC_BAND_GAIN_TABLE_STRU;

typedef struct
{
    UINT16      usRxCalibrFreqList[RF_RX_FREQ_NUM];            /*Rx频率校准表*/

    INT16   	asAgcNoBlkAnt1FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asAgcNoBlkAnt2FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asAgcBlkAnt1FreqComp[8][RF_RX_FREQ_NUM];       /*补偿table*/
    INT16     	asAgcBlkAnt2FreqComp[8][RF_RX_FREQ_NUM];
    INT16     	asRxTempCmpVal[32];
    INT16       asIP2CalChanList[8];
    INT16       asIP2CalResult[8][2];
    NV_IIP2_CAL_TABLE stIP2CalResult;
    UINT16      usIP2CalThreshold;
    UINT16      usRsv2;
    NV_AGC_BAND_GAIN_TABLE_STRU           stAGCTable;        /*agc NV项 */
    RF_DCOC_CAL_STRU stAnt0Dcoc;
    RF_DCOC_CAL_STRU stAnt1Dcoc;
}NV_BAND_RXPATH_PARA_STRU;

typedef struct{
    UINT8 ucRxBtLeverMapTable[16];
}NV_RX_BT_LEVEL_MAP_TABLE_STRU;

typedef struct
{
    UINT16                      usRegionAVal;
    UINT16                      usRegionBVal;
    UINT16                      usRegionCVal;
    UINT16                      usReserved;
}UL_AMPR_STRU;

typedef struct
{
	INT16  sWireLessMaxPwr;                   /*无线状态最大功率*/
	INT16  sWiredMaxPwr;                      /*传导状态最大功率*/
	UINT16 usTestModeInd;                     /*降SAR测试模式指示*/
	INT16  sReducedPwr[9];                    /*降SAR回退功率*/
}NV_ANT_SAR_STRU;
typedef struct
{
    INT16  sDivLossComp;
    UINT16 usRes;
}LTE_TX_DIVERSITY_LOSS_COMP;
#if 0
typedef struct
{
	INT16 sTx1RbAdjVal;                      /*1RB发送时调整值 1/8db为单位*/
	INT16 sRsv[15];
}NV_TX_CMP_RSV_STRU;
#endif
/* BEGIN: Added by xueqiuyan, 2013/1/4   PN:ONE_RB*/
typedef struct
{
    UINT16 usWirelessOneRbMprVal;
    UINT16 usWiredOneRbMprVal;
    UINT16 usRsv[4];
}UL_ONE_RB_MPR_STRU;
/* END:   Added by xueqiuyan, 2013/1/4 */

typedef struct
{
    NV_PA_LEVEL_THRE_STRU stPaThre;          /*PA档位门限*/
    UINT16 usTxCalibrFreqList[RF_TX_FREQ_NUM];           /*TX校准频点，由低到高放置*/
    INT16 asTxMaxPwr[4];                     /*校准max power值*/
    INT16 asPaHighCalPwr[4];                 /*PA高档校准功率值*/
    INT16 asPaMidCalPwr[4];                  /*PA中档校准功率值*/
    INT16 asPaLowCalPwr[10];                 /*PA低档校准功率值*/
    INT16 asTxFreqCmpHighVal[4][16];         /*PA高档补偿值 1/8db为单位*/
    INT16 asTxFreqCmpMidVal[4][16];          /*PA中档补偿值*/
    INT16 asTxFreqCmpLowVal[10][16];         /*PA低档补偿值*/
    INT16 asTxTempCmpVal[16][32];  /*tx温补*/
    UL_APT_PARA_STRU                   stAptPara;        /*APT功能使能开关*/
    UL_APT_GAIN_VS_VBIAS_STRU          stPaHighPdmTbl;   /*APT PDM高档位控制字*/
    UL_APT_GAIN_VS_VBIAS_STRU          stPaMidPdmTbl;    /*APT PDM中控制字*/
    UL_APT_GAIN_VS_VBIAS_STRU          stPaLowPdmTbl;    /*APT PDM低控制字*/
    /*MPR begin*/
    UINT16 ausMprVal[4];
    /*MPR end*/
    UL_AMPR_STRU astAMprVal[LPHY_MAX_BANDWIDTH_NUM];
    /* END:   Added by xueqiuyan, 2012/5/17 */
    UINT32 ulAmprValNS05;
    UINT16 usAmprValNS09[2];
    /* END:   Added by xueqiuyan, 2012/10/10 */
    /* BEGIN: Added by xueqiuyan, 2013/1/4   PN:ONE_RB*/
    UL_ONE_RB_MPR_STRU stOneRbMprVal;
    /* END:   Added by xueqiuyan, 2013/1/4 */
    INT16  asAptPaHighCmp[UL_APT_VBIAS_NUM];             /*APT PA增益补偿*/
    INT16  asAptPaMidCmp[UL_APT_VBIAS_NUM];              /*APT PA增益补偿*/
    INT16  asAptPaLowCmp[UL_APT_VBIAS_NUM];              /*APT PA增益补偿*/
	/*NV_TX_CMP_RSV_STRU   stTxCmpRsv;*/
	NV_ANT_SAR_STRU   stAntSarPwr;
    LTE_TX_DIVERSITY_LOSS_COMP stDivComp;
    NV_APC_ATT_TABLE_STRU astApcAttTable[APC_ATT_MAX_NUM];     /*衰减表*/
    NV_PA_POWER_DIFFERENCE stPaPowerDiff;
    NV_TX_APC_GAIN_STRU stTxGainStatus;
    RF_TXIQ_CAL_STRU stTxiqCal;
    NV_TX_RF_BB_ATT_STRU stBbAttPara;
    NV_TX_RF_BIAS_STRU stBias;
    NV_TX_RF_FREQ_COMP_STRU stFreq;
    NV_TX_PA_TEMP_COMP stPaTempComp;
    NV_TX_ATTEN_TABLE stAttenTable;
    NV_TX_POWERDET_VOLTAGE stPowerVoltage;

}NV_BAND_TXPATH_PARA_STRU;

typedef struct
{
    UINT16                      usModemLoss[2];                        /*Modem与整机天线间线损*/
    UINT16                      ausTempSensor[32];                      /*PA热敏电阻检测到的平台温度转变成电压*/
}NV_BAND_COMMON_PARA_STRU;



typedef struct
{
	UINT16    usLowRbArea;         /*带宽内最下端多少个RB内需要补偿*/
	UINT16    usHighRbArea;        /*带宽内最上端多少个RB内需要补偿*/
	UINT16    usRbNum;             /*小于多少个RB需要补偿*/
	INT16     sLowPosCmpVal;       /*低RB位置补偿值*/
	INT16     sHighPosCmpVal;      /*高RB位置补偿值*/
}NV_TX_RF_ABB_FILTER_CMP_STRU;

typedef struct
{
	NV_TX_RF_ABB_FILTER_CMP_STRU stBandWidthCmp[4]; /*针对5 10 15 20M带宽补偿*/
}NV_TX_FILTER_CMP_STRU;


/* Begin: Added by luzhejun, 2013-09-23 PN:LTE_WIFI*/
typedef struct
{
    UINT16 				  usLWCoexEnbale;
    UINT16                usTimerAheadTx;
    UINT16				  usTimerDelayTx;
    UINT16                usTimerAheadRx;
    UINT16				  usTimerDelayRx;
    UINT16				  Reserved;	
}NV_LPHY_LWCOEX_INIT_PARA_STRU;

/* END: Added by luzhejun, 2013-09-23 PN:LTE_WIFI*/


#if 1
typedef enum
{
	MIPI_WRITE = 0x3,
	MIPI_READ
}LPHY_MIPI_CMD_TYPE_ENUM;
typedef UINT32 LPHY_MIPI_CMD_TYPE_ENUM_UINT32;

typedef enum
{
	LTE_TO_COM_RF0_SSI  = 0x2,
	LTE_TO_COM_RF1_SSI
}LPHY_MIPI_SSI_OUT_SEL_ENUM;
typedef UINT32 LPHY_MIPI_SSI_OUT_SEL_ENUM_UINT32;

typedef enum
{
	MIPI_ARB_CFG_DISABLE  = 0x0,
	MIPI_ARB_CFG_ENABLE       /*mipi使用仲裁*/
}LPHY_MIPI_ARB_CFG_ENUM;
typedef UINT32 LPHY_MIPI_ARB_CFG_ENUM_UINT32;

typedef enum
{
	PA_STAR_DISABLE = 0x0,
	PA_STAR_ENABLE
}PA_STAR_SWITCH_ENUM;
typedef UINT32 PA_STAR_SWITCH_ENUM_UINT32;

typedef enum
{
	PA_STAR_POWER_OFF   = 0x0,
	PA_STAR_POWER_ON
}PA_STAR_POWER_PROC_ENUM;
typedef UINT32 PA_STAR_POWER_PROC_ENUM_UINT32;

typedef struct
{
	PA_STAR_SWITCH_ENUM_UINT32 enPaStarEn;
	UINT32 			    ulSlaveAddr;
	UINT32 				ulCmdTypeWR;
	UINT32				ulCmdTypeRD;
	UINT32              ulByteCnt;
	UINT32				ulPaStarAdvanceTime;
}LPHY_PA_STAR_MIPI_INIT_STRU;

typedef struct
{
	UINT8 ucRegAddr;    /*PA_STAR寄存器地址*/
	UINT8 ucRegCfg;     /*PA_STAR寄存器对应配置值*/
}LPHY_PA_STAR_CONFIG_STRU;

typedef struct
{
	UINT8 ucRegAddr;    /*PA_STAR寄存器地址*/
	UINT8 ucPowerOn;     /*PA_STAR寄存器对应配置值*/
	UINT8 ucPowerOff;
	UINT8 ucResv;
}LPHY_PA_STAR_POWER_PROC_STRU;


typedef struct
{
	UINT32 ulMipiCmd01;
	UINT32 ulMipiCmd02;
}LPHY_PA_STAR_MIPI_CMD_STRU;


typedef struct
{
	LPHY_PA_STAR_CONFIG_STRU stBuck0InitPara;
	LPHY_PA_STAR_CONFIG_STRU stBuck1InitPara;
	LPHY_PA_STAR_CONFIG_STRU stBuck2InitPara;
	LPHY_PA_STAR_CONFIG_STRU stLDO1InitPara;
	LPHY_PA_STAR_CONFIG_STRU stLDO2InitPara;
	LPHY_PA_STAR_CONFIG_STRU stResv;
	UINT32					 ulResvNum;
	LPHY_PA_STAR_CONFIG_STRU stInitParaResv[12];
}LPHY_PA_STAR_INIT_STRU;


typedef struct
{
	LPHY_PA_STAR_POWER_PROC_STRU stBuck0PowerProc;
	LPHY_PA_STAR_POWER_PROC_STRU stBuck1PowerProc;
	LPHY_PA_STAR_POWER_PROC_STRU stBuck2PowerProc;
	LPHY_PA_STAR_POWER_PROC_STRU stLDO1PowerProc;
	LPHY_PA_STAR_POWER_PROC_STRU stLDO2PowerProc;
	LPHY_PA_STAR_POWER_PROC_STRU stPowerResv[8];
}LPHY_PA_STAR_CTRL_STRU;

typedef struct
{
	LPHY_PA_STAR_MIPI_INIT_STRU stMipiInit;
	LPHY_PA_STAR_INIT_STRU      stPaStarInit;
	LPHY_PA_STAR_CTRL_STRU      stPaStarCtrl;
}NV_LPHY_PASTAR_NV_PARA_STRU;

#endif

typedef struct
{
    UINT16                          usXoType;
    UINT16                          usDcxoFeatureEnable;
}DCXO_NV_ENABLE_STRU;

typedef struct
{
    INT16                           sPaTempTemp;                           /* 温度:0.1度 */
    UINT16                          usPaTempVol;                           /* 热敏电阻检测电压 */
}DCXO_NV_TEMP_ADC_STRU;

typedef struct
{
    DCXO_NV_TEMP_ADC_STRU           astXoTempAdc[32];
}DCXO_NV_TEMP_ADC_TABLE_STRU;

typedef struct
{
    /* A3 A2 A1 A0 系数 */
    UINT32                          aulMantissa[4];
    UINT16                          ausExponent[4];
}DCXO_NV_TEMP_COEF_TABLE_STRU;

typedef struct
{
    UINT16                          usDefaultAfcValue;
    UINT16                          usAfcCfix;
    UINT16                          usAfcCvar;
    UINT16                          usAfcIadj;
}DCXO_NV_TEMP_AFC_PARA_STRU;

typedef struct
{
    INT16                           asBandWithFixCmp[4];  /*校准使用1.4M，此是其他带宽相对1.4的补偿值*/
    INT16                           sCmpValRsv0;
    INT16                           sCmpValRsv1;
    INT16                           sCmpValRsv2;
    INT16                           sCmpValRsv3;
}NV_LPHY_TX_CMP_STRU;
/*****************************************band无关的nv项*********************************/
typedef struct
{
    NV_TIMING_PARA_STRU         stTiming;           /*定时NV项*/
    NV_EMU_FAKECELL_PARA_STRU   stEmuFakeCell;      /*能量测量小区定时失效判决*/
    NV_CQI_PARA_STRU            stCqi;              /*CQI NV项*/
    NV_ANTCORR_PARA_STRU        stCorr;             /*相关 NV项*/
    NV_RLM_PARA_STRU            stRLM;              /*RLM相关项*/
    AFC_NV_PARA_STRU            stAFC;              /*AFC NV项*/
    NV_IRC_PUB_STRU             stIrcPub;
    NV_CHE_INTP_STRU            stCheIntp;
    NV_VITERBI_PARA_STRU        stViterbi;
    NV_TURBO_PARA_STRU          stTurbo;
    NV_DEM_LIST_STRU            stDEM;
    NV_LPHY_AGC_BASE_TABLE_STRU stAgcBase;          /*AGC基准表*/
    NV_UL_PARA_STRU             stUl;
    NV_AGC_PARA_STRU            stAGC;                         /*agc NV项 */
    NV_VERSION_STRU             stVersion;          /*NV 版本信息*/

    NV_LPHY_DSP_CONFIG          stDspCfg;           /*DSP开机初始化公共参数配置NV*/
    NV_GULPHY_COMMON_PARA_CONFIG stGULCommParaCfg;  /*GUL多模公共参数配置NV结构体*/

    LTE_TCXO_DYNAMIC_CONFIG_STRU    stVctcxoDynamicConfig;
    UINT16 	usVctcxoInit;	                        /*Vco初值*/
    UINT16      usRsv1;

    NV_BT_CMP_SWITCH_STRU stBtCmpSwitch;

    /*NV_APC_ATT_TABLE_STRU astApcAttTable[APC_ATT_MAX_NUM];*/     /*衰减表*/


	NV_DSP_CONFIG_TIME_STRU      stRFECfgTime;      /*DSP相关配置时间移入NV项中*/
   /* BEGIN: Added by shijiahong, 2011/12/23   PN:DTS201112302952*/
   NV_LPHY_RFIC_INITIAL_CFG_STRU           stNvLteRFInitialCfg;  /*Hi6360 RF初始化配置*/
   NV_LPHY_LINECTRL_COMN_INFO_STRU         stNvLteLineCtrlComn;  /*公共部分线控配置*/
   NV_LPHY_LINECTRL_PRIV_INFO_STRU         stNvLteLineCtrlPriv;  /*BAND相关线控配置*/

    /*NV_LPHY_RF_LINECTRL_INFO_STRU         stLphyRFLineCtrlCfgPara;*/
   /* END:   Added by shijiahong, 2011/12/23   PN:DTS201112302952*/
    /* BEGIN: Added by luliwu,  2012/2/3  PN: DTS_TISTISTIS */
    NV_PHY_FUNC_VERIFY_STUB_STRU       stPhyFuncDebugPara;
    /* END:   Added by luliwu,  2012/2/3  PN: DTS_TISTISTIS */
    NV_RX_BT_LEVEL_MAP_TABLE_STRU stRxBtMapTable;

    VOS_UINT32                    ulSleepAddr;
	NV_TX_FILTER_CMP_STRU   stTxFilterCmp;

	NV_LPHY_PASTAR_NV_PARA_STRU stPaStarCfg;

    /* BEGIN: Added by w00180842, 2013/8/19   PN:tuner*/
	NV_LPHY_TUNER_NV_PARA_STRU stTunerPara;
    /* END:   Added by w00180842, 2013/8/19 */

    LTE_DRX_NV_PARA_STRU stLteDrxPara;
    DCXO_NV_ENABLE_STRU             stDcxoNvEnable;

    DCXO_NV_TEMP_ADC_TABLE_STRU     stDcxoTempAdcTable;

    DCXO_NV_TEMP_COEF_TABLE_STRU    stDcxoTempCoefTable;

    DCXO_NV_TEMP_AFC_PARA_STRU      stDcxoTempAfcPara;
 
    /* Begin: Added by luzhejun, 2013-09-23 PN:LTE_WIFI*/ 
    
    NV_LPHY_LWCOEX_INIT_PARA_STRU  stLWCoexInitPara;
    /* END: Added by luzhejun, 2013-09-23 PN:LTE_WIFI*/

    NV_LPHY_TX_CMP_STRU   stTxCmpPara;
}LTE_NV_PARA_STRU;
/**********************************************************************************************/
/*******************************band相关的nv项*******************************************/
typedef struct
{
    NV_BAND_COMMON_PARA_STRU         stCommon;
    NV_BAND_RXPATH_PARA_STRU         stRxPath;
    NV_BAND_TXPATH_PARA_STRU         stTxPath;
}LTE_BAND_NV_PARA_STRU;
/**********************************************************************************************/

/*定义全局变量,供各个模块访问*/
extern LTE_NV_PARA_STRU  *gptrLteNvPara;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LTE_NV_PARA_H__ */

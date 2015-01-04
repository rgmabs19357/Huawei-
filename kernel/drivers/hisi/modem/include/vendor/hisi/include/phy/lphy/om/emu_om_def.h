

/************************************************************
                     包含其它模块的头文件
************************************************************/
#ifndef __EMU_OM_DEF_H__
#define __EMU_OM_DEF_H__

#include "om_base_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                               宏定义
************************************************************/
#define EMU_FREQ_NUM                 5
#define EMU_CELL_NUM                 16

/************************************************************
                             数据结构定义
************************************************************/


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_EMU__
{
    LPHY_REQ_EMU_RESERVED            = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_EMU_ENA_ALG,              /*使能能量测量结果上报*/
    LPHY_REQ_EMU_ENA_CFG,              /*配置能量测量的算法开关*/

    LPHY_REQ_EMU_DEBUG,                /*配置debug上报信息是否打开*/
    LPHY_REQ_EMU_ENA_TESTRPT,          /*配置测试部需要的使能 */
}LPHY_REQ_MSGID_EMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_EMU_ENUM_UINT16;


typedef struct _EMU_ALG_CTRL
{
    UINT16 ebTimingLimitFlag;                    /* 时偏补偿模块中限幅模块是否打开               ，TRUE-打开；FALSE-关闭*/
    UINT16 ebDrxAlphaFilterFlag;                 /* DRX态下信道总功率/噪声Alpha滤波清零开关      ，TRUE-打开；FALSE-关闭*/
    UINT16 eDbAlphaFilterFlag;                   /* dB域alpha滤波清零开关                      ，TRUE-打开；FALSE-关闭*/
    UINT16 usMeasSymbolNums;                     /* 每个测量周期测量的符号数*/
}EMU_ALG_CTRL_STRU;

/* 算法标志结构*/
typedef struct _EMU_ALG_CTRL_REQ
{
    LPHY_REQ_MSGID_EMU_ENUM_UINT16   usReqType;  /* 请求类型*/
    UINT16                           ulReaserve;
    EMU_ALG_CTRL_STRU                stAlg_Ctrl;
}EMU_ALG_CTRL_REQ_STRU;

/* 算法数据结构*/
typedef struct _EMU_ALG_RESULT_REQ
{
    LPHY_REQ_MSGID_EMU_ENUM_UINT16   usReqType;                      /* 请求类型*/
    UINT16                           ebReportFlag;                   /* 0 - 不上报；1-上报*/
    UINT16                           usFreqReportNum[EMU_FREQ_NUM];  /* 频点小区上报数量*/
}EMU_ALG_RESULT_REQ_STRU;


/* 测试部上报请求*/
typedef struct _EMU_TEST_CTRL_REQ
{
    LPHY_REQ_MSGID_EMU_ENUM_UINT16   usReqType;  /* 请求类型*/
    UINT16                           ulReaserve;
    UINT16                           ebTest_Rpt;
}EMU_TEST_CTRL_REQ_STRU;

#if 0
/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_EMU__
{
    LPHY_CNF_EMU_RESERVED            = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_CNF, 0x0),
    LPHY_CNF_EMU_ENA_ALG,              /*使能公共测量结果上报*/
    LPHY_CNF_EMU_ENA_CFG,              /*配置公共测量的算法开关*/
}LPHY_CNF_MSGID_EMU_ENUM;
typedef UINT16 LPHY_CNF_MSGID_EMU_ENUM_UINT16;

/* REQ时返回的CNF结构*/
typedef struct _EMU_CNF_REQ{
    LPHY_CNF_MSGID_EMU_ENUM_UINT16   usCnfType;  /* 请求类型*/
    UINT16                           ulReaserve;
}EMU_CNF_STRU;

#endif

/************************************************************
                           3. sg数据结构定义
************************************************************/
typedef enum __LPHY_SG_MSGID_EMU__
{
    LPHY_IND_EMU_RESERVED            = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_EMU_ENA_ALG,              /*使能能量测量结果上报*/
    LPHY_SG_EMU_ENA_TEST,             /*使能测试部需要的测量结果上报*/
}LPHY_SG_MSGID_EMU_ENUM;
typedef UINT16 LPHY_SG_MSGID_EMU_ENUM_UINT16;

/* 返回算法结果*/
typedef struct _EMU_RESULT_REPORT
{
    UINT16 usFreqInfo;                           /* 频点值*/
    UINT16 usCellID;                             /* 小区ID*/
    INT16  sTimingDelta;                         /* 定时调整值*/
    UINT16 usReserved;
    INT32  ulRsrp_R0;                            /* 接收天线0的RSRP*/
    INT32  ulRsrp_R1;                            /* 接收天线1的RSRP*/
    INT32  ulRsrq_R0;                            /* 接收天线0的RSRQ*/
    INT32  ulRsrq_R1;                            /* 接收天线1的RSRQ*/
    INT32  ulRssi_R0;                            /* 接收天线0的RSSI*/
    INT32  ulRssi_R1;                            /* 接收天线1的RSSI*/
}EMU_RESULT_REPORT_STRU;

/* 返回测试部需要的主小区的信息*/
typedef struct _EMU_RESULT_TESTRPT
{
    UINT16 usCellID;                            /* 小区ID*/
    UINT16 usReserved;
    INT32  lRsrp;                               /* 接收天线0的RSRP*/
    INT32  lRsrp_R0;                            /* 接收天线0的RSRP*/
    INT32  lRsrp_R1;                            /* 接收天线1的RSRP*/
    INT32  lRssi_R0;                            /* 接收天线0的RSSI*/
    INT32  lRssi_R1;                            /* 接收天线1的RSSI*/
    INT32  lRsrq;                               /* 接收天线0的RSRQ*/
    INT32  lSINR;
}EMU_RESULT_TESTRPT_STRU;


typedef struct _EMU_RESULT_SG
{
    UINT16 usCellNum;                            /* 有效小区数*/
    UINT16 usReserved;
    EMU_RESULT_REPORT_STRU  stCell[ EMU_CELL_NUM ];
}EMU_RESULT_SG_STRU;


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum
{
    LPHY_TRACE_EMU_CONN_INTRA_EVT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_EMU_CONN_INTER_EVT,
    LPHY_TRACE_EMU_CONN_GSM_EVT,
    LPHY_TRACE_EMU_CONN_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_INTRA_EVT,
    LPHY_TRACE_EMU_IDLE_INTER_EVT,
    LPHY_TRACE_EMU_IDLE_GSM_EVT,
    LPHY_TRACE_EMU_IDLE_WCDMA_EVT,
    LPHY_TRACE_EMU_IDLE_TASK_UPDT_EVT,
    LPHY_TRACE_EMU_CS_ITO_UPDT_EVT,
    LPHY_TRACE_EMU_CS_FINISH_EVT,
    LPHY_TRACE_EMU_IDLE_SETUP_EVT,
    LPHY_TRACE_EMU_IDLE_RELEASE_EVT,
    LPHY_TRACE_EMU_CONN_SETUP_EVT,
    LPHY_TRACE_EMU_CONN_RELEASE_EVT,
	LPHY_TRACE_EMU_HOLD_EVT,
	LPHY_TRACE_EMU_UNHOLD_EVT,
	LPHY_TRACE_EMU_SLAVE_DONE_EVT,
	LPHY_TRACE_EMU_BSIC_REQ_EVT,
	LPHY_TRACE_EMU_ITAT_DONE_EVT,
	LPHY_TRACE_EMU_L_INTER_SHIFT_EVT,
	LPHY_TRACE_EMU_W_FREQ_SHIFT_EVT,
	LPHY_TRACE_EMU_TASK_STOP_EVT,
	LPHY_TRACE_EMU_SERV_LOST_EVT,
	LPHY_TRACE_EMU_PAR_LOW_EVT,
	LPHY_TRACE_EMU_NO_FREE_CELL_EVT,
    LPHY_TRACE_EMU_EVT_BUTT
}LPHY_TRACE_EMU_EVT_ENUM;

/*LPHY_TRACE_EMU_CONN_INTRA_EVT ~ ?*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_TRACE_EMU_EVT_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum
{
    LPHY_WARN_EMU_LOSE_INT              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_ERROR, 0x0),
    LPHY_WARN_EMU_TDD_CELL_POSITION,
    LPHY_WARN_EMU_TRACKER_LOW_PAR,
    LPHY_WARN_EMU_CS_LOSE_SERV,
    LPHY_WARN_EMU_EST_TOF_TOO_LARGE,
    LPHY_WARN_EMU_AFC_UNLOCK,
    LPHY_WARN_EMU_AFC_HOLD
}LPHY_ERROR_EMU_ENUM;

/*LPHY_WARN_EMU_LOSE_INT ~ ?*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];
}LPHY_ERROR_EMU_STRU;



/************************************************************
                           6. IND数据结构定义
************************************************************/
typedef enum
{
    LPHY_IND_EMU_EMU_CFG_GLOBAL              = OM_CMD_ID(LPHY_EMU_MID, OM_TYPE_IND, 0x0),
    LPHY_IND_EMU_EMU_CFG_CHANNELS,
    LPHY_IND_EMU_EMU_INT,
    LPHY_IND_EMU_EMU_RESULT,
    LPHY_IND_EMU_EMU_STATE
}LPHY_IND_EMU_ENUM;

/*LPHY_IND_EMU_EMU_CFG_GLOBAL*/
typedef struct
{
    UINT32 ulCell_Band;
    UINT32 ulInter_En;
    UINT32 ulTiming_En;
    UINT32 ulAngle_Th;
    UINT32 ulDelta_Coeff;
    UINT32 ulAagc_Pos;
    UINT32 ulAdj_En;
    UINT32 ulEmu_Ctrl;
}LPHY_IND_EMU_GLOBAL_CFG_STRU;

typedef struct
{
    UINT32 ulInf;
    UINT32 ulSync;
    UINT32 ulTiming_delta;
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
}LPHY_EMU_BBP_ONE_CH_CFG_STRU;

/*LPHY_IND_EMU_EMU_CFG_CHANNELS*/
typedef struct
{
    #if 0
    UINT16 usFreq;
    UINT16 usCellNum;
    UINT16 usCellIdx[8];
    UINT32 ulEmu_SfSel;
    UINT32 ulEmu_RptMode;
    #endif
    UINT32 ulEmuBwReg;
    UINT32 ulEmuInterEnReg;
    UINT32 ulEmuCtrlReg;
    UINT32 ulEmu_RptMode;
    UINT32 ulEmuFddTddSel;

    LPHY_EMU_BBP_ONE_CH_CFG_STRU stBbpChCfg[8];

    UINT32 ulSym_num0;
    UINT32 ulSym_num1;
    UINT32 ulTiming_kalman_idx0;
    UINT32 ulTiming_kalman_idx1;
    UINT32 ulRsrp_kalman_idx0;
    UINT32 ulRsrp_kalman_idx1;
    UINT32 ulRsrp_alpha;
    UINT32 ulRsrp_first_alpha;
    UINT32 ulEmu_en;
    UINT32 ulEmu_start;
    UINT32 ulEmu_stop;
    UINT32 ulEmu_Dma_en;
}LPHY_IND_EMU_CHANNELS_CFG_STRU;


/*LPHY_IND_EMU_EMU_INT*/
typedef struct
{
    UINT32  ulEmuEvtInfo[6];/*usFreqInfo; BALONGV7_SMU_REG_SMU_SYM_CNT0_REG; BALONGV7_SMU_REG_SMU_SYM_CNT1_REG*/
}LPHY_IND_EMU_INT_STRU;

typedef struct
{
    UINT32 ulLast_delta_i0;
    UINT32 ulLast_delta_q0;
    UINT32 ulLast_delta_i1;
    UINT32 ulLast_delta_q1;
    UINT32 ulLast_agc_gain0;
    UINT32 ulLast_agc_gain1;
    UINT32 ulLast_pn_alpha0;
    UINT32 ulLast_pn_alpha1;
    UINT32 ulLast_rsrp0;
    UINT32 ulLast_rsrp1;
    UINT32 ulLast_rssi0;
    UINT32 ulLast_rssi1;
    UINT32 ulLast_theta;
    UINT8  ucTiming_kalman_index;               /**/
    UINT8  ucRsrp_kalman_index;                 /**/
    UINT8  ucAlpha_Init;                       /**/
    UINT8  ucReserved;                          /**/
}EMU_OM_CELL_BBP_CTX_STRU;


typedef struct
{
    INT16                       sRssi_current0;
    INT16                       sRssi_current1;
    INT16                       sRsrp_current0;
    INT16                       sRsrp_current1;
    INT16                       sRsrq_current0;
    INT16                       sRsrq_current1;
    INT16                       sRsrp_rpt;
    INT16                       sRsrq_rpt;
}EMU_OM_CALC_RESULT_STRU;


typedef struct
{
    EMU_OM_CELL_BBP_CTX_STRU    stEmuBbpCellCtx;
    #if 0
    INT16                       sRssi_current0;
    INT16                       sRssi_current1;
    INT16                       sRsrp_current0;
    INT16                       sRsrp_current1;
    INT16                       sRsrq_current0;
    INT16                       sRsrq_current1;
    INT16                       sRsrp_last;
    INT16                       sRsrq_last;
    INT16                       sRssi_last;
    #endif
    EMU_OM_CALC_RESULT_STRU     stResult;
    UINT16                      usCellId;
    UINT16                      usMeasSymb;
}LPHY_EMU_CELL_RESULT_STRU;


/*LPHY_IND_EMU_EMU_RESULT*/
typedef struct
{
    UINT16 usFreq;
    UINT16 usCellNum;
    UINT32 ulAfcPdm;
    UINT32 ulDemTim;
    /*UINT32 ulAAgc0;*/
    /*UINT32 ulAAgc1;*/
    UINT32 ulAfcState;
    LPHY_EMU_CELL_RESULT_STRU astCellResult[8];
}LPHY_IND_EMU_RESULT_STRU;


/*LPHY_IND_EMU_EMU_STATE*/
typedef struct
{
    UINT32 ulCsInterStartCnt;
    UINT32 ulCsSlaveStartCnt;
    UINT32 ulEmuIntraCfgCnt;
    UINT32 ulEmuIntraIntCnt;
    UINT32 ulEmuInterCfgCnt;
    UINT32 ulEmuInterIntCnt;
    UINT32 ulEmuSlaveCfgCnt;
    UINT32 ulEmuSlaveIntCnt;
    UINT32 ulEmuRptIntraCnt;
    UINT32 ulEmuRptInterCnt;
    UINT32 ulEmuWOccasionCnt;
    UINT32 ulEmuGOccasionCnt;
    UINT32 ulEmuWFinishCnt;
    UINT32 ulEmuGFinishCnt;
}LPHY_IND_EMU_STATE_STRU;



typedef struct
{
    UINT16  ausCQI[2];
    UINT16  usRI;
    UINT8   aucRes[2];
}LPHY_IND_EMU_AT_RI_CQI_STRU;

typedef struct
{
    UINT16  usOpId;
    UINT16  usTa;
    INT32   lSINR;
    LPHY_IND_EMU_AT_RI_CQI_STRU stRiCqiPara;
}LPHY_IND_EMU_AT_MEAS_STRU;

/* END:   Added by xueqiuyan, 2012/12/5 */

/************************************************************
                             接口函数声明
 ************************************************************/




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __EMU_OM_DEF_H__ */

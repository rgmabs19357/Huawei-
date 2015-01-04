/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : cmu_om_def.h
  版 本 号   : 初稿
  生成日期   : 2011年03月29日
  最近修改   :
  功能描述   : 定义公共测量模块OM需要上报的结构体,该文件最终会交付给HiStudio使用
  函数列表   :
  修改历史   :
  1.日    期   : 2011年03月29日
    修改内容   : 创建文件

******************************************************************************/

/************************************************************
                     包含其它模块的头文件
************************************************************/
#include "om_base_def.h"

/************************************************************
                               宏定义
************************************************************/
#define CMU_SB_MAX                 25

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __CMU_OM_DEF_H__
#define __CMU_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CMU__
{
    LPHY_REQ_CMU_RESERVED            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_CMU_ENA_ALG,              /*使能公共测量结果上报*/
    LPHY_REQ_CMU_ENA_CFG,              /*配置公共测量的算法开关*/
}LPHY_REQ_MSGID_CMU_ENUM;
typedef UINT16 LPHY_REQ_MSGID_CMU_ENUM_UINT16;

typedef struct _CMU_ALG_CTRL
{
    UINT16 ebTimingLimitFlag;                    /* 时偏补偿模块中限幅模块是否打开               ，TRUE-打开；FALSE-关闭*/
    UINT16 ebDrxAlphaFilterFlag;                 /* DRX态下信道总功率/噪声Alpha滤波清零开关      ，TRUE-打开；FALSE-关闭*/
    UINT16 ebDrxTimingFilterFlag;                /* DRX态下时偏滤波清零开关                      ，TRUE-打开；FALSE-关闭*/
    UINT16 ebConnectAlphaFilterFlag;             /* CONNECT态下信道总功率/噪声Alpha滤波清零开关  ，TRUE-打开；FALSE-关闭*/
}CMU_ALG_CTRL_STRU;

/* 算法标志结构*/
typedef struct _CMU_ALG_CTRL_REQ
{
    LPHY_REQ_MSGID_CMU_ENUM_UINT16   usReqType;  /* 请求类型*/
    UINT16                           ulReaserve;
    CMU_ALG_CTRL_STRU                stAlg_Ctrl;
}CMU_ALG_CTRL_REQ_STRU;

/* 算法数据结构*/
typedef struct _CMU_ALG_RESULT_REQ
{
    LPHY_REQ_MSGID_CMU_ENUM_UINT16   usReqType;     /* 请求类型*/
    UINT16                           ebReportFlag;  /* 0 - 不上报；1-上报*/
}CMU_ALG_RESULT_REQ_STRU;

#if 0
/************************************************************
                           2. CNF数据结构定义
************************************************************/
typedef enum __LPHY_CNF_MSGID_CMU__
{
    LPHY_CNF_CMU_RESERVED            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_CNF, 0x0),
    LPHY_CNF_CMU_ENA_ALG,              /*使能公共测量结果上报*/
    LPHY_CNF_CMU_ENA_CFG,              /*配置公共测量的算法开关*/
}LPHY_CNF_MSGID_CMU_ENUM;
typedef UINT16 LPHY_CNF_MSGID_CMU_ENUM_UINT16;

/* REQ时返回的CNF结构*/
typedef struct _CMU_CNF_REQ
{
    LPHY_CNF_MSGID_CMU_ENUM_UINT16   usCnfType;  /* 请求类型*/
    UINT16                           ulReaserve;
}CMU_CNF_STRU;

#endif

/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum __LPHY_SG_MSGID_CMU__
{
    LPHY_IND_CMU_RESERVED            = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_CMU_ENA_ALG,              /*使能公共测量结果上报*/
}LPHY_SG_MSGID_CMU_ENUM;
typedef UINT16 LPHY_SG_MSGID_CMU_ENUM_UINT16;

/* 返回算法结果*/
typedef struct
{
    UINT32 ulBwNoise_Rs_Raw_R0;                  /* 接收天线0的CRS不移位宽带噪声*/
    UINT32 ulBwNoise_Rs_Raw_R1;                  /* 接收天线1的CRS不移位宽带噪声*/
    INT16  sSinr_Raw_R0;                         /* 接收天线0的不移位SINR*/
    INT16  sSinr_Raw_R1;                         /* 接收天线1的不移位SINR*/
    UINT32 ulRsrp_Raw_R0;                        /* 接收天线0的不移位RSRP*/
    UINT32 ulRsrp_Raw_R1;                        /* 接收天线1的不移位RSRP*/
    UINT32 ulBwAvgRsrp_Shift;                    /* 两天线平均后的移位RSRP*/
    UINT32 ulShiftedBitsNum;                     /* 右移比特数*/
    UINT32 ulBwAvgNoise_Rs_Shift;                /* 两天线平均后的移位宽带导频噪声*/
    UINT16 usSBwAvgNoise_Rs_Shift[ CMU_SB_MAX ]; /* 两天线平均后的移位子带导频噪声,用 0 表示无效值*/
}CMU_RESULT_SG_STRU;

/************************************************************
                           4. TRACE数据结构定义
************************************************************/
typedef enum __LPHY_TRACE_CMU_
{
    LPHY_TRACE_CMU_RESERVED              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_TRACE, 0x0),
	LPHY_TRACE_CMU_STATE,                        /* 跟踪CMU的状态*/
	LPHY_TRACE_CMU_CFG,                          /* 跟踪CMU的配置过程*/
	LPHY_TRACE_CMU_RESULT,                       /* 跟踪CMU的计算过程*/
	LPHY_TRACE_CMU_CELL,                         /* 跟踪CMU的小区状况*/
	LPHY_TRACE_CMU_SFNUM,                        /* 跟踪CMU的子帧号*/
}LPHY_TRACE_CMU_ENUM;
typedef UINT16 LPHY_TRACE_CMU_ENUM_UINT16;


typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuState;
}LPHY_TRACE_CMU_STATE_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuCell;
}LPHY_TRACE_CMU_CELL_STRU;
typedef enum
{
    CMU_CFG_IDLE = 0,
    CMU_CFG_WAIT,
    CMU_CFG_UPLINK,
    CMU_CFG_MAXTAU,
    CMU_CFG_ALL,
    CMU_CFG_SERVCELL,
    CMU_CFG_ONLYTAU,
}CMU_CONFIG_ENUM;

typedef struct
{
    CMU_CONFIG_ENUM      enCmuCfg;
}LPHY_TRACE_CMU_CFG_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuResult;
}LPHY_TRACE_CMU_RESULT_STRU;

typedef struct
{
    UINT32      ulLineNum;
    UINT32      ulCmuSFNum;
}LPHY_TRACE_CMU_SFNUM_STRU;


/************************************************************
                           5. ERROR数据结构定义
************************************************************/
typedef enum __LPHY_ERROR_CMU_ENUM__
{
    /*PBCH, ERROR ID 1 - 15*/
    LPHY_ERROR_CMU_LOG_ERROR              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_CMU_EXP_ERROR,
    LPHY_ERROR_CMU_DMA_ERROR
}LPHY_ERROR_CMU_ENUM;
typedef UINT16 LPHY_ERROR_CMU_ENUM_UINT16;

typedef struct
{
    UINT32      ulErrorType;
    INT32       lErrorValue;
}LPHY_TRACE_CMU_ERROR_STRU;



/************************************************************
                           6. DEBUG数据结构定义
************************************************************/
typedef enum __LPHY_DEBUG_CMU_ENUM__
{
    LPHY_DEBUG_CMU_RESERVED                         = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_DEBUG, 0x0),
    LPHY_DEBUG_CMU_LOGIC_REG,
    LPHY_DEBUG_CMU_BUFFER_VALUE,
    LPHY_DEBUG_CMU_CURRCAL_VALUE,
}LPHY_DEBUG_CMU_ENUM;
typedef UINT16 LPHY_DEBUG_CMU_ENUM_UINT16;

/* BEGIN: Added by xueqiuyan, 2012/9/28   PN:CMCC_DT*/
/************************************************************
                           7. DT数据结构定义
************************************************************/
typedef enum
{
    LPHY_DT_MEAS_INFO_REQ              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_DT, 0x1)

}LPHY_DT_REQ_CMU_ENUM;

typedef struct __DT_MEAS_INFO_REQ_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16   usEna;
    UINT16   usReportPeriod;
} LPHY_DT_MEAS_INFO_REQ_STRU;


typedef enum
{
    LPHY_DT_MEAS_INFO_IND              = OM_CMD_ID(LPHY_CMU_MID, OM_TYPE_DT, 0x1001)

}LPHY_DT_IND_CMU_ENUM;

typedef struct
{
    LTE_CP_TYPE_ENUM_UINT16 enCpType;
    INT16  sCRS_SinrR0;
    INT16  sCRS_SinrR1;
    INT16  sCRS_AvgSinr;
    INT32  lCRS_Rsrq;
    INT32  lCRS_RsrpR0;
    INT32  lCRS_RsrpR1;
    INT32  lDRS_RsrpR0;
    INT32  lDRS_RsrpR1;
    INT32  lCRS_RssiR0;
    INT32  lCRS_RssiR1;
} LPHY_DT_MEAS_INFO_IND_STRU;


/* END:   Added by xueqiuyan, 2012/9/28 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CMU_OM_DEF_H__ */

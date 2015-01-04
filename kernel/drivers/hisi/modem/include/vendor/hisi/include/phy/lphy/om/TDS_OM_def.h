/******************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TDS_OM_def.h
  版 本 号   : 初稿
  生成日期   : 2012年2月16日
  最近修改   :
  功能描述   : TDS_OM对外接口头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年2月17日
    修改内容   : 创建文件
    				   :	2012.05.20 y00194530 修改用于与HSO 以及TDS各态调用
    

******************************************************************************/

#ifndef __TDS_OM_def_H__
#define __TDS_OM_def_H__
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/
/*#define   TDS_OAM_USE_SOCP*/
#define   TDS_OAM_USE_UART  	0
#define   TDS_OAM_USE_SOCP  	1

#define   TDS_OAM_MSG_BASE              (0x70000000UL)

#define   TDS_OAM_ID_MSG01				(TDS_OAM_MSG_BASE 	+ 	0x1)			/* 与HSO约定MSG ID 从0x70000001 开始 后续ID 依次累加*/

#if( 1 == ASIC_VERSION )
#define   TDPHY_32K_TIMER_BASE_ADDR        		 (U32)(0x9000060CUL)
#else
#define TDPHY_32K_TIMER_BASE_ADDR        		 (U32)(0x5016d000UL)
#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 结构名称   : TDS_OAM_MSG_ID
 协议表格   :
 ASN.1 描述 :
 结构说明   : 定义不同模块上报消息的基址
*****************************************************************************/
enum TDS_OAM_MSG_ID
{
    TDS_OAM_ID_CTU_BASE                     =   ((TDS_OAM_MSG_BASE)),
    TDS_OAM_ID_ICS_BASE                     =   ((TDS_OAM_MSG_BASE) + (0x10000)),
    TDS_OAM_ID_IDL_BASE                     =   ((TDS_OAM_MSG_BASE) + (0x20000)),
    TDS_OAM_ID_ACC_BASE                     =   ((TDS_OAM_MSG_BASE) + (0x30000)),
    TDS_OAM_ID_DCH_BASE                     =   ((TDS_OAM_MSG_BASE) + (0x50000)),
    TDS_OAM_ID_IRAT_BASE                    =   ((TDS_OAM_MSG_BASE) + (0x60000)),
    TDS_OAM_ID_BUTT
};

/*****************************************************************************
 结构名称   : TDS_OAM_DCH_MSG_ID
 协议表格   :
 ASN.1 描述 :
 结构说明   : DCH模块下主动上报的消息ID
*****************************************************************************/
enum TDS_OAM_DCH_MSG_ID
{
    TDS_OAM_ID_DCH_DPCH_BLER_IND            = ((TDS_OAM_ID_DCH_BASE) + 0x8001),

    TDS_OAM_ID_DCH_BUTT
};

/*OM REQ枚举定义*/
typedef enum TPHY_DT_RPT_REQ
{
    TPHY_DT_UE_PCCPCH_MEAS_REQ = 0x70010001,
    TPHY_DT_UE_TS_INFO_REQ,
    TPHY_DT_UE_DPCH_INFO_REQ,
    TPHY_DT_UE_HS_SICH_INFO_REQ,
    TPHY_DT_UE_HSDPA_INFO_REQ  = 0x70010005,
    TPHY_DT_UE_TDS_OM_RPT_REQ  = 0x70900099
}TPHY_DT_RPT_REQ_ENUM;


/*OM 上报枚举定义*/
typedef enum TPHY_DT_RPT_IND
{
    TPHY_DT_UE_PCCPCH_MEAS_IND = 0x70011001,
    TPHY_DT_UE_TS_INFO_IND,
    TPHY_DT_UE_DPCH_INFO_IND,
    TPHY_DT_UE_HS_SICH_INFO_IND,
    TPHY_DT_UE_HSDPA_INFO_IND = 0x70010005,
    TPHY_DT_UE_HSDPA_HARQ_IND = 0x70100001,

}TPHY_DT_RPT_IND_ENUM;

/*OM定义公共使能开关*/
#if 0
typedef enum __OM_REQ_ENABLE__
{
    OM_REQ_DISABLE = 0,
    OM_REQ_ENABLE = 1,
}OM_REQ_ENABLE_ENUM;

typedef U16 OM_REQ_ENABLE_ENUM_UINT16;
#endif
/*	add by y00194530  begin */
typedef struct _OM_SOCP_TRACE_
{
    U16 		 UartBuff_SubFN;
    U16 		 UartBuff_STATE;
    U16 		 UartBuff_504;
    U16 		 UartBuff_MsgID;
    U16 		 UartBuffData04;
    U16 		 UartBuffData05;
    U16 		 UartBuffData06;
    U16 		 UartBuffData07;
    U16 		 UartBuffData08;
    U16 		 UartBuffData09;
    U16 		 UartBuffData10;
    U16 		 UartBuffData11;
    U16 		 UartBuffData12;
    U16 		 UartBuffData13;
    U16 		 UartBuffData14;
    U16 		 UartBuffData15;
    U16 		 UartBuffData16;
    U16 		 UartBuffData17;
    U16 		 UartBuffData18;
    U16 		 UartBuffData19;
    U16 		 UartBuffData20;
    U16 		 UartBuffData21;
    U16 		 UartBuffData22;
    U16 		 UartBuffData23;
    U16 		 UartBuffData24;
    U16 		 UartBuffData25;
    U16 		 UartBuffData26;
    U16 		 UartBuffData27;
    U16 		 UartBuffData28;
    U16 		 UartBuffData29;
    U16 		 UartBuffData30;
    U16 		 UartBuffData31;
    U16 		 UartBuffData32;
    U16 		 UartBuffData33;
    U16 		 UartBuffData34;
    U16 		 UartBuffData35;
}OM_SOCP_TRACE_STRU;

/*y00151394  Add For HSO Display Begin*/

/*64位，32K计数器*/
typedef struct tagUNSIGNED64
{
    U32 uiLow32;
    U32 uiHigh32;
}UNSIGNED64;

typedef struct
{
    U32       ulOmMsgId;
    U32       ulOmMsgLen;
    /*OM原语信息*/
    U16       ausData[8];
}TDS_OM_REQ_MSG_STRU;

/*****************************************************************************
 结构名称: TDS_OM_DPCH_BLER_INFO_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: DPCH 误码率上报
*****************************************************************************/
typedef struct
{
    U16    ausDataTypeNackNum[6];  /* 分别代表不同业务类型的误块个数。0: Signling; 2: PS Data; 2: CsA; 3: CsB; 4: CsC; 5: Cs Media*/
    U16    ausDataTypeTotalNum[6]; /* 不同业务类型TB的总个数*/
    U32    ulDpchTotalTbNack;      /* 以上6个信道NACK总和*/
    U32    ulDpchTotalTbNum;
}TDS_OM_DPCH_BLER_INFO_IND_STRU;

typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptPccpchMeasEna;
    U16 usRptPccpchMeasPeriod;   /*P-CCPCH  测量值上报周期，必须为5ms的整数倍*/
} TPHY_DT_UE_PCCPCH_MEAS_REQ_STRU;

/*物理层输出*/
typedef struct
{
    U16  usTdsSfn;       /*TDS 上报子帧号 0-8191*/
    S16  sPccpchRscp;     /*dBm*/
    S16  sPccpchSir;      /*dB*/
    U16  usRsvd;
}TPHY_DT_UE_PCCPCH_MEAS_IND_STRU;

/*路测原语输入*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptTdsTsInfoEna;
    U16 usRptTsInfoPeriod;    /*信息上报周期，必须为5ms的整数倍*/
}TPHY_DT_UE_TS_INFO_REQ_STRU;

/*物理层输出*/
typedef struct
{
    U16 usTdsSfn;             /*TDS 上报子帧号 0-8191*/
    U16 ausTsIscp[5];         /*每个时隙上的干扰信号码功率，时隙2-6，下同*/
    U16 usDpchTsBitMap;       /*DPCH时隙占用指示，占用为1，否则为0*/
    U16 ausTsDpchRscp[5];     /*每个时隙上的DPCH信道的RSCP , 时隙2-6，下同*/
    U16 ausTsDpchSir[5];      /*每个时隙上的DPCH信道的SIR*/
    U16 usPdschTsBitMap;      /*DDSCH时隙占用指示，占用为1，否则为0*/
    /*UINT16 asTsPdschRscp[5];     */ /*每个时隙上的PDSCH信道的RSCP*/
    /*UINT16 asTsPdschSir[5];      */ /*每个时隙上的PDSCH信道的SIR*/
    U16 asTsTxPower[6];       /*每时隙发送功率 */
    /*UINT16 usRsvd;*/
}TPHY_DT_UE_TS_INFO_IND_STRU;

/*路测原语输入*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptDpchInfoEna;
    U16 usRptDpchInfoPeriod;    /*信息上报周期，必须为5ms的整数倍*/
}TPHY_DT_UE_DPCH_INFO_REQ_STRU;

/*物理层输出*/
typedef struct
{
    U16 usTdsSfn;       /*TDS 上报子帧号 0-8191*/
    U16 usMidambleID;   /*专用物理信道的Midamble码配置*/
    S16  sDpchRscp;      /*专用物理信道的平均接收信号码功率*/
    S16  sTargetDpchSir; /*专用物理信道目标信干比*/
    U16 sDchSir;        /*专用信道信干比的测量值*/
    U16 usTpcDl;        /*下行传输功率控制字*/
    U16 usTpcUl;        /*上行汐输功率控制字*/
    U16 usTpcStep;      /*功率控制步长*/
    U16 usTimeTsCnt;    /*专用物理信道分配的下行时隙数*/
    U16 usTimeTsInfo[5];/*专用物理信道时隙分配*/
    U16 usSf[5];        /*专用物理信道使用的扩频因子*/
    U16 usOvsfNum[5];    /*OVSF NUM,专用物理信道分配的码道数*/
    U16 usOvsfID[5][16];    /*OVSF ID,专用物理信道分配的码道号*/
}TPHY_DT_UE_DPCH_INFO_IND_STRU;

/*路测原语输入*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptHssichInfoEna;
    U16 usRptHssichInfoPeriod;    /*信息上报周期，必须为5ms的整数倍*/
}TPHY_DT_UE_HSSICH_INFO_REQ_STRU;

/* CQI结果输出结构体*/
typedef struct
{
    U16 usCqiOutTbi;    /*TBI 上报值输出*/
    U16 usCqiOutMod;    /*调制方式上报值输出*/
}TDS_CQI_OUT_STRU;

/*物理层输出*/
typedef struct
{
    U16 usTdsSfn;      /*TDS 上报子帧号 0-8191*/
    /*UINT16 usModType;     */ /*调制方式*/
    /*UINT16 usSf;          */ /*扩频因子，SF16*/
    U16 usRsvd;
    /*UINT16 usTsFormat[6];  */ /*时隙格式，无TFCI，TPC，SS*/
    TDS_CQI_OUT_STRU stCqiData;/*CQI测量结果*/
}TPHY_DT_UE_HSSICH_INFO_IND_STRU;

/*路测原语输入*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptHsdpaInfoEna;
    U16 usRptHsdpaPeriod;    /*上报周期，必须为5ms的整数倍*/
}TPHY_DT_UE_HSDPA_INFO_REQ_STRU;

/*路测原语输入*/
typedef struct
{
    OM_REQ_ENABLE_ENUM_UINT16 enRptTdsOmflg;
    U16 usFlg;    /*上报类型0:缺省全部上报，1:只上报分类后的*/
}TPHY_DT_UE_TDS_OM_RPT_REQ_STRU;


/*物理层输出*/
typedef struct
{
    U16 usTdsSfn;         /*TDS 上报子帧号 0-8191*/
    /*UINT16 usQam16ModulRat;  */ /*16QAM调制编码方式占的调制编码方式的比例*/
    /*UINT16 usQpskModulRat;   */ /*1QPSK调制编码方式占的调制编码方式的比例*/
    /*UINT16 usHRnti;          */ /*HSPA下的无线网络临时标识*/
    U16 usHsdschAckCnt;  /*统计周期内，HS-DSCH信道上的ACK占的比率*/
    U16 usHsdschNackCnt; /*统计周期内，HS-DSCH信道上的NACK占的比率*/
    U16 usHsDschTbiTotal;     /*统计周期内，HS-DSCH信道上对应的误块率*/
    /*UINT16 usRsvd;*/
}TPHY_DT_UE_HSDPA_INFO_IND_STRU;
typedef struct
{
    U16                 usQpskCnt;
    U16                 us16Qamcnt;
    U16                 usNewTrans;
    U16                 usFistRetxIndNum;
    U16                 usSecondRetxNum;
    U16                 usThridRetxNum;
    U16                 usForthRetxNum;
    U16                 usMoreRetxNum;
    U16                 usTotalNewInd;
    U16                 usTotalNdi;
    U16                 usTotalDecodeCnt;
    U16                 usTotalCrcRight;
    U16                 usTotalCrcWrong;
    U16                 ausResv[3];
}TDS_OM_DSCH_HARQ_INFO_STRU;
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern U32 OM_Report(U32 ulMsgId, U16 * pInfo, U32 ulInfoLenOf16bit);
extern void OM_MboxMsgProc();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TDS_OM_H__ */


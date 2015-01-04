

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

#ifndef __CS_OM_DEF_H__
#define __CS_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*#include "../interface/cs_interface.h"*/
#include "csu_om_def.h"



#define CS_INVALID_UINT16  (UINT16)(65535)

#define LRRC_LPHY_MAX_CANDIDATE_CELL_NUM 32

#define CS_CL_CELL_BUFFER_SIZE     200/*小区数据缓存的空间大小*/
#define CS_CL_NUM                  6  /*列表总数*/
#define CS_CL_CELL_BUFFER_SPECIAL  (CS_CL_NUM + 1)  /*每个列表对应的基准小区和一个服务小区*/
#define CS_CL_CELL_LIST_SIZE       32 /*小区列表的最多小区数*/
#define CS_CL_ICELL_LIST_SIZE      4 /*干扰小区列表的最多小区数*/
#define CS_CL_CELL_LIFETIME_MAX    18 /*小区列表中小区最大年龄*/
#define CS_CL_ICELL_LIFETIME_MAX   9  /*干扰小区最大年龄*/
#define CS_CL_STEP2RATIO_IC_H      32
#define CS_CL_STEP2RATIO_IC        24

#define CS_BS_BAND0_NUM_MAX   LRRC_LPHY_MAX_SCAN_FREQ_NUM/*频段预处理支持的最大频段数目*/
#define CS_BS_BAND1_NUM_MAX   LRRC_LPHY_MAX_SCAN_FREQ_NUM/*频段排序支持的最大频段数目*/
#define CS_BS_BAND_NUM_MAX  2*LRRC_LPHY_MAX_SCAN_FREQ_NUM/*上面两个的最大值*/

#define CS_OFFSET_BETWEEN_CFG_AND_UPDT 3/*单位为子帧*/
/*结构体定义*/
/*//////////////////////////////////////////////////////////////////////*/
typedef struct 
{
	UINT16 usPrePtr;/*前向指针*/
	UINT16 usNxtPtr;/*后向指针*/
} CS_QLINK_STRU;

typedef struct  _CS_QUEUE_STRU
{
	CS_QLINK_STRU  *pstQlink;
	UINT16 usHptr;/*头指针索引*/
	UINT16 usTptr;/*尾指针索引*/
	UINT16 usLen;/*队列长度*/
	UINT16 usReserved;
} CS_QUEUE_STRU;

typedef struct
{
	UINT16 usAge;            /*该小区的年龄*/
	UINT16 usUpdateAge;      /*小区更新年龄*/
	UINT16 usBaseCellAge;    /*该小区作为基准小区的年龄*/
	UINT16 usOverBaseFlag;   /*超过基准小区标记，1--超过；0--不超过*/
	UINT16 usOverBaseAcc;    /*本小区连续超过基准小区计数*/
	
	UINT16 usCellID;         /*9u*/
	UINT16 usPos;            /*14u*/
	UINT16 usCP;             /*1u*/
	UINT16 usSFType;         /*1u*/
	UINT16 usStep2Ratio;     /*16u*/
	UINT16 usStep1Ratio;     /*10u*/
	INT16  sFFO;             /*16s*/
	INT32  lStep2Ang;	     /*17s*/
	UINT16 usStep2SyncPower; /*逻辑输出13u,需要DSP转换为15s*/
	UINT16 usSegOddEven;     /*检测到本小区的时候，用到的第一段天线数据段的奇偶属性*/
	UINT32 ulIto;            /*32u,帧同步位置,绝对时标*/
	UINT16 usStep2AccNum;
	INT16  sRsrp;
	INT16  sRsrq;
	UINT16 usReserved;
}CS_CL_CELL_DATA_STRU;

typedef struct  
{
	CS_QUEUE_STRU         *pstQueue;/**/
	CS_QUEUE_STRU         *pstIcQueue;/**/
	CS_CL_CELL_DATA_STRU  *pstCellData;/*指向小区信息存储空间的开始位置*/
	UINT16                usFreq;   /*该小区集合对应的频点，freelist集合无效*/
	UINT16                usAge;    /*该小区集合的年龄计数，每刷新一次，年龄清零，freelist集合无效*/
	UINT16                usUnderBaseCellAcc;/*活动列表中最强的连续未过基准小区门限累计计数*/
	UINT16                usBaseCellVld;/*本频点对应的基准小区有效表记*/
	UINT16                usBaseCellIdx;/*本频点对应的基准小区索引*/
	UINT16                usBaseCellInvalidCnt;/*该频点无基准小区计数，搜到基准小区后清0，未搜到增长*/
	CS_CL_CELL_DATA_STRU  *pstBaseCell;
} CS_CL_CELL_LIST_STRU;

#define CS_OMEGA_SIZE_MAX  32
typedef struct 
{
	CS_CL_CELL_LIST_STRU *pstClist;       /*小区列表指针*/
	UINT16 usCellNum;                     /*集合中小区数目，最大值CS_OMEGA_SIZE_MAX*/
	UINT16 usCellIdx[CS_OMEGA_SIZE_MAX];  /*小区索引号*/
} CS_OMEGA_STRU;

typedef struct 
{
	UINT16 usFreq;/*频点*/
	UINT16 usNum;/*小区个数*/
	UINT16 usCellID[8];/*小区ID*/
	UINT32 ulIto[8];/*小区位置，1/4TS精度*/
	UINT16 usCp[8];/*小区CP类型	*/
	UINT16 usIndex[8];/*小区关联的索引，代表该小区数据存储位置*/

	INT16  sRsrp[8];/*RSRP*/
	INT16  sRsrq[8];/*RSRQ*/
	UINT16 usAck;/*RSRP测量值有效标记	*/
	UINT16 usReserved;

	UINT16 usCsType;/*CS_TYPE_INITIAL_NBNC,CS_TYPE_INITIAL_BAR,CS_TYPE_INITIAL_CAND*/
	UINT16 usStep2Th;
	CS_OMEGA_STRU stCS_OmegaCurve;
	CS_OMEGA_STRU stCS_OmegaCurveN;
	CS_OMEGA_STRU stCS_OmegaN;
	CS_OMEGA_STRU stCS_OmegaBarN;
	CS_OMEGA_STRU stCS_OmegaCurveRsrp;

} CS_RSRP_REQ_ACK_STRU;
/*频段链表节点数据结构*/
typedef struct
{
	INT32   lRssi;
	UINT16  usLowBand;
	UINT16  usHighBand;
} CS_BAND_SCAN_NOD_STRU;
/*频段链表结构*/
typedef struct
{
	CS_QUEUE_STRU             *pstQueue;
	CS_BAND_SCAN_NOD_STRU     *pstBandScanNod;
} CS_BAND_SCAN_LIST_STRU;
/*和数据通道的接口，本模块通过数据通道来计算每个频点的RSSI*/
/*typedef struct*/
/*{*/
/*	INT32                    lRssiValid;//握手信号，RSSI生成后生效，CS读取后清零*/
/*	INT32                    lRssi[5];*/
/*	INT32                    lAagcGain[5];*/ /*AAGC增益*/
/*}CS_BAND_SCAN_RSSI_RESULT_STRU;*/

typedef struct
{
	INT32                    lRssiValid;/*握手信号，RSSI生成后生效，CS读取后清零*/
	INT32                    lRssi;
}CS_BAND_SCAN_RSSI_RESULT_STRU;


typedef struct
{
	UINT16                    usRssiEn;/*握手信号，RSSI生成后生效，CS读取后清零*/
	UINT16                    usFreq;
	UINT16                    usBandWidth;/*AAGC增益*/
	UINT16                    usReserved;
}CS_BAND_SCAN_RSSI_CMD_STRU;

/*原语处理模块接口*/
typedef struct
{
	/*UINT16                               usEn;*/
	UINT32                               ulMsgId;
	UINT16                               usOpId;
	UINT16                               enBandInd;
	LRRC_LPHY_BAND_SCAN_TYPE_ENUM_UINT16 usBandScanType;
	UINT16                               usLowBand;
	UINT16                               usHighBand;
	UINT16                               usFddTdd;
}CS_BAND_SCAN_REQ_STRU;

typedef struct
{
	UINT32                      ulMsgId;
	UINT16                      usOpId;
	UINT16                      enBandInd;
	UINT16                      usState;
	UINT16                      usCnt;
	UINT16                      usBsRptNum;
	UINT16                      usBandNum; /*频段个数*/
	UINT16                      usCenterFreq[CS_BS_BAND_NUM_MAX];/*频段的中心频点*/
	UINT16                      usLowFreq[CS_BS_BAND_NUM_MAX];/*频段的下频点*/
	UINT16                      usHighFreq[CS_BS_BAND_NUM_MAX];/*频段的上频点*/
	UINT16                      usFddTdd;
}CS_BAND_SCAN_CTRL_STRU;
/*//////////////////////////////////////////////////////////////////////*/

typedef struct  {
	/*RRC IDLE态服务小区列表更新参数*/
	UINT16                usDelta1Home       ;/*= 32*/
	UINT16                usDelta1Intra      ;/*= 32*/
	UINT16                usDelta1Inter      ;/*= 32*/

	UINT16                usDelta2Home       ;/*= 5*/
	UINT16                usDelta2Intra      ;/*= 0*/
	UINT16                usDelta2Inter      ;/*= 0*/

	INT16                 sEpciHomeRrcIdle   ;/*= -5*/
	INT16                 sEpciHomeRrcConn   ;/*= -5*/
	INT16                 sEpciIntraRrcIdle  ;/*= 0*/
	INT16                 sEpciIntraRrcConn  ;/*= 0*/
	INT16                 sEpciInterRrcIdle  ;/*= 0*/
	INT16                 sEpciInterRrcConn  ;/*= 0*/

	UINT16				  usNHomeRrcIdle     ;/*= 18*/
	UINT16				  usNHomeRrcConn     ;/*= 18*/
	UINT16				  usNIntraRrcIdle    ;/*= 18*/
	UINT16				  usNIntraRrcConn    ;/*= 18*/
	UINT16				  usNInterRrcIdle    ;/*= 18*/
	UINT16				  usNInterRrcConn    ;/*= 18*/

	UINT16				  usTIntra			 ;/*= 1*/
	UINT16				  usTInter			 ;/*= 1	*/
} CS_CLIST_UPDATE_PARA;


typedef struct
{
	UINT16       usNbase1;
	UINT16       usNbase2;
	UINT16       usNbase3;
	UINT16       Step2Ratio_basecell;
}CS_CL_BASECELL_PARA_STRU;

#if 0  //V9R1_CSU to be delete
typedef struct
{
	UINT16       usBaseCellVld;
	UINT16       usBaseCellInvalidCnt;	
	UINT16       usBaseCellId;
	UINT16       usBaseCellCp;
	UINT32       ulBaseCellIto;
}CS_BASE_CELL_INFO_STRU;
#endif

typedef struct
{
	UINT16 usStart;		 /*使能信号*/
	UINT16 usFreq;		 /*频点*/
	UINT16 usIntraInter; /*0--同频；1--异频*/
	UINT16 usFddTdd;	 /*0--FDD；1--TDD*/
	UINT16 usCsDuration; /*搜索时长，ms*/
	UINT16 usEmuTa; 	 /*搜索提前量，ms*/
	UINT16 usMasterMode; /*主模模式，2--2G;3--3G*/
	UINT16 usMasterState;/*主模状态，0--IDLE;1--CONN*/
	UINT16 usNewSearch;  /*主模式为连接态时有效；0--某频点的后续测量；*/
						 /*1--新发起的小区搜索*/
}CS_IRAT_SLAVE_START_PARA_STRU;


/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/
typedef enum __LPHY_REQ_MSGID_CS__
{
    LPHY_REQ_CS_RESERVED           = OM_CMD_ID(LPHY_CS_MID, OM_TYPE_REQ, 0x0),

	LPHY_REQ_CS_STEP1_FILTER_CFG,       /*Step1滤波配置:Step1阶段是否滤波，滤波器系数0、1的值，滤波系数数组最大索引Max_idx*/
    LPHY_REQ_CS_STEP1_PSS_CORR_SWITCH,  /*Step1阶段开窗配置:Step1阶段是否开窗PSSCorrSwitch，开窗长度*/
    LPHY_REQ_CS_STEP1_PARA_DISP,        /*Step1阶段的参数显示:“互相关分段个数”、“是否滤波”、“滤波器最大索引”、“是否开窗”*/

	LPHY_REQ_CS_STEP2_FFO_CFG,			/*step2阶段频偏校正配置:Step2阶段是否启用FFO校正及频偏值来源*/
	LPHY_REQ_CS_STEP2_PARA_CFG, 		/*step2阶段参数配置:Step2Mode、Step2噪声是否减小集合、通道0和1的Step2门限系数*/
	LPHY_REQ_CS_STEP2_THRESHOLD_CFG,    /*Step2门限系数可修改*/
	LPHY_REQ_CS_STEP2_IC_CFG, 			/*step2阶段干扰小区配置:Step2是否消干扰、消除干扰小区个数、Step2Ratio_IC、Step2Ratio_IC_h*/
	LPHY_REQ_CS_STEP2_CELL_NUM_PER_SYNC,/*每个Step1同步位置检测的小区数量*/
	LPHY_REQ_CS_STEP2_PARA_DISP, 		/*Step2阶段的参数显示:Step2阶段所配置的“是否FFO校正”、“计算噪声时是否减去了小集合”、“Step2Mode”、“是否消干扰”、“消除的干扰小区个数”、“干扰小区ID、同步位置、Step1Ratio、Step2Ratio”*/

	LPHY_REQ_CS_CL_DELTA_CFG,		/*参数“delta_home1、delta_home2”、“delta_intra1、delta_intra2”、“delta_inter1、delta_inter2”可修改*/
	LPHY_REQ_CS_CL_EPCI_RRCIDLE_CFG,/*参数“epsilon_home_RRCIDLE、epsilon_intra_RRCIDLE、epsilon_inter_RRCIDLE”可修改*/
	LPHY_REQ_CS_CL_N_RRCIDLE_CFG,   /*参数“N_home_RRCIDLE、N_intra_RRCIDLE、N_inter_RRCIDLE”可修改*/
	LPHY_REQ_CS_CL_EPCI_RRCCONN_CFG,/*参数“epsilon_home_RRCCONN、epsilon_intra_RRCCONN、epsilon_inter_RRCCONN”可修改*/
	LPHY_REQ_CS_CL_N_RRCCONN_CFG,   /*参数“N_home_RRCCONN、N_intra_RRCCONN、N_inter_RRCCONN”可修改*/
	LPHY_REQ_CS_CL_T_CFG,           /*参数“T_intra”、“T_inter”可修改*/
	LPHY_REQ_CS_CL_DISP,            /*同频列表、异频列表实时显示*/

	/*LPHY_REQ_BS_BAND_PREPRO_CFG,  */ /*频段RSSI预处理是否启用*/
	LPHY_REQ_BS_ALG,                /*采用RSSI排序、PSS排序、RSSI+PSS排序*/
	LPHY_REQ_BS_RSSI_PARA,          /*每个优先评估频点RSSI统计带宽、相对门限RelativeThreshole，单个频点RSSI评估时间*/
	LPHY_REQ_BS_PSS_PARA,			/*PSS排序还是顺序，没过PSS门限的频点是否进行搜索，PSS排序门限、每个频点PSS评估时间,*/
	/*LPHY_REQ_BS_PSS_DISP,			*/ /*RSSI排序算法中优先评估的频点数F、Q值、对优先评估频点排序后前32个频点及相应的功率度量值*/
	/*LPHY_REQ_BS_BAND_FIRST_DISP,  */ /*BandFirst的值*/


	LPHY_REQ_CS_STATISTIC_DISP, /*正确检测概率、虚警检测概率统计*/
	LPHY_REQ_CS_STATISTIC_PARA, /*统计参数设置*/

	LPHY_REQ_CS_HST,            /*0--非高铁模式；1--高铁模式*/
	LPHY_REQ_CS_DSP_PRINTF      /*DSP打印控制*/
}LPHY_REQ_MSGID_CS_ENUM;
/**************************************/
typedef enum
{
    FILTER = 0,
    DONT_FILTER
}OM_REQ_CS_STEP1_FILTER_ENUM;
typedef UINT16 OM_REQ_CS_STEP1_FILTER_ENUM_UINT16;

typedef struct 
{
    OM_REQ_CS_STEP1_FILTER_ENUM_UINT16 enStep1FilterEn        ;/*Step1滤波使能信号*/
    UINT16                             usMaxIdx               ;/*滤波系数数组最大索引    */
	UINT16                             aCS_Step1FilterCoef0[8];
	UINT16                             aCS_Step1FilterCoef1[8];
}LPHY_REQ_CS_STEP1_FILTER_CFG_STRU;
/**************************************/
typedef enum
{
    WIN_VALID = 0,
    WIN_INVALID
}OM_REQ_CS_STEP1_WIN_ENUM;
typedef UINT16 OM_REQ_CS_STEP1_WIN_ENUM_UINT16;

typedef struct 
{
    OM_REQ_CS_STEP1_WIN_ENUM_UINT16 enWinEn;
    UINT16                          usWinOffset;
	UINT16                          usWinLen;
	UINT16                          usReserved;
}LPHY_REQ_CS_STEP1_PSS_CORR_SWITCH_STRU;
/**************************************/
typedef struct 
{
    OM_REQ_ENABLE_ENUM_UINT16 enEna;
	UINT16                    usReserved;
}LPHY_REQ_CS_STEP1_PARA_DISP_EN_STRU;

/**************************************/
typedef enum
{
    FFO_INVALID = 0,
	FFO_VALID
}OM_REQ_CS_STEP1_FFO_EN_ENUM;
typedef UINT16 OM_REQ_CS_STEP1_FFO_EN_ENUM_UINT16;

typedef enum
{
    STEP1_RESULT = 0,
    DSP_CFG
}OM_REQ_CS_STEP1_FFO_SOURCE_ENUM;
typedef UINT16 OM_REQ_CS_STEP1_FFO_SOURCE_ENUM_UINT16;


typedef struct 
{
    OM_REQ_CS_STEP1_FFO_EN_ENUM_UINT16     enFfoEn;      /*频偏校正使能*/
    OM_REQ_CS_STEP1_FFO_SOURCE_ENUM_UINT16 usFfoAdjMod;/*频偏值来源:0--频偏值使用step1的结果;1--频偏值使用DSP配置结果*/
}LPHY_REQ_CS_STEP2_FFO_CFG_STRU;
/**************************************/
typedef struct 
{
    UINT16   usStep2Mode;/*1--表示强制为1; 0--表示不强制为1*/
    UINT16   usStep2NoiseType;/*初始非被禁非先验配1，其它配0--目前有疑问?*/
}LPHY_REQ_CS_STEP2_PARA_CFG_STRU;
/**************************************/
typedef enum
{
    INITIAL = 0,
    PERI_NGAG,
    PERI_GAG
}OM_REQ_CS_TYPE_ENUM;
typedef UINT16 OM_REQ_CS_TYPE_ENUM_UINT16;

typedef enum
{
    STEP2_MODE0 = 0,
    STEP2_MODE1
}OM_REQ_CS_STEP2MODE_ENUM;
typedef UINT16 OM_REQ_CS_STEP2MODE_ENUM_UINT16;

typedef enum
{
    NHST = 0,
    HST
}OM_REQ_CS_HST_ENUM;
typedef UINT16 OM_REQ_CS_HST_ENUM_UINT16;

typedef enum
{
    ONE_ANT = 1,
    TWO_ANTS
}OM_REQ_CS_ANT_NUM_ENUM;
typedef UINT16 OM_REQ_CS_ANT_NUM_ENUM_UINT16;

typedef enum
{
    S5MS  = 0,
	S10MS,
	S20MS,
	S30MS,
	S40MS
}OM_REQ_CS_ACC_NUM_ENUM;
typedef UINT16 OM_REQ_CS_ACC_NUM_ENUM_UINT16;

typedef struct 
{
    OM_REQ_CS_TYPE_ENUM_UINT16        enCsType;
	OM_REQ_CS_STEP2MODE_ENUM_UINT16   enCsStep2Mode;
	OM_REQ_CS_HST_ENUM_UINT16         enCsHst;
	OM_REQ_CS_ANT_NUM_ENUM_UINT16     enCsAntNum;
	OM_REQ_CS_ACC_NUM_ENUM_UINT16     enCsAccNUM;
	UINT16                            usStep2Th;		
}LPHY_REQ_CS_STEP2_THRESHOLD_CFG_STRU;
/**************************************/
typedef enum
{
    REMOVE = 0,
    DONT_REMOVE
}OM_REQ_CS_IC_REMOVE_ENUM;
typedef UINT16 OM_REQ_CS_IC_REMOVE_ENUM_UINT16;

typedef struct 
{
    OM_REQ_CS_IC_REMOVE_ENUM_UINT16 enIcRemove;
    UINT16                          usIcNum;
    UINT16                          usStep2Ratio_IC;
    UINT16                          usStep2Ratio_IC_h;	
}LPHY_REQ_CS_STEP2_IC_CFG_STRU;
/**************************************/
typedef struct 
{
    UINT16 usCellNumPerSync;/*每个step1同步位置搜索的小区个数*/
	UINT16 usReserved;
}LPHY_REQ_CS_STEP2_CELL_NUM_PER_SYNC_STRU;
/**************************************/
typedef struct 
{
    OM_REQ_ENABLE_ENUM_UINT16 enEna;
	UINT16                    usReserved;
}LPHY_REQ_CS_STEP2_PARA_DISP_EN_STRU;

/**************************************/
typedef struct _LPHY_REQ_CS_CL_DELTA_CFG_STRU_
{
	UINT16                usDelta1Home       ;/*= 32*/
	UINT16                usDelta1Intra      ;/*= 32*/
	UINT16                usDelta1Inter      ;/*= 32*/

	UINT16                usDelta2Home       ;/*= 5*/
	UINT16                usDelta2Intra      ;/*= 0*/
	UINT16                usDelta2Inter      ;/*= 0*/
} LPHY_REQ_CS_CL_DELTA_CFG_STRU; 

typedef struct
{
	INT16                 sEpciHomeRrcIdle   ;/*= -5*/
	INT16                 sEpciIntraRrcIdle  ;/*= 0*/
	INT16                 sEpciInterRrcIdle  ;/*= 0*/
	UINT16                usReserved;
} LPHY_REQ_CS_CL_EPCI_RRCIDLE_CFG_STRU;

typedef struct
{
	UINT16				  usNHomeRrcIdle     ;/*= 18*/
	UINT16				  usNIntraRrcIdle    ;/*= 18*/
	UINT16				  usNInterRrcIdle    ;/*= 18*/
	UINT16                usReserved;
} LPHY_REQ_CS_CL_N_RRCIDLE_CFG_STRU;

typedef struct
{
	INT16                 sEpciHomeRrcConn   ;/*= -5*/
	INT16                 sEpciIntraRrcConn  ;/*= 0*/
	INT16                 sEpciInterRrcConn  ;/*= 0*/
	UINT16                usReserved;
} LPHY_REQ_CS_CL_EPCI_RRCCONN_CFG_STRU;

typedef struct
{
	UINT16				  usNHomeRrcConn     ;/*= 18*/
	UINT16				  usNIntraRrcConn    ;/*= 18*/
	UINT16				  usNInterRrcConn    ;/*= 18*/
	UINT16                usReserved;
} LPHY_REQ_CS_CL_N_RRCCONN_CFG_STRU;

typedef struct 
{
	UINT16				  usTIntra			 ;/*= 1*/
	UINT16				  usTInter			 ;/*= 1	*/
} LPHY_REQ_CS_CL_T_CFG_STRU;
/*******列表显示*******************************/
typedef struct 
{
    OM_REQ_ENABLE_ENUM_UINT16 enEna;
	UINT16 usReserved;
}LPHY_REQ_CS_CL_DISP_EN_STRU;

/********统计******************************/
typedef struct 
{
    OM_REQ_ENABLE_ENUM_UINT16 enEna;
	UINT16 usReserved;
}LPHY_REQ_CS_STATISTIC_DISP_EN_STRU;

typedef struct 
{
	UINT16  usStatisticsPeri; /*统计周期，默认为1000轮搜索*/
	UINT16  usFreq;
	UINT16  usLegalCellsNum;
	UINT16  usLegalCellId[CS_CL_CELL_LIST_SIZE];
}LPHY_REQ_CS_STATISTIC_PARA_STRU;
/********扫频******************************/
typedef enum
{
    RSSI_PSS = 0,/*采用RSSI+PSS排序*/
    RSSI_RSSI =1,   /*采用RSSI排序*/
	PSS          /*采用PSS排序*/
}OM_REQ_BS_ALG_ENUM;
typedef UINT16 OM_REQ_BS_ALG_ENUM_UINT16;

typedef struct 
{
	OM_REQ_BS_ALG_ENUM_UINT16 enBsAlg;
	UINT16 usReserved;
}LPHY_REQ_BS_ALG_STRU;
/**/
typedef struct 
{
	UINT16 usRssiBandWidth;    /*每个优先评估频点RSSI统计带宽*/
	INT16  usRelativeThreshold;/*相对门限RelativeThreshole*/
	UINT16 usRssiDuration;     /*单个频点RSSI评估时间,ms*/
	UINT16 usReserved;
}LPHY_REQ_BS_RSSI_PARA_STRU;
/**/
typedef struct 
{
	UINT16 usOrderMode_PSS;     /*PSS排序还是顺序0-排序，1-顺序*/
	UINT16 usSearchSwitch;      /*没过PSS门限的频点是否进行搜索,0-不搜索，1-搜索*/
	UINT16 usStep1Threshold_PSS;/*PSS排序门限*/
	UINT16 usPssDuration;       /*每个频点PSS评估时间,ms*/
	UINT16 usPssFilter;         /*Step1Ratio滤波使能*/
	UINT16 usReserved;
}LPHY_REQ_BS_PSS_PARA_STRU;

/************************************************************
                           2. CNF数据结构定义
************************************************************/


/************************************************************
                           3. Ind数据结构定义
************************************************************/
typedef enum 
{
	LPHY_IND_CS_RESERVED         = OM_CMD_ID(LPHY_CS_MID, OM_TYPE_IND, 0x0),
	LPHY_IND_CS_STEP1_PARA_DISP,
	LPHY_IND_CS_STEP2_PARA_DISP,
	LPHY_IND_CS_SVRCELL_DISP,
	LPHY_IND_CS_CLIST0_DISP,
	LPHY_IND_CS_CLIST1_DISP,
	LPHY_IND_CS_CLIST2_DISP,
	LPHY_IND_CS_CLIST3_DISP,	
	LPHY_IND_CS_STATISTIC_DISP /*正确检测概率、虚警检测概率统计*/
}LPHY_IND_MSGID_CS_ENUM;
/**************************************/
/*LPHY_IND_CS_STATISTIC_DISP*/
typedef struct 
{
	UINT16	usPassCnt;	     /*正确检测计数*/
	UINT16	usFalseCellCnt;  /*虚警检测计数*/
	UINT16	usStatisticsPeri;/*统计周期，没usStatisticsPeri次上报后更新统计结果*/
	UINT16  usReserved;
}LPHY_IND_CS_STATISTIC_DISP_STRU;
/*LPHY_IND_CS_STEP1_PARA_DISP*/
typedef struct 
{
	UINT16					  usCorrNum;	   /*互相关分段个数*/
	UINT16					  usStep1FilterEna;/*是否滤波*/
	UINT16					  usMaxIdx; 	   /*滤波器最大索引*/
	UINT16					  usPssCorrSwitch; /*是否开窗*/
}LPHY_IND_CS_STEP1_PARA_DISP_STRU;
/**************************************/
/*LPHY_IND_CS_STEP2_PARA_DISP*/
typedef struct 
{
	UINT16  usFfoEn;            /*是否FFO校正*/
	UINT16  usStep2NoiseType;   /*计算噪声时是否减去了小集合*/
	UINT16  usStep2Mode;        /*Step2Mode*/
	UINT16  usIcRemove;         /*是否消干扰*/
	UINT16  usIcNum;            /*消除的干扰小区个数*/
	UINT16  usIcID[4];          /*干扰小区ID*/
	UINT16  usIcStep1Ratio[4];  /*干扰小区Step1Ratio*/
	UINT16  usIcStep2Ratio[4];  /*干扰小区Step2Ratio*/
	UINT32  ulIcPos[4];         /*干扰小区同步位置,0.25TS*/
}LPHY_IND_CS_STEP2_PARA_DISP_STRU;
/**************************************/
/*LPHY_IND_CS_CLIST0_DISP*/
/*LPHY_IND_CS_CLIST1_DISP*/
/*LPHY_IND_CS_CLIST2_DISP*/
/*LPHY_IND_CS_CLIST3_DISP*/
typedef struct 
{
	UINT16               usFreq;   /*该小区集合对应的频点，freelist集合无效*/
	UINT16               usAge;    /*该小区集合的年龄计数，每刷新一次，年龄清零，freelist集合无效*/
	UINT16               usUnderBaseCellAcc;/*活动列表中最强的连续未过基准小区门限累计计数*/
	UINT16               usBaseCellVld;/*本频点对应的基准小区有效表记*/
	UINT16               usBaseCellInvalidCnt;/*该频点无基准小区计数，搜到基准小区后清0，未搜到增长*/
	UINT16               usCellsNum;/*下面的小区数组中有效小区的数目*/
	CS_CL_CELL_DATA_STRU stBaseCell;/*本频点对应的基准小区*/
	CS_CL_CELL_DATA_STRU stCellData[CS_CL_CELL_LIST_SIZE];/*小区数据数组*/
}LPHY_IND_CS_CL_DISP_STRU;
/**************************************/
/*LPHY_IND_CS_SVRCELL_DISP*/
typedef struct 
{
	UINT16               SvrCellVld;
	UINT16               SvrCellFreq;
	CS_CL_CELL_DATA_STRU SvrCell;
}LPHY_IND_CS_SVRCELL_DISP_STRU;
/**************************************/
/*typedef struct 
{
	LPHY_IND_CS_SVRCELL_DISP_STRU stSvrCell;
	LPHY_IND_CS_CL_DISP_STRU      stClist0;
	LPHY_IND_CS_CL_DISP_STRU      stClist1;
	LPHY_IND_CS_CL_DISP_STRU      stClist2;
	LPHY_IND_CS_CL_DISP_STRU      stClist3;
}LPHY_IND_CS_CELL_LISTS_DISP_STRU;*/

/************************************************************
                           4. SG 数据结构定义, 算法需要绘图的
************************************************************/


/************************************************************
                           5. TRACE数据结构定义
************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CS_OM_DEF_H__ */


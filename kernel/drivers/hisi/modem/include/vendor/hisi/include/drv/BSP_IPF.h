/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_IPF.h
*
*
*   描    述 :  IPF模块用户接口文件
*
*   修改记录 :  2011年01月21日  v1.00  luting  创建
*************************************************************************/

#ifndef    _BSP_IPF_H_
#define    _BSP_IPF_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  头文件包含
**************************************************************************/
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#include "DrvInterface.h"
#include "TtfDrvInterface.h"
#include "product_config.h"
#else
#include "DrvInterface.h"
#include "product_config.h"
#endif
/**************************************************************************
  宏定义
**************************************************************************/

/*************************IPF BEGIN************************/
/**************************************************************************
  宏定义
**************************************************************************/
/*错误码定义*/
#define IPF_SUCCESS                         BSP_OK
#define IPF_ERROR                           BSP_ERROR
#define BSP_ERR_IPF_INVALID_PARA            BSP_DEF_ERR(BSP_MODU_IPF, 0)
#define BSP_ERR_IPF_BDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 1)
#define BSP_ERR_IPF_CDQ_NOT_ENOUGH          BSP_DEF_ERR(BSP_MODU_IPF, 2)
#define BSP_ERR_IPF_RDQ_EMPTY               BSP_DEF_ERR(BSP_MODU_IPF, 3)
#define BSP_ERR_IPF_FILTER_NOT_ENOUGH       BSP_DEF_ERR(BSP_MODU_IPF, 4)
#define BSP_ERR_IPF_NOT_INIT                BSP_DEF_ERR(BSP_MODU_IPF, 5)
#define BSP_ERR_IPF_RESUME_TIMEOUT          BSP_DEF_ERR(BSP_MODU_IPF, 6)
#define BSP_ERR_IPF_SEMTAKE_TIMEOUT         BSP_DEF_ERR(BSP_MODU_IPF, 7)
#define BSP_ERR_IPF_ADQ0_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 8)
#define BSP_ERR_IPF_ADQ1_NOT_ENOUGH         BSP_DEF_ERR(BSP_MODU_IPF, 9)
#define BSP_ERR_IPF_ALLOC_MEM_FAIL          BSP_DEF_ERR(BSP_MODU_IPF, 10)
/*Modify_for_c_reset, l00212112,20130511, starts*/
#define BSP_ERR_IPF_CCORE_RESETTING         BSP_DEF_ERR(BSP_MODU_IPF, 11)
#define BSP_ERR_IPF_INVALID_DLRD            BSP_DEF_ERR(BSP_MODU_IPF, 12)
#define BSP_ERR_IPF_INVALID_ULRD            BSP_DEF_ERR(BSP_MODU_IPF, 13)
/*Modify_for_c_reset, l00212112,20130511, ends*/


#define IPF_ULBD_DESC_SIZE         64   /* 上行BD个数 */
#define IPF_ULRD_DESC_SIZE         64   /* 上行BD个数 */
#define IPF_DLBD_DESC_SIZE         64   /* 下行BD个数 */
#define IPF_DLRD_DESC_SIZE         64   /* 下行BD个数 */
#define IPF_ULAD0_DESC_SIZE        64   /* 上行ADQ0中AD个数 */
#define IPF_ULAD1_DESC_SIZE        64   /* 上行ADQ1中AD个数 */
#define IPF_DLAD0_DESC_SIZE        64   /* 下行ADQ0中AD个数 */
#define IPF_DLAD1_DESC_SIZE        64   /* 下行ADQ1中AD个数 */
#define IPF_DLCD_DESC_SIZE         1024 //上海需求
#define IPF_FILTER_CHAIN_MAX_NUM   8    /* IPF过滤器链最大个数 */
/**************************************************************************
  枚举定义
**************************************************************************/
/*ADQ使能枚举值*/
typedef enum tagIPF_ADQEN_E
{
    IPF_NONE_ADQ_EN = 0,    /*不使用ADQ*/
    IPF_ONLY_ADQ0_EN = 1,   /*仅使用ADQ0*/
    IPF_ONLY_ADQ1_EN = 2,   /*仅使用ADQ1*/
    IPF_BOTH_ADQ_EN = 3,    /*使用ADQ0和ADQ1*/

    IPF_ADQEN_BUTT          /*边界值*/
}IPF_ADQEN_E;

/*ADSize*/
typedef enum tagIPF_ADSIZE_E
{
    IPF_ADSIZE_32 = 0,  /* AD队列大小为32 */
    IPF_ADSIZE_64,      /* AD队列大小为64 */
    IPF_ADSIZE_128,     /* AD队列大小为128 */
    IPF_ADSIZE_256,     /* AD队列大小为256*/
}IPF_ADSIZE_E;

/* 过滤模式 */
typedef enum tagIPF_MODE_E
{
    IPF_MODE_FILTERANDTRANS = 0,   /* 过滤并搬移 */
    IPF_MODE_FILTERONLY,           /* 只过滤 */
    IPF_MODE_TRANSONLY, /*只搬移*/
    IPF_MODE_MAX                    /* 边界值 */
}IPF_MODE_E;

/* BURST最大长度 */
typedef enum tagIPF_BURST_E
{
    IPF_BURST_16 = 0,           /* BURST16 */
    IPF_BURST_8,                /* BURST8 */
    IPF_BURST_4,                /* BURST4 */
    IPF_BURST_MAX                /* BURST4 跟寄存器一致 */
}IPF_BURST_E;

/*ADQ空标志枚举值*/
typedef enum tagIPF_ADQ_EMPTY_E
{
    IPF_EMPTY_ADQ0 = 0x1,                               /*短包队列ADQ0空*/
    IPF_EMPTY_ADQ1 = 0x2,                               /*长包队列ADQ1空*/
    IPF_EMPTY_ADQ = (IPF_EMPTY_ADQ0+IPF_EMPTY_ADQ1),    /*两个队列都空*/
    IPF_EMPTY_MAX                                       /*边界值*/
}IPF_ADQ_EMPTY_E;

typedef enum tagIPF_AD_TYPE_E
{
    IPF_AD_0 = 0,       /*标识ADQ0*/
    IPF_AD_1,           /*标识ADQ1*/

    IPF_AD_MAX         /*边界值*/
}IPF_AD_TYPE_E;
/* IPF状态标识 */
typedef enum tagIPF_RESTORE_STATE_E
{
    IPF_STATE_UNRESTORE = 0,   /* 未恢复 */
    IPF_STATE_RESTORING,       /* 恢复中 */
    IPF_STATE_RESTORED,        /* 已恢复 */

    IPF_STATE_MAX
}IPF_RESTORE_STATE_E;

/* IP类型 */
typedef enum tagIPF_IP_TYPE_E
{
    IPF_IPTYPE_V4 = 0,        /* IPV4 */
    IPF_IPTYPE_V6,            /* IPV6 */
    IPF_IPTYPE_MAX           /* 边界值 */
}IPF_IP_TYPE_E;

/* 通道类型 */
typedef enum tagIPF_CHANNEL_TYPE_E
{
    IPF_CHANNEL_UP  = 0,        /* 上行通道 */
    IPF_CHANNEL_DOWN,         /* 下行通道 */
    IPF_CHANNEL_MAX           /* 边界值 */
}IPF_CHANNEL_TYPE_E;

typedef enum tagIPF_FILTER_CHAIN_TYPE_E
{
    IPF_MODEM0_ULFC = 0,
    IPF_MODEM1_ULFC,
    IPF_MODEM0_DLFC,
    IPF_MODEM1_DLFC,
    IPF_MODEM_MAX = 8
}IPF_FILTER_CHAIN_TYPE_E;

/*Modify_for_c_reset, l00212112,20130511, starts*/
/*改变量用于C核复位时，控制IPF上行*/
typedef enum tagIPF_FORRESET_CONTROL_E
{
    IPF_FORRESET_CONTROL_ALLOW,     /*允许发送*/
    IPF_FORRESET_CONTROL_FORBID,    /*禁止发送*/
    IPF_FORRESET_CONTROL_MAX
}IPF_FORRESET_CONTROL_E;
/*Modify_for_c_reset, l00212112,20130511, ends*/

/* 打印级别定义 */
typedef enum tagIPF_LOG_LEVEL_E
{
    IPF_LOG_DEBUG   = 0,    /* 0x0:debug-level                                  */
    IPF_LOG_INFO    = 1,    /* 0x1:informational                                */
    IPF_LOG_WARNING = 3,    /* 0x3:warning conditions                           */
    IPF_LOG_ERROR,          /* 0x4:error conditions                             */
    IPF_LOG_MAX             /* 边界值 */
} IPF_LOG_LEVEL_E;

/**************************************************************************
  STRUCT定义
**************************************************************************/

/* BD描述符 */
typedef struct tagIPF_BD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32InPtr;
    BSP_U32 u32OutPtr;
    BSP_U16 u16Resv;
    BSP_U16 u16UsrField1;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
} IPF_BD_DESC_S;

/* RD描述符 */
typedef struct tagIPF_RD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32InPtr;
    BSP_U32 u32OutPtr;
    BSP_U16 u16Result;
    BSP_U16 u16UsrField1;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
} IPF_RD_DESC_S;

/* AD描述符 */
typedef struct tagIPF_AD_DESC_S
{
    BSP_U32 u32OutPtr0;
    BSP_U32 u32OutPtr1;
}IPF_AD_DESC_S;

/* CD描述符 */
typedef struct tagIPF_CD_DESC_S
{
    BSP_U16 u16Attribute;
    BSP_U16 u16PktLen;
    BSP_U32 u32Ptr;
}IPF_CD_DESC_S;

/* 通道控制结构体 */
typedef struct tagIPF_CHL_CTRL_S
{
    BSP_BOOL bDataChain;          /* 数据是否为链表 */
    BSP_BOOL bEndian;             /* 大小端指示 */
    IPF_MODE_E eIpfMode;          /* 模式控制 */
    BSP_U32 u32WrrValue;           /* WRR值 */
} IPF_CHL_CTRL_S;

typedef struct tagIPF_CONFIG_ULPARAM_S
{
#if (FEATURE_IPF_VERSION == IPF_V200)
    BSP_U16 u16Len;         /* 上行数据源长度 */
    BSP_U16 u16Attribute;
    BSP_U32 u32Data;        /* 上行数据源地址 */
    BSP_U16 u16UsrField1;   /* Usr field 域1 ,透传 */
    BSP_U16 u16Reserved;
    BSP_U32 u32UsrField2;   /* Usr field 域2 ,透传 */
    BSP_U32 u32UsrField3;   /* Usr field 域3 ,透传*/
#elif (FEATURE_IPF_VERSION == IPF_V300)
    BSP_U32 u32Data;        /* 上行数据源地址 */
    BSP_U32 u32DesAddr;     /* 上行数据目的地址 ,只针对IP搬移 */
    BSP_U16 u16Len;         /* 上行数据源长度 */
    BSP_U16 u16UsrField1;   /* Usr field 域1 ,透传 */
    BSP_U32 u32UsrField2;   /* Usr field 域2 ,透传 */
    BSP_U32 u32UsrField3;   /* Usr field 域3 ,透传*/
#endif
}IPF_CONFIG_ULPARAM_S;
/* 统计计数信息结构体 */
typedef struct tagIPF_FILTER_STAT_S
{
    BSP_U32 u32UlCnt0;
    BSP_U32 u32UlCnt1;
    BSP_U32 u32UlCnt2;
    BSP_U32 u32DlCnt0;
    BSP_U32 u32DlCnt1;
    BSP_U32 u32DlCnt2;
}IPF_FILTER_STAT_S;

BSP_S32 BSP_IPF_ConfigTimeout(BSP_U32 u32Timeout);
#if (FEATURE_IPF_VERSION == IPF_V200)
BSP_S32 BSP_IPF_ConfigUpFilter(BSP_U32 u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara);
#elif (FEATURE_IPF_VERSION == IPF_V300)
BSP_S32 BSP_IPF_ConfigUpFilter(BSP_U32 u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara, BSP_BOOL bintFlag);
#endif
#if (FEATURE_IPF_VERSION == IPF_V200)
BSP_U32 BSP_IPF_GetUlDescNum(BSP_VOID);
#endif
BSP_U32 BSP_IPF_GetUlBDNum(BSP_VOID);
BSP_S32 BSP_IPF_UlStateIdle(BSP_VOID);
BSP_S32 BSP_IPF_SetPktLen(BSP_U32 u32MaxLen, BSP_U32 u32MinLen);
BSP_S32 BSP_IPF_GetStat(IPF_FILTER_STAT_S *pstFilterStat);
typedef BSP_S32 (*BSP_IPF_WakeupUlCb)(BSP_VOID);
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
    /* 公共参数结构体 */
    typedef struct tagIPF_COMMON_PARA_S
    {
#if (FEATURE_IPF_VERSION == IPF_V200)
        BSP_BOOL bAdReport;    /*上、下行通道AD上报选择*/
        BSP_BOOL bMultiModeEn;     /*单通道动态业务模式使能*/
        BSP_BOOL bMultiFilterChainEn;    /*单通道多过滤器链使能*/
#endif
        BSP_BOOL bEspSpiDisable;     /* ESP SPI是否参与匹配控制信号 */
        BSP_BOOL bAhSpiDisable;      /* AH SPI是否参与匹配控制信号 */
        BSP_BOOL bEspAhSel;          /* 0选ESP，1选AH */
        BSP_BOOL bIpv6NextHdSel;    /*IPV6 Next Header选择。*/
        IPF_BURST_E eMaxBurst;       /* BURST最大长度 */
        BSP_BOOL bSpWrrModeSel;     /*SP和WRR模式调度选择*/
        BSP_BOOL bSpPriSel;          /* SP优先级选择 */
        BSP_BOOL bFltAddrReverse;  /* 扩滤器中地址寄存器大小端排列顺序 0表示大端 */
        BSP_BOOL bFilterSeq;        /* 过滤器配置顺序指示 */
    } IPF_COMMON_PARA_S;

    /* 匹配项信息 */
    typedef struct tagIPF_MATCH_INFO_S
    {
        BSP_U8 u8SrcAddr[16];
#if (FEATURE_IPF_VERSION == IPF_V300)
        BSP_U8 u8SrcMsk[16];
#endif
        BSP_U8 u8DstAddr[16];
        BSP_U8 u8DstMsk[16];
        union
        {
            struct
            {
                BSP_U32 u16SrcPortLo:16;
                BSP_U32 u16SrcPortHi:16;
            }Bits;
            BSP_U32 u32SrcPort;
        } unSrcPort;
        union
        {
            struct
            {
                BSP_U32 u16DstPortLo:16;
                BSP_U32 u16DstPortHi:16;
            }Bits;
            BSP_U32 u32DstPort;
        } unDstPort;
#if (FEATURE_IPF_VERSION == IPF_V200)
        union
        {
            struct
            {
                BSP_U8 u8TrafficClass:8;
                BSP_U8 u8TrafficClassMask:8;
                BSP_U16 u16Reserve:16;
            }Bits;
            BSP_U32 u32TrafficClass;
        }unTrafficClass;
        BSP_U32 u32LocalAddressMsk;
#elif (FEATURE_IPF_VERSION == IPF_V300)
		union
		{
			BSP_U32 u32TrafficClass;
			BSP_U32 u32ServiceType;
		}unTrafficClass;
		union
		{
			BSP_U32 u32TrafficClassMsk;
			BSP_U32 u32ServiceTypeMsk;
		} unTrafficClassMsk;
#endif
        union
        {
            BSP_U32 u32NextHeader;
            BSP_U32 u32Protocol;
        }unNextHeader;
        BSP_U32 u32FlowLable;
        union
        {
            struct
            {
                BSP_U32 u16Type:16;
                BSP_U32 u16Code:16;
            }Bits;
            BSP_U32 u32CodeType;
        } unFltCodeType;
        union
        {
            struct
            {
                BSP_U32 u16NextIndex:16;
                BSP_U32 u16FltPri:16;
            }Bits;
            BSP_U32 u32FltChain;
        } unFltChain;
        BSP_U32 u32FltSpi;
        union
        {
            struct
            {
                BSP_U32 FltEn:1;
                BSP_U32 FltType:1;
                BSP_U32 Resv1:2;
                BSP_U32 FltSpiEn:1;
                BSP_U32 FltCodeEn:1;
                BSP_U32 FltTypeEn:1;
                BSP_U32 FltFlEn:1;
                BSP_U32 FltNhEn:1;
                BSP_U32 FltTosEn:1;
                BSP_U32 FltRPortEn:1;
                BSP_U32 FltLPortEn:1;
                BSP_U32 FltRAddrEn:1;
                BSP_U32 FltLAddrEn:1;
                BSP_U32 Resv2:2;
                BSP_U32 FltBid:6;
                BSP_U32 Resv3:10;
            }Bits;
            BSP_U32 u32FltRuleCtrl;
        }unFltRuleCtrl;
    }IPF_MATCH_INFO_S;

/* Filter配置信息结构体 */
typedef struct tagIPF_FILTER_CONFIG_S
{
    BSP_U32 u32FilterID;            /* 低16位表示PS ID;高16位表示PS使用滤波器类型，基本还是扩展 */
    IPF_MATCH_INFO_S stMatchInfo;   /* 过滤器对应的信息 */
} IPF_FILTER_CONFIG_S;

#if (FEATURE_IPF_VERSION == IPF_V200)
typedef struct tagIPF_CONFIG_DLPARAM_S
{
    BSP_U16 u16Len;
    BSP_U16 u16Attribute;
    BSP_U32 u32Data;
    BSP_U16 u16UsrField1;
    BSP_U16 u16Reserved;
    BSP_U32 u32UsrField2;
    BSP_U32 u32UsrField3;
}IPF_CONFIG_DLPARAM_S;
#elif (FEATURE_IPF_VERSION == IPF_V300)
    typedef struct tagIPF_CONFIG_DLPARAM_S
	{
		TTF_MEM_ST* pstSrcTtf;
		TTF_MEM_ST* pstDstTtf;
		BSP_U16 u16UsrField; /* 2Byte透传 */
	}IPF_CONFIG_DLPARAM_S;
#endif

typedef BSP_S32 (*BSP_IPF_DlFreeMemCb)(BSP_U32 u32Num, TTF_MEM_ST** pstMem);
BSP_S32 BSP_IPF_Init(IPF_COMMON_PARA_S *pstCommPara);
BSP_S32 BSP_IPF_ConfigUlChannel(IPF_CHL_CTRL_S *pstCtrl);
BSP_S32 BSP_IPF_ConfigDlChannel(IPF_CHL_CTRL_S *pstCtrl);
#if (FEATURE_IPF_VERSION == IPF_V200)
BSP_S32 BSP_IPF_SetFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, IPF_FILTER_CONFIG_S *pstFilterInfo, BSP_U32 u32FilterNum);
BSP_S32 BSP_IPF_GetFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, BSP_U32 u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo);
BSP_S32 BSP_IPF_ConfigDownFilter(BSP_U32 u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara);
#elif (FEATURE_IPF_VERSION == IPF_V300)
BSP_S32 BSP_IPF_SetFilter(IPF_CHANNEL_TYPE_E eChnType, IPF_FILTER_CONFIG_S *pstFilterInfo, BSP_U32 u32FilterNum);
BSP_S32 BSP_IPF_GetFilter(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo);
BSP_S32 BSP_IPF_ConfigDownFilter(BSP_U32 u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara, BSP_BOOL bintFlag);
#endif
BSP_S32 BSP_IPF_ChannelEnable(IPF_CHANNEL_TYPE_E eChanType, BSP_BOOL bFlag);
#if (FEATURE_IPF_VERSION == IPF_V200)
BSP_U32 BSP_IPF_GetDlDescNum(BSP_VOID);
#endif
BSP_U32 BSP_IPF_GetDlBDNum(BSP_U32* pu32CDNum);
BSP_S32 BSP_IPF_DlStateIdle(BSP_VOID);
BSP_VOID BSP_IPF_ReleaseDlSrcMem (BSP_VOID);
BSP_VOID BSP_IPF_RegisterDlFreeMemCb(BSP_IPF_DlFreeMemCb pFnDlFreeMem);
BSP_S32 BSP_IPF_RegisterWakeupUlCb(BSP_IPF_WakeupUlCb pFnWakeupUl);
BSP_VOID BSP_IPF_GetUlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd);
#if (FEATURE_IPF_VERSION == IPF_V200)
typedef BSP_S32 (*BSP_IPF_AdqEmptyUlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);
BSP_S32 BSP_IPF_GetUlAdNum(BSP_U32* pu32AD0Num, BSP_U32* pu32AD1Num);
BSP_S32 BSP_IPF_ConfigUlAd(IPF_AD_TYPE_E eAdType, BSP_U32 u32AdNum, IPF_AD_DESC_S *pstAdDesc);
BSP_S32 BSP_IPF_RegisterAdqEmptyUlCb(BSP_IPF_AdqEmptyUlCb pAdqEmptyUl);
BSP_S32 BSP_IPF_ConfigADThr(BSP_U32 u32UlADThr,BSP_U32 u32DlADThr);
#endif
#else
typedef BSP_S32 (*BSP_IPF_WakeupDlCb)(BSP_VOID);
BSP_S32 BSP_IPF_RegisterWakeupDlCb(BSP_IPF_WakeupDlCb pFnWakeupDl);
BSP_VOID BSP_IPF_GetDlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd);
BSP_U32 BSP_IPF_GetUlRdNum(BSP_VOID);
BSP_U32 BSP_IPF_GetDlRdNum(BSP_VOID);
#if (FEATURE_IPF_VERSION == IPF_V200)
typedef BSP_S32 (*BSP_IPF_AdqEmptyDlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);
BSP_S32 BSP_IPF_GetDlAdNum(BSP_U32* pu32AD0Num, BSP_U32* pu32AD1Num);
BSP_S32 BSP_IPF_ConfigDlAd(IPF_AD_TYPE_E eAdType, BSP_U32 u32AdNum, IPF_AD_DESC_S *pstAdDesc);
BSP_S32 BSP_IPF_RegisterAdqEmptyDlCb(BSP_IPF_AdqEmptyDlCb pAdqEmptyDl);
BSP_S32 BSP_IPF_GetUsedDlAd(IPF_AD_TYPE_E eAdType, BSP_U32 *pu32AdNum, IPF_AD_DESC_S *pstAdDesc);
BSP_VOID BSP_IPF_DlRegReInit(BSP_VOID);
#endif
#endif
/*Modify_for_c_reset, l00212112,20130511, starts*/
extern BSP_VOID BSP_IPF_SetControlFLagForCcoreReset(IPF_FORRESET_CONTROL_E flagvalue);
/*Modify_for_c_reset, l00212112,20130511, ends*/

/*************************IPF END************************/

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif    /* End #define _BSP_IPF_H_ */



/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : LMacPhyInterface.h
  版 本 号   : 初稿
  生成日期   : 2009年2月03日
  最近修改   :
  功能描述   : MAC与PHY数据交互结构定义
  函数列表   :
  修改历史   :
  1.日    期   : 2009年2月03日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __LMACLPHYINTERFACE_H__
#define __LMACLPHYINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#ifndef LPS_RTT
#include "vos.h"
#endif
#include "memmap_base.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#ifdef LPS_RTT
#define VOS_WIN32   (1)
#define VOS_OS_VER  (3)
#endif

#define LMAC_FEATURE_OFF        (0)
#define LMAC_FEATURE_ON         (1)
#define FEATURE_LMAC_LPHY_R10_CR     LMAC_FEATURE_OFF

/*该宏打开时是V7R1的第二个版本(2011年12月之后的版本)，即合入MBMS的Pilot版本*/
/*#ifdef PRODUCT_CFG_BOARD_TYPE_HI6920CS_P500 */

/*PS已经将该宏删除，为了保持接口一致性，当前只在接口文件中定义,后续将该宏删除*/
#define LTE_UECAP5_MBMS_VERSION


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define ULLMAC_LPHY_MSG_HDR                (0x000009c0)
#define LPHY_ULLMAC_MSG_HDR                (0x00000a00)

#define DLLMAC_LPHY_MSG_HDR                (0x00000a40)
#define LPHY_DLLMAC_MSG_HDR                (0x00000a80)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*****************************************************************************
 结构名    : LMAC_LPHY_MSG_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC和PHY间的接口消息
*****************************************************************************/
enum LMAC_LPHY_MSG_TYPE_ENUM
{
    ID_LMAC_LPHY_ACCESS_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_REQ_STRU */   /* MAC向PHY进行随机接入发起的配置信息消息ID */
    ID_LMAC_LPHY_ACCESS_CNF               = (LPHY_ULLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_ACCESS_CNF_STRU */   /* MAC向PHY进行随机接入发起的配置信息确认消息ID */

    ID_LMAC_LPHY_SR_DATA_REQ              = (ULLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_REQ_STRU */ /* MAC发起调度请求的消息ID */
    ID_LMAC_LPHY_SR_DATA_CNF              = (LPHY_ULLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_SR_DATA_CNF_STRU */   /* MAC发起调度请求的确认消息ID */

    ID_LMAC_LPHY_UL_GRANT_HARQ_IND        = (LPHY_ULLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_UL_GRANT_HARQ_IND_STRU */   /* MAC接收上行授权和上行反馈信息的指示消息ID */
    ID_LMAC_LPHY_PDCCH_ORDER_IND          = (LPHY_ULLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_IND_STRU */   /* MAC接收PDCCH OReder的非竞争解决专用Preamble的消息ID */
    ID_LMAC_LPHY_PDCCH_ORDER_SUCC_IND     = (LPHY_ULLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU */   /* MAC接收PDCCH OReder的竞争解决 成功*/
    ID_LMAC_LPHY_RAR_TIMEOUT_IND          = (LPHY_ULLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_TIMEOUT_IND_STRU */   /* PHY接收RAR超时统计指示消息*/

    ID_LMAC_LPHY_RA_ACK_REQ               = (ULLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_RA_ACK_REQ_STRU */   /* MAC指示PHY关于竞争解决的ACK的消息ID */

    ID_LMAC_LPHY_SPS_RELEASE_REQ          = (ULLMAC_LPHY_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_REQ_STRU */   /* MAC指示PHY释放半静态调度授权信息的消息ID */
    ID_LMAC_LPHY_SPS_RELEASE_CNF          = (LPHY_ULLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_SPS_RELEASE_CNF_STRU */   /* MAC指示PHY释放半静态调度授权信息确认的消息ID */

    ID_LMAC_LPHY_RAR_CONFIG_REQ           = (ULLMAC_LPHY_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_REQ_STRU */   /* MAC向PHY进行随机接入响应的配置信息消息ID */
    ID_LMAC_LPHY_RAR_CONFIG_CNF           = (LPHY_ULLMAC_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_RAR_CONFIG_CNF_STRU */   /* MAC向PHY进行随机接入响应的配置信息确认消息ID */

    ID_LMAC_LPHY_CRNTI_CONFIG_REQ         = (ULLMAC_LPHY_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_REQ_STRU */   /* MAC配置C-RNTI值的消息ID */
    ID_LMAC_LPHY_CRNTI_CONFIG_CNF         = (LPHY_ULLMAC_MSG_HDR + 0x08),       /* _H2ASN_MsgChoice LMAC_LPHY_CRNTI_CONFIG_CNF_STRU */   /* MAC配置C-RNTI值确认消息ID */

    ID_LMAC_LPHY_TA_TIMER_REQ             = (ULLMAC_LPHY_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_REQ_STRU */   /* MAC指示PHY关于TA Timer是否超时或运行的消息ID */
    ID_LMAC_LPHY_TA_TIMER_CNF             = (LPHY_ULLMAC_MSG_HDR + 0x09),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_TIMER_CNF_STRU */   /* MAC指示PHY关于TA Timer是否超时或运行消息确认的消息ID */

    ID_LMAC_LPHY_DATA_REQ                 = (ULLMAC_LPHY_MSG_HDR + 0x07),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_REQ_STRU */   /* MAC向PHY发送的PUSCH数据的消息ID */

    ID_LMAC_LPHY_TA_REQ                   = (DLLMAC_LPHY_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_REQ_STRU */   /* MAC配置TA值的消息ID */
    ID_LMAC_LPHY_TA_CNF                   = (LPHY_DLLMAC_MSG_HDR + 0x00),       /* _H2ASN_MsgChoice LMAC_LPHY_TA_CNF_STRU */   /* MAC配置TA值确认消息ID */

    ID_LMAC_LPHY_CONNECTED_DRX_REQ        = (DLLMAC_LPHY_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_REQ_STRU */   /* MAC指示PHY连接态下的DRX的消息ID */
    ID_LMAC_LPHY_CONNECTED_DRX_CNF        = (LPHY_DLLMAC_MSG_HDR + 0x01),       /* _H2ASN_MsgChoice LMAC_LPHY_CONNECTED_DRX_CNF_STRU */   /* MAC指示PHY连接态下的DRX的确认消息ID*/

    ID_LMAC_LPHY_MTCH_STOP_REQ            = (DLLMAC_LPHY_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_MTCH_STOP_REQ_STRU */   /* MAC指示PHY停止对应PMCH的消息ID */

    ID_LMAC_LPHY_DATA_IND                 = (LPHY_DLLMAC_MSG_HDR + 0x02),       /* _H2ASN_MsgChoice LMAC_LPHY_DATA_IND_STRU */   /* MAC接收PHY发送的PDSCH数据的消息ID */
    ID_LMAC_LPHY_BCCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x03),       /* _H2ASN_MsgChoice LMAC_LPHY_BCCH_DATA_IND_STRU */   /* MAC接收PHY发送的SIB广播数据的消息ID */
    ID_LMAC_LPHY_PCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x04),       /* _H2ASN_MsgChoice LMAC_LPHY_PCH_DATA_IND_STRU */   /* MAC接收PHY发送的寻呼数据的消息ID  */
    ID_LMAC_LPHY_PBCH_DATA_IND            = (LPHY_DLLMAC_MSG_HDR + 0x05),       /* _H2ASN_MsgChoice LMAC_LPHY_PBCH_IND_STRU */   /* MAC接收PHY发送的MIB广播数据的消息ID */
    ID_LMAC_LPHY_MCH_DATA_IND             = (LPHY_DLLMAC_MSG_HDR + 0x06),       /* _H2ASN_MsgChoice LMAC_LPHY_MCH_DATA_IND_STRU */   /* MAC接收PHY发送的MIB广播数据的消息ID */

    ID_LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND  = (LPHY_ULLMAC_MSG_HDR + 0x0a),       /* _H2ASN_MsgChoice LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU */   /* DSP通知MAC关于PDCCH指示的上行半静态释放*/

    ID_LMAC_LPHY_MSG_TYPE_END
};
typedef         VOS_UINT32          LMAC_LPHY_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 结构名    : LTE_ACESS_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC和PHY间的随机接入类型
*****************************************************************************/
enum LTE_ACESS_TYPE_ENUM
{
    LTE_ACCESS_CONN_OR_REEST_REQ        = 0x00,                                 /*初始建立或重建竞争接入*/
    LTE_ACCESS_CONTENT_MAC_REQ          = 0x01,                                 /*MAC触发连接态竞争接入*/
    LTE_ACCESS_CONTENT_PDCCH_ORDER_REQ  = 0x02,                                 /*PDCCH Order触发连接态竞争接入*/
    LTE_ACCESS_NONCONTENT_REQ           = 0x03,                                 /*切换和PDCCH Order触发非竞争接入*/
    LTE_ACESS_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_ACESS_TYPE_ENUM_UINT8;

/*****************************************************************************
 结构名    : LTE_RNTI_TYPE_ENUM
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC和PHY间的RNTI类型
*****************************************************************************/
enum LTE_RNTI_TYPE_ENUM
{
    LTE_RA_RNTI                         = 0,                                    /*接收RAR(PDSCH)所使用RNTI*/
    LTE_P_RNTI                          ,                                       /*寻呼使用的RNTI*/
    LTE_SI_RNTI                         ,                                       /*广播使用的RNTI*/
    LTE_C_RNTI                          ,                                       /*接入后使用的C-RNTI*/
    LTE_SPS_RNTI                        ,                                       /*半静态调度使用的RNTI*/
    LTE_TC_RNTI                         ,                                       /*随机接入过程中使用的临时C-RNTI，用于Msg3加扰，Msg4解析*/
    LTE_TPC_PUCCH_RNTI                  ,                                       /*功控使用RNTI*/
    LTE_TPC_PUSCH_RNTI                  ,                                       /*功控使用RNTI*/
    LTE_M_RNTI                          ,                                       /*MBMS使用RNTI*/
    LTE_RNTI_TYPE_BUTT
};
typedef         VOS_UINT8           LTE_RNTI_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : LMAC_LPHY_ACCESS_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 随机接入发起的配置信息数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucPreambleIndex;                        /*MAC确定的Preamble ID*/
    VOS_UINT8                           ucPrachIndex;                           /*MAC确定的Prach Resource Index*/
    VOS_INT32                           lTxPower;                               /*MAC确定的Preamble发送功率(不包括路损)*/
    VOS_UINT32                          ulRARarTimeWindow;                      /*随机接入响应消息接收窗*/
}LMAC_LPHY_ACCESS_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_ACCESS_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 随机接入发起的配置信息确认数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                               /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usSFN;                                  /*发送Preamble对应空口帧号*/

    VOS_UINT16                          usSubFrameNum;                          /*发送Preamble对应空口子帧号*/
    VOS_UINT8                           aucRev[2];
}LMAC_LPHY_ACCESS_CNF_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_RAR_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 随机响应消息配置信息数据结构
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    LTE_ACESS_TYPE_ENUM_UINT8           enLteAccessType;                        /*随机接入模式指示*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT16                          usTrnti;                                /*临时C-RNTI*/
    VOS_UINT16                          usTa;                                   /*TA值*/

    VOS_UINT16                          usTaRecSysFn;                           /*接收Ta值的系统帧号*/
    VOS_UINT16                          usTaRecSubFn;                           /*接收Ta值的系统子帧号*/

    VOS_UINT16                          usDetalPrampup;                         /*消息3发射功率补偿因子，单位bd*/
    VOS_INT16                           sPreambleInitTargetPwr;                 /*Preamble在eNB的期望接收功率*/

    VOS_UINT32                          ulRarUlGrant;                           /*0-19比特位放20比特的上行授权信息*/
} LMAC_LPHY_RAR_CONFIG_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_RAR_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 随机响应消息配置确认信息数据结构
*****************************************************************************/
typedef struct
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
#endif
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           ucRev;
} LMAC_LPHY_RAR_CONFIG_CNF_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_DATA_REQ_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行数据发送的数据结构头
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usMacDataValid;                         /*MAC新传数据是否有效标志，0:无效 1:有效 */
    VOS_UINT16                          usPhroffset;                            /* 0:无效, 其他值有效，不包含头的偏移*/

    VOS_UINT16                          usTbSize;                               /*单位Bit，Pilot版本是字节*/
    VOS_UINT8                           ucHarqId;
    VOS_UINT8                           aucRev1[1];                             /*预留用*/
    VOS_UINT8                           aucRev2[4];                             /*预留用*/

}LMAC_LPHY_DATA_REQ_HEAD_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行数据发送的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_REQ_HEAD_STRU        stMacPhyDataReqHead;

    VOS_UINT8                           aucData[4];                              /*实际数据*/

} LMAC_LPHY_DATA_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_DATA_IND_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行数据接收的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT32 bitFrameType             :4;                                     /*帧类型*/
    VOS_UINT32 bitHarqProcNum           :4;                                     /*进程号*/
    VOS_UINT32 bitTbSize                :17;                                    /*数据块大小,单位:Bit*/
    VOS_UINT32 bitRecv1                 :3;                                     /*保留字段*/
    VOS_UINT32 bitTranNum               :4;                                     /*传输块序号*/

#ifndef LTE_UECAP5_MBMS_VERSION
    VOS_UINT32 bitSysFrm                :10;                                    /*帧号*/
    VOS_UINT32 bitRecv2                 :6;                                     /*保留字段*/
    VOS_UINT32 bitSubFrm                :4;                                     /*子帧号*/
    VOS_UINT32 bitRecv3                 :4;                                     /*保留字段*/
    VOS_UINT32 bitRntiType              :8;                                     /*RNTI Type*/
#else
    VOS_UINT32 bitSysFrm                :10;                                    /*帧号*/
    VOS_UINT32 bitPmchIndex             :6;                                     /*只有MBMS使用该字段，是指PMCH信道索引，其他业务都不使用*/
    VOS_UINT32 bitSubFrm                :4;                                     /*子帧号*/
    VOS_UINT32 bitRntiType              :4;                                     /*RNTI Type*/
    VOS_UINT32 bitAreaId                :8;                                     /*区域ID*/
#endif
}LMAC_LPHY_DATA_IND_HEAD_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行数据接收的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_DATA_IND_HEAD_STRU        stMacPhyIndHead;

    VOS_UINT8                           aucData[4];                             /*接收下行数据块实际内容*/
} LMAC_LPHY_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行广播数据接收的数据结构头
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_BCCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行广播数据接收的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_BCCH_DATA_IND_HEAD_STRU   stMacphyBcchIndHead;

    VOS_UINT8                           aucData[4];                             /*接收下行广播数据实际内容*/
} LMAC_LPHY_BCCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PCH_DATA_IND_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行寻呼数据接收的数据结构头
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_PCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行寻呼数据接收的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_PCH_DATA_IND_HEAD_STRU    stMacPhyPchIndHead;

    VOS_UINT8                           aucData[4];                             /*接收下行寻呼信息数据实际内容*/
} LMAC_LPHY_PCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_MCH_DATA_IND_HEAD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行MBMS数据接收的数据结构头
*****************************************************************************/
typedef LMAC_LPHY_DATA_IND_HEAD_STRU LMAC_LPHY_MCH_DATA_IND_HEAD_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_MCH_DATA_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行MBMS数据接收的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MCH_DATA_IND_HEAD_STRU    stMacPhyMchIndHead;

    VOS_UINT8                           aucData[4];                             /*接收下行寻呼信息数据实际内容*/
} LMAC_LPHY_MCH_DATA_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PMCH_MTCH_STOP_INFO
 协议表格  :
 ASN.1描述 :
 结构说明  : 单个PMCH停止信息
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPmchIndex;                            /*MBMS对应停止该MBMS区域的PMCH索引*/
    VOS_UINT8                           aucRev[3];
    VOS_UINT32                          ulPmchStopSubFrameNum;                  /*MBMS对应停止该MBMS区域的PMCH的计数*/
}LMAC_LPHY_PMCH_MTCH_STOP_INFO;

/*****************************************************************************
 结构名    : LMAC_LPHY_MTCH_STOP_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC通知PHY停止PMCH的信息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucAreaId;                               /*MBMS对应停止区域ID*/
    VOS_UINT8                           aucRev[1];
    LMAC_LPHY_PMCH_MTCH_STOP_INFO       stPmchStop;
} LMAC_LPHY_MTCH_STOP_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_UL_GRANT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行授权的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNewDataInd;                           /*上行授权新数据指示，0:重传,1:新数据*/
    VOS_UINT8                           ucSchedulMode;                          /*上行授权对应调度模式，0:动态调度,1:半静态调度*/
    VOS_UINT8                           ucGapInd;                               /*该标志只在半静态授权条件才有效，0：Gap无效，1：Gap有效，Gap指示对应得是数据发送时刻*/
    VOS_UINT8                           aucRev1[1];

    VOS_UINT32                          ulTBSize;                               /*上行授权对应的TB大小，单位:bit*/
}LMAC_LPHY_UL_GRANT_INFO_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_HARQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行HARQ反馈信息的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHarqFeedInd;                          /*上行HARQ反馈信息，0:NACK 1:ACK*/
    VOS_UINT8                           aucRev[3];
}LMAC_LPHY_HARQ_INFO_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行授权和上行HARQ反馈信息的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSFN;                                /*上行授权和HARQ的NACK反馈对应的上行数据发送的帧号*/
    VOS_UINT16                          usTxSubFrameNum;                        /*上行授权和HARQ的NACK反馈对应的上行数据发送的子帧号*/

    VOS_UINT8                           ucHarqId;                               /*上行授权和HARQ的NACK反馈对应的上行数据发送的进程号*/
    VOS_UINT8                           ucUlGrantInd;                           /*上行授权是否有效指示,0:无效PHICH上报有效;1:表示有效*/
    VOS_UINT16                          usRnti;                                 /*RNTI指示，用于判断临时RNTI或RNTI，主要用于Msg3处理过程*/

    LMAC_LPHY_UL_GRANT_INFO_STRU          stUlGrantInfo;                          /*上行授权信息*/

    LMAC_LPHY_HARQ_INFO_STRU              stHarqInfo;                             /*上行HARQ反馈信息*/
}LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_UL_GRANT_HARQ_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 上行授权和上行HARQ反馈信息的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usRcvSFN;                               /*上行授权和HARQ反馈接收的帧号*/
    VOS_UINT16                          usRcvSubFrameNum;                       /*上行授权和HARQ反馈接收的子帧号*/

    VOS_UINT8                           ucULGrantNum;                           /*上行授权和HARQ反馈的数目*/
    VOS_UINT8                           aucRev[1];
    VOS_UINT8                           aucRev2[2];

    LMAC_LPHY_UL_GRANT_HARQ_INFO_STRU     astUlGrantHarqInfo[2];                  /*上行授权和HARQ反馈信息*/
} LMAC_LPHY_UL_GRANT_HARQ_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_SR_DATA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 调度请求信息的数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_SR_DATA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 调度请求信息的确认数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucResult;                               /*0:成功，1：取消，2：失败(预留，暂时不用)*/
    VOS_UINT8                           ucSubFrame;                             /*SR发送成功所在的帧号*/
    VOS_UINT16                          usFrame;                                /*SR发送成功所在的子帧号*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SR_DATA_CNF_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_TA_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA值配置信息请求的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTa;                                   /*接收到eNB下发的TA值*/

    VOS_UINT16                          usTaRevSFN;                             /*接收到eNB下发的TA值的帧号*/
    VOS_UINT16                          usTaRcvSubFN;                           /*接收到eNB下发的TA值的子帧号*/
} LMAC_LPHY_TA_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_TA_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA值配置信息请求的确认数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_CNF_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_CRNTI_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : C-RNTI值配置信息请求的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT16                          usCrnti;                                /*接收到eNB下发的Crnti值*/

} LMAC_LPHY_CRNTI_CONFIG_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_CRNTI_CONFIG_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : C-RNTI值配置信息请求的确认数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CRNTI_CONFIG_CNF_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_CONNECTED_DRX_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接态下的DRX控制元接收到指示给PHY的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                               /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                 /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_CONNECTED_DRX_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 连接态下的DRX控制元接收到指示给PHY的确认数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_CONNECTED_DRX_CNF_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_PDCCH_ORDER_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCCH ORDER触发的非竞争解决随机接入的Preamble信息数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT8                           ucDediPreambleID;                       /*专用Preamble ID*/
    VOS_UINT8                           ucPrachMaskIndex;                       /*PRACH MASK Index*/
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PDCCH_ORDER_IND_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PDCCH ORDER触发的竞争解决随机接入的成功信息数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_RAR_TIMEOUT_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY接收RAR的时间窗超时通知MAC的信息数据结构
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_RAR_TIMEOUT_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_SPS_RELEASE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY进行半静态调度上行授权资源释放的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_SPS_RELEASE_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 通知PHY进行半静态调度上行授权资源释放的确认数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_SPS_RELEASE_CNF_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_RA_ACK_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 竞争解决MAC控制元检查正确情况下的ACK/NACK信息数据结构
             MAC写完ACK/NACK信息后设置为有效；DSP读取后清零,该原语是走单独邮箱
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usOpId;
    VOS_UINT8                           ucValidFlag;                            /* 0:ACK/NACK信息无效;1:ACK/NACK信息有效，*/
    VOS_UINT8                           ucAckNack;                              /* 0:表示NACK信息,1:表示ACK信息*/
} LMAC_LPHY_RA_ACK_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_PBCH_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行数据接收的数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/

    VOS_UINT16                          usSFN;                                  /*接收下行MIB数据块的帧号*/
    VOS_UINT16                          usSubFrameNum;                          /*接收下行MIB数据块的子帧号*/

    VOS_UINT16                          usAntennaPortsCount;                    /*物理层的天线端口数*/
    VOS_UINT8                           aucRev[2];

    VOS_UINT32                          ulTBSize;                               /*接收下行MIB数据块的TB大小，单位:bit*/

    VOS_UINT8                           aucData[4];                             /*接收下行MIB数据块实际内容*/
} LMAC_LPHY_PBCH_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_TA_TIMER_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA Timer是否运行通知PHY的响应数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT16                          usTaTimerRunInd;                        /*0：超时不运行，1：启动运行*/
} LMAC_LPHY_TA_TIMER_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_TA_TIMER_CNF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TA Timer是否运行通知PHY的响应数据结构
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/

    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgId;                                /*_H2ASN_Skip*/
    VOS_UINT16                          usOpId;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_TA_TIMER_CNF_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PL_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PL值上报的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlValue;
    VOS_UINT8                           aucRev[2];
} LMAC_LPHY_PL_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PHR_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHR值上报的数据结构
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cPhValue;
    VOS_UINT8                           aucRev[3];
} LMAC_LPHY_PHR_IND_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_FORCE_ACTIVE_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC在连接态DRX期间强制激活数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDrxForceActive;
} LMAC_LPHY_FORCE_ACTIVE_REQ_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC在切换过程中通知PHY关于CQI/SRS生效激活数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHoCqiSrsActive;
} LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : PHY释放上行半静态授权指示
*****************************************************************************/
typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32        enMsgId;                                /*_H2ASN_Skip*/

} LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_CAP_CONFIG_REQ_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MAC配置DSP启停GAP
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulGapStartFlag;                          /*1:Gap start;  0:Gap stop*/
} LMAC_LPHY_CAP_CONFIG_REQ_STRU;
/*****************************************************************************
 结构名    : LMAC_LPHY_MSG3_HARQ_IND_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Msg3重传对应HARQ反馈信息的数据结构
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usTxSfn;                                /*Msg3重传对应发送的帧号*/
    VOS_UINT8                           ucTxSbfn;                               /*Msg3重传对应发送的子帧号*/
    VOS_UINT8                           ucRev;
} LMAC_LPHY_MSG3_HARQ_IND_STRU;

/*****************************************************************************
 结构名    : LMAC_LPHY_DL_TB_BUFF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 下行数据接收的缓存结构
*****************************************************************************/
typedef  struct
{
    VOS_UINT32      ulTotalNum;                                                 /*ARM提供给DSP的TB缓存块总数，范围[0,4]ARM写，DSP读*/
    VOS_UINT32      aulTbAddr[4];                                               /*TB块缓存首地址数组，每一TB块缓存为16Kbyte（暂定）                                                                                连续内存块；缓存地址从首个数组元素依次往后填写，
                                                                                若总块数小于4，则用全0补齐；全0表示该地址无效；ARM写，DSP读*/
    VOS_UINT32      ulUsedNum;                                                  /*DSP一次译码上报的TB块数目，范围[0,4]DSP写，ARM读*/
}LMAC_LPHY_DL_TB_BUFF_STRU;

typedef struct
{
    LMAC_LPHY_MSG_TYPE_ENUM_UINT32      enMsgID;                                /*_H2ASN_MsgChoice_Export LMAC_LPHY_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          LMAC_LPHY_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}LMAC_LPHY_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    LMAC_LPHY_MSG_DATA                    stMsgData;
}MacPhyInterface_MSG;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
/*后续更新*/
#define LMAC_LPHY_SYSFRM_ADDR              (LPHY_LMAC_FRAME_ADDR)               /*MAC直接从BBP寄存器读取系统帧号*/
#define LMAC_LPHY_SUBFRM_ADDR              (LPHY_LMAC_SUB_FRAME_ADDR)           /*MAC直接从BBP寄存器读取系统子帧号*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (LPHY_LMAC_TIMER_LOCK_ADDR)          /*MAC直接从BBP寄存器读取系统帧号和子帧号时需要先清除操作*/

/*后续更新*/
#define DEDI_MAILBOX_FLAG                (0x4)                                  /*专用邮箱的读写标志占4个字节*/
#define DEDI_MAILBOX_UL_START_ADDR       (LPHY_MAILBOX_LMAC_UP_BASE_ADDR)       /*专用邮箱的由PHY上报给MAC的消息的首地址*/
#define DEDI_MAILBOX_DL_START_ADDR       (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR)     /*专用邮箱的由MAC下发给PHY的消息的首地址*/
#else
extern VOS_UINT8        g_aucDediUlMailBox[512];
extern VOS_UINT8        g_aucDediDlMailBox[256];
extern VOS_UINT32       g_usSysFram;
extern VOS_UINT32       g_ucSubFram;
extern VOS_UINT32       g_ulFramLock;

#define LMAC_LPHY_SYSFRM_ADDR              (&g_usSysFram)                           /*MAC直接从BBP寄存器读取系统帧号*/
#define LMAC_LPHY_SUBFRM_ADDR              (&g_ucSubFram)                           /*MAC直接从BBP寄存器读取系统子帧号*/
#define LMAC_LPHY_TIMER_LOCK_ADDR          (&g_ulFramLock)          /*MAC直接从BBP寄存器读取系统帧号和子帧号时需要先清除操作*/

#define DEDI_MAILBOX_FLAG                (0x4)                                  /*专用邮箱的读写标志占4个字节*/
#define DEDI_MAILBOX_UL_START_ADDR       g_aucDediUlMailBox                     /*专用邮箱的由PHY上报给MAC的消息的首地址*/
#define DEDI_MAILBOX_DL_START_ADDR       g_aucDediDlMailBox                           /*专用邮箱的由MAC下发给PHY的消息的首地址*/
#endif


/*****************************************************************************
 专用邮箱的由PHY 上报给MAC的各个消息地址，总大小预留为512Byte
 说明:为了使用方便，以及考虑性能，一些FLAG_ADDR暂时保留不使用
        直接对相关地址读取便可，除非特别说明，FLAG ADDR默认是使用的。
*****************************************************************************/
#define DEDI_UL_GRANT_HARQ_FLAG_ADDR     (DEDI_MAILBOX_UL_START_ADDR)
#define DEDI_UL_GRANT_HARQ_ADDR          (DEDI_UL_GRANT_HARQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_IND_FLAG_ADDR   (DEDI_UL_GRANT_HARQ_ADDR + sizeof(LMAC_LPHY_UL_GRANT_HARQ_IND_STRU))
#define DEDI_PDCCH_ORDER_IND_ADDR        (DEDI_PDCCH_ORDER_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR  (DEDI_PDCCH_ORDER_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_IND_STRU))
#define DEDI_PDCCH_ORDER_SUCC_ADDR       (DEDI_PDCCH_ORDER_SUCC_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RAR_TIMEOUT_IND_FLAG_ADDR   (DEDI_PDCCH_ORDER_SUCC_ADDR + sizeof(LMAC_LPHY_PDCCH_ORDER_SUCC_IND_STRU))
#define DEDI_RAR_TIMEOUT_IND_ADDR        (DEDI_RAR_TIMEOUT_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_ACCESS_CNF_FLAG_ADDR        (DEDI_RAR_TIMEOUT_IND_ADDR + sizeof(LMAC_LPHY_RAR_TIMEOUT_IND_STRU))
#define DEDI_ACCESS_CNF_ADDR             (DEDI_ACCESS_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_CNF_FLAG_ADDR       (DEDI_ACCESS_CNF_ADDR + sizeof(LMAC_LPHY_ACCESS_CNF_STRU))
#define DEDI_SR_DATA_CNF_ADDR            (DEDI_SR_DATA_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_PHR_IND_FLAG_ADDR标志暂时不使用，PS直接读取DEDI_PHR_IND_ADDR信息使用*/
#define DEDI_PHR_IND_FLAG_ADDR           (DEDI_SR_DATA_CNF_ADDR + sizeof(LMAC_LPHY_SR_DATA_CNF_STRU))
#define DEDI_PHR_IND_ADDR                (DEDI_PHR_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_PL_IND_FLAG_ADDR标志暂时不使用，PS直接读取DEDI_PL_IND_ADDR信息使用*/
#define DEDI_PL_IND_FLAG_ADDR            (DEDI_PHR_IND_ADDR + sizeof(LMAC_LPHY_PHR_IND_STRU))
#define DEDI_PL_IND_ADDR                 (DEDI_PL_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*PDCCH释放上行半静态授权的指示*/
#define DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR  (DEDI_PL_IND_ADDR + sizeof(LMAC_LPHY_PL_IND_STRU))
#define DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR       (DEDI_PDCCH_RELEASE_ULSPS_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*Msg3 重传对应HARQ发送帧号和子帧号*/
#define DEDI_MSG3_HARQ_IND_FLAG_ADDR  (DEDI_PDCCH_RELEASE_ULSPS_IND_ADDR + sizeof(LMAC_LPHY_PDCCH_RELEASE_ULSPS_IND_STRU))
#define DEDI_MSG3_HARQ_IND_ADDR       (DEDI_MSG3_HARQ_IND_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG CNF*/
#define DEDI_RAR_CONFIG_CNF_FLAG_ADDR    (DEDI_MSG3_HARQ_IND_ADDR + sizeof(LMAC_LPHY_MSG3_HARQ_IND_STRU))
#define DEDI_RAR_CONFIG_CNF_ADDR         (DEDI_RAR_CONFIG_CNF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DSP检查到MAC PDU Valid标志为无效,把该标志置为1，MAC负责清除*/
#define DEDI_MAC_PDU_INVALID_FLAG        (DEDI_RAR_CONFIG_CNF_ADDR+sizeof(LMAC_LPHY_RAR_CONFIG_CNF_STRU))


/*****************************************************************************
 专用邮箱的由MAC下发给PHY的各个消息地址总大小预留为256Byte
 说明:为了使用方便，以及考虑性能，一些FLAG_ADDR暂时保留不使用
        直接对相关地址读取便可，除非特别说明，FLAG ADDR默认是使用的。
*****************************************************************************/
/*DEDI_DL_TB_BUFF_FLAG_ADDR标志暂时不使用，DSP直接读取DEDI_DL_TB_BUFF_ADDR信息使用*/
#define DEDI_DL_TB_BUFF_FLAG_ADDR        (DEDI_MAILBOX_DL_START_ADDR)
#define DEDI_DL_TB_BUFF_ADDR             (DEDI_DL_TB_BUFF_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_ACCESS_REQ_FLAG_ADDR        (DEDI_DL_TB_BUFF_ADDR + sizeof(LMAC_LPHY_DL_TB_BUFF_STRU))
#define DEDI_ACCESS_REQ_ADDR             (DEDI_ACCESS_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_SR_DATA_REQ_FLAG_ADDR       (DEDI_ACCESS_REQ_ADDR + sizeof(LMAC_LPHY_ACCESS_REQ_STRU))
#define DEDI_SR_DATA_REQ_ADDR            (DEDI_SR_DATA_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

#define DEDI_RA_ACK_REQ_FLAG_ADDR        (DEDI_SR_DATA_REQ_ADDR + sizeof(LMAC_LPHY_SR_DATA_REQ_STRU))
#define DEDI_RA_ACK_REQ_ADDR             (DEDI_RA_ACK_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR标志暂时不使用，DSP直接读取DEDI_FORCE_ACTIVE_REQ_ADDR信息使用*/
#define DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR  (DEDI_RA_ACK_REQ_ADDR + sizeof(LMAC_LPHY_RA_ACK_REQ_STRU))
#define DEDI_FORCE_ACTIVE_REQ_ADDR       (DEDI_FORCE_ACTIVE_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR标志暂时不使用，DSP直接读取DEDI_HO_CQI_SRS_ACTIVE_ADDR信息使用*/
#define DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR (DEDI_FORCE_ACTIVE_REQ_ADDR + sizeof(LMAC_LPHY_FORCE_ACTIVE_REQ_STRU))
#define DEDI_HO_CQI_SRS_ACTIVE_ADDR      (DEDI_HO_CQI_SRS_ACTIVE_FLAG_ADDR + DEDI_MAILBOX_FLAG)

/*RAR CONFIG REQ*/
#define DEDI_RAR_CONFIG_REQ_FLAG_ADDR    (DEDI_HO_CQI_SRS_ACTIVE_ADDR + sizeof(LMAC_LPHY_HO_CQI_SRS_ACTIVE_STRU))
#define DEDI_RAR_CONFIG_REQ_ADDR         (DEDI_RAR_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)


/* L2有缓存，DSP不能进入睡眠，否则影响数传时延，MAC负责置和清除*/
#define DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG   (DEDI_RAR_CONFIG_REQ_ADDR+sizeof(LMAC_LPHY_RAR_CONFIG_REQ_STRU))

#define DEDI_GAP_CONFIG_REQ_FLAG_ADDR     (DEDI_MAC_PHY_ONLY_RF_SLEEP_FLAG + sizeof(VOS_UINT32))
#define DEDI_GAP_CONFIG_REQ_ADDR          (DEDI_GAP_CONFIG_REQ_FLAG_ADDR + DEDI_MAILBOX_FLAG)
/*****************************************************************************
  10 函数声明
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

#endif /* end of LMacPhyInterface.h */

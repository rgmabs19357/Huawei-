/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TDS_DT_OM_def.h
  版 本 号   : 初稿
  生成日期   : 2012年9月19日
  最近修改   :
  功能描述   : TDS  路测功能头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月19日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __TDS_DT_OM_DEF_H__
#define __TDS_DT_OM_DEF_H__
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*y00151394  Add For HSO Display Begin*/
typedef struct _TDS_OM_CELL_INFO_IND_
{

    U16          UartBuff_SubFN;
    U16          UartBuff_STATE;
    U16          UartBuff_504;
    U16          UartBuff_MsgID;
    U16          usCellId;
    U16          usFreq;
    S16          sRscp;
    S16          sRssi;
    S16          sIscp;
    U16          UartBuffData[26];
}TDS_OM_CELL_INFO_IND_STRU;

typedef struct _TDS_OM_TX_PWR_INFO_IND_
{

    U16          UartBuff_SubFN;
    U16          UartBuff_STATE;
    U16          UartBuff_504;
    U16          UartBuff_MsgID;
    U16          sMinTxPower;
    U16          TxTsNum;
    S16          TimeSlot1Power;
    S16          TimeSlot2Power;
    S16          TimeSlot3Power;
    S16          TimeSlot4Power;
    S16          TimeSlot5Power;
    U16          usEPUCHBitMap;
    U16          usHSSICHBITMap;
    U16          usDCHBITMap;
    U16          usRACHBITMap;
    U16          MaxAllowedTxPower;
    U16          TimeSlotTx0;
    U16          TimeSlotTx1;
    U16          TimeSlotTx2;
    U16          TimeSlotTx3;
    U16          TimeSlotTx4;
    U16          TimeSlotTx5;
    U16          TimeSlotTx6;
    U16          EPUCHPathloss;
    U16          DPCHPathloss;
    U16          PowerStepSize;
    U16          TpcSsval;
    U16          TpcKeepflg;
    S16          TcpAdj;
}TDS_OM_RX_PWR_INFO_IND_STRU;

typedef struct
{
    U16          UartBuff_SubFN;
    U16          UartBuff_STATE;
    U16          UartBuff_504;
    U16          UartBuff_MsgID;
    S16          UartBuffData04;
    S16          UartBuffData05;
    S16          UartBuffData06;
    S16          UartBuffData07;
    S16          UartBuffData08;
    S16          UartBuffData09;
    S16          UartBuffData10;
    S16          UartBuffData11;
    S16          UartBuffData12;
    S16          UartBuffData13;
    S16          UartBuffData14;
    S16          UartBuffData15;
    S16          UartBuffData16;
    S16          UartBuffData17;
    S16          UartBuffData18;
    S16          UartBuffData19;
    S16          UartBuffData20;
    S16          UartBuffData21;
    S16          UartBuffData22;
    S16          UartBuffData23;
    S16          UartBuffData24;
    S16          UartBuffData25;
    S16          UartBuffData26;
    S16          UartBuffData27;
    S16          UartBuffData28;
    S16          UartBuffData29;
    S16          UartBuffData30;
    S16          UartBuffData31;
    S16          UartBuffData32;
    S16          UartBuffData33;
    S16          UartBuffData34;
    S16          UartBuffData35;
}TDS_OM_SOCP_TRACE_FOR_HSO;

typedef struct _TDS_OM_TX_PWR_INFO_IND_
{

    U16          UartBuff_SubFN;
    U16          UartBuff_STATE;
    U16          UartBuff_504;
    U16          UartBuff_MsgID;
    U16          TxTsNum;
    U16          TimeSlotTx0;
    U16          TimeSlotTx1;
    U16          TimeSlotTx2;
    U16          TimeSlotTx3;
    U16          TimeSlotTx4;
    U16          TimeSlotTx5;
    U16          TimeSlotTx6;
    S16          TimeSlot0Power;
    S16          TimeSlot1Power;
    S16          TimeSlot2Power;
    S16          TimeSlot3Power;
    S16          TimeSlot4Power;
    S16          TimeSlot5Power;
    S16          TimeSlot6Power;
    U16          usRACHBITMAP;
}TDS_OM_TX_FCH_PWR_INFO_IND_STRU;
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TDS_DT_OM_DEF_H__ */



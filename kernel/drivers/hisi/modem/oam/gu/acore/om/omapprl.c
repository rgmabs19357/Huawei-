/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : Omapprl.c
  版 本 号   : 初稿
  生成日期   : 2008年6月11日
  最近修改   :
  功能描述   : R接口数据转发模块
  函数列表   :
  修改历史   :
  1.日    期   : 2008年6月11日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "omrl.h"
#include "omringbuffer.h"
#include "omprivate.h"
#include "cpm.h"
#include "OmHdlcInterface.h"
#include "OmAppRl.h"
#include "OmApp.h"
#include "omsdlog.h"
#include "OmToolInterface.h"
#include "SCMProc.h"
#include "ombufmngr.h"
#include "AtAppVcomInterface.h"
#include "Omappagent.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -e767 修改人:马昊 00128685;检视人:徐铖 51137;原因:Log打印 */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_OMRL_C
/*lint +e767 修改人:马昊 00128685;检视人:徐铖 51137; */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
OMRL_MSG_COMBINE_INFO_STRU              g_stMsgCombineInfo;

/*控制缓冲区访问的互斥信号量*/
VOS_UINT32                              g_AcpuOmTxBuffSem;

/* 记录从pc侧到ue侧时正常接收数据信息 */
OM_ACPU_PC_UE_SUC_STRU                  g_stAcpuPcToUeSucRecord;

/* 记录数据从pc侧到ue侧时发生的各类错误 */
OM_ACPU_PC_UE_FAIL_STRU                 g_stAcpuPcToUeErrRecord;

/*记录往PC侧发送数据的正常信息 */
OM_UE_PC_SUC_STRU                       g_stAcpuUeToPcSucRecord;

/*记录往PC侧发送数据时发生的各类错误*/
OM_UE_PC_FAIL_STRU                      g_stAcpuUeToPcErrRecord;

#if (FEATURE_ON == FEATURE_CBT_LOG)
OMRL_MSG_COMBINE_INFO_STRU              g_stCBTMsgCombineInfo;

/* 记录从pc侧到ue侧时正常接收数据信息 */
OM_ACPU_PC_UE_SUC_STRU                  g_stCBTAcpuPcToUeSucRecord;

/* 记录数据从pc侧到ue侧时发生的各类错误 */
OM_ACPU_PC_UE_FAIL_STRU                 g_stCBTAcpuPcToUeErrRecord;
#endif

/*记录开始时间*/
VOS_UINT32                              g_ulAcpuLastTick = 0;

/*记录字节长度*/
VOS_UINT32                              g_ulAcpuLastByteCnt = 0;

/*指向OM分包头内容的指针*/
OM_APP_MSG_SEG_EX_STRU                 *g_pstAcpuSegMsgEx = VOS_NULL_PTR;

/* HDLC控制结构 */
OM_HDLC_STRU                            g_stOmHdlcEntity;

OM_HDLC_STRU                            g_stNVHdlcEntity;

#if (FEATURE_ON == FEATURE_CBT_LOG)
OM_HDLC_STRU                            g_stCBTHdlcEntity;
#endif

/* 用来控制OM的打印输出 */
#ifdef OAM_UT_DEBUG
VOS_UINT32                              g_ulOmAcpuDbgFlag = VOS_NULL_DWORD;
#else
VOS_UINT32                              g_ulOmAcpuDbgFlag = VOS_FALSE;
#endif

/* OM缓冲区控制块 */
OM_BUF_CTRL_STRU                        g_stAcpuOmBufCtrl;

OM_NV_MNTN_RECORD_STRU                 *g_pstRecordOmToApp = VOS_NULL_PTR;
VOS_UINT32                              g_ulNvOmToAppCount = 0;

OM_NV_MNTN_RECORD_STRU                 *g_pstRecordAppToOm = VOS_NULL_PTR;
VOS_UINT32                              g_ulNvAppToOmCount = 0;

#if (VOS_LINUX == VOS_OS_VER)
struct semaphore                        g_stOmTxBuffSem;
#endif

#if (FEATURE_ON == FEATURE_CBT_LOG)
VOS_UINT32                              g_ulCBTStatus = OM_NOT_CBT_MSG;
VOS_UINT32                              g_ulCBTEstablishStatus = 0;
VOS_UINT8                              *g_pucCBTHdlcEncBuf;

#if (VOS_LINUX == VOS_OS_VER)
struct semaphore                        g_stOmRxCBTBuffSem;
#endif

#endif

VOS_UINT32                              g_ulCBTLogEnable = 0;

/* 保存SD卡的Debug 信息 */
extern OM_SD_DEBUG_INFO                 g_stOmSDDebugInfo;
extern OM_VCOM_DEBUG_INFO               g_stVComDebugInfo;

#if (FEATURE_ON == FEATURE_CBT_LOG)
extern OM_VCOM_CBT_LOG_DEBUG_INFO     g_stVComCBTDebugInfo;
#endif

extern OM_RECORD_BUF_STRU               g_astAcpuRecordInfo[VOS_EXC_DUMP_MEM_NUM_BUTT];

extern VOS_VOID BSP_SOCP_GetEncSrcReg(VOS_UINT32 *pulData, VOS_UINT32 ulDataMax);

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : OMRL_AcpuCpuIdToPid
 功能描述  : 根据CPU ID找到对应模块的PID
 输入参数  : ucCpuId:   CPU ID
 输出参数  : pulPid -- 指向模块PID
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuCpuIdToPid(VOS_UINT8 ucCpuId, VOS_UINT32 *pulPid)
{

      switch(ucCpuId)
      {
        case OM_TOOL_RSV_ID:
        case OM_TOOL_CCPU_ID:
            *pulPid = WUEPS_PID_OM;/* ccpu om pid */
            break;
        case OM_TOOL_ACPU_ID:
            *pulPid = ACPU_PID_OM; /* acpu om pid */
            break;
        case OM_TOOL_HIFI_ID:
            *pulPid = DSP_PID_HIFI_OM;/* HIFI om pid */
            break;
        case OM_TOOL_MCU_ID:
            *pulPid = ACPU_PID_MCU_OM;/* MCU om pid */
            break;
        default:
            /* 打印错误 */
            return VOS_ERR;
      }

      return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuRecordNvInfo
 功能描述  : 记录和校准工具的数据交互
 输入参数  : none
 输出参数  : none
 返 回 值  : none
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2013年9月12日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OMRL_AcpuRecordNvInfo(VOS_VOID)
{
    APP_OM_MSG_EX_STRU                 *pstAppToOmMsg;
    OM_SW_VER_FLAG_STRU                 stCustomVersion;
    VOS_UINT32                          ulLen;

    if ( VOS_OK != NV_Read(en_NV_Item_SW_VERSION_FLAG, &stCustomVersion, sizeof(stCustomVersion)) )
    {
        stCustomVersion.ulNvSwVerFlag = VOS_TRUE;
    }

    /* 如果ulCustomVersion == VOS_TRUE表示不是烧片版本，则直接返回 */
    if ( (VOS_TRUE == stCustomVersion.ulNvSwVerFlag))
    {
        return;
    }

    /* 烧片版本且FTM模式才记录 */
    if(VOS_TRUE != g_ulAcpuFTMFlag)
    {
        return;
    }

    pstAppToOmMsg = (APP_OM_MSG_EX_STRU*)g_stMsgCombineInfo.pstWholeMsg->aucValue;

    /* 判断码流 */
    if ( (OM_WRF_FUNC == ((pstAppToOmMsg->ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_GRF_FUNC == ((pstAppToOmMsg->ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_QUERY_FUNC == ((pstAppToOmMsg->ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_NV_FUNC == ((pstAppToOmMsg->ucFuncType) & OM_FUNCID_VALUE_BITS)))
    {
        g_pstRecordAppToOm[g_ulNvAppToOmCount].ulSlice = VOS_GetSlice();
        g_pstRecordAppToOm[g_ulNvAppToOmCount].ulFlag  = 0x55555555;

        /* 消息长度加两字节的functype和cpuid */
        ulLen = pstAppToOmMsg->usLength + 2;

        if (ulLen > NV_MNTN_SAVE_MAX_MSG_LEN)
        {
            ulLen = NV_MNTN_SAVE_MAX_MSG_LEN;
        }

        /*lint -e670*/
        VOS_MemCpy(g_pstRecordAppToOm[g_ulNvAppToOmCount].aucVaule, g_stMsgCombineInfo.pstWholeMsg->aucValue, ulLen);
        /*lint +e670*/

        g_ulNvAppToOmCount++;

        if(SAVE_MAX_SEND_INFO == g_ulNvAppToOmCount)
        {
             g_ulNvAppToOmCount = 0;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuMsgDispatch
 功能描述  : 将数据包分发出去
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuMsgDispatch(VOS_VOID)
{
    VOS_UINT32                       ulRslt;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE(g_stMsgCombineInfo.pstWholeMsg->aucValue, g_stMsgCombineInfo.pstWholeMsg->ulLength, OM_ACPU_DISPATCH_MSG);
    /*lint +e40*/

    /* CCPU的消息通过ICC通道发送 */
    if (WUEPS_PID_OM == g_stMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        ulRslt = GU_OamSndPcMsgToCcpu(g_stMsgCombineInfo.pstWholeMsg->aucValue, g_stMsgCombineInfo.pstWholeMsg->ulLength);

        g_stAcpuPcToUeSucRecord.stCcpuData.ulDataLen += g_stMsgCombineInfo.pstWholeMsg->ulLength;
        g_stAcpuPcToUeSucRecord.stCcpuData.ulNum++;

        OMRL_AcpuRecordNvInfo();

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);
    }
    else if (ACPU_PID_OM == g_stMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stAcpuPcToUeSucRecord.stAcpuData.ulDataLen += g_stMsgCombineInfo.pstWholeMsg->ulLength;
        g_stAcpuPcToUeSucRecord.stAcpuData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);
    }
    else if (DSP_PID_HIFI_OM == g_stMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stAcpuPcToUeSucRecord.stHifiData.ulDataLen += g_stMsgCombineInfo.pstWholeMsg->ulLength;
        g_stAcpuPcToUeSucRecord.stHifiData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);
    }
    else
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stAcpuPcToUeSucRecord.stMcuData.ulDataLen += g_stMsgCombineInfo.pstWholeMsg->ulLength;
        g_stAcpuPcToUeSucRecord.stMcuData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);
    }

    g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

    if (VOS_OK != ulRslt )
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : OMRL_AcpuMsgCombine
 功能描述  : 对消息 组包并发送给对应CPU OM消息处理模块处理
 输入参数  : pucData:   需要处理的数据内容
             ulDataLen: 数据长度

 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年6月11日
    修改内容   : 新生成函数
  2.日    期   : 2012年8月6日
    修改内容   : 增加将组包后数据根据CPUID分发

*****************************************************************************/
VOS_UINT32 OMRL_AcpuMsgCombine(VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT32                       ulRslt = VOS_OK;/*Get the return value of PS_SEND_MSG.*/
    VOS_UINT8                        ucCurrentSegSn;/*Reserve the current packet's SN.*/
    OM_APP_MSG_SEGMENT_STRU          *pstOmAppSeg;
    APP_OM_GU_MSG_STRU               *pstAppOmMsg;

    /*Check the input parameter's validity.Make sure empty segment can't pass*/
    if ( (VOS_NULL_PTR == pucData) ||
        (usLen <= sizeof(OM_APP_MSG_SEGMENT_STRU)) )
    {
        LogPrint("OMRL_AcpuMsgCombine: The input is wrong.");

        g_stAcpuPcToUeErrRecord.usLenTooShortErr++;

        return VOS_ERR;
    }

    pstOmAppSeg = (OM_APP_MSG_SEGMENT_STRU *)pucData;

    /*Check the input parameter's validity.*/
    if (usLen != ((pstOmAppSeg->usSegLen + 3) & ~0x3))
    {
        LogPrint("OMRL_AcpuMsgCombine: The input length is wrong.");

        g_stAcpuPcToUeErrRecord.usSegLenErr++;

        return VOS_ERR;
    }

    usLen = pstOmAppSeg->usSegLen;

    ucCurrentSegSn = pstOmAppSeg->ucSegSn;

    /*When the MSG packet is new, we need initialize the static variable.*/
    if (1 == ucCurrentSegSn)
    {
        if (VOS_NULL_PTR != g_stMsgCombineInfo.pstWholeMsg)
        {
            VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);
            g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            g_stAcpuPcToUeErrRecord.usPacketLostErr++;
        }

        /*The new MSG packet is coming.*/
        g_stMsgCombineInfo.ucExpectedSegSn = 1;
        g_stMsgCombineInfo.ulMoveLen       = 0;

        if (usLen < (sizeof(APP_OM_GU_MSG_STRU) + OM_APP_MSG_SEGMENT_HEADER_LENGTH))
        {
            LogPrint("OMRL_AcpuMsgCombine: The input parameter is wrong.");

            g_stAcpuPcToUeErrRecord.usMsgLenErr++;

            return VOS_ERR;
        }

        pstAppOmMsg = (APP_OM_GU_MSG_STRU *)(pucData + OM_APP_MSG_SEGMENT_HEADER_LENGTH);

        g_stMsgCombineInfo.ulTotalMsgLen = pstAppOmMsg->usLength + APP_OM_HEADER_LENGTH;

        /* 组包完成后判断是否大于阈值 */
        if (OM_RL_TOTAL_MSG_MAX_LEN < g_stMsgCombineInfo.ulTotalMsgLen)
        {
            g_stAcpuPcToUeErrRecord.usMsgTooLongErr++;

            LogPrint1("OMRL_AcpuMsgCombine: receive first msg pack is too long %d;\r\n",
                        (VOS_INT32)g_stMsgCombineInfo.ulTotalMsgLen);

            /* 底软最大支持保存1024字节的内容，底软没有提供宏，这里直接使用数字 */
            DRV_SYSTEM_ERROR(OAM_PC_LENGTH_TOO_BIG, (VOS_INT)g_stMsgCombineInfo.ulTotalMsgLen, 0, (VOS_CHAR *)pucData, 1024);

            return VOS_ERR;
        }

        /*Allocate the memory space.*/
        g_stMsgCombineInfo.pstWholeMsg = VOS_AllocMsg(ACPU_PID_OM,  g_stMsgCombineInfo.ulTotalMsgLen);
        if (VOS_NULL_PTR == g_stMsgCombineInfo.pstWholeMsg)
        {
            LogPrint("OMRL_AcpuMsgCombine: VOS_AllocMsg fail.");

            g_stAcpuPcToUeErrRecord.usAllocMsg++;

            return VOS_ERR;
        }

        /* 根据CPU ID查找到相应的PID，对于工具下发数据帧，用VOS_OM_HEADER结构中保留字段表示CPUID */
        ulRslt = OMRL_AcpuCpuIdToPid(pstAppOmMsg->ucCpuId, &g_stMsgCombineInfo.pstWholeMsg->ulReceiverPid);
        if (VOS_OK != ulRslt)
        {
            /* 释放消息空间 */
            VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);

            g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            g_stAcpuPcToUeErrRecord.usCpuIdErr++;

            /* 此处错误直接返回，不用记录，函数里面已经记录了CPU ID错误的情况 */
            return VOS_ERR;
        }

        g_stMsgCombineInfo.ucTotalSegNum = pstOmAppSeg->ucSegNum;
    }

    if ( g_stMsgCombineInfo.ucTotalSegNum != pstOmAppSeg->ucSegNum )
    {
        LogPrint("OMRL_AcpuMsgCombine: The length of the packet is biger than the size of allocated memory.");

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);

        g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stAcpuPcToUeErrRecord.usSegNumErr++;

        return VOS_ERR;
    }

    /*The expected MSG pakcet is lost.*/
    if (g_stMsgCombineInfo.ucExpectedSegSn != ucCurrentSegSn)
    {
        /*Print the error info.*/
        LogPrint2("OMRL_AcpuMsgCombine: expected SN is %d, current SN is %d.", g_stMsgCombineInfo.ucExpectedSegSn, ucCurrentSegSn);

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);

        g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stAcpuPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    /*We make sure that the memory can't be violated.*/
    if (g_stMsgCombineInfo.ulTotalMsgLen < (g_stMsgCombineInfo.ulMoveLen + (usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH)))
    {
        LogPrint("OMRL_AcpuMsgCombine: The length of the packet is biger than the size of allocated memory.\n");

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);

        g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stAcpuPcToUeErrRecord.usNoMemErr++;

        return VOS_ERR;
    }

    VOS_MemCpy((VOS_UINT8*)(g_stMsgCombineInfo.pstWholeMsg->aucValue) + g_stMsgCombineInfo.ulMoveLen,
               pucData + OM_APP_MSG_SEGMENT_HEADER_LENGTH, usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH);
    g_stMsgCombineInfo.ulMoveLen += usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH;
    g_stMsgCombineInfo.ucExpectedSegSn++;

    /*If the current MSG packet is an complete packet.*/
    if (g_stMsgCombineInfo.ucTotalSegNum == ucCurrentSegSn)
    {
        /* 组包完成后判断是否大于阈值 */
        if (OM_RL_TOTAL_MSG_MAX_LEN < g_stMsgCombineInfo.ulTotalMsgLen)
        {
            g_stAcpuPcToUeErrRecord.usMsgTooLongErr++;

            /* 释放消息空间 */
            VOS_FreeMsg(ACPU_PID_OM, g_stMsgCombineInfo.pstWholeMsg);

            g_stMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            return VOS_ERR;
        }

        /*It will send the MSG to OM module.*/
        ulRslt = OMRL_AcpuMsgDispatch();

        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuSendMsg
 功能描述  : 将消息发送到对应的模块
 输入参数  : pucData:   需要处理的数据内容
             ulDataLen: 数据长度
             ulSenderPid:发送PID
             ulReceiverPid:接收消息的PID
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuSendMsg(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen, VOS_UINT32 ulSenderPid, VOS_UINT32 ulReceiverPid)
{

    MsgBlock           *pstAppOmMsg = VOS_NULL_PTR;

    pstAppOmMsg = VOS_AllocMsg(ulSenderPid, ulDataLen);
    if (VOS_NULL_PTR == pstAppOmMsg)
    {
        return VOS_ERR;
    }

    pstAppOmMsg->ulReceiverPid = ulReceiverPid;

    /* copy 消息内容 */
    VOS_MemCpy((VOS_UINT8 *)pstAppOmMsg->aucValue, pucData, ulDataLen);

    return VOS_SendMsg(ulSenderPid, pstAppOmMsg);

}

/*****************************************************************************
 函 数 名  : OMRL_AcpuHeadProc
 功能描述  : 实现消息组包及分发
 输入参数  : pucData:   需要处理的数据内容
             ulSize: 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuHeadProc(VOS_UINT8 *pucData, VOS_UINT32 ulSize)
{
    VOS_UINT32          ulRslt;
    VOS_UINT32          ulValue;
    VOS_UINT32          ulTmpLen;

    if ((OM_RL_DATATYPE_LEN + OM_USB_FRAME_LEN) >= ulSize)
    {
        /* 打印错误 */
        LogPrint("OMRL_AcpuHeadProc: The data length is error.");
        g_stAcpuPcToUeErrRecord.usPacketLenErr++;
        return VOS_ERR;
    }

    VOS_MemCpy(&ulValue, (pucData+OM_RL_DATATYPE_LEN), sizeof(VOS_UINT32));

    /* 区分普通消息和链路消息 */
    /* 数据包跳过一个字节判断是不是0xaaaa5555 */
    if (OM_USB_FRAME_HEAD != ulValue)
    {
        /* 此分支中为链路消息 */
        ulTmpLen =  ulSize - sizeof(OM_APP_MSG_SEGMENT_STRU);

        /* 链路消息长度判断 */
        if (sizeof(APP_OM_MSG_EX_STRU) != ulTmpLen)
        {
            g_stAcpuPcToUeErrRecord.usLinkDataLenErr++;

            return VOS_ERR;
        }

        /* 跳过四字节sn header */
        ulRslt = OMRL_AcpuSendMsg(pucData + sizeof(OM_APP_MSG_SEGMENT_STRU),
                       ulTmpLen, ACPU_PID_OM, ACPU_PID_OM);

        g_stAcpuPcToUeSucRecord.stLinkData.ulDataLen += ulTmpLen;
        g_stAcpuPcToUeSucRecord.stLinkData.ulNum++;

        return ulRslt;
    }

    /* 收到普通消息时先判断当前链路状态 */
    if (OM_STATE_IDLE == g_ulAcpuOMSwitchOnOff)
    {
         g_stAcpuPcToUeErrRecord.usLinkStatusErr++;
         return VOS_ERR;
    }



    /* 普通消息，判断datatype字段是不是GU数据 */
    if (OM_RL_DATATYPE_GU != *pucData)
    {
         g_stAcpuPcToUeErrRecord.usDatatypeErr++;
         return VOS_ERR;
    }

    VOS_MemCpy(&ulValue, (pucData + ulSize - OM_USB_TAIL_LEN), sizeof(VOS_UINT32));

    /* 判断数据包尾是不是0x5555aaaa */
    if (OM_USB_FRAME_TAIL != ulValue)
    {
        /* 记录错误 */
        g_stAcpuPcToUeErrRecord.usDataHeadErr++;
        return VOS_ERR;
    }

    /* 数据指针和长度更新*/
    pucData += (OM_RL_DATATYPE_LEN + OM_USB_HEAD_LEN);
    ulSize  -= (OM_RL_DATATYPE_LEN + OM_USB_FRAME_LEN);

    /* 组包 */
    return OMRL_AcpuMsgCombine(pucData, (VOS_UINT16)ulSize);
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuRcvData
 功能描述  : OM逻辑通道的接收函数
 输入参数  : pucData:   需要发送的数据内容
             ulLen: 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2011年10月8日
     修改内容  : Creat Function
   2.日    期   : 2012年8月6日
     修改内容   : ACPU实现主控OM
*****************************************************************************/
VOS_UINT32 OMRL_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT8                           ucChar;
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;

    ulResult = VOS_ERR;

    g_stAcpuPcToUeSucRecord.stTotalData.ulDataLen += ulLen;
    g_stAcpuPcToUeSucRecord.stTotalData.ulNum++;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE(pucData, ulLen, OM_ACPU_RECV_USB);
    /*lint +e40*/

    /* 当发生释放消息出错时停止接收数据 */
    if (0 < g_stAcpuUeToPcErrRecord.usRlsMemErr)
    {
        return VOS_OK;
    }

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(&g_stOmHdlcEntity, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            /*lint -e40*/
            OM_ACPU_DEBUG_TRACE(g_stOmHdlcEntity.pucDecapBuff,
                g_stOmHdlcEntity.ulInfoLen, OM_ACPU_RECV_USB);
            /*lint +e40*/

            g_stAcpuPcToUeSucRecord.stHdlcDecapData.ulDataLen += g_stOmHdlcEntity.ulInfoLen;
            g_stAcpuPcToUeSucRecord.stHdlcDecapData.ulNum++;

            if (VOS_OK != OMRL_AcpuHeadProc(g_stOmHdlcEntity.pucDecapBuff, g_stOmHdlcEntity.ulInfoLen))
            {
                g_stAcpuPcToUeErrRecord.stLostData.ulDataLen += g_stOmHdlcEntity.ulInfoLen;
                g_stAcpuPcToUeErrRecord.stLostData.ulNum++;
            }
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*不是完整分帧,继续HDLC解封装*/
        }
        else
        {
            g_stAcpuPcToUeErrRecord.ulFrameDecapErr++;
        }
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_CBT_LOG)

/*****************************************************************************
 函 数 名  : OMRL_AcpuCBTMsgDispatch
 功能描述  : 将数据包分发出去
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuCBTMsgDispatch(VOS_VOID)
{
    VOS_UINT32                       ulRslt;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE(g_stCBTMsgCombineInfo.pstWholeMsg->aucValue, g_stCBTMsgCombineInfo.pstWholeMsg->ulLength, OM_ACPU_DISPATCH_MSG);
    /*lint +e40*/

    /* CCPU的消息通过ICC通道发送 */
    if (WUEPS_PID_OM == g_stCBTMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        ulRslt = GU_OamSndPcMsgToCcpu(g_stCBTMsgCombineInfo.pstWholeMsg->aucValue, g_stCBTMsgCombineInfo.pstWholeMsg->ulLength);

        g_stCBTAcpuPcToUeSucRecord.stCcpuData.ulDataLen += g_stCBTMsgCombineInfo.pstWholeMsg->ulLength;
        g_stCBTAcpuPcToUeSucRecord.stCcpuData.ulNum++;

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);
    }
    else if (ACPU_PID_OM == g_stCBTMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stCBTAcpuPcToUeSucRecord.stAcpuData.ulDataLen += g_stCBTMsgCombineInfo.pstWholeMsg->ulLength;
        g_stCBTAcpuPcToUeSucRecord.stAcpuData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);
    }
    else if (DSP_PID_HIFI_OM == g_stCBTMsgCombineInfo.pstWholeMsg->ulReceiverPid)
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stCBTAcpuPcToUeSucRecord.stHifiData.ulDataLen += g_stCBTMsgCombineInfo.pstWholeMsg->ulLength;
        g_stCBTAcpuPcToUeSucRecord.stHifiData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);
    }
    else
    {
        /* 其他cpu的消息通过VOS_SendMsg发送 */
        g_stCBTAcpuPcToUeSucRecord.stMcuData.ulDataLen += g_stCBTMsgCombineInfo.pstWholeMsg->ulLength;
        g_stCBTAcpuPcToUeSucRecord.stMcuData.ulNum++;

        ulRslt = VOS_SendMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);
    }

    g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

    if (VOS_OK != ulRslt )
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

/*****************************************************************************
 函 数 名  : OMRL_AcpuCBTMsgCombine
 功能描述  : 对消息 组包并发送给对应CPU OM消息处理模块处理
 输入参数  : pucData:   需要处理的数据内容
             ulDataLen: 数据长度

 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年6月11日
    修改内容   : 新生成函数
  2.日    期   : 2012年8月6日
    修改内容   : 增加将组包后数据根据CPUID分发

*****************************************************************************/
VOS_UINT32 OMRL_AcpuCBTMsgCombine(VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT32                       ulRslt = VOS_OK;/*Get the return value of PS_SEND_MSG.*/
    VOS_UINT8                        ucCurrentSegSn;/*Reserve the current packet's SN.*/
    OM_APP_MSG_SEGMENT_STRU          *pstOmAppSeg;
    APP_OM_GU_MSG_STRU               *pstAppOmMsg;

    /*Check the input parameter's validity.Make sure empty segment can't pass*/
    if ( (VOS_NULL_PTR == pucData) ||
        (usLen <= sizeof(OM_APP_MSG_SEGMENT_STRU)) )
    {
        LogPrint("OMRL_AcpuCBTMsgCombine: The input is wrong.");

        g_stCBTAcpuPcToUeErrRecord.usLenTooShortErr++;

        return VOS_ERR;
    }

    pstOmAppSeg = (OM_APP_MSG_SEGMENT_STRU *)pucData;

    /*Check the input parameter's validity.*/
    if (usLen != ((pstOmAppSeg->usSegLen + 3) & ~0x3))
    {
        LogPrint("OMRL_AcpuCBTMsgCombine: The input length is wrong.");

        g_stCBTAcpuPcToUeErrRecord.usSegLenErr++;

        return VOS_ERR;
    }

    usLen = pstOmAppSeg->usSegLen;

    ucCurrentSegSn = pstOmAppSeg->ucSegSn;

    /*When the MSG packet is new, we need initialize the static variable.*/
    if (1 == ucCurrentSegSn)
    {
        if (VOS_NULL_PTR != g_stCBTMsgCombineInfo.pstWholeMsg)
        {
            VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);
            g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            g_stCBTAcpuPcToUeErrRecord.usPacketLostErr++;
        }

        /*The new MSG packet is coming.*/
        g_stCBTMsgCombineInfo.ucExpectedSegSn = 1;
        g_stCBTMsgCombineInfo.ulMoveLen       = 0;

        if (usLen < (sizeof(APP_OM_GU_MSG_STRU) + OM_APP_MSG_SEGMENT_HEADER_LENGTH))
        {
            LogPrint("OMRL_AcpuCBTMsgCombine: The input parameter is wrong.");

            g_stCBTAcpuPcToUeErrRecord.usMsgLenErr++;

            return VOS_ERR;
        }

        pstAppOmMsg = (APP_OM_GU_MSG_STRU *)(pucData + OM_APP_MSG_SEGMENT_HEADER_LENGTH);

        g_stCBTMsgCombineInfo.ulTotalMsgLen = pstAppOmMsg->usLength + APP_OM_HEADER_LENGTH;

        /* 组包完成后判断是否大于阈值 */
        if (OM_RL_TOTAL_MSG_MAX_LEN < g_stCBTMsgCombineInfo.ulTotalMsgLen)
        {
            g_stCBTAcpuPcToUeErrRecord.usMsgTooLongErr++;

            LogPrint1("OMRL_AcpuCBTMsgCombine: receive first msg pack is too long %d;\r\n",
                        (VOS_INT32)g_stCBTMsgCombineInfo.ulTotalMsgLen);

            /* 底软最大支持保存1024字节的内容，底软没有提供宏，这里直接使用数字 */
            DRV_SYSTEM_ERROR(OAM_PC_LENGTH_TOO_BIG, (VOS_INT)g_stCBTMsgCombineInfo.ulTotalMsgLen, 0, (VOS_CHAR *)pucData, 1024);

            return VOS_ERR;
        }

        /*Allocate the memory space.*/
        g_stCBTMsgCombineInfo.pstWholeMsg = VOS_AllocMsg(ACPU_PID_OM,  g_stCBTMsgCombineInfo.ulTotalMsgLen);
        if (VOS_NULL_PTR == g_stCBTMsgCombineInfo.pstWholeMsg)
        {
            LogPrint("OMRL_AcpuCBTMsgCombine: VOS_AllocMsg fail.");

            g_stCBTAcpuPcToUeErrRecord.usAllocMsg++;

            return VOS_ERR;
        }

        /* 根据CPU ID查找到相应的PID，对于工具下发数据帧，用VOS_OM_HEADER结构中保留字段表示CPUID */
        ulRslt = OMRL_AcpuCpuIdToPid(pstAppOmMsg->ucCpuId, &g_stCBTMsgCombineInfo.pstWholeMsg->ulReceiverPid);
        if (VOS_OK != ulRslt)
        {
            /* 释放消息空间 */
            VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);

            g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            g_stCBTAcpuPcToUeErrRecord.usCpuIdErr++;

            /* 此处错误直接返回，不用记录，函数里面已经记录了CPU ID错误的情况 */
            return VOS_ERR;
        }

        g_stCBTMsgCombineInfo.ucTotalSegNum = pstOmAppSeg->ucSegNum;
    }

    if ( g_stCBTMsgCombineInfo.ucTotalSegNum != pstOmAppSeg->ucSegNum )
    {
        LogPrint("OMRL_AcpuCBTMsgCombine: The length of the packet is biger than the size of allocated memory.");

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);

        g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stCBTAcpuPcToUeErrRecord.usSegNumErr++;

        return VOS_ERR;
    }

    /*The expected MSG pakcet is lost.*/
    if (g_stCBTMsgCombineInfo.ucExpectedSegSn != ucCurrentSegSn)
    {
        /*Print the error info.*/
        LogPrint2("OMRL_AcpuCBTMsgCombine: expected SN is %d, current SN is %d.", g_stCBTMsgCombineInfo.ucExpectedSegSn, ucCurrentSegSn);

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);

        g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stCBTAcpuPcToUeErrRecord.usMsgSnErr++;

        return VOS_ERR;
    }

    /*We make sure that the memory can't be violated.*/
    if (g_stCBTMsgCombineInfo.ulTotalMsgLen < (g_stCBTMsgCombineInfo.ulMoveLen + (usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH)))
    {
        LogPrint("OMRL_AcpuCBTMsgCombine: The length of the packet is biger than the size of allocated memory.\n");

        /* 释放消息空间 */
        VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);

        g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

        g_stCBTAcpuPcToUeErrRecord.usNoMemErr++;

        return VOS_ERR;
    }

    VOS_MemCpy((VOS_UINT8*)(g_stCBTMsgCombineInfo.pstWholeMsg->aucValue) + g_stCBTMsgCombineInfo.ulMoveLen,
               pucData + OM_APP_MSG_SEGMENT_HEADER_LENGTH, usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH);
    g_stCBTMsgCombineInfo.ulMoveLen += usLen - OM_APP_MSG_SEGMENT_HEADER_LENGTH;
    g_stCBTMsgCombineInfo.ucExpectedSegSn++;

    /*If the current MSG packet is an complete packet.*/
    if (g_stCBTMsgCombineInfo.ucTotalSegNum == ucCurrentSegSn)
    {
        /* 组包完成后判断是否大于阈值 */
        if (OM_RL_TOTAL_MSG_MAX_LEN < g_stCBTMsgCombineInfo.ulTotalMsgLen)
        {
            g_stCBTAcpuPcToUeErrRecord.usMsgTooLongErr++;

            /* 释放消息空间 */
            VOS_FreeMsg(ACPU_PID_OM, g_stCBTMsgCombineInfo.pstWholeMsg);

            g_stCBTMsgCombineInfo.pstWholeMsg = VOS_NULL_PTR;

            return VOS_ERR;
        }

        /*It will send the MSG to OM module.*/
        ulRslt = OMRL_AcpuCBTMsgDispatch();

        return ulRslt;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuCBTHeadProc
 功能描述  : 实现消息组包及分发
 输入参数  : pucData:   需要处理的数据内容
             ulSize: 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年8月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuCBTHeadProc(VOS_UINT8 *pucData, VOS_UINT32 ulSize)
{
    VOS_UINT32          ulRslt;
    VOS_UINT32          ulValue;
    VOS_UINT32          ulTmpLen;
    APP_OM_MSG_EX_STRU  stOmMsg;

    if ((OM_RL_DATATYPE_LEN + OM_USB_FRAME_LEN) >= ulSize)
    {
        /* 打印错误 */
        LogPrint("OMRL_AcpuCBTHeadProc: The data length is error.");
        g_stCBTAcpuPcToUeErrRecord.usPacketLenErr++;
        return VOS_ERR;
    }

    VOS_MemCpy(&ulValue, (pucData+OM_RL_DATATYPE_LEN), sizeof(VOS_UINT32));

    /* 区分普通消息和链路消息 */
    /* 数据包跳过一个字节判断是不是0xaaaa5555 */
    if (OM_USB_FRAME_HEAD != ulValue)
    {
        /* 此分支中为链路消息 */
        ulTmpLen =  ulSize - sizeof(OM_APP_MSG_SEGMENT_STRU);

        /* 链路消息长度判断 */
        if (sizeof(APP_OM_MSG_EX_STRU) != ulTmpLen)
        {
            g_stCBTAcpuPcToUeErrRecord.usLinkDataLenErr++;

            return VOS_ERR;
        }

        VOS_MemCpy((VOS_UINT8 *)(&stOmMsg), (pucData + sizeof(OM_APP_MSG_SEGMENT_STRU)), sizeof(APP_OM_MSG_EX_STRU));

        if (APP_OM_ESTABLISH_REQ == stOmMsg.usPrimId)
        {
            g_ulCBTEstablishStatus = OM_CBT_LOG_ENABLE_FLAG;   
        }
        else if (APP_OM_RELEASE_REQ == stOmMsg.usPrimId )
        {
            g_ulCBTEstablishStatus = VOS_NULL;
        }
        else
        {
            /* blank */
        }
        
        /* 跳过四字节sn header */
        ulRslt = OMRL_AcpuSendMsg(pucData + sizeof(OM_APP_MSG_SEGMENT_STRU),
                       ulTmpLen, ACPU_PID_OM, ACPU_PID_OM);

        g_stCBTAcpuPcToUeSucRecord.stLinkData.ulDataLen += ulTmpLen;
        g_stCBTAcpuPcToUeSucRecord.stLinkData.ulNum++;

        return ulRslt;
    }

    /* 收到普通消息时先判断当前链路状态 */
    if (OM_STATE_IDLE == g_ulAcpuOMSwitchOnOff)
    {
         g_stCBTAcpuPcToUeErrRecord.usLinkStatusErr++;
         return VOS_ERR;
    }


    /* 普通消息，判断datatype字段是不是GU数据 */
    if (OM_RL_DATATYPE_GU != *pucData)
    {
         g_stCBTAcpuPcToUeErrRecord.usDatatypeErr++;
         return VOS_ERR;
    }

    VOS_MemCpy(&ulValue, (pucData + ulSize - OM_USB_TAIL_LEN), sizeof(VOS_UINT32));

    /* 判断数据包尾是不是0x5555aaaa */
    if (OM_USB_FRAME_TAIL != ulValue)
    {
        /* 记录错误 */
        g_stCBTAcpuPcToUeErrRecord.usDataHeadErr++;
        return VOS_ERR;
    }

    /* 数据指针和长度更新*/
    pucData += (OM_RL_DATATYPE_LEN + OM_USB_HEAD_LEN);
    ulSize  -= (OM_RL_DATATYPE_LEN + OM_USB_FRAME_LEN);

    /* 组包 */
    return OMRL_AcpuCBTMsgCombine(pucData, (VOS_UINT16)ulSize);
}


/*****************************************************************************
 函 数 名  : OMRL_AcpuRcvCBTData
 功能描述  : OM逻辑通道的接收函数
 输入参数  : ucDevIndex : VCOM 通道编号
             pucData    : 需要发送的数据内容
             ulLen      : 数据长度
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2011年10月8日
     修改内容  : Creat Function
   2.日    期   : 2014年1月25日
     修改内容   : GU支持CBT抓取LOG
*****************************************************************************/
VOS_INT OMRL_AcpuRcvCBTData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT8                           ucChar;
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult;
    
    if(ucDevIndex != APP_VCOM_DEV_INDEX_CBT)
    {
        return VOS_ERR;
    }

    if ((VOS_NULL_PTR == pucData) || (0 == ulLen))
    {
        return VOS_ERR;
    }

#if (VOS_LINUX == VOS_OS_VER)
    down(&g_stOmRxCBTBuffSem);
#endif

    if ( OM_CBT_LOG_ENABLE_FLAG != g_ulCBTLogEnable )
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxCBTBuffSem);
#endif
        return VOS_OK;
    }

    ulResult = VOS_ERR;

    g_stCBTAcpuPcToUeSucRecord.stTotalData.ulDataLen += ulLen;
    g_stCBTAcpuPcToUeSucRecord.stTotalData.ulNum++;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE(pucData, ulLen, OM_ACPU_RECV_CBT);
    /*lint +e40*/

    /* 当发生释放消息出错时停止接收数据 这里是异常保护不需要更换全局变量用主通道的变量 */
    if (0 < g_stAcpuUeToPcErrRecord.usRlsMemErr)
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxCBTBuffSem);
#endif
        return VOS_OK;
    }

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(&g_stCBTHdlcEntity, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            /*lint -e40*/
            OM_ACPU_DEBUG_TRACE(g_stCBTHdlcEntity.pucDecapBuff,
                g_stCBTHdlcEntity.ulInfoLen, OM_ACPU_RECV_CBT);
            /*lint +e40*/

            g_stCBTAcpuPcToUeSucRecord.stHdlcDecapData.ulDataLen += g_stCBTHdlcEntity.ulInfoLen;
            g_stCBTAcpuPcToUeSucRecord.stHdlcDecapData.ulNum++;

            if (VOS_OK != OMRL_AcpuCBTHeadProc(g_stCBTHdlcEntity.pucDecapBuff, g_stCBTHdlcEntity.ulInfoLen))
            {
                g_stCBTAcpuPcToUeErrRecord.stLostData.ulDataLen += g_stCBTHdlcEntity.ulInfoLen;
                g_stCBTAcpuPcToUeErrRecord.stLostData.ulNum++;
            }
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*不是完整分帧,继续HDLC解封装*/
        }
        else
        {
            g_stCBTAcpuPcToUeErrRecord.ulFrameDecapErr++;
        }
    }

#if (VOS_LINUX == VOS_OS_VER)
    up(&g_stOmRxCBTBuffSem);
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_JudgeCbtMsg
 功能描述  : 对Func Type进行判断，是否是CBT相关消息
 输入参数  : ucFuncType:   Func Type

 输出参数  : 无
 返 回 值  : VOS_TRUE/VOS_FALSE
 修改历史  :
   2.日    期   : 2014年1月23日
     修改内容   : CBT抓取LOG新增
*****************************************************************************/
VOS_BOOL OMRL_JudgeCbtMsg(VOS_UINT8   ucFuncType)
{
    if ( (OM_FS_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_WRF_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_GRF_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_QUERY_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_NV_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_NOSIG_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
                 ||(OM_CBT_TRANS_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS)) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : OMRL_EncCBTData
 功能描述  : 将CBT相关消息经HDLC封装后调NAS接口发走
 输入参数  : pstNVHdlcEntity 待封装码流相关信息

 输出参数  : 无
 返 回 值  : VOS_VOID
 修改历史  :
   2.日    期   : 2014年1月23日
     修改内容   : CBT抓取LOG新增
*****************************************************************************/
VOS_VOID OMRL_EncCBTData(OM_HDLC_STRU *pstNVHdlcEntity)
{
    VOS_UINT16                         usHdlcEncLen;

    g_stVComCBTDebugInfo.ulVCOMHdlcEnNum++;
    
    if ( VOS_OK != Om_HdlcEncap(pstNVHdlcEntity->pucDecapBuff,
                                (VOS_UINT16)pstNVHdlcEntity->ulInfoLen,
                                g_pucCBTHdlcEncBuf,
                                (2*OM_HDLC_BUF_MAX_LEN), &usHdlcEncLen) )
    {
        g_stVComCBTDebugInfo.ulVCOMHdlcEnFailNum++;
        return;
    }

    g_stVComCBTDebugInfo.ulVCOMSendNum++;
    g_stVComCBTDebugInfo.ulVCOMSendLen += usHdlcEncLen;

    if ( OM_CBT_LOG_ENABLE_FLAG != g_ulCBTEstablishStatus )
    {
        return;
    }

    if ( VOS_OK != APP_VCOM_Send(APP_VCOM_DEV_INDEX_CBT, g_pucCBTHdlcEncBuf, usHdlcEncLen) )
    {
        g_stVComCBTDebugInfo.ulVCOMSendErrNum++;
        g_stVComCBTDebugInfo.ulVCOMSendErrLen += usHdlcEncLen;

    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : OMRL_AcpuRecordUeToAPPNvInfo
 功能描述  : 记录UE和校准工具的数据交互
 输入参数  : ucFuncType : func type
             pucData    : 交互数据
             ulLen      : 数据长度
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2014年2月8日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OMRL_AcpuRecordUeToAPPNvInfo(VOS_UINT8 ucFuncType, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    if ( (OM_WRF_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_GRF_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_QUERY_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS))
         ||(OM_NV_FUNC == ((ucFuncType) & OM_FUNCID_VALUE_BITS)))
    {
        g_pstRecordOmToApp[g_ulNvOmToAppCount].ulSlice = VOS_GetSlice();
        g_pstRecordOmToApp[g_ulNvOmToAppCount].ulFlag  = 0xaaaaaaaa;

        if (ulLen > NV_MNTN_SAVE_MAX_MSG_LEN)
        {
            ulLen = NV_MNTN_SAVE_MAX_MSG_LEN;
        }

        VOS_MemCpy(g_pstRecordOmToApp[g_ulNvOmToAppCount].aucVaule, pucData, ulLen);

        g_ulNvOmToAppCount++;

        if (SAVE_MAX_SEND_INFO == g_ulNvOmToAppCount)
        {
             g_ulNvOmToAppCount = 0;
        }
    }
    return;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuHdlcData
 功能描述  : 记录和校准工具的数据交互
 输入参数  : pucData -- 发给USB的数据
             ulLen -- 数据长度
 输出参数  : none
 返 回 值  : none
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2013年9月12日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OMRL_AcpuHdlcData(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UINT8                           ucChar;
    VOS_UINT32                          i;
    VOS_UINT32                          ulResult = VOS_ERR;
    OM_APP_MSG_EX_STRU                 *pstOmToAppMsg;
    VOS_UINT8                          *pucTem;
    VOS_UINT8                           ucSegSn;

    if ( OM_CBT_LOG_ENABLE_FLAG != g_ulCBTLogEnable )
    {
        return;
    }

    for( i = 0; i < ulLen; i++ )
    {
        ucChar = (VOS_UINT8)pucData[i];

        ulResult = Om_HdlcDecap(&g_stNVHdlcEntity, ucChar);

        if ( HDLC_SUCC == ulResult )
        {
            /* 判断码流 */
            pucTem = (VOS_UINT8*)g_stNVHdlcEntity.pucDecapBuff;
            ucSegSn = *(pucTem + OM_RL_DATATYPE_LEN + offsetof(OM_APP_MSG_SEG_EX_STRU, stMsgSeg.ucSegSn));
            pstOmToAppMsg = (OM_APP_MSG_EX_STRU*)(pucTem + OM_RL_DATATYPE_LEN + sizeof(OM_APP_MSG_SEG_EX_STRU));

#if (FEATURE_ON == FEATURE_CBT_LOG)
            /* FuncType只存在于第一帧数据中 */
            if (1 != ucSegSn )
            {
                if  ( OM_CBT_MSG == g_ulCBTStatus )
                {
                     OMRL_EncCBTData(&g_stNVHdlcEntity);
                }

                continue;
            }

            if ( VOS_TRUE == OMRL_JudgeCbtMsg(pstOmToAppMsg->ucFuncType) )
            {
                 g_ulCBTStatus = OM_CBT_MSG;

                 OMRL_EncCBTData(&g_stNVHdlcEntity);
            }
            else
            {
                g_ulCBTStatus = OM_NOT_CBT_MSG;
            }
#else
            if (1 != ucSegSn )
            {
                continue;
            }

#endif
            OMRL_AcpuRecordUeToAPPNvInfo(pstOmToAppMsg->ucFuncType, pucData, ulLen);
        }
        else if (HDLC_NOT_HDLC_FRAME == ulResult)
        {
            /*不是完整分帧,继续HDLC解封装*/
        }
        else
        {
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuHdlcInit
 功能描述  : ACPU初始化HDLC
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2009年3月28日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuHdlcInit(VOS_VOID)
{
    g_stOmHdlcEntity.pucDecapBuff =
        (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_OM, STATIC_MEM_PT, OM_HDLC_BUF_MAX_LEN);

    if (VOS_NULL_PTR == g_stOmHdlcEntity.pucDecapBuff)
    {
        LogPrint("\r\nOMRL_AcpuHdlcInit:Alloc Memory Failed!\r\n");

        g_stOmHdlcEntity.ulDecapBuffSize = 0;

        return VOS_ERR;
    }

    Om_HdlcInit(&g_stOmHdlcEntity);

    g_stOmHdlcEntity.ulDecapBuffSize = OM_HDLC_BUF_MAX_LEN;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuNVHdlcInit
 功能描述  : ACPU初始化HDLC
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_ERR/VOS_OK
 修改历史  :
   1.日    期  : 2013年9月9日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuNVHdlcInit(VOS_VOID)
{
    OM_SW_VER_FLAG_STRU         stCustomVersion;

#if (FEATURE_ON == FEATURE_CBT_LOG)    
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;
    NV_OM_CBT_LOG_ENABLE_STRU   stNVCBTLogEnable;
#endif    

    if ( VOS_OK != NV_Read(en_NV_Item_SW_VERSION_FLAG, &stCustomVersion, sizeof(stCustomVersion)) )
    {
        stCustomVersion.ulNvSwVerFlag = VOS_TRUE;
    }

    /* 如果ulCustomVersion == VOS_TRUE表示不是烧片版本，则直接返回，不用分配记录NV可维可测的资源 */
    if ( VOS_TRUE == stCustomVersion.ulNvSwVerFlag)
    {
        return VOS_OK;
    }

    g_pstRecordOmToApp = (OM_NV_MNTN_RECORD_STRU *)VOS_MemAlloc(ACPU_PID_OM,
                         STATIC_MEM_PT, SAVE_MAX_SEND_INFO*sizeof(OM_NV_MNTN_RECORD_STRU));

    if (VOS_NULL_PTR == g_pstRecordOmToApp)
    {
        LogPrint("\r\nOMRL_AcpuNVHdlcInit:Alloc Memory Failed!\r\n");

        return VOS_ERR;
    }

    g_pstRecordAppToOm = (OM_NV_MNTN_RECORD_STRU *)VOS_MemAlloc(ACPU_PID_OM,
                   STATIC_MEM_PT, SAVE_MAX_SEND_INFO*sizeof(OM_NV_MNTN_RECORD_STRU));

    if (VOS_NULL_PTR == g_pstRecordAppToOm)
    {
        LogPrint("\r\nOMRL_AcpuNVHdlcInit:Alloc Memory Failed!\r\n");

        return VOS_ERR;
    }

#if (FEATURE_ON == FEATURE_CBT_LOG)
    /* 读取OM的物理输出通道 */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_OK;
    }

    stPortCfg.enPortNum += CPM_APP_PORT;
    if ( CPM_VCOM_PORT != stPortCfg.enPortNum )
    {
        return VOS_OK;
    }

    /* 读取新增的NV ，需要新增的使能 Nv 也是打开的 否则直接退出 */
    if (NV_OK != NV_Read(en_NV_Item_CBT_LOG_ENABLE, &stNVCBTLogEnable, sizeof(NV_OM_CBT_LOG_ENABLE_STRU)))
    {
        return VOS_OK;
    }

    if (VOS_TRUE != stNVCBTLogEnable.bCBTLogEnable)
    {
        return VOS_OK;
    }
#endif

    g_ulCBTLogEnable = OM_CBT_LOG_ENABLE_FLAG;

    g_stNVHdlcEntity.pucDecapBuff = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_OM, STATIC_MEM_PT, 2*OM_HDLC_BUF_MAX_LEN);

    if (VOS_NULL_PTR == g_stNVHdlcEntity.pucDecapBuff)
    {
        LogPrint("\r\nOMRL_AcpuNVHdlcInit:Alloc Memory Failed!\r\n");

        g_stNVHdlcEntity.ulDecapBuffSize = 0;

        return VOS_ERR;
    }

    Om_HdlcInit(&g_stNVHdlcEntity);

    g_stNVHdlcEntity.ulDecapBuffSize = 2*OM_HDLC_BUF_MAX_LEN;

#if (FEATURE_ON == FEATURE_CBT_LOG)
    g_stCBTHdlcEntity.pucDecapBuff = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_OM, STATIC_MEM_PT, OM_HDLC_BUF_MAX_LEN);

    if (VOS_NULL_PTR == g_stCBTHdlcEntity.pucDecapBuff)
    {
        LogPrint("\r\n OMRL_AcpuNVHdlcInit:Alloc Memory Failed!\r\n");

        g_stCBTHdlcEntity.ulDecapBuffSize = 0;

        return VOS_ERR;
    }

    Om_HdlcInit(&g_stCBTHdlcEntity);

    g_stCBTHdlcEntity.ulDecapBuffSize = OM_HDLC_BUF_MAX_LEN;

    g_pucCBTHdlcEncBuf = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_OM, STATIC_MEM_PT, 2*OM_HDLC_BUF_MAX_LEN);
    if (VOS_NULL_PTR == g_pucCBTHdlcEncBuf)
    {
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OMRL_AcpuConnectInfoReportEvent
 Description     :
 Input           : pstConnectInfo - 指向消息地址
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2014-04-09
    Modification : Created function
 *****************************************************************************/
VOS_VOID OMRL_AcpuConnectInfoReportEvent(OM_CONNECT_INFO_CNF_STRU *pstConnectInfo)
{
    OM_CONNECT_INFO_EVENT_STRU         *pstAppEvent;
    VOS_UINT32                          ulEventLen;

    /* 构造EVENT事件 */
    ulEventLen = sizeof(OM_CONNECT_INFO_EVENT_STRU);

    pstAppEvent = (OM_CONNECT_INFO_EVENT_STRU *)VOS_MemAlloc(ACPU_PID_OM, DYNAMIC_MEM_PT, ulEventLen);

    if (VOS_NULL_PTR == pstAppEvent)
    {
        return;
    }

    pstAppEvent->stAppHeader.ucFuncType = OM_EVENT_FUNC;
    pstAppEvent->stAppHeader.usLength   = (VOS_UINT16)(ulEventLen - VOS_OM_HEADER_LEN);
    pstAppEvent->ulModuleId             = ACPU_PID_OM;
    pstAppEvent->usEventId              = OAM_EVENT_CONNECT_INFO;
    pstAppEvent->ulOMSwitchOnOff        = pstConnectInfo->ulOMSwitchOnOff;

    OM_AcpuAddSNTime(&(pstAppEvent->stAppHeader.ulSn), &(pstAppEvent->stAppHeader.ulTimeStamp));

    VOS_MemCpy(&pstAppEvent->stUe2PcErrInfo, &pstConnectInfo->stUe2PcErrInfo, sizeof(OM_UE_PC_FAIL_STRU));

    VOS_MemCpy(pstAppEvent->aucPidCfg, pstConnectInfo->aucPidCfg, sizeof(VOS_UINT32) * (VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND));

    BSP_SOCP_GetEncSrcReg(pstAppEvent->aucReg, OM_MAX_SOCP_REG_NUM);

    if (VOS_OK != OM_AcpuSendData((OM_RSP_PACKET_STRU *)pstAppEvent, (VOS_UINT16)ulEventLen))
    {

    }

    /* 释放消息内容空间 */
    VOS_MemFree(ACPU_PID_OM, pstAppEvent);

    return;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuReportEvent
 功能描述  : 通过调用OM_Event上报环形buffer满时的CPU情况
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史  : j00174725
             2012-04-16
*****************************************************************************/
VOS_UINT32 OMRL_AcpuReportEvent(VOS_VOID)
{
    PS_OM_EVENT_IND_STRU    *pstEventInd;
    VOS_UINT32               ulEventLenth;
    VOS_UINT32               ulTemp = 0x5a5a5a5a;
    VOS_UINT32               ulIndex;
    VOS_UINT32               ulSendLen;
    OM_SEND_DEBUG_INFO_STRU  astAcpuDebuginfoTab2[3];
    VOS_UINT32               ulAddr;
    VOS_UINT16               usDebugEventID;

    /* 存放A核调测信息的 大小和地址,分包上报消息 */
    OM_SEND_DEBUG_INFO_STRU  astAcpuDbuginfoTab1[] = {
        {sizeof(g_stAcpuPcToUeSucRecord),                 (VOS_UINT8*)&g_stAcpuPcToUeSucRecord},
        {sizeof(g_stAcpuPcToUeErrRecord),                 (VOS_UINT8*)&g_stAcpuPcToUeErrRecord},
        {sizeof(g_stAcpuUeToPcSucRecord),                 (VOS_UINT8*)&g_stAcpuUeToPcSucRecord},
        {sizeof(g_stAcpuUeToPcErrRecord),                 (VOS_UINT8*)&g_stAcpuUeToPcErrRecord},
        {sizeof(g_stAcpuDebugInfo),                       (VOS_UINT8*)&g_stAcpuDebugInfo      },
        {sizeof(g_stOmSDDebugInfo),                       (VOS_UINT8*)&g_stOmSDDebugInfo      },
        {sizeof(g_stVComDebugInfo),                       (VOS_UINT8*)&g_stVComDebugInfo      },
        {sizeof(g_astAcpuRecordInfo),                     (VOS_UINT8*)g_astAcpuRecordInfo    },
        {sizeof(g_ulAcpuOMSwitchOnOff),                   (VOS_UINT8*)&g_ulAcpuOMSwitchOnOff  },
    };

    astAcpuDebuginfoTab2[0].pucAddr = (VOS_UINT8*)SCM_GetDebugLogInfo();
    astAcpuDebuginfoTab2[0].ulLenth = SCM_GetDebugLogInfoLen();

    astAcpuDebuginfoTab2[1].pucAddr = (VOS_UINT8*)SOCP_GetDebugLogInfo(OM_GET_SOCP_STATUS);
    astAcpuDebuginfoTab2[1].ulLenth = SOCP_GetDebugLogInfoLen(OM_GET_SOCP_STATUS);

    astAcpuDebuginfoTab2[2].pucAddr = (VOS_UINT8*)SOCP_GetDebugLogInfo(OM_GET_SOCP_DEBUG_INFO);
    astAcpuDebuginfoTab2[2].ulLenth = SOCP_GetDebugLogInfoLen(OM_GET_SOCP_DEBUG_INFO);

    /* ---------------第一包数据 astAcpuDbuginfoTab1[]  begin----------- */

    ulEventLenth = (sizeof(PS_OM_EVENT_IND_STRU)-(4 * sizeof(VOS_UINT8)));
    for (ulIndex=0; ulIndex<(sizeof(astAcpuDbuginfoTab1)/sizeof(astAcpuDbuginfoTab1[0])); ulIndex ++)
    {
        ulEventLenth += astAcpuDbuginfoTab1[ulIndex].ulLenth;
    }

    /* 加上分隔符号长度 */
    ulEventLenth += (ulIndex - 1) * sizeof(VOS_UINT32);
    pstEventInd = (PS_OM_EVENT_IND_STRU *)VOS_MemAlloc(ACPU_PID_OM, DYNAMIC_MEM_PT, ulEventLenth);
    if (VOS_NULL_PTR == pstEventInd)
    {
        LogPrint("OMRL_AcpuReportEvent:Alloc Memory Failed!\n");
        return VOS_ERR;
    }

    pstEventInd->ulLength   = ulEventLenth;
    pstEventInd->usEventId  = OAM_DEGUG_EVENT_ID1;
    pstEventInd->ulModuleId = ACPU_PID_OM;

    /*lint -e419 -e416 */
    /* pc侧到ue侧时正常接收数据信息 */
    VOS_MemCpy((VOS_UINT8 *)pstEventInd->aucData,
        (VOS_UINT8*)&g_stAcpuPcToUeSucRecord,
        sizeof(OM_ACPU_PC_UE_SUC_STRU));
     /*lint +e419 +e416 */

    ulEventLenth = 0;
    for (ulIndex=1;ulIndex<(sizeof(astAcpuDbuginfoTab1)/sizeof(astAcpuDbuginfoTab1[0])); ulIndex ++)
    {
        /*lint -e419 -e416 */
        /* 加上分隔符号 */
        ulEventLenth += astAcpuDbuginfoTab1[ulIndex-1].ulLenth;
        VOS_MemCpy((VOS_UINT8 *)pstEventInd->aucData + ulEventLenth,
                   (VOS_UINT8 *)&ulTemp, sizeof(VOS_UINT32));

        ulEventLenth += sizeof(VOS_UINT32);
        VOS_MemCpy((VOS_UINT8 *)pstEventInd->aucData + ulEventLenth,
            astAcpuDbuginfoTab1[ulIndex].pucAddr, astAcpuDbuginfoTab1[ulIndex].ulLenth);
         /*lint +e419 +e416 */
    }
    /*lint +e419 +e416 */

    if (VOS_OK != OM_AcpuEvent(pstEventInd))
    {
        PS_LOG(ACPU_PID_OM, VOS_NULL, PS_PRINT_WARNING, "OMRL_AcpuReportEvent: send event fail.");
    }
    /* 释放消息内容空间 */
    VOS_MemFree(ACPU_PID_OM, pstEventInd);

    /* ---------------第一包数据 astAcpuDbuginfoTab1[]  end----------- */

    /* ---------------astAcpuDbuginfoTab2[] 每项数据较大拆包发送，每包最大发送2k----------- */
    /* Event Id */
    usDebugEventID  = OAM_DEGUG_EVENT_ID2;
    /* 一次性申请 2k 空间，最后释放 */
    pstEventInd = (PS_OM_EVENT_IND_STRU *)VOS_MemAlloc(ACPU_PID_OM, DYNAMIC_MEM_PT,
                                          OM_SEND_DEBUG_INFO_MAX_LEN + sizeof(PS_OM_EVENT_IND_STRU)-(4 * sizeof(VOS_UINT8)));
    if (VOS_NULL_PTR == pstEventInd)
    {
        LogPrint("OMRL_AcpuReportEvent:Alloc Memory Failed!\n");
        return VOS_ERR;
    }

    /* 数据拆分发送 */
    for(ulIndex =0; ulIndex<(sizeof(astAcpuDebuginfoTab2)/sizeof(astAcpuDebuginfoTab2[0])); ulIndex++)
    {
        /* 分配内容空间 最大为 2k*/
        ulSendLen = 0;

        while(ulSendLen < astAcpuDebuginfoTab2[ulIndex].ulLenth)
        {
            if((astAcpuDebuginfoTab2[ulIndex].ulLenth - ulSendLen) > OM_SEND_DEBUG_INFO_MAX_LEN)
            {
                ulEventLenth = OM_SEND_DEBUG_INFO_MAX_LEN;
            }
            else
            {
                ulEventLenth = astAcpuDebuginfoTab2[ulIndex].ulLenth - ulSendLen;
            }

            pstEventInd->ulLength   = ulEventLenth;
            pstEventInd->usEventId  = usDebugEventID++;
            pstEventInd->ulModuleId = ACPU_PID_OM;

            /* make pclint happy  begin */
            ulAddr = (VOS_UINT32)pstEventInd->aucData;
            VOS_MemCpy((VOS_UINT8 *)ulAddr, astAcpuDebuginfoTab2[ulIndex].pucAddr + ulSendLen, ulEventLenth);
            /* make pclint happy  end */

            ulSendLen += ulEventLenth;

            if (VOS_OK != OM_AcpuEvent(pstEventInd))
            {
                PS_LOG(ACPU_PID_OM, VOS_NULL, PS_PRINT_WARNING, "OMRL_AcpuReportEvent: send event fail.");
            }
        }
    }

    /* 释放消息内容空间 */
    VOS_MemFree(ACPU_PID_OM, pstEventInd);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuReleaseSocpData
 功能描述  : 释放OM已发送数据内存
 输入参数  : VOS_VOID

 输出参数  : 无

 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 OMRL_AcpuReleaseSocpData(VOS_VOID)
{
    VOS_UINT32          ulDataAddr;
    VOS_UINT32          ulDataLen;
    VOS_UINT8           *pucRealAddr;

#if 0

    VOS_BOOL            bLoopFlag = VOS_TRUE;

    /* 为了测试充分，这里先按一个一个RD释放 */
    do
    {
        /* 从SCM获得已发送消息总长度 */
        if (VOS_OK != SCM_RlsSrcRDFirst(SOCP_CODER_SRC_GU_OM1, &ulDataAddr, &ulDataLen))
        {
            g_stAcpuUeToPcErrRecord.usRlsRdErr++;

            return VOS_ERR;
        }

        /* 已经没有RD */
        if ((0 == ulDataAddr) || (0 == ulDataLen))
        {
            break;
        }

        g_stAcpuUeToPcSucRecord.stRealRlsData.ulDataLen += ulDataLen;
        g_stAcpuUeToPcSucRecord.stRealRlsData.ulNum++;

        pucRealAddr = (VOS_UINT8*)OM_AddrRealToVirt(&g_stAcpuOmBufCtrl, (VOS_UINT8*)ulDataAddr);

        if (VOS_NULL_PTR == pucRealAddr)
        {
            g_stAcpuUeToPcErrRecord.usRlsAddrErr++;

            return VOS_ERR;
        }

        /* 释放OM缓冲区内存 */
        if (VOS_OK != OM_ReleaseTraceMem(&g_stAcpuOmBufCtrl, pucRealAddr, (VOS_INT32)ulDataLen))
        {
            g_stAcpuUeToPcErrRecord.usRlsMemErr++;

            return VOS_ERR;
        }

    }while(bLoopFlag);

#else
    /* 清空所有已发送RD */
    if (VOS_OK != SCM_RlsSrcRDAll(SOCP_CODER_SRC_GU_OM1, &ulDataAddr, &ulDataLen))
    {
        g_stAcpuUeToPcErrRecord.usRlsRdErr++;

        return VOS_ERR;
    }

    /* 已经没有RD */
    if ((0 == ulDataAddr) || (0 == ulDataLen))
    {
        return VOS_OK;
    }

    g_stAcpuUeToPcSucRecord.stRealRlsData.ulDataLen += ulDataLen;
    g_stAcpuUeToPcSucRecord.stRealRlsData.ulNum++;

    pucRealAddr = (VOS_UINT8*)OM_AddrRealToVirt(&g_stAcpuOmBufCtrl, (VOS_UINT8*)ulDataAddr);

    if (VOS_NULL_PTR == pucRealAddr)
    {
        g_stAcpuUeToPcErrRecord.usRlsAddrErr++;

        return VOS_ERR;
    }

    /* 根据已发送RD总长度释放内存 */
    if (VOS_OK != OM_ReleaseTraceMem(&g_stAcpuOmBufCtrl, pucRealAddr, (VOS_INT32)ulDataLen))
    {
        g_stAcpuUeToPcErrRecord.usRlsMemErr++;

        g_ulAcpuOMSwitchOnOff = OM_STATE_IDLE;

        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuSendSocpData
 功能描述  : 将发送数据挂接到SOCP.
 输入参数  : pucHead   : 数据分包头指针
             ulHeadLen : 数据分包头长度
             pucData   : 数据体指针
             ulDataLen : 数据体长度

 输出参数  : 无

 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 OMRL_AcpuSendSocpData(VOS_UINT8 *pucHead, VOS_UINT32 ulHeadLen,
                            VOS_UINT8 *pucData, VOS_UINT32 ulDataLen)
{
    VOS_UINT8                          *pucMemAddr;
    VOS_INT32                           lUsedBytes;
    VOS_UINT8                          *pucRealMemAddr;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE(pucHead, ulHeadLen, OM_ACPU_SEND_SOCP);
    OM_ACPU_DEBUG_TRACE(pucData, ulDataLen, OM_ACPU_SEND_SOCP);
    /*lint +e40*/

    pucMemAddr = (VOS_UINT8*)OM_AllocTraceMem(&g_stAcpuOmBufCtrl, (VOS_INT32)(ulHeadLen + ulDataLen + sizeof(VOS_UINT32)));

    if (VOS_NULL_PTR == pucMemAddr)
    {
        g_stAcpuUeToPcErrRecord.usNoMemErr++;

        return VOS_ERR;
    }

    /* 拷贝数据头 */
    VOS_MemCpy(pucMemAddr, pucHead, ulHeadLen);

    /* 拷贝数据内容 */
    VOS_MemCpy(pucMemAddr + ulHeadLen, pucData, ulDataLen);

    /* 填写桢尾 */
    *(VOS_UINT32*)(pucMemAddr + ulHeadLen + ulDataLen) = OM_USB_FRAME_TAIL;

    VOS_FlushCpuWriteBuf();

    pucRealMemAddr = (VOS_UINT8*)OM_AddrVirtToReal(&g_stAcpuOmBufCtrl, pucMemAddr);

    if (VOS_NULL_PTR == pucRealMemAddr)
    {
        g_stAcpuUeToPcErrRecord.usSendAddrErr++;

        return VOS_ERR;
    }

    /* 调用SCM提供的接口将数据发送给SOCP */
    if (VOS_OK != SCM_SendCoderSrc(SOCP_CODER_SRC_GU_OM1, pucRealMemAddr, ulHeadLen + ulDataLen + sizeof(VOS_UINT32)))
    {
        g_stAcpuUeToPcErrRecord.usSendSocpDataErr++;

        return VOS_ERR;
    }

    g_stAcpuUeToPcSucRecord.stRealSendData.ulDataLen += (ulHeadLen + ulDataLen + sizeof(VOS_UINT32));
    g_stAcpuUeToPcSucRecord.stRealSendData.ulNum++;

    lUsedBytes = OM_TraceMemNBytes(&g_stAcpuOmBufCtrl);

    if (g_stAcpuUeToPcSucRecord.ulMaxUsedBufSize < (VOS_UINT32)lUsedBytes)
    {
        g_stAcpuUeToPcSucRecord.ulMaxUsedBufSize = (VOS_UINT32)lUsedBytes;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuIsBDEnough
 功能描述  : 判断剩余BD是否满足.
 输入参数  : ucMsgCnt -- 发送消息分包个数

 输出参数  : 无

 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年07月31日
    修改内容   : V900R001项目新增函数

*****************************************************************************/
VOS_UINT32 OMRL_AcpuIsBDEnough(VOS_UINT8 ucMsgCnt)
{
    VOS_UINT32                          ulFreeBdNum = 0;

    /* 获取OM源通道剩余BD个数 */
    if (VOS_OK != SCM_GetBDFreeNum(SOCP_CODER_SRC_GU_OM1, &ulFreeBdNum))
    {
        g_stAcpuUeToPcErrRecord.usGetBDErr++;

        return VOS_ERR;
    }

    /* 判断剩余BD是否满足分包个数 */
    if (ucMsgCnt > ulFreeBdNum)
    {
        g_stAcpuUeToPcErrRecord.usBDLackErr++;

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_ProcessSendData
 功能描述  : 将可维可测数据发送的SOCP模块
 输入参数  : pucMsg    -- 指向发送数据的指针
             usMsgLen  -- 发送数据的长度
             ucMsgCnt  -- 待发送数据包个数
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2009年3月28日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 OMRL_AcpuProcessSendData(VOS_UINT8 *pucMsg, VOS_UINT8 ucMsgCnt, VOS_UINT16 usMsgLen)
{
    VOS_UINT8                           ucCurSegNum = 1; /*当前段序号*/
    VOS_UINT32                          ulTempAddress;
    VOS_BOOL                            bIsHead     = VOS_FALSE;
    OM_APP_TRACE_STRU                  *pstAppTrace;

    pstAppTrace = (OM_APP_TRACE_STRU*)pucMsg;

    ulTempAddress = (VOS_UINT32)pucMsg;

    if ((OM_TRACE_FUNC == pstAppTrace->stAppHeader.ucFuncType)
        &&(OM_APP_TRACE_IND == pstAppTrace->usPrimId))
    {
        ulTempAddress = *(VOS_UINT32*)(pstAppTrace->aucPara);
        VOS_MemCpy(g_pstAcpuSegMsgEx + 1, pucMsg, OM_APP_TRACE_LEN);
        bIsHead = VOS_TRUE;
    }

    /* 填充SOCP头中的RTC值 */
    g_pstAcpuSegMsgEx->stSocpHdr.ulRTC = (VOS_UINT32)DRV_GET_RTC_VALUE();
    g_pstAcpuSegMsgEx->stMsgSeg.ucSegNum = ucMsgCnt;
    g_pstAcpuSegMsgEx->stMsgSeg.usSegLen = OM_APP_SPLIT_MSG_LEN;

    /* 大于最大分包大小的数据，按照最大分包大小进行数据发送的处理 */
    for (ucCurSegNum = 1; ucCurSegNum < ucMsgCnt; ucCurSegNum++)
    {
        g_pstAcpuSegMsgEx->stMsgSeg.ucSegSn = ucCurSegNum;

        if (VOS_TRUE == bIsHead)
        {
            /* 消息头前加上长度信并放入环形缓冲区*/
            if (VOS_OK != OMRL_AcpuSendSocpData((VOS_UINT8 *)g_pstAcpuSegMsgEx,
                (sizeof(OM_APP_MSG_SEG_EX_STRU) + OM_APP_TRACE_LEN),
                (VOS_UINT8*)ulTempAddress, OM_APP_MSG_SEGMENT_LEN - OM_APP_TRACE_LEN))
            {
                return VOS_ERR;
            }

            bIsHead       =  VOS_FALSE;
            ulTempAddress += (OM_APP_MSG_SEGMENT_LEN - OM_APP_TRACE_LEN);
        }
        else
        {
            /* 消息头前加上长度信并放入环形缓冲区*/
            if (VOS_OK != OMRL_AcpuSendSocpData((VOS_UINT8 *)g_pstAcpuSegMsgEx,
                 sizeof(OM_APP_MSG_SEG_EX_STRU),
                (VOS_UINT8*)ulTempAddress, OM_APP_MSG_SEGMENT_LEN))
            {
                return VOS_ERR;
            }

            ulTempAddress += OM_APP_MSG_SEGMENT_LEN;
        }

        /* 计算剩余数据包大小 */
        usMsgLen -= OM_APP_MSG_SEGMENT_LEN;
    }

    /*设置消息头参数*/
    g_pstAcpuSegMsgEx->stMsgSeg.usSegLen = (VOS_UINT16)(usMsgLen + OM_APP_MSG_SEGMENT_HEADER_LENGTH);
    g_pstAcpuSegMsgEx->stMsgSeg.ucSegSn  = ucCurSegNum;

    /*为了保持Ringbuffer中存放的数据包4字节对齐*/
    usMsgLen = (usMsgLen + 3) & ~0x03;

    if (VOS_TRUE == bIsHead)
    {
        /* 消息头前加上长度并放入环形缓冲区 */
        if ( VOS_OK != OMRL_AcpuSendSocpData((VOS_UINT8 *)g_pstAcpuSegMsgEx,
                            (sizeof(OM_APP_MSG_SEG_EX_STRU) + OM_APP_TRACE_LEN),
                            (VOS_UINT8*)ulTempAddress,
                            usMsgLen - OM_APP_TRACE_LEN))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* 消息头前加上长度并放入环形缓冲区 */
        if ( VOS_OK != OMRL_AcpuSendSocpData((VOS_UINT8 *)g_pstAcpuSegMsgEx,
                                        sizeof(OM_APP_MSG_SEG_EX_STRU),
                                        (VOS_UINT8*)ulTempAddress,
                                        usMsgLen))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuMsgSplit
 功能描述  : 当在USB上进行通信时，使用的扩展分包函数
 输入参数  : pucMsg    -- 指向发送数据的指针
             usMsgLen  -- 发送数据的长度
 输出参数  : 无
 返 回 值  : VOS_UINT32

 修改历史      :
  1.日    期   : 2009年3月28日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 OMRL_AcpuMsgSplit(VOS_UINT8 *pucMsg, VOS_UINT16 usMsgLen)
{
    VOS_UINT8                           ucMsgCnt    = 1; /*分段的数量*/
    VOS_UINT32                          ulRet;

    /*进行互斥操作*/
#if (VOS_LINUX == VOS_OS_VER)
    down(&g_stOmTxBuffSem);
#else
    if ( VOS_OK != VOS_SmP(g_AcpuOmTxBuffSem, OM_PV_TIMEOUT) )
    {
        LogPrint("OMRL_AcpuMsgSplit, Error, g_AcpuOmTxBuffSem VOS_SmP Failed.\n");

        g_stAcpuUeToPcErrRecord.usSemErr++;
        return VOS_ERR;
    }
#endif

    /* 释放已发送数据内存 */
    if (VOS_OK != OMRL_AcpuReleaseSocpData())
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmTxBuffSem);
#else
        VOS_SmV(g_AcpuOmTxBuffSem);
#endif
        return VOS_ERR;
    }

    /* 计算分包个数 */
    ucMsgCnt = (VOS_UINT8)(((usMsgLen + OM_APP_MSG_SEGMENT_LEN) - 1)/OM_APP_MSG_SEGMENT_LEN);

    /* 获取OM源通道剩余BD个数 */
    if (VOS_OK != OMRL_AcpuIsBDEnough(ucMsgCnt))
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmTxBuffSem);
#else
        VOS_SmV(g_AcpuOmTxBuffSem);
#endif
        return VOS_ERR;
    }

    ulRet = OMRL_AcpuProcessSendData(pucMsg, ucMsgCnt, usMsgLen);

#if (VOS_LINUX == VOS_OS_VER)
    up(&g_stOmTxBuffSem);
#else
    VOS_SmV(g_AcpuOmTxBuffSem);
#endif

    return ulRet;
}

/*****************************************************************************
 函 数 名  : OMRL_AcpuUsbFrameInit
 功能描述  : 当为虚拟串口时，需要初始化缓冲区
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_UINT32
 修改历史  :
   1.日    期  : 2009年3月28日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuUsbFrameInit(VOS_VOID)
{
    /* 分配分包结构的内存空间 */
    g_pstAcpuSegMsgEx = (OM_APP_MSG_SEG_EX_STRU*)VOS_MemAlloc(ACPU_PID_OM, STATIC_MEM_PT,
                        sizeof(OM_APP_MSG_SEG_EX_STRU) + OM_APP_TRACE_LEN);

    if (VOS_NULL_PTR == g_pstAcpuSegMsgEx)
    {
        LogPrint("OMRL_AcpuUsbFrameInit:VOS_MemAlloc g_pstSegMsgEx Failed!\n");
        return VOS_ERR;
    }

    g_pstAcpuSegMsgEx->stSocpHdr.ucCPUID   = OM_TOOL_ACPU_ID;
    g_pstAcpuSegMsgEx->ulFrameHead         = OM_USB_FRAME_HEAD;

    /* 创建OM发送缓冲区 */
    if (VOS_OK != OM_CreateTraceBuffer(&g_stAcpuOmBufCtrl, OM_UPLINK_BUFFER_SIZE))
    {
        VOS_MemFree(ACPU_PID_OM, g_pstAcpuSegMsgEx);

        LogPrint("OMRL_AcpuUsbFrameInit:OM_CreateTraceBuffer Failed!\n");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OmAcpuInitVar
 功能描述  : 初始化记录错误信息的全局变量
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2009年5月18日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuInitVar(VOS_VOID)
{
    VOS_MemSet(&g_stAcpuPcToUeErrRecord, 0, sizeof(OM_ACPU_PC_UE_FAIL_STRU));
    VOS_MemSet(&g_stAcpuPcToUeSucRecord, 0, sizeof(OM_ACPU_PC_UE_SUC_STRU));
    VOS_MemSet(&g_stAcpuUeToPcErrRecord, 0, sizeof(OM_UE_PC_FAIL_STRU));
    VOS_MemSet(&g_stAcpuUeToPcSucRecord, 0, sizeof(OM_UE_PC_SUC_STRU));

#if (FEATURE_ON == FEATURE_CBT_LOG)
    VOS_MemSet(&g_stCBTAcpuPcToUeErrRecord, 0, sizeof(OM_ACPU_PC_UE_FAIL_STRU));
    VOS_MemSet(&g_stCBTAcpuPcToUeSucRecord, 0, sizeof(OM_ACPU_PC_UE_SUC_STRU));

#if (VOS_LINUX == VOS_OS_VER)
    sema_init(&g_stOmRxCBTBuffSem, 1);
#endif
#endif
}

/*****************************************************************************
 函 数 名     : OMRL_AcpuInit
 功能描述  : OMRL模块的初始化函数
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2008年7月1日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 OMRL_AcpuInit(VOS_VOID)
{
    OmAcpuInitVar();

    VOS_MemSet(&g_stMsgCombineInfo, 0, sizeof(g_stMsgCombineInfo));

    /* 首包序号为1 */
    g_stMsgCombineInfo.ucExpectedSegSn = 1;

#if (FEATURE_ON == FEATURE_CBT_LOG)
    VOS_MemSet(&g_stCBTMsgCombineInfo, 0, sizeof(g_stCBTMsgCombineInfo));

    /* 首包序号为1 */
    g_stCBTMsgCombineInfo.ucExpectedSegSn = 1;
#endif

#if (VOS_LINUX == VOS_OS_VER)
    sema_init(&g_stOmTxBuffSem, 1);
#else
    if (VOS_OK != VOS_SmMCreate("TXRB", VOS_SEMA4_FIFO, &g_AcpuOmTxBuffSem))
    {
        LogPrint("OMRL_AcpuInit: Error, VOS_SmMCreate Fail\n");
        return VOS_ERR;
    }
#endif

    if (VOS_OK != OMRL_AcpuHdlcInit())
    {
        LogPrint("OMRL_AcpuInit:OMRL_AcpuHdlcInit Fail.\n");
        return VOS_ERR;
    }

    /* 读36号NV项为烧片版本 */
    if (VOS_OK != OMRL_AcpuNVHdlcInit())
    {
        LogPrint("OMRL_AcpuInit:OMRL_AcpuNVHdlcInit Fail.\n");
        return VOS_ERR;
    }

    if (VOS_OK != OMRL_AcpuUsbFrameInit())
    {
        LogPrint("OMRL_AcpuInit:OMRL_AcpuUsbFrameInit Fail.\n");
        return VOS_ERR;
    }

    /* 将OM SOCP目的通道处理函数注册给SCM */
    if (VOS_OK != SCM_RegCoderDestProc(SOCP_CODER_DST_GU_OM, (SCM_CODERDESTFUCN)GU_OamSocpSendDataToUDI))
    {
        LogPrint("OMRL_AcpuInit:SCM_RegCoderDestProc Fail.\n");

        return VOS_ERR;
    }

    CPM_LogicRcvReg(CPM_OM_COMM, OMRL_AcpuRcvData);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : OmAcpuSendShow
 功能描述  : 打印数据从UE侧发往PC侧时正常处理的数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年9月04日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuSendShow(VOS_VOID)
{
    vos_printf("Total Data Send by Ps: num:%6u, len:%6u\n",
                g_stAcpuUeToPcSucRecord.stTotalData.ulNum, g_stAcpuUeToPcSucRecord.stTotalData.ulDataLen);

    vos_printf("Real Data send to Socp: num:%6u, len:%6u\n",
                g_stAcpuUeToPcSucRecord.stRealSendData.ulNum, g_stAcpuUeToPcSucRecord.stRealSendData.ulDataLen);

    vos_printf("Real Data release by Socp: num:%6u, len:%6u\n",
                g_stAcpuUeToPcSucRecord.stRealRlsData.ulNum, g_stAcpuUeToPcSucRecord.stRealRlsData.ulDataLen);

    vos_printf("Max Used Buffer Size: size:%6u\n", g_stAcpuUeToPcSucRecord.ulMaxUsedBufSize);

    return;
}

/*****************************************************************************
 函 数 名  : OmAcpuSendErrShow
 功能描述  : 打印数据从UE侧发往PC侧时异常处理的数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年9月04日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuSendErrShow(VOS_VOID)
{
    vos_printf("Interrput Lost Data: num:%6u, len:%6u\n",
                g_stAcpuUeToPcErrRecord.stIntData.ulNum, g_stAcpuUeToPcErrRecord.stIntData.ulDataLen);

    vos_printf("Total Lost Data: num:%6u, len:%6u\n",
                g_stAcpuUeToPcErrRecord.stLostData.ulNum, g_stAcpuUeToPcErrRecord.stLostData.ulDataLen);

    vos_printf("Link Err Data: num:%6u, len:%6u\n",
                g_stAcpuUeToPcErrRecord.stLinkErrData.ulNum, g_stAcpuUeToPcErrRecord.stLinkErrData.ulDataLen);

    vos_printf("Para Err Data: num:%6u, len:%6u\n",
                g_stAcpuUeToPcErrRecord.stParaErrData.ulNum, g_stAcpuUeToPcErrRecord.stParaErrData.ulDataLen);

    vos_printf("num of sem take err: num:%6u\n", g_stAcpuUeToPcErrRecord.usSemErr);

    vos_printf("num of release RD err: num:%6u\n", g_stAcpuUeToPcErrRecord.usRlsRdErr);

    vos_printf("num of release Mem err: num:%6u\n", g_stAcpuUeToPcErrRecord.usRlsMemErr);

    vos_printf("num of BD Lack err: num:%6u\n", g_stAcpuUeToPcErrRecord.usBDLackErr);

    vos_printf("num of get BD err: num:%6u\n", g_stAcpuUeToPcErrRecord.usGetBDErr);

    vos_printf("num of No Mem err: num:%6u\n", g_stAcpuUeToPcErrRecord.usNoMemErr);

    vos_printf("num of Send Socp Data err: num:%6u\n", g_stAcpuUeToPcErrRecord.usSendSocpDataErr);

    vos_printf("num of transfer sending addr err: num:%6u\n", g_stAcpuUeToPcErrRecord.usSendAddrErr);

    vos_printf("num of transfer Release addr err: num:%6u\n", g_stAcpuUeToPcErrRecord.usRlsAddrErr);

    return;
}


/*****************************************************************************
 函 数 名  : OmAcpuRcvShow
 功能描述  : 打印数据从PC侧发往UE侧时正常处理的数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年9月04日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuRcvShow(VOS_VOID)
{
    vos_printf("Total Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stTotalData.ulNum, g_stAcpuPcToUeSucRecord.stTotalData.ulDataLen);

    vos_printf("Data after Hdlc decap:   num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stHdlcDecapData.ulNum, g_stAcpuPcToUeSucRecord.stHdlcDecapData.ulDataLen);

    vos_printf("Link Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stLinkData.ulNum, g_stAcpuPcToUeSucRecord.stLinkData.ulDataLen);

    vos_printf("CCPU Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stCcpuData.ulNum, g_stAcpuPcToUeSucRecord.stCcpuData.ulDataLen);

    vos_printf("ACPU Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stAcpuData.ulNum, g_stAcpuPcToUeSucRecord.stAcpuData.ulDataLen);

    vos_printf("HIFI Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stHifiData.ulNum, g_stAcpuPcToUeSucRecord.stHifiData.ulDataLen);

    vos_printf("MCU Data Recv From PC: num:%6u, len:%6u\n",
                g_stAcpuPcToUeSucRecord.stMcuData.ulNum, g_stAcpuPcToUeSucRecord.stMcuData.ulDataLen);

    vos_printf("Data Send by ICC: num:%6u, len:%6u, slice:%6u\n",
                g_stAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendMsgNum,
                g_stAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendLen,
                g_stAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendSlice);

    vos_printf("Rls Data Recv From PC: num:%6u, slice:%6u\n",
                g_stAcpuPcToUeSucRecord.stRlsData.ulNum, g_stAcpuPcToUeSucRecord.stRlsData.ulDataLen);

#if (FEATURE_ON == FEATURE_CBT_LOG)
    vos_printf("CBT LOG Total Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stTotalData.ulNum, g_stCBTAcpuPcToUeSucRecord.stTotalData.ulDataLen);

    vos_printf("CBT LOG Data after Hdlc decap:   num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stHdlcDecapData.ulNum, g_stCBTAcpuPcToUeSucRecord.stHdlcDecapData.ulDataLen);

    vos_printf("CBT LOG Link Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stLinkData.ulNum, g_stCBTAcpuPcToUeSucRecord.stLinkData.ulDataLen);

    vos_printf("CBT LOG CCPU Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stCcpuData.ulNum, g_stCBTAcpuPcToUeSucRecord.stCcpuData.ulDataLen);

    vos_printf("CBT LOG ACPU Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stAcpuData.ulNum, g_stCBTAcpuPcToUeSucRecord.stAcpuData.ulDataLen);

    vos_printf("CBT LOG HIFI Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stHifiData.ulNum, g_stCBTAcpuPcToUeSucRecord.stHifiData.ulDataLen);

    vos_printf("CBT LOG MCU Data Recv From PC: num:%6u, len:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stMcuData.ulNum, g_stCBTAcpuPcToUeSucRecord.stMcuData.ulDataLen);

    vos_printf("CBT LOG Data Send by ICC: num:%6u, len:%6u, slice:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendMsgNum,
                g_stCBTAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendLen,
                g_stCBTAcpuPcToUeSucRecord.stICCSendSUCInfo.ulICCOmSendSlice);

    vos_printf("CBT LOG Rls Data Recv From PC: num:%6u, slice:%6u\n",
                g_stCBTAcpuPcToUeSucRecord.stRlsData.ulNum, g_stCBTAcpuPcToUeSucRecord.stRlsData.ulDataLen);
#endif
    return;
}

/*****************************************************************************
 函 数 名  : OmAcpuRcvErrShow
 功能描述  : 打印数据从PC侧发往UE侧时异常数据
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年9月04日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuRcvErrShow(VOS_VOID)
{
    vos_printf("Total Lost Data Recv From PC: num:%6u, len:%6u\n",
            g_stAcpuPcToUeErrRecord.stLostData.ulNum, g_stAcpuPcToUeErrRecord.stLostData.ulDataLen);

    vos_printf("Number of Frame Decap Err: num:%6u\n", g_stAcpuPcToUeErrRecord.ulFrameDecapErr);

    vos_printf("Number of Packet Len Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usPacketLenErr);

    vos_printf("Number of Too Short Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usLenTooShortErr);

    vos_printf("Number of Seg Len Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usSegLenErr);

    vos_printf("Number of Seg Num Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usSegNumErr);

    vos_printf("Number of DataType Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usDatatypeErr);

    vos_printf("Number of Too Long Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usMsgTooLongErr);

    vos_printf("Number of Cpu Id Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usCpuIdErr);

    vos_printf("Number of No Mem Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usNoMemErr);

    vos_printf("Number of Data Head Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usDataHeadErr);

    vos_printf("Number of Msg Len Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usMsgLenErr);

    vos_printf("Number of Msg Sn Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usMsgSnErr);

    vos_printf("Number of Packet Lost Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usPacketLostErr);

    vos_printf("Number of Link Data Len Err: num:%6u\n", g_stAcpuPcToUeErrRecord.usLinkDataLenErr);

    vos_printf("Number of Alloc msg Mem: num: %6u\n",g_stAcpuPcToUeErrRecord.usAllocMsg);

    vos_printf("Number of Lost Msg Because Switch Is IDLE: num: %6u\n",g_stAcpuPcToUeErrRecord.usLinkStatusErr);

    vos_printf("Data Send err by ICC: num:%6u, len:%6u, slice:%6u\n",
            g_stAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrNum,
            g_stAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrLen,
            g_stAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrSlice);

#if (FEATURE_ON == FEATURE_CBT_LOG)
    vos_printf("CBT LOG Total Lost Data Recv From PC: num:%6u, len:%6u\n",
               g_stCBTAcpuPcToUeErrRecord.stLostData.ulNum, g_stCBTAcpuPcToUeErrRecord.stLostData.ulDataLen);

    vos_printf("CBT LOG Number of Frame Decap Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.ulFrameDecapErr);

    vos_printf("CBT LOG Number of Packet Len Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usPacketLenErr);

    vos_printf("CBT LOG Number of Too Short Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usLenTooShortErr);

    vos_printf("CBT LOG Number of Seg Len Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usSegLenErr);

    vos_printf("CBT LOG Number of Seg Num Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usSegNumErr);

    vos_printf("CBT LOG Number of DataType Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usDatatypeErr);

    vos_printf("CBT LOG Number of Too Long Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usMsgTooLongErr);

    vos_printf("CBT LOG Number of Cpu Id Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usCpuIdErr);

    vos_printf("CBT LOG Number of No Mem Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usNoMemErr);

    vos_printf("CBT LOG Number of Data Head Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usDataHeadErr);

    vos_printf("CBT LOG Number of Msg Len Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usMsgLenErr);

    vos_printf("CBT LOG Number of Msg Sn Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usMsgSnErr);

    vos_printf("CBT LOG Number of Packet Lost Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usPacketLostErr);

    vos_printf("CBT LOG Number of Link Data Len Err: num:%6u\n", g_stCBTAcpuPcToUeErrRecord.usLinkDataLenErr);

    vos_printf("CBT LOG Number of Alloc msg Mem: num: %6u\n",g_stCBTAcpuPcToUeErrRecord.usAllocMsg);

    vos_printf("CBT LOG Number of Lost Msg Because Switch Is IDLE: num: %6u\n",g_stCBTAcpuPcToUeErrRecord.usLinkStatusErr);

    vos_printf("CBT LOG Data Send err by ICC: num:%6u, len:%6u, slice:%6u\n",
            g_stCBTAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrNum,
            g_stCBTAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrLen,
            g_stCBTAcpuPcToUeErrRecord.stICCSendFailInfo.ulICCOmSendErrSlice);
#endif

    return;
}

/*****************************************************************************
 函 数 名  : OmOpenLog
 功能描述  : 打印当前OM通道的状态
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2009年5月18日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmOpenLog(VOS_UINT32 ulFlag)
{
    g_ulOmAcpuDbgFlag = ulFlag;

    return;
}


/*****************************************************************************
 函 数 名  : OmAcpuRate
 功能描述  : 打印数据从UE侧到PC的流量统计
 输入参数  :
 输出参数  :
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2008年6月25日
     修改内容  : Creat Function
*****************************************************************************/
VOS_VOID OmAcpuRate(VOS_VOID)
{
    VOS_UINT32            ulCurrTick;                    /*记录现在统计时间*/
    VOS_UINT32            ulDeltaTick;                   /*记录统计时间*/
    VOS_UINT32            ulDelData;                     /*记录统计数据大小*/
    VOS_UINT32            ulBandWidth;                   /*记录统计数据大小*/

    vos_printf("OmAcpuRate Show(ALL Data To UDI):\n");

    ulCurrTick = VOS_GetTick();

    if (ulCurrTick < g_ulAcpuLastTick)
    {
        ulDeltaTick = (0xFFFFFFFF - g_ulAcpuLastTick) + ulCurrTick;
    }
    else
    {
        ulDeltaTick = ulCurrTick - g_ulAcpuLastTick;
    }

    ulDelData      = g_stAcpuDebugInfo.ulUSBSendLen - g_ulAcpuLastByteCnt;
    g_ulAcpuLastByteCnt  = g_stAcpuDebugInfo.ulUSBSendLen;

    ulBandWidth    = (ulDelData/ulDeltaTick)/10;

    /*统计OM在ulDeltaTick时间(单位10ms)内发送了ulTotalLen字节数据*/
    vos_printf("OmAcpuRate,Tick <%u> Byte <%u>, BandWidth <%u>.\n",
                 ulDeltaTick, ulDelData, ulBandWidth);

    g_ulAcpuLastTick = ulCurrTick;

    vos_printf("OmAcpuRate Show End\n");
}


VOS_VOID OmAcpuShowCombineInfo(VOS_VOID)
{
    vos_printf("pstWholeMsg:        0x%x\r\n",g_stMsgCombineInfo.pstWholeMsg);
    vos_printf("ucExpectedSegSn:    0x%x\r\n",g_stMsgCombineInfo.ucExpectedSegSn);
    vos_printf("ucTotalSegNum:      0x%x\r\n",g_stMsgCombineInfo.ucTotalSegNum);
    vos_printf("ulMoveLen:          0x%x\r\n",g_stMsgCombineInfo.ulMoveLen);
    vos_printf("ulTotalMsgLen:      0x%x\r\n",g_stMsgCombineInfo.ulTotalMsgLen);
}


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif


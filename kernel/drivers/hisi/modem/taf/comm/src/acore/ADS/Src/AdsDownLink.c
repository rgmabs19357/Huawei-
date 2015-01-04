/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AdsDlProcData.c
  版 本 号   : 初稿
  生成日期   : 2011年12月6日
  最近修改   :
  功能描述   : ADS处理下行数据
  函数列表   :
  修改历史   :
  1.日    期   : 2011年12月6日
    修改内容   : 创建文件

******************************************************************************/
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "DrvInterface.h"
#include "IpsMntn.h"

#include "AcpuReset.h"

#include "AdsFilter.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C
/*lint +e767*/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    /* 增加下行IPF中断统计计数 */
    ADS_DBG_DL_RECV_IPF_BREAK_NUM(1);

    /* 触发下行RD处理事件 */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);

    return VOS_OK;
}


VOS_VOID ADS_DL_RcvTiProtectExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* 统计定时器超时次数 */
    ADS_DBG_DL_RD_TI_PROTECT_EXPIRED_NUM(1);

    /* 停止定时器 */
    ADS_StopTimer(ACPU_PID_ADS_DL, TI_ADS_DL_PROTECT);

    if (BSP_IPF_GetDlRdNum() > 0)
    {
        ADS_DBG_DL_RD_PROTECT_EVENT_NUM(1);

        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    }

    /* 重新启动保护定时器 */
    ADS_DL_StartProtectTimer();

    return;
}

#if (FEATURE_OFF == FEATURE_SKB_EXP)
/*****************************************************************************
 函 数 名  : ADS_DL_IpfAdqEmptyCB
 功能描述  : ADS向IPF注册的下行ADQ空中断处理函数
 输入参数  : IPF_ADQ_EMPTY_E eAdqEmpty
 输出参数  : 无
 返 回 值  : VOS_INT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    /* 增加下行IPF ADQ空中断统计计数 */
    ADS_DBG_DL_RECV_ADQ_EMPTY_BREAK_NUM(1);

    ADS_DBG_DL_GET_ADQ_EMPTY_NUM(eAdqEmpty, 1);

    /* 触发下行ADQ空中断处理事件 */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_ProcIpfAdqEmtpyEvent
 功能描述  : 处理IPF的ADQ空中断事件
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月20日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_ProcIpfAdqEmtpyEvent(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    VOS_UINT                            ulActAd0Num;
    VOS_UINT                            ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* 获取两个ADQ的空闲的AD个数 */
    lRslt = BSP_IPF_GetDlAdNum(&ulIpfAd0Num, &ulIpfAd1Num);

    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_GET_AD_FAIL_NUM(1);
        return;
    }

    /* 首先配置大内存的ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num, &ulActAd1Num);
    }

    /* 再配置小内存的ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num, &ulActAd0Num);
    }

    /* AD0为空或者AD1为空需要重新启动定时器 */
    if (((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
     || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)))
    {
        /* 如果两个ADQ任何一个空且申请不到内存，启定时器 */
        ADS_DL_StartAdqEmptyTimer();
    }
    else
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, TI_ADS_DL_ADQ_EMPTY);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvTiAdqEmptyExpired
 功能描述  : TI_ADS_DL_ADQ_EMPTY超时处理函数
 输入参数  : VOS_UINT32                          ulParam,
             VOS_UINT32                          ulTimerName
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* 触发下行ADQ空中断处理事件 */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
}
VOS_VOID ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum,
    VOS_UINT                           *pulActAdNum
)
{
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstZcData = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPullData = VOS_NULL_PTR;
    VOS_UINT8                          *pstZcHead = VOS_NULL_PTR;
    VOS_UINT32                          ulActAdNum;
    VOS_UINT16                          usLen;
    IPF_AD_DESC_S                      *pstIpfAdDesc = VOS_NULL_PTR;
    VOS_INT32                           lRslt;

    ulActAdNum = 0;

    if (IPF_AD_0 == enAdType)
    {
        usLen = ADS_DL_AD0_DATA_LEN;
    }
    else
    {
        usLen = ADS_DL_AD1_DATA_LEN;
    }

    for (i = 0; i < ulIpfAdNum; i++)
    {
        pstIpfAdDesc = ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i);

        pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(usLen);

        if (VOS_NULL_PTR == pstZcData)
        {
            ADS_DBG_DL_ALLOC_AD_FAIL_NUM(enAdType, 1);
            break;
        }

        /* 保存数据头结点 */
        pstZcHead = pstZcData->data;

        /* 偏移skbuff的tail指针 */
        IMM_ZcPut(pstZcData, usLen);

        /* 偏移head指针14个字节，用于MAC头 */
        pstZcPullData = (VOS_CHAR *)IMM_ZcPull(pstZcData, ADS_DL_AD_DATA_PTR_OFFSET);

        ADS_CACHE_INVALIDATE(pstZcHead, usLen);

        /* 填充OUTPUT0，目的地址 */
        pstIpfAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_UINT32 *)pstZcPullData);

        /* 填充OUTPUT1，SKBUFF */
        pstIpfAdDesc->u32OutPtr1 = (VOS_UINT32)pstZcData;

        ADS_DBG_DL_ALLOC_AD_SUCC_NUM(enAdType, 1);;

        ulActAdNum++;
    }

    /* 申请到AD才需要配置ADQ */
    if (0 != ulActAdNum)
    {
        lRslt = BSP_IPF_ConfigDlAd(enAdType, ulActAdNum, ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, 0));

        if (IPF_SUCCESS != lRslt)
        {
            ADS_DBG_DL_CONFIG_AD_FAIL_NUM(enAdType, 1);

            /* 配置失败，释放内存 */
            for (i = 0; i < ulActAdNum; i++)
            {
                IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i)->u32OutPtr1);
            }

            *pulActAdNum = 0;
            return;
        }

        ADS_DBG_DL_CONFIG_AD_SUCC_NUM(enAdType, 1);
    }

    /* 输出实际配置的AD数目 */
    *pulActAdNum = ulActAdNum;

    return;
}


/*****************************************************************************
 函 数 名  : ADS_DL_ProcAdq
 功能描述  : 处理ADQ
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_ProcAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    VOS_UINT                            ulActAd0Num;
    VOS_UINT                            ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* 获取两个ADQ的空闲的AD个数 */
    lRslt = BSP_IPF_GetDlAdNum(&ulIpfAd0Num, &ulIpfAd1Num);

    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_GET_AD_FAIL_NUM(1);
        return;
    }

    /* 首先配置大内存的ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num, &ulActAd1Num);
    }

    /* 再配置小内存的ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num, &ulActAd0Num);
    }

    return;
}

/*****************************************************************************
 函 数 名  : ADS_DL_InitAdq
 功能描述  : 初始化ADQ
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月19日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_InitAdq(VOS_VOID)
{
    ADS_DL_ProcAdq();
}


VOS_VOID ADS_DL_SendNdClientDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_DATA_IND_STRU         *pstDataInd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /*申请消息  */
    pstDataInd = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2);

    /* 内存申请失败，返回 */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH);

    /*填写消息内容*/
    /* ND CLIENT 的PID */
    pstDataInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstDataInd->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, pstImmZc->data, usDataLen);


    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}
VOS_VOID ADS_DL_FreeIpfUsedAd(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /* 由于局部变量的大小不能超过1K，故AD0和AD1的目的地址数组使用同一个 */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD0_DESC_SIZE];

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE);
    if (IPF_SUCCESS == BSP_IPF_GetUsedDlAd(IPF_AD_1, (BSP_U32 *)&ulAdNum, astAdDesc))
    {
        /* 释放ADQ1的内存 */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)astAdDesc[i].u32OutPtr1);
        }
    }

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE);
    if (IPF_SUCCESS == BSP_IPF_GetUsedDlAd(IPF_AD_0, (BSP_U32 *)&ulAdNum, astAdDesc))
    {
        /* 释放ADQ0的内存 */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)astAdDesc[i].u32OutPtr1);
        }
    }

    return;
}


#if 0
/*****************************************************************************
 函 数 名  : ADS_DL_SendNdClientErrInd
 功能描述  : IPV6大于MTU的包通过VOS发给NDCLIENT
 输入参数  : IPF_RD_DESC_S                      *pstRdDesc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    修改内容   : 新生成函数

  2.日    期   : 2012年12月14日
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_VOID ADS_DL_SendNdClientErrInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_ERR_IND_STRU          *pstErrInd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /*申请消息  */
    pstErrInd = (ADS_NDCLIENT_ERR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_DL,
                                             sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen -2);

    /* 内存申请失败，返回 */
    if( VOS_NULL_PTR == pstErrInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: pstErrInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstErrInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen -2 - VOS_MSG_HEAD_LENGTH);

    /*填写消息内容*/
    /* ND CLIENT 的PID */
    pstErrInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstErrInd->enMsgId       = ID_ADS_NDCLIENT_ERR_IND;
    pstErrInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->enErrType     = ADS_NDCLIENT_ERR_TYPE_MTU_OVERLONG;
    pstErrInd->usLen         = usDataLen;

    PS_MEM_CPY(pstErrInd->aucData, pstImmZc->data, usDataLen);


    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstErrInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: Send msg fail!");
    }

    return;
}
#endif

#else
VOS_VOID ADS_DL_SendNdClientDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_DATA_IND_STRU         *pstDataInd;
    VOS_UINT16                          usDataLen;

    usDataLen = pstRdDesc->u16PktLen;

    /*申请消息  */
    pstDataInd = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2);

    if (0 == usDataLen)
    {
        vos_printf("ADS_DL_SendNdClientDataInd: usDataLen is 0\r\n");
    }

    if (0 == pstRdDesc->u32OutPtr)
    {
        vos_printf("ADS_DL_SendNdClientDataInd: u32OutPtr is NULL\r\n");
    }

    /* 内存申请失败，返回 */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen -2 - VOS_MSG_HEAD_LENGTH);

    /*填写消息内容*/
    /* ND CLIENT 的PID */
    pstDataInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstDataInd->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, (VOS_UINT8 *)TTF_PHY_TO_VIRT(pstRdDesc->u32OutPtr), usDataLen);

    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}

#if 0
/*****************************************************************************
 函 数 名  : ADS_DL_SendNdClientErrInd
 功能描述  : IPV6大于MTU的包通过VOS发给NDCLIENT
 输入参数  : IPF_RD_DESC_S                      *pstRdDesc
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月7日
    修改内容   : 新生成函数

  2.日    期   : 2012年12月14日
    修改内容   : DSDA Phase II
*****************************************************************************/
VOS_VOID ADS_DL_SendNdClientErrInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_ERR_IND_STRU          *pstErrInd;
    VOS_UINT16                          usDataLen;

    usDataLen = pstRdDesc->u16PktLen;

    /*申请消息  */
    pstErrInd = (ADS_NDCLIENT_ERR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_DL,
                                             sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen - 2);

    /* 内存申请失败，返回 */
    if( VOS_NULL_PTR == pstErrInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: pstErrInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstErrInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH);

    /*填写消息内容*/
    /* ND CLIENT 的PID */
    pstErrInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstErrInd->enMsgId       = ID_ADS_NDCLIENT_ERR_IND;
    pstErrInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->enErrType     = ADS_NDCLIENT_ERR_TYPE_MTU_OVERLONG;
    pstErrInd->usLen         = usDataLen;

    PS_MEM_CPY(pstErrInd->aucData, (VOS_UINT8 *)pstRdDesc->u32OutPtr, usDataLen);


    /* 调用VOS发送原语 */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstErrInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: Send msg fail!");
    }

    return;
}
#endif

#endif

/*****************************************************************************
 函 数 名  : ADS_DL_FreeRd
 功能描述  : 释放RD
 输入参数  : pstRdDesc                  - 调用者保证参数非NULL
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月29日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID ADS_DL_FreeRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr));
#else
    /* 释放C核内存 */
    IMM_RemoteFreeTtfMem(ADS_DL_GET_TTFMEM_FROM_IPF_USR2(pstRdDesc->u32UsrField2));
#endif

    return;
}
VOS_VOID ADS_DL_ProcRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT8                           ucRabId;
    IMM_ZC_STRU                        *pstImmZc                = VOS_NULL_PTR;
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc          = VOS_NULL_PTR;
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc    = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    VOS_UINT32                          ulIpLen;
#endif

    /* 接口修改后，获取此值 */
    ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    ucRabId = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* 增加桥功能，输出指针已是SK BUFF */
    pstImmZc       = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
    ulIpLen        = ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen);
    pstImmZc->tail -= (pstImmZc->len - ulIpLen);
    pstImmZc->len  = ulIpLen;
#else
    /* 将IPF过滤出的数据转换成Zc数据 */
    pstImmZc = IMM_DataTransformImmZc((VOS_UINT8*)TTF_PHY_TO_VIRT((VOS_UINT32)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr)),
                                      ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen),
                                      ADS_DL_GET_TTFMEM_FROM_IPF_USR2(pstRdDesc->u32UsrField2));
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNetDevData1: pstImmZc is null! ");

        ADS_DBG_DL_TRANS_FROM_IMMZC_ERR_NUM(1);

        /*IMM_DataTranferImmZc申请不到IMM_ZC头节点，接口内部回收C核跨核共享内存。*/
        return;
    }
#endif

    IPS_MNTN_TraceIpInfo(pstImmZc,ID_IPS_TRACE_IP_ADS_DL);

    /* 获取RABID对应下行回调函数指针 */
    if (ADS_IS_VALID_RABID(ucRabId))
    {
        pRcvDlDataFunc          = ADS_DL_GET_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId);

        pRcvDlFilterDataFunc    = ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId);
    }

    /* 若存在下行过滤回调函数，则需判断是否需要发送给下行过滤函数处理 */
    if (VOS_NULL_PTR != pRcvDlFilterDataFunc)
    {
        /* 调用下行过滤数据包处理函数，如果数据处理完成则直接退出，否则交由正常下行处理 */
        if (VOS_OK == ADS_FILTER_ProcDlPacket(pstImmZc,
                                    ADS_DL_GET_IP_TYPE_FROM_IPF_RSLT(pstRdDesc->u16Result)))
        {
            (VOS_VOID)pRcvDlFilterDataFunc(ADS_BUILD_EX_RAB_ID(ucInstanceIndex, ucRabId),
                                           pstImmZc,
                                           ADS_DL_GET_IP_TYPE_FROM_IPF_RSLT(pstRdDesc->u16Result));
            return;
        }
    }

    /* 正常发送下行数据 */
    if (VOS_NULL_PTR != pRcvDlDataFunc)
    {
        ADS_DBG_SEND_DL_PKT_NUM(ucInstanceIndex, 1);

        (VOS_VOID)pRcvDlDataFunc(ADS_BUILD_EX_RAB_ID(ucInstanceIndex, ucRabId), pstImmZc, ADS_DL_GET_IP_TYPE_FROM_IPF_RSLT(pstRdDesc->u16Result));
    }
    else
    {
        ADS_NORMAL_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_SendNetDevData1: Free TTF memory, RabId is", ucRabId);

        ADS_DBG_DL_FREE_NUM(ucInstanceIndex, 1);

        IMM_ZcFree(pstImmZc);
    }

    return;
}


VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    BSP_U32                             ulRdNum = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulCnt;
    ADS_DL_IPF_RESULT_STRU             *pstIpfRslt;
    IPF_RD_DESC_S                      *pstRdDesc;
    ADS_DRV_ASSEM_FUNC                  pFcAssemTuneFunc = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
#endif

    /*
    IPF_RD_DESC_S中u16Result含义
    [15]Reserve
    [14]bd_cd_noeqBD中len和CD的长度不等错误提示，0表示长度匹配，1表示长度不匹配
    [13]pkt_parse_err数据解析错误指示，0表示数据解析正常，1表示数据解析错误
    [12]bd_pkt_noeqBD中len和IP包头指示的len不等错误指示，0表示长度匹配，1表示长度不匹配
    [11]head_len_err IPV4长度错误指示信号，IPV6不检查长度，0表示头长度正确，1表示头长度错误
    [10]version_err版本号错误指示，0表示版本号是4或6，1表示版本号不是4或6
    [9]ip_type IP包类型，0表示IPV4，1表示IPV6
    [8]ff_type分片包第一个分片是否包含上层头指示，0表示分片包第一个分片包括上层头(IP包未分片时也为0)
     1表示分片包第一个分片包括上层头
    [7:6]pf_type IP包分片指示类型，00表示IP包未分片，01表示IP包分片，且为第一个分片，
       02表示分片，且为最后一个分片，03表示分片，且为中间分片
    [0:5]bear_id承载号，如果为0x3F代表所有过滤器不匹配
    */

    /*
    IPF_RD_DESC_S中user field域含义
    u16UsrField1: RabId
    u32UsrField2: 目的TTF_MEM_ST指针
    u32UsrField3: 源TTF_MEM_ST指针
    */

    /* 获取RD */
    pstRdDesc = ADS_DL_GET_IPF_RD_BUFFER_PTR(0);
    BSP_IPF_GetDlRd(&ulRdNum, pstRdDesc);

    /* 获取的RD为0 */
    if (0 == ulRdNum)
    {
        /* 增加RD获取个数为0的统计个数 */
        ADS_DBG_DL_RECV_RD_ZERO_NUM(1);

        return;
    }

#if (FEATURE_OFF == FEATURE_LTE)
    DRV_WDT_FEED(0);
#endif

    /* 增加RD统计个数 */
    ADS_DBG_DL_RECV_RD_NUM(ulRdNum);

    /* 追踪下行接收数据 */
    ADS_MNTN_TraceRcvDlData();

    /* 检查是否需要调整底软组包参数 */
    if (VOS_TRUE == ADS_DL_IsFcAssemTuneNeeded(ulRdNum))
    {
        pFcAssemTuneFunc = ADS_DL_GET_FC_ASSEM_TUNE_FUNC(0);
        pFcAssemTuneFunc();
    }

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* 先配置AD，再处理RD */
    ADS_DL_ProcAdq();
#endif

    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc  = ADS_DL_GET_IPF_RD_BUFFER_PTR(ulCnt);
        pstIpfRslt = (ADS_DL_IPF_RESULT_STRU*)&(pstRdDesc->u16Result);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
        ADS_CACHE_INVALIDATE(pstImmZc->data - ADS_DL_AD_DATA_PTR_OFFSET, pstRdDesc->u16PktLen + ADS_DL_AD_DATA_PTR_OFFSET);
#endif

        /* 接口修改后，获取此值 */
        ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);

        /* 统计下行周期性收到的数据字节数，用于流量查询 */
        ADS_RECV_DL_PERIOD_PKT_NUM(ucInstanceIndex, ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen));

        /* BearId 0x3F: 正常下行数据包需要转发给NDIS/PPP/RNIC*/
        if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfRslt->usBearedId)
        {
            if (ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(pstRdDesc->u16Result))
            {
                ADS_DBG_DL_IPF_ERR_PKT_NUM(ucInstanceIndex, 1);
            }

            ADS_DL_ProcRd(pstRdDesc);
        }
        /* BearId 19: NDClient包，需要转发给NDClient */
        else if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == pstIpfRslt->usBearedId)
        {
            /* 增加统计计数 */
            ADS_DBG_DL_RECV_NDCLIENT_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_SendNdClientDataInd(pstRdDesc);

            ADS_DL_FreeRd(pstRdDesc);
        }
        /* [0,4]和[5,15]定义为非法数据包; [16,17,18,20,21]目前直接释放 */
        else
        {
            /* 增加统计计数 */
            ADS_DBG_DL_RABID_ERR_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_FreeRd(pstRdDesc);
        }
    }


    BSP_NCM_Write_Ready();

    return;
}


VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* 获取流控阈值参数 */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (VOS_TRUE != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(), (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_EXP_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}
VOS_VOID ADS_DL_RegDrvAssemFunc(FC_ADS_DRV_ASSEM_STRU *pstDrvAssemParam)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemParamInfo;

    pstFcAssemParamInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemParamInfo->ulEnableMask     = pstDrvAssemParam->ucEnableMask;
    pstFcAssemParamInfo->ulRateUpLev      = pstDrvAssemParam->ulDlRateUpLev;
    pstFcAssemParamInfo->ulRateDownLev    = pstDrvAssemParam->ulDlRateDownLev;
    pstFcAssemParamInfo->ulExpireTmrLen   = pstDrvAssemParam->ulExpireTmrLen;
    pstFcAssemParamInfo->pFcAssemTuneFunc = pstDrvAssemParam->pDrvAssemFunc;

    return;
}


VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucRabId,
    RCV_DL_DATA_FUNC                    pFunc)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId的高2个bit表示modem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId合法性检查 */
    if (VOS_OK != ADS_IsValidRabId(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegDlDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* 设置ADS下行数据回调内容 */
    pstDlRabInfo->ucRabId        = ucRealRabId;
    pstDlRabInfo->pRcvDlDataFunc = pFunc;

    return VOS_OK;
}
VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId的高2个bit表示modem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId合法性检查 */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* 设置ADS下行数据过滤回调内容 */
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* 保存过滤地址信息 */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}


VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId的高2个bit表示modem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId合法性检查 */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* 去注册ADS下行数据过滤回调内容 */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* 清除过滤信息 */
    ADS_FILTER_Reset();

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvAtPdpStatusInd(MsgBlock *pMsg)
{
    AT_ADS_PDP_STATUS_IND_STRU         *pstPdpStatusInd;
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    enPktType      = ADS_CDS_IPF_PKT_TYPE_IP;

    pstPdpStatusInd = (AT_ADS_PDP_STATUS_IND_STRU *)pMsg;

    /* AT接口修改后，获取此值 */
    ucInstanceIndex = (VOS_UINT8)pstPdpStatusInd->enModemId;

    /* RabId合法性检查 */
    if (VOS_OK != ADS_IsValidRabId(pstPdpStatusInd->ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvAtPdpStatusInd: Rab Id is invalid");

        return VOS_ERR;
    }

    if (AT_ADS_PDP_PPP == pstPdpStatusInd->enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, pstPdpStatusInd->ucRabId);

    /* PDP激活 */
    if (AT_ADS_PDP_STATUS_ACT == pstPdpStatusInd->enPdpStatus)
    {
        /* 设置ADS下行数据回调的RABID */
        pstDlRabInfo->ucRabId        = pstPdpStatusInd->ucRabId;
        pstDlRabInfo->enPktType      = enPktType;
    }
    /* PDP去激活  */
    else if (AT_ADS_PDP_STATUS_DEACT == pstPdpStatusInd->enPdpStatus)
    {
        /* 清除ADS下行数据回调内容 */
        pstDlRabInfo->ucRabId        = ADS_RAB_ID_INVALID;
        pstDlRabInfo->pRcvDlDataFunc = VOS_NULL_PTR;
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvAtPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    /* 停止所有启动的定时器 */
    for (ucIndex = 0; ucIndex < ADS_MAX_TIMER_NUM; ucIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ucIndex);
    }

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* 释放IPF的AD */
    ADS_DL_FreeIpfUsedAd();
#endif

    /* 释放信号量，使得调用API任务继续运行 */
    VOS_SmV(ADS_GetDLResetSem());

    return VOS_OK;
}
VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* 复位IPF */
    BSP_IPF_DlRegReInit();

    /* 重新初始化ADQ */
    ADS_DL_InitAdq();
#endif

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : ADS_DL_RcvAtMsg
 功能描述  : 接收来自AT的消息
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvAtMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_AT_ADS_PDP_STATUS_IND:
            ADS_DL_RcvAtPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : ADS_DL_RcvCdsMsg
 功能描述  : 接收来自CDS的消息
             暂时没有要处理的消息，预留便于后续扩展
 输入参数  : MsgBlock *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月6日
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* 暂时没有要处理的消息，如果收到消息可能有错误 */
    return VOS_ERR;
}
VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;


    switch(pstMsg->ulMsgName)
    {
        case ID_CCPU_ADS_DL_RESET_START_IND:
            ADS_DL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_CCPU_ADS_DL_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* 消息的分发处理 */
    switch ( pMsg->ulSenderPid )
    {
        /* 来自AT的消息 */
        case WUEPS_PID_AT:
            ADS_DL_RcvAtMsg(pMsg);
            return;

        /* 来自CDS的消息 */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* 来自ADS DL的消息 */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
            return;

        default:
            return;
    }
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


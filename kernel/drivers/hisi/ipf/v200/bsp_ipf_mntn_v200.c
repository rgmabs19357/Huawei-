/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BSP_IPF_MNTN_V200.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月3日
  最近修改   :
  功能描述   : IPF可维可测接口
  函数列表   :
              BSP_IPF_BDInfo
              BSP_IPF_CHInfo
              BSP_IPF_DbgInfo
              BSP_IPF_FilterChainInfo
              BSP_IPF_FilterInfo
              BSP_IPF_FreeFilterInfo
              BSP_IPF_Help
              BSP_IPF_MemInfo
              BSP_IPF_RDInfo
              BSP_IPF_RegDump
              BSP_IPF_UseFilterInfo
  修改历史   :
  1.日    期   : 2013年6月3日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/module.h>
#include "product_config.h"
#if (FEATURE_IPF_VERSION == IPF_V200)

#include "drv_global.h"
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#include "BSP_DRV_IPF_V200.h"
#else
#include "bsp_drv_ipf_v200.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define IPF_REG_OFFSET_TO_ADDR(i)   (IPF_REGBASE_ADR + 4 * i)

extern IPF_UL_S g_stIpfUl;
extern IPF_DL_S g_stIpfDl;
extern IPF_DEBUG_INFO_S* g_stIPFDebugInfo;
extern BSP_U32* g_pbIPFInit;
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
extern IPF_FILTER_INFO_S g_stIPFFilterInfo[IPF_FILTER_CHAIN_MAX_NUM];
extern IPF_MATCH_INFO_S* g_pstExFilterAddr;
extern IPF_ID_S* g_stIPFBasicFreeList;
#endif
/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
BSP_VOID BSP_IPF_Help(BSP_VOID)
{
    IPF_PRINT("===============================================\n");
    IPF_PRINT("BSP_IPF_RegDump 参数1:无\n");
    IPF_PRINT("BSP_IPF_DbgInfo 参数1:无\n");
    IPF_PRINT("BSP_IPF_MemInfo 参数1:无\n");
    IPF_PRINT("BSP_IPF_BDInfo  参数1:通道类型(0-上行；1-下行)  参数2:BD指针偏移(0~63)\n");
    IPF_PRINT("BSP_IPF_RDInfo  参数1:通道类型(0-上行；1-下行)  参数2:RD指针偏移(0~63)\n");
    IPF_PRINT("BSP_IPF_CHInfo  参数1:通道类型(0-上行；1-下行)\n");
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
    IPF_PRINT("BSP_IPF_UseFilterInfo   参数1:过滤器链组号(0~7)\n");
    IPF_PRINT("                              0-modem0上行\n");
    IPF_PRINT("                              0-modem1上行\n");
    IPF_PRINT("                              0-modem0下行\n");
    IPF_PRINT("                              0-modem1下行\n");
    IPF_PRINT("BSP_IPF_FreeFilterInfo  参数1:无\n");
    IPF_PRINT("BSP_IPF_FilterInfo      参数1:过滤器序号(0~511)\n");
    IPF_PRINT("BSP_IPF_FilterChainInfo 参数1:过滤器链组号(0~7)\n");
#endif
}

BSP_S32 BSP_IPF_RegDump(BSP_VOID)
{
    BSP_U32 i = 0;
    BSP_U32 u32RegValue = 0;

    IPF_PRINT("============BEGIN===========\n");
    for(i = 0; i < IPF_REG_NUM; i++)
    {
        IPF_REG_READ(IPF_REG_OFFSET_TO_ADDR(i), u32RegValue);
        IPF_PRINT("[0x%x]:          0x%x\n", IPF_REG_OFFSET_TO_ADDR(i), u32RegValue);
    }
    IPF_PRINT("=============END============\n");

    return 0;
}

BSP_S32 BSP_IPF_DbgInfo(BSP_VOID)
{
    IPF_PRINT("============BEGIN===========\n");
    IPF_PRINT("上行处理结果中断上报次数:           %d\n",g_stIPFDebugInfo->u32UlResultCnt);
    IPF_PRINT("上行处理结果超时中断上报次数:       %d\n",g_stIPFDebugInfo->u32UlResultTimeoutCnt);
    IPF_PRINT("下行处理结果中断上报次数:           %d\n",g_stIPFDebugInfo->u32DlResultCnt);
    IPF_PRINT("下行处理结果超时中断上报次数:       %d\n",g_stIPFDebugInfo->u32DlResultTimeoutCnt);
    IPF_PRINT("上行ADQ0空中断次数:                 %d\n",g_stIPFDebugInfo->u32UlAdq0Empty);
    IPF_PRINT("上行ADQ1空中断次数:                 %d\n",g_stIPFDebugInfo->u32UlAdq1Empty);
    IPF_PRINT("下行ADQ0空中断次数:                 %d\n",g_stIPFDebugInfo->u32DlAdq0Empty);
    IPF_PRINT("下行ADQ1空中断次数:                 %d\n",g_stIPFDebugInfo->u32DlAdq1Empty);
    IPF_PRINT("上行配置BD,BD不够用次数:            %d\n",g_stIPFDebugInfo->u32UlBdNotEnough);
    IPF_PRINT("下行配置BD,BD不够用次数:            %d\n",g_stIPFDebugInfo->u32DlBdNotEnough);
    IPF_PRINT("下行配置CD,CD不够用次数:            %d\n",g_stIPFDebugInfo->u32DlCdNotEnough);

    IPF_PRINT("上行过滤规则恢复超时次数:           %d\n",g_stIPFDebugInfo->u32UlResumeTimeoutCnt);
    IPF_PRINT("下行过滤规则恢复超时次数:           %d\n",g_stIPFDebugInfo->u32DlResumeTimeoutCnt);
    IPF_PRINT("上行发送BD计数:                     %d\n",g_stIPFDebugInfo->u32UlBdNum);
    IPF_PRINT("上行配置AD0计数:                    %d\n",g_stIPFDebugInfo->u32UlAdq0Num);
    IPF_PRINT("上行配置AD1计数:                    %d\n",g_stIPFDebugInfo->u32UlAdq1Num);
    IPF_PRINT("上行接收RD计数:                     %d\n",g_stIPFDebugInfo->u32UlRdNum);
    IPF_PRINT("下行发送BD计数:                     %d\n",g_stIPFDebugInfo->u32DlBdNum);
    IPF_PRINT("下行配置AD0计数:                    %d\n",g_stIPFDebugInfo->u32DlAdq0Num);
    IPF_PRINT("下行配置AD1计数:                    %d\n",g_stIPFDebugInfo->u32DlAdq1Num);
    IPF_PRINT("下行接收RD计数:                     %d\n",g_stIPFDebugInfo->u32DlRdNum);
    IPF_PRINT("=============END============\n");

    return 0;
}

BSP_VOID BSP_IPF_MemInfo(BSP_VOID)
{
    IPF_PRINT("============BEGIN===========\n");
    IPF_PRINT("   BSP_IPF_MEM          ADDR            SIZE\n");
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_ULBD_MEM_ADDR    ", IPF_ULBD_MEM_ADDR, IPF_ULBD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_ULRD_MEM_ADDR    ", IPF_ULRD_MEM_ADDR, IPF_ULRD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLBD_MEM_ADDR    ", IPF_DLBD_MEM_ADDR, IPF_DLBD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLRD_MEM_ADDR    ", IPF_DLRD_MEM_ADDR, IPF_DLRD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLCD_MEM_ADDR    ", IPF_DLCD_MEM_ADDR, IPF_DLCD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_INIT_ADDR        ", IPF_INIT_ADDR, IPF_INIT_SIZE);
    IPF_PRINT("%20s%#x\t\t%#x\n", "IPF_DEBUG_INFO_ADDR  ", IPF_DEBUG_INFO_ADDR, IPF_DEBUG_INFO_SIZE);
    IPF_PRINT("=============END============\n");
}

BSP_S32 BSP_IPF_BDInfo(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32BdqPtr)
{
    BSP_U32 u32CdPtr;
    if(u32BdqPtr >= IPF_ULBD_DESC_SIZE)
    {
        return IPF_ERROR;
    }
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:

                IPF_PRINT("==========BD Info=========\n");
                IPF_PRINT("BD位置:         %d\n",u32BdqPtr);
                IPF_PRINT("u16Attribute:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Attribute);
                IPF_PRINT("u16PktLen:      %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16PktLen);
                IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32InPtr);
                IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
                IPF_PRINT("u16Resv:        %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Resv);
                IPF_PRINT("u16UsrField1:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
                IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
                IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
            break;
       case IPF_CHANNEL_DOWN:
                IPF_PRINT("==========BD Info=========\n");
                IPF_PRINT("BD位置:         %d\n",u32BdqPtr);
                IPF_PRINT("u16Attribute:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Attribute);
                IPF_PRINT("u16PktLen:      %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16PktLen);
                IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr);
                IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
                IPF_PRINT("u16Resv:        %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Resv);
                IPF_PRINT("u16UsrField1:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
                IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
                IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
            #ifdef PRODUCT_CFG_CORE_TYPE_MODEM
                u32CdPtr = g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr-(BSP_U32)g_stIpfDl.pstIpfCDQ;
            #else
                u32CdPtr = IO_ADDRESS(g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr)-(BSP_U32)g_stIpfDl.pstIpfCDQ;
            #endif
                u32CdPtr = u32CdPtr/sizeof(IPF_CD_DESC_S);
                while(g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u16Attribute != 1)
                {
                    IPF_PRINT("==========CD Info=========\n");
                    IPF_PRINT("CD位置:             %d\n",u32CdPtr);
                    IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u16Attribute);
                    IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u16PktLen);
                    IPF_PRINT("u32Ptr:             0x%x\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u32Ptr);
                    u32CdPtr = ((u32CdPtr+1) < IPF_DLCD_DESC_SIZE)?(u32CdPtr+1):0;
                };
                IPF_PRINT("==========CD Info=========\n");
                IPF_PRINT("CD位置:             %d\n",u32CdPtr);
                IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u16Attribute);
                IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u16PktLen);
                IPF_PRINT("u32Ptr:             0x%x\n",g_stIpfDl.pstIpfDebugCDQ[u32CdPtr].u32Ptr);
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

BSP_S32 BSP_IPF_RDInfo(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32RdqPtr)
{
    if(u32RdqPtr >= IPF_ULRD_DESC_SIZE)
    {
        return IPF_ERROR;
    }
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            IPF_PRINT("===========RD Info==========\n");
            IPF_PRINT("RD位置:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
            break;
       case IPF_CHANNEL_DOWN:
            IPF_PRINT("============RD Info===========\n");
            IPF_PRINT("RD位置:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

BSP_S32 BSP_IPF_CHInfo(IPF_CHANNEL_TYPE_E eChnType)
{
    BSP_U32 u32ChanCtrlInfo = 0;
    BSP_U32 u32ChanStateInfo = 0;

    BSP_U32 u32BdqBaseAddr = 0;
    BSP_U32 u32BdqDepth = 0;
    BSP_U32 u32BdqWptr = 0;
    BSP_U32 u32BdqRptr = 0;
    BSP_U32 u32BdqWaddr = 0;
    BSP_U32 u32BdqRaddr = 0;
    BSP_U32 u32RdqBaseAddr = 0;
    BSP_U32 u32RdqDepth = 0;
    BSP_U32 u32RdqRptr = 0;
    BSP_U32 u32RdqWptr = 0;
    BSP_U32 u32RdqWaddr = 0;
    BSP_U32 u32RdqRaddr = 0;
    BSP_U32 u32Depth = 0;

    BSP_U32 u32AdqCtrlInfo = 0;
    BSP_U32 u32Adq0BaseAddr = 0;
    BSP_U32 u32Adq0StateInfo = 0;
    BSP_U32 u32Adq0Wptr = 0;
    BSP_U32 u32Adq0Rptr = 0;
    BSP_U32 u32Adq1BaseAddr = 0;
    BSP_U32 u32Adq1StateInfo = 0;
    BSP_U32 u32Adq1Wptr = 0;
    BSP_U32 u32Adq1Rptr = 0;

    switch (eChnType) {

        case IPF_CHANNEL_UP:
            IPF_REG_READ(SOC_IPF_CH0_CTRL_ADDR(IPF_REGBASE_ADR), u32ChanCtrlInfo);
            IPF_REG_READ(SOC_IPF_CH0_STATE_ADDR(IPF_REGBASE_ADR), u32ChanStateInfo);

            IPF_REG_READ(SOC_IPF_CH0_BDQ_BADDR_ADDR(IPF_REGBASE_ADR), u32BdqBaseAddr);
            IPF_REG_READ(SOC_IPF_CH0_BDQ_SIZE_ADDR(IPF_REGBASE_ADR), u32BdqDepth);
            IPF_REG_READ(SOC_IPF_CH0_BDQ_WPTR_ADDR(IPF_REGBASE_ADR), u32BdqWptr);
            IPF_REG_READ(SOC_IPF_CH0_BDQ_RPTR_ADDR(IPF_REGBASE_ADR), u32BdqRptr);
            IPF_REG_READ(SOC_IPF_CH0_BDQ_WADDR_ADDR(IPF_REGBASE_ADR), u32BdqWaddr);
            IPF_REG_READ(SOC_IPF_CH0_BDQ_RADDR_ADDR(IPF_REGBASE_ADR), u32BdqRaddr);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_BADDR_ADDR(IPF_REGBASE_ADR), u32RdqBaseAddr);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_SIZE_ADDR(IPF_REGBASE_ADR), u32RdqDepth);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_RPTR_ADDR(IPF_REGBASE_ADR), u32RdqRptr);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_WPTR_ADDR(IPF_REGBASE_ADR), u32RdqWptr);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_WADDR_ADDR(IPF_REGBASE_ADR), u32RdqWaddr);
            IPF_REG_READ(SOC_IPF_CH0_RDQ_RADDR_ADDR(IPF_REGBASE_ADR), u32RdqRaddr);
            IPF_REG_READ(SOC_IPF_CH0_DQ_DEPTH_ADDR(IPF_REGBASE_ADR), u32Depth);

            IPF_REG_READ(SOC_IPF_CH0_ADQ_CTRL_ADDR(IPF_REGBASE_ADR), u32AdqCtrlInfo);
            IPF_REG_READ(SOC_IPF_CH0_ADQ0_BASE_ADDR(IPF_REGBASE_ADR), u32Adq0BaseAddr);
            IPF_REG_READ(SOC_IPF_CH0_ADQ0_STAT_ADDR(IPF_REGBASE_ADR), u32Adq0StateInfo);
            IPF_REG_READ(SOC_IPF_CH0_ADQ0_WPTR_ADDR(IPF_REGBASE_ADR), u32Adq0Wptr);
            IPF_REG_READ(SOC_IPF_CH0_ADQ0_RPTR_ADDR(IPF_REGBASE_ADR), u32Adq0Rptr);
            IPF_REG_READ(SOC_IPF_CH0_ADQ1_BASE_ADDR(IPF_REGBASE_ADR), u32Adq1BaseAddr);
            IPF_REG_READ(SOC_IPF_CH0_ADQ1_STAT_ADDR(IPF_REGBASE_ADR), u32Adq1StateInfo);
            IPF_REG_READ(SOC_IPF_CH0_ADQ1_WPTR_ADDR(IPF_REGBASE_ADR), u32Adq1Wptr);
            IPF_REG_READ(SOC_IPF_CH0_ADQ1_RPTR_ADDR(IPF_REGBASE_ADR), u32Adq1Rptr);
            break;

        case IPF_CHANNEL_DOWN:
            IPF_REG_READ(SOC_IPF_CH1_CTRL_ADDR(IPF_REGBASE_ADR), u32ChanCtrlInfo);
            IPF_REG_READ(SOC_IPF_CH1_STATE_ADDR(IPF_REGBASE_ADR), u32ChanStateInfo);

            IPF_REG_READ(SOC_IPF_CH1_BDQ_BADDR_ADDR(IPF_REGBASE_ADR), u32BdqBaseAddr);
            IPF_REG_READ(SOC_IPF_CH1_BDQ_SIZE_ADDR(IPF_REGBASE_ADR), u32BdqDepth);
            IPF_REG_READ(SOC_IPF_CH1_BDQ_WPTR_ADDR(IPF_REGBASE_ADR), u32BdqWptr);
            IPF_REG_READ(SOC_IPF_CH1_BDQ_RPTR_ADDR(IPF_REGBASE_ADR), u32BdqRptr);
            IPF_REG_READ(SOC_IPF_CH1_BDQ_WADDR_ADDR(IPF_REGBASE_ADR), u32BdqWaddr);
            IPF_REG_READ(SOC_IPF_CH1_BDQ_RADDR_ADDR(IPF_REGBASE_ADR), u32BdqRaddr);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_BADDR_ADDR(IPF_REGBASE_ADR), u32RdqBaseAddr);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_SIZE_ADDR(IPF_REGBASE_ADR), u32RdqDepth);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_RPTR_ADDR(IPF_REGBASE_ADR), u32RdqRptr);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_WPTR_ADDR(IPF_REGBASE_ADR), u32RdqWptr);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_WADDR_ADDR(IPF_REGBASE_ADR), u32RdqWaddr);
            IPF_REG_READ(SOC_IPF_CH1_RDQ_RADDR_ADDR(IPF_REGBASE_ADR), u32RdqRaddr);
            IPF_REG_READ(SOC_IPF_CH1_DQ_DEPTH_ADDR(IPF_REGBASE_ADR), u32Depth);

            IPF_REG_READ(SOC_IPF_CH1_ADQ_CTRL_ADDR(IPF_REGBASE_ADR), u32AdqCtrlInfo);
            IPF_REG_READ(SOC_IPF_CH1_ADQ0_BASE_ADDR(IPF_REGBASE_ADR), u32Adq0BaseAddr);
            IPF_REG_READ(SOC_IPF_CH1_ADQ0_STAT_ADDR(IPF_REGBASE_ADR), u32Adq0StateInfo);
            IPF_REG_READ(SOC_IPF_CH1_ADQ0_WPTR_ADDR(IPF_REGBASE_ADR), u32Adq0Wptr);
            IPF_REG_READ(SOC_IPF_CH1_ADQ0_RPTR_ADDR(IPF_REGBASE_ADR), u32Adq0Rptr);
            IPF_REG_READ(SOC_IPF_CH1_ADQ1_BASE_ADDR(IPF_REGBASE_ADR), u32Adq1BaseAddr);
            IPF_REG_READ(SOC_IPF_CH1_ADQ1_STAT_ADDR(IPF_REGBASE_ADR), u32Adq1StateInfo);
            IPF_REG_READ(SOC_IPF_CH1_ADQ1_WPTR_ADDR(IPF_REGBASE_ADR), u32Adq1Wptr);
            IPF_REG_READ(SOC_IPF_CH1_ADQ1_RPTR_ADDR(IPF_REGBASE_ADR), u32Adq1Rptr);
            break;

        default:
            IPF_PRINT("invalidable channel type \n");
            break;
    }

    IPF_PRINT("============BEGIN===========\n");
    IPF_PRINT("通道控制寄存器:     0x%x\n", u32ChanCtrlInfo);
    IPF_PRINT("通道状态寄存器:     0x%x\n", u32ChanStateInfo);

    IPF_PRINT("BD 基地址:          0x%x\n", u32BdqBaseAddr);
    IPF_PRINT("BD 深度:            0x%x\n", u32BdqDepth);
    IPF_PRINT("BD 写指针:          0x%x\n", u32BdqWptr);
    IPF_PRINT("BD 读指针:          0x%x\n", u32BdqRptr);
    IPF_PRINT("BD 写地址:          0x%x\n", u32BdqWaddr);
    IPF_PRINT("BD 读地址:          0x%x\n", u32BdqRaddr);
    IPF_PRINT("RD 基地址:          0x%x\n", u32RdqBaseAddr);
    IPF_PRINT("RD 深度:            0x%x\n", u32RdqDepth);
    IPF_PRINT("RD 读指针:          0x%x\n", u32RdqRptr);
    IPF_PRINT("RD 写指针:          0x%x\n", u32RdqWptr);
    IPF_PRINT("RD 读地址:          0x%x\n", u32RdqRaddr);
    IPF_PRINT("RD 写地址:          0x%x\n", u32RdqWaddr);
    IPF_PRINT("通道深度寄存器:     0x%x\n", u32Depth);

    IPF_PRINT("ADQ控制寄存器:      0x%x\n", u32AdqCtrlInfo);
    IPF_PRINT("ADQ0 基地址:          0x%x\n", u32Adq0BaseAddr);
    IPF_PRINT("ADQ0 状态寄存器:          0x%x\n", u32Adq0StateInfo);
    IPF_PRINT("ADQ0 写指针:            0x%x\n", u32Adq0Wptr);
    IPF_PRINT("ADQ0 读指针:          0x%x\n", u32Adq0Rptr);
    IPF_PRINT("ADQ1 基地址:          0x%x\n", u32Adq1BaseAddr);
    IPF_PRINT("ADQ1 状态寄存器:          0x%x\n", u32Adq1StateInfo);
    IPF_PRINT("ADQ1 写指针:            0x%x\n", u32Adq1Wptr);
    IPF_PRINT("ADQ1 读指针:          0x%x\n", u32Adq1Rptr);
    IPF_PRINT("=============END============\n");
    return 0;
}

#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
/*****************************************************************************
* 函 数 名  : BSP_IPF_UseFilterInfo
*
* 功能描述  : 提供的debug接口，获取已经使用的filter号
*
* 输入参数  : eFilterChainhead  通道过滤器链组号
*
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
              2011年3月30日   鲁婷  修改
*****************************************************************************/
BSP_VOID BSP_IPF_UseFilterInfo(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    IPF_ID_S* current = (IPF_ID_S*)BSP_NULL;
    BSP_U32 u32FilterNum = 0;
    BSP_S32 s32GetChar = 0;
    BSP_U32 u32cyc = 10;

    u32FilterNum = g_stIPFFilterInfo[eFilterChainhead].u32FilterNum;
    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;

    IPF_PRINT("============BEGIN===========\n");
    while(u32FilterNum)
    {
        while(u32cyc&&u32FilterNum)
        {
            IPF_PRINT("Filter ID = %d,    PS ID = %d\n",current->u32FilterID, current->u32PsID);
            current = current->pstNext;
            u32FilterNum--;
            u32cyc--;
        }
        if(u32FilterNum > 0)
        {
            IPF_PRINT("\npress \'Enter\' to continue, press \'q\' to stop\n");
            s32GetChar = getchar();
            if ('q' == s32GetChar)
            {
                break;
            }
            u32cyc = 10;
        }
        else
        {
            break;
        }
    }
    IPF_PRINT("=============END============\n");
}

/*****************************************************************************
* 函 数 名  : BSP_IPF_FreeFilterInfo
*
* 功能描述  : 提供的debug接口，获取未使用的filter号
*
* 输入参数  :
*
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
*
*****************************************************************************/
BSP_VOID BSP_IPF_FreeFilterInfo(BSP_VOID)
{
    IPF_ID_S* current = (IPF_ID_S*)BSP_NULL;
    BSP_S32 s32GetChar = 0;
    BSP_U32 u32cyc = 10;

    current = g_stIPFBasicFreeList;

    IPF_PRINT("============BEGIN===========\n");
    while(current != BSP_NULL)
    {
        while(u32cyc&&(current != BSP_NULL))
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext;
            u32cyc--;
        }
        IPF_PRINT("\npress \'Enter\' to continue, press \'q\' to stop\n");
        s32GetChar = getchar();
        if ('q' == s32GetChar)
        {
            break;
        }
        u32cyc = 10;
    }
    IPF_PRINT("=============END============\n");
}

BSP_VOID BSP_IPF_FilterInfo(BSP_U32 u32FilterID)
{
    IPF_MATCH_INFO_S stMatchInfo = {0};

    if(u32FilterID < IPF_BF_NUM)
    {
         /* 写过滤表操作地址 */
        IPF_REG_WRITE(SOC_IPF_BFLT_INDEX_ADDR(IPF_REGBASE_ADR), u32FilterID);

        /* 读出过滤器的配置 */
        memcpy(&stMatchInfo, (BSP_VOID*)SOC_IPF_FLT_LOCAL_ADDR0_ADDR(IPF_REGBASE_ADR), sizeof(IPF_MATCH_INFO_S));
    }
    else
    {
        memcpy(&stMatchInfo, (BSP_VOID*)(g_pstExFilterAddr + u32FilterID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }

    IPF_PRINT("src ADDR0 :      %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[0], stMatchInfo.u8SrcAddr[1], stMatchInfo.u8SrcAddr[2], stMatchInfo.u8SrcAddr[3]);
    IPF_PRINT("src ADDR1 :      %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[4], stMatchInfo.u8SrcAddr[5], stMatchInfo.u8SrcAddr[6], stMatchInfo.u8SrcAddr[7]);
    IPF_PRINT("src ADDR2 :      %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[8], stMatchInfo.u8SrcAddr[9], stMatchInfo.u8SrcAddr[10], stMatchInfo.u8SrcAddr[11]);
    IPF_PRINT("src ADDR3 :      %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[12], stMatchInfo.u8SrcAddr[13], stMatchInfo.u8SrcAddr[14], stMatchInfo.u8SrcAddr[15]);
    IPF_PRINT("dst ADDR0 :      %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[0], stMatchInfo.u8DstAddr[1], stMatchInfo.u8DstAddr[2], stMatchInfo.u8DstAddr[3]);
    IPF_PRINT("dst ADDR1 :      %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[4], stMatchInfo.u8DstAddr[5], stMatchInfo.u8DstAddr[6], stMatchInfo.u8DstAddr[7]);
    IPF_PRINT("dst ADDR2 :      %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[8], stMatchInfo.u8DstAddr[9], stMatchInfo.u8DstAddr[10], stMatchInfo.u8DstAddr[11]);
    IPF_PRINT("dst ADDR3 :      %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[12], stMatchInfo.u8DstAddr[13], stMatchInfo.u8DstAddr[14], stMatchInfo.u8DstAddr[15]);
    IPF_PRINT("dst MASK0 :      %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[0], stMatchInfo.u8DstMsk[1], stMatchInfo.u8DstMsk[2], stMatchInfo.u8DstMsk[3]);
    IPF_PRINT("dst MASK1 :      %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[4], stMatchInfo.u8DstMsk[5], stMatchInfo.u8DstMsk[6], stMatchInfo.u8DstMsk[7]);
    IPF_PRINT("dst MASK2 :      %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[8], stMatchInfo.u8DstMsk[9], stMatchInfo.u8DstMsk[10], stMatchInfo.u8DstMsk[11]);
    IPF_PRINT("dst MASK3 :      %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[12], stMatchInfo.u8DstMsk[13], stMatchInfo.u8DstMsk[14], stMatchInfo.u8DstMsk[15]);
    IPF_PRINT("SrcPort   :      %x\n", stMatchInfo.unSrcPort.u32SrcPort);
    IPF_PRINT("DstPort   :      %x\n", stMatchInfo.unDstPort.u32DstPort);
    IPF_PRINT("TrafficClass :   %x\n", stMatchInfo.unTrafficClass.u32TrafficClass);
    IPF_PRINT("local MASK:      %d\n", stMatchInfo.u32LocalAddressMsk);
    IPF_PRINT("Protocol  :      %x\n", stMatchInfo.unNextHeader.u32Protocol);
    IPF_PRINT("FlowLable :      %x\n", stMatchInfo.u32FlowLable);
    IPF_PRINT("CodeType  :      %x\n", stMatchInfo.unFltCodeType.u32CodeType);
    IPF_PRINT("NextIndex : %d  FltPri: %d\n", stMatchInfo.unFltChain.Bits.u16NextIndex, stMatchInfo.unFltChain.Bits.u16FltPri);
    IPF_PRINT("FltSpi :             %d\n", stMatchInfo.u32FltSpi);
    IPF_PRINT("FltRuleCtrl :        %x\n", stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl);
    IPF_PRINT("============================\n");
}

BSP_VOID BSP_IPF_FilterChainInfo(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    BSP_U32 u32FilterNum = g_stIPFFilterInfo[eFilterChainhead].u32FilterNum;
    IPF_ID_S* current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;

    IPF_PRINT("FilterChainId :      %d\n", eFilterChainhead);
    IPF_PRINT("============BEGIN===========\n");
    while(u32FilterNum)
    {
        IPF_PRINT("PsID :      %d\n", current->u32PsID);
        BSP_IPF_FilterInfo(current->u32FilterID);
        current = current->pstNext;
        u32FilterNum--;
    }
    IPF_PRINT("=============END============\n");
}
#endif

#ifndef PRODUCT_CFG_CORE_TYPE_MODEM
EXPORT_SYMBOL(BSP_IPF_Help);
EXPORT_SYMBOL(BSP_IPF_RegDump);
EXPORT_SYMBOL(BSP_IPF_DbgInfo);
EXPORT_SYMBOL(BSP_IPF_MemInfo);
EXPORT_SYMBOL(BSP_IPF_BDInfo);
EXPORT_SYMBOL(BSP_IPF_RDInfo);
EXPORT_SYMBOL(BSP_IPF_CHInfo);
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

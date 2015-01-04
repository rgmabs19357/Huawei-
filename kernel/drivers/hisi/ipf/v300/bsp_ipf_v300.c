/*************************************************************************
*   版权所有(C) 1987-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_IPF.c
*
*   作    者 :  luting
*
*   描    述 :  本文主要完成IP过滤接口函数，实现上行和下行的IP过滤功能
*
*   修改记录 :  2011年1月11日  v1.00  luting  创建
*
*************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#if (FEATURE_IPF_VERSION == IPF_V300)
#ifdef __VXWORKS__
#include <vxWorks.h>
#include <cacheLib.h>
#include <intLib.h>
#include <logLib.h>
#include <string.h>
#include <taskLib.h>
#include <memLib.h>
#include <config.h>
#include <stdio.h>
#include <stdlib.h>

#include "arm_pbxa9.h"
#include "product_config.h"
#include "BSP_GLOBAL.h"
#include "BSP_MEMORY.h"
#include "BSP.h"
#include "BSP_IPF.h"
#include "BSP_DRV_IPF_V300.h"
#else 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/string.h>
#include "BSP.h"
#include "BSP_IPF.h"
#include "bsp_drv_ipf_v300.h"
#endif

/* 变量定义 */
IPF_UL_S g_stIpfUl = {0};
IPF_DL_S g_stIpfDl = {0};
/* 结构体定义 */
IPF_DEBUG_INFO_S* g_stIPFDebugInfo = BSP_NULL;
BSP_U32* g_pbIPFInit = BSP_NULL;

#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
    IPF_MATCH_INFO_S* g_pstExFilterAddr;
    IPF_ID_S* g_stIPFFreeList = BSP_NULL;
    IPF_FILTER_INFO_S g_stIPFFilterInfo[IPF_CHANNEL_MAX];
#endif

/* 内部函数申明 */
#ifdef __KERNEL__
irqreturn_t  IPF_IntHandler (int irq, void* dev);
#else
BSP_VOID IPF_IntHandler(BSP_VOID);
#endif
BSP_VOID IPF_Int_Connect(BSP_VOID);


/* UT测试用例寄存器读接口打桩 */
#ifdef _DRV_LLT_
BSP_VOID BSP_IPF_RegRead(BSP_U32 base, BSP_U32 reg,BSP_U32* result)
{
    /* DO NOTHING */
}
#endif
/*****************************************************************************
* 函 数 名      : IPF_Init
*
* 功能描述  : IPF初始化     内部使用，不作为接口函数
*
* 输入参数  : BSP_VOID
* 输出参数  : 无
* 返 回 值     : IPF_SUCCESS    初始化成功
*                           IPF_ERROR      初始化失败
*
* 修改记录  :2011年1月21日   鲁婷  创建
*****************************************************************************/
#ifdef __KERNEL__
BSP_S32 IPF_Init(BSP_VOID)
#else
BSP_S32 IPF_Init(BSP_VOID)
#endif
{
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
    BSP_U32 u32IntMask0 = 0;
    BSP_U32 u32IntMask1 = 0;
    BSP_U32 u32ChanCtrl[IPF_CHANNEL_MAX] = {0,0};
    BSP_U32 u32IntStatus = 0;
    BSP_U32 u32Timeout = 0;
    BSP_U32 u32BDSize[IPF_CHANNEL_MAX] = {IPF_ULBD_DESC_SIZE, IPF_ULRD_DESC_SIZE};
    BSP_U32 u32RDSize[IPF_CHANNEL_MAX] = {IPF_DLBD_DESC_SIZE, IPF_DLRD_DESC_SIZE};
    BSP_U32 i = 0;

    /* 初始化全局结构体 */
    memset((BSP_VOID*)MEMORY_AXI_IPF_ADDR, 0x0, MEMORY_AXI_IPF_SIZE);
    
    g_pbIPFInit = (BSP_U32*)IPF_INIT_ADDR;
    
    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (BSP_U32*)IPF_ULBD_IDLENUM_ADDR;
    *(BSP_U32*)IPF_ULBD_IDLENUM_ADDR = IPF_ULBD_DESC_SIZE;
    
    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;
    g_stIpfDl.u32IpfCdRptr = (BSP_U32*)IPF_DLCD_PTR_ADDR;
    g_stIpfDl.u32IpfCdWptr = (BSP_U32*)(IPF_DLCD_PTR_ADDR+4);
    #ifdef __BSP_IPF_DEBUG__
    g_stIpfDl.pstIpfDebugCDQ = (IPF_CD_DESC_S*)IPF_DEBUG_DLCD_ADDR;
    #endif
    g_stIpfDl.u32IdleBd = IPF_DLBD_DESC_SIZE;

    g_stIPFDebugInfo = (IPF_DEBUG_INFO_S*)IPF_DEBUG_INFO_ADDR;

    /* 申请扩展过滤器的内存, 配置扩展过滤器的基址 */
    g_pstExFilterAddr = (IPF_MATCH_INFO_S*)cacheDmaMalloc(EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S));
    memset((BSP_VOID*)g_pstExFilterAddr, 0x0, EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S));
    
    /* 配置扩展过滤器的起始地址 */
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_EF_BADDR, (BSP_U32)g_pstExFilterAddr);

    /* 初始化过滤器链表 */
    if(IPF_FilterList_Init() != IPF_SUCCESS)
    {
        IPF_PRINT( "\r IPF_Init malloc list ERROR! \n");
        goto FREE_ERROR;
    }
    
    /* 配置超时配置寄存器，使能超时中断，设置超时时间 */
    u32Timeout = TIME_OUT_CFG | (1<<16);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_TIME_OUT, u32Timeout);

    for(i = 0; i < IPF_CHANNEL_MAX; i++)
    {
        /* 清除上下行队列 */
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_CTRL(i), u32ChanCtrl[i]);
        u32ChanCtrl[i] |= 0x30;
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(i), u32ChanCtrl[i]);

        /* 配置上下行通道的BD和RD深度 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_BDQ_SIZE(i), u32BDSize[i]-1);
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_RDQ_SIZE(i), u32RDSize[i]-1);
    }

    /* 上行和下行通道的BD和RD起始地址*/    
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_BDQ_BADDR(IPF_CHANNEL_UP), (BSP_U32)g_stIpfUl.pstIpfBDQ);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_RDQ_BADDR(IPF_CHANNEL_UP), (BSP_U32)g_stIpfUl.pstIpfRDQ);
    
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_BDQ_BADDR(IPF_CHANNEL_DOWN), (BSP_U32)g_stIpfDl.pstIpfBDQ);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_RDQ_BADDR(IPF_CHANNEL_DOWN), (BSP_U32)g_stIpfDl.pstIpfRDQ);
    
    /* 配置中断屏蔽,只开3个中断，结果上报，结果超时，RD下溢 */
    u32IntMask0 = IPF_INT_OPEN0;  /* 0号为Modem CPU */
    u32IntMask1 = IPF_INT_OPEN1;
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_MASK0, u32IntMask0);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_MASK1, u32IntMask1);

    /* 清中断 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_INT_STATE, u32IntStatus);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_STATE, u32IntStatus);

    IPF_Int_Connect();

    *g_pbIPFInit = BSP_TRUE;
    BSP_SYNC_Give(SYNC_MODULE_IPF);
    
    return IPF_SUCCESS;
    
FREE_ERROR:
    IPF_PRINT( "\r IPF_Init malloc ERROR! \n");
    return IPF_ERROR;
#else
    BSP_S32 s32Ret = 0;

    g_pbIPFInit = (BSP_U32*)IPF_INIT_ADDR;

    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (BSP_U32*)IPF_ULBD_IDLENUM_ADDR;

    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;
    g_stIpfDl.u32IpfCdRptr = (BSP_U32*)IPF_DLCD_PTR_ADDR;
    g_stIpfDl.u32IpfCdWptr = (BSP_U32*)(IPF_DLCD_PTR_ADDR+4);
    #ifdef __BSP_IPF_DEBUG__
    g_stIpfDl.pstIpfDebugCDQ = (IPF_CD_DESC_S*)IPF_DEBUG_DLCD_ADDR;
    #endif

    g_stIPFDebugInfo = (IPF_DEBUG_INFO_S*)IPF_DEBUG_INFO_ADDR;

    IPF_Int_Connect();

    s32Ret = BSP_SYNC_Wait(SYNC_MODULE_IPF, 5000);
    if(s32Ret != BSP_OK)
    {
        IPF_PRINT( "\r IPF BSP_SYNC_Wait error! \n");
        return IPF_ERROR;
    }

    return IPF_SUCCESS;

#endif
}

/*****************************************************************************
* 函 数 名     : IPF_Int_Connect
*
* 功能描述  : 挂IPF中断处理函数(两核都提供)
*
* 输入参数  : BSP_VOID
* 输出参数  : 无
* 返 回 值      : 无
*
* 修改记录  :2011年12月2日   鲁婷  创建
*****************************************************************************/
BSP_VOID IPF_Int_Connect(BSP_VOID)
{
#ifdef __VXWORKS__
    /* 挂中断使能 */
    (BSP_VOID)BSP_INT_Connect((VOIDFUNCPTR *)(INT_VEC_IPF), (VOIDFUNCPTR)IPF_IntHandler, 0);    
    /* 使能中断号 */
    (BSP_VOID)BSP_INT_Enable(INT_LVL_IPF);        
#elif defined(__KERNEL__)
    /* 挂中断使能 */
    /* 使能中断号 */

    if(request_irq(INT_LVL_IPF, (irq_handler_t)IPF_IntHandler, 0, "IPF_APP_IRQ", NULL) != 0)
    {
        IPF_PRINT("irequest_irq error\n");
    }
#endif
}

/*****************************************************************************
* 函 数 名  : IPF_IntHandler
*
* 功能描述  : IPF中断处理函数
*
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  :2011年1月24日   鲁婷  创建
*****************************************************************************/
#ifdef __KERNEL__
irqreturn_t  IPF_IntHandler (int irq, void* dev)
#else
BSP_VOID IPF_IntHandler(BSP_VOID)
#endif
{
    BSP_U32 u32IntStatus = 0;
    BSP_U32 u32IpfInt = 0;

    /* 读取中断状态 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM    
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_INT0, u32IpfInt); 
    /* 上行结果上报和结果超时上报 */
    if(u32IpfInt&0x3)
    {
        /* 写1清除上行结果和结果超时中断 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_STATE, (IPF_UL_RPT_INT | IPF_UL_TIMEOUT_INT));        
        /* 唤醒ps上行任务 */
        if(g_stIpfUl.pFnUlIntCb != BSP_NULL)
        {
            (BSP_VOID)g_stIpfUl.pFnUlIntCb();
        }
        else
        {
            IPF_PRINT( "\r IPF_IntHandler ULTASK NULL! \n",0,0,0,0,0,0);
        }
    }
    /* 上行BDQ上溢指示 */
    if(u32IpfInt&0x80)
    {
        /* 写1清除上行结果和结果超时中断 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_STATE, IPF_UL_BDQ_UP_OVERFLOW_INT);
        g_stIPFDebugInfo->u32UlBdqOverflow++;
    }
#else
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_INT1, u32IpfInt); 
    /* 下行结果上报和结果超时上报 */
    if(u32IpfInt&0x30000)
    {
        /* 写1清除上行结果和结果超时中断 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_STATE, (IPF_DL_RPT_INT | IPF_DL_TIMEOUT_INT));            
        /* 唤醒ps下行任务 */
        if(g_stIpfDl.pFnDlIntCb != BSP_NULL)
        {
            (BSP_VOID)g_stIpfDl.pFnDlIntCb();  
        }
        else
        {
            IPF_PRINT( "\r IPF_IntHandler DLTASK NULL! \n",0,0,0,0,0,0);
        }
    } 
    /* 下行BDQ上溢指示 */
    if(u32IpfInt&0x800000)
    {
        /* 写1清除上行结果和结果超时中断 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_INT_STATE, IPF_DL_BDQ_UP_OVERFLOW_INT);    
        g_stIPFDebugInfo->u32DlBdqOverflow++;
    }

    return IRQ_HANDLED;
#endif
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_ConfigTimeout
*
* 功能描述  : 调试使用，配置超时时间接口
*
* 输入参数  : BSP_U32 u32Timeout 配置的超时时间
* 输出参数  : 无
* 返 回 值     : IPF_SUCCESS    成功
*                           BSP_ERR_IPF_INVALID_PARA      参数无效
*
* 说明              : 1代表256个时钟周期
*
* 修改记录   : 2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_ConfigTimeout(BSP_U32 u32Timeout)
{
    if((u32Timeout == 0) || (u32Timeout > 0xFFFF))
    {
        IPF_PRINT( "\r BSP_IPF_ConfigTimeout u32Timeout ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    u32Timeout |= (1<<16);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_TIME_OUT, u32Timeout);
    
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_ConfigUpFilter
*
* 功能描述  : IPF上行IP过滤函数 
*
* 输入参数  : BSP_U32 u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara, BSP_BOOL bintFlag
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS    配置成功
*                           IPF_ERROR      配置失败
*                           BSP_ERR_IPF_NOT_INIT         模块未初始化
*                           BSP_ERR_IPF_INVALID_PARA     参数错误
*
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_ConfigUpFilter(BSP_U32 u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara, BSP_BOOL bintFlag)
{
    BSP_U32 u32BdqWptr = 0;
    IPF_CONFIG_ULPARAM_S* pstUlParam = pstUlPara;
    BSP_U32 u32BD = 0;
    BSP_U32 u32LastBd = 0;
    BSP_U32 i = 0;

    /* 参数检查 */
    if((NULL == pstUlPara))
    {
        IPF_PRINT( "\r BSP_IPF_ConfigUpFilter pInfoNode NULL! \n",0,0,0,0,0,0);
        return BSP_ERR_IPF_INVALID_PARA;
    }

    /* 检查模块是否初始化 */
    if(!(*g_pbIPFInit))
    {
        IPF_PRINT( "\r IPF Not Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    #ifdef __BSP_IPF_DEBUG__
    if(u32Num > *(g_stIpfUl.pu32IdleBd))
    {
        g_stIPFDebugInfo->u32UlBdNotEnough++;
        return IPF_ERROR;
    }
    #endif

    /* 读出BD写指针,将u32BdqWptr作为临时写指针使用 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(IPF_CHANNEL_UP), u32BdqWptr); 

    u32BD = u32BdqWptr;
    for(i = 0; i < u32Num; i++)
    {
        g_stIpfUl.pstIpfBDQ[u32BD].u16Attribute = 0;
        g_stIpfUl.pstIpfBDQ[u32BD].u32InPtr = pstUlParam[i].u32Data;
        g_stIpfUl.pstIpfBDQ[u32BD].u32OutPtr = pstUlParam[i].u32DesAddr;
        g_stIpfUl.pstIpfBDQ[u32BD].u16PktLen = pstUlParam[i].u16Len;
        g_stIpfUl.pstIpfBDQ[u32BD].u16UsrField1 = pstUlParam[i].u16UsrField1;
        g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField2= pstUlParam[i].u32UsrField2;
        g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField3 = pstUlParam[i].u32UsrField3;
        #ifdef __BSP_IPF_DEBUG__
        if(g_stIPFDebugInfo->u32IpfDebug)
        {
            IPF_PRINT(" func: %d  %x, %d\n", u32BD, g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField2,g_stIpfUl.pstIpfBDQ[u32BD].u32UsrField3);
        }
        #endif
        u32BD = ((u32BD + 1) < IPF_ULBD_DESC_SIZE)? (u32BD + 1) : 0;
    }
    
    if((u32BdqWptr+u32Num-1) < IPF_ULBD_DESC_SIZE)
    {
        u32LastBd = u32BdqWptr+u32Num-1;
    }
    else
    {
        u32LastBd = u32BdqWptr+u32Num-1 - IPF_ULBD_DESC_SIZE;
    }
    g_stIpfUl.pstIpfBDQ[u32LastBd].u16Attribute = bintFlag;
    
    /* 更新BD写指针*/
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(IPF_CHANNEL_UP), u32BD);  

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetUlBDNum
*
* 功能描述  : 该接口用于获取上行空闲BD 数目
*                            范围: 0~64
* 输入参数  : 无
*
* 输出参数  : 无
* 返 回 值      : 空闲BD数目
*  
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_U32 BSP_IPF_GetUlBDNum(BSP_VOID)
{
    BSP_U32 u32UlBdDepth = 0;
    BSP_U32 u32IdleBd = 0;

    /* 计算空闲BD数量 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_UP), u32UlBdDepth);
    u32IdleBd = IPF_ULBD_DESC_SIZE - (u32UlBdDepth & 0x1FF);
    *(g_stIpfUl.pu32IdleBd) = u32IdleBd;
    
    return u32IdleBd;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_UlStateIdle
*
* 功能描述  : 该接口用于获取上行通道是否为空闲
*                            
* 输入参数  : 无
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS  表示上行空闲，可以切换模式
*                            IPF_ERROR      表示上行非空闲，不可以切换模式
*  
* 修改记录  :2011年12月9日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_UlStateIdle(BSP_VOID)
{
    BSP_U32 u32UlState = 0;
    
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_STATE(IPF_CHANNEL_UP), u32UlState);

    if(u32UlState != 0x14)
    {
        return IPF_ERROR;
    }

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_PktLen
*
* 功能描述  : 该接口用来配置过滤器的最大和最小包长
*
* 输入参数  : BSP_U32 MaxLen   最大包长
*                           BSP_U32 MinLen   最小包长
*
* 输出参数   : 无
* 返 回 值      : IPF_SUCCESS                成功
*                           BSP_ERR_IPF_INVALID_PARA   参数错误(最大包长比最小包长小)
*
* 修改记录  :2011年2月17日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_SetPktLen(BSP_U32 u32MaxLen, BSP_U32 u32MinLen)
{
    BSP_U32 u32PktLen = 0;

    /* 参数检查 */
    if(u32MaxLen < u32MinLen)
    {
        IPF_PRINT( "\r BSP_IPF_PktLen input error! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    u32PktLen = ((u32MaxLen&0x3FFF)<<16) | (u32MinLen&0x3FFF);
    
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_PKT_LEN, u32PktLen);
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名  : BSP_IPF_GetStat
*
* 功能描述  : 该接口获取统计计数器的值
*
* 输入参数  : IPF_FILTER_STAT_S *pstFilterStat 统计计数结构体指针
*             
*
* 输出参数  : 无
* 返 回 值  : IPF_SUCCESS                成功
*             BSP_ERR_IPF_INVALID_PARA   参数错误
*
* 修改记录  :2011年2月17日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_GetStat(IPF_FILTER_STAT_S *pstFilterStat)
{
    /* 参数检查 */
    if(BSP_NULL == pstFilterStat)
    {
        IPF_PRINT( "\r BSP_IPF_GetStat input error ! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_UL_CNT0, pstFilterStat->u32UlCnt0); 
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_UL_CNT1, pstFilterStat->u32UlCnt1);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_UL_CNT2, pstFilterStat->u32UlCnt2);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_DL_CNT0, pstFilterStat->u32DlCnt0);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_DL_CNT1, pstFilterStat->u32DlCnt1);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_DL_CNT2, pstFilterStat->u32DlCnt2);
    return IPF_SUCCESS;
}

/**********************************可维可测接口函数************************************/
BSP_VOID BSP_IPF_Help(BSP_VOID)
{
    IPF_PRINT("===============================================\n");
    IPF_PRINT("BSP_IPF_Info    参数1:通道类型  0为上行，1为下行\n");
    IPF_PRINT("BSP_IPF_BDInfo  参数1:通道类型  参数2:BD指针\n");
    IPF_PRINT("BSP_IPF_RDInfo  参数1:通道类型  参数2:RD指针\n"); 
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM    
    IPF_PRINT("===============================================\n");
    IPF_PRINT("BSP_IPF_UseFilterInfo  参数1:通道类型\n"); 
    IPF_PRINT("BSP_IPF_FreeFilterInfo\n"); 
    IPF_PRINT("BSP_IPF_FilterInfoHWID  参数1:硬件Filter ID\n");
    IPF_PRINT("BSP_IPF_FilterInfoPSID  参数1 :PS Filter ID\n");
#endif
    IPF_PRINT("===============================================\n");
    IPF_PRINT("上行配置BD,BD不够用次数:            %d\n",g_stIPFDebugInfo->u32UlBdNotEnough);
    IPF_PRINT("下行配置BD,BD不够用次数:            %d\n",g_stIPFDebugInfo->u32DlBdNotEnough);
    IPF_PRINT("下行配置CD,CD不够用次数:            %d\n",g_stIPFDebugInfo->u32DlCdNotEnough);
    IPF_PRINT("中断上报上行BD队列溢出次数:         %d\n",g_stIPFDebugInfo->u32UlBdqOverflow);
    IPF_PRINT("中断上报下行BD队列溢出次数:         %d\n",g_stIPFDebugInfo->u32DlBdqOverflow);
    IPF_PRINT("===============================================\n");
}

BSP_S32 BSP_IPF_BDInfo(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32BdqPtr)
{
#ifdef __BSP_IPF_DEBUG__
    BSP_U32 u32CdPtr;
#endif
      
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
                if(u32BdqPtr >= IPF_ULBD_DESC_SIZE)
                {
                    return IPF_ERROR;
                }
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
                if(u32BdqPtr >= IPF_DLBD_DESC_SIZE)
                {
                    return IPF_ERROR;
                }
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
                #ifdef __BSP_IPF_DEBUG__
                #ifdef __VXWORKS__
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
                #endif
            break; 
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

BSP_S32 BSP_IPF_RDInfo(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32RdqPtr)
{     
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32RdqPtr >= IPF_ULRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
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
            if(u32RdqPtr >= IPF_DLRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
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
BSP_S32 BSP_IPF_Info(IPF_CHANNEL_TYPE_E eChnType)
{
    BSP_U32 u32BdqDepth = 0;
    BSP_U32 u32BdqWptr = 0;
    BSP_U32 u32BdqRptr = 0;
    BSP_U32 u32BdqWaddr = 0;
    BSP_U32 u32BdqRaddr = 0;
    BSP_U32 u32RdqDepth = 0;
    BSP_U32 u32RdqRptr = 0;
    BSP_U32 u32RdqWptr = 0;
    BSP_U32 u32RdqWaddr = 0;
    BSP_U32 u32RdqRaddr = 0;
    BSP_U32 u32Depth = 0;

    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(eChnType), u32Depth);
    u32RdqDepth = (u32Depth>>16)&0x1FF;
    u32BdqDepth = u32Depth&0x1FF;
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(eChnType), u32BdqWptr); 
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_RPTR(eChnType), u32BdqRptr); 
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_WADDR(eChnType), u32BdqWaddr); 
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_RADDR(eChnType), u32BdqRaddr); 

    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_RPTR(eChnType), u32RdqRptr);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_WPTR(eChnType), u32RdqWptr);
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_WADDR(eChnType), u32RdqWaddr); 
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_RADDR(eChnType), u32RdqRaddr); 

    IPF_PRINT("============================\n");
    IPF_PRINT("BD 深度:            %d\n", u32BdqDepth);
    IPF_PRINT("BD 写指针:          %d\n", u32BdqWptr);
    IPF_PRINT("BD 读指针:          %d\n", u32BdqRptr);
    IPF_PRINT("BD 写地址:          0x%x\n", u32BdqWaddr);
    IPF_PRINT("BD 读地址:          0x%x\n", u32BdqRaddr);
    IPF_PRINT("RD 深度:            %d\n", u32RdqDepth);
    IPF_PRINT("RD 读指针:          %d\n", u32RdqRptr);
    IPF_PRINT("RD 写指针:          %d\n", u32RdqWptr);
    IPF_PRINT("RD 读地址:          0x%x\n", u32RdqRaddr);
    IPF_PRINT("RD 写地址:          0x%x\n", u32RdqWaddr);
    IPF_PRINT("============================\n");   
    return 0;
}

BSP_VOID BSP_IPF_MEM(BSP_VOID)
{
    IPF_PRINT("=======================================\n");
    IPF_PRINT("   BSP_IPF_MEM          ADDR            SIZE\n");
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_ULBD_MEM_ADDR    ", IPF_ULBD_MEM_ADDR, IPF_ULBD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_ULRD_MEM_ADDR    ", IPF_ULRD_MEM_ADDR, IPF_ULRD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLBD_MEM_ADDR    ", IPF_DLBD_MEM_ADDR, IPF_DLBD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLRD_MEM_ADDR    ", IPF_DLRD_MEM_ADDR, IPF_DLRD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_DLCD_MEM_ADDR    ", IPF_DLCD_MEM_ADDR, IPF_DLCD_MEM_SIZE);
    IPF_PRINT("%s%#x\t\t%#x\n", "IPF_INIT_ADDR        ", IPF_INIT_ADDR, IPF_INIT_SIZE);
    IPF_PRINT("%20s%#x\t\t%#x\n", "IPF_DEBUG_INFO_ADDR  ", IPF_DEBUG_INFO_ADDR, IPF_DEBUG_INFO_SIZE);
}

#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
/*****************************************************************************
* 函 数 名  : IPF_FilterList_Init
*
* 功能描述  : IPF过滤器链表初始化     内部使用，不作为接口函数
*
* 输入参数  : BSP_VOID
* 输出参数  : 无
* 返 回 值  : IPF_SUCCESS    过滤器链表初始化成功
*                       IPF_ERROR      过滤器链表初始化失败
*
* 修改记录  :2011年11月17日   鲁婷  创建
*****************************************************************************/
BSP_S32 IPF_FilterList_Init(BSP_VOID)
{
    BSP_U32 i = 0;
    IPF_ID_S* current = BSP_NULL;
    IPF_ID_S* prev = BSP_NULL;
    
    /* 初始化上下行uselist */
    for(i = 0; i < IPF_CHANNEL_MAX; i++)
    {
        g_stIPFFilterInfo[i].u32FilterNum = 0;
        g_stIPFFilterInfo[i].pstUseList = BSP_NULL;
    }
    
    /* 初始化freelist */
    for(i = 0; i < IPF_TOTAL_FILTER_NUM; i++)
    {
        current = (IPF_ID_S*)malloc(sizeof(IPF_ID_S));
        if(BSP_NULL == current)
        {
            IPF_PRINT( "\r IPF_FilterList_Init malloc ERROR! \n");
            goto FREE_ALL;
        }
        if(g_stIPFFreeList != BSP_NULL)
        {
            prev->pstNext = current;/*lint !e613*/
        }
        else /* 头结点 */
        {
            g_stIPFFreeList = current;
        }
        current->u32FilterID = i;
        current->u32PsID = 0;
        current->pstNext = BSP_NULL;
        prev = current;
    }
    return IPF_SUCCESS;
    
FREE_ALL:
    while(g_stIPFFreeList!= BSP_NULL)
    {
        free(g_stIPFFreeList);
        g_stIPFFreeList = g_stIPFFreeList->pstNext;
    }
    return IPF_ERROR;
}

/*****************************************************************************
* 函 数 名  : IPF_AddToFreeList
*
* 功能描述  : 将结点加到freelist的合适位置
*
* 输入参数  : IPF_ID_S* stNode             待插入的结点指针
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID IPF_AddToFreeList(IPF_ID_S* stNode)
{
    IPF_ID_S* current = BSP_NULL;    
    IPF_ID_S* prev = BSP_NULL;

    current = g_stIPFFreeList;

    /* 如果freelist为空 */
    if(BSP_NULL == current)
    {
        g_stIPFFreeList = stNode;
        g_stIPFFreeList->pstNext = BSP_NULL;
        return;
    }

    /* 如果比第一个结点的ID还小 */
    if(stNode->u32FilterID < current->u32FilterID)
    {
        stNode->pstNext = current;
        g_stIPFFreeList = stNode;       
        return;
    }

    prev = g_stIPFFreeList;
    current = g_stIPFFreeList->pstNext;

    while(current != BSP_NULL)
    {
        if(stNode->u32FilterID < current->u32FilterID)
        {
            prev->pstNext = stNode;
            stNode->pstNext = current;
            return;
        }
        prev = current;
        current = current->pstNext;
    }
    /* 放在最后 */
    prev->pstNext = stNode;
    stNode->pstNext = BSP_NULL;

}


/*****************************************************************************
* 函 数 名  : IPF_DeleteAll
*
* 功能描述  : 删除链表中的所有结点
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型           
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  :2011年3月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID IPF_DeleteAll(IPF_CHANNEL_TYPE_E eChnType)
{
    IPF_ID_S* pstMove = BSP_NULL;
    BSP_U32 u32temp = 0;
    BSP_U32 u32Mask[IPF_CHANNEL_MAX] = {0x1FF,0x1FF0000};
    
    while(g_stIPFFilterInfo[eChnType].u32FilterNum)
    {
        pstMove = g_stIPFFilterInfo[eChnType].pstUseList;
        /* 将结点从uselist删除 */
        g_stIPFFilterInfo[eChnType].pstUseList = g_stIPFFilterInfo[eChnType].pstUseList->pstNext;

        /* 将删除的结点添加到freelist中 */ 
        IPF_AddToFreeList(pstMove); 
        g_stIPFFilterInfo[eChnType].u32FilterNum--;
    }
    g_stIPFFilterInfo[eChnType].pstUseList = BSP_NULL;

    /* 将过滤器起始索引设置为511 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_FLT_ZERO_INDEX, u32temp);
    u32temp |= u32Mask[eChnType];
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_FLT_ZERO_INDEX, u32temp);
}

/*****************************************************************************
* 函 数 名  : IPF_MallocOneFilter
*
* 功能描述  : 从freelist中分配一个结点(取出第一个结点)
*
* 输入参数  : 无       
*             
* 输出参数  : 无

* 返 回 值  : 结点指针
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*
* 说明      : 由调用函数来保证一定能分配到结点
*****************************************************************************/
IPF_ID_S* IPF_MallocOneFilter(BSP_VOID)
{
    IPF_ID_S* current = BSP_NULL;
    current = g_stIPFFreeList;

    if(BSP_NULL == current)
    {
        IPF_PRINT( "IPF_MallocOneFilter error\n");
        return current;
    }
    g_stIPFFreeList = g_stIPFFreeList->pstNext;  

    return current;
}

/*****************************************************************************
* 函 数 名  : IPF_AddTailUsedFilter
*
* 功能描述  : 将结点加到uselist的结尾
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型   
*             IPF_ID_S* stNode             待插入的结点指针
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID IPF_AddTailUsedFilter(IPF_CHANNEL_TYPE_E eChnType, IPF_ID_S* stNode)
{
    IPF_ID_S* current = BSP_NULL;

    current = g_stIPFFilterInfo[eChnType].pstUseList;

    if(BSP_NULL == current)
    {
        g_stIPFFilterInfo[eChnType].pstUseList = stNode;
        g_stIPFFilterInfo[eChnType].pstUseList->pstNext = BSP_NULL;
        g_stIPFFilterInfo[eChnType].u32FilterNum = 1;
        return;
    }

    /* 将结点加到链表结尾 */
    while(current->pstNext != BSP_NULL)
    {
        current = current->pstNext;
    }
    current->pstNext = stNode;
    stNode->pstNext = BSP_NULL;
    
    g_stIPFFilterInfo[eChnType].u32FilterNum++;

}

/*****************************************************************************
* 函 数 名  : IPF_AddTailFilterChain
*
* 功能描述  :将过滤器配置到硬件中
*
* 输入参数  : BSP_U32 u32LastFilterID, BSP_U32 u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo
*             
* 输出参数  : 无

* 返 回 值  : 无
*
* 修改记录  : 2011年3月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID IPF_AddTailFilterChain(BSP_U32 u32LastFilterID, BSP_U32 u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo)
{
    BSP_U32 u32Value = 0;
    IPF_MATCH_INFO_S* pstLastMatchInfo = BSP_NULL;
    BSP_U32 u32Spi = 0;

    u32Spi = pstMatchInfo->u32FltSpi;
    pstMatchInfo->u32FltSpi = ((u32Spi&0xff000000)>>24) |
                              ((u32Spi&0x00ff0000)>>8) |
                              ((u32Spi&0x0000ff00)<<8) |
                              ((u32Spi&0x000000ff)<<24);
    
    /* 基本过滤器--将新的过滤器规则配置到过滤器 */
    if(u32FilterID < IPF_BF_NUM)
    {
        IPF_REG_WRITE(IPF_REGBASE_ADR, BFLT_INDEX, u32FilterID); 
        memcpy((BSP_VOID*)(IPF_REGBASE_ADR+FLT_LOCAL_ADDR0), pstMatchInfo, sizeof(IPF_MATCH_INFO_S));
    }
    /* 扩展过滤器 */
    else
    {
        memcpy((BSP_VOID*)(g_pstExFilterAddr + u32FilterID - IPF_BF_NUM), pstMatchInfo, sizeof(IPF_MATCH_INFO_S));
    }

    /* 不是第一个filter才需要配置上一个filter的nextindex域 */
    if(u32LastFilterID != IPF_TAIL_INDEX)
    {
        /* 将上次配置最后一个过滤器的nextIndex域重新配置 */
        if(u32LastFilterID < IPF_BF_NUM)
        {
            IPF_REG_WRITE(IPF_REGBASE_ADR, BFLT_INDEX, u32LastFilterID); 
            IPF_REG_READ(IPF_REGBASE_ADR, FTL_CHAIN, u32Value);
            u32Value = (u32Value&0x1FF0000) + u32FilterID;
            IPF_REG_WRITE(IPF_REGBASE_ADR, FTL_CHAIN, u32Value);
        }
        else
        {
            pstLastMatchInfo = g_pstExFilterAddr + u32LastFilterID - IPF_BF_NUM;
            pstLastMatchInfo->unFltChain.Bits.u16NextIndex = u32FilterID;        
        }
    }
    
}

/*****************************************************************************
* 函 数 名     : IPF_FindFilterID
*
* 功能描述  : 在上下行链表中寻找与PS ID 匹配的Filter ID
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType    通道类型
*                           BSP_U32 u32PsID                PS ID            
*             
* 输出参数  : BSP_U32* u32FilterID   查询到的Filter ID

* 返 回 值     : IPF_SUCCESS                查询成功
*                          IPF_ERROR                  查询失败
*
* 修改记录  :2011年1月11日   鲁婷  创建
*****************************************************************************/
BSP_S32 IPF_FindFilterID(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32PsID, BSP_U32* u32FilterID)
{
    IPF_ID_S* current = BSP_NULL;

    current = g_stIPFFilterInfo[eChnType].pstUseList;
    while(current != BSP_NULL)
    {
        if(current->u32PsID != u32PsID)
        {
            current = current->pstNext;
        }
        else
        {
            *u32FilterID = current->u32FilterID;
            return IPF_SUCCESS;
        }
    }

    return IPF_ERROR;        
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_Init
*
* 功能描述  : IPF公共参数初始化
*
* 输入参数  : IPF_COMMON_PARA_S *pstCommPara
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS    配置成功
*                           BSP_ERR_IPF_NOT_INIT     未初始化
*                           BSP_ERR_IPF_INVALID_PARA  参数错误
*
* 说明             : 配置IPF全局控制配置寄存器 建议选择按优先级排序配置
*
* 修改记录  : 2011年11月29日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_Init(IPF_COMMON_PARA_S *pstCommPara)
{
    BSP_U32 u32IPFCtrl = 0;
    BSP_U32 i = 0;

    /* 参数检查 */
    if(NULL == pstCommPara)
    {
        IPF_PRINT( "\r BSP_IPF_Init pstCommPara NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(!(*g_pbIPFInit))
    {
        IPF_PRINT( "\r IPF NOT Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* 配置IPF全局控制配置寄存器 */
    u32IPFCtrl = pstCommPara->bFilterSeq | (pstCommPara->bFltAddrReverse<<1) | (pstCommPara->bSpPriSel<<2)/*lint !e701*/ 
                 | (pstCommPara->bSpWrrModeSel<<3) | (pstCommPara->eMaxBurst<<4)/*lint !e701*/
                 | (pstCommPara->bIpv6NextHdSel<<6) | (pstCommPara->bEspAhSel<<7)/*lint !e701*/
                 | (pstCommPara->bAhSpiDisable<<8) | (pstCommPara->bEspSpiDisable<<9);/*lint !e701*/
    IPF_PRINT( "\r u32IPFCtrl = 0x%x \n", u32IPFCtrl);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CTRL, u32IPFCtrl); 

    return  IPF_SUCCESS; 
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_ConfigUlChannel
*
* 功能描述  : 配置上行通道控制参数
*
* 输入参数  : IPF_CHL_CTRL_S *pstCtrl 
* 输出参数  : 无
* 返 回 值      : 无
*
* 说明             : 配置上行IPF通道控制寄存器
*
* 修改记录  : 2011年11月29日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_ConfigUlChannel(IPF_CHL_CTRL_S *pstCtrl)
{
    BSP_U32 u32ChanCtrl = 0; 

    /* 参数检查 */
    if(NULL == pstCtrl)
    {
        IPF_PRINT( "\r BSP_IPF_ConfigUlChannel pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    /*配置上行通道控制寄存器 */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    IPF_PRINT( "\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_UP), u32ChanCtrl);  

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_ConfigDlChannel
*
* 功能描述  : 配置上行通道控制参数
*
* 输入参数  : IPF_CHL_CTRL_S *pstCtrl 
* 输出参数  : 无
* 返 回 值      : 无
*
* 说明             : 配置下行IPF通道控制寄存器
*
* 修改记录  : 2011年11月29日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_ConfigDlChannel(IPF_CHL_CTRL_S *pstCtrl)
{
    BSP_U32 u32ChanCtrl = 0; 

    /* 参数检查 */
    if(NULL == pstCtrl)
    {
        IPF_PRINT( "\r BSP_IPF_ConfigDlChannel pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    /*配置上行通道控制寄存器 */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    IPF_PRINT( "\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_DOWN), u32ChanCtrl);

    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_SetFilter
*
* 功能描述  : 用来配置所有的Filter
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType 通道类型
*                           IPF_FILTER_CONFIG_S *pFilterInfo  Filter配置结构体指针
*                           BSP_U32 u32FilterNum   Filter个数
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS                      配置成功
*                            BSP_ERR_IPF_NOT_INIT             模块未初始化
*                            BSP_ERR_IPF_FILTER_NOT_ENOUGH    Filter个数不够
*                            BSP_ERR_IPF_INVALID_PARA         参数错误
*
* 修改记录  :2011年1月11日   鲁婷  创建
                            2011年3月30日   鲁婷  修改
                            2011年11月30日   鲁婷  修改
*****************************************************************************/
BSP_S32 BSP_IPF_SetFilter(IPF_CHANNEL_TYPE_E eChnType, IPF_FILTER_CONFIG_S *pstFilterInfo, BSP_U32 u32FilterNum)
{
    BSP_U32 i = 0;
    IPF_ID_S* current = BSP_NULL;
    BSP_U32 u32temp = 0;
    IPF_CHANNEL_TYPE_E eType = IPF_CHANNEL_MAX;
    BSP_U32 u32LastFilterID = 0;

    /* 参数检查 */
    if((eChnType >= IPF_CHANNEL_MAX) || (NULL == pstFilterInfo) || (eChnType < IPF_CHANNEL_UP))
    {
        IPF_PRINT( "\r BSP_IPF_SetFilter input para ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    /* 检查模块是否初始化 */
    if(!(*g_pbIPFInit))
    {
        IPF_PRINT( "\r IPF Not Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    eType = (eChnType == IPF_CHANNEL_UP)?IPF_CHANNEL_DOWN:IPF_CHANNEL_UP;

    if(u32FilterNum > (IPF_TOTAL_FILTER_NUM - g_stIPFFilterInfo[eType].u32FilterNum))
    {
        IPF_PRINT( "\r BSP_IPF_SetFilter Num is not enough! \n");
        return BSP_ERR_IPF_FILTER_NOT_ENOUGH;
    }

    /* 清除该方向的所有结点 */
    IPF_DeleteAll(eChnType);

    for(i = 0; i < u32FilterNum; i++)
    {
        /* 从freelist中取出未配置的过滤器 */
        current = IPF_MallocOneFilter();        
        if(current == BSP_NULL)
        {       
            IPF_PRINT( "\r IPF_MallocOneFilter error! \n");
            return IPF_ERROR;
        }
        current->u32PsID = pstFilterInfo->u32FilterID;
        
        /* 先将NextIndex配置为511 */
        pstFilterInfo->stMatchInfo.unFltChain.Bits.u16NextIndex = IPF_TAIL_INDEX;

        if(0 == i)
        {
            /* 将起始索引配到寄存器 */
            IPF_REG_READ(IPF_REGBASE_ADR, IPF_FLT_ZERO_INDEX, u32temp);
            if(eChnType == IPF_CHANNEL_UP)
            {
                u32temp &= 0xFFFF0000;
                u32temp += (current->u32FilterID);
            }
            else
            {
                u32temp &= 0x0000FFFF;
                u32temp += (current->u32FilterID<<16);
            }
            IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_FLT_ZERO_INDEX, u32temp);  
            IPF_AddTailFilterChain(IPF_TAIL_INDEX, current->u32FilterID, &pstFilterInfo->stMatchInfo);
        } 
        else
        {
            IPF_AddTailFilterChain(u32LastFilterID, current->u32FilterID, &pstFilterInfo->stMatchInfo);
        }
        
        /* 更新该方向的uselist */
        IPF_AddTailUsedFilter(eChnType, current);
        u32LastFilterID = current->u32FilterID;
        
        pstFilterInfo++; 
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名      : BSP_IPF_GetFilter
*
* 功能描述  : 提供给PS查询某个Filter配置信息
*
* 输入参数  : BSP_U32 u32FilterID   Filter ID号
*             
* 输出参数  : IPF_FILTER_CONFIG_S * pFilterInfo  查询到的Filter信息

* 返 回 值     : IPF_SUCCESS                查询成功
*                           IPF_ERROR                  查询失败
*                           BSP_ERR_IPF_NOT_INIT       模块未初始化
*                           BSP_ERR_IPF_INVALID_PARA   参数错误
*
* 修改记录  : 2011年1月11日   鲁婷  创建
                             2011年3月30日   鲁婷  修改
                             2011    11月30日   鲁婷  修改
*****************************************************************************/
BSP_S32 BSP_IPF_GetFilter(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo)
{
    BSP_U32 u32FindID = 0;
    
    /* 参数检查 */
    if(NULL == pstFilterInfo)
    {
        IPF_PRINT( "\r BSP_IPF_GetFilter input para ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    /* 检查模块是否初始化 */
    if(!(*g_pbIPFInit))
    {
        IPF_PRINT( "\r IPF Not Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* 查找PS ID 对应的FilterID*/
    if(IPF_FindFilterID(eChnType, u32FilterID, &u32FindID) != IPF_SUCCESS)
    {
        return IPF_ERROR;
    }
    pstFilterInfo->u32FilterID = u32FilterID;    
    
    /* 如果是基本过滤器 */
    if(u32FindID < IPF_BF_NUM)
    {
        /* 写过滤表操作地址 */    
        IPF_REG_WRITE(IPF_REGBASE_ADR, BFLT_INDEX, u32FindID); 
         
        /* 读出过滤器的配置 */
        memcpy(&pstFilterInfo->stMatchInfo, (BSP_VOID*)(IPF_REGBASE_ADR+FLT_LOCAL_ADDR0), sizeof(IPF_MATCH_INFO_S));
    }
    /* 扩展过滤器 */
    else
    {
        /* 读出过滤器的配置 */
        memcpy(&pstFilterInfo->stMatchInfo, (BSP_VOID*)(g_pstExFilterAddr + u32FindID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }
    
    return IPF_SUCCESS;

}

/*****************************************************************************
* 函 数 名      : IPF_ConfigCD
*
* 功能描述  : 配置CD
*
* 输入参数  : TTF_MEM_ST *pstTtf, BSP_U16* pu16TotalDataLen, BSP_U32* pu32BdInPtr
* 输出参数  : 无
* 返 回 值      :  无
*
* 修改记录  :2011年1月24日   鲁婷  创建
*****************************************************************************/
BSP_S32 IPF_ConfigCD(TTF_MEM_ST *pstTtf, BSP_U16* pu16TotalDataLen, BSP_U32* pu32BdInPtr)
{
    BSP_U32 u32DlCDWptr = 0;
    BSP_U32 u32DlCDRptr = 0;
    BSP_U16 u16TotalDataLen = 0;
    TTF_MEM_ST* p = BSP_NULL;

    /* 为防止BD 满或者后续申请目的地址不成功，设置临时cd的位置 */
    u32DlCDWptr = *(g_stIpfDl.u32IpfCdWptr);
    u32DlCDRptr = *(g_stIpfDl.u32IpfCdRptr);
    *pu32BdInPtr = (BSP_U32)(g_stIpfDl.pstIpfCDQ + (u32DlCDWptr));

    /* 配置CD */
    p = pstTtf;
    do
    {
        /* 判断是否有空闲CD */
        if(u32DlCDRptr != (u32DlCDWptr+1)%IPF_DLCD_DESC_SIZE)
        {
            g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u32Ptr = (BSP_U32)p->pData;
            g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16PktLen = p->usUsed;
            #ifdef __BSP_IPF_DEBUG__
            g_stIpfDl.pstIpfDebugCDQ[u32DlCDWptr].u32Ptr = (BSP_U32)p->pData;
            g_stIpfDl.pstIpfDebugCDQ[u32DlCDWptr].u16PktLen = p->usUsed;
            if(g_stIPFDebugInfo->u32IpfDebug)
            {
                IPF_PRINT("usUsed = %d  pData = 0x%x\n", p->usUsed, p->pData);
            }
            #endif
            u16TotalDataLen += p->usUsed;
            
            /* 标识是否结束 */
            if(p->pNext != BSP_NULL)
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 0;
                #ifdef __BSP_IPF_DEBUG__
                g_stIpfDl.pstIpfDebugCDQ[u32DlCDWptr].u16Attribute = 0;
                #endif
                if(u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)
                {
                    u32DlCDWptr += 1;
                    p = p->pNext;
                }
                /* 未结束时，CD不能翻转，这是记录CD的尾部，同时将从0开始配置CD */
                else
                {
                    u32DlCDWptr = 0;
                    u16TotalDataLen = 0;
                    p = pstTtf;
                    *pu32BdInPtr = (BSP_U32)g_stIpfDl.pstIpfCDQ;
                    #ifdef __BSP_IPF_DEBUG__
                    if(g_stIPFDebugInfo->u32IpfDebug)
                    {
                        IPF_PRINT("CD 翻转 \n");
                    }
                    #endif
                }
            }
            else
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 1;
                #ifdef __BSP_IPF_DEBUG__
                g_stIpfDl.pstIpfDebugCDQ[u32DlCDWptr].u16Attribute = 1;
                #endif
                
                /* 结束时CD可以翻转 */
                u32DlCDWptr = (u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)?(u32DlCDWptr+1):0;
                #ifdef __BSP_IPF_DEBUG__
                if(g_stIPFDebugInfo->u32IpfDebug)
                {
                    IPF_PRINT("u32DlCDWptr  = %d\n", u32DlCDWptr);
                }
                #endif
                break;
            }
        }
        else
        {
            IPF_PRINT( "\r DownFilter CD FULL ! u32DlCDRptr=%d u32DlCDWptr=%d\n",u32DlCDRptr,u32DlCDWptr);
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }        
    }while(p != BSP_NULL);
    
    *(g_stIpfDl.u32IpfCdWptr) = u32DlCDWptr;
    *pu16TotalDataLen = u16TotalDataLen;
    
    return IPF_SUCCESS;

}

BSP_S32 BSP_IPF_ConfigDownFilter(BSP_U32 u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara, BSP_BOOL bintFlag)
{
    BSP_U32 u32BdqWptr = 0;
    TTF_MEM_ST* p = BSP_NULL;
    BSP_U32 i;
    BSP_U32 u32BdInPtr = 0;
    BSP_U32 u32BD = 0;
    BSP_U32 u32LastBd = 0;
    BSP_U16 u16TotalDataLen = 0;

    if(BSP_NULL == pstDlPara)
    {
        IPF_PRINT( "\r BSP_IPF_ConfigDownFilter input para ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    /* 检查模块是否初始化 */
    if(!(*g_pbIPFInit))
    {
        IPF_PRINT( "\r IPF Not Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    if(u32Num > g_stIpfDl.u32IdleBd)
    {
        g_stIPFDebugInfo->u32DlBdNotEnough++;
        return IPF_ERROR;
    }

    /* 读出BD写指针 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(IPF_CHANNEL_DOWN), u32BdqWptr);
    u32BD = u32BdqWptr;
    for(i = 0; i < u32Num; i++)
    {
        /* 配置CD */
        if(IPF_ConfigCD(pstDlPara[i].pstSrcTtf, &u16TotalDataLen, &u32BdInPtr) != IPF_SUCCESS)
        {
            g_stIPFDebugInfo->u32DlCdNotEnough++;
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }
        g_stIpfDl.pstIpfBDQ[u32BD].u16Attribute = 0; 
        g_stIpfDl.pstIpfBDQ[u32BD].u32InPtr =  u32BdInPtr;
        g_stIpfDl.pstIpfBDQ[u32BD].u16PktLen = u16TotalDataLen;
        g_stIpfDl.pstIpfBDQ[u32BD].u32OutPtr = (BSP_U32)pstDlPara[i].pstDstTtf->pData;
        g_stIpfDl.pstIpfBDQ[u32BD].u16UsrField1 = pstDlPara[i].u16UsrField;
        g_stIpfDl.pstIpfBDQ[u32BD].u32UsrField2 = (BSP_U32)pstDlPara[i].pstDstTtf;
        g_stIpfDl.pstIpfBDQ[u32BD].u32UsrField3 = (BSP_U32)pstDlPara[i].pstSrcTtf;
        u32BD = ((u32BD + 1) < IPF_DLBD_DESC_SIZE)? (u32BD + 1) : 0;
    }

    if((u32BdqWptr+u32Num-1) < IPF_DLBD_DESC_SIZE)
    {
        u32LastBd = u32BdqWptr+u32Num-1;
    }
    else
    {
        u32LastBd = u32BdqWptr+u32Num-1 - IPF_DLBD_DESC_SIZE;
    }
    g_stIpfDl.pstIpfBDQ[u32LastBd].u16Attribute = bintFlag; 

    /* 更新BD写指针 */
    IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(IPF_CHANNEL_DOWN), u32BD);  

    return IPF_SUCCESS;
}
/*****************************************************************************
* 函 数 名     : BSP_IPF_ChannelEnable
*
* 功能描述  : 该接口用于使能或复位IP过滤器上下行通道
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChanType      上下行通道标识
*                           BSP_BOOL bFlag   使能复位标识 
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS                使能复位成功
*                            IPF_ERROR                  使能复位失败
*                            BSP_ERR_IPF_INVALID_PARA   参数错误
*
* 修改记录  :2011年1月11日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_ChannelEnable(IPF_CHANNEL_TYPE_E eChanType, BSP_BOOL bFlag)
{
    BSP_U32 u32ChanEnable = 0;
    BSP_U32 u32ChanState = 0;
    BSP_U32 u32Times = 0;
    BSP_U32 u32ChCtrl = 0;
    
    /* 参数检查 */
    if((eChanType >= IPF_CHANNEL_MAX) || (eChanType < IPF_CHANNEL_UP))
    {
        IPF_PRINT( "\r BSP_IPF_ChannelEnable eChanType = %d ! \n",eChanType,0,0,0,0,0);
        return BSP_ERR_IPF_INVALID_PARA;
    }

    /* 通道使能 */
    if(bFlag)
    {
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_EN, u32ChanEnable);
        u32ChanEnable |= 0x1<<eChanType;
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_EN, u32ChanEnable);                        
    }
    /* 通道去使能 */
    else
    {
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_EN, u32ChanEnable);
        u32ChanEnable &= 0xFFFFFFFF ^ (0x1<<eChanType);
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_EN, u32ChanEnable); 
        
        /* 遍历直到通道状态为0 */      
        do
        {
            (BSP_VOID)taskDelay(1);
            IPF_REG_READ(IPF_REGBASE_ADR, IPF_EN_STATE, u32ChanState);
            u32ChanState &= 0x1<<eChanType;
            u32Times++;
        }while((u32ChanState) && (u32Times < 100)); 
        
        if(100 == u32Times)
        {
            IPF_PRINT( "\r BSP_IPF_ChannelEnable disable error u32Times = %d ! \n",u32Times,0,0,0,0,0);
            return IPF_ERROR;
        }

        /* 复位输入队列和输出队列的读写指针 */
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_CTRL(eChanType), u32ChCtrl);
        u32ChCtrl |= 0x30; /* 将4，5bit设置为1 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(eChanType), u32ChCtrl); 
    }

    
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetDlBDNum
*
* 功能描述  : 该接口用于获取下行空闲BD和CD 数目
*                           BD 范围: 0~64      CD范围: 0~64*4
* 输入参数  : 无
*
* 输出参数  : 空闲CD数目
* 返 回 值      : 空闲BD数目
*  
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_U32 BSP_IPF_GetDlBDNum(BSP_U32* pu32CDNum)
{
    BSP_U32 u32DlBdDepth = 0;
    BSP_U32 u32DlCDWptr = 0;
    BSP_U32 u32DlCDRptr = 0;
    BSP_U32 u32IdleBd = 0;
    BSP_U32 u32IdleCd = 0;
    BSP_U32 u32IdleCdDown = 0;
    BSP_U32 u32IdleCdUp = 0;
    BSP_U32 u32Tmp = 0;

    u32DlCDWptr = *(g_stIpfDl.u32IpfCdWptr);
    u32DlCDRptr = *(g_stIpfDl.u32IpfCdRptr);
    /* 计算空闲BD数量 */
    /*IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_BDQ_WPTR(IPF_CHANNEL_DOWN), u32BdqWptr);*/
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_DOWN), u32DlBdDepth);
    u32IdleBd = IPF_DLBD_DESC_SIZE - (u32DlBdDepth & 0x1FF);
    /* 计算空闲CD 数量 */
    if(u32DlCDRptr > u32DlCDWptr)
    {
        u32IdleCd = u32DlCDRptr - u32DlCDWptr - 1;
    }
    else
    {
        u32IdleCdUp = (u32DlCDRptr > 1)?(u32DlCDRptr - 1):0;
        u32IdleCdDown = IPF_DLCD_DESC_SIZE -  u32DlCDWptr - 1;
        u32IdleCd = (u32IdleCdUp > u32IdleCdDown)? u32IdleCdUp:u32IdleCdDown;
    }
    g_stIpfDl.u32IdleBd = u32IdleBd;
    *pu32CDNum = u32IdleCd;
    
    return u32IdleBd;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_DlStateIdle
*
* 功能描述  : 该接口用于获取下行通道是否为空闲
*                            
* 输入参数  : 无
*
* 输出参数  : 无
* 返 回 值      : IPF_SUCCESS  表示下行空闲，可以切换模式
*                            IPF_ERROR      表示下行非空闲，不可以切换模式
*  
* 修改记录  :2011年12月9日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_DlStateIdle(BSP_VOID)
{
    BSP_U32 u32DlState = 0;
    BSP_U32 u32BdqWptr = 0;
    
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_STATE(IPF_CHANNEL_DOWN), u32DlState);

    if(u32DlState != 0x14)
    {
        return IPF_ERROR;
    }
    return IPF_SUCCESS;
}
/*****************************************************************************
* 函 数 名     : BSP_IPF_RegisterWakeupUlCb
*
* 功能描述  : 该接口用于注册上行PS任务回调函数
*                           
* 输入参数  : BSP_IPF_WakeupUlCb *pFnWakeupUl
*
* 输出参数  : 无
* 返 回 值      : 无
*  
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_RegisterWakeupUlCb(BSP_IPF_WakeupUlCb pFnWakeupUl)
{
    /* 参数检查 */
    if(BSP_NULL == pFnWakeupUl)
    {
        IPF_PRINT( "\r BSP_IPF_RegisterWakeupUlCb inputPara ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfUl.pFnUlIntCb = pFnWakeupUl;
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetUlRd
*
* 功能描述  : 该接口用于读取上行BD, 支持一次读取多个BD
*
* 输入参数  : BSP_U32* pu32Num    
*                           IPF_RD_DESC_S *pstRd
*   
* 输出参数  : BSP_U32* pu32Num    实际读取的RD数目
*
* 返 回 值     : IPF_SUCCESS               操作成功
*                           IPF_ERROR                   操作失败
*
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID BSP_IPF_GetUlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd)
{
    BSP_U32 u32RdqRptr = 0;
    BSP_U32 u32RdqDepth = 0;
    BSP_U32 u32Num = 0;
    BSP_U32 i = 0;
  
    /* 读取RD深度 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_UP), u32RdqDepth);
    u32RdqDepth = (u32RdqDepth>>16)&0x1FF;
    
    u32Num = (u32RdqDepth < *pu32Num)?u32RdqDepth:*pu32Num;

    if(u32Num > 0)
    {
        /* 读取RD读指针 */
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_RPTR(IPF_CHANNEL_UP), u32RdqRptr);
        #ifdef __BSP_IPF_DEBUG__
        if(g_stIPFDebugInfo->u32IpfDebug)
        {
            IPF_PRINT("in u32RdqRptr = %d\n", u32RdqRptr);
        }
        #endif
        for(i = 0; i < u32Num; i++)
        {        
            /* 获取RD */
            pstRd[i].u16Attribute = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Attribute;
            pstRd[i].u16PktLen = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16PktLen;
            pstRd[i].u16Result = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Result;
            pstRd[i].u32InPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32InPtr;
            pstRd[i].u32OutPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32OutPtr;
            pstRd[i].u16UsrField1 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16UsrField1;
            pstRd[i].u32UsrField2 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField2;
            pstRd[i].u32UsrField3 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField3;
            
            u32RdqRptr = ((u32RdqRptr+1) < IPF_ULRD_DESC_SIZE)?(u32RdqRptr+1):0;        
        }
        /* 更新RD读指针 */
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_RDQ_RPTR(IPF_CHANNEL_UP), u32RdqRptr);
        #ifdef __BSP_IPF_DEBUG__
        if(g_stIPFDebugInfo->u32IpfDebug)
        {
            IPF_PRINT("out u32RdqRptr = %d\n", u32RdqRptr);
        }
        #endif
    }
    *pu32Num = u32Num;
}

/*****************************************************************************
* 函 数 名  : BSP_IPF_UseFilterInfo
*
* 功能描述  : 提供的debug接口，获取已经使用的filter号
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
                             2011年3月30日   鲁婷  修改
*****************************************************************************/
BSP_VOID BSP_IPF_UseFilterInfo(IPF_CHANNEL_TYPE_E eChnType)
{
    IPF_ID_S* current = BSP_NULL;
    BSP_U32 u32FilterNum = 0;
    BSP_S32 s32GetChar = 0;
    BSP_U32 u32cyc = 10;
    
    u32FilterNum = g_stIPFFilterInfo[eChnType].u32FilterNum;
    current = g_stIPFFilterInfo[eChnType].pstUseList;

    IPF_PRINT("=============================\n");

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
            s32GetChar = getchar();/*lint !e666*/
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
    IPF_PRINT("*****************************\n");

}

/*****************************************************************************
* 函 数 名  : BSP_IPF_FreeFilterInfo
*
* 功能描述  : 提供的debug接口，获取未使用的filter号
*
* 输入参数  : IPF_CHANNEL_TYPE_E eChnType  通道类型
*             
* 输出参数  : 无
* 返 回 值  : 无
*
* 修改记录  : 2011年1月11日   鲁婷  创建
*
*****************************************************************************/
BSP_VOID BSP_IPF_FreeFilterInfo()
{
    IPF_ID_S* current = BSP_NULL;
    BSP_S32 s32GetChar = 0;
    BSP_U32 u32cyc = 10;

    current = g_stIPFFreeList;

    IPF_PRINT("============================\n");

    while(current != BSP_NULL)
    {
        while(u32cyc&&(current != BSP_NULL))
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext; 
            u32cyc--;
        }
        IPF_PRINT("\npress \'Enter\' to continue, press \'q\' to stop\n");
        s32GetChar = getchar();/*lint !e666*/
        if ('q' == s32GetChar)
        {
            break;
        }
        u32cyc = 10;
    }
    IPF_PRINT("*****************************\n");    
}

BSP_VOID BSP_IPF_FilterInfoHWID(BSP_U32 u32Num)
{
    BSP_U32* p = BSP_NULL;
    BSP_U32 i = 0;
    IPF_MATCH_INFO_S stMatchInfo = {0}; 
    
    if(u32Num < IPF_BF_NUM)
    {
         /* 写过滤表操作地址 */    
        IPF_REG_WRITE(IPF_REGBASE_ADR, BFLT_INDEX, u32Num); 
         
        /* 读出过滤器的配置 */
        memcpy(&stMatchInfo, (BSP_VOID*)(IPF_REGBASE_ADR+FLT_LOCAL_ADDR0), sizeof(IPF_MATCH_INFO_S));
    }
    else
    {
        memcpy(&stMatchInfo, (BSP_VOID*)(g_pstExFilterAddr + u32Num - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }

    IPF_PRINT("============================\n");
    IPF_PRINT("src ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[0], stMatchInfo.u8SrcAddr[1], stMatchInfo.u8SrcAddr[2], stMatchInfo.u8SrcAddr[3]);
    IPF_PRINT("src ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[4], stMatchInfo.u8SrcAddr[5], stMatchInfo.u8SrcAddr[6], stMatchInfo.u8SrcAddr[7]);
    IPF_PRINT("src ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[8], stMatchInfo.u8SrcAddr[9], stMatchInfo.u8SrcAddr[10], stMatchInfo.u8SrcAddr[11]);
    IPF_PRINT("src ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[12], stMatchInfo.u8SrcAddr[13], stMatchInfo.u8SrcAddr[14], stMatchInfo.u8SrcAddr[15]);
    IPF_PRINT("src MASK0 : %x.%x.%x.%x\n", stMatchInfo.u8SrcMsk[0], stMatchInfo.u8SrcMsk[1], stMatchInfo.u8SrcMsk[2], stMatchInfo.u8SrcMsk[3]);
    IPF_PRINT("src MASK1 : %x.%x.%x.%x\n", stMatchInfo.u8SrcMsk[4], stMatchInfo.u8SrcMsk[5], stMatchInfo.u8SrcMsk[6], stMatchInfo.u8SrcMsk[7]);
    IPF_PRINT("src MASK2 : %x.%x.%x.%x\n", stMatchInfo.u8SrcMsk[8], stMatchInfo.u8SrcMsk[9], stMatchInfo.u8SrcMsk[10], stMatchInfo.u8SrcMsk[11]);
    IPF_PRINT("src MASK3 : %x.%x.%x.%x\n", stMatchInfo.u8SrcMsk[12], stMatchInfo.u8SrcMsk[13], stMatchInfo.u8SrcMsk[14], stMatchInfo.u8SrcMsk[15]);
    IPF_PRINT("dst ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[0], stMatchInfo.u8DstAddr[1], stMatchInfo.u8DstAddr[2], stMatchInfo.u8DstAddr[3]);
    IPF_PRINT("dst ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[4], stMatchInfo.u8DstAddr[5], stMatchInfo.u8DstAddr[6], stMatchInfo.u8DstAddr[7]);
    IPF_PRINT("dst ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[8], stMatchInfo.u8DstAddr[9], stMatchInfo.u8DstAddr[10], stMatchInfo.u8DstAddr[11]);
    IPF_PRINT("dst ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[12], stMatchInfo.u8DstAddr[13], stMatchInfo.u8DstAddr[14], stMatchInfo.u8DstAddr[15]);
    IPF_PRINT("dst MASK0 : %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[0], stMatchInfo.u8DstMsk[1], stMatchInfo.u8DstMsk[2], stMatchInfo.u8DstMsk[3]);
    IPF_PRINT("dst MASK1 : %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[4], stMatchInfo.u8DstMsk[5], stMatchInfo.u8DstMsk[6], stMatchInfo.u8DstMsk[7]);
    IPF_PRINT("dst MASK2 : %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[8], stMatchInfo.u8DstMsk[9], stMatchInfo.u8DstMsk[10], stMatchInfo.u8DstMsk[11]);
    IPF_PRINT("dst MASK3 : %x.%x.%x.%x\n", stMatchInfo.u8DstMsk[12], stMatchInfo.u8DstMsk[13], stMatchInfo.u8DstMsk[14], stMatchInfo.u8DstMsk[15]);
    IPF_PRINT("SrcPortLo : %d  SrcPortHi: %d\n", stMatchInfo.unSrcPort.Bits.u16SrcPortLo, stMatchInfo.unSrcPort.Bits.u16SrcPortHi);
    IPF_PRINT("DstPortLo : %d  DstPortHi: %d\n", stMatchInfo.unDstPort.Bits.u16DstPortLo, stMatchInfo.unDstPort.Bits.u16DstPortHi);
    IPF_PRINT("TrafficClass :      %d\n", stMatchInfo.unTrafficClass.u32TrafficClass);
    IPF_PRINT("TrafficClassMsk :  %d\n", stMatchInfo.unTrafficClassMsk.u32TrafficClassMsk);
    IPF_PRINT("Protocol :          %d\n", stMatchInfo.unNextHeader.u32Protocol);
    IPF_PRINT("FlowLable :         %d\n", stMatchInfo.u32FlowLable);
    IPF_PRINT("Type :        %d  Code: %d\n", stMatchInfo.unFltCodeType.Bits.u16Type, stMatchInfo.unFltCodeType.Bits.u16Code);
    IPF_PRINT("NextIndex : %d  FltPri: %d\n", stMatchInfo.unFltChain.Bits.u16NextIndex, stMatchInfo.unFltChain.Bits.u16FltPri);
    IPF_PRINT("FltSpi :             %d\n", stMatchInfo.u32FltSpi);
    IPF_PRINT("FltRuleCtrl :        %x\n", stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl);    
    IPF_PRINT("============================\n");
}

BSP_VOID BSP_IPF_FilterInfoPSID(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32Num)
{
    BSP_U32 u32FindID = 0;
    
    /* 查找PS ID 对应的FilterID*/
    if(IPF_FindFilterID(eChnType, u32Num, &u32FindID) != IPF_SUCCESS)
    {
        IPF_PRINT( "\r cannot find filter ID! \n");
        return ;
    }

    BSP_IPF_FilterInfoHWID(u32FindID);
}
#else
/*****************************************************************************
* 函 数 名     : BSP_IPF_RegisterWakeupDlCb
*
* 功能描述  : 该接口用于注册下行PS任务回调函数
*                           
* 输入参数  : BSP_IPF_WakeupDlkCb *pFnWakeupDl
*
* 输出参数  : 无
* 返 回 值      : 无
*  
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_S32 BSP_IPF_RegisterWakeupDlCb(BSP_IPF_WakeupDlCb pFnWakeupDl)
{
    /* 参数检查 */
    if(BSP_NULL == pFnWakeupDl)
    {
        IPF_PRINT( "\r BSP_IPF_RegisterWakeupDlCb inputPara ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfDl.pFnDlIntCb = pFnWakeupDl;
    return IPF_SUCCESS;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetDlRd
*
* 功能描述  : 该接口用于读取下行BD, 支持一次读取多个BD
*
* 输入参数  : BSP_U32* pu32Num    
*                           IPF_RD_DESC_S *pstRd
*   
* 输出参数  : BSP_U32* pu32Num    实际读取的RD数目
*
* 返 回 值     : IPF_SUCCESS               操作成功
*                           IPF_ERROR                   操作失败
*
* 修改记录  :2011年11月30日   鲁婷  创建
*****************************************************************************/
BSP_VOID BSP_IPF_GetDlRd(BSP_U32* pu32Num, IPF_RD_DESC_S *pstRd)
{
#if 1/* 下行ipf源地址释放上移,add by z00212992,2012-8-13 */
    BSP_U32 u32CdqRptr = 0;
#endif
    BSP_U32 u32RdqRptr = 0;
    BSP_U32 u32RdqDepth = 0;
    BSP_U32 u32Num = 0;
    BSP_U32 i = 0;
    /* 读取RD深度 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_DOWN), u32RdqDepth);
    u32RdqDepth = (u32RdqDepth>>16)&0x1FF;
    
    u32Num = (u32RdqDepth < *pu32Num)?u32RdqDepth:*pu32Num;
    for(i = 0; i < u32Num; i++)
    {
        /* 读取RD读指针 */
        IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_RDQ_RPTR(IPF_CHANNEL_DOWN), u32RdqRptr);
        /* 获取RD */
        pstRd[i].u16Attribute = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16Attribute;
        pstRd[i].u16PktLen = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16PktLen;
        pstRd[i].u16Result = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16Result;
        pstRd[i].u32InPtr = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32InPtr;
        pstRd[i].u32OutPtr = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32OutPtr;
        pstRd[i].u16UsrField1 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u16UsrField1;
        pstRd[i].u32UsrField2 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32UsrField2;
        pstRd[i].u32UsrField3 = g_stIpfDl.pstIpfRDQ[u32RdqRptr].u32UsrField3;
                
        /* 更新RD读指针 */
        u32RdqRptr = ((u32RdqRptr+1) < IPF_DLRD_DESC_SIZE)?(u32RdqRptr+1):0;        
        IPF_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_RDQ_RPTR(IPF_CHANNEL_DOWN), u32RdqRptr);         
    #if 1/* 下行ipf源地址释放上移,add by z00212992,2012-8-13 */
        /* 更新CD读指针 */
    u32CdqRptr = (IO_ADDRESS(pstRd[i].u32InPtr)- (BSP_U32)g_stIpfDl.pstIpfCDQ)/sizeof(IPF_CD_DESC_S);
    while(g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16Attribute != 1)
    {
        /* 将释放的CD  清0 */
        g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16Attribute = 0;
        g_stIpfDl.pstIpfCDQ[u32CdqRptr].u16PktLen = 0;
        g_stIpfDl.pstIpfCDQ[u32CdqRptr].u32Ptr = 0;
        u32CdqRptr = ((u32CdqRptr+1) < IPF_DLCD_DESC_SIZE)?(u32CdqRptr+1):0;
    }
    u32CdqRptr = ((u32CdqRptr+1) < IPF_DLCD_DESC_SIZE)?(u32CdqRptr+1):0;
    *(g_stIpfDl.u32IpfCdRptr) = u32CdqRptr;
    #endif
    }
    
    *pu32Num = u32Num;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetUlRdNum
*
* 功能描述  : 该接口用于读取上行RD数目
*
* 输入参数  : 无
*   
* 输出参数  : 无
*
* 返 回 值     : 上行RD数目
*
* 修改记录  :2012年2月16日   鲁婷  创建
*****************************************************************************/
BSP_U32 BSP_IPF_GetUlRdNum(BSP_VOID)
{
    BSP_U32 u32RdqDepth = 0;
  
    /* 读取RD深度 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_UP), u32RdqDepth);
    u32RdqDepth = (u32RdqDepth>>16)&0x1FF;
    return u32RdqDepth;
}

/*****************************************************************************
* 函 数 名     : BSP_IPF_GetDlRdNum
*
* 功能描述  : 该接口用于读取下行RD数目
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值     :  下行RD数目
*
* 修改记录  :2012年7月16日   鲁婷  创建
*****************************************************************************/
BSP_U32 BSP_IPF_GetDlRdNum(BSP_VOID)
{
    BSP_U32 u32RdqDepth = 0;
  
    /* 读取RD深度 */
    IPF_REG_READ(IPF_REGBASE_ADR, IPF_CH_DQ_DEPTH(IPF_CHANNEL_DOWN), u32RdqDepth);
    u32RdqDepth = (u32RdqDepth>>16)&0x1FF;
    return u32RdqDepth;
}


#endif

#ifdef __KERNEL__
EXPORT_SYMBOL(BSP_IPF_ConfigTimeout);
EXPORT_SYMBOL(BSP_IPF_ConfigUpFilter);
EXPORT_SYMBOL(BSP_IPF_GetUlBDNum);
EXPORT_SYMBOL(BSP_IPF_UlStateIdle);
EXPORT_SYMBOL(BSP_IPF_SetPktLen);
EXPORT_SYMBOL(BSP_IPF_GetStat);
EXPORT_SYMBOL(BSP_IPF_RegisterWakeupDlCb);
EXPORT_SYMBOL(BSP_IPF_GetDlRd);
EXPORT_SYMBOL(BSP_IPF_GetUlRdNum);
EXPORT_SYMBOL(BSP_IPF_GetDlRdNum);
EXPORT_SYMBOL(BSP_IPF_Help);
EXPORT_SYMBOL(BSP_IPF_BDInfo);
EXPORT_SYMBOL(BSP_IPF_RDInfo);
EXPORT_SYMBOL(BSP_IPF_Info);
EXPORT_SYMBOL(BSP_IPF_MEM);
MODULE_LICENSE("GPL");

#endif
#endif

#ifdef __cplusplus
}
#endif


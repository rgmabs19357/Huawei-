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
#include "BSP_MEM.h"
#include "BSP_DRV_IPF_V300.h"
#else 
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <asm/system.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/delay.h>
#include "mach/common/mem/bsp_mem.h"
#include "BSP.h"
#include "bsp_drv_ipf_v300.h"
#endif
typedef struct tagStreamIPv4Header
{
    BSP_U32 TOL:16;
    BSP_U32 TOS:8;
    BSP_U32 HeaderLen:4;
    BSP_U32 Vers:4; 
    BSP_U32 offset:13;
    BSP_U32 MF:1;
    BSP_U32 DF:1;
    BSP_U32 ReservFlag:1;
    BSP_U32 ID:16;
    BSP_U32 Checksum:16;
    BSP_U32 Prot:8;
    BSP_U32 TTL:8;    
    BSP_U32 SourceAddr;
    BSP_U32 DestAddr;
}StreamIPv4Header;

typedef struct tagStreamUDP
{
    BSP_U32 DstPort:16;
    BSP_U32 SrcPort:16;
    BSP_U32 Checksum:16;
    BSP_U32 Length:16;    
}StreamUDP;

typedef struct tagIpfChanState
{
    IPF_CHANNEL_TYPE_E chanType;
    BSP_BOOL chanFlag;
}IpfChanState;
#ifndef __VXWORKS__
typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;
enum TTF_BLK_MEM_STATE_ENUM
{
    TTF_BLK_MEM_STATE_FREE,       /*该内存未申请过或已释放*/
    TTF_BLK_MEM_STATE_ALLOC,      /*该内存已申请*/

    TTF_BLK_MEM_STATE_BUTT
};
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*本内存属于哪一个内存池 */
    unsigned char                   ucClusterId;    /*本内存是属于哪一个级别*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* 该数据的下一段 */
    unsigned short                  usType;         /* 内存类型，DYN、BLK、EXT类型 */
    unsigned short                  usLen;          /* 申请数据的总长度，但不一定全部被使用 */
    unsigned short                  usUsed;         /* 已经使用的数据长度   */
    unsigned short                  usApp;          /* 使用者可以使用的区域 */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* 记录数据的原始指针 */
    unsigned char                  *pData;          /* 存放数据的指针，物理上指向结构体的连续内存 */
    void                           *pExtBuffAddr;   /* 保存extern类型的内存地址用于释放 */
    unsigned long                   ulForCds[1];    /*预留给CDS使用，GU模不用初始化*/

    unsigned long                   ulForLte[6];    /*预留给LTE使用，GU模不用初始化*/
} TTF_MEM_ST;
#endif

int g_IpfUlTaskId = 0;
BSP_BOOL g_u32IpfStAllInit = BSP_FALSE;
BSP_U32* g_ipftestdebug = (BSP_U32*)(IPF_INIT_ADDR + 4);
BSP_U32* g_pu32DlTaskCmp = (BSP_U32*)(IPF_INIT_ADDR + 12);

#ifdef __VXWORKS__
SEM_ID g_IpfUlTaskSemId;
SEM_ID g_IpfUlIntSemId;
BSP_S32 IpfUlIntCb()
{
    semGive(g_IpfUlIntSemId);
    return OK;
}
BSP_VOID IPF_UL_Task_1(BSP_VOID)
{
    BSP_U32 u32Num = 0;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    BSP_U32 i = 0;

    while(1)
    { 
        memset(stRd, 0x0, sizeof(IPF_RD_DESC_S) * IPF_ULRD_DESC_SIZE);
        u32Num = IPF_ULRD_DESC_SIZE;
        semTake(g_IpfUlIntSemId, WAIT_FOREVER);
        if(*g_ipftestdebug)
        {
            IPF_PRINT("TESTERROR    IPF_UL_Task_1 in \n");
        }
        BSP_IPF_GetUlRd(&u32Num, stRd);
        for(i = 0; i < u32Num; i++)
        {
            /* 测试代码通过u32UsrField3  标识是否释放内存*/
            if(stRd[i].u32UsrField3 != 0)
            {
                if(*g_ipftestdebug)
                {
                    IPF_PRINT("TESTERROR    IPF_UL_Task_1:%d, u32Num = %d, i = %d \n",__LINE__, u32Num, i);
                }
                BSP_SFREE((BSP_VOID*)stRd[i].u32InPtr);                
            }
            if(stRd[i].u16Result != 2)
            {
                IPF_PRINT("TESTERROR    IPF_UL_Task_1:%d, u16Result = %x, i = %d \n",__LINE__, stRd[i].u16Result, i);
            }
        }
        if(*g_ipftestdebug)
        {
            IPF_PRINT("TESTERROR    IPF_UL_Task_1 out \n");
        }
        semGive(g_IpfUlTaskSemId);
    }
}

BSP_S32 IPF_ST_INIT(BSP_VOID)
{
    IPF_COMMON_PARA_S stCommPara;
    BSP_S32 s32Ret = 0;
    
    if(BSP_TRUE == g_u32IpfStAllInit)
    {
        return OK;
    }
    /*初始化时IP过滤的参数配置*/
    stCommPara.bEspSpiDisable = 1;      /* ESP SPI是否参与匹配控制信号 */
    stCommPara.bAhSpiDisable = 1;       /* AH SPI是否参与匹配控制信号 */
    stCommPara.bEspAhSel= 0;           /* 0选ESP，1选AH */
    stCommPara.bIpv6NextHdSel = 0;
    stCommPara.eMaxBurst = IPF_BURST_16;       /* BURST最大长度 */
    stCommPara.bSpWrrModeSel = 0;
    stCommPara.bSpPriSel = 0;          /* SP优先级选择 */
    stCommPara.bFltAddrReverse = 1;        /* 配置为0,地址为大端 */
    stCommPara.bFilterSeq = 0;         /* 过滤器配置顺序指示 */

    s32Ret = BSP_IPF_Init(&stCommPara) ;
    if (s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:&d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }
    g_u32IpfStAllInit = BSP_TRUE;
    
    return OK;
}

BSP_S32 IPF_ST_UL_INIT(BSP_VOID)
{
    IPF_CHL_CTRL_S stCtrl;
    IPF_FILTER_CONFIG_S stUlFilterInfo[100];
    BSP_S32 s32Ret = 0;
    BSP_U32 i = 0;
    
    memset(stUlFilterInfo, 0x0, 100*sizeof(IPF_FILTER_CONFIG_S));
    for(i=0;i<99;i++)
    {
        stUlFilterInfo[i].u32FilterID = i;
        stUlFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0xffffffff;
    }
    
    stUlFilterInfo[99].u32FilterID = 172;
    stUlFilterInfo[99].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x23C01;
    *(BSP_U32*)(stUlFilterInfo[99].stMatchInfo.u8SrcAddr) = 0xACA84649;
    *(BSP_U32*)(stUlFilterInfo[99].stMatchInfo.u8SrcMsk) = 0xFFFFFFFF;
    *(BSP_U32*)(stUlFilterInfo[99].stMatchInfo.u8DstAddr) = 0x0202014E;
    *(BSP_U32*)(stUlFilterInfo[99].stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo[99].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 1;
    stUlFilterInfo[99].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 5100;
    stUlFilterInfo[99].stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo[99].stMatchInfo.unDstPort.Bits.u16DstPortHi = 5100;
    stUlFilterInfo[99].stMatchInfo.unTrafficClass.u32ServiceType = 3;
    stUlFilterInfo[99].stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
    stUlFilterInfo[99].stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo[99].stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo[99].stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo[99].stMatchInfo.u32FltSpi = 4;

    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_INIT:%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    stCtrl.bDataChain = BSP_FALSE;
    stCtrl.bEndian = BSP_TRUE; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 0;
    s32Ret = BSP_IPF_ConfigUlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, stUlFilterInfo, 100);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = BSP_IPF_ChannelEnable(IPF_CHANNEL_UP, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ChannelEnable :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    if((g_IpfUlIntSemId = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY)) == NULL)
    {
        IPF_PRINT("TESTERROR    semBCreate :%d\n",__LINE__);
        return ERROR;
    }

    if((g_IpfUlTaskSemId = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY)) == NULL)
    {
        IPF_PRINT("TESTERROR    semBCreate :%d\n",__LINE__);
        return ERROR;
    }

    g_IpfUlTaskId = taskSpawn("IpfUlTask1", 132, 2000, 20000, (FUNCPTR) IPF_UL_Task_1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    return OK;
}

BSP_S32 IPF_ST_DL_INIT(BSP_VOID)
{
    IPF_CHL_CTRL_S stCtrl;
    IPF_FILTER_CONFIG_S stDlFilterInfo;
    BSP_S32 s32Ret = 0;

    memset(&stDlFilterInfo, 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stDlFilterInfo.u32FilterID = 176;
    stDlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x53C01;
    *(BSP_U32*)(stDlFilterInfo.stMatchInfo.u8SrcAddr) = 0xACA84649;
    *(BSP_U32*)(stDlFilterInfo.stMatchInfo.u8SrcMsk) = 0xFFFFFFFF;
    *(BSP_U32*)(stDlFilterInfo.stMatchInfo.u8DstAddr) = 0x0202014E;
    *(BSP_U32*)(stDlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stDlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 1;
    stDlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 5100;
    stDlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stDlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 5100;
    stDlFilterInfo.stMatchInfo.unTrafficClass.u32ServiceType = 3;
    stDlFilterInfo.stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
    stDlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stDlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stDlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stDlFilterInfo.stMatchInfo.u32FltSpi = 4;

    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
    IPF_PRINT("TESTERROR    IPF_ST_INIT :%d\n",__LINE__);
    return ERROR;
    }

    stCtrl.bDataChain = BSP_TRUE;
    stCtrl.bEndian = BSP_TRUE; /* 小端 */
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 0;
    s32Ret = BSP_IPF_ConfigDlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }

    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_DOWN, &stDlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;   
    } 

    s32Ret = BSP_IPF_ChannelEnable(IPF_CHANNEL_DOWN, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ChannelEnable :%d, s32ret = %x\n",__LINE__, s32Ret);
        return ERROR;
    }
    
    return OK;
}
#else
struct semaphore g_IpfDlTaskSemId;
struct semaphore g_IpfDlIntSemId;
struct task_struct * g_IpfDlTaskId;

typedef int (*IPFTHREADFN)(void *pdata);

BSP_S32 IpfDlIntCb(BSP_VOID)
{
    up(&g_IpfDlIntSemId);
    return OK;
}
BSP_VOID IPF_DL_Task_1(BSP_VOID)
{
    BSP_U32 u32Num = 0;
    IPF_RD_DESC_S stRd[IPF_ULRD_DESC_SIZE];
    TTF_MEM_ST* pstTtf = BSP_NULL;
    BSP_U32 i = 0;

    while(1)
    { 
        memset(stRd, 0x0, (sizeof(IPF_RD_DESC_S) * IPF_ULRD_DESC_SIZE));
        u32Num = IPF_ULRD_DESC_SIZE;
        down(&g_IpfDlIntSemId);
        if(*g_ipftestdebug)
        {
            IPF_PRINT("TESTERROR    IPF_DL_Task_1 in \n");
        }
        BSP_IPF_GetDlRd(&u32Num, stRd);
        for(i = 0; i < u32Num; i++)
        {
            if(stRd[i].u32UsrField2 != 0)
            {
                pstTtf = (TTF_MEM_ST*)(IO_ADDRESS(stRd[i].u32UsrField2));
                if(*g_ipftestdebug)
                {
                    IPF_PRINT("TESTERROR    IPF_DL_Task_1:%d, u32Num = %d, i = %d \n",__LINE__, u32Num, i);
                    IPF_PRINT("pstTtf = %x pData = %x\n",(BSP_U32)pstTtf, (BSP_U32)(IO_ADDRESS(pstTtf->pData)));
                }
                BSP_SFREE(IO_ADDRESS(pstTtf->pData));
                BSP_SFREE(pstTtf);   
            }
            if(stRd[i].u16Result != 5)
            {
                IPF_PRINT("TESTERROR    IPF_DL_Task_1:%d, u16Result = %x, i = %d \n",__LINE__, stRd[i].u16Result, i);
            }
        }
        if(*g_ipftestdebug)
        {
            IPF_PRINT("TESTERROR    IPF_DL_Task_1 out \n");
        }
        up(&g_IpfDlTaskSemId);

        break;
    }
}
BSP_S32 IPF_ST_DL_INIT(BSP_VOID)
{
    sema_init(&g_IpfDlTaskSemId, 0);
    sema_init(&g_IpfDlIntSemId, 0);

    g_IpfDlTaskId = kthread_run((IPFTHREADFN)IPF_DL_Task_1, BSP_NULL, "IpfDlTask");  

    return OK;
}

BSP_S32 __init BSP_IPF_ST_INIT(BSP_VOID)
{
    return OK;
}
BSP_VOID __exit BSP_IPF_ST_EXIT(BSP_VOID)
{

}
#endif

/****************************************
* 0   两核各自都用的测试用例
* 1   先执行M核后执行A核用例
* 2   C   核的测试用例
* 3   先执行A核后执行M核用例
****************************************/

/* test BSP_IPF_ConfigTimeout */
BSP_S32 IPF_ST_ConfigTimeout(BSP_U32 u32Timeout)
{
    BSP_S32 s32ret = 0;
    s32ret = BSP_IPF_ConfigTimeout(u32Timeout);
    if(s32ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    IPF_ST_ConfigTimeout:%d, u32Timeout :%d\n",__LINE__, u32Timeout);
        return BSP_ERROR;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_TIME_OUT) != (0x10000 | u32Timeout))
    {
        IPF_PRINT("TESTERROR    IPF_ST_ConfigTimeout:%d, u32Timeout :%d\n",__LINE__, u32Timeout);
        return BSP_ERROR;
    }
    return BSP_OK;
}
BSP_S32 IPF_ST_TimeoutCheck(BSP_U32 u32Timeout)
{
    BSP_S32 s32ret = 0;
    s32ret = BSP_IPF_ConfigTimeout(u32Timeout);
    if(s32ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    IPF_ST_TimeoutCheck:%d, u32Timeout :%d\n",__LINE__, u32Timeout);
        return BSP_ERROR;
    }
    return BSP_OK;
}
BSP_S32 BSP_IPF_ST_001(BSP_VOID)
{
    BSP_U32 u32Timeout = 0;
    BSP_U32 u32OldTime = 0;
    BSP_S32 s32ret = 0;

    BSP_REG_READ(IPF_REGBASE_ADR, IPF_TIME_OUT, u32OldTime);

    s32ret = IPF_ST_TimeoutCheck(u32Timeout);
   
    u32Timeout = 1;
    s32ret += IPF_ST_ConfigTimeout(u32Timeout);

    u32Timeout = 0xffff;
    s32ret += IPF_ST_ConfigTimeout(u32Timeout);

    u32Timeout = 0x10000;
    s32ret += IPF_ST_TimeoutCheck(u32Timeout);

    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_TIME_OUT, u32OldTime);

    if(BSP_OK == s32ret)
    {
        IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);
        return BSP_OK;
    }
    else
    {
        return BSP_ERROR;
    }
}

/* test BSP_IPF_SetPktLen */
BSP_S32 BSP_IPF_ST_002(BSP_VOID)
{
    BSP_S32 s32Ret;
    BSP_U32 u32MaxLen = 0;
    BSP_U32 u32MinLen = 0;

    s32Ret = BSP_IPF_SetPktLen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetPktLen:%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 0x5;
    u32MinLen = 0x6;
    s32Ret = BSP_IPF_SetPktLen(u32MaxLen,u32MinLen);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetPktLen:%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 0x345;
    u32MinLen = 0x123;
    s32Ret = BSP_IPF_SetPktLen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetPktLen:%d\n",__LINE__);
        return ERROR;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_PKT_LEN) != 0x3450123)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetPktLen:%d\n",__LINE__);
        return ERROR;
    }

    u32MaxLen = 1500;
    u32MinLen = 40;
    s32Ret = BSP_IPF_SetPktLen(u32MaxLen,u32MinLen);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetPktLen:%d\n",__LINE__);
        return ERROR;
    }
    
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);
    return OK;
}

/* test BSP_IPF_GetStat */
BSP_S32 BSP_IPF_ST_003(BSP_VOID)
{
    BSP_S32 s32Ret;
    IPF_FILTER_STAT_S stFilterStat;

    s32Ret = BSP_IPF_GetStat(BSP_NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetStat:%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_GetStat(&stFilterStat);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetStat:%d\n",__LINE__);
        return ERROR;
    }

    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);
    return OK;
}

#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
extern BSP_S32 BSP_IPF_ST_211(BSP_VOID);
extern BSP_S32 BSP_IPF_ST_212(BSP_VOID);
extern BSP_S32 BSP_IPF_ST_213(BSP_VOID);

BSP_S32 BSP_IPF_ST_101(BSP_VOID)
{
    BSP_U32 u32Num = 1;
    BSP_S32 s32Ret = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_UL_INIT:%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_RegisterWakeupUlCb(IpfUlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupUlCb:%d\n",__LINE__);
        return ERROR;
    }

    IPF_PRINT(" ACPU 可以输入测试用例\n");

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle:%d \n",__LINE__);
        return ERROR;
    }

    semDelete(g_IpfUlIntSemId);
    semDelete(g_IpfUlTaskSemId);
    taskDelete(g_IpfUlTaskId);

    return OK;
}

BSP_S32 BSP_IPF_ST_102(BSP_VOID)
{
    return BSP_IPF_ST_101();
}

BSP_S32 BSP_IPF_ST_103(BSP_VOID)
{
    BSP_U32 u32Num = 1;
    BSP_S32 s32Ret = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_UL_INIT:%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_RegisterWakeupUlCb(IpfUlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupUlCb:%d\n",__LINE__);
        return ERROR;
    }
    
    s32Ret = BSP_IPF_ConfigTimeout(0xFFFF);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigTimeout:%d\n",__LINE__);
        return ERROR;
    }

    IPF_PRINT(" A核可以输入测试用例\n");

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle:%d \n",__LINE__);
        return ERROR;
    }

    semDelete(g_IpfUlIntSemId);
    semDelete(g_IpfUlTaskSemId);
    taskDelete(g_IpfUlTaskId);

    s32Ret = BSP_IPF_ConfigTimeout(500);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigTimeout:%d\n",__LINE__);
        return ERROR;
    }
    
    return OK;
}

BSP_S32 BSP_IPF_ST_104(BSP_VOID)
{
    BSP_S32 s32Ret = 0;

    s32Ret = BSP_IPF_ST_101();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_101:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_ST_211();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_211:%d \n",__LINE__);
        return ERROR;
    }

    return OK;
}

BSP_S32 BSP_IPF_ST_105(BSP_VOID)
{
    BSP_S32 s32Ret = 0;

    s32Ret = BSP_IPF_ST_102();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_101:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_ST_212();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_211:%d \n",__LINE__);
        return ERROR;
    }

    return OK;
}

BSP_S32 BSP_IPF_ST_106(BSP_VOID)
{
    BSP_S32 s32Ret = 0;

    s32Ret = BSP_IPF_ST_103();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_101:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle:%d \n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_ST_213();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ST_211:%d \n",__LINE__);
        return ERROR;
    }

    return OK;
}

/* test BSP_IPF_Init */
BSP_S32 BSP_IPF_ST_201(BSP_VOID)
{
    BSP_S32 s32Ret;
    BSP_U32 u32OldPara = 0;
    IPF_COMMON_PARA_S stCommPara;

    BSP_REG_READ(IPF_REGBASE_ADR, IPF_CTRL, u32OldPara); 
    
    s32Ret = BSP_IPF_Init(BSP_NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:%d\n",__LINE__);
        goto error;
    }

    stCommPara.bEspSpiDisable = BSP_TRUE;
    stCommPara.bAhSpiDisable = BSP_TRUE;
    stCommPara.bEspAhSel = BSP_TRUE;
    stCommPara.bIpv6NextHdSel = BSP_TRUE;
    stCommPara.eMaxBurst = IPF_BURST_8;
    stCommPara.bSpWrrModeSel = BSP_TRUE;
    stCommPara.bSpPriSel = BSP_TRUE;
    stCommPara.bFltAddrReverse = BSP_TRUE;
    stCommPara.bFilterSeq = BSP_TRUE;       
    s32Ret = BSP_IPF_Init(&stCommPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CTRL) != 0x3DF)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:%d, %x\n",__LINE__,*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CTRL));
        goto error;
    }

    stCommPara.bEspSpiDisable = BSP_FALSE;
    stCommPara.bAhSpiDisable = BSP_FALSE;
    stCommPara.bEspAhSel = BSP_FALSE;
    stCommPara.bIpv6NextHdSel = BSP_FALSE;
    stCommPara.eMaxBurst = IPF_BURST_4;
    stCommPara.bSpWrrModeSel = BSP_FALSE;
    stCommPara.bSpPriSel = BSP_FALSE;
    stCommPara.bFltAddrReverse = BSP_FALSE;
    stCommPara.bFilterSeq = BSP_FALSE;       
    s32Ret = BSP_IPF_Init(&stCommPara);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CTRL) != 0x20)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_Init:%d, %x\n",__LINE__,*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CTRL));
        goto error;
    }

    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CTRL, u32OldPara); 
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);    
    return OK;
error:
    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CTRL, u32OldPara); 
    return ERROR;
}

/* test BSP_IPF_ConfigUlChannel */
BSP_S32 BSP_IPF_ST_202(BSP_VOID)
{
    BSP_S32 s32Ret;
    BSP_U32 u32OldPara = 0;
    IPF_CHL_CTRL_S stCtrl;

    BSP_REG_READ(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_UP), u32OldPara); 
    
    s32Ret = BSP_IPF_ConfigUlChannel(BSP_NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = BSP_TRUE;
    stCtrl.bEndian = BSP_TRUE;
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 1000;
    s32Ret = BSP_IPF_ConfigUlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CH_CTRL(IPF_CHANNEL_UP)) != 0x3E8000D)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = BSP_FALSE;
    stCtrl.bEndian = BSP_FALSE;
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 100;
    s32Ret = BSP_IPF_ConfigUlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CH_CTRL(IPF_CHANNEL_UP)) != 0x640000)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUlChannel:%d\n",__LINE__);
        goto error;
    }

    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_UP), u32OldPara); 
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);    
    return OK;
error:
    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_UP), u32OldPara); 
    return ERROR;
}

/* test BSP_IPF_ConfigDlChannel */
BSP_S32 BSP_IPF_ST_203(BSP_VOID)
{
    BSP_S32 s32Ret;
    BSP_U32 u32OldPara = 0;
    IPF_CHL_CTRL_S stCtrl;

    BSP_REG_READ(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_DOWN), u32OldPara); 
    
    s32Ret = BSP_IPF_ConfigDlChannel(BSP_NULL);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = BSP_TRUE;
    stCtrl.bEndian = BSP_TRUE;
    stCtrl.eIpfMode = IPF_MODE_FILTERONLY;
    stCtrl.u32WrrValue = 1000;
    s32Ret = BSP_IPF_ConfigDlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CH_CTRL(IPF_CHANNEL_DOWN)) != 0x3E8000D)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel:%d\n",__LINE__);
        goto error;
    }

    stCtrl.bDataChain = BSP_FALSE;
    stCtrl.bEndian = BSP_FALSE;
    stCtrl.eIpfMode = IPF_MODE_FILTERANDTRANS;
    stCtrl.u32WrrValue = 100;
    s32Ret = BSP_IPF_ConfigDlChannel(&stCtrl);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel:%d\n",__LINE__);
        goto error;
    }
    if(*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CH_CTRL(IPF_CHANNEL_DOWN)) != 0x640000)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDlChannel:%d\n",__LINE__);
        goto error;
    }

    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_DOWN), u32OldPara); 
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);    
    return OK;
error:
    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_CTRL(IPF_CHANNEL_DOWN), u32OldPara); 
    return ERROR;
}

/* test BSP_IPF_ChannelEnable */
BSP_S32 BSP_IPF_ST_204(BSP_VOID)
{
    BSP_U32 i = 0;
    IPF_CHANNEL_TYPE_E eChanType = IPF_CHANNEL_MAX;
    BSP_BOOL bFlag = BSP_FALSE;
    IpfChanState chan[4] = {{IPF_CHANNEL_UP,BSP_TRUE},
                                          {IPF_CHANNEL_UP,BSP_FALSE},
                                          {IPF_CHANNEL_DOWN,BSP_TRUE},
                                          {IPF_CHANNEL_DOWN,BSP_FALSE}};
    BSP_U32 u32OldPara = 0;
    BSP_S32 s32Ret;

    BSP_REG_READ(IPF_REGBASE_ADR, IPF_CH_EN, u32OldPara); 
    
    s32Ret = BSP_IPF_ChannelEnable(eChanType, bFlag);
    if(s32Ret != BSP_ERR_IPF_INVALID_PARA)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ChannelEnable:type=%d, flag=%d\n",eChanType,bFlag);
        goto error;
    }

    /* test  IPF_CHANNEL */
    for(i = 0; i < 4; i ++)
    {
        s32Ret = BSP_IPF_ChannelEnable(chan[i].chanType, chan[i].chanFlag);
        if(s32Ret != IPF_SUCCESS)
        {
            IPF_PRINT("TESTERROR    BSP_IPF_ChannelEnable:type=%d, flag=%d\n",chan[i].chanType,chan[i].chanFlag);
            goto error;
        }
        if((*(BSP_U32*)(IPF_REGBASE_ADR+IPF_CH_EN) & (1 << chan[i].chanType)) !=  (chan[i].chanFlag << chan[i].chanType))
        {
            IPF_PRINT("TESTERROR    BSP_IPF_ChannelEnabletype=%d flag=%d\n",chan[i].chanType,chan[i].chanFlag);
            goto error;
        }
    }

    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_EN, u32OldPara); 
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);    
    return OK;
 error:  
    BSP_REG_WRITE(IPF_REGBASE_ADR, IPF_CH_EN, u32OldPara); 
    return ERROR;    
}

BSP_S32 CmpFilterInfo(IPF_FILTER_CONFIG_S* p1, IPF_FILTER_CONFIG_S* p2)
{
    BSP_U32 i = 0;
    BSP_U32 u32Len = sizeof(IPF_FILTER_CONFIG_S);

    for(i=0; i<u32Len; i++)
    {
        if(*(BSP_U32*)p1 != *(BSP_U32*)p2)
        {
            return ERROR;
        }
    }
    return 0;
}

BSP_VOID PrintFilterInfo(BSP_U32* pu32FilterInfo)
{
    BSP_U32 i = 0;
    BSP_U32* p = pu32FilterInfo;

    for(i=0; i<25; i++)
    {
        IPF_PRINT("0x%08x    0x%08x    0x%08x    0x%08x\n", *(p+i), *(p+i+1), *(p+i+2), *(p+i+3));
        i = i+4;
    }
    IPF_PRINT("0x%08x    0x%08x\n", *(p+i), *(p+i+1));
}
/* test  测试上行过滤器设置和查询 */
BSP_S32 BSP_IPF_ST_205(BSP_VOID)
{
    #define TST_NUM  (2)
    BSP_U32 i = 0;
    BSP_U32 filterID[TST_NUM] = {50,30};
    IPF_FILTER_CONFIG_S stUlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stUlFilterInfo1 = {0};
    BSP_S32 s32Ret= 0;

    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_INIT:%d\n",__LINE__);
        return ERROR;
    }

    memset(&stUlFilterInfo, 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stUlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcAddr) = 0x020113C6;//00xC6130102;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcMsk) = 0xFFFFFFFF;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstAddr) = 0x010113C6;//00xC6130101;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
    stUlFilterInfo.stMatchInfo.unTrafficClass.u32ServiceType = 3;
    stUlFilterInfo.stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
    stUlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16FltPri = 100;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 200;
    stUlFilterInfo.stMatchInfo.u32FltSpi = 4;

    /* 配置上行，PS ID 分别是50 和30*/
    for(i = 0; i < TST_NUM; i ++)
    {
        stUlFilterInfo.u32FilterID = filterID[i];
        s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 1);
        if(s32Ret != IPF_SUCCESS)    
        {
            IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:filterID=%d\n",filterID[i]);
            return ERROR;   
        }       
        if(BSP_IPF_GetFilter(IPF_CHANNEL_UP, filterID[i], &stUlFilterInfo1) != IPF_SUCCESS)
        {
            IPF_PRINT("TESTERROR    BSP_IPF_GetFilter:filterID=%d\n",filterID[i]);
            return ERROR; 
        }
        stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;

        s32Ret = CmpFilterInfo(&stUlFilterInfo, &stUlFilterInfo1);
        if(s32Ret != 0)
        {
            IPF_PRINT("TESTERROR    CmpFilterInfo:filterID=%d\n",filterID[i]);
            return ERROR; 
        }
    }
   
    /* 查询没有配置的Filter返回错误 */
    if(BSP_IPF_GetFilter(IPF_CHANNEL_UP, 50, &stUlFilterInfo1) != IPF_ERROR)
    {
            IPF_PRINT("TESTERROR    BSP_IPF_GetFilter:filterID=%d\n",filterID[i]);
        return ERROR; 
    }
    
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);    
    return OK; 
}

/* test  测试上行过滤器设置和查询(Ps ID 一致 ) */
BSP_S32 BSP_IPF_ST_206(BSP_VOID)
{
    IPF_FILTER_CONFIG_S stUlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stUlFilterInfoCheck= {0};
    IPF_FILTER_CONFIG_S stDlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stDlFilterInfoCheck= {0};
    BSP_S32 s32Ret = 0;

    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_INIT:%d\n",__LINE__);
        return ERROR;
    }
    
    memset(&stUlFilterInfo, 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stUlFilterInfo.u32FilterID = 2;
    stUlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcAddr) = 0x020113C6;//00xC6130102;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcMsk) = 0xFFFFFFFF;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstAddr) = 0x010113C6;//00xC6130101;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
    stUlFilterInfo.stMatchInfo.unTrafficClass.u32ServiceType = 3;
    stUlFilterInfo.stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
    stUlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16FltPri = 100;
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 200;
    stUlFilterInfo.stMatchInfo.u32FltSpi = 10;

    memcpy(&stDlFilterInfo, &stUlFilterInfo, sizeof(IPF_FILTER_CONFIG_S));
    stDlFilterInfo.stMatchInfo.u32FltSpi = 20;

    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_DOWN, &stDlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:%d\n",__LINE__);
        return ERROR;   
    }  
    
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:%d\n",__LINE__);
        return ERROR;   
    }
    
    if(BSP_IPF_GetFilter(IPF_CHANNEL_DOWN, 2, &stDlFilterInfoCheck) != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetFilter:%d\n",__LINE__);
        return ERROR; 
    }
    stDlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
       
    s32Ret = CmpFilterInfo(&stDlFilterInfo, &stDlFilterInfoCheck);
    if(s32Ret != 0)
    {
        IPF_PRINT("TESTERROR    CmpFilterInfo:%d\n",__LINE__);
        return ERROR; 
    }

    if(BSP_IPF_GetFilter(IPF_CHANNEL_UP, 2, &stUlFilterInfoCheck) != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetFilter:%d\n",__LINE__);
        return ERROR; 
    }
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
    
    s32Ret = CmpFilterInfo(&stUlFilterInfo, &stUlFilterInfoCheck);
    if(s32Ret != 0)
    {
        IPF_PRINT("TESTERROR    CmpFilterInfo:%d\n",__LINE__);
        return ERROR; 
    }

    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:%d\n",__LINE__);
        return ERROR;   
    } 
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_DOWN, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:%d\n",__LINE__);
        return ERROR;   
    } 
    
    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);        
    return OK; 
}

BSP_U32 IPF_ST_ConfigCheckFilter(IPF_CHANNEL_TYPE_E eChnType)
{
    BSP_U32 u32FilterNum = 150;
    IPF_FILTER_CONFIG_S stFilterInfo[150];
    IPF_FILTER_CONFIG_S stFilterInfoCheck;
    BSP_S32 s32Ret = 0;
    BSP_U32 i = 0;
    
    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_INIT:s32Ret=%d\n",s32Ret);
        return ERROR;
    }

    for(i = 0; i < u32FilterNum; i++)
    {
        memset(&stFilterInfo[i], 0x0, sizeof(IPF_FILTER_CONFIG_S));
        stFilterInfo[i].u32FilterID = i+2;
        stFilterInfo[i].stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = (i+1000)&0xFFFFFFF3;
        *(BSP_U32*)(stFilterInfo[i].stMatchInfo.u8SrcAddr) = i+2000;
        *(BSP_U32*)(stFilterInfo[i].stMatchInfo.u8SrcMsk) = i+3000;
        *(BSP_U32*)(stFilterInfo[i].stMatchInfo.u8DstAddr) = i+4000;
        *(BSP_U32*)(stFilterInfo[i].stMatchInfo.u8DstMsk) = i+5000;
        stFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortLo = i+10;
        stFilterInfo[i].stMatchInfo.unSrcPort.Bits.u16SrcPortHi = i+30;
        stFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortLo = i+10;
        stFilterInfo[i].stMatchInfo.unDstPort.Bits.u16DstPortHi = i+30;
        stFilterInfo[i].stMatchInfo.unTrafficClass.u32ServiceType = i+3;
        stFilterInfo[i].stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
        stFilterInfo[i].stMatchInfo.unNextHeader.u32Protocol = i+1;
        stFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Type = i+2;
        stFilterInfo[i].stMatchInfo.unFltCodeType.Bits.u16Code = i+3;
        stFilterInfo[i].stMatchInfo.unFltChain.Bits.u16FltPri = i+100;
        stFilterInfo[i].stMatchInfo.unFltChain.Bits.u16NextIndex = i+200;
        stFilterInfo[i].stMatchInfo.u32FltSpi = i+4;
    }
           
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_DOWN, stFilterInfo, u32FilterNum);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:filterNum=%d\n",u32FilterNum);
        return ERROR;   
    }

    for(i = 0; i < u32FilterNum; i++)
    {
        if(BSP_IPF_GetFilter(IPF_CHANNEL_DOWN, i+2, &stFilterInfoCheck) != IPF_SUCCESS)
        {
            IPF_PRINT("TESTERROR    BSP_IPF_GetFilter:filterID=%d\n",(i+2));
            return ERROR; 
        }
        if(i<u32FilterNum-1)
        {
            stFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = i+1;
        }
        else
        {
            stFilterInfoCheck.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;
        }
        
        s32Ret = CmpFilterInfo(&stFilterInfoCheck, &stFilterInfo[i]);
        if(s32Ret != 0)
        {
            IPF_PRINT("filterNum = %d \n",i);
            IPF_PRINT("========in=======\n");
            PrintFilterInfo((BSP_U32*)&stFilterInfo[i]);
            IPF_PRINT("========out=======\n");
            PrintFilterInfo((BSP_U32*)&stFilterInfoCheck);
            return ERROR; 
        }
    }
    
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_DOWN, stFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter:s32Ret=%d\n",s32Ret);
        return ERROR;   
    } 

    IPF_PRINT("%s : SUCCESS!\n",__FUNCTION__);           
    return OK; 
}
/* test 测试配置150 个上行过滤器并查询比较，用到了扩展过滤器 */
BSP_S32 BSP_IPF_ST_207(BSP_VOID)
{
    BSP_S32 s32Ret = 0;
    s32Ret =  IPF_ST_ConfigCheckFilter(IPF_CHANNEL_UP);
    if(OK == s32Ret)
    {
        IPF_PRINT("%s : SUCCESS\n",__FUNCTION__);          
    }
    return s32Ret;
}


/* test 测试配置150 个下行过滤器并查询比较，用到了扩展过滤器 */
BSP_S32 BSP_IPF_ST_208(BSP_VOID)
{
    BSP_S32 s32Ret = 0;
    s32Ret =  IPF_ST_ConfigCheckFilter(IPF_CHANNEL_DOWN);
    if(OK == s32Ret)
    {
        IPF_PRINT("%s : SUCCESS\n",__FUNCTION__);          
    }
    return s32Ret;  
}

/* test 测试过滤器设置和查询  */
BSP_S32 BSP_IPF_ST_209(BSP_VOID)
{
    IPF_FILTER_CONFIG_S stUlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stUlFilterInfoCheck= {0};
    IPF_FILTER_CONFIG_S stDlFilterInfo = {0};
    IPF_FILTER_CONFIG_S stDlFilterInfoCheck= {0};
    BSP_S32 s32Ret = 0;
    BSP_U32 i = 0;

    s32Ret = IPF_ST_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_INIT:%d\n",__LINE__);
        return ERROR;
    }

    memset(&stUlFilterInfo, 0x0, sizeof(IPF_FILTER_CONFIG_S));
    stUlFilterInfo.u32FilterID = 3;
    stUlFilterInfo.stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl = 0x13361;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcAddr) = 0x020113C6;//00xC6130102;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8SrcMsk) = 0xFFFFFFFF;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstAddr) = 0x010113C6;//00xC6130101;
    *(BSP_U32*)(stUlFilterInfo.stMatchInfo.u8DstMsk) = 0xFFFFFFFF;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortLo = 10;
    stUlFilterInfo.stMatchInfo.unSrcPort.Bits.u16SrcPortHi = 30;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortLo = 10;
    stUlFilterInfo.stMatchInfo.unDstPort.Bits.u16DstPortHi = 30;
    stUlFilterInfo.stMatchInfo.unTrafficClass.u32ServiceType = 3;
    stUlFilterInfo.stMatchInfo.unTrafficClassMsk.u32ServiceTypeMsk = 0xFF;
    stUlFilterInfo.stMatchInfo.unNextHeader.u32Protocol = 1;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Type = 2;
    stUlFilterInfo.stMatchInfo.unFltCodeType.Bits.u16Code = 3;
    stUlFilterInfo.stMatchInfo.u32FltSpi = 4;

    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 1);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter :%d\n",__LINE__);    
        return ERROR;   
    }
    if(BSP_IPF_GetFilter(IPF_CHANNEL_UP, 3, &stUlFilterInfoCheck) != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetFilter :%d\n",__LINE__);
        return ERROR; 
    }
    stUlFilterInfo.stMatchInfo.unFltChain.Bits.u16NextIndex = 511;    
   
    s32Ret = CmpFilterInfo(&stUlFilterInfo, &stUlFilterInfoCheck);
    if(s32Ret != 0)
    {
        IPF_PRINT("========in=======\n");
        PrintFilterInfo((BSP_U32*)&stUlFilterInfo);
        IPF_PRINT("========out=======\n");
        PrintFilterInfo((BSP_U32*)&stUlFilterInfoCheck);
        return ERROR; 
    }    
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter :%d\n",__LINE__);
        return ERROR;   
    } 
    if(BSP_IPF_GetFilter(IPF_CHANNEL_UP, 3, &stUlFilterInfoCheck) != IPF_ERROR)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetFilter :%d\n",__LINE__);
        return ERROR; 
    }
    s32Ret = BSP_IPF_SetFilter(IPF_CHANNEL_UP, &stUlFilterInfo, 0);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_SetFilter :%d\n",__LINE__);
        return ERROR;   
    } 
    
    IPF_PRINT("%s : SUCCESS\n",__FUNCTION__);          
    return OK; 

}

BSP_S32 BSP_IPF_ST_211(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U32 i = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_UL_INIT :%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_RegisterWakeupUlCb(IpfUlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupUlCb :%d\n",__LINE__);
        return ERROR;
    }    
    
    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stUlPara[0].u32Data = (BSP_U32)pu8Data;
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x211;
    stUlPara[0].u32UsrField3 = 0;

    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3= 1;

    s32Ret = BSP_IPF_ConfigUpFilter(IPF_ULBD_DESC_SIZE, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle :%d \n",__LINE__);
        return ERROR;
    }

    semDelete(g_IpfUlIntSemId);
    semDelete(g_IpfUlTaskSemId);
    taskDelete(g_IpfUlTaskId);

    return OK;
}

BSP_S32 BSP_IPF_ST_212(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[1];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U32 i = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_UL_INIT :%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_RegisterWakeupUlCb(IpfUlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupUlCb :%d\n",__LINE__);
        return ERROR;
    }    
    
    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stUlPara[0].u32Data = (BSP_U32)pu8Data;
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x212;
    stUlPara[0].u32UsrField3 = 0;

    s32Ret = BSP_IPF_ConfigUpFilter(1, stUlPara, BSP_FALSE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE - 1)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    stUlPara[0].u16UsrField1 = 1;
    stUlPara[0].u32UsrField3 = 3;
    s32Ret = BSP_IPF_ConfigUpFilter(1, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle :%d \n",__LINE__);
        return ERROR;
    }

    semDelete(g_IpfUlIntSemId);
    semDelete(g_IpfUlTaskSemId);
    taskDelete(g_IpfUlTaskId);

    return OK;
}

BSP_S32 BSP_IPF_ST_213(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U32 i = 0;
   
    s32Ret = IPF_ST_UL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_UL_INIT :%d\n",__LINE__);
        return ERROR;
    }

    s32Ret = BSP_IPF_RegisterWakeupUlCb(IpfUlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupUlCb :%d\n",__LINE__);
        return ERROR;
    }    

    s32Ret = BSP_IPF_ConfigTimeout(0xFFFF);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigTimeout :%d\n",__LINE__);
        return ERROR;
    }
    
    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stUlPara[0].u32Data = (BSP_U32)pu8Data;
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x213;
    stUlPara[0].u32UsrField3 = 0;

    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }

    s32Ret = BSP_IPF_ConfigUpFilter(32, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num < (IPF_ULBD_DESC_SIZE - 32))
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 3;
    s32Ret = BSP_IPF_ConfigUpFilter(IPF_ULBD_DESC_SIZE - 32, &stUlPara[32], BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }
    if(*g_ipftestdebug)
    {
        for(i = 0; i < IPF_ULBD_DESC_SIZE; i++)
        {
            IPF_PRINT(" test: %d  %x, %d\n", i, stUlPara[i].u32UsrField2 ,stUlPara[i].u32UsrField3);
        }
    }

    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);
    semTake(g_IpfUlTaskSemId, WAIT_FOREVER);

    s32Ret = BSP_IPF_UlStateIdle();
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_UlStateIdle :%d \n",__LINE__);
        return ERROR;
    }

    semDelete(g_IpfUlIntSemId);
    semDelete(g_IpfUlTaskSemId);
    taskDelete(g_IpfUlTaskId);

    s32Ret = BSP_IPF_ConfigTimeout(500);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigTimeout :%d\n",__LINE__);
        return ERROR;
    }
    return OK;
}
BSP_U32 IPF_StDlCheck()
{
    BSP_U32 u32CDNum = 0;
    BSP_U32 u32BDNum = 0;
    BSP_S32 s32Ret = BSP_OK;

    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }

    u32BDNum = BSP_IPF_GetDlBDNum(&u32CDNum);
    if(u32BDNum != IPF_DLBD_DESC_SIZE)
    {
        IPF_PRINT(" %d :  下行队列不为空u32BDNum = %d,  u32CDNum = %d\n"
        ,__LINE__, u32BDNum, u32CDNum);
        return ERROR;
    }
}
/* 1个TTF结点，配1个BD */
BSP_S32 BSP_IPF_ST_301(BSP_VOID)
{
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    IPF_CONFIG_DLPARAM_S stDlPara;
    TTF_MEM_ST stSrcTtf;
    TTF_MEM_ST* pstDstTtf;
    BSP_U32 u32Num = 1;
    BSP_S32 s32Ret = BSP_OK;
   
    if(BSP_ERROR == IPF_StDlCheck())
    {
        return BSP_ERROR;
    }
    stSrcTtf.usUsed = 1500;
    stSrcTtf.pData = cacheDmaMalloc(stSrcTtf.usUsed);
    stSrcTtf.pNext = BSP_NULL;
    if(stSrcTtf.pData == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pstDstTtf = BSP_SMALLOC(sizeof(TTF_MEM_ST), MEM_ICC_DDR_POOL);
    if(pstDstTtf == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  BSP_SMALLOC :%d\n",__LINE__);
        goto error1;
    }
    pstDstTtf->usUsed = stSrcTtf.usUsed;
    pstDstTtf->pData = BSP_SMALLOC(pstDstTtf->usUsed, MEM_ICC_DDR_POOL);
    if(pstDstTtf->pData == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = stSrcTtf.usUsed;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(stSrcTtf.pData, 0x0, stSrcTtf.usUsed);
    memcpy(stSrcTtf.pData, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(stSrcTtf.pData+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));
    
    stDlPara.pstSrcTtf = &stSrcTtf;
    stDlPara.pstDstTtf = pstDstTtf;
    stDlPara.u16UsrField = 200; 
    s32Ret = BSP_IPF_ConfigDownFilter(u32Num, &stDlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error3;
    } 

    taskDelay(200);
    
    //BSP_IPF_ST_ReleaseDlSrcMem ();
    cacheDmaFree(stSrcTtf.pData);
    s32Ret = BSP_IPF_DlStateIdle();
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_DlStateIdle :%d\n",__LINE__);
        return ERROR;
    } 

    return OK;
    
error3:
    BSP_SFREE(pstDstTtf->pData);
error2:
    BSP_SFREE(pstDstTtf);
error1:
    cacheDmaFree(stSrcTtf.pData);
    return ERROR;
}

/* 5个TTF结点，配1个BD */
BSP_S32 BSP_IPF_ST_302(BSP_VOID)
{
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U8* pu8IPData;
    BSP_U32 u32Len = 1000;
    IPF_CONFIG_DLPARAM_S stDlPara;
    TTF_MEM_ST stSrcTtf[5];
    TTF_MEM_ST* pstDstTtf;
    BSP_U32 u32Num = 1;
    BSP_S32 s32Ret = BSP_OK;

    if(BSP_ERROR == IPF_StDlCheck())
    {
        return BSP_ERROR;
    }

    pu8IPData = (BSP_U8*)cacheDmaMalloc(u32Len);
    if(pu8IPData == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        return ERROR;
    }

    pstDstTtf = BSP_SMALLOC(sizeof(TTF_MEM_ST), MEM_ICC_DDR_POOL);
    if(pstDstTtf == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  BSP_SMALLOC :%d\n",__LINE__);
        goto error1;
    }
    pstDstTtf->usUsed = u32Len;
    pstDstTtf->pData = BSP_SMALLOC(pstDstTtf->usUsed, MEM_ICC_DDR_POOL);
    if(pstDstTtf->pData == BSP_NULL)
    {
        IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
        goto error2;
    }
    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u32Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8IPData, 0x0, u32Len);
    memcpy(pu8IPData, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8IPData+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stSrcTtf[0].usUsed = 200;
    stSrcTtf[0].pData = pu8IPData;
    stSrcTtf[0].pNext = &stSrcTtf[1];

    stSrcTtf[1].usUsed = 100;
    stSrcTtf[1].pData = pu8IPData + stSrcTtf[0].usUsed;
    stSrcTtf[1].pNext = &stSrcTtf[2];

    stSrcTtf[2].usUsed = 200;
    stSrcTtf[2].pData = pu8IPData + stSrcTtf[1].usUsed;
    stSrcTtf[2].pNext = &stSrcTtf[3];

    stSrcTtf[3].usUsed = 200;
    stSrcTtf[3].pData = pu8IPData + stSrcTtf[2].usUsed;
    stSrcTtf[3].pNext = &stSrcTtf[4];

    stSrcTtf[4].usUsed = 300;
    stSrcTtf[4].pData = pu8IPData + stSrcTtf[3].usUsed;
    stSrcTtf[4].pNext = BSP_NULL;
    
    stDlPara.pstSrcTtf = stSrcTtf;
    stDlPara.pstDstTtf = pstDstTtf;
    stDlPara.u16UsrField = 200; 
    s32Ret = BSP_IPF_ConfigDownFilter(u32Num, &stDlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error3;
    } 

    taskDelay(200);
    
    //BSP_IPF_ST_ReleaseDlSrcMem ();
    cacheDmaFree(pu8IPData);

    s32Ret = BSP_IPF_DlStateIdle();
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_DlStateIdle :%d\n",__LINE__);
        return ERROR;
    } 

    return OK;
    
error3:
    BSP_SFREE(pstDstTtf->pData);
error2:
    BSP_SFREE(pstDstTtf);
error1:
    cacheDmaFree(pu8IPData);
    return ERROR;
}

/* 5个TTF结点，配32个BD */
BSP_S32 BSP_IPF_ST_303(BSP_VOID)
{
    #define BDNUM   32
    BSP_U32 i = 0;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U8* pu8IPData[BDNUM];
    BSP_U32 u32Len = 1000;
    IPF_CONFIG_DLPARAM_S stDlPara[BDNUM];
    TTF_MEM_ST stSrcTtf[BDNUM][5];
    TTF_MEM_ST* pstDstTtf[BDNUM];
    BSP_U32 u32Num = BDNUM;
    BSP_S32 s32Ret = BSP_OK;

    if(BSP_ERROR == IPF_StDlCheck())
    {
        return BSP_ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u32Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;

    for(i = 0; i < BDNUM; i++)
    {
        pu8IPData[i] = (BSP_U8*)cacheDmaMalloc(u32Len);
        if(pu8IPData[i] == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
            goto error1;
        }

        pstDstTtf[i] = BSP_SMALLOC(sizeof(TTF_MEM_ST), MEM_ICC_DDR_POOL);
        if(pstDstTtf[i] == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  BSP_SMALLOC :%d\n",__LINE__);
            goto error2;
        }
        pstDstTtf[i]->usUsed = u32Len;
        pstDstTtf[i]->pData = BSP_SMALLOC(pstDstTtf[i]->usUsed, MEM_ICC_DDR_POOL);
        if(pstDstTtf[i]->pData == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
            goto error3;
        }
        
        memset(pu8IPData[i], 0x0, u32Len);
        memcpy(pu8IPData[i], &stIPHeader, sizeof(StreamIPv4Header));
        memcpy(pu8IPData[i]+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

        stSrcTtf[i][0].usUsed = 200;
        stSrcTtf[i][0].pData = pu8IPData[i];
        stSrcTtf[i][0].pNext = &stSrcTtf[i][1];

        stSrcTtf[i][1].usUsed = 100;
        stSrcTtf[i][1].pData = pu8IPData[i] + stSrcTtf[i][0].usUsed;
        stSrcTtf[i][1].pNext = &stSrcTtf[i][2];

        stSrcTtf[i][2].usUsed = 200;
        stSrcTtf[i][2].pData = pu8IPData[i] + stSrcTtf[i][1].usUsed;
        stSrcTtf[i][2].pNext = &stSrcTtf[i][3];

        stSrcTtf[i][3].usUsed = 200;
        stSrcTtf[i][3].pData = pu8IPData[i] + stSrcTtf[i][2].usUsed;
        stSrcTtf[i][3].pNext = &stSrcTtf[i][4];

        stSrcTtf[i][4].usUsed = 300;
        stSrcTtf[i][4].pData = pu8IPData[i] + stSrcTtf[i][3].usUsed;
        stSrcTtf[i][4].pNext = BSP_NULL;
    
        stDlPara[i].pstSrcTtf = stSrcTtf[i];
        stDlPara[i].pstDstTtf = pstDstTtf[i];
        stDlPara[i].u16UsrField = 200; 
        if(*g_ipftestdebug)
        {
            IPF_PRINT("pstDstTtf = 0x%x, pData = 0x%x\n", pstDstTtf[i], pstDstTtf[i]->pData);
        }
    }
    
    s32Ret = BSP_IPF_ConfigDownFilter(u32Num, stDlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error3;
    } 

    taskDelay(200);

    //BSP_IPF_ST_ReleaseDlSrcMem ();
    for(i = 0; i < BDNUM; i++)
    {
        if(pu8IPData[i] != BSP_NULL)
        {
            cacheDmaFree(pu8IPData[i]);
        }
    }    
    s32Ret = BSP_IPF_DlStateIdle();
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_DlStateIdle :%d\n",__LINE__);
        return ERROR;
    } 
    return OK;
error3:
    for(i = 0; i < BDNUM; i++)
    {
        if(pstDstTtf[i]->pData != BSP_NULL)
        {
            BSP_SFREE(pstDstTtf[i]->pData);
        }
    }
error2:
    for(i = 0; i < BDNUM; i++)
    {
        if(pstDstTtf[i] != BSP_NULL)
        {
            BSP_SFREE(pstDstTtf[i]);
        }
    }
error1:
    for(i = 0; i < BDNUM; i++)
    {
        if(pu8IPData[i] != BSP_NULL)
        {
            cacheDmaFree(pu8IPData[i]);
        }
    }
    return ERROR;
}

/* 5个TTF结点，配64个BD */
BSP_S32 BSP_IPF_ST_304(BSP_VOID)
{
    #define BDNUM   64
    BSP_U32 i = 0;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U8* pu8IPData[BDNUM];
    BSP_U32 u32Len = 1200;
    IPF_CONFIG_DLPARAM_S stDlPara[BDNUM];
    TTF_MEM_ST stSrcTtf[BDNUM][5];
    TTF_MEM_ST* pstDstTtf[BDNUM];
    BSP_U32 u32Num = BDNUM;
    BSP_S32 s32Ret = 0;

    if(BSP_ERROR == IPF_StDlCheck())
    {
        return BSP_ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u32Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
    
    for(i = 0; i < BDNUM; i++)
    {
        pu8IPData[i] = (BSP_U8*)cacheDmaMalloc(u32Len);
        if(pu8IPData[i] == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
            goto error1;
        }

        pstDstTtf[i] = BSP_SMALLOC(sizeof(TTF_MEM_ST), MEM_ICC_DDR_POOL);
        if(pstDstTtf[i] == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  BSP_SMALLOC :%d\n",__LINE__);
            goto error2;
        }
        pstDstTtf[i]->usUsed = u32Len;
        pstDstTtf[i]->pData = BSP_SMALLOC(pstDstTtf[i]->usUsed, MEM_ICC_DDR_POOL);
        if(pstDstTtf[i]->pData == BSP_NULL)
        {
            IPF_PRINT("TESTERROR  cacheDmaMalloc :%d\n",__LINE__);
            goto error3;
        }
        
        memset(pu8IPData[i], 0x0, u32Len);
        memcpy(pu8IPData[i], &stIPHeader, sizeof(StreamIPv4Header));
        memcpy(pu8IPData[i]+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

        stSrcTtf[i][0].usUsed = 300;
        stSrcTtf[i][0].pData = pu8IPData[i];
        stSrcTtf[i][0].pNext = &stSrcTtf[i][1];

        stSrcTtf[i][1].usUsed = 100;
        stSrcTtf[i][1].pData = pu8IPData[i] + stSrcTtf[i][0].usUsed;
        stSrcTtf[i][1].pNext = &stSrcTtf[i][2];

        stSrcTtf[i][2].usUsed = 200;
        stSrcTtf[i][2].pData = pu8IPData[i] + stSrcTtf[i][1].usUsed;
        stSrcTtf[i][2].pNext = &stSrcTtf[i][3];

        stSrcTtf[i][3].usUsed = 100;
        stSrcTtf[i][3].pData = pu8IPData[i] + stSrcTtf[i][2].usUsed;
        stSrcTtf[i][3].pNext = &stSrcTtf[i][4];

        stSrcTtf[i][4].usUsed = 500;
        stSrcTtf[i][4].pData = pu8IPData[i] + stSrcTtf[i][3].usUsed;
        stSrcTtf[i][4].pNext = BSP_NULL;
    
        stDlPara[i].pstSrcTtf = stSrcTtf[i];
        stDlPara[i].pstDstTtf = pstDstTtf[i];
        stDlPara[i].u16UsrField = 200; 
        if(*g_ipftestdebug)
        {
            IPF_PRINT("pstDstTtf = 0x%x, pData = 0x%x\n", pstDstTtf[i], pstDstTtf[i]->pData);
        }
    }
    
    s32Ret = BSP_IPF_ConfigDownFilter(u32Num, stDlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigDownFilter :%d\n",__LINE__);
        goto error3;
    } 

    taskDelay(200);
    
    //BSP_IPF_ST_ReleaseDlSrcMem ();
    for(i = 0; i < BDNUM; i++)
    {
        if(pu8IPData[i] != BSP_NULL)
        {
            cacheDmaFree(pu8IPData[i]);
        }
    }    
    s32Ret = BSP_IPF_DlStateIdle();
    if(s32Ret != IPF_SUCCESS)    
    {
        IPF_PRINT("TESTERROR    BSP_IPF_DlStateIdle :%d\n",__LINE__);
        return ERROR;
    } 
    
    return OK;
error3:
    for(i = 0; i < BDNUM; i++)
    {
        if(pstDstTtf[i]->pData != BSP_NULL)
        {
            BSP_SFREE(pstDstTtf[i]->pData);
        }
    }
error2:
    for(i = 0; i < BDNUM; i++)
    {
        if(pstDstTtf[i] != BSP_NULL)
        {
            BSP_SFREE(pstDstTtf[i]);
        }
    }
error1:
    for(i = 0; i < BDNUM; i++)
    {
        if(pu8IPData[i] != BSP_NULL)
        {
            cacheDmaFree(pu8IPData[i]);
        }
    }
    return ERROR;
}
#else
/* 一次配置IPF_ULBD_DESC_SIZE 个BD */
BSP_S32 BSP_IPF_ST_101(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U32 i = 0;

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    IPF_PRINT("sizeof(StreamIPv4Header) = %d  sizeof(StreamUDP) = %d \n", 
                      sizeof(StreamIPv4Header), sizeof(StreamUDP));

    stUlPara[0].u32Data = DDR_VIRT_TO_PHY(pu8Data);
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x101;
    stUlPara[0].u32UsrField3= 0;

    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }
    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 1;

    s32Ret = BSP_IPF_ConfigUpFilter(IPF_ULBD_DESC_SIZE, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    return OK;    
}

BSP_S32 BSP_IPF_ST_102(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[1];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num !=  IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stUlPara[0].u32Data = DDR_VIRT_TO_PHY(pu8Data);
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x102;
    stUlPara[0].u32UsrField3 = 0;

    s32Ret = BSP_IPF_ConfigUpFilter(1, stUlPara, BSP_FALSE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE - 1)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    stUlPara[0].u16UsrField1 = 1;
    stUlPara[0].u32UsrField3 = 3;
    s32Ret = BSP_IPF_ConfigUpFilter(1, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    return OK;    
}

BSP_S32 BSP_IPF_ST_103(BSP_VOID)
{
    IPF_CONFIG_ULPARAM_S stUlPara[IPF_ULBD_DESC_SIZE];
    BSP_U32 u32Num = 0;
    BSP_S32 s32Ret = 0;
    BSP_U8* pu8Data = BSP_NULL;
    BSP_U16 u16Len = 1500;
    StreamIPv4Header stIPHeader;
    StreamUDP stUDP;
    BSP_U32 i = 0;

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num != IPF_ULBD_DESC_SIZE)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        return ERROR;
    }

    pu8Data = (BSP_U8*)BSP_SMALLOC(u16Len, MEM_ICC_DDR_POOL);
    if(pu8Data == BSP_NULL)
    {
        IPF_PRINT("TESTERROR    BSP_SMALLOC :%d\n",__LINE__);
        return ERROR;
    }

    stIPHeader.Vers = 4;
    stIPHeader.HeaderLen = 5;
    stIPHeader.TOS = 3;
    stIPHeader.TOL = u16Len;
    stIPHeader.ID = 1;
    stIPHeader.ReservFlag = 0;
    stIPHeader.DF = 0;
    stIPHeader.MF = 0;
    stIPHeader.offset = 0;
    stIPHeader.TTL = 128;
    stIPHeader.Prot = 17; /* UDP */
    stIPHeader.Checksum = 0xEC3A;
    stIPHeader.SourceAddr = 0xACA84649;
    stIPHeader.DestAddr = 0x0202014E;

    stUDP.SrcPort = 5088;
    stUDP.DstPort = 2923;
        
    memset(pu8Data, 0x0, 1500);
    memcpy(pu8Data, &stIPHeader, sizeof(StreamIPv4Header));
    memcpy(pu8Data+sizeof(StreamIPv4Header), &stUDP, sizeof(StreamUDP));

    stUlPara[0].u32Data = DDR_VIRT_TO_PHY(pu8Data);
    stUlPara[0].u16Len = u16Len;
    stUlPara[0].u16UsrField1 = 0;
    stUlPara[0].u32UsrField2 = 0x103;
    stUlPara[0].u32UsrField3= 0;

    for(i = 1; i < IPF_ULBD_DESC_SIZE; i++)
    {
        memcpy(&stUlPara[i], &stUlPara[0], sizeof(IPF_CONFIG_ULPARAM_S));
        stUlPara[i].u16UsrField1 = i;
    }

    s32Ret = BSP_IPF_ConfigUpFilter(32, stUlPara, BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    u32Num = BSP_IPF_GetUlBDNum();
    if(u32Num < (IPF_ULBD_DESC_SIZE - 32))
    {
        IPF_PRINT("TESTERROR    BSP_IPF_GetUlBDNum :%d, u32Num = %d\n",__LINE__, u32Num);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    stUlPara[IPF_ULBD_DESC_SIZE-1].u32UsrField3 = 3;
    s32Ret = BSP_IPF_ConfigUpFilter(IPF_ULBD_DESC_SIZE - 32, &stUlPara[32], BSP_TRUE);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_ConfigUpFilter :%d, s32Ret = %x\n",__LINE__, s32Ret);
        BSP_SFREE(pu8Data);
        return ERROR;
    }

    if(*g_ipftestdebug)
    {
        for(i = 0; i < IPF_ULBD_DESC_SIZE; i++)
        {
            IPF_PRINT(" test: %d  %x, %d\n", i, stUlPara[i].u32UsrField2, stUlPara[i].u32UsrField3);
        }
    }
    return OK;    
}

BSP_S32 BSP_IPF_ST_104(BSP_VOID)
{
    return BSP_IPF_ST_101();
}

BSP_S32 BSP_IPF_ST_105(BSP_VOID)
{
    return BSP_IPF_ST_102();
}

BSP_S32 BSP_IPF_ST_106(BSP_VOID)
{
    return BSP_IPF_ST_103();
}

BSP_S32 BSP_IPF_ST_301(BSP_VOID)
{
    BSP_S32 s32Ret = 0;

    s32Ret = IPF_ST_DL_INIT();
    if(s32Ret != OK)
    {
        IPF_PRINT("TESTERROR    IPF_ST_DL_INIT :%d\n",__LINE__);
        return ERROR;
    }
    
    s32Ret = BSP_IPF_RegisterWakeupDlCb(IpfDlIntCb);
    if(s32Ret != IPF_SUCCESS)
    {
        IPF_PRINT("TESTERROR    BSP_IPF_RegisterWakeupDlCb :%d\n",__LINE__);
        return ERROR;
    }   

    IPF_PRINT("CCPU 可以输入测试用例\n");

    down(&g_IpfDlTaskSemId);
    
    return OK;
}

BSP_S32 BSP_IPF_ST_302(BSP_VOID)
{    
    return BSP_IPF_ST_301();
}

BSP_S32 BSP_IPF_ST_303(BSP_VOID)
{    
    return BSP_IPF_ST_301();
}

BSP_S32 BSP_IPF_ST_304(BSP_VOID)
{    
    return BSP_IPF_ST_301();
}
#endif

#ifdef __KERNEL__
EXPORT_SYMBOL(BSP_IPF_ST_001);
EXPORT_SYMBOL(BSP_IPF_ST_002);
EXPORT_SYMBOL(BSP_IPF_ST_003);
EXPORT_SYMBOL(BSP_IPF_ST_101);
EXPORT_SYMBOL(BSP_IPF_ST_102);
EXPORT_SYMBOL(BSP_IPF_ST_103);
EXPORT_SYMBOL(BSP_IPF_ST_104);
EXPORT_SYMBOL(BSP_IPF_ST_105);
EXPORT_SYMBOL(BSP_IPF_ST_106);
EXPORT_SYMBOL(BSP_IPF_ST_301);
EXPORT_SYMBOL(BSP_IPF_ST_302);
EXPORT_SYMBOL(BSP_IPF_ST_303);
EXPORT_SYMBOL(BSP_IPF_ST_304);
//module_param(g_ipftestdebug, int, 0);
MODULE_AUTHOR("luting00168886");
MODULE_DESCRIPTION("IPF TEST MODULE");
MODULE_LICENSE("GPL");
#endif
#endif

#ifdef __cplusplus
}
#endif


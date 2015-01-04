/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_DRV_IPF.h
*
*   作    者 :  
*
*   描    述 :  IPF模块用户接口文件
*
*   修改记录 :
*   1.修改日期 : 2011年1月21日
*     修改作者 : 
*     修改记录 : 创建 v1.00
*   2.修改日期 : 2012年8月4日
*     修改作者 : 
*     修改记录 : 源地址内存释放上移修改
*   3.修改日期 : 2012年11月29日
*     修改作者 : 
*     修改记录 : 新增桥接功能、双待双通以及低功耗场景备份恢复机制；
*                根据soc_ipf_interface.h提供接口，操作寄存器读写、位操作
*************************************************************************/

#ifndef    _BSP_DRV_IPF_H_
#define    _BSP_DRV_IPF_H_

#ifdef __cplusplus
extern "C" 
{ 
#endif /* __cplusplus */

/**************************************************************************
  头文件包含                            
**************************************************************************/
#include "product_config.h"
#if (FEATURE_IPF_VERSION == IPF_V200)
#ifdef __VXWORKS__
#include <vxWorks.h>
#include <lstLib.h>
#include "BSP.h"
#include "BSP_GLOBAL.h"
#else
#include "BSP.h"
#include <mach/hardware.h>
#include "MemoryLayout.h"
#include "soc_irqs.h"
#endif
#include "BSP_IPF.h"
#include "soc_baseaddr_interface.h"
#include "soc_ipf_interface.h"
/**************************************************************************
  宏定义 
**************************************************************************/
#define __BSP_IPF_DEBUG__

#ifdef _DRV_LLT_
#define __STATIC__      
#define __INLINE__ 
#define IPF_AXI_MEM_ADDR                ((BSP_U32)g_ipfInfoStub)         
#else
#define __STATIC__      static
#define __INLINE__      inline
#define IPF_AXI_MEM_ADDR                MEMORY_AXI_IPF_ADDR
#endif
#define IPF_AXI_MEM_SIZE                MEMORY_AXI_IPF_SIZE

/* IPF地址配置信息 */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define IPF_ULBD_MEM_ADDR               IPF_AXI_MEM_ADDR
#else
#define IPF_ULBD_MEM_ADDR               (IO_ADDRESS(IPF_AXI_MEM_ADDR))
#endif
#define IPF_ULBD_MEM_SIZE               (IPF_ULBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_ULRD_MEM_ADDR               (IPF_ULBD_MEM_ADDR + IPF_ULBD_MEM_SIZE)
#define IPF_ULRD_MEM_SIZE               (IPF_ULRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_ULAD0_MEM_ADDR              (IPF_ULRD_MEM_ADDR + IPF_ULRD_MEM_SIZE)
#define IPF_ULAD0_MEM_SIZE              (IPF_ULAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_ULAD1_MEM_ADDR              (IPF_ULAD0_MEM_ADDR + IPF_ULAD0_MEM_SIZE)
#define IPF_ULAD1_MEM_SIZE              (IPF_ULAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLBD_MEM_ADDR               (IPF_ULAD1_MEM_ADDR + IPF_ULAD1_MEM_SIZE)
#define IPF_DLBD_MEM_SIZE               (IPF_DLBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_DLRD_MEM_ADDR               (IPF_DLBD_MEM_ADDR + IPF_DLBD_MEM_SIZE)
#define IPF_DLRD_MEM_SIZE               (IPF_DLRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_DLAD0_MEM_ADDR              (IPF_DLRD_MEM_ADDR + IPF_DLRD_MEM_SIZE)
#define IPF_DLAD0_MEM_SIZE              (IPF_DLAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLAD1_MEM_ADDR              (IPF_DLAD0_MEM_ADDR + IPF_DLAD0_MEM_SIZE)
#define IPF_DLAD1_MEM_SIZE              (IPF_DLAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLCD_MEM_ADDR               (IPF_DLAD1_MEM_ADDR  + IPF_DLAD1_MEM_SIZE)
#define IPF_DLCD_MEM_SIZE               (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

#define IPF_INIT_ADDR                   (IPF_DLCD_MEM_ADDR + IPF_DLCD_MEM_SIZE)
#define IPF_INIT_SIZE                   16

#define IPF_ULBD_IDLENUM_ADDR           (IPF_INIT_ADDR + IPF_INIT_SIZE)
#define IPF_ULBD_IDLENUM_SIZE           16

#define IPF_DEBUG_INFO_ADDR             (IPF_ULBD_IDLENUM_ADDR + IPF_ULBD_IDLENUM_SIZE)
#define IPF_DEBUG_INFO_SIZE             sizeof(IPF_DEBUG_INFO_S)

#define IPF_DEBUG_DLCD_ADDR             (IPF_DEBUG_INFO_ADDR + IPF_DEBUG_INFO_SIZE)
#define IPF_DEBUG_DLCD_SIZE             (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

/* 保存下行CD读写指针 */
#define IPF_DLCD_PTR_ADDR               (IPF_DEBUG_DLCD_ADDR + IPF_DEBUG_DLCD_SIZE)
#define IPF_DLCD_PTR_SIZE               8

#define IPF_MEM_USED_SIZE               (IPF_DLCD_PTR_ADDR + IPF_DLCD_PTR_SIZE - IPF_ULBD_MEM_ADDR)

/* IPF属性配置信息 */
#define IPF_REG_NUM                         (172)         /* IPF寄存器个数 */
#define IPF_BF_NUM                          FEATURE_IPF_BF_NUM          /* 基本过滤器数目 */
#define IPF_TOTAL_FILTER_NUM                (256)         /* 过滤器总数目先使用一半 */
#define IPF_EXFLITER_NUM                    (IPF_TOTAL_FILTER_NUM-IPF_BF_NUM) /* 扩展过滤器数目 */
#define IPF_TAIL_INDEX                      (511)         /* 标识最后一个filter */
#define IPF_FILTERCHAIN_HEAD_INDEX          (0)           /* 过滤器链组头所在链的位置 */
#define IPF_FILTERTYPE_MASK                 (0xFFFF)      /* 区分过滤器是基本还是扩展滤波器 */
#define IPF_TIME_OUT_CFG                    (65)          /* RD超时时间0.1ms时钟频率166MHZ下 */
#define IPF_ULADQ_PLEN_TH                   (404)         /* 上行包长阈值 */
#define IPF_DLADQ_PLEN_TH                   (448)         /* 下行包长阈值 */
#define IPF_RESUME_COUNT                    (200)         /* 过滤规则恢复超时,单位10us,共2ms */
#define IPF_OBLIGATE_AD_NUM                 (3)           /* ADQ队列预留AD个数 */
#define IPF_OBLIGATE_BD_NUM                 (3)           /* ADQ队列预留BD个数 */
#define IPF_CH_IDLE                         (0x14)        /* 通道IDLE状态值 */
#define IPF_IDLE_TIMEOUT_NUM                (30)          /* 软件等待超时值,单位10ms,确保该时间内IPF处理完 */
#define IPF_ADQ_BUF_EPT_MASK                0x00000004    /* ADQ BUFF空预读状态mask */
#define IPF_ADQ_BUF_FULL_MASK               0x00000008    /* ADQ BUFF满预读状态mask */

/* IPF中断上报、屏蔽、状态寄存器位定义,上报、屏蔽、状态三者一一对应 */
#define IPF_UL_RPT_INT                     (1 << 0)    /* 上行结果上报 */
#define IPF_UL_TIMEOUT_INT                 (1 << 1)    /* 上行结果上报超时 */
#define IPF_UL_RDQ_DOWN_OVERFLOW_INT       (1 << 6)    /* 上行RDQ下溢 */
#define IPF_UL_BDQ_UP_OVERFLOW_INT         (1 << 7)    /* 上行BDQ上溢 */
#define IPF_UL_RDQ_FULL_INT                (1 << 8)    /* 上行RDQ满 */
#define IPF_UL_BDQ_EMPTY_INT               (1 << 9)    /* 上行通道BDQ空 */
#define IPF_UL_ADQ0_EMPTY_INT              (1 << 10)   /* 上行通道ADQ0空 */
#define IPF_UL_ADQ1_EMPTY_INT              (1 << 11)   /* 上行通道ADQ1空 */

#define IPF_DL_RPT_INT                     (1 << 16)   /* 下行结果上报 */
#define IPF_DL_TIMEOUT_INT                 (1 << 17)   /* 下行结果上报超时 */
#define IPF_DL_RDQ_DOWN_OVERFLOW_INT       (1 << 22)   /* 下行RDQ下溢 */
#define IPF_DL_BDQ_UP_OVERFLOW_INT         (1 << 23)   /* 下行BDQ上溢 */
#define IPF_DL_RDQ_FULL_INT                (1 << 24)   /* 下行RDQ满 */
#define IPF_DL_BDQ_EMPTY_INT               (1 << 25)   /* 下行通道BDQ空 */
#define IPF_DL_ADQ0_EMPTY_INT              (1 << 26)   /* 下行通道ADQ0空 */
#define IPF_DL_ADQ1_EMPTY_INT              (1 << 27)   /* 下行通道ADQ1空 */
/* INTO中断上报情况: */
#define IPF_INT_OPEN0                       ( IPF_UL_RPT_INT \
                                            | IPF_UL_TIMEOUT_INT \
                                            | IPF_UL_ADQ0_EMPTY_INT \
                                            | IPF_UL_ADQ1_EMPTY_INT)   
/* INT1中断上报情况: */                                            
#define IPF_INT_OPEN1                       ( IPF_DL_RPT_INT \
                                            | IPF_DL_TIMEOUT_INT \
                                            | IPF_DL_ADQ0_EMPTY_INT \
                                            | IPF_DL_ADQ1_EMPTY_INT)  
#ifdef __VXWORKS__
#define IPF_PRINT   printf
#define IPF_DEBUG(enLogLevel, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    BSP_TRACE(enLogLevel, BSP_MODU_IPF, fmt,arg1,arg2,arg3,arg4,arg5,arg6)
#ifdef _DRV_LLT_
#define IPF_REGBASE_ADR                 ((BSP_U32)g_ipfRegStub)
#else
#define IPF_REGBASE_ADR                 SOC_IPF_BASE_ADDR
#endif
#define INT_LVL_IPF                     INT_LVL_IPF_0
#define INT_VEC_IPF                     IVEC_TO_INUM(INT_LVL_IPF)
#elif defined(__KERNEL__)
#define IPF_PRINT   printk
#define IPF_DEBUG(fmt, arg...) \
    printk(KERN_ERR fmt, ##arg)
#ifdef _DRV_LLT_
#define IPF_REGBASE_ADR                 ((BSP_U32)g_ipfRegStub)
#else
#define IPF_REGBASE_ADR                 IO_ADDRESS(SOC_IPF_BASE_ADDR)
#endif
#define INT_LVL_IPF                     IRQ_IPF1
#define INT_VEC_IPF                     IVEC_TO_INUM(INT_LVL_IPF)
#endif

#define IPF_REG_WRITE(uwAddr,uwValue)   (*((volatile BSP_U32 *)(uwAddr)) = uwValue)
#define IPF_REG_READ(uwAddr,uwValue)    (uwValue = *((volatile BSP_U32 *)(uwAddr))) 
/**************************************************************************
  枚举定义
**************************************************************************/

/**************************************************************************
  STRUCT定义
**************************************************************************/
typedef struct tagIPF_UL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;    
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM      
    BSP_IPF_WakeupUlCb pFnUlIntCb; /* 中断中唤醒的PS任务 */
    BSP_IPF_AdqEmptyUlCb pAdqEmptyUlCb;
#endif   
    BSP_U32* pu32IdleBd; /* 记录上一次获取的空闲BD 数 */
}IPF_UL_S;

typedef struct tagIPF_DL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;    
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;
    IPF_CD_DESC_S* pstIpfCDQ;
    IPF_CD_DESC_S* pstIpfDebugCDQ;
#ifndef PRODUCT_CFG_CORE_TYPE_MODEM     
    BSP_IPF_WakeupDlCb pFnDlIntCb; /* 中断中唤醒的PS任务 */
    BSP_IPF_AdqEmptyDlCb pAdqEmptyDlCb;
#endif    
    BSP_U32* u32IpfCdRptr; /* 当前可以读出的位置 */
    BSP_U32* u32IpfCdWptr;
    BSP_U32  u32IdleBd; /* 记录上一次获取的空闲BD 数 */
}IPF_DL_S;

typedef struct tagIPF_ID_S
{
    BSP_U32 u32PsID;
    BSP_U32 u32FilterID;
    struct tagIPF_ID_S* pstNext;
}IPF_ID_S;

typedef struct tagIPF_FILTER_INFO_S
{
    IPF_ID_S* pstUseList;
    BSP_U32 u32FilterNum;
}IPF_FILTER_INFO_S;

typedef struct tagIPF_DEBUG_INFO_S
{
    BSP_U32 u32IpfDebug;            /* 允许debug标识:1-允许 0-禁止 */

    BSP_U32 u32UlResultTime;        /* 上行最后一次上报结果中断时间 */
    BSP_U32 u32UlGetRdTime;         /* 上行最后一次获取处理结果时间 */
    BSP_U32 u32DlResultTime;        /* 下行最后一次上报结果中断时间 */
    BSP_U32 u32DlGetRdTime;         /* 下行最后一次获取处理结果时间 */
    BSP_U32 u32UlResultCnt;         /* 上行上报结果中断计数 */
    BSP_U32 u32UlResultTimeoutCnt;  /* 上行上报结果超时中断计数 */
    BSP_U32 u32DlResultCnt;         /* 下行上报结果中断计数 */
    BSP_U32 u32DlResultTimeoutCnt;  /* 下行上报结果超时中断计数 */

    BSP_U32 u32UlBdqEmptyCnt;       /* 上行BDQ空计数 */
    BSP_U32 u32UlRdqFullCnt;        /* 上行RDQ满计数 */
    BSP_U32 u32DlBdqEmptyCnt;       /* 下行BDQ空计数 */
    BSP_U32 u32DlRdqFullCnt;        /* 下行RDQ满计数 */
    BSP_U32 u32UlBdqOverflow;       /* 中断上报上行BD队列溢出次数 */
    BSP_U32 u32DlBdqOverflow;       /* 中断上报下行BD队列溢出次数 */
    BSP_U32 u32UlBdNotEnough;       /* 上行配置BD,BD不够用次数 */
    BSP_U32 u32DlBdNotEnough;       /* 下行配置BD,BD不够用次数 */
    BSP_U32 u32UlAdq0Empty;         /* 中断上报上行ADQ0空次数 */
    BSP_U32 u32UlAdq1Empty;         /* 中断上报上行ADQ1空次数 */
    BSP_U32 u32DlAdq0Empty;         /* 中断上报下行ADQ0空次数 */
    BSP_U32 u32DlAdq1Empty;         /* 中断上报下行ADQ1空次数 */
    BSP_U32 u32UlAd0NotEnough;      /* 上行ADQ0不够次数 */
    BSP_U32 u32UlAd1NotEnough;      /* 上行ADQ0不够次数 */
    BSP_U32 u32DlAd0NotEnough;      /* 下行ADQ0不够次数 */
    BSP_U32 u32DlAd1NotEnough;      /* 下行ADQ0不够次数 */
    BSP_U32 u32DlCdNotEnough;       /* 下行配置CD,CD不够用次数 */
    BSP_U32 u32UlIPFBusyNum;        /* 上行IPF忙次数 */
    BSP_U32 u32DlIPFBusyNum;        /* 下行IPF忙次数 */
    BSP_U32 u32UlResumeTimeoutCnt;  /* 上行过滤规则恢复超时次数 */
    BSP_U32 u32DlResumeTimeoutCnt;  /* 下行过滤规则恢复超时次数 */

    BSP_U32 u32UlBdNum;             /* 上行发送BD计数 */
    BSP_U32 u32UlAdq0Num;           /* 上行配置AD0计数 */
    BSP_U32 u32UlAdq1Num;           /* 上行配置AD1计数 */
    BSP_U32 u32UlRdNum;             /* 上行接收RD计数 */
    BSP_U32 u32DlBdNum;             /* 下行发送BD计数 */
    BSP_U32 u32DlAdq0Num;           /* 下行配置AD1计数 */
    BSP_U32 u32DlAdq1Num;           /* 下行配置AD1计数 */
    BSP_U32 u32DlRdNum;             /* 下行接收RD计数 */
}IPF_DEBUG_INFO_S;

typedef struct tagIPF_ADQ_INFO_S
{
    BSP_U32 u32RptReg;      /* 读指针寄存器 */
    BSP_U32 u32StaReg;      /* 状态寄存器 */
    BSP_U32 u32AqMaxNum;    /* 最大支持的个数 */    
}IPF_ADQ_INFO_S;

/**************************************************************************
  UNION定义
**************************************************************************/

/**************************************************************************
  OTHERS定义
**************************************************************************/



/**************************************************************************
  函数声明
**************************************************************************/
#endif

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif    /* End #define _BSP_DRV_IPF_H_ */


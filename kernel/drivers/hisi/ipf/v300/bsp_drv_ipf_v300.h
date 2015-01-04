/*************************************************************************
*   版权所有(C) 2008-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_DRV_IPF.h
*
*   作    者 :  
*
*   描    述 :  IPF模块用户接口文件
*
*   修改记录 :  2011年01月21日  v1.00  luting  创建
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
#if (FEATURE_IPF_VERSION == IPF_V300)
#ifdef __VXWORKS__
#include <vxWorks.h>
#include <lstLib.h>
#include "product_config.h"
#include "BSP.h"
#else
#include "BSP.h"
#include <mach/hardware.h>
#include "MemoryLayout.h"
#include "soc_irqs.h"
#endif
#include "BSP_IPF.h"
#include "soc_baseaddr_interface.h"
/**************************************************************************
  宏定义 
**************************************************************************/
#ifdef __BSP_DEBUG__
#define __BSP_IPF_DEBUG__
#endif

#ifdef __VXWORKS__
#define IPF_ULBD_MEM_ADDR               MEMORY_AXI_IPF_ADDR
#else
#define IPF_ULBD_MEM_ADDR              (IO_ADDRESS(MEMORY_AXI_IPF_ADDR))
#endif
#define IPF_ULBD_MEM_SIZE               (IPF_ULBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_ULRD_MEM_ADDR              (IPF_ULBD_MEM_ADDR + IPF_ULBD_MEM_SIZE)
#define IPF_ULRD_MEM_SIZE               (IPF_ULRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_DLBD_MEM_ADDR              (IPF_ULRD_MEM_ADDR + IPF_ULRD_MEM_SIZE)
#define IPF_DLBD_MEM_SIZE               (IPF_DLBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_DLRD_MEM_ADDR              (IPF_DLBD_MEM_ADDR + IPF_DLBD_MEM_SIZE)
#define IPF_DLRD_MEM_SIZE               (IPF_DLRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_DLCD_MEM_ADDR              (IPF_DLRD_MEM_ADDR + IPF_DLRD_MEM_SIZE)
#define IPF_DLCD_MEM_SIZE               (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

#define IPF_INIT_ADDR                        (IPF_DLCD_MEM_ADDR + IPF_DLCD_MEM_SIZE)
#define IPF_INIT_SIZE                          16

#define IPF_ULBD_IDLENUM_ADDR       (IPF_INIT_ADDR + IPF_INIT_SIZE)
#define IPF_ULBD_IDLENUM_SIZE          16

#define IPF_DEBUG_INFO_ADDR           (IPF_ULBD_IDLENUM_ADDR + IPF_ULBD_IDLENUM_SIZE)
#define IPF_DEBUG_INFO_SIZE            sizeof(IPF_DEBUG_INFO_S)

#define IPF_DEBUG_DLCD_ADDR           (IPF_DEBUG_INFO_ADDR + IPF_DEBUG_INFO_SIZE)
#define IPF_DEBUG_DLCD_SIZE            (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

/* 保存下行CD读写指针 */
#define IPF_DLCD_PTR_ADDR               (IPF_DEBUG_DLCD_ADDR + IPF_DEBUG_DLCD_SIZE)
#define IPF_DLCD_PTR_SIZE                  8

#define IPF_BF_NUM                          FEATURE_IPF_BF_NUM          /* 基本过滤器数目 */
#define IPF_TOTAL_FILTER_NUM             256  /* 过滤器总数目 */
#define EXFLITER_NUM                            (IPF_TOTAL_FILTER_NUM-IPF_BF_NUM) /* 扩展过滤器数目 */
#define IPF_TAIL_INDEX                          511  /* filter标识最后一个filter */

#define TIME_OUT_CFG                       500           /* RD超时时间 */

#define IPF_CH_EN                         0x0008
#define IPF_EN_STATE                   0x000C
#define IPF_CTRL                            0x0014
#define IPF_INT0                            0x0030
#define IPF_INT1                            0x0034
#define IPF_INT_MASK0                 0x0038
#define IPF_INT_MASK1                 0x003C
#define IPF_INT_STATE                 0x0040
#define IPF_TIME_OUT                   0x0044
#define IPF_PKT_LEN                     0x0048
#define IPF_FLT_ZERO_INDEX        0x0070
#define IPF_EF_BADDR                   0x0074
#define BFLT_INDEX                       0x0078
#define FLT_LOCAL_ADDR0             0x0080
#define FTL_CHAIN                         0x00DC
#define IPF_CH_CTRL(i)                 (0x0100 + i * 0x50)
#define IPF_CH_STATE(i)               (IPF_CH_CTRL(i) + 0x04)
#define IPF_CH_BDQ_BADDR(i)      (IPF_CH_CTRL(i) + 0x08)
#define IPF_CH_BDQ_SIZE(i)         (IPF_CH_CTRL(i) + 0x0C)
#define IPF_CH_BDQ_WPTR(i)        (IPF_CH_CTRL(i) + 0x10)
#define IPF_CH_BDQ_RPTR(i)         (IPF_CH_CTRL(i) + 0x14)
#define IPF_CH_BDQ_WADDR(i)      (IPF_CH_CTRL(i) + 0x18)
#define IPF_CH_BDQ_RADDR(i)       (IPF_CH_CTRL(i) + 0x1C)
#define IPF_CH_RDQ_BADDR(i)      (IPF_CH_CTRL(i) + 0x20)
#define IPF_CH_RDQ_SIZE(i)         (IPF_CH_CTRL(i) + 0x24)
#define IPF_CH_RDQ_WPTR(i)         (IPF_CH_CTRL(i) + 0x28)
#define IPF_CH_RDQ_RPTR(i)         (IPF_CH_CTRL(i) + 0x2C)
#define IPF_CH_RDQ_WADDR(i)      (IPF_CH_CTRL(i) + 0x30)
#define IPF_CH_RDQ_RADDR(i)       (IPF_CH_CTRL(i) + 0x34)
#define IPF_CH_DQ_DEPTH(i)         (IPF_CH_CTRL(i) + 0x38)
#define IPF_UL_CNT0                     0x0200
#define IPF_UL_CNT1                     0x0204
#define IPF_UL_CNT2                     0x0208
#define IPF_DL_CNT0                     0x0210
#define IPF_DL_CNT1                     0x0214
#define IPF_DL_CNT2                     0x0218

/* IPF中断上报、屏蔽、状态寄存器位定义,上报、屏蔽、状态三者一一对应 */
#define IPF_UL_RPT_INT                     (1 << 0)    /* 上行结果上报 */
#define IPF_UL_TIMEOUT_INT                 (1 << 1)    /* 上行结果上报超时 */
#define IPF_UL_RDQ_DOWN_OVERFLOW_INT       (1 << 6)    /* 上行RDQ下溢 */
#define IPF_UL_BDQ_UP_OVERFLOW_INT         (1 << 7)    /* 上行BDQ上溢 */
#define IPF_UL_RDQ_FULL_INT                (1 << 8)    /* 上行RDQ满 */

#define IPF_DL_RPT_INT                     (1 << 16)   /* 下行结果上报 */
#define IPF_DL_TIMEOUT_INT                 (1 << 17)   /* 下行结果上报超时 */
#define IPF_DL_RDQ_DOWN_OVERFLOW_INT       (1 << 22)   /* 下行RDQ下溢 */
#define IPF_DL_BDQ_UP_OVERFLOW_INT         (1 << 23)   /* 下行BDQ上溢 */
#define IPF_DL_RDQ_FULL_INT                (1 << 24)   /* 下行RDQ满 */
/* INTO中断上报情况: */
#define IPF_INT_OPEN0                       ( IPF_UL_RPT_INT \
                                            | IPF_UL_TIMEOUT_INT \
                                            | IPF_UL_BDQ_UP_OVERFLOW_INT)   
/* INT1中断上报情况: */                                            
#define IPF_INT_OPEN1                       ( IPF_DL_RPT_INT \
                                            | IPF_DL_TIMEOUT_INT \
                                            | IPF_DL_BDQ_UP_OVERFLOW_INT)  
#ifdef __VXWORKS__
#define IPF_PRINT                         printf
#define IPF_REGBASE_ADR            SOC_IPF_BASE_ADDR
#define INT_LVL_IPF                     INT_LVL_IPF_0
#define INT_VEC_IPF                     INT_VEC_IPF_C
#elif defined(__KERNEL__)
#define IPF_PRINT                         printk
#define IPF_REGBASE_ADR            IO_ADDRESS(SOC_IPF_BASE_ADDR)
#define INT_LVL_IPF                     IRQ_IPF1
#define INT_VEC_IPF                     IVEC_TO_INUM(INT_LVL_IPF)
#endif

#ifdef _DRV_LLT_
extern BSP_VOID BSP_IPF_RegRead(BSP_U32 base, BSP_U32 reg,BSP_U32* result);
#define IPF_REG_WRITE(x,y,z)      
#define IPF_REG_READ(x,y,z)         BSP_IPF_RegRead(x,y,&z)
#else
#define IPF_REG_WRITE(x,y,z)       BSP_REG_WRITE(x,y,z)
#define IPF_REG_READ(x,y,z)         BSP_REG_READ(x,y,z)
#endif
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
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM      
    BSP_IPF_WakeupUlCb pFnUlIntCb; /* 中断中唤醒的PS任务 */
#endif   
    BSP_U32* pu32IdleBd; /* 记录上一次获取的空闲BD 数 */
}IPF_UL_S;

typedef struct tagIPF_DL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;    
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_CD_DESC_S* pstIpfCDQ;
    IPF_CD_DESC_S* pstIpfDebugCDQ;
#ifndef PRODUCT_CFG_CORE_TYPE_MODEM 
    BSP_IPF_WakeupDlCb pFnDlIntCb; /* 中断中唤醒的PS任务 */
#endif
    BSP_U32* u32IpfCdRptr; /* 当前可以读出的位置 */
    BSP_U32* u32IpfCdWptr;
    BSP_U32 u32IdleBd; /* 记录上一次获取的空闲BD 数 */
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
#ifdef __BSP_IPF_DEBUG__
    BSP_U32 u32IpfDebug;
#endif
    BSP_U32 u32UlBdqOverflow; /* 中断上报上行BD队列溢出次数 */
    BSP_U32 u32DlBdqOverflow; /* 中断上报下行BD队列溢出次数 */
    BSP_U32 u32UlBdNotEnough;       /* 上行配置BD,BD不够用次数 */
    BSP_U32 u32DlBdNotEnough;       /* 下行配置BD,BD不够用次数 */
    BSP_U32 u32DlCdNotEnough;       /* 下行配置CD,CD不够用次数 */
    BSP_U32 u32UlIPFBusyNum;       /* 上行IPF忙次数 */
    BSP_U32 u32DlIPFBusyNum;       /* 下行IPF忙次数 */
}IPF_DEBUG_INFO_S;

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

#endif    /* End #define _BSP_DMAC_H_ */


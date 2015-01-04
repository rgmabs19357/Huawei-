
#ifndef __DRV_MODEM_BSP_H__
#define __DRV_MODEM_BSP_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))
/*
    开机模式定义
*/
typedef enum DRV_START_MODE_tag
{
    DRV_START_MODE_EXCEPTION,  /* 异常开机模式，此时大部分业务都不启动, 仅提示信息 */
    DRV_START_MODE_CHARGING,   /* 充电开机模式, ps 等业务不启动  */
    DRV_START_MODE_NORMAL,     /* 正常开机模式，所有业务启动     */
    DRV_START_MODE_BUTT
}DRV_START_MODE_ENUM;

/************************************************************************************
 *Function Name :  drv_start_mode_get
 *Description   :  获取本次开机的模式，参见 DRV_START_MODE_ENUM 定义
 *Others        :  No
************************************************************************************/
DRV_START_MODE_ENUM drvStartModeGet( void );

/*************************************************
  Function:      drv_sleep
  Description:   使用always on 定时器实现sleep功能
  Calls:
  Called By:
  Data Accessed: NONE
  Data Updated:  NONE
  Input:    ulLength ：sleep 单位，目前为10ms
            ulFileID:  File name, for debug;
            usLineNo:  Line number, for debug;
  Output:
  Return:
  Others:

************************************************/
void drv_sleep( UINT32 ulLength, UINT32 ulFileID, UINT32 usLineNo);

#endif

/*****************************************************************************
* 函 数 名  : BSP_INT_Enable
*
* 功能描述  : 使能某个中断
*
* 输入参数  : INT32 ulLvl 要使能的中断号，取值范围0～40
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_INT_Enable ( BSP_S32 s32Lvl);
#define DRV_VICINT_ENABLE(ulLvl)    BSP_INT_Enable(ulLvl)

/*****************************************************************************
 * 函 数 名  : BSP_INT_Disable
 *
 * 功能描述  : 去使能某个中断
 *
 * 输入参数  : INT32 ulLvl 要使能的中断号，取值范围0～40
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 *****************************************************************************/
BSP_S32 BSP_INT_Disable ( BSP_S32 s32Lvl);
#define  DRV_VICINT_DISABLE(ulLvl)    BSP_INT_Disable(ulLvl)

/*****************************************************************************
 * 函 数 名  : BSP_INT_Connect
 *
 * 功能描述  : 注册某个中断
 *
 * 输入参数  : VOIDFUNCPTR * vector 中断向量号，取值范围0～40
 *           VOIDFUNCPTR routine  中断服务程序
 *           INT32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 *****************************************************************************/
BSP_S32 BSP_INT_Connect  (VOIDFUNCPTR * vector,VOIDFUNCPTR routine, BSP_S32 parameter);
#define DRV_VICINT_CONNECT(vector,routine,parameter)    BSP_INT_Connect(vector,routine,parameter)


/**************************************************************************
  宏定义
**************************************************************************/
/* 内存池类型, Flags标记用 */
typedef enum tagMEM_POOL_TYPE
{
    MEM_NORM_DDR_POOL = 0,
    MEM_ICC_DDR_POOL,
    MEM_ICC_AXI_POOL,
    MEM_POOL_MAX
}MEM_POOL_TYPE;

/**************************************************************************
  接口声明
**************************************************************************/
BSP_VOID* BSP_Malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
BSP_VOID* BSP_MallocDbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line);
BSP_VOID  BSP_Free(BSP_VOID* pMem);
BSP_VOID  BSP_FreeDbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line);

/*****************************************************************************
* 函 数 名  : BSP_MALLOC
*
* 功能描述  : BSP 动态内存分配
*
* 输入参数  : sz: 分配的大小(byte)
*             flags: 内存属性(暂不使用,预留)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_MALLOC(sz, flags) BSP_MallocDbg(sz, flags, __FILE__, __LINE__)
#else
#define BSP_MALLOC(sz, flags) BSP_Malloc(sz, flags)
#endif

/*****************************************************************************
* 函 数 名  : BSP_FREE
*
* 功能描述  : BSP 动态内存释放
*
* 输入参数  : ptr: 动态内存指针
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_FREE(ptr) BSP_FreeDbg(ptr, __FILE__, __LINE__)
#else
#define BSP_FREE(ptr) BSP_Free(ptr)
#endif



/*****************************************************************************
* 函 数 名  : BSP_SFree
*
* 功能描述  : BSP 动态内存释放(加spin lock保护,多核场景使用)
*
* 输入参数  : pMem: 动态内存指针
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
BSP_VOID  BSP_SFree(BSP_VOID* pMem);
/*****************************************************************************
* 函 数 名  : BSP_SMalloc
*
* 功能描述  : BSP 动态内存分配(加spin lock保护,多核场景使用)
*
* 输入参数  : u32Size: 分配的大小(byte)
*             enFlags: 内存属性(暂不使用,预留)
* 输出参数  : 无
* 返 回 值  : 分配出来的内存指针
*****************************************************************************/
BSP_VOID* BSP_SMalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);


#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_VOID* OSAL_CacheDmaMalloc(BSP_U32  bytes);
#define DRV_CACHEDMAM_ALLOC(bytes) OSAL_CacheDmaMalloc(bytes)
#else
#define DRV_CACHEDMAM_ALLOC(bytes) kmalloc(bytes, GFP_KERNEL)
#endif

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_S32 OSAL_CacheDmaFree(BSP_VOID*  pBuf);
#define DRV_CACHEDMAM_FREE(pBuf) OSAL_CacheDmaFree(pBuf)
#else
#define DRV_CACHEDMAM_FREE(pBuf) kfree(pBuf)
#endif

/************************************************************************
 * FUNCTION
 *       vmEnable
 * DESCRIPTION
 *       内存读写保护功能使能函数
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int vmEnable(int enable);
#define DRV_VM_ENABLE(flag)   vmEnable(flag)

/*****************************************************************************
 函 数 名  : vmStateSet
 功能描述  : 设置地址空间状态
 输入参数  : 无

 输出参数  : 无。
 返 回 值  : 无
 注意事项  ：
*****************************************************************************/
#define DRV_VM_STATESET(context, virtAdrs, len, stateMask, state) vmStateSet(context, virtAdrs, len, stateMask, state)

/*****************************************************************************
 函 数 名  : BSP_CACHE_DATA_FLUSH
 功能描述  :
 输入参数  :
 输出参数  : None
 返 回 值  : void
*****************************************************************************/
extern void BSP_CACHE_DATA_FLUSH(void * addr, int size);

/************************************************************************
 * FUNCTION
 *       max_freeblock_size_get
 * DESCRIPTION
 *       get memory max free block size
 * INPUTS
 *       无
 * OUTPUTS
 *       max free block size
 *************************************************************************/
extern int DRV_GET_FREE_BLOCK_SIZE(void);

/*****************************************************************************
 函 数 名  : BSP_DFS_GetCurCpuLoad
 功能描述  : 查询当前CPU
 输入参数  : pu32AcpuLoad ACPUload指针
             pu32CcpuLoad CCPUload指针
 输出参数  : pu32AcpuLoad ACPUload指针
             pu32CcpuLoad CCPUload指针
 返 回 值  : 0:  操作成功；
            -1：操作失败。
*****************************************************************************/
extern BSP_U32 BSP_DFS_GetCurCpuLoad(BSP_U32 *pu32AcpuLoad,BSP_U32 *pu32CcpuLoad);
#define DRV_GET_CUR_CPU_LOAD(pu32AcpuLoad,pu32CcpuLoad) BSP_DFS_GetCurCpuLoad(pu32AcpuLoad,pu32CcpuLoad)


/*****************************************************************************
 函 数 名  : BSP_GU_GetVerTime
 功能描述  : 获取版本编译时间
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
extern char *BSP_GU_GetVerTime(void);
#define DRV_GET_VERSION_TIME()    BSP_GU_GetVerTime()

/***********************************内存拷贝优化*****************************************/
/*****************************************************************************
 函 数 名  : __rt_memcpy
 功能描述  : 汇编版本的memcpy函数
 输入参数  : Dest :目的地址
             Src :源地址
             Count:拷贝数据的大小
 输出参数  : 无。
 返 回 值  : 目的地址。
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern void * __rt_memcpy(void * Dest, const void * Src, unsigned long Count);
#define DRV_RT_MEMCPY(Dest,Src,Count)       __rt_memcpy(Dest,Src,Count)
#else
#define DRV_RT_MEMCPY(Dest,Src,Count)       memcpy(Dest,Src,Count)
#endif

/*****************************************************************************
 函 数 名  : bsp_memcpy_align32
 功能描述  : 汇编版本的32位数据对齐memcpy函数
 输入参数  : Dest :目的地址
             Src :源地址
             Count:拷贝数据的大小
 输出参数  : 无。
 返 回 值  : 目的地址。
*****************************************************************************/
extern void bsp_memcpy_align32(UINT32 *pDstBuf,  UINT32 *pSrcBuf, UINT32 ulSize);
#define DRV_MEMCPY_ALIGN32(Dest,Src,Count)       bsp_memcpy_align32(Dest,Src,Count)

/*****************************************************************************
 函 数 名  : bsp_memcpy_auto_align64
 功能描述  : 自动按64位对齐版本的memcpy函数
 输入参数  : Dest :目的地址
             Src :源地址
             Count:拷贝数据的大小
 输出参数  : 无。
 返 回 值  : 目的地址。
*****************************************************************************/
extern void bsp_memcpy_auto_align(void *pDstBuf,  void *pSrcBuf, UINT32 ulLen, UINT32 ulAlignSize);
#define DRV_MEMCPY_AUTO_ALIGN64(Dest,Src,Count) bsp_memcpy_auto_align(Dest,Src,Count,8);

/*****************************************************************
Function: free_mem_size_get
Description:
    get mem size
Input:
    N/A
Output:
    N/A
Return:
    free mem size
*******************************************************************/
extern unsigned long free_mem_size_get(void);
#define FREE_MEM_SIZE_GET() free_mem_size_get()

/*****************************************************************************
 函 数 名  : BSP_DMR_ATAnalyze
 功能描述  : 供NAS查询动态内存占用信息，通过AT命令查询
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 成功0，失败-1
*****************************************************************************/
extern int BSP_DMR_ATANALYZE(void * pstMem,unsigned int uiSize, unsigned int * puiModIdSum);


/* 定义所有需要查询的IP类型 */
typedef enum tagBSP_IP_TYPE_E
{
    BSP_IP_TYPE_SOCP = 0x0,
    BSP_IP_TYPE_CICOM0,
    BSP_IP_TYPE_CICOM1,
    BSP_IP_TYPE_HDLC,
    BSP_IP_TYPE_BBPMASTER,
    BSP_IP_TYPE_ZSP_ITCM,
    BSP_IP_TYPE_ZSP_DTCM,
    BSP_IP_TYPE_AHB,
    BSP_IP_TYPE_WBBP,
    BSP_IP_TYPE_WBBP_DRX,
    BSP_IP_TYPE_GBBP,
    BSP_IP_TYPE_GBBP_DRX,
    BSP_IP_TYPE_GBBP1,
    BSP_IP_TYPE_GBBP1_DRX,
    BSP_IP_TYPE_ZSPDMA,
    BSP_IP_TYPE_SYSCTRL,
    BSP_IP_TYPE_CTU,
    BSP_IP_TYPE_TDSSYS,
    BSP_IP_TYPE_ZSPDHI,

    BSP_IP_TYPE_BUTTOM
}BSP_IP_TYPE_E;

/*****************************************************************************
 函 数 名  : BSP_GetIPBaseAddr
 功能描述  : IP基地址查询
 输入参数  : enIPType: 需要查询的IP类型
 输出参数  : 无
 返回值    ：查询到的IP基地址
*****************************************************************************/
BSP_U32 BSP_GetIPBaseAddr(BSP_IP_TYPE_E enIPType);
#define DRV_GET_IP_BASE_ADDR(enIPType)  BSP_GetIPBaseAddr(enIPType)

/* 定义所有需要查询的MEM类型 */
typedef enum tagBSP_DDR_TYPE_E
{
    BSP_DDR_TYPE_DDR_GU = 0x0,          /*DDR:GU预留*/
    BSP_DDR_TYPE_DDR_TLPHY_IMAGE,       /*DDR:TL DSP 镜像*/
    /*BSP_DDR_TYPE_DDR_LPHY_SDR,*/      /*NO USED*/
    BSP_DDR_TYPE_DDR_TLPHY_LCS,         /*DDR:TL DSP LCS*/
    BSP_DDR_TYPE_DDR_TLPHY_BANDNV,      /*DDR:TL DSP BAND*/
    BSP_DDR_TYPE_DDR_TPHY_TABLE,        /*DDR:TL TDS TABLE*/
    BSP_DDR_TYPE_DDR_HIFI,              /*DDR:HIFI*/
    BSP_DDR_TYPE_SRAM_TLPHY,            /*SRAM:TL DSP*/
    BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG,   /*SRAM:TL DSP睡眠唤醒标记*/
    BSP_DDR_TYPE_SHM_TEMPERATURE,       /*共享内存:温饱*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_HEAD,   /*共享内存:BBE16->HIFI邮箱头*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_HEAD,   /*共享内存:HIFI->BBE16邮箱头*/
    BSP_DDR_TYPE_SHM_BBE16_HIFI_QUEUE,  /*共享内存:BBE16->HIFI邮箱队列*/
    BSP_DDR_TYPE_SHM_HIFI_BBE16_QUEUE,  /*共享内存:HIFI->BBE16邮箱队列*/
    /*BSP_DDR_TYPE_SHM_TIMESTAMP,*/     /*NO USED*/

    BSP_DDR_TYPE_BUTTOM
}BSP_DDR_TYPE_E;
/*****************************************************************************
 函 数 名  : BSP_GetMemAddrSize
 功能描述  : 获取mem地址和大小信息
 输入参数  : enMemType: 需要查询的mem类型
 输出参数  : addr 地址
             size 大小
 返回值    ：BSP_OK    查询成功
             BSP_ERROR 查询失败
*****************************************************************************/
BSP_U32 BSP_GetMemAddrSize(BSP_DDR_TYPE_E enDdrType, BSP_U32 *addr, BSP_U32 *size);
#define DRV_GET_MEM_ADDR_SIZE(enDdrType, pAddr, pSize)  BSP_GetMemAddrSize(enDdrType, pAddr, pSize)


/* 需要查询的中断类型 */
typedef enum tagBSP_INT_TYPE_E
{
    BSP_INT_TYPE_RTC = 0,
    BSP_INT_TYPE_WDT,
    BSP_INT_TYPE_USBOTG,
    BSP_INT_TYPE_UICC,
    BSP_INT_TYPE_IPF_C,
    BSP_INT_TYPE_IPF_A,
    BSP_INT_TYPE_SOCP_A,
    BSP_INT_TYPE_SOCP_C,
    BSP_INT_TYPE_CICOM_UL,
    BSP_INT_TYPE_CICOM_DL,
    BSP_INT_TYPE_CICOM1_UL,
    BSP_INT_TYPE_CICOM1_DL,
    BSP_INT_TYPE_HDLC_DEF,
    BSP_INT_TYPE_HDLC_FRM,

    BSP_INT_TYPE_GBBP,          /*G_BBP_INT_LEVEL*/
    BSP_INT_TYPE_GBBP_AWAKE,    /*G_BBP_AWAKE_INT_LEVEL*/
    BSP_INT_TYPE_GBBP_DSP,
    BSP_INT_TYPE_GBBP_AWAKE_DSP,
    BSP_INT_TYPE_GBBP1,
    BSP_INT_TYPE_GBBP1_AWAKE,
    BSP_INT_TYPE_GBBP1_DSP,
    BSP_INT_TYPE_GBBP1_AWAKE_DSP,
    BSP_INT_TYPE_WBBP_0MS,      /*card1 0ms中断*/
    BSP_INT_TYPE_WBBP_AWAKE,    /*睡眠、唤醒中断*/
    BSP_INT_TYPE_WBBP_SWITCH,   /*时钟切换中断*/
    BSP_INT_TYPE_WBBP1_0MS,     /*Card2 0ms 中断*/
    BSP_INT_TYPE_WBBP_SEARCH,   /*小区搜索中断*/
    BSP_INT_TYPE_WBBP_RAKE,     /*Rake解调上报中断*/
    BSP_INT_TYPE_WBBP_DECODE,   /*译码数据上报中断*/
    BSP_INT_TYPE_WBBP_TIME,     /*card1定时中断*/
    BSP_INT_TYPE_WBBP1_TIME,    /*card2定时中断*/
    BSP_INT_TYPE_WBBP_MULTI_SEARCH, /*多径搜索测量中断*/
    BSP_INT_TYPE_WBBP_BBPMST,       /*译码BBP Master上报中断*/
    BSP_INT_TYPE_UPACC_DSP,
    BSP_INT_TYPE_INT_OSRTC,     /*RTC_DUAL_TIMER_INT_LEVEL*/
    BSP_INT_TYPE_INT_SMIM,      /*SOC_SMIM_INT_LEVEL*/
    BSP_INT_TYPE_INT_ZSP_DOG,   /*ZSP_WDG_INT_LEVEL*/
    BSP_INT_TYPE_INT_HIFI_DOG,  /*HIFI_WDG_INT_LEVEL*/

    BSP_INT_TYPE_INT12_G2,        /*CTU产生与G2相关的中断*/
    BSP_INT_TYPE_ODTOA_INT12,     /*目标定位中断*/
    BSP_INT_TYPE_CTU_INT_W,       /*CTU产生与W模相关的中断(W可以为主模，也可以为从模)*/
    BSP_INT_TYPE_CTU_INT_G,       /*CTU产生与G模相关的中断(G可以为主模，也可以为从模)*/
    BSP_INT_TYPE_CTU_INT_LTE,     /*CTU产生与LTE模相关的中断(LTE可以为主模，也可以为从模)*/
    BSP_INT_TYPE_CTU_INT_TDS,     /*CTU产生与TDS模相关的中断(TDS可以为主模，也可以为从模)*/
    BSP_INT_TYPE_UPACC_INTR,              /*UPACC中断*/
    BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR, /*PHY_32K时钟域中断(仅含非掉电区)*/

    BSP_INT_TYPE_LTE_CIPHER,          /*L Cipher中断*/
    BSP_INT_TYPE_LTE_APP_ARM_PUB,     /*电平中断，dbg业务相关，给ARM A核*/
    BSP_INT_TYPE_LTE_ARM_POSITIONS,   /*脉冲中断，给ARM M核，122.8MHz，8cycle*/
    BSP_INT_TYPE_LTE_DL_DMA,          /*脉冲中断，给ARM M核，122.8MHz，8cycle*/
    BSP_INT_TYPE_LTE_ARM_POSITION,    /*电平中断，stu相关，给ARM M核*/
    BSP_INT_TYPE_LTE_ARM_DL_DMA,      /*电平中断，tdl业务相关，给ARM M核*/
    BSP_INT_TYPE_LTE_ARM_CLK_SWITCH,  /*drx模块中断，给ARM M核*/
    BSP_INT_TYPE_LBBP_AWAKE,          /*drx模块中断，给ARM M核*/
    BSP_INT_TYPE_LTE_PUB,             /*drx模块中断，给ARM M核*/
    BSP_INT_TYPE_TDS_STU_ARM1,        /*tds定时模块子帧中断，给ARM，81.92M时钟域//电平中断*/
    BSP_INT_TYPE_TBBP_AWAKE,          /*tds drx给ARM的唤醒中断*/
    BSP_INT_TYPE_TDS_DRX_ARM2,        /*tds drx给ARM的clk_switch中断*/
    BSP_INT_TYPE_BBE16_GPIO1,         /*BBE16内部的GPIO1输出，用于核间通信(ltedsp_tie_expstate[1])*/

    BSP_INT_TYPE_BUTTOM
}BSP_INT_TYPE_E;


/*****************************************************************************
 函 数 名  : BSP_GetIntNO
 功能描述  : 中断号查询
 输入参数  : enIntType: 需要查询的中断类型
 输出参数  : 无
 返回值    ：查询到的中断号
*****************************************************************************/
BSP_S32 BSP_GetIntNO(BSP_INT_TYPE_E enIntType);
#define DRV_GET_INT_NO(enIntType)    BSP_GetIntNO(enIntType)


/*****************************************************************************
 函 数 名  : BSP_GUDSP_ShareAddrGet
 功能描述  : 获取物理层共享地址段的信息。
 输入参数  : 无。
 输出参数  : pulAddr：存放物理层共享地址段信息的缓存。
 返 回 值  : 无。
*****************************************************************************/
extern int BSP_GUDSP_ShareAddrGet(unsigned int * pulAddrInTcm, unsigned int * pulAddrInDdr, unsigned int * pulLength);
#define DRV_DSP_SHARE_ADDR_GET(pulAddrInTcm,pulAddrInDdr,pulLength)    BSP_GUDSP_ShareAddrGet(pulAddrInTcm,pulAddrInDdr,pulLength)

/*****************************************************************************
 函 数 名  : BSP_UpateDSPShareInfo
 功能描述  : 更新物理层BSS COMMON段信息。
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 0:成功，-1:失败。
*****************************************************************************/
extern int BSP_GUDSP_UpateShareInfo(unsigned long shareAddr);
#define DRV_BSP_UPDATE_DSP_SHAREINFO(shareAddr)  BSP_GUDSP_UpateShareInfo(shareAddr)
/*****************************************************************************
 函 数 名  : BSP_GUDSP_DrxGpioValSet
 功能描述  : 提供GPIO设置接口为DSP的DRX使用
 输入参数  : u32Data:1 GPIO输出高，0 GPIO输出低。
 输出参数  : 无
 返 回 值  : 0:成功，-1:失败。
*****************************************************************************/
extern int BSP_GUDSP_DrxGpioValSet(BSP_U32 u32Data);
#define DRV_DSP_DRX_GPIO_VAL_SET(u32Data) BSP_GUDSP_DrxGpioValSet(u32Data)


/*****************************************************************************
 函 数 名  : BSP_SendNMIInterrupt
 功能描述  : 发送 NMI 的中断
 输入参数  : NMI中断的bit位
 输出参数  : 无
 返 回 值  : 中断是否需要处理
*****************************************************************************/
extern BSP_VOID BSP_SendNMIInterrupt(unsigned int SocBitNO, unsigned int ZspBitNO);
#define DRV_SEND_NMI_INT(SocBitNO,ZspBitNO) BSP_SendNMIInterrupt(SocBitNO,ZspBitNO)


/*产线版本写SDT信息的文件系统的分区名*/
#define MANUFACTURE_ROOT_PATH "/manufacture"

/*****************************************************************************
 函 数 名  : drvOnLineUpdateResult
 功能描述  : WebUI模块函数注册。
 输入参数  : 无
 输出参数  : 无。
 返 回 值  : 无
 注意事项  ：
*****************************************************************************/
extern void drvOnLineUpdateResult(void);
#define DRV_ONLINE_UPDATE_RESULT()    drvOnLineUpdateResult()

/******************************************************************************
*
  函数名:       BSP_S32 nand_get_bad_block (BSP_U32 *len, BSP_U32 **ppBadBlock)
  函数描述:     查询整个NAND的所有FLASH 坏块
  输入参数:     无
  输出参数:     pNum       : 返回坏块个数
                ppBadBlock ：数组指针，返回所有坏块的index索引
  返回值:       0    : 查询成功
                负数 : 查询失败
*******************************************************************************/
extern BSP_S32 nand_get_bad_block(BSP_U32 *pNum, BSP_U32 **ppBadBlock);
#define NAND_GET_BAD_BLOCK(pNum, ppBadBlock) nand_get_bad_block(pNum, ppBadBlock)

/******************************************************************************
*
  函数名:       BSP_VOID  nand_free_bad_block_mem(BSP_U32* pBadBlock)
  函数描述:     通过nand_get_bad_block接口申请的坏块内存由底软申请，由协议栈调用
                该接口释放。
  输入参数:     pBadBlock
  输出参数:     无
  返回值:       BSP_VOID
*******************************************************************************/
extern BSP_VOID  nand_free_bad_block_mem(BSP_U32* pBadBlock);
#define NAND_FREE_BAD_BLOCK_MEM(pBadBlock)  nand_free_bad_block_mem(pBadBlock)

/******************************************************************************
*
  函数名:   BSP_Sram_BackupInfoReg
  函数描述: 注册SRAM段备份恢复信息
  输入参数: pucSramAddr 注册的段在SRAM的加载地址
            ulSectLen   注册的段的字节大小，函数内部默认不做任何字节对齐处理
            ulNeedMulBck该段是否需要每次下电都做备份处理，一般启动之后可能数据
                        会变的段，例如:data段需要每次都备份最新内容，那么该参数
                        填写为1；而text段启动之后一直不变，故备份一次即可，减少
                        总线访问次数，该参数填写为0
            ulNeedCheck 恢复的数据是否需要校验，由于校验对性能影响较大，故该功能
                        参数目前留作后续扩展，暂不实现，传入值无效
  输出参数: None
  返回值:   BSP_OK      处理成功
            BSP_ERROR   处理失败
*******************************************************************************/
extern int BSP_SRAM_BackupInfoReg(unsigned char *pucSramAddr, unsigned long ulSectLen, unsigned long ulNeedMulBak, unsigned long ulNeedCheck);
#define DRV_SRAM_BACKUP_INFO_REG(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)  BSP_SRAM_BackupInfoReg(pucSramAddr, ulSectLen, ulNeedMulBak, ulNeedCheck)


#define NAND_MFU_NAME_MAX_LEN    16
#define NAND_DEV_SPEC_MAX_LEN    32

typedef struct
{
    BSP_U32           MufId;                                         /* 厂商ID */
    BSP_U8      aucMufName[NAND_MFU_NAME_MAX_LEN];             /* 厂商名称字符串 */
    BSP_U32           DevId;                                         /* 设备ID */
    BSP_U8      aucDevSpec[NAND_DEV_SPEC_MAX_LEN];             /* 设备规格字符串 */
}NAND_DEV_INFO_S;

/******************************************************************************
*
  函数名:       BSP_S32 nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo)
  函数描述:     查询NAND设备相关信息：包括厂商ID、厂商名称、设备ID、设备规格
  输入参数:     无
  输出参数:     pNandDevInfo    存储NAND设备相关信息的结构体
  返回值:       0    : 查询成功
                负数 : 查询失败
*******************************************************************************/
extern BSP_S32 nand_get_dev_info(NAND_DEV_INFO_S *pNandDevInfo);
#define NAND_GET_DEV_INFO(pNandDevInfo) nand_get_dev_info(pNandDevInfo)


/******************************************************************************
* Function     :   BSP_NANDF_Read
*
* Description  :   读取Nand Flash中指定地址和长度内容到指定空间中
*
* Input        :   u32FlashAddr  读取数据的源地址
*              :   u32NumByte    读取数据长度，单位为字节
*
* Output       :   pRamAddr      读取的数据存放的地址
*
* return       :   读操作成功与否
******************************************************************************/
BSP_S32 BSP_NANDF_Read(BSP_VOID* pRamAddr, BSP_U32 u32FlashAddr, BSP_U32 u32NumByte);

/******************************************************************************
* Function     :   BSP_NANDF_Write
*
* Description  :   将指定地址和长度内容到写到指定FLASH地址中
*
* Input        :   pRamAddr     写操作源地址
*              :   u32NumByte   数据长度，单位为字节
*
* Output       :   u32FlashAddr 写操作目的地址
*
* return       :   写操作成功与否
******************************************************************************/
BSP_S32 BSP_NANDF_Write(BSP_U32 u32FlashAddr, BSP_VOID *pRamAddr,  BSP_U32 u32NumByte);

/******************************************************************************
* Function     :   BSP_NANDF_Erase
*
* Description  :   擦除指定Flash地址所在块
*
* Input        :   u32address   要擦除块的ID
*
* Output       :   无
*
* return       :   擦除操作成功与否
******************************************************************************/
BSP_S32 BSP_NANDF_Erase(BSP_U32 u32BlockID);

BSP_U32 nand_isbad(BSP_U32 blockID, BSP_U32 *flag);

/*****************************************************************************
* 函 数 名  : BSP_IPM_FreeBspBuf
*
* 功能描述  : 释放内存接口
*
* 输入参数  : BSP_U8 *pBuf 需要释放的指针
*
* 输出参数  : 无
* 返 回 值  : 无
*
*****************************************************************************/
BSP_VOID BSP_IPM_FreeBspBuf(BSP_U8 *pBuf);



/*****************************************************************************
 函 数 名  : DRV_INT_GET_CONTEXT
 功能描述  : 判断当前任务是否在中断中执行
 输入参数  : 无
 输出参数  : 无
 返回值    ：0  代表非中断
             1  代表中断
*****************************************************************************/
unsigned int DRV_INT_GET_CONTEXT(void);

/*****************************************************************************
 函 数 名  : DRV_INT_GET_NUM
 功能描述  : 获取当前中断号
 输入参数  : 无
 输出参数  : 无
 返回值    ：中断号
*****************************************************************************/
signed int DRV_INT_GET_NUM(void);
#if defined(BSP_CORE_MODEM)
/*****************************************************************************
 函 数 名  : BSP_DMB_INSTRUCTION
 功能描述  : DMB接口，DSP调用
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
#define BSP_DMB_INSTRUCTION \
{\
    __asm("STMFD r13!, {r0}");\
    __asm("MOV r0, #0");\
    __asm("MCR p15, 0, r0, c7, c10, 5");\
    __asm("LDMIA r13!, {r0}");\
}
#define DRV_DMB_INSTRUCTION() BSP_DMB_INSTRUCTION
#endif

#endif


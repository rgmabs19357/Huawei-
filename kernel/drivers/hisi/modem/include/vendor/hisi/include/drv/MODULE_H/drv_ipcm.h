/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_ipcm.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_ipcm.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_IPCM_H__
#define __DRV_IPCM_H__
#include "drv_global.h"

#ifdef __OS_RTOSCK__

#if defined(BSP_CORE_MODEM) 
#include <sre_base.h>
#endif

#else 

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(__VXWORKS__)
#include <vxWorks.h>
#endif

#endif

/* 处理器类型*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_ARM11 = 0x0,   /* P500上的IPC */
    IPC_CORE_A9,
    IPC_CORE_CEVA,
    IPC_CORE_TENS0,
    IPC_CORE_TENS1,
    IPC_CORE_DSP,
    IPC_CORE_APPARM = 0x0,  /* V7R1/V3R2上的IPC */
    IPC_CORE_COMARM,
    IPC_CORE_LTEDSP,
    IPC_CORE_VDSP,
    IPC_CORE_ZSP,
    IPC_CORE_DSP_GU,
    IPC_CORE_ACPU = 0x0,/* V9R1 SFT上的IPC */
    IPC_CORE_CCPU,
    IPC_CORE_MCU,
    IPC_CORE_HIFI,
    IPC_CORE_BBE16,


    /* !!!!新增元素请添加到最后  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

/*********************************************************
*  添加新IPC资源，枚举命名格式:
*  IPC_<目标处理器>_INT_SRC_<源处理器>_<功能/作用>
*  目标处理器:ACPU、CCPU、MCU、HIFI、BBE16
*  源处理器  :ACPU、CCPU、MCU、HIFI、BBE16
*  功能/作用 :
*********************************************************/
typedef enum tagIPC_INT_LEV_E
{
   /* 定义CCPU IPC跨核消息中断源bit位置 */
    IPC_INT_DSP_MODEM                   = 0,
    IPC_CCPU_INT_SRC_HIFI_MSG           = 1,    /* bit1, HIFI跨核消息通知 */
    IPC_INT_DSP_MSP                     = 2,
    IPC_INT_DSP_PS 						= 3,
    IPC_CCPU_INT_SRC_MCU_MSG            = 5,    /* bit5, MCU跨核消息通知 */
    IPC_CCPU_INT_SRC_ACPU_MSG           = 6,
    IPC_CCPU_INT_SRC_ACPU_IFC           = 7,
    IPC_INT_DSP_HALT                    = 8,    /* bit8, DSP通知ARM睡眠*/
    IPC_INT_DSP_RESUME                  = 9,    /* bit9, DSP通知ARM完成唤醒后的恢复操作*/
    IPC_CCPU_INT_SRC_MCU_IFC            = 10,
    IPC_INT_WAKE_GU                     = 11,   /* bit11, 主模唤醒从模中断*/
    IPC_INT_SLEEP_GU                    = 12,   /* bit12, 从模睡眠中断*/
    IPC_INT_DICC_USRDATA_ACPU           = 13,   /* bit13, 占位,该值必须与IPC_INT_DICC_USRDATA一致*/
    IPC_INT_DICC_RELDATA_ACPU           = 14,   /* bit14, 占位,该值必须与IPC_INT_DICC_USRDATA一致*/
    IPC_INT_ARM_SLEEP                   = 15,   /* bit15, 由8修改为15*/
    /* 定义TDS使用的邮箱IPC中断,begin */
    IPC_INT_WAKE_GSM                    = 16,   /* bit16, BBE16通知CCPU,唤醒GSM从模 */
    IPC_INT_WAKE_WCDMA                  = 17,   /* bit17, BBE16通知CCPU,唤醒WCDMA从模 */
    IPC_INT_DSP_PS_PUB_MBX              = 18,   /* 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_PS_MAC_MBX              = 19,   /* 上行DSP->ARM,与低功耗IPC中断复用 */
    IPC_INT_DSP_MBX_RSD                 = 20,   /* 上行DSP->ARM,与低功耗IPC中断复用 */
    /* 定义TDS使用的邮箱IPC中断,end */
    IPC_CCPU_INT_SRC_ACPU_ICC           = 30,
    IPC_CCPU_INT_SRC_BUTT               = 32,

   /* 定义MCU IPC跨核消息中断源bit位置 */
    IPC_MCU_INT_SRC_ACPU_MSG            = 4,    /* bit4, ACPU跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_MSG            = 5,    /* bit5, CCPU跨核消息通知 */
    IPC_MCU_INT_SRC_HIFI_MSG            = 6,    /* bit6, HIFI跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_IFC            = 7,    /* bit7, HIFI跨核消息通知 */
    IPC_MCU_INT_SRC_CCPU_IPF            = 8,    /* bit8, IPF低功耗 */
    IPC_MCU_INT_SRC_ACPU_IFC            = 9,    /* bit9, ACPU跨核函数调用通知 */
    IPC_MCU_INT_SRC_ACPU_HOTPLUG,
    IPC_MCU_INT_SRC_ACPU_PD             = 16,   /* bit16, acpu power down */
    IPC_MCU_INT_SRC_CCPU_PD             = 17,   /* bit17, ccpu power down */
    IPC_MCU_INT_SRC_HIFI_PD             = 18,   /* bit18, hifi power down */
    IPC_MCU_INT_SRC_MCU_AGT             = 19,   /* bit19, mcu agent */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    = 21,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   = 22,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID = 23,
    IPC_MCU_INT_SRC_BUTT                = 32,

    /* 定义ACPU IPC跨核消息中断源bit位置 */
    IPC_ACPU_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU跨核消息通知 */
    IPC_ACPU_INT_SRC_HIFI_MSG           = 2,    /* bit2, HIFI跨核消息通知 */
    IPC_ACPU_INT_SRC_MCU_MSG            = 3,    /* bit3, ACPU跨核消息通知 */
    IPC_ACPU_INT_SRC_CCPU_NVIM          = 4,    /* bit4,用于NVIM模块C核与A核之间的同步*/
    IPC_ACPU_INT_SRC_CCPU_IFC           = 5,
    IPC_ACPU_INT_SRC_MCU_IFC            = 6,
    IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH   = 7,    /*MCU电池放电高温关机IPC中断通知ACPU*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_LOW    = 8,    /*MCU电池放电低温关机IPC中断通知ACPU*/
    IPC_INT_DSP_APP                     = 9,
    IPC_INT_DICC_USRDATA                = 13,   /*必须与IPC_INT_DICC_USRDATA_ACPU同时修改*/
    IPC_INT_DICC_RELDATA                = 14,   /*必须与IPC_INT_DICC_RELDATA_ACPU同时修改*/
    IPC_ACPU_INI_SRC_MCU_EXC_REBOOT     = 27,
    IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT    = 28,
    IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT = 29,
    IPC_ACPU_INT_SRC_MCU_DDR_EXC        = 30,
    IPC_ACPU_INT_SRC_CCPU_ICC           = 31,
    IPC_ACPU_INT_SRC_BUTT               = 32,


    /* 定义HIFI IPC跨核消息中断源bit位置 */
    IPC_HIFI_INT_SRC_ACPU_MSG           = 0,    /* bit0, ACPU跨核消息通知 */
    IPC_HIFI_INT_SRC_CCPU_MSG           = 1,    /* bit1, CCPU跨核消息通知 */
    IPC_HIFI_INT_SRC_BBE_MSG            = 4,    /* bit4, TDDSP跨核消息通知 */
    IPC_HIFI_INT_SRC_MCU_MSG            = 6,
    IPC_HIFI_INT_SRC_BUTT               = 32,

    /* 定义BBE16 IPC跨核消息中断源bit位置 */
    IPC_INT_MSP_DSP_OM_MBX              = 0,   /* 下行ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX              = 1,   /* 下行ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX              = 2,   /* 下行ARM->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG          = 3,   /* bit3, HIFI跨核消息通知 */
    IPC_BBE16_INT_SRC_BUTT              = 32,
    /* 仅解决编译问题 */
    IPC_INT_BUTTOM                      = 32,
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_ICC,
    IPC_SEM_NAND,
    IPC_SEM_MEM,
    IPC_SEM_DICC,
    IPC_SEM_RFILE_LOG,          /*用于flashless可维可测*/
    IPC_SEM_EMMC,
    IPC_SEM_NVIM,
    IPC_SEM_SMP_CPU0 = 21,
    IPC_SEM_SMP_CPU1 = 22,
    IPC_SEM_SMP_CPU2 = 23,
    IPC_SEM_SMP_CPU3 = 24,
    IPC_SEM_SYNC = 25,
    IPC_SEM_BBP = 26,           /*该值与BBE16镜像绑定，修改需通知BBE16作相应修改*/
    IPC_SEM_DFS_HOTPLUG = 27,   /*调频调核互斥资源锁*/
    IPC_SEM_SYSCTRL = 30,
    IPC_SEM_ZSP_HALT = 31,
    IPC_SEM_BUTTOM
}IPC_SEM_ID_E;


#define INTSRC_NUM                     32

/* 新增P500的IPC驱动接口,该IPC专为L模LMSP、LPS封装使用,与GU模的IPC不冲突。
*/
/*****************************************************************************
* 函 数 名  : BSP_DRV_IPCIntInit_Lt
*
* 功能描述  : IPC模块初始化,L模专用
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_S32 BSP_DRV_IPCIntInit_Lt(void);

/*****************************************************************************
* 函 数 名  : BSP_IPC_IntEnable_Lt
*
* 功能描述  : 使能某个中断,L模专用
*
* 输入参数  :   IPC_INT_CORE_E enCoreNum 要使能中断的core
                BSP_U32 ulLvl 要使能的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntEnable_Lt (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 * 函 数 名  : BSP_INT_Disable_Lt
 *
 * 功能描述  : 去使能某个中断
 *
 * 输入参数  : IPC_INT_CORE_E enCoreNum 要使能中断的core
                BSP_U32 ulLvl 要使能的中断号，取值范围0～31
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 *****************************************************************************/
BSP_S32 BSP_IPC_IntDisable_Lt (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 * 函 数 名  : BSP_IPC_IntConnect_Lt
 *
 * 功能描述  : 注册某个中断,L模专用
 *
 * 输入参数  : IPC_INT_CORE_E enCoreNum 要使能中断的core
               BSP_U32 ulLvl 要使能的中断号，取值范围0～31
               VOIDFUNCPTR routine 中断服务程序
 *             BSP_U32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 *****************************************************************************/
BSP_S32 BSP_IPC_IntConnect_Lt(IPC_INT_LEV_E ulLvl, VOIDFUNCPTR routine, BSP_U32 parameter);

/*****************************************************************************
 * 函 数 名  : BSP_IPC_IntDisonnect_Lt
 *
 * 功能描述  : 取消注册某个中断,L模专用
 *
 * 输入参数  :
 *              BSP_U32 ulLvl 要使能的中断号，取值范围0～31
 *              VOIDFUNCPTR routine 中断服务程序
 *             BSP_U32 parameter      中断服务程序参数
 * 输出参数  : 无
 *
 * 返 回 值  : OK&ERROR
 *
 *****************************************************************************/
 BSP_S32 BSP_IPC_IntDisonnect_Lt (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);

 /*****************************************************************************
 * 函 数 名  : BSP_DRV_IpcIntHandler_Lt
 *
 * 功能描述  : 中断处理函数,L模专用
 *
 * 输入参数  : 无
 * 输出参数  : 无
 *
 * 返 回 值  : 无
 *
 *****************************************************************************/
BSP_VOID BSP_DRV_IpcIntHandler_Lt(void);

/*****************************************************************************
* 函 数 名  : BSP_IPC_IntSend_Lt
*
* 功能描述  : 发送中断,L模专用
*
* 输入参数  :
                IPC_INT_CORE_E enDstore 要接收中断的core
                BSP_U32 ulLvl 要发送的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntSend_Lt(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

/* 新增P500的IPC驱动接口,该IPC专为L模LPHY、LPS封装使用,与GU模的IPC不冲突。
*/

/*****************************************************************************
* 函 数 名  : BSP_DRV_IPCIntInit
*
* 功能描述  : IPC模块初始化
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_S32 BSP_DRV_IPCIntInit(void);


/*****************************************************************************
* 函 数 名  : DRV_IPC_SEMCREATE
*
* 功能描述  : 信号量创建函数
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_S32 BSP_IPC_SemCreate(BSP_U32 u32SignalNum);
extern BSP_S32 DRV_IPC_SEMCREATE(BSP_U32 u32SignalNum);

/*****************************************************************************
* 函 数 名  : DRV_IPC_SEMDELETE
*
* 功能描述  : 删除信号量
*
* 输入参数  :   BSP_U32 u32SignalNum 要删除的信号量编号

* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_SemDelete(BSP_U32 u32SignalNum);
extern BSP_S32 DRV_IPC_SEMDELETE(BSP_U32 u32SignalNum);

/*****************************************************************************
* 函 数 名  : BSP_IPC_IntEnable
*
* 功能描述  : 使能某个中断
*
* 输入参数  :
                BSP_U32 ulLvl 要使能的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntEnable (IPC_INT_LEV_E ulLvl);
extern BSP_S32 DRV_IPC_INTENABLE(IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* 函 数 名  : DRV_IPC_INTDISABLE
*
* 功能描述  : 去使能某个中断
*
* 输入参数  :
            BSP_U32 ulLvl 要使能的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntDisable (IPC_INT_LEV_E ulLvl);
extern BSP_S32 DRV_IPC_INTDISABLE(IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* 函 数 名  : BSP_IPC_IntConnect
*
* 功能描述  : 注册某个中断
*
* 输入参数  :
           BSP_U32 ulLvl 要使能的中断号，取值范围0～31
           VOIDFUNCPTR routine 中断服务程序
*             BSP_U32 parameter      中断服务程序参数
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntConnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);
extern BSP_S32 DRV_IPC_INTCONNECT(IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);

/*****************************************************************************
* 函 数 名  : BSP_IPC_IntDisonnect
*
* 功能描述  : 取消注册某个中断
*
* 输入参数  :
*              BSP_U32 ulLvl 要使能的中断号，取值范围0～31
*              VOIDFUNCPTR routine 中断服务程序
*             BSP_U32 parameter      中断服务程序参数
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntDisonnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);
extern BSP_S32 DRV_IPC_INTDISCONNECT  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);

/*****************************************************************************
* 函 数 名  : DRV_IPC_INTSEND
*
* 功能描述  : 发送中断
*
* 输入参数  :
                IPC_INT_CORE_E enDstore 要接收中断的core
                BSP_U32 ulLvl 要发送的中断号，取值范围0～31
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
*****************************************************************************/
BSP_S32 BSP_IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
extern BSP_S32 DRV_IPC_INTSEND(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

/*****************************************************************************
* 函 数 名  : DRV_IPC_SEMTAKE
*
* 功能描述  : 获取信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_S32 BSP_IPC_SemTake(BSP_U32 u32SignalNum,BSP_S32 s32timeout);
extern BSP_S32 DRV_IPC_SEMTAKE(BSP_U32 u32SignalNum, BSP_S32 s32timeout);

/*****************************************************************************
* 函 数 名  : DRV_IPC_SEMGIVE
*
* 功能描述  : 释放信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_VOID BSP_IPC_SemGive(BSP_U32 u32SignalNum);
extern BSP_VOID DRV_IPC_SEMGIVE(BSP_U32 u32SignalNum);

/*****************************************************************************
* 函 数 名  : BSP_IPC_SpinLock
*
* 功能描述  : 获取信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_VOID BSP_IPC_SpinLock (BSP_U32 u32SignalNum);
extern BSP_VOID DRV_SPIN_LOCK (BSP_U32 u32SignalNum);

/*****************************************************************************
* 函 数 名  : DRV_SPIN_UNLOCK
*
* 功能描述  : 释放信号量
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
*****************************************************************************/
BSP_VOID BSP_IPC_SpinUnLock (BSP_U32 u32SignalNum);
extern BSP_VOID DRV_SPIN_UNLOCK(BSP_U32 u32SignalNum);


BSP_S32 BSP_SGI_Connect(BSP_U32 ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);
BSP_S32 BSP_SGI_IntSend(BSP_U32 ulLvl);

#endif


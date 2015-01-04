/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_dpm.c
  版 本 号   : 初稿
  作    者   : c61362
  生成日期   : 2012年3月2日
  最近修改   :
  功能描述   : 底软给上层软件封装的接口层
  修改历史   :
  1.日    期   : 2012年3月2日
    作    者   : c61362
    修改内容   : 新建Drvinterface.c

  2.日    期   : 2013年2月19日
    作    者   : 蔡喜 220237
    修改内容   : 由Drvinterface.c拆分所得

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#if (defined BSP_CORE_APP)
#include <linux/module.h>
#endif

#include "BSP.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern void BSP_PWRCTRL_GetCcpuLoadCB(PWRCTRLFUNCPTR pFunc );
extern int printf(const char *format, ...);

/*****************************************************************************
  2 函数声明
*****************************************************************************/

#define printk(a)

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
Function:   DRV_PWRCTRL_SLEEP_IN_CB
Description:
Input:
Output:     None;
Return:
Others:
*****************************************************************************/
int DRV_PWRCTRL_SLEEP_IN_CB(PWC_DS_SOCP_CB_STRU stFunc)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_POWER_OFF
 功能描述  : 单板直接下电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void DRV_POWER_OFF(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#if( FEATURE_POWER_ON_OFF == FEATURE_ON )
    BSP_ONOFF_DrvPowerOff();
#else
    DRV_PRINTF("Function DRV_POWER_OFF unsupport!\n");
#endif
#endif

#if (defined BSP_CORE_APP)
    return;   /* 打桩 */
#endif
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEP_CALLBACK_REG
 功能描述  : 注册PWC函数给底软使用
 输入参数  : 待注册的函数
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
int DRV_PWRCTRL_SLEEP_CALLBACK_REG(PWC_SLEEP_CALLBACK_STRU pCallback)
{
    return 0;   /* 打桩 */
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC
 功能描述  : arm上下电功能，需要备份ahb数据，该接口申请数据保存地址和长度
 输入参数  : length     保存申请空间大小的指针
 输出参数  : 无
 返 回 值  : 申请空间的地址 。
*****************************************************************************/
void * DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC(unsigned int * length)
{
    return (void *)0;
}

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_RLS_PRF_CCPU
Description:Release the Vote Result
Input:      ulClientID: The Vote Module Client
Output:     None;
Return:     The Vote Result
Others:
*****************************************************************************/
BSP_U32 DRV_PWRCTRL_DFS_RLS_PRF_CCPU(PWC_DFS_ID_E ulClientID)
{
    return 0;
}

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_SET_PRF_CCPU
Description:Set the System Min Profile
Input:      ulClientID: The Vote Module Client
            enProfile:  The Min Profile Value
Output:     None
Return:     The Vote Result
Others:
*****************************************************************************/
BSP_U32  DRV_PWRCTRL_DFS_SET_PRF_CCPU(PWC_DFS_ID_E ulClientID, PWC_DFS_PROFILE_E enProfile)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GET_TEMP
 功能描述  : 获取OLED、电池、GPA、WPA、SIM卡、DCXO的温度。
 输入参数  : enModule:PWC_TEMP_PROTECT_E
             hkAdcTable:电压温度换算表
 输出参数  : pslData:存储的电压转换为的温度值
 返 回 值  : HKADC_OK/HKADC_ERROR 。
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_GET_TEMP(PWC_TEMP_PROTECT_E enModule, BSP_U16 *hkAdcTable,BSP_S32 *pslData)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GetCcpuLoadCB
 功能描述  : arm 提供给TTF的回调函数
 输入参数  : pFunc:TTF函数指针
 输出参数  : 无
 返 回 值  : 申请空间的地址 。
*****************************************************************************/
void DRV_PWRCTRL_GetCcpuLoadCB(PWRCTRLFUNCPTR pFunc )
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_PWRCTRL_GetCcpuLoadCB(pFunc);
#endif

#if (defined BSP_CORE_APP)
    ;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GetCpuLoad
 功能描述  : arm cpu占有率查询函数
 输入参数  : 无
 输出参数  : ulAcpuLoad:Acpu占有率地址.
             ulCcpuLoad:Ccpu占有率地址.
 返 回 值  : 0/1 。
*****************************************************************************/
unsigned int DRV_PWRCTRL_GetCpuLoad(unsigned int *ulAcpuLoad,unsigned int *ulCcpuLoad)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (unsigned int)BSP_PWRCTRL_GetCpuLoad(ulAcpuLoad,ulCcpuLoad);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PLL_ENABLE
 功能描述  : 通信模块控制时钟使能接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PLLENABLE (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PllEnable (enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PLL_DISABLE
 功能描述  : 通信模块控制时钟关闭接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PLLDISABLE (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PllDisable (enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_PllStatusGet
 功能描述  : 通信模块控制时钟状态查询接口
 输入参数  : enCommMode     通信模式
             enCommModule   通信模块
             enCommCard    时 卡号
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         时钟打开
             PWRCTRL_COMM_OFF        时钟关闭
             RET_ERR                 查询失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PLLSTATUSGET (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PllStatusGet(enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PWRUP
 功能描述  : 通信模块控制电源上电接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PWRUP (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PwrUp (enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PWRDOWN
 功能描述  : 通信模块控制电源下电接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PWRDOWN (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PwrDown (enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_PwrStatusGet
 功能描述  : 通信模块控制电源状态查询接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         上电
             PWRCTRL_COMM_OFF        下电
             RET_ERR                 状态查询失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_PWRSTATUSGET(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_PWRCTRL_PwrStatusGet(enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif

}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_LOCK
 功能描述  : 外设禁止睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
BSP_U32 DRV_PWRCTRL_SLEEPVOTE_LOCK(PWC_CLIENT_ID_E enClientId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (BSP_U32)BSP_PWRCTRL_SleepVoteLock(enClientId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 功能描述  : 外设允许睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
BSP_U32 DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWC_CLIENT_ID_E enClientId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (BSP_U32)BSP_PWRCTRL_SleepVoteUnLock(enClientId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKENABLE
 功能描述  : 开启通信模块时钟
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_BBPCLKENABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return PWRCTRL_BbpClkEnable(enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKDISABLE
 功能描述  : 关闭通信模块时钟
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
BSP_S32 DRV_PWRCTRL_BBPCLKDISABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return PWRCTRL_BbpClkDisable(enModeId, enModuleId, enModemId);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}


#define __DRV_STUB_DEF__

unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0; /*nas stub*/
}

void PWRCTRL_AcpuWakeUpInt(unsigned int type)
{
    return ;  /*drv ipc 模块打桩*/
}

int BSP_Modem_OS_Status_Switch(int enable)
{
    /*stub interface*/
    return 0;
}

BSP_VOID BSP_PWC_MspVoteRegister(FUNCPTR routine)
{
    /*stub interface*/
    return;
}

VOID BSP_PWC_SetTimer4WakeSrc(VOID)
{
    /*stub interface*/
    return;
}

VOID BSP_PWC_DelTimer4WakeSrc(VOID)
{
    /*stub interface*/
    return;
}

/*****************************************************************************
 Prototype      : BSP_PWRCTRL_StandbyStateAcpu
 Description    : AT^PSTANDBY
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By
*****************************************************************************/
unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchtime)
{
    return 0;   /* 打桩 */
}


#if (defined BSP_CORE_APP)
EXPORT_SYMBOL(BSP_Modem_OS_Status_Switch);
EXPORT_SYMBOL(DRV_PWRCTRL_SLEEPVOTE_LOCK);    /* nas acpu    需要打桩*/
EXPORT_SYMBOL(DRV_PWRCTRL_SLEEPVOTE_UNLOCK);  /* nas acpu    需要打桩*/
#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


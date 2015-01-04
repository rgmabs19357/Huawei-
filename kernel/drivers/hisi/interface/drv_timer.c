/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_timer.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年3月2日
  最近修改   :
  功能描述   : 底软给上层软件封装的接口层
  修改历史   :
  1.日    期   : 2012年3月2日
    作    者   : 
    修改内容   : 新建Drvinterface.c
    
  2.日    期   : 2013年2月19日
    作    者   : 
    修改内容   : 由Drvinterface.c拆分所得

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "BSP.h"
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include <vxWorks.h>
#include <private/vmLibP.h>
#include <cacheLib.h>
#include "arm_pbxa9.h"
#include <cacheLib.h>
#include "BSP_TIMER.h"
#include "sys_config.h"
#include "soc_baseaddr_interface.h"
#include "string.h"
#include "stdio.h"
#endif

#if (defined BSP_CORE_APP)
#include "bsp_timer_if.h"
#endif

#include "soc_baseaddr_interface.h"
#include "soc_timer_interface.h"
#include "soc_sctrl_interface.h"
#include <soc_ao_sctrl_interface.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

extern BSP_U32 BSP_BBP_GetCurTime(BSP_U64 *pCurTime);

/*****************************************************************************
  2 函数声明
*****************************************************************************/
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_S32 BSP_TIMER_GetRestTime(BSP_U32 usrClkId, BSP_U32 unitType, BSP_U32 * pRestTime);
extern BSP_S32 BSP_TIMER_UsrClkStart
(
    BSP_U32     usrClkId,
    FUNCPTR_1   routine,
    BSP_S32     arg,
    BSP_U32     timerValue,
    BSP_U32     mode,
    BSP_U32     unitType
);
extern BSP_S32 BSP_TIMER_UsrClkDisable(BSP_U32 usrClkId);
#endif

#if (defined BSP_CORE_APP)
extern int start_om_hard_timer(unsigned int value);
extern int stop_om_hard_timer(void);
extern int clear_om_hard_timer_int(void);
extern unsigned int GetHardTimerCurTime(void);
extern BSP_U32 BBPGetCurTime(BSP_U64 *pCurTime);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/************************************************************************
 * FUNCTION
 *       BSP_StartHardTimer
 * DESCRIPTION
 *       start hard timer
 * INPUTS
 *       value -- timer's value.uint is 32K cycle
 * OUTPUTS
 *       NONE
 *************************************************************************/
BSP_VOID BSP_StartHardTimer(BSP_U32 value)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return;/*delete by z00212992*/
#if 0 
    BSP_REG_WRITE((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_CTRL, CLK_DEF_TC_DISABLE);
    BSP_REG_WRITE((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_LOAD, value);
    BSP_REG_WRITE((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_CTRL, CLK_DEF_TC_ENABLE);
#endif
#endif

#if (defined BSP_CORE_APP)
    start_om_hard_timer(value);
#endif
}

/************************************************************************
 * FUNCTION
 *       BSP_StopHardTimer
 * DESCRIPTION
 *       Stop hard timer
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
BSP_VOID BSP_StopHardTimer(BSP_VOID)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return;/*delete by z00212992*/
#if 0    
    BSP_REG_WRITE((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_CTRL, CLK_DEF_TC_DISABLE);
#endif
#endif

#if (defined BSP_CORE_APP)
    stop_om_hard_timer();
#endif
}

/************************************************************************
 * FUNCTION
 *       BSP_GetHardTimerCurTime
 * DESCRIPTION
 *       Get hard timer Current Value
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
BSP_U32 BSP_GetHardTimerCurTime(BSP_VOID)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;/*delete by z00212992*/
#if 0    
    BSP_U32 readValue;
    BSP_REG_READ((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_CTRL, readValue);

    if(CLK_DEF_TC_DISABLE == readValue)
    {
        return 0;
    }

    BSP_REG_READ((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_VALUE, readValue);

    return readValue;
#endif    
#endif

#if (defined BSP_CORE_APP)
    return GetHardTimerCurTime();
#endif
}

/************************************************************************
 * FUNCTION
 *       BSP_ClearTimerINT
 * DESCRIPTION
 *       
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
BSP_VOID BSP_ClearTimerINT(BSP_VOID)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return;/*delete by z00212992*/
#if 0    
    BSP_U32 ulValue;    
    BSP_REG_READ((RTC_TIMER_REGBASE_ADDR), CLK_REGOFF_CLEAR, ulValue);
    
    /*for pclint*/
    ulValue = ulValue;

    return ;
#endif    
#endif

#if (defined BSP_CORE_APP)
    clear_om_hard_timer_int();
#endif
}

extern unsigned int omTimerGet(void);
/********************************************************************************************************************
 函 数 名  : BSP_GetSliceValue
 功能描述  : 获取时间戳Timer的当前值
 输出参数  :
 返 回 值  :
********************************************************************************************************************/
unsigned int BSP_GetSliceValue(void)
{
    return omTimerGet();
}

extern BSP_S32 BSP_TIMER_GetRestTime(BSP_U32 clk_logic_id, BSP_U32 unitType, BSP_U32 * pRestTime);
/*****************************************************************************
 函 数 名  : DRV_TIMER_GET_REST_TIME
 功能描述  : 获取定时器的剩余时间
 输入参数  : usrClkId:时钟ID,取值0~19
            unitType
            pRestTime
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史  :
 1.日    期   : 2012年7月19日
   作    者   :  
   修改内容   : 新生成函数

*****************************************************************************/
int DRV_TIMER_GET_REST_TIME(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime)
{    
    return BSP_TIMER_GetRestTime(usrClkId, unitType, pRestTime); 
}

extern BSP_S32 BSP_TIMER_UsrClkStart
(
    BSP_U32     clk_logic_id,
    FUNCPTR_1   routine,
    BSP_S32     arg,
    BSP_U32     timerValue,
    BSP_U32     mode,
    BSP_U32     unitType
);
/*****************************************************************************
 函 数 名  : DRV_TIMER_START
 功能描述  : 封装给协议栈的用户时钟定时器启动函数
 输入参数  : usrClkId:时钟ID,取值0~19
             routine:回调函数
             arg:回调参数
             timerValue:计数值
             mode:定时器模式，单次模式或周期模式.
             unitType:0表示单位ms，1表示单位us，2表示直接写load寄存器启动timer

 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史  :
 1.日    期   : 2012年7月19日
   作    者   :  
   修改内容    : 新生成函数

*****************************************************************************/
int DRV_TIMER_START
(
    unsigned int     usrClkId,
    FUNCPTR_1        routine,
    int              arg,
    unsigned int     timerValue,
    unsigned int     mode,
    unsigned int     unitType
)
{ 
    return BSP_TIMER_UsrClkStart(usrClkId, routine, arg, timerValue, mode, unitType);
}

extern BSP_S32 BSP_TIMER_UsrClkDisable(BSP_U32 clk_logic_id);
/*****************************************************************************
 函 数 名  : DRV_TIMER_STOP
 功能描述  : 封装给协议栈的用户时钟定时器停止函数
 输入参数  : usrClkId:时钟ID,取值0~19
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   作    者   :  
   修改内容    : 新生成函数

*****************************************************************************/
int DRV_TIMER_STOP(unsigned int usrClkId)
{
    return BSP_TIMER_UsrClkDisable(usrClkId);
}

/*****************************************************************************
* 函 数 名  : BSP_PWC_SetDrxTimerWakeSrc
* 功能描述  : 设置DRX timer 作为唤醒源
* 输入参数  :
* 输出参数  :
* 返 回 值   :
* 修改记录  : 从v7r1移植过来，内部固定使用TIMER_CCPU_DRX_TIMER_ID
*****************************************************************************/
void BSP_PWC_SetDrxTimerWakeSrc(void)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_TIMER_SetDrxTimerWakeSrc();
#endif

#if (defined BSP_CORE_APP)
    return;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_PWC_DelDrxTimerWakeSrc
* 功能描述  : 设置DRX timer 不作为唤醒源
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  : 从v7r1移植过来，内部固定使用TIMER_CCPU_DRX_TIMER_ID
*****************************************************************************/
void BSP_PWC_DelDrxTimerWakeSrc(void)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_TIMER_DelDrxTimerWakeSrc();
#endif

#if (defined BSP_CORE_APP)
    return;
#endif
}

extern unsigned int BSP_GET_RTC_VALUE(void);
/*****************************************************************************
 函 数 名  : DRV_GET_RTC_VALUE
 功能描述  : 读内rtc寄存器，获得当前RTC的值
 输入参数  : 无
 输出参数  : 无
 返回值    ：RTC值，单位s
 修改说明  :
             V9sft A、C核规格实现(A核在mach_info.c文件中，C核在BSP_TIMER.c文件中)
             V3sft A、C核打桩
*****************************************************************************/
unsigned int DRV_GET_RTC_VALUE(void)
{
    return BSP_GET_RTC_VALUE();
}

/*****************************************************************************
* 函 数 名  : BSP_USRCLK_Alloc
*
* 功能描述  : 申请用户时钟ID
*
* 输入参数  : BSP_S32 * ps32UsrClkId
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
BSP_U32 BSP_USRCLK_Alloc(BSP_S32 * ps32UsrClkId)
{
    return 0;
}

/*****************************************************************************
* 函 数 名  : BSP_BBPGetCurTime
*
* 功能描述  : 被PS调用，用来获取系统精确时间
*
* 输入参数  : 无
* 输出参数  : BSP_U32 u32CurTime:当前时刻
*
* 返 回 值  : BSP_OK : 获取成功
*                        BSP_ERR_INVALID_PARA  :获取失败
*
* 修改记录  : 2011年3月7日  wangjing  creat
*****************************************************************************/
BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)    
    return BSP_BBP_GetCurTime(pCurTime);
#endif

#if (defined BSP_CORE_APP)
    return BBPGetCurTime(pCurTime);
#endif
}

BSP_S32 BSP_TIMER_UsrClkEnable(BSP_U32 usrClkId, BSP_U32 value, BSP_U32 mode)
{
    return 0;
}

BSP_S32 BSP_USRCLK_Connect(FUNCPTR routine, BSP_S32 arg, BSP_S32 s32UsrClkid)
{
    return 0;
}   

BSP_S32 BSP_USRCLK_Disable (BSP_S32 s32UsrClkid)
{
    return 0;
}
 
BSP_S32 BSP_USRCLK_Enable (BSP_S32 s32UsrClkid)
{
    return 0;
}

BSP_S32 BSP_USRCLK_RateSet(BSP_S32 ticksPerSecond, BSP_S32 s32UsrClkid)
{
    return 0;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_wdt.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_wdt.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_WDT_H__
#define __DRV_WDT_H__
#include "drv_global.h"
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)

/*****************************************************************************
* 函 数 名  : BSP_WDT_Init
*
* 功能描述  : 初始化定制看门狗，设置超时时间，挂接中断服务函数
*
* 输入参数  : wdtId         看门狗ID,芯片提供1个看门狗，ID可以为0
*             wdtTimeOuts   看门狗超时时间，单位秒,时间最大不能超过51秒
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
*****************************************************************************/
BSP_S32 BSP_WDT_Init(BSP_U8 wdtId , BSP_U32 wdtTimeOuts);
#define DRV_WDT_INIT(wdtId,wdtTimeOuts)      BSP_WDT_Init(wdtId,wdtTimeOuts)

/*****************************************************************************
* 函 数 名  : BSP_WDT_EnableWdt
*
* 功能描述  : 开启看门狗
*
* 输入参数  : wdtId  看门狗ID
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
*****************************************************************************/
BSP_S32 BSP_WDT_Enable(BSP_U8 wdtId);
#define DRV_WDT_ENABLE(wdtId)    BSP_WDT_Enable(wdtId)

/*****************************************************************************
* 函 数 名  : BSP_WDT_Disable
*
* 功能描述  : 关闭看门狗
*
* 输入参数  : wdtId  看门狗ID
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
*****************************************************************************/
BSP_S32 BSP_WDT_Disable(BSP_U8 wdtId);
#define DRV_WDT_DISABLE(wdtId)    BSP_WDT_Disable(wdtId)
#endif

/*****************************************************************************
* 函 数 名  : BSP_WDT_HardwareFeed
*
* 功能描述  : 重置看门狗计数寄存器（喂狗）
*
* 输入参数  : wdtId  看门狗ID
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
*****************************************************************************/
BSP_S32 BSP_WDT_HardwareFeed(BSP_U8 wdtId);
#define DRV_WDT_FEED(wdtId)    BSP_WDT_HardwareFeed(wdtId)

/*****************************************************************************
 函 数 名  : BSP_ClearZSPWatchDogInt
 功能描述  : 清除一个ZSP WatchDog的中断
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 中断是否需要处理
*****************************************************************************/
extern BSP_BOOL BSP_ClearZSPWatchDogInt(BSP_VOID);
#define DRV_CLEAR_ZSPDOG_INT()   BSP_ClearZSPWatchDogInt()

/*****************************************************************************
 函 数 名  : BSP_ClearHIFIWatchDogInt
 功能描述  : 清除一个HIFI WatchDog的中断
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 中断是否需要处理
*****************************************************************************/
extern BSP_BOOL BSP_ClearHIFIWatchDogInt(BSP_VOID);
#define DRV_CLEAR_HIFIDOG_INT()   BSP_ClearHIFIWatchDogInt()

/*****************************************************************************
 函 数 名  : BSP_ZspWatchDogIntEnalbe
 功能描述  : 使能一个ZSP WatchDog的中断
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 中断是否需要处理
*****************************************************************************/
extern BSP_VOID BSP_ZSPWatchDogIntEnalbe(int level);
#define DRV_ZSPDOG_INT_ENABLE(level) BSP_ZSPWatchDogIntEnalbe(level)

/*****************************************************************************
 函 数 名  : BSP_ZspWatchDogIntEnalbe
 功能描述  : 使能一个ZSP WatchDog的中断
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 中断是否需要处理
*****************************************************************************/
extern BSP_VOID BSP_HIFIWatchDogIntEnalbe(int level);
#define DRV_HIFIDOG_INT_ENABLE(level) BSP_HIFIWatchDogIntEnalbe(level)

#endif


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_debug_led.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_debug_led.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_DEBUG_LED_H__
#define __DRV_DEBUG_LED_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*V9R1SFT SC基地址，BBIT平台无SC*/
#define SC_BASE    SOC_SCTRL_BASE_ADDR

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    DBLED_DRV1 = 0,        /* DRV调试灯1 */
    DBLED_DRV2,            /* DRV调试灯2 */
    DBLED_DSP1 = 2,        /* DSP调试灯1 */
    DBLED_DSP2,            /* DSP调试灯2 */
    DBLED_RESERVED1 = 4,   /* 保留调试灯1 */
    DBLED_RESERVED2,       /* 保留调试灯2 */
    DBLED_MAX
}DBLED_ID_E;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : DRV_DBLED_ON
 功能描述  : 调试灯灯点亮处理函数
 输入参数  : ledId:点灯ID,取值0~5
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月25日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_DBLED_ON(unsigned int ledId);

/*****************************************************************************
 函 数 名  : DRV_DBLED_OFF
 功能描述  : 调试灯熄灭处理函数
 输入参数  : ledId:点灯ID,取值0~5
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月25日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_DBLED_OFF(unsigned int ledId);

/*****************************************************************************
 函 数 名  : DRV_SYSCTRL_REG_SET
 功能描述  : DRV提供统一的sysctrl写接口函数
 输入参数  : regAddr：SC寄存器偏移地址；
             setData: SC寄存器值。
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月25日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_SYSCTRL_REG_SET(unsigned int regAddr, unsigned int setData);

/*****************************************************************************
 函 数 名  : DRV_SYSCTRL_REG_GET
 功能描述  : DRV提供统一的sysctrl读接口函数
 输入参数  : regAddr： SC寄存器偏移地址。
             getData：保存SC寄存器值的指针。
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月25日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_SYSCTRL_REG_GET(unsigned int regAddr, unsigned int * getData);





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_debug_led.h */


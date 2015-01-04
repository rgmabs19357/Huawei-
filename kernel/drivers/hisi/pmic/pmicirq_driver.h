/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmicirq_driver.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmicirq_driver.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PMIC_IRQ_DRIVER_H__
#define __PMIC_IRQ_DRIVER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/printk.h>
#include <linux/irq.h>
#include <linux/irqdesc.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/bitops.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/irqnr.h>
#include <linux/err.h>

#include <mach/early-debug.h>
#include <mach/gpio.h>
#include <mach/irqs.h>

#include "soc_smart_interface.h"
#include "soc_ao_sctrl_interface.h"

#include "pmic_driver.h"
#include "pmic_common.h"
#include "regulator_pmic_info.h"
#include "pmic_ssi.h"
#include "pmic_reg.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PMIC_NOMAL_PD 0
#define PMIC_EXC_PD   1
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct __PMUIRQ_DATA__
{
     struct platform_device *pdev;
     BSP_U32                 version ;
     unsigned  int           irq;
     spinlock_t              pmic_spinlock ;
     PMIC_MNTN_DESC*         mntn_desc;
}PMUIRQ_DATA;

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
extern void pmu_irq_unmask(unsigned int irq_num);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __PMIC_IRQ_DRIVER_H__ */


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : DrvInterface.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : DrvInterface.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_INTERFACE_H__
#define __DRV_INTERFACE_H__

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(__VXWORKS__)

#include "product_config.h"

#ifdef WIN32
#define __attribute__(p)
#endif

#ifndef _lint
#include "MemoryMap.h"
#endif

#ifdef __OS_RTOSCK__
#include <sre_base.h>
#else
#include <vxWorks.h>
#endif

#else

#ifndef _lint
#include <asm/io.h>
#include <mach/hardware.h>
#include "product_config.h"
#include <mach/drvLogDef.h>
#include <linux/scatterlist.h>
#include "MemoryMap.h"
#endif
#endif

#pragma pack(4)
#include "drv_interface_product_service.h"
#include "drv_interface_equipment_device.h"
#include "drv_interface_soc_device.h" 
#include "drv_interface_system_service.h"
#include "drv_interface_transfer_service.h"
#include "MODULE_H/drv_stub.h"
#include "MODULE_H/drv_nve.h"

#pragma pack(0)
#endif


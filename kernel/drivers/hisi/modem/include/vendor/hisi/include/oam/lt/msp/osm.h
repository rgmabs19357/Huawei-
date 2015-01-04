/*****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

*****************************************************************************
  文 件 名   : osm.h
  版 本 号   : V1.0
  生成日期   : 2008年07月07日
  功能描述   : OSL接口申明
  函数列表   : 无
  修改历史   :
  1.日    期 : 2008年07月07日
    修改内容 : 创建文件
*****************************************************************************/

#ifndef __OSM_H__
#define __OSM_H__

#include "vos.h"
#include "msp_errno.h"
#include "msp_nvim.h"
#if (VOS_VXWORKS == VOS_OS_VER)
#include <wdLib.h> /*c00149739*/

#elif (VOS_LINUX == VOS_OS_VER)
/* TO DO c00149739*/
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/socket.h>
#include <linux/skbuff.h>
#include <linux/list.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
/* c64416 for AT unite*/
/*#include <linux/decompress/mm.h>*/
#include <linux/tty.h>
#include <linux/delay.h>
#include <net/sock.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>
/* c64416 for AT unite*/
/*#include <../arch/powerpc/boot/stdio.h>*/
/*#include <../arch/powerpc/boot/stdlib.h>*/
#include <linux/time.h>
#include <../fs/ntfs/malloc.h>
#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/vmalloc.h>
/*#include <linux/kmalloc.h>*/
#include <linux/sem.h>
#include <linux/shm.h>
#include <linux/signal.h>

//#include "bsp_socp_drv.h"

/* c64416 for AT unite*/
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#define HAL_TRACE    vos_printf
#define HAL_PRINT    vos_printf
#define HAL_SDMLOG   vos_printf
#else
#define HAL_TRACE
#define HAL_PRINT
#if (VOS_LINUX == VOS_OS_VER)

#define HAL_SDMLOG   (VOS_VOID)printk
#else /* VX*/
#define HAL_SDMLOG  (VOS_VOID)vos_printf
#endif
#endif



typedef struct
{
    VOS_UINT32 ulMsgId;
    VOS_UINT32 ulParam1;
    VOS_UINT32 ulParam2;
} OS_MSG_STRU;

typedef struct
{
    VOS_UINT32 ulTimeId;
    VOS_UINT32 ulPara;    /* 对应原来的ulParam2*/
} OSM_MSG_TIMER_STRU;



/*****************************************************************************
 Heap Management
*****************************************************************************/

#define MSP_MEMCPY(dst,src,count)   memcpy(dst,src,count)   /* memcpy(dst,src,count) OSA_Memcpy(dst,src,count)*/
#define MSP_MEMSET(dst, val, count) memset(dst, val, count) /* memset(dst, val, count) OSA_Memset(dst, val, count)*/


#if (VOS_VXWORKS == VOS_OS_VER)
#define MSP_MALLOC(ulSize)          malloc(ulSize)
#define MSP_FREE(pAddr)             free(pAddr)
#elif (VOS_LINUX == VOS_OS_VER)
#define MSP_MALLOC(ulSize)          kmalloc(ulSize)
#define MSP_FREE(pAddr)             kfree(pAddr)
#else
#define MSP_MALLOC(ulSize)          malloc(ulSize)
#define MSP_FREE(pAddr)             free(pAddr)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __MSP_OSA_H__*/

/*************************************************************************
*   版权所有(C) 1987-2010, 深圳华为技术有限公司.
*
*   文 件 名 :  BSP_SYNC.c
*
*   作    者 :  wangxuesong
*
*   描    述 :  本文件基于IFC模块实现，用于管理模块主从核同步操作。
*
*   修改记录 :  2010年4月2日  v1.00  wangxuesong  创建
*************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/semaphore.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <asm/io.h>
#include <linux/sched.h>
#include <mach/hardware.h>

/*#include <mach/spinLockAmp.h>*/
#include <mach/common/mem/bsp_mem.h>
/*#include <mach/balong_v100r001.h>*/
#include "BSP.h"

#include "bsp_sync_drv.h"



/*--------------------------------------------------------------*
 * 宏定义                                                       *
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
 * 外部函数原型说明                                             *
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
 * 内部函数原型说明                                             *
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
 * 外部变量引用                                                 *
 *--------------------------------------------------------------*/

/*--------------------------------------------------------------*
 * 全局变量申明                                                 *
 *--------------------------------------------------------------*/

#define SYNC_SPINLOCK_ADDR  (MEM_CORESHARE_SYNC_ADDR)
#define SYNC_LOCK_ADDR      (SYNC_SPINLOCK_ADDR + 32)
#define SYNC_STATE_ADDR     (SYNC_LOCK_ADDR + 32)

BSP_U32 g_semSync = 0;
BSP_CHAR *g_pSyncLock = (BSP_CHAR*)SYNC_LOCK_ADDR;
BSP_CHAR *g_pSyncState = (BSP_CHAR*)SYNC_STATE_ADDR;

spinlock_t g_ipc_sem_sync_lock = SPIN_LOCK_UNLOCKED;
BSP_S32 SyncSpinLock(spinlock_t *lock)
{
    unsigned long flag;

    spin_lock_irqsave(lock, flag);
    BSP_IPC_SpinLock(IPC_SEM_SYNC);

    return (BSP_S32)flag;
}

BSP_VOID SyncSpinUnlock(spinlock_t *lock, BSP_S32 flag)
{
    BSP_IPC_SpinUnLock(IPC_SEM_SYNC);
    spin_unlock_irqrestore(lock, (unsigned long)flag);

    return;
}


/*****************************************************************************
* 函 数 名 : BSP_SYNC_Lock
*
* 功能描述 : 锁定并查询模块的初始化状态
*
* 输入参数 : u32Module     模块
*            pState        状态指针
*            u32TimeOut    超时值，0为永远等待；
*
* 输出参数 : 无
*
* 返 回 值 : OK&ERROR
*
* 其它说明: 无
*
*****************************************************************************/
BSP_S32 BSP_SYNC_Lock(SYNC_MODULE_E u32Module, BSP_U32 *pState, BSP_U32 u32TimeOut)
{
    BSP_S32 flag;
    struct timeval tmStart;
    struct timeval tmCur;
    struct timeval tmEnd;

    if(!pState || (u32Module >= SYNC_MODULE_BUTT))
    {
        printk("BSP_SYNC_Lock, invalid param, module=0x%x, pState=0x%x\n", u32Module, (BSP_U32)pState);
        return BSP_ERROR;
    }

    do_gettimeofday(&tmStart);
    tmEnd.tv_sec = tmStart.tv_sec + u32TimeOut/1000;
    tmEnd.tv_usec = tmStart.tv_usec + (u32TimeOut%1000)*1000;

    /* 目前只是在usrAppInit中使用，单任务情况下，使用循环查询效率较高
       如果需要支持多任务，需要适当的让出CPU */
    for(;;)
    {
        if(!g_pSyncLock[u32Module])
        {
            flag = SyncSpinLock(&g_ipc_sem_sync_lock);
            if(!g_pSyncLock[u32Module])
            {
                g_pSyncLock[u32Module] = 1;
                SyncSpinUnlock(&g_ipc_sem_sync_lock, flag);
                break;
            }
            else
            {
                SyncSpinUnlock(&g_ipc_sem_sync_lock, flag);
            }
        }

        if(u32TimeOut)
        {
            do_gettimeofday(&tmCur);
            if((tmEnd.tv_sec < tmCur.tv_sec) || ((tmEnd.tv_sec == tmCur.tv_sec) && (tmEnd.tv_usec < tmCur.tv_usec)))
            {
                printk("BSP_SYNC_Lock, timeout2, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);
                return BSP_ERR_SYNC_TIMEOUT;
            }
        }

        msleep(1);
    }

    *pState = (BSP_U32)g_pSyncState[u32Module];

    return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : BSP_SYNC_UnLock
*
* 功能描述  : 解锁并更新模块初始化状态
*
* 输入参数  : u32Module     模块
*             u32State       更新模块状态
*
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_S32 BSP_SYNC_UnLock(SYNC_MODULE_E u32Module, BSP_U32 u32State)
{
    if(u32Module >= SYNC_MODULE_BUTT)
    {
        printk("BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);

        return BSP_ERROR;
    }

    g_pSyncState[u32Module] = (BSP_CHAR)u32State;
    g_pSyncLock[u32Module] = 0;

    return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : BSP_SYNC_Wait
*
* 功能描述  : 从核等待主核操作完成函数
*
* 输入参数  : u32Module     模块
*             u32TimeOut    超时值，0为永远等待；
*
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_S32 BSP_SYNC_Wait(SYNC_MODULE_E u32Module, BSP_U32 u32TimeOut)
{
    struct timeval tmStart;
    struct timeval tmCur;
    struct timeval tmEnd;

    if(u32Module >= SYNC_MODULE_BUTT)
    {
        printk("BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);

        return BSP_ERROR;
    }

    do_gettimeofday(&tmStart);
    tmEnd.tv_sec = tmStart.tv_sec + u32TimeOut/1000;
    tmEnd.tv_usec = tmStart.tv_usec + (u32TimeOut%1000)*1000;

    for(;;)
    {
        if(g_pSyncState[u32Module])
        {
            return BSP_OK;
        }

        if(u32TimeOut)
        {
            do_gettimeofday(&tmCur);
            if((tmEnd.tv_sec < tmCur.tv_sec) || ((tmEnd.tv_sec == tmCur.tv_sec) && (tmEnd.tv_usec < tmCur.tv_usec)))
            {
                printk("BSP_SYNC_Wait, timeout, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);

                return BSP_ERR_SYNC_TIMEOUT;
            }
        }

        msleep(1);
    }
}


/*****************************************************************************
* 函 数 名  : BSP_SYNC_Give
*
* 功能描述  : 主核通知从核主核操作已经完成
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK&ERROR
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_S32 BSP_SYNC_Give(SYNC_MODULE_E u32Module)
{
    if(u32Module >= SYNC_MODULE_BUTT)
    {
        printk("BSP_SYNC_Give, invalid param, module=0x%x\n", u32Module);

        return BSP_ERROR;
    }

    g_pSyncState[u32Module] = 1;

    return BSP_OK;
}
EXPORT_SYMBOL(BSP_SYNC_Lock);
EXPORT_SYMBOL(BSP_SYNC_UnLock);
EXPORT_SYMBOL(BSP_SYNC_Wait);
EXPORT_SYMBOL(BSP_SYNC_Give);


#if 0   /*only for pc-lint*/
#include <kernel.h>
#include <kthread.h>
#include <module.h>
#include <slab.h>
#include <reset.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include <soc_wdt_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_mddrc_axi_interface.h>
#include <io.h>
#include "rfilesystem_process.h"
#include "rfilesystem_interface.h"
#include "BSP_IPF.h"
#include "bsp_icc_drv.h"
#include "bsp_drv_ipc.h"
#include "bsp_mailbox.h"
#include "usb_shell.h"
#include "excDrv.h"
#define KERN_INFO   "LEVEL2"
#define GFP_KERNEL  0
#else
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <mach/reset.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include <soc_wdt_interface.h>
#include <soc_baseaddr_interface.h>
#include <soc_mddrc_axi_interface.h>
#include <linux/io.h>
#include "MemoryMap.h"
#include "../../rfile/rfilesystem_process.h"
#include "../../rfile/rfilesystem_interface.h"
#include "BSP_IPF.h"
#include "../../multicore/icc/bsp_icc_drv.h"
#include "../../multicore/ipcm/bsp_drv_ipc.h"
#include "bsp_mailbox.h"
#include "../usb/usb_shell.h"
#include "linux/etb.h"
#include "../../mntn/excDrv.h"
#include <linux/notifier.h>         /* For notifier... */
#include "drv_timer.h"
#include <mach/util.h>				/* For mach_call_usermoduleshell*/
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
宏以及变量定义
*****************************************************************************/
#define CCORE_RESET_FLAG_VALUE      0x87654321  /*Ccore复位标志，寄存器值*/
#define CCORE_RESET_OK_FROM_CCORE      0x12345678  /*Ccore复位成功标志*/

/*C核狗相关值*/
#define CCORE_WDT_REG_VALUE_UNLOCK        0x1ACCE551
#define CCORE_WDT_REG_VALUE_LOCK          0x00000000

#define RESET_CBFUNC_PRIO_LEVEL_LOWT    0
#define RESET_CBFUNC_PRIO_LEVEL_HIGH    49
#define RESET_WAIT_TIMEOUT_MAILMSG      5000   /*ms, time of wating mail msg reply from hifi/mcu*/
#define RESET_WAIT_CCPU_STARTUP_TIMEOUT 30000  /*ms, time of wating mail msg reply from ccpu*/
#define RESET_WAIT_CCPU_ACKDONE_TIMEOUT 100    /*100us, time of wating ack done from ccpu*/

#define RESET_CBFUN_IGNORE_NAME         "NONAME"
/*因为b090以后已经支持把printk打印信息存储到文件，所以不需要本模块自己存储*/
#define PRINK_TO_FILE

#ifndef NULL
#define NULL    0
#endif

#define CCORE_RESET_TASK_PHASE_SET(a)     (g_stResetDebugInfo.ulCcpuTaskPhase = (a))
#define CCORE_RESET_TASK_PHASE_GET()      (g_stResetDebugInfo.ulCcpuTaskPhase)

/*用于协助完成复位过程*/
sreset_mgr_assistant   g_reset_assistant;
/*Link used for c core reset*/
sreset_mgr_LLI  *g_pmgr_ccorereset_data = NULL;
/*Link used for hifi reset*/
sreset_mgr_LLI  *g_pmgr_hifireset_data = NULL;
/*single reset debug info*/
sreset_debug_info g_stResetDebugInfo;

/*****************************************************************************
函数声明
*****************************************************************************/
int ccorereset_enable_wdt_irq(void);

extern void reset_set_cpu_status(unsigned int iOff, unsigned int iflag);
extern int ccorereset_loadcbin_loadaddr(void);
int platform_ddr_protect_init(int flag);
extern void codec_btn_simu_func(int pressed_button);

/*****************************************************************************
函数定义
*****************************************************************************/
IFC_GEN_CALL0(MAILBOX_IFC_ACPU_TO_CCPU_RST_MODEM, BSP_CCPU_Reset_Byhimself)

/*****************************************************************************
 函 数 名  : mailbox_recfun_mcu
 功能描述  : 用于接收来自于MCU的MAILBOX消息
 输入参数  : void  *UserHandle, 用户句柄
            void *MailHandle, 邮箱句柄
            unsigned long MailLen, 数据长度
 输出参数  : 无
 返 回 值  : void
*****************************************************************************/
void mailbox_recfun_mcu(void  *UserHandle,void *MailHandle,unsigned long MailLen)
{
    unsigned long   ulresult = 0;
    unsigned long   msg_len = sizeof(int);
    int msg_mcu = 0;

    ulresult = mailbox_read_msg_data(MailHandle, (unsigned char *)(&msg_mcu), &msg_len);
    printk(KERN_INFO "%s: receive mail from mcu, msg_mcu = %d,result = %ld\n", __FUNCTION__, msg_mcu, ulresult);
    if (0 == msg_mcu)
    {
        up(&(g_reset_assistant.sem_wait_mcu_msg));
    }
    else
    {
        /*保存log*/
        reset_no_ok_savelog("mcu", (int)msg_mcu, DRV_RESET_CALLCBFUN_RESET_BEFORE, BSP_RESET_MODULE_CCORE);

        /*复位系统*/
        printk(KERN_ERR "%s: mcu give wrong msg, msg is %d\n", __FUNCTION__, msg_mcu);
        do_reset_system(RESET_TYPE_MSG_FROM_MCU_WRONG);
    }
}
/*****************************************************************************
 函 数 名  : mailbox_recfun_mcu_hifireset
 功能描述  : 用于接收来自于MCU的MAILBOX消息
 输入参数  : void  *UserHandle, 用户句柄
            void *MailHandle, 邮箱句柄
            unsigned long MailLen, 数据长度
 输出参数  : 无
 返 回 值  : void
*****************************************************************************/
void mailbox_recfun_mcu_hifireset(void  *UserHandle,void *MailHandle,unsigned long MailLen)
{
    unsigned long   ulresult = 0;
    unsigned long   msg_len = sizeof(int);
    int msg_mcu = 0;

    ulresult = mailbox_read_msg_data(MailHandle, (unsigned char *)(&msg_mcu), &msg_len);
    printk(KERN_INFO "%s: receive mail from mcu, msg_mcu = %d,result = %ld\n", __FUNCTION__, msg_mcu, ulresult);
    if (1 == msg_mcu)
    {
        up(&(g_reset_assistant.sem_wait_mcu_msg_hifireset));
    }
    else
    {
        /*复位系统*/
        printk(KERN_INFO "%s: mcu give wrong msg, msg is %d\n", __FUNCTION__, msg_mcu);
        do_reset_system(RESET_TYPE_MSG_FROM_MCU_WRONG);
    }
}

/*****************************************************************************
 函 数 名  : mailbox_recfun_hifi
 功能描述  : 用于接收来自于HIFI的MAILBOX消息
 输入参数  : void  *UserHandle, 用户句柄
            void *MailHandle, 邮箱句柄
            unsigned long MailLen, 数据长度
 返 回 值  : void
*****************************************************************************/
void mailbox_recfun_hifi(void  *UserHandle,void *MailHandle,unsigned long MailLen)
{
    unsigned long   ulresult = 0;
    unsigned long   msg_len = sizeof(HIFI_AP_CCPU_RESET_CNF_STRU);
    HIFI_AP_CCPU_RESET_CNF_STRU msg_hifi = {0};

    ulresult = mailbox_read_msg_data(MailHandle, (unsigned char *)(&msg_hifi), &msg_len);
    printk(KERN_INFO "%s: receive mail from hifi, msg_hifi ret = %d,result = %ld\n", __FUNCTION__, msg_hifi.uhwResult, ulresult);

    if (ID_HIFI_AP_CCPU_RESET_CNF == msg_hifi.uhwMsgId
        && 0 == msg_hifi.uhwResult)
    {
        up(&(g_reset_assistant.sem_wait_hifi_msg));
    }
    else
    {
        /*复位系统*/
        printk(KERN_ERR "%s: hifi's msg is wrong\n", __FUNCTION__);
        do_reset_system(RESET_TYPE_MSG_FROM_HIFI_WRONG);
    }
}
/*****************************************************************************
 函 数 名  : reset_do_regcbfunc
 功能描述  : 用于其它组件注册回调函数，处理Modem复位前后相关数据。
 输入参数  :
         sreset_mgr_LLI *plink,管理链表，注意，允许为空.
            const char *pname, 组件注册的名字
         pdrv_reset_cbfun cbfun,    组件注册的回调函数
         int userdata,组件的私有数据
         Int Priolevel, 回调函数调用优先级 0-49，其中0-9 保留。
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
sreset_mgr_LLI * reset_do_regcbfunc(sreset_mgr_LLI *plink, const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    sreset_mgr_LLI  *phead = plink;
    sreset_mgr_LLI  *pmgr_unit = NULL;

    /*判断入参是否合法，不合法返回错误*/
    if (NULL == pname
        || NULL == pcbfun
        || (priolevel < RESET_CBFUNC_PRIO_LEVEL_LOWT || priolevel > RESET_CBFUNC_PRIO_LEVEL_HIGH))
    {
        printk(KERN_ERR "%s: fail in ccore reset regcb,fail, name 0x%x, cbfun 0x%x, prio %d\n", __FUNCTION__, \
                        (unsigned int)pname, (unsigned int)pcbfun, priolevel);
        return NULL;
    }

    /*分配空间*/
    pmgr_unit = (sreset_mgr_LLI*)kmalloc(sizeof(sreset_mgr_LLI), GFP_KERNEL);
    if (NULL != pmgr_unit)
    {
        memset((void*)pmgr_unit, 0, (sizeof(sreset_mgr_LLI)));
        /*赋值*/
        strncpy(pmgr_unit->cbfuninfo.name, pname, DRV_RESET_MODULE_NAME_LEN);
        pmgr_unit->cbfuninfo.priolevel = priolevel;
        pmgr_unit->cbfuninfo.userdata = userdata;
        pmgr_unit->cbfuninfo.cbfun = pcbfun;
    }

    /*第一次调用该函数，链表为空*/
    if (NULL == phead)
    {
        phead = pmgr_unit;
    }
    else
    {
    /*根据优先级插入链表*/
        phead = reset_link_insert(phead, pmgr_unit);
    }
    return phead;
}

/*****************************************************************************
 函 数 名  : ccorereset_regcbfunc
 功能描述  : 用于其它组件注册回调函数，处理Modem复位前后相关数据。
 输入参数  : const char *pname, 组件注册的名字
         pdrv_reset_cbfun cbfun,    组件注册的回调函数
         int userdata,组件的私有数据
         Int Priolevel, 回调函数调用优先级 0-49，其中0-9 保留。
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    g_pmgr_ccorereset_data = reset_do_regcbfunc(g_pmgr_ccorereset_data, pname, pcbfun, userdata, priolevel);
    printk(KERN_INFO "%s: %s registered a cbfun for ccore reset\n", __FUNCTION__, pname);
    return BSP_RESET_OK;
}


/*****************************************************************************
 函 数 名  : hifireset_regcbfunc
 功能描述  : 用于其它组件注册回调函数，处理HIFI复位前后相关数据。
 输入参数  : const char *pname, 组件注册的名字
         pdrv_reset_cbfun cbfun,    组件注册的回调函数
         int userdata,组件的私有数据
         Int Priolevel, 回调函数调用优先级 0-49，其中0-9 保留。
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    g_pmgr_hifireset_data = reset_do_regcbfunc(g_pmgr_hifireset_data, pname, pcbfun, userdata, priolevel);
    printk(KERN_INFO "%s: %s registered a cbfun for hifi reset\n", __FUNCTION__, pname);
    return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : ccorereset_task
 功能描述  : ccpu复位消息通知其他cpu。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_notify_other_cpu(struct notifier_block *cb, unsigned long code, void *p)
{
        int iResult = BSP_RESET_OK;

        /*填充消息内容*/
        g_reset_assistant.smailboxmsg_mcu.iproctec = BSP_RESET_MAILBOX_MSG_PROTECT;
        g_reset_assistant.smailboxmsg_mcu.idata = BSP_RESET_MCU_MSG_CCORE_RESET_BEFORE;
        /*消息ID*/
        g_reset_assistant.smailboxmsg_hifi.uhwMsgId = ID_AP_HIFI_CCPU_RESET_REQ;

        /*发送消息给HIFI*/
        printk(KERN_INFO "%s: msg id send to hifi is %d\n", __FUNCTION__, g_reset_assistant.smailboxmsg_hifi.uhwMsgId);
        iResult = ccorereset_tonotify(DRV_RESET_CALLCBFUN_RESET_BEFORE, BSP_RESET_MODULE_HIFI);
        if(BSP_RESET_OK != iResult)
        {
            printk(KERN_ERR "%s: fail send msg to hifi\n", __FUNCTION__);
            return BSP_RESET_ERROR;
        }
        iResult = ccorereset_tonotify(DRV_RESET_CALLCBFUN_RESET_BEFORE, BSP_RESET_MODULE_MCU);
        if(BSP_RESET_OK != iResult)
        {
            printk(KERN_ERR "%s: fail send msg to hifi\n", __FUNCTION__);
            return BSP_RESET_ERROR;
        }

        return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : ccorereset_task
 功能描述  : 等待其他cpu反馈。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
void ccorereset_wait_other_cpu(void)
{
#ifndef _DRV_LLT_
        if (0 != down_timeout(&(g_reset_assistant.sem_wait_hifi_msg), msecs_to_jiffies(RESET_WAIT_TIMEOUT_MAILMSG)))
        {
            /*复位系统*/
            printk(KERN_ERR "%s: fail to get mail from hifi,reset system\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_FAILGET_MSG_FROM_HIFI);
            return;
        }
#endif
        /*发送消息给MCU*/
        printk(KERN_INFO "%s: receive mail from hifi\n", __FUNCTION__);

#ifndef _DRV_LLT_
        if (0 != down_timeout(&(g_reset_assistant.sem_wait_mcu_msg), msecs_to_jiffies(RESET_WAIT_TIMEOUT_MAILMSG)))
        {
            /*复位系统*/
            printk(KERN_ERR "%s: fail to get mail from mcu,reset system\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_FAILGET_MSG_FROM_MCU);
            return;
        }
#endif
        printk(KERN_INFO "%s: receive mail from mcu\n", __FUNCTION__);
        printk(KERN_INFO "%s: leave\n", __FUNCTION__);
}

/*****************************************************************************
 函 数 名  : ccorereset_task
 功能描述  : 用于处理Modem复位。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_task(void *arg)
{
    int iresult = BSP_RESET_OK;

#ifdef _DRV_LLT_
#else
    for ( ; ; )
#endif
    {
        down(&(g_reset_assistant.sem_wait_ccorereset));
        printk(KERN_ERR "%s: enter\n", __FUNCTION__);
        CCORE_RESET_TASK_PHASE_SET(0);

        /*等待其他cpu的回复,这里主要指hifi和mcu*/
        ccorereset_wait_other_cpu();
        CCORE_RESET_TASK_PHASE_SET(1);

        /*调用复位前各组件注册回调函数*/
        iresult = ccorereset_runcbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE);
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to run callback fun before reset\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_RUNCB_STEP1_FAIL);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(2);

        /*复位ccpu、modem uart以及ipf等*/
        iresult = ccorereset_doreset();
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s:: fail to reset ccore\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_DORESET);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(3);

#ifdef _DRV_LLT_
#else
       /*重新加载BBE16核映像*/
        iresult = ccorereset_loadbbebin();
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to load bbe16 bin\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_LOAD_BBE16_FAIL);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(4);

       /*重新加载C核映像*/
        iresult = ccorereset_loadcbin();
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to load ccpu bin\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_LOAD_CCPU_FAIL);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(5);
#endif
        /*用于表示ccore已经复位*/
        g_reset_assistant.iccore_reset = 1;

        /*设置寄存器值,告诉ccpu这是复位后开机*/
        (void)ccorereset_setCresetFlag();
        CCORE_RESET_TASK_PHASE_SET(6);

        /*解复位ccpu*/
        (void)ccorereset_dostart();
        CCORE_RESET_TASK_PHASE_SET(7);

        enable_etm_reset();
        CCORE_RESET_TASK_PHASE_SET(8);

        /*设置发送给mcu的mailbox数据值,发送消息给MCU*/
        g_reset_assistant.smailboxmsg_mcu.iproctec = BSP_RESET_MAILBOX_MSG_PROTECT;
        g_reset_assistant.smailboxmsg_mcu.idata = BSP_RESET_MCU_MSG_CCORE_RESET_AFTER;
        iresult = ccorereset_tonotify(DRV_RESET_CALLCBFUN_RESET_AFTER, BSP_RESET_MODULE_MCU);
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to notify mcu after reset\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_NOTIFY_AFTER);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(9);

        /*等待ccpu启动成功通知*/
        printk(KERN_ERR "%s: wait for ccore startup finish\n", __FUNCTION__);
        if (0 != down_timeout(&(g_reset_assistant.sem_wait_ccorereset_ok), msecs_to_jiffies(RESET_WAIT_CCPU_STARTUP_TIMEOUT)))
        {
            printk(KERN_ERR "%s: wait for ccpu startup, timeout\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_CRUN_NO_OK);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(10);

        /*调用复位后回调函数*/
        iresult = ccorereset_runcbfun(DRV_RESET_CALLCBFUN_RESET_AFTER);
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to run after-cb fun\n", __FUNCTION__);
            /*复位系统*/
            do_reset_system(RESET_TYPE_CRESET_RUNCB_STEP2_FAIL);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(11);

        /*设置发送给mcu的mailbox数据值,发送消息给MCU*/
        g_reset_assistant.smailboxmsg_mcu.iproctec = BSP_RESET_MAILBOX_MSG_PROTECT;
        g_reset_assistant.smailboxmsg_mcu.idata = BSP_RESET_MCU_MSG_CCORE_RESET_FINISH;
        iresult = ccorereset_tonotify(DRV_RESET_CALLCBFUN_RESET_AFTER, BSP_RESET_MODULE_MCU);
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to notify mcu finish reset\n", __FUNCTION__);
            do_reset_system(RESET_TYPE_CRESET_NOTIFY_FINISH);
            return BSP_RESET_ERROR;
        }
        CCORE_RESET_TASK_PHASE_SET(12);
        
        mach_call_usermodeshell("/system/etc/log/crash_notice.sh",0);/*notice LogServer to handle log-bins*/
        
        printk(KERN_ERR "%s: leave\n", __FUNCTION__);
    }
}

/*****************************************************************************
 函 数 名  : hifireset_task
 功能描述  : 用于处理HIFI复位。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int hifireset_task(void *arg)
{
    int iresult = BSP_RESET_OK;

#ifdef _DRV_LLT_
#else
    for ( ; ; )
#endif
    {
        printk(KERN_INFO "%s: enter hifireset_task\n", __FUNCTION__);
        down(&(g_reset_assistant.sem_wait_hifireset));
        printk(KERN_INFO "%s: hifi reset int is coming!\n", __FUNCTION__);
        reset_for_savelog("\n=============hifi reset=============\n");

        /*调用回调函数*/
        iresult = hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE);
        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to run cb func before hifi reset\n", __FUNCTION__);

            /*复位系统*/
            do_reset_system(RESET_TYPE_HIFIRESET_RUNCB_STEP1_FAIL);
            return BSP_RESET_ERROR;
        }
#ifdef _DRV_LLT_
#else
        if (0 != down_timeout(&(g_reset_assistant.sem_wait_mcu_msg_hifireset), msecs_to_jiffies(RESET_WAIT_TIMEOUT_MAILMSG)))
        {
            /*复位系统*/
            printk(KERN_ERR "%s: fail to get mail from mcu,reset system\n", __FUNCTION__);
            /*do_reset_system(RESET_TYPE_FAILGET_MSG_FROM_MCU);*/
            return BSP_RESET_ERROR;
        }
        printk(KERN_INFO "%s: to load hifi bin!\n", __FUNCTION__);
        reset_for_savelog("To load hifi bin\n");
       /*重新加载HIFI映像*/
        iresult = hifireset_loadhifibin();
        if (BSP_RESET_OK != iresult)
        {
            reset_for_savelog("fail to load hifi bin\n");
            printk(KERN_ERR "%s: fail to load hifi bin! reset system\n", __FUNCTION__);
            /*复位系统*/
            do_reset_system(RESET_TYPE_HIFIRESET_LOAD_BIN_FAIL);
            return BSP_RESET_ERROR;
        }
#endif

        printk(KERN_INFO "%s: to run cb fun after hifi reset!\n", __FUNCTION__);
        reset_for_savelog("To run cb func after hifi reset\n");
        /*HIFI加载完毕后，调用回调函数*/
        iresult = hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_AFTER);

        /*恢复中断使能*/
        finish_reset_sub();

        if (BSP_RESET_OK != iresult)
        {
            printk(KERN_ERR "%s: fail to run cb fun after hifi reset! reset system\n", __FUNCTION__);
            /*复位系统*/
            do_reset_system(RESET_TYPE_HIFIRESET_RUNCB_STEP2_FAIL);
            return BSP_RESET_ERROR;
        }
        printk(KERN_INFO "%s: reset hifi successfully!\n", __FUNCTION__);
        reset_for_savelog("hifi reset ok\n");
    }
}

/*****************************************************************************
 函 数 名  : ccorereset_runcbfun
 功能描述  : Modem复位前后调用回调函数的函数。
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam, 0 表示modem复位前；非零表示复位后。

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int ccorereset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam)
{
    int  iresult = 0;

    sreset_mgr_LLI  *phead = g_pmgr_ccorereset_data;

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        reset_set_cpu_status(1, RESET_CPU_CCORE_STATUS_OFF);
    }
    else
    {
        reset_set_cpu_status(0, RESET_CPU_CCORE_STATUS_OFF);
    }
    /*根据回调函数优先级，调用回调函数*/
    while (NULL != phead)
    {
        if (NULL != phead->cbfuninfo.cbfun)
        {
            iresult = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
            if (BSP_RESET_OK != iresult)
            {
                /*如果返回失败，记录下组件名字,返回值*/
                printk(KERN_ERR "%s: fail to run cbfun of %s, at %d return %d\n", __FUNCTION__, phead->cbfuninfo.name, eparam, iresult);
                break;
            }
            printk(KERN_INFO "%s: run %s cb function 0x%x success\n", __FUNCTION__, phead->cbfuninfo.name, (unsigned int)phead->cbfuninfo.cbfun);
        }
        phead = phead->pnext;
    }
    printk(KERN_INFO "%s: leave, eparam = %d, iresult = %d\n", __FUNCTION__, eparam, iresult);
    return iresult;
}

/*****************************************************************************
 函 数 名  :  hifireset_doruncbfun
 功能描述  : HIFI复位前后调用回调函数的函数。由于圈复杂度超标，所以这里封装函数
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam, 0 表示HIFI复位前；非零表示复位后。

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int hifireset_doruncbfun (const char *pname, DRV_RESET_CALLCBFUN_MOMENT eparam)
{
    int  iresult = BSP_RESET_OK;

    sreset_mgr_LLI  *phead = g_pmgr_hifireset_data;

    if (NULL != pname)
    {
        /*不判断模块名字,按顺序执行*/
        if (strcmp(pname, RESET_CBFUN_IGNORE_NAME) == 0)
        {
            while (NULL != phead)
            {
                if (NULL != phead->cbfuninfo.cbfun)
                {
                    iresult = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
                    if (BSP_RESET_OK != iresult)
                    {
                        /*如果返回失败，记录下组件名字,返回值*/
                        reset_no_ok_savelog(phead->cbfuninfo.name, iresult, eparam, BSP_RESET_MODULE_CCORE);
                        printk(KERN_ERR "%s: fail to run cbfun of %s, at %d return %d\n", __FUNCTION__, phead->cbfuninfo.name, eparam, iresult);
                        break;
                    }
                    printk(KERN_INFO "%s: run %s cb function 0x%x\n", __FUNCTION__, phead->cbfuninfo.name, (unsigned int)phead->cbfuninfo.cbfun);
                }
                phead = phead->pnext;
            }
        }
        else/*需要判断模块名字，执行指定的回调函数*/
        {
            while (NULL != phead)
            {
                if (strcmp(pname, phead->cbfuninfo.name) == 0
                    && NULL != phead->cbfuninfo.cbfun)
                {
                    iresult  = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
                    printk(KERN_INFO "%s: run %s cb function 0x%x\n", __FUNCTION__, phead->cbfuninfo.name, (unsigned int)phead->cbfuninfo.cbfun);
                    break;
                }
                phead = phead->pnext;
            }
        }
    }
    else
    {
        iresult = BSP_RESET_ERROR;
    }
    if (BSP_RESET_OK != iresult)
    {
        if (NULL != phead)
        {
            reset_no_ok_savelog(phead->cbfuninfo.name, iresult, eparam, BSP_RESET_MODULE_HIFI);
            printk(KERN_ERR "%s: fail to run cbfun of %s, at %d, return %d\n", __FUNCTION__, phead->cbfuninfo.name, eparam ,iresult);

        }
        else
        {
            printk(KERN_ERR "%s: fail to run cbfun, but phead or pname is null\n", __FUNCTION__);
        }
    }
    return iresult;
}

/*****************************************************************************
 函 数 名  :  hifireset _runcbfun
 功能描述  : HIFI复位前后调用回调函数的函数。
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam, 0 表示HIFI复位前；非零表示复位后。

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int hifireset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam)
{
    int  iresult = 0;

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        /*Mailbox 处理*/
        reset_set_cpu_status(1, RESET_CPU_HIFI_STATUS_OFF);
        /*遍历回调函数链表，调用NAS的回调*/
        iresult = hifireset_doruncbfun("NAS_AT", eparam);
        if (BSP_RESET_OK != iresult)
        {
        /*如果返回失败，记录下组建name, 返回值，保存到文件*/
            goto return_error;
        }

        /*遍历回调函数链表，调用音频的回调*/
        iresult = hifireset_doruncbfun("CODEC", eparam);
        if (BSP_RESET_OK != iresult)
        {
        /*如果返回失败，记录下组建name, 返回值，保存到文件*/
            goto return_error;
        }

        /*通知MCU*/
        g_reset_assistant.smailboxmsg_mcu.iproctec = BSP_RESET_MAILBOX_MSG_PROTECT;
        g_reset_assistant.smailboxmsg_mcu.idata = BSP_RESET_MCU_MSG_HIFI_RESET_BEFORE;
        hifireset_tonotify(eparam, BSP_RESET_MODULE_MCU);
        /*遍历回调函数链表，调用OM的回调*/
        iresult = hifireset_doruncbfun("OAM", eparam);
        if (BSP_RESET_OK != iresult)
        {
        /*如果返回失败，记录下组建name, 返回值，保存到文件*/
            goto return_error;
        }
    }
    else
    {
        /*通知MCU*/
        g_reset_assistant.smailboxmsg_mcu.idata = BSP_RESET_MCU_MSG_HIFI_RESET_AFTER;
        hifireset_tonotify(eparam, BSP_RESET_MODULE_MCU);

        /*MAILBOX处理*/
        reset_set_cpu_status(0, RESET_CPU_HIFI_STATUS_OFF);

        /*遍历回调函数链表，调用回调函数*/
        iresult = hifireset_doruncbfun(RESET_CBFUN_IGNORE_NAME, eparam);
        if (BSP_RESET_OK != iresult)
        {
            goto return_error;
        }
    }
    printk(KERN_INFO "%s: end of run cb functions for hifi reset at %d, %d\n", __FUNCTION__, eparam, iresult);
    return BSP_RESET_OK;
return_error:
    return BSP_RESET_ERROR;
}
/*****************************************************************************
 函 数 名  : reset_link_insert
 功能描述  : 将数据插入链表
 输入参数  : sreset_mgr_LLI *plink, 链表指针
             sreset_mgr_LLI *punit，待插入的节点指针
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit)
{
    sreset_mgr_LLI    *phead = plink;
    sreset_mgr_LLI    *ppose = plink;
    sreset_mgr_LLI    *ptail = plink;

    if (NULL == plink || NULL == punit)
    {
        return NULL;
    }
    while (NULL != ppose)
    {
        /*根据优先级插入到链表中*/
        if (ppose->cbfuninfo.priolevel > punit->cbfuninfo.priolevel)
        {
            if (phead == ppose)
            {
                punit->pnext = ppose;
                phead = punit;
            }
            else
            {
                ptail->pnext = punit;
                punit->pnext = ppose;
            }
            break;
        }
        ptail = ppose;
        ppose = ppose->pnext;
    }
    if (NULL == ppose)
    {
        ptail->pnext = punit;
    }
    return phead;
}

/*****************************************************************************
 函 数 名  : ccorereset_tonotify
 功能描述  : CCORE复位时，通知MCU或者HIFI
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam,复位前还是复位后
            int imodule, 要通知的模块，0，MCU;1,HIFI
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule)
{
    unsigned long   result = 0;

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        if (BSP_RESET_MODULE_MCU == emodule)
        {
            result = mailbox_send_msg(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
                (void *)(&g_reset_assistant.smailboxmsg_mcu), sizeof(g_reset_assistant.smailboxmsg_mcu));
        }
        else if (BSP_RESET_MODULE_HIFI == emodule)
        {
            result = mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_CCORE_RESET_ID,
                (void *)(&g_reset_assistant.smailboxmsg_hifi), sizeof(g_reset_assistant.smailboxmsg_hifi));
        }
    }
    else
    {
        if (BSP_RESET_MODULE_MCU == emodule)
        {
            result = mailbox_send_msg(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
                (void *)(&g_reset_assistant.smailboxmsg_mcu), sizeof(g_reset_assistant.smailboxmsg_mcu));
        }
        else
        {
            /*printk(KERN_INFO "%s: to notify none in ccorereset_tonotify\n", __FUNCTION__);*/
        }
    }
    /*printk(KERN_INFO "%s: send mail to %d, at %d, result=%d\n", __FUNCTION__, emodule, eparam, result);*/

    return ((MAILBOX_OK == result) ? BSP_RESET_OK : BSP_RESET_ERROR);
}

/*****************************************************************************
 函 数 名  : ccorereset_tonotify
 功能描述  : HIFI复位时，通知MCU
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam,复位前还是复位后
            int imodule, 要通知的模块，0，MCU;1,HIFI
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int hifireset_tonotify(DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule)
{
    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        if (BSP_RESET_MODULE_MCU == emodule)
        {
            mailbox_send_msg(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
                (void *)(&g_reset_assistant.smailboxmsg_mcu), sizeof(g_reset_assistant.smailboxmsg_mcu));
        }
        else
        {
            printk(KERN_ERR "%s: to notify none in hifireset_tonotify\n", __FUNCTION__);
        }
    }
    else
    {
        if (BSP_RESET_MODULE_MCU == emodule)
        {
            mailbox_send_msg(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_RST_CH,
                (void *)(&g_reset_assistant.smailboxmsg_mcu), sizeof(g_reset_assistant.smailboxmsg_mcu));
        }
        else
        {
            printk(KERN_ERR "%s: to notify none in hifireset_tonotify\n", __FUNCTION__);
        }
    }
    printk(KERN_INFO "%s: after send mail to %d, %d\n", __FUNCTION__, emodule, eparam);
    return BSP_RESET_OK;
}
/*****************************************************************************
 函 数 名  : ccorereset_setCresetFlag
 功能描述  : 设置复位CCORE标志寄存器
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_setCresetFlag(void)
{
#ifdef _DRV_LLT_
#else
    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
    unsigned long uvalue = 0;

    uvalue = readl(SOC_SCTRL_SC_RESERVED16_ADDR(sctrl_off));
    printk(KERN_INFO "%s: org value = 0x%lx\n", __FUNCTION__, uvalue);

    writel(CCORE_RESET_FLAG_VALUE, SOC_SCTRL_SC_RESERVED16_ADDR(sctrl_off));

#endif
    printk(KERN_INFO "%s: leave\n", __FUNCTION__);
    return 0;
}
/*****************************************************************************
 函 数 名  : ccorereset_doreset
 功能描述  : 复位CCORE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_doreset(void)
{
#ifdef _DRV_LLT_
#else
    unsigned long sctrl_on  = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
    unsigned long uvalue_jedge = 0;
    volatile unsigned long uvalue = 0;
    unsigned int ulAckWaitCnt = 0;

    uvalue = readl(SOC_SCTRL_SC_CARM_STAT0_ADDR(sctrl_off));
    uvalue = readl(SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
    printk(KERN_INFO "%s: org value = 0x%lx\n", __FUNCTION__, uvalue);
    /*mcpu debug req*/
    writel((uvalue | BIT(SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_START)), SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));

    /*wait, dbgack & dbgdone*/
    uvalue_jedge = (BIT(SOC_SCTRL_SC_CARM_STAT0_carm_dbgack_START)
                    | BIT(SOC_SCTRL_SC_CARM_STAT0_carm_dbgcpudone_START));
    do{
        udelay(100);
        uvalue = readl(SOC_SCTRL_SC_CARM_STAT0_ADDR(sctrl_off));
        ulAckWaitCnt++;
    }while(((uvalue & uvalue_jedge) != uvalue_jedge) && (ulAckWaitCnt < RESET_WAIT_CCPU_ACKDONE_TIMEOUT));
    if((uvalue & uvalue_jedge) != uvalue_jedge)
    {
        return BSP_RESET_ERROR;
    }

    /*iso*/
    writel(BIT(SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_5mcpu_START), SOC_AO_SCTRL_SC_PW_ISOEN1_ADDR(sctrl_on));

    /*mcpu外设复位*/
    writel((BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_11mcpu_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_12mscu_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_13mp_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_14mwd_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_15mdbg_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_16mdapb_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_17matb_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_18mptm_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_19malone_START)), SOC_SCTRL_SC_PERIPH_RSTEN0_ADDR(sctrl_off));

    uvalue = readl(SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));
    printk(KERN_INFO "%s: new value = 0x%lx\n", __FUNCTION__, uvalue);
    /*恢复dbg req*/
    writel((uvalue & (~(BIT(SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_START)))), SOC_SCTRL_SC_CARM_CTRL0_ADDR(sctrl_off));

    /*HOLD BBE16*/
    uvalue = readl(SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ADDR(sctrl_off));
    uvalue = uvalue | BIT(SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_runstall_START);
    writel(uvalue, SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ADDR(sctrl_off));
    /*wait for holding*/
    msleep(5);
    /*复位BBE16*/
    writel(BIT(SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_14ltebbptop_START), SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(sctrl_on));

    /*复位muart*/
    writel((BIT(SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_16muart0_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_17muart1_START)), SOC_SCTRL_SC_PERIPH_RSTEN6_ADDR(sctrl_off));

    /* 复位IPF */
    writel(BIT(SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_21reset_ipf_n_START), SOC_SCTRL_SC_PERIPH_RSTEN1_ADDR(sctrl_off));

    printk(KERN_INFO "%s: leave\n", __FUNCTION__);
#endif
    return BSP_RESET_OK;
}
/*****************************************************************************
 函 数 名  : ccorereset_enable_wdt_irq
 功能描述  : 通过写寄存器实现其他核中断到a核
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_enable_wdt_irq(void)
{
#ifdef _DRV_LLT_
#else
    unsigned long sctrl_on  = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    unsigned long uvalue = 0;

    uvalue = readl(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(sctrl_on));
    printk(KERN_INFO "%s: org val = 0x%lx\n", __FUNCTION__, uvalue);

    writel((uvalue | (1 << 6)), SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(sctrl_on));
    uvalue = readl(SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(sctrl_on));
    printk(KERN_INFO "%s: new val = 0x%lx\n", __FUNCTION__, uvalue);

    writel(0x1f, SOC_AO_SCTRL_SC_INT_EN0_ADDR(sctrl_on));
    uvalue = readl(SOC_AO_SCTRL_SC_INT_EN0_ADDR(sctrl_on));
    printk(KERN_INFO "%s: new uvalue = 0x%lx\n", __FUNCTION__, uvalue);

#endif
    return 0;
}

#ifdef _DRV_LLT_
int platform_ddr_protect_init(int flag)
{
    return 0;
}
#endif

/*****************************************************************************
 函 数 名  : ccorereset_dostart
 功能描述  : 解复位CCORE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_dostart(void)
{
#ifdef _DRV_LLT_
#else

    unsigned long sctrl_on  = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
    unsigned long   iviraddr_dest1 = 0;


    /* modem 的起始地址固定为零地址，因此需要在零地址写跳转指令 */
    iviraddr_dest1 = (unsigned long)(ioremap_nocache(0x00000000, 4096));

    writel(0xE59F0004, iviraddr_dest1);            /*ldr  r0, 0xc*/
    writel(0xE59FD004, iviraddr_dest1 + 4);   /*ldr  r13, 0x10*/
    writel(0xE1A0F000, iviraddr_dest1 + 8);   /*mov  pc, r0*/
    writel(MODEM_UNZIP_RUN_ADDR, iviraddr_dest1 + 0xc);   /*写入modem 镜像起始地址*/
    writel(MODEM_ZIP_LOAD_ADDR, iviraddr_dest1 + 0x10);   /*写入栈地址*/
    iounmap((void*)iviraddr_dest1);

    writel(BIT(SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_5mcpu_START), SOC_AO_SCTRL_SC_PW_ISODIS1_ADDR(sctrl_on));
    writel((BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_11mcpu_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_12mscu_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_13mp_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_14mwd_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_15mdbg_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_16mdapb_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_17matb_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_18mptm_START)
            | BIT(SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_19malone_START)), SOC_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sctrl_off));
#endif

    printk(KERN_INFO "%s: leave\n", __FUNCTION__);
    return 0;
}


/*****************************************************************************
 函 数 名  : ccorereset_icc_cok_notify
 功能描述  : 用于Modem复位成功后调用以便通知ACPU复位成功。
 输入参数  : 无

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
unsigned int ccorereset_icc_cok_notify(unsigned int chenalId,signed int u32size)
{
    unsigned int readSize;
    int ireadvalue = 0;


    /*ICC读取数据*/
    readSize = udi_read(g_reset_assistant.ccorereset_IccFd,(void*)(&ireadvalue),u32size);
    printk(KERN_INFO "%s: get icc msg from c core, readsize = %d, wantsize = %d, ireadvalue = 0x%x\n", \
                    __FUNCTION__, readSize, u32size, ireadvalue);

    if (readSize != u32size)
    {
        printk(KERN_ERR "%s: udi_read 's size is error readSize:%d VS u32size:%d\n", __FUNCTION__, readSize, u32size);
        return (unsigned int)(BSP_RESET_ERROR);
    }
    if (1 == g_reset_assistant.iccore_reset)
    {
        if (CCORE_RESET_OK_FROM_CCORE == ireadvalue)
        {
            printk(KERN_INFO "%s: c tell me it's ok\n", __FUNCTION__);
            /*释放ｃ核启动成功信号量*/
            up(&(g_reset_assistant.sem_wait_ccorereset_ok));
        }
        else
        {
            printk(KERN_ERR "%s: fail to run c core!return %d\n", __FUNCTION__, ireadvalue);
            /*do nothing*/
            do_reset_system(RESET_TYPE_CRESET_CRUN_NO_OK);
        }
    }
    return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : drv_ccorereset_cbfun
 功能描述  : 底软在Modem单独复位时用于处理IPF,ICC, FILEAGENT,CSHELL, IFC相关数据。
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam, 表示复位前还是复位后调用
            　int userdata,用户数据．

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int drv_ccorereset_cbfun(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata)
{
    int     iresult = 0;

#ifdef _DRV_LLT_
#else

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        /*复位ICC通道*/
        BSP_ICC_ResetFun();

        /*调用处理IPF数据的函数*/
        BSP_IPF_SetControlFLagForCcoreReset(IPF_FORRESET_CONTROL_FORBID);
        /*清除c核ipc锁*/
        BSP_IPC_SemGive_Ccore_All();
    }
    else
    {
        BSP_IPF_SetControlFLagForCcoreReset(IPF_FORRESET_CONTROL_ALLOW);

        /*使能复位前关闭的中断*/
        finish_reset_sub();
    }
#endif

    /*调用FILEAGENT关闭句柄*/
    iresult = close_all_filehandle(eparam);
    if (0 != iresult)
    {
        printk(KERN_ERR "%s: drv_close file fail, return %d\n", __FUNCTION__, iresult);
        goto error_return;
    }

    /*调用处理CSHELL相关的函数*/
    iresult = set_for_cshell(eparam);
    if (0 != iresult)
    {
        printk(KERN_ERR "%s: drv_cshell fail, return %d\n", __FUNCTION__, iresult);
        goto error_return;
    }

    return iresult;
error_return:
    printk(KERN_ERR "%s: drv cb fun run fail, return = %d\n", __FUNCTION__, iresult);
    return BSP_RESET_ERROR;
}
/*****************************************************************************
 函 数 名  : reset_icc_open
 功能描述  : 打开icc
 输入参数  : 无

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int reset_icc_open(void)
{
    g_reset_assistant.attr.enChanMode  = ICC_CHAN_MODE_PACKET;
    g_reset_assistant.attr.u32Priority = 0;
    g_reset_assistant.attr.u32TimeOut  = 10000;
    g_reset_assistant.attr.event_cb    = NULL;
    g_reset_assistant.attr.read_cb     = ccorereset_icc_cok_notify;
    g_reset_assistant.attr.write_cb    = NULL;
    g_reset_assistant.attr.u32FIFOInSize  = 1024;
    g_reset_assistant.attr.u32FIFOOutSize = 1024;

    g_reset_assistant.ccorereset_IccParam.devid = UDI_ICC_GUOM7_ID;
    g_reset_assistant.ccorereset_IccParam.pPrivate = &(g_reset_assistant.attr);

    /*打开ICC通道*/
    g_reset_assistant.ccorereset_IccFd = udi_open(&(g_reset_assistant.ccorereset_IccParam));

    if (g_reset_assistant.ccorereset_IccFd <= 0)
    {
        printk(KERN_ERR "%s: in reset_icc_open ICC failed:[0x%x]\n", __FUNCTION__, g_reset_assistant.ccorereset_IccFd);

        return BSP_RESET_ERROR;
    }
    printk(KERN_INFO "%s: in reset_icc_open ICC SUCCESS:[0x%x]\n", __FUNCTION__, g_reset_assistant.ccorereset_IccFd);
    return BSP_RESET_OK;
}
int  set_for_cshell(DRV_RESET_CALLCBFUN_MOMENT eparam)
{
#ifdef _DRV_LLT_
#else
    if(DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        /*cshell invalid*/
        bsp_ccpu_rest_cshell_handle(CSHELL_INVALID);
    }
    else
    {
        bsp_ccpu_rest_cshell_handle(CSHELL_VALID);
    }
#endif
    return BSP_RESET_OK;
}
int  close_all_filehandle(DRV_RESET_CALLCBFUN_MOMENT eparam)
{
#ifdef _DRV_LLT_
#else
    if(DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        bsp_ccpu_rest_rfile_handle();
    }
    else
    {
        ;
    }
#endif
    return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : do_reset_system
 功能描述  : 用于复位系统
 输入参数  : int ireset_type,复位类型
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
void  do_reset_system(int ireset_type)
{
#ifdef _DRV_LLT_
#else

    systemError((int)BSP_MODU_DORESET, EXCH_S_DORESET, ireset_type, 0, 0);

#endif
}
/*****************************************************************************
 函 数 名  : reset_set_cpu_status
 功能描述  : 当hifi或者ccpu复位时，记下状态，用于mailbox拦击发向hifi  的mail.
 输入参数  : unsigned int iOff  1-不使能;0-关闭
             unsigned int iflag 标识cpu状态对应的偏移
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
void reset_set_cpu_status(unsigned int iOff, unsigned int iflag)
{
    if (1 == iOff)
    {
        g_reset_assistant.icpustatus = (g_reset_assistant.icpustatus) | iflag;
    }
    else
    {
        g_reset_assistant.icpustatus = (g_reset_assistant.icpustatus) & (~iflag);
    }
    printk(KERN_INFO "%s: reset_set_cpu_status, ioff = %d, iflag = %d\n", __FUNCTION__, iOff, iflag);
}

/*****************************************************************************
 函 数 名  : BSP_CPU_StateGet
 功能描述  : 提供给mailbox模块，用于获得相关cpu状态
 输入参数  : int CpuID, MCU, HIFI,CCPU
 输出参数  : 无
 返 回 值  : int,1:使能；0:不使能
*****************************************************************************/
int BSP_CPU_StateGet(int CpuID)
{
    unsigned int u32CpuStatusOffset = 0;

    switch (CpuID)
    {
    case MAILBOX_CPUID_HIFI:
        u32CpuStatusOffset = RESET_CPU_HIFI_STATUS_OFF;
        break;
    case MAILBOX_CPUID_CCPU:
        u32CpuStatusOffset = RESET_CPU_CCORE_STATUS_OFF;
        break;
    default:
        break;
    }

    return (g_reset_assistant.icpustatus & u32CpuStatusOffset) ? 0 : 1;
}

/*****************************************************************************
 函 数 名  : reset_ccore_up_semaphone
 功能描述  : 释放ccore reset信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void reset_ccore_up_semaphone(void)
{
#ifdef BSP_C_HIFI_RESET_ALONE_FEATURE
    up(&(g_reset_assistant.sem_wait_ccorereset));
    printk(KERN_INFO "%s: reset_ccore_up_semaphone\n", __FUNCTION__);
#endif
}

void reset_ccore_up_byhimself(void)
{
#ifdef BSP_C_HIFI_RESET_ALONE_FEATURE
    printk(KERN_INFO "%s: reset_ccore_up_byhimselfs\n", __FUNCTION__);
    BSP_CCPU_Reset_Byhimself(0);

#endif
}

/*****************************************************************************
 函 数 名  : reset_hifi_up_semaphone
 功能描述  : 释放hifi reset信号量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void reset_hifi_up_semaphone(void)
{
#ifdef BSP_C_HIFI_RESET_ALONE_FEATURE
    up(&(g_reset_assistant.sem_wait_hifireset));
    printk(KERN_INFO "%s: reset_hifi_up_semaphone\n", __FUNCTION__);
#endif
}

/*****************************************************************************
 函 数 名  : reset_clean_wdt_int
 功能描述  : 收到复位中断后，清理c核/hifi狗中断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void reset_clean_wdt_int(ereset_module emodule)
{
#ifdef _DRV_LLT_
#else
#ifdef BSP_C_HIFI_RESET_ALONE_FEATURE
    unsigned long sctrl_on  = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);

    switch (emodule)
    {
    case BSP_RESET_MODULE_CCORE:
        writel(0x10, SOC_AO_SCTRL_SC_INT_CLEAR_ADDR(sctrl_on));
        break;
    case BSP_RESET_MODULE_HIFI:
        writel(0x4, SOC_AO_SCTRL_SC_INT_CLEAR_ADDR(sctrl_on));
        break;
    default:
        break;
    }
#endif
    printk(KERN_INFO "%s: reset_clean_wdt_int %d\n", __FUNCTION__, emodule);
#endif
}

/*****************************************************************************
 函 数 名  : drv_hifireset_cbfun
 功能描述  : 底软在hifi单独复位时用于处理mailbox相关数据。
 输入参数  : DRV_RESET_CALLCBFUN_MOMENT eparam, 表示复位前还是复位后调用
            　int userdata,用户数据．

 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int drv_hifireset_cbfun(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata)
{
    int     iresult = 0;

#ifdef _DRV_LLT_
#else

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        printk(KERN_INFO"RESET LOG: reset mediaserver task! before\n");

        mach_call_usermodeshell("/system/etc/log/mediaserver_reset.sh" , 0);

        printk(KERN_INFO"RESET LOG: reset mediaserver task! after\n");
    }
    else
    {
    }

    printk(KERN_INFO"RESET LOG: HIFI cb fun %d run ok(%d)\n", eparam, iresult);

#endif

    return iresult;
}

/*************************************************************************
可维可测接口
*************************************************************************/

/*****************************************************************************
 函 数 名  : reset_no_ok_savelog
 功能描述  : 在调用回调函数时如果回调函数返回失败，则记录下模块名字，返回值
 输入参数  : char *pname,组件注册回调函数时注册的名字；
             int iresult,回调函数的返回值。
             ereset_module emodule, 复位的模块,ccore or hifi
 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int reset_no_ok_savelog(char *pname, int iresult, DRV_RESET_CALLCBFUN_MOMENT eparam, ereset_module emodule)
{
    int     iwrite = 0;
    int     ilen = 0;
    char    *psavelog = NULL;
    char    *ptime = (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam?"before":"after");
#ifdef PRINK_TO_FILE    /*如果实现了printk打印信息生成文件功能，则不需要该函数功能*/
    return BSP_RESET_OK;
#endif

    if (NULL == pname)
    {
        printk(KERN_ERR "[%s ]name is NULL, in savelog fun\n", __FUNCTION__);
        return BSP_RESET_ERROR;
    }

    psavelog = (char*)kmalloc(BSP_RESET_LOG_INFO_ITEM_LEN, GFP_KERNEL);
    if (NULL == psavelog)
    {
        printk(KERN_ERR "%s: fail to malloc, in savelog fun\n", __FUNCTION__);
        return BSP_RESET_ERROR;
    }
    memset((void*)psavelog, 0, BSP_RESET_LOG_INFO_ITEM_LEN);
    switch (emodule)
    {
    case BSP_RESET_MODULE_CCORE:
        sprintf(psavelog, "%s ccore reset, %s fail, return %d\n",ptime, pname, iresult);
        break;
    case BSP_RESET_MODULE_HIFI:
        sprintf(psavelog, "%s hifi reset, %s fail, return %d\n",ptime, pname, iresult);
        break;
    default:
        sprintf(psavelog, "valid module, %s fail, return %d\n",pname, iresult);
        printk(KERN_ERR "%s: module id %d invalid!!, in savelog fun\n", __FUNCTION__, emodule);
        break;

    }
    reset_for_savelog(psavelog);
    kfree(psavelog);
    psavelog = NULL;
    printk(KERN_INFO "%s: %s, iwrite/len %d/%d\n", __FUNCTION__, psavelog, iwrite, ilen);
    return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : reset_for_savelog
 功能描述  : 保存log
 输入参数  : char *pstr,log内容
 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
int reset_for_savelog(char *pstr)
{
    FILE   *pfh = NULL;
    int     iwrite = 0;
    int     ilen = 0;


#ifdef PRINK_TO_FILE    /*如果实现了printk打印信息生成文件功能，则不需要该函数功能*/
    return BSP_RESET_OK;
#endif
#ifdef _DRV_LLT_
#else
    if (NULL == pstr)
    {
        printk(KERN_ERR "%s: pstr is NULL, in savelog fun\n", __FUNCTION__);
        return BSP_RESET_ERROR;
    }
    pfh = BSP_fopen(BSP_RESET_LOG_FILE, "a");
    if (NULL == pfh)
    {
        printk(KERN_ERR "%s: no log file, create one\n", __FUNCTION__);
        pfh = BSP_fopen(BSP_RESET_LOG_FILE, "w");
    }
    if (NULL != pfh)
    {
        ilen = strlen(pstr);
        iwrite = BSP_fwrite((const void*)pstr,ilen, 1, pfh);
        if (iwrite < 1)
        {
            printk(KERN_ERR "%s: can not write all: %d / %d\n", __FUNCTION__, iwrite, ilen);
        }
        BSP_fclose(pfh);
        pfh = NULL;
        printk(KERN_INFO "%s: iwrite len %d\n", __FUNCTION__, ilen);
    }
#endif
    return BSP_RESET_OK;
}

/*****************************************************************************
 函 数 名  : reset_info_show
 功能描述  : 显示可维可测信息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
void reset_info_show(void)
{
    sreset_mgr_LLI  *phead = g_pmgr_ccorereset_data;

    while (NULL != phead)
    {
        printk(KERN_INFO "%s: name:%s cbfun:0x%8x data:%d priolevel:%d\n", __FUNCTION__, phead->cbfuninfo.name,
            (unsigned int)phead->cbfuninfo.cbfun, phead->cbfuninfo.userdata, phead->cbfuninfo.priolevel);
        phead = phead->pnext;
    }

    phead = g_pmgr_hifireset_data;
    while (NULL != phead)
    {
        printk(KERN_INFO "%s: hifi reset: name:%s cbfun:0x%8x data:%d priolevel:%d\n", __FUNCTION__, phead->cbfuninfo.name,
            (unsigned int)phead->cbfuninfo.cbfun, phead->cbfuninfo.userdata, phead->cbfuninfo.priolevel);
        phead = phead->pnext;
    }

    /*C核单独复位状态*/
    printk(KERN_INFO "%s: ccore reset task process %d phase\n", __FUNCTION__, CCORE_RESET_TASK_PHASE_GET());
}
/*测试用接口*/
#ifdef BSP_C_HIFI_RESET_ALONE_TESET_VALID
/*These functions are used for testing!!!only!!!, starts*/
extern int simulate_irq_c_freeze(void);
extern int simulate_irq_c_panic(void);
extern int simulate_irq_c_reset(void);
extern int simulate_irq_hifi_reset(void);
extern int simulate_irq_mcuwdt_reset(void);

#ifdef _DRV_LLT_
#else
extern BSP_S32 BSP_IPF_ST_101(BSP_U32 u32PacketNum);
#endif

void test_clean_mgr_ccore_link(void)
{
    sreset_mgr_LLI  *phead = g_pmgr_ccorereset_data;
    sreset_mgr_LLI  *ptail = g_pmgr_ccorereset_data;

    while (NULL != phead)
    {
        ptail = phead->pnext;
        kfree(phead);
        phead = ptail;
    }
    g_pmgr_ccorereset_data = NULL;
}
void test_clean_mgr_hifi_link(void)
{
    sreset_mgr_LLI  *phead = g_pmgr_hifireset_data;
    sreset_mgr_LLI  *ptail = g_pmgr_hifireset_data;

    while (NULL != phead)
    {
        ptail = phead->pnext;
        kfree(phead);
        phead = ptail;
    }
    g_pmgr_hifireset_data = NULL;
}

/*ends*/

/*****************************************************************************
 函 数 名  : reset_only_for_test
 功能描述  : 该函数只用于测试!!
 输入参数  : int iparam, 测试case:
             0,测试modem 狗复位
             1,测试modem 软件异常复位
             2,测试modem 正常复位
             3,测试hifi复位
             4,测试mcu狗复位
             5,测试底软在ccore复位时所做的处理，如ipf,icc,fileagent,cshell相应功能是否正确
 输出参数  : 无
 返 回 值  : int
        0, 成功，非0，失败
*****************************************************************************/
void reset_only_for_test(int iparam)
{
    int     iresult = 0;
#ifdef _DRV_LLT_
#else
    switch (iparam)
    {
    case 0:
        up(&(g_reset_assistant.sem_wait_hifi_msg));
        up(&(g_reset_assistant.sem_wait_mcu_msg));

        simulate_irq_c_freeze();
        break;
    case 1:
        up(&(g_reset_assistant.sem_wait_hifi_msg));
        up(&(g_reset_assistant.sem_wait_mcu_msg));

        simulate_irq_c_panic();
        break;
    case 2:
        up(&(g_reset_assistant.sem_wait_hifi_msg));
        up(&(g_reset_assistant.sem_wait_mcu_msg));

        simulate_irq_c_reset();
        break;
    case 3:
        simulate_irq_hifi_reset();
        break;
    case 4:
        simulate_irq_mcuwdt_reset();
        break;
    case 5:
        /*send ip*/
        iresult = BSP_IPF_ST_101(20);

        drv_ccorereset_cbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE, 0);
        /*send ip*/
        iresult = BSP_IPF_ST_101(20);
        break;
    case 6:
       reset_no_ok_savelog("drv", -2, 0, BSP_RESET_MODULE_HIFI);
       do_reset_system(RESET_TYPE_FOR_TEST);
        break;
    case 7:
        ccorereset_regcbfunc("drv", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL);
        ccorereset_regcbfunc("OAM", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL+1);
        ccorereset_regcbfunc("TTF", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL-1);
        ccorereset_regcbfunc("NAS", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL+1);

        break;
    case 8:
        hifireset_regcbfunc("OAM", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL+1);
        hifireset_regcbfunc("CODEC", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL+1);
        hifireset_regcbfunc("NAS", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL+1);


        break;
    case 9:
        test_clean_mgr_ccore_link();
        break;
    case 10:
        test_clean_mgr_hifi_link();
        break;
    case 11:
        ccorereset_runcbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE);
        ccorereset_runcbfun(DRV_RESET_CALLCBFUN_RESET_AFTER);
        break;
    case 12:
        hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_BEFORE);
        hifireset_runcbfun(DRV_RESET_CALLCBFUN_RESET_AFTER);

        break;
    case 13:
        up(&(g_reset_assistant.sem_wait_hifi_msg));

        break;
    case 14:
        up(&(g_reset_assistant.sem_wait_mcu_msg));
        break;
    case 15:
        up(&(g_reset_assistant.sem_wait_ccorereset_ok));
        break;
    case 16:
        up(&(g_reset_assistant.sem_wait_hifireset));
        break;
    case 17:
        break;
    default:
        break;
    }
#endif
}

#endif


/*Added by l00212112,functions for c reset alone are defined, ends*/
#ifdef BSP_C_HIFI_RESET_ALONE_FEATURE
/*****************************************************************************
 函 数 名  : reset_sub_mgr_init
 功能描述  : 用于C核,hifi单独复位机制的初始化,在reset_module_init中调用,用于创建信号量,创建任务等操作.
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
int reset_sub_mgr_init (void)
{
    struct task_struct    *pCCoreTask = NULL;
    struct task_struct    *pHifiTask = NULL;
    int     iret = BSP_RESET_OK;

    /*默认HIFI/CCPU使能*/
    reset_set_cpu_status(0, RESET_CPU_HIFI_STATUS_OFF);
    reset_set_cpu_status(0, RESET_CPU_CCORE_STATUS_OFF);

    /*创建需要的信号量*/

    printk(KERN_INFO "%s: enter\n", __FUNCTION__);
    memset(&g_stResetDebugInfo, 0, sizeof(sreset_debug_info));
    memset(&g_reset_assistant, 0, sizeof(sreset_mgr_assistant));
    sema_init(&(g_reset_assistant.sem_wait_ccorereset), SEM_EMPTY);
    sema_init(&(g_reset_assistant.sem_wait_hifireset), SEM_EMPTY);
    sema_init(&(g_reset_assistant.sem_wait_ccorereset_ok), SEM_EMPTY);
    sema_init(&(g_reset_assistant.sem_wait_hifi_msg), SEM_EMPTY);
    sema_init(&(g_reset_assistant.sem_wait_mcu_msg), SEM_EMPTY);
    sema_init(&(g_reset_assistant.sem_wait_mcu_msg_hifireset), SEM_EMPTY);

    /*创建C复位处理线程*/
    pCCoreTask = kthread_run(ccorereset_task,  NULL, "ccorereset_task");

    printk(KERN_INFO "%s: create ccorereset_task, return %p\n", __FUNCTION__, pCCoreTask);

    /*创建hifi复位处理线程*/
    pHifiTask = kthread_run(hifireset_task,  NULL, "hifireset_task");

    printk(KERN_INFO "%s: create hifireset_task, return %p\n", __FUNCTION__, pHifiTask);

    /*注册C核复位回调函数*/
    ccorereset_regcbfunc("DRV", drv_ccorereset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL);

    /*注册HIFI复位回调函数*/
    hifireset_regcbfunc("CODEC", drv_hifireset_cbfun, 0, BSP_DRV_CBFUN_PRIOLEVEL);

    /*注册C核复位回调函数*/
    reset_icc_open();

    ccorereset_enable_wdt_irq();
    /*注册ACPU与MCU之间的MAILBOX*/
    iret = mailbox_reg_msg_cb(MAILBOX_MAILCODE_MCU_TO_ACPU_CCORE_RESET_ID, mailbox_recfun_mcu, NULL);
    iret = mailbox_reg_msg_cb(MAILBOX_MAILCODE_MCU_TO_ACPU_HIFI_RESET_ID, mailbox_recfun_mcu_hifireset, NULL);
    printk(KERN_INFO"RESET LOG: LEAVE reset_sub_mgr_init0! iret = %d\n", iret);


    /*注册ACPU与HIFI之间的MAILBOX*/
    iret = mailbox_reg_msg_cb(MAILBOX_MAILCODE_HIFI_TO_ACPU_CCORE_RESET_ID, mailbox_recfun_hifi, NULL);

    printk(KERN_INFO "%s: leave, iret = %d\n", __FUNCTION__, iret);
    return BSP_RESET_OK;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

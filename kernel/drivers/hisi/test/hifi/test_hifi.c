/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_hifi.c
  版 本 号   : 初稿
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : hifi A核  linux平台板侧ST测试功能接口文件
  函数列表   :

  修改历史   :


******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/notifier.h>
#include <linux/proc_fs.h>
#include <linux/clk.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <asm/uaccess.h>
#include <linux/syscalls.h>

#include "drv_mailbox.h"
#include "drv_mailbox_gut.h"
#include "drv_mailbox_cfg.h"

#include "drv_mailbox_platform.h"
#include "drv_mailbox_debug.h"
#include "bsp_mailbox.h"
#include "hifidrvinterface.h"
#include "test_hifi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 可维可测信息中包含的C文件编号宏定义
*****************************************************************************/
#undef  _HIFI_FILE_
#define _HIFI_FILE_   "th"

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*****************************************************************************
 函 数 名  : test_send_encap_msg
 功能描述  : 给hifi发送封装的消息，用于事件驱动hifi执行任务
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    修改内容   : 新生成函数

*****************************************************************************/
int test_send_encap_msg(unsigned char  *buff, unsigned long len)
{
    int ret = OK;

    /*调用核间通信接口发送数据*/
    ret = mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_AUDIO, buff, len);
    if ( OK != ret )
    {
        printk("mailbox_send_msg error\n");
        return ERROR;
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : test_audioplayer_query
 功能描述  : 查询播放进度
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月14日
    修改内容   : 新生成函数

*****************************************************************************/
int test_audioplayer_time_query(void)
{
    int ret = OK;

    TEST_HIFI_MSG_STRU                stHifiMsg;
    AUDIO_PLAYER_QUERY_TIME_REQ_STRU  stQuery;
    unsigned long                     ulSize   = 0;
    unsigned char                    *pucBuff  = NULL;

    /* ap与hifi测试通道消息ID */
    stHifiMsg.usMsgId       = ID_AP_HIFI_TEST_CMD;
    stHifiMsg.ulSenderPid   = DSP_PID_AUDIO;
    stHifiMsg.ulReceiverPid = DSP_PID_AUDIO_RT;
    stHifiMsg.ulChannel     = DRV_MAILBOX_CHANNEL_AUDIO_CH;
    stHifiMsg.ulMsgLen      = sizeof(AUDIO_PLAYER_QUERY_TIME_REQ_STRU);

    /* Query消息构造 */
    stQuery.uhwMsgId        = ID_AP_AUDIO_PLAY_QUERY_TIME_REQ;

    ulSize = sizeof(TEST_HIFI_MSG_STRU) + stHifiMsg.ulMsgLen;


    /* 分配内核态内存 */
    pucBuff = kmalloc(ulSize, GFP_KERNEL);

    /* 内存copy */
    memcpy(pucBuff, &stHifiMsg, sizeof(TEST_HIFI_MSG_STRU));
    memcpy(pucBuff+sizeof(TEST_HIFI_MSG_STRU), &stQuery, sizeof(AUDIO_PLAYER_QUERY_TIME_REQ_STRU));

    /* 给hifi发测试消息 */
    ret = test_send_encap_msg(pucBuff,ulSize);

    if (NULL != pucBuff)
    {
        kfree(pucBuff);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : test_hifi_help
 功能描述  : show test function
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    修改内容   : 新生成函数

*****************************************************************************/
int test_hifi_help( void  )
{
    printk("test_audioplayer_time_query\n");
    printk("test_hifi_mail_reg\n");
    printk("test_hifi_pcm_open\n");
    return 0;
}

/*****************************************************************************
 函 数 名  : test_hifi_mail_handle
 功能描述  : 邮箱回调函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    修改内容   : 新生成函数

*****************************************************************************/
void test_hifi_handle_mail( void *usr_para, void *mail_handle, unsigned int mail_len  )
{
    int ret_mail = OK;
    unsigned int *pmail_value;
    unsigned char *mail_buff;       /* 邮箱数据接收的buff */

    printk("test_hifi_handle_mail\n");

    mail_buff = (unsigned char *)kmalloc(mail_len, GFP_ATOMIC);

    /* 将剩余内容copy透传到buff中 */
    ret_mail = mailbox_read_msg_data(mail_handle, (unsigned char*)mail_buff, (unsigned long *)&mail_len);

    pmail_value =(unsigned int *) mail_buff;
    if (NULL != pmail_value)
    {
        printk("mail reture value %x \n",*pmail_value);

    }


    if (NULL != mail_buff)
    {
        kfree(mail_buff);
    }

}

/*****************************************************************************
 函 数 名  : test_hifi_mail_reg
 功能描述  : 邮箱注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月25日
    修改内容   : 新生成函数

*****************************************************************************/
int test_hifi_mail_reg( void  )
{

    unsigned long RecvMailCode = MAILBOX_MAILCODE_CHANNEL(MAILBOX_CPUID_HIFI, MAILBOX_CPUID_ACPU, 0);

    printk("test_hifi_mail_reg %x\n", (unsigned int)RecvMailCode);

    /*注册双核通信处理函数*/
    mailbox_reg_msg_cb( RecvMailCode, (mb_msg_cb)test_hifi_handle_mail, NULL );

    return 0;
}

/*****************************************************************************
 函 数 名  : test_hifi_bit_read
 功能描述  : 按比特范围读取32位地址
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32             - 读取的内容
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    修改内容   : 新生成函数

*****************************************************************************/
void test_hifi_bit_read(
                unsigned int            Addr,
                unsigned int            StartBit,
                unsigned int            EndBit)
{
    unsigned int                          Content;
    unsigned int                          TmpMask;
    unsigned int                          TmpBit;

    Addr = (unsigned int)(ioremap(Addr, 4));

    /*参数异常时则读取所有32bit内容*/
    if ((EndBit < StartBit)
        || (StartBit > 31)
        || (EndBit > 31))
    {
        StartBit = 0;
        EndBit   = 31;
    }

    /*根据起始和结束比特生成掩码*/
    TmpBit        = 31 - EndBit;
    TmpMask       = 0xffffffff << TmpBit;
    TmpMask       = TmpMask >> ( StartBit + TmpBit );
    TmpMask       = TmpMask << StartBit;

    Content       = readl(Addr);
    Content      &= TmpMask;
    Content       = Content >> StartBit;

    printk("test_hifi_bit_read %x\n",Content);

}
/*****************************************************************************
 函 数 名  : test_hifi_bit_write
 功能描述  : 按比特范围写32位地址
 输入参数  : VOS_UINT32 uwAddr      - 待写入的地址
             VOS_UINT16 uhwStartBit - 写入的起始比特,0-31
             VOS_UINT16 uhwEndBit   - 写入的结束比特,uhwStartBit-31
             VOS_UINT32 uwContent   - 待写入的内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    修改内容   : 新生成函数

*****************************************************************************/
int test_hifi_bit_write(
                unsigned int              Addr,
                unsigned int              StartBit,
                unsigned int              EndBit,
                unsigned int              Content)
{
    unsigned int                          SetValue;
    unsigned int                          RegContent;
    unsigned int                          TmpMask;
    unsigned int                          TmpBit;

    Addr = (unsigned int)(ioremap(Addr, 4));

    /*其它参数异常时进行异常处理*/
    if ((EndBit < StartBit)
        || (StartBit > 31)
        || (EndBit > 31))
    {
        return -1;
    }

    /*根据待写入内容和起始比特信息，生成写寄存器的数据*/
    SetValue      = Content;
    SetValue      = SetValue << StartBit;

    /*根据起始和结束比特生成掩码*/
    TmpBit        = 31 - EndBit;
    TmpMask       = 0xffffffff << TmpBit;
    TmpMask       = TmpMask >> ( StartBit + TmpBit);
    TmpMask       = TmpMask << StartBit;

    /*先读取WBBP寄存器地址中的内容，再写入指定bit数据*/
    RegContent    = readl(Addr);
    RegContent   &= (~TmpMask);
    SetValue     &= TmpMask;
    writel((RegContent | SetValue),Addr);

    printk("test_hifi_bit_write %x\n",(RegContent | SetValue));
    return 0;
}

/*****************************************************************************
 函 数 名  : test_hifi_read
 功能描述  : 按比特范围读取32位地址
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32             - 读取的内容
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    修改内容   : 新生成函数

*****************************************************************************/
void test_hifi_read(unsigned int Addr)
{
    unsigned int                          Content;
    Addr = (unsigned int)(ioremap(Addr, 4));

    Content = readl(Addr);

    printk("test_hifi_read %x\n",Content);

}
/*****************************************************************************
 函 数 名  : test_hifi_write
 功能描述  :
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   :
    修改内容   : 新生成函数

*****************************************************************************/
int test_hifi_write(
                unsigned int              uwAddr,
                unsigned int              uwContent)
{
    uwAddr = (unsigned int)(ioremap(uwAddr, 4));

    writel(uwContent,uwAddr);

    printk("test_hifi_write %x\n",uwContent);
    return 0;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


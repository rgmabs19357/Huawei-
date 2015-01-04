/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_drv_mailbox.h
  版 本 号   : 初稿
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   : mailbox C核  vxWorks平台板侧测试功能接口头文件
  函数列表   :

 修改历史      :
  1.日    期   : 2012年11月20日
    修改内容   : 新生成函数

******************************************************************************/
#ifndef __TEST_DRV_MAILBOX_H__
#define __TEST_DRV_MAILBOX_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define TEST_MAILBOX_INIT_FLAG          (0x5aa55aa5)

#define TM_MAILBOX_BYTE_PER_KB          (1024)

#define Second_To_Millisecond           (1000)
 /*计算带宽的乘法上限*/
#define MAILBOX_BOARDST_BOUNDWIDTH_MUL_LIMIT   30

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

/*****************************************************************************
 实 体 名  : struct tm_mb_handle
 功能描述  : 板侧测试模块控制句柄
*****************************************************************************/
struct tm_mb_handle
{
    void *          mutex;
    unsigned long   init_flag;
};

/*****************************************************************************
 实 体 名  : struct tm_mb_cb
 功能描述  : 板侧测试的用户回调句柄
*****************************************************************************/
struct tm_mb_cb
{
    void *           finish_sema;
    void *           sync_sema;
    unsigned long    start_slice;       /*for calculate boundwidth*/
    unsigned long    end_slice;         /*for calculate boundwidth*/
    unsigned long    prob_slice;        /*for calculate latency*/
    unsigned long    back_slice;        /*for calculate latency*/
    unsigned long    msg_count;
    unsigned long    task_count;
    unsigned long    check_ret;
};

/*****************************************************************************
 实 体 名  : test_mailbox_send_proc_func
 功能描述  : 板侧测试的入口函数
*****************************************************************************/
typedef void (*test_mailbox_send_proc_func)(
                unsigned long mailcode,
                unsigned long recvcode,
                unsigned long sendsize,
                unsigned long msgnum,
                unsigned long delaytick,
                unsigned long delaynum,
                unsigned long trytimes,
                struct tm_mb_cb * cb);

/*****************************************************************************
 实 体 名  : struct test_mailbox_proc
 功能描述  : 板侧测试的任务入参结构体
*****************************************************************************/
struct test_mailbox_proc
{
    test_mailbox_send_proc_func proc_cb;
    unsigned long mail_code;
    unsigned long recv_code;
    unsigned long send_size;
    unsigned long msg_num;
    unsigned long delay_tick;
    unsigned long delay_num;
    unsigned long try_times;
    struct tm_mb_cb * mb_cb;
};


/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


extern unsigned long test_mailbox_msg_multi_send(
                unsigned long DstId,
                unsigned long CarrierID,
                unsigned long TaskNum,
                unsigned long MsgLen,
                unsigned long MsgNum,
                unsigned long Priority,
                unsigned long DelayTick,
                unsigned long DelayNum,
                unsigned long TryTimes
);

extern unsigned long test_mailbox_msg_multi_test(
                unsigned long DstId,
                unsigned long TaskNum,
                unsigned long MsgNum,
                unsigned long DelayNum);

extern unsigned long test_mailbox_msg_single_test(
                unsigned long DstId,
                unsigned long MsgLen,
                unsigned long MsgNum,
                unsigned long DelayNum);

extern void test_mailbox_msg_reg(unsigned long ChannelID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of test_drv_mailbox.h */


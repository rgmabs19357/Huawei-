/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hifi_lpp.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年8月2日
  最近修改   :
  功能描述   :hifi设备驱动,用于hifi low-power play
  函数列表   :
              hifi_misc_async_write
              hifi_misc_exit
              hifi_misc_handle_mail
              hifi_misc_init
              hifi_misc_ioctl
              hifi_misc_open
              hifi_misc_probe
              hifi_misc_proc_init
              hifi_misc_proc_read
              hifi_misc_receive_task
              hifi_misc_release
              hifi_misc_remove
              hifi_misc_sync_write
  修改历史   :
  1.日    期   : 2012年7月26日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <asm/memory.h>
#include <asm/types.h>
#include <asm/io.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#include <drv_mailbox_cfg.h>
#include <linux/errno.h>

#include <bsp_mailbox.h>
#include "audio_hifi.h"
#include "hifi_lpp.h"
#include <mntn/excDrv.h>

//systrace
#include <trace/trace_kernel.h>

#include <mach/util.h>				/* For mach_call_usermoduleshell*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* HIFI专用区 BASE ADDR 物理地址 */
unsigned char *g_hifi_priv_area = NULL;

DEFINE_SEMAPHORE(g_misc_sem);

/* hifi可维可测工作队列 */
hifi_mntn_work_stru      hifi_mntn_work;
struct workqueue_struct *hifi_misc_mntn_wq;

LIST_HEAD(recv_sync_work_queue_head);
LIST_HEAD(recv_proc_work_queue_head);

struct hifi_misc_priv{
    spinlock_t recv_sync_lock;
    spinlock_t recv_proc_lock;
    /* 写同步信号量 */
    struct semaphore sync_sem;
    /* proc读同步信号量 */
    wait_queue_head_t proc_waitq;
    int wait_flag;
    unsigned int sn;
    struct wake_lock hifi_misc_wakelock;
};
struct hifi_misc_priv g_misc_data;

/*****************************************************************************
 函 数 名  : hifi_misc_async_write
 功能描述  : Hifi MISC 设备异步发送接口，将异步消息发给Hifi，非阻塞接口
 输入参数  :
             unsigned char *arg  :需要下发的数据buff指针
             unsigned int len    :下发的数据长度
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_async_write(unsigned char *arg, unsigned int len)
{
    int ret =0;

    IN_FUNCTION;

    if ( arg==NULL )
    {
        loge("input arg is NULL\n");
        return ERROR;
    }

    logd("len=%d, arg=0x%X\n", len, arg);

    /*调用核间通信接口发送数据*/
    ret = mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, arg, len);
    if ( OK != ret )
    {
        loge("msg send to hifi fail,ret is %d\n", ret);
        return ERROR;
    }
    logd("SendMail ret=%d\n", ret);

    OUT_FUNCTION;

    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_sync_write
 功能描述  : Hifi MISC 设备同步发送接口，将同步消息发给Hifi，阻塞接口
 输入参数  :
             unsigned char  *buff  :需要下发的数据buff指针
             unsigned int len     :下发的数据长度
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_sync_write(unsigned char  *buff, unsigned int len)
{
    int ret =0;
    struct recv_request *recv;

    IN_FUNCTION;

    if ( buff == NULL )
    {
        loge("input arg is NULL\n");
        return ERROR;
    }

    logd("len=%d, buff=0x%x, msgID=0x%x", len, buff, *((int *)buff));

    ret = down_trylock(&g_misc_data.sync_sem);
    if (!ret){
        loge("some msg need to be cleaned enter\n");
        spin_lock_bh(&g_misc_data.recv_sync_lock);
        while(!list_empty(&recv_sync_work_queue_head)){
            recv = list_entry(recv_sync_work_queue_head.next, struct recv_request, recv_node);
            list_del(&recv->recv_node);
            kfree(recv->rev_msg.mail_buff);
            kfree(recv);
            recv = NULL;
        }
        spin_unlock_bh(&g_misc_data.recv_sync_lock);
        loge("some msg need to be cleaned exist\n");
    }
    /*调用核间通信接口发送数据，得到返回值ret*/
    ret = mailbox_send_msg(MAILBOX_MAILCODE_ACPU_TO_HIFI_MISC, buff, len);
    if ( OK != ret )
    {
        loge("msg send to hifi fail,ret is %d\n", ret);
        return ERROR;
    }
    logd("sendmail ret=%d\n", ret);

    logd("down_timeout B, mb_ret=%d\n", ret);

    /*等待同步信号量*/
    ret = down_timeout(&g_misc_data.sync_sem, msecs_to_jiffies(2000));

    logd("down_timeout L, down_ret=%d\n", ret);
    g_misc_data.sn++;
    if (unlikely(g_misc_data.sn & 0x10000000)){
        g_misc_data.sn = 0;
    }

    if (OK != ret )
    {
        loge("wait sem timeout!\n");
        return ERROR;
    }

    OUT_FUNCTION;

    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_handle_mail
 功能描述  : Hifi MISC 设备双核通信接收中断处理函数
            约定收到HIIF邮箱消息的首4个字节是MSGID
 输入参数  : void *usr_para             : 注册时传递的参数
             void *mail_handle          : 邮箱数据参数
             unsigned int mail_len      : 邮箱数据长度
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void hifi_misc_handle_mail( void *usr_para, void *mail_handle, unsigned int mail_len )
{
    unsigned long ret_mail          = 0;
    struct recv_request *recv;
    HIFI_CHN_CMD *cmd_para = NULL;


    IN_FUNCTION;



    if ( mail_handle == NULL )
    {
        loge("mail_handle is NULL\n");
        return ;
    }
    if ( mail_len <= SIZE_CMD_ID )
    {
        loge("mail_len is less than SIZE_CMD_ID(%d)\n", mail_len);
        return ;
    }
    logd("mail_len=%d\n", mail_len);

    recv = (struct recv_request *)kmalloc(sizeof(struct recv_request), GFP_ATOMIC);

    if (unlikely(!recv))
    {
        loge("kmalloc recv  fail\n");
    }

    /* 设定SIZE */
    recv->rev_msg.mail_buff_len = mail_len;

    /* 分配总的空间 */
    recv->rev_msg.mail_buff = (unsigned char *)kmalloc(SIZE_LIMIT_PARAM, GFP_ATOMIC);

    if (unlikely(!(recv->rev_msg.mail_buff)))
    {
        kfree(recv);
        loge("kmalloc maibuf fail \n");
    }

    /* 将剩余内容copy透传到buff中 */
    ret_mail = mailbox_read_msg_data(mail_handle, (unsigned char*)recv->rev_msg.mail_buff, (unsigned long *)&recv->rev_msg.mail_buff_len);
    if ((ret_mail != MAILBOX_OK) || (recv->rev_msg.mail_buff_len <= 0))
    {
        loge("Empty point or data length error! ret=0x%x, mail_size: %d\n", (unsigned int)ret_mail, recv->rev_msg.mail_buff_len);

        goto ERR;
    }

    logd("ret_mail=%d, mail_buff_len=%d, msgID=0x%x\n", ret_mail, recv->rev_msg.mail_buff_len,
        *((unsigned int *)(recv->rev_msg.mail_buff + mail_len - SIZE_CMD_ID)));

    if (recv->rev_msg.mail_buff_len > mail_len) {
        loge("ReadMailData mail_size(%d) > mail_len(%d)\n", recv->rev_msg.mail_buff_len, mail_len);

        goto ERR;
    }
         /* 约定，前4个字节是cmd_id */
    cmd_para   = (HIFI_CHN_CMD *)(recv->rev_msg.mail_buff + mail_len - SIZE_CMD_ID);
        /* 赋予不同的接收指针，由接收者释放分配空间 */
    if ((HIFI_CHN_SYNC_CMD == cmd_para->cmd_type) && (g_misc_data.sn == cmd_para->sn)) {
        wake_lock_timeout(&g_misc_data.hifi_misc_wakelock, HZ / 2);
        spin_lock_bh(&g_misc_data.recv_sync_lock);
        list_add_tail(&recv->recv_node, &recv_sync_work_queue_head);
        spin_unlock_bh(&g_misc_data.recv_sync_lock);
        up(&g_misc_data.sync_sem);
        goto OUT;
    } else if ((HIFI_CHN_READNOTICE_CMD == cmd_para->cmd_type) && (ACPU_TO_HIFI_ASYNC_CMD == cmd_para->sn)){
        wake_lock_timeout(&g_misc_data.hifi_misc_wakelock, HZ);
        spin_lock_bh(&g_misc_data.recv_proc_lock);
        list_add_tail(&recv->recv_node, &recv_proc_work_queue_head);
        g_misc_data.wait_flag++;
        spin_unlock_bh(&g_misc_data.recv_proc_lock);
        wake_up(&g_misc_data.proc_waitq);
        goto OUT;
    } else {
        loge("unknown msg comed from hifi \n");
        goto ERR;
    }

ERR:
    kfree(recv->rev_msg.mail_buff);
    kfree(recv);
OUT:
    OUT_FUNCTION;

    return ;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_input_param
 功能描述  : 获取用户空间入参，并转换为内核空间入参
 输入参数  : usr_para_size，用户空间入参SIZE
            usr_para_addr，用户空间入参地址
 输出参数  : krn_para_size，转换后的内核空间入参SIZE
            krn_para_addr，转换后的内核空间入参地址
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_get_input_param(unsigned int usr_para_size, void *usr_para_addr,
                        unsigned int *krn_para_size, void **krn_para_addr)
{
    void *para_in = NULL;
    unsigned int para_size_in = 0;

    IN_FUNCTION;

    /*获取arg入参*/
    para_size_in = usr_para_size + SIZE_CMD_ID;

    /* 限制分配空间 */
    if (para_size_in > SIZE_LIMIT_PARAM) {
        loge("para_size_in exceed LIMIT(%d/%d)\n", para_size_in, SIZE_LIMIT_PARAM);
        goto End;
    }

    para_in = kzalloc(para_size_in, GFP_KERNEL);
    if (NULL == para_in) {
        loge("kzalloc fail\n");
        goto End;
    }
    logd("kzalloc para_in=0x%x\n", para_in);

    if (NULL != usr_para_addr) {
        if (copy_from_user(para_in , usr_para_addr, usr_para_size)) {
            loge("copy_from_user fail\n");
            goto End;
        }
    } else {
        /*无数据源，仅kernel分配空间，不做处理*/
    }

    /* 设置出参 */
    *krn_para_size = para_size_in;
    *krn_para_addr = para_in;

    OUT_FUNCTION;

    return OK;
End:
    if (para_in != NULL) {
        kfree(para_in);
        para_in = NULL;
    }

    return ERROR;

}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_input_param_free
 功能描述  : 释放分配的内核空间
 输入参数  : krn_para_addr，待释放的内核空间地址
 输出参数  : 无
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void hifi_dsp_get_input_param_free(void **krn_para_addr)
{
    IN_FUNCTION;

    if (*krn_para_addr != NULL) {
        kfree(*krn_para_addr);
        *krn_para_addr = NULL;
    } else {
        loge("krn_para_addr to free is NULL\n");
    }

    OUT_FUNCTION;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_output_param
 功能描述  : 内核空间出参转换为用户空间出参
 输入参数  : krn_para_size，转换后的内核空间出参SIZE
            krn_para_addr，转换后的内核空间出参地址
 输出参数  : usr_para_size，用户空间出参SIZE
            usr_para_addr，用户空间出参地址
 返 回 值  : OK / ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月26日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_get_output_param(unsigned int krn_para_size, void *krn_para_addr,
                        unsigned int *usr_para_size, void *usr_para_addr)
{
    int ret         = 0;
    void *para_to = NULL;
    unsigned int para_n = 0;

    IN_FUNCTION;

    /* 入参判定 */
    if (NULL==krn_para_addr) {
        loge("krn_para_addr is NULL\n");
        return -EINVAL;
    }

    /* 入参判定 */
    if ((NULL==usr_para_addr) || (NULL==usr_para_size)) {
        loge("usr_size_p=0x%x, usr_addr=0x%x\n", (unsigned int)usr_para_size, (unsigned int)usr_para_addr);
        return -EINVAL;
    }

    logd("krn_size=%d, krn_addr=0x%x\n", krn_para_size, krn_para_addr);
    logd("usr_size=%d, usr_addr=0x%x\n", *usr_para_size, usr_para_addr);

    para_to = usr_para_addr;
    para_n = krn_para_size;
    if (para_n > SIZE_LIMIT_PARAM) {
        loge("para_n exceed limit (%d / %d)\n", para_n, SIZE_LIMIT_PARAM);
        return -EINVAL;
    }

    if (para_n > *usr_para_size) {
        loge("para_n exceed usr_size(%d / %d)\n", para_n, *usr_para_size);
        return -EINVAL;
    }

    /* Copy data from kernel space to user space
        to, from, n */
    ret = copy_to_user(para_to, krn_para_addr, para_n);
    if ( OK != ret )
    {
        loge("copy_to_user fail, ret is %d\n", ret);
        return ERROR;
    }

    *usr_para_size = para_n;

    OUT_FUNCTION;

    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_async_cmd
 功能描述  : Hifi MISC IOCTL异步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_async_cmd(unsigned long arg)
{
    int ret         = 0;
    struct misc_io_async_param param;
    void *para_krn_in = NULL;
    unsigned int para_krn_size_in = 0;
    HIFI_CHN_CMD *cmd_para = NULL;

    IN_FUNCTION;

    if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_async_param))) {
        loge("copy_from_user fail\n");
        return ERROR;
    }

    /*获取arg入参*/
    ret = hifi_dsp_get_input_param(param.para_size_in, param.para_in,
                        &para_krn_size_in, &para_krn_in);
    if (OK != ret) {
        loge("get ret=%d\n", ret);
        goto End;
    }
    /* add cmd id and sn  */
    cmd_para = (HIFI_CHN_CMD *)(para_krn_in+para_krn_size_in-SIZE_CMD_ID);
    cmd_para->cmd_type = HIFI_CHN_SYNC_CMD;
    cmd_para->sn = ACPU_TO_HIFI_ASYNC_CMD;

    /*邮箱发送至HIFI, 异步*/
    ret = hifi_misc_async_write(para_krn_in, para_krn_size_in);
    if (OK != ret) {
        loge("async_write ret=%d\n", ret);
        goto End2;
    }

End2:
    /*释放krn入参*/
    hifi_dsp_get_input_param_free(&para_krn_in);

End:
    logd("ret=%d\n", ret);

    OUT_FUNCTION;

    return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_sync_cmd
 功能描述  : Hifi MISC IOCTL同步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_sync_cmd(unsigned long arg)
{
    int ret         = 0;
    struct misc_io_sync_param param;
    void *para_krn_in = NULL;
    unsigned int para_krn_size_in = 0;
    HIFI_CHN_CMD *cmd_para = NULL;
    struct recv_request *recv;


    IN_FUNCTION;
    
    if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_sync_param))) {
        loge("copy_from_user fail\n");
        return ERROR;
    }

    logd("para_size_in=%d\n", param.para_size_in);

    /*获取arg入参*/
    ret = hifi_dsp_get_input_param(param.para_size_in, param.para_in,
                        &para_krn_size_in, &para_krn_in);
    if (OK != ret) {
        loge("get ret=%d\n", ret);
        goto End;
    }

    /* add cmd id and sn  */
    cmd_para = (HIFI_CHN_CMD *)(para_krn_in+para_krn_size_in-SIZE_CMD_ID);
    cmd_para->cmd_type = HIFI_CHN_SYNC_CMD;

    cmd_para->sn = g_misc_data.sn;

    /*邮箱发送至HIFI, 同步*/

    ret = hifi_misc_sync_write(para_krn_in, para_krn_size_in);
    if (OK != ret) {
        loge("hifi_misc_sync_write ret=%d\n", ret);
        goto End;
    }


    logd("hifi_misc_sync_write ret=%d\n", ret);

    /*将获得的rev_msg信息填充到出参arg*/
	spin_lock_bh(&g_misc_data.recv_sync_lock);

    if (!list_empty(&recv_sync_work_queue_head)){
        recv = list_entry(recv_sync_work_queue_head.next, struct recv_request, recv_node);
        ret = hifi_dsp_get_output_param(recv->rev_msg.mail_buff_len- SIZE_CMD_ID, recv->rev_msg.mail_buff,
                        &param.para_size_out, param.para_out);
        if (OK != ret) {
            loge("get_out ret=%d\n", ret);
        }

        list_del(&recv->recv_node);
	kfree(recv->rev_msg.mail_buff);
	kfree(recv);
        recv = NULL;
    }
    spin_unlock_bh(&g_misc_data.recv_sync_lock);

    if (copy_to_user((void*)arg, &param, sizeof(struct misc_io_sync_param))) {
        loge("copy_to_user fail\n");
        goto End;
    }

End:
    /*释放krn入参*/
    hifi_dsp_get_input_param_free(&para_krn_in);
    OUT_FUNCTION;

    return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_get_phys_cmd
 功能描述  : Hifi MISC IOCTL获取物理地址
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_get_phys_cmd(unsigned long arg)
{
    int ret         = OK;
    struct misc_io_get_phys_param param;

    IN_FUNCTION;

    if (copy_from_user(&param,(void*) arg, sizeof(struct misc_io_get_phys_param))) {
        loge("copy_from_user fail\n");
        return ERROR;
    }

    switch (param.flag)
    {
    case 0:
        param.phys_addr = (unsigned long)g_hifi_priv_area;
        logd("para->phys_addr=0x%x\n", param.phys_addr);
        break;

    default:
        ret = ERROR;
        loge("invalid flag=%d\n", param.flag);
        break;
    }

    if (copy_to_user((void*)arg, &param, sizeof(struct misc_io_get_phys_param))) {
        loge("copy_to_user fail\n");
        return ERROR;
    }

    OUT_FUNCTION;

    return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_senddata_sync_cmd
 功能描述  : Hifi MISC IOCTL发送数据同步命令处理函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_senddata_sync_cmd(unsigned long arg)
{
    /* this func is not used yet so close it*/
	loge("%s this cmd is not supported by now \n", __FUNCTION__);
    return -EBUSY;

}

/*****************************************************************************
 函 数 名  : hifi_dsp_test_cmd
 功能描述  : 测试函数
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月18日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_test_cmd(unsigned long arg)
{
    IN_FUNCTION;

    OUT_FUNCTION;

    return OK;


}

/*****************************************************************************
 函 数 名  : hifi_dsp_write_param
 功能描述  : 将用户态算法参数拷贝到HIFI中
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年10月24日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_write_param(unsigned long arg)
{
    int ret = OK;
    phys_addr_t hifi_phy_addr       = 0;
    void*       hifi_vir_addr       = NULL;
    phys_addr_t hifi_param_phy_addr = 0;
    void*       hifi_param_vir_addr = NULL;
    CARM_HIFI_DYN_ADDR_SHARE_STRU* hifi_addr = NULL;
    struct misc_io_sync_param *para = (struct misc_io_sync_param *)arg;

    IN_FUNCTION;

    hifi_phy_addr = (phys_addr_t)HIFI_SYS_MEM_ADDR;
    logd("hifi_phy_addr=0x%x\n", (unsigned int)hifi_phy_addr);
    hifi_vir_addr = (unsigned char*)ioremap(HIFI_SYS_MEM_ADDR, OFFSET_HIFI_PRIV);
    if (NULL == hifi_vir_addr) {
        loge("hifi_vir_addr ioremap fail\n");
        ret = ERROR;
        goto error1;
    }
    logd("hifi_vir_addr=0x%x\n", (unsigned int)hifi_vir_addr);

    hifi_addr = (CARM_HIFI_DYN_ADDR_SHARE_STRU*)hifi_vir_addr;
    hifi_param_phy_addr = (phys_addr_t)hifi_addr->uwReserved[0];
    logd("hifi_param_phy_addr = 0x%x\n", (unsigned int)hifi_param_phy_addr);
    hifi_param_vir_addr = (unsigned char*)ioremap(hifi_param_phy_addr, SIZE_PARAM_PRIV);
    if (NULL == hifi_param_vir_addr) {
        loge("hifi_param_vir_addr ioremap fail\n");
        ret = ERROR;
        goto error2;
    }
    logd("hifi_param_vir_addr = 0x%x\n", (unsigned int)hifi_param_vir_addr);

    logd("user addr = 0x%x, size = %d", para->para_in, para->para_size_in);
    ret = copy_from_user(hifi_param_vir_addr, para->para_in, para->para_size_in);
    if ( ret != 0) {
        loge("copy data to hifi error! ret = %d", ret);
    }

error1:
    if (hifi_vir_addr != NULL) {
        iounmap(hifi_vir_addr);
    }

error2:
    if (hifi_param_vir_addr != NULL) {
        iounmap(hifi_param_vir_addr);
    }

    put_user(ret, (int*)para->para_out);

    OUT_FUNCTION;
    return ret;
}

/*****************************************************************************
 函 数 名  : hifi_dsp_dump_hifi_cmd
 功能描述  : HIFI_MISC_IOCTL_DUMP_HIFI处理函数
             该函数读取HIFI在DDR上的数据 并拷贝至用户空间已分配的数据内存中
 输入参数  : unsigned long arg : ioctl的入参
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_dsp_dump_hifi_cmd(unsigned long arg)
{
    if(1 == himntn_hifi_resetlog)
    {
        /* 使用工作队列进行脚本调用. 使得脚本调用时具有root权限 */
        queue_work(hifi_misc_mntn_wq, &(hifi_mntn_work.work_stru));
    }
    
    return 0;
}

/*****************************************************************************
 函 数 名  : hifi_handle_mntn_work
 功能描述  : hifi处理可维可测工作任务
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年11月14日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static void hifi_handle_mntn_work(struct work_struct *work)
{
    /* 直接调用脚本完成功能 */
    mach_call_usermodeshell("/system/etc/log/hifi_freeze.sh" , 0);
}

/*****************************************************************************
 函 数 名  : hifi_misc_open
 功能描述  : Hifi MISC 设备打开操作
 输入参数  : struct inode *finode  :设备节点信息
             struct file *fd    :对应设备fd
 输出参数  : 无
 返 回 值  : 成功:OK 失败:BUSY
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_open(struct inode *finode, struct file *fd)
{
    IN_FUNCTION;

    OUT_FUNCTION;

    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_release
 功能描述  : Hifi MISC 设备不再使用时释放函数
 输入参数  : struct inode *finode  :设备节点信息
             struct file *fd    :对应设备fd
 输出参数  : 无
 返 回 值  : OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_release(struct inode *finode, struct file *fd)
{

    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_ioctl
 功能描述  : Hifi MISC 设备提供给上层与设备交互的控制通道接口
 输入参数  : struct file *fd  :对应fd
             unsigned int cmd   :cmd类型
             unsigned long arg  :上层传下来的buff地址
 输出参数  : 无
 返 回 值  : 成功:OK 失败:ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
long hifi_misc_ioctl(struct file *fd,
                             unsigned int cmd,
                             unsigned long arg)
{


    int ret                  = 0;

    IN_FUNCTION;
    logi("cmd=0x%x, arg=0x%x\n", cmd, arg);

    if ((void __user *)arg == NULL)
    {
        loge("Input buff is NULL\n");
        return ERROR;
    }

    /*cmd命令处理*/
    switch(cmd) {
        case HIFI_MISC_IOCTL_ASYNCMSG/*异步命令*/:
            trace_dot(ADSP,"2",0);
            ret = hifi_dsp_async_cmd(arg);
            trace_dot(ADSP,"3",0);
            break;

        case HIFI_MISC_IOCTL_SYNCMSG/*同步命令*/:
            trace_dot(ADSP,"4",0);
            ret = down_interruptible(&g_misc_sem);
            ret = hifi_dsp_sync_cmd(arg);
            up(&g_misc_sem);
            trace_dot(ADSP,"5",0);
            break;

        case HIFI_MISC_IOCTL_SENDDATA_SYNC/*发送接收数据*/:
            trace_dot(ADSP,"6",0);
            ret = down_interruptible(&g_misc_sem);
            ret = hifi_dsp_senddata_sync_cmd(arg); /*not used by now*/
            up(&g_misc_sem);
            trace_dot(ADSP,"7",0);
            break;

        case HIFI_MISC_IOCTL_GET_PHYS/*获取*/:
            trace_dot(ADSP,"8",0);
            ret = hifi_dsp_get_phys_cmd(arg);
            trace_dot(ADSP,"9",0);
            break;

        case HIFI_MISC_IOCTL_TEST/*测试接口*/:
            ret = hifi_dsp_test_cmd(arg);
            break;

        case HIFI_MISC_IOCTL_WRITE_PARAMS : /* write algo param to hifi*/
            ret = hifi_dsp_write_param(arg);
            break;
            
        case HIFI_MISC_IOCTL_DUMP_HIFI/*DUMP HIFI DDR MEMORY*/:
            ret = hifi_dsp_dump_hifi_cmd(arg);
            break;
            
        default:
            /*打印无该CMD类型*/
            ret = (int)ERROR;
            loge("Invalid CMD =0x%x\n", cmd);
            break;
    }

    OUT_FUNCTION;

    return (long)ret;
}

static int hifi_misc_mmap(struct file *file, struct vm_area_struct *vma)
{
    int ret = 0;
    unsigned long phys_page_addr = 0;

    IN_FUNCTION;

#if 1
    phys_page_addr = (unsigned long)g_hifi_priv_area >> PAGE_SHIFT;
#else
    phys_addr = virt_to_phys((void *)((unsigned long)g_hifi_priv_area)) >> PAGE_SHIFT;
#endif

    logd("vma=0x%x\n", vma);
    logd("siz=0x%x, vma->vm_start=0x%x, end=%x%x\n", vma->vm_end - vma->vm_start,
                            vma->vm_start, vma->vm_end);
    logd("phys_page_addr=0x%x\n", phys_page_addr);

    ret = remap_pfn_range(vma,
                    vma->vm_start,
                    phys_page_addr,
                    vma->vm_end - vma->vm_start,
                    PAGE_SHARED);
    if(ret != 0)
    {
        loge("remap_pfn_range ret=%d\n", ret);
        return ERROR;
    }

    OUT_FUNCTION;

    return ret;
}

/*****************************************************************************
 函 数 名  : hifi_misc_proc_read
 功能描述  : 用于将Hifi MISC 设备接收Hifi的消息/数据通过文件的方式递交给用户
             态
 输入参数  : char *pg   :系统自动填充的用以填充数据的buff，为系统申请的一页
             char**start  :指示读文件的起始位置，page的偏移量
             off_t off    :读文件时page的偏移，当*start存在时，
                           off会被系统忽略而认为*start就是off
             int count    :表示读多少字节
             int *eof     :读动作是否停止下发标志
             void *data   :保留为驱动内部使用
 输出参数  : 无
 返 回 值  : 尚未读取部分的长度,如果长度大于4K则返回ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_proc_read(char *pg,
                            char**start,
                            off_t off,
                            int count,
                            int *eof,
                            void *data)
{
    char *page_d = pg;
    int len = 0, ret = 0;
    struct recv_request *recv;

    IN_FUNCTION;

    /*等待读信号量*/

    ret = wait_event_interruptible(g_misc_data.proc_waitq, g_misc_data.wait_flag!=0);

    if (ret) {
        loge("wait_event_interruptible: wake up by signal\n");
        return -EBUSY;
    }

    logd("wait_event_interruptible\n");

    spin_lock_bh(&g_misc_data.recv_proc_lock);

    if (likely(g_misc_data.wait_flag > 0)) {
        g_misc_data.wait_flag--;
    }

    if (!list_empty(&recv_proc_work_queue_head)){
        recv = list_entry(recv_proc_work_queue_head.next, struct recv_request, recv_node);
        len = recv->rev_msg.mail_buff_len;

        if (unlikely(len >= PAGE_MAX_SIZE)){
            loge("buff size is over 4K\n");
            ret = (int)ERROR;
        } else {
            /*将数据写到page中*/
            memcpy(page_d, recv->rev_msg.mail_buff, recv->rev_msg.mail_buff_len-SIZE_CMD_ID);
            ret = len;
        }

        list_del(&recv->recv_node);
	kfree(recv->rev_msg.mail_buff);
	kfree(recv);
        recv = NULL;
    }

    spin_unlock_bh(&g_misc_data.recv_proc_lock);

#ifndef _DRV_LLT_
    *eof = 1;
#endif

    OUT_FUNCTION;

    return ret;
}

const struct file_operations hifi_misc_fops =
{
    .owner          = THIS_MODULE,
    .open           = hifi_misc_open,
    .release        = hifi_misc_release,
    .unlocked_ioctl = hifi_misc_ioctl,
    .mmap           = hifi_misc_mmap,
};

struct miscdevice hifi_misc_device =
{
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = "hifi_misc",
    .fops   = &hifi_misc_fops,
};

/*****************************************************************************
 函 数 名  : hifi_misc_proc_init
 功能描述  : proc文件初始化函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void hifi_misc_proc_init( void )
{
    struct proc_dir_entry * entry ;
    struct proc_dir_entry * hifi_misc_dir;

    hifi_misc_dir = proc_mkdir("hifidsp", NULL);
    if (hifi_misc_dir == NULL) {
        loge("Unable to create /proc/dsp directory\n");
        return ;
    }

    /* Creating read/write "status" entry */
    entry = create_proc_entry("hifi", 0777, hifi_misc_dir);
    if (entry == NULL) {
        remove_proc_entry("dsp", 0);
        loge("Unable to create /proc/hifidsp/hifi entry\n");
        return ;
    }
#ifndef _DRV_LLT_
    entry->read_proc = hifi_misc_proc_read;
#endif
}

/*****************************************************************************
 函 数 名  : hifi_misc_probe
 功能描述  : Hifi MISC设备探测注册函数
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : 成功:OK 失败:ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_probe (struct platform_device *pdev)
{
    int ret =0;


    IN_FUNCTION;

    ret = misc_register(&hifi_misc_device);
    if ( OK != ret )
    {
        loge("hifi misc device register fail,ERROR is %d\n", ret);
        return ERROR;
    }

    /*初始化接受信号量*/
    spin_lock_init(&g_misc_data.recv_sync_lock);
    spin_lock_init(&g_misc_data.recv_proc_lock);

    /*初始化同步信号量*/
    sema_init(&g_misc_data.sync_sem,0);
    /*初始化读文件信号量*/
    init_waitqueue_head(&g_misc_data.proc_waitq);
    g_misc_data.wait_flag = 0;
    g_misc_data.sn = 0;

    wake_lock_init(&g_misc_data.hifi_misc_wakelock,WAKE_LOCK_SUSPEND,"hifi_wakelock");

    /*初始化HIFI专用区*/
    g_hifi_priv_area = (unsigned char *)HIFI_PRIV_ADDR;
    logd("g_hifi_priv_area=0x%x\n", g_hifi_priv_area);

    /*注册双核通信处理函数*/
    ret = mailbox_reg_msg_cb( MAILBOX_MAILCODE_HIFI_TO_ACPU_MISC, ( mb_msg_cb)hifi_misc_handle_mail, NULL );
    if (OK != ret)
    {
        loge("hifi mailbox handle func register fail\n");
        goto Error;
    }

    
    /* 创建hifi可维可测队列 */
    hifi_misc_mntn_wq = create_singlethread_workqueue("hifi_misc_mntn_workqueue");
    INIT_WORK(&(hifi_mntn_work.work_stru), hifi_handle_mntn_work);


    /*注册proc文件*/
    hifi_misc_proc_init();

    OUT_FUNCTION;
    return OK;

Error:

    (void)misc_deregister(&hifi_misc_device);

    OUT_FUNCTION;
    return ERROR;
}

/*****************************************************************************
 函 数 名  : hifi_misc_remove
 功能描述  : Hifi MISC 设备移除
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int hifi_misc_remove(struct platform_device *pdev)
{
    IN_FUNCTION;

    /* misc deregister*/
    (void)misc_deregister(&hifi_misc_device);

    OUT_FUNCTION;

    return OK;
}


struct platform_driver hifi_misc_driver = {
    .driver =
    {
        .name  = "hifi_dsp_misc",
        .owner = THIS_MODULE,
    },
    .probe  = hifi_misc_probe,
    .remove = __devexit_p(hifi_misc_remove),
};

/*****************************************************************************
 函 数 名  : hifi_misc_init
 功能描述  : Hifi MISC driver注册到platform driver上
 输入参数  : void
 输出参数  : 无
 返 回 值  : 成功:OK 失败:ERROR
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int __init hifi_misc_init( void )
{
    int ret = 0;

    IN_FUNCTION;

    ret = platform_driver_register(&hifi_misc_driver);
    if(OK != ret)
    {
        loge("hifi driver register fail,ERROR is %d\n", ret);
        return ERROR;
    }

    OUT_FUNCTION;
    return OK;
}

/*****************************************************************************
 函 数 名  : hifi_misc_exit
 功能描述  : Hifi MISC driver从platform driver上去注册
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void __exit hifi_misc_exit( void )
{
    IN_FUNCTION;

    platform_driver_unregister(&hifi_misc_driver);

    OUT_FUNCTION;
}

module_init(hifi_misc_init);
module_exit(hifi_misc_exit);

MODULE_DESCRIPTION("hifi driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/netlink.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/netfilter.h>
#include <linux/spinlock.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <net/flow.h>
#include "drv_ipcm.h"

#define TFR     printk      /*trace function routine*/

static struct sock *thermal_nl = NULL;    /*模块内部全局的netlink套接字*/
static __u32  thermal_user_pid = 0;	 /*保存 应用发过来的pid号，用于后面的温保消息通知 */

enum
{
    THERMAL_NL_HIGH_POWEROFF =  NLMSG_MIN_TYPE,
    THERMAL_NL_LOW_POWEROFF
};

static DEFINE_MUTEX(thermal_nl_mutex);

static void thermal_nl_lock(void)
{
    mutex_lock(&thermal_nl_mutex);
}

static void thermal_nl_unlock(void)
{
    mutex_unlock(&thermal_nl_mutex);
}


/*****************************************************************************
 函 数 名  : thermal_nl_send_msg
 功能描述  : 向温保用户层发送数据
 输入参数  :  msg_type: 要发送的消息事件类型
              msg_data: 消息数据地址
             msg_len: 消息数据长度

 输出参数  : 成功返回0，失败返回错误号。
 返 回 值  :
*****************************************************************************/
int thermal_nl_send_msg(__u16 msg_type, char * msg_data, int msg_len)
{
    struct sk_buff *skb;
    struct nlmsghdr *nlh;

    if (!thermal_nl) {
        printk(KERN_ERR "thermal_nl not init.\n");
        return -1;
    }

  /* nlmsg_new 新申请一个socket buffer ，其大小为
        socket消息头大小+  netlink 消息头大小+ 用户消息大小*/
    skb = nlmsg_new(msg_len, GFP_KERNEL);
    if(!skb) {
        printk(KERN_ERR "thermal_nl_sendnlmsg:alloc_skb_1 error\n");
        return -1;
    }

    nlh = nlmsg_put(skb,0,0,msg_type,msg_len,0);   /*填充部分netlink消息头*/

    NETLINK_CB(skb).pid = 0;        /*描述发送者ID,内核为0*/
    NETLINK_CB(skb).dst_group = 0;

    if ((msg_data) && (msg_len)) {
        memcpy(NLMSG_DATA(nlh), msg_data, msg_len);/*填充用户区数据*/
    }

    /*如果用户pid纯在，发送单播消息，否则报错。*/
    if (thermal_user_pid) {
        return netlink_unicast(thermal_nl, skb, thermal_user_pid, MSG_DONTWAIT);
    } else {
        kfree_skb(skb);
        printk("error: thermal usr pid not init.\n");
    }
    return 0;
}

/*****************************************************************************
 函 数 名  : thermal_nl_rcv_msg
 功能描述  : 接收用户层传过来的netlink消息，并且记录用户的pid号码
 输入参数  : skb: 装载netlink数据的socket buffer
             nlh: netlink消息头指针地址

 输出参数  : 成功返回0，失败返回错误号。
 返 回 值  :
*****************************************************************************/
static int thermal_nl_rcv_msg(struct sk_buff *skb, struct nlmsghdr *nlh)
{
    TFR("thermal_nl_rcv_msg enter.\n");

    printk("nlmsg_len(%d) nlmsg_type(0x%x) nlmsg_flags(0x%x) nlmsg_seq(%d) nlmsg_pid(0x%x)\n",
    nlh->nlmsg_len, nlh->nlmsg_type, nlh->nlmsg_flags, nlh->nlmsg_seq, nlh->nlmsg_pid);

    /*保存用户thermal数据号*/
    thermal_user_pid = nlh->nlmsg_pid;

    if (nlh->nlmsg_len > 0) {
#if 0
        str_buf = kmalloc(nlh->nlmsg_len, GFP_KERNEL);
        memcpy(str_buf, NLMSG_DATA(nlh), nlh->nlmsg_len);
        str_buf[nlh->nlmsg_len - 1] = '\0';
        printk("Message received(%d):%s\n", nlh->nlmsg_pid, str_buf) ;
        kfree(str_buf);

        /*nlh->nlmsg_pid是发送者的用户进程ID,传递用于描述内核返回消息的发送对象*/
        if(!thermal_nl_send_msg("From kernel: hello user!", nlh->nlmsg_pid)){
            printk("thermal_nl_rcv_msg send fail. \n");
        }
#endif
    }

    TFR("thermal_nl_rcv_msg exit.\n");

    return 0;
}

/*
netlink是基于socket套接字实现的通讯，所以netlink接收到的原始数据是
socket数据类型，由struct sk_buff定义netlink_rcv_sk会解析sk_buff，通过
nlh = nlmsg_hdr(skb);
获取socket数据中的netlink的数据(由struct nlmsghdr定义)，
并传递给thermal_nl_rcv_msg()
*/

static void thermal_nl_rcv(struct sk_buff *skb)
{
    TFR("thermal_nl_rcv enter.skb(0x%x)\n", (unsigned int) skb);

    thermal_nl_lock();
    netlink_rcv_skb(skb, &thermal_nl_rcv_msg);
    thermal_nl_unlock();

    TFR("thermal_nl_rcv exit.\n");
}

void thermal_nl_ipc_handle(int data )
{
    __u16 msg_type = 0;

    printk("thermal_nl_ipc_handle: %d\n",data);
    switch (data)
    {
        case IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH:
            msg_type = THERMAL_NL_HIGH_POWEROFF;
            break;

        case IPC_ACPU_INT_SRC_MCU_THERMAL_LOW:
            msg_type = THERMAL_NL_LOW_POWEROFF;
            break;

        default:
            break;
    }

    if (msg_type)
        thermal_nl_send_msg(msg_type, 0, 0);
}

/*
1) .netlink_kernel_create 为 NETLINK_THERMAL协议创建了一个套接字。
2) &init_net 使用当前的网络命名空间。
3) thermal_nl_rcv 使用这个处理用户发送过来的soket数据。
*/
static int __init thermal_nl_init(void)
{
    int rv = 0;

    printk("thermal kernel netlink_init.\n");

    /*根据netlink协议号，创建一个netlink通道*/
    thermal_nl = netlink_kernel_create(&init_net, NETLINK_THERMAL, 0,
                     thermal_nl_rcv, NULL, THIS_MODULE);
    if (!thermal_nl) {
        printk(KERN_ERR "cannot initialize nfnetlink!\n");
        return -1;
    }

    /*注册A核接收m核的IPC中断服务程序*/
    BSP_IPC_IntConnect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH ,
                    (VOIDFUNCPTR)thermal_nl_ipc_handle, IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH);
    BSP_IPC_IntConnect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_MCU_THERMAL_LOW ,
                    (VOIDFUNCPTR)thermal_nl_ipc_handle, IPC_ACPU_INT_SRC_MCU_THERMAL_LOW);

    BSP_IPC_IntEnable ((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH);
    BSP_IPC_IntEnable ((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_MCU_THERMAL_LOW);

    return rv;
}


static void __exit thermal_nl_exit(void)
{
    printk("Removing thermal kernel NETLINK layer.\n");
    netlink_kernel_release(thermal_nl);
    return;
}

module_init(thermal_nl_init);
module_exit(thermal_nl_exit);
MODULE_AUTHOR("monan@huawei.com");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("hi6620 thermal netlink interface");


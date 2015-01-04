/*
 * net/ipv4/pwrtmg_aegis.c
 *
 * Copyright (C) 2013 Huawei Device Co.,Ltd.
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifdef CONFIG_AEGIS
#include <linux/cdev.h>
#include <net/netlink.h>
#include <linux/skbuff.h>
#include <linux/inetdevice.h>
#include <linux/if_arp.h>
#include <net/tcp.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "net/pwrtmg_aegis.h"


#define AEGIS_BUFF_SIZE          256
#define MAX_LONG_CNT             0x7FFFFFFF

#define AEGIS_PORT_BUFF_MAX      8
#define AEGIS_IP_BUFF_MAX        40
#define AEGIS_REG_BUFF_MAX       20

#define AEGIS_PID_INVALID        -1

#define AEGIS_RET_SUCCESS        0
#define AEGIS_RET_ERROR          -1

#ifndef NETLINK_AEGIS_PROTOCOL
#define NETLINK_AEGIS_PROTOCOL   21
#endif
/*
 * Kernel updates port Type.
 */
typedef enum
{
    AEGIS_PORT_NOTIFY_NON = 0,
    AEGIS_TCP_ADD_PORT,             /*indicates a new TCP port*/
    AEGIS_TCP_DEL_PORT,             /*indicates a TCP port has been deleted*/
    AEGIS_UDP_ADD_PORT,             /*indicates a new UDP port*/
    AEGIS_UDP_DEL_PORT,             /*indicates a UDP port has been deleted*/
} AEGIS_PORT_NOTIFY_FLAG;

/*
 * AEGIS NETLINK COMMUNICATION MESSAGE TYPE
 * Kernel space communicates with User space
 * So the communication message must have distinguishability.
 */
typedef enum
{
    AEGIS_NETLINK_NON = 0,                          /* No actuall means                                                       */
    AEGIS_NETLINK_TCP,                              /* User Space requests to kernel: only TCP ports update                   */
    AEGIS_NETLINK_UDP,                              /* User Space requests to kernel: only UDP ports update                   */
    AEGIS_NETLINK_TCP_UDP,                          /* User Space requests to kernel: both TCP and UDP ports update           */
    AEGIS_NETLINK_PORT_LISTEN,                      /* User Space requests to kernel: only TCP listen ports update            */
    AEGIS_NETLINK_REG,                              /* User Space notify READY message to kernel by register to kernel        */
    AEGIS_NETLINK_DEREG,                            /* User Space notify NOT READY message to kernel by deregister to kernel  */
    AEGIS_NETLINK_KER_REG_OK,                       /* Kernel Space Message Type: notify User Space registered                */
    AEGIS_NETLINK_KER_MSG_PORT,                     /* Kernel Space Message Type:notify ports to this module                  */
    AEGIS_NETLINK_KER_MSG_IP,                       /* Kernel Space Message Type:notify IP to this module                     */
    AEGIS_NETLINK_KER_MSG_NET_DEVICE_DOWN           /* Kernel Space Message Type:notify PPP0 device down state to this module */
} AEGIS_NETLINK_MESSAGE_TYPE;

/*
 * AEGIS DISCARD PACKET INFORMATION
 * This struct records discarded TCP and UDP packets number during a period of time
 */
typedef struct aegis_discard_pkt_info
{
    long discard_tcp_pkt_num;               /*discarded TCP packets number*/
    long discard_udp_pkt_num;               /*discarded UDP packets number*/
    long total_time;                        /*record duration time */
    int last_netdev_state;                  /*net device have NETDEV_UP and NETDEV_DOWN state*/
    struct timeval last_netdev_up_time;     /*record the time when net device is NETDEV_UP, so we can calculate duration time when net device is NETDEV_DOWN*/
} AEGIS_DIS_PACKET_INF_T;

static AEGIS_DIS_PACKET_INF_T aegis_dp_info;

/*
 * Aegis Netlink Socket File Descriptor
 */
static struct sock *aegis_nlfd = NULL;

/*
 * Client process ID saved when aegis_nlfd has a client.
 * This client must come from rild damon.
 */
static int aegis_rild_pid = AEGIS_PID_INVALID;

static char aegis_ip[AEGIS_IP_BUFF_MAX] = {0};

/*
 * User Space send port state to Kernel, saved in this variable.
 * So Kernel can filter the ports User Space wanted.
 */
static int aegis_notify_port_state = AEGIS_NETLINK_NON;

/*===========================================================================

FUNCTION aegis_notify

DESCRIPTION
  This function sends port and IP address to User Space through netlink socket.

DEPENDENCIES
  ptr: message to be send.
  len: message length.
  type: message type, see further definition in AEGIS_NETLINK_MESSAGE_TYPE.

RETURN VALUE
  int: -1 if error happens, 0 means success.

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_notify(const char* data, size_t data_size, AEGIS_NETLINK_MESSAGE_TYPE type)
{
    int ret = AEGIS_RET_ERROR;
    int size;
    unsigned char *old_tail;
    struct sk_buff *skb;
    struct nlmsghdr *nlh;
    char *data_ptr;

    if ( (NULL == data) || (data_size > AEGIS_BUFF_SIZE) )
    {
        return ret;
    }

    if ( (AEGIS_PID_INVALID == aegis_rild_pid) || (NULL == aegis_nlfd) )
    {
        return ret;
    }

    /*calculate total space needed, include data_size and struct nlmsghdr size*/
    size = NLMSG_SPACE(data_size);
    skb = alloc_skb(size, GFP_ATOMIC);
    if ( NULL == skb)
    {
        return ret;
    }

    old_tail = skb->tail;
    nlh = NLMSG_PUT(skb, 0, 0, type, size-sizeof(*nlh));/*fill in struct nlmsghdr*/
    data_ptr = NLMSG_DATA(nlh);/*get actually data buffer pointer*/
    memcpy(data_ptr, data, data_size);
    nlh->nlmsg_len = skb->tail - old_tail;

    /*send port or ip to User Space*/
    netlink_unicast(aegis_nlfd, skb, aegis_rild_pid, MSG_DONTWAIT);

    return AEGIS_RET_SUCCESS;

nlmsg_failure:
    ret = AEGIS_RET_ERROR;
    if( NULL != skb)
    {
        kfree_skb(skb);
    }
    return ret;
}

/*===========================================================================

FUNCTION aegis_check_notify_flag

DESCRIPTION
  This function checks if the port needs to be pass to User Space by port type.

DEPENDENCIES
  port_flag: port type

RETURN VALUE
  aegis_port_notify_flag: AEGIS_PORT_NOTIFY_NON means the port do not need to be passed. otherwise passes the port.

SIDE EFFECTS
  None

===========================================================================*/
static AEGIS_PORT_NOTIFY_FLAG aegis_check_notify_flag(AEGIS_PORT_NOTIFY_FLAG port_flag)
{
    if ( AEGIS_NETLINK_NON != aegis_notify_port_state )
    {
        return port_flag;
    }
    else
    {
        return AEGIS_PORT_NOTIFY_NON;
    }
}

/*===========================================================================

FUNCTION aegis_port_notify

DESCRIPTION
  This function passes port information to aegis_notify function and judges if it need to be passed

DEPENDENCIES
  port_flag: port type
  port: port value

RETURN VALUE
  AEGIS_RET_ERROR -1
  AEGIS_RET_SUCCESS  0

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_port_notify(AEGIS_PORT_NOTIFY_FLAG port_flag, uint16_t port)
{
    char notify_msg[AEGIS_PORT_BUFF_MAX];
    int len;
    int ret = AEGIS_RET_ERROR;

    if ( AEGIS_PORT_NOTIFY_NON == aegis_check_notify_flag(port_flag) )
    {
        return ret;
    }

    memset(notify_msg, 0, AEGIS_PORT_BUFF_MAX);
    len = snprintf(notify_msg, AEGIS_PORT_BUFF_MAX,"%d:%d",port_flag,port);
    if ( len < 0 )
    {
        return ret;
    }

    ret = aegis_notify(notify_msg, AEGIS_PORT_BUFF_MAX, AEGIS_NETLINK_KER_MSG_PORT);

    return ret;
}

/*===========================================================================

FUNCTION aegis_listen_port_add

DESCRIPTION
  This function is called in inet_hashtables.c and inet6_hashtables.c when a new listen port is generated.

DEPENDENCIES
  port: new port added

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void aegis_listen_port_add(uint16_t port)
{
    aegis_port_notify(AEGIS_TCP_ADD_PORT, port);
}
EXPORT_SYMBOL(aegis_listen_port_add);

/*===========================================================================

FUNCTION aegis_listen_port_delete

DESCRIPTION
  This function is called in inet_hashtables.c when a listen port is deleted.

DEPENDENCIES
  port: the port deleted

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void aegis_listen_port_delete(uint16_t port)
{
    aegis_port_notify(AEGIS_TCP_DEL_PORT, port);
}
EXPORT_SYMBOL(aegis_listen_port_delete);

/*===========================================================================

FUNCTION aegis_ip_notify

DESCRIPTION
  This function passes ip address to aegis_notify function and judges if it's the same

DEPENDENCIES
  ip_ptr: Ip address information

RETURN VALUE
  AEGIS_RET_ERROR -1
  AEGIS_RET_SUCCESS  0

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_ip_notify(const char * ip_ptr)
{
    int ptr_len;
    const char * ptr;
    int ret;

    if ( NULL == ip_ptr )
    {
        return AEGIS_RET_ERROR;
    }

    ptr = ip_ptr;
    ptr_len = strlen(ptr);

    if( ptr_len >= AEGIS_IP_BUFF_MAX)
    {
        return AEGIS_RET_ERROR;
    }
    ret = AEGIS_RET_SUCCESS;
    if ( 0 != strcmp(aegis_ip, ptr) )
    {
        strcpy(aegis_ip, ptr);
        ret = aegis_notify(ptr, AEGIS_IP_BUFF_MAX, AEGIS_NETLINK_KER_MSG_IP);
    }

    return ret;
}

/*===========================================================================

FUNCTION aegis_reg_ok_notify

DESCRIPTION
  This function replys User Space reg_ok message when received User Space registration message.

DEPENDENCIES
  None

RETURN VALUE
  AEGIS_RET_ERROR -1
  AEGIS_RET_SUCCESS  0

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_reg_ok_notify(void)
{
    int ret;
    char msg[AEGIS_REG_BUFF_MAX] = {0};

    strncpy(msg, "reg ok!", AEGIS_REG_BUFF_MAX);

    ret = aegis_notify(msg, AEGIS_REG_BUFF_MAX, AEGIS_NETLINK_KER_REG_OK);

    return ret;
}

/*===========================================================================

FUNCTION aegis_inetaddr_event

DESCRIPTION
  This function is called in inet_hashtables.c when a listen port is deleted.

DEPENDENCIES
  this: noted used.
  ev: indicates net device state, it can be neither NETDEV_UP or NETDEV_DOWN.
  ptr: points to in_ifaddr struct which stores net device related information.

RETURN VALUE
  int: NOTIFY_DONE means caller should not care.

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_inetaddr_event(struct notifier_block *pnb, unsigned long ev, void *ptr)
{
    struct timeval tv_down;
    long distance = 0;
    struct in_ifaddr *ifa;
    char ip_buff[AEGIS_BUFF_SIZE] = {0};
    __be32 ipaddr;

    if ( NULL == ptr )
    {
        return NOTIFY_DONE;
    }

    ifa = (struct in_ifaddr *)ptr;
    ipaddr = ifa->ifa_local;

    if ( 0 == net_eq(dev_net(ifa->ifa_dev->dev), &init_net) )
    {
        return NOTIFY_DONE;
    }

    if ( ARPHRD_PPP != ifa->ifa_dev->dev->type )
    {
        return NOTIFY_DONE;
    }

    snprintf(ip_buff, sizeof(ip_buff), "%d.%d.%d.%d",
            ipaddr & 0xff,
            ((ipaddr >> 8) & 0xff),
            ((ipaddr >> 16) & 0xff),
            ((ipaddr >> 24) & 0xff));

    switch ( ev )
    {
        case NETDEV_UP:
            pr_info("%s NETDEV_UP ipaddr:%s\n",__func__,ip_buff);
            do_gettimeofday(&(aegis_dp_info.last_netdev_up_time));
            aegis_dp_info.last_netdev_state = NETDEV_UP;
            aegis_ip_notify(ip_buff);
            break;

        case NETDEV_DOWN:
            pr_info("%s NETDEV_DOWN ipaddr:%s\n",__func__,ip_buff);
            do_gettimeofday(&tv_down);
            distance = tv_down.tv_sec - aegis_dp_info.last_netdev_up_time.tv_sec;
            aegis_dp_info.total_time += distance;
            aegis_dp_info.last_netdev_state = NETDEV_DOWN;
            break;

        default:
            pr_info("%s: do noting for [%s] Event: %lu\n",__func__, ifa->ifa_label, ev);
            break;
    }

    return NOTIFY_DONE;
}

static struct notifier_block aegis_inetaddr_notifier = {
    .notifier_call = aegis_inetaddr_event,
};
/*===========================================================================

FUNCTION aegis_receive

DESCRIPTION
  Callback function when netlink socket have movement.
  It receives User Space messages through netlink socket.
  It records netlink client sockets owner's pid and port notify type.

DEPENDENCIES
  skb: message received.

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void aegis_receive(struct sk_buff * skb)
{
    if ( NULL == skb )
    {
        return;
    }
    if ( skb->len >= NLMSG_HDRLEN )
    {
        struct nlmsghdr *nlh;
        nlh = (struct nlmsghdr *)skb->data;
        if ( (nlh->nlmsg_len >= NLMSG_HDRLEN) && (skb->len >= nlh->nlmsg_len) )
        {
            pr_info("%s nlh->nlmsg_type: %d\n",__func__,nlh->nlmsg_type);

            switch ( nlh->nlmsg_type )
            {
                case AEGIS_NETLINK_NON:
                case AEGIS_NETLINK_TCP:
                case AEGIS_NETLINK_UDP:
                case AEGIS_NETLINK_TCP_UDP:
                case AEGIS_NETLINK_PORT_LISTEN:
                    aegis_notify_port_state = nlh->nlmsg_type;
                    break;

                case AEGIS_NETLINK_REG:
                    aegis_rild_pid = nlh->nlmsg_pid;
                    aegis_reg_ok_notify();
                    break;

                 case AEGIS_NETLINK_DEREG:
                    aegis_rild_pid = AEGIS_PID_INVALID;
                    break;

                default:
                    pr_info("%s nlh->nlmsg_type: %d\n",__func__,nlh->nlmsg_type);
                    break;
            }
        }
    }
}

/*===========================================================================

FUNCTION aegis_tcp4_discard_pkt_increase

DESCRIPTION
  This function is called in tcp_ipv4.c when a TCP4 port is discarded.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void aegis_tcp4_discard_pkt_increase(void)
{
    aegis_dp_info.discard_tcp_pkt_num++;
    if( MAX_LONG_CNT == aegis_dp_info.discard_tcp_pkt_num )
    {
        aegis_dp_info.discard_tcp_pkt_num = 0;
    }
}
EXPORT_SYMBOL(aegis_tcp4_discard_pkt_increase);

/*===========================================================================

FUNCTION aegis_udp4_discard_pkt_increase

DESCRIPTION
  This function is called in udp.c when a UDP4 port is discarded.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void aegis_udp4_discard_pkt_increase(void)
{
    aegis_dp_info.discard_udp_pkt_num++;
    if( MAX_LONG_CNT == aegis_dp_info.discard_udp_pkt_num )
    {
        aegis_dp_info.discard_udp_pkt_num = 0;
    }
}
EXPORT_SYMBOL(aegis_udp4_discard_pkt_increase);

/*===========================================================================

FUNCTION discard_pkt_seq_open

DESCRIPTION
  This function is the open operation when User Space open "proc/net/pwrtmg_aegis_discard_packet_info".
  When User Space requires read proc/net/pwrtmg_aegis_discard_packet_info, It must calculate total time.

DEPENDENCIES
  inode: It stores proc file operation information
  file: It indicates while file to operate.

RETURN VALUE
  int: 0 means success, otherwise failure

SIDE EFFECTS
  None

===========================================================================*/
static int discard_pkt_seq_open(struct inode *inode, struct file *file)
{
    struct tcp_seq_afinfo *afinfo = NULL;
    int err;

    if ( (NULL == inode) || (NULL == file) )
    {
        return AEGIS_RET_ERROR;
    }

    afinfo = PDE(inode)->data;

    /*when last net device is down, so do not need to calculate time, but when last net device is up, calculate total time up to now*/
    if ( NETDEV_UP == aegis_dp_info.last_netdev_state )
    {
        struct timeval tv_current;
        long distance = 0;
        do_gettimeofday(&tv_current);/*get current time*/
        distance = tv_current.tv_sec - aegis_dp_info.last_netdev_up_time.tv_sec;
        aegis_dp_info.total_time += distance;
        aegis_dp_info.last_netdev_up_time = tv_current;
    }

    err = seq_open_net(inode, file, &afinfo->seq_ops, sizeof(struct seq_net_private));

    return err;
}

/*===========================================================================

FUNCTION discard_pkt_seq_start

DESCRIPTION
  This function shows whether kernel have more information to output when proc file is wanted by User Space

DEPENDENCIES
  seq: Current proc file operation information
  pos: File operation detailed location

RETURN VALUE
  void *: It indicates whether kernel have more information to output.
  SEQ_START_TOKEN means first in.
  &aegis_dp_info means more information to tell.
  NULL means nothing to tell.

SIDE EFFECTS
  None

===========================================================================*/
static void * discard_pkt_seq_start(struct seq_file *seq, loff_t *pos)
{
    if ( NULL == pos )
    {
        return NULL;
    }
    if ( 0 == *pos )
    {
        return SEQ_START_TOKEN;
    }
    else if ( (loff_t *)SEQ_START_TOKEN == pos )
    {
        return &aegis_dp_info;
    }
    return NULL;
}

/*===========================================================================

FUNCTION discard_pkt_seq_next

DESCRIPTION
  This function shows whether kernel have more information to output

DEPENDENCIES
  seq: Current proc file operation information
  v: File operation location
  pos: File operation detailed location

RETURN VALUE
  void *: It indicates whether kernel have more information to output.

SIDE EFFECTS
  None

===========================================================================*/
static void *discard_pkt_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
    if( (NULL == v)||(NULL == pos) )
    {
        return NULL;
    }
    ++*pos;
    if ( SEQ_START_TOKEN == v )
    {
        return &aegis_dp_info;
    }
    else
    {
        return NULL;
    }
}

/*===========================================================================

FUNCTION discard_pkt_seq_stop

DESCRIPTION
  This function ends the output process of kernel aegis discard packet information to proc file.

DEPENDENCIES
  seq: Current proc file operation information
  v: File operation location

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void discard_pkt_seq_stop(struct seq_file *seq, void *v)
{
    rcu_read_unlock();
}

/*===========================================================================

FUNCTION aegis_discard_pkt_register

DESCRIPTION
  This function create "pwrtmg_aegis_discard_packet_info" proc file node.

DEPENDENCIES
  net: It points proc file ascription
  afinfo: Struct contains proc file operation function

RETURN VALUE
  int: 0 means success, otherwise failure

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_discard_pkt_register(struct net *net, struct tcp_seq_afinfo *afinfo)
{
    int rc = AEGIS_RET_SUCCESS;
    struct proc_dir_entry *p;

    if( (NULL == net) || (NULL == afinfo) )
    {
        return AEGIS_RET_ERROR;
    }
    afinfo->seq_fops.open = discard_pkt_seq_open;
    afinfo->seq_fops.read = seq_read;
    afinfo->seq_fops.llseek = seq_lseek;
    afinfo->seq_fops.release = seq_release_net;

    afinfo->seq_ops.start = discard_pkt_seq_start;
    afinfo->seq_ops.next = discard_pkt_seq_next;
    afinfo->seq_ops.stop = discard_pkt_seq_stop;

    p = proc_create_data(afinfo->name, S_IRUGO, net->proc_net, &afinfo->seq_fops, afinfo);
    if ( NULL == p )
    {
        rc = -ENOMEM;
    }
    return rc;
}

/*===========================================================================

FUNCTION aegis_discard_pkt_unregister

DESCRIPTION
  This function destroyes "pwrtmg_aegis_discard_packet_info" proc file node.

DEPENDENCIES
  net: It points proc file ascription
  afinfo: It indicates proc file name which is to be deleted

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void aegis_discard_pkt_unregister(struct net *net, struct tcp_seq_afinfo *afinfo)
{
    if((NULL == net)||(NULL == afinfo))
    {
        return;
    }
    proc_net_remove(net, afinfo->name);
}

/*===========================================================================

FUNCTION discard_pkt_seq_show

DESCRIPTION
  This function export kernel aegis discard packet information to proc/net/pwrtmg_aegis_discard_packet_info

DEPENDENCIES
  seq: Current proc file operation information
  v: File operation location

RETURN VALUE
  int: 0 means succuess always

SIDE EFFECTS
  None

===========================================================================*/
static int discard_pkt_seq_show(struct seq_file *seq, void *v)
{
    if ( SEQ_START_TOKEN == v )
    {
        seq_puts(seq, "total_time tcp4_discard_pkt_num upd4_discard_pkt_num\n");
    }
    else
    {
        seq_printf(seq, "%10ld %20ld %20ld\n", aegis_dp_info.total_time, aegis_dp_info.discard_tcp_pkt_num, aegis_dp_info.discard_udp_pkt_num);
    }

    return AEGIS_RET_SUCCESS;
}

/*
 * aegis_discard_pkt_seq_afinfo
 * Proc file detailed information
 */
static struct tcp_seq_afinfo aegis_discard_pkt_seq_afinfo = {
    .name = "pwrtmg_aegis_discard_packet_info",
    .family = AF_INET,
    .seq_fops = {
        .owner = THIS_MODULE,
    },
    .seq_ops = {
        .show = discard_pkt_seq_show,
    },
};
/*===========================================================================

FUNCTION aegis_discard_pkt_proc_init

DESCRIPTION
  This function creates "pwrtmg_aegis_discard_packet_info" proc file.

DEPENDENCIES
  net: It points proc file ascription

RETURN VALUE
  int: 0 means success, otherwise failure

SIDE EFFECTS
  None

===========================================================================*/
static int __net_init aegis_discard_pkt_proc_init(struct net *net)
{
    return aegis_discard_pkt_register(net, &aegis_discard_pkt_seq_afinfo);
}

/*===========================================================================

FUNCTION aegis_discard_pkt_proc_exit

DESCRIPTION
  This function destroyes "pwrtmg_aegis_discard_packet_info" proc file.

DEPENDENCIES
  net: It points proc file ascription

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void __net_exit aegis_discard_pkt_proc_exit(struct net *net)
{
    aegis_discard_pkt_unregister(net, &aegis_discard_pkt_seq_afinfo);
}

/*
 * aegis_discard_pkt_ops
 * A pernet operations structure which has init and exit functions
 * that are called when aegis discard packet network namespace are created and
 * destroyed respectively.
 */
static struct pernet_operations aegis_discard_pkt_ops = {
    .init = aegis_discard_pkt_proc_init,
    .exit = aegis_discard_pkt_proc_exit,
};

/*===========================================================================

FUNCTION aegis_discard_pkt_init

DESCRIPTION
  This function register a network namespace subsystem of "aegis_discard_pkt_ops".

DEPENDENCIES
  None

RETURN VALUE
  int: 0 means success, otherwise failure

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_discard_pkt_init(void)
{
    return register_pernet_subsys(&aegis_discard_pkt_ops);
}

/*===========================================================================

FUNCTION aegis_discard_pkt_exit

DESCRIPTION
  This function unregister "aegis_discard_pkt_ops" network namespace subsystem.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void aegis_discard_pkt_exit(void)
{
    unregister_pernet_subsys(&aegis_discard_pkt_ops);
}

/*===========================================================================

FUNCTION aegis_init_discard_pkt_info

DESCRIPTION
  This function init aegis discard packet pernet subsystem and clear aegis_dp_info global variable.

DEPENDENCIES
  None

RETURN VALUE
  AEGIS_RET_ERROR -1
  AEGIS_RET_SUCCESS  0

SIDE EFFECTS
  None

===========================================================================*/
static int aegis_init_discard_pkt_info(void)
{
    aegis_dp_info.discard_tcp_pkt_num = 0;
    aegis_dp_info.discard_udp_pkt_num = 0;
    aegis_dp_info.last_netdev_state = NETDEV_DOWN;
    aegis_dp_info.total_time = 0;

    if ( AEGIS_RET_SUCCESS != aegis_discard_pkt_init() )
    {
        pr_info("aegis_discard_pkt_init error");
        aegis_discard_pkt_exit();
        return AEGIS_RET_ERROR;
    }

    return AEGIS_RET_SUCCESS;
}

/*===========================================================================

FUNCTION aegis_init

DESCRIPTION
  This function is module init function, it has three jobs to do.
  1: Init "pwrtmg_aegis_discard_packet_info" device.
  2: Create netlink socket to communicate with RIL Aegis Module.
  3: Register ip change callback function.

DEPENDENCIES
  None

RETURN VALUE
  AEGIS_RET_ERROR -1
  AEGIS_RET_SUCCESS  0

SIDE EFFECTS
  None

===========================================================================*/
static int __init aegis_init(void)
{
    aegis_init_discard_pkt_info();

    aegis_nlfd = netlink_kernel_create(&init_net, NETLINK_AEGIS_PROTOCOL, 0, aegis_receive, NULL, THIS_MODULE);
    if( NULL == aegis_nlfd )
    {
        pr_info("%s: error call netlink_kernel_create\n",__func__);
        return AEGIS_RET_ERROR;
    }

    register_inetaddr_notifier(&aegis_inetaddr_notifier);
    pr_info("%s: aegis init success!\n",__func__);
    return AEGIS_RET_SUCCESS;
}

/*===========================================================================

FUNCTION aegis_deinit

DESCRIPTION
  This function is module exit function, it releases netlink socket, and unregisters  ip notifier.

DEPENDENCIES
  None

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
static void __exit aegis_deinit(void)
{
    if ( (NULL != aegis_nlfd) && (NULL != aegis_nlfd->sk_socket) )
    {
        sock_release(aegis_nlfd->sk_socket);
        aegis_nlfd = NULL;
    }
    unregister_inetaddr_notifier(&aegis_inetaddr_notifier);

    aegis_discard_pkt_exit();
}

/*
 * Module init and exit call
 */
fs_initcall(aegis_init);
module_exit(aegis_deinit);

MODULE_LICENSE("GPL");
#endif //CONFIG_AEGIS

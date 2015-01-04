/* Kernel module to match running port */

#include <linux/module.h>
// We needn't to handle network operation currently,
// but we will use it for check port operation later.
//#include <linux/skbuff.h>
// For add the source to the kernel code, move the header file
// and modify the include directive
#include <linux/netfilter/xt_port.h>
//#include "xt_port.h"
#include <linux/netfilter/x_tables.h>

#include <net/inet_hashtables.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LiuDonghua");
MODULE_DESCRIPTION("Xtables: Port match");
MODULE_ALIAS("ipt_port");
MODULE_ALIAS("ip6t_port");

extern struct inet_hashinfo tcp_hashinfo;
extern struct net init_net;

static bool is_tcp_port_listening(unsigned short bind_port) {
    struct inet_hashinfo *hashinfo = &tcp_hashinfo;
    struct net *net  = &init_net;
    struct sock *sk;
    struct hlist_nulls_node *node;
    struct inet_listen_hashbucket *ilb =
            &hashinfo->listening_hash[inet_lhashfn(net, bind_port)];
    bool ret = false;

    spin_lock_bh(&ilb->lock);
    sk_nulls_for_each(sk, node, &ilb->head) {
        // print each socket info
        struct inet_sock *inet = inet_sk(sk);
        //inet_daddr - Foreign IPv4 addr
        __be32 my_inet_rcv_saddr = inet->inet_rcv_saddr;
        //inet_rcv_saddr - Bound local IPv4 addr
        __be32 my_inet_daddr = inet->inet_daddr;
        //inet_num - Local port
        __u16 my_inet_num = inet->inet_num;
        // print sock info
        printk("sk->sk_state: %d, sk->sk_bound_dev_if: %d, "
               "my_inet_rcv_saddr: %pI4, my_inet_daddr: %pI4, "
               "my_inet_num: %d\n",
               sk->sk_state, sk->sk_bound_dev_if, &my_inet_rcv_saddr,
               &my_inet_daddr, my_inet_num);
        if(sk->sk_state == TCP_LISTEN) {
            ret = true;
            break;
        }
    }
    spin_unlock_bh(&ilb->lock);
    printk("is_port_listening(%d) returns %d\n", bind_port, ret);
    return ret;
}

static int port_mt_check(const struct xt_mtchk_param *par)
{
    const struct xt_port_info *portinfo = par->matchinfo;
    printk("entered xt_port check!\n");

    /* Must specify no unknown invflags */
    return (portinfo->invflags & ~XT_PORT_INV_MASK) ? -EINVAL : 0;
}

static bool port_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
    const struct xt_port_info *portinfo = par->matchinfo;
    bool ret = false;
    u_int16_t port;
    printk("entered xt_port match!\n");
    printk("tcp_port_using: [%d:%d].\n",
           portinfo->tcp_port_using[0], portinfo->tcp_port_using[1]);

    for(port = portinfo->tcp_port_using[0];
        port <= portinfo->tcp_port_using[1]; port ++) {
        if(is_tcp_port_listening(port) ^
                !!(portinfo->invflags & XT_PORT_INV_TCP_PORT_USING)) {
            ret = true;
            break;
        }
    }
    printk("port_mt result: %d\n", ret);
    return ret;
}

static struct xt_match port_mt_reg __read_mostly = {
    .name       = "port",
    .revision   = 0,
    .family     = NFPROTO_UNSPEC,
    .checkentry = port_mt_check,
    .match      = port_mt,
    .matchsize  = sizeof(struct xt_port_info),
    .me         = THIS_MODULE,
};

static int __init port_mt_init(void)
{
    printk(KERN_ALERT "__init port_mt_init\n");
    return xt_register_match(&port_mt_reg);
}

static void __exit port_mt_exit(void)
{
    printk(KERN_ALERT " __exit port_mt_exit\n");
    xt_unregister_match(&port_mt_reg);
}

module_init(port_mt_init);
module_exit(port_mt_exit);


/*
 * INET     An implementation of the TCP/IP protocol suite for the LINUX
 *      operating system.  INET is implemented using the  BSD Socket
 *      interface as the means of communication with the user level.
 *
 *      "Ping" sockets
 *
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      2 of the License, or (at your option) any later version.
 *
 * Based on ipv4/ping.c code.
 *
 * Authors: Lorenzo Colitti (IPv6 support)
 *      Vasiliy Kulikov / Openwall (IPv4 implementation, for Linux 2.6),
 *      Pavel Kankovsky (IPv4 implementation, for Linux 2.4.32)
 *
 */

#include <net/addrconf.h>
#include <net/ipv6.h>
#include <net/ip6_route.h>
#include <net/protocol.h>
#include <net/udp.h>
#include <net/transp_v6.h>
#include <net/ping.h>
#include <linux/socket.h>
#include <net/icmp.h>


struct pingfakehdr6 {
    struct icmphdr icmph;
    struct iovec *iov;
    sa_family_t family;
    u32 wcheck;
};



#define ENABLE_SOCKET_DEBUG 1

int socket_debug = 0;

#define MAX_SOCK   256

typedef struct
{
    unsigned char  cnt;
    unsigned char  rsv[3];
    struct sock *sock[MAX_SOCK];
    struct mutex ping6_mutex;
}ping6_entity;

ping6_entity  ping6_table;

#define SOCKET_DBG(format, arg...) {                    \
    if (socket_debug == ENABLE_SOCKET_DEBUG)            \
        printk(format, ## arg);             \
}


int ping6_debug_switch(int dbgswitch)
{
     socket_debug = dbgswitch;

     SOCKET_DBG(KERN_ERR "[%s][%d] debug:%d\r\n "
       ,__FUNCTION__,__LINE__,dbgswitch);

     return 0;
}

static int ping6_init_sock(struct sock *sk)
{

     SOCKET_DBG(KERN_ERR "[%s][%d] enter\r\n "
       ,__FUNCTION__,__LINE__);

     return 0;
}

static void ping6_close(struct sock *sk, long timeout)
{
    struct inet_sock *isk;

    SOCKET_DBG(KERN_ERR "[%s][%d] enter\r\n "
      ,__FUNCTION__,__LINE__);


    mutex_lock(&ping6_table.ping6_mutex);
    isk = inet_sk(sk);

    if ((isk->inet_num <= MAX_SOCK) && (0 < isk->inet_num))
    {
        ping6_table.sock[isk->inet_num - 1] = NULL;
    }

    mutex_unlock(&ping6_table.ping6_mutex);

    sk_common_release(sk);
}

static void ping6_hash(struct sock *sk)
{
    pr_debug("ping6_hash(sk->port=%u)\n", inet_sk(sk)->inet_num);
    BUG(); /* "Please do not press this button again." */
}

static inline bool __ipv6_addr_needs_scope_id(int type)
{
    return type & IPV6_ADDR_LINKLOCAL ||
           (type & IPV6_ADDR_MULTICAST &&
        (type & (IPV6_ADDR_LOOPBACK|IPV6_ADDR_LINKLOCAL)));
}


static int ping6_getfrag(void *from, char * to,
            int offset, int fraglen, int odd, struct sk_buff *skb)
{
    struct pingfakehdr6 *pfh = (struct pingfakehdr6 *)from;

    if (offset == 0) {
        if (fraglen < sizeof(struct icmp6hdr))
            BUG();
        if (csum_partial_copy_fromiovecend(to + sizeof(struct icmphdr),
                pfh->iov, 0, fraglen - sizeof(struct icmphdr),
                &pfh->wcheck))
            return -EFAULT;

    }
    else
    {
        if (offset < sizeof(struct icmphdr))
            BUG();
        if (csum_partial_copy_fromiovecend
                (to, pfh->iov, offset - sizeof(struct icmphdr),
                 fraglen, &pfh->wcheck))
            return -EFAULT;
    }

    skb->csum = pfh->wcheck;
    skb->ip_summed = CHECKSUM_NONE;
    pfh->wcheck = 0;

    return 0;
}


static int ping6_push_pending_frames(struct sock *sk, struct flowi6 *fl6, struct icmp6hdr *thdr, int len)
{
    struct sk_buff *skb;
    struct icmp6hdr *icmp6h;
    int err = 0;

    if ((skb = skb_peek(&sk->sk_write_queue)) == NULL)
        goto out;

    icmp6h = icmp6_hdr(skb);
    memcpy(icmp6h, thdr, sizeof(struct icmp6hdr));
    icmp6h->icmp6_cksum = 0;

    if (skb_queue_len(&sk->sk_write_queue) == 1) {
        skb->csum = csum_partial(icmp6h,
                    sizeof(struct icmp6hdr), skb->csum);
        icmp6h->icmp6_cksum = csum_ipv6_magic(&fl6->saddr,
                              &fl6->daddr,
                              len, fl6->flowi6_proto,
                              skb->csum);
    } else {
        __wsum tmp_csum = 0;

        skb_queue_walk(&sk->sk_write_queue, skb) {
            tmp_csum = csum_add(tmp_csum, skb->csum);
        }

        tmp_csum = csum_partial(icmp6h,
                    sizeof(struct icmp6hdr), tmp_csum);
        icmp6h->icmp6_cksum = csum_ipv6_magic(&fl6->saddr,
                              &fl6->daddr,
                              len, fl6->flowi6_proto,
                              tmp_csum);
    }

    ip6_push_pending_frames(sk);
out:
    return err;
}


int ping6_sendmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,  size_t len)
{
    struct inet_sock *inet = inet_sk(sk);
    struct ipv6_pinfo *np = inet6_sk(sk);
    struct icmp6hdr user_icmph;
    int addr_type;
    struct in6_addr *daddr;
    int iif = 0;
    struct flowi6 fl6;
    int err;
    int hlimit;
    struct dst_entry *dst;
    struct rt6_info *rt;
    struct pingfakehdr6 pfh;


    SOCKET_DBG(KERN_ERR "[%s][%d] enter, len=%d\r\n "
      ,__FUNCTION__, __LINE__, len);

    if (memcpy_fromiovec(&user_icmph, msg->msg_iov, sizeof(user_icmph)))
            return -EFAULT;

    if (msg->msg_name) {
        struct sockaddr_in6 *u = (struct sockaddr_in6 *) msg->msg_name;
        if (msg->msg_namelen < sizeof(struct sockaddr_in6) ||
            u->sin6_family != AF_INET6) {

            SOCKET_DBG(KERN_ERR "line[%d] error [%d][%d] \r\n " , __LINE__, msg->msg_namelen, sizeof(struct sockaddr_in6));

            return -EINVAL;
        }
        if (sk->sk_bound_dev_if &&
            sk->sk_bound_dev_if != u->sin6_scope_id) {
            SOCKET_DBG(KERN_ERR "line[%d] error [%d][%d] \r\n " , __LINE__, sk->sk_bound_dev_if, u->sin6_scope_id);

            return -EINVAL;
        }
        daddr = &(u->sin6_addr);
        iif = u->sin6_scope_id;
    } else {
        if (sk->sk_state != TCP_ESTABLISHED)
            return -EDESTADDRREQ;
        daddr = &np->daddr;
    }

    if (!iif)
        iif = sk->sk_bound_dev_if;

#if 0
    addr_type = ipv6_addr_type(daddr);
    if (__ipv6_addr_needs_scope_id(addr_type) && !iif)
        return -EINVAL;
    if (addr_type & IPV6_ADDR_MAPPED)
        return -EINVAL;
#endif

    /* TODO: use ip6_datagram_send_ctl to get options from cmsg */

    memset(&fl6, 0, sizeof(fl6));

    fl6.flowi6_proto = IPPROTO_ICMPV6;
    fl6.saddr = np->saddr;
    fl6.daddr = *daddr;
    fl6.fl6_icmp_type = user_icmph.icmp6_type;
    fl6.fl6_icmp_code = user_icmph.icmp6_code;
    fl6.flowi6_oif    = sk->sk_bound_dev_if;
    security_sk_classify_flow(sk, flowi6_to_flowi(&fl6));

    if (!fl6.flowi6_oif && ipv6_addr_is_multicast(&fl6.daddr))
        fl6.flowi6_oif = np->mcast_oif;


    dst = ip6_sk_dst_lookup_flow(sk, &fl6,  daddr, 1);
    if (IS_ERR(dst))
        return PTR_ERR(dst);
    rt = (struct rt6_info *) dst;

    np = inet6_sk(sk);
    if (!np)
        return -EBADF;

    if (!fl6.flowi6_oif && ipv6_addr_is_multicast(&fl6.daddr))
        fl6.flowi6_oif = np->mcast_oif;


    pfh.icmph.type = user_icmph.icmp6_type;
    pfh.icmph.code = user_icmph.icmp6_code;
    pfh.icmph.checksum = 0;
    pfh.icmph.un.echo.id = inet->inet_sport;
    pfh.icmph.un.echo.sequence = user_icmph.icmp6_sequence;
    pfh.iov = msg->msg_iov;
    pfh.wcheck = 0;
    pfh.family = AF_INET6;

    if (ipv6_addr_is_multicast(&fl6.daddr))
        hlimit = np->mcast_hops;
    else
        hlimit = np->hop_limit;
    if (hlimit < 0)
        hlimit = ip6_dst_hoplimit(dst);

    err = ip6_append_data(sk, ping6_getfrag, &pfh, len,
                  0, hlimit,
                  np->tclass, NULL, &fl6, rt,
                  MSG_DONTWAIT, np->dontfrag);

    if (err) {
        ICMP6_INC_STATS_BH(sock_net(sk), rt->rt6i_idev,
                   ICMP6_MIB_OUTERRORS);
        ip6_flush_pending_frames(sk);
    } else {
        err = ping6_push_pending_frames(sk, &fl6,
                         (struct icmp6hdr *) &pfh.icmph,
                         len);
    }

    SOCKET_DBG(KERN_ERR "[%s][%d] exit err = %d\r\n "
      ,__FUNCTION__,__LINE__, err);

    return len;
    //return err;
}

int  ping6_recvmsg(struct kiocb *iocb, struct sock *sk, struct msghdr *msg,
          size_t len, int noblock, int flags, int *addr_len)
{
    struct inet_sock *isk = inet_sk(sk);
    struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)msg->msg_name;
    struct sk_buff *skb;
    int copied, err;

    SOCKET_DBG(KERN_ERR "[%s][%d] enter (sk=%p,sk->num=%u)\r\n "
      ,__FUNCTION__,__LINE__, isk, isk->inet_num);


    if (flags & MSG_OOB)
        goto out;

    if (addr_len)
        *addr_len = sizeof(*sin6);

    if (flags & MSG_ERRQUEUE)
        return ip_recv_error(sk, msg, len);

    skb = skb_recv_datagram(sk, flags, noblock, &err);
    if (!skb)
        goto out;

    copied = skb->len;
    if (copied > len) {
        msg->msg_flags |= MSG_TRUNC;
        copied = len;
    }

    /* Don't bother checking the checksum */
    err = skb_copy_datagram_iovec(skb, 0, msg->msg_iov, copied);
    if (err)
        goto done;

    sock_recv_timestamp(msg, sk, skb);

    /* Copy the address. */
    if (sin6) {
        struct ipv6_pinfo *np = inet6_sk(sk);
        struct ipv6hdr *ip6 = ipv6_hdr(skb);
        sin6 = (struct sockaddr_in6 *) msg->msg_name;
        sin6->sin6_family   = AF_INET6;
        sin6->sin6_flowinfo = 0;
        sin6->sin6_port     = 0;
        sin6->sin6_addr     = ip6->saddr;
        sin6->sin6_scope_id = 0;

        if (__ipv6_addr_needs_scope_id(
            ipv6_addr_type(&sin6->sin6_addr)))
            {
                sin6->sin6_scope_id = IP6CB(skb)->iif;
            }

        if (inet6_sk(sk)->rxopt.all)
            datagram_recv_ctl(sk, msg, skb);
    }
    if (isk->cmsg_flags)
        ip_cmsg_recv(msg, skb);

    err = copied;

done:
    skb_free_datagram(sk, skb);
out:
    pr_debug("ping_recvmsg -> %d\n", err);
    return err;

    return 0;
}

int  ping6_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
    SOCKET_DBG(KERN_ERR "[%s][%d] enter\r\n "
      ,__FUNCTION__,__LINE__);

    if (sock_queue_rcv_skb(sk, skb) < 0) {
        ICMP_INC_STATS_BH(sock_net(sk), ICMP_MIB_INERRORS);
        kfree_skb(skb);
        SOCKET_DBG(KERN_ERR "[%s][%d] ping6_queue_rcv_skb fail\r\n ");
        return -1;
    }

    return 0;
}

int  ping6_get_port(struct sock *sk, unsigned short ident)
{
    struct sock *sk2;
    struct inet_sock *isk = inet_sk(sk);
    int i = 0;

    mutex_lock(&ping6_table.ping6_mutex);

    if ( (isk->inet_num >=  MAX_SOCK) || (0 == isk->inet_num))
    {
        for (i = 0; i < MAX_SOCK; i++)
        {
            if (NULL == ping6_table.sock[ping6_table.cnt])
            {
                ping6_table.sock[ping6_table.cnt] = sk;
                isk->inet_num = (__u16)ping6_table.cnt + 1;
                ping6_table.cnt++;

                mutex_unlock(&ping6_table.ping6_mutex);

                return 0;
            }

            ping6_table.cnt++;
        }
    }
    else
    {
        sk2 = ping6_table.sock[isk->inet_num - 1];
        if (sk2 != sk)
        {
            return -1;
        }
    }

    mutex_unlock(&ping6_table.ping6_mutex);

    return -1;
}


int  ping6_bind(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
    SOCKET_DBG(KERN_ERR "[%s][%d] enter\r\n "
      ,__FUNCTION__,__LINE__);

    return 0;
}

static void ping6_unhash(struct sock *sk)
{
    SOCKET_DBG(KERN_ERR "[%s][%d] enter\r\n ", __FUNCTION__, __LINE__);
}


struct proto ping6_prot = {
    .name =     "PINGv6",
    .owner =    THIS_MODULE,
    .init =     ping6_init_sock,
    .close =    ping6_close,
    .connect =  ip6_datagram_connect,
    .disconnect =   udp_disconnect,
    .setsockopt =   ipv6_setsockopt,
    .getsockopt =   ipv6_getsockopt,
    .sendmsg =  ping6_sendmsg,
    .recvmsg =  ping6_recvmsg,
    .bind =     ping6_bind,
    .backlog_rcv =  ping6_queue_rcv_skb,
    .hash =     ping6_hash,
    .unhash =   ping6_unhash,
    .get_port = ping6_get_port,
    .obj_size = sizeof(struct raw6_sock),
};
EXPORT_SYMBOL_GPL(ping6_prot);

static struct inet_protosw pingv6_protosw = {
    .type =      SOCK_DGRAM,
    .protocol =  IPPROTO_ICMPV6,
    .prot =      &ping6_prot,
    .ops =       &inet6_dgram_ops,
    .no_check =  UDP_CSUM_DEFAULT,
    .flags =     INET_PROTOSW_REUSE,
};


struct sock *ping6_lookup(__u16 id)
{
    struct sock *sk = NULL;

    if ((id >  MAX_SOCK) || (0 == id))
    {
        return NULL;
    }

    sk = ping6_table.sock[id - 1];

    if (sk)
    {
        sock_hold(sk);
    }

    return sk;
}

void ping6_rcv(struct sk_buff *skb)
{
    struct sock *sk;
    struct net *net = dev_net(skb->dev);
    struct iphdr *iph = ip_hdr(skb);
    struct icmphdr *icmph = icmp_hdr(skb);
    u32 saddr = iph->saddr;
    u32 daddr = iph->daddr;

    SOCKET_DBG(KERN_ERR "[%s][%d] enter ping_rcv(skb=%p,id=%04x,seq=%04x)\r\n ",
        __FUNCTION__, __LINE__, skb, ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));

    /* We assume the packet has already been checked by icmp_rcv */

    pr_debug("ping_rcv(skb=%p,id=%04x,seq=%04x)\n",
        skb, ntohs(icmph->un.echo.id), ntohs(icmph->un.echo.sequence));

    /* Push ICMP header back */
    skb_push(skb, skb->data - (u8 *)icmph);

    sk = ping6_lookup(ntohs(icmph->un.echo.id));
    if (sk != NULL) {
        pr_debug("rcv on socket %p\n", sk);
        ping6_queue_rcv_skb(sk, skb_get(skb));
        sock_put(sk);
        return;
    }

    pr_debug("no socket, dropping\n");
}

int __init ping6_init(void)
{
    memset(&ping6_table, 0, sizeof(ping6_table));

    mutex_init(&ping6_table.ping6_mutex);

    return inet6_register_protosw(&pingv6_protosw);
}


/* This never gets called because it's not possible to unload the ipv6 module,
 * but just in case.
 */
void ping6_exit(void)
{
    inet6_unregister_protosw(&pingv6_protosw);
}


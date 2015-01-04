/*
 * INET		An implementation of the TCP/IP protocol suite for the LINUX
 *		operating system.  INET is implemented using the  BSD Socket
 *		interface as the means of communication with the user level.
 *
 *		Definitions for the "ping" module.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#ifndef _PING_H
#define _PING_H

#include <net/netns/hash.h>

/* PING_HTABLE_SIZE must be power of 2 */
#define PING_HTABLE_SIZE 	64
#define PING_HTABLE_MASK 	(PING_HTABLE_SIZE-1)

#define ping_portaddr_for_each_entry(__sk, node, list) \
	hlist_nulls_for_each_entry(__sk, node, list, sk_nulls_node)

/*
 * gid_t is either uint or ushort.  We want to pass it to
 * proc_dointvec_minmax(), so it must not be larger than MAX_INT
 */
#define GID_T_MAX (((gid_t)~0U) >> 1)

struct ping_table {
	struct hlist_nulls_head	hash[PING_HTABLE_SIZE];
	rwlock_t		lock;
};

struct ping_iter_state {
	struct seq_net_private  p;
	int			bucket;
};

extern struct proto ping_prot;

#ifdef CONFIG_IPV6
extern struct proto ping6_prot;
#endif

extern void ping_rcv(struct sk_buff *);
extern void ping_err(struct sk_buff *, u32 info);

#ifdef CONFIG_PROC_FS
extern int __init ping_proc_init(void);
extern void ping_proc_exit(void);
#endif

void __init ping_init(void);

#ifdef CONFIG_IPV6
int  __init ping6_init(void);
void ping6_exit(void);
#endif

#endif /* _PING_H */

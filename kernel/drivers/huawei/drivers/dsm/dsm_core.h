/**********************************************************
 * Filename:	dsm_core.h
 *
 * Discription: Huawei device state monitor head file
 *
 * Copyright: (C) 2014 huawei.
 *
 * Author: w00140597
 *
**********************************************************/

#ifndef _DSM_CORE_H
#define _DSM_CORE_H
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/mutex.h>
#include <linux/ioctl.h>
#include <linux/err.h>
#include "dsm_errno.h"

extern int debug_output;

#define DSM_LOG_DEBUG(format, ...)				\
	do {						\
		if (debug_output)			\
			 printk("[DSM] "format,## __VA_ARGS__);\
	} while (0)


#define DSM_LOG_INFO(format, ...)		printk("[DSM] "format,## __VA_ARGS__)
#define DSM_LOG_ERR(format, ...)		printk("[DSM] "format,## __VA_ARGS__)


#define CLIENT_NAME_LEN		(32)
#define CLIENT_SIZE			(32)
#define UINT_BUF_MAX        	(12)

#define CBUFF_OCCUPY_BIT	(0)
#define CBUFF_READY_BIT		(1)

#define DSM_CBUFF(client)	(client->dump_buff)
#define DSM_CBUFF_ERROR(client)	(client->error_no)

#define DSM_IOCTL_GET_CLIENT_COUNT	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF0, CLIENT_NAME_LEN)
#define DSM_IOCTL_BIND					_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF1, CLIENT_NAME_LEN)
#define DSM_IOCTL_POLL_CLIENT_STATE	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF2, CLIENT_NAME_LEN)
#define DSM_IOCTL_FORCE_DUMP			_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF3, CLIENT_NAME_LEN)
#define DSM_IOCTL_GET_CLIENT_ERROR	_IOC(_IOC_READ|_IOC_WRITE, 'x', 0xF4, CLIENT_NAME_LEN)

enum {
	DSM_CLIENT_NOTIFY_BIT = 0,
	DSM_CLIENT_VAILD_BIT = 31,
	DSM_CLIENT_NOTIFY = 1<<DSM_CLIENT_NOTIFY_BIT,
	DSM_CLIENT_VAILD = 1<<DSM_CLIENT_VAILD_BIT,
};

struct dsm_client_ops{
	int (*poll_state) (void);
	int (*dump_func) (int type, void *buff, int size);
};

struct dsm_dev{
	const char *name;
	struct dsm_client_ops *fops;
	size_t buff_size;
};

struct dsm_client{
	char client_name[CLIENT_NAME_LEN];
	int client_id;
	int error_no;
	unsigned long buff_flag;
	struct dsm_client_ops *cops;
	wait_queue_head_t waitq;
	size_t read_size;
	size_t used_size;
	size_t buff_size;
	u8 dump_buff[];
};

struct dsm_server{
	unsigned long client_flag[CLIENT_SIZE];
	struct dsm_client *client_list[CLIENT_SIZE];
	int client_count;
	struct workqueue_struct *dsm_wq;
	struct mutex mtx_lock;
};

#ifdef CONFIG_HUAWEI_DSM
struct dsm_client *dsm_register_client (struct dsm_dev *dev);
int dsm_client_ocuppy(struct dsm_client *client);
int dsm_client_record(struct dsm_client *client, const char *fmt, ...);
int dsm_client_copy(struct dsm_client *client, void *src, int sz);
void dsm_client_notify(struct dsm_client *client, int error_no);
#else
static inline struct dsm_client *dsm_register_client (struct dsm_dev *dev)
{
	return NULL;
}
static inline int dsm_client_ocuppy(struct dsm_client *client)
{
	return 1;
}
static inline int dsm_client_record(struct dsm_client *client, const char *fmt, ...)
{
	return 0;
}
static inline int dsm_client_copy(struct dsm_client *client, void *src, int sz)
{
	return 0;
}
static inline void dsm_client_notify(struct dsm_client *client, int error_no)
{
	return;
}
#endif

#endif

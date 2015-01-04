/*
 *  drivers/huawei/device/log_jank.c
 *
 *  Copyright (C) 2014 Huawei Technologies Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/aio.h>
#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/log_jank.h>

static int __write_jank_init(char*, char*);
static int __write_jank_null(char*, char*);
static int __write_jank_kernel(char*, char*);

static int (*write_jank)(char*, char*) = __write_jank_init;
static struct file* filp = NULL;
static char pr_buf[256];

static DEFINE_MUTEX(io_mutex);

static int __write_jank_init(char* tag, char* msg)
{
    mm_segment_t oldfs;

    oldfs = get_fs();
    set_fs(get_ds());

    filp = filp_open(LOG_JANK_FS, O_WRONLY, 0);

    set_fs(oldfs);

    if (IS_ERR(filp)) {
        pr_err("log_jank: failed to open %s: %ld\n", LOG_JANK_FS, PTR_ERR(filp));
        write_jank = __write_jank_null;
    } else {
        write_jank = __write_jank_kernel;
    }

    return write_jank(tag, msg);
}

static int __write_jank_null(char* tag, char* msg)
{
    return -1;
}

static int __write_jank_kernel(char* tag, char* msg)
{
    int prio = 3; // priority: DEBUG
    struct iovec vec[3];

    mm_segment_t oldfs;
    int ret;

    if (unlikely(!tag || !msg)) {
        pr_err("log_jank: invalid arguments\n");
        return -1;
    }

    if (IS_ERR(filp)) {
        pr_err("log_jank: file descriptor to %s is invalid: %ld\n", LOG_JANK_FS, PTR_ERR(filp));
        return -1;
    }

    // format: <priority:1><tag:N>\0<message:N>\0
    vec[0].iov_base = &prio;
    vec[0].iov_len  = 1;
    vec[1].iov_base = tag;
    vec[1].iov_len  = strlen(tag) + 1;
    vec[2].iov_base = msg;
    vec[2].iov_len  = strlen(msg) + 1;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_writev(filp, &vec[0], 3, &filp->f_pos);

    set_fs(oldfs);

    if (unlikely(ret < 0)) {
        pr_err("log_jank: failed to write %s\n", LOG_JANK_FS);
    }
    return ret;
}

int pr_jank(char* tag, const char* fmt, ...)
{
    va_list args;
    int len;

    mutex_lock(&io_mutex);

    va_start(args, fmt);
    vscnprintf(pr_buf, sizeof(pr_buf), fmt, args);
    va_end(args);

    len = write_jank(tag, pr_buf);

    mutex_unlock(&io_mutex);

    return len;
}

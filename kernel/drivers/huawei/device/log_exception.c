#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/log_exception.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/aio.h>
#include<linux/types.h>

/**
 *  tag: the tag of this command
 *  msg: concrete command string to write to /dev/log/exception
 *  return: on success return the bytes writed successfully, on error return -1
 *
*/
int log_to_exception(char* tag, char* msg)
{

    mm_segment_t oldfs;
    struct file *file;
    unsigned char * prio_err = "6";//ANDROID_ERROR
    int ret = 0;
    struct iovec vec[3];

    if(NULL == tag || NULL == msg)
    {
        pr_err("log_exception: the arguments invalidate\n");
        return -1;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    file = filp_open(LOG_EXCEPTION_FS,O_RDWR,0);

    if(!file || IS_ERR(file))
    {
        pr_err("log_exception: Failed to access /dev/log/exception\n");
        set_fs(oldfs);
        return -1;
    }

    vec[0].iov_base = prio_err;
    vec[0].iov_len = 1;
    vec[1].iov_base = tag;
    vec[1].iov_len = strlen(tag) + 1;
    vec[2].iov_base = msg;
    vec[2].iov_len = strlen(msg)+1;
    ret = vfs_writev(file, &vec[0], 3, &file->f_pos);
    if(ret < 0)
    {
        pr_err("log_exception: Failed to write to /dev/log/exception\n");
        filp_close(file, NULL);
        set_fs(oldfs);
        return -1;
    }

    filp_close(file, NULL);
    set_fs(oldfs);
    return ret;
}

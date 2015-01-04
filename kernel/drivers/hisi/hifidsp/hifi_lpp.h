/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hifi_misc.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年8月2日
  最近修改   :
  功能描述   : hifi_misc.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月2日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __HIFI_MISC_H__
#define __HIFI_MISC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*#define HIFI_MISC_NAME "hifi"*/

/* Debug info */
#define INFO_LEVEL   0
#define DEBUG_LEVEL  0
#define ERROR_LEVEL  1
#define PAGE_MAX_SIZE        0x1000

#ifndef OK
#define OK           0
#endif
#define ERROR       (-1)
#define BUSY        (-2)
#define NOMEM       (-3)
#define INVAILD     (-4)

/* IOCTL入参和出参的SIZE限制 */
#define SIZE_LIMIT_PARAM        (256)

/* HIFI专用区 */
#define OFFSET_HIFI_PRIV        (0x00300000)
#define SIZE_HIFI_PRIV          (0x00500000)
#define HIFI_PRIV_ADDR          (HIFI_SYS_MEM_ADDR + OFFSET_HIFI_PRIV)
#define SIZE_PARAM_PRIV         (100 * 1024)

/* 接收HIFI消息，前部cmd_id占用的字节数 */

#define SIZE_CMD_ID        (8)

/* notice主动上报一次缓冲 */
#define REV_MSG_NOTICE_ID_MAX       2

#define ACPU_TO_HIFI_ASYNC_CMD    0xFFFFFFFF

#define BUFFER_NUM  8

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum{
    HIFI_CLOSE,
    HIFI_OPENED,
}HIFI_STATUS;


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/

/*处理hifi回复消息，记录cmd_id和数据*/
typedef struct
{
    unsigned char *mail_buff;       /* 邮箱数据接收的buff */
    unsigned int mail_buff_len;
    unsigned int cmd_id;            /* 邮箱接收数据前4个字节是cmd_id */
    unsigned char *out_buff_ptr;    /* 指向mail_buff cmd_id后的位置 */
    unsigned int out_buff_len;
} rev_msg_buff;

/* hifi可维可测工作结构 */
typedef struct
{
    unsigned int        work_id;
    struct work_struct  work_stru;
} hifi_mntn_work_stru;


struct recv_request{
    struct list_head recv_node;
    rev_msg_buff rev_msg;
};



/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
#ifndef LOG_TAG
#define LOG_TAG "hifi_misc "
#endif

#if INFO_LEVEL
#define logi(fmt, ...) pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logi(fmt, ...)
#endif

#if DEBUG_LEVEL
#define logd(fmt, ...) pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define logd(fmt, ...)
#endif

#if ERROR_LEVEL
#define loge(fmt, ...) pr_info(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define loge(fmt, ...)
#endif

#define IN_FUNCTION   logd("Begin\n");
#define OUT_FUNCTION  logd("End\n");

/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
int hifi_misc_async_write(unsigned char *arg, unsigned int len);
void __exit hifi_misc_exit( void );
void hifi_misc_handle_mail( void *usr_para, void *mail_handle, unsigned int mail_len );
int __init hifi_misc_init( void );
long hifi_misc_ioctl(struct file *fd,
                                    unsigned int cmd,
                                    unsigned long arg);
int hifi_misc_open(struct inode *finode, struct file *fd);
int hifi_misc_probe (struct platform_device *pdev);
void hifi_misc_proc_init( void );
int hifi_misc_proc_read(char *pg,
                                   char**start,
                                   off_t off,
                                   int count,
                                   int *eof,
                                   void *data);
void hifi_misc_receive_task_sync(void);
void hifi_misc_receive_task_proc(void);
int hifi_misc_release(struct inode *finode, struct file *fd);
int hifi_misc_remove(struct platform_device *pdev);
int hifi_misc_sync_write(unsigned char  *arg, unsigned int len);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hifi_misc.h */

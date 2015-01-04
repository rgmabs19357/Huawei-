/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : acm_ncopy_io.c
  版 本 号   : 初稿
  作    者   : 周明发 00145324
  生成日期   : 2013年4月15日
  最近修改   :
  功能描述   : 用于ACM零拷贝IO接口
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 创建文件

*******************************************************************************/

/*******************************************************************************
  1 头文件包含
*******************************************************************************/
#include <linux/serial_core.h>
#include <linux/syscalls.h>
#include <linux/dma-mapping.h>
#include <u_serial.h>
#include <asm/cacheflush.h>
#include "acm_ncopy_io.h"
#include "bsp_udi_adp.h"
#include <mach/ddr_map.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*******************************************************************************
  2 全局变量定义
*******************************************************************************/
struct acm_ncopy_ctx g_acm_ncpy[USB_ACM_COM_UDI_NUM] = {{0}};
int g_acm_ncpy_dbg_lev = 3;  /* KERN_ERR */

/*******************************************************************************
  3 函数声明
*******************************************************************************/
#define ACM_NCPY_ERR(args,...) do {\
    if (3 <= g_acm_ncpy_dbg_lev) {\
        printk("%s:%d:", __func__, __LINE__);\
        printk(args, ##__VA_ARGS__);\
    }\
}while(0)

#define ACM_NCPY_DBG(args,...) do {\
    if (7 <= g_acm_ncpy_dbg_lev) {\
        printk("%s:%d:", __func__, __LINE__);\
        printk(args, ##__VA_ARGS__);\
    }\
}while(0)

#define ACM_NCPY_STATS_INCR(ctx, stats_info) do {\
    spin_lock_irqsave(&ctx->tx_lock,flags);\
    (ctx->stats_info)++;\
    spin_unlock_irqrestore(&ctx->tx_lock,flags);\
}while(0)

STATIC struct usb_request * acm_ncopy_alloc_one_request(gfp_t gfp_flags);
STATIC void acm_ncopy_free_one_request(struct usb_request *req);
STATIC int acm_ncopy_alloc_requests(struct list_head *head,
            void (*fn)(struct usb_ep *, struct usb_request *), int *allocated);
STATIC void acm_ncopy_free_requests(struct list_head *head, int *allocated);
STATIC int  acm_ncopy_queue(struct acm_ncopy_ctx * acm_ncopy, unsigned char *buf,
        unsigned int size);
STATIC void acm_ncopy_tx_task(unsigned long arg);
STATIC void acm_ncopy_tx_complete(struct usb_ep *ep, struct usb_request *req);
/*******************************************************************************
  4 函数实现
*******************************************************************************/

/*****************************************************************************
 函 数 名  : acm_ncopy_init
 功能描述  : acm零拷贝初始化接口
 输入参数  : acm_dev : 对应acm对象设备
 输出参数  : 无
 返 回 值  : NCPY_OK 初始化成功，NCPY_ERROR 初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_init(int acm_dev)
{
    struct acm_ctx *acm = (struct acm_ctx *)acm_dev;
    struct acm_ncopy_ctx *acm_ncpy = NULL;
    long rc = 0;
    int i = 0;

    if (!acm) {
        ACM_NCPY_ERR("device is not invalid\n");
        return NCPY_ERROR;
    }

    ACM_NCPY_DBG("acm[%s] tty[0x%x] enter\n", acm->tty_name, (unsigned int)acm->tty);

    for (i = 0; i < USB_ACM_COM_UDI_NUM; i++) {
        if (!g_acm_ncpy[i].acm || (acm == g_acm_ncpy[i].acm)) {
            acm_ncpy = &g_acm_ncpy[i];
            acm->acm_ncpy = (void *)acm_ncpy;
            break;
        }
    }

    if (!acm_ncpy) {
        ACM_NCPY_ERR("acm_ncpy[%s] not found\n", acm->tty_name);
        return NCPY_ERROR;
    }

    acm_ncpy->magic  = ACM_NCOPY_MAGIC;
    acm_ncpy->acm  = (void *)acm;
    acm_ncpy->tty  = (struct tty_struct *)acm->tty;
    acm_ncpy->port = (void *)acm_ncopy_port_ready(acm_ncpy->tty);
    if (!acm_ncpy->port) {
        ACM_NCPY_ERR("[%s] get port fail\n", acm->tty_name);
        return NCPY_ERROR;
    }

    INIT_LIST_HEAD(&acm_ncpy->tx_list);
    INIT_LIST_HEAD(&acm_ncpy->free_list);
    spin_lock_init(&acm_ncpy->tx_lock);

    rc = acm_ncopy_alloc_requests(&acm_ncpy->free_list,
                acm_ncopy_tx_complete, &acm_ncpy->allocated);
    if (rc) {
		ACM_NCPY_ERR("[%s] alloc requests fail\n", acm->tty_name);
        return NCPY_ERROR;
    }

    tasklet_init(&acm_ncpy->tx_task, acm_ncopy_tx_task, (unsigned long)acm_ncpy);
    acm_ncpy->available = 1;

    return NCPY_OK;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_uninit
 功能描述  : acm零拷贝去初始化接口
 输入参数  : acm_dev : 对应acm对象设备
 输出参数  : 无
 返 回 值  : NCPY_OK 去初始化成功，NCPY_ERROR 去初始化失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_uninit(int acm_dev)
{
    struct acm_ctx *acm = (struct acm_ctx *)acm_dev;
    struct acm_ncopy_ctx *acm_ncpy = NULL;

    unsigned long flags = 0;
    struct list_head *tx_pool = NULL;
    struct usb_request *req = NULL;

    if (!acm) {
        ACM_NCPY_ERR("device is not invalid\n");
        return NCPY_ERROR;
    }

    ACM_NCPY_DBG("acm[%s] enter\n", acm->tty_name);

    acm_ncpy = (struct acm_ncopy_ctx *)acm->acm_ncpy;
    if (!acm_ncpy) {
        ACM_NCPY_ERR("acm_ncpy[%s] not found\n", acm->tty_name);
        return NCPY_ERROR;
    }

    tasklet_kill(&acm_ncpy->tx_task);

    spin_lock_irqsave(&acm_ncpy->tx_lock, flags);
    acm_ncpy->available = 0;

    tx_pool = &acm_ncpy->tx_list;
    while (!list_empty(tx_pool)) {
        req = list_entry(tx_pool->next, struct usb_request, list);
        list_del(&req->list);
        spin_unlock(&acm_ncpy->tx_lock);
        acm->writeDoneCB((char *)req->buf, NCPY_ERROR);
        spin_lock(&acm_ncpy->tx_lock);
        acm_ncpy->tx_fail++;
        acm_ncpy->tx_cb++;
        list_add_tail(&req->list, &acm_ncpy->free_list);
        req->buf = NULL;
    }

    acm_ncopy_free_requests(&acm_ncpy->free_list, &acm_ncpy->allocated);
    spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);

    return NCPY_OK;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_alloc_one_request
 功能描述  : 分配单个 USB请求
 输入参数  : gfp_t gfp_flags
 输出参数  : 无
 返 回 值  : struct usb_request * 分配成功，0  分配失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月14日
    作    者   : w00140341
    修改内容   : 新生成函数

*****************************************************************************/
STATIC struct usb_request * acm_ncopy_alloc_one_request(gfp_t gfp_flags)
{
    struct usb_request *usb_req;

    ACM_NCPY_DBG("acm_ncopy_alloc_one_request(%d)\n", gfp_flags);

    usb_req = kzalloc(sizeof(*usb_req), gfp_flags);
    if (0 == usb_req) {
        ACM_NCPY_ERR("acm_ncopy_alloc_one_request allocation failed\n");
        return 0;
    }

    usb_req->dma = (~(unsigned int)0);

    return usb_req;
}


/*****************************************************************************
 函 数 名  : acm_ncopy_alloc_one_request
 功能描述  : 分配单个 USB请求
 输入参数  : struct usb_request *req
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年8月14日
    作    者   : w00140341
    修改内容   : 新生成函数

*****************************************************************************/
STATIC void acm_ncopy_free_one_request(struct usb_request *req)
{
    ACM_NCPY_DBG("acm_ncopy_free_one_request(%p)\n",  req);

    if (0 == req) {
        ACM_NCPY_ERR("acm_ncopy_free_one_request Invalid req\n");
        return;
    }

    kfree(req);
}



/*****************************************************************************
 函 数 名  : acm_ncopy_alloc_requests
 功能描述  : 分配USB请求用于零拷贝tx操作
 输入参数  : head     : 存储USB请求的链表
             fn       : USB请求完成回调接口
             allocated: 待分USB请求个数
 输出参数  : 无
 返 回 值  : NCPY_OK 分配成功，-ENOMEM 分配失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
STATIC int acm_ncopy_alloc_requests(struct list_head *head,
        void (*fn)(struct usb_ep *, struct usb_request *), int *allocated)
{
    struct usb_request *req;
    int i = 0;
    int n = 0;

    n = allocated ? (ACM_NCOPY_TX_ALLOCATED - *allocated) : ACM_NCOPY_TX_ALLOCATED;
    ACM_NCPY_DBG("alloc [%2d] requests\n", n);
    /* Pre-allocate up to ACM_NCOPY_TX_ALLOCATED transfers, but if we can't
     * do quite that many this time, don't fail ... we just won't
     * be as speedy as we might otherwise be.
     */
    for (i = 0; i < n; i++) {
        req = acm_ncopy_alloc_one_request(GFP_ATOMIC);
        if (!req) {
            ACM_NCPY_ERR("alloc req[%d] fail\n", i);
            return list_empty(head) ? -ENOMEM : 0;
        }

        ACM_NCPY_DBG("alloc [%2d] requests[%p]\n", i, req);

        req->complete = fn;
        req->context  = NULL;
        req->buf = NULL;
        req->length = 0;
        req->zero = 0;

        list_add_tail(&req->list, head);
        if (allocated) {
            (*allocated)++;
        }
    }

    return NCPY_OK;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_free_requests
 功能描述  : 释放USB请求及其对应内存
 输入参数  : head     : 存储USB请求的链表
             allocated: 待分USB请求个数
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
STATIC void acm_ncopy_free_requests(struct list_head *head,
            int *allocated)
{
    struct usb_request	*req;

    while (!list_empty(head)) {
        req = list_entry(head->next, struct usb_request, list);

        list_del(&req->list);

        acm_ncopy_free_one_request(req);

        if (allocated) {
            (*allocated)--;
        }
    }
}

/*****************************************************************************
 函 数 名  : acm_ncopy_start_tx
 功能描述  : acm零拷贝tx接口
 输入参数  : acm_dev : acm对象设备
             buf     : 待发送数据buffer
             size    : 待发送数据字节数
 输出参数  : 无
 返 回 值  : NCPY_OK tx操作成功，NCPY_ERROR tx操作失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_start_tx(int acm_dev, unsigned char *buf, unsigned int size)
{
    struct acm_ctx *acm = (struct acm_ctx *)acm_dev;
    struct acm_ncopy_ctx *acm_ncpy = NULL;
    int rc = NCPY_OK;
    unsigned long flags = 0;

    if (!acm) {
        ACM_NCPY_ERR("device is invalid\n");
        return NCPY_ERROR;
    }

    if ((NULL == buf) || (0 == size)) {
        ACM_NCPY_ERR("[%s] buf is invalid, size[%d]\n", acm->tty_name, size);
        return NCPY_ERROR;
    }

    if (size > ACM_NCOPY_TX_MAX_SIZE) {
        ACM_NCPY_ERR("[%s] size[%d] exceed the limit\n", acm->tty_name, size);
        return NCPY_ERROR;
    }

    ACM_NCPY_DBG("ACM[%s] send buf[%p] size[%d]\n", acm->tty_name, buf, size);

    acm_ncpy = (struct acm_ncopy_ctx *)acm->acm_ncpy;
    if (NULL == acm_ncpy)  {
        ACM_NCPY_ERR("[%s] acm_ncpy is invalid\n", acm->tty_name);
        return NCPY_ERROR;
    }

    ACM_NCPY_STATS_INCR(acm_ncpy, tx_got);

    if (likely(acm_ncpy->available)) {
        /* Insert tx buffer into the list */
        rc = acm_ncopy_queue(acm_ncpy, buf, size);

        /* Schedule the task */
        tasklet_schedule(&acm_ncpy->tx_task);
        return rc;
    }

    ACM_NCPY_STATS_INCR(acm_ncpy, tx_discard);

    ACM_NCPY_ERR("ACM[%s] discard for invalid buf[%p] size[%d]\n",
            acm->tty_name, buf, size);

    return NCPY_ERROR;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_queue
 功能描述  : acm零拷贝tx请求插入链表，
 输入参数  : acm_ncopy_ctx : acm设备
             buf   : 待发送数据buffer
             size  : 待发送数据字节数
 输出参数  : 无
 返 回 值  : NCPY_OK 入队成功，NCPY_ERROR 入队失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
STATIC int acm_ncopy_queue(struct acm_ncopy_ctx * acm_ncopy, unsigned char *buf,
        unsigned int size)
{
    struct acm_ncopy_ctx *acm_ncpy = acm_ncopy;
    struct list_head *tx_pool = &acm_ncpy->tx_list;
    struct list_head *free_pool  = &acm_ncpy->free_list;
    struct usb_request *req = NULL;
    unsigned long flags = 0;
    dma_addr_t dma_addr;
    int rc = 0;

    spin_lock_irqsave(&acm_ncpy->tx_lock, flags);
    if (!list_empty(free_pool)) {
        /* Get an item from free list */
        req = list_entry(free_pool->next, struct usb_request, list);

        req->buf = (void *)buf;
        req->length = size;
        req->context = (void *)acm_ncpy;
        req->zero = size ? 0 : 1;

        rc = v2p_get_pa((int)buf, (int *)&dma_addr);
        if (NCPY_OK == rc) {
            /* In case memory coherent fail, such like kmalloc */
            #if 0
            dmac_flush_range((void *)buf, (void *)(buf + size));
            outer_flush_range((phys_addr_t)dma_addr,
                        (phys_addr_t)((char *)dma_addr + size));
            #endif
        }
        else
        {
            /* map fail! */
            acm_ncpy->tx_discard++;
            spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);
            ACM_NCPY_ERR("map fail buf[%p], dma[0x%x]\n", buf, dma_addr);
            return NCPY_ERROR;
        }

        req->dma = dma_addr;

        /* Insert into tx list */
        list_del(&req->list);
        list_add_tail(&req->list, tx_pool);
        acm_ncpy->tx_queued++;
        spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);
        return NCPY_OK;
    }
    else {
        acm_ncpy->tx_discard++;
        spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);
        ACM_NCPY_ERR("no free item for buf[%p], size[%d]\n", buf, size);
        return NCPY_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : acm_ncopy_tx_task
 功能描述  : acm零拷贝tx任务，调用USB底层接口执行发送动作
 输入参数  : arg : 任务入参，指向acm_ncopy设备
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
STATIC void acm_ncopy_tx_task(unsigned long arg)
{
    struct acm_ncopy_ctx *acm_ncpy = (struct acm_ncopy_ctx *)arg;
    struct acm_ctx *acm = (struct acm_ctx *)acm_ncpy->acm;
    struct list_head *tx_pool = &acm_ncpy->tx_list;
    struct list_head *free_pool  = &acm_ncpy->free_list;
    struct usb_request *req = NULL;
    struct gserial *port = NULL;
    struct usb_ep *ep_in = NULL;
    unsigned long flags = 0;
    int rc = 0;

    spin_lock_irqsave(&acm_ncpy->tx_lock, flags);
    port = (struct gserial *)acm_ncopy_port_ready(acm_ncpy->tty);
    if (!port) {
        spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);
        ACM_NCPY_ERR("%s port not ready\n", acm->tty_name);
        return;
    }
    ep_in = port->in;

    while (!list_empty(tx_pool))
    {
        req = list_entry(tx_pool->next, struct usb_request, list);

        list_del(&req->list);
        acm_ncpy->tx_sending++;
        spin_unlock(&acm_ncpy->tx_lock);
        ACM_NCPY_DBG("sending req[%p] ep[%s]\n", req, ep_in->name);
        rc = usb_ep_queue(ep_in, req, GFP_ATOMIC);
        if (rc) {
            ACM_NCPY_ERR("%s queue %s err %d\n", acm->tty_name,
                    ep_in->name, rc);
            if (acm->freeSendbuff) {
               acm->freeSendbuff((char *)req->buf);
            }
            else if (acm->writeDoneCB) {
                acm->writeDoneCB((char *)req->buf, NCPY_ERROR);
                ACM_NCPY_STATS_INCR(acm_ncpy, tx_cb);
            }

            spin_lock(&acm_ncpy->tx_lock);
            acm_ncpy->tx_fail++;
            req->buf = NULL;
            list_add_tail(&req->list, free_pool);
            break;
        }
        spin_lock(&acm_ncpy->tx_lock);
    }
    spin_unlock_irqrestore(&acm_ncpy->tx_lock, flags);

    return;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_port_ready
 功能描述  : 通过tty设备检查acm端口是否枚举
 输入参数  : tty: acm端口对应acm设备
 输出参数  : 无
 返 回 值  : tty对应的port信息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月7日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_port_ready(void *tty)
{
    if (!tty) {
        return 0;
    }
    return ((int)usb_tty_port_get(tty));
}

/*****************************************************************************
 函 数 名  : acm_ncopy_tx_complete
 功能描述  : acm零拷贝tx完成回调
 输入参数  : ep  : acm设备对应端点
             req : USB请求
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
STATIC void acm_ncopy_tx_complete(struct usb_ep *ep, struct usb_request *req)
{
    struct acm_ncopy_ctx *acm_ncpy = (struct acm_ncopy_ctx *)req->context;
    struct acm_ctx *acm = (struct acm_ctx *)acm_ncpy->acm;
    unsigned long flags = 0;

    ACM_NCPY_DBG("req[%p] finish[%d]\n", req, req->status);

    if (!req->status) {
        /* normal completion */
        ACM_NCPY_STATS_INCR(acm_ncpy, tx_sent);
    } else {
        /* presumably a transient fault */
        ACM_NCPY_STATS_INCR(acm_ncpy, tx_fail);
        ACM_NCPY_ERR(" unexpected %s status 0x%x\n", ep->name, req->status);
    }

    if (acm->freeSendbuff) {
       acm->freeSendbuff((char *)req->buf);
    }
    else if (acm->writeDoneCB) {
        acm->writeDoneCB((char *)req->buf, req->status ? -1 : (int)req->length);
        ACM_NCPY_STATS_INCR(acm_ncpy, tx_cb);
    }

    spin_lock(&acm_ncpy->tx_lock);
    list_add_tail(&req->list, &acm_ncpy->free_list);
    spin_unlock(&acm_ncpy->tx_lock);
}

/*****************************************************************************
 函 数 名  : acm_ncopy_dbg_lev_set
 功能描述  : acm零拷贝模块打印级别设置接口
 输入参数  : lev : 打印级别
 输出参数  : 无
 返 回 值  : 打印级别
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_dbg_lev_set(int lev)
{
    g_acm_ncpy_dbg_lev = lev;
    return g_acm_ncpy_dbg_lev;
}

/*****************************************************************************
 函 数 名  : acm_ncopy_dump
 功能描述  : acm零拷贝模块信息dump接口
 输入参数  : acm_idx : acm设备端口索引
 输出参数  : 无
 返 回 值  : NCPY_OK 正常dump，NCPY_ERROR dump失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月15日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_dump(int acm_idx)
{
    struct acm_ncopy_ctx *acm_ncpy = NULL;
    struct acm_ctx *acm = NULL;

    if (USB_ACM_COM_UDI_NUM <= acm_idx) {
        printk("acm_ncopy_dump invalid index[%d]\n", acm_idx);
        return NCPY_ERROR;
    }

    acm_ncpy = &g_acm_ncpy[acm_idx];
    acm = (struct acm_ctx *)acm_ncpy->acm;

    if (!acm_ncpy->available) {
        printk("acm_ncpy[%d] invalid\n", acm_idx);
        return NCPY_ERROR;
    }

    printk("acm_ncpy[%d] info:\n", acm_idx);
    printk("acm         :%p\n", acm_ncpy->acm);
    printk("tty         :%p\n", acm_ncpy->tty);
    printk("port        :%p\n", acm_ncpy->port);
    printk("tx_lock     :%p\n", &acm_ncpy->tx_lock);
    printk("tx_list     :%p\n", &acm_ncpy->tx_list);
    printk("free_list   :%p\n", &acm_ncpy->free_list);
    printk("tx_task     :%p\n", &acm_ncpy->tx_task);
    printk("allocated   :%d\n", acm_ncpy->allocated);
    printk("available   :%d\n", acm_ncpy->available);
    printk("tx_got      :%d\n", acm_ncpy->tx_got);
    printk("tx_discard  :%d\n", acm_ncpy->tx_discard);
    printk("tx_queued   :%d\n", acm_ncpy->tx_queued);
    printk("tx_sending  :%d\n", acm_ncpy->tx_sending);
    printk("tx_sent     :%d\n", acm_ncpy->tx_sent);
    printk("tx_fail     :%d\n", acm_ncpy->tx_fail);
    printk("tx_cb       :%d\n", acm_ncpy->tx_cb);

    printk("acm_ctx info:\n");
    printk("open        :%d\n",    acm->bopen);
    printk("dev_id      :%d\n",    acm->dev_id);
    printk("fd          :0x%lx\n", acm->fd);
    printk("tty_name    :%s\n",    acm->tty_name);
    printk("readDoneCB  :%p\n",    acm->readDoneCB);
    printk("writeDoneCB :%p\n",    acm->writeDoneCB);
    printk("freeSendbuff:%p\n",    acm->freeSendbuff);
    printk("eventCB     :%p\n",    acm->eventCB);
    printk("acm_ncpy    :%p\n",    acm->acm_ncpy);
    printk("tty         :%p\n",    acm->tty);
    printk("do_copy     :%d\n",    acm->do_copy);
    printk("cur_evt     :%d\n",    acm->cur_evt);
    printk("ncopy       :%d\n",    acm->ncopy);

    return NCPY_OK;
}


/******************************************************************************
以下代码用于实现内核态虚拟地址到物理地址的转换，转换方法参见ARM MMU相关章节。
*******************************************************************************/
#define V2P_L1_TRANS_VALID_BIT  0xFFFFC000      /* L1传输基地址，14-31位 */
#define V2P_L2_TRANS_VALID_BIT  0xFFFFFC00      /* L2传输基地址，10-31位 */
#define V2P_TTBCRN_VALID_BIT    0x00000007      /* TTBCR.N 有效位 0-2位 */
#define V2P_L1_TABLE_VALID_BIT  0xFFF00000      /* L1表有效位，20-31位 */
#define V2P_L2_TABLE_VALID_BIT  0x000FF000      /* L2表有效位，12-19位 */
#define V2P_L1_TABLE_OFFSET     20              /* L1表偏移，20位 */
#define V2P_L2_TABLE_OFFSET     12              /* L2表偏移，12位 */
#define V2P_L1_PHY_HIGH_IDX     0xFFF00000      /* L1物理地址高位，20-31位 */
#define V2P_L1_PHY_LOW_IDX      0x000FFFFF      /* L1物理地址低位，0-19位 */
#define V2P_L2_PHY_HIGH_IDX     0xFFFFF000      /* L2物理地址高位，12-31位 */
#define V2P_L2_PHY_LOW_IDX      0x00000FFF      /* L2物理地址低位，0-11位 */
#define V2P_TABLE_BASE_ADDR     0x80000000      /* 分割基地址 */
#define V2P_VIRTUL_BASE_ADDR    0xC0000000          /* 虚拟基地址 */
#define V2P_PHYSICAL_BASE_ADDR  PLAT_MEM_BASE_ADDR  /* 物理基地址 */

/*获取存储一级页表起始地址的协处理器寄存器TTBR0/TTBR1/TTBCR.N */
int v2p_mmu_get_ttbr0(void)
{
    asm("mrc p15,0,r0,c2,c0,0");
}


int v2p_mmu_get_ttbr1(void)
{
    asm("mrc p15,0,r0,c2,c0,1");
}

int v2p_mmu_get_ttbcr(void)
{
    asm("mrc p15,0,r0,c2,c0,2");
}

STATIC int v2p_get_prime_ptba0(void)
{
    int ttbr0 = 0;

    ttbr0 = v2p_mmu_get_ttbr0();

    return (ttbr0 & V2P_L1_TRANS_VALID_BIT);
}

STATIC int v2p_get_prime_ptba1(void)
{
    int ttbr1 = 0;

    ttbr1 = v2p_mmu_get_ttbr1();

    return (ttbr1 & V2P_L1_TRANS_VALID_BIT);
}

/* 实现虚拟地址到物理地址转换 */
int v2p_get_pa(int va, int *pa)
{
    int prime_ptb0_start_addr;
    int prime_ptb1_start_addr;
    int prime_ptb_start_addr;
    int ttbcr;
    int ttbcr_n;
    /*first address translated with ttbr1*/
    int first_addr_ttbr1;
    int va_index;
    int prime_ptb_va_value;
    int secondary_ptb_start_addr;
    int secondary_ptb_va_value;

    prime_ptb0_start_addr = v2p_get_prime_ptba0();
    prime_ptb1_start_addr = v2p_get_prime_ptba1();
    ttbcr = v2p_mmu_get_ttbcr();
    ttbcr_n = ttbcr & V2P_TTBCRN_VALID_BIT;
    if (0 == ttbcr_n) {
        /*only use ttbr0*/
        prime_ptb_start_addr = prime_ptb0_start_addr;
    }
    else {
        first_addr_ttbr1 = V2P_TABLE_BASE_ADDR >> (ttbcr_n - 1);
        if ((unsigned int)va >= (unsigned int)first_addr_ttbr1) {
            prime_ptb_start_addr = prime_ptb1_start_addr;
        }
        else {
            prime_ptb_start_addr = prime_ptb0_start_addr;
        }
    }

    prime_ptb_start_addr = prime_ptb_start_addr - V2P_PHYSICAL_BASE_ADDR
                            + V2P_VIRTUL_BASE_ADDR;
    va_index = (va & V2P_L1_TABLE_VALID_BIT) >> V2P_L1_TABLE_OFFSET;

    prime_ptb_va_value = *((int *)(prime_ptb_start_addr + va_index * 4));
    if (prime_ptb_va_value == 0) {
        return NCPY_ERROR;
    }

    if (prime_ptb_va_value & 0x1) {
        secondary_ptb_start_addr = prime_ptb_va_value & V2P_L2_TRANS_VALID_BIT;
        secondary_ptb_start_addr = secondary_ptb_start_addr
                        - V2P_PHYSICAL_BASE_ADDR + V2P_VIRTUL_BASE_ADDR;
        va_index = (va & V2P_L2_TABLE_VALID_BIT) >> V2P_L2_TABLE_OFFSET;
        secondary_ptb_va_value = *((int *)(secondary_ptb_start_addr + va_index * 4));
        if (secondary_ptb_va_value == 0) {
            return NCPY_ERROR;
        }
        *pa = ((secondary_ptb_va_value & V2P_L2_PHY_HIGH_IDX) | (va & V2P_L2_PHY_LOW_IDX));
    }
    else {
        *pa = ((prime_ptb_va_value & V2P_L1_PHY_HIGH_IDX) | (va & V2P_L1_PHY_LOW_IDX));
    }

    return NCPY_OK;
}

/*******************************************************************************
                              test function
*******************************************************************************/
#ifndef _DRV_LLT_
int v2p_test_dma_alloc(int size)
{
    void *vir = NULL;
    dma_addr_t phy = 0;
    int  phy_get = 0;

    vir = dma_alloc_coherent(0, size, &phy, GFP_KERNEL);
    v2p_get_pa((int)vir, &phy_get);
    printk("dma alloc size[0x%x] vir[0x%x] phy[0x%x] phy_get[0x%x]\n",
        size, (int)vir, phy, phy_get);
    return NCPY_OK;
}

int v2p_test_kmalloc(int size)
{
    void *vir = NULL;
    dma_addr_t phy = 0;
    int  phy_get = 0;

    vir = kmalloc(size, GFP_KERNEL);
    phy = dma_map_single(0, vir, size, DMA_TO_DEVICE);
    v2p_get_pa((int)vir, &phy_get);

    printk("dma alloc size[0x%x] vir[0x%x] phy[0x%x] phy_get[0x%x]\n",
        size, (int)vir, phy, phy_get);
    return NCPY_OK;
}

void v2p_test_get_pa(int va)
{
    int pa;

    if (NCPY_OK == v2p_get_pa(va, &pa)) {
        printk("va= 0x%x, pa = 0x%x.\n", va, pa);
    }
    else {
        printk("get pa failed!\n");
    }
}
EXPORT_SYMBOL(v2p_test_get_pa);

/*#define ACM_NCOPY_IO_TEST*/
#ifdef ACM_NCOPY_IO_TEST

#include <linux/kthread.h>
#include <linux/delay.h>

#define ACM_NCOPY_TEST_MEM_SIZE     0x1000
#define ACM_NCOPY_TEST_MEM_NUM      16
#define ACM_NCOPY_TEST_START        0x87654321
#define ACM_NCOPY_OP_WRITE          0x1
#define ACM_NCOPY_OP_WRITEBACK      0x2

struct acm_ncopy_test_mem{
    unsigned int       valid;
    struct acm_ncopy_test_mem *next;
    char       *data;
    dma_addr_t handle;
};

struct acm_ncopy_test{
    struct acm_ncopy_ctx        *acm_ncpy;
    struct acm_ncopy_test_mem   acm_mem[ACM_NCOPY_TEST_MEM_NUM];
    struct task_struct          *thread;
    spinlock_t  lock;
    int         thr_state;
    int         id;
    int         op;
    int         seize;
};

struct acm_ncopy_test g_acm_test;

static int acm_ncopy_loop(void *arg);
static void acm_ncpy_write_cb(char *buf, int size)
{
    struct acm_ncopy_test_mem *acm_mem = NULL;
    struct acm_ncopy_test *acm_test = &g_acm_test;
    unsigned long flags;

    spin_lock_irqsave(&acm_test->lock, flags);
    acm_mem = container_of(buf, struct acm_ncopy_test_mem, data);
    acm_mem->valid = 1;
    spin_unlock_irqrestore(&acm_test->lock, flags);
}

/*****************************************************************************
 函 数 名  : acm_ncopy_transceiv
 功能描述  : acm零拷贝模块测试接口
 输入参数  : id 端口号，4为OM口
             op 操作模式，1为写操作(UE->PC); 2为环回(PC->UE->PC)
 输出参数  : 无
 返 回 值  : -1 无法测试，0 开始测试
 调用函数  : NA
 被调函数  : A核shell手动调用

 修改历史      :
  1.日    期   : 2013年5月28日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int acm_ncopy_transceiv(int id, int op)
{
    struct acm_ncopy_ctx *acm_ncpy = NULL;
    struct acm_ctx *acm = NULL;
    struct acm_ncopy_test *acm_test = NULL;
    int i = 0, j = 0;

    ACM_NCPY_ERR("acm[%d] enter\n", id);

    for (i = 0; i < USB_ACM_COM_UDI_NUM; i++) {
        acm = (struct acm_ctx *)g_acm_ncpy[i].acm;
        if (acm) {
            if (id == acm->dev_id) {
                acm_ncpy = &g_acm_ncpy[i];
                break;
            }
        }
    }

    if (!acm_ncpy) {
        ACM_NCPY_ERR("acm_ncpy[%d] not found\n", id);
        return NCPY_ERROR;
    }

    acm_test = &g_acm_test;
    acm_test->acm_ncpy = acm_ncpy;
    acm_test->id = id;
    acm_test->op = op;
    acm_test->seize = 0;

    if (ACM_NCOPY_TEST_START == acm_test->thr_state)
    {
        ACM_NCPY_ERR("thread already created ID[%d]\n", id);
        return NCPY_ERROR;
    }

    spin_lock_init(&acm_test->lock);

    for (i = 0; i < ACM_NCOPY_TEST_MEM_NUM; i++) {
        acm_test->acm_mem[i].next = &acm_test->acm_mem[(i+1)%ACM_NCOPY_TEST_MEM_NUM];
        acm_test->acm_mem[i].valid = 1;
        acm_test->acm_mem[i].data = (char *)dma_alloc_coherent(NULL,
                ACM_NCOPY_TEST_MEM_SIZE, &acm_test->acm_mem[i].handle, GFP_KERNEL);
        ACM_NCPY_ERR("buf:[%p]\n", acm_test->acm_mem[i].data);
        if (!acm_test->acm_mem[i].data) {
            ACM_NCPY_ERR("acm_ncpy[%d] not found\n", id);
            for (j = 0; j < i; j++)
            {
                dma_free_coherent(NULL, (size_t)ACM_NCOPY_TEST_MEM_SIZE,
                    (void *)acm_test->acm_mem[j].data, acm_test->acm_mem[j].handle);
            }
            return NCPY_ERROR;
        }
        memset(acm_test->acm_mem[i].data, 'a' + i, ACM_NCOPY_TEST_MEM_SIZE);
    }

    acm_test->thread = kthread_run(acm_ncopy_loop, (void *)acm_test, "acm_ncopy_test");
    if (acm_test->thread == ERR_PTR(-ENOMEM)) {
		for (j = 0; j < i; j++)
        {
            dma_free_coherent(NULL, (size_t)ACM_NCOPY_TEST_MEM_SIZE,
                    (void *)acm_test->acm_mem[j].data, acm_test->acm_mem[j].handle);
        }

        ACM_NCPY_ERR("thread create fail ID[%d]\n", id);
        return NCPY_ERROR;
    }
    acm_test->thr_state = ACM_NCOPY_TEST_START;

}

int acm_ncopy_stop(int id)
{
    struct acm_ncopy_test *acm_test = &g_acm_test;
    int i = 0;

    if (id != acm_test->id) {
        ACM_NCPY_ERR("invalid acm device ID[%d]\n", id);
        return NCPY_ERROR;
    }

    if (ACM_NCOPY_TEST_START == acm_test->thr_state) {
        ACM_NCPY_ERR("acm test not started ID[%d]\n", id);
        return NCPY_ERROR;
    }

    acm_test->seize = 1;
    msleep(100);
    kthread_stop(acm_test->thread);
    acm_test->thr_state = 0;

    for (i = 0; i < ACM_NCOPY_TEST_MEM_NUM; i++)
    {
        if (acm_test->acm_mem[i].data) {
            dma_free_coherent(NULL, (size_t)ACM_NCOPY_TEST_MEM_SIZE,
                    (void *)acm_test->acm_mem[i].data, acm_test->acm_mem[i].handle);
        }
    }

    return OK;
}

static int acm_ncopy_loop(void *arg)
{
    struct acm_ncopy_test *acm_test = (struct acm_ncopy_test *)arg;
    struct acm_ncopy_ctx *acm_ncpy = acm_test->acm_ncpy;
    struct acm_ctx *acm = (struct acm_ctx *)acm_ncpy->acm;
    struct acm_ncopy_test_mem *acm_mem;
    unsigned char *buf = NULL;
    int  len  = ACM_NCOPY_TEST_MEM_SIZE;
    unsigned long flags;
    int l = 0, i = 0;
    int times = 0;
    int rc = 0;

    ACM_NCPY_ERR("acm test enter\n");

    if (acm->bopen) {
        ACM_NCPY_ERR("acm opened by others\n");
        acm->freeSendbuff = 0;
    }
	else {
        rc = acm_open(acm_test->id);
        if (rc <= 0)
        {
            ACM_NCPY_ERR("acm opened fail\n");
            return NCPY_ERROR;
        }
    }

    acm->readDoneCB  = 0;
    acm->writeDoneCB = acm_ncpy_write_cb;
    acm_mem = &acm_test->acm_mem[0];

    while (1)
    {
        spin_lock_irqsave(&acm_test->lock, flags);
        if (acm_mem->valid) {
            buf = acm_mem->data;
            acm_mem->valid = 0;
            acm_mem = acm_mem->next;
        } else {
            times = 0;
            acm_mem = acm_mem->next;
            for (i = 0; i < ACM_NCOPY_TEST_MEM_NUM; i++)
            {
                if (acm_mem->valid) {
                    buf = acm_mem->data;
                    acm_mem->valid = 0;
                    acm_mem = acm_mem->next;
                    break;
                } else {
                    acm_mem = acm_mem->next;
                    if (ACM_NCOPY_TEST_MEM_NUM == i) {
                        i = 0;
                        times++;
                        if (times > 10) {
                            spin_unlock_irqrestore(&acm_test->lock, flags);
                            return NCPY_ERROR;
                        }
                        spin_unlock_irqrestore(&acm_test->lock, flags);
                        msleep(200);
                        spin_lock_irqsave(&acm_test->lock, flags);
                    }
                }
            }
        }
        spin_unlock_irqrestore(&acm_test->lock, flags);

        if (ACM_NCOPY_OP_WRITEBACK == acm_test->op) {
            memset((void *)buf, 0, ACM_NCOPY_TEST_MEM_SIZE);

            len = udi_acm_read((int)acm, buf, ACM_NCOPY_TEST_MEM_SIZE);
            if (len <= 0) {
                ACM_NCPY_ERR("acm recv fail [0x%x]\n", len);
                continue;
            }
        }

        l = acm_async_write((int)acm, buf, len);
        if (len != l) {
            ACM_NCPY_ERR("acm send size mismatch [%d-%d]\n", l, len);
            msleep(1);
        }

        if (acm_test->seize) {
            break;
        }
    }

    return NCPY_OK;
}

#endif
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




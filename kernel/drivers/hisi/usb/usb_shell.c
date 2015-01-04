/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : usb_shell.c
  版 本 号   : 初稿
  作    者   : 张彪 kf67996
  生成日期   : 2012年9月13日
  最近修改   :
  功能描述   : 用于实现A SHELL / C SHELL虚拟串口模块
  函数列表   :
              ashell_console_register
              ashell_console_setup
              ashell_console_write
              ashell_init
              ashell_start_io
              ashell_stop_io
              ashell_uninit
              cshell_event_cb
              cshell_icc_init
              cshell_icc_uninit
              cshell_init
              cshell_read_cb
              cshell_usb_rx_cb
              cshell_udi_close_cb
              cshell_udi_open_cb
              cshell_uninit
              cshell_write_cb
              usb_shell_init
              usb_tty_exist
  修改历史   :
  1.日    期   : 2012年9月13日
    作    者   : 张彪 kf67996
    修改内容   : 创建文件

*******************************************************************************/

/*******************************************************************************
  1 头文件包含
*******************************************************************************/

#include <linux/poll.h>
#include <linux/kallsyms.h>
#include <linux/serial_core.h>
#include <DrvInterface.h>
#include <u_serial.h>
#include <linux/dma-mapping.h>

#include "usb_shell.h"
#include "drv_usb_if.h"
#include "bsp_udi_adp.h"
#include "acm_ncopy_io.h"
#include "bsp_mailbox.h"

#include <hsad/config_mgr.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*******************************************************************************
  2 全局变量定义
*******************************************************************************/

struct cshell_ctx_t g_cshell_ctx = {0};
struct ashell_ctx_t g_ashell_ctx = {0};
unsigned int g_cshell_send_index = 0;

extern struct acm_ctx g_acm_priv[];

struct usb_tty_t g_usb_tty_map_table[USB_TTY_INSTANCES_NUM] =
{
    {USB_TTY_ASH_INDEX,   USB_TTY_ASH_TYPE,   USB_TTY_ASH_NAME  },
    {USB_TTY_AT_INDEX,    USB_TTY_AT_TYPE,    USB_TTY_AT_NAME   },
    {USB_TTY_CTRL_INDEX,  USB_TTY_CTRL_TYPE,  USB_TTY_CTRL_NAME },
    {USB_TTY_OM_INDEX,    USB_TTY_OM_TYPE,    USB_TTY_OM_NAME   },
    {USB_TTY_CSH_INDEX,   USB_TTY_CSH_TYPE,   USB_TTY_CSH_NAME  },
    {USB_TTY_LTEOM_INDEX, USB_TTY_LTEOM_TYPE, USB_TTY_LTEOM_NAME},
    {USB_TTY_GPS_INDEX,   USB_TTY_GPS_TYPE,   USB_TTY_GPS_NAME  },
};

int g_usb_shell_dbg_lev = 3;  /* KERN_ERR */

#define USB_SHELL_ERR(args,...) do {\
    if (3 <= g_usb_shell_dbg_lev) {\
        printk("A:%s:%d:", __func__, __LINE__);\
        printk(args, ##__VA_ARGS__);\
    }\
}while(0)

#define USB_SHELL_DBG(args,...) do {\
    if (7 <= g_usb_shell_dbg_lev) {\
        printk("A:%s:%d:", __func__, __LINE__);\
        printk(args, ##__VA_ARGS__);\
    }\
}while(0)

/*******************************************************************************
  3 函数声明
*******************************************************************************/
static struct tty_struct *ashell_tty_get(void);
static int cshell_get_tx_item(struct shell_mem_info *tx_mem, unsigned int count);
static int ashell_get_tx_item(struct shell_mem_info *tx_mem, unsigned int count);
static void cshell_usb_event_handle(ACM_EVT_E evt);
void cshell_usb_tx_complete(char *buf, int size);
void cshell_usb_rx_cb(void);
void cshell_usb_tx_work(struct work_struct *work);
void cshell_icc_tx_work(struct work_struct *work);
extern UDI_HANDLE cshell_get_handle(void);
extern struct console* get_uart_console(void);
extern long cshell_ccore_start(void *arg, int len, unsigned long timeout);

/*******************************************************************************
  4 函数实现
*******************************************************************************/
/*****************************************************************************
 函 数 名  : usb_tty_exist
 功能描述  : find out whether the tty device exists
 输入参数  : char *tty_name-tty device name
 输出参数  : NA
 返 回 值  : SHELL_ERROR-not exist, SHELL_OK-exist
 调用函数  : usb_tty_driver_get
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012.11.5
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
int usb_tty_exist(char *name)
{
    int i = 0;

    if (!name) {
        printk("usb_tty_exist: param invalid\n");
        return SHELL_ERROR;
    }

    /* check out whether it's in the tty group */
    for (i = 0; i < USB_TTY_INSTANCES_NUM; i++) {
        if (!strncmp(g_usb_tty_map_table[i].name, name, strlen(name))) {
            return SHELL_OK;
        }
    }

    printk("usb_tty_exist: tty NULL! tty[%s]\n", name);
    return SHELL_ERROR;
}

int __initdata g_usb_ashell_disabled = 0;
static int __init usb_ashell_disable(char *__unused)
{
      g_usb_ashell_disabled = 1;

      return 0;
}
early_param("no_usb_ashell", usb_ashell_disable);

int __initdata g_usb_cshell_disabled = 0;
static int __init usb_cshell_disable(char *__unused)
{
      g_usb_cshell_disabled = 1;

      return 0;
}
early_param("no_usb_cshell", usb_cshell_disable);

/*****************************************************************************
 函 数 名  : usb_shell_init
 功能描述  : initialize ashell、cshell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : 张彪 zkf67996
    修改内容   : 新生成函数

*****************************************************************************/
int usb_cshell_init_work(void)
{
    int c_start = 1;
#ifdef CONFIG_MACH_HI6620OEM
		
    if (1 == g_usb_cshell_disabled) {
        printk("%s : usb cshell disabled !\n", __FUNCTION__);
    } else {
        printk("%s : usb cshell enabled!\n", __FUNCTION__);
        if (SHELL_OK == usb_tty_exist(USB_TTY_CSH_NAME)) {
            if (SHELL_OK == cshell_icc_init()) {
                if (SHELL_OK == cshell_init()) {
                   cshell_ccore_start(&c_start, sizeof(int), 0);
                }
           }
        }
    }
#endif
   return SHELL_OK;
}
int usb_shell_init(void)
{
#ifdef CONFIG_MACH_HI6620OEM
    printk("usb shell init\n");

    if (1 == g_usb_ashell_disabled) {
        printk("%s : usb ashell disabled !\n", __FUNCTION__);
    } else {
        if (SHELL_OK == usb_tty_exist(USB_TTY_ASH_NAME)) {
            ashell_init();
        }
    }
#endif

   return SHELL_OK;
}

/*****************************************************************************
 函 数 名  : cshell_icc_init
 功能描述  : init the icc channel and alloc all resource for c shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
int cshell_icc_init(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *mem_tmp = NULL;
    UDI_HANDLE icc_handle = UDI_INVALID_HANDLE;
    int i = 0;

    USB_SHELL_ERR("start \n");

    /* c shell invalid */
    csh_ctx->usb_valid = 0;
    csh_ctx->icc_valid = 0;

    /* memory for usb tx */
    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->usb_tx_mem[i];
        (void)memset((void *)mem_tmp, 0, sizeof(struct shell_mem_info));

        mem_tmp->vbuf = (char *)dma_alloc_coherent(NULL, CSHELL_BUFFER_SIZE,
                (dma_addr_t *)(&mem_tmp->pbuf), GFP_KERNEL);
        if (!mem_tmp->vbuf) {
            USB_SHELL_ERR("malloc usb send mem fail \n");
            goto error;
        }
        (void)memset((void *)mem_tmp->vbuf, 0, CSHELL_BUFFER_SIZE);

        mem_tmp->free = 1;
        mem_tmp->idx  = i;
        mem_tmp->next = &csh_ctx->usb_tx_mem[(i + 1) % CSHELL_SEND_BUFFER_NUM];
    }
    csh_ctx->usb_tx_idx = 0;

    /* memroy for icc rx */
    csh_ctx->usb_rx_buf = (char *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if (!csh_ctx->usb_rx_buf) {
        USB_SHELL_ERR("malloc usb_rx_buf fail\n");
        goto error;
    }
    (void)memset((void *)csh_ctx->usb_rx_buf, 0, CSHELL_BUFFER_SIZE);

    /* memory for icc tx */
    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->icc_tx_mem[i];
        (void)memset((void *)mem_tmp, 0, sizeof(struct shell_mem_info));

        mem_tmp->vbuf = (char *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
        if (!mem_tmp->vbuf) {
            USB_SHELL_ERR("malloc icc_tx_mem fail \n");
            goto error;
        }
        (void)memset((void *)mem_tmp->vbuf, 0, CSHELL_BUFFER_SIZE);

        mem_tmp->free = 1;
        mem_tmp->idx  = i;
        mem_tmp->next = &csh_ctx->icc_tx_mem[(i + 1) % CSHELL_SEND_BUFFER_NUM];
    }
    csh_ctx->icc_tx_idx = 0;

    /* memroy for icc rx */
    csh_ctx->icc_rx_buf = (char *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if (!csh_ctx->icc_rx_buf) {
        USB_SHELL_ERR("malloc icc_rx_buf fail \n");
        goto error;
    }
    (void)memset((void *)csh_ctx->icc_rx_buf, 0, CSHELL_BUFFER_SIZE);

    /* get icc channel handle */
    icc_handle = cshell_get_handle();
    csh_ctx->icc_fd = icc_handle;
    if (icc_handle > 0) {
        csh_ctx->icc_chan_id = CSHELL_ICC_CHANNEL_ID;
        csh_ctx->icc_opened  = 1;
    } else {
        csh_ctx->icc_chan_id = CSHELL_ICC_CHANNEL_INVALID_ID;
        csh_ctx->icc_opened  = 0;
        USB_SHELL_ERR("get icc handle fail: [0x%x]\n", icc_handle);
        goto error;
    }
    csh_ctx->icc_valid = 1;

    USB_SHELL_ERR("init ok\n");
    return SHELL_OK;

error:
    cshell_icc_uninit();
    USB_SHELL_ERR("init fail...\n");
    return SHELL_ERROR;
}

/*****************************************************************************
 函 数 名  : cshell_icc_uninit
 功能描述  : free all resource for c shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
void cshell_icc_uninit(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *mem_tmp = NULL;
    int i = 0;

    USB_SHELL_ERR("enter\n");

    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->usb_tx_mem[i];
        if (mem_tmp->vbuf) {
            dma_free_coherent(NULL, CSHELL_BUFFER_SIZE, (void *)mem_tmp->vbuf,
                    (dma_addr_t)(mem_tmp->pbuf));
        }
        memset(mem_tmp, 0, sizeof(struct shell_mem_info));
    }

    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->icc_tx_mem[i];
        if (mem_tmp->vbuf) {
            kfree((void *)mem_tmp->vbuf);
        }
        memset(mem_tmp, 0, sizeof(struct shell_mem_info));
    }

    if (csh_ctx->usb_rx_buf) {
        kfree(csh_ctx->usb_rx_buf);
        csh_ctx->usb_rx_buf = NULL;
    }

    if (csh_ctx->icc_rx_buf) {
        kfree(csh_ctx->icc_rx_buf);
        csh_ctx->icc_rx_buf = NULL;
    }

    if (csh_ctx->icc_opened) {
        udi_close(csh_ctx->icc_fd);
        csh_ctx->icc_fd = 0;
    }

    csh_ctx->icc_valid = 0;
    csh_ctx->icc_opened = 0;
    csh_ctx->icc_chan_id = CSHELL_ICC_CHANNEL_INVALID_ID;
}



/*******************************************************************************
 函 数 名  : cshell_init
 功能描述  : init c shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
int cshell_init(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;

    USB_SHELL_ERR("start\n");

    spin_lock_init(&csh_ctx->usb_lock);
    spin_lock_init(&csh_ctx->icc_lock);
    INIT_WORK(&csh_ctx->usb_tx_work, cshell_usb_tx_work);
    INIT_WORK(&csh_ctx->icc_tx_work, cshell_icc_tx_work);

    BSP_USB_RegUdiEnableCB(cshell_udi_open_cb);
    BSP_USB_RegUdiDisableCB(cshell_udi_close_cb);

    USB_SHELL_ERR("init ok\n");
    return SHELL_OK;
}

/*******************************************************************************
 函 数 名  : cshell_uninit
 功能描述  : uninit c shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_uninit(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;

    USB_SHELL_ERR("enter\n");

    cshell_icc_uninit();
    csh_ctx->usb_valid = 0;
}

/*******************************************************************************
 函 数 名  : cshell_udi_open_cb
 功能描述  : callback for usb online, open the port and register callback
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_udi_open_cb(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    UDI_OPEN_PARAM cshell_bluetooth_param;
    int usb_handle = UDI_INVALID_HANDLE;
    int ret = 0;

    USB_SHELL_ERR("acm plugin: [0x%x]\n", csh_ctx->usb_fd);

    if (csh_ctx->usb_fd > 0)
    {
        USB_SHELL_ERR("acm already opened:[0x%x]\n", csh_ctx->usb_fd);
        return;
    }

    /* open the usb port for c shell */
    cshell_bluetooth_param.devid = UDI_ACM_SHELL_ID;
    usb_handle = udi_open(&cshell_bluetooth_param);
    if (usb_handle <= 0)
    {
        USB_SHELL_ERR("acm open fail: [0x%x]\n", usb_handle);
        return;
    }
    csh_ctx->usb_fd = usb_handle;

    ret = udi_ioctl(csh_ctx->usb_fd, ACM_IOCTL_SET_READ_CB, cshell_usb_rx_cb);
    if (SHELL_OK != ret)
    {
        USB_SHELL_ERR("rx cb register fail: [0x%x]\n", ret);
        return;
    }

    ret = udi_ioctl(csh_ctx->usb_fd, ACM_IOCTL_SET_WRITE_CB, cshell_usb_tx_complete);
    if (SHELL_OK != ret)
    {
        USB_SHELL_ERR("tx cb register fail: [0x%x]\n", ret);
        return;
    }

    ret = udi_ioctl(csh_ctx->usb_fd, ACM_IOCTL_SET_EVT_CB, cshell_usb_event_handle);
    if (SHELL_OK != ret)
    {
        USB_SHELL_ERR("evt cb register fail: [0x%x]\n", ret);
        return;
    }

    /*csh_ctx->usb_valid = 1;*/

    USB_SHELL_ERR(" usb connected !!!\n");
}

/*******************************************************************************
 函 数 名  : cshell_udi_close_cb
 功能描述  : callback for usb offline, close the port and unregister callback
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_udi_close_cb(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    int ret = 0;

    USB_SHELL_ERR("acm unplug: [0x%x]\n", csh_ctx->usb_fd);

    if (csh_ctx->usb_fd > 0)
    {
        ret = udi_close(csh_ctx->usb_fd);
        if (BSP_OK != ret)
        {
            USB_SHELL_ERR(" fail: [0x%x]\n", ret);
            return;
        }
        csh_ctx->usb_fd = 0;
    }
}

/*******************************************************************************
 函 数 名  : cshell_event_cb
 功能描述  : callback for icc event, ignored
 输入参数  : id     icc channel id
             event  event type
             param  info for the event
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
unsigned int cshell_event_cb(unsigned int id, unsigned int event, void *Param)
{
    USB_SHELL_ERR("chan[%d], event:%d\n", id, event);
    return SHELL_OK;
}

/*******************************************************************************
 函 数 名  : cshell_write_cb
 功能描述  : callback for icc write event, write the next packet
 输入参数  : id     icc channel id
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
unsigned int cshell_write_cb(unsigned int id)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;

    USB_SHELL_DBG("chan[%d]\n", id);

    if(csh_ctx->icc_valid) {
        schedule_work(&csh_ctx->icc_tx_work);
    } else {
        USB_SHELL_DBG("usb_valid[%d] icc_valid[%d]\n",
                csh_ctx->usb_valid, csh_ctx->icc_valid);
    }

    return SHELL_OK;
}

/*******************************************************************************
 函 数 名  : cshell_read_cb
 功能描述  : callback for icc read event, read icc data immediately
 输入参数  : id     icc channel id
             size   data size to read
 输出参数  : NA
 返 回 值  : SHELL_ERROR-success, SHELL_OK-fail
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
unsigned int cshell_read_cb(unsigned int id, int size)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    char *tx_buf = NULL;
    unsigned long flags;
    int count = 0;

    USB_SHELL_DBG(" size[%d]\n", size);

    if (!csh_ctx->icc_valid) {
        USB_SHELL_DBG("[Warning] C core not ready\n");
        return (unsigned int)SHELL_ERROR;
    }

    /* read data from c core */
    count = BSP_ICC_Read(csh_ctx->icc_chan_id, csh_ctx->icc_rx_buf, size);
    if (count < 0) {
        USB_SHELL_ERR("read fail ret[0x%x]\n", count);
        return (unsigned int)SHELL_ERROR;
    } else if (count == size) {
        USB_SHELL_DBG("all [%d] data read\n", size);
    } else if (count < size) {
        USB_SHELL_ERR("read[%d], all[%d]\n", count, size);
    } else {
        USB_SHELL_ERR("read fail ret[0x%x]\n", count);
        return (unsigned int)SHELL_ERROR;
    }

    /* usb not ready,  */
    if (!csh_ctx->usb_valid) {
        USB_SHELL_DBG("[Warning] usb not ready\n");
        return (unsigned int)SHELL_ERROR;
    }

    /* get a usb_tx_mem and update the info */
    spin_lock_irqsave(&csh_ctx->usb_lock, flags);
    tx_mem = &csh_ctx->usb_tx_mem[csh_ctx->usb_tx_idx];
    tx_mem = (struct shell_mem_info *)cshell_get_tx_item(tx_mem, (unsigned int)count);
    if (!tx_mem) {
        spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);
        USB_SHELL_DBG("usb tx mem full count[%d]\n", count);
        return (unsigned int)SHELL_ERROR;
    }
    tx_buf = tx_mem->vbuf + tx_mem->used;
    tx_mem->used += (unsigned int)count;
    spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);

    /* copy the icc data to usb tx mem */
    memcpy(tx_buf, csh_ctx->icc_rx_buf, (unsigned int)count);

    USB_SHELL_DBG("icc recv [%d] usb_send_mem[0x%p] used[%d] idx[%d]\n", count,
            tx_mem, tx_mem->used, tx_mem->idx);

    schedule_work(&csh_ctx->usb_tx_work);

    return SHELL_OK;
}

/*******************************************************************************
 函 数 名  : cshell_usb_tx_cb
 功能描述  : callback for usb tx complete
 输入参数  : NA
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_usb_tx_complete(char *buf, int size)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    unsigned long flags;
    int i = 0;

    for (i = 0; i < ASHELL_SEND_BUFFER_NUM; i++) {
        tx_mem = &csh_ctx->usb_tx_mem[i];
        if (tx_mem->vbuf == buf) {
            break;
        }
    }

    if (tx_mem->vbuf != buf) {
        USB_SHELL_ERR("buf invalid: buf[0x%p] size[%d]\n", buf, size);
        return;
    }

    USB_SHELL_DBG("tx_mem[0x%p] used[%d] idx[%d]\n", tx_mem,
            tx_mem->used, tx_mem->idx);
    spin_lock_irqsave(&csh_ctx->usb_lock, flags);
    tx_mem->used = 0;
    tx_mem->free = 1;
    spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);
}

/*******************************************************************************
 函 数 名  : cshell_usb_rx_cb
 功能描述  : callback for usb data ready, fetch it now
 输入参数  : NA
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_usb_rx_cb(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    char *tx_buf = NULL;
    unsigned long flags;
    int count = 0;

    USB_SHELL_DBG("enter\n");

    /* read data from usb */
    count = udi_read(csh_ctx->usb_fd, csh_ctx->usb_rx_buf, CSHELL_BUFFER_SIZE);
    if (count <= 0) {
        USB_SHELL_DBG("read data fail: count[0x%x]\n", count);
        return;
    }

    /* get a icc_tx_mem and update the info */
    spin_lock_irqsave(&csh_ctx->icc_lock, flags);
    tx_mem = &csh_ctx->icc_tx_mem[csh_ctx->icc_tx_idx];
    tx_mem = (struct shell_mem_info *)cshell_get_tx_item(tx_mem, (unsigned int)count);
    if (!tx_mem) {
        spin_unlock_irqrestore(&csh_ctx->icc_lock, flags);
        USB_SHELL_ERR("icc tx mem full count[0x%x]\n", count);
        return;
    }
    tx_buf = tx_mem->vbuf + tx_mem->used;
    tx_mem->used += (unsigned int)count;
    spin_unlock_irqrestore(&csh_ctx->icc_lock, flags);

    /* copy the usb data to icc tx mem */
    memcpy(tx_buf, csh_ctx->usb_rx_buf, (unsigned int)count);

    USB_SHELL_DBG("usb recv [%d] icc_tx_mem[0x%p] used[%d] idx[%d]\n", count,
            tx_mem, tx_mem->used, tx_mem->idx);

    schedule_work(&csh_ctx->icc_tx_work);
}

/*****************************************************************************
 函 数 名  : cshell_usb_event_handle
 功能描述  : c shell event handler, if the usb port is opened,
             there is a "READY" event, otherwise "SUSPEND"
 输入参数  : evt event to be handle
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.19
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
static void cshell_usb_event_handle(ACM_EVT_E evt)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    unsigned long flags;

    USB_SHELL_DBG("evt[%d] \n", evt);

    spin_lock_irqsave(&csh_ctx->usb_lock, flags);
    if (ACM_EVT_DEV_SUSPEND == evt) {
        csh_ctx->usb_valid = 0;
    }
    else if (ACM_EVT_DEV_READY == evt) {
        csh_ctx->usb_valid = 1;
    }
    spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);
}

/*******************************************************************************
 函 数 名  : cshell_get_tx_item
 功能描述  : get a free tx memory
 输入参数  : NA
 输出参数  : NA
 返 回 值  : tx_mem or NULL
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
static int cshell_get_tx_item(struct shell_mem_info *tx_mem, unsigned int count)
{
    int i = CSHELL_SEND_BUFFER_NUM;

    while (i--) {
        if (tx_mem->free &&
            ((tx_mem->used + count) < CSHELL_BUFFER_SIZE)) {
            return (int)tx_mem;
        }
        tx_mem = tx_mem->next;
    }

    /* no free item */
    return 0;
}

/*******************************************************************************
 函 数 名  : cshell_usb_tx_work
 功能描述  : usb tx work, flush all pending data to usb
 输入参数  : work  usb tx work handle
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_usb_tx_work(struct work_struct *work)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    ACM_WR_ASYNC_INFO mem_info;
    unsigned long flags;
    int ret = 0;

    spin_lock_irqsave(&csh_ctx->usb_lock, flags);
    tx_mem = &csh_ctx->usb_tx_mem[csh_ctx->usb_tx_idx];
    while (tx_mem->free && tx_mem->used && csh_ctx->usb_valid)
    {
        tx_mem->free = 0;
        mem_info.pBuffer = tx_mem->vbuf;
        mem_info.u32Size = tx_mem->used;
        spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);

        USB_SHELL_DBG("tx_mem[0x%p] used[%d] idx[%d]\n", tx_mem,
                tx_mem->used, tx_mem->idx);

        /* send to PC */
        ret = udi_ioctl(csh_ctx->usb_fd, ACM_IOCTL_WRITE_ASYNC, &mem_info);
        if (SHELL_OK == ret) {
            USB_SHELL_DBG("all sent[%d]\n", tx_mem->used);
        } else {
            USB_SHELL_ERR("send to PC fail, count[0x%x]\n", ret);
            spin_lock_irqsave(&csh_ctx->usb_lock, flags);
            tx_mem->used = 0;
            tx_mem->free = 1;
            spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);

        }

        spin_lock_irqsave(&csh_ctx->usb_lock, flags);
        tx_mem = tx_mem->next;
        csh_ctx->usb_tx_idx = tx_mem->idx;
    }
    spin_unlock_irqrestore(&csh_ctx->usb_lock, flags);

}

/*******************************************************************************
 函 数 名  : cshell_icc_tx_work
 功能描述  : icc tx work, flush all pending data to icc
 输入参数  : work  icc tx work handle
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.15
    作    者   : z00145324
    修改内容   : new function

*******************************************************************************/
void cshell_icc_tx_work(struct work_struct *work)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    unsigned long flags;
    int count= 0;

    spin_lock_irqsave(&csh_ctx->icc_lock, flags);
    tx_mem = &csh_ctx->icc_tx_mem[csh_ctx->icc_tx_idx];
    while (tx_mem->free && tx_mem->used && csh_ctx->icc_valid)
    {
        tx_mem->free = 0;
        spin_unlock_irqrestore(&csh_ctx->icc_lock, flags);

        USB_SHELL_DBG("tx_mem[0x%p] used[%d] idx[%d]\n", tx_mem,
                tx_mem->used, tx_mem->idx);

        /* send to C core */
        count = udi_write(csh_ctx->icc_fd, tx_mem->vbuf, tx_mem->used);
        if (count == tx_mem->used) {
            USB_SHELL_DBG("all sent, count[%d] \n", count);
        } else if (count < 0) {
            USB_SHELL_ERR("send to PC fail, count[0x%x]\n", count);
        } else {
            USB_SHELL_ERR("part sent [%d-%d]\n", count, tx_mem->used);
        }

        spin_lock_irqsave(&csh_ctx->icc_lock, flags);
        /* tx_mem is copied to icc buffer, update it... */
        tx_mem->used = 0;
        tx_mem->free = 1;
        tx_mem = tx_mem->next;
        csh_ctx->icc_tx_idx = tx_mem->idx;
    }
    spin_unlock_irqrestore(&csh_ctx->icc_lock, flags);
}

/*****************************************************************************
 函 数 名  : ashell_start_io
 功能描述  : register the write callback for console
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012.11.5
    作    者   : z00145324
    修改内容   : new function
*****************************************************************************/
int ashell_start_io(void)
{
    struct ashell_ctx_t* ash_ctx = &g_ashell_ctx;
    struct acm_ctx *acm = (struct acm_ctx *)ash_ctx->acm_ctx;
    unsigned long flags;
    int ret = 0;

    printk("ashell_start_io\n");

    /* get the tty struct and init ncopy */
    ash_ctx->tty = ashell_tty_get();
    if (!ash_ctx->tty) {
        printk("ashell_init tty get fail\n");
        return SHELL_ERROR;
    } else {
        acm->tty = ash_ctx->tty;
        ret = acm_ncopy_init((int)acm);
        if (SHELL_OK != ret) {
            printk("ashell_init ncopy init fail\n");
            return SHELL_ERROR;
        }
    }

    spin_lock_irqsave(&ash_ctx->lock, flags);
    ash_ctx->enable = 1;
    spin_unlock_irqrestore(&ash_ctx->lock, flags);

    return SHELL_OK;
}

/*****************************************************************************
 函 数 名  : ashell_stop_io
 功能描述  : unregister the write callback for console
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012.11.5
    作    者   : z00145324
    修改内容   : new function
*****************************************************************************/
int ashell_stop_io(void)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct acm_ctx *acm = (struct acm_ctx *)ash_ctx->acm_ctx;

    if (ash_ctx->enable) {
        ash_ctx->enable = 0;
        if (acm->ncopy) {
            acm_ncopy_uninit((int)acm);
        }
        printk("ashell_stop_io\n");
    } else {
        printk("ashell_stop_io:already stopped\n");
    }

    return SHELL_OK;
}

/*****************************************************************************
 函 数 名  : ashell_tx_work
 功能描述  : work for ashell write
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.05
    作    者   : z00145324
    修改内容   : new function
*****************************************************************************/
static void ashell_tx_work(struct work_struct *work)
{
    struct ashell_ctx_t *ash_ctx = container_of((struct delayed_work *)work, struct ashell_ctx_t, tx_work);
    struct acm_ctx *acm = (struct acm_ctx *)ash_ctx->acm_ctx;
    struct shell_mem_info *tx_mem = NULL;
    unsigned long flags;

    spin_lock_irqsave(&ash_ctx->lock, flags);
    tx_mem = &ash_ctx->tx_mem[ash_ctx->tx_idx];
    while (tx_mem->free && tx_mem->used && ash_ctx->enable)
    {
        tx_mem->free = 0;
        spin_unlock_irqrestore(&ash_ctx->lock, flags);
        acm_ncopy_start_tx((int)acm, (unsigned char *)tx_mem->vbuf, tx_mem->used);
        spin_lock_irqsave(&ash_ctx->lock, flags);
        tx_mem = tx_mem->next;
        ash_ctx->tx_idx = tx_mem->idx;
    }
    spin_unlock_irqrestore(&ash_ctx->lock, flags);
}

/*****************************************************************************
 函 数 名  : ashell_get_tx_item
 功能描述  : get a free tx memory
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
static int ashell_get_tx_item(struct shell_mem_info *tx_mem, unsigned int count)
{
    int i = ASHELL_SEND_BUFFER_NUM;

    while (i--) {
        if (tx_mem->free &&
            ((tx_mem->used + count) < ASHELL_BUFFER_SIZE)) {
            return (int)tx_mem;
        }
        tx_mem = tx_mem->next;
    }

    /* no free item */
    return 0;
}

/*****************************************************************************
 函 数 名  : ashell_write
 功能描述  : a shell write function with no copy
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
int ashell_write(struct ashell_ctx_t *ash_ctx, char *buf, unsigned int count)
{
    struct shell_mem_info *tx_mem = NULL;
    unsigned long flags;

    spin_lock_irqsave(&ash_ctx->lock, flags);
    /* no more than the threahold */
    if (count > ASHELL_BUFFER_SIZE) {
        count = ASHELL_BUFFER_SIZE;
    }

    tx_mem = &ash_ctx->tx_mem[ash_ctx->tx_idx];
    tx_mem = (struct shell_mem_info *)ashell_get_tx_item(tx_mem, count);
    if (!tx_mem) {
        spin_unlock_irqrestore(&ash_ctx->lock, flags);
        return SHELL_ERROR;
    }

    memcpy((void *)(tx_mem->vbuf + tx_mem->used), (void *)buf, count);
    tx_mem->used += count;
    spin_unlock_irqrestore(&ash_ctx->lock, flags);

    schedule_delayed_work(&ash_ctx->tx_work, msecs_to_jiffies(100));
    return SHELL_OK;
}

/*****************************************************************************
 函 数 名  : ashell_write_complete
 功能描述  : a shell write callback
 输入参数  : buf  buffer processed
             size number of bytes processed
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
void ashell_write_complete(char *buf, int size)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct shell_mem_info *tx_mem = NULL;
    unsigned long flags;
    int i = 0;

    for (i = 0; i < ASHELL_SEND_BUFFER_NUM; i++) {
        tx_mem = &ash_ctx->tx_mem[i];
        if (tx_mem->vbuf == buf) {
            break;
        }
    }

    /*WARN_ON(tx_mem->vbuf != buf);*/
    /*memset((void *)buf, 0, size);*/

    spin_lock_irqsave(&ash_ctx->lock, flags);
    tx_mem->used = 0;
    tx_mem->free = 1;
    spin_unlock_irqrestore(&ash_ctx->lock, flags);
}

/*****************************************************************************
 函 数 名  : ashell_event_handle
 功能描述  : a shell event handler
 输入参数  : evt event to be handle
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
void ashell_event_handle(ACM_EVT_E evt)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    unsigned long flags;

    spin_lock_irqsave(&ash_ctx->lock, flags);
    if (ACM_EVT_DEV_SUSPEND == evt) {
        ash_ctx->port_open = 0;
    }
    else if (ACM_EVT_DEV_READY == evt) {
        ash_ctx->port_open = 1;
    }
    spin_unlock_irqrestore(&ash_ctx->lock, flags);
}



/*****************************************************************************
 函 数 名  : ashell_init
 功能描述  : initialize a shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : BSP_USB_RegUdiEnableCB
             BSP_USB_RegUdiDisableCB
             ashell_console_register
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012.11.5
    作    者   : z00145324
    修改内容   : new function

*****************************************************************************/
int ashell_init(void)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct acm_ctx *acm = &g_acm_priv[USB_TTY_ASH_INDEX];
    struct shell_mem_info *tx_mem = NULL;
    int i = 0;

    printk("ashell_init enter\n");

    for (i = 0; i < ASHELL_SEND_BUFFER_NUM; i++) {
        tx_mem = &ash_ctx->tx_mem[i];
        tx_mem->vbuf = (char *)dma_alloc_coherent(NULL, ASHELL_BUFFER_SIZE,
                (dma_addr_t *)(&tx_mem->pbuf), GFP_KERNEL);
        if (!ash_ctx->tx_mem[i].vbuf) {
            goto error;
        }
        tx_mem->idx  = i;
        tx_mem->used = 0;
        tx_mem->free = 1;
        tx_mem->next = &(ash_ctx->tx_mem[(i + 1) % ASHELL_SEND_BUFFER_NUM]);
        /*printk("ashell_init:idx[%d] tx_mem[0x%x] vbuf[0x%x] pbuf[0x%x]\n",
                i, tx_mem, tx_mem->vbuf, tx_mem->pbuf);*/
    }
    ash_ctx->enable = 0;
    ash_ctx->tx_idx = 0;
    ash_ctx->port_open = 0;

    /* Info for ashell port */
    acm->writeDoneCB = ashell_write_complete;
    acm->eventCB     = ashell_event_handle;
    ash_ctx->acm_ctx = (void *)acm;

    spin_lock_init(&ash_ctx->lock);
    INIT_DELAYED_WORK(&ash_ctx->tx_work, ashell_tx_work);
    BSP_USB_RegUdiEnableCB((USB_UDI_ENABLE_CB_T)ashell_start_io);
    BSP_USB_RegUdiDisableCB((USB_UDI_DISABLE_CB_T)ashell_stop_io);

    ashell_console_register();

    return SHELL_OK;

error:
    for (i = 0; i < ASHELL_SEND_BUFFER_NUM; i++) {
        if (ash_ctx->tx_mem[i].vbuf) {
            dma_free_coherent(NULL, ASHELL_BUFFER_SIZE, (void *)ash_ctx->tx_mem[i].vbuf,
                    (dma_addr_t)(ash_ctx->tx_mem[i].pbuf));
        }
        ash_ctx->tx_mem[i].used = 1;
        ash_ctx->tx_mem[i].free = 0;
    }
    (void)unregister_console(&ash_ctx->port_console);
    return SHELL_ERROR;
}

/*****************************************************************************
 函 数 名  : ashell_uninit
 功能描述  : uninitialize a shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : SHELL_OK-success
 调用函数  : unregister_console
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012.11.5
    作    者   : z00145324
    修改内容   : new function
*****************************************************************************/
int ashell_uninit(void)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct acm_ctx *acm = (struct acm_ctx *)ash_ctx->acm_ctx;
    unsigned long flags = 0;
    int i = 0;

    printk("ashell_uninit enter\n");

    cancel_delayed_work(&ash_ctx->tx_work);
    spin_lock_irqsave(&ash_ctx->lock, flags);
    ash_ctx->enable = 0;
    for (i = 0; i < ASHELL_SEND_BUFFER_NUM; i++) {
        if (ash_ctx->tx_mem[i].vbuf) {
            dma_free_coherent(NULL, ASHELL_BUFFER_SIZE, (void *)ash_ctx->tx_mem[i].vbuf,
                    (dma_addr_t)(ash_ctx->tx_mem[i].pbuf));
        }
        ash_ctx->tx_mem[i].used = 1;
        ash_ctx->tx_mem[i].free = 0;
    }
    ash_ctx->tx_idx = 0;

    acm->writeDoneCB  = NULL;
    acm->eventCB      = NULL;
    acm->tty          = NULL;
    spin_unlock_irqrestore(&ash_ctx->lock, flags);

    (void)unregister_console(&ash_ctx->port_console);
    return SHELL_OK;
}

/*****************************************************************************
 函 数 名  : ashell_console_register
 功能描述  : 将虚拟串口注册console设备
 输入参数  : struct ashell_ctx_t* ash_ctx ashell结构体
 输出参数  : 无
 返 回 值  : 无
 调用函数  : get_uart_console
             ashell_console_write
             ashell_console_device
             ashell_console_setup
             unregister_console
             register_console
             ACM_DEBUG
 被调函数  : gserial_setup

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : 张彪 zkf67996
    修改内容   : 移植v3r2

*****************************************************************************/
int ashell_console_register(void)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct console *uart_console = NULL;
    unsigned long flags = 0;

    printk("ashell_console_register enter\n");
    spin_lock_irqsave(&ash_ctx->lock, flags);
    strncpy(ash_ctx->port_console.name,"ttyGS",sizeof("ttyGS"));
    ash_ctx->port_console.write  = ashell_console_write;
    ash_ctx->port_console.device = ashell_console_device;
    ash_ctx->port_console.setup  = ashell_console_setup;
    ash_ctx->port_console.flags  = CON_PRINTBUFFER;
    ash_ctx->port_console.index  = -1;
    ash_ctx->port_console.data   = ash_ctx;
    spin_unlock_irqrestore(&ash_ctx->lock, flags);

    uart_console = get_uart_console();
    if (uart_console){
        unregister_console(uart_console);
    }

    register_console(&ash_ctx->port_console);
    /* register_console(uart_console); */

    return SHELL_OK;
}

/* This stolen/adapted from serial/sn_console.c */
/*****************************************************************************
 函 数 名  : ashell_console_write
 功能描述  : ashell console write
 输入参数  : struct console *cons  设备的console结构体
             const char *buf       需要写入的BUF
             unsigned count        需要写入的字节大小
 输出参数  : NA
 返 回 值  : NA
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : 张彪 zkf67996
    修改内容   : 新生成函数

*****************************************************************************/
void ashell_console_write(struct console *cons, const char *buf, unsigned count)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;
    struct acm_ctx *acm = (struct acm_ctx *)ash_ctx->acm_ctx;



    /* check param */
    if ((NULL == cons) || (NULL == buf) || (0 == count)) {
        return;
    }

    if (!ash_ctx->enable || !ash_ctx->port_open) {
        return;
    }

    /* write to pc */
    if (acm->ncopy) {
        ashell_write(ash_ctx, (char *)buf, count);
    }
    else {
        /* if nocopy is not needed, reset flag "ncopy" and make this act */
        /* if (ash_ctx->tty) {
            tty = ash_ctx->tty;
        } else {
            return;
        }

        if (tty->ops->write) {
            ret = tty->ops->write(tty, (const unsigned char *)buf, (int)count);
            if (ret < (int)count) {
                return;
            }
        } */
    }

    return;
}

/*****************************************************************************
 函 数 名  : ashell_console_setup
 功能描述  : 通过struct ashell_ctx_t_s结构体指针获取port_console指针
 输入参数  : char *options
             struct console *cons  设备的console结构体
 输出参数  : 无
 返 回 值  : int 成功返回OK
 调用函数  : container_of
 被调函数  : ashell_console_register

 修改历史      :
  1.日    期   : 2012年9月12日
    作    者   : 张彪 zkf67996
    修改内容   : 移植v3r2

*****************************************************************************/

int ashell_console_setup (struct console *cons, char *options)
{
    struct ashell_ctx_t* ash_ctx;
    /*
     * If this is called we are about to become the active console. (?)
     *
     * That is not what this hook is for, but it serves our purposes.
     *
     * Since there is no actual tty yet, we have to do some of what is
     * normally done in gs_open.
     */
    ash_ctx = container_of(cons, struct ashell_ctx_t, port_console);
    ash_ctx = ash_ctx;
    return (int)SHELL_OK;
}

/*****************************************************************************
 函 数 名  : ashell_tty_get
 功能描述  : get the tty of a shell
 输入参数  : NA
 输出参数  : NA
 返 回 值  : tty
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013.08.01
    作    者   : z00145324
    修改内容   : new function
*****************************************************************************/
static struct tty_struct *ashell_tty_get(void)
{
    struct tty_driver *driver = NULL;
    struct tty_struct *tty = NULL;

    /* get driver */
    driver = usb_tty_driver_get();
    if (!driver) {
        printk("ashell tty driver get fail \n");
        return NULL;
    }

    /*
     * get the tty for ashell(index is 0 !!!)
     */
    tty = driver->ttys[USB_TTY_ASH_INDEX];
    if (!tty) {
        printk("ashell tty get fail \n");
        return NULL;
    }

    return tty;
}

/*Modify_for_c_reset, l00212112,20130511, starts*/
/*****************************************************************************
 函 数 名  : bsp_ccpu_rest_cshell_handle
 功能描述  : CCPU单独复位时，ashell处理流程
 输入参数  : int status
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月18日
    作    者   : 袁旦 00145322
    修改内容   : 新生成函数

*****************************************************************************/
int bsp_ccpu_rest_cshell_handle(int status)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    unsigned long flags;
    int c_start = 1;

    if (1 == g_usb_cshell_disabled) {
        USB_SHELL_ERR("usb cshell disabled\n");
        return SHELL_ERROR;
    }

    if (!csh_ctx->icc_fd) {
        USB_SHELL_ERR("icc fail\n");
        return SHELL_ERROR;
    }

    spin_lock_irqsave(&csh_ctx->icc_lock, flags);
    csh_ctx->icc_valid = status;
    spin_unlock_irqrestore(&csh_ctx->icc_lock, flags);

    cshell_ccore_start(&c_start, sizeof(int), 0);
    return SHELL_OK;
}
/*Modify_for_c_reset, l00212112,20130511, ends*/

/*****************************************************************************
 函 数 名  : acm_shell_dbg_lev_set
 功能描述  : USB shell模块打印级别设置接口
 输入参数  : lev : 打印级别
 输出参数  : 无
 返 回 值  : 打印级别
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月04日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int usb_shell_dbg_lev_set(int lev)
{
    g_usb_shell_dbg_lev = lev;
    return g_usb_shell_dbg_lev;
}

/*****************************************************************************
 函 数 名  : acm_shell_dbg_lev_set
 功能描述  : USB shell模块打印级别设置接口
 输入参数  : lev : 打印级别
 输出参数  : 无
 返 回 值  : 打印级别
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年07月04日
    作    者   : 周明发 00145324
    修改内容   : 新生成函数

*****************************************************************************/
int usb_ashell_dump(void)
{
    struct ashell_ctx_t *ash_ctx = &g_ashell_ctx;

    printk("g_ashell_ctx:0x%p \n", &g_ashell_ctx);
    printk("tty       :0x%p  \n",  ash_ctx->tty);
    printk("acm_ctx   :0x%p  \n",  ash_ctx->acm_ctx);
    printk("lock      :0x%p  \n",  &ash_ctx->lock);
    printk("enable    :0x%x  \n",  ash_ctx->enable);
    printk("port_open :0x%x  \n",  ash_ctx->port_open);
    printk("tx_idx    :0x%x  \n",  ash_ctx->tx_idx);
    printk("tx_work   :0x%p  \n",  &ash_ctx->tx_work);
    printk("tx_mem    :0x%p  \n",  &ash_ctx->tx_mem[0]);
    printk("port_console:0x%p\n",  &ash_ctx->port_console);
    return SHELL_OK;
}

int usb_cshell_dump(void)
{
    struct cshell_ctx_t *csh_ctx = &g_cshell_ctx;
    struct shell_mem_info *mem_tmp = NULL;
    int i = 0;

    printk("g_cshell_ctx:0x%p \n",  &g_cshell_ctx);
    printk("icc_chan_id :0x%x \n",  csh_ctx->icc_chan_id);
    printk("icc_opened  :0x%x \n",  csh_ctx->icc_opened);
    printk("icc_fd      :0x%x \n",  csh_ctx->icc_fd);
    printk("usb_fd      :0x%x \n",  csh_ctx->usb_fd);
    printk("icc_valid   :0x%x \n",  csh_ctx->icc_valid);
    printk("usb_valid   :0x%x \n",  csh_ctx->usb_valid);
    printk("icc_lock    :0x%p \n",  &csh_ctx->icc_lock);
    printk("usb_lock    :0x%p \n",  &csh_ctx->usb_lock);
    printk("icc_rx_buf  :0x%p \n",  csh_ctx->icc_rx_buf);
    printk("usb_rx_buf  :0x%p \n",  csh_ctx->usb_rx_buf);
    printk("icc_tx_work :0x%p \n",  &csh_ctx->icc_tx_work);
    printk("usb_tx_work :0x%p \n",  &csh_ctx->usb_tx_work);
    printk("icc_tx_idx  :0x%x \n",  csh_ctx->icc_tx_idx);
    printk("usb_tx_idx  :0x%x \n",  csh_ctx->usb_tx_idx);
    printk("icc_tx_mem  :0x%p \n",  &csh_ctx->icc_tx_mem[0]);
    printk("usb_tx_mem  :0x%p \n",  &csh_ctx->usb_tx_mem[0]);

    /* memory for usb tx */
    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->usb_tx_mem[i];
        printk("usb_tx_mem[%d]:0x%p, next[0x%p], pbuf[0x%x] \n",
                i, mem_tmp, mem_tmp->next, mem_tmp->pbuf);
        printk("vbuf[0x%p], used[%d], free[%d], idx[%d]\n",  mem_tmp->vbuf,
                mem_tmp->used, mem_tmp->free, mem_tmp->idx);
    }

    /* memory for usb tx */
    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++) {
        mem_tmp = &csh_ctx->icc_tx_mem[i];
        printk("icc_tx_mem[%d]:0x%p, next[0x%p], pbuf[0x%x] \n",
                i, mem_tmp, mem_tmp->next, mem_tmp->pbuf);
        printk("vbuf[0x%p], used[%d], free[%d], idx[%d]\n",  mem_tmp->vbuf,
                mem_tmp->used, mem_tmp->free, mem_tmp->idx);
    }

    return SHELL_OK;
}

#ifndef _DRV_LLT_
IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_CSHELL_START, cshell_ccore_start,
                    IFC_INVAR, void *, arg, 0,
                    IFC_INCNT, int, len, 0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



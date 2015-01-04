/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : usb_api.h
  版 本 号   : 初稿
  生成日期   : 2012年9月15日
  最近修改   :
  功能描述   : usb_api.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月15日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __USB_API_H__
#define __USB_API_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define USB_API_DBG printk

#define M_ZERO          0x0001

#define USB_TTY_NAME0                 "ttyGS0"
#define USB_TTY_NAME1                 "ttyGS1"
#define USB_TTY_NAME2                 "ttyGS2"
#define USB_TTY_NAME3                 "ttyGS3"
#define USB_TTY_NAME4                 "ttyGS4"
#define USB_TTY_NAME5                 "ttyGS5"
#define USB_TTY_NAME6                 "ttyGS6"

#define USB_TTY_ASH_NAME              USB_TTY_NAME0
#define USB_TTY_AT_NAME               USB_TTY_NAME1
#define USB_TTY_CTRL_NAME             USB_TTY_NAME2
#define USB_TTY_OM_NAME               USB_TTY_NAME3
#define USB_TTY_CSH_NAME              USB_TTY_NAME4
#define USB_TTY_LTEOM_NAME            USB_TTY_NAME5
#define USB_TTY_GPS_NAME              USB_TTY_NAME6

#define USB_ACM_STATUS_NOTIFIER       0xA3

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
enum usb_tty_type {
    USB_TTY_ASH_TYPE = 0,
    USB_TTY_AT_TYPE,
    USB_TTY_CTRL_TYPE,
    USB_TTY_OM_TYPE,
    USB_TTY_CSH_TYPE,
    USB_TTY_LTEOM_TYPE,
    USB_TTY_GPS_TYPE,
    USB_TTY_RESERVED_TYPE
};

enum usb_tty_index {
    USB_TTY_ASH_INDEX = 0,
    USB_TTY_AT_INDEX,
    USB_TTY_CTRL_INDEX,
    USB_TTY_OM_INDEX,
    USB_TTY_CSH_INDEX,
    USB_TTY_LTEOM_INDEX,
    USB_TTY_GPS_INDEX,
    USB_TTY_RESERVED_INDEX
};

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct PNP_CALLBACK_STACK
{
    void (*pCallback)(void);
    struct PNP_CALLBACK_STACK *pPre;
} PNP_CALLBACK_STACK;

struct usb_tty_t {
    enum usb_tty_index  index;
    enum usb_tty_type   type;
    char                *name;
};

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
int acm_handle_command(int cmd, int interface, char *buf, int size);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of usb_api.h */

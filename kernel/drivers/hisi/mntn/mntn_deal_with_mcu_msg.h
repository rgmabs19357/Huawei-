/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : mntn_deal_with_mcu_msg.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2013年5月4日
  最近修改   :
  功能描述   : mntn_deal_with_mcu_msg.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月4日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include <linux/kernel.h>

#ifndef __MNTN_DEAL_WITH_MCU_MSG_H__
#define __MNTN_DEAL_WITH_MCU_MSG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*#define MNTN_DEBUG*/

#define PRINT_LEV KERN_INFO

#define DATA_SIZE_IN_MSG_HEAD   4   /* 消息头为数据分配4字节，用于4字节对齐 */

#define DATA_MAX_LEN  (50)
#define MNTN_BUFF_SIZE   (0x200)    /* 乒乓buffer，每个buff大小定为512字节 */

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum
{
    TP_MODULE_PRINT_ID,                //touchpad
    LS_MODULE_PRINT_ID,
    GS_MODULE_PRINT_ID,
    SHL_MODULE_PRINT_ID,                //shell
    PRT_MODULE_PRINT_ID,               //print
    URT_MODULE_PRINT_ID,               //uart
    I2C_MODULE_PRINT_ID,              //i2c
    MB_MODULE_PRINT_ID,               //mailbox
    SOFTIMER_MODULE_PRINT_ID,         //softtimer
    EXC_MODULE_PRINT_ID,              //exc
    HUTAF_MODULE_PRINT_ID,            //hutaf
    PWC_MODULE_PRINT_ID,              //pwrctrl
    PMUSSI_MODULE_PRINT_ID,
    GPIO_MODULE_PRINT_ID,
    MNTN_MODULE_PRINT_ID,
    MCU_MAX_PRINT_ID
}MCU_MODULE_PRINT_ID;

typedef enum
{
    ID_MCU_DATA_EVENT = 0x0,     /* 事件上报 */
    ID_MCU_DATA_TRACE,           /* 普通Trace */
    ID_MCU_DATA_DEBUG,           /* 为实现在规定时间内至少发送一次的填充数据 */
    ID_MCU_DATA_TYPE_BUTT
} DATA_TYPE;

typedef enum
{
    /* 抬高频率 */
    ID_MCU_EVENT_DFS_UP     =   0,

    /* 降低频率 */
    ID_MCU_EVENT_DFS_DOWN   =   1,

    /* 上电 */
    ID_MCU_EVENT_POWER_ON   =   2,

    /* 下电 */
    ID_MCU_EVENT_POWER_OFF  =   3,

    ID_MCU_EVENT_TYPE_BUTT
} EVENT_TYPE;


typedef enum
{
    /* DFS及Core0上下电受MCU控制 */
    ID_MCU_ADJUST_ACPU0     =   0,

    /* DFS及上下电受MCU控制 */
    ID_MCU_ADJUST_CCPU      =   1,

    /* DFS受MCU控制 */
    ID_MCU_ADJUST_GPU       =   2,

    /* 下电受MCU控制 */
    ID_MCU_ADJUST_HIFI      =   3,

    /* DFS受MCU控制 */
    ID_MCU_ADJUST_DDR       =   4,

    ID_MCU_ADJUST_MODULE_BUTT
} MODULE_TYPE;


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct
{
    u32              ulTimeStamp;    /* 时间戳，填写当前的Counter值 */
    u16              enEventType;    /* MCU调节事件类型 EVENT_TYPE枚举 */
    u16              enModule;       /* MCU调节模块类型 MODULE_TYPE枚举 */
    u32              ulPreVAl;       /* 对DFS有效，指示调节前的频率 */
    u32              ulCurVal;       /* 对DFS有效，指示调节后的当前频率 */
} MCU_EVENT;

/* 单元数据格式，发往A核 */
typedef struct
{
    u32                 ulTimeStemp;    /* 时间戳 */
    u16                 enDataType;     /* 数据类型 DATA_TYPE枚举 */
    u16                 enPrintModule;  /* 打印模块 MCU_MODULE_PRINT_ID枚举 */
    u32                 ulLength;       /* 该项数据的长度 单位:字节 */
    u8                  data[DATA_SIZE_IN_MSG_HEAD];        /* data长度由usLength决定 */
} MCU_TO_ACPU_MSG;


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

extern s32 mntn_init(void);
extern void mntn_deal_with_mcu_mail(void * UserHandle, void * MailHandle, u32 ulMailLen);
extern s32 mntn_deal_with_msg(u8* data, u32 enDataType, u32 ulTimeStemp);
extern void RunMcuCmd(char* cmd);
extern long aprintk(char* str, int len);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mntn_deal_with_mcu_msg.h */

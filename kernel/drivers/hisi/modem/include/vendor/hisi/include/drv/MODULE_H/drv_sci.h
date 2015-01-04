/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_sci.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_sci.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_SCI_H__
#define __DRV_SCI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1
} SCI_DETECT_STATE;

/*for dsda*/
typedef enum
{
    RF_ID0 = 0,
    RF_ID1 = 1,
    RF_ID_BUTTOM
}RF_ID;

/*for reset mode*/
typedef enum
{
    WARM_RESET = 0, /*热复位*/
    COLD_RESET = 1, /*冷复位*/
    RESET_MODE_BUTTOM
}RESET_MODE;

/*for protocol mode*/
typedef enum
{
    T0_PROTOCOL_MODE = 0,          /*T=0*/
    T1_PROTOCOL_MODE = 1,          /*T=1*/
    PROTOCOL_MODE_BUTTOM
}PROTOCOL_MODE;

/*for EDC mode*/
typedef enum
{
    T1_ERR_DETECT_MODE_LRC = 0, /*LRC*/
    T1_ERR_DETECT_MODE_CRC = 1, /*CRC*/
    T1_ERR_DETECT_MODE_BUTTOM
}T1_ERR_DETECT_MODE;


/* 上层使用到的SCI特殊的返回值 */
#define SCI_CARD_BUSY       (1)
#define SCI_VLTG_HIGH       (1)

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
/*for ATR info*/
typedef struct {
    PROTOCOL_MODE      Tbyte;   
    BSP_U32            valIFSC;
    BSP_U32            valIFSD;
    T1_ERR_DETECT_MODE errDetectMode;
}SCI_ATRInfo;

/*for sci record info*/
typedef struct stSciRecordInfo{
    BSP_U16            cardClass;         /*卡电压类型:1800或3000*/
    BSP_U16            ATRlen;            /*ATR数据实际长度*/
    BSP_U8             ATRData[40];       /*ATR数据记录，不超过40个字节*/
    BSP_U32            SciRegData[36];    /*SCI所有寄存器记录*/
    BSP_U8             SimRecordData[72]; /*和卡交互的最后8条数据，每条不超过9个字节*/
    BSP_U32            SciEvent[32];      /*SCI 底层事件最后8条记录*/
}SCI_RECORD_INFO;


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
/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_ERRNO
*
* 功能描述  : 本接口用于获取SCI驱动的错误号
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : SCI驱动的错误号
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_GetErrno(BSP_VOID);
BSP_S32 I1_BSP_SCI_GetErrno(BSP_VOID);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_GET_ERRNO()    I1_BSP_SCI_GetErrno()
#else
#define DRV_USIMMSCI_GET_ERRNO()    BSP_SCI_GetErrno()
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RST
*
* 功能描述  : 本接口用于复位SCI（Smart Card Interface）驱动和USIM（Universal
*           Subscriber Identity Module）卡
*
* 输入参数  : RESET_MODE enResetMode
              WARM_RESET:热复位
              CODE_RESET:冷复位

* 输出参数  : 无
*
* 返 回 值  : OK  复位成功
*
*
*****************************************************************************/
BSP_U32 BSP_SCI_Reset(RESET_MODE enResetMode);
BSP_U32 I1_BSP_SCI_Reset(RESET_MODE enResetMode);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_RST(enResetMode)    I1_BSP_SCI_Reset(enResetMode)
#else
#define DRV_USIMMSCI_RST(enResetMode)    BSP_SCI_Reset(enResetMode)
#endif

/********************************************************************************************************************
 函 数 名  : DRV_USIMMSCI_GET_CARD_STAU
 功能描述  : 本接口用于获得卡当前的状态，目前LTE提供接口参数类型不一致
 输入参数  : 无。
 输出参数  :
 返 回 值  : OK:  卡处于Ready；
             ERROR：卡未处于Ready。
             SCI_CARD_BUSY:卡处于busy状态
 注意事项  ：有效调用BSP_SCI_Reset()函数后，再调用此函数。
********************************************************************************************************************/
BSP_S32 BSP_GUSCI_GetCardStatus(BSP_VOID);
BSP_S32 I1_BSP_GUSCI_GetCardStatus(BSP_VOID);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_GET_CARD_STAU()    I1_BSP_GUSCI_GetCardStatus()
#else
#define DRV_USIMMSCI_GET_CARD_STAU()    BSP_GUSCI_GetCardStatus()
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_SND_DATA
*
* 功能描述  : 本接口用于发送一段数据到USIM卡
*
* 输入参数  : BSP_U32 u32DataLength 发送数据的有效长度。取值范围1～256，单位为字节
*             BSP_U8 *pu8DataBuffer 发送数据所在内存的首地址，如是动态分配，调用接口
*                                   后不能立即释放，依赖于硬件发完数据
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_SendData(BSP_U32 u32DataLength, BSP_U8 *pu8DataBuffer);
BSP_S32 I1_BSP_SCI_SendData(BSP_U32 u32DataLength, BSP_U8 *pu8DataBuffer);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_SND_DATA(u32DataLength, pu8DataBuffer)    I1_BSP_SCI_SendData(u32DataLength, pu8DataBuffer)
#else
#define DRV_USIMMSCI_SND_DATA(u32DataLength, pu8DataBuffer)    BSP_SCI_SendData(u32DataLength, pu8DataBuffer)
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_RCV
*
* 功能描述  : 本接口用于USIM Manager读取来自SCI Driver的卡返回数据
*             该接口为阻塞接口，只有SCI接收到足够的数据量后才会返回；
*             该接口的超时门限为1s
*
* 输入参数  : BSP_U32 u32DataLength USIM Manager欲从SCI Driver读取的数据长度。
* 输出参数  : BSP_U8 *pu8DataBuffer USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
* 返 回 值  : OK/ERROR
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_ReceiveSync(BSP_U32 u32Length, BSP_U8 *pu8Data);
BSP_S32 I1_BSP_SCI_ReceiveSync(BSP_U32 u32Length, BSP_U8 *pu8Data);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_RCV(u32Length, pu8Data)    I1_BSP_SCI_ReceiveSync(u32Length, pu8Data)
#else
#define DRV_USIMMSCI_RCV(u32Length, pu8Data)    BSP_SCI_ReceiveSync(u32Length, pu8Data)
#endif

/*************************************************************************************
* 函 数 名  : DRV_USIMMSCI_GET_ATR
*
* 功能描述  : 本接口用于将Driver层缓存的ATR数据和数据个数返回给USIM Manager层
*
* 输入参数  : BSP_VOID
* 输出参数  : unsigned long *u8DataLength  Driver读取的ATR数据长度，返回给USIM Manager。
*                                   取值范围0～32，单位是字节
*             BSP_U8 *pu8ATR          USIM Manager指定的Buffer，SCI Driver将ATR
*                                   数据拷贝到本Buffer。一般为操作系统函数动态分配
*                                   或者静态分配的地址
*             SCI_ATRInfo *sciATRInfo 用于存储底软解析过的ATR信息
*
*
*
* 返 回 值  : OK/ERROR
*
*
************************************************************************************/
BSP_S32 BSP_SCI_GetATR(unsigned long *u32DataLength,BSP_U8 *pu8ATR,SCI_ATRInfo *sciATRInfo);
BSP_S32 I1_BSP_SCI_GetATR(unsigned long *u32DataLength,BSP_U8 *pu8ATR,SCI_ATRInfo *sciATRInfo);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_GET_ATR(u32DataLength, pu8ATR,sciATRInfo)    I1_BSP_SCI_GetATR(u32DataLength, pu8ATR,sciATRInfo)
#else
#define DRV_USIMMSCI_GET_ATR(u32DataLength, pu8ATR,sciATRInfo)    BSP_SCI_GetATR(u32DataLength, pu8ATR,sciATRInfo)
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_CLASS_SWITCH
*
* 功能描述  : 本接口用于支持PS对卡的电压类型进行切换，从1.8V切换到3V
*
* 输入参数  : BSP_VOID
* 输出参数  : 无
*
* 返 回 值  :  OK    当前电压不是最高的，进行电压切换操作
*              ERROR 切换失败
*              SCI_VLTG_HIGH   当前电压已经是最高电压，没有进行电压切换
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_ClassSwitch(BSP_VOID);
BSP_S32 I1_BSP_SCI_ClassSwitch(BSP_VOID);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_CLASS_SWITCH()    I1_BSP_SCI_ClassSwitch()
#else
#define DRV_USIMMSCI_CLASS_SWITCH()    BSP_SCI_ClassSwitch()
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_TM_STOP
*
* 功能描述  : 本接口用于支持PS关闭SIM卡时钟
*
* 输入参数  :
*           SCI_CLK_STOP_TYPE_E enTimeStopCfg 时钟停止模式
*
* 输出参数  : 无
*
 * 返 回 值  : 无
*
*****************************************************************************/
BSP_VOID BSP_SCI_TimeStop(BSP_U32 ulStopType);
BSP_VOID I1_BSP_SCI_TimeStop(BSP_U32 ulStopType);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_TM_STOP(ulStopType)    I1_BSP_SCI_TimeStop(ulStopType)
#else
#define DRV_USIMMSCI_TM_STOP(ulStopType)    BSP_SCI_TimeStop(ulStopType)
#endif

/*****************************************************************************
* 函 数 名  : DRV_USIMMSCI_DEACT
*
* 功能描述  : 本接口用于对SIM卡的去激活操作
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_U32 BSP_SCI_Deactive(BSP_VOID);
BSP_U32 I1_BSP_SCI_Deactive(BSP_VOID);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_DEACT()    I1_BSP_SCI_Deactive()
#else
#define DRV_USIMMSCI_DEACT()    BSP_SCI_Deactive()
#endif

/*****************************************************************************
* 函 数 名  : DRV_PCSC_GET_CLK_FREQ
*
* 功能描述  : 本接口用于获取当前SIM卡时钟频率
*
* 输入参数  : 无
*
* 输出参数  : unsigned long *pLen   时钟频率数据的长度
*             BSP_U8 *pBuf    时钟频率数据
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetClkFreq(unsigned long *pLen, BSP_U8 *pBuf);
BSP_U32 I1_BSP_SCI_GetClkFreq(unsigned long *pLen, BSP_U8 *pBuf);
#if defined(INSTANCE_1)
#define DRV_PCSC_GET_CLK_FREQ(pLen, pBuf)    I1_BSP_SCI_GetClkFreq(pLen, pBuf)
#else
#define DRV_PCSC_GET_CLK_FREQ(pLen, pBuf)    BSP_SCI_GetClkFreq(pLen, pBuf)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_GetBaudRate
*
* 功能描述  : 本接口用于获取当前SIM卡时钟频率
*
* 输入参数  : 无
*
* 输出参数  : unsigned long *pLen   波特率数据的长度
*             BSP_U8 *pBuf    波特率数据
*
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetBaudRate(unsigned long *pLen, BSP_U8 *pBuf);
BSP_U32 I1_BSP_SCI_GetBaudRate(unsigned long *pLen, BSP_U8 *pBuf);
#if defined(INSTANCE_1)
#define DRV_PCSC_GET_BAUD_RATE(pLen, pBuf)    I1_BSP_SCI_GetBaudRate(pLen, pBuf)
#else
#define DRV_PCSC_GET_BAUD_RATE(pLen, pBuf)    BSP_SCI_GetBaudRate(pLen, pBuf)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_GetPCSCParameter
*
* 功能描述  : 本接口用于获取当前SIM卡的PCSC相关参数
*
* 输入参数  : 无
*
* 输出参数  : BSP_U8 *pBuf    PCSC相关参数
*
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_U32 BSP_SCI_GetPCSCParameter(BSP_U8 *pBuf);
BSP_U32 I1_BSP_SCI_GetPCSCParameter(BSP_U8 *pBuf);
#if defined(INSTANCE_1)
#define DRV_PCSC_GET_SCI_PARA(pBuf)    I1_BSP_SCI_GetPCSCParameter(pBuf)
#else
#define DRV_PCSC_GET_SCI_PARA(pBuf)    BSP_SCI_GetPCSCParameter(pBuf)
#endif

/*****************************************************************************
 函 数 名  : DRV_USIMMSCI_RECORD_DATA_SAVE
 功能描述  : 本接口用于获取当前SIM卡交互数据。属于异常处理模块，V7先打桩
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 无
 注意事项  ：
*****************************************************************************/
/*extern int BSP_USIMMSCI_STUB(void);*/
BSP_VOID BSP_SCI_RecordDataSave(BSP_VOID);
BSP_VOID I1_BSP_SCI_RecordDataSave(BSP_VOID);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_RECORD_DATA_SAVE()       I1_BSP_SCI_RecordDataSave()
#else
#define DRV_USIMMSCI_RECORD_DATA_SAVE()       BSP_SCI_RecordDataSave()
#endif

typedef void (*OMSCIFUNCPTR)(unsigned int ulVal);

/*****************************************************************************
* 函 数 名  : BSP_SCIFuncRegister
*
* 功能描述  : 本接口用于注册OAM的回调函数
*
* 输入参数  : omSciFuncPtr
* 输出参数  : 无
*
* 返 回 值  : 无
*
*
*****************************************************************************/
BSP_VOID BSP_SCIFuncRegister(OMSCIFUNCPTR omSciFuncPtr);
BSP_VOID I1_BSP_SCIFuncRegister(OMSCIFUNCPTR omSciFuncPtr);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    I1_BSP_SCIFuncRegister(omSciFuncPtr)
#else
#define DRV_USIMMSCI_FUNC_REGISTER(omSciFuncPtr)    BSP_SCIFuncRegister(omSciFuncPtr)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_SetBWT
*
* 功能描述  : 本接口用于配置块等待时间
*
* 输入参数  : BSP_U32 nBWT :配置超时时间为BWT的nBWT倍
*
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_S32 BSP_SCI_SetBWT(BSP_U32 nBWT);
BSP_S32 I1_BSP_SCI_SetBWT(BSP_U32 nBWT);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_SETBWT(nBWT)    I1_BSP_SCI_SetBWT(nBWT)
#else
#define DRV_USIMMSCI_SETBWT(nBWT)    BSP_SCI_SetBWT(nBWT)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_Protocol_Switch
*
* 功能描述  : 本接口用于通知底软进行T=0和T=1协议类型切换
*
* 输入参数  : RESET_MODE enSIMProtocolMode:需要切换为的协议类型
*
* 输出参数  : 无
*
* 返 回 值  : OK/ERROR
*
*****************************************************************************/
BSP_S32 BSP_SCI_Protocol_Switch(PROTOCOL_MODE enSIMProtocolMode);
BSP_S32 I1_BSP_SCI_Protocol_Switch(PROTOCOL_MODE enSIMProtocolMode);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_PROTOCOL_SWITCH(enSIMProtocolMode)    I1_BSP_SCI_Protocol_Switch(enSIMProtocolMode)
#else
#define DRV_USIMMSCI_PROTOCOL_SWITCH(enSIMProtocolMode)    BSP_SCI_Protocol_Switch(enSIMProtocolMode)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_BLK_Receive
* 功能描述  : 本接口用于在T=1时USIM Manager读取来自SCI Driver的卡返回数据；
*             如果出现BWT超时，在数据读取时返回一个超时的值SCI_TIMEOUT
*
* 输入参数  : 无
* 输出参数  : BSP_U8 *pu8Data USIM Manager指定的Buffer，SCI Driver将数据拷贝到本Buffer。
              BSP_U32 *pulLength SCI Driver接收到的数据长度。

* 返 回 值  : OK : 0
              ERROR : -1
              SCI_TIMEOUT : 1
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_BLK_Receive(BSP_U8 *pu8Data,BSP_U32 *pulLength);
BSP_S32 I1_BSP_SCI_BLK_Receive(BSP_U8 *pu8Data,BSP_U32 *pulLength);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_BLK_RCV(pu8Data,pulLength)    I1_BSP_SCI_BLK_Receive(pu8Data,pulLength)
#else
#define DRV_USIMMSCI_BLK_RCV(pu8Data,pulLength)    BSP_SCI_BLK_Receive(pu8Data,pulLength)
#endif

/*****************************************************************************
* 函 数 名  : BSP_SCI_RecordLog_Read
* 功能描述  : 本接口用于读取SIM卡log数据，数据内容参见结构体SCI_RECORD_INFO
*
* 输入参数  : BSP_U32 ulMaxLength 指定传入buff的最大长度(不可小于SCI_RECORD_INFO长度)
* 输出参数  : BSP_U8 *pucDataBuff USIM Manager指定的Buffer，
*             SCI Driver将log信息拷贝到本Buffer。
*             BSP_U32 *pulLength SCI Driver拷贝到pucDataBuff的长度
*
* 返 回 值  : OK : 0
*             ERROR : -1
*
*
*
*****************************************************************************/
BSP_S32 BSP_SCI_RecordLog_Read(BSP_U8 *pucDataBuff,BSP_U32 *pulLength,BSP_U32 ulMaxLength);
BSP_S32 I1_BSP_SCI_RecordLog_Read(BSP_U8 *pucDataBuff,BSP_U32 *pulLength,BSP_U32 ulMaxLength);
#if defined(INSTANCE_1)
#define DRV_USIMMSCI_RECORDLOG_READ(pucDataBuff,pulLength,ulMaxLength)    I1_BSP_SCI_RecordLog_Read(pucDataBuff,pulLength,ulMaxLength)
#else
#define DRV_USIMMSCI_RECORDLOG_READ(pucDataBuff,pulLength,ulMaxLength)    BSP_SCI_RecordLog_Read(pucDataBuff,pulLength,ulMaxLength)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_sci.h */


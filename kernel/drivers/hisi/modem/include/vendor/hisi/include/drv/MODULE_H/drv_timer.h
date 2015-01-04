/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_timer.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_timer.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__
#include "drv_global.h"

#define BSP_BBP_POWER_DOWN       0xFFFF

/* 下行业务数据DMA搬移完成中断,此中断只对应Modem核*/
typedef BSP_VOID (*BSPBBPIntDlTbFunc)(BSP_VOID);
/* BBP子帧中断处理函数,此中断只对应Modem核*/
typedef BSP_VOID (*BSPBBPIntTimerFunc)(BSP_VOID);
/* BBP TDS中断处理函数,此中断只对应Modem核 */
typedef BSP_VOID (*BSPBBPIntTdsFunc)(BSP_VOID);

typedef enum
{
    PHY_LOAD_MODE_GU,     /* 加载GUDSP,目前GUPHY移到ARM,暂不实现,该位预留 */
    PHY_LOAD_MODE_LTE,    /* 加载LTEDSP */
    PHY_LOAD_MODE_TDS,    /* 加载TDSDSP */
    PHY_LOAD_MODE_CDMA,   /* 加载CDMADSP */
    PHY_LOAD_MODE_BUTTOM
}PHY_LOAD_MODE_E;


/*****************************************************************************
* 函 数 名  : BSP_LPS_GetTa
*
* 功能描述  : 被LPS调用，查看上行子帧头相对系统子帧头的提前量
*
* 输入参数  :无
* 输出参数  :无
*
* 返 回 值  : BSP_U16
*
*****************************************************************************/
extern BSP_U16 BSP_LPS_GetTa(void);
#define DRV_LPS_GET_TA() BSP_LPS_GetTa()

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTimerRegCb
*
* 功能描述  : 被PS调用，用来向底软注册1ms定时中断的回调
*
* 输入参数  :
* 输出参数  :无
*
* 返 回 值  : VOID
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntTimerRegCb(BSPBBPIntTimerFunc pFunc);
#define DRV_BBP_INT_TIMER_REG_CB(pFunc) BSP_BBPIntTimerRegCb(pFunc)

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTimerClear
*
* 功能描述  : 被PS调用，用来清除1ms定时中断
*
* 输入参数  : 无
* 输出参数  :无
*
* 返 回 值  : VOID
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntTimerClear(void);
#define DRV_BBP_INT_TIMER_CLEAR() BSP_BBPIntTimerClear()

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTimerEnable
*
* 功能描述  : 被PS调用，用来打开1ms定时中断
*
* 输入参数  : 无
* 输出参数  :无
*
* 返 回 值  : VOID
*
*****************************************************************************/
extern BSP_S32 BSP_BBPIntTimerEnable(void);
#define DRV_BBP_INT_TIMER_ENABLE() BSP_BBPIntTimerEnable()

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTimerDisable
*
* 功能描述  : 被PS调用，用来关闭1ms定时中断
*
* 输入参数  : 无
* 输出参数  :无
*
* 返 回 值  : VOID
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntTimerDisable(void);
#define DRV_BBP_INT_TIMER_DISABLE() BSP_BBPIntTimerDisable()

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTimerSwitchStatus
* 功能描述  : 用于获取lte 1ms定时器中断使能/开关状态
* 输入参数  : 无
* 输出参数  : BSP_BOOL  定时器中断开关状态(1:中断使能、0:中断去时能,BBP禁止访问时默认中断去使能)
* 返 回 值  : BSP_OK    LTE-BBP处于允许访问状态
*             BSP_ERROR LTE-BBP处于禁止访问状态
*****************************************************************************/
BSP_S32 BSP_BBPIntTimerSwitchStatus(BSP_BOOL *pbStat);
#define DRV_BBP_INT_TIMER_SWITCH_STATUS(pbStat) BSP_BBPIntTimerSwitchStatus(pbStat)

/*****************************************************************************
 函 数 名  : BSP_BBP_Get32kMs
 功能描述  : 通过读取BBP系统时间转换成ms
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 系统时间对应的ms数
 调 用 者  : LPS
 修改记录  : 
*****************************************************************************/
BSP_U32 BSP_BBP_Get32kMs(BSP_VOID);
#define DRV_GET_32K_MS()    BSP_BBP_Get32kMs()

/*****************************************************************************
* 函 数 名  : BSP_BBPGetCurTime
*
* 功能描述  : 被PS调用，用来获取系统精确时间
*
* 输入参数  : 无
* 输出参数  : BSP_U32 u32CurTime:当前时刻
*
* 返 回 值  : BSP_OK : 获取成功
*                        BSP_ERR_INVALID_PARA  :获取失败
*
*****************************************************************************/
extern BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime);
#define DRV_BBP_GET_CUR_TIME(pCurTime) BSP_BBPGetCurTime(pCurTime)

/*****************************************************************************
 函 数 名  : DRV_GET_BBP_TIMER_VALUE
 功能描述  : 获取BBP定时器的值。用于OAM 时戳
 输入参数  : 无。
 输出参数  : pulHigh32bitValue:BBP定时器的值获取高32bit,本参数如为空，
                                                      则只返回低32bit的值
                            pulLow32bitValue:BBP定时器的值获取低 32bit,不能为空，否则会返回失败。
 返 回 值  : 0-成功
                       -1 -失败
*****************************************************************************/
extern int DRV_GET_BBP_TIMER_VALUE(unsigned int  *pulHigh32bitValue,  unsigned int  *pulLow32bitValue);

/*****************************************************************************
* 函 数 名  : BSP_BBPIntDlTbRegCb
*
* 功能描述  : 被PS调用，用来向底软注册下行数据DMA搬移完成中断的回调
*
* 输入参数  :
* 输出参数  :无
*
* 返 回 值  : VOID
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntDlTbRegCb(BSPBBPIntDlTbFunc pFunc);

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTdsTFRegCb
*
* 功能描述  : regist callback，被LPS调用
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 其它说明  : 无
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntTdsTFRegCb(BSPBBPIntTdsFunc pFunc);
#define DRV_BBP_INT_TDS_TF_REG_CB(pFunc) BSP_BBPIntTdsTFRegCb(pFunc)

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTdsTFEnable
*
* 功能描述  : enable tdstf，被LPS调用
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 其它说明  : 无
*
*****************************************************************************/
extern BSP_S32 BSP_BBPIntTdsTFEnable(BSP_VOID);
#define DRV_BBP_INT_TDS_TF_ENABLE() BSP_BBPIntTdsTFEnable()

/*****************************************************************************
* 函 数 名  : BSP_BBPIntTdsTFDisable
*
* 功能描述  : disable tdstf，被LPS调用
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 无
*
* 其它说明  : 无
*
*****************************************************************************/
extern BSP_VOID BSP_BBPIntTdsTFDisable(BSP_VOID);
#define DRV_BBP_INT_TDS_TF_DISABLE() BSP_BBPIntTdsTFDisable()

/*****************************************************************************
* 函 数 名  : BSP_GetSysFrame
*
* 功能描述  : get system frame num
*
* 输入参数  : 无
* 输出参数  :
*
* 返 回 值  : frame num/0xffff
*
*****************************************************************************/
extern BSP_U32 BSP_GetSysFrame(BSP_VOID);
#define DRV_GET_SYS_FRAME()   BSP_GetSysFrame()

/*****************************************************************************
* 函 数 名  : BSP_GetSysSubFrame
*
* 功能描述  : get sub system frame num
*
* 输入参数  : 无
* 输出参数  :
*
* 返 回 值  : frame num/0xffff
*
*****************************************************************************/
extern BSP_U32 BSP_GetSysSubFrame(BSP_VOID);
#define DRV_GET_SYS_SUB_FRAME()   BSP_GetSysSubFrame()

/*****************************************************************************
 函 数 名  : BSP_GetTdsSubFrame
 功能描述  : TDS子帧号获取保护接口
 输入参数  : 无。
 输出参数  : 无.
 返 回 值  : 如果1A下电返回0xFFFF，否则返回读取的子帧号取值.
 调 用 者  : TDS PS
 修改记录  :  
*****************************************************************************/
extern BSP_U16 BSP_GetTdsSubFrame(BSP_VOID);
#define DRV_GET_TDS_SUB_FRAME()   BSP_GetTdsSubFrame()

/*****************************************************************************
 函 数 名  : BSP_SetTdsSubFrameOffset
 功能描述  : TDS子帧号偏移设置保护接口
 输入参数  : usOffset 偏移值。
 输出参数  : 无.
 返 回 值  : 如果1A下电返回0xFFFF，否则返回BSP_OK,即0.
 调 用 者  : TDS PS
 修改记录  :  
*****************************************************************************/
extern BSP_U16 BSP_SetTdsSubFrameOffset(BSP_U16 usOffset);
#define DRV_SET_TDS_SUB_FRAME_OFFSET(usOffset)   BSP_SetTdsSubFrameOffset(usOffset)

/*****************************************************************************
 函 数 名  : BSP_GetTdsSleepTime
 功能描述  : TDS睡眠时长获取接口
 输入参数  : 无。
 输出参数  : 无.
 返 回 值  : TDS睡眠长度。
 调 用 者  : TDS PS
 修改记录  :  
*****************************************************************************/
extern BSP_U32 BSP_GetTdsSleepTime(BSP_VOID);
#define DRV_GET_TDS_SLEEP_TIME()   BSP_GetTdsSleepTime()

/*****************************************************************************
 函 数 名  : BSP_GetTdsClkSwitchStatus
 功能描述  : 判断当前BBE16时钟状态
 输入参数  : 无。
 输出参数  : 无.
 返 回 值  : BSP_FALSE  切换到系统时钟
             BSP_TRUE   切换到到32K
 调 用 者  : TDS PS
 修改记录  :  
*****************************************************************************/
extern BSP_S32 BSP_GetTdsClkSwitchStatus(BSP_VOID);
#define DRV_GET_TDS_CLK_STATUS()   BSP_GetTdsClkSwitchStatus()

/*****************************************************************************
 函 数 名  : BSP_GetSliceValue
 功能描述  : 获取Slice定时器的值。
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 定时器的值。
*****************************************************************************/
extern unsigned int BSP_GetSliceValue(BSP_VOID);
#define DRV_GET_SLICE()   BSP_GetSliceValue()

/*****************************************************************************
 函 数 名  : BSP_StartHardTimer
 功能描述  : 启动一个定时器的值。
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 定时器的值。
*****************************************************************************/
extern BSP_VOID BSP_StartHardTimer( BSP_U32 value );
#define DRV_STATR_HARD_TIMER(value)   BSP_StartHardTimer(value)

/*****************************************************************************
 函 数 名  : BSP_StartHardTimer
 功能描述  : 启动一个定时器的值。
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 定时器的值。
*****************************************************************************/
extern BSP_VOID BSP_StopHardTimer(BSP_VOID);
#define DRV_STOP_HARD_TIMER()   BSP_StopHardTimer()

/*****************************************************************************
 函 数 名  : BSP_GetHardTimerCurTime
 功能描述  : 获取一个定时器的剩余值。
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 定时器的剩余值。
*****************************************************************************/
extern BSP_U32 BSP_GetHardTimerCurTime(BSP_VOID);
#define DRV_GET_TIMER_CUR_TIME()   BSP_GetHardTimerCurTime()

/*****************************************************************************
 函 数 名  : BSP_ClearTimerINT
 功能描述  : 清除一个定时器的中断
 输入参数  : 无。
 输出参数  : 无
 返 回 值  : 定时器的剩余值。
*****************************************************************************/
extern BSP_VOID BSP_ClearTimerINT(BSP_VOID);
#define DRV_CLEAR_TIMER_INT()   BSP_ClearTimerINT()


/*****************************************************************************
* 函 数 名  : BSP_USRCLK_Connect
*
* 功能描述  : This routine specifies the interrupt service routine to be called
*             at each clock interrupt.  It does not enable usr clock interrupts.
*
* 输入参数  : FUNCPTR routine   routine to be called at each clock interrupt
              BSP_S32 arg           argument with which to call routine
              BSP_S32 s32UsrClkid      which user clock the interrup routine belongs to
* 输出参数  : 无
* 返 回 值  : OK, or ERROR if the routine cannot be connected to the interrupt.
*
*****************************************************************************/
extern BSP_S32  BSP_USRCLK_Connect(FUNCPTR routine, BSP_S32 arg, BSP_S32 s32UsrClkid);

/*****************************************************************************
* 函 数 名  : BSP_USRCLK_Disable
*
* 功能描述  : This routine disables user clock interrupts.
*
* 输入参数  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* 输出参数  : 无
* 返 回 值  : OK, or ERROR
*
*****************************************************************************/
extern BSP_S32   BSP_USRCLK_Disable (BSP_S32 s32UsrClkid);

/*****************************************************************************
* 函 数 名  : BSP_USRCLK_Enable
*
* 功能描述  : This routine enables user clock interrupts.
*
* 输入参数  : BSP_S32 s32UsrClkid  which user clock the interrup routine belongs to
* 输出参数  : 无
* 返 回 值  : OK, or ERROR
*
*****************************************************************************/
extern BSP_S32    BSP_USRCLK_Enable (BSP_S32 s32UsrClkid);

/*****************************************************************************
* 函 数 名  : BSP_USRCLK_RateSet
*
* 功能描述  : This routine sets the interrupt rate of the usr clock.
*
* 输入参数  : BSP_S32 ticksPerSecond   number of clock interrupts per second
              BSP_S32 s32UsrClkid         which user clock the interrup routine belongs to
* 输出参数  : 无
* 返 回 值  : OK, or ERROR if the tick rate is invalid or the timer cannot be set.
*
*****************************************************************************/
extern BSP_S32  BSP_USRCLK_RateSet(BSP_S32 ticksPerSecond, BSP_S32 s32UsrClkid);

typedef enum
{
    TIMER_CCPU_OSA_ID           = 0,         /*v3r3 ,v9r1 c核提供给osa的timer ID*/
    TIMER_CCPU_MSP_ID           = 1,
    TIMER_CCPU_APP_ID           = 2,
    TIMER_CCPU_SOFTTIMER_ID     = 3,         /* v3r3 ,v9r1 c核分配给软timer的ID */
    TIMER_DSP_TIMER1_ID         = 4,         /* v3r3 ,v9r1分配给DSP的timerID1 */
    TIMER_DSP_TIMER2_ID         = 5,         /*v3r3 , v9r1分配给DSP的timerID2 ,v3r3 为32k时钟，供低功耗使用*/
    TIMER_HIFI_TIMER1_ID        = 6,         /*v9r1 分配给HIFI的timerID1,v3r3分配给A核codec的的timer ID */
    TIMER_CCPU_DFS_ID           = 7,
    TIMER_CCPU_SYS_ID           = 8,         /* v3r3 ,v9r1分配给系统时钟的ID */
    TIMER_CCPU_AUX_ID           = 9,         /* v3r3 ,v9r1分配给系统辅助时钟的ID */
    TIMER_CCPU_DSP_DRX_PROT_ID  = 10,        /* 只有v9r1 sft和v9r1 bbit会用，分配给DSP */
    TIMER_CCPU_DRX_STAMP_ID     = 12,
    TIMER_HIFI_TIMER2_ID        = 13,
    TIMER_ALL_SLICE_ID          = 14,        /* A、C核共用的slicetimerID */
    TIMER_MCU_TIMER1_ID         = 15,        /* 预留给将来MCU使用 */
    TIMER_MCU_TIMER2_ID         = 16,        /* 预留给将来MCU使用 */
    TIMER_CCPU_CPUVIEW_ID       = 17,        /*提供给TTF使用*/
    TIMER_CCPU_DRX1_STABLE_ID   = 18,        /* v9r1分配给DRX1 TCXO稳定的时钟的ID */
    TIMER_CCPU_DRX2_STABLE_ID   = 19,        /* v9r1分配给DRX2 TCXO稳定的时钟的ID */
    TIMER_ACPU_SYSTEM_ID        = 20,        /* v3r3 ,v9r1分配给系统时钟的ID */
    TIMER_ACPU_FREE_RUN         = 21,        /* v3r3 ,v9r1分配给linux 自由时钟的ID */
    TIMER_ACPU_OSA_ID           = 22,        /*v3r3 ,v9r1 A核提供给osa的timer ID*/
    TIMER_ACPU_SOFTTIMER_ID     = 23,        /* v3r3 ,v9r1 A核分配给软timer的ID */
    TIMER_OM_TCXO_ID            = 24,        /* (已废弃)提供给OM 的高精度定时器,A核C核均提供 */
    TIMER_ACPU_APP_ID           = 25,        /* v9r1 v3r3 bbit使用 */
    TIMER_CCPU_DRX_TIMER_ID     = 26,        /* V3R3 v9r1 低功耗drx对齐特性使用 */
    TIMER_ACPU_IDLE_ID          = 27,        /* a核低功耗用,cpu idle */
    TIMER_ACPU_OM_TCXO_ID       = 28,        /* 为解决VOS_TIMER频繁调度的问题，分配该timer给OAM */
    TIMER_CCPU_G1PHY_DRX_ID     = 29,        /* 只有v9r1用，分配给DSP 用于drx规避方案 */
    TIMER_MCU_SYSTEM_ID         = 38,
    TIMER_MCU_SOFTTIMER_ID      = 39,
    TIMER_ID_MAX                = 40
} DRV_TIMER_ID;

typedef enum
{
    TIMER_ONCE_COUNT = 0,        /* 单次定时器模式 */
    TIMER_PERIOD_COUNT,          /* 周期定时器模式 */
    TIMER_COUNT_BUTT
}DRV_TIMER_MODE;

typedef enum
{
    TIMER_UNIT_MS = 0,           /* 0表示单位ms模式 */
    TIMER_UNIT_US,               /* 1表示单位us模式 */
    TIMER_UNIT_NONE,             /* 2表示单位1，即直接操作load寄存器模式  */
    TIMER_UNIT_BUTT
}DRV_TIMER_UNIT;

/*****************************************************************************
 函 数 名  : DRV_TIMER_START
 功能描述  : 封装给协议栈的用户时钟定时器启动函数
 输入参数  : usrClkId:使用DRV_TIMER_ID 提供的timerID
             routine:回调函数
             arg:回调参数
             timerValue:计数值
             mode:定时器工作模式，单次模式或周期模式，参见DRV_TIMER_MODE
             unitType: 0表示单位ms； 1表示单位us； 2表示单位1，即直接操作load寄存器模式
                unitType=0时, 频率为19.2MHz的timer  timerValue取值范围[1,223696]
                              频率为32KHz  的timer  timerValue取值范围[1,131071]
                unitType=1时, 频率为19.2MHz的timer  timerValue取值范围[1,223696]
                              频率为32KHz  的timer，可以正常启动，但因硬件限制，支持的最小刻度约为31us;
                                                    timerValue范围[1,31]，则延迟1us;
                                                              范围[32,131071]时，因实现上是用(timerValue*32768)/1000000来配定时器的count值，故无法区分31us和60us，依次类推
                unitType=2时, timerValue取值范围[1,0xFFFFFFFF]

 输出参数  : 无
 返 回 值  : int  0 启动成功； -1 启动失败
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   修改内容    : 新生成函数

 2.日    期   : 2013年5月21日
   修改内容   : 增加对32K时钟调用微秒接口的支持，只不过定时最小刻度约为31us

*****************************************************************************/
extern int DRV_TIMER_START
(
    unsigned int     usrClkId,
    FUNCPTR_1        routine,
    int              arg,
    unsigned int     timerValue,
    unsigned int     mode,
    unsigned int     unitType
);

/*****************************************************************************
 函 数 名  : DRV_TIMER_STOP
 功能描述  : 封装给协议栈的用户时钟定时器停止函数
 输入参数  : usrClkId:时钟ID,取值0~19
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年7月19日
   修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_TIMER_STOP(unsigned int usrClkId);

/*****************************************************************************
 函 数 名  : DRV_TIMER_GET_REST_TIME
 功能描述  : 获取定时器的剩余时间
 输入参数  : usrClkId:时钟ID,取值0~19
            unitType
            pRestTime
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史  :
 1.日    期   : 2012年7月19日
   修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_TIMER_GET_REST_TIME(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime);

/*****************************************************************************
* 函 数 名  : BSP_PWC_SetDrxTimerWakeSrc
* 功能描述  : 设置DRX timer 作为唤醒源
* 输入参数  :
* 输出参数  :
* 返 回 值   :
                v9r1 sft c核实现 a核打桩
                v9r1 bbit 硬件不支持，打桩
                v3r3 sft c核实现 a核打桩
*****************************************************************************/
extern void BSP_PWC_SetDrxTimerWakeSrc(void);
#define DRV_SET_DRX_TIMER_WAKE_SRC() BSP_PWC_SetDrxTimerWakeSrc()

/*****************************************************************************
* 函 数 名  : BSP_PWC_DelDrxTimerWakeSrc
* 功能描述  : 设置DRX timer 不作为唤醒源
* 输入参数  :
* 输出参数  :
* 返 回 值  :
                v9r1 sft c核实现 a核打桩
                v9r1 bbit 硬件不支持，打桩
                v3r3 sft c核实现 a核打桩
*****************************************************************************/
extern void BSP_PWC_DelDrxTimerWakeSrc(void);
#define DRV_DEL_DRX_TIMER_WAKE_SRC() BSP_PWC_DelDrxTimerWakeSrc()

/*****************************************************************************
 函 数 名  : DRV_GET_RTC_VALUE
 功能描述  : 读内rtc寄存器，获得当前RTC的值
 输入参数  : 无
 输出参数  : 无
 返回值    ：RTC值，单位s
 修改说明  :
             V9sft A、C核规格实现(A核在mach_info.c文件中，C核在BSP_TIMER.c文件中)
             V3sft A、C核打桩
*****************************************************************************/
unsigned int DRV_GET_RTC_VALUE(void);

/*****************************************************************************
 函 数 名  : DRV_GET_SLICE_VALUE
 功能描述  : 获得当前SLICE值
 输入参数  : 无
 输出参数  : 无
 返回值    ：SLICE
*****************************************************************************/
unsigned int DRV_GET_SLICE_VALUE(void);

#endif


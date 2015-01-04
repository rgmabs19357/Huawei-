/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_dpm.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_dpm.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_DPM_H__
#define __DRV_DPM_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))

/************************************************************************
 * FUNCTION
 *       pwrctrl_wifi_lowppwer_enter
 * DESCRIPTION
 *       pwrctrl_wifi_lowppwer_enter
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void pwrctrl_wifi_lowpower_enter(void);



/************************************************************************
 * FUNCTION
 *       pwrctrl_wifi_lowppwer_exit
 * DESCRIPTION
 *       pwrctrl_wifi_lowppwer_exit
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void pwrctrl_wifi_lowpower_exit(void);

/************************************************************************
 * FUNCTION
 *       pwrctrl_wifi_nolink_timer_set
 * DESCRIPTION
 *       pwrctrl_wifi_nolink_timer_set
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
int pwrctrl_wifi_nolink_timer_set(unsigned int time);

/************************************************************************
 * FUNCTION
 *       pwrctrl_usb_lowpower_enter
 * DESCRIPTION
 *       pwrctrl_usb_lowpower_enter
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void pwrctrl_usb_lowpower_enter(void);


/************************************************************************
 * FUNCTION
 *       pwrctrl_usb_lowpower_exit
 * DESCRIPTION
 *       pwrctrl_usb_lowpower_exit
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void pwrctrl_usb_lowpower_exit(void);

#endif
/*****************************************************************************
 函 数 名  : BSP_ONOFF_DrvPowerOff
 功能描述  : 单板直接下电
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
extern void DRV_POWER_OFF(void);


/*****************************************************************************
 函 数 名  : pwrctrl_wpa_pwr_up
 功能描述  : RF下电
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
extern void pwrctrl_wpa_pwr_up(void);
#define DRV_WPA_POWERUP()


#define PWRCTRL_GET_SUCCESS         (0x00)
#define PWRCTRL_GET_PARAINVALID     (0x01)
#define PWRCTRL_ONORLOCK            (0x10)
#define PWRCTRL_OFFORUNLOCK         (0x20)

typedef unsigned long (*pULULFUNCPTR)( unsigned long ulPara );

typedef struct
{
    pULULFUNCPTR pRestoreFunction;
    pULULFUNCPTR pEnableFunction;
    pULULFUNCPTR pDisableFunction;
    pFUNCPTR2    pDfsSetFunc;
    pULULFUNCPTR pDfsReleaseFunc;
}DPM_SLEEP_CALLBACK_STRU;

/*wangwei dfs*/
typedef  enum
{
    PWRCTRL_DFS_USB = 0,
    PWRCTRL_DFS_SD  = 1,
    PWRCTRL_DFS_PS1 = 2,
    PWRCTRL_DFS_HIFI = 3,  /*hifi*/
    PWRCTRL_DFS_BUTT
} PWC_DFS_ID_E;

typedef enum
{
    DFS_PROFILE_0 = 0,            /*频率级别1*/
    DFS_PROFILE_1 = 1,            /*频率级别2*/
    DFS_PROFILE_2 = 2,            /*频率级别3*/
    DFS_PROFILE_3 = 3,            /*频率级别4*/
    DFS_PROFILE_4 = 4,            /*频率级别5*/
    DFS_PROFILE_BUTT
} PWC_DFS_PROFILE_E;


typedef enum tagPWC_COMM_MODE_E
{
    PWC_COMM_MODE_GSM=0,
    PWC_COMM_MODE_WCDMA=1,
    PWC_COMM_MODE_LTE=2,
    PWC_COMM_MODE_TDS=3,
    PWC_COMM_MODE_BUTT
}PWC_COMM_MODE_E;

typedef enum tagPWC_COMM_MODULE_E
{
    PWC_COMM_MODULE_PA,
    PWC_COMM_MODULE_RF,
    PWC_COMM_MODULE_ABB,
    PWC_COMM_MODULE_BBE16,

    PWC_COMM_MODULE_BBP_DRX,  /*W:1A,2A,2C,2D,3*/
    PWC_COMM_MODULE_BBP_DPA,  /*W:1B*/
    PWC_COMM_MODULE_BBP_MEM,  /*W:2B*/

    PWC_COMM_MODULE_BUTT
}PWC_COMM_MODULE_E;


typedef enum tagPWC_COMM_STATUS_E
{
    PWRCTRL_COMM_ON = 0x10,
    PWRCTRL_COMM_OFF = 0x20,
    PWC_COMM_STATUS_BUTT
}PWC_COMM_STATUS_E;

typedef BSP_S32 (*PWC_TCXO_FUNCPTR)(int);

/* 睡眠投票ID */
typedef enum tagPWC_CLIENT_ID_E
{
    /*0x100*/
    PWRCTRL_SLEEP_SCI      = 0x100, /*drv*/
    PWRCTRL_SLEEP_SCI1,             /*drv*/
    PWRCTRL_SLEEP_DMA,              /*drv*/
    PWRCTRL_SLEEP_MEM,              /*drv,flash or emmc*/

    PWRCTRL_SLEEP_PS_G0,            /*oam*/
    PWRCTRL_SLEEP_PS_W0,            /*oam*/

    PWRCTRL_SLEEP_PS_G1,            /*oam*/
    PWRCTRL_SLEEP_PS_W1,            /*oam*/

    PWRCTRL_SLEEP_RNIC,             /*nas*/
    PWRCTRL_SLEEP_FTM,              /*nas*/
    PWRCTRL_SLEEP_FTM_1,            /*nas*/
    PWRCTRL_SLEEP_NAS_1,            /*nas*/
    PWRCTRL_SLEEP_NAS,              /*nas*/

    PWRCTRL_SLEEP_TLPS,             /*V7 TDS和LTE RTT共用*/
    PWRCTRL_SLEEP_OAM,              /*V7 MSP*/

    PWRCTRL_SLEEP_SD,               /*v3r3 a core*/
    PWRCTRL_SLEEP_BOOT,             /*v3r3 a core*/
    PWRCTRL_SLEEP_ACPU,             /*v3r3 c core*/
    PWRCTRL_SLEEP_HSIC,             /*v3r3 a core*/

    PWRCTRL_LIGHTSLEEP_WIFI,        /* HSIC不能掉电 */
    PWRCTRL_SLEEP_WIFI,             /*v3r3 a core*/
    PWRCTRL_SLEEP_USB,              /*v3r3 a core*/
    PWRCTRL_SLEEP_LCD,              /*v3r3 a core*/
    PWRCTRL_SLEEP_KEY,              /*v3r3 c&a core*/
    PWRCTRL_SLEEP_ACM,
    PWRCTRL_SLEEP_ICC,              /*v3r3 c&a core*/
    PWRCTRL_SLEEP_IFC,
    PWRCTRL_SLEEP_CHG,              /*v3r3 c core*/

    PWRCTRL_SLEEP_DSFLOW,           /*nas*/
    PWRCTRL_SLEEP_CDMAUART,         /*drv cdma uart 数传*/

    /* Test */
    PWRCTRL_TEST_DEEPSLEEP  = 0x11F,

    PWRCTRL_CLIENT_BUTT     = 0x120
} PWC_CLIENT_ID_E;


/*
 *  DFS Device QoS
 */
typedef enum tagDFS_QOS_ID_E
{
    DFS_QOS_ID_ACPU_MINFREQ_E = 0,  /*(0)*/
    DFS_QOS_ID_ACPU_MAXFREQ_E,      /*(1)*/
    DFS_QOS_ID_CCPU_MINFREQ_E,      /*(2)*/
    DFS_QOS_ID_CCPU_MAXFREQ_E,      /*(3)*/
    DFS_QOS_ID_DDR_MINFREQ_E,       /*(4)*/
    DFS_QOS_ID_DDR_MAXFREQ_E,       /*(5)*/
    DFS_QOS_ID_GPU_MINFREQ_E,       /*(6)*/
    DFS_QOS_ID_GPU_MAXFREQ_E,       /*(7)*/
    DFS_QOS_ID_BUS_MINFREQ_E,       /*(8)*/
    DFS_QOS_ID_BUS_MAXFREQ_E        /*(9)*/
}DFS_QOS_ID_E;


typedef struct
{
    PWRCTRLFUNCPTRVOID  pFuncDsIn;
    PWRCTRLFUNCPTRVOID  pFuncDsOut;
}PWC_DS_SOCP_CB_STRU;

typedef enum tagPWC_TEMP_PROTECT_E
{
    PWC_TEMP_OLED,
    PWC_TEMP_BATTERY,
	PWC_TEMP_L_PA,
    PWC_TEMP_G_PA,
    PWC_TEMP_W_PA,
    PWC_TEMP_SIM_CARD,
    PWC_TEMP_DCXO,
    PWC_TEMP_BUTT
}PWC_TEMP_PROTECT_E;

typedef struct
{
    PWRCTRLFUNCPTR drx_slow;
} PWC_SLEEP_CALLBACK_STRU;

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_DEEPSLEEP_FOREVER
 功能描述  : AARM CARM 下电接口
 输入参数  : None
 输出参数  : None
 返 回 值  : None

*****************************************************************************/
extern void DRV_PWRCTRL_DEEPSLEEP_FOREVER(void );

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEP_CALLBACK_REG
 功能描述  : 注册PWC函数给底软使用
 输入参数  : 待注册的函数
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int DRV_PWRCTRL_SLEEP_CALLBACK_REG(PWC_SLEEP_CALLBACK_STRU pCallback);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GET_TEMP
 功能描述  : 获取OLED、电池、GPA、WPA、SIM卡、DCXO的温度。
 输入参数  : enModule:PWC_TEMP_PROTECT_E
             hkAdcTable:电压温度换算表
 输出参数  : pslData:存储的电压转换为的温度值
 返 回 值  : HKADC_OK/HKADC_ERROR 。
*****************************************************************************/
/*V3R2 CS f00164371，这个接口暂时不隔离，因为SFT平台是返回0，实际回片需要实现，
需要使用CS_SFT宏进行区分，但是不同组件的CS_SFT宏不一定统一，所以不能直接屏蔽掉，
采用在接口代码内部进行隔离*/
extern BSP_S32 DRV_PWRCTRL_GET_TEMP(PWC_TEMP_PROTECT_E enModule, BSP_U16 *hkAdcTable,BSP_S32 *pslData);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC
 功能描述  : arm上下电功能，需要备份ahb数据，该接口申请数据保存地址和长度
 输入参数  : length     保存申请空间大小的指针
 输出参数  : 无
 返 回 值  : 申请空间的地址 。
*****************************************************************************/
/*V3R2 CS f00164371，这个接口暂时不隔离*/
extern void * DRV_PWRCTRL_AHB_BAK_ADDR_ALLOC(unsigned int * length);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GetCcpuLoadCB
 功能描述  : arm 提供给TTF的回调函数
 输入参数  : pFunc:TTF函数指针
 输出参数  : 无
 返 回 值  : 申请空间的地址 。
*****************************************************************************/
extern void DRV_PWRCTRL_GetCcpuLoadCB(PWRCTRLFUNCPTR pFunc );

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_GetCpuLoad
 功能描述  : arm cpu占有率查询函数
 输入参数  : 无
 输出参数  : ulAcpuLoad:Acpu占有率地址.
             ulCcpuLoad:Ccpu占有率地址.
 返 回 值  : 0/1 。
*****************************************************************************/
extern unsigned int DRV_PWRCTRL_GetCpuLoad(unsigned int *ulAcpuLoad,unsigned int *ulCcpuLoad);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PWRUP
 功能描述  : 通信模块控制电源上电接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_PWRUP (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PWRDOWN
 功能描述  : 通信模块控制电源下电接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_PWRDOWN (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PWRSTATUSGET
 功能描述  : 通信模块控制电源状态查询接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         上电
             PWRCTRL_COMM_OFF        下电
             RET_ERR                 状态查询失败
*****************************************************************************/
extern  BSP_S32 DRV_PWRCTRL_PWRSTATUSGET(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PLLENABLE
 功能描述  : 通信模块控制时钟使能接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_PLLENABLE (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PLLDISABLE
 功能描述  : 通信模块控制时钟关闭接口
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_PLLDISABLE (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_PLLSTATUSGET
 功能描述  : 通信模块控制时钟状态查询接口
 输入参数  : enCommMode     通信模式
             enCommModule   通信模块
             enCommCard     卡号
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         时钟打开
             PWRCTRL_COMM_OFF        时钟关闭
             RET_ERR                 查询失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_PLLSTATUSGET (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
* 函 数 名  : DRV_PWRCTRL_DSP_RESET
* 功能描述  : L模下DSP复位接口
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_VOID DRV_PWRCTRL_DSP_RESET(BSP_VOID);


/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_LOCK
 功能描述  : 外设禁止睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
extern BSP_U32 DRV_PWRCTRL_SLEEPVOTE_LOCK(PWC_CLIENT_ID_E enClientId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 功能描述  : 外设允许睡眠投票接口。
 输入参数  : enClientId:PWC_CLIENT_ID_E
 输出参数  : None
 返 回 值  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
extern BSP_U32 DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWC_CLIENT_ID_E enClientId);

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_SET_PRF_CCPU
Description:Set the System Min Profile
Input:      ulClientID: The Vote Module Client
            enProfile:  The Min Profile Value
Output:     None
Return:     The Vote Result
Others:
*****************************************************************************/
extern BSP_U32  DRV_PWRCTRL_DFS_SET_PRF_CCPU(PWC_DFS_ID_E ulClientID, PWC_DFS_PROFILE_E enProfile);

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_RLS_PRF_CCPU
Description:Release the Vote Result
Input:      ulClientID: The Vote Module Client
Output:     None;
Return:     The Vote Result
Others:
*****************************************************************************/
extern BSP_U32 DRV_PWRCTRL_DFS_RLS_PRF_CCPU(PWC_DFS_ID_E ulClientID);

/*****************************************************************************
Function:   DRV_PWRCTRL_SLEEP_IN_CB
Description:
Input:
Output:     None;
Return:
Others:
*****************************************************************************/
extern int DRV_PWRCTRL_SLEEP_IN_CB(PWC_DS_SOCP_CB_STRU stFunc);

/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_UsbLowPowerEnter
 功能描述  : USB进入低功耗接口
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
extern void DRV_PWRCTRL_USB_LOWPOWER_ENTER(void);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_USB_LOWPOWER_EXIT
 功能描述  : USB退出低功耗接口
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
extern void DRV_PWRCTRL_USB_LOWPOWER_EXIT(void);


/*****************************************************************************
 函 数 名  : BSP_32K_GetTick
 功能描述  : 32K时钟对应Tick查询接口
 输入参数  : None
 输出参数  : None
 返 回 值  : 32K时钟对应Tick值
*****************************************************************************/
extern BSP_U32 BSP_32K_GetTick( BSP_VOID );


/*****************************************************************************
Function:   BSP_PWC_GetMeansFlag
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
extern BSP_S32 BSP_PWC_GetMeansFlag(PWC_COMM_MODE_E enCommMode);
#define DRV_PWC_GET_MEANSFLAG(enCommMode) BSP_PWC_GetMeansFlag(enCommMode)

extern BSP_VOID BSP_PWC_MspVoteRegister(FUNCPTR routine);
extern BSP_VOID BSP_PWC_SocpVoteRegister(FUNCPTR routine);

/*****************************************************************************
 Function   : BSP_PWC_SetTimer4WakeSrc
 Description: 设置timer4作为唤醒源
 Input      :
 Return     : void
 Other      :
*****************************************************************************/
extern VOID BSP_PWC_SetTimer4WakeSrc(VOID);

/*****************************************************************************
 Function   : BSP_PWC_DelTimer4WakeSrc
 Description: 设置timer4不作为唤醒源
 Input      :
            :
 Return     : void
 Other      :
*****************************************************************************/
extern VOID BSP_PWC_DelTimer4WakeSrc(VOID);


/*****************************************************************************
 函 数 名  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 功能描述  : AT^PSTANDBY
 输入参数  :
 输出参数  :
 返回值：
*****************************************************************************/
extern unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
extern unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
#define DRV_PWRCTRL_STANDBYSTATEACPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateAcpu(ulStandbyTime, ulSwitchTime)
#define DRV_PWRCTRL_STANDBYSTATECCPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateCcpu(ulStandbyTime, ulSwitchTime)

/***************************************************************************
 函 数 名  : BSP_TCXO_RfclkStatus
 功能描述  : 获取RF CLK状态
 输入参数  :
		enModemId  Modem ID
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         使能;
             PWRCTRL_COMM_OFF        禁止;
             RET_ERR                 参数异常
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    修改内容   : 新生成函数
**************************************************************************/
extern int BSP_TCXO_RfclkStatus(PWC_COMM_MODEM_E enModemId);
#define DRV_TCXO_RFCLKSTATUS(enModemId) BSP_TCXO_RfclkStatus(enModemId)
/*****************************************************************************
 函 数 名  : DRV_TCXO_RfclkEnable
 功能描述  : 通信模块控制RF 19.2M时钟使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    修改内容   : 新生成函数

*****************************************************************************/
extern int BSP_TCXO_RfclkEnable(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);
#define DRV_TCXO_RFCLKENABLE(enModemId, enModeType) BSP_TCXO_RfclkEnable(enModemId, enModeType)
/*****************************************************************************
 函 数 名  : BSP_TCXO_RfclkDisable
 功能描述  : 通信模块控制RF 19.2M时钟去使能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月24日
    修改内容   : 新生成函数

*****************************************************************************/
extern int BSP_TCXO_RfclkDisable(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);
#define DRV_TCXO_RFCLKDISABLE(enModemId, enModeType) BSP_TCXO_RfclkDisable(enModemId, enModeType)
/***************************************************************************
 函 数 名  : DRV_TCXO_GETSTATUS
 功能描述  : 获取TCXO状态
 输入参数  :
		enModemId  Modem ID
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON         使能;
             PWRCTRL_COMM_OFF        禁止;
             RET_ERR                 参数异常
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern int BSP_TCXO_GetStatus(PWC_COMM_MODEM_E enModemId);
#define DRV_TCXO_GETSTATUS(enModemId)   BSP_TCXO_GetStatus(enModemId)
/***************************************************************************
 函 数 名  : DRV_TCXO_ENABLE
 功能描述  : 使能TCXO
 输入参数  : enModemId  Modem ID
	         enModeType    Mode type
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern int BSP_TCXO_Enable(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);
#define DRV_TCXO_ENABLE(enModemId, enModeType)  BSP_TCXO_Enable(enModemId, enModeType)
/***************************************************************************
 函 数 名  : DRV_TCXO_DISABLE
 功能描述  : 关闭TCXO
 输入参数  : enModemId  Modem ID
	         enModeType    Mode type
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
	         RET_ERR_NOT_FOUND 没有投票使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern int BSP_TCXO_Disable(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);
#define DRV_TCXO_DISABLE(enModemId, enModeType) BSP_TCXO_Disable(enModemId, enModeType)
/***************************************************************************
 函 数 名  : DRV_TCXO_TIMER_START
 功能描述  : TCXO 定时器启动
 输入参数  : enModemId  Modem ID
    	     enModeType    Mode type
    	     routine:回调函数  注:回调函数在中断上下文中执行
             arg:回调参数
             timerValue:计数值 单位ms
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern int BSP_TCXO_Timer_Start(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_TCXO_FUNCPTR routine, int arg, unsigned int timerValue);
#define DRV_TCXO_TIMER_START(enModemId, enModeType, routine, arg, timerValue)   BSP_TCXO_Timer_Start(enModemId, enModeType, routine, arg, timerValue)

/***************************************************************************
 函 数 名  : PWRCTRL_DfsQosRequest
 功能描述  : 调频投票请求
 输入参数  : qos_id  投票模块 ID
    	     req_value   频率值
    	     req_id: 请求到的ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern BSP_S32 PWRCTRL_DfsQosRequest(BSP_S32 qos_id, BSP_U32 req_value, BSP_S32* req_id);
/***************************************************************************
 函 数 名  : PWRCTRL_DfsQosRelease
 功能描述  : 调频投票释放
 输入参数  : qos_id  投票模块 ID
    	     req_id: 待释放的ID
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern BSP_S32 PWRCTRL_DfsQosRelease(BSP_S32 qos_id, BSP_S32* req_id);
/***************************************************************************
 函 数 名  : PWRCTRL_DfsQosUpdate
 功能描述  : 调频投票值更新
 输入参数  : qos_id  投票模块 ID
    	     req_id: 待释放的ID
    	     req_value:待更新的值
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月19日
    修改内容   : 新生成函数
**************************************************************************/
extern BSP_S32 PWRCTRL_DfsQosUpdate(BSP_S32 qos_id, BSP_S32 req_id, BSP_U32 req_value);

/*****************************************************************************
Function:   BSP_DSPTcmStore
Description:    BBE16 TCM备份，供TL低功耗调用
Input:
Output:
Return:
Others:
*****************************************************************************/
extern BSP_S32 BSP_DSPTcmStore(BSP_VOID);
#define DRV_EDMA_DSP_MemStore() BSP_DSPTcmStore()

/*****************************************************************************
Function:   BSP_DSPTcmRestore
Description:    BBE16 TCM恢复，供TL低功耗调用
Input:
Output:
Return:
Others:
*****************************************************************************/
extern BSP_S32 BSP_DSPTcmRestore(BSP_VOID);
#define DRV_EDMA_DSP_MemRestore() BSP_DSPTcmRestore()

/*****************************************************************************
Function:   BSP_GetDspTaskState
Description:    BBE16 TCM备份恢复状态查询，供TL低功耗调用
Input:
Output:
Return:
Others:
*****************************************************************************/
extern BSP_S32 BSP_GetDspTaskState(BSP_VOID);
#define DRV_EDMA_DSP_StateGet() BSP_GetDspTaskState()

/*****************************************************************************
Function:   BSP_StopDsp
Description:    BBE16停止运行
Input:
Output:
Return:
Others:
*****************************************************************************/
extern BSP_VOID BSP_StopDsp(BSP_VOID);
#define DRV_PWRCTRL_DSP_HOLD() BSP_StopDsp()

/*****************************************************************************
Function:   BSP_RunDsp
Description:    BBE16开始运行
Input:
Output:
Return:
Others:
*****************************************************************************/
extern BSP_VOID BSP_RunDsp(BSP_VOID);
#define DRV_PWRCTRL_DSP_RUN() BSP_RunDsp()

/*****************************************************************************
* 函 数 名  : BSP_ResetDsp
* 功能描述  : L模下DSP复位接口
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_VOID BSP_ResetDsp(void);
#define DRV_PWRCTRL_DSP_RESET() BSP_ResetDsp()

/*****************************************************************************
* 函 数 名  : BSP_UnresetDsp
* 功能描述  : L模下DSP解复位接口
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_VOID BSP_UnresetDsp(void);
#define DRV_PWRCTRL_DSP_UNRESET() BSP_UnresetDsp()

/*****************************************************************************
* 函 数 名  : BSP_DspClkEnable
* 功能描述  : L模下DSP时钟使能接口
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_VOID BSP_DspClkEnable(void);
#define DRV_PWRCTRL_DSP_CLKENABLE() BSP_DspClkEnable()

/*****************************************************************************
* 函 数 名  : BSP_DspClkDisable
* 功能描述  : L模下DSP时钟去使能接口
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_VOID BSP_DspClkDisable(void);
#define DRV_PWRCTRL_DSP_CLKDISABLE() BSP_DspClkDisable()

/*****************************************************************************
Function:   BSP_BBPIntWakeEnable
Description:    enable bbp wakeup int
Input:  PWC_COMM_MODE_E mode
Output:
Return:
Others:
*****************************************************************************/
extern BSP_VOID BSP_BBPIntWakeEnable(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_ENABLE(mode) BSP_BBPIntWakeEnable(mode) 

/*****************************************************************************
Function:   BSP_BBPIntWakeDisable
Description:    disable bbp wakeup int
Input:  PWC_COMM_MODE_E mode
Output:
Return:
Others:
*****************************************************************************/
extern BSP_VOID BSP_BBPIntWakeDisable(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_DISABLE(mode) BSP_BBPIntWakeDisable(mode) 

/*****************************************************************************
Function:   BSP_BBPIntWakeClear
Description:    clear bbp wakeup int
Input:  PWC_COMM_MODE_E mode
Output:
Return:
Others:
*****************************************************************************/
extern BSP_VOID BSP_BBPIntWakeClear(PWC_COMM_MODE_E mode);
#define DRV_BBPWAKE_INT_CLEAR(mode) BSP_BBPIntWakeClear(mode) 

/*****************************************************************************
* 函 数 名  : PWRCTRL_GetSleepSlice
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_U32 PWRCTRL_GetSleepSlice(void);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKENABLE
 功能描述  : 开启通信模块时钟
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_BBPCLKENABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 函 数 名  : DRV_PWRCTRL_BBPCLKDISABLE
 功能描述  : 关闭通信模块时钟
 输入参数  : enModeId     通信模式
             enModuleId   通信模块
             enModemId    卡号
 输出参数  : 无
 返 回 值  : RET_OK         成功
             RET_ERR        失败
*****************************************************************************/
extern BSP_S32 DRV_PWRCTRL_BBPCLKDISABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);


#endif


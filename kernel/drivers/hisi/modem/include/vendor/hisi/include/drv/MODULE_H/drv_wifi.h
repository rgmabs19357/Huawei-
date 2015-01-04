/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_wifi.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_wifi.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_WIFI_H__
#define __DRV_WIFI_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))
#ifdef BSP_CORE_MODEM
#include "../../app/CommAppInterface.h"
#else
#include "CommAppInterface.h"
#endif
#define WPS_PIN_LEN (8)                   /* WIFI WPS PIN CODE LEN */          


typedef enum 
{
    GPIO_WLAN_WAKE, /*WIFI芯片唤醒中断上报*/
}GPIO_EVENT;

typedef enum
{
    MMI_PASS, 
}SCREEN_EVENT;

typedef enum
{
    WLAN_WPS_SUC,  /* wps激活成功 */
    WLAN_WPS_FAIL,  /* wps激活失败 */
    WLAN_NO_STA,/* 无station用户接入 */
    WLAN_TIME_OUT,/* wlan定时器超时 */
}WLAN_EVENT;

typedef struct
{
	int ulAID;              /* UID */
	unsigned char ulYiAddr[6];       /* MAC ADDR */
	int ulConnTime;          /* Total time of connected */
} stWLANSTAT;

/*****************************************************************************
 Function   : drivers_event_dispatch
 Description: 
 Calls      :
 Called By  : 
 Input      : None
 Return     : VOS_OK or VOS_ERR
 Other      : just dispatch, no process, no global variable return quikly
              Not support NOW, dont USE it! remove it later.
 *****************************************************************************/
int drivers_event_dispatch(device_event_t * device_event);

typedef int (*DRIVERS_EVENT_DISPATCH)(device_event_t * device_event);

void drv_dispatch_register( DRIVERS_EVENT_DISPATCH pCallback );

void drv_dispatch_unregister( void );



/*
   注册 MMI 测试的回调函数。当用户注册后，默认进入 MMI 测试模式。
   未注册或者取消后，默认退出 MMI 测试模式
*/
void drv_kpd_mmi_test_register( DRIVERS_EVENT_DISPATCH pCallback );
void drv_kpd_mmi_test_unregister( void );

/* Interface for app */
/************************************************************************
 * FUNCTION
 *       wifi_athr_startup
 * DESCRIPTION
 *       initialize wifi driver include enable wifi power, load firmware, 
 *       init wifi driver and hostapd. after the operate, the wifi modules 
 *       will be normal working status. The function should load hostapd 
 *       config file and wmi config file.
 * INPUTS
 *       type: 
 *           WIFI_NORMAL     0
 *           WIFI_TEST       1
 *           WIFI_ART        2
 *
 *       cal_mode:
 *          WIFI_CAL_HIGH  0
 *          WIFI_CAL_LOW   1
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_startup(int type, int cal_mode);


/************************************************************************
 * FUNCTION
 *       wifi_athr_shutdown
 * DESCRIPTION
 *       deinitialize the wifi driver, cut down the power of wifi.
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_shutdown(void);


/************************************************************************
 * FUNCTION
 *       wifi_athr_reset
 * DESCRIPTION
 *      reset the wifi driver, except cut down the power and load firmware, 
 *      the operate as same to wifi driver startup. all config of the wifi 
 *      will be reset from hostapd config file. and the module enter normal 
 *      working status. 
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_reset(void);


/************************************************************************
 * FUNCTION
 *       wifi_athr_powersave_enter
 * DESCRIPTION
 *       wifi chipset enter power save mode.
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_powersave_enter(void);



/************************************************************************
 * FUNCTION
 *       wifi_athr_powersave_exit
 * DESCRIPTION
 *       wifi_athr_powersave_exit
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_powersave_exit(void);



/************************************************************************
 * FUNCTION
 *       wifi_ath_get_sta
 * DESCRIPTION
 *       get connected station, it include all of ssid.
 *       Attention: the stStaList's memory should be malloc and free by caller(app).
 * INPUTS
 *       stWLANSTAT: user list
 * OUTPUTS
 *       -1: failed other: cnt of connected station
 *************************************************************************/
int wifi_ath_get_sta(stWLANSTAT *stStaList);


/************************************************************************
 * FUNCTION
 *       wifi_reg_wps_hook
 * DESCRIPTION
 *       register wps hook
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
unsigned long wifi_reg_wps_hook(DRIVERS_EVENT_DISPATCH pCallback);


/************************************************************************
 * FUNCTION
 *       wifi_athr_wps_key_startup
 * DESCRIPTION
 *       startup wps authentication with key
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void wifi_athr_wps_key_startup(void);


/************************************************************************
 * FUNCTION
 *       wifi_athr_wps_pin_startup
 * DESCRIPTION
 *       startup wps authentication with pin
 * INPUTS
 *       scWpsPin: PIN CODE
 * OUTPUTS
 *       NONE
 *************************************************************************/
void wifi_athr_wps_pin_startup(char scWpsPin[WPS_PIN_LEN]);

/************************************************************************
 * FUNCTION
 *       wifi_athr_get_sta_cnt
 * DESCRIPTION
 *       startup wps authentication with pin
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0 no station connected, other: the number of connected.
 *************************************************************************/
int wifi_athr_get_sta_cnt(void);


/************************************************************************
 * FUNCTION
 *       wifi_athr_balong_sleep
 * DESCRIPTION
 *       balong enter sleep mode, inform wifi chipset
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_balong_sleep(void);


/************************************************************************
 * FUNCTION
 *       wifi_athr_balong_wakeup
 * DESCRIPTION
 *       balong leave form sleep mode, inform wifi chipset
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: succuess 1: failed
 *************************************************************************/
int wifi_athr_balong_wakeup(void);

#endif

/*****************************************************************************
 函 数 名  : WifiCalDataLen
 功能描述  : WIFI计算需要数据块内存
 输入参数  : usLen - 用户申请数据长度Len
 输出参数  : 无
 返 回 值  : 申请的数据区的总长度
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月22日
    修改内容   : 新生成函数

*****************************************************************************/
extern unsigned short BSP_WifiCalDataLen(unsigned short usLen);
#define DRV_WifiCalDataLen(usLen) BSP_WifiCalDataLen(usLen)

/*****************************************************************************
 函 数 名  : WIFI_TEST_CMD
 功能描述  : 测试命令
 输入参数  : cmdStr；命令字符串
 输出参数  : 无
 返回值    ：无
*****************************************************************************/
extern void WIFI_TEST_CMD(char * cmdStr);

/*****************************************************************************
 函 数 名  : WIFI_GET_TCMD_MODE
 功能描述  : 获取测试命令的模式
 输入参数  : 无
 输出参数  : 16：校准测试模式
             17：表示处于发射模式
             18：表示接收模式
 返回值    ：函数执行的状态结果值
*****************************************************************************/
extern int WIFI_GET_TCMD_MODE(void);

/*****************************************************************************
 函 数 名  : WIFI_POWER_START
 功能描述  : WIFI上电
 输入参数  : 无
 输出参数  : 无
 返回值    ： 0: execute ok
              1: execute failed
*****************************************************************************/
extern int WIFI_POWER_START(void);

/*****************************************************************************
 函 数 名  : WIFI_POWER_SHUTDOWN
 功能描述  : WIFI下电
 输入参数  : 无
 输出参数  : 无
 返回值    ： 0: execute ok
              1: execute failed
*****************************************************************************/
extern int WIFI_POWER_SHUTDOWN(void);

/*****************************************************************************
 函 数 名  : WIFI_GET_STATUS
 功能描述  : WIFI状态获取
 输入参数  : 无
 输出参数  : 无
 返回值    ： 0: wifi is off
              1: wifi is in normal mode
              2: wifi is in tcmd mode
*****************************************************************************/
extern int WIFI_GET_STATUS(void);

/*****************************************************************************
 函 数 名  : WIFI_GET_RX_DETAIL_REPORT
 功能描述  : get result of rx report: totalPkt, GoodPkt, ErrorPkt
 输入参数  : 无
 输出参数  : totalPkt、goodPkt、badPkt
 返回值    ：无
*****************************************************************************/
extern void WIFI_GET_RX_DETAIL_REPORT(int* totalPkt,int* goodPkt,int* badPkt);

/*****************************************************************************
 函 数 名  : WIFI_GET_RX_PACKET_REPORT
 功能描述  : get result of rx ucast&mcast packets
 输入参数  : 无
 输出参数  : ucastPkts、mcastPkts
 返回值    ：无
*****************************************************************************/
extern void  WIFI_GET_RX_PACKET_REPORT(unsigned int *ucastPkts, unsigned int *mcastPkts);

/*****************************************************************************
 函 数 名  : WIFI_GET_PA_CUR_MODE
 功能描述  : get the currrent PA mode of the wifi chip
 输入参数  : 无
 输出参数  : 无
 返回值    ：0:  (WIFI_ONLY_PA_MODE) WIFI chip is in PA mode
             1:  (WIFI_ONLY_NOPA_MODE) WIFI chip is in no PA mode
             -1: wifi chip is in abnormal mode
*****************************************************************************/
extern int WIFI_GET_PA_CUR_MODE(void);

/*****************************************************************************
 函 数 名  : WIFI_GET_PA_MODE
 功能描述  : get the support PA mode of wifi chip
 输入参数  : 无
 输出参数  : 无
 返回值    ：0:  (WIFI_ONLY_PA_MODE) WIFI suppport only PA mode
             1:  (WIFI_ONLY_NOPA_MODE) WIFI suppport only no PA mode
             2:  (WIFI_PA_NOPA_MODE) WIFI suppport both PA &  no PA mode
             -1: failed
*****************************************************************************/
extern int WIFI_GET_PA_MODE(void);

/*****************************************************************************
 函 数 名  : WIFI_SET_PA_MODE
 功能描述  : set the PA mode of wifi chip
 输入参数  : 0:  (WIFI_ONLY_PA_MODE) WIFI suppport only PA mode
             1:  (WIFI_ONLY_NOPA_MODE) WIFI suppport only no PA mode
             2:  (WIFI_PA_NOPA_MODE) WIFI suppport both PA &  no PA mode
 输出参数  : 无
 返回值    ：0: success
             -1: failed
*****************************************************************************/
extern int WIFI_SET_PA_MODE(int wifiPaMode);

/*****************************************************************************
 函 数 名  : DRV_WIFI_DATA_RESERVED_TAIL
 功能描述  : WIFI计算需要数据块内存
 输入参数  : usLen - 用户申请数据长度Len
 输出参数  : 无
 返 回 值  : 数据区的尾部预留的长度
*****************************************************************************/
extern unsigned int DRV_WIFI_DATA_RESERVED_TAIL(unsigned int len);

/*****************************************************************************
 函 数 名  : DRV_WIFI_SET_RX_FCTL
 功能描述  : 设置WIFI接收流控标识
 输入参数  : para1、para2
 输出参数  : 无
 返 回 值  : BSP_OK/BSP_ERROR
*****************************************************************************/
extern unsigned long DRV_WIFI_SET_RX_FCTL(unsigned long para1, unsigned long para2);

/*****************************************************************************
 函 数 名  : DRV_WIFI_CLR_RX_FCTL
 功能描述  : 清除WIFI接收流控标识
 输入参数  : para1、para2
 输出参数  : 无
 返 回 值  : 1 : 有
             0 : 无
*****************************************************************************/
extern unsigned long DRV_WIFI_CLR_RX_FCTL(unsigned long para1, unsigned long para2);

/*****************************************************************************
 函 数 名  : DRV_AT_GET_USER_EXIST_FLAG
 功能描述  : 返回当前是否有USB连接或者WIFI用户连接(C核调用)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1 : 有
             0 : 无
*****************************************************************************/
extern unsigned long  DRV_AT_GET_USER_EXIST_FLAG(void);


unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOUtTimeout);
unsigned long USB_ETH_DrvSetDeviceAssembleParam(unsigned long ulEthTxMinNum,
											    unsigned long ulEthTxTimeout,
											    unsigned long ulEthRxMinNum,
											    unsigned long ulEthRxTimeout);

#endif


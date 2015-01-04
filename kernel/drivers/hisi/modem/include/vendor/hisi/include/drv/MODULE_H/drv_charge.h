

#ifndef __DRV_CHARGE_H__
#define __DRV_CHARGE_H__
#include "drv_global.h"

typedef enum CHARGING_STATE_ENUM_tag
{
        CHARGING_INIT = -1,
        NO_CHARGING_UP = 0,  /*开机未充电*/
        CHARGING_UP ,              /*开机正充电*/
        NO_CHARGING_DOWN ,  /*关机未充电*/
        CHARGING_DOWN         /*关机未充电*/
}CHARGING_STATE_ENUM;

typedef enum BATT_LEVEL_ENUM_tag
{
        BATT_INIT = -2,
        BATT_LOW_POWER =-1,    /*电池低电*/
        BATT_LEVEL_0,                 /*0格电池电量*/
        BATT_LEVEL_1,                  /*1格电池电量*/
        BATT_LEVEL_2,                   /*2格电池电量*/
        BATT_LEVEL_3,                    /*3格电池电量*/
        BATT_LEVEL_4,                    /*4格电池电量*/
        BATT_LEVEL_MAX
}BATT_LEVEL_ENUM;

typedef struct BATT_STATE_tag
{
    CHARGING_STATE_ENUM  charging_state;
    BATT_LEVEL_ENUM           battery_level;
}BATT_STATE_T;

#define CHARGER_ONLINE                  (1) /*充电器在位*/
#define CHARGER_OFFLINE                 (0)/*充电器不在位*/

typedef enum   
{
BAT_CHARGING_ON_START = 0,/*在开机模式，开始充电**/
BAT_CHARGING_OFF_START,	/*在关机模式，开始充电*/
BAT_LOW_POWER, 	/*电池电量低时，上报此事件*/
BAT_CHARGING_UP_STOP, 	/*停止充电时，上报此事件*/
BAT_CHARGING_DOWN_STOP,
BAT_EVENT_MAX,  /*如果事件值不小于此值，则为非法事件*/
}BATTERY_EVENT;

typedef enum
{
    TEMP_BATT_LOW, /*电池低温事件*/
    TEMP_BATT_HIGH,  /*电池高温事件*/
}TEMPERATURE_EVENT;
typedef enum
{
    CHARGER_ATTACH,
    CHARGER_REMOVE,
}CHARGER_EVENT;

typedef enum USB_CHARGE_TYPE_ENUM_tag
{
    USB_CHARGE_TYPE_NON_CHECK = -1,          /* 还未判断出来连接线类型 */
    USB_CHARGE_TYPE_HW = 0,                      /* 华为充电器             */
    USB_CHARGE_TYPE_NON_HW =1,                  /* 非华为充电器           */
    
}USB_CHARGE_TYPE_ENUM;

/************************************************************************
 * FUNCTION
 *       app_get_battery_state
 * DESCRIPTION
 *       获取底层电池状态信息       
 * INPUTS
 *       NONE
 * OUTPUTS: battery_state:是否充电/电池电量
 * return:    0 Success, -1 failed     
 *************************************************************************/
int app_get_battery_state(BATT_STATE_T *battery_state);
/************************************************************************
 * FUNCTION
 *       int getCbcState(unsigned char *pucBcs ,unsigned char  *pucBcl)
 * DESCRIPTION
 *       pucBcs
            0: 电池在供电
            1: 与电池连接电池未供电
            2: 没有与电池连接
         pucBcl
            0:电量不足或没有与电池连接
             100: 剩余电量百分比
 * INPUTS
 *          
 * OUTPUTS: 
           pucBcs
           pucBcl
 * return:    0 Success, -1 failed     
 *******************************************************************/
int getCbcState(unsigned char  *pucBcs ,unsigned char   *pucBcl);

/************************************************************************************
 *Function Name :  usb_charge_type   
 *Description   :  获取插入USB线的类型,判断是华为充电器,
                    还是非华为充电器(包括非华为充电器和普通PC机)
 *Others        :  No
************************************************************************************/
USB_CHARGE_TYPE_ENUM usb_charge_type( void );

/************************************************************************************
 *Function Name :  usb_enum_completed   
 *Description   :  判断USB的枚举是否完成,
                        完成返回(1),未完成返回(0)
 *Others        :  No
************************************************************************************/
unsigned int usb_enum_completed( void );

/************************************************************************
 * FUNCTION
 *       usb_get_charger_status
 * DESCRIPTION
 *       获取充电器的在位状态
 * INPUTS
 *       NONE
 * OUTPUTS
 *       在位则返回1，否则返回0。
 *************************************************************************/
unsigned int usb_get_charger_status(void);


/*****************************************************************************
 函 数 名  : BSP_CHG_GetCbcState
 功能描述  : 返回电池状态和电量
 输入参数  :pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
                          pucBcl  0:电量不足或没有与电池连接
 输出参数  : pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
                          pucBcl  0:电量不足或没有与电池连接
 返回值：   0 操作成功
                         -1操作失败

*****************************************************************************/
extern int BSP_CHG_GetCbcState(unsigned char *pusBcs,unsigned char *pucBcl);
extern int DRV_CHG_GET_CBC_STATE(unsigned char *pusBcs,unsigned char *pucBcl);

/*AT 命令枚举类型*/
typedef enum
{
    CHG_AT_BATTERY_CHECK,        /* Battery校准*/
    CHG_AT_BATTERY_LEVEL,        /* Battery电量 */
    CHG_AT_BATTERY_ADC,          /* Battery Temperature保护*/
    CHG_AT_BATTERY_INVALID
} ENUM_CHG_ATCM_TYPE;

typedef enum ENUM_POWER_ON_MODE_tag
{
    POWER_ON_INVALID = 0,          	/* 无效开机模式*/
    POWER_ON_NORMAL,       	 	/* 正常开机模式*/
    POWER_ON_CHARGING,       	/* 关机充电模式*/
    POWER_ON_MAX
} ENUM_POWER_ON_MODE;
/*****************************************************************************
 函 数 名  : BSP_CHG_GetBatteryState
 功能描述  :获取底层电池状态信息
 输入参数  :battery_state 电量信息
 输出参数  :battery_state 电量信息
 返回值：   0 操作成功
                         -1操作失败

*****************************************************************************/
extern int BSP_CHG_GetBatteryState(BATT_STATE_T *battery_state);
extern int DRV_CHG_GET_BATTERY_STATE(BATT_STATE_T *battery_state);

/*****************************************************************************
 函 数 名  : BSP_CHG_ChargingStatus
 功能描述  :查询目前是否正在充电中
 输入参数  :无
 输出参数  :无
 返回值：   0 未充电
                          1 充电中
*****************************************************************************/
extern int BSP_CHG_ChargingStatus(void);
extern int DRV_CHG_GET_CHARGING_STATUS(void);

/*****************************************************************************
 函 数 名  : BSP_CHG_StateSet
 功能描述  :使能或者禁止充电
 输入参数  :ulState      0:禁止充电
 						1:使能充电
 输出参数  :无
 返回值：    无
*****************************************************************************/
extern void DRV_CHG_STATE_SET(unsigned long ulState);

/*****************************************************************************
 函 数 名  : BSP_CHG_StateGet
 功能描述  :查询
 输入参数  :
 输出参数  :无
 返回值：    无
*****************************************************************************/
extern BSP_S32 BSP_CHG_StateGet(void);
#define DRV_CHG_STATE_GET()    BSP_CHG_StateGet()

/*****************************************************************************
 函 数 名  : BSP_CHG_Sply
 功能描述  :查询
 输入参数  :
 输出参数  :无
 返回值：    无
*****************************************************************************/
extern BSP_S32 BSP_CHG_Sply(void);
#define DRV_CHG_BATT_SPLY()    BSP_CHG_Sply()


/*****************************************************************************
* 函 数 名  : BSP_TBAT_Read
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_S32 BSP_TBAT_Read(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/*****************************************************************************
* 函 数 名  : BSP_TBAT_Write
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
extern BSP_S32 BSP_TBAT_Write(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/**********************************************************************
函 数 名      : BSP_TBAT_CHRStGet
功能描述  :  TBAT AT^TCHRENABLE?是否需要补电

输入参数  : 无
输出参数  : 无
返 回 值      : 1:需要补电
			      0:不需要补电
注意事项  : 无
***********************************************************************/
extern BSP_S32 BSP_TBAT_CHRStGet(void);

/**********************************************************************
函 数 名      : BSP_TBAT_CHRSuply
功能描述  :  TBAT AT^TCHRENABLE=4补电实现
            			需要提供补电成功LCD显示图样
输入参数  : 无
输出参数  : 无
返 回 值      :
注意事项  : 无
***********************************************************************/
extern BSP_S32 BSP_TBAT_CHRSply(void);

/**********************************************************************
函 数 名      : BSP_ONOFF_StartupModeGet
功能描述  :  A核判断开关机模式

输入参数  : 无
输出参数  : 无
返 回 值      :
注意事项  : 无
***********************************************************************/
ENUM_POWER_ON_MODE BSP_ONOFF_StartupModeGet( void );
/*****************************************************************************
* 函 数 名  : BSP_PMU_BattCali
*
* 功能描述  : 电池校准前减小单板电流接口，给AT调用
*
* 输入参数  :
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
extern void BSP_PMU_BattCali(void);


#endif




#ifndef __DRV_HKADC_H__
#define __DRV_HKADC_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))

#define HKADC_OK  (0)
#define HKADC_ERROR (-1)
#define HKADC_BBP_CLK_CLOSE (1)

#define SYS_TEM_HKADC_TABLE_LEN  (32)
#define SYS_TEM_LOW              (-20)
#define SYS_TEM_HIGH             (85)
#define TEM_INVALID_VAL         (-100)

#define SIM_TEM_HKADC_TABLE_LEN  (19)
#define SIM_TEM_LOW              (10)
#define SIM_TEM_HIGH             (100)
#define SIM_TEM_OFFSET           (5)
#define ID_NV_Item_AT_SHELL_OPEN_FLAG (33)        /* 保存当前SHELL口的开关状态 */


#define TEMPERATURE_HKADC_CHANNEL      (3)



/*************************************************
*  Function:  hkadcGsmTempRead
*  Description: Read gsm temperature *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         pslData:对应hkadc通道的温度值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcGsmPATempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcWcdmaTempRead
*  Description: Read wcdma temperature *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         pslData:对应hkadc通道的温度值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcWcdmaPATempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcSIMTempRead
*  Description: Read SIM temperature *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         pslData:对应hkadc通道的温度值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcSIMTempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcOLEDTempRead
*  Description: Read OLED temperature *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         pslData:对应hkadc通道的温度值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcOLEDTempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcBatTempRead
*  Description: Read battery temperature *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         pslData:对应hkadc通道的温度值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcBatTempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcBatRefTempRead
*  Description: 通过电池自身NTC电阻来读温度，用来判断电池是否在位*
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:*          
           hkAdcTable:  电压温度换算表；
*  Output:
*         pslData:     存储的电压转换为的温度值；
*  Return:
*         函数执行的状态结果值；
*************************************************/
int hkadcBatRefTempRead(int *pslData, unsigned short *hkAdcTable);

/*************************************************
*  Function:  hkadcPaPowerRead
*  Description: Read gsm PA power *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         N/A
*  Return:
*         N/A
*************************************************/
int hkadcPAPowerRead(int *pslData);


/*************************************************
*  Function:  hkadcTemVoltTrans
*  Description:  *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*          
*  Output:
*         N/A
*  Return:
*         N/A
*************************************************/
signed short hkadcTemVoltTrans(unsigned char ucChan, unsigned short usVoltage, unsigned short *hkAdcTable);


/*************************************************
*  Function:  hkadcBatVoltRefSet
*  Description:  * 设置Battery最低和最高电压对应的adc值
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*        minVol:最低电压，minAdc：最低电压对应的adc值，
*	 maxVol:最高电压，maxAdc：最高电压对应的adc值
*  Output:
*         N/A
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcBatVoltRefSet(int minVol, int minAdc, int maxVol, int maxAdc);

/*************************************************
*  Function:  hkadcBatVoltGet
*  Description:  *
*  Called By:sysctrl
*  Table Accessed:
*  Table Updated:
*  Input:
*        N/A  
*  Output:
*         pslData : 电池电压值
*  Return:
*         HKADC_OK/HKADC_ERROR
*************************************************/
int hkadcBatVoltGet(int *pslData );



/*************************************************
*  Function:  hkadcBatADCRead
*  Description: Read the battery adc value 
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         pslData:对应hkadc通道adc值
*  Return:
*         HKADC_OK/HKADC_ERROR；
*************************************************/
int hkadcBatADCRead(int* pslData);

#endif

#ifndef _DRV_LLT_
typedef enum _KEY_EVENT
{
	KEY_WAKEUP = 0,
	KEY_WLAN,
	KEY_WPS,
	KEY_FACTORY_RESTORE,
	KEY_POWER_OFF,
	KEY_UPDATE,
	KEY_SSID,
    KEY_WPS_PROMPT = 7,
	KEY_WIFI_OFFLOAD = 15,
	KEY_EVENT_MAX
} KEY_EVENT;
#else

#ifndef KEY_WAKEUP
#define KEY_WAKEUP 0
#endif

#ifndef KEY_WLAN
#define KEY_WLAN 1
#endif

#ifndef KEY_FACTORY_RESTORE
#define KEY_FACTORY_RESTORE 3
#endif

#ifndef KEY_POWER_OFF
#define KEY_POWER_OFF 4
#endif

#ifndef KEY_UPDATE
#define KEY_UPDATE       5
#endif

#ifndef KEY_SSID
#define KEY_SSID         6
#endif

#ifndef KEY_WPS_PROMPT
#define KEY_WPS_PROMPT   7
#endif

#ifndef KEY_WIFI_OFFLOAD
#define KEY_WIFI_OFFLOAD 15
#endif

#ifndef KEY_EVENT_MAX
#define KEY_EVENT_MAX    16
#endif

#endif

typedef enum tagHKADC_TEMP_PROTECT_E
{
    HKADC_TEMP_TOP = 0,
    HKADC_TEMP_BATTERY = HKADC_TEMP_TOP,     /*0*/
	HKADC_TEMP_PA0,                          /*1*/
	HKADC_TEMP_PA1,                          /*2*/
	HKADC_TEMP_DCXO0,                        /*3*/
	HKADC_TEMP_DCXO0_LOW,                    /*4*/
	HKADC_TEMP_DCXO1,                        /*5*/
	HKADC_TEMP_DCXO1_LOW,                    /*6*/
	HKADC_TEMP_LCD,                          /*7*/
	HKADC_TEMP_SIM_CARD,                     /*8*/
	HKADC_TEMP_SYSTEMH,                      /*9*/
	HKADC_TEMP_SYSTEML,                      /*10*/
	HKADC_TEMP_BATT_ID,                      /*11*/
	HKADC_TEMP_CAMERA0_ID,                   /*12*/
	HKADC_TEMP_CAMERA1_ID,                   /*13*/
	HKADC_TEMP_SCAMERA,                      /*14*/
	HKADC_TEMP_FLASH,                        /*15*/

	HKADC_TEMP_BUTT
}HKADC_TEMP_PROTECT_E;


typedef enum tagHKADC_CONV_MODE_E
{
    HKADC_CONV_DELAY = 0,
    HKADC_CONV_NO_DELAY,
    HKADC_CONV_BUTT
}HKADC_CONV_MODE_E;

/*************************************************
 函 数 名   : DRV_HKADC_BAT_VOLT_GET
 功能描述   : 返回当前电池电压值
 输入参数   : pslData : 电池电压值
 输出参数   : pslData : 电池电压值
 返 回 值   :0:获取成功
            -1:获取失败
*************************************************/
extern BSP_S32 DRV_HKADC_BAT_VOLT_GET(BSP_S32 *ps32Data);


/*****************************************************************************
* 函 数 名  : BSP_HKADC_PaValueGet
*
* 功能描述  :
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : 无
*
*
*****************************************************************************/
BSP_S32 BSP_HKADC_PaValueGet( BSP_U16 *pusValue );

/*****************************************************************************
 函 数 名  : hkadcBatADCRead
 功能描述  : 获取电池电压采样值
 输入参数  : 无
 输出参数  : pTemp：        指向电池温度的指针。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern BSP_S32 DRV_GET_BATTERY_ADC(BSP_S32 * pslData);

/*****************************************************************************
 函 数 名  : DRV_HKADC_GET_TEMP
 功能描述  : 获取设备的温度值和电压值
 输入参数  : enMode, *pusVolt, *psTemp, ulMode
 输出参数  : *pusVolt, *psTemp
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int DRV_HKADC_GET_TEMP(HKADC_TEMP_PROTECT_E enMode, unsigned short* pusVolt, short* psTemp, HKADC_CONV_MODE_E ulMode);

#endif


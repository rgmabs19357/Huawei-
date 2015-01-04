/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_oled.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_oled.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_OLED_H__
#define __DRV_OLED_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))
/*OLED驱动枚举事件*/
typedef enum 
{
    OLED_LIGHT = 0,
    OLED_SLEEP,
    OLED_DIM,
    OLED_RESET,
    OLED_UPDATE,
    OLED_CONTRAST,
    OLED_BRIGHTNESS,
    OLED_POWER_ON,
    OLED_POWER_OFF,
    OLED_DEL_TIMER,/*delete the power on animation timer*/
    OLED_SYS_POWER_DOWN,
    OLED_INIT_IMAGE,
    /* BB5D02326,z67631, begin 2009/8/31 */
    OLED_POWER_OFF_CHARGING_START,/*restart power off charging animation*/
    OLED_POWER_OFF_CHARGING_STOP,/*stop power off charging animation*/
    /* BB5D02326,z67631, end 2009/8/31 */
    OLED_CMD_MAX
}OLED_IOCTL_CMD;


/*************************************************
*  Function:  oledRefresh
*  Description: oled refresh *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*          unsigned int ulXStart, unsigned int ulYStart－－起始坐标
*          unsigned int ulXOffset, unsigned int ulYOffset－－横向纵向偏移
*          unsigned char *pucBuffer－－显示数据

*  Output:
*         N/A
*  Return:
*         N/A
*************************************************/
int oledRefresh(unsigned int ulXStart, unsigned int ulYStart,unsigned int ulXOffset, unsigned int ulYOffset, unsigned char *pucBuffer);

/*************************************************
*  Function:  oledClear
*  Description: oled clear *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*          unsigned int ulXStart, unsigned int ulYStart－－起始坐标
*           unsigned int ulXOffset, unsigned int ulYOffset－－横向纵向偏移
*  Output:
*         N/A
*  Return:
*         N/A
*************************************************/
int oledClear(unsigned int ulXStart, unsigned int ulYStart,unsigned int ulXOffset, unsigned int ulYOffset);


/*************************************************
*  Function:  oledIoctrl
*  Description: oled ioctrl *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*          int cmd --command ID
*          arg--para

*  Output:
*         N/A
*  Return:
*         N/A
*************************************************/
int oledIoctrl(unsigned int cmd,  unsigned long arg);


#else

/*****************************************************************************
*  Function:  DRV_OLED_CLEAR_WHOLE_SCREEN
*  Description: oled clear *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern BSP_VOID DRV_OLED_CLEAR_WHOLE_SCREEN(BSP_VOID);

/*****************************************************************************
*  Function:  DRV_OLED_UPDATE_STATE_DISPLAY
*  Description: oled display right or not right  *
*  Called By:AP
*  Table Accessed:
*  Table Updated:
*  Input:
*         N/A
*  Output:
*         N/A
*  Return:
*         N/A
*****************************************************************************/
extern  void DRV_OLED_UPDATE_STATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 函 数 名  : DRV_OLED_UPDATE_DISPLAY
 功能描述  : SD卡烧片版本升级，OLED显示
 输入参数  : BOOL UpdateStatus
 输出参数  : 无。
 返回值：   无
 其它:  升级成功，NV备份完成后调用该函数打勾
        升级失败后调用该函数打叉
*****************************************************************************/
extern void DRV_OLED_UPDATE_DISPLAY(int UpdateStatus);

/*****************************************************************************
 函 数 名  : DRV_OLED_STRING_DISPLAY
 功能描述  : oled字符串显示函数
 输入参数  :
 *           要显示字符串的起始坐标
 *           要显示的字符串
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
extern BSP_VOID DRV_OLED_STRING_DISPLAY(UINT8 ucX, UINT8 ucY, UINT8 *pucStr);

/*****************************************************************************
 函 数 名  : DRV_OLED_POWER_OFF
 功能描述  : oled下电函数
 输入参数  :
 输出参数  : None
 返 回 值  : void
*****************************************************************************/
extern BSP_VOID DRV_OLED_POWER_OFF(BSP_VOID);

#endif
#endif

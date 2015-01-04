/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_charge.c
  版 本 号   : 初稿
  作    者   : c61362
  生成日期   : 2012年3月2日
  最近修改   :
  功能描述   : 底软给上层软件封装的接口层
  修改历史   :
  1.日    期   : 2012年3月2日
    作    者   : c61362
    修改内容   : 新建Drvinterface.c
    
  2.日    期   : 2013年2月19日
    作    者   : 蔡喜 220237
    修改内容   : 由Drvinterface.c拆分所得

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "BSP.h"
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "sys_config.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 函数声明
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : DRV_CHG_GET_BATTERY_STATE
 功能描述  : 获取底层电池状态信息
 输入参数  : battery_state 电量信息
 输出参数  : battery_state 电量信息
 返回值：    0 操作成功
             -1操作失败
*****************************************************************************/
int DRV_CHG_GET_BATTERY_STATE(BATT_STATE_T *bttery_state)
{
    return BSP_ERROR;
#if 0    
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
#if( FEATURE_CHARGE == FEATURE_ON )
    BSP_CHG_GetBatteryState(bttery_state);
#else
    DRV_PRINTF("Function DRV_CHG_GET_BATTERY_STATE unsupport!\n");
    return -1;
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : BSP_CHG_GetCbcState
 功能描述  : 返回电池状态和电量
 输入参数  : pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
             pucBcl  0:电量不足或没有与电池连接
 输出参数  : pusBcs 0:电池在供电 1:与电池连接电池未供电 2:没有与电池连接
             pucBcl  0:电量不足或没有与电池连接
 返回值：    0 操作成功
             -1操作失败
*****************************************************************************/
int DRV_CHG_GET_CBC_STATE(unsigned char *pusBcs,unsigned char *pucBcl)
{
    return BSP_ERROR;
#if 0    
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
#if( FEATURE_CHARGE == FEATURE_ON )
    BSP_CHG_GetCbcState(pusBcs, pucBcl);
#else
    DRV_PRINTF("Function DRV_CHG_GET_CBC_STATE unsupport!\n");
    return -1;
#endif
#endif
#endif
}
/*****************************CHARGE END************************************/

/*****************************************************************************
 函 数 名  : BSP_CHG_ChargingStatus
 功能描述  :查询目前是否正在充电中
 输入参数  :无
 输出参数  :无
 返回值：   0 未充电
            1 充电中
*****************************************************************************/
int DRV_CHG_GET_CHARGING_STATUS(void)
{
    return 0;
#if 0    
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
#if( FEATURE_CHARGE == FEATURE_ON )
    return BSP_CHG_ChargingStatus();
#else
    DRV_PRINTF("Function DRV_CHG_GET_CHARGING_STATUS unsupport!\n");
    return 0;
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : DRV_CHG_STATE_SET
 功能描述  : 使能或者禁止充电
 输入参数  : ulState    0:禁止充电
 						1:使能充电
 输出参数  : 无
 返回值：    无
*****************************************************************************/
BSP_VOID  DRV_CHG_STATE_SET(unsigned long ulState)
{
    return;
#if 0    
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
#if( FEATURE_CHARGE == FEATURE_ON )
    BSP_CHG_StateSet(ulState);
#else
    DRV_PRINTF("Function DRV_CHG_STATE_SET unsupport!\n");
#endif
#endif
#endif
}

/*****************************************************************************
 函 数 名  : BSP_CHG_Sply
 功能描述  : chg_state_set(UINT32 ulstate)在A核的映射函数,查询是否需要补电
 输入参数  :
 输出参数  :
 返回值：
*****************************************************************************/
BSP_S32 BSP_CHG_Sply( void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
    return BSP_ERROR;
#endif
}

/*****************************************************************************
 函 数 名  : BSP_CHG_StateGet
 功能描述  : chg_state_set(UINT32 ulstate)在A核的映射函数,查询是否需要补电
 输入参数  :
 输出参数  :
 返回值：
*****************************************************************************/
BSP_S32 BSP_CHG_StateGet(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
    return BSP_ERROR;
#endif
}

/**********************************************************************
函 数 名  : BSP_ONOFF_StartupModeGet
功能描述  :  A核判断开关机模式
输入参数  : 无
输出参数  : 无
返 回 值      :
注意事项  : 无
***********************************************************************/
ENUM_POWER_ON_MODE BSP_ONOFF_StartupModeGet( void )
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (ENUM_POWER_ON_MODE)0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
    return POWER_ON_MAX;
#endif
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


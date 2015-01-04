/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_pmu.c
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


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef _DRV_LLT_
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#include "BSP_PMU_INTERFACE.h"
#endif
#endif
/*****************************************************************************
  2 函数声明
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : BSP_PMU_GetPMUState
 功能描述  : 获取PMU模块开机方式、充电状态、电池电量、电池在位状态。
 输入参数  : 无。
 输出参数  : Pmu_State :开机方式、充电状态、电池电量、电池在位状态。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
unsigned int DRV_GET_PMU_STATE(void*  Pmu_State)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (unsigned int)(-1);
#endif

#if (defined BSP_CORE_APP)
    return 0;   /* 打桩 */
#endif
}

#define printk(a)


BSP_S32 BSP_PMU_AptDisable(BSP_VOID)
{
    printk("stub: BSP_PMU_AptEnable\n");
	return 0;
}


BSP_S32 BSP_PMU_AptEnable(BSP_VOID)
{
    printk("stub  monan :BSP_PMU_AptEnable. \n");
    return 0;
}


BSP_BOOL BSP_PMU_AptIsEnable(BSP_VOID)
{
    printk("stub: BSP_PMU_AptIsEnable\n");
    return 0;
}

int HI6451_BoardInit(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
    printk("stub  monan :HI6451_BoardInit. \n");
    return 0;
#endif
}

#ifndef _DRV_LLT_
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
 /*****************************************************************************
 函 数 名  : DRV_PASTAR_EXC_CHECK
 功能描述  : 通信模块检查PASTAR是否有异常接口
 输入参数  : modem_id       卡号
 输出参数  : 无
 返 回 值  : BSP_OK          没有异常
             BSP_ERROR       存在异常
*****************************************************************************/
BSP_S32 DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id)
{
    return bsp_pastar_exc_check(modem_id);
}

/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_SET
 功能描述  : 通信模块设置电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      设置的电压值毫伏
 输出参数  : 无
 返 回 值  : BSP_OK          设置成功
             BSP_ERROR       设置失败
*****************************************************************************/
BSP_S32 DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 voltage_mv )
{
    return bsp_modem_voltage_set(consumer_id, voltage_mv);
}
/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_GET
 功能描述  : 通信模块获取电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      获得的电压值毫伏
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
BSP_S32 DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 *voltage_mv )
{
    return bsp_modem_voltage_get(consumer_id, voltage_mv);
}
/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_LIST
 功能描述  : 通信模块获取电压设置范围接口
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
BSP_S32 DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,BSP_U16 **list, BSP_U32 *size)
{
    return bsp_modem_voltage_list(consumer_id, list, size);
}
/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_ENABLE
 功能描述  : 通信模块使能APT接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         设置成功
             BSP_ERROR      设置失败
*****************************************************************************/
BSP_S32 DRV_MODEM_APT_ENABLE(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return bsp_modem_apt_enable(modem_id, mode_id);
}
/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_DISABLE
 功能描述  : 通信模块去使能APT接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         设置成功
             BSP_ERROR      设置失败
*****************************************************************************/
BSP_S32 DRV_MODEM_APT_DISABLE(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return bsp_modem_apt_disable(modem_id, mode_id);
}
/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_STATUS_GET
 功能描述  : 通信模块获取当前APT状态接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON     APT使能
             PWRCTRL_COMM_OFF    APT未使能
             BSP_ERROR           获取失败
*****************************************************************************/
BSP_S32 DRV_MODEM_APT_STATUS_GET(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return bsp_modem_apt_status_get(modem_id, mode_id);
}

/*****************************************************************************
 函 数 名  : DRV_MODEM_MODE_CONFIG
 功能描述  : 通信模块配置G模或W模接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         配置成功
             BSP_ERROR      配置失败
*****************************************************************************/
BSP_S32 DRV_MODEM_MODE_CONFIG(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return bsp_modem_mode_config(modem_id, mode_id);
}
/**********************************NEW PMU INTERFACE END*******************************************/
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


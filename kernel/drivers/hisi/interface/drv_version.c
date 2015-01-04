/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_version.c
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2012年3月2日
  最近修改   :
  功能描述   : 底软给上层软件封装的接口层
  修改历史   :
  1.日    期   : 2012年3月2日
    作    者   :  
    修改内容   : 新建Drvinterface.c
    
  2.日    期   : 2013年2月19日
    作    者   : 
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

extern int printf(const char *format, ...);

/*****************************************************************************
  2 函数声明
*****************************************************************************/
#define SOC_ARM_VERSION_ADDR            ((INTEGRATOR_SC_BASE)+(0x0f1c))
#define W_BBP_VERSION_ADDR              ((WBBP_BASE_ADDR) + (0x0088))
#define G_BBP_VERSION_ADDR              ((GBBP_BASE_ADDR) + (0x5760))

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_VOID WriteChipVersion(BSP_U32 ulAddress, BSP_U32 ucType);
extern BSP_VOID GetPlatformInfo(unsigned long *u32PlatformInfo);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : BSP_CheckModuleSupport
 功能描述  : 查询模块是否支持
 输入参数  : enModuleType: 需要查询的模块类型
 输出参数  : 无
 返回值    ：BSP_MODULE_SUPPORT或BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType)
{
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)    
    BSP_MODULE_SUPPORT_E enRet = BSP_MODULE_SUPPORT;

    if(enModuleType >= BSP_MODULE_TYPE_BUTTOM)
    {
        return BSP_MODULE_UNSUPPORT;
    }

    switch(enModuleType)
    {
        case BSP_MODULE_TYPE_SD:
            break;
        case BSP_MODULE_TYPE_CHARGE:
#if (FEATURE_CHARGE == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_WIFI:
#if (FEATURE_WIFI == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_OLED:
#if (FEATURE_OLED == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HIFI:
#if (FEATURE_HIFI == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_POWER_ON_OFF:
#if (FEATURE_POWER_ON_OFF == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HSIC:
#if defined(FEATURE_HSIC_SLAVE)
#if (FEATURE_HSIC_SLAVE == FEATURE_OFF)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
#else
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_HSIC_NCM:
            /*todo*/
#ifdef USB_HSIC_SUPPORT_NCM
            enRet = BSP_MODULE_SUPPORT;
#else
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        case BSP_MODULE_TYPE_LOCALFLASH:
#if defined (FEATURE_FLASH_LESS)
            enRet = BSP_MODULE_UNSUPPORT;
#endif
            break;
        default:
            enRet = BSP_MODULE_UNSUPPORT;
            break;
    }

    return enRet;
#endif

#if (defined BSP_CORE_APP)

    BSP_MODULE_SUPPORT_E enRet = BSP_MODULE_SUPPORT;

    switch(enModuleType)
    {
        case BSP_MODULE_TYPE_LOCALFLASH:

            enRet = BSP_MODULE_SUPPORT;

            break;
        default:
            enRet = BSP_MODULE_UNSUPPORT;
            break;
    }

    return enRet;

#endif
}

/******************************************************************************
*  Function:  DRV_START_MODEGET
*  Description:
*  History:
*               
********************************************************************************/
BSP_S32  DRV_START_MODEGET()
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#if( FEATURE_POWER_ON_OFF == FEATURE_ON )
    return BSP_StartModeGet();
#else
    DRV_PRINTF("Function DRV_START_MODEGET unsupport!\n");
    return 1;
#endif
#endif

#if (defined BSP_CORE_APP)
    return 0;   /* 打桩 */
#endif
}

/*****************************************************************************
 函 数 名  : BSP_WriteChipVersion
 功能描述  : 写入芯片的版本号
 输入参数  : 无
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
BSP_VOID BSP_WriteChipVersion(BSP_U32 ulAddress, BSP_U32 ucType)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    WriteChipVersion(ulAddress, ucType);
#endif

#if (defined BSP_CORE_APP)
    return;   /* 打桩 */
#endif
}

/*****************************************************************************
 函 数 名  : BSP_GetPlatformInfo
 功能描述  : 获取芯片的版本号
 输入参数  : 无
 输出参数  : u32PlatformInfo:芯片的版本号
 返 回 值  : void
*****************************************************************************/
BSP_VOID BSP_GetPlatformInfo(unsigned long *u32PlatformInfo)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    GetPlatformInfo(u32PlatformInfo);
#endif

#if (defined BSP_CORE_APP)
    return;   /* 打桩 */
#endif
}

/*****************************************************************************
 函 数 名  : BSP_InitPlatformVerInfo
 功能描述  : 初始化芯片的版本号
 输入参数  : 无
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
BSP_VOID BSP_InitPlatformVerInfo(BSP_VOID)
{
    return;
}

BSP_S32 BSP_GetSupportBands( BAND_INFO_T *pBandInfo)
{
    return 0;
}


BSP_BOOL BSP_HwIsSupportWifi(BSP_VOID)
{
    return 0;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


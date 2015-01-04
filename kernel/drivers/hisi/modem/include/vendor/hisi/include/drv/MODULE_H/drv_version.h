
#ifndef __DRV_VERSION_H__
#define __DRV_VERSION_H__
#include "drv_global.h"
/* 硬件产品信息适配 */
#define HW_VER_INVALID              (BSP_U16)0xFFFF

/* Porting板和P500板兼容 */
#define HW_VER_PRODUCT_PORTING      (BSP_U16)0xFFFE
#define HW_VER_PRODUCT_PV500        (BSP_U16)0xFFFD

/* 测试板 */
#define HW_VER_PRODUCT_UDP          (BSP_U16)0xFFFC

/* Stick */
#define HW_VER_PRODUCT_E392S_U      (BSP_U16)HW_VER_INVALID
#define HW_VER_PRODUCT_E3276S_150   (BSP_U16)0x0201

/* E5 */
#define HW_VER_PRODUCT_E5_SBM       (BSP_U16)0x0001

/*E5776*/
#define HW_VER_PRODUCT_E5776_EM     (BSP_U16)0x0000

/*Epad, S10 101u */
#define HW_VER_PRODUCT_S10_101U     (BSP_U16)0x0401

/*Epad, S10 102u */
#define HW_VER_PRODUCT_S10_102U      (BSP_U16)0x0406

/*Epad, S10 LTE */
#define HW_VER_PRODUCT_S10_101L     (BSP_U16)0x0501

/*Epad, S10 Modem */
#define HW_VER_PRODUCT_S10_MODEM     (BSP_U16)0x0000

/*Epad, S10 Temp */
#define HW_VER_PRODUCT_S10_TEMP     (BSP_U16)0x0005

/*****************************************************************************
* 函 数 名  : BSP_HwGetVerMain
* 功能描述  : 获取产品版本号
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
BSP_U16 BSP_HwGetVerMain(BSP_VOID);

/*****************************************************************************
* 函 数 名  : BSP_GetProductName
* 功能描述  : 获取产品名称
* 输入参数  : char* pProductName,字符串指针，保证不小于32字节
*             BSP_U32 ulLength,缓冲区长度
* 输出参数  : 无
* 返 回 值  : 0：正确，非0: 失败
*****************************************************************************/
BSP_S32 BSP_GetProductName (char * pProductName, unsigned int ulLength);

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

typedef struct  tagUE_SW_BUILD_VER_INFO_STRU
{
    BSP_U16 ulVVerNo;        /* V部分 */
    BSP_U16 ulRVerNo;        /*  R部分*/
    BSP_U16 ulCVerNo;        /* C部分*/
    BSP_U16 ulBVerNo;         /* B部分*/
    BSP_U16 ulSpcNo;          /* SPC部分*/
    BSP_U16 ulCustomVer;     /* 客户需定制部分, 针对硬件接口低8bit PCB号,高8bitHW号*/
    BSP_U32 ulProductNo;     /* such as porting,CPE, ... */
    BSP_S8 acBuildDate[BUILD_DATE_LEN];  /* build日期,*/
    BSP_S8 acBuildTime[BUILD_TIME_LEN];  /* build时间*/
} UE_SW_BUILD_VER_INFO_STRU; /* 内部版本*/


typedef struct {
    BSP_U32   bandGU;         	/*支持的GU频段*/
    BSP_U32   bamdLTELow;         /*支持LTE频段，B1~B32*/
    BSP_U32   bamdLTEHigh;        /*支持LTE频段，B33~B64*/
}BAND_INFO_T;

typedef struct {
    BSP_U16  index;         /*硬件版本号数值(大版本号1+大版本号2)，区分不同产品*/
    BSP_U16   hwIdSub;         /*硬件子版本号，区分产品的不同的版本*/
    BSP_CHAR* name;           /*内部产品名*/
    BSP_CHAR* namePlus;       /*内部产品名PLUS*/
    BSP_CHAR* hwVer;          /*硬件版本名称*/
    BSP_CHAR* dloadId;        /*升级中使用的名称*/
    BSP_CHAR* productId;      /*外部产品名*/
    BAND_INFO_T  band;            /*产品支持的频段*/
    BAND_INFO_T  bandDiv;         /*产品支持的分集*/
    BSP_CHAR reserve[4];      /*预留*/
}PRODUCT_INFO_T;

/*****************************************************************************
* 函 数 名  : BSP_GetBuildVersion
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
const UE_SW_BUILD_VER_INFO_STRU* BSP_GetBuildVersion(BSP_VOID);


/*****************************************************************************
* 函 数 名  : BSP_HwGetHwVersion
* 功能描述  : 获取硬件版本名称
* 输入参数  : BSP_CHAR* pHwVersion,字符串指针，保证不小于32字节
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
BSP_S32 BSP_HwGetHwVersion (char* pFullHwVersion, BSP_U32 ulLength);


/*****************************************************************************
* 函 数 名  : BSP_GetSupportBands
*
* 功能描述  : 获取支持的频段
*
* 输入参数  : BAND_INFO_T *pBandInfo,频段信息结构体指针
* 输出参数  :
*
 返 回 值  : 0：正确，非0: 失败
*
* 其它说明  :
*
*****************************************************************************/
BSP_S32 BSP_GetSupportBands( BAND_INFO_T *pBandInfo);

/*****************************************************************************
* 函 数 名  : BSP_HwIsSupportWifi
* 功能描述  : 打印硬件版本信息,打桩
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  : 无
* 其它说明  : 无
*****************************************************************************/
BSP_BOOL BSP_HwIsSupportWifi(BSP_VOID);


/********************************************************************************************************
 函 数 名  : getHwVersionIndex
 功能描述  : 获取由HKADC读取的硬件ID经过拼装后的硬件索引值
 输入参数  : 无
 输出参数  : 硬件ID的索引值

 返 回 值  : 非-1:  操作成功；
             -1：操作失败。
********************************************************************************************************/
extern int getHwVersionIndex(void);
#define DRV_GET_HW_VERSION_INDEX()       getHwVersionIndex()


/*****************************************************************************
 函 数 名  : VerifySIMLock
 功能描述  : 判断当前解锁码是否正确 .
 输入参数  : imei       - 单板IMEI号
             unlockcode - 解锁码
 输出参数  : 无。
 返 回 值  : 1：   解锁成功
             0:    解锁失败
*****************************************************************************/
extern int VerifySL(char* UnlockCode, char* Key);
#define DRV_CARDLOCK_MD5_VERIFY(unlockcode, imei)  VerifySL(unlockcode, imei)


extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()


/* 当前版本是否支持某个模块 */
typedef enum tagBSP_MODULE_SUPPORT_E
{
    BSP_MODULE_SUPPORT     = 0,
    BSP_MODULE_UNSUPPORT   = 1,
    BSP_MODULE_SUPPORT_BUTTOM
}BSP_MODULE_SUPPORT_E;

/* 查询的模块类型 */
typedef enum tagBSP_MODULE_TYPE_E
{
    BSP_MODULE_TYPE_SD = 0x0,
    BSP_MODULE_TYPE_CHARGE,
    BSP_MODULE_TYPE_WIFI,
    BSP_MODULE_TYPE_OLED,
    BSP_MODULE_TYPE_HIFI,
    BSP_MODULE_TYPE_POWER_ON_OFF,
    BSP_MODULE_TYPE_HSIC,
    BSP_MODULE_TYPE_HSIC_NCM,
    BSP_MODULE_TYPE_LOCALFLASH,

    BSP_MODULE_TYPE_BUTTOM
}BSP_MODULE_TYPE_E;

/*****************************************************************************
 函 数 名  : BSP_CheckModuleSupport
 功能描述  : 查询模块是否支持
 输入参数  : enModuleType: 需要查询的模块类型
 输出参数  : 无
 返回值    ：BSP_MODULE_SUPPORT或BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType);

#define DRV_GET_BATTERY_SUPPORT()   BSP_CheckModuleSupport(BSP_MODULE_TYPE_CHARGE)

#define DRV_GET_WIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_WIFI)

#define DRV_GET_SD_SUPPORT()        BSP_CheckModuleSupport(BSP_MODULE_TYPE_SD)

#define DRV_GET_OLED_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_OLED)

#define DRV_GET_HIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HIFI)

#define DRV_GET_HSIC_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HSIC)


/*****************************************************************************
 函 数 名  : BSP_InitPlatformVerInfo
 功能描述  : 初始化芯片的版本号
 输入参数  : 无
 输出参数  : none
 返 回 值  : void
*****************************************************************************/
extern BSP_VOID BSP_InitPlatformVerInfo(BSP_VOID);
#define DRV_INIT_PLATFORM_VER() BSP_InitPlatformVerInfo()


extern BSP_S32  DRV_START_MODEGET(void);

/*****************************************************************************
 函 数 名  : BSP_GetPlatformInfo
 功能描述  : 获取芯片的版本号
 输入参数  : 无
 输出参数  : u32PlatformInfo:芯片的版本号
 返 回 值  : void
*****************************************************************************/
extern BSP_VOID BSP_GetPlatformInfo(unsigned long *u32PlatformInfo);
#define DRV_GET_PLATFORM_INFO(u32PlatformInfo) BSP_GetPlatformInfo(u32PlatformInfo)

#endif


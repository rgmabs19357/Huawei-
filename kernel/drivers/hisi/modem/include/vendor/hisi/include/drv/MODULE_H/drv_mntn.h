/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_mntn.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_mntn.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_MNTN_H__
#define __DRV_MNTN_H__
#include "drv_global.h"



typedef enum DRV_SHUTDOWN_REASON_tag_s
{
    DRV_SHUTDOWN_LOW_BATTERY,           /* 电池电量低                 */
    DRV_SHUTDOWN_BATTERY_ERROR,         /* 电池异常                   */
    DRV_SHUTDOWN_POWER_KEY,             /* 长按 Power 键关机          */
    DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* 过温保护关机               */
    DRV_SHUTDOWN_LOW_TEMP_PROTECT,
    DRV_SHUTDOWN_RESET,                 /* 系统软复位                 */
    DRV_SHUTDOWN_CHARGE_REMOVE,         /* 关机充电模式下，拔除充电器 */
    DRV_SHUTDOWN_UPDATE,                /* 关机并进入升级模式         */
    DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_ENUM;


#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))

/************************************************************************************
 *Function Name :  drvShutdown
 *Description   :  关闭系统(发送消息告知关机模块后立刻返回，实际关机由关机模块处理)
 *Others        :  No
************************************************************************************/
void drvShutdown( DRV_SHUTDOWN_REASON_ENUM eReason );


/************************************************************************************
 *Function Name :  drvPowerOff
 *Description   :  直接下电
 *Others        :  No
************************************************************************************/
void drvPowerOff( void );

/************************************************************************************
 *Function Name :  drvReboot(
 *Description   :  热复位(通过系统控制器的复位实现，不调电)
 *Others        :  No
************************************************************************************/
void drvReboot( void );

#endif
typedef int  (*pUartRecv)(unsigned char uPortNo, unsigned char* pData, unsigned short uslength);

#define PROCESS_ENTER(pADDRESS)  do { } while (0)
#define PROCESS_EXIT(pADDRESS)   do { } while (0)

typedef enum{
     ADDRTYPE8BIT,
     ADDRTYPE16BIT,
     ADDRTYPE32BIT
}ENADDRTYPE;

typedef enum{
     BOARD_TYPE_LTE_ONLY    = 0,
     BOARD_TYPE_GUL
}BOARD_TYPE_E;

typedef enum{
     BSP_MODEM_CORE         = 0,
     BSP_APP_CORE
}BSP_CORE_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     PV500_V9R1ES_CHIP
}BSP_CHIP_TYPE_E;

/******************************************************************************
* Function     :   BSP_OM_RegRead
*
* Description  :
*
* Input        :
*
* Output       :   无
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegRead(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 *pu32Value);


/******************************************************************************
* Function     :   BSP_OM_RegWrite
*
* Description  :
*
* Input        :
*
* Output       :   无
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegWrite(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 u32Value);

/******************************************************************************
* Function     :   BSP_OM_SoftReboot
*
* Description  :
*
* Input        :
*
* Output       :   无
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_SoftReboot(void);

/*****************************************************************************
* 函 数 名  : BSP_OM_GetBoardType
*
* 功能描述  : 获取单板类型
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : BSP单板类型枚举
*
* 其它说明  : 无
*
*****************************************************************************/
BOARD_TYPE_E BSP_OM_GetBoardType(BSP_VOID);

/*****************************************************************************
* 函 数 名  : BSP_GetHostCore
*
* 功能描述  : 查询当前CPU主从核类型
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : CPU主从核类型
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_CORE_TYPE_E BSP_GetHostCore(BSP_VOID);

/*****************************************************************************
* 函 数 名  : BSP_OM_GetChipType
*
* 功能描述  : 获取芯片类型
*
* 输入参数  : BSP_VOID
*
* 输出参数  : 无
*
* 返 回 值  : 芯片类型
*             PV500_CHIP:PV500芯片
*             V7R1_CHIP: V7R1芯片
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_CHIP_TYPE_E BSP_OM_GetChipType(BSP_VOID);

typedef struct tagBSP_OM_NET_S
{
    BSP_U32 u32NetRxStatOverFlow;       /* 接收FIFO溢出统计计数 */
    BSP_U32 u32NetRxStatPktErr;         /* 接收总错包计数 */
    BSP_U32 u32NetRxStatCrcErr;         /* 接收CRC错包计数 */
    BSP_U32 u32NetRxStatLenErr;         /* 接收无效长度包计数 */
    BSP_U32 u32NetRxNoBufInt;           /* 接收没有BUFFER中断计数 */
    BSP_U32 u32NetRxStopInt;            /* 接收停止中断计数 */
    BSP_U32 u32NetRxDescErr;            /* 接收描述符错误 */

    BSP_U32 u32NetTxStatUnderFlow;      /* 发送FIFO下溢统计计数 */
    BSP_U32 u32NetTxUnderFlowInt;       /* 发送FIFO下溢中断计数 */
    BSP_U32 u32NetTxStopInt;            /* 发送停止中断计数 */
    BSP_U32 u32NetTxDescErrPs;          /* 发送描述符错误(Ps) */
    BSP_U32 u32NetTxDescErrOs;          /* 发送描述符错误(Os) */
    BSP_U32 u32NetTxDescErrMsp;         /* 发送描述符错误(Msp) */

    BSP_U32 u32NetFatalBusErrInt;      /* 总线错误*/
}BSP_OM_NET_S;

/******************************************************************************
* Function     :   BSP_OM_NET
*
* Description  :
*
* Input        :
*
* Output       :   无
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_NET(BSP_OM_NET_S *pstNetOm);

/*VERSIONINFO_I数据结构中版本字符串最大有效字符长度*/
#define VER_MAX_LENGTH                  30

/*memVersionCtrl接口操作类型*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

#define OM_SAVE_EXCHFILE_ING            0
#define OM_SAVE_EXCHFILE_END            1


/*组件类型*/
typedef enum
{
    VER_BOOTLOAD = 0,
    VER_BOOTROM =1,
    VER_NV =2 ,
    VER_VXWORKS =3,
    VER_DSP =4 ,
    VER_PRODUCT_ID =5 ,
    VER_WBBP =6 ,
    VER_PS =7,
    VER_OAM =8,
    VER_GBBP =9 ,
    VER_SOC =10,
    VER_HARDWARE =11,
    VER_SOFTWARE =12,
    VER_MEDIA =13,
    VER_APP =14,
    VER_ASIC =15,
    VER_RF =16,
    VER_PMU =17,
    VER_PDM = 18,
    VER_PRODUCT_INNER_ID = 19,
    VER_INFO_NUM =20
}COMP_TYPE_I;

/* 三色灯状态编号*/
enum
{
    LED_LIGHT_SYSTEM_STARTUP,
    LED_LIGHT_POWER_ON,
    LED_LIGHT_G_REGISTERED,
    LED_LIGHT_W_REGISTERED,
    LED_LIGHT_G_CONNECTED,
    LED_LIGHT_W_CONNNECTED,
    LED_LIGHT_H_CONNNECTED,
    LED_LIGHT_OFFLINE,
    LED_LIGHT_FORCE_UPDATING,
    LED_LIGHT_NORMAL_UPDATING,
    LED_LIGHT_UPDATE_FAIL,
    LED_LIGHT_UPDATE_SUCCESS,
    LED_LIGHT_UPDATE_FILEFAIL,
    LED_LIGHT_UPDATE_NVFAIL,
    LED_LIGHT_SIM_ABSENT,
    LED_LIGHT_SHUTDOWN,
    LED_LIGHT_G_PLMN_SEARCH,
    LED_LIGHT_W_PLMN_SEARCH,
    LED_LIGHT_L_REGISTERED,
    LED_LIGHT_STATE_MAX = 32
};/*the state of LED */

enum SECURE_SUPPORT_STATUS_I
{
    SECURE_NOT_SUPPORT = 0,
    SECURE_SUPPORT = 1
};

enum SECURE_ENABLE_STATUS_I
{
    SECURE_DISABLE = 0,
    SECURE_ENABLE = 1
};

typedef enum                /* CACHE_TYPE */
{
    PS_OSAL_INSTRUCTION_CACHE ,
    PS_OSAL_DATA_CACHE
} PS_OSAL_CACHE_TYPE_I;

typedef int  (*OM_SAVE_FUNC)(int funcType, unsigned char *data, unsigned int* ulLength);

typedef struct
{
    unsigned char CompId;              /* 组件号：参见COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* 最大版本长度 30 字符+ \0 */
}VERSIONINFO_I;

#ifndef __SUPPORT_MAX_HSPA_CAPA_STRU
#define __SUPPORT_MAX_HSPA_CAPA_STRU
typedef struct
{
    unsigned char enHSDSCHSupport;          /*硬件是否支持HSDPA*/
    unsigned char ucHSDSCHPhyCategory;      /*硬件支持的最大HSDPA能力等级*/
    unsigned char enEDCHSupport;            /*硬件是否支持HSUPA*/
    unsigned char ucEDCHPhyCategory;        /*硬件支持的最大HSUPA能力等级*/
    unsigned int  reserved;                 /*预留*/
}SUPPORT_MAX_HSPA_CAPA_STRU;
#endif
/*****************************BSP_MspProcReg  begin******************************/
typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
/*****************************************************************************
* 函 数 名  : DRV_MSP_PROC_REG
*
* 功能描述  : DRV提供给OM的注册函数
*
* 输入参数  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* 输出参数  : NA
*
* 返 回 值  : NA
*
* 其它说明  : 可维可测接口函数
*
*****************************************************************************/
extern void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);


/*****************************************************************************
 函 数 名  : BSP_MNTN_GetFlashSpec
 功能描述  : Get flash infomation
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern int BSP_MNTN_GetFlashSpec(unsigned char * pFlashInfo, unsigned int ulLength);
#define DRV_GET_FLASH_INFO(pFlashInfo, usLength)    BSP_MNTN_GetFlashSpec (pFlashInfo, usLength )

/*************************************************
 函 数 名   : BSP_MNTN_ProductTypeGet
 功能描述   : 返回当前产品类型
 输入参数   : 无
 输出参数   : 无
 返 回 值   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern BSP_U32 BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()


/*****************************************************************************
 函 数 名  : BSP_MNTN_GetGsmPATemperature
 功能描述  : 获取GSM PA温度
 输入参数  : Temprature
             hkAdcTalble
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_GetGsmPATemperature(int *temperature, unsigned short *hkAdcTable);
#define DRV_GET_PA_GTEMP(temperature, hkAdcTable)   \
                BSP_MNTN_GetGsmPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 函 数 名  : getWcdmaPATemperature
 功能描述  : 获取WCDMA PA温度
 输入参数  : Temprature
             hkAdcTalble
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_GetWcdmaPATemperature (int *temperature, unsigned short *hkAdcTable);
#define  DRV_GET_PA_WTEMP(temperature, hkAdcTable)  \
              BSP_MNTN_GetWcdmaPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetSIMTemperature
 功能描述  : 获取SIM卡温度
 输入参数  : pusHkAdcTable：电磁电压表
 输出参数  : pTemp：        指向SIM卡温度的指针。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_GetSIMTemperature(int *plTemp, unsigned short *pusHkAdcTable);
#define DRV_GET_SIM_TEMP(plTemp, pusHkAdcTable)   \
               BSP_MNTN_GetSIMTemperature(plTemp, pusHkAdcTable)


/*****************************************************************************
 函 数 名  : BSP_MNTN_MemVersionCtrl
 功能描述  : 组件版本读写接口。
 输入参数  : pcData：当Mode为读的时候，为调用者待保存返回的组件版本信息的内存地址；
                     当Mode为写的时候，为调用者准备写入的组件版本信息的地址。
             ucLength：当Mode为读的时候，为调用者待保存返回的组件版本信息的内存大小；
                       当Mode为写的时候，为调用者准备写入的组件版本信息的字符数（不包括'\0'）。
             ucType：版本信息ID，
                     0： BOOTLOAD；
                     1： BOOTROM；
                     2： NV；
                     3： VXWORKS；
                     4： DSP；
                     5； CDROMISO；
                     6： PHY；
                     7： PS；
                     8： COM；
                     9： RF；
                     10：SOC；
                     11：HARDWARE；
                     12：SOFTWARE；
                     13：MEDIA；
                     14：APP；
                     15：INFO_NUM。
             ucMode：0：读取指定ID的组件版本信息；1：写入指定ID的组件版本信息。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_MemVersionCtrl(signed char *pcData, unsigned char ucLength, unsigned char ucType, unsigned char ucMode);
#define DRV_MEM_VERCTRL(pcData,ucLength,ucType,ucMode)  \
                          BSP_MNTN_MemVersionCtrl(pcData,ucLength,ucType,ucMode)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetFullHwVersion
 功能描述  : 硬件完整版本读接口。
 输入参数  : pFullHwVersion：为调用者待保存返回的硬件完整版本信息的内存首地址；
             ulLength      ：为调用者待保存返回的硬件完整版本信息的内存大小；
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_GetFullHwVersion(char * pFullHwVersion,unsigned int ulLength);
#define  DRV_GET_FULL_HW_VER(pFullHwVersion,ulLength)  \
               BSP_MNTN_GetFullHwVersion(pFullHwVersion,ulLength)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetProductIdInter
 功能描述  : 产品名称完整版本读接口。
 输入参数  : pProductIdInter：为调用者待保存返回的产品名称完整版本的内存首地址；
             ulLength       ：为调用者待保存返回的产品名称完整版本的内存大小；
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_GetProductIdInter(char * pProductIdInter, unsigned int ulLength);
#define  DRV_GET_PRODUCTID_INTER_VER(pProductIdInter,ulLength)  \
              BSP_MNTN_GetProductIdInter(pProductIdInter,ulLength)

/*****************************************************************************
 函 数 名  : BSP_MNTN_VersionQueryApi
 功能描述  : 查询所有组件的版本号。
 输入参数  : ppVersionInfo：待保存的版本信息地址。
 输出参数  : ucLength：待返回的数据的字节数。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_VersionQueryApi(void ** ppVersionInfo, unsigned int * ulLength);
#define  DRV_VER_QUERY(ppVersionInfo,ulLength)  \
              BSP_MNTN_VersionQueryApi (ppVersionInfo,ulLength)


/*****************************************************************************
 函 数 名  : DRV_SHUT_DOWN
 功能描述  : 单板关机
 输入参数  : 无
 输出参数  : eReason：        关机原因
 返 回 值  : 无
*****************************************************************************/
void drvShutdown( DRV_SHUTDOWN_REASON_ENUM eReason );
void DRV_SHUT_DOWN( DRV_SHUTDOWN_REASON_ENUM eReason );

typedef enum tagMNTN_FILE_TYPE_E
{
	MNTN_TYPE_ZSP = 0,
	MNTN_TYPE_HIFI,
    MNTN_TYPE_MAX
}MNTN_FILE_TYPE_E;

/*****************************************************************************
 函 数 名  : BSP_MNTN_ABBSelfCheck
 功能描述  : 返回abb自检结果
 输入参数  : None
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_ABBSelfCheck(void);
#define DRV_ABB_SELFCHECK()    BSP_MNTN_ABBSelfCheck()

/*****************************************************************************
 函 数 名  : BSP_MNTN_PmuSelfCheck
 功能描述  : PMU自检。
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_PmuSelfCheck(void);
#define DRV_PMU_SELFCHECK()    BSP_MNTN_PmuSelfCheck()

/*****************************************************************************
 函 数 名  : BSP_MNTN_I2cSelfCheck
 功能描述  : 返回I2c自检结果
 输入参数  : None
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
extern int BSP_MNTN_I2cSelfCheck(void);
#define DRV_I2C_SELFCHECK()    BSP_MNTN_I2cSelfCheck()

/*****************************************************************************
 函 数 名  : BSP_MNTN_SpiSelfCheck
 功能描述  : 返回spi自检结果
 输入参数  : None
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
extern int BSP_MNTN_SpiSelfCheck(void);
#define DRV_SPI_SELFCHECK()    BSP_MNTN_SpiSelfCheck()

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetCodecFuncStatus
 功能描述  : 获取CODEC功能状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 1:  CODEC存在
             0：CODEC 不存在
*****************************************************************************/
extern  int BSP_MNTN_GetCodecFuncStatus(void);
#define DRV_GET_CODEC_FUNC_STATUS()    BSP_MNTN_GetCodecFuncStatus()

/*****************************************************************************
 函 数 名  : MNTN_RFGLockStateGet
 功能描述  : 读取GSM RF锁定状态。
 输入参数  : 无。
 输出参数  : Status：存放锁定状态的输出值，
                        0：TX或者RX被锁定。
                        1：TX、RX都没有被锁定；

 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_RFGLockStateGet(unsigned int *Status);
#define DRV_GET_RF_GLOCKSTATE(Status)    BSP_MNTN_RFGLockStateGet(Status)

/****************************************************************************
 函 数 名  : BSP_MNTN_LedStateFuncReg
 功能描述  : 本接口为提供给协议栈的钩子函数，用于获取协议栈的点灯状态。
 输入参数  : 协议栈获取点灯状态函数的指针。
 输出参数  : 无。
 返 回 值  : 无。
 注意事项  : 无。

******************************************************************************/
extern void BSP_MNTN_LedStateFuncReg (pFUNCPTR p);
#define DRV_LED_STATE_FUNREG(p)    BSP_MNTN_LedStateFuncReg(p)

/*****************************************************************************
 函 数 名  : BSP_MNTN_LedFlush
 功能描述  : 三色灯设置。
 输入参数  : status：三色灯的状态，见LED_STATUS_I
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_LedFlush(unsigned long state);
#define DRV_LED_FLUSH(state)    BSP_MNTN_LedFlush(state)

/*****************************************************************************
 函 数 名  : BSP_MNTN_LedControlAddressGet
 功能描述  : 得到定制的点灯数据
 输入参数  : 无
 输出参数  : 无。
 返 回 值  : 点灯控制数据的全局变量地址
*****************************************************************************/
extern unsigned int BSP_MNTN_LedControlAddressGet(void);
#define DRV_LED_GET_ADDRESS()   BSP_MNTN_LedControlAddressGet()

/*****************************************************************************
 函 数 名  : BSP_MNTN_BootForceloadModeCheck
 功能描述  : 强制加载模式查询。
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 0：强制加载；
             1：非强制加载。
*****************************************************************************/
extern unsigned int BSP_MNTN_BootForceloadModeCheck(void);
#define DRV_BOOT_FORCELOAD_MODE_CHECK()    BSP_MNTN_BootForceloadModeCheck()

/*****************************************************************************
 函 数 名  : BSP_MNTN_BootFlagConfig
 功能描述  : 配置Bootline数据中的启动标志为快速自启动、倒计时7秒自启动或手动启动。
 输入参数  : ulBootFlag：暂未定义。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern  int BSP_MNTN_BootFlagConfig(unsigned int ulBootFlag);
#define DRV_BOOTFLAG_CFG(ulBootFlag)    BSP_MNTN_BootFlagConfig(ulBootFlag)

/*****************************************************************************
 函 数 名  : BSP_MNTN_CheckArmTCM
 功能描述  : TCM检测
 输入参数  : 无。
 输出参数  : 无。
 返回值：   0xffff0000：检测成功，TCM正常
            地址：检测出错的地址（0－0x5fff）
            0xffffffff:检测失败

*****************************************************************************/
extern unsigned int BSP_MNTN_CheckArmTCM(void);
#define DRV_CHECK_ARM_TCM()    BSP_MNTN_CheckArmTCM()

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExchOMSaveRegister
 功能描述  : 注册给底软的trace保存函数，用来在单板复位时，
             保存当前的信令和日志信息。
 输入参数  : funcType: 功能ID
             pFunc:注册的回调函数
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：相同的funcType只能注册一个回调函数，重复注册会覆盖原来函数
*****************************************************************************/
extern int BSP_MNTN_ExchOMSaveRegister(int funcType, OM_SAVE_FUNC *pFunc);
#define DRV_SAVE_REGISTER(funcType, pFunc)    BSP_MNTN_ExchOMSaveRegister(funcType, pFunc)

/*****************************************************************************
 函 数 名  : BSP_MNTN_SystemError
 功能描述  : 系统热启动。
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_SystemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);
#define DRV_SYSTEM_ERROR(modId, arg1, arg2, arg3, arg3Length)\
                   BSP_MNTN_SystemError(modId, arg1, arg2, arg3, arg3Length)

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExchMemMalloc
 功能描述  : 与systemOsaError接口一起用来记录大块的复位信息。
             目前最多支持128k.
 输入参数  : ulSize - 内存大小
 输出参数  : 无。
 返 回 值  : 内存地址
*****************************************************************************/
extern unsigned int BSP_MNTN_ExchMemMalloc(unsigned int ulSize);
#define DRV_EXCH_MEM_MALLOC(ulSize)    BSP_MNTN_ExchMemMalloc(ulSize)

/*****************************************************************************
 函 数 名  : BSP_MNTN_OmExchFileSave
 功能描述  : 用来记录ARM和DSP交互的异常文件
 输入参数  :    address：buffer地址
                length：存储长度
                IsFileEnd：1表示文件的最后一块，0表示非最后一块
 输出参数  : 无。
 返 回 值  : 0 为OK。
*****************************************************************************/
extern int BSP_MNTN_OmExchFileSave(void * address, unsigned long length,unsigned char IsFileEnd,unsigned char type);
#define DRV_EXCH_FILE_SAVE(address, length, IsFileEnd, type) BSP_MNTN_OmExchFileSave(address, length, IsFileEnd, type)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetHwGpioInfo
 功能描述  : Get flash infomation
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern int BSP_MNTN_GetHwGpioInfo(unsigned char *pGpioInfo, unsigned long usLength );
#define DRV_GET_GPIO_INFO(pGpioInfo, usLength)    BSP_MNTN_GetHwGpioInfo(pGpioInfo, usLength )

/*****************************************************************************
 函 数 名  : BSP_MNTN_Int4ToString
 功能描述  : 将寄存器的值转换为ASCII字符
 输入参数  : 寄存器的值，和转换字符的存储空间,最大空间不超过30byte
 输出参数  : 转换字符
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int BSP_MNTN_Int4ToString(unsigned int value, char * string);
#define DRV_MEM_VERCONVERT(value,string)    BSP_MNTN_Int4ToString(value, string)

/*****************************************************************************
 函 数 名  : BSP_MNTN_HeapInfoGet
 功能描述  : 获取单板侧的内存信息。
 输入参数  : allocSize: 已经分配的堆内存大小，单位byte。
             totalSize: 堆内存总尺寸，单位byte。
 输出参数  : None
 返 回 值  : 0: 操作成功；
             -1：  操作失败。
*****************************************************************************/
extern int BSP_MNTN_HeapInfoGet(unsigned int *allocSize, unsigned int *totalSize);
#define DRV_GET_HEAPINFO(allocSize, totalSize)    BSP_MNTN_HeapInfoGet(allocSize, totalSize)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetSupportBands
 功能描述  : 从底软获得当前支持的Bands.
 输入参数  : pusWBands - WCDMA的频段值
             pusGBands - GSM的频段值

 输出参数  : pusWBands - WCDMA的频段值
             pusGBands - GSM的频段值

 返 回 值  : 0：正确，非0: 失败
             通过Bit位来表示哪些频段支持。
*****************************************************************************/
extern int BSP_MNTN_GetSupportBands(unsigned short *pusWBands, unsigned short *pusGBands);
#define DRV_GET_SUPPORT_BANDS(pusWBands, pusGBands)    BSP_MNTN_GetSupportBands(pusWBands, pusGBands)

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetSupportDivBands
 功能描述  : 从底软获得当前支持的分级频段
 输入参数  : N/A

 输出参数  : pDivBands - 返回当前单板所支持的分级频段，频段按bit
 			      流方式排列(同W 和G的频段查询)

 返 回 值  : 0：正确，非0: 失败
*****************************************************************************/
extern int BSP_MNTN_GetSupportDivBands(unsigned short* pDivBands);
#define DRV_GET_SUPPORT_DIVBANDS(pDivBands)    BSP_MNTN_GetSupportDivBands(pDivBands)

/********************************************************************************************************
 函 数 名  : BSP_MNTN_WriteSysBackupFile
 功能描述  : 向FLASH备份ZSP、NV数据
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0:  操作成功；
             -1：操作失败。
********************************************************************************************************/
extern int BSP_MNTN_WriteSysBackupFile(void);
#define DRV_BACKUP_SYS_FILE()    BSP_MNTN_WriteSysBackupFile()

/*****************************************************************************
 函 数 名  : BSP_MNTN_GetExtAntenLockState
 功能描述  : 获取有线与无线的连接状态
 输入参数  : enModemId:0 - modem0
                       1 - modem1
 输出参数  : pulStatus:0 - 无线连接
                       1 - 有线连接
 返 回 值  : 0 - 成功
             其它为失败

*****************************************************************************/
extern int BSP_MNTN_GetExtAntenLockState(PWC_COMM_MODEM_E enModemId, unsigned int *pulStatus);
#define DRV_GET_ANTEN_LOCKSTATE(enModemId, pulStatus)    BSP_MNTN_GetExtAntenLockState(enModemId, pulStatus)

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExtAntenIntInstall
 功能描述  : 中断注册函数，用来获得当前的天线状态
 输入参数  : enModemId:0 - modem0
                       1 - modem1
             routine   - 中断处理函数
             para      - 当前的天线状态
 输出参数  : None
 返 回 值  : void

*****************************************************************************/
extern void BSP_MNTN_ExtAntenIntInstall(PWC_COMM_MODEM_E enModemId, void* routine, int para);
#define DRV_ANTEN_INT_INSTALL(enModemId, routine, para)    BSP_MNTN_ExtAntenIntInstall(enModemId, routine, para)

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExchHookFuncAdd
 功能描述  : 任务切换及中断钩子注册
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
extern void BSP_MNTN_ExchHookFuncAdd(void);
#define DRV_EXCH_HOOK_FUNC_ADD()    BSP_MNTN_ExchHookFuncAdd()

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExchHookFuncDelete
 功能描述  : 任务切换及中断钩子注销
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
*****************************************************************************/
extern void BSP_MNTN_ExchHookFuncDelete(void);
#define DRV_EXCH_HOOK_FUNC_DELETE()    BSP_MNTN_ExchHookFuncDelete()

/*****************************************************************************
 函 数 名  : BSP_MNTN_ExcStackPeakRecord
 功能描述  : 记录任务栈超标的任务信息.
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_ExcStackPeakRecord(void);
#define DRV_STACK_HIGH_RECORD()    BSP_MNTN_ExcStackPeakRecord()

/*****************************************************************************
 函 数 名  : BSP_MNTN_SubIntHook
 功能描述  : 二级中断服务钩子函数注册。可维可测相关
 输入参数  : p_Func：钩子函数指针。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_SubIntHook(pFUNCPTR p_Func);
#define DRV_VICINT_HOOK_ADD(p_Func)    BSP_MNTN_SubIntHook(p_Func)

/*****************************************************************************
 函 数 名  : BSP_MNTN_SubIntHookDel
 功能描述  : 二级中断服务钩子函数注销。可维可测相关
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_SubIntHookDel(void);
#define DRV_VICINT_HOOK_DEL()    BSP_MNTN_SubIntHookDel()

/*****************************************************************************
 函 数 名  : BSP_MNTN_IntBreakInHook
 功能描述  : 一级中断入口钩子函数注册。可维可测相关
 输入参数  : p_Func :钩子函数。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntBreakInHook(pFUNCPTR p_Func);
#define DRV_VICINT_IN_HOOK_ADD(p_Func)   BSP_MNTN_IntBreakInHook(p_Func)

/*****************************************************************************
 函 数 名  : BSP_MNTN_IntBreakInHookDel
 功能描述  : 一级中断入口钩子函数注销。可维可测相关
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntBreakInHookDel(void);
#define DRV_VICINT_IN_HOOK_DEL()    BSP_MNTN_IntBreakInHookDel()

/*****************************************************************************
 函 数 名  : BSP_MNTN_IntBreakOutHook
 功能描述  : 一级中断出口钩子函数注册。可维可测相关，V7先打桩
 输入参数  : p_Func: 钩子函数。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntBreakOutHook(pFUNCPTR p_Func);
#define DRV_VICINT_OUT_HOOK_ADD(p_Func)    BSP_MNTN_IntBreakOutHook(p_Func)

/*****************************************************************************
 函 数 名  : vicIntBreakOutHookDel
 功能描述  : 一级中断出口钩子函数注销。可维可测相关
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntBreakOutHookDel(void);
#define DRV_VICINT_OUT_HOOK_DEL()    BSP_MNTN_IntBreakOutHookDel()

/*****************************************************************************
 函 数 名  : BSP_MNTN_IntLvlChgHook
 功能描述  : 一级中断level change钩子函数注册。可维可测相关
 输入参数  : p_Func: 钩子函数。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntLvlChgHook(FUNCPTR_1 p_Func);
#define DRV_VICINT_LVLCHG_HOOK_ADD(p_Func)    BSP_MNTN_IntLvlChgHook(p_Func)

/*****************************************************************************
 函 数 名  : BSP_MNTN_IntLvlChgHookDel
 功能描述  : 一级中断level change钩子函数注销。可维可测相关
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
*****************************************************************************/
extern void BSP_MNTN_IntLvlChgHookDel(void);
#define DRV_VICINT_LVLCHG_HOOK_DEL()    BSP_MNTN_IntLvlChgHookDel()

/*****************************************************************************
 函 数 名  : vic_int_exit_hook_register
 功能描述  : 系统中断退出钩子函数中注册钩子函数接口
 输入参数  : FUNCPTR_1 p_Func
 输出参数  : 无
 返 回 值  : extern void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    修改内容   : 新生成函数

*****************************************************************************/
extern void vic_int_exit_hook_register(FUNCPTR_1 p_Func);
#define DRV_VICINT_EXIT_HOOK_ADD(p_Func)    vic_int_exit_hook_register(p_Func)

/*****************************************************************************
 函 数 名  : vic_int_exit_hook_unregister
 功能描述  : 系统中断退出钩子函数中注销钩子函数接口
 输入参数  : void
 输出参数  : 无
 返 回 值  : extern void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月20日
    修改内容   : 新生成函数

*****************************************************************************/
extern void vic_int_exit_hook_unregister(void);
#define DRV_VICINT_EXIT_HOOK_DEL()    vic_int_exit_hook_unregister()

/*****************************************************************************
 函 数 名  : BSP_MNTN_TFUPIfNeedNvBackup
 功能描述  : 使用TF卡升级前通过该接口判断是否需要备份NV项.
 输入参数  : None
 输出参数  : None
 返 回 值  : 1:需要备份
             0:无需备份
*****************************************************************************/
extern int BSP_MNTN_TFUPIfNeedNvBackup(void);
#define DRV_TF_NVBACKUP_FLAG()    BSP_MNTN_TFUPIfNeedNvBackup()

/*****************************************************************************
 函 数 名  : BSP_MNTN_GETSDSTATUS
 功能描述  : 返回SD卡在位状态
 输入参数  : 无。
 输出参数  : 无。
 返回值：   1在位
            0不在位

*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern int BSP_MNTN_GETSDSTATUS(void);
#define DRV_SDMMC_GET_STATUS()    BSP_MNTN_GETSDSTATUS()
#else
extern int BSP_SDMMC_GetSDStatus(void);
#define DRV_SDMMC_GET_STATUS()    BSP_SDMMC_GetSDStatus()
#endif

/*****************************************************************************
 函 数 名  : SDIO_read_write_blkdata
 功能描述  : SD卡读写接口
 输入参数  :    nCardNo     SD卡号
                dwBlkNo     块数
                nBlkCount   读写大小
                pbDataBuff  读写缓冲区
                nFlags      读/写
 输出参数  : 无。
 返回值：   0:  读写成功
            非0:错误码
*****************************************************************************/
extern int BSP_MNTN_SDRWBlkData(int nCardNo,unsigned int dwBlkNo,
                   unsigned int nBlkCount, unsigned char *pbDataBuff,int nFlags);
#define DRV_SDMMC_BLK_DATA_RW(nCardNo,dwBlkNo,nBlkCount,pbDataBuff,nFlags)   \
             BSP_MNTN_SDRWBlkData(nCardNo,dwBlkNo,nBlkCount,pbDataBuff, nFlags)

/*****************************************************************************
 函 数 名  : CicomClkEnable
 功能描述  : This routine enable CICOM IP clock gating.低功耗相关，V7打桩
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
/*extern void CicomClkEnable(void);*/
#define DRV_CICOM_CLK_ENABLE()

/*****************************************************************************
 函 数 名  : CicomClkDisable
 功能描述  : This routine disable CICOM IP clock gating.低功耗相关，V7打桩
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
/*extern void CicomClkDisable(void);*/
#define DRV_CICOM_CLK_DISABLE()

/*****************************************************************************
 函 数 名  : HdlcClkEnable
 功能描述  : This routine enable HDLC IP clock gating.低功耗相关，V7打桩
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
/*extern void HdlcClkEnable(void);*/
#define DRV_HDLC_CLK_ENABLE()

/*****************************************************************************
 函 数 名  : HdlcClkDisable
 功能描述  : This routine disable HDLC IP clock gating.低功耗相关，V7打桩
 输入参数  : None
 输出参数  : None
 返 回 值  : None
*****************************************************************************/
/*extern void HdlcClkDisable(void);*/
#define DRV_HDLC_CLK_DISABLE()

/*****************************************************************************
 函 数 名  : DRV_MEM_READ
 功能描述  : 按32位宽度查询内存，输出4字节数据。可维可测，V7先打桩
 输入参数  : ulAddress：查询地址空间地址，地址需在内存范围内，否则返回-1。
 输出参数  : pulData：指向查询内容的指针。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
extern int DRV_MEM_READ(unsigned int ulAddress, unsigned int* pulData);

/*****************************************************************************
 函 数 名  : DrvLogInstall
 功能描述  : 打印函数注册。可维可测，V7先打桩
 输入参数  : fptr 注册的函数指针
 输出参数  : None
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
/*extern int DrvLogInstall(PVOIDFUNC fptr, PVOIDFUNC fptr1, PVOIDFUNC fptr2, PVOIDFUNC fptr3, PVOIDFUNC fptr4);*/
#define DRV_LOG_INSTALL(fptr, fptr1, fptr2, fptr3, fptr4)     DRV_OK

/*****************************************************************************
* 函 数 名  : BSP_MNTN_GetBattState
*
* 功能描述  : 获取电池在位状态
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : 成功：0，1，2
              失败：负数
*
*
*****************************************************************************/
extern BSP_S32 BSP_MNTN_GetBattState(void);
#define DRV_MNTN_GET_BATT_STATE() BSP_MNTN_GetBattState()


/*******************************************************************************
 函 数 名: DRV_EXCH_CUST_FUNC_REG
 功能描述: 临终遗言模块提供对外接口，供上层注册回调，用于复位时保存上层指定信息
 输入参数: cb 上层指定回调接口
 输出参数: 无
 返 回 值: 0-添加成功，其他-添加失败
 说明    :  pucData :指定记录信息地址，请注意不要指定栈等临时数据区，堆空间数据，
                     使用者自己维护，包括空间使用完，自己释放。建议全局变量。
            aucName :名称
            ulDataLen: 数据长度

返回值列表:
    CUST_REG_OK = 0,                        添加成功
    CUST_REG_PARM_NULL,                     入参为空
    CUST_REG_EXCH_NOT_READY,                EXCH模块尚未初始化
    CUST_REG_EXCH_REBOOT_CONTEXT,           已经进入复位流程
    CUST_REG_EXCH_QUEUE_NOT_INIT,           注册队列尚未初始化
    CUST_REG_EXCH_QUEUE_FULL,               队列已满
    CUST_REG_EXCH_ALREADY_IN_QUEUE,         重复注册
    CUST_REG_EXCH_MUTEX_REJECT,             MUTEX REJECT
    CUST_REG_EXCH_QUEUE_IN_ERR              入队列失败

请通过返回值定位解决错误

*******************************************************************************/
#define EXCH_CB_NAME_SIZE           (32)
typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char *pucData;
    unsigned int  ulDataLen;
}cb_buf_t;

typedef int  (*exchCBReg)(cb_buf_t *);
extern int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb);

/*动态配置唤醒源*/
typedef enum 
{
    DRV_WAKE_SRC_UART0 = 0,
    DRV_WAKE_SRC_SOCP,
    DRV_WAKE_SRC_DRX_TIMER,
    DRV_WAKE_SRC_BUT
}DRV_PM_WAKE_SRC_ENUM;
/*****************************************************************************
* 函 数 名  : DRV_PM_SET_WAKE_SRC
* 功能描述  : 动态设置唤醒源
* 输入参数  : eWakeSrc 唤醒源枚举值
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
extern BSP_VOID BSP_PM_SetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src);
#define DRV_PM_SET_WAKE_SRC(eWakeSrc)   BSP_PM_SetWakeSrc(eWakeSrc)

/*****************************************************************************
* 函 数 名  : DRV_PM_UNSET_WAKE_SRC
* 功能描述  : 动态取消唤醒源
* 输入参数  : eWakeSrc 唤醒源枚举值
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
extern BSP_VOID BSP_PM_UnsetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src);
#define DRV_PM_UNSET_WAKE_SRC(eWakeSrc)   BSP_PM_UnsetWakeSrc(eWakeSrc)
#endif


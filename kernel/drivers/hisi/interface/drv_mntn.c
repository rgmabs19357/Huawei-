/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_mntn.c
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

/*多模测量标志寄存器*/
#define BBP_CTU_MEAS_FLAG_L_RD          (0x0640)
#define BBP_CTU_MEAS_FLAG_W_RD          (0x0644)
#define BBP_CTU_MEAS_FLAG_T_RD          (0x0648)
#define BBP_CTU_MEAS_FLAG_GM_RD         (0x064C)

extern int printf(const char *format, ...);

/*****************************************************************************
  2 函数声明
*****************************************************************************/

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern int exch_notifier_chain_register(exchCBReg cb);
extern int BSP_MEM_READ (unsigned int ulAddress, unsigned int* pulData);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

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

规格约束:
            缓冲区大小:64K。共分8个通道，每个通道均值最大不得超过8k.
            注册函数返回值为:
                正常:    ulDataLen data数据长度；
                异常:    0

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
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb)
{
    return exch_notifier_chain_register(cb);
}
#endif

/*****************************************************************************
 函 数 名  : DRV_MEM_READ
 功能描述  : 按32位宽度查询内存，输出4字节数据。可维可测，V7先打桩
 输入参数  : ulAddress：查询地址空间地址，地址需在内存范围内，否则返回-1。
 输出参数  : pulData：指向查询内容的指针。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
int DRV_MEM_READ (unsigned int ulAddress, unsigned int* pulData)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)    
    return BSP_MEM_READ(ulAddress, pulData);
#endif

#if (defined BSP_CORE_APP)
    return 0;   /* 打桩 */
#endif
}

void drvShutdown(DRV_SHUTDOWN_REASON_ENUM eReason)
{
    return;   /* 打桩 */
}

/*****************************************************************************
 函 数 名  : DRV_SHUT_DOWN
 功能描述  : 单板关机
 输入参数  : 无
 输出参数  : eReason：        关机原因
 返 回 值  : 无
*****************************************************************************/
void DRV_SHUT_DOWN( DRV_SHUTDOWN_REASON_ENUM eReason )
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#if( FEATURE_POWER_ON_OFF == FEATURE_ON )
    drvShutdown(eReason);
#else
    DRV_PRINTF("Function DRV_SHUT_DOWN unsupport!\n");
#endif
#endif

#if (defined BSP_CORE_APP)
    return;   /* 打桩 */
#endif
}

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
*****************************************************************************/
void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc)
{
    BSP_MspProcReg(eFuncID, pFunc);
}

#define printk(a)

int BSP_MNTN_BootFlagConfig(unsigned int ulBootFlag)
{
    return 0;
}
 
int BSP_MNTN_GetFlashSpec(unsigned char * pFlashInfo, unsigned int ulLength)
{
    return 0;
}

int BSP_MNTN_GetSupportBands(unsigned short *pusWBands, unsigned short *pusGBands)
{
    return 0;
}

int BSP_MNTN_RFGLockStateGet(unsigned int *Status)
{
    return 0;
}

int BSP_MNTN_WriteSysBackupFile(void)
{
    return 0;
}


BSP_BOOL DRV_MNTN_GetExtAntenLockState(unsigned int *Status)
{
    printk("stub: DRV_MNTN_GetExtAntenLockState\n");
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_MNTN_GETSDSTATUS
 功能描述  : 返回SD卡在位状态
 输入参数  : 无。
 输出参数  : 无。
 返回值：   1在位
            0不在位

*****************************************************************************/
int BSP_SDMMC_GetSDStatus(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return 0;   /* 打桩 */
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_OM_GetChipType
*
* 功能描述  : 获取芯片类型,HSO数采使用
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : BSP芯片类型枚举
*
* 其它说明  : 无
*
*****************************************************************************/
BSP_CHIP_TYPE_E BSP_OM_GetChipType(void)
{
    return 8; /* V9ASIC暂时写8，后续核对 */
}

/*****************************************************************************
* 函 数 名  : BSP_HwGetVerMain
* 功能描述  : 获取产品版本号,用于HSO链接时UE版本号的显示
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  :
*****************************************************************************/
BSP_U16 BSP_HwGetVerMain(void)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return (BSP_U16)(getHwVersionIndex());
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_TFUP_CompleteDeal
* 功能描述  : 装备使用,TL使用
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  :
*****************************************************************************/
BSP_VOID BSP_TFUP_CompleteDeal(void)
{
   return ; /* 打桩 */
}

/*****************************************************************************
* 函 数 名  : BSP_TBAT_Read
* 功能描述  : 装备使用,TL使用
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  :
*****************************************************************************/
BSP_S32 BSP_TBAT_Read(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return  0; /* 打桩 */
}

/*****************************************************************************
* 函 数 名  : BSP_TBAT_Write
* 功能描述  : 装备使用,TL使用
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
BSP_S32 BSP_TBAT_Write(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return 0; /* 打桩 */
}

/*****************************************************************************
* 函 数 名  : BSP_DLOAD_GetSoftwareVer
* 功能描述  : 获取软件版本号
* 输入参数  : BSP_S8 *str   :字符串缓冲区
*             BSP_S32 len   :字符串长度
* 输出参数  : BSP_S8 *str   :字符串缓冲区
* 返 回 值  : BSP_ERROR     :输入参数非法
*             其它          :返回字符串长度
* 其它说明  : AT模块调用
*             正常模式支持
*             下载模式支持
*****************************************************************************/
BSP_S32 BSP_DLOAD_GetSoftwareVer(BSP_CHAR *str, BSP_U32 len)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_MNTN_MemVersionCtrl((signed char*)str, (unsigned char)len, (unsigned char)VER_SOFTWARE, (unsigned char)VERIONREADMODE);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_GetProductName
* 功能描述  : 获取产品名称
* 输入参数  : char* pProductName,字符串指针，保证不小于32字节
*             BSP_U32 ulLength,缓冲区长度
* 输出参数  : 无
* 返 回 值  : 0：正确，非0: 失败
* 修改记录  :
*****************************************************************************/
BSP_S32 BSP_GetProductName (char * pProductName, unsigned int ulLength)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_MNTN_MemVersionCtrl((signed char*)pProductName, (unsigned char)ulLength, (unsigned char)VER_PRODUCT_ID, (unsigned char)VERIONREADMODE);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_HwGetHwVersion
* 功能描述  : 获取硬件版本名称
* 输入参数  : BSP_CHAR* pHwVersion,字符串指针，保证不小于32字节
* 输出参数  : 无
* 返 回 值  : 无
* 修改记录  :
*****************************************************************************/
BSP_S32 BSP_HwGetHwVersion (char* pFullHwVersion, BSP_U32 ulLength)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return BSP_MNTN_MemVersionCtrl((signed char*)pFullHwVersion, (unsigned char)ulLength, (unsigned char)VER_HARDWARE, (unsigned char)VERIONREADMODE);
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}

/*****************************************************************************
* 函 数 名  : BSP_PWC_GetMeansFlag
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  :
*****************************************************************************/
BSP_S32 BSP_PWC_GetMeansFlag(PWC_COMM_MODE_E enCommMode)
{
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    BSP_U32 pwc_meas_offset = 0;
    BSP_U32 pwc_meas_value = 0;

    switch(enCommMode){
            case PWC_COMM_MODE_WCDMA:
                pwc_meas_offset = BBP_CTU_MEAS_FLAG_W_RD;
                break;
            case PWC_COMM_MODE_GSM:
                pwc_meas_offset = BBP_CTU_MEAS_FLAG_GM_RD;
                break;
            case PWC_COMM_MODE_LTE:
                pwc_meas_offset = BBP_CTU_MEAS_FLAG_L_RD;
                break;
            case PWC_COMM_MODE_TDS:
                pwc_meas_offset = BBP_CTU_MEAS_FLAG_T_RD;
                break;
            default:
                return -1;
                break;
        }

    /*lint -e40*/
    BSP_REG_READ(SOC_BBP_COMM_BASE_ADDR, pwc_meas_offset, pwc_meas_value);
    /*lint +e40*/

    return pwc_meas_value;
#endif

#if (defined BSP_CORE_APP)
    return 0;
#endif
}
/*****************************************************************************
* 函 数 名  : BSP_BBPDMA_DrxBakReg
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
* 修改记录  :
*****************************************************************************/
BSP_S32 BSP_BBPDMA_DrxBakReg(void)
{
    return  0; /* 打桩 */
}

/*****************************************************************************
* 函 数 名  : BSP_CPU_GetTotalUtilize
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
BSP_U32 BSP_CPU_GetTotalUtilize(void)
{
    return  0; /* 打桩 */
}

/*****************************************************************************
 函 数 名  : BSP_GUSYS_ModeSwitchs
 功能描述  : 本接口实现WCDMA/GSM系统模式切换。
 输入参数  : uiSysMode：0：切换到WCDMA模式；1：切换到GSM模式。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
*****************************************************************************/
BSP_S32 BSP_GUSYS_ModeSwitch(BSP_U32 uiSysMode)
{
    return 0; /* 临时打桩，后续需要规格实现 */
}

/*****************************************************************************
* 函 数 名  : nand_isbad
* 功能描述  :
* 输入参数  :
* 输出参数  :
* 返 回 值  :
*****************************************************************************/
BSP_U32 nand_isbad(BSP_U32 blockID, BSP_U32 *flag)
{
    return 0; /* 打桩,返回NAND_OK */
}

/*****************************************************************************
* 函 数 名  : BSP_PM_SetWakeSrc
* 功能描述  : 动态设置唤醒源
* 输入参数  : eWakeSrc 唤醒源枚举值
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
BSP_VOID BSP_PM_SetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src)
{
    /*V9R1打桩处理*/
    return;
}

/*****************************************************************************
* 函 数 名  : BSP_PM_UnsetWakeSrc
* 功能描述  : 动态设置唤醒源
* 输入参数  : eWakeSrc 唤醒源枚举值
* 输出参数  : 无
* 返 回 值  : 无
*****************************************************************************/
BSP_VOID BSP_PM_UnsetWakeSrc(DRV_PM_WAKE_SRC_ENUM wake_src)
{
    /*V9R1打桩处理*/
    return;
}

/********************************************************************************************************
 函 数 名  : BSP_FS_GetDskspc
 功能描述  : 得到文件系统空间。(Modem Core,/yaffs0)
 输入参数  : path：文件系统路径。
 输出参数  : DskSpc：总空间。
                           UsdSpc：用过空间。
                           VldSpc：空闲空间。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
********************************************************************************************************/
int BSP_FS_GetDskspc(const char *path,unsigned int *DskSpc,unsigned int *UsdSpc,  unsigned int *VldSpc)
{
    return 0;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


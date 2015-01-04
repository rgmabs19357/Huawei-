/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_sd.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_sd.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_SD_H__
#define __DRV_SD_H__
#include "drv_global.h"
typedef enum _SD_EVENT
{
	SD_ATTATCH = 0,
	SD_REMOVE,
	SD_DETACH,      /*l00205892*/
	SD_EVENT_MAX
} SD_EVENT;


/************************************************************************
 * FUNCTION
 *       sdmmcUsbGetStatus
 * DESCRIPTION
 *       Get sd card in or out status
 * INPUTS
 *       NONE
 * OUTPUTS
 *       0: CARD IN 
          -1: CARD out
 *************************************************************************/

unsigned int  sdmmcUsbGetStatus(void);

#define WRFlAG     1
#define RDFlAG     0

typedef enum
{
    TFUP_FAIL = 0,  /*打叉*/
    TFUP_OK         /*打勾*/
}TFUP_DISPLAY_TYPE;

enum SD_MMC_OPRT_ENUM
{
    SD_MMC_OPRT_FORMAT = 0,
    SD_MMC_OPRT_ERASE_ALL,
    SD_MMC_OPRT_ERASE_SPEC_ADDR,
    SD_MMC_OPRT_WRITE,
    SD_MMC_OPRT_READ,
    SD_MMC_OPRT_BUTT
};

typedef unsigned int SD_MMC_OPRT_ENUM_UINT32;


/*SD卡设备类型*/
typedef struct _sd_dev_type_str
{
    unsigned long   devNameLen;
    char            devName[16];
}SD_DEV_TYPE_STR;

/*****************************************************************************
 函 数 名  : BSP_SDMMC_ATProcess
 功能描述  : at^sd,SD卡操作，写，擦除，格式化操作
 输入参数  : 操作类型 ulOp:
            0  格式化SD卡
            1  擦除整个SD卡内容；
            2  用于指定地址内容的擦除操作，指定擦除的内容长度为512字节。擦除后的地址中写全1
            3  写数据到SD卡的指定地址中，需要带第二个和第三个参数
            4  读取ulAddr指定的地址(ulAddr*512)的512个字节的内容到pucBuffer中

            ulAddr < address >  地址，以512BYTE为一个单位，用数字n表示

            ulData
             < data >            数据内容，表示512BYTE的内容，每个字节的内容均相同。
             0       字节内容为0x00
             1       字节内容为0x55
             2       字节内容为0xAA
             3       字节内容为0xFF

 输出参数  : pulErr
 返 回 值  : 0 ：OK  非 0 ：Error

            具体的错误值填充在*pulErr中
            0 表示SD卡不在位
            1 表示SD卡初始化失败
            2 表示<opr>参数非法，对应操作不支持(该错误由AT使用,不需要底软使用)
            3 表示<address>地址非法，超过SD卡本身容量
            4 其他未知错误
*****************************************************************************/
extern  unsigned long  BSP_SDMMC_ATProcess(SD_MMC_OPRT_ENUM_UINT32 ulOp,
                unsigned long ulAddr,  unsigned long ulData,unsigned char *pucBuffer,unsigned long *pulErr);
#define DRV_SDMMC_AT_PROCESS(ulOp,ulAddr,ulData,pucBuffer,pulErr)   \
                     BSP_SDMMC_ATProcess (ulOp,ulAddr,ulData,pucBuffer,pulErr)

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
/*****************************************************************************
* 函 数 名  : sd_mmc_blk_w
*
* 功能描述  :写卡接口
*
* 输入参数  : u32StartBlk 起始块
				  pu8DataBuf  写数据缓存
				  u32Len 写数据大小，必须为512字节的整数倍
* 输出参数  : NA
*
* 返 回 值  :  成功返回0
*
* 其它说明  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_w(BSP_U32 u32StartBlk,BSP_U8 *pu8DataBuf,BSP_U32 u32Len);
/*****************************************************************************
* 函 数 名  : sd_mmc_blk_r
*
* 功能描述  : 读卡接口
*
* 输入参数  : u32StartBlk 起始块
				  pu8DataBuf  读数据缓存
				  u32Len  读数据大小，必须为512字节的整数倍
* 输出参数  : NA
*
* 返 回 值  :  成功返回0
*
* 其它说明  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_r(BSP_U32 u32StartBlk,BSP_U8 *pu8DataBuf,BSP_U32 u32Len);
/*****************************************************************************
* 函 数 名  : sd_mmc_blk_erase
*
* 功能描述  : 卡块擦除接口
*
* 输入参数  : u32StartBlk 起始块
				  u32EndBlk  终止块
* 输出参数  : NA
*
* 返 回 值  :  成功返回0
*
* 其它说明  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_blk_erase(BSP_U32 u32StartBlk,BSP_U32 u32EndBlk);
/*****************************************************************************
* 函 数 名  : sd_mmc_get_status
*
* 功能描述  : 卡在位查询
*
* 输入参数  : void
* 输出参数  : NA
*
* 返 回 值  : 0 : 在位；-1: 不在位
*
* 其它说明  : NA
*
*****************************************************************************/
extern BSP_S32 sd_mmc_get_status(BSP_VOID);
#endif

/*****************************************************************************
 函 数 名  : BSP_SDMMC_GetOprtStatus
 功能描述  : at^sd,SD卡当前操作状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
            0: 未操作或操作已经完成;
            1: 操作中
            2: 上次操作失败
*****************************************************************************/
extern unsigned long BSP_SDMMC_GetOprtStatus(void);
#define DRV_SDMMC_GET_OPRT_STATUS()    BSP_SDMMC_GetOprtStatus()

/*****************************************************************************
 函 数 名  : BSP_SDMMC_AddHook
 功能描述  : TF模块钩子函数注册。
 输入参数  : hookType：回调函数类型，
                       0：获得升级文件信息后调用的回调函数；
                       1：TF卡插入通知OM的回调函数；
                       2：TF卡拔出通知OM的回调函数；
                       3； TF卡初始化后通知U盘的回调函数。
             p：回调函数指针。
 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项  ：对于同一类型回调函数，重复注册会覆盖以前设置。
*****************************************************************************/
/*#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
 */
extern int sdmmcAddHook (int hookType , void * p);/*y00186965 for sd_update*/
#define DRV_SDMMC_ADD_HOOK(hookType,p)    sdmmcAddHook(hookType,p)
/*#else
 */
/*extern int BSP_SDMMC_AddHook(int hookType, void * p);
 */
/*#define DRV_SDMMC_ADD_HOOK(hookType,p)    BSP_SDMMC_AddHook(hookType,p)
 */
/*#endif
 */

/*****************************************************************************
 函 数 名  : BSP_SDMMC_UsbGetStatus
 功能描述  : 返回SD卡状态
 输入参数  : 无。
 输出参数  : 无。
 返回值：   0  为可用
           非0 不可用

*****************************************************************************/
extern unsigned int BSP_SDMMC_UsbGetStatus(void);
#define DRV_SDMMC_USB_STATUS()    BSP_SDMMC_UsbGetStatus();

/*****************************************************************************
* 函 数 名  : sdmmc_ClearWholeScreen
* 功能描述  : SD卡升级NV恢复后的显示，清屏
* 输入参数  : 无
* 输出参数  : 无
* 返 回 值  :无
* 其它说明  : 无
*****************************************************************************/
extern void sdmmc_ClearWholeScreen(void);
#define DRV_SDMMC_CLEAR_WHOLE_SCREEN()    sdmmc_ClearWholeScreen()

/*****************************************************************************
* 函 数 名  : sdmmc_UpdateDisplay
* 功能描述  : SD卡升级NV恢复后的显示，显示
* 输入参数  : BOOL UpdateStatus
* 输出参数  : 无
* 返 回 值  :无
* 其它说明  : 升级成功，NV备份完成后调用该函数打勾
              升级失败后调用该函数打叉
*****************************************************************************/
extern void sdmmc_UpdateDisplay(unsigned int UpdateStatus);
#define DRV_SDMMC_UPDATE_DISPLAY(state)    sdmmc_UpdateDisplay(state)

/*****************************************************************************
* 函 数 名  : DRV_SD_GET_STATUS
*
* 功能描述  : 卡在位查询
*
* 输入参数  : void
* 输出参数  : NA
*
* 返 回 值  : 0 : 在位；-1: 不在位
*
* 其它说明  : NA
*
*****************************************************************************/
extern int DRV_SD_GET_STATUS(void);

/*****************************************************************************
* 函 数 名  : DRV_SD_GET_CAPACITY
*
* 功能描述  : 卡容量查询
*
* 输入参数  : void
* 输出参数  : NA
*
* 返 回 值  : 0 : 失败；>0: 卡容量
*
* 其它说明  : NA
*
*****************************************************************************/
extern int DRV_SD_GET_CAPACITY(void);

/*****************************************************************************
* 函 数 名  : DRV_SD_TRANSFER
*
* 功能描述  : 数据传输
*
* 输入参数  : struct scatterlist *sg    待传输数据结构体指针
                            unsigned dev_addr   待写入的SD block 地址
                            unsigned blocks    待写入的block个数
                            unsigned blksz      每个block的大小，单位字节
                            int wrflags    读写标志位，写:WRFlAG ; 读:RDFlAG
* 输出参数  : NA
*
* 返 回 值  : 0 : 成功；其它: 失败
*
* 其它说明  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_TRANSFER(struct scatterlist *sg, unsigned dev_addr,unsigned blocks, unsigned blksz, int wrflags);
#endif
/*****************************************************************************
* 函 数 名  : DRV_SD_SG_INIT_TABLE
*
* 功能描述  : SD多块数据传输sg list初始化
*
* 输入参数  : const void *buf		待操作的buffer地址
				  unsigned int buflen	待操作的buffer大小，小于32K, 大小为512B的整数倍
				  					大于32K, 大小为32KB的整数倍，最大buffer为128K
* 输出参数  : NA
*
* 返 回 值  :  0 : 成功;  其它:失败
* 其它说明  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_SG_INIT_TABLE(const void *buf,unsigned int buflen);
#endif
/*****************************************************************************
* 函 数 名  : DRV_SD_MULTI_TRANSFER
*
* 功能描述  : SD多块数据传输
*
* 输入参数  : unsigned dev_addr	待写入的SD block地址
				  unsigned blocks		待写入的block 个数
				  unsigned blksz		每个block 的大小，单位字节
				  int write			读写标志位，写:1;	读:0
* 输出参数  : NA
*
* 返 回 值  :  0 : 成功;  其它:失败
* 其它说明  : NA
*
*****************************************************************************/
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#else
extern int DRV_SD_MULTI_TRANSFER(unsigned dev_addr,unsigned blocks,unsigned blksz,int write);
#endif
/*****************************************************************************
 函 数 名  : BSP_MNTN_GetSDDevName
 功能描述  : 获取设备列表中的SD设备名
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : SD_DEV_TYPE_STR结构指针。
*****************************************************************************/
extern SD_DEV_TYPE_STR * BSP_MNTN_GetSDDevName(void);
#define DRV_GET_SD_PATH()     BSP_MNTN_GetSDDevName()

#endif


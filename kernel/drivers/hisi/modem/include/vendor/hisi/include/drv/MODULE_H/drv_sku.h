/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_sku.h
  版 本 号   : 初稿
  生成日期   : 2013年3月15日
  最近修改   :
  功能描述   : drv_sku.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月15日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_SKU_H__
#define __DRV_SKU_H__
#include "drv_global.h"


#define NV_MAX_CARRIER_PATH_LEN         (100)                    /* 运营商路径最大长度 不包括\0*/
#define NV_MAX_IMAGE_PATH_LEN           (100)                     /* IMAGE 路径最大长度 不包括\0*/
/* 运营商和运营商切换标记 */
typedef struct
{
    char     acCurrentCarrierPath[NV_MAX_CARRIER_PATH_LEN + 1]; /* 当前运营商路径*/
    char     acSwitchCarrierPath[NV_MAX_CARRIER_PATH_LEN + 1];  /* 切换运营商路径*/
    char     acCurrentImagePath[NV_MAX_IMAGE_PATH_LEN + 1];     /* 当前Image路径 */
    char     acSwitchImagePath[NV_MAX_IMAGE_PATH_LEN + 1];      /* 待切换Image路径 */
    unsigned long  ulCarrierSwitchFlag;      /* 0:无需切换 1：需要切换 */
    unsigned long  ulImageSwitchFlag;        /* 0:无需切换 1：需要切换 */
}SKU_SWITCH_FLAG_STRU;

/*****************************************************************************
函 数 名  : signed long sku_drv_get_carrier_path
功能描述  : 给OM提供接口，查询指定运营商路径
输入参数  :
char   *pcCarrierName         运营商名称
unsigned long  ulCarrierNameLen     运营商名称长度
char   *pcCurrentCarrierPath  对应运营商路径
unsigned long *pulCurrentCarrierPathLen 对应运营商路径的长度
返回值    : OSAL_OK     成功
            OSAL_ERROR  失败

***************************************************************************/
signed long sku_drv_get_carrier_path(
                                    char    *pcCarrierName,
                                    unsigned long   ulCarrierNameLen,
                                    char    *pcCurrentCarrierPath,
                                    unsigned long  *pulCurrentCarrierPathLen);

#define DRV_GET_CARRIER_PATH(pcCarrierName,ulCarrierNameLen,pcCurrentCarrierPath,pulCurrentCarrierPathLen)  \
        sku_drv_get_carrier_path(pcCarrierName,ulCarrierNameLen,pcCurrentCarrierPath,pulCurrentCarrierPathLen)


/*****************************************************************************
函 数 名  : sku_switch_flag_file_read
功能描述  : 切换标识读函数
输入参数  :
            SKU_SWITCH_FLAG_STRU * pstSkuUpdateSwitchFlag 切换镜像的路径
输出参数  : 无
返 回 值  : SKU_OK 成功
            SKU_ERROR 失败
***************************************************************************/
int sku_switch_flag_file_read(SKU_SWITCH_FLAG_STRU * pstSkuUpdateSwitchFlag);
#define DRV_READ_SWITCH_FLAG(pstSkuUpdateSwitchFlag) \
        sku_switch_flag_file_read(pstSkuUpdateSwitchFlag)


/*****************************************************************************
函 数 名  : sku_switch_flag_file_write
功能描述  : 切换标识写函数
输入参数  :
            SKU_SWITCH_FLAG_STRU * pstSkuUpdateSwitchFlag 切换镜像的路径
输出参数  : 无
返 回 值  : SKU_OK 成功
            SKU_ERROR 失败
***************************************************************************/

int sku_drv_write_switch_flag(SKU_SWITCH_FLAG_STRU *pstSkuUpdateSwitchFlag);
#define DRV_WRITE_SWITCH_FLAG(pstSkuUpdateSwitchFlag) \
        sku_drv_write_switch_flag(pstSkuUpdateSwitchFlag)


/*****************************************************************************
函 数 名  : sku_get_current_image_path
功能描述  : 获得当前使用的image路径
输入参数  : 无

输出参数  : 无
返 回 值  : img_ptr
***************************************************************************/
int sku_get_current_image_path(char * pcImagePath);
#define DRV_GET_CURRENT_IMAGE_PATH(pcImagePath) \
        sku_get_current_image_path(pcImagePath)

/*****************************************************************************
函 数 名  : sku_get_available_carrier_path
功能描述  : 在当前Image下，获取一个可用的运营商路径
输入参数  :  char     *pcCarrierPath     运营商存放地址
              VOS_UNIT *pulCarrierPathLen  最大长度

输出参数  : char     *pcCarrierPath     运营商存放地址
             VOS_UNIT *pulCarrierPathLen 运营商地址实际长度
返 回 值  : img_ptr
***************************************************************************/
signed long sku_get_available_carrier_path(char * pcCarrierPath, unsigned long *pulCarrierPathLen);
#define DRV_GET_AVAILABLE_CARRIER_PATH(pcImagePath, pulCarrierPathLen)\
        sku_get_available_carrier_path(pcImagePath, pulCarrierPathLen)

/*****************************************************************************
函 数 名  : sku_drv_return_Image_path
功能描述  : 通过Image名称获取Image路径
输入参数  : 无

输出参数  : 无
返 回 值  : int 0 创建成功 其它创建失败
***************************************************************************/
int sku_drv_return_image_path(char *pcImageName, char *pcImagePath);
#define DRV_GET_IMAGE_PATH(pcFileName, pcImagePath) \
        sku_drv_return_image_path(pcFileName, pcImagePath)

#endif


/******************************************************************************

                  版权所有 (C), 2001-2013, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_nve.h
  版 本 号   : 初稿
  生成日期   : 2013年6月27日
  最近修改   :
  功能描述   : drv_nve.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月27日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_NVE_H__
#define __DRV_NVE_H__
#include "drv_global.h"

#define BSP_NVE_NAME_LENGTH          8       /*NV name maximum length*/
#define BSP_NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define BSP_NV_READ                 1       /*NV read  operation*/
#define BSP_NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	BSP_U32 nv_operation;              /*0-write,1-read*/
	BSP_U32 nv_number;                 /*NV number you want to visit*/
	BSP_S8 nv_name[BSP_NVE_NAME_LENGTH];
	BSP_U32 valid_size;
	BSP_U8 nv_data[BSP_NVE_NV_DATA_SIZE];
}NVE_INFO_S;

/*****************************************************************************
* 函 数 名  : DRV_NVE_ACCESS
*
* 功能描述  : 访问LINUX NVE
*
* 输入参数  : nve  ID
*
* 输出参数  : 无
*
* 返 回 值  : OK& ERROR
*
*****************************************************************************/
BSP_S32 DRV_NVE_ACCESS(NVE_INFO_S *nve);


#endif


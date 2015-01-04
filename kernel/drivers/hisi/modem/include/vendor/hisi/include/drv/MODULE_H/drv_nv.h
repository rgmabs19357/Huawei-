/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_nv.h
  版 本 号   : 初稿
  生成日期   : 2013年2月2日
  最近修改   :
  功能描述   : drv_nv.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_NV_H__
#define __DRV_NV_H__
#include "drv_global.h"
#if (defined(FEATURE_E5) &&  defined(FEATURE_HILINK) && ((FEATURE_E5 == FEATURE_ON) || (FEATURE_HILINK == FEATURE_ON)))
/*应用请用此宏进行延时,单位是10ms*/
#define  APP_SLEEP(tick)   drv_sleep((tick), (unsigned int )__FILE__, __LINE__)
#endif

/***************************************************************
*  函数名        :   BSP_MMI_TestResultSet
*  函数功能      :   本接口是将MMI的测试标志写入NV
                     若ulFlag == 1 则写入 “ST P”
                     若ulFlag == 0 则写入 “ST F”
*  输入参数      :   BSP_U32 ulFlag
*  输出参数      :   无
*  返回值        :   成功(0)  失败(-1)
***************************************************************/
int BSP_MMI_TestResultSet(unsigned int ulFlag);
#define DVR_MMI_TEST_RESULT_SET(ulFlag) BSP_MMI_TestResultSet(ulFlag)

/***************************************************************
*  函数名        :   BSP_MMI_TestResultGet
*  函数功能      :   本接口比较MMI NV中的是否是“ST P”
                                  是返回1   不是返回0
*  输入参数      :   无
*  输出参数      :   无
*  返回值        :   成功(1)  失败(0)
***************************************************************/
unsigned int BSP_MMI_TestResultGet(void);
#define DVR_MMI_TEST_RESULT_GET() BSP_MMI_TestResultGet()

/*****************************************************************************
 函 数 名  : BSP_PROD_GetRecoverNvInfo
 功能描述  : 从底软获得当前需要覆盖的NV信息
 输入参数  : N/A

 输出参数  : ppNvInfo  - 指向NV信息结构体的数组
             pulNvNum  - 数组个数

 返 回 值  : 0：正确，非0: 失败
*****************************************************************************/
extern  int BSP_PROD_GetRecoverNvInfo(void **ppNvInfo, unsigned long *pulNvNum);
#define  DRV_GET_RECOVER_NV_INFO(ppNvInfo, pulNvNum)  \
                BSP_PROD_GetRecoverNvInfo(ppNvInfo, pulNvNum)

/*****************************************************************************
 函 数 名  : DRV_COPY_NVUSE_TO_NVBACKUP
 功能描述  : 将NV从使用区拷贝到备份区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int，0成功，其它失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月21日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_COPY_NVUSE_TO_NVBACKUP ( void );


/*****************************************************************************
 函 数 名  : DRV_COPY_NVUPGRADE_TO_NVUSE
 功能描述  : 将NV从升级区拷贝到使用区
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int，0成功，其它失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月21日
    修改内容   : 新生成函数

*****************************************************************************/
extern int DRV_COPY_NVUPGRADE_TO_NVUSE( void );

#endif


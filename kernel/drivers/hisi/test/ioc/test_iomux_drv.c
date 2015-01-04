/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_iomux_drv.c
  版 本 号   : 初稿
  生成日期   : 2012年10月15日
  最近修改   :
  功能描述   : test_iomux_drv
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月15日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <linux/mux.h>
#include  "test_acore.h"
#include  "test_iomux_drv.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
int test_iomux_get_config(void)
{
    if (0 == iomux_get_block("block_uart0"))
        return ERROR;
    if (0 == iomux_get_blockconfig("block_uart0"))
        return ERROR;
    return OK;
}












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


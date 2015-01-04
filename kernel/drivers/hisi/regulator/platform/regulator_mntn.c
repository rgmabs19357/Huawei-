/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : regulator_mntn.c
  版 本 号   : 初稿
  作    者   : 王振伟 176398
  生成日期   : 2012年12月19日
  最近修改   :
  功能描述   : regulator可谓可测相关接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月19日
    作    者   : 王振伟 176398
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>



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

/*this function is get regulator name in order to trace*/
const char *regulator_platform_get_name(struct regulator_dev *rdev)
{
    if (rdev == NULL) {
        return "Invalid Regulator Device";
    }
    if (rdev->constraints && rdev->constraints->name)
        return rdev->constraints->name;
    else if (rdev->desc->name)
        return rdev->desc->name;
    return "error";
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


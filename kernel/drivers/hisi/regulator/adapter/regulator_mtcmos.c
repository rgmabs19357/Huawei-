/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : regulator_mtcmos.c
  版 本 号   : 初稿
  作    者   : 王振伟 176398
  生成日期   : 2012年12月19日
  最近修改   :
  功能描述   : mtcmos电源操作适配层，用于对接regulator平台驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月19日
    作    者   : 王振伟 176398
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include "regulator_mtcmos.h"
#include "regulator_mntn.h"
#include "mtcmos_driver.h"


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

int regulator_mtcmos_is_enabled(struct regulator_dev *dev)
{
    int  regulator_id;
    int ret;

    rdev_info(dev, "%s func is called\n", __func__);
    regulator_id =  rdev_get_id(dev);

    ret = mtcmos_power_status(regulator_id);
    if (MTCMOS_MODULE_STATUS_ON == ret) {
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

int regulator_mtcmos_enable(struct regulator_dev *dev)
{
    int  regulator_id;
    int ret;

    rdev_info(dev, "%s func is called\n", __func__);
    regulator_id =  rdev_get_id(dev);

    ret = mtcmos_power_on(regulator_id);
    if (MTCMOS_MODULE_OK == ret) {
        ret = 0;
    } else {
        ret = -1;
    }

    return ret;
}
int regulator_mtcmos_disable(struct regulator_dev *dev)
{
    int  regulator_id;
    int ret;

    rdev_info(dev, "%s func is called\n", __func__);
    regulator_id =  rdev_get_id(dev);

    ret = mtcmos_power_off(regulator_id);
    if (MTCMOS_MODULE_OK == ret) {
        ret = 0;
    } else {
        ret = -1;
    }

    return ret;
}

struct regulator_ops regulator_mtcmos_ops = {
    .is_enabled = regulator_mtcmos_is_enabled,
    .enable = regulator_mtcmos_enable,
    .disable = regulator_mtcmos_disable,
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


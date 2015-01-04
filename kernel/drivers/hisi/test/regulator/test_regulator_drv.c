/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_regulator_drv.c
  版 本 号   : 初稿
  生成日期   : 2012年10月15日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2012年10月15日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include  <linux/regulator/consumer.h>
#include  <linux/err.h>
#include  "test_acore.h"
#include  "test_regulator_drv.h"



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
int test_regulator_get(void)
{
     struct regulator *g3d_regulator;
     g3d_regulator = regulator_get(NULL,"vcc_g3d");

     if (IS_ERR(g3d_regulator))
     {
         printk(KERN_ERR "the function regulator_get return value : %ld",PTR_ERR(g3d_regulator));
         return ERROR;
     }
     regulator_put(g3d_regulator);
     return OK;

}
int test_regulator_enable(void)
{
     struct regulator *g3d_regulator;
     int ret;
     g3d_regulator = regulator_get(NULL,"vcc_g3d");

     if (IS_ERR(g3d_regulator))
     {     
         printk(KERN_ERR "the regulator_get return value : %ld",PTR_ERR(g3d_regulator));
         return ERROR;
     }

     ret = regulator_enable(g3d_regulator);
     if (ret < 0)
     {
         printk(KERN_ERR "the regulator_enable return value : %d",ret);
         regulator_put(g3d_regulator);
         return ERROR;
     }

     ret = regulator_disable(g3d_regulator);
     regulator_put(g3d_regulator);
     return OK;

}

int test_regulator_disable(void)
{
     struct regulator *g3d_regulator;
     int ret;
     g3d_regulator = regulator_get(NULL,"vcc_g3d");

     if (IS_ERR(g3d_regulator))
     {     
         printk(KERN_ERR "the regulator_get return value : %ld",PTR_ERR(g3d_regulator));
         return ERROR;
     }

     ret = regulator_enable(g3d_regulator);
     if (ret < 0)
     {
         printk(KERN_ERR "the regulator_enable return value : %d",ret);
         regulator_put(g3d_regulator);
         return ERROR;
     }

     ret = regulator_disable(g3d_regulator);
     if (ret < 0)
     {
         printk(KERN_ERR "the regulator_disable return value : %d",ret);
         regulator_put(g3d_regulator);
         return ERROR;
     }
     regulator_put(g3d_regulator);
     return OK;

}











#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


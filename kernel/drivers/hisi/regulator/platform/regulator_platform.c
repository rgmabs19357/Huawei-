/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : regulator_platform.c
  版 本 号   : 初稿
  作    者   : 王振伟 176398
  生成日期   : 2012年12月19日
  最近修改   :
  功能描述   : regulator 平台注册及去注册等平台相关功能实现
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月19日
    作    者   : 王振伟 176398
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/slab.h>
#include <mach/platform.h>
#include <hsad/config_mgr.h>
#include "regulator_platform.h"
#include "regulator_mntn.h"
#include <regulator_desc.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
static struct regulator_desc* regulators = NULL;
#if 0
struct regulator * g_regulator_handle = NULL;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
void get_regulator_handle(unsigned int id, unsigned int user_index)
{
    printk("%s is called\n", __func__);

    if(30 == user_index)
    {
        g_regulator_handle = regulator_get(NULL, "SCU_VDD");
        printk("power name:%s", "SCU_VDD");
    }
    else {
        printk("supply name:%s\n", platform_regulators[id].consumer_supplies[user_index].supply);
        g_regulator_handle = regulator_get(NULL, platform_regulators[id].consumer_supplies[user_index].supply);
    }

    printk("%s: ret value:%d\n",__func__, (int)g_regulator_handle);
}

int is_regulator_enable()
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_is_enabled(g_regulator_handle);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int enable_regulator()
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_enable(g_regulator_handle);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int disable_regulator()
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_disable(g_regulator_handle);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int get_regulator_voltage()
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_get_voltage(g_regulator_handle);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int set_regulator_voltage(int min, int max)
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_set_voltage(g_regulator_handle, min, max);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int get_regulator_mode()
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_get_mode(g_regulator_handle);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}

int set_regulator_mode(int mode)
{
    int ret = -1;

    printk("%s is called\n", __func__);

    if(g_regulator_handle != NULL) {
        ret = regulator_set_mode(g_regulator_handle, mode);
    }
    else {
        printk("please get regulator handle at first\n");
    }

    return ret;
}
#endif

unsigned int get_boardid(void);

#ifdef _DRV_LLT_
int regulator_platform_probe(struct platform_device *pdev)
#else
static __devinit int regulator_platform_probe(struct platform_device *pdev)
#endif
{
    int regulator_id;
    unsigned int board_id = get_boardid();
    struct regulator_config_desc_table *table_item = NULL;

    struct regulator_platform_data  *regulator_platform_data;
    struct regulator_init_data *regulator_init_data = (struct regulator_init_data *)pdev->dev.platform_data;

    printk("%s enter...\r\n",__func__);
    regulator_platform_data = kzalloc(sizeof(*regulator_platform_data), GFP_KERNEL);
    if (regulator_platform_data == NULL) {
        rdev_err(NULL, "regulator kzalloc mem fail,please check!\n");
        return -ENOMEM;
    }

    /* get the target regulator des coresponding with board id */
    table_item = &(regulators_total[0]);
    while (REGULATOR_CONFIG_DESC_TBL_END_SYMBOL != table_item->board_id) {
        if (board_id == table_item->board_id) {
            break;
        }
        table_item++;
    }
    if (REGULATOR_CONFIG_DESC_TBL_END_SYMBOL == table_item->board_id){
        printk("Get regulator desc fail!, not match with %d.\n", table_item->board_id);
        goto err_free_mem;
    }
    regulators = table_item->table;

    /*register all regulator*/
    for (regulator_id = 0; regulator_id < REGULATORS_TOTAL_NUM; regulator_id++) {
        regulator_platform_data->rdev[regulator_id] = regulator_register(&regulators[regulator_id], &pdev->dev,
                regulator_init_data + regulator_id, regulator_platform_data);
        if (IS_ERR(regulator_platform_data->rdev[regulator_id])) {
            //rdev_err(regulator_platform_data->rdev[regulator_id], "regulator register faile\n");
            printk("regualtor_id %d, errno %d\n", regulator_id, (int)regulator_platform_data->rdev[regulator_id]);
            goto err_free_mem;
        }
    }

    platform_set_drvdata(pdev, regulator_platform_data);
    return 0;

err_free_mem:
    printk("%s failed!!!\r\n",__func__);
    kfree(regulator_platform_data);
    return -ENOMEM;
}
static __devexit int regulator_platform_remove(struct platform_device *pdev)
{
    int regulator_id;
    struct regulator_platform_data *regulator_platform_data;

    regulator_platform_data = platform_get_drvdata(pdev);
    if (NULL == regulator_platform_data) {
        pr_err("%s %d, platform_get_drvdata is NULL\n", __func__, __LINE__);
        return -1;
    }

    for (regulator_id = 0; regulator_id < REGULATORS_TOTAL_NUM; regulator_id++) {
        if (!IS_ERR(regulator_platform_data->rdev[regulator_id])) {
            regulator_unregister(regulator_platform_data->rdev[regulator_id]);
        }
    }
    /*release memory*/
    kfree(regulator_platform_data);
    return 0;
}

#ifdef CONFIG_PM
static int regulator_platform_suspend(struct platform_device *pdev, pm_message_t state)
{
    struct regulator_platform_data *regulator_platform_data;

    rdev_info(NULL, "regulator entry suspend successfully");

    regulator_platform_data = platform_get_drvdata(pdev);
    if (NULL == regulator_platform_data) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}
static int regulator_platform_resume(struct platform_device *pdev)
{
    int ret = 0;
    struct regulator_platform_data *regulator_platform_data;

    rdev_info(NULL, "regulator entry resume successfully");

    regulator_platform_data = platform_get_drvdata(pdev);
    if (NULL == regulator_platform_data) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return -1;
    }

    return ret;
}
#endif

static struct platform_driver regulator_platform_driver = {
    .probe = regulator_platform_probe,
    .remove = regulator_platform_remove,
#ifdef CONFIG_PM
    .suspend = regulator_platform_suspend,
    .resume = regulator_platform_resume,
#endif
    .driver = {
        .name   = "platform-regulator",
    },
};
static int __init regulator_platform_init(void)
{
    int ret = 0;

    ret = platform_driver_register(&regulator_platform_driver);
    printk("\n*******************regulator driver init(%d)**********************\n",ret);

    return ret;
}
static void __exit regulator_platform_exit(void)
{
    platform_driver_unregister(&regulator_platform_driver);
}
core_initcall(regulator_platform_init);
module_exit(regulator_platform_exit);
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


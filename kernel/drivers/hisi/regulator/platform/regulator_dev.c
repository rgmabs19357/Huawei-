/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : regulator_dev.c
  版 本 号   : 初稿
  作    者   : 王振伟 176398
  生成日期   : 2012年12月20日
  最近修改   :
  功能描述   : regulator设备注册
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月20日
    作    者   : 王振伟 176398
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/platform_device.h>
#include <mach/platform.h>
#include <linux/regulator/machine.h>
#include <hsad/config_mgr.h>
#include <regulator_map.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
struct regulator_init_data* platform_regulators = NULL;

#ifdef _DRV_LLT_
struct platform_device regulator_platform_device =
#else
static struct platform_device regulator_platform_device =
#endif
{
    .name =  "platform-regulator",
    .id = 0,
    .dev = {
        .platform_data = NULL,
    },
};

#if 0
/* please add all pmu related platform device in the struct.*/
static struct platform_device *regulator_platform_dev[] __initdata = {
    &regulator_platform_device
       /*add other pmu device here*/
};
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

unsigned int get_boardid(void);

int __init regulator_platform_dev_init(void)
{
    int ret = 0;
    unsigned int board_id = get_boardid();
    struct regulator_config_platform_table *table_item = NULL;

    table_item = &(platform_regulators_total[0]);
    while (REGULATOR_CONFIG_PLAT_TBL_END_SYMBOL != table_item->board_id) {
        if (board_id == table_item->board_id) {
            break;
        }
        table_item++;
    }
    if (REGULATOR_CONFIG_PLAT_TBL_END_SYMBOL == table_item->board_id){
        printk("Get regulator_type fail!, not match with %d.\n", table_item->board_id);
        return -EINVAL;
    }

    platform_regulators = table_item->table;
    regulator_platform_device.dev.platform_data = platform_regulators;

    ret = platform_device_register(&regulator_platform_device);
    //ret = platform_add_devices(regulator_platform_dev, ARRAY_SIZE(regulator_platform_dev));

    printk("\n*******************regulator device init(%d)**********************\n",ret);

    return ret;
};

arch_initcall(regulator_platform_dev_init);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


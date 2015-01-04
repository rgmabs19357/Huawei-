/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_driver.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic driver
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/printk.h>
#include <linux/irq.h>
#include <linux/irqdesc.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/bitops.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/clk.h>
#include <linux/irqnr.h>
#include <linux/err.h>

#include <hsad/config_mgr.h>

#include <mach/early-debug.h>
#include <mach/gpio.h>
#include <mach/irqs.h>

#include "soc_smart_interface.h"
#include "soc_ao_sctrl_interface.h"

#include "pmic_driver.h"
#include "pmic_common.h"
#include "pmic_driver_inner.h"
#include "regulator_pmic_info.h"
#include "pmic_ssi.h"
#include "pmic_reg.h"

PMU_DATA  pmu_desc;

#define PMU_LOCK()            spin_lock_irq(&pmu_desc.pmic_spinlock)
#define PMU_UNLOCK()          spin_unlock_irq(&pmu_desc.pmic_spinlock)

#if defined CONFIG_MACH_HI6620SFT
static int ops_hole_us = 200;
void pmu_set_ops_delay(int delay)  {ops_hole_us = delay;}
#define PMU_OP_DELAY()       udelay(ops_hole_us)
#else
#define PMU_OP_DELAY()       udelay(1)
#endif

int      g_PMIC_STATUS =   PMIC_STATUS_OFF;

/*****************************************************************************
 函 数 名  : pmic_get_channel_res_by_id
 功能描述  : 通过CHANNEL ID获取CHANNEL RES
 输入参数  :
             int id
 输出参数  : 无
 返 回 值  : COMMON_RES*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
COMMON_RES* pmic_get_channel_res_by_id(int id)
{
    PMU_RES_CTRL* pmu_res_ctrl = NULL;
    COMMON_RES *channel_res= NULL;
    int channel_num = 0;
    int i = 0;

	/*规避没有pmu 设备的情况*/
    if((NULL == pmu_desc.pdev)||(id >= PMU_CHANNEL_ID_BUTT) )
    {
        pr_err("%s %d pdev  %p,id %d \n",
        __func__, __LINE__,pmu_desc.pdev,id);
        goto FUN_ERR;
    }

    pmu_res_ctrl = pmu_desc.pdev->dev.platform_data;
    if(NULL == pmu_res_ctrl)
    {
        pr_err("%s %d pdev  %p,id %d pmu_res_ctrl %p \n",
        __func__, __LINE__,pmu_desc.pdev,id,pmu_res_ctrl);
        goto FUN_ERR;
    }

    channel_res= pmu_res_ctrl->res;
    if(NULL == channel_res)
    {
        pr_err("%s %d pdev  %p,id %d pmu_res_ctrl %p channel_res %p \n",
        __func__, __LINE__,pmu_desc.pdev,id,pmu_res_ctrl,channel_res);
        goto FUN_ERR;
    }


    channel_num = pmu_res_ctrl->res_num;


    for(i=0;i<channel_num;i++)
    {
        if(PMU_CHANNEL_ID_BUTT <= channel_res[i].id)
        {
/*
          pr_err("channel %d cannot access\n",channel_res[i].id);
 */
          goto NOT_SUPPORT;
        }

        if(id == channel_res[i].id)
        {
            return &channel_res[i];
        }
    }

FUN_ERR:
    return (COMMON_RES*)NULL;
NOT_SUPPORT:
    return (COMMON_RES*)PMU_CHANNEL_ID_BUTT;
}

int pmic_is_exist(void)
{
    return PMIC_STATUS_ON;
}

EXPORT_SYMBOL_GPL(pmic_is_exist);
/*+++++++++++++++++++API for regulater ++++++++++++++++-s*/

/*****************************************************************************
 函 数 名  : pmic_channel_status
 功能描述  : report batter channel switch state  to regulator
 输入参数  : int  channel_id
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月13日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int pmic_power_status(int channel_id)
{
    BSP_U32 reg_value=0;
    COMMON_SWITCH* cur_sw_config = NULL;
    COMMON_RES* channel_res = NULL;
    int ret = PMIC_MODULE_OK;

    if (PMU_CHANNEL_ID_BUTT <= channel_id)
    {
        pr_err("channel id err %d %s %d  \n", channel_id,__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    /*get device res*/
    channel_res = pmic_get_channel_res_by_id(channel_id);
    if (NULL == channel_res)
    {
        pr_err(" get channel_res  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }
    else if(PMU_CHANNEL_ID_BUTT == (int)channel_res)
    {
        return PMIC_MODULE_STATUS_ON;
    }

    cur_sw_config = &channel_res->power_switch;
    PMU_LOCK();

    ret = pmic_reg_read(&cur_sw_config->reg_cfg[CHANNEL_SWI_ONOFF_STATUS],&reg_value);
    if (PMIC_MODULE_OK != ret)
    {
        pr_err(" pmic_reg_read  err %s %d  \n",__func__, __LINE__);
        reg_value = PMIC_MODULE_ERROR;
    }

    PMU_UNLOCK();

    /*返回当前电源的开关状态*/
    return (BSP_S32)reg_value;

}

EXPORT_SYMBOL_GPL(pmic_power_status);

/*****************************************************************************
 函 数 名  : pmic_power_switch
 功能描述  : channel power on/off
 输入参数  : int id,int onoff
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int pmic_power_switch( int id,int onoff)
{
    COMMON_SWITCH*cur_sw_config = NULL;
    COMMON_RES* cur_channel_res = NULL;
    int onoff_flag = 0x01;
    int ret = PMIC_MODULE_OK;

    if (PMU_CHANNEL_ID_BUTT <= id)
    {
        pr_err("channel id err %d %s %d  \n", id,__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    /*get device res*/
    cur_channel_res = pmic_get_channel_res_by_id(id);
    if (NULL == cur_channel_res)
    {
        pr_err(" get channel_res  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }
    else if(PMU_CHANNEL_ID_BUTT == (int)cur_channel_res)
    {
        return PMIC_MODULE_OK;
    }

    if (onoff > CHANNEL_SWI_DISABLE)
    {
        pr_err(" onoff  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    cur_sw_config = &cur_channel_res->power_switch;
    PMU_LOCK();

    if((BOOST1_ID == id)&&(onoff == CHANNEL_SWI_DISABLE))
    {
        onoff_flag = 0x0;
    }

    ret = pmic_reg_write(&cur_sw_config->reg_cfg[onoff],onoff_flag);
    if(PMIC_MODULE_OK != ret)
    {
        pr_err(" pmic_reg_write  err %s %d  \n",__func__, __LINE__);
        PMU_UNLOCK();
        return PMIC_MODULE_ERROR;
    }

    if(CHANNEL_SWI_ENABLE == onoff)/*open channel need steady time */
    {
        if( (BUCK_ID_BEGIN <= id)&&(BUCK_ID_END >= id) )
        {
            udelay(480);
        }
        else if( (BOOST_ID_BEGIN <= id)&&(BOOST_ID_END >= id) )
        {
            udelay(480);
        }
        else if( (LDO_ID_BEGIN <= id)&&(LDO_ID_END >= id) )
        {
            udelay(240);
        }
        else if( (LVS_ID_BEGIN <= id)&&(LVS_ID_END >= id) )
        {
            udelay(180);
        }
        else{}

    }

    PMU_UNLOCK();

    return PMIC_MODULE_OK;
}

EXPORT_SYMBOL_GPL(pmic_power_switch);

/*****************************************************************************
 函 数 名  : pmic_list_vol_tab
 功能描述  : list voltage table
 输入参数  : int id ,unsigned int selector
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int pmic_list_vol_tab( int id ,unsigned int selector )
{
    COMMON_VALUE_SET *cur_voltage_list = NULL;
    unsigned int vol_table_size = 0;
    COMMON_RES* cur_channel_res = NULL;
#ifdef  PMIC_DEBUG
    int i = 0;
#endif
    if (PMU_CHANNEL_ID_BUTT <= id)
    {
        pr_err("channel id err %d %s %d  \n", id,__func__, __LINE__);
        return -1;
    }

    if ((id >= LVS_ID_BEGIN)&&(id <= LVS_ID_END))
    {
       /*LVS电路电压不可设返回默认值*/
        return 900000;
    }

    /*get device res*/
    cur_channel_res = pmic_get_channel_res_by_id(id);
    if (NULL == cur_channel_res)
    {
        pr_err(" get channel_res  err %s %d  \n",__func__, __LINE__);
        return -1;
    }
    else if(PMU_CHANNEL_ID_BUTT == (int)cur_channel_res)
    {
        /*电压软件不可设电路返回默认值*/
        return -6;/*PMIC Acore 不管理的电路返回给regulator -6*/
    }

    cur_voltage_list = &(cur_channel_res->value_set);
    vol_table_size = cur_voltage_list->value_range_num;

    if (selector >= vol_table_size)
    {
        pr_err(" selector err %s %d  \n",__func__, __LINE__);
        return -1;
    }

#ifdef  PMIC_DEBUG
    printk(" %s %d  vol_table_size %d\n",__func__, __LINE__,vol_table_size);
    for(i = 0;i<vol_table_size;i++)
    {
        printk(" %d",cur_voltage_list->value_range[i]);
    }
#endif

    return cur_voltage_list->value_range[selector];

}

EXPORT_SYMBOL_GPL(pmic_list_vol_tab);

/*****************************************************************************
 函 数 名  : pmic_get_voltage
 功能描述  : get pmic channel voltage
 输入参数  : int id
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月20日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int pmic_get_voltage(int id)
{
    BSP_U32 reg_value=0;
    int vol_id = 0;
    COMMON_VALUE_SET* cur_voltage = NULL;
    COMMON_RES* cur_channel_res = NULL;
    int ret = PMIC_MODULE_OK;

    if (PMU_CHANNEL_ID_BUTT <= id)
    {
        pr_err("channel id err %d %s %d  \n", id,__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    if ((id >= LVS_ID_BEGIN)&&(id <= LVS_ID_END))
    {
        printk(" LVS  %s %d  \n",__func__, __LINE__);
        return 900000;
    }

    /*get device res*/
    cur_channel_res = pmic_get_channel_res_by_id(id);
    if (NULL == cur_channel_res)
    {
        pr_err(" get channel_res  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }
    else if(PMU_CHANNEL_ID_BUTT == (int)cur_channel_res)
    {
        return -6;/*PMIC Acore 不管理的电路返回给regulator -6*/
    }

    cur_voltage = &(cur_channel_res->value_set);

    PMU_LOCK();
    ret = pmic_reg_read(&cur_voltage->reg_cfg,&vol_id);
    if (PMIC_MODULE_OK != ret)
    {
        pr_err(" pmic_reg_read  err %s %d  \n",__func__, __LINE__);
        reg_value = PMIC_MODULE_ERROR;
    }

    reg_value = cur_voltage->value_range[vol_id];

    PMU_UNLOCK();

    return reg_value;
}

EXPORT_SYMBOL_GPL(pmic_get_voltage);

/*****************************************************************************
 函 数 名  : pmic_set_voltage
 功能描述  :  set pmic channel voltage
 输入参数  : int id ,int min_uV, int max_uV, unsigned *selector
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月21日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int  pmic_set_voltage(int id ,int min_uV, int max_uV, unsigned *selector)
{
    int i = 0;
    COMMON_VALUE_SET *cur_voltage_list = NULL;
    COMMON_RES* cur_channel_res = NULL;
    int ret = PMIC_MODULE_OK;
    unsigned int vol = 0;
    unsigned int vol_num = 0;

    if (PMU_CHANNEL_ID_BUTT <= id)
    {
        pr_err("channel id err %d %s %d  \n", id,__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    if (NULL == selector)
    {
        pr_err(" selector NULL %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    if ((id >= LVS_ID_BEGIN)&&(id <= LVS_ID_END))
    {
        printk(" LVS  %s %d  \n",__func__, __LINE__);
        return 0;
    }

    /*get device res*/
    cur_channel_res = pmic_get_channel_res_by_id(id);
    if (NULL == cur_channel_res)
    {
        pr_err(" get channel_res  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }
    else if(PMU_CHANNEL_ID_BUTT == (int)cur_channel_res)
    {
        return 0;
    }

    cur_voltage_list = &(cur_channel_res->value_set);
    if (NULL == cur_voltage_list)
    {
        pr_err(" get cur_voltage_list  err %s %d  \n",__func__, __LINE__);
        return PMIC_MODULE_ERROR;
    }

    vol_num = cur_voltage_list->value_range_num;

    PMU_LOCK();
    for(i = 0;i<vol_num;i++)
    {
        vol = cur_voltage_list->value_range[i];

        if((vol >= min_uV)&&(vol <= max_uV))
        {
            /*set voltage*/
            ret = pmic_reg_write(&cur_voltage_list->reg_cfg,i);
            if(PMIC_MODULE_OK != ret)
            {
                pr_err(" pmic_reg_write  err %s %d  \n",__func__, __LINE__);
                goto FUN_ERR;
            }

            *selector = i;
            PMU_UNLOCK();
            return PMIC_MODULE_OK;
        }
    }

FUN_ERR:
    PMU_UNLOCK();
    return PMIC_MODULE_ERROR;
}

EXPORT_SYMBOL_GPL(pmic_set_voltage);

/*+++++++++++++++++++API for regulater ++++++++++++++++-e*/

/*****************************************************************************
 函 数 名  : pmic_default_value_set
 功能描述  : pmic default value set
 输出参数  : 无
 返 回 值  : BSP_S32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 pmic_default_value_set(struct platform_device *pdev)
{
    PMU_RES_CTRL* pmu_res_ctrl = NULL;

    if(NULL == pdev)
    {
        pr_err("%s %d pmu's pdev is NULL\n", __func__, __LINE__);
        return BSP_ERROR;
    }

    pmu_res_ctrl = pdev->dev.platform_data;
    if(NULL == pmu_res_ctrl)
    {
        pr_err("%s %d pmu no platform data\n", __func__, __LINE__);
        return BSP_ERROR;
    }

    /*默认上电的电源电压设置和上电*/
    /*设置LD024电压为3.15V,该电压与AUXADC、CODEC共用*/
    (void)BSP_PMU_RegSet(SOC_SMART_LDO24_REG_ADJ_ADDR(0),PMU_LDO24_3_15V);
    /*打开LDO24*/
    (void)BSP_PMU_RegSet(SOC_SMART_ENABLE4_ADDR(0),PMU_LDO24_OPEN);
    /*配置PMU AUXDAC_EN 由内部寄存器控制*/
    (void)BSP_PMU_RegSet(SOC_SMART_DAC_CTRL_ADDR(0),PMU_AUXADC_EN);


    /*部分电源的eco等属性配置，待PMU回片调试*/

    /*返回*/

    return BSP_OK;
}

unsigned int ldo_dont_ocp_mask = 0;

/*****************************************************************************
 函 数 名  : init_ldo_bit_mask
 功能描述  : 初始化ldo特殊处理的标志，ldo1对应1<<0，ldo24对应1<<23
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月4日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
void init_ldo_ocp_mask(void)
{
    if (!get_hw_config_int("power/ldo_ocp_bit_mask", &ldo_dont_ocp_mask, NULL) ) {
        ldo_dont_ocp_mask = 0;
        pr_err("get ldo_ocp_bit_mask failed\n");
    }

    printk("ldo_dont_ocp_mask = %d\n", ldo_dont_ocp_mask);
}

/*****************************************************************************
 函 数 名  : pmic_probe
 功能描述  : pmic probe
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
static int __init pmic_probe(struct platform_device *pdev)
{
    BSP_S32 ret = 0;
    /*后续过保护项目:上电初始化流程需要读取 中断寄存器，状态寄存器，非下电寄存器
      判断 上次下电原因、本次开机原因   本次不做开发*/

    memset((void*)&pmu_desc,0,sizeof(pmu_desc));
    pmu_desc.pdev = pdev;
    spin_lock_init(&pmu_desc.pmic_spinlock);
    /*default_set*/
    ret = pmic_default_value_set(pdev);
    if (BSP_OK != ret)
    {
       pr_err("%d pmic_default_value_set\n", __LINE__);
       return -EINVAL;
    }

    init_ldo_ocp_mask();

    printk("pmic_probe attach OK\n");

    return 0;
}

/*****************************************************************************
 函 数 名  : pmic_remove
 功能描述  : pmic remove
 输入参数  : struct platform_device *pdev
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
int pmic_remove(struct platform_device *pdev)
{
    *(volatile int *)SOC_AO_SCTRL_SC_PERIPH_RSTEN4_ADDR(SOC_SC_ON_BASE_ADDR) = \
    (1<<SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_1pmussi_START);

    return 0;
}

static struct platform_driver pmic_driver = {
    .probe = pmic_probe,
    .remove = pmic_remove,
    .driver     = {
        .name   = "smartStar",
    },
};

static char banner[] __initdata =
    KERN_INFO "PMIC driver, (c) 2013 Hisilicon Electronics\n";

/*****************************************************************************
 函 数 名  : pmic_init
 功能描述  : pmic init
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
static int __init pmic_init(void)
{
    int ret = 0;
    printk(banner);
    ret = platform_driver_register(&pmic_driver);
    if (ret != 0)
    {
        pr_err("Failed to register  driver: %d %s %d  \n",ret,__func__, __LINE__);
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : pmic_exit
 功能描述  : pmic exit
 输入参数  : void
 输出参数  : 无
 返 回 值  : static void __exit
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月9日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
static void __exit pmic_exit(void)
{
    platform_driver_unregister(&pmic_driver);
}

core_initcall(pmic_init);
module_exit(pmic_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");
MODULE_DESCRIPTION(" Hisilicon PMIC driver");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


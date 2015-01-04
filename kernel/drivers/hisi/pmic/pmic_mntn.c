/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_mntn.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic mntn
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

#include "pmic_mntn_inner.h"

PMUIRQ_DATA* pmic_get_pmuirq_desc(void)
{
    return &pmuirq_desc;
}

/*****************************************************************************
 函 数 名  : pmic_mntn_init
 功能描述  : pmu mntn init
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int  pmic_mntn_init(void)
{
    PMIC_MNTN_POWER_ON_OPS* cur_mntn_ops = NULL;
    PMUIRQ_DATA* pmuirq_desc = pmic_get_pmuirq_desc();
    PMIC_MNTN_DESC* cur_mntn_desc = NULL;
    int ret = 0;

    pmic_mntn_dev_register();
    cur_mntn_desc = pmuirq_desc->mntn_desc;
    cur_mntn_ops = pmuirq_desc->mntn_desc->mntn_ops;


    if(NULL != cur_mntn_ops->no_pwr_read)
    {
        cur_mntn_ops->no_pwr_read();
    }

    if(NULL != cur_mntn_ops->no_pwr_clear)
    {
        cur_mntn_ops->no_pwr_clear();
    }

    if(NULL != cur_mntn_ops->irq_read)
    {
        cur_mntn_ops->irq_read();
    }

    if(NULL != cur_mntn_ops->irq_clear)
    {
        cur_mntn_ops->irq_clear();
    }

    if(NULL != cur_mntn_ops->record_read)
    {
        cur_mntn_ops->record_read();
    }

    if(NULL != cur_mntn_ops->record_clear)
    {
        cur_mntn_ops->record_clear();
    }

    if(NULL != cur_mntn_ops->mntn_power_on_info)
    {
        cur_mntn_ops->mntn_power_on_info();
    }

    if(NULL != cur_mntn_desc->power_off_notifier)
    {
        register_reboot_notifier(cur_mntn_desc->power_off_notifier);
    }

    if(NULL == cur_mntn_desc->mntn_init_wk_ops)
    {
        pr_err("%s mntn_init_wk_ops NULL\n",__func__);
        return -1;
    }

    cur_mntn_desc->mntn_init_wq = create_singlethread_workqueue("pmu mntn init");
    if (NULL == cur_mntn_desc->mntn_init_wq)
    {
        pr_err("%s create_workqueue failed\n",__func__);
        return -1;
    }

    ret = pmu_version_check();
    pmussi_device_state_notify(SSI_DEVICE_PMU, ret);
    ret = pmu_32kclk_check();
    pmussi_device_state_notify(SSI_DEVICE_32K, ret);

    INIT_DELAYED_WORK(&cur_mntn_desc->mntn_init_wk, cur_mntn_desc->mntn_init_wk_ops);
    queue_delayed_work(cur_mntn_desc->mntn_init_wq, &cur_mntn_desc->mntn_init_wk,120*HZ);

    return 0;
}


int  pmic_mntn_uninit(void)
{
    PMUIRQ_DATA* pmuirq_desc = pmic_get_pmuirq_desc();
    PMIC_MNTN_DESC* cur_mntn_desc = pmuirq_desc->mntn_desc;
    if(NULL != cur_mntn_desc->power_off_notifier)
    {
        unregister_reboot_notifier(cur_mntn_desc->power_off_notifier);
    }

    return 0;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


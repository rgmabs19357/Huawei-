/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *
*****************************************************************************
  文 件 名   : pmic_reg.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic register driver
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
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/module.h>

#include "pmic_common.h"
#include "pmic_reg.h"
#include "pmic_ssi.h"
#include "pmic_driver.h"
#include "pmicirq_driver.h"


extern PMUIRQ_DATA pmuirq_desc;

extern BSP_S32 BSP_PMU_RegGet( BSP_U32 regAddr, BSP_U32 * getData );

/*****************************************************************************
 函 数 名  : pmic_reg_read
 功能描述  : pmic  register read
 输入参数  : COMMON_REG_CFG* reg_cfg
             BSP_U32 *value
 输出参数  : 无
 返 回 值  : BSP_S32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 pmic_reg_read(COMMON_REG_CFG* reg_cfg, BSP_U32 *value)
{
    BSP_S32 ret=BSP_ERROR;
    BSP_U32 reg_value=0;
    /*非法入参判断*/
    if ((NULL == reg_cfg)||(NULL == value))
    {
       pr_err("PRARM NULL %s %d  \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*将该baseaddr和value作为入参调用ssi读接口执行读寄存器操作*/
    ret=BSP_PMU_RegGet(reg_cfg->baseaddr,&reg_value);
    if (BSP_OK != ret)
    {
       pr_err("BSP_PMU_RegGet err %s %d  \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    *value = BSP_REG_GETBITS(&reg_value,0,reg_cfg->bits_offset,reg_cfg->bits_num);

    /*返回*/
    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : pmic_reg_write
 功能描述  : pmic register  write
 输入参数  : COMMON_REG_CFG* reg_cfg
             BSP_U32 value
 输出参数  : 无
 返 回 值  : BSP_S32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 pmic_reg_write(COMMON_REG_CFG* reg_cfg, BSP_U32 value)
{
    BSP_S32 ret=BSP_ERROR;
    BSP_U32 reg_value=0;

    /*非法入参判断*/
    if (NULL == reg_cfg)
    {
       pr_err("PRARM NULL %s %d  \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*获得寄存器值*/
    ret=BSP_PMU_RegGet(reg_cfg->baseaddr,&reg_value);
    if (BSP_OK != ret)
    {
       pr_err("BSP_PMU_RegGet err %s %d  \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*组合新的寄存器值*/
    BSP_REG_SETBITS(&reg_value,0,reg_cfg->bits_offset,reg_cfg->bits_num,value);
    /*将该baseaddr和value作为入参调用ssi写接口执行写寄存器操作*/
    ret=BSP_PMU_RegSet(reg_cfg->baseaddr,reg_value);
    if (BSP_OK != ret)
    {
       pr_err("BSP_PMU_RegSet err %s %d  \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*返回*/
    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : pmu_status_reg_read
 功能描述  : 中断寄存器状态保存
 输入参数  : PMUIRQ_RES_CTRL* pmu_res_ctrl
             BSP_U32 reg_type_id(中断寄存器，状态寄存器...)
 输出参数  : 无
 返 回 值  : BSP_S32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月29日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 pmu_status_reg_read(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id)
{
    BSP_S32 ret=BSP_ERROR;
    BSP_U32 reg_id=0;
    BSP_U32 reg_size=0;
    BSP_U32*reg_addr=(BSP_U32*)NULL;
    BSP_U32*stat_reg_buf=(BSP_U32*)NULL;
    PMUIRQ_STAT* cur_stat = (PMUIRQ_STAT*)NULL;

    /*非法入参判断*/
    if (NULL == pmu_res_ctrl)
    {
       pr_err("%s %d  pmu_res_ctrl null\n",__func__, __LINE__);
       return BSP_ERROR;
    }

    cur_stat = pmic_get_pmustat();

    /*根据reg_type_id获得操作对象stat_reg[reg_type_id]*/
    /*通过ID获取中断状态寄存器地址*/
    reg_addr = pmu_res_ctrl->stat_reg[reg_type_id];
    /*寄存器个数*/
    reg_size = pmu_res_ctrl->stat_reg_size[reg_type_id];

    stat_reg_buf = cur_stat->stat_reg_buf[reg_type_id];
    memset((void*)stat_reg_buf,0,reg_size);

    /*循环调用ssi读接口读操作对象所有寄存器*/
    /*并且将信息保存在dev->stat的stat_reg_buf[reg_type_id]中*/
    for(reg_id = 0;reg_id < reg_size; ++reg_id)
    {
        ret=BSP_PMU_RegGet(reg_addr[reg_id],&(stat_reg_buf[reg_id]));
#ifdef PMIC_DEBUG
        printk("pmu register addr 0x%0x  data 0x0%0x\n",reg_id,stat_reg_buf[reg_id]);
#endif
    }

    /*返回*/
    return ret;

}

BSP_S32 pmic_status_reg_read(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id,BSP_U32* data_buf)
{
    BSP_S32 ret=BSP_ERROR;
    BSP_U32 reg_id=0;
    BSP_U32 reg_size=0;
    BSP_U32*reg_addr=(BSP_U32*)NULL;
    BSP_U32 stat_reg_buf[PMIC_BUF_MAX_SIZE] = {0};

    /*非法入参判断*/
    if (NULL == pmu_res_ctrl)
    {
       pr_err("%s %d  pmu_res_ctrl null\n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*根据reg_type_id获得操作对象stat_reg[reg_type_id]*/
    /*通过ID获取中断状态寄存器地址*/
    reg_addr = pmu_res_ctrl->stat_reg[reg_type_id];
    /*寄存器个数*/
    reg_size = pmu_res_ctrl->stat_reg_size[reg_type_id];

    memset((void*)stat_reg_buf,0,reg_size);

    /*循环调用ssi读接口读操作对象所有寄存器*/
    /*并且将信息保存在dev->stat的stat_reg_buf[reg_type_id]中*/
    for(reg_id = 0;reg_id < reg_size; ++reg_id)
    {
        ret=BSP_PMU_RegGet(reg_addr[reg_id],&(stat_reg_buf[reg_id]));
        printk("pmu register addr 0x%0x  data 0x0%0x\n",reg_id,stat_reg_buf[reg_id]);
    }

    memcpy((void*)data_buf,stat_reg_buf,reg_size*sizeof(unsigned int));

    /*返回*/
    return ret;

}

/*****************************************************************************
 函 数 名  : pmu_status_reg_clear
 功能描述  : pmu status register clear
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 pmu_status_reg_clear(PMUIRQ_RES_CTRL* pmu_res_ctrl,BSP_U32 reg_type_id)
{
    BSP_S32 ret=BSP_ERROR;
    BSP_U32 reg_id=0;
    BSP_U32 reg_size=0;
    BSP_U32*reg_addr=(BSP_U32*)NULL;

    /*非法入参判断*/
    if(PMU_STATUS_REG_TYPE_ID_IS_INVALID(reg_type_id))
    {
       pr_err("%s %d reg_type_id \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    if(NULL == pmu_res_ctrl)
    {
       pr_err("%s %d pmu_res_ctrl null \n",__func__, __LINE__);
       return BSP_ERROR;
    }

    /*根据reg_type_id获得操作对象stat_reg[reg_type_id]*/
    reg_addr = pmu_res_ctrl->stat_reg[reg_type_id];
    /*寄存器个数*/
    reg_size = pmu_res_ctrl->stat_reg_size[reg_type_id];
    /*循环调用ssi写接口清除操作对象所有寄存器*/
    for(reg_id=0;reg_id<reg_size;++reg_id)
    {
        ret=BSP_PMU_RegSet(reg_addr[reg_id],(BSP_U32)PMU_IRQ_VALUE_CLEAR);/*W1C*/
    }

    /*返回*/
    return ret;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

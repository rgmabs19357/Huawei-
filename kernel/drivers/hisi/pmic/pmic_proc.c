/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_proc.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic proc file
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

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/percpu.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include "pmic_driver.h"
#include "pmic_common.h"
#include "pmicirq_driver.h"


extern  PMUIRQ_DATA pmuirq_desc;

static int  proc_show(struct seq_file *s, void *p)
{
   int i = 0;
   COMMON_VALUE_SET *cur_voltage_list = NULL;
   unsigned int vol_table_size = 0;
   COMMON_RES* cur_channel_res = NULL;

#if 0
    /*PMIC IRQ info*/
    for (i =PMIC_REG_IRQ1;i<PMIC_IRQ_REG_BUTT;i++)
    {
        seq_printf(s, "IRQ STATUS:%d; %0x\n",i,pmuirq_desc.irq_stat_reg_buf[i]);
    }
#endif
    seq_printf(s, "STATUS 0:OFF 1:ON\n");

    /*pmic register power channel info*/
    for(i = BUCK_ID_BEGIN ;i<PMU_CHANNEL_ID_BUTT;i++)
    {
        if(0 == pmic_power_status(i))
        {
              seq_printf(s, "Channel ID:%d  STATUS OFF  VOL %d\n",i, pmic_get_voltage(i));
        }
        else if(1 == pmic_power_status(i))
        {
            seq_printf(s, "Channel ID:%d  STATUS ON  VOL %d\n",i, pmic_get_voltage(i));
        }
         
         udelay(1);
    }

    /*channel voltage list show*/
    for(i = BUCK_ID_BEGIN ;i<LVS_ID_BEGIN;i++)
    {
         int j = 0;

         /*get device res*/
        cur_channel_res = pmic_get_channel_res_by_id(i);
        if (NULL == cur_channel_res)
        {
            continue;
        }
        else if(PMU_CHANNEL_ID_BUTT == (int)cur_channel_res)
        {
            continue;
        }

        cur_voltage_list = &(cur_channel_res->value_set);
        vol_table_size = cur_voltage_list->value_range_num;

        if(0 == vol_table_size)
        {
            continue;
        }

        seq_printf(s, "Channel ID:%d VOL_LIST:\n",i);
        
        for(j= 0;j<vol_table_size;j++)
        {
             seq_printf(s, "%d  ",cur_voltage_list->value_range[j]);
        }

        seq_printf(s, "\n ");
    }
   
   return 0;
}

static int pmic_seq_open(struct inode *inode, struct file *file)
{
    return single_open(file,proc_show, NULL);
}

static struct file_operations pmic_seq_fops = {
        .open = pmic_seq_open,
        .read = seq_read,
        .llseek = seq_lseek,
        .release = single_release,
};

static int __init pmic_seq_init(void)
{
    static struct proc_dir_entry *entry = NULL;
    entry = create_proc_entry("pmicinfo", 0, NULL);
    if (entry)
    {
       entry->proc_fops = &pmic_seq_fops;
    }

    return 0;
}

static void __exit pmic_seq_exit(void)
{
    remove_proc_entry("pmicinfo", NULL);
}

module_init(pmic_seq_init);
module_exit(pmic_seq_exit);
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


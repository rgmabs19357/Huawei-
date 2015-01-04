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

#include "pmic_mntn_dev_inner.h"
#include "BSP.h"

PMU_MNTN_LOG pmu_onoff_event[] =
{
  {
    {SOC_SMART_NP_IRQ1_RECORD_ADDR(0),SOC_SMART_NP_IRQ1_RECORD_np_hreset_n_f_START,
    (SOC_SMART_NP_IRQ1_RECORD_np_hreset_n_f_END-SOC_SMART_NP_IRQ1_RECORD_np_hreset_n_f_START+1)},
    PMIC_NOMAL_PD,
    "hot-reset"/*按键复位*/
  },

  {
    {SOC_SMART_NP_IRQ1_RECORD_ADDR(0),SOC_SMART_NP_IRQ1_RECORD_np_otmp_d1r_START,
    (SOC_SMART_NP_IRQ1_RECORD_np_otmp_d1r_END-SOC_SMART_NP_IRQ1_RECORD_np_otmp_d1r_START+1)},
    PMIC_NOMAL_PD,
    "over-temperature"/*过温记录【NV】*/
  },

  {
    {SOC_SMART_NP_IRQ1_RECORD_ADDR(0),SOC_SMART_NP_IRQ1_RECORD_np_vsys_2p5_f_START,
    (SOC_SMART_NP_IRQ1_RECORD_np_vsys_2p5_f_END-SOC_SMART_NP_IRQ1_RECORD_np_vsys_2p5_f_START+1)},
    PMIC_NOMAL_PD,
    "low voltage or battery out"/*电压欠压 or 电池拔出*/
  },

  {
    {SOC_SMART_NP_IRQ1_RECORD_ADDR(0),SOC_SMART_NP_IRQ1_RECORD_np_vsys_6p0_d200ur_START,
    (SOC_SMART_NP_IRQ1_RECORD_np_vsys_6p0_d200ur_END-SOC_SMART_NP_IRQ1_RECORD_np_vsys_6p0_d200ur_START+1)},
    PMIC_NOMAL_PD,
    "over voltage"/*过压*/
  },

  {
    {SOC_SMART_NP_IRQ2_RECORD_ADDR(0),SOC_SMART_NP_IRQ2_RECORD_np_pwron_dnsr_START,
    (SOC_SMART_NP_IRQ2_RECORD_np_pwron_dnsr_END-SOC_SMART_NP_IRQ2_RECORD_np_pwron_dnsr_START+1)},
    PMIC_EXC_PD,
    "long key-press"/*长按键关机*/
  },

  {
    {SOC_SMART_NP_IRQ2_RECORD_ADDR(0),SOC_SMART_NP_IRQ2_RECORD_np_otmp150_d1r_START,
    (SOC_SMART_NP_IRQ2_RECORD_np_otmp150_d1r_END-SOC_SMART_NP_IRQ2_RECORD_np_otmp150_d1r_START+1)},
    PMIC_EXC_PD,
    "over-temperature-150"/*过温复位*/
  }
};

PMU_CPU_HANDLER ccpu_handler[] =
{
    {SOC_SMART_OCP_RECORD3_ADDR(0),SOC_SMART_OCP_RECORD3_ocp_ldo9_START},
    {SOC_SMART_OCP_RECORD3_ADDR(0),SOC_SMART_OCP_RECORD3_ocp_ldo11_START},
    {SOC_SMART_OCP_RECORD5_ADDR(0),SOC_SMART_OCP_RECORD5_ocp_lvs5_START},
};

/*IRQ寄存器 缓存单元*/
BSP_U32 irq_stat_reg_buf[PMIC_IRQ_REG_BUTT]={0};
/*status 状态寄存器 缓存单元*/
BSP_U32 status_stat_reg_buf[PMIC_STATUS_REG_BUTT]={0};

BSP_U32 record_stat_reg_buf[PMIC_RECORD_REG_BUTT]={0};
/*非下电寄存器 缓存单元*/
BSP_U32 no_power_stat_reg_buf[PMIC_NO_PWR_REG_BUTT]={0};

BSP_U32 irq_mask_reg_buf[PMIC_IRQ_REG_MASK_BUTT]={0};

BSP_U32 smart_mask_vote[IRQ_PMU_NR_END-IRQ_PMU_NR_BASE]= {0};
BSP_U32 smart_unmask_vote[IRQ_PMU_NR_END-IRQ_PMU_NR_BASE]= {0};

char print_string_buf[PRINT_MAX_LEN] ={'\0'};

#ifndef    _DRV_LLT_
IFC_GEN_CALL1(
                    MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT,
                    pmu_ccore_irqevent_handler,
                    IFC_INFIX, struct _PMU_CPU_HANDLER_*  , pMsgBody, sizeof(struct _PMU_CPU_HANDLER_))
#endif

unsigned int pmic_is_ccpu_handler(unsigned int reg_id,unsigned char reg_bit)
{
    unsigned int scan_size = sizeof(ccpu_handler)/sizeof(ccpu_handler[0]);
    unsigned int scan_id = 0;
    for(scan_id = 0;scan_id < scan_size;scan_id++)
    {
        if((reg_id == ccpu_handler[scan_id].reg_id)&&(reg_bit == ccpu_handler[scan_id].bit_id))
        {
            return IS_CCPU_EVENT;
        }
    }

    return NOT_CCPU_EVENT;
}

/*****************************************************************************
 函 数 名  : pmic_get_pmuctrl
 功能描述  : pmic get  pmuctrl
 输入参数  : void
 输出参数  : 无
 返 回 值  : PMUIRQ_RES_CTRL*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月12日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
PMUIRQ_RES_CTRL*  pmic_get_pmuctrl(void)
{
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    PMUIRQ_DATA * pmu_irq_data = &pmuirq_desc;
    pmu_res_ctrl = pmu_irq_data->pdev->dev.platform_data;
    return pmu_res_ctrl;
}

void pmic_poweroff_scan(BSP_U32 reg_base ,BSP_U32 reg_bit)
{
    PMUIRQ_STAT* pmu_res_stat = NULL;
    BSP_U32 scan_max = sizeof(pmu_onoff_event)/sizeof(PMU_MNTN_LOG);
    BSP_U32 scan_id = 0;

    pmu_res_stat = pmic_get_pmustat();

    for(scan_id = 0;scan_id < scan_max;scan_id++)
    {
        if((reg_base == pmu_onoff_event[scan_id].exc_addr.baseaddr)&&\
           (reg_bit == pmu_onoff_event[scan_id].exc_addr.bits_offset))
        {
            pr_err("PMU INFO  %s\n",pmu_onoff_event[scan_id].mntn_log);
            if(PMIC_EXC_PD == pmu_onoff_event[scan_id].is_exc_pd)
            {
                pmu_res_stat->is_exc_pd = PMIC_EXC_PD;
                snprintf(print_string_buf,PRINT_MAX_LEN,"reason %s\n",pmu_onoff_event[scan_id].mntn_log);
            }
        }
    }
}

/*****************************************************************************
 函 数 名  : pmic_poweroff_reason
 功能描述  :  pmic poweroff reason
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void pmic_poweroff_reason(void)
{
 /*过流 过压 欠压 过热 导致的关机 在history.log 做一行打印记录
表明上次关机为异常关机
其他正常类型关机不在history.log记录，但可以在pmu_log查找非下电寄存器获取;
开机原因不在history.log记录,但可以在pmu_log查找非下电寄存器获取
*/
  PMUIRQ_STAT* pmu_res_stat = NULL;
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  BSP_U32* stat_no_pwr_reg_buf = (BSP_U32*)NULL;
  BSP_U32 reg_id = 0;
  BSP_U32* no_pwr_base_reg_addr = (BSP_U32*)NULL;
  BSP_U32 data_width = 0;

  pmu_res_ctrl = pmic_get_pmuctrl();
  pmu_res_stat = pmic_get_pmustat();
  data_width = pmu_res_ctrl->data_width;
  stat_no_pwr_reg_buf = pmu_res_stat->stat_reg_buf[PMIC_NOPWR_REG_TYPE_ID];
  no_pwr_base_reg_addr = pmu_res_ctrl->stat_reg[PMIC_NOPWR_REG_TYPE_ID];

  for (reg_id = 0; reg_id < PMIC_NO_PWR_REG_BUTT; reg_id++)
  {
    if(0 != stat_no_pwr_reg_buf[reg_id])
    {
        if(PMIC_SCP_RECORD_NO_PWR_REG == reg_id)
        {
            pmu_res_stat->is_exc_pd = PMIC_EXC_PD;
            pr_err("PMU SCP:BUCK0~6 addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],stat_no_pwr_reg_buf[reg_id]);
            snprintf(print_string_buf,PRINT_MAX_LEN,"reason SCP:BUCK0~6 addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],stat_no_pwr_reg_buf[reg_id]);
        }
        else if(PMIC_OCP_RECORD3_NO_PWR_REG == reg_id)
        {
            unsigned char reg_data = (unsigned char)stat_no_pwr_reg_buf[reg_id];
            reg_data &= ~(BIT(SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo9_START)|\
                          BIT(SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo10_START)|\
                      BIT(SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo11_START));

            pr_err("PMU OCP:addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],stat_no_pwr_reg_buf[reg_id]);

            if(reg_data)
            {
                pmu_res_stat->is_exc_pd = PMIC_EXC_PD;
                snprintf(print_string_buf,PRINT_MAX_LEN,"reason OCP:addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],reg_data);
            }
        }
        else if((PMIC_OCP_RECORD1_NO_PWR_REG <= reg_id)&&(PMIC_OCP_RECORD7_NO_PWR_REG >= reg_id))
        {
            pmu_res_stat->is_exc_pd = PMIC_EXC_PD;
            pr_err("PMU OCP:addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],stat_no_pwr_reg_buf[reg_id]);
            snprintf(print_string_buf,PRINT_MAX_LEN,"reason OCP:addr 0x%x data 0x%x\n",no_pwr_base_reg_addr[reg_id],stat_no_pwr_reg_buf[reg_id]);
        }
        else
        {
            char bit = 0;
            for (bit = 0; bit < data_width; bit++)
            {
                char reg_bit = 0x01 << bit;
                if ((stat_no_pwr_reg_buf[reg_id] & reg_bit))
                {
                    pmic_poweroff_scan(no_pwr_base_reg_addr[reg_id],bit);
                }
            }
        }
    }
  }

}

void pmic_poweron_show(void)
{
  BSP_U32 reg_type = 0;
  PMUIRQ_STAT* pmu_res_stat = NULL;
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  BSP_U32* reg_base_addr = (BSP_U32*)NULL;
  BSP_U32 reg_num = 0;
  BSP_U32* stat_buf_addr = (BSP_U32*)NULL;

  pmu_res_ctrl = pmic_get_pmuctrl();
  pmu_res_stat = pmic_get_pmustat();

  for(reg_type = PMIC_IRQ_REG_TYPE_ID ;reg_type<= PMIC_NOPWR_REG_TYPE_ID;reg_type++)
  {
      BSP_U32 reg_id = 0;
      reg_base_addr = pmu_res_ctrl->stat_reg[reg_type];
      reg_num = pmu_res_ctrl->stat_reg_size[reg_type];
      stat_buf_addr = pmu_res_stat->stat_reg_buf[reg_type];

      for(reg_id = 0;reg_id < reg_num ;reg_id++)
      {
        pr_err("addr 0x%x  data 0x%x\n",reg_base_addr[reg_id],stat_buf_addr[reg_id]);
      }

      pr_err("\n");

  }

}

void smart_no_pwr_reg_read(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_read(pmu_res_ctrl,PMIC_NOPWR_REG_TYPE_ID);
}

void smart_no_pwr_reg_clear(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_clear(pmu_res_ctrl,PMIC_NOPWR_REG_TYPE_ID);
}

void smart_irq_reg_read(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_read(pmu_res_ctrl,PMIC_IRQ_REG_TYPE_ID);
}

void smart_irq_reg_clear(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_clear(pmu_res_ctrl,PMIC_IRQ_REG_TYPE_ID);
}

void smart_record_reg_read(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_read(pmu_res_ctrl,PMIC_RECORD_REG_TYPE_ID);
}

void smart_record_reg_clear(void)
{
  PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
  pmu_res_ctrl = pmic_get_pmuctrl();
  (void)pmu_status_reg_clear(pmu_res_ctrl,PMIC_RECORD_REG_TYPE_ID);
}

void smart_poweron_info(void)
{
    pr_err("\n\nPMU POWER ON MNTN SHOW \n");
    pmic_poweron_show();
    pmic_poweroff_reason();
}

void smart_otmp_hander(struct work_struct *work)
{
    pr_err("PMU OTMP EVENT happen\n");
}

PMIC_MNTN_POWER_ON_OPS smart_mntn_power_on_ops =
{
    .no_pwr_read = smart_no_pwr_reg_read,
    .no_pwr_clear = smart_no_pwr_reg_clear,
    .irq_read = smart_irq_reg_read,
    .irq_clear = smart_irq_reg_clear,
    .record_read = smart_record_reg_read,
    .record_clear = smart_record_reg_clear,
    .mntn_power_on_info = smart_poweron_info,
};

struct notifier_block smart_power_off_notifier = {
.notifier_call = smart_power_off,
};


PMIC_MNTN_DESC smart_mntn_ops =
{
   .mntn_ops = &smart_mntn_power_on_ops,
   .power_off_notifier = &smart_power_off_notifier,
   .ocp_scp_wk_ops = smart_ocp_scp_wq_hander,
   .mntn_init_wk_ops = smart_mntn_init,
   .otmp_wk_ops = smart_otmp_hander,
   .stat ={
              {irq_stat_reg_buf,status_stat_reg_buf,record_stat_reg_buf,no_power_stat_reg_buf,irq_mask_reg_buf},
               smart_mask_vote,
               smart_unmask_vote,
               PMIC_NOMAL_PD,
          }

};

void smart_mntn_init(struct work_struct *work)
{
    int ret = 0;
    NV_HW_CONFIG_STRU drv_55nv;
    volatile unsigned char otmp = 0;
    PMIC_MNTN_DESC * mntn_desc = &smart_mntn_ops;

    if(PMIC_EXC_PD == mntn_desc->stat.is_exc_pd)
    {
      pr_err("%s save pmu_reboot \n",__func__);
      mach_call_usermodeshell(PMU_SHELL_SCRIPT,1,print_string_buf);
    }

    ret = DR_NV_Read(en_NV_Item_HW_CONFIG, &drv_55nv, sizeof(NV_HW_CONFIG_STRU));
    if (ret != NV_OK)
    {
        pr_err("%s: en_NV_Item_HW_CONFIG use default data\n", __func__);
    }

    otmp = pmussi_reg_read(SOC_SMART_BANDGAP_THSD_ADJ2_ADDR(0));
    otmp &= ~(0x03<<SOC_SMART_BANDGAP_THSD_ADJ2_thsd_set_tmp_START);
    otmp |= drv_55nv.PMU_PROTECT.OTMP_TMP<<SOC_SMART_BANDGAP_THSD_ADJ2_thsd_set_tmp_START;
    pmussi_reg_write(SOC_SMART_BANDGAP_THSD_ADJ2_ADDR(0),otmp);

}

/*****************************************************************************
 函 数 名  : smart_ocp_scp_finally_work
 功能描述  : smart ocp scp finally work
 输入参数  : PMU_CPU_HANDLER *pMsgBody
             PMIC_MNTN_DESC * mntn_desc
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void  smart_ocp_scp_finally_work(PMIC_MNTN_DESC * mntn_desc)
{
    if(NULL == mntn_desc->mntn_ops->record_clear)
    {
        pr_err("%s %d record_clear return NULL\n", __func__, __LINE__);
        return  ;
    }

    mntn_desc->mntn_ops->record_clear();

    pmu_irq_unmask(OCP_SCP_R_TYPE);

    return ;
}

/*****************************************************************************
 函 数 名  : smart_dont_ocp_mask
 功能描述  : 把特殊处理的电源bit位置1
 输入参数  : reg_addr
 输出参数  : 无
 返 回 值  : bit mask
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月4日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned char  smart_dont_ocp_mask(BSP_U32 reg_addr)
{
    extern unsigned int ldo_dont_ocp_mask;

    static struct{
        BSP_U32 reg_addr;
        unsigned char bit;
    }ldo_ocp_tbl[24] = {
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo1_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo2_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo3_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo4_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo5_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo6_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo7_START)},
        {SOC_SMART_OCP_RECORD2_ADDR(0), BIT(SOC_SMART_OCP_RECORD2_ocp_ldo8_START)},
        
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo9_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo10_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo11_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo12_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo13_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo14_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo15_START)},
        {SOC_SMART_OCP_RECORD3_ADDR(0), BIT(SOC_SMART_OCP_RECORD3_ocp_ldo16_START)},

        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo17_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo18_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo19_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo20_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo21_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo22_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo23_START)},
        {SOC_SMART_OCP_RECORD4_ADDR(0), BIT(SOC_SMART_OCP_RECORD4_ocp_ldo24_START)},
    };

    int i;
    unsigned char ret = 0;

    for (i=0;i<24;i++){
        if (reg_addr == ldo_ocp_tbl[i].reg_addr && (ldo_dont_ocp_mask&(1<<i))){
            ret |= ldo_ocp_tbl[i].bit;
        }
    }

    return ret;
}

/*****************************************************************************
 函 数 名  : smart_ocp_scp_wq_hander
 功能描述  :  smart ocp scp hander
 输入参数  : struct work_struct *work
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月8日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void smart_ocp_scp_wq_hander(struct work_struct *work)
{
    PMUIRQ_STAT* cur_stat = (PMUIRQ_STAT*)NULL;
    BSP_U32*reg_base_addr = (BSP_U32*)NULL;
    BSP_U32*stat_reg_buf = (BSP_U32*)NULL;
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    BSP_U32 reg_size=0;
    BSP_U32 reg_id = 0;
    BSP_U32 data_width = 0;
    PMIC_MNTN_DESC * mntn_desc = &smart_mntn_ops;

    cur_stat = pmic_get_pmustat();
    pmu_res_ctrl = pmic_get_pmuctrl();

    mntn_desc->mntn_ops->record_read();

    reg_base_addr = pmu_res_ctrl->stat_reg[PMIC_RECORD_REG_TYPE_ID];
    stat_reg_buf = cur_stat->stat_reg_buf[PMIC_RECORD_REG_TYPE_ID];
    reg_size = pmu_res_ctrl->stat_reg_size[PMIC_RECORD_REG_TYPE_ID];
    data_width = pmu_res_ctrl->data_width;

    for(reg_id= 0;reg_id<reg_size;reg_id++)
    {
        if(0 != stat_reg_buf[reg_id])
        {
          char string_buf[128] = "\0";
          volatile unsigned char ocp_deb_data = 0;
          ocp_deb_data = pmussi_reg_read(SOC_SMART_OCP_DEB_ADDR(0));
          pr_err("PMU OCP DEB: 0x%x\n",ocp_deb_data);
          pr_err("PMU OCP SCP:addr 0x%x data 0x%x\n",reg_base_addr[reg_id],stat_reg_buf[reg_id]);
          snprintf(string_buf,128,"PMU DEB:0x%x OCP SCP:addr 0x%x data 0x%x\n",ocp_deb_data,reg_base_addr[reg_id],stat_reg_buf[reg_id]);

          if(SOC_SMART_OCP_RECORD3_ADDR(0) == reg_base_addr[reg_id])
          {
            unsigned char reg_data = (unsigned char)stat_reg_buf[reg_id];
            unsigned char ocp_ldo9_bit = reg_data&BIT(SOC_SMART_OCP_RECORD3_ocp_ldo9_START);
            unsigned char ocp_ldo11_bit = reg_data&BIT(SOC_SMART_OCP_RECORD3_ocp_ldo11_START);
            unsigned char ocp_ldo10_bit = reg_data&BIT(SOC_SMART_OCP_RECORD3_ocp_ldo10_START);

            reg_data &= ~(BIT(SOC_SMART_OCP_RECORD3_ocp_ldo9_START)|\
                      BIT(SOC_SMART_OCP_RECORD3_ocp_ldo11_START)|\
                          BIT(SOC_SMART_OCP_RECORD3_ocp_ldo10_START));

            reg_data &= ~smart_dont_ocp_mask(reg_base_addr[reg_id]);

            if(reg_data)
            {
              systemError(BSP_MODU_PMU,EXCH_S_PMU,0,string_buf,strlen(string_buf));
            }

            if(ocp_ldo9_bit)
            {
               unsigned char ldo9_onoff_status = pmussi_reg_read(SOC_SMART_SIMCARD_EN_ADDR(0));
               ldo9_onoff_status &= ~(BIT(SOC_SMART_SIMCARD_EN_en_ldo9_int_START));
               pmussi_reg_write(SOC_SMART_SIMCARD_EN_ADDR(0),ldo9_onoff_status);
            }

            /*SD card ocp, close SD power ldo10,then clear record and irq*/
            if(ocp_ldo10_bit)
            {
                unsigned char disable_ldo10 = 0;
                disable_ldo10 |= BIT(SOC_SMART_DISABLE3_dis_ldo10_int_START);
                pmussi_reg_write(SOC_SMART_DISABLE3_ADDR(0),disable_ldo10);
            }

            if(ocp_ldo11_bit)
            {
               unsigned char ldo11_onoff_status = pmussi_reg_read(SOC_SMART_SIMCARD_EN_ADDR(0));
               ldo11_onoff_status &= ~(BIT(SOC_SMART_SIMCARD_EN_en_ldo11_int_START));
               pmussi_reg_write(SOC_SMART_SIMCARD_EN_ADDR(0),ldo11_onoff_status);
            }

              smart_ocp_scp_finally_work(mntn_desc);
          }
          else
          {
              unsigned char reg_data = (unsigned char)stat_reg_buf[reg_id];

              reg_data &= ~smart_dont_ocp_mask(reg_base_addr[reg_id]);

              if (reg_data){
                  systemError(BSP_MODU_PMU,EXCH_S_PMU,0,string_buf,strlen(string_buf));
              }
              
              smart_ocp_scp_finally_work(mntn_desc);
          }
        }
    }
}

/*****************************************************************************
 函 数 名  : smart_power_off
 功能描述  : smart power 0ff info show
 输入参数  : struct notifier_block *self
             unsigned long event
             void *data
 输出参数  : 无
 返 回 值  : static int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月11日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static int smart_power_off(struct notifier_block *self, unsigned long event, void *data)
{
    PMIC_MNTN_DESC * mntn_desc = &smart_mntn_ops;
    unsigned int reg_id = 0;
    unsigned int vote_id = 0;

    pr_err("PMU SMART POWER DOWN SHOW\n");

    mntn_desc->mntn_ops->no_pwr_read();
    mntn_desc->mntn_ops->irq_read();
    mntn_desc->mntn_ops->record_read();
    pmic_poweron_show();

    pr_err("mask register\n");
    for(reg_id = SOC_SMART_IRQ1_MASK_ADDR(0);reg_id <= SOC_SMART_COUL_IRQ_MASK_ADDR(0);reg_id++)
    {
        pr_err("reg addr 0x%x data 0x%x\n",reg_id,pmussi_reg_read(reg_id));
    }

        pr_err("usr vote mask unmask\n");


    for(vote_id = 0;vote_id < IRQ_PMU_NR_END-IRQ_PMU_NR_BASE;vote_id++)
    {
        pr_err("     %d  %d     %d\n",vote_id,smart_mask_vote[vote_id],smart_unmask_vote[vote_id]);
    }

    return NOTIFY_OK;
}

/*****************************************************************************
 函 数 名  : pmic_get_pmustat
 功能描述  : pmic_get_pmustat
 输入参数  : void
 输出参数  : 无
 返 回 值  : PMUIRQ_STAT*
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
PMUIRQ_STAT* pmic_get_pmustat(void)
{
    return &smart_mntn_ops.stat;
}

/*****************************************************************************
 函 数 名  : pmic_mntn_dev_register
 功能描述  : pmic_mntn_dev_register
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void  pmic_mntn_dev_register(void)
{
    PMUIRQ_DATA* pmuirq_desc = pmic_get_pmuirq_desc();
    pmuirq_desc->mntn_desc = &smart_mntn_ops;
}

int pmu_version_check(void)
{
    unsigned int regval = 0;
    int ret = SSI_DEVICE_ERR;

    regval = pmussi_reg_read(PMU_VERSION_ADDR);
    if((regval >= PMU_VER_START) && (regval <= PMU_VER_END))
    {
        ret = SSI_DEVICE_OK;
    }

    return ret;
}

int pmu_32kclk_check(void)
{
    unsigned int regval = 0;
    int ret = SSI_DEVICE_ERR;

    regval = pmussi_reg_read(PMU_32K_STAT_ADDR);
    regval &= PMU_32K_FLAG_OFFSET;
    if(PMU_32K_OK_FLAG == regval)
    {
        ret = SSI_DEVICE_OK;
    }

    return ret;
}

/*以下为测试程序*/
void smart_ocp_scp_wq_test(void)
{
    struct work_struct test_work;
    smart_ocp_scp_wq_hander(&test_work);
}

void smart_mntn_init_test(void)
{
    struct work_struct test_work;
    smart_mntn_init(&test_work);
}

/*ADB SHELL 正常 中断异常 查看PMU 中断状态*/
void smart_mask_test(void)
{
    struct notifier_block self;
    int data;
    smart_power_off(&self,0,&data);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


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

#include <hsad/config_mgr.h>
#include "pmicirq_driver_inner.h"

PMUIRQ_DATA  pmuirq_desc;

unsigned int pmic_debug_flag = 0;
static int PMU_GPIO_IRQ = 0;

#ifdef    _DRV_LLT_
    extern struct irq_desc irq_desc[NR_IRQS];
    #define irq_to_desc(irq)    (&irq_desc[irq])
#endif

/*****************************************************************************
 函 数 名  : pmic_get_mntndesc
 功能描述  : get pmic mntn
 输入参数  : void
 输出参数  : 无
 返 回 值  : PMIC_MNTN_DESC *
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
PMIC_MNTN_DESC * pmicirq_get_mntndesc(void)
{
    if(NULL == pmuirq_desc.mntn_desc)
    {
        pr_err("%s %d mntn_desc NULL\n", __func__, __LINE__);
    }

    return pmuirq_desc.mntn_desc;
}

/*****************************************************************************
 函 数 名  : pmu_irq_unmask
 功能描述  : unmask
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void pmu_irq_unmask(unsigned int irq_num)
{
    struct irq_desc *desc = NULL ;

    if((irq_num < IRQ_PMU_NR_BASE)||(irq_num >= IRQ_PMU_NR_END))
    {
        pr_err("%s %d irq_num err 0x%x\n", __func__, __LINE__,irq_num);
        return ;
    }

    desc = irq_to_desc(irq_num);
    if (!desc) {
        printk("%s: request irq_desc fail\n",__func__);
        return;
    }

    if(NULL != desc->irq_data.chip->irq_unmask)
    {
        desc->irq_data.chip->irq_unmask(&desc->irq_data);
    }
}

/*****************************************************************************
 函 数 名  : pmic_ifc_handler
 功能描述  : Ccore notice Acore exec had done
 输入参数  : PMU_CPU_HANDLER *pMsgBody
 输出参数  : 无
 返 回 值  : long
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
long  pmic_ifc_handler(PMU_CPU_HANDLER *pMsgBody)
{
    return 0;
}


#ifndef    _DRV_LLT_
IFC_GEN_EXEC1(pmic_ifc_handler,IFC_INFIX, struct _PMU_CPU_HANDLER_* , pMsgBody, sizeof(struct _PMU_CPU_HANDLER_))
#endif
/*****************************************************************************
 函 数 名  : pmic_irq_mask
 功能描述  : irq mask
 输入参数  : struct irq_data *data
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void pmic_irq_mask(struct irq_data *data)
{
    BSP_U32 stat_reg_size = 0;
    BSP_U32*stat_reg = NULL;
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    PMUIRQ_DATA* pmu_irq_data = NULL;
    unsigned int irq = 0;
    unsigned int irq_opps = 0;
    unsigned int irq_base = 0;
    volatile unsigned char irq_reg_data = 0;
    unsigned char irq_reg_bit = 0;
    unsigned long flags = 0;
    PMIC_MNTN_DESC * mntn_desc = NULL;

    if (NULL == data)
    {
        pr_err("%s %d data return NULL\n", __func__, __LINE__);
        return;
    }

    irq = data->irq;
    if ((irq < IRQ_PMU_NR_BASE) || (irq > NR_IRQS)) {
        printk(" pmu irq is error,please check irq=%d\n", irq);
        return;
    }

    pmu_irq_data = (PMUIRQ_DATA* )irq_get_chip_data(irq);
    if (NULL == pmu_irq_data) {
        pr_err("%s %d irq_get_chip_data return NULL\n", __func__, __LINE__);
        return;
    }

    mntn_desc = pmicirq_get_mntndesc();
    mntn_desc->stat.mask_vote[irq-IRQ_PMU_NR_BASE]++;

    spin_lock_irqsave(&pmu_irq_data->pmic_spinlock,flags);

    pmu_res_ctrl = pmu_irq_data->pdev->dev.platform_data;

    stat_reg=pmu_res_ctrl->stat_reg[PMIC_IRQMASK_REG_TYPE_ID];
    stat_reg_size=pmu_res_ctrl->stat_reg_size[PMIC_IRQMASK_REG_TYPE_ID];

    irq_opps = irq - IRQ_PMU_NR_BASE;
    irq_base = irq_opps >> 3;/*pmu register width 8*/
    irq_reg_bit = irq_opps%8;
    irq_reg_data = pmussi_reg_read(stat_reg[irq_base]);
    irq_reg_data|= BIT(irq_reg_bit);
    pmussi_reg_write(stat_reg[irq_base],irq_reg_data);

    spin_unlock_irqrestore(&pmu_irq_data->pmic_spinlock,flags);

    return ;
}
/*****************************************************************************
 函 数 名  : pmic_irq_unmask
 功能描述  : irq mask
 输入参数  : struct irq_data *data
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void pmic_irq_unmask(struct irq_data *data)
{
    BSP_U32 stat_reg_size = 0;
    BSP_U32*stat_reg = NULL;
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    PMUIRQ_DATA* pmu_irq_data = NULL;
    unsigned int irq = 0;
    unsigned int irq_opps = 0;
    unsigned int irq_base = 0;
    volatile unsigned char irq_reg_data = 0;
    unsigned char irq_reg_bit = 0;
    unsigned long flags = 0;
    PMIC_MNTN_DESC * mntn_desc = NULL;

    if (NULL == data)
    {
        pr_err("%s %d data return NULL\n", __func__, __LINE__);
        return;
    }

    irq = data->irq;
    if ((irq < IRQ_PMU_NR_BASE) || (irq > NR_IRQS)) {
        printk(" pmu irq is error,please check irq=%d\n", irq);
        return;
    }

    pmu_irq_data = (PMUIRQ_DATA* )irq_get_chip_data(irq);
    if (NULL == pmu_irq_data) {
        pr_err("%s %d irq_get_chip_data return NULL\n", __func__, __LINE__);
        return;
    }

    mntn_desc = pmicirq_get_mntndesc();
    mntn_desc->stat.unmask_vote[irq-IRQ_PMU_NR_BASE]++;

    spin_lock_irqsave(&pmu_irq_data->pmic_spinlock,flags);

    pmu_res_ctrl = pmu_irq_data->pdev->dev.platform_data;

    stat_reg=pmu_res_ctrl->stat_reg[PMIC_IRQMASK_REG_TYPE_ID];
    stat_reg_size=pmu_res_ctrl->stat_reg_size[PMIC_IRQMASK_REG_TYPE_ID];

    irq_opps = irq - IRQ_PMU_NR_BASE;

    irq_base = irq_opps >> 3;/*pmu register width 8*/

    irq_reg_bit = irq_opps%8;

    irq_reg_data = pmussi_reg_read(stat_reg[irq_base]);

    irq_reg_data = irq_reg_data & (~(BIT(irq_reg_bit)));

    pmussi_reg_write(stat_reg[irq_base],irq_reg_data);

    spin_unlock_irqrestore(&pmu_irq_data->pmic_spinlock,flags);

    return ;
}

static struct irq_chip pmu_irqchip = {
    .name       = "PMU",
    .irq_mask   = pmic_irq_mask,
    .irq_unmask = pmic_irq_unmask,
};

void sim_hpd_irq_mask(void)
{
    int i = 0;
     struct irq_desc *desc = NULL ;
    /*mask sim hpd irq*/
    for (i = SIM1_HPD_OUT_F_TYPE; i < (SIM2_HPD_IN_R_TYPE+1); i++)
    {
        desc = irq_to_desc(i);
        if (!desc) {
            printk("sim_hpd_irq_mask[%d] request irq_desc fail\n",i);
            continue;
        }
        desc->irq_data.chip->irq_mask(&desc->irq_data);
    }
}

void sim_hpd_regulator(unsigned irq)
{
    int ret;
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    BSP_U32*reg_addr = NULL;
    BSP_U32 reg_value=0;
    SOC_SMART_IRQ4_UNION  irq4_reg_val;
    SOC_SMART_SIMCARD_EN_UNION simcard_en;

    pmu_res_ctrl = pmuirq_desc.pdev->dev.platform_data;
    reg_addr = pmu_res_ctrl->stat_reg[PMIC_IRQ_REG_TYPE_ID];

    ret=BSP_PMU_RegGet(SOC_SMART_SIMCARD_EN_ADDR(0),&reg_value);
    if (BSP_OK != ret)
    {
       pr_err("BSP_PMU_RegGet err %s %d  \n",__func__, __LINE__);
       return;
    }
    simcard_en.value = reg_value;

    ret=BSP_PMU_RegGet(reg_addr[PMIC_REG_IRQ4],&reg_value);
    if (BSP_OK != ret)
    {
       pr_err("BSP_PMU_RegGet err %s %d  \n",__func__, __LINE__);
       return;
    }
    irq4_reg_val.value = reg_value;

    if(irq4_reg_val.reg.sim0_hpd_out_f)
    {
        simcard_en.reg.en_ldo9_int = 1;
        simcard_en.reg.sim0_en_int = 1;
        pr_info("sim1_hpd_out_f, SIM_CARD_EN set to %d\n", simcard_en.value);
    }

    if(irq4_reg_val.reg.sim0_hpd_in_f)
    {
        simcard_en.reg.en_ldo9_int = 0;
        simcard_en.reg.sim0_en_int = 0;
        pr_info("sim1_hpd_in_f, SIM_CARD_EN set to %d\n", simcard_en.value);
    }

    if(irq4_reg_val.reg.sim1_hpd_out_f)
    {
        simcard_en.reg.en_ldo11_int = 1;
        simcard_en.reg.sim1_en_int = 1;
        pr_info("sim2_hpd_out_f, SIM_CARD_EN RO set to %d\n", simcard_en.value);
    }

    if(irq4_reg_val.reg.sim1_hpd_in_f)
    {
        simcard_en.reg.en_ldo11_int = 0;
        simcard_en.reg.sim1_en_int = 0;
        pr_info("sim2_hpd_in_f, SIM_CARD_EN set to %d\n", simcard_en.value);
    }

    if (irq4_reg_val.reg.sim0_hpd_out_f || irq4_reg_val.reg.sim0_hpd_in_f
        || irq4_reg_val.reg.sim1_hpd_out_f || irq4_reg_val.reg.sim1_hpd_in_f)
    {
        pr_info("SIM_CARD_EN W %d\n", simcard_en.value);
        BSP_PMU_RegSet(SOC_SMART_SIMCARD_EN_ADDR(0),simcard_en.value);
    }

    ret=BSP_PMU_RegGet(SOC_SMART_SIMCARD_EN_ADDR(0),&reg_value);
    pr_info("SIM_CARD_EN RO %d\n", reg_value);
    return;
}

/*****************************************************************************
 函 数 名  : pmic_irq_handler
 功能描述  : irq hander functions
 输入参数  : unsigned irq
             struct irq_desc *desc
 输出参数  : 无
 返 回 值  : static void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月25日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
void pmic_irq_handler(unsigned irq, struct irq_desc *desc)
{
    PMUIRQ_RES_CTRL* pmu_res_ctrl = NULL;
    PMUIRQ_DATA * pmu_irq_data = &pmuirq_desc;
    unsigned int irq_data[PMIC_IRQ_REG_BUTT] = {0};
    BSP_U32 reg_id=0;
    BSP_U32 bit=0;
    BSP_U32 irq_reg_num = 0;
    BSP_U32 data_width = 0;

    if (NULL == desc)
    {
        pr_err("%s %d desc  NULL\n", __func__, __LINE__);
        return;
    }

    printk("%s irq 0x%0x\n",__func__,irq);

    /*关中断*/
    desc->irq_data.chip->irq_disable(&desc->irq_data);

    /*SIM小卡热插拔(HPD)需要在检测到HPD中断后*/
    /*先关闭对应的LDO电源及sim卡切换电路再清中断，*/
    /*这个是由PMU设计决定的*/
    /*在HPD中断处理中关闭电源是为了防止卡拔出过程中电源短路*/
    /***重要说明***/
    /*由于硬件支持hpd较少，且hpd存在一定缺陷，*/
    /*故软件方案上采用1点检测方案，如需要采用两点方案，*/
    /*放开sim_hpd_regulator，并打开balong_sim.h的SIM_HPD宏*/
#if 0
    sim_hpd_regulator(irq);
#endif

    pmu_res_ctrl = pmu_irq_data->pdev->dev.platform_data;

    (void)pmic_status_reg_read(pmu_res_ctrl,PMIC_IRQ_REG_TYPE_ID,irq_data);
    (void)pmu_status_reg_clear(pmu_res_ctrl,PMIC_IRQ_REG_TYPE_ID);

    irq_reg_num = pmu_res_ctrl->stat_reg_size[PMIC_IRQ_REG_TYPE_ID];
    data_width = pmu_res_ctrl->data_width;

    for (reg_id = 0; reg_id < irq_reg_num; reg_id++)
    {
        for (bit = 0; bit < data_width; bit++)
        {
            if (irq_data[reg_id] & (0x01 << bit))
            {
              unsigned int irq_num = IRQ_PMU_NR_BASE+reg_id*data_width+bit;
              printk("PMU generic_handle_irq start irq 0x%0x\n",irq_num);
              generic_handle_irq(irq_num);
              printk("PMU generic_handle_irq end irq 0x%0x\n",irq_num);
            }
        }
    }

    desc->irq_data.chip->irq_enable(&desc->irq_data);
}

/*****************************************************************************
 函 数 名  : pmic_ocp_scp_irq_hander
 功能描述  : ocp scp irq hander
 输入参数  : int irq
             void *data
 输出参数  : 无
 返 回 值  : static irqreturn_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static irqreturn_t pmic_ocp_scp_irq_hander(int irq, void *data)
{
    struct irq_desc *desc = NULL ;
    PMUIRQ_DATA  *pmu_irq_data = (PMUIRQ_DATA*)data;
    PMIC_MNTN_DESC* mntn_desc = pmu_irq_data->mntn_desc;

    desc = irq_to_desc(irq);
    if (!desc) {
        printk("PMU irq handler request irq_desc fail\n");
        return IRQ_NONE;
    }

    if(NULL != desc->irq_data.chip->irq_mask)
    {
        desc->irq_data.chip->irq_mask(&desc->irq_data);
    }

    queue_work(mntn_desc->ocp_scp_wq, &mntn_desc->ocp_scp_wk);
    return IRQ_HANDLED;
}

/*****************************************************************************
 函 数 名  : pmic_otmp_irq_hander
 功能描述  : otmp irq hander
 输入参数  : int irq
             void *data
 输出参数  : 无
 返 回 值  : static irqreturn_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月5日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static irqreturn_t pmic_otmp_irq_hander(int irq, void *data)
{
    PMUIRQ_DATA  *pmu_irq_data = (PMUIRQ_DATA*)data;
    PMIC_MNTN_DESC* mntn_desc = pmu_irq_data->mntn_desc;
    queue_work(mntn_desc->otmp_wq, &mntn_desc->otmp_wk);
    return IRQ_HANDLED;
}

/*****************************************************************************
 函 数 名  : pmic_irq_init
 功能描述  : pmic irq  init
 输出参数  : 无
 返 回 值  : BSP_S32 p
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月1日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
 BSP_S32 pmic_irq_init(struct platform_device *pdev)
 {
    int ret = 0;
    unsigned int i = 0;
    int irq = -1;
    struct irq_desc *desc = NULL ;
    struct irq_desc *gpio_desc = NULL;
    PMUIRQ_DATA  *pmu_irq_data = NULL;
    PMIC_MNTN_DESC* mntn_desc = NULL;

    if (NULL == pdev)
    {
        pr_err("%s %d pmu no platform data\n", __func__, __LINE__);
        return -EINVAL;
    }

    irq = gpio_to_irq(PMU_GPIO_IRQ);
    pmuirq_desc.irq = irq;

    printk("PMU GPIO IRQ 0x%0x\n",irq);

    pmu_irq_data = (PMUIRQ_DATA *)kzalloc(sizeof(*pmu_irq_data), GFP_KERNEL);
    if (pmu_irq_data == NULL) {
        pr_err(" pmu irq kzalloc is failed,please check!\n");
        return -ENOMEM;
    }

    pmu_irq_data->pdev = pdev;
    pmu_irq_data->mntn_desc = pmicirq_get_mntndesc();
    mntn_desc = pmu_irq_data->mntn_desc;

    spin_lock_init(&pmu_irq_data->pmic_spinlock);

    for (i = IRQ_PMU_NR_BASE; i < IRQ_PMU_NR_END; i++)
    {
        irq_set_chip(i, &pmu_irqchip);
        irq_set_handler(i, handle_simple_irq);
        set_irq_flags(i, IRQF_VALID);
        irq_set_chip_data(i, pmu_irq_data);
        desc = irq_to_desc(i);
        if (!desc) {
            printk("sim_hpd_irq_mask[%d] request irq_desc fail\n",i);
            continue;
        }

        desc->irq_data.chip->irq_mask(&desc->irq_data);
    }

    pmu_irq_data->irq = irq;

    ret = gpio_request(PMU_GPIO_IRQ, "pmuirq");
    if (ret) {
        pr_err("pmic_irq_init probe can't request gpio for data.\n");
        goto err_gpio_free;
    }

    gpio_direction_input(PMU_GPIO_IRQ);
    gpio_desc = irq_to_desc(irq);
    if (!gpio_desc) {
        printk("%s: request gpio_desc fail\n",__func__);
        goto err_gpio_free;
    }

    irq_set_handler_data(irq, pmu_irq_data);
    irq_set_chained_handler(irq, pmic_irq_handler);
    irq_set_irq_type(irq, IRQ_TYPE_LEVEL_LOW);
    gpio_desc->irq_data.chip->irq_enable(&gpio_desc->irq_data);


    mntn_desc->ocp_scp_wq = create_singlethread_workqueue("pmu-ocp-scp-wq");
    INIT_WORK(&mntn_desc->ocp_scp_wk, (void *)mntn_desc->ocp_scp_wk_ops);

    ret = request_irq(OCP_SCP_R_TYPE, pmic_ocp_scp_irq_hander, IRQF_DISABLED|IRQF_NO_SUSPEND,
          "pmu-ocp_scp-irq", (void*)pmu_irq_data);
    if(ret)
    {
        pr_err("%s,%d request_irq OCP_SCP_R_TYPE faile\n", __func__, __LINE__);
        goto err_gpio_free;
    }

    mntn_desc->otmp_wq = create_singlethread_workqueue("pmu-otmp-wq");
    INIT_WORK(&mntn_desc->otmp_wk, (void *)mntn_desc->otmp_wk_ops);

    ret = request_irq(OTMP_D1R_TYPE, pmic_otmp_irq_hander, IRQF_DISABLED|IRQF_NO_SUSPEND,
        "pmu-otmp-irq", (void*)pmu_irq_data);
    if(ret)
    {
        pr_err("request_irq OCP_SCP_R_TYPE\n");
        goto err_gpio_free;
    }

    /*mask sim hpd irq*/
    sim_hpd_irq_mask();

    return 0;

err_gpio_free:
    gpio_free(PMU_GPIO_IRQ);
    kfree(pmu_irq_data);
    return ret;
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
static int __init pmicirq_probe(struct platform_device *pdev)
{
    memset((void*)&pmuirq_desc,0,sizeof(pmuirq_desc));
    pmuirq_desc.pdev = pdev;

    if(BSP_ERROR == pmic_mntn_init())
    {
       pr_err("%s %d err\n",__func__,__LINE__);
       return -EINVAL;
    }

    if(0 != pmic_irq_init(pdev))
    {
       pr_err("%d pmic_irq_init err\n", __LINE__);
       return -EINVAL;
    }

    printk("IRQ_PMU_NR_BASE:0x%0x IRQ_PMU_NR_END 0x%0x\n",IRQ_PMU_NR_BASE,IRQ_PMU_NR_END);

    return 0;
}

/*****************************************************************************
 函 数 名  : pmicirq_remove
 功能描述  : pmicirq_remove
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
int pmicirq_remove(struct platform_device *pdev)
{
    int i = 0;

    gpio_free(PMU_GPIO_IRQ);

    /* cleanup irqchip */
    for (i = IRQ_PMU_NR_BASE; i < IRQ_PMU_NR_END; i++) {
        irq_set_chip_and_handler(i, NULL, NULL);
    }

    pmic_mntn_uninit();

    return 0;
}

static struct platform_driver pmicirq_driver = {
    .probe = pmicirq_probe,
    .remove = pmicirq_remove,
    .driver     = {
        .name   = "smartStarIrq",
    },
};

static char banner[] __initdata =
    KERN_INFO "PMIC IRQ driver, (c) 2013 Hisilicon Electronics\n";

static void set_pmu_gpio(void)
{
    int ret = 0;

    ret = get_hw_config_int("pmu/gpio_pmu_irq", &PMU_GPIO_IRQ, NULL);
    if (false == ret) {
        printk("PMU_GPIO_IRQ value not found !\n");
        PMU_GPIO_IRQ = GPIO_1_0;
    }
}

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
static int __init pmicirq_init(void)
{
    int ret = 0;

    set_pmu_gpio();
	
    printk(banner);
    ret = platform_driver_register(&pmicirq_driver);
    if (ret != 0)
    {
        pr_err("pmicirq_init Failed to register  driver: %d %s %d  \n",ret,__func__, __LINE__);
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
static void __exit pmicirq_exit(void)
{
    platform_driver_unregister(&pmicirq_driver);
}

#if (defined(BOARD_ASIC))
subsys_initcall(pmicirq_init);
module_exit(pmicirq_exit);
#endif

static int __init pmic_ifc_init(void)
{
#ifndef    _DRV_LLT_
   if(MAILBOX_OK !=mailbox_ifc_register(MAILBOX_IFC_ACPU_TO_CCPU_PMIC_IRQEVENT_REPO,pmic_ifc_handler))
   {
       pr_err("%s %d  mailbox_ifc_register err\n",__func__, __LINE__);
       return -1;
   }
#endif
    return 0;
}

module_init(pmic_ifc_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");
MODULE_DESCRIPTION(" Hisilicon PMIC IRQ driver");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


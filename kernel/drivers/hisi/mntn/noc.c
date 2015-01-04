/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  reset.c    hisi kernel noc driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/wakelock.h>			/* For file operations */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/suspend.h>
#include <linux/completion.h>
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/workqueue.h>		/* For workqueue... */
#include <linux/notifier.h>			/* For notifier... */
#include <linux/interrupt.h>		/* For request_irq*/
#include <linux/io.h>				/* For writel */
#include <linux/reboot.h>			/* For writel */
#include <general_sram_map.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include <DrvInterface.h>
#include <mach/platform.h>

#include "../../mntn/excDrv.h"
#include "BSP.h"

#ifndef BIT
#define BIT(x)  (1<<(x))
#endif

#define FaultEn_OFFSET 0x08
#define ErrClr_OFFSET  0x10
#define NOC_IRQ_MAX_TIMES 10
#define SHORT_INTERVAL_TIME 200    /*200ms*/

void __iomem *error_logger = NULL;
static int dummy = 0;
unsigned int g_noc_irq_times = 0;
unsigned long g_first_noc_irq_time =0;


static void dump_error_logger(void *base, unsigned int size)
{
    unsigned int offset;
    unsigned int *reg;

    printk("error logger dump : \n");

    for(offset = 0 ; offset < size ; offset += 4 * sizeof(unsigned int)){
        reg = (unsigned int *)(base + offset);
        printk("[%08x] : %08x %08x %08x %08x\n", offset, *reg, \
            *(reg + 1), *(reg + 2), *(reg + 3));
    }

    return;
}

static int noc_panic_notify(struct notifier_block *self,
			  unsigned long event, void *data)
{
    dump_error_logger(error_logger, REG_ERROR_LOGGER_0_IOSIZE);

	return NOTIFY_OK;
}

static struct notifier_block noc_on_panic_nb = {
	.notifier_call = noc_panic_notify,
	.priority = INT_MAX,
};

static irqreturn_t noc_irq(int irqno, void *param)
{
    unsigned int val;
    unsigned int reg;
    unsigned int flag = 0;
	unsigned long sctrl_base = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    unsigned long route_id;

    val = BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_19bit_START) |\
          BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_20bit_START);
    reg = readl(SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_ADDR(sctrl_base));
    if (reg & val)
        flag = 1;

    val = BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_19bit_START) |\
          BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_20bit_START);
    reg = readl(SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_ADDR(sctrl_base));
    if (reg & val)
        flag = 1;

    /*not this irq*/
    if (!flag)
        return IRQ_NONE;

    dump_error_logger(error_logger, REG_ERROR_LOGGER_0_IOSIZE);

    route_id = *(volatile unsigned int*)((unsigned int)error_logger + 0x18);

    if (check_himntn(HIMNTN_ACCESS_ERROR_REBOOT))
    {
        systemError((int)BSP_MODU_MNTN, EXCH_S_NOC, 0, error_logger, REG_ERROR_LOGGER_0_IOSIZE);
    }
    /*ends*/

    printk(KERN_ERR "Noc irq, route_id is 0x%x, g_noc_irq_times is %d\n", route_id, g_noc_irq_times);

    if (0 == g_noc_irq_times) {
        g_first_noc_irq_time = jiffies;
    }

    /*when noc_irq_times is 10, reboot by using systemError */
    if ((++g_noc_irq_times) >= NOC_IRQ_MAX_TIMES) {
        if (time_before(jiffies, g_first_noc_irq_time + msecs_to_jiffies(SHORT_INTERVAL_TIME))) {
            systemError((int)BSP_MODU_MNTN, EXCH_S_NOC, 0, error_logger, REG_ERROR_LOGGER_0_IOSIZE);
        }
        else {
            g_noc_irq_times = 0;
        }
    }

    /*clear error logger status*/
    reg = readl(error_logger + ErrClr_OFFSET);
    reg |= 0x1;
    writel(reg, error_logger + ErrClr_OFFSET);

    return IRQ_HANDLED;
}

unsigned int g_noc_fault_en_reg = 0;

static int noc_pm_notify(struct notifier_block *nfb, unsigned long action, void *ignored)
{
	switch (action)
	{
	case PM_SUSPEND_PREPARE:
        g_noc_fault_en_reg = readl(error_logger + FaultEn_OFFSET);
		break;
	case PM_POST_SUSPEND:
        writel(g_noc_fault_en_reg, error_logger + FaultEn_OFFSET);
		break;
	default:
		break;
	}

	return NOTIFY_OK;
}

static struct notifier_block noc_pm_nb = {
	.notifier_call = noc_pm_notify,
};
static int __init noc_init(void)
{
    unsigned int reg;
	unsigned long sctrl_base = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    int ret;

    error_logger = (void *)ioremap(REG_BASE_ERROR_LOGGER_0, REG_ERROR_LOGGER_0_IOSIZE);
    if (!error_logger){
        printk("%s : failed to ioremap error logger\n", __FUNCTION__);
        return -1;
    }

    /*enable error logger*/
    reg = readl(error_logger + FaultEn_OFFSET);
    reg |= 0x1;
    writel(reg, error_logger + FaultEn_OFFSET);

    /*clear error logger status*/
    reg = readl(error_logger + ErrClr_OFFSET);
    reg |= 0x1;
    writel(reg, error_logger + ErrClr_OFFSET);

#if 0
    /* if noc errLog is open, enable noc bus, configure 24bit of SYS_CTRL3 */
    if (0 != check_himntn(HIMNTN_NOC_ErrLog)){
        reg = readl(SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_ADDR(sctrl_base));
        reg |= 0x01000000;
        writel(reg, SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_ADDR(sctrl_base));
    }
#endif

    /*enable noc irq */
    reg = readl(SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_ADDR(sctrl_base));
    reg |= BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_20bit_START);
    reg |= BIT(SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_19bit_START);
    writel(reg, SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_ADDR(sctrl_base));

    /*connect irq handler*/
    ret = request_irq(IRQ_NOC, noc_irq, IRQF_SHARED, "noc",  &dummy);
	if (0 != ret) {
		printk(KERN_ERR"failed to request noc irq (%d)\n", ret);
        goto out;
   	}

	atomic_notifier_chain_register(&panic_notifier_list, &noc_on_panic_nb);

    /* register noc driver */
    (void)register_pm_notifier(&noc_pm_nb);

    return 0;

out:
    iounmap(error_logger);

    return -1;
}
module_init(noc_init);
static void __exit noc_exit(void)
{
	atomic_notifier_chain_unregister(&panic_notifier_list, &noc_on_panic_nb);

    free_irq(IRQ_NOC, NULL);

    return;
}
module_exit(noc_exit);



MODULE_DESCRIPTION("Hisilicon NOC module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");



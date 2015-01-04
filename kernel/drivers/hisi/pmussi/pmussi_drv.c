/*
 * Filename:	pmussi_drv.c
 *
 * Discription:  provide the pmussi interface
 *
 * Copyright: 	(C) 2013 Huawei.
 *
 * revision history: 1.0
 ****/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/pmussi_drv.h>
#include <linux/delay.h>
#include <linux/hardirq.h>
#include <mntn/excDrv.h>
#include <mach/platform.h>
#include "general_sram_map.h"

#define PMUSSI_LOCK()
#define PMUSSI_UNLOCK()
#define PMU_VER_REG_OPPS              (16)
#define PMU_VER_REG_WIDTH             (0x0FF)

static void __iomem *g_pmussi_base_addr = NULL;
static long sysfs_pmuss_regaddr = 0;
static DEFINE_MUTEX(pmussi_mutex);
static spinlock_t ssi_hardware_spinlock_t;
static unsigned long flags = 0;

#define PMUSSI_DEBUG
#ifdef PMUSSI_DEBUG
#define PMUSSI_ASSERT(expr)  do {if(expr) printk(KERN_ERR "pmussi fatal error!!!\n");} while(0)
#else
#define PMUSSI_ASSERT(expr)  do {} while(0)
#endif

#if defined CONFIG_MACH_HI6620SFT
static int ops_hole_us = 200;
void pmussi_set_ops_delay(int delay)  {ops_hole_us = delay;}
#define PMUSSI_OP_DELAY()       udelay(ops_hole_us)
#else
#define PMUSSI_OP_DELAY()
#endif
#define PMUSSI_REG(reg_addr)    (((reg_addr)<<2) + (unsigned int)g_pmussi_base_addr)


unsigned int pmu_get_version(void)
{
    unsigned int    uvalue = 0;

    uvalue = readl(SOC_AO_SCTRL_SC_RESERVED34_ADDR(REG_BASE_SC_ON_VIRT));
    uvalue = uvalue >> PMU_VER_REG_OPPS;
    uvalue = uvalue & PMU_VER_REG_WIDTH;
    return uvalue;
}

void ssi_hardware_spinlock(SSI_VOTE1_E bit_ops)
{
    volatile SOC_AO_SCTRL_SC_SYS_STAT0_UNION *sc_sys_stat0 = 0;

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
        return;
    }

    while(1)
    {
        spin_lock_irqsave((spinlock_t *)&ssi_hardware_spinlock_t, flags);
        *(volatile int *)AOSCTRL_SC_MCU_VOTE1EN0 = 1<<bit_ops;
        sc_sys_stat0 = (volatile SOC_AO_SCTRL_SC_SYS_STAT0_UNION *)AOSCTRL_SC_SYS_STAT0;
        if(0 == sc_sys_stat0->reg.vote1_semphsta)
        {
           return ;/*get vote*/
        }
        else
        {
            *(volatile int *)AOSCTRL_SC_MCU_VOTE1DIS0 = 1<<bit_ops;
            spin_unlock_irqrestore((spinlock_t *)&ssi_hardware_spinlock_t, flags);
            udelay(1);
        }

    }
}

void ssi_hardware_unspinlock(SSI_VOTE1_E bit_ops)
{
    udelay(1);

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
        return;
    }

    *(volatile int *)AOSCTRL_SC_MCU_VOTE1DIS0 = 1<<bit_ops;
    spin_unlock_irqrestore((spinlock_t *)&ssi_hardware_spinlock_t, flags);

}

unsigned char pmussi_err_reg_read (void __iomem *base, unsigned int reg_addr)
{
    unsigned char regval;

#define PMUSSI_ERR_REG(reg_addr)    (((reg_addr)<<2) + (unsigned int)base)

    ssi_hardware_spinlock(VOTE1_ACPU_PMU_GET);
    regval =  *(volatile unsigned char*)PMUSSI_ERR_REG(reg_addr);
    ssi_hardware_unspinlock(VOTE1_ACPU_PMU_GET);

    return regval;
}

void pmussi_err_reg_write (void __iomem *base, unsigned int reg_addr, unsigned char regval)
{
    #define PMUSSI_ERR_REG(reg_addr)    (((reg_addr)<<2) + (unsigned int)base)

    ssi_hardware_spinlock(VOTE1_ACPU_PMU_SET);
    *(volatile unsigned char*)PMUSSI_REG(reg_addr) = regval;
    ssi_hardware_unspinlock(VOTE1_ACPU_PMU_SET);
}

unsigned char pmussi_reg_read (unsigned int reg_addr)
{
    unsigned char regval;

    PMUSSI_ASSERT(0 == g_pmussi_base_addr);

    ssi_hardware_spinlock(VOTE1_ACPU_PMU_GET);
    regval =  *(volatile unsigned char*)PMUSSI_REG(reg_addr);
    ssi_hardware_unspinlock(VOTE1_ACPU_PMU_GET);

    return regval;
}

void pmussi_reg_write (unsigned int reg_addr, unsigned char regval)
{
    PMUSSI_ASSERT(0 == g_pmussi_base_addr);

    ssi_hardware_spinlock(VOTE1_ACPU_PMU_SET);
    *(volatile unsigned char*)PMUSSI_REG(reg_addr) = regval;
    ssi_hardware_unspinlock(VOTE1_ACPU_PMU_SET);
}



int pmussi_recv_data (unsigned int reg_addr, char *buffer, int len)
{
    int i;

    if ((len > 32) || (NULL == buffer)) {
        return -EINVAL;
    }

    PMUSSI_ASSERT(0 == g_pmussi_base_addr);

    PMUSSI_LOCK();
    for (i = 0; i < len; i++) {
        *(buffer + i) = pmussi_reg_read(reg_addr+i);
        PMUSSI_OP_DELAY();
    }
    PMUSSI_UNLOCK();

    return 0;
}

int pmussi_send_data (unsigned int reg_addr, char *buffer, int len)
{
    int i;

    if ((len > 32) || (NULL == buffer)) {
        return -EINVAL;
    }

    PMUSSI_ASSERT(0 == g_pmussi_base_addr);

    PMUSSI_LOCK();
    for (i = 0; i < len; i++) {
        pmussi_reg_write(reg_addr+i,*(buffer + i));
        PMUSSI_OP_DELAY();
    }
    PMUSSI_UNLOCK();

    return 0;
}


static ssize_t pmussi_regaddr_show(struct device_driver *driver, char *buf)
{
    if (g_pmussi_base_addr == 0)
        return (ssize_t)strncpy(buf,"not-ready",sizeof("not-ready"));
    else
        return sprintf(buf, "0x%x\n", (unsigned int)sysfs_pmuss_regaddr);
}

static ssize_t pmussi_regaddr_store(struct device_driver *driver,const char *buf, size_t count)
{
    long val;
    if ((strict_strtol(buf, 16, &val) < 0)
        || (g_pmussi_base_addr == 0))
        return -EINVAL;
    else
        sysfs_pmuss_regaddr = val;

    return count;
}

static ssize_t pmussi_regval_show(struct device_driver *driver, char *buf)
{
    char regval = 0;

    if (g_pmussi_base_addr == 0) {
        return (ssize_t)strncpy(buf,"not-ready",sizeof("not-ready"));
    } else {
        pmussi_recv_data(sysfs_pmuss_regaddr,(char*)&regval,1);
        return sprintf(buf, "0x%x\n",regval);
    }
}

static ssize_t pmussi_regval_store(struct device_driver *driver,const char *buf, size_t count)
{
    long regval;
    if ((strict_strtol(buf, 16, &regval) < 0)
        || (g_pmussi_base_addr == 0)) {
        return -EINVAL;
    } else {
        pmussi_send_data(sysfs_pmuss_regaddr,(char*)&regval,1);
    }
    return count;
}


static DRIVER_ATTR(pmussi_regaddr, S_IRUGO|S_IWUSR, pmussi_regaddr_show, pmussi_regaddr_store);
static DRIVER_ATTR(pmussi_regval, S_IRUGO|S_IWUSR, pmussi_regval_show, pmussi_regval_store);

SSI_DEVICE_INFO_STRU ssi_devices[SSI_DEVICE_BUTT] =
{
    {"PMU"   , -1},
    {"CODEC" , -1},
    {"32KClk", -1}
};

void pmussi_device_state_notify(SSI_DEVICE_E dev_type , int dev_stat)
{
    if((dev_type < 0) || (dev_type >= SSI_DEVICE_BUTT))
    {
        printk("pmussi device tpye error : %d\n",dev_type);
        return;
    }

    if((SSI_DEVICE_OK != dev_stat) && (SSI_DEVICE_ERR != dev_stat))
    {
        printk("pmussi device stat error : %d\n",dev_stat);
        return;
    }

    ssi_devices[dev_type].dev_stat = dev_stat;

    return;
}

static ssize_t pmussi_device_check_show(struct device_driver *driver, char *buf)
{
    char *temp = buf;
    ssize_t len = 0;
    ssize_t sumlen = 0;
    int i = 0;

    for( i=0 ; i<SSI_DEVICE_BUTT ; i++)
    {
        len = sprintf(temp, "%s : %d\n", ssi_devices[i].dev_name , ssi_devices[i].dev_stat);
        temp = temp + len;
        sumlen = sumlen + len;
    }

    return sumlen;
}

static DRIVER_ATTR(pmussi_device_check, S_IRUGO|S_IWUSR, pmussi_device_check_show, NULL);

static int __devinit pmussi_probe(struct platform_device *pdev)
{
    struct pmussi_dev_info *di = (struct pmussi_dev_info *)pdev->dev.platform_data;

    spin_lock_init(&ssi_hardware_spinlock_t);

    g_pmussi_base_addr = (void __iomem *)ioremap(di->phy_base_addr,0x1000);
    if (!g_pmussi_base_addr) {
    	dev_err(&pdev->dev,	"map virtaddr failed!\n");
    	return -ENOMEM;
    }

    if (di->init)
        di->init();

    platform_set_drvdata(pdev, di);

    return 0;
}

static void pmussi_shutdown(struct platform_device *pdev)
{
    printk("[%s],+\n", __func__);
    printk("[%s],-\n", __func__);
}

#ifdef CONFIG_PM
static int pmussi_suspend(struct platform_device *pdev, pm_message_t pm)
{
    /*struct pmussi_dev_info *di = (struct pmussi_dev_info *)pdev->dev.platform_data;*/

    printk("[%s],+\n", __func__);
    printk("[%s],-\n", __func__);

    return 0;
}

static int pmussi_resume(struct platform_device *pdev)
{
    /*struct pmussi_dev_info *di = (struct pmussi_dev_info *)pdev->dev.platform_data;*/

    printk("[%s],+\n", __func__);
    printk("[%s],-\n", __func__);

    return 0;
}

#else
#define pmussi_suspend NULL
#define pmussi_resume NULL
#endif

static struct platform_driver pmussi_driver = {
	.probe  = pmussi_probe,
	.suspend	= pmussi_suspend,
	.resume		= pmussi_resume,
	.shutdown  = pmussi_shutdown,
	.driver	= {
		.name =	"pmussi",
		.owner = THIS_MODULE,
	},
};

/**
 * init the module.
 */
static int __init pmussi_init(void)
{
	int	retval = 0;
	retval	= platform_driver_register(&pmussi_driver);
	if (retval) {
		printk("%s:	platform_driver_register failed %d\n",
				__func__, retval);
	}

    retval = driver_create_file(&(pmussi_driver.driver), &driver_attr_pmussi_regaddr);
    if (retval) {
        platform_driver_unregister(&pmussi_driver);
    }

    retval = driver_create_file(&(pmussi_driver.driver), &driver_attr_pmussi_device_check);
    if (retval) {
        platform_driver_unregister(&pmussi_driver);
    }

    retval = driver_create_file(&(pmussi_driver.driver), &driver_attr_pmussi_regval);
    if (retval) {
        platform_driver_unregister(&pmussi_driver);
        driver_remove_file(&(pmussi_driver.driver), &driver_attr_pmussi_regaddr);
    }

	return retval;
}

/**
 * Cleans up the module.
 */
static void	__exit pmussi_exit(void)
{
    driver_remove_file(&(pmussi_driver.driver), &driver_attr_pmussi_regaddr);
    driver_remove_file(&(pmussi_driver.driver), &driver_attr_pmussi_regval);
    driver_remove_file(&(pmussi_driver.driver), &driver_attr_pmussi_device_check);
	platform_driver_unregister(&pmussi_driver);
}


core_initcall(pmussi_init);
module_exit(pmussi_exit);

MODULE_AUTHOR("Hisilicon Co. Ltd");
MODULE_DESCRIPTION("PMUSSI interface driver");
MODULE_LICENSE("GPL");




/*************************************************************************
*   版权所有(C) 1987-2012, 深圳华为技术有限公司.
*
*   文 件 名 :  etb.c
*   作    者 :  刘磊
*   描    述 :  A核上下电备份恢复
*   修改历史 :    
*   1.修改日期 : 
*     修改作者 : 
*     修改记录 : 低功耗场景备份恢复机制
*************************************************************************/
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/watchdog.h>		/* For the watchdog specific items */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/platform_device.h>	/* For platform_driver framework */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/io.h>				/* For inb/outb/... */
#include <linux/clk.h>
#include <linux/etb.h>
#include <linux/mtd/nve.h>
#include <linux/mtd/nve_interface.h>

static void __iomem *etm_base_acpu = NULL;
static unsigned int etm_srigster = 0x0;

#if 1
/*****acpu_while_test********/
void etb_test(void)
{
    while(1)
    {
        writel(0x81a181a1,0xF74103A8);
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        writel(0x11111111, 0xF74103A8);
        asm("NOP");
        asm("NOP");
        asm("NOP");
        writel(0x7E577E57, 0xF74103A8);
    }
}
#endif

/************************************************
功能:配置ETM 计数器级联
*************************************************/
static void set_etm_counter(void __iomem *etm_base)
{
	unsigned int ulRegEtmcntenr1 = 0;
	
	writel(COUNTER_VALUE1, ETM_ETMCNTRLDVR1(etm_base));
	/*配置计数器1到达0时触发计数*/
	ulRegEtmcntenr1 = 0x20041;
	writel(ulRegEtmcntenr1, ETM_ETMCNTENR1(etm_base));
	/*配置计数器0到达0时触发重载*/
	writel(0x40, ETM_ETMCNTRELDEVR1(etm_base));
	writel(COUNTER_VALUE1, ETM_ETMCNTVR1(etm_base));
	
	writel(COUNTER_VALUE2, ETM_ETMCNTRLDVR2(etm_base));
	ulRegEtmcntenr1 = readl(ETM_ETMCNTENR2(etm_base));
	ulRegEtmcntenr1 |= ALWAYS_TRUE;
	writel(ulRegEtmcntenr1, ETM_ETMCNTENR2(etm_base));
	/*配置计数器1到达0时触发重载*/
	writel(0x41, ETM_ETMCNTRELDEVR2(etm_base));
	writel(COUNTER_VALUE2, ETM_ETMCNTVR2(etm_base));
}

/************************************************
功能:配置ETM 组件
*************************************************/
int config_etm( char processor, void __iomem *etm_base)
{
	char max_processor = 0;
	unsigned int count = TIMEOUT;
	unsigned int ulReg = 0;

	/**make sure the processor is existence**/
	max_processor = (readl(ETM_ETMSCR(etm_base)) >> 12) & 0x7;	
	if(processor > max_processor)
	{
		printk(KERN_ERR "[ETB] max_processor=%d,processor=%d\r\n", max_processor, processor);
		printk(KERN_ERR "[ETB] cpu etb enable fail! no such processor\r\n");
		return -1;
	}
	
	etm_unlock(etm_base);
	
	REG_SET_BIT(ETM_ETMPDCR(etm_base), ETMPDCR_POWERUP);
	REG_CLEAR_BIT(ETM_ETMCR(etm_base), ETMCR_POWERDOWN);

	/***set program bit***/
	REG_SET_BIT(ETM_ETMCR(etm_base), ETMCR_PROGBIT);
	while(!REG_TEST_BIT(ETM_ETMSR(etm_base), ETMSR_PROGBIT) && --count);
	if(!count)
	{
		/* 超时错误*/
		printk(KERN_ERR "[ETB] Waiting for progbit to assert timed out(enable1).\n");
		etm_lock(etm_base);
		return -1; 
	}

	/****start set reg****/
	ulReg = readl(ETM_ETMCR(etm_base));
	ulReg &= (BIT(ETMCR_PROGBIT) | BIT(ETMCR_POWERDOWN));
	if(processor)
	{
		/*设置跟踪的processor*/
		ulReg |= (processor<<25);   
	}
	writel(ulReg, ETM_ETMCR(etm_base));
	writel(0x6F, ETM_ETMTRIGGER(etm_base));
	writel(0x0, ETM_ETMTSSCR(etm_base));
	writel(0x6F, ETM_ETMTEEVR(etm_base));
	REG_CLEAR_BIT(ETM_ETMSR(etm_base),BIT(3));
	writel(0x1000000, ETM_ETMTECR1(etm_base));
	writel(0x01, ETM_ETMTRACEIDR(etm_base)); 

	REG_SET_BIT(ETM_SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR, 6);
	REG_SET_BIT(ETM_ETMCR(etm_base), ETMCR_TIMESTAMPENABLE); 
	/****设置计数器0触发****/
	writel(0x40, ETM_ETMTSEVR(etm_base));
	set_etm_counter(etm_base);
	
	/****end program bit****/
	count = TIMEOUT;
	REG_CLEAR_BIT(ETM_ETMCR(etm_base), ETMCR_PROGBIT);
	while(REG_TEST_BIT(ETM_ETMSR(etm_base), ETMSR_PROGBIT) && --count);
	if(!count)
	{
		printk(KERN_ERR "[ETB] Waiting for progbit to assert timed out(enable2).\n");
		etm_lock(etm_base);
		return -1; 
	}		
	etm_lock(etm_base);
	printk(KERN_INFO "[ETB] Etm enable...\n");
	return 0;
}

/************************************************
功能:唤醒使能ETM 组件
*************************************************/
static int enable_etm_resume(struct platform_device *pdev)
{
	unsigned char processor = 0;
	int ret = 0;
	
    /*读取备份初始化配置*/
    	if(!(etm_srigster & BIT(10)))
    	{
        	processor = ((etm_srigster >> 24) & 0x07);
    	}
    	else
    	{
        	printk(KERN_INFO "[ETB]no config etb for acpu. \r\n");
        	return 0;
    	}
	/*acpu ETM配置*/
	printk(KERN_INFO "[ETB] Set ETB begin.\r\n");
	ret = config_etm(processor, etm_base_acpu);
	printk(KERN_INFO "[ETB] Acpu etb enable acpu%d!\r\n",processor);
	if (ret)
	{
		printk(KERN_ERR "[ETB] Acpu etb enable fail!!\r\n");
	}
	return ret;
}

/************************************************
功能:disabel etm 组件
*************************************************/
static int enable_etm_suspend(struct platform_device *pdev, pm_message_t state)
{
	int count = TIMEOUT;
	if((etm_srigster & BIT(10)))
      {
        	printk(KERN_INFO "[ETB]no config etb for acpu. \r\n");
        	return 0;
    	}
	/*acpu已配置*/
	printk(KERN_INFO "[ETB] disable ETB begin...\r\n");
	etm_unlock(etm_base_acpu);
	REG_SET_BIT(ETM_ETMCR(etm_base_acpu), ETMCR_PROGBIT);
	while(!REG_TEST_BIT(ETM_ETMSR(etm_base_acpu), ETMSR_PROGBIT) && --count);
	if(!count)
	{
		printk(KERN_ERR "[ETB] ETB disable failed!\n");
		etm_lock(etm_base_acpu);
		return -1; 
	}
	
	writel((0x6F|BIT(14)), ETM_ETMTEEVR(etm_base_acpu));

	/*disable etm clock/power*/
	REG_SET_BIT(ETM_ETMCR(etm_base_acpu), ETMCR_POWERDOWN);
	printk(KERN_INFO "[ETB] disable ETB end.\r\n");
	etm_lock(etm_base_acpu);

	return 0;
}

static int enable_etm_probe(struct platform_device *pdev)
{	
	struct device *dev = &pdev->dev;
	struct etb_platform_data *platform_data;

	int ret = 0;

	platform_data = (struct etb_platform_data *)dev->platform_data;
	
	if (NULL == platform_data)
	{
        	dev_err(dev, "enable_etm_probe failed\r\n");
		ret = -EBUSY;
		goto err_free;
   	}
	if(!request_mem_region( platform_data->iobase, platform_data->size, "etb"))
	{
		ret = -EBUSY;
		goto request_mem_fail;
	}
	etm_base_acpu = ioremap(platform_data->iobase, platform_data->size);
	if(NULL == etm_base_acpu)
	{
		ret = -EIO;
		printk(KERN_ERR "[ETM] etm remap failed!\r\n");
		goto etm_iomap_fail;
	}

	etm_srigster = readl(ETM_ETMCR(etm_base_acpu));
	return ret;
	
etm_iomap_fail:
	iounmap(etm_base_acpu);
	release_mem_region(platform_data->iobase, platform_data->size);
		
request_mem_fail:
err_free:
	return ret;

}

/************************************************
功能:读取NV 项---c核单独复位
*************************************************/
void  etb_nve_read(unsigned char *config)
{
	struct nve_info_user info_user;
	int ret = 0;
	info_user.nv_operation = NV_READ;
	info_user.nv_number = ETB_NVE_NUMBER;
	info_user.valid_size = 8;

	memset(info_user.nv_data, 0x0, 8);
	ret = nve_direct_access(&info_user);
	if(ret == -1)
	{
        printk(KERN_ERR "[ETM-ccpu_reset] config_info read failed!\r\n");
        strncpy(config, "00001000", 8);
	}
	else
	{
		strncpy(config, info_user.nv_data, 8);
	}
	return ;
}

/************************************************
功能:c核单独复位重新配置
*************************************************/
void  enable_etm_reset(void)
{
	unsigned int ccpu_etm_base = (CCPU_BASE + ETM_BASE);
	unsigned int size = 0x1000;
	char config[8] = {0};
	static void __iomem *etm_base_ccpu = NULL;
	int ret;
	etm_base_ccpu = ioremap(ccpu_etm_base, size);	
	if(NULL == etm_base_ccpu)
	{
		ret = -EIO;
		printk(KERN_ERR "[ETM-ccpu_reset] etm ioremap failed!\r\n");
		goto etm_iomap_fail;
	}
	etb_nve_read(config);
	if('1' == *config)
	{
		printk(KERN_INFO "[ETM-ccpu_reset] Set Ccpu ETM.\r\n");
		ret = config_etm(0, etm_base_ccpu);
		if (ret)
		{
			printk(KERN_ERR "[ETM-ccpu_reset] Ccpu ETM enable failed!!\r\n");
		}
    }
    else
    {
        printk(KERN_INFO "[ETM-ccpu_reset] not config Ccpu ETM.\r\n");
    }
etm_iomap_fail:
	iounmap(etm_base_ccpu);

	return ;
}

/* Description : platform driver definition*/
static struct platform_driver enable_etb_driver = {		
	.probe = enable_etm_probe,
	.suspend = enable_etm_suspend, 	
	.resume = enable_etm_resume, 	
	.driver ={		
		.owner = THIS_MODULE,		
		.name = "etb",	
	},
};

static int __init enable_etb_init(void)
{
	return platform_driver_register(&enable_etb_driver);	
}

static void __exit enable_etb_exit(void)
{
	platform_driver_unregister(&enable_etb_driver);
	return;
}

module_init(enable_etb_init);
module_exit(enable_etb_exit);

MODULE_DESCRIPTION("enable the etb function.");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("l00189326");

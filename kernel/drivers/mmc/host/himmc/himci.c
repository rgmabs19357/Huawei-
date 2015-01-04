/*
 * himci.c - hisilicon MMC Host driver
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <asm/cacheflush.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mshci.h>
#include <linux/gpio.h>

#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/switch.h>

#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <linux/workqueue.h>
#include <linux/wakelock.h>
#include <linux/freezer.h>
#include <asm/dma.h>
#include <linux/io.h>
#include <mach/irqs.h>
#include <mach/mmc.h>
#include <linux/clk.h>
#include <asm/sizes.h>
#include <linux/uaccess.h>
#include <linux/dma-mapping.h>
#include <mach/hardware.h>
#include <linux/mux.h>
#include <mach/boardid.h>

#include <mach/early-debug.h>
#include <mach/gpio.h>
#include <linux/regulator/consumer.h>
#include <asm/irq.h>
/* used for enable phase shifting */
#include "reg_ops.h"
#include <mach/platform.h>
#include <soc_sctrl_interface.h>

#include "himci.h"
#include <linux/mux.h>
#include <mach/pmussi_drv.h>

#include <hsad/config_mgr.h>
#include <linux/notifier.h>

/* parameters */
int trace_level = HIMCI_TRACE_LEVEL; /* 5 - the highest trace level */

/*当read、massread操作时发包使用*/
struct semaphore     sem_to_rfile_sync_req;

#define SD_CLK_PIN "ag2"


extern int emmc_sem_flag;
extern struct mutex emmc_mutex;
extern unsigned int g_ulmmc_suspend_flag;

#ifdef SD_FPGA_GPIO
#define GPIO_CD_DATA(__X__)	(*((unsigned volatile*)(__X__ + 0x200)))
#define GPIO_CD_DIR(__X__)	(*((unsigned volatile*)(__X__ + 0x400)))
#define GPIO_CD_IS(__X__)	(*((unsigned volatile*)(__X__ + 0x404)))
#define GPIO_CD_IBE(__X__)	(*((unsigned volatile*)(__X__ + 0x408)))
#define GPIO_CD_IE(__X__)	(*((unsigned volatile*)(__X__ + 0x410)))
#define GPIO_CD_RIS(__X__)	(*((unsigned volatile*)(__X__ + 0x414)))
#define GPIO_CD_IC(__X__)	(*((unsigned volatile*)(__X__ + 0x41C)))
#endif

#ifdef MODULE
module_param(trace_level, int, 0600);
MODULE_PARM_DESC(trace_level, "HIMCI_TRACE_LEVEL");
#endif



/*通过xml硬件配置项获取sdcard 时钟信息*/
unsigned int g_sdcard_frequency = 0;

extern struct mmc_host *g_host;

#if 0
/* IOMG addr for SD */
#define    IOMG_047	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x0BC)
#define    IOMG_048	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x0C0)

/* IOCG addr for SD */
#define    IOCG_107	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x98C)
#define    IOCG_108	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x990)
#define    IOCG_109	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x994)
#define    IOCG_110	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x998)
#define    IOCG_111	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x99C)
#define    IOCG_112	   (IO_ADDRESS(REG_BASE_IOC_OFF) + 0x9A0)

void dump_hw_info()
{
	printk(KERN_ERR ": ===========================================\n");

	printk(KERN_ERR " IOMG_047: 0 == %d\n", readl(IOMG_047));
	printk(KERN_ERR " IOMG_048: 0 == %d\n", readl(IOMG_048));

	printk(KERN_ERR " IOCG_107: 0x30 == 0x%x\n", readl(IOCG_107));
	printk(KERN_ERR " IOCG_108: 0x31 == 0x%x\n", readl(IOCG_108));
	printk(KERN_ERR " IOCG_109: 0x31 == 0x%x\n", readl(IOCG_109));
	printk(KERN_ERR " IOCG_110: 0x31 == 0x%x\n", readl(IOCG_110));
	printk(KERN_ERR " IOCG_111: 0x31 == 0x%x\n", readl(IOCG_111));
	printk(KERN_ERR " IOCG_112: 0x31 == 0x%x\n", readl(IOCG_112));

	printk(KERN_ERR ": -------------------------------------------\n");
}
#endif

static void mshci_sd_lowpower(void)
{
    /* used for sd card low power  */
  
    int ret;
    int gpio_val;

    ret = get_hw_config_int("sd_card/sdcard_clk_pin", &gpio_val, NULL);
    if (false == ret) {
        printk("sdcard_clk_pin value not found !\n");
        gpio_val = GPIO_8_2;
    }

    ret = gpio_request(gpio_val,"SD_CLK");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    ++gpio_val;

    ret = gpio_request(gpio_val,"SD_CMD");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    ++gpio_val;

    ret = gpio_request(gpio_val,"SD_DATA0");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    ++gpio_val;

    ret = gpio_request(gpio_val,"SD_DATA1");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    ++gpio_val;

    ret = gpio_request(gpio_val,"SD_DATA2");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    ++gpio_val;

    ret = gpio_request(gpio_val,"SD_DATA3");
    if (ret < 0){
        printk("GPIO request failed\n");
    }
    gpio_direction_output(gpio_val, 0);
    gpio_free(gpio_val);
    gpio_free(--gpio_val);
    gpio_free(--gpio_val);
    gpio_free(--gpio_val);
    gpio_free(--gpio_val);
    gpio_free(--gpio_val);
}

/*NOT called by VIA*/
static void mshci_sd_power_onoff(struct mshci_host *ms_host,int ispowerup)
{
    struct himci_host * hi_host = (struct himci_host *)(ms_host->private);
    int ret = 0;

    if (ispowerup){

        udelay(30);
        if (hi_host->signal_vcc){
            ret = regulator_enable(hi_host->signal_vcc);
            if (ret) {
               himci_error("failed to regulator_enable");
            }
        }
        udelay(30);
        if (hi_host->vcc_lvs){
            ret = regulator_enable(hi_host->vcc_lvs);
            if (ret) {
               himci_error("failed to regulator_enable");
            }
        }

        if (hi_host->vcc_ldo) {
            ret = regulator_set_voltage(hi_host->vcc_ldo, SDMMC_SDCARD_285, SDMMC_SDCARD_285);
            if (ret != 0) {
                himci_error("failed to LDO10 regulator_set_voltage 2.85 \n");
            }
        }
        if (hi_host->vcc_ldo){
            ret = regulator_enable(hi_host->vcc_ldo);
            if (ret) {
                himci_error("failed to regulator_enable");
            }
        }
        ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
		if (ret) {
		    himci_error("failed to blockmux_set");
		}
    }
    else{
        ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, LOWPOWER);
		if (ret) {
		    himci_error("failed to blockmux_set");
		}
        mshci_sd_lowpower();
		if (hi_host->vcc_ldo){
            ret = regulator_disable(hi_host->vcc_ldo);
            if (ret) {
                himci_error("failed to regulator_disable LDO10");
            }
        }
        if (hi_host->vcc_lvs){
            ret = regulator_disable(hi_host->vcc_lvs);
            if (ret) {
               himci_error("failed to regulator_disable LDO7");
            }
        }
        udelay(30);
        if (hi_host->signal_vcc){
            ret = regulator_disable(hi_host->signal_vcc);
            if (ret) {
               himci_error("failed to regulator_disable LDO22");
            }
        }
    }
}


static irqreturn_t mshci_hi_card_detect_gpio(int irq, void *data)
{
	struct mshci_host *ms_host = (struct mshci_host *)data;
	struct himci_host *hi_host = (struct himci_host *)(ms_host->private);

#ifdef SD_FPGA_GPIO
#if 0
	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "y00145322: CD Interrupt 0x%x\n",
					GPIO_CD_RIS(hi_host->gpioaddr));
	GPIO_CD_IC(hi_host->gpioaddr) = SD_DET_GPIO;
#endif
#endif
	hi_host->ocp_flag = 0;

	tasklet_schedule(&ms_host->card_tasklet);
	return IRQ_HANDLED;
};

unsigned int mshci_hi_get_present_status(struct mshci_host *ms_host)
{
	struct himci_host * hi_host = (struct himci_host *)(ms_host->private);
	unsigned int status;

	unsigned int sdcard_flag;  /* 1 means support sd card */
	unsigned int present_flag; /* 1 means high vol is present, 0 means low vol is present */
	int ret;

	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		if (ms_host->flags & MSHCI_DEVICE_DEAD)
			return 1;
		else
			return 0;
	} else if (ms_host->quirks & MSHCI_QUIRK_EXTERNAL_CARD_DETECTION) {
		status |= hi_host->ocp_flag;
		/* GPIO Low mean SD Card insert; ASIC IS opposite*/
#ifdef CONFIG_MACH_HI6620SFT
		status = gpio_get_value(hi_host->plat->cd_gpio);
#endif
#ifdef CONFIG_MACH_HI6620OEM

		/* support sd card? */
		ret = get_hw_config_int("sd_card/sdcard_support", &sdcard_flag, NULL);
		if ((0 == ret) || (0 == sdcard_flag)) {
			printk("%s : sd card is not supported\n", __FUNCTION__);
			status = 1;
		} else {
			/* 获取sd card在位电平 */
			ret = get_hw_config_int("sd_card/present_voltage", &present_flag, NULL);
			if (0 == ret) {
				printk("%s : get_hw_config sd_card/sdcard_voltage failed\n", __FUNCTION__);
				return 1;
			}
			/* 检测gpio电压 */
			if (1 == present_flag) {
				status = !gpio_get_value(hi_host->plat->cd_gpio);
			} else {
				status = gpio_get_value(hi_host->plat->cd_gpio);
			}
		}

#endif
		return status;
	} else {
		return 0;
	}
}


static int mshci_hi_set_clk_rate(struct mshci_host *ms_host, unsigned int clock)
{
    int ret;
    unsigned int wifi_clock_val = 50000000;

    if (MMC_CCLK_MAX_150M == clock){/* hs200 need to set dsppll clock 300M */
        ret = clk_set_rate( ms_host->clk_mmc_high, MMC_CCLK_MAX_300M );
    }
    else{
        ret = clk_set_rate( ms_host->clk_mmc_high, 2*MMC_CCLK_MAX_100M );
    }
    if (ret) {
        printk("Unable to set clock to the suited rate\n");
        return ret;	
    }
    if ((ms_host->hw_mmc_id == 1)&&(ms_host->quirks & MSHCI_QUIRK_CBP_DETECTION)){
	 ret = clk_set_rate( ms_host->clk_mmc_high, 240*1000*1000 );
        clock = 48*1000*1000;
    }

    if (ms_host->hw_mmc_id == 2){
        ret = get_hw_config_int("wifi/wifi_clock", &wifi_clock_val, NULL);
        if (false == ret) {
            printk(KERN_ERR "Error to find wifi_clock_val !\n");
        }
        clock = wifi_clock_val;
    }
    return clk_set_rate( ms_host->pclk, clock );
}

/* set host timing config */
static int mshci_hi_set_timing(struct mshci_host *ms_host, int timing)
{
	struct himci_host * hi_host = (struct himci_host *)(ms_host->private);
	int cbp_flag = 0;
	int ret = 0;

    if (ms_host->mmc->ios.timing == hi_host->old_timing){
        return ;
    } else {
        hi_host->old_timing = ms_host->mmc->ios.timing;
    }

    ms_host->tuning_needed = false;
    ms_host->tuning_done = false;

	ret = get_hw_config_int("modem/viacbp82d", &cbp_flag, NULL);
	if ((!ret) || (0 == cbp_flag)) {
		pr_info("%s has no cbp support\n", __func__);
	}

	if  ((1 == hi_host->pdev->id)&&(cbp_flag))
	{
		ms_host->mmc->ios.timing = 0;
		return mshci_hi_set_clk_rate(ms_host, 24*1000*1000);
	}
    
    switch (ms_host->mmc->ios.timing){
    case MMC_TIMING_LEGACY:
         return mshci_hi_set_clk_rate(ms_host, MMC_CCLK_MAX_25M);
    case MMC_TIMING_MMC_HS:
    case MMC_TIMING_UHS_SDR25:
         return mshci_hi_set_clk_rate(ms_host, MMC_CCLK_MAX_50M);
    case MMC_TIMING_UHS_DDR50:
         if (0 == hi_host->pdev->id){
            return mshci_hi_set_clk_rate(ms_host, MMC_CCLK_MAX_100M);
         } else {
            return mshci_hi_set_clk_rate(ms_host, MMC_CCLK_MAX_50M);
         }
    case MMC_TIMING_MMC_HS200:
         ms_host->tuning_needed = true;
         return mshci_hi_set_clk_rate(ms_host, MMC_CCLK_MAX_150M);
    case MMC_TIMING_UHS_SDR50:
         return mshci_hi_set_clk_rate(ms_host, g_sdcard_frequency*1000*1000);
    default:
         printk(KERN_ERR "error the timing we can not support \n");

    }
}

void mshci_hi_set_ios(struct mshci_host *ms_host, struct mmc_ios *ios)
{
	struct himci_host * hi_host = (struct himci_host *)(ms_host->private);
	int ret = -1;
	int cbp_flag = 0;

	hi_host_trace(HIMCI_TRACE_GEN_API, "++");

	himci_assert(ios);
	himci_assert(hi_host);

	hi_host_trace(HIMCI_TRACE_GEN_INFO, "ios->power_mode = %d ", ios->power_mode);
	hi_host_trace(HIMCI_TRACE_GEN_INFO, "ios->clock = %d ", ios->clock);
	hi_host_trace(HIMCI_TRACE_GEN_INFO, "ios->bus_width = %d ", ios->bus_width);
	hi_host_trace(HIMCI_TRACE_GEN_INFO, "ios->timing = %d ", ios->timing);

	ret = get_hw_config_int("modem/viacbp82d", &cbp_flag, NULL);
	if ((!ret) || (0 == cbp_flag)) {
		pr_info("%s has no cbp support\n", __func__);
	}

	pr_info("%s mode %d\n", __func__, ios->power_mode);

	/* process power */
	if (hi_host->old_power_mode != ios->power_mode) {
		switch (ios->power_mode) {
		case MMC_POWER_OFF:
			if ((!cbp_flag)&&(1 == ms_host->hw_mmc_id)){
				mshci_sd_power_onoff(ms_host, 0);
				break;
			}
			hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "set io to lowpower");
			if (hi_host->piomux_block && hi_host->pblock_config){
				ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, LOWPOWER);
					if (ret) {
						himci_error("failed to blockmux_set");
					}
			}

			if (hi_host->vcc_lvs){
				ret = regulator_disable(hi_host->vcc_lvs);
				if (ret) {
					himci_error("failed to regulator_enable");
				}
			}

			if (hi_host->vcc_ldo){
				ret = regulator_disable(hi_host->vcc_ldo);
				if (ret) {
					himci_error("failed to regulator_enable");
				}
			}
			break;
		case MMC_POWER_UP:

			hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "set io to normal");
			if ((!cbp_flag)&&(1 == ms_host->hw_mmc_id)){
				mshci_sd_power_onoff(ms_host, 1);
				break;
			}
			if (hi_host->vcc_ldo){
				ret = regulator_enable(hi_host->vcc_ldo);
				if (ret) {
					himci_error("failed to regulator_enable");
				}
			}
			if((1 == hi_host->ms_host->hw_mmc_id)&&(cbp_flag)){
				/*cbp need set as fixed 1.8v*/
				himci_error("sdio regulator_set_voltage 1.8 \n");
				if (hi_host->vcc_lvs) {
					ret = regulator_set_voltage(hi_host->vcc_lvs, SDMMC_1V8_IO_LDO7_180, SDMMC_1V8_IO_LDO7_180);
					if (ret != 0) {
						himci_error("failed to LDO7 regulator_set_voltage 1.8 \n");
					}
				}
			}
            if (hi_host->vcc_lvs){
                    ret = regulator_enable(hi_host->vcc_lvs);
                if (ret) {
                    himci_error("failed to regulator_enable");
                }
            }
            

            if (hi_host->piomux_block && hi_host->pblock_config){
                ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
                if (ret) {
                    himci_error("failed to blockmux_set");
                }
            }
			break;
		case MMC_POWER_ON:
			break;
		default:
			himci_error("unknown power supply mode");
			break;
		}
		hi_host->old_power_mode = ios->power_mode;
	}

	hi_host_trace(HIMCI_TRACE_GEN_API, "--");
}

static unsigned int mshci_hi_get_max_clk(struct mshci_host *ms_host)
{

#ifdef CONFIG_MACH_HI6620SFT
    return MMC_CCLK_MAX_30M;/*get the clock*/
#else
    return clk_get_rate( ms_host->pclk );/*get the clock*/
#endif
}



static int mshci_hi_start_signal_voltage_switch(struct mshci_host *ms_host,
				struct mmc_ios *ios)
{
#if 1
	struct himci_host *hi_host = (struct himci_host *)(ms_host->private);
	int ret =0;




if (ms_host->quirks & MSHCI_QUIRK_EXTERNAL_CARD_DETECTION) {

	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "++");

	himci_assert(ios);
	himci_assert(hi_host);

	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "old_sig_voltage = %d ",
					hi_host->old_sig_voltage);
	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "new_sig_voltage = %d ",
					ios->signal_voltage);
	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "allow_switch_signal_voltage = %d ",
					hi_host->allow_switch_signal_voltage);

	if (hi_host->allow_switch_signal_voltage &&
		(hi_host->old_sig_voltage != ios->signal_voltage)) {
		switch (ios->signal_voltage) {
		case MMC_SIGNAL_VOLTAGE_330:
#ifdef CONFIG_MACH_HI6620OEM

            printk("yuandan 330 \n");

            hi_host->old_sig_voltage = ios->signal_voltage;

            /*
            3.3V IO 设置
            LDO7   2.85V
            LDO22  1.425V
            */

		    if (hi_host->vcc_lvs) {
				ret = regulator_set_voltage(hi_host->vcc_lvs, SDMMC_3V3_IO_LDO7_285, SDMMC_3V3_IO_LDO7_285);
				if (ret != 0) {
					himci_error("failed to LDO7 regulator_set_voltage 3.3 \n");
				}
		    }
		    if(ms_host->quirks & MSHCI_QUIRK_EXTERNAL_CARD_DETECTION){
			    pmussi_reg_write(0x36,0x8);
		    }

#endif
			break;
		case MMC_SIGNAL_VOLTAGE_180:
#ifdef CONFIG_MACH_HI6620OEM
            printk("yuandan 180 \n");

			hi_host->old_sig_voltage = ios->signal_voltage;

            /*
            1.8V IO 设置
            LDO7   1.8V
            LDO22  0V
            */

		    if (hi_host->vcc_lvs) {
				ret = regulator_set_voltage(hi_host->vcc_lvs, SDMMC_1V8_IO_LDO7_180, SDMMC_1V8_IO_LDO7_180);
				if (ret != 0) {
					himci_error("failed to LDO7 regulator_set_voltage 1.8 \n");
				}
		    }
            if(ms_host->quirks & MSHCI_QUIRK_EXTERNAL_CARD_DETECTION){
                pmussi_reg_write(0xd2, 0x07);/* DR1 current control */
                pmussi_reg_write(0xd5, 0x07);/* DR2 current control */
                pmussi_reg_write(0xcf, 0x11);/* Turn on DR1 DR2 */
                pmussi_reg_write(0x37,0x8);
            }

			/* update time config*/
#endif
			break;

		case MMC_SIGNAL_VOLTAGE_120:
			/* FIXME */
			/* 1.20v is not support */
			himci_error("1.20V is not supported");
			break;
		default:
			himci_error("unknown signal voltage");
			break;
		}
	}

	hi_host_trace(HIMCI_TRACE_SIGNIFICANT, "--");

}
#endif

	return 0;
}

static int mshci_enable_tuning(struct mshci_host *host, int enable)
{
    int ret;

    if (enable){
        phy_reg_writel(REG_BASE_SC_OFF,
            SOC_SCTRL_SC_PERIPH_CTRL2_ADDR(CALC_REG_OFFSET),
            SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_START,
            SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_END, 0);
        ret = clk_enable(host->clk_mmc_high);
        if (ret) {
            printk("%s:failed to enable clock \n", __func__);
            return ret;		
        }
    }
    else{
       /*disable tuning*/
       phy_reg_writel(REG_BASE_SC_OFF,
            SOC_SCTRL_SC_PERIPH_CTRL2_ADDR(CALC_REG_OFFSET),
            SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_START,
            SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_END, 1);
       clk_disable(host->clk_mmc_high);
    }
    return 0;
}

static struct mshci_ops mshci_hi_ops = {
	.get_max_clock		= mshci_hi_get_max_clk,
	.get_min_clock		= NULL,
	.get_present_status = mshci_hi_get_present_status,  /* return: 0 -- present; 1 -- not present */
	.set_ios			= mshci_hi_set_ios,
	.start_signal_voltage_switch
						= mshci_hi_start_signal_voltage_switch,
	.set_clock		    = mshci_hi_set_clk_rate,
	.set_timing_state    = mshci_hi_set_timing,
	.tuning_state_enable = mshci_enable_tuning,
};

static void mshci_hi_notify_change(struct platform_device *dev, int state)
{
	struct mshci_host *host = platform_get_drvdata(dev);
	unsigned long flags;

	if (host) {
		spin_lock_irqsave(&host->lock, flags);
		if (state) {
			dev_info(&dev->dev, "card inserted.\n");
			host->flags &= ~MSHCI_DEVICE_DEAD;
		} else {
			dev_info(&dev->dev, "card removed.\n");
			host->flags |= MSHCI_DEVICE_DEAD;
		}
		tasklet_schedule(&host->card_tasklet);
		spin_unlock_irqrestore(&host->lock, flags);
	}
}
static void mshci_hi_sdio_set_power(struct platform_device *dev, int val)
{
	struct mshci_host *host = platform_get_drvdata(dev);
	struct himci_host * hi_host = (struct himci_host *)(host->private);
	/*int ret = -1;*/
	u32 loop_count = 1000; /* wait 10S */
	u32 i = 0;

	himci_assert(host);
	himci_assert(hi_host);

	for (i = 0; i < loop_count; i++) {
		if (MMC_HOST_BUSY == host->working || host->mrq) {
			msleep(10);
		} else {
			break;
		}
	}
#if 0
	if (val) {
		printk("%s:val=%d, set io to normal mode\n", __func__, val);
		host->mmc->ios.power_mode = MMC_POWER_UP;
		host->mmc->ios.timing = MMC_TIMING_LEGACY;
		host->mmc->ios.bus_width = MMC_BUS_WIDTH_1;
		host->mmc->ios.clock = 0;
		host->mmc->ops->set_ios(host->mmc, &host->mmc->ios);

		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
		if (ret) {
			himci_error("failed to blockmux_set");
		}
		msleep(10);

		host->mmc->ios.power_mode = MMC_POWER_ON;
		host->mmc->ios.clock = 400000;
		host->mmc->ops->set_ios(host->mmc, &host->mmc->ios);

		//to do w00215368
		//blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
	} else {
		printk("%s:val=%d, set io to lowpower mode\n", __func__, val);
		host->mmc->ios.clock = 0;
		host->mmc->ios.power_mode = MMC_POWER_OFF;
		host->mmc->ios.bus_width = MMC_BUS_WIDTH_1;
		host->mmc->ios.timing = MMC_TIMING_LEGACY;

		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, LOWPOWER);
		if (ret) {
			himci_error("failed to blockmux_set");
		}
	}
#endif
}


static int mshci_hi_disable_voltage(struct notifier_block *nb,
				    unsigned long event,
				    void *ignored)
{
	struct himci_host *hi_host = container_of(nb, struct himci_host, nb);
	struct mshci_host *ms_host = hi_host->ms_host;

	if ((event & REGULATOR_EVENT_FORCE_DISABLE) == REGULATOR_EVENT_FORCE_DISABLE) {
		hi_host->ocp_flag = 1;
		printk(KERN_ERR "%s ocp_flag = %d, event:0x%x\n", __func__, hi_host->ocp_flag, (int)event);
		tasklet_schedule(&ms_host->card_tasklet);
	}

	return NOTIFY_OK;
}

static int __devinit hi_mci_probe(struct platform_device *pdev)
{
	struct mshci_host *ms_host = NULL;
	struct himci_host *hi_host = NULL;
	struct hisik3_mmc_platform_data *plat = NULL;
	struct resource *memres = NULL;


	int ret = 0, irq;
	int err;
	bool RetVal = 0;
	unsigned long flags;
	unsigned int sdcard_frequency = 0;



    #ifdef CONFIG_MACH_HI6620OEM
    if(1 == pdev->id)
    {
        raw_mmc_turn_on();
    }
    #endif

	himci_trace(HIMCI_TRACE_GEN_API, "++");

	himci_assert(pdev);

	plat = pdev->dev.platform_data;

	himci_trace(HIMCI_TRACE_SIGNIFICANT, "id:%d", pdev->id);

    /*通过读取硬件配置项，或者sdcard时钟配置，只需要SD卡流程走，走一遍*/
    #ifdef CONFIG_MACH_HI6620OEM

    if(1 == pdev->id)
    {
        RetVal = get_hw_config_int("sd_card/sdcard_frequency", &sdcard_frequency, NULL);

    	printk("hsad: sd_card/sdcard_frequency = %d, RetVal = %d\n", sdcard_frequency, RetVal);

        /*读取失败，配置默认值*/
    	if (RetVal == false) {
            printk(KERN_ERR "get board type failed.\n");
            g_sdcard_frequency = 90;
    	}

        /*如果获取配置值异常，则配置默认值*/
    	if ((sdcard_frequency != 100)&&(sdcard_frequency != 90)) {
            printk(KERN_ERR "sdcard_frequency %x is error.\n",sdcard_frequency);
            g_sdcard_frequency = 90;
    	}

    	g_sdcard_frequency = sdcard_frequency;
	}

    #endif

	/* 获取自己定义的数据 */
	if (!plat) {
		himci_error("Platform data not available");
		return -ENOENT;
	}
	if(0 == pdev->id)
	{
	     sema_init(&sem_to_rfile_sync_req,0);
	}

    /*创建硬件信号量IPC_SEM_EMMC*/
    if (0 == pdev->id) {
        mutex_lock(&emmc_mutex);
        emmc_sem_flag = 1;
        mutex_unlock(&emmc_mutex);
    }

	irq = platform_get_irq(pdev, 0);
	memres = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	if ((!irq) || (!memres)) {
		himci_error("resource error");
		ret = -ENOENT;
        goto err_resource_get;
	}

	himci_trace(HIMCI_TRACE_SIGNIFICANT, "irq:%d,start:0x%x,size:0x%x", irq, \
										memres->start, resource_size(memres));

	ms_host = mshci_alloc_host(&pdev->dev, sizeof(struct himci_host));
	if (IS_ERR(ms_host)) {
		himci_error("mshci_alloc_host() failed\n");
		ret = PTR_ERR(ms_host);
        goto err_resource_get;
	}

	hi_host = mshci_priv(ms_host);
	hi_host->ms_host = ms_host;
	hi_host->pdev = pdev;
	hi_host->dev = &pdev->dev;
	hi_host->plat = plat;


	platform_set_drvdata(pdev, ms_host);

	/* MMC IP rstdis */
	if (plat->rstdis_mmc){
        ret = plat->rstdis_mmc();
        if ( ret < 0 ){
	        goto err_resource_get;
	    }
	}

    /* set emmc clk */

	hi_host->pclk = clk_get(&pdev->dev, plat->clk_mmc_low); /* work clk */

	if (IS_ERR(hi_host->pclk)) {
		himci_error("clk_get clk_mmc_low fail!");
		ret = PTR_ERR(hi_host->pclk);
		goto err_io_clk;
	}
	hi_host->clk_mmc_high= clk_get(&pdev->dev, plat->clk_mmc_high); /* highclk used for tuning */

    if (IS_ERR(hi_host->clk_mmc_high)) {
		himci_error("clk_get clk_mmc_high fail!");
		ret = PTR_ERR(hi_host->clk_mmc_high);
		goto err_io_clk;
	}

    ms_host->pclk = NULL;
    ms_host->clk_ref_counter = CLK_DISABLED;
    ms_host->clk_mmc_high = NULL;

	ms_host->pclk = hi_host->pclk;
	ms_host->clk_mmc_high = hi_host->clk_mmc_high;

	if (ret) {
	    himci_error("failed to clk_set_rate");
	}

    if(ms_host->clk_ref_counter == CLK_DISABLED){
        ret = clk_enable(hi_host->pclk);
        ms_host->clk_ref_counter = CLK_ENABLED;
        if (ret) {
            himci_error("clk_enable failed");
            ret = -ENOENT;
            goto err_clk_ops;
        }
    }



	ms_host->ioaddr = ioremap_nocache(memres->start, resource_size(memres));
	if (!ms_host->ioaddr) {
		himci_error("ioremap_nocache failed");
		ret = -ENXIO;
		goto err_req_regs;
	}

	ms_host->hw_name = "hisi_hi6620_mmc";
	ms_host->hw_mmc_id = hi_host->pdev->id;
	ms_host->ops = &mshci_hi_ops;
	ms_host->quirks = 0;
	ms_host->irq = irq;

	/* Setup quirks for the controller */

	if (plat->quirks) {
		ms_host->quirks |= plat->quirks;
	}

	if (plat->caps & MMC_CAP_CLOCK_GATING) {
		/* there is no reason not to use interral clock gating */
		ms_host->mmc->caps |= plat->caps;
		ms_host->mmc->caps |= MMC_CAP_CLOCK_GATING;
		ms_host->clock_gate = 1;
    } else {
		ms_host->mmc->caps |= plat->caps;
		ms_host->clock_gate = 0;
	}

	ms_host->mmc->caps2 = plat->caps2;

	/* sandisk card need clock longer than spec ask */
	/* sdcard also disable ip clock gate c00261379*/
	if (ms_host->hw_mmc_id == 0 || ms_host->hw_mmc_id == 1)
		ms_host->clock_gate = 0;

	if (plat->ocr_mask)
		ms_host->mmc->ocr_avail |= plat->ocr_mask;


    #ifdef CONFIG_MACH_HI6620OEM
    if (plat->iomux_name){
        hi_host->piomux_block = iomux_get_block(plat->iomux_name);
	    hi_host->pblock_config = iomux_get_blockconfig(plat->iomux_name);
    }

    /* todo requlator */
	if (plat->reg_name_ldo) {
		himci_trace(HIMCI_TRACE_SIGNIFICANT, "devname : %s, regname: %s",
					dev_name(hi_host->dev), plat->reg_name_ldo);
		hi_host->vcc_ldo = regulator_get(hi_host->dev, plat->reg_name_ldo);
		if (!IS_ERR(hi_host->vcc_ldo)) {
			/*
			 * Setup a notifier block to update this if another device
			 * causes the voltage to change
			 */
			hi_host->nb.notifier_call = &mshci_hi_disable_voltage;
			ret = regulator_register_notifier(hi_host->vcc_ldo, &hi_host->nb);
			if (ret) {
				dev_err(&pdev->dev,
					"regulator notifier request failed\n");
			}
		} else {
			dev_err(&pdev->dev, "regulator_get() failed\n");
			hi_host->vcc_ldo = NULL;
		}
	}

	if (plat->reg_name_lvs) {
		himci_trace(HIMCI_TRACE_SIGNIFICANT, "devname : %s, regname: %s",
					dev_name(hi_host->dev), plat->reg_name_lvs);
		hi_host->vcc_lvs = regulator_get(hi_host->dev, plat->reg_name_lvs);
		if (!IS_ERR(hi_host->vcc_lvs)) {
			/*
			 * Setup a notifier block to update this if another device
			 * causes the voltage to change
			 */
			hi_host->nb.notifier_call = &mshci_hi_disable_voltage;
			ret = regulator_register_notifier(hi_host->vcc_lvs, &hi_host->nb);
			if (ret) {
				dev_err(&pdev->dev,
					"regulator notifier request failed\n");
			}
		} else {
			dev_err(&pdev->dev, "regulator_get() failed\n");
			hi_host->vcc_lvs = NULL;
		}
	}
	hi_host->ocp_flag = 0;

	if (plat->signal_reg_name) {
		himci_trace(HIMCI_TRACE_SIGNIFICANT, "devname : %s, signal regname: %s",
						dev_name(hi_host->dev), plat->signal_reg_name);
		hi_host->signal_vcc = regulator_get(hi_host->dev, plat->signal_reg_name);
		if (IS_ERR(hi_host->signal_vcc)) {
			dev_err(&pdev->dev, "regulator_get() failed\n");
			hi_host->signal_vcc = NULL;
		}
	}
    #endif

	if( (1 == pdev->id)&&( (ms_host->quirks & MSHCI_QUIRK_CBP_DETECTION) == 0)) {
		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, LOWPOWER);
		if (ret) {
			himci_error("failed to blockmux_set");
		}
		mshci_sd_lowpower();
		if (hi_host->vcc_lvs){
			ret = regulator_enable(hi_host->vcc_lvs);
			if (ret) {
				himci_error("failed to regulator_enable LDO7");
			}
			ret = regulator_disable(hi_host->vcc_lvs);
			if (ret) {
			himci_error("failed to regulator_disable LDO7");
			}
		}
		udelay(30);
		if (hi_host->signal_vcc){
			ret = regulator_enable(hi_host->signal_vcc);
			if (ret) {
				himci_error("failed to regulator_enable LDO22");
			}
			ret = regulator_disable(hi_host->signal_vcc);
			if (ret) {
				himci_error("failed to regulator_disable LDO22");
			}
		}
	}else {/*for cbp*/
		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
		if (ret) {
			himci_error("failed to blockmux_set");
		}

		if (hi_host->vcc_lvs){
			ret = regulator_enable(hi_host->vcc_lvs);
			if (ret) {
				himci_error("failed to regulator_enable LDO7");
			}
		}
		udelay(30);
		if (hi_host->signal_vcc){
			ret = regulator_enable(hi_host->signal_vcc);
			if (ret) {
				himci_error("failed to regulator_enable LDO22");
			}

			ret = regulator_disable(hi_host->signal_vcc);
			if (ret) {
				himci_error("failed to regulator_disable LDO22");
			}
		}
	}

	hi_host->old_sig_voltage = plat->default_signal_voltage;
	hi_host->old_timing = MMC_TIMING_UHS_DDR50;
	hi_host->timing_config = plat->timing_config;
	hi_host->allow_switch_signal_voltage = plat->allow_switch_signal_voltage;
	hi_host->suspend_timing_config = plat->suspend_timing_config;

	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		ms_host->flags |= MSHCI_DEVICE_DEAD;
		ms_host->flags |= MMC_PM_KEEP_POWER;
		ms_host->mmc->pm_caps |= MMC_PM_KEEP_POWER;
	}

	ret = mshci_add_host(ms_host);
	if (ret) {
		dev_err(&pdev->dev, "mshci_add_host() failed\n");
		goto err_add_host;
	}

	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		ms_host->flags |= MSHCI_DEVICE_DEAD;
	        ms_host->flags |= MMC_PM_KEEP_POWER;
	        ms_host->mmc->pm_caps |= MMC_PM_KEEP_POWER;
		if (plat->ext_cd_init)
			plat->ext_cd_init(&mshci_hi_notify_change);
		plat->set_power = mshci_hi_sdio_set_power;
	}

	if( (1 == pdev->id)&&( (ms_host->quirks & MSHCI_QUIRK_CBP_DETECTION) != 0)) {
	        ms_host->flags |= MMC_PM_KEEP_POWER;
	        ms_host->mmc->pm_caps |= MMC_PM_KEEP_POWER;
	}


	if (ms_host->quirks & MSHCI_QUIRK_EXTERNAL_CARD_DETECTION) {

		err = gpio_request_one(plat->cd_gpio, GPIOF_IN, "ESDHC_CD");
		if (err) {
			dev_warn(mmc_dev(ms_host->mmc),
				"no card-detect pin available!\n");
			goto no_card_detect_pin;
		}
		/*SD_INT_FIX_suspend DTS:2013082704916 modifier: y00241633*/
		err = request_irq(gpio_to_irq(plat->cd_gpio), mshci_hi_card_detect_gpio,
				 IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND,
				 mmc_hostname(ms_host->mmc), ms_host);
		if (err) {
			dev_warn(mmc_dev(ms_host->mmc), "request gpio irq error\n");
			goto no_card_detect_irq;
		}

        if ( plat->sw_gpio ){
            /* only sft has this gpio */
		    err = gpio_request_one(plat->sw_gpio, 0, "ESDHC_POWER_SWITCH");
		    if (err) {
			    dev_warn(mmc_dev(ms_host->mmc),
				    "no card-power-switch pin available!\n");
			    goto no_card_power_switch_pin;
		    }

            /*控制I/O口电平 1V8 or 3V3*/
            gpio_direction_output(plat->sw_gpio, 1);
        }

	}

	return 0;

no_card_power_switch_pin:
	plat->sw_gpio = err;
no_card_detect_irq:
	gpio_free(plat->cd_gpio);
no_card_detect_pin:
	plat->cd_gpio = err;
err_add_host:
	iounmap(ms_host->ioaddr);
	ms_host->ioaddr = NULL;
err_req_regs:
	spin_lock_irqsave(&ms_host->lock, flags);
	if(ms_host->clk_ref_counter == CLK_ENABLED){
		clk_disable(hi_host->pclk);
		ms_host->clk_ref_counter = CLK_DISABLED;
	}
	spin_unlock_irqrestore(&ms_host->lock, flags);
err_clk_ops:
    clk_put(hi_host->clk_mmc_high);
	clk_put(hi_host->pclk);
err_io_clk:
	mshci_free_host(ms_host);

err_resource_get:

	return ret;
}

static int __devexit hi_mci_remove(struct platform_device *pdev)
{
	int ret;
	struct mshci_host *ms_host =  NULL;
	struct himci_host *hi_host = NULL;
	struct hisik3_mmc_platform_data *plat = NULL;
	unsigned long flags;

	ms_host =  platform_get_drvdata(pdev);
	if (!ms_host) {
		printk(KERN_ERR "get drvdata failed !\n");
		return -1;
	}
	hi_host = mshci_priv(ms_host);
	plat = pdev->dev.platform_data;

	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		if (plat->ext_cd_init)
			plat->ext_cd_cleanup(&mshci_hi_notify_change);
	}

	mshci_remove_host(ms_host, 1);

	iounmap(ms_host->ioaddr);
	ms_host->ioaddr = NULL;


	spin_lock_irqsave(&ms_host->lock, flags);
	if(ms_host->clk_ref_counter == CLK_ENABLED){
		clk_disable(hi_host->pclk);
		ms_host->clk_ref_counter = CLK_DISABLED;
	}
	spin_unlock_irqrestore(&ms_host->lock, flags);

	clk_put(hi_host->pclk);
	if (hi_host->vcc_ldo) {
		regulator_unregister_notifier(hi_host->vcc_ldo, &hi_host->nb);
		ret = regulator_disable(hi_host->vcc_ldo);
		if (ret) {
			printk("%s:failed to disable regulator\n", __func__);
			return ret;
		}
		regulator_put(hi_host->vcc_ldo);
	}
	if (hi_host->vcc_lvs) {
		regulator_unregister_notifier(hi_host->vcc_lvs, &hi_host->nb);
		ret = regulator_disable(hi_host->vcc_lvs);
		if (ret) {
			printk("%s:failed to disable regulator\n", __func__);
			return ret;
		}
		regulator_put(hi_host->vcc_lvs);
	}

	if (hi_host->signal_vcc) {
		regulator_put(hi_host->signal_vcc);
	}

	mshci_free_host(ms_host);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

#ifdef CONFIG_PM
volatile int cbp_clock_enabled = 0;
volatile int cbp_host_waked = 0;
volatile int cbp_in_sdio_tras = 1;
static int hi_mci_suspend(struct platform_device *dev, pm_message_t pm)
{

	struct mshci_host *ms_host = NULL;
	struct himci_host *hi_host = NULL;
	int ret = 0;
	unsigned long flags;
	int cbp_flag = 0;
	int cbp_ret = 0;

	ms_host = platform_get_drvdata(dev);
	if (!ms_host) {
		printk(KERN_ERR "get drvdata failed !\n");
		return -1;
	}
	hi_host = mshci_priv(ms_host);

    if(0 == hi_host->pdev->id)
    {
        g_ulmmc_suspend_flag = true;
        printk("hi_mci_suspend,set g_ulmmc_suspend_flag.");
    }

	cbp_ret = get_hw_config_int("modem/viacbp82d", &cbp_flag, NULL);
	if ((!cbp_ret) || (0 == cbp_flag)) {
		pr_info("%s has no cbp support\n", __func__);
	}

	if ((1 == hi_host->pdev->id)&&(cbp_flag)){
		if (ms_host->mmc->ios.power_mode != MMC_POWER_OFF) {
			pr_info("%s cbp ext suspend sdio\n", __func__);
			if (cbp_in_sdio_tras){
				pr_info("%s cbp_in_sdio_tras %d\n", __func__, cbp_in_sdio_tras);
				return -EAGAIN;
			}
			cbp_clock_enabled = 0;
			cbp_host_waked = 0;
			cbp_notifier_call_chain(0, NULL);

			ms_host->mmc->ios.power_mode = MMC_POWER_UP;
			ms_host->mmc->ios.clock = 0;
			ms_host->mmc->ops->set_ios(ms_host->mmc, &ms_host->mmc->ios);
		}
		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, LOWPOWER);
		if (ret) {
			himci_error("failed to blockmux_set");
		}
	}


	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		/* sdio power off */
		if (ms_host->mmc->ios.power_mode != MMC_POWER_OFF) {
			ret = mmc_sdio_suspend_ext(ms_host->mmc);
			if (ret) {
				printk("%s, sdio suspend error\n", __func__);
				return ret;
			}

			ms_host->mmc->ios.power_mode = MMC_POWER_UP;
			hi_host->old_timing = 0;
			hi_host->old_sig_voltage = 0;
		}
	}

    /*sd and emmc share the same suspend and resume*/
    mshci_suspend_host(ms_host, pm);

	spin_lock_irqsave(&ms_host->lock, flags);
	if(ms_host->clk_ref_counter == CLK_ENABLED){
		clk_disable(hi_host->pclk);
		ms_host->clk_ref_counter = CLK_DISABLED;
	}
	spin_unlock_irqrestore(&ms_host->lock, flags);


	return 0;
}

static int hi_mci_resume(struct platform_device *dev)
{
	int ret = 0;
	struct mshci_host *ms_host = NULL;
	struct himci_host *hi_host = NULL;   
	int cbp_flag = 0;
	int cbp_ret = 0;
	unsigned int oldclock = 0;

	ms_host = platform_get_drvdata(dev);
	if (!ms_host) {
		printk(KERN_WARNING "the return value of platform_get_drvdata is NULL !\n");
		return -1;
	}
	hi_host = mshci_priv(ms_host);

	cbp_ret = get_hw_config_int("modem/viacbp82d", &cbp_flag, NULL);
	if ((!cbp_ret) || (0 == cbp_flag)) {
		pr_info("%s has no cbp support\n", __func__);
	}

	if ((1 == hi_host->pdev->id)&&(cbp_flag)){
		ret = blockmux_set(hi_host->piomux_block, hi_host->pblock_config, NORMAL);
		if (ret) {
			himci_error("failed to blockmux_set");
		}
	}

	printk(KERN_INFO "hi_mci_resume is called \n");
	mshci_resume_host(ms_host);

	if (ms_host->quirks & MSHCI_QUIRK_WLAN_DETECTION) {
		if (ms_host->mmc->ios.power_mode != MMC_POWER_OFF) {
			ret = mmc_sdio_resume_ext(ms_host->mmc);
			if (ret) {
				printk("%s, sdio resume error\n", __func__);
				return ret;
			}
		}
	}

	if ((1 == hi_host->pdev->id)&&(cbp_flag)){
		if (ms_host->mmc->ios.power_mode != MMC_POWER_OFF) {
			pr_info("%s cbp resume sdio maxclock = %d, cur_clk=%d\n", __func__, ms_host->max_clk, ms_host->clock);
			ms_host->mmc->ios.clock = ms_host->mmc->f_max;
			ms_host->mmc->ops->set_ios(ms_host->mmc, &ms_host->mmc->ios);
			ms_host->mmc->ops->enable_sdio_irq(ms_host->mmc, 1);
		}
		cbp_host_waked = 1;
		cbp_notifier_call_chain(1, NULL);
	}

    if(0 == hi_host->pdev->id)
    {
        g_ulmmc_suspend_flag = false;
        /*emmc resume 完毕*/
        printk("mmc_blk_resume, clr g_ulmmc_suspend_flag.\n");
    }
	return ret;
}

#else
#define hi_mci_suspend  NULL
#define hi_mci_resume   NULL
#endif

static struct platform_driver hi_mci_driver = {
	.probe		= hi_mci_probe,
	.remove		= hi_mci_remove,
	.suspend	= hi_mci_suspend,
	.resume		= hi_mci_resume,
	.driver		= {
		.name	  = "hi_mci",
	},
};

static int __init hi_mci_init(void)
{
    return platform_driver_register(&hi_mci_driver);
}

static void __exit hi_mci_exit(void)
{
	platform_driver_unregister(&hi_mci_driver);
}


module_init(hi_mci_init);
module_exit(hi_mci_exit);

#ifdef MODULE
MODULE_AUTHOR("Hisilicon Driver Group");
MODULE_DESCRIPTION("MMC/SD driver for the Hisilicon MMC/SD Host Controller");
MODULE_LICENSE("GPL");
#endif

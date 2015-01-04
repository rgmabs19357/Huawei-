/*******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 *******************************************************************************
  文 件 名   : dev_spi.c
  版 本 号   : 初稿
  作    者   : 张彪 zkf67996
  生成日期   : 2012年8月9日
  最近修改   :
  功能描述   : header
  修改历史   :
  1.日    期   : 2012年8月9日
    作    者   : 张彪 zkf67996
    修改内容   : 创建文件

*******************************************************************************/

/*******************************************************************************
  1 头文件包含
*******************************************************************************/
#include <mach/early-debug.h>
#include <linux/spi/spi.h>
#include <linux/amba/bus.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <linux/amba/pl022.h>
#include <linux/mux.h>
#include <linux/delay.h>
#include "reg_ops.h"
#include <mach/platform.h>
#include "soc_ao_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"
#include <mach/gpio.h>
#include <mach/dma.h>


#define SPI_RESET_CONTROLLER_TIMEOUT	(10)

#define MINI_ISP_SPI_CS_GPIO		(GPIO_14_2)
#define MINI_ISP_IRQ_GPIO			(GPIO_6_3)
#define MINI_ISP_RESET_GPIO			(GPIO_14_6)
#define MINI_ISP_POWER_GPIO			(GPIO_14_5)

struct mini_isp_plat_data {
	int spi_cs_gpio;
	int irq_gpio;
	int reset_gpio;
	int power_gpio;
};

static struct mini_isp_plat_data misp_plat_info = {
	.spi_cs_gpio = MINI_ISP_SPI_CS_GPIO,
	.irq_gpio    = MINI_ISP_IRQ_GPIO,
	.reset_gpio  = MINI_ISP_RESET_GPIO,
	.power_gpio  = MINI_ISP_POWER_GPIO,
};

static void ssp0_init(void)
{
	unsigned int ret;
	int timeout = SPI_RESET_CONTROLLER_TIMEOUT;

	//printk(KERN_INFO "%s enter\n", __func__);
	//phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(0),14,14,1);
	//phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(0),15,15,1);

	phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_RSTDIS1_ADDR(0),7, 7, 1);

	while (timeout--) {
		ret = phy_reg_readl(REG_BASE_SC_OFF, \
			SOC_SCTRL_SC_PERIPH_RSTSTAT1_ADDR(0), 7, 7);

		if (ret && (!timeout)) {
			printk(KERN_ERR "spi0 clock rst disable fail\n");
		} else if (!ret) {
			break;
		}
	}
}

static void ssp0_exit(void)
{
	unsigned int ret;
	int timeout = SPI_RESET_CONTROLLER_TIMEOUT;

	//printk(KERN_INFO "%s enter\n", __func__);
	//phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_CLKDIS1_ADDR(0),14,14,1);
	//phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_CLKDIS1_ADDR(0),15,15,1);

	phy_reg_writel(REG_BASE_SC_OFF,SOC_SCTRL_SC_PERIPH_RSTEN1_ADDR(0), 7, 7, 1);

	while (timeout--) {
		ret = phy_reg_readl(REG_BASE_SC_OFF, \
			SOC_SCTRL_SC_PERIPH_RSTSTAT1_ADDR(0), 7, 7);

		if ((!timeout) && (!ret)) {
			printk(KERN_ERR "spi0 clock rst enable fail\n");
		} else if (ret){
			break;
		}
	}
}

/*******************************************************************************
  2 全局变量定义
*******************************************************************************/

extern struct iomux_block *iomux_get_block(char *name);
extern struct block_config *iomux_get_blockconfig(char *name);
extern int blockmux_set(struct iomux_block *blockmux,
        	struct block_config *config, enum iomux_func newmode);

/****************************************************************************
#ifdef _DRV_LLT_
void common_block_set(char *block_name, enum iomux_func newmode);
#else
static void common_block_set(char *block_name, enum iomux_func newmode);
#endif
****************************************************************************/
static void hi6620_spidev0_cs_set(u32 control)
{
	int ret;

	//pr_info("%s: control = %s\n", __func__, (control==0)?"select":"diselect");

	if (SSP_CHIP_SELECT == control) {
		/* cs steup time at least 10ns */
		ndelay(20);
		ret = gpio_direction_output(MINI_ISP_SPI_CS_GPIO, control);
	} else {
		/* cs hold time at least 4*40ns(@25MHz) */
		ret = gpio_direction_output(MINI_ISP_SPI_CS_GPIO, control);
		ndelay(200);
	}

    if (ret < 0)
		pr_err("%s: fail to set gpio cs, result = %d.", __func__, ret);
}

static void hi6620_spidev1_cs_set(u32 control)
{

}


#define PL022_CONFIG_CHIP(id)						\
static struct pl022_config_chip spidev##id##_chip_info = {		\
	.com_mode 		= DMA_TRANSFER,				\
	.iface			= SSP_INTERFACE_MOTOROLA_SPI,         	\
	.hierarchy		= SSP_MASTER,				\
	.slave_tx_disable	= 0,					\
	.rx_lev_trig		= SSP_RX_16_OR_MORE_ELEM,		\
	.tx_lev_trig		= SSP_TX_64_OR_MORE_EMPTY_LOC,		\
	.ctrl_len		= SSP_BITS_8,				\
	.wait_state		= SSP_MWIRE_WAIT_ZERO,			\
	.duplex 		= SSP_MICROWIRE_CHANNEL_FULL_DUPLEX,	\
	.cs_control		= hi6620_spidev##id##_cs_set,         	                \
}

PL022_CONFIG_CHIP(0);
PL022_CONFIG_CHIP(1);

K3_DEF_DMA_PARAM(spi0_RX);
K3_DEF_DMA_PARAM(spi0_TX);

static struct pl022_ssp_controller spi_plat_data[] = {
	[0] = {
		.bus_id = 0,
		.num_chipselect = 1,
		.enable_dma = 1,
		.dma_filter = k3_def_dma_filter,
		.dma_rx_param = &K3_DMA_PARAM_NAME(spi0_RX),
		.dma_tx_param = &K3_DMA_PARAM_NAME(spi0_TX),
		.init = ssp0_init,
		.exit = ssp0_exit,
		.iomux_name = "block_spi0",
	},
	[1] = {
		.bus_id = 1,
		.num_chipselect = 1,
		.enable_dma = 0,
		.dma_filter = NULL,
		.dma_rx_param = NULL,
		.dma_tx_param = NULL,
		.init = NULL,
		.exit = NULL,
		.iomux_name = NULL,
	},
};

#ifdef _DRV_LLT_
#define AMBA_DEVICE(name, busid, base, plat)			\
 struct amba_device name##_device = {			\
	.dev		= {					\
		.coherent_dma_mask = ~0,			\
		.init_name = busid,				\
		.platform_data = plat,				\
	},							\
	.res		= {					\
		.start	= REG_BASE_##base,			\
		.end	= (REG_BASE_##base) + SZ_4K - 1,	\
		.flags	= IORESOURCE_MEM,			\
	},							\
	.dma_mask	= ~0,					\
	.irq		= { IRQ_##base, NO_IRQ },		\
}
#else
#define AMBA_DEVICE(name, busid, base, plat)			\
static struct amba_device name##_device = {			\
	.dev		= {					\
		.coherent_dma_mask = ~0,			\
		.init_name = busid,				\
		.platform_data = plat,				\
	},							\
	.res		= {					\
		.start	= REG_BASE_##base,			\
		.end	= (REG_BASE_##base) + SZ_4K - 1,	\
		.flags	= IORESOURCE_MEM,			\
	},							\
	.dma_mask	= ~0,					\
	.irq		= { IRQ_##base, NO_IRQ },		\
}
#endif

AMBA_DEVICE(spi0, "dev:ssp0", SSP0, &spi_plat_data[0]);
AMBA_DEVICE(spi1, "dev:ssp1", SSP1, &spi_plat_data[1]);

/*******************************************************************************
  4 函数实现
*******************************************************************************/
#if 0
#ifdef _DRV_LLT_
void common_block_set(char *block_name, enum iomux_func newmode)
#else
static void common_block_set(char *block_name, enum iomux_func newmode)
#endif
{
	struct iomux_block *block_tmp = NULL;
	struct block_config *config_tmp = NULL;
	int ret = -1;

	block_tmp = iomux_get_block(block_name);
	if (!block_tmp) {
		pr_err("%s: iomux_get_block(%s) error.\n",
			__func__, block_name);
		return;
	}

	config_tmp = iomux_get_blockconfig(block_name);
	if (!config_tmp) {
		pr_err("%s: iomux_get_blockconfig(%s) error.\n",
			__func__, block_name);
		return;
	}

	ret = blockmux_set(block_tmp, config_tmp, newmode);
	if (ret) {
		pr_err("%s: blockmux_set error.\n", __func__);
		return;
	}
	pr_info("%s:ssp0 iomux block config ok.\n", __func__);
}
#endif

/* spi_devs driver registration */
#ifdef _DRV_LLT_
int k3v2_spi_board_register(void)
#else
static int k3v2_spi_board_register(void)
#endif
{
	static struct spi_board_info info[] = {

#if 0
		[0] = {
			.modalias = "spi_dev",
			.max_speed_hz = 6000000,
			.bus_num = 0,
			.chip_select = 0,
			.controller_data = &spidev0_chip_info,
		},
#else
		[0] = {
			.modalias = "mini_isp",
			.max_speed_hz = 26000000,
			.bus_num = 0,
			.chip_select = 0,
			.irq = IRQ_GPIO(MINI_ISP_IRQ_GPIO),
			.platform_data =(void *) &misp_plat_info,
			.controller_data = &spidev0_chip_info,
		},
#endif
		[1] = {
			.modalias = "spi_dev",
			.max_speed_hz = 6000000,
			.bus_num = 1,
			.chip_select = 0,
			.controller_data = &spidev1_chip_info,
		},
	};

	return spi_register_board_info(info, ARRAY_SIZE(info));
}

#ifdef _DRV_LLT_
 struct amba_device *amba_spi_devs[]  = {
	&spi0_device,
    &spi1_device,
};
#else
static struct amba_device *amba_spi_devs[] __initdata = {
	&spi0_device,
       &spi1_device,
};
#endif

#ifdef _DRV_LLT_
static int  hisik3_spi_init(void)
#else
static int __init hisik3_spi_init(void)
#endif
{
	int i;
       int ret;

	edb_trace(1);

	ret = k3v2_spi_board_register();
	if(0!=ret)
	{
		printk(KERN_ERR "k3v2_spi_board_register failed  ret = %d.\n", ret);
	}

	for (i = 0; i < ARRAY_SIZE(amba_spi_devs); i++) {
		struct amba_device *d = amba_spi_devs[i];
		amba_device_register(d, &iomem_resource);
	}
	edb_trace(1);
    return 0;
}

arch_initcall(hisik3_spi_init);

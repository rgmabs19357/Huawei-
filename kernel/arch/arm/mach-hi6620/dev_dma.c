/*dma device declare and register*/
/*
 * Copyright (C) Hisilicon Technologies Co.,Ltd.
 *	k3<k3dma@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/platform_device.h>
#include <linux/clk.h>
#include <mach/dma.h>

static u64 k3_dma_mask = DMA_BIT_MASK(32);
static bool set_acp(bool on)
{
	void __iomem		*pctrl;
	if (!request_mem_region(REG_BASE_PCTRL, 4, DEVICE_NAME))
		return false;

	pctrl = ioremap(REG_BASE_PCTRL, 4);
	if (!pctrl) {
		release_mem_region(REG_BASE_PCTRL, 4);
		return false;
	}

	if (on)
		writel((1 << 22), pctrl);
	else
		writel((1 << 22) | (1 << 6), pctrl);

	iounmap(pctrl);
	release_mem_region(REG_BASE_PCTRL, 4);
	return true;
}

static bool set_clkgate(bool on)
{
	void __iomem		*pctrl;
	if (!request_mem_region(REG_BASE_PCTRL, 4, DEVICE_NAME))
		return false;

	pctrl = ioremap(REG_BASE_PCTRL, 4);
	if (!pctrl) {
		release_mem_region(REG_BASE_PCTRL, 4);
		return false;
	}

	if (on)
		writel((1 << 24), pctrl);
	else
		writel((1 << 24) | (1 << 8), pctrl);

	iounmap(pctrl);
	release_mem_region(REG_BASE_PCTRL, 4);
	return true;
}

static struct clk *get_clkacp(void)
{
	struct clk *clkacp = clk_get(NULL, "clk_acp");
	if (IS_ERR(clkacp))
		return NULL;

	return clkacp;
}

/*resources*/
static struct resource k3_dma_resources[] = {
	[0] = {
		.start	= REG_BASE_DMAC,
		.end	= REG_BASE_DMAC + REG_DMAC_IOSIZE - 1,
		.flags	= IORESOURCE_DMA,
	},
	[1] = {
		.start	= IRQ_DMAC_SEC,
		.end	= IRQ_DMAC_SEC,
		.flags	= IORESOURCE_IRQ,
	},
};

/* Do remember! The index of channel data should be the same with peri */
static struct k3dma_platform_data k3_dma_data = {
	.nr_phy_channels	= 16,
	.nr_slave_channels	= DMACH_NUMBER,
	.hasacp = false,
	.cd = {
		[0] = {
			.peri		= DMACH_spi0_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_SPI0_RX,
		},
		[1] = {
			.peri		= DMACH_spi0_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_SPI0_TX,
		},
		[4] = {
			.peri		= DMACH_uart1_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[5] = {
			.peri		= DMACH_uart1_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[6] = {
			.peri		= DMACH_uart2_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[7] = {
			.peri		= DMACH_uart2_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[8] = {
			.peri		= DMACH_uart3_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_UART3_RX,
		},
		[9] = {
			.peri		= DMACH_uart3_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_UART3_TX,
		},
		[10] = {
			.peri		= DMACH_uart4_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[11] = {
			.peri		= DMACH_uart4_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[12] = {
			.peri		= DMACH_uart5_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[13] = {
			.peri		= DMACH_uart5_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[28] = {
			.peri		= DMACH_spi1_RX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},
		[29] = {
			.peri		= DMACH_spi1_TX,
			.pri		= DMACH_PRIORITY_0,
			.phy_ch		= DMACH_PHY_INVALID,
		},

	},
	.acp_enable = set_acp,
	.clkgate_enable = set_clkgate,
	.clkacp_get = get_clkacp,
};

static struct platform_device k3_dma_device = {
	.name			= DEVICE_NAME,
	.id			= 0,
	.dev			= {
				.dma_mask		= &k3_dma_mask,
				.coherent_dma_mask	= DMA_BIT_MASK(32),
				.platform_data		= &k3_dma_data,
				.init_name		= DEVICE_NAME,
	},
	.resource	= k3_dma_resources,
	.num_resources	= ARRAY_SIZE(k3_dma_resources),
};

static struct platform_device *k3_dmacs[] __initdata = {
	&k3_dma_device,
};

static int __init k3_dma_init(void)
{
	printk(KERN_INFO "hi6620_dma_init");
	platform_add_devices(k3_dmacs, ARRAY_SIZE(k3_dmacs));

	return 0;
}
arch_initcall(k3_dma_init);


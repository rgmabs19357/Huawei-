/*
 * arch/arm/mach-hi6620/include/mach/dma.h
 *
 * Copyright (C) 2011 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 * Clockdev definitions and inline macros
 */
#ifndef __MACH_DMA_H
#define __MACH_DMA_H

#include <mach/platform.h>
#include <mach/irqs.h>
#include <linux/dmaengine.h>

#define	DEVICE_NAME			"hidmav300"

/*
 * Dma channels assigned to devices
 */
enum dma_ch {
	DMACH_spi0_RX = 0,
	DMACH_spi0_TX = 1,
	DMACH_uart1_RX = 4,
	DMACH_uart1_TX = 5,
	DMACH_uart2_RX = 6,
	DMACH_uart2_TX = 7,
	DMACH_uart3_RX = 8,
	DMACH_uart3_TX = 9,
	DMACH_uart4_RX = 10,
	DMACH_uart4_TX = 11,
	DMACH_uart5_RX = 12,
	DMACH_uart5_TX = 13,
	DMACH_spi1_RX = 28,
	DMACH_spi1_TX = 29,
#if 0
	DMACH_SCI_RX,
	DMACH_SCI_TX,
	DMACH_I2C0_RX,
	DMACH_I2C0_TX,
	DMACH_I2C1_RX,
	DMACH_I2C1_TX,
	DMACH_GPS_RX,
	DMACH_I2C2_RX,
	DMACH_I2C2_TX,
	DMACH_I2C3_RX,
	DMACH_I2C3_TX,
#endif
	DMACH_NUMBER,
	DMACH_uart0_RX = 33,
	DMACH_uart0_TX,
	DMACH_uart6_RX,
	DMACH_uart6_TX,
};

/*define number of  reserved phy channel*/
#define			HI6620_DMA_PHYCH_RESERVED		  7

#define			HI6620_DMA_PHYCH_SPI0_RX		(11)

/* dma phy channels*/
enum dma_phy_chan{
	DMACH_PHY_INVALID = -1,
	DMACH_PHY_BEGIN = HI6620_DMA_PHYCH_RESERVED,
	DMACH_PHY_UART3_RX = DMACH_PHY_BEGIN,
	DMACH_PHY_UART3_TX,
	DMACH_PHY_SPI0_RX = HI6620_DMA_PHYCH_SPI0_RX,
	DMACH_PHY_SPI0_TX,
	DMACH_PHY_MAX,
};

/* judge the phy chan is hi6620 used or not */
#define IS_HI6620_DMA_DEV(dev) ((DMACH_PHY_UART3_RX == dev) ||(DMACH_PHY_UART3_TX == dev) ||\
								(DMACH_PHY_SPI0_RX == dev)  ||(DMACH_PHY_SPI0_TX == dev))

/* interrupt mask according to phy chan */
#define HI6620_INT_MASK_BITS ((1 << DMACH_PHY_UART3_RX) | (1 << DMACH_PHY_UART3_TX) |\
							  (1 << DMACH_PHY_SPI0_RX) | (1 << DMACH_PHY_SPI0_TX))
#define HI6620_INT_MASK_ON (0xFFFF & HI6620_INT_MASK_BITS)
#define HI6620_INT_MASK_OFF (0xFFFF & (~(0xFFFF & HI6620_INT_MASK_BITS)))

/* dma channels priority*/
enum dma_ch_priority {
	DMACH_PRIORITY_0	= 0,
	DMACH_PRIORITY_1,
	DMACH_PRIORITY_2,
	DMACH_PRIORITY_3,
};

/*
 * Default dma param structure
 * used by dma filter function to check matched dma channel
 */
struct k3_def_dma_param {
	int chan_id;
};

#define K3_DMA_PARAM_NAME(req_name)	dma_##req_name

/*
 * Use this macro to define the dma param in device's platform data
 */
#define K3_DEF_DMA_PARAM(req_name)				\
static struct k3_def_dma_param K3_DMA_PARAM_NAME(req_name) =	\
{								\
	.chan_id = DMACH_##req_name,				\
}

/* Default dma filter function */
static inline bool
k3_def_dma_filter(struct dma_chan *chan, void *filter_param) {
	if ((chan == NULL) || (filter_param == NULL))
		return false;

	return (chan->chan_id ==
		((struct k3_def_dma_param *)filter_param)->chan_id);
}

/*channels*/
struct k3dma_channel_data {
	enum dma_ch peri;
	enum dma_ch_priority pri;
	enum dma_phy_chan phy_ch;
};
/*platforms*/
struct k3dma_platform_data {
	u32	nr_phy_channels;
	u32	nr_slave_channels;
	bool	hasacp;
	dma_cap_mask_t	cap_mask;
	struct k3dma_channel_data cd[DMACH_NUMBER];

	bool (*acp_enable)(bool on);
	bool (*clkgate_enable)(bool on);
	struct clk *(*clkacp_get)(void);
};
#endif

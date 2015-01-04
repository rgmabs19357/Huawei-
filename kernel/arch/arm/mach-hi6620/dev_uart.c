#include <mach/dma.h>
#include <linux/amba/serial.h>
#include <linux/amba/bus.h>
#include <mach/irqs.h>
#include <mach/dev.h>
#include <mach/early-debug.h>
#include "reg_ops.h"
#include "soc_sctrl_interface.h"
/*uart device declare and register*/

#define UART_RESET_CONTROLLER_TIMEOUT 10

#define MODULE_FUNCS_DEFINE(chip_id, dev_name)				\
static void dev_name ## _init(void){				\
    unsigned int ret;\
    int timeout = UART_RESET_CONTROLLER_TIMEOUT;\
\
    phy_reg_writel(REG_BASE_SC_OFF,\
        SOC_SCTRL_SC_PERIPH_RSTDIS1_ADDR(CALC_REG_OFFSET),\
        SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_ ## chip_id ## dev_name ## _START,\
        SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_ ## chip_id ## dev_name ## _END, 1);\
\
    while (timeout--){\
        ret = phy_reg_readl(REG_BASE_SC_OFF, \
            SOC_SCTRL_SC_PERIPH_RSTSTAT1_ADDR(CALC_REG_OFFSET),\
            SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_ ## chip_id ## dev_name ## _START,\
            SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_ ## chip_id ## dev_name ## _END);\
\
        if (ret && (!timeout)){\
            printk(KERN_ERR "mmc %d clock rst fail\n", chip_id);\
        } else if (!ret){\
              break;\
        } \
    } \
}								\
static void dev_name##_exit(void){				\
}

K3_DEF_DMA_PARAM(uart0_RX);
K3_DEF_DMA_PARAM(uart0_TX);
K3_DEF_DMA_PARAM(uart1_RX);
K3_DEF_DMA_PARAM(uart1_TX);
K3_DEF_DMA_PARAM(uart2_RX);
K3_DEF_DMA_PARAM(uart2_TX);
K3_DEF_DMA_PARAM(uart3_RX);
K3_DEF_DMA_PARAM(uart3_TX);
K3_DEF_DMA_PARAM(uart4_RX);
K3_DEF_DMA_PARAM(uart4_TX);
K3_DEF_DMA_PARAM(uart5_RX);
K3_DEF_DMA_PARAM(uart5_TX);
K3_DEF_DMA_PARAM(uart6_RX);
K3_DEF_DMA_PARAM(uart6_TX);

#define UART0_BLOCK_NAME            "block_uart0"
#define UART1_BLOCK_NAME            "block_uart1"
#define UART3_BLOCK_NAME            "block_uart3"

MODULE_FUNCS_DEFINE(0, uart0)
MODULE_FUNCS_DEFINE(1, uart1)
MODULE_FUNCS_DEFINE(2, uart2)
MODULE_FUNCS_DEFINE(3, uart3)
MODULE_FUNCS_DEFINE(4, uart4)
MODULE_FUNCS_DEFINE(5, uart5)
MODULE_FUNCS_DEFINE(6, uart6)

#define uart0_dma_filter  NULL
#define uart1_dma_filter  NULL
#define uart2_dma_filter  NULL
#define uart3_dma_filter  k3_def_dma_filter
#define uart4_dma_filter  NULL
#define uart5_dma_filter  NULL
#define uart6_dma_filter  NULL

#define K3_UART_PLAT_DATA(dev_name, flag)				\
	{								\
		.dma_filter = dev_name##_dma_filter,			\
		.dma_rx_param = &K3_DMA_PARAM_NAME(dev_name##_RX),	\
		.dma_tx_param = &K3_DMA_PARAM_NAME(dev_name##_TX),	\
		.irq_flags = flag,					\
		.init = dev_name##_init,				\
		.exit = dev_name##_exit,				\
	}

static struct amba_pl011_data uart_plat_data[] = {
	K3_UART_PLAT_DATA(uart0, 0),
	K3_UART_PLAT_DATA(uart1, 0),
	K3_UART_PLAT_DATA(uart2, 0),
	K3_UART_PLAT_DATA(uart3, 0),
	K3_UART_PLAT_DATA(uart4, 0),
	K3_UART_PLAT_DATA(uart5, 0),
	K3_UART_PLAT_DATA(uart6, 0),
};

#ifdef CONFIG_MACH_HI6620SFT
AMBA_DEVICE(uart6, "amba-uart.6", UART6, &uart_plat_data[6]);
AMBA_DEVICE(uart3, "amba-uart.3", UART3, &uart_plat_data[3]);
AMBA_DEVICE(uart4, "amba-uart.4", UART4, &uart_plat_data[4]);
#endif

#ifdef CONFIG_MACH_HI6620OEM
AMBA_DEVICE(uart0, "amba-uart.0", UART0, &uart_plat_data[0]);
AMBA_DEVICE(uart1, "amba-uart.1", UART1, &uart_plat_data[1]);
AMBA_DEVICE(uart2, "amba-uart.2", UART2, &uart_plat_data[2]);
AMBA_DEVICE(uart3, "amba-uart.3", UART3, &uart_plat_data[3]);
AMBA_DEVICE(uart4, "amba-uart.4", UART4, &uart_plat_data[4]);
AMBA_DEVICE(uart5, "amba-uart.5", UART5, &uart_plat_data[5]);
AMBA_DEVICE(uart6, "amba-uart.6", UART6, &uart_plat_data[6]);
#endif


static struct amba_device *amba_uart_devs[] __initdata = {

#ifdef CONFIG_MACH_HI6620SFT
	&uart6_device,
	&uart3_device,
	&uart4_device,
#endif

#ifdef CONFIG_MACH_HI6620OEM
    &uart0_device,
	&uart1_device,
	&uart2_device,
	&uart3_device,
	&uart4_device,
	&uart5_device,
	&uart6_device,
#endif

};


static int __initdata uart_console_enabled = 1;
static int __init uart_console_disable(char *__unused)
{
	uart_console_enabled = 0;

	return 0;
}
early_param("no_uart_console", uart_console_disable);


static int __init amba_uart_dev_init(void)
{
    int i;

    edb_trace(1);

    for (i = 1; i < ARRAY_SIZE(amba_uart_devs); i++) {
        struct amba_device *d = amba_uart_devs[i];
        amba_device_register(d, &iomem_resource);
    }

    if (uart_console_enabled){
        struct amba_device *d = amba_uart_devs[0];
        amba_device_register(d, &iomem_resource);
    }

    edb_trace(1);

    return 0;
}

arch_initcall(amba_uart_dev_init);

#include <linux/amba/bus.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/system.h>
#include <asm/pmu.h>
#include <asm/setup.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/lm.h>
#include <mach/irqs.h>
#include "soc_irqs.h"
#include <mach/io.h>
#include <linux/amba/pl061.h>
#include <mach/early-debug.h>
#include <mach/mmc.h>
#include <mach/dma.h>
#include <linux/amba/serial.h>
#include <linux/amba/pl022.h>
/*#include <mach/board-hi6421-regulator.h>*/
#include <mach/k3v2_regulators_vcc.h>
#include "drv_regulator_user.h"
#include <linux/mux.h>
#include <linux/delay.h>
#ifdef CONFIG_MFD_HI6421_IRQ
#include <sound/hi6421_common.h>
#endif
#include <mach/usb_phy.h>
#include <mach/boardid.h>
#include <mach/xmm_power.h>
#include <mach/gpio.h>
#include <mach/hisi_mem.h>
#include <hsad/config_mgr.h>

static struct resource hisik3_fb_resources[] = {
	[0] = {
		.name = "reg_base_edc0",
		.start = REG_BASE_EDC0,
		.end = REG_BASE_EDC0 + REG_EDC0_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.name = "reg_base_edc1",
		.start = REG_BASE_EDC1,
		.end = REG_BASE_EDC1 + REG_EDC1_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[2] = {
		.name = "irq_edc0",
		.start = IRQ_EDC0,
		.end = IRQ_EDC0,
		.flags = IORESOURCE_IRQ,
	},
	[3] = {
		.name = "irq_edc1",
		.start = IRQ_EDC1,
		.end = IRQ_EDC1,
		.flags = IORESOURCE_IRQ,
	},
	[4] = {
		.name = "irq_ldi0",
		.start = IRQ_EDC0_LDI,
		.end = IRQ_EDC0_LDI,
		.flags = IORESOURCE_IRQ,
	},
	[5] = {
		.name = "irq_ldi1",
		.start = IRQ_EDC1_LDI,
		.end = IRQ_EDC1_LDI,
		.flags	 = IORESOURCE_IRQ,
	},
	[6] = {
    	.name   = "reg_base_dsi0",
    	.start  = REG_BASE_DSI0,
    	.end    = REG_BASE_DSI0 + REG_DSI0_IOSIZE - 1,
    	.flags  = IORESOURCE_MEM,
    },
};

static struct platform_device hisik3_fb_device = {
	.name	= "k3_fb",
	.id	= 0,
	.num_resources	= ARRAY_SIZE(hisik3_fb_resources),
	.resource	= hisik3_fb_resources,
};

/*static struct platform_device *fb_devices[] __initdata = {
	&hisik3_fb_device,
};*/


static int __init fb_device_init(void)
{
	int ret = 0;
	ret = platform_device_register(&hisik3_fb_device);
	return ret;
};

arch_initcall(fb_device_init);




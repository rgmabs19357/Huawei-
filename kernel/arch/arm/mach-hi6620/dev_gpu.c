#include <mach/irqs.h>
#include <mach/platform.h>
#include <linux/platform_device.h>

#define REG_G2D_IOSIZE                      PAGE_ALIGN(SZ_256K)

static struct resource gpu_resources[] = {
	{
		.name	= "g2d_irq",
		.start	= IRQ_G2D,
		.end	= IRQ_G2D,
		.flags	= IORESOURCE_IRQ,
	},
	{
		.name  	= "g2d_base",
		.start	= REG_BASE_G2D,
		.end	= REG_BASE_G2D + REG_G2D_IOSIZE - 1,
		.flags	= IORESOURCE_MEM,
	},

};

static struct platform_device gpu_device = {
	.name	= "galcore",
	.id	= 0,
	.num_resources	= ARRAY_SIZE(gpu_resources),
	.resource	= gpu_resources,
};

static int __init plat_gpu_init(void)
{
	int ret = 0;
	ret = platform_device_register(&gpu_device);
	
	return ret;
};


arch_initcall(plat_gpu_init);
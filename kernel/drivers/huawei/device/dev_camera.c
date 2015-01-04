/*camera device declare and register*/
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>
#include <mach/platform.h>
#include <mach/system.h>
#include "soc_irqs.h"

static struct resource hisik3_camera_resources[] = {
	{
		.name		= "isp_base",
		.start		= REG_BASE_ISP,
		.end		= REG_BASE_ISP + REG_ISP_IOSIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.name		= "isp_irq",
		.start		= IRQ_ISP,
		.end		= IRQ_ISP,
		.flags		= IORESOURCE_IRQ,
	},
	{
		.name		= "csi_base",
		.start		= REG_BASE_CSI,
		.end		= REG_BASE_CSI + REG_CSI_IOSIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.name		= "csi0_irq",
		.start		= IRQ_MIPI_CSI0,
		.end		= IRQ_MIPI_CSI0,
		.flags		= IORESOURCE_IRQ,
	},
	{
		.name		= "csi1_irq",
		.start		= IRQ_MIPI_CSI1,
		.end		= IRQ_MIPI_CSI1,
		.flags		= IORESOURCE_IRQ,
	}
};

static struct platform_device hisik3_camera_device = {
	.id	= 0,
	.name	= "k3-camera-v4l2",
	.dev = {
		.init_name = "camera",
	},
	.resource	= hisik3_camera_resources,
	.num_resources	= ARRAY_SIZE(hisik3_camera_resources),
};


/* please add platform device in the struct.*/
static struct platform_device *plat_camera_dev[] __initdata = {
	&hisik3_camera_device
       /*add other device here*/
};

static int __init plat_camera_dev_init(void)
{
	int ret = 0;
	
	ret = platform_add_devices(plat_camera_dev, ARRAY_SIZE(plat_camera_dev));

	return ret;
};

arch_initcall(plat_camera_dev_init);

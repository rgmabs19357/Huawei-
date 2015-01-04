/*audio device declare and register*/

#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/init.h>
#include <mach/platform.h>
#include <mach/system.h>
#include "soc_irqs.h"


static struct resource hx170dec_resources[] = {
	[0] = {
	       .start = REG_BASE_VDEC,
	       .end = REG_BASE_VDEC + REG_VDEC_IOSIZE - 1,
	       .flags = IORESOURCE_MEM,
	       },

	[1] = {
	       .start = IRQ_VDEC,
	       .end = IRQ_VDEC,
	       .flags = IORESOURCE_IRQ,
	       }
};

static struct platform_device hisik3_hx170dec_device = {
	.name = "hx170dec",
	.id = 0,
	.resource = hx170dec_resources,
	.num_resources = 2,
};


static struct resource hx280enc_resources[] = {
	[0] = {
	       .start = REG_BASE_VENC,
	       .end = REG_BASE_VENC + REG_VENC_IOSIZE - 1,
	       .flags = IORESOURCE_MEM,
	       },

	[1] = {
	       .start = IRQ_VENC,
	       .end = IRQ_VENC,
	       .flags = IORESOURCE_IRQ,
	       }
};

static struct platform_device hisik3_hx280enc_device = {
	.name = "hx280enc",
	.id = 0,
	.resource = hx280enc_resources,
	.num_resources = 2,
};


/* please add platform device in the struct.*/
static struct platform_device *plat_codec_dev[] __initdata = {
	&hisik3_hx170dec_device,
	&hisik3_hx280enc_device
       /*add other device here*/
};

static int __init plat_codec_dev_init(void)
{
	int ret = 0;
	printk("enter plat_hantro_dev_init()\n");

	ret = platform_add_devices(plat_codec_dev, ARRAY_SIZE(plat_codec_dev));

	return ret;
};


#if 0
module_init(plat_codec_dev_init);
#endif

arch_initcall(plat_codec_dev_init);


#if 0
static int __init hisik3_hx170dec_dev_init(void)
{
	int i;
	int ret = -1;

    ret = platform_device_register(&hisik3_hx170dec_device);


	return ret;
}

arch_initcall(hisik3_hx170dec_dev_init);

#endif



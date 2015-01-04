#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/ioport.h>
#include "soc_irqs.h"
#include <mach/platform.h>
#include <linux/mhl/mhl.h>

static struct resource hisik3_mhl_resources[] = {
    [0] = {
        .name = MHL_IRQ_NAME,
        .start = IRQ_HDMI_MHL,
        .end = IRQ_HDMI_MHL,
        .flags = IORESOURCE_IRQ,
    },
    [1] = {
        .name = MHL_REG_NAME,
        .start = REG_BASE_EDC1,
        .end = REG_BASE_EDC1 + REG_EDC1_IOSIZE - 1,
        .flags = IORESOURCE_MEM,
    }
};

static struct platform_device hisik3_mhl_device = {
    .name = MHL_DEVICE_NAME,
    .id = 0,
    .num_resources = ARRAY_SIZE(hisik3_mhl_resources),
    .resource = hisik3_mhl_resources,
};

static int __init mhl_device_init(void)
{
    return platform_device_register(&hisik3_mhl_device);
};

arch_initcall(mhl_device_init);

#include <mach/irqs.h>
#include <linux/kernel.h>/*array_size is defined in kernel.h*/
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <linux/rmi.h>
#include <linux/delay.h>

#include <mach/sound/modemctl.h>
#include <hsad/config_mgr.h>

static struct modemctl_platform_data modem_switch_pdata = {
	.gpio_modemctl_en    = GPIO_14_3,
};
static struct platform_device modem_switch_device = {
	.name    = MODEMCTL_NAME,
	.id      = 0,
	.dev     = {
		.platform_data = &modem_switch_pdata,
	},
};

static void init_modemctl_gpio(void)
{
    int ret = 0;
    int gpio_enable = 0;

    ret = get_hw_config_int("audio/gpio_modemctl_enble", &gpio_enable, NULL);
    if (false == ret) {
        printk(KERN_ERR "gpio_enable value not found !\n");
        modem_switch_pdata.gpio_modemctl_en = GPIO_14_3;
    } else {
        modem_switch_pdata.gpio_modemctl_en = gpio_enable;
    }
}

static int __init modemctl_dev_init(void)
{
    init_modemctl_gpio();
    platform_device_register(&modem_switch_device);

    return 0;
}


arch_initcall(modemctl_dev_init);


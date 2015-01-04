#include <mach/irqs.h>
#include <linux/kernel.h>/*array_size is defined in kernel.h*/
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <linux/rmi.h>
#include <linux/delay.h>

#include <mach/sound/es305.h>
#include <hsad/config_mgr.h>

static struct es305_platform_data audience_platform_data = {
	.gpio_es305_wakeup  = GPIO_18_6,
	.gpio_es305_reset   = GPIO_13_7,
};



static struct i2c_board_info audience_i2c_es305[] = {
	[0]	=	{
        .type			= ES305_NAME,
		.addr			= 0x3E,
		.flags 			= true,
		.platform_data 	= &audience_platform_data,
	},
};

static void init_es305_gpio(void)
{
    int ret = 0;
    int gpio_wakeup = 0;
    int gpio_reset = 0;

    ret = get_hw_config_int("audio/gpio_es305_wakeup", &gpio_wakeup, NULL);
    if (false == ret) {
        printk(KERN_ERR "gpio_wakeup value not found !\n");
        audience_platform_data.gpio_es305_wakeup = GPIO_18_6;
    } else {
        audience_platform_data.gpio_es305_wakeup = gpio_wakeup;
    }

    ret = get_hw_config_int("audio/gpio_es305_reset", &gpio_reset, NULL);
    if (false == ret) {
        printk(KERN_ERR "gpio_reset value not found !\n");
        audience_platform_data.gpio_es305_reset = GPIO_13_7;
    } else {
        audience_platform_data.gpio_es305_reset = gpio_reset;
    }
}

static int __init audience_dev_init(void)
{
    int ret;

    init_es305_gpio();
    ret = i2c_register_board_info(1, &audience_i2c_es305[0], ARRAY_SIZE(audience_i2c_es305));
    
    if(ret)
        printk(KERN_ERR "register audience hardware device error!\n");

    return ret;
}

postcore_initcall(audience_dev_init);


#include <mach/irqs.h>
#include <linux/kernel.h>/*array_size is defined in kernel.h*/
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <linux/rmi.h>
#include <linux/delay.h>

#include <mach/sound/tfa9887.h>

static struct i2c_board_info smartpa_i2c_tfa9887[] = {
   [0] =   {
		.type			= TFA9887_NAME,
		.addr			= TFA9887_I2C_ADDR,
		.flags 			= true,
	},
};

#if 0
static int __init smartpa_dev_init(void)
{
	const char str_tfa9887[] = "TFA9887";
	/* Register smartpa devices to I2C Bus1*/
	if(get_spk_pa(str_tfa9887) == true) {
	    int bus_id;
	    if(product_fullname("CEDGED") || product_fullname("UEDGE") || product_fullname("UEDGE_G")){
		    bus_id = 0;
		}else{
		    bus_id = 3;
		}
	    i2c_register_board_info(bus_id, smartpa_i2c_tfa9887,
					    ARRAY_SIZE(smartpa_i2c_tfa9887));
    }
}
#else
static int __init smartpa_dev_init(void)
{
    int ret;

    ret = i2c_register_board_info(1, &smartpa_i2c_tfa9887[0], ARRAY_SIZE(smartpa_i2c_tfa9887));
    
    if(ret)
        printk(KERN_ERR "register smartpa hardware device error!\n");

    return ret;
}
#endif

postcore_initcall(smartpa_dev_init);


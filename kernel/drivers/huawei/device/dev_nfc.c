 /*
  * arch/arm/mach-hi6620/dev_nfc.c
  *
  * Copyright (C) 2013 Huawei, Inc.
  *
  * This software is licensed under the terms of the GNU General Public
  * License version 2, as published by the Free Software Foundation, and
  * may be copied, distributed, and modified under those terms.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  */
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include "dev_common.h"
#include "dev_nfc.h"
#include "hsad_connectivity.h"

static int nfc_gpio_setup (struct pn544_i2c_platform_data *platform_data)
 {
         int retval = 0; 
 
         retval = gpio_request(platform_data->firm_gpio, "nfc_firm");
         if (retval) {
             pr_err("%s: Failed to get nfc_firm gpio %d. Code: %d.",
                    __func__, platform_data->firm_gpio, retval);
             return retval;
         }    
 
         retval = gpio_direction_output(platform_data->firm_gpio,0);
         if (retval) {
             pr_err("%s: Failed to setup nfc_firm gpio %d. Code: %d.",
                    __func__, platform_data->firm_gpio, retval);
             gpio_free(platform_data->firm_gpio);
             return retval;
         }    
 
 
         retval = gpio_request(platform_data->ven_gpio, "nfc_ven");
         if (retval) {
             pr_err("%s: Failed to get nfc_ven gpio %d. Code: %d.",
                    __func__, platform_data->ven_gpio, retval);
             gpio_free(platform_data->firm_gpio);
             return retval;
         }
 
         retval = gpio_direction_output(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 0:1);
         if (retval) {
             pr_err("%s: Failed to setup nfc_ven gpio %d. Code: %d.",
                    __func__, platform_data->ven_gpio, retval);
             gpio_free(platform_data->ven_gpio);
             gpio_free(platform_data->firm_gpio);
             return retval;
         }
 
         msleep (20);
         retval = gpio_direction_output(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
         if (retval) {
             pr_err("%s: Failed to setup nfc_ven gpio %d. Code: %d.",
                    __func__, platform_data->ven_gpio, retval);
             gpio_free(platform_data->ven_gpio);
             gpio_free(platform_data->firm_gpio);
         }
         msleep (10);
 
         return retval;
 }
 
 
 static struct pn544_i2c_platform_data pn544_platform_data = {
 
     .irq_gpio = 0,
     .ven_gpio = 0,
     .firm_gpio = 0,
     .ven_valid_level = 0,
     .clock_src = "",
     .gpio_config = nfc_gpio_setup,
 };

static struct i2c_board_info hi6620_nfc_i2c0_devs[]= {
     [0] =   {
         .type           = NFC_NAME,
         .addr           = NFC_ADDR,
         .platform_data  = &pn544_platform_data,
         .irq            = 0,
        },   
};

static void init_nfc_dev_info(struct i2c_board_info *nfc_devs)
{
        if(NULL == nfc_devs){
            printk(KERN_ERR "%s nfc_devs == NULL !\n", __func__);
            return ;
        }
        
		((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->irq_gpio = hsad_get_nfc_irq_id();
		((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->ven_gpio = hsad_get_nfc_ven_id();
		((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->firm_gpio = hsad_get_nfc_firm_dload_id();
		((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->ven_valid_level = hsad_get_nfc_ven_valid_level();
        
        if(false == hsad_get_nfc_clk_src(((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->clock_src)){
    		printk(KERN_WARNING "%s hsad_get_nfc_clk_src is %s!\n", __func__, ((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->clock_src);            
        }        
		printk(KERN_WARNING "%s clock src is %s!\n", __func__, ((struct pn544_i2c_platform_data *)nfc_devs[0].platform_data)->clock_src);
        	
		nfc_devs[0].irq = hsad_get_nfc_irq_id();
				
}


static int __init nfc_i2c_device_init(void)
{
	int status = -1;
	
	init_nfc_dev_info(hi6620_nfc_i2c0_devs);

	/*NFC PN547  board use I2C bus 0 */
        status =  dev_i2c_add_devices(0, hi6620_nfc_i2c0_devs, ARRAY_SIZE(hi6620_nfc_i2c0_devs));
	if(status)
	{
		printk(KERN_ERR "register nfc_i2c_device error!\n");
		return status;
	}

	return 0;
}

device_initcall(nfc_i2c_device_init);

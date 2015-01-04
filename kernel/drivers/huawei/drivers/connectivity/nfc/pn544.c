/*
 * Copyright (C) 2010 Trusted Logic S.A.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/reboot.h>
#include <linux/clk.h>
#include <linux/wakelock.h>
#include <mach/clk_name_interface.h>
#include "dev_nfc.h"
#include "hsad_connectivity.h"
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif

#define NFC_FWVERSION_LEN   16
#define MAX_BUFFER_SIZE	512
static int firmware_update = 0;
char nfc_firmware_version[NFC_FWVERSION_LEN] = {0};
static struct wake_lock wlock_read;

struct pn544_dev	{
	wait_queue_head_t	read_wq;
	struct mutex		read_mutex;
	struct i2c_client	*client;
	struct miscdevice	pn544_device;
	unsigned int 		ven_gpio;
	unsigned int 		firm_gpio;
	unsigned int		irq_gpio;
	bool			irq_enabled;
	spinlock_t		irq_enabled_lock;
	struct clk              *clk;
	char                    *clk_src;
};

static void pn544_disable_irq(struct pn544_dev *pn544_dev)
{
	unsigned long flags;

	spin_lock_irqsave(&pn544_dev->irq_enabled_lock, flags);
	if (pn544_dev->irq_enabled) {
		disable_irq_nosync(gpio_to_irq(pn544_dev->client->irq));
		pn544_dev->irq_enabled = false;
	}
	spin_unlock_irqrestore(&pn544_dev->irq_enabled_lock, flags);
}

static irqreturn_t pn544_dev_irq_handler(int irq, void *dev_id)
{
	struct pn544_dev *pn544_dev = dev_id;

	pn544_disable_irq(pn544_dev);

	pr_info("%s : Enter\n", __func__);

	/*set a wakelock to avoid entering into suspend */
	wake_lock_timeout(&wlock_read, 1 * HZ);

	/* Wake up waiting readers */
	wake_up(&pn544_dev->read_wq);

	pr_info("%s : Exit\n", __func__);

	return IRQ_HANDLED;
}

static ssize_t pn544_dev_read(struct file *filp, char __user *buf,
		size_t count, loff_t *offset)
{
	struct pn544_dev *pn544_dev = filp->private_data;
	char tmp[MAX_BUFFER_SIZE];
	char *tmpStr = NULL;
        size_t ret;
	int i;
        int retry;
        bool isSuccess = false;

	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;


	mutex_lock(&pn544_dev->read_mutex);

	if (!gpio_get_value(pn544_dev->irq_gpio)) {
		if (filp->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			goto fail;
		}

		pn544_disable_irq(pn544_dev);

		pn544_dev->irq_enabled = true;
		enable_irq(gpio_to_irq(pn544_dev->client->irq));
		ret = wait_event_interruptible(pn544_dev->read_wq,
				gpio_get_value(pn544_dev->irq_gpio));

		if (ret)
			goto fail;

	}

	tmpStr = (char *)kzalloc(sizeof(tmp)*2, GFP_KERNEL);
	if (!tmpStr) {
		pr_info("%s:Cannot allocate memory for read tmpStr.\n", __func__);
		ret = -ENOMEM;
		goto fail;
	}

        /* Read data, we have 3 chances */
        for(retry = 0; retry < 3; retry++)
        {
	    ret = (size_t)i2c_master_recv(pn544_dev->client, tmp, count);

            for(i=0; i<count; i++)
            {
                snprintf(&tmpStr[i * 2], 3, "%02X", tmp[i]);
            }

            pr_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, count, tmpStr);


	    if(ret == count)
	    {
                 isSuccess = true;
		 break;
	    }
	    else
	    {
	         pr_info("%s : read data try =%d returned %d\n", __func__,retry,ret);
	         msleep(10);
	         continue;
	    }
        }

	kfree(tmpStr);

	if (false == isSuccess) {
		pr_err("%s : i2c_master_recv returned %d\n", __func__, ret);
		ret = -EIO;
	}

	mutex_unlock(&pn544_dev->read_mutex);

	if (ret < 0) {
		pr_err("%s: i2c_master_recv returned %d\n", __func__, ret);
		return ret;
	}
	if (ret > count) {
		pr_err("%s: received too many bytes from i2c (%d)\n",
			__func__, ret);
		return -EIO;
	}
	if (copy_to_user(buf, tmp, ret)) {
		pr_err("%s : failed to copy to user space\n", __func__);
		return -EFAULT;
	}
	return ret;

fail:
	mutex_unlock(&pn544_dev->read_mutex);
	return (ssize_t)ret;
}

static ssize_t pn544_dev_write(struct file *filp, const char __user *buf,
		size_t count, loff_t *offset)
{
	struct pn544_dev  *pn544_dev;
	char tmp[MAX_BUFFER_SIZE];
	char *tmpStr = NULL;
	size_t ret;
	int retry;
	int i;
        bool isSuccess = false;

	pn544_dev = filp->private_data;

	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;

	if (copy_from_user(tmp, buf, count)) {
		pr_err("%s : failed to copy from user space\n", __func__);
		return -EFAULT;
	}

	tmpStr = (char *)kzalloc(sizeof(tmp)*2, GFP_KERNEL);
	if (!tmpStr) {
		pr_info("%s:Cannot allocate memory for write tmpStr.\n", __func__);
		return -ENOMEM;
	}

	/* Write data, we have 3 chances */
        for(retry = 0; retry < 3; retry++)
        {
	    ret = (size_t)i2c_master_send(pn544_dev->client, tmp, count);

            for(i=0; i<count; i++)
            {
                snprintf(&tmpStr[i * 2], 3, "%02X", tmp[i]);
            }

            pr_info("%s : retry = %d, ret = %d, count = %3d > %s\n", __func__, retry, ret, count, tmpStr);


	    if (ret == count)
	    {
                isSuccess = true;
                break;
	    }
	    else
            {
		if(retry > 0)
		{
	            pr_info("%s : send data try =%d returned %d\n", __func__,retry,ret);
		}
                msleep(10);
	        continue;
            }
        }

	kfree(tmpStr);

	if (false == isSuccess) {
		pr_err("%s : i2c_master_send returned %d\n", __func__, ret);
		ret = -EIO;
	}

	return (ssize_t)ret;
}

static int pn544_dev_open(struct inode *inode, struct file *filp)
{
	struct pn544_dev *pn544_dev = container_of(filp->private_data,
						struct pn544_dev,
						pn544_device);

	filp->private_data = pn544_dev;

        pr_info("%s : %d,%d\n", __func__, imajor(inode), iminor(inode));

	return 0;
}

static long pn544_dev_ioctl(struct file *filp,
			    unsigned int cmd, unsigned long arg)
{
	struct pn544_dev *pn544_dev = filp->private_data;
        int ven_valid_level = 0;

        ven_valid_level = hsad_get_nfc_ven_valid_level();

	switch (cmd) {
	case PN544_SET_PWR:
		if (arg == 2) {
			/* power on with firmware download (requires hw reset)
			 */
			pr_info("%s power on with firmware\n", __func__);
			gpio_set_value(pn544_dev->ven_gpio, (NFC_GPIO_LEVEL_HIGH == ven_valid_level)? 1:0);
			gpio_set_value(pn544_dev->firm_gpio, 1);
			msleep(20);
			gpio_set_value(pn544_dev->ven_gpio, (NFC_GPIO_LEVEL_HIGH == ven_valid_level)? 0:1);
			msleep(60);
			gpio_set_value(pn544_dev->ven_gpio, (NFC_GPIO_LEVEL_HIGH == ven_valid_level)? 1:0);
			msleep(20);
		} else if (arg == 1) {
			/* power on */
			pr_info("%s power on\n", __func__);
			gpio_set_value(pn544_dev->firm_gpio, 0);
			gpio_set_value(pn544_dev->ven_gpio, (NFC_GPIO_LEVEL_HIGH == ven_valid_level)? 1:0);
			msleep(20);
		} else  if (arg == 0) {
			/* power off */
			pr_info("%s power off\n", __func__);
			gpio_set_value(pn544_dev->firm_gpio, 0);
			gpio_set_value(pn544_dev->ven_gpio, (NFC_GPIO_LEVEL_HIGH == ven_valid_level)? 0:1);
			msleep(60);
		} else {
			pr_err("%s bad arg %lu\n", __func__, arg);
			return -EINVAL;
		}
		break;
	default:
		pr_err("%s bad ioctl %u\n", __func__, cmd);
		return -EINVAL;
	}

	return 0;
}

static const struct file_operations pn544_dev_fops = {
	.owner	= THIS_MODULE,
	.llseek	= no_llseek,
	.read	= pn544_dev_read,
	.write	= pn544_dev_write,
	.open	= pn544_dev_open,
	.unlocked_ioctl	= pn544_dev_ioctl,
};

static ssize_t nfc_fwupdate_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{

	if ('1' == buf[0]) {
		firmware_update = 1;
		printk("%s:firmware update success\n", __func__);
	}

	return (ssize_t)count;
}

static ssize_t nfc_fwupdate_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	return (ssize_t)(snprintf(buf, sizeof(firmware_update)+1, "%d", firmware_update));
}

static ssize_t nfc_fwversion_store(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{

	if (NULL != buf) {
		memcpy(nfc_firmware_version, buf, NFC_FWVERSION_LEN > count ? count:NFC_FWVERSION_LEN);
		pr_warning("%s:nfc_firmware_version = %s, buf = %s, count = %d\n", __func__, nfc_firmware_version, buf, count);
	}

	return (ssize_t)count;
}

static ssize_t nfc_fwversion_show(struct device *dev, struct device_attribute *attr, char *buf)
{
        if (NULL != buf) {
                return (ssize_t)(snprintf(buf, strlen(nfc_firmware_version)+1, "%s", nfc_firmware_version));
        }
}

static struct device_attribute pn544_attr[] ={

	__ATTR(nfc_fwupdate, 0664, nfc_fwupdate_show, nfc_fwupdate_store),
	__ATTR(nfc_fwversion, 0664, nfc_fwversion_show, nfc_fwversion_store),
};
static int create_sysfs_interfaces(struct device *dev)
{
       int i;
       for (i = 0; i < ARRAY_SIZE(pn544_attr); i++){
	        if (device_create_file(dev, pn544_attr + i)){
                    goto error;
            }
       }

       return 0;
error:
	for ( ; i >= 0; i--){
		   device_remove_file(dev, pn544_attr + i);
    }

    pr_err("%s:pn544 unable to create sysfs interface.\n", __func__ );
    return -1;
}

static int remove_sysfs_interfaces(struct device *dev)
{
       int i;
       for (i = 0; i < ARRAY_SIZE(pn544_attr); i++){
	           device_remove_file(dev, pn544_attr + i);
       }

       return 0;
}
static int nfc_ven_low_beforepwd(struct notifier_block *this, unsigned long code,
                                                                void *unused)
{
        int retval = 0;
            printk("%s: enter  nfc_ven_low_beforepwd\n", __func__);
            retval = gpio_direction_output(hsad_get_nfc_ven_id(), (NFC_GPIO_LEVEL_HIGH == hsad_get_nfc_ven_valid_level())? 0:1);
        if (retval) {
            pr_err("%s: Failed to setup nfc_ven gpio %d. Code: %d.",
                   __func__, hsad_get_nfc_ven_id(), retval);
            gpio_free(hsad_get_nfc_ven_id());
        }
        return retval;
}

static struct notifier_block nfc_ven_low_notifier = {
        .notifier_call =        nfc_ven_low_beforepwd,
};

static int check_pn544(struct i2c_client *client)
{
       int ret = -1;
       int count = 0;
       const char host_to_pn544[4] = {0x20, 0x00, 0x01, 0x01};
       const char firm_dload_cmd[8]={0x00, 0x04, 0xD0, 0x09, 0x00, 0x00, 0xB1, 0x84};

       struct pn544_i2c_platform_data *platform_data;
       platform_data = client->dev.platform_data;

       printk("%s:check pn544 chip,send cmd 3 times at most\n",__func__);
       for(count = 0; count < 3;count++)
       {
	   ret = i2c_master_send(client,  host_to_pn544, sizeof(host_to_pn544));
	   if (ret < 0){
		pr_err("%s:pn544_i2c_write failed and ret = %d,at %d times\n", __func__,ret,count);
		msleep(10);
		continue;
	   }
	   else{
		printk("%s:pn544_i2c_write success and ret = %d,at %d times\n",__func__,ret,count);
		msleep(10);
		return ret;
	   }

       }

       for(count = 0; count < 3;count++)
       {

           printk("%s:enter fw download mode\n", __func__);
           gpio_set_value(platform_data->firm_gpio, 1);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
           msleep(20);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 0:1);
           msleep(60);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
           msleep(20);

           printk("%s:send fw download cmd for check pn544\n", __func__);
           ret = i2c_master_send(client,  firm_dload_cmd, sizeof(firm_dload_cmd));
           if (ret < 0)
           {
               printk("%s:pn544_i2c_write download cmd failed:%d, ret = %d\n", __func__, count, ret);
               gpio_set_value(platform_data->firm_gpio, 0);
               gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
               msleep(20);
               gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 0:1);
               msleep(60);
               gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
               msleep(20);
               continue;
           }

           printk("%s:exit firmware download for check pn544 successfully\n", __func__);
           gpio_set_value(platform_data->firm_gpio, 0);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
           msleep(20);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 0:1);
           msleep(60);
           gpio_set_value(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 1:0);
           msleep(20);

           break;
	}

       return ret;
}

static int pn544_probe(struct i2c_client *client,
		const struct i2c_device_id *id)
{
	int ret;
	struct pn544_i2c_platform_data *platform_data;
	struct pn544_dev *pn544_dev;

	platform_data = client->dev.platform_data;

	if (platform_data == NULL) {
		pr_err("%s : nfc probe fail\n", __func__);
		return  -ENODEV;
	}

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("%s : need I2C_FUNC_I2C\n", __func__);
		return  -ENODEV;
	}

	ret = gpio_request(platform_data->irq_gpio, "nfc_int");
	if (ret)
		return  -ENODEV;

	/*nfc gpio config*/
	if (platform_data->gpio_config) {
		dev_info(&client->dev, "Configuring GPIOs.\n");
		ret = platform_data->gpio_config(platform_data);
		if (ret< 0) {
			dev_err(&client->dev, "Failed to configure GPIOs, code: %d.\n",ret);
			goto err_config;
		}
		dev_info(&client->dev, "Done with GPIO configuration.\n");
	}

	ret = create_sysfs_interfaces(&client->dev);
	if (ret < 0) {
		dev_err(&client->dev, "Failed to create_sysfs_interfaces\n");
		goto err_sysfs;
	}

	pn544_dev = kzalloc(sizeof(*pn544_dev), GFP_KERNEL);
	if (pn544_dev == NULL) {
		dev_err(&client->dev,"failed to allocate memory for module data\n");
		ret = -ENOMEM;
		goto err_exit;
	}

	ret = check_pn544(client);
	if(ret < 0){
            pr_err("%s: pn544 probe failed \n",__func__);
            kfree(pn544_dev);
	    goto err_exit;
	}

	ret = gpio_direction_output(platform_data->ven_gpio, (NFC_GPIO_LEVEL_HIGH == platform_data->ven_valid_level)? 0:1);
	if (ret) {
		pr_err("%s: Failed to setup nfc_ven gpio %d. Code: %d.",
	                   __func__, platform_data->ven_gpio, ret);
		kfree(pn544_dev);
		goto err_exit;

	}

	pn544_dev->irq_gpio = platform_data->irq_gpio;
	pn544_dev->ven_gpio  = platform_data->ven_gpio;
	pn544_dev->firm_gpio  = platform_data->firm_gpio;
	pn544_dev->clk_src = platform_data->clock_src;
	pn544_dev->client   = client;

	/* init mutex and queues */
	init_waitqueue_head(&pn544_dev->read_wq);
	mutex_init(&pn544_dev->read_mutex);
	spin_lock_init(&pn544_dev->irq_enabled_lock);
        /* Initialize wakelock*/
        wake_lock_init(&wlock_read, WAKE_LOCK_SUSPEND, "nfc_read");

	pn544_dev->pn544_device.minor = MISC_DYNAMIC_MINOR;
	pn544_dev->pn544_device.name = "pn544";
	pn544_dev->pn544_device.fops = &pn544_dev_fops;

	ret = misc_register(&pn544_dev->pn544_device);
	if (ret) {
		pr_err("%s : misc_register failed\n", __FILE__);
		goto err_misc_register;
	}

	/* request irq.  the irq is set whenever the chip has data available
	 * for reading.  it is cleared when all data has been read.
	 */
	pr_info("%s : requesting IRQ %d\n", __func__, client->irq);
	pn544_dev->irq_enabled = true;
	ret = request_irq(gpio_to_irq(client->irq), pn544_dev_irq_handler,
			  IRQF_TRIGGER_HIGH | IRQF_NO_SUSPEND, client->name, pn544_dev);
	if (ret) {
		dev_err(&client->dev, "request_irq failed\n");
		goto err_request_irq_failed;
	}
	pn544_disable_irq(pn544_dev);
	i2c_set_clientdata(client, pn544_dev);

        ret = register_reboot_notifier(&nfc_ven_low_notifier);
        if (ret != 0) {
                pr_info(KERN_ERR "cannot register reboot notifier (err=%d)\n",
                        ret);
                goto err_request_irq_failed;
        }

	#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	set_hw_dev_flag(DEV_I2C_NFC);
	#endif
	
    if(strstr(pn544_dev->clk_src, NFC_CLK_SRC_PLL)){
        printk(KERN_WARNING "%s clock src is %s!\n", __func__, NFC_CLK_SRC_PLL);
    	pn544_dev->clk = clk_get(NULL, CLK_NFC);
    	if (IS_ERR(pn544_dev->clk)) {
    		dev_err(&client->dev, "Get NFC clk failed\n");
    		goto err_request_irq_failed;
    	}
	
    	ret = clk_enable(pn544_dev->clk);
    	if (ret) {
    		dev_err(&client->dev, "Enable NFC clk failed, ret=%d\n", ret);
	        clk_put(pn544_dev->clk);
    		goto err_request_irq_failed;
    	    }
	}
    else{
        printk(KERN_WARNING "%s clock src is %s!\n", __func__, NFC_CLK_SRC_XTAL);
    }
    
	return 0;

err_request_irq_failed:
	misc_deregister(&pn544_dev->pn544_device);
err_misc_register:
	wake_lock_destroy(&wlock_read);
	mutex_destroy(&pn544_dev->read_mutex);
	kfree(pn544_dev);
err_exit:
	remove_sysfs_interfaces(&client->dev);
err_sysfs:
	gpio_free(platform_data->firm_gpio);
	gpio_free(platform_data->ven_gpio);
err_config:
	gpio_free(platform_data->irq_gpio);
	return ret;
}

static int pn544_remove(struct i2c_client *client)
{
	struct pn544_dev *pn544_dev;

	unregister_reboot_notifier(&nfc_ven_low_notifier);
	pn544_dev = i2c_get_clientdata(client);
	free_irq(gpio_to_irq(client->irq), pn544_dev);
	misc_deregister(&pn544_dev->pn544_device);
	wake_lock_destroy(&wlock_read);
	mutex_destroy(&pn544_dev->read_mutex);
	gpio_free(pn544_dev->irq_gpio);
	gpio_free(pn544_dev->ven_gpio);
	gpio_free(pn544_dev->firm_gpio);
	remove_sysfs_interfaces(&client->dev);
    if(strstr(pn544_dev->clk_src, NFC_CLK_SRC_PLL)){
  	    clk_put(pn544_dev->clk);
    }
	kfree(pn544_dev);

	return 0;
}

static const struct i2c_device_id pn544_id[] = {
	{ "pn544", 0 },
	{ }
};

#ifdef CONFIG_PM
static int pn544_suspend(struct i2c_client *client, pm_message_t mesg)
{		
        struct pn544_dev *pn544_dev;
        
	    printk("[%s] +\n", __func__);
		
	    pn544_dev = i2c_get_clientdata(client);
        
        if(strstr(pn544_dev->clk_src, NFC_CLK_SRC_PLL)){  	    
            clk_disable(pn544_dev->clk);     
        }

        printk("[%s] -\n", __func__);
        
        return 0;
}
static int pn544_resume(struct i2c_client *client)
{
        int ret = -1;
    	struct pn544_dev *pn544_dev;
        
    	printk("[%s] +\n", __func__);
		
    	pn544_dev = i2c_get_clientdata(client);
    
        if(strstr(pn544_dev->clk_src, NFC_CLK_SRC_PLL)){  	    
            ret = clk_enable(pn544_dev->clk);
            if (ret < 0) {
                printk("%s: clk_enable failed, ret:%d\n", __func__, ret);
            }
        }
	else{
	    ret = 0;
	}

        printk("[%s] -\n", __func__);
        
        return ret;
}
#else
#define pn544_suspend      NULL
#define pn544_resume       NULL
#endif /* CONFIG_PM */

static struct i2c_driver pn544_driver = {
	.id_table	= pn544_id,
	.probe		= pn544_probe,
	.remove		= pn544_remove,
	.suspend	= pn544_suspend,
	.resume 	= pn544_resume,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "pn544",
	},
};

/*
 * module load/unload record keeping
 */

static int __init pn544_dev_init(void)
{
	pr_info("Loading pn544 driver\n");
	return i2c_add_driver(&pn544_driver);
}
module_init(pn544_dev_init);

static void __exit pn544_dev_exit(void)
{
	pr_info("Unloading pn544 driver\n");
	i2c_del_driver(&pn544_driver);
}
module_exit(pn544_dev_exit);

MODULE_AUTHOR("Sylvain Fonteneau");
MODULE_DESCRIPTION("NFC PN544 driver");
MODULE_LICENSE("GPL");

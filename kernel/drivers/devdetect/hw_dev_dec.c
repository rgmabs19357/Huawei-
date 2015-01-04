#include <linux/uaccess.h>
#include <mach/gpio.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/crc-ccitt.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/hw_dev_dec.h>
#include <linux/hw_dev_array.h>
#include <hsad/config_interface.h>

#ifndef TYPEDEF_UINT8
typedef unsigned char	uint8;
#endif

#ifndef TYPEDEF_UINT16
typedef unsigned short	uint16;
#endif

#ifndef TYPEDEF_UINT32
typedef unsigned int	uint32;
#endif

#ifndef TYPEDEF_UINT64
typedef unsigned long long	uint64;
#endif

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

struct dev_flag_device{
    const char    *name;
    struct device    *dev;
    int        index;
};

static struct dev_flag_device dev_dct = {
    .name = "dev_flag",
    .index = 0,
};

static struct dev_flag_device boardid_dev_dct = {
    .name = "boardid_devcheck_flag",
    .index = 0,
};
static struct dev_flag_device rt_dev_dct = {
    .name = "rt_devcheck_flag",
    .index = 0,
};


static uint64 dev_flag_long = 0;
static uint64 boardid_devcheck_flag_long = 0;
static uint64 rt_devcheck_flag_long = 0;

/* set device flag */
int set_hw_dev_flag( int dev_id )
{
    if( (dev_id >= 0) && ( dev_id < DEV_I2C_MAX ) )
    {
        dev_flag_long = dev_flag_long | (1 << dev_id);
    }
    else
    {
        return false;
    }
    return true;
}

static ssize_t dev_flag_show(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    return sprintf((char *)buf, "%llu\n",dev_flag_long);
}

static ssize_t boardid_devcheck_flag_show(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    return sprintf((char *)buf, "%llu\n",boardid_devcheck_flag_long);
}

static ssize_t rt_devcheck_flag_show(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
{
    return sprintf((char *)buf, "%llu\n",rt_devcheck_flag_long);
}

static DEVICE_ATTR(dev_flag, S_IRUGO | S_IWUSR, dev_flag_show, NULL);

static DEVICE_ATTR(boardid_devcheck_flag, S_IRUGO | S_IWUSR, boardid_devcheck_flag_show, NULL);

static DEVICE_ATTR(rt_devcheck_flag, S_IRUGO | S_IWUSR, rt_devcheck_flag_show, NULL);


static int __devinit dev_dct_probe(struct platform_device *pdev)
{
    int ret = 0;
    int i;
    int type;
    struct class *myclass = class_create(THIS_MODULE, "dev_dct");
 //   struct class *boardid_devcheck_class = class_create(THIS_MODULE, "boardid_dev_dct");
    
    dev_dct.dev = device_create(myclass, NULL, MKDEV(0, dev_dct.index), NULL, dev_dct.name);
    ret = device_create_file(dev_dct.dev, &dev_attr_dev_flag);

    boardid_dev_dct.dev = device_create(myclass, NULL, MKDEV(0, boardid_dev_dct.index), NULL, boardid_dev_dct.name);
    ret = device_create_file(boardid_dev_dct.dev, &dev_attr_boardid_devcheck_flag);

    rt_dev_dct.dev = device_create(myclass, NULL, MKDEV(0,rt_dev_dct.index), NULL, rt_dev_dct.name);
    ret = device_create_file(rt_dev_dct.dev, &dev_attr_rt_devcheck_flag);

    for(i = 0;i<sizeof(hw_dec_device_array)/sizeof(hw_dec_struct);i++)
    {
        if(hw_dec_device_array[i].devices_id >= DEV_CONNECTIVITY_START && hw_dec_device_array[i].devices_id < DEV_CONNECTIVITY_MAX)
            type = get_connectivity_devices(hw_dec_device_array[i].devices_name);
        else
            type = get_I2C_devices(hw_dec_device_array[i].devices_name);
        if(type == 1 )
        {
            boardid_devcheck_flag_long = boardid_devcheck_flag_long | (1 << hw_dec_device_array[i].devices_id);

            if (hw_dec_device_array[i].devices_id >= DEV_I2C_START && hw_dec_device_array[i].devices_id < DEV_I2C_MAX){
                rt_devcheck_flag_long = rt_devcheck_flag_long | (1 << hw_dec_device_array[i].devices_id);
            }
	}
	else if(type == 2 )
        {
		if (hw_dec_device_array[i].devices_id >= DEV_I2C_START && hw_dec_device_array[i].devices_id < DEV_I2C_MAX){
			rt_devcheck_flag_long = rt_devcheck_flag_long | (1 << hw_dec_device_array[i].devices_id);
		}
        }
	else
	{
              printk("device check type:%d is not support!", type);
	}
    }
  
    return 0;
}

static struct platform_driver dev_dct_driver = {
    .driver = {
    .name   = "hw-dev-detect",
    },
    .probe  = dev_dct_probe,
    .remove = NULL,
};

static int __init hw_dev_dct_init(void)
{
    return platform_driver_register(&dev_dct_driver);
}

static void __exit hw_dev_dct_exit(void)
{
    platform_driver_unregister(&dev_dct_driver);
}

/* priority is 7s */
late_initcall_sync(hw_dev_dct_init);

module_exit(hw_dev_dct_exit);

MODULE_AUTHOR("sjm");
MODULE_DESCRIPTION("Device Detect Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dev_dct");

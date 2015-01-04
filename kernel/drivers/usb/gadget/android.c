/*
 * Gadget Driver for Android
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: Mike Lockwood <lockwood@android.com>
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

/* #define DEBUG */
/* #define VERBOSE_DEBUG */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/platform_device.h>

#include <linux/usb/ch9.h>
#include <linux/usb/composite.h>
#include <linux/usb/gadget.h>

#include "gadget_chips.h"

/*
 * Kbuild is not very cooperative with respect to linking separately
 * compiled library objects into one module.  So for now we won't use
 * separate compilation ... ensuring init/exit sections work to shrink
 * the runtime footprint, and giving us at least some parts of what
 * a "gcc --combine ... part1.c part2.c part3.c ... " build would.
 */
#include "usbstring.c"
#include "config.c"
#include "epautoconf.c"
#include "composite.c"

#include "f_mass_storage.c"
#include "u_serial.c"
#include "f_acm.c"
#include "f_serial.c"
#include "f_adb.c"
#include "f_mtp.c"
#include "f_accessory.c"
#define USB_ETH_RNDIS y
#include "f_rndis.c"
#include "rndis.c"
#include "u_ether.c"

MODULE_AUTHOR("Mike Lockwood");
MODULE_DESCRIPTION("Android Composite USB Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

static const char longname[] = "Gadget Android";

/* Default vendor and product IDs, overridden by userspace */
#define VENDOR_ID		0x12D1
#define PRODUCT_ID		0x1057
#define USB_DEVIEC_PLUGIN  1
#define USB_DEVIEC_PLUGOUT 2
#define USB_REQ_SEND_HOST_TIME    0xA2

struct android_usb_function {
	char *name;
	void *config;

	struct device *dev;
	char *dev_name;
	struct device_attribute **attributes;

	/* for android_dev.enabled_functions */
	struct list_head enabled_list;

	/* Optional: initialization during gadget bind */
	int (*init)(struct android_usb_function *, struct usb_composite_dev *);
	/* Optional: cleanup during gadget unbind */
	void (*cleanup)(struct android_usb_function *);

	int (*bind_config)(struct android_usb_function *, struct usb_configuration *);

	/* Optional: called when the configuration is removed */
	void (*unbind_config)(struct android_usb_function *, struct usb_configuration *);
	/* Optional: handle ctrl requests before the device is configured */
	int (*ctrlrequest)(struct android_usb_function *,
					struct usb_composite_dev *,
					const struct usb_ctrlrequest *);
};

struct android_dev {
	struct android_usb_function **functions;
	struct list_head enabled_functions;
	struct usb_composite_dev *cdev;
	struct device *dev;

	bool enabled;
	bool connected;
	bool sw_connected;
	bool disabled;
	struct work_struct work;
	struct work_struct	notify_work;
	int event;
};

struct _time {
    int            time_bias;
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short millisecond;
    unsigned short weekday;
};

static struct class *android_class;
static struct android_dev *_android_dev;
static int android_bind_config(struct usb_configuration *c);
static void android_unbind_config(struct usb_configuration *c);
static int android_function_supported_check(unsigned char * f_name); /* added by hisi-balong */
static int android_enable_function_check(unsigned char *f_name);
static int android_acm_debug_check(void);
static int android_setup_config(struct usb_configuration *c,
        const struct usb_ctrlrequest *ctrl);


/* string IDs are assigned dynamically */
#define STRING_MANUFACTURER_IDX		0
#define STRING_PRODUCT_IDX		1
#define STRING_SERIAL_IDX		2

static char manufacturer_string[256];
static char product_string[256];
static char serial_string[256];

/* String Table */
static struct usb_string strings_dev[] = {
	[STRING_MANUFACTURER_IDX].s = manufacturer_string,
	[STRING_PRODUCT_IDX].s = product_string,
	[STRING_SERIAL_IDX].s = serial_string,
	{  }			/* end of list */
};

static struct usb_gadget_strings stringtab_dev = {
	.language	= 0x0409,	/* en-us */
	.strings	= strings_dev,
};

static struct usb_gadget_strings *dev_strings[] = {
	&stringtab_dev,
	NULL,
};

static struct usb_device_descriptor device_desc = {
	.bLength              = sizeof(device_desc),
	.bDescriptorType      = USB_DT_DEVICE,
	.bcdUSB               = __constant_cpu_to_le16(0x0200),
	.bDeviceClass         = USB_CLASS_PER_INTERFACE,
	.idVendor             = __constant_cpu_to_le16(VENDOR_ID),
	.idProduct            = __constant_cpu_to_le16(PRODUCT_ID),
	.bcdDevice            = __constant_cpu_to_le16(0xffff),
	.bNumConfigurations   = 1,
};

static struct usb_configuration android_config_driver = {
	.label		= "android",
	.unbind		= android_unbind_config,
	.setup      = android_setup_config,
	.bConfigurationValue = 1,
	.bmAttributes	= USB_CONFIG_ATT_ONE | USB_CONFIG_ATT_SELFPOWER,
	.bMaxPower	= 0xFA, /* 500ma */
};

static struct usb_ctrlrequest android_ctrl_request;

ATOMIC_NOTIFIER_HEAD(android_usb_suspend_notifier_list);
ATOMIC_NOTIFIER_HEAD(android_usb_resume_notifier_list);

EXPORT_SYMBOL(android_usb_suspend_notifier_list);
EXPORT_SYMBOL(android_usb_resume_notifier_list);

static void android_work(struct work_struct *data)
{
	struct android_dev *dev = container_of(data, struct android_dev, work);
	struct usb_composite_dev *cdev = dev->cdev;
	char *disconnected[2] = { "USB_STATE=DISCONNECTED", NULL };
	char *connected[2]    = { "USB_STATE=CONNECTED", NULL };
	char *configured[2]   = { "USB_STATE=CONFIGURED", NULL };
	char *disabled[2]   = { "USB_STATE=SETPROP", NULL };
	char **uevent_envp = NULL;
	unsigned long flags;

	if (!cdev) {
		printk(KERN_ERR "the point cdev is NULL !\n");
		return;
	}
	
	spin_lock_irqsave(&cdev->lock, flags);
	if (dev->disabled)
	    uevent_envp = disabled;
	else if (cdev->config)
		uevent_envp = configured;
	else if (dev->connected != dev->sw_connected)
		uevent_envp = dev->connected ? connected : disconnected;
	dev->sw_connected = dev->connected;
	spin_unlock_irqrestore(&cdev->lock, flags);

	if (uevent_envp) {
        if (uevent_envp != disabled) {
		    kobject_uevent_env(&dev->dev->kobj, KOBJ_CHANGE, uevent_envp);
		}
		pr_info("%s: sent uevent %s\n", __func__, uevent_envp[0]);
	} else {
		pr_info("%s: did not send uevent (%d %d %p)\n", __func__,
			 dev->connected, dev->sw_connected, cdev->config);
	}
}


/*-------------------------------------------------------------------------*/
/* Supported functions initialization */

static int adb_function_init(struct android_usb_function *f, struct usb_composite_dev *cdev)
{
	pr_info("android_usb: enter %s\n", __func__);
	return adb_setup();
}

static void adb_function_cleanup(struct android_usb_function *f)
{
	pr_info("android_usb: enter %s\n", __func__);
	adb_cleanup();
}

static int adb_function_bind_config(struct android_usb_function *f, struct usb_configuration *c)
{
	pr_info("android_usb: enter %s\n", __func__);
	return adb_bind_config(c);
}

static struct android_usb_function adb_function = {
	.name		= "adb",
	.init		= adb_function_init,
	.cleanup	= adb_function_cleanup,
	.bind_config	= adb_function_bind_config,
};

#ifdef CONFIG_ARCH_HI6620
/* added by hisi-balong */
#define MAX_ACM_INSTANCES 7
#else
#define MAX_ACM_INSTANCES 4
#endif

struct acm_function_config {
	int instances;
};

static int acm_function_init(struct android_usb_function *f, struct usb_composite_dev *cdev)
{
	pr_info("android_usb: enter %s\n", __func__);
	f->config = kzalloc(sizeof(struct acm_function_config), GFP_KERNEL);
	if (!f->config)
		return -ENOMEM;

	/* Now, default enable one usb-serial port */
#ifdef CONFIG_ARCH_HI6620
	((struct acm_function_config *)(f->config))->instances = MAX_ACM_INSTANCES; /* added by hisi-balong */
#else
	((struct acm_function_config *)(f->config))->instances = 2;
#endif

	return gserial_setup(cdev->gadget, MAX_ACM_INSTANCES);
}

static void acm_function_cleanup(struct android_usb_function *f)
{
	pr_info("android_usb: enter %s\n", __func__);
	gserial_cleanup();
	kfree(f->config);
	f->config = NULL;
}

static int acm_function_bind_config(struct android_usb_function *f, struct usb_configuration *c)
{
	int i;
	int ret = 0;
	struct acm_function_config *config = f->config;
	printk(KERN_INFO "acm_function_bind_config, instances:%d.\n",
		config->instances);

	for (i = 0; i < config->instances; i++) {
		ret = gser_bind_config(c, i);
		if (ret) {
			pr_err("Could not bind ser%u config\n", i);
			break;
		}
	}

	return ret;
}

static ssize_t acm_instances_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct acm_function_config *config = f->config;
	return sprintf(buf, "%d\n", config->instances);

}

static ssize_t acm_instances_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct acm_function_config *config = f->config;
	int value;

	sscanf(buf, "%d", &value);
	if (value > MAX_ACM_INSTANCES)
		value = MAX_ACM_INSTANCES;
	config->instances = value;
	return size;
}

static DEVICE_ATTR(instances, S_IRUGO | S_IWUSR, acm_instances_show, acm_instances_store);
static struct device_attribute *acm_function_attributes[] = { &dev_attr_instances, NULL };

static struct android_usb_function acm_function = {
	.name		= "acm",
	.init		= acm_function_init,
	.cleanup	= acm_function_cleanup,
	.bind_config	= acm_function_bind_config,
	.attributes	= acm_function_attributes,
};


static int mtp_function_init(struct android_usb_function *f, struct usb_composite_dev *cdev)
{
	return mtp_setup();
}

static void mtp_function_cleanup(struct android_usb_function *f)
{
	mtp_cleanup();
}

static int mtp_function_bind_config(struct android_usb_function *f, struct usb_configuration *c)
{
	return mtp_bind_config(c, false);
}

static int ptp_function_init(struct android_usb_function *f, struct usb_composite_dev *cdev)
{
	/* nothing to do - initialization is handled by mtp_function_init */
	return 0;
}

static void ptp_function_cleanup(struct android_usb_function *f)
{
	/* nothing to do - cleanup is handled by mtp_function_cleanup */
}

static int ptp_function_bind_config(struct android_usb_function *f, struct usb_configuration *c)
{
	return mtp_bind_config(c, true);
}

static int mtp_function_ctrlrequest(struct android_usb_function *f,
						struct usb_composite_dev *cdev,
						const struct usb_ctrlrequest *c)
{
	return mtp_ctrlrequest(cdev, c);
}

static struct android_usb_function mtp_function = {
	.name		= "mtp",
	.init		= mtp_function_init,
	.cleanup	= mtp_function_cleanup,
	.bind_config	= mtp_function_bind_config,
	.ctrlrequest	= mtp_function_ctrlrequest,
};

/* PTP function is same as MTP with slightly different interface descriptor */
static struct android_usb_function ptp_function = {
	.name		= "ptp",
	.init		= ptp_function_init,
	.cleanup	= ptp_function_cleanup,
	.bind_config	= ptp_function_bind_config,
	.ctrlrequest	= mtp_function_ctrlrequest,
};


struct rndis_function_config {
	u8      ethaddr[ETH_ALEN];
	u32     vendorID;
	char	manufacturer[256];
	bool	wceis;
};

static int rndis_function_init(struct android_usb_function *f, struct usb_composite_dev *cdev)
{
	f->config = kzalloc(sizeof(struct rndis_function_config), GFP_KERNEL);
	if (!f->config)
		return -ENOMEM;
	return 0;
}

static void rndis_function_cleanup(struct android_usb_function *f)
{
	kfree(f->config);
	f->config = NULL;
}

static int rndis_function_bind_config(struct android_usb_function *f,
					struct usb_configuration *c)
{
	int ret;
	struct rndis_function_config *rndis = f->config;

	if (!rndis) {
		pr_err("%s: rndis_pdata\n", __func__);
		return -1;
	}

	pr_info("%s MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", __func__,
		rndis->ethaddr[0], rndis->ethaddr[1], rndis->ethaddr[2],
		rndis->ethaddr[3], rndis->ethaddr[4], rndis->ethaddr[5]);

	ret = gether_setup(c->cdev->gadget, rndis->ethaddr);
	if (ret) {
		pr_err("%s: gether_setup failed\n", __func__);
		return ret;
	}

	if (rndis->wceis) {
		/* "Wireless" RNDIS; auto-detected by Windows */
		rndis_iad_descriptor.bFunctionClass =
						USB_CLASS_WIRELESS_CONTROLLER;
		rndis_iad_descriptor.bFunctionSubClass = 0x01;
		rndis_iad_descriptor.bFunctionProtocol = 0x03;
		rndis_control_intf.bInterfaceClass =
						USB_CLASS_WIRELESS_CONTROLLER;
		rndis_control_intf.bInterfaceSubClass =	 0x01;
		rndis_control_intf.bInterfaceProtocol =	 0x03;
	}

	return rndis_bind_config(c, rndis->ethaddr, rndis->vendorID,
				    rndis->manufacturer);
}

static void rndis_function_unbind_config(struct android_usb_function *f,
						struct usb_configuration *c)
{
	gether_cleanup();
}

static ssize_t rndis_manufacturer_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;
	return sprintf(buf, "%s\n", config->manufacturer);
}

static ssize_t rndis_manufacturer_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;

	if (size >= sizeof(config->manufacturer))
		return -EINVAL;
	if (sscanf(buf, "%s", config->manufacturer) == 1)
		return size;
	return -1;
}

static DEVICE_ATTR(manufacturer, S_IRUGO | S_IWUSR, rndis_manufacturer_show,
						    rndis_manufacturer_store);

static ssize_t rndis_wceis_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;
	return sprintf(buf, "%d\n", config->wceis);
}

static ssize_t rndis_wceis_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;
	int value;

	if (sscanf(buf, "%d", &value) == 1) {
		config->wceis = value;
		return size;
	}
	return -EINVAL;
}

static DEVICE_ATTR(wceis, S_IRUGO | S_IWUSR, rndis_wceis_show,
					     rndis_wceis_store);

static ssize_t rndis_ethaddr_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *rndis = f->config;
	return sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x\n",
		rndis->ethaddr[0], rndis->ethaddr[1], rndis->ethaddr[2],
		rndis->ethaddr[3], rndis->ethaddr[4], rndis->ethaddr[5]);
}

static ssize_t rndis_ethaddr_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *rndis = f->config;

	if (sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x\n",
		    (int *)&rndis->ethaddr[0], (int *)&rndis->ethaddr[1],
		    (int *)&rndis->ethaddr[2], (int *)&rndis->ethaddr[3],
		    (int *)&rndis->ethaddr[4], (int *)&rndis->ethaddr[5]) == 6)
		return size;
	return -EINVAL;
}

static DEVICE_ATTR(ethaddr, S_IRUGO | S_IWUSR, rndis_ethaddr_show,
					       rndis_ethaddr_store);

static ssize_t rndis_vendorID_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;
	return sprintf(buf, "%04x\n", config->vendorID);
}

static ssize_t rndis_vendorID_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct rndis_function_config *config = f->config;
	int value;

	if (sscanf(buf, "%04x", &value) == 1) {
		config->vendorID = value;
		return size;
	}
	return -EINVAL;
}

static DEVICE_ATTR(vendorID, S_IRUGO | S_IWUSR, rndis_vendorID_show,
						rndis_vendorID_store);

static struct device_attribute *rndis_function_attributes[] = {
	&dev_attr_manufacturer,
	&dev_attr_wceis,
	&dev_attr_ethaddr,
	&dev_attr_vendorID,
	NULL
};

static struct android_usb_function rndis_function = {
	.name		= "rndis",
	.init		= rndis_function_init,
	.cleanup	= rndis_function_cleanup,
	.bind_config	= rndis_function_bind_config,
	.unbind_config	= rndis_function_unbind_config,
	.attributes	= rndis_function_attributes,
};


struct mass_storage_function_config {
	struct fsg_config fsg;
	struct fsg_common *common;
};

#define MS_STG_SET_LEN     	(32)
#define FSG_MAX_LUNS_HUAWEI	(2)
static char autorun[MS_STG_SET_LEN] = "enable";		/* enable/disable autorun function "enable"/"disable" */
static char luns[MS_STG_SET_LEN]    = "sdcard";		/* "sdcard"/"cdrom,sdcard"/"cdrom"/"sdcard,cdrom" can be used*/
static int mass_storage_function_init(struct android_usb_function *f,
					struct usb_composite_dev *cdev)
{
	struct mass_storage_function_config *config;
	struct fsg_common *common;
	int err;

	char *name = NULL;
	char buf[MS_STG_SET_LEN];
	char *b = NULL;
	memset(buf, 0, sizeof(buf));
	config = kzalloc(sizeof(struct mass_storage_function_config),
								GFP_KERNEL);
	pr_info("android_usb: enter %s\n", __func__);
	if (!config){
		pr_err("%s: %d failed\n", __func__, __LINE__);
		return -ENOMEM;
	}

	strlcpy(buf, luns, sizeof(buf));
	b = strim(buf);
	config->fsg.nluns = 0;
	while (b){
	        name = strsep(&b, ",");
	        if(name){
		        if(0==strcmp(name, "sdcard")){
				config->fsg.luns[config->fsg.nluns].cdrom = 0;
				config->fsg.luns[config->fsg.nluns].ro = 0;
				config->fsg.luns[config->fsg.nluns].removable = 1;
				config->fsg.luns[config->fsg.nluns].nofua = 0;
				config->fsg.nluns++;
				pr_info("mass_storage: %s, %d\n", name, config->fsg.nluns);
			}else if(0==strcmp(name, "cdrom")){
			        if(0==strcmp(autorun, "disable") ){
				        continue;
				}else if(0!=strcmp(autorun, "enable")){
				        pr_err("mass_storage: not support autorun type '%s' \n", autorun);
				        continue;
				}
				config->fsg.luns[config->fsg.nluns].cdrom = 1;
				config->fsg.luns[config->fsg.nluns].ro = 1;
				config->fsg.luns[config->fsg.nluns].removable = 1;
				config->fsg.luns[config->fsg.nluns].nofua = 1;
				config->fsg.nluns++;
				pr_info("mass_storage: %s, %d\n", name, config->fsg.nluns);
			}else{
				pr_err("mass_storage: not support storage type '%s' \n", name);
			}
		}
		if(config->fsg.nluns >= FSG_MAX_LUNS_HUAWEI){
                        pr_err("mass_storage: not support too many luns\n");
			break;
		}
	}

	common = fsg_common_init(NULL, cdev, &config->fsg);
	if (IS_ERR(common)) {
		kfree(config);
		pr_err("%s: %d failed\n", __func__, __LINE__);
		return PTR_ERR(common);
	}

	err = sysfs_create_link(&f->dev->kobj,
				&common->luns[0].dev.kobj,
				"lun");
	if (err) {
		kfree(config);
		pr_err("%s: %d failed\n", __func__, __LINE__);
		return err;
	}
	if(config->fsg.nluns > 1 ){
		err = sysfs_create_link(&f->dev->kobj,&common->luns[1].dev.kobj, "lun1");
		if (err)
		{
			sysfs_delete_link(&f->dev->kobj,&common->luns[0].dev.kobj, "lun");
			kfree(config);
			pr_err("%s: %d failed\n", __func__, __LINE__);
			return err;
		}
	}

	config->common = common;
	f->config = config;
	return 0;
}

static void mass_storage_function_cleanup(struct android_usb_function *f)
{
	pr_info("android_usb: enter %s\n", __func__);
	kfree(f->config);
	f->config = NULL;
}

static int mass_storage_function_bind_config(struct android_usb_function *f,
						struct usb_configuration *c)
{
	struct mass_storage_function_config *config = f->config;
	pr_info("android_usb: enter %s\n", __func__);
	return fsg_bind_config(c->cdev, c, config->common);
}

static ssize_t mass_storage_inquiry_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct mass_storage_function_config *config = f->config;
	return sprintf(buf, "%s\n", config->common->inquiry_string);
}

static ssize_t mass_storage_inquiry_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	struct android_usb_function *f = dev_get_drvdata(dev);
	struct mass_storage_function_config *config = f->config;
	if (size >= sizeof(config->common->inquiry_string))
		return -EINVAL;
	if (sscanf(buf, "%s", config->common->inquiry_string) != 1)
		return -EINVAL;
	return size;
}

static DEVICE_ATTR(inquiry_string, S_IRUGO | S_IWUSR,
					mass_storage_inquiry_show,
					mass_storage_inquiry_store);

#include "hw_msconfig.c"
#include "hw_hisuite.c"

static struct device_attribute *mass_storage_function_attributes[] = {
	&dev_attr_inquiry_string,
	&dev_attr_autorun,
	&dev_attr_luns,
	&dev_attr_suitestate,
	NULL
};

static struct android_usb_function mass_storage_function = {
	.name		= "mass_storage",
	.init		= mass_storage_function_init,
	.cleanup	= mass_storage_function_cleanup,
	.bind_config	= mass_storage_function_bind_config,
	.attributes	= mass_storage_function_attributes,
};


static int accessory_function_init(struct android_usb_function *f,
					struct usb_composite_dev *cdev)
{
	pr_info("android_usb: enter %s\n", __func__);
	return acc_setup();
}

static void accessory_function_cleanup(struct android_usb_function *f)
{
	pr_info("android_usb: enter %s\n", __func__);
	acc_cleanup();
}

static int accessory_function_bind_config(struct android_usb_function *f,
						struct usb_configuration *c)
{
	pr_info("android_usb: enter %s\n", __func__);
	return acc_bind_config(c);
}

static int accessory_function_ctrlrequest(struct android_usb_function *f,
						struct usb_composite_dev *cdev,
						const struct usb_ctrlrequest *c)
{
	pr_info("android_usb: enter %s\n", __func__);
	return acc_ctrlrequest(cdev, c);
}

static struct android_usb_function accessory_function = {
	.name		= "accessory",
	.init		= accessory_function_init,
	.cleanup	= accessory_function_cleanup,
	.bind_config	= accessory_function_bind_config,
	.ctrlrequest	= accessory_function_ctrlrequest,
};

#include "hw_modem_serial.c"

static struct android_usb_function *supported_functions[] = {
	&adb_function,
	&acm_function,
	&mtp_function,
	&ptp_function,
	&rndis_function,
	&mass_storage_function,
	&accessory_function,
#ifdef CONFIG_USB_F_SERIAL
	&nmea_function,
	&modem_function,
	&diag_function,
#endif
	NULL
};


static int android_init_functions(struct android_usb_function **functions,
				  struct usb_composite_dev *cdev)
{
	struct android_dev *dev = _android_dev;
	struct android_usb_function *f;
	struct device_attribute **attrs;
	struct device_attribute *attr;
	int err = 0;
	int index = 0;

	for (; (f = *functions++); index++) {
		f->dev_name = kasprintf(GFP_KERNEL, "f_%s", f->name);
		f->dev = device_create(android_class, dev->dev,
				MKDEV(0, index), f, f->dev_name);
		if (IS_ERR(f->dev)) {
			pr_err("%s: Failed to create dev %s", __func__,
							f->dev_name);
			err = PTR_ERR(f->dev);
			goto err_create;
		}

		if (f->init) {
			err = f->init(f, cdev);
			if (err) {
				pr_err("%s: Failed to init %s", __func__,
								f->name);
				goto err_out;
			}
		}

		attrs = f->attributes;
		if (attrs) {
			while ((attr = *attrs++) && !err)
				err = device_create_file(f->dev, attr);
		}
		if (err) {
			pr_err("%s: Failed to create function %s attributes",
					__func__, f->name);
			goto err_out;
		}

#ifdef CONFIG_ARCH_HI6620
        /* added by hisi-balong*/
        /* if it's acm device, just kick off usb shell */
        if (!strcmp(f->name, "acm")) {
            /* VID and PID supported now */
            if (__constant_cpu_to_le16(0x12d1) == device_desc.idVendor) {
                if ((__constant_cpu_to_le16(0x3a13) == device_desc.idProduct) ||
                    (__constant_cpu_to_le16(0x1057) == device_desc.idProduct)) {
                    usb_shell_init();
                }
            }
        }
        /* added by hisi-balong */
#endif
	}
	return 0;

err_out:
	device_destroy(android_class, f->dev->devt);
err_create:
	kfree(f->dev_name);
	return err;
}

static void android_cleanup_functions(struct android_usb_function **functions)
{
	struct android_usb_function *f;

	while (*functions) {
		f = *functions++;

		if (f->dev) {
			device_destroy(android_class, f->dev->devt);
			kfree(f->dev_name);
		}

		if (f->cleanup)
			f->cleanup(f);
	}
}

static int
android_bind_enabled_functions(struct android_dev *dev,
			       struct usb_configuration *c)
{
	struct android_usb_function *f;
	int ret;

	list_for_each_entry(f, &dev->enabled_functions, enabled_list) {
		ret = f->bind_config(f, c);
		if (ret) {
			pr_err("%s: %s failed", __func__, f->name);
			return ret;
		}
	}
	return 0;
}

static void
android_unbind_enabled_functions(struct android_dev *dev,
			       struct usb_configuration *c)
{
	struct android_usb_function *f;

	list_for_each_entry(f, &dev->enabled_functions, enabled_list) {
		if (f->unbind_config)
			f->unbind_config(f, c);
	}
}

static int android_enable_function(struct android_dev *dev, char *name)
{
	struct android_usb_function **functions = dev->functions;
	struct android_usb_function *f;
	while ((f = *functions++)) {
		if (!strcmp(name, f->name)) {
			list_add_tail(&f->enabled_list, &dev->enabled_functions);
			return 0;
		}
	}
	return -EINVAL;
}

/*-------------------------------------------------------------------------*/
/* /sys/class/android_usb/android%d/ interface */

static ssize_t
functions_show(struct device *pdev, struct device_attribute *attr, char *buf)
{
	struct android_dev *dev = dev_get_drvdata(pdev);
	struct android_usb_function *f;
	char *buff = buf;

	list_for_each_entry(f, &dev->enabled_functions, enabled_list)
		buff += sprintf(buff, "%s,", f->name);
	if (buff != buf)
		*(buff-1) = '\n';
	return buff - buf;
}

static ssize_t
functions_store(struct device *pdev, struct device_attribute *attr,
			       const char *buff, size_t size)
{
	struct android_dev *dev = dev_get_drvdata(pdev);
	char *name;
	char buf[256], *b;
	int err;

	INIT_LIST_HEAD(&dev->enabled_functions);

	strncpy(buf, buff, sizeof(buf));
	b = strim(buf);

	while (b) {
		name = strsep(&b, ",");
		pr_info("android_usb: enable '%s'\n", name);
		if (name) {
			err = android_enable_function(dev, name);
			if (err)
				pr_err("android_usb: Cannot enable '%s'", name);
		}
	}

	return size;
}

static ssize_t enable_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
	struct android_dev *dev = dev_get_drvdata(pdev);
	return sprintf(buf, "%d\n", dev->enabled);
}

static ssize_t enable_store(struct device *pdev, struct device_attribute *attr,
			    const char *buff, size_t size)
{
	struct android_dev *dev = dev_get_drvdata(pdev);
	struct usb_composite_dev *cdev = dev->cdev;
	int enabled = 0;

	sscanf(buff, "%d", &enabled);
    if (!enabled) {
        port_num = 0;
        gser_num = 0;
        rndis_num = 0;
       }
    if (!strcmp(serial_string, "cleanup"))
    {
        cdev->desc.iSerialNumber = 0;
        memset(serial_string, 0, 256);
    }
    else
    {
        cdev->desc.iSerialNumber = device_desc.iSerialNumber;
    }
	if (enabled && !dev->enabled) {
		/* update values in composite driver's copy of device descriptor */
		cdev->desc.idVendor = device_desc.idVendor;
		cdev->desc.idProduct = device_desc.idProduct;
		cdev->desc.bcdDevice = device_desc.bcdDevice;
		cdev->desc.bDeviceClass = device_desc.bDeviceClass;
		cdev->desc.bDeviceSubClass = device_desc.bDeviceSubClass;
		cdev->desc.bDeviceProtocol = device_desc.bDeviceProtocol;
		usb_add_config(cdev, &android_config_driver,
					android_bind_config);
		usb_gadget_connect(cdev->gadget);
		dev->enabled = true;
	} else if (!enabled && dev->enabled) {	
		usb_gadget_disconnect(cdev->gadget);

		if(android_acm_debug_check())
		{
		    /* Disconnect for usb setprop */
		    atomic_notifier_call_chain(&android_usb_suspend_notifier_list, 0, 0);

			dev->disabled = 1;
			dev->event = USB_DEVIEC_PLUGOUT;
			schedule_work(&dev->notify_work);
			do
			{  
				mdelay(10);
			}while(dev->disabled == 1);
		}
		
		usb_remove_config(cdev, &android_config_driver);
		dev->enabled = false;
		cdev->next_string_id = 0;
	} else {
		pr_err("android_usb: already %s\n",
				dev->enabled ? "enabled" : "disabled");
	}
	return size;
}

static ssize_t portNum_show(struct device *pdev, struct device_attribute *attr,
                       char *buf)
{
        return sprintf(buf, "%d\n", port_num);
}

static ssize_t portNum_store(struct device *pdev, struct device_attribute *attr,
                        const char *buf, size_t size)
{
     int value;
     if (sscanf(buf, "%04x\n", &value) == 1) {
         port_num = value;
         printk("port_num: %04x\n", value);
         return size;
     }
     return -1;
}

static ssize_t state_show(struct device *pdev, struct device_attribute *attr,
			   char *buf)
{
	struct android_dev *dev = dev_get_drvdata(pdev);
	struct usb_composite_dev *cdev = dev->cdev;
	char *state = "DISCONNECTED";
	unsigned long flags;

	if (!cdev)
		goto out;

	spin_lock_irqsave(&cdev->lock, flags);
        if (cdev->config)
		state = "CONFIGURED";
	else if (dev->connected)
		state = "CONNECTED";
	spin_unlock_irqrestore(&cdev->lock, flags);
out:
	return sprintf(buf, "%s\n", state);
}

#define DESCRIPTOR_ATTR(field, format_string)				\
static ssize_t								\
field ## _show(struct device *dev, struct device_attribute *attr,	\
		char *buf)						\
{									\
	return sprintf(buf, format_string, device_desc.field);		\
}									\
static ssize_t								\
field ## _store(struct device *dev, struct device_attribute *attr,	\
		const char *buf, size_t size)		       		\
{									\
	int value;					       		\
	if (sscanf(buf, format_string, &value) == 1) {			\
		device_desc.field = value;				\
		return size;						\
	}								\
	return -1;							\
}									\
static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, field ## _show, field ## _store);

#define DESCRIPTOR_STRING_ATTR(field, buffer)				\
static ssize_t								\
field ## _show(struct device *dev, struct device_attribute *attr,	\
		char *buf)						\
{									\
	return sprintf(buf, "%s", buffer);				\
}									\
static ssize_t								\
field ## _store(struct device *dev, struct device_attribute *attr,	\
		const char *buf, size_t size)		       		\
{									\
	if (size >= sizeof(buffer)) return -EINVAL;			\
	if (sscanf(buf, "%s", buffer) == 1) {			       	\
		return size;						\
	}								\
	return -1;							\
}									\
static DEVICE_ATTR(field, S_IRUGO | S_IWUSR, field ## _show, field ## _store);


DESCRIPTOR_ATTR(idVendor, "%04x\n")
DESCRIPTOR_ATTR(idProduct, "%04x\n")
DESCRIPTOR_ATTR(bcdDevice, "%04x\n")
DESCRIPTOR_ATTR(bDeviceClass, "%d\n")
DESCRIPTOR_ATTR(bDeviceSubClass, "%d\n")
DESCRIPTOR_ATTR(bDeviceProtocol, "%d\n")
DESCRIPTOR_STRING_ATTR(iManufacturer, manufacturer_string)
DESCRIPTOR_STRING_ATTR(iProduct, product_string)
DESCRIPTOR_STRING_ATTR(iSerial, serial_string)

static DEVICE_ATTR(functions, S_IRUGO | S_IWUSR, functions_show, functions_store);
static DEVICE_ATTR(enable, S_IRUGO | S_IWUSR, enable_show, enable_store);
static DEVICE_ATTR(state, S_IRUGO, state_show, NULL);
static DEVICE_ATTR(portNum, S_IRUGO | S_IWUSR, portNum_show, portNum_store);

#include "hw_rwswitch.c"

static struct device_attribute *android_usb_attributes[] = {
	&dev_attr_idVendor,
	&dev_attr_idProduct,
	&dev_attr_bcdDevice,
	&dev_attr_bDeviceClass,
	&dev_attr_bDeviceSubClass,
	&dev_attr_bDeviceProtocol,
	&dev_attr_iManufacturer,
	&dev_attr_iProduct,
	&dev_attr_iSerial,
	&dev_attr_functions,
	&dev_attr_enable,
	&dev_attr_state,
	&dev_attr_portNum,
	&dev_attr_switch_request,
	NULL
};

/*-------------------------------------------------------------------------*/
/* Composite driver */
static void android_handle_host_time(struct usb_ep *ep, struct usb_request *req)
{
    struct _time *host_time;

    host_time = (struct _time *)req->buf;

    printk("Time Bias:%d minutes\n", host_time->time_bias);

    printk("Host Time:[%d:%d:%d %d:%d:%d:%d Weekday:%d]\n", host_time->year,
            host_time->month, host_time->day, host_time->hour, host_time->minute,
            host_time->second, host_time->millisecond, host_time->weekday);

    return;
}

static int android_bind_config(struct usb_configuration *c)
{
	struct android_dev *dev = _android_dev;
	int ret = 0;

	ret = android_bind_enabled_functions(dev, c);
	if (ret)
		return ret;

	return 0;
}

static void android_unbind_config(struct usb_configuration *c)
{
	struct android_dev *dev = _android_dev;

	android_unbind_enabled_functions(dev, c);
}

static int android_setup_config(struct usb_configuration *c,
        const struct usb_ctrlrequest *ctrl)
{
    struct usb_composite_dev *cdev = c->cdev;
    struct usb_request *req = cdev->req;
    u16     w_index  = le16_to_cpu(ctrl->wIndex);
    u16     w_value  = le16_to_cpu(ctrl->wValue);
    u16     w_length = le16_to_cpu(ctrl->wLength);
    int     value    = -EOPNOTSUPP;

    /*
     * for MBB spec command such like "40 A2",
     * to support any other commands, add here.
     */
    switch (ctrl->bRequestType) {
    case (USB_DIR_OUT | USB_TYPE_VENDOR):
        switch (ctrl->bRequest) {
        case (USB_REQ_SEND_HOST_TIME):
            /*
             * "40 A1"-The host sends sys-time to device
             */
            memcpy((void *)&android_ctrl_request, (void *)ctrl,
                    sizeof(struct usb_ctrlrequest));
            req->context = &android_ctrl_request;
            req->complete = android_handle_host_time;
            cdev->gadget->ep0->driver_data = cdev;
            value = w_length;
            break;

        default:
            pr_warning("invalid control req%02x.%02x v%04x i%04x l%d\n",
                ctrl->bRequestType, ctrl->bRequest,	w_value, w_index, w_length);
            break;
        }
        break;

    default:
        pr_warning("invalid control req%02x.%02x v%04x i%04x l%d\n",
            ctrl->bRequestType, ctrl->bRequest,	w_value, w_index, w_length);
        break;
    }

    /* respond with data transfer or status phase? */
    if (value >= 0) {
        req->zero = 0;
        req->length = value;
        value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
        if (value < 0) {
            pr_warning("android_setup_config response err 0x%x\n", value);
        }
    }

    return value;
}

static int android_bind(struct usb_composite_dev *cdev)
{
	struct android_dev *dev = _android_dev;
	struct usb_gadget	*gadget = cdev->gadget;
	int			gcnum, id, ret;

	usb_gadget_disconnect(gadget);

	ret = android_init_functions(dev->functions, cdev);
	if (ret)
		return ret;

	/* Allocate string descriptor numbers ... note that string
	 * contents can be overridden by the composite_dev glue.
	 */
	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_MANUFACTURER_IDX].id = id;
	device_desc.iManufacturer = id;

	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_PRODUCT_IDX].id = id;
	device_desc.iProduct = id;

	/* Default strings - should be updated by userspace */
	strncpy(manufacturer_string, "Android", sizeof(manufacturer_string) - 1);
	strncpy(product_string, "Android", sizeof(product_string) - 1);
	strncpy(serial_string, "0123456789ABCDEF", sizeof(serial_string) - 1);

	id = usb_string_id(cdev);
	if (id < 0)
		return id;
	strings_dev[STRING_SERIAL_IDX].id = id;
	device_desc.iSerialNumber = id;

	if (gadget->ops->wakeup)
		android_config_driver.bmAttributes |= USB_CONFIG_ATT_WAKEUP;
	gcnum = usb_gadget_controller_number(gadget);
	if (gcnum >= 0)
		device_desc.bcdDevice = cpu_to_le16(0x0200 + gcnum);
	else {
		/* gadget zero is so simple (for now, no altsettings) that
		 * it SHOULD NOT have problems with bulk-capable hardware.
		 * so just warn about unrcognized controllers -- don't panic.
		 *
		 * things like configuration and altsetting numbering
		 * can need hardware-specific attention though.
		 */
		pr_warning("%s: controller '%s' not recognized\n",
			longname, gadget->name);
		device_desc.bcdDevice = __constant_cpu_to_le16(0x9999);
	}

	usb_gadget_set_selfpowered(gadget);
	dev->cdev = cdev;

	/* enable functions. */
	// functions_store(dev->dev, NULL, "ptp,acm,adb", sizeof("ptp,acm,adb"));
	// enable_store(dev->dev, NULL, "1", sizeof("1"));

	return 0;
}

static int android_usb_unbind(struct usb_composite_dev *cdev)
{
	struct android_dev *dev = _android_dev;

	cancel_work_sync(&dev->work);
	cancel_work_sync(&dev->notify_work);
	android_cleanup_functions(dev->functions);
	return 0;
}

static void android_usb_suspend(struct usb_composite_dev *cdev)
{
    pr_info("%s: enter\n", __func__);

    if (android_acm_debug_check()) {
        atomic_notifier_call_chain(&android_usb_suspend_notifier_list, 0, 0);
    }

    return;
}

static void android_usb_resume(struct usb_composite_dev *cdev)
{
    /*atomic_notifier_call_chain(&android_usb_resume_notifier_list, 0, 0);*/
    return;
}

static struct usb_composite_driver android_usb_driver = {
	.name		= "android_usb",
	.dev		= &device_desc,
	.strings	= dev_strings,
	.unbind		= android_usb_unbind,
	.suspend    = android_usb_suspend,
	.resume     = android_usb_resume,
};

static int
android_setup(struct usb_gadget *gadget, const struct usb_ctrlrequest *c)
{
	struct android_dev		*dev = _android_dev;
	struct usb_composite_dev	*cdev = NULL;
	struct usb_request		*req = NULL;    
	struct android_usb_function	*f;
	int value = -EOPNOTSUPP;
	unsigned long flags;

	cdev = get_gadget_data(gadget);
	if (!cdev) {
		printk(KERN_ERR "the point cdev is NULL !\n");
		return -1;
	}
	req = cdev->req;
	req->zero = 0;
	req->complete = composite_setup_complete;
	req->length = 0;
	gadget->ep0->driver_data = cdev;

	list_for_each_entry(f, &dev->enabled_functions, enabled_list) {
		if (f->ctrlrequest) {
			value = f->ctrlrequest(f, cdev, c);
			if (value >= 0)
				break;
		}
	}

	/* Special case the accessory function.
	 * It needs to handle control requests before it is enabled.
	 */
	if (value < 0)
		value = acc_ctrlrequest(cdev, c);

	if (value < 0)
		value = composite_setup(gadget, c);

	spin_lock_irqsave(&cdev->lock, flags);
	if (!dev->connected) {
		dev->connected = 1;
		schedule_work(&dev->work);
		pr_info("android_setup connected\n");
	}
	else if (c->bRequest == USB_REQ_SET_CONFIGURATION && cdev->config) {
		schedule_work(&dev->work);

		dev->event = USB_DEVIEC_PLUGIN;
		schedule_work(&dev->notify_work);
		pr_info("android_setup configured\n");
	}
	spin_unlock_irqrestore(&cdev->lock, flags);

	return value;
}

static void android_disconnect(struct usb_gadget *gadget)
{
    struct android_dev *dev = _android_dev;
    struct usb_composite_dev *cdev = NULL;
    unsigned long flags;

    if (!dev) {
        printk(KERN_ERR "the point dev is NULL !\n");
        return;
    }

    cdev = dev->cdev;
    if (!cdev) {
        printk(KERN_ERR "the point cdev is NULL !\n");
        return;
    }
    /* for usb invalid such like unplugged */
    if (android_acm_debug_check()) {
        atomic_notifier_call_chain(&android_usb_suspend_notifier_list, 0, 0);
    }

    composite_disconnect(gadget);

    spin_lock_irqsave(&cdev->lock, flags);
    dev->connected = 0;
    schedule_work(&dev->work);

    dev->event = USB_DEVIEC_PLUGOUT;
    schedule_work(&dev->notify_work);

    spin_unlock_irqrestore(&cdev->lock, flags);

    pr_info("android_disconnect \n");
}

static int android_create_device(struct android_dev *dev)
{
	struct device_attribute **attrs = android_usb_attributes;
	struct device_attribute *attr;
	int err;

	dev->dev = device_create(android_class, NULL,
					MKDEV(0, 0), NULL, "android0");
	if (IS_ERR(dev->dev))
		return PTR_ERR(dev->dev);

	dev_set_drvdata(dev->dev, dev);

	while ((attr = *attrs++)) {
		err = device_create_file(dev->dev, attr);
		if (err) {
			device_destroy(android_class, dev->dev->devt);
			return err;
		}
	}
	return 0;
}

static void android_notify(struct work_struct *data)
{
    struct android_dev *dev = _android_dev;
    pr_info("android_notify %d enter\n",dev->event);

    if (!android_acm_debug_check()) {
        pr_warning("android_notify acm not exist [%d] \n", dev->event);
        return;
    }

    if (USB_DEVIEC_PLUGIN == dev->event)
    {
        BSP_USB_UdiEnableNotify();
        atomic_notifier_call_chain(&android_usb_resume_notifier_list, 0, 0);
    }
    else if(USB_DEVIEC_PLUGOUT == dev->event)
    {
        BSP_USB_UdiDisableNotify();
        dev->disabled = 0;
    }
    else
    {
        printk("android_notify event[%d] error\n",dev->event);
    }
    pr_info("android_notify leave [%d]\n",dev->disabled);
}

static int __init init(void)
{
	struct android_dev *dev;
	int err;

	android_class = class_create(THIS_MODULE, "android_usb");
	if (IS_ERR(android_class))
		return PTR_ERR(android_class);

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;

	dev->functions = supported_functions;
	INIT_LIST_HEAD(&dev->enabled_functions);
	INIT_WORK(&dev->work, android_work);

	INIT_WORK(&dev->notify_work, android_notify);
	dev->event = 0;

	err = android_create_device(dev);
	if (err) {
		class_destroy(android_class);
		kfree(dev);
		return err;
	}

    dev->disabled = 0;
	_android_dev = dev;

	/* Override composite driver functions */
	composite_driver.setup = android_setup;
	composite_driver.disconnect = android_disconnect;

	return usb_composite_probe(&android_usb_driver, android_bind);
}

module_init(init);

static void __exit cleanup(void)
{
	usb_composite_unregister(&android_usb_driver);
	class_destroy(android_class);
	kfree(_android_dev);
	_android_dev = NULL;
}
module_exit(cleanup);

/* added by hisi-balong */
/**
 * android_function_supported_check() - check whether the usb function supported
 * @f_name: the function name
 * Return of '1' means the function supported, 0 means unsupported .
 */
static int android_function_supported_check(unsigned char *f_name)
{
    int size = 0;
    int i = 0;

    size = sizeof(supported_functions)/sizeof(struct android_usb_function *);
    for (i = 0; i < size; i++) {
        if (!strcmp(supported_functions[i]->name, f_name)) {
            return 1;
        }
    }

    return 0;
}
/* added by hisi-balong */

/**
 * android_enable_function_check() - check whether the usb function exists
 * @f_name: the function name
 * Return of '1' means the function exist, 0 means non-exist .
 */
static int android_enable_function_check(unsigned char *f_name)
{
	struct android_dev *dev = _android_dev;
	struct android_usb_function *f;

	list_for_each_entry(f, &dev->enabled_functions, enabled_list)
	{   
		if (!strcmp(f->name, f_name)) 
		{
			return 1;
		}
	}
	return 0;
}

/**
 * android_acm_debug_check() - check whether the usb is in debug mode, that
 * means all acm ports are used for debug and follow our own rules but tty's
 * Return of '1' means in debug mode, 0 but others .
 */
static int android_acm_debug_check(void)
{
    /**
    * besides the acm, the vid and pid must be the specific one
    */
    if (android_enable_function_check("acm")) {
        if (__constant_cpu_to_le16(0x12d1) == device_desc.idVendor) {
            if ((__constant_cpu_to_le16(0x3a13) == device_desc.idProduct) ||
                (__constant_cpu_to_le16(0x1057) == device_desc.idProduct)) {
                return 1;
            }
        }
    }
	return 0;
}


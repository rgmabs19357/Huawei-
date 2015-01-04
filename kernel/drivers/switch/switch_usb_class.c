/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_usb_class.c
* Author: lixiuna(00213837)       Version : 0.1      Date:  2013-11-06
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
*  Description:    .c adatper file for USBSwitch
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/switch_usb.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <asm/mach/irq.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/syscalls.h>
#include <linux/notifier.h>
#include <linux/switch_usb.h>
#include "switch_usb_class.h"
#include <hsad/config_mgr.h>
#include "switch_chip.h"

#define PLAT_K3V3   0
#define PLAT_V9R1   1
#define USE_DTS     0
#define USE_BOARDID 1

static struct switch_usb_dev sdev;
#if USE_NOTIFY_CHAIN
static struct switch_usb_info *p_switch_usb_info = NULL;
#endif
static int gpio_switch_back = -1;
static int switch_usb_set_state(struct switch_usb_dev *sdev, int state);
struct class *switch_usb_class=NULL;

int get_swstate_value(void)
{
    return sdev.state;
}
EXPORT_SYMBOL_GPL(get_swstate_value);

void switch_usb2_access_through_ap(void)
{
    int ret = 0;
    ret = fsa9685_manual_sw(FSA9685_USB2);
    if (ret < 0)
        printk(KERN_ERR "%s: error. ret = %d" ,__func__, ret);
}
EXPORT_SYMBOL_GPL(switch_usb2_access_through_ap);

//switch USB state to AP due to gpio go to up
static void usb_switch_work(struct work_struct *work)
{
    switch_usb_set_state(&sdev, USB_TO_AP);
}
EXPORT_SYMBOL_GPL(usb_switch_work);

//Handle gpio irq function
static irqreturn_t int_gpio_irq_handler(int irq, void *dev_id)
{
    int int_gpio_value1 = 0;

    printk(KERN_INFO "%s++\n", __func__);

    if (gpio_switch_back >= 0)
    {
        int_gpio_value1 = gpio_get_value(gpio_switch_back);
        printk(KERN_INFO "%s: int_gpio_value1 = %d\n", __func__, int_gpio_value1);
        if (GPIO_HI == int_gpio_value1) {
            schedule_work(&sdev.work);
        }
    }else {
        printk(KERN_ERR "%s no gpio_switch_back\n", __func__);
    }
    printk(KERN_INFO "%s--\n", __func__);
    return IRQ_HANDLED;
}

//Show and Store function for sys node
static ssize_t usb_state_show(struct device *dev, struct device_attribute *attr,
        char *buf)
{
    struct switch_usb_dev *sdev = (struct switch_usb_dev *)
        dev_get_drvdata(dev);

    return sprintf(buf, "%d\n", sdev->state);
}


static ssize_t usb_state_store(struct device *dev,
        struct device_attribute *attr, const char *buf, size_t size)
{
    struct switch_usb_dev *sdev = (struct switch_usb_dev *)
                dev_get_drvdata(dev);
    int state;

    sscanf(buf, "%d", &state);

    if (switch_usb_set_state(sdev, state) < 0) {
        printk(KERN_ERR "%s: switch_usb_set_state %d err\n", __func__, state);
        return -EINVAL;
    }

    return size;
}

#if USE_NOTIFY_CHAIN
static void notify_switch_state(int state)
{
    atomic_notifier_call_chain(&p_switch_usb_info->charger_type_notifier_head,
                state, NULL);
    printk(KERN_INFO "%s: state = %d\n", __func__, state);
}
#endif

static void set_reg_to_target_state(int state)
{
    int ret = 0;

    printk(KERN_INFO "%s++ state = %d" ,__func__, state);

    switch(state){
    case USB_TO_AP:
        ret = fsa9685_manual_sw(FSA9685_USB1);
        break;
    case USB_TO_MODEM1:
        ret = fsa9685_manual_sw(FSA9685_USB2);
        break;
    case USB_OFF:
        fsa9685_manual_sw(FSA9685_OPEN);
        break;
    default:
        printk(KERN_ERR "%s: state[%d] is error!!!\n", __func__, state);
        break;
    }
    printk(KERN_INFO "%s--" ,__func__);
}

//Store usb state to sys node
static int switch_usb_set_state(struct switch_usb_dev *sdev, int state)
{
    int ret = 0;
    struct usb_switch_platform_data *pdata = sdev->pdata;
    BUG_ON(pdata == NULL);

    if ((state < USB_TO_AP) || (state > USB_OFF))
    {
        printk(KERN_ERR "%s error swstate[%d] is invalid\n", __func__, state);
        ret = -EINVAL;
        return ret;
    }

    if (sdev->state == state)
    {
        printk(KERN_INFO "%s: swstate is not changed. sdev->state[%d] and state[%d]\n", __func__, sdev->state, state);
        ret = -EINVAL;
        return ret;
    }

    set_reg_to_target_state(USB_OFF);
    msleep (1000);

    if (state != USB_OFF)
    {
        set_reg_to_target_state(state);
    }

    // update the sys value
    sdev->state = state;
#if USE_NOTIFY_CHAIN
    notify_switch_state(state);
#endif
    return ret;
}

static DEVICE_ATTR(swstate, S_IRUGO | S_IWUSR, usb_state_show, usb_state_store);
#if USE_NOTIFY_CHAIN
//register notifier function to notify usb state switch
int switch_usb_register_notifier(struct notifier_block *nb)
{
    unsigned long flags;
    int ret = -1;
    if(p_switch_usb_info != NULL) {
        spin_lock_irqsave(&p_switch_usb_info->reg_flag_lock, flags);
        ret = atomic_notifier_chain_register(
                &p_switch_usb_info->charger_type_notifier_head, nb);
        spin_unlock_irqrestore(&p_switch_usb_info->reg_flag_lock, flags);
    }
    return ret;
}
EXPORT_SYMBOL_GPL(switch_usb_register_notifier);



int switch_usb_unregister_notifier(struct notifier_block *nb)
{
    unsigned long flags;
    int ret = -1;
    if(p_switch_usb_info != NULL) {
        spin_lock_irqsave(&p_switch_usb_info->reg_flag_lock, flags);
        ret = atomic_notifier_chain_unregister(
                &p_switch_usb_info->charger_type_notifier_head, nb);
        spin_unlock_irqrestore(&p_switch_usb_info->reg_flag_lock, flags);
    }
    return ret;
}
EXPORT_SYMBOL_GPL(switch_usb_unregister_notifier);
#endif

static int create_switch_usb_class(void)
{
    if (NULL==switch_usb_class) {
        switch_usb_class = class_create(THIS_MODULE, "usbswitch");
        if (IS_ERR(switch_usb_class)){
            printk(KERN_ERR "%s  error %p\n",__func__, switch_usb_class);
            return PTR_ERR(switch_usb_class);
        }
    }

    return 0;
}

static int switch_usb_dev_register(struct switch_usb_dev *sdev)
{
    int ret = 0;

    if (IS_ERR_OR_NULL(switch_usb_class)) {
        ret = create_switch_usb_class();
        if (ret < 0)
        {
            goto err_create_file;
        }
    }

    sdev->dev = device_create(switch_usb_class, NULL,
        MKDEV(0, 0), NULL, sdev->name);
    if (IS_ERR(sdev->dev))
    {
        ret = PTR_ERR(sdev->dev);
        goto err_create_file;
    }

    return 0;

err_create_file:
    printk(KERN_ERR "%s Failed to register driver %s\n",__func__, sdev->name);

    return ret;
}


static void switch_usb_dev_unregister(struct switch_usb_dev *sdev)
{
    device_destroy(switch_usb_class, MKDEV(0, 0));
}


//Config DTS information
#ifdef CONFIG_OF
static const struct of_device_id platform_usbswitch_ids[] = {
    { .compatible = "huawei,usbswitch" },
    {},
};
MODULE_DEVICE_TABLE(of, platform_usbswitch_ids);
#endif

static int usb_switch_probe(struct platform_device *pdev)
{
    struct usb_switch_platform_data *pdata = pdev->dev.platform_data;
#if USE_DTS
    struct device_node *node = pdev->dev.of_node;
#endif
    int ret = 0;
    int use_switch_driver = 0;
    printk(KERN_INFO "%s++\n", __func__);

#if USE_BOARDID
    ret = get_hw_config_int("usb/use_switch_driver", &use_switch_driver, NULL);
#endif
    if (!ret || use_switch_driver == 0){
        printk(KERN_ERR "%s no use_switch_driver\n", __func__);
        ret = -1;
        goto err_switch_usb_dev_register;
    }

    if (!pdata){
        printk(KERN_ERR "%s-- no pdata\n", __func__);
        return -EBUSY;
    }

    sdev.pdata = pdata;
    sdev.name = pdev->name;

    INIT_WORK(&sdev.work, usb_switch_work);

    ret = switch_usb_dev_register(&sdev);
    if (ret < 0){
        printk(KERN_ERR "%s reg dev\n", __func__);
        goto err_switch_usb_dev_register;
    }

    ret = device_create_file(sdev.dev, &dev_attr_swstate);
    if (ret < 0){
        printk(KERN_ERR "%s create dev file\n", __func__);
        goto err_switch_usb_dev_register;
    }
    dev_set_drvdata(sdev.dev, &sdev);
    sdev.state = USB_TO_AP;
#if 0
#if USE_DTS
    gpio_switch_back = of_get_named_gpio(node, "gpio_switch_back", 0);
#endif
#if USE_BOARDID
    ret = get_hw_config_int("usb/gpio_switch_back", &gpio_switch_back, NULL);
#endif
    if (!ret || gpio_switch_back < 0)
        goto err_of_get_named_gpio;

#if PLAT_K3V3
    sdev.irq1 = gpio_to_irq(gpio_switch_back);
#endif
#if PLAT_V9R1
    sdev.irq1 = IRQ_GPIO(gpio_switch_back);
#endif
    if (sdev.irq1 < 0) {
        ret = sdev.irq1;
        goto err_detect_irq_num_failed1;
    }

    ret = gpio_request(gpio_switch_back, "usb_sw_interrupt1");
    if (ret < 0){
        printk(KERN_ERR "%s gpio request %d error\n", __func__, gpio_switch_back);
        goto err_request_int_gpio1;
    }

    ret = gpio_direction_input(gpio_switch_back);
    if (ret < 0){
        printk(KERN_ERR "%s gpio set dir %d error\n", __func__, gpio_switch_back);
        goto err_set_gpio_input1;
    }

    ret = request_irq(sdev.irq1, int_gpio_irq_handler,
                pdata->irq_flags, "usb_sw_interrupt1", &sdev);
    if (ret < 0){
        printk(KERN_ERR "%s request irq %d error\n", __func__, sdev.irq1);
        goto err_request_irq1;
    }
    disable_irq(sdev.irq1);
#endif
    printk(KERN_INFO "%s-- OK\n", __func__);
    return 0;

err_request_irq1:
err_detect_irq_num_failed1:
err_set_gpio_input1:
    gpio_free(gpio_switch_back);
err_of_get_named_gpio:
err_request_int_gpio1:
    switch_usb_dev_unregister(&sdev);
err_switch_usb_dev_register:
    printk(KERN_INFO "%s-- %d fail\n", __func__, ret);
    return ret;
}

static int  usb_switch_remove(struct platform_device *pdev)
{
    struct usb_switch_platform_data *pdata = pdev->dev.platform_data;

    if (!pdata) {
        return -EINVAL;
    }

    cancel_work_sync(&sdev.work);
    switch_usb_dev_unregister(&sdev);
    device_remove_file(sdev.dev, &dev_attr_swstate);
    dev_set_drvdata(sdev.dev, NULL);
    class_destroy(switch_usb_class);
    gpio_free(gpio_switch_back);
    free_irq(sdev.irq1, &sdev);
    gpio_switch_back = -1;

    return 0;
}

static struct platform_driver usb_switch_driver = {
    .probe        = usb_switch_probe,
    .remove        = usb_switch_remove,
    .driver        = {
        .name    = "usbsw",
        .owner    = THIS_MODULE,
#if USE_DTS
        .of_match_table = of_match_ptr(platform_usbswitch_ids),
#endif
    },
};

//init function for switch_usb_class mode
static int __init switch_usb_class_init(void)
{
#if USE_NOTIFY_CHAIN
    struct switch_usb_info *sui;
#endif
    int ret = 0;
    printk(KERN_INFO "%s++\n", __func__);
#if USE_NOTIFY_CHAIN
   if(NULL == p_switch_usb_info)
    {
        sui = kzalloc(sizeof(struct switch_usb_info), GFP_KERNEL);
        if(NULL == sui) {
            printk(KERN_ERR "%s kzalloc failed!\n", __func__);
            return -ENOMEM;
        }
        p_switch_usb_info = sui;
        ATOMIC_INIT_NOTIFIER_HEAD(&sui->charger_type_notifier_head);
        spin_lock_init(&sui->reg_flag_lock);
    }
#endif
    ret = platform_driver_register(&usb_switch_driver);
    printk(KERN_INFO "%s-- %d\n", __func__, ret);
    return ret;
}

static void __exit switch_usb_class_exit(void)
{
#if USE_NOTIFY_CHAIN
   struct switch_usb_info *sui = p_switch_usb_info;

    if(NULL != sui)
    {
        kfree(sui);
        p_switch_usb_info = NULL;
    }
#endif
    platform_driver_unregister(&usb_switch_driver);
}

module_init(switch_usb_class_init);
module_exit(switch_usb_class_exit);

MODULE_AUTHOR("Lixiuna<lixiuna@huawei.com>");
MODULE_DESCRIPTION("Switch usb class driver");
MODULE_LICENSE("GPL");

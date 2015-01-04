/*
 *  drivers/switch/switch_gpio.c
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: Jake.Chen
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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/switch_usb.h>
#include <linux/workqueue.h>
#include <mach/gpio.h>
#include <linux/io.h>
#include <linux/delay.h>

static void usb_switch_work(struct work_struct *work)
{
	struct usb_switch_data	*switch_data =
		container_of(work, struct usb_switch_data, work);

	switch_usb_set_state(&switch_data->sdev, USB_TO_AP);
}

static irqreturn_t int_gpio_irq_handler(int irq, void *dev_id)
{
	struct usb_switch_data *switch_data =
	    (struct usb_switch_data *)dev_id;
	const int MAX_RETRY = 5;
	int i = 0;
	int int_gpio_value = 0;

	dev_info(switch_data->sdev.dev, "%s entry.\n", __func__);

	for (i=0; i<MAX_RETRY; i++) {
		int_gpio_value = gpio_get_value(switch_data->usw_int_gpio);
		dev_info(switch_data->sdev.dev, "%s: int_gpio_value: %d.\n",
			__func__, int_gpio_value);
		if (GPIO_HI == int_gpio_value) {
			/* disable irq interrupt */
			disable_irq_nosync(irq);
			schedule_work(&switch_data->work);
			break;
		}
		udelay(2);
	}
	dev_info(switch_data->sdev.dev, "%s end with retry time=%d\n", __func__, i);

	return IRQ_HANDLED;
}

static int usb_switch_probe(struct platform_device *pdev)
{
	struct usb_switch_platform_data *pdata = pdev->dev.platform_data;
	struct usb_switch_data *switch_data;
	int ret = 0;

	printk(KERN_INFO "usb_switch_probe entry.\n");

	if (!pdata)
		return -EBUSY;

	switch_data = kzalloc(sizeof(struct usb_switch_data), GFP_KERNEL);
	if (!switch_data)
		return -ENOMEM;

	switch_data->sdev.pdata = pdata;
	switch_data->sdev.name = pdata->name;
	switch_data->usw_en_gpio = pdata->usw_en_gpio;
	switch_data->usw_ctrl_gpio = pdata->usw_ctrl_gpio;
	switch_data->usw_int_gpio = pdata->usw_int_gpio;

	ret = switch_usb_dev_register(&switch_data->sdev);
	if (ret < 0)
		goto err_switch_usb_dev_register;

	ret = gpio_request(switch_data->usw_int_gpio, "usb_sw_interrupt");
	if (ret < 0)
		goto err_request_int_gpio;

	ret = gpio_direction_input(switch_data->usw_int_gpio);
	if (ret < 0)
		goto err_set_gpio_input;

	INIT_WORK(&switch_data->work, usb_switch_work);

	switch_data->irq = gpio_to_irq(switch_data->usw_int_gpio);
	if (switch_data->irq < 0) {
		ret = switch_data->irq;
		goto err_detect_irq_num_failed;
	}

	ret = request_irq(switch_data->irq, int_gpio_irq_handler,
			  pdata->irq_flags, "usb_sw_interrupt", switch_data);
	if (ret < 0)
		goto err_request_irq;

	/* disable irq interrupt */
	disable_irq(switch_data->irq);

	return 0;

err_request_irq:
err_detect_irq_num_failed:
err_set_gpio_input:
	gpio_free(switch_data->usw_int_gpio);
err_request_int_gpio:
	switch_usb_dev_unregister(&switch_data->sdev);
err_switch_usb_dev_register:
	kfree(switch_data);

	return ret;
}

static int __devexit usb_switch_remove(struct platform_device *pdev)
{
	struct usb_switch_data *switch_data = platform_get_drvdata(pdev);

	if (!switch_data) {
		return -1;
	}

	cancel_work_sync(&switch_data->work);
	gpio_free(switch_data->usw_int_gpio);
	switch_usb_dev_unregister(&switch_data->sdev);
	free_irq(switch_data->irq, switch_data);
	kfree(switch_data);

	return 0;
}

static struct platform_driver usb_switch_driver = {
	.probe		= usb_switch_probe,
	.remove		= __devexit_p(usb_switch_remove),
	.driver		= {
		.name	= "switch-usb",
		.owner	= THIS_MODULE,
	},
};

static int __init usb_switch_init(void)
{
	return platform_driver_register(&usb_switch_driver);
}

static void __exit usb_switch_exit(void)
{
	platform_driver_unregister(&usb_switch_driver);
}

module_init(usb_switch_init);
module_exit(usb_switch_exit);

MODULE_AUTHOR("Jake.chen");
MODULE_DESCRIPTION("USB Switch driver");
MODULE_LICENSE("GPL");

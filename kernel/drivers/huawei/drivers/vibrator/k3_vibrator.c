/* drivers/misc/vibrator_k3.c
 *
 * Copyright (C) 2008 Google, Inc.
 * Author: y36721
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
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/hrtimer.h>
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/regulator/consumer.h>

#include "timed_output.h"
#include <linux/vibrator/k3_vibrator.h>
#include <hisi/drv_regulator_user.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/clk.h>

#include "hsad_vibrator.h"

#ifdef CONFIG_ANDROID_K3_VIBRATOR_AUTO_CONTROL
#include <linux/hkadc/hisi_adc_hal.h>
#endif

#define MOTOR_LDO 1

struct k3_vibrator_data {
	struct timed_output_dev dev;
	struct k3_vibrator_platform_data *plat_data;
	struct hrtimer timer;
	struct mutex lock;
	struct clk *clk;
	void __iomem *k3_vibrator_base;
	int value;
	u8 freq;
	u8 power;
	u8 mode;
#ifdef CONFIG_ANDROID_K3_VIBRATOR_AUTO_CONTROL
	u8 battery_power;
#endif
};

struct k3_vibrator_data *k3_vibrator_pdata;
static void k3_vibrator_onoff_handler(struct work_struct *data);
static struct workqueue_struct *done_queue;

static bool vib_reg_enabled=false;
static int k3_vibrator_vout_number;
static struct regulator *k3_vibrator_vout_reg=NULL;

#ifdef CONFIG_ANDROID_K3_VIBRATOR_AUTO_CONTROL
static unsigned long g_pre_set_time;
#endif

static DECLARE_WORK(done_work, k3_vibrator_onoff_handler);

static void k3_vibrator_onoff(int on)
{
	struct k3_vibrator_data *pdata = k3_vibrator_pdata;
	pdata->value = on;
	queue_work(done_queue, &done_work);
}

static void k3_vibrator_regulator_enable(void)
{
	int error;

	if (true == vib_reg_enabled)
		return ;

	BUG_ON(IS_ERR(k3_vibrator_vout_reg));

	error = regulator_enable(k3_vibrator_vout_reg);
	if (error < 0) {
		pr_err( "%s: failed to enable edge vibrator vdd\n", __func__);
		return ;
	}

	vib_reg_enabled = true;
	return ;
}

static void k3_vibrator_regulator_disable(void)
{
	int error;

	if (false == vib_reg_enabled)
		return ;

	BUG_ON(IS_ERR(k3_vibrator_vout_reg));

	error = regulator_disable(k3_vibrator_vout_reg);
	if (error < 0) {
		pr_err( "%s: failed to disable edge vibrator vdd\n", __func__);
		return ;
	}

	vib_reg_enabled = false;
	return ;
}

static void k3_vibrator_onoff_handler(struct work_struct *data)
{
	struct k3_vibrator_data *pdata = k3_vibrator_pdata;
	int on = pdata->value;
	int ret = 0;

        mutex_lock(&pdata->lock);

	if (on) {
            k3_vibrator_regulator_enable();
	} else {
            k3_vibrator_regulator_disable();
	}

        mutex_unlock(&pdata->lock);

	return ;
}

static enum hrtimer_restart k3_vibrator_timer_func(struct hrtimer *timer)
{
	k3_vibrator_onoff(0);

	return HRTIMER_NORESTART;
}

static int k3_vibrator_get_time(struct timed_output_dev *dev)
{
	struct k3_vibrator_data *pdata =
			container_of(dev, struct k3_vibrator_data, dev);
	if (hrtimer_active(&pdata->timer)) {
		ktime_t r = hrtimer_get_remaining(&pdata->timer);
		struct timeval t = ktime_to_timeval(r);
		return t.tv_sec * 1000 + t.tv_usec / 1000;
	} else
		return 0;
}

static void k3_vibrator_enable(struct timed_output_dev *dev, int value)
{
	struct k3_vibrator_data *pdata = container_of(dev, struct k3_vibrator_data, dev);
#ifdef CONFIG_ANDROID_K3_VIBRATOR_AUTO_CONTROL
	static int set_count;
#endif

	if (value < 0) {
		pr_err("error:vibrator_enable value:%d is negative\n", value);
		return;
	}
	/* cancel previous timer */
	if (hrtimer_active(&pdata->timer))
        	hrtimer_cancel(&pdata->timer);

	if (value > 0) {
#ifdef CONFIG_ANDROID_K3_VIBRATOR_AUTO_CONTROL
		if (time_after(jiffies, g_pre_set_time+60*HZ)) {
			g_pre_set_time = jiffies;
			set_count = 0;
		}
		if (set_count == 0)
			pdata->battery_power = k3_vibrator_get_iset_value(0);

		set_count = (set_count+1)%50;
#endif

		if (value < TIMEOUT_MIN)
			value = TIMEOUT_MIN;
		k3_vibrator_onoff(1);
		hrtimer_start(&pdata->timer,
			ktime_set(value / 1000, (value % 1000) * 1000000),
			HRTIMER_MODE_REL);
	} else {
		k3_vibrator_onoff(0);
	}
}

static int k3_vibrator_get_vout(struct platform_device *pdev){
	char req_reg_name[32]={0};
	int min_voltage=0;
	int max_voltage=0;

	k3_vibrator_vout_number = get_vibrator_vout_number();

	if (-1 == k3_vibrator_vout_number){
		pr_err( "%s: ldo motor get vibrator vout fail\n", __func__);
		return -EPERM;
	}

	snprintf(req_reg_name, sizeof(req_reg_name),
		"vdd-vib-ldo%d", k3_vibrator_vout_number);

	k3_vibrator_vout_reg = regulator_get(&pdev->dev, VIBRATOR_VDD);

	if (IS_ERR(k3_vibrator_vout_reg)){
	pr_err( "%s: k3_vibrator_vout_reg error\n", __func__);
		return -EPERM;
	}

	min_voltage = get_vibrator_vout_min_voltage();
	max_voltage = get_vibrator_vout_max_voltage();

	if (-1 == min_voltage || -1 == max_voltage) return 0;

	if (regulator_set_voltage(k3_vibrator_vout_reg, min_voltage, max_voltage)){
		pr_err( "%s: vibrator set voltage error\n", __func__);
		return -EPERM;
	}

	return 0;
}
static ssize_t k3_vibrator_status(struct device_driver *driver, const char *buf, size_t count)
{
	long val;
    int status = count;

    if ((strict_strtol(buf, 10, &val) < 0))
        return -EINVAL;
    if(val)
        k3_vibrator_onoff(1);
    else
        k3_vibrator_onoff(0);
    return status;
}

static DRIVER_ATTR(state, S_IRUGO|S_IWUSR, NULL, k3_vibrator_status);

static struct platform_driver k3_vibrator_driver;

static int k3_vibrator_probe(struct platform_device *pdev)
{
	struct k3_vibrator_data *p_data;
	struct resource *res;
	int ret = 0;
	ret = k3_vibrator_get_vout(pdev);
	if (ret) {
		dev_err(&pdev->dev, "failed to get vib vout\n");
		return ret;
	}

	p_data = kzalloc(sizeof(struct k3_vibrator_data), GFP_KERNEL);
	if (p_data == NULL) {
		dev_err(&pdev->dev, "failed to allocate vibrator_device\n");
		return -ENOMEM;
	}
	/* get base_addres */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&pdev->dev, "failed to find registers\n");
		ret = -ENXIO;
		goto err;
	}
	p_data->k3_vibrator_base = ioremap(res->start, resource_size(res));
	if (p_data->k3_vibrator_base == 0) {
		dev_err(&pdev->dev, "failed to map registers\n");
		ret = -ENXIO;
		goto err;
	}

	/* init timer */
	hrtimer_init(&p_data->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	p_data->timer.function = k3_vibrator_timer_func;

	/* init lock */
	mutex_init(&p_data->lock);

	p_data->plat_data = pdev->dev.platform_data;

	if (NULL == p_data->plat_data) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "failed get platform_data.\n");
		goto err_remap;
	}

	p_data->mode = p_data->plat_data->mode;
	p_data->freq = p_data->plat_data->low_freq;
	p_data->power = p_data->plat_data->low_power;

	p_data->dev.name = K3_VIBRATOR;
	p_data->dev.get_time = k3_vibrator_get_time;
	p_data->dev.enable = k3_vibrator_enable;

	ret = timed_output_dev_register(&p_data->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to regist dev\n");
		goto err_remap;
	}
	platform_set_drvdata(pdev, p_data);

	k3_vibrator_pdata = p_data;

	/* create a single thread workquene */
	done_queue = create_workqueue("done_queue");
	if (!done_queue) {
		dev_err(&pdev->dev, "failed to creat workqueue\n");
		ret = -ENOMEM;
		goto err_regis;
	}
    ret = driver_create_file(&k3_vibrator_driver.driver, &driver_attr_state);
    if (ret) {
        dev_err(&pdev->dev, "could not create sysfs files\n");
        goto err_regis;
    }
    printk("%s: successful!\n",__FUNCTION__);
	return 0;

err_regis:
	timed_output_dev_unregister(&p_data->dev);
err_remap:
	iounmap(p_data->k3_vibrator_base);
err:
	kfree(p_data);
	p_data = NULL;
	return ret;
}

static int k3_vibrator_remove(struct platform_device *pdev)
{
	struct k3_vibrator_data *pdata = platform_get_drvdata(pdev);

	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	if (hrtimer_active(&pdata->timer))
		hrtimer_cancel(&pdata->timer);

	timed_output_dev_unregister(&pdata->dev);
	iounmap(pdata->k3_vibrator_base);
	kfree(pdata);
	pdata = NULL;
	destroy_workqueue(done_queue);
	platform_set_drvdata(pdev, NULL);
	return 0;
}

static void k3_vibrator_shutdown(struct platform_device *pdev)
{
	int ret = 0;
	struct k3_vibrator_data *pdata = platform_get_drvdata(pdev);
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return;
	}

	if (hrtimer_active(&pdata->timer))
		hrtimer_cancel(&pdata->timer);

        k3_vibrator_regulator_disable();

	return ;
}

#ifdef CONFIG_PM
static int  k3_vibrator_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct k3_vibrator_data *pdata = platform_get_drvdata(pdev);
	int ret;
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	if (!mutex_trylock(&pdata->lock)) {
		dev_err(&pdev->dev, "%s: mutex_trylock.\n", __func__);
		return -EAGAIN;
	}
	if (hrtimer_active(&pdata->timer)) {
		if (ret) {
			pr_err("pmu clock enable failed,ret:%d\n", ret);
			mutex_unlock(&pdata->lock);
			return ret;
		}
		hrtimer_cancel(&pdata->timer);
        k3_vibrator_regulator_disable();
	}

	return 0;
}

static int k3_vibrator_resume(struct platform_device *pdev)
{
	struct k3_vibrator_data *pdata = platform_get_drvdata(pdev);
	if (pdata == NULL) {
		dev_err(&pdev->dev, "%s:pdata is NULL\n", __func__);
		return -ENODEV;
	}

	mutex_unlock(&pdata->lock);

	return 0;
}
#endif

static struct platform_driver k3_vibrator_driver = {
	.probe  = k3_vibrator_probe,
	.remove = k3_vibrator_remove,
	.shutdown	= k3_vibrator_shutdown,
#ifdef CONFIG_PM
	.suspend	= k3_vibrator_suspend,
	.resume		= k3_vibrator_resume,
#endif
	.driver = {
		.name   = K3_VIBRATOR,
		.owner  = THIS_MODULE,
	},
};

static int __init k3_vibrator_init(void)
{
    if(MOTOR_LDO == get_motor_board_type())
        return platform_driver_register(&k3_vibrator_driver);
    else
        return -EPERM;
}

static void __exit k3_vibrator_exit(void)
{
        k3_vibrator_vout_number = -1;
        if (!IS_ERR(k3_vibrator_vout_reg))
            regulator_put(k3_vibrator_vout_reg);

        platform_driver_unregister(&k3_vibrator_driver);
}

module_init(k3_vibrator_init);
module_exit(k3_vibrator_exit);

MODULE_AUTHOR("skf57909");
MODULE_DESCRIPTION(" k3 vibrator driver");
MODULE_LICENSE("GPL");


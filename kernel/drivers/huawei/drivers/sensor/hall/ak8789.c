/*
 *
 * Copyright (C) 2013 HUAWEI, Inc.
 * Author: wangliang <bill.wangliang@huawei.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/board_sensors.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/wakelock.h>

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif

#include <linux/gpio.h>
#include <mach/gpio.h>
#include <asm/io.h>
#include <linux/mux.h>
#include <linux/wakelock.h>
#include <hsad/config_interface.h>
#include <linux/platform_device.h>
#include <hsad/config_mgr.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>
#include <linux/timer.h>

#define DRIVER_VERSION        "1.0.0"

/*board id config resouce*/
#define BOARD_RES_HALL_EXIST "sensor/hall_exist"
#define BOARD_RES_HALL_TYPE  "sensor/hall_used_type"
#define BOARD_RES_RIGHT_NORTH "sensor/hall_gpio_config_rn"
#define BOARD_RES_RIGHT_SOUTH "sensor/hall_gpio_config_rs"
#define BOARD_RES_LEFT_NORTH "sensor/hall_gpio_config_ln"
#define BOARD_RES_LEFT_SOUTH "sensor/hall_gpio_config_ls"

/*gpio name resouce*/
#define HALL_NAME_RIGHT_NORTH "hall_gpio_config_rn"
#define HALL_NAME_RIGHT_SOUTH "hall_gpio_config_rs"
#define HALL_NAME_LEFT_NORTH "hall_gpio_config_ln"
#define HALL_NAME_LEFT_SOUTH "hall_gpio_config_ls"

/*hall value*/
#define LEFT_HALL_N_value	(1<<0)
#define LEFT_HALL_S_value	(1<<2)
#define RIGHT_HALL_N_value	(1<<1)
#define RIGHT_HALL_S_value	(1<<3)

/*the LEFT(RIGHT)_HALL_S(N)_value alse used to mark the current trigger type when debug*/
static atomic_t irq_trigger = ATOMIC_INIT(0);

typedef struct gpio_struct{
	int gpio;
	unsigned long wake_up; /*wake: IRQF_NO_SUSPEND, sleep: IRQF_TRIGGER_NONE */
	char *name;
	int hall_value;/*hall value*/
}gpio_data_t;

typedef enum hall_used_type{
	ONE_POLE = 1,
	TWO_POLE = 2,
	FOUR_POLE = 4,
} hall_used_type_t;

struct hall_dev {
	struct input_dev *hw_input_hall;
	struct platform_driver hall_drv_pf;
	struct platform_device hall_dev_pf;
	struct workqueue_struct *hall_wq;
	struct work_struct hall_work;
	hall_used_type_t used_type;
	gpio_data_t* gpio_data;
};

static struct wake_lock hall_wk;
static struct timer_list hall_timer;

static int hall_pf_probe(struct platform_device *pdev);
static int hall_pf_remove(struct platform_device *dev);
static void hall_pf_shutdown(struct platform_device *dev);
static irqreturn_t hall_event_isr(int irq, void *dev);

static struct hall_dev hw_hall_dev = {
	.hw_input_hall = NULL,
	.hall_drv_pf = {
		.probe = hall_pf_probe,
		.remove = hall_pf_remove,
		.shutdown = hall_pf_shutdown,
		.driver = {
			.name = "hall_platform",
			.owner = THIS_MODULE,
		},
	},
	.hall_dev_pf = {
		.name = "hall_platform",
	},
	.gpio_data = NULL,
};

/*when gpio low, the interrupt trigged, set bit as 1*/
#define GROUP_VALUE(GPIO_NUM, GPIO_VALUE)\
	do{\
		ret = gpio_get_value(GPIO_NUM);\
		if (!ret)\
			value |= (GPIO_VALUE);\
		else\
			value &= (~GPIO_VALUE);\
	}while(0)

int query_hall_event(void)
{
	int value = 0;
	int ret = 0;
	int i = 0;
	gpio_data_t *gpio_ptr = hw_hall_dev.gpio_data;

	if (hw_hall_dev.used_type == FOUR_POLE){
		for ( i = 0; i < 4; i++){
			GROUP_VALUE(gpio_ptr->gpio, gpio_ptr->hall_value);
			gpio_ptr++;
		}
	}else if (hw_hall_dev.used_type == TWO_POLE){
		for ( i = 0; i < 2; i++){
			GROUP_VALUE(gpio_ptr->gpio, gpio_ptr->hall_value);
			gpio_ptr++;
		}
	}

	return value;
}

int gpio_setup(int gpio_num, const char* gpio_name)
{
	int ret = 0;

	ret = gpio_request(gpio_num, gpio_name);
	if(ret){
		pr_err("%s requset gpio %d err %d\n", __func__, gpio_num, ret);
		return ret;
	}
	ret = gpio_direction_input(gpio_num);
	if(ret){
		pr_err("%s gpio %d direction input err %d\n", __func__, gpio_num, ret);
		return ret;
	}
	return ret;
}

int hall_request_irq(int current_value, int hall_value, int irq, const char *name, unsigned long wake_flags)
{
	int ret = 0;
	pr_info("%s name %s current_value %d hall_value %d irq %d flags %lu\n", __func__, name, current_value, hall_value, irq, wake_flags);
	/*if current gpio is high, set low as irq, otherwise vs*/
	if (!(current_value & hall_value)){/* the operator is bit operator &, not logic operator &&*/
		ret = request_irq(irq, hall_event_isr,
			 IRQF_TRIGGER_LOW | wake_flags, name, &hw_hall_dev);
		if (ret){
			pr_err("%s gpio %s request_irq fail %d\n", __func__, name, ret);
			return ret;
		}
		atomic_set(&irq_trigger, atomic_read(&irq_trigger) & (~hall_value));
		pr_info("%s irq trigger %d\n", __func__,  atomic_read(&irq_trigger));
	}else{
		ret = request_irq(irq, hall_event_isr,
			 IRQF_TRIGGER_HIGH | wake_flags, name, &hw_hall_dev);
		if (ret){
			pr_err("%s gpio %s request_irq fail %d\n", __func__, name, ret);
			return ret;
		}
		atomic_set(&irq_trigger, atomic_read(&irq_trigger) | hall_value);
		pr_info("%s irq trigger %d\n", __func__, atomic_read(&irq_trigger));
	}

	return ret;
}

static int hall_gpio_irq_setup(void)
{
	int ret = 0;
	int value = 0;
	gpio_data_t *gpio_ptr = hw_hall_dev.gpio_data;
	int i = 0;

	if (hw_hall_dev.used_type == FOUR_POLE){
		for (i = 0; i < 4; i++){
			ret = gpio_setup(gpio_ptr->gpio, gpio_ptr->name);
			if (ret){
				pr_err("%s gpio_setup failed %s\n", __func__, gpio_ptr->name);
				return ret;
			}
			gpio_ptr++;
		}
	} else if(hw_hall_dev.used_type == TWO_POLE){
		for (i = 0; i < 2; i++){
			ret = gpio_setup(gpio_ptr->gpio, gpio_ptr->name);
			if (ret){
				pr_err("%s gpio_setup failed %s\n", __func__, gpio_ptr->name);
				return ret;
			}
			gpio_ptr++;
		}
	}

	value = query_hall_event();

	gpio_ptr = hw_hall_dev.gpio_data;

	/*just N need wakeup*/
	if (hw_hall_dev.used_type == FOUR_POLE){
		for (i = 0; i < 4; i++){
			ret = hall_request_irq(value, gpio_ptr->hall_value, gpio_to_irq(gpio_ptr->gpio), gpio_ptr->name, gpio_ptr->wake_up);
			if (ret){
				pr_err("%s hall _request_irq error %d\n", __func__, ret);
				return ret;
			}
			gpio_ptr++;
		}
	} else if(hw_hall_dev.used_type == TWO_POLE){
		for (i = 0; i < 2; i++){
			ret = hall_request_irq(value, gpio_ptr->hall_value, gpio_to_irq(gpio_ptr->gpio), gpio_ptr->name, gpio_ptr->wake_up);
			if (ret){
				pr_err("%s hall _request_irq error %d\n", __func__, ret);
				return ret;
			}
			gpio_ptr++;
		}
	}

	return ret;
}

int hall_pf_probe(struct platform_device *pdev)
{
	int ret = 0;
	pr_info("called probe %s\n", __func__);
	ret = hall_gpio_irq_setup();
	return ret;
};

static void free_hall_resource(struct hall_dev *dev)
{
	gpio_data_t *gpio_ptr = dev->gpio_data;
	int i = 0;
	if (hw_hall_dev.used_type == FOUR_POLE){
		for (i = 0; i < 4; i++){
			free_irq(gpio_to_irq(gpio_ptr->gpio), dev);
			gpio_free(gpio_ptr->gpio);
			gpio_ptr++;
		}
	} else if(hw_hall_dev.used_type == TWO_POLE){
		for (i = 0; i < 2; i++){
			free_irq(gpio_to_irq(gpio_ptr->gpio), dev);
			gpio_free(gpio_ptr->gpio);
			gpio_ptr++;
		}
	}

}

int hall_pf_remove(struct platform_device *dev)
{

	struct hall_dev *data = container_of(dev, struct hall_dev, hall_dev_pf);
	flush_workqueue(data->hall_wq);
	destroy_workqueue(data->hall_wq);
	wake_lock_destroy(&hall_wk);
	free_hall_resource(data);
	return 0;
}

void hall_pf_shutdown(struct platform_device *dev)
{
	struct hall_dev *data = container_of(dev, struct hall_dev, hall_dev_pf);
	flush_workqueue(data->hall_wq);
	destroy_workqueue(data->hall_wq);
	wake_lock_destroy(&hall_wk);
	free_hall_resource(data);
}

static atomic_t irq_no_at = ATOMIC_INIT(0);
void hall_work_func(struct work_struct *work)
{
	int value = 0;
	value = query_hall_event();
	input_event(hw_hall_dev.hw_input_hall, EV_MSC, MSC_SCAN, value);
	input_sync(hw_hall_dev.hw_input_hall);
	atomic_dec(&irq_no_at);
}

irqreturn_t hall_event_isr(int irq, void *dev)
{

	struct hall_dev *data = dev;
	struct irq_desc *desc = irq_to_desc(irq);
	unsigned int trigger = 0;
	int irq_type = 0;
	int ret = 0;
	int i = 0;
	gpio_data_t *gpio_ptr = NULL;

	if ((!data)||(!desc)){
		pr_err("%s dev null, or irq_desc null\n", __func__);
		return IRQ_NONE;
	}

	gpio_ptr = data->gpio_data;

	wake_lock_timeout(&hall_wk, HZ);

	trigger = desc->irq_data.state_use_accessors & IRQD_TRIGGER_MASK;

	if (trigger & IRQF_TRIGGER_LOW){
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_HIGH);
		if (ret){
			pr_err(" hall irq_set_irq_type error %s\n", desc->name);
		}
		trigger = IRQF_TRIGGER_HIGH;
	}else if (trigger & IRQF_TRIGGER_HIGH){
		ret = irq_set_irq_type(irq, IRQF_TRIGGER_LOW);
		if (ret){
			pr_err(" hall irq_set_irq_type error %s\n", desc->name);
		}
		trigger = IRQF_TRIGGER_LOW;
	}else{
		wake_unlock(&hall_wk);
		pr_err(" hall trigger not level type, error\n");
		return IRQ_NONE;
	}

	if (data->used_type == FOUR_POLE){
		irq_type = atomic_read(&irq_trigger);
		for (i = 0; i < 4; i++){
			if (irq == gpio_to_irq(gpio_ptr->gpio)){
				if (trigger == IRQF_TRIGGER_LOW){
					atomic_set(&irq_trigger, irq_type & (~gpio_ptr->hall_value));
				} else {
					atomic_set(&irq_trigger, irq_type | gpio_ptr->hall_value);
				}
			}
			gpio_ptr++;
		}
	} else if(data->used_type == TWO_POLE){
		irq_type = atomic_read(&irq_trigger);
		for (i = 0; i < 2; i++){
			if (irq == gpio_to_irq(gpio_ptr->gpio)){
				if (trigger == IRQF_TRIGGER_LOW){
					atomic_set(&irq_trigger, irq_type & (~gpio_ptr->hall_value));
				} else {
					atomic_set(&irq_trigger, irq_type | gpio_ptr->hall_value);
				}
			}
			gpio_ptr++;
		}
	}

	atomic_inc(&irq_no_at);

	queue_work(data->hall_wq, &data->hall_work);
	return IRQ_HANDLED;
}

static void ak8987_first_input_work()
{
	int value = 0;
	value = query_hall_event();
	input_event(hw_hall_dev.hw_input_hall, EV_MSC, MSC_SCAN, value);
	input_sync(hw_hall_dev.hw_input_hall);
}

static int hall_enable_status = 0;
static ssize_t ak8987_store_enable_hall_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = simple_strtoul(buf, NULL, 10);
	pr_info("%s enable value %lu \n", __func__, val);

	if (val == 1){
		hall_enable_status = 1;
		mod_timer(&hall_timer,jiffies + msecs_to_jiffies(2000));
	}else if (val == 0){
		hall_enable_status = 0;
	}else{
		pr_err("%s enable value error\n", __func__);
		return count;
	}
	return count;

}

static ssize_t ak8987_show_enable_hall_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", hall_enable_status);
}

static DEVICE_ATTR(enable_hall_sensor, 0664, ak8987_show_enable_hall_sensor, ak8987_store_enable_hall_sensor);

static ssize_t ak8987_show_irq_count(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", atomic_read(&irq_no_at));
}

static DEVICE_ATTR(irq_count, 0664, ak8987_show_irq_count, NULL);

static ssize_t ak8987_show_get_hall_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int value = 0;
	value = query_hall_event();

	return snprintf(buf, PAGE_SIZE, "%d\n", value);
}

static DEVICE_ATTR(get_hall_status, 0664, ak8987_show_get_hall_status, NULL);

static ssize_t ak8987_show_irq_trigger(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%d\n", atomic_read(&irq_trigger));
}
static DEVICE_ATTR(irq_trigger, 0664, ak8987_show_irq_trigger, NULL);

static struct attribute *ak8987_attributes[] = {
	&dev_attr_enable_hall_sensor.attr,
	&dev_attr_get_hall_status.attr, /*debug, purpose*/
	&dev_attr_irq_count.attr,/*debug purpose*/
	&dev_attr_irq_trigger.attr,/*debug purpose*/
	NULL
};

static const struct attribute_group ak8987_attr_group = {
	.attrs = ak8987_attributes,
};

/* input: buf as s_xxxx, w_xxxx, xxxx is gpio number, s is sleep, w is wake
 *        wake, 1:wake, 0:sleep
 * output:gpio number
 */
static int parse_gpio_config(const char *buf, unsigned long *wake)
{
	int gpio;
	char *wake_buf;
	char *gpio_buf;
	char *p;

	gpio_buf = strchr(buf, '_');
	if (!gpio_buf){
		return -ENXIO;
	}

	gpio_buf += 1;
	gpio = simple_strtol(gpio_buf, &p, 0);

	wake_buf = strchr(buf, 'w');
	if (wake_buf){
		*wake = IRQF_NO_SUSPEND;
		pr_info("%s %s %d, wake %lu\n", __func__, gpio_buf, gpio, *wake);
		return gpio;
	}

	wake_buf = strchr(buf, 's');
	if (wake_buf){
		*wake = IRQF_TRIGGER_NONE;
		pr_info("%s %s %d, wake %lu\n", __func__, gpio_buf, gpio, *wake);
		return gpio;
	}

	return -ENXIO;
}

#define gpio_config(n) gpio_config##n
#define gpio_config_x(n) gpio_config(n)
#define convert_gpio(str) #str

static int ak8987_init(void)
{
	int err = 0;
	int exist = 0;
	int used_type = 0;
	char gpio_config_str[20] = {};
	int gpio = 0;
	unsigned long wake = 0;
	gpio_data_t *gpio_ptr;
	pr_info("%s module init\n", __func__);

	err = get_hw_config_int(BOARD_RES_HALL_EXIST, &exist, NULL);
	if ((!err)||(!exist)){
		pr_err("%s err %d exist %d\n", __func__, err, exist);
		return -ENXIO;
	}

	/*return false, not found, true found*/
	err = get_hw_config_int(BOARD_RES_HALL_TYPE, &used_type, NULL);
	if (!err){
		pr_err("%s err %d exist %d\n", __func__, err, exist);
		return -ENXIO;
	}

	hw_hall_dev.used_type = (hall_used_type_t)used_type;

	/*add timer for report status in starting up */
	init_timer(&hall_timer);
	hall_timer.function = ak8987_first_input_work;

	switch(used_type){
	case 4:/*four pole*/
	{
		hw_hall_dev.gpio_data = kzalloc(sizeof(*hw_hall_dev.gpio_data)*4, GFP_KERNEL);
		if (IS_ERR(hw_hall_dev.gpio_data)){
			pr_err("%s kzalloc err\n", __func__);
			return PTR_ERR(hw_hall_dev.gpio_data);
		}
		gpio_ptr = hw_hall_dev.gpio_data;

		err = get_hw_config_string(BOARD_RES_RIGHT_NORTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_rn_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_RIGHT_NORTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  hall_gpio_config_rn err\n", __func__);
			err =  PTR_ERR(hw_hall_dev.gpio_data);
			goto rn_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_RIGHT_NORTH, sizeof(HALL_NAME_RIGHT_NORTH));
		gpio_ptr->hall_value = RIGHT_HALL_N_value;

		gpio_ptr++;
		err = get_hw_config_string(BOARD_RES_RIGHT_SOUTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_rs_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_RIGHT_SOUTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  hall_gpio_config_rs err\n", __func__);
			err =  PTR_ERR(hw_hall_dev.gpio_data);
			goto rs_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_RIGHT_SOUTH, sizeof(HALL_NAME_RIGHT_SOUTH));
		gpio_ptr->hall_value = RIGHT_HALL_S_value;

		gpio_ptr++;
		err = get_hw_config_string(BOARD_RES_LEFT_NORTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_ln_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_LEFT_NORTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  hall_gpio_config_ln err\n", __func__);
			err = PTR_ERR(hw_hall_dev.gpio_data);
			goto ln_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_LEFT_NORTH, sizeof(HALL_NAME_LEFT_NORTH));
		gpio_ptr->hall_value = LEFT_HALL_N_value;

		gpio_ptr++;
		err = get_hw_config_string(BOARD_RES_LEFT_SOUTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_ls_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_LEFT_SOUTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  hall_gpio_config_ls err\n", __func__);
			err =  PTR_ERR(hw_hall_dev.gpio_data);
			goto ls_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_LEFT_SOUTH, sizeof(HALL_NAME_LEFT_SOUTH));
		gpio_ptr->hall_value = LEFT_HALL_S_value;
		break;
	}
	case 2:/*two pole*/
	{
		hw_hall_dev.gpio_data = kzalloc(sizeof(*hw_hall_dev.gpio_data)*2, GFP_KERNEL);
		if (IS_ERR(hw_hall_dev.gpio_data)){
			pr_err("%s kzlloc err\n", __func__);
			return PTR_ERR(hw_hall_dev.gpio_data);
		}
		gpio_ptr = hw_hall_dev.gpio_data;

		err = get_hw_config_string(BOARD_RES_RIGHT_NORTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_rn_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_RIGHT_NORTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  %s err\n", __func__, HALL_NAME_RIGHT_NORTH);
			err = PTR_ERR(hw_hall_dev.gpio_data);
			goto rn_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_RIGHT_NORTH, sizeof(HALL_NAME_RIGHT_NORTH));
		gpio_ptr->hall_value = RIGHT_HALL_N_value;

		gpio_ptr++;
		err = get_hw_config_string(BOARD_RES_RIGHT_SOUTH, gpio_config_str, sizeof(gpio_config_str), NULL);
		gpio = parse_gpio_config(gpio_config_str, &wake);
		if (gpio < 0){
			err = gpio;
			goto gpio_rs_err;
		}

		gpio_ptr->gpio = gpio;
		gpio_ptr->wake_up = wake;
		gpio_ptr->name = kzalloc(sizeof(HALL_NAME_RIGHT_SOUTH), GFP_KERNEL);
		if (IS_ERR(gpio_ptr->name)){
			pr_err("%s kzalloc  %s err\n", __func__, HALL_NAME_RIGHT_SOUTH);
			err = PTR_ERR(hw_hall_dev.gpio_data);
			goto rs_mem;
		}
		memcpy(gpio_ptr->name, HALL_NAME_RIGHT_SOUTH, sizeof(HALL_NAME_RIGHT_SOUTH));
		gpio_ptr->hall_value = RIGHT_HALL_S_value;
		break;
	}
	default:
	{
		pr_err("%s err %d exist %d\n", __func__, err, exist);
		return -ENXIO;
	}
	}/*end switch*/


	hw_hall_dev.hw_input_hall = input_allocate_device();
	if (IS_ERR(hw_hall_dev.hw_input_hall)){
		dev_err(&hw_hall_dev.hw_input_hall->dev, "hw_input_hall alloc error %ld\n", PTR_ERR(hw_hall_dev.hw_input_hall));
		goto input_err;
	}
	
	hw_hall_dev.hw_input_hall->name = HALL_INPUT_DEV_NAME;
	set_bit(EV_MSC, hw_hall_dev.hw_input_hall->evbit);
	set_bit(MSC_SCAN, hw_hall_dev.hw_input_hall->mscbit);

	err = input_register_device(hw_hall_dev.hw_input_hall);
	if (err){
		dev_err(&hw_hall_dev.hw_input_hall->dev, "hw_input_hall regiset error %d\n", err);
		goto input_register_fail;
	}

	err = platform_device_register(&hw_hall_dev.hall_dev_pf);
	if (err){
		dev_err(&hw_hall_dev.hall_dev_pf.dev, "hall_pf_dev_fall regiset error %d\n", err);
		goto hall_pf_dev_fail;
	}

	err = platform_driver_register(&hw_hall_dev.hall_drv_pf);
	if (err){
		dev_err(&hw_hall_dev.hall_dev_pf.dev, "hall_pf_drv_fall regiset error %d\n", err);
		goto hall_pf_drv_fail;
	}

	err =  sysfs_create_group(&hw_hall_dev.hall_dev_pf.dev.kobj, &ak8987_attr_group);
	if (err){
		dev_err(&hw_hall_dev.hw_input_hall->dev, "sysfs create error %d\n", err);
		goto sysfs_create_fail;
	}

	hw_hall_dev.hall_wq = create_singlethread_workqueue("hall_wq");
	if (IS_ERR(hw_hall_dev.hall_wq)){
		dev_err(&hw_hall_dev.hw_input_hall->dev, "wq create error %ld\n", PTR_ERR(hw_hall_dev.hall_wq));
		goto wq_fail;
	}

	INIT_WORK(&hw_hall_dev.hall_work, hall_work_func);

	wake_lock_init(&hall_wk, WAKE_LOCK_SUSPEND, "hall_wakelock");
#ifdef CONFIG_HUAWEI_SENSORS_INPUT_INFO
	err = set_sensor_chip_info(HALL, HALL_INPUT_DEV_NAME);
	if (err) {
		pr_err("HALL set_sensor_chip_info error\n");
	}

#endif
	return err;
wq_fail:
sysfs_create_fail:
hall_pf_drv_fail:
	platform_driver_unregister(&hw_hall_dev.hall_drv_pf);
hall_pf_dev_fail:
	platform_device_unregister(&hw_hall_dev.hall_dev_pf);
input_register_fail:
	input_free_device(hw_hall_dev.hw_input_hall);
input_err:
	kfree(gpio_ptr->name);
	if (used_type == 4){
ls_mem:
gpio_ls_err:
	gpio_ptr--;
	kfree(gpio_ptr->name);
ln_mem:
gpio_ln_err:
	gpio_ptr--;
	kfree(gpio_ptr->name);
	}
rs_mem:
gpio_rs_err:
	gpio_ptr--;
	kfree(gpio_ptr->name);

rn_mem:
gpio_rn_err:

	kfree(hw_hall_dev.gpio_data);
	return err;
}

static void __exit ak8987_exit(void)
{
	platform_driver_unregister(&hw_hall_dev.hall_drv_pf);
	platform_device_unregister(&hw_hall_dev.hall_dev_pf);
	input_unregister_device(hw_hall_dev.hw_input_hall);
}

MODULE_AUTHOR("Liang Wang <bill.wangliang@huawei.com>");
MODULE_DESCRIPTION("ak8987 hall");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(ak8987_init);
module_exit(ak8987_exit);


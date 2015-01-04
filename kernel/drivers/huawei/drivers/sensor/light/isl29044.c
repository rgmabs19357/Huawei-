/*
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
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/gpio.h>
#include <linux/board_sensors.h>
#include <linux/earlysuspend.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <asm/io.h>
#include <linux/mux.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>
#include <linux/regulator/consumer.h>
#include <linux/earlysuspend.h>
#include <hsad/config_mgr.h>
#include <hsad/configdata.h>
#include <hsad/config_interface.h>
#include <linux/semaphore.h>

#include "isl29044.h"

#define DRIVER_VERSION "1.0.0"
#define PS_THRESHOLD_L (40)
#define PS_THRESHOLD_H (110)
#define TP_COEFF (122)
#define PS_MAX_FLOOR_NOISE (150)
#define PS_DEF_FLOOR_NOISE (150)
#define PS_POLL_TIME (50)
#define PS_THRESHOLD_COVER (200) /*used for cover ps and enable ps*/

struct isl29044_data {
	struct i2c_client *client;
	struct early_suspend early_drv;
	struct regulator *io_vdd;
	struct regulator *vdd;
	struct semaphore als_ps_sema;

	u8 als_pwr_status;
	u8 als_range; /* als rang, 0: 125Lux, 1:2000Lux*/
	u8 als_mode; /* als mode, 0: Visible light, 1: IR light*/
	spinlock_t als_timer_lock;
	struct delayed_work als_work;
	struct workqueue_struct *als_wq;
	struct input_dev *als_input_dev;
	u8 als_range_using;
	u8 als_pwr_before_suspend;
	u32 als_ir_cnt;
	u32 als_ir_cnt_set;
	u16 als_ir;
	int als_last; /*dummy*/
	u8 als_type_now; /* 0 for als, 1 for IR */
	int als_value;
	int als_poll_delay; /*poll delay set by hal, delay 200ms*/
	ulong enable;
	int als_init;/*dummy*/

	u8 ps_pwr_status;/*depends on enable, enable:1, disable:0*/
	u8 ps_led_drv_cur; /* led driver current, 0: 110mA, 1: 220mA*/
	u8 ps_lt; /* ps low limit*/
	u8 ps_ht; /* ps high limit*/
	spinlock_t ps_timer_lock;
	struct delayed_work ps_work;
	struct workqueue_struct *ps_wq;
	struct input_dev *ps_input_dev;
	int ps_last;/*the last ps value, used to determin whether report event*/
	u8 ps_floor_noise;
	int ps_value;
	int ps_poll_delay; /*poll delay set by hal, delay 100ms*/
	int ps_irq;
	int ps_irq_gpio;
	int ps_init;

	u8 als_show_raw; /*show als raw data flag, used for debug*/
	u8 ps_show_raw; /* used for debug */
};

static struct wake_lock wlock;

static int set_sensor_reg(struct isl29044_data *data);

static void do_als_work(struct work_struct *work)
{
	struct isl29044_data *data;
	int ret = 0;
	int als_dat = 0;
	u8 show_raw_dat = 0;
	int lux = 0;
	u8 als_range = 0;
	u8 reset_reg = 0;
	u8 als_ir_cnt = 0;
	int next_time = 0;
	u8 buf[2];

	data = container_of(work, struct isl29044_data, als_work.work);

	if(down_interruptible(&data->als_ps_sema))
		goto sema_err;

	show_raw_dat = data->als_show_raw;
	als_range = data->als_range_using;

	/*0x09, 0x0A, 12bit als value*/
	ret = i2c_smbus_read_i2c_block_data(data->client, 0x09, 2, buf);
	if (ret < 0)
		goto err_rd;
	als_dat = buf[0] + (buf[1] << 8);

	if (als_range)
	{
		/* divide 10 is because TP_COEFF is X10 */
		lux = (als_dat * 2000 * TP_COEFF) / 4096 / 10;
	}
	else
	{
		lux = (als_dat * 125 * TP_COEFF) / 4096 / 10;
	}

	input_report_abs(data->als_input_dev, ABS_MISC, lux);
	input_sync(data->als_input_dev);
	if (show_raw_dat)
	{
		printk(KERN_INFO "now als raw data is = %d, LUX = %d\n", als_dat, lux);
	}

	if (data->als_range)
	{
		if (als_dat < 204)	/* About 100 Lux */
		{
			data->als_range = 0;
			reset_reg = 1;
		}
	}
	else
	{
		if (als_dat > 3768)	/* About 115 Lux */
		{
			data->als_range = 1;
			reset_reg = 1;
		}
	}

	if (reset_reg)
	{
		pr_info("%s isl29044 reset reg happened\n", __func__);
		ret = set_sensor_reg(data);
		/*if error, nothing to do, if sucess, change the range mark*/
		if (!ret)
			data->als_range_using = data->als_range;
	}

	/* restart timer */
	if (data->als_pwr_status == 0)
	{
		return;
	}
	next_time = data->als_poll_delay;
	if (als_ir_cnt == 0)
	{
		next_time = next_time - 250;
		if (next_time < 250) next_time = 250;
	}

err_rd:
	up(&data->als_ps_sema);
sema_err:
	queue_delayed_work(data->als_wq, &data->als_work, next_time);

	return;

}

static void do_ps_work(struct work_struct *work)
{
	struct isl29044_data *data;
	int ps_last;
	int ret;
	u8 show_raw_dat;
	u8 ps_raw_dat;
	u8 reg_dat[5];
	int i;
	static unsigned int is_modify_threshold = 0;

	data = container_of(work, struct isl29044_data, ps_work.work);
	show_raw_dat = data->ps_show_raw;

	if (show_raw_dat)
		pr_info("%s isl29044 called\n", __func__);

	pr_info("%s isl29044 called\n", __func__);

	if(down_interruptible(&data->als_ps_sema))
		goto sema_err;

	/* initial to find the ps floor noise */
	/* read ps raw data */
	ret = i2c_smbus_read_byte_data(data->client, 0x08);
	if (ret < 0)
		goto enable_irq;
	ps_raw_dat = ret;

	if (show_raw_dat)
		pr_info("%s get raw data %d\n", __func__, ps_raw_dat);

	ps_last = data->ps_last;
	/*if ps_raw_dat bigger than PS_THRESHOLD_COVER, its to be recognise as cover the ps*/
	if (ps_raw_dat > PS_THRESHOLD_COVER){
		data->ps_last = 0;
		input_event(data->ps_input_dev, EV_ABS, ABS_DISTANCE, 0);
		input_sync(data->ps_input_dev);
		is_modify_threshold = 0;
		goto enable_irq;
	}


	/*1:far, 0:near*/
	data->ps_last = gpio_get_value(data->ps_irq_gpio);
	pr_info("isl29044 get value %d\n", data->ps_last);


	if (ps_last != data->ps_last){
		input_report_abs(data->ps_input_dev, ABS_DISTANCE, data->ps_last);
		input_sync(data->ps_input_dev);
		if (show_raw_dat)
			printk(KERN_INFO "ps status changed, now = %d\n", data->ps_last);
	}

	if (data->ps_last == 0){
		is_modify_threshold = 0;
		goto enable_irq;
	}else{

		/* ajuest ps threshold */
		if (ps_raw_dat > PS_MAX_FLOOR_NOISE){
			/* ps data is too larger, I think the floor noise is not right, use default */
			data->ps_floor_noise = PS_DEF_FLOOR_NOISE;
		}else{
			data->ps_floor_noise = ps_raw_dat;
		}

		reg_dat[3] = data->ps_floor_noise + data->ps_lt;
		reg_dat[4] = data->ps_floor_noise + data->ps_ht;
		for(i = 3 ; i <= 4; i++){
			if (show_raw_dat)
				pr_info("isl29044 reset threshold reg %X = %d\n", i, reg_dat[i]);
			ret = i2c_smbus_write_byte_data(data->client, i, reg_dat[i]);
			if (ret < 0) {
				printk(KERN_ERR "In set_sensor_reg() err0, ret=%d\n", ret);
			}
		}
		queue_delayed_work(data->ps_wq, &data->ps_work, data->ps_poll_delay);
		is_modify_threshold++;
	}

enable_irq:
	up(&data->als_ps_sema);
sema_err:
	if ((!data->ps_init) && (is_modify_threshold <= 1 )) {
		enable_irq(data->ps_irq);
	}
	data->ps_init = 0;
	return;
}


/*state: true enable, false, disable*/
#define SET_PWR_ST(name)											\
	static int set_##name##_pwr_st(u8 state, struct isl29044_data *data)					\
	{													\
		int ret = 0;											\
		unsigned long flags = 0;									\
		pr_info("%s isl29044 called, power set as %d\n", __func__, state);				\
														\
		spin_lock_irqsave(&data->name##_timer_lock, flags);						\
		if (data->name##_pwr_status == state){								\
			spin_unlock_irqrestore(&data->name##_timer_lock, flags);				\
			return ret;										\
		}												\
		data->name##_pwr_status = state;								\
		data->name##_last = -1;										\
		data->name##_init = state;									\
		spin_unlock_irqrestore(&data->name##_timer_lock, flags);					\
														\
		ret =  set_sensor_reg(data);									\
		if (ret){											\
			dev_err(&data->client->dev, "%s set_sensor_reg %s power on failed %d\n",__func__, #name, ret);\
			return ret;										\
		}												\
		if (state)											\
			queue_delayed_work(data->name##_wq, &data->name##_work, msecs_to_jiffies(112));		\
		else												\
			__cancel_delayed_work(&data->name##_work);						\
		return ret;											\
	}

SET_PWR_ST(ps)
SET_PWR_ST(als)

#define STORE_ENABLE_SENSOR(name)								\
	static ssize_t store_enable_##name##_sensor(struct device *dev,				\
			struct device_attribute *attr, const char *buf, size_t count)		\
	{											\
		int ret;									\
												\
		struct isl29044_data *data = NULL;						\
		struct i2c_client *client = NULL;						\
		unsigned long val = simple_strtoul(buf, NULL, 10);				\
		pr_info("%s called enable sensor value is %ld\n", __func__, val);		\
		client = to_i2c_client(dev);							\
		data = i2c_get_clientdata(client);						\
		if ((val != 0) && (val != 1)) {							\
			pr_err("%s: enable sensor=%ld error\n", __func__, val);		\
			return count;								\
		}										\
		ret = set_##name##_pwr_st(val, data);							\
		if (ret)										\
			dev_err(&client->dev, "%s set_ %s _pwr_st err %d\n", __func__, #name, ret);	\
		return count;										\
	}

STORE_ENABLE_SENSOR(ps)
STORE_ENABLE_SENSOR(als)

#define SHOW_SENSOR_INFO(name, info) \
	static ssize_t show_##name##_sensor_##info(struct device *dev, \
			struct device_attribute *attr, char *buf)\
	{											\
		struct isl29044_data *data = NULL;						\
		struct i2c_client *client = NULL;						\
		u8 value = 0;									\
												\
		client = to_i2c_client(dev);							\
		data = i2c_get_clientdata(client);						\
												\
		value = data->name##_##info;							\
												\
		return snprintf(buf, PAGE_SIZE, "%d\n", value);					\
	}

SHOW_SENSOR_INFO(ps, pwr_status)
SHOW_SENSOR_INFO(als, pwr_status)
SHOW_SENSOR_INFO(als, range)
SHOW_SENSOR_INFO(als, mode)
SHOW_SENSOR_INFO(als, show_raw)
SHOW_SENSOR_INFO(ps, show_raw)

#define STORE_SENSOR_INFO(name, info) \
	static ssize_t store_##name##_sensor_##info(struct device *dev, \
			struct device_attribute *attr, const char *buf, size_t count)\
	{											\
		struct isl29044_data *data = NULL;						\
		struct i2c_client *client = NULL;						\
		unsigned long flags = 0;							\
		int value = 0;									\
												\
		client = to_i2c_client(dev);							\
		data = i2c_get_clientdata(client);						\
		value = simple_strtoul(buf, NULL, 10);						\
		if ((value != 1)&&(value != 0))							\
			return -EINVAL;								\
		spin_lock_irqsave(&data->name##_timer_lock, flags);				\
		data->name##_##info = value;							\
		spin_unlock_irqrestore(&data->name##_timer_lock, flags);			\
												\
		return count;									\
	}

STORE_SENSOR_INFO(als, range)
STORE_SENSOR_INFO(als, mode)
STORE_SENSOR_INFO(als, show_raw)
STORE_SENSOR_INFO(ps, show_raw)

static int get_reg = 0;
static ssize_t store_get_reg_value(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	get_reg = simple_strtoul(buf, NULL, 10);
	pr_info("isl29044 get_reg %d\n", get_reg);
	return count;
}

static ssize_t show_get_reg_value(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct isl29044_data *data = NULL;
	struct i2c_client *client = NULL;
	int value = 0;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	value = i2c_smbus_read_byte_data(data->client, get_reg);
	pr_info("isl29044 reg %d\n", value);
	return snprintf(buf, PAGE_SIZE, "%X\n", value);
}

static int set_reg = 0;
static int set_reg_value = 0;
static ssize_t store_set_reg_value(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = NULL;
	int ret = 0;
	client = to_i2c_client(dev);

	ret = sscanf(buf, "%d %d", &set_reg, &set_reg_value);
	if (ret != 2){
		pr_err("%s parameter err\n", __func__);
		return -EINVAL;
	}

	ret = i2c_smbus_write_byte_data(client, set_reg, set_reg_value);
	return count;
}

ssize_t show_set_reg_value(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct i2c_client *client = NULL;
	int value = 0;

	client = to_i2c_client(dev);

	value = i2c_smbus_read_byte_data(client, get_reg);
	return snprintf(buf, PAGE_SIZE, "%X\n", value);
}
static DEVICE_ATTR(enable_als_sensor, 0664, show_als_sensor_pwr_status,
		store_enable_als_sensor);
static DEVICE_ATTR(enable_ps_sensor, 0664, show_ps_sensor_pwr_status,
		store_enable_ps_sensor);
static DEVICE_ATTR(als_range, 0664, show_als_sensor_range,
		store_als_sensor_range);
static DEVICE_ATTR(als_mode, 0664, show_als_sensor_mode,
		store_als_sensor_mode);
static DEVICE_ATTR(als_show_raw, 0664, show_als_sensor_show_raw,
		store_als_sensor_show_raw);
static DEVICE_ATTR(ps_show_raw, 0664, show_ps_sensor_show_raw,
		store_ps_sensor_show_raw);
static DEVICE_ATTR(get_reg_value, 0664, show_get_reg_value, store_get_reg_value);
static DEVICE_ATTR(set_reg_value, 0664, show_set_reg_value, store_set_reg_value);

static ssize_t store_als_poll_delay(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct isl29044_data *data = NULL;
	struct i2c_client *client = NULL;
	unsigned long delay = 0;
	unsigned long flags = 0;

	if (sscanf(buf, "%lu", &delay) != 1)
		return -EINVAL;

	if (delay < 5000)
		delay = 5000;

	pr_info("%s isl29044 called, set delay  parameter is %lu\n", __func__, delay);

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);
	delay = delay / 1000;

	spin_lock_irqsave(&data->als_timer_lock, flags);
	data->als_poll_delay = delay/1000;
	spin_unlock_irqrestore(&data->als_timer_lock, flags);

	if (data->als_pwr_status == 1){
		__cancel_delayed_work(&data->als_work);
		queue_delayed_work(data->als_wq, &data->als_work, msecs_to_jiffies(data->als_poll_delay));
	}
	return count;
}

static ssize_t show_als_poll_delay(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct isl29044_data *data = NULL;
	struct i2c_client *client = NULL;
	u8 delay = 0;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	delay = data->als_poll_delay;

	return snprintf(buf, PAGE_SIZE, "%d\n", delay);
}
static DEVICE_ATTR(als_poll_delay, S_IWUSR| S_IRUGO,
		show_als_poll_delay, store_als_poll_delay);


/*dummy, just for compatible*/
#define DUMMY_SHOW_FUNC(name) \
	static ssize_t show_##name(struct device *dev,\
			struct device_attribute *attr, char *buf)\
	{\
		return snprintf(buf, PAGE_SIZE, "%d\n", 0);\
	}
#define DUMMY_STOR_FUNC(name) \
	static ssize_t store_##name(struct device *dev,\
			struct device_attribute *attr, const char *buf, size_t count)\
	{\
		return count;\
	}

DUMMY_SHOW_FUNC(pdata_value)
DUMMY_STOR_FUNC(pdata_value)
DUMMY_SHOW_FUNC(rdata_value)
DUMMY_STOR_FUNC(rdata_value)
DUMMY_SHOW_FUNC(cdata_value)
DUMMY_STOR_FUNC(cdata_value)

static DEVICE_ATTR(pdata_value, 0664, show_pdata_value, store_pdata_value);
static DEVICE_ATTR(rdata_value, 0664, show_rdata_value, store_rdata_value);
static DEVICE_ATTR(cdata_value, 0664, show_cdata_value, store_cdata_value);

static struct attribute *isl_attrs[] = {
	/*ori*/
	&dev_attr_enable_als_sensor.attr,
	&dev_attr_als_poll_delay.attr,
	/*new*/
	&dev_attr_als_range.attr,
	&dev_attr_als_mode.attr,
	&dev_attr_als_show_raw.attr,
	/*ori*/
	&dev_attr_enable_ps_sensor.attr,
	/*new*/
	&dev_attr_ps_show_raw.attr,
	&dev_attr_set_reg_value.attr,
	&dev_attr_get_reg_value.attr,
	/*data*/
	&dev_attr_pdata_value.attr,
	&dev_attr_cdata_value.attr,
	&dev_attr_rdata_value.attr,
	NULL
};

static const struct attribute_group isl_attr_grp = {
	.attrs = isl_attrs,
};

static int init_input_dev(struct isl29044_data *data)
{
	struct input_dev *als_dev;
	struct input_dev *ps_dev;
	int err;

	als_dev = input_allocate_device();
	if (IS_ERR(als_dev)){
		dev_err(&data->client->dev, "alloc als_dev failed %ld\n", PTR_ERR(als_dev));
		return PTR_ERR(als_dev);
	}

	ps_dev = input_allocate_device();
	if (IS_ERR(ps_dev)){
		dev_err(&data->client->dev, "alloc als_dev failed %ld\n", PTR_ERR(ps_dev));
		err = PTR_ERR(ps_dev);
		goto err_ps_alloc;
	}

	als_dev->name = ALS_INPUT_DEV_NAME;
	als_dev->id.bustype = BUS_I2C;
	als_dev->id.vendor = 0x0001;
	als_dev->id.version = 0x0100;
	als_dev->id.product = 0x0001;
	als_dev->evbit[0] = BIT_MASK(EV_ABS);
	als_dev->absbit[BIT_WORD(ABS_MISC)] |= BIT_MASK(ABS_MISC);
	input_set_abs_params(als_dev, ABS_MISC, 0, 2000 * TP_COEFF, 0, 0);
	als_dev->dev.parent = &data->client->dev;
	als_dev->dev.platform_data = data;

	ps_dev->name = PS_INPUT_DEV_NAME;
	ps_dev->id.bustype = BUS_I2C;
	ps_dev->id.vendor = 0x0001;
	ps_dev->id.product = 0x0002;
	ps_dev->id.version = 0x0100;
	ps_dev->evbit[0] = BIT_MASK(EV_ABS);
	ps_dev->absbit[BIT_WORD(ABS_DISTANCE)] |= BIT_MASK(ABS_DISTANCE);
	input_set_abs_params(ps_dev, ABS_DISTANCE, 0, 1, 0, 0);
	ps_dev->dev.parent = &data->client->dev;
	ps_dev->dev.platform_data = data;

	err = input_register_device(als_dev);
	if (err){
		dev_err(&data->client->dev, "input_register_device als_dev failed %d\n", err);
		goto err_als_reg;
	}

	err = input_register_device(ps_dev);
	if (err){
		dev_err(&data->client->dev, "input_register_device ps_dev failed %d\n", err);
		goto err_ps_reg;
	}

	err = sysfs_create_group(&data->client->dev.kobj, &isl_attr_grp);
	if (err){
		dev_err(&data->client->dev, "sysfs create group als_dev failed %d\n", err);
		goto err_sysfs;
	}

	data->als_input_dev = als_dev;
	data->ps_input_dev= ps_dev;


	/*export info*/
	err = set_sensor_chip_info(ALS, "ISL29044");
	if (err)
		dev_err(&data->client->dev, "set sensor info %d\n", err);

	err = set_sensor_chip_info(PS, "ISL29044");
	if (err)
		dev_err(&data->client->dev, "set sensor info %d\n", err);

	return err;

err_sysfs:
	input_unregister_device(ps_dev);
err_ps_reg:
	input_unregister_device(als_dev);
err_als_reg:
	input_free_device(ps_dev);
err_ps_alloc:
	input_free_device(als_dev);
	return err;
}

static int set_sensor_reg(struct isl29044_data *data)
{
	u8 reg_dat[5] = {0};
	unsigned long flags;
	int i;
	int err;

	pr_info("isl29044 %s called\n", __func__);

	reg_dat[1] = 0x70; /*set ps sleep time to 12.5ms */
	reg_dat[2] = 0x22;/*set interrupte controll*/

	/*TODO:optimise, seperate the als ps*/
	spin_lock_irqsave(&data->ps_timer_lock, flags);

	reg_dat[3] = data->ps_floor_noise + data->ps_lt;
	reg_dat[4] = data->ps_floor_noise + data->ps_ht;
	if (data->als_pwr_status)
		reg_dat[1] |= 0x04;/*bit2:1 enable ALS and IR sensing*/
	if (data->ps_pwr_status)
		reg_dat[1] |= 0x80;/*bit7:1 enable prox sensing*/
	if (data->als_mode)
		reg_dat[1] |= 0x01;/*bit0:1 IR Spectrum sensing data*/
	if (data->als_range)
		reg_dat[1] |= 0x02;/*bit1:1 rang 3200*/
	if (data->ps_led_drv_cur)
		reg_dat[1] |= 0x08;/*bit3:1 prox_dr, 220ma current sink*/

	spin_unlock_irqrestore(&data->ps_timer_lock, flags);

	for (i = 2; i <= 4; i++){
		err = i2c_smbus_write_byte_data(data->client, i, reg_dat[i]);
		if (err < 0){
			dev_err(&data->client->dev, "%s set reg %d err %d\n", __func__, i, err);
			return err;
		}
	}

	err = i2c_smbus_write_byte_data(data->client, 0x01, reg_dat[1]);
	if (err < 0){
		dev_err(&data->client->dev, "%s set reg 1 err %d\n", __func__, err);
		return err;
	}
	return err;
}

static int isl_regulator_configure(struct isl29044_data *data, struct i2c_client *client)
{
	int err = 0;
	data->vdd = regulator_get(&client->dev, "SENSORS_ANALOG_VDD");
	if (IS_ERR(data->vdd)){
		dev_err(&client->dev, "regulator vdd get failed isl29044 %ld\n", PTR_ERR(data->vdd));
		return PTR_ERR(data->vdd);
	}

	err = regulator_set_voltage(data->vdd, 2850000, 2850000);
	if (err){
		dev_err(&client->dev, "regulator get failed isl29044 %d\n", err);
		goto err_reg;
	}

	data->io_vdd = regulator_get(&client->dev, "SENSOR_IO_VDD");
	if (IS_ERR(data->io_vdd)){
		dev_err(&client->dev, "regulator io vdd get failed isl29044 %ld\n", PTR_ERR(data->io_vdd));
		err = PTR_ERR(data->io_vdd);
		goto err_reg;
	}
	return err;
err_reg:
	regulator_put(data->vdd);
	return err;
}

static void isl_regulator_put(struct isl29044_data *data)
{
	regulator_put(data->vdd);
	regulator_put(data->io_vdd);
}

static int isl_regulator_enable(struct isl29044_data *data)
{
	int err = 0;

	err = regulator_enable(data->vdd);
	if (err){
		dev_err(&data->client->dev, "enable vdd failed isl29044 %d\n", err);
		return err;
	}

	err = regulator_enable(data->io_vdd);
	if (err){
		dev_err(&data->client->dev, "enable vdd failed isl29044 %d\n", err);
		goto err_enable;
	}
	return err;
err_enable:
	err = regulator_disable(data->vdd);
	if (err)
		dev_err(&data->client->dev, " %s disable vdd failed isl29044 %d\n", __func__, err);
	return err;
}

static int isl_regulator_disable(struct isl29044_data *data)
{
	int err = 0;

	err = regulator_disable(data->vdd);
	if (err){
		dev_err(&data->client->dev, "disable vdd failed isl29044 %d\n", err);
		return err;
	}

	err = regulator_disable(data->io_vdd);
	if (err){
		dev_err(&data->client->dev, "disable io vdd failed isl29044 %d\n", err);
		return err;
	}
	return err;
}

static void isl29044_early_suspend(struct early_suspend *h)
{
	struct isl29044_data *data = container_of(h, struct isl29044_data, early_drv);
	unsigned long flags;
	int ret;

	pr_info("%s isl29044 called\n", __func__);

	ret = set_als_pwr_st(0, data);
	if (ret){
		dev_err(&data->client->dev, "%s set_ps_pwr_st err %d\n", __func__, ret);
	}

	spin_lock_irqsave(&data->als_timer_lock, flags);
	data->als_pwr_before_suspend = data->als_pwr_status;
	spin_unlock_irqrestore(&data->als_timer_lock, flags);
}

static void isl29044_later_resume(struct early_suspend *h)
{
	struct isl29044_data *data = container_of(h, struct isl29044_data, early_drv);
	int ret = 0;

	pr_info("%s isl29044 called\n", __func__);

	ret = set_als_pwr_st(data->als_pwr_before_suspend, data);
	if (ret){
		dev_err(&data->client->dev, "%s set_als_pwr_st err %d\n", __func__, ret);
	}
}


static void isl29044_reschedule_work(struct isl29044_data *data,
					  unsigned long delay)
{
	__cancel_delayed_work(&data->ps_work);
	queue_delayed_work(data->ps_wq, &data->ps_work, delay);
}

static irqreturn_t isl29044_ps_interrupt(int vec, void *info)
{
	struct isl29044_data *data = (struct isl29044_data*)info;
	/*if the ps coverd before anable, the work queued by set_ps_pwr_st
	 * will cancel, so need set init at 0 */
	data->ps_init = 0;
	wake_lock_timeout(&wlock, HZ/2);
	disable_irq_nosync(data->ps_irq);
	isl29044_reschedule_work(data, 0);

	return IRQ_HANDLED;
}
static int __devinit isl29044_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct isl29044_data *data = NULL;
	u8 reg_dat[8] = {0};
	int i = 0;
	int err = 0;
	int gpio_irq = 0;

	pr_info("%s called\n", __func__);
	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (unlikely(IS_ERR(data))){
		pr_err("%s %s %d error %ld\n", __FILE__, __func__, __LINE__, PTR_ERR(data));
		return PTR_ERR(data);
	}


	err = isl_regulator_configure(data, client);
	if (unlikely(err)){
		pr_err("%s %s %d error %d\n", __FILE__, __func__, __LINE__, err);
		goto err_regulator_cfg;
	}

	err = isl_regulator_enable(data);
	if (unlikely(err)){
		pr_err("%s %s %d error %d\n", __FILE__, __func__, __LINE__, err);
		goto err_regulator_enable;
	}

	/*check id*/
	err = i2c_smbus_read_byte_data(client, 0x00);
	if (0x2E != err >>2){
		pr_err("%s %s %d error %d\n", __FILE__, __func__, __LINE__, err);
		goto err_i2c;
	}

	/*init data*/
	data->client = client;

	data->als_pwr_status = 0;
	data->als_range = 1;
	data->als_mode = 0; /*mode is set from user space, default is 0, visible spectrum ASL sensing data*/
	data->als_poll_delay = 200;
	data->als_show_raw = 0;
	data->als_ir_cnt_set = 1;

	data->ps_pwr_status = 0;
	data->ps_led_drv_cur = 1;
	data->ps_lt = PS_THRESHOLD_L;
	data->ps_ht = PS_THRESHOLD_H;
	data->ps_show_raw = 0;
	data->ps_value = 1;
	data->enable = 0;
	data->ps_poll_delay = PS_POLL_TIME;

	spin_lock_init(&data->als_timer_lock);
	spin_lock_init(&data->ps_timer_lock);

	INIT_DELAYED_WORK(&data->als_work, &do_als_work);
	INIT_DELAYED_WORK(&data->ps_work, &do_ps_work);

	data->als_wq = create_workqueue("als_wq");
	if (IS_ERR(data->als_wq)){
		dev_err(&client->dev, "create workqueue err %ld\n", PTR_ERR(data->als_wq));
		goto err_wq_als;
	}

	data->ps_wq = create_workqueue("ps_wq");
	if (IS_ERR(data->ps_wq)){
		dev_err(&client->dev, "create workqueue err %ld\n", PTR_ERR(data->ps_wq));
		goto err_wq_ps;
	}

	err = set_sensor_reg(data);
	if (err)
		goto err_sensor_reg;

	/*als use polling, the LT and HT set as default, so no als interrupt trigger*/
	reg_dat[5] = 0x00; /*ALS_TH1_LSB*/
	reg_dat[6] = 0xf0; /*ALS_TH2_MSB, bit0:bit3; ALS_TH2_LSB, bit4:bit7*/
	reg_dat[7] = 0xff; /*ALS_TH3_MSB*/
	for (i = 5; i <= 7; i++){
		err = i2c_smbus_write_byte_data(client, i, reg_dat[i]);
		if (err < 0){
			dev_err(&client->dev, "i2c set als interrupts threshold err reg %d err %d\n", i, err);
			goto err_sensor_cfg;
		}
	}

	i2c_set_clientdata(client, data);

	err = init_input_dev(data);
	if (err){
		dev_err(&client->dev, "input dev init err %d",err);
		goto err_input_dev;
	}


	if (get_hw_config_int("sensor/proximity_gpio", &gpio_irq, NULL ) == false)
		goto err_ps_irq;
	if (-1==gpio_irq) {
		pr_err("%s: Failed to get proximity_gpio number in hsad.", __func__);
		err = -ENXIO;
		goto err_gpio;
	}
	data->ps_irq_gpio = gpio_irq;
	data->ps_irq = gpio_to_irq(gpio_irq);

	err = gpio_request(gpio_irq, "gpio_ps_irq");
	if (err) {
		dev_err(&client->dev, "%s: failed to request gpio int1 for irq\n",
			__func__);
		goto err_gpio_request;
	}

	err = gpio_direction_input(gpio_irq);
	if (err) {
		dev_err(&client->dev, "%s: failed to config gpio direction\n",
			__func__);
		goto err_dir;
	}

	err = request_irq(data->ps_irq, isl29044_ps_interrupt,
			IRQF_DISABLED | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_NO_SUSPEND,
			PS_INPUT_DEV_NAME, (void *)data);
	if (err) {
		dev_err(&client->dev, "%s  allocate APDS990x_IRQ failed.\n",
			__func__);
		goto err_irq;
	}

	/* Initialize wakelock*/
	wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "adps990x");/*hold for ps, avoid system sleep*/

	sema_init(&data->als_ps_sema, 1);

#ifdef CONFIG_HAS_EARLYSUSPEND
	data->early_drv.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	data->early_drv.suspend = isl29044_early_suspend;
	data->early_drv.resume = isl29044_later_resume;
	register_early_suspend(&data->early_drv);
#endif
	return 0;
err_irq:
err_dir:
	gpio_free(gpio_irq);
err_gpio_request:
err_gpio:
err_ps_irq:
err_input_dev:
err_sensor_cfg:
err_sensor_reg:
	destroy_workqueue(data->ps_wq);
err_wq_ps:
	destroy_workqueue(data->als_wq);
err_wq_als:
err_i2c:
err_regulator_enable:
	isl_regulator_put(data);
err_regulator_cfg:
	kfree(data);
	data = NULL;
	return err;
	/*free space*/
}

static int __devinit isl29044_remove(struct i2c_client *client)
{
	struct input_dev *als_dev;
	struct input_dev *ps_dev;
	struct isl29044_data *data = NULL;

	dev_info(&client->dev, "%s called\n", __func__);

	data = i2c_get_clientdata(client);

	sysfs_remove_group(&data->client->dev.kobj, &isl_attr_grp);

	/* clean the isl29044 data struct when isl29044 device remove */
	data->client = NULL;
	data->als_pwr_status = 0;
	data->ps_pwr_status = 0;

	als_dev = data->als_input_dev;
	ps_dev = data->ps_input_dev;

	input_unregister_device(als_dev);
	input_unregister_device(ps_dev);
	
	destroy_workqueue(data->ps_wq);
	destroy_workqueue(data->als_wq);

	data->als_input_dev = NULL;
	data->ps_input_dev = NULL;

#ifdef CONFIG_HAS_EARLYSUSPEND
	unregister_early_suspend(&data->early_drv);
#endif
	isl_regulator_disable(data);
	isl_regulator_put(data);

	wake_lock_destroy(&wlock);

	return 0;
}

static const struct i2c_device_id isl29044_id[] = {
	{ISL_DRIVER_NAME, 0},
	{}
};

static unsigned short normal_i2c[] = {ISL29044_I2C_ADDR, I2C_CLIENT_END};

static struct i2c_driver isl29044_i2c_driver = {
	.driver = {
		.name = ISL_DRIVER_NAME,
		.owner = THIS_MODULE,
	},
	.probe = isl29044_probe,
	.remove = isl29044_remove,
	.id_table = isl29044_id,
	.address_list = normal_i2c,
};

static int __init isl29044_init(void)
{
	return i2c_add_driver(&isl29044_i2c_driver);
}

static void __exit isl29044_exit(void)
{
	i2c_del_driver(&isl29044_i2c_driver);
}

module_init(isl29044_init);
module_exit(isl29044_exit);

MODULE_AUTHOR("Liang Wang <bill.wangliang@huawei.com>");
MODULE_DESCRIPTION("ISL29044AIROMZ-T7 sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

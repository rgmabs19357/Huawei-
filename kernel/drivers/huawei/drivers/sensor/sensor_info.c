/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/board_sensors.h>
#include <hsad/config_interface.h>
#include "../../device/hsad_sensor.h"

extern unsigned int g_compass_softiron_type;
static char *sensor_binder_input[SENSOR_MAX] = {NULL};
static char *sensor_chip_info[SENSOR_MAX] = {NULL};
static char *gyro_selfTest_result;
static char *akm_selfTest_result;

static char *input_sensor_name[SENSOR_MAX] = {
	[ACC] = ACCL_INPUT_DEV_NAME,
	[COMPASS] = COMPASS_INPUT_DEV_NAME,
	[GYRO] = GYRO_INPUT_DEV_NAME,
	[ALS] = ALS_INPUT_DEV_NAME,
	[PS] = PS_INPUT_DEV_NAME,
	[HALL] = HALL_INPUT_DEV_NAME,
	[CS] = CAP_INPUT_DEV_NAME
};

int set_sensor_chip_info(enum input_sensor name, const char *chip_info)
{
	if (name >= SENSOR_MAX || chip_info == NULL) {
		pr_err("set_sensor name =%d chip_info = %s\n",
				name, chip_info);
		return -EINVAL;
	}
	sensor_chip_info[name] = (char *)chip_info;
	return 0;
}
EXPORT_SYMBOL(set_sensor_chip_info);

int set_sensor_event(const char *dev_name, const char *event_name)
{
	int i = 0;

	for (i = 0; i < SENSOR_MAX; i++){
		if(input_sensor_name[i]&&(!strncmp(input_sensor_name[i], dev_name, strlen(input_sensor_name[i])))){
			sensor_binder_input[i] = (char *)event_name;
		}
	}
	return 0;
}
EXPORT_SYMBOL(set_sensor_event);

int set_gyro_selfTest_result(enum input_sensor name, const char *result)
{
	if (name >= SENSOR_MAX || result == NULL) {
		pr_err("gyro self test result = %s\n", result);
		return -EINVAL;
	}
	gyro_selfTest_result = (char *)result;
	return 0;
}
EXPORT_SYMBOL(set_gyro_selfTest_result);

int set_compass_selfTest_result(enum input_sensor name, const char *result)
{
	if (name >= SENSOR_MAX || result == NULL) {
		pr_err("compass self test result = %s\n", result);
		return -EINVAL;
	}
	akm_selfTest_result = (char *)result;
	return 0;
}
EXPORT_SYMBOL(set_compass_selfTest_result);
static struct platform_device sensor_input_info = {
	.name = "huawei_sensor",
	.id = -1,
};

static ssize_t show_acc_chip_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("acc_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[ACC]);
}
static DEVICE_ATTR(acc_info, S_IRUGO,
				   show_acc_chip_info, NULL);
static ssize_t show_akm_chip_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("akm_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[COMPASS]);
}
static DEVICE_ATTR(akm_info, S_IRUGO,
				   show_akm_chip_info, NULL);
static ssize_t show_gyro_chip_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("gyro_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[GYRO]);
}
static DEVICE_ATTR(gyro_info, S_IRUGO,
				   show_gyro_chip_info, NULL);
static ssize_t show_ps_chip_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("ps_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[PS]);
}
static DEVICE_ATTR(ps_info, S_IRUGO,
				   show_ps_chip_info, NULL);
static ssize_t show_als_chip_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("als_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[ALS]);
}
static DEVICE_ATTR(als_info, S_IRUGO,
				   show_als_chip_info, NULL);

static ssize_t sensor_show_compass_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_compass_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[COMPASS]);

}
static DEVICE_ATTR(compass_input, S_IRUGO,
				   sensor_show_compass_input, NULL);



static ssize_t sensor_show_acc_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_acc_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[ACC]);
}
static DEVICE_ATTR(acc_input, S_IRUGO,
				   sensor_show_acc_input, NULL);

static ssize_t sensor_show_gyro_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_gyro_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[GYRO]);
}
static DEVICE_ATTR(gyro_input, S_IRUGO,
				   sensor_show_gyro_input, NULL);

static ssize_t sensor_show_ps_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_ps_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[PS]);
}
static DEVICE_ATTR(ps_input, S_IRUGO,
				   sensor_show_ps_input, NULL);

static ssize_t sensor_show_als_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_als_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[ALS]);
}
static DEVICE_ATTR(als_input, S_IRUGO,
				   sensor_show_als_input, NULL);

static ssize_t sensor_show_ori_input(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("sensor_show_als_input dev is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[ORI]);
}
static DEVICE_ATTR(ori_input, S_IRUGO,
				   sensor_show_ori_input, NULL);
static ssize_t show_gyro_selfTest_result(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("gyro self test result is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", gyro_selfTest_result);
}
static ssize_t attr_set_gyro_selftest(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size)
{
	unsigned long val = 0;
	int err = -1;
	int i;

	if (strict_strtoul(buf, 10, &val)) {
		pr_err("gyro self test val invalid, val = %d\n", val);
		return -EINVAL;
	}
	for (i = 0; i < 3; i++) {
		if(set_selftest_lm330(val)) {
			set_gyro_selfTest_result(GYRO, "1");
			pr_info("gyro self test success\n");
			break;
		}else {
			set_gyro_selfTest_result(GYRO, "0");
			pr_err("gyro self test faild, try %d\n", i);
		}
	}
	return size;
}

static DEVICE_ATTR(gyro_selfTest, 0664,
				   show_gyro_selfTest_result, attr_set_gyro_selftest);
static ssize_t show_akm_selfTest_result(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("akm self tset result is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", akm_selfTest_result);
}
static ssize_t write_akm_selfTest_result(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
       unsigned long val = 0;
	if (strict_strtoul(buf, 10, &val)) {
		pr_err("akm self test write invalid val, val = %d\n", val);
		return -EINVAL;
	}
	if(val) akm_selfTest_result = "1";
	else akm_selfTest_result = "0";
	return count;
}
static DEVICE_ATTR(akm_selfTest, 0664,
				   show_akm_selfTest_result, write_akm_selfTest_result);
static ssize_t show_compass_softiron_type(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("compass_softiron_type is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%d\n", g_compass_softiron_type);
}
static DEVICE_ATTR(compass_softiron_type, S_IRUGO,
				   show_compass_softiron_type, NULL);

static ssize_t show_gyro_exist(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int gyro_exist = 0;
	if (dev == NULL) {
		pr_err("device is null\n");
		return -EINVAL;
	}
	gyro_exist = hsad_gyro_exist_info();
	return snprintf(buf, PAGE_SIZE, "%d\n", gyro_exist);
}
static DEVICE_ATTR(gyro_exist, S_IRUGO,
				   show_gyro_exist, NULL);

static ssize_t show_huawei_hall(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("device is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[HALL]);
}
static DEVICE_ATTR(hall_input, S_IRUGO,
				   show_huawei_hall, NULL);
static ssize_t show_huawei_hall_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("als_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[HALL]);
}
static DEVICE_ATTR(hall_info, S_IRUGO,
				   show_huawei_hall_info, NULL);

static ssize_t show_huawei_cap(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("device is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_binder_input[CS]);
}
static DEVICE_ATTR(cs_input, S_IRUGO,
				   show_huawei_cap, NULL);
static ssize_t show_huawei_cap_info(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	if (dev == NULL) {
		pr_err("als_chip info is null\n");
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%s\n", sensor_chip_info[CS]);
}
static DEVICE_ATTR(cap_info, S_IRUGO,
				   show_huawei_cap_info, NULL);
static struct attribute *sensor_input_attributes[] = {
	&dev_attr_ps_input.attr,
	&dev_attr_als_input.attr,
	&dev_attr_acc_input.attr,
	&dev_attr_compass_input.attr,
	&dev_attr_gyro_input.attr,
	&dev_attr_ori_input.attr,
	&dev_attr_acc_info.attr,
	&dev_attr_akm_info.attr,
	&dev_attr_gyro_info.attr,
	&dev_attr_ps_info.attr,
	&dev_attr_als_info.attr,
	&dev_attr_gyro_selfTest.attr,
	&dev_attr_akm_selfTest.attr,
	&dev_attr_compass_softiron_type.attr,
	&dev_attr_gyro_exist.attr,
	&dev_attr_hall_input.attr,
	&dev_attr_hall_info.attr,
       &dev_attr_cs_input.attr,
       &dev_attr_cap_info.attr,
	NULL
};
static const struct attribute_group sensor_input = {
	.attrs = sensor_input_attributes,
};
static int __init sensor_input_info_init(void)
{
	int ret = 0;
	printk(KERN_INFO"[%s] ++", __func__);

	ret = platform_device_register(&sensor_input_info);
	if (ret) {
		pr_err("%s: platform_device_register failed, ret:%d.\n",
				__func__, ret);
		goto REGISTER_ERR;
	}

	ret = sysfs_create_group(&sensor_input_info.dev.kobj, &sensor_input);
	if (ret) {
		pr_err("sensor_input_info_init sysfs_create_group error ret =%d", ret);
		goto SYSFS_CREATE_CGOUP_ERR;
	}
	printk(KERN_INFO"[%s] --", __func__);

	return 0;
SYSFS_CREATE_CGOUP_ERR:
	platform_device_unregister(&sensor_input_info);
REGISTER_ERR:
	return ret;

}

device_initcall(sensor_input_info_init);
MODULE_DESCRIPTION("sensor input info");
MODULE_AUTHOR("huawei driver group of k3v2");
MODULE_LICENSE("GPL");

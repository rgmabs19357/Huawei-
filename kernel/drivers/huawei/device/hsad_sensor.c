/*
 *
 * Copyright (C) 2013 HUAWEI Device Corp,Ltd.
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
#include <linux/kernel.h>
#include <hsad/config_mgr.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <hsad/configdata.h>
#define HSAD_DEV_NAME_LEN 64

int hsad_sensor_get_gpio(char *name)
{
    int gpio = 0;

    if (get_hw_config_int(name, &gpio, NULL ) == false)
        return -1;

    return gpio;
}
int hsad_sensor_get_type(void)
{
	return hsad_sensor_get_gpio("sensor/sensor_type");
}

int hsad_compass_softiron_type(void)
{
	unsigned int type = 0;

	bool ret = get_hw_config_int("sensor/compass_softiron_type", &type, NULL);
	HW_CONFIG_DEBUG("hsad: compass_softiron_type = %d,  ret = %d\n", type, ret);
	if (ret == true) {
		return type;
	}

	return -1;
}

int hsad_gyro_exist_info(void)
{
	unsigned int type = 0;

	bool ret = get_hw_config_int("sensor/gyro_exist_info", &type, NULL);
	HW_CONFIG_DEBUG("hsad: gyro_exist = %d,  ret = %d\n", type, ret);
	if (ret == true) {
		return type;
	}

	return -1;
}
int hsad_apds_get_type(void)
{
	unsigned int type = 0;

	bool ret = get_hw_config_int("apds/apds_type", &type, NULL);
	HW_CONFIG_DEBUG("hsad: apds_type = %d,  ret = %d\n", type, ret);
	if (ret == true) {
		return type;
	}

	return -1;
}
int hsad_get_cap_exist(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("sensor/cap_exist", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

int hsad_get_hall_exist(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("sensor/hall_exist", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

int hsad_get_akm8963_type(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("sensor/akm8963", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

int hsad_get_akm09911_type(void)
{
	bool ret;
	int value = 0;

	ret = get_hw_config_int("sensor/akm09911", &value, NULL);
	if (ret == true) {
		return value;
	}

	return value;
}

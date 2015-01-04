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
#include <hsad/config_mgr.h>
#include "hsad_vibrator.h"

int get_motor_board_type(void)
{
    unsigned int type = 0;

    bool ret = get_hw_config_int("audio/motor_type", &type, NULL);
    //HW_CONFIG_DEBUG("hsad: motor_type = %d\n", type);
    if (ret == true) {
        return type;
    }

    return 1;
}

int get_vibrator_vout_number(void)
{
    unsigned int value = 0;

    bool ret = get_hw_config_int("audio/type_1_vout_number", &value, NULL);
    if (ret == true){
	return (int)value;
    }

    return 20;
}

int get_vibrator_vout_min_voltage(void)
{
    unsigned int value = 0;

    bool ret = get_hw_config_int("audio/type_1_vout_min_voltage", &value, NULL);
    if (ret == true){
	return (int)value;
    }

    return 3000000;
}

int get_vibrator_vout_max_voltage(void)
{
    unsigned int value = 0;

    bool ret = get_hw_config_int("audio/type_1_vout_max_voltage", &value, NULL);
    if (ret == true){
	return (int)value;
    }

    return 3000000;
}

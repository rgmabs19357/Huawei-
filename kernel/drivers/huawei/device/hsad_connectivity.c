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
#define MAX_NFC_CLK_SRC_LEN   32

int hsad_connectivity_get_gpio(char *name)
{
    int gpio = 0;

    if (get_hw_config_int(name, &gpio, NULL ) == false)
        return -1;

    return gpio;
}
int hsad_get_bt_en(void)
{
	return hsad_connectivity_get_gpio("bluetooth/gpio_bt_en");
}

int hsad_get_bt_wake_host(void)
{
	return hsad_connectivity_get_gpio("bluetooth/gpio_bt_wake_host");
}

int hsad_get_host_wake_bt(void)
{
	return hsad_connectivity_get_gpio("bluetooth/gpio_host_wake_bt");
}

/*for Wi-Fi*/
int hsad_wifi_get_gpio(char *name)
{
    int gpio = 0;

    if (get_hw_config_int(name, &gpio, NULL ) == false)
        return -1;

    return gpio;
}
int hsad_get_wifi_enable(void)
{
	return hsad_wifi_get_gpio("wifi/gpio_wifi_enable");
}
int hsad_get_wifi_irq(void)
{
	return hsad_wifi_get_gpio("wifi/gpio_wifi_irq");
}

int hsad_get_nfc_ven_id(void)
{
	return hsad_connectivity_get_gpio("nfc/gpio_nfc_enable");
}

int hsad_get_nfc_irq_id(void)
{
	return hsad_connectivity_get_gpio("nfc/gpio_nfc_irq");
}

int hsad_get_nfc_firm_dload_id(void)
{
	return hsad_connectivity_get_gpio("nfc/gpio_nfc_firm_dload");
}

int hsad_get_nfc_ven_valid_level(void)
{
	return hsad_connectivity_get_gpio("nfc/gpio_nfc_enable_valid");
}

bool hsad_get_nfc_clk_src(char *clk_src)
{
    if(NULL == clk_src)
        return false;

    if(get_hw_config_string("nfc/clock_src", clk_src, MAX_NFC_CLK_SRC_LEN, NULL)){
        return true;
    }

    return false;
}

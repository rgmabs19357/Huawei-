/*
 * linux/arch/arm/mach-k3v2/k3v2_wifi_power.h
 *
 * Copyright (C) 2010 Texas Instruments Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _K3V2_WIFI_POWER_H
#define _K3V2_WIFI_POWER_H

#include <mach/gpio.h>

#define PREALLOC_WLAN_NUMBER_OF_SECTIONS (4)
#define PREALLOC_WLAN_NUMBER_OF_BUFFERS  (320)
#define PREALLOC_WLAN_SECTION_HEADER     (24)
#define WLAN_SKB_BUF_MIN                 (8192)
#define WLAN_SKB_BUF_MAX                 (16384)
#define WLAN_SKB_BUF_NUM                 (16)
#define WLAN_SECTION_SIZE_0     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 128)
#define WLAN_SECTION_SIZE_1     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 128)
#define WLAN_SECTION_SIZE_2     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 512)
#define WLAN_SECTION_SIZE_3     (PREALLOC_WLAN_NUMBER_OF_BUFFERS * 1024)

#define WLAN_MAC_LEN            6
#define NV_WLAN_NUM             193
#define WLAN_VALID_SIZE      17
#define NV_WLAN_VALID_SIZE   12

#define MAC_ADDRESS_FILE "/data/misc/wifi/macwifi"


#if defined CONFIG_MACH_HI6620SFT
#define K3V2_WIFI_IRQ_GPIO      GPIO_2_4
#define K3V2_WIFI_POWER_GPIO    GPIO_2_3
#define K3V2_WIFI_VDD_GPIO      GPIO_3_2
#define K3V2_WIFI_VDD_VOLTAGE   900000
#else
#define K3V2_WIFI_VDD_GPIO
#define K3V2_WIFI_VDD_VOLTAGE   1800000
#endif
extern int hi_sdio_detectcard_to_core(int val);
extern void hi_sdio_set_power(int val);

#endif /*_K3V2_WIFI_POWER_H*/

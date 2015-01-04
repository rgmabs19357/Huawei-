/*
 * Copyright (C) 2009 Texas	Instruments
 *
 * Author: Pradeep Gurumath	<pradeepgurumath@ti.com>
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 */

/* linux/arch/arm/mach-k3v2/k3v2_wifi_power.c
 */

/*=========================================================================
 *
 * histoty
 *
 *=========================================================================
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/err.h>
#include <linux/random.h>
#include <linux/skbuff.h>
#include <generated/mach-types.h>
#include <linux/wifi_tiwlan.h>
#include <asm/mach-types.h>
#include <linux/mux.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/clk.h>
#include <linux/mtd/nve_interface.h>
#include <linux/ctype.h>


#include "k3v2_wifi_power.h"

struct wifi_host_s {
	struct regulator *vdd;
	struct clk *clk;
	struct iomux_block *block;
	struct block_config *config;
	bool bEnable;
	unsigned char macAddr[WLAN_MAC_ADDR_MAXLENGTH];
};

struct wifi_host_s *wifi_host;

static struct sk_buff *wlan_static_skb[WLAN_SKB_BUF_NUM];
typedef struct wifi_mem_prealloc_struct {
	void *mem_ptr;
	unsigned long size;
} wifi_mem_prealloc_t;

static wifi_mem_prealloc_t wifi_mem_array[PREALLOC_WLAN_NUMBER_OF_SECTIONS] = {
	{ NULL, (WLAN_SECTION_SIZE_0 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_1 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_2 + PREALLOC_WLAN_SECTION_HEADER) },
	{ NULL, (WLAN_SECTION_SIZE_3 + PREALLOC_WLAN_SECTION_HEADER) }
};

/*kmalloc memory for wifi*/
void *wifi_mem_prealloc(int section, unsigned long size)
{
	if (section == PREALLOC_WLAN_NUMBER_OF_SECTIONS)
		return wlan_static_skb;
	if ((section < 0) || (section > PREALLOC_WLAN_NUMBER_OF_SECTIONS)) {
		pr_err("%s: is error(section:%d).\n", __func__, section);
		return NULL;
	}
	if (wifi_mem_array[section].size < size) {
		pr_err("%s: is error(size:%lu).\n", __func__, size);
		return NULL;
	}
	return wifi_mem_array[section].mem_ptr;
}

#ifndef	CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(wifi_mem_prealloc);
#endif

/*init wifi buf*/
int init_wifi_mem(void)
{
	int i = 0;

	pr_info("init_wifi_mem.\n");
	for (i = 0; i < WLAN_SKB_BUF_NUM; i++) {
		if (i < (WLAN_SKB_BUF_NUM / 2))
			wlan_static_skb[i] = dev_alloc_skb(WLAN_SKB_BUF_MIN);
		else
			wlan_static_skb[i] = dev_alloc_skb(WLAN_SKB_BUF_MAX);
		if (wlan_static_skb[i] == NULL) {
			pr_err("%s: dev_alloc_skb is error(%d).\n", __func__, i);
			return -ENOMEM;
		}
	}

	for	(i = 0; i < PREALLOC_WLAN_NUMBER_OF_SECTIONS; i++) {
		wifi_mem_array[i].mem_ptr = kzalloc(wifi_mem_array[i].size,
			GFP_KERNEL);
		if (wifi_mem_array[i].mem_ptr == NULL) {
			pr_err("%s: alloc mem_ptr is error(%d).\n", __func__, i);
			return -ENOMEM;
		}
	}
	return 0;
}

/*deinit wifi buf*/
int deinit_wifi_mem(void)
{
	int i = 0;

	pr_info("deinit_wifi_mem.\n");
	for (i = 0; i < WLAN_SKB_BUF_NUM; i++) {
		if (wlan_static_skb[i] != NULL) {
			dev_kfree_skb(wlan_static_skb[i]);
			wlan_static_skb[i] = NULL;
		} else
			break;
	}
	for	(i = 0;	i < PREALLOC_WLAN_NUMBER_OF_SECTIONS; i++) {
		if (wifi_mem_array[i].mem_ptr != NULL) {
			kfree(wifi_mem_array[i].mem_ptr);
			wifi_mem_array[i].mem_ptr = NULL;
		} else
			break;
	}
	return 0;
}

int k3v2_wifi_power(int on)
{
	int ret = 0;
	pr_info("%s: on:%d\n", __func__, on);
#if defined CONFIG_MACH_K3V2OEM1
	if (NULL == wifi_host) {
		pr_err("%s: wifi_host is null\n", __func__);
		return -1;
	}
#endif

	if (on) {
		/*hi_sdio_set_power(on);*/
#if defined CONFIG_MACH_K3V2OEM1
		if (wifi_host->bEnable) {
			pr_err("%s: wifi had power on.\n", __func__);
			return ret;
		}
		ret = clk_enable(wifi_host->clk);
		if (ret < 0) {
			pr_err("%s: clk_enable failed, ret:%d\n", __func__, ret);
			return ret;
		}
		ret = blockmux_set(wifi_host->block, wifi_host->config, NORMAL);
		if (ret < 0) {
			pr_err("%s: blockmux_set failed, ret:%d\n", __func__, ret);
			clk_disable(wifi_host->clk);
			return ret;
		}
#endif

#if defined CONFIG_MACH_K3V2OEM1
		ret = regulator_enable(wifi_host->vdd);
		if (ret < 0) {
			pr_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
			clk_disable(wifi_host->clk);
			ret = blockmux_set(wifi_host->block, wifi_host->config, LOWPOWER);
			if (ret < 0)
				pr_err("%s: blockmux_set failed, ret:%d\n", __func__, ret);
			return ret;
	}
#endif
		gpio_set_value(K3V2_WIFI_POWER_GPIO, 0);
		msleep(100);
		gpio_set_value(K3V2_WIFI_POWER_GPIO, 1);
		msleep(200);
#if defined CONFIG_MACH_K3V2OEM1
		wifi_host->bEnable = true;
#endif
		hi_sdio_set_power(on);
	} else {
		hi_sdio_set_power(on);
		gpio_set_value(K3V2_WIFI_POWER_GPIO, 0);
		msleep(20);

#if defined CONFIG_MACH_K3V2OEM1
		if (!wifi_host->bEnable) {
			pr_err("%s: wifi had power off\n", __func__);
			return ret;
		}
		ret = regulator_disable(wifi_host->vdd);
		if (ret < 0)
			pr_err("%s: regulator_enable failed, ret:%d\n", __func__, ret);
#endif

#if defined CONFIG_MACH_K3V2OEM1
		ret = blockmux_set(wifi_host->block, wifi_host->config, LOWPOWER);
		if (ret < 0)
			pr_err("%s: blockmux_set failed, ret:%d\n", __func__, ret);

		clk_disable(wifi_host->clk);
		wifi_host->bEnable = false;
		/*hi_sdio_set_power(on);*/
#endif
	}

	return ret;
}

#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(k3v2_wifi_power);
#endif

int k3v2_wifi_reset(int on)
{
	pr_info("%s: on:%d.\n", __func__, on);
	if (on)
		gpio_set_value(K3V2_WIFI_POWER_GPIO, 1);
	else
		gpio_set_value(K3V2_WIFI_POWER_GPIO, 0);

	return 0;
}

#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(k3v2_wifi_reset);
#endif

int char2byte(u_char *strori, u_char *outbuf)
{
	int i = 0;
	int err = 0;
	u_char tmp[3];

	for (i = 0; i < WLAN_MAC_ADDR_MAXLENGTH; i++) {
		if ((isxdigit(strori[i*2])) && (isxdigit(strori[i*2+1]))) {
			memset(tmp, 0, 3);
			tmp[0] = strori[i*2];
			tmp[1] = strori[i*2+1];
			outbuf[i] = (u_char)simple_strtoul(tmp, NULL, 16);
		} else {
			pr_err("%s:invalid wlanmac number, strori[%d*2]:%x, strori[%d*2+1]:%x\n",
				__func__, i, strori[i*2], i, strori[i*2+1]);
			err = 1;
			break;
		}
	}

	return err;
}

void byte2char(u_char *strori, u_char *outbuf)
{
	int i = 0;
	u_char tmp[3];

	for (i = 0; i < WLAN_MAC_ADDR_MAXLENGTH; i++) {
		memset(tmp, 0, 3);
		sprintf(tmp, "%02x", strori[i]);
		outbuf[i*2] = tmp[0];
		outbuf[i*2+1] = tmp[1];
	}

	return;
}

int k3v2_wifi_get_mac_addr(unsigned char *buf)
{
	struct nve_info_user nve_wlanmac_info;
	int ret = 0;
	u_char macbuf[WLAN_MAC_ADDR_MAXLENGTH];
	u_char tmpbuf[WLAN_MAC_ADDR_MAXLENGTH];

	if (NULL == buf) {
		pr_err("%s: k3v2_wifi_get_mac_addr failed\n", __func__);
		return -1;
	}

	/* read nv partion*/
	memset(&nve_wlanmac_info, 0, sizeof(struct nve_info_user));
	nve_wlanmac_info.nv_number = WLAN_MAC_NV_NUMBER;
	strcpy(nve_wlanmac_info.nv_name, WLAN_MAC_NV_NAME);
	nve_wlanmac_info.valid_size = WLAN_MAC_NV_VALID_SIZE;
	nve_wlanmac_info.nv_operation = NV_READ;

	ret = nve_direct_access(&nve_wlanmac_info);
	if (ret) {
		pr_err("%s: read nv partion failed\n", __func__);
		memcpy(buf, wifi_host->macAddr, WLAN_MAC_ADDR_MAXLENGTH);
		return 0;
	}
	pr_info("%s: read mac from nv: %s\n", __func__, nve_wlanmac_info.nv_data);

	memset(macbuf, 0x0, WLAN_MAC_ADDR_MAXLENGTH);
	ret = char2byte(nve_wlanmac_info.nv_data, macbuf);
	if (ret) {
		pr_err("%s: char2byte failed, maybe invalid number\n", __func__);
		ret = 0;
	} else {
		memset(tmpbuf, 0x0, WLAN_MAC_ADDR_MAXLENGTH);
		ret = memcmp(tmpbuf, macbuf, WLAN_MAC_ADDR_MAXLENGTH);
		if (ret) {
			memset(tmpbuf, 0xFF, WLAN_MAC_ADDR_MAXLENGTH);
			ret = memcmp(tmpbuf, macbuf, WLAN_MAC_ADDR_MAXLENGTH);
		}
	}

	if (!ret) {
		pr_warning("%s: write wlan mac address to nv partion(original nv mac maybe invalid)\n", __func__);
		/* write to nv partion */
		memset(nve_wlanmac_info.nv_data, 0, sizeof(nve_wlanmac_info.nv_data));
		memcpy(macbuf, wifi_host->macAddr, WLAN_MAC_ADDR_MAXLENGTH);
		pr_info("%s: mac for write:%02x:%02x:%02x:%02x:%02x:%02x\n",
			__func__,
			macbuf[0],
			macbuf[1],
			macbuf[2],
			macbuf[3],
			macbuf[4],
			macbuf[5]);
		byte2char(macbuf, nve_wlanmac_info.nv_data);
		nve_wlanmac_info.nv_operation = NV_WRITE;
		ret = nve_direct_access(&nve_wlanmac_info);
		if (ret) {
			pr_warning("%s: write nv partion failed\n", __func__);
			memcpy(buf, wifi_host->macAddr, WLAN_MAC_ADDR_MAXLENGTH);
			return 0;
		}
	} else {
		if ((macbuf[0]%2) != 0) {
			pr_warning("%s: mac[0] is invalid, force to 0\n", __func__);
			macbuf[0] = 0x0;
		} else {
			pr_info("%s: get wlan mac from nv partion success, mac = %02x:%02x:%02x:%02x:%02x:%02x\n",
				__func__,
				macbuf[0],
				macbuf[1],
				macbuf[2],
				macbuf[3],
				macbuf[4],
				macbuf[5]);
		}
	}

	memcpy(buf, macbuf, WLAN_MAC_ADDR_MAXLENGTH);
	return 0;
}

#ifndef CONFIG_WIFI_CONTROL_FUNC
EXPORT_SYMBOL(k3v2_wifi_get_mac_addr);
#endif
struct wifi_platform_data k3v2_wifi_control = {
	.set_power = k3v2_wifi_power,
	.set_reset = k3v2_wifi_reset,
	.set_carddetect = hi_sdio_detectcard_to_core,
	.get_mac_addr = k3v2_wifi_get_mac_addr,
	.mem_prealloc = wifi_mem_prealloc,
};

#ifdef CONFIG_WIFI_CONTROL_FUNC
static struct resource k3v2_wifi_resources[] = {
	[0] = {
	.name  = "bcm4329_wlan_irq",
	.start = IRQ_GPIO(K3V2_WIFI_IRQ_GPIO),
	.end   = IRQ_GPIO(K3V2_WIFI_IRQ_GPIO),
	.flags = IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHLEVEL
			| IRQF_NO_SUSPEND,/* IORESOURCE_IRQ_HIGHEDGE */
	},
};

static struct platform_device k3v2_wifi_device = {
	.name = "bcm4329_wlan",
	.id = 1,
	.num_resources = ARRAY_SIZE(k3v2_wifi_resources),
	.resource = k3v2_wifi_resources,
	.dev = {
		.platform_data = &k3v2_wifi_control,
	},
};
#endif

static int __init k3v2_wifi_init(void)
{
	int ret = 0;
	int i = 0;
	struct timeval s_time_rec;

	ret = init_wifi_mem();
	if (ret) {
		pr_err("%s: init_wifi_mem failed.\n", __func__);
		goto err_malloc_wifi_host;
	}

	wifi_host = kzalloc(sizeof(struct wifi_host_s), GFP_KERNEL);
	if (!wifi_host)	{
		pr_err("%s: malloc wifi_host failed.\n", __func__);
		ret = -ENOMEM;
		goto err_malloc_wifi_host;
	}

#if defined CONFIG_MACH_K3V2OEM1
	wifi_host->bEnable = false;

	/* get 32kb clock */
	wifi_host->clk = clk_get(NULL, "clk_pmu32kb");
	if (IS_ERR(wifi_host->clk)) {
		pr_err("%s: clk_get failed\n", __func__);
		ret = -ENXIO;
		goto err_clk_get;
	}

	/* get wifiio vdd */
	wifi_host->vdd = regulator_get(NULL, "wifiio-vcc");
	if (IS_ERR(wifi_host->vdd)) {
		pr_err("%s: regulator_get failed.\n", __func__);
		ret = -ENXIO;
		goto err_regulator_get;
	}

	ret = regulator_set_voltage(wifi_host->vdd,
		K3V2_WIFI_VDD_VOLTAGE, K3V2_WIFI_VDD_VOLTAGE);
	if (ret < 0) {
		pr_err("%s: regulator_set_voltage failed, ret:%d.\n",
			__func__, ret);
		ret = -ENXIO;
		goto err_regulator_set_voltage;
	}

	/* set io mux*/
	wifi_host->block = iomux_get_block("block_wifi");
	if (!wifi_host->block) {
		pr_err("%s: iomux_lookup_block failed.\n", __func__);
		ret = -ENXIO;
		goto err_iomux_get_block;
	}

	wifi_host->config = iomux_get_blockconfig("block_wifi");
	if (!wifi_host->config) {
		pr_err("%s: iomux_get_blockconfig failed.\n", __func__);
		ret = -ENXIO;
		goto err_iomux_get_blockconfig;
	}

	ret	= blockmux_set(wifi_host->block, wifi_host->config, LOWPOWER);
	if (ret < 0) {
		pr_err("%s: blockmux_set failed, ret.\n", __func__);
		goto err_blockmux_set;
	}
#else
	/* fpga VDD open forver,if can not request other driver maybe has open*/
	ret = gpio_request(K3V2_WIFI_VDD_GPIO, NULL);
	if (ret < 0) {
		pr_err("%s: gpio_request failed, ret:%d.\n", __func__,
			K3V2_WIFI_VDD_GPIO);
	} else
		gpio_direction_output(K3V2_WIFI_VDD_GPIO, 1);
#endif
	/* set power gpio */
	ret = gpio_request(K3V2_WIFI_POWER_GPIO, NULL);
	if (ret < 0) {
		pr_err("%s: gpio_request failed, ret:%d.\n", __func__,
			K3V2_WIFI_POWER_GPIO);
		goto err_power_gpio_request;
	}
	gpio_direction_output(K3V2_WIFI_POWER_GPIO, 0);
	/* set apwake gpio */
	ret = gpio_request(K3V2_WIFI_IRQ_GPIO, NULL);
	if (ret < 0) {
		pr_err("%s: gpio_request failed, ret:%d.\n", __func__,
			K3V2_WIFI_IRQ_GPIO);
		goto err_irq_gpio_request;
	}
	gpio_direction_input(K3V2_WIFI_IRQ_GPIO);

#ifdef CONFIG_WIFI_CONTROL_FUNC
	ret = platform_device_register(&k3v2_wifi_device);
	if (ret) {
		pr_err("%s: platform_device_register failed, ret:%d.\n",
			__func__, ret);
		goto err_platform_device_register;
	}
#endif
	memset(wifi_host->macAddr, 0, WLAN_MAC_ADDR_MAXLENGTH);

	/*generate random mac address*/
	for (i = 0; i < WLAN_MAC_ADDR_MAXLENGTH; i++) {
		do_gettimeofday(&s_time_rec);
		srandom32(s_time_rec.tv_usec);
		wifi_host->macAddr[i] = random32() & 0xFF;
	}
	wifi_host->macAddr[0] = 0x0;

	return 0;

err_platform_device_register:
	gpio_free(K3V2_WIFI_IRQ_GPIO);
err_irq_gpio_request:
	gpio_free(K3V2_WIFI_POWER_GPIO);
err_power_gpio_request:

#if defined(CONFIG_MACH_K3V2OEM1)
err_blockmux_set:
err_iomux_get_blockconfig:
err_iomux_get_block:
err_regulator_set_voltage:
	regulator_put(wifi_host->vdd);
err_regulator_get:
	clk_put(wifi_host->clk);
err_clk_get:
	kfree(wifi_host);
	wifi_host = NULL;
#else
	gpio_free(K3V2_WIFI_VDD_GPIO);
#endif
err_malloc_wifi_host:
	deinit_wifi_mem();
	return ret;
}

device_initcall(k3v2_wifi_init);

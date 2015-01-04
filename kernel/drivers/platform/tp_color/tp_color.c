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
#include <linux/mtd/nve_interface.h>
#include "tp_color.h"

#define WHITE	0xE1
#define BLACK	0xD2
#define PINK	0xC3
#define RED		0xB4
#define YELLOW	0xA5
#define BLUE	0x96
u8 cypress_tp_color[15]={0};
int is_color_correct(u8 color)
{
	return ((color&0x0f)==((~(color>>4))&0x0f));
}
static u8 read_tp_color_from_nv(char *color_info)
{
	int ret=0;
	struct nve_info_user user_info;
	memset(&user_info, 0, sizeof(user_info));

	user_info.nv_operation = 1;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strcpy(user_info.nv_name, "TPCOLOR");
	if (ret = nve_direct_access(&user_info))
	{
		printk(KERN_ERR "nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	if((!strncmp(user_info.nv_data, "white", strlen("white")))
		||(!strncmp(user_info.nv_data, "black", strlen("black")))
		||(!strncmp(user_info.nv_data, "pink", strlen("pink")))
		||(!strncmp(user_info.nv_data, "red", strlen("red")))
		||(!strncmp(user_info.nv_data, "yellow", strlen("yellow")))
		||(!strncmp(user_info.nv_data, "blue", strlen("blue"))))
	{
		strncpy(color_info, user_info.nv_data, strlen(user_info.nv_data));
		return 0;
	}
	else
	{
		printk(KERN_ERR"[%s]:read_tp_color_from_nv read unormal value!!\n", __func__);
		return -1;
	}
}
static int write_tp_color_to_nv(void)
{
	int ret=0;
	u8 lcd_id=0;
	u8 phone_color=0;
	struct nve_info_user user_info;
	memset(&user_info, 0, sizeof(user_info));
	lcd_id = get_tp_color();
	if(is_color_correct(cypress_tp_color[0]))
		phone_color=cypress_tp_color[0];
	else if(is_color_correct(lcd_id))
		phone_color=lcd_id;
	else
	{
		printk(KERN_ERR "LCD/TP ID both error£¡\n");
		return -1;
	}
	switch(phone_color)
	{
	case WHITE:
			strcpy(user_info.nv_data, "white");
			break;
	case BLACK:
			strcpy(user_info.nv_data, "black");
			break;
	case PINK:
			strcpy(user_info.nv_data, "pink");
			break;
	case RED:
			strcpy(user_info.nv_data, "red");
			break;
	case YELLOW:
			strcpy(user_info.nv_data, "yellow");
			break;
	case BLUE:
			strcpy(user_info.nv_data, "blue");
			break;
	default:
			strcpy(user_info.nv_data, "");
			break;
	}
	user_info.nv_operation = 0;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "TPCOLOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name)-1]='\0';
	ret = nve_direct_access(&user_info);
	if (ret)
	{
		printk(KERN_ERR "nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	printk(KERN_INFO "[%s]:(%s)\n", __func__, user_info.nv_data);
	return ret;
}
static ssize_t attr_get_tp_color_info(struct device *dev, struct device_attribute *attr, char *buf)
{
	int ret=0;
	u8 lcd_id=0;
	u8 phone_color=0;
	lcd_id = get_tp_color();
	printk(KERN_INFO"%s:tp id=%x   lcd id=%x.\n", __func__, cypress_tp_color[0], lcd_id);
	if(is_color_correct(cypress_tp_color[0]))
		phone_color=cypress_tp_color[0];
	else if(is_color_correct(lcd_id))
		phone_color=lcd_id;
	else
	{
		ret=read_tp_color_from_nv(buf);
		if(ret) strcpy(buf, "");
		return strlen(buf);
	}
	switch(phone_color)
	{
	case WHITE:
			strcpy(buf, "white");
			break;
	case BLACK:
			strcpy(buf, "black");
			break;
	case PINK:
			strcpy(buf, "pink");
			break;
	case RED:
			strcpy(buf, "red");
			break;
	case YELLOW:
			strcpy(buf, "yellow");
			break;
	case BLUE:
			strcpy(buf, "blue");
			break;
	default:
			strcpy(buf, "");
			break;
	}
	return strlen(buf);
}

static ssize_t attr_set_tp_color_info(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned long val = simple_strtoul(buf, NULL, 10);
	printk(KERN_INFO"[%s] val=%lu\n", __func__, val);
	if (val == 1) {
		write_tp_color_to_nv();
	}
	return count;
}
static struct device_attribute tp_color_file =
	__ATTR(tp_color_info, 0664, attr_get_tp_color_info, attr_set_tp_color_info);

static struct platform_device huawei_tp_color = {
	.name = "huawei_tp_color",
	.id = -1,
};

static int __init tp_color_info_init(void)
{
	int ret = 0;
	printk(KERN_INFO"[%s] ++", __func__);

	ret = platform_device_register(&huawei_tp_color);
	if (ret) {
		printk(KERN_ERR"%s: platform_device_register failed, ret:%d.\n",
				__func__, ret);
		goto REGISTER_ERR;
	}
	if (device_create_file(&huawei_tp_color.dev, &tp_color_file)) {
		printk(KERN_ERR"%s:Unable to create interface\n", __func__);
		goto SYSFS_CREATE_FILE_ERR;
	}
	printk(KERN_INFO"[%s] --", __func__);
	return 0;

SYSFS_CREATE_FILE_ERR:
	platform_device_unregister(&huawei_tp_color);
REGISTER_ERR:
	return ret;

}

device_initcall(tp_color_info_init);
MODULE_DESCRIPTION("tp color info");
MODULE_AUTHOR("huawei driver group of k3");
MODULE_LICENSE("GPL");

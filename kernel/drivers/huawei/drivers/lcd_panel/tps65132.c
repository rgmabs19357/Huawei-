/*
 * drivers/huawei/drivers/tps65132.c
 *
 * tps65132 driver reffer to lcd
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/param.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/idr.h>
#include <linux/i2c.h>
#include <asm/unaligned.h>
#include <linux/interrupt.h>
#include <asm/irq.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <mach/gpio.h>
#include <linux/mutex.h>
#include <hsad/config_mgr.h>
#include <tps65132.h>

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif




static struct tps65132_configure_info configure_info_arrary[] =
{
	{
        .lcd_name = "mipi_jdi_OTM1902B",
        .vpos_cmd = TPS65132_VOL_55,
        .vneg_cmd = TPS65132_VOL_55,
    },
    {
        .lcd_name = "mipi_cmi_OTM1282B",
        .vpos_cmd = TPS65132_VOL_54,
        .vneg_cmd = TPS65132_VOL_54,
    },
};


static int tps65132_reg_inited(struct i2c_client *client, u8 vpos_target_cmd, u8 vneg_target_cmd)
{
	int vpos = 0;
	int vneg = 0;
	int nRet = 0;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VPOS);
	if (nRet < 0) {
		pr_err("%s read vpos voltage failed\n", __func__);
		goto exit;
	}
	vpos = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VNEG);
	if (nRet < 0) {
		pr_err("%s read vneg voltage failed\n", __func__);
		goto exit;
	}
	vneg = nRet;

	if(  ((vpos & TPS65132_REG_VOL_MASK) == vpos_target_cmd)
      && ((vneg & TPS65132_REG_VOL_MASK) == vneg_target_cmd)
      )
		nRet = 1;
	else
		nRet = 0;

exit:
	return nRet;
}


static int tps65132_reg_init(struct i2c_client *client, u8 vpos_cmd, u8 vneg_cmd)
{
	int vpos = 0;
	int vneg = 0;
	int nRet = 0;
	int app_dis = 0;
	int ctl = 0;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VPOS);
	if (nRet < 0) {
		pr_err("%s read vpos voltage failed\n", __func__);
		goto exit;
	}
	vpos = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_VNEG);
	if (nRet < 0) {
		pr_err("%s read vneg voltage failed\n", __func__);
		goto exit;
	}
	vneg = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_APP_DIS);
	if (nRet < 0) {
		pr_err("%s read app_dis failed\n", __func__);
		goto exit;
	}
	app_dis = nRet;

	nRet = i2c_smbus_read_byte_data(client, TPS65132_REG_CTL);
	if (nRet < 0) {
		pr_err("%s read ctl failed\n", __func__);
		goto exit;
	}
	ctl = nRet;

	vpos = (vpos&(~TPS65132_REG_VOL_MASK)) | vpos_cmd;
	vneg = (vneg&(~TPS65132_REG_VOL_MASK)) | vneg_cmd;
	app_dis = app_dis | TPS65312_APPS_BIT | TPS65132_DISP_BIT | TPS65132_DISN_BIT;
	ctl = ctl | TPS65132_WED_BIT;

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_VPOS, (u8)vpos);
	if (nRet < 0) {
		pr_err("%s write vpos failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_VNEG, (u8)vneg);
	if (nRet < 0) {
		pr_err("%s write vneg failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_APP_DIS, (u8)app_dis);
	if (nRet < 0) {
		pr_err("%s write app_dis failed\n", __func__);
		goto exit;
	}

	nRet = i2c_smbus_write_byte_data(client, TPS65132_REG_CTL, (u8)ctl);
	if (nRet < 0) {
		pr_err("%s write ctl failed\n", __func__);
		goto exit;
	}
	msleep(60);

exit:
	return nRet;
}


static void tps65132_get_target_voltage(int *vpos_target, int *vneg_target)
{
	bool nRet = 0;
	int i = 0;
    char lcd_chip_name[60] = {0};
	struct tps65132_configure_info *p_configure_data = NULL;

	nRet = get_hw_config_string("lcd/devices", lcd_chip_name, 60, NULL);
	if (!nRet) {
		*vpos_target = TPS65132_VOL_54;
		*vneg_target = TPS65132_VOL_54;
		return;
	}

	for(i=0; i<ARRAY_SIZE(configure_info_arrary); i++) {
		if(!strcmp(lcd_chip_name, configure_info_arrary[i].lcd_name)) {
			p_configure_data = &configure_info_arrary[i];
			break;
		}
	}

	if (!p_configure_data) {
		*vpos_target = TPS65132_VOL_54;
		*vneg_target = TPS65132_VOL_54;
	} else {
		*vpos_target = p_configure_data->vpos_cmd;
		*vneg_target = p_configure_data->vneg_cmd;
	}

	pr_info("tps65132 vpos=%d, vneg=%d\n", *vpos_target, *vneg_target);

	return ;
}


static int tps65132_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int retval = 0;
	int nRet = 0;
	int vpos_target = 0;
	int vneg_target = 0;
	struct tps65132_device_info *di = NULL;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		pr_err("[%s,%d]: need I2C_FUNC_I2C\n",__FUNCTION__,__LINE__);
		retval = -ENODEV;
		goto failed_1;
	}

	di = kzalloc(sizeof(*di), GFP_KERNEL);
	if (!di) {
		dev_err(&client->dev, "failed to allocate device info data\n");
		retval = -ENOMEM;
		goto failed_1;
	}

	i2c_set_clientdata(client, di);
	di->dev = &client->dev;
	di->client = client;

	tps65132_get_target_voltage(&vpos_target, &vneg_target);

	nRet = tps65132_reg_inited(di->client, (u8)vpos_target, (u8)vneg_target);
	if (nRet > 0) {
		pr_info("tps65132 inited needn't reset value\n");
	} else if (nRet < 0) {
		pr_err("tps65132 I2C read fail\n");
		retval = -ENODEV;
		goto failed_2;
	} else {
		nRet = tps65132_reg_init(di->client, (u8)vpos_target, (u8)vneg_target);
		if (nRet) {
			pr_err("tps65132_reg_init failed\n");
			retval = -ENODEV;
			goto failed_2;
		}
		pr_info("tps65132 inited succeed\n");
	}

	#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	set_hw_dev_flag(DEV_I2C_DC_DC);
	#endif

	return 0;

failed_2:
	if (di)
		kfree(di);

failed_1:
	return retval;
}



static const struct i2c_device_id tps65132_id[] = {
	{"tps65132",0},
	{},
};


static struct i2c_driver tps65132_driver = {
	.driver = {
		.name = "tps65132",
	},
	.probe = tps65132_probe,
	.id_table = tps65132_id,
};


static int __init tps65132_init(void)
{
	int ret = 0;

	ret = i2c_add_driver(&tps65132_driver);
	if (ret)
		pr_err("Unable to register tps65132 driver\n");

	return ret;
}

fs_initcall(tps65132_init);

static void __exit tps65132_exit(void)
{
	i2c_del_driver(&tps65132_driver);
}
module_exit(tps65132_exit);

MODULE_AUTHOR("HUAWEI");
MODULE_DESCRIPTION("Tps65132 driver");
MODULE_LICENSE("GPL");

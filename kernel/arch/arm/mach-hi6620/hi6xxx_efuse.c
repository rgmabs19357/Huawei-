/*
  * hisilicon efuse driver, hisi_efuse.c
  *
  * Author: butao, from yz
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/smp.h>
#include "hi6xxx_efuse.h"
#include "bsp_mailbox.h"

#define EFUSE_DEV_NAME "efuse"

/*IFC 核间函数调用*/
IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_CHIPID, get_efuse_chipid_value,
              IFC_BIVAR, unsigned char *, pu8Buf, 0,
              IFC_INCNT, unsigned int, uiLength, 0)

IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_CHIPID, set_efuse_chipid_value,
              IFC_INVAR, unsigned char *, pu8Buf, 0,
              IFC_INCNT, unsigned int, uiLength, 0)

IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_AUTHKEY, set_efuse_authkey_value,
              IFC_INVAR, unsigned char *, pu8Buf, 0,
              IFC_INCNT, unsigned int, uiLength, 0)

IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_AUTHKEY, get_efuse_authkey_value,
              IFC_BIVAR, unsigned char *, pu8Buf, 0,
              IFC_INCNT, unsigned int, uiLength, 0)

IFC_GEN_CALL1(MAILBOX_IFC_ACPU_TO_CCPU_SET_EFUSE_DEBUGMODE, set_efuse_securitydebug_value,
              IFC_INCNT, unsigned int , uiMode, 0)

IFC_GEN_CALL1(MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_DEBUGMODE, get_efuse_securitydebug_value,
              IFC_OUTFIX, unsigned int *, puiMode, sizeof(int))

IFC_GEN_CALL2(MAILBOX_IFC_ACPU_TO_CCPU_GET_EFUSE_DIEID, get_efuse_dieid_value,
              IFC_BIVAR, unsigned char *, pu8Buf, 0,
              IFC_INCNT, unsigned int, uiLength, 0)

/*
 * Function name:efusec_ioctl.
 * Discription:complement read/write efuse by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long efusec_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = OK;
	void __user *argp = (void __user *)arg;
	unsigned char efuse_buf[EFUSE_BUF_SIZE] = {0};
    unsigned int ulmode = 0;
	int i = 0;

	switch (cmd) {
	case HISI_EFUSE_READ_CHIPID:
		ret = get_efuse_chipid_value(efuse_buf, BYTE_8, 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_read_chipID failed.\n", __func__, __LINE__);
			break;
		}
		
		for(i = 0; i < 8; i++)
			pr_info("line%d, get_efuse_chipid_value[%d] = %2x.\n", __LINE__, i, efuse_buf[i]);
			
		/*send back to user*/
		if (copy_to_user(argp, efuse_buf, 8)){
			ret = -EFAULT;
			break;
		}

		break;
	case HISI_EFUSE_WRITE_CHIPID:
		/*get data from user*/
		if (copy_from_user(efuse_buf, argp, sizeof(efuse_buf))){
			ret = -EFAULT;
			break;
		}

		for(i = 0; i < 8; i++)
			pr_info("line%d, set_efuse_chipid_value[%d] = %2x.\n", __LINE__, i, efuse_buf[i]);
			
		ret = set_efuse_chipid_value(efuse_buf, sizeof(efuse_buf), 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_set_chipID failed.\n", __func__, __LINE__);
			break;
		}

		break;	
	case HISI_EFUSE_READ_CHIPIDLEN:
		ulmode = BIT_64;
			
		/*send back to user*/
		if (copy_to_user(argp, &ulmode, sizeof(ulmode))){
			ret = -EFAULT;
			break;
		}

		break;
	case HISI_EFUSE_WRITE_AUTHKEY:
		/*get data from user*/
		if (copy_from_user(efuse_buf, argp, sizeof(efuse_buf))){
			ret = -EFAULT;
			break;
		}

		for(i = 0; i < 8; i++)
			pr_info("line%d, set_efuse_authkey_value[%d] = %2x.\n", __LINE__, i, efuse_buf[i]);

		ret = set_efuse_authkey_value(efuse_buf, sizeof(efuse_buf), 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_set_Authkey failed.\n", __func__, __LINE__);
			break;
		}

		break;
	case HISI_EFUSE_READ_AUTHKEY:
		ret = get_efuse_authkey_value(efuse_buf, BYTE_8, 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_get_ChipIDLen failed.\n", __func__, __LINE__);
			break;
		}
		
		for(i = 0; i < 8; i++)
			pr_info("line%d, get_efuse_authkey_value[%d] = %2x.\n", __LINE__, i, efuse_buf[i]);
			
		/*send back to user*/
		if (copy_to_user(argp, efuse_buf, 8)){
			ret = -EFAULT;
			break;
		}

		break;
	case HISI_EFUSE_WRITE_DEBUGMODE:
		/*get data from user*/
		if (copy_from_user(&ulmode, argp, sizeof(ulmode))){
			ret = -EFAULT;
			break;
		}

		pr_info("line%d: set_efuse_securitydebug_value = %2x.\n", __LINE__, ulmode);

		ret = set_efuse_securitydebug_value(ulmode, 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_set_SecureDebugMode failed.\n", __func__, __LINE__);
			break;
		}

		break;
	case HISI_EFUSE_READ_DEBUGMODE:
		ret = get_efuse_securitydebug_value(&ulmode, 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_get_SecureDebugMode failed.\n", __func__, __LINE__);
			break;
		}

		pr_info("line%d: get_efuse_securitydebug_value = %2x.\n", __LINE__, ulmode);

		/*send back to user*/
		if (copy_to_user(argp, &ulmode, sizeof(ulmode))){
			ret = -EFAULT;
			break;
		}

		break;
	case HISI_EFUSE_READ_DIEID:
		ret = get_efuse_dieid_value(efuse_buf, BYTE_20, 1000);
		if (ret < 0) {
			pr_err("%s: %d: efusec_ioctl: efuse_get_DieID failed.\n", __func__, __LINE__);
			break;
		}
		
		for(i = 0; i < 20; i++)
			pr_info("line%d, get_efuse_dieid_value[%d] = %2x.\n", __LINE__, i, efuse_buf[i]);

		/*send back to user*/
		if (copy_to_user(argp, efuse_buf, 20)){
			ret = -EFAULT;
			break;
		}

		break;
	default:
		pr_err("[EFUSE][%s] Unknow command!\n", __func__);
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct file_operations efusec_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = efusec_ioctl,
};

static int __init hisi_efusec_init(void)
{
	int ret = 0;
	int major = 0;
	struct class *efuse_class;
	struct device *pdevice;

	/*创建字符型设备文件节点*/
	major = register_chrdev(0, EFUSE_DEV_NAME, &efusec_fops);
	if (major <= 0) {
		ret = -EFAULT;
		pr_err("hisi efuse: unable to get major for memory devs.\n");
	}

	efuse_class = class_create(THIS_MODULE, EFUSE_DEV_NAME);
	if (IS_ERR(efuse_class)) {
		ret = -EFAULT;
		pr_err("hisi efuse: class_create error.\n");
		goto error1;
	}

	pdevice = device_create(efuse_class, NULL, MKDEV(major, 0), NULL, EFUSE_DEV_NAME);
	if (IS_ERR(pdevice)){
		ret = -EFAULT;
		pr_err("hisi efuse: device_create error.\n");
		goto error2;
	}
	pr_info("efuse init");

	return ret;
error2:
	class_destroy(efuse_class);
	efuse_class = NULL;
error1:
	unregister_chrdev(major, EFUSE_DEV_NAME);
	return ret;
}

late_initcall(hisi_efusec_init);

MODULE_DESCRIPTION("Hisilicon efuse module");
MODULE_AUTHOR("butao@huawei.com.sh");
MODULE_LICENSE("GPL");

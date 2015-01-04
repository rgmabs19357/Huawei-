/*
  * hisilicon memset driver, memsetdev.c
  *
  * Author: wanglei
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
#include <soc_baseaddr_interface.h>
#include <soc_mddrc_axi_interface.h>


static DEFINE_MUTEX(memset_mutex);
u8 reference = 0;

extern unsigned int reg_read_u32(unsigned int pAddr);
extern void reg_write_u32(unsigned int pAddr, unsigned int value);

#define  MEMSET_DEV_NAME "memsetdev"
#define  MEMSET_BUF_SIZE 16
#define  HISI_MEMSET_CMD_LOCK 0x12345678
#define  HISI_MEMSET_CMD_UNLOCK 0x56781234

void memset_lock(void)
{
	mutex_lock(&memset_mutex);
	if (0 == reference) {
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG0_ADDR(SOC_DDRC_AXI_BASE_ADDR, 0x4), 0x6);
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG0_ADDR(SOC_DDRC_AXI_BASE_ADDR, 0x5), 0x6);
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG1_ADDR(SOC_DDRC_AXI_BASE_ADDR), 0xA);
	}
	reference++;
	pr_info("[%s]reference is %d\n",__func__,reference);
	mutex_unlock(&memset_mutex);
}
void memset_unlock(void)
{
	mutex_lock(&memset_mutex);
	if (reference){
		reference--;
	} else {
		pr_err("[%s] error reference is %d\n",__func__,reference);
	}
	if (0 == reference){
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG0_ADDR(SOC_DDRC_AXI_BASE_ADDR, 0x4), 0x1F);
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG0_ADDR(SOC_DDRC_AXI_BASE_ADDR, 0x5), 0x1F);
		reg_write_u32(SOC_MDDRC_AXI_AXI_OSTDCFG1_ADDR(SOC_DDRC_AXI_BASE_ADDR), 0x1F);
	}
	pr_info("[%s]reference is %d\n",__func__,reference);
	mutex_unlock(&memset_mutex);
}

void *hisi_memset(void* p, int v, __kernel_size_t n)
{
    int flags;

    if (unlikely(n < SZ_8M)){
        memset(p,v,n);
    } else {
        memset_lock();
        memset(p,v,n);
        memset_unlock();
    }
}
/*
 * Function name:efusec_ioctl.
 * Discription:complement memset by terms of sending command-words.
 * return value:
 *          @ 0 - success.
 *          @ -1- failure.
 */
static long memset_ioctl(struct file *file, u_int cmd, u_long arg)
{
	int ret = 0;
	switch (cmd) {
	case HISI_MEMSET_CMD_LOCK:
        	memset_lock();
		break;
	case HISI_MEMSET_CMD_UNLOCK:
		memset_unlock();
	 	break;

	default:
		pr_err("error command unknown \n", __func__);
		ret = -ENOTTY;
		break;
	}

	return ret;
}

static const struct file_operations hisi_memset_fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl = memset_ioctl,
};

static int __init hisi_memset_init(void)
{
	int ret = 0;
	int major = 0;
	struct class *memset_class;
	struct device *pdevice;

	/*创建字符型设备文件节点*/
	pr_info("memset init begin");
	major = register_chrdev(0, MEMSET_DEV_NAME, &hisi_memset_fops);
	if (major <= 0) {
		ret = -EFAULT;
		pr_err("hisi memset: unable to get major for memory devs.\n");
	}

	memset_class = class_create(THIS_MODULE, MEMSET_DEV_NAME);
	if (IS_ERR(memset_class)) {
		ret = -EFAULT;
		pr_err("hisi memset: class_create error.\n");
		goto error1;
	}

	pdevice = device_create(memset_class, NULL, MKDEV(major, 0), NULL, MEMSET_DEV_NAME);
	if (IS_ERR(pdevice)){
		ret = -EFAULT;
		pr_err("hisi memset: device_create error.\n");
		goto error2;
	}
	pr_info("memset init end");

	return ret;
error2:
	class_destroy(memset_class);
	memset_class = NULL;
error1:
	unregister_chrdev(major, MEMSET_DEV_NAME);
	return ret;
}

arch_initcall(hisi_memset_init);

MODULE_DESCRIPTION("Hisilicon memsetdev module");
MODULE_LICENSE("GPL");

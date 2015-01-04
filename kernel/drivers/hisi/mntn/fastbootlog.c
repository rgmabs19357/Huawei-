/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  fastbootlog.c    hisi fastbootlog module
 *                   record fastbootlog into filesystem when booting kernel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/stat.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/sysdev.h>
#include <mach/io.h>
#include <mach/platform.h>
#include <mach/early-debug.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <mach/util.h>					/* For mach_call_usermoduleshell*/
#include <linux/uaccess.h>				/* For copy_to_user*/
#include <linux/vmalloc.h>				/* For vmalloc*/

#define EMMC_BLOCK_SIZE 	(512)    	/*same as fastboot emmc raw block size*/
#define EFUSE_COPY_SIZE     (2*EMMC_BLOCK_SIZE)
#define HIPSE_SIZE          (16*EMMC_BLOCK_SIZE + EFUSE_COPY_SIZE)
#define FASTBOOTLOG_BASE	(1280<<10)	/*same as externl/efipartition/partition.h*/
#define FASTBOOTLOG_SIZE	((256<<10)-HIPSE_SIZE) 	/*same as externl/efipartition/partition.h*/
#define HIPSE_BASE                (FASTBOOTLOG_BASE+FASTBOOTLOG_SIZE)
#define MAGIC_STR       "HISI"
#define MAGIC_LEN       4
#define FASTBOOT_ERROR_FLAG            0x00000020
static char *fastboot_log_buff = NULL;
static loff_t fastboot_log_size = 0;
static char *hipse_log_buff = NULL;
static loff_t hipse_log_size = 0;

extern unsigned int g_BitMapOfAbnRst;
extern int k3v2_mmc_raw_read(char *buf, sector_t start_sect, unsigned int block_nums);
extern int k3v2_mmc_raw_write(char *buf, sector_t start_sect, unsigned int block_nums);

static ssize_t hipselog_read(struct file *file, char __user *userbuf,
	size_t bytes, loff_t *off)
{
	return general_proc_file_read(hipse_log_buff+MAGIC_LEN, hipse_log_size-MAGIC_LEN,
				userbuf, bytes, off);
}

static const struct file_operations hipselog_proc_fops = {
	.read = hipselog_read,
};

static int __init  hipselog_dump_init(void)
{
	int i;
	int blks = 0;
	int blkno = 0;
	int ret = 0;
	char magic[MAGIC_LEN+1];
	char buffer[EMMC_BLOCK_SIZE];

    memset(buffer, 0, EMMC_BLOCK_SIZE);
	/*calc the base block number*/
	blks = HIPSE_SIZE/EMMC_BLOCK_SIZE;
	blkno = HIPSE_BASE/EMMC_BLOCK_SIZE;

	ret = k3v2_mmc_raw_read(buffer, blkno, 1);
	if (ret < 0){
		printk(KERN_ERR"%s read emmc error \r\n", __FUNCTION__);
		return -EIO;
	}
	/*no data to record, just return*/
	memcpy(magic, buffer, MAGIC_LEN);
	magic[MAGIC_LEN] = 0;
	/*get fastboot log size*/
	if (strcmp(magic, MAGIC_STR)) {
		return 0;
	}

	printk("%s has hipse log\n", __func__);
	/*we can use uncontinues memory here*/
	hipse_log_buff = (char *)vmalloc(HIPSE_SIZE + 1);
	if (NULL == hipse_log_buff){
		printk(KERN_ERR"hipse log malloc bufferfail\n");
		return -ENOMEM;
	}
	/*raw emmc read and erase*/
	memset(buffer, 0, EMMC_BLOCK_SIZE);
	for (i = 0; i < blks; i++){
	    /*read and erase fastboot log on emmc*/
		ret = k3v2_mmc_raw_read(hipse_log_buff + EMMC_BLOCK_SIZE * i, blkno + i, 1);
		k3v2_mmc_raw_write(buffer , blkno + i, 1);
		if (ret < 0){
			printk(KERN_ERR"%s read emmc error \r\n", __FUNCTION__);
			hipse_log_buff[i*EMMC_BLOCK_SIZE] = 0;
			break;
		}
	}
	hipse_log_size = HIPSE_SIZE;

	if (hipse_log_size != 0) {
		balong_create_log_proc_entry("hipse", S_IRUGO, &hipselog_proc_fops, NULL);
	}

    return 0;
}
arch_initcall(hipselog_dump_init);

static void __exit hipselog_dump_exit(void)
{
	if (hipse_log_size != 0) {
		balong_remove_log_proc_entry("hipse");
	}

	if (hipse_log_buff){
		vfree(hipse_log_buff);
		hipse_log_buff = NULL;
	}
	hipse_log_size = 0;

	return;
}
module_exit(hipselog_dump_exit);

/*****************************************************************************
 Description : copy fastbootlog from fastboot_log_buff into user-space, and update offset
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static ssize_t fastbootlog_read(struct file *file, char __user *userbuf,
	size_t bytes, loff_t *off)
{
	return general_proc_file_read(fastboot_log_buff, fastboot_log_size,
				userbuf, bytes, off);
}

static const struct file_operations fastbootlog_proc_fops = {
	.read = fastbootlog_read,
};


/*****************************************************************************
 Description : fastbootlog init
		      check emmc leaves log to record
		      if there is log, launch work queue, and create /proc/balong/fastbootlog
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static int __init fastbootlog_dump_init(void)
{
	int i;
	int blks = 0;
	int blkno = 0;
	int ret = 0;
	char buffer[EMMC_BLOCK_SIZE];

    memset(buffer, 0, EMMC_BLOCK_SIZE);
	/*calc the base block number*/
	blks = FASTBOOTLOG_SIZE/EMMC_BLOCK_SIZE;
	blkno = FASTBOOTLOG_BASE/EMMC_BLOCK_SIZE;
	ret = k3v2_mmc_raw_read(buffer, blkno, 1);
	if (ret < 0){
		printk(KERN_ERR"%s read emmc error \r\n", __FUNCTION__);
		return -EIO;
	}
	/*no data to record, just return*/
	if (0 == buffer[0]){
		return 0;
	}

	/*we can use uncontinues memory here*/
	fastboot_log_buff = (char *)vmalloc(FASTBOOTLOG_SIZE + 1);
	if (NULL == fastboot_log_buff){
		printk(KERN_ERR"fastboot log malloc bufferfail\n");
		return -ENOMEM;
	}

	/*raw emmc read and erase*/
	memset(buffer, 0, EMMC_BLOCK_SIZE);

	for (i = 0; i < blks; i++){
	    /*read and erase fastboot log on emmc*/
    	ret = k3v2_mmc_raw_read(fastboot_log_buff + EMMC_BLOCK_SIZE * i, blkno + i, 1);
		k3v2_mmc_raw_write(buffer , blkno + i, 1);
		if (ret < 0){
			printk(KERN_ERR"%s read emmc error \r\n", __FUNCTION__);
			fastboot_log_buff[i*EMMC_BLOCK_SIZE] = 0;
			break;
		}
	}
	/*make sure an end*/
	fastboot_log_buff[FASTBOOTLOG_SIZE] = 0;

	/*get fastboot log size*/
	fastboot_log_size = strlen(fastboot_log_buff);

	g_BitMapOfAbnRst |= FASTBOOT_ERROR_FLAG;

	balong_create_log_proc_entry("fastboot", S_IRUGO, &fastbootlog_proc_fops, NULL);

#if 0
	/*delay 3 minutes to make record*/
	INIT_DELAYED_WORK(&fastboot_work, fastbootlog_do_work);
	schedule_delayed_work(&fastboot_work, 180*HZ);
#endif

	return 0;
}
fs_initcall(fastbootlog_dump_init);

/*****************************************************************************
  Description : fastbootlog exit
                     destroy the workqueue
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static void __exit fastbootlog_dump_exit(void)
{
	balong_remove_log_proc_entry("fastboot");

	if (fastboot_log_buff){
		vfree(fastboot_log_buff);
		fastboot_log_buff = NULL;
	}
	fastboot_log_size = 0;

	return;
}
module_exit(fastbootlog_dump_exit);

MODULE_DESCRIPTION("Hisilicon Fastboot Log Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


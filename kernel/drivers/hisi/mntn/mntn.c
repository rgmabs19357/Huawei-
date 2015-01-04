/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  mntn.c    hisi mntn driver, maintain function s when panic/freeze happens
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
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/ioport.h>			/* For io-port access */
#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */
#include <linux/uaccess.h>			/* For copy_to_user/put_user/... */
#include <linux/workqueue.h>		/* For workqueue... */
#include <linux/notifier.h>			/* For notifier... */
#include <mach/reset.h>			/* For register notifier*/
#include <mach/util.h>				/* For mach_call_usermoduleshell*/
#include <linux/delay.h>
#include <asm/stat.h>
#include <mntn/excDrv.h>
#include "../../rfile/rfilesystem_interface.h"

extern unsigned int get_boot_into_recovery_flag(void);
extern int nve_direct_access(struct nve_info_user * user_info);
static int read_nogui_flag(void)
{
    int ret;
    struct nve_info_user user_info;
    int nogui_flag = 0;

    user_info.nv_operation = 1;
    user_info.nv_number = 206;
    user_info.valid_size = 1;
    strcpy(user_info.nv_name, "NOGUI");
    ret = nve_direct_access(&user_info);
    if (ret)
    {
        printk(KERN_ERR "nve_direct_access read error(%d)\n", ret);
        return -1;
    }
    nogui_flag = user_info.nv_data[0];
    printk("[read_nogui_flag]: nogui_flag = %d.\n", nogui_flag);
    if (nogui_flag == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



#define CALLER_DECLARE(name, list, sh_cmd, prop)\
static int name ## _notifier_call(struct notifier_block *cb, unsigned long code, void *p)\
{\
    if((get_boot_into_recovery_flag()==1)&& (read_nogui_flag()==0)) return 0;\
	DRV_STAT_STRU state;\
	int num = 0;\
    	while(1)\
    	{\
    		if(((bsp_linux_stat("/data/cp-log/", &state)) != -1) && ((bsp_linux_stat("/system/etc/log/", &state)) != -1))\
    			break;\
    		msleep(1000);\
    		num++;\
    		if(num > 10)\
    			break;\
    	}\
    	mach_call_usermodeshell(sh_cmd, 0);\
	return 0;\
}\
\
static struct notifier_block name ## _notifier_block = {\
	.notifier_call = name ## _notifier_call,\
};\
\
static int __init name ## _mntn_init(void)\
{\
	if (!prop){\
		return 0;\
	}\
	list ## _regsister_notifier(&name ## _notifier_block);\
	return 0;\
}\
\
static void __exit name ## _mntn_exit(void)\
{\
	if (!prop){\
		return;\
	}\
	list ## _unregsister_notifier(&name ## _notifier_block);\
	return;\
}\
\
module_init(name ## _mntn_init);\
module_exit(name ## _mntn_exit);


CALLER_DECLARE(mcu_freeze_sh, mcu_freeze, "/system/etc/log/mcu_freeze.sh", himntn_gobal_resetlog)
CALLER_DECLARE(mcu_panic_sh, mcu_panic, "/system/etc/log/mcu_panic.sh", HIMNTN_ALWAYS_RESETLOG)
CALLER_DECLARE(modem_panic_sh, modem_panic, "/system/etc/log/modem_panic.sh", himntn_modem_resetlog)
CALLER_DECLARE(modem_reboot_sh, modem_reboot, "/system/etc/log/modem_reboot.sh", himntn_modem_resetlog)
CALLER_DECLARE(modem_freeze_sh, modem_freeze, "/system/etc/log/modem_freeze.sh", himntn_modem_resetlog)
CALLER_DECLARE(hifi_freeze_sh, hifi_freeze, "/system/etc/log/hifi_freeze.sh", himntn_hifi_resetlog)
CALLER_DECLARE(android_freeze_sh, android_freeze, "/system/etc/log/android_freeze.sh", himntn_gobal_resetlog)
CALLER_DECLARE(android_reboot_sh, android_reboot, "/system/etc/log/android_reboot.sh", himntn_gobal_resetlog)
CALLER_DECLARE(wdg_rstlog_save_sh, wdg_rstlog_save, "/system/etc/log/wdg_rstlog_save.sh", himntn_gobal_resetlog)
CALLER_DECLARE(acpuwdg_historylog_write_sh, acpuwdg_historylog_write,"/system/etc/log/acpuwdg_historylog_write.sh", himntn_gobal_resetlog)
CALLER_DECLARE(mculocalwdg_historylog_write_sh, mculocalwdg_historylog_write,"/system/etc/log/mculocalwdg_historylog_write.sh", himntn_gobal_resetlog)
CALLER_DECLARE(mcuglbwdg_historylog_write_sh, mcuglbwdg_historylog_write,"/system/etc/log/mcuglbwdg_historylog_write.sh", himntn_gobal_resetlog)
CALLER_DECLARE(mcu_puzzle_sh, mcu_puzzle, "/system/etc/log/mcu_puzzle.sh", himntn_gobal_resetlog)

MODULE_DESCRIPTION("Hisilicon Device Reset Maintain Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");



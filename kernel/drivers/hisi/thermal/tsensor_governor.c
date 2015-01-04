/*
 * Copyright (c) 2011 Hisilicon Technologies Co., Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <linux/err.h>
#include <linux/io.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/stddef.h>
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/mutex.h>

#include <linux/interrupt.h>
#include <asm/irq.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/reboot.h>
#include <linux/slab.h>
#include <linux/pm_qos_params.h>
#include <linux/delay.h>
#include <linux/timer.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#endif
#include "tsensor_driver.h"
#include "drv_regulator_user.h"
#include "reg_ops.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_ao_sctrl_interface.h"
//#include "balong_nvim.h"
#include "mntn/excDrv.h"
struct tsensor_governor *tsensor_gov = NULL;

extern struct tsensor_info tsensor0_info;
extern struct tsensor_info tsensor1_info;

/*
 * sysfs hook functions
 */
static ssize_t show_tsensor0_localtemp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n",  tsensor0_localremote_temp_get(TSENSOR_LOC_LOCAL, 2));
}

static ssize_t show_tsensor0_remotetemp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n", tsensor0_localremote_temp_get(TSENSOR_LOC_REMOTE, 2));
}

static ssize_t show_tsensor0_temp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n", tsensor0_temp_get());
}

static ssize_t show_tsensor0_state(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d,%d\n", tsensor0_info.hot_temp_num, tsensor0_info.maxfreq_lock);
}

static ssize_t set_tsensor0_state(struct device *dev, struct device_attribute *attr,
			   const char *buf, size_t n)
{
    systemError(0x3f, 3, 0, 0, 0);

    return n;
}

static ssize_t show_tsensor1_localtemp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n",  tsensor1_localremote_temp_get(TSENSOR_LOC_LOCAL, 2));
}

static ssize_t show_tsensor1_remotetemp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n", tsensor1_localremote_temp_get(TSENSOR_LOC_REMOTE, 2));
}

static ssize_t show_tsensor1_temp(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d\n", tsensor1_temp_get());
}

static ssize_t show_tsensor1_state(struct device *dev,
                    struct device_attribute *devattr, char *buf)
{
    /*struct platform_device *pdev = to_platform_device(dev);*/

    return snprintf(buf, sizeof(int), "%d,%d\n", tsensor1_info.hot_temp_num, tsensor1_info.maxfreq_lock);
}


/*注册sysfs接口*/
static DEVICE_ATTR(tsensor0_localtemp, S_IWUSR | S_IRUGO, show_tsensor0_localtemp, NULL);
static DEVICE_ATTR(tsensor0_remotetemp, S_IWUSR | S_IRUGO, show_tsensor0_remotetemp, NULL);
static DEVICE_ATTR(acputemp, S_IWUSR | S_IRUGO, show_tsensor0_temp, NULL);
static DEVICE_ATTR(tsensor0_state, S_IWUSR | S_IRUGO, show_tsensor0_state, set_tsensor0_state);
static DEVICE_ATTR(tsensor1_localtemp, S_IWUSR | S_IRUGO, show_tsensor1_localtemp, NULL);
static DEVICE_ATTR(tsensor1_remotetemp, S_IWUSR | S_IRUGO, show_tsensor1_remotetemp, NULL);
static DEVICE_ATTR(gputemp, S_IWUSR | S_IRUGO, show_tsensor1_temp, NULL);
static DEVICE_ATTR(tsensor1_state, S_IWUSR | S_IRUGO, show_tsensor1_state, NULL);


static struct attribute *tsensor_attributes[] = {
    &dev_attr_tsensor0_localtemp.attr,
    &dev_attr_tsensor0_remotetemp.attr,
    &dev_attr_acputemp.attr,
    &dev_attr_tsensor0_state.attr,
    &dev_attr_tsensor1_localtemp.attr,
    &dev_attr_tsensor1_remotetemp.attr,
    &dev_attr_gputemp.attr,
    &dev_attr_tsensor1_state.attr,
    NULL
};

static const struct attribute_group tsensor_group = {
    .attrs = tsensor_attributes,
};


static inline void monitor_timer_exit(void)
{
	cancel_delayed_work_sync(&tsensor_gov->tsensor_monitor_work);
}

static int tsensor_reboot_notify(struct notifier_block *nb,
				unsigned long code, void *unused)
{
	if ((code == SYS_RESTART) || (code == SYS_POWER_OFF) ||
		(code == SYS_HALT)) {
		/*printk("tsensor_reboot_notify code 0x%lx stop read tsensor\n", code);*/
		monitor_timer_exit();
		return NOTIFY_OK;
	}
	return NOTIFY_DONE;
}

static struct notifier_block tsensor_reboot_nb = {
	.notifier_call	= tsensor_reboot_notify,
	.next		= NULL,
	.priority	= INT_MAX, /* before any real devices */
};

/*****************************************************************************
 函 数 名  : tsensor_monitor_work_fn
 功能描述  : tsensor 温度监控保护work函数
 输入参数  :
             work:work句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static void tsensor_monitor_work_fn(struct work_struct *work)
{
    /*printk(KERN_INFO"tsensor_monitor_work_fn\n");*/

    /*读取Tsensor的温度，做温度保护 */
    tsensor_temp_protect();
}

/*****************************************************************************
 函 数 名  : hi6620_tsensor_probe
 功能描述  : tsensor driver probe函数
 输入参数  :
             pdev:设备句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static int hi6620_tsensor_probe(struct platform_device *pdev)
{
    struct tsensor_devinfo *devinfo = NULL;
    int ret = 0;

    printk(KERN_INFO "hi6620_tsensor_probe\n");

    /*全局变量初始化 */
    tsensor_gov = kzalloc(sizeof(struct tsensor_governor), GFP_KERNEL);
    if (!tsensor_gov) {
        printk(KERN_ERR "hi6620_tsensor_probe kzalloc failed\n");
        pr_err("%s:Cannot allocate memory\n", __func__);
        return -ENOMEM;
    }

    devinfo = kzalloc(sizeof(struct tsensor_devinfo), GFP_KERNEL);
    if (!devinfo) {
        printk(KERN_ERR "hi6620_tsensor_probe kzalloc failed111\n");
        pr_err("%s:Cannot allocate memory\n", __func__);
        goto probe_err;
    }

    devinfo->pdev = pdev;
    devinfo->dev = &pdev->dev;

    kobject_uevent(&pdev->dev.kobj, KOBJ_ADD);
    platform_set_drvdata(pdev, devinfo);

    /*创建sysfs节点 */
    ret = sysfs_create_group(&pdev->dev.kobj, &tsensor_group);
    if (ret) {
        printk(KERN_ERR "hi6620_tsensor_probe sysfs_create_group failed\n");
        dev_err(&pdev->dev, "could not create sysfs files\n");
        goto probe_err;
    }

    /* Init delayed work to monitor tsensor temperature */
    INIT_DELAYED_WORK(&tsensor_gov->tsensor_monitor_work,
             tsensor_monitor_work_fn);
    tsensor_gov->average_period = TSENSOR_NORMAL_MONITORING_RATE;

    mutex_init(&(tsensor_gov->lock));

    register_reboot_notifier(&tsensor_reboot_nb);

    /*printk(KERN_ERR "before tsensor_init\n");*/

    /*tsensor初始化,AC核解耦后，该调用放到modem_init.c中，因为要使用邮箱和C核NV，需保证C核初始化完成*/
    /*ret = tsensor_init();
    if (ret != 0) {
        dev_err(&pdev->dev, "tsensor_init\n");
        goto probe_err;
    }*/

    printk(KERN_INFO "hi6620_tsensor_probe probe success\n");

    return ret;

probe_err:
    platform_set_drvdata(pdev, NULL);
    if (devinfo)
    {
        kfree(devinfo);
        devinfo = NULL;
    }
    if (tsensor_gov)
    {
        kfree(tsensor_gov);
        tsensor_gov = NULL;
    }
    return ret;
}

#ifdef CONFIG_PM
/*****************************************************************************
 函 数 名  : hi6620_tsensor_suspend
 功能描述  : tsensor driver suspend函数
 输入参数  :
             pdev:设备句柄
             state:pm状态
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static int  hi6620_tsensor_suspend(struct platform_device *pdev, pm_message_t state)
{
    /*tsensor进入休眠状态 */
    tsensor_suspend();

    /*取消定时监控 */
    cancel_delayed_work_sync(&tsensor_gov->tsensor_monitor_work);

    dev_info(&pdev->dev, "tsensor suspend successfully\n");

    return 0;
}

/*****************************************************************************
 函 数 名  : hi6620_tsensor_resume
 功能描述  : tsensor driver resume函数
 输入参数  :
             pdev:设备句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static int hi6620_tsensor_resume(struct platform_device *pdev)
{
    int ret = 0;

    /*tsensor重新初始化 */
    tsensor_resume();

    dev_info(&pdev->dev, "tsensor resume successfully\n");

    return ret;
}
#endif

/*****************************************************************************
 函 数 名  : hi6620_tsensor_remove
 功能描述  : tsensor driver remote函数
 输入参数  :
             pdev:设备句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static int __devexit hi6620_tsensor_remove(struct platform_device *pdev)
{
    struct tsensor_devinfo *devinfo = platform_get_drvdata(pdev);

    printk(KERN_INFO"hi6620_tsensor_remove\n");

    if (devinfo == NULL) {
        dev_err(&pdev->dev, "devinfo is null\n");
        return -ENODEV;
    }

    /*tsensor挂起*/
    tsensor_suspend();

    kfree(devinfo);

    kfree(tsensor_gov);
    tsensor_gov = NULL;

    platform_set_drvdata(pdev, NULL);


    return 0;
}

/*****************************************************************************
 函 数 名  : hi6620_tsensor_shutdown
 功能描述  : tsensor driver shutdown函数
 输入参数  :
             pdev:设备句柄
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/

static void hi6620_tsensor_shutdown(struct platform_device *pdev)
{
    struct tsensor_devinfo *devinfo = platform_get_drvdata(pdev);

    printk(KERN_INFO"hi6620_tsensor_shutdown\n");

    if (devinfo == NULL) {
        dev_err(&pdev->dev, "devinfo is null\n");
        return ;
    }

    /*取消tsensor温度监控*/
    cancel_delayed_work_sync(&tsensor_gov->tsensor_monitor_work);

    unregister_reboot_notifier(&tsensor_reboot_nb);

    /*tsensor挂起 */
    tsensor_suspend();

    kfree(devinfo);
    devinfo = NULL;

    kfree(tsensor_gov);
    tsensor_gov = NULL;

    platform_set_drvdata(pdev, NULL);

    printk("hi6620_tsensor_shutdown\n");

    return;
}

#define  DRIVER_NAME  "hi6620-tsensor"
/*tsensor platform driver信息 */
static struct platform_driver hi6620_tsensor_driver = {
    .probe      = hi6620_tsensor_probe,
#ifdef CONFIG_PM
    .suspend   = hi6620_tsensor_suspend,
    .resume    = hi6620_tsensor_resume,
#endif
    .remove   = __devexit_p(hi6620_tsensor_remove),
    .shutdown  = hi6620_tsensor_shutdown,
    .driver      = {
    .owner  = THIS_MODULE,
    .name   = DRIVER_NAME,
    },
};

static void hi6620_tsensor_release(struct device *dev)
{
}

static struct platform_device hi6620_tsensor_device = {
        .name           = DRIVER_NAME,
        .id             = 1,
        .dev = {
            .release      = hi6620_tsensor_release,
    },
};

/*****************************************************************************
 函 数 名  : hi6620_tsensor_init
 功能描述  : tsensor driver初始化函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/
int __init hi6620_tsensor_init(void)
{
    int ret;

	ret = platform_device_register(&hi6620_tsensor_device);
    if(ret)
    {
        printk(KERN_ERR"hi6620 platform_device_register erro ret %d\n", ret);
        return ret;
    }

    ret = platform_driver_register(&hi6620_tsensor_driver);
    if (ret < 0)
    {
        printk(KERN_ERR"hi6620 platform_driver_register ret %d\n", ret);
        platform_device_unregister(&hi6620_tsensor_device);
        return ret;
    }

    printk(KERN_INFO"hi6620_tsensor_init ret %d\n", ret);

    return ret;
}

/*****************************************************************************
 函 数 名  : hi6620_tsensor_exit
 功能描述  : tsensor driver退出函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月6日
    作    者   : 刘龙 00217270
    修改内容   : 新生成函数

*****************************************************************************/
static void __exit hi6620_tsensor_exit(void)
{
    printk(KERN_INFO"hi6620_tsensor_exit.\n");
    platform_driver_unregister(&hi6620_tsensor_driver);
}

late_initcall(hi6620_tsensor_init);
module_exit(hi6620_tsensor_exit);

MODULE_DESCRIPTION("Hi6620 Tsensor Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("<liulong@huawei.com>");


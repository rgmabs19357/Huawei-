/*
 * Filename:kernel/drivers/input/keyboard/k3v2_power_key.c
 * Discription:realize power key in kernel.
 * Copyright (C) 2011 Hisilicon
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Revision history:
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/earlysuspend.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/mux.h>
#include <mach/irqs.h>
#include <linux/gpio.h>
//#include <mach/k3_keypad.h>
#include <linux/reboot.h>
#include <soc_ao_sctrl_interface.h>
#include <linux/mtd/nve_interface.h>
#include <linux/mtd/nve_number.h>
#include <asm/irq_regs.h>
#include <mntn/excDrv.h>
#include <linux/wakelock.h>


#if defined (CONFIG_ARCH_HI6620)
#include <linux/pm_qos_params.h>
extern struct pm_qos_request_list g_cpunum_policy_qos;
extern struct pm_qos_request_list g_ddr_policy_qos;
#endif

#define TRUE				    (1)
#define FALSE				    (0)

#define POWER_KEY_RELEASE       (0)
#define POWER_KEY_PRESS         (1)
#define POWER_KEY_LONG_PRESS_4S (2)


/* To be delete after pmu irq.h ok --start */
//#include <mach/platform.h>
//#define IRQ_PMU_BASE		            (SOC_PMUSSI_BASE_ADDR + 0x003)

#define IRQ_POWER_KEY_LONG_PRESS_4S		POWERON_D4sR_TYPE//(IRQ_PMU_BASE + 4)
#define IRQ_POWER_KEY_RELEASE	        POWERON_D20F_TYPE//(IRQ_PMU_BASE + 5)
#define IRQ_POWER_KEY_PRESS	            POWERON_D20R_TYPE//(IRQ_PMU_BASE + 6)
/* To be delete after pmu irq.h ok --end */
#define MANUAL_DUMP_NV_NAME         "MANUDMP"
#define BOOT_TO_MANUAL_DUMP_TRUE    (1)
#define BOOT_TO_MANUAL_DUMP_FALSE   (0)

struct k3v2_power_key {
	struct input_dev *input_dev;
	void __iomem *base;
	int power_key_press_irq;
	int power_key_release_irq;
	int power_key_long_press_4s_irq;
	struct wake_lock wake_lock;
	int key_pressed_flag;
};
void (*notify_call)(int);
void notify_key_status_to_device(void (*callback)(int))
{
    notify_call = callback;
}
extern void gpio_key_vol_updown_press_set(int istate_val);
extern int gpio_key_vol_updown_press_get(void);

static int k3v2_power_key_open(struct input_dev *dev)
{
	return 0;
}

static void k3v2_power_key_close(struct input_dev *dev)
{
	return 0;
}

static irqreturn_t k3v2_power_key_irq_handler(int irq, void *dev_id)
{
	struct k3v2_power_key *power_key = (struct k3v2_power_key *)dev_id;

	switch(irq) {
		case IRQ_POWER_KEY_PRESS:
			printk(KERN_DEBUG "[%s]response press interrupt!\n", __FUNCTION__);
			input_report_key(power_key->input_dev, KEY_POWER, POWER_KEY_PRESS);
			input_sync(power_key->input_dev);
			break;
		case IRQ_POWER_KEY_RELEASE:
			printk(KERN_DEBUG "[%s]response release interrupt!\n", __FUNCTION__);
			if ((KEY_VOLUMEUP + KEY_VOLUMEDOWN) == gpio_key_vol_updown_press_get())
			{
				gpio_key_vol_updown_press_set(0);
				if (check_himntn(HIMNTN_PRESS_KEY_TO_FASTBOOT))
				{
					systemError(0x25, EXCH_S_LOGDUMP, 0,0,0);
				}
			}
			input_report_key(power_key->input_dev, KEY_POWER, POWER_KEY_RELEASE);
			input_sync(power_key->input_dev);
            if(notify_call) {
                (*notify_call)(POWER_KEY_RELEASE);
            }
			power_key->key_pressed_flag = TRUE;
			break;

		case IRQ_POWER_KEY_LONG_PRESS_4S:
			printk(KERN_DEBUG "[%s]long press 4s interrupt! start reboot system\n", __FUNCTION__);
			//machine_restart("softreset");
			if(notify_call) {
                (*notify_call)(POWER_KEY_LONG_PRESS_4S);
            }
			printk(KERN_DEBUG "[%s]finish reboot system\n", __FUNCTION__);
			break;

		default:
			printk(KERN_ERR "[%s]invalid irq %d!\n", __FUNCTION__, irq);
			break;
	}

	return IRQ_HANDLED;
}

static int __devinit k3v2_power_key_probe(struct platform_device* pdev)
{
	struct k3v2_power_key *power_key = NULL;
	struct input_dev *input_dev = NULL;
	int err;

	if(NULL == pdev) {
		printk(KERN_ERR "[Pwrkey]parameter error!\n");
		err = -EINVAL;
		return err;
	}

	power_key = kzalloc(sizeof(struct k3v2_power_key), GFP_KERNEL);
	if(!power_key) {
		dev_err(&pdev->dev, "Failed to allocate struct k3v2_power_key!\n");
		err = -ENOMEM;
		return err;
	}

	input_dev = input_allocate_device();
	if (!input_dev) {
		dev_err(&pdev->dev, "Failed to allocate struct input_dev!\n");
		err = -ENOMEM;
		goto err_alloc_input_device;
	}

	input_dev->name = pdev->name;
	input_dev->id.bustype = BUS_HOST;
	input_dev->dev.parent = &pdev->dev;
	input_set_drvdata(input_dev, power_key);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(KEY_POWER, input_dev->keybit);
	input_dev->open = k3v2_power_key_open;
	input_dev->close = k3v2_power_key_close;

	power_key->input_dev = input_dev;
	power_key->key_pressed_flag = FALSE;
	wake_lock_init(&power_key->wake_lock, WAKE_LOCK_SUSPEND, "power_key");

	power_key->power_key_press_irq = platform_get_irq(pdev, 0);
	if (power_key->power_key_press_irq < 0) {
		dev_err(&pdev->dev, "Failed to get power key press irq!\n");
		err = power_key->power_key_press_irq;
		goto err_get_press_irq;

	}

	err = request_irq(power_key->power_key_press_irq, k3v2_power_key_irq_handler, IRQF_NO_SUSPEND, pdev->name, power_key);
	if (err) {
		dev_err(&pdev->dev, "Failed to request press interupt handler!\n");
		goto err_request_press_irq;
	}

	power_key->power_key_release_irq = platform_get_irq(pdev, 1);
	if (power_key->power_key_release_irq < 0) {
		dev_err(&pdev->dev, "Failed to get power key release irq!\n");
		err = power_key->power_key_release_irq;
		goto err_get_release_irq;
	}

	err = request_irq(power_key->power_key_release_irq, k3v2_power_key_irq_handler, IRQF_NO_SUSPEND, pdev->name, power_key);
	if (err) {
		dev_err(&pdev->dev, "Failed to request release interupt handler!\n");
		goto err_request_release_irq;
	}

	power_key->power_key_long_press_4s_irq= platform_get_irq(pdev, 2);
	if (power_key->power_key_long_press_4s_irq < 0) {
		dev_err(&pdev->dev, "Failed to get power key long_press_4s irq!\n");
		err = power_key->power_key_long_press_4s_irq;
		goto err_get_long_press_4s_irq;
	}

	err = request_irq(power_key->power_key_long_press_4s_irq, k3v2_power_key_irq_handler, IRQF_NO_SUSPEND, pdev->name, power_key);
	if (err) {
		dev_err(&pdev->dev, "Failed to request long_press_4s interupt handler!\n");
		goto err_request_long_press_4s_irq;
	}

	err = input_register_device(power_key->input_dev);
	if (err) {
		dev_err(&pdev->dev, "Failed to register input device!\n");
		goto err_register_device;
	}

	device_init_wakeup(&pdev->dev, true);
	platform_set_drvdata(pdev, power_key);
	dev_info(&pdev->dev, "k3v2 power key driver probes successfully!\n");

	return 0;

err_register_device:
    free_irq(power_key->power_key_long_press_4s_irq, power_key);
err_get_long_press_4s_irq:
err_request_long_press_4s_irq:
	free_irq(power_key->power_key_release_irq, power_key);
err_request_release_irq:
err_get_release_irq:
	free_irq(power_key->power_key_press_irq, power_key);
err_request_press_irq:
err_get_press_irq:
	input_free_device(input_dev);
	wake_lock_destroy(&power_key->wake_lock);
err_alloc_input_device:
	kfree(power_key);
	power_key = NULL;
	pr_info(KERN_ERR "K3v2 power_key probe failed! ret = %d.\n", err);
	return err;
}

static int __devexit k3v2_power_key_remove(struct platform_device *pdev)
{
	struct k3v2_power_key *power_key =  platform_get_drvdata(pdev);

	if(power_key == NULL){
		dev_info(&pdev->dev, "get invalid power_key pointer\n");
		return -EINVAL;
	}

	free_irq(power_key->power_key_press_irq, power_key);
	free_irq(power_key->power_key_release_irq, power_key);
    free_irq(power_key->power_key_long_press_4s_irq, power_key);

	wake_lock_destroy(&power_key->wake_lock);

	input_unregister_device(power_key->input_dev);
	platform_set_drvdata(pdev, NULL);
	kfree(power_key);

	return 0;
}

#ifdef CONFIG_PM
static int k3v2_power_key_suspend(struct platform_device *pdev)
{
	struct k3v2_power_key *power_key =  platform_get_drvdata(pdev);

	power_key->key_pressed_flag = FALSE;

	pr_info("[%s]suspend successfully\n", __FUNCTION__);
	return 0;
}

static int k3v2_power_key_resume(struct platform_device *pdev)
{
	struct k3v2_power_key *power_key =  platform_get_drvdata(pdev);

	if (TRUE == power_key->key_pressed_flag){
		wake_lock_timeout(&power_key->wake_lock, HZ/2);
#if defined (CONFIG_ARCH_HI6620)
		pm_qos_update_request(&g_cpunum_policy_qos, PM_QOS_CPU_NUMBER_MIN_VALUE_FOR_DISPLAY);
		pm_qos_update_request(&g_ddr_policy_qos, 533000);
#endif
	}

	pr_info("[%s]resume successfully\n", __FUNCTION__);
	return 0;
}
#endif


struct platform_driver k3v2_power_key_driver = {
	.probe = k3v2_power_key_probe,
	.remove = __devexit_p(k3v2_power_key_remove),
	.driver = {
		.name = "k3v2_power_key",
		.owner = THIS_MODULE,
	},
	#ifdef CONFIG_PM
	.suspend = k3v2_power_key_suspend,
	.resume = k3v2_power_key_resume,
	#endif
};

static int __init k3v2_power_key_init(void)
{
	pr_info(KERN_INFO "k3v2 power key init!\n");

	return platform_driver_register(&k3v2_power_key_driver);
}

static void __exit k3v2_power_key_exit(void)
{
	pr_info(KERN_INFO "k3v2 power key exit!\n");
	platform_driver_unregister(&k3v2_power_key_driver);
}

module_init(k3v2_power_key_init);
module_exit(k3v2_power_key_exit);
MODULE_AUTHOR("Hisilicon K3 Driver Group");
MODULE_DESCRIPTION("K3v2 keypad platform driver");
MODULE_LICENSE("GPL");

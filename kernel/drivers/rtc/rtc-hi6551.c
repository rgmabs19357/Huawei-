
#include <linux/platform_device.h>
#include <mach/pmussi_drv.h>
#include <linux/rtc.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <soc_smart_interface.h>
#include <mach/platform.h>
#include "bsp_ao_sctrl.h"

#include <linux/reboot.h>
#include <linux/syscalls.h>
#include <linux/workqueue.h>
#include <linux/init.h>
#include <linux/kthread.h>

/*
 * Externel RTC Register definitions
 */
#define	RTCCR_A0		SOC_SMART_RTCCR_A0_ADDR(0)	/* RTC_A Data  register 0 bit[7:0] */
#define	RTCCR_A1		SOC_SMART_RTCCR_A1_ADDR(0)	/* RTC_A Data  register 1 bit[15:8] */
#define	RTCCR_A2		SOC_SMART_RTCCR_A2_ADDR(0)	/* RTC_A Data  register 2 bit[23:16] */
#define	RTCCR_A3		SOC_SMART_RTCCR_A3_ADDR(0)	/* RTC_A Data  register 3 bit[31:24] */
#define	RTCLR_A0		SOC_SMART_RTCLR_A0_ADDR(0)	/* RTCLR_A Data load register 0 bit[7:0]*/
#define	RTCLR_A1		SOC_SMART_RTCLR_A1_ADDR(0)	/* RTCLR_A Data load register 1 bi[15:8]*/
#define	RTCLR_A2		SOC_SMART_RTCLR_A2_ADDR(0)	/* RTCLR_A Data load register 2 bit[23:16]*/
#define	RTCLR_A3		SOC_SMART_RTCLR_A3_ADDR(0)	/* RTCLR_A Data load register 3 bit[31:24]*/
#define	RTCCTRL_A		SOC_SMART_RTCCTRL_A_ADDR(0) /* RTCCTRL_A Control register */

#define	RTCMR_A_A0		SOC_SMART_RTCMR_A_A0_ADDR(0)	/* RTC_A_A Match register 0 bit[7:0]*/
#define	RTCMR_A_A1		SOC_SMART_RTCMR_A_A1_ADDR(0)	/* RTC_A_A Match register 1 bi[15:8]*/
#define	RTCMR_A_A2		SOC_SMART_RTCMR_A_A2_ADDR(0)	/* RTC_A_A Match register 2 bit[23:16]*/
#define	RTCMR_A_A3		SOC_SMART_RTCMR_A_A3_ADDR(0)	/* RTC_A_A Match register 3 bit[31:24]*/

#define	PMU_REG_IRQ3	SOC_SMART_IRQ3_ADDR(0)
#define	RTC_IRQ3_IMSC	SOC_SMART_IRQ3_MASK_ADDR(0)     /* IRQ3_MASK Interrupt mask and set register */
#define	RTC_ALARM_A	    0x001							/* A Alarm interrupt bit */


/*internal RTC Register 32bit*/
#define	RTCDR			0x000	/* Data  register */
#define	RTCMR			0x004	/* Match register */
#define	RTCLR			0x008	/* Data load register */
#define	RTCCR			0x00c	/* Control register  1:enable,0:disable*/
#define	RTCIMSC		    0x010	/* Interrupt mask and set register  1:enable,0:disable*/
#define	RTCRIS			0x014	/* Raw interrupt status register  1:interrupted*/
#define	RTCMIS			0x018  	/* Masked interrupt status register  1:interrupted*/
#define	RTCICR			0x01C	/* Interrupt clear register  1:clear interrupt*/
#define	RTC_ALARM_INT	(1 << 0)	/* Alarm interrupt bit */

#define PMU_RTC_VERSION        0
#define PMU_RTC_ADJ1           0x124
#define PMU_RTC_ADJ2           0x125

struct hi6620_local {
	struct rtc_device *rtc;
	void __iomem      *base;
};

extern unsigned int get_pd_charge_flag(void);
extern struct rtc_wkalrm poweroff_rtc_alarm;

/* Read external rtc time*/
static int pmu_get_time(unsigned long *time)
{
	*time = (pmussi_reg_read(RTCCR_A3) << 24) | (pmussi_reg_read(RTCCR_A2) << 16) |
			(pmussi_reg_read(RTCCR_A1) << 8) | pmussi_reg_read(RTCCR_A0);

	return 0;
}

/* Set external rtc time*/
static int pmu_set_time(unsigned long time)
{
	unsigned char temp_val;

	/*write operation must start form low bit*/
	temp_val = time & 0xFF;
	pmussi_reg_write(RTCLR_A0, temp_val);
	temp_val =  (time >> 8) & 0xFF;
	pmussi_reg_write(RTCLR_A1, temp_val);
	temp_val =  (time >> 16) & 0xFF;
	pmussi_reg_write(RTCLR_A2, temp_val);
	temp_val =  (time >> 24) & 0xFF;
	pmussi_reg_write(RTCLR_A3, temp_val);

	return 0;
}

static int pmu_get_alarm_time(void)
{
	return (pmussi_reg_read(RTCMR_A_A3) << 24) | \
                (pmussi_reg_read(RTCMR_A_A2) << 16) | \
                (pmussi_reg_read(RTCMR_A_A1) << 8) | \
                pmussi_reg_read(RTCMR_A_A0);
}

/* Read internal rtc alarm time*/
int pmu_set_alarm_time(unsigned long time)
{
	unsigned char temp_val;
        int a, b;
	/*write operation must start form low bit*/
	temp_val = time & 0xFF;
	pmussi_reg_write(RTCMR_A_A0, temp_val);
	temp_val =  (time >> 8) & 0xFF;
	pmussi_reg_write(RTCMR_A_A1, temp_val);
	temp_val =  (time >> 16) & 0xFF;
	pmussi_reg_write(RTCMR_A_A2, temp_val);
	temp_val =  (time >> 24) & 0xFF;
	pmussi_reg_write(RTCMR_A_A3, temp_val);

	pmussi_reg_write(RTC_IRQ3_IMSC, ~RTC_ALARM_A);

	return 0;
}

/* Read external rtc alarm time*/
static void pmu_read_alarm(struct rtc_time *tm)
{
	unsigned long time;

	time = pmu_get_alarm_time();

	rtc_time_to_tm(time, tm);

	return;
}
static int pmu_write_alarm(struct rtc_time *tm)
{
	unsigned long time;
	int err;

	err = rtc_valid_tm(tm);
	if (err != 0) {
		return err;
	}
	rtc_tm_to_time(tm, &time);
	pmu_set_alarm_time(time);

        return 0;
}

/* Read internal rtc time*/
static int hi6620_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	unsigned long time;

        /* use pmu rtc time */
	pmu_get_time(&time);
	rtc_time_to_tm(time, tm);

	return 0;
}

/* Set internal rtc time*/
static int hi6620_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	int err;
	unsigned long time;
	struct hi6620_local *ldata = dev_get_drvdata(dev);

	err = rtc_valid_tm(tm);
	if (err != 0) {
		return err;
	}

	rtc_tm_to_time(tm, &time);

	writel(time, ldata->base + RTCLR);
    /* set pmu rtc */
	pmu_set_time(time);

	return 0;
}

static int hi6620_rtc_alarm_irq_enable(struct device *dev,
	unsigned int enabled)
{

	struct hi6620_local *ldata = dev_get_drvdata(dev);
	unsigned long imsc;

	/* Clear any pending alarm interrupts. */
	writel(RTC_ALARM_INT, ldata->base + RTCICR);

	imsc = readl(ldata->base + RTCIMSC);

	if (enabled == 1)
		writel(imsc | RTC_ALARM_INT, ldata->base + RTCIMSC);
	else
		writel(imsc & ~RTC_ALARM_INT, ldata->base + RTCIMSC);

	return 0;
}

static int oem_rtc_reboot_thread(void *u)
{
	printk("Entering Rebooting Causeed by Alarm...\n");
	emergency_remount();
	sys_sync();
	kernel_restart("oem_rtc");

	/* should not be here */
	panic("oem_rtc");
	return 0;
}

void oem_rtc_reboot(unsigned long t)
{
	kernel_thread(oem_rtc_reboot_thread, NULL, CLONE_FS | CLONE_FILES);
}

static DECLARE_TASKLET(oem_rtc_reboot_tasklet, oem_rtc_reboot, 0);

static irqreturn_t pmu_rtc_interrupt(int irq, void *dev_id)
{
	unsigned char irq_bit;
        irq_bit = pmussi_reg_read(PMU_REG_IRQ3);
        if (0 == (irq_bit & RTC_ALARM_A)) {
                return IRQ_NONE;
        }
        /* clear irq status */
        pmussi_reg_write(PMU_REG_IRQ3, irq_bit | RTC_ALARM_A);

	if(unlikely(get_pd_charge_flag())) {
		tasklet_schedule(&oem_rtc_reboot_tasklet);
        }
	return IRQ_HANDLED;
}

static irqreturn_t hi6620_rtc_interrupt(int irq, void *dev_id)
{
	struct hi6620_local *ldata = dev_id;
	unsigned long rtcmis;
	unsigned long events = 0;
	rtcmis = readl(ldata->base + RTCMIS); /*read interrupt*/
	if (rtcmis) {
		writel(rtcmis, ldata->base + RTCICR); /*clear interrupt*/

		if (rtcmis & RTC_ALARM_INT)
			events |= (RTC_AF | RTC_IRQF);
		rtc_update_irq(ldata->rtc, 1, events);

		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}

/* Read internal rtc alarm time*/
static int hi6620_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct hi6620_local *ldata = dev_get_drvdata(dev);
	unsigned long time;

	time = readl(ldata->base + RTCMR);

	rtc_time_to_tm(time, &alarm->time);

	alarm->pending = readl(ldata->base + RTCRIS) & RTC_ALARM_INT;
	alarm->enabled = readl(ldata->base + RTCIMSC) & RTC_ALARM_INT;

	return 0;
}

/* Set internal rtc alarm time*/
static int hi6620_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct hi6620_local *ldata = dev_get_drvdata(dev);
	unsigned long time;
	int ret;

	ret = rtc_valid_tm(&alarm->time);

	if (ret == 0) {
		ret = rtc_tm_to_time(&alarm->time, &time);
		if (ret == 0) {
			writel(time, ldata->base + RTCMR);
			hi6620_rtc_alarm_irq_enable(dev, alarm->enabled);
		}
	}
	return ret;
}

static int hi6620_rtc_proc(struct device *dev, struct seq_file *seq)
{
	char tmp;

	tmp = pmussi_reg_read(PMU_RTC_VERSION);
	seq_printf(seq, "@@ PMU VERSION:  0x%x\n", tmp);

	tmp = pmussi_reg_read(PMU_RTC_ADJ1);
	seq_printf(seq, "@@ PMU RTC_ADJ1: 0x%x\n", tmp);

	tmp = pmussi_reg_read(PMU_RTC_ADJ2);
	seq_printf(seq, "@@ PMU RTC_ADJ2: 0x%x\n", tmp);

	return 0;
}

static struct rtc_class_ops hi6620_rtc_ops = {
	.read_time = hi6620_rtc_read_time,
	.set_time = hi6620_rtc_set_time,
	.read_alarm = hi6620_rtc_read_alarm,
	.set_alarm = hi6620_rtc_set_alarm,
	.alarm_irq_enable = hi6620_rtc_alarm_irq_enable,
	.proc = hi6620_rtc_proc,
};

static void hi6620_shutdown(struct platform_device *pdev)
{
	if(unlikely(get_pd_charge_flag()))
		return;

	if (poweroff_rtc_alarm.enabled) {
		pmu_write_alarm(&poweroff_rtc_alarm.time);
	} else {
		pmu_set_alarm_time(0);
	}

}

static int hi6620_probe(struct platform_device *pdev)
{
	int ret;
	struct hi6620_local *ldata;
	unsigned long time;
	unsigned int base = IO_ADDRESS(REG_BASE_SC_ON);
	struct rtc_time alarm_tm;
	struct rtc_time time_tm;
	struct rtc_time ap_time_tm;
	unsigned long ap_time;
	unsigned long alarm_time = 0;

	ldata = kzalloc(sizeof(struct hi6620_local), GFP_KERNEL);
	if (!ldata) {
		ret = -ENOMEM;
		goto out;
	}
	platform_set_drvdata(pdev, ldata);

	ldata->base = ioremap(pdev->resource->start, resource_size(pdev->resource));
	ldata->rtc = rtc_device_register("hi6620", &pdev->dev, &hi6620_rtc_ops,
					THIS_MODULE);
	if (IS_ERR(ldata->rtc)) {
		ret = PTR_ERR(ldata->rtc);
		goto out_no_rtc;
	}

	if (request_irq(IRQ_RTC, hi6620_rtc_interrupt,
			IRQF_DISABLED, "rtc-hi6620", ldata)) {
		ret = -EIO;
		goto out_no_irq;
	}

	if (request_irq(ALARM_ON_A_TYPE, pmu_rtc_interrupt,
			IRQF_DISABLED, "rtc-pmu", ldata)) {
		ret = -EIO;
		free_irq(IRQ_RTC, ldata->rtc);
		goto out_no_irq;
	}

	/* get PMU RTC time */
	pmu_get_time(&time);
	rtc_time_to_tm(time, &time_tm);
	printk(KERN_DEBUG "RTC time %d-%d-%d %d:%d:%d\n",
	       time_tm.tm_year, time_tm.tm_mon,
	       time_tm.tm_mday, time_tm.tm_hour,
	       time_tm.tm_min, time_tm.tm_sec);

	/* get PMU RTC alarm */
	pmu_read_alarm(&alarm_tm);
	printk(KERN_DEBUG "Last alarm %d-%d-%d %d:%d:%d\n",
	       alarm_tm.tm_year, alarm_tm.tm_mon,
	       alarm_tm.tm_mday, alarm_tm.tm_hour,
	       alarm_tm.tm_min, alarm_tm.tm_sec);

        /* 打开1Hz的时钟门控，即将0bit配1，reg属性:写0无效 */
	writel(1, SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(base));

	/* sync pmu rtc to ap rtc */
	writel(1, ldata->base + RTCCR);
	writel(time, ldata->base + RTCLR);

	/* get ap rtc initial value */
	ap_time = readl(ldata->base + RTCDR);
	rtc_time_to_tm(ap_time, &ap_time_tm);
	printk(KERN_DEBUG "Init AP RTC %d-%d-%d %d:%d:%d\n",
			ap_time_tm.tm_year, ap_time_tm.tm_mon,
			ap_time_tm.tm_mday, ap_time_tm.tm_hour,
			ap_time_tm.tm_min, ap_time_tm.tm_sec);

	rtc_tm_to_time(&alarm_tm, &alarm_time);
	if (unlikely(get_pd_charge_flag() && (alarm_time > time))) {
		poweroff_rtc_alarm.enabled = 1;
		memcpy(&poweroff_rtc_alarm.time, &alarm_tm, sizeof(struct rtc_time));
		printk(KERN_DEBUG "set to poweroff alarm %d-%d-%d %d:%d:%d\n",
			poweroff_rtc_alarm.time.tm_year,
			poweroff_rtc_alarm.time.tm_mon,
			poweroff_rtc_alarm.time.tm_mday,
			poweroff_rtc_alarm.time.tm_hour,
			poweroff_rtc_alarm.time.tm_min,
			poweroff_rtc_alarm.time.tm_sec);
	}

	return 0;

out_no_irq:
	rtc_device_unregister(ldata->rtc);

out_no_rtc:
	kfree(ldata);
	platform_set_drvdata(pdev, NULL);
out:

	return ret;
}

static int hi6620_remove(struct platform_device *pdev)
{
	struct hi6620_local *ldata = dev_get_drvdata(&pdev->dev);

	free_irq(ALARM_ON_A_TYPE, ldata->rtc);
	free_irq(IRQ_RTC, ldata->rtc);

	platform_set_drvdata(pdev, NULL);
	rtc_device_unregister(ldata->rtc);

	iounmap(ldata->base);
	kfree(ldata);

	return 0;
}


static struct platform_driver hi6620_rtc_driver = {
	.probe  = hi6620_probe,
	.remove = hi6620_remove,
	.shutdown  = hi6620_shutdown,
	.driver	= {
		.name =	"rtc-hi6620",
		.owner = THIS_MODULE,
	},
};

static int __init hi6620_init(void)
{
	return platform_driver_register(&hi6620_rtc_driver);
}

static void __exit hi6620_exit(void)
{
	platform_driver_unregister(&hi6620_rtc_driver);
}

module_init(hi6620_init);
module_exit(hi6620_exit);

MODULE_AUTHOR("Hisilicon Co. Ltd");
MODULE_DESCRIPTION("hi6620 RTC Driver");
MODULE_LICENSE("GPL");


#include <linux/platform_device.h>
#include <mach/lm.h>
#include <mach/platform.h>
#include <mach/early-debug.h>
#include <mach/irqs.h>
#include <mach/irqs.h>
#include <mach/pmussi_drv.h>
#include <linux/cdev.h>
#include <linux/irq.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/mux.h>
#include <linux/usb/balong/hisi_susb.h>
#include <bsp_ao_sctrl.h>
#include <bsp_sctrl.h>
#include <hsad/config_mgr.h>
#include <mach/lm.h>
#include <linux/switch_usb.h>

#if (defined _DRV_LLT_)  || (defined _DRV_LLT_UT_) || (defined MED_UT) || (defined PC_UT_TEST_ON)
#define PM_QOS_CPU_INT_LATENCY    23
#endif

#ifdef CONFIG_SWITCH_USB_CLS
static struct usb_switch_platform_data platformdata = {
    .irq_flags = 0,
};
static struct platform_device usb_switch_device = {
	.name   = "usbsw",
	.dev    = {
		.init_name = "usbsw",
		.platform_data = &platformdata,
	},
};

static struct platform_device *plat_usb_dev[] __initdata = {
    &usb_switch_device,
};
#endif

#ifdef CONFIG_SWITCH_FSA9685
extern int fsa9685_manual_detach(void);
#endif

static char* usb_ct_str[] = {
    "CHARGER_TYPE_USB",
    "CHARGER_TYPE_BC_USB",
    "CHARGER_TYPE_NON_STANDARD",
    "CHARGER_TYPE_STANDARD",
    "CHARGER_REMOVED",
    "USB_EVENT_OTG_ID",
    "unknown",
};
#define HIUSB_MAX_STATUS 3
static char* usb_status[] = {
    "HIUSB_OFF",
    "HIUSB_DEVICE",
    "HIUSB_HOST",
    "HIUSB_SUSPEND"
};

/* --------------------- sysfs file --------------------------------------*/
/**
 * Show the switch gpio status.
 */
STATIC struct hiusb_info *g_hiusb_info;
irqreturn_t hiusb_vbus_intr(int irq, void *dev);
int use_switch_driver=0;
int id_no_bypass=0;

void hiusb_system_info(void)
{
    uint32_t reg;

    reg = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    printk("AOSCTRL_SC_ALWAYSON_SYS_CTRL9:0x%8.8x\n",reg);
    reg = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL8);
    printk("AOSCTRL_SC_ALWAYSON_SYS_CTRL8:0x%8.8x\n",reg);
    reg = readl(SCTRL_SC_PERIPH_CTRL8);
    printk("SCTRL_SC_PERIPH_CTRL8:0x%8.8x\n",reg);
    reg = readl(AOSCTRL_SC_PW_ISO_STAT0);
    printk("AOSCTRL_SC_PW_ISO_STAT0:0x%8.8x\n",reg & (0x1<<20));
    reg = readl(AOSCTRL_SC_PW_RST_STAT0);
    printk("AOSCTRL_SC_PW_RST_STAT0:0x%8.8x\n",reg & (0x1<<20));
    reg = readl(AOSCTRL_SC_PERIPH_RSTSTAT4);
    printk("AOSCTRL_SC_PERIPH_RSTSTAT4:0x%8.8x\n",reg & (0xf<<16));
    reg = readl(SCTRL_SC_PERIPH_RSTSTAT1);
    printk("SCTRL_SC_PERIPH_RSTSTAT1:0x%8.8x\n",reg & (0x3<<26));
    reg = readl(AOSCTRL_SC_PW_CLK_STAT0);
    printk("AOSCTRL_SC_PW_CLK_STAT0:0x%8.8x\n",reg & (0x1<<20));
    reg = readl(SCTRL_SC_PERIPH_CLKSTAT2);
    printk("SCTRL_SC_PERIPH_CLKSTAT2:0x%8.8x\n",reg & (0x3<<19));
    reg = readl(AOSCTRL_SC_PERIPH_CLKSTAT6);
    printk("AOSCTRL_SC_PERIPH_CLKSTAT6:0x%8.8x\n",reg & (0x7<<1));
}

STATIC ssize_t swstate_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    uint32_t val = simple_strtoul(buf, NULL, 16);

    if (val == 0) {
        if (g_hiusb_info->cdma_usb_enable == -1) {
            pr_err("%s: no cdma_usb_enable gpio!\n", __func__);
        } else {
            gpio_direction_output(g_hiusb_info->cdma_usb_enable, 0);
        }
        switch_off();
        msleep(1000);
        switch_reset();
    } else if(val == 1) {
        if (g_hiusb_info->cdma_usb_enable == -1) {
            pr_err("%s: no cdma_usb_enable gpio!\n", __func__);
        } else {
            gpio_direction_output(g_hiusb_info->cdma_usb_enable, 1);
        }
        switch_off();
        msleep(1000);
        switch_cdma();
    } else {
        if (g_hiusb_info->cdma_usb_enable == -1) {
            pr_err("%s: no cdma_usb_enable gpio!\n", __func__);
        } else {
            gpio_direction_output(g_hiusb_info->cdma_usb_enable, 0);
        }
        switch_off();
    }

    return count;
}
STATIC ssize_t swstate_show(struct device *_dev,
              struct device_attribute *attr, char *buf)
{
    struct hiusb_info *hiusb_info = g_hiusb_info;
    int cdma_usb_enable=0;

    if (g_hiusb_info->cdma_usb_enable != -1)
        cdma_usb_enable = gpio_get_value_cansleep(g_hiusb_info->cdma_usb_enable);

    return sprintf(buf, "%d", cdma_usb_enable);
}
DEVICE_ATTR(swstate, S_IRUGO|S_IWUSR, swstate_show, swstate_store);

/**
 * Show the charger status.
 */
STATIC ssize_t charger_show(struct device *_dev,
              struct device_attribute *attr, char *buf)
{
    struct lm_device *lm_dev = container_of(_dev, struct lm_device, dev);
    struct hiusb_info *hiusb_info;
    int ret;
    char charger_type[10];

    hiusb_info = lm_dev->hiusb_info;
    ret = get_charger_name();
    switch (ret) {
        case CHARGER_TYPE_USB:
            strcpy(charger_type, "SDP");
            break;
        case CHARGER_TYPE_BC_USB:
            strcpy(charger_type, "CDP");
            break;
        case CHARGER_TYPE_NON_STANDARD:
            strcpy(charger_type, "SDP");
            break;
        case CHARGER_TYPE_STANDARD:
            strcpy(charger_type, "DCP");
            break;
        case CHARGER_REMOVED:
            strcpy(charger_type, "REMOVED");
            break;
        default:
            return sprintf(buf, "usb not init\n");
    }

    return sprintf(buf, "charger_type:%d(%s)\n", ret, charger_type);
}
DEVICE_ATTR(charger, S_IRUGO, charger_show, NULL);

/**
 * Show the hiusb_status.
 */
STATIC ssize_t hiusb_status_show(struct device *_dev,
              struct device_attribute *attr, char *buf)
{
    struct lm_device *lm_dev = container_of(_dev, struct lm_device, dev);
    struct hiusb_info *hiusb_info;
    int ret;
    char hiusb_status[20];

    hiusb_info = lm_dev->hiusb_info;

    ret = down_interruptible(&hiusb_info->hiusb_info_sema);
    if (ret) {
        pr_err("%s: down hiusb_info_sema failed!\n", __func__);
        return ret;
    }
    ret = hiusb_info->hiusb_status;
    up(&hiusb_info->hiusb_info_sema);

    switch (ret) {
        case HIUSB_OFF:
            strcpy(hiusb_status, "HIUSB_OFF");
            break;
        case HIUSB_DEVICE:
            strcpy(hiusb_status, "HIUSB_DEVICE");
            break;
        case HIUSB_HOST:
            strcpy(hiusb_status, "HIUSB_HOST");
            break;
        case HIUSB_SUSPEND:
            strcpy(hiusb_status, "HIUSB_SUSPEND");
            break;
        default:
            strcpy(hiusb_status, "UNKNOWN");
            break;
    }

    return sprintf(buf, "hiusb_status:%d(%s)\n", hiusb_info->hiusb_status, hiusb_status);
}
DEVICE_ATTR(hiusb_status, S_IRUGO, hiusb_status_show, NULL);

/**
 * Store the test_vbus_store attribure.
 */
STATIC ssize_t test_vbus_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    struct lm_device *lm_dev = container_of(_dev, struct lm_device, dev);
    struct hiusb_info *hiusb_info = lm_dev->hiusb_info;
    uint32_t val = simple_strtoul(buf, NULL, 16);

    if (hiusb_info->insert_irq == 0 || hiusb_info->draw_irq == 0) {
        dev_info(&lm_dev->dev, "No insert/draw irq.\n");
        return 0;
    }

    if (val == 0) {
        hiusb_vbus_intr(hiusb_info->draw_irq, lm_dev);
    } else {
        hiusb_vbus_intr(hiusb_info->insert_irq, lm_dev);
    }

    return count;
}
DEVICE_ATTR(test_vbus, S_IWUSR, NULL, test_vbus_store);

/**
 * Store the test_id_store attribure.
 */
STATIC ssize_t test_id_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    struct lm_device *lm_dev = container_of(_dev, struct lm_device, dev);
    struct hiusb_info *hiusb_info = lm_dev->hiusb_info;
    uint32_t val = simple_strtoul(buf, NULL, 16);

    if (hiusb_info->insert_irq == 0 || hiusb_info->draw_irq == 0) {
        dev_info(&lm_dev->dev, "No insert/draw irq.\n");
        return 0;
    }

    if (val == 0) {
        hiusb_id_changed(ID_RISE_EVENT);
        msleep(3000);
        hiusb_id_changed(ID_FALL_EVENT);
    } else {
        hiusb_vbus_intr(hiusb_info->draw_irq, lm_dev);
        msleep(3000);
        hiusb_vbus_intr(hiusb_info->insert_irq, lm_dev);
    }

    return count;
}
DEVICE_ATTR(test_id, S_IWUSR, NULL, test_id_store);

/**
 * Store the test_hibernation_store attribure.
 */
STATIC ssize_t test_hibernation_store(struct device *_dev,
                 struct device_attribute *attr,
                 const char *buf, size_t count)
{
    struct lm_device *lm_dev = container_of(_dev, struct lm_device, dev);
    struct hiusb_info *hiusb_info = lm_dev->hiusb_info;
    uint32_t val = simple_strtoul(buf, NULL, 16);

    if (hiusb_info->insert_irq == 0 || hiusb_info->draw_irq == 0) {
        dev_info(&lm_dev->dev, "No insert/draw irq.\n");
        return 0;
    }

    dwc_otg_set_hibernation(lm_dev, val);

    return count;
}
DEVICE_ATTR(test_hibernation, S_IWUSR, NULL, test_hibernation_store);

void hiusb_attr_create(struct lm_device *lm_dev)
{
    int error;
    struct class *switch_usb_class;
    struct device *switch_usb_dev;

    if(!use_switch_driver){
        switch_usb_class = class_create(THIS_MODULE, "usbswitch");
        switch_usb_dev = device_create(switch_usb_class, NULL, MKDEV(0,0), NULL, "usbsw");
        error = device_create_file(switch_usb_dev, &dev_attr_swstate);
    }

    error = device_create_file(&lm_dev->dev, &dev_attr_charger);
    error = device_create_file(&lm_dev->dev, &dev_attr_hiusb_status);
    error = device_create_file(&lm_dev->dev, &dev_attr_test_vbus);
    error = device_create_file(&lm_dev->dev, &dev_attr_test_id);
    error = device_create_file(&lm_dev->dev, &dev_attr_test_hibernation);
}

void hiusb_attr_remove(struct lm_device *lm_dev)
{
    device_remove_file(&lm_dev->dev, &dev_attr_charger);
    device_remove_file(&lm_dev->dev, &dev_attr_hiusb_status);
    device_remove_file(&lm_dev->dev, &dev_attr_test_vbus);
    device_remove_file(&lm_dev->dev, &dev_attr_test_id);
    device_remove_file(&lm_dev->dev, &dev_attr_test_hibernation);
}

/* ---------------------- usb charger ------------------------------------*/
/* pmu read */
STATIC unsigned char pmu_version(void)
{
    return pmussi_reg_read(0x115);
}

STATIC unsigned char vbus_status(void)
{
    unsigned char vbus_status;
    vbus_status = pmussi_reg_read(0x002);
    vbus_status &= (1<<5);
    return vbus_status;
}

int get_charger_name(void)
{
    int ret = -1;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return ret;
    }

    ret = down_interruptible(&g_hiusb_info->hiusb_info_sema);
    if (ret) {
        pr_err("%s: down hiusb_info_sema failed!\n", __func__);
        return ret;
    }

    ret = g_hiusb_info->charger_type;

    up(&g_hiusb_info->hiusb_info_sema);

    return ret;
}
EXPORT_SYMBOL_GPL(get_charger_name);


int hiusb_charger_registe_notifier(struct notifier_block *nb)
{
    int ret = -1;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return ret;
    }

    ret = atomic_notifier_chain_register(
            &g_hiusb_info->charger_type_notifier_head, nb);

    return ret;

}
EXPORT_SYMBOL_GPL(hiusb_charger_registe_notifier);


int hiusb_charger_unregiste_notifier(struct notifier_block *nb)
{
    int ret = -1;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return ret;
    }

    ret = atomic_notifier_chain_unregister(
            &g_hiusb_info->charger_type_notifier_head, nb);

    return ret;
}
EXPORT_SYMBOL_GPL(hiusb_charger_unregiste_notifier);

STATIC void notify_charger_type(void)
{
    atomic_notifier_call_chain(&g_hiusb_info->charger_type_notifier_head,
        g_hiusb_info->charger_type, g_hiusb_info);
    pr_info("%s: Notify charger type: %s\n", __func__, g_hiusb_info->charger_type < CHARGER_TYPE_MAX ? usb_ct_str[g_hiusb_info->charger_type]:"error type");
    return;
}

STATIC int detect_charger_type(void)
{
    int type;

    /* todo: wait huangyonggang */
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_UNION ao_sctrl_ctrl9;
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_UNION ao_sctrl_stat2;

    ao_sctrl_ctrl9.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_bc_mode = 1;
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_dcdenb = 1;
    writel(ao_sctrl_ctrl9.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL9);

    msleep(900);

    ao_sctrl_stat2.value = readl(AOSCTRL_SC_ALWAYSON_SYS_STAT2);
    if (ao_sctrl_stat2.reg.datcondet_sts == 0) {
        type = CHARGER_TYPE_USB;
        goto out;
    }
    msleep(20);
    ao_sctrl_ctrl9.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_chrgsel = 0;
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_vdatsrcend = 1;
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_vdatdetenb = 1;
    writel(ao_sctrl_ctrl9.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    msleep(20);
    ao_sctrl_stat2.value = readl(AOSCTRL_SC_ALWAYSON_SYS_STAT2);
    if (ao_sctrl_stat2.reg.chgdet_sts == 0) {
        type = CHARGER_TYPE_USB;  /*SDP*/
        goto out;
    } else {
        type = CHARGER_TYPE_STANDARD;     /*CDP OR DCP*/
    }

    ao_sctrl_ctrl9.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_chrgsel = 1;
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_vdatsrcend = 1;
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_vdatdetenb = 1;
    writel(ao_sctrl_ctrl9.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    msleep(20);
    ao_sctrl_stat2.value = readl(AOSCTRL_SC_ALWAYSON_SYS_STAT2);
    if (ao_sctrl_stat2.reg.chgdet_sts == 0) {
        type = CHARGER_TYPE_BC_USB;  /*CDP*/
    } else {
        type = CHARGER_TYPE_STANDARD;     /*DCP*/
    }

out:
    ao_sctrl_ctrl9.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_bc_mode = 0;
    writel(ao_sctrl_ctrl9.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL9);

    return type;
}

/* ---------------------- usb switch ------------------------------------*/
STATIC int switch_init(struct lm_device *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;
    int ret;

    lm_dev = dev;
    hiusb_info = lm_dev->hiusb_info;


    dev_info(&lm_dev->dev, "%s +.\n", __func__);

    ret = get_hw_config_int("usb/switch_pin1", &hiusb_info->switch_pin1, NULL);
    if (ret && hiusb_info->switch_pin1  != -1) {
        ret = gpio_request(hiusb_info->switch_pin1, "switch_pin1");
        if (ret < 0) {
            dev_err(&lm_dev->dev, "%s request switch_pin1 failed.\n", __func__);
            goto request_pin1_fail;
        }
        gpio_direction_output(hiusb_info->switch_pin1, 0);
    }

    ret = get_hw_config_int("usb/switch_pin2", &hiusb_info->switch_pin2, NULL);
    if (ret && hiusb_info->switch_pin2  != -1) {
        ret = gpio_request(hiusb_info->switch_pin2, "switch_pin2");
        if (ret < 0) {
            dev_err(&lm_dev->dev, "%s request switch_pin2 failed.\n", __func__);
            goto request_pin2_fail;
        }
        gpio_direction_output(hiusb_info->switch_pin2, 0);
    }

    ret = get_hw_config_int("usb/switch_id_pin", &hiusb_info->switch_id_pin, NULL);
    if (ret && hiusb_info->switch_id_pin  != -1) {
        ret = gpio_request(hiusb_info->switch_id_pin, "switch_id_pin");
        if (ret < 0) {
            dev_err(&lm_dev->dev, "%s request switch_id_pin failed.\n", __func__);
            goto request_id_pin_fail;
        }
        gpio_direction_output(hiusb_info->switch_id_pin, 1);
    }

    ret = get_hw_config_int("usb/cdma_usb_enable", &hiusb_info->cdma_usb_enable, NULL);
    if (ret && hiusb_info->cdma_usb_enable  != -1) {
        ret = gpio_request(hiusb_info->cdma_usb_enable, "cdma_usb_enable");
        if (ret < 0) {
            dev_err(&lm_dev->dev, "%s request cdma_usb_enable failed.\n", __func__);
            goto request_id_pin_fail;
        }
        gpio_direction_output(hiusb_info->cdma_usb_enable, 0);
    }

    pr_info("%s:switch_pin1:%d, switch_pin2:%d, switch_id_pin:%d, cdma_usb_enable:%d\n", __func__, hiusb_info->switch_pin1, hiusb_info->switch_pin2, hiusb_info->switch_id_pin, hiusb_info->cdma_usb_enable);

    return 0;

request_id_pin_fail:
    gpio_free(hiusb_info->switch_pin2);
request_pin2_fail:
    gpio_free(hiusb_info->switch_pin1);
request_pin1_fail:
    return ret;
}

int switch_reset(void)
{

    unsigned long flags;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    /*todo : D+/D- -- usb | ID -- MHL*/
    if(!use_switch_driver){
        gpio_direction_output(g_hiusb_info->switch_pin1, 0);
        gpio_direction_output(g_hiusb_info->switch_pin2, 0);
        gpio_direction_output(g_hiusb_info->switch_id_pin, 1);
    }else{
        //add switch default code here
#ifdef CONFIG_SWITCH_FSA9685
    if(!id_no_bypass)
        fsa9685_manual_detach();
#endif
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int __switch_usb_id(void)
{

    unsigned long flags;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    if(!use_switch_driver){
       gpio_direction_output(g_hiusb_info->switch_id_pin, 0);
    }else{
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int __switch_usb(void)
{

    unsigned long flags;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    if(!use_switch_driver){
        gpio_direction_output(g_hiusb_info->switch_pin1, 0);
        gpio_direction_output(g_hiusb_info->switch_pin2, 0);
        gpio_direction_output(g_hiusb_info->switch_id_pin, 0);
    }else{
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int switch_usb(void)
{
    int ret = -1;
    if(!use_switch_driver){
        ret = __switch_usb();

        hiusb_id_changed(ID_FALL_EVENT);
        return ret;
    }else{
        hiusb_id_changed(ID_FALL_EVENT);
        //just return
        return 0;
    }
}

int __switch_mhl_id(void)
{

    unsigned long flags;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    if(!use_switch_driver){
        gpio_direction_output(g_hiusb_info->switch_id_pin, 1);
    }else{
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int switch_mhl(void)
{

    unsigned long flags;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    if(!use_switch_driver){
        spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
        gpio_direction_output(g_hiusb_info->switch_pin1, 0);
        gpio_direction_output(g_hiusb_info->switch_pin2, 1);
        gpio_direction_output(g_hiusb_info->switch_id_pin, 1);
        spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);
    }else{
         //wait 30ms for fsa9685 switch
         msleep(30);
    }

    return 0;
}

int switch_cdma(void)
{

    unsigned long flags;
    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    if(!use_switch_driver){
        gpio_direction_output(g_hiusb_info->switch_pin1, 1);
        gpio_direction_output(g_hiusb_info->switch_pin2, 0);
        gpio_direction_output(g_hiusb_info->switch_id_pin, 1);
    }else{
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int switch_off(void)
{

    unsigned long flags;
    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    pr_info("%s", __func__);
    /*todo : D+/D- -- usb | ID -- MHL*/
    spin_lock_irqsave(&g_hiusb_info->switch_lock, flags);
    if(!use_switch_driver){
        gpio_direction_output(g_hiusb_info->switch_pin1, 1);
        gpio_direction_output(g_hiusb_info->switch_pin2, 1);
        gpio_direction_output(g_hiusb_info->switch_id_pin, 0);
    }else{
    }
    spin_unlock_irqrestore(&g_hiusb_info->switch_lock, flags);

    return 0;
}

int id_state(void)
{
    int id = 0;
    if(!use_switch_driver){
        if (g_hiusb_info->switch_id_pin!= -1) {
            id = gpio_get_value_cansleep(g_hiusb_info->switch_id_pin);
        }
    }else{
        id = 1;
    }
    return id;
}

/*sel_state(D+/D-):
 *0 == usb
 *1 == mhl
 *2 == cdma
 *other == off
 */
int sel_state(void)
{
    int sel_state = 0;
    int sel0 = 0;
    int sel1 = 0;

    if (g_hiusb_info->switch_pin1!= -1) {
        sel0 = gpio_get_value_cansleep(g_hiusb_info->switch_pin1);
    }
    if (g_hiusb_info->switch_pin2!= -1) {
        sel1 = gpio_get_value_cansleep(g_hiusb_info->switch_pin2);
    }

    if (sel0 == 0 && sel1 == 0) {
        sel_state = 0;
    } else if (sel0 == 0 && sel1 == 1) {
        sel_state = 1;
    } else if (sel0 == 1 && sel1 == 0) {
        sel_state = 2;
    } else {
        sel_state = 3;
    }

    return sel_state;
}

/* ---------------------- usb common -------------------------------------*/
#define HI6620_USB_NAME    "hisik3-usb-otg"

/* usb rst registers */
struct hisi_rst hiusb_rst[] = {
    {AOSCTRL_SC_PW_CLKDIS0, (0x1<<20), AOSCTRL_SC_PW_CLK_STAT0, 0, 10},  /*pw clk*/
    {AOSCTRL_SC_PERIPH_RSTEN4, (0xf<<16), AOSCTRL_SC_PERIPH_RSTSTAT4, 1, 10},/* OTG AND PHY in alwayson sctrl */
    {SCTRL_SC_PERIPH_RSTEN1, (0x3<<26), SCTRL_SC_PERIPH_RSTSTAT1, 1, 10}, /* otg in sctrl */
    {AOSCTRL_SC_PW_RSTEN0, (0x1<<20), AOSCTRL_SC_PW_RST_STAT0, 1, 10},  /*pw rst*/
    {AOSCTRL_SC_PW_ISOEN0, (0x1<<20), AOSCTRL_SC_PW_ISO_STAT0, 1, 10},  /*pw iso*/
    {0,0,0},
};

/* usb nrst registers */
struct hisi_rst hiusb_nrst[] = {
    {AOSCTRL_SC_PW_ISODIS0, (0x1<<20), AOSCTRL_SC_PW_ISO_STAT0, 0, 10},    /*pw iso*/
    {AOSCTRL_SC_PW_RSTDIS0, (0x1<<20), AOSCTRL_SC_PW_RST_STAT0, 0, 10},    /*pw rst*/
    {AOSCTRL_SC_PERIPH_RSTDIS4, (0xf<<16), AOSCTRL_SC_PERIPH_RSTSTAT4, 0, 10},/* OTG AND PHY in alwayson sctrl */
    {SCTRL_SC_PERIPH_RSTDIS1, (0x3<<26), SCTRL_SC_PERIPH_RSTSTAT1, 0, 10},   /* otg in sctrl */
    {AOSCTRL_SC_PW_CLKEN0, (0x1<<20), AOSCTRL_SC_PW_CLK_STAT0, 1, 10},    /*pw clk*/
    {0,0,0},
};

void hiusb_hibernation_init(void)
{

    SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_UNION ao_sctrl_ctrl8;

    ao_sctrl_ctrl8.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL8);
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_16bc11_c = 0;
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_17bc11_b = 0;
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_20bc11_float = 0;
    writel(ao_sctrl_ctrl8.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL8);
    udelay(10);
    pr_info("%s .\n", __func__);

    return;
}

void hiusb_otg_and_phy_setup(int mode)
{
    int i;
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_UNION ao_sctrl_ctrl8;
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_UNION ao_sctrl_ctrl9;
    unsigned int val;
    int count;
    int ret;
    unsigned int eye_pattern_val = 0x709334ff;

    ret = blockmux_set(g_hiusb_info->usb_block, g_hiusb_info->usb_config, NORMAL);
    if (ret) {
        printk("%s:failed to blockmux_set\n", __func__);
    }

    /* nrst */
    for (i=0;hiusb_nrst[i].addr != 0; i++) {
        count = 0;
        do {
            writel(hiusb_nrst[i].value, hiusb_nrst[i].addr);
            udelay(hiusb_nrst[i].udelay);
            val = readl(hiusb_nrst[i].addr_stat) & (hiusb_nrst[i].value);
            if (hiusb_nrst[i].stat == 1 && val == hiusb_nrst[i].value) {
                break;
            } else if (hiusb_nrst[i].stat == 0 && val == 0) {
                break;
            } else {
                count ++;
            }
            if (count > 1000) {
                pr_err("%s set fail 0x%x:0x%x,0x%x,0x%x\n", __func__,
                    hiusb_nrst[i].addr,
                    hiusb_nrst[i].value,
                    val, hiusb_nrst[i].stat);
                break;
            }
        } while(1);
    }



    /* ctrl 9 */
    ao_sctrl_ctrl9.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL9);
    ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_bc_mode = 0;
    if ((g_hiusb_info->quirks & HIUSB_QUIRKS_PMUIRQ) == 0) {
        if (mode == 1) {
            ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_iddig = 1;
        } else {
            ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_iddig = 0;
        }
    } else {
            ao_sctrl_ctrl9.reg.alwayson_and_periph_sys_ctrl9_picophy_iddig = 1;
    }
    writel(ao_sctrl_ctrl9.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL9);

    /* ctrl 8 */
    ao_sctrl_ctrl8.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL8);

    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_6ddq = 0;
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_8pico_ogdisable = 0;
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_10pico_vbusvldextsel = 1;
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_11pico_vbusvldext = 1;
    writel(ao_sctrl_ctrl8.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL8);
    udelay(60);

    ret = get_hw_config_int("usb/eye_pattern", &eye_pattern_val, NULL);
    if (false == ret) {
        printk(KERN_WARNING "find eye_pattern_val failed !\n");
    }
    writel(eye_pattern_val, SCTRL_SC_PERIPH_CTRL8);

    // clk_enable();
    ret = clk_enable(g_hiusb_info->clk_usbotg_off);
    if (ret) {
        printk("%s:failed to enable clock1\n", __func__);
    }
    ret = clk_enable(g_hiusb_info->clk_picophy);
    if (ret) {
        printk("%s:failed to enable clock2\n", __func__);
    }

    hiusb_system_info();

    pr_info("%s .\n", __func__);

    return;
}

void hiusb_otg_and_phy_cleanup(void)
{
    int i;
    SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_UNION ao_sctrl_ctrl8;
    unsigned int val;
    int count;
    int ret;

    /* clk_disable(); */
    clk_disable(g_hiusb_info->clk_usbotg_off);
    clk_disable(g_hiusb_info->clk_picophy);

    /* ctrl 8 */
    ao_sctrl_ctrl8.value = readl(AOSCTRL_SC_ALWAYSON_SYS_CTRL8);
    ao_sctrl_ctrl8.reg.alwayson_and_periph_sys_ctrl8_6ddq = 1;
    writel(ao_sctrl_ctrl8.value , AOSCTRL_SC_ALWAYSON_SYS_CTRL8);

    /* rst */
    for (i=0;hiusb_rst[i].addr != 0; i++) {
        count = 0;
        do {
            writel(hiusb_rst[i].value, hiusb_rst[i].addr);
            udelay(hiusb_rst[i].udelay);
            val = readl(hiusb_rst[i].addr_stat) & (hiusb_rst[i].value);
            if (hiusb_rst[i].stat == 1 && val == hiusb_rst[i].value) {
                break;
            } else if (hiusb_rst[i].stat == 0 && val == 0) {
                break;
            } else {
                count ++;
            }
            if (count > 1000) {
                pr_err("%s set fail 0x%x:0x%x,0x%x,0x%x\n", __func__,
                    hiusb_rst[i].addr,
                    hiusb_rst[i].value,
                    val, hiusb_rst[i].stat);
                break;
            }
        } while(1);
    }

    ret = blockmux_set(g_hiusb_info->usb_block, g_hiusb_info->usb_config, NORMAL);
    if (ret) {
        printk("%s:failed to blockmux_set\n", __func__);
    }

    hiusb_system_info();
    pr_info("%s -.\n", __func__);
    return;
}

STATIC void hiusb_otg_intr_work(struct work_struct *work)
{
    struct hiusb_info *hiusb_info;
    struct lm_device *lm_dev;
    int intr_flag;
    unsigned long flags;
    int ret = 0;

    hiusb_info = container_of(to_delayed_work(work),
            struct hiusb_info, otg_intr_work);
    lm_dev = hiusb_info->lm_dev;
    dev_info(&lm_dev->dev, "%s +.\n", __func__);

    if (down_interruptible(&hiusb_info->hiusb_info_sema)) {
        dev_err(&lm_dev->dev, "%s down fail.\n", __func__);
        return;
    }

    spin_lock_irqsave(&hiusb_info->intr_flag_lock, flags);
    intr_flag = hiusb_info->intr_flag;
    spin_unlock_irqrestore(&hiusb_info->intr_flag_lock, flags);

    switch (intr_flag) {
        case CHARGER_INSERT:
            if ((0 != pmu_version()) && (vbus_status() == 0)) {
                dev_err(&lm_dev->dev, "%s charge INSERT no vbus error.\n", __func__);
                spin_lock(&hiusb_info->intr_flag_lock);
                hiusb_info->intr_flag = CHARGER_DRAW;
                spin_unlock(&hiusb_info->intr_flag_lock);
                schedule_delayed_work(&hiusb_info->otg_intr_work, 0);
                break;
            }
            if (hiusb_info->hiusb_status != HIUSB_OFF ) {
                dev_err(&lm_dev->dev, "%s charge INSERT wrong status error:(%d)%s.\n",
                    __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error");
                break;
            }

            if(hiusb_info->acpu_idle_add_request)
            {
                hiusb_info->acpu_idle_add_request(lm_dev);
            }

            wake_lock(&hiusb_info->dev_wakelock);
            /* usb sc init */
            hiusb_otg_and_phy_setup(0);
            /* detect charger */
            if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                hiusb_info->charger_type = detect_charger_type();
                notify_charger_type();
            }
            /* usb ip init */
            ret = dwc_dev_insert_init(lm_dev);
            if (0 == ret) {
                dev_dbg(&lm_dev->dev, "%s status:(%d)%s -> %s .\n", __func__,
                        hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? \
                        usb_status[hiusb_info->hiusb_status]:"error", usb_status[HIUSB_DEVICE]);
                hiusb_info->hiusb_status = HIUSB_DEVICE;
            } else {
                dev_dbg(&lm_dev->dev, "%s dwc_dev_insert_init error .\n", __func__);
                if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                    hiusb_info->charger_type = CHARGER_REMOVED;
                    notify_charger_type();
                }
                hiusb_otg_and_phy_cleanup();
                wake_unlock(&hiusb_info->dev_wakelock);
            }
            break;
        case CHARGER_DRAW:
            if ((0 != pmu_version()) && (vbus_status() != 0)) {
                dev_err(&lm_dev->dev, "%s charge DRAW have vbus error.\n", __func__);
                spin_lock(&hiusb_info->intr_flag_lock);
                hiusb_info->intr_flag = CHARGER_INSERT;
                spin_unlock(&hiusb_info->intr_flag_lock);
                schedule_delayed_work(&hiusb_info->otg_intr_work, 0);
                break;
            }
            if (hiusb_info->hiusb_status != HIUSB_DEVICE) {
                dev_err(&lm_dev->dev, "%s charge DRAW wrong status error:(%d)%s.\n",
                    __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error");
                break;
            }
            dwc_dev_draw_init(lm_dev);
            if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                hiusb_info->charger_type = CHARGER_REMOVED;
                notify_charger_type();
            }
            hiusb_otg_and_phy_cleanup();
            __switch_mhl_id();
            wake_unlock(&hiusb_info->dev_wakelock);

            if(hiusb_info->acpu_idle_remove_request)
            {
                hiusb_info->acpu_idle_remove_request(lm_dev);
            }
            dev_dbg(&lm_dev->dev, "%s status:(%d)%s -> %s .\n",
                    __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error", usb_status[HIUSB_OFF]);
            hiusb_info->hiusb_status = HIUSB_OFF;
            break;
        case ID_FALL_EVENT:
            if (hiusb_info->hiusb_status != HIUSB_OFF) {
                dev_err(&lm_dev->dev, "%s ID_FALL in wrong status error:(%d)%s.\n",
                    __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error");
                break;
            }
            if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                hiusb_info->charger_type = USB_EVENT_OTG_ID;
                notify_charger_type();
            }

            if(hiusb_info->acpu_idle_add_request)
            {
                hiusb_info->acpu_idle_add_request(lm_dev);
            }

            wake_lock(&hiusb_info->host_wakelock);
            if (hiusb_info->vbus_pin != 0) {
                gpio_direction_output(hiusb_info->vbus_pin, 1);
            }
            hiusb_otg_and_phy_setup(1);
            ret = dwc_host_insert_init(lm_dev);
            if (0 == ret) {
                dev_dbg(&lm_dev->dev, "%s status:(%d)%s -> %s .\n",
                        __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error", usb_status[HIUSB_HOST]);
                hiusb_info->hiusb_status = HIUSB_HOST;
            } else {
                dev_dbg(&lm_dev->dev, "%s dwc_host_insert_init error .\n", __func__);
                if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                    hiusb_info->charger_type = CHARGER_REMOVED;
                    notify_charger_type();
                }
                hiusb_otg_and_phy_cleanup();
                wake_unlock(&hiusb_info->host_wakelock);
            }
            break;
        case ID_RISE_EVENT:
            if (hiusb_info->hiusb_status != HIUSB_HOST) {
                dev_err(&lm_dev->dev, "%s ID_RISE in wrong status error:(%d)%s.\n",
                    __func__, hiusb_info->hiusb_status,hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error");
#ifdef CONFIG_SWITCH_FSA9685
		if(!id_no_bypass)
                    fsa9685_manual_detach();
#endif
                break;
            }
            dwc_host_draw_init(lm_dev);
            if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                hiusb_info->charger_type = CHARGER_REMOVED;
                notify_charger_type();
            }
            hiusb_otg_and_phy_cleanup();
            if (hiusb_info->vbus_pin != 0) {
                gpio_direction_output(hiusb_info->vbus_pin, 0);
            }
            switch_reset();
            wake_unlock(&hiusb_info->host_wakelock);

            if(hiusb_info->acpu_idle_remove_request)
            {
                hiusb_info->acpu_idle_remove_request(lm_dev);
            }

            dev_dbg(&lm_dev->dev, "%s status:(%d)%s -> %s .\n",
                    __func__, hiusb_info->hiusb_status, hiusb_info->hiusb_status <= HIUSB_MAX_STATUS ? usb_status[hiusb_info->hiusb_status]:"error", usb_status[HIUSB_OFF]);
            hiusb_info->hiusb_status = HIUSB_OFF;
            break;
        default:
            dev_err(&lm_dev->dev, "%s error flag.\n", __func__);
            break;
    }
    up(&hiusb_info->hiusb_info_sema);
    dev_info(&lm_dev->dev, "%s done.\n", __func__);
    return;
}

int hiusb_id_changed(int flag)
{
    struct hiusb_info *hiusb_info;

    if (NULL ==  g_hiusb_info) {
       pr_err("%s: g_hiusb_info not init!\n", __func__);
       return -1;
    }

    if (flag != ID_FALL_EVENT && flag != ID_RISE_EVENT)
    {
        return -EINVAL;
    }
    pr_debug("%s +.\n", __func__);
    hiusb_info = g_hiusb_info;
    spin_lock(&hiusb_info->intr_flag_lock);
    hiusb_info->intr_flag = flag;
    spin_unlock(&hiusb_info->intr_flag_lock);

    schedule_delayed_work(&hiusb_info->otg_intr_work, 0);
    pr_debug("%s %d -.\n", __func__, flag);

    return 0;
}

irqreturn_t hiusb_vbus_intr(int irq, void *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = lm_dev->hiusb_info;
    dev_dbg(&lm_dev->dev, "%s +.\n", __func__);

    spin_lock(&hiusb_info->intr_flag_lock);
    if (irq == hiusb_info->insert_irq) {
        hiusb_info->intr_flag = CHARGER_INSERT;
    } else {
        hiusb_info->intr_flag = CHARGER_DRAW;
    }
    spin_unlock(&hiusb_info->intr_flag_lock);

    if( use_switch_driver && irq == hiusb_info->insert_irq )
        schedule_delayed_work(&hiusb_info->otg_intr_work, msecs_to_jiffies(30) );
    else
	schedule_delayed_work(&hiusb_info->otg_intr_work, 0 );

    dev_dbg(&lm_dev->dev, "%s irq(%d) %s %s -.\n", __func__, irq, "Vbus", (irq==hiusb_info->insert_irq) ? "insert":"remove");
    return IRQ_HANDLED;
}

irqreturn_t hiusb_otggpio_intr(int irq, void *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = lm_dev->hiusb_info;
    dev_dbg(&lm_dev->dev, "%s +.\n", __func__);

    if(1==hiusb_info->otg_without_mhl) {
        if ((irq == IRQ_GPIO(hiusb_info->otg_int_gpio))  &&
		    (0 == gpio_get_value_cansleep(hiusb_info->otg_int_gpio))) {
            if (irq == IRQ_GPIO(hiusb_info->otg_int_gpio) ) {
                switch_usb();
            }
        }
    }


    dev_dbg(&lm_dev->dev, "%s irq %d -.\n", __func__, irq);
    return IRQ_HANDLED;
}

STATIC int hiusb_init_resource(struct lm_device *dev)
{
    int ret = 0;
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;

    ATOMIC_INIT_NOTIFIER_HEAD(&hiusb_info->charger_type_notifier_head);
    spin_lock_init(&hiusb_info->intr_flag_lock);
    wake_lock_init(&hiusb_info->dev_wakelock, WAKE_LOCK_SUSPEND, "hiusb_dev_wakelock");
    wake_lock_init(&hiusb_info->host_wakelock, WAKE_LOCK_SUSPEND, "hiusb_host_wakelock");
    sema_init(&hiusb_info->hiusb_info_sema, 0);
    spin_lock_init(&hiusb_info->switch_lock);
    hiusb_info->charger_type = CHARGER_REMOVED;
    hiusb_info->hiusb_status = HIUSB_OFF;
    hiusb_info->gadget_enable = 0;
    hiusb_info->pm_qos_req.pm_qos_class = 0;

    ret = get_hw_config_int("usb/use_switch_driver", &use_switch_driver, NULL);
    if (false == ret) {
        printk(KERN_ERR "%s : error config usb/use_switch_driver\n", __FUNCTION__);
    }
    dev_info(&lm_dev->dev, "use_switch_driver:%d.\n", use_switch_driver);

    ret = get_hw_config_int("usb/id_no_bypass", &id_no_bypass, NULL);
    if (false == ret) {
        printk(KERN_ERR "%s : error config usb/id_no_bypass\n", __FUNCTION__);
    }
    dev_info(&lm_dev->dev, "id_no_bypass:%d.\n", id_no_bypass);

    ret = get_hw_config_int("usb/otg_without_mhl", &hiusb_info->otg_without_mhl, NULL);

    dev_info(&lm_dev->dev, "otg_without_mhl:%d.\n", hiusb_info->otg_without_mhl);

    ret = get_hw_config_int("usb/gpio_otg_int", &hiusb_info->otg_int_gpio, NULL);
    dev_info(&lm_dev->dev, "gpio_otg_int:%d.\n", hiusb_info->otg_int_gpio);

    hiusb_info->usb_block = iomux_get_block("block_switch");
    hiusb_info->usb_config = iomux_get_blockconfig("block_switch");

    hiusb_info->clk_usbotg_off= clk_get(NULL, "clk_usbotg_off");
    ret = IS_ERR(hiusb_info->clk_usbotg_off);
    if (ret) {
        dev_err(&lm_dev->dev, "get clk_usbotg_off failed!\n");
        goto get_clk_usbotg_off_fail;
    }
    hiusb_info->clk_picophy= clk_get(NULL, "clk_picophy");
    ret = IS_ERR(hiusb_info->clk_picophy);
    if (ret) {
        dev_err(&lm_dev->dev, "get clk_picophy failed!\n");
        goto get_clk_picophy_fail;
    }

    switch_init(lm_dev);

    if (hiusb_info->vbus_pin != 0) {
        ret = gpio_request(hiusb_info->vbus_pin, "USB_VBUS");
        if (ret < 0) {
            dev_err(&dev->dev, "%s usb vbus gpio error", __func__);
            goto request_vbus_pin_fail;
        }
        gpio_direction_output(hiusb_info->vbus_pin, 0);
    }

    if (hiusb_info->phy_reset_pin != 0) {
        ret = gpio_request(hiusb_info->phy_reset_pin, "USBPHY_REST");
        if (ret < 0) {
            dev_err(&dev->dev, "%s usb phy reset gpio error", __func__);
            goto request_gpio_fail;
        }
        gpio_direction_output(hiusb_info->phy_reset_pin, 0);
        mdelay(100);
        gpio_direction_output(hiusb_info->phy_reset_pin, 1);
    }

    if (hiusb_info->otg_int_gpio != -1) {
        ret = gpio_request(hiusb_info->otg_int_gpio, "OTG_INT_GPIO");
        if (ret < 0) {
            dev_err(&dev->dev, "%s usb otg int gpio error", __func__);
            goto request_gpio_fail;
        }
        gpio_direction_input(hiusb_info->otg_int_gpio);
    }

    /* init workqueue for usb insert/draw : only for debug */
    INIT_DELAYED_WORK(&hiusb_info->otg_intr_work, hiusb_otg_intr_work);
    dev_info(&lm_dev->dev, "%s.\n", __func__);

    return 0;

request_gpio_fail:
    if (hiusb_info->vbus_pin != 0) {
        gpio_free(hiusb_info->vbus_pin);
    }
request_vbus_pin_fail:
    clk_put(hiusb_info->clk_picophy);
get_clk_picophy_fail:
    clk_put(hiusb_info->clk_usbotg_off);
get_clk_usbotg_off_fail:
    return ret;
}

STATIC int hiusb_free_resource(struct lm_device *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;

    clk_put(hiusb_info->clk_usbotg_off);
    clk_put(hiusb_info->clk_picophy);
    if (hiusb_info->vbus_pin != 0) {
        gpio_free(hiusb_info->vbus_pin);
    }
    if (hiusb_info->phy_reset_pin != 0) {
        gpio_free(hiusb_info->phy_reset_pin);
    }
    if (hiusb_info->otg_int_gpio != -1) {
        gpio_free(hiusb_info->otg_int_gpio);
    }
    dev_info(&lm_dev->dev, "%s.\n", __func__);
    return 0;
}

STATIC int hiusb_request_irq(struct lm_device *dev)
{
    int ret = 0;
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;

    if (hiusb_info->insert_irq == 0 || hiusb_info->draw_irq == 0) {
        if ((hiusb_info->quirks & HIUSB_QUIRKS_PMUIRQ) == 0) {
            hiusb_info->insert_irq = 1;
            hiusb_info->draw_irq = 2;
        }
        dev_info(&lm_dev->dev, "No insert/draw irq.\n");
        return 0;
    }

    /* request insert irq */
    ret = request_irq(hiusb_info->insert_irq, hiusb_vbus_intr,
            IRQF_NO_SUSPEND, "hiusb_insert_intr", lm_dev);
    if (ret) {
        dev_err(&dev->dev, "request insert irq failed.\n");
        goto request_insert_irq_fail;
    }

    /* request draw irq */
    ret = request_irq(hiusb_info->draw_irq, hiusb_vbus_intr,
            IRQF_NO_SUSPEND, "hiusb_draw_intr", lm_dev);
    if (ret) {
        dev_err(&dev->dev, "request draw irq failed.\n");
        goto request_draw_irq_fail;
    }

    /* request otg gpio int irq */
    if(-1 != hiusb_info->otg_int_gpio) {
        gpio_direction_input(hiusb_info->otg_int_gpio);
        ret = request_irq(IRQ_GPIO(hiusb_info->otg_int_gpio), hiusb_otggpio_intr,
            IRQF_NO_SUSPEND|IRQF_TRIGGER_FALLING, "hiusb_otggpio_intr", lm_dev);
        if (ret) {
            dev_err(&dev->dev, "request gpio irq failed.\n");
            goto request_gpio_irq_fail;
        }
    }

    dev_info(&dev->dev, "request insert irq: %d\n", hiusb_info->insert_irq);
    dev_info(&dev->dev, "request draw irq: %d\n", hiusb_info->draw_irq);
    dev_info(&dev->dev, "request gpio: %d irq\n", hiusb_info->otg_int_gpio);
    return 0;

request_gpio_irq_fail:
    free_irq(hiusb_info->draw_irq, dev);
request_draw_irq_fail:
    free_irq(hiusb_info->insert_irq, dev);
request_insert_irq_fail:
    return ret;
}

STATIC int hiusb_free_irq(struct lm_device *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;

    if (hiusb_info->insert_irq == 0 || hiusb_info->draw_irq == 0
            || (hiusb_info->quirks & HIUSB_QUIRKS_PMUIRQ) == 0) {
        dev_info(&lm_dev->dev, "No insert/draw irq.\n");
    } else {
        free_irq(hiusb_info->insert_irq, dev);
        free_irq(hiusb_info->draw_irq, dev);
    }
    dev_info(&lm_dev->dev, "%s.\n", __func__);
    return 0;
}

STATIC int hiusb_pullup(struct lm_device *dev,int is_on)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;

    if (is_on) {
        hiusb_info->gadget_enable = 1;
    } else {
        hiusb_info->gadget_enable = 0;
    }

    dev_dbg(&lm_dev->dev, "%s !\n", __func__);

    return 0;
}

STATIC int hiusb_suspend(struct lm_device *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;
    __switch_usb_id();

    dev_dbg(&lm_dev->dev, "%s !\n", __func__);

    return 0;
}

STATIC int hiusb_resume(struct lm_device *dev)
{
    struct lm_device *lm_dev;

    struct hiusb_info *hiusb_info;
    int state;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;
    /* nothing to do */
    state = sel_state();
    if (state == 1) {
        switch_reset();
    } else {
        __switch_mhl_id();
    }

    dev_dbg(&lm_dev->dev, "%s !\n", __func__);

    return 0;
}

STATIC int hiusb_init_phase1(struct lm_device *dev)
{
    int ret = 0;
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = dev->hiusb_info;
    hiusb_info->lm_dev = lm_dev;
    /* only for charger */
    g_hiusb_info =  dev->hiusb_info;

    /*init resource*/
    ret = hiusb_init_resource(lm_dev);
    if (ret < 0) {
        dev_err(&dev->dev, "hiusb_init_resource failed!\n");
        goto request_init_resource_fail;
    }

    hiusb_otg_and_phy_setup(0);

    if (pmu_version() == 0) {
        dev_info(&dev->dev, "pmu ec before!\n");
        dev_info(&dev->dev, "dev wakelock!\n");
        if(hiusb_info->acpu_idle_add_request)
        {
            hiusb_info->acpu_idle_add_request(lm_dev);
        }

        wake_lock(&hiusb_info->dev_wakelock);
    } else {
        dev_info(&dev->dev, "pmu ec after!\n");
        if (vbus_status() != 0) {
            dev_info(&dev->dev, "dev wakelock!\n");
            if(hiusb_info->acpu_idle_add_request)
            {
                hiusb_info->acpu_idle_add_request(lm_dev);
            }

            wake_lock(&hiusb_info->dev_wakelock);
            if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
                hiusb_info->charger_type = detect_charger_type();
                notify_charger_type();
            }
        }
    }

    hiusb_attr_create(lm_dev);

    dev_info(&lm_dev->dev, "%s done.\n", __func__);

    return 0;

request_init_resource_fail:
    return ret;
}

STATIC int hiusb_init_phase2(struct lm_device *dev)
{
    int ret;
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = lm_dev->hiusb_info;

    ret = hiusb_request_irq(lm_dev);
    if (ret < 0) {
        dev_err(&dev->dev, "hiusb_request_irq failed!\n");
        goto request_irq_fail;
    }

    /* init finish */

    if (hiusb_is_host_mode(lm_dev)) {
        dev_info(&dev->dev, "host wakelock!\n");
        if(hiusb_info->acpu_idle_add_request)
        {
            hiusb_info->acpu_idle_add_request(lm_dev);
        }
        wake_lock(&hiusb_info->host_wakelock);
        if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
            hiusb_info->charger_type = USB_EVENT_OTG_ID;
            notify_charger_type();
        }
        hiusb_info->hiusb_status = HIUSB_HOST;
    } else if ((pmu_version() != 0) && (vbus_status() == 0)) {
        dev_info(&dev->dev, "usb disconnect!\n");
        hiusb_otg_and_phy_cleanup();
        wake_unlock(&hiusb_info->dev_wakelock);
        if (hiusb_info->quirks & HIUSB_QUIRKS_CHARGER) {
            hiusb_info->charger_type = CHARGER_REMOVED;
            notify_charger_type();
        }
        hiusb_info->hiusb_status = HIUSB_OFF;
    } else {
        hiusb_info->hiusb_status = HIUSB_DEVICE;
        dwc_pm_runtime_disable(lm_dev);
    }
    up(&hiusb_info->hiusb_info_sema);

    dev_info(&lm_dev->dev, "%s done.\n", __func__);

    return 0;

request_irq_fail:
    hiusb_free_resource(lm_dev);
    return ret;
}

STATIC int hiusb_remove(struct lm_device *dev)
{
    struct lm_device *lm_dev;
    struct hiusb_info *hiusb_info;

    lm_dev = dev;
    hiusb_info = lm_dev->hiusb_info;
    hiusb_attr_remove(lm_dev);
    hiusb_free_resource(lm_dev);
    hiusb_free_irq(lm_dev);
    return 0;
}


STATIC void hiusb_acpu_idle_add_request(struct lm_device *dev)
{
    struct hiusb_info *hiusb_info;
    hiusb_info = dev->hiusb_info;
    dev_info(&dev->dev, "add request!\n");

    if(pm_qos_request_active(&hiusb_info->pm_qos_req)){
        printk(KERN_ERR "hiusb_acpu_idle_add_request, already add request! \n");
        return;
    }

    pm_qos_add_request(&hiusb_info->pm_qos_req, PM_QOS_CPU_INT_LATENCY, USB_QOS);
}

STATIC void hiusb_acpu_idle_remove_request(struct lm_device *dev)
{
    struct hiusb_info *hiusb_info;
    hiusb_info = dev->hiusb_info;

    dev_info(&dev->dev, "remove request!\n");

    if (!pm_qos_request_active(&hiusb_info->pm_qos_req)){
        printk(KERN_ERR "hiusb_acpu_idle_remove_request, remove request which hadn't been added!!! \n");
        return;
    }

    pm_qos_remove_request(&hiusb_info->pm_qos_req);
}


/* ---------------------- usb oem -------------------------------------*/
STATIC struct hiusb_info hiusb_sft_info = {
    .phy_reset_pin      =   GPIO_2_2,
    .init_phase1        =   hiusb_init_phase1,
    .init_phase2        =   hiusb_init_phase2,
    .remove             =   hiusb_remove,
    .pullup             =   hiusb_pullup,
    .suspend            =   hiusb_suspend,
    .resume             =   hiusb_resume,
};


struct lm_device usb_sft_otg = {
    .dev            = {
        .init_name = HI6620_USB_NAME,
    },
    .resource.start = REG_BASE_USBOTG,
    .resource.end = REG_BASE_USBOTG + REG_USBOTG_IOSIZE - 1,
    .resource.flags = IORESOURCE_MEM,
    .irq = IRQ_USB2OTG,
    .hiusb_info = &hiusb_sft_info,
    .id = -1,
};

/* ---------------------- usb oem -------------------------------------*/

STATIC struct hiusb_info hiusb_oem_info = {

    .switch_pin1            = -1,
    .switch_pin2            = -1,
    .switch_id_pin          = -1,
    .cdma_usb_enable       = -1,
    .otg_int_gpio            = -1,
    .otg_without_mhl         = -1,
    .insert_irq              = IRQ_VBUS_COMP_VBAT_RISING,
    .draw_irq               = IRQ_VBUS_COMP_VBAT_FALLING,
    .quirks                  =   HIUSB_QUIRKS_CHARGER | HIUSB_QUIRKS_PMUIRQ,
    .init_phase1           =   hiusb_init_phase1,
    .init_phase2           =   hiusb_init_phase2,
    .pullup                   =   hiusb_pullup,
    .remove                 =   hiusb_remove,
    .suspend                =   hiusb_suspend,
    .resume                  =   hiusb_resume,
    .acpu_idle_add_request = hiusb_acpu_idle_add_request,
    .acpu_idle_remove_request = hiusb_acpu_idle_remove_request,
};

static struct lm_device usb_oem_otg = {
    .dev            = {
        .init_name = HI6620_USB_NAME,
    },
    .resource.start = REG_BASE_USBOTG,
    .resource.end = REG_BASE_USBOTG + REG_USBOTG_IOSIZE - 1,
    .resource.flags = IORESOURCE_MEM,
    .irq = IRQ_USB2OTG,
    .hiusb_info = &hiusb_oem_info,
    .id = -1,
};

static int lm_dev_init(void)
{
#ifdef RUN_IN_EMULATOR
    return 0;
#endif

    return lm_device_register(&usb_oem_otg);
}

arch_initcall(lm_dev_init);

#ifdef CONFIG_SWITCH_USB_CLS
static int __init plat_usb_dev_init(void)
{
    int ret = 0;

    ret = platform_add_devices(plat_usb_dev, ARRAY_SIZE(plat_usb_dev));

    return ret;
};

device_initcall(plat_usb_dev_init);
#endif


/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: switch_fsa9685.c
* Author: lixiuna(00213837)       Version : 0.1      Date:  2013-11-06
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*  Description:    .c file for switch chip
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/param.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <asm/mach/irq.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/switch_usb.h>
#include "switch_chip.h"
#include <hsad/config_mgr.h>
#include <linux/usb/balong/hisi_susb.h>

//#define USE_LEVEL_IRQ
#define FSA9685_HAVE_PM
#define FSA9685_HAVE_RESET

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif

#define PLAT_K3V3   0
#define PLAT_V9R1   1
#define USE_DTS     0
#define USE_BOARDID 1
#define STATUS_FSA9685_ATTACH	1
#define STATUS_FSA9685_DETACH	0
#define STATUS_FSA9685_UNINIT	2
#define FSA9685_ERROR_TAG       "fsa9685_error"
static int gpio = -1;
static struct i2c_client *this_client = NULL;
static struct work_struct   g_intb_work;
static struct work_struct   g_detach_work;
static struct work_struct   g_reset_work;
static int g_detach_work_init = 0;
DEFINE_SEMAPHORE(g_intb_sema);
#ifdef CONFIG_FSA9685_DEBUG_FS
static int reg_locked = 1;
static char chip_regs[0x20] = { 0 };
#endif
extern int hiusb_id_changed(int flag);
static void fsa9685_intb_work(struct work_struct *work);
static struct i2c_board_info fsa9685_i2c_bus_devs[]= {
	[0]	=	{
		.type			= "fsa9685",
		.addr			= 0x25,
	},
};

static int fsa9685_write_reg(int reg, int val)
{
    int ret;
    ret = i2c_smbus_write_byte_data(this_client, reg, val);
    if (ret < 0)
        printk(KERN_ERR "%s: reg:%d, val:0x%x, error=%d", __func__, reg, val, ret);

#ifdef CONFIG_FSA9685_DEBUG_FS
    if (ret >= 0)
        chip_regs[reg] = val;
#endif
    return ret;
}

static int fsa9685_read_reg(int reg)
{
    int ret;
    ret = i2c_smbus_read_byte_data(this_client, reg);
    if (ret < 0)
        printk(KERN_ERR "%s: reg:%d, error = %d", __func__, reg, ret);

#ifdef CONFIG_FSA9685_DEBUG_FS
    if (ret >=0 )
        chip_regs[reg] = ret;
#endif
    return ret;
}

int fsa9685_manual_sw(int input_select)
{
    int value = 0, ret = 0;
    if (NULL == this_client)
    {
        printk(KERN_ERR "%s: error this_client = NULL" ,__func__);
        return -ENODEV;
    }

    printk(KERN_INFO "%s: input_select = %d" ,__func__, input_select);
    switch (input_select)
    {
        case FSA9685_USB1:
            value = REG_VAL_FSA9685_USB1;
            break;
        case FSA9685_USB2:
            value = REG_VAL_FSA9685_USB2;
            break;
        case FSA9685_UART:
            value = REG_VAL_FSA9685_UART;
            break;
        case FSA9685_MHL:
            value = REG_VAL_FSA9685_MHL;
            break;
        case FSA9685_OPEN:
        default:
            value = REG_VAL_FSA9685_OPEN;
            break;
    }

    ret = fsa9685_write_reg(FSA9685_REG_MANUAL_SW_1, value);
    if ( ret < 0 )
        return ERRNUM_FSA9685_REG_MANUAL_SW_1;

    value = fsa9685_read_reg(FSA9685_REG_CONTROL);
    value &= (~FSA9685_MANUAL_SW); // 0: manual switching
    ret = fsa9685_write_reg(FSA9685_REG_CONTROL, value);
    if ( ret < 0 )
        return ERRNUM_FSA9685_REG_CONTROL;

    return 0;
}
EXPORT_SYMBOL_GPL(fsa9685_manual_sw);

static void fsa9685_reset_work(struct work_struct *work)
{
    int ret, reg02, reg04;
    if (NULL == this_client)
    {
        printk(KERN_ERR "%s: error this_client = NULL" ,__func__);
        return;
    }

    ret = fsa9685_write_reg(FSA9685_REG_RESET, 0x89);
    if ( ret < 0 )
        printk(KERN_ERR "%s: error write iic reg" ,__func__);

    /* clear INT MASK */
    reg02 = fsa9685_read_reg(FSA9685_REG_CONTROL);
    reg04 = fsa9685_read_reg(FSA9685_REG_INTERRUPT_MASK);
    printk(KERN_INFO "%s: fsa9685_read_reg(FSA9685_REG_CONTROL) reg02=0x%x reg04=0x%x.\n", __func__, reg02, reg04);
    reg04 &= (~FSA9685_VBUS_CHANGE);
    ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg04);
    if(ret<0){
        printk(KERN_ERR "%s write iic reg04 %d\n", __func__, ret);
    }

    reg02 &= (~FSA9685_INT_MASK);
    ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg02);
    if(ret<0){
        printk(KERN_ERR "%s write iic reg02 %d\n", __func__, ret);
    }

    return;
}

int fsa9685_manual_detach(void)
{
    int ret = -1;
    printk(KERN_INFO "%s++\n" ,__func__ );
    if(g_detach_work_init){
        schedule_work(&g_detach_work);
        ret = 0;
    }else{
        printk(KERN_ERR "%s: error not init work" ,__func__);
    }
    printk(KERN_INFO "%s-- %d\n" ,__func__, ret);
    return ret;
}
static void fsa9685_detach_work(struct work_struct *work)
{
    int ret;
    if (NULL == this_client)
    {
        printk(KERN_ERR "%s: error this_client = NULL" ,__func__);
        return;
    }

    ret = fsa9685_write_reg(FSA9685_REG_DETACH_CONTROL, 1);
    if ( ret < 0 )
        printk(KERN_ERR "%s: error write iic reg" ,__func__);

    return;
}
EXPORT_SYMBOL_GPL(fsa9685_manual_detach);
static irqreturn_t fsa9685_irq_handler(int irq, void *dev_id)
{
    printk(KERN_INFO "%s fsa9685_intb_work: ++\n", __func__);

#ifdef USE_LEVEL_IRQ
    fsa9685_intb_work(&g_intb_work);
#else
    schedule_work(&g_intb_work);
#endif

    printk(KERN_INFO "%s fsa9685_intb_work: --\n", __func__);
    return IRQ_HANDLED;
}

static void fsa9685_intb_work(struct work_struct *work)
{
    int gpio_value = 0;
    int reg02, reg03, reg05, reg08, reg09, reg10;
    int ret = -1;
    static int otg_attach = 0;
    int invalid_status=1;
    static int invalid_times=0;
    static int last_status = STATUS_FSA9685_UNINIT;

    if (down_interruptible(&g_intb_sema)) {
        printk(KERN_ERR "%s %s down_interruptible error\n", __func__, FSA9685_ERROR_TAG);
        return;
    }

    printk(KERN_INFO "%s ++\n", __func__);

    gpio_value = gpio_get_value(gpio);

    reg03 = fsa9685_read_reg(FSA9685_REG_INTERRUPT);
    printk(KERN_INFO "%s reg03=0x%x\n", __func__,reg03);

    if(unlikely(reg03<0)){
         invalid_status=0;
         printk(KERN_ERR "%s %s read intr error\n", __func__, FSA9685_ERROR_TAG);
    }else if(unlikely(reg03==0)){
         invalid_status=0;
         printk(KERN_ERR "%s no intr\n", __func__);
    }else {
	if(gpio_value==1){
            printk(KERN_ERR "%s %s intb high when interrupt\n", __func__, FSA9685_ERROR_TAG);
        }

        if ( (reg03 & FSA9685_DETACH) && (last_status == STATUS_FSA9685_ATTACH) )
        {
            printk(KERN_INFO "%s: FSA9685_DETACH\n", __func__);
	    reg03 &= ~FSA9685_DETACH;
            last_status = STATUS_FSA9685_DETACH;
            invalid_status = 0;
            /* check control register, if manual switch, reset to auto switch */
            reg02 = fsa9685_read_reg(FSA9685_REG_CONTROL);
            reg09 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_2);
            printk(KERN_INFO "%s reg02=0x%x\n", __func__, reg02);
            if ( 0 == (reg02 & FSA9685_MANUAL_SW) )
            {
                reg02 |= FSA9685_MANUAL_SW;
                ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg02);
                if ( ret < 0 ){
                    printk(KERN_ERR "%s %s write reg02 fail\n", __func__, FSA9685_ERROR_TAG);
                    goto OUT;
                }
            }
            if (reg09 & FSA9685_JIG_UART ) {
                printk(KERN_INFO "%s: FSA9685_JIG_UART\n", __func__);
            }
	    if (otg_attach==1) {
                hiusb_id_changed(ID_RISE_EVENT);
		otg_attach=0;
	    }
        }


        if ( reg03 & FSA9685_ATTACH )
        {
            last_status = STATUS_FSA9685_ATTACH;
	    reg03 &= ~FSA9685_ATTACH;
            printk(KERN_INFO "%s: FSA9685_ATTACH\n", __func__);
            reg08 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_1);
            reg09 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_2);
            reg10 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_3);
            printk(KERN_INFO "%s reg08=0x%x, reg09=0x%x, reg10=0x%x\n", __func__, reg08, reg09, reg10);

            if (reg08 & FSA9685_FC_USB_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_FC_USB_DETECTED\n", __func__);
            }
            if (reg08 & FSA9685_FC_RF_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_FC_RF_DETECTED\n", __func__);
            }
            if (reg08 & FSA9685_USB_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_USB_DETECTED\n", __func__);
                invalid_status = 0;
                if (FSA9685_USB1 == get_swstate_value())
                {
                    switch_usb2_access_through_ap();
                    printk(KERN_INFO "%s: fsa9685 switch to USB2 by setvalue\n", __func__);
                }
            }
            if (reg08 & FSA9685_UART_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_UART_DETECTED\n", __func__);
            }
            if (reg08 & FSA9685_MHL_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_MHL_DETECTED\n", __func__);
                invalid_status = 0;
            }
            if (reg08 & FSA9685_CDP_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_CDP_DETECTED\n", __func__);
                invalid_status = 0;
            }
            if (reg08 & FSA9685_DCP_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_DCP_DETECTED\n", __func__);
                invalid_status = 0;
            }
            if (reg08 & FSA9685_USBOTG_DETECTED ) {
                printk(KERN_INFO "%s: FSA9685_USBOTG_DETECTED and wait for 30ms\n", __func__);
                invalid_status = 0;
                msleep(30);
		otg_attach = 1;
                hiusb_id_changed(ID_FALL_EVENT);
            }
            if (reg09 & FSA9685_JIG_UART ) {
                printk(KERN_INFO "%s: FSA9685_JIG_UART\n", __func__);
                invalid_status = 0;
            }

        }

        if ( reg03 & FSA9685_DETACH )
        {
            printk(KERN_INFO "%s: FSA9685_DETACH\n", __func__);
	    reg03 &= ~FSA9685_DETACH;
            last_status = STATUS_FSA9685_DETACH;
            invalid_status = 0;
            /* check control register, if manual switch, reset to auto switch */
            reg02 = fsa9685_read_reg(FSA9685_REG_CONTROL);
            reg09 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_2);
            printk(KERN_INFO "%s reg02=0x%x\n", __func__, reg02);
            if ( 0 == (reg02 & FSA9685_MANUAL_SW) )
            {
                reg02 |= FSA9685_MANUAL_SW;
                ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg02);
                if ( ret < 0 ){
                    printk(KERN_ERR "%s %s write reg02 fail\n", __func__, FSA9685_ERROR_TAG);
                    goto OUT;
                }
            }
            if (reg09 & FSA9685_JIG_UART ) {
                printk(KERN_INFO "%s: FSA9685_JIG_UART\n", __func__);
            }
	    if (otg_attach==1) {
                hiusb_id_changed(ID_RISE_EVENT);
		otg_attach=0;
	    }
        }

        if ( reg03 & FSA9685_VBUS_CHANGE)
        {
            invalid_status = 0;
            printk(KERN_INFO "%s: FSA9685_VBUS_CHANGE\n", __func__);
        }

        if ( reg03 & FSA9685_RESERVED_ATTACH )
        {
            printk(KERN_INFO "%s: FSA9685_RESERVED_ATTACH\n", __func__);
        }

        if ( reg03 & FSA9685_ADC_CHANGE)
        {
            reg05 = fsa9685_read_reg(FSA9685_REG_ADC);
            printk(KERN_INFO "%s: FSA9685_ADC_CHANGE. reg05= 0x%x\n", __func__, reg05);
            /* do user specific handle */
        }
    }
OUT:
#ifdef FSA9685_HAVE_RESET
    if(invalid_status && invalid_times<3){
        invalid_times++;
        printk(KERN_ERR "%s %s invalid time:%d reset fsa9685 work\n", __func__, FSA9685_ERROR_TAG, invalid_times);
        fsa9685_reset_work(&g_reset_work);
    }else{
	invalid_times=0;
    }
#endif
    up(&g_intb_sema);
    printk(KERN_INFO "%s --\n", __func__);
    return;
}

#ifdef CONFIG_FSA9685_DEBUG_FS
static ssize_t dump_regs_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    const int regaddrs[] = {0x01, 0x02, 0x03, 0x04, 0x5, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d};
    const char str[] = "0123456789abcdef";
    int i = 0, index;
    char val = 0;
    for (i=0; i<0x60; i++) {
        if ((i%3)==2)
            buf[i]=' ';
        else
            buf[i] = 'x';
    }
    buf[0x5d] = '\n';
    buf[0x5e] = 0;
    buf[0x5f] = 0;
    if ( reg_locked != 0 ) {
        for (i=0; i<ARRAY_SIZE(regaddrs); i++) {
            if (1/*regaddrs[i] != 0x03*/) {
                val = fsa9685_read_reg(regaddrs[i]);
                chip_regs[regaddrs[i]] = val;
            }
        }
    }

    for (i=0; i<ARRAY_SIZE(regaddrs); i++) {
        index = regaddrs[i];
        val = chip_regs[index];
            buf[3*index] = str[(val&0xf0)>>4];
        buf[3*index+1] = str[val&0x0f];
        buf[3*index+2] = ' ';
    }

    return 0x60;
}
static DEVICE_ATTR(dump_regs, S_IRUGO | S_IWUSR, dump_regs_show, NULL);
#endif


#ifdef CONFIG_OF
static const struct of_device_id switch_fsa9685_ids[] = {
    { .compatible = "huawei,fairchild_fsa9685" },
    {},
};
MODULE_DEVICE_TABLE(of, switch_fsa9685_ids);
#endif

static int fsa9685_probe(
    struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0, reg02, reg04, reg08, reg09, gpio_value;
    struct device_node *node = client->dev.of_node;

    printk(KERN_INFO "%s++\n", __func__);

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
        printk(KERN_ERR "%s i2c check fail\n", __func__);
        ret = -ENODEV;
        this_client == NULL;
        goto check_funcionality_failed;
    }
    this_client = client;

    INIT_WORK(&g_detach_work, fsa9685_detach_work);
    g_detach_work_init = 1;
    INIT_WORK(&g_reset_work, fsa9685_reset_work);

#ifdef CONFIG_FSA9685_DEBUG_FS
    ret = device_create_file(&client->dev, &dev_attr_dump_regs);
        if (ret < 0) {
            printk(KERN_ERR "%s create dev file fail %d\n", __func__, ret);
            ret = ERRNUM_SWITCH_USB_DEV_REGISTER;
            goto err_switch_usb_dev_register;
        }
#endif

#if USE_DTS
    gpio = of_get_named_gpio(node, "fairchild_fsa9685,gpio-intb", 0);
#endif
#if USE_BOARDID
    get_hw_config_int("usb/gpio_intb", &gpio, NULL);
#endif
    printk(KERN_INFO "%s gpio_intb=%d\n", __func__, gpio);
    if (gpio < 0) {
        ret = ERRNUM_OF_GET_NAME_GPIO;
        goto err_of_get_named_gpio;
    }

#if PLAT_K3V3
    client->irq = gpio_to_irq(gpio);
#endif
#if PLAT_V9R1
    client->irq = IRQ_GPIO(gpio);
#endif
    if (client->irq < 0) {
        printk(KERN_ERR "%s get irq fail\n", __func__);
        ret = ERRUNM_GPIO_TO_IRQ;
        goto err_gpio_to_irq;
    }

    ret = gpio_request(gpio, "fsa9685_int");
    if (ret < 0) {
        printk(KERN_ERR "%s request gpio:%d fail\n", __func__, gpio);
        ret = ERRNUM_GPIO_REQUEST;
        goto err_gpio_request;
    }

    ret = gpio_direction_input(gpio);
    if (ret < 0) {
        printk(KERN_ERR "%s set dir %d fail\n", __func__, gpio);
        ret = ERRNUM_GPIO_DIRECTION_INPUT;
        goto err_gpio_direction_input;
    }
    reg08 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_1);
    reg09 = fsa9685_read_reg(FSA9685_REG_DEVICE_TYPE_2);
    printk(KERN_INFO "%s: reg08=0x%x reg09=0x%x.\n", __func__, reg08, reg09);
    if(!( (reg08 & (FSA9685_USB_DETECTED| FSA9685_MHL_DETECTED| FSA9685_CDP_DETECTED| FSA9685_DCP_DETECTED/*| FSA9685_USBOTG_DETECTED*/)) || (reg09 & FSA9685_JIG_UART) ) ) {
         printk(KERN_INFO "%s: no valid device,start reset \n", __func__);
	 ret = fsa9685_write_reg(FSA9685_REG_RESET, 0x89);
         if ( ret < 0 )
             printk(KERN_ERR "%s: error write iic reg" ,__func__);
    }
    /* interrupt register */
    INIT_WORK(&g_intb_work, fsa9685_intb_work);
#ifndef USE_LEVEL_IRQ
    ret = request_irq(client->irq,
               fsa9685_irq_handler,
               IRQF_TRIGGER_FALLING,
               "fsa9685_int", client);
#endif
    if (ret < 0) {
        printk(KERN_ERR "%s request thread irq %d fail\n", __func__, ret);
        ret = ERRNUM_REQUEST_THREADED_IRQ;
        goto err_request_threaded_irq;
    }
    /* clear INT MASK */
    reg02 = fsa9685_read_reg(FSA9685_REG_CONTROL);
    reg04 = fsa9685_read_reg(FSA9685_REG_INTERRUPT_MASK);
    printk(KERN_INFO "%s: fsa9685_read_reg(FSA9685_REG_CONTROL) reg02=0x%x reg04=0x%x.\n", __func__, reg02, reg04);
    reg04 &= (~FSA9685_VBUS_CHANGE);
    ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg04);
    if(ret<0){
        printk(KERN_ERR "%s write iic reg04 %d\n", __func__, ret);
        goto err_i2c_write;
    }
    reg02 &= (~FSA9685_INT_MASK);
    ret = fsa9685_write_reg(FSA9685_REG_CONTROL, reg02);
    if(ret<0){
        printk(KERN_ERR "%s write iic reg02 %d\n", __func__, ret);
        goto err_i2c_write;
    }

    gpio_value = gpio_get_value(gpio);
    printk(KERN_INFO "%s intb=%d after clear MASK\n", __func__, gpio_value);

#ifdef USE_LEVEL_IRQ
    ret = request_threaded_irq(client->irq, NULL,
               fsa9685_irq_handler,
               IRQF_TRIGGER_LOW | IRQF_ONESHOT,
               "fsa9685_int", client);
#endif

#ifndef USE_LEVEL_IRQ
    schedule_work(&g_intb_work);
#endif

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    set_hw_dev_flag(DEV_I2C_USB_SWITCH);
#endif


    goto ret_val;

err_i2c_write:
err_request_threaded_irq:
err_gpio_direction_input:
    gpio_free(gpio);
err_gpio_request:
err_gpio_to_irq:
err_of_get_named_gpio:
err_switch_usb_dev_register:
check_funcionality_failed:

ret_val:
    printk(KERN_INFO "%s-- ret = %d.\n",__func__, ret);
    return ret;
}

static int fsa9685_remove(struct i2c_client *client)
{
    printk(KERN_INFO "%s++\n",__func__);
    free_irq(client->irq, client);
    gpio_free(gpio);
    printk(KERN_INFO "%s--\n",__func__);
    return 0;
}

static int fsa9685_suspend(struct i2c_client *client,
              pm_message_t state)
{
    printk(KERN_INFO "%s ++\n", __func__);
    printk(KERN_INFO "%s --\n", __func__);
    return 0;
}

static int fsa9685_resume(struct i2c_client *client)
{
   printk(KERN_INFO "%s ++\n", __func__);
   schedule_work(&g_intb_work);
   printk(KERN_INFO "%s --\n", __func__);
   return 0;
}

static const struct i2c_device_id fsa9685_i2c_id[] = {
    { "fsa9685", 0 },
    { }
};

static struct i2c_driver fsa9685_i2c_driver = {
    .driver = {
        .name = "fsa9685",
        .owner = THIS_MODULE,
#if USE_DTS
        .of_match_table = of_match_ptr(switch_fsa9685_ids),
#endif
    },
    .probe    = fsa9685_probe,
    .remove   = fsa9685_remove,
#ifdef FSA9685_HAVE_PM
    .suspend = fsa9685_suspend,
    .resume = fsa9685_resume,
#endif
    .id_table = fsa9685_i2c_id,
};

static __init int fsa9685_i2c_init(void)
{
    int ret = 0;
    printk(KERN_INFO "%s++\n", __func__);
    ret = i2c_add_driver(&fsa9685_i2c_driver);
    if(ret)
        printk(KERN_ERR "add fsa9685 i2c driver failed\n");
    printk(KERN_INFO "%s-- %d\n", __func__, ret);
    return ret;
}

static __exit void fsa9685_i2c_exit(void)
{
    i2c_del_driver(&fsa9685_i2c_driver);
}

module_init(fsa9685_i2c_init);
module_exit(fsa9685_i2c_exit);

static int __init fsa9685_dev_init(void)
{
    int status;
    printk(KERN_INFO "%s++\n", __func__);
    status = i2c_register_board_info(0,&fsa9685_i2c_bus_devs[0], ARRAY_SIZE(fsa9685_i2c_bus_devs));

    if(status)
    {
        printk(KERN_ERR "%s register fsa9685 hardware device error! %d\n", __func__, status);
    }
    printk(KERN_INFO "%s-- %d\n", __func__, status);
    return status;
}

postcore_initcall(fsa9685_dev_init);

MODULE_AUTHOR("Lixiuna<lixiuna@huawei.com>");
MODULE_DESCRIPTION("I2C bus driver for FSA9685 USB Accesory Detection Switch");
MODULE_LICENSE("GPL v2");

/*
 * arch/arm/mach-k3v2/board-tc45msu3.c
 *
 * Copyright (C) 2010 Google, Inc.
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
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/serial_8250.h>
#include <linux/clk.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <linux/dma-mapping.h>
#include <linux/pda_power.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/sysdev.h>
#include <linux/amba/bus.h>
#include <linux/io.h>
#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS_RMI4
#include <linux/synaptics_i2c_rmi4.h>
#endif
#include <linux/i2c.h>
#include <linux/power/k3_bq24161.h>
#include <linux/power/k3_bq27510.h>
#include <linux/power/k3_battery_monitor.h>
#include <linux/mhl/mhl.h>

#include <linux/hkadc/hiadc_hal.h>
#include <asm/setup.h>
#include <asm/mach-types.h>
#include <asm/system.h>
#include <asm/mach/arch.h>
#include <mach/hardware.h>
#include <mach/system.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/gpio.h>
#include <mach/early-debug.h>
#include <mach/hisi_mem.h>
#include <mach/k3_keypad.h>
#include <mach/boardid.h>
#include <mach/atmel_mXT224E.h>
#include <mach/tps61310.h>

#include "board.h"
#include "clock.h"
#include "k3v2_clocks_init_data.h"
#include <mach/sound/tpa2028_spk_l.h>
#include <mach/sound/tpa2028_spk_r.h>
#include <mach/sound/tpa6132.h>
#include <mach/sound/es305.h>
#include <mach/dev_gps.h>

#include <linux/switch_usb.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/irq.h>
#include <hsad/config_debugfs.h>
#include <hsad/config_interface.h>
#ifdef CONFIG_LEDS_K3_6421
#include <linux/led/k3-leds.h>
#endif

#ifdef CONFIG_ANDROID_K3_VIBRATOR
#include <linux/vibrator/k3_vibrator.h>
#endif

#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif
#ifdef CONFIG_TOUCHSCREEN_RMI4_SYNAPTICS_GENERIC
#include <linux/rmi.h>
#include <linux/interrupt.h>
#endif

#define	GPIO_BT_EN					(GPIO_21_1)
#define	GPIO_BT_RST					(GPIO_21_0)
#define	GPIO_HOST_WAKEUP			(GPIO_20_6)
#define	GPIO_DEV_WAKEUP				(GPIO_20_7)

#define	REGULATOR_DEV_BLUETOOTH_NAME	"bt-io"


/* for framebuffer */
#define TOUCH_INT_PIN  GPIO_19_5  /*GPIO_157*/
#define TOUCH_RESET_PIN GPIO_19_4
#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS2202
#define ENABLE_GPIO GPIO_7_5 /*GPIO_61*/
#endif
#define SYNA_NAME "rmi_i2c"
#ifdef CONFIG_LCD_TOSHIBA_MDW70
#define PLATFORM_DEVICE_LCD_NAME "mipi_toshiba_MDW70_V001"
#elif  defined(CONFIG_LCD_PANASONIC_VVX10F002A00)
#define PLATFORM_DEVICE_LCD_NAME "mipi_panasonic_VVX10F002A00"
#elif defined(CONFIG_LCD_CMI_OTM1280A)
#define PLATFORM_DEVICE_LCD_NAME "mipi_cmi_OTM1280A"
#elif defined(CONFIG_LCD_SAMSUNG_LMS350DF04)
#define PLATFORM_DEVICE_LCD_NAME "ldi_samsung_LMS350DF04"
#elif defined(CONFIG_LCD_SAMSUNG_S6E39A)
#define PLATFORM_DEVICE_LCD_NAME "mipi_samsung_S6E39A"
#elif defined(CONFIG_LCD_SHARP_LS035B3SX)
#define PLATFORM_DEVICE_LCD_NAME "mipi_sharp_LS035B3SX"
#elif defined(CONFIG_LCD_CMI_PT045TN07)
#define PLATFORM_DEVICE_LCD_NAME "mipi_cmi_PT045TN07"
#elif defined(CONFIG_LCD_JDI_OTM1282B)
#define PLATFORM_DEVICE_LCD_NAME "mipi_jdi_OTM1282B"
#elif defined(CONFIG_LCD_TOSHIBA_MDY90)
#define PLATFORM_DEVICE_LCD_NAME "mipi_toshiba_MDY90"
#elif defined(CONFIG_LCD_K3_FAKE)
#define PLATFORM_DEVICE_LCD_NAME "lcd_k3_fake_fb"
#else
#error "PLATFORM_DEVICE_LCD_NAME not defined"
#endif

#define GPIO_GPS_BCM_VBAT_ENABLE    (GPIO_18_7)
#define GPIO_GPS_BCM_RESET   (GPIO_19_0)

//#define GPIO_GPS_BCM_EN_NAME    "gpio_gps_bcm_enable"
//#define GPIO_GPS_BCM_RET_NAME   "gpio_gps_bcm_rest"


static struct resource k3_adc_resources = {
	.start	= REG_BASE_PMUSPI,
	.end	= REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
	.flags	= IORESOURCE_MEM,
};

static struct adc_data hi6421_adc_table[] = {
	{
		.ch = ADC_ADCIN1,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_ADCIN2,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_ADCIN3,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_NC0,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_VBATMON,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER2,
	},
	{
		.ch = ADC_VCOINMON,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER2,
	},
	{
		.ch = ADC_RTMP,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_PB_DETECT,
		.vol = ADC_VOLTAGE_MOD2,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_NC1,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_NC2,
		.vol = ADC_VOLTAGE_MOD1,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
	{
		.ch = ADC_500K,
		.vol = ADC_VOLTAGE_MOD2,
		.clock = HKADC_CK_SEL_TWO,
		.buffer = HKADC_BUFF_SEL_YES,
		.parameter = ADC_PARAMETER1,
	},
};

static struct adc_dataEx hi6421_adc_tableEx = {
	.data = hi6421_adc_table,
	.sum = ARRAY_SIZE(hi6421_adc_table),
};

static struct platform_device hisik3_adc_device = {
	.name    = "k3adc",
	.id    = 0,
	.dev    = {
		.platform_data = &hi6421_adc_tableEx,
		.init_name = "hkadc",
	},
	.num_resources    = 1,
	.resource    =  &k3_adc_resources,
};

static struct platform_device hisik3_device_hwmon = {
	.name		= "k3-hwmon",
	.id		= -1,
};

#ifdef CONFIG_LEDS_K3_6421
/*k3_led begin*/
static struct k3_led_platform_data hi6421_leds = {
	.leds_size = K3_LEDS_MAX,
	.leds = {
		[0] = {
			.name = "red",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
		[1] = {
			.name = "green",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
		[2] {
			.name = "blue",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
	},
};

static struct k3_led_platform_data hi6421_leds_phone = {
	.leds_size = K3_LEDS_MAX,
	.leds = {
		[0] = {
			.name = "green",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
		[1] = {
			.name = "red",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
		[2] {
			.name = "blue",
			.brightness = LED_OFF,
			.delay_on = 0,
			.delay_off = 0,
			.default_trigger = "timer",
		},
	},
};

static struct resource hi6421_led_resources = {
	.start		= REG_BASE_PMUSPI,
	.end			= REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
	.flags		= IORESOURCE_MEM,

};
static struct platform_device hi6421_led_device = {
	.name		= K3_LEDS,
	.id			= 0,
	.dev = {
		.platform_data = &hi6421_leds,
		.init_name = "hkled",
	},
	.num_resources		= 1,
	.resource       =  &hi6421_led_resources,
};
/*k3_led end*/
#endif

#ifdef CONFIG_ANDROID_K3_VIBRATOR
static struct k3_vibrator_platform_data hi6421_vibrator = {
	.low_freq  = PERIOD,
	.low_power = ISET_POWER,
	.mode  = SET_MODE,
	.high_freq = PERIOD_QUICK,
	.high_power = ISET_POWERSTRONG,
};

/*vibrator  begin*/
static struct resource hi6421_vibrator_resources = {
	.start		= REG_BASE_PMUSPI,
	.end		= REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
	.flags		= IORESOURCE_MEM,

};
static struct platform_device hi6421_vibrator_device = {
	.name		= K3_VIBRATOR,
	.id			= 0,
	.dev = {
		.platform_data = &hi6421_vibrator,
		.init_name = "hkvibrator",
	},
	.num_resources		= 1,
	.resource       =  &hi6421_vibrator_resources,
};
#endif

/*vibrator end*/

static struct resource hi6421_irq_resources[] = {
	{
		.start		= REG_BASE_PMUSPI,
		.end		= REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= IRQ_GPIO159,
		.end		= IRQ_GPIO159,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct platform_device hisik3_hi6421_irq_device = {
	.name		= "hi6421-irq",
	.id			= 0,
	.dev.platform_data	= NULL,
	.num_resources		= ARRAY_SIZE(hi6421_irq_resources),
	.resource       =  hi6421_irq_resources,
};

static struct platform_device k3_lcd_device = {
	.name = PLATFORM_DEVICE_LCD_NAME,
	.id	= 1,
	.dev = {
		.init_name = "k3_dev_lcd",
	},
};


/* USB switch device define */
#define CONFIG_SWITCH_USB_TTY_NAME   "/dev/ttyACM0"

#define USB_SWITCH_CONTROL_GPIO     144
#define USB_SWITCH_EN_GPIO          174
#define USB_SWITCH_INTERRUPT_GPIO   99

static struct usb_switch_platform_data usw_plat_data = {
		.name           = "usbsw",
		.usw_ctrl_gpio  = USB_SWITCH_CONTROL_GPIO,
		.usw_en_gpio    = USB_SWITCH_EN_GPIO,
		.usw_int_gpio   = USB_SWITCH_INTERRUPT_GPIO,
		.irq_flags      = IRQ_TYPE_EDGE_RISING,
};

static struct platform_device usb_switch_device = {
	.name   = "switch-usb",
	.dev    = {
		.init_name = "switch-usb",
		.platform_data = &usw_plat_data,
	},
};


static struct resource k3_gps_bcm_resources[] = {
	[0] = {
	.name  = GPIO_GPS_BCM_VBAT_ENABLE_NAME,
	.start = GPIO_GPS_BCM_VBAT_ENABLE,
	.end   = GPIO_GPS_BCM_VBAT_ENABLE,
	.flags = IORESOURCE_IO,
	},
	[1] = {
	.name  = GPIO_GPS_BCM_RESET_NAME,
	.start = GPIO_GPS_BCM_RESET,
	.end   = GPIO_GPS_BCM_RESET,
	.flags = IORESOURCE_IO,
	},
};

static struct platform_device k3_gps_bcm_device = {
	.name = "k3_gps_bcm_47511",
	.id	= 1,
	.dev = {
		.init_name = "gps_bcm_47511",
	},
	.num_resources = ARRAY_SIZE(k3_gps_bcm_resources),
	.resource = k3_gps_bcm_resources,
};

static struct resource bluepower_resources[] = {
	{
		.name	= "bt_gpio_enable",
		.start	= GPIO_BT_EN,
		.end	= GPIO_BT_EN,
		.flags	= IORESOURCE_IO,
	},
	{
		.name	= "bt_gpio_rst",
		.start	= GPIO_BT_RST,
		.end	= GPIO_BT_RST,
		.flags	= IORESOURCE_IO,
	},
};

static struct platform_device btbcm_device = {
	.name =	"bt_power",
	.dev  =	{
		.platform_data = NULL,
		.init_name = REGULATOR_DEV_BLUETOOTH_NAME,
	},
	.id	= -1,
	.num_resources	= ARRAY_SIZE(bluepower_resources),
	.resource	= bluepower_resources,

};

static struct resource bluesleep_resources[] = {
	{
		.name	= "gpio_host_wake",
		.start	= GPIO_HOST_WAKEUP,
		.end	= GPIO_HOST_WAKEUP,
		.flags	= IORESOURCE_IO,
	},
	{
		.name	= "gpio_ext_wake",
		.start	= GPIO_DEV_WAKEUP,
		.end	= GPIO_DEV_WAKEUP,
		.flags	= IORESOURCE_IO,
	},
};

static struct platform_device bcm_bluesleep_device = {
	.name =	"bluesleep",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(bluesleep_resources),
	.resource	= bluesleep_resources,
};
/*  camera resources */
static struct resource hisik3_camera_resources[] = {
	{
		.name		= "isp_base",
		.start		= REG_BASE_ISP,
		.end		= REG_BASE_ISP + REG_ISP_IOSIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.name		= "isp_irq",
		.start		= IRQ_ISP,
		.end		= IRQ_ISP,
		.flags		= IORESOURCE_IRQ,
	},
	{
		.name		= "csi0_irq",
		.start		= IRQ_MIPICSI0,
		.end		= IRQ_MIPICSI0,
		.flags		= IORESOURCE_IRQ,
	},
	{
		.name		= "csi1_irq",
		.start		= IRQ_MIPICSI1,
		.end		= IRQ_MIPICSI1,
		.flags		= IORESOURCE_IRQ,
	}
};

static struct platform_device hisik3_camera_device = {
	.id	= 0,
	.name	= "k3-camera-v4l2",
	.dev = {
		.init_name = "camera",
	},
	.resource	= hisik3_camera_resources,
	.num_resources	= ARRAY_SIZE(hisik3_camera_resources),
};

static struct platform_device hisik3_fake_camera_device = {
	.id	= 1,
	.name	= "k3-fake-camera-v4l2",
	.resource	= 0,
	.num_resources	= 0,
	/*
	.dev = {
		.release = camera_platform_release,
	}
	,*/
};

/* Keypad device and platform data start, use KPC realizing keypad. */
static const uint32_t default_keymap[] = {
	/*row, col, key*/
#if 0
	/* used for truly platform.*/
	KEY(0, 0, KEY_MENU),
	KEY(1, 0, KEY_SEND),
	KEY(2, 0, KEY_VOLUMEUP),
	
	KEY(0, 1, KEY_HOME),
	KEY(1, 1, KEY_END),
	KEY(2, 1, KEY_VOLUMEDOWN),
	
	KEY(0, 2, KEY_CAMERA_FOCUS),
	KEY(1, 2, KEY_CAMERA),
	KEY(2, 2, DPAD_CENTER),
#endif

	/*row, col, key*/
	/* used for debug only.*/
	KEY(0, 0, KEY_MENU),
	KEY(0, 1, KEY_BACK),
        
	KEY(1, 0, KEY_LEFT),
	KEY(1, 1, KEY_RIGHT),
	
	KEY(2, 0, KEY_UP),
	
	KEY(2, 1, KEY_DOWN),
	KEY(2, 2, DPAD_CENTER),
	
	KEY(0, 2, KEY_CAMERA_FOCUS),
	KEY(1, 2, KEY_CAMERA),
	
	/* TODO: add your keys below*/

	/*Used for software function, not physical connection!*/
	
};

static struct matrix_keymap_data hisik3_keymap_data = {
	.keymap = default_keymap,
	.keymap_size = ARRAY_SIZE(default_keymap),
};
static uint16_t long_func_key1[] = {KEY_BACK};
static uint16_t long_func_key2[] = {DPAD_CENTER, KEY_VOLUMEDOWN};

static struct keypad_remap_item remap_items[] = {
	{KEY_HOME, 1, 1000/*ms*/, long_func_key1},
	/*{KEY_A, 2, 500, long_func_key2},*/
	/*TODO: add your remap_item here*/
};

static struct keypad_remap keypad_long_remap = {
	.count = ARRAY_SIZE(remap_items),
	.items = remap_items,
};

static struct resource hisik3_keypad_resources[] = {
	[0] = {
		.start = REG_BASE_KPC,
		.end = REG_BASE_KPC + REG_KPC_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_KPC,
		.end = IRQ_KPC,
		.flags = IORESOURCE_IRQ,
	},
};

static struct k3v2_keypad_platdata hisik3_keypad_platdata = {
	.keymap_data = &hisik3_keymap_data,
	.keypad_remap = &keypad_long_remap,
	.rows = 8,
	.cols = 8,
	.row_shift = 3,
};

static struct platform_device hisik3_keypad_device = {
	.name = "k3_keypad",
	.id = -1,
	.num_resources = ARRAY_SIZE(hisik3_keypad_resources),
	.resource = hisik3_keypad_resources,
	.dev.platform_data = &hisik3_keypad_platdata,
};

/* Keypad device and platform data start, use GPIO realizing keypad. */

static struct resource hisik3_gpio_keypad_resources[] = {
	[0] = {
		.start = REG_BASE_GPIO18,
		.end = REG_BASE_GPIO18 + REG_GPIO18_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_GPIO(GPIO_17_1),
		.end = IRQ_GPIO(GPIO_17_1),
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_GPIO(GPIO_17_2),
		.end = IRQ_GPIO(GPIO_17_2),
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device hisik3_gpio_keypad_device = {
	.name = "k3v2_gpio_key",
	.id = -1,
	.num_resources = ARRAY_SIZE(hisik3_gpio_keypad_resources),
	.resource = hisik3_gpio_keypad_resources,
};

/*power-key*/
static struct resource hisik3_power_key_resources[] = {
	[0] = {
		.start = REG_BASE_PMUSPI,
		.end = REG_BASE_PMUSPI + REG_PMUSPI_IOSIZE - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_POWER_KEY_PRESS,
		.end = IRQ_POWER_KEY_PRESS,
		.flags = IORESOURCE_IRQ,
	},
	[2] = {
		.start = IRQ_POWER_KEY_RELEASE,
		.end = IRQ_POWER_KEY_RELEASE,
		.flags = IORESOURCE_IRQ,
	},
	[3] = {
		.start = IRQ_POWER_KEY_LONG_PRESS_1S,
		.end = IRQ_POWER_KEY_LONG_PRESS_1S,
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device hisik3_power_key_device = {
	.name = "k3v2_power_key",
	.id = -1,
	.num_resources = ARRAY_SIZE(hisik3_power_key_resources),
	.resource = hisik3_power_key_resources,
};

/*watchdog added by s00212129*/
static struct resource  hisik3_watchdog_resources[] = {
	[0] = {
		.start = REG_BASE_WD,
		.end = REG_BASE_WD + REG_WD_IOSIZE -1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = IRQ_WDOG,
		.end   = IRQ_WDOG,
		.flags = IORESOURCE_IRQ,
	},
};

static struct platform_device  hisik3_watchdog_device = {
	.name = "k3v2_watchdog",
	.id = -1,
	.num_resources = ARRAY_SIZE(hisik3_watchdog_resources),
	.resource = hisik3_watchdog_resources,
};
 /*end watchdog*/

/*Keypad backlight*/
static struct platform_device hisik3_keypad_backlight_device = {
	.name = "keyboard-backlight",
};

#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS_RMI4
/* TouchScreen start*/
static struct synaptics_rmi4_platform_data synaptics_ts_platform_data = {
	.irq				= GPIO_19_5,
	.irq_flag			= IRQF_TRIGGER_LOW,
	.flip_flags			= SYNAPTICS_NO_FLIP,
	.x_res				= LCD_X_720P,
	.y_res				= LCD_Y_720P,
	.y_all				= LCD_Y_ALL_720P,
	.fuzz_x				= 0,
	.fuzz_y				= 0,
	.fuzz_p				= 0,
	.fuzz_w				= 0,
	.reset_pin			= GPIO_19_4,
};
#endif

static ssize_t synaptics_virtual_keys_show(struct kobject *kobj,
			       struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf,
		__stringify(EV_KEY) ":" __stringify(KEY_BACK)   ":125:1380:160:90"
		":" __stringify(EV_KEY) ":" __stringify(KEY_HOMEPAGE)   ":360:1380:160:90"
		":" __stringify(EV_KEY) ":" __stringify(KEY_MENU) ":598:1380:160:90"
		"\n");
}

static struct kobj_attribute synaptics_virtual_keys_attr = {
	.attr = {
		.name = "virtualkeys.synaptics",
		.mode = S_IRUGO,
	},
	.show = &synaptics_virtual_keys_show,
};

static struct attribute *synaptics_properties_attrs[] = {
	&synaptics_virtual_keys_attr.attr,
	NULL
};

static struct attribute_group synaptics_properties_attr_group = {
	.attrs = synaptics_properties_attrs,
};
	
static void __init synaptics_virtual_keys_init(void)
{
	struct kobject *properties_kobj;
	int ret = 0;

	properties_kobj = kobject_create_and_add("board_properties", NULL);
	if (properties_kobj)
		ret = sysfs_create_group(properties_kobj,
			&synaptics_properties_attr_group);
	if (!properties_kobj || ret)
		pr_err("%s: failed to create board_properties!\n", __func__);
}
/* TouchScreen end*/

/* Atmel mXT224E Touchscreen start*/
static struct atmel_i2c_platform_data atmel_tp_platform_data = {
	.version = 0x10,
	.source = 0,
	.abs_x_min = 0,
	.abs_x_max = 719,
	.abs_y_min = 0,
	.abs_y_max = 1279,
	.abs_pressure_min = 0,
	/*.abs_pressure_max = 15,*/
	.abs_pressure_max = 255,
	.abs_width_min = 0,
	.abs_width_max = 255,
	/*.abs_area_min = 0,*/
	/*.abs_area_max = 255,*/
	.gpio_irq = GPIO_19_5,
	.gpio_reset = GPIO_19_4,
	.power = NULL,
	.config_T6 = {
		0, 0, 0, 0, 0,
		0
	},
	.config_T7 = {
		32, 255, 10
	},
	.config_T8 = {
		24, 0, 1, 10, 0,
		0, 5, 60, 10, 192
	},
	.config_T9 = {
		143, 0, 0, 19, 11,
		0, 32, 66, 2, 3,
		0, 2, 2, 47, 10,
		15, 22, 10, 106, 5,/*XRANGE = 1386*/
		207, 2, 0, 0, 0,/* YRANGE = 719*/
		0, 161, 40, 183, 64,
		30, 20, 0, 0, 1
	},
	.config_T15 = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0
	},
	.config_T19 = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0
	},
	.config_T23 = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
	},
	.config_T25 = {
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0
	},
	.config_T40 = {
		0, 0, 0, 0, 0
	},
	.config_T42 = {
		0, 40, 40, 80, 128,
		0, 0, 0
	},
	.config_T46 = {
		0, 3, 32, 32, 0,
		0, 0, 0, 0
	},
	.config_T47 = {
		0, 20, 50, 5, 2,
		40, 40, 180, 0, 100
	},
	.config_T48 = {
		1, 4, 10, 0, 0,
		0, 0, 0, 1, 1,
		0, 0, 0, 6, 6,
		0, 0, 63, 6, 64,
		10, 0, 20, 5, 0,
		38, 0, 20, 0, 0,
		0, 0, 0, 0, 0,
		40, 2, 2, 2, 32,
		10, 12, 20, 241, 251,
		0, 0, 191, 40, 183,
		64, 30, 15, 0
	},
	.object_crc = {
		0xFD, 0x3B, 0x8D
	},/*CRC*/
	.cable_config = {
		70, 30, 32, 32
	},
	.cable_config_T7 = {
		32, 16, 25
	},
	.cable_config_T8 = {
		24, 0, 5, 5, 0,
		0, 5, 60, 10, 192
	},
	.cable_config_T9 = {
		139, 0, 0, 19, 11,
		0, 32, 66, 2, 3,
		0, 5, 2, 64, 10,
		12, 20, 10, 106, 5,/*XRANGE = 1386*/
		207, 2, 0, 0, 0,/* YRANGE = 719*/
		0, 161, 40, 183, 64,
		30, 20, 0, 0, 0
	},
	.cable_config_T46 = {
		0, 3, 40, 40, 0,
		0, 0, 0, 0
	},

	.cable_config_T48 = {
		1, 128, 114, 0, 0,
		0, 0, 0, 1, 2,
		0, 0, 0, 6, 6,
		0, 0, 63, 6, 64,
		10, 0, 20, 5, 0,
		38, 0, 20, 0, 0,
		0, 0, 0, 0, 0,
		40, 2, 2, 2, 32,
		10, 12, 20, 241, 251,
		0, 0, 191, 40, 183,
		64, 30, 15, 0
	},
	.noise_config = {
		70, 3, 35
	},
	.filter_level = {
		0, 0, 539, 539
	},
	.GCAF_level = {
		8, 16, 24, 32, 40
	},
	.ATCH_NOR = {
		0, 0, 5, 60, 10,
		192
	},
	.ATCH_NOR_20S = {
		0, 0, 255, 1, 0,
		0
	},
};
/* Atmel mXT224E Touchscreen end*/
#ifdef CONFIG_TOUCHSCREEN_RMI4_SYNAPTICS_GENERIC
struct syna_gpio_data {
    u16 attn_gpio_number;
    u16 reset_gpio_number;
    char* attn_gpio_name;
    char* reset_gpio_name;
};
static int synaptics_touchpad_gpio_setup(void *gpio_data, bool configure)
{
    int retval=0;
    struct syna_gpio_data *data = gpio_data;
    if (configure) {
        retval = gpio_request(data->attn_gpio_number, "rmi4_attn");
        if (retval) {
            pr_err("%s: Failed to get attn gpio %d. Code: %d.",
                   __func__, data->attn_gpio_number, retval);
            return retval;
        }
        retval = gpio_direction_input(data->attn_gpio_number);
        if (retval) {
            pr_err("%s: Failed to setup attn gpio %d. Code: %d.",
                   __func__, data->attn_gpio_number, retval);
            gpio_free(data->attn_gpio_number);
        }
        retval = gpio_request(data->reset_gpio_number, "rmi4_reset");
        if (retval) {
            pr_err("%s: Failed to get reset gpio %d. Code: %d.",
                   __func__, data->reset_gpio_number, retval);
            return retval;
        }
        retval = gpio_direction_output(data->reset_gpio_number,0);
        if (retval) {
            pr_err("%s: Failed to setup reset gpio %d. Code: %d.",
                   __func__, data->reset_gpio_number, retval);
            gpio_free(data->reset_gpio_number);
        }
        msleep (10);
        retval = gpio_direction_output(data->reset_gpio_number,1);
        if (retval) {
            pr_err("%s: Failed to setup reset gpio %d. Code: %d.",
                   __func__, data->reset_gpio_number, retval);
            gpio_free(data->reset_gpio_number);
        }
        msleep(10);
    } else {
	gpio_free(data->attn_gpio_number);
	gpio_free(data->reset_gpio_number);
        pr_warn("%s: No way to deconfigure gpio %d and %d.",
               __func__, data->attn_gpio_number,data->reset_gpio_number);
    }
    return retval;
};
static struct syna_gpio_data rmi4_gpiodata = {
	    .attn_gpio_number = TOUCH_INT_PIN,
	    .reset_gpio_number = TOUCH_RESET_PIN,
	    .attn_gpio_name = "rmi4_attn",
	    .reset_gpio_name = "rmi4_reset",
	};
static struct rmi_device_platform_data syna_platformdata ={
    .driver_name = "rmi_generic",
    .sensor_name = "RMI4",
    .attn_gpio = TOUCH_INT_PIN,
#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS2202
    .enable_gpio = ENABLE_GPIO,
#endif
    .attn_polarity = 0,
    .gpio_data = &rmi4_gpiodata,
    .gpio_config = synaptics_touchpad_gpio_setup,
    .reset_delay_ms = 100,
#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS2202
    .axis_align = {
    .flip_x = false,
    .flip_y = false,},
#else
    .axis_align = {
    .flip_x = true,
    .flip_y = true,},
#endif
};
#endif



/* Audience */

static struct es305_platform_data audience_platform_data = {
	.gpio_es305_wakeup  = GPIO_16_0,/* 128 */
	.gpio_es305_reset   = GPIO_18_1,/* 145 */
};

/* TPA2028_SPK_L */
static struct tpa2028_l_platform_data tpa2028_l_pdata = {
	.gpio_tpa2028_en    = GPIO_14_5,/* 117 */
};

/* TPA2028_SPK_R */
static struct tpa2028_r_platform_data tpa2028_r_pdata = {
    //.gpio_tpa2028_en    = GPIO_14_5,/* 117 */
};

/* TPA6132 */
static struct tpa6132_platform_data tpa6132_pdata = {
	.gpio_tpa6132_en    = GPIO_14_6,/* 118 */
};

static struct platform_device tpa6132_device = {
	.name    = TPA6132_NAME,
	.id      = 0,
	.dev     = {
		.platform_data = &tpa6132_pdata,
	},
};

#ifdef CONFIG_HIK3_CAMERA_FLASH
static struct tps61310_platform_data tps61310_platform_data = 
{
	.reset_pin			= GPIO_9_4,
	.strobe0			= GPIO_8_1,
	.strobe1			= GPIO_8_2,
};
#endif

static struct platform_device boardid_dev ={
    .name    = "boardid_dev",
    .id      = 0,
};

/* please add i2c bus 0 devices here */
static struct i2c_board_info hisik3_i2c_bus0_devs[]= {
	/*TODO: add your device here*/
	/* TPA2028 FOR SPEAKER LEFT */
	[0] =   {
		.type			= TPA2028_L_NAME,
		.addr			= TPA2028_I2C_ADDR,
		.flags 			= true,
		.platform_data 	= &tpa2028_l_pdata,
	},
	
	/* camera tps61310 light */
#ifdef CONFIG_HIK3_CAMERA_FLASH	
	[1]	=	{
		.type			= K3_FLASH_NAME, 
		.addr			= K3_FLASH_I2C_ADDR,
		.platform_data		= &tps61310_platform_data,
	},
#endif	
};

static int hi6421_batt_table[] = {
	/* adc code for temperature in degree C */
	929, 925, /* -2 ,-1 */
	920, 917, 912, 908, 904, 899, 895, 890, 885, 880, /* 00 - 09 */
	875, 869, 864, 858, 853, 847, 841, 835, 829, 823, /* 10 - 19 */
	816, 810, 804, 797, 790, 783, 776, 769, 762, 755, /* 20 - 29 */
	748, 740, 732, 725, 718, 710, 703, 695, 687, 679, /* 30 - 39 */
	671, 663, 655, 647, 639, 631, 623, 615, 607, 599, /* 40 - 49 */
	591, 583, 575, 567, 559, 551, 543, 535, 527, 519, /* 50 - 59 */
	511, 504, 496 /* 60 - 62 */
};

static struct k3_battery_monitor_platform_data hi6421_bci_data = {
	.termination_currentmA		=CIN_LIMIT_100,
	.monitoring_interval		= MONITOR_TIME,
	.max_charger_currentmA		= HIGH_CURRENT,
	.max_charger_voltagemV		= HIGH_VOL,
	.max_bat_voltagemV		= BAT_FULL_VOL,
	.low_bat_voltagemV		= BAT_SLOW_VOL,
	.battery_tmp_tbl		= hi6421_batt_table,
	.tblsize			= ARRAY_SIZE(hi6421_batt_table),
};

static struct resource hisik3_battery_resources[] = {
	[0] = {
		.start  = IRQ_VBATLOW_RISING,
		.name   = NULL,
		.flags  = IORESOURCE_IRQ,
	} ,
};

static struct platform_device hisik3_battery_monitor = {
	.name	= "k3_battery_monitor",
	.id	= 1,
	.resource	= hisik3_battery_resources,
	.num_resources	= ARRAY_SIZE(hisik3_battery_resources),
	.dev = {
		.platform_data	= &hi6421_bci_data,
	},
};

static struct k3_bq24161_platform_data k3_bq24161_data = 
{
	.max_charger_currentmA = 1000,
	.max_charger_voltagemV = 4200,
	.gpio = BQ24161_GPIO_074,
};
static struct mhl_platform_data k3_mhl_data =
{
	.gpio_reset 	= MHL_GPIO_RESET,
	.gpio_wake_up	= MHL_GPIO_WAKE_UP,
	.gpio_int	= MHL_GPIO_INT,
#ifdef CONFIG_MHL_USB_SHARE
	.gpio_switch_1	= MHL_GPIO_SWITCH_1,
	.gpio_switch_2	= MHL_GPIO_SWITCH_2,
#endif
	.gpio_dcdc	= MHL_GPIO_DCDC_MODE,
};
/* please add i2c bus 1 devices here */
static struct i2c_board_info hisik3_i2c_bus1_devs[]= {
	[0]	=	{
		.type			= "k3_bq24161_charger",
		.addr			= I2C_ADDR_BQ24161,
		.platform_data 	= &k3_bq24161_data,
		.irq				= GPIO_0_5,
	},
	[1]	=	{
		.type			= "bq27510-battery",
		.addr			= I2C_ADDR_BQ27510,
		.platform_data 	= NULL,
		.irq				= GPIO_21_2,
	},
/*	[3]	=	{
        .type			= ES305_NAME,
		.addr			= 0x3E,
		.flags 			= true,
		.platform_data 	= &audience_platform_data,
	},*/
	/* Atmel mXT224E touchscreen*/
	[3] = 	{
		.type			= ATMEL_MXT224E_NAME,
		.addr			= 0x4A,
		.platform_data	= &atmel_tp_platform_data,
	},
	[4]	=	{
		.type			= "mhl_Sii9244_page0",
		.addr			= MHL_SII9244_PAGE0_ADDR,
		.platform_data 		= &k3_mhl_data,
	},
	[5]	=	{
		.type			= "mhl_Sii9244_page1",
	.addr			= MHL_SII9244_PAGE1_ADDR,
		.platform_data 		= NULL,
	},
	[6]	=	{
		.type			= "mhl_Sii9244_page2",
		.addr			= MHL_SII9244_PAGE2_ADDR,
		.platform_data 		= NULL,
	},
	[7]	=	{
		.type			= "mhl_Sii9244_cbus",
		.addr			= MHL_SII9244_CBUS_ADDR,
		.platform_data 		= NULL,
	},
	/* TPA2028 FOR SPEAKER RIGHT */
	[8] =   {
		.type			= TPA2028_R_NAME,
		.addr			= TPA2028_I2C_ADDR,
		.flags 			= true,
		.platform_data 	= &tpa2028_r_pdata,
	},
	/*TODO: add your device here*/
};

static struct i2c_board_info hisik3_i2c1_tp_devs[]= {
	/* Atmel mXT224E touchscreen*/
	[0] = 	{
		.type			= ATMEL_MXT224E_NAME,
		.addr			= 0x4A,
		.platform_data	= &atmel_tp_platform_data,
	},
	/*TODO: add your device here*/
#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS_RMI4
	/* Synaptics Touchscreen*/
	[1] = {
		.type		= SYNAPTICS_RMI4_NAME,
		.addr		= SYNAPTICS_RMI4_I2C_ADDR,
		/* Multi-touch support*/
		.flags 		= true,
		.platform_data 	= &synaptics_ts_platform_data,
	},
#endif
};

static struct i2c_board_info hisik3_i2c_bus3_devs[]= {
	[0]	=	{
        .type			= ES305_NAME,
		.addr			= 0x3E,
		.flags 			= true,
		.platform_data 	= &audience_platform_data,
	},
	/*TODO: add your device here*/
};

static struct i2c_board_info hisik3_i2c2_tp_devs[]= {
	/* Atmel mXT224E touchscreen*/
	[0] = 	{
		.type			= ATMEL_MXT224E_NAME,
		.addr			= 0x4A,
		.platform_data	= &atmel_tp_platform_data,
	},
	/*TODO: add your device here*/
#ifdef CONFIG_TOUCHSCREEN_RMI4_SYNAPTICS_GENERIC
	/*Synaptics Touchscreen*/
	[1] = {
		.type			= SYNA_NAME,
		.addr			= 0x70,
		.flags 			= true,
		.platform_data	= &syna_platformdata,
	},
#else
	#ifdef CONFIG_TOUCH_INPUT_SYNAPTICS_RMI4
	/* Synaptics Touchscreen*/
	[1] = {
		.type		= SYNAPTICS_RMI4_NAME,
		.addr		= SYNAPTICS_RMI4_I2C_ADDR,
		/* Multi-touch support*/
		.flags 		= true,
		.platform_data 	= &synaptics_ts_platform_data,
	},
	#endif
#endif
};

/* please add platform device in the struct.*/
static struct platform_device *k3v2oem1_public_dev[] __initdata = {
	&hisik3_hi6421_irq_device,
	&hisik3_adc_device,
#ifdef CONFIG_LEDS_K3_6421	
	&hi6421_led_device,
#endif

#ifdef CONFIG_ANDROID_K3_VIBRATOR	
	&hi6421_vibrator_device,
#endif
	&hisik3_camera_device,
	&hisik3_fake_camera_device,
	&hisik3_device_hwmon,
	&hisik3_keypad_device,
	&hisik3_keypad_backlight_device,
	&k3_lcd_device, 
	&k3_gps_bcm_device, 
	&hisik3_battery_monitor,
	/*&btbcm_device,*/
	/*&bcm_bluesleep_device,*/
	&hisik3_power_key_device,
	&tpa6132_device,
	&usb_switch_device,
	&boardid_dev,
	&hisik3_watchdog_device,
};

static void k3v2_i2c_devices_init(void)
{
	/* Register devices on I2C Bus0 and Bus1*/
	i2c_register_board_info(0, hisik3_i2c_bus0_devs,
					ARRAY_SIZE(hisik3_i2c_bus0_devs));
	i2c_register_board_info(1, hisik3_i2c_bus1_devs,
					ARRAY_SIZE(hisik3_i2c_bus1_devs));
	i2c_register_board_info(3, hisik3_i2c_bus3_devs,
					ARRAY_SIZE(hisik3_i2c_bus3_devs));

	/*Some board, TP is register on I2C1,but some on I2C2,so register both*/
	i2c_register_board_info(1, hisik3_i2c1_tp_devs,
					ARRAY_SIZE(hisik3_i2c1_tp_devs));
	i2c_register_board_info(2, hisik3_i2c2_tp_devs,
					ARRAY_SIZE(hisik3_i2c2_tp_devs));
}


static void __init k3v2oem1_init(void)
{
	unsigned int  index = 0;
	unsigned int  board_type;

	edb_trace(1);
	k3v2_common_init();
	/* 
	 * providing two ways of realizing keypad, one is KPC, the other is GPIO.
	 * depending on current boardid, use corresponding register device.
	 * boardid=0 means board, choose hisik3_keypad_device which is realized by KPC.
	 * boardid=1 means phone, choose hisi_gpiokeypad_device which is realized by GPIO.
	 */
	board_type = get_board_type();
	switch (board_type) {
	case E_BOARD_TYPE_U9510:
#ifdef CONFIG_LEDS_K3_6421
		hi6421_led_device.dev.platform_data = &hi6421_leds_phone;
#endif
		for( index =0; index <  ARRAY_SIZE(k3v2oem1_public_dev); index++ ) {
			if ( (struct platform_device *)(&hisik3_keypad_device) == (struct platform_device *)(k3v2oem1_public_dev[index]) ) {
				k3v2oem1_public_dev[index] = &hisik3_gpio_keypad_device;
				break;
			}
		}
		break;
	case E_BOARD_TYPE_PLATFORM:
		break;
	default:
		break;
	}
	platform_add_devices(k3v2oem1_public_dev, ARRAY_SIZE(k3v2oem1_public_dev));

	k3v2_i2c_devices_init();
	synaptics_virtual_keys_init();

#ifdef CONFIG_DEBUG_FS
	config_debugfs_init();
#endif
}

static void __init k3v2_early_init(void)
{
	int chip_id = 0;
	k3v2_init_clock();
	chip_id = get_chipid();
	if (chip_id == CS_CHIP_ID) {
		k3v2_clk_init_from_table(common_clk_init_table_cs);
	} else if (chip_id == DI_CHIP_ID) {
		k3v2_clk_init_from_table(common_clk_init_table_es);
	}
}

#if 0
static void k3v2_mem_setup(void)
{
	unsigned long reserved_size;

	printk(KERN_INFO "k3v2_mem_setup\n");

	/*
	   Memory reserved for Graphic/ Dcode/EnCode
	*/
	reserved_size = hisi_get_reserve_mem_size();

	/*
	 * Memory configuration with SPARSEMEM enabled on  (see
	 * asm/mach/memory.h for more information).
	 */
	arm_add_memory(PLAT_PHYS_OFFSET, (HISI_BASE_MEMORY_SIZE - reserved_size));

	return;
}

/*
 * k3v2_mem=size1@start1[,size2@start2][,...]
 * size means memory size which larger than 512M
 */
static int __init early_k3v2_mem(char *p)
{
	unsigned long size;
	phys_addr_t start;
	char *endp = NULL;
	char *ep = NULL;

	k3v2_mem_setup();

	printk(KERN_INFO "k3v2_mem = %s\n", p);

	start = PLAT_PHYS_OFFSET + HISI_BASE_MEMORY_SIZE;
	while (*p != '\0') {
		size  = memparse(p, &endp);
		if (*endp == '@')
			start = memparse(endp + 1, &ep);

		/* oem ec1 1G memory based */
		if ((start == SZ_512M)) {
			if (size < SZ_512M)
				size = 0;
			else
				size -= SZ_512M;
		}

		arm_add_memory(start, size);

		printk(KERN_INFO "early_k3v2_mem start 0x%x size 0x%lx\n", start, size);

		if (*ep == ',')
			p = ep + 1;
		else
			break;

		printk(KERN_INFO "k3v2_mem = %s\n", p);
	}

	return 0;
}
early_param("k3v2_mem", early_k3v2_mem);
#endif

static void __init k3v2_map_io(void)
{
	printk("k3v2oem1 map io\n");
	k3v2_map_common_io();
}

//qijiwen reserve memory for  Graphic/ Dcode/EnCode etc.
#include <linux/memblock.h>
static void k3v2_reserve(void)
{
	unsigned long reserved_size;
	phys_addr_t base;
	/*
	   Memory reserved for Graphic/ Dcode/EnCode
	*/
	reserved_size = hisi_get_reserve_mem_size();

	base = PLAT_PHYS_OFFSET + HISI_BASE_MEMORY_SIZE - reserved_size;

	printk(KERN_INFO "%s the reserved memor region base:0x%08lx size:0x%08lx\n", __func__, base, reserved_size);

	memblock_remove(base, reserved_size);
}

MACHINE_START(K3V2OEM1, "k3v2oem1")
	.boot_params	= PLAT_PHYS_OFFSET + 0x00000100,
	.init_irq       = k3v2_gic_init_irq,
	.init_machine   = k3v2oem1_init,
	.map_io         = k3v2_map_io,
	.timer          = &k3v2_timer,
	.init_early 	= k3v2_early_init,
	.reserve	    = k3v2_reserve, 
MACHINE_END

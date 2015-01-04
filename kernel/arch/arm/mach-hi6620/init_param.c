/*
 * arch/arm/mach-k3v2/common.c
 *
 * Copyright (C) 2011 Hisilicon Co. Ltd.
 *
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
#include <linux/amba/bus.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <asm/hardware/cache-l2x0.h>
#include <asm/system.h>
#include <asm/pmu.h>
#include <asm/setup.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/lm.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <linux/amba/pl061.h>
#include <mach/early-debug.h>
#include <mach/mmc.h>
#include <mach/dma.h>
#include <linux/amba/serial.h>
#include <linux/i2c/designware.h>
#include <linux/amba/pl022.h>
#include <linux/spi/spi.h>
#include <linux/mux.h>
#include <linux/delay.h>
#include <mach/boardid.h>
#include <hsad/config_mgr.h>
#include <mach/hisi_mem.h>
#include <mach/ddr_map.h>

#define FULLHD_STRING_MAX 1

unsigned int g_ddr_size = SZ_2G;

static int __init early_get_memsize(char *p)
{
	unsigned int size = SZ_2G;
	char *endp = NULL;

	printk(KERN_ERR "mem_size = %s\n", p);

	while (*p != '\0') {
		size  = memparse(p, &endp);
		printk(KERN_INFO "size = 0x%x\n", size);
		if (*endp == ',') {
			p = endp + 1;
        } else {
			break;
        }
	}
	g_ddr_size = size;

	return 0;
}
early_param("mem_size", early_get_memsize);

static void __init plat_mem_setup(void)
{
	printk(KERN_INFO "plat_mem_setup\n");

	/*
	 * Memory configuration with SPARSEMEM enabled on  (see
	 * asm/mach/memory.h for more information).
	 */

	arm_add_memory(PLAT_PHYS_OFFSET, (g_ddr_size - PLAT_PHYS_OFFSET));

	return;
}

/*
 * k3v2_mem=size1@start1[,size2@start2][,...]
 * size means memory size which larger than 512M
 */
static int __init early_mem_param(char *__unused)
{
	plat_mem_setup();

	return 0;
}
early_param("k3v2mem", early_mem_param);




#define SHIFT_1M 20 /*1M ÄÚ´æµ¥Î»Æ«ÒÆ*/
#define SHIFT_1G 30

#define print_mem_map(string, section)\
printk(KERN_INFO "[%18s] : phy %08x ~ %08x size %dMB\n", string,  (unsigned int)section##_ADDR,\
	((unsigned int)section##_ADDR + section##_SIZE),  section##_SIZE>>SHIFT_1M);

static void __init plat_mem_print(void)
{
    printk("memory section dump :\n");
	print_mem_map("modem system", MODEM_SYS_MEM);
	print_mem_map("hifi system", HIFI_SYS_MEM);
	print_mem_map("mcu system", MCU_SYS_MEM);
	print_mem_map("gu reserved memory", GU_RESERVED_MEM);
	print_mem_map("lps reserved memory", LPS_RESERVED_MEM);
	print_mem_map("ipc share", IPC_SHARE_MEM);
	print_mem_map("modem dump log", MODEM_DUMP_LOG);
	print_mem_map("mcu share mem", MCU_SHARE_MEM);
	print_mem_map("android dump log", ANDROID_DUMP_LOG);
	print_mem_map("fastboot system", FASTBOOT_SYS_MEM);  /*add*/
	print_mem_map("android system", ANDROID_SYS_MEM);

	return;
}

#define check_mem_map(string, section)\
do{\
	if (section##_ADDR != current_offset){\
		printk(KERN_ERR "memory map check error : section [%s]  phy %x current offset %x \n", \
			string, (unsigned int)section##_ADDR, current_offset );\
		panic("memory map check error");\
	}\
	current_offset += section##_SIZE;\
}while(0);

static unsigned int __init plat_get_mem_size(void)
{
    return g_ddr_size;

}

static void __init plat_mem_check(void)
{
	unsigned int current_offset = 0;
    unsigned int total_size = plat_get_mem_size();

	check_mem_map("modem system", MODEM_SYS_MEM);
	check_mem_map("hifi system", HIFI_SYS_MEM);
	check_mem_map("mcu system", MCU_SYS_MEM);
	check_mem_map("gu reserved memory", GU_RESERVED_MEM);
	check_mem_map("lps reserved memory", LPS_RESERVED_MEM);
	check_mem_map("ipc share", IPC_SHARE_MEM);
	check_mem_map("modem dump log", MODEM_DUMP_LOG);
	check_mem_map("mcu share mem", MCU_SHARE_MEM);
	check_mem_map("android dump log", ANDROID_DUMP_LOG);
	check_mem_map("fastboot system", FASTBOOT_SYS_MEM);  /*add*/
    current_offset += g_ddr_size - PLAT_PHYS_OFFSET; /*android mem detect*/

	/*SFT total memory size*/
	if (current_offset != total_size){
		printk(KERN_ERR "###################################\n");
		printk(KERN_ERR "Memory MAP Check total size error !\n");
		printk(KERN_ERR "Total   Size 0x%08x\n",total_size);
		printk(KERN_ERR "Current Size 0x%08x\n",current_offset);
		printk(KERN_ERR "###################################\n");

		panic("memory check total size error");
	}

	return;
}

static int __init  mem_check(void)
{
	plat_mem_print();

	plat_mem_check();

	return 0;
}

late_initcall(mem_check);


int get_isfullhd(void)
{
    int isfullhd = 0;
    int ret = 0;

    ret = get_hw_config_int("lcd/resolution_type", &isfullhd, NULL);
    if (!ret) {
        isfullhd = 0;
        printk(KERN_ERR "get lcd type from hw_config fail\n");
    }

    printk(KERN_INFO "resolution_type is [%d]\n",isfullhd);

    return isfullhd;
}
EXPORT_SYMBOL(get_isfullhd);

static unsigned char g_tp_color_value;
static int __init get_tp_color_setup(char *val)
{
	if (val) {
		g_tp_color_value = simple_strtol(val, NULL, 0);
	}
    return 0;
}

early_param("tp_color", get_tp_color_setup);

unsigned char get_tp_color(void)
{
    return g_tp_color_value;
}
EXPORT_SYMBOL(get_tp_color);

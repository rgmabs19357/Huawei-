/*
 * Decoder device driver (kernel module)
 *
 * Copyright (C) 2012 Google Finland Oy.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>
/* needed for __init,__exit directives */
#include <linux/init.h>
/* needed for remap_pfn_range
    SetPageReserved
    ClearPageReserved
*/
#include <linux/mm.h>
/* obviously, for kmalloc */
#include <linux/slab.h>
/* for struct file_operations, register_chrdev() */
#include <linux/fs.h>
/* standard error codes */
#include <linux/errno.h>

#include <linux/moduleparam.h>
/* request_irq(), free_irq() */
#include <linux/interrupt.h>

/* needed for virt_to_phys() */
#include <linux/io.h>
#include <linux/pci.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>
#include <linux/sched.h>
#include <asm/irq.h>
#include <linux/platform_device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/hisi_ion.h>

#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/hardware.h>
#include <mach/early-debug.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include <linux/pm_qos_params.h>

/* B050底软提供接口文件 */
#include <mach/clk_name_interface.h>
#include "drv_regulator_user.h"
#include "reg_ops.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_ao_sctrl_interface.h"
#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/string.h>
#endif

/* our own stuff */
#include "hx170dec.h"
#include "mach/hisi_mem.h"

/* add for video mntn, modifier: w00228831, begin */
#include "video_mntn_kernel.h"
/* add for video mntn, modifier: w00228831, end */

#include <hsad/config_mgr.h>
#ifdef __KERNEL__
#define DECODER_CLOCK               CONFIG_G1_DEC_CLK
#define DECODER_WAIT_TIMEOUT_COEFF  CONFIG_G1_DEC_WAIT_TIMEOUT_COEFF
#endif

#ifndef DECODER_CLOCK
#define DECODER_CLOCK               200000000
#endif

#ifndef DECODER_WAIT_TIMEOUT_COEFF
#define DECODER_WAIT_TIMEOUT_COEFF  1
#endif



/* Decoder interrupt register */
#define X170_INTERRUPT_REGISTER_DEC (1*4)
#define X170_INTERRUPT_REGISTER_PP (60*4)

#define HX_DEC_INTERRUPT_BIT        0x100
#define HX_PP_INTERRUPT_BIT         0x100

/* dump SCCTRL/AO_SCCTRL/PMCTRL reg about dec power on/off,
   rst en/dis and clk en/dis, 2013/05/06 */
//#define DUMP_SCCTRL_DEC_REG

#ifdef CONFIG_DEBUG_FS
#define VDEC_DEBUGFS_DIR_NAME           "mit2vdec"
#define VDEC_DEBUGFS_PWDN_FILE_NAME     "pwdn"
#endif

static const int DecHwId[] = { 0x8190, 0x8170, 0x9170, 0x9190, 0x6731 };

static u32 hx_pp_instance;
static u32 hx_dec_instance;

/* and this is our MAJOR; use 0 for dynamic allocation (recommended)*/
static int hx170dec_major;

/* here's all the must remember stuff */
typedef struct {
	char *buffer;
	unsigned long iobaseaddr;
	unsigned int iosize;
	volatile u8 *hwregs;
	int open_count;
	unsigned int irq;
	unsigned int done;
	wait_queue_head_t dec_queue;
	struct semaphore busy_lock;
	struct fasync_struct *async_queue_dec;
	struct fasync_struct *async_queue_pp;
	struct cdev cdev;
	struct device dev;
	struct clk *clock;
	struct regulator *reg;
	struct pm_qos_request_list qos_req_cpu_int_latency;
} hx170dec_t;

/* B050 VDEC时钟 */
typedef struct
{
	struct clk *s_src_clk;
	struct clk *s_x2x_clk;
	struct clk *s_p2p_clk;
	struct clk *s_vdec_clk;

	unsigned int src_clk   : 1;
	unsigned int x2x_clk   : 1;
	unsigned int p2p_clk   : 1;
	unsigned int vdec_clk  : 1;
	unsigned int reserve   : 28;
} vdec_clk;

static vdec_clk s_vdec_clk;


static hx170dec_t hx170dec_data;    /* dynamic allocation? */

static u32 vdec_dbgfs_pwdncfg = 1;
static u32 vdec_pwdn_status = 0;

static int ReserveIO(void);
static void ReleaseIO(void);
static void ResetAsic(hx170dec_t *dev);

#ifdef HX170DEC_DEBUG
static void dump_regs(unsigned long data);
#endif

/* IRQ handler */
static irqreturn_t hx170dec_isr(int irq, void *dev_id);


#ifdef DUMP_SCCTRL_DEC_REG
/***********************************************************************************
* Function:       dump_scctrl_dec_reg
* Description:    dump SCCTRL/AO_SCCTRL/PMCTRL register about dec power on/off,
                  rst en/dis and clk en/dis.
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
void dump_scctrl_dec_reg(void)
{
    unsigned int reg_value;

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_MTCMOS_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_RST_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_ISO_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_CLK_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_RSTSTAT7_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_RSTSTAT7 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT12_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT12 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT10_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT10 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT8_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT8 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_CLKCFG8BIT8 = 0x%0x,\n", __func__, reg_value);
}
#endif

/*------------------------------------------------------------------------------
    Function name   : hx170dec_ioctl
    Description     : communication method to/from the user space

    Return type     : int
------------------------------------------------------------------------------*/

static long hx170dec_ioctl(struct file *filp,
                           unsigned int cmd, unsigned long arg)
{
	int err = 0;


	/*PDEBUG("ioctl cmd 0x%08ux\n", cmd); */
	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != HX170DEC_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > HX170DEC_IOC_MAXNR)
		return -ENOTTY;

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
	if (err)
		return -EFAULT;

	switch (cmd) {
		case HX170DEC_IOC_CLI:
			disable_irq(hx170dec_data.irq);
			break;

		case HX170DEC_IOC_STI:
			enable_irq(hx170dec_data.irq);
			break;
		case HX170DEC_IOCGHWOFFSET:
			__put_user(hx170dec_data.iobaseaddr, (unsigned long *)arg);
			break;
		case HX170DEC_IOCGHWIOSIZE:
			__put_user(hx170dec_data.iosize, (unsigned int *)arg);
			break;
		case HX170DEC_PP_INSTANCE:
			filp->private_data = &hx_pp_instance;
			break;
		case HX170DEC_IOC_WAIT_DONE:

			/* timeout: arg second */

            if (!wait_event_interruptible_timeout(hx170dec_data.dec_queue,
                                                  hx170dec_data.done,
                                                  arg*HZ*DECODER_WAIT_TIMEOUT_COEFF)) {


				printk(KERN_INFO "hx170dec:wait event timeout\n");
				return -ETIME;
			} else if (signal_pending(current)) {
				printk(KERN_INFO "hx170dec:signal pending\n");
				hx170dec_data.done = 0;

				return -ERESTARTSYS;
			}

			hx170dec_data.done = 0;
			break;

		case HX170DEC_IOC_CLOCK_ON:
#if 0
			ret = regulator_enable(hx170dec_data.reg);
			if ( ret ) {
				printk(KERN_ERR "hx170dec: regulator_enable failed\n");
			}


			ret = clk_enable(hx170dec_data.clock);
			if ( ret ) {
				printk(KERN_ERR "hx170dec: clk_enable failed\n");
			}
#endif
			break;

		case HX170DEC_IOC_CLOCK_OFF:
#if 0
			clk_disable(hx170dec_data.clock);
			regulator_disable(hx170dec_data.reg);
#endif
			break;

		case HX170DEC_IOCHARDRESET:
			/*
			 * reset the counter to 1, to allow unloading in case
			 * of problems. Use 1, not 0, because the invoking
			 * process has the device open.
			 */
			module_put(THIS_MODULE);
			break;
		default:
			break;
	}
	return 0;
}

/*------------------------------------------------------------------------------
    Function name   : hx170dec_open
    Description     : open method

    Return type     : int
------------------------------------------------------------------------------*/
static int hx170dec_open(struct inode *inode, struct file *filp)
{
	int ret = 0;

    ret = down_interruptible(&(hx170dec_data.busy_lock));
	if (0 != ret) {
		printk(KERN_ERR "hx170dec_error: hx170dec_open down_interruptible failed\n");
		return -EINTR;
	}

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec:enter hx170dec_open()");

    if (hx170dec_data.open_count > 0) {
        mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG,
                       "hx170dec:don't need to open device, the open count is %d", hx170dec_data.open_count);
        filp->private_data = &hx_dec_instance;
        hx170dec_data.open_count++;
        up(&(hx170dec_data.busy_lock));
        return 0;
    }

    if (0 == vdec_pwdn_status) {
    	/* 配置VDEC下电区 */
        ret = vdec_regulator_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx170dec_error: hx170dec_open regulator_enable failed\n");
            up(&(hx170dec_data.busy_lock));
    		return -EIO;
    	}

    	/* 配置VDEC工作时钟域解复位 */
        vdec_clk_rstdisable();

        /* 配置VDEC总线桥、VDEC IP时钟使能,配置VDEC工作时钟分频比 */
        ret = vdec_clk_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx170dec_error: hx170dec_open clk_enable failed\n");
    		vdec_regulator_disable();
            up(&(hx170dec_data.busy_lock));
    		return -EIO;
    	}

        vdec_pwdn_status = 1;
    }
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec_open: vdec debugfs pwdn config = %d, vdec pwdn status = %d", vdec_dbgfs_pwdncfg, vdec_pwdn_status);

#ifdef DUMP_SCCTRL_DEC_REG
    dump_scctrl_dec_reg();
#endif

	hx170dec_data.open_count++;

	filp->private_data = &hx_dec_instance;

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec: hx170dec_open open_count = %d", hx170dec_data.open_count);

    //mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_INFO, "hx170dec:dev opened.");

    pm_qos_add_request(&hx170dec_data.qos_req_cpu_int_latency, PM_QOS_CPU_INT_LATENCY, 0);
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "%s, req cpu int latency for cpu idle.", __func__);

	up(&(hx170dec_data.busy_lock));

	return 0;
}

/*------------------------------------------------------------------------------
    Function name   : hx170dec_fasync
    Description     : Method for signing up for a interrupt

    Return type     : int
------------------------------------------------------------------------------*/

static int hx170dec_fasync(int fd, struct file *filp, int mode)
{

	hx170dec_t *dev = &hx170dec_data;

	/*PDEBUG("dec %x pp %x this %x\n",
	 * &hx_dec_instance,
	 * &hx_pp_instance,
	 * (u32 *)filp->private_data); */

	/* select which interrupt this instance will sign up for */

	if (((u32 *) filp->private_data) == &hx_dec_instance) {
		/* decoder interrupt */
		printk(KERN_INFO "hx170dec:decoder fasync called %d %x %d %x\n",
		       fd, (u32) filp, mode, (u32)&dev->async_queue_dec);
		return fasync_helper(fd, filp, mode, &dev->async_queue_dec);
	} else {
		/* pp interrupt */
		printk(KERN_INFO "hx170dec:pp fasync called %d %x %d %x\n",
		       fd, (u32) filp, mode, (u32)&dev->async_queue_dec);
		return fasync_helper(fd, filp, mode, &dev->async_queue_pp);
	}
}

/*------------------------------------------------------------------------------
    Function name   : hx170dec_release
    Description     : Release driver

    Return type     : int
------------------------------------------------------------------------------*/

static int hx170dec_release(struct inode *inode, struct file *filp)
{
    int ret = 0;

    ret = down_interruptible(&(hx170dec_data.busy_lock));
	if (0 != ret)
	{
        printk("hx170dec_error: hx170dec_release down_interruptible() failed.\n");
		return -EINTR;
	}

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec:enter hx170dec_release()");

    hx170dec_data.open_count--;

    if (hx170dec_data.open_count >0)
    {
        mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG,
                       "hx170dec: can't close device, the open count is %d", hx170dec_data.open_count);
        up(&(hx170dec_data.busy_lock));
        return 0;
    }

	/* remove this filp from the asynchronusly notified filp's */
	/* hx170dec_fasync(-1, filp, 0); */

	hx170dec_data.done = 0;
    //mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_INFO, "hx170dec:dev closed");

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG,
                   "hx170dec: hx170dec_release open_count = %d",hx170dec_data.open_count);

    pm_qos_remove_request(&hx170dec_data.qos_req_cpu_int_latency);
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "%s, remove cpu int latency for cpu idle.", __func__);

    if (0 != vdec_dbgfs_pwdncfg) {
        /* 配置VDEC IP、VDEC总线桥时钟关闭 */
    	vdec_clk_disable();

    	/* 配置VDEC下电区掉电 */
    	vdec_regulator_disable();

        vdec_pwdn_status = 0;
    }
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG,
        "hx170dec_release: vdec debugfs pwdn config = %d, vdec pwdn status = %d", vdec_dbgfs_pwdncfg, vdec_pwdn_status);

#ifdef DUMP_SCCTRL_DEC_REG
    dump_scctrl_dec_reg();
#endif

	up(&(hx170dec_data.busy_lock));

	return 0;
}

static int CheckHwId(hx170dec_t *dev)
{
	long int hwid;

	size_t numHw = sizeof(DecHwId) / sizeof(*DecHwId);

	hwid = readl(dev->hwregs);
	printk(KERN_INFO "hx170dec: HW ID=0x%08lx\n", hwid);

	hwid = (hwid >> 16) & 0xFFFF;   /* product version only */

	while (numHw--) {
		if (hwid == DecHwId[numHw]) {
			printk(KERN_INFO
			       "hx170dec: Compatible HW found at 0x%08lx\n",
			       dev->iobaseaddr);
			return 1;
		}
	}

	printk(KERN_INFO "hx170dec: No Compatible HW found at 0x%08lx\n",
	       dev->iobaseaddr);
	return 0;
}

/*------------------------------------------------------------------------------
    Function name   : ReserveIO
    Description     : IO reserve

    Return type     : int
------------------------------------------------------------------------------*/
static int ReserveIO(void)
{
	if (!request_mem_region
	    (hx170dec_data.iobaseaddr, hx170dec_data.iosize, "hx170dec")) {
		printk(KERN_ERR "hx170dec_error: failed to reserve HW regs\n");
		return -EBUSY;
	}

	hx170dec_data.hwregs =
	    (volatile u8 *)ioremap_nocache(hx170dec_data.iobaseaddr,
	                                   hx170dec_data.iosize);

	if (hx170dec_data.hwregs == NULL) {
		printk(KERN_ERR "hx170dec_error: failed to ioremap HW regs\n");
		ReleaseIO();
		return -EBUSY;
	}

	/* check for correct HW */
	if (!CheckHwId(&hx170dec_data)) {
		ReleaseIO();
		return -EBUSY;
	}

	return 0;
}

/*------------------------------------------------------------------------------
    Function name   : releaseIO
    Description     : release

    Return type     : void
------------------------------------------------------------------------------*/

static void ReleaseIO(void)
{
	if (hx170dec_data.hwregs)
		iounmap((void *)hx170dec_data.hwregs);
	release_mem_region(hx170dec_data.iobaseaddr, hx170dec_data.iosize);
}

/*------------------------------------------------------------------------------
    Function name   : hx170dec_isr
    Description     : interrupt handler

    Return type     : irqreturn_t
------------------------------------------------------------------------------*/

static irqreturn_t hx170dec_isr(int irq, void *dev_id)
{
	unsigned int handled = 0;

	hx170dec_t *dev = (hx170dec_t *) dev_id;
	u32 irq_status_dec;
	u32 irq_status_pp;

	handled = 0;

	/* interrupt status register read */
	irq_status_dec = readl(dev->hwregs + X170_INTERRUPT_REGISTER_DEC);
	irq_status_pp = readl(dev->hwregs + X170_INTERRUPT_REGISTER_PP);

	if ((irq_status_dec & HX_DEC_INTERRUPT_BIT) ||
	    (irq_status_pp & HX_PP_INTERRUPT_BIT)) {
		if (irq_status_dec & HX_DEC_INTERRUPT_BIT) {
			/* clear dec IRQ */
			writel(irq_status_dec & (~HX_DEC_INTERRUPT_BIT),
			       dev->hwregs + X170_INTERRUPT_REGISTER_DEC);
			/* fasync kill for decoder instances */
			if (dev->async_queue_dec != NULL) {
				kill_fasync(&dev->async_queue_dec,
				            SIGIO, POLL_IN);
			} else {
				/*printk(KERN_WARNING "x170: IRQ received w/o
				 * anybody waiting for it!\n");
				 */
			}

			hx170dec_data.done = 1;
			wake_up_interruptible(&hx170dec_data.dec_queue);
		}

		if (irq_status_pp & HX_PP_INTERRUPT_BIT) {
			/* clear pp IRQ */
			writel(irq_status_pp & (~HX_PP_INTERRUPT_BIT),
			       dev->hwregs + X170_INTERRUPT_REGISTER_PP);

			/* kill fasync for PP instances */
			if (dev->async_queue_pp != NULL) {
				kill_fasync(&dev->async_queue_pp,
				            SIGIO, POLL_IN);
			} else {
                mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec: IRQ received w/o anybody waiting for it!");
			}
			/*PDEBUG("pp IRQ received!\n"); */
			hx170dec_data.done = 1;
			wake_up_interruptible(&hx170dec_data.dec_queue);
		}

		handled = 1;
	} else {
		printk(KERN_INFO "hx170dec:IRQ received, but not x170's!\n");
	}

	return IRQ_RETVAL(handled);
}

/*------------------------------------------------------------------------------
    Function name   : ResetAsic
    Description     : reset asic

    Return type     :
------------------------------------------------------------------------------*/

void ResetAsic(hx170dec_t *dev)
{
	int i;

	writel(0, dev->hwregs + 0x04);

	for (i = 4; i < dev->iosize; i += 4)
		writel(0, dev->hwregs + i);
}

/*------------------------------------------------------------------------------
    Function name   : dump_regs
    Description     : Dump registers

    Return type     :
------------------------------------------------------------------------------*/
#ifdef HX170DEC_DEBUG
void dump_regs(unsigned long data)
{
	hx170dec_t *dev = (hx170dec_t *) data;
	int i;

	printk(KERN_INFO "hx170dec:Reg Dump Start\n");
	for (i = 0; i < dev->iosize; i += 4)
		printk(KERN_INFO "hx170dec:\toffset %02X = %08X\n", i, readl(dev->hwregs + i));

	printk(KERN_INFO "hx170dec:Reg Dump End\n");
}
#endif

static int hx170dec_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long start = vma->vm_start;
	unsigned long size = vma->vm_end - vma->vm_start;
	int retval = 0;

	if (!get_cma_type()) {
		unsigned int  cfg_size;
		unsigned long pyhs_start = vma->vm_pgoff << PAGE_SHIFT;
		unsigned long pyhs_end = pyhs_start + size;

    	if (true != get_hw_config_int("memory_config/codec", &cfg_size, NULL))
    	{
    	    printk(KERN_ERR "get_hw_config_int failed\n");
    	    return -EFAULT;
    	}

    	if (0 == cfg_size) {
    	    printk(KERN_ERR "codec memory size is 0.\n");
    	    return -EFAULT;
    	}

		if(!(pyhs_start >= hisi_reserved_codec_phymem//not codec memory
				&& pyhs_end <= hisi_reserved_codec_phymem + PAGE_ALIGN(cfg_size * SZ_1K))
			&& !(pyhs_start >= hx170dec_data.iobaseaddr//not io address
				&& pyhs_end <= hx170dec_data.iobaseaddr + hx170dec_data.iosize)) {
			printk(KERN_ERR "%s(%d) failed map:0x%lx-0x%lx\n", __FUNCTION__, __LINE__, pyhs_start, pyhs_end);
			return -EFAULT;
		}
	}
	/* make buffers write-thru cacheable */
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec:enter hx170dec_mmap.");
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_DEC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx170dec:hx170dec_mmap start = %ld size = %ld.", start, size);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	if (remap_pfn_range(vma, start, vma->vm_pgoff, size, vma->vm_page_prot))
		retval = -ENOBUFS;

	return retval;
}

/* VFS methods */
static const struct file_operations hx170dec_fops = {
open:
	hx170dec_open,
release :
	hx170dec_release,
unlocked_ioctl :
	hx170dec_ioctl,
fasync :
	hx170dec_fasync,
mmap :
	hx170dec_mmap,
};

static void hx170dec_dev_release(struct device *dev)
{
	return;
}

static ssize_t show_index(struct device *cd,
                          struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "0");
}

static ssize_t show_name(struct device *cd,
                         struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "hx170dec\n");
}

static struct device_attribute dec_attrs[] = {
	__ATTR(name, S_IRUGO, show_index, NULL),
	__ATTR(index, S_IRUGO, show_name, NULL),
	__ATTR_NULL
};

static struct class dec_class = {
		.name = "hx170dec",
		.dev_attrs = dec_attrs,
	};

/***********************************************************************************
* Function:       vdec_clk_get
* Description:    配置VDEC相关时钟获取
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
int vdec_clk_get(void)
{
	/* VDEC分频前时钟门控的时钟获取 */
	s_vdec_clk.s_src_clk = clk_get(NULL, CLK_PERIPLL_VDEC_GATED);
    if (IS_ERR(s_vdec_clk.s_src_clk)) {
    	printk(KERN_ERR "hx170dec_error:get CLK_VDEC_SRC clock failed.\n");
		return -EIO;
    }

	/* VDEC X2X桥时钟获取 */
	s_vdec_clk.s_x2x_clk = clk_get(NULL, CLK_X2X_VDEC_BRG_S);
    if (IS_ERR(s_vdec_clk.s_x2x_clk)) {
    	printk(KERN_ERR "hx170dec_error:get CLK_VDEC_X2X clock failed.\n");
		return -EIO;
    }

	/* CFGMAPB到VDEC的P2P桥时钟获取 */
	s_vdec_clk.s_p2p_clk = clk_get(NULL, CLK_P2P_VDEC_BRG_S);
    if (IS_ERR(s_vdec_clk.s_p2p_clk)) {
    	printk(KERN_ERR "hx170dec_error:get CLK_VDEC_P2P clock failed.\n");
		return -EIO;
    }

	/* VDEC系统工作时钟获取 */
	s_vdec_clk.s_vdec_clk = clk_get(NULL, CLK_1VDEC_SLAVE_CLK);
    if (IS_ERR(s_vdec_clk.s_vdec_clk)) {
    	printk(KERN_ERR "hx170dec_error:get CLK_VDEC clock failed.\n");
		return -EIO;
    }

	return 0;
}

/***********************************************************************************
* Function:       vdec_clk_rstdisable
* Description:    配置VDEC工作时钟域解复位
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void vdec_clk_rstdisable(void)
{
    /* VDEC RST DISABLE */
	phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
				   SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(CALC_REG_OFFSET),
               	   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_15vdecw_START,
               	   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_15vdecw_END,
               	   1);
	return;
}

/***********************************************************************************
* Function:       vdec_clk_enable
* Description:    配置VDEC相关时钟使能
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/

int vdec_clk_enable(void)
{
	if (NULL == s_vdec_clk.s_src_clk || NULL == s_vdec_clk.s_x2x_clk
        || NULL == s_vdec_clk.s_p2p_clk || NULL == s_vdec_clk.s_vdec_clk) {
	    printk(KERN_ERR "hx170dec_error:the clk is nul. s_vdec_clk.s_src_clk = %p,s_vdec_clk.s_x2x_clk = %p,s_vdec_clk.s_p2p_clk  = %p,s_vdec_clk.s_vdec_clk = %p\n",s_vdec_clk.s_src_clk,s_vdec_clk.s_x2x_clk,s_vdec_clk.s_p2p_clk ,s_vdec_clk.s_vdec_clk);
     	return -EIO;
	}

	/* VDEC分频前时钟门控的时钟使能 */
    if (0 != clk_enable(s_vdec_clk.s_src_clk)) {
    	printk(KERN_ERR "hx170dec_error:s_src_clk enable failed.\n");
	    return -EIO;
    }
    s_vdec_clk.src_clk= 1;

    /* VDEC IP工作时钟分频比配置 */
	if (0 != clk_set_rate(s_vdec_clk.s_vdec_clk, DECODER_CLOCK)) {
    	printk(KERN_ERR "hx170dec_error:clk_set_rate failed.\n");
    	vdec_clk_disable();
	    return -EIO;
    }

	/* VDEC X2X桥时钟使能 */
	if (0 != clk_enable(s_vdec_clk.s_x2x_clk)) {
    	printk(KERN_ERR "hx170dec_error:s_x2x_clk enable failed.\n");
    	vdec_clk_disable();
	    return -EIO;
    }
    s_vdec_clk.x2x_clk = 1;

	/* CFGMAPB到VDEC的P2P桥时钟使能 */
	if (0 != clk_enable(s_vdec_clk.s_p2p_clk)) {
    	printk(KERN_ERR "hx170dec_error:s_p2p_clk enable failed.\n");
    	vdec_clk_disable();
	    return -EIO;
    }
    s_vdec_clk.p2p_clk = 1;

	/* VDEC系统工作时钟使能 */
	if (0 != clk_enable(s_vdec_clk.s_vdec_clk)) {
    	printk(KERN_ERR "hx170dec_error:s_vdec_clk enable failed.\n");
    	vdec_clk_disable();
	    return -EIO;
    }
    s_vdec_clk.vdec_clk = 1;

	return 0;
}

/***********************************************************************************
* Function:       vdec_clk_disable
* Description:    配置VDEC相关时钟禁止
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void vdec_clk_disable(void)
{
	/* VDEC系统工作时钟禁止 */
	if (NULL != s_vdec_clk.s_vdec_clk && 1 == s_vdec_clk.vdec_clk) {
		clk_disable(s_vdec_clk.s_vdec_clk);
		s_vdec_clk.vdec_clk = 0;
	}

	/* VDEC X2X桥时钟禁止 */
	if (NULL != s_vdec_clk.s_x2x_clk && 1 == s_vdec_clk.x2x_clk) {
		clk_disable(s_vdec_clk.s_x2x_clk);
		s_vdec_clk.x2x_clk = 0;
	}

	/* CFGMAPB到VDEC的P2P桥时钟禁止 */
	if (NULL != s_vdec_clk.s_p2p_clk && 1 == s_vdec_clk.p2p_clk) {
		clk_disable(s_vdec_clk.s_p2p_clk);
		s_vdec_clk.p2p_clk = 0;
	}

	/* VDEC分频前时钟门控的时钟禁止 */
	if (NULL != s_vdec_clk.s_src_clk && 1 == s_vdec_clk.src_clk) {
		clk_disable(s_vdec_clk.s_src_clk);
		s_vdec_clk.src_clk = 0;
	}

	return;
}

/***********************************************************************************
* Function:       vdec_clk_put
* Description:    配置VDEC相关时钟释放
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void vdec_clk_put(void)
{
    /* VDEC系统工作时钟释放 */
    if (NULL != s_vdec_clk.s_vdec_clk) {
        clk_put(s_vdec_clk.s_vdec_clk);
        s_vdec_clk.s_vdec_clk = NULL;
    }

    /* VDEC X2X桥时钟释放 */
    if (NULL != s_vdec_clk.s_x2x_clk) {
        clk_put(s_vdec_clk.s_x2x_clk);
        s_vdec_clk.s_x2x_clk = NULL;
    }

    /* CFGMAPB到VDEC的P2P桥时钟释放 */
    if (NULL != s_vdec_clk.s_p2p_clk) {
        clk_put(s_vdec_clk.s_p2p_clk);
        s_vdec_clk.s_p2p_clk = NULL;
    }

    /* VDEC分频前时钟门控的时钟释放 */
    if (NULL != s_vdec_clk.s_src_clk) {
        clk_put(s_vdec_clk.s_src_clk);
        s_vdec_clk.s_src_clk = NULL;
    }

    return;

}


/***********************************************************************************
* Function:       vdec_regulator_enable
* Description:    配置VDEC掉电区上电
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
int vdec_regulator_enable(void)
{
    /* VDEC掉电区电源上电 */
    if (0 != regulator_enable(hx170dec_data.reg)) {
    	printk(KERN_ERR "hx170dec_error:failed to enable VDEC_VDD regulator.\n");
        return -1;
    }

    /* VDEC掉电区解复位 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_7dec_START,
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_7dec_END,
				   1);

    /* VDEC掉电区ISO禁止 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_7dec_START,
				   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_7dec_END,
				   1);

    /* VDEC掉电区时钟使能 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_7dec_START,
			       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_7dec_END,
			       1);

	return 0;
}

/***********************************************************************************
* Function:       vdec_regulator_disable
* Description:    配置VDEC掉电区下电
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void vdec_regulator_disable(void)
{
    int rc = 1;
    /* VDEC掉电区时钟关闭 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_7dec_START,
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_7dec_END,1);

    /* VDEC掉电区ISO使能 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_7dec_START,
				   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_7dec_END,1);

	/* VDEC掉电区复位 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_7dec_START,
				   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_7dec_END,1);

	/* VDEC掉电区电源关闭 */
	if (NULL !=  hx170dec_data.reg)
	{
    	rc = regulator_disable(hx170dec_data.reg);
    	if (rc)
    	{
  			printk(KERN_ERR "Regulator vdec disable failed rc=%d\n", rc);
  		}
    }

	return;
}

/***********************************************************************************
* Function:       vdec_regulator_put
* Description:    配置VDEC掉电区电源释放
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void vdec_regulator_put(void)
{
	/* VDEC掉电区电源释放 */
	if (NULL !=  hx170dec_data.reg) {
    	regulator_put(hx170dec_data.reg);
		hx170dec_data.reg = NULL;
    }

	return;
}

#ifdef CONFIG_DEBUG_FS
int __init vdec_dbgfs_init(void)
{
    struct dentry *vdec_debugfs_dir = NULL;

    printk("vdec_debugfs_init, vdec_dbgfs_pwdncfg = %d, vdec_pwdn_status = %d.\n", vdec_dbgfs_pwdncfg, vdec_pwdn_status);

    vdec_debugfs_dir = debugfs_create_dir(VDEC_DEBUGFS_DIR_NAME, NULL);
    if (ERR_PTR(-ENODEV) == vdec_debugfs_dir) {
        printk("debugfs_create_dir create dir %s failed!\n", VDEC_DEBUGFS_DIR_NAME);
        return -EINVAL;
    }

    debugfs_create_u32(VDEC_DEBUGFS_PWDN_FILE_NAME, 0664, vdec_debugfs_dir, &vdec_dbgfs_pwdncfg);

    return 0;
}
late_initcall(vdec_dbgfs_init);
#endif

/*------------------------------------------------------------------------------
    Function name   : hx170dec_dev_probe
    Description     : probe hx170 dec device

    Return type     : int
------------------------------------------------------------------------------*/
static int hx170dec_dev_probe(struct platform_device *pdev)
{
	struct resource *res;
	int result;
	dev_t dev;
	int devno;
	int ret = 0;

    /* B050初始化结构体变量s_vdec_clk */
	memset(&s_vdec_clk, 0, sizeof(s_vdec_clk));

    hx170dec_data.open_count = 0;
    hx170dec_data.reg = NULL;
	hx170dec_data.reg= regulator_get(NULL, VDEC_VDD);
	if (IS_ERR(hx170dec_data.reg)) {
		printk(KERN_ERR "hx170dec_error: hx170dec_dev_probe get dec regulator failed\n");
		ret =  PTR_ERR(hx170dec_data.reg);
        hx170dec_data.reg = NULL;
        goto err;
	}

	ret = vdec_clk_get();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx170dec_error: hx170dec_dev_probe get dec clock failed\n");
        goto err;
	}

    /* 配置VDEC下电区 */
    ret = vdec_regulator_enable();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx170dec_error: hx170dec_dev_probe regulator_enable failed\n");
		goto err;
	}

    /* 配置VDEC工作时钟域解复位 */
    vdec_clk_rstdisable();

    /* 配置VDEC总线桥、VDEC IP时钟使能,配置VDEC工作时钟分频比 */
    ret = vdec_clk_enable();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx170dec_error: hx170dec_dev_probe clk_enable failed\n");
		goto err;
	}

    vdec_pwdn_status = 1;

#ifdef DUMP_SCCTRL_DEC_REG
    dump_scctrl_dec_reg();
#endif

	/* get io mem resource */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (NULL == res) {
		printk(KERN_ERR "hx170dec_error: get io mem resource failed\n");
		ret = -ENODEV;
		goto err;
	}
	hx170dec_data.iobaseaddr = res->start;
	hx170dec_data.iosize = res->end - res->start + 1;

	/* get irq resource */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	hx170dec_data.irq = res->start;

	/* get kernel virtual address */
	result = ReserveIO();
	if (result < 0) {
		ReleaseIO();
		ret = result;
		goto err;
	}

	/* reset hardware */
	ResetAsic(&hx170dec_data);

	/* request irq */
	result = request_irq(hx170dec_data.irq, hx170dec_isr,
	                     IRQF_DISABLED | IRQF_SHARED, "hx170dec",
	                     (void *)&hx170dec_data);
	if (result < 0) {
		printk(KERN_ERR "hx170dec_error: request irq failed\n");
		ReleaseIO();
		ret = result;
		goto err;
	}

	/* dymamic alloc major */
	result = alloc_chrdev_region(&dev, 0, 1, "hx170dec");
	if (result < 0) {
		printk(KERN_ERR "hx170dec: unable to get major %d\n",
		       hx170dec_major);
		ReleaseIO();
		ret = result;
		goto err;
	}
	hx170dec_major = MAJOR(dev);

	printk(KERN_INFO "hx170dec:hx170dec_major is %d\n", hx170dec_major);

	/* register cdev */
	devno = MKDEV(hx170dec_major, 0);
	cdev_init(&hx170dec_data.cdev, &hx170dec_fops);
	hx170dec_data.cdev.owner = THIS_MODULE;
	result = cdev_add(&hx170dec_data.cdev, devno, 1);
	if (result < 0) {
		printk(KERN_ERR "hx170dec_error: add cdev failed\n");
		free_irq(hx170dec_data.irq, &hx170dec_data);
		ReleaseIO();
		ret = result;
		goto err;
	}

	/* register sysfs */
	result = class_register(&dec_class);
	if (result < 0) {
		printk(KERN_ERR "hx170dec_error: add cdev failed\n");
		free_irq(hx170dec_data.irq, &hx170dec_data);
		ReleaseIO();
		cdev_del(&hx170dec_data.cdev);
		ret = result;
		goto err;
	}
	/*hx170dec_data.dev.driver_data = &hx170dec_data; */
	hx170dec_data.dev.class = &dec_class;
	hx170dec_data.dev.devt = MKDEV(hx170dec_major, 0);
	hx170dec_data.dev.release = hx170dec_dev_release;
	dev_set_name(&hx170dec_data.dev, "%s", "hx170dec");
	result = device_register(&hx170dec_data.dev);
	if (result < 0) {
		printk(KERN_ERR "hx170dec_error: add cdev failed\n");
		free_irq(hx170dec_data.irq, &hx170dec_data);
		ReleaseIO();
		cdev_del(&hx170dec_data.cdev);
		ret = result;
		goto err;
	}

	init_waitqueue_head(&hx170dec_data.dec_queue);

    if (0 != vdec_dbgfs_pwdncfg) {
        /* 配置VDEC IP、VDEC总线桥时钟关闭 */
    	vdec_clk_disable();

    	/* 配置VDEC下电区掉电 */
    	vdec_regulator_disable();

        vdec_pwdn_status = 0;
    }

#ifdef DUMP_SCCTRL_DEC_REG
    dump_scctrl_dec_reg();
#endif

    printk(KERN_INFO "hx170dec: dev probe OK\n");

	return ret;

  err:
    printk(KERN_ERR "hx170dec_error: module inserted failed\n");

    vdec_clk_disable();
	vdec_regulator_disable();
    vdec_pwdn_status = 0;
	vdec_clk_put();
	vdec_regulator_put();

	return ret;
}

/*
 **************************************************************************
 * FunctionName: hx170dec_dev_resume;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int hx170dec_dev_resume(struct platform_device *pdev)
{
	int ret = 0;

	printk(KERN_INFO "enter %s", __func__);

	if (0 == hx170dec_data.open_count) {
	    /*should not open the dec*/

	} else {
		printk(KERN_ERR "BUG: should not be HERE !! [open_count=%d]", hx170dec_data.open_count);

        /* 配置VDEC下电区 */
        ret = vdec_regulator_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx170dec_error: hx170dec_open regulator_enable failed\n");
    		return -EIO;
    	}

    	/* 配置VDEC工作时钟域解复位 */
        vdec_clk_rstdisable();

        /* 配置VDEC总线桥、VDEC IP时钟使能,配置VDEC工作时钟分频比 */
        ret = vdec_clk_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx170dec_error: hx170dec_open clk_enable failed\n");
    		vdec_regulator_disable();
    		return -EIO;
    	}
		printk(KERN_INFO "hx170dec resume successfully");
	}

	return ret;
}


/*
 **************************************************************************
 * FunctionName: hx170dec_dev_suspend;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int hx170dec_dev_suspend(struct platform_device *pdev, pm_message_t state)
{
	printk(KERN_INFO "enter %s", __func__);
	if (0 != hx170dec_data.open_count) {
		printk(KERN_ERR "BUG: should NOT be here [open_count=%d]", hx170dec_data.open_count);

		/* 配置VDEC IP、VDEC总线桥时钟关闭 */
    	vdec_clk_disable();

    	/* 配置VDEC下电区掉电 */
    	vdec_regulator_disable();
    	printk(KERN_INFO "hx170dec suspend successfully");
	}

	return 0;
}


static struct platform_driver hx170dec_driver = {
	.driver = {
		.name = "hx170dec",
	},
	.probe = hx170dec_dev_probe,
    .suspend = hx170dec_dev_suspend,
	.resume = hx170dec_dev_resume,
 };

/*------------------------------------------------------------------------------
    Function name   : hx170dec_init
    Description     : Initialize the driver

    Return type     : int
------------------------------------------------------------------------------*/
int __init hx170dec_init(void)
{
	int result;
    printk(KERN_INFO "hx170dec:enter hx170dec_init\n");

	result = platform_driver_register(&hx170dec_driver);

	sema_init(&(hx170dec_data.busy_lock), 1);

	return result;
}

/*------------------------------------------------------------------------------
    Function name   : hx170dec_cleanup
    Description     : clean up

    Return type     : int
------------------------------------------------------------------------------*/
void __exit hx170dec_cleanup(void)
{
	hx170dec_t *dev = (hx170dec_t *)&hx170dec_data;

	/* y44207 revived : Clock off state , Can't write register*/
#if 0
	/* clear dec IRQ */
	writel(0, hx170dec_data.hwregs + X170_INTERRUPT_REGISTER_DEC);
	/* clear pp IRQ */
	writel(0, hx170dec_data.hwregs + X170_INTERRUPT_REGISTER_PP);
#endif

#ifdef HX170DEC_DEBUG
	dump_regs((unsigned long)dev);  /* dump the regs */
#endif

	/* free the encoder IRQ */
	printk(KERN_INFO "hx170dec:free_irq.\n");
	free_irq(dev->irq, (void *)&hx170dec_data);

	printk(KERN_INFO "hx170dec:cdev_del.\n");
	cdev_del(&dev->cdev);

    printk(KERN_INFO "hx170dec:device_unregister\n");
	device_unregister(&hx170dec_data.dev);

	printk(KERN_INFO "hx170dec:class_unregister\n");
	class_unregister(&dec_class);

	ReleaseIO();

    printk(KERN_INFO "hx170dec:platform_driver_unregister\n");

	platform_driver_unregister(&hx170dec_driver);

    /* B050 VDEC相关时钟释放 */
	vdec_clk_put();

	/* B050 VDEC掉电区电源释放 */
	vdec_regulator_put();

#if 0
	clk_put(hx170dec_data.clock);
	regulator_put(hx170dec_data.reg);
#endif

	printk(KERN_INFO "hx170dec: module removed\n");
	return;
}

module_init(hx170dec_init);
module_exit(hx170dec_cleanup);

/* module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hantro Products Oy");
MODULE_DESCRIPTION("hx170dec - driver module for Hantro x170 decoder");

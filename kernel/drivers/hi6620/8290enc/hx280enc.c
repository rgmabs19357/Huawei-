/*
 * Encoder device driver (kernel module)
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
--------------------------------------------------------------------------------
--
--  Abstract : 6280/7280/8270/8290 Encoder device driver (kernel module)
--
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <linux/pci.h>
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#include <linux/wait.h>
#include <linux/clk.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include <linux/pm_qos_params.h>
#include <linux/hisi_ion.h>

#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/hisi_mem.h>
#include <hsad/config_mgr.h>


/* our own stuff */
#include "hx280enc.h"

#include "video_mntn_kernel.h"

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

/* add for video mntn, modifier: w00228831, begin */
#define MODULE_NAME "hx280enc"
/* add for video mntn, modifier: w00228831, end */


#ifdef __KERNEL__
#define ENCODER_CLOCK               CONFIG_8290_ENC_CLK
#define ENCODER_WAIT_TIMEOUT_COEFF  CONFIG_8290_ENC_WAIT_TIMEOUT_COEFF
#endif

#ifndef ENCODER_CLOCK
#define ENCODER_CLOCK               288000000
#endif

#ifndef ENCODER_WAIT_TIMEOUT_COEFF
#define ENCODER_WAIT_TIMEOUT_COEFF  1
#endif


#define HIENC8290_ERR(fmt, args...) \
    do {\
        printk(KERN_ERR MODULE_NAME ": " fmt "\n", ## args); \
    } while (0)

#define HIENC8290_WARN(fmt, args...) \
    do {\
        printk(KERN_WARNING MODULE_NAME ": " fmt "\n", ## args); \
    } while (0)

#define HIENC8290_INFO(fmt, args...) \
    do {\
        printk(KERN_INFO MODULE_NAME ": " fmt "\n", ## args); \
    } while (0)

#ifdef HI8290_DEBUG
#define HIENC8290_DEBUG(fmt, args...) \
    do {\
        printk(KERN_DEBUG MODULE_NAME ": " fmt "\n", ## args); \
    } while (0)
#else
#define HIENC8290_DEBUG(fmt, args...)
#endif

/* these could be module params in the future */
#define ENC_HW_ID1                  0x62800000
#define ENC_HW_ID2                  0x72800000
#define ENC_HW_ID3                  0x82700000
#define ENC_HW_ID4                  0x82900000
#define ENC_IRQ_REG_OFFSET          0x04

/* dump SCCTRL/AO_SCCTRL/PMCTRL reg about enc power on/off,
   rst en/dis, and clk en/dis, 2013/05/06 */
//#define DUMP_SCCTRL_ENC_REG

#ifdef CONFIG_DEBUG_FS
#define VENC_DEBUGFS_DIR_NAME           "mit2venc"
#define VENC_DEBUGFS_PWDN_FILE_NAME     "pwdn"
#endif

/* and this is our MAJOR; use 0 for dynamic allocation (recommended)*/
static int hx280enc_major;
static int g_enc_done;
static unsigned long virtbase;
static unsigned long enc_clk_level = HX280ENC_CLOCK_FREQ_288;
static unsigned long clk_freq_arr[HX280ENC_CLOCK_FREQ_MAX] = {180000000, ENCODER_CLOCK};

/* here's all the must remember stuff */
typedef struct {
	struct semaphore sem;
	unsigned long iobaseaddr;
	unsigned int iosize;
	volatile u8 *hwregs;
	int open_count;
	unsigned int irq;
	struct semaphore busy_lock;
	struct fasync_struct *async_queue;
	wait_queue_head_t enc_done_queue;
	struct cdev cdev;
	struct device dev;
	struct clk *clock;
	struct regulator *reg;
	struct pm_qos_request_list qos_req_cpu_int_latency;
} hx280enc_t;


/* B050 VENC时钟 */
typedef struct
{
	struct clk *s_src_clk;
	struct clk *s_x2x_clk;
	struct clk *s_p2p_clk;
	struct clk *s_venc_clk;

	unsigned int src_clk   : 1;
	unsigned int x2x_clk   : 1;
	unsigned int p2p_clk   : 1;
	unsigned int venc_clk  : 1;
	unsigned int reserve   : 28;
} venc_clk;

static  venc_clk s_venc_clk;


static hx280enc_t hx280enc_data;    /* dynamic allocation? */

static u32 venc_dbgfs_pwdncfg = 1;
static u32 venc_pwdn_status = 0;

static int ReserveIO(void);
static void ReleaseIO(void);
static void ResetAsic(hx280enc_t *dev);
static irqreturn_t hx280enc_isr(int irq, void *dev_id);
extern int pmem_kalloc(const size_t size, const uint32_t id);
extern int pmem_kfree(const uint32_t id, const int32_t physaddr);


#ifdef DUMP_SCCTRL_ENC_REG
/***********************************************************************************
* Function:       dump_scctrl_enc_reg
* Description:    dump SCCTRL/AO_SCCTRL/PMCTRL register about enc power on/off,
                  rst en/dis, clk en/dis.
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
void dump_scctrl_enc_reg(void)
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

static int hx280enc_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long start = vma->vm_start;
	unsigned long size = vma->vm_end - vma->vm_start;
	int retval = 0;
	if (!get_cma_type()) {
		unsigned int cfg_size;
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

		if (!(pyhs_start >= hisi_reserved_codec_phymem//not codec memory
				&& pyhs_end <= hisi_reserved_codec_phymem + PAGE_ALIGN(cfg_size * SZ_1K))
			&& !(pyhs_start >= hx280enc_data.iobaseaddr//not io address
				&& pyhs_end <= hx280enc_data.iobaseaddr + hx280enc_data.iosize)){
			printk(KERN_ERR "%s(%d) failed map:0x%lx-0x%lx\n", __FUNCTION__, __LINE__, pyhs_start, pyhs_end);
			return -EFAULT;
		}
	}

	/* make buffers write-thru cacheable */
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx280enc:enter hx280enc_mmap.");
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG,
                   "hx280enc:hx280enc_mmap start = %ld size = %ld.", start, size);

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	if (remap_pfn_range(vma, start, vma->vm_pgoff, size, vma->vm_page_prot)) {
		retval = -ENOBUFS;
	}

	return retval;
}

static long hx280enc_ioctl(struct file *filp,
                           unsigned int cmd, unsigned long arg)
{
	int err = 0;
	hx280enc_t *encdev;

	/*
	 * extract the type and number bitfields, and don't decode
	 * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
	 */
	if (_IOC_TYPE(cmd) != HX280ENC_IOC_MAGIC) {
		return -ENOTTY;
	}

	if (_IOC_NR(cmd) > HX280ENC_IOC_MAXNR) {
		return -ENOTTY;
	}

	/*
	 * the direction is a bitmask, and VERIFY_WRITE catches R/W
	 * transfers. `Type' is user-oriented, while
	 * access_ok is kernel-oriented, so the concept of "read" and
	 * "write" is reversed
	 */
	if (_IOC_DIR(cmd) & _IOC_READ) {
		err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	} else if (_IOC_DIR(cmd) & _IOC_WRITE) {
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
	}
	if (err) {
		printk(KERN_ERR "hx280enc_error:io ctrl access check failed\n");
		return -EFAULT;
	}

	encdev = (hx280enc_t *) (filp->private_data);
	if (NULL == encdev) {
		printk(KERN_ERR "hx280enc_error:get vout semphore failed\n");
		return -EINVAL;
	}

	/* make this multi process safe */
	if (down_interruptible(&encdev->sem)) {
		printk(KERN_ERR "hx280enc_error:get vout semphore failed\n");
		return -ERESTARTSYS;
	}

	switch (cmd) {
		case HX280ENC_IOCGHWOFFSET: {
			__put_user(hx280enc_data.iobaseaddr,
			           (unsigned long *)arg);
			break;
		}

		case HX280ENC_IOCGHWIOSIZE: {
			__put_user(hx280enc_data.iosize, (unsigned int *)arg);
			break;
		}

		case HX280ENC_IOC_CLI: {
			/*disable_irq(h5650enc_data.irq); */
			break;
		}

		case HX280ENC_IOC_STI: {
			/*enable_irq(h5650enc_data.irq); */
			break;
		}

		case HX280ENC_IOCHARDRESET: {
			/*
			 * reset the counter to 1, to allow unloading in case
			 * of problems. Use 1, not 0, because the invoking
			 * process has the device open.
			 */
			break;
		}

		case HX280ENC_IOCVIRTBASE: {
			virtbase = (unsigned long)arg;
			break;
		}

		case HX280ENC_IOCWAITDONE: {


            if (!wait_event_interruptible_timeout
                (encdev->enc_done_queue, g_enc_done, arg*HZ*ENCODER_WAIT_TIMEOUT_COEFF)) {


				g_enc_done = 0;
				err = -ETIME;
				printk(KERN_INFO "hx280enc: wait timeout\n");
				break;
			} else if (signal_pending(current)) {
				err = -ERESTARTSYS;
				printk(KERN_INFO "hx280enc: signal pending\n");
				break;
			}

			g_enc_done = 0;
			break;
		}
		case HX280ENC_IOC_CLOCK_ON:
#if 0
			ret = regulator_enable(hx280enc_data.reg);
			if ( ret ) {
				printk(KERN_ERR "hx280enc: regulator_enable failed\n");
			}

			ret = clk_enable(hx280enc_data.clock);
			if ( ret ) {
				printk(KERN_ERR "hx280enc: clk_enable failed\n");
			}
#endif
			break;

		case HX280ENC_IOC_CLOCK_OFF:
#if 0
			clk_disable(hx280enc_data.clock);
			regulator_disable( hx280enc_data.reg );
#endif
			break;
	    case HX280ENC_IOC_CLOCK_FREQ_SET:
	        if( arg >= HX280ENC_CLOCK_FREQ_MAX)
	        {
                enc_clk_level = HX280ENC_CLOCK_FREQ_288;
            }
            else
            {
                enc_clk_level = arg;
            }
			break;
		default:
			break;
	}

	up(&encdev->sem);
	return err;
}

static int hx280enc_open(struct inode *inode, struct file *filp)
{
	hx280enc_t *dev = &hx280enc_data;
	int ret = 0;

    ret = down_interruptible(&(hx280enc_data.busy_lock));
	if (ret != 0) {
		printk(KERN_ERR "hx280enc_error: hx280enc_open down_interruptible failed.\n");
		return -EINTR;
	}

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx280enc:enter hx280enc_open()");

    if (hx280enc_data.open_count > 0)
    {
        mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG,
                       "hx280enc: don't need to open device, the open count is %d", hx280enc_data.open_count);
        filp->private_data = (void *)dev;
        hx280enc_data.open_count++;
        up(&(hx280enc_data.busy_lock));
        return 0;
    }

    if (0 == venc_pwdn_status) {
        /* 配置VENC下电区 */
        ret = venc_regulator_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx280enc_error: hx280enc_open regulator_enable failed.\n");
            up(&(hx280enc_data.busy_lock));
    		return -EIO;
    	}

    	/* 配置VENC工作时钟域解复位 */
        venc_clk_rstdisable();

        /* 配置VENC总线桥、VENC IP时钟使能,配置VENC工作时钟分频比 */
        ret = venc_clk_enable();
    	if ( 0 != ret ) {
    		printk(KERN_ERR "hx280enc_error: hx280enc_open clk_enable failed.\n");
    		venc_regulator_disable();
            up(&(hx280enc_data.busy_lock));
    		return -EIO;
    	}

        venc_pwdn_status = 1;
    }
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG,
        "hx280enc_open: venc debugfs pwdn config = %d, venc pwdn status = %d", venc_dbgfs_pwdncfg, venc_pwdn_status);

#ifdef DUMP_SCCTRL_ENC_REG
    dump_scctrl_enc_reg();
#endif

    hx280enc_data.open_count++;
	filp->private_data = (void *)dev;

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_INFO, "hx280enc:dev opened.");

    pm_qos_add_request(&hx280enc_data.qos_req_cpu_int_latency, PM_QOS_CPU_INT_LATENCY, 0);
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG, "%s, req cpu int latency for cpu idle.", __func__);

	up(&(hx280enc_data.busy_lock));
	return 0;
}

#if 0
static int hx280enc_fasync(int fd, struct file *filp, int mode)
{
	/*hx280enc_t *dev = (hx280enc_t *) filp->private_data;

	   HIENC8290_ERR("fasync called\n");

	   return fasync_helper(fd, filp, mode, &dev->async_queue); */
	return 0;
}
#endif

#ifdef HI8290_DEBUG
static void dump_regs(unsigned long data);
#endif


static int hx280enc_release(struct inode *inode, struct file *filp)
{
#ifdef HI8290_DEBUG
	hx280enc_t *dev = (hx280enc_t *) filp->private_data;
#endif
	int ret = 0;

    ret = down_interruptible(&(hx280enc_data.busy_lock));
	if (ret != 0) {
		printk(KERN_ERR "hx280enc: hx280enc_release down_interruptible failed.\n");
		return -EINTR;
	}

	hx280enc_data.open_count--;

	if (hx280enc_data.open_count > 0)
	{
        mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG,
                       "hx280enc: can't close device, the open count is %d", hx280enc_data.open_count);
        up(&(hx280enc_data.busy_lock));
	    return 0;
	}

	/* this is necessary if user process exited asynchronously */
	/* disable_irq(dev->irq); */
#ifdef HI8290_DEBUG
	dump_regs((unsigned long)dev);  /* dump the regs */
#endif

	/* y44207 deleted: Clock off state , Can't set register */
	//ResetAsic(dev);     /* reset hardware */

	/* remove this filp from the asynchronusly notified filp's */
	/* hx280enc_fasync(-1, filp, 0); */

    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_INFO, "hx280enc:dev closed");

    pm_qos_remove_request(&hx280enc_data.qos_req_cpu_int_latency);
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG, "%s, remove cpu int latency for cpu idle.", __func__);

    if (0 != venc_dbgfs_pwdncfg) {
        /* 配置VENC IP、VENC总线桥时钟关闭 */
    	venc_clk_disable();

    	/* 配置VENC下电区掉电 */
    	venc_regulator_disable();

        venc_pwdn_status = 0;
    }
    mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG,
        "hx280enc_release: venc debugfs pwdn config = %d, venc pwdn status = %d", venc_dbgfs_pwdncfg, venc_pwdn_status);

#ifdef DUMP_SCCTRL_ENC_REG
    dump_scctrl_enc_reg();
#endif

	up(&(hx280enc_data.busy_lock));

	return 0;
}

/* VFS methods */
static struct file_operations hx280enc_fops = {
mmap:
	hx280enc_mmap,
open :
	hx280enc_open,
release :
	hx280enc_release,
unlocked_ioctl :
	hx280enc_ioctl,
};

static int ReserveIO(void)
{
	long int hwid;

	if (!request_mem_region
	    (hx280enc_data.iobaseaddr, hx280enc_data.iosize, "hx280enc")) {
		printk(KERN_ERR "hx280enc_error: ReserveIO(), failed to reserve HW regs\n");
		return -EBUSY;
	}

	hx280enc_data.hwregs =
	    (volatile u8 *)ioremap_nocache(hx280enc_data.iobaseaddr,
	                                   hx280enc_data.iosize);

	if (hx280enc_data.hwregs == NULL) {
		printk(KERN_ERR "hx280enc_error: ReserveIO(), failed to ioremap HW regs\n");
		ReleaseIO();
		return -EBUSY;
	}

	hwid = readl(hx280enc_data.hwregs);

	/* check for encoder HW ID */
	if ((((hwid >> 16) & 0xFFFF) != ((ENC_HW_ID1 >> 16) & 0xFFFF)) &&
	    (((hwid >> 16) & 0xFFFF) != ((ENC_HW_ID2 >> 16) & 0xFFFF)) &&
	    (((hwid >> 16) & 0xFFFF) != ((ENC_HW_ID3 >> 16) & 0xFFFF)) &&
	    (((hwid >> 16) & 0xFFFF) != ((ENC_HW_ID4 >> 16) & 0xFFFF))) {
		printk(KERN_ERR "hx280enc_error: ReserveIO(), HW not found at 0x%08lx\n",
		              hx280enc_data.iobaseaddr);
#ifdef HX280ENC_DEBUG
		dump_regs((unsigned long)&hx280enc_data);
#endif
		ReleaseIO();
		return -EBUSY;
	} else {
		printk
		(KERN_NOTICE "hx280enc: ReserveIO(), Valid HW found at base <0x%08lx> with ID <0x%08lx>\n",
		 hx280enc_data.iobaseaddr, hwid);
	}

	return 0;

}

static void ReleaseIO(void)
{
	if (hx280enc_data.hwregs) {
		iounmap((void *)hx280enc_data.hwregs);
		hx280enc_data.hwregs = 0;
	}
	release_mem_region(hx280enc_data.iobaseaddr, hx280enc_data.iosize);
}

static irqreturn_t hx280enc_isr(int irq, void *dev_id)
{
	hx280enc_t *dev = (hx280enc_t *) dev_id;
	u32 irq_status;

	irq_status = readl(dev->hwregs + ENC_IRQ_REG_OFFSET);

	if (irq_status & 0x01) {

		/* clear enc IRQ and slice ready interrupt bit */
		writel(irq_status & (~0x101), dev->hwregs + ENC_IRQ_REG_OFFSET);

		/* Handle slice ready interrupts. The reference implementation
		 * doesn't signal slice ready interrupts to EWL.
		 * The EWL will poll the slices ready register value. */
		if ((irq_status & 0x1FE) == 0x100) {
			printk(KERN_ERR "hx280enc_error:Slice ready IRQ handled!\n");
			return IRQ_HANDLED;
		}

		/* All other interrupts will be signaled to EWL. */
		if (dev->async_queue) {
			kill_fasync(&dev->async_queue, SIGIO, POLL_IN);
		} else {
            mntn_print_log(EN_ID_MNTN_BLVIDEO_DRV_ENC, EN_VIDEO_LOG_LEVLE_DEBUG, "hx280enc: IRQ received w/o anybody waiting for it!");
		}

		g_enc_done = 1;
		wake_up_interruptible(&dev->enc_done_queue);

		return IRQ_HANDLED;
	} else {
		printk(KERN_INFO "hx280enc:IRQ received, but NOT handled!\n");
		return IRQ_NONE;
	}

}

void ResetAsic(hx280enc_t *dev)
{
	int i;

	writel(0, dev->hwregs + 0x38);

	for (i = 4; i < dev->iosize; i += 4) {
		writel(0, dev->hwregs + i);
	}
}

#ifdef HX280ENC_DEBUG
void dump_regs(unsigned long data)
{
	hx280enc_t  *dev = (hx280enc_t *) data;
	int i;

	printk(KERN_INFO "hx280enc:Reg Dump Start\n");
	for (i = 0; i < dev->iosize; i += 4) {
		printk(KERN_INFO "hx280enc:\toffset %02X = %08X\n", i,
		                readl(dev->hwregs + i));
	}
	printk(KERN_INFO "hx280enc:Reg Dump End\n");
}
#endif

static void hx280enc_dev_release(struct device *dev)
{
	return;
}

static struct device_attribute dec_attrs[] = {
	__ATTR(name, S_IRUGO, NULL, NULL),
	__ATTR(index, S_IRUGO, NULL, NULL),
	__ATTR_NULL
};

static struct class enc_class = {
		.name = "hx280enc",
		.dev_attrs = dec_attrs,
	};

/***********************************************************************************
* Function:       venc_clk_get
* Description:    配置VENC相关时钟获取
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
int venc_clk_get(void)
{
	/* VENC分频前时钟门控的时钟获取 */
	s_venc_clk.s_src_clk = clk_get(NULL, CLK_PERIPLL_VENC_GATED);
    if (IS_ERR(s_venc_clk.s_src_clk)) {
    	printk(KERN_ERR "hx280enc_error:get CLK_VENC_SRC clock failed.\n");
		return -EIO;
    }

	/* VENC X2X桥时钟获取 */
	s_venc_clk.s_x2x_clk = clk_get(NULL, CLK_X2X_VENC_BRG_S);
    if (IS_ERR(s_venc_clk.s_x2x_clk)) {
    	printk(KERN_ERR "hx280enc_error:get CLK_VENC_X2X clock failed.\n");
		return -EIO;
    }

	/* CFGMAPB到VENC的P2P桥时钟获取 */
	s_venc_clk.s_p2p_clk = clk_get(NULL, CLK_P2P_VENC_BRG_S);
    if (IS_ERR(s_venc_clk.s_p2p_clk)) {
    	printk(KERN_ERR "hx280enc_error:get CLK_VENC_P2P clock failed.\n");
		return -EIO;
    }

	/* VENC系统工作时钟获取 */
	s_venc_clk.s_venc_clk = clk_get(NULL, CLK_0VENC_SLAVE_CLK);
    if (IS_ERR(s_venc_clk.s_venc_clk)) {
    	printk(KERN_ERR "hx280enc_error:get CLK_VENC clock failed.\n");
		return -EIO;
    }

	return 0;
}

/***********************************************************************************
* Function:       venc_clk_rstdisable
* Description:    配置VENC工作时钟域解复位
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void venc_clk_rstdisable(void)
{
    /* VENC RST DISABLE */
	phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
				   SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(CALC_REG_OFFSET),
               	   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_14vencw_START,
               	   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_14vencw_END,
               	   1);
	return;
}

/***********************************************************************************
* Function:       venc_clk_enable
* Description:    配置VENC相关时钟使能
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
int venc_clk_enable(void)
{
	if (NULL == s_venc_clk.s_src_clk || NULL == s_venc_clk.s_x2x_clk
        || NULL == s_venc_clk.s_p2p_clk || NULL == s_venc_clk.s_venc_clk) {
    	printk(KERN_ERR "hx280enc_error:the clk is null. s_venc_clk.s_src_clk = %p,s_venc_clk.s_x2x_clk = %p,s_venc_clk.s_p2p_clk  = %p,s_venc_clk.s_venc_clk = %p\n",s_venc_clk.s_src_clk,s_venc_clk.s_x2x_clk,s_venc_clk.s_p2p_clk ,s_venc_clk.s_venc_clk);
     	return -EIO;
	}

	/* VENC分频前时钟门控的时钟使能 */
    if (0 != clk_enable(s_venc_clk.s_src_clk)) {
    	printk(KERN_ERR "hx280enc_error:s_src_clk enable failed.\n");
	    return -EIO;
    }
    s_venc_clk.src_clk= 1;

    /* VENC IP工作时钟分频比配置 */

	if (0 != clk_set_rate(s_venc_clk.s_venc_clk, clk_freq_arr[enc_clk_level])) {
    	printk(KERN_ERR "hx280enc_error:clk_set_rate failed.\n");
    	venc_clk_disable();
	    return -EIO;
    }

	/* VENC X2X桥时钟使能 */
	if (0 != clk_enable(s_venc_clk.s_x2x_clk)) {
    	printk(KERN_ERR "hx280enc_error:s_x2x_clk enable failed.\n");
    	venc_clk_disable();
	    return -EIO;
    }
    s_venc_clk.x2x_clk = 1;

	/* CFGMAPB到VENC的P2P桥时钟使能 */
	if (0 != clk_enable(s_venc_clk.s_p2p_clk)) {
    	printk(KERN_ERR "hx280enc_error:s_p2p_clk enable failed.\n");
    	venc_clk_disable();
	    return -EIO;
    }
    s_venc_clk.p2p_clk = 1;

	/* VENC系统工作时钟使能 */
	if (0 != clk_enable(s_venc_clk.s_venc_clk)) {
    	printk(KERN_ERR "hx280enc_error:s_venc_clk enable failed.\n");
    	venc_clk_disable();
	    return -EIO;
    }
    s_venc_clk.venc_clk = 1;

	return 0;
}

/***********************************************************************************
* Function:       venc_clk_disable
* Description:    配置VENC相关时钟禁止
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void venc_clk_disable(void)
{
	/* VENC系统工作时钟禁止 */
	if (NULL != s_venc_clk.s_venc_clk && 1 == s_venc_clk.venc_clk) {
		clk_disable(s_venc_clk.s_venc_clk);
    	s_venc_clk.venc_clk = 0;
	}

	/* VENC X2X桥时钟禁止 */
	if (NULL != s_venc_clk.s_x2x_clk && 1 == s_venc_clk.x2x_clk) {
		clk_disable(s_venc_clk.s_x2x_clk);
    	s_venc_clk.x2x_clk = 0;
	}

	/* CFGMAPB到VENC的P2P桥时钟禁止 */
	if (NULL != s_venc_clk.s_p2p_clk && 1 == s_venc_clk.p2p_clk) {
		clk_disable(s_venc_clk.s_p2p_clk);
    	s_venc_clk.p2p_clk = 0;
	}

	/* VENC分频前时钟门控的时钟禁止 */
	if (NULL != s_venc_clk.s_src_clk && 1 == s_venc_clk.src_clk) {
		clk_disable(s_venc_clk.s_src_clk);
    	s_venc_clk.src_clk = 0;
	}

	return;
}

/***********************************************************************************
* Function:       venc_clk_put
* Description:    配置VENC相关时钟释放
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void venc_clk_put(void)
{
	/* VENC系统工作时钟释放 */
	if (NULL != s_venc_clk.s_venc_clk) {
		clk_put(s_venc_clk.s_venc_clk);
    	s_venc_clk.s_venc_clk = NULL;
	}

	/* VENC X2X桥时钟释放 */
	if (NULL != s_venc_clk.s_x2x_clk) {
		clk_put(s_venc_clk.s_x2x_clk);
        s_venc_clk.s_x2x_clk = NULL;
	}

	/* CFGMAPB到VENC的P2P桥时钟释放 */
	if (NULL != s_venc_clk.s_p2p_clk) {
		clk_put(s_venc_clk.s_p2p_clk);
        s_venc_clk.s_p2p_clk = NULL;
	}

	/* VENC分频前时钟门控的时钟释放 */
	if (NULL != s_venc_clk.s_src_clk) {
    	clk_put(s_venc_clk.s_src_clk);
        s_venc_clk.s_src_clk = NULL;
	}

	return;
}

/***********************************************************************************
* Function:       venc_regulator_enable
* Description:    配置VENC掉电区上电
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
int venc_regulator_enable(void)
{
    /* VENC掉电区电源上电 */
    if (0 != regulator_enable(hx280enc_data.reg)) {
    	printk(KERN_ERR "hx280enc_error:VENC regulator_enable failed.\n");
        return -1;
    }

    /* VENC掉电区解复位 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_6enc_START,
				   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_6enc_END,
				   1);

    /* VENC掉电区ISO禁止 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_6enc_START,
				   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_6enc_END,
				   1);

    /* VENC掉电区时钟使能 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_6enc_START,
			       SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_6enc_END,
			       1);

	return 0;
}

/***********************************************************************************
* Function:       venc_regulator_disable
* Description:    配置VENC掉电区下电
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void venc_regulator_disable(void)
{
    int rc = 1;
    /* VENC掉电区时钟关闭 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_6enc_START,
				   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_6enc_END,1);

    /* VENC掉电区ISO使能 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_6enc_START,
				   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_6enc_END,1);

	/* VENC掉电区复位 */
	phy_reg_writel(SOC_SC_ON_BASE_ADDR,
				   SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),
				   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_6enc_START,
				   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_6enc_END,1);

	/* VENC掉电区电源关闭 */
	if (NULL !=  hx280enc_data.reg) {
    	rc = regulator_disable(hx280enc_data.reg);
    	if (rc)
    	{
  			printk(KERN_ERR "Regulator venc disable failed rc=%d\n", rc);
  		}
    }

	return;
}

/***********************************************************************************
* Function:       venc_regulator_put
* Description:    配置VENC掉电区电源释放
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  NA
* Others:
***********************************************************************************/
void venc_regulator_put(void)
{
	/* VENC掉电区电源释放 */
	if (NULL !=  hx280enc_data.reg) {
    	regulator_put(hx280enc_data.reg);
		hx280enc_data.reg = NULL;
    }

	return;
}

#ifdef CONFIG_DEBUG_FS
int __init venc_dbgfs_init(void)
{
    struct dentry *venc_debugfs_dir = NULL;

    printk("venc_debugfs_init, venc_dbgfs_pwdncfg = %d, venc_pwdn_status = %d.\n", venc_dbgfs_pwdncfg, venc_pwdn_status);

    venc_debugfs_dir = debugfs_create_dir(VENC_DEBUGFS_DIR_NAME, NULL);
    if (ERR_PTR(-ENODEV) == venc_debugfs_dir) {
        printk("debugfs_create_dir create dir %s failed!\n", VENC_DEBUGFS_DIR_NAME);
        return -EINVAL;
    }

    debugfs_create_u32(VENC_DEBUGFS_PWDN_FILE_NAME, 0664, venc_debugfs_dir, &venc_dbgfs_pwdncfg);

    return 0;
}
late_initcall(venc_dbgfs_init);
#endif

static int hx280enc_dev_probe(struct platform_device *pdev)
{
	struct resource *res;
	int result;
	dev_t dev;
	int devno;
	int ret = 0;

	hx280enc_data.open_count = 0;
	hx280enc_data.reg = NULL;
	hx280enc_data.reg= regulator_get(NULL, VENC_VDD);
	if (IS_ERR(hx280enc_data.reg)) {
		printk(KERN_ERR "hx280enc_error: hx280enc_dev_probe get enc regulator failed.\n");
		ret = PTR_ERR(hx280enc_data.reg);
		goto err;
	}

	ret = venc_clk_get();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx280enc_error: hx280enc_dev_probe get enc clock failed.\n");
        goto err;
	}

    /* 配置VENC下电区 */
    ret = venc_regulator_enable();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx280enc_error: hx280enc_dev_probe regulator_enable failed.\n");
		goto err;
	}

    /* 配置VENC工作时钟域解复位 */
    venc_clk_rstdisable();

    /* 配置VENC总线桥、VENC IP时钟使能,配置VENC工作时钟分频比 */
    ret = venc_clk_enable();
	if ( 0 != ret ) {
		printk(KERN_ERR "hx280enc_error: hx280enc_dev_probe clk_enable failed.\n");
		goto err;
	}

    venc_pwdn_status = 1;

#ifdef DUMP_SCCTRL_ENC_REG
    dump_scctrl_enc_reg();
#endif

	/* get io mem resource */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (NULL == res) {
		printk(KERN_ERR "hx280enc_error: get io mem resource failed\n");
		ret = -ENODEV;
		goto err;
	}
	hx280enc_data.iobaseaddr = res->start;
	hx280enc_data.iosize = res->end - res->start + 1;

	/* get irq resource */
	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	hx280enc_data.irq = res->start;

	/* request irq */
	result = request_irq(hx280enc_data.irq, hx280enc_isr, IRQF_DISABLED, "hx280enc",
	                     (void *)&hx280enc_data);

	if (result < 0) {
		printk(KERN_ERR "hx280enc_error: request irq failed\n");
		ReleaseIO();
		ret = result;
		goto err;
	}

	/* get kernel virtual address */
	result = ReserveIO();
	if (result < 0) {
		ReleaseIO();
		free_irq(hx280enc_data.irq, &hx280enc_data);
		ret = result;
		goto err;
	}

	/* reset hardware */
	ResetAsic(&hx280enc_data);

	/* dymamic alloc major */
	result = alloc_chrdev_region(&dev, 0, 1, "hx280enc");
	if (result < 0) {
		printk(KERN_ERR "hx280enc_error: unable to get major %d\n",
		              hx280enc_major);
		ReleaseIO();
		free_irq(hx280enc_data.irq, &hx280enc_data);
		ret = result;
		goto err;
	}
	hx280enc_major = MAJOR(dev);

	/* init semphore */
	sema_init(&(hx280enc_data.sem) , 1);

	/* init wait queue */
	init_waitqueue_head(&(hx280enc_data.enc_done_queue));

	/* register cdev */
	devno = MKDEV(hx280enc_major, 0);
	cdev_init(&hx280enc_data.cdev, &hx280enc_fops);
	hx280enc_data.cdev.owner = THIS_MODULE;
	result = cdev_add(&hx280enc_data.cdev, devno, 1);
	if (result < 0) {
		printk(KERN_ERR "hx280enc_error: add cdev failed\n");
		free_irq(hx280enc_data.irq, &hx280enc_data);
		ReleaseIO();
		ret = result;
		goto err;
	}

	memset(&hx280enc_data.dev, 0, sizeof(hx280enc_data.dev));

	class_register(&enc_class);

	/*hx280enc_data.dev.driver_data = &hx280enc_data; */
	hx280enc_data.dev.class = &enc_class;
	dev_set_name(&hx280enc_data.dev, "%s", "hx280enc");
	hx280enc_data.dev.devt = MKDEV(hx280enc_major, 0);
	hx280enc_data.dev.release = hx280enc_dev_release;
	result = device_register(&hx280enc_data.dev);

	printk(KERN_INFO "hx280enc:register driver ok,major is %d,result %d\n",
	                hx280enc_major, result);

    if (0 != venc_dbgfs_pwdncfg) {
        /* 配置VENC IP、VENC总线桥时钟关闭 */
    	venc_clk_disable();

    	/* 配置VENC下电区掉电 */
    	venc_regulator_disable();

        venc_pwdn_status = 0;
    }

#ifdef DUMP_SCCTRL_ENC_REG
    dump_scctrl_enc_reg();
#endif

	printk(KERN_INFO "hx280enc: dev probe OK\n");

	return ret;

  err:
    printk(KERN_ERR "hx280enc_error:module inserted failed\n");

    venc_clk_disable();
	venc_regulator_disable();
    venc_pwdn_status = 0;
	venc_clk_put();
	venc_regulator_put();

	return ret;

	return 0;
}

static struct platform_driver hx280enc_driver = {
	.driver = {
		.name = "hx280enc",
	},
	.probe = hx280enc_dev_probe,
 };

int __init hx280enc_init(void)
{
	int result;

	printk(KERN_INFO "hx280enc:enter hx280enc_init\n");

	result = platform_driver_register(&hx280enc_driver);

	sema_init(&(hx280enc_data.busy_lock) , 1);

	return result;
}

void __exit hx280enc_cleanup(void)
{
	/* free the encoder IRQ */
	printk(KERN_INFO "hx280enc:free_irq.\n");
	free_irq(hx280enc_data.irq, &hx280enc_data);

	printk(KERN_INFO "hx280enc:cdev_del.\n");
	cdev_del(&hx280enc_data.cdev);

	printk(KERN_INFO "hx280enc:device_unregister\n");
	device_unregister(&hx280enc_data.dev);

	printk(KERN_INFO "hx280enc:class_unregister\n");
	class_unregister(&enc_class);
	ReleaseIO();

	platform_driver_unregister(&hx280enc_driver);

	/* B050 VENC相关时钟释放 */
	venc_clk_put();

	/* B050 VENC掉电区电源释放 */
	venc_regulator_put();

    printk(KERN_INFO "hx280enc: module removed\n");

	return;
}

module_init(hx280enc_init);
module_exit(hx280enc_cleanup);

/* module description */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hantro Products Oy");
MODULE_DESCRIPTION("hx280enc - driver module for Hantro 8090 encoder");

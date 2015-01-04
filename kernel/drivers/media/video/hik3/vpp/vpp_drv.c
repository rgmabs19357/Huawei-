
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <asm/irq.h>
#include <media/v4l2-common.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <mach/hisi_mem.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>

#include "vpp_drv.h"

#define LOG_TAG "VPP_DRV"
#include "vpp_log.h"

/* module description */
MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("j00140427");
MODULE_DESCRIPTION("vpp driver");

#define VPP_DEVICE_ID 19

static struct video_device *s_vpp_device_p = NULL;
static struct video_device s_vpp_device;

static wait_queue_head_t s_wait_queue;
static bool s_interrupt_cond = false;
static struct clk *s_clk = NULL;
static struct regulator *s_vdec_vcc = NULL;

//VPP主设备open次数
static unsigned int s_vpp_count = 0;

/*the func regist to irq*/
static irqreturn_t vpp_isr ( int irq, void *dev_id )
{
    if (hal_get_int_sta(HAL_INTMSK_VTEINT))
    {
        logd("============== the irq is my care\n");
        s_interrupt_cond = true;
        wake_up_interruptible(&s_wait_queue);
        hal_clear_int_sta(HAL_INTMSK_VTEINT);
    }
    else
    {
        logd("============== the irq is not my care\n");
    }

    return IRQ_HANDLED;
}

int __init vpp_init(void)
{
    int ret = 0;
    struct video_device *video_dev = NULL;

    logi("in vpp_init: vpp_phymem = 0x%x, camera_phymem = 0x%x, codec_phymem = 0x%x\n",
         hisi_reserved_vpp_phymem,
         hisi_reserved_camera_phymem,
         hisi_reserved_codec_phymem);

    /* alloc memory for video device */
    video_dev = video_device_alloc();
    if (NULL == video_dev)
    {
        loge("alloc video device failed\n");
        ret =  -ENOMEM;
        goto err;
    }

    /* init v4l device */
    s_interrupt_cond = false;
    *video_dev = s_vpp_device;

    /* register vpp device */
    if (video_register_device(video_dev, 0, VPP_DEVICE_ID))
    {
        loge("video device register failed\n");
        ret = -EINVAL;
        goto err;
    }
    s_vpp_device_p = video_dev;

    /*init the wait queue*/
    init_waitqueue_head(&s_wait_queue);

    /*register a irq for vpp*/
    ret = request_irq(IRQ_VPP, vpp_isr, 0, "VPP", NULL);
    if(ret != 0)
    {
        loge("fail to request irq, ret = 0x%x\n",ret);
        goto err;
    }

    s_vdec_vcc = regulator_get(NULL,  "vcc_vdec");
    if (IS_ERR(s_vdec_vcc)) {
        loge("%s: failed to get vcc_vdec regulator\n", __func__);
        ret =  PTR_ERR(s_vdec_vcc);
        s_vdec_vcc = NULL;
        goto err;
    }

    s_clk = clk_get(NULL, "clk_vpp");
    if (IS_ERR(s_clk))
    {
        loge("get clock failed\n");
        ret =  PTR_ERR(s_clk);
        goto err;
    }
    hal_init();
    return ret;

  err:
    loge("module not inserted\n");
    if (NULL != s_vpp_device_p)
    {
        video_unregister_device(video_dev);
        s_vpp_device_p = NULL;
    }

    if(NULL != video_dev)
    {
        kfree(video_dev);
        video_dev = NULL;
    }

	if (NULL != s_vdec_vcc) {
        regulator_put(s_vdec_vcc);
        s_vdec_vcc = NULL;
    }

    return ret;
}

void __exit vpp_deinit(void)
{
    logi("in vpp_deinit\n");
    hal_deinit();

    if (NULL != s_vpp_device_p)
    {
        video_unregister_device(s_vpp_device_p);
        kfree(s_vpp_device_p);
        s_vpp_device_p = NULL;
    }
    free_irq(IRQ_VPP, 0);

    return;
}

static int vpp_open(struct file *file)
{
    int ret = -EFAULT;

    logi("in vpp_open\n");

    logi("vpp_phymem = 0x%x, camera_phymem = 0x%x, codec_phymem = 0x%x\n",
         hisi_reserved_vpp_phymem,
         hisi_reserved_camera_phymem,
         hisi_reserved_codec_phymem);
    if ( s_vpp_count > 0 )
    {
        logi("don't need to open device, the open count is %d\n", s_vpp_count);
        s_vpp_count++;
        return 0;
    }

    if (0 != regulator_enable(s_vdec_vcc)) {
        loge("failed to enable vdec-vcc regulator.\n");
        return -1;
    }

    if (NULL != s_clk)
     {
        ret = clk_enable(s_clk);
        if (ret)
        {
            loge("clk_enable failed ret = %#x\n",ret);
        }
        else
        {
            logi(" clock is enable \n");
            ret = clk_set_rate(s_clk, 140000000);
            if (ret) {
                loge("clk_set_rate failed ret = %#x\n",ret);
            } else {
                logi(" clock set rate success \n");
            }
        }
    }
    else
    {
        loge("%s,the s_clk is null\n",__FUNCTION__);
    }

    ret = inter_init();
    if(K3_SUCCESS != ret)
    {
        loge("vpp init failed ret = %#x\n",ret);
        return -EFAULT;
    }

    inter_open(HAL_LAYER_VIDEO1);
    hal_set_int_enable(HAL_INTMSK_VTEINT);

    s_vpp_count++;

    return 0;
}

static int vpp_close(struct file *file)
{
    logi("in vpp_close\n");

    s_vpp_count--;
    logi("in vpp_close s_vpp_count = %d\n",s_vpp_count);
    if (s_vpp_count > 0)//TODO: < 0, 试一下
    {
        logi("don't need to close device, the open count is %d\n", s_vpp_count);
        return 0;
    }

    inter_close(HAL_LAYER_VIDEO1);

    inter_deinit();

    if ( NULL != s_clk)
    {
        clk_disable(s_clk);
        logi(" clock is disable \n");
    }
    else
    {
        loge("the s_clk is null\n");
    }

    /*disable vdec regulator*/
    if( NULL !=  s_vdec_vcc)
    {
        regulator_disable(s_vdec_vcc);
    }

    return 0;
}

static long vpp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0;

    logi("in vpp_ioctl\n");
    /*
     * extract the type and number bitfields, and don't decode
     * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
     */
    if(_IOC_TYPE(cmd) != VPP_IOC_MAGIC)
    {
        loge("vpp magic is wrong\n");
        return -ENOTTY;
    }

    if(_IOC_NR(cmd) > VPP_IOC_MAXNR)
    {
        loge("vpp NR is wrong\n");
        return -ENOTTY;
    }

    if(_IOC_DIR(cmd) & _IOC_READ)
    {
        err = !access_ok(VERIFY_WRITE, (void *) arg, _IOC_SIZE(cmd));
    }
    else if(_IOC_DIR(cmd) & _IOC_WRITE)
    {
        err = !access_ok(VERIFY_READ, (void *) arg, _IOC_SIZE(cmd));
    }

    if(err)
    {
        loge("vpp err: %d\n",err);
        return -EFAULT;
    }

    switch (cmd)
    {
        case VPP_STARTCONFIG:
        {
            VPP_CONFIG_S vpp_config;

            logi("VPP_STARTCONFIG\n");

            err = __copy_from_user(&vpp_config, (const void *) arg, sizeof(VPP_CONFIG_S));
            if (err)
            {
                loge("__copy_from_user failed\n");
                err =  -EFAULT;
                break;
            }

            s_interrupt_cond = false;

            err = inter_start( &vpp_config );
            if( K3_SUCCESS == err )
            {   //fixme:time
                int ret = wait_event_interruptible_timeout(s_wait_queue, s_interrupt_cond, HZ/2);
                s_interrupt_cond = false;
                if( ret > 0 )
                {
                    err = 0;
                    logi("wait event success\n");
                }
                else
                {
                    loge("wait event time out\n");
                    err = -ETIME;
                }
            }
            else
            {
                err = -EFAULT;
                loge("set vpp config failed\n");
            }

            break;
        }

        /* just for test */
        case VPP_GETBUSADDR:
        {
            VPP_BUSADDR_S stBussAddr;

            stBussAddr.vppBusAddr       = hisi_reserved_vpp_phymem;
            stBussAddr.codecBusAddr     = hisi_reserved_codec_phymem;
            stBussAddr.cameraBusAddr    = hisi_reserved_camera_phymem;

            if (__copy_to_user((void *)arg, &stBussAddr, sizeof(stBussAddr)))
            {
                printk(KERN_ERR "%s(%d):ioctl error\n", __FUNCTION__, __LINE__);
                return -EFAULT;
            }

            break;
        }

        default:
        {
            loge("unsurport cmd cmd = %d\n",cmd);
            err = -ENOIOCTLCMD;
            break;
        }
    }

    return err;
}

//only for test
static int vpp_mmap(struct file *file, struct vm_area_struct *vma)
{
    unsigned long start = 0;
    unsigned long size = 0;

    logi();

    if (NULL == vma)
    {
        loge("can not get vm_area_struct!");
        return -EBADF;
    }

    start = vma->vm_start;
    size = vma->vm_end - vma->vm_start;

    /* make buffers write-thru cacheable */
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot); //update to 2.6.32
    if (remap_pfn_range(vma, start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        loge("remap_pfn_range error!");
        return -ENOBUFS;
    }

    return 0;
}

static void vpp_release( struct video_device *vdev )
{
    if (NULL != s_clk) {
        clk_put(s_clk);
        s_clk = NULL;
    }

    if (NULL != s_vdec_vcc) {
        regulator_put(s_vdec_vcc);
        s_vdec_vcc = NULL;
    }

    logi("in vpp_release\n");
    return;
}

/* VFS methods */
static struct v4l2_file_operations s_vpp_fops = {
  .owner = THIS_MODULE,
  .open =  vpp_open,
  .release = vpp_close,
  .mmap = vpp_mmap,
  .ioctl= vpp_ioctl,
};

static struct video_device s_vpp_device = {
    .name      = "VPP",
    .fops      = &s_vpp_fops,
    .ioctl_ops = NULL,
    .release   = vpp_release,
};

module_init(vpp_init);
module_exit(vpp_deinit);
MODULE_LICENSE("GPL");


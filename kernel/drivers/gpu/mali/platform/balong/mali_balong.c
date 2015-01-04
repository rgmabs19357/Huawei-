/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2010, 2012-2013 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_platform.c
 * Platform specific Mali driver functions for:
 * - Realview Versatile platforms with ARM11 Mpcore and virtex 5.
 * - Versatile Express platforms with ARM Cortex-A9 and virtex 6.
 */
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/pm.h>
#ifdef CONFIG_PM_RUNTIME
#include <linux/pm_runtime.h>
#endif
#include <asm/io.h>
#include <linux/mali/mali_utgard.h>
#include "mali_kernel_common.h"
#include <linux/dma-mapping.h>
#include <linux/moduleparam.h>
#include "mali_pp_scheduler.h"

#include "mali_balong_pmm.h"
#include <mach/hisi_mem.h>
#include <mach/irqs.h>
#include <mach/platform.h>

static void mali_platform_device_release(struct device *device);
static int mali_os_suspend(struct device *device);
static int mali_os_resume(struct device *device);
static int mali_os_freeze(struct device *device);
static int mali_os_thaw(struct device *device);
static void mali_gpu_utilization_proc(struct mali_gpu_utilization_data *data);
#ifdef CONFIG_PM_RUNTIME
static int mali_runtime_suspend(struct device *device);
static int mali_runtime_resume(struct device *device);
static int mali_runtime_idle(struct device *device);
#endif

/* Base address DEFINATION */
#define MALI_BASE_ADDR                  REG_BASE_G3D

#define MALI_FRAME_BUFFER_ADDR          0x33000000
#define MALI_FRAME_BUFFER_SIZE          0x01000000

/* irq number */
#define MALI_IRQ_ID                     IRQ_G3D_MALI

static void mali_platform_device_release(struct device *device);

static struct resource mali_gpu_resources_m450_mp4[] =
{
    #ifdef CONFIG_ARCH_K3V2
    MALI_GPU_RESOURCES_MALI450_MP2(MALI_BASE_ADDR, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID)
    #else
    MALI_GPU_RESOURCES_MALI450_MP4(MALI_BASE_ADDR, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID, MALI_IRQ_ID)
    #endif
};

static struct dev_pm_ops mali_gpu_device_type_pm_ops =
{
    .suspend = mali_os_suspend,
    .resume = mali_os_resume,
    .freeze = mali_os_freeze,
    .thaw = mali_os_thaw,
#ifdef CONFIG_PM_RUNTIME
    .runtime_suspend = mali_runtime_suspend,
    .runtime_resume = mali_runtime_resume,
    .runtime_idle = mali_runtime_idle,
#endif
};

static struct device_type mali_gpu_device_device_type =
{
    .pm = &mali_gpu_device_type_pm_ops,
};

static struct mali_gpu_device_data mali_gpu_data =
{
    .shared_mem_size =1024 * 1024 * 1024, /* 1GB */
    .fb_start = MALI_FRAME_BUFFER_ADDR,
    .fb_size = MALI_FRAME_BUFFER_SIZE,
	.max_job_runtime = 2000, /* 2 seconds time out */
    .utilization_interval = 50,        /* 50ms */
    .utilization_callback = mali_gpu_utilization_proc,
	.pmu_switch_delay = 0xFF, /* do not have to be this high on FPGA, but it is good for testing to have a delay */
	.pmu_domain_config = {0x1, 0x2, 0x4, 0x4, 0x4, 0x8, 0x8, 0x8, 0x8, 0x1, 0x2, 0x8},
};
static struct platform_device mali_gpu_device =
{
    .name = MALI_GPU_NAME_UTGARD,
    .id = 0,
    .dev.release = mali_platform_device_release,
    .dev.type = &mali_gpu_device_device_type,/* .dev.pm_domain perhaps should be implemented on newer kernel */
	.dev.coherent_dma_mask = DMA_BIT_MASK(32),
	.dev.platform_data = &mali_gpu_data,
};


/* init the config.h with dynamic mem of hisi */
void mali_hisi_mem_init(void)
{
    mali_gpu_data.fb_start  = HISI_FRAME_BUFFER_BASE;
    mali_gpu_data.fb_size   = HISI_FRAME_BUFFER_SIZE;
}

/*****************************************************************************
 function name  : mali_platform_device_register
 description    : mali platform device register
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_init

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
int mali_platform_device_register(void)
{
    int err = -1;

    MALI_DEBUG_PRINT(4, ("mali_platform_device_register() called\n"));
    MALI_DEBUG_PRINT(4, ("Registering Mali-450 MP8 device\n"));

    /* init the mem first of hisi */
    mali_hisi_mem_init();
	mali_gpu_device.num_resources = ARRAY_SIZE(mali_gpu_resources_m450_mp4);
	mali_gpu_device.resource = mali_gpu_resources_m450_mp4;

    /* Register the platform device */
    err = platform_device_register(&mali_gpu_device);
    if (0 == err)
    {
        mali_platform_init();
#ifdef CONFIG_PM_RUNTIME
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,37))
        pm_runtime_set_autosuspend_delay(&(mali_gpu_device.dev), 1000);
        pm_runtime_use_autosuspend(&(mali_gpu_device.dev));
#endif
        pm_runtime_enable(&(mali_gpu_device.dev));
#endif

        return 0;
    }

    return err;
}

/*****************************************************************************
 function name  : mali_platform_device_unregister
 description    : mali platform device unregister
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : platform_device_unregister

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_platform_device_unregister(void)
{
    MALI_DEBUG_PRINT(4, ("mali_platform_device_unregister() called\n"));
    mali_platform_deinit();
    platform_device_unregister(&mali_gpu_device);
	platform_device_put(&mali_gpu_device);

}

/*****************************************************************************
 function name  : mali_platform_device_release
 description    : mali platform device release
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : NA

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static void mali_platform_device_release(struct device *device)
{
    MALI_DEBUG_PRINT(4, ("mali_platform_device_release() called\n"));
}

/*****************************************************************************
 function name  : mali_os_suspend
 description    : os suspend
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_power_mode_change

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_os_suspend(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_os_suspend() called\n"));

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->suspend)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->suspend(device);
    }

    mali_platform_power_mode_change(MALI_POWER_MODE_DEEP_SLEEP);

    return ret;
}

/*****************************************************************************
 function name  : mali_os_resume
 description    : os resume
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_power_mode_change

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_os_resume(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_os_resume() called\n"));

    mali_platform_power_mode_change(MALI_POWER_MODE_ON);

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->resume)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->resume(device);
    }

    return ret;
}

/*****************************************************************************
 function name  : mali_os_freeze
 description    : os freeze
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : NA

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_os_freeze(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_os_freeze() called\n"));

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->freeze)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->freeze(device);
    }

    return ret;
}
/*****************************************************************************
 function name  : mali_os_thaw
 description    : os thaw
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : NA

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_os_thaw(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_os_thaw() called\n"));

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->thaw)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->thaw(device);
    }

    return ret;
}
/*****************************************************************************
 function name  : mali_gpu_utilization_proc
 description    : mali_gpu_utilization_proc
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : NA

 called         : os

 history        :
  1.data        : 20/11/2013
    modify      : new

*****************************************************************************/
static void mali_gpu_utilization_proc(struct mali_gpu_utilization_data *data)
{
    static int count = 0;

    /*Just lock the gpu for the first 40 seconds after power up, this function be called every 50ns, 40s = 50ns * 800*/
    if(800 == count)
    {
        MALI_DEBUG_PRINT(2,("set the gpu min_freq to 160M after about 40 seconds\n"));
        pmqos_gpu_dfs_limit_min(0);
        count++;
    }

    mali_gpu_utilization_handler(data->utilization_gpu);

    if(count < 800)
    {
        count++;
    }
}

#ifdef CONFIG_PM_RUNTIME
/*****************************************************************************
 function name  : mali_runtime_suspend
 description    : runtime suspend
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_power_mode_change

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_runtime_suspend(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_runtime_suspend() called\n"));

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->runtime_suspend)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->runtime_suspend(device);
    }

    mali_platform_power_mode_change(MALI_POWER_MODE_LIGHT_SLEEP);

    return ret;
}

/*****************************************************************************
 function name  : mali_runtime_resume
 description    : runtime resume
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_power_mode_change

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_runtime_resume(struct device *device)
{
    int ret = 0;

    MALI_DEBUG_PRINT(4, ("mali_runtime_resume() called\n"));

    mali_platform_power_mode_change(MALI_POWER_MODE_ON);

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->runtime_resume)
    {
        /* Need to notify Mali driver about this event */
        ret = device->driver->pm->runtime_resume(device);
    }

    return ret;
}

/*****************************************************************************
 function name  : mali_runtime_resume
 description    : runtime resume
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : mali_platform_power_mode_change

 called         : os

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
static int mali_runtime_idle(struct device *device)
{
    MALI_DEBUG_PRINT(4, ("mali_runtime_idle() called\n"));

    if (NULL != device->driver &&
        NULL != device->driver->pm &&
        NULL != device->driver->pm->runtime_idle)
    {
        /* Need to notify Mali driver about this event */
        int ret = device->driver->pm->runtime_idle(device);
        if (0 != ret)
        {
            return ret;
        }
    }

    pm_runtime_suspend(device);

    return 0;
}

#endif



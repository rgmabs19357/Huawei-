/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : trace_kernel.c
  版 本 号   : 初稿
  生成日期   : 2013年4月15日
  最近修改   :
  功能描述   : Add some API to support trace kernel function by systrace
               tool
  函数列表   :
  修改历史   :
  1.日    期   : 2013年4月15日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/syscalls.h>
#include <linux/debugfs.h>
#include <linux/slab.h>
#include <asm/memory.h>
#include <trace/trace_kernel.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/*B120 start*/
#define POINTMAX      (30)
#define MAX_LEN        (128)

static unsigned long *g_perf_para = NULL;

static char tracedot_name[MODULE_ID_MAX+1][10] = {
    {"tp"},
    {"rec"},
    {"cam"},
    {"stf"},
    {"nup"},
    {"vdec"},
    {"venc"},
    {"vpp"},
    {"aply"},
    {"arec"},
    {"apcm"},
    {"adsp"},
    {"aasp"},
    {"gpu"},
    {"sf"},
    {"mhl"},
    {"reserved"},
};

typedef struct it1_para{
    unsigned long gpu_perf_enable;
    unsigned long sf_perf_enable;
    unsigned long mhl_perf_enable;
}it1_para_type;

typedef struct it2_para{
    unsigned long rec_perf_enable;
    unsigned long stf_perf_enable;
    unsigned long nup_perf_enable;
    unsigned long vdec_perf_enable;
    unsigned long venc_perf_enable;
    unsigned long vpp_perf_enable;
}it2_para_type;

typedef struct codec_para{
   unsigned long aply_perf_enable;
   unsigned long arec_perf_enable;
   unsigned long apcm_perf_enable;
   unsigned long adsp_perf_enable;
   unsigned long aasp_perf_enable;
}codec_para_type;

typedef struct drv4_para{
   unsigned long tp_perf_enable;
}drv4_para_type;

typedef struct perf_para{
    drv4_para_type drv4_para;
    it2_para_type it2_para;
    codec_para_type codec_para;
    it1_para_type it1_para;
}perf_para_type;

static int perf_para_mmap(struct file * file, struct vm_area_struct * vma)
{
    unsigned long paddr = 0;
    unsigned long pfn = 0;
    
    if(!g_perf_para)
    {
        printk(KERN_ERR "perf_para_mmap: g_perf_para is NULL !\n");
        return -EINVAL;
    }
    
    paddr = __pa(g_perf_para);
    pfn = __phys_to_pfn(paddr);
    
    printk(KERN_INFO "perf_para_mmap, paddr [0x%lx]  pfn [0x%lx]\n", paddr, pfn);
    
    return remap_pfn_range(vma, vma->vm_start, pfn, 1, vma->vm_page_prot);
}

static const struct file_operations kernel_trace_fops = {
    .mmap = perf_para_mmap,
};
/*B120 end*/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : trace_begin
 功能描述  : Add log with the "begin format" to trace_marker which will
             be dumped by systrace.
 输入参数  : i
 输出参数  : 无
 返 回 值  : i
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : 陈易超
    修改内容   : 新生成函数

*****************************************************************************/
void trace_begin(long tag, const char*name)
{
    char buf[MAX_LEN];
    long len = 0;
    long fd = 0;
    mm_segment_t fs = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);

    len = sprintf(buf, "B|%ld|%s", sys_getpid(), name);
    fd = sys_open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY, 0);
    sys_write(fd, buf, len);
    sys_close(fd);

    set_fs(fs);
}

/*****************************************************************************
 函 数 名  : trace_end
 功能描述  : Add log with the "end format" to trace_marker which will be
             dumped by systrace.
 输入参数  : i
 输出参数  : 无
 返 回 值  : i
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : 陈易超
    修改内容   : 新生成函数

*****************************************************************************/
void trace_end(long tag)
{
    long fd = 0;
    char buf = 'E';
    mm_segment_t fs = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY, 0);
    sys_write(fd, &buf, 1);
    sys_close(fd);

    set_fs(fs);
}

/*****************************************************************************
 函 数 名  : trace_counter
 功能描述  : Add log with the "counter format" to trace_marker which will
             be dumped by systrace.
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年4月28日
    作    者   : 陈易超
    修改内容   : 新生成函数

*****************************************************************************/
void trace_counter(long tag, const char*name, long value)
{
    char buf[MAX_LEN];
    long len = 0;
    long fd = 0;
    mm_segment_t fs = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);

    len = sprintf(buf, "C|%ld|%s|%ld", sys_getpid(), name, value);
    fd = sys_open("/sys/kernel/debug/tracing/trace_marker", O_WRONLY, 0);
    sys_write(fd, buf, len);
    sys_close(fd);

    set_fs(fs);
}


#ifdef CONFIG_DEBUG_FS
/*****************************************************************************
 函 数 名  : trace_dot
 功能描述  : 在trace_counter的基础上加入了打点开关控制.
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月18日
    作    者   : 蒋孝伟
    修改内容   : 新生成函数

*****************************************************************************/
void trace_dot(unsigned long id, const char* point, long value)
{
#if defined(_DRV_LLT_) ||defined(MED_UT)  ||defined(PC_UT_TEST_ON)
    return;
#endif

    char buf[MAX_LEN];
    unsigned long pt = 0;

    pt = (unsigned long)simple_strtoul(point, NULL, 10);

    if ((id >= MODULE_ID_MAX) || (pt > POINTMAX)){
        return;
    }

    if((*(g_perf_para + id) & (1 << pt)) && (*(g_perf_para + id) & (1 << 31)))
	{
        snprintf(buf, MAX_LEN, "%s%lu", tracedot_name[id], pt);
        trace_counter(0xff, buf, value);
    }
}

static int __init kernel_trace_init(void)
{
    struct dentry *d;
    struct dentry *perf_para_root;
    int i;

    /*In order to mmap g_perf_para to userspace, the memory size should be at least one page.*/
    g_perf_para = (unsigned long *)get_zeroed_page(GFP_KERNEL);
    if (NULL == g_perf_para)
    {
        return -ENOMEM;
    }
    d = debugfs_create_dir("perf_para", NULL);
    perf_para_root = d;
    d = debugfs_create_file("perf_para", S_IWUSR|S_IWGRP|S_IRUGO, perf_para_root, NULL, &kernel_trace_fops);

    for (i=0; i<MODULE_ID_MAX; i++)
    {
        debugfs_create_x32(tracedot_name[i], S_IWUSR|S_IWGRP|S_IRUGO, perf_para_root, (unsigned int *)(g_perf_para + i));
    }

    return 0;
}

static void __exit kernel_trace_exit(void)
{
    return;
}

#else
void trace_dot(unsigned long id, const char* point, long value)
{
    return;
}

static int __init kernel_trace_init(void)
{
    return 0;
}

static void __exit kernel_trace_exit(void)
{
    return;
}

#endif

module_init(kernel_trace_init);
module_exit(kernel_trace_exit);

MODULE_DESCRIPTION("Kernel Trace Driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


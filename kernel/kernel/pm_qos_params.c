/*
 * This module exposes the interface to kernel space for specifying
 * QoS dependencies.  It provides infrastructure for registration of:
 *
 * Dependents on a QoS value : register requests
 * Watchers of QoS value : get notified when target QoS value changes
 *
 * This QoS design is best effort based.  Dependents register their QoS needs.
 * Watchers register to keep track of the current QoS needs of the system.
 *
 * There are 3 basic classes of QoS parameter: latency, timeout, throughput
 * each have defined units:
 * latency: usec
 * timeout: usec <-- currently not used.
 * throughput: kbs (kilo byte / sec)
 *
 * There are lists of pm_qos_objects each one wrapping requests, notifiers
 *
 * User mode requests on a QOS parameter register themselves to the
 * subsystem by opening the device node /dev/... and writing there request to
 * the node.  As long as the process holds a file handle open to the node the
 * client continues to be accounted for.  Upon file release the usermode
 * request is removed and a new qos target is computed.  This way when the
 * request that the application has is cleaned up when closes the file
 * pointer or exits the pm_qos_object will get an opportunity to clean up.
 *
 * Mark Gross <mgross@linux.intel.com>
 */

/*#define DEBUG*/

#include <linux/pm_qos_params.h>
#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/string.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/uaccess.h>

#if defined (CONFIG_ARCH_HI6620)
#include "pwrctrl_multi_def.h"
#include <mach/pwrctrl/pwrctrl_common.h>
#endif
/*
 * locking rule: all changes to requests or notifiers lists
 * or pm_qos_object list and pm_qos_objects need to happen with pm_qos_lock
 * held, taken with _irqsave.  One lock to rule them all
 */
enum pm_qos_type {
    PM_QOS_MAX,     /* return the largest value */
    PM_QOS_MIN      /* return the smallest value */
};

/*
 * Note: The lockless read path depends on the CPU accessing
 * target_value atomically.  Atomic access is only guaranteed on all CPU
 * types linux supports for 32 bit quantites
 */
struct pm_qos_object {
    struct plist_head requests;
    struct blocking_notifier_head *notifiers;
    struct miscdevice pm_qos_power_miscdev;
    char *name;
    s32 target_value;   /* Do not change to 64 bit */
    s32 default_value;
    enum pm_qos_type type;
};

static DEFINE_SPINLOCK(pm_qos_lock);

static struct pm_qos_object null_pm_qos;
static BLOCKING_NOTIFIER_HEAD(cpu_dma_lat_notifier);
static struct pm_qos_object cpu_dma_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_dma_pm_qos.requests),
    .notifiers = &cpu_dma_lat_notifier,
    .name = "cpu_dma_latency",
    .target_value = PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(network_lat_notifier);
static struct pm_qos_object network_lat_pm_qos = {
    .requests = PLIST_HEAD_INIT(network_lat_pm_qos.requests),
    .notifiers = &network_lat_notifier,
    .name = "network_latency",
    .target_value = PM_QOS_NETWORK_LAT_DEFAULT_VALUE,
    .default_value = PM_QOS_NETWORK_LAT_DEFAULT_VALUE,
    .type = PM_QOS_MIN
};


static BLOCKING_NOTIFIER_HEAD(network_throughput_notifier);
static struct pm_qos_object network_throughput_pm_qos = {
    .requests = PLIST_HEAD_INIT(network_throughput_pm_qos.requests),
    .notifiers = &network_throughput_notifier,
    .name = "network_throughput",
    .target_value = PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE,
    .default_value = PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_ARCH_K3V2)
#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_CPU_FREQ_GOV_K3HOTPLUG)
/* sun add 2011-8-22 begin */

static BLOCKING_NOTIFIER_HEAD(cpu_maxprofile_notifier);
static struct pm_qos_object cpu_maxprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_maxprofile_pm_qos.requests),
    .notifiers = &cpu_maxprofile_notifier,
    .name = "cpu_maxprofile",
    .target_value = PM_QOS_CPU_MAXPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_MAXPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(cpu_minprofile_notifier);
static struct pm_qos_object cpu_minprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_minprofile_pm_qos.requests),
    .notifiers = &cpu_minprofile_notifier,
    .name = "cpu_minprofile",
    .target_value = PM_QOS_CPU_MINPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_MINPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(cpu_blkprofile_notifier);
static struct pm_qos_object cpu_blkprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_blkprofile_pm_qos.requests),
    .notifiers = &cpu_blkprofile_notifier,
    .name = "cpu_profile_block",
    .target_value = PM_QOS_CPU_BLKPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_BLKPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(cpu_safeprofile_notifier);
static struct pm_qos_object cpu_safeprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_safeprofile_pm_qos.requests),
    .notifiers = &cpu_safeprofile_notifier,
    .name = "cpu_profile_safe",
    .target_value = PM_QOS_CPU_SAFEPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_SAFEPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(gpu_maxprofile_notifier);
static struct pm_qos_object gpu_maxprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_maxprofile_pm_qos.requests),
    .notifiers = &gpu_maxprofile_notifier,
    .name = "gpu_maxprofile",
    .target_value = PM_QOS_GPU_MAXPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_GPU_MAXPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(gpu_minprofile_notifier);
static struct pm_qos_object gpu_minprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_minprofile_pm_qos.requests),
    .notifiers = &gpu_minprofile_notifier,
    .name = "gpu_minprofile",
    .target_value = PM_QOS_GPU_MINPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_GPU_MINPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(gpu_blkprofile_notifier);
static struct pm_qos_object gpu_blkprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_blkprofile_pm_qos.requests),
    .notifiers = &gpu_blkprofile_notifier,
    .name = "gpu_profile_block",
    .target_value = PM_QOS_GPU_BLKPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_GPU_BLKPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(gpu_safeprofile_notifier);
static struct pm_qos_object gpu_safeprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_safeprofile_pm_qos.requests),
    .notifiers = &gpu_safeprofile_notifier,
    .name = "gpu_profile_safe",
    .target_value = PM_QOS_GPU_SAFEPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_GPU_SAFEPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(ddr_maxprofile_notifier);
static struct pm_qos_object ddr_maxprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_maxprofile_pm_qos.requests),
    .notifiers = &ddr_maxprofile_notifier,
    .name = "ddr_maxprofile",
    .target_value = PM_QOS_DDR_MAXPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_DDR_MAXPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(ddr_minprofile_notifier);
static struct pm_qos_object ddr_minprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_minprofile_pm_qos.requests),
    .notifiers = &ddr_minprofile_notifier,
    .name = "ddr_minprofile",
    .target_value = PM_QOS_DDR_MINPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_DDR_MINPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(ddr_blkprofile_notifier);
static struct pm_qos_object ddr_blkprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_blkprofile_pm_qos.requests),
    .notifiers = &ddr_blkprofile_notifier,
    .name = "ddr_profile_block",
    .target_value = PM_QOS_DDR_BLKPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_DDR_BLKPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(ddr_safeprofile_notifier);
static struct pm_qos_object ddr_safeprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_safeprofile_pm_qos.requests),
    .notifiers = &ddr_safeprofile_notifier,
    .name = "ddr_profile_safe",
    .target_value = PM_QOS_DDR_SAFEPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_DDR_SAFEPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(cpu_numberlock_notifier);
static struct pm_qos_object cpu_numberlock_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_numberlock_pm_qos.requests),
    .notifiers = &cpu_numberlock_notifier,
    .name = "cpu_number_lock",
    .target_value  = PM_QOS_CPU_NUMBER_LOCK_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_NUMBER_LOCK_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(cpu_maxnumber_notifier);
static struct pm_qos_object cpu_maxnumber_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_maxnumber_pm_qos.requests),
    .notifiers = &cpu_maxnumber_notifier,
    .name = "cpu_number_max",
    .target_value  = PM_QOS_CPU_NUMBER_MAX_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_NUMBER_MAX_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(cpu_minnumber_notifier);
static struct pm_qos_object cpu_minnumber_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_minnumber_pm_qos.requests),
    .notifiers = &cpu_minnumber_notifier,
    .name = "cpu_number_min",
    .target_value  = PM_QOS_CPU_NUMBER_MIN_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_NUMBER_MIN_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

static BLOCKING_NOTIFIER_HEAD(cpu_safenumber_notifier);
static struct pm_qos_object cpu_safenumber_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpu_safenumber_pm_qos.requests),
    .notifiers = &cpu_safenumber_notifier,
    .name = "cpu_number_safe",
    .target_value = PM_QOS_CPU_NUMBER_SAFE_DEFAULT_VALUE,
    .default_value = PM_QOS_CPU_NUMBER_SAFE_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(ipps_policy_notifier);
static struct pm_qos_object ipps_policy_pm_qos = {
    .requests = PLIST_HEAD_INIT(ipps_policy_pm_qos.requests),
    .notifiers = &ipps_policy_notifier,
    .name = "ipps_policy",
    .target_value = PM_QOS_IPPS_POLICY_DEFAULT_VALUE,
    .default_value = PM_QOS_IPPS_POLICY_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

#ifdef CONFIG_ARCH_HI6620
/*bus max & min pm qos*/
static BLOCKING_NOTIFIER_HEAD(bus_maxprofile_notifier);
static struct pm_qos_object bus_maxprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(bus_maxprofile_pm_qos.requests),
    .notifiers = &bus_maxprofile_notifier,
    .name = "bus_maxprofile",
    .target_value = PM_QOS_BUS_MAXPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_BUS_MAXPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MIN,
};

static BLOCKING_NOTIFIER_HEAD(bus_minprofile_notifier);
static struct pm_qos_object bus_minprofile_pm_qos = {
    .requests = PLIST_HEAD_INIT(bus_minprofile_pm_qos.requests),
    .notifiers = &bus_minprofile_notifier,
    .name = "bus_minprofile",
    .target_value = PM_QOS_BUS_MINPROFILE_DEFAULT_VALUE,
    .default_value = PM_QOS_BUS_MINPROFILE_DEFAULT_VALUE,
    .type = PM_QOS_MAX,
};

/*cpuidle inttruppt vote pm qos*/
static BLOCKING_NOTIFIER_HEAD(cpuide_int_vote_notifier);
static struct pm_qos_object cpuide_int_vote_pm_qos = {
    .requests = PLIST_HEAD_INIT(cpuide_int_vote_pm_qos.requests),
    .notifiers = &cpuide_int_vote_notifier,
    .name = "cpuidle_int_vote",
    .target_value = PM_QOS_CPUIDLE_INT_DEFAULT_VALUE,
    .default_value = PM_QOS_CPUIDLE_INT_DEFAULT_VALUE ,
    .type = PM_QOS_MIN,
};
#endif

#endif
#else
static BLOCKING_NOTIFIER_HEAD(ddr_minfreq_notifier_head);
static struct pm_qos_object ddr_minfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_minfreq_pm_qos.requests),
    .notifiers = &ddr_minfreq_notifier_head,
    .name = "ddr_minfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MAX
};

static BLOCKING_NOTIFIER_HEAD(ddr_maxfreq_notifier_head);
static struct pm_qos_object ddr_maxfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(ddr_maxfreq_pm_qos.requests),
    .notifiers = &ddr_maxfreq_notifier_head,
    .name = "ddr_maxfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MIN
};

static BLOCKING_NOTIFIER_HEAD(acpu_minfreq_notifier_head);
static struct pm_qos_object acpu_minfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(acpu_minfreq_pm_qos.requests),
    .notifiers = &acpu_minfreq_notifier_head,
    .name = "acpu_minfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MAX
};

static BLOCKING_NOTIFIER_HEAD(acpu_maxfreq_notifier_head);
static struct pm_qos_object acpu_maxfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(acpu_maxfreq_pm_qos.requests),
    .notifiers = &acpu_maxfreq_notifier_head,
    .name = "acpu_maxfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MIN
};

static BLOCKING_NOTIFIER_HEAD(gpu_minfreq_notifier_head);
static struct pm_qos_object gpu_minfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_minfreq_pm_qos.requests),
    .notifiers = &gpu_minfreq_notifier_head,
    .name = "gpu_minfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MAX
};

static BLOCKING_NOTIFIER_HEAD(gpu_maxfreq_notifier_head);
static struct pm_qos_object gpu_maxfreq_pm_qos = {
    .requests = PLIST_HEAD_INIT(gpu_maxfreq_pm_qos.requests),
    .notifiers = &gpu_maxfreq_notifier_head,
    .name = "gpu_maxfreq",
    .target_value  = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .default_value = PM_QOS_PWRCTRL_DFS_DEFAULT_VALUE,
    .type = PM_QOS_MIN
};
#endif

static struct pm_qos_object *pm_qos_array[] = {
    &null_pm_qos,
    &cpu_dma_pm_qos,
    &network_lat_pm_qos,
    &network_throughput_pm_qos,
#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_ARCH_K3V2)
#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_CPU_FREQ_GOV_K3HOTPLUG)
    &cpu_maxprofile_pm_qos,
    &cpu_minprofile_pm_qos,
    &cpu_blkprofile_pm_qos,
    &cpu_safeprofile_pm_qos,
    &gpu_maxprofile_pm_qos,
    &gpu_minprofile_pm_qos,
    &gpu_blkprofile_pm_qos,
    &gpu_safeprofile_pm_qos,
    &ddr_maxprofile_pm_qos,
    &ddr_minprofile_pm_qos,
    &ddr_blkprofile_pm_qos,
    &ddr_safeprofile_pm_qos,
    &cpu_numberlock_pm_qos,
    &cpu_maxnumber_pm_qos,
    &cpu_minnumber_pm_qos,
    &cpu_safenumber_pm_qos,
    &ipps_policy_pm_qos,
#if defined (CONFIG_ARCH_HI6620)
    &bus_maxprofile_pm_qos,
    &bus_minprofile_pm_qos,
    &cpuide_int_vote_pm_qos,
#endif
#endif
#else
    &ddr_minfreq_pm_qos,
    &ddr_maxfreq_pm_qos,
    &acpu_minfreq_pm_qos,
    &acpu_maxfreq_pm_qos,
    &gpu_minfreq_pm_qos,
    &gpu_maxfreq_pm_qos
#endif
};


#if defined (CONFIG_ARCH_HI6620)
struct pm_qos_request_list g_cpunum_policy_qos;
struct pm_qos_request_list g_ddr_policy_qos;
#endif


static ssize_t pm_qos_power_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *f_pos);
static ssize_t pm_qos_power_read(struct file *filp, char __user *buf,
        size_t count, loff_t *f_pos);
static int pm_qos_power_open(struct inode *inode, struct file *filp);
static int pm_qos_power_release(struct inode *inode, struct file *filp);

static const struct file_operations pm_qos_power_fops = {
    .write = pm_qos_power_write,
    .read = pm_qos_power_read,
    .open = pm_qos_power_open,
    .release = pm_qos_power_release,
    .llseek = noop_llseek,
};

static inline void pm_qos_owner_init(struct plist_node *node)
{
    node->owner_id = current->pid;
    strncpy(node->owner_name,current->comm,TASK_COMM_LEN);
}
/* unlocked internal variant */
static inline int pm_qos_get_value(struct pm_qos_object *o)
{
    if (plist_head_empty(&o->requests))
        return o->default_value;

    switch (o->type) {
    case PM_QOS_MIN:
        return plist_first(&o->requests)->prio;

    case PM_QOS_MAX:
        return plist_last(&o->requests)->prio;

    default:
        /* runtime check for not using enum */
        BUG();
    }
}

static inline s32 pm_qos_read_value(struct pm_qos_object *o)
{
    return o->target_value;
}

static inline void pm_qos_set_value(struct pm_qos_object *o, s32 value)
{
    o->target_value = value;
}

static void update_target(struct pm_qos_object *o, struct plist_node *node,
              int del, int value)
{
    unsigned long flags;
    int prev_value, curr_value;

    spin_lock_irqsave(&pm_qos_lock, flags);
    prev_value = pm_qos_get_value(o);

    /*printk("update_target: the pre_vale is %x\n",prev_value);*/
    /* PM_QOS_DEFAULT_VALUE is a signal that the value is unchanged */
    if (value != PM_QOS_DEFAULT_VALUE) {
        /*
         * to change the list, we atomically remove, reinit
         * with new value and add, then see if the extremal
         * changed
         */
        plist_del(node, &o->requests);

        /*printk(KERN_ERR"update,current id:0x%x,current name:%s .\r\n",current->pid,current->comm);*/
        plist_node_init(node, value);
        pm_qos_owner_init(node);

        plist_add(node, &o->requests);
    } else if (del) {
        plist_del(node, &o->requests);
    } else {
        plist_add(node, &o->requests);
    }
    curr_value = pm_qos_get_value(o);
    pm_qos_set_value(o, curr_value);
    spin_unlock_irqrestore(&pm_qos_lock, flags);

    /*printk("update_target: the pre_vale is %x, the curr_value is %x\n",prev_value,curr_value);*/


    if (prev_value != curr_value)
        blocking_notifier_call_chain(o->notifiers,
                         (unsigned long)curr_value,
                         NULL);
}

static int register_pm_qos_misc(struct pm_qos_object *qos)
{
    qos->pm_qos_power_miscdev.minor = MISC_DYNAMIC_MINOR;
    qos->pm_qos_power_miscdev.name = qos->name;
    qos->pm_qos_power_miscdev.fops = &pm_qos_power_fops;

    return misc_register(&qos->pm_qos_power_miscdev);
}

static int find_pm_qos_object_by_minor(int minor)
{
    int pm_qos_class;

    for (pm_qos_class = 0;
        pm_qos_class < PM_QOS_NUM_CLASSES; pm_qos_class++) {
        if (minor ==
            pm_qos_array[pm_qos_class]->pm_qos_power_miscdev.minor)
            return pm_qos_class;
    }
    return -1;
}

/**
 * pm_qos_request - returns current system wide qos expectation
 * @pm_qos_class: identification of which qos value is requested
 *
 * This function returns the current target value.
 */
int pm_qos_request(int pm_qos_class)
{
    return pm_qos_read_value(pm_qos_array[pm_qos_class]);
}
EXPORT_SYMBOL_GPL(pm_qos_request);

int pm_qos_request_active(struct pm_qos_request_list *req)
{
    return req->pm_qos_class != 0;
}
EXPORT_SYMBOL_GPL(pm_qos_request_active);

#ifdef CONFIG_ARCH_K3V2
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG

void pm_qos_verify_request(int pm_qos_class, s32 *value)
{
    s32 tmpv;

    switch (pm_qos_class) {
    case PM_QOS_CPU_MAX_PROFILE:

        tmpv = pm_qos_request(PM_QOS_CPU_MIN_PROFILE);

        if (*value < tmpv) {
            pr_warn("***[%s] CPU_MAX can not be smaller than CPU_MIN.\n",
                __func__);
            pr_warn("***[%s] CPU_MAX REQ=%d CPU_MIN=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

    break;
    case PM_QOS_CPU_MIN_PROFILE:

        tmpv = pm_qos_request(PM_QOS_CPU_MAX_PROFILE);

        if (*value > tmpv) {
            pr_warn("***[%s] CPU_MIN can not be larger than CPU_MAX.\n",
                __func__);
            pr_warn("***[%s] CPU_MIN REQ=%d CPU_MAX=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

        break;
    case PM_QOS_GPU_MAX_PROFILE:

        tmpv = pm_qos_request(PM_QOS_GPU_MIN_PROFILE);

        if (*value < tmpv) {
            pr_warn("***[%s] GPU_MAX can not be smaller than GPU_MIN.\n",
                __func__);
            pr_warn("***[%s] GPU_MAX REQ=%d GPU_MIN=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

        break;
    case PM_QOS_GPU_MIN_PROFILE:

        tmpv = pm_qos_request(PM_QOS_GPU_MAX_PROFILE);

        if (*value > tmpv) {
            pr_warn("***[%s] GPU_MIN can not be larger than GPU_MAX.\n",
                __func__);
            pr_warn("***[%s] GPU_MIN REQ=%d GPU_MAX=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

        break;
    case PM_QOS_DDR_MAX_PROFILE:

        tmpv = pm_qos_request(PM_QOS_DDR_MIN_PROFILE);

        if (*value < tmpv) {
            pr_warn("***[%s] DDR_MAX can not be smaller than DDR_MIN.\n",
                __func__);
            pr_warn("***[%s] DDR_MAX REQ=%d DDR_MIN=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

        break;
    case PM_QOS_DDR_MIN_PROFILE:

        tmpv = pm_qos_request(PM_QOS_DDR_MAX_PROFILE);

        if (*value > tmpv) {
            pr_warn("***[%s] DDR_MIN can not be larger than DDR_MAX.\n",
                __func__);
            pr_warn("***[%s] DDR_MIN REQ=%d DDR_MAX=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }

        break;
    case PM_QOS_CPU_NUMBER_MAX:
        tmpv = pm_qos_request(PM_QOS_CPU_NUMBER_MIN);

        if (*value < tmpv) {
            pr_warn("***[%s] CPUNUMBER_MAX can not be smaller than CPUNUMBER_MIN.\n",
                __func__);
            pr_warn("***[%s] CPUNUMBER_MAX REQ=%d CPUNUMBER_MIN=%d.\n",
                __func__, *value, tmpv);

            *value = tmpv;
        }
        break;
    case PM_QOS_CPU_NUMBER_MIN:
        tmpv = pm_qos_request(PM_QOS_CPU_NUMBER_MAX);

        if (*value > tmpv) {
            pr_warn("***[%s] CPUNUMBER_MIN can not be larger than CPUNUMBER_MAX.\n",
                __func__);
            pr_warn("***[%s] CPUNUMBER_MIN REQ=%d CPUNUMBER_MAX=%d.\n", __func__,
                *value, tmpv);

            *value = tmpv;
        }
        break;
    default:
        break;
    }
}

#endif
#endif
struct pm_qos_request_list g_test_pm_qos[10];

void test_pm_req(int index, int pm_qos_class, s32 value)
{
    printk(KERN_ERR"req(%d) pm_qos_class:%d value:%d\n", index, pm_qos_class, value);
    pm_qos_add_request(&g_test_pm_qos[index], pm_qos_class, value);
}

void test_pm_update(int index, s32 value)
{
    printk(KERN_ERR"update(%d) value:%d\n",index, value);
    pm_qos_update_request(&g_test_pm_qos[index], value);
}

void test_pm_rm(int index)
{
    printk(KERN_ERR"rm(%d)\n",index);
    pm_qos_remove_request(&g_test_pm_qos[index]);
}

void pm_qos_print_owner(int pm_qos_class)
{
    struct pm_qos_object *o =  pm_qos_array[pm_qos_class];
	struct plist_node *node_pos,*first;

    if (plist_head_empty(&o->requests))
    {
        printk(KERN_ERR"pm_qos_print_owner list null.\n");
        return ;
    }

	node_pos = first = plist_first(&o->requests);
	plist_for_each(node_pos, first) {
		printk(KERN_ERR"prio:0x%x,owner id:0x%x,owner name:%s\r\n",
		node_pos->prio,node_pos->owner_id,node_pos->owner_name);
	}
}

/**
 * pm_qos_add_request - inserts new qos request into the list
 * @dep: pointer to a preallocated handle
 * @pm_qos_class: identifies which list of qos request to use
 * @value: defines the qos request
 *
 * This function inserts a new entry in the pm_qos_class list of requested qos
 * performance characteristics.  It recomputes the aggregate QoS expectations
 * for the pm_qos_class of parameters and initializes the pm_qos_request_list
 * handle.  Caller needs to save this handle for later use in updates and
 * removal.
 */

void pm_qos_add_request(struct pm_qos_request_list *dep,
            int pm_qos_class, s32 value)
{
    struct pm_qos_object *o =  pm_qos_array[pm_qos_class];
    int new_value;

#if defined (CONFIG_ARCH_HI6620)
    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_QOS))
    {
        /*WARN(1, KERN_ERR "pm_qos disable\n");*/
        return;
    }
#endif

    if (pm_qos_request_active(dep)) {
        WARN(1, KERN_ERR "pm_qos_add_request() called for already added request\n");
        return;
    }

    if (value == PM_QOS_DEFAULT_VALUE)
        new_value = o->default_value;
    else
        new_value = value;
#ifdef CONFIG_ARCH_K3V2
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
    pm_qos_verify_request(pm_qos_class, &new_value);
#endif
#endif
    plist_node_init(&dep->list, new_value);
    /*printk(KERN_ERR"request,current id:0x%x,current name:%s .\r\n",current->pid,current->comm);*/

    pm_qos_owner_init(&dep->list);

    dep->pm_qos_class = pm_qos_class;
    update_target(o, &dep->list, 0, PM_QOS_DEFAULT_VALUE);
}
EXPORT_SYMBOL_GPL(pm_qos_add_request);

/**
 * pm_qos_update_request - modifies an existing qos request
 * @pm_qos_req : handle to list element holding a pm_qos request to use
 * @value: defines the qos request
 *
 * Updates an existing qos request for the pm_qos_class of parameters along
 * with updating the target pm_qos_class value.
 *
 * Attempts are made to make this code callable on hot code paths.
 */
void pm_qos_update_request(struct pm_qos_request_list *pm_qos_req,
               s32 new_value)
{
    s32 temp;
    struct pm_qos_object *o;

#if defined (CONFIG_ARCH_HI6620)
    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_QOS))
    {
        /*WARN(1, KERN_ERR "pm_qos disable\n");*/
        return;
    }
#endif

    if (!pm_qos_req) /*guard against callers passing in null */
        return;

    if (!pm_qos_request_active(pm_qos_req)) {
        WARN(1, KERN_ERR "pm_qos_update_request() called for unknown object\n");
        return;
    }

    o = pm_qos_array[pm_qos_req->pm_qos_class];

    if (new_value == PM_QOS_DEFAULT_VALUE)
        temp = o->default_value;
    else
        temp = new_value;

#ifdef CONFIG_ARCH_K3V2
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG  
    pm_qos_verify_request(pm_qos_req->pm_qos_class, &temp);
#endif
#endif

    if (temp != pm_qos_req->list.prio)
        update_target(o, &pm_qos_req->list, 0, temp);
}
EXPORT_SYMBOL_GPL(pm_qos_update_request);

/**
 * pm_qos_remove_request - modifies an existing qos request
 * @pm_qos_req: handle to request list element
 *
 * Will remove pm qos request from the list of requests and
 * recompute the current target value for the pm_qos_class.  Call this
 * on slow code paths.
 */
void pm_qos_remove_request(struct pm_qos_request_list *pm_qos_req)
{
    struct pm_qos_object *o;

#if defined (CONFIG_ARCH_HI6620)
    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_QOS))
    {
        /*WARN(1, KERN_ERR "pm_qos disable\n");*/
        return;
    }
#endif

    if (pm_qos_req == NULL)
        return;
        /* silent return to keep pcm code cleaner */

    if (!pm_qos_request_active(pm_qos_req)) {
        WARN(1, KERN_ERR "pm_qos_remove_request() called for unknown object\n");
        return;
    }

    o = pm_qos_array[pm_qos_req->pm_qos_class];
    update_target(o, &pm_qos_req->list, 1, PM_QOS_DEFAULT_VALUE);
    memset(pm_qos_req, 0, sizeof(*pm_qos_req));
}
EXPORT_SYMBOL_GPL(pm_qos_remove_request);

/**
 * pm_qos_add_notifier - sets notification entry for changes to target value
 * @pm_qos_class: identifies which qos target changes should be notified.
 * @notifier: notifier block managed by caller.
 *
 * will register the notifier into a notification chain that gets called
 * upon changes to the pm_qos_class target value.
 */
int pm_qos_add_notifier(int pm_qos_class, struct notifier_block *notifier)
{
    int retval;

    retval = blocking_notifier_chain_register(
            pm_qos_array[pm_qos_class]->notifiers, notifier);

    return retval;
}
EXPORT_SYMBOL_GPL(pm_qos_add_notifier);

/**
 * pm_qos_remove_notifier - deletes notification entry from chain.
 * @pm_qos_class: identifies which qos target changes are notified.
 * @notifier: notifier block to be removed.
 *
 * will remove the notifier from the notification chain that gets called
 * upon changes to the pm_qos_class target value.
 */
int pm_qos_remove_notifier(int pm_qos_class, struct notifier_block *notifier)
{
    int retval;

    retval = blocking_notifier_chain_unregister(
            pm_qos_array[pm_qos_class]->notifiers, notifier);

    return retval;
}
EXPORT_SYMBOL_GPL(pm_qos_remove_notifier);

static int pm_qos_power_open(struct inode *inode, struct file *filp)
{
    long pm_qos_class;

    pm_qos_class = find_pm_qos_object_by_minor(iminor(inode));
    if (pm_qos_class >= 0) {
        struct pm_qos_request_list *req = kzalloc(sizeof(*req), GFP_KERNEL);
        if (!req)
            return -ENOMEM;

        pm_qos_add_request(req, pm_qos_class, PM_QOS_DEFAULT_VALUE);
        filp->private_data = req;

        if (filp->private_data)
            return 0;
    }

    return -EPERM;
}

static int pm_qos_power_release(struct inode *inode, struct file *filp)
{
    struct pm_qos_request_list *req;

    req = filp->private_data;
    pm_qos_remove_request(req);
    kfree(req);

    return 0;
}


static ssize_t pm_qos_power_read(struct file *filp, char __user *buf,
        size_t count, loff_t *f_pos)
{
    s32 value;
    unsigned long flags;
    struct pm_qos_object *o;
    struct pm_qos_request_list *pm_qos_req = filp->private_data;

    if (!pm_qos_req)
        return -EINVAL;
    if (!pm_qos_request_active(pm_qos_req))
        return -EINVAL;

    o = pm_qos_array[pm_qos_req->pm_qos_class];
    spin_lock_irqsave(&pm_qos_lock, flags);
    value = pm_qos_get_value(o);
    spin_unlock_irqrestore(&pm_qos_lock, flags);

    return simple_read_from_buffer(buf, count, f_pos, &value, sizeof(s32));
}

static ssize_t pm_qos_power_write(struct file *filp, const char __user *buf,
        size_t count, loff_t *f_pos)
{
    s32 value;
    struct pm_qos_request_list *pm_qos_req;

    if (count == sizeof(s32)) {
        if (copy_from_user(&value, buf, sizeof(s32)))
            return -EFAULT;
    } else if (count <= 11) { /* ASCII perhaps? */
        char ascii_value[11];
        unsigned long int ulval;
        int ret;

        if (copy_from_user(ascii_value, buf, count))
            return -EFAULT;

        if (count > 10) {
            if (ascii_value[10] == '\n')
                ascii_value[10] = '\0';
            else
                return -EINVAL;
        } else {
            ascii_value[count] = '\0';
        }
        ret = strict_strtoul(ascii_value, 16, &ulval);
        if (ret) {
            pr_debug("%s, 0x%lx, 0x%x\n", ascii_value, ulval, ret);
            return -EINVAL;
        }
        value = (s32)lower_32_bits(ulval);
    } else {
        return -EINVAL;
    }

    pm_qos_req = filp->private_data;
    pm_qos_update_request(pm_qos_req, value);

    return count;
}


static int __init pm_qos_power_init(void)
{
    int ret = 0;

    ret = register_pm_qos_misc(&cpu_dma_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR "pm_qos_param: cpu_dma_latency setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&network_lat_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR "pm_qos_param: network_latency setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&network_throughput_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: network_throughput setup failed\n");
        return ret;
    }

#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_ARCH_K3V2)
#if defined (CONFIG_ARCH_HI6620) || defined (CONFIG_CPU_FREQ_GOV_K3HOTPLUG)
    /* sun add 2011-8-22 begin */

    ret = register_pm_qos_misc(&cpu_maxprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: cpu_maxprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_minprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: cpu_minprofile setup failed\n");

        return ret;
    }
    ret = register_pm_qos_misc(&cpu_blkprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: cpu_blkprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_safeprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: cpu_safeprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&gpu_maxprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_maxprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&gpu_minprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_minprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&gpu_blkprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_blkprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&gpu_safeprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_safeprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&ddr_maxprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_maxprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&ddr_minprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_minprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&ddr_blkprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_blkprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&ddr_safeprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_safeprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_numberlock_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: cpu_numberlock setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_maxnumber_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:cpu_maxnumber setup failed.\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_minnumber_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:cpu_minnumber setup failed.\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpu_safenumber_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:cpu_safenumber setup failed.\n");
        return ret;
    }

    ret = register_pm_qos_misc(&ipps_policy_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:ipps_policy setup failed.\n");
        return ret;
    }

    /* sun add 2011-8-22 end */
#ifdef CONFIG_ARCH_HI6620
    ret = register_pm_qos_misc(&bus_maxprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: bus_maxprofile setup failed\n");
        return ret;
    }
    ret = register_pm_qos_misc(&bus_minprofile_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:bus_minprofile setup failed.\n");
        return ret;
    }
    ret = register_pm_qos_misc(&cpuide_int_vote_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param:cpuidle_int setup failed.\n");
        return ret;
    }
#endif
#endif
#else
    ret = register_pm_qos_misc(&ddr_minfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_minfreq_pm_qos setup failed\n");
        return ret;
    }

    ret = register_pm_qos_misc(&ddr_maxfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: ddr_maxfreq_pm_qos setup failed\n");
        return ret;
    }

    ret = register_pm_qos_misc(&acpu_minfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: acpu_minfreq_pm_qos setup failed\n");
        return ret;
    }

    ret = register_pm_qos_misc(&acpu_maxfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: acpu_maxfreq_pm_qos setup failed\n");
        return ret;
    }

    ret = register_pm_qos_misc(&gpu_minfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_minfreq_pm_qos setup failed\n");
        return ret;
    }

    ret = register_pm_qos_misc(&gpu_maxfreq_pm_qos);
    if (ret < 0) {
        printk(KERN_ERR
            "pm_qos_param: gpu_maxfreq_pm_qos setup failed\n");
        return ret;
    }
#endif

#if defined (CONFIG_ARCH_HI6620)
	pm_qos_add_request(&g_cpunum_policy_qos, PM_QOS_CPU_NUMBER_MIN,PM_QOS_CPU_NUMBER_MIN_VALUE_FOR_DISPLAY);
	pm_qos_add_request(&g_ddr_policy_qos, PM_QOS_DDR_MIN_PROFILE,PM_QOS_DDR_MINPROFILE_VALUE_FOR_DISPLAY);
#endif
    return ret;
}

late_initcall(pm_qos_power_init);

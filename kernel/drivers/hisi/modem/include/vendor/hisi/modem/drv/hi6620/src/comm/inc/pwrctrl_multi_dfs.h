#ifndef __PWRCTRL_MULTI_DFS_H__
#define __PWRCTRL_MULTI_DFS_H__

#include "pwrctrl_multi_def.h"
#include "drv_dpm.h"

/*
 *  DFS return types
 */
#define dfs_ret                 int
#define DFS_INVALID_ID          (-1)

/*
 *  DFS Logs
 */
#define DFS_LOG_INFO(fmt, arg0, arg1, arg2)     \
    PWC_TRACE(PWC_LOG_INFO,    fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_WARNING(fmt, arg0, arg1, arg2)  \
    PWC_TRACE(PWC_LOG_WARNING, fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_ERROR(fmt, arg0, arg1, arg2)    \
    PWC_TRACE(PWC_LOG_ERROR,   fmt, arg0, arg1, arg2, 0, 0, 0)

#define DFS_LOG_MEM(info, addr, size)           \
    PWC_LOG_MEM(info, addr, size)

/*
 *  DFS state mask and operations.
 */
typedef enum
{
    INITED      = 0x1,
    DVFS_ENABLE = 0x2,
    AVS_ENABLE  = 0x4,
    DFS_ENABLE  = 0x8,
    LOCKED      = 0x10
} dfs_state_mask;

typedef enum
{
    BUS_DFS_BIT_ACPU = 0,
    BUS_DFS_BIT_CCPU = 16,
    BUS_DFS_BIT_MAX  = 32
}BUS_DFS_BIT_DEF;

typedef enum
{
    DFS_CORE_ACPU = 0x0,
    DFS_CORE_CCPU = 0x1,
    DFS_CORE_MAX
}DFS_CORE_ID;

#define BUS_DFS_BIT_MASK (0x10001)

#define DFS_STATE_INIT(x, v)        ((x) = (v))
#define DFS_STATE_SET(x, s)         (pwc_set_bits((u32_t)&(x), (s)))
#define DFS_STATE_CLR(x, s)         (pwc_clr_bits((u32_t)&(x), (s)))
#define DFS_STATE_IS(x, s)          (pwc_is_bits_set((u32_t)&(x), (s)))

/*
 *  DFS Device
 */
#define DFS_DEVICE_ID_ACPU          (0)
#define DFS_DEVICE_ID_CCPU          (1)
#define DFS_DEVICE_ID_DDR           (2)
#define DFS_DEVICE_ID_GPU           (3)
#define DFS_DEVICE_ID_BUS           (4)

#define DFS_DEVICE_ACPU_NAME        "acpu"
#define DFS_DEVICE_CCPU_NAME        "ccpu"
#define DFS_DEVICE_DDR_NAME         "ddr"
#define DFS_DEVICE_GPU_NAME         "gpu"
#define DFS_DEVICE_BUS_NAME         "bus"

/*
 *  DFS Device Policy
 */
#define DFS_POLICY_ID_ACPU          (0)
#define DFS_POLICY_ID_CCPU          (1)
#define DFS_POLICY_ID_DDR           (2)
#define DFS_POLICY_ID_GPU           (3)

#define DFS_POLICY_ACPU_NAME        "acpu_policy"
#define DFS_POLICY_CCPU_NAME        "ccpu_policy"
#define DFS_POLICY_DDR_NAME         "ddr_policy"
#define DFS_POLICY_GPU_NAME         "gpu_policy"

/*
 *  DFS Device QoS
 */
#define DFS_QOS_ID_ACPU_MINFREQ     (DFS_QOS_ID_ACPU_MINFREQ_E)
#define DFS_QOS_ID_ACPU_MAXFREQ     (DFS_QOS_ID_ACPU_MAXFREQ_E)
#define DFS_QOS_ID_CCPU_MINFREQ     (DFS_QOS_ID_CCPU_MINFREQ_E)
#define DFS_QOS_ID_CCPU_MAXFREQ     (DFS_QOS_ID_CCPU_MAXFREQ_E)
#define DFS_QOS_ID_DDR_MINFREQ      (DFS_QOS_ID_DDR_MINFREQ_E)
#define DFS_QOS_ID_DDR_MAXFREQ      (DFS_QOS_ID_DDR_MAXFREQ_E)
#define DFS_QOS_ID_GPU_MINFREQ      (DFS_QOS_ID_GPU_MINFREQ_E)
#define DFS_QOS_ID_GPU_MAXFREQ      (DFS_QOS_ID_GPU_MAXFREQ_E)
#define DFS_QOS_ID_BUS_MINFREQ      (DFS_QOS_ID_BUS_MINFREQ_E)
#define DFS_QOS_ID_BUS_MAXFREQ      (DFS_QOS_ID_BUS_MAXFREQ_E)


#define DFS_QOS_ACPU_MINFREQ_NAME   "acpu_minfreq"
#define DFS_QOS_ACPU_MAXFREQ_NAME   "acpu_maxfreq"
#define DFS_QOS_CCPU_MINFREQ_NAME   "ccpu_minfreq"
#define DFS_QOS_CCPU_MAXFREQ_NAME   "ccpu_maxfreq"
#define DFS_QOS_DDR_MINFREQ_NAME    "ddr_minfreq"
#define DFS_QOS_DDR_MAXFREQ_NAME    "ddr_maxfreq"
#define DFS_QOS_GPU_MINFREQ_NAME    "gpu_minfreq"
#define DFS_QOS_GPU_MAXFREQ_NAME    "gpu_maxfreq"
#define DFS_QOS_BUS_MINFREQ_NAME    "bus_minfreq"
#define DFS_QOS_BUS_MAXFREQ_NAME    "bus_maxfreq"

/*bus dfs freq def*/
#define DFS_BUS_FREQ_SYS (300*1000)
#define DFS_BUS_FREQ_MAX (150*1000)
#define DFS_BUS_FREQ_MIN (75*1000)

#endif

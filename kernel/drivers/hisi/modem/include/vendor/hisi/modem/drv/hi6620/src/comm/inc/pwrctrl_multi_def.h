/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_multi_def.h
  版 本 号   : 初稿
  生成日期   : 2012年9月6日
  最近修改   :
  功能描述   : 低功耗多核公共的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月6日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#ifndef __PWRCTRL_MULTI_DEF_H__
#define __PWRCTRL_MULTI_DEF_H__

#include "pwrctrl_multi_dfs_asm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
/*just for temp stub*/
/*
#ifndef FEATURE_ON
#define FEATURE_ON              1
#endif
#define FEATURE_POWER_DRV       FEATURE_ON
*/

#if defined (WIN32) || defined (GENERIC_PROJECT)
#define local_t
#else
#define local_t static
#endif

#define bool_t  unsigned int
#define void_t  void

#define s8_t    char
#define s16_t   short
#define s32_t   int

#define u8_t    unsigned char
#define u16_t   unsigned short
#define u32_t   unsigned int

#ifndef NULL
#define NULL ((void*)0)
#endif
#ifndef BIT
#define BIT(x)                      ((unsigned)0x1 << (x))
#endif
#define BITMSK(x)                   (BIT(x) << 16)

#ifdef WIN32
#define PWC_TASK_LOOP()
#else
#define PWC_TASK_LOOP()             for ( ; ; )
#endif

#if defined (WIN32) || defined (GENERIC_PROJECT)
#define RET_CODE_IF_NOT_OK(func)    (func)
#define RET_ERR_IF(cond)            (cond)
#define LOG_IF(cond)                (cond)
#else
#define RET_CODE_IF_NOT_OK(func)                             \
{                                                            \
    dfs_ret _ERR_CODE = func;                                \
    if(_ERR_CODE != RET_OK)                                  \
    {                                                        \
        PWC_TRACE(PWC_LOG_ERROR, #func" return %d (FILE:%s, LINE:%d)", _ERR_CODE, __FILE__, __LINE__, 0, 0, 0);  \
        return _ERR_CODE;                                    \
    }                                                        \
}

#define RET_ERR_IF(cond)                                     \
    if(cond)                                                 \
    {                                                        \
        PWC_TRACE(PWC_LOG_ERROR, #cond" (FILE:%s, LINE:%d)", __FILE__, __LINE__, 0, 0, 0, 0);  \
        return RET_ERR;                                      \
    }

#define LOG_IF(cond)                                         \
    if(cond)                                                 \
    {                                                        \
        PWC_TRACE(PWC_LOG_INFO,  #cond" (FILE:%s, LINE:%d)", __FILE__, __LINE__, 0, 0, 0, 0);  \
    }
#endif

/*log output*/
#define MODULE_PWRCTRL              (0x20)

/*****************************************************************************/
#define PWRCTRL_SWITCH_OFF          (0)
#define PWRCTRL_SWITCH_ON           (1)

#define PWRCTRL_FALSE               (0)
#define PWRCTRL_TRUE                (1)

#define PWRCTRL_BOOT_SYN_TIME       (100)            /*单位: slice timer 33us*/
#define PWRCTRL_BOOT_SYNC_BIT       (BIT(16))

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#define PWRCTRL_DELAY_TCXO_1US(x)       (x*19)              /*单位-近似 1us    (19200000/1000000)*/
#define PWRCTRL_DELAY_32K_100US(x)      (x*3)               /*单位-近似 100 us  (32768/1000000)*100 */

#define PWRCTRL_REG_MAX_VALUE       (0xFFFFFFFF)


#define PWRCTRL_SLICETIMER_XLOAD    (PWRCTRL_REG_MAX_VALUE)
#define PWRCTRL_SLICE_CLK           (32)
#define PWRCTRL_SLICE_UNIT_CONV     (1000)           /*s -> us*/
#define PWC_SLICE_TIMER_ID          (10)


#define MCA_OBJ_BEGIN (0)
#define MCA_OBJ_CPU (0)
#define MCA_OBJ_GPU (1)
#define MCA_OBJ_DDR (2)
#define MCA_OBJ_CCPU (3)
#define MCA_OBJ_BUS (4)
#define MCA_OBJ_END MCA_OBJ_BUS /*如果增加OBJ，请更新END*/
#define MCA_OBJ_NUM (MCA_OBJ_END + 1)

#define MCA_PARAM_BEGIN (0)
#define MCA_PARAM_MAX (0)
#define MCA_PARAM_MIN (1)
#define MCA_PARAM_LOCK (2)
#define MCA_PARAM_SAFE (3)
#define MCA_PARAM_END MCA_PARAM_SAFE /*如果增加PARAM，请更新END*/
#define MCA_PARAM_NUM (MCA_PARAM_END + 1)

#define CPU_IDLE_STAT_VALID 0x55aa
#define CPU_IDLE_STAT_INVALID 0
/*       31~16                  15~0   */
/*       magic            cpuidle state*/
#define CPUIDLE_STATE_MAGIC_START_BIT 16
#define CPUIDLE_STATE_START_BIT 0

/*#define POLICY_MAX_TOTAL_SIZE (MAX_PROFILE_NUM * POLICY_LEN)*/

#define BYTES_PER_UINT32 (4)

/*更改profile size时请注意更新PROFILE_MAX_TOTAL_SIZE的值*/
#define ACPU_PROFILE_LEN (20)
#define ACPU_PROFILE_NUM (6)

#define DDR_PROFILE_LEN (22)
#define DDR_PROFILE_NUM (6)

#define GPU_PROFILE_LEN (1)
#define GPU_PROFILE_NUM (4)

#define CPU_PROFILE_SIZE (ACPU_PROFILE_LEN * ACPU_PROFILE_NUM * BYTES_PER_UINT32)
#define DDR_PROFILE_SIZE (DDR_PROFILE_LEN * DDR_PROFILE_NUM * BYTES_PER_UINT32)
#define GPU_PROFILE_SIZE (GPU_PROFILE_LEN * GPU_PROFILE_NUM * BYTES_PER_UINT32)

#define PROFILE_MAX_TOTAL_SIZE DDR_PROFILE_SIZE

#define HPM_SEARCH_VOLT_ENABLE
#define HPM_SEARCH_VOLT_ACPU_ENABLE
#define HPM_SEARCH_VOLT_DDR_ENABLE
#define FREQ_MAX_NUM 6
#define VALID_VOLTAGE_MAGIC 0x5a5ac5c5

#define ACPU_FREQ_1_6G 1596000
#define ACPU_FREQ_1_8G 1795000
#define ACPU_FREQ_2_0G 1996000
#define ACPU_PLL_1_75_G 0x524416d/*1752M*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/* 返回值定义 */
typedef enum
{
    RET_ERR_PARAM_NULL = -0xF000,
    RET_ERR_PARAM_INVALID,
    RET_ERR_OVERFLOW,
    RET_ERR_INSUFFICIENT,
    RET_ERR_LIMITED,
    RET_ERR_NOT_FOUND,
    RET_ERR_NOT_OPEN,
    RET_ERR_DUPLICATE,
    RET_ERR_CONNECT_FAIL,
    RET_ERR_TIME_OUT,
    RET_ERR_UNKNOWN,
    RET_ERR = -1,
    RET_OK = 0
} EM_PWC_RET;


/* 打印通道选择定义 */
typedef enum
{
    PWC_DEBUG_UART = 0,     /* 0x0:UART                                  */
    PWC_DEBUG_LOG,          /* 0x1:trace log                             */
    PWC_DEBUG_BUG,          /* 0x2:定位使用                              */
    PWC_DEBUG_DRX,          /* 0x3:通信模块                              */
    PWC_DEBUG_OFF = 0xff    /* 0x4:关闭                                  */
} EM_PWC_LOG_CHAN;


/* 低功耗特性开关定义 */
typedef enum
{
    PWC_SWITCH_CSLEEP = 0,      /* 0x0: C核上下电   */
    PWC_SWITCH_ASLEEP,          /* 0x1: A核上下电   */
    PWC_SWITCH_MSLEEP,          /* 0x2: 系统外设区上下电     */
    PWC_SWITCH_HIFI,            /* 0x3: hifi 上下电          */

    PWC_SWITCH_CDFS,            /* 0x4: C核动态调频          */
    PWC_SWITCH_ADFS,            /* 0x5: A核动态调频调压、AVS */
    PWC_SWITCH_DDFS,            /* 0x6: DDR 动态调频         */
    PWC_SWITCH_GDFS,            /* 0x7: GPU动态调频调压      */

    PWC_SWITCH_CAVS,            /* 0x8: C核动态调压          */
    PWC_SWITCH_AAVS,            /* 0x9: A核动态调压 */
    PWC_SWITCH_DAVS,            /* 0xA: DDR 动态调压         */
    PWC_SWITCH_GAVS,            /* 0xB: GPU动态调压          */

    PWC_SWITCH_CPUIDLE,         /* 0xC: ACPU cpu IDLE        */
    PWC_SWITCH_BDFS,            /* 0xD: bus调频              */
    PWC_SWITCH_AUTOHOTPLUG,     /* 0xE: AUTO PLUG            */
    PWC_SWITCH_QOS,             /* 0xF: dvfs qos             */

    PWC_SWITCH_MNTN = 16,       /* bit16: 可维可测           */
    PWC_SWITCH_DEBPT,           /* bit17: 调试开关           */
    PWC_SWITCH_APNTFLAG,        /* bit18: 打印至A核          */

    PWC_SWITCH_BUTT = 32        /* 边界值 */

} EM_PWC_SWITCH;

typedef enum {
    PWC_FUNC_INVALID = 0xFF,
    PWC_FUNC_DFS_ENABLE = 1,
    PWC_FUNC_AVS_ENABLE = 2,
    PWC_FUNC_DVFS_ENABLE = 4,
    PWC_FUNC_DFS_DISABLE = 8,
    PWC_FUNC_AVS_DISABLE = 0x10,
    PWC_FUNC_DVFS_DISABLE = 0x20,
    PWC_FUNC_BUTT
}EM_PWC_FUNC;

/* 模块的上电状态 */
typedef enum
{
    PWC_STATUS_ACORE = 0,       /* 0x0: A核上电标志   */
    PWC_STATUS_CCORE = 1,       /* 0x1: C核上电标志   */
    PWC_STATUS_HIFI =  2,       /* 0x2: HIFI核上电标志   */
    PWC_STATUS_BUTT = 32        /* 边界值 */

} EM_PWC_STATUS;

/* cpu idle status */
typedef enum
{
    CPU_IDLE_INVALID = -1,
    CPU_IDLE_C0,
    CPU_IDLE_C1,
    CPU_IDLE_C2,
    CPU_IDLE_C3, /*以上为IDLE状态*/
    CPU_IDLE_C4, /*表示全系统下电*/
    CPU_IDLE_MAX
} CPU_IDLE_STAT;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct ST_PWC_SWITCH_STRU_S
{
    bool_t cSleep     :1; /*bit0*/
    bool_t aSleep     :1; /*bit1*/
    bool_t mSleep     :1; /*bit2*/
    bool_t hifi       :1; /*bit3*/

    bool_t cDfs       :1; /*bit4*/
    bool_t aDfs       :1; /*bit5*/
    bool_t dDfs       :1; /*bit6*/
    bool_t gDfs       :1; /*bit7*/

    bool_t cAvs       :1; /*bit8*/
    bool_t aAvs       :1; /*bit9*/
    bool_t dAvs       :1; /*bit10*/
    bool_t gAvs       :1; /*bit11*/
    bool_t cpuIdle    :1; /*bit12*/
    bool_t bDfs       :1; /*bit13*/
    bool_t aHotPlug   :1; /*bit14*/

    bool_t qos        :1; /*bit15*/

    bool_t mntn       :1; /*bit16*/
    bool_t debPt      :1; /*bit17*/
    bool_t apntFlag   :1; /*bit18*/
}ST_PWC_SWITCH_STRU;

typedef struct ST_PWC_STATUS_STRU_S
{
    bool_t ACore     :1; /*bit0*/
    bool_t CCore     :1; /*bit1*/
    bool_t HIFI      :1; /*bit2*/

}ST_PWC_STATUS_STRU;

struct freq_volt_stru
{
    unsigned int magic;
    unsigned int support_freq_num;
    unsigned int support_freq_max;
    unsigned int start_prof;
    unsigned int vol[FREQ_MAX_NUM + 1]; /*每个频点的电压*/
};

/******z00241656 add for freqdump begin********/
struct freqdump
{
    unsigned int freq_acpu_freq_last;
    unsigned int freq_acpu_freq_cur;
    
    unsigned int freq_acpu_load;
    unsigned int freq_acpu_core_online;
    unsigned int freq_every_acpu_load[4];

    unsigned int freq_ddr_freq_last;
    unsigned int freq_ddr_freq_cur;
    unsigned int freq_ddr_data_load;
    unsigned int freq_ddr_cmd_load;

    unsigned int freq_ccpu_freq_last;
    unsigned int freq_ccpu_freq_cur;
    unsigned int freq_ccpu_load;

};
/******z00241656 add for freqdump end********/

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
typedef void_t          (*PWCVFUNCPTRV)(void_t);
typedef s32_t           (*PWCFUNCPTR0)(void_t);
typedef s32_t           (*PWCFUNCPTR2)(u32_t arg1, u32_t arg2);



/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_multi_sleep.h */


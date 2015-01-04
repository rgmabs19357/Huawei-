/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_common.h
  版 本 号   : 初稿
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic 公共头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PMIC_H__
#define __PMIC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/platform_device.h>
#include <hisi/regulator_info.h>

#ifdef    _DRV_LLT_
#include "drv_global.h"
#else
typedef    unsigned int    BSP_U32;
typedef    unsigned short  BSP_U16;
typedef    unsigned char   BSP_U8;
typedef    signed int      BSP_S32;
typedef    void            BSP_VOID;
#endif
/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define     PMU_LOCAL   static
#define     BSP_OK     (0)
#define     BSP_ERROR  (-1)

#define PMU_REGISTER_DATA_BIT (8)
#define PMU_IRQ_VALUE_CLEAR   (0xFF)

/* 跟regulator_pmic_info.h保持一致 */
#define PMU_CHANNEL_ID_BUTT (LVS_ID_END+1)

#define PMU_POWER_NAME_SIZE             (16)    /*电源名长度*/

/*regulator ops 模块返回值定义*/
#define PMIC_MODULE_ERROR -1       /*错误返回值*/
#define PMIC_MODULE_OK 0           /*成功返回值*/
#define PMIC_MODULE_STATUS_ON 1    /*mtcmos 状态为打开*/
#define PMIC_MODULE_STATUS_OFF 2   /*mtcmos 状态为关闭*/

#define PMU_SWITCH_OFF          (0)     /*PMU电源关*/
#define PMU_SWITCH_ON           (1)     /*PMU电源开*/

#define PMU_LVS_VOL_SET_INVAILD  0xFFFF

#define PMU_STATUS_REG_TYPE_ID_IS_INVALID(x)       (x > PMIC_IRQMASK_REG_TYPE_ID) /*check id合法性*/

#define PMUSSI_TRACE(fmt, ...)    printk(fmt, ##__VA_ARGS__)

/*定义一组PMU register所包含的BIT个数*/
#define PMU_REG_WIDTH  (8)

/*定义PMU RECORD资源*/
#define PMU_SCP_RECORD1(_nr)    (_nr)
#define PMU_OCP_RECORD1(_nr)    (PMU_SCP_RECORD1(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD2(_nr)    (PMU_OCP_RECORD1(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD3(_nr)    (PMU_OCP_RECORD2(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD4(_nr)    (PMU_OCP_RECORD3(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD5(_nr)    (PMU_OCP_RECORD4(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD6(_nr)    (PMU_OCP_RECORD5(PMU_REG_WIDTH - 1) + (_nr) + 1)
#define PMU_OCP_RECORD7(_nr)    (PMU_OCP_RECORD6(PMU_REG_WIDTH - 1) + (_nr) + 1)

#define IRQ_OCP_LDO9    PMU_OCP_RECORD3(0)
#define IRQ_OCP_LDO11   PMU_OCP_RECORD3(2)
#define IRQ_OCP_LVS5    PMU_OCP_RECORD5(3)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum EM_PMIC_IRQ_REG_ID_E
{
    PMIC_REG_IRQ1 = 0,
    PMIC_REG_IRQ2,
    PMIC_REG_IRQ3,
    PMIC_REG_IRQ4,
    PMIC_REG_COUL,
    PMIC_IRQ_REG_BUTT
}EM_PMIC_IRQ_REG_ID;

typedef enum EM_PMIC_IRQMASK_REG_ID_E
{
    PMIC_REG_IRQ1_MASK = 0,
    PMIC_REG_IRQ2_MASK,
    PMIC_REG_IRQ3_MASK,
    PMIC_REG_IRQ4_MASK,
    PMIC_REG_COUL_MASK,
    PMIC_IRQ_REG_MASK_BUTT
}EM_PMIC_IRQMASK_REG_ID;

typedef enum EM_PMIC_STATUS_REG_ID_E
{
    PMIC_STATUS1_REG,
    PMIC_STATUS2_REG,
    PMIC_STATUS_REG_BUTT
}EM_PMIC_STATUS_REG_ID;

typedef enum EM_PMIC_RECORD_REG_ID_E
{
    PMIC_SCP_RECORD1_REG,
    PMIC_OCP_RECORD1_REG,
    PMIC_OCP_RECORD2_REG,
    PMIC_OCP_RECORD3_REG,
    PMIC_OCP_RECORD4_REG,
    PMIC_OCP_RECORD5_REG,
    PMIC_OCP_RECORD6_REG,
    PMIC_OCP_RECORD7_REG,
    PMIC_RECORD_REG_BUTT
}EM_PMIC_RECORD_REG_ID;

typedef enum EM_PMIC_NP_IRQ_REG_ID_E
{
    PMIC_IRQ1_NO_PWR_REG,
    PMIC_IRQ2_NO_PWR_REG,
    PMIC_IRQ3_NO_PWR_REG,
    PMIC_SCP_RECORD_NO_PWR_REG,
    PMIC_OCP_RECORD1_NO_PWR_REG,
    PMIC_OCP_RECORD2_NO_PWR_REG,
    PMIC_OCP_RECORD3_NO_PWR_REG,
    PMIC_OCP_RECORD4_NO_PWR_REG,
    PMIC_OCP_RECORD5_NO_PWR_REG,
    PMIC_OCP_RECORD6_NO_PWR_REG,
    PMIC_OCP_RECORD7_NO_PWR_REG,
    PMIC_NO_PWR_REG_BUTT
}EM_PMIC_NP_IRQ_REG_ID;

#define PMIC_BUF_MAX_SIZE   PMIC_NO_PWR_REG_BUTT

typedef enum _CHANNEL_SWI_TYPE_
{
  CHANNEL_SWI_ENABLE,
  CHANNEL_SWI_DISABLE,
  CHANNEL_SWI_ONOFF_STATUS,
  CHANNEL_SWI_BUTTOM
}CHANNEL_SWI_TYPE;

typedef enum EM_PMICSTATUS_REG_TYPE_ID_E
{
    PMIC_IRQ_REG_TYPE_ID,/*中断寄存器的id*/
    PMIC_STAT_REG_TYPE_ID,/*状态寄存器的id*/
    PMIC_RECORD_REG_TYPE_ID,
    PMIC_NOPWR_REG_TYPE_ID, /*非下电寄存器的id*/
    PMIC_IRQMASK_REG_TYPE_ID, /*中断屏蔽寄存器的id*/
    PMIC_REG_TYPE_ID_BUTT
}EM_PMICSTATUS_REG_TYPE_ID;
/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
/* 记录电压源或电流源设置的寄存器地址，可设置的bit位，bit位在寄存器地址中的偏移量（以bit计）*/
/*  ┏━━━━━━━┳━━━━━┳━━━━━━┓
    ┃寄存器基地址  ┃bit偏移量 ┃设置bit位数 ┃
    ┗━━━━━━━┻━━━━━┻━━━━━━┛    */
typedef struct pmu_common_reg_config
{
    BSP_U32 baseaddr;    /*寄存器基地址*/
    BSP_U32 bits_offset; /*所设置bit的偏移量*/
    BSP_U32 bits_num;    /*设置哪几个bit*/
}COMMON_REG_CFG;

/*  ┏━━━━━┳━━━━━━━━━━┓
    ┃寄存器地址┃电压开关bit位置     ┃
    ┗━━━━━┻━━━━━━━━━━┛    */
typedef struct pmu_common_switch
{
    COMMON_REG_CFG reg_cfg[CHANNEL_SWI_BUTTOM];
    BSP_U32 def_sw; /*初始开关状态*/
}COMMON_SWITCH;

/* 记录电压源或电流源设置的寄存器地址，可设置的bit位，bit位在寄存器地址中的偏移量（以bit计）*/
/*  ┏━━━━━━━┳━━━━┳━━━━━━┳━━━━━┳━━━━━━┓
    ┃有效值范围数组┃数组大小┃寄存器基地址┃bit偏移量 ┃设置bit位数 ┃
    ┗━━━━━━━┻━━━━┻━━━━━━┻━━━━━┻━━━━━━┛    */
typedef struct pmu_common_value_set
{
    BSP_U32 *value_range;   /*设置值有效范围数组  eg ldo1_set*/
    BSP_U32 value_range_num; /*有效范围数组大小 eg sizeof(ldo1_set)*/
    COMMON_REG_CFG reg_cfg;
}COMMON_VALUE_SET;

/*bat channel & voltage relation table*/
typedef struct pmu_common_resource
{
    BSP_U32 id;/*电源 id*/
    signed char  name[PMU_POWER_NAME_SIZE];/*电源名数组*/
    COMMON_SWITCH power_switch;     /*电源开关*/
    COMMON_VALUE_SET value_set;     /*电源设置值*/
}COMMON_RES;

typedef struct _PMU_RES_CTRL_
{
    COMMON_RES *res;/*资源数组*/
    BSP_U32 res_num;/*资源个数*/
    BSP_U32 data_width;  /*PMU数据宽度，目前为8bit*/
    COMMON_REG_CFG version;
}PMU_RES_CTRL;

typedef struct _PMUIRQ_RES_CTRL_
{
    BSP_U32 data_width;  /*PMU数据宽度，目前为8bit*/
    /*中断寄存器、状态寄存器和非下电寄存器数组*/
    BSP_U32*stat_reg[PMIC_REG_TYPE_ID_BUTT];
    /*中断寄存器、状态寄存器和非下电寄存器数组大小*/
    BSP_U32 stat_reg_size[PMIC_REG_TYPE_ID_BUTT];
}PMUIRQ_RES_CTRL;

typedef void (*mntn_reg_ops)(void);

typedef struct _PMIC_MNTN_POWER_ON_OPS_
{
    mntn_reg_ops no_pwr_read;
    mntn_reg_ops no_pwr_clear;
    mntn_reg_ops irq_read;
    mntn_reg_ops irq_clear;
    mntn_reg_ops record_read;
    mntn_reg_ops record_clear;
    mntn_reg_ops mntn_power_on_info;
}PMIC_MNTN_POWER_ON_OPS;

typedef struct _PMU_MNTN_LOG_
{
 COMMON_REG_CFG exc_addr;
 BSP_U32  is_exc_pd;
 char* mntn_log;
}PMU_MNTN_LOG;

typedef struct _PMUIRQ_STAT_
{
    /*中断寄存器、状态寄存器和非下电寄存器数组，寄存器个数为(stat_reg_size)*/
    BSP_U32* stat_reg_buf[PMIC_REG_TYPE_ID_BUTT];
    BSP_U32* mask_vote;
    BSP_U32* unmask_vote;
    BSP_U32  is_exc_pd;
}PMUIRQ_STAT;

typedef struct _PMIC_MNTN_DESC_
{
    PMIC_MNTN_POWER_ON_OPS* mntn_ops;
    struct notifier_block* power_off_notifier;
    PMU_MNTN_LOG* power_onoff_event;
    struct workqueue_struct *ocp_scp_wq;
    struct work_struct ocp_scp_wk;
    void (*ocp_scp_wk_ops)(struct work_struct *work);
    struct workqueue_struct *mntn_init_wq;
    struct delayed_work mntn_init_wk;
    void (*mntn_init_wk_ops)(struct work_struct *work);
    struct workqueue_struct *otmp_wq;
    struct work_struct otmp_wk;
    void (*otmp_wk_ops)(struct work_struct *work);
    PMUIRQ_STAT             stat;
}PMIC_MNTN_DESC;

typedef struct _PMU_CPU_HANDLER_
{
    int             reg_id;
    int             bit_id;
}PMU_CPU_HANDLER;

/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


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

#endif


/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tsensor_driver.h
  版 本 号   : 初稿
  作    者   : 刘龙l00217270
  生成日期   : 2013年5月14日
  最近修改   :
  功能描述   : tsensor_driver.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年5月14日
    作    者   : 刘龙l00217270
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/


#ifndef __TSENSOR_DRVIER_H__
#define __TSENSOR_DRVIER_H__

#include <linux/err.h>
#include <linux/io.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/stddef.h>
#include <linux/sysfs.h>
#include <linux/types.h>
#include <linux/mutex.h>

#include <linux/interrupt.h>
#include <asm/irq.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/reboot.h>
#include <linux/slab.h>
#include <linux/pm_qos_params.h>
#include <linux/delay.h>
#include <linux/timer.h>
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#endif




/*****************************************************************************
  2 宏定义
*****************************************************************************/
//#define TSENSOR_DEBUG


#define TSENSOR_NAME_LEN                 (50)
#define TSENSOR_WQ_NAME_LEN         (50)
#define TSENSOR_IRQ_NAME_LEN         (50)

#define TSENSOR_NORMAL_MONITORING_RATE  (1000)

#define ACPU_TSENSOR_ENABLE             0x01
#define GPU_TSENSOR_ENABLE             0x02

/*tsensor修正值偏移与长度*/
#define EFUSE_TSENSOR_TRIM_OFFSET           1408 /*1280*/
#define EFUSE_TSENSOR_TRIM_LEN              32

/*tsensor修正值转换宏*/
#define GPUR_TRIM_DATA_MASK                0x7F000000
#define GPUR_TRIM_DATA_PLUSMINUS           0x80000000

#define GPUL_TRIM_DATA_MASK                0x007F0000
#define GPUL_TRIM_DATA_PLUSMINUS           0x00800000

#define ACPUR_TRIM_DATA_MASK                0x00007F00
#define ACPUR_TRIM_DATA_PLUSMINUS           0x00008000

#define ACPUL_TRIM_DATA_MASK                0x0000007F
#define ACPUL_TRIM_DATA_PLUSMINUS           0x00000080


/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum {
    TSENSOR_ALARAM_ON = 0,
    TSENSOR_ALARAM_OFF,
    TSENSOR_ALARAM_BUFF,
} enum_tsensor_alarm;


typedef enum {
    TSENSOR_LOC_LOCAL = 0,
    TSENSOR_LOC_REMOTE,
    TSENSOR_LOC_BUFF,
} enum_tsensor_location;

typedef enum {
    TSENSOR_TYPE_0 = 0,
    TSENSOR_TYPE_1,
    TSENSOR_TYPE_BUFF,
} enum_tsensor_type;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
struct tsensor_config {
    unsigned int enable;               /* bit0:ACPU 温保使能 bit1:GPU温保使能 1  使能 0 关闭*/
    unsigned int lag_value0;             /* tsensor0滞回门限值 */
    unsigned int lag_value1;             /* tsensor1滞回门限值 */
    unsigned int thres_value0;          /* tsensor0告警门限值*/
    unsigned int thres_value1;          /* tsensor1告警门限值*/
    unsigned int reset_thres_value0;      /* tsensor0复位门限值*/   
    unsigned int reset_thres_value1;      /* tsensor1复位门限值*/ 
    unsigned int alarm_count1;      /* 在中断上报后，累计检查超过门限的
                                                           次数达到此上限后限制profile为acpumaxfreq/gpumaxfreq, ddrmaxfreq 
                                                          */
    unsigned int alarm_count2;      /* 已经降了profile后，累计检查超过门限的
                                                           次数后逐级降低profile 
                                                          */                                                          
    unsigned int resume_count;     /*如果温度累计低于滞回门限的次数达到此上限，取消max限制 
                                                      */

    unsigned int acpu_maxfreq;         /* 超过门限后限制acpu的最大频率*/
    unsigned int gpu_maxfreq;           /* 超过门限后限制gpu的最大频率*/
    unsigned int ddr_maxfreq;            /* 超过门限后限制ddr的最大频率*/
    unsigned int reserved[4];            /*保留*/
};


struct tsensor_info {
    char name[TSENSOR_NAME_LEN];
    char wqname[TSENSOR_WQ_NAME_LEN];
    char irqname[TSENSOR_IRQ_NAME_LEN];
    struct mutex lock;
    unsigned int irqnum;
    enum_tsensor_alarm tsensor_alarm_flag;
    unsigned int tsensor_alarm_count;
    unsigned int tsensor_resume_count;
    unsigned int hot_temp_num;    

    enum_tsensor_location last_access;  /*记录上次访问的sensor目标，避免重复设置*/
    
    bool maxfreq_lock;     /*是否已经锁频*/
    int exceed_temperature_time;

    /*记录逐级profile*/
    int cpu_profile_index;
    int gpu_profile_index;
    int ddr_profile_index; 

    /*记录NV配置里最大的profile*/
    int cpu_max_profile;
    int gpu_max_profile;
    int ddr_max_profile;     

    int thres_value;
    int lag_value;
    int reset_thres_value;
    
    struct work_struct tsensor_alarm_wk;
    struct workqueue_struct *tsensor_alaram_wq;
    
    void (*tsensor_init) (void);
    void (*tsensor_suspend)(void);
    irqreturn_t (*tsensor_irq)(int irq, void *data);
    void (*tsensor_irq_delaywork)(struct work_struct *work);
    void (*tsensor_temp_protect)(void);
    
};

struct tsensor_devinfo {
    struct platform_device *pdev;
    struct device *dev;
};

struct tsensor_governor { 
    struct mutex lock;
    struct delayed_work tsensor_monitor_work;
    int average_period; 
};

struct efuse_trim
{
   int gpu_remote;
   int gpu_local;
   int acpu_remote;
   int acpu_local;
};

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
    
int tsensor0_localremote_temp_get(enum_tsensor_location remotelocal, int count);
int tsensor0_temp_get(void);
void tsensor0_alarmstate_set(enum_tsensor_alarm onoff);
enum_tsensor_alarm tsensor0_alarmstate_get(void);
irqreturn_t tsensor0_irq(int irq, void *data);
void tsensor0_irq_delaywork(struct work_struct *work);
void tsensor0_suspend(void);
void tsensor0_init(void);
void tsensor0_temp_protect(void);

int tsensor1_localremote_temp_get(enum_tsensor_location remotelocal, int count);
int tsensor1_temp_get(void);
void tsensor1_alarmstate_set(enum_tsensor_alarm onoff);
enum_tsensor_alarm tsensor1_alarmstate_get(void);
irqreturn_t tsensor1_irq(int irq, void *data);
void tsensor1_irq_delaywork(struct work_struct *work);
void tsensor1_suspend(void);
void tsensor1_init(void);
void tsensor1_temp_protect(void);


int tsensor_config_init(void);


int tsensor_init(void);
int tsensor_suspend(void);
int tsensor_resume(void);
void tsensor_temp_protect(void);





#endif /* end of tsensor_driver.h */



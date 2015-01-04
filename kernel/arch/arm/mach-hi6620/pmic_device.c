/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_driver.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic device resource
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/module.h>

#include <mach/irqs.h>

#include "soc_smart_interface.h"
#include "pmic_common.h"
#include "regulator_pmic_info.h"

#define BUCK2_SET_SIZE    64

/* channel voltage set list*/
PMU_LOCAL BSP_U32 ldo2_set[]={2500000,2600000,2800000,2900000,3000000,3100000,3200000,3300000};
PMU_LOCAL BSP_U32 ldo5_set[]={2850000,2900000,2950000,3000000,3050000,3100000,3150000,3150000,3300000};
PMU_LOCAL BSP_U32 ldo7_set[]={1800000,1850000,2800000,2850000,2900000,2950000,3000000,3050000};
PMU_LOCAL BSP_U32 ldo10_set[]={2800000,2850000,2900000,2950000,3000000,3050000,3100000,3150000};
PMU_LOCAL BSP_U32 ldo13_set[]={1800000,2500000,2600000,2700000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo14_set[]={1800000,2500000,2600000,2700000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo15_set[]={1800000,2500000,2600000,2700000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo16_set[]={1800000,2500000,2600000,2700000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo17_set[]={900000,950000,1000000,1050000,1100000,1150000,1200000,1250000};
PMU_LOCAL BSP_U32 ldo18_set[]={1800000,2500000,2600000,2700000,2800000,2850000,2900000,3000000};
PMU_LOCAL BSP_U32 ldo19_set[]={900000,925000,950000,975000,1000000,1025000,1050000,1075000};
PMU_LOCAL BSP_U32 ldo20_set[]={2500000,2600000,2700000,2750000,2800000,2850000,3000000,3100000};
PMU_LOCAL BSP_U32 ldo21_set[]={1200000,1250000,1275000,1300000,1325000,1350000,1500000,1800000};
PMU_LOCAL BSP_U32 ldo22_set[]={1400000,1425000,1450000,1475000,1500000,1525000};
PMU_LOCAL BSP_U32 ldo23_set[]={1500000,1800000,1850000,1900000,1950000,2500000,2800000,2850000};
PMU_LOCAL BSP_U32 ldo24_set[]={2800000,2850000,2900000,2950000,3000000,3050000,3100000,3150000};

PMU_LOCAL BSP_U32 boost1_set[]={5500000,5400000,5200000,5000000,4200000,3800000,3500000,3400000};
PMU_LOCAL BSP_U32 buck2_set[BUCK2_SET_SIZE]={0};/*在初始化时循环赋值*/
PMU_LOCAL BSP_U32 lvs_set[1]={PMU_LVS_VOL_SET_INVAILD};


/*********电路资源表*****************
电路资源由各CPU唯一管理，不可多核管理
BUCK1 BUCK5 MCU管理。
LVS电路 固定电压 软件不可控  
************************************/

PMU_LOCAL COMMON_RES pmic_res[] =
{
    /*channel_id*/
    /*channel_name*/
    /*bat channel switch(on/off) register config*/
    /*voltage(current) set register config*/
    {
        LDO2_ID,
        LDO2_NAME,
        {
            {
                /*
                  ENABLE,
                  DISABLE,
                  ONOFF_STATUS
                  */
               {
                  SOC_SMART_ENABLE2_ADDR(0),
                  SOC_SMART_ENABLE2_en_ldo2_int_START,
                  (SOC_SMART_ENABLE2_en_ldo2_int_END-SOC_SMART_ENABLE2_en_ldo2_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_ADDR(0),
                  SOC_SMART_DISABLE2_dis_ldo2_int_START,
                  (SOC_SMART_DISABLE2_dis_ldo2_int_END-SOC_SMART_DISABLE2_dis_ldo2_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_st_ldo2_int_START,
                  (SOC_SMART_ONOFF_STATUS2_st_ldo2_int_END-SOC_SMART_ONOFF_STATUS2_st_ldo2_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo2_set,
            sizeof(ldo2_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO2_REG_ADJ_ADDR(0),
                SOC_SMART_LDO2_REG_ADJ_vset_ldo2_START,
                (SOC_SMART_LDO2_REG_ADJ_vset_ldo2_END-SOC_SMART_LDO2_REG_ADJ_vset_ldo2_START+1),
            },
        },
    },

    {
        LDO5_ID,
        LDO5_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_ADDR(0),
                  SOC_SMART_ENABLE2_en_ldo5_int_START,
                  (SOC_SMART_ENABLE2_en_ldo5_int_END-SOC_SMART_ENABLE2_en_ldo5_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_ADDR(0),
                  SOC_SMART_DISABLE2_dis_ldo5_int_START,
                  (SOC_SMART_DISABLE2_dis_ldo5_int_END-SOC_SMART_DISABLE2_dis_ldo5_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_st_ldo5_int_START,
                  (SOC_SMART_ONOFF_STATUS2_st_ldo5_int_END-SOC_SMART_ONOFF_STATUS2_st_ldo5_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo5_set,
            sizeof(ldo5_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO5_REG_ADJ_ADDR(0),
                SOC_SMART_LDO5_REG_ADJ_vset_ldo5_START,
                (SOC_SMART_LDO5_REG_ADJ_vset_ldo5_END-SOC_SMART_LDO5_REG_ADJ_vset_ldo5_START+1),
            },
        },
    },

    {
        LDO7_ID,
        LDO7_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE2_ADDR(0),
                  SOC_SMART_ENABLE2_en_ldo7_int_START,
                  (SOC_SMART_ENABLE2_en_ldo7_int_END-SOC_SMART_ENABLE2_en_ldo7_int_START+1),
               },
               {
                  SOC_SMART_DISABLE2_ADDR(0),
                  SOC_SMART_DISABLE2_dis_ldo7_int_START,
                  (SOC_SMART_DISABLE2_dis_ldo7_int_END-SOC_SMART_DISABLE2_dis_ldo7_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS2_ADDR(0),
                  SOC_SMART_ONOFF_STATUS2_st_ldo7_int_START,
                  (SOC_SMART_ONOFF_STATUS2_st_ldo7_int_END-SOC_SMART_ONOFF_STATUS2_st_ldo7_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo7_set,
            sizeof(ldo7_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO7_REG_ADJ_ADDR(0),
                SOC_SMART_LDO7_REG_ADJ_vset_ldo7_START,
                (SOC_SMART_LDO7_REG_ADJ_vset_ldo7_END-SOC_SMART_LDO7_REG_ADJ_vset_ldo7_START+1),
            },
        },
    },

    {
        LDO10_ID,
        LDO10_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo10_int_START,
                  (SOC_SMART_ENABLE3_en_ldo10_int_END-SOC_SMART_ENABLE3_en_ldo10_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo10_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo10_int_END-SOC_SMART_DISABLE3_dis_ldo10_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo10_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo10_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo10_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo10_set,
            sizeof(ldo10_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO10_REG_ADJ_ADDR(0),
                SOC_SMART_LDO10_REG_ADJ_vset_ldo10_START,
                (SOC_SMART_LDO10_REG_ADJ_vset_ldo10_END-SOC_SMART_LDO10_REG_ADJ_vset_ldo10_START+1),
            },
        },
    },

    {
        LDO13_ID,
        LDO13_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo13_int_START,
                  (SOC_SMART_ENABLE3_en_ldo13_int_END-SOC_SMART_ENABLE3_en_ldo13_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo13_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo13_int_END-SOC_SMART_DISABLE3_dis_ldo13_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo13_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo13_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo13_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo13_set,
            sizeof(ldo13_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO13_REG_ADJ_ADDR(0),
                SOC_SMART_LDO13_REG_ADJ_vset_ldo13_START,
                (SOC_SMART_LDO13_REG_ADJ_vset_ldo13_END-SOC_SMART_LDO13_REG_ADJ_vset_ldo13_START+1),
            },
        },
    },

    {
        LDO14_ID,
        LDO14_NAME,
        {
            {
               {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo14_int_START,
                  (SOC_SMART_ENABLE3_en_ldo14_int_END-SOC_SMART_ENABLE3_en_ldo14_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo14_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo14_int_END-SOC_SMART_DISABLE3_dis_ldo14_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo14_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo14_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo14_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo14_set,
            sizeof(ldo14_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO14_REG_ADJ_ADDR(0),
                SOC_SMART_LDO14_REG_ADJ_vset_ldo14_START,
                (SOC_SMART_LDO14_REG_ADJ_vset_ldo14_END-SOC_SMART_LDO14_REG_ADJ_vset_ldo14_START+1),
            },
        },
    },

    {
        LDO15_ID,
        LDO15_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo15_int_START,
                  (SOC_SMART_ENABLE3_en_ldo15_int_END-SOC_SMART_ENABLE3_en_ldo15_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo15_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo15_int_END-SOC_SMART_DISABLE3_dis_ldo15_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo15_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo15_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo15_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo15_set,
            sizeof(ldo15_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO15_REG_ADJ_ADDR(0),
                SOC_SMART_LDO15_REG_ADJ_vset_ldo15_START,
               (SOC_SMART_LDO15_REG_ADJ_vset_ldo15_END-SOC_SMART_LDO15_REG_ADJ_vset_ldo15_START+1),
            },
        },
    },

    {
        LDO16_ID,
        LDO16_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo16_int_START,
                  (SOC_SMART_ENABLE3_en_ldo16_int_END-SOC_SMART_ENABLE3_en_ldo16_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo16_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo16_int_END-SOC_SMART_DISABLE3_dis_ldo16_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo16_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo16_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo16_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo16_set,
            sizeof(ldo16_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO16_REG_ADJ_ADDR(0),
                SOC_SMART_LDO16_REG_ADJ_vset_ldo16_START,
                (SOC_SMART_LDO16_REG_ADJ_vset_ldo16_END-SOC_SMART_LDO16_REG_ADJ_vset_ldo16_START+1),
            },
        },
    },

    {
        LDO17_ID,
        LDO17_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo17_int_START,
                  (SOC_SMART_ENABLE3_en_ldo17_int_END-SOC_SMART_ENABLE3_en_ldo17_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo17_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo17_int_END-SOC_SMART_DISABLE3_dis_ldo17_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo17_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo17_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo17_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo17_set,
            sizeof(ldo17_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO17_REG_ADJ_ADDR(0),
                SOC_SMART_LDO17_REG_ADJ_vset_ldo17_START,
                (SOC_SMART_LDO17_REG_ADJ_vset_ldo17_END-SOC_SMART_LDO17_REG_ADJ_vset_ldo17_START+1),
            },
        },
    },

    {
        LDO18_ID,
        LDO18_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE3_ADDR(0),
                  SOC_SMART_ENABLE3_en_ldo18_int_START,
                  (SOC_SMART_ENABLE3_en_ldo18_int_END-SOC_SMART_ENABLE3_en_ldo18_int_START+1),
               },
               {
                  SOC_SMART_DISABLE3_ADDR(0),
                  SOC_SMART_DISABLE3_dis_ldo18_int_START,
                  (SOC_SMART_DISABLE3_dis_ldo18_int_END-SOC_SMART_DISABLE3_dis_ldo18_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS3_ADDR(0),
                  SOC_SMART_ONOFF_STATUS3_st_ldo18_int_START,
                  (SOC_SMART_ONOFF_STATUS3_st_ldo18_int_END-SOC_SMART_ONOFF_STATUS3_st_ldo18_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo18_set,
            sizeof(ldo18_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO18_REG_ADJ_ADDR(0),
                SOC_SMART_LDO18_REG_ADJ_vset_ldo18_START,
                (SOC_SMART_LDO18_REG_ADJ_vset_ldo18_END-SOC_SMART_LDO18_REG_ADJ_vset_ldo18_START+1),
            },
        },
    },

    {
        LDO19_ID,
        LDO19_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo19_int_START,
                  (SOC_SMART_ENABLE4_en_ldo19_int_END-SOC_SMART_ENABLE4_en_ldo19_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo19_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo19_int_END-SOC_SMART_DISABLE4_dis_ldo19_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo19_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo19_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo19_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo19_set,
            sizeof(ldo19_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO19_REG_ADJ_ADDR(0),
                SOC_SMART_LDO19_REG_ADJ_vset_ldo19_START,
                (SOC_SMART_LDO19_REG_ADJ_vset_ldo19_END-SOC_SMART_LDO19_REG_ADJ_vset_ldo19_START+1),
            },
        },
    },

    {
        LDO20_ID,
        LDO20_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo20_int_START,
                  (SOC_SMART_ENABLE4_en_ldo20_int_END-SOC_SMART_ENABLE4_en_ldo20_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo20_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo20_int_END-SOC_SMART_DISABLE4_dis_ldo20_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo20_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo20_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo20_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo20_set,
            sizeof(ldo20_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO20_REG_ADJ_ADDR(0),
                SOC_SMART_LDO20_REG_ADJ_vset_ldo20_START,
                (SOC_SMART_LDO20_REG_ADJ_vset_ldo20_END-SOC_SMART_LDO20_REG_ADJ_vset_ldo20_START+1),
            },
        },
    },

    {
        LDO21_ID,
        LDO21_NAME,
       {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo21_int_START,
                  (SOC_SMART_ENABLE4_en_ldo21_int_END-SOC_SMART_ENABLE4_en_ldo21_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo21_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo21_int_END-SOC_SMART_DISABLE4_dis_ldo21_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo21_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo21_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo21_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo21_set,
            sizeof(ldo21_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO21_REG_ADJ_ADDR(0),
                SOC_SMART_LDO21_REG_ADJ_vset_ldo21_START,
                (SOC_SMART_LDO21_REG_ADJ_vset_ldo21_END-SOC_SMART_LDO21_REG_ADJ_vset_ldo21_START+1),
            },
        },
    },

    {
        LDO22_ID,
        LDO22_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo22_int_START,
                  (SOC_SMART_ENABLE4_en_ldo22_int_END-SOC_SMART_ENABLE4_en_ldo22_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo22_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo22_int_END-SOC_SMART_DISABLE4_dis_ldo22_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo22_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo22_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo22_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo22_set,
            sizeof(ldo22_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO22_REG_ADJ_ADDR(0),
                SOC_SMART_LDO22_REG_ADJ_vset_ldo22_START,
                (SOC_SMART_LDO22_REG_ADJ_vset_ldo22_END-SOC_SMART_LDO22_REG_ADJ_vset_ldo22_START+1),
            },
        },
    },

    {
        LDO23_ID,
        LDO23_NAME,
       {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo23_int_START,
                  (SOC_SMART_ENABLE4_en_ldo23_int_END-SOC_SMART_ENABLE4_en_ldo23_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo23_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo23_int_END-SOC_SMART_DISABLE4_dis_ldo23_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo23_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo23_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo23_int_START+1),
               },
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            ldo23_set,
            sizeof(ldo23_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO23_REG_ADJ_ADDR(0),
                SOC_SMART_LDO23_REG_ADJ_vset_ldo23_START,
                (SOC_SMART_LDO23_REG_ADJ_vset_ldo23_END-SOC_SMART_LDO23_REG_ADJ_vset_ldo23_START+1),
            },
        },
    },

    {
        LDO24_ID,
        LDO24_NAME,
        {
            {
                {
                  SOC_SMART_ENABLE4_ADDR(0),
                  SOC_SMART_ENABLE4_en_ldo24_int_START,
                  (SOC_SMART_ENABLE4_en_ldo24_int_END-SOC_SMART_ENABLE4_en_ldo24_int_START+1),
               },
               {
                  SOC_SMART_DISABLE4_ADDR(0),
                  SOC_SMART_DISABLE4_dis_ldo24_int_START,
                  (SOC_SMART_DISABLE4_dis_ldo24_int_END-SOC_SMART_DISABLE4_dis_ldo24_int_START+1),
               },
              {
                  SOC_SMART_ONOFF_STATUS4_ADDR(0),
                  SOC_SMART_ONOFF_STATUS4_st_ldo24_int_START,
                  (SOC_SMART_ONOFF_STATUS4_st_ldo24_int_END-SOC_SMART_ONOFF_STATUS4_st_ldo24_int_START+1),
               },
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            ldo24_set,
            sizeof(ldo24_set)/sizeof(BSP_U32),
            {
                SOC_SMART_LDO24_REG_ADJ_ADDR(0),
                SOC_SMART_LDO24_REG_ADJ_vset_ldo24_START,
                (SOC_SMART_LDO24_REG_ADJ_vset_ldo24_END-SOC_SMART_LDO24_REG_ADJ_vset_ldo24_START+1),
            },
        },
    },

    {
        BOOST1_ID,
        BOOST1_NAME,
        {
            {
                {
                    SOC_SMART_BOOST_ADJ0_ADDR(0),
                    SOC_SMART_BOOST_ADJ0_en_bst_int_START,
                    (SOC_SMART_BOOST_ADJ0_en_bst_int_END-SOC_SMART_BOOST_ADJ0_en_bst_int_START+1),/*写1打开*/
                },
               {
                    SOC_SMART_BOOST_ADJ0_ADDR(0),
                    SOC_SMART_BOOST_ADJ0_en_bst_int_START,
                    (SOC_SMART_BOOST_ADJ0_en_bst_int_END-SOC_SMART_BOOST_ADJ0_en_bst_int_START+1), /*写0关闭*/      /*此处不同于其他数组元素*/
                },
                {
                    SOC_SMART_BOOST_ADJ0_ADDR(0),
                    SOC_SMART_BOOST_ADJ0_en_bst_int_START,
                    (SOC_SMART_BOOST_ADJ0_en_bst_int_END-SOC_SMART_BOOST_ADJ0_en_bst_int_START+1),/*1打开，0关闭*/
                }
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            boost1_set,
            sizeof(boost1_set)/sizeof(BSP_U32),
            {
                SOC_SMART_BOOST_ADJ9_ADDR(0),
                SOC_SMART_BOOST_ADJ9_vo_START,
                (SOC_SMART_BOOST_ADJ9_vo_END-SOC_SMART_BOOST_ADJ9_vo_START+1),
            },
        },
    },

     {
        BUCK2_ID,
        BUCK2_NAME,
        {/*POWER SWITCH*/
            {
                {
                    SOC_SMART_ENABLE1_ADDR(0),
                    SOC_SMART_ENABLE1_en_buck2_int_START,
                    (SOC_SMART_ENABLE1_en_buck2_int_END-SOC_SMART_ENABLE1_en_buck2_int_START+1),
                },
                {
                    SOC_SMART_DISABLE1_ADDR(0),
                    SOC_SMART_DISABLE1_dis_buck2_int_START,
                    (SOC_SMART_DISABLE1_dis_buck2_int_END-SOC_SMART_DISABLE1_dis_buck2_int_START+1),
                },
                {
                    SOC_SMART_ONOFF_STATUS1_ADDR(0),
                    SOC_SMART_ONOFF_STATUS1_st_buck2_int_START,
                    (SOC_SMART_ONOFF_STATUS1_st_buck2_int_END-SOC_SMART_ONOFF_STATUS1_st_buck2_int_START+1),
                }
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {/*VALUE SET*/
            buck2_set,
            sizeof(buck2_set)/sizeof(BSP_U32),
            {
                SOC_SMART_VSET_BUCK2_ADJ_ADDR(0),
                SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_START,
                (SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_END-SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_START+1),
            },
        },
    },

    {
        LVS2_ID,
        LVS2_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs2_int_START,
                      (SOC_SMART_ENABLE5_en_lvs2_int_END-SOC_SMART_ENABLE5_en_lvs2_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs2_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs2_int_END-SOC_SMART_DISABLE5_dis_lvs2_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs2_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs2_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs2_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS3_ID,
        LVS3_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs3_int_START,
                      (SOC_SMART_ENABLE5_en_lvs3_int_END-SOC_SMART_ENABLE5_en_lvs3_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs3_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs3_int_END-SOC_SMART_DISABLE5_dis_lvs3_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs3_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs3_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs3_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS4_ID,
        LVS4_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs4_int_START,
                      (SOC_SMART_ENABLE5_en_lvs4_int_END-SOC_SMART_ENABLE5_en_lvs4_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs4_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs4_int_END-SOC_SMART_DISABLE5_dis_lvs4_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs4_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs4_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs4_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS5_ID,
        LVS5_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs5_int_START,
                      (SOC_SMART_ENABLE5_en_lvs5_int_END-SOC_SMART_ENABLE5_en_lvs5_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs5_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs5_int_END-SOC_SMART_DISABLE5_dis_lvs5_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs5_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs5_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs5_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS6_ID,
        LVS6_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs6_int_START,
                      (SOC_SMART_ENABLE5_en_lvs6_int_END-SOC_SMART_ENABLE5_en_lvs6_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs6_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs6_int_END-SOC_SMART_DISABLE5_dis_lvs6_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs6_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs6_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs6_int_START+1),
                }
            },
            PMU_SWITCH_ON,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

     {
        LVS7_ID,
        LVS7_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs7_int_START,
                      (SOC_SMART_ENABLE5_en_lvs7_int_END-SOC_SMART_ENABLE5_en_lvs7_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs7_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs7_int_END-SOC_SMART_DISABLE5_dis_lvs7_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs7_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs7_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs7_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS8_ID,
        LVS8_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE5_ADDR(0),
                      SOC_SMART_ENABLE5_en_lvs8_int_START,
                      (SOC_SMART_ENABLE5_en_lvs8_int_END-SOC_SMART_ENABLE5_en_lvs8_int_START+1),
                },
                {
                      SOC_SMART_DISABLE5_ADDR(0),
                      SOC_SMART_DISABLE5_dis_lvs8_int_START,
                      (SOC_SMART_DISABLE5_dis_lvs8_int_END-SOC_SMART_DISABLE5_dis_lvs8_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS5_ADDR(0),
                      SOC_SMART_ONOFF_STATUS5_st_lvs8_int_START,
                      (SOC_SMART_ONOFF_STATUS5_st_lvs8_int_END-SOC_SMART_ONOFF_STATUS5_st_lvs8_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        LVS10_ID,
        LVS10_NAME,
        {
            {
                {
                      SOC_SMART_ENABLE6_ADDR(0),
                      SOC_SMART_ENABLE6_en_lvs10_int_START,
                      (SOC_SMART_ENABLE6_en_lvs10_int_END-SOC_SMART_ENABLE6_en_lvs10_int_START+1),
                },
                {
                      SOC_SMART_DISABLE6_ADDR(0),
                      SOC_SMART_DISABLE6_dis_lvs10_int_START,
                      (SOC_SMART_DISABLE6_dis_lvs10_int_END-SOC_SMART_DISABLE6_dis_lvs10_int_START+1),
                },
                {
                      SOC_SMART_ONOFF_STATUS6_ADDR(0),
                      SOC_SMART_ONOFF_STATUS6_st_lvs10_int_START,
                      (SOC_SMART_ONOFF_STATUS6_st_lvs10_int_END-SOC_SMART_ONOFF_STATUS6_st_lvs10_int_START+1),
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    },

    {
        PMU_CHANNEL_ID_BUTT,
        "PMU_CHANNEL_BUTT",
        {
            {
                {
                      0,
                      0,
                      0,
                },
                {
                      0,
                      0,
                      0,
                },
                {
                      0,
                      0,
                      0,
                }
            },
            PMU_SWITCH_OFF,/*bat switch init state*/
        },
        {
            lvs_set,
            sizeof(lvs_set)/sizeof(BSP_U32),
            {
                0,
                0,
                0,
            },
        },
    }
};

PMU_LOCAL PMU_RES_CTRL  smart_res_ctrl =
{
    pmic_res,
    PMU_CHANNEL_ID_BUTT,
    PMU_REGISTER_DATA_BIT,
    {SOC_SMART_VERSION_ADDR(0),0,0}
};



static struct platform_device smart_device = {
    .name       = "smartStar",
    .id         = 0,
    .dev.platform_data  = &smart_res_ctrl,
};

/* devices we initialise */
static struct platform_device __initdata *smart_devs[] = {
    &smart_device,
};

/*****************************************************************************
 函 数 名  : pmic_device_init
 功能描述  : device init
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月28日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
static int __init pmic_device_init(void)
{
    int i = 0;
    PMU_RES_CTRL*  res_ctrl = &smart_res_ctrl;
    res_ctrl->res_num = sizeof(pmic_res)/sizeof(COMMON_RES);

    /*buck 0~~0x3f*/
    for(i= 0;i<BUCK2_SET_SIZE;i++)
    {
        buck2_set[i] = (700 +8*i)*1000;
    }

    platform_add_devices(smart_devs, ARRAY_SIZE(smart_devs));
    printk("pmic_device_init\n");
    return 0;
}

/*must after pmussi gpio*/
core_initcall(pmic_device_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");
MODULE_DESCRIPTION(" Hisilicon PMIC driver");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


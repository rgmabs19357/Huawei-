/*
 * Copyright (C) 2010-2012 ARM Limited. All rights reserved.
 *
 * This program is free software and is provided to you under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, and any use by you of this program is subject to the terms of such GNU licence.
 *
 * A copy of the licence is included with the program, and can also be obtained from Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**
 * @file mali_platform_dvfs.c
 * Platform specific Mali driver dvfs functions
 * dvfs by balong
 */
#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_balong_pmm.h"

#include <linux/clk.h>
#include <linux/err.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <mach/delay.h>

#include <asm/io.h>

#include <linux/workqueue.h>

/* hal software interfaces */
#ifndef PC_UT_TEST_ON
#include "drv_regulator_user.h"
#endif
#include "reg_ops.h"
#include "mach/clk_name_interface.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/string.h>
#endif

#ifdef CONFIG_PROC_FS
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/seq_file.h>
#endif

#include <asm/spinlock.h>
#include "drv_pmic_if.h"
#include <mach/pmussi_drv.h>

#define DVFS_STEP_OVER          0
#define STATIC   static

/* recorder the current status for test */
typedef struct mali_dvfs_statusTag{
    mali_dvfs_status  currentStep;
}mali_dvfs_currentstatus;

/* dvfs profile */
typedef struct mali_dvfs_profileTag{
    unsigned int freq;                      /* pll0 should config freq,so calc is ness */
    unsigned int pllProfile;                /* pll reg according to freq*/
    unsigned int volProfile;                /* should calc this to reg value */
    unsigned int pllNum;                    /* pll0 or pll1 */
    unsigned int pllFreqReg;                /* pll0 for freq lock */
}mali_dvfs_profile_table;

typedef struct mali_volt_cal_para
{
    unsigned int freq;
    unsigned int vol_max_thd;  /*上限电压*/
    unsigned int vol_min_thd;  /*下限电压*/
    unsigned int mali_ref_hpm; /*mali参考HPM码字*/
}mali_dvfs_cal_para;

typedef struct mali_dfs_prof_pli
{
    int up_threshold;           /*up threshhold*/
    int down_threshold;         /*down threshhold*/
    int up_step;                /*up step len ==1*/
    int down_step;              /*down step len ==1*/
    int up_delay;               /*up delay ==0 */
    int down_delay;             /*down delay ==0*/
}mali_dvfs_policy_table;

/*dvfs policy using this table*/
mali_dvfs_policy_table mali_dvfs_policy[MALI_DVFS_STEPS]=
{
    #if SFT_GPU_DVFS_PROFILE
    {80,40,1,1,0,0},
    {80,40,1,1,0,0},
    {80,40,1,1,0,0}
    #else
    {80,40,1,1,0,0},
    {80,50,1,1,0,0},
    {85,55,1,1,0,0},
    {100,60,1,1,0,0},
    {100,70,1,1,0,0}
    #endif
};
/*dvfs status*/
mali_dvfs_currentstatus g_stMaliDvfsStatus;

/*dvfs current profile*/
STATIC u32 s_uwDvfsCurrPrf  = 0;
STATIC u32 s_uwDvfsBakPrf   = 2;
STATIC u32 s_uwDVFSLockPrf  = 2;

extern int g_mali_dvfs_steps;

STATIC mali_dvfs_profile_table mali_dvfs_profile[MALI_DVFS_STEPS]=
{
    #if SFT_GPU_DVFS_PROFILE
    {15, 0x11,0x9b0b, 1,0},
    {30, 0x01,0x9b13, 1,0},             /* 0.9v */
    {60, 0x00,0x9b19, 0,0}              /* 60Mhz */
    #else
    {160, 0x00,0x9b14, 0,0x5381032},              /* 160Mhz,pll0,1div, 0.8V */
    {266, 0x31,0x9b1d, 1,0x524206f},              /* 266Mhz,pll1,4div, 0.9V */
    {355, 0x21,0x9b1d, 1,0x524206f},              /* 355Mhz,pll1,3div, 0.9V */
    {533, 0x11,0x9b2a, 1,0x524206f},               /* 533Mhz,pll1,2div, 1.0V */
    {700, 0x00,0x9b32, 0,0x5282092}               /* 700Mhz */
    #endif
};

/* avs parameters fix here when soc update */
static u32 mali_avs_paras[MALI_DVFS_STEPS][8]=
{
    #if SFT_GPU_DVFS_PROFILE
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
    #else
    {0x500005,0x4000000D,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xE0F,0x090001FF},
    {0x500007,0x40000011,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xE19,0x090001FF},
    {0x500009,0x40000016,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0xE19,0x090001FF},
    {0x50000B,0x4000001A,0x87654321,0x0FEDCBA9,0x87654321,0x0FEDCBA9,0x1A26,0x090001FF},
    {0,0,0,0,0,0,0,0}
    #endif
};

/* dfs_limit_max */
static u32 s_uwDvfslimitMaxPrf = MALI_DVFS_STEPS -1;

/* dfs_limit_min */
static u32 s_uwDvfslimitMinPrf = 0;


/* utilization exchange */
static u32 s_uwMaliDvfsUtilization = 255;
STATIC u32 s_auwUtilization[MALI_UTILIZATION_NUM]={0};
STATIC u32 s_uwLockProfile      = 0;
STATIC u32 s_uwDebugFsDvfsOn    = 1;
STATIC u32 s_uwDebugFsAvsOn     = 0;  /* PMUSSI ISSUE: boardId <= 0x23 close avs */
static spinlock_t gpupmc_lock; //   ={0}; /* PMUSSI ISSUE: spinlock */

STATIC mali_dvfs_cal_para mali_vol_cal_paras[MALI_DVFS_STEPS]=
{
    #if SFT_GPU_DVFS_PROFILE
    {15,0x0b,0x0b,280},
    {30,0x13,0x13,390},
    {60,0x19,0x19,586}
    #else
    {160,0x14,0x14,280},
    {266,0x2c,0x14,350},
    {355,0x2c,0x15,447},
    {533,0x36,0x19,539},
    {700,0x3c,0x20,635}
    #endif
};
void mali_dvfs_work_handler(struct work_struct *w);
u32 find_current_weight(u32 utilization);
u32 mali_find_dvfs_profile(u32 rate);
int mali_get_target_profile(u32 curr, int step);

STATIC struct workqueue_struct *mali_dvfs_wq = 0;

/*Declare the DVFS work method*/
static DECLARE_WORK(mali_dvfs_work, mali_dvfs_work_handler);
/*****************************************************************************
 function name  : find_current_weight
 description    : performance prefer,so 90% has 3 weight ,95% has 5 weight
 input vars     : void
 output vars    : NA
 return value   : u32
 calls          : NA

 called         : decideNextStatus

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
u32 find_current_weight(u32 utilization)
{
    u32         weight;
    if (utilization <= (255*30/100))
    {
        weight  = 1;
    }
    else if (utilization > (255*95/100))
    {
        weight  = 5;
    }
    else
    {
        weight  = utilization*100/255/30;
    }

    return weight;
}

/*****************************************************************************
 function name  : get_mali_dvfs_status
 description    : get mali dvfs status to trace
 input vars     : void
 output vars    : NA
 return value   : mali_dvfs_status
 calls          : NA

 called         : mali_dvfs_status_update

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_dvfs_status get_mali_dvfs_status(void)
{
    return g_stMaliDvfsStatus.currentStep;
}

/*****************************************************************************
 function name  : decideNextStatus
 description    : using several s_auUtilization to decide include percent and extra outstanding
 input vars     : void
 output vars    : NA
 return value   : mali_dvfs_status
 calls          : find_current_weight

 called         : mali_dvfs_status_update

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_dvfs_status decideNextStatus(void)
{
    mali_dvfs_status    dvfsStatus = MALI_DVFS_BUTT;
    u32                 utilization;
    int                 count;
    u32                 weight;
    u32                 sum_utilization=0;
    u32                 sum_weight=0;

    int                 bystep_upthd;
    int                 bystep_downthd;
    int                 stepover_upthd;
    int                 stepover_downthd;

    /*parsing thd from policy*/
    bystep_upthd        = mali_dvfs_policy[s_uwDvfsCurrPrf].up_threshold;
    bystep_upthd        = (int)((255*bystep_upthd)/100);
    bystep_downthd      = mali_dvfs_policy[s_uwDvfsCurrPrf].down_threshold;
    bystep_downthd      = (int)((255*bystep_downthd)/100);
    stepover_upthd      = (int)((255*90)/100);
    stepover_downthd    = (int)((255*20)/100);

    /*get the weighted utilization*/
    for (count = 0; count < MALI_UTILIZATION_NUM; count++ )
    {
        weight          = find_current_weight(s_auwUtilization[count]);

        sum_utilization += weight*s_auwUtilization[count];
        sum_weight      += weight;
    }

    utilization         = sum_utilization/sum_weight;

    /*get the decision*/
    if (utilization > stepover_upthd)
    {
        dvfsStatus      = MALI_DVFS_INCREASE_HIGHEST;
    }
    else if (utilization > bystep_upthd)
    {
        dvfsStatus      = MALI_DVFS_INCREASE;
    }
    else if (utilization < stepover_downthd)
    {
        dvfsStatus      = MALI_DVFS_DECREASE_LOWEST;
    }
    else if (utilization < bystep_downthd)
    {
        dvfsStatus      = MALI_DVFS_DECREASE;
    }
    else
    {
        dvfsStatus      = MALI_DVFS_HOLD;
    }

    return dvfsStatus;
}

/*****************************************************************************
 function name  : mali_dvfs_status_update
 description    : as MALI_GPU_UTILIZATION_TIMEOUT we consider period = 50ms,every 250ms generate a decision
 input vars     : void
 output vars    : NA
 return value   : mali_dvfs_status
 calls          : get_mali_dvfs_status
                  decideNextStatus
                  pwrctrl_dfs_gpu_target

 called         : mali_dvfs_work_handler

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_bool mali_dvfs_status_update(u32 utilization)
{
    mali_dvfs_status curStatus  = MALI_DVFS_BUTT;
    mali_dvfs_status nextStatus = MALI_DVFS_BUTT;
    int i;

    MALI_DEBUG_PRINT(3, ("> mali_dvfs_status: utilization = %d \n",utilization));

    /* sliding window */
    for(i=0; i< MALI_UTILIZATION_NUM-1; i++)
    {
        s_auwUtilization[i]=s_auwUtilization[i+1];
    }
    s_auwUtilization[MALI_UTILIZATION_NUM-1] = utilization;

    /*decide next step*/
    curStatus   = get_mali_dvfs_status();
    nextStatus  = decideNextStatus();

    MALI_DEBUG_PRINT(3, ("nextStatus %d, g_stMaliDvfsStatus.currentStep %d \n", nextStatus, g_stMaliDvfsStatus.currentStep));

    /*if next status is same with current status, don't change anything*/
    if (nextStatus != MALI_DVFS_HOLD)
    {
        pwrctrl_dfs_gpu_target((s32)nextStatus - (s32)MALI_DVFS_HOLD);
    }

    /*update the dvfs action status*/
    g_stMaliDvfsStatus.currentStep = nextStatus;

    return MALI_TRUE;
}

/*****************************************************************************
 function name  : mali_dvfs_work_handler
 description    : we consider period = 50ms,every 250ms generate a decision
 input vars     : struct work_struct *w
 output vars    : NA
 return value   : void
 calls          : NA

 called         : decideNextStatus

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_dvfs_work_handler(struct work_struct *w)
{
    MALI_DEBUG_PRINT(3, ("=== mali_dvfs_work_handler\n"));

    if (!mali_dvfs_status_update(s_uwMaliDvfsUtilization))
        MALI_DEBUG_PRINT(1,( "error on mali dvfs status in mali_dvfs_work_handler\n"));

}

/*****************************************************************************
 function name  : mali_dvfs_status_init
 description    : we consider period = 50ms,every 250ms generate a decision
 input vars     : maliDvfsStatus
 output vars    : NA
 return value   : mali_bool
 calls          : create_singlethread_workqueue
 called         : mali_platform_init

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_bool mali_dvfs_status_init(mali_dvfs_status maliDvfsStatus)
{
    /*default status
    add here with the right function to get initilization value.
    */
    if (!mali_dvfs_wq)
    {
        mali_dvfs_wq = create_singlethread_workqueue("mali_dvfs");
    }

    /*add a error handling here*/
    g_stMaliDvfsStatus.currentStep = maliDvfsStatus;

    return MALI_TRUE;
}

/*****************************************************************************
 function name  : mali_dvfs_status_deinit
 description    : deinit dvfs by destroy workqueue
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : destroy_workqueue
 called         : mali_platform_init

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_dvfs_status_deinit(void)
{
    if (mali_dvfs_wq)
    {
        destroy_workqueue(mali_dvfs_wq);
    }

    mali_dvfs_wq = NULL;
}

/*****************************************************************************
 function name  : mali_dvfs_handler
 description    : put utilization into work queue
 input vars     : utilization
 output vars    : NA
 return value   : mali_bool
 calls          : queue_work_on
 called         : mali_gpu_utilization_handler

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_bool mali_dvfs_handler(u32 utilization)
{
    #ifdef MALI_UT_TEST

    #else
    s_uwMaliDvfsUtilization = utilization;
    queue_work_on(0, mali_dvfs_wq,&mali_dvfs_work);
    #endif
    /*add error handle here*/
    return MALI_TRUE;
}

int mali_dvfs_cal_find_min_once(void)
{
    int regmin,regRet[4];
    regRet[0] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM01OPC_ADDR(0),0,9);
    regRet[1] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM01OPC_ADDR(0),10,19);
    regRet[2] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM23OPC_ADDR(0),0,9);
    regRet[3] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM23OPC_ADDR(0),10,19);

    regmin = min(regRet[0],regRet[1]);
    regmin = min(regmin,regRet[2]);
    regmin = min(regmin,regRet[3]);

    return regmin;
}
int mali_dvfs_cal_find_min_256(void)
{
    int regmin,regRet[4];
    regRet[0] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM01PC_ADDR(0),0,9);
    regRet[1] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM01PC_ADDR(0),10,19);
    regRet[2] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM23PC_ADDR(0),0,9);
    regRet[3] = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPM23PC_ADDR(0),10,19);

    regmin = min(regRet[0],regRet[1]);
    regmin = min(regmin,regRet[2]);
    regmin = min(regmin,regRet[3]);

    return regmin;
}
/*****************************************************************************
 function name  : mali_dvfs_calibration
 description    : dvfs voltage calibration when driver init
 input vars     : NA
 output vars    : NA
 return value   : NA
 calls          :
 called         :

 history        :
  1.data        : 19/08/2013
    modify      : new

FREQ Vmax     Vmin  Hpm code
266	1.05	　0.85	5	280
355	1.05	　0.86	5	390
533	1.15	　0.9	5	586
*****************************************************************************/
void mali_dvfs_calibration(void)
{
    int i;
    int volRegRet;
    int csgl_mali;
    int cmul_mali;
    int volRegCal[MALI_DVFS_STEPS]={0};

    /*step1,change vol to 0.85v,pll0 div 0*/
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKDIV_ADDR(0),0,3,0x0);
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLPMUADDR_ADDR(0),16,16,0x1);
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),0,6,mali_vol_cal_paras[0].vol_min_thd);
    while(mali_vol_cal_paras[0].vol_min_thd != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),8,14));

    /* DIS reset hpm */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0), 28, 28, 0x1);

    /* init avs for cal */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA0_ADDR(0),0,31,0x510005);
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA7_ADDR(0),0,31,0x80000ff);
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARAUDP_ADDR(0),0,0,0x1);
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMMASKDIS_ADDR(0),0,31,0xf);
    udelay(500);
    MALI_DEBUG_PRINT(3,( "mali_dvfs_calibration init ok,freqreg=%x,avsen=%x,div=%x\n",phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL0FREQ_ADDR(0),0,31),
    phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSEN_ADDR(0),0,31),
    phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKDIV_ADDR(0),0,31)));

    /* step2: set first step and cal from the second one */
    volRegCal[0]= mali_vol_cal_paras[0].vol_min_thd;

    /* get each freq vol calibration */
    for ( i=1; i < g_mali_dvfs_steps; i++)
    {
        MALI_DEBUG_PRINT(3,( "mali_dvfs_calibration SOC_PMCTRL_PMCSTATUS_ADDR=%x\n",
        phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCSTATUS_ADDR(0),16,18)));
        /* get current voltage profile reg value*/
        volRegRet = phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),8,14);

        for (;;)
        {
            /* limit it to max and continue next rount */
            if ( volRegRet > mali_vol_cal_paras[i].vol_max_thd )
            {
                /* point out error and limit it to max */
                MALI_DEBUG_PRINT(2,( "error on dvfs vol calibration %d\n",i));

                phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),0,6,mali_vol_cal_paras[i].vol_max_thd);
                while(mali_vol_cal_paras[i].vol_max_thd != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),8,14));
                udelay(5);

                volRegCal[i] = mali_vol_cal_paras[i].vol_max_thd;
                break;
            }

            /* limit it to min and cal */
            if (volRegRet < mali_vol_cal_paras[i].vol_min_thd)
            {
                volRegRet = mali_vol_cal_paras[i].vol_min_thd;
                phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),0,6,mali_vol_cal_paras[i].vol_min_thd);

                while(volRegRet != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),8,14));
                udelay(5);
            }
            MALI_DEBUG_PRINT(3,( "mali_dvfs_calibration maxmin limit ok with voldest=%x\n",volRegRet));

            /* read once to get4 hpm output, min() as csgl_mali */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMCTRL_ADDR(0),0,3,0xf);
            while(0xf != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMOPCVALID_ADDR(0),0,3));
            csgl_mali = mali_dvfs_cal_find_min_once();
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMCTRL_ADDR(0),0,3,0x0);
            MALI_DEBUG_PRINT(3,( "mali_dvfs_calibration read hpm once ok =%d\n",csgl_mali));

            /* 256 average read hpm */
            if (csgl_mali > mali_vol_cal_paras[i].mali_ref_hpm)
            {
                phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARAUDP_ADDR(0),0,0,0x1);
                phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSEN_ADDR(0),0,1,0x1);
                while(0x7 != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCSTATUS_ADDR(0),16,19));
                phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSEN_ADDR(0),0,1,0x0);

                cmul_mali = mali_dvfs_cal_find_min_256();
                MALI_DEBUG_PRINT(3,( "mali_dvfs_calibration read hpm 256 ok cmul_mali =%d,max than %d?\n",cmul_mali,mali_vol_cal_paras[i].mali_ref_hpm));

                if( cmul_mali > mali_vol_cal_paras[i].mali_ref_hpm )
                {
                    volRegCal[i] = volRegRet;
                    break;
                }
            }

            /* set vol to next stage by add 1*/
            volRegRet++;
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),0,6,volRegRet);
            while(volRegRet != phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),8,14));
            udelay(5);
        }


        mali_dvfs_profile[i].volProfile = (mali_dvfs_profile[i].volProfile&0xffffff00) + volRegCal[i];
        MALI_DEBUG_PRINT(2,( "dvfs vol calibration result vol[%d]=%d,volprofile=0x%x\n",i,volRegCal[i],mali_dvfs_profile[i].volProfile));
    }

    /*step3: finish*/
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLPMUADDR_ADDR(0),16,16,0x0);

}
/*****************************************************************************
 function name  : pwrctrl_g3d_dfs_init
 description    : init when system up
 input vars     : NA]
 output vars    : NA
 return value   : NA
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
void pwrctrl_g3d_dfs_init(void)
{
    /*pmussi issue init by pmu version*/
    if(pmu_get_version()<= PMU_VERSION_SSI_BUG)
    {
        s_uwDebugFsAvsOn = 0;
    }

    /* first init related registers of DVFS */
    /* PMUSSI ISSUE: spinlock init */
    spin_lock_init(&gpupmc_lock);

    /* DVFS voltage calibration */
    mali_dvfs_calibration();

    /* G3DDFTVOL[6:0] = 0x19 to set base voltage */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDFTVOL_ADDR(0),0,6,0x19);

    /* G3DVOLPMUADDR = 0x98 SET hardware auto config g3d vol PMU register*/
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLPMUADDR_ADDR(0),0,31,0x98);

    /* G3DVOLUPSTEP = 0x1 SET increase step to 1 */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLUPSTEP_ADDR(0),0,31,0x1);

    /* G3DVOLDNSTEP = 0x1 SET decrease step to 1 */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLDNSTEP_ADDR(0),0,31,0x1);

    /* G3DPMUVOLUPTIME = 0x60 SET wait time for vol increase to stable */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPMUVOLUPTIME_ADDR(0),0,31,0x60);

    /* G3DPMUVOLDNTIME = 0x60 SET wait time for vol decrease to stable */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPMUVOLDNTIME_ADDR(0),0,31,0x60);


    /* second init related registers of AVS ,fix here when update by soc*/

    /* G3DHPMCTRL = 0x0 select standard HPM*/
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMCTRL_ADDR(0),0,31,0);

    /* G3DHPMBYPASS = 0x0 enable HPM clock hardware detect */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMBYPASS_ADDR(0),0,31,0);

    /* G3DHPMMASKDIS = 0xf enable all HPM ctrol */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMMASKDIS_ADDR(0),0,31,0xf);

    /* G3DAVSPERIOD = 0x20000 set AVS peroid to 6ms */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPERIOD_ADDR(0),0,31,0x20000);

    /* G3DAVSPARA7 = 0x90001ff set HPM sampling number as 512 */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA7_ADDR(0),0,31,0x90001ff);

    /* dis reset the avs */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0), 0, 31, 0x10000000);

    /* for test only when no power up and down */
    pwrctrl_dfs_gpu_enable();

    MALI_DEBUG_PRINT(2, (" init mali dvfs avs ok\n"));

}
/*****************************************************************************
 function name  : pwrctrl_dfs_gpu_target
 description    : act dvfs as required
 input vars     : step [-3,3]
 output vars    : NA
 return value   : int
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
int pwrctrl_dfs_gpu_target(int step)
{
    int targetProfile;
    int byStep;
    u32 upFlg;
    if (1 == s_uwDebugFsDvfsOn)
    {
        /* parameters check */
        if ((step > 3) || (step < -3))
        {
            MALI_DEBUG_PRINT(3,( "bad parameters input to pwrctrl_dfs_gpu_target \r\n"));
            return MALI_FALSE;
        }

    if (0 == step)
    {
        MALI_DEBUG_PRINT(3,( "step=0,no need call this dvfs func \r\n"));
        return MALI_TRUE;
    }

    /* dfs action */
    MALI_DEBUG_PRINT(3,( "current GPU DVFS Profile is %d \r\n",s_uwDvfsCurrPrf));


    targetProfile = mali_get_target_profile(s_uwDvfsCurrPrf, step);

    if (s_uwDvfsCurrPrf == targetProfile)
    {
        MALI_DEBUG_PRINT(3,( "current == target ,no need change \r\n"));
        return MALI_TRUE;
    }
    else
    {
        MALI_DEBUG_PRINT(3,( "current =%d, target=%d doing DVFS \r\n",s_uwDvfsCurrPrf, targetProfile));
    }

    /* get the direction of DVFS */
    if (s_uwDvfsCurrPrf < targetProfile)
    {
        upFlg = MALI_TRUE;
    }
    else
    {
        upFlg = MALI_FALSE;
    }

    /* could support step over or step by step */
    #if DVFS_STEP_OVER
    mali_avs_dfs_target_profile(targetProfile,upFlg);
    #else
    if (s_uwDvfsCurrPrf < targetProfile)
    {
        for ( byStep = s_uwDvfsCurrPrf + 1; byStep <= targetProfile; byStep++ )
        {
            mali_avs_dfs_target_profile(byStep, upFlg);
        }
    }
    else
    {
        for ( byStep = s_uwDvfsCurrPrf - 1; byStep >= targetProfile; byStep-- )
        {
            mali_avs_dfs_target_profile(byStep, upFlg);
        }
    }

    #endif

        s_uwDvfsCurrPrf = targetProfile;
    }

    return MALI_TRUE;
}

/*****************************************************************************
 function name  : pwrctrl_dfs_gpu_disable
 description    : disable MALI dvfs
 input vars     : NA
 output vars    : NA
 return value   : int
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
int pwrctrl_dfs_gpu_disable(void)
{
    u32 ulDelayCnt;

    if (1 == s_uwDebugFsDvfsOn)
    {
        /* back the current profile for powerup */
        s_uwDvfsBakPrf = s_uwDvfsCurrPrf;

       /* switch to pll0 and it's vol before powerdown */
        mali_avs_dfs_target_profile(0,MALI_FALSE);

        if (1 == s_uwDebugFsAvsOn)
        {
            /* G3DAVSEN = 0x0 to disable AVS */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSEN_ADDR(0),0,31,0);
        }

        /* wait PMCSTATUS[6:4] ==0 && PMCSTATUS[18:16] == 0 */
        for (ulDelayCnt = 0; ;ulDelayCnt++ )
        {
            if ( (0 == phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCSTATUS_ADDR(0),4,6))
               &&(0 == phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCSTATUS_ADDR(0),16,18)) )
            {
                break;
            }

            if (ulDelayCnt > 10000000)
            {
                MALI_DEBUG_PRINT(2,( "fail to close G3D avs and dvfs \r\n"));
                return MALI_FALSE;
            }
        }

        /* G3DCLKOFFCFG = 0x0 disable DVFS */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKOFFCFG_ADDR(0),0,31,0);
    }
    return MALI_TRUE;
}
/*****************************************************************************
 function name  : pwrctrl_dfs_gpu_enable
 description    : disable MALI dvfs
 input vars     : NA
 output vars    : NA
 return value   : int
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
int pwrctrl_dfs_gpu_enable(void)
{
    if (1 == s_uwDebugFsDvfsOn)
    {
        if ( 1== s_uwDebugFsAvsOn)
        {
            /* G3DHPMMASKDIS = 0xf enable all HPM ctrol */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMMASKDIS_ADDR(0),0,31,0xf);

            /* G3DAVSEN = 0x33 to enable AVS function */
    		phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSEN_ADDR(0),0,31,0x3);
        }

        /* then G3DCLKOFFCFG = 0x1000 to enable DVFS func */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKOFFCFG_ADDR(0),0,31,0x1000);

    }
   /* powerup with old profile */
   mali_avs_dfs_target_profile(s_uwDvfsBakPrf,MALI_TRUE);

    return MALI_TRUE;
}

/*****************************************************************************
 function name  : mali_find_dvfs_profile
 description    : using rate to find profile number
 input vars     : u32 rate
 output vars    : NA
 return value   : u32
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
u32 mali_find_dvfs_profile(u32 rate)
{
    int i;
    for ( i=0; i<g_mali_dvfs_steps; i++ )
    {
        if (rate == mali_dvfs_profile[i].freq)
        {
            break;
        }
    }

    if (g_mali_dvfs_steps == i)
    {
        MALI_DEBUG_PRINT(3,("bad mali dvfs profile with freq =%d\n",rate));
    }
    return (u32)i;
}

/*****************************************************************************
 function name  : mali_get_target_profile
 description    : as to current profile and step, to get target profile
 input vars     : u32 curr
 output vars    : NA
 return value   : u32
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
int mali_get_target_profile(u32 curr, int step)
{
    int target;
    int currTmp = curr;
    int maxProfile = g_mali_dvfs_steps - 1;

    /* target profile calculate */
    if ( 3 == step )
    {
        target  = maxProfile;
    }
    else if ( -3 == step )
    {
        target  = 0;
    }
    else
    {
        target  = currTmp + step;
        target  = (target>maxProfile)?maxProfile:target;
        target  = ((target<0)?0:target);
    }

    target  = (target<s_uwDvfslimitMinPrf)?s_uwDvfslimitMinPrf:target;
    target  = (target>s_uwDvfslimitMaxPrf)?s_uwDvfslimitMaxPrf:target;
    target  = (target>(g_mali_dvfs_steps - 1))?g_mali_dvfs_steps:target;

    /*if max profile,check if it is forbidden,upthd==100 */
    if((MALI_DVFS_STEPS-1) == target)
    {
        if(mali_dvfs_policy[MALI_DVFS_STEPS-2].up_threshold >= 100)
        {
            target = target-1;
        }
    }

    MALI_DEBUG_PRINT(3,( "g3d tarprofile is %d ,thd=%d\r\n",target,mali_dvfs_policy[MALI_DVFS_STEPS-2].up_threshold));

    if( s_uwLockProfile == 1)
    {
        target = s_uwDVFSLockPrf;
    }

    return target;

}

/*****************************************************************************
 function name  : mali_avs_dfs_to_profile
 description    : doing avs and dfs action to target profile
 input vars     : u32 curr
 output vars    : NA
 return value   : u32
 calls          :
 called         :

 history        :
  1.data        : 12/03/2013
    modify      : new

*****************************************************************************/
void mali_avs_dfs_target_profile(int target, u32 up)
{
    int i;
    u32 dvfsEn;

    unsigned long irq_flags = 0;
    unsigned long trycount;
    SOC_AO_SCTRL_SC_SYS_STAT0_UNION sc_sysstate;

    if (1 == s_uwDebugFsDvfsOn)
    {
        /* parameter check */
        if ((target < 0)||(s_uwDvfsCurrPrf == target))
        {
            return;
        }

        /* PMUSSI ISSUE: try to lock */
        /*pmussi issue by pmu version*/
        if(pmu_get_version()<= PMU_VERSION_SSI_BUG)
        {
            trycount = 0;
            do
            {
                /*ssipatch:firstly lock irq*/
                spin_lock_irqsave(&gpupmc_lock, irq_flags);

                /*SC_MCU_VOTE1EN0 set GPU bit28 =1 to require for operation*/
                phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_MCU_VOTE1EN0_ADDR(0),28,28,0x1);
                /*read SC_SYS_STAT0 vote1_semphsta?1'b0 continue,else SC_MCU_VOTE1DIS0 bit28=1'b1unlock usleep(1) do*/
                for (i=0;i<10;i++)
                {
                    sc_sysstate.value = phy_reg_readl(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(0),0,31);

                    if (0 == sc_sysstate.reg.vote1_semphsta)
                    {
                        break;
                    }
                }

                /*time out for 1000 times read*/
                if (i>=10)
                {
                    /*disable and restore irq*/
                    phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_ADDR(0),28,28,0x1);
                    spin_unlock_irqrestore(&gpupmc_lock, irq_flags);
                    udelay(1);
                }

                trycount++;
                if ((trycount&0xfff) == 0xfff)
                {
                    MALI_DEBUG_PRINT(1,("pmussi try to lock %d us\n",trycount));
                    return;
                }
            }while(i>=10);
        }

        if (1 == s_uwDebugFsAvsOn)
        {
            /* AVS config first G3DAVSPARA0[22:20]=0x5,G3DAVSPARA0[17:16]=0x1 to select min */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA0_ADDR(0),20,22,0x5);
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA0_ADDR(0),16,17,0x0);

            /* G3DAVSPARA0[5:0] = ? set g3d target freq HPM meas time */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA0_ADDR(0),0,5,mali_avs_paras[target][0]);

            /* G3DAVSPARA1 = ? set g3d target freq ref performance value */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA1_ADDR(0),0,31,mali_avs_paras[target][1]);

            /* G3DAVSPARA2~ G3DAVSPARA5 value to set gain of perf vs vol */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA2_ADDR(0),0,31,mali_avs_paras[target][2]);
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA3_ADDR(0),0,31,mali_avs_paras[target][3]);
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA4_ADDR(0),0,31,mali_avs_paras[target][4]);
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA5_ADDR(0),0,31,mali_avs_paras[target][5]);


            /* G3DAVSPARA6 = ? AVS valu limitation */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DAVSPARA6_ADDR(0),0,31,mali_avs_paras[target][6]);
        }

        /* then config DVFS */
        if (MALI_TRUE == up)
        {
            dvfsEn = 0x3;
        }
        else
        {
            dvfsEn = 0x1;
        }

        /* find the target PLL and open it if no open, as to PLL0 should set freq first */
        if (0 == mali_dvfs_profile[target].pllNum)
        {
            /* G3DPLL0FREQ =  mali_dvfs_profile[target].pllFreqReg ,calc by tool */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL0FREQ_ADDR(0),0,31,mali_dvfs_profile[target].pllFreqReg);

            /* G3DPLL0CTRL[0] =1 to enable G3DPLL0 */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL0CTRL_ADDR(0),0,0,0x1);

        }
        else
        {
           /* G3DPLL1FREQ =  mali_dvfs_profile[target].pllFreqReg ,calc by tool */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL1FREQ_ADDR(0),0,31,mali_dvfs_profile[target].pllFreqReg);
            /* G3DPLL1CTRL[0] =1 to enable G3DPLL1 */
            phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL1CTRL_ADDR(0),0,0,0x1);

        }

        /* G3DCLKPROFILE0 = 0xxx to set clk from pll*/
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKPROFILE0_ADDR(0),0,31,mali_dvfs_profile[target].pllProfile);

        /* G3DVOLPROFILE =  mali_dvfs_profile[target].vol to set target vol ,look into reg manual */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DVOLPROFILE_ADDR(0),0,31,mali_dvfs_profile[target].volProfile);

        /* SOC_PMCTRL_PMCINTRAW_ADDR bit15 =1 to clear intraw of DVFS first */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCINTCLR_ADDR(0),15,15,1);

        /* G3DDVFSEN to start DVFS */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDVFSEN_ADDR(0),0,1,dvfsEn);

        /* wait for finish 1000 us */
        for (i=0; i<1000; i++)
        {
            /* PMCINTRAW bit9 ==1 */
            if (1 == phy_reg_readl(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_PMCINTRAW_ADDR(0),15,15))
            {
                break;
            }
            udelay(1);
        }

        if (1000 <= i)
        {
            MALI_DEBUG_PRINT(1,("bad mali dvfs timeout for 1ms reads\n"));
        }
        else
        {
            s_uwDvfsCurrPrf = target;

            /*test*/
            MALI_DEBUG_PRINT(3,("mali dvfs to %d interrupt return ok\n",target));
        }

        /* PMUSSI ISSUE: SC_MCU_VOTE1DIS0 bit28=1'b1 unlock usleep(1)*/
        /*pmussi issue by pmu version*/
        if(pmu_get_version()<= PMU_VERSION_SSI_BUG)
        {
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_ADDR(0),28,28,0x1);
            /*irq enable*/
            spin_unlock_irqrestore(&gpupmc_lock, irq_flags);
            udelay(1);
        }
    }

}

/*****************************************************************************
 function name  : pmqos_gpu_dfs_get_current_profile
 description    : doing avs and dfs action to target profile
 input vars     : u32 *profile_id
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_dfs_get_current_profile(u32 *profile_id)
{
    *profile_id = s_uwDvfsCurrPrf;
}
/*****************************************************************************
 function name  : pmqos_gpu_get_current_func
 description    : get curr pwrctrl
 input vars     : u32 *curr_func
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_get_current_func(unsigned int *curr_func)
{
    if ( (s_uwDebugFsDvfsOn == 1) && (s_uwDebugFsAvsOn == 1))
    {
        *curr_func = 4;
    }
    else if( s_uwDebugFsDvfsOn == 1 )
    {
        *curr_func = 1;
    }
    else if( s_uwDebugFsAvsOn ==  1)
    {
        *curr_func = 2;
    }
    else
    {
        *curr_func = 0x20;
    }
}
/*****************************************************************************
 function name  : pmqos_gpu_set_current_func
 description    : get curr pwrctrl
 input vars     : u32 *curr_func
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_set_current_func(unsigned int target_func)
{
    if ( target_func == 1 )
    {
        s_uwDebugFsDvfsOn = 1;
    }
    else if( target_func == 2)
    {
        s_uwDebugFsAvsOn = 1;
    }
    else if( target_func == 4)
    {
        s_uwDebugFsDvfsOn = 1;
        s_uwDebugFsAvsOn = 1;
    }
    else if ( target_func == 8 )
    {
        s_uwDebugFsDvfsOn = 0;
    }
    else if ( target_func == 0x10 )
    {
        s_uwDebugFsAvsOn = 0;
    }
    else if ( target_func == 0x20)
    {
        s_uwDebugFsDvfsOn = 0;
        s_uwDebugFsAvsOn = 0;
    }
    else
    {
        //do something here;
    }
}
/*****************************************************************************
 function name  : pmqos_gpu_dfs_lock
 description    : lock profile
 input vars     : u32 *lock_profile
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_dfs_lock(u32 lock_profile)
{
    s_uwLockProfile = 1;//to control the dvfs caculator and run

    s_uwDVFSLockPrf = lock_profile;

}
/*****************************************************************************
 function name  : pmqos_gpu_dfs_unlock
 description    : lock profile
 input vars     : u32 *lock_profile
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_dfs_unlock(void)
{
    s_uwLockProfile = 0;//to control the dvfs caculator and run
}
/*****************************************************************************
 function name  : pmqos_gpu_dfs_limit_max
 description    : limit the max frequence ,<xxKhz
 input vars     : u32 max_freq_limit
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_dfs_limit_max(u32 max_freq_limit)
{
    int currPrf;

    if( 0 == max_freq_limit)
    {
        s_uwDvfslimitMaxPrf = g_mali_dvfs_steps - 1;
    }
    else
    {
        for(currPrf = (g_mali_dvfs_steps - 1); currPrf >= 0; currPrf--)
        {
            if(currPrf == 0)
            {
                s_uwDvfslimitMaxPrf = 0;
                break;
            }

            if ( mali_dvfs_profile[currPrf].freq <= (max_freq_limit/1000))
            {
                s_uwDvfslimitMaxPrf = currPrf;
                break;
            }
        }
    }

}
/*****************************************************************************
 function name  : pmqos_gpu_dfs_limit_min
 description    : limit the max frequence ,>xxKhz
 input vars     : u32 min_freq_limit
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 9/06/2013
    modify      : new

*****************************************************************************/
void pmqos_gpu_dfs_limit_min(u32 min_freq_limit)
{
    int currPrf;

    if( 0 == min_freq_limit)
    {
        s_uwDvfslimitMinPrf = 0;
    }
    else
    {
        for(currPrf = 0; currPrf <= (g_mali_dvfs_steps - 1); currPrf++)
        {
            if(currPrf == (g_mali_dvfs_steps - 1))
            {
                s_uwDvfslimitMinPrf = g_mali_dvfs_steps - 1;
                break;
            }

            if ( mali_dvfs_profile[currPrf].freq >= (min_freq_limit/1000))
            {
                s_uwDvfslimitMinPrf = currPrf;
                break;
            }
        }

    }
}

void mali_set_default_voltage(void)
{
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DDESTVOL_ADDR(0),0,6,mali_vol_cal_paras[0].vol_min_thd);
}
/*****************************************************************************
 function name  : pmqos_gpu_dfs_set_policy
 description    : set policy when model changes
 input vars     : void *profile --input memory src,orgnized by structure
                  unsigned int len --total bytes to be set
 output vars    : NA
 return value   : void
 calls          :
 called         :

 history        :
  1.data        : 27/01/2014
    modify      : new

*****************************************************************************/

void pmqos_gpu_dfs_set_policy(void *profile, unsigned int len)
{
    #if SFT_GPU_DVFS_PROFILE
    #else
    int i;
    memcpy(mali_dvfs_policy,profile,len);
    MALI_DEBUG_PRINT(3,( "pmqos_gpu_dfs_set_policy len=%d\n",len));
    for(i=0;i<MALI_DVFS_STEPS;i++)
    {
        MALI_DEBUG_PRINT(3,( "set_policy mali_dvfs_policy[%d]=%d,%d,%d,%d,%d,%d\n",i,mali_dvfs_policy[i].up_threshold,mali_dvfs_policy[i].down_threshold,mali_dvfs_policy[i].up_step,mali_dvfs_policy[i].down_step,mali_dvfs_policy[i].up_delay,mali_dvfs_policy[i].down_delay));
    }
    #endif
}

#ifdef CONFIG_DEBUG_FS

#define G3D_DFS_DEBUGFS_FILE_NAME   "mit1_g3d_dfs"
#define G3D_AVS_DEBUGFS_FILE_NAME   "mit1_g3d_avs"

int __init mali_dfs_debugfs_init(void)
{
    printk("mali_dfs_debugfs_init\n");
    debugfs_create_u32(G3D_DFS_DEBUGFS_FILE_NAME, 0664, NULL,  &s_uwDebugFsDvfsOn);


    return 0;
}
int __init mali_avs_debugfs_init(void)
{
    printk("mali_avs_debugfs_init\n");

    debugfs_create_u32(G3D_AVS_DEBUGFS_FILE_NAME, 0664, NULL,  &s_uwDebugFsAvsOn);

    return 0;
}
module_init(mali_dfs_debugfs_init);
module_init(mali_avs_debugfs_init);

#endif

#ifdef CONFIG_PROC_FS

#define GPU_PROCFS_NAME "gpu_stat"

static int mali_procfs_read(struct seq_file *buf, void *p)
{
	if(s_uwMaliDvfsUtilization > 255)
	{
		s_uwMaliDvfsUtilization = 255;
	}

	seq_printf(buf, "%d\n", s_uwMaliDvfsUtilization);

	return 0;
}

static int mali_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, mali_procfs_read, NULL);
}

static const struct file_operations mali_procfs_ops = {
    .open 		= mali_proc_open,
    .read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init gpu_procfs_init(void)
{
    printk("gpu_procfs_init\n");

	proc_create(GPU_PROCFS_NAME, 0, NULL, &mali_procfs_ops);

    return 0;
}

module_init(gpu_procfs_init);

#endif


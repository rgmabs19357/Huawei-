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
 * @file mali_platform.c
 * Platform specific Mali driver functions for a default platform
 */

/* BALONG LOWPOWER */

#include "mali_kernel_common.h"
#include "mali_osk.h"
#include "mali_balong_pmm.h"

#include <linux/clk.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <mach/delay.h>

/* hal software interfaces */
#include "drv_regulator_user.h"
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

#include <linux/pm_qos_params.h>

#include <hsad/config_mgr.h>


struct pm_qos_request_list g3d_pm_qos_req;

/*Macro defination begin-----------------------------------------*/
#define     MALI_DVFS_ENABLED           1
/*Macro defination end-------------------------------------------*/

/*Globle Variant Defination begin--------------------------------*/
struct clk              *mali_clock         = NULL;         /* mali clk IP */
struct clk              *mali_clock_bus     = NULL;         /* mali clk Bus */
struct clk              *mali_clock_x2x_m   = NULL;         /* mali clk x2x master */
struct clk              *mali_clock_x2x_s   = NULL;         /* mali clk x2x slave */
struct clk              *mali_clock_p2p     = NULL;         /* mali clk p2p */

struct regulator        *mali_regulator     = NULL;         /* mali g3d regulator */
int                     g_swGpuPowerState;                  /* globle power state,1 up ;0 down*/

/*static int mali_default_clk                 = 160;*/
/*static unsigned int mali_default_vol        = 900000;        0.9V */
static unsigned int GPU_MHZ                 = 1000000;
static u32 s_uwDebugFsPowerDown = 1;

int g_mali_dvfs_steps = 0;

/*Globle Variant Defination end----------------------------------*/
/*****************************************************************************
 function name  : mali_clk_get
 description    : clock get
 input vars     : void
 output vars    : NA
 return value   : mali_bool
 calls          : clk_get

 called         : mali_platform_powerup

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_bool mali_clk_get(void)
{

    if ( NULL == mali_clock )
    {
        /* open and get the clk and regulator without mali pmm */
        mali_clock      = clk_get(NULL,CLK_MALI);

        if (IS_ERR(mali_clock))
        {
            MALI_PRINT( ("MALI Error : failed to get source CLK_MALI\n"));
            return _MALI_OSK_ERR_FAULT;
        }
    }

    if ( NULL == mali_clock_bus )
    {
        /* open and get the clk and regulator without mali pmm */
        mali_clock_bus      = clk_get(NULL,CLK_AXI_MALI_BUS);

        if (IS_ERR(mali_clock_bus))
        {
            MALI_PRINT( ("MALI Error : failed to get source mali_clock_bus\n"));
            return _MALI_OSK_ERR_FAULT;
        }
    }

    if ( NULL == mali_clock_x2x_m )
    {
        /* open and get the clk and regulator without mali pmm */
        mali_clock_x2x_m      = clk_get(NULL,CLK_X2X_MALI_BRG_M);

        if (IS_ERR(mali_clock_x2x_m))
        {
            MALI_PRINT( ("MALI Error : failed to get source CLK_X2X_MALI_BRG_M\n"));
            return _MALI_OSK_ERR_FAULT;
        }
    }

    if ( NULL == mali_clock_x2x_s )
    {
        /* open and get the clk and regulator without mali pmm */
        mali_clock_x2x_s      = clk_get(NULL,CLK_X2X_MALI_BRG_S);

        if (IS_ERR(mali_clock_x2x_s))
        {
            MALI_PRINT( ("MALI Error : failed to get source CLK_X2X_MALI_BRG_S\n"));
            return _MALI_OSK_ERR_FAULT;
        }
    }

    if ( NULL == mali_clock_p2p )
    {
        /* open and get the clk and regulator without mali pmm */
        mali_clock_p2p      = clk_get(NULL,CLK_P2P_MALI_BRG_S);

        if (IS_ERR(mali_clock_p2p))
        {
            MALI_PRINT( ("MALI Error : failed to get source mali_clock_p2p\n"));
            return _MALI_OSK_ERR_FAULT;
        }
    }

    return MALI_TRUE;
}

/*****************************************************************************
 function name  : mali_clk_put
 description    : clock put
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : clk_put

 called         : deinit_mali_clock_regulator

 history        :
  1.data        : 31/01/2013
    modify      : new

*****************************************************************************/
void mali_clk_put(void)
{
    if (NULL != mali_clock_bus)
    {
        clk_put(mali_clock_bus);
    }

    if (NULL != mali_clock_p2p)
    {
        clk_put(mali_clock_p2p);
    }

    if (NULL != mali_clock_x2x_m)
    {
        clk_put(mali_clock_x2x_m);
    }

    if (NULL != mali_clock_x2x_s)
    {
        clk_put(mali_clock_x2x_s);
    }

    if (NULL != mali_clock)
    {
        clk_put(mali_clock);
    }

}

/*****************************************************************************
 function name  : mali_clk_set_rate
 description    : clock off mali by calling clk
 input vars     : unsigned int clk, unsigned int mhz
 output vars    : NA
 return value   : void
 calls          : clk_set_rate

 called         : mali_platform_powerdown

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
mali_bool mali_clk_set_rate(unsigned int clk, unsigned int mhz)
{
    int err;
    unsigned long rate = (unsigned long)clk * (unsigned long)mhz;

    MALI_DEBUG_PRINT(3, ("Mali platform: Setting frequency to %d mhz\n", clk));

    err = clk_set_rate(mali_clock, rate);

    if (err)
    {
        MALI_PRINT_ERROR(("Failed to set Mali clock: %d\n", err));

        return MALI_FALSE;
    }

    rate = clk_get_rate(mali_clock);

    MALI_PRINT(("Mali frequency %d\n", rate / mhz));
    return MALI_TRUE;
}

/*****************************************************************************
 function name  : mali_clk_get_rate
 description    : mali clk get rate as Mhz
 input vars     : unsigned int clk, unsigned int mhz
 output vars    : NA
 return value   : void
 calls          : clk_set_rate

 called         : mali_platform_powerdown

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
unsigned int mali_clk_get_rate(void)
{
    unsigned long rate;
    rate = clk_get_rate(mali_clock);
    rate = rate/GPU_MHZ;

    return rate;
}

/*****************************************************************************
 function name  : mali_clock_on
 description    : clock on mali by calling clk
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : clk_enable

 called         : mali_platform_powerup

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_clock_on(void)
{
    int err;

    /* firstly G3DHPMMASKEN = 0xf to disable HPM */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMMASKEN_ADDR(0),0,31,0xf);

    if( IS_ERR_OR_NULL(mali_clock_bus) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_bus is null\n"));
        return;
    }

    err = clk_enable(mali_clock_bus);

    if( IS_ERR_OR_NULL(mali_clock_x2x_m) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_x2x_m is null\n"));
        return;
    }

    err = clk_enable(mali_clock_x2x_m);

    if( IS_ERR_OR_NULL(mali_clock_x2x_s) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_x2x_s is null\n"));
        return;
    }

    err = clk_enable(mali_clock_x2x_s);

    if( IS_ERR_OR_NULL(mali_clock_p2p) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_p2p is null\n"));
        return;
    }

    err = clk_enable(mali_clock_p2p);

    if( IS_ERR_OR_NULL(mali_clock) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock is null\n"));
        return;
    }

    err = clk_enable(mali_clock);

    MALI_DEBUG_PRINT(1, ("clk_enable result %d \n",err));
}
/*****************************************************************************
 function name  : mali_clock_off
 description    : clock off mali by calling clk
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : clk_disable

 called         : mali_platform_powerdown

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_clock_off(void)
{
    /* firstly G3DHPMMASKEN = 0xf to disable HPM */
    phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DHPMMASKEN_ADDR(0),0,31,0xf);

    if( IS_ERR_OR_NULL(mali_clock_bus) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_bus is null\n"));
        return;
    }

    clk_disable(mali_clock_bus);

    if( IS_ERR_OR_NULL(mali_clock_x2x_m) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_x2x_m is null\n"));
        return;
    }

    clk_disable(mali_clock_x2x_m);

    if( IS_ERR_OR_NULL(mali_clock_x2x_s) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_x2x_s is null\n"));
        return;
    }

    clk_disable(mali_clock_x2x_s);

    if( IS_ERR_OR_NULL(mali_clock_p2p) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_clock_on : mali_clock_p2p is null\n"));
        return;
    }

    clk_disable(mali_clock_p2p);

    if( IS_ERR_OR_NULL(mali_clock) )
    {
        MALI_DEBUG_PRINT(1, ("error  mali_clock_off: mali_clock is null\n"));
        return;
    }

    clk_disable(mali_clock);

    MALI_DEBUG_PRINT(1, ("mali_clock_off \n"));
}

/*****************************************************************************
 function name  : mali_domain_powerup_finish
 description    : powerup finish to run
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : phy_reg_writel

 called         : mali_platform_powerup

 history        :
  1.data        : 01/02/2013
    modify      : new

*****************************************************************************/
void mali_domain_powerup_finish(void)
{
    /* set SC_ON PW_ISODIS0 = 0x00000002 to disable ISO */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(0), 0, 31, 0x2);

    /* set SC_ON PW_CLKEN0 = 0x00000002 to enable g3d clk gate */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(0), 0, 31, 0x2);

    udelay(1);

    /* powerup operation first remove reset of p2p  x2x */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(0), 0, 31, 0x8200000);

    /* set SC_ON PW_RSTDIS0 = 0x00000002 to leave reset */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(0), 0, 31, 0x2);
}
/*****************************************************************************
 function name  : mali_domain_powerdown_begin
 description    : powerdown begin with it
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : phy_reg_writel

 called         : mali_platform_powerdown

 history        :
  1.data        : 01/02/2013
    modify      : new

*****************************************************************************/
void mali_domain_powerdown_begin(void)
{
    /* set MALI clk disable SC_ON PW_CLKDIS0 = 0x00000002 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(0),0,31,0x2);

    /* set MALI ISO enable SC_ON PW_ISOEN0 = 0x00000002 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(0),0,31,0x2);

    /* set MALI power reset enable SC_ON PW_RSTEN0 = 0x00000002 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(0),0,31,0x2);
}
/*****************************************************************************
 function name  : mali_pll_close_vote
 description    : close pll vote
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : phy_reg_writel

 called         : mali_platform_powerdown

 history        :
  1.data        : 01/02/2013
    modify      : new

*****************************************************************************/
void mali_pll_close_vote(u32 voteMask)
{
    if ( 0x3 == (voteMask & 0x3) )
    {
        /* firstly set G3DCLKSEL[0] = 0 */
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DCLKSEL_ADDR(0),0,0,0);
    }

    /* set PMCTRL G3DPLL0CTRL[0] = 0 */
    if ( 0x1 == (voteMask & 0x1) )
    {
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL0CTRL_ADDR(0),0,0,0);
    }

    /* set PMCTRL G3DPLL1CTRL[0] = 0 */
    if ( 0x2 == (voteMask & 0x2) )
    {
        phy_reg_writel(SOC_PMCTRL_BASE_ADDR,SOC_PMCTRL_G3DPLL1CTRL_ADDR(0),0,0,0);
    }

}
/*****************************************************************************
 function name  : mali_regulator_enable
 description    : powerup mali by calling regulator
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : regulator_enable

 called         : mali_platform_powerup

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_regulator_enable(void)
{

    if( IS_ERR_OR_NULL(mali_regulator) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_regulator_enable : g3d_regulator is null\n"));
        return;
    }

    pm_qos_add_request(&g3d_pm_qos_req, PM_QOS_CPU_INT_LATENCY, 0);


    (void)regulator_enable(mali_regulator);
    MALI_DEBUG_PRINT(3, ("regulator_enable  \n"));

    MALI_DEBUG_PRINT(3, ("Mali voltage: %d\n", regulator_get_voltage(mali_regulator)));



}

/*****************************************************************************
 function name  : mali_regulator_disable
 description    : powerdown mali by calling regulator
 input vars     : void
 output vars    : NA
 return value   : void
 calls          : regulator_disable

 called         : mali_platform_powerdown

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_regulator_disable(void)
{
    mali_domain_powerdown_begin();

    if( IS_ERR_OR_NULL(mali_regulator) )
    {
        MALI_DEBUG_PRINT(1, ("error on mali_regulator_disable : g3d_regulator is null\n"));
        return;
    }

    (void)regulator_disable(mali_regulator);

    pm_qos_remove_request(&g3d_pm_qos_req);

    MALI_DEBUG_PRINT(3, ("regulator_disable\n"));

}

/*****************************************************************************
 function name  : init_mali_clock_regulator
 description    : mali clk and regulator init
 input vars     : void
 output vars    : NA
 return value   : mali_bool
 calls          : mali_clk_get

 called         : mali_platform_init

 history        :
  1.data        : 31/01/2013
    modify      : new

*****************************************************************************/
static mali_bool init_mali_clock_regulator(void)
{
    mali_bool ret       = MALI_TRUE;

    g_swGpuPowerState   = MALI_TRUE;

    /* regulator init */
    mali_regulator  = regulator_get(NULL, G3D_VDD);

    if (IS_ERR(mali_regulator))
    {
        MALI_PRINT( ("MALI Error : failed to get mali_vdd\n"));
        return _MALI_OSK_ERR_FAULT;
    }
    /* regulator set votage */
    mali_set_default_voltage();
    mali_regulator_enable();

    /* clk init */
    if (mali_clock != 0)
    {
        return ret;
    }
    if (!mali_clk_get())
    {
        MALI_PRINT(("Error: Failed to get Mali clock\n"));
        return MALI_FALSE;
    }

    /* CLK on and set rate */
    mali_clock_on();

    MALI_DEBUG_PRINT(2, (" init mali clock regulator ok\n"));

    mali_domain_powerup_finish();

    return MALI_TRUE;

}

/*****************************************************************************
 function name  : deinit_mali_clock_regulator
 description    : mali clk and regulator deinit
 input vars     : void
 output vars    : NA
 return value   : mali_bool
 calls          : mali_clk_put,mali_regulator_disable

 called         : mali_platform_deinit

 history        :
  1.data        : 31/01/2013
    modify      : new

*****************************************************************************/
static mali_bool deinit_mali_clock_regulator(void)
{
    if ( (NULL == mali_clock) || (NULL == mali_regulator))
    {
        return MALI_TRUE;
    }

    /* powerdown */
    mali_platform_powerdown();

    /* CLK */
    mali_clk_put();

    /* REGULATOR */
    regulator_put(mali_regulator);

    return MALI_TRUE;
}


/*****************************************************************************
 function name  : mali_platform_powerdown
 description    : powerdown mali by calling interface of low software
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : AMAPI_mali_clk_off
                  AMAPI_mali_power_down
 called         : mali_platform_power_mode_change

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
_mali_osk_errcode_t mali_platform_powerdown(void)
{
    MALI_DEBUG_PRINT(3,("power down is called in mali_platform_powerdown state %x \n", g_swGpuPowerState));

    /* debug fs Powerdown */
    if (0==s_uwDebugFsPowerDown)
        MALI_SUCCESS;

    if (g_swGpuPowerState != MALI_FALSE)
    {
        MALI_DEBUG_PRINT( 3,("disable clock\n"));

        /*info DVFS to stop*/
        pwrctrl_dfs_gpu_disable();

        /*clk and regulator off*/
        mali_regulator_disable();
        mali_clock_off();
        mali_pll_close_vote( (1<<0) | (1<<1));
    }
    else
    {
        MALI_PRINT(("mali_platform_powerdown gpu_power_state == 0 \n"));
    }

    g_swGpuPowerState = MALI_FALSE;

    MALI_SUCCESS;
}

/*****************************************************************************
 function name  : mali_platform_powerup
 description    : powerup mali by calling interFace of low software
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : AMAPI_mali_power_up
                  AMAPI_mali_clk_on
 called         : mali_platform_power_mode_change

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
_mali_osk_errcode_t mali_platform_powerup(void)
{
    MALI_DEBUG_PRINT(3,("power up is called in mali_platform_powerup state %x \n", g_swGpuPowerState));


    if (MALI_FALSE == g_swGpuPowerState)
    {
        MALI_DEBUG_PRINT(4,("enable clock and power\n"));
        mali_regulator_enable();
        mali_clock_on();
        mali_domain_powerup_finish();

        /*enable DVFS to run*/
        pwrctrl_dfs_gpu_enable();

    }

    g_swGpuPowerState = MALI_TRUE;

    MALI_SUCCESS;
}

/*****************************************************************************
 function name  : mali_platform_init
 description    : init mali by calling interFace of low software and dvfs
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : mali_clock_init
                  mali_dvfs_status_init
 called         : mali_driver_init

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
_mali_osk_errcode_t mali_platform_init(void)
{
    #if MALI_DVFS_ENABLED
    mali_bool   initRet;
    int mali_dvfs_prof;
    #endif

    /* open and get the clk and regulator without mali pmm */
    init_mali_clock_regulator();

    #if MALI_DVFS_ENABLED
	 initRet = get_hw_config_int("pwc/gfreq", &mali_dvfs_prof, NULL);

	 if ( initRet != MALI_TRUE )
	 {
		MALI_DEBUG_PRINT(2, ("mali_platform_init_dvfs failed\n"));
		return _MALI_OSK_ERR_FAULT;
	 }
	 else if( 700000 == mali_dvfs_prof)
	 {
		g_mali_dvfs_steps = 5;
	 }
	 else if( 533000 == mali_dvfs_prof)
	 {
		g_mali_dvfs_steps = 4;
	 }

	 MALI_DEBUG_PRINT(2, ("mali_platform_init_dvfs, mali_dvfs_steps = %d\n", g_mali_dvfs_steps));
    #endif

    /* init the dvfs PWRC registers */
    pwrctrl_g3d_dfs_init();

    #if SFT_GPU_DVFS_PROFILE
    /* firstly on SFT to down profile when boot */
    mali_avs_dfs_target_profile(0,MALI_FALSE);
    #endif

    #if MALI_DVFS_ENABLED
    /* init the dvfs AND work queue */
    initRet                 = mali_dvfs_status_init(MALI_DVFS_HOLD);

    if ( initRet != MALI_TRUE )
    {
        MALI_DEBUG_PRINT(2, ("mali_platform_init_dvfs failed\n"));
        return _MALI_OSK_ERR_FAULT;
    }
    #endif
    #if MALI_DVFS_ENABLED
        MALI_DEBUG_PRINT(2, ("set gpu min_freq to max when the platform is power up\n"));
        pmqos_gpu_dfs_limit_min(mali_dvfs_prof);
    #endif

    MALI_SUCCESS;
}

/*****************************************************************************
 function name  : mali_platform_deinit
 description    : deinit mali by calling interFace of low software and dvfs
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : mali_clock_deinit
                  mali_dvfs_status_deinit
 called         : mali_driver_exit

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
_mali_osk_errcode_t mali_platform_deinit(void)
{
    #if MALI_DVFS_ENABLED
    mali_dvfs_status_deinit();
    #endif

    /* release clk and regulator */
    deinit_mali_clock_regulator();

    MALI_SUCCESS;
}

/*****************************************************************************
 function name  : mali_platform_deinit
 description    : power mode change action
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : mali_platform_powerup
                  mali_platform_powerdown
 called         : mali_pm_powerup
                  mali_pm_powerdown
                  mali_pm_runtime_suspend
                  mali_pm_runtime_resume

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
_mali_osk_errcode_t mali_platform_power_mode_change(mali_power_mode power_mode)
{
    switch (power_mode)
    {
        case MALI_POWER_MODE_ON:
            if (MALI_FALSE == g_swGpuPowerState)
            {
                mali_platform_powerup(); /*power up include clk up*/
            }
        break;
        case MALI_POWER_MODE_LIGHT_SLEEP:
        case MALI_POWER_MODE_DEEP_SLEEP:

            if (MALI_TRUE == g_swGpuPowerState)
            {
                mali_platform_powerdown();/*power down include clk down*/
            }

        break;
        default:
            MALI_DEBUG_PRINT( 3,("error input to mali_platform_power_mode_change\n"));
        break;
    }

    MALI_SUCCESS;
}

/*****************************************************************************
 function name  : mali_platform_deinit
 description    : mali ddk send utilization here when timer=50 out
 input vars     : void
 output vars    : NA
 return value   : _mali_osk_errcode_t
 calls          : mali_dvfs_handler

 called         : calculate_gpu_utilization

 history        :
  1.data        : 18/10/2012
    modify      : new

*****************************************************************************/
void mali_gpu_utilization_handler(u32 utilization)
{
    /*DVFS when power on*/
    if ( MALI_TRUE == g_swGpuPowerState )
    {
    #if MALI_DVFS_ENABLED
        if(!mali_dvfs_handler(utilization))
            MALI_DEBUG_PRINT(1,( "error on mali dvfs status in utilization\n"));
    #endif
    }

    return;
}

void set_mali_parent_power_domain(void* dev)
{
}

#ifdef CONFIG_DEBUG_FS

#define G3D_POWERDOWN_DEBUGFS_FILE_NAME "mit1_g3d_powerdown"
int __init mali_powerdown_debugfs_init(void)
{

    printk("mali_powerdown_debugfs_init\n");

    debugfs_create_u32(G3D_POWERDOWN_DEBUGFS_FILE_NAME, 0664, NULL,  &s_uwDebugFsPowerDown);

    return 0;
}
module_init(mali_powerdown_debugfs_init);

#endif


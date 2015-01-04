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
 * @file mali_platform.h
 * Platform specific Mali driver functions
 */

#ifndef __MALI_BALONG_H__
#define __MALI_BALONG_H__

#include "mali_osk.h"

#ifdef __cplusplus
extern "C" {
#endif

/*Macro defination*/
#ifdef  CONFIG_MACH_HI6620OEM
#define SFT_GPU_DVFS_PROFILE    0
#else
#define SFT_GPU_DVFS_PROFILE    1
#endif

#if SFT_GPU_DVFS_PROFILE
#define MALI_DVFS_STEPS         3
#else
#define MALI_DVFS_STEPS         5
#endif

#define MALI_UTILIZATION_NUM    5

typedef enum mali_dvfs_status_tag
{
    MALI_DVFS_DECREASE_LOWEST   = 0,            /**< Freq down to lowest level*/
    MALI_DVFS_DECREASE          = 2,            /**< Freq down */
    MALI_DVFS_HOLD              = 3,            /**< Freq No change */
    MALI_DVFS_INCREASE          = 4,            /**< Freq up */
    MALI_DVFS_INCREASE_HIGHEST  = 6,            /**< Freq up TO highest level*/
    MALI_DVFS_BUTT,
} mali_dvfs_status;

/** @brief description of power change reasons
 */
typedef enum mali_power_mode_tag
{
    MALI_POWER_MODE_ON,           /**< Power Mali on */
    MALI_POWER_MODE_LIGHT_SLEEP,  /**< Mali has been idle for a short time, or runtime PM suspend */
    MALI_POWER_MODE_DEEP_SLEEP,   /**< Mali has been idle for a long time, or OS suspend */
} mali_power_mode;

/*kernel acpu - mcu APIs*/
extern int pwrctrl_dfs_gpu_target(int step);
extern int pwrctrl_dfs_gpu_disable(void);
extern int pwrctrl_dfs_gpu_enable(void);

/*mali dvfs*/
mali_dvfs_status get_mali_dvfs_status(void);
mali_bool mali_dvfs_status_init(mali_dvfs_status maliDvfsStatus);
void mali_dvfs_status_deinit(void);
mali_bool mali_dvfs_handler(u32 utilization);

/*platform clk and power*/
_mali_osk_errcode_t mali_platform_powerup(void);
_mali_osk_errcode_t mali_platform_powerdown(void);

/** @brief Platform specific setup and initialisation of MALI
 *
 * This is called from the entrypoint of the driver to initialize the platform
 *
 * @return _MALI_OSK_ERR_OK on success otherwise, a suitable _mali_osk_errcode_t error.
 */
_mali_osk_errcode_t mali_platform_init(void);

/** @brief Platform specific deinitialisation of MALI
 *
 * This is called on the exit of the driver to terminate the platform
 *
 * @return _MALI_OSK_ERR_OK on success otherwise, a suitable _mali_osk_errcode_t error.
 */
_mali_osk_errcode_t mali_platform_deinit(void);

/** @brief Platform specific powerdown sequence of MALI
 *
 * Notification from the Mali device driver stating the new desired power mode.
 * MALI_POWER_MODE_ON must be obeyed, while the other modes are optional.
 * @param power_mode defines the power modes
 * @return _MALI_OSK_ERR_OK on success otherwise, a suitable _mali_osk_errcode_t error.
 */
_mali_osk_errcode_t mali_platform_power_mode_change(mali_power_mode power_mode);


/** @brief Platform specific handling of GPU utilization data
 *
 * When GPU utilization data is enabled, this function will be
 * periodically called.
 *
 * @param utilization The workload utilization of the Mali GPU. 0 = no utilization, 256 = full utilization.
 */
void mali_gpu_utilization_handler(u32 utilization);

/** @brief Setting the power domain of MALI
 *
 * This function sets the power domain of MALI if Linux run time power management is enabled
 *
 * @param dev Reference to struct platform_device (defined in linux) used by MALI GPU
 */
void set_mali_parent_power_domain(void* dev);
unsigned int mali_clk_get_rate(void);
void pwrctrl_g3d_dfs_init(void);
void mali_pll_close_vote(u32 voteMask);
void mali_avs_dfs_target_profile(int target, u32 up);
void pmqos_gpu_dfs_get_current_profile(u32 *profile_id);
void pmqos_gpu_get_current_func(unsigned int *curr_func);
void pmqos_gpu_set_current_func(unsigned int target_func);
void pmqos_gpu_dfs_lock(u32 lock_profile);
void pmqos_gpu_dfs_unlock(void);
void pmqos_gpu_dfs_limit_max(u32 max_freq_limit);
void pmqos_gpu_dfs_limit_min(u32 min_freq_limit);
void mali_set_default_voltage(void);
void pmqos_gpu_dfs_set_policy(void *profile, unsigned int len);
#ifdef __cplusplus
}
#endif
#endif

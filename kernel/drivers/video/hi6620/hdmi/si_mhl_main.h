/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_mhl_main.h
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/

#ifndef __SI_MHL_MAIN_H__
#define __SI_MHL_MAIN_H__
#include <linux/kernel.h>
#include <linux/wakelock.h>
#include <linux/mutex.h>
#include <linux/switch.h>
#include <linux/input.h>

#include "si_edid.h"
#include "si_mhl_hw.h"

#include <linux/pm_qos_params.h>

#define HDMI_FOR_CERTIFICATION       0
#define USE_3D                       0     /* 3D feature is not implemented */
#define ENABLE_REG_DUMP              1
#define ENABLE_MOCK_24FPS            0
#define USE_PEER_ABORT               0
#define WRITE_BURST                  0
#define USE_PP_MODE                  0     /* Packed pixel mode feature is not implemented */

typedef enum _hdmi_s3d_frame_structure {
    HDMI_S3D_FRAME_PACKING          = 0,    /* frame packing type of 3d */
    HDMI_S3D_FIELD_ALTERNATIVE      = 1,    /* field alternative type of 3d */
    HDMI_S3D_LINE_ALTERNATIVE       = 2,    /* line alternative type of 3d */
    HDMI_S3D_SIDE_BY_SIDE_FULL      = 3,    /* side by side full type of 3d */
    HDMI_S3D_L_DEPTH                = 4,    /* L depth type of 3d */
    HDMI_S3D_L_DEPTH_GP_GP_DEPTH    = 5,    /* L depth gp gp depth type of 3d */
    HDMI_S3D_TOP_TO_BOTTOM          = 6,    /* top to bottom type of 3d */
    HDMI_S3D_SIDE_BY_SIDE_HALF      = 8,    /* side by side half type of 3d */
    HDMI_2D                         = 0xFF  /* 2d type not 3d type */
} hdmi_s3d_frame_structure;

/* Subsampling types used for Sterioscopic 3D over HDMI. Below HOR
 * stands for Horizontal, QUI for Quinxcunx Subsampling, O for odd fields,
 * E for Even fields, L for left view and R for Right view */
typedef enum _hdmi_s3d_subsampling_type {
    /* horizontal subsampling with odd fields
     * from left view and even fields from the right view */
    HDMI_S3D_HOR_OL_OR = 0,
    HDMI_S3D_HOR_OL_ER = 1,
    HDMI_S3D_HOR_EL_OR = 2,
    HDMI_S3D_HOR_EL_ER = 3,
    HDMI_S3D_QUI_OL_OR = 4,
    HDMI_S3D_QUI_OL_ER = 5,
    HDMI_S3D_QUI_EL_OR = 6,
    HDMI_S3D_QUI_EL_ER = 7
} hdmi_s3d_subsampling_type;

typedef struct _hdmi_s3d_info {
    bool subsamp;                            /* whether has subsamp_pos info */
    hdmi_s3d_subsampling_type subsamp_pos;   /* Subsampling used in Vendor Specific Infoframe */
    hdmi_s3d_frame_structure  type;          /* Frame Structure for the S3D Frame */
} hdmi_s3d_info;


typedef struct _hdmi_device {
    /* device */
    struct platform_device *pdev;

    /* mutex */
    struct mutex lock;    /*mutex of video register set*/
    struct mutex lock_aux;/*mutex of audio register set*/

    /* config */
    hdmi_config cfg;    /* current config */
    hdmi_core_infoframe_avi avi_param;
    hdmi_audio_format audio_fmt;
    hw_audio_configure audio_core_cfg;

    /* timings */
    int code;                       /* current timing code */
    int mode;                       /* current timing mode */
    hdmi_video_timings *timings;    /* current timing array */
    bool manual_set;                /* for manual set timing*/
    bool auto_set;                  /* for auto set timing */
    int originalcode;               /* code back up when auto set is true */

    /* hpd enable*/
    bool hpd_enabled;
    bool last_hpd_enabled;

    /* 3d */
    bool s3d_enabled;                   /* current 3d mode is enabled */
    hdmi_s3d_frame_structure  s3d_type; /* current 3d type */

    hdmi_display_state state;       /* current display state */

    /* power */
    hdmi_power_state power_state;   /* current power */
    struct switch_dev hpd_switch;    /* switch device*/

    /*audio */
    int sample_freq;
    int sample_size;
    int layout;
    int audiotype;
    hdmi_core_hdmi_dvi hdmi_mode;    /* hdmi mode */
    bool bsio;
    bool audiochanged;

    /* hdmi status */
    bool connected;             /* cable is connected */
    bool hpd_current_state;     /* hpd state - last notification state */
    bool edid_set;              /* edid data is readed */
    bool custom_set;            /* custom set video timing code */

    /* move irq section to this for UT test */
    /* irq */
    int    irq_is_init;             /* whether the irq has been inited*/
    struct work_struct *work;       /* irq work */
    struct wake_lock wake_lock;
    struct wake_lock usb_otg_lock;  /* for USB OTG wakeup */
    
    struct input_dev *rcp_dev;
    
    bool has_request_ddr;
	struct pm_qos_request_list ddr_qos_request;

    struct pm_qos_request_list cpu_qos_request;

 }hdmi_device;

// Standard result codes are in the range of 0 - 4095
typedef enum _SiiResultCodes_t
{
    PLATFORM_SUCCESS = 0,           // Success.
    SII_SUCCESS      = 0,           // Success.
    SII_ERR_FAIL,                   // General failure.
    SII_ERR_INVALID_PARAMETER,      //
    SII_ERR_IN_USE,                 // Module already initialized.
    SII_ERR_NOT_AVAIL,              // Allocation of resources failed.
} SiiResultCodes_t;

typedef enum TimerId
{
     TIMER_0 = 0,		// DO NOT USE - reserved for TimerWait()
     TIMER_POLLING,		// Reserved for main polling loop
     TIMER_ABORT,       //used for 2s timer (Tabort_next)
     TIMER_COUNT		// MUST BE LAST!!!!
} timerId_t;

#define LOG_TAG                    "[mhl]"
#define DEBUG_VERSION              0   /* 1:msgs printed; 0:no msgs */

#ifdef CONFIG_DEBUG_FS
enum {
    MHL_DEBUGFS_FLAG_CLOSE_ALL   =  0x00,
    MHL_DEBUGFS_FLAG_OPEN_DEBUG  =  0x01,
};

void SII_DBG_PRINT(const char* fmt, ...);
void logd(const char* fmt, ...);
#else 
#define SII_DBG_PRINT(fmt, ...)
#define logd(fmt, ...)
#endif

/* Don't use these if we use debugfs to disable debug printk. */
#define IN_FUNCTION                
#define OUT_FUNCTION              

/* Don't use the following method to control debug output after using debugfs */
/*
#if DEBUG_VERSION
#define SII_DBG_PRINT(fmt, ...)    pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define logd(fmt, ...)             pr_info(LOG_TAG"[D]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define SII_DBG_PRINT(fmt, ...)
#define logd
#endif

#define IN_FUNCTION                SII_DBG_PRINT ("in.\n")
#define OUT_FUNCTION               SII_DBG_PRINT ("out.\n")
*/

#define logi(fmt, ...)             pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define logw(fmt, ...)             pr_warn(LOG_TAG"[W]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define loge(fmt, ...)             pr_err(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define SII_INF_PRINT(fmt, ...)    pr_info(LOG_TAG"[I]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define SII_WRN_PRINT(fmt, ...)    pr_warn(LOG_TAG"[W]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define SII_ERR_PRINT(fmt, ...)    pr_err(LOG_TAG"[E]:%s:%d: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__)

extern int hdmi_audio_set_param(int sample_freq, int sample_size, bool bsio,
                                  int layout, int audiotype);
extern void hdmi_process_tmds_status(bool tmds_enable);
extern void hdmi_process_cbus_connection(bool connection);
extern int hdmi_control_notify_hpd_status(bool onoff);
extern void hdmi_init_partial_data(void);
extern int mhl_rcp_register_input_dev(void);
extern int mhl_rcp_unregister_input_dev(void);
#endif  // __SI_MHL_MAIN_H__

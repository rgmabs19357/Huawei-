/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_mhl_main.c
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/

#include <linux/interrupt.h>
#include <linux/switch.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/timer.h>
#include <linux/mhl/mhl.h>

#include "k3_fb.h"

#include "si_mhl_main.h"
#include "si_drv_mhl_tx.h"
#include "si_mhl_hw.h"
#include "si_mhl_tx.h"

#ifdef CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#endif

#include <hisi/drv_hisi_mutex_service.h>

extern  hdmi_hw_res     hw_res;
extern  mhlTx_config_t  g_PlumTxConfig;
uint8_t     edid[HDMI_EDID_MAX_LENGTH]         = {0};
hdmi_device hdmi                               = {0};
static struct k3_panel_info hdmi_panel_info    = {0};
static struct k3_fb_panel_data hdmi_panel_data = {
    .panel_info = &hdmi_panel_info,
};
static struct timer_list hdmi_timer;

static unsigned short rcpKeyCode[] =
{
        KEY_MENU,/* 139 */
        KEY_SELECT,/* 0x161 */
        KEY_UP,/* 103 */
        KEY_LEFT,/* 105 */
        KEY_RIGHT,/* 106 */
        KEY_DOWN,/* 108 */
        KEY_EXIT,/* 174 */
        KEY_1, /* 0x02 */
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9, /* 0x10 */
        KEY_0,
        KEY_DOT,/* 52 */
        KEY_ENTER,/* 28 */
        KEY_CLEAR,/* 0x163 *//* DEL */
        KEY_SOUND,/* 0x213 */
        KEY_PLAY,/* 207 */
        KEY_PAUSE,/* 119 */
        KEY_STOP,/* 128 */
        KEY_FASTFORWARD,/* 208 */
        KEY_REWIND,/* 168 */
        KEY_EJECTCD,/* 161 */
        KEY_FORWARD,/* 159 */
        KEY_BACK,/* 158 */
        KEY_PLAYCD,/* 200 */
        KEY_PAUSECD,/* 201 */
        KEY_STOP,/* 128 */
        KEY_F1,/* 59 */
        KEY_F2,/* 60 */
        KEY_F3,
        KEY_F4,
        KEY_F5,/* 63 */
        KEY_CHANNELUP, /* 0x192 */
        KEY_CHANNELDOWN, /* 0x193 */
        KEY_MUTE, /* 113 */
        KEY_PREVIOUS, /* 0x19c */
        KEY_VOLUMEDOWN, /* 114 */
        KEY_VOLUMEUP, /* 115 */
        KEY_RECORD, /* 167 */
        KEY_REPLY,
        KEY_PLAYPAUSE,
        KEY_PREVIOUSSONG, /* add  */
        KEY_BACKSPACE, /* DEL */
        KEY_HOMEPAGE
};

extern bool HDCP_Switch_On;

static int enable_hpd(bool enable);
static ssize_t hdmi_get_timing_list(char *buf, bool mhl_check);
static int hdmi_control_create_sysfs(struct platform_device *dev);
static void hdmi_control_remove_sysfs(struct platform_device *dev);
#if USE_3D
static ssize_t hdmi_control_3d_show(struct device *dev,
                                      struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_3d_store(struct device *dev,
                                       struct device_attribute *attr,
                                       const char *buf, size_t size);
#endif
static ssize_t hdmi_control_audio_show(struct device *dev,
                                         struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_bufisfree_store(struct device *dev,
                                                         struct device_attribute *attr,
                                                         const char *buf, size_t size);
static ssize_t hdmi_control_connected_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_connected_store(struct device *dev,
                                                       struct device_attribute *attr,
                                                       const char *buf, size_t size);
static int hdmi_control_create_device_file(struct device *dev,
          const struct device_attribute *attr);
static ssize_t hdmi_control_defaultcode_show(struct device *dev,
                                          struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_edidbin_show(struct device *dev,
                                        struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_edid_show(struct device *dev,
                                        struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_edid_show_all(struct device *dev,
                                        struct device_attribute *attr, char *buf);
#if USE_HDCP
static ssize_t hdmi_control_hdcp_show(struct device *dev,
                                        struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_hdcp_store(struct device *dev,
                                         struct device_attribute *attr,
                                         const char *buf, size_t size);
#endif
static ssize_t hdmi_control_hpd_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_hpd_store(struct device *dev,
                                        struct device_attribute *attr,
                                        const char *buf, size_t size);
#if ENABLE_REG_DUMP
static ssize_t hdmi_control_regbin_show(struct device *dev,
                                        struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_regbin_store(struct device *dev,
                                      struct device_attribute *attr, const char *buf, size_t size);
#endif
static void hdmi_control_remove_device_file(struct device *dev,
          const struct device_attribute *attr);
static ssize_t hdmi_control_reset(struct device *dev,
                                                         struct device_attribute *attr,
                                                         const char *buf, size_t size);

static ssize_t hdmi_control_s3dsupport_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);

static ssize_t hdmi_control_timing_show(struct device *dev,
                                          struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_timing_store(struct device *dev,
          struct device_attribute *attr,
          const char *buf, size_t size);
static ssize_t hdmi_control_audiosupport_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);
static ssize_t mhl_control_devcapbin_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);
static ssize_t hdmi_control_reg_show(struct device *dev,
                                       struct device_attribute *attr, char *buf);
static int hdmi_regist_fb(struct platform_device *pdev);
static int set_custom_timing_code(int code, int mode);
static irqreturn_t mhl_interrupt_handler(int irq, void *arg);

/******************************************************************************
* Function:       hdmi_init_partial_data
* Description:    Initialize hdmi partial global data
* Input:
* Output:
* Return:
*******************************************************************************/
void hdmi_init_partial_data(void)
{
    /* reset config data */
    memset(&hdmi.cfg, 0, sizeof(hdmi.cfg));
    memset(&hdmi.avi_param, 0, sizeof(hdmi.avi_param));
    memset(&hdmi.audio_fmt, 0, sizeof(hdmi.audio_fmt));
    memset(&hdmi.audio_core_cfg, 0, sizeof(hdmi.audio_core_cfg));

    hdmi.s3d_enabled       = false;
    hdmi.s3d_type          = HDMI_2D;
    hdmi.cfg.s3d_structure = HDMI_2D;

    /* reset hdmi status */
    hdmi.connected         = false;
    hdmi.edid_set          = false;
    hdmi.custom_set        = false;
   if(hdmi.auto_set)
   {
        if(hdmi.originalcode > HDMI_CODE_VESA_OFFSET)
        {
            hdmi.code  = hdmi.originalcode - HDMI_CODE_VESA_OFFSET;
            hdmi.mode = HDMI_CODE_TYPE_VESA;
        }
        else
        {
            hdmi.code  = hdmi.originalcode;
            hdmi.mode = HDMI_CODE_TYPE_CEA;
        }
        hdmi.auto_set          = false;
   }

    /* recover user config */
/*    hdmi.manual_set     = false;
    hdmi.code               = edid_get_default_code();
    hdmi.mode              = HDMI_DEFAULT_TIMING_MODE;
    hdmi.timings           = edid_get_timings_byindex(get_timings_index());
*/
    /* reset audio default param */
    hdmi.sample_freq       = 48000;
    hdmi.sample_size       = HDMI_SAMPLE_16BITS;
    hdmi.bsio              = false;
    hdmi.layout            = LAYOUT_2CH;
    hdmi.audiotype         = 1;
    hdmi.audiochanged      = false;

    hdmi.has_request_ddr   = false;
}

/******************************************************************************
* Function:       hdmi_control_notify_hpd_status
* Description:    notify cable connection state to user space
* Input:          connection state
* Output:
* Return:
*******************************************************************************/
int hdmi_control_notify_hpd_status(bool onoff) //UT YANG
{
    int ret   = -1;
    int count = 30;

    logi("hpd state: %d, hpd current state: %d. \n", onoff, hdmi.hpd_current_state);

    if (onoff == hdmi.hpd_current_state) {
        logi("don't need to send hpd message.\n");
        return 0;
    }

    hdmi.hpd_current_state = onoff;
    hdmi.connected = onoff;          /* we may use one of both(connected/hpd_current_state) */
    hdmi.audiochanged = true;

    ret = kobject_uevent(&hdmi.pdev->dev.kobj, onoff ? KOBJ_ADD : KOBJ_REMOVE);
    while (ret && (-2 != ret) && count > 0) {
        ret = kobject_uevent(&hdmi.pdev->dev.kobj, onoff ? KOBJ_ADD : KOBJ_REMOVE);

        /* kobject_uevent seems to always return an error (-2) even success. */
        if (ret && (-2 != ret)) {
            logw("send hot plug event err: %d and retry.\n", ret);
        }

        if (!onoff) {
            break;
        }

        msleep(300);
        count --;
    }

    /* config switch */
    switch_set_state(&hdmi.hpd_switch, onoff ? 1 : 0);

    k3fb_set_hdmi_state(onoff);

    return 0;
}

/******************************************************************************
* Function:       set_custom_timing_code
* Description:    set code and mode to hdmi device
* Input:          timing code and mode
* Output:
* Return:
*******************************************************************************/
static int set_custom_timing_code(int code, int mode)
{
    int ret   = 0;

    hdmi.code = code;
    hdmi.mode = mode;
    hdmi.timings = edid_get_timings_byindex(get_timings_index());

        /* Added for video play */
        if (hdmi.custom_set == true && hdmi.hpd_current_state == true) {
            hdmi.hpd_current_state = false;
            hdmi_control_notify_hpd_status(true);
            hdmi.custom_set = false;
        }

    return ret;
}

/******************************************************************************
* Function:       enable_hpd
* Description:    enable hpd will turn on hdmi device, disable will turn it off
* Input:          true or false
* Output:
* Return:         0 for success, or error code.
*******************************************************************************/
static int enable_hpd(bool enable)
{
    int ret = 0;

    IN_FUNCTION;
    logi("current hpd status is %d, enable is %d\n", hdmi.hpd_enabled, enable);

    if (hdmi.hpd_enabled == enable) {
        logw("set hpd %d is same as current state, do nothing.\n", enable);
        OUT_FUNCTION;
        return 0;
    }

    hdmi.hpd_enabled = enable;

    mutex_lock(&hdmi.lock);
    if (enable) {
        hw_core_power_on();

        /* HDMI daemon will use FB_BLANK_UNBLANK to initial fb1 when MHL cable is connected. */
        //ret = k3_fb1_blank(FB_BLANK_UNBLANK);

        /* MHL IP and TX global variable initialize */
        SiiInitialize();

        if (hdmi.irq_is_init == 0) {
            /* after request_irq, the interrupt has been enabled */
            ret = request_irq(hw_res.irq, mhl_interrupt_handler, 0, "mhl_irq", (void *)0);
            if (ret) {
                loge("request_irq error %d.\n", ret);
            }
            hdmi.irq_is_init = 1;
        }

        hw_enable_irqs(true);

    } else {
        ret = k3_fb1_blank(FB_BLANK_POWERDOWN);
        hdmi_pw_power_off();
    }

    mutex_unlock(&hdmi.lock);

    OUT_FUNCTION;
    return ret;
}

int hdmi_preempt_func(int param)
{
    hdmi_process_tmds_status(false);
    return 0;
}
/******************************************************************************
* Function:       hdmi_process_tmds_status
* Description:    hdmi process the TMDS status change of PLUM MHL
* Input:          true: TMDS enable; false: TMDS disable
* Output:
* Return:
*******************************************************************************/
void hdmi_process_tmds_status(bool tmds_enable)
{
    int ret;

    if (tmds_enable) 
    {
        ret = hisi_mutex_mng_service_start(MUTEX_SERVICE_HDMI_ID, &hdmi_preempt_func);
        if(START_OK != ret)
        {
            loge("hisi_mutex_mng_service_start hdmi fail %d\n", ret);
            return;
        }

        hdmi_pw_power_on_full();
        update_set_timing_code(&hdmi.mode, &hdmi.code);
        mhl_enable_cfg();

        ret = hdmi_control_notify_hpd_status(true);
        if (ret) {
            logw("notify hpd status fail: %d.\n", ret);
        }
        add_timer(&hdmi_timer);
    } 
    else
    {
       del_timer(&hdmi_timer);
       hdmi_pw_power_on_min();

        ret = hdmi_control_notify_hpd_status(false);
        if (ret) {
            logw("notify hpd status fail: %d.\n", ret);
            return;
        }

        ret = hisi_mutex_mng_service_stop(MUTEX_SERVICE_HDMI_ID);
        if(STOP_OK != ret)
        {
            loge("hisi_mutex_mng_service_stop hdmi fail %d\n", ret);
            return;
        }
    }
}

/******************************************************************************
* Function:       hdmi_process_cbus_connection
* Description:    hdmi process the cbus connection/disconnection event
* Input:          true: cbus connection; false: cbus disconnection
* Output:
* Return:
*******************************************************************************/
void hdmi_process_cbus_connection(bool connection)
{
    if (connection) {

    } else {
        memset(edid, 0, sizeof(edid));

        /* Others operations are executed in TMDS_DISABLE event. */
    }
}

/******************************************************************************
* Function:       hdmi_get_timing_list
* Description:    get timing codes and store to buf
* Input:          mhl_check: true: check mhl and return mhl supported code, false: not check
* Output:         buf: with video timing codes
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_get_timing_list(char *buf, bool mhl_check)
{
    int size                 = 0;
    char* p                  = buf;

    bool audio_support = false;
    bool s3d_enabled = false;

    IN_FUNCTION;

    if (false == edid_is_valid_edid(edid)) {
        loge("edid isn't readed, and use default code.\n");
        OUT_FUNCTION;
        return snprintf(buf, PAGE_SIZE, "%d\n", hdmi.code);
    }

    /*
     *  Verify if the sink supports audio
     */
    /* check if EDID has CEA extension block */
    if ((((hdmi_edid *)edid)->extension_edid != 0x00)
        /* check if CEA extension block is version 3 */
        && (3 == ((hdmi_edid *)edid)->extention_rev)
        /* check if extension block has the IEEE HDMI ID*/
        &&(edid_has_ieee_id(edid))
        /* check if sink supports basic audio */
        &&(((hdmi_edid *)edid)->num_dtd & HDMI_AUDIO_BASIC_MASK)) {

        audio_support = true;
    }

    edid_get_timing_code_from_videoblock(&p, &size, mhl_check);
    edid_get_timing_code_from_b0DTD(&p, &size, mhl_check, s3d_enabled);
    edid_get_timing_code_from_SVD(&p, &size, mhl_check, s3d_enabled);
    edid_get_timing_code_from_b1DTD(&p, &size, mhl_check, s3d_enabled, audio_support);
    edid_get_timing_code_from_EstablishTiming(&p, &size, mhl_check);
    edid_get_timing_code_from_StandardTiming(&p, &size, mhl_check);

    if (size > 0) {
        buf[size-1] = '\n';
        buf[size] = '\0';
    }

    if (/*(!has_image_format) ||*/ (size == 0) || (hdmi.manual_set && mhl_check)) {
        if (0 == hdmi.mode) {
            size = snprintf(buf, PAGE_SIZE, "%d\n",hdmi.code+100);
        } else {
            size = snprintf(buf, PAGE_SIZE, "%d\n",hdmi.code);
        }
    }

    logi("edid: %s",buf);

    OUT_FUNCTION;
    return size;
}

/******************************************************************************
* Function:       hdmi_control_edid_show
* Description:    read func of sysfs--edid, write video timing codes to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with video timing codes
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_edid_show(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    if (MHL_HPD & g_PlumTxConfig.mhlHpdRSENflags) {
        return hdmi_get_timing_list(buf, true);
    } else {
        logw("Not connection with monitor, can't show edid\n");
        return -1;
    }
}

/******************************************************************************
* Function:       hdmi_control_edid_show_all
* Description:    read func of sysfs--edid, write all video timing codes to buf
* Data Accessed:
* Data Updated:
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with video timing codes
* Return:         writed size
* Others:
*******************************************************************************/
static ssize_t hdmi_control_edid_show_all(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    if (MHL_HPD & g_PlumTxConfig.mhlHpdRSENflags) {
        return hdmi_get_timing_list(buf, false);
    } else {
        logw("Not connection with monitor, can't show alledid\n");
        return -1;
    }
}

/******************************************************************************
* Function:       hdmi_control_edidbin_show
* Description:    get edid data
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with video timing codes
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_edidbin_show(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    memcpy(buf, edid, sizeof(edid));

    return sizeof(edid);
}

#if ENABLE_REG_DUMP
/******************************************************************************
* Function:       hdmi_control_regbin_show
* Description:    get register data of MHL
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: register data
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_regbin_show(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "regbin isn't implemented, pls use reg file\n");
}

/******************************************************************************
* Function:       hdmi_control_regbin_store
* Description:    config mhl register
* Input:          dev: device, attr: device attribute descriptor.
* Output:
* Return:         reg value
*******************************************************************************/
static ssize_t hdmi_control_regbin_store(struct device *dev,
                                      struct device_attribute *attr, const char *buf, size_t size)
{
	int mode 		= 0; // 0: read, 1: write
	int reg_offset 	= 0;
	int reg_page 	= 0;
	int reg_value 	= 0;
	char *p 		       = (char *)buf;

	if ((buf[0] == '0') && (buf[1]=='x')) {
		sscanf(buf,"0x%x",&reg_offset);
	} else {
		loge("Input param is error: %s.\n", buf);
		loge("-----------------------------------------------------.\n");
		loge("Input param: reg_offset [-r]/[-w reg_value] [-p page] \n");
		loge("        [-r]: read reg /[-w reg_value]: write reg_value(0xX) to offset     \n");
		loge("        [-p page]: 0:PAGE_0, 1=PAGE_1, 2=PAGE_2  \n");
		loge("                        p: PHY_PAGE, t:TPI_PAGE, c:CBUS_PAGE\n");
		loge("default: read CBUS PAGE  reg_offset value \n");
		return -1;
	}

	while((p = strchr(p,'-')))
	{
		switch(*(++p))
		{
			case 'r':
				mode = 0;
				break;
			case 'w':
				mode = 1;

				if (*(++p) == ' ') {
					if ((*(++p) == '0') && (p[1] == 'x')) {
						sscanf(p,"0x%x",&reg_value);
					} else {
						loge("reg_value must 0xXX\n");
						return -1;
					}
				}

				if(reg_value>0xFF){
					loge("Input param is error: %s.\n", buf);
					loge("reg_value must 0x0~0xFF\n");
					return -1;
				}
				break;
			case 'p':
				if(p[1] == ' ')
					switch(p[2])
					{
						case '0':
							reg_page = 1;/* p0 */
							break;
						case '1':
							reg_page = 2;/* p1 */
							break;
						case '2':
							reg_page = 3;/* p2 */
							break;
						case 'p':
							reg_page =4;/* phy */
							break;
						case 't':
							reg_page = 5;/* tpi */
							break;
						case 'c':
							reg_page = 0;/* CBUS */
							break;
						default:
							reg_page = 0;/* CBUS */
					}
				break;
			default:
				loge("Input param is error: %s.\n", buf);
				loge("-----------------------------------------------------.\n");
				loge("Input param: reg_offset [-r]/[-w reg_value] [-p page] \n");
				loge("        [-r]: read reg /[-w reg_value]: write reg_value(0xX) to offset     \n");
				loge("        [-p page]: 0:PAGE_0, 1=PAGE_1, 2=PAGE_2  \n");
				loge("                        p: PHY_PAGE, t:TPI_PAGE, c:CBUS_PAGE\n");
				loge("default: read CBUS PAGE  reg_offset value \n");
				return -1;
		}
	}

	hw_read_write_reg(mode, reg_page, reg_value, reg_offset);
	return size;
}

#endif

/******************************************************************************
* Function:       hdmi_control_timing_show
* Description:    read func of sysfs--code, write current timing code to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with current timing code
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_timing_show(struct device *dev,
                                        struct device_attribute *attr, char *buf)
{
    int showCode = hdmi.code;
    ssize_t size;

    IN_FUNCTION;
/*
    if (!hdmi.connected) {
        logw("The cable is not connected, can't show timing.\n");
        OUT_FUNCTION;
        return -1;
    }
*/
    if (HDMI_CODE_TYPE_VESA == hdmi.mode) {
        showCode = hdmi.code + HDMI_CODE_VESA_OFFSET;
    }

    size = snprintf(buf, PAGE_SIZE, "%s:%u\n", hdmi.mode ? "CEA" : "VESA", showCode);
    logi("timing is %s \n", buf);

    OUT_FUNCTION;
    return size;
}

/******************************************************************************
* Function:       hdmi_control_defaultcode_show
* Description:    read func of sysfs--code, write current timing code to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with default timing code
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_defaultcode_show(struct device *dev,
                                        struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    return snprintf(buf, PAGE_SIZE, "%u\n", edid_get_default_code());
}

/******************************************************************************
* Function:       hdmi_control_timing_store
* Description:    set timing code to hdmi device
* Input:          buf: string of timing code, size: length of buf
*                 buf with '#': manual set, with '*': auto set
* Output:
* Return:         length of buf
*******************************************************************************/
static ssize_t hdmi_control_timing_store(struct device *dev,
        struct device_attribute *attr,
        const char *buf, size_t size)
{
    unsigned long code = 0;
    int mode           = HDMI_CODE_TYPE_CEA;
    int ret            = 0;
    char *pstrchrIn      = NULL;
    char *pstrchrOut    = NULL;

    IN_FUNCTION;
/*
    if (!hdmi.connected) {
        logw("The cable is not connected, can't set timing.\n");
        OUT_FUNCTION;
        return -1;
    }
*/
    logi("hdmi.mode: %d code: %d hdmi.originalcode %d\n", hdmi.mode, hdmi.code,hdmi.originalcode);
    if ((!*buf)) {
        logw("Input param is error: %s.\n", buf);
        OUT_FUNCTION;
        return -EINVAL;
    }

    /* with '#': 1080P video custum set */
    if(hdmi.auto_set) //controled by driver but not user
    {
        pstrchrOut = strchr(buf, '*');
        if(pstrchrOut) //now Video->UI
        {
            *pstrchrOut        = 0;
            hdmi.custom_set = true;
            hdmi.auto_set = false; //special procedure finish
            code = hdmi.originalcode;
        }
        else
        {
            pstrchrIn = strchr(buf, '#');
            if(pstrchrIn) //now video->Video, diff video
            {
                *pstrchrIn        = 0;
                hdmi.custom_set = true;
                hdmi.auto_set = true; //special procedure start

                ret = strict_strtoul(buf, 0, &code);
                if (ret) {
                    logw("Input param is error: %s. \n", buf);
                    OUT_FUNCTION;
                    return -EINVAL;
                }
            }
            else
            {
                return size; //in special proc , can't set new code
            }
        }
    }
    else
    {
        pstrchrIn = strchr(buf, '#');
        if(pstrchrIn) //now UI->Video
        {
            *pstrchrIn        = 0;
            hdmi.custom_set = true;
            hdmi.auto_set = true; //special procedure start

            hdmi.originalcode = hdmi.code + ((HDMI_CODE_TYPE_VESA == hdmi.mode) ? HDMI_CODE_VESA_OFFSET : 0);
        }

        ret = strict_strtoul(buf, 0, &code);
        if (ret) {
            logw("Input param is error: %s. \n", buf);
            OUT_FUNCTION;
            return -EINVAL;
        }
    }

    if(code > HDMI_CODE_VESA_OFFSET)
    {
        code -= HDMI_CODE_VESA_OFFSET;
        mode = HDMI_CODE_TYPE_VESA;
    }
    else
    {
        mode = HDMI_CODE_TYPE_CEA;
    }

    logi("set timing mode: %d code: %d custom_set %d hdmi.originalcode %d\n", mode, (int)code,hdmi.custom_set,hdmi.originalcode);
    update_set_timing_code((int*)&mode, (int*)&code);

    /* if the current code is same to the set code, so don't process */
    if ((code != hdmi.code) || (mode != hdmi.mode)) {
        ret = set_custom_timing_code((int)code, mode);
        if (ret) {
            logw("set custom timing code fail: %d.\n", ret);
            hdmi.custom_set = false;
            OUT_FUNCTION;
            return ret;
        }
    } else {
        logi("The setting code is same with current code, and do nothing.\n");
    }

    hdmi.custom_set = false;
    OUT_FUNCTION;
    return size;
}

#if USE_HDCP
/******************************************************************************
* Function:       hdmi_control_hdcp_show
* Description:    read func of sysfs--hdcp, write whether hdcp enable to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with whether hdcp enable
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_hdcp_show(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    ssize_t size;

    size = snprintf(buf, PAGE_SIZE, "HDCP: %s\n", HDCP_Switch_On ? "ENABLE" : "DISABLE");
    logi("%s \n", buf);

    return size;
}

/******************************************************************************
* Function:       hdmi_control_hdcp_store
* Description:    enable or disable hdcp auth
* Input:          buf: string of "yY1nN0", size: length of buf
* Output:
* Return:         length of buf
*******************************************************************************/
static ssize_t hdmi_control_hdcp_store(struct device *dev,
                                       struct device_attribute *attr,
                                       const char *buf, size_t size)
{
    bool enable = false;

    if ((!*buf) ||(!strchr("yY1nN0", *buf))) {
        loge("Input param is error(valid: yY1nN0): %s. \n",buf);
        return -EINVAL;
    }

    enable = !!strchr("yY1", *buf++);

    logi("enable = %d\n", enable);
    hw_reconfig_hdcp(enable);

    return size;
}
#endif

#if USE_3D
/******************************************************************************
* Function:       hdmi_control_3d_show
* Description:    read func of sysfs--s3d, write current 3d type to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with current 3d type
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_3d_show(struct device *dev,
                                    struct device_attribute *attr, char *buf)
{
    char * type = "NONE";

    IN_FUNCTION;

    if (!hdmi.connected) {
        logw("The cable is not connected, can't show 3d.\n");
        OUT_FUNCTION;
        return -1;
    }

    switch (hdmi.s3d_type) {
        case HDMI_S3D_FRAME_PACKING: {
            type = "HDMI_S3D_FRAME_PACKING";
            break;
        }
        case HDMI_S3D_FIELD_ALTERNATIVE : {
            type = "HDMI_S3D_FIELD_ALTERNATIVE";
            break;
        }
        case HDMI_S3D_LINE_ALTERNATIVE : {
            type = "HDMI_S3D_LINE_ALTERNATIVE";
            break;
        }
        case HDMI_S3D_SIDE_BY_SIDE_FULL: {
            type = "HDMI_S3D_SIDE_BY_SIDE_FULL";
            break;
        }
        case HDMI_S3D_L_DEPTH : {
            type = "HDMI_S3D_L_DEPTH";
            break;
        }
        case HDMI_S3D_L_DEPTH_GP_GP_DEPTH : {
            type = "HDMI_S3D_L_DEPTH_GP_GP_DEPTH";
            break;
        }
        case HDMI_S3D_SIDE_BY_SIDE_HALF : {
            type = "HDMI_S3D_SIDE_BY_SIDE_HALF";
            break;
        }
        case HDMI_S3D_TOP_TO_BOTTOM: {
            type = "HDMI_S3D_TOP_TO_BOTTOM";
            break;
        }
        default: {
            type = "NONE";
            break;
        }
    }

    OUT_FUNCTION;

    return snprintf(buf, PAGE_SIZE, "3D: %s TYPE: %s\n", hdmi.s3d_enabled ? "ON" : "OFF", type);
}

/******************************************************************************
* Function:       hdmi_control_hdcp_store
* Description:    enable or disable hdcp auth
* Input:          buf: string of "0nN1sS2tT", size: length of buf.
*                 0,n,N: 2d;  1,s,S: sidebyside; 2,t,T: top bottom
* Output:
* Return:         length of buf
*******************************************************************************/
static ssize_t hdmi_control_3d_store(struct device *dev,
                                     struct device_attribute *attr,
                                     const char *buf, size_t size)
{
    bool is_3d = true;

    IN_FUNCTION;

    if (!hdmi.connected) {
        logw("The cable is not connected, can't set 3d.\n");
        OUT_FUNCTION;
        return -1;
    }

    if ((!*buf) || (!strchr("0nN1sS2tT", *buf))) {
        loge("Input param buf is error(valid: 0,n,N, 1,s,S, 2,t,T): %s. \n",buf);
        OUT_FUNCTION;
        return -EINVAL;
    }

    is_3d = !strchr("0nN", *buf++);
    if (*buf && (strcmp(buf, "\n"))) {
        loge("Input param buf is error, last char not is \\n . \n");
        OUT_FUNCTION;
        return -EINVAL;
    }

    if (is_3d) {
        switch (*(buf-1)) {
            case '1':
            case 's':
            case 'S': {
                logd("set s3d mode is SBS.\n");
                hdmi.cfg.s3d_structure = HDMI_S3D_SIDE_BY_SIDE_HALF;
                hdmi.cfg.subsamp_pos = HDMI_S3D_HOR_EL_ER;
                break;
            }
            case '2':
            case 't':
            case 'T': {
                logd("set s3d mode is TTB.\n");
                hdmi.cfg.s3d_structure = HDMI_S3D_TOP_TO_BOTTOM;
                break;
            }
            default: {
                loge("Input param buf is error(valid: 0,n,N, 1,s,S, 2,t,T): %s. \n",buf);
                OUT_FUNCTION;
                return -EINVAL;
            }
        }
    } else {
        logd("set to 2d mode.\n");
        hdmi.cfg.s3d_structure = HDMI_2D;
    }

    hdmi.custom_set = true;
    if ((hdmi.s3d_enabled != is_3d) || (hdmi.s3d_type != hdmi.cfg.s3d_structure)) {
        hdmi.s3d_enabled = is_3d;
        hdmi.s3d_type = hdmi.cfg.s3d_structure;
    }

    OUT_FUNCTION;
    return size;
}
#endif /* USE_3D */

/******************************************************************************
* Function:       hdmi_control_audio_show
* Description:    read func of sysfs--dst, write audio formats to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with audio format
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_audio_show(struct device *dev,
                                       struct device_attribute *attr, char *buf)
{
    int size                 = 0;
    int len                  = 6;
    int i                    = 0;
    int has_audio_format     = 0;
    char* p                  = buf;
    audio_format *aud_format = NULL;

    IN_FUNCTION;

    if (!hdmi.connected) {
        logw("The cable is not connected, can't show audio.\n");
        OUT_FUNCTION;
        return -1;
    }

    if (false == edid_is_valid_edid((u8*)edid)) {
        logw("edid isn't readed, get default type: %d chn_num: %d freq: %d.\n",
                      HDMI_DEFAULT_AUDIO_TYPE,
                      HDMI_DEFAULT_AUDIO_CHANNL_NUM + 1,//return real num of ch, so muse add 1.
                      HDMI_DEFAULT_AUDIO_FREQUENCY);
        p[0] = HDMI_DEFAULT_AUDIO_TYPE;
        p[2] = HDMI_DEFAULT_AUDIO_CHANNL_NUM + 1;
        p[4] = HDMI_DEFAULT_AUDIO_FREQUENCY;
        OUT_FUNCTION;
        return len;
    }

    aud_format = kzalloc(sizeof(audio_format), GFP_KERNEL);
    if (!aud_format) {
        loge("malloc mem fail.\n");
        OUT_FUNCTION;
        return -ENOMEM;
    }

    has_audio_format = edid_get_audio_format(edid, aud_format);
    if (!has_audio_format) {
        logw("there isn't audio format.\n");
    }

    logd("audio format number: %d. \n", aud_format->number);

    for (i = 0 ; i < aud_format->number ; i++) {
        logd( "format: %d, channel number: %d, sampling freq: %d. \n",
              aud_format->fmt[i].format,
              aud_format->fmt[i].num_of_ch,
              aud_format->fmt[i].sampling_freq);

        p[0] = aud_format->fmt[i].format;
        p[2] = aud_format->fmt[i].num_of_ch;
        p[4] = aud_format->fmt[i].sampling_freq;

        size += len;
        p += len;
    }

    kfree(aud_format);

    OUT_FUNCTION;
    return size;
}

/******************************************************************************
* Function:       hdmi_control_hpd_show
* Description:    read func of sysfs--hpd, write hdmi power state to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: hdmi power state
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_hpd_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    char * power = "HDMI_POWER_OFF";

    IN_FUNCTION;

    switch (hdmi.power_state) {
        case HDMI_POWER_OFF: {
            power = "HDMI_POWER_OFF";
            break;
        }
        case HDMI_POWER_MIN: {
            power = "HDMI_POWER_MIN";
            break;
        }
        case HDMI_POWER_FULL : {
            power = "HDMI_POWER_FULL";
            break;
        }
        default: { /* fake branch */
            loge("power state is invalid: %d.\n", hdmi.power_state);
            break;
        }
    }

    OUT_FUNCTION;
    return snprintf(buf, PAGE_SIZE, "%s\n", power);
}

/******************************************************************************
* Function:       hdmi_control_hpd_store
* Description:    Turn on or off EDC1 subsystem
* Input:          buf: string of "yY1nN0", size: length of buf.
* Output:
* Return:         length of buf
*******************************************************************************/
static ssize_t hdmi_control_hpd_store(struct device *dev,
                                      struct device_attribute *attr,
                                      const char *buf, size_t size)
{
    bool enable = false;
    int ret = 0;

    char *pstrchr = NULL;

    IN_FUNCTION;

    if ((!*buf) ||(!strchr("yY1nN0", *buf))) {
        loge("Input param buf is error(valid: yY1nN0): %s. \n", buf);
        OUT_FUNCTION;
        return -EINVAL;
    }

    pstrchr = strchr(buf, '#');
    if (pstrchr) {
        *pstrchr = 0;
    }

    enable = !!strchr("yY1", *buf++);

    if (*buf && (strcmp(buf, "\n"))) {
        loge("Input param buf is error, last char not is \\n. \n");
        OUT_FUNCTION;
        return -EINVAL;
    }

    logi("enable hpd: %d \n", enable);

    ret = enable_hpd(enable);
    if (ret) {
        loge("enable hdp fail.\n");
        OUT_FUNCTION;
        return -1;
    }

    OUT_FUNCTION;
    return size;
}

/******************************************************************************
* Function:       hdmi_control_reset
* Description:    reset hdmi after para change
* Input:
* Output:
* Return:
*******************************************************************************/
static ssize_t hdmi_control_reset(struct device *dev,
                                                       struct device_attribute *attr,
                                                       const char *buf, size_t size)
{
	logd("sysfs(reset) is not used in MHL.\n");
	return 1;
}

/******************************************************************************
* Function:       hdmi_control_conected_show
* Description:    get connected state
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: registers dump
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_connected_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;
    return snprintf(buf, PAGE_SIZE, "%d\n", hdmi.connected ? 1 : 0);
}

/******************************************************************************
* Function:       hdmi_control_conected_store
* Description:    get connected state
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: registers dump
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_connected_store(struct device *dev,
                                                       struct device_attribute *attr,
                                                       const char *buf, size_t size)
{
    int ret   = 0;

    IN_FUNCTION;

    /* for now only set this while on or on HPD */
    if (!mhl_is_connect()) {
        logw("the hdmi state is not active, only set it.\n");
        return 0;
    }
    else {
        ret = hw_reconfig();
        if (ret) {
            loge("reconfig fail: %d\n", ret);
        }
    }

    return size;
}

/******************************************************************************
* Function:       hdmi_control_s3dsupport_show
* Description:    get whether the monitor supports 3d
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: 1 --- support s3d
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_s3dsupport_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    if (!(MHL_HPD & g_PlumTxConfig.mhlHpdRSENflags)) {
        logw("The cable is not connected, can't show s3dsupport.\n");
        OUT_FUNCTION;
        return -1;
    }
    return snprintf(buf, PAGE_SIZE, "%d\n", edid_s3d_supported(edid) ? 1 : 0);
}

/******************************************************************************
* Function:       hdmi_control_audiosupport_show
* Description:    get whether the monitor supports audio
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: 1 --- support audio
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_audiosupport_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    return snprintf(buf, PAGE_SIZE, "%d\n", (int)hdmi.cfg.hdmi_dvi);
}

/******************************************************************************
* Function:       hdmi_control_manualset_show
* Description:    get whether the monitor supports manualset
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: 1 --- support manualset
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_manualset_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    IN_FUNCTION;

    return snprintf(buf, PAGE_SIZE, "%d\n", (int)hdmi.manual_set);
}

/******************************************************************************
* Function:       hdmi_control_manualset_store
* Description:    check whether manual set or not
* Input:          manual set flag.
* Output:
* Return:         
*******************************************************************************/
static ssize_t hdmi_control_manualset_store(struct device *dev,
                                                       struct device_attribute *attr,
                                                       const char *buf, size_t size)
{
    IN_FUNCTION;

    switch(*buf)
    {
        case '1':    hdmi.manual_set = true;break;
        case '0':    hdmi.manual_set = false;break;
        default:    logw("invalid manual set mode %c\n",*buf); break;
    }

    logw("hdmi.manual_set %d\n",hdmi.manual_set);
    OUT_FUNCTION;
    return  size;
}

/******************************************************************************
* Function:       hdmi_control_bufisfree_store
* Description:    check video is free
* Input:          addres.
* Output:
* Return:         1 free, 0 in use, -1 err
*******************************************************************************/
static ssize_t hdmi_control_bufisfree_store(struct device *dev,
                                                       struct device_attribute *attr,
                                                       const char *buf, size_t size)
{
    int addr = *(int*)buf;

    if ((!mhl_is_connect()) || (size != sizeof(int)) || (addr == 0)) {
        return -1;
    }

    return  k3fb_buf_isfree(addr);
}

/******************************************************************************
* Function:       mhl_control_devcapbin_show
* Description:    read device capability of mhl dongle/sink
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: with device capability
* Return:         writed size
*******************************************************************************/
static ssize_t mhl_control_devcapbin_show(struct device *dev,
                                        struct device_attribute *attr, char *buf)
{
    memcpy(buf, g_PlumTxConfig.devCapCache.aucDevCapCache, DEVCAP_SIZE);

    return DEVCAP_SIZE;
}

/******************************************************************************
* Function:       hdmi_control_reg_show
* Description:    read func of sysfs--reg, write registers dump to buf
* Input:          dev: device, attr: device attribute descriptor.
* Output:         buf: registers dump
* Return:         writed size
*******************************************************************************/
static ssize_t hdmi_control_reg_show(struct device *dev,
                                     struct device_attribute *attr, char *buf)
{
    dump_mhl_reg();

    return snprintf(buf, PAGE_SIZE, "reg_dump\n");
}

#define S_SYSFS_W (S_IWUSR|S_IWGRP)
/* sysfs attribute */
static DEVICE_ATTR(edid, S_IRUGO, hdmi_control_edid_show, NULL);
static DEVICE_ATTR(alledid, S_IRUGO, hdmi_control_edid_show_all, NULL);
static DEVICE_ATTR(code, S_IRUGO| S_SYSFS_W, hdmi_control_timing_show, hdmi_control_timing_store);
#if USE_3D
static DEVICE_ATTR(s3d, S_IRUGO | S_SYSFS_W, hdmi_control_3d_show, hdmi_control_3d_store);
#endif
static DEVICE_ATTR(dst, S_IRUGO, hdmi_control_audio_show, NULL);
static DEVICE_ATTR(hpd, S_IRUGO| S_SYSFS_W, hdmi_control_hpd_show, hdmi_control_hpd_store);
#if USE_HDCP
static DEVICE_ATTR(hdcp, S_IRUGO | S_SYSFS_W, hdmi_control_hdcp_show, hdmi_control_hdcp_store);
#endif
static DEVICE_ATTR(reset, S_IRUGO | S_SYSFS_W, NULL, hdmi_control_reset);
static DEVICE_ATTR(connected, S_IRUGO | S_SYSFS_W, hdmi_control_connected_show, hdmi_control_connected_store);
static DEVICE_ATTR(s3dsupport, S_IRUGO, hdmi_control_s3dsupport_show, NULL);
static DEVICE_ATTR(audiosupport, S_IRUGO, hdmi_control_audiosupport_show, NULL);
static DEVICE_ATTR(bufisfree, S_IRUGO | S_SYSFS_W, NULL, hdmi_control_bufisfree_store);
static DEVICE_ATTR(manualset, S_IRUGO | S_SYSFS_W, hdmi_control_manualset_show, hdmi_control_manualset_store);
static DEVICE_ATTR(edidbin, S_IRUGO, hdmi_control_edidbin_show, NULL);
static DEVICE_ATTR(defaultcode, S_IRUGO, hdmi_control_defaultcode_show, NULL);
#if ENABLE_REG_DUMP
static DEVICE_ATTR(regbin, S_IRUGO | S_SYSFS_W, hdmi_control_regbin_show, hdmi_control_regbin_store);
#endif
static DEVICE_ATTR(devcapbin, S_IRUGO, mhl_control_devcapbin_show, NULL);
static DEVICE_ATTR(reg, S_IRUGO, hdmi_control_reg_show, NULL);

/******************************************************************************
* Function:      hdmi_control_create_device_file
* Description:   create sysfs attribute file for device.
* Input:         dev: device attr: device attribute descriptor.
* Output:
* Return:
*******************************************************************************/
static int hdmi_control_create_device_file(struct device *dev,
        const struct device_attribute *attr)
{
    BUG_ON(NULL == dev);

    return sysfs_create_file(&dev->kobj, &attr->attr);
}

/******************************************************************************
* Function:      hdmi_control_remove_device_file
* Description:   remove sysfs attribute file.
* Input:         dev: device  attr: device attribute descriptor
* Output:
* Return:
*******************************************************************************/
static void hdmi_control_remove_device_file(struct device *dev,
        const struct device_attribute *attr)
{
    BUG_ON(NULL == dev);

    sysfs_remove_file(&dev->kobj, &attr->attr);

    return;
}

/******************************************************************************
* Function:       hdmi_control_create_sysfs
* Description:    create files of sysfs
* Input:          platform device
* Output:
* Return:
*******************************************************************************/
static int hdmi_control_create_sysfs(struct platform_device *dev)
{
    BUG_ON(NULL == dev);

    /* register HDMI specific sysfs files */
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_edid)) {
        loge("failed to create sysfs file --edid \n");
	    goto err;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_code)) {
        loge("failed to create sysfs file --timing \n");
	    goto err1;
    }
#if USE_3D
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_s3d)) {
        loge("failed to create sysfs file --s3d \n");
	    goto err2;
    }
#endif
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_dst)) {
        loge("failed to create sysfs file --audio \n");
	    goto err3;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_hpd)) {
        loge("failed to create sysfs file --hpd \n");
	    goto err4;
    }
#if USE_HDCP
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_hdcp)) {
        loge("failed to create sysfs file --hdcp \n");
	    goto err5;
    }
#endif

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_connected)) {
        loge("failed to create connected file --connected \n");
	    goto err6;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_s3dsupport)) {
        loge("failed to create s3dsupport file --s3dsupport \n");
	    goto err7;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_audiosupport)) {
        loge("failed to create audiosupport file --audiosupport \n");
	    goto err8;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_bufisfree)) {
        loge("failed to create videoisfree file --videoisfree \n");
	    goto err9;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_reset)) {
        loge("failed to create reset file --reset \n");
	    goto err10;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_edidbin)) {
        loge("failed to create edidbin file --edidbin \n");
	    goto err11;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_defaultcode)) {
        loge("failed to create defaultcode file --defaultcode \n");
	    goto err12;
    }

#if ENABLE_REG_DUMP
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_regbin)) {
        loge("failed to create regbin file --regbin \n");
	    goto err13;
    }
#endif
    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_devcapbin)) {
        loge("failed to create devcapbin file \n");
	    goto err14;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_alledid)) {
        loge("failed to create alledid file --alledid \n");
	    goto err15;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_reg)) {
        loge("failed to create reg show file --reg \n");
	    goto err16;
    }

    if (hdmi_control_create_device_file(&dev->dev, &dev_attr_manualset)) {
        loge("failed to create manualset file --manualset \n");
	    goto err17;
    }

    return 0;

err17:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_reg);
err16:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_alledid);
err15:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_devcapbin);
err14:
#if ENABLE_REG_DUMP
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_regbin);
err13:
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_defaultcode);
err12:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_edidbin);
err11:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_reset);
err10:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_bufisfree);
err9:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_audiosupport);
err8:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_s3dsupport);
err7:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_connected);
err6:
#if USE_HDCP
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_hdcp);
err5:
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_hpd);
err4:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_dst);
err3:
#if USE_3D
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_s3d);
err2:
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_code);
err1:
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_edid);
err:
    return -1;
}

/******************************************************************************
* Function:       hdmi_control_remove_sysfs
* Description:    remove files of sysfs
* Input:          platform device
* Output:
* Return:
*******************************************************************************/
static void hdmi_control_remove_sysfs(struct platform_device *dev)
{
    BUG_ON(NULL == dev);

    hdmi_control_remove_device_file(&dev->dev, &dev_attr_edid);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_code);
#if USE_3D
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_s3d);
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_dst);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_hpd);
#if USE_HDCP
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_hdcp);
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_connected);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_s3dsupport);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_audiosupport);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_bufisfree);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_reset);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_edidbin);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_defaultcode);
#if ENABLE_REG_DUMP
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_regbin);
#endif
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_devcapbin);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_alledid);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_reg);
    hdmi_control_remove_device_file(&dev->dev, &dev_attr_manualset);
    return;
}

/******************************************************************************
* Function:       hdmi_audio_set_param
* Description:    set audio parameter
* Input:
* Output:
* Return:
*******************************************************************************/
int hdmi_audio_set_param(int sample_freq, int sample_size, bool bsio,
                         int layout, int audiotype)//UT XU
{
    int ret = 0;

    IN_FUNCTION;

    logi("audio param: sample freq: %d, the sample size: %d, bsio: %d, layout: %d, audiotype: %d.\n",
          sample_freq, sample_size, bsio, layout, audiotype);

    /*if hdmi.audiochanged is true, recalculate config*/
    if ((hdmi.audiochanged == false) &&
        (hdmi.sample_freq == sample_freq) &&
        (hdmi.sample_size == sample_size) &&
        (hdmi.bsio == bsio) &&
        (hdmi.layout == layout) &&
        (hdmi.audiotype == audiotype)) {
        logi("same param: not set.\n");
        return 0;
    }

    hdmi.sample_freq = sample_freq;
    hdmi.sample_size =sample_size;
    hdmi.bsio = bsio;
    hdmi.layout = layout;
    hdmi.audiotype = audiotype;
    hdmi.audiochanged = true;

    switch (sample_freq) {
        case 48000:
            hdmi.audio_core_cfg.fs = FS_48000;
            hdmi.audio_core_cfg.if_fs = IF_FS_48000;
            break;
        case 44100:
            hdmi.audio_core_cfg.fs = FS_44100;
            hdmi.audio_core_cfg.if_fs = IF_FS_44100;
            break;
        case 32000:
            hdmi.audio_core_cfg.fs = FS_32000;
            hdmi.audio_core_cfg.if_fs = IF_FS_32000;
            break;
        case 88200:
            hdmi.audio_core_cfg.fs = FS_88200;
            hdmi.audio_core_cfg.if_fs = IF_FS_88200;
            break;
        case 96000:
            hdmi.audio_core_cfg.fs = FS_96000;
            hdmi.audio_core_cfg.if_fs = IF_FS_96000;
            break;
        case 192000:
            hdmi.audio_core_cfg.fs = FS_192000;
            hdmi.audio_core_cfg.if_fs = IF_FS_192000;
            break;
        case 176400:
            hdmi.audio_core_cfg.fs = FS_176400;
            hdmi.audio_core_cfg.if_fs = IF_FS_176400;
            break;
        default:
            logw("sample freq is invalid: %d. \n", sample_freq);
            ret = -EINVAL;
            OUT_FUNCTION;
    		return ret;
        }

    /*config sample size*/
    switch (sample_size) {
        case HDMI_SAMPLE_16BITS:
            hdmi.audio_core_cfg.if_sample_size = IF_16BIT_PER_SAMPLE;
            hdmi.audio_core_cfg.i2schst_max_word_length = I2S_CHST_WORD_MAX_20;
            hdmi.audio_core_cfg.i2schst_word_length = I2S_CHST_WORD_16_BITS;
            hdmi.audio_core_cfg.i2s_in_bit_length = I2S_IN_LENGTH_16;
            hdmi.audio_core_cfg.i2s_justify = HDMI_AUDIO_JUSTIFY_LEFT;
            hdmi.audio_fmt.sample_number = HDMI_ONEWORD_TWO_SAMPLES;
            hdmi.audio_fmt.sample_size = HDMI_SAMPLE_16BITS;
            hdmi.audio_fmt.justify = HDMI_AUDIO_JUSTIFY_LEFT;
            break;
        case HDMI_SAMPLE_20BITS:
            hdmi.audio_core_cfg.if_sample_size = IF_20BIT_PER_SAMPLE;
            hdmi.audio_core_cfg.i2schst_max_word_length = I2S_CHST_WORD_MAX_24;
            hdmi.audio_core_cfg.i2schst_word_length = I2S_CHST_WORD_20_BITS_24MAX;
            hdmi.audio_core_cfg.i2s_in_bit_length = I2S_IN_LENGTH_20;
            hdmi.audio_core_cfg.i2s_justify = HDMI_AUDIO_JUSTIFY_LEFT;
            hdmi.audio_fmt.sample_number = HDMI_ONEWORD_ONE_SAMPLE;
            hdmi.audio_fmt.sample_size = HDMI_SAMPLE_20BITS;
            hdmi.audio_fmt.justify = HDMI_AUDIO_JUSTIFY_LEFT;
            break;
        case HDMI_SAMPLE_24BITS:
            hdmi.audio_core_cfg.if_sample_size = IF_24BIT_PER_SAMPLE;
            hdmi.audio_core_cfg.i2schst_max_word_length = I2S_CHST_WORD_MAX_24;
            hdmi.audio_core_cfg.i2schst_word_length = I2S_CHST_WORD_24_BITS;
            hdmi.audio_core_cfg.i2s_in_bit_length = I2S_IN_LENGTH_24;
            hdmi.audio_core_cfg.i2s_justify = HDMI_AUDIO_JUSTIFY_LEFT;
            hdmi.audio_fmt.sample_number = HDMI_ONEWORD_ONE_SAMPLE;
            hdmi.audio_fmt.sample_size = HDMI_SAMPLE_24BITS;
            hdmi.audio_fmt.justify = HDMI_AUDIO_JUSTIFY_RIGHT;
            break;
        default:
            loge("input param is invalid(valid: 0 - 16bit, 1 - 24bit): %d.\n", sample_size);
            ret = -EINVAL;
            OUT_FUNCTION;
    		return ret;
    }

    hdmi.audio_fmt.left_before = HDMI_SAMPLE_LEFT_FIRST;

    /*set bsio layout and type*/

    switch(layout)
    {
        case LAYOUT_2CH:
                 hdmi.audio_core_cfg.if_channel_number         = 2;
                 hdmi.audio_core_cfg.if_audio_channel_location = HDMI_CEA_CODE_00;
                 break;

        case LAYOUT_5CH:
                 hdmi.audio_core_cfg.if_channel_number         = 5;
                 hdmi.audio_core_cfg.if_audio_channel_location = HDMI_CEA_CODE_0A;
                 break;

        case LAYOUT_6CH:
                 hdmi.audio_core_cfg.if_channel_number         = 6;
                 hdmi.audio_core_cfg.if_audio_channel_location = HDMI_CEA_CODE_0B;
                 break;

        case LAYOUT_8CH:
                 hdmi.audio_core_cfg.if_channel_number         = 8;
                 hdmi.audio_core_cfg.if_audio_channel_location = HDMI_CEA_CODE_1F;
                 break;

        default:
                 loge("input param layout invalid(valid: 0, 1): %d.\n", layout);
                 ret = -EINVAL;
                OUT_FUNCTION;
		   return ret;
    }

    hdmi.audio_core_cfg.bsio = bsio;
    hdmi.audio_core_cfg.layout = layout;
    hdmi.audio_core_cfg.audiotype = audiotype;

    OUT_FUNCTION;
    return ret;
}

/******************************************************************************
* Function:       k3_hdmi_audio_set_power
* Description:    turn on/off audio power
* Input:          true for turn on, false for other
* Output:
* Return:
*******************************************************************************/
int k3_hdmi_audio_set_power(bool audio_on)
{
    int ret = 0;

    IN_FUNCTION;

    if (audio_on == true) {
        if (!mhl_is_connect()) {
            loge("the hdmi state is not active, can't set it.\n");
            OUT_FUNCTION;
            return -1;
        }

        if (hdmi.audiochanged == false) {
            loge("the hdmi audiochanged is false, can't set it.\n");
            OUT_FUNCTION;
            return -1;
        }

        /* config n and cts by pixel_clock and fs */
        ret = hw_configure_acr(hdmi.timings->pixel_clock, hdmi.audio_core_cfg.fs);
        if (ret) {
            loge("configure hardware acr fail, %d. \n", ret);
            ret = -EINVAL;
        }

        /* set audio config to hdmi device */
        hw_configure_audio(&hdmi.audio_core_cfg);
        hdmi.audiochanged = false;
    }

    OUT_FUNCTION;
    return ret;
}

/******************************************************************************
* Function:       k3_hdmi_audio_set_param
* Description:    set audio parameter
* Input:
* Output:
* Return:
*******************************************************************************/
int k3_hdmi_audio_set_param(int sample_freq, int sample_size, bool bsio,
                            int layout, int audiotype)
{
    int ret = 0;

    IN_FUNCTION;

    mutex_lock(&hdmi.lock_aux);
    ret = hdmi_audio_set_param(sample_freq, sample_size, bsio, layout, audiotype);
    mutex_unlock(&hdmi.lock_aux);

    OUT_FUNCTION;
    return ret;
}

EXPORT_SYMBOL(k3_hdmi_audio_set_power);
EXPORT_SYMBOL(k3_hdmi_audio_set_param);

/******************************************************************************
* Function:       hdmi_get_vsync_bycode
* Description:    get vsync pol by
* Input:          true - eanble
* Output:
* Return:
*******************************************************************************/
int hdmi_get_vsync_bycode(int code)
{
    int index = INVALID_VALUE;
    int mode  = HDMI_CODE_TYPE_CEA;

    if (code >= HDMI_CODE_VESA_OFFSET) {
        mode = HDMI_CODE_TYPE_VESA;
        code -= HDMI_CODE_VESA_OFFSET;
    }

    if (edid_is_valid_code(mode, code)) {
        index = edid_get_timings_index(mode, code);
        if (INVALID_VALUE != index) {
            return edid_get_hvpol_byindex(index)->vsync_pol == 1 ? 0 : 1;
        }
    }

    return 0;
}

/******************************************************************************
* Function:       hdmi_get_hsync_bycode
* Description:    get Hsync pol by code
* Input:          true - eanble
* Output:
* Return:
*******************************************************************************/
int hdmi_get_hsync_bycode(int code)
{
    int index = INVALID_VALUE;
    int mode  = HDMI_CODE_TYPE_CEA;

    if (code >= HDMI_CODE_VESA_OFFSET) {
        mode = HDMI_CODE_TYPE_VESA;
        code -= HDMI_CODE_VESA_OFFSET;
    }

    if (edid_is_valid_code(mode, code)) {
        index = edid_get_timings_index(mode, code);
        if (INVALID_VALUE != index) {
            return edid_get_hvpol_byindex(index)->hsync_pol == 1 ? 0 : 1;
        }
    }

    return 0;
}

EXPORT_SYMBOL(hdmi_get_vsync_bycode);
EXPORT_SYMBOL(hdmi_get_hsync_bycode);

void mhl_timeout_timer(unsigned long value)
{
    int ret = 0;

    if(hdmi.connected)
    {
        ret = hisi_mutex_mng_notify_alive(MUTEX_SERVICE_HDMI_ID);
        if(ret)
        {
            loge("hdmi notify mutex center alive fail %d!\n", ret);
        }

        logd("hdmi notify mutex center alive success!\n");
        mod_timer(&hdmi_timer, jiffies + 1 * HZ);
    }
    else
    {
        loge("hdmi timer on but disconnect!\n");
        del_timer(&hdmi_timer);
    }
}
/******************************************************************************
* Function:       hdmi_regist_fb
* Description:    regist hdmi device to fb driver, fb will transmit image out
                  to hdmi device
* Input:          platform device
* Output:
* Return:
*******************************************************************************/
static int hdmi_regist_fb(struct platform_device *pdev)
{
    int index = 0;
    struct k3_panel_info *pinfo = NULL;
    hdmi_video_timings *ptimings = NULL;

    BUG_ON(NULL == pdev);

    IN_FUNCTION;

    //set the fb1's timing to 720p default
	index    = edid_get_timings_index(HDMI_DEFAULT_TIMING_MODE, edid_get_default_code());
	ptimings = edid_get_timings_byindex(index);

    pinfo                    = hdmi_panel_data.panel_info;
    pinfo->xres              = ptimings->x_res;
    pinfo->yres              = ptimings->y_res;
    pinfo->type              = PANEL_HDMI;
    pinfo->orientation       = LCD_LANDSCAPE;
    pinfo->bpp               = EDC_OUT_RGB_888;
    pinfo->s3d_frm           = EDC_FRM_FMT_2D;
    pinfo->bgr_fmt           = EDC_RGB;
    pinfo->clk_rate          = ptimings->pixel_clock * 1000;
    pinfo->ldi.h_back_porch  = ptimings->hbp;
    pinfo->ldi.h_front_porch = ptimings->hfp;
    pinfo->ldi.h_pulse_width = ptimings->hsw;
    pinfo->ldi.v_back_porch  = ptimings->vbp;
    pinfo->ldi.v_front_porch = ptimings->vfp;
    pinfo->ldi.v_pulse_width = ptimings->vsw;
    pinfo->ldi.hsync_plr     = hdmi_get_hsync_bycode(edid_get_default_code());
    pinfo->ldi.vsync_plr     = hdmi_get_vsync_bycode(edid_get_default_code());
    pinfo->ldi.pixelclk_plr  = 1;
    pinfo->ldi.data_en_plr   = 0;
    pinfo->ldi.disp_mode     = LDI_DISP_MODE_NOT_3D_FBF;

    /* alloc panel device data */
    if (platform_device_add_data(pdev, &hdmi_panel_data, sizeof(struct k3_fb_panel_data))) {
        loge("k3fb, platform_device_add_data failed!\n");

        OUT_FUNCTION;
        return -ENOMEM;
    }

    if (NULL == k3_fb_add_device(pdev)) {
        loge("k3_fb_add_device error....\n");

        OUT_FUNCTION;
        return -ENOMEM;
    }

    OUT_FUNCTION;
    return 0;
}

/******************************************************************************
* Function:      mhl_rcp_register_input_dev
* Description:   MHL RCP register input to report Key code
* Input:         none
* Output:
* Return:
*******************************************************************************/
int mhl_rcp_register_input_dev(void)
{
    int i = 0;
    int ret = 0;

    /* register mhl rcp input device */
    hdmi.rcp_dev = input_allocate_device();
    if (!hdmi.rcp_dev)
    {
	    loge("mhl input_allocate_device error\n");
	    return  -1;
    }

    hdmi.rcp_dev->name = "mhl_rcp_dev";
    hdmi.rcp_dev->id.bustype = BUS_I2C;
    hdmi.rcp_dev->keycode = rcpKeyCode;
    hdmi.rcp_dev->keycodesize = sizeof(rcpKeyCode[0]);
    hdmi.rcp_dev->keycodemax = ARRAY_SIZE(rcpKeyCode);

    __set_bit(EV_KEY, hdmi.rcp_dev->evbit);
    __clear_bit(EV_REP, hdmi.rcp_dev->evbit);

    for (i = 0; i < ARRAY_SIZE(rcpKeyCode); i++)
    {
        input_set_capability( hdmi.rcp_dev, EV_KEY, rcpKeyCode[i]);
    }

    __clear_bit(KEY_RESERVED, hdmi.rcp_dev->keybit);

    ret = input_register_device(hdmi.rcp_dev);
    if(ret)
    {
	   loge("register input device failed: %d\n", ret);
	   input_free_device(hdmi.rcp_dev);
    }

    return ret;
}

int mhl_rcp_unregister_input_dev(void)
{
    if (hdmi.rcp_dev) {
        //input_unregister_device(hdmi.rcp_dev);
        input_free_device(hdmi.rcp_dev);
    }

    return 0;
}
/******************************************************************************
* Function:      mhl_interrupt_handler
* Description:   MHL interrupt handler.
* Input:         int irq: interrupt number, void *arg: not used
* Output:
* Return:        IRQ_HANDLED
*******************************************************************************/
static irqreturn_t mhl_interrupt_handler(int irq, void *arg)
{
    disable_irq_nosync(irq);
    schedule_work(hdmi.work);
    return IRQ_HANDLED;
}

/******************************************************************************
* Function:      mhl_work_queue
* Description:   MHL work queue for handling interrupt
* Input:         struct work_struct *work
* Output:
* Return:        IRQ_HANDLED
*******************************************************************************/
static void mhl_work_queue(struct work_struct *work)
{
    wake_lock(&hdmi.wake_lock);
    enable_irq(hw_res.irq);
    SiiDeviceIsr();
    wake_unlock(&hdmi.wake_lock);
}

/******************************************************************************
* Function:      mhl_remove
* Description:   resources recycle when mhl driver removed
* Input:         platform device
* Output:
* Return:        int, 0 for success, others for fail
*******************************************************************************/
int mhl_remove(struct platform_device* dev)
{
    int ret = 0;

    IN_FUNCTION;

    ret = enable_hpd(false);
    if (ret) {
        loge("disable hpd fail: %d.\n", ret);
    }

    if(hdmi.work) {
        ret = cancel_work_sync(hdmi.work);
        if (ret) {
            loge("cancel hdmi work fail: %d.\n", ret);
        }

        kfree(hdmi.work);
    }

    hw_free_resources();

    hdmi_control_remove_sysfs(dev);

    switch_dev_unregister(&hdmi.hpd_switch);

    memset(&hdmi, 0, sizeof(hdmi_device));

    OUT_FUNCTION;
    return ret;
}

/******************************************************************************
* Function:      mhl_probe
* Description:   probe function of mhl driver
* Input:         platform device
* Output:
* Return:        int, 0 for success, others for fail
*******************************************************************************/
int mhl_probe(struct platform_device *pdev) //UT YANG
{
    int ret = 0;

    IN_FUNCTION;

    /* Initialize global variable */
    memset(&hdmi, 0, sizeof(hdmi));
    hdmi_init_partial_data();

    hdmi.pdev = pdev;

    mutex_init(&hdmi.lock);
    mutex_init(&hdmi.lock_aux);
    wake_lock_init(&hdmi.wake_lock, WAKE_LOCK_SUSPEND, "mhl wake lock");
    wake_lock_init(&hdmi.usb_otg_lock, WAKE_LOCK_SUSPEND, "mhl's rgnd wake lock");

    ret = hdmi_control_create_sysfs(pdev);
    if (ret) {
        loge("create sysfs error %d\n", ret);
        goto err0;
    }

    /* get device resources */
    ret= hw_get_resources(pdev);
    if (ret) {
        loge("get mhl resources error %d\n", ret);
        goto err;
    }

    /* register hdmi switch*/
    hdmi.hpd_switch.name = "hdmi";
    ret = switch_dev_register(&hdmi.hpd_switch);
    if (ret) {
        loge("switch_dev_register error %d\n", ret);
        goto err;
    }


    hdmi.work = kzalloc(sizeof(struct work_struct), GFP_ATOMIC);
    if (!hdmi.work) {
        ret = -ENOMEM;
        goto err;
    }
    INIT_WORK(hdmi.work, mhl_work_queue);

    /* regist mhl to fb driver */
    ret = hdmi_regist_fb(pdev);
    if (ret) {
        loge("regist fb device error %d\n", ret);
        goto err;
    }

    ret = enable_hpd(true);
    if (ret) {
        loge("enable hpd fail: %d.\n", ret);
        goto err;
    }

    hdmi_timer.expires = jiffies + 1 * HZ;
    hdmi_timer.function = mhl_timeout_timer;
    init_timer(&hdmi_timer);

    OUT_FUNCTION;
    return ret;

err0:
    memset(&hdmi, 0, sizeof(hdmi_device));
    OUT_FUNCTION;
    return ret;
err:
    mhl_remove(pdev);

    OUT_FUNCTION;
    return ret;
}

/******************************************************************************
* Function:      mhl_suspend
* Description:   mhl device suspend when product suspend
* Input:         platform device and power manager state
* Output:
* Return:        int
*******************************************************************************/
int mhl_suspend(struct platform_device *dev, pm_message_t state)
{
    int ret = 0;

    IN_FUNCTION;

    /* In Balong platorm, it should power off when the system suspends */

    hdmi.last_hpd_enabled = hdmi.hpd_enabled;

    ret = enable_hpd(false);
    if (ret) {
        loge("disable hpd fail: %d.\n", ret);
    }

    del_timer(&hdmi_timer);
    OUT_FUNCTION;
    return ret;
}

/******************************************************************************
* Function:      mhl_resume
* Description:   mhl device resume when product resume
* Input:         platform device
* Output:        na
* Return:        int
*******************************************************************************/
int mhl_resume(struct platform_device *dev)
{
    int ret = 0;

    IN_FUNCTION;

    /* In Balong platorm, it should power on when the system resumes */

    if (!hdmi.hpd_enabled) {
        ret = enable_hpd(hdmi.last_hpd_enabled);
        if (ret) {
            loge("enable hpd fail: %d.\n", ret);
        }
    }

    OUT_FUNCTION;
    return ret;
}

static struct platform_driver this_driver = {
    .probe   = mhl_probe,
    .remove  = mhl_remove,
    .suspend = mhl_suspend,
    .resume  = mhl_resume,
    .driver  = {
        .name = MHL_DEVICE_NAME,
    }
};

/******************************************************************************
* Function:      mhl_init
* Description:   driver init function, register platform driver
* Input:         void
* Output:
* Return:        int, 0 for success, others for fail
*******************************************************************************/
static int __init mhl_init(void)
{
    int ret = 0;

    ret = platform_driver_register(&this_driver);
    if (ret) {
        loge("failed to init mhl driver\n");
    }

    return ret;
}

/******************************************************************************
* Function:      mhl_exit
* Description:   driver exit func, unregister platform driver
* Input:         void
* Output:
* Return:        void
*******************************************************************************/
static void __exit mhl_exit(void)
{
    platform_driver_unregister(&this_driver);
    return;
}

late_initcall(mhl_init);
module_exit(mhl_exit);

#ifdef CONFIG_DEBUG_FS
int g_mhl_debugfs_flag = 0;
#define MHL_DEBUGFS_FILE_NAME   "mit1_mhl"

void logd (const char* fmt, ...)
{
    va_list args;

    if ((g_mhl_debugfs_flag & 0x01) == MHL_DEBUGFS_FLAG_OPEN_DEBUG) {
    	va_start(args, fmt);
    	vprintk(fmt, args);
    	va_end(args);
	}
}

void SII_DBG_PRINT (const char* fmt, ...)
{
    va_list args;

    if ((g_mhl_debugfs_flag & 0x01) == MHL_DEBUGFS_FLAG_OPEN_DEBUG) {
    	va_start(args, fmt);
    	vprintk(fmt, args);
    	va_end(args);
	}
}

static int __init mhl_debugfs_init(void)
{
    debugfs_create_u32(MHL_DEBUGFS_FILE_NAME, 0664, NULL,  &g_mhl_debugfs_flag);
    return 0;
}

late_initcall(mhl_debugfs_init);
#endif /* CONFIG_DEBUG_FS */


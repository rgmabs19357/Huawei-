/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_mhl_hw.c
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/

#include <linux/kernel.h>
#include <linux/clk.h>
#include <linux/mux.h>
#include <linux/regulator/consumer.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/mhl/mhl.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

#include "k3_fb.h"
#include "si_reg_access.h"
#include "si_drv_mhl_tx.h"
#include "si_mhl_hw.h"
#include "si_mhl_main.h"
#include "si_mhl_tx.h"

extern uint8_t edid[HDMI_EDID_MAX_LENGTH];
extern mhlTx_config_t g_PlumTxConfig;

extern hdmi_device hdmi;
extern u32 k3fd_reg_base_edc1;

hdmi_hw_res hw_res = {0};

extern bool HDCP_Switch_On;
extern bool HDCP_Started;
extern bool HDCP_AksvValid;
#if USE_HDCP
extern void SiiHDCP_CheckStatus (void);
extern void SiiDrvHDCP_Off(void);
#endif

static void config_phy_tmds(deep_color *vsdb_format);
static void disable_clk(u32 clks);
static void enable_clk(u32 clks);
#if USE_3D
static int get_s3d_timings_index(void);
#endif

static int hw_configure_lrfr(void);
static void hw_core_audio_infoframe_avi(hdmi_core_infoframe_avi info_avi);
//static void hw_core_av_packet_config(hdmi_core_packet_enable_repeat r_p);
static void hw_core_init(hdmi_core_video_config *v_cfg,
                           hw_audio_configure *audio_cfg,
                           hdmi_core_infoframe_avi *avi,
                           hdmi_core_packet_enable_repeat *r_p);
static void hw_core_video_config(hdmi_core_video_config *cfg);
static void update_cfg(hdmi_config *cfg, hdmi_video_timings *timings);
static void update_cfg_pol(hdmi_config *cfg, int index);
static int hw_get_aspect_ratio(u16 video_format);

#ifdef CONFIG_MACH_HI6620SFT
extern int mhl_phy_write_reg(u8 reg, u8 val);
extern int mhl_phy_read_reg(u8 reg);
#endif

#define DDR_VALID_FREQ_BUF_MAX_LEN      (128)
#define DDR_VALID_FREQ_PATH "/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_ddrfrequencies"
static unsigned long getDdrMaxFreq(void)
{
    char buf[DDR_VALID_FREQ_BUF_MAX_LEN] = {0};
    int size = 0;
    unsigned long ddr_max_freq = MHL_DDR_MIN_FREQ_800M;
    int ret = 0;
    unsigned long fs = 0;
    int ddrValidFreqFd;

    fs = get_fs();
    set_fs(KERNEL_DS);

    ddrValidFreqFd = sys_open(DDR_VALID_FREQ_PATH, O_RDONLY, 0);

    if (ddrValidFreqFd < 0)
    {
        loge("'%s' open fail", DDR_VALID_FREQ_PATH);
    }
    else
    {
        size = sys_read(ddrValidFreqFd, buf, sizeof(buf)-1);
        if (size <= 0)
        {
            loge("file empty '%s'", DDR_VALID_FREQ_PATH);
        }
        else
        {
            while (size > 1 && ((buf[size-1] > '9') || (buf[size-1] < '0')))
            {
                --size;
            }
            buf[size]='\0';
            while (size > 1 && ((buf[size-1] <= '9') && (buf[size-1] >= '0')))
            {
                --size;
            }
            ret  = strict_strtoul((buf+size), 0, &ddr_max_freq);
            if(ret < 0)
            {
                loge("Input param is error: %s. size %d ret %d\n", buf+size, size, ret);
            }
        }

        sys_close(ddrValidFreqFd);
    }

    set_fs(fs);
     
    return ddr_max_freq;
}

/******************************************************************************
* Function:       get_timings_index
* Description:    get index of video timing from timing code
* Input:
* Output:
* Return:         timing index
*******************************************************************************/
int get_timings_index(void)
{
    int index = edid_get_timings_index(hdmi.mode, hdmi.code);

    if (INVALID_VALUE == index) {
        logw("the time index is invalid, mode: %d, code: %d.\n", hdmi.mode, hdmi.code);
        hdmi.mode = HDMI_DEFAULT_TIMING_MODE;
        hdmi.code = edid_get_default_code();
        index = edid_get_timings_index(hdmi.mode, hdmi.code);
    }

    return index;
}

/******************************************************************************
* Function:       mhl_is_connect
* Description:    whether mhl is connected
* Input:
* Output:
* Return:
*******************************************************************************/
bool mhl_is_connect(void)  //UT YANG
{
    u32 hpd_state = 0;

    if (hdmi.state != HDMI_DISPLAY_ACTIVE) {
        logw("hdmi state is not active.\n");
        return false;
    }

    hpd_state = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_CBUS_CONN_STATUS_ADDR);

    return (hpd_state & BIT2)? true: false;
}  

/******************************************************************************
* Function:       hw_enable_irqs
* Description:    enable or disable irq
* Input:          true to enable irq, false to disable irq
* Output:
* Return:
*******************************************************************************/
void hw_enable_irqs(bool enable)
{
    static bool irq_isdisabled = false;

    logd("irq_isdisabled:%d, enable:%d. \n", irq_isdisabled, enable);

    if((!enable) && (!irq_isdisabled)) {
        logd("disable irq.\n");
        disable_irq(hw_res.irq);
        irq_isdisabled = true;
    }
    
    if((enable) && (irq_isdisabled)) {
        logd("enable irq.\n");
        enable_irq(hw_res.irq);
        irq_isdisabled = false;
    }

    return;
}

/******************************************************************************
* Function:       hw_set_phy_low_power
* Description:    set mhl phy to low power
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_set_phy_low_power(void)
{
    /* set PHY: DM_TX_CTRL[5] = 0, disable TMDS output */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, 0x00);

    /* set PHY: DM_TX_CTRL[4] = 0, power down */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT4, 0x00);

    msleep(1);
    return;
}

/******************************************************************************
* Function:       hw_set_phy_full_power
* Description:    set mhl phy to full power
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_set_phy_full_power(void)
{
    /* set PHY: DM_TX_CTRL[4] = 1, power normal */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT4, BIT4);

    /* Don't enable TMDS output, wait after reading EDID and
       sending AVI infoframe in hw_enable() */

    msleep(5);
    return;
}

/******************************************************************************
* Function:       hw_phy_power_off
* Description:    turn off hdmi phy
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_phy_power_off(void)
{
    /* set PHY: DM_TX_CTRL[5] = 0, disable TMDS output */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, 0x00);

    /* set PHY: DM_TX_CTRL[4] = 0, power down */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT4, 0x00);

    return;
}

/******************************************************************************
* Function:       hw_core_power_on
* Description:    turn on mhl device
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_core_power_on(void) //UT YANG
{
    /*
    if (regulator_enable(hw_res.edc_vcc) != 0) {
        loge("failed to enable edc1-vcc regulator.\n");
    }
    */
    if (edc_mtcos_enable(1) != 0) {
        loge("failed to enable edc1-vcc regulator.\n");
    }
    
    DISABLE_ISO_EDC1_PW;
    msleep(1);
    DISABLE_RST_EDC1_PW;  
    DISABLE_RST_MHL_PHY_PW;
    ENABLE_CLK_EDC1_PW;
    
    DISABLE_RST_EDC1_REST;
    DISABLE_RST_MHL_CORE;   
    
    /* It must enable these clocks before accessing MHL registers. 
     * Other clocks are enabled when the MHL cable is connected. */
    enable_clk(HDMI_CLK_EDC1_APB | HDMI_CLK_HDMI_APB);
    
    msleep(1);    
    hdmi.state       = HDMI_DISPLAY_ACTIVE;
    hdmi.power_state = HDMI_POWER_MIN;
    
    return;
}

/******************************************************************************
* Function:       hw_core_power_off
* Description:    turn off hdmi device
* Input:
* Output:
* Return:
*******************************************************************************/
void  hw_core_power_off(void)  //UT YANG
{
    RST_MHL_CORE;
    RST_EDC1_REST;
    
    DISABLE_CLK_EDC1_PW;
    ENABLE_ISO_EDC1_PW;
    RST_MHL_PHY_PW;
    RST_EDC1_PW;
    
    /*disable edc1 regulator*/
    //regulator_disable(hw_res.edc_vcc);
    edc_mtcos_disable(1);
}

/******************************************************************************
* Function:       hw_set_core_low_power
* Description:    set EDC1/MHL Controller to low power state
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_set_core_low_power(void)
{
    return;
}

/******************************************************************************
* Function:       hw_set_core_full_power
* Description:    set EDC1/MHL Controller to full power state
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_set_core_full_power(void) //UT YANG
{
    return;
}

/******************************************************************************
* Function:       hdmi_pw_power_on_min
* Description:    turn on hdmi device to min
* Input:
* Output:
* Return:
*******************************************************************************/
void hdmi_pw_power_on_min(void)
{
    if (hdmi.power_state != HDMI_POWER_FULL) {
        logw("Current power state(%d) is not FULL(2) and can't set it to MIN.\n", 
              hdmi.power_state);
        return;
    }
    
    logd("hdmi power state: FULL-->MIN\n");
    
    if (hdmi.has_request_ddr) {
        hdmi.has_request_ddr = false;
        pm_qos_remove_request(&hdmi.ddr_qos_request);
    }

    pm_qos_remove_request(&hdmi.cpu_qos_request);

#ifdef CONFIG_MACH_HI6620OEM
    hw_set_phy_low_power();
#endif

    hdmi_init_partial_data();
    hdmi.power_state = HDMI_POWER_MIN;
    
    return;
}

/******************************************************************************
* Function:       hdmi_pw_power_on_full
* Description:    turn on hdmi device to full state
* Input:
* Output:
* Return:
*******************************************************************************/
void hdmi_pw_power_on_full(void)
{    
    if (hdmi.power_state != HDMI_POWER_MIN) {
        logw("Current power state(%d) is not MIN(1) and can't set it to FULL.\n", 
              hdmi.power_state);
        return;
    }
    
    logd("hdmi power state: MIN-->FULL\n");
    
#ifdef CONFIG_MACH_HI6620OEM
    hw_set_phy_full_power();
#endif

    /* MHL is connected, and set DDR freq*/
    pm_qos_add_request(&hdmi.ddr_qos_request, PM_QOS_DDR_PROFILE_BLOCK, getDdrMaxFreq());
    hdmi.has_request_ddr = true;

    pm_qos_add_request(&hdmi.cpu_qos_request, PM_QOS_CPU_INT_LATENCY, 0);

    hdmi.power_state = HDMI_POWER_FULL;

    return;
}

/******************************************************************************
* Function:       hdmi_pw_power_off
* Description:    turn off hdmi device, and notify to user space
* Input:
* Output:
* Return:
*******************************************************************************/
void hdmi_pw_power_off(void)
{
    int ret = 0;

    switch (hdmi.power_state) {
        case HDMI_POWER_MIN:
            logd("hdmi power state: MIN-->OFF\n");
            break;
        case HDMI_POWER_FULL:    
            logd("hdmi power state: FULL-->OFF\n");
            
            if (hdmi.has_request_ddr) {
                hdmi.has_request_ddr = false;
                pm_qos_remove_request(&hdmi.ddr_qos_request);
            }
            
            pm_qos_remove_request(&hdmi.cpu_qos_request);
            
#ifdef CONFIG_MACH_HI6620OEM
            hw_phy_power_off();
#endif            
            break;
        case HDMI_POWER_OFF:
            logw("hdmi power state: OFF-->OFF, don't set it.\n");
            return;
    }    
    
    disable_clk(HDMI_CLK_EDC1_APB | HDMI_CLK_HDMI_APB);

#if USE_HDCP
    SiiDrvHDCP_Off();
#endif

    hw_enable_irqs(false);    

    hw_core_power_off();
    
    ret = hdmi_control_notify_hpd_status(false);
    if (ret) {
        logw("notify hpd status fail: %d.\n", ret);
    }
    
    /* Clear data */
    hdmi_init_partial_data();
    memset(edid, 0, sizeof(edid));
    SiiMhlTxResetStates();
    
    hdmi.state = HDMI_DISPLAY_DISABLED;
    hdmi.power_state = HDMI_POWER_OFF;
    
    return;
}

/******************************************************************************
* Function:       enable_clk
* Description:    enable some clocks
* Input:          clock index
* Output:
* Return:
*******************************************************************************/
static void enable_clk(u32 clks)
{
    int ret = 0;
    
    logd("enable clk: 0x%x. Clock definition: \n", clks);
    logd("HDMI_APB:0x1, EDC1_APB:0x2, EDC1_PIXEL:0x4, EDC1_CORE:0x8, EDC1_AXI:0x10\n");

    if (clks & HDMI_CLK_EDC1_APB) {
        ret = clk_enable(hw_res.clk_pclk_edc1);
        if(ret){
            loge("enable edc1 APB clock error %d\n",ret);
        }
    }

    if (clks & HDMI_CLK_HDMI_APB) {
        ret = clk_enable(hw_res.clk_pclk_hdmi);
        if (ret){
            loge("enable hdmi APB clock error %d\n",ret);
        }
    }
    
    if (clks & HDMI_CLK_EDC1_PIXEL) {
        ret = clk_enable(hw_res.clk_edc1_pixel);
        if (ret){
            loge("enable edc1 pixel clock error %d\n", ret);
        }
    }
    
    if (clks & HDMI_CLK_EDC1_CORE) {
        ret = clk_enable(hw_res.clk_edc1_core);
        if (ret){
            loge("enable edc1 core clock error %d\n", ret);
        }
    }
    
    if (clks & HDMI_CLK_EDC1_AXI) {
        ret = clk_enable(hw_res.clk_edc1_axi);
        if (ret){
            loge("enable edc1 axi bus clock error %d\n", ret);
        }
    }
    return;
}

/******************************************************************************
* Function:       disable_clk
* Description:    disable some clocks
* Input:          clock index
* Output:
* Return:
*******************************************************************************/
static void disable_clk(u32 clks)
{
    logd("enable clk: 0x%x. Clock definition: \n", clks);
    logd("HDMI_APB:0x1, EDC1_APB:0x2, EDC1_PIXEL:0x4, EDC1_CORE:0x8, EDC1_AXI:0x10\n");

    if (clks & HDMI_CLK_EDC1_APB) {
        clk_disable(hw_res.clk_pclk_edc1);
    }

    if (clks & HDMI_CLK_HDMI_APB) {
        clk_disable(hw_res.clk_pclk_hdmi);
    }
    
    if (clks & HDMI_CLK_EDC1_PIXEL) {
        clk_disable(hw_res.clk_edc1_pixel);
    }
    
    if (clks & HDMI_CLK_EDC1_CORE) {
        clk_disable(hw_res.clk_edc1_pixel);
    }
    
    if (clks & HDMI_CLK_EDC1_AXI) {
        clk_disable(hw_res.clk_edc1_pixel);
    }
    
    return;
}

/***********************************************************************************
* Function:       hw_core_blank_video
* Description:    set vide blank
* Input:          bool blank : true:need blank, false: need not blank
* Output:         NA
* Return:         NA
***********************************************************************************/
void hw_core_blank_video(bool blank)
{
    if (blank) {
        /* set 0x72:0D[2] = 1(blank) */
        SiiDrvModifyIndexedRegister(INDEXED_PAGE_0, P0_DCTL_ADDR, BIT2, BIT2);
    }
    else {
        /*set 0x72:0D[2] = 0 (unblank) */
        SiiDrvModifyIndexedRegister(INDEXED_PAGE_0, P0_DCTL_ADDR, BIT2, 0x00);
    }

    return;
}

/******************************************************************************
* Function:       hw_core_init
* Description:    init default parameter
* Input:
* Output:         video and audio configure, avi, packet repeat
* Return:
*******************************************************************************/
static void hw_core_init(hdmi_core_video_config *v_cfg,
                         hw_audio_configure *audio_cfg,
                         hdmi_core_infoframe_avi *avi,
                         hdmi_core_packet_enable_repeat *r_p)
{

    BUG_ON((NULL == v_cfg) || (NULL == audio_cfg) || (NULL == avi) || (NULL == r_p));

    /* Current MHL IP does not support deep color, so set the default values */
    v_cfg->input_bus_wide                = HDMI_INPUT_8BIT;
    v_cfg->output_dither_truncation      = HDMI_OUTPUT_TRUNCATION_8BIT;
    v_cfg->deep_color_packet_enabled     = HDMI_DEEP_COLOR_PACKECT_DISABLE;
    v_cfg->packet_mode                   = HDMI_PACKET_MODE_24BIT_PER_PIXEL;
    v_cfg->hdmi_dvi                      = HDMI_HDMI;
    v_cfg->tclk_sel_clk_mult             = FPLL10IDCK;

    /* audio core */
    audio_cfg->fs                        = FS_48000;
    audio_cfg->n                         = 6144;
    audio_cfg->layout                    = LAYOUT_2CH;
    audio_cfg->if_fs                     = IF_FS_NO;
    audio_cfg->if_channel_number         = 2;
    audio_cfg->if_sample_size            = IF_NO_PER_SAMPLE;
    audio_cfg->if_audio_channel_location = HDMI_CEA_CODE_00;
    audio_cfg->i2schst_max_word_length   = I2S_CHST_WORD_MAX_20;
    audio_cfg->i2schst_word_length       = I2S_CHST_WORD_16_BITS;
    audio_cfg->i2s_in_bit_length         = I2S_IN_LENGTH_16;
    audio_cfg->i2s_justify               = HDMI_AUDIO_JUSTIFY_LEFT;
    audio_cfg->aud_par_busclk            = 0;
    audio_cfg->bsio                      = true;
    audio_cfg->cts_mode                  = CTS_MODE_HW;

    /* info frame */
    avi->db1y_rgb_yuv422_yuv444          = INFOFRAME_AVI_DB1Y_RGB;
    avi->db1a_active_format_off_on       = INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_OFF;
    avi->db1b_no_vert_hori_verthori      = INFOFRAME_AVI_DB1B_NO;
    avi->db1s_0_1_2                      = INFOFRAME_AVI_DB1S_0;
    avi->db2c_no_itu601_itu709_extented  = INFOFRAME_AVI_DB2C_NO;
    avi->db2m_no_43_169                  = INFOFRAME_AVI_DB2M_NO;
    avi->db2r_same_43_169_149            = INFOFRAME_AVI_DB2R_SAME;
    avi->db3itc_no_yes                   = INFOFRAME_AVI_DB3ITC_NO;
    avi->db3ec_xvyuv601_xvyuv709         = INFOFRAME_AVI_DB3EC_XVYUV601;
    avi->db3q_default_lr_fr              = INFOFRAME_AVI_DB3Q_DEFAULT;
    avi->db3sc_no_hori_vert_horivert     = INFOFRAME_AVI_DB3SC_NO;
    avi->db4vic_videocode                = 0;
    avi->db5pr_no_2_3_4_5_6_7_8_9_10     = INFOFRAME_AVI_DB5PR_NO;
    avi->db6_7_lineendoftop              = 0 ;
    avi->db8_9_linestartofbottom         = 0;
    avi->db10_11_pixelendofleft          = 0;
    avi->db12_13_pixelstartofright       = 0;

    /* packet enable and repeat */
    r_p->audio_packet_ed                 = PACKET_DISABLE;
    r_p->audio_packet_repeat             = PACKET_REPEAT_OFF;
    r_p->avi_info_frame_ed               = PACKET_DISABLE;
    r_p->avi_info_frame_repeat           = PACKET_REPEAT_OFF;
    r_p->general_control_packet_ed       = PACKET_DISABLE;
    r_p->general_control_packet_repeat   = PACKET_REPEAT_OFF;
    r_p->generic_packet_ed               = PACKET_DISABLE;
    r_p->generic_packet_repeat           = PACKET_REPEAT_OFF;
    r_p->mpeg_info_frame_ed              = PACKET_DISABLE;
    r_p->mpeg_info_frame_repeat          = PACKET_REPEAT_OFF;
    r_p->spd_info_frame_ed               = PACKET_DISABLE;
    r_p->spd_info_frame_repeat           = PACKET_REPEAT_OFF;

    return;
}

/******************************************************************************
* Function:       hw_core_video_config
* Description:    set video config
* Input:          video config
* Output:
* Return:
*******************************************************************************/
static void hw_core_video_config(hdmi_core_video_config *cfg)
{
    BUG_ON(NULL == cfg);

    /* Most registers use default value after chip initilized except the following */

    //set 0x7A:0x2F[5:3] = cfg->packet_mode
    //set 0x7A:0x2F[0]   = cfg->hdmi_dvi
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR,
                                 (BIT5 | BIT4 | BIT3 | BIT0),
                                 ((cfg->packet_mode << 3) + cfg->hdmi_dvi));

    return;
}

/******************************************************************************
* Function:       hw_core_audio_infoframe_avi
* Description:    set avi info
* Input:          avi info
* Output:
* Return:
*******************************************************************************/
static void hw_core_audio_infoframe_avi(hdmi_core_infoframe_avi info_avi)
{
    uint8_t ifData[SIZE_AVI_INFOFRAME] = {0};
    
    ifData[0]  = 0x82;                    /* type  (AVI InfoFrame) */
    ifData[1]  = 0x02;                    /* version */
    ifData[2]  = 0x0D;                    /* length */
    ifData[3]  = 0x00;                    /* checksum */
    ifData[4]  = (info_avi.db1y_rgb_yuv422_yuv444 << 5)
		     | (info_avi.db1a_active_format_off_on << 4)
		     | (info_avi.db1s_0_1_2);

    ifData[5]  = (info_avi.db2m_no_43_169 << 4) | (info_avi.db2r_same_43_169_149);

    //ifData[6]  = info_avi.db3q_default_lr_fr << 2;

    ifData[7]  = info_avi.db4vic_videocode;

    /* ifData[8]~ifData[16] are always 0x00 */

    ifData[3] = CalculateGenericCheckSum(ifData, 0, SIZE_AVI_INFOFRAME);

    /* Disbale MPEG/Vendor Specific InfoFrames */
    SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR, 0x00);

    /* Re-enable Avi InfoFrame transmission and repeat */
    SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR, BIT_TPI_INFO_RPT | BIT_TPI_INFO_EN | BIT_TPI_INFO_SEL_AVI);

    SiiDrvWriteBlockTPI(TPI_AVI_DBYTE_ADDR, SIZE_AVI_INFOFRAME - 3, ifData + 3);

    return;
}

#if 0
/******************************************************************************
* Function:       hw_core_av_packet_config
* Description:    set audio and video packet config
* Input:          hdmi_core_packet_enable_repeat
* Output:
* Return:
*******************************************************************************/
static void hw_core_av_packet_config(hdmi_core_packet_enable_repeat r_p)
{    
    r_p.avi_info_frame_ed     = PACKET_ENABLE;
    r_p.avi_info_frame_repeat = PACKET_REPEAT_ON;
    
    r_p.audio_packet_ed       = PACKET_ENABLE;
    r_p.audio_packet_repeat   = PACKET_REPEAT_ON;
    
    r_p.spd_info_frame_ed     = PACKET_DISABLE;
    r_p.spd_info_frame_repeat = PACKET_REPEAT_OFF;
    
    r_p.generic_packet_ed     = PACKET_ENABLE;
    r_p.generic_packet_repeat = PACKET_REPEAT_ON;
    
    /* enable/repeat the infoframe */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_INF_CTRL1_ADDR, (uint8_t)
             ((r_p.mpeg_info_frame_ed << 7) |
              (r_p.mpeg_info_frame_repeat << 6) |
              (r_p.audio_packet_ed << 5) |
              (r_p.audio_packet_repeat << 4) |
              (r_p.spd_info_frame_ed << 3) |
              (r_p.spd_info_frame_repeat << 2) |
              (r_p.avi_info_frame_ed << 1) |
              (r_p.avi_info_frame_repeat)));

    /* enable/repeat the packet */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_INF_CTRL2_ADDR, (uint8_t)
             ((r_p.general_control_packet_ed << 3) |
              (r_p.general_control_packet_repeat << 2) |
              (r_p.generic_packet_ed << 1) |
              (r_p.generic_packet_repeat)));

    return;
}
#endif

/******************************************************************************
* Function:       hw_configure_lrfr
* Description:    Setting the AVI infroframe to respective limited range
* Input:          
* Output:
* Return:
*******************************************************************************/
static int hw_configure_lrfr()
{
    if ((INFOFRAME_AVI_DB1Y_RGB == hdmi.avi_param.db1y_rgb_yuv422_yuv444)
    && (HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3 == hdmi.avi_param.db4vic_videocode))
    {
        hdmi.avi_param.db3q_default_lr_fr = INFOFRAME_AVI_DB3Q_FR;

        //set TPI 0x09[3:2]=0b'01
        SiiDrvModifyByteTPI(TPI_OUTPUT_FMT_ADDR, BIT3 | BIT2, OUTPUT_RANGE_FULL << 2);
    }
    else
    {
        hdmi.avi_param.db3q_default_lr_fr = INFOFRAME_AVI_DB3Q_LR;

        //set TPI 0x0A[3:2]=0b'10
        SiiDrvModifyByteTPI(TPI_OUTPUT_FMT_ADDR, BIT3 | BIT2, OUTPUT_RANGE_LIMIT << 2);
    }

    return 0;
}

/***********************************************************************************
* Function:       hw_core_mute_audio
* Description:    enable or disable audio mute.
* Input:          bool benabled: true:enable audio mute, false:disable audio mute
* Output:         NA
* Return:         NA
***********************************************************************************/
void hw_core_mute_audio(bool benabled)
{
    uint8_t audio_cfg;

    /* get mute flag from audio configuration write data(0x26) */
    audio_cfg = SiiDrvReadByteTPI (TPI_AUDIO_CONF_1_ADDR);

    /* if mute flag is true and want to unmute, then set 0 to mute flag */
    if(audio_cfg & 0x10)
    {
        if(false == benabled)
        {
            SiiDrvModifyByteTPI (TPI_AUDIO_CONF_1_ADDR, BIT4, 0x00);
            logd("unmute audio.\n");
        }
    }
    else
    {
        /* if mute flag is false and want to mute, then set 1 to mute flag */
        if(true == benabled)
        {
            SiiDrvModifyByteTPI (TPI_AUDIO_CONF_1_ADDR, BIT4, BIT4);
            logd("mute audio.\n");
        }
    }

    return;
}

/******************************************************************************
* Function:       hw_configure_acr
* Description:    config n and cts by pclk, fs and deep_color
* Input:          pixel clock, audio fs
* Output:
* Return:
*******************************************************************************/
int hw_configure_acr(u32 pclk, hdmi_core_fs audio_fs)
{
    u32 fs          = 0;
    u32 n           = 0;
    u32 cts         = 0;

    switch (audio_fs) {
        case FS_32000:
            fs = 32000;
            n = 4096;
            break;
        case FS_44100:
            fs = 44100;
            n = 6272;
            break;
        case FS_48000:
            fs = 48000;
            n = 6144;
            break;
        case FS_96000:
            fs = 96000;
            n = 12288;
            break;
        case FS_176400:
            fs = 176400;
            n = 25088;
            break;
        case FS_192000:
            fs = 192000;
            n = 24576;
            break;
        case FS_88200:
            fs = 88200;
            n = 12544;
            break;
        case FS_NOT_INDICATED:
        default:
            loge("fs is invalid: %d.\n", audio_fs);
            OUT_FUNCTION;
            return -EINVAL;
    }

    /* Process CTS */
    cts = (pclk * (n / 128) * 10) / (fs / 100);

    hdmi.audio_core_cfg.n = n;
    hdmi.audio_core_cfg.cts = cts;

    logi("audio: n is %d, cts is %d\n", n, cts);

    return 0;
}

/******************************************************************************
* Function:       hw_core_audio_config
* Description:    set audio config
* Input:          audio config
* Output:
* Return:
*******************************************************************************/
void hw_configure_audio(hw_audio_configure *audio_cfg)
{
    IN_FUNCTION;

    /*1. Mute the audio sent to the receiver. Set TPI 0x26[4] to 1*/
    hw_core_mute_audio(true);

    /*2. Disable the audio input stream by setting TPI 0x26[7:6] to 0.*/
    SiiDrvModifyByteTPI(TPI_AUDIO_CONF_1_ADDR, (BIT7 | BIT6), 0x0);

    /*3. Set all audio mode registers to the new audio mode as needed.*/
    mhl_audio_config_param(audio_cfg);

    mhl_audio_config_infoframe(audio_cfg);

    /*4. Wait 6 ms.*/
    mdelay(6);

    /*5. Unmute the audio sent to the receiver. (Set TPI 0x26[4] to 0).*/
    hw_core_mute_audio(false);

    OUT_FUNCTION;

    return;
}

/******************************************************************************
* Function:      mhl_audio_config_param
* Description:   config audio params set in audio_core_cfg
* Input:         audio_core_cfg
* Output:        na
* Return:        void
*******************************************************************************/
void mhl_audio_config_param(hw_audio_configure *audio_cfg) //UT XU
{
    BUG_ON(NULL == audio_cfg);

    IN_FUNCTION;

    logi("audio_cfg->n=%d, audio_cfg->if_channel_number=%d,\n"
           "audio_cfg->aud_par_busclk=%d, audio_cfg->fs=%d,\n"
           "audio_cfg->audiotype=%d, audio_cfg->i2s_justify=%d,\n"
           "audio_cfg->bsio=%d, audio_cfg->i2schst_word_length=%d,\n"
           "audio_cfg->i2schst_max_word_length=%d, audio_cfg->i2s_in_bit_length=%d,\n"
           "audio_cfg->layout=%d\n", 
           audio_cfg->n, audio_cfg->if_channel_number,
           audio_cfg->aud_par_busclk, audio_cfg->fs,
           audio_cfg->audiotype, audio_cfg->i2s_justify,
           audio_cfg->bsio, audio_cfg->i2schst_word_length,
           audio_cfg->i2schst_max_word_length, audio_cfg->i2s_in_bit_length,
           audio_cfg->layout);

    /* CTS_MODE :MCLK_EN (1: enable) NCTSPKT_EN(1: enable) CTS Source Select (1:SW, 0:HW)
        CTS_SEL: Silicon Image recommends the utilization of a MCLK and not set this bit to 1.
        N_SVAL: default 0x1880                      CTS_SVAL: only CTS_SEL set to 1 */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_ACR_CTRL_ADDR,
                                                   ((0x1 << 2)|(1 << 1)|(CTS_MODE_HW << 0)));
    /* FREQ_VAL: FM_IN_VAL_SW(MCLK input mode--000:128*Fs; 001:256*Fs)
         TPI 0x27: AUDIO_CONFIG_FS when FS is 192 or 176.4, MCLK should be 128*Fs */
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_FREQ_SVAL_ADDR, (BIT2 | BIT1 | BIT0), 
		                                      /* ((FS_192000 == audio_cfg->fs) || (FS_176400 == audio_cfg->fs)) ? 0 : */1);


    /* Set I2S sample freq */
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_I2S_CHST4_ADDR, (BIT3 | BIT2 | BIT1 | BIT0), (uint8_t)(audio_cfg->fs));
    SiiDrvWriteByteTPI(TPI_AUDIO_CONF_2_ADDR,
                                    (uint8_t)((audio_cfg->if_sample_size << 6)
                                                |(audio_cfg->if_fs << 3)
                                                |(audio_cfg->if_channel_number)));

    /* write audio FS_ORIG and i2s word length */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_CHST5_ADDR,
                                                   (uint8_t)(((audio_cfg->fs) << 4) /* FS_ORIG */
                                                              | ((audio_cfg->i2schst_word_length) << 1)
                                                              | (audio_cfg->i2schst_max_word_length)));
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_I2S_IN_LEN_ADDR, (BIT3 | BIT2 | BIT1 | BIT0),
                                                    (uint8_t)(audio_cfg->i2s_in_bit_length));
    
    /* channel enable depend of the layout */
    if (false == audio_cfg->bsio)
    {
        /* SPDIF */
        SiiDrvModifyByteTPI(TPI_AUDIO_CONF_1_ADDR,
                                          BIT_TPI_CONFIG_3_AUDIO_INTERFACE_MASK,
                                          BIT_TPI_CONFIG_3_AUDIO_INTERFACE_SPDIF);

        SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x0);

        //SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR, BIT2 | BIT1, 0x2);//why
        //SiiDrvModifyByteTPI(TPI_AUDIO_HANDLING_ADDR, BIT1|BIT0, 0);
        /* FS_OVERRIDE = 0 disable, sample freq of SPDIF is detected automatically */
        SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_SPDIF_CTRL_ADDR, BIT1, 0);
    }
    else
    {
        /* I2S */
        SiiDrvModifyByteTPI(TPI_AUDIO_CONF_1_ADDR,
                                          BIT_TPI_CONFIG_3_AUDIO_INTERFACE_MASK,
                                          BIT_TPI_CONFIG_3_AUDIO_INTERFACE_I2S);

        /* number of channel */
        SiiDrvModifyByteTPI(TPI_AUDIO_CONF_2_ADDR, (BIT2 | BIT1 | BIT0), (uint8_t)(audio_cfg->if_channel_number-1));


	    if (LAYOUT_2CH == audio_cfg->layout)
	    {
	        /* 2 channel */
                SiiDrvModifyByteTPI(TPI_AUDIO_CONF_1_ADDR,
                                          BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_MASK,
                                          BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_2CH);

                SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x80);

                SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_MODE_ADDR, 0x11);

                SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR, BIT2 | BIT1, 0x0);
	    }
	    else if (LAYOUT_8CH == audio_cfg->layout)
	    {
	        /* 8 channel */
                SiiDrvModifyByteTPI(TPI_AUDIO_CONF_1_ADDR,
                                          BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_MASK,
                                          BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_8CH_MAX);

	        SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x80);//enable SD0
	        SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x81);//enable SD1
	        SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x82);//enable SD2
	        SiiDrvWriteByteTPI(TPI_IIS_MAP_ADDR, 0x83);//enable SD3

                SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_MODE_ADDR, 0xF1);

                SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR, BIT2 | BIT1, 0x2);
	    }
    }

    /*
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_PAR_BUSCLK_1_ADDR, (uint8_t)(audio_cfg->aud_par_busclk));
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_PAR_BUSCLK_2_ADDR, (uint8_t)((audio_cfg->aud_par_busclk >> 8)));
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_PAR_BUSCLK_3_ADDR, (uint8_t)((audio_cfg->aud_par_busclk >> 16)));
    */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (uint8_t)(audio_cfg->n));
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (uint8_t)(audio_cfg->n >> 8));
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (uint8_t)(audio_cfg->n >> 16));

    /*
     * audio config is mainly due to wrapper hardware connection
     * and so are fixed (hardware) I2S deserializer is by-passed
     * so I2S configuration is not needed (I2S don't care).
     * Wrapper is directly connected at the I2S deserialiser
     * output level so some registers call I2S and need to be
     * programmed to configure this parallel bus, there configuration
     * is also fixed and due to the hardware connection (I2S hardware)
     */
    if (1 == audio_cfg->audiotype)
    {
        /* PCM  */
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_ASRC_ADDR,
                  (0x1 << 4) | /* HBR_SPR_MASK */
                  (0x0 << 1) | /*  0 = Down-sample 2-to-1 when SRC_EN is set to 1; 1 = Down-sample 4-to-1 when SRC_EN is set to 1 */
                  (0x0 << 0)); /*  Audio sample rate conversion disable */

        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_IN_CTRL_ADDR,
                  (0 << 7) |    /* HBRA_ON */
                  (1 << 6) |    /* SCK_EDGE Sample clock is rising */
                  (0 << 5) |    /* CBIT_ORDER */
                  (0 << 4) |    /* VBit, 0x0=PCM, 0x1=compressed */
                  (0 << 3) |    /* I2S_WS, 0xdon't care */
                  (audio_cfg->i2s_justify << 2) | /* I2S_JUST*/
                  (0 << 1) |    /* I2S_DIR, 0xdon't care */
                  (0));         /* I2S_SHIFT, 0x0 don't care */
    }
    else
    {
        if (true == audio_cfg->bsio)
        {
            /* high bit compressed */
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_ASRC_ADDR, 0x0); /* HBR_SPR_MASK,Audio sample rate conversion disable */
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_IN_CTRL_ADDR,
                      (1 << 7) |    /* HBRA */
                      (1 << 6) |    /* SCK_EDGE Sample clock is rising */
                      (1 << 5) |    /* CBIT_ORDER */
                      (1 << 4) |    /* VBit, 0x0=PCM, 0x1=compressed */
                      (0 << 3) |    /* I2S_WS, 0xdon't care */
                      (audio_cfg->i2s_justify << 2) | /* I2S_JUST*/
                      (0 << 1) |    /* I2S_DIR, 0xdon't care */
                      (0));         /* I2S_SHIFT, 0x0 don't care */
        }
        else
        {
            /* low bit compressed */
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_ASRC_ADDR, 0x0); /* HBR_SPR_MASK,Audio sample rate conversion disable */
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_IN_CTRL_ADDR,
                      (0 << 7) |    /* not HBRA */
                      (1 << 6) |    /* SCK_EDGE Sample clock is rising */
                      (0 << 5) |    /* CBIT_ORDER */
                      (1 << 4) |    /* VBit, 0x0=PCM, 0x1=compressed */
                      (0 << 3) |    /* I2S_WS, 0xdon't care */
                      (audio_cfg->i2s_justify << 2) | /* I2S_JUST*/
                      (0 << 1) |    /* I2S_DIR, 0xdon't care */
                      (0));        /* I2S_SHIFT, 0x0 don't care */
        }
    }

    OUT_FUNCTION;
    return;
}
/******************************************************************************
* Function:      mhl_audio_config_infoframe
* Description:   config audio info frame to MHL IP when play in I2S mode
* Input:         na
* Output:        na
* Return:        void
*******************************************************************************/
void mhl_audio_config_infoframe(hw_audio_configure *audio_cfg)
{
    uint8_t ifData[SIZE_AUDIO_INFOFRAME] = {0};

    IN_FUNCTION;

    /* Enable selected audio infoframe (can't be read) and repeat each frame; */
    SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR,
                                    BIT_TPI_INFO_EN
                                    | BIT_TPI_INFO_RPT
                                    | BIT_TPI_INFO_READ_FLAG_NO_READ
                                    | BIT_TPI_INFO_SEL_Audio);

    /* Audio info frame setting refer to CEA-861-d spec p75 */
    /* Audio Info Frame Type */
    ifData[0] = 0x84;

    /* Audio Info Frame Version */
    ifData[1] = 0x01;

    /* Audio Info Frame Word Length */
    ifData[2] = 0x0A;

    /* Audio Info Frame Data Byte 1:  bit7:4 Coding Type;  bit2:0 Channel Number;  0: Refer to StreamHeader  */
    /* For HDMI 1.4a spec code type is always 0, 0b1001 for DSD audio */
    ifData[4] = (uint8_t)(/*(audio_cfg->audiotype << 4) +*/ (audio_cfg->if_channel_number - 1));

    /* Audio Info Frame Data Byte 2:  bit4:2 Sample Frequency;  bit1:0 Sample Size;  0: Refer to StreamHeader  */
    /* For HDMI 1.4a spec , this byte is always 0 for PCM audio */
    ifData[5] = (1 == audio_cfg->audiotype) ? 0 : ((audio_cfg->if_fs << 2) + audio_cfg->if_sample_size);

    /* Audio Info Frame Data Byte 4:  speaker placement according to CEA spec */
    ifData[7] = audio_cfg->if_audio_channel_location;

    /* Other Bytes of Audio Info Frame are 0 */

    /* Audio Info Frame Checksum */
    ifData[3] = CalculateGenericCheckSum(ifData, 0, SIZE_AUDIO_INFOFRAME);

    SiiDrvRegWriteBlock(MHL_TPI_SYS, TPI_I_F_TYPE_ADDR, ifData, SIZE_AUDIO_INFOFRAME);

    OUT_FUNCTION;

    return;
}

/******************************************************************************
* Function:       hw_get_aspect_ratio
* Description:    get the aspect ratio 4:3 or 16:9 or other
* Input:          video_format
* Output:         aspect ratio
* Return:
*******************************************************************************/
static int hw_get_aspect_ratio(u16 video_format)
{
    int ret = INFOFRAME_AVI_DB2M_NO;
    
	/* Support AR in AVI infoframe */
    switch (video_format) {
        /* 16:9 */
        case HDMI_EDID_EX_VIDEO_720x480p_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1280x720p_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x240p_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080i_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080p_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1440x480p_60Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x576p_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1280x720p_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080i_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x288p_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1440x576p_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080p_50Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080p_24Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080p_25Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1920x1080p_30Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1280x720p_100Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x576p_100Hz_16_9:
        case HDMI_EDID_EX_VIDEO_1280x720p_120Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x480p_120Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x576p_200Hz_16_9:
        case HDMI_EDID_EX_VIDEO_720x480p_240Hz_16_9:
            ret= INFOFRAME_AVI_DB2M_169;
            break;
        /* 4:3 */
        case HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x480p_60Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x480i_60Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x576p_50Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x576i_50Hz_4_3:
        case HDMI_EDID_EX_VIDEO_1440x576p_50Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x240p_60Hz_4_3:
        case HDMI_EDID_EX_VIDEO_1440x480p_60Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x288p_50Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x576p_100Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x480p_120Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x576p_200Hz_4_3:
        case HDMI_EDID_EX_VIDEO_720x480p_240Hz_4_3:
            ret = INFOFRAME_AVI_DB2M_43;
            break;
        default:
            ret = INFOFRAME_AVI_DB2M_NO;
            break;
    }

	return ret;
}

/******************************************************************************
* Function:       hw_enable
* Description:    config hdmi by hdmi config or default
* Input:          hdmi configs
* Output:
* Return:
*******************************************************************************/
void hw_enable(hdmi_config *cfg)
{
#if USE_3D
    /* s3d param */
    hdmi_s3d_config s3d_param                   = {0};
#endif
    /* HDMI core */
    hdmi_core_video_config v_core_cfg           = {0};
    hdmi_core_packet_enable_repeat repeat_param = {0};

    BUG_ON(NULL == cfg);

    IN_FUNCTION;

    hw_core_init(&v_core_cfg,
                 &hdmi.audio_core_cfg,
                 &hdmi.avi_param,
                 &repeat_param);

    /****************************** CORE *******************************/
    /************* configure core video part ********************************/
    v_core_cfg.hdmi_dvi = cfg->hdmi_dvi;

    hw_core_video_config(&v_core_cfg);  

    if (HDMI_HDMI == cfg->hdmi_dvi) {
        hdmi.audiochanged = true;
        hdmi_audio_set_param(hdmi.sample_freq, hdmi.sample_size, hdmi.bsio, hdmi.layout, hdmi.audiotype);

        /* config n and cts by pixel_clock and fs */
        hw_configure_acr(hdmi.timings->pixel_clock, hdmi.audio_core_cfg.fs);

        /* set audio config to hdmi device */
        hw_configure_audio(&hdmi.audio_core_cfg);

#if USE_PP_MODE
        SiiMhlTxAttemptPackedPixel(); 
#endif /* USE_PP_MODE */

        /* send avi infoframe */
        /* configure packet, only fill the values which are different from initial value*/
        hdmi.avi_param.db1y_rgb_yuv422_yuv444 = INFOFRAME_AVI_DB1Y_RGB;
        //hdmi.avi_param.db1y_rgb_yuv422_yuv444 = INFOFRAME_AVI_DB1Y_YUV444;  //for YUV444 test

        hdmi.avi_param.db4vic_videocode       = cfg->video_format;
        hdmi.avi_param.db2m_no_43_169         = hw_get_aspect_ratio(cfg->video_format);
        hdmi.avi_param.db1a_active_format_off_on = 1;
        hdmi.avi_param.db1s_0_1_2 = (HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3 == cfg->video_format) ?  2 : 1;
        if (cfg->has_vcdb) {
            int ret = hw_configure_lrfr();
            if (ret) {
                logw("hw_configure_lrfr fail, ret: %d.\n", ret);
            }
        }
        hw_core_audio_infoframe_avi(hdmi.avi_param);

        /* send vsif infoframe */
#if USE_3D
        s3d_param.structure    = cfg->s3d_structure;
        s3d_param.s3d_ext_data = cfg->subsamp_pos;
        hw_core_vsi_infoframe(av_base_addr, s3d_param);
#endif
        /* send packet config */
        //hw_core_av_packet_config(repeat_param);

        hdmi.audiochanged = false;
    }    
  
#ifdef CONFIG_MACH_HI6620OEM
    /* set PHY: DM_TX_CTRL[5] = 1, enable TMDS output */
    /* once TMDS output is enabled, it will trigger HDCP process  */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, BIT5);
#endif

    /* Unmute */
#if (!USE_HDCP)
    SiiDrvVideoUnmute();  
#endif 

    logd("%s: TPI_0x1A is 0x%02x\n", __FUNCTION__, SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR));

    OUT_FUNCTION;
    return;
}

/******************************************************************************
* Function:       hw_free_resources
* Description:    free resources, irq, clk.
* Input:
* Output:
* Return:
*******************************************************************************/
void hw_free_resources(void)
{
    IN_FUNCTION;

    if (hdmi.irq_is_init && hw_res.irq) {
        free_irq(hw_res.irq, (void *)0);
    }

    if (hw_res.clk_pclk_edc1) {
        clk_put(hw_res.clk_pclk_edc1);
        hw_res.clk_pclk_edc1 = NULL;
    }

    if (hw_res.clk_pclk_hdmi) {
        clk_put(hw_res.clk_pclk_hdmi);
        hw_res.clk_pclk_hdmi = NULL;
    }

    if (hw_res.clk_edc1_pixel) {
        clk_put(hw_res.clk_edc1_pixel);
        hw_res.clk_edc1_pixel = NULL;
    }
    
    if (hw_res.clk_edc1_core) {
        clk_put(hw_res.clk_edc1_core);
        hw_res.clk_edc1_core = NULL;
    }
    
    if (hw_res.clk_edc1_axi) {
        clk_put(hw_res.clk_edc1_axi);
        hw_res.clk_edc1_axi = NULL;
    }

    if (hw_res.edc_vcc) {
        regulator_put(hw_res.edc_vcc);
        hw_res.edc_vcc = NULL;
    }

    memset(&hw_res, 0x00, sizeof(hdmi_hw_res));

    OUT_FUNCTION;
    return;
}

/******************************************************************************
* Function:       hw_get_resources
* Description:    get resources, irq, clk, and config base address
* Input:          platform device
* Output:
* Return:
*******************************************************************************/
int hw_get_resources(struct platform_device *pdev)  //UT YANG
{
    int ret              = 0;
    struct resource *res = NULL;

    BUG_ON(NULL == pdev);

    memset(&hw_res, 0, sizeof(hdmi_hw_res));

    res = platform_get_resource_byname(pdev, IORESOURCE_MEM, MHL_REG_NAME);
    if (!res) {
        loge("get mhl reg resource fail.\n");
        OUT_FUNCTION;
        return -ENXIO;
    }

    hw_res.physical_addr = (u32)res->start;

    /* EDC1 shares the same space with MHL */
    hw_res.base_core = k3fd_reg_base_edc1;
    hw_res.base_tpi  = hw_res.base_core;
    hw_res.base_phy  = hw_res.base_core + MHL_PHY_REG_OFFSET;
	hw_res.base_cbus = hw_res.base_core + MHL_CBUS_REG_OFFSET;

    logd("MHL physical addr: 0x%x, virtual addr(base_core): 0x%x\n",
                   (int)hw_res.physical_addr, (int)hw_res.base_core);

    res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, MHL_IRQ_NAME);
    if (!res) {
        loge("get hdmi irq fail.\n");
        ret = -ENXIO;
        goto err;
    }

    hw_res.irq = res->start;
    logd("MHL interrupt number is %d\n", hw_res.irq);

    hw_res.edc_vcc = regulator_get(NULL,  HDMI_EDC1_VCC_NAME);
    if (IS_ERR(hw_res.edc_vcc)) {
        hw_res.edc_vcc = NULL;
        loge("failed to get edc1-vcc regulator\n");
        ret = -ENXIO;
        goto err;
    }

    hw_res.clk_pclk_hdmi = clk_get(NULL, HDMI_APB_CLK_NAME);
    if (IS_ERR(hw_res.clk_pclk_hdmi)) {
        hw_res.clk_pclk_hdmi = NULL;
        loge("failed to get hdmi pclk\n");
        ret = -ENXIO;
        goto err;
    }

    hw_res.clk_pclk_edc1 = clk_get(NULL, EDC1_APB_CLK_NAME);
    if (IS_ERR(hw_res.clk_pclk_edc1)) {
        hw_res.clk_pclk_edc1 = NULL;
        loge("failed to get edc1 pclk\n");
        ret = -ENXIO;
        goto err;
    }
    
    hw_res.clk_edc1_pixel = clk_get(NULL, EDC1_PIXEL_CLK_NAME);
    if (IS_ERR(hw_res.clk_edc1_pixel)) {
        hw_res.clk_edc1_pixel = NULL;
        loge("failed to get edc1 pixel clock\n");
        ret = -ENXIO;
        goto err;
    }
    
    hw_res.clk_edc1_core = clk_get(NULL, EDC1_CORE_CLK_NAME);
    if (IS_ERR(hw_res.clk_edc1_core)) {
        hw_res.clk_edc1_core = NULL;
        loge("failed to get edc1 core clock\n");
        ret = -ENXIO;
        goto err;
    }

    hw_res.clk_edc1_axi = clk_get(NULL, EDC1_AXI_CLK_NAME);
    if (IS_ERR(hw_res.clk_edc1_axi)) {
        hw_res.clk_edc1_axi = NULL;
        loge("failed to get edc1 axi clock\n");
        ret = -ENXIO;
        goto err;
    }

    return 0;

err:
    hw_free_resources();
    return ret;
}

#if USE_3D
/******************************************************************************
* Function:       get_s3d_timings_index
* Description:    get index of 3d video timing from timing code
* Input:
* Output:
* Return:         timing index
*******************************************************************************/
static int get_s3d_timings_index(void)
{
    int index = edid_get_s3d_timings_index(hdmi.mode, hdmi.code);

    if (INVALID_VALUE == index) {
        hdmi.s3d_enabled = false;
        hdmi.mode        = HDMI_DEFAULT_TIMING_MODE;
        hdmi.code        = edid_get_default_code();
        index            = edid_get_timings_index(hdmi.mode, hdmi.code);
    }

    return index;
}
#endif /* USE_3D */

/******************************************************************************
* Function:       update_cfg
* Description:    update hdmi config with video timing
* Input:          video timing
* Output:         hdmi config
* Return:
*******************************************************************************/
static void update_cfg(hdmi_config *cfg, hdmi_video_timings *timings)
{
    BUG_ON((NULL == cfg) || (NULL == timings));

    cfg->pixel_clock = timings->pixel_clock;
    cfg->ppl         = timings->x_res;
    cfg->lpp         = timings->y_res;
    cfg->hbp         = timings->hbp;
    cfg->hfp         = timings->hfp;
    cfg->hsw         = timings->hsw;
    cfg->vbp         = timings->vbp;
    cfg->vfp         = timings->vfp;
    cfg->vsw         = timings->vsw;

    return;
}

/******************************************************************************
* Function:       update_cfg_pol
* Description:    update hdmi config with timing index
* Input:          timing index
* Output:
* Return:
*******************************************************************************/
static void update_cfg_pol(hdmi_config *cfg, int index)
{
    BUG_ON(NULL == cfg);

    cfg->v_pol = edid_get_hvpol_byindex(index)->vsync_pol;
    cfg->h_pol = edid_get_hvpol_byindex(index)->hsync_pol;

    return;
}

/******************************************************************************
* Function:       config_phy_tmds
* Description:    to calculate best aclk_dig
* Input:          vsdb_format
* Output:
* Return:
*******************************************************************************/
static void config_phy_tmds(deep_color *vsdb_format)
{
    int phy                 = 0;

    /* Current MHL IP not support deep color */
    phy                 = hdmi.timings->pixel_clock;
    hdmi.cfg.deep_color = HDMI_DEEP_COLOR_24BIT;

    /* TMDS freq_out in the PHY should be set based on the TMDS clock */
    logd("phy clock: %d.\n", phy);

    /* In new MHL IP, aclkmount is 0b'10(means audio clock range: 98~190MHz) */

    return;
}

void update_set_timing_code(int *mode, int * code)
{
    hdmi_cm cm_best = {INVALID_VALUE, INVALID_VALUE};
    int best_order = 0;
    int order = 0;

    IN_FUNCTION;

    if (hdmi.edid_set == false) {
        logd("hdmi.edid_set :%d, no need to update, mode %d, code %d\n", hdmi.edid_set, *mode, *code);
        return;
    }

    cm_best = edid_get_best_timing((hdmi_edid *)edid);
    if (INVALID_VALUE == cm_best.code) {
        loge("the best code is invalid: mode %d code %d.\n", cm_best.mode, cm_best.code);
        return;
    }

#ifdef CONFIG_MACH_HI6620SFT                
    if (cm_best.code > 104) {
        logd("Stub for DVI, the best code is %d, we set it to 104(640x480/p60)\n", cm_best.code);
        cm_best.code = 104;
    }
#endif               

    if (cm_best.code > HDMI_CODE_VESA_OFFSET) {
        cm_best.code -= HDMI_CODE_VESA_OFFSET;
    }

    /* ignore invalid codes, using best code instead */
    if (!edid_is_valid_code(*mode, *code)) {
        loge("the code is invalid: m - %d, c - %d.\n", *mode, *code);
        *code = cm_best.code;
        *mode = cm_best.mode;
        return;
    }

    logd("manual_set :%d\n", hdmi.manual_set);
    if (hdmi.manual_set) {
        if (cm_best.mode == *mode) {
            if(*mode == HDMI_CODE_TYPE_CEA)
            {
                order = edid_get_timing_order(*code, !hdmi.auto_set);
                best_order = edid_get_timing_order(cm_best.code, !hdmi.auto_set);
            }
            else
            {
                order = edid_get_vesa_timing_order(*code+HDMI_CODE_VESA_OFFSET, !hdmi.auto_set);
                best_order = edid_get_vesa_timing_order(cm_best.code+HDMI_CODE_VESA_OFFSET, !hdmi.auto_set);
            }

            if((order < 0) || (order > best_order)) { //if same mode and user code > best code, use best code
                *code = cm_best.code;
            }
        }
        else {
            if(*mode == HDMI_CODE_TYPE_VESA) { // if cea and vesa , use cea
                *code = cm_best.code;
                *mode = cm_best.mode;
            }
        }
    }
    else { //if auto set, use best timing
        *code = cm_best.code;
        *mode = cm_best.mode;
    }

    logd("update_set_timing_code result: mode %d, code %d\n", *mode, *code);
    OUT_FUNCTION;
}
/******************************************************************************
* Function:       mhl_enable_cfg
* Description:    config parameters to MHL IP
* Input:
* Output:
* Return:
*******************************************************************************/
void mhl_enable_cfg(void)
{
    int index              = INVALID_VALUE;
    deep_color vsdb_format = {0};

    IN_FUNCTION;

#if USE_3D
        if (hdmi.s3d_enabled) {
            /* Update flag to convey if sink supports 3D */
            hdmi.s3d_enabled = edid_s3d_supported(edid);
        }

        if ((hdmi.s3d_enabled) && (HDMI_S3D_FRAME_PACKING == hdmi.cfg.s3d_structure)) {
            logd("using the 3d timings.\n");
            index = get_s3d_timings_index();
        }
        else
#else            
        {
            index = get_timings_index();
        }
#endif /* USE_3D */

        hdmi.timings = edid_get_timings_byindex(index);

        logd("get best timing mode:%d code:%d index:%d\n", hdmi.mode, hdmi.code, index);

        edid_dump_video_timings(hdmi.timings);

        edid_get_deep_color_info(edid, &vsdb_format);

        logd("deep color : bit30=%d, bit36=%d, max_tmds_freq=%d.\n",
             vsdb_format.bit_30, vsdb_format.bit_36,
             vsdb_format.max_tmds_freq);

    /* update config to hdmi device */
    update_cfg(&hdmi.cfg, hdmi.timings);

#if 0
#if USE_3D
    if ((hdmi.s3d_enabled) && (HDMI_S3D_FRAME_PACKING ==  hdmi.cfg.s3d_structure)) {
        logd("using the s3d index.\n");
        index = get_s3d_timings_index();
    } 
    else 
#else        
    {
        logd("using the common index\n");
        index = get_timings_index();
    }
#endif /* USE_3D */
#endif

    update_cfg_pol(&hdmi.cfg, index);

#if 0
    /* update pixel clock with deep color */
    hdmi.timings = edid_get_timings_byindex(index);
    logd("timing index: %d.\n", index);
#endif

    config_phy_tmds(&vsdb_format);

    hdmi.cfg.vsi_enabled = hdmi.s3d_enabled;

    /* This is K3 code:
    hdmi.cfg.hdmi_dvi    = (int)(edid_get_audio_format((u8*)edid, &aformat) ||
                                 (edid_has_ieee_id((u8 *)edid) && hdmi.mode));
    */
    hdmi.cfg.hdmi_dvi = (hdmi_core_hdmi_dvi)g_PlumTxConfig.EDID.HDMI_Sink;
    logd("hdmi.cfg.hdmi_dvi is %d\n", hdmi.cfg.hdmi_dvi);

    if (false == edid_is_valid_edid((u8*)edid)) {
        logw("edid isn't readed, and set to support audio.\n");
        hdmi.cfg.hdmi_dvi = HDMI_HDMI;
	    SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, BIT0, BIT0);     //HDMI output
        //To make sure this bit is set correctly.
        SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR, BIT0, BIT0);
	
    }

    //xzx for audiosupport stub
    hdmi.hdmi_mode = hdmi.cfg.hdmi_dvi;

    hdmi.cfg.video_format = hdmi.code;
    hdmi.cfg.supports_ai  = edid_ai_supported(edid);

    logi("Supports AI: %s, %s: %d, resolution: %dx%d \n",
         hdmi.cfg.supports_ai ? "YES" : "NO",
         hdmi.cfg.hdmi_dvi ? "CEA" : "VESA",
         hdmi.code,
         hdmi.timings->x_res,
         hdmi.timings->y_res);

    if (HDMI_CODE_TYPE_CEA == hdmi.mode) {
        if(EDID_TIMING_MODE_I == edid_get_timing_mode(hdmi.code)) {
            hdmi.cfg.interlace = 1;
        } else {
            hdmi.cfg.interlace = 0;
        }
    }

    hdmi.cfg.has_vcdb = edid_has_vcdb((u8 *) edid);

    hw_enable(&hdmi.cfg);

    if (hdmi.s3d_enabled) {
        hdmi.s3d_type = hdmi.cfg.s3d_structure;
    }
    else {
        hdmi.s3d_type = HDMI_2D;
    }

#if ENABLE_REG_DUMP
    //memcpy((void*)hdmi_reg, (const void*)HDMI_CORE_SYS, HDMI_REG_LENGTH);
    //memcpy((void*)(hdmi_reg + HDMI_REG_LENGTH), (const void*)HDMI_PHY_BASE, HDMI_PHY_REG_LENGTH);
#endif

    OUT_FUNCTION;
}

/******************************************************************************
* Function:      hw_reconfig
* Description:   reconfig when MHL in connected state
* Input:         void
* Output:        na
* Return:        int, 0 for success, others for fail
*******************************************************************************/
int hw_reconfig(void)  //UT YANG
{
    if (!mhl_is_connect()) {
        logw("mhl is disconnect, can't reconfig.\n");
        return -EINVAL;
    }

    if (HDCP_Started == true) {
        if (hdmi.cfg.hdmi_dvi == HDMI_HDMI) {
            /* In HDMI mode, send AV mute to sink, this will disable HDCP */
            SiiDrvVideoMute();
        } else {
            /* In DVI mode, disable HDCP by setting TPI 0x2A[0]=0 */
            SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, BIT0, 0x00);
        }
    } else {
        SiiDrvVideoMute();
    }   

    /* waiting for 64ms to disable HDCP */
    msleep(T_WAIT_FOR_HDCP);

#ifdef CONFIG_MACH_HI6620OEM
    /* config MHL PHY register to disable TMDS output, bit[5]=0 */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, 0x00);
#endif

    /* infoframe packet can send to sink after 128ms */
    msleep(T_WAIT_FOR_INFOFRAME);

    /* config MHL registers to make changed parameters work  */
    mhl_enable_cfg();

#ifdef CONFIG_MACH_HI6620OEM
    /* config MHL PHY register to enable TMDS output, bit[5]=1 */
    SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, BIT5);
#endif

    if (HDCP_Started == true) {
        if (hdmi.cfg.hdmi_dvi == HDMI_HDMI) {
            /* In HDMI mode, send AV unmute to sink, this will enable HDCP */
            SiiDrvVideoUnmute();
        } else {
            /* In DVI mode, enable HDCP by setting TPI 0x2A[0]=1 */
            SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, BIT0, BIT0);
        }
    } 
    /* If HDCP switch is on and TX's KSV is invalid, still mute */
    else if (HDCP_Switch_On == false) {
        SiiDrvVideoUnmute();
    }
    else if (HDCP_AksvValid == true) {
        /* If HDCP switch is on and TX's KSV is valid, check hdcp again */
        SiiHDCP_CheckStatus();
    }

    return 0;
}


/******************************************************************************
* Function:      hw_read_write_reg
* Description:   read or write reg
* Input:         mode: 0-read 1-write reg_page reg_value reg_offset
* Output:        na
* Return:        void
*******************************************************************************/
void hw_read_write_reg(int mode,int reg_page, int reg_value, int reg_offset)
{
	if (mode==0) {
		switch (reg_page)
		{
			case 1: /* p0 */
				reg_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, reg_offset);
				logd("read PAGE_0  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 2:/* p1 */
			       reg_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_1, reg_offset);
				logd("read PAGE_1  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 3:/*p2*/
				reg_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_2, reg_offset);
				logd("read PAGE_2  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 4:/* p phy */
#ifdef CONFIG_MACH_HI6620OEM                
				reg_value = SiiDrvRegRead(MHL_PHY_BASE, reg_offset);
#endif

#ifdef CONFIG_MACH_HI6620SFT
                if (reg_offset <= 0xA8) {
                    reg_value = mhl_phy_read_reg((uint8_t)reg_offset);
                } else {
                    logw("You are configuring wolv40 PHY, its register must be little than 0xA8\n");
                }                
#endif
				logd("read PAGE_PHY  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 5:/* p tpi */
				reg_value = SiiDrvReadByteTPI( reg_offset );
				logd("read TPI  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			default:/* p cbus */
				reg_value = SiiDrvRegRead(MHL_CBUS_BASE, reg_offset);
				logd("read CBUS PAGE  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
		}
	}else {
		switch (reg_page)
		{
			case 1:
				SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, reg_offset, reg_value);
				logd("Write PAGE_0  reg_offset:0x%X value:0x%X", reg_offset ,reg_value);
				break;
			case 2:
				SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, reg_offset, reg_value);
				logd("Write PAGE_1  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 3:
				SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, reg_offset, reg_value);
				logd("Write PAGE_2  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 4:
#ifdef CONFIG_MACH_HI6620OEM                
                SiiDrvRegWrite(MHL_PHY_BASE, reg_offset, reg_value);
#endif

#ifdef CONFIG_MACH_HI6620SFT
                if (reg_offset <= 0xA8) {
                    mhl_phy_write_reg((uint8_t)reg_offset, (uint8_t)reg_value);
                } else {
                    logw("You are configuring wolv40 PHY, its register must be little than 0xA8\n");
                }                
#endif				
				logd("Write PAGE_PHY  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			case 5:
				SiiDrvWriteByteTPI(reg_offset, reg_value);
				logd("Write TPI  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
			default:
				SiiDrvRegWrite(MHL_CBUS_BASE, reg_offset, reg_value);
				logd("Write CBUS PAGE  reg_offset:0x%X value:0x%X", reg_offset, reg_value);
				break;
		}
	
	}
	return;
}

/******************************************************************************
* Function:      dump_mhl_reg
* Description:   dump mhl registers, include TPI/PAGE0/PAGE1/PGAE2/CBUS/PHY
* Input:         void
* Output:        na
* Return:        int, 0 for success, others for fail
*******************************************************************************/
void dump_mhl_reg(void)
{
    int i;
    
    printk("\n============ begin of mhl TPI registers ============");
    for (i = 0; i <= 0xff; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvRegRead(MHL_TPI_SYS, i * 4));
    }
    printk("\n============= end of mhl TPI registers =============\n\n");
    
    printk("============ begin of mhl page0 registers ============");
    for (i = 0; i <= 0xff; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvReadIndexedRegister(INDEXED_PAGE_0, i*4));
    }
    printk("\n============= end of mhl page0 registers =============\n\n");
    
    printk("============ begin of mhl page1 registers ============");
    for (i = 0; i <= 0xff; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvReadIndexedRegister(INDEXED_PAGE_1, i*4));
    }
    printk("\n============= end of mhl page1 registers =============\n\n");
    
    printk("============ begin of mhl page2 registers ============");
    for (i = 0; i <= 0xff; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvReadIndexedRegister(INDEXED_PAGE_2, i*4));
    }
    printk("\n============= end of mhl page2 registers =============\n\n");
    
    printk("============ begin of mhl cbus registers ============");
    for (i = 0; i <= 0xff; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvRegRead(MHL_CBUS_BASE, i * 4));
    }
    printk("\n============= end of mhl cbus registers =============\n\n");

#ifdef CONFIG_MACH_HI6620OEM    
    printk("============ begin of mhl phy registers ============");

    /* hare28hpm has 37(0x25 in hex) registers */
    for (i = 0; i <= 0x25; i++) {
        if (i % 16 == 0) {
            printk("\n0x%02x: ", i);
        }        
        printk("%02x ", SiiDrvRegRead(MHL_PHY_BASE, i * 4));
    }
    printk("\n============= end of mhl phy registers =============\n\n");
#endif    
}

#if USE_HDCP
/******************************************************************************
* Function:      hw_reconfig_hdcp
* Description:   reconfig hdcp when user enable/disable hdcp 
* Input:         hdcp_enable, true for enable, false for disable
* Output:        na
* Return:        na
*******************************************************************************/
void hw_reconfig_hdcp(bool hdcp_enable)  
{
    logi("Currrent HDCP switch: %d, enable: %d\n", HDCP_Switch_On, hdcp_enable);
    
    if (HDCP_Switch_On == hdcp_enable) {
        return;
    }

    HDCP_Switch_On = hdcp_enable;

    if (HDMI_POWER_FULL != hdmi.power_state) {
        logd("MHL isn't in FULL state, don't reconfig HDCP.\n");
        return;
    }

    /* In connected state, enable HDCP */
    if (hdcp_enable == true) {
        SiiDrvVideoMute();

#ifdef CONFIG_MACH_HI6620OEM        
        /* config MHL PHY register to disable TMDS output, bit[5]=0 */
        SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, 0x00);
#endif
        /* infoframe packet can send to sink after 128ms */
        msleep(T_WAIT_FOR_INFOFRAME);

        /* HDCP handle function */
        SiiHDCP_CheckStatus();

#ifdef CONFIG_MACH_HI6620OEM
        /* config MHL PHY register to enable TMDS output, bit[5]=1 */
        SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, BIT5);
#endif
    }
    /* In connected state, disable HDCP */
    else {
        SiiDrvHDCP_Off();
        
        /* waiting for 64ms to disable HDCP */
        msleep(T_WAIT_FOR_HDCP);
        
#ifdef CONFIG_MACH_HI6620OEM
        /* config MHL PHY register to disable TMDS output, bit[5]=0 */
        SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, 0x00);
#endif
        /* infoframe packet can send to sink after 128ms */
        msleep(T_WAIT_FOR_INFOFRAME);

#ifdef CONFIG_MACH_HI6620OEM
        /* config MHL PHY register to enable TMDS output, bit[5]=1 */
        SiiDrvRegModify(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, BIT5, BIT5);
#endif

        SiiDrvVideoUnmute();
    }

    return;
}
#endif /* USE_HDCP */

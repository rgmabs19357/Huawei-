/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_mhl_hw.h
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/

#ifndef __SI_MHL_HW_H__
#define __SI_MHL_HW_H__

#include <linux/platform_device.h>
#include "reg_ops.h"
#include "soc_baseaddr_interface.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#include <mach/clk_name_interface.h>

/* When using MHL, we need to lock DDR frequency */
enum
{
    MHL_DDR_MIN_FREQ_75M  = 75000,
    MHL_DDR_MIN_FREQ_150M = 150000,
    MHL_DDR_MIN_FREQ_260M = 260000,
    MHL_DDR_MIN_FREQ_360M = 360000,
    MHL_DDR_MIN_FREQ_533M = 533000,
    MHL_DDR_MIN_FREQ_800M = 800000,
};

#define T_WAIT_FOR_HDCP                    64        /* disable HDCP, waiting time */
#define T_WAIT_FOR_INFOFRAME               128       /* disable TMDS, waiting time */

/* set SC_PW_RSTDIS0[4]=1, disable reset of EDC1 power area */
#define DISABLE_RST_EDC1_PW \
    phy_reg_writel(SOC_SC_ON_BASE_ADDR, \
                   SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET), 4, 4, 1)

/* set SC_PW_RSTDIS0[26]=1, disable reset of MHL PHY power area */
#define DISABLE_RST_MHL_PHY_PW \
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                   SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET), 26, 26, 1)

/* set SC_PW_ISODIS0[4]=1, disable ISO of EDC1 */
#define DISABLE_ISO_EDC1_PW \
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                   SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(CALC_REG_OFFSET), 4, 4, 1)

/* set SC_PW_CLKEN0[4]=1, open clock of EDC1 power area */
#define ENABLE_CLK_EDC1_PW \
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                   SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(CALC_REG_OFFSET), 4, 4, 1)

/* set PERIPH_RSTDIS7[22]=1, disable reset of HDMI/MHL */
#define DISABLE_RST_MHL_CORE \
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,\
                   SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(CALC_REG_OFFSET), 22, 22, 1)

/* set PERIPH_RSTDIS7[4:8]=11111, disable reset of other edc1 clock*/
#define DISABLE_RST_EDC1_REST \
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,\
                   SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(CALC_REG_OFFSET), \
                   4, 8, 0x1f)

#define ENABLE_CLK_EDC1_REST \
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,\
                   SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(CALC_REG_OFFSET), \
                   7, 7, 0x1)                 

/* set PERIPH_RSTEN7[22]=1, reset of HDMI/MHL */
#define RST_MHL_CORE \
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,\
                       SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(CALC_REG_OFFSET),\
                       22, 22, 1)

/* set PERIPH_RSTEN7[4:8]=11111, reset of other edc1 clock*/
#define RST_EDC1_REST \
        phy_reg_writel(SOC_SC_OFF_BASE_ADDR,\
                      SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(CALC_REG_OFFSET), \
                      4, 8, 0x1f)


/* set SC_PW_CLKDIS0[4]=1, disable clock of EDC1 power area */
#define DISABLE_CLK_EDC1_PW \
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                       SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(CALC_REG_OFFSET),\
                       4, 4, 1)

/* set SC_PW_ISOEN0[4]=1, enable ISO of EDC1 */
#define ENABLE_ISO_EDC1_PW \
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                       SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(CALC_REG_OFFSET),\
                       4, 4, 1)

/* set SC_PW_RSTEN0[26]=1, reset of MHL PHY power area */
#define RST_MHL_PHY_PW \
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                       SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),\
                       26, 26, 1)

/* set SC_PW_RSTEN0[4]=1, reset of EDC1 power area */
#define RST_EDC1_PW \
        phy_reg_writel(SOC_SC_ON_BASE_ADDR,\
                       SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),\
                       4, 4, 1)

#define MHL_CBUS_REG_OFFSET 	0x2000
#define MHL_PHY_REG_OFFSET      0x1800
#define MHL_EFUSEC_OFFSET       0x1000
#define MHL_LDI1_OFFSET         0x2800
#define MHL_EDC1_OFFSET         0x3000

#ifndef REG_MHL_IOSIZE
#define REG_MHL_IOSIZE                           PAGE_ALIGN(SZ_16K)
#endif

#define EDC1_CORE_CLK_NAME  CLK_EDC1_CORE			/* edc1 core clock */
#define EDC1_PIXEL_CLK_NAME CLK_EDC1_PIX_LDI	    /* edc1 pix clock */
#define EDC1_AXI_CLK_NAME   CLK_EDC1_AXI	    	/* edc1 axi bus interface clock */
#define EDC1_APB_CLK_NAME   CLK_EDC1_CFG_CLK	   	/* edc1 APB config clock */
#define HDMI_APB_CLK_NAME   CLK_HDMI_SLAVE          /* HDMI/MHL ABP config slave clock */


#define HDMI_EDC1_VCC_NAME  "EDC1_VDD"

typedef enum _output_format_range {
    OUTPUT_RANGE_AUTO  = 0,  /* Auto-selected */
    OUTPUT_RANGE_FULL  = 1,  /* Full range (0-255) */
    OUTPUT_RANGE_LIMIT = 2,  /* Limited range (16-235) */
    OUTPUT_RANGE_RSVD  = 3   /* reserved */
} output_format_range;

typedef enum _hdmi_core_inputbus_width {
    HDMI_INPUT_8BIT  = 0,   /* input bus width with 8 bit */
    HDMI_INPUT_10BIT = 1,   /* input bus width with 10 bit */
    HDMI_INPUT_12BIT = 2    /* input bus width with 12 bit */
} hdmi_core_inputbus_width;

typedef enum _hdmi_core_dither_trunc {
    HDMI_OUTPUT_TRUNCATION_8BIT  = 0,   /* output truncation with 8 bit */
    HDMI_OUTPUT_TRUNCATION_10BIT = 1,   /* output truncation with 10 bit */
    HDMI_OUTPUT_TRUNCATION_12BIT = 2,   /* output truncation with 12 bit */
    HDMI_OUTPUT_DITHER_8BIT      = 3,   /* output dither with 8 bit */
    HDMI_OUTPUT_DITHER_10BIT     = 4,   /* output dither with 10 bit */
    HDMI_OUTPUT_DITHER_12BIT     = 5    /* output dither with 12 bit */
} hdmi_core_dither_trunc;

typedef enum _hdmi_core_deep_color_ed {
    HDMI_DEEP_COLOR_PACKECT_DISABLE = 0,    /* deep color packect is disable */
    HDMI_DEEP_COLOR_PACKECT_ENABLE  = 1     /* deep color packect is enable */
} hdmi_core_deep_color_ed;

typedef enum _hdmi_core_packet_mode {
    HDMI_PACKET_MODE_RESERVED_VALUE  = 0,   /* packet mode reserved value */
    HDMI_PACKET_MODE_24BIT_PER_PIXEL = 4,   /* packet mode 24 bit per pixel */
    HDMI_PACKET_MODE_30BIT_PER_PIXEL = 5,   /* packet mode 30 bit per pixel */
    HDMI_PACKET_MODE_36BIT_PER_PIXEL = 6,   /* packet mode 36 bit per pixel */
    HDMI_PACKET_MODE_48BIT_PER_PIXEL = 7    /* packet mode 48 bit per pixel */
} hdmi_core_packet_mode;

typedef enum _hdmi_core_hdmi_dvi {
    HDMI_DVI     = 0,   /* hdmi mode -- dvi mode */
    HDMI_HDMI    = 1    /* hdmi mode -- hdmi mode */
} hdmi_core_hdmi_dvi;

typedef enum _hdmi_core_tclkselclkmult {
    FPLL05IDCK  = 0,    /* FPLL is 0.5*IDCK */
    FPLL10IDCK  = 1,    /* FPLL is 1.0*IDCK */
    FPLL20IDCK  = 2,    /* FPLL is 2.0*IDCK */
    FPLL40IDCK  = 3     /* FPLL is 4.0*IDCK */
} hdmi_core_tclkselclkmult;

typedef struct _hdmi_core_video_config_t {
    hdmi_core_inputbus_width input_bus_wide;              /* input bus wide */
    hdmi_core_dither_trunc   output_dither_truncation;    /* output dither truncation */
    hdmi_core_deep_color_ed  deep_color_packet_enabled;   /* deep color packet */
    hdmi_core_packet_mode    packet_mode;                 /* packet mode */
    hdmi_core_hdmi_dvi       hdmi_dvi;                    /* hdmi or dvi mode */
    hdmi_core_tclkselclkmult tclk_sel_clk_mult;
} hdmi_core_video_config;

typedef enum _hdmi_core_fs {
    FS_32000  = 0x3,        /* audio fs is    32 kHz */
    FS_44100  = 0x0,        /* audio fs is  44.1 kHz */
    FS_48000  = 0x2,        /* audio fs is    48 kHz */
    FS_88200  = 0x8,        /* audio fs is  88.2 kHz */
    FS_96000  = 0xA,        /* audio fs is    96 kHz */
    FS_176400 = 0xC,        /* audio fs is 176.4 kHz */
    FS_192000 = 0xE,        /* audio fs is   192 kHz */
    FS_NOT_INDICATED = 0x1  /* audio fs is indicated */
} hdmi_core_fs;

typedef enum _hdmi_core_layout {
    LAYOUT_2CH = 0,     /* audio is 2 channel */
    LAYOUT_3CH,     /* audio is 3 channel */
    LAYOUT_4CH,     /* audio is 4 channel */
    LAYOUT_5CH,     /* audio is 5 channel */
    LAYOUT_6CH,     /* audio is 6 channel */
    LAYOUT_7CH,     /* audio is 7 channel */
    LAYOUT_8CH      /* audio is 8 channel */
} hdmi_core_layout;

typedef enum _hdmi_core_cts_mode {
    CTS_MODE_HW = 0,    /* cts make reference to hardware */
    CTS_MODE_SW = 1     /* cts make reference to software */
} hdmi_core_cts_mode;

typedef enum _hdmi_core_packet_ctrl {
    PACKET_ENABLE    = 1,   /* packet enable */
    PACKET_DISABLE   = 0,   /* packet disable */
    PACKET_REPEAT_ON  = 1,  /* packet repeat is on */
    PACKET_REPEAT_OFF = 0   /* packet repeat is off */
} hdmi_core_packet_ctrl;

/* INFOFRAME_AVI_ definations */
typedef enum _hdmi_core_infoframe {
    INFOFRAME_AVI_DB1Y_RGB      = 0,
    INFOFRAME_AVI_DB1Y_YUV422   = 1,
    INFOFRAME_AVI_DB1Y_YUV444   = 2,
    INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_OFF = 0,
    INFOFRAME_AVI_DB1A_ACTIVE_FORMAT_ON  = 1,
    INFOFRAME_AVI_DB1B_NO       = 0,
    INFOFRAME_AVI_DB1B_VERT     = 1,
    INFOFRAME_AVI_DB1B_HORI     = 2,
    INFOFRAME_AVI_DB1B_VERTHORI = 3,
    INFOFRAME_AVI_DB1S_0        = 0,
    INFOFRAME_AVI_DB1S_1        = 1,
    INFOFRAME_AVI_DB1S_2        = 2,
    INFOFRAME_AVI_DB2C_NO       = 0,
    INFOFRAME_AVI_DB2C_ITU601   = 1,
    INFOFRAME_AVI_DB2C_ITU709   = 2,
    INFOFRAME_AVI_DB2C_EC_EXTENDED  = 3,
    INFOFRAME_AVI_DB2M_NO       = 0,
    INFOFRAME_AVI_DB2M_43       = 1,
    INFOFRAME_AVI_DB2M_169      = 2,
    INFOFRAME_AVI_DB2R_SAME     = 8,
    INFOFRAME_AVI_DB2R_43       = 9,
    INFOFRAME_AVI_DB2R_169      = 10,
    INFOFRAME_AVI_DB2R_149      = 11,
    INFOFRAME_AVI_DB3ITC_NO     = 0,
    INFOFRAME_AVI_DB3ITC_YES    = 1,
    INFOFRAME_AVI_DB3EC_XVYUV601    = 0,
    INFOFRAME_AVI_DB3EC_XVYUV709    = 1,
    INFOFRAME_AVI_DB3Q_DEFAULT  = 0,
    INFOFRAME_AVI_DB3Q_LR       = 1,
    INFOFRAME_AVI_DB3Q_FR       = 2,
    INFOFRAME_AVI_DB3SC_NO      = 0,
    INFOFRAME_AVI_DB3SC_HORI    = 1,
    INFOFRAME_AVI_DB3SC_VERT    = 2,
    INFOFRAME_AVI_DB3SC_HORIVERT    = 3,
    INFOFRAME_AVI_DB5PR_NO      = 0,
    INFOFRAME_AVI_DB5PR_2       = 1,
    INFOFRAME_AVI_DB5PR_3       = 2,
    INFOFRAME_AVI_DB5PR_4       = 3,
    INFOFRAME_AVI_DB5PR_5       = 4,
    INFOFRAME_AVI_DB5PR_6       = 5,
    INFOFRAME_AVI_DB5PR_7       = 6,
    INFOFRAME_AVI_DB5PR_8       = 7,
    INFOFRAME_AVI_DB5PR_9       = 8,
    INFOFRAME_AVI_DB5PR_10      = 9
} hdmi_core_infoframe;

typedef struct _hdmi_core_infoframe_avi {
    u8  db1y_rgb_yuv422_yuv444;             /* yuv format */
    u8  db1a_active_format_off_on;          /* active information present */
    u8  db1b_no_vert_hori_verthori;         /* bar info data valid */
    u8  db1s_0_1_2;                         /* scan information */
    u8  db2c_no_itu601_itu709_extented;     /* colorimetry */
    u8  db2m_no_43_169;                     /* picture aspect ratio */
    u8  db2r_same_43_169_149;               /* active format aspect ratio */
    u8  db3itc_no_yes;                      /* IT content */
    u8  db3ec_xvyuv601_xvyuv709;            /* extended colorimetry */
    u8  db3q_default_lr_fr;                 /* quantization range */
    u8  db3sc_no_hori_vert_horivert;        /* Non-uniform picture scaling */
    u8  db4vic_videocode;                   /* video format identification code */
    u8  db5pr_no_2_3_4_5_6_7_8_9_10;        /* pixel repetition factor */
    u8  rsvd[3];
    u16 db6_7_lineendoftop;                 /* line end of top */
    u16 db8_9_linestartofbottom;            /* line start of bottom */
    u16 db10_11_pixelendofleft;             /* pixel end of left */
    u16 db12_13_pixelstartofright;          /* pixel start of right */
} hdmi_core_infoframe_avi;

typedef struct _hdmi_core_packet_enable_repeat {
    u32 mpeg_info_frame_ed;                 /* mpeg info repeat state */
    u32 mpeg_info_frame_repeat;             /* mpeg info repeat on/off */

    u32 audio_packet_ed;                    /* audio info repeat state */
    u32 audio_packet_repeat;                /* audio info repeat on/off */

    u32 spd_info_frame_ed;                  /* spd info repeat state */
    u32 spd_info_frame_repeat;              /* spd info repeat on/off */

    u32 avi_info_frame_ed;                  /* avi info repeat state */
    u32 avi_info_frame_repeat;              /* avi info repeat on/off */

    u32 general_control_packet_ed;          /* general info repeat state */
    u32 general_control_packet_repeat;      /* general info repeat on/off */

    u32 generic_packet_ed;                  /* generic info repeat state */
    u32 generic_packet_repeat;              /* generic info repeat on/off */
} hdmi_core_packet_enable_repeat;

typedef enum _hdmi_stereo_channel {
    HDMI_STEREO_NOCHANNEL     = 0,  /* 0 stereo channel */
    HDMI_STEREO_ONECHANNELS   = 1,  /* 1 stereo channel */
    HDMI_STEREO_TWOCHANNELS   = 2,  /* 2 stereo channel */
    HDMI_STEREO_THREECHANNELS = 3,  /* 3 stereo channel */
    HDMI_STEREO_FOURCHANNELS  = 4   /* 4 stereo channel */
} hdmi_stereo_channel;

/* cea code */
typedef enum _hdmi_cea_code {
    HDMI_CEA_CODE_00 = 0x0,
    HDMI_CEA_CODE_01 = 0x1,
    HDMI_CEA_CODE_02 = 0x2,
    HDMI_CEA_CODE_03 = 0x3,
    HDMI_CEA_CODE_04 = 0x4,
    HDMI_CEA_CODE_05 = 0x5,
    HDMI_CEA_CODE_06 = 0x6,
    HDMI_CEA_CODE_07 = 0x7,
    HDMI_CEA_CODE_08 = 0x8,
    HDMI_CEA_CODE_09 = 0x9,
    HDMI_CEA_CODE_0A = 0xA,
    HDMI_CEA_CODE_0B = 0xB,
    HDMI_CEA_CODE_0C = 0xC,
    HDMI_CEA_CODE_0D = 0xD,
    HDMI_CEA_CODE_0E = 0xE,
    HDMI_CEA_CODE_0F = 0xF,
    HDMI_CEA_CODE_10 = 0x10,
    HDMI_CEA_CODE_11 = 0x11,
    HDMI_CEA_CODE_12 = 0x12,
    HDMI_CEA_CODE_13 = 0x13,
    HDMI_CEA_CODE_14 = 0x14,
    HDMI_CEA_CODE_15 = 0x15,
    HDMI_CEA_CODE_16 = 0x16,
    HDMI_CEA_CODE_17 = 0x17,
    HDMI_CEA_CODE_18 = 0x18,
    HDMI_CEA_CODE_19 = 0x19,
    HDMI_CEA_CODE_1A = 0x1A,
    HDMI_CEA_CODE_1B = 0x1B,
    HDMI_CEA_CODE_1C = 0x1C,
    HDMI_CEA_CODE_1D = 0x1D,
    HDMI_CEA_CODE_1E = 0x1E,
    HDMI_CEA_CODE_1F = 0x1F,
    HDMI_CEA_CODE_20 = 0x20,
    HDMI_CEA_CODE_21 = 0x21,
    HDMI_CEA_CODE_22 = 0x22,
    HDMI_CEA_CODE_23 = 0x23,
    HDMI_CEA_CODE_24 = 0x24,
    HDMI_CEA_CODE_25 = 0x25,
    HDMI_CEA_CODE_26 = 0x26
} hdmi_cea_code;

typedef enum _hdmi_iec_format {
    HDMI_AUDIO_FORMAT_LPCM = 0, /* audio format is Linear PCM */
    HDMI_AUDIO_FORMAT_IEC  = 1  /* audio format is IEC PCM */
} hdmi_iec_format;

typedef enum _hdmi_audio_justify {
    HDMI_AUDIO_JUSTIFY_LEFT  = 0,   /* audio justify is left */
    HDMI_AUDIO_JUSTIFY_RIGHT = 1    /* audio justify is right */
} hdmi_audio_justify;

typedef enum _hdmi_sample_order {
    HDMI_SAMPLE_RIGHT_FIRST = 0,    /* sample right channel first */
    HDMI_SAMPLE_LEFT_FIRST  = 1     /* sample left channel first */
} hdmi_sample_order;

typedef enum _hdmi_sample_perword {
    HDMI_ONEWORD_ONE_SAMPLE  = 0,   /* one sample in one word */
    HDMI_ONEWORD_TWO_SAMPLES = 1    /* two samples in one word */
} hdmi_sample_perword;

typedef enum _hdmi_sample_size {
    HDMI_SAMPLE_16BITS = 0,         /* sample size is 16 bits */
    HDMI_SAMPLE_20BITS,               /* sample size is 20 bits */
    HDMI_SAMPLE_24BITS                /* sample size is 24 bits */
} hdmi_sample_size;

typedef enum _hdmi_block_start_end {
    HDMI_BLOCK_STARTEND_ON  = 0,    /* block start end is on */
    HDMI_BLOCK_STARTEND_OFF = 1     /* block start end is off */
} hdmi_block_start_end;

typedef struct _hdmi_audio_format {
    hdmi_stereo_channel    stereo_channel_enable;   /* stereo channel enable */
    hdmi_cea_code          audio_channel_location;  /* audio channel location */
    hdmi_iec_format        iec;                     /* iec format */
    hdmi_audio_justify     justify;                 /* audio justify */
    hdmi_sample_order      left_before;             /* sample order */
    hdmi_sample_perword    sample_number;           /* sample perword */
    hdmi_sample_size       sample_size;             /* sample size */
    hdmi_block_start_end   block_start_end;         /* block start end */
} hdmi_audio_format;

typedef enum _hdmi_packing_mode {
    HDMI_PACK_10b_RGB_YUV444        = 0,
    HDMI_PACK_24b_RGB_YUV444_YUV422 = 1,
    HDMI_PACK_ALREADYPACKED         = 7
} hdmi_packing_mode;

typedef enum _hdmi_deep_color_mode {
    HDMI_DEEP_COLOR_24BIT = 0,  /* deep color is 24 bit */
    HDMI_DEEP_COLOR_30BIT = 1,  /* deep color is 30 bit */
    HDMI_DEEP_COLOR_36BIT = 2   /* deep color is 36 bit */
} hdmi_deep_color_mode;

typedef enum _hdmi_range {
    HDMI_LIMITED_RANGE = 0,     /* hdmi is limited range */
    HDMI_FULL_RANGE    = 1,     /* hdmi is full range */
} hdmi_range;

typedef struct _hdmi_s3d_config {
    int structure;          /* 3d structure */
    int s3d_ext_data;       /* 3d extend data */
} hdmi_s3d_config;

typedef struct _hdmi_config {
    u16 ppl;            /* pixel per line */
    u16 lpp;            /* line per panel */
    u32 pixel_clock;    /* pixel clock */
    u16 hsw;            /* Horizontal synchronization pulse width */
    u16 hfp;            /* Horizontal front porch */
    u16 hbp;            /* Horizontal back porch */
    u16 vsw;            /* Vertical synchronization pulse width */
    u16 vfp;            /* Vertical front porch */
    u16 vbp;            /* Vertical back porch */
    u16 interlace;      /* whether resolution is interlace */
    u16 h_pol;          /* Horizontal polarity */
    u16 v_pol;          /* Vertical polarity */
    u16 video_format;               /* timing code */
    u16 deep_color;                 /* deep color */
    u16 s3d_structure;              /* Frame Structure for the S3D Frame */
    hdmi_core_hdmi_dvi hdmi_dvi;    /* hdmi mode */
    bool supports_ai;               /* whether supports ai */
    bool has_vcdb;                  /*whether has video capability data block*/
    int vsi_enabled;                /* Vender Specific InfoFrame enabled/disabled */
    u16 subsamp_pos;                /* Subsampling used in Vendor Specific Infoframe */
    u16 rsved;
} hdmi_config;

typedef enum _hdmi_core_if_fs {
    IF_FS_NO     = 0x0,     /* audio fs is indicated */
    IF_FS_32000  = 0x1,     /* audio fs is    32 kHz */
    IF_FS_44100  = 0x2,     /* audio fs is  44.1 kHz */
    IF_FS_48000  = 0x3,     /* audio fs is    48 kHz */
    IF_FS_88200  = 0x4,     /* audio fs is  88.2 kHz */
    IF_FS_96000  = 0x5,     /* audio fs is    96 kHz */
    IF_FS_176400 = 0x6,     /* audio fs is 176.4 kHz */
    IF_FS_192000 = 0x7      /* audio fs is   192 kHz */
} hdmi_core_if_fs;

typedef enum _hdmi_core_if_sample_size {
    IF_NO_PER_SAMPLE    = 0x0,  /* no sample size */
    IF_16BIT_PER_SAMPLE = 0x1,  /* 16 bit per sample size */
    IF_20BIT_PER_SAMPLE = 0x2,  /* 20 bit per sample size */
    IF_24BIT_PER_SAMPLE = 0x3   /* 24 bit per sample size */
} hdmi_core_if_sample_size;

typedef enum _hdmi_i2s_chst_audio_max_word_length {
    I2S_CHST_WORD_MAX_20 = 0,   /* max word length is 20 */
    I2S_CHST_WORD_MAX_24 = 1,   /* max word length is 24 */
} hdmi_i2s_chst_audio_max_word_length;

/* The word length depends on how the max word length is set.
 * Therefore, some values are duplicated. */
typedef enum _hdmi_i2s_chst_audio_word_length {
    I2S_CHST_WORD_NOT_SPECIFIED = 0x0,
    I2S_CHST_WORD_16_BITS       = 0x1,
    I2S_CHST_WORD_17_BITS       = 0x6,
    I2S_CHST_WORD_18_BITS       = 0x2,
    I2S_CHST_WORD_19_BITS       = 0x4,
    I2S_CHST_WORD_20_BITS_20MAX = 0x5,
    I2S_CHST_WORD_20_BITS_24MAX = 0x1,
    I2S_CHST_WORD_21_BITS       = 0x6,
    I2S_CHST_WORD_22_BITS       = 0x2,
    I2S_CHST_WORD_23_BITS       = 0x4,
    I2S_CHST_WORD_24_BITS       = 0x5,
} hdmi_i2s_chst_audio_word_length;

typedef enum _hdmi_i2s_in_length {
    I2S_IN_LENGTH_NA = 0x0,
    I2S_IN_LENGTH_16 = 0x2,
    I2S_IN_LENGTH_17 = 0xC,
    I2S_IN_LENGTH_18 = 0x4,
    I2S_IN_LENGTH_19 = 0x8,
    I2S_IN_LENGTH_20 = 0xA,
    I2S_IN_LENGTH_21 = 0xD,
    I2S_IN_LENGTH_22 = 0x5,
    I2S_IN_LENGTH_23 = 0x9,
    I2S_IN_LENGTH_24 = 0xb,
} hdmi_i2s_in_length;

typedef enum _hdmi_core_av_csc {
    RGB        = 0x0,   /* color space is rgb */
    RGB_TO_YUV = 0x1,   /* color space is from rgb to yuv */
    YUV_TO_RGB = 0x2    /* color space is from yuv to rgb */
} hdmi_core_av_csc;

typedef struct _hw_audio_configure {
    hdmi_core_fs   fs;              /* Fs Sampling Frequency */
    u32  n;                         /* N Value for audio clock regeneration method */
    u32  cts;                       /* CTS Value for audio clock regeneration method */
    u32  aud_par_busclk;            /* audio bus clock */
    u32  audiotype;                 /* compressed */
    bool bsio;                      /* sio input */
    hdmi_core_layout   layout;      /* Audio packet header layout indicator; */
                                    /* 0x0 = Layout 0 (2-channel); 0x1 = Layout 1 (up to 8 channels)*/
    hdmi_core_cts_mode cts_mode;    /* CTS Source Select (1:SW, 0:HW) */
    hdmi_core_if_fs    if_fs;       /* Sampling Frequency */
    u32  if_channel_number;         /* audio channel number */
    hdmi_core_if_sample_size   if_sample_size;                      /* sample size */
    hdmi_cea_code              if_audio_channel_location;           /* Channel/Speaker allocation */
    hdmi_i2s_chst_audio_max_word_length i2schst_max_word_length;    /* Maximum audio sample word length */
    hdmi_i2s_chst_audio_word_length i2schst_word_length;            /* Audio sample word length */
    hdmi_i2s_in_length i2s_in_bit_length;                           /* Number of valid bits in the input I2S stream. */
    hdmi_audio_justify i2s_justify;                                 /* audio justify */
} hw_audio_configure;

/* HDMI power states */
typedef enum _hdmi_power_state {
    HDMI_POWER_OFF  = 0,
    HDMI_POWER_MIN  = 1,    /* minimum power */
    HDMI_POWER_FULL = 2,    /* full power */
} hdmi_power_state;

/* HDMI states */
typedef enum _hdmi_display_state {
    HDMI_DISPLAY_DISABLED = 0,  /* hdmi display disable state */
    HDMI_DISPLAY_ACTIVE,        /* hdmi display active state */
    HDMI_DISPLAY_SUSPENDED,     /* hdmi display suspended state */
    HDMI_DISPLAY_TRANSITION,    /* hdmi display transition state */
} hdmi_display_state;

typedef enum _hdmi_clock {
    HDMI_CLK_HDMI_APB   = 1 << 0,
    HDMI_CLK_EDC1_APB   = 1 << 1,
    HDMI_CLK_EDC1_PIXEL = 1 << 2,
    HDMI_CLK_EDC1_CORE  = 1 << 3,
    HDMI_CLK_EDC1_AXI   = 1 << 4,
} hdmi_clock;

/* hdmi hardware resource */
typedef struct _hdmi_hw_res {
    u32 physical_addr;          /* physical address of MHL */

    /* reg addr */
	u32 base_core;              /* base address of mhl ip core */
	u32 base_tpi;               /* base address of mhl ip core tpi */
	u32 base_phy;               /* base address of mhl ip PHY module */
	u32 base_cbus;              /* base address of mhl ip cbus */

    /* clk */
    struct clk *clk_pclk_hdmi;  /* clock of pclk hdmi, 100M */
    struct clk *clk_pclk_edc1;  /* clock of pclk edc1, 150M */
    struct clk *clk_edc1_core;  /* clock of edc1 core */
    struct clk *clk_edc1_pixel; /* clock of edc1 pixel */
    struct clk *clk_edc1_axi;   /* clock of edc1 axi bus */

    struct regulator *edc_vcc;  /* regulator of edc1*/

    int irq;
} hdmi_hw_res;

extern void hw_core_mute_audio(bool benabled);
extern void hw_enable(hdmi_config *cfg);
extern int get_timings_index(void);
extern int hw_configure_acr(u32 pclk, hdmi_core_fs audio_fs);
extern void hw_configure_audio(hw_audio_configure *audio_cfg);
extern void hw_core_blank_video(bool blank);
extern void  hw_core_power_off(void);
extern void hw_core_power_on(void);
extern void hw_enable_irqs(bool enable);
extern void hw_free_resources(void);
extern int hw_get_resources(struct platform_device *pdev);
/* extern void hw_init_irqs(void); */
extern void hw_phy_power_off(void);
extern void hw_set_phy_full_power(void);
extern void hw_set_phy_low_power(void);
extern void hw_set_core_low_power(void);
extern void hw_set_core_full_power(void);
extern int hw_reconfig(void);
extern void mhl_audio_config_infoframe(hw_audio_configure *audio_cfg);
extern void mhl_audio_config_param(hw_audio_configure *audio_cfg);
extern void update_set_timing_code(int *mode, int * code);
extern void mhl_enable_cfg(void);
extern bool mhl_is_connect(void);
extern void hw_read_write_reg(int mode,int reg_page, int reg_value, int reg_offset);
extern void dump_mhl_reg(void);
extern void hdmi_pw_power_off(void);
extern void hdmi_pw_power_on_full(void);
extern void hdmi_pw_power_on_min(void);
#if USE_HDCP
extern void hw_reconfig_hdcp(bool hdcp_enable);
#endif /* USE_HDCP */
#endif

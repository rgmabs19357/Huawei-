/*
 *****************************************************************************
 *
 * Copyright 2010, Silicon Image, Inc.  All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of: Silicon Image, Inc., 1060
 * East Arques Avenue, Sunnyvale, California 94085
 *****************************************************************************
 */

/*
 *****************************************************************************
 * @file  si_edid.c
 *
 * @brief Implementation of the EDID.
 *
 *****************************************************************************
 */

#include "si_drv_mhl_tx.h"
#include "si_edid.h"
//#include "si_hdcp.h"
#include "si_infoframe.h"
#include "si_mhl_defs.h"
#include "si_mhl_hw.h"
#include "si_mhl_main.h"
#include "si_mhl_tx.h"
#include "si_reg_access.h"

#include "k3_fb.h"

bool SiiDrvDoEDID_Checksum(uint8_t *Block);

extern hdmi_device hdmi;
extern mhlTx_config_t g_PlumTxConfig;
extern uint8_t edid[HDMI_EDID_MAX_LENGTH];

/* edid */
static u8 edid_header[8] = {0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0};

/* All supported timing values that  supports */
static hdmi_video_timings all_timings_direct[] = {
    { 640,  480,  25200,  96,  16,  48, 2, 10, 33, 60}, /* 1     -- 0 */
    {1280,  720,  74250,  40, 440, 220, 5,  5, 20, 50}, /* 19 */
    {1280,  720,  74250,  40, 110, 220, 5,  5, 20, 60}, /* 4 */
    { 720,  480,  27000,  62,  16,  60, 6,  9, 30, 60}, /* 2,3 */
    {2880,  576, 108000, 256,  48, 272, 5,  5, 39, 60}, /* 37 */
    {1440,  240,  27000, 124,  38, 114, 3,  4, 15, 60}, /* 6,7   -- 5 */
    {1440,  288,  27000, 126,  24, 138, 3,  2, 19, 50}, /* 21,22 */
    {1920,  540,  74250,  44, 528, 148, 5,  2, 15, 50}, /* 20 */
    {1920,  540,  74250,  44,  88, 148, 5,  2, 15, 60}, /* 5 */
    {1920, 1080, 148500,  44,  88, 148, 5,  4, 36, 60}, /* 16 */
    { 720,  576,  27000,  64,  12,  68, 5,  5, 39, 50}, /* 17,18 -- 10 */
    {1440,  576,  54000, 128,  24, 136, 5,  5, 39, 50}, /* 29,30 */
    {1920, 1080, 148500,  44, 528, 148, 5,  4, 36, 50}, /* 31 */
    {2880,  480, 108000, 248,  64, 240, 6,  9, 30, 60}, /* 35,36 */
    {1920, 1080,  74250,  44, 638, 148, 5,  4, 36, 24}, /* 32 */
    {1920, 1080,  74250,  44, 528, 148, 5,  4, 36, 25}, /* 33 */
    {1920, 1080,  74250,  44,  88, 148, 5,  4, 36, 30}, /* 34 */
    { 720,  480,  27030,  62,  16,  60, 6,  9, 30, 60}, /* 3     -- 40 */
    {1440,  240,  27000, 124,  38, 114, 3,  4, 15, 60}, /* 8,9 */
    {1440,  480,  54000, 124,  32, 120, 6,  9, 30, 60}, /* 14,15 */
    {1440,  288,  27000, 126,  24, 138, 3,  2, 19, 50}, /* 23,24 */
    {1280,  720, 148500,  40, 400, 220, 5,  5, 20, 100}, /* 41 */
    { 720,  576,  54000,  64,  12,  68, 5,  5, 39, 100}, /* 42,43 -- 45 */
    {1280,  720, 148350,  40, 110, 220, 5,  5, 20, 120}, /* 47 */
    { 720,  480,  54000,  62,  16,  60, 6,  1, 30, 120}, /* 48,49 */
    { 720,  576, 108000,  64,  12,  68, 5,  5, 39, 200}, /* 52,53 */
    { 720,  480, 108000,  62,  16,  60, 6,  9, 30, 240}  /* 56,57 */
    /* Vesa from here */
    ,
    { 640,  350,  31500,  64,  32,  96, 3, 32, 60, 85}, /*  1, 640 x 350 @ 85Hz; */
    { 640,  400,  31500,  64,  32,  96, 3,  1, 41, 85}, /*  2, 640 x 400 @ 85Hz; */
    { 720,  400,  35500,  72,  36, 108, 3,  1, 42, 85}, /*  3, 720 x 400 @ 85Hz; */
    { 640,  480,  25175,  96,  16,  48, 2, 10, 33, 60}, /*  4, 640 x 480 @ 60Hz; -- 30 */
    { 640,  480,  31500,  40,  128, 128,3,  9, 28, 72}, /*  5, 640 x 480 @ 72Hz; */
    { 640,  480,  31500,  64,  24, 128, 3,  9, 28, 75}, /*  6, 640 x 480 @ 75Hz; */
    { 640,  480,  36000,  56,  24, 128, 3,  9, 25, 85}, /*  7, 640 x 480 @ 85Hz; */
    { 800,  600,  36000,  72,  24, 128, 2,  1, 22, 56}, /*  8, 800 x 600 @ 56Hz; */
    { 800,  600,  40000, 128,  40,  88, 4,  1, 23, 60}, /*  9, 800 x 600 @ 60Hz; -- 35 */
    { 800,  600,  50000, 120,  56,  64, 6, 37, 23, 72}, /* 10, 800 x 600 @ 72Hz; */
    { 800,  600,  49500,  80,  16, 160, 3,  1, 21, 75}, /* 11, 800 x 600 @ 75Hz; */
    { 800,  600,  56250,  64,  32, 152, 3,  1, 27, 85}, /* 12, 800 x 600 @ 85Hz; */
    { 800,  600,  73250,  32,  48,  80, 3,  4, 29, 120}, /* 13, 800 x 600 @ 120Hz;*/
    { 848,  480,  33750, 112,  16, 112, 8,  6, 23, 60}, /* 14, 848 x 480 @ 60Hz; -- 40 */
    {1024,  768,  44900, 176,   8,  56, 4,  0, 20, 43}, /* 15, 1024 x 768 @ 43Hz */
    {1024,  768,  65000, 136,  24, 160, 6,  3, 29, 60}, /* 16, 1024 x 768 @ 60Hz */
    {1024,  768,  75000, 136,  24, 144, 6,  3, 19, 70}, /* 17, 1024 x 768 @ 70Hz */
    {1024,  768,  78750,  96,  16, 176, 3,  1, 28, 75}, /* 18, 1024 x 768 @ 75Hz */
    {1024,  768,  94500,  96,  48, 208, 3,  1, 36, 85}, /* 19, 1024 x 768 @ 85Hz -- 45 */
    {1024,  768, 115500,  32,  48,  80, 4,  3, 38, 120}, /* 20, 1024 x 768 @ 120Hz */
    {1152,  864, 108000, 128,  64, 256, 3,  1, 32, 75}, /* 21, 1152 x 864 @ 75Hz; */
    {1280,  768,  68250,  32,  48,  80, 7,  3, 12, 60}, /* 22, 1280 x 768 @ 60Hz CVT */
    {1280,  768,  79500, 128,  64, 192, 7,  3, 20, 60}, /* 23, 1280 x 768 @ 60Hz */
    {1280,  768, 102250, 128,  80, 208, 7,  3, 27, 75}, /* 24, 1280 x 768 @ 75Hz  -- 50 */
    {1280,  768, 117500, 136,  80, 216, 7,  3, 31, 85}, /* 25, 1280 x 768 @ 85Hz */
    {1280,  768, 140250,  32,  48,  80, 7,  3, 35, 120}, /* 26, 1280 x 768 @ 120Hz */
    {1280,  800,  71000,  32,  48,  80, 6,  3, 14, 60}, /* 27, 1280 x 800 @ 60Hz CVT */
    {1280,  800,  83500, 128,  72, 200, 6,  3, 22, 60}, /* 28, 1280 x 800 @ 60Hz */
    {1280,  800, 106500, 128,  80, 208, 6,  3, 29, 75}, /* 29, 1280 x 800 @ 75Hz  -- 55 */
    {1280,  800, 122500, 136,  80, 216, 6,  3, 34, 85}, /* 30, 1280 x 800 @ 85Hz */
    {1280,  800, 146250,  32,  48,  80, 6,  3, 38, 120}, /* 31, 1280 x 800 @ 120Hz */
    {1280,  960, 108000, 112,  96, 312, 3,  1, 36, 60}, /* 32, 1280 x 960 @ 60Hz */
    {1280,  960, 148500, 160,  64, 224, 3,  1, 47, 85}, /* 33, 1280 x 960 @ 85Hz */
    {1280,  960, 175500,  32,  48,  80, 4,  3, 50, 120}, /* 34, 1280 x 960 @ 120Hz -- 60*/
    {1280, 1024, 108000, 112,  48, 248, 3,  1, 38, 60}, /* 35, 1280 x 1024 @ 60Hz */
    {1280, 1024, 135000, 144,  16, 248, 3,  1, 38, 75}, /* 36, 1280 x 1024 @ 75Hz */
    {1280, 1024, 157500, 160,  64, 224, 3,  1,  4, 85}, /* 37, 1280 x 1024 @ 85Hz */
    {1280, 1024, 187250,  32,  48,  80, 7,  3, 44, 120}, /* 38, 1280 x 1024 @ 120Hz */
    {1360,  768,  85500, 112,  64, 256, 6,  3, 18, 60}, /* 39, 1360 x 768 @ 60Hz  -- 65 */
    {1360,  768, 148250,  32,  48,  80, 5,  3, 37, 120}, /* 40, 1360 x 768 @ 120Hz */
    {1400, 1050, 101000,  32,  48,  80, 4,  3, 23, 60}, /* 41, 1400 x 1050 @ 60Hz */
    {1400, 1050, 121750, 144,  88, 232, 4,  3, 32, 60}, /* 42, 1400 x 1050 @ 60Hz */
    {1400, 1050, 156000, 144, 104, 248, 4,  3, 42, 75}, /* 43, 1400 x 1050 @ 75Hz */
    {1400, 1050, 179500, 152, 104, 256, 4,  3, 48, 85}, /* 44, 1400 x 1050 @ 85Hz -- 70 */
    {1400, 1050, 208000,  32,  48,  80, 4,  3, 55, 120}, /* 45, 1400 x 1050 @ 120Hz */
    {1440,  900,  88750,  32,  48,  80, 6,  3, 17, 60}, /* 46, 1440 x 900 @ 60Hz CVT */
    {1440,  900, 106500, 152,  80, 232, 6,  3, 25, 60}, /* 47, 1440 x 900 @ 60Hz */
    {1440,  900, 136750, 152,  96, 248, 6,  3, 33, 75}, /* 48, 1440 x 900 @ 75Hz; */
    {1440,  900, 157000, 152, 104, 256, 6,  3, 39, 85}, /* 49, 1440 x 900 @ 85Hz; -- 75 */
    {1440,  900, 182750,  32,  48,  80, 6,  3, 44, 120}, /* 50, 1440 x 900 @ 120Hz; */
    {1600, 1200, 162000, 304,  64, 304, 3,  1, 46, 60}, /* 51, 1600 x 1200 @ 60Hz */
    {1600, 1200, 175500, 192,  64, 304, 3,  1, 46, 65}, /* 52, 1600 x 1200 @ 65Hz */
    {1600, 1200, 189000, 192,  64, 304, 3,  1, 46, 70}, /* 53, 1600 x 1200 @ 70Hz */
    {1600, 1200, 202500, 192,  64, 304, 3,  1, 46, 75}, /* 54, 1600 x 1200 @ 75Hz -- 80 */
    {1600, 1200, 229500, 192,  64, 304, 3,  1, 46, 85}, /* 55, 1600 x 1200 @ 85Hz */
    {1600, 1200, 268250,  32,  48,  80, 4,  3, 64, 120}, /* 56, 1600 x 1200 @ 120Hz */
    {1680, 1050, 119000,  32,  48,  80, 6,  3, 21, 60}, /* 57, 1680 x 1050 @ 60Hz CVT */
    {1680, 1050, 146250, 176, 104, 280, 6,  3, 30, 60}, /* 58, 1680 x 1050 @ 60Hz */
    {1680, 1050, 187000, 176, 120, 296, 6,  3, 40, 75}, /* 59, 1680 x 1050 @ 75Hz -- 85 */
    {1680, 1050, 214750, 176, 128, 304, 6,  3, 46, 85}, /* 60, 1680 x 1050 @ 85Hz */
    {1680, 1050, 245500,  32,  48,  80, 6,  3, 53, 120}, /* 61, 1680 x 1050 @ 120Hz */
    {1920, 1200, 154000,  32,  48,  80, 6,  3, 26, 60}, /* 68, 1920 x 1200 @ 60Hz; CVT */
    {1920, 1200, 193250, 200, 136, 336, 6,  3, 36, 60}, /* 69, 1920 x 1200 @ 60Hz; */
    {1920, 1200, 245250, 208, 136, 344, 6,  3, 46, 75}, /* 70, 1920 x 1200 @ 75Hz -- 90 */
    {1920, 1200, 281250, 208, 144, 352, 6,  3, 53, 85}, /* 71, 1920 x 1200 @ 85Hz; */
    {1920, 1200, 317000,  32,  48,  80, 6,  3, 62, 120}, /* 72, 1920 x 1200 @ 120Hz; */
    {1366,  768,  85500, 143,  70, 213, 3,  3, 24, 0}, /* 81 */
    {1920, 1080, 148500,  44,  88, 148, 5,  4, 36, 60}, /* 82 == CEA 16*/
    {1280,  720,  74250,  40, 110, 220, 5,  5, 20, 60}, /* 85 == CEA 4 -- 95 */
    /* supported 3d timings UNDEROVER full frame */
    {1280, 1470, 148350,  40, 110, 220, 5,  5, 20, 0},
    {1280, 1470, 148500,  40, 110, 220, 5,  5, 20, 0},
    {1280, 1470, 148500,  40, 440, 220, 5,  5, 20, 0}
};

/* Array which maps the timing values with corresponding CEA / VESA code */
//todo
//static int code_index[ARRAY_SIZE(all_timings_direct)] = {
static int code_index[] = {
    /* <--0 CEA 26--> */
    /*      L2      L4      L6      L8   */
     1, 19,  4,  2, 37,  6, 21, 20,  5, 16,
    17, 29, 31, 35, 32, 33, 34,  3,  8, 14,
    23, 41, 42, 47, 48, 52, 56,
    /*   <--27 VESA 95-->   */   1,  2,  3,
     4,  5,  6,  7,  8,  9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26 ,27 ,28, 29, 30, 31, 32, 33,
    34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
    44, 45, 46, 47, 48, 49, 50, 51, 52, 53,
    54, 55 ,56, 57, 58, 59, 60, 61, 68, 69,
    70, 71, 72, 81, 82, 85,
    /* <--96 3D 98--> */
     4,  4, 19
};

/* Mapping the Timing values with the corresponding Vsync and Hsync polarity */
//todo
//static hdmi_hvsync_pol hvpol_mapping[ARRAY_SIZE(all_timings_direct)] = {
static hdmi_hvsync_pol hvpol_mapping[] = {
    /*L0              L2              L4              L6              L8         */
    {0, 0}, {1, 1}, {1, 1}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 1}, {1, 1}, {1, 1},
    {0, 0}, {0, 0}, {1, 1}, {0, 0}, {1, 1}, {1, 1}, {1, 1}, {0, 0}, {0, 0}, {0, 0},
    {0, 0}, {1, 1}, {0, 0}, {1, 1}, {0, 0}, {0, 0}, {0, 0},
    /*                       VESA                    */     {0, 0}, {1, 1}, {1, 1},
    {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {0, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 1},
    {1, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 1}, {1, 0},
                                                            {0, 0}, {1, 1}, {1, 1},
    {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {0, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 1},
    {1, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 1}, {1, 1},
    {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {0, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 1},
    {1, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {1, 1}, {1, 0}, {0, 0}, {1, 1}, {1, 1},
    {1, 0}, {1, 0}, {1, 1}, {1, 1}, {1, 1}, {0, 0},
    /*                   3D                   */    {1, 1}, {1, 1}, {1, 1}
};

/* Map CEA code to the corresponding timing values (10 entries/line) */
static int code_cea[60] = {
    /*      L2      L4      L6      L8   */
    -1,  0,  3,  3,  2, -1, -1, -1, 18, 18,
    -1, -1, -1, -1, 19, 19,  9, 10, 10,  1,
    -1, -1, -1, 20, 20, -1, -1, -1, -1, 11,
    11, 12, 14, 15, 16, -1, -1, -1, -1, -1,
    -1, 21, 22, 22, -1, -1, -1, 23, 24, 24,
    -1, -1, 25, 25, -1, -1, 26, 26, -1, -1
};

/* Map CEA code to the corresponding 3D timing values */
static int s3d_code_cea[60] = {
    /*      L2      L4      L6      L8   */
    -1, -1, -1, -1, 97, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 98,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

/* Map VESA code to the corresponding timing values */
static int code_vesa[86] = {
    /*      L2      L4      L6      L8   */
    -1, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
    66, 67, 68, 69, 70, 71, 72, 73, 74, 75,
    76, 77, 78, 79, 80, 81, 82, 83, 84, 85,
    86, 87, -1, -1, -1, -1, -1, -1, 88, 89,
    90, 91, 92, -1, -1, -1, -1, -1, -1, -1,
    -1, 93, 94, -1, -1, 95
};

static int timing_order[] = {
    HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3,
    HDMI_EDID_EX_VIDEO_720x480p_60Hz_4_3,
    HDMI_EDID_EX_VIDEO_720x480p_60Hz_16_9,
    HDMI_EDID_EX_VIDEO_720x576p_50Hz_4_3,
    HDMI_EDID_EX_VIDEO_720x576p_50Hz_16_9,
    HDMI_EDID_EX_VIDEO_1280x720p_50Hz_16_9,
    HDMI_EDID_EX_VIDEO_1280x720p_60Hz_16_9,
    HDMI_EDID_EX_VIDEO_1920x1080p_24Hz_16_9,
    HDMI_EDID_EX_VIDEO_1920x1080p_25Hz_16_9,
    HDMI_EDID_EX_VIDEO_1920x1080p_30Hz_16_9/*,
    HDMI_EDID_EX_VIDEO_1920x1080p_50Hz_16_9,
    HDMI_EDID_EX_VIDEO_1920x1080p_60Hz_16_9*/
};

static int vesa_timing_order[] = {
    HDMI_EDID_VESA_VIDEO_640x350p_85Hz_4_3, /* -- 0 -- */
    HDMI_EDID_VESA_VIDEO_640x400p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_720x400p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_640x480p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_640x480p_72Hz_4_3,
    HDMI_EDID_VESA_VIDEO_640x480p_75Hz_4_3, /* -- 5 -- */
    HDMI_EDID_VESA_VIDEO_640x480p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_800x600p_56Hz_4_3,
    HDMI_EDID_VESA_VIDEO_800x600p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_800x600p_72Hz_4_3,
    HDMI_EDID_VESA_VIDEO_800x600p_75Hz_4_3, /* -- 10 -- */
    HDMI_EDID_VESA_VIDEO_800x600p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_848x480p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1024x768p_43Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1024x768p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1280x720p_60Hz_16_9, /* -- 15 -- */
    HDMI_EDID_VESA_VIDEO_1024x768p_70Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1024x768p_75Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1024x768p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1152x864p_75Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1280x768p_60Hz_CVT_16_9, /* -- 20 -- */
    HDMI_EDID_VESA_VIDEO_1280x768p_60Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1280x768p_75Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1280x800p_60Hz_CVT_16_9,
    HDMI_EDID_VESA_VIDEO_1280x800p_60Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1280x800p_75Hz_16_9, /* -- 25 -- */
    HDMI_EDID_VESA_VIDEO_1280x960p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1280x1024p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1360x768p_60Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1400x1050p_60Hz_CVT_4_3,
    HDMI_EDID_VESA_VIDEO_1440x900p_60Hz_CVT_16_9, /* -- 30 -- */
    HDMI_EDID_VESA_VIDEO_1440x900p_60Hz_16_9,    
    HDMI_EDID_VESA_VIDEO_1280x768p_85Hz_16_9,    
    HDMI_EDID_VESA_VIDEO_1280x800p_85Hz_16_9,    
    HDMI_EDID_VESA_VIDEO_1280x960p_85Hz_4_3,    
    HDMI_EDID_VESA_VIDEO_1280x1024p_75Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1280x1024p_85Hz_4_3,    
    HDMI_EDID_VESA_VIDEO_1400x1050p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1400x1050p_75Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1400x1050p_85Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1440x900p_75Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1440x900p_85Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1600x1200p_60Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1600x1200p_65Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1600x1200p_70Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1600x1200p_75Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1600x1200p_80Hz_4_3,
    HDMI_EDID_VESA_VIDEO_1680x1050p_60Hz_CVT_16_9,
    HDMI_EDID_VESA_VIDEO_1680x1050p_60Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1680x1050p_75Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1680x1050p_85Hz_16_9,
    HDMI_EDID_VESA_VIDEO_1920x1080p_60Hz_16_9
};

/*3d supported format of sink*/
static char *s3d_format[] = {
        "HDMI_S3D_FRAME_PACKING",
        "HDMI_S3D_FIELD_ALTERNATIVE",
        "HDMI_S3D_LINE_ALTERNATIVE",
        "HDMI_S3D_SIDE_BY_SIDE_FULL",
        "HDMI_S3D_L_DEPTH",
        "HDMI_S3D_L_DEPTH_GRAPHICS_GRAPHICS_DEPTH",
        "HDMI_S3D_SIDE_BY_SIDE_HALF_FORMAT"
};

static void edid_get_ext_timings_info(int current_descriptor_addrs, u8 *edid ,
                                               hdmi_video_timings *timings);
static void edid_get_video_svds(u8 *edid, int *offset, int *svd_number);
static void edid_get_av_delay(u8 *edid, latency *lat);
static hdmi_cm get_timing_code(hdmi_video_timings *timings);
static bool SiiDrvGetDDC_Access (uint8_t *reg_val);
static void SiiDrvParseBlock_0_TimingDescripors(uint8_t *Data);
static void SiiDrvParseEstablishedTiming(uint8_t *Data);
static void SiiDrvParseStandardTiming(uint8_t *Data);
static bool SiiDrvReleaseDDC(byte SysCtrlRegVal);
static int get_timings_by_index(int mode, int code);


//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   uint8_t SiiDrvParseEDID()
// PURPOSE      :   Extract sink properties from its EDID file and save them in
//                  global structure g_PlumTxConfig.EDID.
// INPUT PARAMS :   Pointer to start of EDID 0
// OUTPUT PARAMS:   None
// GLOBALS USED :   g_PlumTxConfig.EDID
// RETURNS      :   A byte error code to indicates success or error type.
// NOTE         :   Fields that are not supported by the 9022/4 (such as deep
//                  color) were not parsed.
//
//////////////////////////////////////////////////////////////////////////////

uint8_t SiiDrvParseEDID (uint8_t *pEdid, uint8_t *numExt)
{
#if DEBUG_VERSION    
    uint8_t i, j, k;
#endif

    SII_DBG_PRINT("EDID DATA (Segment = 0 Block = 0 Offset = %d):\n", (int)EDID_BLOCK_0_OFFSET);
#if DEBUG_VERSION    
    for (j = 0, i = 0; j < EDID_BLOCK_SIZE; j++)
    {
        k = pEdid[j];
        printk("0x%02X ", (int) k);    //use printk for easy read
        i++;

        if (i == 0x10)
        {
            printk("\n");
            i = 0;
        }
    }
#endif

    SII_DBG_PRINT("\n");

    if (!edid_is_valid_edid(pEdid))
    {
        // first 8 bytes of EDID must be {0, FF, FF, FF, FF, FF, FF, 0}
        SII_DBG_PRINT("EDID -> Incorrect Header\n");
        return EDID_INCORRECT_HEADER;
    }

    if (!SiiDrvDoEDID_Checksum(pEdid))
    {
        // non-zero EDID checksum
        SII_DBG_PRINT("EDID -> Checksum Error\n");
        return EDID_CHECKSUM_ERROR;
    }

    SiiDrvParseBlock_0_TimingDescripors(pEdid);           // Parse EDID Block #0 Desctiptors

    *numExt = pEdid[NUM_OF_EXTEN_ADDR]; // read # of extensions from offset 0x7E of block 0
    SII_DBG_PRINT("EDID -> Num of 861 Extensions = %d\n", (int) *numExt);
    if (!(*numExt))
    {
        // No extensions to worry about
        return EDID_NO_861_EXTENSIONS;
    }

    return (EDID_OK);
}

uint8_t SiiDrvMhlTxReadEdid (void) //UT XU
{
    uint8_t Result = EDID_OK;
    uint8_t NumOfExtensions;
    uint8_t reg_val;

    // If we already have valid EDID data, ship this whole thing
    // Request access to DDC bus from the receiver
    if (SiiDrvGetDDC_Access(&reg_val))
    {
        memset(g_PlumTxConfig.EDID.edidBlockData, 0x00, sizeof(g_PlumTxConfig.EDID.edidBlockData));
        SiiDrvReadBlockEDID(0);

        Result = SiiDrvParseEDID(g_PlumTxConfig.EDID.edidBlockData, &NumOfExtensions);

        if (Result != EDID_OK)
        {
            if (Result == EDID_NO_861_EXTENSIONS)
            {
                SII_DBG_PRINT("EDID -> No 861 Extensions, NOT HDMI Sink device\n");

                /* copy first block raw EDID data to another global data area */
                memcpy(edid, g_PlumTxConfig.EDID.edidBlockData, EDID_BLOCK_SIZE);
            }
            else
            {
                SII_DBG_PRINT("EDID -> Parse FAILED\n");
            }

            g_PlumTxConfig.EDID.HDMI_Sink   = false;
            g_PlumTxConfig.EDID.YCbCr_4_4_4 = false;
            g_PlumTxConfig.EDID.YCbCr_4_2_2 = false;
            g_PlumTxConfig.EDID.CEC_A_B = 0x00;
            g_PlumTxConfig.EDID.CEC_C_D = 0x00;
        }
        else
        {
            // Parse 861 Extensions (short and long descriptors);
            Result = SiiDrvParse861Extensions(NumOfExtensions);
            if (Result != EDID_OK)
            {
                SII_DBG_PRINT("EDID -> Extension Parse FAILED\n");
                // Make it DVI
                g_PlumTxConfig.EDID.HDMI_Sink   = false;
                g_PlumTxConfig.EDID.YCbCr_4_4_4 = false;
                g_PlumTxConfig.EDID.YCbCr_4_2_2 = false;
                g_PlumTxConfig.EDID.CEC_A_B = 0x00;
                g_PlumTxConfig.EDID.CEC_C_D = 0x00;
            }
            else {
                SII_DBG_PRINT("EDID -> Extension Parse ok\n");
                memcpy(edid, g_PlumTxConfig.EDID.edidBlockData, HDMI_EDID_MAX_LENGTH);
            }
        }

        SII_DBG_PRINT("g_PlumTxConfig.EDID.HDMI_Sink = %d\n",
                                                      (int)g_PlumTxConfig.EDID.HDMI_Sink);
        SII_DBG_PRINT("g_PlumTxConfig.EDID.YCbCr_4_4_4 = %d\n",
                                                      (int)g_PlumTxConfig.EDID.YCbCr_4_4_4);
        SII_DBG_PRINT("g_PlumTxConfig.EDID.YCbCr_4_2_2 = %d\n",
                                                      (int)g_PlumTxConfig.EDID.YCbCr_4_2_2);
        SII_DBG_PRINT("g_PlumTxConfig.EDID.CEC_A_B = 0x%x\n", (int)g_PlumTxConfig.EDID.CEC_A_B);
        SII_DBG_PRINT("g_PlumTxConfig.EDID.CEC_C_D = 0x%x\n", (int)g_PlumTxConfig.EDID.CEC_C_D);

        // Host must release DDC bus once it is done reading EDID
        if (!SiiDrvReleaseDDC(reg_val))
        {
            SII_WRN_PRINT("EDID -> DDC bus release failed\n");
            return EDID_DDC_BUS_RELEASE_FAILURE;
        }
    }
    else
    {
        SII_WRN_PRINT("EDID -> DDC bus request failed\n");
        return EDID_DDC_BUS_REQ_FAILURE;
    }

    return Result;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvParseBlock_0_TimingDescripors()
//
// PURPOSE      :   Parse EDID Block 0 timing descriptors per EEDID 1.3
//                  standard. printf() values to screen.
//
// INPUT PARAMS :   Pointer to the 128 byte array where the data read from EDID
//                  Block0 is stored.
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   Void
//
//////////////////////////////////////////////////////////////////////////////
static void SiiDrvParseBlock_0_TimingDescripors(uint8_t *Data)
{
    uint8_t i;
    uint8_t Offset;

    SiiDrvParseEstablishedTiming(Data);
    SiiDrvParseStandardTiming(Data);

    for (i = 0; i < NUM_OF_DETAILED_DESCRIPTORS; i++)
    {
        Offset = DETAILED_TIMING_OFFSET + (LONG_DESCR_LEN * i);
        SiiDrvParseDetailedTiming(Data, Offset, EDID_BLOCK_0);
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   byte SiiDrvParse861Extensions()
//
// PURPOSE      :   Parse CEA-861 extensions from EDID ROM (EDID blocks beyond
//                  block #0). Save short descriptors in global structure
//                  g_PlumTxConfig.EDID. printf() long descriptors to the screen.
//
// INPUT PARAMS :   The number of extensions in the EDID being parsed
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   EDID_PARSED_OK if EDID parsed correctly. Error code if failed.
//
// NOTE         :   Fields that are not supported by the 9022/4 (such as deep
//                  color) were not parsed.
//
//////////////////////////////////////////////////////////////////////////////

uint8_t SiiDrvParse861Extensions(uint8_t NumOfExtensions)//UT XU
{
#if DEBUG_VERSION
    byte i, j, k;
#endif
    byte ErrCode;
    byte Block  = 0;

    g_PlumTxConfig.EDID.HDMI_Sink = false;

    do
    {
        Block++;
        SII_DBG_PRINT("EDID HW Assist: Read EDID block number 0x%02X\n", (int)Block);

        // read block n
        SiiDrvReadBlockEDID(Block);

#if DEBUG_VERSION
        for (j = 0, i = 0; j < 128; j++)
        {
            k = g_PlumTxConfig.EDID.edidBlockData[Block * EDID_BLOCK_SIZE + j];

            /* use printk for easy print */
            printk("0x%02X ", (int) k);
            i++;

            if (i == 0x10)
            {
                printk("\n");
                i = 0;
            }
        }
#endif

        if ((NumOfExtensions > 1) && (Block == 1))
        {
            continue;
        }

        ErrCode = SiiDrvParse861ShortDescriptors(g_PlumTxConfig.EDID.edidBlockData + Block * EDID_BLOCK_SIZE);

        if (ErrCode != EDID_SHORT_DESCRIPTORS_OK)
        {
            return ErrCode;
        }

        ErrCode = SiiDrvParse861LongDescriptors(g_PlumTxConfig.EDID.edidBlockData + Block * EDID_BLOCK_SIZE);
        if (ErrCode != EDID_LONG_DESCRIPTORS_OK)
        {
            return ErrCode;
        }
    } while (Block < NumOfExtensions);

    return EDID_OK;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   byte SiiDrvParse861LongDescriptors()
//
// PURPOSE      :   Parse CEA-861 extension long descriptors of the EDID block
//                  passed as a parameter and printf() them to the screen.
//                  g_PlumTxConfig.EDID.
//
// INPUT PARAMS :   A pointer to the EDID block being parsed
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   An error code if no long descriptors found; EDID_PARSED_OK
//                  if descriptors found.
//
//////////////////////////////////////////////////////////////////////////////
uint8_t SiiDrvParse861LongDescriptors(uint8_t *Data)
{
    uint8_t LongDescriptorsOffset;
    uint8_t DescriptorNum = 1;

    LongDescriptorsOffset = Data[LONG_DESCR_PTR_IDX];   // EDID block offset 2 holds the offset

    if (!LongDescriptorsOffset)                         // per CEA-861-D, table 27
    {
        SII_DBG_PRINT("EDID -> No Detailed Descriptors\n");
        return EDID_NO_DETAILED_DESCRIPTORS;
    }

    // of the 1st 18-byte descriptor
    while (LongDescriptorsOffset + LONG_DESCR_LEN < EDID_BLOCK_SIZE)
    {
        SII_DBG_PRINT("Parse Results - CEA-861 Long Descriptor #%d:\n", (int) DescriptorNum);
        SII_DBG_PRINT("===========================================================\n");

        if (!SiiDrvParseDetailedTiming(Data, LongDescriptorsOffset, EDID_BLOCK_2_3))
        {
            break;
        }

        LongDescriptorsOffset += LONG_DESCR_LEN;
        DescriptorNum++;
    }

    return EDID_LONG_DESCRIPTORS_OK;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   bool SiiDrvDoEDID_Checksum()
//
// PURPOSE      :   Calculte checksum of the 128 byte block pointed to by the
//                  pointer passed as parameter
//
// INPUT PARAMS :   Pointer to a 128 byte block whose checksum needs to be
//                  calculated
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   TRUE if chcksum is 0. FALSE if not.
//
//////////////////////////////////////////////////////////////////////////////

bool SiiDrvDoEDID_Checksum(uint8_t *Block)
{
    uint8_t i;
    uint8_t CheckSum = 0;

    for (i = 0; i < EDID_BLOCK_SIZE; i++)
    {
        CheckSum += Block[i];
    }

    if (CheckSum)
    {
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvParseEstablishedTiming()
//
// PURPOSE      :   Parse the established timing section of EDID Block 0 and
//                  print their decoded meaning to the screen.
//
// INPUT PARAMS :   Pointer to the array where the data read from EDID
//                  Block0 is stored.
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   Void
//
//////////////////////////////////////////////////////////////////////////////
static void SiiDrvParseEstablishedTiming(uint8_t *Data)
{
    SII_DBG_PRINT("Parsing Established Timing:\n");
    SII_DBG_PRINT("===========================\n");

    // Parse Established Timing Byte #0

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT7)
    {
        SII_DBG_PRINT("720 x 400 @ 70Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT6)
    {
        SII_DBG_PRINT("720 x 400 @ 88Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT5)
    {
        SII_DBG_PRINT("640 x 480 @ 60Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT4)
    {
        SII_DBG_PRINT("640 x 480 @ 67Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT3)
    {
        SII_DBG_PRINT("640 x 480 @ 72Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT2)
    {
        SII_DBG_PRINT("640 x 480 @ 75Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT1)
    {
        SII_DBG_PRINT("800 x 600 @ 56Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX] & BIT0)
    {
        SII_DBG_PRINT("800 x 400 @ 60Hz\n");
    }

    // Parse Established Timing Byte #1:

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT7)
    {
        SII_DBG_PRINT("800 x 600 @ 72Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT6)
    {
        SII_DBG_PRINT("800 x 600 @ 75Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT5)
    {
        SII_DBG_PRINT("832 x 624 @ 75Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT4)
    {
        SII_DBG_PRINT("1024 x 768 @ 87Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT3)
    {
        SII_DBG_PRINT("1024 x 768 @ 60Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT2)
    {
        SII_DBG_PRINT("1024 x 768 @ 70Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT1)
    {
        SII_DBG_PRINT("1024 x 768 @ 75Hz\n");
    }

    if (Data[ESTABLISHED_TIMING_INDEX + 1] & BIT0)
    {
        SII_DBG_PRINT("1280 x 1024 @ 75Hz\n");
    }

    // Parse Established Timing Byte #2:

    if (Data[ESTABLISHED_TIMING_INDEX + 2] & 0x80)
    {
        SII_DBG_PRINT("1152 x 870 @ 75Hz\n");
    }

    if ((!Data[0]) && (!Data[ESTABLISHED_TIMING_INDEX + 1]) && (!Data[2]))
    {
        SII_DBG_PRINT("No established video modes\n");
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvParseStandardTiming()
//
// PURPOSE      :   Parse the standard timing section of EDID Block 0 and
//                  print their decoded meaning to the screen.
//
// INPUT PARAMS :   Pointer to the array where the data read from EDID
//                  Block0 is stored.
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   Void
//
//////////////////////////////////////////////////////////////////////////////

static void SiiDrvParseStandardTiming(uint8_t *Data)
{
    uint8_t i;
    uint8_t AR_Code;

    SII_DBG_PRINT("Parsing Standard Timing:\n");
    SII_DBG_PRINT("========================\n");

    for (i = 0; i < NUM_OF_STANDARD_TIMINGS * 2; i += 2)
    {
        if ((Data[STANDARD_TIMING_OFFSET + i] == 0x01) && ((Data[STANDARD_TIMING_OFFSET + i + 1]) == 1))
        {
            SII_DBG_PRINT("Standard Timing Undefined\n"); // per VESA EDID standard, Release A, Revision 1, February 9, 2000, Sec. 3.9
        }
        else
        {
            SII_DBG_PRINT("Horizontal Active pixels: %i\n",
                                                  (int)((Data[STANDARD_TIMING_OFFSET + i] + 31) * 8));                                                   // per VESA EDID standard, Release A, Revision 1, February 9, 2000, Table 3.15

            AR_Code = (Data[STANDARD_TIMING_OFFSET + i + 1] & TWO_MSBITS) >> 6;

            SII_DBG_PRINT("Aspect Ratio: ");

            switch (AR_Code)
            {
            case AR16_10:
                SII_DBG_PRINT("16:10\n");
                break;

            case AR4_3:
                SII_DBG_PRINT("4:3\n");
                break;

            case AR5_4:
                SII_DBG_PRINT("5:4\n");
                break;

            case AR16_9:
                SII_DBG_PRINT("16:9\n");
                break;
            default:
                SII_WRN_PRINT("invalid aspect ratio.\n");
                break;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvParseDetailedTiming()
//
// PURPOSE      :   Parse the detailed timing section of EDID Block 0 and
//                  print their decoded meaning to the screen.
//
// INPUT PARAMS :   Pointer to the array where the data read from EDID
//                  Block0 is stored.
//
//                  Offset to the beginning of the Detailed Timing Descriptor
//                  data.
//
//                  Block indicator to distinguish between block #0 and blocks
//                  #2, #3
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   Void
//
//////////////////////////////////////////////////////////////////////////////
bool SiiDrvParseDetailedTiming(uint8_t *Data, uint8_t DetailedTimingOffset, uint8_t Block)//UT XU
{
    uint8_t TmpByte;
    uint8_t i;
    uint16_t TmpWord;

    TmpWord = Data[DetailedTimingOffset + PIX_CLK_OFFSET] +
              256 * Data[DetailedTimingOffset + PIX_CLK_OFFSET + 1];

    if (TmpWord == 0x00)                // 18 byte partition is used as either for Monitor Name or for Monitor Range Limits or it is unused
    {
        if (Block == EDID_BLOCK_0)              // if called from Block #0 and first 2 bytes are 0 => either Monitor Name or for Monitor Range Limits
        {
            if (Data[DetailedTimingOffset + 3] == 0xFC)     // these 13 bytes are ASCII coded monitor name
            {
                SII_DBG_PRINT("Monitor Name: ");
                for (i = 0; i < 13; i++)
                {
                    printk("%c", Data[DetailedTimingOffset + 5 + i]);   // Display monitor name on SiIMon
                }

                printk("\n");
            }
            else if (Data[DetailedTimingOffset + 3] == 0xFD)             // these 13 bytes contain Monitor Range limits, binary coded
            {
                SII_DBG_PRINT("Monitor Range Limits:\n\n");

                i = 0;

                SII_DBG_PRINT("Min Vertical Rate in Hz: %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                                       //
                SII_DBG_PRINT("Max Vertical Rate in Hz: %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                               //
                SII_DBG_PRINT("Min Horizontal Rate in Hz: %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                                         //
                SII_DBG_PRINT("Max Horizontal Rate in Hz: %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                                         //
                SII_DBG_PRINT("Max Supported pixel clock rate in MHz/10: %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                                                        //
                SII_DBG_PRINT("Tag for secondary timing formula (00h=not used): %d\n",
                (int) Data[DetailedTimingOffset + 5 + i++]);                                                                                                                       //
                SII_DBG_PRINT("Min Vertical Rate in Hz %d\n",
                (int) Data[DetailedTimingOffset + 5 + i]);                                                                                                      //
            }
        }
        else if (Block == EDID_BLOCK_2_3)                                  // if called from block #2 or #3 and first 2 bytes are 0x00 (padding) then this
        {
            // descriptor partition is not used and parsing should be stopped
            SII_DBG_PRINT("No More Detailed descriptors in this block\n");
            return false;
        }
    }
    else   // first 2 bytes are not 0 => this is a detailed timing descriptor from either block
    {
        if ((Block == EDID_BLOCK_0) && (DetailedTimingOffset == 0x36))
        {
            SII_DBG_PRINT("Parse Results, EDID Block #0, Detailed Descriptor Number 1:\n");
            SII_DBG_PRINT("===========================================================\n");
        }
        else if ((Block == EDID_BLOCK_0) && (DetailedTimingOffset == 0x48))
        {
            SII_DBG_PRINT("Parse Results, EDID Block #0, Detailed Descriptor Number 2:\n");
            SII_DBG_PRINT("===========================================================\n");
        }

        SII_DBG_PRINT("Pixel Clock (MHz * 100): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + H_ACTIVE_OFFSET] +
                  256 * ((Data[DetailedTimingOffset + H_ACTIVE_OFFSET + 2] >> 4) & FOUR_LSBITS);

        SII_DBG_PRINT("Horizontal Active Pixels: %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + H_BLANKING_OFFSET] +
                  256 * (Data[DetailedTimingOffset + H_BLANKING_OFFSET + 1] & FOUR_LSBITS);

        SII_DBG_PRINT("Horizontal Blanking (Pixels): %d\n", (int)TmpWord);

        TmpWord = (Data[DetailedTimingOffset + V_ACTIVE_OFFSET]) +
                  256 * ((Data[DetailedTimingOffset + (V_ACTIVE_OFFSET) +2] >> 4) & FOUR_LSBITS);

        SII_DBG_PRINT("Vertical Active (Lines): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + V_BLANKING_OFFSET] +
                  256 * (Data[DetailedTimingOffset + V_BLANKING_OFFSET + 1] & FOUR_LSBITS);

        SII_DBG_PRINT("Vertical Blanking (Lines): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + H_SYNC_OFFSET] +
                  256 * ((Data[DetailedTimingOffset + (H_SYNC_OFFSET + 3)] >> 6) & TWO_LSBITS);

        SII_DBG_PRINT("Horizontal Sync Offset (Pixels): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + H_SYNC_PW_OFFSET] +
                  256 * ((Data[DetailedTimingOffset + (H_SYNC_PW_OFFSET + 2)] >> 4) & TWO_LSBITS);

        SII_DBG_PRINT("Horizontal Sync Pulse Width (Pixels): %d\n",
        (int)TmpWord);

        TmpWord = ((Data[DetailedTimingOffset + V_SYNC_OFFSET] >> 4) & FOUR_LSBITS) +
                  256 * ((Data[DetailedTimingOffset + (V_SYNC_OFFSET + 1)] >> 2) & TWO_LSBITS);

        SII_DBG_PRINT("Vertical Sync Offset (Lines): %d\n", (int)TmpWord);

        TmpWord = ((Data[DetailedTimingOffset + V_SYNC_PW_OFFSET]) & FOUR_LSBITS) +
                  256 * (Data[DetailedTimingOffset + (V_SYNC_PW_OFFSET + 1)] & TWO_LSBITS);

        SII_DBG_PRINT("Vertical Sync Pulse Width (Lines): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + H_IMAGE_SIZE_OFFSET] +
                  256 * (((Data[DetailedTimingOffset + (H_IMAGE_SIZE_OFFSET + 2)]) >> 4) & FOUR_LSBITS);
        SII_DBG_PRINT("Horizontal Image Size (mm): %d\n", (int)TmpWord);

        TmpWord = Data[DetailedTimingOffset + V_IMAGE_SIZE_OFFSET] +
                  256 * (Data[DetailedTimingOffset + (V_IMAGE_SIZE_OFFSET + 1)] & FOUR_LSBITS);
        SII_DBG_PRINT("Vertical Image Size (mm): %d\n", (int)TmpWord);

        TmpByte = Data[DetailedTimingOffset + H_BORDER_OFFSET];

        SII_DBG_PRINT("Horizontal Border (Pixels): %d\n", (int)TmpByte);

        TmpByte = Data[DetailedTimingOffset + V_BORDER_OFFSET];

        SII_DBG_PRINT("Vertical Border (Lines): %d\n", (int)TmpByte);

        TmpByte = Data[DetailedTimingOffset + FLAGS_OFFSET];
        if (TmpByte & BIT7)
        {
            SII_DBG_PRINT("Interlaced\n");
        }
        else
        {
            SII_DBG_PRINT("Non-Interlaced\n");
        }

        if (!(TmpByte & BIT5) && (!(TmpByte & BIT6)))
        {
            SII_DBG_PRINT("Normal Display, No Stereo\n");
        }
        else
        {
            SII_DBG_PRINT("Refer to VESA E-EDID Release A, Revision 1, table 3.17\n");
        }

        if (!(TmpByte & BIT3) && (!(TmpByte & BIT4)))
        {
            SII_DBG_PRINT("Analog Composite\n");
        }
        else if ((TmpByte & BIT3) && (!(TmpByte & BIT4)))
        {
            SII_DBG_PRINT("Bipolar Analog Composite\n");
        }
        else if (!(TmpByte & BIT3) && (TmpByte & BIT4))
        {
            SII_DBG_PRINT("Digital Composite\n");
        }
        else if ((TmpByte & BIT3) && (TmpByte & BIT4))
        {
            SII_DBG_PRINT("Digital Separate\n");
        }
    }

    return true;
}

static bool SiiDrvGetDDC_Access (uint8_t *reg_val)
{
    byte TPI_ControlImage;

    // Read and store original value. Will be passed into SiiDrvReleaseDDC()
    *reg_val = SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR);

    // register map should be update, bit[1] =0: tpi is handling ddc --xueping
    SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, 0x02, 0x00);

    TPI_ControlImage = SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR);
    if (!(TPI_ControlImage & 0x02))
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool SiiDrvReleaseDDC(byte SysCtrlRegVal)
{
    byte DDCReqTimeout = T_DDC_ACCESS;
    byte TPI_ControlImage;

    SiiDrvModifyByteTPI(TPI_HW_DBG7_ADDR, 0x80, 0x00); //xueping : release ddc master
    SysCtrlRegVal &= ~BITS_2_1;                 // Just to be sure bits [2:1] are 0 before it is written

    while (DDCReqTimeout--)                     // Loop till 0x1A[1] reads "0"
    {
        // Cannot use ReadClearWriteTPI() here. A read of TPI_SYSTEM_CONTROL is invalid while DDC is granted.
        // Doing so will return 0xFF, and cause an invalid value to be written back.
        //ReadClearWriteTPI(TPI_SYSTEM_CONTROL,BITS_2_1); // 0x1A[2:1] = "0" - release the DDC bus

        SiiDrvWriteByteTPI(TPI_SYSTEM_CTRL_ADDR, SysCtrlRegVal);
        TPI_ControlImage = SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR);

        if (!(TPI_ControlImage & BITS_2_1))
        {
            // When 0x1A[2:1] read "0"
            return true;
        }
    }

    return false;                               // Failed to release DDC bus control
}

void SiiDrvEDIDReadFIFO(uint8_t Segment, uint8_t BlockOffset, uint8_t *pBufEdid, uint8_t FifoOffset)//UT XU
{
    uint8_t ddc_fifo_status = 0;
    uint8_t status = 0;
    uint8_t OverTime = 10;
    uint8_t i = 0;

    //Step 1: Clear FIFO
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_CMD_ADDR, 0x09);
    //Check DDC Status and make sure it's cleared.
    ddc_fifo_status = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_DDC_STATUS_ADDR);
    if (0x04 != (ddc_fifo_status & (P0_DDC_FIFO_EMPTY_MASK)))
    {
        SII_DBG_PRINT("DDC fifo cleared error!\n");
    }

    //Step 2: Write target slave address
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_ADDR_ADDR, 0xa0);

    //Step 3: Write target segment address
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_SEGM_ADDR, Segment);

    //Step 4: Write target offset address
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_OFFSET_ADDR, (BlockOffset + FifoOffset));

    //Step 5: Write number of bytes to read
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_COUNT1_ADDR, EDID_FIFO_LENGTH); //set the size of the EDID infomation

    //Step 6: Begin to read.
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_CMD_ADDR, (0 == Segment) ? 0x02 : 0x04); //sequential or enhanced DDC read without ack

    while (OverTime--)
    {
        msleep(1);

        //Read when FIFO is full. You can also use BIT1 or BIT3 register 0x73(Interrupt Source #3 Register).
        status = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_DDC_STATUS_ADDR);
        if (status & P0_DDC_FIFO_FULL_MASK)
        {
            for (i = 0; i < EDID_FIFO_LENGTH; i++)
            {
                pBufEdid[FifoOffset + i] = SiiDrvReadByteTPI(TPI_DDC_DATA_ADDR);
            }
            break;
        }
    }

	return ;
}

//*************************************************//
//**
//**read edid block0 and edid block 1   , set address = 0xa0
//**
//*************************************************//
void SiiDrvReadBlockEDID(uint8_t Block)
{
    uint8_t FifoOffset = 0;
    uint8_t Segment = 0;
    uint8_t BlockOffset = 0;
    uint8_t *pBufEdid = g_PlumTxConfig.EDID.edidBlockData + Block * EDID_BLOCK_SIZE;

    Segment   = (Block / 2);
    BlockOffset = 0;
    if ((Block % 2) > 0)
    {
        BlockOffset = EDID_BLOCK_SIZE;
    }

    SII_DBG_PRINT("EDID DATA (Segment = %d Block = %d BlockOffset = %d):\n", (int) Segment, (int) Block, (int) BlockOffset);
    
    // TPI_0xBB = 0xF6 to set DDC bus parameters
    SiiDrvWriteByteTPI(TPI_SECURITY_CTRL_ADDR, 0xF6);

    // DDC master speed = 100K
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_DELAY_CNT_ADDR, 0x28);

    // TPI_0x7F[7] = 1 to enable TPI HW DDC Master Controller so that Host software can access EDID 
    // by parallel bus. 
    SiiDrvWriteByteTPI(TPI_HW_DBG7_ADDR, 0x80); 

    do
    {
        SiiDrvEDIDReadFIFO(Segment, BlockOffset, pBufEdid, FifoOffset);  //where the fifo size is 16 bytes, read 16 bytes
        FifoOffset += EDID_FIFO_LENGTH;
    } while (FifoOffset < EDID_BLOCK_SIZE);
}

/******************************************************************************
* Function:       mhl_read_edid
* Description:    read edid
* Input:
* Output:
* Return:
*******************************************************************************/
int mhl_read_edid(void) //UT XU
{
    int i   = 0;
    int ret = -1;

    memset(edid, 0x00, sizeof(edid));

    for (i = 0; i < MHL_READ_EDID_COUNT && mhl_is_connect(); i++) {
        ret = SiiDrvMhlTxReadEdid();

        /* sink is HDMI or DVI */
        if ((ret == EDID_OK) || (ret == EDID_NO_861_EXTENSIONS)) {
            hdmi.edid_set = true;
            ret = 0;
            logi("read edid success.\n");
            break;
        }

        logw("read edid fail, and retry.\n");
        msleep(100);
    }

    if (ret) {
        loge("read edid fail.\n");
        memset(edid, 0x00, sizeof(edid));
        hdmi.edid_set = false;
        ret = -EIO;
    }

    return ret;
}


/******************************************************************************
* Function:       edid_get_timing_order
* Description:    get timing order from timings list.
* Input:          timing code
* Output:         order in list by priority
* Return:         video timing
*******************************************************************************/
int edid_get_timing_order(int code, bool mhl_check)
{
    int count = ARRAY_SIZE(timing_order);
    int i = 0;
    int max_order = MHL_NOT_SUPPORT_TIMING_ORDER;
    struct fb_var_screeninfo * fbvar = k3fb_get_fb_var(0);

    if (fbvar && (fbvar->xres * fbvar->yres >= HDMI_TIMING_1080P_XRES * HDMI_TIMING_1080P_YRES)) {
        max_order = MHL_NOT_SUPPORT_TIMING_ORDER_1080P;
    }
    
#ifdef CONFIG_MACH_HI6620SFT
    max_order = MHL_NOT_SUPPORT_TIMING_ORDER_FPGA;
#endif
    
#if (USE_PP_MODE)
    /* TODO: In PP mode, MHL will support up to 1080p/60, otherwise 720p/60 or 1080p/30 */
#endif

    for (i = 0; i < count; i++) {
        if (timing_order[i] == code) {
            if(mhl_check && (i >= max_order)){
                return -1;
            }
            return i;
        }
    }
    return -1;
}

int edid_get_vesa_timing_order(int code, bool mhl_check)
{
    int count = ARRAY_SIZE(vesa_timing_order);
    int i = 0;
    int max_order = MHL_NOT_SUPPORT_VESA_TIMING_ORDER;

#ifdef CONFIG_MACH_HI6620SFT
    max_order = MHL_NOT_SUPPORT_VESA_TIMING_ORDER_FPGA;
#endif

    for (i = 0; i < count; i++) {
        if (vesa_timing_order[i] == code) {
            if(mhl_check && (i >= max_order)){
                return -1;
            }
            return i;
        }
    }
    return -1;
}

/******************************************************************************
* Function:       get_datablock_offset
* Description:    get offset of cea block by extension_edid_db
* Input:          edid data and data block type of cea
* Output:         offset index
* Return:
*******************************************************************************/
int get_datablock_offset(u8 *edid, extension_edid_db datablock,
                                int *offset)//UT XU
{
    int current_byte = 0;
    int disp = 0;
    int i = 0;
    int number = 0;

    BUG_ON((NULL == edid) || (NULL == offset));

    if (0x00 == edid[0x7e]) {
        logd( "has NO extension block! \n");
        return -1;
    }

    disp = edid[(0x80) + 2];
    //logd( "Extension block present db %d %x\n", datablock, disp);
    if (0x4 == disp) {
        loge( "NO data is provided in the reserved data block! \n");
        return -1;
    }

    i = 0x80 + 0x4;
    //logd( "%x\n", i);
    while (i < (0x80 + disp)) {
        current_byte = edid[i];

        /*logd( "i = %d current_byte = 0x%x (current_byte & HDMI_EDID_EX_DATABLOCK_TAG_MASK) = %d\n",
              i, current_byte, (current_byte & HDMI_EDID_EX_DATABLOCK_TAG_MASK));*/

        if ((current_byte >> 5) == datablock) {
            *offset = i;
            //logd( "datablock %d %d\n", datablock, *offset);

            return 0;

        } else {
            number = (current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK) + 1;
            i += number;
        }
    }
    logw( "not found Extension block db %d \n", datablock);
    return -1;
}

/******************************************************************************
* Function:       edid_get_timing_mode
* Description:    differentiate timing code between interleaved(I) and pronounced(P)
* Input:          timing code
* Output:
* Return:         I or P in edid_timing_mode
*******************************************************************************/
edid_timing_mode edid_get_timing_mode(int code)
{
    switch (code) {
        case HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3    :
        case HDMI_EDID_EX_VIDEO_720x480p_60Hz_4_3    :
        case HDMI_EDID_EX_VIDEO_720x480p_60Hz_16_9   :
        case HDMI_EDID_EX_VIDEO_1280x720p_60Hz_16_9  :
        case HDMI_EDID_EX_VIDEO_720x240p_60Hz_4_3    :
        case HDMI_EDID_EX_VIDEO_720x240p_60Hz_16_9   :
        case HDMI_EDID_EX_VIDEO_2880x240p_60Hz_4_3   :
        case HDMI_EDID_EX_VIDEO_2880x240p_60Hz_16_9  :
        case HDMI_EDID_EX_VIDEO_1440x480p_60Hz_4_3   :
        case HDMI_EDID_EX_VIDEO_1440x480p_60Hz_16_9  :
        case HDMI_EDID_EX_VIDEO_720x576p_50Hz_4_3    :
        case HDMI_EDID_EX_VIDEO_720x576p_50Hz_16_9   :
        case HDMI_EDID_EX_VIDEO_1280x720p_50Hz_16_9  :
        case HDMI_EDID_EX_VIDEO_720x288p_50Hz_4_3    :
        case HDMI_EDID_EX_VIDEO_720x288p_50Hz_16_9   :
        case HDMI_EDID_EX_VIDEO_1440x576p_50Hz_4_3   :
        case HDMI_EDID_EX_VIDEO_1440x576p_50Hz_16_9  :
        case HDMI_EDID_EX_VIDEO_1920x1080p_24Hz_16_9 :
        case HDMI_EDID_EX_VIDEO_1920x1080p_25Hz_16_9 :
        case HDMI_EDID_EX_VIDEO_1920x1080p_30Hz_16_9 :
        case HDMI_EDID_EX_VIDEO_1920x1080p_60Hz_16_9 :
        case HDMI_EDID_EX_VIDEO_1920x1080p_50Hz_16_9 :{
            return EDID_TIMING_MODE_P;
        }

        default: {
            return EDID_TIMING_MODE_I;
        }
    }
}

/******************************************************************************
* Function:       edid_get_video_svds
* Description:    get offset of timing code block from cea
* Input:          edid data
* Output:         offset of timing code block and timing number
* Return:
*******************************************************************************/
static void edid_get_video_svds(u8 *edid, int *offset, int *svd_number)
{
    extension_edid_db vdb =  DATABLOCK_VIDEO;

    BUG_ON(NULL == edid);
    BUG_ON((NULL == offset) || (NULL == svd_number));

    if (!get_datablock_offset(edid, vdb, offset)) {
        *svd_number = edid[*offset] & HDMI_EDID_EX_DATABLOCK_LEN_MASK;
        (*offset)++;

        logd("there is a video timing info.\n");
        return;
    }

    logw("there isn't a video timing info.\n");
    *svd_number = 0;
    *offset = 0;

    return;
}
void edid_print_valid_timing_code(hdmi_cm cm, char** p, int *size, bool mhl_check)
{
    int len    = 0;
    int code = cm.code;
    char aucCode[5] = {'\0'};
    char *q;

        if (HDMI_CODE_TYPE_VESA == cm.mode) {
            code += HDMI_CODE_VESA_OFFSET;
            if (code > HDMI_MAX_VESA_TIMING_CODE)
            {
                   code = HDMI_MAX_VESA_TIMING_CODE;
            }
            if (edid_get_vesa_timing_order(code, mhl_check) < 0) 
            {
                   code = INVALID_VALUE;
            }
        } else if(HDMI_CODE_TYPE_CEA == cm.mode){
            if (edid_get_timing_order(code, mhl_check) < 0) {
                    code = INVALID_VALUE;
            }
        }else{
            code = INVALID_VALUE;
        }

        if (code != INVALID_VALUE)
        {
            /* Modified  for Delete the repeate code begin */
            snprintf(aucCode, sizeof(aucCode), "%d,", code);
            q = strstr((*p - *size), aucCode);
            if(( q == NULL ) || ( (q != (*p-*size))  && ( *(q-1) != ',')) )
            {
            	len = snprintf(*p, PAGE_SIZE-*size, "%d,", code);
            	*size += len;
            	*p += len;
            }
            /* Modified  for Delete the repeate code end */
        }

    return;
}
int edid_get_timing_code_from_videoblock(char** p, int *size, bool mhl_check)
{
    image_format img_format = {0};
    int has_image_format     = 0;
    int i = 0;
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    IN_FUNCTION;

    /*get all support timing code*/
    has_image_format = edid_get_image_format(edid, &img_format);
    if (!has_image_format) {
        logd("there isn't video image format in edid.\n");
        return -1;
    }

    logd(" video format number: %d.\n", img_format.number);

    for (i = 0 ; i < img_format.number; i++) {
        /* now we only support p mode. */
		#if 0
        if (1 == img_format.fmt[i].code) {
            *oneNum++;
        }
		#endif

        cm.mode = HDMI_CODE_TYPE_CEA;
        cm.code = img_format.fmt[i].code;
        edid_print_valid_timing_code(cm, p, size, mhl_check);
    }

    OUT_FUNCTION;
    return 0;
}

int edid_get_timing_code_from_b0DTD(char** p, int *size, bool mhl_check, bool s3d_enabled)
{
    int i        = 0;
    hdmi_video_timings edid_timings = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    IN_FUNCTION;

    /* Seach block 0, there are 4 DTDs arranged in priority order */
    for (i = 0; i < EDID_SIZE_BLOCK0_TIMING_DESCRIPTOR; i++) {
        if (0 == edid_get_timings_info(&(((hdmi_edid *)edid)->dtd[i]), &edid_timings)) {
            logd("this block[%d] hasn't timing info.\n", i);
            continue;
        }

        logd("Block0 [%d] timings:\n", i);
        edid_dump_video_timings(&edid_timings);
        cm = get_timing_code(&edid_timings);
        logd("Block0 [%d] value matches code = %d , mode = %d\n", i, cm.code, cm.mode);

        if (INVALID_VALUE == cm.code) {
            logd("this block[%d]'s code is invalid.\n", i);
            continue;
        }

        if ((s3d_enabled)
            && (INVALID_VALUE == s3d_code_cea[cm.code])) {
            logd("this block[%d]'s code isn't s3d.\n", i);
            continue;
        }

		#if 0
        /* if sink supports audio, use CEA video timing */
        if ((audio_support) && (HDMI_CODE_TYPE_VESA == cm.mode)) {
            logd("this block[%d]'s mode don't surport audio.\n", i);
            //continue;
        }
		#endif

         edid_print_valid_timing_code(cm, p, size, mhl_check);
    }
    OUT_FUNCTION;

    return 0;
}


int edid_get_timing_code_from_SVD(char** p, int *size, bool mhl_check, bool s3d_enabled)
{
    int i = 0;
    int j = 0;
    int svd_base    = 0;
    int svd_number  = 0;
    int svd_code    = 0;
    int svd_native  = 0;
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    IN_FUNCTION;

        /* Search SVDs in block 1 twice: first natives and then all */
    if (0x00 != ((hdmi_edid *)edid)->extension_edid) {
        edid_get_video_svds((u8 *)edid, &svd_base, &svd_number);
        for (j = 1; j >= 0; j--) {
            for (i = 0; i < svd_number; i++) {
                svd_native = ((u8 *)edid)[svd_base+i] & HDMI_EDID_EX_VIDEO_NATIVE;
                svd_code = ((u8 *)edid)[svd_base+i] & HDMI_EDID_EX_VIDEO_MASK;

                if (svd_code >= ARRAY_SIZE(code_cea)) {
                    continue;
                }

                /* Check if this SVD is native*/
                if ((!svd_native) && j) {
                    continue;
                }

                /* Check if this 3D CEA timing is supported*/
                if ((s3d_enabled) && (INVALID_VALUE == s3d_code_cea[svd_code])) {
                    continue;
                }

                /* Check if this CEA timing is supported*/
                if (INVALID_VALUE == code_cea[svd_code]) {
                    continue;
                }

                edid_print_valid_timing_code(cm, p, size, mhl_check);

            }
        }
    }
    OUT_FUNCTION;
    return 0;
}

int edid_get_timing_code_from_b1DTD(char** p, int *size, bool mhl_check, bool s3d_enabled, bool audio_support)
{
    int i = 0;
    u32 offset   = 0;
    u32 addr     = 0;
    hdmi_video_timings edid_timings = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    IN_FUNCTION;

    /* Search DTDs in block1 */
    if (((hdmi_edid *)edid)->extension_edid != 0x00) {
        offset = ((hdmi_edid *)edid)->offset_dtd;
        if (offset != 0) {
            addr = EDID_DESCRIPTOR_BLOCK1_ADDRESS + offset;
        }

        for (i = 0; i < EDID_SIZE_BLOCK1_TIMING_DESCRIPTOR; i++) {
            edid_get_ext_timings_info(addr, (u8 *)edid, &edid_timings);
            addr += EDID_TIMING_DESCRIPTOR_SIZE;
            cm = get_timing_code(&edid_timings);
            logd("Block1[%d] value matches code = %d , mode = %d\n",
                 i, cm.code, cm.mode);
            if (INVALID_VALUE == cm.code) {
                continue;
            }

            if ((true == s3d_enabled) && (INVALID_VALUE == s3d_code_cea[cm.code])) {
                continue;
            }

            /* if sink supports audio, use CEA video timing */
            if ((true == audio_support) && (HDMI_CODE_TYPE_VESA == cm.mode)) {
                continue;
            }

            edid_print_valid_timing_code(cm, p, size, mhl_check);
        }
    }
    OUT_FUNCTION;
    return 0;
}

int edid_get_timing_code_from_EstablishTiming(char** p, int *size, bool mhl_check)
{
    int i = 0;
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};
    int EstablishTimingCode[2][8] = {
       {HDMI_EDID_VESA_VIDEO_800x600p_60Hz_4_3,
	  HDMI_EDID_VESA_VIDEO_800x600p_56Hz_4_3,
         HDMI_EDID_VESA_VIDEO_640x480p_75Hz_4_3,
         HDMI_EDID_VESA_VIDEO_640x480p_72Hz_4_3,
         INVALID_VALUE,/* 640*480 67Hz */
         HDMI_EDID_VESA_VIDEO_640x480p_60Hz_4_3,
         INVALID_VALUE,/* 720*400 88Hz */
         INVALID_VALUE /* 720*400 70Hz */
       },
       {HDMI_EDID_VESA_VIDEO_1280x1024p_75Hz_4_3,
	  HDMI_EDID_VESA_VIDEO_1024x768p_75Hz_4_3,
	  HDMI_EDID_VESA_VIDEO_1024x768p_70Hz_4_3,
	  HDMI_EDID_VESA_VIDEO_1024x768p_60Hz_4_3,
         INVALID_VALUE,/* 1024*768 87Hz */
         INVALID_VALUE,/* 832*624 75Hz */
	  HDMI_EDID_VESA_VIDEO_800x600p_75Hz_4_3,
	  HDMI_EDID_VESA_VIDEO_800x600p_72Hz_4_3
       }
    };

    IN_FUNCTION;

    /*As last resort, check for best establish timing supported:*/
    for(i=0;i<8;i++)
    {
        if (((hdmi_edid *)edid)->timing_1 & (0x01<<i)) {
            cm.mode = HDMI_CODE_TYPE_VESA;
            cm.code = EstablishTimingCode[0][i] - HDMI_CODE_VESA_OFFSET;
    
            edid_print_valid_timing_code(cm, p, size, mhl_check);
      }
    }

    for(i=0;i<8;i++)
    {
        if (((hdmi_edid *)edid)->timing_2 & (0x01<<i)) {
            cm.mode = HDMI_CODE_TYPE_VESA;
            cm.code = EstablishTimingCode[1][i] - HDMI_CODE_VESA_OFFSET;
    
            edid_print_valid_timing_code(cm, p, size, mhl_check);
      }
    }
    OUT_FUNCTION;

    return 0;
}

int edid_get_timing_code_from_StandardTiming(char** p, int *size, bool mhl_check)
{
    int i, j;
    uint8_t AR_Code;
    u16 x_res;          /* Unit: pixels */
    u16 y_res;          /* Unit: pixels */
    u32 refresh_rate;    /* Unit: KHz */
    hdmi_video_timings temp = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    for (i = 0; i < NUM_OF_STANDARD_TIMINGS * 2; i += 2)
    {
        if ((edid[STANDARD_TIMING_OFFSET + i] == 0x01) && ((edid[STANDARD_TIMING_OFFSET + i + 1]) == 1))
        {
            SII_DBG_PRINT("Standard Timing Undefined\n"); // per VESA EDID standard, Release A, Revision 1, February 9, 2000, Sec. 3.9
        }
        else
        {
            x_res = (int)((edid[STANDARD_TIMING_OFFSET + i] + 31) * 8);                                                   // per VESA EDID standard, Release A, Revision 1, February 9, 2000, Table 3.15

            AR_Code = (edid[STANDARD_TIMING_OFFSET + i + 1] & TWO_MSBITS) >> 6;

            SII_DBG_PRINT("Aspect Ratio: ");
            switch (AR_Code)
            {
                case AR16_10:
                    SII_DBG_PRINT("16:10\n");
                    y_res = x_res * 10 / 16;
                    break;

                case AR4_3:
                    SII_DBG_PRINT("4:3\n");
                    y_res = x_res * 3 / 4;
                    break;

                case AR5_4:
                    SII_DBG_PRINT("5:4\n");
                    y_res = x_res * 4 / 5;
                    break;

                case AR16_9:
                    SII_DBG_PRINT("16:9\n");
                    y_res = x_res * 9 / 16;
                    break;
                default:
                    SII_WRN_PRINT("invalid aspect ratio.\n");
                    y_res = 0;
                    break;
            }

            refresh_rate = (edid[STANDARD_TIMING_OFFSET + i + 1] & 0x3F) +60;
            
            for (j = HDMI_TIMINGS_VESA_START; j < ARRAY_SIZE(all_timings_direct); j++) {
                temp = all_timings_direct[j];
        
                if ((temp.refresh_rate != refresh_rate)
                    || (temp.x_res != x_res)
                    || (temp.y_res != y_res)) {        
                    continue;
                }
        
                cm.code = code_index[j];
                cm.mode = (j < HDMI_TIMINGS_VESA_START || j > HDMI_TIMINGS_VESA_END) ? HDMI_CODE_TYPE_CEA : HDMI_CODE_TYPE_VESA;
                logd("Video code = %d mode = %s\n", cm.code, cm.mode ? "CEA" : "VESA");
                break;
            }

            edid_print_valid_timing_code(cm, p, size, mhl_check);
        }
    }

    return 0;
}
/******************************************************************************
* Function:       edid_get_timing_code
* Description:    get video code from edid
* Input:          parsed data of edid, s3d enabled
* Output:
* Return:         hdmi mode and code
*******************************************************************************/
hdmi_cm edid_get_best_timing_code(hdmi_edid *edid, bool s3d_enabled)//UT XU
{
    int i        = 0;
    int j        = 0;
    u32 offset   = 0;
    u32 addr     = 0;

    int svd_base    = 0;
    int svd_number  = 0;
    int svd_code    = 0;
    int svd_native  = 0;

    bool audio_support = false;

    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    hdmi_video_timings edid_timings = {0};

    BUG_ON(NULL == edid);

    if (false == edid_is_valid_edid((u8*)edid)) {
        loge("the edid isn't readed, and use default code.\n");
        cm.mode = HDMI_DEFAULT_TIMING_MODE;
        cm.code = edid_get_default_code();
        return cm;
    }

    /*
     *  Verify if the sink supports audio
     */
    /* check if EDID has CEA extension block */
    if ((edid->extension_edid != 0x00)
        /* check if CEA extension block is version 3 */
        && (3 == edid->extention_rev)
        /* check if extension block has the IEEE HDMI ID*/
        &&(edid_has_ieee_id((u8 *)edid))
        /* check if sink supports basic audio */
        &&(edid->num_dtd & HDMI_AUDIO_BASIC_MASK)) {

        audio_support = true;
    }

    /* Seach block 0, there are 4 DTDs arranged in priority order */
    for (i = 0; i < EDID_SIZE_BLOCK0_TIMING_DESCRIPTOR; i++) {
        if (0 == edid_get_timings_info(&edid->dtd[i], &edid_timings)) {
            logd("this block[%d] hasn't timing info.\n", i);
            continue;
        }

        logd("Block0 [%d] timings:\n", i);
        edid_dump_video_timings(&edid_timings);
        cm = get_timing_code(&edid_timings);
        logd("Block0 [%d] value matches code = %d , mode = %d\n", i, cm.code, cm.mode);

        if (INVALID_VALUE == cm.code) {
            logd("this block[%d]'s code is invalid.\n", i);
            continue;
        }

        if ((s3d_enabled)
            && (INVALID_VALUE == s3d_code_cea[cm.code])) {
            logd("this block[%d]'s code isn't s3d.\n", i);
            continue;
        }

        /* if sink supports audio, use CEA video timing */
        if ((audio_support) && (HDMI_CODE_TYPE_VESA == cm.mode)) {
            logd("this block[%d]'s mode don't surport audio.\n", i);
            audio_support = false;
            //continue;
        }
        return cm;
    }

    /* Search SVDs in block 1 twice: first natives and then all */
    if (0x00 != edid->extension_edid) {
        edid_get_video_svds((u8 *)edid, &svd_base, &svd_number);
        for (j = 1; j >= 0; j--) {
            for (i = 0; i < svd_number; i++) {
                svd_native = ((u8 *)edid)[svd_base+i] & HDMI_EDID_EX_VIDEO_NATIVE;
                svd_code = ((u8 *)edid)[svd_base+i] & HDMI_EDID_EX_VIDEO_MASK;

                if (svd_code >= ARRAY_SIZE(code_cea)) {
                    continue;
                }

                /* Check if this SVD is native*/
                if ((!svd_native) && j) {
                    continue;
                }

                /* Check if this 3D CEA timing is supported*/
                if ((s3d_enabled) && (INVALID_VALUE == s3d_code_cea[svd_code])) {
                    continue;
                }

                /* Check if this CEA timing is supported*/
                if (INVALID_VALUE == code_cea[svd_code]) {
                    continue;
                }

                return cm;
            }
        }
    }

    /* Search DTDs in block1 */
    if (edid->extension_edid != 0x00) {
        offset = edid->offset_dtd;
        if (offset != 0) {
            addr = EDID_DESCRIPTOR_BLOCK1_ADDRESS + offset;
        }

        for (i = 0; i < EDID_SIZE_BLOCK1_TIMING_DESCRIPTOR; i++) {
            edid_get_ext_timings_info(addr, (u8 *)edid, &edid_timings);
            addr += EDID_TIMING_DESCRIPTOR_SIZE;
            cm = get_timing_code(&edid_timings);
            logd("Block1[%d] value matches code = %d , mode = %d\n",
                 i, cm.code, cm.mode);
            if (INVALID_VALUE == cm.code) {
                continue;
            }

            if ((true == s3d_enabled) && (INVALID_VALUE == s3d_code_cea[cm.code])) {
                continue;
            }

            /* if sink supports audio, use CEA video timing */
            if ((true == audio_support) && (HDMI_CODE_TYPE_VESA == cm.mode)) {
                continue;
            }

            return cm;
        }
    }

    /*As last resort, check for best standard timing supported:*/
    if (edid->timing_1 & 0x01) {
        logd("800x600@60Hz\n");
        cm.mode = HDMI_CODE_TYPE_VESA;
        cm.code = HDMI_EDID_VESA_VIDEO_800x600p_60Hz_4_3;

        return cm;
    }

    if (edid->timing_2 & 0x08) {
        logd("1024x768@60Hz\n");
        cm.mode = HDMI_CODE_TYPE_VESA;
        cm.code = HDMI_EDID_VESA_VIDEO_1024x768p_60Hz_4_3;

        return cm;
    }

    cm.mode = INVALID_VALUE;
    cm.code = INVALID_VALUE;

    return cm;
}

/******************************************************************************
* Function:       edid_get_best_timing
* Description:    get best video code from edid
* Input:          parsed data of edid
* Output:
* Return:         hdmi mode and code
*******************************************************************************/
hdmi_cm edid_get_best_timing(hdmi_edid *edid)//UT XU
{
    int has_image_format = 0;
    int i = 0;
    image_format img_format = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};
    hdmi_cm externcm = {INVALID_VALUE, INVALID_VALUE};
    int order = 0;
    int best_order = 0;

    IN_FUNCTION;

    if (false == edid_is_valid_edid((u8*)edid)) {
        loge("the edid isn't readed, and use default code.\n");
        cm.mode = HDMI_DEFAULT_TIMING_MODE;
        cm.code = edid_get_default_code();
        OUT_FUNCTION;
        return cm;
    }

    /*get all support timing code*/
    has_image_format = edid_get_image_format((u8 *)edid, &img_format);
    if (!has_image_format) {
        logd("there isn't video image format in edid.\n");
    }

    logd(" video format number: %d.\n", img_format.number);

    for (i = 0 ; i < img_format.number; i++) {
        order = edid_get_timing_order(img_format.fmt[i].code, !hdmi.auto_set);
        if (order >= best_order) {
            best_order = order;
            cm.mode = HDMI_CODE_TYPE_CEA;
            cm.code = img_format.fmt[i].code;
        }
    }

    if (0 == best_order) {
        externcm = edid_get_best_timing_code((hdmi_edid *)edid, false);
        if (HDMI_CODE_TYPE_CEA == externcm.mode) {
            order = edid_get_timing_order(externcm.code, !hdmi.auto_set);
            if (order) {
                best_order = order;
                cm.code = externcm.code;
                cm.mode = externcm.mode;
            }
        } else {
            if (INVALID_VALUE != externcm.code) {
                externcm.code = externcm.code + HDMI_CODE_VESA_OFFSET;

                if (externcm.code > HDMI_MAX_VESA_TIMING_CODE) {
                    externcm.code = HDMI_MAX_VESA_TIMING_CODE;
                }
                
                order = edid_get_vesa_timing_order(externcm.code, !hdmi.auto_set);
                if (order >= best_order) {
                    best_order = order;
                    cm.code = externcm.code;
                    cm.mode = externcm.mode;
                }
            }
        }
    }

    OUT_FUNCTION;
    return cm;
}

/******************************************************************************
* Function:       edid_get_default_code
* Description:
* Input:
* Output:
* Return:
*******************************************************************************/
int edid_get_default_code(void)
{
#ifdef CONFIG_MACH_HI6620OEM    
	return HDMI_DEFAULT_MHL_TIMING_CODE;
#endif

#ifdef CONFIG_MACH_HI6620SFT
    return HDMI_EDID_EX_VIDEO_720x576p_50Hz_16_9;
#endif
}

/******************************************************************************
* Function:       edid_get_av_delay
* Description:    get latency of audio and video from edid
* Input:          edid data
* Output:         struct of latency
* Return:
*******************************************************************************/
static void edid_get_av_delay(u8 *edid, latency *lat)
{
    int offset       = 0;
    int current_byte = 0;
    int number       = 0;
    extension_edid_db vsdb =  DATABLOCK_VENDOR;

    BUG_ON((NULL == edid) || (NULL == lat));

    if (!get_datablock_offset(edid, vsdb, &offset)) {
        current_byte = edid[offset];
        number = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;

        if ((number >= 8) && ((current_byte + 8) & 0x80)) {
            lat->vid_latency = ((current_byte + 8) - 1) * 2;
            lat->aud_latency = ((current_byte + 9) - 1) * 2;
        }

        if ((number >= 8) && ((current_byte + 8) & 0xC0)) {
            lat->int_vid_latency = ((current_byte + 10) - 1) * 2;
            lat->int_aud_latency = ((current_byte + 11) - 1) * 2;
        }
    }

    return;
}
/******************************************************************************
* Function:       dump_s3d_format
* Description:    dump the s3d supported format info of sink
* Input:          edid offset
* Output:         3d supported format
* Return:
*******************************************************************************/
void s3d_format_dump(u8 *edid,int offset){
    u8 *e = NULL;
    int i = 0;
    e = edid;
    e += offset;

    for(; i < 6; i++){
        if(FLD_GET(e[0],i,i)){
            logd( "s3d_surpported_format:%s\n" ,s3d_format[i]);
        }
    }

    e += 1;
    if(FLD_GET(e[0],0,0)){
        logd( "s3d_surpported_format:%s\n" ,s3d_format[6]);
    }
}
/******************************************************************************
* Function:       edid_s3d_supported
* Description:    get 3D ability of the device from edid
* Input:          edid data
* Output:
* Return:         whether the device support 3D
*******************************************************************************/
bool edid_s3d_supported(u8 *edid)
{
    bool s3d_support  = false;
    int  offset       = 0;
    int  current_byte = 0;
    int  current_bit = 0;

    BUG_ON(NULL == edid);

    if (!get_datablock_offset(edid, DATABLOCK_VENDOR, &offset)) {
       if((edid[offset] & 0x1F) < 8){
           s3d_support =false;
       }else {
            offset += 8;
            current_byte = edid[offset++];
            /* Latency_Fields_Present */
            if (current_byte & 0x80) {
                offset += 2;
            }

            /* I_Latency_Fields_Present */
            if (current_byte & 0x40) {
                offset += 2;
            }

            /* HDMI_Video_present */
            if (current_byte & 0x20) {//HDMI_video_present
                current_byte = edid[offset];
                /* 3D_Present */
                if (current_byte & 0x80) {
                    logd( "S3D supported\n");
                    s3d_support = true;

                }
                if(s3d_support){
                   current_bit = FLD_GET(current_byte,6,5);
                   if((current_bit == 0x01) || (current_bit == 0x02)){
                       offset += 1;
                       current_byte = edid[offset++];
                       offset += current_byte >> 5;
                       s3d_format_dump(edid,offset);
                   }
                }

            }
       }
    }

    return s3d_support;
}

/******************************************************************************
* Function:       edid_get_s3d_timings_index
* Description:    get 3D timing code
* Input:
* Output:
* Return:         timing code of 3D format
*******************************************************************************/
int edid_get_s3d_timings_index(int mode, int code)
{
    int index = s3d_code_cea[code];

    if (INVALID_VALUE == index) {
        index = code_cea[edid_get_default_code()];
    }

    return index;
}

/******************************************************************************
* Function:       get_timings_by_index
* Description:    get index of video timing from timing code
* Input:          timing code and timing mode
* Output:
* Return:         timing index
*******************************************************************************/
int get_timings_by_index(int mode, int code)
{
    int index = INVALID_VALUE;

    if (edid_is_valid_code(mode, code)) {
        if (HDMI_CODE_TYPE_VESA == mode) {
            index = code_vesa[code];
        } else {
            index = code_cea[code];
        }
    }

    return index;
}

/******************************************************************************
* Function:       edid_get_timings_index
* Description:    get index of timing by code and mode
* Input:          timing code and timing mode
* Output:
* Return:         timing index
*******************************************************************************/
int edid_get_timings_index(int mode, int code)
{
    hdmi_video_timings *timing = NULL;
    int x_res   = 0;
    int y_res   = 0;
    int tmp     = 0;

    int index = get_timings_by_index(mode, code);

    if (INVALID_VALUE != index) {
        timing = edid_get_timings_byindex(index);
        x_res = timing->x_res;
        y_res = timing->y_res;
        if (x_res > y_res) {
            tmp = x_res;
            x_res = y_res;
            y_res = tmp;
        }
    }

    if (INVALID_VALUE == index
        || x_res > K3_FB_MAX_WIDTH
        || y_res > K3_FB_MAX_HEIGHT) {
        index =  INVALID_VALUE;
    }

    return index;
}

/******************************************************************************
* Function:       edid_get_timings_info
* Description:
* Input:          dtd of edid
* Output:         video timing
* Return:         1 - there is timing info  0 - there isn't timing info
*******************************************************************************/
int edid_get_timings_info(hdmi_edid_dtd *edid_dtd,
                                 hdmi_video_timings *timings)
{
    BUG_ON((NULL == edid_dtd) || (NULL == timings));

    if (edid_dtd->video.pixel_clock) {
        hdmi_edid_dtd_video *vid = &edid_dtd->video;

        timings->pixel_clock = 10 * vid->pixel_clock;
        timings->x_res = vid->horiz_active | (((u16)vid->horiz_high & 0xf0) << 4);
        timings->y_res = vid->vert_active | (((u16)vid->vert_high & 0xf0) << 4);

        timings->hfp = vid->horiz_sync_offset | (((u16)vid->sync_pulse_high & 0xc0) << 2);
        timings->hsw = vid->horiz_sync_pulse | (((u16)vid->sync_pulse_high & 0x30) << 4);
        timings->hbp = (vid->horiz_blanking |
                        (((u16)vid->horiz_high & 0x0f) << 8)) -
                       (timings->hfp + timings->hsw);

        timings->vfp = ((vid->vert_sync_pulse & 0xf0) >> 4) | ((vid->sync_pulse_high & 0x0f) << 2);
        timings->vsw = (vid->vert_sync_pulse & 0x0f) | ((vid->sync_pulse_high & 0x03) << 4);
        timings->vbp = (vid->vert_blanking |
                        (((u16)vid->vert_high & 0x0f) << 8)) -
                       (timings->vfp + timings->vsw);

        logd("there is timing info.\n");
        return 1;
    }

    switch (edid_dtd->monitor_name.block_type) {
        case HDMI_EDID_DTD_TAG_STANDARD_TIMING_DATA:
            logd( "standard timing data, there isn't timing info.\n");
            break;
        case HDMI_EDID_DTD_TAG_COLOR_POINT_DATA:
            logd( "color point data, there isn't timing info.\n");
            break;
        case HDMI_EDID_DTD_TAG_MONITOR_NAME:
            logd( "monitor name: %s, , there isn't timing info.\n", edid_dtd->monitor_name.text);
            break;
        case HDMI_EDID_DTD_TAG_MONITOR_LIMITS: {
            hdmi_edid_dtd_monitor *limits = &edid_dtd->monitor_limits;

            logd("monitor limits\n"
                 "  min_vert_freq=%d\n"
                 "  max_vert_freq=%d\n"
                 "  min_horiz_freq=%d\n"
                 "  max_horiz_freq=%d\n"
                 "  pixel_clock_mhz=%d\n",
                 limits->min_vert_freq,
                 limits->max_vert_freq,
                 limits->min_horiz_freq,
                 limits->max_horiz_freq,
                 limits->pixel_clock_mhz);

            break;
        }
        case HDMI_EDID_DTD_TAG_ASCII_STRING:
            logd( "this is ascii string, and there isn't timing info.\n");
            break;
        case HDMI_EDID_DTD_TAG_MONITOR_SERIALNUM:
            logd( "monitor serialnum: %s, there isn't timing info.\n", edid_dtd->monitor_serial_number.text);
            break;
        default:
            logd( "unsupported EDID descriptor block format, there isn't timing info.\n");
            break;
    }

    return 0;
}

/******************************************************************************
* Function:       edid_get_ext_timings_info
* Description:    get video timing from current address of edid data
* Input:          edid and current address
* Output:         video timing
* Return:
*******************************************************************************/
static void edid_get_ext_timings_info(int current_descriptor_addrs, u8 *edid ,
                                      hdmi_video_timings *timings)
{
    BUG_ON((NULL == edid) || (NULL == timings));

    timings->x_res = (((edid[current_descriptor_addrs + 4] & 0xF0) << 4)
                      | edid[current_descriptor_addrs + 2]);
    timings->y_res = (((edid[current_descriptor_addrs + 7] & 0xF0) << 4)
                      | edid[current_descriptor_addrs + 5]);

    timings->pixel_clock = ((edid[current_descriptor_addrs + 1] << 8)
                            | edid[current_descriptor_addrs]);
    timings->pixel_clock = 10 * timings->pixel_clock;

    timings->hfp = edid[current_descriptor_addrs + 8];
    timings->hsw = edid[current_descriptor_addrs + 9];
    timings->hbp = (((edid[current_descriptor_addrs + 4] & 0x0F) << 8)
                    | edid[current_descriptor_addrs + 3]) -
                   (timings->hfp + timings->hsw);

    timings->vfp = ((edid[current_descriptor_addrs + 10] & 0xF0) >> 4);
    timings->vsw = (edid[current_descriptor_addrs + 10] & 0x0F);
    timings->vbp = (((edid[current_descriptor_addrs + 7] & 0x0F) << 8)
                    | edid[current_descriptor_addrs + 6]) -
                   (timings->vfp + timings->vsw);

    return;
}

/******************************************************************************
* Function:       get_timing_code
* Description:    get timing code from video timing
* Input:          video timing
* Output:
* Return:         timing code and timing mode
*******************************************************************************/
static hdmi_cm get_timing_code(hdmi_video_timings *timings)
{
    int i            = 0;
    int temp_vsync   = 0;
    int temp_hsync   = 0;
    int timing_hsync = 0;
    int timing_vsync = 0;
    int code         = INVALID_VALUE;

    hdmi_video_timings temp = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    BUG_ON(NULL == timings);

    logd("get_timing_code\n");

    for (i = 0; i < ARRAY_SIZE(all_timings_direct); i++) {
        temp = all_timings_direct[i];

        if ((((temp.pixel_clock + PIXEL_CLOCK_OFFSET) < timings->pixel_clock)
            || ((temp.pixel_clock - PIXEL_CLOCK_OFFSET) > timings->pixel_clock))
            || (temp.x_res != timings->x_res)
            || (temp.y_res != timings->y_res)) {

            continue;
        }

        temp_hsync = temp.hfp + temp.hsw + temp.hbp;
        timing_hsync = timings->hfp + timings->hsw + timings->hbp;
        temp_vsync = temp.vfp + temp.vsw + temp.vbp;
        timing_vsync = timings->vfp + timings->vsw + timings->vbp;

        logd("Temp_hsync = %d, temp_vsync = %d, "
             "timing_hsync = %d, timing_vsync = %d\n",
             temp_hsync, temp_vsync, timing_hsync, timing_vsync);

        if ((temp_hsync == timing_hsync) && (temp_vsync == timing_vsync)) {
            code = i;
            cm.code = code_index[i];
            cm.mode = (code < HDMI_TIMINGS_VESA_START || code > HDMI_TIMINGS_VESA_END) ? HDMI_CODE_TYPE_CEA : HDMI_CODE_TYPE_VESA;
            logd("Video code = %d mode = %s\n", cm.code, cm.mode ? "CEA" : "VESA");
            break;
        }
    }
    return cm;
}

/******************************************************************************
* Function:       edid_get_image_format
* Description:    get image format which the device support from edid
* Input:          edid data
* Output:         struct of image format
* Return:         1 -- there is image format  0 -- there isn't image format
*******************************************************************************/
int edid_get_image_format(u8 *edid, image_format *format)
{
    int offset       = 0;
    int current_byte = 0;
    int i            = 0;
    int j            = 0;
    int number       = 0;
    extension_edid_db vsdb =  DATABLOCK_VIDEO;

    BUG_ON((NULL == edid) || (NULL == format));

    format->number = 0;
    memset(format->fmt, 0x00, sizeof(format->fmt));

    if (0 != get_datablock_offset(edid, vsdb, &offset)) {
        logd("there isn't video datablock.\n");
        return 0;
    }

    current_byte = edid[offset];
    number       = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;

#if ENABLE_MOCK_24FPS
    format->fmt[0].code = 32;
    format->fmt[1].code = 33;
    format->fmt[2].code = 34;
    i = 3;
    number -= i;
#endif

    for (j = 1 ; j <= number ; j++) {
        current_byte = edid[offset+j];
        format->fmt[i].code = current_byte & HDMI_EDID_EX_VIDEO_MASK;
        format->fmt[i].pref = current_byte & HDMI_EDID_EX_VIDEO_NATIVE;
        if (++i == HDMI_IMG_FORMAT_MAX_LENGTH) {
            break;
        }
    }
    format->number = i;

    return 1;
}

/******************************************************************************
* Function:       edid_get_audio_format
* Description:    get image format which the device support from edid
* Input:          edid data
* Output:         struct of audio format
* Return:         1 - there is audio format, 0 - there isn't audio format
*******************************************************************************/
int edid_get_audio_format(u8 *edid, audio_format *format)//UT XU
{
    int offset       = 0;
    int current_byte = 0;
    int j            = 0;
    int number       = 0;
    int ind          = 0;
    extension_edid_db vsdb =  DATABLOCK_AUDIO;

    BUG_ON((NULL == edid) || (NULL == format));

    format->number = 0;
    memset(format->fmt, 0x00, sizeof(format->fmt));

    if (!get_datablock_offset(edid, vsdb, &offset)) {
        logd("edid_get_audio_format  offset ==0x%02X \n",offset);
        current_byte = edid[offset];
        number = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;

        if (number/3 >= HDMI_AUDIO_FORMAT_MAX_LENGTH) {
            format->number = HDMI_AUDIO_FORMAT_MAX_LENGTH;
        } else {
            format->number = number/3;
        }

        for (j = 1 ; j < number ; j++) {
            if (1 == j%3) {
                current_byte = edid[offset + j];
                format->fmt[ind].format = FLD_GET(current_byte, 6, 3);
                format->fmt[ind].num_of_ch = FLD_GET(current_byte, 2, 0) + 1;
            } else if (2 == j%3) {
                format->fmt[ind].sampling_freq = edid[offset + j];
                ind++;
            }
        }

        return 1;
    }

    return 0;
}

/******************************************************************************
* Function:       edid_has_vcdb
* Description:    get whether the device have vcdb
* Input:          edid data
* Output:
* Return:         whether the device have vcdb OUI
*******************************************************************************/
bool edid_has_vcdb(u8 *edid)
{
    int offset       = 0;
    int current_byte = 0;
    extension_edid_db vsdb =  DATABLOCK_EXTENDED_TAG;

    BUG_ON(NULL == edid);
    IN_FUNCTION;

    if (!get_datablock_offset(edid, vsdb, &offset)) {
        current_byte = edid[offset+1];

        if (0 == current_byte) {
            logd("there is video capability data block.\n");
            return true;
        }
    }
    OUT_FUNCTION;
    return false;
}

/******************************************************************************
* Function:       edid_has_ieee_id
* Description:    get whether the device have IEEE registration OUI
* Input:          edid data
* Output:
* Return:         whether the device have IEEE registration OUI
*******************************************************************************/
bool edid_has_ieee_id(u8 *edid)
{
    int offset       = 0;
    int current_byte = 0;
    int number       = 0;
    extension_edid_db vsdb =  DATABLOCK_VENDOR;
    u32 hdmi_identifier = 0;

    BUG_ON(NULL == edid);

    if (!get_datablock_offset(edid, vsdb, &offset)) {
        current_byte = edid[offset];
        number = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;

        if (number < 3) {
            logd("number < 3, and hasn't ieee id.\n");
            return false;
        }

        offset++;
        hdmi_identifier = edid[offset] | edid[offset+1]<<8
                          | edid[offset+2]<<16;
        if (HDMI_IEEE_REGISTRATION_ID == hdmi_identifier) {
            logd("there is a ieee id.\n");
            return true;
        }
    }

    return false;
}

/******************************************************************************
* Function:       edid_get_deep_color_info
* Description:    get deep color ability of the device
* Input:          edid data
* Output:         struct of deep_color
* Return:
*******************************************************************************/
void edid_get_deep_color_info(u8 *edid, deep_color *format)
{
    int offset       = 0;
    int current_byte = 0;
    int number       = 0;
    extension_edid_db vsdb = DATABLOCK_VENDOR;

    BUG_ON((NULL == edid) || (NULL == format));

    if (!get_datablock_offset(edid, vsdb, &offset)) {
        current_byte = edid[offset];
        number = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;

        if (number >= 6) {
            format->bit_30 = ((current_byte + 6) & 0x10);
            format->bit_36 = ((current_byte + 6) & 0x20);
        }

        if (number >= 7) {
            format->max_tmds_freq = ((current_byte + 7)) * 5;
        }
    }

    return;
}

/******************************************************************************
* Function:       edid_tv_yuv_supported
* Description:    get whether the device support YUV
* Data Accessed:
* Data Updated:
* Input:          edid data
* Output:
* Return:         whether the device support YUV
* Others:
*******************************************************************************/
bool edid_tv_yuv_supported(u8 *edid)
{
    BUG_ON(NULL == edid);

    if ((edid[0x7e] != 0x00) && (edid[0x83] & 0x30)) {
        logd( "YUV supported\n");
        return true;
    }

    return false;
}

/******************************************************************************
* Function:       edid_ai_supported
* Description:    get whether the device support ai
* Input:          edid data
* Output:
* Return:         whether the device support AI
*******************************************************************************/
bool edid_ai_supported(u8 *edid)
{
    int offset       = 0;
    int current_byte = 0;
    int number       = 0;

    BUG_ON(NULL == edid);

    if (!get_datablock_offset(edid, DATABLOCK_VENDOR, &offset)) {
        current_byte = edid[offset];
        number = current_byte & HDMI_EDID_EX_DATABLOCK_LEN_MASK;
        if (number < 6) {
            return false;
        }

        offset += 6;
        if (edid[offset] & HDMI_EDID_EX_SUPPORTS_AI_MASK) {
            return true;
        }
    }

    return false;
}

/******************************************************************************
* Function:       edid_dump
* Description:    print edid data
* Input:          edid data
* Output:
* Return:
*******************************************************************************/
void edid_dump(u8* edid)
{
    int i = 0;

    BUG_ON(NULL == edid);

    printk("\n========================== edid dump ==========================\n");
    for (; i < HDMI_EDID_MAX_LENGTH; i++) {
        if ((i%16) == 0) {
            printk("\n%02x :",(i/16));
        }
        /* debug func for dump edid, use printk for easy read format. */
        printk("0x%02X",edid[i]);
    }
    printk("\n========================== edid dump ==========================\n");

    return;
}

/******************************************************************************
* Function:       edid_dump_parser
* Description:    print parsed edid data
* Input:          edid data
* Output:
* Return:
*******************************************************************************/
void edid_dump_parser(u8* edid)
{
    u32 i      = 0;
    int offset = 0;
    int addr   = 0;
    int number = 0;
    int has_timing_info = 0;
    int ret    = 0;
    u8  *e     = NULL;

    hdmi_edid    *edid_st     = (hdmi_edid *)edid;
    image_format img_format  = {0};
    audio_format aud_format  = {0};
    deep_color   vsdb_format = {0};
    latency      lat         = {0};

    hdmi_video_timings timings = {0};
    hdmi_cm cm = {INVALID_VALUE, INVALID_VALUE};

    BUG_ON(NULL == edid);

    printk("\n=========================== edid parse ===========================\n");
    e = edid;
    printk( "\nedid_header:\n%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t"
            "%02x\t%02x\n", e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7]);
    e += 8;
    printk( "Vendor & Product:\n%02x\t%02x\t%02x\t%02x\t%02x\t"
            "%02x\t%02x\t%02x\t%02x\t%02x\n",
            e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9]);
    e += 10;
    printk( "EDID Structure:\n%02x\t%02x\n",
            e[0], e[1]);
    e += 2;
    printk( "Basic Display Parameter:\n%02x\t%02x\t%02x\t%02x\t%02x\n",
            e[0], e[1], e[2], e[3], e[4]);
    e += 5;
    printk( "Color Characteristics:\n%02x\t%02x\t%02x\t%02x\t"
            "%02x\t%02x\t%02x\t%02x\t%02x\t%02x\n",
            e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7], e[8], e[9]);
    e += 10;
    printk( "Established timings:\n%02x\t%02x\t%02x\n",
            e[0], e[1], e[2]);
    e += 3;
    printk( "Standard timings:\n%02x\t%02x\t%02x\t%02x\t%02x\t"
            "%02x\t%02x\t%02x\n",
            e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7]);
    e += 8;
    printk( "%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\t%02x\n",
            e[0], e[1], e[2], e[3], e[4], e[5], e[6], e[7]);
    e += 8;

    for (i = 0; i < EDID_SIZE_BLOCK0_TIMING_DESCRIPTOR; i++) {
        logd( "Extension 0 Block %d\n", i);
        has_timing_info = edid_get_timings_info(&edid_st->dtd[i],
                                               &timings);
        if (has_timing_info) {
            cm = get_timing_code(&timings);
            edid_dump_video_timings(&timings);
            logd( "Video code: %d video mode %d\n", cm.code, cm.mode);
        }
    }

    if (edid[0x7e] != 0x00) {
        offset = edid[EDID_DESCRIPTOR_BLOCK1_ADDRESS + 2];
        logd( "offset %x\n", offset);
        if (offset != 0) {
            addr = EDID_DESCRIPTOR_BLOCK1_ADDRESS + offset;
            /* to determine the number of descriptor blocks */
            for (i = 0; i < EDID_SIZE_BLOCK1_TIMING_DESCRIPTOR;
                 i++) {
                logd( "Extension 1 Block %d\n", i);
                edid_get_ext_timings_info(addr, edid, &timings);
                addr += EDID_TIMING_DESCRIPTOR_SIZE;
                edid_dump_video_timings(&timings);
                cm = get_timing_code(&timings);
                logd( "Video code: %d video mode %d\n",
                        cm.code, cm.mode);
            }
        }
        edid_get_video_svds(edid, &offset, &number);
        logd( "No of SVDs: %d\n", number);
        for (i = 0; i < number; i++) {
            logd( "SVD[%d]: CEA code[%d], native[%s]\n",
                    i, edid[offset+i] & HDMI_EDID_EX_VIDEO_MASK,
                    edid[offset+i] & HDMI_EDID_EX_VIDEO_NATIVE ?
                    "YES" : "NO");
        }
        logd( "No. of native dtd: %d\n",
                (edid[EDID_DESCRIPTOR_BLOCK1_ADDRESS + 3]
                 & HDMI_VIDEO_NATIVE_DTDS_MASK));

        logd( "Supports basic audio: %s\n",
                (edid[EDID_DESCRIPTOR_BLOCK1_ADDRESS + 3]
                 & HDMI_AUDIO_BASIC_MASK) ? "YES" : "NO");
    }

    logd( "Has IEEE HDMI ID: %s\n", edid_has_ieee_id(edid) ? "YES" : "NO");

    ret = edid_get_image_format(edid, &img_format);
    logd( "%d image number\n", img_format.number);
    for (i = 0 ; (ret && i < img_format.number); i++) {
        logd( "%d %d pref code\n",
                img_format.fmt[i].pref, img_format.fmt[i].code);
    }

    ret = edid_get_audio_format(edid, &aud_format);
    logd( "%d audio number\n", aud_format.number);
    for (i = 0 ; (ret && i < aud_format.number); i++) {
        logd( "%d %d format num_of_channels\n",
                aud_format.fmt[i].format,
                aud_format.fmt[i].num_of_ch);
    }

    edid_get_deep_color_info(edid, &vsdb_format);
    logd( "%d deep color bit 30 %d  deep color 36 bit "
            "%d max tmds freq\n", vsdb_format.bit_30, vsdb_format.bit_36,
            vsdb_format.max_tmds_freq);

    edid_get_av_delay(edid, &lat);
    logd( "%d vid_latency %d aud_latency "
            "%d interlaced vid latency %d interlaced aud latency\n",
            lat.vid_latency, lat.aud_latency,
            lat.int_vid_latency, lat.int_aud_latency);

    logd( "YUV supported %d\n", (int)edid_tv_yuv_supported(edid));
    logd("\n=========================== edid parse ===========================\n");

    return;
}

/******************************************************************************
* Function:       edid_dump_video_timings
* Description:    debug function to print video timing
* Input:          video timings
* Output:
* Return:
*******************************************************************************/
void edid_dump_video_timings(hdmi_video_timings *timings)
{
    BUG_ON(NULL == timings);
    
    IN_FUNCTION;
    
    logd( "Timing Info:\n"
            "  pixel_clk = %d\n"
            "  x_res     = %d\n"
            "  y_res     = %d\n"
            "  hfp       = %d\n"
            "  hsw       = %d\n"
            "  hbp       = %d\n"
            "  vfp       = %d\n"
            "  vsw       = %d\n"
            "  vbp       = %d\n",
            timings->pixel_clock,
            timings->x_res,
            timings->y_res,
            timings->hfp,
            timings->hsw,
            timings->hbp,
            timings->vfp,
            timings->vsw,
            timings->vbp);
    
    OUT_FUNCTION;
    return;
}

/******************************************************************************
* Function:       edid_get_timings_byindex
* Description:    get video timing by timing code
* Input:          code of video timing
* Output:
* Return:         video timing
*******************************************************************************/
hdmi_video_timings* edid_get_timings_byindex(int index)
{
    BUG_ON((index < 0) || (index >= ARRAY_SIZE(all_timings_direct)));
    return &all_timings_direct[index];
}

/******************************************************************************
* Function:       edid_get_hvpol_bycode
* Description:    get Vsync and Hsync polarity by code
* Input:          timing code
* Output:         hdmi_hvsync_pol of Vsync and Hsync polarity
* Return:
*******************************************************************************/
hdmi_hvsync_pol* edid_get_hvpol_byindex(int index)
{
    BUG_ON((index < 0) || (index >= ARRAY_SIZE(hvpol_mapping)));
    return &hvpol_mapping[index];
}

/******************************************************************************
* Function:       edid_is_valid_code
* Description:    get whether the code is valid
* Input:          timing mode and timing code
* Output:
* Return:         whether the code is valid
*******************************************************************************/
bool edid_is_valid_code(int mode, int code)
{
    return (((HDMI_CODE_TYPE_VESA == mode) && (code < ARRAY_SIZE(code_vesa)) && (code_vesa[code] >= 0))
            || ((HDMI_CODE_TYPE_CEA == mode) && (code < ARRAY_SIZE(code_cea)) && (code_cea[code] >= 0))) ;
}

/******************************************************************************
* Function:       edid_is_valid_edid
* Description:
* Input:
* Output:
* Return:
*******************************************************************************/
bool edid_is_valid_edid(u8 *edid)
{
    if(memcmp(edid, edid_header, sizeof(edid_header))) {
        return false;
    }

    return true;
}

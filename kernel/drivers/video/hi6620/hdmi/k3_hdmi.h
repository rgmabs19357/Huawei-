/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */

#ifndef __K3_HDMI_H__
#define __K3_HDMI_H__

/* This header file is used by another module for the following function */

typedef enum _hdmi_sample_size {
    HDMI_SAMPLE_16BITS = 0,         /* sample size is 16 bits */
    HDMI_SAMPLE_20BITS,               /* sample size is 20 bits */
    HDMI_SAMPLE_24BITS                /* sample size is 24 bits */
} hdmi_sample_size;

typedef enum _hdmi_core_layout {
    LAYOUT_2CH = 0,     /* audio is 2 channel */
    LAYOUT_3CH,     /* audio is 3 channel */
    LAYOUT_4CH,     /* audio is 4 channel */
    LAYOUT_5CH,     /* audio is 5 channel */
    LAYOUT_6CH,     /* audio is 6 channel */
    LAYOUT_7CH,     /* audio is 7 channel */
    LAYOUT_8CH      /* audio is 8 channel */
} hdmi_core_layout;

int hdmi_audio_set_param(int sample_freq, int sample_size, bool bsio, int layout, int audiotype);
int k3_hdmi_audio_set_power(bool audio_on);
int k3_hdmi_audio_set_param(int sample_freq, int sample_size, bool bsio, int layout, int audiotype);
int hdmi_get_vsync_bycode(int code);
int hdmi_get_hsync_bycode(int code);

#endif


/*
 *  s5k3h2yx_foxconn camera driver head file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
 *  Version:  1.2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _S5K3H2YX_FOXCONN_H
#define _S5K3H2YX_FOXCONN_H

#include "../isp/k3_isp_io.h"
/***********************************************************************
 *
 * s5k3h2yx_foxconn init sensor registers list
 *
 ***********************************************************************/
/* default is 1600*1200 9fps 2lane */
const struct _sensor_reg_t s5k3h2yx_foxconn_init_regs[] = {
	{0x0100,0x00},
	{0x0103,0x01},
	{0x0101,0x00},
	{0x3065,0x35},
	{0x310E,0x00},
	{0x3098,0xAB},
	{0x30C7,0x0A},
	{0x309A,0x01},
	{0x310D,0xC6},
	{0x30C1,0x07},
	{0x30c3,0x40},
	{0x30BB,0x02},
	{0x30BC,0x38},
	{0x30BD,0x40},
	{0x3110,0x70},
	{0x3111,0x80},
	{0x3112,0x7B},
	{0x3113,0xC0},
	{0x30C7,0x1A},
	{0x3000,0x08},
	{0x3001,0x05},
	{0x3002,0x0D},
	{0x3003,0x21},
	{0x3004,0x62},
	{0x3005,0x0B},
	{0x3006,0x6D},
	{0x3007,0x02},
	{0x3008,0x62},
	{0x3009,0x62},
	{0x300A,0x41},
	{0x300B,0x10},
	{0x300C,0x21},
	{0x300D,0x04},
	{0x307E,0x03},
	{0x307F,0xA5},
	{0x3080,0x04},
	{0x3081,0x29},
	{0x3082,0x03},
	{0x3083,0x21},
	{0x3011,0x5F},
	{0x3156,0xE2},
	{0x3027,0xBE},
	{0x300f,0x02},
	{0x3010,0x10},
	{0x3017,0x74},
	{0x3018,0x00},
	{0x3020,0x02},
	{0x3021,0x00},
	{0x3023,0x80},
	{0x3024,0x08},
	{0x3025,0x08},
	{0x301C,0xD4},
	{0x315D,0x00},
	{0x3054,0x00},
	{0x3055,0x35},
	{0x3062,0x04},
	{0x3063,0x38},
	{0x31A4,0x04},
	{0x3016,0x54},
	{0x3157,0x02},
	{0x3158,0x00},
	{0x315B,0x02},
	{0x315C,0x00},
	{0x301B,0x05},
	{0x3028,0x41},
	{0x302A,0x10},
	{0x3060,0x00},
	{0x302D,0x19},
	{0x302B,0x05},
	{0x3072,0x13},
	{0x3073,0x21},
	{0x3074,0x82},
	{0x3075,0x20},
	{0x3076,0xA2},
	{0x3077,0x02},
	{0x3078,0x91},
	{0x3079,0x91},
	{0x307A,0x61},
	{0x307B,0x28},
	{0x307C,0x31},
	{0x304E,0x40},
	{0x304F,0x01},
	{0x3050,0x00},
	{0x3088,0x01},
	{0x3089,0x00},
	{0x3210,0x01},
	{0x3211,0x00},
	{0x308E,0x01},
	{0x308F,0x8F},
	{0x3064,0x03},
	{0x31A7,0x0F},

	{0x0120,0x00},/*global gain*/

	{0x0305,0x04},
	{0x0306,0x00},
	{0x0307,0x6C},
	{0x0303,0x01},
	{0x0301,0x05},
	{0x030B,0x01},
	{0x0309,0x05},
	{0x30CC,0xB0},
	{0x31A1,0x58},
	{0x0344,0x00},
	{0x0345,0x00},
	{0x0346,0x00},
	{0x0347,0x00},
	{0x0348,0x0C},
	{0x0349,0xCF},
	{0x034A,0x09},
	{0x034B,0x9F},
	{0x0381,0x01},
	{0x0383,0x01},
	{0x0385,0x01},
	{0x0387,0x01},
	{0x0401,0x00},
	{0x0405,0x10},
	{0x0700,0x05},
	{0x0701,0x30},
	{0x034C,0x0C},/*width*/
	{0x034D,0xC0},
	{0x034E,0x09},/*height*/
	{0x034F,0x90},
	{0x0200,0x02},
	{0x0201,0x50},
	{0x0202,0x04},
	{0x0203,0xE7},
	{0x0204,0x00},
	{0x0205,0x20},
	{0x0342,0x0D},/*hts*/
	{0x0343,0x8E},
	{0x0340,0x09},/*vts*/
	{0x0341,0xB0},
	{0x300E,0x29},
	{0x31A3,0x00},
	{0x301A,0x77},
	{0x3053,0xCF},
	{0x0100,0x01},
};

/*1600x1200*/
const struct _sensor_reg_t s5k3h2yx_foxconn_framesize_1600x1200[] = {
	//{0x0100,0x01},
};

/*1920x1080*/
const struct _sensor_reg_t s5k3h2yx_foxconn_framesize_1080p[] = {
};

/*RES_3264x2448 full size*/
const struct _sensor_reg_t s5k3h2yx_foxconn_framesize_full[] = {
};

#endif /* S5K3H2YX_FOXCONN_H_INCLUDED */

/************************** END ***************************/


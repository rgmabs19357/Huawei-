/*
 *  Hisilicon K3 soc camera v4l2 driver header file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
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

#ifndef __K3_V4L2_CAPTURE_COMM_H__
#define __K3_V4L2_CAPTURE_COMM_H__

#include <linux/videodev2.h>
#include <linux/semaphore.h>

#define VIDIOC_CHECK_CAP  _IOWR('V', 200, struct v4l2_ext_controls)

/*
 * key and value pair struct
 * used for setting parameters
 */
enum {
	PKEY_IN_WIDTH = 1,	/* camera sensor input width */
	PKEY_IN_HEIGHT,		/* camera sensor input height */
	PKEY_IN_RESOLUTION,
	PKEY_START_X,		/* capture start x position */
	PKEY_START_Y,
	PKEY_START_POS,
	PKEY_OUT_WIDTH,
	PKEY_OUT_HEIGHT,
	PKEY_OUT_RESOLUTION,
	PKEY_OUT_FMT,
	PKEY_MIRROR,
	PKEY_BRIGHT,
	PKEY_CONTRAST,
	PKEY_FRAMERATE,
	PKEY_OUT_STRIDE,
};

#endif /*__K3_V4L2_CAPTURE_H__ */

/********************************* END ***********************************************/

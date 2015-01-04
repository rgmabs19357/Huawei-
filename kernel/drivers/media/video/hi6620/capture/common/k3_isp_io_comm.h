/*
 *  Hisilicon K3 soc camera ISP driver header file
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

#ifndef __K3_ISP_IO_COMM_H__
#define __K3_ISP_IO_COMM_H__

#ifdef CONFIG_HI6620_CAMERA_OV5642
#define CAMERA_ANALOG_VDD   (GPIO_8_4)
#define CAMERA_IO_VCC       (GPIO_8_6)
#define CAMERA_CORE_VDD     (GPIO_8_5)
#define CAMERA_VCM_VCC      (0xFF)           /* not available in B050 */
#else
#define CAMERA_ANALOG_VDD   (GPIO_8_2)
#define CAMERA_IO_VCC       (GPIO_8_3)
#define CAMERA_CORE_VDD     (GPIO_0_6)
#define CAMERA_VCM_VCC      (GPIO_8_1)
#endif

#endif /*__K3_ISP_IO_H__ */

/********************** END **********************/

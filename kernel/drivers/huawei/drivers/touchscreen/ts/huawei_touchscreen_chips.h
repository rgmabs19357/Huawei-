/*
 * Huawei Touchscreen chips
 *
 * Copyright (C) 2013 Huawei Device Co.Ltd
 * License terms: GNU General Public License (GPL) version 2
 *
 */
 /* this file list all support ts chip information */
 
#include "huawei_touchscreen.h"
 
extern struct ts_device_ops ts_synaptics_ops;
extern struct ts_device_ops ts_cypress_ops;

static struct ts_device_data g_ts_device_map[] =
{
	[0] =   {
		.chip_name = "synaptics",
		.irq_gpio = TS_IO_UNDEFINE, //must be defined in dts/boardid
		.irq_config = TS_IRQ_CFG_UNDEFINE,//must be defined in dts/boardid
		.reset_gpio = TS_IO_UNDEFINE,//must be defined in dts/boardid
		.ops = &ts_synaptics_ops,
	},

	[1]	=	{
		.chip_name = "cypress",
		.irq_gpio = TS_IO_UNDEFINE,
		.irq_config = TS_IRQ_CFG_UNDEFINE,
		.reset_gpio = TS_IO_UNDEFINE,
		.ops = &ts_cypress_ops,
	},
};

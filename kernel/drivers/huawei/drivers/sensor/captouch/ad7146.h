/**
 * \file ad7146.h
 * This file is the header file for AD7146 captouch, contains the platform data structure and can be found in the include/linux/input/ad7146.h .
 *
 * AD7146 is very flexible,it can be used as buttons, scrollwheel, slider, touchpad at the same time. That depends on the boards. The platform_data for the device's "struct device" holds this information.
 *
 * Copyright 2013 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */


#define __LINUX_INPUT_AD714X_H__
#include <linux/sched.h>

/**
Register count of AD7146
*/
#define REGCNT     40

/**
This is the platform data for the AD7146 chip used in registration.
This structure is also sent to the I2C client and will be used in the AD7146 probe routine,
Hardware initialization...etc.,
*/
struct ad7146_platform_data {
	unsigned int regs[REGCNT];
	unsigned long irqflags;
	int ad7146_gpio;
};



#ifndef _BALONG_POWER_H
#define _BALONG_POWER_H

#include <linux/platform_device.h>
#include <linux/gpio.h>

enum balong_gpio_index {
	BALONG_RESET,
	BALONG_POWER_ON,
	BALONG_PMU_RESET,
	BALONG_HOST_ACTIVE,
	BALONG_HOST_WAKEUP,
	BALONG_SLAVE_WAKEUP,
	BALONG_POWER_IND,
	BALONG_RESET_IND,
	BALONG_GPIO_NUM
};

struct balong_power_plat_data {
	bool                    flashless;
	struct gpio             gpios[BALONG_GPIO_NUM];
	struct platform_device* echi_device;
	char                   *block_name;
        void**                   post_suspend;
        void**                   pre_resume;
};


/* The state that can be set through FS interface */
#define POWER_SET_DEBUGOFF     	0    /* Only turn off the modem, for debug USE */
#define POWER_SET_DEBUGON      	1    /* Only turn on the modem, for debug USE */
#define POWER_SET_OFF       	2
#define POWER_SET_ON       	3
#define POWER_SET_DL_FINISH     4

/* For usb to call for bus suspend/resume */
extern void balong_power_runtime_idle(void);
extern void balong_power_runtime_resume(void);


#endif /*_balong_POWER_H*/


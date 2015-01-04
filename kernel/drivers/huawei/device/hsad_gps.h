#ifndef _HSAD_DEV_H_
#define _HSAD_DEV_H_
#include <linux/types.h>
extern int hsad_gps_get_gpio(char *name);
extern int hsad_get_gps_en(void);
extern int hsad_get_gps_refclk(void);

#endif /* _HSAD_DEV_H_ */


#ifndef _HSAD_DEV_H_
#define _HSAD_DEV_H_
#include <linux/types.h>
extern int hsad_sensor_get_gpio(char *name);
extern int hsad_sensor_get_type(void);
extern int hsad_compass_softiron_type(void);
extern int hsad_gyro_exist_info(void);
extern int hsad_apds_get_type(void);
extern int hsad_get_cap_exist(void);
extern int hsad_get_hall_exist(void);
extern int hsad_get_akm8963_type(void);
extern int hsad_get_akm09911_type(void);
#endif /* _HSAD_DEV_H_ */

#include <linux/types.h>
#ifndef HSAD_VIBRATOR_H
#define HSAD_VIBRATOR_H

int get_motor_board_type(void);
int get_vibrator_vout_number(void);
int get_vibrator_vout_min_voltage(void);
int get_vibrator_vout_max_voltage(void);

#endif //HSAD_VIBRATOR_H
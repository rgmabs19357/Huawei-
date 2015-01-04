#ifndef _DEV_COMMON_H_
#define _DEV_COMMON_H_

int dev_i2c_add_devices(int busnum, struct i2c_board_info const *devs, int len);

#endif /* _DEV_COMMON_H_ */


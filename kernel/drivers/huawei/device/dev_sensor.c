/*sensor device declare and register, such as touchscreen, keypad, compass, accelerator*/

/*sensor unification for differ platform*/
/*==============================================================================
History

Problem NO.         Name        Time         Reason

==============================================================================*/
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/io.h>
#include <linux/i2c.h>
#include <mach/gpio.h>
#include <mach/boardid.h>

#include "../drivers/sensor/accelerometer/lis3dh.h"
#include "../drivers/sensor/accelerometer/adxl34x.h"
#include "../drivers/sensor/accelerometer/gs_mma8452.h"
#include "../drivers/sensor/gyroscope/l3g4200d.h"
#include "../drivers/sensor/captouch/ad7146.h"
#define CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
#include "../drivers/sensor/accelerometer/lsm330.h"
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_COMPASS_LSM303D
#include "../drivers/sensor/accelerometer/lsm303d.h"
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8975
#include "../drivers/sensor/compass/akm8975.h"
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
#include "../drivers/sensor/compass/akm8963.h"
#endif
#include "../drivers/sensor/light/apds990x.h"
#ifdef CONFIG_HUAWEI_FEATURE_LIGHT_ISL29044
#include "../drivers/sensor/light/isl29044.h"
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM09911
#include "../drivers/sensor/compass/akm09911.h"
#endif
#include <linux/board_sensors.h>
#include "hsad_sensor.h"


unsigned int g_compass_softiron_type = 0;

#define E_SENSOR_TYPE_UEDGE_G_PLUS_VA  1
#define E_SENSOR_TYPE_OSCAR_3G 2
#define E_SENSOR_TYPE_UDP 0
#define E_SENSOR_TYPE_SOPHIA_TL 3
#define E_SENSOR_TYPE_SOPHIA_UL_V1 4

#define COMPASS_LAYOUT 4
#define SENSOR_TYPE 1

static struct lis3dh_acc_platform_data gs_platform_data = {

	.poll_interval = 10,
	.min_interval = 10,

	.g_range = 0x00,

	.axis_map_x = 0,
	.axis_map_y = 1,
	.axis_map_z = 2,

	.negate_x = 1,
	.negate_y = 1,
	.negate_z = 0,

	.gpio_int1 = -1, /* if used this irq,set gpio_int1=GPIO_18_4 */
	.gpio_int2 = -1, /* if used this irq,set gpio_int2=GPIO_6_3	*/
};
struct mma8452_acc_platform_data mma8452_platform_data = {
};


#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AD7146
static struct ad7146_platform_data ad7146_i2c_platform_data = {
        .regs =  {
		0x008037BF,     0x00813FFF,     0x00821600,     0x00832626,
		0x008401F4,     0x00850254,     0x00860258,     0x00870258,
		0x00883FFF,     0x00893DEF,     0x008a3900,     0x008b2626,
		0x008c01F4,     0x008d024B,     0x008e0258,     0x008f0258,
	        ///5
		0x00903BFF,     0x00912FFF,     0x00923c00,     0x00932626,
		0x009401F4,     0x00950254,     0x00960258,     0x00970258,
	        //11
		0x00983FFF,     0x00992EFF,     0x009a3ca4,     0x009b2626,
		0x009c01F4,     0x009d024B,     0x009e0258,     0x009f0258,


		0x0000C030,     0x0002323B,     0x0003A064,     0x00040832,
		0x00050000,     0x00060000,     0x00070001,     0x00010000,
        },

};
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
static struct lsm330_acc_platform_data lsm330_acc_pdata = {
	.fs_range = LSM330_ACC_G_2G,
	.poll_interval = 10,
	.min_interval = LSM330_ACC_MIN_POLL_PERIOD_MS,
	.gpio_int1 = LSM330_ACC_DEFAULT_INT1_GPIO,
	.gpio_int2 = LSM330_ACC_DEFAULT_INT2_GPIO,
};
static struct lsm330_gyr_platform_data lsm330_gyr_pdata = {
	.fs_range = LSM330_GYR_FS_2000DPS,

	.poll_interval = 10,
	.min_interval = LSM330_GYR_MIN_POLL_PERIOD_MS,	/* 2ms */

	.gpio_int1 = LSM330_GYR_DEFAULT_INT1_GPIO,
	.gpio_int2 = LSM330_GYR_DEFAULT_INT2_GPIO,	/* int for fifo */
};
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_COMPASS_LSM303D
static struct lsm303d_acc_platform_data lsm303d_acc_pdata = {
	.fs_range = LSM303D_ACC_FS_2G,
	.axis_map_x = 0,
	.axis_map_y = 1,
	.axis_map_z = 2,
	.negate_x = 0,
	.negate_y = 0,
	.negate_z = 0,
	.poll_interval = 100,
	.min_interval = LSM303D_ACC_MIN_POLL_PERIOD_US,
};
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8975
static struct akm8975_platform_data compass_akm8975_platform_data = {
	.gpio_DRDY = GPIO_15_5 ,/* GPIO-125	*/ 
};
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
static struct akm8963_platform_data compass_akm8963_platform_data = {
	.outbit = 1,
	.gpio_RST = 0,
};
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM09911
static struct akm09911_platform_data compass_akm09911_platform_data = {
	.gpio_RSTN = 0,
};
#endif

static struct l3g4200d_gyr_platform_data l3g4200d_gyr_platform_data = {
	.poll_interval = 10,
	.min_interval = 10,

	.fs_range = 0x30,

	.axis_map_x = 1,
	.axis_map_y = 0,
	.axis_map_z = 2,

	.negate_x = 1,
	.negate_y = 1,
	.negate_z = 0,
};


static struct adxl34x_platform_data adxl34x_default_init = {
	.tap_threshold = 35,
	.tap_duration = 3,
	.tap_latency = 20,
	.tap_window = 20,
	.tap_axis_control = ADXL_TAP_X_EN | ADXL_TAP_Y_EN | ADXL_TAP_Z_EN,
	.act_axis_control = 0xFF,
	.activity_threshold = 6,
	.inactivity_threshold = 4,
	.inactivity_time = 3,
	.free_fall_threshold = 8,
	.free_fall_time = 0x20,
	.data_rate = 10,
	/* .data_rate = 8, */
	.data_range = ADXL_FULL_RES,

	.ev_type = EV_ABS,
	.ev_code_x = ABS_X,    /* EV_REL */
	.ev_code_y = ABS_Y,    /* EV_REL */
	.ev_code_z = ABS_Z,    /* EV_REL */

	.ev_code_tap_x = BTN_TOUCH,    /* EV_KEY */
	.ev_code_tap_y = BTN_TOUCH,    /* EV_KEY */
	.ev_code_tap_z = BTN_TOUCH,    /* EV_KEY */
	.power_mode = ADXL_LINK,
	.fifo_mode = FIFO_STREAM,
	.watermark = 0,
};

struct apds990x_platform_data apds990x_light_platform_data = {
};

static struct i2c_board_info  v9r1_i2c_3_boardinfo[] = {


#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8975
	{
		I2C_BOARD_INFO(AKM8975C_I2C_NAME, AKM8975C_I2C_ADDR),
		.platform_data = &compass_akm8975_platform_data,
	},
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
	{
		I2C_BOARD_INFO(AKM8963_I2C_NAME, AKM8963_I2C_ADDR),
		.platform_data = &compass_akm8963_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM09911
	{
		I2C_BOARD_INFO(AKM_I2C_NAME, AKM09911_I2C_ADDR),
		.platform_data = &compass_akm09911_platform_data,
	},
#endif


#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
	{
		I2C_BOARD_INFO(LSM330_ACC_DEV_NAME,LSM330_ACC_I2C_ADDR),
		.platform_data = &lsm330_acc_pdata,
	},
	{
		I2C_BOARD_INFO(LSM330_GYR_DEV_NAME, LSM330_GYR_I2C_ADDR),  //0x6b
		.platform_data = &lsm330_gyr_pdata,
	},

#endif


#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_YAMAHA_COMPASS
    {
        I2C_BOARD_INFO("yamaha_geomagnetic", 0x2e),//7 bit addr, no write bit
        .platform_data = &yamaha_compass_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ST_LIS3XH
	{
		I2C_BOARD_INFO(LIS3DH_I2C_NAME, LIS3DH_I2C_ADDR),
		.platform_data = &gs_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_MMA8452
	{
		I2C_BOARD_INFO(MMA8452_I2C_NAME, MMA8452_I2C_ADDR),
		.platform_data = &mma8452_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_GYROSCOPE_L3G4200DH
	{
		I2C_BOARD_INFO(L3G4200D_I2C_NAME, L3G4200D_I2C_ADDR),
		.platform_data = &l3g4200d_gyr_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACCELEROMETER_ADI_ADXL346
	{
		I2C_BOARD_INFO(ADXL34X_I2C_NAME, ADXL34X_I2C_ADDR),
		.platform_data = &adxl34x_default_init,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_PROXIMITY_APDS990X
	{
		I2C_BOARD_INFO(APDS990x_I2C_NAME, APDS990x_I2C_ADDR),
		.platform_data = &apds990x_light_platform_data,
	},
#endif

#ifdef CONFIG_HUAWEI_FEATURE_CM3320
       {
        I2C_BOARD_INFO(CM3320_I2C_NAME, CM3320_I2C_ADDR),
       },
#endif

//add three_color_led drivered by tca6507
	{
		I2C_BOARD_INFO("led_colors", 0x45),
    },

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AD7146
{
                I2C_BOARD_INFO("ad7146", AD7146_I2C_ADDR),
                .platform_data = &ad7146_i2c_platform_data,


        },
#endif

#ifdef CONFIG_HUAWEI_FEATURE_LIGHT_ISL29044
	{
		I2C_BOARD_INFO(ISL_DRIVER_NAME, ISL29044_I2C_ADDR),
	},
#endif
};



/* sensor layout init for different board */
void sensor_layout_init(void)
{
	unsigned int sensor_type = SENSOR_TYPE;
	int compass_gpio_num = -1;
	int ps_gpio_num = -1;
	int hand_gpio_num = -1;
	int layout_num = COMPASS_LAYOUT;
	unsigned int compass_softiron_type = 0;

	sensor_type = hsad_sensor_get_type();
	if (-1==sensor_type) {
		pr_err("%s: Failed to get compass_layout number in hsad.",
                   __func__);
		layout_num = SENSOR_TYPE;
	}

	compass_softiron_type = hsad_compass_softiron_type();
	g_compass_softiron_type = compass_softiron_type;

	compass_gpio_num= hsad_sensor_get_gpio("sensor/compass_gpio");
	if (-1 == compass_gpio_num) {
		pr_err("%s: Failed to get compass_gpio number in hsad.",
                   __func__);
    }

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
	compass_akm8963_platform_data.gpio_DRDY = compass_gpio_num;
#endif

	layout_num= hsad_sensor_get_gpio("sensor/compass_layout");
	if (-1==layout_num) {
		pr_err("%s: Failed to get compass_layout number in hsad.",
                   __func__);
		layout_num = COMPASS_LAYOUT;
	}

#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963
	compass_akm8963_platform_data.layout = layout_num;
#endif
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_AKM09911
	compass_akm09911_platform_data.layout = layout_num;
#endif

	ps_gpio_num= hsad_sensor_get_gpio("sensor/proximity_gpio");
	if (-1==ps_gpio_num) {
		 pr_err("%s: Failed to get proximity_gpio number in hsad.",
                   __func__);
	}
	apds990x_light_platform_data.apds990x_gpio = ps_gpio_num;

	hand_gpio_num= hsad_sensor_get_gpio("sensor/ad7146_gpio");
	if (-1==hand_gpio_num) {
		pr_err("%s: Failed to get ad7146_gpio number in hsad.",
                   __func__);
	 }
	ad7146_i2c_platform_data.ad7146_gpio = hand_gpio_num;

	switch (sensor_type) {
		case E_SENSOR_TYPE_UEDGE_G_PLUS_VA:
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
		lsm330_acc_pdata.axis_map_x = 0;
		lsm330_acc_pdata.axis_map_y = 1;
		lsm330_acc_pdata.axis_map_z = 2;
		lsm330_acc_pdata.negate_x = 0;
		lsm330_acc_pdata.negate_y = 1;
		lsm330_acc_pdata.negate_z = 1;
		lsm330_gyr_pdata.axis_map_x =0;
		lsm330_gyr_pdata.axis_map_y = 1;
		lsm330_gyr_pdata.axis_map_z = 2;
		lsm330_gyr_pdata.negate_x = 0;
		lsm330_gyr_pdata.negate_y = 0;
		lsm330_gyr_pdata.negate_z = 1;
 #endif
             gs_platform_data.axis_map_x = 1;
		gs_platform_data.axis_map_y = 0;
		gs_platform_data.axis_map_z = 2;
		gs_platform_data.negate_x = 0;
		gs_platform_data.negate_y = 0;
		gs_platform_data.negate_z = 1;
		mma8452_platform_data.config_mxc_mma_position = 6;
		break;
  
		case E_SENSOR_TYPE_OSCAR_3G:
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
		lsm330_acc_pdata.axis_map_x = 1;
		lsm330_acc_pdata.axis_map_y = 0;
		lsm330_acc_pdata.axis_map_z = 2;
		lsm330_acc_pdata.negate_x = 0;
		lsm330_acc_pdata.negate_y = 1;
		lsm330_acc_pdata.negate_z = 0;
		lsm330_gyr_pdata.axis_map_x =1;
		lsm330_gyr_pdata.axis_map_y = 0;
		lsm330_gyr_pdata.axis_map_z = 2;
		lsm330_gyr_pdata.negate_x = 0;
		lsm330_gyr_pdata.negate_y = 0;
		lsm330_gyr_pdata.negate_z = 0;
#endif
		gs_platform_data.axis_map_x = 1;
		gs_platform_data.axis_map_y = 0;
		gs_platform_data.axis_map_z = 2;
		gs_platform_data.negate_x = 0;
		gs_platform_data.negate_y = 0;
		gs_platform_data.negate_z = 1;
		mma8452_platform_data.config_mxc_mma_position = 6;
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_YAMAHA_COMPASS
		yamaha_compass_platform_data.layout = 0;
#endif
		l3g4200d_gyr_platform_data.negate_x = 0;
		l3g4200d_gyr_platform_data.negate_y = 0;
		l3g4200d_gyr_platform_data.negate_z = 0;
		break;

		case E_SENSOR_TYPE_UDP:
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
		lsm330_acc_pdata.axis_map_x = 0;
		lsm330_acc_pdata.axis_map_y = 1;
		lsm330_acc_pdata.axis_map_z = 2;
		lsm330_acc_pdata.negate_x = 1;
		lsm330_acc_pdata.negate_y = 1;
		lsm330_acc_pdata.negate_z = 0;
		lsm330_gyr_pdata.axis_map_x = 0;
		lsm330_gyr_pdata.axis_map_y = 1;
		lsm330_gyr_pdata.axis_map_z = 2;
		lsm330_gyr_pdata.negate_x = 1;
		lsm330_gyr_pdata.negate_y = 0;
		lsm330_gyr_pdata.negate_z = 0;
#endif
		break;

		case E_SENSOR_TYPE_SOPHIA_TL:
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
		lsm330_acc_pdata.axis_map_x = 1;
		lsm330_acc_pdata.axis_map_y = 0;
		lsm330_acc_pdata.axis_map_z = 2;
		lsm330_acc_pdata.negate_x = 1;
		lsm330_acc_pdata.negate_y = 1;
		lsm330_acc_pdata.negate_z = 1;
		lsm330_gyr_pdata.axis_map_x = 1;
		lsm330_gyr_pdata.axis_map_y = 0;
		lsm330_gyr_pdata.axis_map_z = 2;
		lsm330_gyr_pdata.negate_x = 1;
		lsm330_gyr_pdata.negate_y = 0;
		lsm330_gyr_pdata.negate_z = 1;
#endif
		break;

		case E_SENSOR_TYPE_SOPHIA_UL_V1:
#ifdef CONFIG_HUAWEI_FEATURE_SENSORS_ACC_GYRO_LSM330
		lsm330_acc_pdata.axis_map_x = 1;
		lsm330_acc_pdata.axis_map_y = 0;
		lsm330_acc_pdata.axis_map_z = 2;
		lsm330_acc_pdata.negate_x = 0;
		lsm330_acc_pdata.negate_y = 0;
		lsm330_acc_pdata.negate_z = 1;
		lsm330_gyr_pdata.axis_map_x = 1;
		lsm330_gyr_pdata.axis_map_y = 0;
		lsm330_gyr_pdata.axis_map_z = 2;
		lsm330_gyr_pdata.negate_x = 0;
		lsm330_gyr_pdata.negate_y = 1;
		lsm330_gyr_pdata.negate_z = 1;
#endif
		break;


	default:
		pr_err("sensor_type unsupported\n");
		break;
	}
}

static int __devinit hw_devices_init(void)
{
	sensor_layout_init();

	i2c_register_board_info(3, v9r1_i2c_3_boardinfo, ARRAY_SIZE(v9r1_i2c_3_boardinfo));
	return 0;
}

core_initcall(hw_devices_init);

MODULE_AUTHOR("huawei skf55108");
MODULE_DESCRIPTION("huawei devices init");
MODULE_LICENSE("GPL");

/*****************************************************************************************
* Filename:	hisi_smartstar_coul.c
*
* Discription:  smartstar coulometer functions.
* Copyright: 	(C) 2013 huawei.
*
* revision history:
* 03/25/13 yuanqinshun -v1.0
*
******************************************************************************************/
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/power_supply.h>
#include <linux/power/k3_bq24161.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <asm/irq.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/power/hisi_coul_drv.h>
#include <mach/pmussi_drv.h>
#include <mach/gpio.h>
#include <linux/delay.h>
#include "hisi_battery_data.h"

#if 1 /* for debug */
int v_offset = -42000;
int c_offset = 7000; /*ua*/
#endif

#ifdef _DRV_LLT_
#define SMARTSTAR_COUL_ERR(fmt,args...) do { printf("[smartstar]" fmt, ## args); } while (0)
#define SMARTSTAR_COUL_EVT(fmt,args...) do { printf("[smartstar]" fmt, ## args); } while (0)
#define SMARTSTAR_COUL_INF(fmt,args...) do { printf("[smartstar]" fmt, ## args); } while (0)
#else
#define SMARTSTAR_COUL_ERR(fmt,args...) do { printk(KERN_ERR "[smartstar]" fmt, ## args); } while (0)
#define SMARTSTAR_COUL_EVT(fmt,args...) do { printk(KERN_INFO "[smartstar]" fmt, ## args); } while (0)
#define SMARTSTAR_COUL_INF(fmt,args...) do { printk(KERN_INFO "[smartstar]" fmt, ## args); } while (0)
#endif

#define DI_LOCK()    do {mutex_lock(&di->soc_mutex);} while (0)
#define DI_UNLOCK()  do {mutex_unlock(&di->soc_mutex);} while (0)


#define ABNORMAL_BATT_TEMPERATURE_LOW   (-30)
#define ABNORMAL_BATT_TEMPERATURE_HIGH  (60)

#define BATTERY_CC_WARNING_LEV  10
#define BATTERY_CC_LOW_LEV      5

#define BATTERY_EXIST_FLAG  0x1


#define BATTERY_MOVE_MAGIC_NUM        0xc3


#define TEMP_TOO_HOT            (60)
#define TEMP_TOO_COLD          (-20)


#define CHARGING_STATE_CHARGE_START         (1)
#define CHARGING_STATE_CHARGE_DONE          (2)
#define CHARGING_STATE_CHARGE_STOP          (3)
#define CHARGING_STATE_CHARGE_RECHARGE      (4)
#define CHARGING_STATE_CHARGE_UNKNOW        (0x0)

#define SMARTSTAR_DEBUG

#define IAVG_SAMPLES 16
#define CHARGING_IAVG_MA 250

#define R_COUL_MOHM     10  /* resisitance mohm */

/************************************************************
    coul register of smartstar
************************************************************/
#define SMARTSTAR_REG_READ(regAddr)             pmussi_reg_read(regAddr)
#define SMARTSTAR_REG_WRITE(regAddr,regval)     pmussi_reg_write((unsigned int)(regAddr),(char)regval)

#define SMARTSTAR_REGS_READ(regAddr,buf,size)   pmussi_recv_data((unsigned int)(regAddr),(char*)(buf),(int)(size))
#define SMARTSTAR_REGS_WRITE(regAddr,buf,size)  pmussi_send_data((unsigned int)(regAddr),(char*)(buf),(int)(size))

#define COUL_CTRL_ENABLE     (1<<7)
#define COUL_CALI_ENABLE     (1<<6)
#define COUL_ECO_FLT_20MS    (0)
#define COUL_ECO_FLT_25MS    (0x1<<4)
#define COUL_ECO_FLT_30MS    (0x2<<4)
#define COUL_ECO_FLT_35MS    (0x3<<4)
#define COUL_ALL_REFLASH    (0x0)
#define COUL_ECO_REFLASH    (0x1<<3)
#define COUL_ECO_ENABLE     (0x1<<2)
#define COUL_ECO_PMU_EN     (0x3)   /*enable ECO with PMU, and enable signal filter*/
#define COUL_ECO_DISABLE    (0x0)

#define DEFAULT_COUL_CTRL_VAL   (COUL_CTRL_ENABLE | COUL_ECO_FLT_20MS  \
                                | COUL_ALL_REFLASH |COUL_ECO_DISABLE)


#define  COUL_VBAT_LOW_INT      (0x1<<5)
#define  COUL_LOAD_TIMER_INT    (0x1<<4)
#define  COUL_CHG_TIMER_INT     (0x1<<3)
#define  COUL_CCIN_CNT_INT      (0x1<<2)
#define  COUL_CCOUT_CNT_INT     (0x1<<1)
#define  COUL_CCOUT_BIG_INT     (0x1<<0)

#define DEFAULT_INT_MASK_VAL    (0x0)

#define SMARTSTAR_COUL_IRQ_REG      0x007
#define SMARTSTAR_COUL_IRQ_MASK_REG 0x00c

#define SMARTSTAR_COUL_CTRL_REG 0x133
#define SMARTSTAR_CL_OUT_BASE   0x139
#define SMARTSTAR_CL_IN_BASE    0x135
#define SMARTSTAR_CHG_TIMER_BASE 0x141
#define SMARTSTAR_LOAD_TIMER_BASE 0x13d
#define SMARTSTAR_CL_INT_BASE 0x149
#define SMARTSTAR_VOL_INT_BASE    0x14d
#define SMARTSTAR_OFFSET_VOLTAGE 0x151
#define SMARTSTAR_OCV_REG_BASE  0x153
#define SMARTSTAR_VOL_FIFO_BASE 0x155
#define SMARTSTAR_CUR_FIFO_BASE 0x17d
#define SMARTSTAR_FIFO_CLEAR 0x1a7
#define SMARTSTAR_BATTERY_MOVE_ADDR 0x1a8

#define SMARTSTAR_LOW_VOL_INT_LVL1_SOC      (15)
#define SMARTSTAR_LOW_VOL_INT_LVL2_SOC      (2)
#define SMARTSTAR_LOW_VOL_INT_LVL1_FLAG    (1<<0)
#define SMARTSTAR_LOW_VOL_INT_LVL2_FLAG    (1<<1)
#define SMARTSTAR_LOW_VOL_INT_MASK   (SMARTSTAR_LOW_VOL_INT_LVL1_FLAG | SMARTSTAR_LOW_VOL_INT_LVL2_FLAG)

#ifdef SMARTSTAR_DEBUG
#define DBG_CNT_INC(xxx)     di->xxx++
#else
#define DBG_CNT_INC(xxx)
#endif

struct smartstar_coul_device
{
    int flag;
    int prev_pc_unusable;
    int irq;
    int batt_ocv_cur_limit;
    int batt_ocv_curreglimit;
    int batt_ocv; // ocv in uv
    int batt_changed_flag;
    int batt_vol_low_flag;
    int soc_limit_flag;
    int batt_temp; // temperature in degree*10
    int batt_fcc;
    int batt_rm;
    int batt_uuc;
    int charging_begin_soc;
    int charging_state;
    unsigned int batt_soc;
    unsigned int batt_id_vol;
    unsigned int batt_chargecycles; //chargecycle in percent
    unsigned int cc_end_value;
    unsigned int cc_start_value;
    unsigned int v_cutoff;
    unsigned long	get_cc_start_time;
    unsigned long 	get_cc_end_time;
    unsigned long   suspend_time; // time when suspend
    long charging_begin_cc;  /*the unit is uah*/
    long suspend_cc; // cc when suspend
    struct mutex soc_mutex;
    struct hisi_smartstar_coul_battery_data *batt_data;
    struct single_row_lut	*adjusted_fcc_temp_lut;
    struct delayed_work	notifier_work;
    struct delayed_work	calculate_soc_delayed_work;
    struct hisi_coul_ops *   ops;

#ifdef SMARTSTAR_DEBUG
    unsigned int dbg_ocv_cng_0; /*ocv change count by wake up*/
    unsigned int dbg_ocv_cng_1; /*ocv change count by full charged*/
    unsigned int dbg_valid_vol; /*vaild voltage from FIFO vol registers*/
    unsigned int dbg_invalid_vol; /*invaild voltage from FIFO vol registers*/
    unsigned int dbg_ocv_fc_failed; /*full charged can't update OCV*/
#endif
};

#ifdef _DRV_LLT_
struct smartstar_coul_device *g_smartstar_coul_dev = NULL;
#else
static struct smartstar_coul_device *g_smartstar_coul_dev = NULL;
#endif

#define CHARGECYCLES_NAME  "CHGCYCS"
#define CHARGECYCLES_NUM   (0) // TODO: nv num = ?
#define CHARGECYCLES_SIZE  (4)

#define MIN_BEGIN_PERCENT_FOR_LEARNING 30


int delta_sleep_time = 100; // sleep time bigger could update ocv, in s
int delta_sleep_current = 50; // sleep current less could updat eocv, in mA
int delta_ocv_update_time = 2*60; // min time between ocv update, in s

#ifndef _DRV_LLT_
module_param(delta_sleep_time, int, 0644);
module_param(delta_ocv_update_time, int, 0644);
module_param(delta_sleep_current, int, 0644);

static int batt_id_voltage; // in mV

static int ro_ops_set(const char *buffer, const struct kernel_param *kp)
{
    return -EINVAL;
}

static int batt_id_voltage_ops_get(char *buffer, const struct kernel_param *kp)
{
    // TODO: HKADC batt_id_voltage

    sprintf(buffer, "%d mV", batt_id_voltage);
    return 0;
}
static struct kernel_param_ops batt_id_voltage_ops={
    .set = ro_ops_set,
    .get = batt_id_voltage_ops_get,
};

module_param_cb(batt_id_voltage, &batt_id_voltage_ops,&batt_id_voltage, 0444);

#endif

/**
 * clear_cc_register
 *
 * clear the cc register
 */
static void clear_cc_register(void)
{
	long ccregval = 0;
    SMARTSTAR_REGS_WRITE(SMARTSTAR_CL_IN_BASE,&ccregval,4);
    SMARTSTAR_REGS_WRITE(SMARTSTAR_CL_OUT_BASE,&ccregval,4);
}

/**
 * convert_regval2uah
 * 1bit = 1bit current * 0.11 c = 5/10661 * 11/100 c = 5/10661 * 11/100 * 1000/3600 mAh
 *       = 11 / (10661*2*36) mAh = 11 * 1000/ (10661 *2 *36) uAh
 *       = 11 * 125/ (10661* 9) uAh
 * convert battery voltage to uah
 */
static long convert_regval2uah(unsigned long reg_val)
{
    long ret;
    s64 temp;

    temp = reg_val;
    temp = temp * 11 *125;
    temp = div_s64(temp, (10661*9));

    ret = temp / (R_COUL_MOHM/10);

    return ret;
}

/**
 * smartstar_battery_voltage
 *
 * battery voltage in milivolts
 */
static long calculate_cc_uah(void)
{
	unsigned long cc_in = 0;
	unsigned long cc_out= 0;
	long cc_uah = 0;

    SMARTSTAR_REGS_READ(SMARTSTAR_CL_IN_BASE,&cc_in,4);
    SMARTSTAR_REGS_READ(SMARTSTAR_CL_OUT_BASE,&cc_out,4);

    cc_uah = convert_regval2uah(cc_out);
    cc_uah = cc_uah - convert_regval2uah(cc_in);

	return cc_uah;
}

/*
 *	from coul get battery cl_in or cl_out.
 */
static void clear_coul_time(void)
{
    unsigned long cl_time = 0;

    SMARTSTAR_REGS_WRITE(SMARTSTAR_CHG_TIMER_BASE,&cl_time ,4);
    SMARTSTAR_REGS_WRITE(SMARTSTAR_LOAD_TIMER_BASE,&cl_time ,4);
}


/*
 *	from coul get battery cl_in or cl_out.
 */
static unsigned long get_coul_time(void)
{
    unsigned long cl_in_time, cl_out_time;

    SMARTSTAR_REGS_READ(SMARTSTAR_CHG_TIMER_BASE,&cl_in_time,4);
    SMARTSTAR_REGS_READ(SMARTSTAR_LOAD_TIMER_BASE,&cl_out_time,4);

    return (cl_in_time + cl_out_time);
}

/**
 * convert_regval2uv
 * 1 bit = 225.1196 uv = 4.8/21322 V = 4.8/21322 * 1000 * 1000 uV = 24 * 1000 * 100/ 10661 uV
 * convert regval to uv
 */
static  int convert_regval2uv(short reg_val)
{
    s64 temp;

    if (reg_val & 0x8000) {
        return -1;
    }

    temp = (s64)((s64)(reg_val)  * (s64)(24 * 1000 * 100));

    temp = div_s64(temp, 10661);

#if 1 /* for debug */
    temp += v_offset;
#endif

    return (int)temp;
}

/**
 * convert_uv2regval
 * 1 uv = 10661 / 24 * 1000 * 100 bit
 * convert uv to regval
 */
static  short convert_uv2regval(int uv_val)
{
    short ret;
    s64 temp;

    temp = (s64)((s64)uv_val * (s64)10661);
    temp = div_s64(temp,2400000);

    ret = (short)temp;

    return ret;
}

/**
 * smartstar_battery_voltage_uv
 *
 * battery voltage in uv
 */
static int smartstar_battery_voltage_uv(void)
{
    short regval;

    SMARTSTAR_REGS_READ(SMARTSTAR_VOL_FIFO_BASE, &regval, 2);

    return(convert_regval2uv(regval));
}

/**
 * convert_regval2ua
 * 10 mohm resistance: 1 bit = 5/10661 A = 5*1000*1000 / 10661 uA
 * 20 mohm resistance: 1 bit = 10 mohm / 2
 * 30 mohm resistance: 1 bit = 10 mohm / 3
 * ...
 * high bit = 0 is in, 1 is out
 * convert regval to ua
 */
static  int convert_regval2ua(short reg_val)
{
    int ret;
    s64 temp;

    ret = reg_val;
    temp = (s64)(ret) * (s64)(1000 * 1000 * 5);
    temp = div_s64(temp, 10661);

    ret = temp / (R_COUL_MOHM/10);

    ret = -ret;

#if 1 /* for debug */
    ret += c_offset;
#endif

    return ret;
}
/**
 * convert_ua2regval
 *
 * 10 mohm resistance: 1 bit = 5/10661 A = 5*1000*1000 / 10661 uA
 * 20 mohm resistance: 1 bit = 10 mohm / 2
 * 30 mohm resistance: 1 bit = 10 mohm / 3
 */
static  short convert_ua2regval(int ua)
{
    s64 temp;
    short regval;

    temp = ((s64)(ua) * (s64)(10661 * (R_COUL_MOHM/10)));
    temp = div_s64(temp,5000000);

    regval = (short)(-temp);

    return regval;
}

/**
 * smartstar_battery_current_ua - return the current of battery.
 *
 * return the battery current in uA.
 */
int smartstar_battery_current_ua(void)
{
    short regval;

    SMARTSTAR_REGS_READ(SMARTSTAR_CUR_FIFO_BASE, &regval, 2);

    return convert_regval2ua(regval);
}


static int is_between(int left, int right, int value)
{
	if ((left >= right) && (left >= value) && (value >= right))
		return 1;
	if ((left <= right) && (left <= value) && (value <= right))
		return 1;

	return 0;
}

static int linear_interpolate(int y0, int x0, int y1, int x1, int x)
{
	if ((y0 == y1) || (x == x0))
		return y0;
	if ((x1 == x0) || (x == x1))
		return y1;

	return y0 + ((y1 - y0) * (x - x0) / (x1 - x0));
}

static int interpolate_single_lut(struct single_row_lut *lut, int x)
{
	int i, result;

	if (x < lut->x[0]) {
		return lut->y[0];
	}
	if (x > lut->x[lut->cols - 1]) {
		return lut->y[lut->cols - 1];
	}

	for (i = 0; i < lut->cols; i++)
		if (x <= lut->x[i])
			break;
	if (x == lut->x[i]) {
		result = lut->y[i];
	} else {
		result = linear_interpolate(
			lut->y[i - 1],
			lut->x[i - 1],
			lut->y[i],
			lut->x[i],
			x);
	}
	return result;
}

static int interpolate_single_y_lut(struct single_row_lut *lut, int y)
{
	int i, result;

	if (y < lut->y[0]) {
		return lut->x[0];
	}
	if (y > lut->y[lut->cols - 1]) {
		return lut->x[lut->cols - 1];
	}

	for (i = 0; i < lut->cols; i++)
		if (y <= lut->y[i])
			break;
	if (y == lut->y[i]) {
		result = lut->x[i];
	} else {
		result = linear_interpolate(
			lut->x[i - 1],
			lut->y[i - 1],
			lut->x[i],
			lut->y[i],
			y);
	}
	return result;
}

static int interpolate_scalingfactor(struct sf_lut *sf_lut,
				int row_entry, int pc)
{
	int i, scalefactorrow1, scalefactorrow2, scalefactor;
	int rows, cols;
	int row1 = 0;
	int row2 = 0;

	/*
	 * sf table could be null when no battery aging data is available, in
	 * that case return 100%
	 */
	if (!sf_lut)
		return 100;

	rows = sf_lut->rows;
	cols = sf_lut->cols;
	if (pc > sf_lut->percent[0]) {
		SMARTSTAR_COUL_EVT("pc %d greater than known pc ranges for sfd\n", pc);
		row1 = 0;
		row2 = 0;
	}
	if (pc < sf_lut->percent[rows - 1]) {
		SMARTSTAR_COUL_EVT("pc %d less than known pc ranges for sf\n", pc);
		row1 = rows - 1;
		row2 = rows - 1;
	}
	for (i = 0; i < rows; i++) {
		if (pc == sf_lut->percent[i]) {
			row1 = i;
			row2 = i;
			break;
		}
		if (pc > sf_lut->percent[i]) {
			row1 = i - 1;
			row2 = i;
			break;
		}
	}

	if (row_entry < sf_lut->row_entries[0])
		row_entry = sf_lut->row_entries[0];
	if (row_entry > sf_lut->row_entries[cols - 1])
		row_entry = sf_lut->row_entries[cols - 1];

	for (i = 0; i < cols; i++)
		if (row_entry <= sf_lut->row_entries[i])
			break;
	if (row_entry == sf_lut->row_entries[i]) {
		scalefactor = linear_interpolate(
				sf_lut->sf[row1][i],
				sf_lut->percent[row1],
				sf_lut->sf[row2][i],
				sf_lut->percent[row2],
				pc);
		return scalefactor;
	}

	scalefactorrow1 = linear_interpolate(
				sf_lut->sf[row1][i - 1],
				sf_lut->row_entries[i - 1],
				sf_lut->sf[row1][i],
				sf_lut->row_entries[i],
				row_entry);

	scalefactorrow2 = linear_interpolate(
				sf_lut->sf[row2][i - 1],
				sf_lut->row_entries[i - 1],
				sf_lut->sf[row2][i],
				sf_lut->row_entries[i],
				row_entry);

	scalefactor = linear_interpolate(
				scalefactorrow1,
				sf_lut->percent[row1],
				scalefactorrow2,
				sf_lut->percent[row2],
				pc);

	return scalefactor;
}


static void get_simultaneous_battery_voltage_and_current(struct smartstar_coul_device *di, int *ibat_ua, int *vbat_uv)
{
    int vol[3], cur[3];
    int i;
    for (i=0; i<3; i++){
        vol[i] = smartstar_battery_voltage_uv();
        cur[i] = smartstar_battery_current_ua();
    }

    if (vol[0]==vol[1] && cur[0]==cur[1]){
        *ibat_ua = cur[0];
        *vbat_uv = vol[0];
    } else if (vol[1]==vol[2] && cur[1]==cur[2]){
        *ibat_ua = cur[1];
        *vbat_uv = vol[1];
    } else {
        *ibat_ua = cur[2];
        *vbat_uv = vol[2];
    }

}



/**
 * interpolate_fcc
 *
 * look for fcc value by battery temperature
 */
static int interpolate_fcc(struct smartstar_coul_device *di, int batt_temp)
{
	/* batt_temp is in tenths of degC - convert it to degC for lookups */
	batt_temp = batt_temp/10;
	return interpolate_single_lut(di->batt_data->fcc_temp_lut, batt_temp);
}

/**
 * interpolate_scalingfactor_fcc
 *
 * look for fcc scaling factory value by battery charge cycles
 */
static int interpolate_scalingfactor_fcc(struct smartstar_coul_device *di,
								int cycles)
{
	/*
	 * sf table could be null when no battery aging data is available, in
	 * that case return 100%
	 */
	if (di->batt_data->fcc_sf_lut)
		return interpolate_single_lut(di->batt_data->fcc_sf_lut, cycles);
	else
		return 100;
}

static int interpolate_fcc_adjusted(struct smartstar_coul_device *di, int batt_temp)
{
	/* batt_temp is in tenths of degC - convert it to degC for lookups */
	batt_temp = batt_temp/10;
	return interpolate_single_lut(di->adjusted_fcc_temp_lut, batt_temp);
}

static int calculate_fcc_uah(struct smartstar_coul_device *di, int batt_temp,
							int chargecycles)
{
    int initfcc, result, scalefactor = 0;

    if (di->adjusted_fcc_temp_lut == NULL) {
        initfcc = interpolate_fcc(di, batt_temp);
        scalefactor = interpolate_scalingfactor_fcc(di, chargecycles);

        /* Multiply the initial FCC value by the scale factor. */
        result = (initfcc * scalefactor * 1000) / 100;

    } else {
		return 1000 * interpolate_fcc_adjusted(di, batt_temp);
    }

    return result;
}

static int interpolate_pc(struct pc_temp_ocv_lut *lut,
				int batt_temp, int ocv)
{
    int i, j, pcj, pcj_minus_one, pc;
    int rows = lut->rows;
    int cols = lut->cols;

    /* batt_temp is in tenths of degC - convert it to degC for lookups */
    batt_temp = batt_temp/10;

    if (batt_temp < lut->temp[0]) {
    	SMARTSTAR_COUL_ERR("batt_temp %d < known temp range for pc\n", batt_temp);
    	batt_temp = lut->temp[0];
    }
    if (batt_temp > lut->temp[cols - 1]) {
    	SMARTSTAR_COUL_ERR("batt_temp %d > known temp range for pc\n", batt_temp);
    	batt_temp = lut->temp[cols - 1];
    }

    for (j = 0; j < cols; j++)
    	if (batt_temp <= lut->temp[j])
    		break;
    if (batt_temp == lut->temp[j]) {
    	/* found an exact match for temp in the table */
    	if (ocv >= lut->ocv[0][j])
    		return lut->percent[0];
    	if (ocv <= lut->ocv[rows - 1][j])
    		return lut->percent[rows - 1];
    	for (i = 0; i < rows; i++) {
    		if (ocv >= lut->ocv[i][j]) {
    			if (ocv == lut->ocv[i][j])
    				return lut->percent[i];
    			pc = linear_interpolate(
    				lut->percent[i],
    				lut->ocv[i][j],
    				lut->percent[i - 1],
    				lut->ocv[i - 1][j],
    				ocv);
    			return pc;
    		}
    	}
    }

    /*
     * batt_temp is within temperature for
     * column j-1 and j
     */
    if (ocv >= lut->ocv[0][j])
    	return lut->percent[0];
    if (ocv <= lut->ocv[rows - 1][j - 1])
    	return lut->percent[rows - 1];

    pcj_minus_one = 0;
    pcj = 0;
    for (i = 0; i < rows-1; i++) {
    	if (pcj == 0
    		&& is_between(lut->ocv[i][j],
    			lut->ocv[i+1][j], ocv)) {
    		pcj = linear_interpolate(
    			lut->percent[i],
    			lut->ocv[i][j],
    			lut->percent[i + 1],
    			lut->ocv[i+1][j],
    			ocv);
    	}

    	if (pcj_minus_one == 0
    		&& is_between(lut->ocv[i][j-1],
    			lut->ocv[i+1][j-1], ocv)) {

    		pcj_minus_one = linear_interpolate(
    			lut->percent[i],
    			lut->ocv[i][j-1],
    			lut->percent[i + 1],
    			lut->ocv[i+1][j-1],
    			ocv);
    	}

    	if (pcj && pcj_minus_one) {
    		pc = linear_interpolate(
    			pcj_minus_one,
    			lut->temp[j-1],
    			pcj,
    			lut->temp[j],
    			batt_temp);
    		return pc;
    	}
    }

    if (pcj)
    	return pcj;

    if (pcj_minus_one)
    	return pcj_minus_one;

    SMARTSTAR_COUL_ERR("%d ocv wasn't found for temp %d in the LUT returning 100%%\n",
                                            ocv, batt_temp);
    return 100;
}


static int calculate_pc(struct smartstar_coul_device *di, int ocv_uv, int batt_temp,
							int chargecycles)
{
    int pc, scalefactor;

    pc = interpolate_pc(di->batt_data->pc_temp_ocv_lut, batt_temp, ocv_uv / 1000);

    scalefactor = interpolate_scalingfactor(di->batt_data->pc_sf_lut, chargecycles, pc);

    /* Multiply the initial FCC value by the scale factor. */
    pc = (pc * scalefactor) / 100;
    return pc;
}

static int calculate_remaining_charge_uah(struct smartstar_coul_device *di,
						int fcc_uah, int batt_temp,
						int chargecycles)
{
    int  ocv, pc;

    ocv = di->batt_ocv;
    pc = calculate_pc(di, ocv, batt_temp, chargecycles);
    return (fcc_uah * pc) / 100;
}


static int get_rbatt(struct smartstar_coul_device *di, int soc_rbatt, int batt_temp)
{
	int rbatt, scalefactor;

	rbatt = di->batt_data->default_rbatt_mohm;
	if (di->batt_data->rbatt_sf_lut == NULL)  {
		return rbatt;
	}
	/* Convert the batt_temp to DegC from deciDegC */
	batt_temp = batt_temp / 10;
	scalefactor = interpolate_scalingfactor(di->batt_data->rbatt_sf_lut,
							batt_temp, soc_rbatt);
	rbatt = (rbatt * scalefactor) / 100;

	if (is_between(20, 10, soc_rbatt))
		rbatt = rbatt
			+ ((20 - soc_rbatt) * di->batt_data->delta_rbatt_mohm) / 10;
	else
		if (is_between(10, 0, soc_rbatt))
			rbatt = rbatt + di->batt_data->delta_rbatt_mohm;

	return rbatt;
}

/* get ocv given a soc  -- reverse lookup */
static int interpolate_ocv(struct pc_temp_ocv_lut *lut,
				int batt_temp_degc, int pc)
{
	int i, ocvrow1, ocvrow2, ocv;
	int rows, cols;
	int row1 = 0;
	int row2 = 0;

	rows = lut->rows;
	cols = lut->cols;
	if (pc > lut->percent[0]) {
		SMARTSTAR_COUL_EVT("pc %d greater than known pc ranges for sfd\n", pc);
		row1 = 0;
		row2 = 0;
	}
	if (pc < lut->percent[rows - 1]) {
		SMARTSTAR_COUL_EVT("pc %d less than known pc ranges for sf\n", pc);
		row1 = rows - 1;
		row2 = rows - 1;
	}
	for (i = 0; i < rows; i++) {
		if (pc == lut->percent[i]) {
			row1 = i;
			row2 = i;
			break;
		}
		if (pc > lut->percent[i]) {
			row1 = i - 1;
			row2 = i;
			break;
		}
	}

	if (batt_temp_degc < lut->temp[0])
		batt_temp_degc = lut->temp[0];
	if (batt_temp_degc > lut->temp[cols - 1])
		batt_temp_degc = lut->temp[cols - 1];

	for (i = 0; i < cols; i++)
		if (batt_temp_degc <= lut->temp[i])
			break;
	if (batt_temp_degc == lut->temp[i]) {
		ocv = linear_interpolate(
				lut->ocv[row1][i],
				lut->percent[row1],
				lut->ocv[row2][i],
				lut->percent[row2],
				pc);
		return ocv;
	}

	ocvrow1 = linear_interpolate(
				lut->ocv[row1][i - 1],
				lut->temp[i - 1],
				lut->ocv[row1][i],
				lut->temp[i],
				batt_temp_degc);

	ocvrow2 = linear_interpolate(
				lut->ocv[row2][i - 1],
				lut->temp[i - 1],
				lut->ocv[row2][i],
				lut->temp[i],
				batt_temp_degc);

	ocv = linear_interpolate(
				ocvrow1,
				lut->percent[row1],
				ocvrow2,
				lut->percent[row2],
				pc);

	return ocv;
}


static int calculate_termination_uuc(struct smartstar_coul_device *di,
				 int batt_temp, int chargecycles,
				int fcc_uah, int i_ma,
				int *ret_pc_unusable)
{
	int unusable_uv, pc_unusable, uuc;
	int i = 0;
	int ocv_mv;
	int batt_temp_degc = batt_temp / 10;
	int rbatt_mohm;
	int delta_uv;
	int prev_delta_uv = 0;
	int prev_rbatt_mohm = 0;
	int prev_ocv_mv = 0;
	int uuc_rbatt_uv;

	for (i = 0; i <= 100; i++) {
		ocv_mv = interpolate_ocv(di->batt_data->pc_temp_ocv_lut, batt_temp_degc, i);
		rbatt_mohm = get_rbatt(di, i, batt_temp);
		unusable_uv = (rbatt_mohm * i_ma) + (di->v_cutoff * 1000);
		delta_uv = ocv_mv * 1000 - unusable_uv;

		if (delta_uv > 0)
			break;

		prev_delta_uv = delta_uv;
		prev_rbatt_mohm = rbatt_mohm;
		prev_ocv_mv = ocv_mv;
	}

	uuc_rbatt_uv = linear_interpolate(rbatt_mohm, delta_uv,
					prev_rbatt_mohm, prev_delta_uv,
					0);

	unusable_uv = (uuc_rbatt_uv * i_ma) + (di->v_cutoff * 1000);

	pc_unusable = calculate_pc(di, unusable_uv, batt_temp, chargecycles);
	uuc = (fcc_uah * pc_unusable) / 100;
	*ret_pc_unusable = pc_unusable;
	return uuc;
}

static int adjust_uuc(struct smartstar_coul_device *di, int fcc_uah,
			int new_pc_unusable,
			int new_uuc,
			int batt_temp,
			int rbatt,
			int *iavg_ma)
{
	int new_unusable_mv;
	int batt_temp_degc = batt_temp / 10;

	if (di->prev_pc_unusable == -EINVAL
		|| abs(di->prev_pc_unusable - new_pc_unusable) <= 1) {
		di->prev_pc_unusable = new_pc_unusable;
		return new_uuc;
	}

	/* the uuc is trying to change more than 1% restrict it */
	if (new_pc_unusable > di->prev_pc_unusable)
		di->prev_pc_unusable++;
	else
		di->prev_pc_unusable--;

	new_uuc = (fcc_uah * di->prev_pc_unusable) / 100;

	/* also find update the iavg_ma accordingly */
	new_unusable_mv = interpolate_ocv(di->batt_data->pc_temp_ocv_lut, batt_temp_degc,
						di->prev_pc_unusable);
	if (new_unusable_mv < di->v_cutoff)
		new_unusable_mv = di->v_cutoff;

	*iavg_ma = (new_unusable_mv - di->v_cutoff) * 1000 / rbatt;
	if (*iavg_ma == 0)
		*iavg_ma = 1;

	return new_uuc;
}

static int calculate_unusable_charge_uah(struct smartstar_coul_device *di,
				int rbatt, int fcc_uah, int cc_uah,
				int soc_rbatt, int batt_temp, int chargecycles,
				int iavg_ua)
{
	int uuc_uah_iavg;
	int i;
	int iavg_ma = iavg_ua / 1000;
	static int iavg_samples[IAVG_SAMPLES];
	static int iavg_index;
	static int iavg_num_samples;
	int pc_unusable;

	/*
	 * if we are charging use a nominal avg current so that we keep
	 * a reasonable UUC while charging
	 */
	if (iavg_ma < 0)
		iavg_ma = CHARGING_IAVG_MA;
	iavg_samples[iavg_index] = iavg_ma;
	iavg_index = (iavg_index + 1) % IAVG_SAMPLES;
	iavg_num_samples++;
	if (iavg_num_samples >= IAVG_SAMPLES)
		iavg_num_samples = IAVG_SAMPLES;

	/* now that this sample is added calcualte the average */
	iavg_ma = 0;
	if (iavg_num_samples != 0) {
		for (i = 0; i < iavg_num_samples; i++) {
			iavg_ma += iavg_samples[i];
		}

		iavg_ma = DIV_ROUND_CLOSEST(iavg_ma, iavg_num_samples);
	}

	uuc_uah_iavg = calculate_termination_uuc(di,
					batt_temp, chargecycles,
					fcc_uah, iavg_ma,
					&pc_unusable);

    SMARTSTAR_COUL_INF("UUC before adjust=%d uAh, iavg_ma=%d mA, pc=%d\n", uuc_uah_iavg, iavg_ma, pc_unusable);

	/* restrict the uuc such that it can increase only by one percent */
	uuc_uah_iavg = adjust_uuc(di, fcc_uah, pc_unusable, uuc_uah_iavg,
					batt_temp, rbatt, &iavg_ma);

	/* find out what the avg current should be for this uuc */
	/*di->prev_uuc_iavg_ma = iavg_ma;*/
	di->batt_uuc = uuc_uah_iavg;

	return uuc_uah_iavg;
}

/**
 * recalc_chargecycles - recalculate the chargecycle
 * @di: stmartstar coul device
 *
 */
static unsigned int recalc_chargecycles(struct smartstar_coul_device *di)
{
    int cc_end, real_fcc, fcc, temp, pc, new_chargecycles;
    unsigned int retval = 0;

    if (di->batt_soc==100 && di->charging_begin_soc<MIN_BEGIN_PERCENT_FOR_LEARNING) {
        cc_end = calculate_cc_uah();
        temp = di->batt_temp;
        real_fcc = (cc_end - di->charging_begin_cc)*100/(100 - di->charging_begin_soc);
        fcc = interpolate_fcc(di,temp);
        pc = real_fcc *100 / fcc;
        new_chargecycles = interpolate_single_y_lut(di->batt_data->fcc_sf_lut, pc);
        new_chargecycles -= 40*100;
        retval = (unsigned int)(new_chargecycles>0?new_chargecycles:0);

        SMARTSTAR_COUL_EVT("trigger battery charge cycle reclac, val = %d!\n", new_chargecycles);
    }

    return retval;
}

static unsigned int get_chargecycles(struct smartstar_coul_device *di)
{
    return 0;
}

static void save_chargecycles(struct smartstar_coul_device *di)
{
    // TODO:
    return;
}

static void update_chargecycles(struct smartstar_coul_device *di)
{
    if (di->batt_soc - di->charging_begin_soc > 0) {
        di->batt_chargecycles += di->batt_soc - di->charging_begin_soc;
        /* save chargecycles to nv */
        save_chargecycles(di);
    }
}









/**
 * is_smartstar_coul_ready -
 *
 * 0:not ready, 1: ready
 */
int is_smartstar_coul_ready(void)
{
    // TODO: do something here ?
    return 1;
}

/**
 * hisi_smartstar_temperature
 *
 * return the battery temperature in centigrade.
 */
int smartstar_battery_temperature_tenth_degree(void)
{
    /*
    int temperature;
    temperature= hkadc_battery_temperature();
    return temperature;
    */

    return 250; /*return 25 degree*/
}

/**
 * hisi_smartstar_temperature
 *
 * return the battery temperature in centigrade.
 */
int smartstar_battery_temperature(void)
{
    int temp = smartstar_battery_temperature_tenth_degree();

    return temp/10;
}


/**
 * is_smartstar_battery_exist -
 *
 * 0:battery isn't exist, 1: exist
 */
int is_smartstar_battery_exist(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;
    int temp;

    if (di->flag & BATTERY_EXIST_FLAG)
        return 1;

#if defined CONFIG_MACH_HI6620SFT
    /*read version register*/
    if (SMARTSTAR_REG_READ(0x0) != 0x20) {
        return 0;
    }
#endif

    temp = smartstar_battery_temperature();
    if ((temp >= ABNORMAL_BATT_TEMPERATURE_LOW)
        && (temp >= ABNORMAL_BATT_TEMPERATURE_LOW)) {
        di->flag |= BATTERY_EXIST_FLAG;
        return 1;
    } else {
        di->flag &= ~BATTERY_EXIST_FLAG;
        return 0;
    }
}

/**
 * is_smartstar_battery_reach_thresholds
 */
int is_smartstar_battery_reach_threshold(void)
{

    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    if (di->batt_soc < BATTERY_CC_LOW_LEV)
        return 1;
    else
        return 0;
}

/**
 * is_smartstar_battery_full
 */
int is_smartstar_battery_full(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    if (di->batt_soc >= 100)
        return 1;
    else
        return 0;
}

/**
 * smartstar_battery_voltage
 *
 * battery voltage in milivolts
 */
int smartstar_battery_voltage(void)
{
    int vol = smartstar_battery_voltage_uv();

    return vol/1000;
}

/**
 * smartstar_battery_current - return the current of battery.
 *
 * return the battery current in mA.
 */
int smartstar_battery_current(void)
{
    int cur = smartstar_battery_current_ua();
    return cur / 1000;
}

/**
 * smartstar_battery_capacity - return the capacity of battery.
 *
 * return the battery current in percent.
 */
int smartstar_battery_capacity(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    return di->batt_soc;
}


/**
 * smartstar_battery_rm
 *
 * return the remaining capacity in mAh.
 */
int smartstar_battery_rm(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    return di->batt_rm;
}

/**
 * smartstar_battery_fcc
 *
 * return battery FullChargeCapacity,the reture value is mAh Or < 0 if something fails.
 */
int smartstar_battery_fcc (void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    return di->batt_fcc;
}

/**
 * smartstar_battery_tte
 *
 * return time to empty, the reture value is min, or -1 in charging;
 */
int smartstar_battery_tte (void)
{
    int cc, cur;
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    cur = smartstar_battery_current_ua();

    if (cur < 0){
        return -1; /* charging now */
    }

    cc = di->batt_rm - di->batt_uuc;

	if (cc < 0) {
        return -1;
    }

    return cc * 60 / cur;
}

/**
 * smartstar_battery_ttf
 *
 * return time to full, the reture value is min, or -1 in discharging.
 */
int smartstar_battery_ttf (void)
{
    int cc, cur;
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    cur = smartstar_battery_current_ua();

    if (cur >= 0){
        return -1; /* discharging now */
    }

    cc = di->batt_fcc - di->batt_rm;

    return cc * 60 / (-cur); /* cur is < 0 */
}

/**
 * smartstar_battery_health
 *
 * return 0->"Unknown", 1->"Good", 2->"Overheat", 3->"Dead", 4->"Over voltage",
 *			    5->"Unspecified failure", 6->"Cold",
 */
int smartstar_battery_health (void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;
    int status = POWER_SUPPLY_HEALTH_GOOD;
    int temp = di->batt_temp/10;

    if (temp < TEMP_TOO_COLD)
        status = POWER_SUPPLY_HEALTH_COLD;
    else if (temp > TEMP_TOO_HOT)
        status = POWER_SUPPLY_HEALTH_OVERHEAT;

    return status;
}

/**
 * smartstar_battery_capacity_level
 *
 * return battery FullChargeCapacity,the reture value is mAh Or < 0 if something fails.
 */
int smartstar_battery_capacity_level (void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;
    int data_capacity = di->batt_soc;
    int status;

    if(data_capacity > 100 || data_capacity < 0)
        return POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
    else if ((data_capacity >= 0) && (data_capacity <= 5))
        status = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
    else if ((data_capacity > 5) && (data_capacity <= 15))
        status = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
    else if ((data_capacity >= 95) && (data_capacity < 100))
        status = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
    else if (100 == data_capacity)
        status = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
    else
        status = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;

    return status;
}

/**
 * smartstar_battery_technology
 */
int smartstar_battery_technology (void)
{
    /*Default technology is "Li-poly"*/
    return POWER_SUPPLY_TECHNOLOGY_LIPO;
}

/**
 * get_ocv_by_fcc - interpolate ocv value by full charge capacity.
 * @di: stmartstar coul device
 * @batt_temp: temperature
 * called when receive charging complete event
 */
static void get_ocv_by_fcc(struct smartstar_coul_device *di,int batt_temp)
{
    unsigned int new_ocv;
    int batt_temp_degc = batt_temp/10;

    /*looking for ocv value in the OCV-FCC table*/
    new_ocv = interpolate_ocv(di->batt_data->pc_temp_ocv_lut, batt_temp_degc, 100);

    if ((new_ocv - di->batt_ocv) > 0) {
        DBG_CNT_INC(dbg_ocv_cng_1);
        SMARTSTAR_COUL_EVT("full charged, nad OCV change,\
                            new_ocv = %d, old_ocv = %d \n",new_ocv,di->batt_ocv);
        di->batt_ocv = new_ocv;

        /*clear cc register*/
        clear_cc_register();
        di->cc_start_value = 0;
        di->get_cc_start_time = get_coul_time();

    } else {
        DBG_CNT_INC(dbg_ocv_fc_failed);
        SMARTSTAR_COUL_ERR("full charged, but OCV don't change,\
                            new_ocv = %d, old_ocv = %d \n",new_ocv,di->batt_ocv);
    }
}

/**
 * get_ocv_by_vol - update the ocv from the value of vol FIFO.
 * @di: stmartstar coul device
 *
 * should be called when AP exit from deep sleep
 */
static void get_ocv_by_vol(struct smartstar_coul_device *di)
{
    int i,used;
    short regval,curreglimit;
    int totolvol;

    curreglimit = (short)di->batt_ocv_curreglimit;

    totolvol = 0;
    used = 0;
    for (i=0; i<20; i++) {
        SMARTSTAR_REGS_READ(SMARTSTAR_CUR_FIFO_BASE + i*2,&regval,2);
        if ((regval >= curreglimit) || (regval <= 0)) {
            DBG_CNT_INC(dbg_invalid_vol);
            continue;
        }
        DBG_CNT_INC(dbg_valid_vol);
        SMARTSTAR_REGS_READ(SMARTSTAR_VOL_FIFO_BASE + i*2,&regval,2);
        totolvol += regval;
        used++;
    }

    if (used > 1) {
        regval = (short)totolvol/used;

        SMARTSTAR_COUL_EVT("awake from deep sleep, old OCV = %d \n",di->batt_ocv);

        di->batt_ocv = convert_regval2uv(regval);

        clear_cc_register();
        di->cc_start_value = 0;
        di->get_cc_start_time = get_coul_time();

        SMARTSTAR_COUL_EVT("awake from deep sleep, new OCV = %d \n",di->batt_ocv);
        DBG_CNT_INC(dbg_ocv_cng_0);
    }
}

/**
 * is_ocv_invalid - check the invalid of ocv.
 */
int is_ocv_invalid (int ocv)
{
    return 0;
}

/**
 * get_initial_ocv - get first ocv from register, hardware record it during system reset.
 */
static void get_initial_ocv(struct smartstar_coul_device *di)
{
    short ocvreg,volreg_offset;
    int ocv;

    /*read ocv and offset */
    SMARTSTAR_REGS_READ(SMARTSTAR_OCV_REG_BASE,&ocvreg,2);
    SMARTSTAR_REGS_READ(SMARTSTAR_OFFSET_VOLTAGE,&volreg_offset,2);

    ocv = convert_regval2uv(ocvreg - volreg_offset);

    SMARTSTAR_COUL_INF("ocvreg=0x%x volreg_offset = 0x%x\n", ocvreg,volreg_offset);

    /*check val of ocv */
    if (is_ocv_invalid(ocv)) {
        SMARTSTAR_COUL_ERR("invalid ocv value = %d\n", ocv);
        ocv = smartstar_battery_voltage_uv();
    }

    di->batt_ocv = ocv;

    di->cc_start_value = 0;

    SMARTSTAR_COUL_INF("initial OCV = %d\n", di->batt_ocv);
}

/**
* calacute and set the low voltage interrupt value
*/
static void set_low_vol_int_reg(struct smartstar_coul_device *di)
{
    int batt_temp_degc, vol;
    short regval;

    batt_temp_degc = di->batt_temp/10;

    if (di->batt_soc > BATTERY_CC_WARNING_LEV) {
        vol = interpolate_ocv(di->batt_data->pc_temp_ocv_lut, batt_temp_degc, BATTERY_CC_WARNING_LEV);
    } else {
        vol = interpolate_ocv(di->batt_data->pc_temp_ocv_lut, batt_temp_degc, BATTERY_CC_LOW_LEV);
    }

    SMARTSTAR_COUL_INF("set low power vol is %d uv,and soc = %d\n",vol,di->batt_soc);

    regval = convert_uv2regval(vol*1000);

    SMARTSTAR_REGS_WRITE(SMARTSTAR_VOL_INT_BASE, &regval, 2);
}


/**
 * is_smartstar_battery_moved - check whether user have changed a battery
 *
 * 0:not moved, 1: moved
 */
int is_smartstar_battery_moved(void)
{
    unsigned char val;
    val = SMARTSTAR_REG_READ(SMARTSTAR_BATTERY_MOVE_ADDR);

    if (val == BATTERY_MOVE_MAGIC_NUM){
        return 0;
    }
    else {
        SMARTSTAR_REG_WRITE(SMARTSTAR_BATTERY_MOVE_ADDR, BATTERY_MOVE_MAGIC_NUM);
        return 1;
    }

}


/**
 * get_battery_id_voltage - get voltage on ID pin by HKADC.
 * @di: stmartstar coul device
 * called in module initalization
 */
static void get_battery_id_voltage(struct smartstar_coul_device *di)
{
    // TODO: HKADC
    /*change ID get from NTC resistance by HKADC path*/
    di->batt_id_vol= 150;
}

static int bound_soc(int soc)
{
	soc = max(0, soc);
	soc = min(100, soc);
	return soc;
}

static int adjust_soc(struct smartstar_coul_device *di, int soc,
		int batt_temp, int chargecycles,
		int rbatt, int fcc_uah, int uuc_uah, int cc_uah)
{
    int ibat_ua = 0, vbat_uv = 0;
    int ocv_est_uv = 0, soc_est = 0, pc_est = 0, pc = 0;
    int delta_ocv_uv = 0;
    int n = 0;
    int rc_new_uah = 0;
    int pc_new = 0;
    int soc_new = 0;
    int m = 0;
    int delta_ocv_uv_limit = 0;
    int ocv = di->batt_ocv;
    static int last_soc_est = -EINVAL;


    get_simultaneous_battery_voltage_and_current(di,
                                                &ibat_ua, &vbat_uv);

    delta_ocv_uv_limit = DIV_ROUND_CLOSEST(ibat_ua, 1000);

    ocv_est_uv = vbat_uv + (ibat_ua * rbatt /1000);
    pc_est = calculate_pc(di, ocv_est_uv, batt_temp, chargecycles);
    soc_est = div_s64((s64)fcc_uah * pc_est - uuc_uah*100,
    					(s64)fcc_uah - uuc_uah);
    soc_est = bound_soc(soc_est);

    if (ibat_ua < 0) {
    	goto out;
    }

    /*
     * do not adjust
     * if soc is same as what bms calculated
     * if soc_est is between 45 and 25, this is the flat portion of the
     * curve where soc_est is not so accurate. We generally don't want to
     * adjust when soc_est is inaccurate except for the cases when soc is
     * way far off (higher than 50 or lesser than 20).
     * Also don't adjust soc if it is above 90 becuase we might pull it low
     * and  cause a bad user experience
     */
    if (soc_est==soc || is_between(45, 25, soc_est) || soc>=90)
    {
    	goto out;
    }
    if (last_soc_est == -EINVAL)
    	last_soc_est = soc;

    n = min(200, max(1 , soc + soc_est + last_soc_est));
    /* remember the last soc_est in last_soc_est */
    last_soc_est = soc_est;

    pc = calculate_pc(di, di->batt_ocv,
    			batt_temp, di->batt_chargecycles);
    if (pc > 0) {
    	pc_new = calculate_pc(di, di->batt_ocv - (++m * 1000),
    					batt_temp, di->batt_chargecycles);
    	while (pc_new == pc) {
    		/* start taking 10mV steps */
    		m = m + 10;
    		pc_new = calculate_pc(di,
    					di->batt_ocv - (m * 1000),
    					batt_temp, di->batt_chargecycles);
    	}
    } else {
    	/*
    	 * pc is already at the lowest point,
    	 * assume 1 millivolt translates to 1% pc
    	 */
    	pc = 1;
    	pc_new = 0;
    	m = 1;
    }

    delta_ocv_uv = div_s64((soc - soc_est) * (s64)m * 1000,
    						n * (pc - pc_new));

    if (abs(delta_ocv_uv) > delta_ocv_uv_limit) {
    	SMARTSTAR_COUL_INF("limiting delta ocv %d limit = %d\n", delta_ocv_uv,
    			delta_ocv_uv_limit);

    	if (delta_ocv_uv > 0)
    		delta_ocv_uv = delta_ocv_uv_limit;
    	else
    		delta_ocv_uv = -1 * delta_ocv_uv_limit;
    }

    /* di->last_ocv_uv -= delta_ocv_uv;*/

    /* calculate the soc based on this new ocv */
    pc_new = calculate_pc(di, di->batt_ocv,
    					batt_temp, di->batt_chargecycles);
    rc_new_uah = (fcc_uah * pc_new) / 100;
    soc_new = (rc_new_uah - cc_uah - uuc_uah)*100 / (fcc_uah - uuc_uah);
    soc_new = bound_soc(soc_new);

    /*
     * if soc_new is ZERO force it higher so that phone doesnt report soc=0
     * soc = 0 should happen only when soc_est == 0
     */
    if (soc_new == 0 && soc_est != 0)
    	soc_new = 1;

    soc = soc_new;

out:
    SMARTSTAR_COUL_INF("ibat_ua = %d, vbat_uv = %d, ocv_est_uv = %d, pc_est = %d, "
    	"soc_est = %d, n = %d, delta_ocv_uv = %d, last_ocv_uv = %d, "
    	"pc_new = %d, soc_new = %d, rbatt = %d, m = %d\n",
    	ibat_ua, vbat_uv, ocv_est_uv, pc_est,
    	soc_est, n, delta_ocv_uv, ocv,
    	pc_new, soc_new, rbatt, m);

    return soc = bound_soc(soc);
}

static int limit_soc(struct smartstar_coul_device *di,int input_soc)
{
    int output_soc;

    int last_soc = di->batt_soc;
    int current_ua = smartstar_battery_current_ua();

    if(current_ua >= 0) {
    	if(last_soc - input_soc > 1)
    		output_soc = last_soc - 1;
    	else
    		output_soc = last_soc;
    }
    else {
    	if(input_soc - last_soc > 1)
    		output_soc = last_soc + 1;
    	else
    		output_soc = last_soc;
    }

    if (di->charging_state == CHARGING_STATE_CHARGE_START && input_soc > 99){
        output_soc = 99;
    }
    else if ((di->charging_state == CHARGING_STATE_CHARGE_RECHARGE)
            || (di->charging_state == CHARGING_STATE_CHARGE_DONE)){
        output_soc = 100;
    }

    return output_soc;
}

static void calculate_soc_params(struct smartstar_coul_device *di,
						int *fcc_uah,
						int *unusable_charge_uah,
						int *remaining_charge_uah,
						int *cc_uah,
						int *rbatt)
{
    int soc_rbatt, iavg_ua, delta_time_s;
    int batt_temp = di->batt_temp;
    int chargecycles = di->batt_chargecycles;

    *fcc_uah = calculate_fcc_uah(di, batt_temp, chargecycles);

    di->batt_fcc = *fcc_uah;

    /* calculate remainging charge */
    *remaining_charge_uah = calculate_remaining_charge_uah(di,
    				*fcc_uah, batt_temp, chargecycles);

    /* calculate cc micro_volt_hour */
    di->cc_end_value = calculate_cc_uah();
    *cc_uah = di->cc_end_value - di->cc_start_value;

    di->batt_rm = *remaining_charge_uah - *cc_uah;

    soc_rbatt = ((*remaining_charge_uah - *cc_uah) * 100) / *fcc_uah;
    if (soc_rbatt < 0)
    	soc_rbatt = 0;

    *rbatt = get_rbatt(di, soc_rbatt, batt_temp);

    di->get_cc_end_time = get_coul_time();

    delta_time_s = (int)(di->get_cc_end_time - di->get_cc_start_time);

    if (delta_time_s > 0) {
        iavg_ua = div_s64((s64)*cc_uah * 3600, delta_time_s);
    } else {
        iavg_ua = smartstar_battery_current_ua();
    }

    *unusable_charge_uah = calculate_unusable_charge_uah(di, *rbatt,
    				*fcc_uah, *cc_uah, soc_rbatt,
    				batt_temp, chargecycles, iavg_ua);
}


#ifdef _DRV_LLT_
int calculate_state_of_charge(struct smartstar_coul_device *di)
#else
static int calculate_state_of_charge(struct smartstar_coul_device *di)
#endif
{
    int remaining_usable_charge_uah, fcc_uah, unusable_charge_uah;
    int remaining_charge_uah, soc;
    int cc_uah;
    int rbatt;
    int temp;

    /* check temperature */
    temp = smartstar_battery_temperature_tenth_degree();

    if (temp != di->batt_temp){
        di->batt_temp = temp;
        SMARTSTAR_COUL_INF("battery temperature is %d.%d\n", temp/10, temp%10);
    }

    calculate_soc_params(di,
                                    &fcc_uah,
                                    &unusable_charge_uah,
                                    &remaining_charge_uah,
                                    &cc_uah,
                                    &rbatt);

    SMARTSTAR_COUL_INF("FCC=%duAh, UUC=%duAh, RC=%duAh, CC=%duAh, Rbatt=%dmOhm\n",
                                            fcc_uah, unusable_charge_uah, remaining_charge_uah, cc_uah, rbatt);

    /* calculate remaining usable charge */
    remaining_usable_charge_uah = remaining_charge_uah
                                                - cc_uah - unusable_charge_uah;

    if (fcc_uah - unusable_charge_uah <= 0) {
    	soc = 0;
    } else {
    	soc = DIV_ROUND_CLOSEST((remaining_usable_charge_uah * 100),
    				(fcc_uah - unusable_charge_uah));
    }
    if (soc > 100)
    	soc = 100;

    if (fcc_uah > unusable_charge_uah){
        SMARTSTAR_COUL_INF("SOC before adjust = %d\n", soc);
        soc= adjust_soc(di, soc, di->batt_temp, di->batt_chargecycles,
    		    rbatt, fcc_uah, unusable_charge_uah, cc_uah);
        SMARTSTAR_COUL_INF("SOC before limit = %d\n", soc);
    }

    if (di->soc_limit_flag)
        soc = limit_soc(di, soc);

    SMARTSTAR_COUL_INF("SOC_NEW = %d\n", soc);


#if defined CONFIG_MACH_HI6620SFT
    if (soc < 5) {
        soc = 5;
        SMARTSTAR_COUL_ERR("SFT board: adjust Battery Capacity to %d Percents\n", soc);
    }
#endif

    di->batt_soc = soc;

    return soc;
}



#define CALCULATE_SOC_MS    40000
/**
 * calculate_soc_work - schedule every CALCULATE_SOC_MS.
 */
 static void calculate_soc_work(struct work_struct *work)
{
    struct smartstar_coul_device *di = container_of(work,
				struct smartstar_coul_device,
				calculate_soc_delayed_work.work);

    DI_LOCK();
    /* calc soc */
    di->batt_soc = calculate_state_of_charge(di);
    DI_UNLOCK();

    schedule_delayed_work(&di->calculate_soc_delayed_work,
    		round_jiffies_relative(msecs_to_jiffies(CALCULATE_SOC_MS)) );
}

#define SHUTDOWN_SOC 2
/**
 * interrupt_notifier_work - send a notifier event to battery monitor.
 */
 static void interrupt_notifier_work(struct work_struct *work)
{
    long evt;
    struct smartstar_coul_device *di = container_of(work,
				struct smartstar_coul_device,
				calculate_soc_delayed_work.work);

    DI_LOCK();
    /* voltage interrupt */
    di->batt_soc = calculate_state_of_charge(di);

    if (di->batt_soc < SHUTDOWN_SOC){
        evt = BATTERY_LOW_SHUTDOWN;
    }
    else {
        evt = BATTERY_LOW_WARNING;
    }

    DI_UNLOCK();

    set_low_vol_int_reg(di);

    hisi_coul_charger_event_rcv(evt);

}
/**
 * coul_irq_cb - coul irq handler
 */
static irqreturn_t coul_irq_cb(int irq,  void *_di)
{
    struct smartstar_coul_device *di = _di;

    unsigned char intstat;

    intstat = SMARTSTAR_REG_READ(SMARTSTAR_COUL_IRQ_REG);

    if (intstat | COUL_VBAT_LOW_INT) {
        schedule_delayed_work(&di->notifier_work, 0);
    }

    return IRQ_HANDLED;
}


/**
 * aging_update_begin - begin aging update when charging beging.
 * @di: stmartstar coul device
 *
 * should be called after charging beging, and this can't be called
 * in atomic context
 */
static void smartstar_charging_begin (struct smartstar_coul_device *di)
{
    SMARTSTAR_COUL_INF("smartstar_charging_begin +\n");

    SMARTSTAR_COUL_INF("pre charging state is %d \n",di->charging_state);

    /*change state*/
    if (di->charging_state == CHARGING_STATE_CHARGE_START)
        return;
    else if (di->charging_state == CHARGING_STATE_CHARGE_DONE)
        di->charging_state = CHARGING_STATE_CHARGE_RECHARGE;
    else
        di->charging_state = CHARGING_STATE_CHARGE_START;

    /*calculate soc again*/
    di->batt_soc = calculate_state_of_charge(di);

    /*record soc of charging begin*/
    di->charging_begin_soc = di->batt_soc;

    /*record cc value*/
    di->charging_begin_cc = calculate_cc_uah();

    SMARTSTAR_COUL_INF("smartstar_charging_begin -\n");

}


static void smartstar_charging_stop (struct smartstar_coul_device *di)
{
    if (CHARGING_STATE_CHARGE_START == di->charging_state)
        update_chargecycles(di);

    di->charging_state = CHARGING_STATE_CHARGE_STOP;
}

static void smartstar_charging_done (struct smartstar_coul_device *di)
{

    if (CHARGING_STATE_CHARGE_START != di->charging_state) {
        SMARTSTAR_COUL_ERR("smartstar_charging_done, but pre charge state is %d \n",
                            di->charging_state);
        return;
    }

    di->batt_soc = calculate_state_of_charge(di);
    SMARTSTAR_COUL_EVT("smartstar_charging_done, adjust soc from %d to 100\n",di->batt_soc);
    di->batt_soc = 100;

    if (di->batt_changed_flag) {
        /*recalculate charge cycles*/
        recalc_chargecycles(di);
    }

    update_chargecycles(di);

    SMARTSTAR_COUL_INF("new charging cycles = %d\n", di->batt_chargecycles);

    di->charging_state = CHARGING_STATE_CHARGE_DONE;
}

#ifdef _DRV_LLT_
void charger_event_process(struct smartstar_coul_device *di,unsigned long event)
#else
static void charger_event_process(struct smartstar_coul_device *di,unsigned long event)
#endif
{
    switch (event) {
    	case BQ24161_START_USB_CHARGING:
    	case BQ24161_START_AC_CHARGING:
    	case BQ24161_START_CHARGING:
            SMARTSTAR_COUL_EVT("receive charge start event = 0x%x\n",(int)event);
            /*record soc and cc value*/
            DI_LOCK();
            smartstar_charging_begin(di);
            DI_UNLOCK();
    		break;

    	case BQ24161_STOP_CHARGING:
            SMARTSTAR_COUL_EVT("receive charge stop event = 0x%x\n",(int)event);
            DI_LOCK();
    	    smartstar_charging_stop(di);
    	    DI_UNLOCK();
    	    break;

    	case BQ24161_CHARGE_DONE:
            SMARTSTAR_COUL_EVT("receive charge done event = 0x%x\n",(int)event);
            DI_LOCK();
    	    smartstar_charging_done(di);
    	    DI_UNLOCK();
    		break;

    	case BQ24161_NOT_CHARGING:
    	    di->charging_state = CHARGING_STATE_CHARGE_UNKNOW;
            SMARTSTAR_COUL_ERR("charging is stop by fault\n");
    	    break;

    	case POWER_SUPPLY_OVERVOLTAGE:
    	    di->charging_state = CHARGING_STATE_CHARGE_UNKNOW;
            SMARTSTAR_COUL_ERR("charging is stop by overvoltage\n");
    		break;

    	default:
            di->charging_state = CHARGING_STATE_CHARGE_UNKNOW;
    	    SMARTSTAR_COUL_ERR("unknow event %d\n",(int)event);
    		break;
    }
}

/**
 * smartstar_battery_charger_event_rcv
 */
int smartstar_battery_charger_event_rcv (unsigned long evt)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;

    charger_event_process(di,evt);

    return 0;
}



/**
 * smartstar_coul_config_power_on_reg - config smartstar registers.
 */
static void smartstar_coul_config_power_on_reg(struct smartstar_coul_device *di)
{
    short low_vol_reg;

    /* Mode */
    SMARTSTAR_REG_WRITE(SMARTSTAR_COUL_CTRL_REG,DEFAULT_COUL_CTRL_VAL);

    /* coulometer interrupt mask */
    SMARTSTAR_REG_WRITE(SMARTSTAR_COUL_IRQ_MASK_REG,DEFAULT_INT_MASK_VAL);

    /* set voltage interrupt */
    SMARTSTAR_REGS_WRITE(SMARTSTAR_VOL_INT_BASE, &low_vol_reg, 2);
}


/**
 * smartstar_coul_config_power_off_reg - close coul when probe failed.
 */
static void smartstar_disable_coul(struct smartstar_coul_device *di)
{
    /* Mode */
    SMARTSTAR_REG_WRITE(SMARTSTAR_COUL_CTRL_REG, (~COUL_CTRL_ENABLE) );
}

#ifdef SMARTSTAR_DEBUG
void ss_cur_show(void)
{
    int i,ua;
    short regval;

    for (i=0; i<20; i++) {
        SMARTSTAR_REGS_READ(SMARTSTAR_CUR_FIFO_BASE+i*2, &regval, 2);
        ua = convert_regval2ua(regval);
        printk(KERN_ERR"[%02d]:regval=0x%04x,cur = %d ua \n",i,regval,ua);
    }
}

void ss_vol_show(void)
{
    int i,uv;
    short regval;

    for (i=0; i<20; i++) {
        SMARTSTAR_REGS_READ(SMARTSTAR_VOL_FIFO_BASE+i*2, &regval, 2);
        uv = convert_regval2uv(regval);
        printk(KERN_ERR"[%02d]:regval=0x%04x,vol = %d uv \n",i,regval,uv);
    }
}

void ss_ocv_show(void)
{
    short ocvreg,volreg_offset;
    int ocv;

    /*read ocv and offset */
    SMARTSTAR_REGS_READ(SMARTSTAR_OCV_REG_BASE,&ocvreg,2);
    SMARTSTAR_REGS_READ(SMARTSTAR_OFFSET_VOLTAGE,&volreg_offset,2);

    ocv = convert_regval2uv(ocvreg - volreg_offset);

    printk(KERN_ERR"regval=0x%04x,offset = 0x%04x,ocv = %d uv \n",\
            ocvreg,volreg_offset,ocv);

}

void ss_cc_show(void)
{
	unsigned long cc_in = 0;
	unsigned long cc_out= 0;
	long cc_uah = 0;

    SMARTSTAR_REGS_READ(SMARTSTAR_CL_IN_BASE,&cc_in,4);
    SMARTSTAR_REGS_READ(SMARTSTAR_CL_OUT_BASE,&cc_out,4);

    cc_uah = convert_regval2uah(cc_out);
    cc_uah = cc_uah - convert_regval2uah(cc_in);

    printk(KERN_ERR"ccout_reg=0x%x,ccin_reg = 0x%x,cc = %d uah \n",\
            (unsigned int)cc_out,(unsigned int)cc_in,(unsigned int)cc_uah);

}

void ss_time_show(void)
{
    long cl_in_time,cl_out_time;

    SMARTSTAR_REGS_READ(SMARTSTAR_CHG_TIMER_BASE,&cl_in_time,4);
    SMARTSTAR_REGS_READ(SMARTSTAR_LOAD_TIMER_BASE,&cl_out_time,4);

    printk(KERN_ERR"cl_in_time=%d,cl_out_time = %d,total = %d\n",\
            (unsigned int)cl_in_time,(unsigned int)cl_out_time,(unsigned int)(cl_in_time+cl_out_time));

}

void ss_soc_update(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;
    unsigned int old_soc;
    old_soc = di->batt_soc;
    di->batt_soc = calculate_state_of_charge(di);
    printk(KERN_ERR"batt_soc %d ---> %d \n",old_soc,di->batt_soc);
}

void ss_di_show(void)
{
    struct smartstar_coul_device *di = g_smartstar_coul_dev;


    printk(KERN_ERR"flag = 0x%x\n",di->flag);
    printk(KERN_ERR"prev_pc_unusable = 0x%x\n",di->prev_pc_unusable);
    printk(KERN_ERR"irq = %d\n",di->irq);
    printk(KERN_ERR"batt_ocv_cur_limit = %d\n",di->batt_ocv_cur_limit);
    printk(KERN_ERR"batt_ocv = %d uv\n",di->batt_ocv);
    printk(KERN_ERR"batt_changed_flag = 0x%x\n",di->batt_changed_flag);
    printk(KERN_ERR"batt_vol_low_flag = 0x%x\n",di->batt_vol_low_flag);
    printk(KERN_ERR"batt_temp = %d tenths of degC\n",di->batt_temp);
    printk(KERN_ERR"batt_fcc = %d\n",di->batt_fcc);
    printk(KERN_ERR"batt_rm = %d\n",di->batt_rm);
    printk(KERN_ERR"charging_begin_soc = %d\n",di->charging_begin_soc);
    printk(KERN_ERR"charging_state = %d\n",di->charging_state);
    printk(KERN_ERR"batt_soc = %d\n",di->batt_soc);
    printk(KERN_ERR"batt_id_vol = %d\n",di->batt_id_vol);
    printk(KERN_ERR"batt_chargecycles = %d\n",di->batt_chargecycles);
    printk(KERN_ERR"cc_end_value = %d\n",di->cc_end_value);
    printk(KERN_ERR"cc_start_value = %d\n",di->cc_start_value);
    printk(KERN_ERR"v_cutoff = %d\n",di->v_cutoff);
    printk(KERN_ERR"get_cc_start_time = %d\n",(unsigned int)di->get_cc_start_time);
    printk(KERN_ERR"get_cc_end_time = %d\n",(unsigned int)di->get_cc_end_time);
    printk(KERN_ERR"suspend_time = %d\n",(unsigned int)di->suspend_time);
    printk(KERN_ERR"charging_begin_cc = %d\n",(unsigned int)di->charging_begin_cc);
    printk(KERN_ERR"suspend_cc = %d\n",(unsigned int)di->suspend_cc);
    printk(KERN_ERR"suspend_cc = %d\n",(unsigned int)di->suspend_cc);

    printk(KERN_ERR"dbg_ocv_cng_0 = %d\n",di->dbg_ocv_cng_0);
    printk(KERN_ERR"dbg_ocv_cng_1 = %d\n",di->dbg_ocv_cng_1);
    printk(KERN_ERR"dbg_valid_vol = %d\n",di->dbg_valid_vol);
    printk(KERN_ERR"dbg_invalid_vol = %d\n",di->dbg_invalid_vol);
    printk(KERN_ERR"dbg_ocv_fc_failed = %d\n",di->dbg_ocv_fc_failed);

}

void ss_offset_show(void)
{
    SMARTSTAR_COUL_ERR("Current offset = %d uA, Voltage offset = %d uV\n", c_offset, v_offset);
}

void ss_offset_set(int c, int v)
{
    c_offset = c;
    v_offset = v;
}


#endif

#ifdef _DRV_LLT_
int hisi_smartstar_coul_probe(struct platform_device *pdev)
#else
static int __init hisi_smartstar_coul_probe(struct platform_device *pdev)
#endif
{
    struct hisi_coul_ops *coul_ops = NULL;
    struct smartstar_coul_device *di = NULL;
    int retval = 0;
	struct resource *resource = NULL;

#if defined CONFIG_MACH_HI6620SFT
    gpio_request(GPIO_4_1,"pmu");
    gpio_request(GPIO_4_2,"pmu");
    gpio_request(GPIO_7_4,"pmu");
    gpio_request(GPIO_6_2,"pmu");
    gpio_request(GPIO_9_0,"pmu");
    /*enable smartstar*/
    gpio_direction_output(GPIO_4_1,1);
    gpio_direction_output(GPIO_4_2,1);
    gpio_direction_output(GPIO_7_4,1);
    gpio_direction_output(GPIO_6_2,1);
    gpio_direction_output(GPIO_9_0,1);

    int tryloop = 0;
    do {
        retval = SMARTSTAR_REG_READ(0x0);
        SMARTSTAR_COUL_INF("do a dummy read, smartstar version is 0x%x\n",
                            retval);

        udelay(500);

        if ((tryloop++) > 5)
            return -EPERM;

    } while(retval != 0x20);
#endif

    di = (struct smartstar_coul_device *)kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di) {
		SMARTSTAR_COUL_ERR("%s failed to alloc di struct\n",__FUNCTION__);
		retval = -ENOMEM;
		goto coul_failed_0;
    }

    g_smartstar_coul_dev = di;

    platform_set_drvdata(pdev, di);

    /*set di element */
    di->prev_pc_unusable = -EINVAL;

    /*get irq number*/
    resource = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
    if (!resource) {
        SMARTSTAR_COUL_ERR("smartstar deviece haven't include IRQ\n");
        SMARTSTAR_COUL_ERR("disable smart star coul function\n");
        retval = -EPERM;
        goto coul_failed_1;
    }

    di->irq = resource->start;

    di->v_cutoff = 3200;
    di->batt_ocv_cur_limit = 25000; /*ua*/
    di->batt_ocv_curreglimit = (short)convert_ua2regval(di->batt_ocv_cur_limit);

    /*check battery is exist*/
    if (!is_smartstar_battery_exist()) {
        SMARTSTAR_COUL_ERR("%s: temperature(%d) is abnormal\n",__FUNCTION__,smartstar_battery_temperature());
        retval = -EPERM;
        goto coul_failed_1;
    }

    /*set battery data*/
    get_battery_id_voltage(di);
    di->batt_data = get_battery_data(di->batt_id_vol);
    if (NULL == di->batt_data) {
        SMARTSTAR_COUL_ERR("%s: batt ID(0x%x) is invalid\n",__FUNCTION__,di->batt_id_vol);
        retval = -EINVAL;
        goto coul_failed_1;
    }

    SMARTSTAR_COUL_INF("%s: batt ID is %d\n",__FUNCTION__,di->batt_id_vol);

    INIT_DELAYED_WORK(&di->calculate_soc_delayed_work,
        calculate_soc_work);

    /*calculate first soc */
    SMARTSTAR_COUL_INF("mdelay(10), before get ocv\n");
    mdelay(10);
    get_initial_ocv(di);

    #warning "STUB for CC"
    clear_cc_register();
    clear_coul_time();

    /*config coul reg */
    smartstar_coul_config_power_on_reg(di);

    /*get charge cycles */
    di->batt_chargecycles = get_chargecycles(di);

    if(is_smartstar_battery_moved()){
        di->batt_chargecycles = 0;
        di->batt_changed_flag = 1;
        save_chargecycles(di);
        SMARTSTAR_COUL_INF("battery changed, reset chargecycles!\n");
    } else if (di->batt_chargecycles == 0){
        di->batt_changed_flag = 1;
        SMARTSTAR_COUL_INF("battery chargecycles is 0, need recalc.\n");
    } else {
        SMARTSTAR_COUL_INF("battery not changed, chargecycles = %d%%\n", di->batt_chargecycles);
    }

    mutex_init(&di->soc_mutex);

    /*get the first soc value*/
    DI_LOCK();
    di->soc_limit_flag = 0;
    di->batt_soc = calculate_state_of_charge(di);
    di->soc_limit_flag = 1;
    DI_UNLOCK();

    /*schedule calculate_soc_work*/
    schedule_delayed_work(&di->calculate_soc_delayed_work,
                        round_jiffies_relative(msecs_to_jiffies(CALCULATE_SOC_MS)));


    INIT_DELAYED_WORK(&di->notifier_work,
                      interrupt_notifier_work);


    set_low_vol_int_reg(di);

    gpio_request(di->irq,"cool int");
	gpio_direction_input(di->irq);
    retval = request_irq(gpio_to_irq(di->irq), coul_irq_cb, IRQF_NO_SUSPEND, pdev->name, di);
    if (retval) {
        SMARTSTAR_COUL_ERR("Failed to request coul handler!\n");
        goto coul_failed_2;
    } else {
		enable_irq_wake(gpio_to_irq(di->irq));
    }

    coul_ops = (struct hisi_coul_ops*) kzalloc(sizeof (*coul_ops), GFP_KERNEL);
    if (!coul_ops) {
		SMARTSTAR_COUL_ERR("failed to alloc coul_ops struct\n");
		retval = -ENOMEM;
        goto coul_failed_3;
    }

    coul_ops->is_coul_ready = is_smartstar_coul_ready;
    coul_ops->is_battery_exist = is_smartstar_battery_exist;
    coul_ops->is_battery_reach_threshold = is_smartstar_battery_reach_threshold;
    coul_ops->is_battery_full = is_smartstar_battery_full;
    coul_ops->battery_voltage = smartstar_battery_voltage;
    coul_ops->battery_current = smartstar_battery_current;
    coul_ops->battery_capacity = smartstar_battery_capacity;
    coul_ops->battery_temperature = smartstar_battery_temperature;
    coul_ops->battery_rm = smartstar_battery_rm;
    coul_ops->battery_fcc = smartstar_battery_fcc;
    coul_ops->battery_tte = smartstar_battery_tte;
    coul_ops->battery_ttf = smartstar_battery_ttf;
    coul_ops->battery_health = smartstar_battery_health;
    coul_ops->battery_capacity_level = smartstar_battery_capacity_level;
    coul_ops->battery_technology = smartstar_battery_technology;
    coul_ops->charger_event_rcv = smartstar_battery_charger_event_rcv;

    di->ops = coul_ops;
    retval = hisi_coul_ops_register(coul_ops,COUL_SMARTSTAR);
    if (retval) {
        SMARTSTAR_COUL_ERR("failed to register coul ops\n");
        goto coul_failed_4;
    }

    return retval;


coul_failed_4:
    kfree(coul_ops);
    di->ops = NULL;
coul_failed_3:
    free_irq(gpio_to_irq(di->irq),di);
	cancel_delayed_work(&di->calculate_soc_delayed_work);
coul_failed_2:
	cancel_delayed_work(&di->notifier_work);
coul_failed_1:
    platform_set_drvdata(pdev, NULL);
    kfree(di);
    g_smartstar_coul_dev = NULL;
coul_failed_0:
    smartstar_disable_coul(di);
    return retval;
}

static int __devexit hisi_smartstar_coul_remove(struct platform_device *pdev)
{
    struct smartstar_coul_device *di = platform_get_drvdata(pdev);

    hisi_coul_ops_unregister(di->ops);
    kfree(di->ops);
    di->ops = NULL;
    kfree(di);
    g_smartstar_coul_dev = NULL;

    return 0;
}

#ifdef CONFIG_PM
static int hisi_smartstar_coul_suspend(struct platform_device *pdev,
	pm_message_t state)
{
    struct smartstar_coul_device *di = platform_get_drvdata(pdev);

    DI_LOCK();
    di->suspend_cc = calculate_cc_uah();
    di->suspend_time = get_coul_time();
    DI_UNLOCK();

    cancel_delayed_work_sync(&di->calculate_soc_delayed_work);

    return 0;
}

static int ocv_could_update(struct smartstar_coul_device *di)
{
    long sleep_cc;
    unsigned long sleep_time, time_now;

    sleep_cc = calculate_cc_uah();
    sleep_cc = sleep_cc - di->suspend_cc;
    time_now = get_coul_time();
    sleep_time = time_now - di->suspend_time;

    if (sleep_time < delta_sleep_time)
        return 0;

    if (sleep_cc/sleep_time > delta_sleep_current)
        return 0;

    return 1;
}

static int hisi_smartstar_coul_resume(struct platform_device *pdev)
{
    struct smartstar_coul_device *di = platform_get_drvdata(pdev);
    unsigned long sleep_time;
    unsigned int sleep_soc,soc_sf;

    DI_LOCK();
    if (ocv_could_update(di)){
        get_ocv_by_vol(di);
    }
    sleep_soc = di->batt_soc;

    di->soc_limit_flag = 0;
    di->batt_soc = calculate_state_of_charge(di);
    di->soc_limit_flag = 1;

    sleep_time = get_coul_time() - di->suspend_time;

    soc_sf = (sleep_time/(CALCULATE_SOC_MS/1000));

    if ((sleep_soc - di->batt_soc) > soc_sf){
        di->batt_soc = sleep_soc - soc_sf;
    }

    if (di->batt_soc > sleep_soc){
        di->batt_soc = sleep_soc;
    }

    DI_UNLOCK();

    schedule_delayed_work(&di->calculate_soc_delayed_work,
                round_jiffies_relative(msecs_to_jiffies(CALCULATE_SOC_MS)));

    return 0;
}
#endif

static struct platform_driver hisi_smartstar_coul_driver = {
	.probe		= hisi_smartstar_coul_probe,
	.remove		= __devexit_p(hisi_smartstar_coul_remove),
#ifdef CONFIG_PM
	.suspend	       = hisi_smartstar_coul_suspend,
	.resume		= hisi_smartstar_coul_resume,
#endif
	.driver		= {
	.name		= "hisi_smartstar_coul",
	},
};

int __init hisi_smartstar_coul_init(void)
{
    return (platform_driver_register(&hisi_smartstar_coul_driver));
}

void __exit hisi_smartstar_coul_exit(void)
{
    platform_driver_unregister(&hisi_smartstar_coul_driver);
}


fs_initcall(hisi_smartstar_coul_init);
module_exit(hisi_smartstar_coul_exit);

MODULE_AUTHOR("HUAWEI");
MODULE_DESCRIPTION("hisi coul module driver");
MODULE_LICENSE("GPL");



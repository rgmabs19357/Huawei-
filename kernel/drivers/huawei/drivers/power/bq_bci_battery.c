/*
 * linux/drivers/power/bq_bci_battery.c
 *
 * K3:battery driver for Linux
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/power_supply.h>
#include <linux/wakelock.h>
#include <linux/hkadc/hisi_adc_hal.h>
#include <linux/hkadc/hisi_adc_linux.h>
#include <linux/notifier.h>
#include <bq27510_battery.h>
#include <bq2419x_charger.h>
#include <bq_bci_battery.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <mach/irqs.h>
#include <linux/usb/hiusb_android.h>
#include <hsad/config_mgr.h>
#include <mach/boardid.h>
#include <hisi_coul_drv.h>
#include <linux/log_exception.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <linux/module.h>

#define WINDOW_LEN                   (10)
#define LOG_ARCH_DELAY_TIME          (60000)
extern struct i2c_client *g_battery_measure_by_bq27510_i2c_client;
static struct bq27510_device_info dev27510;
static struct wake_lock low_power_lock;
static int is_low_power_locked = 0;
static unsigned int    capacity_filter[WINDOW_LEN];
static unsigned int    capacity_sum;
static unsigned int    suspend_capacity;
extern void hisi_smartstar_print_cc_reg(int c); //debug
extern int is_smartstar_fcc_debounce(void);


static int is_fake_battery = 0;
module_param(is_fake_battery, int, 0644);

struct bq_bci_device_info {
    int             *battery_tmp_tbl;
    unsigned int    tblsize;

    int    limited_charge_voltagemV;
    int    bat_voltage;
    int    bat_temperature;
    int    bat_exist;
    int    bat_health;
    int    bat_capacity;
    int    bat_capacity_level;
    int    bat_technolog;
    int    bat_rm;
    int    bat_fcc;
    short           bat_current;
    unsigned int    bat_err;

    int    amb_temperature;
    int    bk_voltage_mV;
    int    charge_status;
    int    power_supply_status;

    u8     usb_online;
    u8     ac_online;
    u8     chargedone_stat;

    u16    monitoring_interval;

    unsigned int    max_charger_voltagemV;
    unsigned int    max_charger_currentmA;
    unsigned int    regulation_voltagemV;
    unsigned int    low_bat_voltagemV;
    unsigned int    termination_currentmA;
    unsigned long   event;

    unsigned int    capacity;
    unsigned int    capacity_filter_count;
    unsigned int    prev_capacity;
    unsigned int    charge_full_count;
    unsigned int    wakelock_enabled;

    struct power_supply    bat;
    struct power_supply    usb;
    struct power_supply    ac;
    struct power_supply    bk_bat;

    struct device   *dev;
    struct bq_bci_platform_data *platform_data;
    struct notifier_block    nb;
    struct delayed_work bq_bci_monitor_work;
};

struct bq_bci_device_info *g_bq_bci_dev = NULL;

BLOCKING_NOTIFIER_HEAD(notifier_list);

extern int getcalctemperature(int channel);

#define CHG_ODD_CAPACITY                (2)
#define CHG_CANT_FULL_THRESHOLD         (95) /*bad gasgauge ic can't report capacity correctly
                                              *when charging schedule near full-state.   */
#define REACH_FULL_RESAMPLE_THRESHOLD   (90)
#define REACH_EMPTY_RESAMPLE_THRESHOLD  (10)
#define NORMAL_SAMPLE_INTERVAL          (10)
#define REACH_FULL_SAMPLE_INTERVAL      (30)
#define REACH_EMPTY_SAMPLE_INTERVAL     (5)
#define CHARGE_FULL_TIME                (40*60)/REACH_FULL_SAMPLE_INTERVAL   /*40min = 2400s/INTERVAL*/
#define BATT_OVERVOLTAGE_THRES          (4550)
#define BATT_LOWVOLTAGE_THRES           (3100)
#define ARCH_NAME_MAX                   (256)


static enum power_supply_property bq_bci_battery_props[] = {
    POWER_SUPPLY_PROP_STATUS,
    POWER_SUPPLY_PROP_HEALTH,
    POWER_SUPPLY_PROP_PRESENT,
    POWER_SUPPLY_PROP_ONLINE,
    POWER_SUPPLY_PROP_TECHNOLOGY,
    POWER_SUPPLY_PROP_VOLTAGE_NOW,
    POWER_SUPPLY_PROP_CURRENT_NOW,
    POWER_SUPPLY_PROP_CURRENT_AVG,
    POWER_SUPPLY_PROP_CAPACITY,
    POWER_SUPPLY_PROP_CAPACITY_LEVEL,
    POWER_SUPPLY_PROP_TEMP,
    POWER_SUPPLY_PROP_CAPACITY_RM,
    POWER_SUPPLY_PROP_CAPACITY_FCC,
    POWER_SUPPLY_PROP_TEMP_AMBIENT,
    POWER_SUPPLY_PROP_VOLTAGE_MAX,
};

static enum power_supply_property bq_usb_props[] = {
    POWER_SUPPLY_PROP_ONLINE,
    POWER_SUPPLY_PROP_VOLTAGE_NOW,
    POWER_SUPPLY_PROP_HEALTH,
};

static enum power_supply_property bq_ac_props[] = {
    POWER_SUPPLY_PROP_ONLINE,
    POWER_SUPPLY_PROP_VOLTAGE_NOW,
    POWER_SUPPLY_PROP_HEALTH,
};

static enum power_supply_property bq_bk_bci_battery_props[] = {
    POWER_SUPPLY_PROP_VOLTAGE_NOW,
};

static int modem_off = false;

static void get_time_stamp(char* timestamp_buf,unsigned int len)
{
   struct timeval tv;
   struct rtc_time tm;

   if(NULL == timestamp_buf) {
       return;
   }
   memset(&tv, 0, sizeof(struct timeval));
   memset(&tm, 0, sizeof(struct rtc_time));
   do_gettimeofday(&tv);
   tv.tv_sec -= sys_tz.tz_minuteswest * 60;
   rtc_time_to_tm(tv.tv_sec, &tm);
   snprintf(timestamp_buf,len, "%04d%02d%02d%02d%02d%02d",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static void bq_log_exception_archive(unsigned int bat_err)
{
    struct bq_bci_device_info *di = g_bq_bci_dev;
    char cmd[ARCH_NAME_MAX];
    char time_buf[16];
    int ret = 0;

    get_time_stamp(time_buf,16);
    snprintf(cmd, ARCH_NAME_MAX, "%s%s%s%s%s%x%s",
             "archive -i /data/android_logs/charge_log -i /data/android_logs/charge_log.1",
                    " -i /data/android_logs/kmsgcat-log -i /data/android_logs/kmsgcat-log.1",
                    " -o ", time_buf, "_BattErr0x", bat_err, " -z zip");

    ret = log_to_exception("charge",cmd);
    if(ret < 0 ){
        dev_info(di->dev,"logexception sysfs err.\n");
    }
}

int notify_mdm_off_to_pm(void)
{
    if (system_state != SYSTEM_RUNNING)
        return 0;
    if ((hisi_battery_voltage() < 3400)&&
        (get_charger_name() == CHARGER_REMOVED)){
        modem_off = true;
        return 1;
    }
    return 0;
}

static int calc_capacity_from_voltage(void)
{
    int data  = 50;
    int battery_voltage = 0;
    int battery_current = 0;

    battery_current = -hisi_battery_current();
    battery_voltage = hisi_battery_voltage();//bq27510_battery_voltage(&dev27510);
    if (battery_voltage <= BAT_VOL_3200){
        data = 0;
        return data;
    }
    battery_voltage = hisi_battery_voltage()-120*battery_current/1000;
    if (battery_voltage < BAT_VOL_3500)
        data = 2;
    else if (battery_voltage < BAT_VOL_3550)
        data = 10;
    else if (battery_voltage < BAT_VOL_3600)
        data = 20;
    else if (battery_voltage < BAT_VOL_3700)
        data = 30;
    else if (battery_voltage < BAT_VOL_3800)
        data = 40;    
    else if (battery_voltage < BAT_VOL_3850)
        data = 50;    
    else if (battery_voltage < BAT_VOL_3900)
        data = 60;
    else if (battery_voltage < BAT_VOL_3950)
        data = 65;
    else if (battery_voltage < BAT_VOL_4000)
        data = 70;
    else if (battery_voltage < BAT_VOL_4250)
        data = 85;
    else if (battery_voltage >= BAT_VOL_4250)
       data = 100;
    return data;
}

/*
 * Return channel value
 * Or < 0 on failure.
 */
static int bq_get_gpadc_conversion(struct bq_bci_device_info *di, int channel_no)
{
#if 1
return 0;
#else
    unsigned char reserve = 0;
    int value = 0;
    int ret = 0;

    ret = k3_adc_open_channel(channel_no);
    if (ret < 0)
        dev_err(di->dev, "%s is error\n", __func__);

    value = k3_adc_get_value(channel_no, &reserve);

    ret = k3_adc_close_channal(channel_no);
    if (ret < 0)
        dev_err(di->dev, "%s is error\n", __func__);

   return value;
#endif
}

/*only charge-work can not reach full(95%).Change capacity to full after 40min.*/
static int bq_force_full_timer(int curr_capacity, struct bq_bci_device_info *di)
{
    if(curr_capacity > CHG_CANT_FULL_THRESHOLD) {
        di->charge_full_count++;
        if(di->charge_full_count >= CHARGE_FULL_TIME){
            dev_info(di->dev,"FORCE_CHARGE_FULL = %d\n",curr_capacity);
            di->charge_full_count = CHARGE_FULL_TIME;
            curr_capacity = 100;
        }
    } else {
        di->charge_full_count = 0;
    }

    return curr_capacity;
}

static int bq_capacity_pulling_filter(int curr_capacity, struct bq_bci_device_info *di)
{
    int index = 0;
    di->bat_exist = is_hisi_battery_exist();

    if ((!di->bat_exist) || (is_fake_battery)){
        curr_capacity = calc_capacity_from_voltage();
        return curr_capacity;
    }
    index = di->capacity_filter_count%WINDOW_LEN;

    capacity_sum -= capacity_filter[index];
    capacity_filter[index] = curr_capacity;
    capacity_sum += capacity_filter[index];

    if (++di->capacity_filter_count >= WINDOW_LEN) {
        di->capacity_filter_count = 0;
    }

    /*rounding-off 0.5 method*/
    curr_capacity = (capacity_sum*10)/WINDOW_LEN;
    curr_capacity = (curr_capacity+5)/10;

    return curr_capacity;
}

static int capacity_changed(struct bq_bci_device_info *di)
{
    int ret = 0;
    int curr_capacity = 0;
    int low_bat_flag = is_hisi_battery_reach_threshold();
    int ambient_temperature = 0;
    struct battery_charge_param_s param;

    di->bat_exist = is_hisi_battery_exist();

    /* if battery is not present we assume it is on battery simulator
    *  if we are in factory mode, BAT FW is not updated yet, we use volt2Capacity
    */
    if ((!di->bat_exist) || (is_fake_battery) ||
            (strstr(saved_command_line, "androidboot.swtype=factory") && (COUL_BQ27510 == hisi_coulometer_type()))
         ){
        curr_capacity = calc_capacity_from_voltage();
    } else {
        curr_capacity = hisi_battery_capacity();
        ambient_temperature = 0;// getcalctemperature(0x02) * 10; //h00121290 mod temply
    }

    if((low_bat_flag & BQ27510_FLAG_LOCK) != BQ27510_FLAG_LOCK && is_low_power_locked){
        wake_unlock(&low_power_lock);
        is_low_power_locked = 0;
    }

    /* Debouncing of power on init. */
    if (di->capacity == -1) {
        di->capacity = curr_capacity;
        di->prev_capacity = curr_capacity;
        di->amb_temperature = ambient_temperature;
        return 1;
    }
    di->amb_temperature = ambient_temperature;

    if (modem_off) {
        dev_info(di->dev," modem off so shut down AP and curr_capacity = %d \n", curr_capacity);
        curr_capacity = 0;
        return 1;
    }
    /*Only availability if the capacity changed*/
    if (curr_capacity != di->prev_capacity) {
        if (abs(di->prev_capacity -curr_capacity) >= CHG_ODD_CAPACITY){
            dev_info(di->dev,"prev_capacity = %d \n"
            "curr_capacity = %d \n" "curr_voltage = %d \n",
            di->prev_capacity, curr_capacity,hisi_battery_voltage());
        }
    }

    if (curr_capacity < 2 ){
        di->capacity = curr_capacity;
        return 1;
    }

    switch(di->charge_status) {
    case POWER_SUPPLY_STATUS_CHARGING:
        curr_capacity = bq_force_full_timer(curr_capacity,di);
        break;

    case POWER_SUPPLY_STATUS_FULL:
        ret = hisi_battery_charge_param(&param);
        if(!ret){
            param.max_voltagemV = 4200;
        }
        if(hisi_battery_current_avg() >= 0)
            if(hisi_battery_voltage() >= (param.max_voltagemV-RECHG_PROTECT_THRESHOLD)){
                curr_capacity = 100;
                dev_info(di->dev,"Force soc=100\n");
            }
        di->charge_full_count = 0;
        break;

    case POWER_SUPPLY_STATUS_DISCHARGING:
    case POWER_SUPPLY_STATUS_NOT_CHARGING:
        /*capacity-count will always decrease when discharging || notcharging*/
        if(di->prev_capacity < curr_capacity)
            return 0;
        di->charge_full_count = 0;
        break;

    default:
        dev_err(di->dev, "%s defualt run.\n", __func__);
        break;
    }

    /*change monitoring interval from 10s to 30s when capacity greater than 90%*/
    if(curr_capacity > REACH_FULL_RESAMPLE_THRESHOLD) {
        di->monitoring_interval = REACH_FULL_SAMPLE_INTERVAL;
    } else if(curr_capacity < REACH_EMPTY_RESAMPLE_THRESHOLD) {
        di->monitoring_interval = REACH_EMPTY_SAMPLE_INTERVAL;
    } else {
        di->monitoring_interval = di->platform_data->monitoring_interval;
    }

    /*filter*/
    curr_capacity = bq_capacity_pulling_filter(curr_capacity,di);

    if(di->prev_capacity == curr_capacity)
        return 0;

    dev_info(di->dev,"Capacity Updated = %d, charge_full_count = %d, charge_status = %d\n",
                         curr_capacity, di->charge_full_count, di->charge_status);

    di->capacity = curr_capacity;
    di->prev_capacity = curr_capacity;
    return 1;
}

static int bq_charger_event(struct notifier_block *nb, unsigned long event,
            void *_data)
{
    struct bq_bci_device_info *di;
    int ret = 0;
    di = container_of(nb, struct bq_bci_device_info, nb);

    switch (event) {
    case VCHRG_START_USB_CHARGING_EVENT:
        di->usb_online = 1;
        di->ac_online = 0;
        di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
        di->charge_full_count = 0;
        break;

    case VCHRG_START_AC_CHARGING_EVENT:
        di->ac_online = 1;
        di->usb_online = 0;
        di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
        di->charge_full_count = 0;
        break;

    case VCHRG_STOP_CHARGING_EVENT:
        di->usb_online = 0;
        di->ac_online = 0;
        di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_UNKNOWN;
        di->charge_full_count = 0;
        break;

    case VCHRG_START_CHARGING_EVENT:
        di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
        break;

    case VCHRG_NOT_CHARGING_EVENT:
        di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
        break;
    case VCHRG_CHARGE_DONE_EVENT:
   /****Do not need charge status change to full when bq24192 chargedone.
    because bq27510 will insure the charge status to full when capacity is 100.
    *****************************************************************/
        if (strstr(saved_command_line, "androidboot.swtype=factory")){
            di->charge_status = POWER_SUPPLY_STATUS_FULL;
            di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
        }
        break;
    case VCHRG_POWER_SUPPLY_OVERVOLTAGE:
        di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
        break;

	case VCHRG_POWER_SUPPLY_WEAKSOURCE:
        di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	    di->power_supply_status = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
	break;

    case BATTERY_LOW_WARNING:
        break;
    case BATTERY_LOW_SHUTDOWN:
        wake_lock(&low_power_lock);
        is_low_power_locked = 1;
        break;
    default:
        dev_err(di->dev, "%s defualt run.\n", __func__);
        break;
    }

    if ((di->usb_online || di->ac_online) && di->capacity == 100)
        di->charge_status = POWER_SUPPLY_STATUS_FULL;
   /*in case charger can not get the report of charger removed, so
    * update the status of charger.*/
   if(get_charger_name() == CHARGER_REMOVED){
        di->usb_online = 0;
        di->ac_online = 0;
        di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;
        di->power_supply_status = POWER_SUPPLY_HEALTH_UNKNOWN;
        di->charge_full_count = 0;
   }

    if(event == VCHRG_CHARGE_DONE_EVENT)
        di->chargedone_stat = 1;
    else
        di->chargedone_stat = 0;
    dev_info(di->dev,"received event = %x, charge_status = %d\n",event,di->charge_status);
    power_supply_changed(&di->bat);
    return ret;
}

int bq_get_error_info(struct bq_bci_device_info *di)
{
    static int pre_bat_err =0, archive_state = 1;
    static unsigned long timeout_jiffies = 0;
    static int first_in = 1;
    static int pre_uf_capacity = 0;
    static int pre_capacity = 0, capacity_stay_count = 0;;
    static int pre_temp = 999, temp_stay_count = 0;
    static int online_delay_count = 0;
    int curr_by_coultype = 1;
    int bat_uf_capacity = 0;
    char val;
    if (COUL_SMARTSTAR == hisi_coulometer_type())
        curr_by_coultype = -1;

    di->bat_err = 0;

    if(!is_hisi_battery_exist())
        di->bat_err |= ERROR_BATT_NOT_EXIST;

    if(hisi_battery_temperature()< BQ2419x_COLD_BATTERY_THRESHOLD
           || hisi_battery_temperature()>= BQ2419x_HOT_BATTERY_THRESHOLD)
    {
        if(di->charge_status == POWER_SUPPLY_STATUS_NOT_CHARGING)
            di->bat_err |= ERROR_BATT_TEMP_STOP;
        if(di->charge_status == POWER_SUPPLY_STATUS_CHARGING)
            di->bat_err |= ERROR_BATT_TEMP_CHARGE;

        di->bat_err |= ERROR_BATT_TEMP_OUT;
        dev_info(di->dev,"batt temp = %d\n", hisi_battery_temperature());
    }

    if(di->charge_status == POWER_SUPPLY_STATUS_NOT_CHARGING
        && !(bq2419x_get_factory_flag())) {
        if(di->power_supply_status == POWER_SUPPLY_HEALTH_OVERVOLTAGE)
            di->bat_err |= ERROR_VBUS_OVERVOLTAGE;
        if(hisi_battery_voltage() > BATT_OVERVOLTAGE_THRES)
            di->bat_err |= ERROR_BATT_OVERVOLTAGE;

        di->bat_err |= ERROR_BATT_NOT_CHARGING;
    } else {
        if(hisi_battery_voltage() > BATT_OVERVOLTAGE_THRES
           || hisi_battery_voltage() < BATT_LOWVOLTAGE_THRES) {
            di->bat_err |= ERROR_BATT_VOLTAGE;
            dev_info(di->dev,"batt volt = %d\n", hisi_battery_voltage());
        }
    }

    if(di->chargedone_stat && hisi_battery_capacity() <= CHG_CANT_FULL_THRESHOLD){
        di->bat_err |= ERROR_PRE_CHARGEDONE;
        dev_info(di->dev,"batt capacity = %d\n", hisi_battery_capacity());
    }

    if(di->charge_status == POWER_SUPPLY_STATUS_CHARGING
       && hisi_battery_current_avg() <= 50
       && hisi_battery_current_avg() >= 10
       && (curr_by_coultype*hisi_battery_current()) <= 50
       && (curr_by_coultype*hisi_battery_current()) >= 10
       && di->capacity == 100) {
        di->bat_err |= ERROR_NO_CHARGEDONE;
        dev_info(di->dev,"batt curr = %d batt curr_avg = %d\n",
                         (curr_by_coultype*hisi_battery_current()), hisi_battery_current_avg());
    }

    if((!di->usb_online) && (!di->ac_online)){
        if((-hisi_battery_current() > 0) && (online_delay_count++ == 1)){
             di->bat_err |= ERROR_BAD_CURR_SENSOR;
             online_delay_count = 0;
             dev_info(di->dev,"batt curr = %d\n", (-hisi_battery_current()));
        }
    } else {
        online_delay_count = 0;
    }

    bat_uf_capacity = hisi_battery_unfiltered_capacity();
    if(first_in){
        pre_uf_capacity = bat_uf_capacity;
        pre_capacity = di->capacity;
        pre_temp = hisi_battery_uf_temperature();
        first_in = 0;
    } else {
        if (abs(pre_uf_capacity - bat_uf_capacity) >= 3) {
            if (100 != bat_uf_capacity) {
                di->bat_err |= ERROR_UFCAPCITY_DEBOUNCE_OTHER;
            }
            else {
                if (abs(pre_uf_capacity - bat_uf_capacity) > 10)
                    di->bat_err |= ERROR_UFCAPCITY_DEBOUNCE_100;
            }
            hisi_smartstar_print_cc_reg(2); //debug
        }
        pre_uf_capacity = bat_uf_capacity;
    }

    if(di->charge_status == POWER_SUPPLY_STATUS_NOT_CHARGING
       || di->charge_status == POWER_SUPPLY_STATUS_DISCHARGING) {
        if (pre_capacity > 0 && di->capacity != pre_capacity) {
            if(di->capacity > REACH_FULL_RESAMPLE_THRESHOLD) {
                if(capacity_stay_count <= 2) {
                    di->bat_err |= ERROR_CAPACITY_CHANGE_FAST;
                    capacity_stay_count = 0;
                }
            } else if (di->capacity < REACH_EMPTY_RESAMPLE_THRESHOLD) {
                if(capacity_stay_count <= 12) {
                    di->bat_err |= ERROR_CAPACITY_CHANGE_FAST;
                    capacity_stay_count = 0;
                }
            } else {
                if(capacity_stay_count <= 6) {
                    di->bat_err |= ERROR_CAPACITY_CHANGE_FAST;
                    capacity_stay_count = 0;
                }
            }
            capacity_stay_count = 0;
            dev_info(di->dev,"pre_capacity=%d capacity=%d\n", pre_capacity, di->capacity);
        } else {
            capacity_stay_count++;
        }
    }
    pre_capacity = di->capacity;

    if(hisi_battery_uf_temperature() == pre_temp) {
        if(di->capacity > REACH_FULL_RESAMPLE_THRESHOLD) {
            if(temp_stay_count >= 240) {
                di->bat_err |= ERROR_BATT_TEMP_STAY;
                temp_stay_count = 0;
            }
        } else if (di->capacity < REACH_EMPTY_RESAMPLE_THRESHOLD) {
            if(temp_stay_count >= 1440) {
                di->bat_err |= ERROR_BATT_TEMP_STAY;
                capacity_stay_count = 0;
            }
        } else {
            if(temp_stay_count >= 720) {
                di->bat_err |= ERROR_BATT_TEMP_STAY;
                temp_stay_count = 0;
            }
        }
        temp_stay_count = 0;
    } else {
        temp_stay_count++;
    }
    pre_temp = hisi_battery_uf_temperature();

    if (is_smartstar_fcc_debounce()) {
        di->bat_err |= ERROR_FCC_DEBOUNCE;
    }

    if(di->bat_err != pre_bat_err && archive_state == 1){
        timeout_jiffies = jiffies + msecs_to_jiffies(LOG_ARCH_DELAY_TIME);
        archive_state = 0;
        dev_info(di->dev,"(%s) BATT ERR = %x\n", hisi_battery_brand(), di->bat_err);
    }
    pre_bat_err = di->bat_err;

    if(time_is_before_jiffies(timeout_jiffies) && archive_state == 0){
        bq_log_exception_archive(di->bat_err);
        archive_state = 1;
    }

    return di->bat_err;
}

static void bq_get_battery_info(struct bq_bci_device_info *di)
{
    di->bat_rm = hisi_battery_rm();
    di->bat_fcc = hisi_battery_fcc();

    if (!(di->bat_exist)) {
        di->bat_health         = POWER_SUPPLY_HEALTH_UNKNOWN;
        di->bat_capacity_level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
        di->bat_technolog      = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
        di->bat_temperature    = 0;
    } else {
        di->bat_health         = hisi_battery_health();
        di->bat_capacity_level = hisi_battery_capacity_level();
        di->bat_technolog      = hisi_battery_technology();
        di->bat_temperature    = hisi_battery_temperature() ;
   }
}

static void bq_bci_battery_work(struct work_struct *work)
{
    struct bq_bci_device_info *di = container_of(work,
               struct bq_bci_device_info, bq_bci_monitor_work.work);

    bq_get_battery_info(di);

    bq_get_error_info(di);

    schedule_delayed_work(&di->bq_bci_monitor_work,
                 msecs_to_jiffies(1000 * di->monitoring_interval));

    if (capacity_changed(di)){
        power_supply_changed(&di->bat);
    }
}

#define to_bq_ac_device_info(x) container_of((x), \
         struct bq_bci_device_info, ac);

static int bq_ac_get_property(struct power_supply *psy,
                    enum power_supply_property psp,
                    union power_supply_propval *val)
{
    struct bq_bci_device_info *di = to_bq_ac_device_info(psy);

    switch (psp) {
    case POWER_SUPPLY_PROP_ONLINE:
        val->intval = di->ac_online;
        break;
    case POWER_SUPPLY_PROP_VOLTAGE_NOW:
        val->intval = bq_get_gpadc_conversion(di, ADC_VBATMON);
        break;
    case POWER_SUPPLY_PROP_HEALTH:
        val->intval = di->power_supply_status;
        break;
     default:
        return -EINVAL;
    }

    return 0;
}

#define to_bq_usb_device_info(x) container_of((x), \
         struct bq_bci_device_info, usb);

static int bq_usb_get_property(struct power_supply *psy,
                    enum power_supply_property psp,
                    union power_supply_propval *val)
{
    struct bq_bci_device_info *di = to_bq_usb_device_info(psy);

    switch (psp) {
    case POWER_SUPPLY_PROP_ONLINE:
        val->intval = di->usb_online;
        break;
    case POWER_SUPPLY_PROP_VOLTAGE_NOW:
        val->intval = bq_get_gpadc_conversion(di, ADC_VBATMON);
        break;
    case POWER_SUPPLY_PROP_HEALTH:
        val->intval = di->power_supply_status;
        break;
     default:
        return -EINVAL;
    }

    return 0;
}

#define to_bq_bk_bci_device_info(x) container_of((x), \
         struct bq_bci_device_info, bk_bat);

static int bq_bk_bci_battery_get_property(struct power_supply *psy,
                    enum power_supply_property psp,
                    union power_supply_propval *val)
{
    struct bq_bci_device_info *di = to_bq_bk_bci_device_info(psy);

    switch (psp) {
    case POWER_SUPPLY_PROP_VOLTAGE_NOW:
        /*Use gpadc channel for measuring bk battery voltage*/
        val->intval = bq_get_gpadc_conversion(di, ADC_VBATMON);
        break;
    default:
        return -EINVAL;
    }

    return 0;
}

#define to_bq_bci_device_info(x) container_of((x), \
                 struct bq_bci_device_info, bat);

static int bq_bci_battery_get_property(struct power_supply *psy,
                    enum power_supply_property psp,
                    union power_supply_propval *val)
{
    struct bq_bci_device_info *di;

    di = to_bq_bci_device_info(psy);

    switch (psp) {
    case POWER_SUPPLY_PROP_STATUS:
        val->intval = di->charge_status;
        break;
    case POWER_SUPPLY_PROP_VOLTAGE_NOW:
        di->bat_voltage = hisi_battery_voltage();
        if (COUL_SMARTSTAR == hisi_coulometer_type()){
            val->intval = hisi_battery_voltage_uv();
        }
        else{
            val->intval = di->bat_voltage * 1000;
        }
        break;
    case POWER_SUPPLY_PROP_CURRENT_NOW:
    case POWER_SUPPLY_PROP_CURRENT_AVG:
        di->bat_current = hisi_battery_current();
        if(COUL_SMARTSTAR == hisi_coulometer_type()){
            di->bat_current = -(di->bat_current);
        }
        val->intval = di->bat_current;
        break;
    case POWER_SUPPLY_PROP_TEMP:
        val->intval = di->bat_temperature * 10;
        break;
    case POWER_SUPPLY_PROP_TEMP_AMBIENT:
        val->intval = di->amb_temperature;
        break;
    case POWER_SUPPLY_PROP_PRESENT:
    case POWER_SUPPLY_PROP_ONLINE:
        val->intval = di->bat_exist;
        break;
    case POWER_SUPPLY_PROP_HEALTH:
        val->intval = di->bat_health;
        break;
    case POWER_SUPPLY_PROP_CAPACITY:
        if (modem_off) {
            val->intval = 0;
        }else{
            val->intval = di->capacity;
        }
        break;
    case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
        val->intval = di->bat_capacity_level;
        break;
    case POWER_SUPPLY_PROP_TECHNOLOGY:
        val->intval = di->bat_technolog;
        break;
    case POWER_SUPPLY_PROP_CAPACITY_RM:
        val->intval = di->bat_rm;
        break;
    case POWER_SUPPLY_PROP_CAPACITY_FCC:
        val->intval = di->bat_fcc;
        break;
    case POWER_SUPPLY_PROP_VOLTAGE_MAX:
         val->intval = di->limited_charge_voltagemV;
        break;
    default:
        return -EINVAL;
    }
    return 0;
}
int bq_bci_show_capacity(void)
{
    struct bq_bci_device_info *di = g_bq_bci_dev;

    if (di)
        return di->capacity;
    else
        return 0;
}
int bq_register_notifier(struct notifier_block *nb,
                         unsigned int events)
{
    return blocking_notifier_chain_register(&notifier_list, nb);
}
EXPORT_SYMBOL_GPL(bq_register_notifier);

int bq_unregister_notifier(struct notifier_block *nb,
                           unsigned int events)
{
    return blocking_notifier_chain_unregister(&notifier_list, nb);
}
EXPORT_SYMBOL_GPL(bq_unregister_notifier);

static char *bq_bci_supplied_to[] = {
    "bq_bci_battery",
};

static int bq_get_max_charge_voltage(struct bq_bci_device_info *di)
{
    bool ret = 0;
    int battery_id_status = 0;

    di->limited_charge_voltagemV = 4200;
    battery_id_status = get_battery_id();
    switch(battery_id_status){
    case BAT_ID_10K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_10k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_22K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_22k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_39K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_39k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_68K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_68k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_110K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_110k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_200K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_200k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_470K_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_470k", &di->limited_charge_voltagemV, NULL);
        break;
    case BAT_ID_2M_STATUS:
         ret = get_hw_config_int("gas_gauge/charge_voltage_2m", &di->limited_charge_voltagemV, NULL);
        break;
    default:
         ret = get_hw_config_int("gas_gauge/charge_voltage",&di->limited_charge_voltagemV, NULL);
        break;
    }
    if(ret){
        return true;
    }else{
        di->limited_charge_voltagemV = 4200;
        dev_err(di->dev, "boardid does not set limited charge voltage\n");
        return false;
    }

}

static int __devinit bq_bci_battery_probe(struct platform_device *pdev)
{
    struct bq_bci_platform_data *pdata = pdev->dev.platform_data;
    struct bq_bci_device_info *di;
    int low_bat_flag = 0;
    int ret = 0;
    unsigned int i = 0;

    if (!pdata) {
        dev_dbg(&pdev->dev, "platform_data not available\n");
        return -EINVAL;
    }

    di = kzalloc(sizeof(*di), GFP_KERNEL);
    if (!di)
        return -ENOMEM;
    g_bq_bci_dev = di;

    di->platform_data = kmemdup(pdata, sizeof(*pdata), GFP_KERNEL);
    if (!di->platform_data) {
        kfree(di);
        return -ENOMEM;
    }

    /* Get I2C client - bq27510 */
/*
    if(g_battery_measure_by_bq27510_i2c_client) {
       dev27510.client = g_battery_measure_by_bq27510_i2c_client;
    } else {
        dev_err(&pdev->dev, "%s failed, check bq27510 module installed...\n", __func__);
    }
*/

    if (pdata->monitoring_interval == 0) {
        di->monitoring_interval = NORMAL_SAMPLE_INTERVAL;
    } else {
        di->monitoring_interval = pdata->monitoring_interval;
    }

    bq_get_max_charge_voltage(di);

    di->platform_data = pdata;

    di->max_charger_currentmA = pdata->max_charger_currentmA;
    di->max_charger_voltagemV = pdata->max_bat_voltagemV;
    di->termination_currentmA = pdata->termination_currentmA;
    di->regulation_voltagemV = pdata->max_bat_voltagemV;
    di->low_bat_voltagemV = pdata->low_bat_voltagemV;
    di->battery_tmp_tbl = pdata->battery_tmp_tbl;
    di->tblsize = pdata->tblsize;


    di->dev = &pdev->dev;

    di->bat.name = "Battery";
    di->bat.supplied_to = bq_bci_supplied_to;
    di->bat.num_supplicants = ARRAY_SIZE(bq_bci_supplied_to);
    di->bat.type = POWER_SUPPLY_TYPE_BATTERY;
    di->bat.properties = bq_bci_battery_props;
    di->bat.num_properties = ARRAY_SIZE(bq_bci_battery_props);
    di->bat.get_property = bq_bci_battery_get_property;
    di->bat_health = POWER_SUPPLY_HEALTH_GOOD;
    di->bat_exist = is_hisi_battery_exist();
    di->bat_err = 0;

    di->usb.name = "USB";
    di->usb.type = POWER_SUPPLY_TYPE_USB;
    di->usb.properties = bq_usb_props;
    di->usb.num_properties = ARRAY_SIZE(bq_usb_props);
    di->usb.get_property = bq_usb_get_property;
    di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;

    di->ac.name = "Mains";
    di->ac.type = POWER_SUPPLY_TYPE_MAINS;
    di->ac.properties = bq_ac_props;
    di->ac.num_properties = ARRAY_SIZE(bq_ac_props);
    di->ac.get_property = bq_ac_get_property;

    di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;

    di->bk_bat.name = "bq_bk_battery";
    di->bk_bat.type = POWER_SUPPLY_TYPE_UPS;
    di->bk_bat.properties = bq_bk_bci_battery_props;
    di->bk_bat.num_properties = ARRAY_SIZE(bq_bk_bci_battery_props);
    di->bk_bat.get_property = bq_bk_bci_battery_get_property;

    di->capacity = -1;
    di->capacity_filter_count = 0;
    di->charge_full_count = 0;

    for(i=0;i<WINDOW_LEN;i++) {
            capacity_filter[i] = hisi_battery_capacity();
            capacity_sum += capacity_filter[i];
    }

    bq_get_battery_info(di);

    platform_set_drvdata(pdev, di);

    wake_lock_init(&low_power_lock, WAKE_LOCK_SUSPEND, "low_power_wake_lock");

    low_bat_flag = is_hisi_battery_reach_threshold();
    if(( low_bat_flag & BQ27510_FLAG_LOCK ) == BQ27510_FLAG_LOCK) {
        wake_lock(&low_power_lock);
        is_low_power_locked = 1;
    }

    ret = power_supply_register(&pdev->dev, &di->bat);
    if (ret) {
        dev_dbg(&pdev->dev, "failed to register main battery\n");
        goto batt_failed;
    }

    ret = power_supply_register(&pdev->dev, &di->usb);
    if (ret) {
        dev_dbg(&pdev->dev, "failed to register usb power supply\n");
        goto usb_failed;
    }

    ret = power_supply_register(&pdev->dev, &di->ac);
    if (ret) {
        dev_dbg(&pdev->dev, "failed to register ac power supply\n");
        goto ac_failed;
    }

    ret = power_supply_register(&pdev->dev, &di->bk_bat);
    if (ret) {
        dev_dbg(&pdev->dev, "failed to register backup battery\n");
        goto bk_batt_failed;
    }

    INIT_DELAYED_WORK_DEFERRABLE(&di->bq_bci_monitor_work,
                bq_bci_battery_work);
    schedule_delayed_work(&di->bq_bci_monitor_work, 0);

    di->nb.notifier_call = bq_charger_event;
    bq_register_notifier(&di->nb, 1);

    return 0;

bk_batt_failed:
    cancel_delayed_work(&di->bq_bci_monitor_work);
    power_supply_unregister(&di->ac);
ac_failed:
    power_supply_unregister(&di->usb);
usb_failed:
    power_supply_unregister(&di->bat);
batt_failed:
    wake_lock_destroy(&low_power_lock);
    platform_set_drvdata(pdev, NULL);
    kfree(di);
    di = NULL;
    return ret;
}

static int __devexit bq_bci_battery_remove(struct platform_device *pdev)
{
    struct bq_bci_device_info *di = platform_get_drvdata(pdev);

    if (di == NULL) {
        dev_err(&pdev->dev, "di is NULL!\n");
        return -ENODEV;
    }

    bq_unregister_notifier(&di->nb, 1);
    cancel_delayed_work(&di->bq_bci_monitor_work);

    power_supply_unregister(&di->bat);
    power_supply_unregister(&di->usb);
    power_supply_unregister(&di->ac);
    power_supply_unregister(&di->bk_bat);
    wake_lock_destroy(&low_power_lock);
    platform_set_drvdata(pdev, NULL);
    kfree(di->platform_data);
    kfree(di);
    di = NULL;

    return 0;
}

static void bq_bci_battery_shutdown(struct platform_device *pdev)
{
    struct bq_bci_device_info *di = platform_get_drvdata(pdev);

    if (di == NULL) {
        dev_err(&pdev->dev, "di is NULL!\n");
        return;
    }

    cancel_delayed_work(&di->bq_bci_monitor_work);

    wake_lock_destroy(&low_power_lock);

    return;
}

#ifdef CONFIG_PM
static int bq_bci_battery_suspend(struct device *dev)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct bq_bci_device_info *di = platform_get_drvdata(pdev);

    if (di == NULL) {
        dev_err(&pdev->dev, "di is NULL!\n");
        return -ENODEV;
    }
    suspend_capacity = hisi_battery_capacity();

    cancel_delayed_work(&di->bq_bci_monitor_work);

    return 0;
}

static int bq_bci_battery_resume(struct device *dev)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct bq_bci_device_info *di = platform_get_drvdata(pdev);
    int i = 0, resume_capacity = 0;

    if (di == NULL) {
        dev_err(&pdev->dev, "di is NULL!\n");
        return -ENODEV;
    }
    resume_capacity = hisi_battery_capacity();
    if(di->charge_status == POWER_SUPPLY_STATUS_DISCHARGING
        || di->charge_status == POWER_SUPPLY_STATUS_NOT_CHARGING) {
        if ((suspend_capacity - resume_capacity)>=2) {
            capacity_sum = 0;
            for(i=0;i<WINDOW_LEN;i++) {
                    capacity_filter[i] = resume_capacity;
                    capacity_sum += capacity_filter[i];
            }
        }
    }
    schedule_delayed_work(&di->bq_bci_monitor_work, 0);

    return 0;
}
#else
#define bq_bci_battery_suspend	NULL
#define bq_bci_battery_resume	NULL
#endif /* CONFIG_PM */

static const struct dev_pm_ops pm_ops = {
    .suspend = bq_bci_battery_suspend,
    .resume = bq_bci_battery_resume,
};

static struct platform_driver bq_bci_battery_driver = {
    .probe = bq_bci_battery_probe,
    .remove = __devexit_p(bq_bci_battery_remove),
    .shutdown = bq_bci_battery_shutdown,
    .driver = {
        .name = "bq_bci_battery",
        .pm = &pm_ops,
    },
};

static int __init bq_battery_init(void)
{
    return platform_driver_register(&bq_bci_battery_driver);
}

module_init(bq_battery_init);

static void __exit bq_battery_exit(void)
{
    platform_driver_unregister(&bq_bci_battery_driver);
}

module_exit(bq_battery_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:bq_bci");
MODULE_AUTHOR("HUAWEI Inc");

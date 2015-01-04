/*
 *  apds990x.c - Linux kernel modules for ambient light + proximity sensor
 *
 *  Copyright (C) 2010 Lee Kai Koon <kai-koon.lee@avagotech.com>
 *  Copyright (C) 2010 Avago Technologies
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/input.h>
#include <linux/earlysuspend.h>
#include "apds990x.h"
#include <linux/board_sensors.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <asm/io.h>
#include <linux/mux.h>
#include <linux/wakelock.h>
#include <hsad/config_interface.h>
#include <linux/mtd/nve_interface.h>
#include "../../../device/hsad_sensor.h"


#define DEBUG 1

/* Change History
 *
 * 1.0.1	Functions apds990x_show_rev(), apds990x_show_id() and apds990x_show_status()
 *			have missing CMD_BYTE in the i2c_smbus_read_byte_data(). APDS-990x needs
 *			CMD_BYTE for i2c write/read byte transaction.
 *
 *
 * 1.0.2	Include PS switching threshold level when interrupt occurred
 *
 *
 * 1.0.3	Implemented ISR and delay_work, correct PS threshold storing
 *
 * 1.0.4	Added Input Report Event
 */

/*
 * Management functions
 */
#define  MAX_ADC_PROX_VALUE  1023
#define  PS_FIRST_LOW_VALUE  549
#define  PS_FIRST_VALUE      550
#define 	FAR_THRESHOLD(x)		(min_proximity_value<(x)?(x):min_proximity_value)
#define 	NEAR_THRESHOLD(x)		((FAR_THRESHOLD(x) + apds_990x_pwindows_value - 1)>1022?1022:(FAR_THRESHOLD(x) + apds_990x_pwindows_value - 1))
#define  	MAX_FAR_THRESHOLD  MAX_ADC_PROX_VALUE - apds_990x_pwindows_value-1//723

#define  DELAY_FOR_DATA_RADY            300

static struct wake_lock wlock;
static int lux_old = 300;
static int IC_old = 0;
static int min_proximity_value;
static int apds_990x_pwindows_value = 300;
static int apds_990x_pwave_value = 250;
static int ps_h, ps_l = 0;
static int ps_pulse_count=5;
static int als_polling_count;
static unsigned int apds_type = 0;
static unsigned int threshold_value = 0;
static int tp_color_for_edge = 0;
//extern unsigned int lcd_product_id;
static int get_reg = 0;
static ssize_t store_get_reg_value(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	get_reg = simple_strtoul(buf, NULL, 10);
	return count;
}

static ssize_t show_get_reg_value(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	int value = 0;

	value = i2c_smbus_read_byte_data(data->client, get_reg);
	return snprintf(buf, PAGE_SIZE, "%X\n", value);
}
DEVICE_ATTR(get_reg_value, 0664, show_get_reg_value, store_get_reg_value);

static int apds990x_set_command(struct i2c_client *client, int command)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;
	int clearInt;

	if (command == 0)
		clearInt = CMD_CLR_PS_INT;
	else if (command == 1)
		clearInt = CMD_CLR_ALS_INT;
	else
		clearInt = CMD_CLR_PS_ALS_INT;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte(client, clearInt);
	mutex_unlock(&data->update_lock);

	return ret;
}
static int read_tp_color_from_nv(void)
{
	int ret;
	struct nve_info_user user_info;

	user_info.nv_operation = 1;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "TPCOLOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name)-1]='\0';
	ret = nve_direct_access(&user_info);
	if (ret)
	{
		printk(KERN_ERR "nve_direct_access read error(%d)\n", ret);
		return 0;
	}
	if(!strncmp(user_info.nv_data, "pink", 4)) ret = 1;
	else if(!strncmp(user_info.nv_data, "white", 5)) ret = 2;
	else if(!strncmp(user_info.nv_data, "black", 5)) ret = 0;
	else
	{
		printk("err: read_tp_color_from_nv read unormal value!!\n");
		ret = 0;
	}
	return ret;
}


//write offset value to nv partation
static int write_tp_color_to_nv(void)
{
	int ret;
	struct nve_info_user user_info;
	user_info.nv_operation = 0;
	user_info.nv_number = 16;
	user_info.valid_size = 15;
	strncpy(user_info.nv_name, "TPCOLOR", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name)-1]='\0';

	user_info.nv_data[0] = 'w';
	user_info.nv_data[1] = 'h';
	user_info.nv_data[2] = 'i';
	user_info.nv_data[3] = 't';
	user_info.nv_data[4] = 'e';

	ret = nve_direct_access(&user_info);
	if (ret)
	{
		printk(KERN_ERR "nve_direct_access write error(%d)\n", ret);
		return -1;
	}
	printk( "write gsensor_offset (%d %d %d )\n",user_info.nv_data[0],user_info.nv_data[1],user_info.nv_data[2]);
	return ret;
}
static int apds990x_regulator_configure(struct apds990x_data *data, struct i2c_client *client)
{
	int rc;

	data->apds990x_vdd = regulator_get(&client->dev, "SENSORS_ANALOG_VDD");
	if (IS_ERR(data->apds990x_vdd)) {
		rc = PTR_ERR(data->apds990x_vdd);
		dev_err(&client->dev,
			"Regulator get failed apds990x_vdd rc=%d\n", rc);
		return rc;
	}

	rc = regulator_set_voltage(data->apds990x_vdd, 2850000,
							2850000);
		if (rc) {
			dev_err(&client->dev,
				"regulator set_vtg failed rc=%d\n", rc);
			return rc;
		}

       data->apds990x_io_vdd = regulator_get(&client->dev, "SENSOR_IO_VDD");
	if (IS_ERR(data->apds990x_io_vdd)) {
		rc = PTR_ERR(data->apds990x_io_vdd);
		dev_err(&client->dev,
			"Regulator get failed apds990x_io_vdd rc=%d\n", rc);
		return rc;
	}

	return 0;
}
static int  apds990x_regulator_enable(struct apds990x_data *data)
{
	int rc = 1;

	rc = regulator_enable(data->apds990x_vdd);
	if (rc) {
		printk(KERN_ERR "Regulator apds990x_vdd enable failed rc=%d\n", rc);
		return rc;
		}


	rc = regulator_enable(data->apds990x_io_vdd);
	if (rc) {
		printk(KERN_ERR "Regulator apds990x_io_vdd enable failed rc=%d\n", rc);
		return rc;
	}
	return 0;
}
static int  apds990x_regulator_disable(struct apds990x_data *data)
{
	int rc = 1;
	rc = regulator_disable(data->apds990x_vdd);
	if (rc) {
		printk(KERN_ERR "Regulator apds990x_vdd disable failed rc=%d\n", rc);
		return rc;
		}

	rc = regulator_disable(data->apds990x_io_vdd);
	if (rc) {
		printk(KERN_ERR "Regulator apds990x_io_vdd disable failed rc=%d\n", rc);
		return rc;
	}
	return 0;
}

static int apds990x_set_enable(struct i2c_client *client, int enable)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_ENABLE_REG, enable);
	mutex_unlock(&data->update_lock);

	data->enable = enable;

	return ret;
}

static int apds990x_set_atime(struct i2c_client *client, int atime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_ATIME_REG, atime);
	mutex_unlock(&data->update_lock);

	data->atime = atime;

	return ret;
}

static int apds990x_set_ptime(struct i2c_client *client, int ptime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_PTIME_REG, ptime);
	mutex_unlock(&data->update_lock);

	data->ptime = ptime;

	return ret;
}

static int apds990x_set_wtime(struct i2c_client *client, int wtime)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_WTIME_REG, wtime);
	mutex_unlock(&data->update_lock);

	data->wtime = wtime;

	return ret;
}

static int apds990x_set_ailt(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_AILTL_REG, threshold);
	mutex_unlock(&data->update_lock);

	data->ailt = threshold;

	return ret;
}

static int apds990x_set_aiht(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_AIHTL_REG, threshold);
	mutex_unlock(&data->update_lock);

	data->aiht = threshold;

	return ret;
}

static int apds990x_set_pilt(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_PILTL_REG, threshold);
	mutex_unlock(&data->update_lock);

	data->pilt = threshold;

	return ret;
}

static int apds990x_set_piht(struct i2c_client *client, int threshold)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_PIHTL_REG, threshold);
	mutex_unlock(&data->update_lock);

	data->piht = threshold;

	return ret;
}

static int apds990x_set_pers(struct i2c_client *client, int pers)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_PERS_REG, pers);
	mutex_unlock(&data->update_lock);

	data->pers = pers;

	return ret;
}

static int apds990x_set_config(struct i2c_client *client, int config)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_CONFIG_REG, config);
	mutex_unlock(&data->update_lock);

	data->config = config;

	return ret;
}

static int apds990x_set_ppcount(struct i2c_client *client, int ppcount)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_PPCOUNT_REG, ppcount);
	mutex_unlock(&data->update_lock);

	data->ppcount = ppcount;

	return ret;
}

static int apds990x_set_control(struct i2c_client *client, int control)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int ret;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_CONTROL_REG, control);
	mutex_unlock(&data->update_lock);

	data->control = control;

	/* obtain ALS gain value */
	if ((data->control & 0x03) == 0x00) /* 1X Gain */
		data->als_gain = 1;
	else if ((data->control & 0x03) == 0x01) /* 8X Gain */
		data->als_gain = 8;
	else if ((data->control & 0x03) == 0x02) /* 16X Gain */
		data->als_gain = 16;
	else  /* 120X Gain */
		data->als_gain = 120;

	return ret;
}

static int LuxCalculation(struct i2c_client *client, int cdata, int irdata)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int luxValue = 0;

	int IAC1 = 0;
	int IAC2 = 0;
	int IAC = 0;
	int GA;
	int COE_B;
	int COE_C;
	int COE_D;
	int DF = 52;

	if((data->enable_ps_sensor == 1 && cdata >= 6144) || (cdata >= 37886 && data->enable_ps_sensor == 0))  return 10000;
//       GA=5000;
	COE_B=2117;
	COE_C=76;
	COE_D=78;
	IAC1 = (cdata - (COE_B*irdata)/1000);	// re-adjust COE_B to avoid 2 decimal point
	IAC2 = ((COE_C*cdata)/1000 - (COE_D*irdata)/1000); // re-adjust COE_C and COE_D to void 2 decimal point

	if (IAC1 > IAC2)
		IAC = IAC1;
	else IAC = IAC2;

	if(IAC < 0) IAC =IC_old;
	else IC_old = IAC;

	if(E_APDS_TYPE_U9701L==apds_type)
	{
		GA=220;
		if(cdata < 21*irdata/10)
			GA = GA*100/230;
		if(cdata >= 21*irdata/10&& cdata < 50*irdata/10)
			GA = GA*100/112;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/10)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if(E_APDS_TYPE_U9700L==apds_type)
	{
		GA=5000;
		if(cdata < 225*irdata/100)
			GA = GA*100/200;
		else if(cdata >= 225*irdata/100 && cdata <= 50*irdata/10 )
			GA= GA *100/160;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if(E_APDS_TYPE_U9700G==apds_type)
	{
		GA=290;
		if(cdata < 21*irdata/10)
			GA = GA*100/260;
		if(cdata >= 21*irdata/10 && cdata < 22*irdata/10 )
			GA= GA *100/180;
		else if(cdata >= 22*irdata/10 && cdata < 50*irdata/10 )
			GA= GA *100/115;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/10)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if (E_APDS_TYPE_EDGE == apds_type)
	{
		GA=420;
		if(cdata < 215*irdata/100)
			GA = GA*100/310;
		else if(cdata >= 215*irdata/100 && cdata <= 40*irdata/10 )
			GA= GA *100/125;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/10)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if (E_APDS_TYPE_EDGE_N == apds_type)
	{
	//粉色product  id为0的手机用的是黑色手机的油墨，因此需要和其他粉色的区分
		//if((tp_color_for_edge == 2) || (tp_color_for_edge == 1 && lcd_product_id != 0)) //white or pink(pro_id==0) TP
		if((tp_color_for_edge == 2) || (tp_color_for_edge == 1 ))
		{
			GA=3100;
			if(cdata < 234*irdata/100)
				GA = GA *100/120;
			else if(cdata >= 234*irdata/100 && cdata <= 40*irdata/10 )
				GA= GA *100/137;
			else
				GA = GA;
			luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
		}
		else //(black TP)
		{
			GA=6000;
			if(cdata < 220*irdata/100)
				GA = GA*100/230;
			else if(cdata >= 220*irdata/100 && cdata <= 40*irdata/10 )
				GA= GA *100/160;
			else
				GA = GA ;
			luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
		}
	}
	else if (E_APDS_TYPE_OSCAR == apds_type)
	{
		GA=3750;
		if(cdata < 220*irdata/100)
			GA = GA*100/90;
		else if(cdata >= 220*irdata/100 && cdata <= 40*irdata/10 )
			GA= GA *100/125;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else if (E_APDS_TYPE_SOPHIA == apds_type)
	{
		GA=4300;
		if(cdata < 220*irdata/100)
			GA = GA*100/90;
		else if(cdata >= 220*irdata/100 && cdata <= 40*irdata/10 )
			GA= GA *100/110;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	else
	{
		GA=3600;
		if(cdata < 215*irdata/100)
			GA = GA*100/150;
		else if(cdata >= 215*irdata/100 && cdata <= 50*irdata/10 )
			GA= GA *100/145;
		else
			GA = GA ;
		luxValue = ((IAC*GA*DF)/1000)/(((272*(256-data->atime))/100) *data->als_gain);
	}
	return luxValue;
}

static int loop = 10;
static void apds990x_change_ps_threshold(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

	int pthreshold_h = 0, pthreshold_l = 0;
	data->ps_data =	i2c_smbus_read_word_data(client, CMD_WORD|APDS990x_PDATAL_REG);

        if ((data->ps_data + apds_990x_pwave_value) < min_proximity_value && (data->ps_data >= 0))
        {
            min_proximity_value = data->ps_data + apds_990x_pwave_value;
            i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, FAR_THRESHOLD(threshold_value));
            i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value));
        }
//	printk("ps_data = %d min_proximity_value = %d pthreshold_h = %d pthresold_l= %d\n",data->psdata,min_proximity_value,pthreshold_h,pthreshold_l);
        pthreshold_h = i2c_smbus_read_word_data(client,CMD_WORD| APDS990x_PIHTL_REG);
        pthreshold_l = i2c_smbus_read_word_data(client, CMD_WORD|APDS990x_PILTL_REG);
		/* far-to-near detected */
//	printk("ps_data = %d min_proximity_value = %d pthreshold_h = %d pthresold_l= %d\n",data->ps_data,min_proximity_value,pthreshold_h,pthreshold_l);
        if (data->ps_data >= pthreshold_h)/*near*/
        {
            data->ps_detection = 1;
            i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, FAR_THRESHOLD(threshold_value));
	    i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PIHTL_REG, 1023);

            input_report_abs(data->input_dev_ps, ABS_DISTANCE, 0);/* FAR-to-NEAR detection */
            input_sync(data->input_dev_ps);
        }
        /* if less than the value of  proximity low threshold we set*/
        /* the condition of pdata==pthreshold_l is valid */
        else if (data->ps_data <=  pthreshold_l)/*far*/
        {
            data->ps_detection = 0;
            //i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, 0);
            i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value));
	    if (!loop){
	        i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, 0);
	    } else {
	        loop--;
	    }

            input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);/* NEAR-to-FAR detection */
	    input_sync(data->input_dev_ps);

        }
        /*on 27a platform ,bug info is a lot*/
        else
        {
            printk("Wrong status!\n");
            i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, FAR_THRESHOLD(threshold_value));
        }

		pthreshold_h = i2c_smbus_read_word_data(client,CMD_WORD| APDS990x_PIHTL_REG);
        pthreshold_l = i2c_smbus_read_word_data(client, CMD_WORD|APDS990x_PILTL_REG);
        ps_h = pthreshold_h;
        ps_l = pthreshold_l;


}

static void apds990x_change_als_threshold(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);
	int cdata, irdata;
	int luxValue = 0;

	cdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_CDATAL_REG);
	irdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_IRDATAL_REG);

	luxValue = LuxCalculation(client, cdata, irdata);

	luxValue = luxValue > 0 ? luxValue : 0;
	luxValue = luxValue < 10000 ? luxValue : 10000;

	/* check PS under sunlight */
	if ((data->ps_detection == 1) &&
			(irdata > 5500)) {
		/*PS was previously in far-to-near condition*/
		/* need to inform input event as there will be no interrupt from the PS */
		/* NEAR-to-FAR detection */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);

		input_sync(data->input_dev_ps);

		//i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, 0);
	       i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value));
		data->pilt = 0;
		data->piht = data->ps_threshold;

		data->ps_detection = 0;	/* near-to-far detected */

		dev_dbg(&client->dev, "apds_990x_proximity_handler = FAR\n");
	}


	input_report_abs(data->input_dev_als, ABS_MISC, luxValue); /* report the lux level */
	input_sync(data->input_dev_als);

	data->als_data = cdata;

	data->als_threshold_l = (data->als_data *
		(100 - APDS990x_ALS_THRESHOLD_HSYTERESIS)) / 100;
	data->als_threshold_h = (data->als_data *
		(100 + APDS990x_ALS_THRESHOLD_HSYTERESIS)) / 100;

	if (data->als_threshold_h >= 65535)
		data->als_threshold_h = 65535;

	i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_AILTL_REG, data->als_threshold_l);

	i2c_smbus_write_word_data(client,
		CMD_WORD | APDS990x_AIHTL_REG, data->als_threshold_h);
}

static void apds990x_reschedule_work(struct apds990x_data *data,
					  unsigned long delay)
{
	/* unsigned long flags; */
    /* dev_dbg(&client->dev, "reschedule_work enter\n");*/
	/* spin_lock_irqsave(&data->update_lock, flags);*/

	/*
	 * If work is already scheduled then subsequent schedules will not
	 * change the scheduled time that's why we have to cancel it first.
	 */
	__cancel_delayed_work(&data->dwork);
	queue_delayed_work(data->ps_wq, &data->dwork, delay);

	/* spin_unlock_irqrestore(&data->update_lock, flags); */
}

/* ALS polling routine */
static void apds990x_als_polling_work_handler(struct work_struct *work)
{
	struct apds990x_data *data = container_of(work, struct apds990x_data, als_dwork.work);
	struct i2c_client *client = data->client;
	int cdata, irdata, pdata;
	int luxValue = 0;

	cdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_CDATAL_REG);
	irdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_IRDATAL_REG);
	pdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_PDATAL_REG);
	if(irdata < 0 ||cdata < 0 || pdata < 0)
	{
	   dev_err(&client->dev, "apds990x: als read i2c read fail!cdata(%d),irdata(%d),pdata(%d)\n", cdata, irdata, pdata);
	}
	luxValue = LuxCalculation(client, cdata, irdata);
	if(luxValue < 0)
	{
	   input_report_abs(data->input_dev_als, ABS_MISC, lux_old); // report the lux level
	   input_sync(data->input_dev_als);
	   dev_err(&client->dev,"apds990x:luxvaule = %d!\n", luxValue);
	   return;
	}
	luxValue = luxValue < 10000 ? luxValue : 10000;
	lux_old = luxValue;
	//printk("%s: lux = %d cdata = %d  irdata = %d pdata = %d \n", __func__, luxValue, cdata, irdata, pdata);

	/* check PS under sunlight */
	if ((data->ps_detection == 1) && (irdata > 5500)) {

		/* PS was previously in far-to-near condition*/
		/* need to inform input event as there will be no interrupt from the PS */

		/* NEAR-to-FAR detection */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);

		//i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PILTL_REG, 0);
		i2c_smbus_write_word_data(client, CMD_WORD|APDS990x_PIHTL_REG, NEAR_THRESHOLD(threshold_value));
		data->pilt = 0;
		data->piht = data->ps_threshold;

		data->ps_detection = 0;	/* near-to-far detected */

		dev_dbg(&client->dev, "apds_990x_proximity_handler = FAR\n");
	}
	if( als_polling_count <5 )
	{
		if(luxValue == 10000)
			luxValue = luxValue - als_polling_count%2;
		else
			luxValue = luxValue + als_polling_count%2;
		als_polling_count++;
	}
	input_report_abs(data->input_dev_als, ABS_MISC, luxValue); /* report the lux level */
	input_sync(data->input_dev_als);

	if((E_APDS_TYPE_U9701L==apds_type)||(E_APDS_TYPE_U9700G==apds_type))
	{
		if(data->enable_ps_sensor == 0)
		{
			if(cdata >35000)
			{
				if(data->als_gain!=1)
				{
					apds990x_set_enable(client, 0x00);//close
					apds990x_set_control(client, 0x20);
					apds990x_set_enable(client, 0x03);//open
					msleep(400);
					//return;//break;
				}
			}
			else if(cdata <1800)
			{
				if(data->als_gain!=16)
				{
					apds990x_set_enable(client, 0x00);//close
					apds990x_set_control(client, 0x22);
					apds990x_set_enable(client, 0x03);//open
					msleep(400);
					//return;//break;
				}
			}
		 }
	}

	/* restart timer */
	schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(data->als_poll_delay));
}

/* PS interrupt routine */
static void apds990x_work_handler(struct work_struct *work)
{
	struct apds990x_data *data = container_of(work,
		struct apds990x_data, dwork.work);
	struct i2c_client *client = data->client;
	int	status;
	int cdata,irdata;


	status = i2c_smbus_read_byte_data(client, CMD_BYTE | APDS990x_STATUS_REG);
	irdata = i2c_smbus_read_word_data(client, CMD_WORD|APDS990x_IRDATAL_REG);

	/* disable 990x's ADC first */
	i2c_smbus_write_byte_data(client, CMD_BYTE | APDS990x_ENABLE_REG, 1);

	dev_dbg(&client->dev, "status = %x\n", status);

	if ((status & data->enable & 0x30) == 0x30) {/*not used*/
		/* both PS and ALS are interrupted */
		apds990x_change_als_threshold(client);

		cdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_CDATAL_REG);
		if (irdata < 5500)
			apds990x_change_ps_threshold(client);
		else {
			if (data->ps_detection == 1) {
				apds990x_change_ps_threshold(client);
			} else {
				dev_dbg(&client->dev, "Triggered by background ambient noise\n");
			}
		}

		apds990x_set_command(client, 2);	/* 2 = CMD_CLR_PS_ALS_INT */
	} else if ((status & data->enable & 0x20) == 0x20) {
		/* only PS is interrupted */

		/* check if this is triggered by background ambient noise */
		cdata = i2c_smbus_read_word_data(client,
			CMD_WORD | APDS990x_CDATAL_REG);
		if (irdata < 5500)
			apds990x_change_ps_threshold(client);
		else {
			if (data->ps_detection == 1) {
				apds990x_change_ps_threshold(client);
			} else {
				dev_dbg(&client->dev, "Triggered by background ambient noise\n");
			}
		}

		apds990x_set_command(client, 0);	/* 0 = CMD_CLR_PS_INT */
	} else if ((status & data->enable & 0x10) == 0x10) {/*not used*/
		/* only ALS is interrupted */
		apds990x_change_als_threshold(client);

		apds990x_set_command(client, 1);	/* 1 = CMD_CLR_ALS_INT */
	}

	i2c_smbus_write_byte_data(client,
		CMD_BYTE | APDS990x_ENABLE_REG, data->enable);
	enable_irq(data->irq);
}

/* assume this is ISR */
static irqreturn_t apds990x_interrupt(int vec, void *info)
{
	struct i2c_client *client = (struct i2c_client *)info;
	struct apds990x_data *data = i2c_get_clientdata(client);
	wake_lock_timeout(&wlock, HZ);
	disable_irq_nosync(data->irq);
	apds990x_reschedule_work(data, 0);

	return IRQ_HANDLED;
}

/*
 * SysFS support
 */

static ssize_t apds990x_show_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->enable_ps_sensor);
}

static ssize_t apds990x_store_enable_ps_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	unsigned long flags;
	printk("[%s] val=%ld\n", __func__, val);

	dev_dbg(dev, "%s: enable ps senosr ( %ld)\n", __func__, val);

	if ((val != 0) && (val != 1)) {
		dev_dbg(dev, "%s:store unvalid value=%ld\n", __func__, val);
		return count;
	}

	if (data->ps_lock == 0) {
		dev_dbg(dev, "%s:ps lock value=%u\n", __func__, data->ps_lock);
		return count;
	}
	if (val == 1) {
		/*turn on p sensor
		first status is FAR */
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);

		/*ps calibrate*/
		loop = 10;

		if (data->enable_ps_sensor == 0) {

			data->enable_ps_sensor = 1;
			__cancel_delayed_work(&data->als_dwork);
			apds990x_set_enable(client,0); /* Power Off */
			apds990x_set_atime(client, 0xfa); /* 27.2ms */
			apds990x_set_ptime(client, 0xff); /* 2.72ms */

			apds990x_set_ppcount(client, ps_pulse_count);
			//apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			apds990x_set_pilt(client, PS_FIRST_LOW_VALUE);
			apds990x_set_piht(client, PS_FIRST_VALUE);

			apds990x_set_ailt( client, 0);
			apds990x_set_aiht( client, 0xffff);

			apds990x_set_pers(client, 0x33); /* 3 persistence */
			apds990x_set_enable(client, 0x27);	 /* only enable PS interrupt */

			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
		}
	}
	 else
	 {
		/*turn off p sensor - kk 25 Apr 2011 we can't turn off the entire sensor, the light sensor may be needed by HAL*/
		data->enable_ps_sensor = 0;
		if (data->enable_als_sensor) {
			__cancel_delayed_work(&data->als_dwork);
			// reconfigute light sensor setting
			apds990x_set_enable(client,0); /* Power Off */
			apds990x_set_atime(client, 0xdb);
			apds990x_set_ailt( client, 0);
			apds990x_set_aiht( client, 0xffff);

			/* modify FAE */
			/* apds990x_set_control(client, 0x20);*/ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_pers(client, 0x33); /* 3 persistence */

			apds990x_set_enable(client, 0x3);	 /* only enable light sensor */

			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
		}
		else
		{
			apds990x_set_enable(client, 0);


			/*
			 * If work is already scheduled then subsequent schedules will not
			 * change the scheduled time that's why we have to cancel it first.
			 */
			__cancel_delayed_work(&data->als_dwork);
		}
	}


	return count;
}

static DEVICE_ATTR(enable_ps_sensor, 0664,
				   apds990x_show_enable_ps_sensor, apds990x_store_enable_ps_sensor);

static ssize_t apds990x_show_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->enable_als_sensor);
}

static ssize_t apds990x_store_enable_als_sensor(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	unsigned long flags;

	dev_dbg(dev, "%s: enable als sensor ( %ld)\n",
		__func__, val);

	if ((val != 0) && (val != 1)) {
		dev_dbg(dev, "%s: enable als sensor=%ld\n",
			__func__, val);
		return count;
	}
	printk("[%s] val=%ld\n", __func__, val);
	if (val == 1) {
		/* turn on light sensor */
		if (data->enable_als_sensor == 0) {
			als_polling_count = 0;

			data->enable_als_sensor = 1;
			apds990x_set_enable(client, 0); /* Power Off */

			apds990x_set_ailt(client, 0);
			apds990x_set_aiht(client, 0xffff);
			/* modify 1020 */
			/* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */
			apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */
			apds990x_set_pers(client, 0x33); /* 3 persistence */

			if (data->enable_ps_sensor) {
				apds990x_set_atime(client, 0xfa);
				apds990x_set_ptime(client, 0xff); /* 2.72ms */

			/*	apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
				apds990x_set_ppcount(client, ps_pulse_count);
				/* if prox sensor was activated previously */
				apds990x_set_enable(client, 0x27);
			}
			else {
				apds990x_set_atime(client, 0xdb);

				apds990x_set_enable(client, 0x3);	 /* only enable light sensor */
			}
			if(E_APDS_TYPE_EDGE_N==apds_type)
			{
				tp_color_for_edge = read_tp_color_from_nv();
				printk("als:color=%d\n",tp_color_for_edge);
			}
			/*
			 * If work is already scheduled then subsequent schedules will not
			 * change the scheduled time that's why we have to cancel it first.
			 */
			__cancel_delayed_work(&data->als_dwork);
			schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(DELAY_FOR_DATA_RADY));
		}
	} else {
		/*turn off light sensor
		what if the p sensor is active?*/
		data->enable_als_sensor = 0;
		if (data->enable_ps_sensor) {
			apds990x_set_enable(client, 0); /* Power Off */
			apds990x_set_atime(client, 0xfa);  /* 27.2ms */
			apds990x_set_ptime(client, 0xff); /* 2.72ms */
			/*apds990x_set_ppcount(client, 8);*/ /* 8-pulse */
			apds990x_set_ppcount(client, ps_pulse_count);
			/* modify */
			/* apds990x_set_control(client, 0x20); */ /* 100mA, IR-diode, 1X PGAIN, 1X AGAIN */

			/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN */
                     apds990x_set_control(client, 0x20); /* 100mA, IR-diode, 1X PGAIN, 16X AGAIN */

			apds990x_set_pilt(client, ps_l);
			apds990x_set_piht(client, ps_h);

			apds990x_set_ailt(client, 0);
			apds990x_set_aiht(client, 0xffff);

			/* 3 persistence */
			apds990x_set_pers(client, 0x33);

			/* only enable prox sensor with interrupt */
			apds990x_set_enable(client, 0x27);
		}
		else {
			apds990x_set_enable(client, 0);
		}

		/*
		 * If work is already scheduled then subsequent schedules will not
		 * change the scheduled time that's why we have to cancel it first.
		 */
		__cancel_delayed_work(&data->als_dwork);
	}

	return count;
}

static DEVICE_ATTR(enable_als_sensor, 0664,
				   apds990x_show_enable_als_sensor, apds990x_store_enable_als_sensor);

static ssize_t apds990x_show_als_poll_delay(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	/* return in micro-second */
	return snprintf(buf, PAGE_SIZE, "%d\n", data->als_poll_delay*1000);
}

static ssize_t apds990x_store_als_poll_delay(struct device *dev,
					struct device_attribute *attr, const char *buf, size_t count)
{

	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	int poll_delay = 0;
	/*unsigned long flags;*/
	printk("[%s] val=%ld\n", __func__, val);

	if (val < 5000)
		val = 5000;	/* minimum 5ms*/

	data->als_poll_delay = val / 1000;	/* convert us => ms */

	/* the minimum is 2.72ms = 2720 us, maximum is 696.32ms */
	poll_delay = 256 - (val / 2720);
	if (poll_delay < 0)
		data->als_atime = 0;
	else
		data->als_atime = poll_delay;
	return count;

}

static DEVICE_ATTR(als_poll_delay, S_IWUSR | S_IRUGO,
				   apds990x_show_als_poll_delay, apds990x_store_als_poll_delay);

static ssize_t apds990x_show_ps_enable(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);

	return snprintf(buf, PAGE_SIZE, "%d\n", data->ps_lock);
}
static ssize_t apds990x_store_ps_enable(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);
	printk("[%s] val=%lu\n", __func__, val);

	if (val != 0) {
		if (data->enable_ps_sensor == 0) {
			data->ps_lock = 1;
		} else {/*ps opened */
			dev_dbg(dev, "%s:store ps lock value=%u\n", __func__, data->ps_lock);
		}
	} else {
		apds990x_store_enable_ps_sensor(dev,
				attr, buf, count);
		data->ps_lock = 0;

		min_proximity_value = MAX_FAR_THRESHOLD;//MAX_ADC_PROX_VALUE - apds_990x_pwindows_value;
		input_report_abs(data->input_dev_ps, ABS_DISTANCE, 1);
		input_sync(data->input_dev_ps);
	}
	return count;
}



static DEVICE_ATTR(ps_enable, 0664,
				   apds990x_show_ps_enable, apds990x_store_ps_enable);

static ssize_t apds990x_show_pdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct apds990x_data *data = i2c_get_clientdata(client);
	data->ps_data = i2c_smbus_read_word_data(client, CMD_WORD|APDS990x_PDATAL_REG);
	return snprintf(buf, PAGE_SIZE, "%d\n", data->ps_data);
}


static DEVICE_ATTR(pdata_value, 0664,
				   apds990x_show_pdata_value, NULL);

static ssize_t apds990x_show_cdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int cdata=0;
	cdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_CDATAL_REG);
	return snprintf(buf, PAGE_SIZE, "%d\n", cdata);
}

static DEVICE_ATTR(cdata_value, 0664,
				   apds990x_show_cdata_value, NULL);


static ssize_t apds990x_show_rdata_value(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	int rdata=0;
	rdata = i2c_smbus_read_word_data(client, CMD_WORD | APDS990x_IRDATAL_REG);
	return snprintf(buf, PAGE_SIZE, "%d\n", rdata);
}

static DEVICE_ATTR(rdata_value, 0664,
				   apds990x_show_rdata_value, NULL);

static struct attribute *apds990x_attributes[] = {
	&dev_attr_enable_ps_sensor.attr,
	&dev_attr_enable_als_sensor.attr,
	&dev_attr_als_poll_delay.attr,
	&dev_attr_ps_enable.attr,
	&dev_attr_pdata_value.attr,
	&dev_attr_cdata_value.attr,
	&dev_attr_rdata_value.attr,
	&dev_attr_get_reg_value.attr,
	NULL
};


static const struct attribute_group apds990x_attr_group = {
	.attrs = apds990x_attributes,
};

/*
 * Initialization function
 */
static int apds990x_init_client(struct i2c_client *client)
{
	int err;
	int id;

	err = apds990x_set_enable(client, 0);

	if (err < 0) {
		dev_err(&client->dev, "%s, apds990x_set_enable failed\n",
				__func__);
		return err;
	}

	id = i2c_smbus_read_byte_data(client, CMD_BYTE | APDS990x_ID_REG);
	if (id == 0x20) {
		dev_dbg(&client->dev, "APDS-9901, or TMD27711\n");
	} else if (id == 0x29) {
		dev_dbg(&client->dev, "APDS-9900, or TMD27713\n");
	} else if (id == 0x39) {
		dev_dbg(&client->dev, "TMD27723\n");
	} else if (id == 0x30) {
		dev_dbg(&client->dev, "TMD27721\n");
	} else {
		dev_dbg(&client->dev, "Neither APDS-9901 nor APDS-9901\n");
		return -EIO;
	}
	dev_info(&client->dev, "Read apds990x chip ok, ID is 0x%x \n", id);
	apds990x_set_atime(client, 0xDB);	/* 100.64ms ALS integration time*/
	apds990x_set_ptime(client, 0xFF);	/* 2.72ms Prox integration time*/
	apds990x_set_wtime(client, 0xFF);	/* 2.72ms Wait time*/

	apds990x_set_ppcount(client, ps_pulse_count);

	apds990x_set_config(client, 0);		/* no long wait */

	apds990x_set_control(client, 0x62);	/* 50mA, IR-diode, 1X PGAIN, 16X AGAIN*/

	ps_l = PS_FIRST_LOW_VALUE;
	ps_h = PS_FIRST_VALUE;
	apds990x_set_pilt(client, ps_l);		// init threshold for proximity
	apds990x_set_piht(client, ps_h);


	/* init threshold for als*/
	apds990x_set_ailt(client, 0);
	apds990x_set_aiht(client, 0xFFFF);

	/* 2 consecutive Interrupt persistence*/
	apds990x_set_pers(client, 0x22);

	/* sensor is in disabled mode but all the configurations are preset*/

	return 0;
}

#ifdef CONFIG_HAS_EARLYSUSPEND
static void apds990x_early_suspend(struct early_suspend *h)
{
	struct apds990x_data *data = container_of(h, struct apds990x_data, early_suspend);
	struct i2c_client *client = data->client;
	unsigned long flags;
	dev_dbg(&client->dev, "%s: apds990x try to suspend\n", __func__);

	if (!data->enable_ps_sensor && data->enable_als_sensor) {
		__cancel_delayed_work(&data->als_dwork);
		i2c_smbus_write_byte_data(client, CMD_BYTE | APDS990x_ENABLE_REG, 0);
	}

	return;
}

static void apds990x_later_resume(struct early_suspend *h)
{
	struct apds990x_data *data = container_of(h, struct apds990x_data, early_suspend);
	struct i2c_client *client = data->client;
	unsigned long flags;
	dev_dbg(&client->dev, "%s: apds990x try to resume\n", __func__);
	if (!data->enable_ps_sensor && data->enable_als_sensor) {
		i2c_smbus_write_byte_data(client, CMD_BYTE | APDS990x_ENABLE_REG, data->enable);
		__cancel_delayed_work(&data->als_dwork);
		schedule_delayed_work(&data->als_dwork, msecs_to_jiffies(data->als_poll_delay));
	}
	return;
}
#endif

/*
 * I2C init/probing/exit functions
 */

static struct i2c_driver apds990x_driver;
static int __devinit apds990x_probe(struct i2c_client *client,
				   const struct i2c_device_id *id)
{
	struct apds990x_data *data;
	struct apds990x_platform_data *pdata;
	int err = 0;
	int error = 1;
	data = kzalloc(sizeof(struct apds990x_data), GFP_KERNEL);
	if (NULL == data) {
		err = -ENOMEM;
		goto exit;
	}
	pdata = client->dev.platform_data;
		 /* set regulator*/
	error = apds990x_regulator_configure(data, client);
	if (error) {
		dev_err(&client->dev, "Failed to intialize hardware\n");
		goto exit_kfree;
	}

	apds990x_regulator_enable(data);
       msleep(10);

	apds_type = hsad_apds_get_type();
	if(E_APDS_TYPE_U9701L==apds_type)
	{
		apds_990x_pwave_value= 250;
		threshold_value = 300;
	}
	else if(E_APDS_TYPE_U9700L==apds_type)
	{
		apds_990x_pwave_value = 250;
		threshold_value = 300;
	}
	else if(E_APDS_TYPE_U9700G==apds_type)
	{
		apds_990x_pwave_value = 150;
		threshold_value = 200;
	}
	else if(E_APDS_TYPE_EDGE_N==apds_type)
	{
		apds_990x_pwave_value = 200;
		threshold_value = 250;
	}
	else
	{
		apds_990x_pwave_value = 250;
		threshold_value = 400;
	}

	ps_pulse_count=5;

	apds_990x_pwindows_value = 300;

	if(E_APDS_TYPE_OSCAR==apds_type)
	{
		apds_990x_pwave_value = 40;
		threshold_value = 50;
		apds_990x_pwindows_value = 100;
		ps_pulse_count=3;
	}

	if(E_APDS_TYPE_SOPHIA==apds_type)
	{
		apds_990x_pwave_value = 60;
		threshold_value = 70;
		apds_990x_pwindows_value = 100;
		ps_pulse_count = 5;
	}

	min_proximity_value = MAX_FAR_THRESHOLD;//MAX_ADC_PROX_VALUE - apds_990x_pwindows_value;

	if (!i2c_check_functionality(client->adapter,
		I2C_FUNC_SMBUS_BYTE)) {
		printk("-------------i2c check error!--------\n");

		err = -ENODEV;
		goto exit;
	}


	data->client = client;
	i2c_set_clientdata(client, data);

	data->enable = 0;	/* default mode is standard */
	data->ps_lock = 1; /* default ps can be opened*/
	data->ps_threshold = 0;
	data->ps_hysteresis_threshold = 0;
	data->ps_detection = 0;	/* default to no detection */
	data->enable_als_sensor = 0;	/* default to 0 */
	data->enable_ps_sensor = 0;	/* default to 0 */
	/*data->als_poll_delay = 100;*/	/* default to 100ms*/
	data->als_poll_delay = 500;	/* default to 500ms*/
	data->als_atime	= 0xdb;			/* work in conjuction with als_poll_delay*/
	data->irq = gpio_to_irq(pdata->apds990x_gpio);
	data->apds_gpio = pdata->apds990x_gpio;

	dev_dbg(&client->dev, "enable = %x\n", data->enable);

	mutex_init(&data->update_lock);
	data->ps_wq = create_singlethread_workqueue("ps_wq");
	if (!data->ps_wq) {
		dev_err(&client->dev, "failed to create ps workqueue!\n");
		goto exit_kfree;
	}
	INIT_DELAYED_WORK(&data->dwork, apds990x_work_handler);
	INIT_DELAYED_WORK(&data->als_dwork, apds990x_als_polling_work_handler);
	/* Initialize the APDS990x chip */
	err = apds990x_init_client(client);
	if (err)
		goto exit_kfree;

	err = gpio_request(pdata->apds990x_gpio, "gpio_3_5");
	if (err) {
		dev_err(&client->dev, "%s: failed to request gpio int1 for irq\n",
			__func__);
		goto exit_kfree;
	}

	err = gpio_direction_input(pdata->apds990x_gpio);
	if (err) {
		dev_err(&client->dev, "%s: failed to config gpio direction\n",
			__func__);
		goto exit_gpio_request;
	}

	/* Initialize wakelock*/
	wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "apds990x");

	err = request_irq(data->irq, apds990x_interrupt,
			IRQF_DISABLED | IRQ_TYPE_LEVEL_LOW | IRQF_NO_SUSPEND,
						APDS990x_DRV_NAME, (void *)client);
	if (err) {
		dev_err(&client->dev, "%s  allocate APDS990x_IRQ failed.\n",
			__func__);
		goto exit_gpio_request;
	}


	dev_dbg(&client->dev, "%s interrupt is hooked\n", __func__);



	/* Register to Input Device */
	data->input_dev_als = input_allocate_device();
	if (!data->input_dev_als) {
		err = -ENOMEM;
		dev_err(&client->dev, "%s, Failed to allocate input device als\n",
			__func__);
		goto exit_free_irq;
	}

	data->input_dev_ps = input_allocate_device();
	if (!data->input_dev_ps) {
		err = -ENOMEM;
		dev_err(&client->dev, "%s, Failed to allocate input device ps\n",
			__func__);
		goto exit_free_dev_als;
	}

	data->input_dev_als->name = ALS_INPUT_DEV_NAME;
	data->input_dev_als->id.bustype = BUS_I2C;
	data->input_dev_als->dev.parent = &data->client->dev;
	data->input_dev_ps->name = PS_INPUT_DEV_NAME;
	data->input_dev_ps->id.bustype = BUS_I2C;
	data->input_dev_ps->dev.parent = &data->client->dev;

	set_bit(EV_ABS, data->input_dev_als->evbit);
	set_bit(EV_ABS, data->input_dev_ps->evbit);

	input_set_abs_params(data->input_dev_als, ABS_MISC, 0, 10000, 0, 0);
	input_set_abs_params(data->input_dev_ps, ABS_DISTANCE, 0, 1, 0, 0);

	err = input_register_device(data->input_dev_als);
	if (err) {
		dev_err(&client->dev, "%s, Unable to register input device als: %s\n",
		       __func__, data->input_dev_als->name);
		goto exit_free_dev_ps;
	}

	err = input_register_device(data->input_dev_ps);
	if (err) {
		dev_err(&client->dev, "%s,Unable to register input device ps: %s\n",
		       __func__, data->input_dev_ps->name);
		goto exit_unregister_dev_als;
	}

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &apds990x_attr_group);
	if (err) {
		dev_err(&client->dev, "%s, sysfs_create_group failed\n", __func__);
		goto exit_unregister_dev_ps;
	}

#ifdef CONFIG_HUAWEI_SENSORS_INPUT_INFO
	if(false == get_rgb_sensor_type()) {
		if(E_APDS_TYPE_EDGE_N == apds_type) {
			err = set_sensor_chip_info(ALS, "AVAGO APDS9900 or TAOS TMD27713");
			}
		else {
			err = set_sensor_chip_info(ALS, "AVAGO APDS9930 or TAOS TMD27723");
			}

	    if (err) {
		    dev_err(&client->dev, "set_ALS_sensor_chip_info error\n");
	    }
    }

	if(E_APDS_TYPE_EDGE_N == apds_type) {
		err = set_sensor_chip_info(PS, "AVAGO APDS9900 or TAOS TMD27713");
		}
	else {
		err = set_sensor_chip_info(PS, "AVAGO APDS9930 or TAOS TMD27723");
		}

	if (err) {
		dev_err(&client->dev, "set_PS_sensor_chip_info error\n");
	    }
#endif
#ifdef CONFIG_HAS_EARLYSUSPEND
	data->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 1;
	data->early_suspend.suspend = apds990x_early_suspend;
	data->early_suspend.resume = apds990x_later_resume;
	register_early_suspend(&data->early_suspend);
#endif
	dev_dbg(&client->dev, "%s support ver. %s enabled\n",
		__func__, DRIVER_VERSION);

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
        set_hw_dev_flag(DEV_I2C_L_SENSOR);
#endif
 //     apds990x_regulator_disable(data);
	return 0;

exit_unregister_dev_ps:
	input_unregister_device(data->input_dev_ps);
exit_unregister_dev_als:
	input_unregister_device(data->input_dev_als);
exit_free_dev_ps:
	input_free_device(data->input_dev_ps);
exit_free_dev_als:
	input_free_device(data->input_dev_als);
exit_free_irq:
	if (data->irq >= 0)
	free_irq(data->irq, client);
exit_gpio_request:
	if (data->irq >= 0)
	gpio_free(pdata->apds990x_gpio);
exit_kfree:
        if (data->ps_wq)
		destroy_workqueue(data->ps_wq);
	i2c_set_clientdata(client, NULL);
	kfree(data);
	data = NULL;


exit:
	return err;
}

static int __devexit apds990x_remove(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

	input_unregister_device(data->input_dev_als);
	input_unregister_device(data->input_dev_ps);

	input_free_device(data->input_dev_als);
	input_free_device(data->input_dev_ps);

	if (data->irq >= 0) {
		free_irq(data->irq, client);
		gpio_free(data->apds_gpio );
	}

        if (data->ps_wq)
		destroy_workqueue(data->ps_wq);

	sysfs_remove_group(&client->dev.kobj, &apds990x_attr_group);
	/* Power down the device */
	apds990x_set_enable(client, 0);
	i2c_set_clientdata(client, NULL);
	kfree(data);
	data = NULL;

	return 0;
}

static void apds990x_shutdown(struct i2c_client *client)
{
	struct apds990x_data *data = i2c_get_clientdata(client);

	printk("[%s] +\n", __func__);

	if (data->irq >= 0) {
		free_irq(data->irq, client);
	}

	__cancel_delayed_work(&data->dwork);
	__cancel_delayed_work(&data->als_dwork);

	/* Power down the device */
	apds990x_set_enable(client, 0);

	wake_lock_destroy(&wlock);

	printk("[%s] -\n", __func__);
}


static const struct i2c_device_id apds990x_id[] = {
	{ "apds990x", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, apds990x_id);

static struct i2c_driver apds990x_driver = {
	.driver = {
		.name	= APDS990x_DRV_NAME,
		.owner	= THIS_MODULE,
	},
	.probe	= apds990x_probe,
	//.probe	= NULL,
	.remove	= __devexit_p(apds990x_remove),
	.shutdown = apds990x_shutdown,
	.id_table = apds990x_id,
};

static int __init apds990x_init(void)
{
	return i2c_add_driver(&apds990x_driver);
}

static void __exit apds990x_exit(void)
{
	i2c_del_driver(&apds990x_driver);
}

MODULE_AUTHOR("Lee Kai Koon <kai-koon.lee@avagotech.com>");
MODULE_DESCRIPTION("APDS990x ambient light + proximity sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);

module_init(apds990x_init);
module_exit(apds990x_exit);


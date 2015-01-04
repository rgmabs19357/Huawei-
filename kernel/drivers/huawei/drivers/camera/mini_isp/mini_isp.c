/*
 * A driver for the mini isp.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/spi/spi.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <mach/gpio.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/ctype.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <hsad/config_interface.h>
#include <hsad/config_mgr.h>
#include <linux/vmalloc.h>
#include <linux/random.h>
#include "drv_regulator_user.h"
#include "mini_isp.h"
#include "mini_cam_log.h"
#include "mini_k3_isp.h"

#ifdef LOG_TAG
#undef LOG_TAG
#define LOG_TAG "mini_isp"
#endif

#define MINI_ISP_SPI_SPEED_BOOT		(12000000)
#define MINI_ISP_SPI_SPEED_NORMAL	(25000000)
#define MINI_ISP_BOOT_CODE		("/system/miniBoot.bin")
#define MINI_ISP_BASIC_CODE		("/system/TBM_Latour.bin")
#define MINI_ISP_WAIT_TIMEOUT	(HZ*2)
#define MINI_ISP_POLL_TIMES		(20)
#define MINI_ISP_MAX_ERR_CODE	(10)

#define MINI_ISP_CMD_DELAY_US	(1000)

#define MINI_ISP_FW_LOG_BUF		(4096)

#define SPI_TX_BUF_SIZE			(64)
#define SPI_RX_BUF_SIZE			(64)
#define SPI_BLOCK_BUF_SIZE		(8192)

#define ISPCMD_DUMMYBYTES		(4)
#define ISPCMD_LENFLDBYTES		(2)
#define ISPCMD_OPCODEBYTES		(2)
#define ISPCMD_CKSUMBYTES		(2) 
#define ISPCMD_HDRSIZE			(ISPCMD_LENFLDBYTES+ISPCMD_OPCODEBYTES)
#define ISPCMD_HDRSIZEWDUMMY	(ISPCMD_LENFLDBYTES+ISPCMD_OPCODEBYTES+ISPCMD_DUMMYBYTES)

struct misp_plat_data {
	int spi_cs_gpio;
	int irq_gpio;
	int reset_gpio;
	int power_gpio;
};

struct misp_fw_ver_info {
	char	info[16];
	u32		product;
	u16		major;
	u16		minor;
	char	user[9];
};

struct misp_data {
	struct spi_device	*spi;
	struct mutex		busy_lock;
	struct misp_plat_data	*plat_data;
	struct regulator	*ldo_core;
	struct regulator	*ldo_io;
	struct workqueue_struct	*work_queue;
	wait_queue_head_t	wait_queue;
	wait_queue_head_t	sync_queue;
	wait_queue_head_t	pwdn_queue;
	int		state;
	u32		last_error_code[MINI_ISP_MAX_ERR_CODE];
	/*
	 * NOTE: All buffers should be dma-safe buffers
	 * ext_buf:used only for 1-byte ctrl_byte in font of tx or rx
	 * tx_buf :used for 64-Bytes CMD-send or 8K-Bytes Block-send
	 * rx_buf :used for 64-Bytes CMD-recv or 4K-Bytes Block-recv
	 */
	u8		*tx_buf;
	u8		*rx_buf;
	u8		*ext_buf;
	/*
	 * NOTE:
	 * all these tx/rx/ext buffers above used with mutex lock, but
	 * irq cannot use mutex lock, so a special buffer is supplied
	 */
	u8		*irq_buf;
	/* debug config & debug info */
	u32		debug_config;
	u32		debug_log_level;
	struct work_struct	dump_err_work;
	struct work_struct	dump_log_work;
	struct misp_fw_ver_info fw_info;
	struct misp_fw_ver_info boot_info;
	u32 	flush_reg_flag;
};

typedef enum {
    USPICTRL_MS_CB_ORG                  = (0x00<<6),    /*!< Ctrl-Byte, original command */
    USPICTRL_MS_CB_STS                  = (0x01<<6),    /*!< Ctrl-Byte, polling status */
    USPICTRL_MS_CB_RSP                  = (0x02<<6),    /*!< Ctrl-Byte, get response */
    USPICTRL_MS_CB_DIS                  = (0x03<<6),    /*!< Ctrl-Byte, disable Ctrl-Byte mode */

    USPICTRL_MS_ORG                     = 0x5A,     /*!< Ctrl-Byte, original command */
    USPICTRL_MS_RSP                     = 0xA5,     /*!< Ctrl-Byte, get response */
    USPICTRL_MS_BK0                     = 0xB5,     /*!< Ctrl-Byte, send bulk for 1~(N-1) one */
    USPICTRL_MS_BKN                     = 0xBB,     /*!< Ctrl-Byte, senc bulk for last one */
    USPICTRL_MS_DIS                     = 0x05,     /*!< Ctrl-Byte, disable get response */
} USPICTRL_MS_CB_ID;

enum {
	MINI_ISP_STATE_IDLE				= (0U),
	MINI_ISP_STATE_READY			= (1U<<0),
	MINI_ISP_STATE_SYNC				= (1U<<1),
	MINI_ISP_STATE_PWDN				= (1U<<2),
};

enum {
	MINI_ISP_IRQ_READY_DONE			= (1U<<0),
	MINI_ISP_IRQ_CMD_ERR			= (1U<<1),
	MINI_ISP_IRQ_OTHRE_ERR			= (1U<<2),
	MINI_ISP_IRQ_LOG_FULL			= (1U<<3),
	MINI_ISP_IRQ_SYNC				= (1U<<4),
	MINI_ISP_IRQ_PWDN				= (1U<<5),
};

enum {
	MINI_ISP_DEBUG_SPI_DATA			= (1U<<0),
	MINI_ISP_DEBUG_LOG_FILE			= (1U<<1),
};

enum {
	MINI_ISP_LOG_LEVEL_NONE			= (0x0),
	MINI_ISP_LOG_LEVEL_SW1			= (0x00000001),
	MINI_ISP_LOG_LEVEL_SW2			= (0x00000002),
	MINI_ISP_LOG_LEVEL_SW3			= (0x00000004),
	MINI_ISP_LOG_LEVEL_IQ1			= (0x00000010),
	MINI_ISP_LOG_LEVEL_IQ2			= (0x00000020),
	MINI_ISP_LOG_LEVEL_IQ3			= (0x00000040),
	MINI_ISP_LOG_LEVEL_ISR			= (0x00000100),
};

enum {
	MINI_ISP_FLUSH_REG_NONE			= (0U),
	MINI_ISP_FLUSH_REG_ALREADY		= (1U),
};

static struct misp_data *misp_drv_data;
static u32 misp_default_reg_table [] ={
	0xffe80200,
	0xffe80228,
	0xffe80250,
	0xffe80278,
	0xffe802a0,
	0xffe802c8,
	0xffe802f0,
	0xffe80318,
	0xffe80340,
	0xffe80368,
	0xffe80390,
	0xffe803b8,
	0xffe803e0,
	0xffe80408,
	0xffe80430,
	0xffe80458,
	0xffe80480,
	0xffe804a8,
	0xffe804d0,
	0xffe804f8,
	0xffe80520,
	0xffe80548,
	0xffe80570,
	0xffe80598,
	0xffe805c0,
	0xffe805e8,
	0xffe80610,
	0xffe80638,
	0xffe80660,
	0xffe80688,
	0xffe806b0,
	0xffe806b0,
	0xffe80700,
	0xffe80728,
	0xffe80750,
	0xffe80778,
	0xffe807a0,
	0xffe807c8,
	0xffe807f0,
	0xffe80818,
	0xffe80840,
	0xffe80868,

	0xffeb0000,
	0xffeb0028,
	0xffeb0050,
	0xffeb0078,
	0xffeb00a0,
	0xffeb00c8,
	0xffeb00f0,
	0xffeb0118,
	0xffeb0140,
	0xffeb0168,

	0xffeb1000,
	0xffeb1028,
	0xffeb1050,
	0xffeb1078,
	0xffeb10a0,
	0xffeb10c8,
	0xffeb10f0,
	0xffeb1118,
	0xffeb1140,
	0xffeb1168,

	0xffeba000,
	0xffeba028,

	0xffebb000,
	0xffebb028,

	0xffedc000,
	0xffedc028,
	0xffedc050,
	0xffedc078,
	0xffedc0a0,
	0xffedc0c8,
	0xffedc0f0,

	0xffedd000,
	0xffedd028,
	0xffedd050,
	0xffedd078,
	0xffedd0a0,
	0xffedd0c8,
	0xffedd0f0,

	0xffede000,
	0xffede028,
	0xffede050,
	0xffede078,
	0xffede0a0,
	0xffede0c8,
	0xffede0f0,

	0xffedf000,
	0xffedf028,
	0xffedf050,
	0xffedf078,
	0xffedf0a0,
	0xffedf0c8,
	0xffedf0f0,
	0xffe30000,

	0xfff10900,
	0xfff10928,

	0xfff18900,
	0xfff18928,

	0xfffa1000,
	0xfffa1028,
	0xfffa1050,
	0xfffa1078,
	0xfffa10a0,
	0xfffa10c8,
	0xfffa10f0,
	0xfffa1118,
	0xfffa1140,
	0xfffa1168,
	0xfffa1190,

	0xfffa2000,
	0xfffa2028,
	0xfffa2050,
	0xfffa2078,
	0xfffa20a0,
	0xfffa20c8,
	0xfffa20f0,
	0xfffa2118,
	0xfffa2140,
	0xfffa2168,
	0xfffa2190,

	0xfffa3000,
	0xfffa3028,

	0xfffa4000,
	0xfffa4028,

	0xfffa9000,
	0xfffa9028,
	0xfffa9050,
	0xfffa9078,
	0xfffa90a0,
	0xfffa90c8,

	0xfffaa000,
	0xfffaa028,
	0xfffaa050,
	0xfffaa078,
	0xfffaa0a0,
	0xfffaa0c8,
};


static struct misp_data* get_misp_data(void);
static int misp_send_cmd(struct misp_data *devdata, u16 opcode, u8 *param, u32 len);
static int misp_recv_data(struct misp_data *devdata, u8 *param, u32 len);
static u16 calculate_checksum(u8 *buf, u16 size);
static void spi_data_debug(const void *buf, int data_len, int dbg_len);
static void misp_dump_err(struct work_struct *work);
static void misp_dump_log(struct work_struct *work);
static int misp_spi_send(struct misp_data *devdata, u32 len);
static int misp_spi_recv(struct misp_data *devdata, u32 len);
static int misp_poll_status(struct misp_data *devdata);
static int misp_load_boot_code(struct misp_data *devdata, char *name);
static int misp_load_basic_code(struct misp_data *devdata, char *name);

static void misp_config_spi(struct misp_data *pdata, u32 mode, u32 bits, u32 speed);
static void misp_config_log(struct misp_data *pdata, u32 new_config, u32 new_log_level);
static void misp_dump_reg(struct misp_data *pdata, u32* reg_table, u32 reg_table_size);
static void misp_dump_ram(struct misp_data *pdata, u32 start, u32 total, u32 mode);
static void misp_write_reg(struct misp_data *pdata, u32 addr, u32 val);
static void misp_test_spi(struct misp_data *pdata);

/* 
 * mini isp export functions, export to other driver modules to use.
 * include :
 * @applicaton-layer spi cmd
 * @init and exit function
 * @power control funciont
 */

u32 misp_construct_opcode(u32 opcode, u32 set_flag, u32 len)
{
	u32 cmd;
	cmd = (set_flag<<31)+ (len<<16) + opcode;
	print_debug("cmd=0x%08x", cmd);
	return cmd;	
}
EXPORT_SYMBOL(misp_construct_opcode);

int misp_exec_cmd(u32 opcode, u8 *param)
{
	struct misp_data *devdata = get_misp_data();
	int err = 0;
	u8 set_flag = 0;
	u8 len = 0;
	u16 cmd;
	   
	set_flag = opcode>>31;
	len = (opcode>>16)&0x7fff;
	cmd = opcode&0x0000ffff;

	if (!devdata) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	mutex_lock_interruptible(&devdata->busy_lock);
	if (set_flag == 1) {
		devdata->state = MINI_ISP_STATE_IDLE;
		err = misp_send_cmd(devdata, cmd, param, len);
		if (err)
			goto out;

		/* special cmd <stream off> need to wait until done*/
		if ((cmd == ISPCMD_CAMERA_PREVIEWSTREAMONOFF) &&
			(param[0]==0 && param[1]==0 && param[2]==0)) {

			wait_event_interruptible_timeout(devdata->sync_queue,\
						(devdata->state == MINI_ISP_STATE_SYNC),\
						MINI_ISP_WAIT_TIMEOUT);

			if (devdata->state != MINI_ISP_STATE_SYNC) {
				print_warn("%s wait sync signal timeout", __func__);
				err = -EAGAIN;
				goto out;
			}
		}
	} else {
		devdata->state = MINI_ISP_STATE_IDLE;
		err = misp_send_cmd(devdata, opcode, NULL, 0);
		if (err)
			goto out;

		wait_event_interruptible_timeout(devdata->wait_queue,\
					(devdata->state == MINI_ISP_STATE_READY),\
					MINI_ISP_WAIT_TIMEOUT);

		if (devdata->state != MINI_ISP_STATE_READY) {
			print_warn("%s wait ready signal timeout", __func__);
			err = -EAGAIN;
			goto out;
		}

		err = misp_recv_data(devdata, param, len);
	}
out:
	udelay(MINI_ISP_CMD_DELAY_US);
	mutex_unlock(&devdata->busy_lock);
	return err;
}
EXPORT_SYMBOL(misp_exec_cmd);

int misp_exec_inout_cmd(u16 cmd, u8 *in, u32 in_len,
										u8 *out, u32 out_len)
{
	struct misp_data *devdata = get_misp_data();
	int err = 0, ret = 0;

	if (!devdata) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	if ((in == NULL) || (out == NULL)) {
		print_error("%s in out buf invalid", __func__);
		return -EINVAL;
	}

	mutex_lock_interruptible(&devdata->busy_lock);

	devdata->state = MINI_ISP_STATE_IDLE;
	err = misp_send_cmd(devdata, cmd, in, in_len);
	if (err)
		goto out;

	ret = wait_event_interruptible_timeout(devdata->wait_queue,\
						(devdata->state == MINI_ISP_STATE_READY),\
						MINI_ISP_WAIT_TIMEOUT);
	if (ret <= 0) {
		print_warn("%s wait ready signal timeout", __func__);
		err = -EAGAIN;
		goto out;
	}

	err = misp_recv_data(devdata, out, out_len);
out:
	udelay(MINI_ISP_CMD_DELAY_US);
	mutex_unlock(&devdata->busy_lock);
	return err;
}
EXPORT_SYMBOL(misp_exec_inout_cmd);

int misp_init(void)
{
	struct misp_data *drv_data = get_misp_data();
	struct misp_plat_data *plat_data = NULL;
	struct regulator *ldo_core = NULL, *ldo_io = NULL;
	int ret = 0;

	print_info("%s enter", __func__);

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = drv_data->plat_data;

	/* restore gpio to output mode when init */
	gpio_direction_output(plat_data->spi_cs_gpio, 1);
	gpio_direction_output(plat_data->reset_gpio,  0);

	/* init power ldo */
	ldo_core = regulator_get(&drv_data->spi->dev, MINI_ISP_ANALOG_VDD);
	if (IS_ERR_OR_NULL(ldo_core)) {
		print_error("%s failed to get misp core(1.1v) ldo", __func__);
		ret = -ENODEV;
		goto err_core_ldo_get;
	}

	ldo_io = regulator_get(&drv_data->spi->dev, M_CAMERA_IO_VDD);
	if (IS_ERR_OR_NULL(ldo_io)) {
		print_error("%s failed to get misp IO(1.8) ldo", __func__);
		ret = -ENODEV;
		goto err_io_ldo_get;
	}

	ret |= regulator_set_mode(ldo_core, REGULATOR_MODE_NORMAL);
	ret |= regulator_set_voltage(ldo_core, LDO_VOLTAGE_11V, LDO_VOLTAGE_11V);

	ret |= regulator_set_mode(ldo_io, REGULATOR_MODE_NORMAL);
	ret |= regulator_set_voltage(ldo_io, LDO_VOLTAGE_18V, LDO_VOLTAGE_18V);

	if (ret) {
		print_error("%s failed to config misp ldo voltage", __func__);
		goto err_config_ldo;
	}

	drv_data->ldo_core = ldo_core;
	drv_data->ldo_io = ldo_io;

	/* debug level reset */
	drv_data->debug_log_level = MINI_ISP_LOG_LEVEL_NONE;
	drv_data->flush_reg_flag = MINI_ISP_FLUSH_REG_NONE;

	return 0;

err_config_ldo:
	regulator_put(ldo_io);
err_io_ldo_get:
	regulator_put(ldo_core);
err_core_ldo_get:
	drv_data->ldo_core = NULL;
	drv_data->ldo_io = NULL;
	return ret;
}
EXPORT_SYMBOL(misp_init);

int misp_exit(void)
{
	struct misp_data *drv_data = get_misp_data();
	struct misp_plat_data *plat_data = NULL;

	print_info("%s enter", __func__);

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = drv_data->plat_data;

	/* set gpio to low power when exit */
	gpio_direction_input(plat_data->spi_cs_gpio);
	gpio_direction_input(plat_data->reset_gpio);

	/* deinit power ldo */
	if (drv_data->ldo_core)
		regulator_put(drv_data->ldo_core);

	if (drv_data->ldo_io)
		regulator_put(drv_data->ldo_io);

	drv_data->ldo_core = NULL;
	drv_data->ldo_io = NULL;

	/* debug level reset */
	drv_data->debug_log_level = 0;

	return 0;
}
EXPORT_SYMBOL(misp_exit);

int misp_set_power(camera_power_state power)
{
	struct misp_data *drv_data = get_misp_data();
	struct misp_plat_data *plat_data = NULL;
	int ret = 0;

	print_info("%s power=%s", __func__, (power==POWER_ON)?"on":"off");

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	if (!drv_data->ldo_core || !drv_data->ldo_io) {
		print_error("%s no ldo", __func__);
		return -EINVAL;
	}

	plat_data = drv_data->plat_data;

	if (power == POWER_ON) {
		/* (1)dc/dc 1.1v power up 1:enable 0:disable */
		gpio_direction_output(plat_data->power_gpio,  1);
		udelay(5);
		/* (2)core 1.1v ldo power up */
		ret |= regulator_enable(drv_data->ldo_core);
		udelay(5);
		/* (3)io 1.8v ldo power up */
		ret |= regulator_enable(drv_data->ldo_io);
		msleep(2);
	} else {
		/* (1)io 1.8v ldo power down */
    	ret |= regulator_disable(drv_data->ldo_io);
		udelay(5);
		/* (2)analog 1.1v ldo power down */
    	ret |= regulator_disable(drv_data->ldo_core);
    	udelay(5);
		/* (3)dc/dc 1.1v power down 1:enable 0:disable */
    	gpio_direction_output(plat_data->power_gpio, 0);
		msleep(2);
	}

	return ret;
}
EXPORT_SYMBOL(misp_set_power);

int misp_flush_log(void)
{
	struct misp_data *drv_data = get_misp_data();

	print_info("%s enter", __func__);

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	/* force to record last log when exit */
	if (drv_data->debug_config & MINI_ISP_DEBUG_LOG_FILE) {
		queue_work(drv_data->work_queue, &drv_data->dump_log_work);
		flush_work(&drv_data->dump_log_work);
	}

	return 0;
}
EXPORT_SYMBOL(misp_flush_log);


int misp_reset_vcm(void)
{
	struct misp_data *drv_data = get_misp_data();
	u8 mode = 5;
	int ret = 0, err= 0;

	print_info("%s enter", __func__);

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	mutex_lock_interruptible(&drv_data->busy_lock);

	drv_data->state = MINI_ISP_STATE_IDLE;
	err = misp_send_cmd(drv_data, ISPCMD_SYSTEM_CHANGEMODE, &mode, sizeof(mode));

	ret = wait_event_interruptible_timeout(drv_data->pwdn_queue,\
						(drv_data->state == MINI_ISP_STATE_PWDN),\
						msecs_to_jiffies(500));
	if (ret <= 0) {
		print_warn("%s wait vcm pwdn signal timeout", __func__);
		err = -EAGAIN;
	}
	udelay(MINI_ISP_CMD_DELAY_US);
	mutex_unlock(&drv_data->busy_lock);

	return err;
}
EXPORT_SYMBOL(misp_reset_vcm);

int misp_flush_reg(void)
{
	struct misp_data *drv_data = get_misp_data();
	u32 *addr_table = misp_default_reg_table;
	u32 size = ARRAY_SIZE(misp_default_reg_table);

	print_info("%s enter", __func__);

	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	/* don't dump twice */
	if (drv_data->flush_reg_flag == MINI_ISP_FLUSH_REG_ALREADY)
		return 0;

	/* mark register already dumped */
	drv_data->flush_reg_flag = MINI_ISP_FLUSH_REG_ALREADY;

	misp_dump_reg(drv_data, addr_table, size);

	return 0;
}
EXPORT_SYMBOL(misp_flush_reg);

int misp_load_fw(void)
{
	struct misp_data *drv_data = get_misp_data();
	struct misp_plat_data *plat_data = NULL;
	int ret = 0;

	print_info("%s enter", __func__);
	if (!drv_data) {
		print_error("%s no driver data", __func__);
		return -ENODEV;
	}

	plat_data = drv_data->plat_data;

	/* reset mini-isp keep low for at least 200us, release to high for 20ms */
	gpio_direction_output(plat_data->reset_gpio,  0);
	msleep(1);
	gpio_direction_output(plat_data->reset_gpio,  1);
	msleep(25);

	/* load boot code firmware */
	drv_data->spi->max_speed_hz = MINI_ISP_SPI_SPEED_BOOT;
	ret = spi_setup(drv_data->spi);
	if (ret < 0) {
		print_error("%s - failed to setup spi speed:%u", __func__,
										drv_data->spi->max_speed_hz);
		goto out;
	}
	ret = misp_load_boot_code(drv_data, MINI_ISP_BOOT_CODE);
	if (ret)
		goto out;
	msleep(1);

	/* load main code firmware */
	drv_data->spi->max_speed_hz = MINI_ISP_SPI_SPEED_NORMAL;
	ret = spi_setup(drv_data->spi);
	if (ret < 0) {
		print_error("%s - failed to setup spi speed:%u", __func__,
										drv_data->spi->max_speed_hz);
		goto out;
	}
	drv_data->state = MINI_ISP_STATE_IDLE;
	ret |= misp_load_basic_code(drv_data, MINI_ISP_BASIC_CODE);
	if (ret)
		goto out;

	wait_event_interruptible_timeout(drv_data->wait_queue,\
					(drv_data->state == MINI_ISP_STATE_READY),\
					MINI_ISP_WAIT_TIMEOUT);
	if (drv_data->state != MINI_ISP_STATE_READY)
		print_warn("%s wait ready signal timeout", __func__);

out:
	return ret;
}
EXPORT_SYMBOL(misp_load_fw);


/*
 * mini isp local functions, no need to export to other driver modules.
 * include :
 * @lowlevel spi transfer
 * @firmware load
 * @interrupte handle...
 */
static struct misp_data* get_misp_data(void)
{
	if (likely(misp_drv_data))
		return misp_drv_data;
	else
		return NULL;
}

static int misp_send_cmd(struct misp_data *devdata, u16 opcode, u8 *param, u32 len)
{
    u16 *p_len, *p_opcode, total_len;
    int err = 0;
	u16 calc_chk_sum;

	memset(devdata->tx_buf, 0, SPI_TX_BUF_SIZE);

	p_len = (u16 *)&devdata->tx_buf[0];
	p_opcode = (u16 *)&devdata->tx_buf[ISPCMD_OPCODEBYTES];

	total_len = ISPCMD_HDRSIZE + len;
	*p_len      = total_len - ISPCMD_LENFLDBYTES;

	*p_opcode	= opcode;
	memcpy(&devdata->tx_buf[ISPCMD_HDRSIZE], param, len);

   /* calculate checksum */
   calc_chk_sum = calculate_checksum(devdata->tx_buf, total_len);
   memcpy(&devdata->tx_buf[total_len], &calc_chk_sum, ISPCMD_CKSUMBYTES);

   /* add bytes for checksum */
   total_len += ISPCMD_CKSUMBYTES;

   /* send command to slave */
   err = misp_spi_send(devdata,  total_len);

   return err;
}


static int misp_recv_data(struct misp_data *devdata, u8 *param, u32 len)
{
    int err = 0;
	u32 total_len;
	u16  calc_chk_sum, recv_chk_sum;

	memset(devdata->rx_buf, 0, SPI_RX_BUF_SIZE);
    total_len = len + ISPCMD_HDRSIZEWDUMMY + ISPCMD_CKSUMBYTES;

    /* get data via spi bus */
    err = misp_spi_recv(devdata, total_len);
	if (err)
		return err;

    /* calculate checksum */
    memcpy(&recv_chk_sum, &devdata->rx_buf[(total_len - ISPCMD_CKSUMBYTES)], ISPCMD_CKSUMBYTES);
	calc_chk_sum = calculate_checksum(devdata->rx_buf, (total_len - ISPCMD_CKSUMBYTES));
	if(calc_chk_sum != recv_chk_sum) {
		print_error("%s recicev data check sum not match", __func__);
		return -1;
	}

    /* copy param data to caller */
    memcpy(param, &devdata->rx_buf[ISPCMD_HDRSIZEWDUMMY], len);

    return 0;

}

static u16 calculate_checksum(u8 *buf, u16 size)
{
    u16 index;
	u32 sum = 0;
	u16 sumvalue;

	for (index=0 ; index < size ; index++) {
	  	if( 0 == (index%2))
			sum += buf[index];
		else
			sum += (buf[index] << 8);
	}
	sumvalue = (u16) ( 65536 - (sum & 0x0000FFFF));
	return sumvalue;
}

static void spi_data_debug(const void *buf, int data_len, int dbg_len)
{
	int len=0, pos=0;
	unsigned char *cbuf = (unsigned char *)buf;

	len = (dbg_len>data_len)?data_len:dbg_len;
	len =  roundup(len, 16);
	len = (len<16)?16:len;

	pos = 0;
	while (len > 0) {
		print_info("buf[%04d]:%02x %02x %02x %02x %02x %02x %02x %02x "
							 "%02x %02x %02x %02x %02x %02x %02x %02x",
					pos,
					cbuf[pos],   cbuf[pos+1], cbuf[pos+2], cbuf[pos+3],
					cbuf[pos+4], cbuf[pos+5], cbuf[pos+6], cbuf[pos+7],
					cbuf[pos+8], cbuf[pos+9], cbuf[pos+10],cbuf[pos+11],
					cbuf[pos+12],cbuf[pos+13],cbuf[pos+14],cbuf[pos+15]);
		len -= 16;
		pos += 16;
	}
}

static irqreturn_t misp_irq_thread(int irq, void *handle)
{
	struct misp_data *drv_data = (struct misp_data *)handle;
	u16	irq_code = 0, cmd, err_code;
	u8	ctrl_byte = USPICTRL_MS_CB_STS;
	struct spi_message	m;
	struct spi_transfer	xfer[2] = {
		[0] = {
			.tx_buf = drv_data->irq_buf,
			.rx_buf = NULL,
			.len = sizeof(ctrl_byte),
		},
		[1] = {
			.tx_buf = NULL,
			.rx_buf = drv_data->irq_buf,
			.len = sizeof(irq_code),
		},
	};

	drv_data->irq_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	spi_sync(drv_data->spi, &m);
	memcpy(&irq_code, drv_data->irq_buf, sizeof(irq_code));
	print_info("misp irq state=0x%04x", irq_code);

	/* handle ready done */
	if (irq_code & MINI_ISP_IRQ_READY_DONE) {
		drv_data->state = MINI_ISP_STATE_READY;
		wake_up_interruptible(&drv_data->wait_queue);
	}

	/* handle sync signal */
	if (irq_code & MINI_ISP_IRQ_SYNC) {
		drv_data->state = MINI_ISP_STATE_SYNC;
		wake_up_interruptible(&drv_data->sync_queue);
	}

	/* handle pwdn signal */
	if (irq_code & MINI_ISP_IRQ_PWDN) {
		drv_data->state = MINI_ISP_STATE_PWDN;
		wake_up_interruptible(&drv_data->pwdn_queue);
	}

	/* handle cmd error */
	if (irq_code & MINI_ISP_IRQ_CMD_ERR)
		print_error("mini isp critical error, cmd not respond");

	/* handle other error */
	if (irq_code & MINI_ISP_IRQ_OTHRE_ERR)
		queue_work(drv_data->work_queue, &drv_data->dump_err_work);

	/* handle dump log */
	if (irq_code & MINI_ISP_IRQ_LOG_FULL) {
		if (drv_data->debug_config & MINI_ISP_DEBUG_LOG_FILE)
			queue_work(drv_data->work_queue, &drv_data->dump_log_work);
	}

	return IRQ_HANDLED;
}

static void misp_dump_err(struct work_struct *work)
{
	struct misp_data *drv_data =
		container_of(work, struct misp_data, dump_err_work);
	int err = 0, index = 0;

	print_info("%s enter", __func__);

	/* send get error cmd*/
	mutex_lock_interruptible(&drv_data->busy_lock);
	err = misp_send_cmd(drv_data, ISPCMD_SYSTEM_GET_ERRORCODE, NULL, 0);
	if (err)
		goto out;
	err = misp_poll_status(drv_data);
	if (err)
		goto out;
	err = misp_recv_data(drv_data, drv_data->last_error_code,
						sizeof(u32)*MINI_ISP_MAX_ERR_CODE);
out:
	udelay(MINI_ISP_CMD_DELAY_US);
	mutex_unlock(&drv_data->busy_lock);

	/* dump last error code */
	if (!err) {
		for (index=0; index<MINI_ISP_MAX_ERR_CODE; index++) {
			print_info("misp last error code[%d] = 0x%08x",
					index, drv_data->last_error_code[index]);
		}
	}
}

static void misp_dump_log(struct work_struct *work)
{
	int err = 0;
	struct misp_data *devdata =
			container_of(work, struct misp_data, dump_log_work);
	struct file *fp = NULL;
	mm_segment_t oldfs = get_fs();
	u8 param[8], ctrl_byte = USPICTRL_MS_CB_DIS;
	u32 *psize, *pblock;
	size_t len;
	struct spi_transfer	xfer[2];
	struct spi_message	m;

	print_info("%s enter", __func__);

	psize  = &param[0];
	pblock = &param[4];
	*psize = MINI_ISP_FW_LOG_BUF;
	*pblock= SPI_BLOCK_BUF_SIZE;
	memset(xfer, 0, sizeof(xfer));

	/* save log to buffer */
	mutex_lock_interruptible(&devdata->busy_lock);

	err = misp_send_cmd(devdata, ISPCMD_BULK_LOG_DUMP, param, sizeof(param));
	if (err)
		goto cmd_out;

	err = misp_poll_status(devdata);
	if (err)
		goto cmd_out;

	/*one message only, incase broken by spi interrupt */
	devdata->ext_buf[0] = ctrl_byte;
	xfer[0].tx_buf = devdata->ext_buf;
	xfer[0].len = sizeof(ctrl_byte);
	xfer[0].cs_change = 1;
	xfer[0].delay_usecs = 1;
	xfer[1].rx_buf = devdata->rx_buf;
	xfer[1].len = MINI_ISP_FW_LOG_BUF;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	spi_sync(devdata->spi, &m);

	/* dump log buffer to file */
	devdata->rx_buf[MINI_ISP_FW_LOG_BUF-1] = 0;
	len = strlen((char *)(devdata->rx_buf));
	if (len == 0) {
		print_warn("%s no data in log buf", __func__);
		goto cmd_out;
	}

	set_fs(KERNEL_DS);
	fp = filp_open("/data/k3_camera/misp.log", O_CREAT|O_APPEND|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_error("%s open log file error", __func__);
		goto file_out;
	}
	if (fp->f_pos < (4*1024*1024L)) {
		vfs_write(fp, devdata->rx_buf, len, &fp->f_pos);
	} else {
		print_warn("%s log file is larger than 4MB", __func__);
		filp_close(fp, NULL);
		fp = filp_open("/data/k3_camera/misp.log", O_CREAT|O_TRUNC|O_WRONLY, 0666);
		if (IS_ERR_OR_NULL(fp)) {
			print_error("%s create new log file error", __func__);
			goto file_out;
		}
		vfs_write(fp, devdata->rx_buf, len, &fp->f_pos);
	}

file_out:
	if (!IS_ERR_OR_NULL(fp))
		filp_close(fp, NULL);
	set_fs(oldfs);
cmd_out:
	udelay(MINI_ISP_CMD_DELAY_US);
	mutex_unlock(&devdata->busy_lock);
}

static int misp_spi_send(struct misp_data *devdata, u32 len)
{
	int status;
	u8 ctrl_byte = USPICTRL_MS_CB_ORG;
	struct spi_transfer	xfer[2] = {
		[0] = {
			.tx_buf = devdata->ext_buf,
			.rx_buf = NULL,
			.len = 1,
		},
		[1] = {
			.tx_buf = devdata->tx_buf,
			.rx_buf = NULL,
			.len = len,
		},
	};
	struct spi_message	m;

	print_debug("%s - send buf len=%d:", __func__, len);

	if ((!devdata) || (len > SPI_TX_BUF_SIZE)) {
		print_error("%s - invalid arg devdata=%p,len=%d",__func__, devdata, len);
		return -EINVAL;
	}
	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		print_error("%s - sync error: status=%d", __func__, status);
		return status;
	}

	if (devdata->debug_config & MINI_ISP_DEBUG_SPI_DATA)
		spi_data_debug(devdata->tx_buf, SPI_TX_BUF_SIZE, len);

	return status;
}

static int misp_spi_recv(struct misp_data *devdata, u32 len)
{
	int status;
	u8	ctrl_byte = USPICTRL_MS_CB_RSP;
	struct spi_transfer	xfer[2] = {
		[0] = {
			.tx_buf = devdata->ext_buf,
			.rx_buf = NULL,
			.len = 1,
		},
		[1] = {
			.tx_buf = NULL,
			.rx_buf = devdata->rx_buf,
			.len = len,
		},
	};
	struct spi_message	m;

	print_info("%s - recv buf len=%d:", __func__, len);

	if ((!devdata) || (len > SPI_RX_BUF_SIZE)) {
		print_error("%s - invalid arg devdata=%p,len=%d", __func__, devdata, len);
		return -EINVAL;
	}
	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);
	status = spi_sync(devdata->spi, &m);
	if (status) {
		print_error("%s - sync error: status=%d", __func__, status);
		return status;
	}

	if (devdata->debug_config & MINI_ISP_DEBUG_SPI_DATA)
		spi_data_debug(devdata->rx_buf, SPI_RX_BUF_SIZE, len);

	return status;
}

static int misp_poll_status(struct misp_data *devdata)
{
	int status, trys;
	u8	ctrl_byte = USPICTRL_MS_CB_STS;
	u16 ack = 0;
	struct spi_transfer	xfer[2] = {
		[0] = {
			.tx_buf = devdata->ext_buf,
			.rx_buf = NULL,
			.len = 1,
		},
		[1] = {
			.tx_buf = NULL,
			.rx_buf = devdata->rx_buf,
			.len = 2,
		},
	};
	struct spi_message	m;

	if (!devdata) {
		print_error("%s - invalid arg devdata=%p", __func__, devdata);
		return -EINVAL;
	}

	devdata->ext_buf[0] = ctrl_byte;
	spi_message_init(&m);
	spi_message_add_tail(&xfer[0], &m);
	spi_message_add_tail(&xfer[1], &m);

	for (trys=0 ; trys<MINI_ISP_POLL_TIMES; trys++) {
		status = spi_sync(devdata->spi, &m);
		if (status) {
			print_error("%s - sync error: status=%d", __func__, status);
			return status;
		}
		memcpy(&ack, devdata->rx_buf, sizeof(ack));
		if (ack == MINI_ISP_IRQ_READY_DONE)
			break;

		msleep(5);
	}

	if (ack == MINI_ISP_IRQ_READY_DONE) {
		print_info("%s - try times=%d", __func__, trys);
		return 0;
	} else {
		print_error("%s - timeout ack=0x%04x", __func__, ack);
		return -EAGAIN;
	}
}

static int misp_load_boot_code(struct misp_data *devdata, char *name)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	int file_size, one_size, left, block, ret;
	loff_t pos;

	set_fs(KERNEL_DS);
	fp = filp_open(name, O_RDONLY, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		print_info("%s open file error", __func__);
		set_fs(oldfs);
		return -EINVAL;
	}

	file_size =(int)(vfs_llseek(fp, 0L, SEEK_END));
	print_info("start sending boot code... size=0x%x", file_size);

	mutex_lock_interruptible(&devdata->busy_lock);
	vfs_llseek(fp, 0L, SEEK_SET);
	pos = fp->f_pos;
	for (left = file_size, block = 0; left > 0; left -= SPI_BLOCK_BUF_SIZE) {
		/* memset(devdata->tx_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE)? SPI_BLOCK_BUF_SIZE : left;

		ret = vfs_read(fp, devdata->tx_buf, one_size, &pos);
		if (ret < 0) {
			print_error("%s vfs read error %d", __func__, ret);
			break;
		}

		ret = spi_write(devdata->spi, devdata->tx_buf, one_size);
		if (ret < 0) {
			print_error("%s spi send error %d", __func__, ret);
			break;
		}
		block++;
	}

	print_info("%s succeed to send %d blocks", __func__, block);

	/* get boot code version info */
	vfs_llseek(fp, -32L, SEEK_END);
	vfs_read(fp, &devdata->boot_info, 32, &fp->f_pos);
	devdata->boot_info.info[15] = '\0';
	devdata->boot_info.user[8]  = '\0';
	print_info("%s boot version: %01u.%04u user=%s", __func__, \
										devdata->boot_info.major,\
										devdata->boot_info.minor,\
										devdata->boot_info.user);
	mutex_unlock(&devdata->busy_lock);
	filp_close(fp, 0);
	set_fs(oldfs);
	return ret;
}

static int misp_load_basic_code(struct misp_data *devdata, char *name)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	int one_size, left, block, ret;
	loff_t pos;
	u8 param[16];
	u32 *p_addr = (u32 *)&param[0];
	u32 *p_total_size =  (u32 *)&param[4];
	u32 *p_block_size =  (u32 *)&param[8]; 
	u32 *p_chk_sum =  (u32 *)&param[12];
	u8 ctrl_byte = USPICTRL_MS_CB_DIS, ack[2] = {0};
	
	set_fs(KERNEL_DS);
	fp = filp_open(name, O_RDONLY, 0644);
	if (IS_ERR_OR_NULL(fp)) {
		print_info("%s open file error", __func__);
		set_fs(oldfs);
		return -EINVAL;
	}

	vfs_llseek(fp, 0L, SEEK_SET);
	pos = fp->f_pos;
	vfs_read(fp, (char *)p_addr,		4, &pos);
	vfs_read(fp, (char *)p_total_size,	4, &pos);
	vfs_read(fp, (char *)p_chk_sum,		4, &pos);
	vfs_read(fp, (char *)p_block_size,	4, &pos);

	print_info("start sending basic code... size=0x%08x", *p_total_size);
	print_info("basic code info:addr=0x%08x chksum=0x%08x", *p_addr, *p_chk_sum);
	*p_block_size = SPI_BLOCK_BUF_SIZE;

	/* need to send a cmd to tell mini isp how many blocks to send*/
	mutex_lock_interruptible(&devdata->busy_lock);
	ret = misp_send_cmd(devdata, ISPCMD_BULK_WRITE_BASICCODE, param, sizeof(param));
	if (ret) {
		print_error("%s send cmd error", __func__);
		goto out;
	}

	/* disable other control bytes */
	/* todo: better to be one message with tx buf */
	devdata->ext_buf[0] = ctrl_byte;
	spi_write(devdata->spi, devdata->ext_buf, 1);

	/* basic code actually start with 16bytes offset */
	vfs_llseek(fp, 16L, SEEK_SET);
	pos = fp->f_pos;
	for (left = *p_total_size, block = 0; left > 0; left -= SPI_BLOCK_BUF_SIZE) {
		/* memset(devdata->ext_buf, 0, SPI_BLOCK_BUF_SIZE); */
		one_size = (left > SPI_BLOCK_BUF_SIZE)? SPI_BLOCK_BUF_SIZE : left;

		ret = vfs_read(fp, devdata->tx_buf, one_size, &pos);
		if (ret < 0) {
			print_error("%s vfs read error %d", __func__, ret);
			break;
		}

		ret = spi_write(devdata->spi, devdata->tx_buf, one_size);
		if (ret < 0) {
			print_error("%s spi send error %d", __func__, ret);
			break;
		}
		block++;
	}
	print_info("%s succeed to send %d blocks", __func__, block);

	/* get firmware version info */
	vfs_llseek(fp, -32L, SEEK_END);
	vfs_read(fp, &devdata->fw_info, 32, &fp->f_pos);
	devdata->fw_info.info[15] = '\0';
	devdata->fw_info.user[8]  = '\0';
	print_info("%s firmware version: %01u.%04u user=%s", __func__, \
											devdata->fw_info.major,\
											devdata->fw_info.minor,\
											devdata->fw_info.user);
out:
	mutex_unlock(&devdata->busy_lock);
	filp_close(fp, 0);
	set_fs(oldfs);
	return ret;
}

/*
 * mini isp debug functions, used to debug.
 * include :
 * [spi config] item
 * [debug config] item
 *
 */
static ssize_t misp_config_show(struct device *dev,
				struct device_attribute *attr, char *buf);
static ssize_t misp_config_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count);
static DEVICE_ATTR(misp_config, 0644, misp_config_show, misp_config_store);

static ssize_t misp_config_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	int ret = 0, index;
	struct misp_data *pdata = NULL;
	char *offset;

	print_info("%s - enter", __func__);

	pdata = (struct misp_data *)dev_get_drvdata(dev);
	if (NULL==pdata) {
		print_error("%s - get pdata error", __func__);
		return 0;
	}

	/* show [spi config info] item */
	offset = buf;
	ret = snprintf(offset, PAGE_SIZE, "[spi config info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  mode=%d, bit=%d, speed=%d\n",
					pdata->spi->mode,
					pdata->spi->bits_per_word,
					pdata->spi->max_speed_hz);

	/* show [debug config info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[debug config info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  debug=0x%08x\n", pdata->debug_config);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  log level=0x%08x\n", pdata->debug_log_level);

	/* show [boot version info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[boot version info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  info=%s\n", pdata->boot_info.info);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  version=%01u.%04u\n",\
										pdata->boot_info.major,\
										pdata->boot_info.minor);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  user=%s\n", pdata->boot_info.user);

	/* show [fw version info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[fw version info]\n");

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  info=%s\n", pdata->fw_info.info);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  version=%01u.%04u\n",\
										pdata->fw_info.major,\
										pdata->fw_info.minor);

	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "  user=%s\n", pdata->fw_info.user);

	/* show [last error info] item */
	offset += ret;
	ret = snprintf(offset, PAGE_SIZE, "[last error info]\n");

	offset += ret;
	for (index=0; index<MINI_ISP_MAX_ERR_CODE; index++) {
		ret = snprintf(offset, PAGE_SIZE, "  error code(%d)=0x%08x\n",
						index, pdata->last_error_code[index]);
		offset += ret;
	}
	return (offset-buf);
}

static void misp_config_spi(struct misp_data *pdata,
								u32 mode, u32 bits, u32 speed)
{
	int err;

	if (((mode & 0x03UL) > 3) || (bits > 32) || (speed > 48000000)) {
		print_warn("%s - invalid spi config [mode=0x%x bits=%d speed=%d]",
				__func__, mode, bits, speed);
		return ;
	}

	pdata->spi->mode= mode;
	pdata->spi->max_speed_hz = speed;
	pdata->spi->bits_per_word = bits;

	/* handle spi config */
	err = spi_setup(pdata->spi);
	if (!err) {
		print_info("%s - setup spi [mode=%d bits=%d speed=%d]",
					__func__, mode, bits, speed);
		return;
	}

	/* invalid spi config , set default spi config */
	print_warn("%s - setup spi failed. use default config", __func__);
	pdata->spi->mode = SPI_MODE_3;
	pdata->spi->max_speed_hz = MINI_ISP_SPI_SPEED_BOOT;
	pdata->spi->bits_per_word = 8;
	spi_setup(pdata->spi);
}

static void misp_config_log(struct misp_data *pdata,
								u32 new_config, u32 new_log_level)
{
	u32 old_config = pdata->debug_config;

	/* config misp linux driver log */
	if ( (old_config & MINI_ISP_DEBUG_LOG_FILE) &&
		!(new_config & MINI_ISP_DEBUG_LOG_FILE)) {
		queue_work(pdata->work_queue, &pdata->dump_log_work);
		flush_work(&pdata->dump_log_work);
	}
	pdata->debug_config = new_config;

	/* config misp internal firmware log */
	if (pdata->debug_log_level == new_log_level)
		return;
	pdata->debug_log_level = new_log_level;
	mutex_lock_interruptible(&pdata->busy_lock);
	misp_send_cmd(pdata, ISPCMD_SYSTEM_SET_LOG_LEVEL, &new_log_level, 4);
	mutex_unlock(&pdata->busy_lock);
}

static void misp_dump_reg(struct misp_data *pdata,
								u32* reg_table, u32 reg_table_size)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	u8 param[8], reg[48], reg_head[16], version[16];
	u32 *pstart=&param[0], *pcount=&param[4], index;
	int ret;
	char name[64];

	if (reg_table_size == 0) {
		print_error("%s invalid reg table size", __func__);
		return;
	}

	print_info("%s reg start=0x%x, reg end=0x%x", __func__,
				reg_table[0], reg_table[reg_table_size-1]);

	memset(name, 0, sizeof(name));
	snprintf(name, sizeof(name), "/data/k3_camera/misp_0x%08x.regx",
													reg_table[0]);

	/* create reg file */
	set_fs(KERNEL_DS);
	fp = filp_open(name, O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_error("%s create reg bin file error", __func__);
		set_fs(oldfs);
		return ;
	}

	/* add firmware version in dump file */
	memset(version, 0, sizeof(version));
	snprintf(version, sizeof(version), "%01u.%04u%s",
									pdata->fw_info.major,
									pdata->fw_info.minor,
									pdata->fw_info.user);
	vfs_write(fp, version, sizeof(version), &fp->f_pos);
	print_info("%s firmware version: %01u.%04u user=%s",
										__func__,
									pdata->fw_info.major,
									pdata->fw_info.minor,
									pdata->fw_info.user);

	/* get reg from spi cmd */
	mutex_lock_interruptible(&pdata->busy_lock);

	for (index = 0; index < reg_table_size; index++) {
		*pstart = reg_table[index];
		*pcount = 10;
		memset(reg_head, 0, sizeof(reg_head));
		snprintf(reg_head, sizeof(reg_head)-1, "[0x%08x]", reg_table[index]);

		pdata->state = MINI_ISP_STATE_IDLE;
		ret= misp_send_cmd(pdata, ISPCMD_SYSTEM_GET_ISPREGISTER, &param, sizeof(param));
		if (ret)
			break;

		ret = wait_event_interruptible_timeout(pdata->wait_queue,\
						(pdata->state == MINI_ISP_STATE_READY),\
						MINI_ISP_WAIT_TIMEOUT);

		if (ret <= 0) {
			print_warn("%s wait ready signal timeout", __func__);
			break;
		}

		ret = misp_recv_data(pdata, reg, sizeof(reg));
		if (ret)
			break;

		/* save reg head to file    : 16bytes */
		vfs_write(fp, reg_head, sizeof(reg_head), &fp->f_pos);
		/* save reg context to file : 48bytes */
		vfs_write(fp, reg, sizeof(reg), &fp->f_pos);
	}

out:
	mutex_unlock(&pdata->busy_lock);
	filp_close(fp, NULL);
	set_fs(oldfs);
	return ;
}


static void paser_reg_table(char *buf, u32 **out_ptr, u32 *out_count)
{
	u32  *reg_buf = NULL, reg_count = 0, reg_addr = 0, index = 0;
	char *pos = NULL;

	/* calulate how many reg table need to dump */
	pos = buf;
	reg_count = 0;
	while(*pos) {
		if (*pos == ']')
			break;
		if (pos[0] == '0' && tolower(pos[1]) == 'x') {
			reg_count++;
			pos += 2;
		} else
			pos++;
	}

	/* alloc buf and fill the buf with reg_address*/
	if (reg_count == 0) {
		reg_buf = NULL;
	} else {
		reg_buf = kmalloc(sizeof(u32) * reg_count, GFP_KERNEL);
		pos = buf;
		index = 0;
		while ((*pos) && (index < reg_count)) {
			if (*pos == ']')
				break;

			while (!isdigit(*pos))
				pos++;

			reg_addr = simple_strtoul(pos, &pos, 0);
			reg_buf[index] = reg_addr;

			index++;
		}
	}

	print_info("%s reg_count=%d", __func__, reg_count);
	*out_ptr = reg_buf;
	*out_count = reg_count;
}


static void misp_dump_ram(struct misp_data *pdata,
								u32 start, u32 total, u32 mode)
{
	mm_segment_t oldfs = get_fs();
	struct file *fp = NULL;
	u8 param[16], ctrl_byte = USPICTRL_MS_CB_DIS;
	u32 *paddr=&param[0], *ptotal=&param[4], *pblock=&param[8], *pmode=&param[12];
	int ret, one_size, left;
	char name[64];

	print_info("%s start=0x%x, total=%u, mode=%u", __func__, start, total, mode);

	memset(name, 0, sizeof(name));
	snprintf(name, sizeof(name), "/data/k3_camera/misp_0x%08x.ram", start);

	set_fs(KERNEL_DS);
	fp = filp_open(name, O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if (IS_ERR_OR_NULL(fp)) {
		print_error("%s create ram bin file error", __func__);
		set_fs(oldfs);
		return;
	}

	if (total == 0)
		total = 936*1024;
	memset(param, 0, sizeof(param));
	*paddr = start;
	*ptotal = total;
	*pblock = SPI_BLOCK_BUF_SIZE;
	*pmode = mode;

	mutex_lock_interruptible(&pdata->busy_lock);

	pdata->state = MINI_ISP_STATE_IDLE;
	ret= misp_send_cmd(pdata, ISPCMD_BULK_READ_MEMORY, &param, sizeof(param));
	if (ret)
		goto out;

	ret = wait_event_interruptible_timeout(pdata->wait_queue,\
						(pdata->state == MINI_ISP_STATE_READY),\
						MINI_ISP_WAIT_TIMEOUT);

	if (ret <= 0) {
		print_warn("%s wait ready signal timeout", __func__);
		goto out;
	}

	/* disable interrpt to avoid messages broken */
	disable_irq(pdata->spi->irq);
	pdata->ext_buf[0] = ctrl_byte;
	spi_write(pdata->spi, pdata->ext_buf, sizeof(ctrl_byte));
	for (left = total; left > 0; left -= SPI_BLOCK_BUF_SIZE) {
		one_size = (left > SPI_BLOCK_BUF_SIZE)? SPI_BLOCK_BUF_SIZE : left;
		spi_read(pdata->spi, pdata->rx_buf, one_size);
		vfs_write(fp, pdata->rx_buf, one_size, &fp->f_pos);
	}
	enable_irq(pdata->spi->irq);

out:
	mutex_unlock(&pdata->busy_lock);
	filp_close(fp, NULL);
	set_fs(oldfs);
	return;
}

static void misp_write_reg(struct misp_data *pdata,
										u32 addr, u32 val)
{
	u8 param[8];
	u32 *paddr=&param[0], *pval=&param[4];

	print_info("%s addr=0x%x, val=0x%x", __func__, addr, val);

	*paddr = addr;
	*pval = val;
	mutex_lock_interruptible(&pdata->busy_lock);
	misp_send_cmd(pdata, ISPCMD_SYSTEM_SET_ISPREGISTER, &param, sizeof(param));
	mutex_unlock(&pdata->busy_lock);
}

static void misp_test_spi(struct misp_data *pdata)
{
	int index;
	struct spi_transfer	xfer = {
		.tx_buf = pdata->tx_buf,
		.rx_buf = pdata->rx_buf,
		.len = SPI_TX_BUF_SIZE,
	};
	struct spi_message m;

	mutex_lock_interruptible(&pdata->busy_lock);

	for (index = 0; index < SPI_TX_BUF_SIZE; index++) {
		get_random_bytes(&(pdata->tx_buf[index]), 1);
		pdata->rx_buf[index] = 0;
	}

	spi_message_init(&m);
	spi_message_add_tail(&xfer, &m);
	spi_sync(pdata->spi, &m);

	mutex_unlock(&pdata->busy_lock);

	if (pdata->debug_config & MINI_ISP_DEBUG_SPI_DATA) {
		print_info("%s - send buf len=%d:", __func__, SPI_TX_BUF_SIZE);
		spi_data_debug(pdata->tx_buf, SPI_TX_BUF_SIZE, SPI_TX_BUF_SIZE);
		print_info("%s - recv buf len=%d:", __func__, SPI_RX_BUF_SIZE);
		spi_data_debug(pdata->rx_buf, SPI_TX_BUF_SIZE, SPI_TX_BUF_SIZE);
	}
}

static ssize_t misp_config_store(struct device *dev,
				struct device_attribute *attr, const char *buf, size_t count)
{
	int ret = 0;
	u32 mode = 0, bits = 0, speed = 0;
	u32 new_log_config = 0, new_log_level = 0;
	u32 dump_reg_table_count = 0, *dump_reg_table = NULL;
	u32 *default_reg_table = misp_default_reg_table;
	u32 default_reg_table_count = ARRAY_SIZE(misp_default_reg_table);
	u32 dump_ram_start = 0, dump_ram_total = 0, dump_ram_mode = 0;
	u32 write_reg_addr = 0, write_reg_val = 0;
	struct misp_data *pdata = NULL;
	char *pos;

	print_info("%s - enter", __func__);

	pdata = (struct misp_data *)dev_get_drvdata(dev);
	if (NULL == pdata) {
		print_error("%s - get pdata error", __func__);
		return 0;
	}

	if (count == 0)
		return 0;

	pos = buf;
	if (0 == strncmp("spi_config", pos, strlen("spi_config"))) {
		while ((*pos) && (!isdigit(*pos)))
			pos++;
		sscanf(pos, "0x%x %u %u", &mode, &bits, &speed);
		misp_config_spi(pdata, mode, bits, speed);
	} else if (0 == strncmp("log_config", pos, strlen("log_config"))) {
		while ((*pos) && (!isdigit(*pos)))
			pos++;
		sscanf(pos, "%u %u", &new_log_config, &new_log_level);
		misp_config_log(pdata, new_log_config, new_log_level);
	} else if (0 == strncmp("dump_reg", pos, strlen("dump_reg"))) {
		pos += strlen("dump_reg");
		if (*pos == '=')
			paser_reg_table(pos, &dump_reg_table, &dump_reg_table_count);
		if (dump_reg_table == NULL) {
			misp_dump_reg(pdata, default_reg_table, default_reg_table_count);
		} else {
			misp_dump_reg(pdata, dump_reg_table, dump_reg_table_count);
			kfree(dump_reg_table);
		}
	} else if (0 == strncmp("dump_ram", pos, strlen("dump_ram"))) {
		while ((*pos) && (!isdigit(*pos)))
			pos++;
		sscanf(pos, "0x%x %u %u", &dump_ram_start, &dump_ram_total, &dump_ram_mode);
		misp_dump_ram(pdata, dump_ram_start, dump_ram_total, dump_ram_mode);
	} else if (0 == strncmp("write_reg", pos, strlen("write_reg"))) {
		while ((*pos) && (!isdigit(*pos)))
			pos++;
		sscanf(pos, "0x%x 0x%x", &write_reg_addr, &write_reg_val);
		misp_write_reg(pdata, write_reg_addr, write_reg_val);
	} else if (0 == strncmp("test_spi", pos, strlen("test_spi"))) {
		misp_test_spi(pdata);
	}

	return count;
}


static int mini_isp_probe(struct spi_device *spi)
{
	struct misp_data *drv_data = NULL;
	struct misp_plat_data *plat_data = NULL;
	int ret = 0;
	u32 use_misp_driver = 0;

	print_info("%s - enter", __func__);

	get_hw_config_int("camera/miniisp", &use_misp_driver, NULL);
	if (!use_misp_driver) {
		print_warn("probe - not configed to use mini isp drvier\n");
		return -ENODEV;
	}

	plat_data = (struct misp_plat_data *)(dev_get_platdata(&spi->dev));
	if (!plat_data) {
		print_error("probe - no plat data");
		return -ENODEV;
	}

	/* step 1: alloc driver data struct */
	drv_data = kmalloc(sizeof(*drv_data), GFP_KERNEL);
	if (!drv_data) {
		print_error("probe - can not alloc driver data");
		return -ENOMEM;
	}
	memset(drv_data, 0, sizeof(*drv_data));

	drv_data->tx_buf  = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(2*PAGE_SIZE));
	drv_data->rx_buf  = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(PAGE_SIZE));
	drv_data->ext_buf = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(PAGE_SIZE));
	drv_data->irq_buf = (void *)__get_free_pages(GFP_KERNEL|GFP_DMA, get_order(PAGE_SIZE));
	print_info("probe - tx_buf=0x%p rx_buf=0x%p ext_buf=0x%p, irq_buf=0x%p",
		drv_data->tx_buf, drv_data->rx_buf, drv_data->ext_buf, drv_data->irq_buf);
	if ((!drv_data->tx_buf) || (!drv_data->rx_buf) ||
		(!drv_data->ext_buf)|| (!drv_data->irq_buf)) {
		print_error("probe - can not alloc dma buf page");
		ret = -ENOMEM;
		goto err_alloc_buf;
	}

	/* step 2: init driver data */
	drv_data->spi = spi;
	drv_data->plat_data = plat_data;
	drv_data->state = MINI_ISP_STATE_IDLE;
	drv_data->debug_config = 0;
	mutex_init(&drv_data->busy_lock);
	INIT_WORK(&drv_data->dump_log_work, misp_dump_log);
	INIT_WORK(&drv_data->dump_err_work, misp_dump_err);
	init_waitqueue_head(&drv_data->wait_queue);
	init_waitqueue_head(&drv_data->sync_queue);
	init_waitqueue_head(&drv_data->pwdn_queue);
	drv_data->work_queue = create_singlethread_workqueue(
									dev_name(&spi->dev));
	if (!drv_data->work_queue) {
		print_error("probe - create workqueue error");
		ret = -EBUSY;
		goto err_create_queue;
	}

	/* step 3: setup spi */
	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = MINI_ISP_SPI_SPEED_BOOT;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret<0) {
		print_error("probe - setup spi error");
		goto err_spi_setup;
	}

	/* step 4:config gpio & irq */
	ret = gpio_request(plat_data->spi_cs_gpio, "mini_isp_spi_cs");
	if (ret) {
		print_error("probe - request spi cs gpio error");
		goto err_cs_gpio;
	}
	if (gpio_direction_input(plat_data->spi_cs_gpio))
		print_warn("probe - spi cs gpio direction input error");


	ret = gpio_request(plat_data->reset_gpio, "mini_isp_reset");
	if (ret) {
		print_error("probe - request reset gpio error");
		goto err_reset_gpio;
	}

	ret = gpio_request(plat_data->power_gpio, "mini_isp_dcdc");
	if (ret) {
		print_error("probe - request power gpio error");
		goto err_power_gpio;
	}

	ret = gpio_request(plat_data->irq_gpio, "mini_isp_irq");
	if (ret) {
		print_error("probe - request irq gpio error");
		goto err_irq_gpio;
	}
	if (gpio_direction_input(plat_data->irq_gpio))
		print_warn("probe - irq gpio direction input error");

	ret = request_threaded_irq(spi->irq, NULL, misp_irq_thread,
							IRQF_ONESHOT | IRQF_TRIGGER_RISING,
							"mini_isp", drv_data);
	if (ret) {
		print_error("probe - request irq error");
		goto err_irq_config;
	}

	/* setp 5:other additional config */
	ret = device_create_file(&spi->dev, &dev_attr_misp_config);
	if (ret) {
	    print_error("probe - create dev attr file fail");
		goto err_dev_attr;
	}

	/* setp 6: set driver_data to device */
	spi_set_drvdata(spi, drv_data);

	misp_drv_data = drv_data;

	print_info("mini isp probe success");
	return ret;

err_dev_attr:
	free_irq(spi->irq, drv_data);
err_irq_config:
	gpio_free(plat_data->irq_gpio);
err_irq_gpio:
	gpio_free(plat_data->power_gpio);
err_power_gpio:
	gpio_free(plat_data->reset_gpio);
err_reset_gpio:	
	gpio_free(plat_data->spi_cs_gpio);
err_cs_gpio:
err_spi_setup:
	destroy_workqueue(drv_data->work_queue);
err_create_queue:
	free_pages((unsigned long)drv_data->tx_buf,  get_order(2*PAGE_SIZE));
	free_pages((unsigned long)drv_data->rx_buf,  get_order(PAGE_SIZE));
	free_pages((unsigned long)drv_data->ext_buf, get_order(PAGE_SIZE));
	free_pages((unsigned long)drv_data->irq_buf, get_order(PAGE_SIZE));
err_alloc_buf:
	kfree(drv_data);
	misp_drv_data = NULL;
	return ret;
}


static struct spi_driver mini_isp_drv = {
	.driver = {
		.name =         "mini_isp",
		.owner =        THIS_MODULE,
	},
	.probe =        mini_isp_probe,
	.remove =       NULL,
};

static int __init mini_isp_init(void)
{
	return spi_register_driver(&mini_isp_drv);
}

static void __exit mini_isp_exit(void)
{
	spi_unregister_driver(&mini_isp_drv);
}

module_init(mini_isp_init);
module_exit(mini_isp_exit);
MODULE_LICENSE("Huawei/GPL");

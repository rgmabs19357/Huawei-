/*
 *  Hisilicon K3 soc camera ISP driver source file
 *
 *  CopyRight (C) Hisilicon Co., Ltd.
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* system include */
#include <linux/io.h>
#include <mach/irqs.h>
#include <mach/platform.h>
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/err.h>
#include <linux/platform_device.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include "mini_k3_ispv1_io.h"
#include "mini_cam_dbg.h"

#include <mach/clk_name_interface.h>
#include "reg_ops.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_pmctrl_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "drv_regulator_user.h"

#include <mach/io_mutex.h>
#include "camera_agent.h"
#include <linux/rtc.h>
#include <linux/time.h>
#include <linux/log_exception.h>


#define DEBUG_DEBUG 0
#define LOG_TAG "K3_ISPV1_IO"
#include "mini_cam_log.h"

#define CSI_INT_EN 0x00000000
#define CSI_INT_DIS 0xffffffff

/*#define SETREG8(mem, value) iowrite8_mutex((value), (mem))*/
/*#define GETREG8(mem) (*(volatile u8 *)(mem))*/
#define CSI_GETREG32(mem) ioread32_mutex((mem))
#define CSI_SETREG32(mem, value) iowrite32_mutex((value), (mem))

static mini_ispio_controller ispv1_io_ctl;

static mini_ispio_hw_t ispv1_io;


#define CSI0_REG_OFFSET  (0x00)
#define CSI1_REG_OFFSET  (0x800)


#define CSI0_REG_BASE  (ispv1_io.csi0_base)
#define CSI1_REG_BASE  (ispv1_io.csi1_base)

#define CSI_REG_N_LANES     	(0x04)
#define CSI_REG_PHY_SHUTDOWNZ   (0x08)
#define CSI_REG_DPHY_RSTZ       (0x0c)
#define CSI_REG_RESETN      	(0x10)
#define CSI_REG_PHY_STATE       (0x14)
#define CSI_REG_MASK1           (0x28)
#define CSI_REG_MASK2           (0x2c)

#define CSI0_REG_ERR1            (CSI0_REG_BASE + 0x20)
#define CSI0_REG_ERR2            (CSI0_REG_BASE + 0x24)
#define CSI1_REG_ERR1            (CSI1_REG_BASE + 0x20)
#define CSI1_REG_ERR2            (CSI1_REG_BASE + 0x24)

#define PHY_TST_CONTRL0           (0x30)
#define PHY_TST_CONTRL1           (0x34)

#define PHY_STATE_STOPSTATE0       (1 << 4)
#define PHY_STATE_STOPSTATE1       (1 << 5)
#define PHY_STATE_RXCLKACTIVEHS    (1 << 8)
#define PHY_STATE_STOPSTATECLK     (1 << 10)

static void ispv1_io_set_default(void);


void fake_csi_error(void)
{
	mini_ispio_hw_t *dev_data = &ispv1_io;

	print_info("Enter %s", __func__);

	if (!dev_data->mipi_csi_exception_already_report) {
		dev_data->mipi_csi_exception_already_report = true;
		schedule_work(&dev_data->mipi_csi_exception_work);
		flush_work(&dev_data->mipi_csi_exception_work);
	}
}

void get_time_stamp(char* timestamp_buf,unsigned int len)
{
	struct timeval tv;
	struct rtc_time tm;

	if (NULL == timestamp_buf) {
		print_error("%s,timestamp is NULL", __func__);
		return;
	}
	memset(&tv, 0, sizeof(struct timeval));
	memset(&tm, 0, sizeof(struct rtc_time));
	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);
	snprintf(timestamp_buf,len,"%04d%02d%02d%02d%02d%02d",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	print_info("%s,exception time=%s", __func__, timestamp_buf);
}

static void mipi_csi_exception_handler(struct work_struct *work)
{
	char cmd[256];
	char time_stamp[16];

	print_info("%s enter", __func__);

	memset(time_stamp, 0, sizeof(time_stamp));
	get_time_stamp(time_stamp, sizeof(time_stamp));

	memset(cmd, 0, sizeof(cmd));
	snprintf(cmd, sizeof(cmd),
			"archive -i %s -i %s -i %s -o %s_CAMERA-MIPICSI -z zip",
			"/data/android_logs/kmsgcat-log",
			"/data/android_logs/kmsgcat-log.1",
			"/data/k3_camera/misp.regx",
			time_stamp);

	print_info("%s:%s", __func__, linux_banner);
	misp_flush_reg();
	log_to_exception("CAMERA", cmd);
}


#ifdef REG_CSI_IRQ
/*
 **************************************************************************
 * FunctionName: k3_csi0_isr;
 * Description : csi0 interrupt handler;
 * Input       : irq; dev_id
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static irqreturn_t k3_csi0_isr(int irq, void *dev_id)
{
	u32 irq_status1;
	u32 irq_status2;
	mini_ispio_hw_t *dev_data = dev_id;

	irq_status1 = CSI_GETREG32(CSI0_REG_ERR1);
	irq_status2 = CSI_GETREG32(CSI0_REG_ERR2);

	if ((irq_status1 | irq_status2) != 0) {
		print_error("k3_csi_isr1 ERR1[%#x], ERR2[%#x]", irq_status1, irq_status2);
		if (!dev_data->mipi_csi_exception_already_report) {
			dev_data->mipi_csi_exception_already_report = true;
			schedule_work(&dev_data->mipi_csi_exception_work);
		}
	}

	/* automatic clear all interrupts */

	return IRQ_HANDLED;

}

/*
 **************************************************************************
 * FunctionName: k3_csi1_isr;
 * Description : csi0 interrupt handler;
 * Input       : irq; dev_id
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static irqreturn_t k3_csi1_isr(int irq, void *dev_id)
{
	u32 irq_status1;
	u32 irq_status2;
	mini_ispio_hw_t *dev_data = dev_id;

	irq_status1 = CSI_GETREG32(CSI1_REG_ERR1);
	irq_status2 = CSI_GETREG32(CSI1_REG_ERR2);

	if ((irq_status1 | irq_status2) != 0) {
		print_error("k3_csi_isr2 ERR1[%#x], ERR2[%#x]", irq_status1, irq_status2);
		if (!dev_data->mipi_csi_exception_already_report) {
			dev_data->mipi_csi_exception_already_report = true;
			schedule_work(&dev_data->mipi_csi_exception_work);
		}
	}
	/* automatic clear all interrupts */

	return IRQ_HANDLED;
}
#endif

static int ispv1_get_iomux(u8 *name, struct iomux_block **block,
		    struct block_config **block_conf)
{

	*block = iomux_get_block(name);

	if (!*block) {
		print_error("%s: failed to get iomux %s\n", __func__, name);
		return PTR_ERR(*block);
	}

	*block_conf = iomux_get_blockconfig(name);

	if (!*block_conf) {
		print_error("%s: failed to get iomux isp %s\n", __func__, name);
		return PTR_ERR(*block_conf);
	}

	return 0;

}

static int ispv1_get_resource(void)
{
	struct clk *clk = NULL;
	struct resource *res = NULL;
	int ret = 0;

	print_debug("%s", __func__);

	/* get reg base */


	res = platform_get_resource_byname(ispv1_io.pdev, IORESOURCE_MEM, "csi_base");
	if (res == NULL) {
		print_error("failed to get io men resource");
		ret = -ENXIO;
		goto fail;
	}


    /*FIXME: BSP has not support the interface IO_ADDRESS*/

	ispv1_io.csi0_base = ioremap(res->start, resource_size(res));
	if (!ispv1_io.csi0_base) {
		print_error("failed to get ispv1_io.csi0_base)");
		return -ENOMEM;
	}
    ispv1_io.csi1_base = ispv1_io.csi0_base + CSI1_REG_OFFSET;

	mini_register_cam_dbg_info(DBG_INFO_CSI0_BASE, (void *)ispv1_io.csi0_base);
	mini_register_cam_dbg_info(DBG_INFO_CSI1_BASE, (void *)ispv1_io.csi1_base);

	/* get irq resource */
#ifdef REG_CSI_IRQ
	res = platform_get_resource_byname(ispv1_io.pdev, IORESOURCE_IRQ, "csi0_irq");

	if (res == NULL) {
		print_error("failed to get irq: csi0_irq");
		ret = -ENXIO;
		goto fail;
	}

	ispv1_io.csi0_irq = res->start;

	res = platform_get_resource_byname(ispv1_io.pdev, IORESOURCE_IRQ, "csi1_irq");

	if (res == NULL) {
		print_error("failed to get irq: csi1_irq");
		ret = -ENXIO;
		goto fail;
	}

	ispv1_io.csi1_irq = res->start;
#endif
	/* get clk
	clk = clk_get(NULL, "clk_ispmipi");
	if (IS_ERR_OR_NULL(clk)) {
		print_error("failed to get isp clock");
		ret = -ENXIO;
		goto fail;

	}
	ispv1_io.csi_clk = clk;*/

	clk = clk_get(NULL, CLK_CSIO_CFG);
	if (IS_ERR_OR_NULL(clk)) {
		print_error("failed to get csi0 controller clock");
		ret = -ENXIO;
		goto fail;
	}
	ispv1_io.csi0_clk= clk;

	clk = clk_get(NULL, CSI2_CFG_CLK);
	if (IS_ERR_OR_NULL(clk)) {
		print_error("failed to get csi2 controller clock");
		ret = -ENXIO;
		goto fail;
	}
	ispv1_io.csi2_clk= clk;

	clk = clk_get(NULL, CLK_DPHY1_CFG);
	if (IS_ERR_OR_NULL(clk)) {
		print_error("failed to get dphy1 clock");
		ret = -ENXIO;
		goto fail;
	}
	ispv1_io.phy1_clk = clk;

	clk = clk_get(NULL, CLK_DPHY2_CFG);
	if (IS_ERR_OR_NULL(clk)) {
		print_error("failed to get dphy2 clock");
		ret = -ENXIO;
		goto fail;
	}
	ispv1_io.phy2_clk = clk;

#ifdef REG_CSI_IRQ
	print_info("request csi0 & csi1 irq");
	ret = request_irq(ispv1_io.csi0_irq, k3_csi0_isr, 0, "csi0_irq", &ispv1_io);

	if (ret != 0) {
		print_error("fail to request irq [%d]", res->start);
		goto fail;
	}

	ret = request_irq(ispv1_io.csi1_irq, k3_csi1_isr, 0, "csi1_irq", &ispv1_io);

	if (ret != 0) {
		print_error("fail to request irq [%d]", res->start);
		goto fail;
	}
#endif

	print_debug("exit %s, csi0_base[%#x]", __func__, ispv1_io.csi0_base);

	return 0;

fail:
#ifdef REG_CSI_IRQ
	if (ispv1_io.csi0_irq) {
		free_irq(ispv1_io.csi0_irq, &ispv1_io);
	}

	if (ispv1_io.csi1_irq) {
		free_irq(ispv1_io.csi1_irq, &ispv1_io);
	}
#endif

	/*if (ispv1_io.csi_clk) {
		clk_put(ispv1_io.csi_clk);
		ispv1_io.csi_clk = NULL;
	}*/

	if (ispv1_io.csi0_clk) {
		clk_put(ispv1_io.csi0_clk);
		ispv1_io.csi0_clk = NULL;
	}

	if (ispv1_io.csi2_clk) {
		clk_put(ispv1_io.csi2_clk);
		ispv1_io.csi2_clk = NULL;
	}

	if (ispv1_io.phy1_clk) {
		clk_put(ispv1_io.phy1_clk);
		ispv1_io.phy1_clk = NULL;
	}

	if (ispv1_io.phy2_clk) {
		clk_put(ispv1_io.phy2_clk);
		ispv1_io.phy2_clk = NULL;
	}

	return ret;
}

static void ispv1_release_resource(void)
{
	print_debug("enter %s", __func__);

#ifdef REG_CSI_IRQ
	if (ispv1_io.csi0_irq) {
		free_irq(ispv1_io.csi0_irq, &ispv1_io);
		ispv1_io.csi0_irq = 0;
	}

	if (ispv1_io.csi1_irq) {
		free_irq(ispv1_io.csi1_irq, &ispv1_io);
		ispv1_io.csi1_irq = 0;
	}
#endif

        /*FIXME: BSP has not support the interface IO_ADDRESS*/

        iounmap(ispv1_io.csi0_base);


	if (ispv1_io.csi0_clk) {
		clk_put(ispv1_io.csi0_clk);
		ispv1_io.csi0_clk = NULL;
	}

	if (ispv1_io.csi2_clk) {
		clk_put(ispv1_io.csi2_clk);
		ispv1_io.csi2_clk = NULL;
	}

	if (ispv1_io.phy1_clk) {
		/*clk_disable(ispv1_io.phy1_clk); */
		clk_put(ispv1_io.phy1_clk);
		ispv1_io.phy1_clk = NULL;
	}

	if (ispv1_io.phy2_clk) {
		/*clk_disable(ispv1_io.phy2_clk); */
		clk_put(ispv1_io.phy2_clk);
		ispv1_io.phy2_clk = NULL;

	}

}

/***************************************************************************
 * FunctionName: ispv1_csi_phy_set;
 * Description : csi phyhardware poweron region set;
 * Input       : csiphy_power_enum;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 ***************************************************************************/
static void ispv1_csi_phy_set(camera_power_state type, csi_index_t index)
{
    if (POWER_ON == type) {
        if (index == CSI_INDEX_0) {
            /* CSI PHY0 RSTDIS */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_22cs0phy_START,
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_22cs0phy_END,
                           0x1);

            /* CSI PHY0 CLKREG ENABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_22cs0phy_START,
                           SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_22cs0phy_END,
                           0x1);
        } else {
            /* CSI PHY2 RSTDIS */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_24cs2phy_START,
                           SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_24cs2phy_END,
                           0x1);

            /* CSI PHY2 CLKREG ENABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_24cs2phy_START,
                           SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_24cs2phy_END,
                           0x1);
        }
    } else if (POWER_OFF == type) {
        if (index == CSI_INDEX_0) {
            /* CSI PHY0 CLKREG DISABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_22cs0phy_START,
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_22cs0phy_END,
                           0x1);

            /* CSI PHY0 RST ENABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_22cs0phy_START,
                           SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_22cs0phy_END,
                           0x1);
        } else {
            /* CSI PHY2 CLKREG DISABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_24cs2phy_START,
                           SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_24cs2phy_END,
                           0x1);

            /* CSI PHY2 RST ENABLE */
            phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                           SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(0),
                           SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_24cs2phy_START,
                           SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_24cs2phy_END,
                           0x1);
        }
    } else {
        print_error("%s, ispv1_power_enum input error:%d", __func__, type);
    }

    return;
}

/***************************************************************************
 * FunctionName: ispv1_csi_poweron;
 * Description : csi&phy clock enable
 * Input       : csi_index_t enum
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 ***************************************************************************/
static int ispv1_csi_poweron(csi_index_t index)
{
	int ret = 0;

    if (0 != mini_get_cam_pwdn_status(DEBUGFS_PWDN_CSI)) {
	    print_info("%s, csi&phy is already poweron.", __func__);
        return ret;
    }

    print_info("%s, enable phy clock", __func__);

	/* clk_set_rate(ispv1_io.isp_clk, 132000000);  132MHz  */
	/* clk_enable(ispv1_io.csi_clk); */

    ispv1_csi_phy_set(POWER_ON, index);

	if (index == CSI_INDEX_0) {
		ret = clk_enable(ispv1_io.csi0_clk);
		if (IS_ERR_OR_NULL(ispv1_io.csi0_clk))
		    return ret;

		ret = clk_enable(ispv1_io.phy1_clk);
		if (IS_ERR_OR_NULL(ispv1_io.phy1_clk)) {
		    clk_disable(ispv1_io.csi0_clk);
		    return ret;
		}
	} else {
	    ret = clk_enable(ispv1_io.csi2_clk);
		if (IS_ERR_OR_NULL(ispv1_io.csi2_clk))
		    return ret;

		ret = clk_enable(ispv1_io.phy2_clk);
		if (IS_ERR_OR_NULL(ispv1_io.phy2_clk)) {
		    clk_disable(ispv1_io.csi2_clk);
		    return ret;
		}
	}

    mini_set_cam_pwdn_status(DEBUGFS_PWDN_CSI, 1);

    return ret;
}

/***************************************************************************
 * FunctionName: ispv1_csi_poweroff;
 * Description : csi&phy clock disable
 * Input       : csi_index_t enum
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 ***************************************************************************/
static void ispv1_csi_poweroff(csi_index_t index)
{
	struct clk *phy_clk = NULL;
	struct clk* csi_clk = NULL;

    if (0 == mini_get_cam_dbgfs_pwdncfg()) {
	    print_info("%s, csi&phy not need to power off.", __func__);
        return;
    }

    if (index == CSI_INDEX_0) {
        csi_clk = ispv1_io.csi0_clk;
        phy_clk = ispv1_io.phy1_clk;
    } else {
        csi_clk = ispv1_io.csi2_clk;
        phy_clk = ispv1_io.phy2_clk;
    }

    clk_disable(phy_clk);
    clk_disable(csi_clk);

    ispv1_csi_phy_set(POWER_OFF, index);

    mini_set_cam_pwdn_status(DEBUGFS_PWDN_CSI, 0);
}

/*
 **************************************************************************
 * FunctionName: ispv1_init_csi;
 * Description : csi init;
 * Input       : mipi_lane_count: lane count 1~8
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_init_csi(csi_index_t index, csi_lane_t mipi_lane_count, u8 lane_clk)
{
	int ret = 0;
	u32 phy_state1;
	u8 __iomem * reg_base;

	ret = ispv1_get_resource();
	if (ret)
		return ret;

	print_info("Enter %s, index[%d], mipi_lane_count[%d]", __func__,
		   index, mipi_lane_count);

    ret = ispv1_csi_poweron(index);
    print_info("%s, csi debugfs pwdn config = %d, csi pwdn status = %d\n",
        __func__, mini_get_cam_dbgfs_pwdncfg(), mini_get_cam_pwdn_status(DEBUGFS_PWDN_CSI));
#ifdef DUMP_SCCTRL_ISP_REG
    mini_dump_scctrl_isp_reg();
#endif
    if (ret) {
		print_error("%s: csi power on fail.", __func__);
        return ret;
    }

    if (index == CSI_INDEX_0) {
        reg_base = ispv1_io.csi0_base;
    } else {
        reg_base = ispv1_io.csi1_base;
    }

	CSI_SETREG32(reg_base + CSI_REG_PHY_SHUTDOWNZ, 0);
	CSI_SETREG32(reg_base + CSI_REG_PHY_SHUTDOWNZ, 1);
	CSI_SETREG32(reg_base + CSI_REG_N_LANES, (u32) mipi_lane_count);

	/*msleep(10); */

	CSI_SETREG32(reg_base + CSI_REG_DPHY_RSTZ, 0);
	CSI_SETREG32(reg_base + CSI_REG_DPHY_RSTZ, 1);
	CSI_SETREG32(reg_base + CSI_REG_RESETN, 0);
	CSI_SETREG32(reg_base + CSI_REG_RESETN, 1);
	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 1);
	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);

	CSI_SETREG32(reg_base + PHY_TST_CONTRL1, 0x10044);
	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 2);
	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);

	CSI_SETREG32(reg_base + PHY_TST_CONTRL1, lane_clk);

	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 2);
	CSI_SETREG32(reg_base + PHY_TST_CONTRL0, 0);

	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that all data
	   and clock lanes of the D-PHY are in Stop State (that is, ready to receive data).
	 */

	/*
	   Configure the MIPI Camera Sensor - Access Camera Sensor using CCI interface to initialize and
	   configure the Camera Sensor to start transmitting a clock on the D-PHY clock lane.
	 */

	/*
	   csi-2 Controller programming - Read the PHY status register (PHY_STATE) to confirm that the
	   D-PHY is receiving a clock on the D-PHY clock lane.
	 */
	phy_state1 = CSI_GETREG32(reg_base + CSI_REG_PHY_STATE);

	if (0 == (phy_state1 & PHY_STATE_STOPSTATE0)
	    && 0 == (phy_state1 & PHY_STATE_STOPSTATECLK)) {
		print_info("Not all data and clock lanes of the D-PHY are in Stop State, "
			"phy_state1 : %#x ", phy_state1);
	}

	if (0 == (phy_state1 & PHY_STATE_RXCLKACTIVEHS))
		print_info("D-PHY was not receive a clock \n");

	/*enable all interrupt */
	CSI_SETREG32(reg_base + CSI_REG_MASK1, CSI_INT_EN);	/* TBD 0x0f00f000 except err_l_seq_di err_frame_data_vc */
	CSI_SETREG32(reg_base + CSI_REG_MASK2, CSI_INT_EN);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_deinit_csi;
 * Description : csi deinit;
 * Input       : NA
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_deinit_csi(csi_index_t index)
{
	u8 __iomem * reg_base;

	print_debug("Enter %s, index[%d]", __func__, index);

	if (index == CSI_INDEX_0) {
		reg_base = ispv1_io.csi0_base;
	} else {
		reg_base = ispv1_io.csi1_base;
	}

	CSI_SETREG32(reg_base + CSI_REG_RESETN, 0);
	CSI_SETREG32(reg_base + CSI_REG_PHY_SHUTDOWNZ, 0);

    ispv1_csi_poweroff(index);
    print_info("%s, csi debugfs pwdn config = %d, csi pwdn status = %d",
        __func__, mini_get_cam_dbgfs_pwdncfg(), mini_get_cam_pwdn_status(DEBUGFS_PWDN_CSI));
#ifdef DUMP_SCCTRL_ISP_REG
    mini_dump_scctrl_isp_reg();
#endif

	ispv1_release_resource();
}

/*
 **************************************************************************
 * FunctionName: ispv1_io_power_init;
 * Description : ldo register;
 * Input       : NA
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_io_power_init(char *ldo_name, u32 vol_min, u32 vol_max)
{
	int i = 0;
	struct regulator *regu = NULL;

	print_info("Enter %s, register LDO. dev[%p]", __func__, &(ispv1_io.pdev->dev));

	if (ldo_name == NULL) {
		print_error("%s: ldo_name is NULL", __func__);
		return -EINVAL;
	}

	/* get ldo */
	regu = regulator_get(&ispv1_io.pdev->dev, ldo_name);

	if (IS_ERR_OR_NULL(regu)) {
		print_error("%s: Could not get regulator : %s\n", __func__, ldo_name);
		goto fail;
	}

	if (ispv1_io.ldo[ispv1_io.ldo_count].regulator != NULL) {
		print_error("LDO too many!");
		regulator_put(regu);
		goto fail;
	}

	strncpy(ispv1_io.ldo[ispv1_io.ldo_count].name, ldo_name, strlen(ldo_name) + 1);

	ispv1_io.ldo[ispv1_io.ldo_count].regulator = regu;
	ispv1_io.ldo[ispv1_io.ldo_count].vol_min = vol_min;
	ispv1_io.ldo[ispv1_io.ldo_count].vol_max = vol_max;

	/* set audio_ldo eco mode */
	/*regulator_set_optimum_mode (regu, 5000); */

	ispv1_io.ldo_count++;

	return 0;

fail:
	for (i = 0; i < ispv1_io.ldo_count; i++) {
		if (ispv1_io.ldo[i].regulator != NULL) {
			regulator_put(ispv1_io.ldo[i].regulator);
			ispv1_io.ldo[i].regulator = NULL;
		}
	}
	ispv1_io.ldo_count = 0;

	return -EINVAL;
}

/*
 **************************************************************************
 * FunctionName: ispv1_io_power_deinit;
 * Description : ldo deregister;
 * Input       : NA
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_io_power_deinit(void)
{
	int i = 0;

	print_debug("enter %s ldo_count=%d", __func__, ispv1_io.ldo_count);

	for (i = 0; i < ispv1_io.ldo_count; i++) {
		if (ispv1_io.ldo[i].regulator != NULL) {
			regulator_put(ispv1_io.ldo[i].regulator);
			ispv1_io.ldo[i].regulator = NULL;
		}
	}
	ispv1_io.ldo_count = 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_io_power_sensor;
 * Description : ldo open or eco;
 * Input       : power_state: on/off
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_io_power_sensor(camera_power_state power_state, char *ldo_name)
{
	int i = 0;
	int ret = 0;
	u32 mode = REGULATOR_MODE_NORMAL;

	print_info("%s config LDO: ldo_name=%s ldo_count=%d power_state=%d",
		   __func__, ldo_name, ispv1_io.ldo_count, power_state);

	if (power_state == POWER_ON) {
		for (i = 0; i < ispv1_io.ldo_count; i++) {
			if (0 == strcmp(ldo_name, ispv1_io.ldo[i].name)) {
				ret |= regulator_set_mode(ispv1_io.ldo[i].regulator, mode);
				ret |= regulator_set_voltage(ispv1_io.ldo[i].regulator,
						ispv1_io.ldo[i].vol_min, ispv1_io.ldo[i].vol_max);
				/* enable ldo */
				ret = regulator_enable(ispv1_io.ldo[i].regulator);
				if (ret < 0) {
					print_error("%s: regulator enable failed\n", __func__);
					goto fail;
				}
				break;
			}
		}
	} else {
		for (i = 0; i < ispv1_io.ldo_count; i++) {
			if (0 == strcmp(ldo_name, ispv1_io.ldo[i].name)) {
				ret = regulator_disable(ispv1_io.ldo[i].regulator);
                if (ret < 0) {
                    print_error("%s: regulator disable failed\n", __func__);
                }
			}
		}
	}

	return ret;

fail:
	for (i = 0; i < ispv1_io.ldo_count; i++) {
		if (ispv1_io.ldo[i].regulator != NULL) {
			ret = regulator_disable(ispv1_io.ldo[i].regulator);
		}
        if (ret < 0) {
            print_error("%s: regulator disable failed\n", __func__);
        }
	}

	return -EINVAL;
}

/*
 **************************************************************************
 * FunctionName: ispv1_ioconfig;
 * Description : iomux config;
 * Input       : power_state: on/off
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_ioconfig(camera_power_state power_state, data_interface_t type)
{

	int ret = 0;
	print_info("%s camera iomux config", __func__);

#if 0
	if (power_state == POWER_ON) {
		ret = blockmux_set(ispv1_io.block_i2c, ispv1_io.block_conf_i2c, NORMAL);
		if (ret != 0) {
			print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);
		}

		ret |= blockmux_set(ispv1_io.block_rst, ispv1_io.block_conf_rst, NORMAL);
		if (ret != 0) {
			print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);
		}

		ret |= blockmux_set(ispv1_io.block_isp, ispv1_io.block_conf_isp, NORMAL);
		if (ret != 0) {
			print_error("%s: failed to set iomux isp to GPIO mode.\n", __func__);
		}

		if (type == DVP) {
			ret |= blockmux_set(ispv1_io.block_dvp, ispv1_io.block_conf_dvp, NORMAL);
			if (ret != 0) {
				print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);
			}
		}
	} else {
		ret = blockmux_set(ispv1_io.block_i2c, ispv1_io.block_conf_i2c, LOWPOWER);
		if (ret != 0) {
			print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);
		}

		ret |= blockmux_set(ispv1_io.block_rst, ispv1_io.block_conf_rst, LOWPOWER);
		if (ret != 0) {
			print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);
		}
		ret |= blockmux_set(ispv1_io.block_isp, ispv1_io.block_conf_isp, LOWPOWER);
		if (ret != 0) {
			print_error("%s: failed to set iomux isp to GPIO mode.\n", __func__);
		}

		if (type == DVP) {
			ret |= blockmux_set(ispv1_io.block_dvp, ispv1_io.block_conf_dvp, LOWPOWER);
			if (ret != 0) {
				print_error("%s: failed to set iomux dvp to normal mode.\n", __func__);

			}

		}

	}
#endif

#if defined(CONFIG_MACH_HI6620OEM)
	if (power_state == POWER_ON) {
		ret = blockmux_set(ispv1_io.block_mcam, ispv1_io.block_conf_mcam, NORMAL);
		if (ret != 0) {
			print_error("%s: failed to set iomux mcam to normal mode.\n", __func__);
		}

		ret = blockmux_set(ispv1_io.block_scam, ispv1_io.block_conf_scam, NORMAL);
		if (ret != 0) {
			print_error("%s: failed to set iomux scam to normal mode.\n", __func__);
		}
	} else {
		ret = blockmux_set(ispv1_io.block_mcam, ispv1_io.block_conf_mcam, LOWPOWER);
		if (ret != 0) {
			print_error("%s: failed to set iomux mcam to lowpower mode.\n", __func__);
		}

		ret = blockmux_set(ispv1_io.block_scam, ispv1_io.block_conf_scam, LOWPOWER);
		if (ret != 0) {
			print_error("%s: failed to set iomux scam to lowpower mode.\n", __func__);
		}
    }
#endif

	return ret;

}

/*
 **************************************************************************
 * FunctionName: ispv1_io_hw_init;
 * Description : ispio & csi init;
 * Input       : pdev: used to get resource
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_io_hw_init(struct platform_device *pdev)
{
	int ret = 0;

	print_debug("enter %s, pdev[%p]", __func__, pdev);

	ispv1_io_set_default();

	INIT_WORK(&ispv1_io.mipi_csi_exception_work, mipi_csi_exception_handler);
	ispv1_io.mipi_csi_exception_already_report = false;

	ispv1_io.pdev = pdev;

#if 0 /* k3 code */
	ret = ispv1_get_iomux(IOMUX_DVP_NAME, &ispv1_io.block_dvp, &ispv1_io.block_conf_dvp);
	ret |= ispv1_get_iomux(IOMUX_ISP_NAME, &ispv1_io.block_isp, &ispv1_io.block_conf_isp);
	ret |= ispv1_get_iomux(IOMUX_RST_NAME, &ispv1_io.block_rst, &ispv1_io.block_conf_rst);
	ret |= ispv1_get_iomux(IOMUX_I2C_NAME, &ispv1_io.block_i2c, &ispv1_io.block_conf_i2c);
#endif
#if defined(CONFIG_MACH_HI6620OEM)
	ret = ispv1_get_iomux(IOMUX_MCAMERA, &ispv1_io.block_mcam, &ispv1_io.block_conf_mcam);
	ret = ispv1_get_iomux(IOMUX_SCAMERA, &ispv1_io.block_scam, &ispv1_io.block_conf_scam);
#endif

	return ret;
}

/*
 **************************************************************************
 * FunctionName: ispv1_io_hw_deinit;
 * Description : ispio & csi deinit;
 * Input       : NA
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int ispv1_io_hw_deinit(void)
{
	print_info("Enter %s", __func__);

	flush_work(&ispv1_io.mipi_csi_exception_work);

	return 0;
}

/*
 **************************************************************************
 * FunctionName: ispv1_io_set_default;
 * Description : Set default value of ispio_ctl struct;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void ispv1_io_set_default(void)
{

	ispv1_io_ctl.power_init 		= ispv1_io_power_init;
	ispv1_io_ctl.power_deinit 		= ispv1_io_power_deinit;
	ispv1_io_ctl.power_sensor 		= ispv1_io_power_sensor;
	ispv1_io_ctl.ispio_hw_init 		= ispv1_io_hw_init;
	ispv1_io_ctl.ispio_hw_deinit 		= ispv1_io_hw_deinit;
	ispv1_io_ctl.deinit_csi 		= ispv1_deinit_csi;
	ispv1_io_ctl.init_csi 			= ispv1_init_csi;
	ispv1_io_ctl.ioconfig 			= ispv1_ioconfig;

	memset(&ispv1_io, 0, sizeof(ispv1_io));
}

mini_ispio_controller *mini_get_ispio_controller(void)
{

	/*
	 * we need to set ispv1_io_hw_init field first,
	 * because it is an invalid value at the
	 * first calling of this function.
	 */
	ispv1_io_ctl.ispio_hw_init = ispv1_io_hw_init;

	return &ispv1_io_ctl;

}

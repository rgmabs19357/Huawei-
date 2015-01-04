/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_balong_ddr3cap_udp_6361s_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_BALONG_DDR3CAP_UDP_6361S_IOMUX_BLOCKS_H__
#define __HI6620_BALONG_DDR3CAP_UDP_6361S_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_balong_ddr3cap_udp_6361s_iomux_pins.h"
#include <hsad/config_interface.h>

extern struct iomux_ops iomux_block_ops;

#define IOMUX_BLOCK(_iomux_block, _block_name, _block_func, _pins)   \
struct iomux_block _iomux_block = {\
    .block_name  = _block_name,\
    .block_func   =  _block_func,\
    .pins = _pins,\
    .ops = &iomux_block_ops,\
    .init = 0, \
};

/*TODO:every config of blocks*/
#define BLOCK_CONFIG(_name, _block, _configarray) \
{\
    .name = _name,\
    .block = _block,\
    .config_array = _configarray,\
},


/*charger pins */
static struct  iomux_pin *charger_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_4_0_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_1_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_balong_ddr3cap_udp_6361s, "block_charger", NORMAL, charger_pins_balong_ddr3cap_udp_6361s)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {charger_func_normal_balong_ddr3cap_udp_6361s, charger_pullud_normal_balong_ddr3cap_udp_6361s, charger_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {charger_func_lowpower_balong_ddr3cap_udp_6361s, charger_pullud_lowpower_balong_ddr3cap_udp_6361s, charger_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*flash pins */
static struct  iomux_pin *flash_pins_balong_ddr3cap_udp_6361s[] = {
    &ISP_GPIO5_BALONG_DDR3CAP_UDP_6361S, &ISP_STROBE1_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_0_BALONG_DDR3CAP_UDP_6361S, &ISP_STROBE0_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_balong_ddr3cap_udp_6361s, "block_flash", NORMAL, flash_pins_balong_ddr3cap_udp_6361s)



/*FLASH*/

static enum lowlayer_func flash_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {flash_func_normal_balong_ddr3cap_udp_6361s, flash_pullud_normal_balong_ddr3cap_udp_6361s, flash_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {flash_func_lowpower_balong_ddr3cap_udp_6361s, flash_pullud_lowpower_balong_ddr3cap_udp_6361s, flash_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*bt pins */
static struct  iomux_pin *bt_pins_balong_ddr3cap_udp_6361s[] = {
    &UART4_CTS_N_BALONG_DDR3CAP_UDP_6361S, &UART4_RTS_N_BALONG_DDR3CAP_UDP_6361S, &UART4_RXD_BALONG_DDR3CAP_UDP_6361S, &UART4_TXD_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_5_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_7_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_balong_ddr3cap_udp_6361s, "block_bt", NORMAL, bt_pins_balong_ddr3cap_udp_6361s)



/*BT*/

static enum lowlayer_func bt_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {bt_func_normal_balong_ddr3cap_udp_6361s, bt_pullud_normal_balong_ddr3cap_udp_6361s, bt_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {bt_func_lowpower_balong_ddr3cap_udp_6361s, bt_pullud_lowpower_balong_ddr3cap_udp_6361s, bt_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_balong_ddr3cap_udp_6361s[] = {
    &ISP_GPIO1_BALONG_DDR3CAP_UDP_6361S, &ISP_GPIO4_BALONG_DDR3CAP_UDP_6361S, &ISP_RESETB1_BALONG_DDR3CAP_UDP_6361S, &ISP_CCLK1_BALONG_DDR3CAP_UDP_6361S, &ISP_SDA1_BALONG_DDR3CAP_UDP_6361S, &ISP_SCL1_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_balong_ddr3cap_udp_6361s, "block_scamera", NORMAL, scamera_pins_balong_ddr3cap_udp_6361s)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {scamera_func_normal_balong_ddr3cap_udp_6361s, scamera_pullud_normal_balong_ddr3cap_udp_6361s, scamera_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {scamera_func_lowpower_balong_ddr3cap_udp_6361s, scamera_pullud_lowpower_balong_ddr3cap_udp_6361s, scamera_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*codec pins */
static struct  iomux_pin *codec_pins_balong_ddr3cap_udp_6361s[] = {
    &PCM1_XCLK_BALONG_DDR3CAP_UDP_6361S, &PCM1_XFS_BALONG_DDR3CAP_UDP_6361S, &PCM1_DI_BALONG_DDR3CAP_UDP_6361S, &PCM1_DO_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_balong_ddr3cap_udp_6361s, "block_codec", NORMAL, codec_pins_balong_ddr3cap_udp_6361s)



/*CODEC*/

static enum lowlayer_func codec_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {codec_func_normal_balong_ddr3cap_udp_6361s, codec_pullud_normal_balong_ddr3cap_udp_6361s, codec_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {codec_func_lowpower_balong_ddr3cap_udp_6361s, codec_pullud_lowpower_balong_ddr3cap_udp_6361s, codec_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_balong_ddr3cap_udp_6361s[] = {
    &UART1_TXD_BALONG_DDR3CAP_UDP_6361S, &UART2_RXD_BALONG_DDR3CAP_UDP_6361S, &UART2_TXD_BALONG_DDR3CAP_UDP_6361S, &I2S_XCLK_BALONG_DDR3CAP_UDP_6361S, &I2S_XFS_BALONG_DDR3CAP_UDP_6361S, &I2S_DI_BALONG_DDR3CAP_UDP_6361S, &I2S_DO_BALONG_DDR3CAP_UDP_6361S, &PCM0_XCLK_BALONG_DDR3CAP_UDP_6361S, &PCM0_XFS_BALONG_DDR3CAP_UDP_6361S, &PCM0_DI_BALONG_DDR3CAP_UDP_6361S, &PCM0_DO_BALONG_DDR3CAP_UDP_6361S, &TS_ERR_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_balong_ddr3cap_udp_6361s, "block_es305", NORMAL, es305_pins_balong_ddr3cap_udp_6361s)



/*ES305*/

static enum lowlayer_func es305_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {es305_func_normal_balong_ddr3cap_udp_6361s, es305_pullud_normal_balong_ddr3cap_udp_6361s, es305_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {es305_func_lowpower_balong_ddr3cap_udp_6361s, es305_pullud_lowpower_balong_ddr3cap_udp_6361s, es305_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_balong_ddr3cap_udp_6361s[] = {
    &HKADC_SSI_BALONG_DDR3CAP_UDP_6361S, &AUX_SSI0_BALONG_DDR3CAP_UDP_6361S, &AUX_SSI1_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_0_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_balong_ddr3cap_udp_6361s, "block_pmu", NORMAL, pmu_pins_balong_ddr3cap_udp_6361s)



/*PMU*/

static enum lowlayer_func pmu_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_balong_ddr3cap_udp_6361s[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {pmu_func_normal_balong_ddr3cap_udp_6361s, pmu_pullud_normal_balong_ddr3cap_udp_6361s, pmu_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {pmu_func_lowpower_balong_ddr3cap_udp_6361s, pmu_pullud_lowpower_balong_ddr3cap_udp_6361s, pmu_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_balong_ddr3cap_udp_6361s[] = {
    &EMMC_CLK_BALONG_DDR3CAP_UDP_6361S, &EMMC_CMD_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA0_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA1_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA2_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA3_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA4_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA5_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA6_BALONG_DDR3CAP_UDP_6361S, &EMMC_DATA7_BALONG_DDR3CAP_UDP_6361S, &GPIO_2_3_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_balong_ddr3cap_udp_6361s, "block_emmc", NORMAL, emmc_pins_balong_ddr3cap_udp_6361s)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config emmc_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {emmc_func_normal_balong_ddr3cap_udp_6361s, emmc_pullud_normal_balong_ddr3cap_udp_6361s, emmc_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {emmc_func_lowpower_balong_ddr3cap_udp_6361s, emmc_pullud_lowpower_balong_ddr3cap_udp_6361s, emmc_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*rf pins */
static struct  iomux_pin *rf_pins_balong_ddr3cap_udp_6361s[] = {
    &RF_TCVR_ON0_BALONG_DDR3CAP_UDP_6361S, &RF_TCVR_ON1_BALONG_DDR3CAP_UDP_6361S, &RF_TX_EN0_BALONG_DDR3CAP_UDP_6361S, &RF_TX_EN1_BALONG_DDR3CAP_UDP_6361S, &RF_MIPI_CLK1_BALONG_DDR3CAP_UDP_6361S, &RF_MIPI_DATA1_BALONG_DDR3CAP_UDP_6361S, &RF_SSI0_BALONG_DDR3CAP_UDP_6361S, &RF_SSI1_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_2_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_3_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_4_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_5_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_6_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_7_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_8_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_9_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_10_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_11_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_12_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_13_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_14_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_15_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_16_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_17_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_18_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_19_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_20_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_21_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_22_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_23_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_24_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_25_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_26_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_27_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_28_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_29_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_30_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_balong_ddr3cap_udp_6361s, "block_rf", NORMAL, rf_pins_balong_ddr3cap_udp_6361s)



/*RF*/

static enum lowlayer_func rf_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {rf_func_normal_balong_ddr3cap_udp_6361s, rf_pullud_normal_balong_ddr3cap_udp_6361s, rf_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {rf_func_lowpower_balong_ddr3cap_udp_6361s, rf_pullud_lowpower_balong_ddr3cap_udp_6361s, rf_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*tp pins */
static struct  iomux_pin *tp_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_18_7_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_balong_ddr3cap_udp_6361s, "block_tp", NORMAL, tp_pins_balong_ddr3cap_udp_6361s)



/*TP*/

static enum lowlayer_func tp_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {tp_func_normal_balong_ddr3cap_udp_6361s, tp_pullud_normal_balong_ddr3cap_udp_6361s, tp_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {tp_func_lowpower_balong_ddr3cap_udp_6361s, tp_pullud_lowpower_balong_ddr3cap_udp_6361s, tp_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*exphp pins */
static struct  iomux_pin *exphp_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_5_1_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: exphp*/
IOMUX_BLOCK(block_exphp_balong_ddr3cap_udp_6361s, "block_exphp", NORMAL, exphp_pins_balong_ddr3cap_udp_6361s)



/*EXPHP*/

static enum lowlayer_func exphp_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func exphp_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static struct block_config exphp_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {exphp_func_normal_balong_ddr3cap_udp_6361s, exphp_pullud_normal_balong_ddr3cap_udp_6361s, exphp_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {exphp_func_lowpower_balong_ddr3cap_udp_6361s, exphp_pullud_lowpower_balong_ddr3cap_udp_6361s, exphp_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*switch pins */
static struct  iomux_pin *switch_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_6_2_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_3_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_balong_ddr3cap_udp_6361s, "block_switch", NORMAL, switch_pins_balong_ddr3cap_udp_6361s)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {switch_func_normal_balong_ddr3cap_udp_6361s, switch_pullud_normal_balong_ddr3cap_udp_6361s, switch_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {switch_func_lowpower_balong_ddr3cap_udp_6361s, switch_pullud_lowpower_balong_ddr3cap_udp_6361s, switch_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*spk pins */
static struct  iomux_pin *spk_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_7_4_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: spk*/
IOMUX_BLOCK(block_spk_balong_ddr3cap_udp_6361s, "block_spk", NORMAL, spk_pins_balong_ddr3cap_udp_6361s)



/*SPK*/

static enum lowlayer_func spk_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func spk_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0,  -INVALID,};

static struct block_config spk_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {spk_func_normal_balong_ddr3cap_udp_6361s, spk_pullud_normal_balong_ddr3cap_udp_6361s, spk_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {spk_func_lowpower_balong_ddr3cap_udp_6361s, spk_pullud_lowpower_balong_ddr3cap_udp_6361s, spk_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_balong_ddr3cap_udp_6361s[] = {
    &RF_MIPI_CLK0_BALONG_DDR3CAP_UDP_6361S, &RF_MIPI_DATA0_BALONG_DDR3CAP_UDP_6361S, &APT_PDM0_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_balong_ddr3cap_udp_6361s, "block_rfpmu", NORMAL, rfpmu_pins_balong_ddr3cap_udp_6361s)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {rfpmu_func_normal_balong_ddr3cap_udp_6361s, rfpmu_pullud_normal_balong_ddr3cap_udp_6361s, rfpmu_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {rfpmu_func_lowpower_balong_ddr3cap_udp_6361s, rfpmu_pullud_lowpower_balong_ddr3cap_udp_6361s, rfpmu_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_balong_ddr3cap_udp_6361s[] = {
    &I2C3_SCL_BALONG_DDR3CAP_UDP_6361S, &I2C3_SDA_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_balong_ddr3cap_udp_6361s, "block_i2c3", NORMAL, i2c3_pins_balong_ddr3cap_udp_6361s)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {i2c3_func_normal_balong_ddr3cap_udp_6361s, i2c3_pullud_normal_balong_ddr3cap_udp_6361s, i2c3_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {i2c3_func_lowpower_balong_ddr3cap_udp_6361s, i2c3_pullud_lowpower_balong_ddr3cap_udp_6361s, i2c3_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_6_5_BALONG_DDR3CAP_UDP_6361S, &GPIO_6_6_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_3_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_balong_ddr3cap_udp_6361s, "block_nfc", NORMAL, nfc_pins_balong_ddr3cap_udp_6361s)



/*NFC*/

static enum lowlayer_func nfc_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC6, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config nfc_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {nfc_func_normal_balong_ddr3cap_udp_6361s, nfc_pullud_normal_balong_ddr3cap_udp_6361s, nfc_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {nfc_func_lowpower_balong_ddr3cap_udp_6361s, nfc_pullud_lowpower_balong_ddr3cap_udp_6361s, nfc_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_balong_ddr3cap_udp_6361s[] = {
    &USIM1_CLK_BALONG_DDR3CAP_UDP_6361S, &USIM1_DATA_BALONG_DDR3CAP_UDP_6361S, &USIM1_RST_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_balong_ddr3cap_udp_6361s, "block_usim1", NORMAL, usim1_pins_balong_ddr3cap_udp_6361s)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {usim1_func_normal_balong_ddr3cap_udp_6361s, usim1_pullud_normal_balong_ddr3cap_udp_6361s, usim1_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {usim1_func_lowpower_balong_ddr3cap_udp_6361s, usim1_pullud_lowpower_balong_ddr3cap_udp_6361s, usim1_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_balong_ddr3cap_udp_6361s[] = {
    &USIM0_CLK_BALONG_DDR3CAP_UDP_6361S, &USIM0_DATA_BALONG_DDR3CAP_UDP_6361S, &USIM0_RST_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_balong_ddr3cap_udp_6361s, "block_usim0", NORMAL, usim0_pins_balong_ddr3cap_udp_6361s)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {usim0_func_normal_balong_ddr3cap_udp_6361s, usim0_pullud_normal_balong_ddr3cap_udp_6361s, usim0_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {usim0_func_lowpower_balong_ddr3cap_udp_6361s, usim0_pullud_lowpower_balong_ddr3cap_udp_6361s, usim0_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_balong_ddr3cap_udp_6361s[] = {
    &ISP_GPIO0_BALONG_DDR3CAP_UDP_6361S, &ISP_GPIO2_BALONG_DDR3CAP_UDP_6361S, &ISP_GPIO3_BALONG_DDR3CAP_UDP_6361S, &ISP_RESETB0_BALONG_DDR3CAP_UDP_6361S, &ISP_CCLK0_BALONG_DDR3CAP_UDP_6361S, &ISP_SDA0_BALONG_DDR3CAP_UDP_6361S, &ISP_SCL0_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_balong_ddr3cap_udp_6361s, "block_mcamera", NORMAL, mcamera_pins_balong_ddr3cap_udp_6361s)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {mcamera_func_normal_balong_ddr3cap_udp_6361s, mcamera_pullud_normal_balong_ddr3cap_udp_6361s, mcamera_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {mcamera_func_lowpower_balong_ddr3cap_udp_6361s, mcamera_pullud_lowpower_balong_ddr3cap_udp_6361s, mcamera_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*led pins */
static struct  iomux_pin *led_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_6_7_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_0_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_1_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_2_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: led*/
IOMUX_BLOCK(block_led_balong_ddr3cap_udp_6361s, "block_led", NORMAL, led_pins_balong_ddr3cap_udp_6361s)



/*LED*/

static enum lowlayer_func led_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func led_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config led_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {led_func_normal_balong_ddr3cap_udp_6361s, led_pullud_normal_balong_ddr3cap_udp_6361s, led_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {led_func_lowpower_balong_ddr3cap_udp_6361s, led_pullud_lowpower_balong_ddr3cap_udp_6361s, led_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_balong_ddr3cap_udp_6361s[] = {
    &I2C0_SCL_BALONG_DDR3CAP_UDP_6361S, &I2C0_SDA_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_balong_ddr3cap_udp_6361s, "block_i2c0", NORMAL, i2c0_pins_balong_ddr3cap_udp_6361s)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {i2c0_func_normal_balong_ddr3cap_udp_6361s, i2c0_pullud_normal_balong_ddr3cap_udp_6361s, i2c0_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {i2c0_func_lowpower_balong_ddr3cap_udp_6361s, i2c0_pullud_lowpower_balong_ddr3cap_udp_6361s, i2c0_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_balong_ddr3cap_udp_6361s[] = {
    &I2C1_SCL_BALONG_DDR3CAP_UDP_6361S, &I2C1_SDA_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_balong_ddr3cap_udp_6361s, "block_i2c1", NORMAL, i2c1_pins_balong_ddr3cap_udp_6361s)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {i2c1_func_normal_balong_ddr3cap_udp_6361s, i2c1_pullud_normal_balong_ddr3cap_udp_6361s, i2c1_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {i2c1_func_lowpower_balong_ddr3cap_udp_6361s, i2c1_pullud_lowpower_balong_ddr3cap_udp_6361s, i2c1_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_balong_ddr3cap_udp_6361s[] = {
    &I2C2_SCL_BALONG_DDR3CAP_UDP_6361S, &I2C2_SDA_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_balong_ddr3cap_udp_6361s, "block_i2c2", NORMAL, i2c2_pins_balong_ddr3cap_udp_6361s)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {i2c2_func_normal_balong_ddr3cap_udp_6361s, i2c2_pullud_normal_balong_ddr3cap_udp_6361s, i2c2_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {i2c2_func_lowpower_balong_ddr3cap_udp_6361s, i2c2_pullud_lowpower_balong_ddr3cap_udp_6361s, i2c2_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*gps pins */
static struct  iomux_pin *gps_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_6_1_BALONG_DDR3CAP_UDP_6361S, &RF_GPIO_1_BALONG_DDR3CAP_UDP_6361S, &UART3_CTS_N_BALONG_DDR3CAP_UDP_6361S, &UART3_RTS_N_BALONG_DDR3CAP_UDP_6361S, &UART3_RXD_BALONG_DDR3CAP_UDP_6361S, &UART3_TXD_BALONG_DDR3CAP_UDP_6361S, &GPS_CLK_BALONG_DDR3CAP_UDP_6361S, &GPIO_6_3_BALONG_DDR3CAP_UDP_6361S, &GPIO_6_4_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_balong_ddr3cap_udp_6361s, "block_gps", NORMAL, gps_pins_balong_ddr3cap_udp_6361s)



/*GPS*/

static enum lowlayer_func gps_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC6,  -INVALID,};
static enum pull_updown gps_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {gps_func_normal_balong_ddr3cap_udp_6361s, gps_pullud_normal_balong_ddr3cap_udp_6361s, gps_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {gps_func_lowpower_balong_ddr3cap_udp_6361s, gps_pullud_lowpower_balong_ddr3cap_udp_6361s, gps_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_balong_ddr3cap_udp_6361s[] = {
    &TCXO0_AFC_BALONG_DDR3CAP_UDP_6361S, &TCXO1_AFC_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_balong_ddr3cap_udp_6361s, "block_tcxo", NORMAL, tcxo_pins_balong_ddr3cap_udp_6361s)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {tcxo_func_normal_balong_ddr3cap_udp_6361s, tcxo_pullud_normal_balong_ddr3cap_udp_6361s, tcxo_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {tcxo_func_lowpower_balong_ddr3cap_udp_6361s, tcxo_pullud_lowpower_balong_ddr3cap_udp_6361s, tcxo_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_7_5_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_6_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_balong_ddr3cap_udp_6361s, "block_rfant", NORMAL, rfant_pins_balong_ddr3cap_udp_6361s)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_balong_ddr3cap_udp_6361s[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfant_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {rfant_func_normal_balong_ddr3cap_udp_6361s, rfant_pullud_normal_balong_ddr3cap_udp_6361s, rfant_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {rfant_func_lowpower_balong_ddr3cap_udp_6361s, rfant_pullud_lowpower_balong_ddr3cap_udp_6361s, rfant_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_2_2_BALONG_DDR3CAP_UDP_6361S, &SDIO_DATA3_BALONG_DDR3CAP_UDP_6361S, &SDIO_DATA2_BALONG_DDR3CAP_UDP_6361S, &SDIO_DATA1_BALONG_DDR3CAP_UDP_6361S, &SDIO_DATA0_BALONG_DDR3CAP_UDP_6361S, &SDIO_CMD_BALONG_DDR3CAP_UDP_6361S, &SDIO_CLK_BALONG_DDR3CAP_UDP_6361S, &GPIO_1_4_BALONG_DDR3CAP_UDP_6361S, &GPIO_1_5_BALONG_DDR3CAP_UDP_6361S, &GPIO_1_6_BALONG_DDR3CAP_UDP_6361S, &GPIO_1_7_BALONG_DDR3CAP_UDP_6361S, &GPIO_2_0_BALONG_DDR3CAP_UDP_6361S, &GPIO_2_1_BALONG_DDR3CAP_UDP_6361S, &GPIO_6_0_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_balong_ddr3cap_udp_6361s, "block_wifi", NORMAL, wifi_pins_balong_ddr3cap_udp_6361s)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config wifi_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {wifi_func_normal_balong_ddr3cap_udp_6361s, wifi_pullud_normal_balong_ddr3cap_udp_6361s, wifi_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {wifi_func_lowpower_balong_ddr3cap_udp_6361s, wifi_pullud_lowpower_balong_ddr3cap_udp_6361s, wifi_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*boot pins */
static struct  iomux_pin *boot_pins_balong_ddr3cap_udp_6361s[] = {
    &BOOT_SEL_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_2_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_balong_ddr3cap_udp_6361s, "block_boot", NORMAL, boot_pins_balong_ddr3cap_udp_6361s)



/*BOOT*/

static enum lowlayer_func boot_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_normal_balong_ddr3cap_udp_6361s[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {boot_func_normal_balong_ddr3cap_udp_6361s, boot_pullud_normal_balong_ddr3cap_udp_6361s, boot_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {boot_func_lowpower_balong_ddr3cap_udp_6361s, boot_pullud_lowpower_balong_ddr3cap_udp_6361s, boot_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_balong_ddr3cap_udp_6361s[] = {
    &PWM_OUT1_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_6_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_7_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_4_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_5_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_balong_ddr3cap_udp_6361s, "block_lcd", NORMAL, lcd_pins_balong_ddr3cap_udp_6361s)



/*LCD*/

static enum lowlayer_func lcd_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {lcd_func_normal_balong_ddr3cap_udp_6361s, lcd_pullud_normal_balong_ddr3cap_udp_6361s, lcd_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {lcd_func_lowpower_balong_ddr3cap_udp_6361s, lcd_pullud_lowpower_balong_ddr3cap_udp_6361s, lcd_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*key pins */
static struct  iomux_pin *key_pins_balong_ddr3cap_udp_6361s[] = {
    &GPIO_4_2_BALONG_DDR3CAP_UDP_6361S, &GPIO_4_3_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_balong_ddr3cap_udp_6361s, "block_key", NORMAL, key_pins_balong_ddr3cap_udp_6361s)



/*KEY*/

static enum lowlayer_func key_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_balong_ddr3cap_udp_6361s[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {key_func_normal_balong_ddr3cap_udp_6361s, key_pullud_normal_balong_ddr3cap_udp_6361s, key_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {key_func_lowpower_balong_ddr3cap_udp_6361s, key_pullud_lowpower_balong_ddr3cap_udp_6361s, key_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*test pins */
static struct  iomux_pin *test_pins_balong_ddr3cap_udp_6361s[] = {
    &UART0_RXD_BALONG_DDR3CAP_UDP_6361S, &UART0_TXD_BALONG_DDR3CAP_UDP_6361S, &GPIO_7_7_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_0_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_1_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_2_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_balong_ddr3cap_udp_6361s, "block_test", NORMAL, test_pins_balong_ddr3cap_udp_6361s)



/*TEST*/

static enum lowlayer_func test_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6,  -INVALID,};
static enum pull_updown test_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6,  -INVALID,};
static enum pull_updown test_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {test_func_normal_balong_ddr3cap_udp_6361s, test_pullud_normal_balong_ddr3cap_udp_6361s, test_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {test_func_lowpower_balong_ddr3cap_udp_6361s, test_pullud_lowpower_balong_ddr3cap_udp_6361s, test_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*cdma pins */
static struct  iomux_pin *cdma_pins_balong_ddr3cap_udp_6361s[] = {
    &UART1_RTS_N_BALONG_DDR3CAP_UDP_6361S, &UART1_RXD_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_6_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_4_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_5_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_6_BALONG_DDR3CAP_UDP_6361S, &GPIO_5_7_BALONG_DDR3CAP_UDP_6361S, &UART1_CTS_N_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_3_BALONG_DDR3CAP_UDP_6361S, &GPIO_15_4_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: cdma*/
IOMUX_BLOCK(block_cdma_balong_ddr3cap_udp_6361s, "block_cdma", NORMAL, cdma_pins_balong_ddr3cap_udp_6361s)



/*CDMA*/

static enum lowlayer_func cdma_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func cdma_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config cdma_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {cdma_func_normal_balong_ddr3cap_udp_6361s, cdma_pullud_normal_balong_ddr3cap_udp_6361s, cdma_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {cdma_func_lowpower_balong_ddr3cap_udp_6361s, cdma_pullud_lowpower_balong_ddr3cap_udp_6361s, cdma_drv_lowpower_balong_ddr3cap_udp_6361s},

};

/*sd pins */
static struct  iomux_pin *sd_pins_balong_ddr3cap_udp_6361s[] = {
    &SD_CLK_BALONG_DDR3CAP_UDP_6361S, &SD_CMD_BALONG_DDR3CAP_UDP_6361S, &SD_DATA0_BALONG_DDR3CAP_UDP_6361S, &SD_DATA1_BALONG_DDR3CAP_UDP_6361S, &SD_DATA2_BALONG_DDR3CAP_UDP_6361S, &SD_DATA3_BALONG_DDR3CAP_UDP_6361S,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_balong_ddr3cap_udp_6361s, "block_sd", NORMAL, sd_pins_balong_ddr3cap_udp_6361s)



/*SD*/

static enum lowlayer_func sd_func_normal_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_balong_ddr3cap_udp_6361s[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_balong_ddr3cap_udp_6361s[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_balong_ddr3cap_udp_6361s[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_balong_ddr3cap_udp_6361s[] = {
    [NORMAL] = {sd_func_normal_balong_ddr3cap_udp_6361s, sd_pullud_normal_balong_ddr3cap_udp_6361s, sd_drv_normal_balong_ddr3cap_udp_6361s},
    [LOWPOWER] = {sd_func_lowpower_balong_ddr3cap_udp_6361s, sd_pullud_lowpower_balong_ddr3cap_udp_6361s, sd_drv_lowpower_balong_ddr3cap_udp_6361s},

};

struct iomux_block_table block_config_table_balong_ddr3cap_udp_6361s[] = {
    BLOCK_CONFIG("block_charger", &block_charger_balong_ddr3cap_udp_6361s, charger_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_flash", &block_flash_balong_ddr3cap_udp_6361s, flash_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_bt", &block_bt_balong_ddr3cap_udp_6361s, bt_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_scamera", &block_scamera_balong_ddr3cap_udp_6361s, scamera_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_codec", &block_codec_balong_ddr3cap_udp_6361s, codec_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_es305", &block_es305_balong_ddr3cap_udp_6361s, es305_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_pmu", &block_pmu_balong_ddr3cap_udp_6361s, pmu_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_emmc", &block_emmc_balong_ddr3cap_udp_6361s, emmc_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_rf", &block_rf_balong_ddr3cap_udp_6361s, rf_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_tp", &block_tp_balong_ddr3cap_udp_6361s, tp_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_exphp", &block_exphp_balong_ddr3cap_udp_6361s, exphp_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_switch", &block_switch_balong_ddr3cap_udp_6361s, switch_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_spk", &block_spk_balong_ddr3cap_udp_6361s, spk_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_balong_ddr3cap_udp_6361s, rfpmu_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_balong_ddr3cap_udp_6361s, i2c3_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_nfc", &block_nfc_balong_ddr3cap_udp_6361s, nfc_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_usim1", &block_usim1_balong_ddr3cap_udp_6361s, usim1_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_usim0", &block_usim0_balong_ddr3cap_udp_6361s, usim0_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_balong_ddr3cap_udp_6361s, mcamera_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_led", &block_led_balong_ddr3cap_udp_6361s, led_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_balong_ddr3cap_udp_6361s, i2c0_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_balong_ddr3cap_udp_6361s, i2c1_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_balong_ddr3cap_udp_6361s, i2c2_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_gps", &block_gps_balong_ddr3cap_udp_6361s, gps_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_balong_ddr3cap_udp_6361s, tcxo_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_rfant", &block_rfant_balong_ddr3cap_udp_6361s, rfant_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_wifi", &block_wifi_balong_ddr3cap_udp_6361s, wifi_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_boot", &block_boot_balong_ddr3cap_udp_6361s, boot_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_lcd", &block_lcd_balong_ddr3cap_udp_6361s, lcd_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_key", &block_key_balong_ddr3cap_udp_6361s, key_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_test", &block_test_balong_ddr3cap_udp_6361s, test_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_cdma", &block_cdma_balong_ddr3cap_udp_6361s, cdma_config_balong_ddr3cap_udp_6361s)
    BLOCK_CONFIG("block_sd", &block_sd_balong_ddr3cap_udp_6361s, sd_config_balong_ddr3cap_udp_6361s)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
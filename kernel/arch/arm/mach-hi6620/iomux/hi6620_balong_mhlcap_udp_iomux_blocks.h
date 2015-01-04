/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_balong_mhlcap_udp_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_BALONG_MHLCAP_UDP_IOMUX_BLOCKS_H__
#define __HI6620_BALONG_MHLCAP_UDP_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_balong_mhlcap_udp_iomux_pins.h"
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


/*acc pins */
static struct  iomux_pin *acc_pins_balong_mhlcap_udp[] = {
    &GPIO_15_1_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: acc*/
IOMUX_BLOCK(block_acc_balong_mhlcap_udp, "block_acc", NORMAL, acc_pins_balong_mhlcap_udp)



/*ACC*/

static enum lowlayer_func acc_func_normal_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown acc_pullud_normal_balong_mhlcap_udp[] = {PULLDOWN,  -INVALID,};
static enum drive_strength acc_drv_normal_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func acc_func_lowpower_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown acc_pullud_lowpower_balong_mhlcap_udp[] = {PULLDOWN,  -INVALID,};
static enum drive_strength acc_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static struct block_config acc_config_balong_mhlcap_udp[] = {
    [NORMAL] = {acc_func_normal_balong_mhlcap_udp, acc_pullud_normal_balong_mhlcap_udp, acc_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {acc_func_lowpower_balong_mhlcap_udp, acc_pullud_lowpower_balong_mhlcap_udp, acc_drv_lowpower_balong_mhlcap_udp},

};

/*charger pins */
static struct  iomux_pin *charger_pins_balong_mhlcap_udp[] = {
    &GPIO_4_0_BALONG_MHLCAP_UDP, &GPIO_4_1_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_balong_mhlcap_udp, "block_charger", NORMAL, charger_pins_balong_mhlcap_udp)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_balong_mhlcap_udp[] = {
    [NORMAL] = {charger_func_normal_balong_mhlcap_udp, charger_pullud_normal_balong_mhlcap_udp, charger_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {charger_func_lowpower_balong_mhlcap_udp, charger_pullud_lowpower_balong_mhlcap_udp, charger_drv_lowpower_balong_mhlcap_udp},

};

/*flash pins */
static struct  iomux_pin *flash_pins_balong_mhlcap_udp[] = {
    &ISP_GPIO5_BALONG_MHLCAP_UDP, &ISP_STROBE1_BALONG_MHLCAP_UDP, &RF_GPIO_0_BALONG_MHLCAP_UDP, &ISP_STROBE0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_balong_mhlcap_udp, "block_flash", NORMAL, flash_pins_balong_mhlcap_udp)



/*FLASH*/

static enum lowlayer_func flash_func_normal_balong_mhlcap_udp[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_balong_mhlcap_udp[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_balong_mhlcap_udp[] = {
    [NORMAL] = {flash_func_normal_balong_mhlcap_udp, flash_pullud_normal_balong_mhlcap_udp, flash_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {flash_func_lowpower_balong_mhlcap_udp, flash_pullud_lowpower_balong_mhlcap_udp, flash_drv_lowpower_balong_mhlcap_udp},

};

/*bt pins */
static struct  iomux_pin *bt_pins_balong_mhlcap_udp[] = {
    &UART4_CTS_N_BALONG_MHLCAP_UDP, &UART4_RTS_N_BALONG_MHLCAP_UDP, &UART4_RXD_BALONG_MHLCAP_UDP, &UART4_TXD_BALONG_MHLCAP_UDP, &GPIO_15_5_BALONG_MHLCAP_UDP, &GPIO_15_7_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_balong_mhlcap_udp, "block_bt", NORMAL, bt_pins_balong_mhlcap_udp)



/*BT*/

static enum lowlayer_func bt_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_balong_mhlcap_udp[] = {
    [NORMAL] = {bt_func_normal_balong_mhlcap_udp, bt_pullud_normal_balong_mhlcap_udp, bt_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {bt_func_lowpower_balong_mhlcap_udp, bt_pullud_lowpower_balong_mhlcap_udp, bt_drv_lowpower_balong_mhlcap_udp},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_balong_mhlcap_udp[] = {
    &ISP_GPIO1_BALONG_MHLCAP_UDP, &ISP_GPIO4_BALONG_MHLCAP_UDP, &ISP_RESETB1_BALONG_MHLCAP_UDP, &ISP_CCLK1_BALONG_MHLCAP_UDP, &ISP_SDA1_BALONG_MHLCAP_UDP, &ISP_SCL1_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_balong_mhlcap_udp, "block_scamera", NORMAL, scamera_pins_balong_mhlcap_udp)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_balong_mhlcap_udp[] = {
    [NORMAL] = {scamera_func_normal_balong_mhlcap_udp, scamera_pullud_normal_balong_mhlcap_udp, scamera_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {scamera_func_lowpower_balong_mhlcap_udp, scamera_pullud_lowpower_balong_mhlcap_udp, scamera_drv_lowpower_balong_mhlcap_udp},

};

/*codec pins */
static struct  iomux_pin *codec_pins_balong_mhlcap_udp[] = {
    &PCM1_XCLK_BALONG_MHLCAP_UDP, &PCM1_XFS_BALONG_MHLCAP_UDP, &PCM1_DI_BALONG_MHLCAP_UDP, &PCM1_DO_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_balong_mhlcap_udp, "block_codec", NORMAL, codec_pins_balong_mhlcap_udp)



/*CODEC*/

static enum lowlayer_func codec_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_balong_mhlcap_udp[] = {
    [NORMAL] = {codec_func_normal_balong_mhlcap_udp, codec_pullud_normal_balong_mhlcap_udp, codec_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {codec_func_lowpower_balong_mhlcap_udp, codec_pullud_lowpower_balong_mhlcap_udp, codec_drv_lowpower_balong_mhlcap_udp},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_balong_mhlcap_udp[] = {
    &UART1_TXD_BALONG_MHLCAP_UDP, &UART2_RXD_BALONG_MHLCAP_UDP, &UART2_TXD_BALONG_MHLCAP_UDP, &I2S_XCLK_BALONG_MHLCAP_UDP, &I2S_XFS_BALONG_MHLCAP_UDP, &I2S_DI_BALONG_MHLCAP_UDP, &I2S_DO_BALONG_MHLCAP_UDP, &PCM0_XCLK_BALONG_MHLCAP_UDP, &PCM0_XFS_BALONG_MHLCAP_UDP, &PCM0_DI_BALONG_MHLCAP_UDP, &PCM0_DO_BALONG_MHLCAP_UDP, &TS_ERR_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_balong_mhlcap_udp, "block_es305", NORMAL, es305_pins_balong_mhlcap_udp)



/*ES305*/

static enum lowlayer_func es305_func_normal_balong_mhlcap_udp[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_balong_mhlcap_udp[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_balong_mhlcap_udp[] = {
    [NORMAL] = {es305_func_normal_balong_mhlcap_udp, es305_pullud_normal_balong_mhlcap_udp, es305_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {es305_func_lowpower_balong_mhlcap_udp, es305_pullud_lowpower_balong_mhlcap_udp, es305_drv_lowpower_balong_mhlcap_udp},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_balong_mhlcap_udp[] = {
    &HKADC_SSI_BALONG_MHLCAP_UDP, &AUX_SSI0_BALONG_MHLCAP_UDP, &AUX_SSI1_BALONG_MHLCAP_UDP, &GPIO_5_0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_balong_mhlcap_udp, "block_pmu", NORMAL, pmu_pins_balong_mhlcap_udp)



/*PMU*/

static enum lowlayer_func pmu_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_balong_mhlcap_udp[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_balong_mhlcap_udp[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_balong_mhlcap_udp[] = {
    [NORMAL] = {pmu_func_normal_balong_mhlcap_udp, pmu_pullud_normal_balong_mhlcap_udp, pmu_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {pmu_func_lowpower_balong_mhlcap_udp, pmu_pullud_lowpower_balong_mhlcap_udp, pmu_drv_lowpower_balong_mhlcap_udp},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_balong_mhlcap_udp[] = {
    &EMMC_CLK_BALONG_MHLCAP_UDP, &EMMC_CMD_BALONG_MHLCAP_UDP, &EMMC_DATA0_BALONG_MHLCAP_UDP, &EMMC_DATA1_BALONG_MHLCAP_UDP, &EMMC_DATA2_BALONG_MHLCAP_UDP, &EMMC_DATA3_BALONG_MHLCAP_UDP, &EMMC_DATA4_BALONG_MHLCAP_UDP, &EMMC_DATA5_BALONG_MHLCAP_UDP, &EMMC_DATA6_BALONG_MHLCAP_UDP, &EMMC_DATA7_BALONG_MHLCAP_UDP, &GPIO_2_3_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_balong_mhlcap_udp, "block_emmc", NORMAL, emmc_pins_balong_mhlcap_udp)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_balong_mhlcap_udp[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_balong_mhlcap_udp[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config emmc_config_balong_mhlcap_udp[] = {
    [NORMAL] = {emmc_func_normal_balong_mhlcap_udp, emmc_pullud_normal_balong_mhlcap_udp, emmc_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {emmc_func_lowpower_balong_mhlcap_udp, emmc_pullud_lowpower_balong_mhlcap_udp, emmc_drv_lowpower_balong_mhlcap_udp},

};

/*rf pins */
static struct  iomux_pin *rf_pins_balong_mhlcap_udp[] = {
    &RF_TCVR_ON0_BALONG_MHLCAP_UDP, &RF_TCVR_ON1_BALONG_MHLCAP_UDP, &RF_TX_EN0_BALONG_MHLCAP_UDP, &RF_TX_EN1_BALONG_MHLCAP_UDP, &RF_MIPI_CLK1_BALONG_MHLCAP_UDP, &RF_MIPI_DATA1_BALONG_MHLCAP_UDP, &RF_SSI0_BALONG_MHLCAP_UDP, &RF_SSI1_BALONG_MHLCAP_UDP, &RF_GPIO_2_BALONG_MHLCAP_UDP, &RF_GPIO_3_BALONG_MHLCAP_UDP, &RF_GPIO_4_BALONG_MHLCAP_UDP, &RF_GPIO_5_BALONG_MHLCAP_UDP, &RF_GPIO_6_BALONG_MHLCAP_UDP, &RF_GPIO_7_BALONG_MHLCAP_UDP, &RF_GPIO_8_BALONG_MHLCAP_UDP, &RF_GPIO_9_BALONG_MHLCAP_UDP, &RF_GPIO_10_BALONG_MHLCAP_UDP, &RF_GPIO_11_BALONG_MHLCAP_UDP, &RF_GPIO_12_BALONG_MHLCAP_UDP, &RF_GPIO_13_BALONG_MHLCAP_UDP, &RF_GPIO_14_BALONG_MHLCAP_UDP, &RF_GPIO_15_BALONG_MHLCAP_UDP, &RF_GPIO_16_BALONG_MHLCAP_UDP, &RF_GPIO_17_BALONG_MHLCAP_UDP, &RF_GPIO_18_BALONG_MHLCAP_UDP, &RF_GPIO_19_BALONG_MHLCAP_UDP, &RF_GPIO_20_BALONG_MHLCAP_UDP, &RF_GPIO_21_BALONG_MHLCAP_UDP, &RF_GPIO_22_BALONG_MHLCAP_UDP, &RF_GPIO_23_BALONG_MHLCAP_UDP, &RF_GPIO_24_BALONG_MHLCAP_UDP, &RF_GPIO_25_BALONG_MHLCAP_UDP, &RF_GPIO_26_BALONG_MHLCAP_UDP, &RF_GPIO_27_BALONG_MHLCAP_UDP, &RF_GPIO_28_BALONG_MHLCAP_UDP, &RF_GPIO_29_BALONG_MHLCAP_UDP, &RF_GPIO_30_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_balong_mhlcap_udp, "block_rf", NORMAL, rf_pins_balong_mhlcap_udp)



/*RF*/

static enum lowlayer_func rf_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_balong_mhlcap_udp[] = {
    [NORMAL] = {rf_func_normal_balong_mhlcap_udp, rf_pullud_normal_balong_mhlcap_udp, rf_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {rf_func_lowpower_balong_mhlcap_udp, rf_pullud_lowpower_balong_mhlcap_udp, rf_drv_lowpower_balong_mhlcap_udp},

};

/*tp pins */
static struct  iomux_pin *tp_pins_balong_mhlcap_udp[] = {
    &GPIO_18_7_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_balong_mhlcap_udp, "block_tp", NORMAL, tp_pins_balong_mhlcap_udp)



/*TP*/

static enum lowlayer_func tp_func_normal_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_balong_mhlcap_udp[] = {
    [NORMAL] = {tp_func_normal_balong_mhlcap_udp, tp_pullud_normal_balong_mhlcap_udp, tp_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {tp_func_lowpower_balong_mhlcap_udp, tp_pullud_lowpower_balong_mhlcap_udp, tp_drv_lowpower_balong_mhlcap_udp},

};

/*exphp pins */
static struct  iomux_pin *exphp_pins_balong_mhlcap_udp[] = {
    &GPIO_5_1_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: exphp*/
IOMUX_BLOCK(block_exphp_balong_mhlcap_udp, "block_exphp", NORMAL, exphp_pins_balong_mhlcap_udp)



/*EXPHP*/

static enum lowlayer_func exphp_func_normal_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_normal_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_normal_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func exphp_func_lowpower_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static struct block_config exphp_config_balong_mhlcap_udp[] = {
    [NORMAL] = {exphp_func_normal_balong_mhlcap_udp, exphp_pullud_normal_balong_mhlcap_udp, exphp_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {exphp_func_lowpower_balong_mhlcap_udp, exphp_pullud_lowpower_balong_mhlcap_udp, exphp_drv_lowpower_balong_mhlcap_udp},

};

/*switch pins */
static struct  iomux_pin *switch_pins_balong_mhlcap_udp[] = {
    &GPIO_7_7_BALONG_MHLCAP_UDP, &GPIO_6_2_BALONG_MHLCAP_UDP, &GPIO_5_3_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_balong_mhlcap_udp, "block_switch", NORMAL, switch_pins_balong_mhlcap_udp)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_balong_mhlcap_udp[] = {
    [NORMAL] = {switch_func_normal_balong_mhlcap_udp, switch_pullud_normal_balong_mhlcap_udp, switch_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {switch_func_lowpower_balong_mhlcap_udp, switch_pullud_lowpower_balong_mhlcap_udp, switch_drv_lowpower_balong_mhlcap_udp},

};

/*spk pins */
static struct  iomux_pin *spk_pins_balong_mhlcap_udp[] = {
    &GPIO_7_4_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: spk*/
IOMUX_BLOCK(block_spk_balong_mhlcap_udp, "block_spk", NORMAL, spk_pins_balong_mhlcap_udp)



/*SPK*/

static enum lowlayer_func spk_func_normal_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_normal_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_normal_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func spk_func_lowpower_balong_mhlcap_udp[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0,  -INVALID,};

static struct block_config spk_config_balong_mhlcap_udp[] = {
    [NORMAL] = {spk_func_normal_balong_mhlcap_udp, spk_pullud_normal_balong_mhlcap_udp, spk_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {spk_func_lowpower_balong_mhlcap_udp, spk_pullud_lowpower_balong_mhlcap_udp, spk_drv_lowpower_balong_mhlcap_udp},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_balong_mhlcap_udp[] = {
    &RF_MIPI_CLK0_BALONG_MHLCAP_UDP, &RF_MIPI_DATA0_BALONG_MHLCAP_UDP, &APT_PDM0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_balong_mhlcap_udp, "block_rfpmu", NORMAL, rfpmu_pins_balong_mhlcap_udp)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_balong_mhlcap_udp[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_balong_mhlcap_udp[] = {
    [NORMAL] = {rfpmu_func_normal_balong_mhlcap_udp, rfpmu_pullud_normal_balong_mhlcap_udp, rfpmu_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {rfpmu_func_lowpower_balong_mhlcap_udp, rfpmu_pullud_lowpower_balong_mhlcap_udp, rfpmu_drv_lowpower_balong_mhlcap_udp},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_balong_mhlcap_udp[] = {
    &I2C3_SCL_BALONG_MHLCAP_UDP, &I2C3_SDA_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_balong_mhlcap_udp, "block_i2c3", NORMAL, i2c3_pins_balong_mhlcap_udp)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_balong_mhlcap_udp[] = {
    [NORMAL] = {i2c3_func_normal_balong_mhlcap_udp, i2c3_pullud_normal_balong_mhlcap_udp, i2c3_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {i2c3_func_lowpower_balong_mhlcap_udp, i2c3_pullud_lowpower_balong_mhlcap_udp, i2c3_drv_lowpower_balong_mhlcap_udp},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_balong_mhlcap_udp[] = {
    &GPIO_6_5_BALONG_MHLCAP_UDP, &GPIO_6_6_BALONG_MHLCAP_UDP, &GPIO_7_3_BALONG_MHLCAP_UDP, &GPIO_15_0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_balong_mhlcap_udp, "block_nfc", NORMAL, nfc_pins_balong_mhlcap_udp)



/*NFC*/

static enum lowlayer_func nfc_func_normal_balong_mhlcap_udp[] = {FUNC6, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_normal_balong_mhlcap_udp[] = {NOPULL, PULLDOWN, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, PULLDOWN, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config nfc_config_balong_mhlcap_udp[] = {
    [NORMAL] = {nfc_func_normal_balong_mhlcap_udp, nfc_pullud_normal_balong_mhlcap_udp, nfc_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {nfc_func_lowpower_balong_mhlcap_udp, nfc_pullud_lowpower_balong_mhlcap_udp, nfc_drv_lowpower_balong_mhlcap_udp},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_balong_mhlcap_udp[] = {
    &USIM1_CLK_BALONG_MHLCAP_UDP, &USIM1_DATA_BALONG_MHLCAP_UDP, &USIM1_RST_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_balong_mhlcap_udp, "block_usim1", NORMAL, usim1_pins_balong_mhlcap_udp)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_balong_mhlcap_udp[] = {
    [NORMAL] = {usim1_func_normal_balong_mhlcap_udp, usim1_pullud_normal_balong_mhlcap_udp, usim1_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {usim1_func_lowpower_balong_mhlcap_udp, usim1_pullud_lowpower_balong_mhlcap_udp, usim1_drv_lowpower_balong_mhlcap_udp},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_balong_mhlcap_udp[] = {
    &USIM0_CLK_BALONG_MHLCAP_UDP, &USIM0_DATA_BALONG_MHLCAP_UDP, &USIM0_RST_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_balong_mhlcap_udp, "block_usim0", NORMAL, usim0_pins_balong_mhlcap_udp)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_balong_mhlcap_udp[] = {
    [NORMAL] = {usim0_func_normal_balong_mhlcap_udp, usim0_pullud_normal_balong_mhlcap_udp, usim0_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {usim0_func_lowpower_balong_mhlcap_udp, usim0_pullud_lowpower_balong_mhlcap_udp, usim0_drv_lowpower_balong_mhlcap_udp},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_balong_mhlcap_udp[] = {
    &ISP_GPIO0_BALONG_MHLCAP_UDP, &ISP_GPIO2_BALONG_MHLCAP_UDP, &ISP_GPIO3_BALONG_MHLCAP_UDP, &ISP_RESETB0_BALONG_MHLCAP_UDP, &ISP_CCLK0_BALONG_MHLCAP_UDP, &ISP_SDA0_BALONG_MHLCAP_UDP, &ISP_SCL0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_balong_mhlcap_udp, "block_mcamera", NORMAL, mcamera_pins_balong_mhlcap_udp)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_balong_mhlcap_udp[] = {
    [NORMAL] = {mcamera_func_normal_balong_mhlcap_udp, mcamera_pullud_normal_balong_mhlcap_udp, mcamera_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {mcamera_func_lowpower_balong_mhlcap_udp, mcamera_pullud_lowpower_balong_mhlcap_udp, mcamera_drv_lowpower_balong_mhlcap_udp},

};

/*led pins */
static struct  iomux_pin *led_pins_balong_mhlcap_udp[] = {
    &GPIO_6_7_BALONG_MHLCAP_UDP, &GPIO_7_0_BALONG_MHLCAP_UDP, &GPIO_7_1_BALONG_MHLCAP_UDP, &GPIO_7_2_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: led*/
IOMUX_BLOCK(block_led_balong_mhlcap_udp, "block_led", NORMAL, led_pins_balong_mhlcap_udp)



/*LED*/

static enum lowlayer_func led_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func led_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config led_config_balong_mhlcap_udp[] = {
    [NORMAL] = {led_func_normal_balong_mhlcap_udp, led_pullud_normal_balong_mhlcap_udp, led_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {led_func_lowpower_balong_mhlcap_udp, led_pullud_lowpower_balong_mhlcap_udp, led_drv_lowpower_balong_mhlcap_udp},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_balong_mhlcap_udp[] = {
    &I2C0_SCL_BALONG_MHLCAP_UDP, &I2C0_SDA_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_balong_mhlcap_udp, "block_i2c0", NORMAL, i2c0_pins_balong_mhlcap_udp)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_balong_mhlcap_udp[] = {
    [NORMAL] = {i2c0_func_normal_balong_mhlcap_udp, i2c0_pullud_normal_balong_mhlcap_udp, i2c0_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {i2c0_func_lowpower_balong_mhlcap_udp, i2c0_pullud_lowpower_balong_mhlcap_udp, i2c0_drv_lowpower_balong_mhlcap_udp},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_balong_mhlcap_udp[] = {
    &I2C1_SCL_BALONG_MHLCAP_UDP, &I2C1_SDA_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_balong_mhlcap_udp, "block_i2c1", NORMAL, i2c1_pins_balong_mhlcap_udp)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_balong_mhlcap_udp[] = {
    [NORMAL] = {i2c1_func_normal_balong_mhlcap_udp, i2c1_pullud_normal_balong_mhlcap_udp, i2c1_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {i2c1_func_lowpower_balong_mhlcap_udp, i2c1_pullud_lowpower_balong_mhlcap_udp, i2c1_drv_lowpower_balong_mhlcap_udp},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_balong_mhlcap_udp[] = {
    &I2C2_SCL_BALONG_MHLCAP_UDP, &I2C2_SDA_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_balong_mhlcap_udp, "block_i2c2", NORMAL, i2c2_pins_balong_mhlcap_udp)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_balong_mhlcap_udp[] = {
    [NORMAL] = {i2c2_func_normal_balong_mhlcap_udp, i2c2_pullud_normal_balong_mhlcap_udp, i2c2_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {i2c2_func_lowpower_balong_mhlcap_udp, i2c2_pullud_lowpower_balong_mhlcap_udp, i2c2_drv_lowpower_balong_mhlcap_udp},

};

/*gps pins */
static struct  iomux_pin *gps_pins_balong_mhlcap_udp[] = {
    &GPIO_6_1_BALONG_MHLCAP_UDP, &RF_GPIO_1_BALONG_MHLCAP_UDP, &UART3_CTS_N_BALONG_MHLCAP_UDP, &UART3_RTS_N_BALONG_MHLCAP_UDP, &UART3_RXD_BALONG_MHLCAP_UDP, &UART3_TXD_BALONG_MHLCAP_UDP, &GPS_CLK_BALONG_MHLCAP_UDP, &GPIO_6_3_BALONG_MHLCAP_UDP, &GPIO_6_4_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_balong_mhlcap_udp, "block_gps", NORMAL, gps_pins_balong_mhlcap_udp)



/*GPS*/

static enum lowlayer_func gps_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC6,  -INVALID,};
static enum pull_updown gps_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_balong_mhlcap_udp[] = {
    [NORMAL] = {gps_func_normal_balong_mhlcap_udp, gps_pullud_normal_balong_mhlcap_udp, gps_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {gps_func_lowpower_balong_mhlcap_udp, gps_pullud_lowpower_balong_mhlcap_udp, gps_drv_lowpower_balong_mhlcap_udp},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_balong_mhlcap_udp[] = {
    &TCXO0_AFC_BALONG_MHLCAP_UDP, &TCXO1_AFC_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_balong_mhlcap_udp, "block_tcxo", NORMAL, tcxo_pins_balong_mhlcap_udp)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_balong_mhlcap_udp[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_balong_mhlcap_udp[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_balong_mhlcap_udp[] = {
    [NORMAL] = {tcxo_func_normal_balong_mhlcap_udp, tcxo_pullud_normal_balong_mhlcap_udp, tcxo_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {tcxo_func_lowpower_balong_mhlcap_udp, tcxo_pullud_lowpower_balong_mhlcap_udp, tcxo_drv_lowpower_balong_mhlcap_udp},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_balong_mhlcap_udp[] = {
    &GPIO_7_5_BALONG_MHLCAP_UDP, &GPIO_7_6_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_balong_mhlcap_udp, "block_rfant", NORMAL, rfant_pins_balong_mhlcap_udp)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_balong_mhlcap_udp[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_balong_mhlcap_udp[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfant_config_balong_mhlcap_udp[] = {
    [NORMAL] = {rfant_func_normal_balong_mhlcap_udp, rfant_pullud_normal_balong_mhlcap_udp, rfant_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {rfant_func_lowpower_balong_mhlcap_udp, rfant_pullud_lowpower_balong_mhlcap_udp, rfant_drv_lowpower_balong_mhlcap_udp},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_balong_mhlcap_udp[] = {
    &GPIO_2_2_BALONG_MHLCAP_UDP, &SDIO_DATA3_BALONG_MHLCAP_UDP, &SDIO_DATA2_BALONG_MHLCAP_UDP, &SDIO_DATA1_BALONG_MHLCAP_UDP, &SDIO_DATA0_BALONG_MHLCAP_UDP, &SDIO_CMD_BALONG_MHLCAP_UDP, &SDIO_CLK_BALONG_MHLCAP_UDP, &GPIO_1_4_BALONG_MHLCAP_UDP, &GPIO_1_5_BALONG_MHLCAP_UDP, &GPIO_1_6_BALONG_MHLCAP_UDP, &GPIO_1_7_BALONG_MHLCAP_UDP, &GPIO_2_0_BALONG_MHLCAP_UDP, &GPIO_2_1_BALONG_MHLCAP_UDP, &GPIO_6_0_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_balong_mhlcap_udp, "block_wifi", NORMAL, wifi_pins_balong_mhlcap_udp)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_balong_mhlcap_udp[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config wifi_config_balong_mhlcap_udp[] = {
    [NORMAL] = {wifi_func_normal_balong_mhlcap_udp, wifi_pullud_normal_balong_mhlcap_udp, wifi_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {wifi_func_lowpower_balong_mhlcap_udp, wifi_pullud_lowpower_balong_mhlcap_udp, wifi_drv_lowpower_balong_mhlcap_udp},

};

/*boot pins */
static struct  iomux_pin *boot_pins_balong_mhlcap_udp[] = {
    &BOOT_SEL_BALONG_MHLCAP_UDP, &GPIO_5_2_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_balong_mhlcap_udp, "block_boot", NORMAL, boot_pins_balong_mhlcap_udp)



/*BOOT*/

static enum lowlayer_func boot_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_balong_mhlcap_udp[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_balong_mhlcap_udp[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_balong_mhlcap_udp[] = {
    [NORMAL] = {boot_func_normal_balong_mhlcap_udp, boot_pullud_normal_balong_mhlcap_udp, boot_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {boot_func_lowpower_balong_mhlcap_udp, boot_pullud_lowpower_balong_mhlcap_udp, boot_drv_lowpower_balong_mhlcap_udp},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_balong_mhlcap_udp[] = {
    &PWM_OUT1_BALONG_MHLCAP_UDP, &GPIO_4_6_BALONG_MHLCAP_UDP, &GPIO_4_7_BALONG_MHLCAP_UDP, &GPIO_4_4_BALONG_MHLCAP_UDP, &GPIO_4_5_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_balong_mhlcap_udp, "block_lcd", NORMAL, lcd_pins_balong_mhlcap_udp)



/*LCD*/

static enum lowlayer_func lcd_func_normal_balong_mhlcap_udp[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_balong_mhlcap_udp[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_balong_mhlcap_udp[] = {
    [NORMAL] = {lcd_func_normal_balong_mhlcap_udp, lcd_pullud_normal_balong_mhlcap_udp, lcd_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {lcd_func_lowpower_balong_mhlcap_udp, lcd_pullud_lowpower_balong_mhlcap_udp, lcd_drv_lowpower_balong_mhlcap_udp},

};

/*key pins */
static struct  iomux_pin *key_pins_balong_mhlcap_udp[] = {
    &GPIO_4_2_BALONG_MHLCAP_UDP, &GPIO_4_3_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_balong_mhlcap_udp, "block_key", NORMAL, key_pins_balong_mhlcap_udp)



/*KEY*/

static enum lowlayer_func key_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_balong_mhlcap_udp[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_balong_mhlcap_udp[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_balong_mhlcap_udp[] = {
    [NORMAL] = {key_func_normal_balong_mhlcap_udp, key_pullud_normal_balong_mhlcap_udp, key_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {key_func_lowpower_balong_mhlcap_udp, key_pullud_lowpower_balong_mhlcap_udp, key_drv_lowpower_balong_mhlcap_udp},

};

/*test pins */
static struct  iomux_pin *test_pins_balong_mhlcap_udp[] = {
    &UART0_RXD_BALONG_MHLCAP_UDP, &UART0_TXD_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_balong_mhlcap_udp, "block_test", NORMAL, test_pins_balong_mhlcap_udp)



/*TEST*/

static enum lowlayer_func test_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_balong_mhlcap_udp[] = {
    [NORMAL] = {test_func_normal_balong_mhlcap_udp, test_pullud_normal_balong_mhlcap_udp, test_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {test_func_lowpower_balong_mhlcap_udp, test_pullud_lowpower_balong_mhlcap_udp, test_drv_lowpower_balong_mhlcap_udp},

};

/*cdma pins */
static struct  iomux_pin *cdma_pins_balong_mhlcap_udp[] = {
    &UART1_RTS_N_BALONG_MHLCAP_UDP, &UART1_RXD_BALONG_MHLCAP_UDP, &GPIO_15_6_BALONG_MHLCAP_UDP, &GPIO_5_4_BALONG_MHLCAP_UDP, &GPIO_5_5_BALONG_MHLCAP_UDP, &GPIO_5_6_BALONG_MHLCAP_UDP, &GPIO_5_7_BALONG_MHLCAP_UDP, &UART1_CTS_N_BALONG_MHLCAP_UDP, &GPIO_15_3_BALONG_MHLCAP_UDP, &GPIO_15_4_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: cdma*/
IOMUX_BLOCK(block_cdma_balong_mhlcap_udp, "block_cdma", NORMAL, cdma_pins_balong_mhlcap_udp)



/*CDMA*/

static enum lowlayer_func cdma_func_normal_balong_mhlcap_udp[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func cdma_func_lowpower_balong_mhlcap_udp[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config cdma_config_balong_mhlcap_udp[] = {
    [NORMAL] = {cdma_func_normal_balong_mhlcap_udp, cdma_pullud_normal_balong_mhlcap_udp, cdma_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {cdma_func_lowpower_balong_mhlcap_udp, cdma_pullud_lowpower_balong_mhlcap_udp, cdma_drv_lowpower_balong_mhlcap_udp},

};

/*sd pins */
static struct  iomux_pin *sd_pins_balong_mhlcap_udp[] = {
    &SD_CLK_BALONG_MHLCAP_UDP, &SD_CMD_BALONG_MHLCAP_UDP, &SD_DATA0_BALONG_MHLCAP_UDP, &SD_DATA1_BALONG_MHLCAP_UDP, &SD_DATA2_BALONG_MHLCAP_UDP, &SD_DATA3_BALONG_MHLCAP_UDP,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_balong_mhlcap_udp, "block_sd", NORMAL, sd_pins_balong_mhlcap_udp)



/*SD*/

static enum lowlayer_func sd_func_normal_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_balong_mhlcap_udp[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_balong_mhlcap_udp[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_balong_mhlcap_udp[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_balong_mhlcap_udp[] = {
    [NORMAL] = {sd_func_normal_balong_mhlcap_udp, sd_pullud_normal_balong_mhlcap_udp, sd_drv_normal_balong_mhlcap_udp},
    [LOWPOWER] = {sd_func_lowpower_balong_mhlcap_udp, sd_pullud_lowpower_balong_mhlcap_udp, sd_drv_lowpower_balong_mhlcap_udp},

};

struct iomux_block_table block_config_table_balong_mhlcap_udp[] = {
    BLOCK_CONFIG("block_acc", &block_acc_balong_mhlcap_udp, acc_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_charger", &block_charger_balong_mhlcap_udp, charger_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_flash", &block_flash_balong_mhlcap_udp, flash_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_bt", &block_bt_balong_mhlcap_udp, bt_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_scamera", &block_scamera_balong_mhlcap_udp, scamera_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_codec", &block_codec_balong_mhlcap_udp, codec_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_es305", &block_es305_balong_mhlcap_udp, es305_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_pmu", &block_pmu_balong_mhlcap_udp, pmu_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_emmc", &block_emmc_balong_mhlcap_udp, emmc_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_rf", &block_rf_balong_mhlcap_udp, rf_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_tp", &block_tp_balong_mhlcap_udp, tp_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_exphp", &block_exphp_balong_mhlcap_udp, exphp_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_switch", &block_switch_balong_mhlcap_udp, switch_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_spk", &block_spk_balong_mhlcap_udp, spk_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_balong_mhlcap_udp, rfpmu_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_balong_mhlcap_udp, i2c3_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_nfc", &block_nfc_balong_mhlcap_udp, nfc_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_usim1", &block_usim1_balong_mhlcap_udp, usim1_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_usim0", &block_usim0_balong_mhlcap_udp, usim0_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_balong_mhlcap_udp, mcamera_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_led", &block_led_balong_mhlcap_udp, led_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_balong_mhlcap_udp, i2c0_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_balong_mhlcap_udp, i2c1_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_balong_mhlcap_udp, i2c2_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_gps", &block_gps_balong_mhlcap_udp, gps_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_balong_mhlcap_udp, tcxo_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_rfant", &block_rfant_balong_mhlcap_udp, rfant_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_wifi", &block_wifi_balong_mhlcap_udp, wifi_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_boot", &block_boot_balong_mhlcap_udp, boot_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_lcd", &block_lcd_balong_mhlcap_udp, lcd_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_key", &block_key_balong_mhlcap_udp, key_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_test", &block_test_balong_mhlcap_udp, test_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_cdma", &block_cdma_balong_mhlcap_udp, cdma_config_balong_mhlcap_udp)
    BLOCK_CONFIG("block_sd", &block_sd_balong_mhlcap_udp, sd_config_balong_mhlcap_udp)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
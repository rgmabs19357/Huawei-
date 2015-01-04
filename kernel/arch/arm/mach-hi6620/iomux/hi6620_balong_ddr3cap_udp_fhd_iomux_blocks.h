/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_balong_ddr3cap_udp_fhd_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_BALONG_DDR3CAP_UDP_FHD_IOMUX_BLOCKS_H__
#define __HI6620_BALONG_DDR3CAP_UDP_FHD_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_balong_ddr3cap_udp_fhd_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_4_0_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_1_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_balong_ddr3cap_udp_fhd, "block_charger", NORMAL, charger_pins_balong_ddr3cap_udp_fhd)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {charger_func_normal_balong_ddr3cap_udp_fhd, charger_pullud_normal_balong_ddr3cap_udp_fhd, charger_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {charger_func_lowpower_balong_ddr3cap_udp_fhd, charger_pullud_lowpower_balong_ddr3cap_udp_fhd, charger_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*flash pins */
static struct  iomux_pin *flash_pins_balong_ddr3cap_udp_fhd[] = {
    &ISP_GPIO5_BALONG_DDR3CAP_UDP_FHD, &ISP_STROBE1_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_0_BALONG_DDR3CAP_UDP_FHD, &ISP_STROBE0_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_balong_ddr3cap_udp_fhd, "block_flash", NORMAL, flash_pins_balong_ddr3cap_udp_fhd)



/*FLASH*/

static enum lowlayer_func flash_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC2, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength flash_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {flash_func_normal_balong_ddr3cap_udp_fhd, flash_pullud_normal_balong_ddr3cap_udp_fhd, flash_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {flash_func_lowpower_balong_ddr3cap_udp_fhd, flash_pullud_lowpower_balong_ddr3cap_udp_fhd, flash_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*bt pins */
static struct  iomux_pin *bt_pins_balong_ddr3cap_udp_fhd[] = {
    &UART4_CTS_N_BALONG_DDR3CAP_UDP_FHD, &UART4_RTS_N_BALONG_DDR3CAP_UDP_FHD, &UART4_RXD_BALONG_DDR3CAP_UDP_FHD, &UART4_TXD_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_5_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_7_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_balong_ddr3cap_udp_fhd, "block_bt", NORMAL, bt_pins_balong_ddr3cap_udp_fhd)



/*BT*/

static enum lowlayer_func bt_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {bt_func_normal_balong_ddr3cap_udp_fhd, bt_pullud_normal_balong_ddr3cap_udp_fhd, bt_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {bt_func_lowpower_balong_ddr3cap_udp_fhd, bt_pullud_lowpower_balong_ddr3cap_udp_fhd, bt_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_balong_ddr3cap_udp_fhd[] = {
    &ISP_GPIO1_BALONG_DDR3CAP_UDP_FHD, &ISP_GPIO4_BALONG_DDR3CAP_UDP_FHD, &ISP_RESETB1_BALONG_DDR3CAP_UDP_FHD, &ISP_CCLK1_BALONG_DDR3CAP_UDP_FHD, &ISP_SDA1_BALONG_DDR3CAP_UDP_FHD, &ISP_SCL1_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_balong_ddr3cap_udp_fhd, "block_scamera", NORMAL, scamera_pins_balong_ddr3cap_udp_fhd)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {scamera_func_normal_balong_ddr3cap_udp_fhd, scamera_pullud_normal_balong_ddr3cap_udp_fhd, scamera_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {scamera_func_lowpower_balong_ddr3cap_udp_fhd, scamera_pullud_lowpower_balong_ddr3cap_udp_fhd, scamera_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*codec pins */
static struct  iomux_pin *codec_pins_balong_ddr3cap_udp_fhd[] = {
    &PCM1_XCLK_BALONG_DDR3CAP_UDP_FHD, &PCM1_XFS_BALONG_DDR3CAP_UDP_FHD, &PCM1_DI_BALONG_DDR3CAP_UDP_FHD, &PCM1_DO_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_balong_ddr3cap_udp_fhd, "block_codec", NORMAL, codec_pins_balong_ddr3cap_udp_fhd)



/*CODEC*/

static enum lowlayer_func codec_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {codec_func_normal_balong_ddr3cap_udp_fhd, codec_pullud_normal_balong_ddr3cap_udp_fhd, codec_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {codec_func_lowpower_balong_ddr3cap_udp_fhd, codec_pullud_lowpower_balong_ddr3cap_udp_fhd, codec_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_balong_ddr3cap_udp_fhd[] = {
    &UART1_TXD_BALONG_DDR3CAP_UDP_FHD, &UART2_RXD_BALONG_DDR3CAP_UDP_FHD, &UART2_TXD_BALONG_DDR3CAP_UDP_FHD, &I2S_XCLK_BALONG_DDR3CAP_UDP_FHD, &I2S_XFS_BALONG_DDR3CAP_UDP_FHD, &I2S_DI_BALONG_DDR3CAP_UDP_FHD, &I2S_DO_BALONG_DDR3CAP_UDP_FHD, &PCM0_XCLK_BALONG_DDR3CAP_UDP_FHD, &PCM0_XFS_BALONG_DDR3CAP_UDP_FHD, &PCM0_DI_BALONG_DDR3CAP_UDP_FHD, &PCM0_DO_BALONG_DDR3CAP_UDP_FHD, &TS_ERR_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_balong_ddr3cap_udp_fhd, "block_es305", NORMAL, es305_pins_balong_ddr3cap_udp_fhd)



/*ES305*/

static enum lowlayer_func es305_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {es305_func_normal_balong_ddr3cap_udp_fhd, es305_pullud_normal_balong_ddr3cap_udp_fhd, es305_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {es305_func_lowpower_balong_ddr3cap_udp_fhd, es305_pullud_lowpower_balong_ddr3cap_udp_fhd, es305_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_balong_ddr3cap_udp_fhd[] = {
    &HKADC_SSI_BALONG_DDR3CAP_UDP_FHD, &AUX_SSI0_BALONG_DDR3CAP_UDP_FHD, &AUX_SSI1_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_0_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_balong_ddr3cap_udp_fhd, "block_pmu", NORMAL, pmu_pins_balong_ddr3cap_udp_fhd)



/*PMU*/

static enum lowlayer_func pmu_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_balong_ddr3cap_udp_fhd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {pmu_func_normal_balong_ddr3cap_udp_fhd, pmu_pullud_normal_balong_ddr3cap_udp_fhd, pmu_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {pmu_func_lowpower_balong_ddr3cap_udp_fhd, pmu_pullud_lowpower_balong_ddr3cap_udp_fhd, pmu_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_balong_ddr3cap_udp_fhd[] = {
    &EMMC_CLK_BALONG_DDR3CAP_UDP_FHD, &EMMC_CMD_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA0_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA1_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA2_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA3_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA4_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA5_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA6_BALONG_DDR3CAP_UDP_FHD, &EMMC_DATA7_BALONG_DDR3CAP_UDP_FHD, &GPIO_2_3_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_balong_ddr3cap_udp_fhd, "block_emmc", NORMAL, emmc_pins_balong_ddr3cap_udp_fhd)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config emmc_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {emmc_func_normal_balong_ddr3cap_udp_fhd, emmc_pullud_normal_balong_ddr3cap_udp_fhd, emmc_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {emmc_func_lowpower_balong_ddr3cap_udp_fhd, emmc_pullud_lowpower_balong_ddr3cap_udp_fhd, emmc_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*rf pins */
static struct  iomux_pin *rf_pins_balong_ddr3cap_udp_fhd[] = {
    &RF_TCVR_ON0_BALONG_DDR3CAP_UDP_FHD, &RF_TCVR_ON1_BALONG_DDR3CAP_UDP_FHD, &RF_TX_EN0_BALONG_DDR3CAP_UDP_FHD, &RF_TX_EN1_BALONG_DDR3CAP_UDP_FHD, &RF_MIPI_CLK1_BALONG_DDR3CAP_UDP_FHD, &RF_MIPI_DATA1_BALONG_DDR3CAP_UDP_FHD, &RF_SSI0_BALONG_DDR3CAP_UDP_FHD, &RF_SSI1_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_2_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_3_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_4_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_5_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_6_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_7_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_8_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_9_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_10_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_11_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_12_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_13_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_14_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_15_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_16_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_17_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_18_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_19_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_20_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_21_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_22_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_23_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_24_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_25_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_26_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_27_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_28_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_29_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_30_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_balong_ddr3cap_udp_fhd, "block_rf", NORMAL, rf_pins_balong_ddr3cap_udp_fhd)



/*RF*/

static enum lowlayer_func rf_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {rf_func_normal_balong_ddr3cap_udp_fhd, rf_pullud_normal_balong_ddr3cap_udp_fhd, rf_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {rf_func_lowpower_balong_ddr3cap_udp_fhd, rf_pullud_lowpower_balong_ddr3cap_udp_fhd, rf_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*tp pins */
static struct  iomux_pin *tp_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_18_7_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_balong_ddr3cap_udp_fhd, "block_tp", NORMAL, tp_pins_balong_ddr3cap_udp_fhd)



/*TP*/

static enum lowlayer_func tp_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {tp_func_normal_balong_ddr3cap_udp_fhd, tp_pullud_normal_balong_ddr3cap_udp_fhd, tp_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {tp_func_lowpower_balong_ddr3cap_udp_fhd, tp_pullud_lowpower_balong_ddr3cap_udp_fhd, tp_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*exphp pins */
static struct  iomux_pin *exphp_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_5_1_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: exphp*/
IOMUX_BLOCK(block_exphp_balong_ddr3cap_udp_fhd, "block_exphp", NORMAL, exphp_pins_balong_ddr3cap_udp_fhd)



/*EXPHP*/

static enum lowlayer_func exphp_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func exphp_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown exphp_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength exphp_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static struct block_config exphp_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {exphp_func_normal_balong_ddr3cap_udp_fhd, exphp_pullud_normal_balong_ddr3cap_udp_fhd, exphp_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {exphp_func_lowpower_balong_ddr3cap_udp_fhd, exphp_pullud_lowpower_balong_ddr3cap_udp_fhd, exphp_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*switch pins */
static struct  iomux_pin *switch_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_6_2_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_3_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_balong_ddr3cap_udp_fhd, "block_switch", NORMAL, switch_pins_balong_ddr3cap_udp_fhd)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {switch_func_normal_balong_ddr3cap_udp_fhd, switch_pullud_normal_balong_ddr3cap_udp_fhd, switch_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {switch_func_lowpower_balong_ddr3cap_udp_fhd, switch_pullud_lowpower_balong_ddr3cap_udp_fhd, switch_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*spk pins */
static struct  iomux_pin *spk_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_7_4_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: spk*/
IOMUX_BLOCK(block_spk_balong_ddr3cap_udp_fhd, "block_spk", NORMAL, spk_pins_balong_ddr3cap_udp_fhd)



/*SPK*/

static enum lowlayer_func spk_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func spk_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0,  -INVALID,};
static enum pull_updown spk_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL,  -INVALID,};
static enum drive_strength spk_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0,  -INVALID,};

static struct block_config spk_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {spk_func_normal_balong_ddr3cap_udp_fhd, spk_pullud_normal_balong_ddr3cap_udp_fhd, spk_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {spk_func_lowpower_balong_ddr3cap_udp_fhd, spk_pullud_lowpower_balong_ddr3cap_udp_fhd, spk_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_balong_ddr3cap_udp_fhd[] = {
    &RF_MIPI_CLK0_BALONG_DDR3CAP_UDP_FHD, &RF_MIPI_DATA0_BALONG_DDR3CAP_UDP_FHD, &APT_PDM0_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_balong_ddr3cap_udp_fhd, "block_rfpmu", NORMAL, rfpmu_pins_balong_ddr3cap_udp_fhd)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {rfpmu_func_normal_balong_ddr3cap_udp_fhd, rfpmu_pullud_normal_balong_ddr3cap_udp_fhd, rfpmu_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {rfpmu_func_lowpower_balong_ddr3cap_udp_fhd, rfpmu_pullud_lowpower_balong_ddr3cap_udp_fhd, rfpmu_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_balong_ddr3cap_udp_fhd[] = {
    &I2C3_SCL_BALONG_DDR3CAP_UDP_FHD, &I2C3_SDA_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_balong_ddr3cap_udp_fhd, "block_i2c3", NORMAL, i2c3_pins_balong_ddr3cap_udp_fhd)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {i2c3_func_normal_balong_ddr3cap_udp_fhd, i2c3_pullud_normal_balong_ddr3cap_udp_fhd, i2c3_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {i2c3_func_lowpower_balong_ddr3cap_udp_fhd, i2c3_pullud_lowpower_balong_ddr3cap_udp_fhd, i2c3_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_6_5_BALONG_DDR3CAP_UDP_FHD, &GPIO_6_6_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_3_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_balong_ddr3cap_udp_fhd, "block_nfc", NORMAL, nfc_pins_balong_ddr3cap_udp_fhd)



/*NFC*/

static enum lowlayer_func nfc_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC6, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config nfc_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {nfc_func_normal_balong_ddr3cap_udp_fhd, nfc_pullud_normal_balong_ddr3cap_udp_fhd, nfc_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {nfc_func_lowpower_balong_ddr3cap_udp_fhd, nfc_pullud_lowpower_balong_ddr3cap_udp_fhd, nfc_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_balong_ddr3cap_udp_fhd[] = {
    &USIM1_CLK_BALONG_DDR3CAP_UDP_FHD, &USIM1_DATA_BALONG_DDR3CAP_UDP_FHD, &USIM1_RST_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_balong_ddr3cap_udp_fhd, "block_usim1", NORMAL, usim1_pins_balong_ddr3cap_udp_fhd)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {usim1_func_normal_balong_ddr3cap_udp_fhd, usim1_pullud_normal_balong_ddr3cap_udp_fhd, usim1_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {usim1_func_lowpower_balong_ddr3cap_udp_fhd, usim1_pullud_lowpower_balong_ddr3cap_udp_fhd, usim1_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_balong_ddr3cap_udp_fhd[] = {
    &USIM0_CLK_BALONG_DDR3CAP_UDP_FHD, &USIM0_DATA_BALONG_DDR3CAP_UDP_FHD, &USIM0_RST_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_balong_ddr3cap_udp_fhd, "block_usim0", NORMAL, usim0_pins_balong_ddr3cap_udp_fhd)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {usim0_func_normal_balong_ddr3cap_udp_fhd, usim0_pullud_normal_balong_ddr3cap_udp_fhd, usim0_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {usim0_func_lowpower_balong_ddr3cap_udp_fhd, usim0_pullud_lowpower_balong_ddr3cap_udp_fhd, usim0_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_balong_ddr3cap_udp_fhd[] = {
    &ISP_GPIO0_BALONG_DDR3CAP_UDP_FHD, &ISP_GPIO2_BALONG_DDR3CAP_UDP_FHD, &ISP_GPIO3_BALONG_DDR3CAP_UDP_FHD, &ISP_RESETB0_BALONG_DDR3CAP_UDP_FHD, &ISP_CCLK0_BALONG_DDR3CAP_UDP_FHD, &ISP_SDA0_BALONG_DDR3CAP_UDP_FHD, &ISP_SCL0_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_balong_ddr3cap_udp_fhd, "block_mcamera", NORMAL, mcamera_pins_balong_ddr3cap_udp_fhd)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {mcamera_func_normal_balong_ddr3cap_udp_fhd, mcamera_pullud_normal_balong_ddr3cap_udp_fhd, mcamera_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {mcamera_func_lowpower_balong_ddr3cap_udp_fhd, mcamera_pullud_lowpower_balong_ddr3cap_udp_fhd, mcamera_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*led pins */
static struct  iomux_pin *led_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_6_7_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_0_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_1_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_2_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: led*/
IOMUX_BLOCK(block_led_balong_ddr3cap_udp_fhd, "block_led", NORMAL, led_pins_balong_ddr3cap_udp_fhd)



/*LED*/

static enum lowlayer_func led_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func led_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown led_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength led_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config led_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {led_func_normal_balong_ddr3cap_udp_fhd, led_pullud_normal_balong_ddr3cap_udp_fhd, led_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {led_func_lowpower_balong_ddr3cap_udp_fhd, led_pullud_lowpower_balong_ddr3cap_udp_fhd, led_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_balong_ddr3cap_udp_fhd[] = {
    &I2C0_SCL_BALONG_DDR3CAP_UDP_FHD, &I2C0_SDA_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_balong_ddr3cap_udp_fhd, "block_i2c0", NORMAL, i2c0_pins_balong_ddr3cap_udp_fhd)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {i2c0_func_normal_balong_ddr3cap_udp_fhd, i2c0_pullud_normal_balong_ddr3cap_udp_fhd, i2c0_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {i2c0_func_lowpower_balong_ddr3cap_udp_fhd, i2c0_pullud_lowpower_balong_ddr3cap_udp_fhd, i2c0_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_balong_ddr3cap_udp_fhd[] = {
    &I2C1_SCL_BALONG_DDR3CAP_UDP_FHD, &I2C1_SDA_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_balong_ddr3cap_udp_fhd, "block_i2c1", NORMAL, i2c1_pins_balong_ddr3cap_udp_fhd)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {i2c1_func_normal_balong_ddr3cap_udp_fhd, i2c1_pullud_normal_balong_ddr3cap_udp_fhd, i2c1_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {i2c1_func_lowpower_balong_ddr3cap_udp_fhd, i2c1_pullud_lowpower_balong_ddr3cap_udp_fhd, i2c1_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_balong_ddr3cap_udp_fhd[] = {
    &I2C2_SCL_BALONG_DDR3CAP_UDP_FHD, &I2C2_SDA_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_balong_ddr3cap_udp_fhd, "block_i2c2", NORMAL, i2c2_pins_balong_ddr3cap_udp_fhd)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {i2c2_func_normal_balong_ddr3cap_udp_fhd, i2c2_pullud_normal_balong_ddr3cap_udp_fhd, i2c2_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {i2c2_func_lowpower_balong_ddr3cap_udp_fhd, i2c2_pullud_lowpower_balong_ddr3cap_udp_fhd, i2c2_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*gps pins */
static struct  iomux_pin *gps_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_6_1_BALONG_DDR3CAP_UDP_FHD, &RF_GPIO_1_BALONG_DDR3CAP_UDP_FHD, &UART3_CTS_N_BALONG_DDR3CAP_UDP_FHD, &UART3_RTS_N_BALONG_DDR3CAP_UDP_FHD, &UART3_RXD_BALONG_DDR3CAP_UDP_FHD, &UART3_TXD_BALONG_DDR3CAP_UDP_FHD, &GPS_CLK_BALONG_DDR3CAP_UDP_FHD, &GPIO_6_3_BALONG_DDR3CAP_UDP_FHD, &GPIO_6_4_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_balong_ddr3cap_udp_fhd, "block_gps", NORMAL, gps_pins_balong_ddr3cap_udp_fhd)



/*GPS*/

static enum lowlayer_func gps_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC6,  -INVALID,};
static enum pull_updown gps_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {gps_func_normal_balong_ddr3cap_udp_fhd, gps_pullud_normal_balong_ddr3cap_udp_fhd, gps_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {gps_func_lowpower_balong_ddr3cap_udp_fhd, gps_pullud_lowpower_balong_ddr3cap_udp_fhd, gps_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_balong_ddr3cap_udp_fhd[] = {
    &TCXO0_AFC_BALONG_DDR3CAP_UDP_FHD, &TCXO1_AFC_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_balong_ddr3cap_udp_fhd, "block_tcxo", NORMAL, tcxo_pins_balong_ddr3cap_udp_fhd)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {tcxo_func_normal_balong_ddr3cap_udp_fhd, tcxo_pullud_normal_balong_ddr3cap_udp_fhd, tcxo_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {tcxo_func_lowpower_balong_ddr3cap_udp_fhd, tcxo_pullud_lowpower_balong_ddr3cap_udp_fhd, tcxo_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_7_5_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_6_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_balong_ddr3cap_udp_fhd, "block_rfant", NORMAL, rfant_pins_balong_ddr3cap_udp_fhd)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_balong_ddr3cap_udp_fhd[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfant_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {rfant_func_normal_balong_ddr3cap_udp_fhd, rfant_pullud_normal_balong_ddr3cap_udp_fhd, rfant_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {rfant_func_lowpower_balong_ddr3cap_udp_fhd, rfant_pullud_lowpower_balong_ddr3cap_udp_fhd, rfant_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_2_2_BALONG_DDR3CAP_UDP_FHD, &SDIO_DATA3_BALONG_DDR3CAP_UDP_FHD, &SDIO_DATA2_BALONG_DDR3CAP_UDP_FHD, &SDIO_DATA1_BALONG_DDR3CAP_UDP_FHD, &SDIO_DATA0_BALONG_DDR3CAP_UDP_FHD, &SDIO_CMD_BALONG_DDR3CAP_UDP_FHD, &SDIO_CLK_BALONG_DDR3CAP_UDP_FHD, &GPIO_1_4_BALONG_DDR3CAP_UDP_FHD, &GPIO_1_5_BALONG_DDR3CAP_UDP_FHD, &GPIO_1_6_BALONG_DDR3CAP_UDP_FHD, &GPIO_1_7_BALONG_DDR3CAP_UDP_FHD, &GPIO_2_0_BALONG_DDR3CAP_UDP_FHD, &GPIO_2_1_BALONG_DDR3CAP_UDP_FHD, &GPIO_6_0_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_balong_ddr3cap_udp_fhd, "block_wifi", NORMAL, wifi_pins_balong_ddr3cap_udp_fhd)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config wifi_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {wifi_func_normal_balong_ddr3cap_udp_fhd, wifi_pullud_normal_balong_ddr3cap_udp_fhd, wifi_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {wifi_func_lowpower_balong_ddr3cap_udp_fhd, wifi_pullud_lowpower_balong_ddr3cap_udp_fhd, wifi_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*boot pins */
static struct  iomux_pin *boot_pins_balong_ddr3cap_udp_fhd[] = {
    &BOOT_SEL_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_2_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_balong_ddr3cap_udp_fhd, "block_boot", NORMAL, boot_pins_balong_ddr3cap_udp_fhd)



/*BOOT*/

static enum lowlayer_func boot_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_normal_balong_ddr3cap_udp_fhd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {boot_func_normal_balong_ddr3cap_udp_fhd, boot_pullud_normal_balong_ddr3cap_udp_fhd, boot_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {boot_func_lowpower_balong_ddr3cap_udp_fhd, boot_pullud_lowpower_balong_ddr3cap_udp_fhd, boot_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_balong_ddr3cap_udp_fhd[] = {
    &PWM_OUT1_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_6_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_7_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_4_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_5_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_balong_ddr3cap_udp_fhd, "block_lcd", NORMAL, lcd_pins_balong_ddr3cap_udp_fhd)



/*LCD*/

static enum lowlayer_func lcd_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {lcd_func_normal_balong_ddr3cap_udp_fhd, lcd_pullud_normal_balong_ddr3cap_udp_fhd, lcd_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {lcd_func_lowpower_balong_ddr3cap_udp_fhd, lcd_pullud_lowpower_balong_ddr3cap_udp_fhd, lcd_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*key pins */
static struct  iomux_pin *key_pins_balong_ddr3cap_udp_fhd[] = {
    &GPIO_4_2_BALONG_DDR3CAP_UDP_FHD, &GPIO_4_3_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_balong_ddr3cap_udp_fhd, "block_key", NORMAL, key_pins_balong_ddr3cap_udp_fhd)



/*KEY*/

static enum lowlayer_func key_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_balong_ddr3cap_udp_fhd[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {key_func_normal_balong_ddr3cap_udp_fhd, key_pullud_normal_balong_ddr3cap_udp_fhd, key_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {key_func_lowpower_balong_ddr3cap_udp_fhd, key_pullud_lowpower_balong_ddr3cap_udp_fhd, key_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*test pins */
static struct  iomux_pin *test_pins_balong_ddr3cap_udp_fhd[] = {
    &UART0_RXD_BALONG_DDR3CAP_UDP_FHD, &UART0_TXD_BALONG_DDR3CAP_UDP_FHD, &GPIO_7_7_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_0_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_1_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_2_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_balong_ddr3cap_udp_fhd, "block_test", NORMAL, test_pins_balong_ddr3cap_udp_fhd)



/*TEST*/

static enum lowlayer_func test_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6,  -INVALID,};
static enum pull_updown test_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6,  -INVALID,};
static enum pull_updown test_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {test_func_normal_balong_ddr3cap_udp_fhd, test_pullud_normal_balong_ddr3cap_udp_fhd, test_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {test_func_lowpower_balong_ddr3cap_udp_fhd, test_pullud_lowpower_balong_ddr3cap_udp_fhd, test_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*cdma pins */
static struct  iomux_pin *cdma_pins_balong_ddr3cap_udp_fhd[] = {
    &UART1_RTS_N_BALONG_DDR3CAP_UDP_FHD, &UART1_RXD_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_6_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_4_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_5_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_6_BALONG_DDR3CAP_UDP_FHD, &GPIO_5_7_BALONG_DDR3CAP_UDP_FHD, &UART1_CTS_N_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_3_BALONG_DDR3CAP_UDP_FHD, &GPIO_15_4_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: cdma*/
IOMUX_BLOCK(block_cdma_balong_ddr3cap_udp_fhd, "block_cdma", NORMAL, cdma_pins_balong_ddr3cap_udp_fhd)



/*CDMA*/

static enum lowlayer_func cdma_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func cdma_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC2, FUNC2, FUNC0, FUNC6, FUNC6, FUNC6, FUNC6, FUNC2, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config cdma_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {cdma_func_normal_balong_ddr3cap_udp_fhd, cdma_pullud_normal_balong_ddr3cap_udp_fhd, cdma_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {cdma_func_lowpower_balong_ddr3cap_udp_fhd, cdma_pullud_lowpower_balong_ddr3cap_udp_fhd, cdma_drv_lowpower_balong_ddr3cap_udp_fhd},

};

/*sd pins */
static struct  iomux_pin *sd_pins_balong_ddr3cap_udp_fhd[] = {
    &SD_CLK_BALONG_DDR3CAP_UDP_FHD, &SD_CMD_BALONG_DDR3CAP_UDP_FHD, &SD_DATA0_BALONG_DDR3CAP_UDP_FHD, &SD_DATA1_BALONG_DDR3CAP_UDP_FHD, &SD_DATA2_BALONG_DDR3CAP_UDP_FHD, &SD_DATA3_BALONG_DDR3CAP_UDP_FHD,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_balong_ddr3cap_udp_fhd, "block_sd", NORMAL, sd_pins_balong_ddr3cap_udp_fhd)



/*SD*/

static enum lowlayer_func sd_func_normal_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_balong_ddr3cap_udp_fhd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_balong_ddr3cap_udp_fhd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_balong_ddr3cap_udp_fhd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_balong_ddr3cap_udp_fhd[] = {
    [NORMAL] = {sd_func_normal_balong_ddr3cap_udp_fhd, sd_pullud_normal_balong_ddr3cap_udp_fhd, sd_drv_normal_balong_ddr3cap_udp_fhd},
    [LOWPOWER] = {sd_func_lowpower_balong_ddr3cap_udp_fhd, sd_pullud_lowpower_balong_ddr3cap_udp_fhd, sd_drv_lowpower_balong_ddr3cap_udp_fhd},

};

struct iomux_block_table block_config_table_balong_ddr3cap_udp_fhd[] = {
    BLOCK_CONFIG("block_charger", &block_charger_balong_ddr3cap_udp_fhd, charger_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_flash", &block_flash_balong_ddr3cap_udp_fhd, flash_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_bt", &block_bt_balong_ddr3cap_udp_fhd, bt_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_scamera", &block_scamera_balong_ddr3cap_udp_fhd, scamera_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_codec", &block_codec_balong_ddr3cap_udp_fhd, codec_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_es305", &block_es305_balong_ddr3cap_udp_fhd, es305_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_pmu", &block_pmu_balong_ddr3cap_udp_fhd, pmu_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_emmc", &block_emmc_balong_ddr3cap_udp_fhd, emmc_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_rf", &block_rf_balong_ddr3cap_udp_fhd, rf_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_tp", &block_tp_balong_ddr3cap_udp_fhd, tp_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_exphp", &block_exphp_balong_ddr3cap_udp_fhd, exphp_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_switch", &block_switch_balong_ddr3cap_udp_fhd, switch_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_spk", &block_spk_balong_ddr3cap_udp_fhd, spk_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_balong_ddr3cap_udp_fhd, rfpmu_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_balong_ddr3cap_udp_fhd, i2c3_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_nfc", &block_nfc_balong_ddr3cap_udp_fhd, nfc_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_usim1", &block_usim1_balong_ddr3cap_udp_fhd, usim1_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_usim0", &block_usim0_balong_ddr3cap_udp_fhd, usim0_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_balong_ddr3cap_udp_fhd, mcamera_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_led", &block_led_balong_ddr3cap_udp_fhd, led_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_balong_ddr3cap_udp_fhd, i2c0_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_balong_ddr3cap_udp_fhd, i2c1_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_balong_ddr3cap_udp_fhd, i2c2_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_gps", &block_gps_balong_ddr3cap_udp_fhd, gps_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_balong_ddr3cap_udp_fhd, tcxo_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_rfant", &block_rfant_balong_ddr3cap_udp_fhd, rfant_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_wifi", &block_wifi_balong_ddr3cap_udp_fhd, wifi_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_boot", &block_boot_balong_ddr3cap_udp_fhd, boot_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_lcd", &block_lcd_balong_ddr3cap_udp_fhd, lcd_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_key", &block_key_balong_ddr3cap_udp_fhd, key_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_test", &block_test_balong_ddr3cap_udp_fhd, test_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_cdma", &block_cdma_balong_ddr3cap_udp_fhd, cdma_config_balong_ddr3cap_udp_fhd)
    BLOCK_CONFIG("block_sd", &block_sd_balong_ddr3cap_udp_fhd, sd_config_balong_ddr3cap_udp_fhd)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
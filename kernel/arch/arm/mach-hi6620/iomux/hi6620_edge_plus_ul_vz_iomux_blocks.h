/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_edge_plus_ul_vz_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_EDGE_PLUS_UL_VZ_IOMUX_BLOCKS_H__
#define __HI6620_EDGE_PLUS_UL_VZ_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_edge_plus_ul_vz_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_edge_plus_ul_vz[] = {
    &GPIO_4_0_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_edge_plus_ul_vz, "block_charger", NORMAL, charger_pins_edge_plus_ul_vz)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static struct block_config charger_config_edge_plus_ul_vz[] = {
    [NORMAL] = {charger_func_normal_edge_plus_ul_vz, charger_pullud_normal_edge_plus_ul_vz, charger_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {charger_func_lowpower_edge_plus_ul_vz, charger_pullud_lowpower_edge_plus_ul_vz, charger_drv_lowpower_edge_plus_ul_vz},

};

/*flash pins */
static struct  iomux_pin *flash_pins_edge_plus_ul_vz[] = {
    &ISP_GPIO5_EDGE_PLUS_UL_VZ, &RF_GPIO_0_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_edge_plus_ul_vz, "block_flash", NORMAL, flash_pins_edge_plus_ul_vz)



/*FLASH*/

static enum lowlayer_func flash_func_normal_edge_plus_ul_vz[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_edge_plus_ul_vz[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_edge_plus_ul_vz[] = {
    [NORMAL] = {flash_func_normal_edge_plus_ul_vz, flash_pullud_normal_edge_plus_ul_vz, flash_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {flash_func_lowpower_edge_plus_ul_vz, flash_pullud_lowpower_edge_plus_ul_vz, flash_drv_lowpower_edge_plus_ul_vz},

};

/*bt pins */
static struct  iomux_pin *bt_pins_edge_plus_ul_vz[] = {
    &UART4_CTS_N_EDGE_PLUS_UL_VZ, &UART4_RTS_N_EDGE_PLUS_UL_VZ, &UART4_RXD_EDGE_PLUS_UL_VZ, &UART4_TXD_EDGE_PLUS_UL_VZ, &GPIO_15_5_EDGE_PLUS_UL_VZ, &GPIO_15_7_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_edge_plus_ul_vz, "block_bt", NORMAL, bt_pins_edge_plus_ul_vz)



/*BT*/

static enum lowlayer_func bt_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_edge_plus_ul_vz[] = {
    [NORMAL] = {bt_func_normal_edge_plus_ul_vz, bt_pullud_normal_edge_plus_ul_vz, bt_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {bt_func_lowpower_edge_plus_ul_vz, bt_pullud_lowpower_edge_plus_ul_vz, bt_drv_lowpower_edge_plus_ul_vz},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_edge_plus_ul_vz[] = {
    &ISP_GPIO1_EDGE_PLUS_UL_VZ, &ISP_GPIO4_EDGE_PLUS_UL_VZ, &ISP_RESETB1_EDGE_PLUS_UL_VZ, &ISP_CCLK1_EDGE_PLUS_UL_VZ, &ISP_SDA1_EDGE_PLUS_UL_VZ, &ISP_SCL1_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_edge_plus_ul_vz, "block_scamera", NORMAL, scamera_pins_edge_plus_ul_vz)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_edge_plus_ul_vz[] = {
    [NORMAL] = {scamera_func_normal_edge_plus_ul_vz, scamera_pullud_normal_edge_plus_ul_vz, scamera_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {scamera_func_lowpower_edge_plus_ul_vz, scamera_pullud_lowpower_edge_plus_ul_vz, scamera_drv_lowpower_edge_plus_ul_vz},

};

/*codec pins */
static struct  iomux_pin *codec_pins_edge_plus_ul_vz[] = {
    &PCM1_XCLK_EDGE_PLUS_UL_VZ, &PCM1_XFS_EDGE_PLUS_UL_VZ, &PCM1_DI_EDGE_PLUS_UL_VZ, &PCM1_DO_EDGE_PLUS_UL_VZ, &I2S_XCLK_EDGE_PLUS_UL_VZ, &I2S_XFS_EDGE_PLUS_UL_VZ, &I2S_DI_EDGE_PLUS_UL_VZ, &I2S_DO_EDGE_PLUS_UL_VZ, &PCM0_XCLK_EDGE_PLUS_UL_VZ, &PCM0_XFS_EDGE_PLUS_UL_VZ, &PCM0_DI_EDGE_PLUS_UL_VZ, &PCM0_DO_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_edge_plus_ul_vz, "block_codec", NORMAL, codec_pins_edge_plus_ul_vz)



/*CODEC*/

static enum lowlayer_func codec_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_edge_plus_ul_vz[] = {
    [NORMAL] = {codec_func_normal_edge_plus_ul_vz, codec_pullud_normal_edge_plus_ul_vz, codec_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {codec_func_lowpower_edge_plus_ul_vz, codec_pullud_lowpower_edge_plus_ul_vz, codec_drv_lowpower_edge_plus_ul_vz},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_edge_plus_ul_vz[] = {
    &HKADC_SSI_EDGE_PLUS_UL_VZ, &AUX_SSI0_EDGE_PLUS_UL_VZ, &AUX_SSI1_EDGE_PLUS_UL_VZ, &GPIO_5_0_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_edge_plus_ul_vz, "block_pmu", NORMAL, pmu_pins_edge_plus_ul_vz)



/*PMU*/

static enum lowlayer_func pmu_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_edge_plus_ul_vz[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_edge_plus_ul_vz[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_edge_plus_ul_vz[] = {
    [NORMAL] = {pmu_func_normal_edge_plus_ul_vz, pmu_pullud_normal_edge_plus_ul_vz, pmu_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {pmu_func_lowpower_edge_plus_ul_vz, pmu_pullud_lowpower_edge_plus_ul_vz, pmu_drv_lowpower_edge_plus_ul_vz},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_edge_plus_ul_vz[] = {
    &EMMC_CLK_EDGE_PLUS_UL_VZ, &EMMC_CMD_EDGE_PLUS_UL_VZ, &EMMC_DATA0_EDGE_PLUS_UL_VZ, &EMMC_DATA1_EDGE_PLUS_UL_VZ, &EMMC_DATA2_EDGE_PLUS_UL_VZ, &EMMC_DATA3_EDGE_PLUS_UL_VZ, &EMMC_DATA4_EDGE_PLUS_UL_VZ, &EMMC_DATA5_EDGE_PLUS_UL_VZ, &EMMC_DATA6_EDGE_PLUS_UL_VZ, &EMMC_DATA7_EDGE_PLUS_UL_VZ, &GPIO_2_3_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_edge_plus_ul_vz, "block_emmc", NORMAL, emmc_pins_edge_plus_ul_vz)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_edge_plus_ul_vz[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_edge_plus_ul_vz[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_edge_plus_ul_vz[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_edge_plus_ul_vz[] = {
    [NORMAL] = {emmc_func_normal_edge_plus_ul_vz, emmc_pullud_normal_edge_plus_ul_vz, emmc_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {emmc_func_lowpower_edge_plus_ul_vz, emmc_pullud_lowpower_edge_plus_ul_vz, emmc_drv_lowpower_edge_plus_ul_vz},

};

/*odt pins */
static struct  iomux_pin *odt_pins_edge_plus_ul_vz[] = {
    &RF_RESET1_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_edge_plus_ul_vz, "block_odt", NORMAL, odt_pins_edge_plus_ul_vz)



/*ODT*/

static enum lowlayer_func odt_func_normal_edge_plus_ul_vz[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_edge_plus_ul_vz[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_edge_plus_ul_vz[] = {
    [NORMAL] = {odt_func_normal_edge_plus_ul_vz, odt_pullud_normal_edge_plus_ul_vz, odt_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {odt_func_lowpower_edge_plus_ul_vz, odt_pullud_lowpower_edge_plus_ul_vz, odt_drv_lowpower_edge_plus_ul_vz},

};

/*rf pins */
static struct  iomux_pin *rf_pins_edge_plus_ul_vz[] = {
    &RF_TCVR_ON0_EDGE_PLUS_UL_VZ, &RF_SSI0_EDGE_PLUS_UL_VZ, &RF_GPIO_2_EDGE_PLUS_UL_VZ, &RF_GPIO_3_EDGE_PLUS_UL_VZ, &RF_GPIO_4_EDGE_PLUS_UL_VZ, &RF_GPIO_5_EDGE_PLUS_UL_VZ, &RF_GPIO_10_EDGE_PLUS_UL_VZ, &RF_GPIO_11_EDGE_PLUS_UL_VZ, &RF_GPIO_13_EDGE_PLUS_UL_VZ, &RF_GPIO_14_EDGE_PLUS_UL_VZ, &RF_GPIO_15_EDGE_PLUS_UL_VZ, &RF_GPIO_16_EDGE_PLUS_UL_VZ, &RF_GPIO_17_EDGE_PLUS_UL_VZ, &RF_GPIO_18_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_edge_plus_ul_vz, "block_rf", NORMAL, rf_pins_edge_plus_ul_vz)



/*RF*/

static enum lowlayer_func rf_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_edge_plus_ul_vz[] = {NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_edge_plus_ul_vz[] = {
    [NORMAL] = {rf_func_normal_edge_plus_ul_vz, rf_pullud_normal_edge_plus_ul_vz, rf_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {rf_func_lowpower_edge_plus_ul_vz, rf_pullud_lowpower_edge_plus_ul_vz, rf_drv_lowpower_edge_plus_ul_vz},

};

/*tp pins */
static struct  iomux_pin *tp_pins_edge_plus_ul_vz[] = {
    &GPIO_18_7_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_edge_plus_ul_vz, "block_tp", NORMAL, tp_pins_edge_plus_ul_vz)



/*TP*/

static enum lowlayer_func tp_func_normal_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_edge_plus_ul_vz[] = {
    [NORMAL] = {tp_func_normal_edge_plus_ul_vz, tp_pullud_normal_edge_plus_ul_vz, tp_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {tp_func_lowpower_edge_plus_ul_vz, tp_pullud_lowpower_edge_plus_ul_vz, tp_drv_lowpower_edge_plus_ul_vz},

};

/*switch pins */
static struct  iomux_pin *switch_pins_edge_plus_ul_vz[] = {
    &GPIO_6_2_EDGE_PLUS_UL_VZ, &GPIO_7_7_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_edge_plus_ul_vz, "block_switch", NORMAL, switch_pins_edge_plus_ul_vz)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_edge_plus_ul_vz[] = {
    [NORMAL] = {switch_func_normal_edge_plus_ul_vz, switch_pullud_normal_edge_plus_ul_vz, switch_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {switch_func_lowpower_edge_plus_ul_vz, switch_pullud_lowpower_edge_plus_ul_vz, switch_drv_lowpower_edge_plus_ul_vz},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_edge_plus_ul_vz[] = {
    &RF_MIPI_CLK0_EDGE_PLUS_UL_VZ, &RF_MIPI_DATA0_EDGE_PLUS_UL_VZ, &APT_PDM0_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_edge_plus_ul_vz, "block_rfpmu", NORMAL, rfpmu_pins_edge_plus_ul_vz)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_edge_plus_ul_vz[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_edge_plus_ul_vz[] = {
    [NORMAL] = {rfpmu_func_normal_edge_plus_ul_vz, rfpmu_pullud_normal_edge_plus_ul_vz, rfpmu_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {rfpmu_func_lowpower_edge_plus_ul_vz, rfpmu_pullud_lowpower_edge_plus_ul_vz, rfpmu_drv_lowpower_edge_plus_ul_vz},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_edge_plus_ul_vz[] = {
    &I2C3_SCL_EDGE_PLUS_UL_VZ, &I2C3_SDA_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_edge_plus_ul_vz, "block_i2c3", NORMAL, i2c3_pins_edge_plus_ul_vz)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_edge_plus_ul_vz[] = {
    [NORMAL] = {i2c3_func_normal_edge_plus_ul_vz, i2c3_pullud_normal_edge_plus_ul_vz, i2c3_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {i2c3_func_lowpower_edge_plus_ul_vz, i2c3_pullud_lowpower_edge_plus_ul_vz, i2c3_drv_lowpower_edge_plus_ul_vz},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_edge_plus_ul_vz[] = {
    &USIM0_CLK_EDGE_PLUS_UL_VZ, &USIM0_DATA_EDGE_PLUS_UL_VZ, &USIM0_RST_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_edge_plus_ul_vz, "block_usim0", NORMAL, usim0_pins_edge_plus_ul_vz)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_edge_plus_ul_vz[] = {
    [NORMAL] = {usim0_func_normal_edge_plus_ul_vz, usim0_pullud_normal_edge_plus_ul_vz, usim0_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {usim0_func_lowpower_edge_plus_ul_vz, usim0_pullud_lowpower_edge_plus_ul_vz, usim0_drv_lowpower_edge_plus_ul_vz},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_edge_plus_ul_vz[] = {
    &ISP_GPIO0_EDGE_PLUS_UL_VZ, &ISP_GPIO2_EDGE_PLUS_UL_VZ, &ISP_GPIO3_EDGE_PLUS_UL_VZ, &ISP_RESETB0_EDGE_PLUS_UL_VZ, &ISP_CCLK0_EDGE_PLUS_UL_VZ, &ISP_SDA0_EDGE_PLUS_UL_VZ, &ISP_SCL0_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_edge_plus_ul_vz, "block_mcamera", NORMAL, mcamera_pins_edge_plus_ul_vz)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_edge_plus_ul_vz[] = {
    [NORMAL] = {mcamera_func_normal_edge_plus_ul_vz, mcamera_pullud_normal_edge_plus_ul_vz, mcamera_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {mcamera_func_lowpower_edge_plus_ul_vz, mcamera_pullud_lowpower_edge_plus_ul_vz, mcamera_drv_lowpower_edge_plus_ul_vz},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_edge_plus_ul_vz[] = {
    &I2C0_SCL_EDGE_PLUS_UL_VZ, &I2C0_SDA_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_edge_plus_ul_vz, "block_i2c0", NORMAL, i2c0_pins_edge_plus_ul_vz)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_edge_plus_ul_vz[] = {
    [NORMAL] = {i2c0_func_normal_edge_plus_ul_vz, i2c0_pullud_normal_edge_plus_ul_vz, i2c0_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {i2c0_func_lowpower_edge_plus_ul_vz, i2c0_pullud_lowpower_edge_plus_ul_vz, i2c0_drv_lowpower_edge_plus_ul_vz},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_edge_plus_ul_vz[] = {
    &I2C1_SCL_EDGE_PLUS_UL_VZ, &I2C1_SDA_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_edge_plus_ul_vz, "block_i2c1", NORMAL, i2c1_pins_edge_plus_ul_vz)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_edge_plus_ul_vz[] = {
    [NORMAL] = {i2c1_func_normal_edge_plus_ul_vz, i2c1_pullud_normal_edge_plus_ul_vz, i2c1_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {i2c1_func_lowpower_edge_plus_ul_vz, i2c1_pullud_lowpower_edge_plus_ul_vz, i2c1_drv_lowpower_edge_plus_ul_vz},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_edge_plus_ul_vz[] = {
    &I2C2_SCL_EDGE_PLUS_UL_VZ, &I2C2_SDA_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_edge_plus_ul_vz, "block_i2c2", NORMAL, i2c2_pins_edge_plus_ul_vz)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_edge_plus_ul_vz[] = {
    [NORMAL] = {i2c2_func_normal_edge_plus_ul_vz, i2c2_pullud_normal_edge_plus_ul_vz, i2c2_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {i2c2_func_lowpower_edge_plus_ul_vz, i2c2_pullud_lowpower_edge_plus_ul_vz, i2c2_drv_lowpower_edge_plus_ul_vz},

};

/*gps pins */
static struct  iomux_pin *gps_pins_edge_plus_ul_vz[] = {
    &GPIO_6_1_EDGE_PLUS_UL_VZ, &RF_GPIO_1_EDGE_PLUS_UL_VZ, &UART3_CTS_N_EDGE_PLUS_UL_VZ, &UART3_RTS_N_EDGE_PLUS_UL_VZ, &UART3_RXD_EDGE_PLUS_UL_VZ, &UART3_TXD_EDGE_PLUS_UL_VZ, &GPS_CLK_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_edge_plus_ul_vz, "block_gps", NORMAL, gps_pins_edge_plus_ul_vz)



/*GPS*/

static enum lowlayer_func gps_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_edge_plus_ul_vz[] = {
    [NORMAL] = {gps_func_normal_edge_plus_ul_vz, gps_pullud_normal_edge_plus_ul_vz, gps_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {gps_func_lowpower_edge_plus_ul_vz, gps_pullud_lowpower_edge_plus_ul_vz, gps_drv_lowpower_edge_plus_ul_vz},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_edge_plus_ul_vz[] = {
    &TCXO0_AFC_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_edge_plus_ul_vz, "block_tcxo", NORMAL, tcxo_pins_edge_plus_ul_vz)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_edge_plus_ul_vz[] = {NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_edge_plus_ul_vz[] = {FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_edge_plus_ul_vz[] = {PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static struct block_config tcxo_config_edge_plus_ul_vz[] = {
    [NORMAL] = {tcxo_func_normal_edge_plus_ul_vz, tcxo_pullud_normal_edge_plus_ul_vz, tcxo_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {tcxo_func_lowpower_edge_plus_ul_vz, tcxo_pullud_lowpower_edge_plus_ul_vz, tcxo_drv_lowpower_edge_plus_ul_vz},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_edge_plus_ul_vz[] = {
    &GPIO_7_5_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_edge_plus_ul_vz, "block_rfant", NORMAL, rfant_pins_edge_plus_ul_vz)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_edge_plus_ul_vz[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_edge_plus_ul_vz[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_edge_plus_ul_vz[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_edge_plus_ul_vz[] = {
    [NORMAL] = {rfant_func_normal_edge_plus_ul_vz, rfant_pullud_normal_edge_plus_ul_vz, rfant_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {rfant_func_lowpower_edge_plus_ul_vz, rfant_pullud_lowpower_edge_plus_ul_vz, rfant_drv_lowpower_edge_plus_ul_vz},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_edge_plus_ul_vz[] = {
    &GPIO_2_2_EDGE_PLUS_UL_VZ, &SDIO_DATA3_EDGE_PLUS_UL_VZ, &SDIO_DATA2_EDGE_PLUS_UL_VZ, &SDIO_DATA1_EDGE_PLUS_UL_VZ, &SDIO_DATA0_EDGE_PLUS_UL_VZ, &SDIO_CMD_EDGE_PLUS_UL_VZ, &SDIO_CLK_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_edge_plus_ul_vz, "block_wifi", NORMAL, wifi_pins_edge_plus_ul_vz)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_edge_plus_ul_vz[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config wifi_config_edge_plus_ul_vz[] = {
    [NORMAL] = {wifi_func_normal_edge_plus_ul_vz, wifi_pullud_normal_edge_plus_ul_vz, wifi_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {wifi_func_lowpower_edge_plus_ul_vz, wifi_pullud_lowpower_edge_plus_ul_vz, wifi_drv_lowpower_edge_plus_ul_vz},

};

/*boot pins */
static struct  iomux_pin *boot_pins_edge_plus_ul_vz[] = {
    &BOOT_SEL_EDGE_PLUS_UL_VZ, &GPIO_5_1_EDGE_PLUS_UL_VZ, &GPIO_5_2_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_edge_plus_ul_vz, "block_boot", NORMAL, boot_pins_edge_plus_ul_vz)



/*BOOT*/

static enum lowlayer_func boot_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC4, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_normal_edge_plus_ul_vz[] = {PULLUP, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC4, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_edge_plus_ul_vz[] = {PULLUP, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_edge_plus_ul_vz[] = {
    [NORMAL] = {boot_func_normal_edge_plus_ul_vz, boot_pullud_normal_edge_plus_ul_vz, boot_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {boot_func_lowpower_edge_plus_ul_vz, boot_pullud_lowpower_edge_plus_ul_vz, boot_drv_lowpower_edge_plus_ul_vz},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_edge_plus_ul_vz[] = {
    &PWM_OUT1_EDGE_PLUS_UL_VZ, &GPIO_4_6_EDGE_PLUS_UL_VZ, &GPIO_4_7_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_edge_plus_ul_vz, "block_lcd", NORMAL, lcd_pins_edge_plus_ul_vz)



/*LCD*/

static enum lowlayer_func lcd_func_normal_edge_plus_ul_vz[] = {FUNC2, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown lcd_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_edge_plus_ul_vz[] = {FUNC2, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_edge_plus_ul_vz[] = {
    [NORMAL] = {lcd_func_normal_edge_plus_ul_vz, lcd_pullud_normal_edge_plus_ul_vz, lcd_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {lcd_func_lowpower_edge_plus_ul_vz, lcd_pullud_lowpower_edge_plus_ul_vz, lcd_drv_lowpower_edge_plus_ul_vz},

};

/*key pins */
static struct  iomux_pin *key_pins_edge_plus_ul_vz[] = {
    &GPIO_4_2_EDGE_PLUS_UL_VZ, &GPIO_4_3_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_edge_plus_ul_vz, "block_key", NORMAL, key_pins_edge_plus_ul_vz)



/*KEY*/

static enum lowlayer_func key_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_edge_plus_ul_vz[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_edge_plus_ul_vz[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_edge_plus_ul_vz[] = {
    [NORMAL] = {key_func_normal_edge_plus_ul_vz, key_pullud_normal_edge_plus_ul_vz, key_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {key_func_lowpower_edge_plus_ul_vz, key_pullud_lowpower_edge_plus_ul_vz, key_drv_lowpower_edge_plus_ul_vz},

};

/*test pins */
static struct  iomux_pin *test_pins_edge_plus_ul_vz[] = {
    &UART0_RXD_EDGE_PLUS_UL_VZ, &UART0_TXD_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_edge_plus_ul_vz, "block_test", NORMAL, test_pins_edge_plus_ul_vz)



/*TEST*/

static enum lowlayer_func test_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_edge_plus_ul_vz[] = {
    [NORMAL] = {test_func_normal_edge_plus_ul_vz, test_pullud_normal_edge_plus_ul_vz, test_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {test_func_lowpower_edge_plus_ul_vz, test_pullud_lowpower_edge_plus_ul_vz, test_drv_lowpower_edge_plus_ul_vz},

};

/*sd pins */
static struct  iomux_pin *sd_pins_edge_plus_ul_vz[] = {
    &SD_CLK_EDGE_PLUS_UL_VZ, &SD_CMD_EDGE_PLUS_UL_VZ, &SD_DATA0_EDGE_PLUS_UL_VZ, &SD_DATA1_EDGE_PLUS_UL_VZ, &SD_DATA2_EDGE_PLUS_UL_VZ, &SD_DATA3_EDGE_PLUS_UL_VZ,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_edge_plus_ul_vz, "block_sd", NORMAL, sd_pins_edge_plus_ul_vz)



/*SD*/

static enum lowlayer_func sd_func_normal_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_edge_plus_ul_vz[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_edge_plus_ul_vz[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_edge_plus_ul_vz[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_edge_plus_ul_vz[] = {
    [NORMAL] = {sd_func_normal_edge_plus_ul_vz, sd_pullud_normal_edge_plus_ul_vz, sd_drv_normal_edge_plus_ul_vz},
    [LOWPOWER] = {sd_func_lowpower_edge_plus_ul_vz, sd_pullud_lowpower_edge_plus_ul_vz, sd_drv_lowpower_edge_plus_ul_vz},

};

struct iomux_block_table block_config_table_edge_plus_ul_vz[] = {
    BLOCK_CONFIG("block_charger", &block_charger_edge_plus_ul_vz, charger_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_flash", &block_flash_edge_plus_ul_vz, flash_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_bt", &block_bt_edge_plus_ul_vz, bt_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_scamera", &block_scamera_edge_plus_ul_vz, scamera_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_codec", &block_codec_edge_plus_ul_vz, codec_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_pmu", &block_pmu_edge_plus_ul_vz, pmu_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_emmc", &block_emmc_edge_plus_ul_vz, emmc_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_odt", &block_odt_edge_plus_ul_vz, odt_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_rf", &block_rf_edge_plus_ul_vz, rf_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_tp", &block_tp_edge_plus_ul_vz, tp_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_switch", &block_switch_edge_plus_ul_vz, switch_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_edge_plus_ul_vz, rfpmu_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_edge_plus_ul_vz, i2c3_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_usim0", &block_usim0_edge_plus_ul_vz, usim0_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_edge_plus_ul_vz, mcamera_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_edge_plus_ul_vz, i2c0_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_edge_plus_ul_vz, i2c1_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_edge_plus_ul_vz, i2c2_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_gps", &block_gps_edge_plus_ul_vz, gps_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_edge_plus_ul_vz, tcxo_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_rfant", &block_rfant_edge_plus_ul_vz, rfant_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_wifi", &block_wifi_edge_plus_ul_vz, wifi_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_boot", &block_boot_edge_plus_ul_vz, boot_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_lcd", &block_lcd_edge_plus_ul_vz, lcd_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_key", &block_key_edge_plus_ul_vz, key_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_test", &block_test_edge_plus_ul_vz, test_config_edge_plus_ul_vz)
    BLOCK_CONFIG("block_sd", &block_sd_edge_plus_ul_vz, sd_config_edge_plus_ul_vz)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
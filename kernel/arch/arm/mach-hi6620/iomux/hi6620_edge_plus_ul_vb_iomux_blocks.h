/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_edge_plus_ul_vb_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_EDGE_PLUS_UL_VB_IOMUX_BLOCKS_H__
#define __HI6620_EDGE_PLUS_UL_VB_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_edge_plus_ul_vb_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_edge_plus_ul_vb[] = {
    &GPIO_4_0_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_edge_plus_ul_vb, "block_charger", NORMAL, charger_pins_edge_plus_ul_vb)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static struct block_config charger_config_edge_plus_ul_vb[] = {
    [NORMAL] = {charger_func_normal_edge_plus_ul_vb, charger_pullud_normal_edge_plus_ul_vb, charger_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {charger_func_lowpower_edge_plus_ul_vb, charger_pullud_lowpower_edge_plus_ul_vb, charger_drv_lowpower_edge_plus_ul_vb},

};

/*flash pins */
static struct  iomux_pin *flash_pins_edge_plus_ul_vb[] = {
    &ISP_GPIO5_EDGE_PLUS_UL_VB, &RF_GPIO_20_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_edge_plus_ul_vb, "block_flash", NORMAL, flash_pins_edge_plus_ul_vb)



/*FLASH*/

static enum lowlayer_func flash_func_normal_edge_plus_ul_vb[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_edge_plus_ul_vb[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_edge_plus_ul_vb[] = {
    [NORMAL] = {flash_func_normal_edge_plus_ul_vb, flash_pullud_normal_edge_plus_ul_vb, flash_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {flash_func_lowpower_edge_plus_ul_vb, flash_pullud_lowpower_edge_plus_ul_vb, flash_drv_lowpower_edge_plus_ul_vb},

};

/*bt pins */
static struct  iomux_pin *bt_pins_edge_plus_ul_vb[] = {
    &UART4_CTS_N_EDGE_PLUS_UL_VB, &UART4_RTS_N_EDGE_PLUS_UL_VB, &UART4_RXD_EDGE_PLUS_UL_VB, &UART4_TXD_EDGE_PLUS_UL_VB, &GPIO_15_7_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_edge_plus_ul_vb, "block_bt", NORMAL, bt_pins_edge_plus_ul_vb)



/*BT*/

static enum lowlayer_func bt_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_edge_plus_ul_vb[] = {
    [NORMAL] = {bt_func_normal_edge_plus_ul_vb, bt_pullud_normal_edge_plus_ul_vb, bt_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {bt_func_lowpower_edge_plus_ul_vb, bt_pullud_lowpower_edge_plus_ul_vb, bt_drv_lowpower_edge_plus_ul_vb},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_edge_plus_ul_vb[] = {
    &ISP_GPIO1_EDGE_PLUS_UL_VB, &ISP_GPIO4_EDGE_PLUS_UL_VB, &ISP_RESETB1_EDGE_PLUS_UL_VB, &ISP_CCLK1_EDGE_PLUS_UL_VB, &ISP_SDA1_EDGE_PLUS_UL_VB, &ISP_SCL1_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_edge_plus_ul_vb, "block_scamera", NORMAL, scamera_pins_edge_plus_ul_vb)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_edge_plus_ul_vb[] = {
    [NORMAL] = {scamera_func_normal_edge_plus_ul_vb, scamera_pullud_normal_edge_plus_ul_vb, scamera_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {scamera_func_lowpower_edge_plus_ul_vb, scamera_pullud_lowpower_edge_plus_ul_vb, scamera_drv_lowpower_edge_plus_ul_vb},

};

/*codec pins */
static struct  iomux_pin *codec_pins_edge_plus_ul_vb[] = {
    &PCM1_XCLK_EDGE_PLUS_UL_VB, &PCM1_XFS_EDGE_PLUS_UL_VB, &PCM1_DI_EDGE_PLUS_UL_VB, &PCM1_DO_EDGE_PLUS_UL_VB, &I2S_XCLK_EDGE_PLUS_UL_VB, &I2S_XFS_EDGE_PLUS_UL_VB, &I2S_DI_EDGE_PLUS_UL_VB, &I2S_DO_EDGE_PLUS_UL_VB, &PCM0_XCLK_EDGE_PLUS_UL_VB, &PCM0_XFS_EDGE_PLUS_UL_VB, &PCM0_DI_EDGE_PLUS_UL_VB, &PCM0_DO_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_edge_plus_ul_vb, "block_codec", NORMAL, codec_pins_edge_plus_ul_vb)



/*CODEC*/

static enum lowlayer_func codec_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_edge_plus_ul_vb[] = {
    [NORMAL] = {codec_func_normal_edge_plus_ul_vb, codec_pullud_normal_edge_plus_ul_vb, codec_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {codec_func_lowpower_edge_plus_ul_vb, codec_pullud_lowpower_edge_plus_ul_vb, codec_drv_lowpower_edge_plus_ul_vb},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_edge_plus_ul_vb[] = {
    &HKADC_SSI_EDGE_PLUS_UL_VB, &AUX_SSI0_EDGE_PLUS_UL_VB, &AUX_SSI1_EDGE_PLUS_UL_VB, &GPIO_5_0_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_edge_plus_ul_vb, "block_pmu", NORMAL, pmu_pins_edge_plus_ul_vb)



/*PMU*/

static enum lowlayer_func pmu_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_edge_plus_ul_vb[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_edge_plus_ul_vb[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_edge_plus_ul_vb[] = {
    [NORMAL] = {pmu_func_normal_edge_plus_ul_vb, pmu_pullud_normal_edge_plus_ul_vb, pmu_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {pmu_func_lowpower_edge_plus_ul_vb, pmu_pullud_lowpower_edge_plus_ul_vb, pmu_drv_lowpower_edge_plus_ul_vb},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_edge_plus_ul_vb[] = {
    &EMMC_CLK_EDGE_PLUS_UL_VB, &EMMC_CMD_EDGE_PLUS_UL_VB, &EMMC_DATA0_EDGE_PLUS_UL_VB, &EMMC_DATA1_EDGE_PLUS_UL_VB, &EMMC_DATA2_EDGE_PLUS_UL_VB, &EMMC_DATA3_EDGE_PLUS_UL_VB, &EMMC_DATA4_EDGE_PLUS_UL_VB, &EMMC_DATA5_EDGE_PLUS_UL_VB, &EMMC_DATA6_EDGE_PLUS_UL_VB, &EMMC_DATA7_EDGE_PLUS_UL_VB, &GPIO_2_3_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_edge_plus_ul_vb, "block_emmc", NORMAL, emmc_pins_edge_plus_ul_vb)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_edge_plus_ul_vb[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_edge_plus_ul_vb[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_edge_plus_ul_vb[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_edge_plus_ul_vb[] = {
    [NORMAL] = {emmc_func_normal_edge_plus_ul_vb, emmc_pullud_normal_edge_plus_ul_vb, emmc_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {emmc_func_lowpower_edge_plus_ul_vb, emmc_pullud_lowpower_edge_plus_ul_vb, emmc_drv_lowpower_edge_plus_ul_vb},

};

/*odt pins */
static struct  iomux_pin *odt_pins_edge_plus_ul_vb[] = {
    &RF_RESET1_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_edge_plus_ul_vb, "block_odt", NORMAL, odt_pins_edge_plus_ul_vb)



/*ODT*/

static enum lowlayer_func odt_func_normal_edge_plus_ul_vb[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_edge_plus_ul_vb[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_edge_plus_ul_vb[] = {
    [NORMAL] = {odt_func_normal_edge_plus_ul_vb, odt_pullud_normal_edge_plus_ul_vb, odt_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {odt_func_lowpower_edge_plus_ul_vb, odt_pullud_lowpower_edge_plus_ul_vb, odt_drv_lowpower_edge_plus_ul_vb},

};

/*rf pins */
static struct  iomux_pin *rf_pins_edge_plus_ul_vb[] = {
    &RF_TCVR_ON0_EDGE_PLUS_UL_VB, &RF_SSI0_EDGE_PLUS_UL_VB, &RF_GPIO_2_EDGE_PLUS_UL_VB, &RF_GPIO_3_EDGE_PLUS_UL_VB, &RF_GPIO_4_EDGE_PLUS_UL_VB, &RF_GPIO_5_EDGE_PLUS_UL_VB, &RF_GPIO_10_EDGE_PLUS_UL_VB, &RF_GPIO_11_EDGE_PLUS_UL_VB, &RF_GPIO_13_EDGE_PLUS_UL_VB, &RF_GPIO_14_EDGE_PLUS_UL_VB, &RF_GPIO_15_EDGE_PLUS_UL_VB, &RF_GPIO_16_EDGE_PLUS_UL_VB, &RF_GPIO_17_EDGE_PLUS_UL_VB, &RF_GPIO_18_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_edge_plus_ul_vb, "block_rf", NORMAL, rf_pins_edge_plus_ul_vb)



/*RF*/

static enum lowlayer_func rf_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_edge_plus_ul_vb[] = {NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_edge_plus_ul_vb[] = {
    [NORMAL] = {rf_func_normal_edge_plus_ul_vb, rf_pullud_normal_edge_plus_ul_vb, rf_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {rf_func_lowpower_edge_plus_ul_vb, rf_pullud_lowpower_edge_plus_ul_vb, rf_drv_lowpower_edge_plus_ul_vb},

};

/*tp pins */
static struct  iomux_pin *tp_pins_edge_plus_ul_vb[] = {
    &GPIO_18_7_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_edge_plus_ul_vb, "block_tp", NORMAL, tp_pins_edge_plus_ul_vb)



/*TP*/

static enum lowlayer_func tp_func_normal_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_edge_plus_ul_vb[] = {
    [NORMAL] = {tp_func_normal_edge_plus_ul_vb, tp_pullud_normal_edge_plus_ul_vb, tp_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {tp_func_lowpower_edge_plus_ul_vb, tp_pullud_lowpower_edge_plus_ul_vb, tp_drv_lowpower_edge_plus_ul_vb},

};

/*switch pins */
static struct  iomux_pin *switch_pins_edge_plus_ul_vb[] = {
    &GPIO_6_2_EDGE_PLUS_UL_VB, &GPIO_7_7_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_edge_plus_ul_vb, "block_switch", NORMAL, switch_pins_edge_plus_ul_vb)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_edge_plus_ul_vb[] = {
    [NORMAL] = {switch_func_normal_edge_plus_ul_vb, switch_pullud_normal_edge_plus_ul_vb, switch_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {switch_func_lowpower_edge_plus_ul_vb, switch_pullud_lowpower_edge_plus_ul_vb, switch_drv_lowpower_edge_plus_ul_vb},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_edge_plus_ul_vb[] = {
    &RF_MIPI_CLK0_EDGE_PLUS_UL_VB, &RF_MIPI_DATA0_EDGE_PLUS_UL_VB, &APT_PDM0_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_edge_plus_ul_vb, "block_rfpmu", NORMAL, rfpmu_pins_edge_plus_ul_vb)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_edge_plus_ul_vb[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_edge_plus_ul_vb[] = {
    [NORMAL] = {rfpmu_func_normal_edge_plus_ul_vb, rfpmu_pullud_normal_edge_plus_ul_vb, rfpmu_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {rfpmu_func_lowpower_edge_plus_ul_vb, rfpmu_pullud_lowpower_edge_plus_ul_vb, rfpmu_drv_lowpower_edge_plus_ul_vb},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_edge_plus_ul_vb[] = {
    &I2C3_SCL_EDGE_PLUS_UL_VB, &I2C3_SDA_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_edge_plus_ul_vb, "block_i2c3", NORMAL, i2c3_pins_edge_plus_ul_vb)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_edge_plus_ul_vb[] = {
    [NORMAL] = {i2c3_func_normal_edge_plus_ul_vb, i2c3_pullud_normal_edge_plus_ul_vb, i2c3_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {i2c3_func_lowpower_edge_plus_ul_vb, i2c3_pullud_lowpower_edge_plus_ul_vb, i2c3_drv_lowpower_edge_plus_ul_vb},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_edge_plus_ul_vb[] = {
    &USIM0_CLK_EDGE_PLUS_UL_VB, &USIM0_DATA_EDGE_PLUS_UL_VB, &USIM0_RST_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_edge_plus_ul_vb, "block_usim0", NORMAL, usim0_pins_edge_plus_ul_vb)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_edge_plus_ul_vb[] = {
    [NORMAL] = {usim0_func_normal_edge_plus_ul_vb, usim0_pullud_normal_edge_plus_ul_vb, usim0_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {usim0_func_lowpower_edge_plus_ul_vb, usim0_pullud_lowpower_edge_plus_ul_vb, usim0_drv_lowpower_edge_plus_ul_vb},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_edge_plus_ul_vb[] = {
    &ISP_GPIO0_EDGE_PLUS_UL_VB, &ISP_GPIO2_EDGE_PLUS_UL_VB, &ISP_GPIO3_EDGE_PLUS_UL_VB, &ISP_RESETB0_EDGE_PLUS_UL_VB, &ISP_CCLK0_EDGE_PLUS_UL_VB, &ISP_SDA0_EDGE_PLUS_UL_VB, &ISP_SCL0_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_edge_plus_ul_vb, "block_mcamera", NORMAL, mcamera_pins_edge_plus_ul_vb)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_edge_plus_ul_vb[] = {
    [NORMAL] = {mcamera_func_normal_edge_plus_ul_vb, mcamera_pullud_normal_edge_plus_ul_vb, mcamera_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {mcamera_func_lowpower_edge_plus_ul_vb, mcamera_pullud_lowpower_edge_plus_ul_vb, mcamera_drv_lowpower_edge_plus_ul_vb},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_edge_plus_ul_vb[] = {
    &I2C0_SCL_EDGE_PLUS_UL_VB, &I2C0_SDA_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_edge_plus_ul_vb, "block_i2c0", NORMAL, i2c0_pins_edge_plus_ul_vb)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_edge_plus_ul_vb[] = {
    [NORMAL] = {i2c0_func_normal_edge_plus_ul_vb, i2c0_pullud_normal_edge_plus_ul_vb, i2c0_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {i2c0_func_lowpower_edge_plus_ul_vb, i2c0_pullud_lowpower_edge_plus_ul_vb, i2c0_drv_lowpower_edge_plus_ul_vb},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_edge_plus_ul_vb[] = {
    &I2C1_SCL_EDGE_PLUS_UL_VB, &I2C1_SDA_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_edge_plus_ul_vb, "block_i2c1", NORMAL, i2c1_pins_edge_plus_ul_vb)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_edge_plus_ul_vb[] = {
    [NORMAL] = {i2c1_func_normal_edge_plus_ul_vb, i2c1_pullud_normal_edge_plus_ul_vb, i2c1_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {i2c1_func_lowpower_edge_plus_ul_vb, i2c1_pullud_lowpower_edge_plus_ul_vb, i2c1_drv_lowpower_edge_plus_ul_vb},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_edge_plus_ul_vb[] = {
    &I2C2_SCL_EDGE_PLUS_UL_VB, &I2C2_SDA_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_edge_plus_ul_vb, "block_i2c2", NORMAL, i2c2_pins_edge_plus_ul_vb)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_edge_plus_ul_vb[] = {
    [NORMAL] = {i2c2_func_normal_edge_plus_ul_vb, i2c2_pullud_normal_edge_plus_ul_vb, i2c2_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {i2c2_func_lowpower_edge_plus_ul_vb, i2c2_pullud_lowpower_edge_plus_ul_vb, i2c2_drv_lowpower_edge_plus_ul_vb},

};

/*gps pins */
static struct  iomux_pin *gps_pins_edge_plus_ul_vb[] = {
    &RF_GPIO_1_EDGE_PLUS_UL_VB, &UART3_CTS_N_EDGE_PLUS_UL_VB, &UART3_RTS_N_EDGE_PLUS_UL_VB, &UART3_RXD_EDGE_PLUS_UL_VB, &UART3_TXD_EDGE_PLUS_UL_VB, &GPS_CLK_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_edge_plus_ul_vb, "block_gps", NORMAL, gps_pins_edge_plus_ul_vb)



/*GPS*/

static enum lowlayer_func gps_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_edge_plus_ul_vb[] = {
    [NORMAL] = {gps_func_normal_edge_plus_ul_vb, gps_pullud_normal_edge_plus_ul_vb, gps_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {gps_func_lowpower_edge_plus_ul_vb, gps_pullud_lowpower_edge_plus_ul_vb, gps_drv_lowpower_edge_plus_ul_vb},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_edge_plus_ul_vb[] = {
    &TCXO0_AFC_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_edge_plus_ul_vb, "block_tcxo", NORMAL, tcxo_pins_edge_plus_ul_vb)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_edge_plus_ul_vb[] = {NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_edge_plus_ul_vb[] = {FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_edge_plus_ul_vb[] = {PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static struct block_config tcxo_config_edge_plus_ul_vb[] = {
    [NORMAL] = {tcxo_func_normal_edge_plus_ul_vb, tcxo_pullud_normal_edge_plus_ul_vb, tcxo_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {tcxo_func_lowpower_edge_plus_ul_vb, tcxo_pullud_lowpower_edge_plus_ul_vb, tcxo_drv_lowpower_edge_plus_ul_vb},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_edge_plus_ul_vb[] = {
    &GPIO_7_5_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_edge_plus_ul_vb, "block_rfant", NORMAL, rfant_pins_edge_plus_ul_vb)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_edge_plus_ul_vb[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_edge_plus_ul_vb[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_edge_plus_ul_vb[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_edge_plus_ul_vb[] = {
    [NORMAL] = {rfant_func_normal_edge_plus_ul_vb, rfant_pullud_normal_edge_plus_ul_vb, rfant_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {rfant_func_lowpower_edge_plus_ul_vb, rfant_pullud_lowpower_edge_plus_ul_vb, rfant_drv_lowpower_edge_plus_ul_vb},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_edge_plus_ul_vb[] = {
    &SDIO_DATA3_EDGE_PLUS_UL_VB, &SDIO_DATA2_EDGE_PLUS_UL_VB, &SDIO_DATA1_EDGE_PLUS_UL_VB, &SDIO_DATA0_EDGE_PLUS_UL_VB, &SDIO_CMD_EDGE_PLUS_UL_VB, &SDIO_CLK_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_edge_plus_ul_vb, "block_wifi", NORMAL, wifi_pins_edge_plus_ul_vb)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_edge_plus_ul_vb[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_edge_plus_ul_vb[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_edge_plus_ul_vb[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config wifi_config_edge_plus_ul_vb[] = {
    [NORMAL] = {wifi_func_normal_edge_plus_ul_vb, wifi_pullud_normal_edge_plus_ul_vb, wifi_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {wifi_func_lowpower_edge_plus_ul_vb, wifi_pullud_lowpower_edge_plus_ul_vb, wifi_drv_lowpower_edge_plus_ul_vb},

};

/*boot pins */
static struct  iomux_pin *boot_pins_edge_plus_ul_vb[] = {
    &BOOT_SEL_EDGE_PLUS_UL_VB, &GPIO_5_1_EDGE_PLUS_UL_VB, &GPIO_5_2_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_edge_plus_ul_vb, "block_boot", NORMAL, boot_pins_edge_plus_ul_vb)



/*BOOT*/

static enum lowlayer_func boot_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC4, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_normal_edge_plus_ul_vb[] = {PULLUP, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC4, FUNC4,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_edge_plus_ul_vb[] = {PULLUP, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_edge_plus_ul_vb[] = {
    [NORMAL] = {boot_func_normal_edge_plus_ul_vb, boot_pullud_normal_edge_plus_ul_vb, boot_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {boot_func_lowpower_edge_plus_ul_vb, boot_pullud_lowpower_edge_plus_ul_vb, boot_drv_lowpower_edge_plus_ul_vb},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_edge_plus_ul_vb[] = {
    &PWM_OUT1_EDGE_PLUS_UL_VB, &GPIO_4_6_EDGE_PLUS_UL_VB, &GPIO_4_7_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_edge_plus_ul_vb, "block_lcd", NORMAL, lcd_pins_edge_plus_ul_vb)



/*LCD*/

static enum lowlayer_func lcd_func_normal_edge_plus_ul_vb[] = {FUNC2, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown lcd_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_edge_plus_ul_vb[] = {FUNC2, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_edge_plus_ul_vb[] = {
    [NORMAL] = {lcd_func_normal_edge_plus_ul_vb, lcd_pullud_normal_edge_plus_ul_vb, lcd_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {lcd_func_lowpower_edge_plus_ul_vb, lcd_pullud_lowpower_edge_plus_ul_vb, lcd_drv_lowpower_edge_plus_ul_vb},

};

/*key pins */
static struct  iomux_pin *key_pins_edge_plus_ul_vb[] = {
    &GPIO_4_2_EDGE_PLUS_UL_VB, &GPIO_4_3_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_edge_plus_ul_vb, "block_key", NORMAL, key_pins_edge_plus_ul_vb)



/*KEY*/

static enum lowlayer_func key_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_edge_plus_ul_vb[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_edge_plus_ul_vb[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_edge_plus_ul_vb[] = {
    [NORMAL] = {key_func_normal_edge_plus_ul_vb, key_pullud_normal_edge_plus_ul_vb, key_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {key_func_lowpower_edge_plus_ul_vb, key_pullud_lowpower_edge_plus_ul_vb, key_drv_lowpower_edge_plus_ul_vb},

};

/*test pins */
static struct  iomux_pin *test_pins_edge_plus_ul_vb[] = {
    &UART0_RXD_EDGE_PLUS_UL_VB, &UART0_TXD_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_edge_plus_ul_vb, "block_test", NORMAL, test_pins_edge_plus_ul_vb)



/*TEST*/

static enum lowlayer_func test_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_edge_plus_ul_vb[] = {
    [NORMAL] = {test_func_normal_edge_plus_ul_vb, test_pullud_normal_edge_plus_ul_vb, test_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {test_func_lowpower_edge_plus_ul_vb, test_pullud_lowpower_edge_plus_ul_vb, test_drv_lowpower_edge_plus_ul_vb},

};

/*sd pins */
static struct  iomux_pin *sd_pins_edge_plus_ul_vb[] = {
    &SD_CLK_EDGE_PLUS_UL_VB, &SD_CMD_EDGE_PLUS_UL_VB, &SD_DATA0_EDGE_PLUS_UL_VB, &SD_DATA1_EDGE_PLUS_UL_VB, &SD_DATA2_EDGE_PLUS_UL_VB, &SD_DATA3_EDGE_PLUS_UL_VB,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_edge_plus_ul_vb, "block_sd", NORMAL, sd_pins_edge_plus_ul_vb)



/*SD*/

static enum lowlayer_func sd_func_normal_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_edge_plus_ul_vb[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_edge_plus_ul_vb[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_edge_plus_ul_vb[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_edge_plus_ul_vb[] = {
    [NORMAL] = {sd_func_normal_edge_plus_ul_vb, sd_pullud_normal_edge_plus_ul_vb, sd_drv_normal_edge_plus_ul_vb},
    [LOWPOWER] = {sd_func_lowpower_edge_plus_ul_vb, sd_pullud_lowpower_edge_plus_ul_vb, sd_drv_lowpower_edge_plus_ul_vb},

};

struct iomux_block_table block_config_table_edge_plus_ul_vb[] = {
    BLOCK_CONFIG("block_charger", &block_charger_edge_plus_ul_vb, charger_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_flash", &block_flash_edge_plus_ul_vb, flash_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_bt", &block_bt_edge_plus_ul_vb, bt_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_scamera", &block_scamera_edge_plus_ul_vb, scamera_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_codec", &block_codec_edge_plus_ul_vb, codec_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_pmu", &block_pmu_edge_plus_ul_vb, pmu_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_emmc", &block_emmc_edge_plus_ul_vb, emmc_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_odt", &block_odt_edge_plus_ul_vb, odt_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_rf", &block_rf_edge_plus_ul_vb, rf_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_tp", &block_tp_edge_plus_ul_vb, tp_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_switch", &block_switch_edge_plus_ul_vb, switch_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_edge_plus_ul_vb, rfpmu_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_edge_plus_ul_vb, i2c3_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_usim0", &block_usim0_edge_plus_ul_vb, usim0_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_edge_plus_ul_vb, mcamera_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_edge_plus_ul_vb, i2c0_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_edge_plus_ul_vb, i2c1_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_edge_plus_ul_vb, i2c2_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_gps", &block_gps_edge_plus_ul_vb, gps_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_edge_plus_ul_vb, tcxo_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_rfant", &block_rfant_edge_plus_ul_vb, rfant_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_wifi", &block_wifi_edge_plus_ul_vb, wifi_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_boot", &block_boot_edge_plus_ul_vb, boot_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_lcd", &block_lcd_edge_plus_ul_vb, lcd_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_key", &block_key_edge_plus_ul_vb, key_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_test", &block_test_edge_plus_ul_vb, test_config_edge_plus_ul_vb)
    BLOCK_CONFIG("block_sd", &block_sd_edge_plus_ul_vb, sd_config_edge_plus_ul_vb)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
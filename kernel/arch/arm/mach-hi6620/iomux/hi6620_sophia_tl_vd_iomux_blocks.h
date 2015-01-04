/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_sophia_tl_vd_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_SOPHIA_TL_VD_IOMUX_BLOCKS_H__
#define __HI6620_SOPHIA_TL_VD_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_sophia_tl_vd_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_sophia_tl_vd[] = {
    &GPIO_4_0_SOPHIA_TL_VD, &GPIO_4_1_SOPHIA_TL_VD, &UART2_RTS_N_SOPHIA_TL_VD,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_sophia_tl_vd, "block_charger", NORMAL, charger_pins_sophia_tl_vd)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_sophia_tl_vd[] = {
    [NORMAL] = {charger_func_normal_sophia_tl_vd, charger_pullud_normal_sophia_tl_vd, charger_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {charger_func_lowpower_sophia_tl_vd, charger_pullud_lowpower_sophia_tl_vd, charger_drv_lowpower_sophia_tl_vd},

};

/*flash pins */
static struct  iomux_pin *flash_pins_sophia_tl_vd[] = {
    &ISP_GPIO5_SOPHIA_TL_VD, &RF_GPIO_20_SOPHIA_TL_VD,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_sophia_tl_vd, "block_flash", NORMAL, flash_pins_sophia_tl_vd)



/*FLASH*/

static enum lowlayer_func flash_func_normal_sophia_tl_vd[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_sophia_tl_vd[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_sophia_tl_vd[] = {
    [NORMAL] = {flash_func_normal_sophia_tl_vd, flash_pullud_normal_sophia_tl_vd, flash_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {flash_func_lowpower_sophia_tl_vd, flash_pullud_lowpower_sophia_tl_vd, flash_drv_lowpower_sophia_tl_vd},

};

/*bt pins */
static struct  iomux_pin *bt_pins_sophia_tl_vd[] = {
    &UART4_CTS_N_SOPHIA_TL_VD, &UART4_RTS_N_SOPHIA_TL_VD, &UART4_RXD_SOPHIA_TL_VD, &UART4_TXD_SOPHIA_TL_VD, &GPIO_15_7_SOPHIA_TL_VD,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_sophia_tl_vd, "block_bt", NORMAL, bt_pins_sophia_tl_vd)



/*BT*/

static enum lowlayer_func bt_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_sophia_tl_vd[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_sophia_tl_vd[] = {
    [NORMAL] = {bt_func_normal_sophia_tl_vd, bt_pullud_normal_sophia_tl_vd, bt_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {bt_func_lowpower_sophia_tl_vd, bt_pullud_lowpower_sophia_tl_vd, bt_drv_lowpower_sophia_tl_vd},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_sophia_tl_vd[] = {
    &ISP_GPIO1_SOPHIA_TL_VD, &ISP_GPIO4_SOPHIA_TL_VD, &ISP_RESETB1_SOPHIA_TL_VD, &ISP_CCLK1_SOPHIA_TL_VD, &ISP_SDA1_SOPHIA_TL_VD, &ISP_SCL1_SOPHIA_TL_VD,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_sophia_tl_vd, "block_scamera", NORMAL, scamera_pins_sophia_tl_vd)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_sophia_tl_vd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_sophia_tl_vd[] = {
    [NORMAL] = {scamera_func_normal_sophia_tl_vd, scamera_pullud_normal_sophia_tl_vd, scamera_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {scamera_func_lowpower_sophia_tl_vd, scamera_pullud_lowpower_sophia_tl_vd, scamera_drv_lowpower_sophia_tl_vd},

};

/*codec pins */
static struct  iomux_pin *codec_pins_sophia_tl_vd[] = {
    &PCM1_XCLK_SOPHIA_TL_VD, &PCM1_XFS_SOPHIA_TL_VD, &PCM1_DI_SOPHIA_TL_VD, &PCM1_DO_SOPHIA_TL_VD, &I2S_XCLK_SOPHIA_TL_VD, &I2S_XFS_SOPHIA_TL_VD, &I2S_DI_SOPHIA_TL_VD, &I2S_DO_SOPHIA_TL_VD, &PCM0_XCLK_SOPHIA_TL_VD, &PCM0_XFS_SOPHIA_TL_VD, &PCM0_DI_SOPHIA_TL_VD, &PCM0_DO_SOPHIA_TL_VD,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_sophia_tl_vd, "block_codec", NORMAL, codec_pins_sophia_tl_vd)



/*CODEC*/

static enum lowlayer_func codec_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_sophia_tl_vd[] = {
    [NORMAL] = {codec_func_normal_sophia_tl_vd, codec_pullud_normal_sophia_tl_vd, codec_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {codec_func_lowpower_sophia_tl_vd, codec_pullud_lowpower_sophia_tl_vd, codec_drv_lowpower_sophia_tl_vd},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_sophia_tl_vd[] = {
    &HKADC_SSI_SOPHIA_TL_VD, &AUX_SSI0_SOPHIA_TL_VD, &AUX_SSI1_SOPHIA_TL_VD, &GPIO_5_0_SOPHIA_TL_VD,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_sophia_tl_vd, "block_pmu", NORMAL, pmu_pins_sophia_tl_vd)



/*PMU*/

static enum lowlayer_func pmu_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_sophia_tl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_sophia_tl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_sophia_tl_vd[] = {
    [NORMAL] = {pmu_func_normal_sophia_tl_vd, pmu_pullud_normal_sophia_tl_vd, pmu_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {pmu_func_lowpower_sophia_tl_vd, pmu_pullud_lowpower_sophia_tl_vd, pmu_drv_lowpower_sophia_tl_vd},

};

/*spi0 pins */
static struct  iomux_pin *spi0_pins_sophia_tl_vd[] = {
    &TS_CLK_SOPHIA_TL_VD, &TS_DATA_SOPHIA_TL_VD, &TS_SYNC_SOPHIA_TL_VD, &TS_VALID_SOPHIA_TL_VD,  NULL,
};

/*define blocks: spi0*/
IOMUX_BLOCK(block_spi0_sophia_tl_vd, "block_spi0", NORMAL, spi0_pins_sophia_tl_vd)



/*SPI0*/

static enum lowlayer_func spi0_func_normal_sophia_tl_vd[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func spi0_func_lowpower_sophia_tl_vd[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config spi0_config_sophia_tl_vd[] = {
    [NORMAL] = {spi0_func_normal_sophia_tl_vd, spi0_pullud_normal_sophia_tl_vd, spi0_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {spi0_func_lowpower_sophia_tl_vd, spi0_pullud_lowpower_sophia_tl_vd, spi0_drv_lowpower_sophia_tl_vd},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_sophia_tl_vd[] = {
    &EMMC_CLK_SOPHIA_TL_VD, &EMMC_CMD_SOPHIA_TL_VD, &EMMC_DATA0_SOPHIA_TL_VD, &EMMC_DATA1_SOPHIA_TL_VD, &EMMC_DATA2_SOPHIA_TL_VD, &EMMC_DATA3_SOPHIA_TL_VD, &EMMC_DATA4_SOPHIA_TL_VD, &EMMC_DATA5_SOPHIA_TL_VD, &EMMC_DATA6_SOPHIA_TL_VD, &EMMC_DATA7_SOPHIA_TL_VD, &GPIO_2_3_SOPHIA_TL_VD,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_sophia_tl_vd, "block_emmc", NORMAL, emmc_pins_sophia_tl_vd)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_sophia_tl_vd[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_sophia_tl_vd[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_sophia_tl_vd[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_sophia_tl_vd[] = {
    [NORMAL] = {emmc_func_normal_sophia_tl_vd, emmc_pullud_normal_sophia_tl_vd, emmc_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {emmc_func_lowpower_sophia_tl_vd, emmc_pullud_lowpower_sophia_tl_vd, emmc_drv_lowpower_sophia_tl_vd},

};

/*odt pins */
static struct  iomux_pin *odt_pins_sophia_tl_vd[] = {
    &RF_RESET1_SOPHIA_TL_VD,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_sophia_tl_vd, "block_odt", NORMAL, odt_pins_sophia_tl_vd)



/*ODT*/

static enum lowlayer_func odt_func_normal_sophia_tl_vd[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_sophia_tl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_sophia_tl_vd[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_sophia_tl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_sophia_tl_vd[] = {
    [NORMAL] = {odt_func_normal_sophia_tl_vd, odt_pullud_normal_sophia_tl_vd, odt_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {odt_func_lowpower_sophia_tl_vd, odt_pullud_lowpower_sophia_tl_vd, odt_drv_lowpower_sophia_tl_vd},

};

/*rf pins */
static struct  iomux_pin *rf_pins_sophia_tl_vd[] = {
    &RF_TX_EN1_SOPHIA_TL_VD, &RF_TCVR_ON0_SOPHIA_TL_VD, &RF_TCVR_ON1_SOPHIA_TL_VD, &RF_SSI0_SOPHIA_TL_VD, &RF_SSI1_SOPHIA_TL_VD, &RF_GPIO_2_SOPHIA_TL_VD, &RF_GPIO_3_SOPHIA_TL_VD, &RF_GPIO_4_SOPHIA_TL_VD, &RF_GPIO_5_SOPHIA_TL_VD, &RF_GPIO_6_SOPHIA_TL_VD, &RF_GPIO_7_SOPHIA_TL_VD, &RF_GPIO_13_SOPHIA_TL_VD, &RF_GPIO_14_SOPHIA_TL_VD, &RF_GPIO_15_SOPHIA_TL_VD, &RF_GPIO_16_SOPHIA_TL_VD, &RF_GPIO_17_SOPHIA_TL_VD, &RF_GPIO_18_SOPHIA_TL_VD, &RF_GPIO_23_SOPHIA_TL_VD, &RF_GPIO_24_SOPHIA_TL_VD, &RF_GPIO_26_SOPHIA_TL_VD, &RF_GPIO_27_SOPHIA_TL_VD, &RF_GPIO_28_SOPHIA_TL_VD,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_sophia_tl_vd, "block_rf", NORMAL, rf_pins_sophia_tl_vd)



/*RF*/

static enum lowlayer_func rf_func_normal_sophia_tl_vd[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_sophia_tl_vd[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_sophia_tl_vd[] = {
    [NORMAL] = {rf_func_normal_sophia_tl_vd, rf_pullud_normal_sophia_tl_vd, rf_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {rf_func_lowpower_sophia_tl_vd, rf_pullud_lowpower_sophia_tl_vd, rf_drv_lowpower_sophia_tl_vd},

};

/*tp pins */
static struct  iomux_pin *tp_pins_sophia_tl_vd[] = {
    &GPIO_18_7_SOPHIA_TL_VD,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_sophia_tl_vd, "block_tp", NORMAL, tp_pins_sophia_tl_vd)



/*TP*/

static enum lowlayer_func tp_func_normal_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_sophia_tl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_sophia_tl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_sophia_tl_vd[] = {
    [NORMAL] = {tp_func_normal_sophia_tl_vd, tp_pullud_normal_sophia_tl_vd, tp_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {tp_func_lowpower_sophia_tl_vd, tp_pullud_lowpower_sophia_tl_vd, tp_drv_lowpower_sophia_tl_vd},

};

/*switch pins */
static struct  iomux_pin *switch_pins_sophia_tl_vd[] = {
    &GPIO_5_3_SOPHIA_TL_VD, &GPIO_6_2_SOPHIA_TL_VD,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_sophia_tl_vd, "block_switch", NORMAL, switch_pins_sophia_tl_vd)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_sophia_tl_vd[] = {
    [NORMAL] = {switch_func_normal_sophia_tl_vd, switch_pullud_normal_sophia_tl_vd, switch_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {switch_func_lowpower_sophia_tl_vd, switch_pullud_lowpower_sophia_tl_vd, switch_drv_lowpower_sophia_tl_vd},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_sophia_tl_vd[] = {
    &RF_MIPI_CLK0_SOPHIA_TL_VD, &RF_MIPI_DATA0_SOPHIA_TL_VD, &APT_PDM0_SOPHIA_TL_VD,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_sophia_tl_vd, "block_rfpmu", NORMAL, rfpmu_pins_sophia_tl_vd)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_sophia_tl_vd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_sophia_tl_vd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_sophia_tl_vd[] = {
    [NORMAL] = {rfpmu_func_normal_sophia_tl_vd, rfpmu_pullud_normal_sophia_tl_vd, rfpmu_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {rfpmu_func_lowpower_sophia_tl_vd, rfpmu_pullud_lowpower_sophia_tl_vd, rfpmu_drv_lowpower_sophia_tl_vd},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_sophia_tl_vd[] = {
    &I2C3_SCL_SOPHIA_TL_VD, &I2C3_SDA_SOPHIA_TL_VD,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_sophia_tl_vd, "block_i2c3", NORMAL, i2c3_pins_sophia_tl_vd)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_sophia_tl_vd[] = {
    [NORMAL] = {i2c3_func_normal_sophia_tl_vd, i2c3_pullud_normal_sophia_tl_vd, i2c3_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {i2c3_func_lowpower_sophia_tl_vd, i2c3_pullud_lowpower_sophia_tl_vd, i2c3_drv_lowpower_sophia_tl_vd},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_sophia_tl_vd[] = {
    &USIM1_CLK_SOPHIA_TL_VD, &USIM1_DATA_SOPHIA_TL_VD, &USIM1_RST_SOPHIA_TL_VD,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_sophia_tl_vd, "block_usim1", NORMAL, usim1_pins_sophia_tl_vd)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_sophia_tl_vd[] = {
    [NORMAL] = {usim1_func_normal_sophia_tl_vd, usim1_pullud_normal_sophia_tl_vd, usim1_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {usim1_func_lowpower_sophia_tl_vd, usim1_pullud_lowpower_sophia_tl_vd, usim1_drv_lowpower_sophia_tl_vd},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_sophia_tl_vd[] = {
    &USIM0_CLK_SOPHIA_TL_VD, &USIM0_DATA_SOPHIA_TL_VD, &USIM0_RST_SOPHIA_TL_VD,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_sophia_tl_vd, "block_usim0", NORMAL, usim0_pins_sophia_tl_vd)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_sophia_tl_vd[] = {
    [NORMAL] = {usim0_func_normal_sophia_tl_vd, usim0_pullud_normal_sophia_tl_vd, usim0_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {usim0_func_lowpower_sophia_tl_vd, usim0_pullud_lowpower_sophia_tl_vd, usim0_drv_lowpower_sophia_tl_vd},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_sophia_tl_vd[] = {
    &ISP_GPIO0_SOPHIA_TL_VD, &ISP_GPIO2_SOPHIA_TL_VD, &ISP_GPIO3_SOPHIA_TL_VD, &ISP_RESETB0_SOPHIA_TL_VD, &ISP_CCLK0_SOPHIA_TL_VD, &ISP_SDA0_SOPHIA_TL_VD, &ISP_SCL0_SOPHIA_TL_VD,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_sophia_tl_vd, "block_mcamera", NORMAL, mcamera_pins_sophia_tl_vd)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_sophia_tl_vd[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_sophia_tl_vd[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_sophia_tl_vd[] = {
    [NORMAL] = {mcamera_func_normal_sophia_tl_vd, mcamera_pullud_normal_sophia_tl_vd, mcamera_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {mcamera_func_lowpower_sophia_tl_vd, mcamera_pullud_lowpower_sophia_tl_vd, mcamera_drv_lowpower_sophia_tl_vd},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_sophia_tl_vd[] = {
    &I2C0_SCL_SOPHIA_TL_VD, &I2C0_SDA_SOPHIA_TL_VD,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_sophia_tl_vd, "block_i2c0", NORMAL, i2c0_pins_sophia_tl_vd)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_sophia_tl_vd[] = {
    [NORMAL] = {i2c0_func_normal_sophia_tl_vd, i2c0_pullud_normal_sophia_tl_vd, i2c0_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {i2c0_func_lowpower_sophia_tl_vd, i2c0_pullud_lowpower_sophia_tl_vd, i2c0_drv_lowpower_sophia_tl_vd},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_sophia_tl_vd[] = {
    &I2C1_SCL_SOPHIA_TL_VD, &I2C1_SDA_SOPHIA_TL_VD,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_sophia_tl_vd, "block_i2c1", NORMAL, i2c1_pins_sophia_tl_vd)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_sophia_tl_vd[] = {
    [NORMAL] = {i2c1_func_normal_sophia_tl_vd, i2c1_pullud_normal_sophia_tl_vd, i2c1_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {i2c1_func_lowpower_sophia_tl_vd, i2c1_pullud_lowpower_sophia_tl_vd, i2c1_drv_lowpower_sophia_tl_vd},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_sophia_tl_vd[] = {
    &I2C2_SCL_SOPHIA_TL_VD, &I2C2_SDA_SOPHIA_TL_VD,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_sophia_tl_vd, "block_i2c2", NORMAL, i2c2_pins_sophia_tl_vd)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_sophia_tl_vd[] = {
    [NORMAL] = {i2c2_func_normal_sophia_tl_vd, i2c2_pullud_normal_sophia_tl_vd, i2c2_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {i2c2_func_lowpower_sophia_tl_vd, i2c2_pullud_lowpower_sophia_tl_vd, i2c2_drv_lowpower_sophia_tl_vd},

};

/*gps pins */
static struct  iomux_pin *gps_pins_sophia_tl_vd[] = {
    &GPIO_6_1_SOPHIA_TL_VD, &RF_GPIO_1_SOPHIA_TL_VD, &UART3_CTS_N_SOPHIA_TL_VD, &UART3_RTS_N_SOPHIA_TL_VD, &UART3_RXD_SOPHIA_TL_VD, &UART3_TXD_SOPHIA_TL_VD, &GPS_CLK_SOPHIA_TL_VD,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_sophia_tl_vd, "block_gps", NORMAL, gps_pins_sophia_tl_vd)



/*GPS*/

static enum lowlayer_func gps_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_sophia_tl_vd[] = {
    [NORMAL] = {gps_func_normal_sophia_tl_vd, gps_pullud_normal_sophia_tl_vd, gps_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {gps_func_lowpower_sophia_tl_vd, gps_pullud_lowpower_sophia_tl_vd, gps_drv_lowpower_sophia_tl_vd},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_sophia_tl_vd[] = {
    &TCXO0_AFC_SOPHIA_TL_VD, &TCXO1_AFC_SOPHIA_TL_VD,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_sophia_tl_vd, "block_tcxo", NORMAL, tcxo_pins_sophia_tl_vd)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_sophia_tl_vd[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_sophia_tl_vd[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_sophia_tl_vd[] = {
    [NORMAL] = {tcxo_func_normal_sophia_tl_vd, tcxo_pullud_normal_sophia_tl_vd, tcxo_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {tcxo_func_lowpower_sophia_tl_vd, tcxo_pullud_lowpower_sophia_tl_vd, tcxo_drv_lowpower_sophia_tl_vd},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_sophia_tl_vd[] = {
    &GPIO_7_5_SOPHIA_TL_VD,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_sophia_tl_vd, "block_rfant", NORMAL, rfant_pins_sophia_tl_vd)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_sophia_tl_vd[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_sophia_tl_vd[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_sophia_tl_vd[] = {
    [NORMAL] = {rfant_func_normal_sophia_tl_vd, rfant_pullud_normal_sophia_tl_vd, rfant_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {rfant_func_lowpower_sophia_tl_vd, rfant_pullud_lowpower_sophia_tl_vd, rfant_drv_lowpower_sophia_tl_vd},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_sophia_tl_vd[] = {
    &SDIO_DATA3_SOPHIA_TL_VD, &SDIO_DATA2_SOPHIA_TL_VD, &SDIO_DATA1_SOPHIA_TL_VD, &SDIO_DATA0_SOPHIA_TL_VD, &SDIO_CMD_SOPHIA_TL_VD, &SDIO_CLK_SOPHIA_TL_VD,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_sophia_tl_vd, "block_wifi", NORMAL, wifi_pins_sophia_tl_vd)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_sophia_tl_vd[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_sophia_tl_vd[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_sophia_tl_vd[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_sophia_tl_vd[] = {
    [NORMAL] = {wifi_func_normal_sophia_tl_vd, wifi_pullud_normal_sophia_tl_vd, wifi_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {wifi_func_lowpower_sophia_tl_vd, wifi_pullud_lowpower_sophia_tl_vd, wifi_drv_lowpower_sophia_tl_vd},

};

/*boot pins */
static struct  iomux_pin *boot_pins_sophia_tl_vd[] = {
    &BOOT_SEL_SOPHIA_TL_VD, &GPIO_5_2_SOPHIA_TL_VD,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_sophia_tl_vd, "block_boot", NORMAL, boot_pins_sophia_tl_vd)



/*BOOT*/

static enum lowlayer_func boot_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_sophia_tl_vd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_sophia_tl_vd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_sophia_tl_vd[] = {
    [NORMAL] = {boot_func_normal_sophia_tl_vd, boot_pullud_normal_sophia_tl_vd, boot_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {boot_func_lowpower_sophia_tl_vd, boot_pullud_lowpower_sophia_tl_vd, boot_drv_lowpower_sophia_tl_vd},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_sophia_tl_vd[] = {
    &PWM_OUT1_SOPHIA_TL_VD, &GPIO_4_6_SOPHIA_TL_VD, &GPIO_4_7_SOPHIA_TL_VD, &GPIO_6_6_SOPHIA_TL_VD, &PWM_OUT0_SOPHIA_TL_VD,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_sophia_tl_vd, "block_lcd", NORMAL, lcd_pins_sophia_tl_vd)



/*LCD*/

static enum lowlayer_func lcd_func_normal_sophia_tl_vd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_sophia_tl_vd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_sophia_tl_vd[] = {
    [NORMAL] = {lcd_func_normal_sophia_tl_vd, lcd_pullud_normal_sophia_tl_vd, lcd_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {lcd_func_lowpower_sophia_tl_vd, lcd_pullud_lowpower_sophia_tl_vd, lcd_drv_lowpower_sophia_tl_vd},

};

/*key pins */
static struct  iomux_pin *key_pins_sophia_tl_vd[] = {
    &GPIO_4_2_SOPHIA_TL_VD,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_sophia_tl_vd, "block_key", NORMAL, key_pins_sophia_tl_vd)



/*KEY*/

static enum lowlayer_func key_func_normal_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_sophia_tl_vd[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_sophia_tl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_sophia_tl_vd[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_sophia_tl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config key_config_sophia_tl_vd[] = {
    [NORMAL] = {key_func_normal_sophia_tl_vd, key_pullud_normal_sophia_tl_vd, key_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {key_func_lowpower_sophia_tl_vd, key_pullud_lowpower_sophia_tl_vd, key_drv_lowpower_sophia_tl_vd},

};

/*test pins */
static struct  iomux_pin *test_pins_sophia_tl_vd[] = {
    &UART0_RXD_SOPHIA_TL_VD, &UART0_TXD_SOPHIA_TL_VD,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_sophia_tl_vd, "block_test", NORMAL, test_pins_sophia_tl_vd)



/*TEST*/

static enum lowlayer_func test_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_sophia_tl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_sophia_tl_vd[] = {
    [NORMAL] = {test_func_normal_sophia_tl_vd, test_pullud_normal_sophia_tl_vd, test_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {test_func_lowpower_sophia_tl_vd, test_pullud_lowpower_sophia_tl_vd, test_drv_lowpower_sophia_tl_vd},

};

/*sd pins */
static struct  iomux_pin *sd_pins_sophia_tl_vd[] = {
    &SD_CLK_SOPHIA_TL_VD, &SD_CMD_SOPHIA_TL_VD, &SD_DATA0_SOPHIA_TL_VD, &SD_DATA1_SOPHIA_TL_VD, &SD_DATA2_SOPHIA_TL_VD, &SD_DATA3_SOPHIA_TL_VD,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_sophia_tl_vd, "block_sd", NORMAL, sd_pins_sophia_tl_vd)



/*SD*/

static enum lowlayer_func sd_func_normal_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_sophia_tl_vd[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_sophia_tl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_sophia_tl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_sophia_tl_vd[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_sophia_tl_vd[] = {
    [NORMAL] = {sd_func_normal_sophia_tl_vd, sd_pullud_normal_sophia_tl_vd, sd_drv_normal_sophia_tl_vd},
    [LOWPOWER] = {sd_func_lowpower_sophia_tl_vd, sd_pullud_lowpower_sophia_tl_vd, sd_drv_lowpower_sophia_tl_vd},

};

struct iomux_block_table block_config_table_sophia_tl_vd[] = {
    BLOCK_CONFIG("block_charger", &block_charger_sophia_tl_vd, charger_config_sophia_tl_vd)
    BLOCK_CONFIG("block_flash", &block_flash_sophia_tl_vd, flash_config_sophia_tl_vd)
    BLOCK_CONFIG("block_bt", &block_bt_sophia_tl_vd, bt_config_sophia_tl_vd)
    BLOCK_CONFIG("block_scamera", &block_scamera_sophia_tl_vd, scamera_config_sophia_tl_vd)
    BLOCK_CONFIG("block_codec", &block_codec_sophia_tl_vd, codec_config_sophia_tl_vd)
    BLOCK_CONFIG("block_pmu", &block_pmu_sophia_tl_vd, pmu_config_sophia_tl_vd)
    BLOCK_CONFIG("block_spi0", &block_spi0_sophia_tl_vd, spi0_config_sophia_tl_vd)
    BLOCK_CONFIG("block_emmc", &block_emmc_sophia_tl_vd, emmc_config_sophia_tl_vd)
    BLOCK_CONFIG("block_odt", &block_odt_sophia_tl_vd, odt_config_sophia_tl_vd)
    BLOCK_CONFIG("block_rf", &block_rf_sophia_tl_vd, rf_config_sophia_tl_vd)
    BLOCK_CONFIG("block_tp", &block_tp_sophia_tl_vd, tp_config_sophia_tl_vd)
    BLOCK_CONFIG("block_switch", &block_switch_sophia_tl_vd, switch_config_sophia_tl_vd)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_sophia_tl_vd, rfpmu_config_sophia_tl_vd)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_sophia_tl_vd, i2c3_config_sophia_tl_vd)
    BLOCK_CONFIG("block_usim1", &block_usim1_sophia_tl_vd, usim1_config_sophia_tl_vd)
    BLOCK_CONFIG("block_usim0", &block_usim0_sophia_tl_vd, usim0_config_sophia_tl_vd)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_sophia_tl_vd, mcamera_config_sophia_tl_vd)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_sophia_tl_vd, i2c0_config_sophia_tl_vd)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_sophia_tl_vd, i2c1_config_sophia_tl_vd)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_sophia_tl_vd, i2c2_config_sophia_tl_vd)
    BLOCK_CONFIG("block_gps", &block_gps_sophia_tl_vd, gps_config_sophia_tl_vd)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_sophia_tl_vd, tcxo_config_sophia_tl_vd)
    BLOCK_CONFIG("block_rfant", &block_rfant_sophia_tl_vd, rfant_config_sophia_tl_vd)
    BLOCK_CONFIG("block_wifi", &block_wifi_sophia_tl_vd, wifi_config_sophia_tl_vd)
    BLOCK_CONFIG("block_boot", &block_boot_sophia_tl_vd, boot_config_sophia_tl_vd)
    BLOCK_CONFIG("block_lcd", &block_lcd_sophia_tl_vd, lcd_config_sophia_tl_vd)
    BLOCK_CONFIG("block_key", &block_key_sophia_tl_vd, key_config_sophia_tl_vd)
    BLOCK_CONFIG("block_test", &block_test_sophia_tl_vd, test_config_sophia_tl_vd)
    BLOCK_CONFIG("block_sd", &block_sd_sophia_tl_vd, sd_config_sophia_tl_vd)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
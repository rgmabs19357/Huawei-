/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_sophia_ulg_vc_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_SOPHIA_ULG_VC_IOMUX_BLOCKS_H__
#define __HI6620_SOPHIA_ULG_VC_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_sophia_ulg_vc_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_sophia_ulg_vc[] = {
    &GPIO_4_0_SOPHIA_ULG_VC, &GPIO_4_1_SOPHIA_ULG_VC, &UART2_RTS_N_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_sophia_ulg_vc, "block_charger", NORMAL, charger_pins_sophia_ulg_vc)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_sophia_ulg_vc[] = {
    [NORMAL] = {charger_func_normal_sophia_ulg_vc, charger_pullud_normal_sophia_ulg_vc, charger_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {charger_func_lowpower_sophia_ulg_vc, charger_pullud_lowpower_sophia_ulg_vc, charger_drv_lowpower_sophia_ulg_vc},

};

/*flash pins */
static struct  iomux_pin *flash_pins_sophia_ulg_vc[] = {
    &ISP_GPIO5_SOPHIA_ULG_VC, &RF_GPIO_20_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_sophia_ulg_vc, "block_flash", NORMAL, flash_pins_sophia_ulg_vc)



/*FLASH*/

static enum lowlayer_func flash_func_normal_sophia_ulg_vc[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_sophia_ulg_vc[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_sophia_ulg_vc[] = {
    [NORMAL] = {flash_func_normal_sophia_ulg_vc, flash_pullud_normal_sophia_ulg_vc, flash_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {flash_func_lowpower_sophia_ulg_vc, flash_pullud_lowpower_sophia_ulg_vc, flash_drv_lowpower_sophia_ulg_vc},

};

/*bt pins */
static struct  iomux_pin *bt_pins_sophia_ulg_vc[] = {
    &UART4_CTS_N_SOPHIA_ULG_VC, &UART4_RTS_N_SOPHIA_ULG_VC, &UART4_RXD_SOPHIA_ULG_VC, &UART4_TXD_SOPHIA_ULG_VC, &GPIO_15_7_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_sophia_ulg_vc, "block_bt", NORMAL, bt_pins_sophia_ulg_vc)



/*BT*/

static enum lowlayer_func bt_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_sophia_ulg_vc[] = {
    [NORMAL] = {bt_func_normal_sophia_ulg_vc, bt_pullud_normal_sophia_ulg_vc, bt_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {bt_func_lowpower_sophia_ulg_vc, bt_pullud_lowpower_sophia_ulg_vc, bt_drv_lowpower_sophia_ulg_vc},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_sophia_ulg_vc[] = {
    &ISP_GPIO1_SOPHIA_ULG_VC, &ISP_GPIO4_SOPHIA_ULG_VC, &ISP_RESETB1_SOPHIA_ULG_VC, &ISP_CCLK1_SOPHIA_ULG_VC, &ISP_SDA1_SOPHIA_ULG_VC, &ISP_SCL1_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_sophia_ulg_vc, "block_scamera", NORMAL, scamera_pins_sophia_ulg_vc)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_sophia_ulg_vc[] = {
    [NORMAL] = {scamera_func_normal_sophia_ulg_vc, scamera_pullud_normal_sophia_ulg_vc, scamera_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {scamera_func_lowpower_sophia_ulg_vc, scamera_pullud_lowpower_sophia_ulg_vc, scamera_drv_lowpower_sophia_ulg_vc},

};

/*codec pins */
static struct  iomux_pin *codec_pins_sophia_ulg_vc[] = {
    &PCM1_XCLK_SOPHIA_ULG_VC, &PCM1_XFS_SOPHIA_ULG_VC, &PCM1_DI_SOPHIA_ULG_VC, &PCM1_DO_SOPHIA_ULG_VC, &I2S_XCLK_SOPHIA_ULG_VC, &I2S_XFS_SOPHIA_ULG_VC, &I2S_DI_SOPHIA_ULG_VC, &I2S_DO_SOPHIA_ULG_VC, &PCM0_XCLK_SOPHIA_ULG_VC, &PCM0_XFS_SOPHIA_ULG_VC, &PCM0_DI_SOPHIA_ULG_VC, &PCM0_DO_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_sophia_ulg_vc, "block_codec", NORMAL, codec_pins_sophia_ulg_vc)



/*CODEC*/

static enum lowlayer_func codec_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_sophia_ulg_vc[] = {
    [NORMAL] = {codec_func_normal_sophia_ulg_vc, codec_pullud_normal_sophia_ulg_vc, codec_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {codec_func_lowpower_sophia_ulg_vc, codec_pullud_lowpower_sophia_ulg_vc, codec_drv_lowpower_sophia_ulg_vc},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_sophia_ulg_vc[] = {
    &HKADC_SSI_SOPHIA_ULG_VC, &AUX_SSI0_SOPHIA_ULG_VC, &AUX_SSI1_SOPHIA_ULG_VC, &GPIO_5_0_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_sophia_ulg_vc, "block_pmu", NORMAL, pmu_pins_sophia_ulg_vc)



/*PMU*/

static enum lowlayer_func pmu_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_sophia_ulg_vc[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_sophia_ulg_vc[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_sophia_ulg_vc[] = {
    [NORMAL] = {pmu_func_normal_sophia_ulg_vc, pmu_pullud_normal_sophia_ulg_vc, pmu_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {pmu_func_lowpower_sophia_ulg_vc, pmu_pullud_lowpower_sophia_ulg_vc, pmu_drv_lowpower_sophia_ulg_vc},

};

/*spi0 pins */
static struct  iomux_pin *spi0_pins_sophia_ulg_vc[] = {
    &TS_CLK_SOPHIA_ULG_VC, &TS_DATA_SOPHIA_ULG_VC, &TS_SYNC_SOPHIA_ULG_VC, &TS_VALID_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: spi0*/
IOMUX_BLOCK(block_spi0_sophia_ulg_vc, "block_spi0", NORMAL, spi0_pins_sophia_ulg_vc)



/*SPI0*/

static enum lowlayer_func spi0_func_normal_sophia_ulg_vc[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func spi0_func_lowpower_sophia_ulg_vc[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config spi0_config_sophia_ulg_vc[] = {
    [NORMAL] = {spi0_func_normal_sophia_ulg_vc, spi0_pullud_normal_sophia_ulg_vc, spi0_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {spi0_func_lowpower_sophia_ulg_vc, spi0_pullud_lowpower_sophia_ulg_vc, spi0_drv_lowpower_sophia_ulg_vc},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_sophia_ulg_vc[] = {
    &EMMC_CLK_SOPHIA_ULG_VC, &EMMC_CMD_SOPHIA_ULG_VC, &EMMC_DATA0_SOPHIA_ULG_VC, &EMMC_DATA1_SOPHIA_ULG_VC, &EMMC_DATA2_SOPHIA_ULG_VC, &EMMC_DATA3_SOPHIA_ULG_VC, &EMMC_DATA4_SOPHIA_ULG_VC, &EMMC_DATA5_SOPHIA_ULG_VC, &EMMC_DATA6_SOPHIA_ULG_VC, &EMMC_DATA7_SOPHIA_ULG_VC, &GPIO_2_3_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_sophia_ulg_vc, "block_emmc", NORMAL, emmc_pins_sophia_ulg_vc)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_sophia_ulg_vc[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_sophia_ulg_vc[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_sophia_ulg_vc[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_sophia_ulg_vc[] = {
    [NORMAL] = {emmc_func_normal_sophia_ulg_vc, emmc_pullud_normal_sophia_ulg_vc, emmc_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {emmc_func_lowpower_sophia_ulg_vc, emmc_pullud_lowpower_sophia_ulg_vc, emmc_drv_lowpower_sophia_ulg_vc},

};

/*odt pins */
static struct  iomux_pin *odt_pins_sophia_ulg_vc[] = {
    &RF_RESET1_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_sophia_ulg_vc, "block_odt", NORMAL, odt_pins_sophia_ulg_vc)



/*ODT*/

static enum lowlayer_func odt_func_normal_sophia_ulg_vc[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_sophia_ulg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_sophia_ulg_vc[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_sophia_ulg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_sophia_ulg_vc[] = {
    [NORMAL] = {odt_func_normal_sophia_ulg_vc, odt_pullud_normal_sophia_ulg_vc, odt_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {odt_func_lowpower_sophia_ulg_vc, odt_pullud_lowpower_sophia_ulg_vc, odt_drv_lowpower_sophia_ulg_vc},

};

/*rf pins */
static struct  iomux_pin *rf_pins_sophia_ulg_vc[] = {
    &RF_TX_EN1_SOPHIA_ULG_VC, &RF_TCVR_ON0_SOPHIA_ULG_VC, &RF_TCVR_ON1_SOPHIA_ULG_VC, &RF_SSI0_SOPHIA_ULG_VC, &RF_SSI1_SOPHIA_ULG_VC, &RF_GPIO_2_SOPHIA_ULG_VC, &RF_GPIO_3_SOPHIA_ULG_VC, &RF_GPIO_4_SOPHIA_ULG_VC, &RF_GPIO_5_SOPHIA_ULG_VC, &RF_GPIO_6_SOPHIA_ULG_VC, &RF_GPIO_7_SOPHIA_ULG_VC, &RF_GPIO_13_SOPHIA_ULG_VC, &RF_GPIO_14_SOPHIA_ULG_VC, &RF_GPIO_15_SOPHIA_ULG_VC, &RF_GPIO_16_SOPHIA_ULG_VC, &RF_GPIO_17_SOPHIA_ULG_VC, &RF_GPIO_18_SOPHIA_ULG_VC, &RF_GPIO_23_SOPHIA_ULG_VC, &RF_GPIO_24_SOPHIA_ULG_VC, &RF_GPIO_26_SOPHIA_ULG_VC, &RF_GPIO_27_SOPHIA_ULG_VC, &RF_GPIO_28_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_sophia_ulg_vc, "block_rf", NORMAL, rf_pins_sophia_ulg_vc)



/*RF*/

static enum lowlayer_func rf_func_normal_sophia_ulg_vc[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_sophia_ulg_vc[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_sophia_ulg_vc[] = {
    [NORMAL] = {rf_func_normal_sophia_ulg_vc, rf_pullud_normal_sophia_ulg_vc, rf_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {rf_func_lowpower_sophia_ulg_vc, rf_pullud_lowpower_sophia_ulg_vc, rf_drv_lowpower_sophia_ulg_vc},

};

/*tp pins */
static struct  iomux_pin *tp_pins_sophia_ulg_vc[] = {
    &GPIO_18_7_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_sophia_ulg_vc, "block_tp", NORMAL, tp_pins_sophia_ulg_vc)



/*TP*/

static enum lowlayer_func tp_func_normal_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_sophia_ulg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_sophia_ulg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_sophia_ulg_vc[] = {
    [NORMAL] = {tp_func_normal_sophia_ulg_vc, tp_pullud_normal_sophia_ulg_vc, tp_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {tp_func_lowpower_sophia_ulg_vc, tp_pullud_lowpower_sophia_ulg_vc, tp_drv_lowpower_sophia_ulg_vc},

};

/*switch pins */
static struct  iomux_pin *switch_pins_sophia_ulg_vc[] = {
    &GPIO_5_3_SOPHIA_ULG_VC, &GPIO_6_2_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_sophia_ulg_vc, "block_switch", NORMAL, switch_pins_sophia_ulg_vc)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_sophia_ulg_vc[] = {
    [NORMAL] = {switch_func_normal_sophia_ulg_vc, switch_pullud_normal_sophia_ulg_vc, switch_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {switch_func_lowpower_sophia_ulg_vc, switch_pullud_lowpower_sophia_ulg_vc, switch_drv_lowpower_sophia_ulg_vc},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_sophia_ulg_vc[] = {
    &RF_MIPI_CLK0_SOPHIA_ULG_VC, &RF_MIPI_DATA0_SOPHIA_ULG_VC, &APT_PDM0_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_sophia_ulg_vc, "block_rfpmu", NORMAL, rfpmu_pins_sophia_ulg_vc)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_sophia_ulg_vc[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_sophia_ulg_vc[] = {
    [NORMAL] = {rfpmu_func_normal_sophia_ulg_vc, rfpmu_pullud_normal_sophia_ulg_vc, rfpmu_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {rfpmu_func_lowpower_sophia_ulg_vc, rfpmu_pullud_lowpower_sophia_ulg_vc, rfpmu_drv_lowpower_sophia_ulg_vc},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_sophia_ulg_vc[] = {
    &I2C3_SCL_SOPHIA_ULG_VC, &I2C3_SDA_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_sophia_ulg_vc, "block_i2c3", NORMAL, i2c3_pins_sophia_ulg_vc)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_sophia_ulg_vc[] = {
    [NORMAL] = {i2c3_func_normal_sophia_ulg_vc, i2c3_pullud_normal_sophia_ulg_vc, i2c3_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {i2c3_func_lowpower_sophia_ulg_vc, i2c3_pullud_lowpower_sophia_ulg_vc, i2c3_drv_lowpower_sophia_ulg_vc},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_sophia_ulg_vc[] = {
    &USIM1_CLK_SOPHIA_ULG_VC, &USIM1_DATA_SOPHIA_ULG_VC, &USIM1_RST_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_sophia_ulg_vc, "block_usim1", NORMAL, usim1_pins_sophia_ulg_vc)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_sophia_ulg_vc[] = {
    [NORMAL] = {usim1_func_normal_sophia_ulg_vc, usim1_pullud_normal_sophia_ulg_vc, usim1_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {usim1_func_lowpower_sophia_ulg_vc, usim1_pullud_lowpower_sophia_ulg_vc, usim1_drv_lowpower_sophia_ulg_vc},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_sophia_ulg_vc[] = {
    &USIM0_CLK_SOPHIA_ULG_VC, &USIM0_DATA_SOPHIA_ULG_VC, &USIM0_RST_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_sophia_ulg_vc, "block_usim0", NORMAL, usim0_pins_sophia_ulg_vc)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_sophia_ulg_vc[] = {
    [NORMAL] = {usim0_func_normal_sophia_ulg_vc, usim0_pullud_normal_sophia_ulg_vc, usim0_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {usim0_func_lowpower_sophia_ulg_vc, usim0_pullud_lowpower_sophia_ulg_vc, usim0_drv_lowpower_sophia_ulg_vc},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_sophia_ulg_vc[] = {
    &ISP_GPIO0_SOPHIA_ULG_VC, &ISP_GPIO2_SOPHIA_ULG_VC, &ISP_GPIO3_SOPHIA_ULG_VC, &ISP_RESETB0_SOPHIA_ULG_VC, &ISP_CCLK0_SOPHIA_ULG_VC, &ISP_SDA0_SOPHIA_ULG_VC, &ISP_SCL0_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_sophia_ulg_vc, "block_mcamera", NORMAL, mcamera_pins_sophia_ulg_vc)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_sophia_ulg_vc[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_sophia_ulg_vc[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_sophia_ulg_vc[] = {
    [NORMAL] = {mcamera_func_normal_sophia_ulg_vc, mcamera_pullud_normal_sophia_ulg_vc, mcamera_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {mcamera_func_lowpower_sophia_ulg_vc, mcamera_pullud_lowpower_sophia_ulg_vc, mcamera_drv_lowpower_sophia_ulg_vc},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_sophia_ulg_vc[] = {
    &I2C0_SCL_SOPHIA_ULG_VC, &I2C0_SDA_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_sophia_ulg_vc, "block_i2c0", NORMAL, i2c0_pins_sophia_ulg_vc)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_sophia_ulg_vc[] = {
    [NORMAL] = {i2c0_func_normal_sophia_ulg_vc, i2c0_pullud_normal_sophia_ulg_vc, i2c0_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {i2c0_func_lowpower_sophia_ulg_vc, i2c0_pullud_lowpower_sophia_ulg_vc, i2c0_drv_lowpower_sophia_ulg_vc},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_sophia_ulg_vc[] = {
    &I2C1_SCL_SOPHIA_ULG_VC, &I2C1_SDA_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_sophia_ulg_vc, "block_i2c1", NORMAL, i2c1_pins_sophia_ulg_vc)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_sophia_ulg_vc[] = {
    [NORMAL] = {i2c1_func_normal_sophia_ulg_vc, i2c1_pullud_normal_sophia_ulg_vc, i2c1_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {i2c1_func_lowpower_sophia_ulg_vc, i2c1_pullud_lowpower_sophia_ulg_vc, i2c1_drv_lowpower_sophia_ulg_vc},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_sophia_ulg_vc[] = {
    &I2C2_SCL_SOPHIA_ULG_VC, &I2C2_SDA_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_sophia_ulg_vc, "block_i2c2", NORMAL, i2c2_pins_sophia_ulg_vc)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_sophia_ulg_vc[] = {
    [NORMAL] = {i2c2_func_normal_sophia_ulg_vc, i2c2_pullud_normal_sophia_ulg_vc, i2c2_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {i2c2_func_lowpower_sophia_ulg_vc, i2c2_pullud_lowpower_sophia_ulg_vc, i2c2_drv_lowpower_sophia_ulg_vc},

};

/*gps pins */
static struct  iomux_pin *gps_pins_sophia_ulg_vc[] = {
    &GPIO_6_1_SOPHIA_ULG_VC, &RF_GPIO_1_SOPHIA_ULG_VC, &UART3_CTS_N_SOPHIA_ULG_VC, &UART3_RTS_N_SOPHIA_ULG_VC, &UART3_RXD_SOPHIA_ULG_VC, &UART3_TXD_SOPHIA_ULG_VC, &GPS_CLK_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_sophia_ulg_vc, "block_gps", NORMAL, gps_pins_sophia_ulg_vc)



/*GPS*/

static enum lowlayer_func gps_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_sophia_ulg_vc[] = {
    [NORMAL] = {gps_func_normal_sophia_ulg_vc, gps_pullud_normal_sophia_ulg_vc, gps_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {gps_func_lowpower_sophia_ulg_vc, gps_pullud_lowpower_sophia_ulg_vc, gps_drv_lowpower_sophia_ulg_vc},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_sophia_ulg_vc[] = {
    &TCXO0_AFC_SOPHIA_ULG_VC, &TCXO1_AFC_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_sophia_ulg_vc, "block_tcxo", NORMAL, tcxo_pins_sophia_ulg_vc)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_sophia_ulg_vc[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_sophia_ulg_vc[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_sophia_ulg_vc[] = {
    [NORMAL] = {tcxo_func_normal_sophia_ulg_vc, tcxo_pullud_normal_sophia_ulg_vc, tcxo_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {tcxo_func_lowpower_sophia_ulg_vc, tcxo_pullud_lowpower_sophia_ulg_vc, tcxo_drv_lowpower_sophia_ulg_vc},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_sophia_ulg_vc[] = {
    &GPIO_7_5_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_sophia_ulg_vc, "block_rfant", NORMAL, rfant_pins_sophia_ulg_vc)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_sophia_ulg_vc[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_sophia_ulg_vc[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_sophia_ulg_vc[] = {
    [NORMAL] = {rfant_func_normal_sophia_ulg_vc, rfant_pullud_normal_sophia_ulg_vc, rfant_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {rfant_func_lowpower_sophia_ulg_vc, rfant_pullud_lowpower_sophia_ulg_vc, rfant_drv_lowpower_sophia_ulg_vc},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_sophia_ulg_vc[] = {
    &SDIO_DATA3_SOPHIA_ULG_VC, &SDIO_DATA2_SOPHIA_ULG_VC, &SDIO_DATA1_SOPHIA_ULG_VC, &SDIO_DATA0_SOPHIA_ULG_VC, &SDIO_CMD_SOPHIA_ULG_VC, &SDIO_CLK_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_sophia_ulg_vc, "block_wifi", NORMAL, wifi_pins_sophia_ulg_vc)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_sophia_ulg_vc[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_sophia_ulg_vc[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_sophia_ulg_vc[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_sophia_ulg_vc[] = {
    [NORMAL] = {wifi_func_normal_sophia_ulg_vc, wifi_pullud_normal_sophia_ulg_vc, wifi_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {wifi_func_lowpower_sophia_ulg_vc, wifi_pullud_lowpower_sophia_ulg_vc, wifi_drv_lowpower_sophia_ulg_vc},

};

/*boot pins */
static struct  iomux_pin *boot_pins_sophia_ulg_vc[] = {
    &BOOT_SEL_SOPHIA_ULG_VC, &GPIO_5_2_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_sophia_ulg_vc, "block_boot", NORMAL, boot_pins_sophia_ulg_vc)



/*BOOT*/

static enum lowlayer_func boot_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_sophia_ulg_vc[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_sophia_ulg_vc[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_sophia_ulg_vc[] = {
    [NORMAL] = {boot_func_normal_sophia_ulg_vc, boot_pullud_normal_sophia_ulg_vc, boot_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {boot_func_lowpower_sophia_ulg_vc, boot_pullud_lowpower_sophia_ulg_vc, boot_drv_lowpower_sophia_ulg_vc},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_sophia_ulg_vc[] = {
    &PWM_OUT1_SOPHIA_ULG_VC, &GPIO_4_6_SOPHIA_ULG_VC, &GPIO_4_7_SOPHIA_ULG_VC, &GPIO_6_6_SOPHIA_ULG_VC, &PWM_OUT0_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_sophia_ulg_vc, "block_lcd", NORMAL, lcd_pins_sophia_ulg_vc)



/*LCD*/

static enum lowlayer_func lcd_func_normal_sophia_ulg_vc[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_sophia_ulg_vc[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_sophia_ulg_vc[] = {
    [NORMAL] = {lcd_func_normal_sophia_ulg_vc, lcd_pullud_normal_sophia_ulg_vc, lcd_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {lcd_func_lowpower_sophia_ulg_vc, lcd_pullud_lowpower_sophia_ulg_vc, lcd_drv_lowpower_sophia_ulg_vc},

};

/*key pins */
static struct  iomux_pin *key_pins_sophia_ulg_vc[] = {
    &GPIO_4_2_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_sophia_ulg_vc, "block_key", NORMAL, key_pins_sophia_ulg_vc)



/*KEY*/

static enum lowlayer_func key_func_normal_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_sophia_ulg_vc[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_sophia_ulg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_sophia_ulg_vc[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_sophia_ulg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config key_config_sophia_ulg_vc[] = {
    [NORMAL] = {key_func_normal_sophia_ulg_vc, key_pullud_normal_sophia_ulg_vc, key_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {key_func_lowpower_sophia_ulg_vc, key_pullud_lowpower_sophia_ulg_vc, key_drv_lowpower_sophia_ulg_vc},

};

/*test pins */
static struct  iomux_pin *test_pins_sophia_ulg_vc[] = {
    &UART0_RXD_SOPHIA_ULG_VC, &UART0_TXD_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_sophia_ulg_vc, "block_test", NORMAL, test_pins_sophia_ulg_vc)



/*TEST*/

static enum lowlayer_func test_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_sophia_ulg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_sophia_ulg_vc[] = {
    [NORMAL] = {test_func_normal_sophia_ulg_vc, test_pullud_normal_sophia_ulg_vc, test_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {test_func_lowpower_sophia_ulg_vc, test_pullud_lowpower_sophia_ulg_vc, test_drv_lowpower_sophia_ulg_vc},

};

/*sd pins */
static struct  iomux_pin *sd_pins_sophia_ulg_vc[] = {
    &SD_CLK_SOPHIA_ULG_VC, &SD_CMD_SOPHIA_ULG_VC, &SD_DATA0_SOPHIA_ULG_VC, &SD_DATA1_SOPHIA_ULG_VC, &SD_DATA2_SOPHIA_ULG_VC, &SD_DATA3_SOPHIA_ULG_VC,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_sophia_ulg_vc, "block_sd", NORMAL, sd_pins_sophia_ulg_vc)



/*SD*/

static enum lowlayer_func sd_func_normal_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_sophia_ulg_vc[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_sophia_ulg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_sophia_ulg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_sophia_ulg_vc[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_sophia_ulg_vc[] = {
    [NORMAL] = {sd_func_normal_sophia_ulg_vc, sd_pullud_normal_sophia_ulg_vc, sd_drv_normal_sophia_ulg_vc},
    [LOWPOWER] = {sd_func_lowpower_sophia_ulg_vc, sd_pullud_lowpower_sophia_ulg_vc, sd_drv_lowpower_sophia_ulg_vc},

};

struct iomux_block_table block_config_table_sophia_ulg_vc[] = {
    BLOCK_CONFIG("block_charger", &block_charger_sophia_ulg_vc, charger_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_flash", &block_flash_sophia_ulg_vc, flash_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_bt", &block_bt_sophia_ulg_vc, bt_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_scamera", &block_scamera_sophia_ulg_vc, scamera_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_codec", &block_codec_sophia_ulg_vc, codec_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_pmu", &block_pmu_sophia_ulg_vc, pmu_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_spi0", &block_spi0_sophia_ulg_vc, spi0_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_emmc", &block_emmc_sophia_ulg_vc, emmc_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_odt", &block_odt_sophia_ulg_vc, odt_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_rf", &block_rf_sophia_ulg_vc, rf_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_tp", &block_tp_sophia_ulg_vc, tp_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_switch", &block_switch_sophia_ulg_vc, switch_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_sophia_ulg_vc, rfpmu_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_sophia_ulg_vc, i2c3_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_usim1", &block_usim1_sophia_ulg_vc, usim1_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_usim0", &block_usim0_sophia_ulg_vc, usim0_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_sophia_ulg_vc, mcamera_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_sophia_ulg_vc, i2c0_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_sophia_ulg_vc, i2c1_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_sophia_ulg_vc, i2c2_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_gps", &block_gps_sophia_ulg_vc, gps_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_sophia_ulg_vc, tcxo_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_rfant", &block_rfant_sophia_ulg_vc, rfant_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_wifi", &block_wifi_sophia_ulg_vc, wifi_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_boot", &block_boot_sophia_ulg_vc, boot_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_lcd", &block_lcd_sophia_ulg_vc, lcd_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_key", &block_key_sophia_ulg_vc, key_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_test", &block_test_sophia_ulg_vc, test_config_sophia_ulg_vc)
    BLOCK_CONFIG("block_sd", &block_sd_sophia_ulg_vc, sd_config_sophia_ulg_vc)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
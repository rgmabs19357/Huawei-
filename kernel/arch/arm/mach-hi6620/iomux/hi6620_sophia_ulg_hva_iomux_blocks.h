/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_sophia_ulg_hva_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_SOPHIA_ULG_HVA_IOMUX_BLOCKS_H__
#define __HI6620_SOPHIA_ULG_HVA_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_sophia_ulg_hva_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_sophia_ulg_hva[] = {
    &GPIO_4_0_SOPHIA_ULG_HVA, &GPIO_4_1_SOPHIA_ULG_HVA, &UART2_RTS_N_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_sophia_ulg_hva, "block_charger", NORMAL, charger_pins_sophia_ulg_hva)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_sophia_ulg_hva[] = {
    [NORMAL] = {charger_func_normal_sophia_ulg_hva, charger_pullud_normal_sophia_ulg_hva, charger_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {charger_func_lowpower_sophia_ulg_hva, charger_pullud_lowpower_sophia_ulg_hva, charger_drv_lowpower_sophia_ulg_hva},

};

/*flash pins */
static struct  iomux_pin *flash_pins_sophia_ulg_hva[] = {
    &ISP_GPIO5_SOPHIA_ULG_HVA, &RF_GPIO_20_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_sophia_ulg_hva, "block_flash", NORMAL, flash_pins_sophia_ulg_hva)



/*FLASH*/

static enum lowlayer_func flash_func_normal_sophia_ulg_hva[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_sophia_ulg_hva[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_sophia_ulg_hva[] = {
    [NORMAL] = {flash_func_normal_sophia_ulg_hva, flash_pullud_normal_sophia_ulg_hva, flash_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {flash_func_lowpower_sophia_ulg_hva, flash_pullud_lowpower_sophia_ulg_hva, flash_drv_lowpower_sophia_ulg_hva},

};

/*bt pins */
static struct  iomux_pin *bt_pins_sophia_ulg_hva[] = {
    &UART4_CTS_N_SOPHIA_ULG_HVA, &UART4_RTS_N_SOPHIA_ULG_HVA, &UART4_RXD_SOPHIA_ULG_HVA, &UART4_TXD_SOPHIA_ULG_HVA, &GPIO_15_7_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_sophia_ulg_hva, "block_bt", NORMAL, bt_pins_sophia_ulg_hva)



/*BT*/

static enum lowlayer_func bt_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_sophia_ulg_hva[] = {
    [NORMAL] = {bt_func_normal_sophia_ulg_hva, bt_pullud_normal_sophia_ulg_hva, bt_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {bt_func_lowpower_sophia_ulg_hva, bt_pullud_lowpower_sophia_ulg_hva, bt_drv_lowpower_sophia_ulg_hva},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_sophia_ulg_hva[] = {
    &ISP_GPIO1_SOPHIA_ULG_HVA, &ISP_GPIO4_SOPHIA_ULG_HVA, &ISP_RESETB1_SOPHIA_ULG_HVA, &ISP_CCLK1_SOPHIA_ULG_HVA, &ISP_SDA1_SOPHIA_ULG_HVA, &ISP_SCL1_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_sophia_ulg_hva, "block_scamera", NORMAL, scamera_pins_sophia_ulg_hva)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_sophia_ulg_hva[] = {
    [NORMAL] = {scamera_func_normal_sophia_ulg_hva, scamera_pullud_normal_sophia_ulg_hva, scamera_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {scamera_func_lowpower_sophia_ulg_hva, scamera_pullud_lowpower_sophia_ulg_hva, scamera_drv_lowpower_sophia_ulg_hva},

};

/*codec pins */
static struct  iomux_pin *codec_pins_sophia_ulg_hva[] = {
    &PCM1_XCLK_SOPHIA_ULG_HVA, &PCM1_XFS_SOPHIA_ULG_HVA, &PCM1_DI_SOPHIA_ULG_HVA, &PCM1_DO_SOPHIA_ULG_HVA, &I2S_XCLK_SOPHIA_ULG_HVA, &I2S_XFS_SOPHIA_ULG_HVA, &I2S_DI_SOPHIA_ULG_HVA, &I2S_DO_SOPHIA_ULG_HVA, &PCM0_XCLK_SOPHIA_ULG_HVA, &PCM0_XFS_SOPHIA_ULG_HVA, &PCM0_DI_SOPHIA_ULG_HVA, &PCM0_DO_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_sophia_ulg_hva, "block_codec", NORMAL, codec_pins_sophia_ulg_hva)



/*CODEC*/

static enum lowlayer_func codec_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_sophia_ulg_hva[] = {
    [NORMAL] = {codec_func_normal_sophia_ulg_hva, codec_pullud_normal_sophia_ulg_hva, codec_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {codec_func_lowpower_sophia_ulg_hva, codec_pullud_lowpower_sophia_ulg_hva, codec_drv_lowpower_sophia_ulg_hva},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_sophia_ulg_hva[] = {
    &HKADC_SSI_SOPHIA_ULG_HVA, &AUX_SSI0_SOPHIA_ULG_HVA, &AUX_SSI1_SOPHIA_ULG_HVA, &GPIO_5_0_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_sophia_ulg_hva, "block_pmu", NORMAL, pmu_pins_sophia_ulg_hva)



/*PMU*/

static enum lowlayer_func pmu_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_sophia_ulg_hva[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_sophia_ulg_hva[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_sophia_ulg_hva[] = {
    [NORMAL] = {pmu_func_normal_sophia_ulg_hva, pmu_pullud_normal_sophia_ulg_hva, pmu_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {pmu_func_lowpower_sophia_ulg_hva, pmu_pullud_lowpower_sophia_ulg_hva, pmu_drv_lowpower_sophia_ulg_hva},

};

/*spi0 pins */
static struct  iomux_pin *spi0_pins_sophia_ulg_hva[] = {
    &TS_CLK_SOPHIA_ULG_HVA, &TS_DATA_SOPHIA_ULG_HVA, &TS_SYNC_SOPHIA_ULG_HVA, &TS_VALID_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: spi0*/
IOMUX_BLOCK(block_spi0_sophia_ulg_hva, "block_spi0", NORMAL, spi0_pins_sophia_ulg_hva)



/*SPI0*/

static enum lowlayer_func spi0_func_normal_sophia_ulg_hva[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func spi0_func_lowpower_sophia_ulg_hva[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config spi0_config_sophia_ulg_hva[] = {
    [NORMAL] = {spi0_func_normal_sophia_ulg_hva, spi0_pullud_normal_sophia_ulg_hva, spi0_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {spi0_func_lowpower_sophia_ulg_hva, spi0_pullud_lowpower_sophia_ulg_hva, spi0_drv_lowpower_sophia_ulg_hva},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_sophia_ulg_hva[] = {
    &EMMC_CLK_SOPHIA_ULG_HVA, &EMMC_CMD_SOPHIA_ULG_HVA, &EMMC_DATA0_SOPHIA_ULG_HVA, &EMMC_DATA1_SOPHIA_ULG_HVA, &EMMC_DATA2_SOPHIA_ULG_HVA, &EMMC_DATA3_SOPHIA_ULG_HVA, &EMMC_DATA4_SOPHIA_ULG_HVA, &EMMC_DATA5_SOPHIA_ULG_HVA, &EMMC_DATA6_SOPHIA_ULG_HVA, &EMMC_DATA7_SOPHIA_ULG_HVA, &GPIO_2_3_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_sophia_ulg_hva, "block_emmc", NORMAL, emmc_pins_sophia_ulg_hva)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_sophia_ulg_hva[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_sophia_ulg_hva[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_sophia_ulg_hva[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_sophia_ulg_hva[] = {
    [NORMAL] = {emmc_func_normal_sophia_ulg_hva, emmc_pullud_normal_sophia_ulg_hva, emmc_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {emmc_func_lowpower_sophia_ulg_hva, emmc_pullud_lowpower_sophia_ulg_hva, emmc_drv_lowpower_sophia_ulg_hva},

};

/*odt pins */
static struct  iomux_pin *odt_pins_sophia_ulg_hva[] = {
    &RF_RESET1_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_sophia_ulg_hva, "block_odt", NORMAL, odt_pins_sophia_ulg_hva)



/*ODT*/

static enum lowlayer_func odt_func_normal_sophia_ulg_hva[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_sophia_ulg_hva[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_sophia_ulg_hva[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_sophia_ulg_hva[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_sophia_ulg_hva[] = {
    [NORMAL] = {odt_func_normal_sophia_ulg_hva, odt_pullud_normal_sophia_ulg_hva, odt_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {odt_func_lowpower_sophia_ulg_hva, odt_pullud_lowpower_sophia_ulg_hva, odt_drv_lowpower_sophia_ulg_hva},

};

/*rf pins */
static struct  iomux_pin *rf_pins_sophia_ulg_hva[] = {
    &RF_TX_EN1_SOPHIA_ULG_HVA, &RF_TCVR_ON0_SOPHIA_ULG_HVA, &RF_TCVR_ON1_SOPHIA_ULG_HVA, &RF_SSI0_SOPHIA_ULG_HVA, &RF_SSI1_SOPHIA_ULG_HVA, &RF_GPIO_2_SOPHIA_ULG_HVA, &RF_GPIO_3_SOPHIA_ULG_HVA, &RF_GPIO_4_SOPHIA_ULG_HVA, &RF_GPIO_5_SOPHIA_ULG_HVA, &RF_GPIO_6_SOPHIA_ULG_HVA, &RF_GPIO_7_SOPHIA_ULG_HVA, &RF_GPIO_13_SOPHIA_ULG_HVA, &RF_GPIO_14_SOPHIA_ULG_HVA, &RF_GPIO_15_SOPHIA_ULG_HVA, &RF_GPIO_16_SOPHIA_ULG_HVA, &RF_GPIO_17_SOPHIA_ULG_HVA, &RF_GPIO_18_SOPHIA_ULG_HVA, &RF_GPIO_23_SOPHIA_ULG_HVA, &RF_GPIO_24_SOPHIA_ULG_HVA, &RF_GPIO_26_SOPHIA_ULG_HVA, &RF_GPIO_27_SOPHIA_ULG_HVA, &RF_GPIO_28_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_sophia_ulg_hva, "block_rf", NORMAL, rf_pins_sophia_ulg_hva)



/*RF*/

static enum lowlayer_func rf_func_normal_sophia_ulg_hva[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_sophia_ulg_hva[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_sophia_ulg_hva[] = {
    [NORMAL] = {rf_func_normal_sophia_ulg_hva, rf_pullud_normal_sophia_ulg_hva, rf_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {rf_func_lowpower_sophia_ulg_hva, rf_pullud_lowpower_sophia_ulg_hva, rf_drv_lowpower_sophia_ulg_hva},

};

/*tp pins */
static struct  iomux_pin *tp_pins_sophia_ulg_hva[] = {
    &GPIO_18_7_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_sophia_ulg_hva, "block_tp", NORMAL, tp_pins_sophia_ulg_hva)



/*TP*/

static enum lowlayer_func tp_func_normal_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_sophia_ulg_hva[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_sophia_ulg_hva[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_sophia_ulg_hva[] = {
    [NORMAL] = {tp_func_normal_sophia_ulg_hva, tp_pullud_normal_sophia_ulg_hva, tp_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {tp_func_lowpower_sophia_ulg_hva, tp_pullud_lowpower_sophia_ulg_hva, tp_drv_lowpower_sophia_ulg_hva},

};

/*switch pins */
static struct  iomux_pin *switch_pins_sophia_ulg_hva[] = {
    &GPIO_5_3_SOPHIA_ULG_HVA, &GPIO_6_2_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_sophia_ulg_hva, "block_switch", NORMAL, switch_pins_sophia_ulg_hva)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_sophia_ulg_hva[] = {
    [NORMAL] = {switch_func_normal_sophia_ulg_hva, switch_pullud_normal_sophia_ulg_hva, switch_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {switch_func_lowpower_sophia_ulg_hva, switch_pullud_lowpower_sophia_ulg_hva, switch_drv_lowpower_sophia_ulg_hva},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_sophia_ulg_hva[] = {
    &RF_MIPI_CLK0_SOPHIA_ULG_HVA, &RF_MIPI_DATA0_SOPHIA_ULG_HVA, &APT_PDM0_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_sophia_ulg_hva, "block_rfpmu", NORMAL, rfpmu_pins_sophia_ulg_hva)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_sophia_ulg_hva[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_sophia_ulg_hva[] = {
    [NORMAL] = {rfpmu_func_normal_sophia_ulg_hva, rfpmu_pullud_normal_sophia_ulg_hva, rfpmu_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {rfpmu_func_lowpower_sophia_ulg_hva, rfpmu_pullud_lowpower_sophia_ulg_hva, rfpmu_drv_lowpower_sophia_ulg_hva},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_sophia_ulg_hva[] = {
    &I2C3_SCL_SOPHIA_ULG_HVA, &I2C3_SDA_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_sophia_ulg_hva, "block_i2c3", NORMAL, i2c3_pins_sophia_ulg_hva)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_sophia_ulg_hva[] = {
    [NORMAL] = {i2c3_func_normal_sophia_ulg_hva, i2c3_pullud_normal_sophia_ulg_hva, i2c3_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {i2c3_func_lowpower_sophia_ulg_hva, i2c3_pullud_lowpower_sophia_ulg_hva, i2c3_drv_lowpower_sophia_ulg_hva},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_sophia_ulg_hva[] = {
    &USIM1_CLK_SOPHIA_ULG_HVA, &USIM1_DATA_SOPHIA_ULG_HVA, &USIM1_RST_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_sophia_ulg_hva, "block_usim1", NORMAL, usim1_pins_sophia_ulg_hva)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_sophia_ulg_hva[] = {
    [NORMAL] = {usim1_func_normal_sophia_ulg_hva, usim1_pullud_normal_sophia_ulg_hva, usim1_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {usim1_func_lowpower_sophia_ulg_hva, usim1_pullud_lowpower_sophia_ulg_hva, usim1_drv_lowpower_sophia_ulg_hva},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_sophia_ulg_hva[] = {
    &USIM0_CLK_SOPHIA_ULG_HVA, &USIM0_DATA_SOPHIA_ULG_HVA, &USIM0_RST_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_sophia_ulg_hva, "block_usim0", NORMAL, usim0_pins_sophia_ulg_hva)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_sophia_ulg_hva[] = {
    [NORMAL] = {usim0_func_normal_sophia_ulg_hva, usim0_pullud_normal_sophia_ulg_hva, usim0_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {usim0_func_lowpower_sophia_ulg_hva, usim0_pullud_lowpower_sophia_ulg_hva, usim0_drv_lowpower_sophia_ulg_hva},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_sophia_ulg_hva[] = {
    &ISP_GPIO0_SOPHIA_ULG_HVA, &ISP_GPIO2_SOPHIA_ULG_HVA, &ISP_GPIO3_SOPHIA_ULG_HVA, &ISP_RESETB0_SOPHIA_ULG_HVA, &ISP_CCLK0_SOPHIA_ULG_HVA, &ISP_SDA0_SOPHIA_ULG_HVA, &ISP_SCL0_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_sophia_ulg_hva, "block_mcamera", NORMAL, mcamera_pins_sophia_ulg_hva)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_sophia_ulg_hva[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_sophia_ulg_hva[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_sophia_ulg_hva[] = {
    [NORMAL] = {mcamera_func_normal_sophia_ulg_hva, mcamera_pullud_normal_sophia_ulg_hva, mcamera_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {mcamera_func_lowpower_sophia_ulg_hva, mcamera_pullud_lowpower_sophia_ulg_hva, mcamera_drv_lowpower_sophia_ulg_hva},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_sophia_ulg_hva[] = {
    &I2C0_SCL_SOPHIA_ULG_HVA, &I2C0_SDA_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_sophia_ulg_hva, "block_i2c0", NORMAL, i2c0_pins_sophia_ulg_hva)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_sophia_ulg_hva[] = {
    [NORMAL] = {i2c0_func_normal_sophia_ulg_hva, i2c0_pullud_normal_sophia_ulg_hva, i2c0_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {i2c0_func_lowpower_sophia_ulg_hva, i2c0_pullud_lowpower_sophia_ulg_hva, i2c0_drv_lowpower_sophia_ulg_hva},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_sophia_ulg_hva[] = {
    &I2C1_SCL_SOPHIA_ULG_HVA, &I2C1_SDA_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_sophia_ulg_hva, "block_i2c1", NORMAL, i2c1_pins_sophia_ulg_hva)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_sophia_ulg_hva[] = {
    [NORMAL] = {i2c1_func_normal_sophia_ulg_hva, i2c1_pullud_normal_sophia_ulg_hva, i2c1_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {i2c1_func_lowpower_sophia_ulg_hva, i2c1_pullud_lowpower_sophia_ulg_hva, i2c1_drv_lowpower_sophia_ulg_hva},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_sophia_ulg_hva[] = {
    &I2C2_SCL_SOPHIA_ULG_HVA, &I2C2_SDA_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_sophia_ulg_hva, "block_i2c2", NORMAL, i2c2_pins_sophia_ulg_hva)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_sophia_ulg_hva[] = {
    [NORMAL] = {i2c2_func_normal_sophia_ulg_hva, i2c2_pullud_normal_sophia_ulg_hva, i2c2_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {i2c2_func_lowpower_sophia_ulg_hva, i2c2_pullud_lowpower_sophia_ulg_hva, i2c2_drv_lowpower_sophia_ulg_hva},

};

/*gps pins */
static struct  iomux_pin *gps_pins_sophia_ulg_hva[] = {
    &GPIO_6_1_SOPHIA_ULG_HVA, &RF_GPIO_1_SOPHIA_ULG_HVA, &UART3_CTS_N_SOPHIA_ULG_HVA, &UART3_RTS_N_SOPHIA_ULG_HVA, &UART3_RXD_SOPHIA_ULG_HVA, &UART3_TXD_SOPHIA_ULG_HVA, &GPS_CLK_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_sophia_ulg_hva, "block_gps", NORMAL, gps_pins_sophia_ulg_hva)



/*GPS*/

static enum lowlayer_func gps_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_sophia_ulg_hva[] = {
    [NORMAL] = {gps_func_normal_sophia_ulg_hva, gps_pullud_normal_sophia_ulg_hva, gps_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {gps_func_lowpower_sophia_ulg_hva, gps_pullud_lowpower_sophia_ulg_hva, gps_drv_lowpower_sophia_ulg_hva},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_sophia_ulg_hva[] = {
    &TCXO0_AFC_SOPHIA_ULG_HVA, &TCXO1_AFC_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_sophia_ulg_hva, "block_tcxo", NORMAL, tcxo_pins_sophia_ulg_hva)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_sophia_ulg_hva[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_sophia_ulg_hva[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_sophia_ulg_hva[] = {
    [NORMAL] = {tcxo_func_normal_sophia_ulg_hva, tcxo_pullud_normal_sophia_ulg_hva, tcxo_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {tcxo_func_lowpower_sophia_ulg_hva, tcxo_pullud_lowpower_sophia_ulg_hva, tcxo_drv_lowpower_sophia_ulg_hva},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_sophia_ulg_hva[] = {
    &GPIO_7_5_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_sophia_ulg_hva, "block_rfant", NORMAL, rfant_pins_sophia_ulg_hva)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_sophia_ulg_hva[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_sophia_ulg_hva[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_sophia_ulg_hva[] = {
    [NORMAL] = {rfant_func_normal_sophia_ulg_hva, rfant_pullud_normal_sophia_ulg_hva, rfant_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {rfant_func_lowpower_sophia_ulg_hva, rfant_pullud_lowpower_sophia_ulg_hva, rfant_drv_lowpower_sophia_ulg_hva},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_sophia_ulg_hva[] = {
    &SDIO_DATA3_SOPHIA_ULG_HVA, &SDIO_DATA2_SOPHIA_ULG_HVA, &SDIO_DATA1_SOPHIA_ULG_HVA, &SDIO_DATA0_SOPHIA_ULG_HVA, &SDIO_CMD_SOPHIA_ULG_HVA, &SDIO_CLK_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_sophia_ulg_hva, "block_wifi", NORMAL, wifi_pins_sophia_ulg_hva)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_sophia_ulg_hva[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_sophia_ulg_hva[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_sophia_ulg_hva[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_sophia_ulg_hva[] = {
    [NORMAL] = {wifi_func_normal_sophia_ulg_hva, wifi_pullud_normal_sophia_ulg_hva, wifi_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {wifi_func_lowpower_sophia_ulg_hva, wifi_pullud_lowpower_sophia_ulg_hva, wifi_drv_lowpower_sophia_ulg_hva},

};

/*boot pins */
static struct  iomux_pin *boot_pins_sophia_ulg_hva[] = {
    &BOOT_SEL_SOPHIA_ULG_HVA, &GPIO_5_2_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_sophia_ulg_hva, "block_boot", NORMAL, boot_pins_sophia_ulg_hva)



/*BOOT*/

static enum lowlayer_func boot_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_sophia_ulg_hva[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_sophia_ulg_hva[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_sophia_ulg_hva[] = {
    [NORMAL] = {boot_func_normal_sophia_ulg_hva, boot_pullud_normal_sophia_ulg_hva, boot_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {boot_func_lowpower_sophia_ulg_hva, boot_pullud_lowpower_sophia_ulg_hva, boot_drv_lowpower_sophia_ulg_hva},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_sophia_ulg_hva[] = {
    &PWM_OUT1_SOPHIA_ULG_HVA, &GPIO_4_6_SOPHIA_ULG_HVA, &GPIO_4_7_SOPHIA_ULG_HVA, &GPIO_6_6_SOPHIA_ULG_HVA, &PWM_OUT0_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_sophia_ulg_hva, "block_lcd", NORMAL, lcd_pins_sophia_ulg_hva)



/*LCD*/

static enum lowlayer_func lcd_func_normal_sophia_ulg_hva[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_sophia_ulg_hva[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_sophia_ulg_hva[] = {
    [NORMAL] = {lcd_func_normal_sophia_ulg_hva, lcd_pullud_normal_sophia_ulg_hva, lcd_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {lcd_func_lowpower_sophia_ulg_hva, lcd_pullud_lowpower_sophia_ulg_hva, lcd_drv_lowpower_sophia_ulg_hva},

};

/*key pins */
static struct  iomux_pin *key_pins_sophia_ulg_hva[] = {
    &GPIO_4_2_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_sophia_ulg_hva, "block_key", NORMAL, key_pins_sophia_ulg_hva)



/*KEY*/

static enum lowlayer_func key_func_normal_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_sophia_ulg_hva[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_sophia_ulg_hva[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_sophia_ulg_hva[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_sophia_ulg_hva[] = {LEVEL0,  -INVALID,};

static struct block_config key_config_sophia_ulg_hva[] = {
    [NORMAL] = {key_func_normal_sophia_ulg_hva, key_pullud_normal_sophia_ulg_hva, key_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {key_func_lowpower_sophia_ulg_hva, key_pullud_lowpower_sophia_ulg_hva, key_drv_lowpower_sophia_ulg_hva},

};

/*test pins */
static struct  iomux_pin *test_pins_sophia_ulg_hva[] = {
    &UART0_RXD_SOPHIA_ULG_HVA, &UART0_TXD_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_sophia_ulg_hva, "block_test", NORMAL, test_pins_sophia_ulg_hva)



/*TEST*/

static enum lowlayer_func test_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_sophia_ulg_hva[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_sophia_ulg_hva[] = {
    [NORMAL] = {test_func_normal_sophia_ulg_hva, test_pullud_normal_sophia_ulg_hva, test_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {test_func_lowpower_sophia_ulg_hva, test_pullud_lowpower_sophia_ulg_hva, test_drv_lowpower_sophia_ulg_hva},

};

/*sd pins */
static struct  iomux_pin *sd_pins_sophia_ulg_hva[] = {
    &SD_CLK_SOPHIA_ULG_HVA, &SD_CMD_SOPHIA_ULG_HVA, &SD_DATA0_SOPHIA_ULG_HVA, &SD_DATA1_SOPHIA_ULG_HVA, &SD_DATA2_SOPHIA_ULG_HVA, &SD_DATA3_SOPHIA_ULG_HVA,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_sophia_ulg_hva, "block_sd", NORMAL, sd_pins_sophia_ulg_hva)



/*SD*/

static enum lowlayer_func sd_func_normal_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_sophia_ulg_hva[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_sophia_ulg_hva[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_sophia_ulg_hva[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_sophia_ulg_hva[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_sophia_ulg_hva[] = {
    [NORMAL] = {sd_func_normal_sophia_ulg_hva, sd_pullud_normal_sophia_ulg_hva, sd_drv_normal_sophia_ulg_hva},
    [LOWPOWER] = {sd_func_lowpower_sophia_ulg_hva, sd_pullud_lowpower_sophia_ulg_hva, sd_drv_lowpower_sophia_ulg_hva},

};

struct iomux_block_table block_config_table_sophia_ulg_hva[] = {
    BLOCK_CONFIG("block_charger", &block_charger_sophia_ulg_hva, charger_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_flash", &block_flash_sophia_ulg_hva, flash_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_bt", &block_bt_sophia_ulg_hva, bt_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_scamera", &block_scamera_sophia_ulg_hva, scamera_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_codec", &block_codec_sophia_ulg_hva, codec_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_pmu", &block_pmu_sophia_ulg_hva, pmu_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_spi0", &block_spi0_sophia_ulg_hva, spi0_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_emmc", &block_emmc_sophia_ulg_hva, emmc_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_odt", &block_odt_sophia_ulg_hva, odt_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_rf", &block_rf_sophia_ulg_hva, rf_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_tp", &block_tp_sophia_ulg_hva, tp_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_switch", &block_switch_sophia_ulg_hva, switch_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_sophia_ulg_hva, rfpmu_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_sophia_ulg_hva, i2c3_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_usim1", &block_usim1_sophia_ulg_hva, usim1_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_usim0", &block_usim0_sophia_ulg_hva, usim0_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_sophia_ulg_hva, mcamera_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_sophia_ulg_hva, i2c0_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_sophia_ulg_hva, i2c1_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_sophia_ulg_hva, i2c2_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_gps", &block_gps_sophia_ulg_hva, gps_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_sophia_ulg_hva, tcxo_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_rfant", &block_rfant_sophia_ulg_hva, rfant_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_wifi", &block_wifi_sophia_ulg_hva, wifi_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_boot", &block_boot_sophia_ulg_hva, boot_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_lcd", &block_lcd_sophia_ulg_hva, lcd_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_key", &block_key_sophia_ulg_hva, key_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_test", &block_test_sophia_ulg_hva, test_config_sophia_ulg_hva)
    BLOCK_CONFIG("block_sd", &block_sd_sophia_ulg_hva, sd_config_sophia_ulg_hva)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
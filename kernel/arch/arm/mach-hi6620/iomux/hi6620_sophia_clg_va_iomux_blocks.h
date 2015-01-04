/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_sophia_clg_va_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_SOPHIA_CLG_VA_IOMUX_BLOCKS_H__
#define __HI6620_SOPHIA_CLG_VA_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_sophia_clg_va_iomux_pins.h"
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
static struct  iomux_pin *charger_pins_sophia_clg_va[] = {
    &GPIO_4_0_SOPHIA_CLG_VA, &GPIO_4_1_SOPHIA_CLG_VA, &UART2_RTS_N_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_sophia_clg_va, "block_charger", NORMAL, charger_pins_sophia_clg_va)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config charger_config_sophia_clg_va[] = {
    [NORMAL] = {charger_func_normal_sophia_clg_va, charger_pullud_normal_sophia_clg_va, charger_drv_normal_sophia_clg_va},
    [LOWPOWER] = {charger_func_lowpower_sophia_clg_va, charger_pullud_lowpower_sophia_clg_va, charger_drv_lowpower_sophia_clg_va},

};

/*flash pins */
static struct  iomux_pin *flash_pins_sophia_clg_va[] = {
    &ISP_GPIO5_SOPHIA_CLG_VA, &RF_GPIO_20_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_sophia_clg_va, "block_flash", NORMAL, flash_pins_sophia_clg_va)



/*FLASH*/

static enum lowlayer_func flash_func_normal_sophia_clg_va[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_sophia_clg_va[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_sophia_clg_va[] = {
    [NORMAL] = {flash_func_normal_sophia_clg_va, flash_pullud_normal_sophia_clg_va, flash_drv_normal_sophia_clg_va},
    [LOWPOWER] = {flash_func_lowpower_sophia_clg_va, flash_pullud_lowpower_sophia_clg_va, flash_drv_lowpower_sophia_clg_va},

};

/*bt pins */
static struct  iomux_pin *bt_pins_sophia_clg_va[] = {
    &UART4_CTS_N_SOPHIA_CLG_VA, &UART4_RTS_N_SOPHIA_CLG_VA, &UART4_RXD_SOPHIA_CLG_VA, &UART4_TXD_SOPHIA_CLG_VA, &GPIO_15_7_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_sophia_clg_va, "block_bt", NORMAL, bt_pins_sophia_clg_va)



/*BT*/

static enum lowlayer_func bt_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_sophia_clg_va[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_sophia_clg_va[] = {
    [NORMAL] = {bt_func_normal_sophia_clg_va, bt_pullud_normal_sophia_clg_va, bt_drv_normal_sophia_clg_va},
    [LOWPOWER] = {bt_func_lowpower_sophia_clg_va, bt_pullud_lowpower_sophia_clg_va, bt_drv_lowpower_sophia_clg_va},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_sophia_clg_va[] = {
    &ISP_GPIO1_SOPHIA_CLG_VA, &ISP_GPIO4_SOPHIA_CLG_VA, &ISP_RESETB1_SOPHIA_CLG_VA, &ISP_CCLK1_SOPHIA_CLG_VA, &ISP_SDA1_SOPHIA_CLG_VA, &ISP_SCL1_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_sophia_clg_va, "block_scamera", NORMAL, scamera_pins_sophia_clg_va)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_sophia_clg_va[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_sophia_clg_va[] = {
    [NORMAL] = {scamera_func_normal_sophia_clg_va, scamera_pullud_normal_sophia_clg_va, scamera_drv_normal_sophia_clg_va},
    [LOWPOWER] = {scamera_func_lowpower_sophia_clg_va, scamera_pullud_lowpower_sophia_clg_va, scamera_drv_lowpower_sophia_clg_va},

};

/*codec pins */
static struct  iomux_pin *codec_pins_sophia_clg_va[] = {
    &PCM1_XCLK_SOPHIA_CLG_VA, &PCM1_XFS_SOPHIA_CLG_VA, &PCM1_DI_SOPHIA_CLG_VA, &PCM1_DO_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_sophia_clg_va, "block_codec", NORMAL, codec_pins_sophia_clg_va)



/*CODEC*/

static enum lowlayer_func codec_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_sophia_clg_va[] = {
    [NORMAL] = {codec_func_normal_sophia_clg_va, codec_pullud_normal_sophia_clg_va, codec_drv_normal_sophia_clg_va},
    [LOWPOWER] = {codec_func_lowpower_sophia_clg_va, codec_pullud_lowpower_sophia_clg_va, codec_drv_lowpower_sophia_clg_va},

};

/*modem_switch pins */
static struct  iomux_pin *modem_switch_pins_sophia_clg_va[] = {
    &GPIO_7_6_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: modem_switch*/
IOMUX_BLOCK(block_modem_switch_sophia_clg_va, "block_modem_switch", NORMAL, modem_switch_pins_sophia_clg_va)



/*modem_switch*/

static enum lowlayer_func modem_switch_func_normal_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown modem_switch_pullud_normal_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength modem_switch_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func modem_switch_func_lowpower_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown modem_switch_pullud_lowpower_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength modem_switch_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config modem_switch_config_sophia_clg_va[] = {
    [NORMAL] = {modem_switch_func_normal_sophia_clg_va, modem_switch_pullud_normal_sophia_clg_va, modem_switch_drv_normal_sophia_clg_va},
    [LOWPOWER] = {modem_switch_func_lowpower_sophia_clg_va, modem_switch_pullud_lowpower_sophia_clg_va, modem_switch_drv_lowpower_sophia_clg_va},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_sophia_clg_va[] = {
    &HKADC_SSI_SOPHIA_CLG_VA, &AUX_SSI0_SOPHIA_CLG_VA, &AUX_SSI1_SOPHIA_CLG_VA, &GPIO_5_0_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_sophia_clg_va, "block_pmu", NORMAL, pmu_pins_sophia_clg_va)



/*PMU*/

static enum lowlayer_func pmu_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_sophia_clg_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_sophia_clg_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_sophia_clg_va[] = {
    [NORMAL] = {pmu_func_normal_sophia_clg_va, pmu_pullud_normal_sophia_clg_va, pmu_drv_normal_sophia_clg_va},
    [LOWPOWER] = {pmu_func_lowpower_sophia_clg_va, pmu_pullud_lowpower_sophia_clg_va, pmu_drv_lowpower_sophia_clg_va},

};

/*spi0 pins */
static struct  iomux_pin *spi0_pins_sophia_clg_va[] = {
    &TS_CLK_SOPHIA_CLG_VA, &TS_DATA_SOPHIA_CLG_VA, &TS_SYNC_SOPHIA_CLG_VA, &TS_VALID_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: spi0*/
IOMUX_BLOCK(block_spi0_sophia_clg_va, "block_spi0", NORMAL, spi0_pins_sophia_clg_va)



/*SPI0*/

static enum lowlayer_func spi0_func_normal_sophia_clg_va[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func spi0_func_lowpower_sophia_clg_va[] = {FUNC2, FUNC2, FUNC1, FUNC2,  -INVALID,};
static enum pull_updown spi0_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength spi0_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config spi0_config_sophia_clg_va[] = {
    [NORMAL] = {spi0_func_normal_sophia_clg_va, spi0_pullud_normal_sophia_clg_va, spi0_drv_normal_sophia_clg_va},
    [LOWPOWER] = {spi0_func_lowpower_sophia_clg_va, spi0_pullud_lowpower_sophia_clg_va, spi0_drv_lowpower_sophia_clg_va},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_sophia_clg_va[] = {
    &EMMC_CLK_SOPHIA_CLG_VA, &EMMC_CMD_SOPHIA_CLG_VA, &EMMC_DATA0_SOPHIA_CLG_VA, &EMMC_DATA1_SOPHIA_CLG_VA, &EMMC_DATA2_SOPHIA_CLG_VA, &EMMC_DATA3_SOPHIA_CLG_VA, &EMMC_DATA4_SOPHIA_CLG_VA, &EMMC_DATA5_SOPHIA_CLG_VA, &EMMC_DATA6_SOPHIA_CLG_VA, &EMMC_DATA7_SOPHIA_CLG_VA, &GPIO_2_3_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_sophia_clg_va, "block_emmc", NORMAL, emmc_pins_sophia_clg_va)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_sophia_clg_va[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_sophia_clg_va[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_sophia_clg_va[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_sophia_clg_va[] = {
    [NORMAL] = {emmc_func_normal_sophia_clg_va, emmc_pullud_normal_sophia_clg_va, emmc_drv_normal_sophia_clg_va},
    [LOWPOWER] = {emmc_func_lowpower_sophia_clg_va, emmc_pullud_lowpower_sophia_clg_va, emmc_drv_lowpower_sophia_clg_va},

};

/*odt pins */
static struct  iomux_pin *odt_pins_sophia_clg_va[] = {
    &RF_RESET1_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_sophia_clg_va, "block_odt", NORMAL, odt_pins_sophia_clg_va)



/*ODT*/

static enum lowlayer_func odt_func_normal_sophia_clg_va[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_sophia_clg_va[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_sophia_clg_va[] = {
    [NORMAL] = {odt_func_normal_sophia_clg_va, odt_pullud_normal_sophia_clg_va, odt_drv_normal_sophia_clg_va},
    [LOWPOWER] = {odt_func_lowpower_sophia_clg_va, odt_pullud_lowpower_sophia_clg_va, odt_drv_lowpower_sophia_clg_va},

};

/*rf pins */
static struct  iomux_pin *rf_pins_sophia_clg_va[] = {
    &RF_TX_EN1_SOPHIA_CLG_VA, &RF_TCVR_ON0_SOPHIA_CLG_VA, &RF_TCVR_ON1_SOPHIA_CLG_VA, &RF_SSI0_SOPHIA_CLG_VA, &RF_SSI1_SOPHIA_CLG_VA, &RF_GPIO_2_SOPHIA_CLG_VA, &RF_GPIO_3_SOPHIA_CLG_VA, &RF_GPIO_4_SOPHIA_CLG_VA, &RF_GPIO_5_SOPHIA_CLG_VA, &RF_GPIO_6_SOPHIA_CLG_VA, &RF_GPIO_7_SOPHIA_CLG_VA, &RF_GPIO_13_SOPHIA_CLG_VA, &RF_GPIO_14_SOPHIA_CLG_VA, &RF_GPIO_15_SOPHIA_CLG_VA, &RF_GPIO_16_SOPHIA_CLG_VA, &RF_GPIO_17_SOPHIA_CLG_VA, &RF_GPIO_18_SOPHIA_CLG_VA, &RF_GPIO_23_SOPHIA_CLG_VA, &RF_GPIO_24_SOPHIA_CLG_VA, &RF_GPIO_26_SOPHIA_CLG_VA, &RF_GPIO_27_SOPHIA_CLG_VA, &RF_GPIO_28_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_sophia_clg_va, "block_rf", NORMAL, rf_pins_sophia_clg_va)



/*RF*/

static enum lowlayer_func rf_func_normal_sophia_clg_va[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_sophia_clg_va[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_sophia_clg_va[] = {
    [NORMAL] = {rf_func_normal_sophia_clg_va, rf_pullud_normal_sophia_clg_va, rf_drv_normal_sophia_clg_va},
    [LOWPOWER] = {rf_func_lowpower_sophia_clg_va, rf_pullud_lowpower_sophia_clg_va, rf_drv_lowpower_sophia_clg_va},

};

/*tp pins */
static struct  iomux_pin *tp_pins_sophia_clg_va[] = {
    &GPIO_18_7_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_sophia_clg_va, "block_tp", NORMAL, tp_pins_sophia_clg_va)



/*TP*/

static enum lowlayer_func tp_func_normal_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_sophia_clg_va[] = {
    [NORMAL] = {tp_func_normal_sophia_clg_va, tp_pullud_normal_sophia_clg_va, tp_drv_normal_sophia_clg_va},
    [LOWPOWER] = {tp_func_lowpower_sophia_clg_va, tp_pullud_lowpower_sophia_clg_va, tp_drv_lowpower_sophia_clg_va},

};

/*switch pins */
static struct  iomux_pin *switch_pins_sophia_clg_va[] = {
    &GPIO_5_3_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_sophia_clg_va, "block_switch", NORMAL, switch_pins_sophia_clg_va)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_sophia_clg_va[] = {NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config switch_config_sophia_clg_va[] = {
    [NORMAL] = {switch_func_normal_sophia_clg_va, switch_pullud_normal_sophia_clg_va, switch_drv_normal_sophia_clg_va},
    [LOWPOWER] = {switch_func_lowpower_sophia_clg_va, switch_pullud_lowpower_sophia_clg_va, switch_drv_lowpower_sophia_clg_va},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_sophia_clg_va[] = {
    &RF_MIPI_CLK0_SOPHIA_CLG_VA, &RF_MIPI_DATA0_SOPHIA_CLG_VA, &APT_PDM0_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_sophia_clg_va, "block_rfpmu", NORMAL, rfpmu_pins_sophia_clg_va)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_sophia_clg_va[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_sophia_clg_va[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_sophia_clg_va[] = {
    [NORMAL] = {rfpmu_func_normal_sophia_clg_va, rfpmu_pullud_normal_sophia_clg_va, rfpmu_drv_normal_sophia_clg_va},
    [LOWPOWER] = {rfpmu_func_lowpower_sophia_clg_va, rfpmu_pullud_lowpower_sophia_clg_va, rfpmu_drv_lowpower_sophia_clg_va},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_sophia_clg_va[] = {
    &I2C3_SCL_SOPHIA_CLG_VA, &I2C3_SDA_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_sophia_clg_va, "block_i2c3", NORMAL, i2c3_pins_sophia_clg_va)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_sophia_clg_va[] = {
    [NORMAL] = {i2c3_func_normal_sophia_clg_va, i2c3_pullud_normal_sophia_clg_va, i2c3_drv_normal_sophia_clg_va},
    [LOWPOWER] = {i2c3_func_lowpower_sophia_clg_va, i2c3_pullud_lowpower_sophia_clg_va, i2c3_drv_lowpower_sophia_clg_va},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_sophia_clg_va[] = {
    &USIM1_CLK_SOPHIA_CLG_VA, &USIM1_DATA_SOPHIA_CLG_VA, &USIM1_RST_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_sophia_clg_va, "block_usim1", NORMAL, usim1_pins_sophia_clg_va)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_sophia_clg_va[] = {
    [NORMAL] = {usim1_func_normal_sophia_clg_va, usim1_pullud_normal_sophia_clg_va, usim1_drv_normal_sophia_clg_va},
    [LOWPOWER] = {usim1_func_lowpower_sophia_clg_va, usim1_pullud_lowpower_sophia_clg_va, usim1_drv_lowpower_sophia_clg_va},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_sophia_clg_va[] = {
    &USIM0_CLK_SOPHIA_CLG_VA, &USIM0_DATA_SOPHIA_CLG_VA, &USIM0_RST_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_sophia_clg_va, "block_usim0", NORMAL, usim0_pins_sophia_clg_va)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_sophia_clg_va[] = {
    [NORMAL] = {usim0_func_normal_sophia_clg_va, usim0_pullud_normal_sophia_clg_va, usim0_drv_normal_sophia_clg_va},
    [LOWPOWER] = {usim0_func_lowpower_sophia_clg_va, usim0_pullud_lowpower_sophia_clg_va, usim0_drv_lowpower_sophia_clg_va},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_sophia_clg_va[] = {
    &ISP_GPIO0_SOPHIA_CLG_VA, &ISP_GPIO2_SOPHIA_CLG_VA, &ISP_GPIO3_SOPHIA_CLG_VA, &ISP_RESETB0_SOPHIA_CLG_VA, &ISP_CCLK0_SOPHIA_CLG_VA, &ISP_SDA0_SOPHIA_CLG_VA, &ISP_SCL0_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_sophia_clg_va, "block_mcamera", NORMAL, mcamera_pins_sophia_clg_va)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_sophia_clg_va[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_sophia_clg_va[] = {FUNC2, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_sophia_clg_va[] = {
    [NORMAL] = {mcamera_func_normal_sophia_clg_va, mcamera_pullud_normal_sophia_clg_va, mcamera_drv_normal_sophia_clg_va},
    [LOWPOWER] = {mcamera_func_lowpower_sophia_clg_va, mcamera_pullud_lowpower_sophia_clg_va, mcamera_drv_lowpower_sophia_clg_va},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_sophia_clg_va[] = {
    &I2C0_SCL_SOPHIA_CLG_VA, &I2C0_SDA_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_sophia_clg_va, "block_i2c0", NORMAL, i2c0_pins_sophia_clg_va)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_sophia_clg_va[] = {
    [NORMAL] = {i2c0_func_normal_sophia_clg_va, i2c0_pullud_normal_sophia_clg_va, i2c0_drv_normal_sophia_clg_va},
    [LOWPOWER] = {i2c0_func_lowpower_sophia_clg_va, i2c0_pullud_lowpower_sophia_clg_va, i2c0_drv_lowpower_sophia_clg_va},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_sophia_clg_va[] = {
    &I2C1_SCL_SOPHIA_CLG_VA, &I2C1_SDA_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_sophia_clg_va, "block_i2c1", NORMAL, i2c1_pins_sophia_clg_va)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_sophia_clg_va[] = {
    [NORMAL] = {i2c1_func_normal_sophia_clg_va, i2c1_pullud_normal_sophia_clg_va, i2c1_drv_normal_sophia_clg_va},
    [LOWPOWER] = {i2c1_func_lowpower_sophia_clg_va, i2c1_pullud_lowpower_sophia_clg_va, i2c1_drv_lowpower_sophia_clg_va},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_sophia_clg_va[] = {
    &I2C2_SCL_SOPHIA_CLG_VA, &I2C2_SDA_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_sophia_clg_va, "block_i2c2", NORMAL, i2c2_pins_sophia_clg_va)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_sophia_clg_va[] = {
    [NORMAL] = {i2c2_func_normal_sophia_clg_va, i2c2_pullud_normal_sophia_clg_va, i2c2_drv_normal_sophia_clg_va},
    [LOWPOWER] = {i2c2_func_lowpower_sophia_clg_va, i2c2_pullud_lowpower_sophia_clg_va, i2c2_drv_lowpower_sophia_clg_va},

};

/*gps pins */
static struct  iomux_pin *gps_pins_sophia_clg_va[] = {
    &GPIO_6_1_SOPHIA_CLG_VA, &RF_GPIO_1_SOPHIA_CLG_VA, &UART3_CTS_N_SOPHIA_CLG_VA, &UART3_RTS_N_SOPHIA_CLG_VA, &UART3_RXD_SOPHIA_CLG_VA, &UART3_TXD_SOPHIA_CLG_VA, &GPS_CLK_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_sophia_clg_va, "block_gps", NORMAL, gps_pins_sophia_clg_va)



/*GPS*/

static enum lowlayer_func gps_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_sophia_clg_va[] = {
    [NORMAL] = {gps_func_normal_sophia_clg_va, gps_pullud_normal_sophia_clg_va, gps_drv_normal_sophia_clg_va},
    [LOWPOWER] = {gps_func_lowpower_sophia_clg_va, gps_pullud_lowpower_sophia_clg_va, gps_drv_lowpower_sophia_clg_va},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_sophia_clg_va[] = {
    &TCXO0_AFC_SOPHIA_CLG_VA, &TCXO1_AFC_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_sophia_clg_va, "block_tcxo", NORMAL, tcxo_pins_sophia_clg_va)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_sophia_clg_va[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_sophia_clg_va[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_sophia_clg_va[] = {
    [NORMAL] = {tcxo_func_normal_sophia_clg_va, tcxo_pullud_normal_sophia_clg_va, tcxo_drv_normal_sophia_clg_va},
    [LOWPOWER] = {tcxo_func_lowpower_sophia_clg_va, tcxo_pullud_lowpower_sophia_clg_va, tcxo_drv_lowpower_sophia_clg_va},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_sophia_clg_va[] = {
    &GPIO_7_5_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_sophia_clg_va, "block_rfant", NORMAL, rfant_pins_sophia_clg_va)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_sophia_clg_va[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_sophia_clg_va[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_sophia_clg_va[] = {
    [NORMAL] = {rfant_func_normal_sophia_clg_va, rfant_pullud_normal_sophia_clg_va, rfant_drv_normal_sophia_clg_va},
    [LOWPOWER] = {rfant_func_lowpower_sophia_clg_va, rfant_pullud_lowpower_sophia_clg_va, rfant_drv_lowpower_sophia_clg_va},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_sophia_clg_va[] = {
    &SDIO_DATA3_SOPHIA_CLG_VA, &SDIO_DATA2_SOPHIA_CLG_VA, &SDIO_DATA1_SOPHIA_CLG_VA, &SDIO_DATA0_SOPHIA_CLG_VA, &SDIO_CMD_SOPHIA_CLG_VA, &SDIO_CLK_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_sophia_clg_va, "block_wifi", NORMAL, wifi_pins_sophia_clg_va)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_sophia_clg_va[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_sophia_clg_va[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_sophia_clg_va[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_sophia_clg_va[] = {
    [NORMAL] = {wifi_func_normal_sophia_clg_va, wifi_pullud_normal_sophia_clg_va, wifi_drv_normal_sophia_clg_va},
    [LOWPOWER] = {wifi_func_lowpower_sophia_clg_va, wifi_pullud_lowpower_sophia_clg_va, wifi_drv_lowpower_sophia_clg_va},

};

/*boot pins */
static struct  iomux_pin *boot_pins_sophia_clg_va[] = {
    &BOOT_SEL_SOPHIA_CLG_VA, &GPIO_5_2_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_sophia_clg_va, "block_boot", NORMAL, boot_pins_sophia_clg_va)



/*BOOT*/

static enum lowlayer_func boot_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_sophia_clg_va[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_sophia_clg_va[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_sophia_clg_va[] = {
    [NORMAL] = {boot_func_normal_sophia_clg_va, boot_pullud_normal_sophia_clg_va, boot_drv_normal_sophia_clg_va},
    [LOWPOWER] = {boot_func_lowpower_sophia_clg_va, boot_pullud_lowpower_sophia_clg_va, boot_drv_lowpower_sophia_clg_va},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_sophia_clg_va[] = {
    &PWM_OUT1_SOPHIA_CLG_VA, &GPIO_4_6_SOPHIA_CLG_VA, &GPIO_4_7_SOPHIA_CLG_VA, &GPIO_6_6_SOPHIA_CLG_VA, &PWM_OUT0_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_sophia_clg_va, "block_lcd", NORMAL, lcd_pins_sophia_clg_va)



/*LCD*/

static enum lowlayer_func lcd_func_normal_sophia_clg_va[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_sophia_clg_va[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_sophia_clg_va[] = {
    [NORMAL] = {lcd_func_normal_sophia_clg_va, lcd_pullud_normal_sophia_clg_va, lcd_drv_normal_sophia_clg_va},
    [LOWPOWER] = {lcd_func_lowpower_sophia_clg_va, lcd_pullud_lowpower_sophia_clg_va, lcd_drv_lowpower_sophia_clg_va},

};

/*key pins */
static struct  iomux_pin *key_pins_sophia_clg_va[] = {
    &GPIO_4_2_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_sophia_clg_va, "block_key", NORMAL, key_pins_sophia_clg_va)



/*KEY*/

static enum lowlayer_func key_func_normal_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_sophia_clg_va[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_sophia_clg_va[] = {FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_sophia_clg_va[] = {PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_sophia_clg_va[] = {LEVEL0,  -INVALID,};

static struct block_config key_config_sophia_clg_va[] = {
    [NORMAL] = {key_func_normal_sophia_clg_va, key_pullud_normal_sophia_clg_va, key_drv_normal_sophia_clg_va},
    [LOWPOWER] = {key_func_lowpower_sophia_clg_va, key_pullud_lowpower_sophia_clg_va, key_drv_lowpower_sophia_clg_va},

};

/*test pins */
static struct  iomux_pin *test_pins_sophia_clg_va[] = {
    &UART0_RXD_SOPHIA_CLG_VA, &UART0_TXD_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_sophia_clg_va, "block_test", NORMAL, test_pins_sophia_clg_va)



/*TEST*/

static enum lowlayer_func test_func_normal_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_sophia_clg_va[] = {
    [NORMAL] = {test_func_normal_sophia_clg_va, test_pullud_normal_sophia_clg_va, test_drv_normal_sophia_clg_va},
    [LOWPOWER] = {test_func_lowpower_sophia_clg_va, test_pullud_lowpower_sophia_clg_va, test_drv_lowpower_sophia_clg_va},

};

/*audio_es305 pins */
static struct  iomux_pin *audio_es305_pins_sophia_clg_va[] = {
    &UART2_RXD_SOPHIA_CLG_VA, &UART2_TXD_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: audio_es305*/
IOMUX_BLOCK(block_audio_es305_sophia_clg_va, "block_audio_es305", NORMAL, audio_es305_pins_sophia_clg_va)



/*audio_es305*/

static enum lowlayer_func audio_es305_func_normal_sophia_clg_va[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown audio_es305_pullud_normal_sophia_clg_va[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func audio_es305_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown audio_es305_pullud_lowpower_sophia_clg_va[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config audio_es305_config_sophia_clg_va[] = {
    [NORMAL] = {audio_es305_func_normal_sophia_clg_va, audio_es305_pullud_normal_sophia_clg_va, audio_es305_drv_normal_sophia_clg_va},
    [LOWPOWER] = {audio_es305_func_lowpower_sophia_clg_va, audio_es305_pullud_lowpower_sophia_clg_va, audio_es305_drv_lowpower_sophia_clg_va},

};

/*sd pins */
static struct  iomux_pin *sd_pins_sophia_clg_va[] = {
    &SD_CLK_SOPHIA_CLG_VA, &SD_CMD_SOPHIA_CLG_VA, &SD_DATA0_SOPHIA_CLG_VA, &SD_DATA1_SOPHIA_CLG_VA, &SD_DATA2_SOPHIA_CLG_VA, &SD_DATA3_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_sophia_clg_va, "block_sd", NORMAL, sd_pins_sophia_clg_va)



/*SD*/

static enum lowlayer_func sd_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_sophia_clg_va[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP,  -INVALID,};
static enum drive_strength sd_drv_normal_sophia_clg_va[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_sophia_clg_va[] = {FUNC1, FUNC1, FUNC1, FUNC1, FUNC1, FUNC1,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_sophia_clg_va[] = {LEVEL1, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_sophia_clg_va[] = {
    [NORMAL] = {sd_func_normal_sophia_clg_va, sd_pullud_normal_sophia_clg_va, sd_drv_normal_sophia_clg_va},
    [LOWPOWER] = {sd_func_lowpower_sophia_clg_va, sd_pullud_lowpower_sophia_clg_va, sd_drv_lowpower_sophia_clg_va},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_sophia_clg_va[] = {
    &I2S_XCLK_SOPHIA_CLG_VA, &I2S_XFS_SOPHIA_CLG_VA, &I2S_DI_SOPHIA_CLG_VA, &I2S_DO_SOPHIA_CLG_VA, &PCM0_XCLK_SOPHIA_CLG_VA, &PCM0_XFS_SOPHIA_CLG_VA, &PCM0_DI_SOPHIA_CLG_VA, &PCM0_DO_SOPHIA_CLG_VA,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_sophia_clg_va, "block_es305", NORMAL, es305_pins_sophia_clg_va)



/*ES305*/

static enum lowlayer_func es305_func_normal_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown es305_pullud_normal_sophia_clg_va[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength es305_drv_normal_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_sophia_clg_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_sophia_clg_va[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength es305_drv_lowpower_sophia_clg_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_sophia_clg_va[] = {
    [NORMAL] = {es305_func_normal_sophia_clg_va, es305_pullud_normal_sophia_clg_va, es305_drv_normal_sophia_clg_va},
    [LOWPOWER] = {es305_func_lowpower_sophia_clg_va, es305_pullud_lowpower_sophia_clg_va, es305_drv_lowpower_sophia_clg_va},

};

struct iomux_block_table block_config_table_sophia_clg_va[] = {
    BLOCK_CONFIG("block_charger", &block_charger_sophia_clg_va, charger_config_sophia_clg_va)
    BLOCK_CONFIG("block_flash", &block_flash_sophia_clg_va, flash_config_sophia_clg_va)
    BLOCK_CONFIG("block_bt", &block_bt_sophia_clg_va, bt_config_sophia_clg_va)
    BLOCK_CONFIG("block_scamera", &block_scamera_sophia_clg_va, scamera_config_sophia_clg_va)
    BLOCK_CONFIG("block_codec", &block_codec_sophia_clg_va, codec_config_sophia_clg_va)
    BLOCK_CONFIG("block_modem_switch", &block_modem_switch_sophia_clg_va, modem_switch_config_sophia_clg_va)
    BLOCK_CONFIG("block_pmu", &block_pmu_sophia_clg_va, pmu_config_sophia_clg_va)
    BLOCK_CONFIG("block_spi0", &block_spi0_sophia_clg_va, spi0_config_sophia_clg_va)
    BLOCK_CONFIG("block_emmc", &block_emmc_sophia_clg_va, emmc_config_sophia_clg_va)
    BLOCK_CONFIG("block_odt", &block_odt_sophia_clg_va, odt_config_sophia_clg_va)
    BLOCK_CONFIG("block_rf", &block_rf_sophia_clg_va, rf_config_sophia_clg_va)
    BLOCK_CONFIG("block_tp", &block_tp_sophia_clg_va, tp_config_sophia_clg_va)
    BLOCK_CONFIG("block_switch", &block_switch_sophia_clg_va, switch_config_sophia_clg_va)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_sophia_clg_va, rfpmu_config_sophia_clg_va)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_sophia_clg_va, i2c3_config_sophia_clg_va)
    BLOCK_CONFIG("block_usim1", &block_usim1_sophia_clg_va, usim1_config_sophia_clg_va)
    BLOCK_CONFIG("block_usim0", &block_usim0_sophia_clg_va, usim0_config_sophia_clg_va)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_sophia_clg_va, mcamera_config_sophia_clg_va)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_sophia_clg_va, i2c0_config_sophia_clg_va)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_sophia_clg_va, i2c1_config_sophia_clg_va)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_sophia_clg_va, i2c2_config_sophia_clg_va)
    BLOCK_CONFIG("block_gps", &block_gps_sophia_clg_va, gps_config_sophia_clg_va)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_sophia_clg_va, tcxo_config_sophia_clg_va)
    BLOCK_CONFIG("block_rfant", &block_rfant_sophia_clg_va, rfant_config_sophia_clg_va)
    BLOCK_CONFIG("block_wifi", &block_wifi_sophia_clg_va, wifi_config_sophia_clg_va)
    BLOCK_CONFIG("block_boot", &block_boot_sophia_clg_va, boot_config_sophia_clg_va)
    BLOCK_CONFIG("block_lcd", &block_lcd_sophia_clg_va, lcd_config_sophia_clg_va)
    BLOCK_CONFIG("block_key", &block_key_sophia_clg_va, key_config_sophia_clg_va)
    BLOCK_CONFIG("block_test", &block_test_sophia_clg_va, test_config_sophia_clg_va)
    BLOCK_CONFIG("block_audio_es305", &block_audio_es305_sophia_clg_va, audio_es305_config_sophia_clg_va)
    BLOCK_CONFIG("block_sd", &block_sd_sophia_clg_va, sd_config_sophia_clg_va)
    BLOCK_CONFIG("block_es305", &block_es305_sophia_clg_va, es305_config_sophia_clg_va)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
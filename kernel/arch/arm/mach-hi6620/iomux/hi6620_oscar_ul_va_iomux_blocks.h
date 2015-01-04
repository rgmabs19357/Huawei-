/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_oscar_ul_va_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_OSCAR_UL_VA_IOMUX_BLOCKS_H__
#define __HI6620_OSCAR_UL_VA_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_oscar_ul_va_iomux_pins.h"
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


/*audio_eph pins */
static struct  iomux_pin *audio_eph_pins_oscar_ul_va[] = {
    &GPIO_5_1_OSCAR_UL_VA,  NULL,
};

/*define blocks: audio_eph*/
IOMUX_BLOCK(block_audio_eph_oscar_ul_va, "block_audio_eph", NORMAL, audio_eph_pins_oscar_ul_va)



/*audio_eph*/

static enum lowlayer_func audio_eph_func_normal_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_eph_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config audio_eph_config_oscar_ul_va[] = {
    [NORMAL] = {audio_eph_func_normal_oscar_ul_va, audio_eph_pullud_normal_oscar_ul_va, audio_eph_drv_normal_oscar_ul_va},
    [LOWPOWER] = {audio_eph_func_lowpower_oscar_ul_va, audio_eph_pullud_lowpower_oscar_ul_va, audio_eph_drv_lowpower_oscar_ul_va},

};

/*charger pins */
static struct  iomux_pin *charger_pins_oscar_ul_va[] = {
    &GPIO_4_0_OSCAR_UL_VA,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_oscar_ul_va, "block_charger", NORMAL, charger_pins_oscar_ul_va)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config charger_config_oscar_ul_va[] = {
    [NORMAL] = {charger_func_normal_oscar_ul_va, charger_pullud_normal_oscar_ul_va, charger_drv_normal_oscar_ul_va},
    [LOWPOWER] = {charger_func_lowpower_oscar_ul_va, charger_pullud_lowpower_oscar_ul_va, charger_drv_lowpower_oscar_ul_va},

};

/*flash pins */
static struct  iomux_pin *flash_pins_oscar_ul_va[] = {
    &ISP_GPIO5_OSCAR_UL_VA, &RF_GPIO_0_OSCAR_UL_VA,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_oscar_ul_va, "block_flash", NORMAL, flash_pins_oscar_ul_va)



/*FLASH*/

static enum lowlayer_func flash_func_normal_oscar_ul_va[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_oscar_ul_va[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_oscar_ul_va[] = {
    [NORMAL] = {flash_func_normal_oscar_ul_va, flash_pullud_normal_oscar_ul_va, flash_drv_normal_oscar_ul_va},
    [LOWPOWER] = {flash_func_lowpower_oscar_ul_va, flash_pullud_lowpower_oscar_ul_va, flash_drv_lowpower_oscar_ul_va},

};

/*bt pins */
static struct  iomux_pin *bt_pins_oscar_ul_va[] = {
    &UART4_CTS_N_OSCAR_UL_VA, &UART4_RTS_N_OSCAR_UL_VA, &UART4_RXD_OSCAR_UL_VA, &UART4_TXD_OSCAR_UL_VA, &GPIO_15_5_OSCAR_UL_VA, &GPIO_15_7_OSCAR_UL_VA,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_oscar_ul_va, "block_bt", NORMAL, bt_pins_oscar_ul_va)



/*BT*/

static enum lowlayer_func bt_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_oscar_ul_va[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_oscar_ul_va[] = {
    [NORMAL] = {bt_func_normal_oscar_ul_va, bt_pullud_normal_oscar_ul_va, bt_drv_normal_oscar_ul_va},
    [LOWPOWER] = {bt_func_lowpower_oscar_ul_va, bt_pullud_lowpower_oscar_ul_va, bt_drv_lowpower_oscar_ul_va},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_oscar_ul_va[] = {
    &ISP_GPIO1_OSCAR_UL_VA, &ISP_GPIO4_OSCAR_UL_VA, &ISP_RESETB1_OSCAR_UL_VA, &ISP_CCLK1_OSCAR_UL_VA, &ISP_SDA1_OSCAR_UL_VA, &ISP_SCL1_OSCAR_UL_VA,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_oscar_ul_va, "block_scamera", NORMAL, scamera_pins_oscar_ul_va)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_oscar_ul_va[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_oscar_ul_va[] = {
    [NORMAL] = {scamera_func_normal_oscar_ul_va, scamera_pullud_normal_oscar_ul_va, scamera_drv_normal_oscar_ul_va},
    [LOWPOWER] = {scamera_func_lowpower_oscar_ul_va, scamera_pullud_lowpower_oscar_ul_va, scamera_drv_lowpower_oscar_ul_va},

};

/*codec pins */
static struct  iomux_pin *codec_pins_oscar_ul_va[] = {
    &PCM1_XCLK_OSCAR_UL_VA, &PCM1_XFS_OSCAR_UL_VA, &PCM1_DI_OSCAR_UL_VA, &PCM1_DO_OSCAR_UL_VA,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_oscar_ul_va, "block_codec", NORMAL, codec_pins_oscar_ul_va)



/*CODEC*/

static enum lowlayer_func codec_func_normal_oscar_ul_va[] = {FUNC2, FUNC2, FUNC2, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_oscar_ul_va[] = {FUNC2, FUNC2, FUNC2, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_oscar_ul_va[] = {
    [NORMAL] = {codec_func_normal_oscar_ul_va, codec_pullud_normal_oscar_ul_va, codec_drv_normal_oscar_ul_va},
    [LOWPOWER] = {codec_func_lowpower_oscar_ul_va, codec_pullud_lowpower_oscar_ul_va, codec_drv_lowpower_oscar_ul_va},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_oscar_ul_va[] = {
    &HKADC_SSI_OSCAR_UL_VA, &AUX_SSI0_OSCAR_UL_VA, &AUX_SSI1_OSCAR_UL_VA, &GPIO_5_0_OSCAR_UL_VA,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_oscar_ul_va, "block_pmu", NORMAL, pmu_pins_oscar_ul_va)



/*PMU*/

static enum lowlayer_func pmu_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_oscar_ul_va[] = {
    [NORMAL] = {pmu_func_normal_oscar_ul_va, pmu_pullud_normal_oscar_ul_va, pmu_drv_normal_oscar_ul_va},
    [LOWPOWER] = {pmu_func_lowpower_oscar_ul_va, pmu_pullud_lowpower_oscar_ul_va, pmu_drv_lowpower_oscar_ul_va},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_oscar_ul_va[] = {
    &EMMC_CLK_OSCAR_UL_VA, &EMMC_CMD_OSCAR_UL_VA, &EMMC_DATA0_OSCAR_UL_VA, &EMMC_DATA1_OSCAR_UL_VA, &EMMC_DATA2_OSCAR_UL_VA, &EMMC_DATA3_OSCAR_UL_VA, &EMMC_DATA4_OSCAR_UL_VA, &EMMC_DATA5_OSCAR_UL_VA, &EMMC_DATA6_OSCAR_UL_VA, &EMMC_DATA7_OSCAR_UL_VA, &GPIO_2_3_OSCAR_UL_VA,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_oscar_ul_va, "block_emmc", NORMAL, emmc_pins_oscar_ul_va)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_oscar_ul_va[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_oscar_ul_va[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_oscar_ul_va[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_oscar_ul_va[] = {
    [NORMAL] = {emmc_func_normal_oscar_ul_va, emmc_pullud_normal_oscar_ul_va, emmc_drv_normal_oscar_ul_va},
    [LOWPOWER] = {emmc_func_lowpower_oscar_ul_va, emmc_pullud_lowpower_oscar_ul_va, emmc_drv_lowpower_oscar_ul_va},

};

/*odt pins */
static struct  iomux_pin *odt_pins_oscar_ul_va[] = {
    &RF_RESET1_OSCAR_UL_VA,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_oscar_ul_va, "block_odt", NORMAL, odt_pins_oscar_ul_va)



/*ODT*/

static enum lowlayer_func odt_func_normal_oscar_ul_va[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_oscar_ul_va[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_oscar_ul_va[] = {
    [NORMAL] = {odt_func_normal_oscar_ul_va, odt_pullud_normal_oscar_ul_va, odt_drv_normal_oscar_ul_va},
    [LOWPOWER] = {odt_func_lowpower_oscar_ul_va, odt_pullud_lowpower_oscar_ul_va, odt_drv_lowpower_oscar_ul_va},

};

/*tp pins */
static struct  iomux_pin *tp_pins_oscar_ul_va[] = {
    &GPIO_18_7_OSCAR_UL_VA,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_oscar_ul_va, "block_tp", NORMAL, tp_pins_oscar_ul_va)



/*TP*/

static enum lowlayer_func tp_func_normal_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_oscar_ul_va[] = {
    [NORMAL] = {tp_func_normal_oscar_ul_va, tp_pullud_normal_oscar_ul_va, tp_drv_normal_oscar_ul_va},
    [LOWPOWER] = {tp_func_lowpower_oscar_ul_va, tp_pullud_lowpower_oscar_ul_va, tp_drv_lowpower_oscar_ul_va},

};

/*rf pins */
static struct  iomux_pin *rf_pins_oscar_ul_va[] = {
    &RF_TX_EN1_OSCAR_UL_VA, &RF_TCVR_ON0_OSCAR_UL_VA, &RF_TCVR_ON1_OSCAR_UL_VA, &RF_SSI0_OSCAR_UL_VA, &RF_SSI1_OSCAR_UL_VA, &RF_GPIO_2_OSCAR_UL_VA, &RF_GPIO_3_OSCAR_UL_VA, &RF_GPIO_4_OSCAR_UL_VA, &RF_GPIO_5_OSCAR_UL_VA, &RF_GPIO_6_OSCAR_UL_VA, &RF_GPIO_7_OSCAR_UL_VA, &RF_GPIO_8_OSCAR_UL_VA, &RF_GPIO_9_OSCAR_UL_VA, &RF_GPIO_10_OSCAR_UL_VA, &RF_GPIO_11_OSCAR_UL_VA, &RF_GPIO_12_OSCAR_UL_VA, &RF_GPIO_13_OSCAR_UL_VA, &RF_GPIO_14_OSCAR_UL_VA, &RF_GPIO_15_OSCAR_UL_VA, &RF_GPIO_16_OSCAR_UL_VA, &RF_GPIO_17_OSCAR_UL_VA, &RF_GPIO_18_OSCAR_UL_VA, &RF_GPIO_19_OSCAR_UL_VA, &RF_GPIO_20_OSCAR_UL_VA, &RF_GPIO_21_OSCAR_UL_VA, &RF_GPIO_22_OSCAR_UL_VA, &RF_GPIO_23_OSCAR_UL_VA, &RF_GPIO_24_OSCAR_UL_VA, &RF_GPIO_25_OSCAR_UL_VA, &RF_GPIO_26_OSCAR_UL_VA, &RF_GPIO_27_OSCAR_UL_VA, &RF_GPIO_28_OSCAR_UL_VA, &RF_GPIO_30_OSCAR_UL_VA,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_oscar_ul_va, "block_rf", NORMAL, rf_pins_oscar_ul_va)



/*RF*/

static enum lowlayer_func rf_func_normal_oscar_ul_va[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_oscar_ul_va[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_oscar_ul_va[] = {
    [NORMAL] = {rf_func_normal_oscar_ul_va, rf_pullud_normal_oscar_ul_va, rf_drv_normal_oscar_ul_va},
    [LOWPOWER] = {rf_func_lowpower_oscar_ul_va, rf_pullud_lowpower_oscar_ul_va, rf_drv_lowpower_oscar_ul_va},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_oscar_ul_va[] = {
    &RF_MIPI_CLK0_OSCAR_UL_VA, &RF_MIPI_DATA0_OSCAR_UL_VA, &APT_PDM0_OSCAR_UL_VA,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_oscar_ul_va, "block_rfpmu", NORMAL, rfpmu_pins_oscar_ul_va)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_oscar_ul_va[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_oscar_ul_va[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_oscar_ul_va[] = {
    [NORMAL] = {rfpmu_func_normal_oscar_ul_va, rfpmu_pullud_normal_oscar_ul_va, rfpmu_drv_normal_oscar_ul_va},
    [LOWPOWER] = {rfpmu_func_lowpower_oscar_ul_va, rfpmu_pullud_lowpower_oscar_ul_va, rfpmu_drv_lowpower_oscar_ul_va},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_oscar_ul_va[] = {
    &I2C3_SCL_OSCAR_UL_VA, &I2C3_SDA_OSCAR_UL_VA,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_oscar_ul_va, "block_i2c3", NORMAL, i2c3_pins_oscar_ul_va)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_oscar_ul_va[] = {
    [NORMAL] = {i2c3_func_normal_oscar_ul_va, i2c3_pullud_normal_oscar_ul_va, i2c3_drv_normal_oscar_ul_va},
    [LOWPOWER] = {i2c3_func_lowpower_oscar_ul_va, i2c3_pullud_lowpower_oscar_ul_va, i2c3_drv_lowpower_oscar_ul_va},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_oscar_ul_va[] = {
    &GPIO_6_5_OSCAR_UL_VA,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_oscar_ul_va, "block_nfc", NORMAL, nfc_pins_oscar_ul_va)



/*NFC*/

static enum lowlayer_func nfc_func_normal_oscar_ul_va[] = {FUNC6,  -INVALID,};
static enum pull_updown nfc_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config nfc_config_oscar_ul_va[] = {
    [NORMAL] = {nfc_func_normal_oscar_ul_va, nfc_pullud_normal_oscar_ul_va, nfc_drv_normal_oscar_ul_va},
    [LOWPOWER] = {nfc_func_lowpower_oscar_ul_va, nfc_pullud_lowpower_oscar_ul_va, nfc_drv_lowpower_oscar_ul_va},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_oscar_ul_va[] = {
    &USIM1_CLK_OSCAR_UL_VA, &USIM1_DATA_OSCAR_UL_VA, &USIM1_RST_OSCAR_UL_VA,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_oscar_ul_va, "block_usim1", NORMAL, usim1_pins_oscar_ul_va)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_oscar_ul_va[] = {FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown usim1_pullud_normal_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength usim1_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_oscar_ul_va[] = {FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_oscar_ul_va[] = {PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_oscar_ul_va[] = {
    [NORMAL] = {usim1_func_normal_oscar_ul_va, usim1_pullud_normal_oscar_ul_va, usim1_drv_normal_oscar_ul_va},
    [LOWPOWER] = {usim1_func_lowpower_oscar_ul_va, usim1_pullud_lowpower_oscar_ul_va, usim1_drv_lowpower_oscar_ul_va},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_oscar_ul_va[] = {
    &USIM0_CLK_OSCAR_UL_VA, &USIM0_DATA_OSCAR_UL_VA, &USIM0_RST_OSCAR_UL_VA,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_oscar_ul_va, "block_usim0", NORMAL, usim0_pins_oscar_ul_va)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_oscar_ul_va[] = {
    [NORMAL] = {usim0_func_normal_oscar_ul_va, usim0_pullud_normal_oscar_ul_va, usim0_drv_normal_oscar_ul_va},
    [LOWPOWER] = {usim0_func_lowpower_oscar_ul_va, usim0_pullud_lowpower_oscar_ul_va, usim0_drv_lowpower_oscar_ul_va},

};

/*audio_spk pins */
static struct  iomux_pin *audio_spk_pins_oscar_ul_va[] = {
    &GPIO_7_4_OSCAR_UL_VA,  NULL,
};

/*define blocks: audio_spk*/
IOMUX_BLOCK(block_audio_spk_oscar_ul_va, "block_audio_spk", NORMAL, audio_spk_pins_oscar_ul_va)



/*audio_spk*/

static enum lowlayer_func audio_spk_func_normal_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_normal_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_spk_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_lowpower_oscar_ul_va[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config audio_spk_config_oscar_ul_va[] = {
    [NORMAL] = {audio_spk_func_normal_oscar_ul_va, audio_spk_pullud_normal_oscar_ul_va, audio_spk_drv_normal_oscar_ul_va},
    [LOWPOWER] = {audio_spk_func_lowpower_oscar_ul_va, audio_spk_pullud_lowpower_oscar_ul_va, audio_spk_drv_lowpower_oscar_ul_va},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_oscar_ul_va[] = {
    &ISP_GPIO0_OSCAR_UL_VA, &ISP_GPIO2_OSCAR_UL_VA, &ISP_GPIO3_OSCAR_UL_VA, &ISP_RESETB0_OSCAR_UL_VA, &ISP_CCLK0_OSCAR_UL_VA, &ISP_SDA0_OSCAR_UL_VA, &ISP_SCL0_OSCAR_UL_VA,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_oscar_ul_va, "block_mcamera", NORMAL, mcamera_pins_oscar_ul_va)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_oscar_ul_va[] = {
    [NORMAL] = {mcamera_func_normal_oscar_ul_va, mcamera_pullud_normal_oscar_ul_va, mcamera_drv_normal_oscar_ul_va},
    [LOWPOWER] = {mcamera_func_lowpower_oscar_ul_va, mcamera_pullud_lowpower_oscar_ul_va, mcamera_drv_lowpower_oscar_ul_va},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_oscar_ul_va[] = {
    &I2C0_SCL_OSCAR_UL_VA, &I2C0_SDA_OSCAR_UL_VA,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_oscar_ul_va, "block_i2c0", NORMAL, i2c0_pins_oscar_ul_va)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_oscar_ul_va[] = {
    [NORMAL] = {i2c0_func_normal_oscar_ul_va, i2c0_pullud_normal_oscar_ul_va, i2c0_drv_normal_oscar_ul_va},
    [LOWPOWER] = {i2c0_func_lowpower_oscar_ul_va, i2c0_pullud_lowpower_oscar_ul_va, i2c0_drv_lowpower_oscar_ul_va},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_oscar_ul_va[] = {
    &I2C1_SCL_OSCAR_UL_VA, &I2C1_SDA_OSCAR_UL_VA,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_oscar_ul_va, "block_i2c1", NORMAL, i2c1_pins_oscar_ul_va)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_oscar_ul_va[] = {
    [NORMAL] = {i2c1_func_normal_oscar_ul_va, i2c1_pullud_normal_oscar_ul_va, i2c1_drv_normal_oscar_ul_va},
    [LOWPOWER] = {i2c1_func_lowpower_oscar_ul_va, i2c1_pullud_lowpower_oscar_ul_va, i2c1_drv_lowpower_oscar_ul_va},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_oscar_ul_va[] = {
    &I2C2_SCL_OSCAR_UL_VA, &I2C2_SDA_OSCAR_UL_VA,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_oscar_ul_va, "block_i2c2", NORMAL, i2c2_pins_oscar_ul_va)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_oscar_ul_va[] = {
    [NORMAL] = {i2c2_func_normal_oscar_ul_va, i2c2_pullud_normal_oscar_ul_va, i2c2_drv_normal_oscar_ul_va},
    [LOWPOWER] = {i2c2_func_lowpower_oscar_ul_va, i2c2_pullud_lowpower_oscar_ul_va, i2c2_drv_lowpower_oscar_ul_va},

};

/*gps pins */
static struct  iomux_pin *gps_pins_oscar_ul_va[] = {
    &GPIO_6_1_OSCAR_UL_VA, &RF_GPIO_1_OSCAR_UL_VA, &UART3_CTS_N_OSCAR_UL_VA, &UART3_RTS_N_OSCAR_UL_VA, &UART3_RXD_OSCAR_UL_VA, &UART3_TXD_OSCAR_UL_VA, &GPS_CLK_OSCAR_UL_VA,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_oscar_ul_va, "block_gps", NORMAL, gps_pins_oscar_ul_va)



/*GPS*/

static enum lowlayer_func gps_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_oscar_ul_va[] = {
    [NORMAL] = {gps_func_normal_oscar_ul_va, gps_pullud_normal_oscar_ul_va, gps_drv_normal_oscar_ul_va},
    [LOWPOWER] = {gps_func_lowpower_oscar_ul_va, gps_pullud_lowpower_oscar_ul_va, gps_drv_lowpower_oscar_ul_va},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_oscar_ul_va[] = {
    &TCXO0_AFC_OSCAR_UL_VA, &TCXO1_AFC_OSCAR_UL_VA,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_oscar_ul_va, "block_tcxo", NORMAL, tcxo_pins_oscar_ul_va)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_oscar_ul_va[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_oscar_ul_va[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_oscar_ul_va[] = {
    [NORMAL] = {tcxo_func_normal_oscar_ul_va, tcxo_pullud_normal_oscar_ul_va, tcxo_drv_normal_oscar_ul_va},
    [LOWPOWER] = {tcxo_func_lowpower_oscar_ul_va, tcxo_pullud_lowpower_oscar_ul_va, tcxo_drv_lowpower_oscar_ul_va},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_oscar_ul_va[] = {
    &GPIO_7_5_OSCAR_UL_VA,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_oscar_ul_va, "block_rfant", NORMAL, rfant_pins_oscar_ul_va)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_oscar_ul_va[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_oscar_ul_va[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_oscar_ul_va[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_oscar_ul_va[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_oscar_ul_va[] = {
    [NORMAL] = {rfant_func_normal_oscar_ul_va, rfant_pullud_normal_oscar_ul_va, rfant_drv_normal_oscar_ul_va},
    [LOWPOWER] = {rfant_func_lowpower_oscar_ul_va, rfant_pullud_lowpower_oscar_ul_va, rfant_drv_lowpower_oscar_ul_va},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_oscar_ul_va[] = {
    &GPIO_2_2_OSCAR_UL_VA, &SDIO_DATA3_OSCAR_UL_VA, &SDIO_DATA2_OSCAR_UL_VA, &SDIO_DATA1_OSCAR_UL_VA, &SDIO_DATA0_OSCAR_UL_VA, &SDIO_CMD_OSCAR_UL_VA, &SDIO_CLK_OSCAR_UL_VA,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_oscar_ul_va, "block_wifi", NORMAL, wifi_pins_oscar_ul_va)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_oscar_ul_va[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_oscar_ul_va[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_oscar_ul_va[] = {
    [NORMAL] = {wifi_func_normal_oscar_ul_va, wifi_pullud_normal_oscar_ul_va, wifi_drv_normal_oscar_ul_va},
    [LOWPOWER] = {wifi_func_lowpower_oscar_ul_va, wifi_pullud_lowpower_oscar_ul_va, wifi_drv_lowpower_oscar_ul_va},

};

/*boot pins */
static struct  iomux_pin *boot_pins_oscar_ul_va[] = {
    &BOOT_SEL_OSCAR_UL_VA, &GPIO_5_2_OSCAR_UL_VA,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_oscar_ul_va, "block_boot", NORMAL, boot_pins_oscar_ul_va)



/*BOOT*/

static enum lowlayer_func boot_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_oscar_ul_va[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_oscar_ul_va[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_oscar_ul_va[] = {
    [NORMAL] = {boot_func_normal_oscar_ul_va, boot_pullud_normal_oscar_ul_va, boot_drv_normal_oscar_ul_va},
    [LOWPOWER] = {boot_func_lowpower_oscar_ul_va, boot_pullud_lowpower_oscar_ul_va, boot_drv_lowpower_oscar_ul_va},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_oscar_ul_va[] = {
    &PWM_OUT1_OSCAR_UL_VA, &GPIO_4_6_OSCAR_UL_VA, &GPIO_4_7_OSCAR_UL_VA, &GPIO_6_6_OSCAR_UL_VA, &PWM_OUT0_OSCAR_UL_VA,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_oscar_ul_va, "block_lcd", NORMAL, lcd_pins_oscar_ul_va)



/*LCD*/

static enum lowlayer_func lcd_func_normal_oscar_ul_va[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_oscar_ul_va[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_oscar_ul_va[] = {
    [NORMAL] = {lcd_func_normal_oscar_ul_va, lcd_pullud_normal_oscar_ul_va, lcd_drv_normal_oscar_ul_va},
    [LOWPOWER] = {lcd_func_lowpower_oscar_ul_va, lcd_pullud_lowpower_oscar_ul_va, lcd_drv_lowpower_oscar_ul_va},

};

/*key pins */
static struct  iomux_pin *key_pins_oscar_ul_va[] = {
    &GPIO_4_2_OSCAR_UL_VA, &GPIO_4_3_OSCAR_UL_VA,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_oscar_ul_va, "block_key", NORMAL, key_pins_oscar_ul_va)



/*KEY*/

static enum lowlayer_func key_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_oscar_ul_va[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_oscar_ul_va[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_oscar_ul_va[] = {
    [NORMAL] = {key_func_normal_oscar_ul_va, key_pullud_normal_oscar_ul_va, key_drv_normal_oscar_ul_va},
    [LOWPOWER] = {key_func_lowpower_oscar_ul_va, key_pullud_lowpower_oscar_ul_va, key_drv_lowpower_oscar_ul_va},

};

/*test pins */
static struct  iomux_pin *test_pins_oscar_ul_va[] = {
    &UART0_RXD_OSCAR_UL_VA, &UART0_TXD_OSCAR_UL_VA,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_oscar_ul_va, "block_test", NORMAL, test_pins_oscar_ul_va)



/*TEST*/

static enum lowlayer_func test_func_normal_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_oscar_ul_va[] = {
    [NORMAL] = {test_func_normal_oscar_ul_va, test_pullud_normal_oscar_ul_va, test_drv_normal_oscar_ul_va},
    [LOWPOWER] = {test_func_lowpower_oscar_ul_va, test_pullud_lowpower_oscar_ul_va, test_drv_lowpower_oscar_ul_va},

};

/*audio_es305 pins */
static struct  iomux_pin *audio_es305_pins_oscar_ul_va[] = {
    &UART2_RXD_OSCAR_UL_VA, &UART2_TXD_OSCAR_UL_VA,  NULL,
};

/*define blocks: audio_es305*/
IOMUX_BLOCK(block_audio_es305_oscar_ul_va, "block_audio_es305", NORMAL, audio_es305_pins_oscar_ul_va)



/*audio_es305*/

static enum lowlayer_func audio_es305_func_normal_oscar_ul_va[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown audio_es305_pullud_normal_oscar_ul_va[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func audio_es305_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown audio_es305_pullud_lowpower_oscar_ul_va[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config audio_es305_config_oscar_ul_va[] = {
    [NORMAL] = {audio_es305_func_normal_oscar_ul_va, audio_es305_pullud_normal_oscar_ul_va, audio_es305_drv_normal_oscar_ul_va},
    [LOWPOWER] = {audio_es305_func_lowpower_oscar_ul_va, audio_es305_pullud_lowpower_oscar_ul_va, audio_es305_drv_lowpower_oscar_ul_va},

};

/*sd pins */
static struct  iomux_pin *sd_pins_oscar_ul_va[] = {
    &SD_CLK_OSCAR_UL_VA, &SD_CMD_OSCAR_UL_VA, &SD_DATA0_OSCAR_UL_VA, &SD_DATA1_OSCAR_UL_VA, &SD_DATA2_OSCAR_UL_VA, &SD_DATA3_OSCAR_UL_VA,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_oscar_ul_va, "block_sd", NORMAL, sd_pins_oscar_ul_va)



/*SD*/

static enum lowlayer_func sd_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_oscar_ul_va[] = {
    [NORMAL] = {sd_func_normal_oscar_ul_va, sd_pullud_normal_oscar_ul_va, sd_drv_normal_oscar_ul_va},
    [LOWPOWER] = {sd_func_lowpower_oscar_ul_va, sd_pullud_lowpower_oscar_ul_va, sd_drv_lowpower_oscar_ul_va},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_oscar_ul_va[] = {
    &I2S_XCLK_OSCAR_UL_VA, &I2S_XFS_OSCAR_UL_VA, &I2S_DI_OSCAR_UL_VA, &I2S_DO_OSCAR_UL_VA, &PCM0_XCLK_OSCAR_UL_VA, &PCM0_XFS_OSCAR_UL_VA, &PCM0_DI_OSCAR_UL_VA, &PCM0_DO_OSCAR_UL_VA, &UART1_TXD_OSCAR_UL_VA, &TS_ERR_OSCAR_UL_VA,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_oscar_ul_va, "block_es305", NORMAL, es305_pins_oscar_ul_va)



/*ES305*/

static enum lowlayer_func es305_func_normal_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_oscar_ul_va[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_oscar_ul_va[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_oscar_ul_va[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_oscar_ul_va[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_oscar_ul_va[] = {
    [NORMAL] = {es305_func_normal_oscar_ul_va, es305_pullud_normal_oscar_ul_va, es305_drv_normal_oscar_ul_va},
    [LOWPOWER] = {es305_func_lowpower_oscar_ul_va, es305_pullud_lowpower_oscar_ul_va, es305_drv_lowpower_oscar_ul_va},

};

struct iomux_block_table block_config_table_oscar_ul_va[] = {
    BLOCK_CONFIG("block_audio_eph", &block_audio_eph_oscar_ul_va, audio_eph_config_oscar_ul_va)
    BLOCK_CONFIG("block_charger", &block_charger_oscar_ul_va, charger_config_oscar_ul_va)
    BLOCK_CONFIG("block_flash", &block_flash_oscar_ul_va, flash_config_oscar_ul_va)
    BLOCK_CONFIG("block_bt", &block_bt_oscar_ul_va, bt_config_oscar_ul_va)
    BLOCK_CONFIG("block_scamera", &block_scamera_oscar_ul_va, scamera_config_oscar_ul_va)
    BLOCK_CONFIG("block_codec", &block_codec_oscar_ul_va, codec_config_oscar_ul_va)
    BLOCK_CONFIG("block_pmu", &block_pmu_oscar_ul_va, pmu_config_oscar_ul_va)
    BLOCK_CONFIG("block_emmc", &block_emmc_oscar_ul_va, emmc_config_oscar_ul_va)
    BLOCK_CONFIG("block_odt", &block_odt_oscar_ul_va, odt_config_oscar_ul_va)
    BLOCK_CONFIG("block_tp", &block_tp_oscar_ul_va, tp_config_oscar_ul_va)
    BLOCK_CONFIG("block_rf", &block_rf_oscar_ul_va, rf_config_oscar_ul_va)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_oscar_ul_va, rfpmu_config_oscar_ul_va)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_oscar_ul_va, i2c3_config_oscar_ul_va)
    BLOCK_CONFIG("block_nfc", &block_nfc_oscar_ul_va, nfc_config_oscar_ul_va)
    BLOCK_CONFIG("block_usim1", &block_usim1_oscar_ul_va, usim1_config_oscar_ul_va)
    BLOCK_CONFIG("block_usim0", &block_usim0_oscar_ul_va, usim0_config_oscar_ul_va)
    BLOCK_CONFIG("block_audio_spk", &block_audio_spk_oscar_ul_va, audio_spk_config_oscar_ul_va)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_oscar_ul_va, mcamera_config_oscar_ul_va)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_oscar_ul_va, i2c0_config_oscar_ul_va)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_oscar_ul_va, i2c1_config_oscar_ul_va)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_oscar_ul_va, i2c2_config_oscar_ul_va)
    BLOCK_CONFIG("block_gps", &block_gps_oscar_ul_va, gps_config_oscar_ul_va)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_oscar_ul_va, tcxo_config_oscar_ul_va)
    BLOCK_CONFIG("block_rfant", &block_rfant_oscar_ul_va, rfant_config_oscar_ul_va)
    BLOCK_CONFIG("block_wifi", &block_wifi_oscar_ul_va, wifi_config_oscar_ul_va)
    BLOCK_CONFIG("block_boot", &block_boot_oscar_ul_va, boot_config_oscar_ul_va)
    BLOCK_CONFIG("block_lcd", &block_lcd_oscar_ul_va, lcd_config_oscar_ul_va)
    BLOCK_CONFIG("block_key", &block_key_oscar_ul_va, key_config_oscar_ul_va)
    BLOCK_CONFIG("block_test", &block_test_oscar_ul_va, test_config_oscar_ul_va)
    BLOCK_CONFIG("block_audio_es305", &block_audio_es305_oscar_ul_va, audio_es305_config_oscar_ul_va)
    BLOCK_CONFIG("block_sd", &block_sd_oscar_ul_va, sd_config_oscar_ul_va)
    BLOCK_CONFIG("block_es305", &block_es305_oscar_ul_va, es305_config_oscar_ul_va)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
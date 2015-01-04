/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_oscar_cg_vc_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_OSCAR_CG_VC_IOMUX_BLOCKS_H__
#define __HI6620_OSCAR_CG_VC_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_oscar_cg_vc_iomux_pins.h"
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
static struct  iomux_pin *audio_eph_pins_oscar_cg_vc[] = {
    &GPIO_5_1_OSCAR_CG_VC,  NULL,
};

/*define blocks: audio_eph*/
IOMUX_BLOCK(block_audio_eph_oscar_cg_vc, "block_audio_eph", NORMAL, audio_eph_pins_oscar_cg_vc)



/*audio_eph*/

static enum lowlayer_func audio_eph_func_normal_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_eph_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config audio_eph_config_oscar_cg_vc[] = {
    [NORMAL] = {audio_eph_func_normal_oscar_cg_vc, audio_eph_pullud_normal_oscar_cg_vc, audio_eph_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {audio_eph_func_lowpower_oscar_cg_vc, audio_eph_pullud_lowpower_oscar_cg_vc, audio_eph_drv_lowpower_oscar_cg_vc},

};

/*charger pins */
static struct  iomux_pin *charger_pins_oscar_cg_vc[] = {
    &GPIO_4_0_OSCAR_CG_VC,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_oscar_cg_vc, "block_charger", NORMAL, charger_pins_oscar_cg_vc)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config charger_config_oscar_cg_vc[] = {
    [NORMAL] = {charger_func_normal_oscar_cg_vc, charger_pullud_normal_oscar_cg_vc, charger_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {charger_func_lowpower_oscar_cg_vc, charger_pullud_lowpower_oscar_cg_vc, charger_drv_lowpower_oscar_cg_vc},

};

/*flash pins */
static struct  iomux_pin *flash_pins_oscar_cg_vc[] = {
    &ISP_GPIO5_OSCAR_CG_VC, &RF_GPIO_20_OSCAR_CG_VC,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_oscar_cg_vc, "block_flash", NORMAL, flash_pins_oscar_cg_vc)



/*FLASH*/

static enum lowlayer_func flash_func_normal_oscar_cg_vc[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_oscar_cg_vc[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_oscar_cg_vc[] = {
    [NORMAL] = {flash_func_normal_oscar_cg_vc, flash_pullud_normal_oscar_cg_vc, flash_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {flash_func_lowpower_oscar_cg_vc, flash_pullud_lowpower_oscar_cg_vc, flash_drv_lowpower_oscar_cg_vc},

};

/*bt pins */
static struct  iomux_pin *bt_pins_oscar_cg_vc[] = {
    &UART4_CTS_N_OSCAR_CG_VC, &UART4_RTS_N_OSCAR_CG_VC, &UART4_RXD_OSCAR_CG_VC, &UART4_TXD_OSCAR_CG_VC, &GPIO_15_7_OSCAR_CG_VC,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_oscar_cg_vc, "block_bt", NORMAL, bt_pins_oscar_cg_vc)



/*BT*/

static enum lowlayer_func bt_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_oscar_cg_vc[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_oscar_cg_vc[] = {
    [NORMAL] = {bt_func_normal_oscar_cg_vc, bt_pullud_normal_oscar_cg_vc, bt_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {bt_func_lowpower_oscar_cg_vc, bt_pullud_lowpower_oscar_cg_vc, bt_drv_lowpower_oscar_cg_vc},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_oscar_cg_vc[] = {
    &ISP_GPIO1_OSCAR_CG_VC, &ISP_GPIO4_OSCAR_CG_VC, &ISP_RESETB1_OSCAR_CG_VC, &ISP_CCLK1_OSCAR_CG_VC, &ISP_SDA1_OSCAR_CG_VC, &ISP_SCL1_OSCAR_CG_VC,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_oscar_cg_vc, "block_scamera", NORMAL, scamera_pins_oscar_cg_vc)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_oscar_cg_vc[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_oscar_cg_vc[] = {
    [NORMAL] = {scamera_func_normal_oscar_cg_vc, scamera_pullud_normal_oscar_cg_vc, scamera_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {scamera_func_lowpower_oscar_cg_vc, scamera_pullud_lowpower_oscar_cg_vc, scamera_drv_lowpower_oscar_cg_vc},

};

/*codec pins */
static struct  iomux_pin *codec_pins_oscar_cg_vc[] = {
    &PCM1_XCLK_OSCAR_CG_VC, &PCM1_XFS_OSCAR_CG_VC, &PCM1_DI_OSCAR_CG_VC, &PCM1_DO_OSCAR_CG_VC,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_oscar_cg_vc, "block_codec", NORMAL, codec_pins_oscar_cg_vc)



/*CODEC*/

static enum lowlayer_func codec_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_oscar_cg_vc[] = {
    [NORMAL] = {codec_func_normal_oscar_cg_vc, codec_pullud_normal_oscar_cg_vc, codec_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {codec_func_lowpower_oscar_cg_vc, codec_pullud_lowpower_oscar_cg_vc, codec_drv_lowpower_oscar_cg_vc},

};

/*modem_switch pins */
static struct  iomux_pin *modem_switch_pins_oscar_cg_vc[] = {
    &TS_VALID_OSCAR_CG_VC,  NULL,
};

/*define blocks: modem_switch*/
IOMUX_BLOCK(block_modem_switch_oscar_cg_vc, "block_modem_switch", NORMAL, modem_switch_pins_oscar_cg_vc)



/*modem_switch*/

static enum lowlayer_func modem_switch_func_normal_oscar_cg_vc[] = {FUNC1,  -INVALID,};
static enum pull_updown modem_switch_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength modem_switch_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func modem_switch_func_lowpower_oscar_cg_vc[] = {FUNC1,  -INVALID,};
static enum pull_updown modem_switch_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength modem_switch_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config modem_switch_config_oscar_cg_vc[] = {
    [NORMAL] = {modem_switch_func_normal_oscar_cg_vc, modem_switch_pullud_normal_oscar_cg_vc, modem_switch_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {modem_switch_func_lowpower_oscar_cg_vc, modem_switch_pullud_lowpower_oscar_cg_vc, modem_switch_drv_lowpower_oscar_cg_vc},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_oscar_cg_vc[] = {
    &HKADC_SSI_OSCAR_CG_VC, &AUX_SSI0_OSCAR_CG_VC, &AUX_SSI1_OSCAR_CG_VC, &GPIO_5_0_OSCAR_CG_VC,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_oscar_cg_vc, "block_pmu", NORMAL, pmu_pins_oscar_cg_vc)



/*PMU*/

static enum lowlayer_func pmu_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_oscar_cg_vc[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_oscar_cg_vc[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_oscar_cg_vc[] = {
    [NORMAL] = {pmu_func_normal_oscar_cg_vc, pmu_pullud_normal_oscar_cg_vc, pmu_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {pmu_func_lowpower_oscar_cg_vc, pmu_pullud_lowpower_oscar_cg_vc, pmu_drv_lowpower_oscar_cg_vc},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_oscar_cg_vc[] = {
    &EMMC_CLK_OSCAR_CG_VC, &EMMC_CMD_OSCAR_CG_VC, &EMMC_DATA0_OSCAR_CG_VC, &EMMC_DATA1_OSCAR_CG_VC, &EMMC_DATA2_OSCAR_CG_VC, &EMMC_DATA3_OSCAR_CG_VC, &EMMC_DATA4_OSCAR_CG_VC, &EMMC_DATA5_OSCAR_CG_VC, &EMMC_DATA6_OSCAR_CG_VC, &EMMC_DATA7_OSCAR_CG_VC, &GPIO_2_3_OSCAR_CG_VC,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_oscar_cg_vc, "block_emmc", NORMAL, emmc_pins_oscar_cg_vc)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_oscar_cg_vc[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_oscar_cg_vc[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_oscar_cg_vc[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_oscar_cg_vc[] = {
    [NORMAL] = {emmc_func_normal_oscar_cg_vc, emmc_pullud_normal_oscar_cg_vc, emmc_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {emmc_func_lowpower_oscar_cg_vc, emmc_pullud_lowpower_oscar_cg_vc, emmc_drv_lowpower_oscar_cg_vc},

};

/*odt pins */
static struct  iomux_pin *odt_pins_oscar_cg_vc[] = {
    &RF_RESET1_OSCAR_CG_VC,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_oscar_cg_vc, "block_odt", NORMAL, odt_pins_oscar_cg_vc)



/*ODT*/

static enum lowlayer_func odt_func_normal_oscar_cg_vc[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_oscar_cg_vc[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_oscar_cg_vc[] = {
    [NORMAL] = {odt_func_normal_oscar_cg_vc, odt_pullud_normal_oscar_cg_vc, odt_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {odt_func_lowpower_oscar_cg_vc, odt_pullud_lowpower_oscar_cg_vc, odt_drv_lowpower_oscar_cg_vc},

};

/*rf pins */
static struct  iomux_pin *rf_pins_oscar_cg_vc[] = {
    &RF_TX_EN1_OSCAR_CG_VC, &RF_TCVR_ON0_OSCAR_CG_VC, &RF_TCVR_ON1_OSCAR_CG_VC, &RF_SSI0_OSCAR_CG_VC, &RF_SSI1_OSCAR_CG_VC, &RF_GPIO_2_OSCAR_CG_VC, &RF_GPIO_3_OSCAR_CG_VC, &RF_GPIO_4_OSCAR_CG_VC, &RF_GPIO_5_OSCAR_CG_VC, &RF_GPIO_6_OSCAR_CG_VC, &RF_GPIO_7_OSCAR_CG_VC, &RF_GPIO_13_OSCAR_CG_VC, &RF_GPIO_14_OSCAR_CG_VC, &RF_GPIO_15_OSCAR_CG_VC, &RF_GPIO_16_OSCAR_CG_VC, &RF_GPIO_17_OSCAR_CG_VC, &RF_GPIO_18_OSCAR_CG_VC, &RF_GPIO_23_OSCAR_CG_VC, &RF_GPIO_24_OSCAR_CG_VC, &RF_GPIO_26_OSCAR_CG_VC, &RF_GPIO_27_OSCAR_CG_VC, &RF_GPIO_28_OSCAR_CG_VC,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_oscar_cg_vc, "block_rf", NORMAL, rf_pins_oscar_cg_vc)



/*RF*/

static enum lowlayer_func rf_func_normal_oscar_cg_vc[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_oscar_cg_vc[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_oscar_cg_vc[] = {
    [NORMAL] = {rf_func_normal_oscar_cg_vc, rf_pullud_normal_oscar_cg_vc, rf_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {rf_func_lowpower_oscar_cg_vc, rf_pullud_lowpower_oscar_cg_vc, rf_drv_lowpower_oscar_cg_vc},

};

/*tp pins */
static struct  iomux_pin *tp_pins_oscar_cg_vc[] = {
    &GPIO_18_7_OSCAR_CG_VC,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_oscar_cg_vc, "block_tp", NORMAL, tp_pins_oscar_cg_vc)



/*TP*/

static enum lowlayer_func tp_func_normal_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_oscar_cg_vc[] = {
    [NORMAL] = {tp_func_normal_oscar_cg_vc, tp_pullud_normal_oscar_cg_vc, tp_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {tp_func_lowpower_oscar_cg_vc, tp_pullud_lowpower_oscar_cg_vc, tp_drv_lowpower_oscar_cg_vc},

};

/*switch pins */
static struct  iomux_pin *switch_pins_oscar_cg_vc[] = {
    &GPIO_5_3_OSCAR_CG_VC, &GPIO_6_2_OSCAR_CG_VC,  NULL,
};

/*define blocks: switch*/
IOMUX_BLOCK(block_switch_oscar_cg_vc, "block_switch", NORMAL, switch_pins_oscar_cg_vc)



/*SWITCH*/

static enum lowlayer_func switch_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func switch_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown switch_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength switch_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config switch_config_oscar_cg_vc[] = {
    [NORMAL] = {switch_func_normal_oscar_cg_vc, switch_pullud_normal_oscar_cg_vc, switch_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {switch_func_lowpower_oscar_cg_vc, switch_pullud_lowpower_oscar_cg_vc, switch_drv_lowpower_oscar_cg_vc},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_oscar_cg_vc[] = {
    &RF_MIPI_CLK0_OSCAR_CG_VC, &RF_MIPI_DATA0_OSCAR_CG_VC, &APT_PDM0_OSCAR_CG_VC,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_oscar_cg_vc, "block_rfpmu", NORMAL, rfpmu_pins_oscar_cg_vc)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_oscar_cg_vc[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_oscar_cg_vc[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_oscar_cg_vc[] = {
    [NORMAL] = {rfpmu_func_normal_oscar_cg_vc, rfpmu_pullud_normal_oscar_cg_vc, rfpmu_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {rfpmu_func_lowpower_oscar_cg_vc, rfpmu_pullud_lowpower_oscar_cg_vc, rfpmu_drv_lowpower_oscar_cg_vc},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_oscar_cg_vc[] = {
    &I2C3_SCL_OSCAR_CG_VC, &I2C3_SDA_OSCAR_CG_VC,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_oscar_cg_vc, "block_i2c3", NORMAL, i2c3_pins_oscar_cg_vc)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_oscar_cg_vc[] = {
    [NORMAL] = {i2c3_func_normal_oscar_cg_vc, i2c3_pullud_normal_oscar_cg_vc, i2c3_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {i2c3_func_lowpower_oscar_cg_vc, i2c3_pullud_lowpower_oscar_cg_vc, i2c3_drv_lowpower_oscar_cg_vc},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_oscar_cg_vc[] = {
    &GPIO_6_5_OSCAR_CG_VC,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_oscar_cg_vc, "block_nfc", NORMAL, nfc_pins_oscar_cg_vc)



/*NFC*/

static enum lowlayer_func nfc_func_normal_oscar_cg_vc[] = {FUNC6,  -INVALID,};
static enum pull_updown nfc_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config nfc_config_oscar_cg_vc[] = {
    [NORMAL] = {nfc_func_normal_oscar_cg_vc, nfc_pullud_normal_oscar_cg_vc, nfc_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {nfc_func_lowpower_oscar_cg_vc, nfc_pullud_lowpower_oscar_cg_vc, nfc_drv_lowpower_oscar_cg_vc},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_oscar_cg_vc[] = {
    &USIM1_CLK_OSCAR_CG_VC, &USIM1_DATA_OSCAR_CG_VC, &USIM1_RST_OSCAR_CG_VC,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_oscar_cg_vc, "block_usim1", NORMAL, usim1_pins_oscar_cg_vc)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_oscar_cg_vc[] = {
    [NORMAL] = {usim1_func_normal_oscar_cg_vc, usim1_pullud_normal_oscar_cg_vc, usim1_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {usim1_func_lowpower_oscar_cg_vc, usim1_pullud_lowpower_oscar_cg_vc, usim1_drv_lowpower_oscar_cg_vc},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_oscar_cg_vc[] = {
    &USIM0_CLK_OSCAR_CG_VC, &USIM0_DATA_OSCAR_CG_VC, &USIM0_RST_OSCAR_CG_VC,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_oscar_cg_vc, "block_usim0", NORMAL, usim0_pins_oscar_cg_vc)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_oscar_cg_vc[] = {
    [NORMAL] = {usim0_func_normal_oscar_cg_vc, usim0_pullud_normal_oscar_cg_vc, usim0_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {usim0_func_lowpower_oscar_cg_vc, usim0_pullud_lowpower_oscar_cg_vc, usim0_drv_lowpower_oscar_cg_vc},

};

/*audio_spk pins */
static struct  iomux_pin *audio_spk_pins_oscar_cg_vc[] = {
    &GPIO_7_4_OSCAR_CG_VC,  NULL,
};

/*define blocks: audio_spk*/
IOMUX_BLOCK(block_audio_spk_oscar_cg_vc, "block_audio_spk", NORMAL, audio_spk_pins_oscar_cg_vc)



/*audio_spk*/

static enum lowlayer_func audio_spk_func_normal_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_normal_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_spk_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_lowpower_oscar_cg_vc[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config audio_spk_config_oscar_cg_vc[] = {
    [NORMAL] = {audio_spk_func_normal_oscar_cg_vc, audio_spk_pullud_normal_oscar_cg_vc, audio_spk_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {audio_spk_func_lowpower_oscar_cg_vc, audio_spk_pullud_lowpower_oscar_cg_vc, audio_spk_drv_lowpower_oscar_cg_vc},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_oscar_cg_vc[] = {
    &ISP_GPIO0_OSCAR_CG_VC, &ISP_GPIO2_OSCAR_CG_VC, &ISP_GPIO3_OSCAR_CG_VC, &ISP_RESETB0_OSCAR_CG_VC, &ISP_CCLK0_OSCAR_CG_VC, &ISP_SDA0_OSCAR_CG_VC, &ISP_SCL0_OSCAR_CG_VC,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_oscar_cg_vc, "block_mcamera", NORMAL, mcamera_pins_oscar_cg_vc)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_oscar_cg_vc[] = {
    [NORMAL] = {mcamera_func_normal_oscar_cg_vc, mcamera_pullud_normal_oscar_cg_vc, mcamera_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {mcamera_func_lowpower_oscar_cg_vc, mcamera_pullud_lowpower_oscar_cg_vc, mcamera_drv_lowpower_oscar_cg_vc},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_oscar_cg_vc[] = {
    &I2C0_SCL_OSCAR_CG_VC, &I2C0_SDA_OSCAR_CG_VC,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_oscar_cg_vc, "block_i2c0", NORMAL, i2c0_pins_oscar_cg_vc)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_oscar_cg_vc[] = {
    [NORMAL] = {i2c0_func_normal_oscar_cg_vc, i2c0_pullud_normal_oscar_cg_vc, i2c0_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {i2c0_func_lowpower_oscar_cg_vc, i2c0_pullud_lowpower_oscar_cg_vc, i2c0_drv_lowpower_oscar_cg_vc},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_oscar_cg_vc[] = {
    &I2C1_SCL_OSCAR_CG_VC, &I2C1_SDA_OSCAR_CG_VC,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_oscar_cg_vc, "block_i2c1", NORMAL, i2c1_pins_oscar_cg_vc)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_oscar_cg_vc[] = {
    [NORMAL] = {i2c1_func_normal_oscar_cg_vc, i2c1_pullud_normal_oscar_cg_vc, i2c1_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {i2c1_func_lowpower_oscar_cg_vc, i2c1_pullud_lowpower_oscar_cg_vc, i2c1_drv_lowpower_oscar_cg_vc},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_oscar_cg_vc[] = {
    &I2C2_SCL_OSCAR_CG_VC, &I2C2_SDA_OSCAR_CG_VC,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_oscar_cg_vc, "block_i2c2", NORMAL, i2c2_pins_oscar_cg_vc)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_oscar_cg_vc[] = {
    [NORMAL] = {i2c2_func_normal_oscar_cg_vc, i2c2_pullud_normal_oscar_cg_vc, i2c2_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {i2c2_func_lowpower_oscar_cg_vc, i2c2_pullud_lowpower_oscar_cg_vc, i2c2_drv_lowpower_oscar_cg_vc},

};

/*gps pins */
static struct  iomux_pin *gps_pins_oscar_cg_vc[] = {
    &GPIO_6_1_OSCAR_CG_VC, &RF_GPIO_1_OSCAR_CG_VC, &UART3_CTS_N_OSCAR_CG_VC, &UART3_RTS_N_OSCAR_CG_VC, &UART3_RXD_OSCAR_CG_VC, &UART3_TXD_OSCAR_CG_VC, &GPS_CLK_OSCAR_CG_VC,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_oscar_cg_vc, "block_gps", NORMAL, gps_pins_oscar_cg_vc)



/*GPS*/

static enum lowlayer_func gps_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_oscar_cg_vc[] = {
    [NORMAL] = {gps_func_normal_oscar_cg_vc, gps_pullud_normal_oscar_cg_vc, gps_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {gps_func_lowpower_oscar_cg_vc, gps_pullud_lowpower_oscar_cg_vc, gps_drv_lowpower_oscar_cg_vc},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_oscar_cg_vc[] = {
    &TCXO0_AFC_OSCAR_CG_VC, &TCXO1_AFC_OSCAR_CG_VC,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_oscar_cg_vc, "block_tcxo", NORMAL, tcxo_pins_oscar_cg_vc)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_oscar_cg_vc[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_oscar_cg_vc[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_oscar_cg_vc[] = {
    [NORMAL] = {tcxo_func_normal_oscar_cg_vc, tcxo_pullud_normal_oscar_cg_vc, tcxo_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {tcxo_func_lowpower_oscar_cg_vc, tcxo_pullud_lowpower_oscar_cg_vc, tcxo_drv_lowpower_oscar_cg_vc},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_oscar_cg_vc[] = {
    &GPIO_7_5_OSCAR_CG_VC,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_oscar_cg_vc, "block_rfant", NORMAL, rfant_pins_oscar_cg_vc)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_oscar_cg_vc[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_oscar_cg_vc[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_oscar_cg_vc[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_oscar_cg_vc[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_oscar_cg_vc[] = {
    [NORMAL] = {rfant_func_normal_oscar_cg_vc, rfant_pullud_normal_oscar_cg_vc, rfant_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {rfant_func_lowpower_oscar_cg_vc, rfant_pullud_lowpower_oscar_cg_vc, rfant_drv_lowpower_oscar_cg_vc},

};

/*wifi pins */
static struct  iomux_pin *wifi_pins_oscar_cg_vc[] = {
    &SDIO_DATA3_OSCAR_CG_VC, &SDIO_DATA2_OSCAR_CG_VC, &SDIO_DATA1_OSCAR_CG_VC, &SDIO_DATA0_OSCAR_CG_VC, &SDIO_CMD_OSCAR_CG_VC, &SDIO_CLK_OSCAR_CG_VC,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_oscar_cg_vc, "block_wifi", NORMAL, wifi_pins_oscar_cg_vc)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_oscar_cg_vc[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_oscar_cg_vc[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_oscar_cg_vc[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_oscar_cg_vc[] = {
    [NORMAL] = {wifi_func_normal_oscar_cg_vc, wifi_pullud_normal_oscar_cg_vc, wifi_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {wifi_func_lowpower_oscar_cg_vc, wifi_pullud_lowpower_oscar_cg_vc, wifi_drv_lowpower_oscar_cg_vc},

};

/*boot pins */
static struct  iomux_pin *boot_pins_oscar_cg_vc[] = {
    &BOOT_SEL_OSCAR_CG_VC, &GPIO_5_2_OSCAR_CG_VC,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_oscar_cg_vc, "block_boot", NORMAL, boot_pins_oscar_cg_vc)



/*BOOT*/

static enum lowlayer_func boot_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_oscar_cg_vc[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_oscar_cg_vc[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_oscar_cg_vc[] = {
    [NORMAL] = {boot_func_normal_oscar_cg_vc, boot_pullud_normal_oscar_cg_vc, boot_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {boot_func_lowpower_oscar_cg_vc, boot_pullud_lowpower_oscar_cg_vc, boot_drv_lowpower_oscar_cg_vc},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_oscar_cg_vc[] = {
    &PWM_OUT1_OSCAR_CG_VC, &GPIO_4_6_OSCAR_CG_VC, &GPIO_4_7_OSCAR_CG_VC, &GPIO_6_6_OSCAR_CG_VC, &PWM_OUT0_OSCAR_CG_VC,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_oscar_cg_vc, "block_lcd", NORMAL, lcd_pins_oscar_cg_vc)



/*LCD*/

static enum lowlayer_func lcd_func_normal_oscar_cg_vc[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_oscar_cg_vc[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_oscar_cg_vc[] = {
    [NORMAL] = {lcd_func_normal_oscar_cg_vc, lcd_pullud_normal_oscar_cg_vc, lcd_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {lcd_func_lowpower_oscar_cg_vc, lcd_pullud_lowpower_oscar_cg_vc, lcd_drv_lowpower_oscar_cg_vc},

};

/*sd pins */
static struct  iomux_pin *sd_pins_oscar_cg_vc[] = {
    &SD_CLK_OSCAR_CG_VC, &SD_CMD_OSCAR_CG_VC, &SD_DATA0_OSCAR_CG_VC, &SD_DATA1_OSCAR_CG_VC, &SD_DATA2_OSCAR_CG_VC, &SD_DATA3_OSCAR_CG_VC,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_oscar_cg_vc, "block_sd", NORMAL, sd_pins_oscar_cg_vc)



/*SD*/

static enum lowlayer_func sd_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_oscar_cg_vc[] = {LEVEL2, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_oscar_cg_vc[] = {LEVEL2, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_oscar_cg_vc[] = {
    [NORMAL] = {sd_func_normal_oscar_cg_vc, sd_pullud_normal_oscar_cg_vc, sd_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {sd_func_lowpower_oscar_cg_vc, sd_pullud_lowpower_oscar_cg_vc, sd_drv_lowpower_oscar_cg_vc},

};

/*key pins */
static struct  iomux_pin *key_pins_oscar_cg_vc[] = {
    &GPIO_4_2_OSCAR_CG_VC, &GPIO_4_3_OSCAR_CG_VC,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_oscar_cg_vc, "block_key", NORMAL, key_pins_oscar_cg_vc)



/*KEY*/

static enum lowlayer_func key_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_oscar_cg_vc[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_oscar_cg_vc[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_oscar_cg_vc[] = {
    [NORMAL] = {key_func_normal_oscar_cg_vc, key_pullud_normal_oscar_cg_vc, key_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {key_func_lowpower_oscar_cg_vc, key_pullud_lowpower_oscar_cg_vc, key_drv_lowpower_oscar_cg_vc},

};

/*test pins */
static struct  iomux_pin *test_pins_oscar_cg_vc[] = {
    &UART0_RXD_OSCAR_CG_VC, &UART0_TXD_OSCAR_CG_VC,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_oscar_cg_vc, "block_test", NORMAL, test_pins_oscar_cg_vc)



/*TEST*/

static enum lowlayer_func test_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_oscar_cg_vc[] = {
    [NORMAL] = {test_func_normal_oscar_cg_vc, test_pullud_normal_oscar_cg_vc, test_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {test_func_lowpower_oscar_cg_vc, test_pullud_lowpower_oscar_cg_vc, test_drv_lowpower_oscar_cg_vc},

};

/*audio_es305 pins */
static struct  iomux_pin *audio_es305_pins_oscar_cg_vc[] = {
    &UART2_RXD_OSCAR_CG_VC, &UART2_TXD_OSCAR_CG_VC,  NULL,
};

/*define blocks: audio_es305*/
IOMUX_BLOCK(block_audio_es305_oscar_cg_vc, "block_audio_es305", NORMAL, audio_es305_pins_oscar_cg_vc)



/*audio_es305*/

static enum lowlayer_func audio_es305_func_normal_oscar_cg_vc[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown audio_es305_pullud_normal_oscar_cg_vc[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func audio_es305_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown audio_es305_pullud_lowpower_oscar_cg_vc[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config audio_es305_config_oscar_cg_vc[] = {
    [NORMAL] = {audio_es305_func_normal_oscar_cg_vc, audio_es305_pullud_normal_oscar_cg_vc, audio_es305_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {audio_es305_func_lowpower_oscar_cg_vc, audio_es305_pullud_lowpower_oscar_cg_vc, audio_es305_drv_lowpower_oscar_cg_vc},

};

/*cdma pins */
static struct  iomux_pin *cdma_pins_oscar_cg_vc[] = {
    &GPIO_5_4_OSCAR_CG_VC, &GPIO_5_5_OSCAR_CG_VC, &GPIO_5_6_OSCAR_CG_VC, &GPIO_5_7_OSCAR_CG_VC,  NULL,
};

/*define blocks: cdma*/
IOMUX_BLOCK(block_cdma_oscar_cg_vc, "block_cdma", NORMAL, cdma_pins_oscar_cg_vc)



/*CDMA*/

static enum lowlayer_func cdma_func_normal_oscar_cg_vc[] = {FUNC6, FUNC6, FUNC6, FUNC6,  -INVALID,};
static enum pull_updown cdma_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func cdma_func_lowpower_oscar_cg_vc[] = {FUNC6, FUNC0, FUNC6, FUNC0,  -INVALID,};
static enum pull_updown cdma_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength cdma_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config cdma_config_oscar_cg_vc[] = {
    [NORMAL] = {cdma_func_normal_oscar_cg_vc, cdma_pullud_normal_oscar_cg_vc, cdma_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {cdma_func_lowpower_oscar_cg_vc, cdma_pullud_lowpower_oscar_cg_vc, cdma_drv_lowpower_oscar_cg_vc},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_oscar_cg_vc[] = {
    &I2S_XCLK_OSCAR_CG_VC, &I2S_XFS_OSCAR_CG_VC, &I2S_DI_OSCAR_CG_VC, &I2S_DO_OSCAR_CG_VC, &PCM0_XCLK_OSCAR_CG_VC, &PCM0_XFS_OSCAR_CG_VC, &PCM0_DI_OSCAR_CG_VC, &PCM0_DO_OSCAR_CG_VC, &UART1_TXD_OSCAR_CG_VC, &TS_ERR_OSCAR_CG_VC,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_oscar_cg_vc, "block_es305", NORMAL, es305_pins_oscar_cg_vc)



/*ES305*/

static enum lowlayer_func es305_func_normal_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_oscar_cg_vc[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_oscar_cg_vc[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_oscar_cg_vc[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_oscar_cg_vc[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_oscar_cg_vc[] = {
    [NORMAL] = {es305_func_normal_oscar_cg_vc, es305_pullud_normal_oscar_cg_vc, es305_drv_normal_oscar_cg_vc},
    [LOWPOWER] = {es305_func_lowpower_oscar_cg_vc, es305_pullud_lowpower_oscar_cg_vc, es305_drv_lowpower_oscar_cg_vc},

};

struct iomux_block_table block_config_table_oscar_cg_vc[] = {
    BLOCK_CONFIG("block_audio_eph", &block_audio_eph_oscar_cg_vc, audio_eph_config_oscar_cg_vc)
    BLOCK_CONFIG("block_charger", &block_charger_oscar_cg_vc, charger_config_oscar_cg_vc)
    BLOCK_CONFIG("block_flash", &block_flash_oscar_cg_vc, flash_config_oscar_cg_vc)
    BLOCK_CONFIG("block_bt", &block_bt_oscar_cg_vc, bt_config_oscar_cg_vc)
    BLOCK_CONFIG("block_scamera", &block_scamera_oscar_cg_vc, scamera_config_oscar_cg_vc)
    BLOCK_CONFIG("block_codec", &block_codec_oscar_cg_vc, codec_config_oscar_cg_vc)
    BLOCK_CONFIG("block_modem_switch", &block_modem_switch_oscar_cg_vc, modem_switch_config_oscar_cg_vc)
    BLOCK_CONFIG("block_pmu", &block_pmu_oscar_cg_vc, pmu_config_oscar_cg_vc)
    BLOCK_CONFIG("block_emmc", &block_emmc_oscar_cg_vc, emmc_config_oscar_cg_vc)
    BLOCK_CONFIG("block_odt", &block_odt_oscar_cg_vc, odt_config_oscar_cg_vc)
    BLOCK_CONFIG("block_rf", &block_rf_oscar_cg_vc, rf_config_oscar_cg_vc)
    BLOCK_CONFIG("block_tp", &block_tp_oscar_cg_vc, tp_config_oscar_cg_vc)
    BLOCK_CONFIG("block_switch", &block_switch_oscar_cg_vc, switch_config_oscar_cg_vc)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_oscar_cg_vc, rfpmu_config_oscar_cg_vc)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_oscar_cg_vc, i2c3_config_oscar_cg_vc)
    BLOCK_CONFIG("block_nfc", &block_nfc_oscar_cg_vc, nfc_config_oscar_cg_vc)
    BLOCK_CONFIG("block_usim1", &block_usim1_oscar_cg_vc, usim1_config_oscar_cg_vc)
    BLOCK_CONFIG("block_usim0", &block_usim0_oscar_cg_vc, usim0_config_oscar_cg_vc)
    BLOCK_CONFIG("block_audio_spk", &block_audio_spk_oscar_cg_vc, audio_spk_config_oscar_cg_vc)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_oscar_cg_vc, mcamera_config_oscar_cg_vc)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_oscar_cg_vc, i2c0_config_oscar_cg_vc)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_oscar_cg_vc, i2c1_config_oscar_cg_vc)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_oscar_cg_vc, i2c2_config_oscar_cg_vc)
    BLOCK_CONFIG("block_gps", &block_gps_oscar_cg_vc, gps_config_oscar_cg_vc)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_oscar_cg_vc, tcxo_config_oscar_cg_vc)
    BLOCK_CONFIG("block_rfant", &block_rfant_oscar_cg_vc, rfant_config_oscar_cg_vc)
    BLOCK_CONFIG("block_wifi", &block_wifi_oscar_cg_vc, wifi_config_oscar_cg_vc)
    BLOCK_CONFIG("block_boot", &block_boot_oscar_cg_vc, boot_config_oscar_cg_vc)
    BLOCK_CONFIG("block_lcd", &block_lcd_oscar_cg_vc, lcd_config_oscar_cg_vc)
    BLOCK_CONFIG("block_sd", &block_sd_oscar_cg_vc, sd_config_oscar_cg_vc)
    BLOCK_CONFIG("block_key", &block_key_oscar_cg_vc, key_config_oscar_cg_vc)
    BLOCK_CONFIG("block_test", &block_test_oscar_cg_vc, test_config_oscar_cg_vc)
    BLOCK_CONFIG("block_audio_es305", &block_audio_es305_oscar_cg_vc, audio_es305_config_oscar_cg_vc)
    BLOCK_CONFIG("block_cdma", &block_cdma_oscar_cg_vc, cdma_config_oscar_cg_vc)
    BLOCK_CONFIG("block_es305", &block_es305_oscar_cg_vc, es305_config_oscar_cg_vc)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
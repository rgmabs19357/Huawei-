/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_oscar_vtl_vd_iomux_blocks.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_OSCAR_VTL_VD_IOMUX_BLOCKS_H__
#define __HI6620_OSCAR_VTL_VD_IOMUX_BLOCKS_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "iomux.h"
#include "hi6620_oscar_vtl_vd_iomux_pins.h"
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


/*wifi pins */
static struct  iomux_pin *wifi_pins_oscar_vtl_vd[] = {
    &SDIO_DATA3_OSCAR_VTL_VD, &SDIO_DATA2_OSCAR_VTL_VD, &SDIO_DATA1_OSCAR_VTL_VD, &SDIO_DATA0_OSCAR_VTL_VD, &SDIO_CMD_OSCAR_VTL_VD, &SDIO_CLK_OSCAR_VTL_VD,  NULL,
};

/*define blocks: wifi*/
IOMUX_BLOCK(block_wifi_oscar_vtl_vd, "block_wifi", NORMAL, wifi_pins_oscar_vtl_vd)



/*WIFI*/

static enum lowlayer_func wifi_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown wifi_pullud_normal_oscar_vtl_vd[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static enum lowlayer_func wifi_func_lowpower_oscar_vtl_vd[] = {FUNC2, FUNC2, FUNC2, FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown wifi_pullud_lowpower_oscar_vtl_vd[] = {PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength wifi_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL1,  -INVALID,};

static struct block_config wifi_config_oscar_vtl_vd[] = {
    [NORMAL] = {wifi_func_normal_oscar_vtl_vd, wifi_pullud_normal_oscar_vtl_vd, wifi_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {wifi_func_lowpower_oscar_vtl_vd, wifi_pullud_lowpower_oscar_vtl_vd, wifi_drv_lowpower_oscar_vtl_vd},

};

/*charger pins */
static struct  iomux_pin *charger_pins_oscar_vtl_vd[] = {
    &GPIO_4_0_OSCAR_VTL_VD,  NULL,
};

/*define blocks: charger*/
IOMUX_BLOCK(block_charger_oscar_vtl_vd, "block_charger", NORMAL, charger_pins_oscar_vtl_vd)



/*CHARGER*/

static enum lowlayer_func charger_func_normal_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func charger_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown charger_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength charger_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config charger_config_oscar_vtl_vd[] = {
    [NORMAL] = {charger_func_normal_oscar_vtl_vd, charger_pullud_normal_oscar_vtl_vd, charger_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {charger_func_lowpower_oscar_vtl_vd, charger_pullud_lowpower_oscar_vtl_vd, charger_drv_lowpower_oscar_vtl_vd},

};

/*flash pins */
static struct  iomux_pin *flash_pins_oscar_vtl_vd[] = {
    &ISP_GPIO5_OSCAR_VTL_VD, &RF_GPIO_20_OSCAR_VTL_VD,  NULL,
};

/*define blocks: flash*/
IOMUX_BLOCK(block_flash_oscar_vtl_vd, "block_flash", NORMAL, flash_pins_oscar_vtl_vd)



/*FLASH*/

static enum lowlayer_func flash_func_normal_oscar_vtl_vd[] = {FUNC2, FUNC0,  -INVALID,};
static enum pull_updown flash_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func flash_func_lowpower_oscar_vtl_vd[] = {FUNC2, FUNC2,  -INVALID,};
static enum pull_updown flash_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength flash_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config flash_config_oscar_vtl_vd[] = {
    [NORMAL] = {flash_func_normal_oscar_vtl_vd, flash_pullud_normal_oscar_vtl_vd, flash_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {flash_func_lowpower_oscar_vtl_vd, flash_pullud_lowpower_oscar_vtl_vd, flash_drv_lowpower_oscar_vtl_vd},

};

/*bt pins */
static struct  iomux_pin *bt_pins_oscar_vtl_vd[] = {
    &UART4_CTS_N_OSCAR_VTL_VD, &UART4_RTS_N_OSCAR_VTL_VD, &UART4_RXD_OSCAR_VTL_VD, &UART4_TXD_OSCAR_VTL_VD, &GPIO_15_7_OSCAR_VTL_VD,  NULL,
};

/*define blocks: bt*/
IOMUX_BLOCK(block_bt_oscar_vtl_vd, "block_bt", NORMAL, bt_pins_oscar_vtl_vd)



/*BT*/

static enum lowlayer_func bt_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func bt_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC4, FUNC0, FUNC4, FUNC0,  -INVALID,};
static enum pull_updown bt_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, PULLUP, NOPULL, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength bt_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config bt_config_oscar_vtl_vd[] = {
    [NORMAL] = {bt_func_normal_oscar_vtl_vd, bt_pullud_normal_oscar_vtl_vd, bt_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {bt_func_lowpower_oscar_vtl_vd, bt_pullud_lowpower_oscar_vtl_vd, bt_drv_lowpower_oscar_vtl_vd},

};

/*scamera pins */
static struct  iomux_pin *scamera_pins_oscar_vtl_vd[] = {
    &ISP_GPIO1_OSCAR_VTL_VD, &ISP_GPIO4_OSCAR_VTL_VD, &ISP_RESETB1_OSCAR_VTL_VD, &ISP_CCLK1_OSCAR_VTL_VD, &ISP_SDA1_OSCAR_VTL_VD, &ISP_SCL1_OSCAR_VTL_VD,  NULL,
};

/*define blocks: scamera*/
IOMUX_BLOCK(block_scamera_oscar_vtl_vd, "block_scamera", NORMAL, scamera_pins_oscar_vtl_vd)



/*SCAMERA*/

static enum lowlayer_func scamera_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown scamera_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength scamera_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func scamera_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown scamera_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength scamera_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config scamera_config_oscar_vtl_vd[] = {
    [NORMAL] = {scamera_func_normal_oscar_vtl_vd, scamera_pullud_normal_oscar_vtl_vd, scamera_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {scamera_func_lowpower_oscar_vtl_vd, scamera_pullud_lowpower_oscar_vtl_vd, scamera_drv_lowpower_oscar_vtl_vd},

};

/*codec pins */
static struct  iomux_pin *codec_pins_oscar_vtl_vd[] = {
    &PCM1_XCLK_OSCAR_VTL_VD, &PCM1_XFS_OSCAR_VTL_VD, &PCM1_DI_OSCAR_VTL_VD, &PCM1_DO_OSCAR_VTL_VD,  NULL,
};

/*define blocks: codec*/
IOMUX_BLOCK(block_codec_oscar_vtl_vd, "block_codec", NORMAL, codec_pins_oscar_vtl_vd)



/*CODEC*/

static enum lowlayer_func codec_func_normal_oscar_vtl_vd[] = {FUNC2, FUNC2, FUNC2, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_normal_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func codec_func_lowpower_oscar_vtl_vd[] = {FUNC2, FUNC2, FUNC2, FUNC0,  -INVALID,};
static enum pull_updown codec_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength codec_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config codec_config_oscar_vtl_vd[] = {
    [NORMAL] = {codec_func_normal_oscar_vtl_vd, codec_pullud_normal_oscar_vtl_vd, codec_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {codec_func_lowpower_oscar_vtl_vd, codec_pullud_lowpower_oscar_vtl_vd, codec_drv_lowpower_oscar_vtl_vd},

};

/*pmu pins */
static struct  iomux_pin *pmu_pins_oscar_vtl_vd[] = {
    &HKADC_SSI_OSCAR_VTL_VD, &AUX_SSI0_OSCAR_VTL_VD, &AUX_SSI1_OSCAR_VTL_VD, &GPIO_5_0_OSCAR_VTL_VD,  NULL,
};

/*define blocks: pmu*/
IOMUX_BLOCK(block_pmu_oscar_vtl_vd, "block_pmu", NORMAL, pmu_pins_oscar_vtl_vd)



/*PMU*/

static enum lowlayer_func pmu_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_normal_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func pmu_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown pmu_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength pmu_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config pmu_config_oscar_vtl_vd[] = {
    [NORMAL] = {pmu_func_normal_oscar_vtl_vd, pmu_pullud_normal_oscar_vtl_vd, pmu_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {pmu_func_lowpower_oscar_vtl_vd, pmu_pullud_lowpower_oscar_vtl_vd, pmu_drv_lowpower_oscar_vtl_vd},

};

/*emmc pins */
static struct  iomux_pin *emmc_pins_oscar_vtl_vd[] = {
    &EMMC_CLK_OSCAR_VTL_VD, &EMMC_CMD_OSCAR_VTL_VD, &EMMC_DATA0_OSCAR_VTL_VD, &EMMC_DATA1_OSCAR_VTL_VD, &EMMC_DATA2_OSCAR_VTL_VD, &EMMC_DATA3_OSCAR_VTL_VD, &EMMC_DATA4_OSCAR_VTL_VD, &EMMC_DATA5_OSCAR_VTL_VD, &EMMC_DATA6_OSCAR_VTL_VD, &EMMC_DATA7_OSCAR_VTL_VD, &GPIO_2_3_OSCAR_VTL_VD,  NULL,
};

/*define blocks: emmc*/
IOMUX_BLOCK(block_emmc_oscar_vtl_vd, "block_emmc", NORMAL, emmc_pins_oscar_vtl_vd)



/*EMMC*/

static enum lowlayer_func emmc_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_normal_oscar_vtl_vd[] = {NOPULL, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, PULLUP, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_normal_oscar_vtl_vd[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static enum lowlayer_func emmc_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC4,  -INVALID,};
static enum pull_updown emmc_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength emmc_drv_lowpower_oscar_vtl_vd[] = {LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL1, LEVEL0,  -INVALID,};

static struct block_config emmc_config_oscar_vtl_vd[] = {
    [NORMAL] = {emmc_func_normal_oscar_vtl_vd, emmc_pullud_normal_oscar_vtl_vd, emmc_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {emmc_func_lowpower_oscar_vtl_vd, emmc_pullud_lowpower_oscar_vtl_vd, emmc_drv_lowpower_oscar_vtl_vd},

};

/*odt pins */
static struct  iomux_pin *odt_pins_oscar_vtl_vd[] = {
    &RF_RESET1_OSCAR_VTL_VD,  NULL,
};

/*define blocks: odt*/
IOMUX_BLOCK(block_odt_oscar_vtl_vd, "block_odt", NORMAL, odt_pins_oscar_vtl_vd)



/*ODT*/

static enum lowlayer_func odt_func_normal_oscar_vtl_vd[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func odt_func_lowpower_oscar_vtl_vd[] = {FUNC4,  -INVALID,};
static enum pull_updown odt_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength odt_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config odt_config_oscar_vtl_vd[] = {
    [NORMAL] = {odt_func_normal_oscar_vtl_vd, odt_pullud_normal_oscar_vtl_vd, odt_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {odt_func_lowpower_oscar_vtl_vd, odt_pullud_lowpower_oscar_vtl_vd, odt_drv_lowpower_oscar_vtl_vd},

};

/*tp pins */
static struct  iomux_pin *tp_pins_oscar_vtl_vd[] = {
    &GPIO_18_7_OSCAR_VTL_VD,  NULL,
};

/*define blocks: tp*/
IOMUX_BLOCK(block_tp_oscar_vtl_vd, "block_tp", NORMAL, tp_pins_oscar_vtl_vd)



/*TP*/

static enum lowlayer_func tp_func_normal_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func tp_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown tp_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength tp_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config tp_config_oscar_vtl_vd[] = {
    [NORMAL] = {tp_func_normal_oscar_vtl_vd, tp_pullud_normal_oscar_vtl_vd, tp_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {tp_func_lowpower_oscar_vtl_vd, tp_pullud_lowpower_oscar_vtl_vd, tp_drv_lowpower_oscar_vtl_vd},

};

/*rf pins */
static struct  iomux_pin *rf_pins_oscar_vtl_vd[] = {
    &RF_TX_EN1_OSCAR_VTL_VD, &RF_TCVR_ON0_OSCAR_VTL_VD, &RF_TCVR_ON1_OSCAR_VTL_VD, &RF_SSI0_OSCAR_VTL_VD, &RF_SSI1_OSCAR_VTL_VD, &RF_GPIO_2_OSCAR_VTL_VD, &RF_GPIO_3_OSCAR_VTL_VD, &RF_GPIO_4_OSCAR_VTL_VD, &RF_GPIO_5_OSCAR_VTL_VD, &RF_GPIO_6_OSCAR_VTL_VD, &RF_GPIO_7_OSCAR_VTL_VD, &RF_GPIO_8_OSCAR_VTL_VD, &RF_GPIO_9_OSCAR_VTL_VD, &RF_GPIO_10_OSCAR_VTL_VD, &RF_GPIO_11_OSCAR_VTL_VD, &RF_GPIO_12_OSCAR_VTL_VD, &RF_GPIO_13_OSCAR_VTL_VD, &RF_GPIO_14_OSCAR_VTL_VD, &RF_GPIO_15_OSCAR_VTL_VD, &RF_GPIO_16_OSCAR_VTL_VD, &RF_GPIO_17_OSCAR_VTL_VD, &RF_GPIO_18_OSCAR_VTL_VD, &RF_GPIO_19_OSCAR_VTL_VD, &RF_GPIO_21_OSCAR_VTL_VD, &RF_GPIO_22_OSCAR_VTL_VD, &RF_GPIO_23_OSCAR_VTL_VD, &RF_GPIO_24_OSCAR_VTL_VD, &RF_GPIO_25_OSCAR_VTL_VD, &RF_GPIO_26_OSCAR_VTL_VD, &RF_GPIO_27_OSCAR_VTL_VD, &RF_GPIO_28_OSCAR_VTL_VD, &RF_GPIO_30_OSCAR_VTL_VD,  NULL,
};

/*define blocks: rf*/
IOMUX_BLOCK(block_rf_oscar_vtl_vd, "block_rf", NORMAL, rf_pins_oscar_vtl_vd)



/*RF*/

static enum lowlayer_func rf_func_normal_oscar_vtl_vd[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rf_func_lowpower_oscar_vtl_vd[] = {FUNC4, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rf_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength rf_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rf_config_oscar_vtl_vd[] = {
    [NORMAL] = {rf_func_normal_oscar_vtl_vd, rf_pullud_normal_oscar_vtl_vd, rf_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {rf_func_lowpower_oscar_vtl_vd, rf_pullud_lowpower_oscar_vtl_vd, rf_drv_lowpower_oscar_vtl_vd},

};

/*rfpmu pins */
static struct  iomux_pin *rfpmu_pins_oscar_vtl_vd[] = {
    &RF_MIPI_CLK0_OSCAR_VTL_VD, &RF_MIPI_DATA0_OSCAR_VTL_VD, &APT_PDM0_OSCAR_VTL_VD,  NULL,
};

/*define blocks: rfpmu*/
IOMUX_BLOCK(block_rfpmu_oscar_vtl_vd, "block_rfpmu", NORMAL, rfpmu_pins_oscar_vtl_vd)



/*RFPMU*/

static enum lowlayer_func rfpmu_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_normal_oscar_vtl_vd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func rfpmu_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown rfpmu_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength rfpmu_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config rfpmu_config_oscar_vtl_vd[] = {
    [NORMAL] = {rfpmu_func_normal_oscar_vtl_vd, rfpmu_pullud_normal_oscar_vtl_vd, rfpmu_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {rfpmu_func_lowpower_oscar_vtl_vd, rfpmu_pullud_lowpower_oscar_vtl_vd, rfpmu_drv_lowpower_oscar_vtl_vd},

};

/*i2c3 pins */
static struct  iomux_pin *i2c3_pins_oscar_vtl_vd[] = {
    &I2C3_SCL_OSCAR_VTL_VD, &I2C3_SDA_OSCAR_VTL_VD,  NULL,
};

/*define blocks: i2c3*/
IOMUX_BLOCK(block_i2c3_oscar_vtl_vd, "block_i2c3", NORMAL, i2c3_pins_oscar_vtl_vd)



/*I2C3*/

static enum lowlayer_func i2c3_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c3_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c3_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c3_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c3_config_oscar_vtl_vd[] = {
    [NORMAL] = {i2c3_func_normal_oscar_vtl_vd, i2c3_pullud_normal_oscar_vtl_vd, i2c3_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {i2c3_func_lowpower_oscar_vtl_vd, i2c3_pullud_lowpower_oscar_vtl_vd, i2c3_drv_lowpower_oscar_vtl_vd},

};

/*nfc pins */
static struct  iomux_pin *nfc_pins_oscar_vtl_vd[] = {
    &GPIO_6_5_OSCAR_VTL_VD,  NULL,
};

/*define blocks: nfc*/
IOMUX_BLOCK(block_nfc_oscar_vtl_vd, "block_nfc", NORMAL, nfc_pins_oscar_vtl_vd)



/*NFC*/

static enum lowlayer_func nfc_func_normal_oscar_vtl_vd[] = {FUNC6,  -INVALID,};
static enum pull_updown nfc_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func nfc_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown nfc_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength nfc_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config nfc_config_oscar_vtl_vd[] = {
    [NORMAL] = {nfc_func_normal_oscar_vtl_vd, nfc_pullud_normal_oscar_vtl_vd, nfc_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {nfc_func_lowpower_oscar_vtl_vd, nfc_pullud_lowpower_oscar_vtl_vd, nfc_drv_lowpower_oscar_vtl_vd},

};

/*usim1 pins */
static struct  iomux_pin *usim1_pins_oscar_vtl_vd[] = {
    &USIM1_CLK_OSCAR_VTL_VD, &USIM1_DATA_OSCAR_VTL_VD, &USIM1_RST_OSCAR_VTL_VD,  NULL,
};

/*define blocks: usim1*/
IOMUX_BLOCK(block_usim1_oscar_vtl_vd, "block_usim1", NORMAL, usim1_pins_oscar_vtl_vd)



/*USIM1*/

static enum lowlayer_func usim1_func_normal_oscar_vtl_vd[] = {FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown usim1_pullud_normal_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength usim1_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim1_func_lowpower_oscar_vtl_vd[] = {FUNC2, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown usim1_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength usim1_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim1_config_oscar_vtl_vd[] = {
    [NORMAL] = {usim1_func_normal_oscar_vtl_vd, usim1_pullud_normal_oscar_vtl_vd, usim1_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {usim1_func_lowpower_oscar_vtl_vd, usim1_pullud_lowpower_oscar_vtl_vd, usim1_drv_lowpower_oscar_vtl_vd},

};

/*usim0 pins */
static struct  iomux_pin *usim0_pins_oscar_vtl_vd[] = {
    &USIM0_CLK_OSCAR_VTL_VD, &USIM0_DATA_OSCAR_VTL_VD, &USIM0_RST_OSCAR_VTL_VD,  NULL,
};

/*define blocks: usim0*/
IOMUX_BLOCK(block_usim0_oscar_vtl_vd, "block_usim0", NORMAL, usim0_pins_oscar_vtl_vd)



/*USIM0*/

static enum lowlayer_func usim0_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func usim0_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown usim0_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength usim0_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config usim0_config_oscar_vtl_vd[] = {
    [NORMAL] = {usim0_func_normal_oscar_vtl_vd, usim0_pullud_normal_oscar_vtl_vd, usim0_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {usim0_func_lowpower_oscar_vtl_vd, usim0_pullud_lowpower_oscar_vtl_vd, usim0_drv_lowpower_oscar_vtl_vd},

};

/*audio_spk pins */
static struct  iomux_pin *audio_spk_pins_oscar_vtl_vd[] = {
    &GPIO_7_4_OSCAR_VTL_VD,  NULL,
};

/*define blocks: audio_spk*/
IOMUX_BLOCK(block_audio_spk_oscar_vtl_vd, "block_audio_spk", NORMAL, audio_spk_pins_oscar_vtl_vd)



/*audio_spk*/

static enum lowlayer_func audio_spk_func_normal_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_spk_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_spk_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_spk_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config audio_spk_config_oscar_vtl_vd[] = {
    [NORMAL] = {audio_spk_func_normal_oscar_vtl_vd, audio_spk_pullud_normal_oscar_vtl_vd, audio_spk_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {audio_spk_func_lowpower_oscar_vtl_vd, audio_spk_pullud_lowpower_oscar_vtl_vd, audio_spk_drv_lowpower_oscar_vtl_vd},

};

/*mcamera pins */
static struct  iomux_pin *mcamera_pins_oscar_vtl_vd[] = {
    &ISP_GPIO0_OSCAR_VTL_VD, &ISP_GPIO2_OSCAR_VTL_VD, &ISP_GPIO3_OSCAR_VTL_VD, &ISP_RESETB0_OSCAR_VTL_VD, &ISP_CCLK0_OSCAR_VTL_VD, &ISP_SDA0_OSCAR_VTL_VD, &ISP_SCL0_OSCAR_VTL_VD,  NULL,
};

/*define blocks: mcamera*/
IOMUX_BLOCK(block_mcamera_oscar_vtl_vd, "block_mcamera", NORMAL, mcamera_pins_oscar_vtl_vd)



/*MCAMERA*/

static enum lowlayer_func mcamera_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown mcamera_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength mcamera_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func mcamera_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC2, FUNC0, FUNC0, FUNC2, FUNC2,  -INVALID,};
static enum pull_updown mcamera_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength mcamera_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config mcamera_config_oscar_vtl_vd[] = {
    [NORMAL] = {mcamera_func_normal_oscar_vtl_vd, mcamera_pullud_normal_oscar_vtl_vd, mcamera_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {mcamera_func_lowpower_oscar_vtl_vd, mcamera_pullud_lowpower_oscar_vtl_vd, mcamera_drv_lowpower_oscar_vtl_vd},

};

/*i2c0 pins */
static struct  iomux_pin *i2c0_pins_oscar_vtl_vd[] = {
    &I2C0_SCL_OSCAR_VTL_VD, &I2C0_SDA_OSCAR_VTL_VD,  NULL,
};

/*define blocks: i2c0*/
IOMUX_BLOCK(block_i2c0_oscar_vtl_vd, "block_i2c0", NORMAL, i2c0_pins_oscar_vtl_vd)



/*I2C0*/

static enum lowlayer_func i2c0_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c0_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c0_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c0_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c0_config_oscar_vtl_vd[] = {
    [NORMAL] = {i2c0_func_normal_oscar_vtl_vd, i2c0_pullud_normal_oscar_vtl_vd, i2c0_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {i2c0_func_lowpower_oscar_vtl_vd, i2c0_pullud_lowpower_oscar_vtl_vd, i2c0_drv_lowpower_oscar_vtl_vd},

};

/*i2c1 pins */
static struct  iomux_pin *i2c1_pins_oscar_vtl_vd[] = {
    &I2C1_SCL_OSCAR_VTL_VD, &I2C1_SDA_OSCAR_VTL_VD,  NULL,
};

/*define blocks: i2c1*/
IOMUX_BLOCK(block_i2c1_oscar_vtl_vd, "block_i2c1", NORMAL, i2c1_pins_oscar_vtl_vd)



/*I2C1*/

static enum lowlayer_func i2c1_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c1_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c1_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c1_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c1_config_oscar_vtl_vd[] = {
    [NORMAL] = {i2c1_func_normal_oscar_vtl_vd, i2c1_pullud_normal_oscar_vtl_vd, i2c1_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {i2c1_func_lowpower_oscar_vtl_vd, i2c1_pullud_lowpower_oscar_vtl_vd, i2c1_drv_lowpower_oscar_vtl_vd},

};

/*i2c2 pins */
static struct  iomux_pin *i2c2_pins_oscar_vtl_vd[] = {
    &I2C2_SCL_OSCAR_VTL_VD, &I2C2_SDA_OSCAR_VTL_VD,  NULL,
};

/*define blocks: i2c2*/
IOMUX_BLOCK(block_i2c2_oscar_vtl_vd, "block_i2c2", NORMAL, i2c2_pins_oscar_vtl_vd)



/*I2C2*/

static enum lowlayer_func i2c2_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func i2c2_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown i2c2_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength i2c2_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config i2c2_config_oscar_vtl_vd[] = {
    [NORMAL] = {i2c2_func_normal_oscar_vtl_vd, i2c2_pullud_normal_oscar_vtl_vd, i2c2_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {i2c2_func_lowpower_oscar_vtl_vd, i2c2_pullud_lowpower_oscar_vtl_vd, i2c2_drv_lowpower_oscar_vtl_vd},

};

/*gps pins */
static struct  iomux_pin *gps_pins_oscar_vtl_vd[] = {
    &GPIO_6_1_OSCAR_VTL_VD, &RF_GPIO_1_OSCAR_VTL_VD, &UART3_CTS_N_OSCAR_VTL_VD, &UART3_RTS_N_OSCAR_VTL_VD, &UART3_RXD_OSCAR_VTL_VD, &UART3_TXD_OSCAR_VTL_VD, &GPS_CLK_OSCAR_VTL_VD,  NULL,
};

/*define blocks: gps*/
IOMUX_BLOCK(block_gps_oscar_vtl_vd, "block_gps", NORMAL, gps_pins_oscar_vtl_vd)



/*GPS*/

static enum lowlayer_func gps_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown gps_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func gps_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown gps_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength gps_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config gps_config_oscar_vtl_vd[] = {
    [NORMAL] = {gps_func_normal_oscar_vtl_vd, gps_pullud_normal_oscar_vtl_vd, gps_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {gps_func_lowpower_oscar_vtl_vd, gps_pullud_lowpower_oscar_vtl_vd, gps_drv_lowpower_oscar_vtl_vd},

};

/*tcxo pins */
static struct  iomux_pin *tcxo_pins_oscar_vtl_vd[] = {
    &TCXO0_AFC_OSCAR_VTL_VD, &TCXO1_AFC_OSCAR_VTL_VD,  NULL,
};

/*define blocks: tcxo*/
IOMUX_BLOCK(block_tcxo_oscar_vtl_vd, "block_tcxo", NORMAL, tcxo_pins_oscar_vtl_vd)



/*TCXO*/

static enum lowlayer_func tcxo_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown tcxo_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength tcxo_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func tcxo_func_lowpower_oscar_vtl_vd[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown tcxo_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN, PULLDOWN,  -INVALID,};
static enum drive_strength tcxo_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config tcxo_config_oscar_vtl_vd[] = {
    [NORMAL] = {tcxo_func_normal_oscar_vtl_vd, tcxo_pullud_normal_oscar_vtl_vd, tcxo_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {tcxo_func_lowpower_oscar_vtl_vd, tcxo_pullud_lowpower_oscar_vtl_vd, tcxo_drv_lowpower_oscar_vtl_vd},

};

/*rfant pins */
static struct  iomux_pin *rfant_pins_oscar_vtl_vd[] = {
    &GPIO_7_5_OSCAR_VTL_VD,  NULL,
};

/*define blocks: rfant*/
IOMUX_BLOCK(block_rfant_oscar_vtl_vd, "block_rfant", NORMAL, rfant_pins_oscar_vtl_vd)



/*RFANT*/

static enum lowlayer_func rfant_func_normal_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_normal_oscar_vtl_vd[] = {PULLUP,  -INVALID,};
static enum drive_strength rfant_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func rfant_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown rfant_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN,  -INVALID,};
static enum drive_strength rfant_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config rfant_config_oscar_vtl_vd[] = {
    [NORMAL] = {rfant_func_normal_oscar_vtl_vd, rfant_pullud_normal_oscar_vtl_vd, rfant_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {rfant_func_lowpower_oscar_vtl_vd, rfant_pullud_lowpower_oscar_vtl_vd, rfant_drv_lowpower_oscar_vtl_vd},

};

/*audio_eph pins */
static struct  iomux_pin *audio_eph_pins_oscar_vtl_vd[] = {
    &GPIO_5_1_OSCAR_VTL_VD,  NULL,
};

/*define blocks: audio_eph*/
IOMUX_BLOCK(block_audio_eph_oscar_vtl_vd, "block_audio_eph", NORMAL, audio_eph_pins_oscar_vtl_vd)



/*audio_eph*/

static enum lowlayer_func audio_eph_func_normal_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_normal_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_normal_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static enum lowlayer_func audio_eph_func_lowpower_oscar_vtl_vd[] = {FUNC0,  -INVALID,};
static enum pull_updown audio_eph_pullud_lowpower_oscar_vtl_vd[] = {NOPULL,  -INVALID,};
static enum drive_strength audio_eph_drv_lowpower_oscar_vtl_vd[] = {LEVEL0,  -INVALID,};

static struct block_config audio_eph_config_oscar_vtl_vd[] = {
    [NORMAL] = {audio_eph_func_normal_oscar_vtl_vd, audio_eph_pullud_normal_oscar_vtl_vd, audio_eph_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {audio_eph_func_lowpower_oscar_vtl_vd, audio_eph_pullud_lowpower_oscar_vtl_vd, audio_eph_drv_lowpower_oscar_vtl_vd},

};

/*boot pins */
static struct  iomux_pin *boot_pins_oscar_vtl_vd[] = {
    &BOOT_SEL_OSCAR_VTL_VD, &GPIO_5_2_OSCAR_VTL_VD,  NULL,
};

/*define blocks: boot*/
IOMUX_BLOCK(block_boot_oscar_vtl_vd, "block_boot", NORMAL, boot_pins_oscar_vtl_vd)



/*BOOT*/

static enum lowlayer_func boot_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_normal_oscar_vtl_vd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func boot_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown boot_pullud_lowpower_oscar_vtl_vd[] = {PULLUP, PULLDOWN,  -INVALID,};
static enum drive_strength boot_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config boot_config_oscar_vtl_vd[] = {
    [NORMAL] = {boot_func_normal_oscar_vtl_vd, boot_pullud_normal_oscar_vtl_vd, boot_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {boot_func_lowpower_oscar_vtl_vd, boot_pullud_lowpower_oscar_vtl_vd, boot_drv_lowpower_oscar_vtl_vd},

};

/*lcd pins */
static struct  iomux_pin *lcd_pins_oscar_vtl_vd[] = {
    &PWM_OUT1_OSCAR_VTL_VD, &GPIO_4_6_OSCAR_VTL_VD, &GPIO_4_7_OSCAR_VTL_VD, &GPIO_6_6_OSCAR_VTL_VD, &PWM_OUT0_OSCAR_VTL_VD,  NULL,
};

/*define blocks: lcd*/
IOMUX_BLOCK(block_lcd_oscar_vtl_vd, "block_lcd", NORMAL, lcd_pins_oscar_vtl_vd)



/*LCD*/

static enum lowlayer_func lcd_func_normal_oscar_vtl_vd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC2,  -INVALID,};
static enum pull_updown lcd_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func lcd_func_lowpower_oscar_vtl_vd[] = {FUNC2, FUNC0, FUNC4, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown lcd_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength lcd_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config lcd_config_oscar_vtl_vd[] = {
    [NORMAL] = {lcd_func_normal_oscar_vtl_vd, lcd_pullud_normal_oscar_vtl_vd, lcd_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {lcd_func_lowpower_oscar_vtl_vd, lcd_pullud_lowpower_oscar_vtl_vd, lcd_drv_lowpower_oscar_vtl_vd},

};

/*key pins */
static struct  iomux_pin *key_pins_oscar_vtl_vd[] = {
    &GPIO_4_2_OSCAR_VTL_VD, &GPIO_4_3_OSCAR_VTL_VD,  NULL,
};

/*define blocks: key*/
IOMUX_BLOCK(block_key_oscar_vtl_vd, "block_key", NORMAL, key_pins_oscar_vtl_vd)



/*KEY*/

static enum lowlayer_func key_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_normal_oscar_vtl_vd[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func key_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown key_pullud_lowpower_oscar_vtl_vd[] = {PULLUP, PULLUP,  -INVALID,};
static enum drive_strength key_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config key_config_oscar_vtl_vd[] = {
    [NORMAL] = {key_func_normal_oscar_vtl_vd, key_pullud_normal_oscar_vtl_vd, key_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {key_func_lowpower_oscar_vtl_vd, key_pullud_lowpower_oscar_vtl_vd, key_drv_lowpower_oscar_vtl_vd},

};

/*test pins */
static struct  iomux_pin *test_pins_oscar_vtl_vd[] = {
    &UART0_RXD_OSCAR_VTL_VD, &UART0_TXD_OSCAR_VTL_VD,  NULL,
};

/*define blocks: test*/
IOMUX_BLOCK(block_test_oscar_vtl_vd, "block_test", NORMAL, test_pins_oscar_vtl_vd)



/*TEST*/

static enum lowlayer_func test_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func test_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown test_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL,  -INVALID,};
static enum drive_strength test_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config test_config_oscar_vtl_vd[] = {
    [NORMAL] = {test_func_normal_oscar_vtl_vd, test_pullud_normal_oscar_vtl_vd, test_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {test_func_lowpower_oscar_vtl_vd, test_pullud_lowpower_oscar_vtl_vd, test_drv_lowpower_oscar_vtl_vd},

};

/*audio_es305 pins */
static struct  iomux_pin *audio_es305_pins_oscar_vtl_vd[] = {
    &UART2_RXD_OSCAR_VTL_VD, &UART2_TXD_OSCAR_VTL_VD,  NULL,
};

/*define blocks: audio_es305*/
IOMUX_BLOCK(block_audio_es305_oscar_vtl_vd, "block_audio_es305", NORMAL, audio_es305_pins_oscar_vtl_vd)



/*audio_es305*/

static enum lowlayer_func audio_es305_func_normal_oscar_vtl_vd[] = {FUNC4, FUNC4,  -INVALID,};
static enum pull_updown audio_es305_pullud_normal_oscar_vtl_vd[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func audio_es305_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0,  -INVALID,};
static enum pull_updown audio_es305_pullud_lowpower_oscar_vtl_vd[] = {PULLDOWN, NOPULL,  -INVALID,};
static enum drive_strength audio_es305_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0,  -INVALID,};

static struct block_config audio_es305_config_oscar_vtl_vd[] = {
    [NORMAL] = {audio_es305_func_normal_oscar_vtl_vd, audio_es305_pullud_normal_oscar_vtl_vd, audio_es305_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {audio_es305_func_lowpower_oscar_vtl_vd, audio_es305_pullud_lowpower_oscar_vtl_vd, audio_es305_drv_lowpower_oscar_vtl_vd},

};

/*sd pins */
static struct  iomux_pin *sd_pins_oscar_vtl_vd[] = {
    &SD_CLK_OSCAR_VTL_VD, &SD_CMD_OSCAR_VTL_VD, &SD_DATA0_OSCAR_VTL_VD, &SD_DATA1_OSCAR_VTL_VD, &SD_DATA2_OSCAR_VTL_VD, &SD_DATA3_OSCAR_VTL_VD,  NULL,
};

/*define blocks: sd*/
IOMUX_BLOCK(block_sd_oscar_vtl_vd, "block_sd", NORMAL, sd_pins_oscar_vtl_vd)



/*SD*/

static enum lowlayer_func sd_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_normal_oscar_vtl_vd[] = {LEVEL2, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func sd_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0,  -INVALID,};
static enum pull_updown sd_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, NOPULL, NOPULL, NOPULL, NOPULL,  -INVALID,};
static enum drive_strength sd_drv_lowpower_oscar_vtl_vd[] = {LEVEL2, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config sd_config_oscar_vtl_vd[] = {
    [NORMAL] = {sd_func_normal_oscar_vtl_vd, sd_pullud_normal_oscar_vtl_vd, sd_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {sd_func_lowpower_oscar_vtl_vd, sd_pullud_lowpower_oscar_vtl_vd, sd_drv_lowpower_oscar_vtl_vd},

};

/*es305 pins */
static struct  iomux_pin *es305_pins_oscar_vtl_vd[] = {
    &I2S_XCLK_OSCAR_VTL_VD, &I2S_XFS_OSCAR_VTL_VD, &I2S_DI_OSCAR_VTL_VD, &I2S_DO_OSCAR_VTL_VD, &PCM0_XCLK_OSCAR_VTL_VD, &PCM0_XFS_OSCAR_VTL_VD, &PCM0_DI_OSCAR_VTL_VD, &PCM0_DO_OSCAR_VTL_VD, &UART1_TXD_OSCAR_VTL_VD, &TS_ERR_OSCAR_VTL_VD,  NULL,
};

/*define blocks: es305*/
IOMUX_BLOCK(block_es305_oscar_vtl_vd, "block_es305", NORMAL, es305_pins_oscar_vtl_vd)



/*ES305*/

static enum lowlayer_func es305_func_normal_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_normal_oscar_vtl_vd[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_normal_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static enum lowlayer_func es305_func_lowpower_oscar_vtl_vd[] = {FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC0, FUNC2, FUNC1,  -INVALID,};
static enum pull_updown es305_pullud_lowpower_oscar_vtl_vd[] = {NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, NOPULL, PULLDOWN, NOPULL, NOPULL, PULLDOWN,  -INVALID,};
static enum drive_strength es305_drv_lowpower_oscar_vtl_vd[] = {LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0, LEVEL0,  -INVALID,};

static struct block_config es305_config_oscar_vtl_vd[] = {
    [NORMAL] = {es305_func_normal_oscar_vtl_vd, es305_pullud_normal_oscar_vtl_vd, es305_drv_normal_oscar_vtl_vd},
    [LOWPOWER] = {es305_func_lowpower_oscar_vtl_vd, es305_pullud_lowpower_oscar_vtl_vd, es305_drv_lowpower_oscar_vtl_vd},

};

struct iomux_block_table block_config_table_oscar_vtl_vd[] = {
    BLOCK_CONFIG("block_wifi", &block_wifi_oscar_vtl_vd, wifi_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_charger", &block_charger_oscar_vtl_vd, charger_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_flash", &block_flash_oscar_vtl_vd, flash_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_bt", &block_bt_oscar_vtl_vd, bt_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_scamera", &block_scamera_oscar_vtl_vd, scamera_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_codec", &block_codec_oscar_vtl_vd, codec_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_pmu", &block_pmu_oscar_vtl_vd, pmu_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_emmc", &block_emmc_oscar_vtl_vd, emmc_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_odt", &block_odt_oscar_vtl_vd, odt_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_tp", &block_tp_oscar_vtl_vd, tp_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_rf", &block_rf_oscar_vtl_vd, rf_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_rfpmu", &block_rfpmu_oscar_vtl_vd, rfpmu_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_i2c3", &block_i2c3_oscar_vtl_vd, i2c3_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_nfc", &block_nfc_oscar_vtl_vd, nfc_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_usim1", &block_usim1_oscar_vtl_vd, usim1_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_usim0", &block_usim0_oscar_vtl_vd, usim0_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_audio_spk", &block_audio_spk_oscar_vtl_vd, audio_spk_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_mcamera", &block_mcamera_oscar_vtl_vd, mcamera_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_i2c0", &block_i2c0_oscar_vtl_vd, i2c0_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_i2c1", &block_i2c1_oscar_vtl_vd, i2c1_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_i2c2", &block_i2c2_oscar_vtl_vd, i2c2_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_gps", &block_gps_oscar_vtl_vd, gps_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_tcxo", &block_tcxo_oscar_vtl_vd, tcxo_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_rfant", &block_rfant_oscar_vtl_vd, rfant_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_audio_eph", &block_audio_eph_oscar_vtl_vd, audio_eph_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_boot", &block_boot_oscar_vtl_vd, boot_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_lcd", &block_lcd_oscar_vtl_vd, lcd_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_key", &block_key_oscar_vtl_vd, key_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_test", &block_test_oscar_vtl_vd, test_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_audio_es305", &block_audio_es305_oscar_vtl_vd, audio_es305_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_sd", &block_sd_oscar_vtl_vd, sd_config_oscar_vtl_vd)
    BLOCK_CONFIG("block_es305", &block_es305_oscar_vtl_vd, es305_config_oscar_vtl_vd)

    {NULL, NULL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : oscar_vtl_ve_regulator_map.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __OSCAR_VTL_VE_REGULATOR_MAP_H__
#define __OSCAR_VTL_VE_REGULATOR_MAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include  <linux/regulator/machine.h>
#include "regulator_info.h"
#include "drv_regulator_user.h"

static struct regulator_consumer_supply buck1_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(ACPU_CORE0_VDD, NULL),
    REGULATOR_SUPPLY(SCU_VDD, NULL),
    REGULATOR_SUPPLY(ACPU_L2$_MEMORY_PERIPHERAL_VDD, NULL),

};
static struct regulator_consumer_supply buck2_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(G3D_VDD, NULL),

};
static struct regulator_consumer_supply buck3_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDDLV_PLL_VDD, NULL),
    REGULATOR_SUPPLY(DVDD_ABB_VDD, NULL),
    REGULATOR_SUPPLY(DVDD_USB_VDD, NULL),
    REGULATOR_SUPPLY(AVCC_MHL_VDD, NULL),
    REGULATOR_SUPPLY(AVCC_MHLPLL_VDD, NULL),
    REGULATOR_SUPPLY(PERIPHERAL_VDD_VDD, NULL),
    REGULATOR_SUPPLY(DSI_PHY_VDD_VDD, NULL),
    REGULATOR_SUPPLY(CSI_PHY_VDD_VDD, NULL),
    REGULATOR_SUPPLY(DDR_PHY_VDD_VDD, NULL),
    REGULATOR_SUPPLY(DDR_PHY_IO_PRE_DRV_VDD, NULL),
    REGULATOR_SUPPLY(TSENSOR_0P9_VDD, NULL),
    REGULATOR_SUPPLY(HDMI_PHY_DVDD_VDD, NULL),
    REGULATOR_SUPPLY(ABB_AD_DIG_VDD, NULL),
    REGULATOR_SUPPLY(ABB_DA_DIG_VDD, NULL),
    REGULATOR_SUPPLY(VDD_VDD, NULL),

};
static struct regulator_consumer_supply buck4_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(LPDDR2_VDDCA_VDD, NULL),
    REGULATOR_SUPPLY(VDDQ_VDD, NULL),
    REGULATOR_SUPPLY(VDD2_VDD, NULL),
    REGULATOR_SUPPLY(VDD_P2_VDD, NULL),
    REGULATOR_SUPPLY(VIN_LDO_L_VDD, NULL),

};
static struct regulator_consumer_supply buck5_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDD_DDR_VDD, NULL),

};
static struct regulator_consumer_supply buck6_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(LPDDR2_VDD1_VDD, NULL),
    REGULATOR_SUPPLY(LPDDR3_VDD1_VDD, NULL),
    REGULATOR_SUPPLY(VDD_P1_VDD, NULL),
    REGULATOR_SUPPLY(PMU_IO_VDD, NULL),
    REGULATOR_SUPPLY(CODEC_IO_VDD, NULL),
    REGULATOR_SUPPLY(RFIC_DIG_VDD, NULL),
    REGULATOR_SUPPLY(WIFI_IO_VDD, NULL),
    REGULATOR_SUPPLY(BT_IO_VDD, NULL),
    REGULATOR_SUPPLY(GPS_IO_VDD, NULL),
    REGULATOR_SUPPLY(FM_IO_VDD, NULL),
    REGULATOR_SUPPLY(SMARTSPKPA_IO_VDD, NULL),
    REGULATOR_SUPPLY(LVS2_VDD, NULL),
    REGULATOR_SUPPLY(LVS3_VDD, NULL),
    REGULATOR_SUPPLY(LVS4_VDD, NULL),
    REGULATOR_SUPPLY(LVS5_VDD, NULL),
    REGULATOR_SUPPLY(LVS6_VDD, NULL),
    REGULATOR_SUPPLY(LVS7_VDD, NULL),
    REGULATOR_SUPPLY(LVS8_VDD, NULL),
    REGULATOR_SUPPLY(LVS9_VDD, NULL),
    REGULATOR_SUPPLY(LVS10_VDD, NULL),
    REGULATOR_SUPPLY(VIN_LDO_M_VDD, NULL),
    REGULATOR_SUPPLY(USB_ID_MHL_CBUS_SWITCH_VDD, NULL),

};
static struct regulator_consumer_supply boost1_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VIN_LDO_H1_VDD, NULL),
    REGULATOR_SUPPLY(VIN_LDO_H2_VDD, NULL),
    REGULATOR_SUPPLY(VIN_LDO_H3_VDD, NULL),
    REGULATOR_SUPPLY(CLASSD_VDD, NULL),

};
static struct regulator_consumer_supply ldo1_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(HKADC_REF_VDD, NULL),

};
static struct regulator_consumer_supply ldo2_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(TP_ANALOG_VDD, NULL),

};
static struct regulator_consumer_supply ldo3_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDD_ON_VDD, NULL),

};
static struct regulator_consumer_supply ldo4_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(DCXO2_VDD, NULL),

};
static struct regulator_consumer_supply ldo5_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(EMMC_VDDM_VDD, NULL),

};
static struct regulator_consumer_supply ldo6_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(DCXO1_VDD, NULL),

};
static struct regulator_consumer_supply ldo7_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDDH_SDIO_VDD, NULL),

};
static struct regulator_consumer_supply ldo8_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(AVDD13_ABB_VDD, NULL),

};
static struct regulator_consumer_supply ldo9_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(SIM1_VDD, NULL),

};
static struct regulator_consumer_supply ldo10_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(SD_CARD_VDD, NULL),

};
static struct regulator_consumer_supply ldo11_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(SIM2_VDD, NULL),

};
static struct regulator_consumer_supply ldo12_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDD33_USB_VDD, NULL),
    REGULATOR_SUPPLY(MHL_SWITCH_VDD, NULL),

};
static struct regulator_consumer_supply ldo13_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(SENSORS_ANALOG_VDD, NULL),

};
static struct regulator_consumer_supply ldo14_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(S_CAMERA_CORE_VDD, NULL),
    REGULATOR_SUPPLY(S_CAMERA_IO_VDD, NULL),

};
static struct regulator_consumer_supply ldo15_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(M_CAMERA_ANALOG_VDD, NULL),

};
static struct regulator_consumer_supply ldo16_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(M_CAMERA_VCM_VDD, NULL),

};
static struct regulator_consumer_supply ldo17_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(M_CAMERA_CORE_VDD, NULL),

};
static struct regulator_consumer_supply ldo18_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(S_CAMERA_ANALOG_VDD, NULL),

};
static struct regulator_consumer_supply ldo19_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDD_APMEM_VDD, NULL),

};
static struct regulator_consumer_supply ldo20_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VIBRATOR_VDD, NULL),

};
static struct regulator_consumer_supply ldo21_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(S_CAMERA_CORE_FOR_BACKUP2_VDD, NULL),

};
static struct regulator_consumer_supply ldo22_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDDL_SDIO_VDD, NULL),

};
static struct regulator_consumer_supply ldo23_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDDSYS_EFUSE_VDD, NULL),

};
static struct regulator_consumer_supply ldo24_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(PMU_AUXDAC_VDD, NULL),
    REGULATOR_SUPPLY(CODEC_AVDD_VDD, NULL),

};
static struct regulator_consumer_supply lvs2_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(TP_IO_VDD, NULL),

};
static struct regulator_consumer_supply lvs3_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(M_CAMERA_IO_VDD, NULL),

};
static struct regulator_consumer_supply lvs4_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(LCD_IO_VDD, NULL),

};
static struct regulator_consumer_supply lvs5_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(PA_STAR_VDD_VDD, NULL),

};
static struct regulator_consumer_supply lvs6_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(EMMC_VDDQ_VDD, NULL),

};
static struct regulator_consumer_supply lvs7_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(AUDIO_CODEC_ANALOG_1P8V_VDD, NULL),

};
static struct regulator_consumer_supply lvs8_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(SENSOR_IO_VDD, NULL),
    REGULATOR_SUPPLY(NFC_IO_VDD, NULL),

};
static struct regulator_consumer_supply lvs9_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(AVDD_MIPI_DSI_VDD, NULL),
    REGULATOR_SUPPLY(AVDD_MIPI_CSI_VDD, NULL),
    REGULATOR_SUPPLY(AVDD18_ABB_VDD, NULL),
    REGULATOR_SUPPLY(VDDHV_PLL_VDD, NULL),
    REGULATOR_SUPPLY(VDD18_MHL_VDD, NULL),
    REGULATOR_SUPPLY(VDD18_USB_VDD, NULL),
    REGULATOR_SUPPLY(VDD_DDRPLL0_VDD, NULL),
    REGULATOR_SUPPLY(VDD_DDRPLL1_VDD, NULL),
    REGULATOR_SUPPLY(VDD_DDRPLL2_VDD, NULL),
    REGULATOR_SUPPLY(AVDD_TS_VDD, NULL),
    REGULATOR_SUPPLY(VDDM_SDIO_VDD, NULL),

};
static struct regulator_consumer_supply lvs10_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(FLASH_MASK_IO_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos1_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(ACPU_CORE1_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos2_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(ACPU_CORE2_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos3_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(ACPU_CORE3_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos4_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(EDC1_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos5_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(EDC0_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos6_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(G2D_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos7_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(ISP_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos8_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VDEC_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos9_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VPP_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos10_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(VENC_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos11_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(HIFI_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos12_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(BBE16_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos13_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(CCPU_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos14_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(TDWBBP1_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos15_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(TDWBBP2_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos16_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(GBBP1_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos17_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(GBBP2_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos18_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(LTEBBP_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos19_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(BBPCOMM1_VDD, NULL),

};
static struct regulator_consumer_supply mtcmos20_consumers_oscar_vtl_ve[] = {
    REGULATOR_SUPPLY(BBPCOMM2_VDD, NULL),

};
static struct regulator_init_data platform_regulators_oscar_vtl_ve[] = {

    [BUCK1_ID] = {
        .constraints = {
            .name = BUCK1_NAME,
            .min_uV = BUCK1_LEVEL_MIN_VALUE,
            .max_uV = BUCK1_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck1_consumers_oscar_vtl_ve),
        .consumer_supplies = buck1_consumers_oscar_vtl_ve,
    },
    [BUCK2_ID] = {
        .constraints = {
            .name = BUCK2_NAME,
            .min_uV = BUCK2_LEVEL_MIN_VALUE,
            .max_uV = BUCK2_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck2_consumers_oscar_vtl_ve),
        .consumer_supplies = buck2_consumers_oscar_vtl_ve,
    },
    [BUCK3_ID] = {
        .constraints = {
            .name = BUCK3_NAME,
            .min_uV = BUCK3_LEVEL_MIN_VALUE,
            .max_uV = BUCK3_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck3_consumers_oscar_vtl_ve),
        .consumer_supplies = buck3_consumers_oscar_vtl_ve,
    },
    [BUCK4_ID] = {
        .constraints = {
            .name = BUCK4_NAME,
            .min_uV = BUCK4_LEVEL_MIN_VALUE,
            .max_uV = BUCK4_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck4_consumers_oscar_vtl_ve),
        .consumer_supplies = buck4_consumers_oscar_vtl_ve,
    },
    [BUCK5_ID] = {
        .constraints = {
            .name = BUCK5_NAME,
            .min_uV = BUCK5_LEVEL_MIN_VALUE,
            .max_uV = BUCK5_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck5_consumers_oscar_vtl_ve),
        .consumer_supplies = buck5_consumers_oscar_vtl_ve,
    },
    [BUCK6_ID] = {
        .constraints = {
            .name = BUCK6_NAME,
            .min_uV = BUCK6_LEVEL_MIN_VALUE,
            .max_uV = BUCK6_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(buck6_consumers_oscar_vtl_ve),
        .consumer_supplies = buck6_consumers_oscar_vtl_ve,
    },
    [BOOST1_ID] = {
        .constraints = {
            .name = BOOST1_NAME,
            .min_uV = BOOST1_LEVEL_MIN_VALUE,
            .max_uV = BOOST1_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(boost1_consumers_oscar_vtl_ve),
        .consumer_supplies = boost1_consumers_oscar_vtl_ve,
    },
    [LDO1_ID] = {
        .constraints = {
            .name = LDO1_NAME,
            .min_uV = LDO1_LEVEL_MIN_VALUE,
            .max_uV = LDO1_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo1_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo1_consumers_oscar_vtl_ve,
    },
    [LDO2_ID] = {
        .constraints = {
            .name = LDO2_NAME,
            .min_uV = LDO2_LEVEL_MIN_VALUE,
            .max_uV = LDO2_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo2_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo2_consumers_oscar_vtl_ve,
    },
    [LDO3_ID] = {
        .constraints = {
            .name = LDO3_NAME,
            .min_uV = LDO3_LEVEL_MIN_VALUE,
            .max_uV = LDO3_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo3_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo3_consumers_oscar_vtl_ve,
    },
    [LDO4_ID] = {
        .constraints = {
            .name = LDO4_NAME,
            .min_uV = LDO4_LEVEL_MIN_VALUE,
            .max_uV = LDO4_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo4_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo4_consumers_oscar_vtl_ve,
    },
    [LDO5_ID] = {
        .constraints = {
            .name = LDO5_NAME,
            .min_uV = LDO5_LEVEL_MIN_VALUE,
            .max_uV = LDO5_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo5_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo5_consumers_oscar_vtl_ve,
    },
    [LDO6_ID] = {
        .constraints = {
            .name = LDO6_NAME,
            .min_uV = LDO6_LEVEL_MIN_VALUE,
            .max_uV = LDO6_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo6_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo6_consumers_oscar_vtl_ve,
    },
    [LDO7_ID] = {
        .constraints = {
            .name = LDO7_NAME,
            .min_uV = LDO7_LEVEL_MIN_VALUE,
            .max_uV = LDO7_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo7_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo7_consumers_oscar_vtl_ve,
    },
    [LDO8_ID] = {
        .constraints = {
            .name = LDO8_NAME,
            .min_uV = LDO8_LEVEL_MIN_VALUE,
            .max_uV = LDO8_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo8_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo8_consumers_oscar_vtl_ve,
    },
    [LDO9_ID] = {
        .constraints = {
            .name = LDO9_NAME,
            .min_uV = LDO9_LEVEL_MIN_VALUE,
            .max_uV = LDO9_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo9_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo9_consumers_oscar_vtl_ve,
    },
    [LDO10_ID] = {
        .constraints = {
            .name = LDO10_NAME,
            .min_uV = LDO10_LEVEL_MIN_VALUE,
            .max_uV = LDO10_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo10_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo10_consumers_oscar_vtl_ve,
    },
    [LDO11_ID] = {
        .constraints = {
            .name = LDO11_NAME,
            .min_uV = LDO11_LEVEL_MIN_VALUE,
            .max_uV = LDO11_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo11_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo11_consumers_oscar_vtl_ve,
    },
    [LDO12_ID] = {
        .constraints = {
            .name = LDO12_NAME,
            .min_uV = LDO12_LEVEL_MIN_VALUE,
            .max_uV = LDO12_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo12_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo12_consumers_oscar_vtl_ve,
    },
    [LDO13_ID] = {
        .constraints = {
            .name = LDO13_NAME,
            .min_uV = LDO13_LEVEL_MIN_VALUE,
            .max_uV = LDO13_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo13_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo13_consumers_oscar_vtl_ve,
    },
    [LDO14_ID] = {
        .constraints = {
            .name = LDO14_NAME,
            .min_uV = LDO14_LEVEL_MIN_VALUE,
            .max_uV = LDO14_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo14_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo14_consumers_oscar_vtl_ve,
    },
    [LDO15_ID] = {
        .constraints = {
            .name = LDO15_NAME,
            .min_uV = LDO15_LEVEL_MIN_VALUE,
            .max_uV = LDO15_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo15_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo15_consumers_oscar_vtl_ve,
    },
    [LDO16_ID] = {
        .constraints = {
            .name = LDO16_NAME,
            .min_uV = LDO16_LEVEL_MIN_VALUE,
            .max_uV = LDO16_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo16_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo16_consumers_oscar_vtl_ve,
    },
    [LDO17_ID] = {
        .constraints = {
            .name = LDO17_NAME,
            .min_uV = LDO17_LEVEL_MIN_VALUE,
            .max_uV = LDO17_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo17_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo17_consumers_oscar_vtl_ve,
    },
    [LDO18_ID] = {
        .constraints = {
            .name = LDO18_NAME,
            .min_uV = LDO18_LEVEL_MIN_VALUE,
            .max_uV = LDO18_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo18_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo18_consumers_oscar_vtl_ve,
    },
    [LDO19_ID] = {
        .constraints = {
            .name = LDO19_NAME,
            .min_uV = LDO19_LEVEL_MIN_VALUE,
            .max_uV = LDO19_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo19_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo19_consumers_oscar_vtl_ve,
    },
    [LDO20_ID] = {
        .constraints = {
            .name = LDO20_NAME,
            .min_uV = LDO20_LEVEL_MIN_VALUE,
            .max_uV = LDO20_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo20_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo20_consumers_oscar_vtl_ve,
    },
    [LDO21_ID] = {
        .constraints = {
            .name = LDO21_NAME,
            .min_uV = LDO21_LEVEL_MIN_VALUE,
            .max_uV = LDO21_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo21_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo21_consumers_oscar_vtl_ve,
    },
    [LDO22_ID] = {
        .constraints = {
            .name = LDO22_NAME,
            .min_uV = LDO22_LEVEL_MIN_VALUE,
            .max_uV = LDO22_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo22_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo22_consumers_oscar_vtl_ve,
    },
    [LDO23_ID] = {
        .constraints = {
            .name = LDO23_NAME,
            .min_uV = LDO23_LEVEL_MIN_VALUE,
            .max_uV = LDO23_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo23_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo23_consumers_oscar_vtl_ve,
    },
    [LDO24_ID] = {
        .constraints = {
            .name = LDO24_NAME,
            .min_uV = LDO24_LEVEL_MIN_VALUE,
            .max_uV = LDO24_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(ldo24_consumers_oscar_vtl_ve),
        .consumer_supplies = ldo24_consumers_oscar_vtl_ve,
    },
    [LVS2_ID] = {
        .constraints = {
            .name = LVS2_NAME,
            .min_uV = LVS2_LEVEL_MIN_VALUE,
            .max_uV = LVS2_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs2_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs2_consumers_oscar_vtl_ve,
    },
    [LVS3_ID] = {
        .constraints = {
            .name = LVS3_NAME,
            .min_uV = LVS3_LEVEL_MIN_VALUE,
            .max_uV = LVS3_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs3_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs3_consumers_oscar_vtl_ve,
    },
    [LVS4_ID] = {
        .constraints = {
            .name = LVS4_NAME,
            .min_uV = LVS4_LEVEL_MIN_VALUE,
            .max_uV = LVS4_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs4_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs4_consumers_oscar_vtl_ve,
    },
    [LVS5_ID] = {
        .constraints = {
            .name = LVS5_NAME,
            .min_uV = LVS5_LEVEL_MIN_VALUE,
            .max_uV = LVS5_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs5_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs5_consumers_oscar_vtl_ve,
    },
    [LVS6_ID] = {
        .constraints = {
            .name = LVS6_NAME,
            .min_uV = LVS6_LEVEL_MIN_VALUE,
            .max_uV = LVS6_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs6_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs6_consumers_oscar_vtl_ve,
    },
    [LVS7_ID] = {
        .constraints = {
            .name = LVS7_NAME,
            .min_uV = LVS7_LEVEL_MIN_VALUE,
            .max_uV = LVS7_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs7_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs7_consumers_oscar_vtl_ve,
    },
    [LVS8_ID] = {
        .constraints = {
            .name = LVS8_NAME,
            .min_uV = LVS8_LEVEL_MIN_VALUE,
            .max_uV = LVS8_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs8_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs8_consumers_oscar_vtl_ve,
    },
    [LVS9_ID] = {
        .constraints = {
            .name = LVS9_NAME,
            .min_uV = LVS9_LEVEL_MIN_VALUE,
            .max_uV = LVS9_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs9_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs9_consumers_oscar_vtl_ve,
    },
    [LVS10_ID] = {
        .constraints = {
            .name = LVS10_NAME,
            .min_uV = LVS10_LEVEL_MIN_VALUE,
            .max_uV = LVS10_LEVEL_MAX_VALUE,
            .valid_modes_mask =  REGULATOR_MODE_NORMAL,
            .valid_ops_mask = REGULATOR_CHANGE_VOLTAGE | REGULATOR_CHANGE_STATUS
                | REGULATOR_CHANGE_MODE | REGULATOR_CHANGE_DRMS,
            .initial_mode = REGULATOR_MODE_NORMAL,
            .always_on = 1,
        },
        .num_consumer_supplies = ARRAY_SIZE(lvs10_consumers_oscar_vtl_ve),
        .consumer_supplies = lvs10_consumers_oscar_vtl_ve,
    },
    [MTCMOS1_ID] = {
        .constraints = {
            .name = MTCMOS1_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos1_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos1_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK1_NAME,
    },
    [MTCMOS2_ID] = {
        .constraints = {
            .name = MTCMOS2_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos2_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos2_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK1_NAME,
    },
    [MTCMOS3_ID] = {
        .constraints = {
            .name = MTCMOS3_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos3_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos3_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK1_NAME,
    },
    [MTCMOS4_ID] = {
        .constraints = {
            .name = MTCMOS4_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos4_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos4_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS5_ID] = {
        .constraints = {
            .name = MTCMOS5_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos5_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos5_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS6_ID] = {
        .constraints = {
            .name = MTCMOS6_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos6_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos6_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS7_ID] = {
        .constraints = {
            .name = MTCMOS7_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos7_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos7_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS8_ID] = {
        .constraints = {
            .name = MTCMOS8_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos8_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos8_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS9_ID] = {
        .constraints = {
            .name = MTCMOS9_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos9_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos9_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS10_ID] = {
        .constraints = {
            .name = MTCMOS10_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos10_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos10_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS11_ID] = {
        .constraints = {
            .name = MTCMOS11_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos11_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos11_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS12_ID] = {
        .constraints = {
            .name = MTCMOS12_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos12_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos12_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS13_ID] = {
        .constraints = {
            .name = MTCMOS13_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos13_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos13_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS14_ID] = {
        .constraints = {
            .name = MTCMOS14_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos14_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos14_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS15_ID] = {
        .constraints = {
            .name = MTCMOS15_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos15_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos15_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS16_ID] = {
        .constraints = {
            .name = MTCMOS16_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos16_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos16_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS17_ID] = {
        .constraints = {
            .name = MTCMOS17_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos17_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos17_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS18_ID] = {
        .constraints = {
            .name = MTCMOS18_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos18_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos18_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS19_ID] = {
        .constraints = {
            .name = MTCMOS19_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos19_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos19_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    [MTCMOS20_ID] = {
        .constraints = {
            .name = MTCMOS20_NAME,
            .valid_ops_mask = REGULATOR_CHANGE_STATUS,
            .always_on = 0,
        },
        .num_consumer_supplies = ARRAY_SIZE(mtcmos20_consumers_oscar_vtl_ve),
        .consumer_supplies = mtcmos20_consumers_oscar_vtl_ve,
        .supply_regulator = BUCK3_NAME,
    },
    NULL,
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

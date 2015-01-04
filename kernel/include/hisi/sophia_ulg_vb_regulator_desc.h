/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : sophia_ulg_vb_regulator_desc.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __SOPHIA_ULG_VB_REGULATOR_DESC_H__
#define __SOPHIA_ULG_VB_REGULATOR_DESC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include  <hisi/regulator_pmic.h>
#include  <hisi/regulator_mtcmos.h>
#include  <linux/regulator/driver.h>
#include  "regulator_info.h"

static struct regulator_desc regulators_sophia_ulg_vb[] = {
    [BUCK1_ID] = {
        .name = BUCK1_NAME,
        .id = BUCK1_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK1_LEVEL_SUPPORT_NUM,
        .type = BUCK1_TYPE,
        .owner = THIS_MODULE,
    },
    [BUCK2_ID] = {
        .name = BUCK2_NAME,
        .id = BUCK2_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK2_LEVEL_SUPPORT_NUM,
        .type = BUCK2_TYPE,
        .owner = THIS_MODULE,
    },
    [BUCK3_ID] = {
        .name = BUCK3_NAME,
        .id = BUCK3_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK3_LEVEL_SUPPORT_NUM,
        .type = BUCK3_TYPE,
        .owner = THIS_MODULE,
    },
    [BUCK4_ID] = {
        .name = BUCK4_NAME,
        .id = BUCK4_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK4_LEVEL_SUPPORT_NUM,
        .type = BUCK4_TYPE,
        .owner = THIS_MODULE,
    },
    [BUCK5_ID] = {
        .name = BUCK5_NAME,
        .id = BUCK5_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK5_LEVEL_SUPPORT_NUM,
        .type = BUCK5_TYPE,
        .owner = THIS_MODULE,
    },
    [BUCK6_ID] = {
        .name = BUCK6_NAME,
        .id = BUCK6_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BUCK6_LEVEL_SUPPORT_NUM,
        .type = BUCK6_TYPE,
        .owner = THIS_MODULE,
    },
    [BOOST1_ID] = {
        .name = BOOST1_NAME,
        .id = BOOST1_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = BOOST1_LEVEL_SUPPORT_NUM,
        .type = BOOST1_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO1_ID] = {
        .name = LDO1_NAME,
        .id = LDO1_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO1_LEVEL_SUPPORT_NUM,
        .type = LDO1_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO2_ID] = {
        .name = LDO2_NAME,
        .id = LDO2_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO2_LEVEL_SUPPORT_NUM,
        .type = LDO2_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO3_ID] = {
        .name = LDO3_NAME,
        .id = LDO3_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO3_LEVEL_SUPPORT_NUM,
        .type = LDO3_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO4_ID] = {
        .name = LDO4_NAME,
        .id = LDO4_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO4_LEVEL_SUPPORT_NUM,
        .type = LDO4_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO5_ID] = {
        .name = LDO5_NAME,
        .id = LDO5_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO5_LEVEL_SUPPORT_NUM,
        .type = LDO5_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO6_ID] = {
        .name = LDO6_NAME,
        .id = LDO6_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO6_LEVEL_SUPPORT_NUM,
        .type = LDO6_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO7_ID] = {
        .name = LDO7_NAME,
        .id = LDO7_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO7_LEVEL_SUPPORT_NUM,
        .type = LDO7_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO8_ID] = {
        .name = LDO8_NAME,
        .id = LDO8_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO8_LEVEL_SUPPORT_NUM,
        .type = LDO8_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO9_ID] = {
        .name = LDO9_NAME,
        .id = LDO9_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO9_LEVEL_SUPPORT_NUM,
        .type = LDO9_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO10_ID] = {
        .name = LDO10_NAME,
        .id = LDO10_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO10_LEVEL_SUPPORT_NUM,
        .type = LDO10_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO11_ID] = {
        .name = LDO11_NAME,
        .id = LDO11_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO11_LEVEL_SUPPORT_NUM,
        .type = LDO11_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO12_ID] = {
        .name = LDO12_NAME,
        .id = LDO12_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO12_LEVEL_SUPPORT_NUM,
        .type = LDO12_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO13_ID] = {
        .name = LDO13_NAME,
        .id = LDO13_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO13_LEVEL_SUPPORT_NUM,
        .type = LDO13_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO14_ID] = {
        .name = LDO14_NAME,
        .id = LDO14_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO14_LEVEL_SUPPORT_NUM,
        .type = LDO14_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO15_ID] = {
        .name = LDO15_NAME,
        .id = LDO15_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO15_LEVEL_SUPPORT_NUM,
        .type = LDO15_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO16_ID] = {
        .name = LDO16_NAME,
        .id = LDO16_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO16_LEVEL_SUPPORT_NUM,
        .type = LDO16_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO17_ID] = {
        .name = LDO17_NAME,
        .id = LDO17_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO17_LEVEL_SUPPORT_NUM,
        .type = LDO17_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO18_ID] = {
        .name = LDO18_NAME,
        .id = LDO18_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO18_LEVEL_SUPPORT_NUM,
        .type = LDO18_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO19_ID] = {
        .name = LDO19_NAME,
        .id = LDO19_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO19_LEVEL_SUPPORT_NUM,
        .type = LDO19_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO20_ID] = {
        .name = LDO20_NAME,
        .id = LDO20_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO20_LEVEL_SUPPORT_NUM,
        .type = LDO20_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO21_ID] = {
        .name = LDO21_NAME,
        .id = LDO21_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO21_LEVEL_SUPPORT_NUM,
        .type = LDO21_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO22_ID] = {
        .name = LDO22_NAME,
        .id = LDO22_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO22_LEVEL_SUPPORT_NUM,
        .type = LDO22_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO23_ID] = {
        .name = LDO23_NAME,
        .id = LDO23_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO23_LEVEL_SUPPORT_NUM,
        .type = LDO23_TYPE,
        .owner = THIS_MODULE,
    },
    [LDO24_ID] = {
        .name = LDO24_NAME,
        .id = LDO24_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LDO24_LEVEL_SUPPORT_NUM,
        .type = LDO24_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS2_ID] = {
        .name = LVS2_NAME,
        .id = LVS2_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS2_LEVEL_SUPPORT_NUM,
        .type = LVS2_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS3_ID] = {
        .name = LVS3_NAME,
        .id = LVS3_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS3_LEVEL_SUPPORT_NUM,
        .type = LVS3_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS4_ID] = {
        .name = LVS4_NAME,
        .id = LVS4_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS4_LEVEL_SUPPORT_NUM,
        .type = LVS4_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS5_ID] = {
        .name = LVS5_NAME,
        .id = LVS5_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS5_LEVEL_SUPPORT_NUM,
        .type = LVS5_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS6_ID] = {
        .name = LVS6_NAME,
        .id = LVS6_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS6_LEVEL_SUPPORT_NUM,
        .type = LVS6_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS7_ID] = {
        .name = LVS7_NAME,
        .id = LVS7_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS7_LEVEL_SUPPORT_NUM,
        .type = LVS7_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS8_ID] = {
        .name = LVS8_NAME,
        .id = LVS8_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS8_LEVEL_SUPPORT_NUM,
        .type = LVS8_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS9_ID] = {
        .name = LVS9_NAME,
        .id = LVS9_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS9_LEVEL_SUPPORT_NUM,
        .type = LVS9_TYPE,
        .owner = THIS_MODULE,
    },
    [LVS10_ID] = {
        .name = LVS10_NAME,
        .id = LVS10_ID,
        .ops = &regulator_pmic_ops,
        .n_voltages = LVS10_LEVEL_SUPPORT_NUM,
        .type = LVS10_TYPE,
        .owner = THIS_MODULE,
    },
    [MTCMOS1_ID] = {
        .name = MTCMOS1_NAME,
        .id = MTCMOS1_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS1_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS2_ID] = {
        .name = MTCMOS2_NAME,
        .id = MTCMOS2_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS2_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS3_ID] = {
        .name = MTCMOS3_NAME,
        .id = MTCMOS3_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS3_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS4_ID] = {
        .name = MTCMOS4_NAME,
        .id = MTCMOS4_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS4_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS5_ID] = {
        .name = MTCMOS5_NAME,
        .id = MTCMOS5_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS5_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS6_ID] = {
        .name = MTCMOS6_NAME,
        .id = MTCMOS6_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS6_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS7_ID] = {
        .name = MTCMOS7_NAME,
        .id = MTCMOS7_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS7_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS8_ID] = {
        .name = MTCMOS8_NAME,
        .id = MTCMOS8_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS8_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS9_ID] = {
        .name = MTCMOS9_NAME,
        .id = MTCMOS9_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS9_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS10_ID] = {
        .name = MTCMOS10_NAME,
        .id = MTCMOS10_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS10_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS11_ID] = {
        .name = MTCMOS11_NAME,
        .id = MTCMOS11_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS11_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS12_ID] = {
        .name = MTCMOS12_NAME,
        .id = MTCMOS12_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS12_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS13_ID] = {
        .name = MTCMOS13_NAME,
        .id = MTCMOS13_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS13_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS14_ID] = {
        .name = MTCMOS14_NAME,
        .id = MTCMOS14_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS14_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS15_ID] = {
        .name = MTCMOS15_NAME,
        .id = MTCMOS15_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS15_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS16_ID] = {
        .name = MTCMOS16_NAME,
        .id = MTCMOS16_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS16_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS17_ID] = {
        .name = MTCMOS17_NAME,
        .id = MTCMOS17_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS17_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS18_ID] = {
        .name = MTCMOS18_NAME,
        .id = MTCMOS18_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS18_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS19_ID] = {
        .name = MTCMOS19_NAME,
        .id = MTCMOS19_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS19_TYPE,
        .owner = THIS_MODULE,
},
    [MTCMOS20_ID] = {
        .name = MTCMOS20_NAME,
        .id = MTCMOS20_ID,
        .ops = &regulator_mtcmos_ops,
        .type = MTCMOS20_TYPE,
        .owner = THIS_MODULE,
},

};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

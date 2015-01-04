/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : regulator_map.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __REGULATOR_MAP_H__
#define __REGULATOR_MAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "balong_lpddr2_udp_regulator_desc.h"
#include "balong_lpddr2_udp_dcm_rf_regulator_desc.h"
#include "balong_lpddr2_udp_6361s_regulator_desc.h"
#include "balong_lpddr2_udp_oscar_rf_regulator_desc.h"
#include "balong_ddr3cap_udp_regulator_desc.h"
#include "balong_ddr3cap_udp_dcm_rf_regulator_desc.h"
#include "balong_ddr3cap_udp_6361s_regulator_desc.h"
#include "balong_mhlcap_udp_regulator_desc.h"
#include "balong_mhl_udp_regulator_desc.h"
#include "balong_lpddr3_udp_regulator_desc.h"
#include "balong_lpddr3_udp_dcm_rf_regulator_desc.h"
#include "balong_lpddr3_udp_6361s_regulator_desc.h"
#include "balong_mhlcap_udp_fhd_regulator_desc.h"
#include "balong_ddr3cap_udp_fhd_regulator_desc.h"
#include "edge_plus_ul_va_regulator_desc.h"
#include "oscar_cg_va_regulator_desc.h"
#include "oscar_tl_va_regulator_desc.h"
#include "oscar_ul_va_regulator_desc.h"
#include "oscar_cg_vb_regulator_desc.h"
#include "oscar_cg_vc_regulator_desc.h"
#include "oscar_cg_vd_regulator_desc.h"
#include "edge_plus_ul_vb_regulator_desc.h"
#include "edge_plus_ul_vx_regulator_desc.h"
#include "edge_plus_ul_vy_regulator_desc.h"
#include "oscar_ul_vb_regulator_desc.h"
#include "oscar_4g_vc_regulator_desc.h"
#include "oscar_tl_vb_regulator_desc.h"
#include "oscar_4g_vd_regulator_desc.h"
#include "oscar_vul_vd_regulator_desc.h"
#include "oscar_vtl_vd_regulator_desc.h"
#include "oscar_4g_ve_regulator_desc.h"
#include "oscar_vul_ve_regulator_desc.h"
#include "oscar_vtl_ve_regulator_desc.h"
#include "edge_plus_ul_vz_regulator_desc.h"
#include "sophia_ul_va_regulator_desc.h"
#include "sophia_ul_vb_regulator_desc.h"
#include "sophia_ul_vc_regulator_desc.h"
#include "sophia_ul_vd_regulator_desc.h"
#include "sophia_ul_vy_regulator_desc.h"
#include "sophia_tl_va_regulator_desc.h"
#include "sophia_tl_vb_regulator_desc.h"
#include "sophia_tl_vc_regulator_desc.h"
#include "sophia_tl_vd_regulator_desc.h"
#include "sophia_ulg_va_regulator_desc.h"
#include "sophia_ulg_vb_regulator_desc.h"
#include "sophia_ulg_vc_regulator_desc.h"
#include "sophia_ulg_vd_regulator_desc.h"
#include "sophia_ulg_hva_regulator_desc.h"
#include "sophia_clg_va_regulator_desc.h"
#include "sophia_clg_vb_regulator_desc.h"
#include "sophia_ul_vu_regulator_desc.h"
#include "balong_lpddr2_udp_regulator_map.h"
#include "balong_lpddr2_udp_dcm_rf_regulator_map.h"
#include "balong_lpddr2_udp_6361s_regulator_map.h"
#include "balong_lpddr2_udp_oscar_rf_regulator_map.h"
#include "balong_ddr3cap_udp_regulator_map.h"
#include "balong_ddr3cap_udp_dcm_rf_regulator_map.h"
#include "balong_ddr3cap_udp_6361s_regulator_map.h"
#include "balong_mhlcap_udp_regulator_map.h"
#include "balong_mhl_udp_regulator_map.h"
#include "balong_lpddr3_udp_regulator_map.h"
#include "balong_lpddr3_udp_dcm_rf_regulator_map.h"
#include "balong_lpddr3_udp_6361s_regulator_map.h"
#include "balong_mhlcap_udp_fhd_regulator_map.h"
#include "balong_ddr3cap_udp_fhd_regulator_map.h"
#include "edge_plus_ul_va_regulator_map.h"
#include "oscar_cg_va_regulator_map.h"
#include "oscar_tl_va_regulator_map.h"
#include "oscar_ul_va_regulator_map.h"
#include "oscar_cg_vb_regulator_map.h"
#include "oscar_cg_vc_regulator_map.h"
#include "oscar_cg_vd_regulator_map.h"
#include "edge_plus_ul_vb_regulator_map.h"
#include "edge_plus_ul_vx_regulator_map.h"
#include "edge_plus_ul_vy_regulator_map.h"
#include "oscar_ul_vb_regulator_map.h"
#include "oscar_4g_vc_regulator_map.h"
#include "oscar_tl_vb_regulator_map.h"
#include "oscar_4g_vd_regulator_map.h"
#include "oscar_vul_vd_regulator_map.h"
#include "oscar_vtl_vd_regulator_map.h"
#include "oscar_4g_ve_regulator_map.h"
#include "oscar_vul_ve_regulator_map.h"
#include "oscar_vtl_ve_regulator_map.h"
#include "edge_plus_ul_vz_regulator_map.h"
#include "sophia_ul_va_regulator_map.h"
#include "sophia_ul_vb_regulator_map.h"
#include "sophia_ul_vc_regulator_map.h"
#include "sophia_ul_vd_regulator_map.h"
#include "sophia_ul_vy_regulator_map.h"
#include "sophia_tl_va_regulator_map.h"
#include "sophia_tl_vb_regulator_map.h"
#include "sophia_tl_vc_regulator_map.h"
#include "sophia_tl_vd_regulator_map.h"
#include "sophia_ulg_va_regulator_map.h"
#include "sophia_ulg_vb_regulator_map.h"
#include "sophia_ulg_vc_regulator_map.h"
#include "sophia_ulg_vd_regulator_map.h"
#include "sophia_ulg_hva_regulator_map.h"
#include "sophia_clg_va_regulator_map.h"
#include "sophia_clg_vb_regulator_map.h"
#include "sophia_ul_vu_regulator_map.h"

#define REGULATOR_CONFIG_PLAT_TBL_END_SYMBOL     (-1)

struct regulator_config_platform_table {
    unsigned int board_id;
    struct regulator_init_data *table;
};

struct regulator_config_platform_table platform_regulators_total[] = {
    {0, platform_regulators_balong_lpddr2_udp},
    {1, platform_regulators_balong_lpddr2_udp_dcm_rf},
    {2, platform_regulators_balong_lpddr2_udp_6361s},
    {9, platform_regulators_balong_lpddr2_udp_oscar_rf},
    {10, platform_regulators_balong_ddr3cap_udp},
    {11, platform_regulators_balong_ddr3cap_udp_dcm_rf},
    {12, platform_regulators_balong_ddr3cap_udp_6361s},
    {20, platform_regulators_balong_mhlcap_udp},
    {30, platform_regulators_balong_mhl_udp},
    {40, platform_regulators_balong_lpddr3_udp},
    {41, platform_regulators_balong_lpddr3_udp_dcm_rf},
    {42, platform_regulators_balong_lpddr3_udp_6361s},
    {96, platform_regulators_balong_mhlcap_udp_fhd},
    {97, platform_regulators_balong_ddr3cap_udp_fhd},
    {701, platform_regulators_edge_plus_ul_va},
    {712, platform_regulators_oscar_cg_va},
    {715, platform_regulators_oscar_tl_va},
    {716, platform_regulators_oscar_ul_va},
    {732, platform_regulators_oscar_cg_vb},
    {734, platform_regulators_oscar_cg_vc},
    {735, platform_regulators_oscar_cg_vd},
    {750, platform_regulators_edge_plus_ul_vb},
    {758, platform_regulators_edge_plus_ul_vx},
    {759, platform_regulators_edge_plus_ul_vy},
    {760, platform_regulators_oscar_ul_vb},
    {761, platform_regulators_oscar_4g_vc},
    {770, platform_regulators_oscar_tl_vb},
    {771, platform_regulators_oscar_4g_vd},
    {772, platform_regulators_oscar_vul_vd},
    {774, platform_regulators_oscar_vtl_vd},
    {781, platform_regulators_oscar_4g_ve},
    {782, platform_regulators_oscar_vul_ve},
    {784, platform_regulators_oscar_vtl_ve},
    {790, platform_regulators_edge_plus_ul_vz},
    {800, platform_regulators_sophia_ul_va},
    {801, platform_regulators_sophia_ul_vb},
    {802, platform_regulators_sophia_ul_vc},
    {803, platform_regulators_sophia_ul_vd},
    {810, platform_regulators_sophia_ul_vy},
    {820, platform_regulators_sophia_tl_va},
    {821, platform_regulators_sophia_tl_vb},
    {822, platform_regulators_sophia_tl_vc},
    {823, platform_regulators_sophia_tl_vd},
    {830, platform_regulators_sophia_ulg_va},
    {831, platform_regulators_sophia_ulg_vb},
    {832, platform_regulators_sophia_ulg_vc},
    {833, platform_regulators_sophia_ulg_vd},
    {835, platform_regulators_sophia_ulg_hva},
    {840, platform_regulators_sophia_clg_va},
    {841, platform_regulators_sophia_clg_vb},
    {860, platform_regulators_sophia_ul_vu},

    {REGULATOR_CONFIG_PLAT_TBL_END_SYMBOL, NULL}
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

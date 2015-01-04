/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 
  文 件 名   : hi6620_iomux.h
  生成日期   : 2014年5月7日
  
******************************************************************************/


#ifndef __HI6620_IOMUX_H__
#define __HI6620_IOMUX_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "hi6620_balong_lpddr2_udp_iomux_blocks.h"
#include "hi6620_balong_lpddr2_udp_iomux_pins.h"
#include "hi6620_balong_lpddr2_udp_dcm_rf_iomux_blocks.h"
#include "hi6620_balong_lpddr2_udp_dcm_rf_iomux_pins.h"
#include "hi6620_balong_lpddr2_udp_6361s_iomux_blocks.h"
#include "hi6620_balong_lpddr2_udp_6361s_iomux_pins.h"
#include "hi6620_balong_lpddr2_udp_oscar_rf_iomux_blocks.h"
#include "hi6620_balong_lpddr2_udp_oscar_rf_iomux_pins.h"
#include "hi6620_balong_ddr3cap_udp_iomux_blocks.h"
#include "hi6620_balong_ddr3cap_udp_iomux_pins.h"
#include "hi6620_balong_ddr3cap_udp_dcm_rf_iomux_blocks.h"
#include "hi6620_balong_ddr3cap_udp_dcm_rf_iomux_pins.h"
#include "hi6620_balong_ddr3cap_udp_6361s_iomux_blocks.h"
#include "hi6620_balong_ddr3cap_udp_6361s_iomux_pins.h"
#include "hi6620_balong_mhlcap_udp_iomux_blocks.h"
#include "hi6620_balong_mhlcap_udp_iomux_pins.h"
#include "hi6620_balong_mhl_udp_iomux_blocks.h"
#include "hi6620_balong_mhl_udp_iomux_pins.h"
#include "hi6620_balong_lpddr3_udp_iomux_blocks.h"
#include "hi6620_balong_lpddr3_udp_iomux_pins.h"
#include "hi6620_balong_lpddr3_udp_dcm_rf_iomux_blocks.h"
#include "hi6620_balong_lpddr3_udp_dcm_rf_iomux_pins.h"
#include "hi6620_balong_lpddr3_udp_6361s_iomux_blocks.h"
#include "hi6620_balong_lpddr3_udp_6361s_iomux_pins.h"
#include "hi6620_balong_mhlcap_udp_fhd_iomux_blocks.h"
#include "hi6620_balong_mhlcap_udp_fhd_iomux_pins.h"
#include "hi6620_balong_ddr3cap_udp_fhd_iomux_blocks.h"
#include "hi6620_balong_ddr3cap_udp_fhd_iomux_pins.h"
#include "hi6620_edge_plus_ul_va_iomux_blocks.h"
#include "hi6620_edge_plus_ul_va_iomux_pins.h"
#include "hi6620_oscar_cg_va_iomux_blocks.h"
#include "hi6620_oscar_cg_va_iomux_pins.h"
#include "hi6620_oscar_tl_va_iomux_blocks.h"
#include "hi6620_oscar_tl_va_iomux_pins.h"
#include "hi6620_oscar_ul_va_iomux_blocks.h"
#include "hi6620_oscar_ul_va_iomux_pins.h"
#include "hi6620_oscar_cg_vb_iomux_blocks.h"
#include "hi6620_oscar_cg_vb_iomux_pins.h"
#include "hi6620_oscar_cg_vc_iomux_blocks.h"
#include "hi6620_oscar_cg_vc_iomux_pins.h"
#include "hi6620_oscar_cg_vd_iomux_blocks.h"
#include "hi6620_oscar_cg_vd_iomux_pins.h"
#include "hi6620_edge_plus_ul_vb_iomux_blocks.h"
#include "hi6620_edge_plus_ul_vb_iomux_pins.h"
#include "hi6620_edge_plus_ul_vx_iomux_blocks.h"
#include "hi6620_edge_plus_ul_vx_iomux_pins.h"
#include "hi6620_edge_plus_ul_vy_iomux_blocks.h"
#include "hi6620_edge_plus_ul_vy_iomux_pins.h"
#include "hi6620_oscar_ul_vb_iomux_blocks.h"
#include "hi6620_oscar_ul_vb_iomux_pins.h"
#include "hi6620_oscar_4g_vc_iomux_blocks.h"
#include "hi6620_oscar_4g_vc_iomux_pins.h"
#include "hi6620_oscar_tl_vb_iomux_blocks.h"
#include "hi6620_oscar_tl_vb_iomux_pins.h"
#include "hi6620_oscar_4g_vd_iomux_blocks.h"
#include "hi6620_oscar_4g_vd_iomux_pins.h"
#include "hi6620_oscar_vul_vd_iomux_blocks.h"
#include "hi6620_oscar_vul_vd_iomux_pins.h"
#include "hi6620_oscar_vtl_vd_iomux_blocks.h"
#include "hi6620_oscar_vtl_vd_iomux_pins.h"
#include "hi6620_oscar_4g_ve_iomux_blocks.h"
#include "hi6620_oscar_4g_ve_iomux_pins.h"
#include "hi6620_oscar_vul_ve_iomux_blocks.h"
#include "hi6620_oscar_vul_ve_iomux_pins.h"
#include "hi6620_oscar_vtl_ve_iomux_blocks.h"
#include "hi6620_oscar_vtl_ve_iomux_pins.h"
#include "hi6620_edge_plus_ul_vz_iomux_blocks.h"
#include "hi6620_edge_plus_ul_vz_iomux_pins.h"
#include "hi6620_sophia_ul_va_iomux_blocks.h"
#include "hi6620_sophia_ul_va_iomux_pins.h"
#include "hi6620_sophia_ul_vb_iomux_blocks.h"
#include "hi6620_sophia_ul_vb_iomux_pins.h"
#include "hi6620_sophia_ul_vc_iomux_blocks.h"
#include "hi6620_sophia_ul_vc_iomux_pins.h"
#include "hi6620_sophia_ul_vd_iomux_blocks.h"
#include "hi6620_sophia_ul_vd_iomux_pins.h"
#include "hi6620_sophia_ul_vy_iomux_blocks.h"
#include "hi6620_sophia_ul_vy_iomux_pins.h"
#include "hi6620_sophia_tl_va_iomux_blocks.h"
#include "hi6620_sophia_tl_va_iomux_pins.h"
#include "hi6620_sophia_tl_vb_iomux_blocks.h"
#include "hi6620_sophia_tl_vb_iomux_pins.h"
#include "hi6620_sophia_tl_vc_iomux_blocks.h"
#include "hi6620_sophia_tl_vc_iomux_pins.h"
#include "hi6620_sophia_tl_vd_iomux_blocks.h"
#include "hi6620_sophia_tl_vd_iomux_pins.h"
#include "hi6620_sophia_ulg_va_iomux_blocks.h"
#include "hi6620_sophia_ulg_va_iomux_pins.h"
#include "hi6620_sophia_ulg_vb_iomux_blocks.h"
#include "hi6620_sophia_ulg_vb_iomux_pins.h"
#include "hi6620_sophia_ulg_vc_iomux_blocks.h"
#include "hi6620_sophia_ulg_vc_iomux_pins.h"
#include "hi6620_sophia_ulg_vd_iomux_blocks.h"
#include "hi6620_sophia_ulg_vd_iomux_pins.h"
#include "hi6620_sophia_ulg_hva_iomux_blocks.h"
#include "hi6620_sophia_ulg_hva_iomux_pins.h"
#include "hi6620_sophia_clg_va_iomux_blocks.h"
#include "hi6620_sophia_clg_va_iomux_pins.h"
#include "hi6620_sophia_clg_vb_iomux_blocks.h"
#include "hi6620_sophia_clg_vb_iomux_pins.h"
#include "hi6620_sophia_ul_vu_iomux_blocks.h"
#include "hi6620_sophia_ul_vu_iomux_pins.h"

#define IOMUX_CONFIG_TBL_END_SYMBOL     (-1)

struct iomux_config_table {
    unsigned int board_id;
    void *table_item;
};

struct iomux_config_table block_config_tables[] = {
    {0, block_config_table_balong_lpddr2_udp},
    {1, block_config_table_balong_lpddr2_udp_dcm_rf},
    {2, block_config_table_balong_lpddr2_udp_6361s},
    {9, block_config_table_balong_lpddr2_udp_oscar_rf},
    {10, block_config_table_balong_ddr3cap_udp},
    {11, block_config_table_balong_ddr3cap_udp_dcm_rf},
    {12, block_config_table_balong_ddr3cap_udp_6361s},
    {20, block_config_table_balong_mhlcap_udp},
    {30, block_config_table_balong_mhl_udp},
    {40, block_config_table_balong_lpddr3_udp},
    {41, block_config_table_balong_lpddr3_udp_dcm_rf},
    {42, block_config_table_balong_lpddr3_udp_6361s},
    {96, block_config_table_balong_mhlcap_udp_fhd},
    {97, block_config_table_balong_ddr3cap_udp_fhd},
    {701, block_config_table_edge_plus_ul_va},
    {712, block_config_table_oscar_cg_va},
    {715, block_config_table_oscar_tl_va},
    {716, block_config_table_oscar_ul_va},
    {732, block_config_table_oscar_cg_vb},
    {734, block_config_table_oscar_cg_vc},
    {735, block_config_table_oscar_cg_vd},
    {750, block_config_table_edge_plus_ul_vb},
    {758, block_config_table_edge_plus_ul_vx},
    {759, block_config_table_edge_plus_ul_vy},
    {760, block_config_table_oscar_ul_vb},
    {761, block_config_table_oscar_4g_vc},
    {770, block_config_table_oscar_tl_vb},
    {771, block_config_table_oscar_4g_vd},
    {772, block_config_table_oscar_vul_vd},
    {774, block_config_table_oscar_vtl_vd},
    {781, block_config_table_oscar_4g_ve},
    {782, block_config_table_oscar_vul_ve},
    {784, block_config_table_oscar_vtl_ve},
    {790, block_config_table_edge_plus_ul_vz},
    {800, block_config_table_sophia_ul_va},
    {801, block_config_table_sophia_ul_vb},
    {802, block_config_table_sophia_ul_vc},
    {803, block_config_table_sophia_ul_vd},
    {810, block_config_table_sophia_ul_vy},
    {820, block_config_table_sophia_tl_va},
    {821, block_config_table_sophia_tl_vb},
    {822, block_config_table_sophia_tl_vc},
    {823, block_config_table_sophia_tl_vd},
    {830, block_config_table_sophia_ulg_va},
    {831, block_config_table_sophia_ulg_vb},
    {832, block_config_table_sophia_ulg_vc},
    {833, block_config_table_sophia_ulg_vd},
    {835, block_config_table_sophia_ulg_hva},
    {840, block_config_table_sophia_clg_va},
    {841, block_config_table_sophia_clg_vb},
    {860, block_config_table_sophia_ul_vu},

    {IOMUX_CONFIG_TBL_END_SYMBOL, NULL},
};

struct iomux_config_table pin_config_tables[] = {
    {0, pin_config_table_balong_lpddr2_udp},
    {1, pin_config_table_balong_lpddr2_udp_dcm_rf},
    {2, pin_config_table_balong_lpddr2_udp_6361s},
    {9, pin_config_table_balong_lpddr2_udp_oscar_rf},
    {10, pin_config_table_balong_ddr3cap_udp},
    {11, pin_config_table_balong_ddr3cap_udp_dcm_rf},
    {12, pin_config_table_balong_ddr3cap_udp_6361s},
    {20, pin_config_table_balong_mhlcap_udp},
    {30, pin_config_table_balong_mhl_udp},
    {40, pin_config_table_balong_lpddr3_udp},
    {41, pin_config_table_balong_lpddr3_udp_dcm_rf},
    {42, pin_config_table_balong_lpddr3_udp_6361s},
    {96, pin_config_table_balong_mhlcap_udp_fhd},
    {97, pin_config_table_balong_ddr3cap_udp_fhd},
    {701, pin_config_table_edge_plus_ul_va},
    {712, pin_config_table_oscar_cg_va},
    {715, pin_config_table_oscar_tl_va},
    {716, pin_config_table_oscar_ul_va},
    {732, pin_config_table_oscar_cg_vb},
    {734, pin_config_table_oscar_cg_vc},
    {735, pin_config_table_oscar_cg_vd},
    {750, pin_config_table_edge_plus_ul_vb},
    {758, pin_config_table_edge_plus_ul_vx},
    {759, pin_config_table_edge_plus_ul_vy},
    {760, pin_config_table_oscar_ul_vb},
    {761, pin_config_table_oscar_4g_vc},
    {770, pin_config_table_oscar_tl_vb},
    {771, pin_config_table_oscar_4g_vd},
    {772, pin_config_table_oscar_vul_vd},
    {774, pin_config_table_oscar_vtl_vd},
    {781, pin_config_table_oscar_4g_ve},
    {782, pin_config_table_oscar_vul_ve},
    {784, pin_config_table_oscar_vtl_ve},
    {790, pin_config_table_edge_plus_ul_vz},
    {800, pin_config_table_sophia_ul_va},
    {801, pin_config_table_sophia_ul_vb},
    {802, pin_config_table_sophia_ul_vc},
    {803, pin_config_table_sophia_ul_vd},
    {810, pin_config_table_sophia_ul_vy},
    {820, pin_config_table_sophia_tl_va},
    {821, pin_config_table_sophia_tl_vb},
    {822, pin_config_table_sophia_tl_vc},
    {823, pin_config_table_sophia_tl_vd},
    {830, pin_config_table_sophia_ulg_va},
    {831, pin_config_table_sophia_ulg_vb},
    {832, pin_config_table_sophia_ulg_vc},
    {833, pin_config_table_sophia_ulg_vd},
    {835, pin_config_table_sophia_ulg_hva},
    {840, pin_config_table_sophia_clg_va},
    {841, pin_config_table_sophia_clg_vb},
    {860, pin_config_table_sophia_ul_vu},

    {IOMUX_CONFIG_TBL_END_SYMBOL, NULL},
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
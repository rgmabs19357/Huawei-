/******************************************************************************
 
  This is an AUTO GENERATED file ! DON'T MODIFY MANUAL! 

******************************************************************************/


#ifndef __IPPS_PARA_H__
#define __IPPS_PARA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "balong_lpddr2_udp_ipps_para.h"
#include "balong_lpddr2_udp_dcm_rf_ipps_para.h"
#include "balong_lpddr2_udp_6361s_ipps_para.h"
#include "balong_lpddr2_udp_oscar_rf_ipps_para.h"
#include "balong_ddr3cap_udp_ipps_para.h"
#include "balong_ddr3cap_udp_dcm_rf_ipps_para.h"
#include "balong_ddr3cap_udp_6361s_ipps_para.h"
#include "balong_mhlcap_udp_ipps_para.h"
#include "balong_mhl_udp_ipps_para.h"
#include "balong_lpddr3_udp_ipps_para.h"
#include "balong_lpddr3_udp_dcm_rf_ipps_para.h"
#include "balong_lpddr3_udp_6361s_ipps_para.h"
#include "balong_mhlcap_udp_fhd_ipps_para.h"
#include "balong_ddr3cap_udp_fhd_ipps_para.h"
#include "edge_plus_ul_va_ipps_para.h"
#include "oscar_cg_va_ipps_para.h"
#include "oscar_tl_va_ipps_para.h"
#include "oscar_ul_va_ipps_para.h"
#include "oscar_cg_vb_ipps_para.h"
#include "oscar_cg_vc_ipps_para.h"
#include "oscar_cg_vd_ipps_para.h"
#include "edge_plus_ul_vb_ipps_para.h"
#include "edge_plus_ul_vx_ipps_para.h"
#include "edge_plus_ul_vy_ipps_para.h"
#include "oscar_ul_vb_ipps_para.h"
#include "oscar_4g_vc_ipps_para.h"
#include "oscar_tl_vb_ipps_para.h"
#include "oscar_4g_vd_ipps_para.h"
#include "oscar_vul_vd_ipps_para.h"
#include "oscar_vtl_vd_ipps_para.h"
#include "oscar_4g_ve_ipps_para.h"
#include "oscar_vul_ve_ipps_para.h"
#include "oscar_vtl_ve_ipps_para.h"
#include "edge_plus_ul_vz_ipps_para.h"
#include "sophia_ul_va_ipps_para.h"
#include "sophia_ul_vb_ipps_para.h"
#include "sophia_ul_vc_ipps_para.h"
#include "sophia_ul_vd_ipps_para.h"
#include "sophia_ul_vy_ipps_para.h"
#include "sophia_tl_va_ipps_para.h"
#include "sophia_tl_vb_ipps_para.h"
#include "sophia_tl_vc_ipps_para.h"
#include "sophia_tl_vd_ipps_para.h"
#include "sophia_ulg_va_ipps_para.h"
#include "sophia_ulg_vb_ipps_para.h"
#include "sophia_ulg_vc_ipps_para.h"
#include "sophia_ulg_vd_ipps_para.h"
#include "sophia_ulg_hva_ipps_para.h"
#include "sophia_clg_va_ipps_para.h"
#include "sophia_clg_vb_ipps_para.h"
#include "sophia_ul_vu_ipps_para.h"
#define IPPS_PARA_DESC_TBL_END_SYMBOL     (-1)

struct ipps_para_config_desc_table {
    unsigned int board_id;
    struct ipps_para *table;
};
struct ipps_para_config_desc_table ipps_para_cpu_total[] = {
    {0, &cpu_balong_lpddr2_udp},
    {1, &cpu_balong_lpddr2_udp_dcm_rf},
    {2, &cpu_balong_lpddr2_udp_6361s},
    {9, &cpu_balong_lpddr2_udp_oscar_rf},
    {10, &cpu_balong_ddr3cap_udp},
    {11, &cpu_balong_ddr3cap_udp_dcm_rf},
    {12, &cpu_balong_ddr3cap_udp_6361s},
    {20, &cpu_balong_mhlcap_udp},
    {30, &cpu_balong_mhl_udp},
    {40, &cpu_balong_lpddr3_udp},
    {41, &cpu_balong_lpddr3_udp_dcm_rf},
    {42, &cpu_balong_lpddr3_udp_6361s},
    {96, &cpu_balong_mhlcap_udp_fhd},
    {97, &cpu_balong_ddr3cap_udp_fhd},
    {701, &cpu_edge_plus_ul_va},
    {712, &cpu_oscar_cg_va},
    {715, &cpu_oscar_tl_va},
    {716, &cpu_oscar_ul_va},
    {732, &cpu_oscar_cg_vb},
    {734, &cpu_oscar_cg_vc},
    {735, &cpu_oscar_cg_vd},
    {750, &cpu_edge_plus_ul_vb},
    {758, &cpu_edge_plus_ul_vx},
    {759, &cpu_edge_plus_ul_vy},
    {760, &cpu_oscar_ul_vb},
    {761, &cpu_oscar_4g_vc},
    {770, &cpu_oscar_tl_vb},
    {771, &cpu_oscar_4g_vd},
    {772, &cpu_oscar_vul_vd},
    {774, &cpu_oscar_vtl_vd},
    {781, &cpu_oscar_4g_ve},
    {782, &cpu_oscar_vul_ve},
    {784, &cpu_oscar_vtl_ve},
    {790, &cpu_edge_plus_ul_vz},
    {800, &cpu_sophia_ul_va},
    {801, &cpu_sophia_ul_vb},
    {802, &cpu_sophia_ul_vc},
    {803, &cpu_sophia_ul_vd},
    {810, &cpu_sophia_ul_vy},
    {820, &cpu_sophia_tl_va},
    {821, &cpu_sophia_tl_vb},
    {822, &cpu_sophia_tl_vc},
    {823, &cpu_sophia_tl_vd},
    {830, &cpu_sophia_ulg_va},
    {831, &cpu_sophia_ulg_vb},
    {832, &cpu_sophia_ulg_vc},
    {833, &cpu_sophia_ulg_vd},
    {835, &cpu_sophia_ulg_hva},
    {840, &cpu_sophia_clg_va},
    {841, &cpu_sophia_clg_vb},
    {860, &cpu_sophia_ul_vu},

    {IPPS_PARA_DESC_TBL_END_SYMBOL, NULL}
};

struct ipps_para_config_desc_table ipps_para_ddr_total[] = {
    {0, &ddr_balong_lpddr2_udp},
    {1, &ddr_balong_lpddr2_udp_dcm_rf},
    {2, &ddr_balong_lpddr2_udp_6361s},
    {9, &ddr_balong_lpddr2_udp_oscar_rf},
    {10, &ddr_balong_ddr3cap_udp},
    {11, &ddr_balong_ddr3cap_udp_dcm_rf},
    {12, &ddr_balong_ddr3cap_udp_6361s},
    {20, &ddr_balong_mhlcap_udp},
    {30, &ddr_balong_mhl_udp},
    {40, &ddr_balong_lpddr3_udp},
    {41, &ddr_balong_lpddr3_udp_dcm_rf},
    {42, &ddr_balong_lpddr3_udp_6361s},
    {96, &ddr_balong_mhlcap_udp_fhd},
    {97, &ddr_balong_ddr3cap_udp_fhd},
    {701, &ddr_edge_plus_ul_va},
    {712, &ddr_oscar_cg_va},
    {715, &ddr_oscar_tl_va},
    {716, &ddr_oscar_ul_va},
    {732, &ddr_oscar_cg_vb},
    {734, &ddr_oscar_cg_vc},
    {735, &ddr_oscar_cg_vd},
    {750, &ddr_edge_plus_ul_vb},
    {758, &ddr_edge_plus_ul_vx},
    {759, &ddr_edge_plus_ul_vy},
    {760, &ddr_oscar_ul_vb},
    {761, &ddr_oscar_4g_vc},
    {770, &ddr_oscar_tl_vb},
    {771, &ddr_oscar_4g_vd},
    {772, &ddr_oscar_vul_vd},
    {774, &ddr_oscar_vtl_vd},
    {781, &ddr_oscar_4g_ve},
    {782, &ddr_oscar_vul_ve},
    {784, &ddr_oscar_vtl_ve},
    {790, &ddr_edge_plus_ul_vz},
    {800, &ddr_sophia_ul_va},
    {801, &ddr_sophia_ul_vb},
    {802, &ddr_sophia_ul_vc},
    {803, &ddr_sophia_ul_vd},
    {810, &ddr_sophia_ul_vy},
    {820, &ddr_sophia_tl_va},
    {821, &ddr_sophia_tl_vb},
    {822, &ddr_sophia_tl_vc},
    {823, &ddr_sophia_tl_vd},
    {830, &ddr_sophia_ulg_va},
    {831, &ddr_sophia_ulg_vb},
    {832, &ddr_sophia_ulg_vc},
    {833, &ddr_sophia_ulg_vd},
    {835, &ddr_sophia_ulg_hva},
    {840, &ddr_sophia_clg_va},
    {841, &ddr_sophia_clg_vb},
    {860, &ddr_sophia_ul_vu},

    {IPPS_PARA_DESC_TBL_END_SYMBOL, NULL}
};

struct ipps_para_config_desc_table ipps_para_gpu_total[] = {
    {0, &gpu_balong_lpddr2_udp},
    {1, &gpu_balong_lpddr2_udp_dcm_rf},
    {2, &gpu_balong_lpddr2_udp_6361s},
    {9, &gpu_balong_lpddr2_udp_oscar_rf},
    {10, &gpu_balong_ddr3cap_udp},
    {11, &gpu_balong_ddr3cap_udp_dcm_rf},
    {12, &gpu_balong_ddr3cap_udp_6361s},
    {20, &gpu_balong_mhlcap_udp},
    {30, &gpu_balong_mhl_udp},
    {40, &gpu_balong_lpddr3_udp},
    {41, &gpu_balong_lpddr3_udp_dcm_rf},
    {42, &gpu_balong_lpddr3_udp_6361s},
    {96, &gpu_balong_mhlcap_udp_fhd},
    {97, &gpu_balong_ddr3cap_udp_fhd},
    {701, &gpu_edge_plus_ul_va},
    {712, &gpu_oscar_cg_va},
    {715, &gpu_oscar_tl_va},
    {716, &gpu_oscar_ul_va},
    {732, &gpu_oscar_cg_vb},
    {734, &gpu_oscar_cg_vc},
    {735, &gpu_oscar_cg_vd},
    {750, &gpu_edge_plus_ul_vb},
    {758, &gpu_edge_plus_ul_vx},
    {759, &gpu_edge_plus_ul_vy},
    {760, &gpu_oscar_ul_vb},
    {761, &gpu_oscar_4g_vc},
    {770, &gpu_oscar_tl_vb},
    {771, &gpu_oscar_4g_vd},
    {772, &gpu_oscar_vul_vd},
    {774, &gpu_oscar_vtl_vd},
    {781, &gpu_oscar_4g_ve},
    {782, &gpu_oscar_vul_ve},
    {784, &gpu_oscar_vtl_ve},
    {790, &gpu_edge_plus_ul_vz},
    {800, &gpu_sophia_ul_va},
    {801, &gpu_sophia_ul_vb},
    {802, &gpu_sophia_ul_vc},
    {803, &gpu_sophia_ul_vd},
    {810, &gpu_sophia_ul_vy},
    {820, &gpu_sophia_tl_va},
    {821, &gpu_sophia_tl_vb},
    {822, &gpu_sophia_tl_vc},
    {823, &gpu_sophia_tl_vd},
    {830, &gpu_sophia_ulg_va},
    {831, &gpu_sophia_ulg_vb},
    {832, &gpu_sophia_ulg_vc},
    {833, &gpu_sophia_ulg_vd},
    {835, &gpu_sophia_ulg_hva},
    {840, &gpu_sophia_clg_va},
    {841, &gpu_sophia_clg_vb},
    {860, &gpu_sophia_ul_vu},

    {IPPS_PARA_DESC_TBL_END_SYMBOL, NULL}
};

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

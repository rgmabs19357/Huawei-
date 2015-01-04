#ifndef __SOC_MDDRC_AXI_INTERFACE_H__
#define __SOC_MDDRC_AXI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_MDDRC_AXI_AXI_CONFIG_ADDR(base) ((base) + (0x000))
#define SOC_MDDRC_AXI_AXI_CKGCFG_ADDR(base) ((base) + (0x004))
#define SOC_MDDRC_AXI_AXI_ECCCFG_ADDR(base) ((base) + (0x008))
#define SOC_MDDRC_AXI_AXI_STATUS_ADDR(base) ((base) + (0x01C))
#define SOC_MDDRC_AXI_AXI_CHCFG0_ADDR(base) ((base) + (0x020))
#define SOC_MDDRC_AXI_AXI_CHCFG1_ADDR(base) ((base) + (0x024))
#define SOC_MDDRC_AXI_AXI_CHCFG2_ADDR(base) ((base) + (0x028))
#define SOC_MDDRC_AXI_AXI_CHCFG3_ADDR(base) ((base) + (0x02C))
#define SOC_MDDRC_AXI_AXI_CHCFG4_ADDR(base) ((base) + (0x030))
#define SOC_MDDRC_AXI_AXI_CHCFG5_ADDR(base) ((base) + (0x034))
#define SOC_MDDRC_AXI_AXI_LPCFG_ADDR(base) ((base) + (0x038))
#define SOC_MDDRC_AXI_AXI_QOSCFG0_ADDR(base,ports) ((base) + (0x040+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_QOSCFG1_ADDR(base,ports) ((base) + (0x080+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_WRPRI_ADDR(base,ports) ((base) + (0x0C0+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_RDPRI_ADDR(base,ports) ((base) + (0x100+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_WRQOS_ADDR(base,ports) ((base) + (0x140+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_RDQOS_ADDR(base,ports) ((base) + (0x180+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_ADDR(base,ports) ((base) + (0x200+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_ADDR(base) ((base) + (0x240))
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ADDR(base) ((base) + (0x244))
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ADDR(base) ((base) + (0x248))
#define SOC_MDDRC_AXI_AXI_FLUX0_ADDR(base,ports) ((base) + (0x280+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_FLUX1_ADDR(base,ports) ((base) + (0x2C0+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_FLUX2_ADDR(base,ports) ((base) + (0x300+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_FLUX3_ADDR(base,ports) ((base) + (0x340+0x4*(ports)))
#define SOC_MDDRC_AXI_AXI_RAM_TMOD_ADDR(base) ((base) + (0x400))
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_ADDR(base) ((base) + (0x404))
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_ADDR(base) ((base) + (0x408))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bank_width : 4;
        unsigned int reserved_0 : 12;
        unsigned int rd_wrap_split_en : 1;
        unsigned int exclusive_en : 1;
        unsigned int wr_rcv_mode : 1;
        unsigned int reserved_1 : 13;
    } reg;
} SOC_MDDRC_AXI_AXI_CONFIG_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CONFIG_bank_width_START (0)
#define SOC_MDDRC_AXI_AXI_CONFIG_bank_width_END (3)
#define SOC_MDDRC_AXI_AXI_CONFIG_rd_wrap_split_en_START (16)
#define SOC_MDDRC_AXI_AXI_CONFIG_rd_wrap_split_en_END (16)
#define SOC_MDDRC_AXI_AXI_CONFIG_exclusive_en_START (17)
#define SOC_MDDRC_AXI_AXI_CONFIG_exclusive_en_END (17)
#define SOC_MDDRC_AXI_AXI_CONFIG_wr_rcv_mode_START (18)
#define SOC_MDDRC_AXI_AXI_CONFIG_wr_rcv_mode_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dyn_ckg_axi0 : 1;
        unsigned int dyn_ckg_axi1 : 1;
        unsigned int dyn_ckg_axi2 : 1;
        unsigned int dyn_ckg_axi3 : 1;
        unsigned int dyn_ckg_axi4 : 1;
        unsigned int dyn_ckg_axi5 : 1;
        unsigned int dyn_ckg_axi6 : 1;
        unsigned int dyn_ckg_axi7 : 1;
        unsigned int dyn_ckg_axi8 : 1;
        unsigned int dyn_ckg_axi9 : 1;
        unsigned int dyn_ckg_axi10 : 1;
        unsigned int dyn_ckg_axi11 : 1;
        unsigned int reserved_0 : 4;
        unsigned int dyn_ckg_rdr : 1;
        unsigned int reserved_1 : 3;
        unsigned int sta_ckg_apb : 1;
        unsigned int reserved_2 : 3;
        unsigned int sta_ckg_dmc0 : 1;
        unsigned int sta_ckg_dmc1 : 1;
        unsigned int sta_ckg_dmc2 : 1;
        unsigned int sta_ckg_dmc3 : 1;
        unsigned int sta_ckg_pub0 : 1;
        unsigned int sta_ckg_pub1 : 1;
        unsigned int sta_ckg_pub2 : 1;
        unsigned int sta_ckg_pub3 : 1;
    } reg;
} SOC_MDDRC_AXI_AXI_CKGCFG_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi0_START (0)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi0_END (0)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi1_START (1)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi1_END (1)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi2_START (2)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi2_END (2)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi3_START (3)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi3_END (3)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi4_START (4)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi4_END (4)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi5_START (5)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi5_END (5)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi6_START (6)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi6_END (6)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi7_START (7)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi7_END (7)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi8_START (8)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi8_END (8)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi9_START (9)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi9_END (9)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi10_START (10)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi10_END (10)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi11_START (11)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_axi11_END (11)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_rdr_START (16)
#define SOC_MDDRC_AXI_AXI_CKGCFG_dyn_ckg_rdr_END (16)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_apb_START (20)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_apb_END (20)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc0_START (24)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc0_END (24)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc1_START (25)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc1_END (25)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc2_START (26)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc2_END (26)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc3_START (27)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_dmc3_END (27)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub0_START (28)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub0_END (28)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub1_START (29)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub1_END (29)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub2_START (30)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub2_END (30)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub3_START (31)
#define SOC_MDDRC_AXI_AXI_CKGCFG_sta_ckg_pub3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ecc_byp_addr : 18;
        unsigned int reserved_0 : 6;
        unsigned int ecc_byp_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int ecc_en : 1;
        unsigned int reserved_2 : 3;
    } reg;
} SOC_MDDRC_AXI_AXI_ECCCFG_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_byp_addr_START (0)
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_byp_addr_END (17)
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_byp_en_START (24)
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_byp_en_END (24)
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_en_START (28)
#define SOC_MDDRC_AXI_AXI_ECCCFG_ecc_en_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axist0 : 1;
        unsigned int axist1 : 1;
        unsigned int axist2 : 1;
        unsigned int axist3 : 1;
        unsigned int axist4 : 1;
        unsigned int axist5 : 1;
        unsigned int axist6 : 1;
        unsigned int axist7 : 1;
        unsigned int axist8 : 1;
        unsigned int axist9 : 1;
        unsigned int axist10 : 1;
        unsigned int axist11 : 1;
        unsigned int reserved : 20;
    } reg;
} SOC_MDDRC_AXI_AXI_STATUS_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_STATUS_axist0_START (0)
#define SOC_MDDRC_AXI_AXI_STATUS_axist0_END (0)
#define SOC_MDDRC_AXI_AXI_STATUS_axist1_START (1)
#define SOC_MDDRC_AXI_AXI_STATUS_axist1_END (1)
#define SOC_MDDRC_AXI_AXI_STATUS_axist2_START (2)
#define SOC_MDDRC_AXI_AXI_STATUS_axist2_END (2)
#define SOC_MDDRC_AXI_AXI_STATUS_axist3_START (3)
#define SOC_MDDRC_AXI_AXI_STATUS_axist3_END (3)
#define SOC_MDDRC_AXI_AXI_STATUS_axist4_START (4)
#define SOC_MDDRC_AXI_AXI_STATUS_axist4_END (4)
#define SOC_MDDRC_AXI_AXI_STATUS_axist5_START (5)
#define SOC_MDDRC_AXI_AXI_STATUS_axist5_END (5)
#define SOC_MDDRC_AXI_AXI_STATUS_axist6_START (6)
#define SOC_MDDRC_AXI_AXI_STATUS_axist6_END (6)
#define SOC_MDDRC_AXI_AXI_STATUS_axist7_START (7)
#define SOC_MDDRC_AXI_AXI_STATUS_axist7_END (7)
#define SOC_MDDRC_AXI_AXI_STATUS_axist8_START (8)
#define SOC_MDDRC_AXI_AXI_STATUS_axist8_END (8)
#define SOC_MDDRC_AXI_AXI_STATUS_axist9_START (9)
#define SOC_MDDRC_AXI_AXI_STATUS_axist9_END (9)
#define SOC_MDDRC_AXI_AXI_STATUS_axist10_START (10)
#define SOC_MDDRC_AXI_AXI_STATUS_axist10_END (10)
#define SOC_MDDRC_AXI_AXI_STATUS_axist11_START (11)
#define SOC_MDDRC_AXI_AXI_STATUS_axist11_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_addr_msk_idx : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG0_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG0_ch_addr_msk_idx_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG0_ch_addr_msk_idx_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_start0 : 2;
        unsigned int ch_start1 : 2;
        unsigned int ch_start2 : 2;
        unsigned int ch_start3 : 2;
        unsigned int ch_start4 : 2;
        unsigned int ch_start5 : 2;
        unsigned int ch_start6 : 2;
        unsigned int ch_start7 : 2;
        unsigned int ch_start8 : 2;
        unsigned int ch_start9 : 2;
        unsigned int ch_start10 : 2;
        unsigned int ch_start11 : 2;
        unsigned int ch_start12 : 2;
        unsigned int ch_start13 : 2;
        unsigned int ch_start14 : 2;
        unsigned int ch_start15 : 2;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG1_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start0_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start0_END (1)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start1_START (2)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start1_END (3)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start2_START (4)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start2_END (5)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start3_START (6)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start3_END (7)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start4_START (8)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start4_END (9)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start5_START (10)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start5_END (11)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start6_START (12)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start6_END (13)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start7_START (14)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start7_END (15)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start8_START (16)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start8_END (17)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start9_START (18)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start9_END (19)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start10_START (20)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start10_END (21)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start11_START (22)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start11_END (23)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start12_START (24)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start12_END (25)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start13_START (26)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start13_END (27)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start14_START (28)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start14_END (29)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start15_START (30)
#define SOC_MDDRC_AXI_AXI_CHCFG1_ch_start15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_mode0 : 2;
        unsigned int ch_mode1 : 2;
        unsigned int ch_mode2 : 2;
        unsigned int ch_mode3 : 2;
        unsigned int ch_mode4 : 2;
        unsigned int ch_mode5 : 2;
        unsigned int ch_mode6 : 2;
        unsigned int ch_mode7 : 2;
        unsigned int ch_mode8 : 2;
        unsigned int ch_mode9 : 2;
        unsigned int ch_mode10 : 2;
        unsigned int ch_mode11 : 2;
        unsigned int ch_mode12 : 2;
        unsigned int ch_mode13 : 2;
        unsigned int ch_mode14 : 2;
        unsigned int ch_mode15 : 2;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG2_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode0_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode0_END (1)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode1_START (2)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode1_END (3)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode2_START (4)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode2_END (5)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode3_START (6)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode3_END (7)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode4_START (8)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode4_END (9)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode5_START (10)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode5_END (11)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode6_START (12)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode6_END (13)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode7_START (14)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode7_END (15)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode8_START (16)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode8_END (17)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode9_START (18)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode9_END (19)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode10_START (20)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode10_END (21)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode11_START (22)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode11_END (23)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode12_START (24)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode12_END (25)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode13_START (26)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode13_END (27)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode14_START (28)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode14_END (29)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode15_START (30)
#define SOC_MDDRC_AXI_AXI_CHCFG2_ch_mode15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_invld0 : 1;
        unsigned int ch_invld1 : 1;
        unsigned int ch_invld2 : 1;
        unsigned int ch_invld3 : 1;
        unsigned int ch_invld4 : 1;
        unsigned int ch_invld5 : 1;
        unsigned int ch_invld6 : 1;
        unsigned int ch_invld7 : 1;
        unsigned int ch_invld8 : 1;
        unsigned int ch_invld9 : 1;
        unsigned int ch_invld10 : 1;
        unsigned int ch_invld11 : 1;
        unsigned int ch_invld12 : 1;
        unsigned int ch_invld13 : 1;
        unsigned int ch_invld14 : 1;
        unsigned int ch_invld15 : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG3_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld0_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld0_END (0)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld1_START (1)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld1_END (1)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld2_START (2)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld2_END (2)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld3_START (3)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld3_END (3)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld4_START (4)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld4_END (4)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld5_START (5)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld5_END (5)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld6_START (6)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld6_END (6)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld7_START (7)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld7_END (7)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld8_START (8)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld8_END (8)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld9_START (9)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld9_END (9)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld10_START (10)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld10_END (10)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld11_START (11)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld11_END (11)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld12_START (12)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld12_END (12)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld13_START (13)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld13_END (13)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld14_START (14)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld14_END (14)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld15_START (15)
#define SOC_MDDRC_AXI_AXI_CHCFG3_ch_invld15_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_sect0 : 4;
        unsigned int ch_sect1 : 4;
        unsigned int ch_sect2 : 4;
        unsigned int ch_sect3 : 4;
        unsigned int ch_sect4 : 4;
        unsigned int ch_sect5 : 4;
        unsigned int ch_sect6 : 4;
        unsigned int ch_sect7 : 4;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG4_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect0_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect0_END (3)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect1_START (4)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect1_END (7)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect2_START (8)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect2_END (11)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect3_START (12)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect3_END (15)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect4_START (16)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect4_END (19)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect5_START (20)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect5_END (23)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect6_START (24)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect6_END (27)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect7_START (28)
#define SOC_MDDRC_AXI_AXI_CHCFG4_ch_sect7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_sect8 : 4;
        unsigned int ch_sect9 : 4;
        unsigned int ch_sect10 : 4;
        unsigned int ch_sect11 : 4;
        unsigned int ch_sect12 : 4;
        unsigned int ch_sect13 : 4;
        unsigned int ch_sect14 : 4;
        unsigned int ch_sect15 : 4;
    } reg;
} SOC_MDDRC_AXI_AXI_CHCFG5_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect8_START (0)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect8_END (3)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect9_START (4)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect9_END (7)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect10_START (8)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect10_END (11)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect11_START (12)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect11_END (15)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect12_START (16)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect12_END (19)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect13_START (20)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect13_END (23)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect14_START (24)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect14_END (27)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect15_START (28)
#define SOC_MDDRC_AXI_AXI_CHCFG5_ch_sect15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_zone_en : 1;
        unsigned int reserved : 15;
        unsigned int lp_zone_size : 16;
    } reg;
} SOC_MDDRC_AXI_AXI_LPCFG_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_LPCFG_lp_zone_en_START (0)
#define SOC_MDDRC_AXI_AXI_LPCFG_lp_zone_en_END (0)
#define SOC_MDDRC_AXI_AXI_LPCFG_lp_zone_size_START (16)
#define SOC_MDDRC_AXI_AXI_LPCFG_lp_zone_size_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_map : 12;
        unsigned int reserved_0 : 4;
        unsigned int id_map_mode : 1;
        unsigned int axqos_revers : 1;
        unsigned int pri_deliver_en : 1;
        unsigned int reserved_1 : 13;
    } reg;
} SOC_MDDRC_AXI_AXI_QOSCFG0_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_QOSCFG0_id_map_START (0)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_id_map_END (11)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_id_map_mode_START (16)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_id_map_mode_END (16)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_axqos_revers_START (17)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_axqos_revers_END (17)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_pri_deliver_en_START (18)
#define SOC_MDDRC_AXI_AXI_QOSCFG0_pri_deliver_en_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_age_prd : 4;
        unsigned int rd_pri_apt : 4;
        unsigned int reserved_0 : 8;
        unsigned int wr_age_prd : 4;
        unsigned int wr_pri_apt : 4;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_MDDRC_AXI_AXI_QOSCFG1_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_QOSCFG1_rd_age_prd_START (0)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_rd_age_prd_END (3)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_rd_pri_apt_START (4)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_rd_pri_apt_END (7)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_wr_age_prd_START (16)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_wr_age_prd_END (19)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_wr_pri_apt_START (20)
#define SOC_MDDRC_AXI_AXI_QOSCFG1_wr_pri_apt_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_pri0 : 3;
        unsigned int reserved_0: 1;
        unsigned int wr_pri1 : 3;
        unsigned int reserved_1: 1;
        unsigned int wr_pri2 : 3;
        unsigned int reserved_2: 1;
        unsigned int wr_pri3 : 3;
        unsigned int reserved_3: 1;
        unsigned int wr_pri4 : 3;
        unsigned int reserved_4: 1;
        unsigned int wr_pri5 : 3;
        unsigned int reserved_5: 1;
        unsigned int wr_pri6 : 3;
        unsigned int reserved_6: 1;
        unsigned int wr_pri7 : 3;
        unsigned int reserved_7: 1;
    } reg;
} SOC_MDDRC_AXI_AXI_WRPRI_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri0_START (0)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri0_END (2)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri1_START (4)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri1_END (6)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri2_START (8)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri2_END (10)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri3_START (12)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri3_END (14)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri4_START (16)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri4_END (18)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri5_START (20)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri5_END (22)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri6_START (24)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri6_END (26)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri7_START (28)
#define SOC_MDDRC_AXI_AXI_WRPRI_wr_pri7_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_pri0 : 3;
        unsigned int reserved_0: 1;
        unsigned int rd_pri1 : 3;
        unsigned int reserved_1: 1;
        unsigned int rd_pri2 : 3;
        unsigned int reserved_2: 1;
        unsigned int rd_pri3 : 3;
        unsigned int reserved_3: 1;
        unsigned int rd_pri4 : 3;
        unsigned int reserved_4: 1;
        unsigned int rd_pri5 : 3;
        unsigned int reserved_5: 1;
        unsigned int rd_pri6 : 3;
        unsigned int reserved_6: 1;
        unsigned int rd_pri7 : 3;
        unsigned int reserved_7: 1;
    } reg;
} SOC_MDDRC_AXI_AXI_RDPRI_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri0_START (0)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri0_END (2)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri1_START (4)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri1_END (6)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri2_START (8)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri2_END (10)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri3_START (12)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri3_END (14)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri4_START (16)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri4_END (18)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri5_START (20)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri5_END (22)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri6_START (24)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri6_END (26)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri7_START (28)
#define SOC_MDDRC_AXI_AXI_RDPRI_rd_pri7_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wr_qosl_tout : 10;
        unsigned int reserved_0 : 2;
        unsigned int wr_qos_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int wr_qosh_tout : 10;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_MDDRC_AXI_AXI_WRQOS_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qosl_tout_START (0)
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qosl_tout_END (9)
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qos_en_START (12)
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qos_en_END (12)
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qosh_tout_START (16)
#define SOC_MDDRC_AXI_AXI_WRQOS_wr_qosh_tout_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_qosl_tout : 10;
        unsigned int reserved_0 : 2;
        unsigned int rd_qos_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int rd_qosh_tout : 10;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_MDDRC_AXI_AXI_RDQOS_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qosl_tout_START (0)
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qosl_tout_END (9)
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qos_en_START (12)
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qos_en_END (12)
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qosh_tout_START (16)
#define SOC_MDDRC_AXI_AXI_RDQOS_rd_qosh_tout_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int port_ostd_lvl0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int port_ostd_lvl1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int port_ostd_lvl2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int port_ostd_lvl3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_MDDRC_AXI_AXI_OSTDCFG0_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl0_START (0)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl0_END (4)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl1_START (8)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl1_END (12)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl2_START (16)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl2_END (20)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl3_START (24)
#define SOC_MDDRC_AXI_AXI_OSTDCFG0_port_ostd_lvl3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_ostd_lvl0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int dmc_ostd_lvl1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int dmc_ostd_lvl2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int dmc_ostd_lvl3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_MDDRC_AXI_AXI_OSTDCFG1_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl0_START (0)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl0_END (4)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl1_START (8)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl1_END (12)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl2_START (16)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl2_END (20)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl3_START (24)
#define SOC_MDDRC_AXI_AXI_OSTDCFG1_dmc_ostd_lvl3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ostd_mode0 : 2;
        unsigned int ostd_mode1 : 2;
        unsigned int ostd_mode2 : 2;
        unsigned int ostd_mode3 : 2;
        unsigned int ostd_mode4 : 2;
        unsigned int ostd_mode5 : 2;
        unsigned int ostd_mode6 : 2;
        unsigned int ostd_mode7 : 2;
        unsigned int ostd_mode8 : 2;
        unsigned int ostd_mode9 : 2;
        unsigned int ostd_mode10 : 2;
        unsigned int ostd_mode11 : 2;
        unsigned int reserved : 8;
    } reg;
} SOC_MDDRC_AXI_AXI_OSTDCFG2_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode0_START (0)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode0_END (1)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode1_START (2)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode1_END (3)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode2_START (4)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode2_END (5)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode3_START (6)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode3_END (7)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode4_START (8)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode4_END (9)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode5_START (10)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode5_END (11)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode6_START (12)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode6_END (13)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode7_START (14)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode7_END (15)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode8_START (16)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode8_END (17)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode9_START (18)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode9_END (19)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode10_START (20)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode10_END (21)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode11_START (22)
#define SOC_MDDRC_AXI_AXI_OSTDCFG2_ostd_mode11_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ostd_st0 : 5;
        unsigned int reserved_0: 3;
        unsigned int ostd_st1 : 5;
        unsigned int reserved_1: 3;
        unsigned int ostd_st2 : 5;
        unsigned int reserved_2: 3;
        unsigned int ostd_st3 : 5;
        unsigned int reserved_3: 3;
    } reg;
} SOC_MDDRC_AXI_AXI_OSTDSTATUS_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st0_START (0)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st0_END (4)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st1_START (8)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st1_END (12)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st2_START (16)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st2_END (20)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st3_START (24)
#define SOC_MDDRC_AXI_AXI_OSTDSTATUS_ostd_st3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_cfg0 : 10;
        unsigned int reserved_0 : 2;
        unsigned int flux_ovfl_lvl0 : 5;
        unsigned int reserved_1 : 3;
        unsigned int flux_ovfl_en0 : 1;
        unsigned int flux_port_en0 : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_MDDRC_AXI_AXI_FLUX0_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_cfg0_START (0)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_cfg0_END (9)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_ovfl_lvl0_START (12)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_ovfl_lvl0_END (16)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_ovfl_en0_START (20)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_ovfl_en0_END (20)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_port_en0_START (21)
#define SOC_MDDRC_AXI_AXI_FLUX0_flux_port_en0_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_cfg1 : 10;
        unsigned int reserved_0 : 2;
        unsigned int flux_ovfl_lvl1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int flux_ovfl_en1 : 1;
        unsigned int flux_port_en1 : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_MDDRC_AXI_AXI_FLUX1_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_cfg1_START (0)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_cfg1_END (9)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_ovfl_lvl1_START (12)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_ovfl_lvl1_END (16)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_ovfl_en1_START (20)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_ovfl_en1_END (20)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_port_en1_START (21)
#define SOC_MDDRC_AXI_AXI_FLUX1_flux_port_en1_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_cfg2 : 10;
        unsigned int reserved_0 : 2;
        unsigned int flux_ovfl_lvl2 : 5;
        unsigned int reserved_1 : 3;
        unsigned int flux_ovfl_en2 : 1;
        unsigned int flux_port_en2 : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_MDDRC_AXI_AXI_FLUX2_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_cfg2_START (0)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_cfg2_END (9)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_ovfl_lvl2_START (12)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_ovfl_lvl2_END (16)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_ovfl_en2_START (20)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_ovfl_en2_END (20)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_port_en2_START (21)
#define SOC_MDDRC_AXI_AXI_FLUX2_flux_port_en2_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_cfg3 : 10;
        unsigned int reserved_0 : 2;
        unsigned int flux_ovfl_lvl3 : 5;
        unsigned int reserved_1 : 3;
        unsigned int flux_ovfl_en3 : 1;
        unsigned int flux_port_en3 : 1;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_MDDRC_AXI_AXI_FLUX3_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_cfg3_START (0)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_cfg3_END (9)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_ovfl_lvl3_START (12)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_ovfl_lvl3_END (16)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_ovfl_en3_START (20)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_ovfl_en3_END (20)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_port_en3_START (21)
#define SOC_MDDRC_AXI_AXI_FLUX3_flux_port_en3_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdrram_tmod : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_MDDRC_AXI_AXI_RAM_TMOD_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_RAM_TMOD_rdrram_tmod_START (0)
#define SOC_MDDRC_AXI_AXI_RAM_TMOD_rdrram_tmod_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdrram_err_inj0 : 2;
        unsigned int reserved_0 : 2;
        unsigned int rdrram_err_inj1 : 2;
        unsigned int reserved_1 : 2;
        unsigned int rdrram_err_inj2 : 2;
        unsigned int reserved_2 : 2;
        unsigned int rdrram_err_inj3 : 2;
        unsigned int reserved_3 : 18;
    } reg;
} SOC_MDDRC_AXI_AXI_RAM_ERRINJ_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj0_START (0)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj0_END (1)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj1_START (4)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj1_END (5)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj2_START (8)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj2_END (9)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj3_START (12)
#define SOC_MDDRC_AXI_AXI_RAM_ERRINJ_rdrram_err_inj3_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdrram_1bit_err0 : 1;
        unsigned int rdrram_2bit_err0 : 1;
        unsigned int reserved_0 : 2;
        unsigned int rdrram_1bit_err1 : 1;
        unsigned int rdrram_2bit_err1 : 1;
        unsigned int reserved_1 : 2;
        unsigned int rdrram_1bit_err2 : 1;
        unsigned int rdrram_2bit_err2 : 1;
        unsigned int reserved_2 : 2;
        unsigned int rdrram_1bit_err3 : 1;
        unsigned int rdrram_2bit_err3 : 1;
        unsigned int reserved_3 : 18;
    } reg;
} SOC_MDDRC_AXI_AXI_RAM_ERRST_UNION;
#endif
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err0_START (0)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err0_END (0)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err0_START (1)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err0_END (1)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err1_START (4)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err1_END (4)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err1_START (5)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err1_END (5)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err2_START (8)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err2_END (8)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err2_START (9)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err2_END (9)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err3_START (12)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_1bit_err3_END (12)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err3_START (13)
#define SOC_MDDRC_AXI_AXI_RAM_ERRST_rdrram_2bit_err3_END (13)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

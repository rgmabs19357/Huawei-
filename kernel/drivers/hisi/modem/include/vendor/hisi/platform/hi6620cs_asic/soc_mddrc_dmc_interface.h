#ifndef __SOC_MDDRC_DMC_INTERFACE_H__
#define __SOC_MDDRC_DMC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_SREF_ADDR(base) ((base) + (0x000))
#define SOC_MDDRC_DMC_DDRC_CTRL_INIT_ADDR(base) ((base) + (0x004))
#define SOC_MDDRC_DMC_DDRC_CTRL_DDRRST_ADDR(base) ((base) + (0x008))
#define SOC_MDDRC_DMC_DDRC_CTRL_SFC_ADDR(base) ((base) + (0x00C))
#define SOC_MDDRC_DMC_DDRC_CTRL_PERF_ADDR(base) ((base) + (0x010))
#define SOC_MDDRC_DMC_DDRC_CTRL_MTEST_ADDR(base) ((base) + (0x014))
#define SOC_MDDRC_DMC_DDRC_CTRL_MCLR_ADDR(base) ((base) + (0x018))
#define SOC_MDDRC_DMC_DDRC_CFG_LP_ADDR(base) ((base) + (0x01C))
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_ADDR(base) ((base) + (0x020))
#define SOC_MDDRC_DMC_DDRC_CFG_INIT_ADDR(base) ((base) + (0x024))
#define SOC_MDDRC_DMC_DDRC_CFG_PD_ADDR(base) ((base) + (0x028))
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_ADDR(base) ((base) + (0x02C))
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_ADDR(base) ((base) + (0x030))
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_ADDR(base) ((base) + (0x034))
#define SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_ADDR(base) ((base) + (0x038))
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_ADDR(base) ((base) + (0x040))
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_ADDR(base) ((base) + (0x050))
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_ADDR(base) ((base) + (0x054))
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_ADDR(base,rnks) ((base) + (0x060+0x4*(rnks)))
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS01_ADDR(base) ((base) + (0x070))
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS23_ADDR(base) ((base) + (0x074))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_ADDR(base) ((base) + (0x080))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_ADDR(base) ((base) + (0x084))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_ADDR(base) ((base) + (0x88))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_ADDR(base) ((base) + (0x8C))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_ADDR(base) ((base) + (0x090))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_ADDR(base) ((base) + (0x094))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_ADDR(base) ((base) + (0x098))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_ADDR(base) ((base) + (0x0A0))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_ADDR(base) ((base) + (0x0A4))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_ADDR(base) ((base) + (0x0A8))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_ADDR(base) ((base) + (0x0AC))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_ADDR(base) ((base) + (0x0B0))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_ADDR(base) ((base) + (0x0B4))
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_ADDR(base) ((base) + (0x0B8))
#define SOC_MDDRC_DMC_DDRC_CFG_BLDATA_ADDR(base) ((base) + (0x0BC))
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_ADDR(base) ((base) + (0x0C0))
#define SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_ADDR(base) ((base) + (0x0C4))
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_ADDR(base) ((base) + (0x0D0))
#define SOC_MDDRC_DMC_DDRC_CFG_QOS_ADDR(base) ((base) + (0x0D4))
#define SOC_MDDRC_DMC_DDRC_CFG_MBIST_ADDR(base) ((base) + (0x0E0))
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN0_ADDR(base) ((base) + (0x0E4))
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN1_ADDR(base) ((base) + (0x0E8))
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN2_ADDR(base) ((base) + (0x0EC))
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN3_ADDR(base) ((base) + (0x0F0))
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN4_ADDR(base) ((base) + (0x0F4))
#define SOC_MDDRC_DMC_DDRC_CFG_TRAIN_ADDR(base) ((base) + (0x180))
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_ADDR(base) ((base) + (0x200))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR(base) ((base) + (0x210))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_ADDR(base) ((base) + (0x214))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR1_ADDR(base) ((base) + (0x218))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA0_ADDR(base) ((base) + (0x21C))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA1_ADDR(base) ((base) + (0x220))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA2_ADDR(base) ((base) + (0x224))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA3_ADDR(base) ((base) + (0x228))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA4_ADDR(base) ((base) + (0x22C))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA5_ADDR(base) ((base) + (0x230))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA6_ADDR(base) ((base) + (0x234))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA7_ADDR(base) ((base) + (0x238))
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_ADDR(base) ((base) + (0x23C))
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_ADDR(base) ((base) + (0x270))
#define SOC_MDDRC_DMC_DDRC_CFG_STAID_ADDR(base) ((base) + (0x274))
#define SOC_MDDRC_DMC_DDRC_CFG_STAIDMSK_ADDR(base) ((base) + (0x278))
#define SOC_MDDRC_DMC_DDRC_INTMSK_ADDR(base) ((base) + (0x280))
#define SOC_MDDRC_DMC_DDRC_RINT_ADDR(base) ((base) + (0x284))
#define SOC_MDDRC_DMC_DDRC_INTSTS_ADDR(base) ((base) + (0x288))
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_ADDR(base) ((base) + (0x290))
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_ADDR(base) ((base) + (0x294))
#define SOC_MDDRC_DMC_DDRC_CURR_EXECST_ADDR(base) ((base) + (0x2A0))
#define SOC_MDDRC_DMC_DDRC_CURR_WGFIFOST_ADDR(base) ((base) + (0x2A4))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR0_ADDR(base) ((base) + (0x2D0))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR1_ADDR(base) ((base) + (0x2D4))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA0_ADDR(base) ((base) + (0x2D8))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA1_ADDR(base) ((base) + (0x2DC))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA2_ADDR(base) ((base) + (0x2E0))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA3_ADDR(base) ((base) + (0x2E4))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA4_ADDR(base) ((base) + (0x2E8))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA5_ADDR(base) ((base) + (0x2EC))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA6_ADDR(base) ((base) + (0x2F0))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA7_ADDR(base) ((base) + (0x2F4))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA8_ADDR(base) ((base) + (0x2F8))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA0_ADDR(base) ((base) + (0x2FC))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA1_ADDR(base) ((base) + (0x300))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA2_ADDR(base) ((base) + (0x304))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA3_ADDR(base) ((base) + (0x308))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA4_ADDR(base) ((base) + (0x30C))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA5_ADDR(base) ((base) + (0x310))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA6_ADDR(base) ((base) + (0x314))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA7_ADDR(base) ((base) + (0x318))
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA8_ADDR(base) ((base) + (0x31C))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR0_ADDR(base) ((base) + (0x320))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR1_ADDR(base) ((base) + (0x324))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ID_ADDR(base) ((base) + (0x328))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA0_ADDR(base) ((base) + (0x330))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA1_ADDR(base) ((base) + (0x334))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA2_ADDR(base) ((base) + (0x338))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA3_ADDR(base) ((base) + (0x33C))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA4_ADDR(base) ((base) + (0x340))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA5_ADDR(base) ((base) + (0x344))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA6_ADDR(base) ((base) + (0x348))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA7_ADDR(base) ((base) + (0x34C))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA8_ADDR(base) ((base) + (0x350))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA0_ADDR(base) ((base) + (0x354))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA1_ADDR(base) ((base) + (0x358))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA2_ADDR(base) ((base) + (0x35C))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA3_ADDR(base) ((base) + (0x360))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA4_ADDR(base) ((base) + (0x364))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA5_ADDR(base) ((base) + (0x368))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA6_ADDR(base) ((base) + (0x36C))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA7_ADDR(base) ((base) + (0x370))
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA8_ADDR(base) ((base) + (0x374))
#define SOC_MDDRC_DMC_DDRC_HIS_SERRCNT_ADDR(base) ((base) + (0x378))
#define SOC_MDDRC_DMC_DDRC_HIS_MERRCNT_ADDR(base) ((base) + (0x37C))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WR_ADDR(base) ((base) + (0x380))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RD_ADDR(base) ((base) + (0x384))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WCMD_ADDR(base) ((base) + (0x0388))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RCMD_ADDR(base) ((base) + (0x038C))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WR_ADDR(base) ((base) + (0x390))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RD_ADDR(base) ((base) + (0x394))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WCMD_ADDR(base) ((base) + (0x0398))
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RCMD_ADDR(base) ((base) + (0x039C))
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_ADDR(base) ((base) + (0x3A0))
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT1_ADDR(base) ((base) + (0x3A4))
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_ADDR(base) ((base) + (0x3A8))
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT1_ADDR(base) ((base) + (0x3AC))
#define SOC_MDDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_ADDR(base) ((base) + (0x3B0))
#define SOC_MDDRC_DMC_DDRC_HIS_CMD_SUM_ADDR(base) ((base) + (0x3BC))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_ADDR(base) ((base) + (0x410))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRADDR_ADDR(base) ((base) + (0x414))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_ADDR(base) ((base) + (0x418))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_ADDR(base) ((base) + (0x41C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_ADDR(base) ((base) + (0x420))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_ADDR(base) ((base) + (0x424))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_ADDR(base) ((base) + (0x428))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_ADDR(base) ((base) + (0x42C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_ADDR(base) ((base) + (0x430))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_ADDR(base) ((base) + (0x434))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_ADDR(base) ((base) + (0x438))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_ADDR(base) ((base) + (0x43C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_ADDR(base) ((base) + (0x440))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_ADDR(base) ((base) + (0x444))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_ADDR(base) ((base) + (0x448))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_ADDR(base) ((base) + (0x44C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_ADDR(base) ((base) + (0x450))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_ADDR(base) ((base) + (0x454))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_ADDR(base) ((base) + (0x458))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_ADDR(base) ((base) + (0x45C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_ADDR(base) ((base) + (0x460))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_ADDR(base) ((base) + (0x464))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_ADDR(base) ((base) + (0x468))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_ADDR(base) ((base) + (0x46C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_ADDR(base) ((base) + (0x470))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_ADDR(base) ((base) + (0x474))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_ADDR(base) ((base) + (0x478))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_ADDR(base) ((base) + (0x47C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_ADDR(base) ((base) + (0x480))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_ADDR(base) ((base) + (0x484))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_ADDR(base) ((base) + (0x488))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_ADDR(base) ((base) + (0x48C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_ADDR(base) ((base) + (0x490))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_ADDR(base) ((base) + (0x494))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_ADDR(base) ((base) + (0x498))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_ADDR(base) ((base) + (0x49C))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_ADDR(base) ((base) + (0x4A0))
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_ADDR(base) ((base) + (0x4A4))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA0_ADDR(base) ((base) + (0x4A8))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA1_ADDR(base) ((base) + (0x4AC))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA2_ADDR(base) ((base) + (0x4B0))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA3_ADDR(base) ((base) + (0x4B4))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA4_ADDR(base) ((base) + (0x4B8))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA5_ADDR(base) ((base) + (0x4BC))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA6_ADDR(base) ((base) + (0x4C0))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA7_ADDR(base) ((base) + (0x4C4))
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_ADDR(base) ((base) + (0x4C8))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE0_ADDR(base) ((base) + (0x4CC))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE1_ADDR(base) ((base) + (0x4D0))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE2_ADDR(base) ((base) + (0x4D4))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE0_ST_ADDR(base) ((base) + (0x4D8))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE1_ST_ADDR(base) ((base) + (0x4DC))
#define SOC_MDDRC_DMC_DDRC_TEST_GENPOSE2_ST_ADDR(base) ((base) + (0x4E0))
#define SOC_MDDRC_DMC_DDRC_TEST_RAM_TMOD_ADDR(base) ((base) + (0x500))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sref_req : 1;
        unsigned int sref_done : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_SREF_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_SREF_sref_req_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_SREF_sref_req_END (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_SREF_sref_done_START (1)
#define SOC_MDDRC_DMC_DDRC_CTRL_SREF_sref_done_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int init_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_INIT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_INIT_init_req_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_INIT_init_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr3_rst_n : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_DDRRST_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_DDRRST_ddr3_rst_n_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_SFC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_SFC_cmd_req_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_SFC_cmd_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perf_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_PERF_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_PERF_perf_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_PERF_perf_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_MTEST_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_MTEST_mtest_start_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_MTEST_mtest_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CTRL_MCLR_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CTRL_MCLR_mclr_start_START (0)
#define SOC_MDDRC_DMC_DDRC_CTRL_MCLR_mclr_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lp_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int lp_soft_en : 1;
        unsigned int lp_ack : 1;
        unsigned int reserved_1 : 2;
        unsigned int tlp_wakeup : 4;
        unsigned int tlp_resp : 4;
        unsigned int t_wcke : 4;
        unsigned int reserved_2 : 12;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_LP_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_en_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_soft_en_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_soft_en_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_ack_START (5)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_lp_ack_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_tlp_wakeup_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_tlp_wakeup_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_tlp_resp_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_tlp_resp_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_t_wcke_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_LP_t_wcke_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sref_cc : 1;
        unsigned int reserved_0 : 3;
        unsigned int sref_odis : 1;
        unsigned int reserved_1 : 3;
        unsigned int clk_switch : 1;
        unsigned int reserved_2 : 3;
        unsigned int sref_arefnum : 4;
        unsigned int reserved_3 : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SREF_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_cc_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_cc_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_odis_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_odis_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_clk_switch_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_clk_switch_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_arefnum_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_SREF_sref_arefnum_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int init_arefnum : 8;
        unsigned int wrlvl_en : 1;
        unsigned int reserved : 23;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_INIT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_INIT_init_arefnum_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_INIT_init_arefnum_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_INIT_wrlvl_en_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_INIT_wrlvl_en_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pd_en : 1;
        unsigned int reserved_0: 3;
        unsigned int pd_prd : 8;
        unsigned int pd_cc : 1;
        unsigned int reserved_1: 3;
        unsigned int pd_ac : 1;
        unsigned int reserved_2: 3;
        unsigned int t_clk_cke : 4;
        unsigned int reserved_3: 8;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_PD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_en_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_prd_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_prd_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_cc_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_cc_END (12)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_ac_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_pd_ac_END (16)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_t_clk_cke_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_PD_t_clk_cke_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aref_mode : 2;
        unsigned int reseverd : 2;
        unsigned int aref_alarm_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int aref_alarm_num : 8;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_AREF_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_mode_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_mode_END (1)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_reseverd_START (2)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_reseverd_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_alarm_en_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_AREF_aref_alarm_num_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ecc_en : 1;
        unsigned int reserved_0: 3;
        unsigned int eccwb_en : 1;
        unsigned int reserved_1: 3;
        unsigned int ecc_byp : 1;
        unsigned int reserved_2: 23;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_ECC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_ecc_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_ecc_en_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_eccwb_en_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_eccwb_en_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_ecc_byp_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_ECC_ecc_byp_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int err_inject_mode : 2;
        unsigned int reserved_0 : 2;
        unsigned int err_inject_bl : 9;
        unsigned int reserved_1 : 3;
        unsigned int err_inject_mask : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mode_END (1)
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_bl_END (12)
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_ERRINJ_err_inject_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sbram_err_inj : 2;
        unsigned int reserved_0 : 2;
        unsigned int rpram_err_inj : 2;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_sbram_err_inj_END (1)
#define SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_FIFO_ERRINJ_rpram_err_inj_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_ratio : 1;
        unsigned int cmd_clkon : 1;
        unsigned int data_clkon : 1;
        unsigned int func_clkon : 1;
        unsigned int apre_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int wrap_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int read_mode : 1;
        unsigned int hdr_mode : 1;
        unsigned int reserved_2 : 2;
        unsigned int dual_ch : 1;
        unsigned int reserved_3 : 3;
        unsigned int reorder_en : 1;
        unsigned int reserved_4 : 3;
        unsigned int exclu_en : 1;
        unsigned int reserved_5 : 3;
        unsigned int wr_rcv_mode : 1;
        unsigned int reserved_6 : 3;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_clk_ratio_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_START (1)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_cmd_clkon_END (1)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_START (2)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_data_clkon_END (2)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_START (3)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_func_clkon_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_apre_en_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_apre_en_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_wrap_en_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_read_mode_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_read_mode_END (12)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_START (13)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_hdr_mode_END (13)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_dual_ch_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_dual_ch_END (16)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_reorder_en_END (20)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_exclu_en_END (24)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_WORKMODE_wr_rcv_mode_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dram_type : 3;
        unsigned int reserved_0: 1;
        unsigned int mem_width : 2;
        unsigned int reserved_1: 2;
        unsigned int brstlen : 1;
        unsigned int reserved_2: 3;
        unsigned int bc_en : 1;
        unsigned int reserved_3: 3;
        unsigned int zqc_en : 1;
        unsigned int odt_on : 1;
        unsigned int reserved_4: 2;
        unsigned int rank : 2;
        unsigned int reserved_5: 10;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_dram_type_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_dram_type_END (2)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_mem_width_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_mem_width_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_brstlen_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_brstlen_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_bc_en_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_bc_en_END (12)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_zqc_en_END (16)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_odt_on_START (17)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_odt_on_END (17)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_rank_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRMODE_rank_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_mirror : 1;
        unsigned int reserved_0 : 3;
        unsigned int parity_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int cke_share_map : 2;
        unsigned int reserved_2 : 22;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_DIMM_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_addr_mirror_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_addr_mirror_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_parity_en_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_parity_en_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_cke_share_map_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_DIMM_cke_share_map_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_col : 3;
        unsigned int reserved_0: 1;
        unsigned int mem_row : 3;
        unsigned int reserved_1: 1;
        unsigned int mem_bank : 1;
        unsigned int reserved_2: 3;
        unsigned int mem_map : 2;
        unsigned int reserved_3: 18;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_col_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_col_END (2)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_row_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_row_END (6)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_bank_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_map_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_RNKVOL_mem_map_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mrs : 16;
        unsigned int emrs1 : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_EMRS01_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS01_mrs_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS01_mrs_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS01_emrs1_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS01_emrs1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emrs2 : 16;
        unsigned int emrs3 : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_EMRS23_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS23_emrs2_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS23_emrs2_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS23_emrs3_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_EMRS23_emrs3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tras : 6;
        unsigned int reserved : 2;
        unsigned int trc : 6;
        unsigned int trcd : 5;
        unsigned int trp : 5;
        unsigned int trrd : 4;
        unsigned int tmrd : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_tras_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_tras_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trc_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trc_END (13)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trcd_START (14)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trcd_END (18)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trp_START (19)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trp_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trrd_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_trrd_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_tmrd_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING0_tmrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trfc : 9;
        unsigned int reserved : 3;
        unsigned int tcl : 4;
        unsigned int twl : 4;
        unsigned int trtw : 4;
        unsigned int tsre : 8;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_trfc_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_trfc_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_tcl_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_tcl_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_twl_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_twl_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_trtw_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_trtw_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_tsre_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING1_tsre_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taref : 11;
        unsigned int reserved_0: 1;
        unsigned int tfaw : 6;
        unsigned int reserved_1: 6;
        unsigned int twtr : 4;
        unsigned int tcke : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_taref_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_taref_END (10)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_tfaw_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_tfaw_END (17)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_twtr_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_twtr_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_tcke_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING2_tcke_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trtp : 4;
        unsigned int txard : 4;
        unsigned int taond : 4;
        unsigned int tzqinit : 10;
        unsigned int tzq_prd : 10;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_trtp_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_trtp_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_txard_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_txard_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_taond_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_taond_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_tzqinit_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_tzqinit_END (21)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_START (22)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING3_tzq_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twlmrd : 6;
        unsigned int reserved_0: 2;
        unsigned int twldqsen : 6;
        unsigned int reserved_1: 2;
        unsigned int twlo : 4;
        unsigned int tmod : 5;
        unsigned int reserved_2: 7;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twlmrd_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twlmrd_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twldqsen_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twldqsen_END (13)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twlo_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_twlo_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_tmod_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING4_tmod_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twr : 5;
        unsigned int reserved_0: 3;
        unsigned int tzqcs : 8;
        unsigned int trnk2rnk : 4;
        unsigned int tdqsck : 3;
        unsigned int reserved_1: 1;
        unsigned int tdqsckmax : 3;
        unsigned int reserved_2: 1;
        unsigned int todt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_twr_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_twr_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tzqcs_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tzqcs_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_trnk2rnk_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tdqsck_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tdqsck_END (22)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_tdqsckmax_END (26)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_todt_ext_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING5_todt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcksre : 4;
        unsigned int tcksrx : 4;
        unsigned int todt_sft : 4;
        unsigned int reseverd : 20;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMING6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_tcksre_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_tcksre_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_tcksrx_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_tcksrx_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_todt_sft_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_todt_sft_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_reseverd_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMING6_reseverd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tras : 6;
        unsigned int reserved : 2;
        unsigned int trc : 6;
        unsigned int trcd : 5;
        unsigned int trp : 5;
        unsigned int trrd : 4;
        unsigned int tmrd : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_tras_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trc_END (13)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_START (14)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trcd_END (18)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_START (19)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trp_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_trrd_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING0_tmrd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trfc : 9;
        unsigned int reserved : 3;
        unsigned int tcl : 4;
        unsigned int twl : 4;
        unsigned int trtw : 4;
        unsigned int tsre : 8;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_trfc_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_trfc_END (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_tcl_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_twl_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_trtw_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING1_tsre_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int taref : 11;
        unsigned int reserved_0: 1;
        unsigned int tfaw : 6;
        unsigned int reserved_1: 6;
        unsigned int twtr : 4;
        unsigned int tcke : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_taref_END (10)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_tfaw_END (17)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_twtr_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING2_tcke_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int trtp : 4;
        unsigned int txard : 4;
        unsigned int taond : 4;
        unsigned int tzqinit : 10;
        unsigned int tzq_prd : 10;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_trtp_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_txard_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_taond_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_tzqinit_END (21)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_START (22)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING3_tzq_prd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twlmrd : 6;
        unsigned int reserved_0: 2;
        unsigned int twldqsen : 6;
        unsigned int reserved_1: 2;
        unsigned int twlo : 4;
        unsigned int tmod : 5;
        unsigned int reserved_2: 7;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twlmrd_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twlmrd_END (5)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twldqsen_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twldqsen_END (13)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_twlo_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING4_tmod_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int twr : 5;
        unsigned int reserved_0: 3;
        unsigned int tzqcs : 8;
        unsigned int trnk2rnk : 4;
        unsigned int tdqsck : 3;
        unsigned int reserved_1: 1;
        unsigned int tdqsckmax : 3;
        unsigned int reserved_2: 1;
        unsigned int todt_ext : 3;
        unsigned int reserved_3: 1;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_twr_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tzqcs_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_trnk2rnk_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsck_END (22)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_tdqsckmax_END (26)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_todt_ext_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING5_todt_ext_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tcksre : 4;
        unsigned int tcksrx : 4;
        unsigned int todt_sft : 4;
        unsigned int reseverd : 20;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksre_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_tcksrx_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_todt_sft_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_reseverd_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_NXT_TIMING6_reseverd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bl_data : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_BLDATA_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_BLDATA_bl_data_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_BLDATA_bl_data_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wodt0 : 4;
        unsigned int wodt1 : 4;
        unsigned int wodt2 : 4;
        unsigned int wodt3 : 4;
        unsigned int rodt0 : 4;
        unsigned int rodt1 : 4;
        unsigned int rodt2 : 4;
        unsigned int rodt3 : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_ODT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt0_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt0_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt1_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt1_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt2_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt2_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt3_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_wodt3_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt0_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt0_END (19)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt1_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt1_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt2_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt2_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt3_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_ODT_rodt3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int que_level : 5;
        unsigned int reserved_0 : 3;
        unsigned int mbist_que_level : 5;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_que_level_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_que_level_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_DMCLVL_mbist_que_level_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timeout_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timeout_level : 4;
        unsigned int timeout0 : 10;
        unsigned int reserved_1 : 2;
        unsigned int timeout1 : 10;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout_en_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout_level_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout0_END (17)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_START (20)
#define SOC_MDDRC_DMC_DDRC_CFG_TIMEOUT_timeout1_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ageprd : 4;
        unsigned int priadpt : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_QOS_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_QOS_ageprd_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_QOS_ageprd_END (3)
#define SOC_MDDRC_DMC_DDRC_CFG_QOS_priadpt_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_QOS_priadpt_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mbist_top_addr : 28;
        unsigned int mbist_rank : 2;
        unsigned int reserved : 2;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MBIST_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MBIST_mbist_top_addr_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_MBIST_mbist_rank_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_MBIST_mbist_rank_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN0_mclr_pattern0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN1_mclr_pattern1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN2_mclr_pattern2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN3_mclr_pattern3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mclr_pattern4 : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_MCLR_PATTERN4_mclr_pattern4_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int train_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_TRAIN_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_TRAIN_train_en_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_TRAIN_train_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rcv_pdr : 1;
        unsigned int reserved_0: 3;
        unsigned int phy_zqen : 1;
        unsigned int reserved_1: 3;
        unsigned int trdlat : 4;
        unsigned int phy_upden : 1;
        unsigned int reserved_2: 19;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_rcv_pdr_END (0)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_phy_zqen_END (4)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_trdlat_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_trdlat_END (11)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_START (12)
#define SOC_MDDRC_DMC_DDRC_CFG_DDRPHY_phy_upden_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_type : 3;
        unsigned int reserved : 1;
        unsigned int cmd_rank : 4;
        unsigned int cmd_ma : 8;
        unsigned int cmd_mrs : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_type_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_type_END (2)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_rank_START (4)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_rank_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_ma_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_ma_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_mrs_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_cmd_mrs_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sfc_col : 16;
        unsigned int sfc_row : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_col_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_col_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_row_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR0_sfc_row_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sfc_bank : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_bank_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_ADDR1_sfc_bank_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA0_wdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA1_wdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA2_wdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA3_wdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA4_wdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA5_wdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA6_wdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA7_wdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdata_ecc0 : 8;
        unsigned int wdata_ecc1 : 8;
        unsigned int wdata_ecc2 : 8;
        unsigned int wdata_ecc3 : 8;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc0_END (7)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_START (8)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc1_END (15)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_START (16)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc2_END (23)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_START (24)
#define SOC_MDDRC_DMC_DDRC_CFG_SFC_WDATA_ECC_wdata_ecc3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perf_prd : 28;
        unsigned int perf_mode : 1;
        unsigned int flux_en : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_PERF_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_perf_prd_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_perf_prd_END (27)
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_perf_mode_START (28)
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_perf_mode_END (28)
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_flux_en_START (29)
#define SOC_MDDRC_DMC_DDRC_CFG_PERF_flux_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sta_id : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_STAID_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_STAID_sta_id_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_STAID_sta_id_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sta_idmask : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CFG_STAIDMSK_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_START (0)
#define SOC_MDDRC_DMC_DDRC_CFG_STAIDMSK_sta_idmask_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_int_mask : 1;
        unsigned int flux_int_mask : 1;
        unsigned int reserved_0 : 2;
        unsigned int merr_int_mask : 1;
        unsigned int sref_err_int_mask : 1;
        unsigned int reserved_1 : 2;
        unsigned int dimm_parity_int_mask : 1;
        unsigned int reserved_2 : 3;
        unsigned int rdtimeout_int_mask : 1;
        unsigned int reserved_3 : 3;
        unsigned int aref_alarm_int_mask : 1;
        unsigned int reserved_4 : 3;
        unsigned int sbram_serr_int_mask : 1;
        unsigned int reserved_5 : 3;
        unsigned int sbram_merr_int_mask : 1;
        unsigned int reserved_6 : 3;
        unsigned int rpram_serr_int_mask : 1;
        unsigned int reserved_7 : 2;
        unsigned int rpram_merr_int_mask : 1;
    } reg;
} SOC_MDDRC_DMC_DDRC_INTMSK_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_INTMSK_serr_int_mask_START (0)
#define SOC_MDDRC_DMC_DDRC_INTMSK_serr_int_mask_END (0)
#define SOC_MDDRC_DMC_DDRC_INTMSK_flux_int_mask_START (1)
#define SOC_MDDRC_DMC_DDRC_INTMSK_flux_int_mask_END (1)
#define SOC_MDDRC_DMC_DDRC_INTMSK_merr_int_mask_START (4)
#define SOC_MDDRC_DMC_DDRC_INTMSK_merr_int_mask_END (4)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sref_err_int_mask_START (5)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sref_err_int_mask_END (5)
#define SOC_MDDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_START (8)
#define SOC_MDDRC_DMC_DDRC_INTMSK_dimm_parity_int_mask_END (8)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_START (12)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rdtimeout_int_mask_END (12)
#define SOC_MDDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_START (16)
#define SOC_MDDRC_DMC_DDRC_INTMSK_aref_alarm_int_mask_END (16)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_START (20)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sbram_serr_int_mask_END (20)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_START (24)
#define SOC_MDDRC_DMC_DDRC_INTMSK_sbram_merr_int_mask_END (24)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_START (28)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rpram_serr_int_mask_END (28)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_START (31)
#define SOC_MDDRC_DMC_DDRC_INTMSK_rpram_merr_int_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rint : 1;
        unsigned int flux_rint : 1;
        unsigned int reserved_0 : 2;
        unsigned int merr_rint : 1;
        unsigned int sref_err_rint : 1;
        unsigned int reserved_1 : 2;
        unsigned int dimm_parity_rint : 1;
        unsigned int reserved_2 : 3;
        unsigned int rdtimeout_rint : 1;
        unsigned int reserved_3 : 3;
        unsigned int aref_alarm_rint : 1;
        unsigned int reserved_4 : 3;
        unsigned int sbram_serr_rint : 1;
        unsigned int reserved_5 : 3;
        unsigned int sbram_merr_rint : 1;
        unsigned int reserved_6 : 3;
        unsigned int rpram_serr_rint : 1;
        unsigned int reserved_7 : 2;
        unsigned int rpram_merr_rint : 1;
    } reg;
} SOC_MDDRC_DMC_DDRC_RINT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_RINT_serr_rint_START (0)
#define SOC_MDDRC_DMC_DDRC_RINT_serr_rint_END (0)
#define SOC_MDDRC_DMC_DDRC_RINT_flux_rint_START (1)
#define SOC_MDDRC_DMC_DDRC_RINT_flux_rint_END (1)
#define SOC_MDDRC_DMC_DDRC_RINT_merr_rint_START (4)
#define SOC_MDDRC_DMC_DDRC_RINT_merr_rint_END (4)
#define SOC_MDDRC_DMC_DDRC_RINT_sref_err_rint_START (5)
#define SOC_MDDRC_DMC_DDRC_RINT_sref_err_rint_END (5)
#define SOC_MDDRC_DMC_DDRC_RINT_dimm_parity_rint_START (8)
#define SOC_MDDRC_DMC_DDRC_RINT_dimm_parity_rint_END (8)
#define SOC_MDDRC_DMC_DDRC_RINT_rdtimeout_rint_START (12)
#define SOC_MDDRC_DMC_DDRC_RINT_rdtimeout_rint_END (12)
#define SOC_MDDRC_DMC_DDRC_RINT_aref_alarm_rint_START (16)
#define SOC_MDDRC_DMC_DDRC_RINT_aref_alarm_rint_END (16)
#define SOC_MDDRC_DMC_DDRC_RINT_sbram_serr_rint_START (20)
#define SOC_MDDRC_DMC_DDRC_RINT_sbram_serr_rint_END (20)
#define SOC_MDDRC_DMC_DDRC_RINT_sbram_merr_rint_START (24)
#define SOC_MDDRC_DMC_DDRC_RINT_sbram_merr_rint_END (24)
#define SOC_MDDRC_DMC_DDRC_RINT_rpram_serr_rint_START (28)
#define SOC_MDDRC_DMC_DDRC_RINT_rpram_serr_rint_END (28)
#define SOC_MDDRC_DMC_DDRC_RINT_rpram_merr_rint_START (31)
#define SOC_MDDRC_DMC_DDRC_RINT_rpram_merr_rint_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_intsts : 1;
        unsigned int flux_intsts : 1;
        unsigned int reservd : 2;
        unsigned int merr_intsts : 1;
        unsigned int sref_err_intsts : 1;
        unsigned int reserved_0 : 2;
        unsigned int dimm_parity_intsts : 1;
        unsigned int reserved_1 : 3;
        unsigned int rdtimeout_intsts : 1;
        unsigned int reserved_2 : 3;
        unsigned int aref_alarm_intsts : 1;
        unsigned int reserved_3 : 3;
        unsigned int sbram_serr_intsts : 1;
        unsigned int reserved_4 : 3;
        unsigned int sbram_merr_intsts : 1;
        unsigned int reserved_5 : 3;
        unsigned int rpram_serr_intsts : 1;
        unsigned int reserved_6 : 2;
        unsigned int rpram_merr_intsts : 1;
    } reg;
} SOC_MDDRC_DMC_DDRC_INTSTS_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_INTSTS_serr_intsts_START (0)
#define SOC_MDDRC_DMC_DDRC_INTSTS_serr_intsts_END (0)
#define SOC_MDDRC_DMC_DDRC_INTSTS_flux_intsts_START (1)
#define SOC_MDDRC_DMC_DDRC_INTSTS_flux_intsts_END (1)
#define SOC_MDDRC_DMC_DDRC_INTSTS_reservd_START (2)
#define SOC_MDDRC_DMC_DDRC_INTSTS_reservd_END (3)
#define SOC_MDDRC_DMC_DDRC_INTSTS_merr_intsts_START (4)
#define SOC_MDDRC_DMC_DDRC_INTSTS_merr_intsts_END (4)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sref_err_intsts_START (5)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sref_err_intsts_END (5)
#define SOC_MDDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_START (8)
#define SOC_MDDRC_DMC_DDRC_INTSTS_dimm_parity_intsts_END (8)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_START (12)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rdtimeout_intsts_END (12)
#define SOC_MDDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_START (16)
#define SOC_MDDRC_DMC_DDRC_INTSTS_aref_alarm_intsts_END (16)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_START (20)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sbram_serr_intsts_END (20)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_START (24)
#define SOC_MDDRC_DMC_DDRC_INTSTS_sbram_merr_intsts_END (24)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_START (28)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rpram_serr_intsts_END (28)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_START (31)
#define SOC_MDDRC_DMC_DDRC_INTSTS_rpram_merr_intsts_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved_0: 3;
        unsigned int busy_dmc : 1;
        unsigned int reserved_1: 3;
        unsigned int busy_func : 1;
        unsigned int reserved_2: 23;
    } reg;
} SOC_MDDRC_DMC_DDRC_CURR_STATUS_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_START (0)
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_END (0)
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_dmc_START (4)
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_dmc_END (4)
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_func_START (8)
#define SOC_MDDRC_DMC_DDRC_CURR_STATUS_busy_func_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int in_sref : 1;
        unsigned int reserved_0: 3;
        unsigned int in_init : 1;
        unsigned int reserved_1: 3;
        unsigned int in_pd : 4;
        unsigned int in_sfc : 1;
        unsigned int reserved_2: 3;
        unsigned int in_eccwb : 1;
        unsigned int reserved_3: 3;
        unsigned int in_mtest : 1;
        unsigned int reserved_4: 3;
        unsigned int in_mclr : 1;
        unsigned int reserved_5: 3;
        unsigned int in_phyupd : 1;
        unsigned int reserved_6: 3;
    } reg;
} SOC_MDDRC_DMC_DDRC_CURR_FUNC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_sref_START (0)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_sref_END (0)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_init_START (4)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_init_END (4)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_pd_START (8)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_pd_END (11)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_sfc_START (12)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_sfc_END (12)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_eccwb_START (16)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_eccwb_END (16)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_mtest_START (20)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_mtest_END (20)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_mclr_START (24)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_mclr_END (24)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_phyupd_START (28)
#define SOC_MDDRC_DMC_DDRC_CURR_FUNC_in_phyupd_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cv : 16;
        unsigned int dmc_ct : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_CURR_EXECST_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CURR_EXECST_dmc_cv_START (0)
#define SOC_MDDRC_DMC_DDRC_CURR_EXECST_dmc_cv_END (15)
#define SOC_MDDRC_DMC_DDRC_CURR_EXECST_dmc_ct_START (16)
#define SOC_MDDRC_DMC_DDRC_CURR_EXECST_dmc_ct_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wgntfifo_e : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_MDDRC_DMC_DDRC_CURR_WGFIFOST_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_START (0)
#define SOC_MDDRC_DMC_DDRC_CURR_WGFIFOST_wgntfifo_e_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_adr0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR0_serr_adr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_adr1 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_ADR1_serr_adr1_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA0_serr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA1_serr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA2_serr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA3_serr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA4_serr_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA5_serr_rdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA6_serr_rdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA7_serr_rdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_rdata8 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_RDATA8_serr_rdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA0_serr_expdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA1_serr_expdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA2_serr_expdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA3_serr_expdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA4_serr_expdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA5_serr_expdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA6_serr_expdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA7_serr_expdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_expdata8 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERR_EXPDATA8_serr_expdata8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_adr0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR0_merr_adr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_adr1 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ADR1_merr_adr1_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_id : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_ID_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ID_merr_id_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_ID_merr_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA0_merr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA1_merr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA2_merr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA3_merr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA4_merr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA5_merr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA6_merr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA7_merr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_RDATA8_merr_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA0_merr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA1_merr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA2_merr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA3_merr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA4_merr_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA5_merr_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA6_merr_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA7_merr_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_rdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_rdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERR_EXPDATA8_merr_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int serr_cnt : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SERRCNT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SERRCNT_serr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int merr_cnt : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MERRCNT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MERRCNT_merr_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_wr : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUX_WR_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WR_flux_wr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_rd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUX_RD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RD_flux_rd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_wr_cmd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUX_WCMD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_WCMD_flux_wr_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int flux_rd_cmd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUX_RCMD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUX_RCMD_flux_rd_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_wr : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WR_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WR_fluxid_wr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_rd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RD_fluxid_rd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_wr_cmd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WCMD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_WCMD_fluxid_wr_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fluxid_rd_cmd : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RCMD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_FLUXID_RCMD_fluxid_rd_cmd_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatcnt_min : 16;
        unsigned int wlatcnt_max : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_min_END (15)
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_START (16)
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT0_wlatcnt_max_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatcnt_all : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_WLATCNT1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_WLATCNT1_wlatcnt_all_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatcnt_min : 16;
        unsigned int rlatcnt_max : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_min_END (15)
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_START (16)
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT0_rlatcnt_max_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatcnt_all : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_RLATCNT1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_RLATCNT1_rlatcnt_all_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inhere_rlatcnt : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_INHERE_RLAT_CNT_inhere_rlatcnt_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dmc_cmd_sum : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_CMD_SUM_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_CMD_SUM_dmc_cmd_sum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err : 1;
        unsigned int reserved_0 : 3;
        unsigned int mtest_bg_cnt : 4;
        unsigned int mtest_element : 3;
        unsigned int reserved_1 : 21;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_err_END (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_START (4)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_bg_cnt_END (7)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_START (8)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERR_INFO_mtest_element_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_addr : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRADDR_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRADDR_mtest_err_addr_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA0_mtest_exp_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA1_mtest_exp_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA2_mtest_exp_data2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA3_mtest_exp_data3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA4_mtest_exp_data4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA5_mtest_exp_data5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA6_mtest_exp_data6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA7_mtest_exp_data7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data8 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA8_mtest_exp_data8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data9 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA9_mtest_exp_data9_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data10 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA10_mtest_exp_data10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data11 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA11_mtest_exp_data11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data12 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA12_mtest_exp_data12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data13 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA13_mtest_exp_data13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data14 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA14_mtest_exp_data14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data15 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA15_mtest_exp_data15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data16 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA16_mtest_exp_data16_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_exp_data17 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_EXPDATA17_mtest_exp_data17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA0_mtest_err_data0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA1_mtest_err_data1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA2_mtest_err_data2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA3_mtest_err_data3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA4_mtest_err_data4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA5_mtest_err_data5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA6_mtest_err_data6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA7_mtest_err_data7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data8 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA8_mtest_err_data8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data9 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA9_mtest_err_data9_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data10 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA10_mtest_err_data10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data11 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA11_mtest_err_data11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data12 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA12_mtest_err_data12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data13 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA13_mtest_err_data13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data14 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA14_mtest_err_data14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data15 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA15_mtest_err_data15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data16 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA16_mtest_err_data16_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtest_err_data17 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_MTEST_ERRDATA17_mtest_err_data17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata0 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA0_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA0_rdata0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata1 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA1_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA1_rdata1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata2 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA2_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA2_rdata2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata3 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA3_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA3_rdata3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata4 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA4_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA4_rdata4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata5 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA5_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA5_rdata5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata6 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA6_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA6_rdata6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata7 : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA7_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA7_rdata7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdata_ecc0 : 8;
        unsigned int rdata_ecc1 : 8;
        unsigned int rdata_ecc2 : 8;
        unsigned int rdata_ecc3 : 8;
    } reg;
} SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_START (0)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc0_END (7)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_START (8)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc1_END (15)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_START (16)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc2_END (23)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_START (24)
#define SOC_MDDRC_DMC_DDRC_HIS_SFC_RDATA_ECC_rdata_ecc3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE0_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE0_ST_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE1_ST_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_GENPOSE2_ST_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ram_tmod : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_MDDRC_DMC_DDRC_TEST_RAM_TMOD_UNION;
#endif
#define SOC_MDDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_START (0)
#define SOC_MDDRC_DMC_DDRC_TEST_RAM_TMOD_ram_tmod_END (8)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

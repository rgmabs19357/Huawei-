#ifndef __SOC_SCTRL_INTERFACE_H__
#define __SOC_SCTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL1_ADDR(base) ((base) + (0x0DC))
#define SOC_SCTRL_SC_PERIPH_CTRL2_ADDR(base) ((base) + (0x0E0))
#define SOC_SCTRL_SC_PERIPH_CTRL3_ADDR(base) ((base) + (0x0E4))
#define SOC_SCTRL_SC_PERIPH_CTRL4_ADDR(base) ((base) + (0x0E8))
#define SOC_SCTRL_SC_PERIPH_CTRL5_ADDR(base) ((base) + (0x0EC))
#define SOC_SCTRL_SC_PERIPH_CTRL6_ADDR(base) ((base) + (0x0F0))
#define SOC_SCTRL_SC_PERIPH_CTRL12_ADDR(base) ((base) + (0x0F4))
#define SOC_SCTRL_SC_PERIPH_CTRL13_ADDR(base) ((base) + (0x0F8))
#define SOC_SCTRL_SC_PERIPH_CTRL14_ADDR(base) ((base) + (0x0FC))
#define SOC_SCTRL_SC_PERIPH_CTRL15_ADDR(base) ((base) + (0x100))
#define SOC_SCTRL_SC_PERIPH_CTRL16_ADDR(base) ((base) + (0x104))
#define SOC_SCTRL_SC_PERIPH_STAT0_ADDR(base) ((base) + (0x108))
#define SOC_SCTRL_SC_PERIPH_STAT1_ADDR(base) ((base) + (0x10C))
#define SOC_SCTRL_SC_DDR_CTRL0_ADDR(base) ((base) + (0x124))
#define SOC_SCTRL_SC_DDR_CTRL1_ADDR(base) ((base) + (0x130))
#define SOC_SCTRL_SC_DDR_CTRL2_ADDR(base) ((base) + (0x134))
#define SOC_SCTRL_SC_DDR_CTRL3_ADDR(base) ((base) + (0x138))
#define SOC_SCTRL_SC_DDR_CTRL4_ADDR(base) ((base) + (0x13C))
#define SOC_SCTRL_SC_PERIPH_STAT2_ADDR(base) ((base) + (0x140))
#define SOC_SCTRL_SC_PERIPH_STAT3_ADDR(base) ((base) + (0x144))
#define SOC_SCTRL_SC_PERIPH_STAT4_ADDR(base) ((base) + (0x148))
#define SOC_SCTRL_SC_PERIPH_STAT6_ADDR(base) ((base) + (0x150))
#define SOC_SCTRL_SC_PERIPH_CTRL8_ADDR(base) ((base) + (0x164))
#define SOC_SCTRL_SC_PERIPH_CTRL9_ADDR(base) ((base) + (0x168))
#define SOC_SCTRL_SC_PERIPH_CTRL10_ADDR(base) ((base) + (0x16C))
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_ADDR(base) ((base) + (0x180))
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_ADDR(base) ((base) + (0x190))
#define SOC_SCTRL_SC_DSP_SUBSYS_STAT0_ADDR(base) ((base) + (0x194))
#define SOC_SCTRL_SC_ACPU_CTRL0_ADDR(base) ((base) + (0x200))
#define SOC_SCTRL_SC_ACPU_CTRL1_ADDR(base) ((base) + (0x204))
#define SOC_SCTRL_SC_ACPU_CTRL2_ADDR(base) ((base) + (0x208))
#define SOC_SCTRL_SC_ACPU_CTRL3_ADDR(base) ((base) + (0x20C))
#define SOC_SCTRL_SC_ACPU_CTRL4_ADDR(base) ((base) + (0x210))
#define SOC_SCTRL_SC_ACPU_CTRL5_ADDR(base) ((base) + (0x214))
#define SOC_SCTRL_SC_ACPU_CTRL6_ADDR(base) ((base) + (0x218))
#define SOC_SCTRL_SC_ACPU_CTRL7_ADDR(base) ((base) + (0x21C))
#define SOC_SCTRL_SC_ACPU_CPURSTEN_ADDR(base) ((base) + (0x220))
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_ADDR(base) ((base) + (0x224))
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_ADDR(base) ((base) + (0x228))
#define SOC_SCTRL_SC_ACPU_CPUCFG_ADDR(base) ((base) + (0x240))
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_ADDR(base) ((base) + (0x244))
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_ADDR(base) ((base) + (0x248))
#define SOC_SCTRL_SCCPUCOREEN_ADDR(base) ((base) + (0x250))
#define SOC_SCTRL_SCCPUCOREDIS_ADDR(base) ((base) + (0x254))
#define SOC_SCTRL_SCCPUCORESTAT_ADDR(base) ((base) + (0x258))
#define SOC_SCTRL_SC_ACPU_STAT0_ADDR(base) ((base) + (0x268))
#define SOC_SCTRL_SC_ACPU_STAT1_ADDR(base) ((base) + (0x26C))
#define SOC_SCTRL_SC_CARM_CTRL0_ADDR(base) ((base) + (0x280))
#define SOC_SCTRL_SC_CARM_CTRL1_ADDR(base) ((base) + (0x284))
#define SOC_SCTRL_SC_CARM_STAT0_ADDR(base) ((base) + (0x290))
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_ADDR(base) ((base) + (0x300))
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_ADDR(base) ((base) + (0x304))
#define SOC_SCTRL_SC_AUTO_CLK_GATE0_ADDR(base) ((base) + (0x308))
#define SOC_SCTRL_SC_AUTO_CLK_GATE1_ADDR(base) ((base) + (0x30C))
#define SOC_SCTRL_SC_RESERVED7_ADDR(base) ((base) + (0x358))
#define SOC_SCTRL_SC_RESERVED8_ADDR(base) ((base) + (0x35C))
#define SOC_SCTRL_SC_PeriphAxi_priority_set_ADDR(base) ((base) + (0x360))
#define SOC_SCTRL_SC_SystemAxi_mst_priority_set_ADDR(base) ((base) + (0x364))
#define SOC_SCTRL_SC_SystemAxi_slv_priority_set_ADDR(base) ((base) + (0x368))
#define SOC_SCTRL_SC_MPeriph_mst_priority_set_ADDR(base) ((base) + (0x36C))
#define SOC_SCTRL_SC_MPeriph_slv_priority_set_ADDR(base) ((base) + (0x370))
#define SOC_SCTRL_SC_RESERVED16_ADDR(base) ((base) + (0x374))
#define SOC_SCTRL_SC_RESERVED17_ADDR(base) ((base) + (0x378))
#define SOC_SCTRL_SC_RESERVED18_ADDR(base) ((base) + (0x37C))
#define SOC_SCTRL_SC_RESERVED21_ADDR(base) ((base) + (0x380))
#define SOC_SCTRL_SC_RESERVED22_ADDR(base) ((base) + (0x384))
#define SOC_SCTRL_SC_RESERVED23_ADDR(base) ((base) + (0x388))
#define SOC_SCTRL_SC_RESERVED24_ADDR(base) ((base) + (0x38C))
#define SOC_SCTRL_SC_RESERVED25_ADDR(base) ((base) + (0x390))
#define SOC_SCTRL_SC_RESERVED26_ADDR(base) ((base) + (0x394))
#define SOC_SCTRL_SC_RESERVED27_ADDR(base) ((base) + (0x398))
#define SOC_SCTRL_SC_RESERVED28_ADDR(base) ((base) + (0x39C))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL0_ADDR(base) ((base) + (0x500))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_ADDR(base) ((base) + (0x504))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_ADDR(base) ((base) + (0x508))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_ADDR(base) ((base) + (0x50C))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_ADDR(base) ((base) + (0x510))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_ADDR(base) ((base) + (0x514))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL6_ADDR(base) ((base) + (0x518))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_ADDR(base) ((base) + (0x51C))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT0_ADDR(base) ((base) + (0x540))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_ADDR(base) ((base) + (0x544))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT2_ADDR(base) ((base) + (0x548))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT3_ADDR(base) ((base) + (0x54C))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT4_ADDR(base) ((base) + (0x550))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_ADDR(base) ((base) + (0x554))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT6_ADDR(base) ((base) + (0x558))
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT7_ADDR(base) ((base) + (0x55C))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ADDR(base) ((base) + (0x580))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_ADDR(base) ((base) + (0x584))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_ADDR(base) ((base) + (0x588))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_ADDR(base) ((base) + (0x58C))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_ADDR(base) ((base) + (0x590))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT1_ADDR(base) ((base) + (0x594))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT2_ADDR(base) ((base) + (0x598))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT3_ADDR(base) ((base) + (0x59C))
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT4_ADDR(base) ((base) + (0x5A4))
#define SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(base) ((base) + (0x600))
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_ADDR(base) ((base) + (0x604))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_ADDR(base) ((base) + (0x608))
#define SOC_SCTRL_SC_PERIPH_CLKEN1_ADDR(base) ((base) + (0x60C))
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_ADDR(base) ((base) + (0x610))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_ADDR(base) ((base) + (0x614))
#define SOC_SCTRL_SC_PERIPH_CLKEN2_ADDR(base) ((base) + (0x618))
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_ADDR(base) ((base) + (0x61C))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_ADDR(base) ((base) + (0x620))
#define SOC_SCTRL_SC_PERIPH_CLKEN3_ADDR(base) ((base) + (0x624))
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_ADDR(base) ((base) + (0x628))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_ADDR(base) ((base) + (0x62C))
#define SOC_SCTRL_SC_PERIPH_CLKEN8_ADDR(base) ((base) + (0x660))
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_ADDR(base) ((base) + (0x664))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_ADDR(base) ((base) + (0x668))
#define SOC_SCTRL_SC_PERIPH_CLKEN9_ADDR(base) ((base) + (0x66C))
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_ADDR(base) ((base) + (0x670))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_ADDR(base) ((base) + (0x674))
#define SOC_SCTRL_SC_PERIPH_CLKEN10_ADDR(base) ((base) + (0x678))
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_ADDR(base) ((base) + (0x67C))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_ADDR(base) ((base) + (0x680))
#define SOC_SCTRL_SC_PERIPH_CLKEN11_ADDR(base) ((base) + (0x684))
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_ADDR(base) ((base) + (0x688))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_ADDR(base) ((base) + (0x68C))
#define SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(base) ((base) + (0x690))
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_ADDR(base) ((base) + (0x694))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_ADDR(base) ((base) + (0x698))
#define SOC_SCTRL_SC_PERIPH_CLKEN13_ADDR(base) ((base) + (0x6A0))
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_ADDR(base) ((base) + (0x6A4))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_ADDR(base) ((base) + (0x6A8))
#define SOC_SCTRL_SC_PERIPH_CLKEN14_ADDR(base) ((base) + (0x6B0))
#define SOC_SCTRL_SC_PERIPH_CLKDIS14_ADDR(base) ((base) + (0x6B4))
#define SOC_SCTRL_SC_PERIPH_CLKSTAT14_ADDR(base) ((base) + (0x6B8))
#define SOC_SCTRL_SC_PERIPH_RSTEN0_ADDR(base) ((base) + (0x6C0))
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_ADDR(base) ((base) + (0x6C4))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_ADDR(base) ((base) + (0x6C8))
#define SOC_SCTRL_SC_PERIPH_RSTEN1_ADDR(base) ((base) + (0x6CC))
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_ADDR(base) ((base) + (0x6D0))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_ADDR(base) ((base) + (0x6D4))
#define SOC_SCTRL_SC_PERIPH_RSTEN2_ADDR(base) ((base) + (0x6D8))
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_ADDR(base) ((base) + (0x6DC))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_ADDR(base) ((base) + (0x6E0))
#define SOC_SCTRL_SC_PERIPH_RSTEN3_ADDR(base) ((base) + (0x6E4))
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_ADDR(base) ((base) + (0x6E8))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_ADDR(base) ((base) + (0x6EC))
#define SOC_SCTRL_SC_PERIPH_RSTEN6_ADDR(base) ((base) + (0x708))
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_ADDR(base) ((base) + (0x70C))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_ADDR(base) ((base) + (0x710))
#define SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(base) ((base) + (0x714))
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(base) ((base) + (0x718))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_ADDR(base) ((base) + (0x71C))
#define SOC_SCTRL_SC_PERIPH_RSTEN8_ADDR(base) ((base) + (0x724))
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_ADDR(base) ((base) + (0x728))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_ADDR(base) ((base) + (0x72C))
#define SOC_SCTRL_SC_PERIPH_RSTEN9_ADDR(base) ((base) + (0x734))
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_ADDR(base) ((base) + (0x738))
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_ADDR(base) ((base) + (0x73C))
#define SOC_SCTRL_SC_G3D_RASTER_ADDR(base) ((base) + (0xA00))
#define SOC_SCTRL_SC_TEMP0_LAG_ADDR(base) ((base) + (0xAC4))
#define SOC_SCTRL_SC_TEMP0_TH_ADDR(base) ((base) + (0xAC8))
#define SOC_SCTRL_SC_TEMP0_RST_TH_ADDR(base) ((base) + (0xACC))
#define SOC_SCTRL_SC_TEMP0_CFG_ADDR(base) ((base) + (0xAD0))
#define SOC_SCTRL_SC_TEMP0_EN_ADDR(base) ((base) + (0xAD4))
#define SOC_SCTRL_SC_TEMP0_INT_MSK_ADDR(base) ((base) + (0xAD8))
#define SOC_SCTRL_SC_TEMP0_INT_CLR_ADDR(base) ((base) + (0xADC))
#define SOC_SCTRL_SC_TEMP0_RST_MSK_ADDR(base) ((base) + (0xAE0))
#define SOC_SCTRL_SC_TEMP0_RAW_INT_ADDR(base) ((base) + (0xAE4))
#define SOC_SCTRL_SC_TEMP0_MSK_INT_ADDR(base) ((base) + (0xAE8))
#define SOC_SCTRL_SC_TEMP0_VALUE_ADDR(base) ((base) + (0xAEC))
#define SOC_SCTRL_SC_TEMP1_LAG_ADDR(base) ((base) + (0xBC4))
#define SOC_SCTRL_SC_TEMP1_TH_ADDR(base) ((base) + (0xBC8))
#define SOC_SCTRL_SC_TEMP1_RST_TH_ADDR(base) ((base) + (0xBCC))
#define SOC_SCTRL_SC_TEMP1_CFG_ADDR(base) ((base) + (0xBD0))
#define SOC_SCTRL_SC_TEMP1_EN_ADDR(base) ((base) + (0xBD4))
#define SOC_SCTRL_SC_TEMP1_INT_MSK_ADDR(base) ((base) + (0xBD8))
#define SOC_SCTRL_SC_TEMP1_INT_CLR_ADDR(base) ((base) + (0xBDC))
#define SOC_SCTRL_SC_TEMP1_RST_MSK_ADDR(base) ((base) + (0xBE0))
#define SOC_SCTRL_SC_TEMP1_RAW_INT_ADDR(base) ((base) + (0xBE4))
#define SOC_SCTRL_SC_TEMP1_MSK_INT_ADDR(base) ((base) + (0xBE8))
#define SOC_SCTRL_SC_TEMP1_VALUE_ADDR(base) ((base) + (0xBEC))
#define SOC_SCTRL_SC_CLK_SEL0_ADDR(base) ((base) + (0xC48))
#define SOC_SCTRL_SC_CLK_SEL1_ADDR(base) ((base) + (0xC4C))
#define SOC_SCTRL_SC_CLKCFGALL0_ADDR(base) ((base) + (0xC80))
#define SOC_SCTRL_SC_CLKCFGALL1_ADDR(base) ((base) + (0xC84))
#define SOC_SCTRL_SC_CLKCFGALL2_ADDR(base) ((base) + (0xC88))
#define SOC_SCTRL_SC_CLKCFGALL3_ADDR(base) ((base) + (0xC8C))
#define SOC_SCTRL_SC_CLKCFGALL4_ADDR(base) ((base) + (0xC90))
#define SOC_SCTRL_SC_CLKCFGALL5_ADDR(base) ((base) + (0xC94))
#define SOC_SCTRL_SC_CLKCFG8BIT0_ADDR(base) ((base) + (0xCA4))
#define SOC_SCTRL_SC_CLKCFG8BIT1_ADDR(base) ((base) + (0xCA8))
#define SOC_SCTRL_SC_CLKCFG8BIT2_ADDR(base) ((base) + (0xCAC))
#define SOC_SCTRL_SC_CLKCFG8BIT3_ADDR(base) ((base) + (0xCB0))
#define SOC_SCTRL_SC_CLKCFG8BIT4_ADDR(base) ((base) + (0xCB4))
#define SOC_SCTRL_SC_CLKCFG8BIT5_ADDR(base) ((base) + (0xCB8))
#define SOC_SCTRL_SC_CLKCFG8BIT6_ADDR(base) ((base) + (0xCBC))
#define SOC_SCTRL_SC_CLKCFG8BIT7_ADDR(base) ((base) + (0xCC0))
#define SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(base) ((base) + (0xCC4))
#define SOC_SCTRL_SC_CLKCFG8BIT9_ADDR(base) ((base) + (0xCC8))
#define SOC_SCTRL_SC_CLKCFG8BIT10_ADDR(base) ((base) + (0xCCC))
#define SOC_SCTRL_SC_BUS_STAT0_ADDR(base) ((base) + (0xD80))
#define SOC_SCTRL_SC_BUS_STAT1_ADDR(base) ((base) + (0xD84))
#define SOC_SCTRL_SC_BUS_STAT2_ADDR(base) ((base) + (0xD88))
#define SOC_SCTRL_SC_BUS_STAT3_ADDR(base) ((base) + (0xD8C))
#define SOC_SCTRL_SC_BUS_STAT4_ADDR(base) ((base) + (0xD90))
#define SOC_SCTRL_SC_BUS_STAT5_ADDR(base) ((base) + (0xD94))
#define SOC_SCTRL_SC_BUS_STAT6_ADDR(base) ((base) + (0xD98))
#define SOC_SCTRL_SC_BUS_STAT7_ADDR(base) ((base) + (0xD9C))
#define SOC_SCTRL_SC_BUS_STAT8_ADDR(base) ((base) + (0xDA0))
#define SOC_SCTRL_SC_BUS_STAT9_ADDR(base) ((base) + (0xDA4))
#define SOC_SCTRL_SC_BUS_STAT10_ADDR(base) ((base) + (0xDA8))
#define SOC_SCTRL_SC_BUS_STAT11_ADDR(base) ((base) + (0xDAC))
#define SOC_SCTRL_SC_BUS_STAT12_ADDR(base) ((base) + (0xDB0))
#define SOC_SCTRL_SC_BUS_STAT13_ADDR(base) ((base) + (0xDB4))
#define SOC_SCTRL_SC_BUS_STAT14_ADDR(base) ((base) + (0xDB8))
#define SOC_SCTRL_SC_BUS_STAT15_ADDR(base) ((base) + (0xDBC))
#define SOC_SCTRL_SC_INT_EN_STAT1_ADDR(base) ((base) + (0xEC0))
#define SOC_SCTRL_SC_INT_STATR1_ADDR(base) ((base) + (0xEC4))
#define SOC_SCTRL_SC_INT_STATM1_ADDR(base) ((base) + (0xEC8))
#define SOC_SCTRL_SC_INT_CLEAR1_ADDR(base) ((base) + (0xECC))
#define SOC_SCTRL_SC_INT_EN1_ADDR(base) ((base) + (0xED0))
#define SOC_SCTRL_SC_INT_DIS1_ADDR(base) ((base) + (0xED4))
#define SOC_SCTRL_SC_INT_EN_STAT2_ADDR(base) ((base) + (0xEE0))
#define SOC_SCTRL_SC_INT_STATR2_ADDR(base) ((base) + (0xEE4))
#define SOC_SCTRL_SC_INT_STATM2_ADDR(base) ((base) + (0xEE8))
#define SOC_SCTRL_SC_INT_CLEAR2_ADDR(base) ((base) + (0xEEC))
#define SOC_SCTRL_SC_INT_EN2_ADDR(base) ((base) + (0xEF0))
#define SOC_SCTRL_SC_INT_DIS2_ADDR(base) ((base) + (0xEF4))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gucicom0sel_mode : 1;
        unsigned int gucicom0soft_auto_clk_gate_en : 1;
        unsigned int gucicom0soft_gate_clk_en : 1;
        unsigned int gucicom1sel_mode : 1;
        unsigned int gucicom11soft_auto_clk_gate_en : 1;
        unsigned int gucicom11soft_gate_clk_en : 1;
        unsigned int TS_auto_clk_gate_en : 1;
        unsigned int TS_soft_gate_clk_en : 1;
        unsigned int sec_ipc_auto_clk_gate_en : 1;
        unsigned int sec_ipc_soft_gate_clk_en : 1;
        unsigned int UPACC_auto_clk_gate_en : 1;
        unsigned int upacc_soft_gate_clk_en : 1;
        unsigned int etr_axi_csysreq_n : 1;
        unsigned int ipc_ns_auto_clk_gate_en : 1;
        unsigned int ipc_ns_soft_gate_clk_en : 1;
        unsigned int periph_ctrl1 : 1;
        unsigned int gucicom0sel_mode_msk : 1;
        unsigned int gucicom0soft_auto_clk_gate_en_msk : 1;
        unsigned int gucicom0soft_gate_clk_en_msk : 1;
        unsigned int gucicom1sel_mode_msk : 1;
        unsigned int gucicom1soft_auto_clk_gate_en_msk : 1;
        unsigned int gucicom1soft_gate_clk_en_msk : 1;
        unsigned int ts_auto_clk_gate_en_msk : 1;
        unsigned int ts_soft_gate_clk_en_msk : 1;
        unsigned int sec_ipc_auto_clk_gate_en_msk : 1;
        unsigned int sec_ipc_soft_gate_clk_en_msk : 1;
        unsigned int UPACC_auto_clk_gate_en_msk : 1;
        unsigned int upacc_soft_gate_clk_en_msk : 1;
        unsigned int etr_axi_csysreq_n_msk : 1;
        unsigned int ipc_ns_auto_clk_gate_en_msk : 1;
        unsigned int ipc_ns_soft_gate_clk_en_msk : 1;
        unsigned int periph_ctrl1_msk : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0sel_mode_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0sel_mode_END (0)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_auto_clk_gate_en_START (1)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_auto_clk_gate_en_END (1)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_gate_clk_en_START (2)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_gate_clk_en_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1sel_mode_START (3)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1sel_mode_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom11soft_auto_clk_gate_en_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom11soft_auto_clk_gate_en_END (4)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom11soft_gate_clk_en_START (5)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom11soft_gate_clk_en_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL1_TS_auto_clk_gate_en_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL1_TS_auto_clk_gate_en_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL1_TS_soft_gate_clk_en_START (7)
#define SOC_SCTRL_SC_PERIPH_CTRL1_TS_soft_gate_clk_en_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_auto_clk_gate_en_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_auto_clk_gate_en_END (8)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_soft_gate_clk_en_START (9)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_soft_gate_clk_en_END (9)
#define SOC_SCTRL_SC_PERIPH_CTRL1_UPACC_auto_clk_gate_en_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL1_UPACC_auto_clk_gate_en_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL1_upacc_soft_gate_clk_en_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL1_upacc_soft_gate_clk_en_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL1_etr_axi_csysreq_n_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL1_etr_axi_csysreq_n_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_auto_clk_gate_en_START (13)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_auto_clk_gate_en_END (13)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_soft_gate_clk_en_START (14)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_soft_gate_clk_en_END (14)
#define SOC_SCTRL_SC_PERIPH_CTRL1_periph_ctrl1_START (15)
#define SOC_SCTRL_SC_PERIPH_CTRL1_periph_ctrl1_END (15)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0sel_mode_msk_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0sel_mode_msk_END (16)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_auto_clk_gate_en_msk_START (17)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_auto_clk_gate_en_msk_END (17)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_gate_clk_en_msk_START (18)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom0soft_gate_clk_en_msk_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1sel_mode_msk_START (19)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1sel_mode_msk_END (19)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1soft_auto_clk_gate_en_msk_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1soft_auto_clk_gate_en_msk_END (20)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1soft_gate_clk_en_msk_START (21)
#define SOC_SCTRL_SC_PERIPH_CTRL1_gucicom1soft_gate_clk_en_msk_END (21)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ts_auto_clk_gate_en_msk_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ts_auto_clk_gate_en_msk_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ts_soft_gate_clk_en_msk_START (23)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ts_soft_gate_clk_en_msk_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_auto_clk_gate_en_msk_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_auto_clk_gate_en_msk_END (24)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_soft_gate_clk_en_msk_START (25)
#define SOC_SCTRL_SC_PERIPH_CTRL1_sec_ipc_soft_gate_clk_en_msk_END (25)
#define SOC_SCTRL_SC_PERIPH_CTRL1_UPACC_auto_clk_gate_en_msk_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL1_UPACC_auto_clk_gate_en_msk_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL1_upacc_soft_gate_clk_en_msk_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL1_upacc_soft_gate_clk_en_msk_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL1_etr_axi_csysreq_n_msk_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL1_etr_axi_csysreq_n_msk_END (28)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_auto_clk_gate_en_msk_START (29)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_auto_clk_gate_en_msk_END (29)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_soft_gate_clk_en_msk_START (30)
#define SOC_SCTRL_SC_PERIPH_CTRL1_ipc_ns_soft_gate_clk_en_msk_END (30)
#define SOC_SCTRL_SC_PERIPH_CTRL1_periph_ctrl1_msk_START (31)
#define SOC_SCTRL_SC_PERIPH_CTRL1_periph_ctrl1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmc_clk_phase_bypass_en_mmc0 : 1;
        unsigned int mmc_clk_phase_bypass_en_mmc1 : 1;
        unsigned int mmc_clk_phase_bypass_en_mmc2 : 1;
        unsigned int reserved_0 : 1;
        unsigned int h2pdma_dfs_on : 1;
        unsigned int otg_scaledown : 2;
        unsigned int reserved_1 : 1;
        unsigned int spi_clkdiv : 8;
        unsigned int x2xmdm_gt_cken : 1;
        unsigned int x2xsys_gt_cken : 1;
        unsigned int x2xvdec_gt_cken : 1;
        unsigned int x2xvenc_gt_cken : 1;
        unsigned int x2xvpp_gt_cken : 1;
        unsigned int axi_peri_gt_cken : 1;
        unsigned int axi_apcfg_gt_cken : 1;
        unsigned int axi_img_gt_cken : 1;
        unsigned int axi_video_gt_cken : 1;
        unsigned int axi_g3d_gt_cken : 1;
        unsigned int axi_acpumbrg_gt_cken : 1;
        unsigned int axi_acpum10_gt_sftcken : 1;
        unsigned int axi_acpucfgbrg_gt_cken : 1;
        unsigned int l2stop_gt_cken : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc0_END (0)
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc1_START (1)
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc1_END (1)
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc2_START (2)
#define SOC_SCTRL_SC_PERIPH_CTRL2_mmc_clk_phase_bypass_en_mmc2_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL2_h2pdma_dfs_on_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL2_h2pdma_dfs_on_END (4)
#define SOC_SCTRL_SC_PERIPH_CTRL2_otg_scaledown_START (5)
#define SOC_SCTRL_SC_PERIPH_CTRL2_otg_scaledown_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL2_spi_clkdiv_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL2_spi_clkdiv_END (15)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xmdm_gt_cken_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xmdm_gt_cken_END (16)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xsys_gt_cken_START (17)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xsys_gt_cken_END (17)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvdec_gt_cken_START (18)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvdec_gt_cken_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvenc_gt_cken_START (19)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvenc_gt_cken_END (19)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvpp_gt_cken_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL2_x2xvpp_gt_cken_END (20)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_peri_gt_cken_START (21)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_peri_gt_cken_END (21)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_apcfg_gt_cken_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_apcfg_gt_cken_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_img_gt_cken_START (23)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_img_gt_cken_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_video_gt_cken_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_video_gt_cken_END (24)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_g3d_gt_cken_START (25)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_g3d_gt_cken_END (25)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpumbrg_gt_cken_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpumbrg_gt_cken_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpum10_gt_sftcken_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpum10_gt_sftcken_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpucfgbrg_gt_cken_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL2_axi_acpucfgbrg_gt_cken_END (28)
#define SOC_SCTRL_SC_PERIPH_CTRL2_l2stop_gt_cken_START (29)
#define SOC_SCTRL_SC_PERIPH_CTRL2_l2stop_gt_cken_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 6;
        unsigned int sci1_i2c2_dmasel0 : 1;
        unsigned int sci1_i2c2_dmasel1 : 1;
        unsigned int apdmac_auto_clken0_sel : 1;
        unsigned int apdmac_auto_clken1_sel : 1;
        unsigned int mdmdmac_auto_clken0_sel : 1;
        unsigned int mdmdmac_auto_clken1_sel : 1;
        unsigned int modem_uart1_int_sel : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 6;
        unsigned int sci1_i2c2_dmasel0_msk : 1;
        unsigned int sci1_i2c2_dmasel1_msk : 1;
        unsigned int apdmac_auto_clken0_sel_msk : 1;
        unsigned int apdmac_auto_clken1_sel_msk : 1;
        unsigned int mdmdmac_auto_clken0_sel_msk : 1;
        unsigned int mdmdmac_auto_clken1_sel_msk : 1;
        unsigned int modem_uart1_int_sel_msk : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int periph_ctrl3 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel0_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel0_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel1_START (7)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel1_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken0_sel_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken0_sel_END (8)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken1_sel_START (9)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken1_sel_END (9)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken0_sel_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken0_sel_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken1_sel_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken1_sel_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL3_modem_uart1_int_sel_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL3_modem_uart1_int_sel_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel0_msk_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel0_msk_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel1_msk_START (23)
#define SOC_SCTRL_SC_PERIPH_CTRL3_sci1_i2c2_dmasel1_msk_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken0_sel_msk_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken0_sel_msk_END (24)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken1_sel_msk_START (25)
#define SOC_SCTRL_SC_PERIPH_CTRL3_apdmac_auto_clken1_sel_msk_END (25)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken0_sel_msk_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken0_sel_msk_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken1_sel_msk_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL3_mdmdmac_auto_clken1_sel_msk_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL3_modem_uart1_int_sel_msk_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL3_modem_uart1_int_sel_msk_END (28)
#define SOC_SCTRL_SC_PERIPH_CTRL3_periph_ctrl3_START (31)
#define SOC_SCTRL_SC_PERIPH_CTRL3_periph_ctrl3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mdmsys_ramctrl_d1w2r_emaa : 3;
        unsigned int mdmsys_ramctrl_d1w2r_emab : 3;
        unsigned int mdmsys_ramctrl_d1w2r_emasa : 1;
        unsigned int mdmsys_ramctrl_d1w2r_colldisn : 1;
        unsigned int reserved_0 : 2;
        unsigned int mdmsys_ramctrl_d1w2r_ret1n : 1;
        unsigned int mdmsys_ramctrl_d1w2r_ret2n : 1;
        unsigned int mdmsys_ramctrl_d1w2r_pgen : 1;
        unsigned int reserved_1 : 3;
        unsigned int mdmsys_ramctrl_s_ema : 3;
        unsigned int reserved_2 : 1;
        unsigned int mdmsys_ramctrl_s_emaw : 2;
        unsigned int mdmsys_ramctrl_s_emas : 1;
        unsigned int reserved_3 : 3;
        unsigned int mdmsys_ramctrl_s_ret1n : 1;
        unsigned int mdmsys_ramctrl_s_ret2n : 1;
        unsigned int mdmsys_ramctrl_s_pgen : 1;
        unsigned int reserved_4 : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL4_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emaa_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emaa_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emab_START (3)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emab_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emasa_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_emasa_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_colldisn_START (7)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_colldisn_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_ret1n_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_ret1n_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_ret2n_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_ret2n_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_pgen_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_d1w2r_pgen_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ema_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ema_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_emaw_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_emaw_END (21)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_emas_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_emas_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ret1n_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ret1n_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ret2n_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_ret2n_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_pgen_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL4_mdmsys_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mediasys_ramctrl_d1w2r_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int mediasys_ramctrl_d1w2r_emaw : 2;
        unsigned int mediasys_ramctrl_d1w2r_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int mediasys_ramctrl_d1w2r_ret1n : 1;
        unsigned int mediasys_ramctrl_d1w2r_ret2n : 1;
        unsigned int mediasys_ramctrl_d1w2r_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int mediasys_ramctrl_s_ema : 3;
        unsigned int reserved_3 : 1;
        unsigned int mediasys_ramctrl_s_emaw : 2;
        unsigned int mediasys_ramctrl_s_emas : 1;
        unsigned int reserved_4 : 3;
        unsigned int mediasys_ramctrl_s_ret1n : 1;
        unsigned int mediasys_ramctrl_s_ret2n : 1;
        unsigned int mediasys_ramctrl_s_pgen : 1;
        unsigned int reserved_5 : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL5_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ema_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ema_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_emaw_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_emaw_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_emas_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_emas_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ret1n_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ret1n_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ret2n_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_ret2n_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_pgen_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_d1w2r_pgen_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ema_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ema_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_emaw_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_emaw_END (21)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_emas_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_emas_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ret1n_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ret1n_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ret2n_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_ret2n_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_pgen_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL5_mediasys_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cssysoff_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int cssysoff_ramctrl_s_emaw : 2;
        unsigned int cssysoff_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int cssysoff_ramctrl_s_ret1n : 1;
        unsigned int cssysoff_ramctrl_s_ret2n : 1;
        unsigned int cssysoff_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int g3d_ramctrl_d1w2r_ret1n : 1;
        unsigned int g3d_ramctrl_d1w2r_ret2n : 1;
        unsigned int g3d_ramctrl_d1w2r_pgen : 1;
        unsigned int reserved_5 : 3;
        unsigned int reserved_6 : 1;
        unsigned int g3d_ramctrl_hardware : 1;
        unsigned int g3d_ramctrl_s_ret1n : 1;
        unsigned int g3d_ramctrl_s_ret2n : 1;
        unsigned int g3d_ramctrl_s_pgen : 1;
        unsigned int reserved_7 : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL6_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ema_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ema_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_emaw_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_emaw_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_emas_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_emas_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ret1n_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ret1n_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ret2n_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_ret2n_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_pgen_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL6_cssysoff_ramctrl_s_pgen_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_ret1n_START (18)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_ret1n_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_ret2n_START (19)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_ret2n_END (19)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_pgen_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_d1w2r_pgen_END (20)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_hardware_START (25)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_hardware_END (25)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_ret1n_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_ret1n_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_ret2n_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_ret2n_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_pgen_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL6_g3d_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perisys_ramctrl_d1w2r_emaa : 3;
        unsigned int perisys_ramctrl_d1w2r_emab : 3;
        unsigned int perisys_ramctrl_d1w2r_emasa : 1;
        unsigned int perisys_ramctrl_d1w2r_colldisn : 1;
        unsigned int reserved_0 : 2;
        unsigned int perisys_ramctrl_d1w2r_ret1n : 1;
        unsigned int perisys_ramctrl_d1w2r_ret2n : 1;
        unsigned int perisys_ramctrl_d1w2r_pgen : 1;
        unsigned int reserved_1 : 3;
        unsigned int perisys_ramctrl_d1rw2rw_ema : 3;
        unsigned int reserved_2 : 1;
        unsigned int perisys_ramctrl_d1rw2rw_emaw : 2;
        unsigned int perisys_ramctrl_d1rw2rw_emas : 1;
        unsigned int perisys_ramctrl_d1rw2rw_colldisn : 1;
        unsigned int reserved_3 : 2;
        unsigned int perisys_ramctrl_d1rw2rw_ret1n : 1;
        unsigned int perisys_ramctrl_d1rw2rw_ret2n : 1;
        unsigned int perisys_ramctrl_d1rw2rw_pgen : 1;
        unsigned int perisys_ramctrl_d1rw2rw : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL12_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emaa_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emaa_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emab_START (3)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emab_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emasa_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_emasa_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_colldisn_START (7)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_colldisn_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_ret1n_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_ret1n_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_ret2n_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_ret2n_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_pgen_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1w2r_pgen_END (12)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ema_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ema_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_emaw_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_emaw_END (21)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_emas_START (22)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_emas_END (22)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_colldisn_START (23)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_colldisn_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ret1n_START (26)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ret1n_END (26)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ret2n_START (27)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_ret2n_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_pgen_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_pgen_END (28)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_START (29)
#define SOC_SCTRL_SC_PERIPH_CTRL12_perisys_ramctrl_d1rw2rw_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int delay_ctrl_i2c0 : 1;
        unsigned int delay_ctrl_i2c0_80ns_sel : 1;
        unsigned int delay_ctrl_i2c1 : 1;
        unsigned int delay_ctrl_i2c1_80ns_sel : 1;
        unsigned int delay_ctrl_i2c2 : 1;
        unsigned int delay_ctrl_i2c2_80ns_sel : 1;
        unsigned int delay_ctrl_i2c3 : 1;
        unsigned int delay_ctrl_i2c3_80ns_sel : 1;
        unsigned int delay_ctrl_i2c4 : 1;
        unsigned int delay_ctrl_i2c4_80ns_sel : 1;
        unsigned int delay_ctrl_i2c5 : 1;
        unsigned int delay_ctrl_i2c5_80ns_sel : 1;
        unsigned int periph_ctrl13 : 20;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL13_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c0_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c0_END (0)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c0_80ns_sel_START (1)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c0_80ns_sel_END (1)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c1_START (2)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c1_END (2)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c1_80ns_sel_START (3)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c1_80ns_sel_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c2_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c2_END (4)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c2_80ns_sel_START (5)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c2_80ns_sel_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c3_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c3_END (6)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c3_80ns_sel_START (7)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c3_80ns_sel_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c4_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c4_END (8)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c4_80ns_sel_START (9)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c4_80ns_sel_END (9)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c5_START (10)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c5_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c5_80ns_sel_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL13_delay_ctrl_i2c5_80ns_sel_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL13_periph_ctrl13_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL13_periph_ctrl13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_ctrl14 : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL14_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL14_periph_ctrl14_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL14_periph_ctrl14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_ctrl15_edc1_rsimgm1_sideband_awuser : 4;
        unsigned int periph_ctrl15_edc1_rsimgm1_sideband_aruser : 4;
        unsigned int periph_ctrl15_isp_rsimgm2_sideband_awuser : 4;
        unsigned int periph_ctrl15_isp_rsimgm2_sideband_aruser : 4;
        unsigned int periph_ctrl15_reserved : 8;
        unsigned int periph_ctrl15_ccpum0_x2xddr2_sideband_awuser : 4;
        unsigned int periph_ctrl15_ccpum0_x2xddr2_sideband_aruser : 4;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL15_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_edc1_rsimgm1_sideband_awuser_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_edc1_rsimgm1_sideband_awuser_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_edc1_rsimgm1_sideband_aruser_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_edc1_rsimgm1_sideband_aruser_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_isp_rsimgm2_sideband_awuser_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_isp_rsimgm2_sideband_awuser_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_isp_rsimgm2_sideband_aruser_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_isp_rsimgm2_sideband_aruser_END (15)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_reserved_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_reserved_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_ccpum0_x2xddr2_sideband_awuser_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_ccpum0_x2xddr2_sideband_awuser_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_ccpum0_x2xddr2_sideband_aruser_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL15_periph_ctrl15_ccpum0_x2xddr2_sideband_aruser_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_ctrl16_edc0_tzasc8_sideband_awuser : 4;
        unsigned int periph_ctrl16_edc0_tzasc8_sideband_aruser : 4;
        unsigned int periph_ctrl16_vdec_x2x_sideband_awuser : 4;
        unsigned int periph_ctrl16_vdec_x2x_sideband_aruser : 4;
        unsigned int periph_ctrl16_venc_x2x_sideband_awuser : 4;
        unsigned int periph_ctrl16_venc_x2x_sideband_aruser : 4;
        unsigned int periph_ctrl16_vpp_x2x_sideband_awuser : 4;
        unsigned int periph_ctrl16_vpp_x2x_sideband_aruser : 4;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL16_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_edc0_tzasc8_sideband_awuser_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_edc0_tzasc8_sideband_awuser_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_edc0_tzasc8_sideband_aruser_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_edc0_tzasc8_sideband_aruser_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vdec_x2x_sideband_awuser_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vdec_x2x_sideband_awuser_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vdec_x2x_sideband_aruser_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vdec_x2x_sideband_aruser_END (15)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_venc_x2x_sideband_awuser_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_venc_x2x_sideband_awuser_END (19)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_venc_x2x_sideband_aruser_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_venc_x2x_sideband_aruser_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vpp_x2x_sideband_awuser_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vpp_x2x_sideband_awuser_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vpp_x2x_sideband_aruser_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL16_periph_ctrl16_vpp_x2x_sideband_aruser_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_state0_gucicom0clk_state : 1;
        unsigned int periph_state0_gucicom1clk_state : 1;
        unsigned int periph_state0_ipf_idle : 1;
        unsigned int periph_state0_socp_idle : 1;
        unsigned int periph_state0_tsclkstate : 1;
        unsigned int etr_axi_csysack_n : 1;
        unsigned int periph_state0 : 26;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_gucicom0clk_state_START (0)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_gucicom0clk_state_END (0)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_gucicom1clk_state_START (1)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_gucicom1clk_state_END (1)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_ipf_idle_START (2)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_ipf_idle_END (2)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_socp_idle_START (3)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_socp_idle_END (3)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_tsclkstate_START (4)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_tsclkstate_END (4)
#define SOC_SCTRL_SC_PERIPH_STAT0_etr_axi_csysack_n_START (5)
#define SOC_SCTRL_SC_PERIPH_STAT0_etr_axi_csysack_n_END (5)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_START (6)
#define SOC_SCTRL_SC_PERIPH_STAT0_periph_state0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int carm_scuidle : 1;
        unsigned int periph_state1 : 31;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_STAT1_carm_scuidle_START (0)
#define SOC_SCTRL_SC_PERIPH_STAT1_carm_scuidle_END (0)
#define SOC_SCTRL_SC_PERIPH_STAT1_periph_state1_START (1)
#define SOC_SCTRL_SC_PERIPH_STAT1_periph_state1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int system_noc_master_qos_11 : 2;
        unsigned int system_noc_master_qos_10 : 2;
        unsigned int system_noc_master_qos_9 : 2;
        unsigned int system_noc_master_qos_8 : 2;
        unsigned int system_noc_master_qos_7 : 2;
        unsigned int system_noc_master_qos_6 : 2;
        unsigned int system_noc_master_qos_5 : 2;
        unsigned int system_noc_master_qos_4 : 2;
        unsigned int system_noc_master_qos_3 : 2;
        unsigned int system_noc_master_qos_2 : 2;
        unsigned int system_noc_master_qos_1 : 2;
        unsigned int system_noc_master_qos_0 : 2;
        unsigned int ddr_ctrl0 : 8;
    } reg;
} SOC_SCTRL_SC_DDR_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_11_START (0)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_11_END (1)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_10_START (2)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_10_END (3)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_9_START (4)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_9_END (5)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_8_START (6)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_8_END (7)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_7_START (8)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_7_END (9)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_6_START (10)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_6_END (11)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_5_START (12)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_5_END (13)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_4_START (14)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_4_END (15)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_3_START (16)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_3_END (17)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_2_START (18)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_2_END (19)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_1_START (20)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_1_END (21)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_0_START (22)
#define SOC_SCTRL_SC_DDR_CTRL0_system_noc_master_qos_0_END (23)
#define SOC_SCTRL_SC_DDR_CTRL0_ddr_ctrl0_START (24)
#define SOC_SCTRL_SC_DDR_CTRL0_ddr_ctrl0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int modem_noc_master_qos_9 : 2;
        unsigned int modem_noc_master_qos_8 : 2;
        unsigned int modem_noc_master_qos_7 : 2;
        unsigned int modem_noc_master_qos_6 : 2;
        unsigned int modem_noc_master_qos_5 : 2;
        unsigned int modem_noc_master_qos_4 : 2;
        unsigned int modem_noc_master_qos_3 : 2;
        unsigned int modem_noc_master_qos_2 : 2;
        unsigned int modem_noc_master_qos_1 : 2;
        unsigned int modem_noc_master_qos_0 : 2;
        unsigned int reserved : 12;
    } reg;
} SOC_SCTRL_SC_DDR_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_9_START (0)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_9_END (1)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_8_START (2)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_8_END (3)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_7_START (4)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_7_END (5)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_6_START (6)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_6_END (7)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_5_START (8)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_5_END (9)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_4_START (10)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_4_END (11)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_3_START (12)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_3_END (13)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_2_START (14)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_2_END (15)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_1_START (16)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_1_END (17)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_0_START (18)
#define SOC_SCTRL_SC_DDR_CTRL1_modem_noc_master_qos_0_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g2d2ddrc9_awqos_map : 4;
        unsigned int g2d2ddrc9_arqos_map : 4;
        unsigned int hifi_pifqos : 4;
        unsigned int reserved : 4;
        unsigned int mili_awqos_map : 4;
        unsigned int mili_arqos_map : 4;
        unsigned int mdmdmac_awqos_map : 4;
        unsigned int mdmdmac_arqos_map : 4;
    } reg;
} SOC_SCTRL_SC_DDR_CTRL2_UNION;
#endif
#define SOC_SCTRL_SC_DDR_CTRL2_g2d2ddrc9_awqos_map_START (0)
#define SOC_SCTRL_SC_DDR_CTRL2_g2d2ddrc9_awqos_map_END (3)
#define SOC_SCTRL_SC_DDR_CTRL2_g2d2ddrc9_arqos_map_START (4)
#define SOC_SCTRL_SC_DDR_CTRL2_g2d2ddrc9_arqos_map_END (7)
#define SOC_SCTRL_SC_DDR_CTRL2_hifi_pifqos_START (8)
#define SOC_SCTRL_SC_DDR_CTRL2_hifi_pifqos_END (11)
#define SOC_SCTRL_SC_DDR_CTRL2_mili_awqos_map_START (16)
#define SOC_SCTRL_SC_DDR_CTRL2_mili_awqos_map_END (19)
#define SOC_SCTRL_SC_DDR_CTRL2_mili_arqos_map_START (20)
#define SOC_SCTRL_SC_DDR_CTRL2_mili_arqos_map_END (23)
#define SOC_SCTRL_SC_DDR_CTRL2_mdmdmac_awqos_map_START (24)
#define SOC_SCTRL_SC_DDR_CTRL2_mdmdmac_awqos_map_END (27)
#define SOC_SCTRL_SC_DDR_CTRL2_mdmdmac_arqos_map_START (28)
#define SOC_SCTRL_SC_DDR_CTRL2_mdmdmac_arqos_map_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mddrc_dto_sel : 1;
        unsigned int reserved : 1;
        unsigned int ddr_ctrl3_reserved : 2;
        unsigned int ddr_ctrl3_reserved31 : 28;
    } reg;
} SOC_SCTRL_SC_DDR_CTRL3_UNION;
#endif
#define SOC_SCTRL_SC_DDR_CTRL3_mddrc_dto_sel_START (0)
#define SOC_SCTRL_SC_DDR_CTRL3_mddrc_dto_sel_END (0)
#define SOC_SCTRL_SC_DDR_CTRL3_ddr_ctrl3_reserved_START (2)
#define SOC_SCTRL_SC_DDR_CTRL3_ddr_ctrl3_reserved_END (3)
#define SOC_SCTRL_SC_DDR_CTRL3_ddr_ctrl3_reserved31_START (4)
#define SOC_SCTRL_SC_DDR_CTRL3_ddr_ctrl3_reserved31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int ddr_ctrl4_reserved31 : 27;
    } reg;
} SOC_SCTRL_SC_DDR_CTRL4_UNION;
#endif
#define SOC_SCTRL_SC_DDR_CTRL4_ddr_ctrl4_reserved31_START (5)
#define SOC_SCTRL_SC_DDR_CTRL4_ddr_ctrl4_reserved31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 4;
        unsigned int reserved_1: 28;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT3_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_state4 : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT4_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_STAT4_periph_state4_START (0)
#define SOC_SCTRL_SC_PERIPH_STAT4_periph_state4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_stat6 : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_STAT6_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_STAT6_periph_stat6_START (0)
#define SOC_SCTRL_SC_PERIPH_STAT6_periph_stat6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_ctrl8_PICOPHY_txrisetune0 : 2;
        unsigned int periph_ctrl8_PICOPHY_txpreempamptune0 : 2;
        unsigned int periph_ctrl8_PICOPHY_txrestune0 : 2;
        unsigned int periph_ctrl8_PICOPHY_txhssvtune0 : 2;
        unsigned int periph_ctrl8_PICOPHY_compdistune0 : 3;
        unsigned int periph_ctrl8_PICOPHY_txpreemppulsetune0 : 1;
        unsigned int periph_ctrl8_PICOPHY_otgtune0 : 3;
        unsigned int periph_ctrl8_reserved15 : 1;
        unsigned int periph_ctrl8_PICOPHY_sqrxtune0 : 3;
        unsigned int periph_ctrl8_reserved19 : 1;
        unsigned int periph_ctrl8_PICOPHY_txvreftune0 : 4;
        unsigned int periph_ctrl8_reserved27 : 4;
        unsigned int periph_ctrl8_PICOPHY_txfslstune0 : 4;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txrisetune0_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txrisetune0_END (1)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txpreempamptune0_START (2)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txpreempamptune0_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txrestune0_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txrestune0_END (5)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txhssvtune0_START (6)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txhssvtune0_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_compdistune0_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_compdistune0_END (10)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txpreemppulsetune0_START (11)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txpreemppulsetune0_END (11)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_otgtune0_START (12)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_otgtune0_END (14)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved15_START (15)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved15_END (15)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_sqrxtune0_START (16)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_sqrxtune0_END (18)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved19_START (19)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved19_END (19)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txvreftune0_START (20)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txvreftune0_END (23)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved27_START (24)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_reserved27_END (27)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txfslstune0_START (28)
#define SOC_SCTRL_SC_PERIPH_CTRL8_periph_ctrl8_PICOPHY_txfslstune0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_ctrl9_picoply_testclken : 1;
        unsigned int periph_ctrl9_picoply_testdataoutsel : 1;
        unsigned int periph_ctrl9 : 2;
        unsigned int periph_ctrl9_picoply_testaddr : 4;
        unsigned int periph_ctrl9_picoply_testdatain : 8;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 2;
        unsigned int reserved_3 : 4;
        unsigned int reserved_4 : 8;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testclken_START (0)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testclken_END (0)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testdataoutsel_START (1)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testdataoutsel_END (1)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_START (2)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_END (3)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testaddr_START (4)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testaddr_END (7)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testdatain_START (8)
#define SOC_SCTRL_SC_PERIPH_CTRL9_periph_ctrl9_picoply_testdatain_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 7;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 4;
        unsigned int reserved_11 : 4;
        unsigned int reserved_12 : 2;
        unsigned int reserved_13 : 2;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int periph_ctrl10 : 2;
    } reg;
} SOC_SCTRL_SC_PERIPH_CTRL10_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CTRL10_periph_ctrl10_START (30)
#define SOC_SCTRL_SC_PERIPH_CTRL10_periph_ctrl10_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int hifi_stat_vector_sel : 1;
        unsigned int hifi_ocd_halton_reset : 1;
        unsigned int hifi_runstall : 1;
        unsigned int reserved_1 : 11;
        unsigned int hifi_xocdmode : 1;
        unsigned int hifi_pwaitmode : 1;
    } reg;
} SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_stat_vector_sel_START (16)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_stat_vector_sel_END (16)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_ocd_halton_reset_START (17)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_ocd_halton_reset_END (17)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_runstall_START (18)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_runstall_END (18)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_xocdmode_START (30)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_xocdmode_END (30)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_pwaitmode_START (31)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_hifi_pwaitmode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbe_notrace_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int bbe_notrace_ramctrl_s_emaw : 2;
        unsigned int bbe_notrace_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int bbe_notrace_ramctrl_s_ret1n : 1;
        unsigned int bbe_notrace_ramctrl_s_ret2n : 1;
        unsigned int bbe_notrace_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int bbe_trace_ramctrl_s_ema : 3;
        unsigned int reserved_3 : 1;
        unsigned int bbe_trace_ramctrl_s_emaw : 2;
        unsigned int bbe_trace_ramctrl_s_emas : 1;
        unsigned int reserved_4 : 3;
        unsigned int bbe_trace_ramctrl_s_ret1n : 1;
        unsigned int bbe_trace_ramctrl_s_ret2n : 1;
        unsigned int bbe_trace_ramctrl_s_pgen : 1;
        unsigned int reserved_5 : 3;
    } reg;
} SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ema_START (0)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ema_END (2)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_emaw_START (4)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_emaw_END (5)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_emas_START (6)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_emas_END (6)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ret1n_START (10)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ret1n_END (10)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ret2n_START (11)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_ret2n_END (11)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_pgen_START (12)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_notrace_ramctrl_s_pgen_END (12)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ema_START (16)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ema_END (18)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_emaw_START (20)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_emaw_END (21)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_emas_START (22)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_emas_END (22)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ret1n_START (26)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ret1n_END (26)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ret2n_START (27)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_ret2n_END (27)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_pgen_START (28)
#define SOC_SCTRL_SC_DSP_SUBSYS_CTRL1_bbe_trace_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsp_subsys_stat0 : 32;
    } reg;
} SOC_SCTRL_SC_DSP_SUBSYS_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_DSP_SUBSYS_STAT0_dsp_subsys_stat0_START (0)
#define SOC_SCTRL_SC_DSP_SUBSYS_STAT0_dsp_subsys_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aarm0l1_ramctrl_s_ret1n : 1;
        unsigned int aarm0l1_ramctrl_s_ret2n : 1;
        unsigned int aarm0l1_ramctrl_s_pgen : 1;
        unsigned int reserved_0 : 1;
        unsigned int aarm1l1_ramctrl_s_ret1n : 1;
        unsigned int aarm1l1_ramctrl_s_ret2n : 1;
        unsigned int aarm1l1_ramctrl_s_pgen : 1;
        unsigned int reserved_1 : 1;
        unsigned int aarm2l1_ramctrl_s_ret1n : 1;
        unsigned int aarm2l1_ramctrl_s_ret2n : 1;
        unsigned int aarm2l1_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 1;
        unsigned int aarm3l1_ramctrl_s_ret1n : 1;
        unsigned int aarm3l1_ramctrl_s_ret2n : 1;
        unsigned int aarm3l1_ramctrl_s_pgen : 1;
        unsigned int reserved_3 : 4;
        unsigned int sc_ca9_cfgnmfi : 4;
        unsigned int sc_l2c_waysize : 3;
        unsigned int sc_l2c_associativity : 1;
        unsigned int reserved_4 : 1;
        unsigned int cpu_wfi_mask_cfg : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_ret1n_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_ret1n_END (0)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_ret2n_START (1)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_ret2n_END (1)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_pgen_START (2)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm0l1_ramctrl_s_pgen_END (2)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_ret1n_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_ret1n_END (4)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_ret2n_START (5)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_ret2n_END (5)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_pgen_START (6)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm1l1_ramctrl_s_pgen_END (6)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_ret1n_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_ret1n_END (8)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_ret2n_START (9)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_ret2n_END (9)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_pgen_START (10)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm2l1_ramctrl_s_pgen_END (10)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_ret1n_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_ret1n_END (12)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_ret2n_START (13)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_ret2n_END (13)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_pgen_START (14)
#define SOC_SCTRL_SC_ACPU_CTRL0_aarm3l1_ramctrl_s_pgen_END (14)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_ca9_cfgnmfi_START (19)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_ca9_cfgnmfi_END (22)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_l2c_waysize_START (23)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_l2c_waysize_END (25)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_l2c_associativity_START (26)
#define SOC_SCTRL_SC_ACPU_CTRL0_sc_l2c_associativity_END (26)
#define SOC_SCTRL_SC_ACPU_CTRL0_cpu_wfi_mask_cfg_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL0_cpu_wfi_mask_cfg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_pwrctli0 : 2;
        unsigned int sc_pwrctli1 : 2;
        unsigned int sc_pwrctli2 : 2;
        unsigned int sc_pwrctli3 : 2;
        unsigned int acpu_ctrl1 : 8;
        unsigned int reserved_0 : 3;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 2;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 3;
        unsigned int aarml2_ramctrl_s_ret1n : 1;
        unsigned int aarml2_ramctrl_s_ret2n : 1;
        unsigned int aarml2_ramctrl_s_pgen : 1;
        unsigned int reserved_5 : 3;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli0_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli0_END (1)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli1_START (2)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli1_END (3)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli2_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli2_END (5)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli3_START (6)
#define SOC_SCTRL_SC_ACPU_CTRL1_sc_pwrctli3_END (7)
#define SOC_SCTRL_SC_ACPU_CTRL1_acpu_ctrl1_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL1_acpu_ctrl1_END (15)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_ret1n_START (26)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_ret1n_END (26)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_ret2n_START (27)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_ret2n_END (27)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_pgen_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL1_aarml2_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 3;
        unsigned int acpu_debug_req : 4;
        unsigned int reserved_2 : 8;
        unsigned int reserved_3 : 4;
        unsigned int reserved_4 : 5;
        unsigned int reserved_5 : 2;
        unsigned int reserved_6 : 5;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL2_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL2_acpu_debug_req_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL2_acpu_debug_req_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perioqos0_cm3_qos : 4;
        unsigned int reserved : 4;
        unsigned int perioqos0_acpucfg_aw : 4;
        unsigned int perioqos0_acpucfg_ar : 4;
        unsigned int perioqos0_acpu_m0_aw : 4;
        unsigned int perioqos0_acpu_m0_ar : 4;
        unsigned int perioqos0_acpu_m1_aw : 4;
        unsigned int perioqos0_acpu_m1_ar : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL3_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_cm3_qos_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_cm3_qos_END (3)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpucfg_aw_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpucfg_aw_END (11)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpucfg_ar_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpucfg_ar_END (15)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m0_aw_START (16)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m0_aw_END (19)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m0_ar_START (20)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m0_ar_END (23)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m1_aw_START (24)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m1_aw_END (27)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m1_ar_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL3_perioqos0_acpu_m1_ar_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perioqos1_accaxi_m1_ipf_aw : 4;
        unsigned int perioqos1_accaxi_m1_ipf_ar : 4;
        unsigned int perioqos1_accaxi_m2_socp_aw : 4;
        unsigned int perioqos1_accaxi_m2_socp_ar : 4;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int perioqos1_seceng_aw : 4;
        unsigned int perioqos1_seceng_ar : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL4_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m1_ipf_aw_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m1_ipf_aw_END (3)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m1_ipf_ar_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m1_ipf_ar_END (7)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m2_socp_aw_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m2_socp_aw_END (11)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m2_socp_ar_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_accaxi_m2_socp_ar_END (15)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_seceng_aw_START (24)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_seceng_aw_END (27)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_seceng_ar_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL4_perioqos1_seceng_ar_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perioqos2_upacc_aw : 4;
        unsigned int perioqos2_upacc_ar : 4;
        unsigned int perioqos2_gucipher0_aw : 4;
        unsigned int perioqos2_gucipher0_ar : 4;
        unsigned int perioqos2_gucipher1_aw : 4;
        unsigned int perioqos2_gucipher1_ar : 4;
        unsigned int perioqos2_lcipher_aw : 4;
        unsigned int perioqos2_lcipher_ar : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL5_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_upacc_aw_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_upacc_aw_END (3)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_upacc_ar_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_upacc_ar_END (7)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher0_aw_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher0_aw_END (11)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher0_ar_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher0_ar_END (15)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher1_aw_START (16)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher1_aw_END (19)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher1_ar_START (20)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_gucipher1_ar_END (23)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_lcipher_aw_START (24)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_lcipher_aw_END (27)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_lcipher_ar_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL5_perioqos2_lcipher_ar_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perisys_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int perisys_ramctrl_s_emaw : 2;
        unsigned int perisys_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int perisys_ramctrl_s_ret1n : 1;
        unsigned int perisys_ramctrl_s_ret2n : 1;
        unsigned int perisys_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int rom_ctrl_ema : 3;
        unsigned int reserved_3 : 1;
        unsigned int rom_ctrl_pgen : 1;
        unsigned int rom_ctrl_ken : 1;
        unsigned int reserved_4 : 10;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL6_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ema_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ema_END (2)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_emaw_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_emaw_END (5)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_emas_START (6)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_emas_END (6)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ret1n_START (10)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ret1n_END (10)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ret2n_START (11)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_ret2n_END (11)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_pgen_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL6_perisys_ramctrl_s_pgen_END (12)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_ema_START (16)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_ema_END (18)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_pgen_START (20)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_pgen_END (20)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_ken_START (21)
#define SOC_SCTRL_SC_ACPU_CTRL6_rom_ctrl_ken_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmc0_hqos : 4;
        unsigned int mmc1_hqos : 4;
        unsigned int mmc2_hqos : 4;
        unsigned int usbotg_hqos : 4;
        unsigned int asp_hqos : 4;
        unsigned int reserved : 4;
        unsigned int apdmac_awqos : 4;
        unsigned int apdmac_arqos : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_CTRL7_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc0_hqos_START (0)
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc0_hqos_END (3)
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc1_hqos_START (4)
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc1_hqos_END (7)
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc2_hqos_START (8)
#define SOC_SCTRL_SC_ACPU_CTRL7_mmc2_hqos_END (11)
#define SOC_SCTRL_SC_ACPU_CTRL7_usbotg_hqos_START (12)
#define SOC_SCTRL_SC_ACPU_CTRL7_usbotg_hqos_END (15)
#define SOC_SCTRL_SC_ACPU_CTRL7_asp_hqos_START (16)
#define SOC_SCTRL_SC_ACPU_CTRL7_asp_hqos_END (19)
#define SOC_SCTRL_SC_ACPU_CTRL7_apdmac_awqos_START (24)
#define SOC_SCTRL_SC_ACPU_CTRL7_apdmac_awqos_END (27)
#define SOC_SCTRL_SC_ACPU_CTRL7_apdmac_arqos_START (28)
#define SOC_SCTRL_SC_ACPU_CTRL7_apdmac_arqos_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu0_srst_req_en : 1;
        unsigned int cpu1_srst_req_en : 1;
        unsigned int cpu2_srst_req_en : 1;
        unsigned int cpu3_srst_req_en : 1;
        unsigned int neon0_srst_req_en : 1;
        unsigned int neon1_srst_req_en : 1;
        unsigned int neon2_srst_req_en : 1;
        unsigned int neon3_srst_req_en : 1;
        unsigned int wd_srst_req_en : 4;
        unsigned int dbg0_srst_req_en : 1;
        unsigned int dbg1_srst_req_en : 1;
        unsigned int dbg2_srst_req_en : 1;
        unsigned int dbg3_srst_req_en : 1;
        unsigned int scu_srst_req_en : 1;
        unsigned int l2_srst_req_en : 1;
        unsigned int periph_srst_req_en : 1;
        unsigned int acp_srst_req_en : 1;
        unsigned int ptm_srst_req_en : 1;
        unsigned int dap_srst_req_en : 1;
        unsigned int acpu_hpm0_srst_req_en : 1;
        unsigned int acpu_hpm1_srst_req_en : 1;
        unsigned int acpu_hpm2_srst_req_en : 1;
        unsigned int acpu_hpm3_srst_req_en : 1;
        unsigned int acpu_hpm4_srst_req_en : 1;
        unsigned int l2c_hpm0_srst_req_en : 1;
        unsigned int l2c_hpm1_srst_req_en : 1;
        unsigned int l2c_hpm2_srst_req_en : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_SCTRL_SC_ACPU_CPURSTEN_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu0_srst_req_en_START (0)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu0_srst_req_en_END (0)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu1_srst_req_en_START (1)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu1_srst_req_en_END (1)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu2_srst_req_en_START (2)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu2_srst_req_en_END (2)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu3_srst_req_en_START (3)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_cpu3_srst_req_en_END (3)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon0_srst_req_en_START (4)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon0_srst_req_en_END (4)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon1_srst_req_en_START (5)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon1_srst_req_en_END (5)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon2_srst_req_en_START (6)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon2_srst_req_en_END (6)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon3_srst_req_en_START (7)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_neon3_srst_req_en_END (7)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_wd_srst_req_en_START (8)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_wd_srst_req_en_END (11)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg0_srst_req_en_START (12)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg0_srst_req_en_END (12)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg1_srst_req_en_START (13)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg1_srst_req_en_END (13)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg2_srst_req_en_START (14)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg2_srst_req_en_END (14)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg3_srst_req_en_START (15)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dbg3_srst_req_en_END (15)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_scu_srst_req_en_START (16)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_scu_srst_req_en_END (16)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2_srst_req_en_START (17)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2_srst_req_en_END (17)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_periph_srst_req_en_START (18)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_periph_srst_req_en_END (18)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acp_srst_req_en_START (19)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acp_srst_req_en_END (19)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_ptm_srst_req_en_START (20)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_ptm_srst_req_en_END (20)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dap_srst_req_en_START (21)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_dap_srst_req_en_END (21)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm0_srst_req_en_START (22)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm0_srst_req_en_END (22)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm1_srst_req_en_START (23)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm1_srst_req_en_END (23)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm2_srst_req_en_START (24)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm2_srst_req_en_END (24)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm3_srst_req_en_START (25)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm3_srst_req_en_END (25)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm4_srst_req_en_START (26)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_acpu_hpm4_srst_req_en_END (26)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm0_srst_req_en_START (27)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm0_srst_req_en_END (27)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm1_srst_req_en_START (28)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm1_srst_req_en_END (28)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm2_srst_req_en_START (29)
#define SOC_SCTRL_SC_ACPU_CPURSTEN_l2c_hpm2_srst_req_en_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu0_srst_req_dis : 1;
        unsigned int cpu1_srst_req_dis : 1;
        unsigned int cpu2_srst_req_dis : 1;
        unsigned int cpu3_srst_req_dis : 1;
        unsigned int neon0_srst_req_dis : 1;
        unsigned int neon1_srst_req_dis : 1;
        unsigned int neon2_srst_req_dis : 1;
        unsigned int neon3_srst_req_dis : 1;
        unsigned int wd_srst_req_dis : 4;
        unsigned int dbg0_srst_req_dis : 1;
        unsigned int dbg1_srst_req_dis : 1;
        unsigned int dbg2_srst_req_dis : 1;
        unsigned int dbg3_srst_req_dis : 1;
        unsigned int scu_srst_req_dis : 1;
        unsigned int l2_srst_req_dis : 1;
        unsigned int periph_srst_req_dis : 1;
        unsigned int acp_srst_req_dis : 1;
        unsigned int ptm_srst_req_dis : 1;
        unsigned int dap_srst_req_dis : 1;
        unsigned int acpu_hpm0_srst_req_dis : 1;
        unsigned int acpu_hpm1_srst_req_dis : 1;
        unsigned int acpu_hpm2_srst_req_dis : 1;
        unsigned int acpu_hpm3_srst_req_dis : 1;
        unsigned int acpu_hpm4_srst_req_dis : 1;
        unsigned int l2c_hpm0_srst_req_dis : 1;
        unsigned int l2c_hpm1_srst_req_dis : 1;
        unsigned int l2c_hpm2_srst_req_dis : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_SCTRL_SC_ACPU_CPURSTDIS_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu0_srst_req_dis_START (0)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu0_srst_req_dis_END (0)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu1_srst_req_dis_START (1)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu1_srst_req_dis_END (1)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu2_srst_req_dis_START (2)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu2_srst_req_dis_END (2)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu3_srst_req_dis_START (3)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_cpu3_srst_req_dis_END (3)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon0_srst_req_dis_START (4)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon0_srst_req_dis_END (4)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon1_srst_req_dis_START (5)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon1_srst_req_dis_END (5)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon2_srst_req_dis_START (6)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon2_srst_req_dis_END (6)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon3_srst_req_dis_START (7)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_neon3_srst_req_dis_END (7)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_wd_srst_req_dis_START (8)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_wd_srst_req_dis_END (11)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg0_srst_req_dis_START (12)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg0_srst_req_dis_END (12)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg1_srst_req_dis_START (13)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg1_srst_req_dis_END (13)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg2_srst_req_dis_START (14)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg2_srst_req_dis_END (14)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg3_srst_req_dis_START (15)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dbg3_srst_req_dis_END (15)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_scu_srst_req_dis_START (16)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_scu_srst_req_dis_END (16)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2_srst_req_dis_START (17)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2_srst_req_dis_END (17)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_periph_srst_req_dis_START (18)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_periph_srst_req_dis_END (18)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acp_srst_req_dis_START (19)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acp_srst_req_dis_END (19)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_ptm_srst_req_dis_START (20)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_ptm_srst_req_dis_END (20)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dap_srst_req_dis_START (21)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_dap_srst_req_dis_END (21)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm0_srst_req_dis_START (22)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm0_srst_req_dis_END (22)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm1_srst_req_dis_START (23)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm1_srst_req_dis_END (23)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm2_srst_req_dis_START (24)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm2_srst_req_dis_END (24)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm3_srst_req_dis_START (25)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm3_srst_req_dis_END (25)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm4_srst_req_dis_START (26)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_acpu_hpm4_srst_req_dis_END (26)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm0_srst_req_dis_START (27)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm0_srst_req_dis_END (27)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm1_srst_req_dis_START (28)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm1_srst_req_dis_END (28)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm2_srst_req_dis_START (29)
#define SOC_SCTRL_SC_ACPU_CPURSTDIS_l2c_hpm2_srst_req_dis_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu0_srst_req_stat : 1;
        unsigned int cpu1_srst_req_stat : 1;
        unsigned int cpu2_srst_req_stat : 1;
        unsigned int cpu3_srst_req_stat : 1;
        unsigned int neon0_srst_req_stat : 1;
        unsigned int neon1_srst_req_stat : 1;
        unsigned int neon2_srst_req_stat : 1;
        unsigned int neon3_srst_req_stat : 1;
        unsigned int wd_srst_req_stat : 4;
        unsigned int dbg0_srst_req_stat : 1;
        unsigned int dbg1_srst_req_stat : 1;
        unsigned int dbg2_srst_req_stat : 1;
        unsigned int dbg3_srst_req_stat : 1;
        unsigned int scu_srst_req_stat : 1;
        unsigned int l2_srst_req_stat : 1;
        unsigned int periph_srst_req_stat : 1;
        unsigned int acp_srst_req_stat : 1;
        unsigned int ptm_srst_req_stat : 1;
        unsigned int dap_srst_req_stat : 1;
        unsigned int acpu_hpm0_srst_req_stat : 1;
        unsigned int acpu_hpm1_srst_req_stat : 1;
        unsigned int acpu_hpm2_srst_req_stat : 1;
        unsigned int acpu_hpm3_srst_req_stat : 1;
        unsigned int acpu_hpm4_srst_req_stat : 1;
        unsigned int l2c_hpm0_srst_req_stat : 1;
        unsigned int l2c_hpm1_srst_req_stat : 1;
        unsigned int l2c_hpm2_srst_req_stat : 1;
        unsigned int reserved : 2;
    } reg;
} SOC_SCTRL_SC_ACPU_CPURSTSTAT_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu0_srst_req_stat_START (0)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu0_srst_req_stat_END (0)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu1_srst_req_stat_START (1)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu1_srst_req_stat_END (1)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu2_srst_req_stat_START (2)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu2_srst_req_stat_END (2)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu3_srst_req_stat_START (3)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_cpu3_srst_req_stat_END (3)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon0_srst_req_stat_START (4)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon0_srst_req_stat_END (4)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon1_srst_req_stat_START (5)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon1_srst_req_stat_END (5)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon2_srst_req_stat_START (6)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon2_srst_req_stat_END (6)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon3_srst_req_stat_START (7)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_neon3_srst_req_stat_END (7)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_wd_srst_req_stat_START (8)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_wd_srst_req_stat_END (11)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg0_srst_req_stat_START (12)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg0_srst_req_stat_END (12)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg1_srst_req_stat_START (13)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg1_srst_req_stat_END (13)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg2_srst_req_stat_START (14)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg2_srst_req_stat_END (14)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg3_srst_req_stat_START (15)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dbg3_srst_req_stat_END (15)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_scu_srst_req_stat_START (16)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_scu_srst_req_stat_END (16)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2_srst_req_stat_START (17)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2_srst_req_stat_END (17)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_periph_srst_req_stat_START (18)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_periph_srst_req_stat_END (18)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acp_srst_req_stat_START (19)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acp_srst_req_stat_END (19)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_ptm_srst_req_stat_START (20)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_ptm_srst_req_stat_END (20)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dap_srst_req_stat_START (21)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_dap_srst_req_stat_END (21)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm0_srst_req_stat_START (22)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm0_srst_req_stat_END (22)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm1_srst_req_stat_START (23)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm1_srst_req_stat_END (23)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm2_srst_req_stat_START (24)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm2_srst_req_stat_END (24)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm3_srst_req_stat_START (25)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm3_srst_req_stat_END (25)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm4_srst_req_stat_START (26)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_acpu_hpm4_srst_req_stat_END (26)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm0_srst_req_stat_START (27)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm0_srst_req_stat_END (27)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm1_srst_req_stat_START (28)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm1_srst_req_stat_END (28)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm2_srst_req_stat_START (29)
#define SOC_SCTRL_SC_ACPU_CPURSTSTAT_l2c_hpm2_srst_req_stat_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cp15disable0 : 1;
        unsigned int cp15disable1 : 1;
        unsigned int cp15disable2 : 1;
        unsigned int cp15disable3 : 1;
        unsigned int cfgdisable : 1;
        unsigned int reserved : 27;
    } reg;
} SOC_SCTRL_SC_ACPU_CPUCFG_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable0_START (0)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable0_END (0)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable1_START (1)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable1_END (1)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable2_START (2)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable2_END (2)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable3_START (3)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cp15disable3_END (3)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cfgdisable_START (4)
#define SOC_SCTRL_SC_ACPU_CPUCFG_cfgdisable_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu0_clkoff : 1;
        unsigned int cpu1_clkoff : 1;
        unsigned int cpu2_clkoff : 1;
        unsigned int cpu3_clkoff : 1;
        unsigned int neon0_clkoff : 1;
        unsigned int neon1_clkoff : 1;
        unsigned int neon2_clkoff : 1;
        unsigned int neon3_clkoff : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_ACPU_CPUCLKOFF_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu0_clkoff_START (0)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu0_clkoff_END (0)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu1_clkoff_START (1)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu1_clkoff_END (1)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu2_clkoff_START (2)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu2_clkoff_END (2)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu3_clkoff_START (3)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_cpu3_clkoff_END (3)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon0_clkoff_START (4)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon0_clkoff_END (4)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon1_clkoff_START (5)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon1_clkoff_END (5)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon2_clkoff_START (6)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon2_clkoff_END (6)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon3_clkoff_START (7)
#define SOC_SCTRL_SC_ACPU_CPUCLKOFF_neon3_clkoff_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_clken_sw : 1;
        unsigned int cpu_clken_sw : 1;
        unsigned int acpu_dap_clk_en : 1;
        unsigned int acpu_trace_clk_en : 1;
        unsigned int acpu_acp_clk_en : 1;
        unsigned int acpu_clk_en_7reserved : 3;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_ACPU_CPUCLKGATE_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_l2_clken_sw_START (0)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_l2_clken_sw_END (0)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_cpu_clken_sw_START (1)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_cpu_clken_sw_END (1)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_dap_clk_en_START (2)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_dap_clk_en_END (2)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_trace_clk_en_START (3)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_trace_clk_en_END (3)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_acp_clk_en_START (4)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_acp_clk_en_END (4)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_clk_en_7reserved_START (5)
#define SOC_SCTRL_SC_ACPU_CPUCLKGATE_acpu_clk_en_7reserved_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int core0en : 1;
        unsigned int core1en : 1;
        unsigned int core2en : 1;
        unsigned int core3en : 1;
        unsigned int l2cacheen : 1;
        unsigned int scuen : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_SCTRL_SCCPUCOREEN_UNION;
#endif
#define SOC_SCTRL_SCCPUCOREEN_core0en_START (0)
#define SOC_SCTRL_SCCPUCOREEN_core0en_END (0)
#define SOC_SCTRL_SCCPUCOREEN_core1en_START (1)
#define SOC_SCTRL_SCCPUCOREEN_core1en_END (1)
#define SOC_SCTRL_SCCPUCOREEN_core2en_START (2)
#define SOC_SCTRL_SCCPUCOREEN_core2en_END (2)
#define SOC_SCTRL_SCCPUCOREEN_core3en_START (3)
#define SOC_SCTRL_SCCPUCOREEN_core3en_END (3)
#define SOC_SCTRL_SCCPUCOREEN_l2cacheen_START (4)
#define SOC_SCTRL_SCCPUCOREEN_l2cacheen_END (4)
#define SOC_SCTRL_SCCPUCOREEN_scuen_START (5)
#define SOC_SCTRL_SCCPUCOREEN_scuen_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int core0dis : 1;
        unsigned int core1dis : 1;
        unsigned int core2dis : 1;
        unsigned int core3dis : 1;
        unsigned int l2cachedis : 1;
        unsigned int scuen : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_SCTRL_SCCPUCOREDIS_UNION;
#endif
#define SOC_SCTRL_SCCPUCOREDIS_core0dis_START (0)
#define SOC_SCTRL_SCCPUCOREDIS_core0dis_END (0)
#define SOC_SCTRL_SCCPUCOREDIS_core1dis_START (1)
#define SOC_SCTRL_SCCPUCOREDIS_core1dis_END (1)
#define SOC_SCTRL_SCCPUCOREDIS_core2dis_START (2)
#define SOC_SCTRL_SCCPUCOREDIS_core2dis_END (2)
#define SOC_SCTRL_SCCPUCOREDIS_core3dis_START (3)
#define SOC_SCTRL_SCCPUCOREDIS_core3dis_END (3)
#define SOC_SCTRL_SCCPUCOREDIS_l2cachedis_START (4)
#define SOC_SCTRL_SCCPUCOREDIS_l2cachedis_END (4)
#define SOC_SCTRL_SCCPUCOREDIS_scuen_START (5)
#define SOC_SCTRL_SCCPUCOREDIS_scuen_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int core0stat : 1;
        unsigned int core1stat : 1;
        unsigned int core2stat : 1;
        unsigned int core3stat : 1;
        unsigned int l2cachestat : 1;
        unsigned int scustat : 1;
        unsigned int reserved_0 : 2;
        unsigned int core0standywfi : 1;
        unsigned int core1standywfi : 1;
        unsigned int core2standywfi : 1;
        unsigned int core3standywfi : 1;
        unsigned int pwrctlo0 : 2;
        unsigned int pwrctlo1 : 2;
        unsigned int pwrctlo2 : 2;
        unsigned int pwrctlo3 : 2;
        unsigned int scuidle : 1;
        unsigned int l2_clkstopped : 1;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_SCTRL_SCCPUCORESTAT_UNION;
#endif
#define SOC_SCTRL_SCCPUCORESTAT_core0stat_START (0)
#define SOC_SCTRL_SCCPUCORESTAT_core0stat_END (0)
#define SOC_SCTRL_SCCPUCORESTAT_core1stat_START (1)
#define SOC_SCTRL_SCCPUCORESTAT_core1stat_END (1)
#define SOC_SCTRL_SCCPUCORESTAT_core2stat_START (2)
#define SOC_SCTRL_SCCPUCORESTAT_core2stat_END (2)
#define SOC_SCTRL_SCCPUCORESTAT_core3stat_START (3)
#define SOC_SCTRL_SCCPUCORESTAT_core3stat_END (3)
#define SOC_SCTRL_SCCPUCORESTAT_l2cachestat_START (4)
#define SOC_SCTRL_SCCPUCORESTAT_l2cachestat_END (4)
#define SOC_SCTRL_SCCPUCORESTAT_scustat_START (5)
#define SOC_SCTRL_SCCPUCORESTAT_scustat_END (5)
#define SOC_SCTRL_SCCPUCORESTAT_core0standywfi_START (8)
#define SOC_SCTRL_SCCPUCORESTAT_core0standywfi_END (8)
#define SOC_SCTRL_SCCPUCORESTAT_core1standywfi_START (9)
#define SOC_SCTRL_SCCPUCORESTAT_core1standywfi_END (9)
#define SOC_SCTRL_SCCPUCORESTAT_core2standywfi_START (10)
#define SOC_SCTRL_SCCPUCORESTAT_core2standywfi_END (10)
#define SOC_SCTRL_SCCPUCORESTAT_core3standywfi_START (11)
#define SOC_SCTRL_SCCPUCORESTAT_core3standywfi_END (11)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo0_START (12)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo0_END (13)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo1_START (14)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo1_END (15)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo2_START (16)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo2_END (17)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo3_START (18)
#define SOC_SCTRL_SCCPUCORESTAT_pwrctlo3_END (19)
#define SOC_SCTRL_SCCPUCORESTAT_scuidle_START (20)
#define SOC_SCTRL_SCCPUCORESTAT_scuidle_END (20)
#define SOC_SCTRL_SCCPUCORESTAT_l2_clkstopped_START (21)
#define SOC_SCTRL_SCCPUCORESTAT_l2_clkstopped_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_smpnamp : 4;
        unsigned int sc_pmupriv : 4;
        unsigned int sc_pmusecure : 4;
        unsigned int sc_standbywfe : 4;
        unsigned int reserved_0 : 1;
        unsigned int sc_l2c_idle : 1;
        unsigned int aarm_dbgack : 4;
        unsigned int aarm_dbgcpudone : 4;
        unsigned int reserved_1 : 2;
        unsigned int reserved_2 : 4;
    } reg;
} SOC_SCTRL_SC_ACPU_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_ACPU_STAT0_sc_smpnamp_START (0)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_smpnamp_END (3)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_pmupriv_START (4)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_pmupriv_END (7)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_pmusecure_START (8)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_pmusecure_END (11)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_standbywfe_START (12)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_standbywfe_END (15)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_l2c_idle_START (17)
#define SOC_SCTRL_SC_ACPU_STAT0_sc_l2c_idle_END (17)
#define SOC_SCTRL_SC_ACPU_STAT0_aarm_dbgack_START (18)
#define SOC_SCTRL_SC_ACPU_STAT0_aarm_dbgack_END (21)
#define SOC_SCTRL_SC_ACPU_STAT0_aarm_dbgcpudone_START (22)
#define SOC_SCTRL_SC_ACPU_STAT0_aarm_dbgcpudone_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SCTRL_SC_ACPU_STAT1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int carm_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int carm_ramctrl_s_emaw : 2;
        unsigned int carm_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int carm_ramctrl_s_ret1n : 1;
        unsigned int carm_ramctrl_s_ret2n : 1;
        unsigned int carm_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int carm_cp15disable : 1;
        unsigned int carm_cfgdisable : 1;
        unsigned int clk_off_carm_sys : 1;
        unsigned int carm_cfgnmfi : 1;
        unsigned int reserved_3 : 7;
        unsigned int reserved_4 : 1;
        unsigned int mcpu_debug_req : 1;
        unsigned int carm_timestamp_en : 1;
        unsigned int carm_event_trigger_en : 1;
        unsigned int reserved_5 : 1;
    } reg;
} SOC_SCTRL_SC_CARM_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ema_START (0)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ema_END (2)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_emaw_START (4)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_emaw_END (5)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_emas_START (6)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_emas_END (6)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ret1n_START (10)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ret1n_END (10)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ret2n_START (11)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_ret2n_END (11)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_pgen_START (12)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_ramctrl_s_pgen_END (12)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cp15disable_START (16)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cp15disable_END (16)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cfgdisable_START (17)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cfgdisable_END (17)
#define SOC_SCTRL_SC_CARM_CTRL0_clk_off_carm_sys_START (18)
#define SOC_SCTRL_SC_CARM_CTRL0_clk_off_carm_sys_END (18)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cfgnmfi_START (19)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_cfgnmfi_END (19)
#define SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_START (28)
#define SOC_SCTRL_SC_CARM_CTRL0_mcpu_debug_req_END (28)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_timestamp_en_START (29)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_timestamp_en_END (29)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_event_trigger_en_START (30)
#define SOC_SCTRL_SC_CARM_CTRL0_carm_event_trigger_en_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int carm_filterstart : 12;
        unsigned int carm_filterend : 12;
        unsigned int carm_filteren : 1;
        unsigned int carm_vinithi : 1;
        unsigned int reserved : 6;
    } reg;
} SOC_SCTRL_SC_CARM_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filterstart_START (0)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filterstart_END (11)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filterend_START (12)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filterend_END (23)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filteren_START (24)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_filteren_END (24)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_vinithi_START (25)
#define SOC_SCTRL_SC_CARM_CTRL1_carm_vinithi_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int carm_pmupriv : 1;
        unsigned int carm_pmusecure : 1;
        unsigned int carm_smp_amp : 1;
        unsigned int carm_standby_wfi : 1;
        unsigned int carm_standby_wfe : 1;
        unsigned int carm_dbgack : 1;
        unsigned int carm_dbgcpudone : 1;
        unsigned int undefined : 25;
    } reg;
} SOC_SCTRL_SC_CARM_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_CARM_STAT0_carm_pmupriv_START (0)
#define SOC_SCTRL_SC_CARM_STAT0_carm_pmupriv_END (0)
#define SOC_SCTRL_SC_CARM_STAT0_carm_pmusecure_START (1)
#define SOC_SCTRL_SC_CARM_STAT0_carm_pmusecure_END (1)
#define SOC_SCTRL_SC_CARM_STAT0_carm_smp_amp_START (2)
#define SOC_SCTRL_SC_CARM_STAT0_carm_smp_amp_END (2)
#define SOC_SCTRL_SC_CARM_STAT0_carm_standby_wfi_START (3)
#define SOC_SCTRL_SC_CARM_STAT0_carm_standby_wfi_END (3)
#define SOC_SCTRL_SC_CARM_STAT0_carm_standby_wfe_START (4)
#define SOC_SCTRL_SC_CARM_STAT0_carm_standby_wfe_END (4)
#define SOC_SCTRL_SC_CARM_STAT0_carm_dbgack_START (5)
#define SOC_SCTRL_SC_CARM_STAT0_carm_dbgack_END (5)
#define SOC_SCTRL_SC_CARM_STAT0_carm_dbgcpudone_START (6)
#define SOC_SCTRL_SC_CARM_STAT0_carm_dbgcpudone_END (6)
#define SOC_SCTRL_SC_CARM_STAT0_undefined_START (7)
#define SOC_SCTRL_SC_CARM_STAT0_undefined_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mp_dma_req_sel0_reserved : 12;
        unsigned int mp_dma_req_sel0_uart5_rx : 1;
        unsigned int mp_dma_req_sel0_uart5_tx : 1;
        unsigned int mp_dma_req_sel0_sci0_rx : 1;
        unsigned int mp_dma_req_sel0_sci0_tx : 1;
        unsigned int mp_dma_req_sel0_msk_reserved : 12;
        unsigned int mp_dma_req_sel0_msk_uart5_rx : 1;
        unsigned int mp_dma_req_sel0_msk_uart5_tx : 1;
        unsigned int mp_dma_req_sel0_msk_sci0_rx : 1;
        unsigned int mp_dma_req_sel0_msk_sci0_tx : 1;
    } reg;
} SOC_SCTRL_SC_MPDMAC_SEL_EN0_UNION;
#endif
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_reserved_START (0)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_reserved_END (11)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_uart5_rx_START (12)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_uart5_rx_END (12)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_uart5_tx_START (13)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_uart5_tx_END (13)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_sci0_rx_START (14)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_sci0_rx_END (14)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_sci0_tx_START (15)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_sci0_tx_END (15)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_reserved_START (16)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_reserved_END (27)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_uart5_rx_START (28)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_uart5_rx_END (28)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_uart5_tx_START (29)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_uart5_tx_END (29)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_sci0_rx_START (30)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_sci0_rx_END (30)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_sci0_tx_START (31)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN0_mp_dma_req_sel0_msk_sci0_tx_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mp_dma_req_sel1_sci1_rx : 1;
        unsigned int mp_dma_req_sel1_sci1_tx : 1;
        unsigned int mp_dma_req_sel1_sio0_rx : 1;
        unsigned int mp_dma_req_sel1_sio0_tx : 1;
        unsigned int mp_dma_req_sel1_sio1_rx : 1;
        unsigned int mp_dma_req_sel1_sio1_tx : 1;
        unsigned int mp_dma_req_sel1_sio2_rx : 1;
        unsigned int mp_dma_req_sel1_sio2_tx : 1;
        unsigned int mp_dma_req_sel1_sio3_rx : 1;
        unsigned int mp_dma_req_sel1_sio3_tx : 1;
        unsigned int reserved_0 : 5;
        unsigned int reserved_1 : 1;
        unsigned int mp_dma_req_sel1_msk_sci1_rx : 1;
        unsigned int mp_dma_req_sel1_msk_sci1_tx : 1;
        unsigned int mp_dma_req_sel1_msk_sio0_rx : 1;
        unsigned int mp_dma_req_sel1_msk_sio0_tx : 1;
        unsigned int mp_dma_req_sel1_msk_sio1_rx : 1;
        unsigned int mp_dma_req_sel1_msk_sio1_tx : 1;
        unsigned int mp_dma_req_sel1_msk_sio2_rx : 1;
        unsigned int mp_dma_req_sel1_msk_sio2_tx : 1;
        unsigned int mp_dma_req_sel1_msk_sio3_rx : 1;
        unsigned int mp_dma_req_sel1_msk_sio3_tx : 1;
        unsigned int reserved_2 : 5;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_SCTRL_SC_MPDMAC_SEL_EN1_UNION;
#endif
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sci1_rx_START (0)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sci1_rx_END (0)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sci1_tx_START (1)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sci1_tx_END (1)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio0_rx_START (2)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio0_rx_END (2)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio0_tx_START (3)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio0_tx_END (3)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio1_rx_START (4)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio1_rx_END (4)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio1_tx_START (5)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio1_tx_END (5)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio2_rx_START (6)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio2_rx_END (6)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio2_tx_START (7)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio2_tx_END (7)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio3_rx_START (8)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio3_rx_END (8)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio3_tx_START (9)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_sio3_tx_END (9)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sci1_rx_START (16)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sci1_rx_END (16)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sci1_tx_START (17)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sci1_tx_END (17)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio0_rx_START (18)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio0_rx_END (18)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio0_tx_START (19)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio0_tx_END (19)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio1_rx_START (20)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio1_rx_END (20)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio1_tx_START (21)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio1_tx_END (21)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio2_rx_START (22)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio2_rx_END (22)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio2_tx_START (23)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio2_tx_END (23)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio3_rx_START (24)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio3_rx_END (24)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio3_tx_START (25)
#define SOC_SCTRL_SC_MPDMAC_SEL_EN1_mp_dma_req_sel1_msk_sio3_tx_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_clk_gate_en31_reserved : 32;
    } reg;
} SOC_SCTRL_SC_AUTO_CLK_GATE0_UNION;
#endif
#define SOC_SCTRL_SC_AUTO_CLK_GATE0_auto_clk_gate_en31_reserved_START (0)
#define SOC_SCTRL_SC_AUTO_CLK_GATE0_auto_clk_gate_en31_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int auto_clk_gate_en1 : 32;
    } reg;
} SOC_SCTRL_SC_AUTO_CLK_GATE1_UNION;
#endif
#define SOC_SCTRL_SC_AUTO_CLK_GATE1_auto_clk_gate_en1_START (0)
#define SOC_SCTRL_SC_AUTO_CLK_GATE1_auto_clk_gate_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved7 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED7_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED7_sc_reserved7_START (0)
#define SOC_SCTRL_SC_RESERVED7_sc_reserved7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved8 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED8_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED8_sc_reserved8_START (0)
#define SOC_SCTRL_SC_RESERVED8_sc_reserved8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved11 : 32;
    } reg;
} SOC_SCTRL_SC_PeriphAxi_priority_set_UNION;
#endif
#define SOC_SCTRL_SC_PeriphAxi_priority_set_sc_reserved11_START (0)
#define SOC_SCTRL_SC_PeriphAxi_priority_set_sc_reserved11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved12 : 32;
    } reg;
} SOC_SCTRL_SC_SystemAxi_mst_priority_set_UNION;
#endif
#define SOC_SCTRL_SC_SystemAxi_mst_priority_set_sc_reserved12_START (0)
#define SOC_SCTRL_SC_SystemAxi_mst_priority_set_sc_reserved12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved13 : 32;
    } reg;
} SOC_SCTRL_SC_SystemAxi_slv_priority_set_UNION;
#endif
#define SOC_SCTRL_SC_SystemAxi_slv_priority_set_sc_reserved13_START (0)
#define SOC_SCTRL_SC_SystemAxi_slv_priority_set_sc_reserved13_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved14 : 32;
    } reg;
} SOC_SCTRL_SC_MPeriph_mst_priority_set_UNION;
#endif
#define SOC_SCTRL_SC_MPeriph_mst_priority_set_sc_reserved14_START (0)
#define SOC_SCTRL_SC_MPeriph_mst_priority_set_sc_reserved14_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved15 : 32;
    } reg;
} SOC_SCTRL_SC_MPeriph_slv_priority_set_UNION;
#endif
#define SOC_SCTRL_SC_MPeriph_slv_priority_set_sc_reserved15_START (0)
#define SOC_SCTRL_SC_MPeriph_slv_priority_set_sc_reserved15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved16 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED16_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED16_sc_reserved16_START (0)
#define SOC_SCTRL_SC_RESERVED16_sc_reserved16_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved17 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED17_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED17_sc_reserved17_START (0)
#define SOC_SCTRL_SC_RESERVED17_sc_reserved17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved18 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED18_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED18_sc_reserved18_START (0)
#define SOC_SCTRL_SC_RESERVED18_sc_reserved18_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved21 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED21_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED21_sc_reserved21_START (0)
#define SOC_SCTRL_SC_RESERVED21_sc_reserved21_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved22 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED22_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED22_sc_reserved22_START (0)
#define SOC_SCTRL_SC_RESERVED22_sc_reserved22_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved23 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED23_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED23_sc_reserved23_START (0)
#define SOC_SCTRL_SC_RESERVED23_sc_reserved23_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved24 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED24_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED24_sc_reserved24_START (0)
#define SOC_SCTRL_SC_RESERVED24_sc_reserved24_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved25 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED25_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED25_sc_reserved25_START (0)
#define SOC_SCTRL_SC_RESERVED25_sc_reserved25_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved26 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED26_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED26_sc_reserved26_START (0)
#define SOC_SCTRL_SC_RESERVED26_sc_reserved26_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved27 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED27_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED27_sc_reserved27_START (0)
#define SOC_SCTRL_SC_RESERVED27_sc_reserved27_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved28 : 32;
    } reg;
} SOC_SCTRL_SC_RESERVED28_UNION;
#endif
#define SOC_SCTRL_SC_RESERVED28_sc_reserved28_START (0)
#define SOC_SCTRL_SC_RESERVED28_sc_reserved28_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl0_mali : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL0_media_subsys_ctrl0_mali_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL0_media_subsys_ctrl0_mali_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl1_csysreq : 1;
        unsigned int media_subsys_ctrl1_g2d : 23;
        unsigned int media_subsys_ctrl1 : 8;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_csysreq_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_csysreq_END (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_g2d_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_g2d_END (23)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_START (24)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL1_media_subsys_ctrl1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl0_isp_dfs_req_i : 1;
        unsigned int media_subsys_ctrl2_isp_p_pwdn_i : 1;
        unsigned int media_subsys_ctrl2 : 30;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl0_isp_dfs_req_i_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl0_isp_dfs_req_i_END (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl2_isp_p_pwdn_i_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl2_isp_p_pwdn_i_END (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl2_START (2)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL2_media_subsys_ctrl2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl1_vpp_srst_req : 1;
        unsigned int media_subsys_ctrl3 : 31;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_END (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl3_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl4_hifi_nmi : 16;
        unsigned int media_subsys_ctrl4_reserved : 16;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_media_subsys_ctrl4_hifi_nmi_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_media_subsys_ctrl4_hifi_nmi_END (15)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_media_subsys_ctrl4_reserved_START (16)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL4_media_subsys_ctrl4_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hifi_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int hifi_ramctrl_s_emaw : 2;
        unsigned int hifi_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int hifi_ramctrl_s_ret1n : 1;
        unsigned int hifi_ramctrl_s_ret2n : 1;
        unsigned int hifi_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int media_subsys_ctrl5 : 16;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ema_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ema_END (2)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_emaw_START (4)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_emaw_END (5)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_emas_START (6)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_emas_END (6)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ret1n_START (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ret1n_END (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ret2n_START (11)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_ret2n_END (11)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_pgen_START (12)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_hifi_ramctrl_s_pgen_END (12)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_media_subsys_ctrl5_START (16)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL5_media_subsys_ctrl5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_ctrl6 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL6_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL6_media_subsys_ctrl6_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL6_media_subsys_ctrl6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int media_subsys_ctrl7_i2s_xfs : 1;
        unsigned int media_subsys_ctrl7_pcm0_xfs : 1;
        unsigned int media_subsys_ctrl7_pcm1_xfs : 1;
        unsigned int media_subsys_ctrl7_ISP_FSIN0 : 1;
        unsigned int media_subsys_ctrl7_ISP_FSIN1 : 1;
        unsigned int media_subsys_ctrl7_ISP_I2C0OD : 1;
        unsigned int media_subsys_ctrl7_ISP_I2C1OD : 1;
        unsigned int media_subsys_ctrl7_dsiphy_mux : 1;
        unsigned int media_subsys_ctrl7_dsiphy_shudownz : 1;
        unsigned int media_subsys_ctrl7_dsiphy_rstz : 1;
        unsigned int media_subsys_ctrl7_csi0phy_mux : 1;
        unsigned int media_subsys_ctrl7_csi0phy_shudownz : 1;
        unsigned int media_subsys_ctrl7_csi0phy_rstz : 1;
        unsigned int media_subsys_ctrl7_csi2phy_mux : 1;
        unsigned int media_subsys_ctrl7_csi2phy_shudownz : 1;
        unsigned int media_subsys_ctrl7_csi2phy_rstz : 1;
        unsigned int reserved_1 : 7;
        unsigned int media_subsys_ctrl7_pcm2_xfs : 1;
        unsigned int media_subsys_ctrl7 : 7;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_i2s_xfs_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_i2s_xfs_END (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm0_xfs_START (2)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm0_xfs_END (2)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm1_xfs_START (3)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm1_xfs_END (3)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_FSIN0_START (4)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_FSIN0_END (4)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_FSIN1_START (5)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_FSIN1_END (5)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_START (6)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C0OD_END (6)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_START (7)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_ISP_I2C1OD_END (7)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_mux_START (8)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_mux_END (8)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_shudownz_START (9)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_shudownz_END (9)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_rstz_START (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_dsiphy_rstz_END (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_mux_START (11)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_mux_END (11)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_shudownz_START (12)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_shudownz_END (12)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_rstz_START (13)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi0phy_rstz_END (13)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_mux_START (14)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_mux_END (14)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_shudownz_START (15)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_shudownz_END (15)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_rstz_START (16)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_csi2phy_rstz_END (16)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm2_xfs_START (24)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_pcm2_xfs_END (24)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_START (25)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL7_media_subsys_ctrl7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 8;
        unsigned int media_subsys_state0 : 22;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT0_media_subsys_state0_START (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT0_media_subsys_state0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state1_csysack : 1;
        unsigned int media_subsys_state1_cactive : 1;
        unsigned int media_subsys_state1_debug_out : 8;
        unsigned int media_subsys_state1 : 22;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_csysack_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_csysack_END (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_cactive_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_cactive_END (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_debug_out_START (2)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_debug_out_END (9)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_START (10)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT1_media_subsys_state1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state2 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT2_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT2_media_subsys_state2_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT2_media_subsys_state2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state3 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT3_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT3_media_subsys_state3_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT3_media_subsys_state3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state4 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT4_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT4_media_subsys_state4_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT4_media_subsys_state4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdmi_hw_rd_finish : 1;
        unsigned int media_subsys_state5 : 31;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_hdmi_hw_rd_finish_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_hdmi_hw_rd_finish_END (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_media_subsys_state5_START (1)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT5_media_subsys_state5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state6 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT6_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT6_media_subsys_state6_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT6_media_subsys_state6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int media_subsys_state7 : 32;
    } reg;
} SOC_SCTRL_SC_MEDIA_SUBSYS_STAT7_UNION;
#endif
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT7_media_subsys_state7_START (0)
#define SOC_SCTRL_SC_MEDIA_SUBSYS_STAT7_media_subsys_state7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ltedsp_runstall : 1;
        unsigned int ltedsp_statvectorsel : 1;
        unsigned int ltedsp_ocdhaltonreset : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 2;
        unsigned int reserved_3 : 2;
        unsigned int bbpabb_subsys_ctrl0 : 23;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_runstall_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_runstall_END (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_statvectorsel_START (1)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_statvectorsel_END (1)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_ocdhaltonreset_START (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_ltedsp_ocdhaltonreset_END (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_bbpabb_subsys_ctrl0_START (9)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL0_bbpabb_subsys_ctrl0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int bbpabb_subsys_ctrl1_ltedsp_cg_en : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 2;
        unsigned int bbpabb_subsys_ctrl1_gubbp_bbpaxi_awuser : 4;
        unsigned int bbpabb_subsys_ctrl1_gubbp_bbpaxi_aruser : 4;
        unsigned int bbpabb_subsys_ctrl1_ltbbp_bbpaxi_aruser : 4;
        unsigned int bbpabb_subsys_ctrl1_ltbbp_bbpaxi_awuser : 4;
        unsigned int bbpabb_subsys_ctrl1_bbe16_pifqos : 4;
        unsigned int reserved_6 : 4;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltedsp_cg_en_START (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltedsp_cg_en_END (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_gubbp_bbpaxi_awuser_START (8)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_gubbp_bbpaxi_awuser_END (11)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_gubbp_bbpaxi_aruser_START (12)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_gubbp_bbpaxi_aruser_END (15)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltbbp_bbpaxi_aruser_START (16)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltbbp_bbpaxi_aruser_END (19)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltbbp_bbpaxi_awuser_START (20)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_ltbbp_bbpaxi_awuser_END (23)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_bbe16_pifqos_START (24)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL1_bbpabb_subsys_ctrl1_bbe16_pifqos_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_ctrl3_bbe_nmi_irq : 16;
        unsigned int bbpabb_subsys_ctrl3_bbe_nmi_irq_msk : 16;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_bbpabb_subsys_ctrl3_bbe_nmi_irq_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_bbpabb_subsys_ctrl3_bbe_nmi_irq_END (15)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_bbpabb_subsys_ctrl3_bbe_nmi_irq_msk_START (16)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL2_bbpabb_subsys_ctrl3_bbe_nmi_irq_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpaxi_priority_set : 2;
        unsigned int bbp_axi_bsi_cg_en : 1;
        unsigned int bbp_axi_rs_cg_en : 1;
        unsigned int bbp_axi_gs_cg_en : 1;
        unsigned int bus_lockdown_protect : 2;
        unsigned int reserved : 9;
        unsigned int bus_bbp_ctrl_atpramctrl : 16;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbpaxi_priority_set_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbpaxi_priority_set_END (1)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_bsi_cg_en_START (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_bsi_cg_en_END (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_rs_cg_en_START (3)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_rs_cg_en_END (3)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_gs_cg_en_START (4)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bbp_axi_gs_cg_en_END (4)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bus_lockdown_protect_START (5)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bus_lockdown_protect_END (6)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bus_bbp_ctrl_atpramctrl_START (16)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_CTRL3_bus_bbp_ctrl_atpramctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_state0_reserved0 : 3;
        unsigned int bbe16_xocdmode : 1;
        unsigned int bbe16_pwaitmode : 1;
        unsigned int bbpabb_subsys_state0 : 27;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbpabb_subsys_state0_reserved0_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbpabb_subsys_state0_reserved0_END (2)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbe16_xocdmode_START (3)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbe16_xocdmode_END (3)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbe16_pwaitmode_START (4)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbe16_pwaitmode_END (4)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbpabb_subsys_state0_START (5)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT0_bbpabb_subsys_state0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_state1 : 32;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_STAT1_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT1_bbpabb_subsys_state1_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT1_bbpabb_subsys_state1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_state2 : 32;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_STAT2_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT2_bbpabb_subsys_state2_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT2_bbpabb_subsys_state2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_state3 : 32;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_STAT3_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT3_bbpabb_subsys_state3_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT3_bbpabb_subsys_state3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbpabb_subsys_state4 : 32;
    } reg;
} SOC_SCTRL_SC_BBPABB_SUBSYS_STAT4_UNION;
#endif
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT4_bbpabb_subsys_state4_START (0)
#define SOC_SCTRL_SC_BBPABB_SUBSYS_STAT4_bbpabb_subsys_state4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken0_clk_acpu_atb : 1;
        unsigned int periph_clken0_clk_acpu_dap : 1;
        unsigned int periph_clken0_acpu_x2x_s : 1;
        unsigned int periph_clken0_clk_ddrc : 1;
        unsigned int periph_clken0_clk_ddrphy : 1;
        unsigned int periph_clken0_clk_ddrio : 1;
        unsigned int periph_clken0_pclk_ddrc : 1;
        unsigned int periph_clken0_pclk_p2p_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken0_clk_kernel_mcpu : 1;
        unsigned int periph_clken0_clk_mcpu_extern : 1;
        unsigned int periph_clken0_clk_mcpu_brg : 1;
        unsigned int periph_clken0_clk_mcpu_dap : 1;
        unsigned int periph_clken0_clk_mcpu_atb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_acpu_atb_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_acpu_atb_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_acpu_dap_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_acpu_dap_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrc_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrc_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrphy_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrphy_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrio_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_ddrio_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_pclk_ddrc_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_pclk_ddrc_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_pclk_p2p_ddrc_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_pclk_p2p_ddrc_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_kernel_mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_kernel_mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_extern_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_extern_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_brg_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_brg_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_dap_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_dap_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_atb_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN0_periph_clken0_clk_mcpu_atb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis0_clk_acpu_atb : 1;
        unsigned int periph_clkdis0_clk_acpu_dap : 1;
        unsigned int periph_clkdis0_acpu_x2x_s : 1;
        unsigned int periph_clkdis0_clk_ddrc : 1;
        unsigned int periph_clkdis0_clk_ddrphy : 1;
        unsigned int periph_clkdis0_clk_ddrio : 1;
        unsigned int periph_clkdis0_pclk_ddrc : 1;
        unsigned int periph_clkdis0_pclk_p2p_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis0_clk_kernel_mcpu : 1;
        unsigned int periph_clkdis0_clk_mcpu_extern : 1;
        unsigned int periph_clkdis0_clk_mcpu_brg : 1;
        unsigned int periph_clkdis0_clk_mcpu_dap : 1;
        unsigned int periph_clkdis0_clk_mcpu_atb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_acpu_atb_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_acpu_atb_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_acpu_dap_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_acpu_dap_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrc_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrc_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrphy_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrphy_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrio_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_ddrio_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_pclk_ddrc_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_pclk_ddrc_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_pclk_p2p_ddrc_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_pclk_p2p_ddrc_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_kernel_mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_kernel_mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_extern_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_extern_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_brg_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_brg_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_dap_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_dap_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_atb_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS0_periph_clkdis0_clk_mcpu_atb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat0_clk_acpu_atb : 1;
        unsigned int periph_clkstat0_clk_acpu_dap : 1;
        unsigned int periph_clkstat0_acpu_x2x_s : 1;
        unsigned int periph_clkstat0_clk_ddrc : 1;
        unsigned int periph_clkstat0_clk_ddrphy : 1;
        unsigned int periph_clkstat0_clk_ddrio : 1;
        unsigned int periph_clkstat0_pclk_ddrc : 1;
        unsigned int periph_clkstat0_pclk_p2p_ddrc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat0_clk_kernel_mcpu : 1;
        unsigned int periph_clkstat0_clk_mcpu_extern : 1;
        unsigned int periph_clkstat0_clk_mcpu_brg : 1;
        unsigned int periph_clkstat0_clk_mcpu_dap : 1;
        unsigned int periph_clkstat0_clk_mcpu_atb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
        unsigned int reserved_18 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_acpu_atb_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_acpu_atb_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_acpu_dap_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_acpu_dap_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrc_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrc_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrphy_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrphy_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrio_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_ddrio_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_pclk_ddrc_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_pclk_ddrc_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_pclk_p2p_ddrc_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_pclk_p2p_ddrc_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_kernel_mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_kernel_mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_extern_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_extern_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_brg_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_brg_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_dap_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_dap_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_atb_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT0_periph_clkstat0_clk_mcpu_atb_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken1_uart0_pclk : 1;
        unsigned int periph_clken1_uart0 : 1;
        unsigned int periph_clken1_uart1_pclk : 1;
        unsigned int periph_clken1_uart1 : 1;
        unsigned int periph_clken1_uart2_pclk : 1;
        unsigned int periph_clken1_uart2 : 1;
        unsigned int periph_clken1_uart3_pclk : 1;
        unsigned int periph_clken1_uart3 : 1;
        unsigned int periph_clken1_uart4_pclk : 1;
        unsigned int periph_clken1_uart4 : 1;
        unsigned int periph_clken1_uart5_pclk : 1;
        unsigned int periph_clken1_uart5 : 1;
        unsigned int periph_clken1_uart6_pclk : 1;
        unsigned int periph_clken1_uart6 : 1;
        unsigned int periph_clken1_spi0_pclk : 1;
        unsigned int periph_clken1_spi0 : 1;
        unsigned int periph_clken1_spi1_pclk : 1;
        unsigned int periph_clken1_spi1 : 1;
        unsigned int periph_clken1_i2c0_pclk : 1;
        unsigned int periph_clken1_i2c0 : 1;
        unsigned int periph_clken1_i2c1_pclk : 1;
        unsigned int periph_clken1_i2c1 : 1;
        unsigned int periph_clken1_i2c2_pclk : 1;
        unsigned int periph_clken1_i2c2 : 1;
        unsigned int periph_clken1_i2c3_pclk : 1;
        unsigned int periph_clken1_i2c3 : 1;
        unsigned int periph_clken1_i2c4_pclk : 1;
        unsigned int periph_clken1_i2c4 : 1;
        unsigned int periph_clken1_i2c5_pclk : 1;
        unsigned int periph_clken1_i2c5 : 1;
        unsigned int periph_clken1_clk_tcxo_gps : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_pclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_pclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart2_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_pclk_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_pclk_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart3_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_pclk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_pclk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart4_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_pclk_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_pclk_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart5_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_pclk_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_pclk_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_uart6_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_pclk_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_pclk_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_pclk_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_pclk_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_spi1_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_pclk_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_pclk_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c0_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_pclk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_pclk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c1_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_pclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_pclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c2_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_pclk_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_pclk_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c3_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_pclk_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_pclk_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c4_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_pclk_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_pclk_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_i2c5_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_clk_tcxo_gps_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN1_periph_clken1_clk_tcxo_gps_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis1_uart0_pclk : 1;
        unsigned int periph_clkdis1_uart0 : 1;
        unsigned int periph_clkdis1_uart1_pclk : 1;
        unsigned int periph_clkdis1_uart1 : 1;
        unsigned int periph_clkdis1_uart2_pclk : 1;
        unsigned int periph_clkdis1_uart2 : 1;
        unsigned int periph_clkdis1_uart3_pclk : 1;
        unsigned int periph_clkdis1_uart3 : 1;
        unsigned int periph_clkdis1_uart4_pclk : 1;
        unsigned int periph_clkdis1_uart4 : 1;
        unsigned int periph_clkdis1_uart5_pclk : 1;
        unsigned int periph_clkdis1_uart5 : 1;
        unsigned int periph_clkdis1_uart6_pclk : 1;
        unsigned int periph_clkdis1_uart6 : 1;
        unsigned int periph_clkdis1_spi0_pclk : 1;
        unsigned int periph_clkdis1_spi0 : 1;
        unsigned int periph_clkdis1_spi1_pclk : 1;
        unsigned int periph_clkdis1_spi1 : 1;
        unsigned int periph_clkdis1_i2c0_pclk : 1;
        unsigned int periph_clkdis1_i2c0 : 1;
        unsigned int periph_clkdis1_i2c1_pclk : 1;
        unsigned int periph_clkdis1_i2c1 : 1;
        unsigned int periph_clkdis1_i2c2_pclk : 1;
        unsigned int periph_clkdis1_i2c2 : 1;
        unsigned int periph_clkdis1_i2c3_pclk : 1;
        unsigned int periph_clkdis1_i2c3 : 1;
        unsigned int periph_clkdis1_i2c4_pclk : 1;
        unsigned int periph_clkdis1_i2c4 : 1;
        unsigned int periph_clkdis1_i2c5_pclk : 1;
        unsigned int periph_clkdis1_i2c5 : 1;
        unsigned int periph_clkdis1_clk_tcxo_gps : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart2_pclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart2_pclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart2_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart2_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart3_pclk_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart3_pclk_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart3_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart3_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart4_pclk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart4_pclk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart4_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart4_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart5_pclk_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart5_pclk_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart5_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart5_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart6_pclk_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart6_pclk_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart6_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_uart6_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi0_pclk_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi0_pclk_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi1_pclk_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi1_pclk_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi1_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_spi1_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c0_pclk_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c0_pclk_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c0_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c0_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c1_pclk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c1_pclk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c1_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c1_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c2_pclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c2_pclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c2_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c2_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c3_pclk_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c3_pclk_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c3_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c3_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c4_pclk_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c4_pclk_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c4_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c4_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c5_pclk_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c5_pclk_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c5_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_i2c5_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_clk_tcxo_gps_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS1_periph_clkdis1_clk_tcxo_gps_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat1_uart0_pclk : 1;
        unsigned int periph_clkstat1_uart0 : 1;
        unsigned int periph_clkstat1_uart1_pclk : 1;
        unsigned int periph_clkstat1_uart1 : 1;
        unsigned int periph_clkstat1_uart2_pclk : 1;
        unsigned int periph_clkstat1_uart2 : 1;
        unsigned int periph_clkstat1_uart3_pclk : 1;
        unsigned int periph_clkstat1_uart3 : 1;
        unsigned int periph_clkstat1_uart4_pclk : 1;
        unsigned int periph_clkstat1_uart4 : 1;
        unsigned int periph_clkstat1_uart5_pclk : 1;
        unsigned int periph_clkstat1_uart5 : 1;
        unsigned int periph_clkstat1_uart6_pclk : 1;
        unsigned int periph_clkstat1_uart6 : 1;
        unsigned int periph_clkstat1_spi0_pclk : 1;
        unsigned int periph_clkstat1_spi0 : 1;
        unsigned int periph_clkstat1_spi1_pclk : 1;
        unsigned int periph_clkstat1_spi1 : 1;
        unsigned int periph_clkstat1_i2c0_pclk : 1;
        unsigned int periph_clkstat1_i2c0 : 1;
        unsigned int periph_clkstat1_i2c1_pclk : 1;
        unsigned int periph_clkstat1_i2c1 : 1;
        unsigned int periph_clkstat1_i2c2_pclk : 1;
        unsigned int periph_clkstat1_i2c2 : 1;
        unsigned int periph_clkstat1_i2c3_pclk : 1;
        unsigned int periph_clkstat1_i2c3 : 1;
        unsigned int periph_clkstat1_i2c4_pclk : 1;
        unsigned int periph_clkstat1_i2c4 : 1;
        unsigned int periph_clkstat1_i2c5_pclk : 1;
        unsigned int periph_clkstat1_i2c5 : 1;
        unsigned int periph_clkstat1_clk_tcxo_gps : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart2_pclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart2_pclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart2_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart2_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart3_pclk_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart3_pclk_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart3_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart3_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart4_pclk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart4_pclk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart4_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart4_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart5_pclk_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart5_pclk_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart5_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart5_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart6_pclk_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart6_pclk_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart6_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_uart6_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi0_pclk_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi0_pclk_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi1_pclk_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi1_pclk_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi1_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_spi1_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c0_pclk_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c0_pclk_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c0_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c0_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c1_pclk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c1_pclk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c1_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c1_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c2_pclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c2_pclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c2_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c2_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c3_pclk_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c3_pclk_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c3_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c3_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c4_pclk_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c4_pclk_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c4_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c4_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c5_pclk_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c5_pclk_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c5_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_i2c5_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_clk_tcxo_gps_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT1_periph_clkstat1_clk_tcxo_gps_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken2_pwm0_pclk : 1;
        unsigned int periph_clken2_pwm0 : 1;
        unsigned int periph_clken2_pwm1_pclk : 1;
        unsigned int periph_clken2_pwm1 : 1;
        unsigned int periph_clken2_clk_coresight_atb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clken2_clk_coresight_tpiu : 1;
        unsigned int periph_clken2_clk_coresight_debug_apb : 1;
        unsigned int periph_clken2_tsensor0_clk : 1;
        unsigned int periph_clken2_tsensor1_clk : 1;
        unsigned int periph_clken2_ipf_axi : 1;
        unsigned int periph_clken2_ipf_hclk : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clken2_socp_axi : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken2_seceng_core : 1;
        unsigned int periph_clken2_seceng_axi : 1;
        unsigned int periph_clken2_ap_dmac_axi0 : 1;
        unsigned int periph_clken2_ap_dmac_axi1 : 1;
        unsigned int periph_clken2_usbotg_bus_clk : 1;
        unsigned int periph_clken2_usbotg_work_clk : 1;
        unsigned int periph_clken2_ts_clk : 1;
        unsigned int periph_clken2_ts_hclk : 1;
        unsigned int periph_clken2_cs_dap_off : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clken2_clk_x2sram : 1;
        unsigned int periph_clken2_x2sram_rom : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_pwm1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_atb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_atb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_tpiu_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_tpiu_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_debug_apb_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_coresight_debug_apb_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor0_clk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor0_clk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor1_clk_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_tsensor1_clk_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ipf_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ipf_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ipf_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ipf_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_socp_axi_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_socp_axi_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_seceng_core_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_seceng_core_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_seceng_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_seceng_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi0_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi0_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ap_dmac_axi1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_bus_clk_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_bus_clk_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_work_clk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_usbotg_work_clk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_clk_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_clk_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_hclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_ts_hclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_cs_dap_off_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_cs_dap_off_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_x2sram_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_clk_x2sram_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_x2sram_rom_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN2_periph_clken2_x2sram_rom_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis2_pwm0_pclk : 1;
        unsigned int periph_clkdis2_pwm0 : 1;
        unsigned int periph_clkdis2_pwm1_pclk : 1;
        unsigned int periph_clkdis2_pwm1 : 1;
        unsigned int periph_clkdis2_clk_coresight_atb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkdis2_clk_coresight_tpiu : 1;
        unsigned int periph_clkdis2_clk_coresight_debug_apb : 1;
        unsigned int periph_clkdis2_tsensor0_clk : 1;
        unsigned int periph_clkdis2_tsensor1_clk : 1;
        unsigned int periph_clkdis2_ipf_axi : 1;
        unsigned int periph_clkdis2_ipf_hclk : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clkdis2_socp_axi : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis2_seceng_core : 1;
        unsigned int periph_clkdis2_seceng_axi : 1;
        unsigned int periph_clkdis2_ap_dmac_axi0 : 1;
        unsigned int periph_clkdis2_ap_dmac_axi1 : 1;
        unsigned int periph_clkdis2_usbotg_bus_clk : 1;
        unsigned int periph_clkdis2_usbotg_work_clk : 1;
        unsigned int periph_clkdis2_ts_clk : 1;
        unsigned int periph_clkdis2_ts_hclk : 1;
        unsigned int periph_clkdis2_cs_dap_off : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clkdis2_clk_x2sram : 1;
        unsigned int periph_clkdis2_x2sram_rom : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_pwm1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_atb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_atb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_tpiu_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_tpiu_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_debug_apb_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_coresight_debug_apb_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_tsensor0_clk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_tsensor0_clk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_tsensor1_clk_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_tsensor1_clk_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ipf_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ipf_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ipf_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ipf_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_socp_axi_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_socp_axi_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_seceng_core_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_seceng_core_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_seceng_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_seceng_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ap_dmac_axi0_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ap_dmac_axi0_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ap_dmac_axi1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ap_dmac_axi1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_usbotg_bus_clk_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_usbotg_bus_clk_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_usbotg_work_clk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_usbotg_work_clk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ts_clk_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ts_clk_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ts_hclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_ts_hclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_cs_dap_off_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_cs_dap_off_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_x2sram_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_clk_x2sram_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_x2sram_rom_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS2_periph_clkdis2_x2sram_rom_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat2_pwm0_pclk : 1;
        unsigned int periph_clkstat2_pwm0 : 1;
        unsigned int periph_clkstat2_pwm1_pclk : 1;
        unsigned int periph_clkstat2_pwm1 : 1;
        unsigned int periph_clkstat2_clk_coresight_atb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkstat2_clk_coresight_tpiu : 1;
        unsigned int periph_clkstat2_clk_coresight_debug_apb : 1;
        unsigned int periph_clkstat2_tsensor0_clk : 1;
        unsigned int periph_clkstat2_tsensor1_clk : 1;
        unsigned int periph_clkstat2_ipf_axi : 1;
        unsigned int periph_clkstat2_ipf_hclk : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clkstat2_socp_axi : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat2_seceng_core : 1;
        unsigned int periph_clkstat2_seceng_axi : 1;
        unsigned int periph_clkstat2_ap_dmac_axi0 : 1;
        unsigned int periph_clkstat2_ap_dmac_axi1 : 1;
        unsigned int periph_clkstat2_usbotg_bus_clk : 1;
        unsigned int periph_clkstat2_usbotg_work_clk : 1;
        unsigned int periph_clkstat2_ts_clk : 1;
        unsigned int periph_clkstat2_ts_hclk : 1;
        unsigned int periph_clkstat2_cs_dap_off : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clkstat2_clk_x2sram : 1;
        unsigned int periph_clkstat2_x2sram_rom : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm0_pclk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm0_pclk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm1_pclk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm1_pclk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_pwm1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_atb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_atb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_tpiu_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_tpiu_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_debug_apb_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_coresight_debug_apb_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_tsensor0_clk_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_tsensor0_clk_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_tsensor1_clk_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_tsensor1_clk_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ipf_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ipf_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ipf_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ipf_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_socp_axi_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_socp_axi_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_seceng_core_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_seceng_core_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_seceng_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_seceng_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ap_dmac_axi0_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ap_dmac_axi0_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ap_dmac_axi1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ap_dmac_axi1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_usbotg_bus_clk_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_usbotg_bus_clk_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_usbotg_work_clk_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_usbotg_work_clk_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ts_clk_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ts_clk_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ts_hclk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_ts_hclk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_cs_dap_off_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_cs_dap_off_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_x2sram_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_clk_x2sram_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_x2sram_rom_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT2_periph_clkstat2_x2sram_rom_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken3_tzma_axi : 1;
        unsigned int periph_clken3_ap_sram_off : 1;
        unsigned int periph_clken3_asp_cfg_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clken3_clk_asp_hdmi_bclk : 1;
        unsigned int periph_clken3_clk_asp_hdmi_ref : 1;
        unsigned int periph_clken3_clk_asp_hdmi_adws : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken3_sio0_bus : 1;
        unsigned int periph_clken3_sio0_work : 1;
        unsigned int periph_clken3_sio1_bus : 1;
        unsigned int periph_clken3_sio1_work : 1;
        unsigned int periph_clken3_sio2_bus : 1;
        unsigned int periph_clken3_sio2_work : 1;
        unsigned int periph_clken3_sio3_bus : 1;
        unsigned int periph_clken3_sio3_work : 1;
        unsigned int periph_clken3_hclk_nandc : 1;
        unsigned int periph_clken3_mmc0_bus : 1;
        unsigned int periph_clken3_mmc1_bus : 1;
        unsigned int periph_clken3_mmc2_bus : 1;
        unsigned int periph_clken3_mmc0high : 1;
        unsigned int periph_clken3_mmc1high : 1;
        unsigned int periph_clken3_mmc2high : 1;
        unsigned int periph_clken3_mmc0low : 1;
        unsigned int periph_clken3_mmc1low : 1;
        unsigned int periph_clken3_mmc2low : 1;
        unsigned int periph_clken3_clk_asp_spdif_ref : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_tzma_axi_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_tzma_axi_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_ap_sram_off_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_ap_sram_off_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_asp_cfg_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_asp_cfg_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_bclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_bclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_ref_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_ref_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_adws_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_hdmi_adws_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio0_bus_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio0_bus_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio0_work_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio0_work_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio1_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio1_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio1_work_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio1_work_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio2_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio2_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio2_work_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio2_work_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio3_bus_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio3_bus_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio3_work_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_sio3_work_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_hclk_nandc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_hclk_nandc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0_bus_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0_bus_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2_bus_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2_bus_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0high_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0high_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1high_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1high_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2high_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2high_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0low_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc0low_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1low_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc1low_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2low_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_mmc2low_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_spdif_ref_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN3_periph_clken3_clk_asp_spdif_ref_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis3_tzma_axi : 1;
        unsigned int periph_clkdis3_ap_sram_off : 1;
        unsigned int periph_clkdis3_asp_cfg_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkdis3_clk_asp_hdmi_bclk : 1;
        unsigned int periph_clkdis3_clk_asp_hdmi_ref : 1;
        unsigned int periph_clkdis3_clk_asp_hdmi_adws : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis3_sio0_bus : 1;
        unsigned int periph_clkdis3_sio0_work : 1;
        unsigned int periph_clkdis3_sio1_bus : 1;
        unsigned int periph_clkdis3_sio1_work : 1;
        unsigned int periph_clkdis3_sio2_bus : 1;
        unsigned int periph_clkdis3_sio2_work : 1;
        unsigned int periph_clkdis3_sio3_bus : 1;
        unsigned int periph_clkdis3_sio3_work : 1;
        unsigned int periph_clkdis3_hclk_nandc : 1;
        unsigned int periph_clkdis3_mmc0_bus : 1;
        unsigned int periph_clkdis3_mmc1_bus : 1;
        unsigned int periph_clkdis3_mmc2_bus : 1;
        unsigned int periph_clkdis3_mmc0high : 1;
        unsigned int periph_clkdis3_mmc1high : 1;
        unsigned int periph_clkdis3_mmc2high : 1;
        unsigned int periph_clkdis3_mmc0low : 1;
        unsigned int periph_clkdis3_mmc1low : 1;
        unsigned int periph_clkdis3_mmc2low : 1;
        unsigned int periph_clkdis3_clk_asp_spdif_ref : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_tzma_axi_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_tzma_axi_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_ap_sram_off_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_ap_sram_off_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_asp_cfg_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_asp_cfg_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_bclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_bclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_ref_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_ref_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_adws_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_hdmi_adws_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio0_bus_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio0_bus_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio0_work_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio0_work_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio1_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio1_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio1_work_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio1_work_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio2_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio2_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio2_work_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio2_work_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio3_bus_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio3_bus_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio3_work_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_sio3_work_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_hclk_nandc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_hclk_nandc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0_bus_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0_bus_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2_bus_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2_bus_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0high_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0high_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1high_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1high_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2high_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2high_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0low_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc0low_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1low_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc1low_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2low_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_mmc2low_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_spdif_ref_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS3_periph_clkdis3_clk_asp_spdif_ref_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat3_tzma_axi : 1;
        unsigned int periph_clkstat3_ap_sram_off : 1;
        unsigned int periph_clkstat3_asp_cfg_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkstat3_clk_asp_hdmi_bclk : 1;
        unsigned int periph_clkstat3_clk_asp_hdmi_ref : 1;
        unsigned int periph_clkstat3_clk_asp_hdmi_adws : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat3_sio0_bus : 1;
        unsigned int periph_clkstat3_sio0_work : 1;
        unsigned int periph_clkstat3_sio1_bus : 1;
        unsigned int periph_clkstat3_sio1_work : 1;
        unsigned int periph_clkstat3_sio2_bus : 1;
        unsigned int periph_clkstat3_sio2_work : 1;
        unsigned int periph_clkstat3_sio3_bus : 1;
        unsigned int periph_clkstat3_sio3_work : 1;
        unsigned int periph_clkstat3_hclk_nandc : 1;
        unsigned int periph_clkstat3_mmc0_bus : 1;
        unsigned int periph_clkstat3_mmc1_bus : 1;
        unsigned int periph_clkstat3_mmc2_bus : 1;
        unsigned int periph_clkstat3_mmc0high : 1;
        unsigned int periph_clkstat3_mmc1high : 1;
        unsigned int periph_clkstat3_mmc2high : 1;
        unsigned int periph_clkstat3_mmc0low : 1;
        unsigned int periph_clkstat3_mmc1low : 1;
        unsigned int periph_clkstat3_mmc2low : 1;
        unsigned int periph_clkstat3_clk_asp_spdif_ref : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_tzma_axi_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_tzma_axi_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_ap_sram_off_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_ap_sram_off_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_asp_cfg_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_asp_cfg_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_bclk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_bclk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_ref_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_ref_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_adws_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_hdmi_adws_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio0_bus_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio0_bus_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio0_work_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio0_work_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio1_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio1_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio1_work_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio1_work_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio2_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio2_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio2_work_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio2_work_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio3_bus_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio3_bus_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio3_work_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_sio3_work_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_hclk_nandc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_hclk_nandc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0_bus_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0_bus_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2_bus_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2_bus_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0high_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0high_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1high_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1high_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2high_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2high_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0low_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc0low_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1low_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc1low_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2low_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_mmc2low_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_spdif_ref_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT3_periph_clkstat3_clk_asp_spdif_ref_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken8_tcxo_pad0 : 1;
        unsigned int periph_clken8_tcxo_pad1 : 1;
        unsigned int periph_clken8_pll_test0 : 1;
        unsigned int periph_clken8_pll_test1 : 1;
        unsigned int periph_clken8_apb_slow_off : 1;
        unsigned int periph_clken8_sys_noc_bus_async : 1;
        unsigned int periph_clken8_sys_noc_hifi : 1;
        unsigned int periph_clken8_cfg_brg_s : 1;
        unsigned int periph_clken8_cfg_brg_m : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clken8_axi_periph_bus : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken8_mahb_bus : 1;
        unsigned int periph_clken8_apb_cfg_bus : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clken8_p2p_venc_brg_s : 1;
        unsigned int periph_clken8_p2p_vdec_brg_s : 1;
        unsigned int periph_clken8_p2p_vpp_brg_s : 1;
        unsigned int periph_clken8_apb_periph_bus : 1;
        unsigned int periph_clken8_x2p2_brg_m : 1;
        unsigned int periph_clken8_hpahb_bus : 1;
        unsigned int periph_clken8_27m : 1;
        unsigned int periph_clken8_90k : 1;
        unsigned int periph_clken8_48m : 1;
        unsigned int periph_clken8_noc_cssys : 1;
        unsigned int periph_clken8_noc_dapb : 1;
        unsigned int periph_clken8_jtag_auth : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_tcxo_pad0_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_tcxo_pad0_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_tcxo_pad1_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_tcxo_pad1_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_pll_test0_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_pll_test0_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_pll_test1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_pll_test1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_slow_off_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_slow_off_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_sys_noc_bus_async_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_sys_noc_bus_async_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_sys_noc_hifi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_sys_noc_hifi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_cfg_brg_s_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_cfg_brg_s_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_cfg_brg_m_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_cfg_brg_m_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_axi_periph_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_axi_periph_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_mahb_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_mahb_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_cfg_bus_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_cfg_bus_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_venc_brg_s_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_venc_brg_s_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vdec_brg_s_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vdec_brg_s_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vpp_brg_s_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_p2p_vpp_brg_s_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_periph_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_apb_periph_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_x2p2_brg_m_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_x2p2_brg_m_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_hpahb_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_hpahb_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_27m_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_27m_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_90k_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_90k_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_48m_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_48m_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_noc_cssys_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_noc_cssys_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_noc_dapb_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_noc_dapb_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_jtag_auth_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN8_periph_clken8_jtag_auth_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis8_tcxo_pad0 : 1;
        unsigned int periph_clkdis8_tcxo_pad1 : 1;
        unsigned int periph_clkdis8_pll_test0 : 1;
        unsigned int periph_clkdis8_pll_test1 : 1;
        unsigned int periph_clkdis8_apb_slow_off : 1;
        unsigned int periph_clkdis8_sys_noc_bus_async : 1;
        unsigned int periph_clkdis8_sys_noc_hifi : 1;
        unsigned int periph_clkdis8_cfg_brg_s : 1;
        unsigned int periph_clkdis8_cfg_brg_m : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clkdis8_axi_periph_bus : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis8_mahb_bus : 1;
        unsigned int periph_clkdis8_apb_cfg_bus : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkdis8_p2p_venc_brg_s : 1;
        unsigned int periph_clkdis8_p2p_vdec_brg_s : 1;
        unsigned int periph_clkdis8_p2p_vpp_brg_s : 1;
        unsigned int periph_clkdis8_apb_periph_bus : 1;
        unsigned int periph_clkdis8_x2p2_brg_m : 1;
        unsigned int periph_clkdis8_hpahb_bus : 1;
        unsigned int periph_clkdis8_27m : 1;
        unsigned int periph_clkdis8_90k : 1;
        unsigned int periph_clkdis8_48m : 1;
        unsigned int periph_clkdis8_noc_cssys : 1;
        unsigned int periph_clkdis8_noc_dapb : 1;
        unsigned int periph_clkdis8_jtag_auth : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_tcxo_pad0_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_tcxo_pad0_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_tcxo_pad1_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_tcxo_pad1_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_pll_test0_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_pll_test0_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_pll_test1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_pll_test1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_slow_off_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_slow_off_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_sys_noc_bus_async_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_sys_noc_bus_async_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_sys_noc_hifi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_sys_noc_hifi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_cfg_brg_s_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_cfg_brg_s_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_cfg_brg_m_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_cfg_brg_m_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_axi_periph_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_axi_periph_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_mahb_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_mahb_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_cfg_bus_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_cfg_bus_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_venc_brg_s_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_venc_brg_s_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_vdec_brg_s_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_vdec_brg_s_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_vpp_brg_s_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_p2p_vpp_brg_s_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_periph_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_apb_periph_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_x2p2_brg_m_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_x2p2_brg_m_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_hpahb_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_hpahb_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_27m_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_27m_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_90k_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_90k_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_48m_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_48m_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_noc_cssys_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_noc_cssys_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_noc_dapb_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_noc_dapb_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_jtag_auth_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS8_periph_clkdis8_jtag_auth_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat8_tcxo_pad0 : 1;
        unsigned int periph_clkstat8_tcxo_pad1 : 1;
        unsigned int periph_clkstat8_pll_test0 : 1;
        unsigned int periph_clkstat8_pll_test1 : 1;
        unsigned int periph_clkstat8_apb_slow_off : 1;
        unsigned int periph_clkstat8_sys_noc_bus_async : 1;
        unsigned int periph_clkstat8_sys_noc_hifi : 1;
        unsigned int periph_clkstat8_cfg_brg_s : 1;
        unsigned int periph_clkstat8_cfg_brg_m : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_clkstat8_axi_periph_bus : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat8_mahb_bus : 1;
        unsigned int periph_clkstat8_apb_cfg_bus : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkstat8_p2p_venc_brg_s : 1;
        unsigned int periph_clkstat8_p2p_vdec_brg_s : 1;
        unsigned int periph_clkstat8_p2p_vpp_brg_s : 1;
        unsigned int periph_clkstat8_apb_periph_bus : 1;
        unsigned int periph_clkstat8_x2p2_brg_m : 1;
        unsigned int periph_clkstat8_hpahb_bus : 1;
        unsigned int periph_clkstat8_27m : 1;
        unsigned int periph_clkstat8_90k : 1;
        unsigned int periph_clkstat8_48m : 1;
        unsigned int periph_clkstat8_noc_cssys : 1;
        unsigned int periph_clkstat8_noc_dapb : 1;
        unsigned int periph_clkstat8_jtag_auth : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_tcxo_pad0_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_tcxo_pad0_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_tcxo_pad1_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_tcxo_pad1_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_pll_test0_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_pll_test0_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_pll_test1_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_pll_test1_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_slow_off_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_slow_off_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_sys_noc_bus_async_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_sys_noc_bus_async_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_sys_noc_hifi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_sys_noc_hifi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_cfg_brg_s_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_cfg_brg_s_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_cfg_brg_m_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_cfg_brg_m_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_axi_periph_bus_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_axi_periph_bus_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_mahb_bus_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_mahb_bus_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_cfg_bus_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_cfg_bus_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_venc_brg_s_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_venc_brg_s_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_vdec_brg_s_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_vdec_brg_s_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_vpp_brg_s_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_p2p_vpp_brg_s_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_periph_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_apb_periph_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_x2p2_brg_m_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_x2p2_brg_m_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_hpahb_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_hpahb_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_27m_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_27m_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_90k_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_90k_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_48m_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_48m_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_noc_cssys_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_noc_cssys_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_noc_dapb_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_noc_dapb_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_jtag_auth_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT8_periph_clkstat8_jtag_auth_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken9_bbe16_kernel_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clken9_clk_bbe16_dap : 1;
        unsigned int periph_clken9_clk_bbe16_atb : 1;
        unsigned int periph_clken9_modem_dmac_axi0 : 1;
        unsigned int periph_clken9_modem_dmac_axi1 : 1;
        unsigned int periph_clken9_cicom_upacc : 1;
        unsigned int periph_clken9_cicom_axi : 1;
        unsigned int periph_clken9_cicom_hclk : 1;
        unsigned int periph_clken9_cicom_l_cipher : 1;
        unsigned int periph_clken9_cicom_gu0 : 1;
        unsigned int periph_clken9_cicom_gu1 : 1;
        unsigned int periph_clken9_modem_uart0_pclk : 1;
        unsigned int periph_clken9_modem_uart0 : 1;
        unsigned int periph_clken9_modem_uart1_pclk : 1;
        unsigned int periph_clken9_modem_uart1 : 1;
        unsigned int periph_clken9_modem_noc_bus : 1;
        unsigned int periph_clken9_modem_noc_bus_async : 1;
        unsigned int periph_clken9_modem_axi_bus : 1;
        unsigned int periph_clken9_modem_sram : 1;
        unsigned int periph_clken9_modem_x2ram : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 2;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_bbe16_kernel_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_bbe16_kernel_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_clk_bbe16_dap_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_clk_bbe16_dap_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_clk_bbe16_atb_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_clk_bbe16_atb_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_dmac_axi0_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_dmac_axi0_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_dmac_axi1_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_dmac_axi1_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_upacc_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_upacc_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_l_cipher_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_l_cipher_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_gu0_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_gu0_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_gu1_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_cicom_gu1_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart0_pclk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart0_pclk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart0_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart0_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart1_pclk_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart1_pclk_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_uart1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_noc_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_noc_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_noc_bus_async_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_noc_bus_async_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_axi_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_axi_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_sram_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_sram_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_x2ram_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN9_periph_clken9_modem_x2ram_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken9_bbe16_kernel_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkdis9_clk_bbe16_dap : 1;
        unsigned int periph_clkdis9_clk_bbe16_atb : 1;
        unsigned int periph_clkdis9_modem_dmac_axi0 : 1;
        unsigned int periph_clkdis9_modem_dmac_axi1 : 1;
        unsigned int periph_clkdis9_cicom_upacc : 1;
        unsigned int periph_clkdis9_cicom_axi : 1;
        unsigned int periph_clkdis9_cicom_hclk : 1;
        unsigned int periph_clkdis9_cicom_l_cipher : 1;
        unsigned int periph_clkdis9_cicom_gu0 : 1;
        unsigned int periph_clkdis9_cicom_gu1 : 1;
        unsigned int periph_clkdis9_modem_uart0_pclk : 1;
        unsigned int periph_clkdis9_modem_uart0 : 1;
        unsigned int periph_clkdis9_modem_uart1_pclk : 1;
        unsigned int periph_clkdis9_modem_uart1 : 1;
        unsigned int periph_clkdis9_modem_noc_bus : 1;
        unsigned int periph_clkdis9_modem_noc_bus_async : 1;
        unsigned int periph_clkdis9_modem_axi_bus : 1;
        unsigned int periph_clkdis9_modem_sram : 1;
        unsigned int periph_clkdis9_modem_x2ram : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 2;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clken9_bbe16_kernel_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clken9_bbe16_kernel_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_clk_bbe16_dap_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_clk_bbe16_dap_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_clk_bbe16_atb_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_clk_bbe16_atb_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_dmac_axi0_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_dmac_axi0_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_dmac_axi1_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_dmac_axi1_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_upacc_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_upacc_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_l_cipher_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_l_cipher_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_gu0_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_gu0_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_gu1_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_cicom_gu1_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart0_pclk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart0_pclk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart0_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart0_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart1_pclk_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart1_pclk_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_uart1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_noc_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_noc_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_noc_bus_async_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_noc_bus_async_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_axi_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_axi_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_sram_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_sram_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_x2ram_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS9_periph_clkdis9_modem_x2ram_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat9_bbe16_kernel_clk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkstat9_clk_bbe16_dap : 1;
        unsigned int periph_clkstat9_clk_bbe16_atb : 1;
        unsigned int periph_clkstat9_modem_dmac_axi0 : 1;
        unsigned int periph_clkstat9_modem_dmac_axi1 : 1;
        unsigned int periph_clkstat9_cicom_upacc : 1;
        unsigned int periph_clkstat9_cicom_axi : 1;
        unsigned int periph_clkstat9_cicom_hclk : 1;
        unsigned int periph_clkstat9_cicom_l_cipher : 1;
        unsigned int periph_clkstat9_cicom_gu0 : 1;
        unsigned int periph_clkstat9_cicom_gu1 : 1;
        unsigned int periph_clkstat9_modem_uart0_pclk : 1;
        unsigned int periph_clkstat9_modem_uart0 : 1;
        unsigned int periph_clkstat9_modem_uart1_pclk : 1;
        unsigned int periph_clkstat9_modem_uart1 : 1;
        unsigned int periph_clkstat9_modem_noc_bus : 1;
        unsigned int periph_clkstat9_modem_noc_bus_async : 1;
        unsigned int periph_clkstat9_modem_axi_bus : 1;
        unsigned int periph_clkstat9_modem_sram : 1;
        unsigned int periph_clkstat9_modem_x2ram : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 2;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_bbe16_kernel_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_bbe16_kernel_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_clk_bbe16_dap_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_clk_bbe16_dap_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_clk_bbe16_atb_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_clk_bbe16_atb_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_dmac_axi0_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_dmac_axi0_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_dmac_axi1_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_dmac_axi1_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_upacc_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_upacc_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_axi_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_axi_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_hclk_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_hclk_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_l_cipher_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_l_cipher_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_gu0_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_gu0_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_gu1_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_cicom_gu1_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart0_pclk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart0_pclk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart0_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart0_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart1_pclk_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart1_pclk_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart1_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_uart1_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_noc_bus_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_noc_bus_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_noc_bus_async_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_noc_bus_async_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_axi_bus_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_axi_bus_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_sram_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_sram_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_x2ram_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT9_periph_clkstat9_modem_x2ram_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken10_x2x_mali_brg_m : 1;
        unsigned int periph_clken10_x2x_sys_brg_m : 1;
        unsigned int periph_clken10_x2x_modem_brg_m : 1;
        unsigned int periph_clken10_x2x_mcpu_brg_m : 1;
        unsigned int periph_clken10_x2x_l2_m0_brg_s : 1;
        unsigned int periph_clken10_x2x_l2_m1_brg_s : 1;
        unsigned int periph_clken10_axi_mali_bus : 1;
        unsigned int periph_clken10_axi_img_bus : 1;
        unsigned int periph_clken10_axi_video_bus : 1;
        unsigned int periph_clken10_x2x_mali_brg_s : 1;
        unsigned int periph_clken10_x2x_sys_brg_s : 1;
        unsigned int periph_clken10_x2x_modem_brg_s : 1;
        unsigned int periph_clken10_x2x_mcpu_brg_s : 1;
        unsigned int periph_clken10_x2x_venc_brg_s : 1;
        unsigned int periph_clken10_x2x_vdec_brg_s : 1;
        unsigned int periph_clken10_x2x_vpp_brg_s : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN10_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_m_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_m_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_sys_brg_m_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_sys_brg_m_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_modem_brg_m_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_modem_brg_m_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mcpu_brg_m_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mcpu_brg_m_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_l2_m0_brg_s_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_l2_m0_brg_s_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_l2_m1_brg_s_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_l2_m1_brg_s_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_mali_bus_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_mali_bus_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_img_bus_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_img_bus_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_video_bus_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_axi_video_bus_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_s_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mali_brg_s_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_sys_brg_s_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_sys_brg_s_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_modem_brg_s_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_modem_brg_s_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mcpu_brg_s_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_mcpu_brg_s_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_venc_brg_s_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_venc_brg_s_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vdec_brg_s_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vdec_brg_s_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vpp_brg_s_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN10_periph_clken10_x2x_vpp_brg_s_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis10_x2x_mali_brg_m : 1;
        unsigned int periph_clkdis10_x2x_sys_brg_m : 1;
        unsigned int periph_clkdis10_x2x_modem_brg_m : 1;
        unsigned int periph_clkdis10_x2x_mcpu_brg_m : 1;
        unsigned int periph_clkdis10_x2x_l2_m0_brg_s : 1;
        unsigned int periph_clkdis10_x2x_l2_m1_brg_s : 1;
        unsigned int periph_clkdis10_axi_mali_bus : 1;
        unsigned int periph_clkdis10_axi_img_bus : 1;
        unsigned int periph_clkdis10_axi_video_bus : 1;
        unsigned int periph_clkdis10_x2x_mali_brg_s : 1;
        unsigned int periph_clkdis10_x2x_sys_brg_s : 1;
        unsigned int periph_clkdis10_x2x_modem_brg_s : 1;
        unsigned int periph_clkdis10_x2x_mcpu_brg_s : 1;
        unsigned int periph_clkdis10_x2x_venc_brg_s : 1;
        unsigned int periph_clkdis10_x2x_vdec_brg_s : 1;
        unsigned int periph_clkdis10_x2x_vpp_brg_s : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS10_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mali_brg_m_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mali_brg_m_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_sys_brg_m_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_sys_brg_m_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_modem_brg_m_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_modem_brg_m_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mcpu_brg_m_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mcpu_brg_m_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_l2_m0_brg_s_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_l2_m0_brg_s_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_l2_m1_brg_s_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_l2_m1_brg_s_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_mali_bus_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_mali_bus_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_img_bus_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_img_bus_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_video_bus_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_axi_video_bus_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mali_brg_s_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mali_brg_s_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_sys_brg_s_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_sys_brg_s_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_modem_brg_s_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_modem_brg_s_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mcpu_brg_s_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_mcpu_brg_s_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_venc_brg_s_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_venc_brg_s_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_vdec_brg_s_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_vdec_brg_s_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_vpp_brg_s_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS10_periph_clkdis10_x2x_vpp_brg_s_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat10_x2x_mali_brg_m : 1;
        unsigned int periph_clkstat10_x2x_sys_brg_m : 1;
        unsigned int periph_clkstat10_x2x_modem_brg_m : 1;
        unsigned int periph_clkstat10_x2x_mcpu_brg_m : 1;
        unsigned int periph_clkstat10_x2x_l2_m0_brg_s : 1;
        unsigned int periph_clkstat10_x2x_l2_m1_brg_s : 1;
        unsigned int periph_clkstat10_axi_mali_bus : 1;
        unsigned int periph_clkstat10_axi_img_bus : 1;
        unsigned int periph_clkstat10_axi_video_bus : 1;
        unsigned int periph_clkstat10_x2x_mali_brg_s : 1;
        unsigned int periph_clkstat10_x2x_sys_brg_s : 1;
        unsigned int periph_clkstat10_x2x_modem_brg_s : 1;
        unsigned int periph_clkstat10_x2x_mcpu_brg_s : 1;
        unsigned int periph_clkstat10_x2x_venc_brg_s : 1;
        unsigned int periph_clkstat10_x2x_vdec_brg_s : 1;
        unsigned int periph_clkstat10_x2x_vpp_brg_s : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT10_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mali_brg_m_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mali_brg_m_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_sys_brg_m_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_sys_brg_m_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_modem_brg_m_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_modem_brg_m_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mcpu_brg_m_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mcpu_brg_m_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_l2_m0_brg_s_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_l2_m0_brg_s_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_l2_m1_brg_s_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_l2_m1_brg_s_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_mali_bus_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_mali_bus_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_img_bus_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_img_bus_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_video_bus_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_axi_video_bus_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mali_brg_s_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mali_brg_s_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_sys_brg_s_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_sys_brg_s_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_modem_brg_s_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_modem_brg_s_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mcpu_brg_s_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_mcpu_brg_s_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_venc_brg_s_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_venc_brg_s_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_vdec_brg_s_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_vdec_brg_s_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_vpp_brg_s_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT10_periph_clkstat10_x2x_vpp_brg_s_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken11_edc0_cfg_clk : 1;
        unsigned int periph_clken11_aclk_edc0 : 1;
        unsigned int periph_clken11_edc0_pix_ldi : 1;
        unsigned int periph_clken11_edc0_core : 1;
        unsigned int periph_clken11_dsio_cfg_clk : 1;
        unsigned int periph_clken11_edc1_cfg_clk : 1;
        unsigned int periph_clken11_edc1_axi : 1;
        unsigned int periph_clken11_edc1_pix_ldi : 1;
        unsigned int periph_clken11_edc1_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clken11_hdmi_slave : 1;
        unsigned int periph_clken11_clk_hdmi_sck : 1;
        unsigned int periph_clken11_mclk_hdmi : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken11_isp_cfg_clk : 1;
        unsigned int periph_clken11_isp_axi : 1;
        unsigned int periph_clken11_clk_isp : 1;
        unsigned int periph_clken11_clk_isp_ref : 1;
        unsigned int periph_clken11_csi_apb_mux : 1;
        unsigned int periph_clken11_clk_csio_cfg : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clken11_csi2_cfg_clk : 1;
        unsigned int periph_clken11_dphy0_clk : 1;
        unsigned int periph_clken11_dphy1_cfg : 1;
        unsigned int periph_clken11_dphy2_cfg_clk : 1;
        unsigned int periph_clken11_dphy0 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN11_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_cfg_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_cfg_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_aclk_edc0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_aclk_edc0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_pix_ldi_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_pix_ldi_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_core_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc0_core_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dsio_cfg_clk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dsio_cfg_clk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_cfg_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_cfg_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_axi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_axi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_pix_ldi_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_pix_ldi_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_core_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_edc1_core_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_hdmi_slave_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_hdmi_slave_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_hdmi_sck_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_hdmi_sck_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_mclk_hdmi_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_mclk_hdmi_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_cfg_clk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_cfg_clk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_isp_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_ref_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_isp_ref_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi_apb_mux_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi_apb_mux_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_csio_cfg_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_clk_csio_cfg_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi2_cfg_clk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_csi2_cfg_clk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_clk_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_clk_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy1_cfg_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy1_cfg_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy2_cfg_clk_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy2_cfg_clk_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN11_periph_clken11_dphy0_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis11_edc0_cfg_clk : 1;
        unsigned int periph_clkdis11_aclk_edc0 : 1;
        unsigned int periph_clkdis11_edc0_pix_ldi : 1;
        unsigned int periph_clkdis11_edc0_core : 1;
        unsigned int periph_clkdis11_dsio_cfg_clk : 1;
        unsigned int periph_clkdis11_edc1_cfg_clk : 1;
        unsigned int periph_clkdis11_edc1_axi : 1;
        unsigned int periph_clkdis11_edc1_pix_ldi : 1;
        unsigned int periph_clkdis11_edc1_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkdis11_hdmi_slave : 1;
        unsigned int periph_clkdis11_clk_hdmi_sck : 1;
        unsigned int periph_clkdis11_mclk_hdmi : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis11_isp_cfg_clk : 1;
        unsigned int periph_clkdis11_isp_axi : 1;
        unsigned int periph_clkdis11_clk_isp : 1;
        unsigned int periph_clkdis11_clk_isp_ref : 1;
        unsigned int periph_clkdis11_csi_apb_mux : 1;
        unsigned int periph_clkdis11_clk_csio_cfg : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkdis11_csi2_cfg_clk : 1;
        unsigned int periph_clkdis11_dphy0_clk : 1;
        unsigned int periph_clkdis11_dphy1_cfg : 1;
        unsigned int periph_clkdis11_dphy2_cfg_clk : 1;
        unsigned int periph_clkdis11_dphy0 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS11_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_cfg_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_cfg_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_aclk_edc0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_aclk_edc0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_pix_ldi_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_pix_ldi_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_core_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc0_core_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dsio_cfg_clk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dsio_cfg_clk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_cfg_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_cfg_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_axi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_axi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_pix_ldi_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_pix_ldi_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_core_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_edc1_core_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_hdmi_slave_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_hdmi_slave_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_hdmi_sck_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_hdmi_sck_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_mclk_hdmi_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_mclk_hdmi_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_isp_cfg_clk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_isp_cfg_clk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_isp_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_isp_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_isp_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_isp_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_isp_ref_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_isp_ref_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_csi_apb_mux_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_csi_apb_mux_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_csio_cfg_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_clk_csio_cfg_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_csi2_cfg_clk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_csi2_cfg_clk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy0_clk_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy0_clk_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy1_cfg_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy1_cfg_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy2_cfg_clk_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy2_cfg_clk_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy0_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS11_periph_clkdis11_dphy0_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat11_edc0_cfg_clk : 1;
        unsigned int periph_clkstat11_aclk_edc0 : 1;
        unsigned int periph_clkstat11_edc0_pix_ldi : 1;
        unsigned int periph_clkstat11_edc0_core : 1;
        unsigned int periph_clkstat11_dsio_cfg_clk : 1;
        unsigned int periph_clkstat11_edc1_cfg_clk : 1;
        unsigned int periph_clkstat11_edc1_axi : 1;
        unsigned int periph_clkstat11_edc1_pix_ldi : 1;
        unsigned int periph_clkstat11_edc1_core : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_clkstat11_hdmi_slave : 1;
        unsigned int periph_clkstat11_clk_hdmi_sck : 1;
        unsigned int periph_clkstat11_mclk_hdmi : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat11_isp_cfg_clk : 1;
        unsigned int periph_clkstat11_isp_axi : 1;
        unsigned int periph_clkstat11_clk_isp : 1;
        unsigned int periph_clkstat11_clk_isp_ref : 1;
        unsigned int periph_clkstat11_csi_apb_mux : 1;
        unsigned int periph_clkstat11_clk_csio_cfg : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_clkstat11_csi2_cfg_clk : 1;
        unsigned int periph_clkstat11_dphy0_clk : 1;
        unsigned int periph_clkstat11_dphy1_cfg : 1;
        unsigned int periph_clkstat11_dphy2_cfg_clk : 1;
        unsigned int periph_clkstat11_dphy0 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT11_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_cfg_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_cfg_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_aclk_edc0_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_aclk_edc0_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_pix_ldi_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_pix_ldi_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_core_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc0_core_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dsio_cfg_clk_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dsio_cfg_clk_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_cfg_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_cfg_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_axi_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_axi_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_pix_ldi_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_pix_ldi_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_core_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_edc1_core_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_hdmi_slave_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_hdmi_slave_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_hdmi_sck_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_hdmi_sck_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_mclk_hdmi_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_mclk_hdmi_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_isp_cfg_clk_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_isp_cfg_clk_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_isp_axi_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_isp_axi_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_isp_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_isp_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_isp_ref_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_isp_ref_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_csi_apb_mux_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_csi_apb_mux_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_csio_cfg_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_clk_csio_cfg_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_csi2_cfg_clk_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_csi2_cfg_clk_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy0_clk_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy0_clk_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy1_cfg_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy1_cfg_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy2_cfg_clk_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy2_cfg_clk_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy0_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT11_periph_clkstat11_dphy0_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken12_0venc_clk : 1;
        unsigned int periph_clken12_1vdec_clk : 1;
        unsigned int periph_clken12_2vpp_slave_clk : 1;
        unsigned int periph_clken12_3g2d_cfg_clk : 1;
        unsigned int periph_clken12_4g2d_axi_clkhb : 1;
        unsigned int periph_clken12_5g2d_core_clk : 1;
        unsigned int periph_clken12_6clk_mali : 1;
        unsigned int periph_clken12_7pclk_p2p_mali : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clken12_27m : 1;
        unsigned int periph_clken12_cssys_gated : 1;
        unsigned int periph_clken12_mali_gated : 1;
        unsigned int periph_clken12_dsppll_g2dcore_gated : 1;
        unsigned int periph_clken12_mux_isp_gated : 1;
        unsigned int periph_clken12_peripll_isp_ref_gated : 1;
        unsigned int periph_clken12_mux_edc0_pix_gated : 1;
        unsigned int periph_clken12_dsppll_edc0_core_gated : 1;
        unsigned int periph_clken12_dsppll_vdec_gated : 1;
        unsigned int periph_clken12_peripll_venc_gated : 1;
        unsigned int periph_clken12_peripll_vpp_gated : 1;
        unsigned int periph_clken12_dsppll_hifi_core_gated : 1;
        unsigned int periph_clken12_dsppll_mmc0_gated : 1;
        unsigned int periph_clken12_dsppll_mmc1_gated : 1;
        unsigned int periph_clken12_dsppll_mmc2_gated : 1;
        unsigned int periph_clken12_dsppll_48m_gated : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN12_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_0venc_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_0venc_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_1vdec_clk_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_1vdec_clk_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_2vpp_slave_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_2vpp_slave_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_3g2d_cfg_clk_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_3g2d_cfg_clk_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_4g2d_axi_clkhb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_4g2d_axi_clkhb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_5g2d_core_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_5g2d_core_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_6clk_mali_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_6clk_mali_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_7pclk_p2p_mali_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_7pclk_p2p_mali_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_27m_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_27m_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_cssys_gated_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_cssys_gated_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mali_gated_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mali_gated_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_g2dcore_gated_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_g2dcore_gated_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_isp_gated_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_isp_gated_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_isp_ref_gated_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_isp_ref_gated_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_edc0_pix_gated_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_mux_edc0_pix_gated_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_edc0_core_gated_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_edc0_core_gated_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_vdec_gated_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_vdec_gated_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_venc_gated_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_venc_gated_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_vpp_gated_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_peripll_vpp_gated_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_hifi_core_gated_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_hifi_core_gated_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc0_gated_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc0_gated_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc1_gated_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc1_gated_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc2_gated_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_mmc2_gated_END (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_48m_gated_START (31)
#define SOC_SCTRL_SC_PERIPH_CLKEN12_periph_clken12_dsppll_48m_gated_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis12_0venc_clk : 1;
        unsigned int periph_clkdis12_1vdec_clk : 1;
        unsigned int periph_clkdis12_2vpp_slave_clk : 1;
        unsigned int periph_clkdis12_3g2d_cfg_clk : 1;
        unsigned int periph_clkdis12_4g2d_axi_clkhb : 1;
        unsigned int periph_clkdis12_5g2d_core_clk : 1;
        unsigned int periph_clkdis12_6clk_mali : 1;
        unsigned int periph_clkdis12_7pclk_p2p_mali : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clkdis12_27m : 1;
        unsigned int periph_clkdis12_cssys_gated : 1;
        unsigned int periph_clkdis12_mali_gated : 1;
        unsigned int periph_clkdis12_dsppll_g2dcore_gated : 1;
        unsigned int periph_clkdis12_mux_isp_gated : 1;
        unsigned int periph_clkdis12_peripll_isp_ref_gated : 1;
        unsigned int periph_clkdis12_mux_edc0_pix_gated : 1;
        unsigned int periph_clkdis12_dsppll_edc0_core_gated : 1;
        unsigned int periph_clkdis12_dsppll_vdec_gated : 1;
        unsigned int periph_clkdis12_peripll_venc_gated : 1;
        unsigned int periph_clkdis12_peripll_vpp_gated : 1;
        unsigned int periph_clkdis12_dsppll_hifi_core_gated : 1;
        unsigned int periph_clkdis12_dsppll_mmc0_gated : 1;
        unsigned int periph_clkdis12_dsppll_mmc1_gated : 1;
        unsigned int periph_clkdis12_dsppll_mmc2_gated : 1;
        unsigned int periph_clken12_dsppll_48m_gated : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS12_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_0venc_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_0venc_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_1vdec_clk_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_1vdec_clk_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_2vpp_slave_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_2vpp_slave_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_3g2d_cfg_clk_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_3g2d_cfg_clk_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_4g2d_axi_clkhb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_4g2d_axi_clkhb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_5g2d_core_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_5g2d_core_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_6clk_mali_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_6clk_mali_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_7pclk_p2p_mali_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_7pclk_p2p_mali_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_27m_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_27m_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_cssys_gated_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_cssys_gated_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mali_gated_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mali_gated_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_g2dcore_gated_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_g2dcore_gated_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mux_isp_gated_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mux_isp_gated_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_isp_ref_gated_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_isp_ref_gated_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mux_edc0_pix_gated_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_mux_edc0_pix_gated_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_edc0_core_gated_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_edc0_core_gated_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_vdec_gated_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_vdec_gated_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_venc_gated_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_venc_gated_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_vpp_gated_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_peripll_vpp_gated_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_hifi_core_gated_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_hifi_core_gated_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc0_gated_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc0_gated_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc1_gated_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc1_gated_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc2_gated_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clkdis12_dsppll_mmc2_gated_END (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clken12_dsppll_48m_gated_START (31)
#define SOC_SCTRL_SC_PERIPH_CLKDIS12_periph_clken12_dsppll_48m_gated_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat12_0venc_clk : 1;
        unsigned int periph_clkstat12_1vdec_clk : 1;
        unsigned int periph_clkstat12_2vpp_slave_clk : 1;
        unsigned int periph_clkstat12_3g2d_cfg_clk : 1;
        unsigned int periph_clkstat12_4g2d_axi_clkhb : 1;
        unsigned int periph_clkstat12_5g2d_core_clk : 1;
        unsigned int periph_clkstat12_6clk_mali : 1;
        unsigned int periph_clkstat12_7pclk_p2p_mali : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int periph_clkstat12_27m : 1;
        unsigned int periph_clkstat12_cssys_gated : 1;
        unsigned int periph_clkstat12_mali_gated : 1;
        unsigned int periph_clkstat12_dsppll_g2dcore_gated : 1;
        unsigned int periph_clkstat12_mux_isp_gated : 1;
        unsigned int periph_clkstat12_peripll_isp_ref_gated : 1;
        unsigned int periph_clkstat12_mux_edc0_pix_gated : 1;
        unsigned int periph_clkstat12_dsppll_edc0_core_gated : 1;
        unsigned int periph_clkstat12_dsppll_vdec_gated : 1;
        unsigned int periph_clkstat12_peripll_venc_gated : 1;
        unsigned int periph_clkstat12_peripll_vpp_gated : 1;
        unsigned int periph_clkstat12_dsppll_hifi_core_gated : 1;
        unsigned int periph_clkstat12_dsppll_mmc0_gated : 1;
        unsigned int periph_clkstat12_dsppll_mmc1_gated : 1;
        unsigned int periph_clkstat12_dsppll_mmc2_gated : 1;
        unsigned int periph_clken12_dsppll_48m_gated : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT12_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_0venc_clk_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_0venc_clk_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_1vdec_clk_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_1vdec_clk_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_2vpp_slave_clk_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_2vpp_slave_clk_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_3g2d_cfg_clk_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_3g2d_cfg_clk_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_4g2d_axi_clkhb_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_4g2d_axi_clkhb_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_5g2d_core_clk_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_5g2d_core_clk_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_6clk_mali_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_6clk_mali_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_7pclk_p2p_mali_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_7pclk_p2p_mali_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_27m_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_27m_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_cssys_gated_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_cssys_gated_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mali_gated_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mali_gated_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_g2dcore_gated_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_g2dcore_gated_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mux_isp_gated_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mux_isp_gated_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_isp_ref_gated_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_isp_ref_gated_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mux_edc0_pix_gated_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_mux_edc0_pix_gated_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_edc0_core_gated_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_edc0_core_gated_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_vdec_gated_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_vdec_gated_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_venc_gated_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_venc_gated_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_vpp_gated_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_peripll_vpp_gated_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_hifi_core_gated_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_hifi_core_gated_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc0_gated_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc0_gated_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc1_gated_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc1_gated_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc2_gated_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clkstat12_dsppll_mmc2_gated_END (30)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clken12_dsppll_48m_gated_START (31)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT12_periph_clken12_dsppll_48m_gated_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken13_122m_tds : 1;
        unsigned int periph_clken13_245m_tds : 1;
        unsigned int periph_clken13_19m_tw : 1;
        unsigned int periph_clken13_122m_tw : 1;
        unsigned int periph_clken13_61m_wbbp_gupd1 : 1;
        unsigned int periph_clken13_122m_wbbp : 1;
        unsigned int periph_clken13_axim_wbbp : 1;
        unsigned int periph_clken13_61m_wbbp_gupd2 : 1;
        unsigned int periph_clken13_122m_wbbp_gupd2 : 1;
        unsigned int periph_clken13_245m_wbbp : 1;
        unsigned int periph_clken13_104m_gbbp1 : 1;
        unsigned int periph_clken13_19m_gbbp1 : 1;
        unsigned int periph_clken13_104m_gbbp2 : 1;
        unsigned int periph_clken13_19m_gbbp2 : 1;
        unsigned int periph_clken13_19m_bbc_soc : 1;
        unsigned int periph_clken13_19m_bbc_rf0 : 1;
        unsigned int periph_clken13_19m_bbc_rf1 : 1;
        unsigned int periph_clken13_axis_bbc : 1;
        unsigned int periph_clken13_axim_bbc : 1;
        unsigned int reserved : 1;
        unsigned int periph_clken13_245m_irm : 1;
        unsigned int periph_clken13_491m_irm : 1;
        unsigned int periph_clken13_122m_wbbp_irm : 1;
        unsigned int periph_clken13_104m_gbbp1_irm : 1;
        unsigned int periph_clken13_104m_gbbp2_irm : 1;
        unsigned int periph_clken13_axi_lte : 1;
        unsigned int periph_clken13_122m_lte_pdt : 1;
        unsigned int periph_clken13_122m_lte_pdf : 1;
        unsigned int periph_clken13_122m_tds_pdt : 1;
        unsigned int periph_clken13_245m_lte : 1;
        unsigned int periph_clken13_19m_lte : 1;
        unsigned int periph_clken13_reserve : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN13_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_61m_wbbp_gupd1_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_61m_wbbp_gupd1_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axim_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axim_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_61m_wbbp_gupd2_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_61m_wbbp_gupd2_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_gupd2_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_gupd2_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp1_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp1_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_gbbp1_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_gbbp1_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp2_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp2_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_gbbp2_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_gbbp2_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_rf0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_rf0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_rf1_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_bbc_rf1_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axis_bbc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axis_bbc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axim_bbc_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axim_bbc_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_irm_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_irm_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_491m_irm_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_491m_irm_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_irm_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_wbbp_irm_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp1_irm_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp1_irm_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp2_irm_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_104m_gbbp2_irm_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axi_lte_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_axi_lte_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_lte_pdt_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_lte_pdt_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_lte_pdf_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_lte_pdf_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tds_pdt_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_122m_tds_pdt_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_lte_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_245m_lte_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_lte_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_19m_lte_END (30)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_reserve_START (31)
#define SOC_SCTRL_SC_PERIPH_CLKEN13_periph_clken13_reserve_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis13_122m_tds : 1;
        unsigned int periph_clkdis13_245m_tds : 1;
        unsigned int periph_clkdis13_19m_tw : 1;
        unsigned int periph_clkdis13_122m_tw : 1;
        unsigned int periph_clkdis13_61m_wbbp_gupd1 : 1;
        unsigned int periph_clkdis13_122m_wbbp : 1;
        unsigned int periph_clkdis13_axim_wbbp : 1;
        unsigned int periph_clkdis13_61m_wbbp_gupd2 : 1;
        unsigned int periph_clkdis13_122m_wbbp_gupd2 : 1;
        unsigned int periph_clkdis13_245m_wbbp : 1;
        unsigned int periph_clkdis13_104m_gbbp1 : 1;
        unsigned int periph_clkdis13_19m_gbbp1 : 1;
        unsigned int periph_clkdis13_104m_gbbp2 : 1;
        unsigned int periph_clkdis13_19m_gbbp2 : 1;
        unsigned int periph_clkdis13_19m_bbc_soc : 1;
        unsigned int periph_clkdis13_19m_bbc_rf0 : 1;
        unsigned int periph_clkdis13_19m_bbc_rf1 : 1;
        unsigned int periph_clkdis13_axis_bbc : 1;
        unsigned int periph_clkdis13_axim_bbc : 1;
        unsigned int periph_clkdis13_reserve : 1;
        unsigned int periph_clkdis13_245m_irm : 1;
        unsigned int periph_clkdis13_491m_irm : 1;
        unsigned int periph_clkdis13_122m_wbbp_irm : 1;
        unsigned int periph_clkdis13_104m_gbbp1_irm : 1;
        unsigned int periph_clkdis13_104m_gbbp2_irm : 1;
        unsigned int periph_clkdis13_axi_lte : 1;
        unsigned int periph_clkdis13_122m_lte_pdt : 1;
        unsigned int periph_clkdis13_122m_lte_pdf : 1;
        unsigned int periph_clkdis13_122m_tds_pdt : 1;
        unsigned int periph_clkdis13_245m_lte : 1;
        unsigned int periph_clkdis13_19m_lte : 1;
        unsigned int periph_clkdis13_reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS13_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_61m_wbbp_gupd1_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_61m_wbbp_gupd1_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axim_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axim_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_61m_wbbp_gupd2_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_61m_wbbp_gupd2_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_gupd2_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_gupd2_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp1_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp1_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_gbbp1_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_gbbp1_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp2_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp2_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_gbbp2_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_gbbp2_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_rf0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_rf0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_rf1_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_bbc_rf1_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axis_bbc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axis_bbc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axim_bbc_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axim_bbc_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_reserve_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_reserve_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_irm_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_irm_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_491m_irm_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_491m_irm_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_irm_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_wbbp_irm_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp1_irm_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp1_irm_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp2_irm_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_104m_gbbp2_irm_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axi_lte_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_axi_lte_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_lte_pdt_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_lte_pdt_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_lte_pdf_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_lte_pdf_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tds_pdt_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_122m_tds_pdt_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_lte_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_245m_lte_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_lte_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_19m_lte_END (30)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_CLKDIS13_periph_clkdis13_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat13_122m_tds : 1;
        unsigned int periph_clkstat13_245m_tds : 1;
        unsigned int periph_clkstat13_19m_tw : 1;
        unsigned int periph_clkstat13_122m_tw : 1;
        unsigned int periph_clkstat13_61m_wbbp_gupd1 : 1;
        unsigned int periph_clkstat13_122m_wbbp : 1;
        unsigned int periph_clkstat13_axim_wbbp : 1;
        unsigned int periph_clkstat13_61m_wbbp_gupd2 : 1;
        unsigned int periph_clkstat13_122m_wbbp_gupd2 : 1;
        unsigned int periph_clkstat13_245m_wbbp : 1;
        unsigned int periph_clkstat13_104m_gbbp1 : 1;
        unsigned int periph_clkstat13_19m_gbbp1 : 1;
        unsigned int periph_clkstat13_104m_gbbp2 : 1;
        unsigned int periph_clkstat13_19m_gbbp2 : 1;
        unsigned int periph_clkstat13_19m_bbc_soc : 1;
        unsigned int periph_clkstat13_19m_bbc_rf0 : 1;
        unsigned int periph_clkstat13_19m_bbc_rf1 : 1;
        unsigned int periph_clkstat13_axis_bbc : 1;
        unsigned int periph_clkstat13_axim_bbc : 1;
        unsigned int periph_clkstat13_reserve : 1;
        unsigned int periph_clkstat13_245m_irm : 1;
        unsigned int periph_clkstat13_491m_irm : 1;
        unsigned int periph_clkstat13_122m_wbbp_irm : 1;
        unsigned int periph_clkstat13_104m_gbbp1_irm : 1;
        unsigned int periph_clkstat13_104m_gbbp2_irm : 1;
        unsigned int periph_clkstat13_axi_lte : 1;
        unsigned int periph_clkstat13_122m_lte_pdt : 1;
        unsigned int periph_clkstat13_122m_lte_pdf : 1;
        unsigned int periph_clkstat13_122m_tds_pdt : 1;
        unsigned int periph_clkstat13_245m_lte : 1;
        unsigned int periph_clkstat13_19m_lte : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT13_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_61m_wbbp_gupd1_START (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_61m_wbbp_gupd1_END (4)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_START (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_END (5)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axim_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axim_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_61m_wbbp_gupd2_START (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_61m_wbbp_gupd2_END (7)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_gupd2_START (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_gupd2_END (8)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp1_START (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp1_END (10)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_gbbp1_START (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_gbbp1_END (11)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp2_START (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp2_END (12)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_gbbp2_START (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_gbbp2_END (13)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_rf0_START (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_rf0_END (15)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_rf1_START (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_bbc_rf1_END (16)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axis_bbc_START (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axis_bbc_END (17)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axim_bbc_START (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axim_bbc_END (18)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_reserve_START (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_reserve_END (19)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_irm_START (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_irm_END (20)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_491m_irm_START (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_491m_irm_END (21)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_irm_START (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_wbbp_irm_END (22)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp1_irm_START (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp1_irm_END (23)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp2_irm_START (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_104m_gbbp2_irm_END (24)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axi_lte_START (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_axi_lte_END (25)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_lte_pdt_START (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_lte_pdt_END (26)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_lte_pdf_START (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_lte_pdf_END (27)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tds_pdt_START (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_122m_tds_pdt_END (28)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_lte_START (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_245m_lte_END (29)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_lte_START (30)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT13_periph_clkstat13_19m_lte_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken14_reserved : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKEN14_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKEN14_periph_clken14_reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKEN14_periph_clken14_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis14_reserved : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKDIS14_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKDIS14_periph_clkdis14_reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKDIS14_periph_clkdis14_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat14_reserved : 32;
    } reg;
} SOC_SCTRL_SC_PERIPH_CLKSTAT14_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_CLKSTAT14_periph_clkstat14_reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_CLKSTAT14_periph_clkstat14_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten0_0aatb : 1;
        unsigned int periph_rsten0_1adap : 1;
        unsigned int periph_rsten0_2acpu_x2x_s : 1;
        unsigned int periph_rsten0_3reset_ddrc_n : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rsten0_5reset_ddrphy_n : 1;
        unsigned int periph_rsten0_6reset_hifi_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rsten0_9reset_abb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rsten0_11mcpu : 1;
        unsigned int periph_rsten0_12mscu : 1;
        unsigned int periph_rsten0_13mp : 1;
        unsigned int periph_rsten0_14mwd : 1;
        unsigned int periph_rsten0_15mdbg : 1;
        unsigned int periph_rsten0_16mdapb : 1;
        unsigned int periph_rsten0_17matb : 1;
        unsigned int periph_rsten0_18mptm : 1;
        unsigned int periph_rsten0_19malone : 1;
        unsigned int periph_rsten0_20ddrc_hpm : 1;
        unsigned int periph_rsten0_31reserved : 11;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_0aatb_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_0aatb_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_1adap_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_1adap_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_2acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_2acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_3reset_ddrc_n_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_3reset_ddrc_n_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_5reset_ddrphy_n_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_5reset_ddrphy_n_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_6reset_hifi_n_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_6reset_hifi_n_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_9reset_abb_n_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_9reset_abb_n_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_11mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_11mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_12mscu_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_12mscu_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_13mp_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_13mp_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_14mwd_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_14mwd_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_15mdbg_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_15mdbg_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_16mdapb_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_16mdapb_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_17matb_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_17matb_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_18mptm_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_18mptm_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_19malone_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_19malone_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_20ddrc_hpm_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_20ddrc_hpm_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_31reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN0_periph_rsten0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis0_0aatb : 1;
        unsigned int periph_rstdis0_1adap : 1;
        unsigned int periph_rstdis0_2acpu_x2x_s : 1;
        unsigned int periph_rstdis0_3reset_ddrc_n : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rstdis0_5reset_ddrphy_n : 1;
        unsigned int periph_rstdis0_6reset_hifi_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rstdis0_9reset_abb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rstdis0_11mcpu : 1;
        unsigned int periph_rstdis0_12mscu : 1;
        unsigned int periph_rstdis0_13mp : 1;
        unsigned int periph_rstdis0_14mwd : 1;
        unsigned int periph_rstdis0_15mdbg : 1;
        unsigned int periph_rstdis0_16mdapb : 1;
        unsigned int periph_rstdis0_17matb : 1;
        unsigned int periph_rstdis0_18mptm : 1;
        unsigned int periph_rstdis0_19malone : 1;
        unsigned int periph_rststat0_20ddrc_hpm : 1;
        unsigned int periph_rstdis0_31reserved : 11;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_0aatb_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_0aatb_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_1adap_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_1adap_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_2acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_2acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_3reset_ddrc_n_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_3reset_ddrc_n_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_5reset_ddrphy_n_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_5reset_ddrphy_n_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_6reset_hifi_n_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_6reset_hifi_n_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_9reset_abb_n_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_9reset_abb_n_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_11mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_11mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_12mscu_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_12mscu_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_13mp_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_13mp_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_14mwd_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_14mwd_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_15mdbg_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_15mdbg_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_16mdapb_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_16mdapb_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_17matb_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_17matb_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_18mptm_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_18mptm_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_19malone_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_19malone_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rststat0_20ddrc_hpm_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rststat0_20ddrc_hpm_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_31reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS0_periph_rstdis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat0_0aatb : 1;
        unsigned int periph_rststat0_1adap : 1;
        unsigned int periph_rststat0_2acpu_x2x_s : 1;
        unsigned int periph_rststat0_3reset_ddrc_n : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rststat0_5reset_ddrphy_n : 1;
        unsigned int periph_rststat0_6reset_hifi_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rststat0_9reset_abb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rststat0_11mcpu : 1;
        unsigned int periph_rststat0_12mscu : 1;
        unsigned int periph_rststat0_13mp : 1;
        unsigned int periph_rststat0_14mwd : 1;
        unsigned int periph_rststat0_15mdbg : 1;
        unsigned int periph_rststat0_16mdapb : 1;
        unsigned int periph_rststat0_17matb : 1;
        unsigned int periph_rststat0_18mptm : 1;
        unsigned int periph_rststat0_19malone : 1;
        unsigned int periph_rstdis0_20ddrc_hpm : 1;
        unsigned int periph_rststat0_31reserved : 11;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT0_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_0aatb_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_0aatb_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_1adap_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_1adap_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_2acpu_x2x_s_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_2acpu_x2x_s_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_3reset_ddrc_n_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_3reset_ddrc_n_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_5reset_ddrphy_n_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_5reset_ddrphy_n_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_6reset_hifi_n_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_6reset_hifi_n_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_9reset_abb_n_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_9reset_abb_n_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_11mcpu_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_11mcpu_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_12mscu_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_12mscu_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_13mp_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_13mp_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_14mwd_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_14mwd_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_15mdbg_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_15mdbg_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_16mdapb_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_16mdapb_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_17matb_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_17matb_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_18mptm_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_18mptm_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_19malone_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_19malone_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rstdis0_20ddrc_hpm_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rstdis0_20ddrc_hpm_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_31reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT0_periph_rststat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten1_0uart0 : 1;
        unsigned int periph_rsten1_1uart1 : 1;
        unsigned int periph_rsten1_2uart2 : 1;
        unsigned int periph_rsten1_3uart3 : 1;
        unsigned int periph_rsten1_4uart4 : 1;
        unsigned int periph_rsten1_5uart5 : 1;
        unsigned int periph_rsten1_6uart6 : 1;
        unsigned int periph_rsten1_7spi0 : 1;
        unsigned int periph_rsten1_8spi1 : 1;
        unsigned int periph_rsten1_9i2c0 : 1;
        unsigned int periph_rsten1_10i2c1 : 1;
        unsigned int periph_rsten1_11i2c2 : 1;
        unsigned int periph_rsten1_12i2c3 : 1;
        unsigned int periph_rsten1_13i2c4 : 1;
        unsigned int periph_rsten1_14i2c5 : 1;
        unsigned int periph_rsten1_15catb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rsten1_17ctpiu : 1;
        unsigned int periph_rsten1_18cdbgapb : 1;
        unsigned int periph_rsten1_19pwm0 : 1;
        unsigned int periph_rsten1_20pwm1 : 1;
        unsigned int periph_rsten1_21reset_ipf_n : 1;
        unsigned int periph_rsten1_22reset_socp_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rsten1_24reset_admac_n : 1;
        unsigned int periph_rsten1_25reset_seceng_n : 1;
        unsigned int periph_rsten1_26usbotgub : 1;
        unsigned int periph_rsten1_27usbotguw : 1;
        unsigned int periph_rsten1_28reset_ts_n : 1;
        unsigned int periph_rsten1_29hreset_ts_n : 1;
        unsigned int periph_rsten1_30cs_dapb_off_n : 1;
        unsigned int periph_rsten1_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_0uart0_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_0uart0_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_1uart1_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_1uart1_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_2uart2_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_2uart2_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_3uart3_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_3uart3_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_4uart4_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_4uart4_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_5uart5_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_5uart5_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_6uart6_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_6uart6_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_7spi0_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_7spi0_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_8spi1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_8spi1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_9i2c0_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_9i2c0_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_10i2c1_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_10i2c1_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_11i2c2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_11i2c2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_12i2c3_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_12i2c3_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_13i2c4_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_13i2c4_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_14i2c5_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_14i2c5_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_15catb_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_15catb_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_17ctpiu_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_17ctpiu_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_18cdbgapb_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_18cdbgapb_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_19pwm0_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_19pwm0_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_20pwm1_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_20pwm1_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_21reset_ipf_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_21reset_ipf_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_22reset_socp_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_22reset_socp_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_24reset_admac_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_24reset_admac_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_25reset_seceng_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_25reset_seceng_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_26usbotgub_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_26usbotgub_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_27usbotguw_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_27usbotguw_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_28reset_ts_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_28reset_ts_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_29hreset_ts_n_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_29hreset_ts_n_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_30cs_dapb_off_n_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_30cs_dapb_off_n_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTEN1_periph_rsten1_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis1_0uart0 : 1;
        unsigned int periph_rstdis1_1uart1 : 1;
        unsigned int periph_rstdis1_2uart2 : 1;
        unsigned int periph_rstdis1_3uart3 : 1;
        unsigned int periph_rstdis1_4uart4 : 1;
        unsigned int periph_rstdis1_5uart5 : 1;
        unsigned int periph_rstdis1_6uart6 : 1;
        unsigned int periph_rstdis1_7spi0 : 1;
        unsigned int periph_rstdis1_8spi1 : 1;
        unsigned int periph_rstdis1_9i2c0 : 1;
        unsigned int periph_rstdis1_10i2c1 : 1;
        unsigned int periph_rstdis1_11i2c2 : 1;
        unsigned int periph_rstdis1_12i2c3 : 1;
        unsigned int periph_rstdis1_13i2c4 : 1;
        unsigned int periph_rstdis1_14i2c5 : 1;
        unsigned int periph_rstdis1_15catb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rstdis1_17ctpiu : 1;
        unsigned int periph_rstdis1_18cdbgapb : 1;
        unsigned int periph_rstdis1_19pwm0 : 1;
        unsigned int periph_rstdis1_20pwm1 : 1;
        unsigned int periph_rstdis1_21reset_ipf_n : 1;
        unsigned int periph_rstdis1_22reset_socp_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rstdis1_24reset_admac_n : 1;
        unsigned int periph_rstdis1_25reset_seceng_n : 1;
        unsigned int periph_rstdis1_26usbotgub : 1;
        unsigned int periph_rstdis1_27usbotguw : 1;
        unsigned int periph_rstdis1_28reset_ts_n : 1;
        unsigned int periph_rstdis1_29hreset_ts_n : 1;
        unsigned int periph_rstdis1_30cs_dapb_off_n : 1;
        unsigned int periph_rstdis1_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_0uart0_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_0uart0_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_1uart1_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_1uart1_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_2uart2_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_2uart2_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_3uart3_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_3uart3_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_4uart4_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_4uart4_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_5uart5_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_5uart5_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_6uart6_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_6uart6_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_7spi0_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_7spi0_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_8spi1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_8spi1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_9i2c0_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_9i2c0_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_10i2c1_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_10i2c1_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_11i2c2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_11i2c2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_12i2c3_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_12i2c3_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_13i2c4_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_13i2c4_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_14i2c5_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_14i2c5_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_15catb_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_15catb_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_17ctpiu_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_17ctpiu_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_18cdbgapb_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_18cdbgapb_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_19pwm0_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_19pwm0_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_20pwm1_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_20pwm1_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_21reset_ipf_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_21reset_ipf_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_22reset_socp_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_22reset_socp_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_24reset_admac_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_24reset_admac_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_25reset_seceng_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_25reset_seceng_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_26usbotgub_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_26usbotgub_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_27usbotguw_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_27usbotguw_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_28reset_ts_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_28reset_ts_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_29hreset_ts_n_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_29hreset_ts_n_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_30cs_dapb_off_n_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_30cs_dapb_off_n_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTDIS1_periph_rstdis1_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat1_0uart0 : 1;
        unsigned int periph_rststat1_1uart1 : 1;
        unsigned int periph_rststat1_2uart2 : 1;
        unsigned int periph_rststat1_3uart3 : 1;
        unsigned int periph_rststat1_4uart4 : 1;
        unsigned int periph_rststat1_5uart5 : 1;
        unsigned int periph_rststat1_6uart6 : 1;
        unsigned int periph_rststat1_7spi0 : 1;
        unsigned int periph_rststat1_8spi1 : 1;
        unsigned int periph_rststat1_9i2c0 : 1;
        unsigned int periph_rststat1_10i2c1 : 1;
        unsigned int periph_rststat1_11i2c2 : 1;
        unsigned int periph_rststat1_12i2c3 : 1;
        unsigned int periph_rststat1_13i2c4 : 1;
        unsigned int periph_rststat1_14i2c5 : 1;
        unsigned int periph_rststat1_15catb : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rststat1_17ctpiu : 1;
        unsigned int periph_rststat1_18cdbgapb : 1;
        unsigned int periph_rststat1_19pwm0 : 1;
        unsigned int periph_rststat1_20pwm1 : 1;
        unsigned int periph_rststat1_21reset_ipf_n : 1;
        unsigned int periph_rststat1_22reset_socp_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rststat1_24reset_admac_n : 1;
        unsigned int periph_rststat1_25reset_seceng_n : 1;
        unsigned int periph_rststat1_26usbotgub : 1;
        unsigned int periph_rststat1_27usbotguw : 1;
        unsigned int periph_rststat1_28reset_ts_n : 1;
        unsigned int periph_rststat1_29hreset_ts_n : 1;
        unsigned int periph_rststat1_30cs_dapb_off_n : 1;
        unsigned int periph_rststat1_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT1_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_0uart0_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_0uart0_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_1uart1_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_1uart1_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_2uart2_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_2uart2_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_3uart3_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_3uart3_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_4uart4_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_4uart4_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_5uart5_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_5uart5_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_6uart6_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_6uart6_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_7spi0_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_7spi0_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_8spi1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_8spi1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_9i2c0_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_9i2c0_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_10i2c1_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_10i2c1_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_11i2c2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_11i2c2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_12i2c3_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_12i2c3_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_13i2c4_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_13i2c4_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_14i2c5_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_14i2c5_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_15catb_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_15catb_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_17ctpiu_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_17ctpiu_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_18cdbgapb_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_18cdbgapb_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_19pwm0_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_19pwm0_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_20pwm1_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_20pwm1_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_21reset_ipf_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_21reset_ipf_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_22reset_socp_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_22reset_socp_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_24reset_admac_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_24reset_admac_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_25reset_seceng_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_25reset_seceng_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_26usbotgub_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_26usbotgub_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_27usbotguw_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_27usbotguw_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_28reset_ts_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_28reset_ts_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_29hreset_ts_n_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_29hreset_ts_n_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_30cs_dapb_off_n_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_30cs_dapb_off_n_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT1_periph_rststat1_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rsten2_3ac : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rsten2_5ahdmi : 1;
        unsigned int periph_rsten2_6sio0 : 1;
        unsigned int periph_rsten2_7sio1 : 1;
        unsigned int periph_rsten2_8sio2 : 1;
        unsigned int periph_rsten2_9sio3 : 1;
        unsigned int periph_rsten2_10mmc0 : 1;
        unsigned int periph_rsten2_11mmc1 : 1;
        unsigned int periph_rsten2_12mmc2 : 1;
        unsigned int periph_rsten2_13nandc : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rsten2_15hport : 1;
        unsigned int periph_rsten2_16aspdif : 1;
        unsigned int periph_rsten2_17reserved : 1;
        unsigned int periph_rsten2_18reserved : 1;
        unsigned int periph_rsten2_19reserved : 1;
        unsigned int periph_rsten2_20reserved : 1;
        unsigned int periph_rsten2_21reserved : 1;
        unsigned int periph_rsten2_22reserved : 1;
        unsigned int periph_rsten2_23reserved : 1;
        unsigned int periph_rsten2_24reserved : 1;
        unsigned int periph_rsten2_25reserved : 1;
        unsigned int periph_rsten2_26reserved : 1;
        unsigned int periph_rsten2_27reserved : 1;
        unsigned int periph_rsten2_28reserved : 1;
        unsigned int periph_rsten2_29reserved : 1;
        unsigned int periph_rsten2_30reserved : 1;
        unsigned int periph_rsten2_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_3ac_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_3ac_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_5ahdmi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_5ahdmi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_6sio0_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_6sio0_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_7sio1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_7sio1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_8sio2_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_8sio2_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_9sio3_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_9sio3_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_10mmc0_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_10mmc0_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_11mmc1_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_11mmc1_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_12mmc2_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_12mmc2_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_13nandc_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_13nandc_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_15hport_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_15hport_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_16aspdif_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_16aspdif_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_17reserved_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_17reserved_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_18reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_18reserved_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_19reserved_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_19reserved_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_21reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_21reserved_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_22reserved_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_22reserved_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_23reserved_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_23reserved_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_24reserved_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_24reserved_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_25reserved_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_25reserved_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_26reserved_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_26reserved_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_27reserved_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_27reserved_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_28reserved_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_28reserved_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_29reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_29reserved_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_30reserved_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_30reserved_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTEN2_periph_rsten2_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rstdis2_3ac : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rstdis2_5ahdmi : 1;
        unsigned int periph_rstdis2_6sio0 : 1;
        unsigned int periph_rstdis2_7sio1 : 1;
        unsigned int periph_rstdis2_8sio2 : 1;
        unsigned int periph_rstdis2_9sio3 : 1;
        unsigned int periph_rstdis2_10mmc0 : 1;
        unsigned int periph_rstdis2_11mmc1 : 1;
        unsigned int periph_rstdis2_12mmc2 : 1;
        unsigned int periph_rstdis2_13nandc : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int periph_rstdis2_16aspdif : 1;
        unsigned int periph_rstdis2_17reserved : 1;
        unsigned int periph_rstdis2_18reserved : 1;
        unsigned int periph_rstdis2_19reserved : 1;
        unsigned int periph_rstdis2_20reserved : 1;
        unsigned int periph_rstdis2_21reserved : 1;
        unsigned int periph_rstdis2_22reserved : 1;
        unsigned int periph_rstdis2_23reserved : 1;
        unsigned int periph_rstdis2_24reserved : 1;
        unsigned int periph_rstdis2_25reserved : 1;
        unsigned int periph_rstdis2_26reserved : 1;
        unsigned int periph_rstdis2_27reserved : 1;
        unsigned int periph_rstdis2_28reserved : 1;
        unsigned int periph_rstdis2_29reserved : 1;
        unsigned int periph_rstedis2_30reserved : 1;
        unsigned int periph_rstdis2_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_3ac_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_3ac_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_5ahdmi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_5ahdmi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_6sio0_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_6sio0_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_7sio1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_7sio1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_8sio2_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_8sio2_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_9sio3_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_9sio3_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_10mmc0_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_10mmc0_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_11mmc1_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_11mmc1_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_12mmc2_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_12mmc2_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_13nandc_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_13nandc_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_16aspdif_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_16aspdif_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_17reserved_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_17reserved_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_18reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_18reserved_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_19reserved_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_19reserved_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_21reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_21reserved_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_22reserved_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_22reserved_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_23reserved_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_23reserved_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_24reserved_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_24reserved_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_25reserved_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_25reserved_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_26reserved_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_26reserved_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_27reserved_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_27reserved_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_28reserved_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_28reserved_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_29reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_29reserved_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstedis2_30reserved_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstedis2_30reserved_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rststat2_3ac : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rststat2_5ahdmi : 1;
        unsigned int periph_rststat2_6sio0 : 1;
        unsigned int periph_rststat2_7sio1 : 1;
        unsigned int periph_rststat2_8sio2 : 1;
        unsigned int periph_rststat2_9sio3 : 1;
        unsigned int periph_rststat2_10mmc0 : 1;
        unsigned int periph_rststat2_11mmc1 : 1;
        unsigned int periph_rststat2_12mmc2 : 1;
        unsigned int periph_rststat2_13nandc : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int periph_rststat2_16aspdif : 1;
        unsigned int periph_rststat2_17reserved : 1;
        unsigned int periph_rststat2_18reserved : 1;
        unsigned int periph_rststat2_19reserved : 1;
        unsigned int periph_rststat2_20reserved : 1;
        unsigned int periph_rststat2_21reserved : 1;
        unsigned int periph_rststat2_22reserved : 1;
        unsigned int periph_rststat2_23reserved : 1;
        unsigned int periph_rststat2_24reserved : 1;
        unsigned int periph_rststat2_25reserved : 1;
        unsigned int periph_rststat2_26reserved : 1;
        unsigned int periph_rststat2_27reserved : 1;
        unsigned int periph_rststat2_28reserved : 1;
        unsigned int periph_rststat2_29reserved : 1;
        unsigned int periph_rststat2_30reserved : 1;
        unsigned int periph_rststat2_31reserved : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT2_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_3ac_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_3ac_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_5ahdmi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_5ahdmi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_6sio0_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_6sio0_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_7sio1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_7sio1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_8sio2_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_8sio2_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_9sio3_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_9sio3_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_10mmc0_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_10mmc0_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_11mmc1_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_11mmc1_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_12mmc2_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_12mmc2_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_13nandc_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_13nandc_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_16aspdif_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_16aspdif_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_17reserved_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_17reserved_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_18reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_18reserved_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_19reserved_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_19reserved_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_21reserved_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_21reserved_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_22reserved_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_22reserved_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_23reserved_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_23reserved_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_24reserved_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_24reserved_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_25reserved_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_25reserved_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_26reserved_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_26reserved_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_27reserved_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_27reserved_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_28reserved_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_28reserved_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_29reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_29reserved_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_30reserved_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_30reserved_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_31reserved_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT2_periph_rststat2_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten3_0reserved : 1;
        unsigned int periph_rsten3_1reserved : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rsten3_3reserved : 1;
        unsigned int periph_rsten3_4reset_cfg_brg_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rsten3_7reserved : 4;
        unsigned int periph_rsten3_11areset_periph_bus_n : 1;
        unsigned int periph_rsten3_12reserved : 1;
        unsigned int periph_rsten3_13hreset_mahb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rsten3_15preset_periph_bus_n : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rsten3_17hreset_hpahb_n : 1;
        unsigned int periph_rsten3_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_0reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_0reserved_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_1reserved_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_1reserved_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_3reserved_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_3reserved_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_4reset_cfg_brg_n_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_4reset_cfg_brg_n_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_7reserved_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_7reserved_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_11areset_periph_bus_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_11areset_periph_bus_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_12reserved_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_12reserved_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_13hreset_mahb_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_13hreset_mahb_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_15preset_periph_bus_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_15preset_periph_bus_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_17hreset_hpahb_n_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_17hreset_hpahb_n_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_31reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN3_periph_rsten3_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis3_0reserved : 1;
        unsigned int periph_rstdis3_1reserved : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rstdis3_3reserved : 1;
        unsigned int periph_rstdis3_4reset_cfg_brg_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rstdis3_7reserved : 4;
        unsigned int periph_rstdis3_11areset_periph_bus_n : 1;
        unsigned int periph_rstdis3_12reserved : 1;
        unsigned int periph_rstdis3_13hreset_mahb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rstdis3_15preset_periph_bus_n : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rstdis3_17hreset_hpahb_n : 1;
        unsigned int periph_rstdis3_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_0reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_0reserved_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_1reserved_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_1reserved_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_3reserved_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_3reserved_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_4reset_cfg_brg_n_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_4reset_cfg_brg_n_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_7reserved_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_7reserved_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_11areset_periph_bus_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_11areset_periph_bus_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_12reserved_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_12reserved_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_13hreset_mahb_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_13hreset_mahb_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_15preset_periph_bus_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_15preset_periph_bus_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_17hreset_hpahb_n_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_17hreset_hpahb_n_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_31reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS3_periph_rstdis3_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat3_0reserved : 1;
        unsigned int periph_rststat3_1reserved : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rststat3_3reserved : 1;
        unsigned int periph_rststat3_4reset_cfg_brg_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rststat3_7reserved : 4;
        unsigned int periph_rststat3_11areset_periph_bus_n : 1;
        unsigned int periph_rststat3_12reserved : 1;
        unsigned int periph_rststat3_13hreset_mahb_n : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rststat3_15preset_periph_bus_n : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rststat3_17hreset_hpahb_n : 1;
        unsigned int periph_rststat3_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT3_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_0reserved_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_0reserved_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_1reserved_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_1reserved_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_3reserved_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_3reserved_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_4reset_cfg_brg_n_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_4reset_cfg_brg_n_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_7reserved_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_7reserved_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_11areset_periph_bus_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_11areset_periph_bus_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_12reserved_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_12reserved_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_13hreset_mahb_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_13hreset_mahb_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_15preset_periph_bus_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_15preset_periph_bus_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_17hreset_hpahb_n_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_17hreset_hpahb_n_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_31reserved_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT3_periph_rststat3_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten6_0bkclk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rsten6_5bdapb : 1;
        unsigned int periph_rsten6_6batb : 1;
        unsigned int periph_rsten6_7bdebug : 1;
        unsigned int periph_rsten6_8batbcore : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rsten6_10reset_x2x_mcpu_m1_m_n : 1;
        unsigned int periph_rsten6_11reset_mdmac_n : 1;
        unsigned int periph_rsten6_12reset_upacc_n : 1;
        unsigned int periph_rsten6_13reset_cicoml_n : 1;
        unsigned int periph_rsten6_14reset_cicom0_n : 1;
        unsigned int periph_rsten6_15reset_cicom1_n : 1;
        unsigned int periph_rsten6_16muart0 : 1;
        unsigned int periph_rsten6_17muart1 : 1;
        unsigned int periph_rsten6_18reset_img_bus_n : 1;
        unsigned int periph_rsten6_19reset_video_bus_n : 1;
        unsigned int periph_rsten6_20reserved : 1;
        unsigned int periph_rsten6_21reset_x2x_l2_n : 1;
        unsigned int periph_rsten6_22reset_x2x_g3d_n : 1;
        unsigned int periph_rsten6_23reset_x2x_sys_n : 1;
        unsigned int periph_rsten6_24reset_mcpu_m_n : 1;
        unsigned int periph_rsten6_25reset_modem_n : 1;
        unsigned int periph_rsten6_26reset_x2x_dec_n : 1;
        unsigned int periph_rsten6_27reset_x2x_venc_n : 1;
        unsigned int periph_rsten6_28reset_x2x_vpp_n : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int periph_rsten6_31areset_mdm_bus_n : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN6_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_0bkclk_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_0bkclk_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_5bdapb_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_5bdapb_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_6batb_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_6batb_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_7bdebug_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_7bdebug_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_8batbcore_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_8batbcore_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_10reset_x2x_mcpu_m1_m_n_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_10reset_x2x_mcpu_m1_m_n_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_11reset_mdmac_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_11reset_mdmac_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_12reset_upacc_n_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_12reset_upacc_n_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_13reset_cicoml_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_13reset_cicoml_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_14reset_cicom0_n_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_14reset_cicom0_n_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_15reset_cicom1_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_15reset_cicom1_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_16muart0_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_16muart0_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_17muart1_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_17muart1_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_18reset_img_bus_n_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_18reset_img_bus_n_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_19reset_video_bus_n_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_19reset_video_bus_n_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_21reset_x2x_l2_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_21reset_x2x_l2_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_22reset_x2x_g3d_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_22reset_x2x_g3d_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_23reset_x2x_sys_n_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_23reset_x2x_sys_n_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_24reset_mcpu_m_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_24reset_mcpu_m_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_25reset_modem_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_25reset_modem_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_26reset_x2x_dec_n_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_26reset_x2x_dec_n_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_27reset_x2x_venc_n_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_27reset_x2x_venc_n_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_28reset_x2x_vpp_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_28reset_x2x_vpp_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_31areset_mdm_bus_n_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTEN6_periph_rsten6_31areset_mdm_bus_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis6_0bkclk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rstdis6_5bdapb : 1;
        unsigned int periph_rstdis6_6batb : 1;
        unsigned int periph_rstdis6_7bdebug : 1;
        unsigned int periph_rstdis6_8batbcore : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rstdis6_10reset_x2x_mcpu_m1_m_n : 1;
        unsigned int periph_rstdis6_11reset_mdmac_n : 1;
        unsigned int periph_rstdis6_12reset_upacc_n : 1;
        unsigned int periph_rstdis6_13reset_cicoml_n : 1;
        unsigned int periph_rstdis6_14reset_cicom0_n : 1;
        unsigned int periph_rstdis6_15reset_cicom1_n : 1;
        unsigned int periph_rstdis6_16muart0 : 1;
        unsigned int periph_rstdis6_17muart1 : 1;
        unsigned int periph_rstdis6_18reset_img_bus_n : 1;
        unsigned int periph_rstdis6_19reset_video_bus_n : 1;
        unsigned int periph_rstdis6_20reserved : 1;
        unsigned int periph_rststat6_21reset_x2x_l2_n : 1;
        unsigned int periph_rstdis6_22reset_x2x_g3d_n : 1;
        unsigned int periph_rstdis6_23reset_x2x_sys_n : 1;
        unsigned int periph_rstdis6_24reset_mcpu_m_n : 1;
        unsigned int periph_rstdis6_25reset_modem_n : 1;
        unsigned int periph_rstdis6_26reset_x2x_dec_n : 1;
        unsigned int periph_rstdis6_27reset_x2x_venc_n : 1;
        unsigned int periph_rstdis6_28reset_x2x_vpp_n : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int periph_rsten6_31areset_mdm_bus_n : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS6_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_0bkclk_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_0bkclk_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_5bdapb_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_5bdapb_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_6batb_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_6batb_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_7bdebug_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_7bdebug_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_8batbcore_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_8batbcore_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_10reset_x2x_mcpu_m1_m_n_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_10reset_x2x_mcpu_m1_m_n_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_11reset_mdmac_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_11reset_mdmac_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_12reset_upacc_n_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_12reset_upacc_n_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_13reset_cicoml_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_13reset_cicoml_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_14reset_cicom0_n_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_14reset_cicom0_n_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_15reset_cicom1_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_15reset_cicom1_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_16muart0_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_16muart0_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_17muart1_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_17muart1_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_18reset_img_bus_n_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_18reset_img_bus_n_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_19reset_video_bus_n_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_19reset_video_bus_n_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rststat6_21reset_x2x_l2_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rststat6_21reset_x2x_l2_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_22reset_x2x_g3d_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_22reset_x2x_g3d_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_23reset_x2x_sys_n_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_23reset_x2x_sys_n_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_24reset_mcpu_m_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_24reset_mcpu_m_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_25reset_modem_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_25reset_modem_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_26reset_x2x_dec_n_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_26reset_x2x_dec_n_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_27reset_x2x_venc_n_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_27reset_x2x_venc_n_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_28reset_x2x_vpp_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rstdis6_28reset_x2x_vpp_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rsten6_31areset_mdm_bus_n_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTDIS6_periph_rsten6_31areset_mdm_bus_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat6_0bkclk : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int periph_rststat6_5bdapb : 1;
        unsigned int periph_rststat6_6batb : 1;
        unsigned int periph_rststat6_7bdebug : 1;
        unsigned int periph_rststat6_8batbcore : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_rststat6_10reset_x2x_mcpu_m1_m_n : 1;
        unsigned int periph_rststat6_11reset_mdmac_n : 1;
        unsigned int periph_rststat6_12reset_upacc_n : 1;
        unsigned int periph_rststat6_13reset_cicoml_n : 1;
        unsigned int periph_rststat6_14reset_cicom0_n : 1;
        unsigned int periph_rststat6_15reset_cicom1_n : 1;
        unsigned int periph_rststat6_16muart0 : 1;
        unsigned int periph_rststat6_17muart1 : 1;
        unsigned int periph_rststat6_18reset_img_bus_n : 1;
        unsigned int periph_rststat6_19reset_video_bus_n : 1;
        unsigned int periph_rststat6_20reserved : 1;
        unsigned int periph_rststat6_21reset_x2x_l2_n : 1;
        unsigned int periph_rststat6_22reset_x2x_g3d_n : 1;
        unsigned int periph_rststat6_23reset_x2x_sys_n : 1;
        unsigned int periph_rststat6_24reset_mcpu_m_n : 1;
        unsigned int periph_rststat6_25reset_modem_n : 1;
        unsigned int periph_rststat6_26reset_x2x_dec_n : 1;
        unsigned int periph_rststat6_27reset_x2x_venc_n : 1;
        unsigned int periph_rststat6_28reset_x2x_vpp_n : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int periph_rsten6_31areset_mdm_bus_n : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT6_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_0bkclk_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_0bkclk_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_5bdapb_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_5bdapb_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_6batb_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_6batb_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_7bdebug_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_7bdebug_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_8batbcore_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_8batbcore_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_10reset_x2x_mcpu_m1_m_n_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_10reset_x2x_mcpu_m1_m_n_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_11reset_mdmac_n_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_11reset_mdmac_n_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_12reset_upacc_n_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_12reset_upacc_n_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_13reset_cicoml_n_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_13reset_cicoml_n_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_14reset_cicom0_n_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_14reset_cicom0_n_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_15reset_cicom1_n_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_15reset_cicom1_n_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_16muart0_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_16muart0_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_17muart1_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_17muart1_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_18reset_img_bus_n_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_18reset_img_bus_n_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_19reset_video_bus_n_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_19reset_video_bus_n_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_20reserved_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_20reserved_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_21reset_x2x_l2_n_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_21reset_x2x_l2_n_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_22reset_x2x_g3d_n_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_22reset_x2x_g3d_n_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_23reset_x2x_sys_n_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_23reset_x2x_sys_n_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_24reset_mcpu_m_n_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_24reset_mcpu_m_n_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_25reset_modem_n_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_25reset_modem_n_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_26reset_x2x_dec_n_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_26reset_x2x_dec_n_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_27reset_x2x_venc_n_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_27reset_x2x_venc_n_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_28reset_x2x_vpp_n_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rststat6_28reset_x2x_vpp_n_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rsten6_31areset_mdm_bus_n_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT6_periph_rsten6_31areset_mdm_bus_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten7_0e0power : 1;
        unsigned int periph_rsten7_1e0axi : 1;
        unsigned int periph_rsten7_2e0pixldi : 1;
        unsigned int periph_rsten7_3e0core : 1;
        unsigned int periph_rsten7_4e1power : 1;
        unsigned int periph_rsten7_5e1axi : 1;
        unsigned int periph_rsten7_6e1pixldi : 1;
        unsigned int periph_rsten7_7e1core : 1;
        unsigned int periph_rsten7_8hdmiapbs : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rsten7_10isppower : 1;
        unsigned int periph_rsten7_11ispaxi : 1;
        unsigned int periph_rsten7_12ispwork : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rsten7_14vencw : 1;
        unsigned int periph_rsten7_15vdecw : 1;
        unsigned int periph_rsten7_16reserved : 1;
        unsigned int periph_rsten7_17vppw : 1;
        unsigned int periph_rsten7_18g2dcon : 1;
        unsigned int periph_rsten7_19g2daxi : 1;
        unsigned int periph_rsten7_20g2dcore : 1;
        unsigned int periph_rsten7_21reset_mali : 1;
        unsigned int periph_rsten7_22hdmi : 1;
        unsigned int periph_rsten7_23csi0 : 1;
        unsigned int periph_rsten7_24csi1 : 1;
        unsigned int periph_rsten7_25csi2 : 1;
        unsigned int periph_rsten7_26csi3 : 1;
        unsigned int periph_rsten7_27g3d_p2p : 1;
        unsigned int periph_rsten7_28g3d_hpm : 1;
        unsigned int periph_rsten7_31reserved : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN7_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_0e0power_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_0e0power_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_1e0axi_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_1e0axi_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_2e0pixldi_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_2e0pixldi_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_3e0core_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_3e0core_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_4e1power_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_4e1power_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_5e1axi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_5e1axi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_6e1pixldi_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_6e1pixldi_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_7e1core_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_7e1core_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_8hdmiapbs_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_8hdmiapbs_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_10isppower_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_10isppower_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_11ispaxi_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_11ispaxi_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_12ispwork_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_12ispwork_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_14vencw_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_14vencw_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_15vdecw_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_15vdecw_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_16reserved_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_16reserved_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_18g2dcon_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_18g2dcon_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_19g2daxi_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_19g2daxi_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_20g2dcore_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_20g2dcore_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_21reset_mali_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_21reset_mali_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_22hdmi_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_22hdmi_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_23csi0_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_23csi0_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_24csi1_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_24csi1_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_25csi2_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_25csi2_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_26csi3_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_26csi3_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_27g3d_p2p_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_27g3d_p2p_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_28g3d_hpm_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_28g3d_hpm_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_31reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis7_0e0power : 1;
        unsigned int periph_rstdis7_1e0axi : 1;
        unsigned int periph_rstdis7_2e0pixldi : 1;
        unsigned int periph_rstdis7_3e0core : 1;
        unsigned int periph_rstdis7_4e1power : 1;
        unsigned int periph_rstdis7_5e1axi : 1;
        unsigned int periph_rstdis7_6e1pixldi : 1;
        unsigned int periph_rstdis7_7e1core : 1;
        unsigned int periph_rstdis7_8hdmiapbs : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rstdis7_10isppower : 1;
        unsigned int periph_rstdis7_11ispaxi : 1;
        unsigned int periph_rstdis7_12ispwork : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rstdis7_14vencw : 1;
        unsigned int periph_rstdis7_15vdecw : 1;
        unsigned int periph_rstdis7_16reserved : 1;
        unsigned int periph_rstdis7_17vppw : 1;
        unsigned int periph_rstdis7_18g2dcon : 1;
        unsigned int periph_rstdis7_19g2daxi : 1;
        unsigned int periph_rstdis7_20g2dcore : 1;
        unsigned int periph_rstdis7_21reset_mali : 1;
        unsigned int periph_rstdis7_22hdmi : 1;
        unsigned int periph_rstdis7_23csi0 : 1;
        unsigned int periph_rstdis7_24csi1 : 1;
        unsigned int periph_rstdis7_25csi2 : 1;
        unsigned int periph_rstdis7_26csi3 : 1;
        unsigned int periph_rstdis7_27g3d_p2p : 1;
        unsigned int periph_rstdis7_28g3d_hpm : 1;
        unsigned int periph_rstdis7_31reserved : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS7_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_0e0power_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_0e0power_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_1e0axi_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_1e0axi_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_2e0pixldi_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_2e0pixldi_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_3e0core_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_3e0core_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_4e1power_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_4e1power_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_5e1axi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_5e1axi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_6e1pixldi_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_6e1pixldi_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_7e1core_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_7e1core_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_8hdmiapbs_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_8hdmiapbs_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_10isppower_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_10isppower_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_11ispaxi_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_11ispaxi_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_12ispwork_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_12ispwork_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_14vencw_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_14vencw_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_15vdecw_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_15vdecw_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_16reserved_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_16reserved_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_17vppw_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_17vppw_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_18g2dcon_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_18g2dcon_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_19g2daxi_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_19g2daxi_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_20g2dcore_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_20g2dcore_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_21reset_mali_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_21reset_mali_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_22hdmi_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_22hdmi_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_23csi0_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_23csi0_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_24csi1_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_24csi1_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_25csi2_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_25csi2_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_26csi3_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_26csi3_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_27g3d_p2p_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_27g3d_p2p_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_28g3d_hpm_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_28g3d_hpm_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_31reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat7_0e0power : 1;
        unsigned int periph_rststat7_1e0axi : 1;
        unsigned int periph_rststat7_2e0pixldi : 1;
        unsigned int periph_rststat7_3e0core : 1;
        unsigned int periph_rststat7_4e1power : 1;
        unsigned int periph_rststat7_5e1axi : 1;
        unsigned int periph_rststat7_6e1pixldi : 1;
        unsigned int periph_rststat7_7e1core : 1;
        unsigned int periph_rststat7_8hdmiapbs : 1;
        unsigned int reserved_0 : 1;
        unsigned int periph_rststat7_10isppower : 1;
        unsigned int periph_rststat7_11ispaxi : 1;
        unsigned int periph_rststat7_12ispwork : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rststat7_14vencw : 1;
        unsigned int periph_rststat7_15vdecw : 1;
        unsigned int periph_rststat7_16reserved : 1;
        unsigned int periph_rststat7_17vppw : 1;
        unsigned int periph_rststat7_18g2dcon : 1;
        unsigned int periph_rststat7_19g2daxi : 1;
        unsigned int periph_rststat7_20g2dcore : 1;
        unsigned int periph_rststat7_21reset_mali : 1;
        unsigned int periph_rststat7_22hdmi : 1;
        unsigned int periph_rststat7_23csi0 : 1;
        unsigned int periph_rststat7_24csi1 : 1;
        unsigned int periph_rststat7_25csi2 : 1;
        unsigned int periph_rststat7_26csi3 : 1;
        unsigned int periph_rststat7_27g3d_p2p : 1;
        unsigned int periph_rststat7_28g3d_hpm : 1;
        unsigned int periph_rststat7_31reserved : 3;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT7_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_0e0power_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_0e0power_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_1e0axi_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_1e0axi_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_2e0pixldi_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_2e0pixldi_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_3e0core_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_3e0core_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_4e1power_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_4e1power_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_5e1axi_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_5e1axi_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_6e1pixldi_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_6e1pixldi_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_7e1core_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_7e1core_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_8hdmiapbs_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_8hdmiapbs_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_10isppower_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_10isppower_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_11ispaxi_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_11ispaxi_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_12ispwork_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_12ispwork_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_14vencw_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_14vencw_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_15vdecw_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_15vdecw_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_16reserved_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_16reserved_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_17vppw_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_17vppw_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_18g2dcon_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_18g2dcon_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_19g2daxi_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_19g2daxi_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_20g2dcore_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_20g2dcore_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_21reset_mali_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_21reset_mali_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_22hdmi_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_22hdmi_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_23csi0_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_23csi0_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_24csi1_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_24csi1_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_25csi2_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_25csi2_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_26csi3_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_26csi3_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_27g3d_p2p_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_27g3d_p2p_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_28g3d_hpm_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_28g3d_hpm_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_31reserved_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT7_periph_rststat7_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten8_122m_tds : 1;
        unsigned int periph_rsten8_245m_tds : 1;
        unsigned int periph_rsten8_19m_tw : 1;
        unsigned int periph_rsten8_32k_tw : 1;
        unsigned int periph_rsten8_122m_tw : 1;
        unsigned int periph_rsten8_61m_wbbp_gupd1 : 1;
        unsigned int periph_rsten8_122m_wbbp : 1;
        unsigned int periph_rsten8_104m_gbbp1_gupd1 : 1;
        unsigned int periph_rsten8_104m_gbbp2_gupd1 : 1;
        unsigned int periph_rsten8_axim_wbbp : 1;
        unsigned int periph_rsten8_61m_wbbp_gupd2 : 1;
        unsigned int periph_rsten8_122m_wbbp_gupd2 : 1;
        unsigned int periph_rsten8_245m_wbbp : 1;
        unsigned int periph_rsten8_104m_gbbp1 : 1;
        unsigned int periph_rsten8_19m_gbbp1_soc : 1;
        unsigned int periph_rsten8_32k_gbbp1 : 1;
        unsigned int periph_rsten8_104m_gbbp2 : 1;
        unsigned int periph_rsten8_19m_gbbp2_soc : 1;
        unsigned int periph_rsten8_32k_gbbp2 : 1;
        unsigned int periph_rsten8_19m_bbc_soc : 1;
        unsigned int periph_rsten8_19m_bbc_rf0 : 1;
        unsigned int periph_rsten8_19m_bbc_rf1 : 1;
        unsigned int periph_rsten8_122m_tw_bbc : 1;
        unsigned int periph_rsten8_122m_lte_pdt_bbc : 1;
        unsigned int periph_rsten8_122m_lte_pdf_bbc : 1;
        unsigned int periph_rsten8_104m_gbbp1_bbc : 1;
        unsigned int periph_rsten8_104m_gbbp2_bbc : 1;
        unsigned int periph_rsten8_axis_bbc : 1;
        unsigned int periph_rsten8_245m_tds_bbc : 1;
        unsigned int periph_rsten8_245m_lte_bbc : 1;
        unsigned int periph_rsten8_axim_bbc : 1;
        unsigned int periph_rsten8_axis_dbg : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tw_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tw_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_61m_wbbp_gupd1_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_61m_wbbp_gupd1_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_gupd1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_gupd1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_gupd1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_gupd1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axim_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axim_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_61m_wbbp_gupd2_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_61m_wbbp_gupd2_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_wbbp_gupd2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_wbbp_gupd2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_wbbp_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_wbbp_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_gbbp1_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_gbbp1_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_gbbp1_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_gbbp1_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_gbbp2_soc_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_gbbp2_soc_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_gbbp2_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_32k_gbbp2_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_soc_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_soc_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_rf0_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_rf0_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_rf1_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_19m_bbc_rf1_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tw_bbc_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_tw_bbc_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_lte_pdt_bbc_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_lte_pdt_bbc_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_lte_pdf_bbc_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_122m_lte_pdf_bbc_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_bbc_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp1_bbc_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_bbc_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_104m_gbbp2_bbc_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axis_bbc_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axis_bbc_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_tds_bbc_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_tds_bbc_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_lte_bbc_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_245m_lte_bbc_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axim_bbc_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axim_bbc_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axis_dbg_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTEN8_periph_rsten8_axis_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis8_122m_tds : 1;
        unsigned int periph_rstdis8_245m_tds : 1;
        unsigned int periph_rstdis8_19m_tw : 1;
        unsigned int periph_rstdis8_32k_tw : 1;
        unsigned int periph_rstdis8_122m_tw : 1;
        unsigned int periph_rstdis8_61m_wbbp_gupd1 : 1;
        unsigned int periph_rstdis8_122m_wbbp : 1;
        unsigned int periph_rstdis8_104m_gbbp1_gupd1 : 1;
        unsigned int periph_rstdis8_104m_gbbp2_gupd1 : 1;
        unsigned int periph_rstdis8_axim_wbbp : 1;
        unsigned int periph_rstdis8_61m_wbbp_gupd2 : 1;
        unsigned int periph_rstdis8_122m_wbbp_gupd2 : 1;
        unsigned int periph_rstdis8_245m_wbbp : 1;
        unsigned int periph_rstdis8_104m_gbbp1 : 1;
        unsigned int periph_rstdis8_19m_gbbp1_soc : 1;
        unsigned int periph_rstdis8_32k_gbbp1 : 1;
        unsigned int periph_rstdis8_104m_gbbp2 : 1;
        unsigned int periph_rstdis8_19m_gbbp2_soc : 1;
        unsigned int periph_rstdis8_32k_gbbp2 : 1;
        unsigned int periph_rstdis8_19m_bbc_soc : 1;
        unsigned int periph_rstdis8_19m_bbc_rf0 : 1;
        unsigned int periph_rstdis8_19m_bbc_rf1 : 1;
        unsigned int periph_rstdis8_122m_tw_bbc : 1;
        unsigned int periph_rstdis8_122m_lte_pdt_bbc : 1;
        unsigned int periph_rstdis8_122m_lte_pdf_bbc : 1;
        unsigned int periph_rstdis8_104m_gbbp1_bbc : 1;
        unsigned int periph_rstdis8_104m_gbbp2_bbc : 1;
        unsigned int periph_rstdis8_axis_bbc : 1;
        unsigned int periph_rstdis8_245m_tds_bbc : 1;
        unsigned int periph_rstdis8_245m_lte_bbc : 1;
        unsigned int periph_rstdis8_axim_bbc : 1;
        unsigned int periph_rstdis8_axis_dbg : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tw_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tw_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_61m_wbbp_gupd1_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_61m_wbbp_gupd1_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_gupd1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_gupd1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_gupd1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_gupd1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axim_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axim_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_61m_wbbp_gupd2_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_61m_wbbp_gupd2_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_wbbp_gupd2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_wbbp_gupd2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_wbbp_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_wbbp_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_gbbp1_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_gbbp1_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_gbbp1_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_gbbp1_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_gbbp2_soc_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_gbbp2_soc_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_gbbp2_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_32k_gbbp2_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_soc_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_soc_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_rf0_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_rf0_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_rf1_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_19m_bbc_rf1_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tw_bbc_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_tw_bbc_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_lte_pdt_bbc_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_lte_pdt_bbc_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_lte_pdf_bbc_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_122m_lte_pdf_bbc_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_bbc_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp1_bbc_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_bbc_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_104m_gbbp2_bbc_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axis_bbc_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axis_bbc_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_tds_bbc_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_tds_bbc_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_lte_bbc_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_245m_lte_bbc_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axim_bbc_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axim_bbc_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axis_dbg_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTDIS8_periph_rstdis8_axis_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat8_122m_tds : 1;
        unsigned int periph_rststat8_245m_tds : 1;
        unsigned int periph_rststat8_19m_tw : 1;
        unsigned int periph_rststat8_32k_tw : 1;
        unsigned int periph_rststat8_122m_tw : 1;
        unsigned int periph_rststat8_61m_wbbp_gupd1 : 1;
        unsigned int periph_rststat8_122m_wbbp : 1;
        unsigned int periph_rststat8_104m_gbbp1_gupd1 : 1;
        unsigned int periph_rststat8_104m_gbbp2_gupd1 : 1;
        unsigned int periph_rststat8_axim_wbbp : 1;
        unsigned int periph_rststat8_61m_wbbp_gupd2 : 1;
        unsigned int periph_rststat8_122m_wbbp_gupd2 : 1;
        unsigned int periph_rststat8_245m_wbbp : 1;
        unsigned int periph_rststat8_104m_gbbp1 : 1;
        unsigned int periph_rststat8_19m_gbbp1_soc : 1;
        unsigned int periph_rststat8_32k_gbbp1 : 1;
        unsigned int periph_rststat8_104m_gbbp2 : 1;
        unsigned int periph_rststat8_19m_gbbp2_soc : 1;
        unsigned int periph_rststat8_32k_gbbp2 : 1;
        unsigned int periph_rststat8_19m_bbc_soc : 1;
        unsigned int periph_rststat8_19m_bbc_rf0 : 1;
        unsigned int periph_rststat8_19m_bbc_rf1 : 1;
        unsigned int periph_rststat8_122m_tw_bbc : 1;
        unsigned int periph_rststat8_122m_lte_pdt_bbc : 1;
        unsigned int periph_rststat8_122m_lte_pdf_bbc : 1;
        unsigned int periph_rststat8_104m_gbbp1_bbc : 1;
        unsigned int periph_rststat8_104m_gbbp2_bbc : 1;
        unsigned int periph_rststat8_axis_bbc : 1;
        unsigned int periph_rststat8_245m_tds_bbc : 1;
        unsigned int periph_rststat8_245m_lte_bbc : 1;
        unsigned int periph_rststat8_axim_bbc : 1;
        unsigned int periph_rststat8_axis_dbg : 1;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT8_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tds_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tds_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_tds_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_tds_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_tw_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_tw_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_tw_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_tw_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tw_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tw_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_61m_wbbp_gupd1_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_61m_wbbp_gupd1_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_wbbp_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_wbbp_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_gupd1_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_gupd1_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_gupd1_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_gupd1_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axim_wbbp_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axim_wbbp_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_61m_wbbp_gupd2_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_61m_wbbp_gupd2_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_wbbp_gupd2_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_wbbp_gupd2_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_wbbp_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_wbbp_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_END (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_gbbp1_soc_START (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_gbbp1_soc_END (14)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_gbbp1_START (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_gbbp1_END (15)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_START (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_END (16)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_gbbp2_soc_START (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_gbbp2_soc_END (17)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_gbbp2_START (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_32k_gbbp2_END (18)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_soc_START (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_soc_END (19)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_rf0_START (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_rf0_END (20)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_rf1_START (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_19m_bbc_rf1_END (21)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tw_bbc_START (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_tw_bbc_END (22)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_lte_pdt_bbc_START (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_lte_pdt_bbc_END (23)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_lte_pdf_bbc_START (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_122m_lte_pdf_bbc_END (24)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_bbc_START (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp1_bbc_END (25)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_bbc_START (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_104m_gbbp2_bbc_END (26)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axis_bbc_START (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axis_bbc_END (27)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_tds_bbc_START (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_tds_bbc_END (28)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_lte_bbc_START (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_245m_lte_bbc_END (29)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axim_bbc_START (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axim_bbc_END (30)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axis_dbg_START (31)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT8_periph_rststat8_axis_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rsten9_245m_irm : 1;
        unsigned int periph_rsten9_491m_irm : 1;
        unsigned int periph_rsten9_122m_wbbp_irm : 1;
        unsigned int periph_rsten9_104m_gbbp1_irm : 1;
        unsigned int periph_rsten9_104m_gbbp2_irm : 1;
        unsigned int periph_rsten9_axis_irm : 1;
        unsigned int periph_rsten9_axi_lte : 1;
        unsigned int periph_rsten9_122m_lte_pdf : 1;
        unsigned int periph_rsten9_122m_lte_pdt : 1;
        unsigned int periph_rsten9_122m_tds_pdt : 1;
        unsigned int periph_rsten9_245m_lte : 1;
        unsigned int periph_rsten9_19m_lte_soc : 1;
        unsigned int periph_rsten9_32k_lte : 1;
        unsigned int periph_rsten9_31reserved : 19;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTEN9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_245m_irm_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_245m_irm_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_491m_irm_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_491m_irm_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_wbbp_irm_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_wbbp_irm_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_104m_gbbp1_irm_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_104m_gbbp1_irm_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_104m_gbbp2_irm_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_104m_gbbp2_irm_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_axis_irm_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_axis_irm_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_axi_lte_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_axi_lte_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_lte_pdf_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_lte_pdf_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_lte_pdt_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_lte_pdt_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_tds_pdt_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_122m_tds_pdt_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_245m_lte_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_245m_lte_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_19m_lte_soc_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_19m_lte_soc_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_32k_lte_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_32k_lte_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_31reserved_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTEN9_periph_rsten9_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rstdis9_245m_irm : 1;
        unsigned int periph_rstdis9_491m_irm : 1;
        unsigned int periph_rstdis9_122m_wbbp_irm : 1;
        unsigned int periph_rstdis9_104m_gbbp1_irm : 1;
        unsigned int periph_rstdis9_104m_gbbp2_irm : 1;
        unsigned int periph_rstdis9_axis_irm : 1;
        unsigned int periph_rstdis9_axi_lte : 1;
        unsigned int periph_rstdis9_122m_lte_pdf : 1;
        unsigned int periph_rstdis9_122m_lte_pdt : 1;
        unsigned int periph_rstdis9_122m_tds_pdt : 1;
        unsigned int periph_rstdis9_245m_lte : 1;
        unsigned int periph_rstdis9_19m_lte_soc : 1;
        unsigned int periph_rstdis9_32k_lte : 1;
        unsigned int periph_rstdis9_31reserved : 19;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTDIS9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_245m_irm_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_245m_irm_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_491m_irm_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_491m_irm_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_wbbp_irm_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_wbbp_irm_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_104m_gbbp1_irm_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_104m_gbbp1_irm_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_104m_gbbp2_irm_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_104m_gbbp2_irm_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_axis_irm_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_axis_irm_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_axi_lte_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_axi_lte_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_lte_pdf_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_lte_pdf_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_lte_pdt_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_lte_pdt_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_tds_pdt_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_122m_tds_pdt_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_245m_lte_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_245m_lte_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_19m_lte_soc_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_19m_lte_soc_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_32k_lte_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_32k_lte_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_31reserved_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTDIS9_periph_rstdis9_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_rststat9_245m_irm : 1;
        unsigned int periph_rststat9_491m_irm : 1;
        unsigned int periph_rststat9_122m_wbbp_irm : 1;
        unsigned int periph_rststat9_104m_gbbp1_irm : 1;
        unsigned int periph_rststat9_104m_gbbp2_irm : 1;
        unsigned int periph_rststat9_axis_irm : 1;
        unsigned int periph_rststat9_axi_lte : 1;
        unsigned int periph_rststat9_122m_lte_pdf : 1;
        unsigned int periph_rststat9_122m_lte_pdt : 1;
        unsigned int periph_rststat9_122m_tds_pdt : 1;
        unsigned int periph_rststat9_245m_lte : 1;
        unsigned int periph_rststat9_19m_lte_soc : 1;
        unsigned int periph_rststat9_32k_lte : 1;
        unsigned int periph_rststat9_31reserved : 19;
    } reg;
} SOC_SCTRL_SC_PERIPH_RSTSTAT9_UNION;
#endif
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_245m_irm_START (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_245m_irm_END (0)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_491m_irm_START (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_491m_irm_END (1)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_wbbp_irm_START (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_wbbp_irm_END (2)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_104m_gbbp1_irm_START (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_104m_gbbp1_irm_END (3)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_104m_gbbp2_irm_START (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_104m_gbbp2_irm_END (4)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_axis_irm_START (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_axis_irm_END (5)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_axi_lte_START (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_axi_lte_END (6)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_lte_pdf_START (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_lte_pdf_END (7)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_lte_pdt_START (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_lte_pdt_END (8)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_tds_pdt_START (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_122m_tds_pdt_END (9)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_245m_lte_START (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_245m_lte_END (10)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_19m_lte_soc_START (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_19m_lte_soc_END (11)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_32k_lte_START (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_32k_lte_END (12)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_31reserved_START (13)
#define SOC_SCTRL_SC_PERIPH_RSTSTAT9_periph_rststat9_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_div : 10;
        unsigned int reserved_0 : 6;
        unsigned int portrait_landscape : 1;
        unsigned int lcd_3d_2d : 1;
        unsigned int g3d_raster_en : 1;
        unsigned int reserved_1 : 1;
        unsigned int lcd_3d_sw_inv : 4;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_SCTRL_SC_G3D_RASTER_UNION;
#endif
#define SOC_SCTRL_SC_G3D_RASTER_g3d_div_START (0)
#define SOC_SCTRL_SC_G3D_RASTER_g3d_div_END (9)
#define SOC_SCTRL_SC_G3D_RASTER_portrait_landscape_START (16)
#define SOC_SCTRL_SC_G3D_RASTER_portrait_landscape_END (16)
#define SOC_SCTRL_SC_G3D_RASTER_lcd_3d_2d_START (17)
#define SOC_SCTRL_SC_G3D_RASTER_lcd_3d_2d_END (17)
#define SOC_SCTRL_SC_G3D_RASTER_g3d_raster_en_START (18)
#define SOC_SCTRL_SC_G3D_RASTER_g3d_raster_en_END (18)
#define SOC_SCTRL_SC_G3D_RASTER_lcd_3d_sw_inv_START (20)
#define SOC_SCTRL_SC_G3D_RASTER_lcd_3d_sw_inv_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_lag : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_SCTRL_SC_TEMP0_LAG_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_LAG_temp0_lag_START (0)
#define SOC_SCTRL_SC_TEMP0_LAG_temp0_lag_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_0th : 8;
        unsigned int temp0_1th : 8;
        unsigned int temp0_2th : 8;
        unsigned int temp0_3th : 8;
    } reg;
} SOC_SCTRL_SC_TEMP0_TH_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_TH_temp0_0th_START (0)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_0th_END (7)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_1th_START (8)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_1th_END (15)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_2th_START (16)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_2th_END (23)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_3th_START (24)
#define SOC_SCTRL_SC_TEMP0_TH_temp0_3th_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_rst_th : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_TEMP0_RST_TH_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_RST_TH_temp0_rst_th_START (0)
#define SOC_SCTRL_SC_TEMP0_RST_TH_temp0_rst_th_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_trim_raw : 4;
        unsigned int temp0_ct_sel_raw : 2;
        unsigned int reserved_0 : 6;
        unsigned int temp0_test_raw : 8;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_SCTRL_SC_TEMP0_CFG_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_trim_raw_START (0)
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_trim_raw_END (3)
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_ct_sel_raw_START (4)
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_ct_sel_raw_END (5)
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_test_raw_START (12)
#define SOC_SCTRL_SC_TEMP0_CFG_temp0_test_raw_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_en_raw : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_EN_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_EN_temp0_en_raw_START (0)
#define SOC_SCTRL_SC_TEMP0_EN_temp0_en_raw_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_int_msk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_INT_MSK_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_INT_MSK_temp0_int_msk_START (0)
#define SOC_SCTRL_SC_TEMP0_INT_MSK_temp0_int_msk_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_int_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_INT_CLR_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_INT_CLR_temp0_int_clr_START (0)
#define SOC_SCTRL_SC_TEMP0_INT_CLR_temp0_int_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_rst_msk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_RST_MSK_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_RST_MSK_temp0_rst_msk_START (0)
#define SOC_SCTRL_SC_TEMP0_RST_MSK_temp0_rst_msk_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_rawint : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_RAW_INT_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_RAW_INT_temp0_rawint_START (0)
#define SOC_SCTRL_SC_TEMP0_RAW_INT_temp0_rawint_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_mskint : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP0_MSK_INT_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_MSK_INT_temp0_mskint_START (0)
#define SOC_SCTRL_SC_TEMP0_MSK_INT_temp0_mskint_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp0_out_s : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_TEMP0_VALUE_UNION;
#endif
#define SOC_SCTRL_SC_TEMP0_VALUE_temp0_out_s_START (0)
#define SOC_SCTRL_SC_TEMP0_VALUE_temp0_out_s_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_lag : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_SCTRL_SC_TEMP1_LAG_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_LAG_temp1_lag_START (0)
#define SOC_SCTRL_SC_TEMP1_LAG_temp1_lag_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_0th : 8;
        unsigned int temp1_1th : 8;
        unsigned int temp1_2th : 8;
        unsigned int temp1_3th : 8;
    } reg;
} SOC_SCTRL_SC_TEMP1_TH_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_TH_temp1_0th_START (0)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_0th_END (7)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_1th_START (8)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_1th_END (15)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_2th_START (16)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_2th_END (23)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_3th_START (24)
#define SOC_SCTRL_SC_TEMP1_TH_temp1_3th_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_rst_th : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_TEMP1_RST_TH_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_RST_TH_temp1_rst_th_START (0)
#define SOC_SCTRL_SC_TEMP1_RST_TH_temp1_rst_th_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_trim_raw : 4;
        unsigned int temp1_ct_sel_raw : 2;
        unsigned int reserved_0 : 6;
        unsigned int temp1_test_raw : 8;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_SCTRL_SC_TEMP1_CFG_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_trim_raw_START (0)
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_trim_raw_END (3)
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_ct_sel_raw_START (4)
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_ct_sel_raw_END (5)
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_test_raw_START (12)
#define SOC_SCTRL_SC_TEMP1_CFG_temp1_test_raw_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_en_raw : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_EN_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_EN_temp1_en_raw_START (0)
#define SOC_SCTRL_SC_TEMP1_EN_temp1_en_raw_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_int_msk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_INT_MSK_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_INT_MSK_temp1_int_msk_START (0)
#define SOC_SCTRL_SC_TEMP1_INT_MSK_temp1_int_msk_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_int_clr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_INT_CLR_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_INT_CLR_temp1_int_clr_START (0)
#define SOC_SCTRL_SC_TEMP1_INT_CLR_temp1_int_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_rst_msk : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_RST_MSK_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_RST_MSK_temp1_rst_msk_START (0)
#define SOC_SCTRL_SC_TEMP1_RST_MSK_temp1_rst_msk_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_rawint : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_RAW_INT_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_RAW_INT_temp1_rawint_START (0)
#define SOC_SCTRL_SC_TEMP1_RAW_INT_temp1_rawint_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_mskint : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SCTRL_SC_TEMP1_MSK_INT_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_MSK_INT_temp1_mskint_START (0)
#define SOC_SCTRL_SC_TEMP1_MSK_INT_temp1_mskint_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int temp1_out_s : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SCTRL_SC_TEMP1_VALUE_UNION;
#endif
#define SOC_SCTRL_SC_TEMP1_VALUE_temp1_out_s_START (0)
#define SOC_SCTRL_SC_TEMP1_VALUE_temp1_out_s_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int sel_clk_uart1 : 1;
        unsigned int sel_clk_uart2 : 1;
        unsigned int sel_clk_uart3 : 1;
        unsigned int sel_clk_uart4 : 1;
        unsigned int sel_clk_uart5 : 1;
        unsigned int sel_clk_uart6 : 1;
        unsigned int reserved_1 : 9;
        unsigned int reserved_2 : 1;
        unsigned int sel_clk_uart1_msk : 1;
        unsigned int sel_clk_uart2_msk : 1;
        unsigned int sel_clk_uart3_msk : 1;
        unsigned int sel_clk_uart4_msk : 1;
        unsigned int sel_clk_uart5_msk : 1;
        unsigned int sel_clk_uart6_msk : 1;
        unsigned int reserved_3 : 9;
    } reg;
} SOC_SCTRL_SC_CLK_SEL0_UNION;
#endif
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_START (1)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_END (1)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_START (2)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_END (2)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_START (3)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_END (3)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_START (4)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_END (4)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_START (5)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_END (5)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_START (6)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_END (6)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_START (17)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart1_msk_END (17)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_START (18)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart2_msk_END (18)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_START (19)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart3_msk_END (19)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_START (20)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart4_msk_END (20)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_START (21)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart5_msk_END (21)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_START (22)
#define SOC_SCTRL_SC_CLK_SEL0_sel_clk_uart6_msk_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_clk_pwm0 : 1;
        unsigned int sel_clk_pwm1 : 1;
        unsigned int sel_clk_24m_0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 9;
        unsigned int sel_clk_pll_1_test1 : 1;
        unsigned int sel_clk_pll_1_test0 : 1;
        unsigned int sel_clk_pll_0_test : 1;
        unsigned int sel_clk_pwm0_msk : 1;
        unsigned int sel_clk_pwm1_msk : 1;
        unsigned int sel_clk_24m_0_msk : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 9;
        unsigned int sel_clk_pll_1_test1_msk : 1;
        unsigned int sel_clk_pll_1_test0_msk : 1;
        unsigned int sel_clk_pll_0_test_msk : 1;
    } reg;
} SOC_SCTRL_SC_CLK_SEL1_UNION;
#endif
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_START (0)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_END (0)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_START (1)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_END (1)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_24m_0_START (2)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_24m_0_END (2)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test1_START (13)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test1_END (13)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test0_START (14)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test0_END (14)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_0_test_START (15)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_0_test_END (15)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_START (16)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm0_msk_END (16)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_START (17)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pwm1_msk_END (17)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_24m_0_msk_START (18)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_24m_0_msk_END (18)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test1_msk_START (29)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test1_msk_END (29)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test0_msk_START (30)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_1_test0_msk_END (30)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_0_test_msk_START (31)
#define SOC_SCTRL_SC_CLK_SEL1_sel_clk_pll_0_test_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_all_cfg0_7xfs : 8;
        unsigned int clk_all_cfg0_15clk : 8;
        unsigned int clk_all_cfg0_16i2spcm : 1;
        unsigned int clk_all_cfg0_17sio0 : 1;
        unsigned int clk_all_cfg0_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL0_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_7xfs_START (0)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_7xfs_END (7)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_15clk_START (8)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_15clk_END (15)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_16i2spcm_START (16)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_16i2spcm_END (16)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_17sio0_START (17)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_17sio0_END (17)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_31reserved_START (18)
#define SOC_SCTRL_SC_CLKCFGALL0_clk_all_cfg0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_all_cfg1_7xfs : 8;
        unsigned int clk_all_cfg1_15clk : 8;
        unsigned int clk_all_cfg1_16i2spcm : 1;
        unsigned int clk_all_cfg1_17sio1 : 1;
        unsigned int clk_all_cfg1_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL1_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_7xfs_START (0)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_7xfs_END (7)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_15clk_START (8)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_15clk_END (15)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_16i2spcm_START (16)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_16i2spcm_END (16)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_17sio1_START (17)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_17sio1_END (17)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_31reserved_START (18)
#define SOC_SCTRL_SC_CLKCFGALL1_clk_all_cfg1_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_all_cfg2_7xfs : 8;
        unsigned int clk_all_cfg2_15clk : 8;
        unsigned int clk_all_cfg2_16i2spcm : 1;
        unsigned int clk_all_cfg2_17sio2 : 1;
        unsigned int clk_all_cfg2_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL2_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_7xfs_START (0)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_7xfs_END (7)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_15clk_START (8)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_15clk_END (15)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_16i2spcm_START (16)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_16i2spcm_END (16)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_17sio2_START (17)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_17sio2_END (17)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_31reserved_START (18)
#define SOC_SCTRL_SC_CLKCFGALL2_clk_all_cfg2_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int divfrac_sio : 24;
        unsigned int clk_all_cfg3_31reserved : 8;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL3_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL3_divfrac_sio_START (0)
#define SOC_SCTRL_SC_CLKCFGALL3_divfrac_sio_END (23)
#define SOC_SCTRL_SC_CLKCFGALL3_clk_all_cfg3_31reserved_START (24)
#define SOC_SCTRL_SC_CLKCFGALL3_clk_all_cfg3_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int divfrac_49m : 24;
        unsigned int div_value_bbppll_24m : 6;
        unsigned int clk_all_cfg4 : 2;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL4_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_START (0)
#define SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_END (23)
#define SOC_SCTRL_SC_CLKCFGALL4_div_value_bbppll_24m_START (24)
#define SOC_SCTRL_SC_CLKCFGALL4_div_value_bbppll_24m_END (29)
#define SOC_SCTRL_SC_CLKCFGALL4_clk_all_cfg4_START (30)
#define SOC_SCTRL_SC_CLKCFGALL4_clk_all_cfg4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_all_cfg5_7xfs : 8;
        unsigned int clk_all_cfg5_15clk : 8;
        unsigned int clk_all_cfg5_16i2spcm : 1;
        unsigned int clk_all_cfg5_17sio3 : 1;
        unsigned int clk_all_cfg5_31reserved : 14;
    } reg;
} SOC_SCTRL_SC_CLKCFGALL5_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_7xfs_START (0)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_7xfs_END (7)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_15clk_START (8)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_15clk_END (15)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_16i2spcm_START (16)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_16i2spcm_END (16)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_17sio3_START (17)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_17sio3_END (17)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_31reserved_START (18)
#define SOC_SCTRL_SC_CLKCFGALL5_clk_all_cfg5_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg0_value0 : 7;
        unsigned int clk_8bit_cfg0_vld0 : 1;
        unsigned int clk_8bit_cfg0_value1 : 7;
        unsigned int clk_8bit_cfg0_vld1 : 1;
        unsigned int clk_8bit_cfg0_value2 : 7;
        unsigned int clk_8bit_cfg0_vld2 : 1;
        unsigned int clk_8bit_cfg0_value3 : 7;
        unsigned int clk_8bit_cfg0_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT0_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT0_clk_8bit_cfg0_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg1_value0 : 7;
        unsigned int clk_8bit_cfg1_vld0 : 1;
        unsigned int clk_8bit_cfg1_value1 : 7;
        unsigned int clk_8bit_cfg1_vld1 : 1;
        unsigned int clk_8bit_cfg1_value2 : 7;
        unsigned int clk_8bit_cfg1_vld2 : 1;
        unsigned int clk_8bit_cfg1_value3 : 7;
        unsigned int clk_8bit_cfg1_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT1_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT1_clk_8bit_cfg1_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg2_value0 : 7;
        unsigned int clk_8bit_cfg2_vld0 : 1;
        unsigned int clk_8bit_cfg2_value1 : 7;
        unsigned int clk_8bit_cfg2_vld1 : 1;
        unsigned int clk_8bit_cfg2_value2 : 7;
        unsigned int clk_8bit_cfg2_vld2 : 1;
        unsigned int clk_8bit_cfg2_value3 : 7;
        unsigned int clk_8bit_cfg2_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT2_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT2_clk_8bit_cfg2_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg3_value0 : 7;
        unsigned int clk_8bit_cfg3_vld0 : 1;
        unsigned int clk_8bit_cfg3_value1 : 7;
        unsigned int clk_8bit_cfg3_vld1 : 1;
        unsigned int clk_8bit_cfg3_value2 : 7;
        unsigned int clk_8bit_cfg3_vld2 : 1;
        unsigned int clk_8bit_cfg3_value3 : 7;
        unsigned int clk_8bit_cfg3_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT3_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT3_clk_8bit_cfg3_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg4_value0 : 7;
        unsigned int clk_8bit_cfg4_vld0 : 1;
        unsigned int clk_8bit_cfg4_value1 : 7;
        unsigned int clk_8bit_cfg4_vld1 : 1;
        unsigned int clk_8bit_cfg4_value2 : 7;
        unsigned int clk_8bit_cfg4_vld2 : 1;
        unsigned int clk_8bit_cfg4_value3 : 7;
        unsigned int clk_8bit_cfg4_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT4_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT4_clk_8bit_cfg4_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg5_value0 : 7;
        unsigned int clk_8bit_cfg5_vld0 : 1;
        unsigned int clk_8bit_cfg5_value1 : 7;
        unsigned int clk_8bit_cfg5_vld1 : 1;
        unsigned int clk_8bit_cfg5_value2 : 7;
        unsigned int clk_8bit_cfg5_vld2 : 1;
        unsigned int clk_8bit_cfg5_value3 : 7;
        unsigned int clk_8bit_cfg5_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT5_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT5_clk_8bit_cfg5_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg6_value0 : 7;
        unsigned int clk_8bit_cfg6_vld0 : 1;
        unsigned int clk_8bit_cfg6_value1 : 7;
        unsigned int clk_8bit_cfg6_vld1 : 1;
        unsigned int clk_8bit_cfg6_value2 : 7;
        unsigned int clk_8bit_cfg6_vld2 : 1;
        unsigned int clk_8bit_cfg6_value3 : 7;
        unsigned int clk_8bit_cfg6_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT6_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT6_clk_8bit_cfg6_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg7_value0 : 7;
        unsigned int clk_8bit_cfg7_vld0 : 1;
        unsigned int clk_8bit_cfg7_value1 : 7;
        unsigned int clk_8bit_cfg7_vld1 : 1;
        unsigned int clk_8bit_cfg7_value2 : 7;
        unsigned int clk_8bit_cfg7_vld2 : 1;
        unsigned int clk_8bit_cfg7_value3 : 7;
        unsigned int clk_8bit_cfg7_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT7_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT7_clk_8bit_cfg7_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg8_value0 : 7;
        unsigned int clk_8bit_cfg8_vld0 : 1;
        unsigned int clk_8bit_cfg8_value1 : 7;
        unsigned int clk_8bit_cfg8_vld1 : 1;
        unsigned int clk_8bit_cfg8_value2 : 7;
        unsigned int clk_8bit_cfg8_vld2 : 1;
        unsigned int clk_8bit_cfg8_value3 : 7;
        unsigned int clk_8bit_cfg8_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT8_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT8_clk_8bit_cfg8_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg9_value0 : 7;
        unsigned int clk_8bit_cfg9_vld0 : 1;
        unsigned int clk_8bit_cfg9_value1 : 7;
        unsigned int clk_8bit_cfg9_vld1 : 1;
        unsigned int clk_8bit_cfg9_value2 : 7;
        unsigned int clk_8bit_cfg9_vld2 : 1;
        unsigned int clk_8bit_cfg9_value3 : 7;
        unsigned int clk_8bit_cfg9_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT9_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT9_clk_8bit_cfg9_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_8bit_cfg10_value0 : 7;
        unsigned int clk_8bit_cfg10_vld0 : 1;
        unsigned int clk_8bit_cfg10_value1 : 7;
        unsigned int clk_8bit_cfg10_vld1 : 1;
        unsigned int clk_8bit_cfg10_value2 : 7;
        unsigned int clk_8bit_cfg10_vld2 : 1;
        unsigned int clk_8bit_cfg10_value3 : 7;
        unsigned int clk_8bit_cfg10_vld3 : 1;
    } reg;
} SOC_SCTRL_SC_CLKCFG8BIT10_UNION;
#endif
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_START (0)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value0_END (6)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld0_START (7)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld0_END (7)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_START (8)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value1_END (14)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld1_START (15)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld1_END (15)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value2_START (16)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value2_END (22)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld2_START (23)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld2_END (23)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value3_START (24)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_value3_END (30)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld3_START (31)
#define SOC_SCTRL_SC_CLKCFG8BIT10_clk_8bit_cfg10_vld3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat0_dmaaxi_dlock_irq : 1;
        unsigned int sc_bus_stat0_dmaaxi_dlock_wr : 1;
        unsigned int sc_bus_stat0_2reserved : 2;
        unsigned int sc_bus_stat0_dmaaxi_dlock_id : 6;
        unsigned int sc_bus_stat0_15reserved : 6;
        unsigned int sc_bus_stat0_dmaaxi_dlock_slv : 1;
        unsigned int sc_bus_stat0_23reserved : 7;
        unsigned int sc_bus_stat0_dmaaxi_dlock_mst : 2;
        unsigned int sc_bus_stat0_lock : 6;
    } reg;
} SOC_SCTRL_SC_BUS_STAT0_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_id_END (9)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_15reserved_START (10)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_slv_END (16)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_23reserved_START (17)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_dmaaxi_dlock_mst_END (25)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_lock_START (26)
#define SOC_SCTRL_SC_BUS_STAT0_sc_bus_stat0_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat1_gpuaxi_dlock_irq : 1;
        unsigned int sc_bus_stat1_gpuaxi_dlock_wr : 1;
        unsigned int sc_bus_stat1_2reserved : 2;
        unsigned int sc_bus_stat1_gpuaxi_dlock_id : 5;
        unsigned int sc_bus_stat1_15reserved : 7;
        unsigned int sc_bus_stat1_gpuaxi_dlock_slv : 1;
        unsigned int sc_bus_stat1_23reserved : 7;
        unsigned int sc_bus_stat1_gpuaxi_dlock_mst : 1;
        unsigned int sc_bus_stat1_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT1_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_id_END (8)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_15reserved_START (9)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_slv_END (16)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_23reserved_START (17)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_gpuaxi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT1_sc_bus_stat1_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat1_mocmaxi_dlock_irq : 1;
        unsigned int sc_bus_stat1_mocmaxi_dlock_wr : 1;
        unsigned int sc_bus_stat1_2reserved : 2;
        unsigned int sc_bus_stat1_mocmaxi_dlock_id : 8;
        unsigned int sc_bus_stat1_15reserved : 4;
        unsigned int sc_bus_stat1_mocmaxi_dlock_slv : 2;
        unsigned int sc_bus_stat1_23reserved : 6;
        unsigned int sc_bus_stat1_mocmaxi_dlock_mst : 1;
        unsigned int sc_bus_stat2_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT2_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_id_END (11)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_15reserved_START (12)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_slv_END (17)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_23reserved_START (18)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat1_mocmaxi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat2_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT2_sc_bus_stat2_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat3_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT3_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT3_sc_bus_stat3_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT3_sc_bus_stat3_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat4_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT4_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT4_sc_bus_stat4_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT4_sc_bus_stat4_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat1_acpucfgaxi_dlock_irq : 1;
        unsigned int sc_bus_stat1_acpucfgaxi_dlock_wr : 1;
        unsigned int sc_bus_stat1_2reserved : 2;
        unsigned int sc_bus_stat1_acpucfgaxi_dlock_id : 8;
        unsigned int sc_bus_stat1_15reserved : 4;
        unsigned int sc_bus_stat1_acpucfgaxi_dlock_slv : 1;
        unsigned int sc_bus_stat1_23reserved : 7;
        unsigned int sc_bus_stat1_acpucfgaxi_dlock_mst : 1;
        unsigned int sc_bus_stat5_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT5_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_id_END (11)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_15reserved_START (12)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_slv_END (16)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_23reserved_START (17)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat1_acpucfgaxi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat5_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT5_sc_bus_stat5_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat1_acpum0axi_dlock_irq : 1;
        unsigned int sc_bus_stat1_acpum0axi_dlock_wr : 1;
        unsigned int sc_bus_stat1_2reserved : 2;
        unsigned int sc_bus_stat1_acpum0axi_dlock_id : 8;
        unsigned int sc_bus_stat1_15reserved : 4;
        unsigned int sc_bus_stat1_acpum0axi_dlock_slv : 2;
        unsigned int sc_bus_stat1_23reserved : 6;
        unsigned int sc_bus_stat1_acpum0axi_dlock_mst : 1;
        unsigned int sc_bus_stat6_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT6_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_id_END (11)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_15reserved_START (12)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_slv_END (17)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_23reserved_START (18)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat1_acpum0axi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat6_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT6_sc_bus_stat6_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat1_acpum1axi_dlock_irq : 1;
        unsigned int sc_bus_stat1_acpum1axi_dlock_wr : 1;
        unsigned int sc_bus_stat1_2reserved : 2;
        unsigned int sc_bus_stat1_acpum1axi_dlock_id : 8;
        unsigned int sc_bus_stat1_15reserved : 4;
        unsigned int sc_bus_stat1_acpum1axi_dlock_slv : 2;
        unsigned int sc_bus_stat1_23reserved : 6;
        unsigned int sc_bus_stat1_acpum1axi_dlock_mst : 1;
        unsigned int sc_bus_stat7_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT7_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_id_END (11)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_15reserved_START (12)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_slv_END (17)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_23reserved_START (18)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat1_acpum1axi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat7_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT7_sc_bus_stat7_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat8_apcfgaxi_dlock_irq : 1;
        unsigned int sc_bus_stat8_apcfgaxi_dlock_wr : 1;
        unsigned int sc_bus_stat8_2reserved : 2;
        unsigned int sc_bus_stat8_apcfgaxi_dlock_id : 12;
        unsigned int sc_bus_stat8_apcfgaxi_dlock_slv : 4;
        unsigned int sc_bus_stat8_23reserved : 4;
        unsigned int sc_bus_stat8_apcfgaxi_dlock_mst : 1;
        unsigned int sc_bus_stat8_lock : 7;
    } reg;
} SOC_SCTRL_SC_BUS_STAT8_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_id_END (15)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_slv_END (19)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_23reserved_START (20)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_apcfgaxi_dlock_mst_END (24)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_lock_START (25)
#define SOC_SCTRL_SC_BUS_STAT8_sc_bus_stat8_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat0_imgaxi_dlock_irq : 1;
        unsigned int sc_bus_stat0_imgaxi_dlock_wr : 1;
        unsigned int sc_bus_stat0_2reserved : 2;
        unsigned int sc_bus_stat0_imgaxi_dlock_id : 5;
        unsigned int sc_bus_stat0_15reserved : 7;
        unsigned int sc_bus_stat0_imgaxi_dlock_slv : 1;
        unsigned int sc_bus_stat0_23reserved : 7;
        unsigned int sc_bus_stat0_imgaxi_dlock_mst : 2;
        unsigned int sc_bus_stat9_lock : 6;
    } reg;
} SOC_SCTRL_SC_BUS_STAT9_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_irq_START (0)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_irq_END (0)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_wr_START (1)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_wr_END (1)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_2reserved_START (2)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_2reserved_END (3)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_id_START (4)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_id_END (8)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_15reserved_START (9)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_15reserved_END (15)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_slv_START (16)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_slv_END (16)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_23reserved_START (17)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_23reserved_END (23)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_mst_START (24)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat0_imgaxi_dlock_mst_END (25)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat9_lock_START (26)
#define SOC_SCTRL_SC_BUS_STAT9_sc_bus_stat9_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat10_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT10_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT10_sc_bus_stat10_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT10_sc_bus_stat10_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat11_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT11_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT11_sc_bus_stat11_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT11_sc_bus_stat11_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat12_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT12_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT12_sc_bus_stat12_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT12_sc_bus_stat12_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat13_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT13_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT13_sc_bus_stat13_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT13_sc_bus_stat13_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat14_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT14_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT14_sc_bus_stat14_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT14_sc_bus_stat14_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_bus_stat15_lock : 32;
    } reg;
} SOC_SCTRL_SC_BUS_STAT15_UNION;
#endif
#define SOC_SCTRL_SC_BUS_STAT15_sc_bus_stat15_lock_START (0)
#define SOC_SCTRL_SC_BUS_STAT15_sc_bus_stat15_lock_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_EN_STAT1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_STATR1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_STATM1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_CLEAR1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_EN1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 8;
        unsigned int reserved_1: 8;
        unsigned int reserved_2: 8;
        unsigned int reserved_3: 8;
    } reg;
} SOC_SCTRL_SC_INT_DIS1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_EN_STAT2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_STATR2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_STATM2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_CLEAR2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_EN2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 31;
    } reg;
} SOC_SCTRL_SC_INT_DIS2_UNION;
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

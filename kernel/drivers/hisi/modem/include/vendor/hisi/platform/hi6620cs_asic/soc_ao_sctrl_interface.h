#ifndef __SOC_AO_SCTRL_INTERFACE_H__
#define __SOC_AO_SCTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_AO_SCTRL_SC_SYS_CTRL0_ADDR(base) ((base) + (0x000))
#define SOC_AO_SCTRL_SC_SYS_CTRL1_ADDR(base) ((base) + (0x004))
#define SOC_AO_SCTRL_SC_SYS_CTRL2_ADDR(base) ((base) + (0x008))
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_ADDR(base) ((base) + (0x00C))
#define SOC_AO_SCTRL_SC_SYS_STAT0_ADDR(base) ((base) + (0x010))
#define SOC_AO_SCTRL_SC_SYS_STAT1_ADDR(base) ((base) + (0x014))
#define SOC_AO_SCTRL_SC_MCU_IMCTRL_ADDR(base) ((base) + (0x018))
#define SOC_AO_SCTRL_SC_MCU_IMSTAT_ADDR(base) ((base) + (0x01C))
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_ADDR(base) ((base) + (0x020))
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_ADDR(base) ((base) + (0x024))
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_ADDR(base) ((base) + (0x028))
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_ADDR(base) ((base) + (0x02C))
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_ADDR(base) ((base) + (0x030))
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_ADDR(base) ((base) + (0x040))
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_ADDR(base) ((base) + (0x044))
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_ADDR(base) ((base) + (0x048))
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_ADDR(base) ((base) + (0x04C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_ADDR(base) ((base) + (0x054))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_ADDR(base) ((base) + (0x058))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_ADDR(base) ((base) + (0x05C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_ADDR(base) ((base) + (0x064))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_ADDR(base) ((base) + (0x068))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_ADDR(base) ((base) + (0x06C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_ADDR(base) ((base) + (0x074))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_ADDR(base) ((base) + (0x078))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_ADDR(base) ((base) + (0x07C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_ADDR(base) ((base) + (0x084))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_ADDR(base) ((base) + (0x088))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_ADDR(base) ((base) + (0x08C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_ADDR(base) ((base) + (0x094))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_ADDR(base) ((base) + (0x098))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_ADDR(base) ((base) + (0x09C))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_ADDR(base) ((base) + (0x0A8))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_ADDR(base) ((base) + (0x0AC))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_ADDR(base) ((base) + (0x0B0))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_ADDR(base) ((base) + (0x0B4))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_ADDR(base) ((base) + (0x0B8))
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_ADDR(base) ((base) + (0x0BC))
#define SOC_AO_SCTRL_SC_INT_EN_STAT_ADDR(base) ((base) + (0x0C0))
#define SOC_AO_SCTRL_SC_INT_STATR_ADDR(base) ((base) + (0x0C4))
#define SOC_AO_SCTRL_SC_INT_STATM_ADDR(base) ((base) + (0x0C8))
#define SOC_AO_SCTRL_SC_INT_CLEAR_ADDR(base) ((base) + (0x0CC))
#define SOC_AO_SCTRL_SC_INT_EN0_ADDR(base) ((base) + (0x0D0))
#define SOC_AO_SCTRL_SC_INT_DIS0_ADDR(base) ((base) + (0x0D4))
#define SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_ADDR(base) ((base) + (0x114))
#define SOC_AO_SCTRL_SC_TIMER_EN0_ADDR(base) ((base) + (0x1D0))
#define SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(base) ((base) + (0x1D4))
#define SOC_AO_SCTRL_SC_TIMER_EN2_ADDR(base) ((base) + (0x1E0))
#define SOC_AO_SCTRL_SC_TIMER_EN3_ADDR(base) ((base) + (0x1E4))
#define SOC_AO_SCTRL_SC_TIMER_EN4_ADDR(base) ((base) + (0x1F0))
#define SOC_AO_SCTRL_SC_TIMER_EN5_ADDR(base) ((base) + (0x1F4))
#define SOC_AO_SCTRL_SC_PWUP_TIME12_ADDR(base) ((base) + (0x340))
#define SOC_AO_SCTRL_SC_PWUP_TIME13_ADDR(base) ((base) + (0x344))
#define SOC_AO_SCTRL_SC_PWUP_TIME14_ADDR(base) ((base) + (0x348))
#define SOC_AO_SCTRL_SC_PWUP_TIME15_ADDR(base) ((base) + (0x34C))
#define SOC_AO_SCTRL_SC_PWUP_TIME16_ADDR(base) ((base) + (0x350))
#define SOC_AO_SCTRL_SC_PWUP_TIME17_ADDR(base) ((base) + (0x354))
#define SOC_AO_SCTRL_SC_RESERVED31_ADDR(base) ((base) + (0x3A0))
#define SOC_AO_SCTRL_SC_RESERVED32_ADDR(base) ((base) + (0x3A4))
#define SOC_AO_SCTRL_SC_RESERVED33_ADDR(base) ((base) + (0x3A8))
#define SOC_AO_SCTRL_SC_RESERVED34_ADDR(base) ((base) + (0x3AC))
#define SOC_AO_SCTRL_SC_RESERVED35_ADDR(base) ((base) + (0x3B0))
#define SOC_AO_SCTRL_SC_RESERVED36_ADDR(base) ((base) + (0x3B4))
#define SOC_AO_SCTRL_SC_RESERVED37_ADDR(base) ((base) + (0x3B8))
#define SOC_AO_SCTRL_SC_RESERVED38_ADDR(base) ((base) + (0x3BC))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL0_ADDR(base) ((base) + (0x400))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_ADDR(base) ((base) + (0x404))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL2_ADDR(base) ((base) + (0x408))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_ADDR(base) ((base) + (0x40C))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_ADDR(base) ((base) + (0x410))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_ADDR(base) ((base) + (0x414))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_ADDR(base) ((base) + (0x418))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_ADDR(base) ((base) + (0x41C))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_ADDR(base) ((base) + (0x440))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT1_ADDR(base) ((base) + (0x444))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT2_ADDR(base) ((base) + (0x448))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT3_ADDR(base) ((base) + (0x44C))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_ADDR(base) ((base) + (0x450))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT5_ADDR(base) ((base) + (0x454))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT6_ADDR(base) ((base) + (0x458))
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_ADDR(base) ((base) + (0x45C))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_ADDR(base) ((base) + (0x480))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_ADDR(base) ((base) + (0x484))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL2_ADDR(base) ((base) + (0x488))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_ADDR(base) ((base) + (0x48C))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ADDR(base) ((base) + (0x490))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_ADDR(base) ((base) + (0x494))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL6_ADDR(base) ((base) + (0x498))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL7_ADDR(base) ((base) + (0x49C))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_ADDR(base) ((base) + (0x4A0))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_ADDR(base) ((base) + (0x4A4))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_ADDR(base) ((base) + (0x4A8))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_ADDR(base) ((base) + (0x4AC))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_ADDR(base) ((base) + (0x4C0))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_ADDR(base) ((base) + (0x4C4))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_ADDR(base) ((base) + (0x4C8))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_ADDR(base) ((base) + (0x4CC))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT4_ADDR(base) ((base) + (0x4D0))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT5_ADDR(base) ((base) + (0x4D4))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_ADDR(base) ((base) + (0x4D8))
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_ADDR(base) ((base) + (0x4DC))
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(base) ((base) + (0x630))
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_ADDR(base) ((base) + (0x634))
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_ADDR(base) ((base) + (0x638))
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_ADDR(base) ((base) + (0x63C))
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_ADDR(base) ((base) + (0x640))
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_ADDR(base) ((base) + (0x644))
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_ADDR(base) ((base) + (0x648))
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_ADDR(base) ((base) + (0x64C))
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_ADDR(base) ((base) + (0x650))
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN7_ADDR(base) ((base) + (0x654))
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS7_ADDR(base) ((base) + (0x658))
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT7_ADDR(base) ((base) + (0x65C))
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_ADDR(base) ((base) + (0x6F0))
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_ADDR(base) ((base) + (0x6F4))
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_ADDR(base) ((base) + (0x6F8))
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN5_ADDR(base) ((base) + (0x6FC))
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS5_ADDR(base) ((base) + (0x700))
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT5_ADDR(base) ((base) + (0x704))
#define SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(base) ((base) + (0x800))
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(base) ((base) + (0x804))
#define SOC_AO_SCTRL_SC_PW_CLKEN1_ADDR(base) ((base) + (0x808))
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_ADDR(base) ((base) + (0x80C))
#define SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(base) ((base) + (0x810))
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(base) ((base) + (0x814))
#define SOC_AO_SCTRL_SC_PW_RSTEN1_ADDR(base) ((base) + (0x818))
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_ADDR(base) ((base) + (0x81C))
#define SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(base) ((base) + (0x820))
#define SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(base) ((base) + (0x824))
#define SOC_AO_SCTRL_SC_PW_ISOEN1_ADDR(base) ((base) + (0x828))
#define SOC_AO_SCTRL_SC_PW_ISODIS1_ADDR(base) ((base) + (0x82C))
#define SOC_AO_SCTRL_SC_PW_EN0_ADDR(base) ((base) + (0x830))
#define SOC_AO_SCTRL_SC_PW_DIS0_ADDR(base) ((base) + (0x834))
#define SOC_AO_SCTRL_SC_PW_EN1_ADDR(base) ((base) + (0x838))
#define SOC_AO_SCTRL_SC_PW_DIS1_ADDR(base) ((base) + (0x83C))
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_ADDR(base) ((base) + (0x840))
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_ADDR(base) ((base) + (0x844))
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_ADDR(base) ((base) + (0x848))
#define SOC_AO_SCTRL_SC_PW_STAT0_ADDR(base) ((base) + (0x850))
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(base) ((base) + (0x854))
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_ADDR(base) ((base) + (0x858))
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(base) ((base) + (0x85C))
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_ADDR(base) ((base) + (0x860))
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(base) ((base) + (0x864))
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_ADDR(base) ((base) + (0x868))
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(base) ((base) + (0x86C))
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_ADDR(base) ((base) + (0x870))
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_ADDR(base) ((base) + (0x874))
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_ADDR(base) ((base) + (0x878))
#define SOC_AO_SCTRL_SC_PWUP_TIME0_ADDR(base) ((base) + (0x880))
#define SOC_AO_SCTRL_SC_PWUP_TIME1_ADDR(base) ((base) + (0x884))
#define SOC_AO_SCTRL_SC_PWUP_TIME2_ADDR(base) ((base) + (0x888))
#define SOC_AO_SCTRL_SC_PWUP_TIME3_ADDR(base) ((base) + (0x88C))
#define SOC_AO_SCTRL_SC_PWUP_TIME4_ADDR(base) ((base) + (0x890))
#define SOC_AO_SCTRL_SC_PWUP_TIME5_ADDR(base) ((base) + (0x894))
#define SOC_AO_SCTRL_SC_PWUP_TIME6_ADDR(base) ((base) + (0x898))
#define SOC_AO_SCTRL_SC_PWUP_TIME7_ADDR(base) ((base) + (0x89C))
#define SOC_AO_SCTRL_SC_PWUP_TIME8_ADDR(base) ((base) + (0x8A0))
#define SOC_AO_SCTRL_SC_PWUP_TIME9_ADDR(base) ((base) + (0x8A4))
#define SOC_AO_SCTRL_SC_PWUP_TIME10_ADDR(base) ((base) + (0x8A8))
#define SOC_AO_SCTRL_SC_PWUP_TIME11_ADDR(base) ((base) + (0x8AC))
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_ADDR(base) ((base) + (0x8B0))
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_ADDR(base) ((base) + (0x8B4))
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_ADDR(base) ((base) + (0x8B8))
#define SOC_AO_SCTRL_SC_PW_CTRL_ADDR(base) ((base) + (0x8CC))
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_ADDR(base) ((base) + (0x8D0))
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_ADDR(base) ((base) + (0x8D4))
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_ADDR(base) ((base) + (0x8D8))
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK0_ADDR(base) ((base) + (0x8E0))
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK1_ADDR(base) ((base) + (0x8E4))
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_MSK_ADDR(base) ((base) + (0x8E8))
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT1_MSK_ADDR(base) ((base) + (0x8EC))
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_ADDR(base) ((base) + (0x8F0))
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_ADDR(base) ((base) + (0x8F4))
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_ADDR(base) ((base) + (0x8F8))
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK0_ADDR(base) ((base) + (0x900))
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK1_ADDR(base) ((base) + (0x904))
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_MSK_ADDR(base) ((base) + (0x908))
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT1_MSK_ADDR(base) ((base) + (0x90C))
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_ADDR(base) ((base) + (0x910))
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_ADDR(base) ((base) + (0x914))
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_ADDR(base) ((base) + (0x918))
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK0_ADDR(base) ((base) + (0x920))
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK1_ADDR(base) ((base) + (0x924))
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_MSK_ADDR(base) ((base) + (0x928))
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT1_MSK_ADDR(base) ((base) + (0x92C))
#define SOC_AO_SCTRL_SC_MCU_VOTEEN0_ADDR(base) ((base) + (0x930))
#define SOC_AO_SCTRL_SC_MCU_VOTEDIS0_ADDR(base) ((base) + (0x934))
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_ADDR(base) ((base) + (0x938))
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK0_ADDR(base) ((base) + (0x940))
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK1_ADDR(base) ((base) + (0x944))
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_MSK_ADDR(base) ((base) + (0x948))
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT1_MSK_ADDR(base) ((base) + (0x94C))
#define SOC_AO_SCTRL_SC_MCU_VOTE1EN0_ADDR(base) ((base) + (0x960))
#define SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_ADDR(base) ((base) + (0x964))
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_ADDR(base) ((base) + (0x968))
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK0_ADDR(base) ((base) + (0x970))
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK1_ADDR(base) ((base) + (0x974))
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_MSK_ADDR(base) ((base) + (0x978))
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT1_MSK_ADDR(base) ((base) + (0x97C))
#define SOC_AO_SCTRL_SC_MCU_VOTE2EN0_ADDR(base) ((base) + (0x980))
#define SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_ADDR(base) ((base) + (0x984))
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_ADDR(base) ((base) + (0x988))
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK0_ADDR(base) ((base) + (0x990))
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK1_ADDR(base) ((base) + (0x994))
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_MSK_ADDR(base) ((base) + (0x998))
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT1_MSK_ADDR(base) ((base) + (0x99C))
#define SOC_AO_SCTRL_SC_ECONUM_ADDR(base) ((base) + (0xD20))
#define SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR(base) ((base) + (0xD40))
#define SOC_AO_SCTRL_SC_SLICER_COUNT1_ADDR(base) ((base) + (0xD44))
#define SOC_AO_SCTRL_SC_SLICER_COUNT2_ADDR(base) ((base) + (0xD48))
#define SOC_AO_SCTRL_SC_SLICER_COUNT3_ADDR(base) ((base) + (0xD4C))
#define SOC_AO_SCTRL_SC_SLICER_COUNT4_ADDR(base) ((base) + (0xD50))
#define SOC_AO_SCTRL_SC_SLICER_COUNT5_ADDR(base) ((base) + (0xD54))
#define SOC_AO_SCTRL_SC_SLICER_COUNT6_ADDR(base) ((base) + (0xD58))
#define SOC_AO_SCTRL_SCSYSID0_ADDR(base) ((base) + (0xF00))
#define SOC_AO_SCTRL_SCSYSID1_ADDR(base) ((base) + (0xF04))
#define SOC_AO_SCTRL_SCSYSID2_ADDR(base) ((base) + (0xF08))
#define SOC_AO_SCTRL_SCSYSID3_ADDR(base) ((base) + (0xF0C))
#define SOC_AO_SCTRL_SCCHIPID_ADDR(base) ((base) + (0xF10))
#define SOC_AO_SCTRL_SCWBBPID_ADDR(base) ((base) + (0xF14))
#define SOC_AO_SCTRL_SCGBBPID_ADDR(base) ((base) + (0xF18))
#define SOC_AO_SCTRL_SCSOCID_ADDR(base) ((base) + (0xF1C))
#define SOC_AO_SCTRL_SC_SOC_FPGA_RTL_DEF_ADDR(base) ((base) + (0xFE0))
#define SOC_AO_SCTRL_SC_SOC_FPGA_PR_DEF_ADDR(base) ((base) + (0xFE4))
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF0_ADDR(base) ((base) + (0xFE8))
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF1_ADDR(base) ((base) + (0xFEC))
#define SOC_AO_SCTRL_SCPCELLID0_ADDR(base) ((base) + (0xFF0))
#define SOC_AO_SCTRL_SCPCELLID1_ADDR(base) ((base) + (0xFF4))
#define SOC_AO_SCTRL_SCPCELLID2_ADDR(base) ((base) + (0xFF8))
#define SOC_AO_SCTRL_SCPCELLID3_ADDR(base) ((base) + (0xFFC))
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_ADDR(base) ((base) + (0x1028))
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_ADDR(base) ((base) + (0x102C))
#define SOC_AO_SCTRL_SC_XTAL_CTRL2_ADDR(base) ((base) + (0x1030))
#define SOC_AO_SCTRL_SC_XTAL_CTRL3_ADDR(base) ((base) + (0x1034))
#define SOC_AO_SCTRL_SC_XTAL_CTRL4_ADDR(base) ((base) + (0x1038))
#define SOC_AO_SCTRL_SC_XTAL_CTRL5_ADDR(base) ((base) + (0x103C))
#define SOC_AO_SCTRL_SC_XTAL_CTRL6_ADDR(base) ((base) + (0x1040))
#define SOC_AO_SCTRL_SC_XTAL_STAT0_ADDR(base) ((base) + (0x1060))
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID0_ADDR(base) ((base) + (0x1080))
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID1_ADDR(base) ((base) + (0x1084))
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_ADDR(base) ((base) + (0x1288))
#define SOC_AO_SCTRL_SC_DBG_STAT_ADDR(base) ((base) + (0x12B4))
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY0_ADDR(base) ((base) + (0x12B8))
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY1_ADDR(base) ((base) + (0x12BC))
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_ADDR(base) ((base) + (0x16C0))
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_ADDR(base) ((base) + (0x16C4))
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_ADDR(base) ((base) + (0x16C8))
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_ADDR(base) ((base) + (0x1C00))
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_ADDR(base) ((base) + (0x1C04))
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_ADDR(base) ((base) + (0x1C08))
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_ADDR(base) ((base) + (0x1C10))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int modectrl0 : 3;
        unsigned int reserved_0 : 1;
        unsigned int rst_cpu_function : 4;
        unsigned int wdg_rst_req : 10;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_AO_SCTRL_SC_SYS_CTRL0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SYS_CTRL0_modectrl0_START (0)
#define SOC_AO_SCTRL_SC_SYS_CTRL0_modectrl0_END (2)
#define SOC_AO_SCTRL_SC_SYS_CTRL0_rst_cpu_function_START (4)
#define SOC_AO_SCTRL_SC_SYS_CTRL0_rst_cpu_function_END (7)
#define SOC_AO_SCTRL_SC_SYS_CTRL0_wdg_rst_req_START (8)
#define SOC_AO_SCTRL_SC_SYS_CTRL0_wdg_rst_req_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aarm_wd_rst_cfg : 1;
        unsigned int vote0_reg_semphen_req : 1;
        unsigned int vote1_reg_semphen_req : 1;
        unsigned int vote2_reg_semphen_req : 1;
        unsigned int aarm_wd_sel : 1;
        unsigned int carm_wd_sel : 1;
        unsigned int xtal1_en_in_single_tcxo : 1;
        unsigned int bbpcom_tcxo_sel_2crg : 1;
        unsigned int xtal_bbp_sel_2crg : 1;
        unsigned int single_tcxo_en : 1;
        unsigned int bus_dfs_fore_hh_cfg : 1;
        unsigned int reserved_0 : 3;
        unsigned int mcu_mem_clken_hardcfg : 1;
        unsigned int mcu_clken_hardcfg : 1;
        unsigned int aarm_wd_rst_cfg_msk : 1;
        unsigned int vote0_reg_semphen_req_msk : 1;
        unsigned int vote1_reg_semphen_req_msk : 1;
        unsigned int vote2_reg_semphen_req_msk : 1;
        unsigned int aarm_wd_sel_msk : 1;
        unsigned int carm_wd_sel_msk : 1;
        unsigned int reserved_1 : 1;
        unsigned int clk104m_bbppll0_sel_2crg_msk : 1;
        unsigned int xtal_sel_bbp_2crg_msk : 1;
        unsigned int single_tcxo_en_msk : 1;
        unsigned int bus_dfs_fore_hd_cfg_msk : 1;
        unsigned int reserved_2 : 3;
        unsigned int mcu_mem_clken_hardcfg_msk : 1;
        unsigned int mcu_clken_hardcfg_msk : 1;
    } reg;
} SOC_AO_SCTRL_SC_SYS_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_rst_cfg_START (0)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_rst_cfg_END (0)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote0_reg_semphen_req_START (1)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote0_reg_semphen_req_END (1)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_START (2)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_END (2)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote2_reg_semphen_req_START (3)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote2_reg_semphen_req_END (3)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_sel_START (4)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_sel_END (4)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_carm_wd_sel_START (5)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_carm_wd_sel_END (5)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal1_en_in_single_tcxo_START (6)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal1_en_in_single_tcxo_END (6)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bbpcom_tcxo_sel_2crg_START (7)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bbpcom_tcxo_sel_2crg_END (7)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal_bbp_sel_2crg_START (8)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal_bbp_sel_2crg_END (8)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_single_tcxo_en_START (9)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_single_tcxo_en_END (9)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bus_dfs_fore_hh_cfg_START (10)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bus_dfs_fore_hh_cfg_END (10)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_mem_clken_hardcfg_START (14)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_mem_clken_hardcfg_END (14)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_clken_hardcfg_START (15)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_clken_hardcfg_END (15)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_rst_cfg_msk_START (16)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_rst_cfg_msk_END (16)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote0_reg_semphen_req_msk_START (17)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote0_reg_semphen_req_msk_END (17)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_msk_START (18)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_msk_END (18)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote2_reg_semphen_req_msk_START (19)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_vote2_reg_semphen_req_msk_END (19)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_sel_msk_START (20)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_aarm_wd_sel_msk_END (20)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_carm_wd_sel_msk_START (21)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_carm_wd_sel_msk_END (21)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_clk104m_bbppll0_sel_2crg_msk_START (23)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_clk104m_bbppll0_sel_2crg_msk_END (23)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal_sel_bbp_2crg_msk_START (24)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_xtal_sel_bbp_2crg_msk_END (24)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_single_tcxo_en_msk_START (25)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_single_tcxo_en_msk_END (25)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bus_dfs_fore_hd_cfg_msk_START (26)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_bus_dfs_fore_hd_cfg_msk_END (26)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_mem_clken_hardcfg_msk_START (30)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_mem_clken_hardcfg_msk_END (30)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_clken_hardcfg_msk_START (31)
#define SOC_AO_SCTRL_SC_SYS_CTRL1_mcu_clken_hardcfg_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 30;
        unsigned int wdg_rst_stat_clear : 1;
        unsigned int glb_srst_stat_clear : 1;
    } reg;
} SOC_AO_SCTRL_SC_SYS_CTRL2_UNION;
#endif
#define SOC_AO_SCTRL_SC_SYS_CTRL2_wdg_rst_stat_clear_START (30)
#define SOC_AO_SCTRL_SC_SYS_CTRL2_wdg_rst_stat_clear_END (30)
#define SOC_AO_SCTRL_SC_SYS_CTRL2_glb_srst_stat_clear_START (31)
#define SOC_AO_SCTRL_SC_SYS_CTRL2_glb_srst_stat_clear_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_en0 : 1;
        unsigned int sc_int_count_en1 : 1;
        unsigned int sc_int_count_en2 : 1;
        unsigned int sc_int_count_en3 : 1;
        unsigned int sc_int_count_en4 : 1;
        unsigned int sc_int_count_en5 : 1;
        unsigned int sc_int_count_en6 : 1;
        unsigned int sc_int_count_en7 : 1;
        unsigned int sc_int_count_en8 : 1;
        unsigned int sc_int_count_en9 : 1;
        unsigned int sc_int_count_en10 : 1;
        unsigned int sc_int_count_en11 : 1;
        unsigned int sc_int_count_en12 : 1;
        unsigned int sc_int_count_en13 : 1;
        unsigned int sc_int_count_en14 : 1;
        unsigned int sc_int_count_en15 : 1;
        unsigned int sc_int_count_en16 : 1;
        unsigned int sc_int_count_en17 : 1;
        unsigned int sc_int_count_en18 : 1;
        unsigned int sc_int_count_en19 : 1;
        unsigned int sc_int_count_en20 : 1;
        unsigned int sc_int_count_en21 : 1;
        unsigned int sc_int_count_en22 : 1;
        unsigned int sc_int_count_en23 : 1;
        unsigned int sc_int_count_en24 : 1;
        unsigned int sc_int_count_en25 : 1;
        unsigned int sc_int_count_en26 : 1;
        unsigned int sc_int_count_en27 : 1;
        unsigned int sc_int_count_en28 : 1;
        unsigned int sc_int_count_en29 : 1;
        unsigned int sc_int_count_en30 : 1;
        unsigned int sc_int_count_en31 : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_EN_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en0_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en0_END (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en1_START (1)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en1_END (1)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en2_START (2)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en2_END (2)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en3_START (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en3_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en4_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en4_END (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en5_START (5)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en5_END (5)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en6_START (6)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en6_END (6)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en7_START (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en7_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en8_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en8_END (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en9_START (9)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en9_END (9)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en10_START (10)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en10_END (10)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en11_START (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en11_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en12_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en12_END (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en13_START (13)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en13_END (13)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en14_START (14)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en14_END (14)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en15_START (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en15_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en16_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en16_END (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en17_START (17)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en17_END (17)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en18_START (18)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en18_END (18)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en19_START (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en19_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en20_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en20_END (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en21_START (21)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en21_END (21)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en22_START (22)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en22_END (22)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en23_START (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en23_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en24_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en24_END (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en25_START (25)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en25_END (25)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en26_START (26)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en26_END (26)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en27_START (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en27_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en28_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en28_END (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en29_START (29)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en29_END (29)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en30_START (30)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en30_END (30)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en31_START (31)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN_sc_int_count_en31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 3;
        unsigned int nand_boot_en : 1;
        unsigned int security_boot_flg : 1;
        unsigned int efuse_nandboot_msk : 1;
        unsigned int efuse_nand_bitwide : 1;
        unsigned int efse_acpu1_msk : 1;
        unsigned int efse_acpu2_msk : 1;
        unsigned int efse_acpu3_msk : 1;
        unsigned int glb_srst_stat : 1;
        unsigned int wdg_rst_stat : 1;
        unsigned int mcu_rst_stat : 1;
        unsigned int mcu_wdgrst_stat : 1;
        unsigned int mcu_softrst_stat : 1;
        unsigned int tsensor0_hardrst_stat : 1;
        unsigned int tsensor1_hardrst_stat : 1;
        unsigned int acpu_wd_glb_rst_stat : 1;
        unsigned int sc_sys_stat0_reserved27 : 10;
        unsigned int vote0_semphsta : 1;
        unsigned int vote1_semphsta : 1;
        unsigned int vote2_semphsta : 1;
        unsigned int sc_sys_stat0 : 1;
    } reg;
} SOC_AO_SCTRL_SC_SYS_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SYS_STAT0_nand_boot_en_START (3)
#define SOC_AO_SCTRL_SC_SYS_STAT0_nand_boot_en_END (3)
#define SOC_AO_SCTRL_SC_SYS_STAT0_security_boot_flg_START (4)
#define SOC_AO_SCTRL_SC_SYS_STAT0_security_boot_flg_END (4)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efuse_nandboot_msk_START (5)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efuse_nandboot_msk_END (5)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efuse_nand_bitwide_START (6)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efuse_nand_bitwide_END (6)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu1_msk_START (7)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu1_msk_END (7)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu2_msk_START (8)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu2_msk_END (8)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu3_msk_START (9)
#define SOC_AO_SCTRL_SC_SYS_STAT0_efse_acpu3_msk_END (9)
#define SOC_AO_SCTRL_SC_SYS_STAT0_glb_srst_stat_START (10)
#define SOC_AO_SCTRL_SC_SYS_STAT0_glb_srst_stat_END (10)
#define SOC_AO_SCTRL_SC_SYS_STAT0_wdg_rst_stat_START (11)
#define SOC_AO_SCTRL_SC_SYS_STAT0_wdg_rst_stat_END (11)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_rst_stat_START (12)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_rst_stat_END (12)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_wdgrst_stat_START (13)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_wdgrst_stat_END (13)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_softrst_stat_START (14)
#define SOC_AO_SCTRL_SC_SYS_STAT0_mcu_softrst_stat_END (14)
#define SOC_AO_SCTRL_SC_SYS_STAT0_tsensor0_hardrst_stat_START (15)
#define SOC_AO_SCTRL_SC_SYS_STAT0_tsensor0_hardrst_stat_END (15)
#define SOC_AO_SCTRL_SC_SYS_STAT0_tsensor1_hardrst_stat_START (16)
#define SOC_AO_SCTRL_SC_SYS_STAT0_tsensor1_hardrst_stat_END (16)
#define SOC_AO_SCTRL_SC_SYS_STAT0_acpu_wd_glb_rst_stat_START (17)
#define SOC_AO_SCTRL_SC_SYS_STAT0_acpu_wd_glb_rst_stat_END (17)
#define SOC_AO_SCTRL_SC_SYS_STAT0_sc_sys_stat0_reserved27_START (18)
#define SOC_AO_SCTRL_SC_SYS_STAT0_sc_sys_stat0_reserved27_END (27)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote0_semphsta_START (28)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote0_semphsta_END (28)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote1_semphsta_START (29)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote1_semphsta_END (29)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote2_semphsta_START (30)
#define SOC_AO_SCTRL_SC_SYS_STAT0_vote2_semphsta_END (30)
#define SOC_AO_SCTRL_SC_SYS_STAT0_sc_sys_stat0_START (31)
#define SOC_AO_SCTRL_SC_SYS_STAT0_sc_sys_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_pw_up_stat : 1;
        unsigned int reserved_0 : 1;
        unsigned int tcxo_div_out : 1;
        unsigned int pll_sw_ok : 1;
        unsigned int xtal_sw_ok : 1;
        unsigned int efuse_hw_rd_finish : 1;
        unsigned int sysstat_reserved6 : 1;
        unsigned int jtag_trst_n_pin : 1;
        unsigned int reserved_1 : 2;
        unsigned int boot_sel_lock : 1;
        unsigned int func_mode_lock : 2;
        unsigned int mode_status : 4;
        unsigned int boot_mode_lock : 4;
        unsigned int fun_jtag_mode_out : 3;
        unsigned int hifi2mcu_wkup_int_out : 1;
        unsigned int mcpu2mcu_wkup_int_out : 1;
        unsigned int acpu2mcu_wkup_int_out : 1;
        unsigned int mcu_wkup_int_out : 1;
        unsigned int reserved_2 : 1;
        unsigned int sysstat_reserved : 3;
    } reg;
} SOC_AO_SCTRL_SC_SYS_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_SYS_STAT1_soc_pw_up_stat_START (0)
#define SOC_AO_SCTRL_SC_SYS_STAT1_soc_pw_up_stat_END (0)
#define SOC_AO_SCTRL_SC_SYS_STAT1_tcxo_div_out_START (2)
#define SOC_AO_SCTRL_SC_SYS_STAT1_tcxo_div_out_END (2)
#define SOC_AO_SCTRL_SC_SYS_STAT1_pll_sw_ok_START (3)
#define SOC_AO_SCTRL_SC_SYS_STAT1_pll_sw_ok_END (3)
#define SOC_AO_SCTRL_SC_SYS_STAT1_xtal_sw_ok_START (4)
#define SOC_AO_SCTRL_SC_SYS_STAT1_xtal_sw_ok_END (4)
#define SOC_AO_SCTRL_SC_SYS_STAT1_efuse_hw_rd_finish_START (5)
#define SOC_AO_SCTRL_SC_SYS_STAT1_efuse_hw_rd_finish_END (5)
#define SOC_AO_SCTRL_SC_SYS_STAT1_sysstat_reserved6_START (6)
#define SOC_AO_SCTRL_SC_SYS_STAT1_sysstat_reserved6_END (6)
#define SOC_AO_SCTRL_SC_SYS_STAT1_jtag_trst_n_pin_START (7)
#define SOC_AO_SCTRL_SC_SYS_STAT1_jtag_trst_n_pin_END (7)
#define SOC_AO_SCTRL_SC_SYS_STAT1_boot_sel_lock_START (10)
#define SOC_AO_SCTRL_SC_SYS_STAT1_boot_sel_lock_END (10)
#define SOC_AO_SCTRL_SC_SYS_STAT1_func_mode_lock_START (11)
#define SOC_AO_SCTRL_SC_SYS_STAT1_func_mode_lock_END (12)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mode_status_START (13)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mode_status_END (16)
#define SOC_AO_SCTRL_SC_SYS_STAT1_boot_mode_lock_START (17)
#define SOC_AO_SCTRL_SC_SYS_STAT1_boot_mode_lock_END (20)
#define SOC_AO_SCTRL_SC_SYS_STAT1_fun_jtag_mode_out_START (21)
#define SOC_AO_SCTRL_SC_SYS_STAT1_fun_jtag_mode_out_END (23)
#define SOC_AO_SCTRL_SC_SYS_STAT1_hifi2mcu_wkup_int_out_START (24)
#define SOC_AO_SCTRL_SC_SYS_STAT1_hifi2mcu_wkup_int_out_END (24)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mcpu2mcu_wkup_int_out_START (25)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mcpu2mcu_wkup_int_out_END (25)
#define SOC_AO_SCTRL_SC_SYS_STAT1_acpu2mcu_wkup_int_out_START (26)
#define SOC_AO_SCTRL_SC_SYS_STAT1_acpu2mcu_wkup_int_out_END (26)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mcu_wkup_int_out_START (27)
#define SOC_AO_SCTRL_SC_SYS_STAT1_mcu_wkup_int_out_END (27)
#define SOC_AO_SCTRL_SC_SYS_STAT1_sysstat_reserved_START (29)
#define SOC_AO_SCTRL_SC_SYS_STAT1_sysstat_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itmd_en0 : 1;
        unsigned int itmd_ctrl0 : 3;
        unsigned int reserved : 28;
    } reg;
} SOC_AO_SCTRL_SC_MCU_IMCTRL_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_IMCTRL_itmd_en0_START (0)
#define SOC_AO_SCTRL_SC_MCU_IMCTRL_itmd_en0_END (0)
#define SOC_AO_SCTRL_SC_MCU_IMCTRL_itmd_ctrl0_START (1)
#define SOC_AO_SCTRL_SC_MCU_IMCTRL_itmd_ctrl0_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itmd_stat0 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_AO_SCTRL_SC_MCU_IMSTAT_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_IMSTAT_itmd_stat0_START (0)
#define SOC_AO_SCTRL_SC_MCU_IMSTAT_itmd_stat0_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_sta0 : 4;
        unsigned int sc_int_count_sta1 : 4;
        unsigned int sc_int_count_sta2 : 4;
        unsigned int sc_int_count_sta3 : 4;
        unsigned int sc_int_count_sta4 : 4;
        unsigned int sc_int_count_sta5 : 4;
        unsigned int sc_int_count_sta6 : 4;
        unsigned int sc_int_count_sta7 : 4;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta0_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta0_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta1_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta1_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta2_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta2_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta3_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta3_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta4_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta4_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta5_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta5_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta6_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta6_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta7_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT0_sc_int_count_sta7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_sta8 : 4;
        unsigned int sc_int_count_sta9 : 4;
        unsigned int sc_int_count_sta10 : 4;
        unsigned int sc_int_count_sta11 : 4;
        unsigned int sc_int_count_sta12 : 4;
        unsigned int sc_int_count_sta13 : 4;
        unsigned int sc_int_count_sta14 : 4;
        unsigned int sc_int_count_sta15 : 4;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta8_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta8_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta9_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta9_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta10_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta10_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta11_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta11_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta12_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta12_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta13_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta13_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta14_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta14_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta15_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT1_sc_int_count_sta15_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_sta16 : 4;
        unsigned int sc_int_count_sta17 : 4;
        unsigned int sc_int_count_sta18 : 4;
        unsigned int sc_int_count_sta19 : 4;
        unsigned int sc_int_count_sta20 : 4;
        unsigned int sc_int_count_sta21 : 4;
        unsigned int sc_int_count_sta22 : 4;
        unsigned int sc_int_count_sta23 : 4;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_STAT2_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta16_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta16_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta17_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta17_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta18_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta18_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta19_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta19_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta20_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta20_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta21_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta21_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta22_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta22_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta23_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT2_sc_int_count_sta23_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_sta24 : 4;
        unsigned int sc_int_count_sta25 : 4;
        unsigned int sc_int_count_sta26 : 4;
        unsigned int sc_int_count_sta27 : 4;
        unsigned int sc_int_count_sta28 : 4;
        unsigned int sc_int_count_sta29 : 4;
        unsigned int sc_int_count_sta30 : 4;
        unsigned int sc_int_count_sta31 : 4;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_STAT3_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta24_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta24_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta25_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta25_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta26_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta26_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta27_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta27_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta28_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta28_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta29_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta29_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta30_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta30_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta31_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT3_sc_int_count_sta31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_sta32 : 4;
        unsigned int sc_int_count_sta33 : 4;
        unsigned int sc_int_count_sta34 : 4;
        unsigned int sc_int_count_sta35 : 4;
        unsigned int sc_int_count_sta36 : 4;
        unsigned int sc_int_count_sta37 : 4;
        unsigned int sc_int_count_sta38 : 4;
        unsigned int sc_int_count_sta39 : 4;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_STAT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta32_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta32_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta33_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta33_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta34_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta34_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta35_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta35_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta36_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta36_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta37_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta37_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta38_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta38_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta39_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_STAT4_sc_int_count_sta39_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_count_en32 : 1;
        unsigned int sc_int_count_en33 : 1;
        unsigned int sc_int_count_en34 : 1;
        unsigned int sc_int_count_en35 : 1;
        unsigned int sc_int_count_en36 : 1;
        unsigned int sc_int_count_en37 : 1;
        unsigned int sc_int_count_en38 : 1;
        unsigned int sc_int_count_en39 : 1;
        unsigned int sc_int_count_en40 : 1;
        unsigned int sc_int_count_en41 : 1;
        unsigned int sc_int_count_en42 : 1;
        unsigned int sc_int_count_en43 : 1;
        unsigned int sc_int_count_en44 : 1;
        unsigned int sc_int_count_en45 : 1;
        unsigned int sc_int_count_en46 : 1;
        unsigned int sc_int_count_en47 : 1;
        unsigned int sc_int_count_en48 : 1;
        unsigned int sc_int_count_en49 : 1;
        unsigned int sc_int_count_en50 : 1;
        unsigned int sc_int_count_en51 : 1;
        unsigned int sc_int_count_en52 : 1;
        unsigned int sc_int_count_en53 : 1;
        unsigned int sc_int_count_en54 : 1;
        unsigned int sc_int_count_en55 : 1;
        unsigned int sc_int_count_en56 : 1;
        unsigned int sc_int_count_en57 : 1;
        unsigned int sc_int_count_en58 : 1;
        unsigned int sc_int_count_en59 : 1;
        unsigned int sc_int_count_en60 : 1;
        unsigned int sc_int_count_en61 : 1;
        unsigned int sc_int_count_en62 : 1;
        unsigned int sc_int_count_en63 : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_COUNT_EN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en32_START (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en32_END (0)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en33_START (1)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en33_END (1)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en34_START (2)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en34_END (2)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en35_START (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en35_END (3)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en36_START (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en36_END (4)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en37_START (5)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en37_END (5)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en38_START (6)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en38_END (6)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en39_START (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en39_END (7)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en40_START (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en40_END (8)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en41_START (9)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en41_END (9)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en42_START (10)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en42_END (10)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en43_START (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en43_END (11)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en44_START (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en44_END (12)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en45_START (13)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en45_END (13)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en46_START (14)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en46_END (14)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en47_START (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en47_END (15)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en48_START (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en48_END (16)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en49_START (17)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en49_END (17)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en50_START (18)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en50_END (18)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en51_START (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en51_END (19)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en52_START (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en52_END (20)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en53_START (21)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en53_END (21)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en54_START (22)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en54_END (22)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en55_START (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en55_END (23)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en56_START (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en56_END (24)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en57_START (25)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en57_END (25)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en58_START (26)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en58_END (26)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en59_START (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en59_END (27)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en60_START (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en60_END (28)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en61_START (29)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en61_END (29)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en62_START (30)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en62_END (30)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en63_START (31)
#define SOC_AO_SCTRL_SC_INT_COUNT_EN1_sc_int_count_en63_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secondry_int_en0_acpu_commrx0 : 1;
        unsigned int sc_secondry_int_en0_acpu_commrx1 : 1;
        unsigned int sc_secondry_int_en0_acpu_commrx2 : 1;
        unsigned int sc_secondry_int_en0_acpu_commrx3 : 1;
        unsigned int sc_secondry_int_en0_acpu_commtx0 : 1;
        unsigned int sc_secondry_int_en0_acpu_commtx1 : 1;
        unsigned int sc_secondry_int_en0_acpu_commtx2 : 1;
        unsigned int sc_secondry_int_en0_acpu_commtx3 : 1;
        unsigned int sc_secondry_int_en0_wbbp_otdoa_int2bbe : 1;
        unsigned int sc_secondry_int_en0_bbpslot_bbe16_in14 : 1;
        unsigned int sc_secondry_int_en0_bbpslot_bbe16_in13 : 1;
        unsigned int sc_secondry_int_en0_upacc_int2bbe : 1;
        unsigned int sc_secondry_int_en0_g1_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_en0_g1_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_en0_g2_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_en0_g2_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_en0_nandc_int_to_acpu : 1;
        unsigned int sc_secondry_int_en0_ltedsp_tie_expstate0_int_bbp_to_acpu : 1;
        unsigned int sc_secondry_int_en0_18bit : 1;
        unsigned int sc_secondry_int_en0_19bit : 1;
        unsigned int sc_secondry_int_en0_20bit : 1;
        unsigned int sc_secondry_int_en0_21bit : 1;
        unsigned int sc_secondry_int_en0_22bit : 1;
        unsigned int sc_secondry_int_en0_23bit : 1;
        unsigned int sc_secondry_int_en0_24bit : 1;
        unsigned int sc_secondry_int_en0_25bit : 1;
        unsigned int sc_secondry_int_en0_26bit : 1;
        unsigned int sc_secondry_int_en0_27bit : 1;
        unsigned int sc_secondry_int_en0_28bit : 1;
        unsigned int sc_secondry_int_en0_29bit : 1;
        unsigned int sc_secondry_int_en0_30bit : 1;
        unsigned int sc_secondry_int_en0_31bit : 1;
    } reg;
} SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx0_START (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx0_END (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx1_START (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx1_END (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx2_START (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx2_END (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx3_START (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commrx3_END (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx0_START (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx0_END (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx1_START (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx1_END (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx2_START (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx2_END (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx3_START (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_acpu_commtx3_END (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_wbbp_otdoa_int2bbe_START (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_wbbp_otdoa_int2bbe_END (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_bbpslot_bbe16_in14_START (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_bbpslot_bbe16_in14_END (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_bbpslot_bbe16_in13_START (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_bbpslot_bbe16_in13_END (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_upacc_int2bbe_START (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_upacc_int2bbe_END (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g1_int_bbp_to_dsp_START (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g1_int_bbp_to_dsp_END (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g1_int_bbp_to_dsp_32k_START (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g1_int_bbp_to_dsp_32k_END (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g2_int_bbp_to_dsp_START (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g2_int_bbp_to_dsp_END (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g2_int_bbp_to_dsp_32k_START (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_g2_int_bbp_to_dsp_32k_END (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_nandc_int_to_acpu_START (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_nandc_int_to_acpu_END (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_ltedsp_tie_expstate0_int_bbp_to_acpu_START (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_ltedsp_tie_expstate0_int_bbp_to_acpu_END (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_18bit_START (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_18bit_END (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_19bit_START (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_19bit_END (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_20bit_START (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_20bit_END (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_21bit_START (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_21bit_END (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_22bit_START (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_22bit_END (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_23bit_START (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_23bit_END (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_24bit_START (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_24bit_END (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_25bit_START (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_25bit_END (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_26bit_START (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_26bit_END (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_27bit_START (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_27bit_END (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_28bit_START (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_28bit_END (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_29bit_START (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_29bit_END (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_30bit_START (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_30bit_END (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_31bit_START (31)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_EN0_sc_secondry_int_en0_31bit_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secondry_int_raw0_acpu_commrx0 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commrx1 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commrx2 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commrx3 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commtx0 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commtx1 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commtx2 : 1;
        unsigned int sc_secondry_int_raw0_acpu_commtx3 : 1;
        unsigned int sc_secondry_int_raw0_wbbp_otdoa_int2bbe : 1;
        unsigned int sc_secondry_int_raw0_bbpslot_bbe16_in14 : 1;
        unsigned int sc_secondry_int_raw0_bbpslot_bbe16_in13 : 1;
        unsigned int sc_secondry_int_raw0_upacc_int2bbe : 1;
        unsigned int sc_secondry_int_raw0_g1_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_raw0_g1_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_raw0_g2_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_raw0_g2_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_raw0_nandc_int_to_acpu : 1;
        unsigned int sc_secondry_int_raw0_ltedsp_tie_expstate0_int_bbp_to_acpu : 1;
        unsigned int sc_secondry_int_raw0_18bit : 1;
        unsigned int sc_secondry_int_raw0_19bit : 1;
        unsigned int sc_secondry_int_raw0_20bit : 1;
        unsigned int sc_secondry_int_raw0_21bit : 1;
        unsigned int sc_secondry_int_raw0_22bit : 1;
        unsigned int sc_secondry_int_raw0_23bit : 1;
        unsigned int sc_secondry_int_raw0_24bit : 1;
        unsigned int sc_secondry_int_raw0_25bit : 1;
        unsigned int sc_secondry_int_raw0_26bit : 1;
        unsigned int sc_secondry_int_raw0_27bit : 1;
        unsigned int sc_secondry_int_raw0_28bit : 1;
        unsigned int sc_secondry_int_raw0_29bit : 1;
        unsigned int sc_secondry_int_raw0_30bit : 1;
        unsigned int sc_secondry_int_raw0_31bit : 1;
    } reg;
} SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx0_START (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx0_END (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx1_START (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx1_END (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx2_START (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx2_END (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx3_START (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commrx3_END (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx0_START (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx0_END (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx1_START (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx1_END (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx2_START (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx2_END (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx3_START (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_acpu_commtx3_END (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_wbbp_otdoa_int2bbe_START (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_wbbp_otdoa_int2bbe_END (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_bbpslot_bbe16_in14_START (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_bbpslot_bbe16_in14_END (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_bbpslot_bbe16_in13_START (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_bbpslot_bbe16_in13_END (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_upacc_int2bbe_START (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_upacc_int2bbe_END (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g1_int_bbp_to_dsp_START (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g1_int_bbp_to_dsp_END (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g1_int_bbp_to_dsp_32k_START (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g1_int_bbp_to_dsp_32k_END (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g2_int_bbp_to_dsp_START (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g2_int_bbp_to_dsp_END (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g2_int_bbp_to_dsp_32k_START (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_g2_int_bbp_to_dsp_32k_END (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_nandc_int_to_acpu_START (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_nandc_int_to_acpu_END (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_ltedsp_tie_expstate0_int_bbp_to_acpu_START (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_ltedsp_tie_expstate0_int_bbp_to_acpu_END (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_18bit_START (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_18bit_END (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_19bit_START (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_19bit_END (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_20bit_START (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_20bit_END (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_21bit_START (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_21bit_END (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_22bit_START (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_22bit_END (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_23bit_START (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_23bit_END (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_24bit_START (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_24bit_END (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_25bit_START (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_25bit_END (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_26bit_START (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_26bit_END (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_27bit_START (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_27bit_END (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_28bit_START (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_28bit_END (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_29bit_START (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_29bit_END (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_30bit_START (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_30bit_END (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_31bit_START (31)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATR0_sc_secondry_int_raw0_31bit_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secondry_int_mask0_acpu_commrx0 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commrx1 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commrx2 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commrx3 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commtx0 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commtx1 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commtx2 : 1;
        unsigned int sc_secondry_int_mask0_acpu_commtx3 : 1;
        unsigned int sc_secondry_int_mask0_wbbp_otdoa_int2bbe : 1;
        unsigned int sc_secondry_int_mask0_bbpslot_bbe16_in14 : 1;
        unsigned int sc_secondry_int_mask0_bbpslot_bbe16_in13 : 1;
        unsigned int sc_secondry_int_mask0_upacc_int2bbe : 1;
        unsigned int sc_secondry_int_mask0_g1_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_mask0_g1_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_mask0_g2_int_bbp_to_dsp : 1;
        unsigned int sc_secondry_int_mask0_g2_int_bbp_to_dsp_32k : 1;
        unsigned int sc_secondry_int_mask0_nandc_int_to_acpu : 1;
        unsigned int sc_secondry_int_mask0_ltedsp_tie_expstate0_int_bbp_to_acpu : 1;
        unsigned int sc_secondry_int_mask0_18bit : 1;
        unsigned int sc_secondry_int_mask0_19bit : 1;
        unsigned int sc_secondry_int_mask0_20bit : 1;
        unsigned int sc_secondry_int_mask0_21bit : 1;
        unsigned int sc_secondry_int_mask0_22bit : 1;
        unsigned int sc_secondry_int_mask0_23bit : 1;
        unsigned int sc_secondry_int_mask0_24bit : 1;
        unsigned int sc_secondry_int_mask0_25bit : 1;
        unsigned int sc_secondry_int_mask0_26bit : 1;
        unsigned int sc_secondry_int_mask0_27bit : 1;
        unsigned int sc_secondry_int_mask0_28bit : 1;
        unsigned int sc_secondry_int_mask0_29bit : 1;
        unsigned int sc_secondry_int_mask0_30bit : 1;
        unsigned int sc_secondry_int_mask0 : 1;
    } reg;
} SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx0_START (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx0_END (0)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx1_START (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx1_END (1)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx2_START (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx2_END (2)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx3_START (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commrx3_END (3)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx0_START (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx0_END (4)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx1_START (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx1_END (5)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx2_START (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx2_END (6)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx3_START (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_acpu_commtx3_END (7)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_wbbp_otdoa_int2bbe_START (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_wbbp_otdoa_int2bbe_END (8)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_bbpslot_bbe16_in14_START (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_bbpslot_bbe16_in14_END (9)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_bbpslot_bbe16_in13_START (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_bbpslot_bbe16_in13_END (10)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_upacc_int2bbe_START (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_upacc_int2bbe_END (11)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g1_int_bbp_to_dsp_START (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g1_int_bbp_to_dsp_END (12)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g1_int_bbp_to_dsp_32k_START (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g1_int_bbp_to_dsp_32k_END (13)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g2_int_bbp_to_dsp_START (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g2_int_bbp_to_dsp_END (14)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g2_int_bbp_to_dsp_32k_START (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_g2_int_bbp_to_dsp_32k_END (15)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_nandc_int_to_acpu_START (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_nandc_int_to_acpu_END (16)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_ltedsp_tie_expstate0_int_bbp_to_acpu_START (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_ltedsp_tie_expstate0_int_bbp_to_acpu_END (17)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_18bit_START (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_18bit_END (18)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_19bit_START (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_19bit_END (19)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_20bit_START (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_20bit_END (20)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_21bit_START (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_21bit_END (21)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_22bit_START (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_22bit_END (22)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_23bit_START (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_23bit_END (23)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_24bit_START (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_24bit_END (24)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_25bit_START (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_25bit_END (25)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_26bit_START (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_26bit_END (26)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_27bit_START (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_27bit_END (27)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_28bit_START (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_28bit_END (28)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_29bit_START (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_29bit_END (29)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_30bit_START (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_30bit_END (30)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_START (31)
#define SOC_AO_SCTRL_SC_SECONDRY_INT_STATM0_sc_secondry_int_mask0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en6_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_en6_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_en6_WatchDog2 : 1;
        unsigned int mcu_wakeup_int_en6_CM3WatchDog1 : 1;
        unsigned int mcu_wakeup_int_en6_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO14 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO15 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO16 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO17 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO18 : 1;
        unsigned int mcu_wakeup_int_en6_GPIO19 : 1;
        unsigned int mcu_wakeup_int_en6_CM3Timer2 : 1;
        unsigned int mcu_wakeup_int_en6_CM3Timer3 : 1;
        unsigned int mcu_wakeup_int_en6 : 19;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_WatchDog2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3WatchDog1_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3WatchDog1_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_MWatchDog0_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_MWatchDog0_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO14_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO14_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO15_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO15_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO16_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO16_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO17_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO17_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO18_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO18_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO19_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_GPIO19_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3Timer2_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3Timer2_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3Timer3_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_CM3Timer3_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN6_mcu_wakeup_int_en6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw6_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_raw6_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_raw6_WatchDog2 : 1;
        unsigned int mcu_wakeup_int_raw6_CM3WatchDog1 : 1;
        unsigned int mcu_wakeup_int_raw6_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO14 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO15 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO16 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO17 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO18 : 1;
        unsigned int mcu_wakeup_int_raw6_GPIO19 : 1;
        unsigned int mcu_wakeup_int_raw6_CM3Timer2 : 1;
        unsigned int mcu_wakeup_int_raw6_CM3Timer3 : 1;
        unsigned int mcu_wakeup_int_raw6 : 19;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_WatchDog2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3WatchDog1_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3WatchDog1_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_MWatchDog0_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_MWatchDog0_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO14_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO14_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO15_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO15_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO16_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO16_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO17_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO17_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO18_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO18_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO19_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_GPIO19_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3Timer2_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3Timer2_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3Timer3_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_CM3Timer3_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR6_mcu_wakeup_int_raw6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask6_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_mask6_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_mask6_WatchDog2 : 1;
        unsigned int mcu_wakeup_int_mask6_CM3WatchDog1 : 1;
        unsigned int mcu_wakeup_int_mask6_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO14 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO15 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO16 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO17 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO18 : 1;
        unsigned int mcu_wakeup_int_mask6_GPIO19 : 1;
        unsigned int mcu_wakeup_int_mask6_CM3Timer2 : 1;
        unsigned int mcu_wakeup_int_mask6_CM3Timer3 : 1;
        unsigned int mcu_wakeup_int_mask6 : 19;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_WatchDog2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3WatchDog1_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3WatchDog1_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_MWatchDog0_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_MWatchDog0_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO14_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO14_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO15_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO15_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO16_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO16_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO17_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO17_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO18_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO18_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO19_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_GPIO19_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3Timer2_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3Timer2_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3Timer3_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_CM3Timer3_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM6_mcu_wakeup_int_mask6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en5_GPIO0 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO1 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO2 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO3 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO4 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO5 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO6 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO7 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO8 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO9 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO10 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO11 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO12 : 1;
        unsigned int mcu_wakeup_int_en5_GPIO13 : 1;
        unsigned int mcu_wakeup_int_en5_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en5_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en5_OTG_WKP_STS : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_en5_RTC_INT : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int mcu_wakeup_int_en5_Timer14 : 1;
        unsigned int mcu_wakeup_int_en5_Timer15 : 1;
        unsigned int mcu_wakeup_int_en5_Timer16 : 1;
        unsigned int mcu_wakeup_int_en5_Timer17 : 1;
        unsigned int mcu_wakeup_int_en5_CM3Timer0 : 1;
        unsigned int mcu_wakeup_int_en5_CM3Timer1 : 1;
        unsigned int mcu_wakeup_int_en5_MTimer16 : 1;
        unsigned int mcu_wakeup_int_en5_MTimer17 : 1;
        unsigned int mcu_wakeup_int_en5_MTimer18 : 1;
        unsigned int mcu_wakeup_int_en5_MTimer19 : 1;
        unsigned int mcu_wakeup_int_en5_CM3WatchDog0 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer14_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer14_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer15_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer15_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer16_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer16_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer17_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_Timer17_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3Timer0_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3Timer0_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3Timer1_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3Timer1_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer16_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer16_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer17_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer17_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer18_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer18_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer19_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_MTimer19_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3WatchDog0_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN5_mcu_wakeup_int_en5_CM3WatchDog0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw5_GPIO0 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO1 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO2 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO3 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO4 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO5 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO6 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO7 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO8 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO9 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO10 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO11 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO12 : 1;
        unsigned int mcu_wakeup_int_raw5_GPIO13 : 1;
        unsigned int mcu_wakeup_int_raw5_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw5_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw5_OTG_WKP_STS : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_raw5_RTC_INT : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int mcu_wakeup_int_raw5_Timer14 : 1;
        unsigned int mcu_wakeup_int_raw5_Timer15 : 1;
        unsigned int mcu_wakeup_int_raw5_Timer16 : 1;
        unsigned int mcu_wakeup_int_raw5_Timer17 : 1;
        unsigned int mcu_wakeup_int_raw5_CM3Timer0 : 1;
        unsigned int mcu_wakeup_int_raw5_CM3Timer1 : 1;
        unsigned int mcu_wakeup_int_raw5_MTimer16 : 1;
        unsigned int mcu_wakeup_int_raw5_MTimer17 : 1;
        unsigned int mcu_wakeup_int_raw5_MTimer18 : 1;
        unsigned int mcu_wakeup_int_raw5_MTimer19 : 1;
        unsigned int mcu_wakeup_int_raw5_CM3WatchDog0 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer14_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer14_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer15_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer15_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer16_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer16_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer17_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_Timer17_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3Timer0_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3Timer0_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3Timer1_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3Timer1_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer16_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer16_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer17_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer17_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer18_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer18_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer19_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_MTimer19_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3WatchDog0_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR5_mcu_wakeup_int_raw5_CM3WatchDog0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask5_GPIO0 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO1 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO2 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO3 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO4 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO5 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO6 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO7 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO8 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO9 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO10 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO11 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO12 : 1;
        unsigned int mcu_wakeup_int_mask5_GPIO13 : 1;
        unsigned int mcu_wakeup_int_mask5_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask5_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask5_OTG_WKP_STS : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_mask5_RTC_INT : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int mcu_wakeup_int_mask5_Timer14 : 1;
        unsigned int mcu_wakeup_int_mask5_Timer15 : 1;
        unsigned int mcu_wakeup_int_mask5_Timer16 : 1;
        unsigned int mcu_wakeup_int_mask5_Timer17 : 1;
        unsigned int mcu_wakeup_int_mask5_CM3Timer0 : 1;
        unsigned int mcu_wakeup_int_mask5_CM3Timer1 : 1;
        unsigned int mcu_wakeup_int_mask5_MTimer16 : 1;
        unsigned int mcu_wakeup_int_mask5_MTimer17 : 1;
        unsigned int mcu_wakeup_int_mask5_MTimer18 : 1;
        unsigned int mcu_wakeup_int_mask5_MTimer19 : 1;
        unsigned int mcu_wakeup_int_mask5_CM3WatchDog0 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer14_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer14_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer15_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer15_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer16_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer16_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer17_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_Timer17_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3Timer0_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3Timer0_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3Timer1_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3Timer1_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer16_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer16_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer17_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer17_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer18_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer18_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer19_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_MTimer19_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3WatchDog0_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM5_mcu_wakeup_int_mask5_CM3WatchDog0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int mcu_wakeup_int_en2_GPIO2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int mcu_wakeup_int_en2_GPIO7 : 1;
        unsigned int reserved_6 : 1;
        unsigned int mcu_wakeup_int_en2_GPIO9 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int mcu_wakeup_int_en2_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en2_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en2_OTG_WKP_STS : 1;
        unsigned int reserved_11 : 1;
        unsigned int mcu_wakeup_int_en2_RTC_INT : 1;
        unsigned int mcu_wakeup_int_en2_MTimer0 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer1 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer2 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer3 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer4 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer5 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer6 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer7 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer8 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer9 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer10 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer11 : 1;
        unsigned int mcu_wakeup_int_en2_MTimer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN2_mcu_wakeup_int_en2_MTimer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int mcu_wakeup_int_raw2_GPIO2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int mcu_wakeup_int_raw2_GPIO7 : 1;
        unsigned int reserved_6 : 1;
        unsigned int mcu_wakeup_int_raw2_GPIO9 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int mcu_wakeup_int_raw2_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw2_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw2_OTG_WKP_STS : 1;
        unsigned int reserved_11 : 1;
        unsigned int mcu_wakeup_int_raw2_RTC_INT : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer0 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer1 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer2 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer3 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer4 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer5 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer6 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer7 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer8 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer9 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer10 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer11 : 1;
        unsigned int mcu_wakeup_int_raw2_MTimer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR2_mcu_wakeup_int_raw2_MTimer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int mcu_wakeup_int_mask2_GPIO2 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int mcu_wakeup_int_mask2_GPIO7 : 1;
        unsigned int reserved_6 : 1;
        unsigned int mcu_wakeup_int_mask2_GPIO9 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int mcu_wakeup_int_mask2_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask2_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask2_OTG_WKP_STS : 1;
        unsigned int reserved_11 : 1;
        unsigned int mcu_wakeup_int_mask2_RTC_INT : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer0 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer1 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer2 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer3 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer4 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer5 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer6 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer7 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer8 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer9 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer10 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer11 : 1;
        unsigned int mcu_wakeup_int_mask2_MTimer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_OTG_WKP_STS_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_OTG_WKP_STS_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM2_mcu_wakeup_int_mask2_MTimer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en3_MTimer13 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer14 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer15 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer16 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer17 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer18 : 1;
        unsigned int mcu_wakeup_int_en3_MTimer19 : 1;
        unsigned int mcu_wakeup_int_en3_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_en3_MCPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_en3_GBBP1WKUP3 : 1;
        unsigned int mcu_wakeup_int_en3_GBBP2WKUP3 : 1;
        unsigned int mcu_wakeup_int_en3_WBBP1WKUP : 1;
        unsigned int mcu_wakeup_int_en3_lte_arm_wakeup_int : 1;
        unsigned int mcu_wakeup_int_en3_tds_drx_arm_int1 : 1;
        unsigned int mcu_wakeup_int_en3_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_en3_IPF_0 : 1;
        unsigned int mcu_wakeup_int_en3_IPF_1 : 1;
        unsigned int mcu_wakeup_int_en3_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_en3_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_en3_IPC2MCPU_06 : 1;
        unsigned int mcu_wakeup_int_en3_SEC_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_en3 : 11;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer18_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer18_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer19_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MTimer19_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MWatchDog0_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MWatchDog0_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MCPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_MCPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_GBBP1WKUP3_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_GBBP1WKUP3_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_GBBP2WKUP3_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_GBBP2WKUP3_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_WBBP1WKUP_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_WBBP1WKUP_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_lte_arm_wakeup_int_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_lte_arm_wakeup_int_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_tds_drx_arm_int1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_tds_drx_arm_int1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPC2MCPU_01_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPC2MCPU_01_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPF_0_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPF_0_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPF_1_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPF_1_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SOCP_0_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SOCP_0_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SOCP_1_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SOCP_1_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPC2MCPU_06_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_IPC2MCPU_06_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SEC_IPC2MCPU_01_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_SEC_IPC2MCPU_01_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN3_mcu_wakeup_int_en3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw3_MTimer13 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer14 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer15 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer16 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer17 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer18 : 1;
        unsigned int mcu_wakeup_int_raw3_MTimer19 : 1;
        unsigned int mcu_wakeup_int_raw3_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_raw3_MCPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_raw3_GBBP1WKUP3 : 1;
        unsigned int mcu_wakeup_int_raw3_GBBP2WKUP3 : 1;
        unsigned int mcu_wakeup_int_raw3_WBBP1WKUP : 1;
        unsigned int mcu_wakeup_int_raw3_lte_arm_wakeup_int : 1;
        unsigned int mcu_wakeup_int_raw3_tds_drx_arm_int1 : 1;
        unsigned int mcu_wakeup_int_raw3_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_raw3_IPF_0 : 1;
        unsigned int mcu_wakeup_int_raw3_IPF_1 : 1;
        unsigned int mcu_wakeup_int_raw3_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_raw3_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_raw3_IPC2MCPU_06 : 1;
        unsigned int mcu_wakeup_int_raw3_SEC_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_raw3 : 11;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer18_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer18_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer19_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MTimer19_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MWatchDog0_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MWatchDog0_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MCPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_MCPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_GBBP1WKUP3_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_GBBP1WKUP3_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_GBBP2WKUP3_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_GBBP2WKUP3_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_WBBP1WKUP_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_WBBP1WKUP_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_lte_arm_wakeup_int_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_lte_arm_wakeup_int_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_tds_drx_arm_int1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_tds_drx_arm_int1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPC2MCPU_01_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPC2MCPU_01_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPF_0_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPF_0_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPF_1_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPF_1_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SOCP_0_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SOCP_0_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SOCP_1_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SOCP_1_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPC2MCPU_06_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_IPC2MCPU_06_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SEC_IPC2MCPU_01_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_SEC_IPC2MCPU_01_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR3_mcu_wakeup_int_raw3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask3_MTimer13 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer14 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer15 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer16 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer17 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer18 : 1;
        unsigned int mcu_wakeup_int_mask3_MTimer19 : 1;
        unsigned int mcu_wakeup_int_mask3_MWatchDog0 : 1;
        unsigned int mcu_wakeup_int_mask3_MCPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_mask3_GBBP1WKUP3 : 1;
        unsigned int mcu_wakeup_int_mask3_GBBP2WKUP3 : 1;
        unsigned int mcu_wakeup_int_mask3_WBBP1WKUP : 1;
        unsigned int mcu_wakeup_int_mask3_lte_arm_wakeup_int : 1;
        unsigned int mcu_wakeup_int_mask3_tds_drx_arm_int1 : 1;
        unsigned int mcu_wakeup_int_mask3_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_mask3_IPF_0 : 1;
        unsigned int mcu_wakeup_int_mask3_IPF_1 : 1;
        unsigned int mcu_wakeup_int_mask3_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_mask3_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_mask3_IPC2MCPU_06 : 1;
        unsigned int mcu_wakeup_int_mask3_SEC_IPC2MCPU_01 : 1;
        unsigned int mcu_wakeup_int_mask3 : 11;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer18_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer18_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer19_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MTimer19_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MWatchDog0_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MWatchDog0_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MCPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_MCPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_GBBP1WKUP3_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_GBBP1WKUP3_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_GBBP2WKUP3_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_GBBP2WKUP3_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_WBBP1WKUP_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_WBBP1WKUP_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_lte_arm_wakeup_int_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_lte_arm_wakeup_int_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_tds_drx_arm_int1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_tds_drx_arm_int1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPC2MCPU_01_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPC2MCPU_01_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPF_0_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPF_0_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPF_1_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPF_1_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SOCP_0_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SOCP_0_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SOCP_1_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SOCP_1_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPC2MCPU_06_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_IPC2MCPU_06_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SEC_IPC2MCPU_01_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_SEC_IPC2MCPU_01_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM3_mcu_wakeup_int_mask3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en4_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en4_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en4_MTimer10 : 1;
        unsigned int mcu_wakeup_int_en4_MTimer11 : 1;
        unsigned int mcu_wakeup_int_en4_MTimer12 : 1;
        unsigned int mcu_wakeup_int_en4_MTimer13 : 1;
        unsigned int mcu_wakeup_int_en4_MWatchDog0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_en4_IPC2HIFI_0 : 1;
        unsigned int mcu_wakeup_int_en4_HIFI_NMI_INT : 1;
        unsigned int mcu_wakeup_int_en4_AP_EDMAC_NSORS : 1;
        unsigned int mcu_wakeup_int_en4_MODEM_EDMAC : 1;
        unsigned int mcu_wakeup_int_en4_SEC_IPC2HIFI_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int mcu_wakeup_int_en4 : 16;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_CSYSPWRUPREQ_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_CSYSPWRUPREQ_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_CDBGPWRUPREQ_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_CDBGPWRUPREQ_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer10_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer10_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer11_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer11_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer12_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer12_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer13_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MTimer13_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MWatchDog0_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MWatchDog0_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_HIFI_WKUP_VOTE_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_HIFI_WKUP_VOTE_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_IPC2HIFI_0_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_IPC2HIFI_0_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_HIFI_NMI_INT_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_HIFI_NMI_INT_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_AP_EDMAC_NSORS_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_AP_EDMAC_NSORS_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MODEM_EDMAC_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_MODEM_EDMAC_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_SEC_IPC2HIFI_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_SEC_IPC2HIFI_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN4_mcu_wakeup_int_en4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw4_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw4_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw4_MTimer10 : 1;
        unsigned int mcu_wakeup_int_raw4_MTimer11 : 1;
        unsigned int mcu_wakeup_int_raw4_MTimer12 : 1;
        unsigned int mcu_wakeup_int_raw4_MTimer13 : 1;
        unsigned int mcu_wakeup_int_raw4_MWatchDog0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_raw4_IPC2HIFI_0 : 1;
        unsigned int mcu_wakeup_int_raw4_HIFI_NMI_INT : 1;
        unsigned int mcu_wakeup_int_raw4_AP_EDMAC_NSORS : 1;
        unsigned int mcu_wakeup_int_raw4_MODEM_EDMAC : 1;
        unsigned int mcu_wakeup_int_raw4_SEC_IPC2HIFI_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int mcu_wakeup_int_raw4 : 16;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_CSYSPWRUPREQ_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_CSYSPWRUPREQ_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_CDBGPWRUPREQ_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_CDBGPWRUPREQ_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer10_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer10_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer11_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer11_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer12_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer12_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer13_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MTimer13_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MWatchDog0_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MWatchDog0_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_IPC2HIFI_0_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_IPC2HIFI_0_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_HIFI_NMI_INT_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_HIFI_NMI_INT_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_AP_EDMAC_NSORS_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_AP_EDMAC_NSORS_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MODEM_EDMAC_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_MODEM_EDMAC_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_SEC_IPC2HIFI_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_SEC_IPC2HIFI_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR4_mcu_wakeup_int_raw4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask4_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask4_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask4_MTimer10 : 1;
        unsigned int mcu_wakeup_int_mask4_MTimer11 : 1;
        unsigned int mcu_wakeup_int_mask4_MTimer12 : 1;
        unsigned int mcu_wakeup_int_mask4_MTimer13 : 1;
        unsigned int mcu_wakeup_int_mask4_MWatchDog0 : 1;
        unsigned int reserved_0 : 1;
        unsigned int mcu_wakeup_int_mask4_IPC2HIFI_0 : 1;
        unsigned int mcu_wakeup_int_mask4_HIFI_NMI_INT : 1;
        unsigned int mcu_wakeup_int_mask4_AP_EDMAC_NSORS : 1;
        unsigned int mcu_wakeup_int_mask4_MODEM_EDMAC : 1;
        unsigned int mcu_wakeup_int_mask4_SEC_IPC2HIFI_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int mcu_wakeup_int_mask4 : 16;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_CSYSPWRUPREQ_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_CSYSPWRUPREQ_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_CDBGPWRUPREQ_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_CDBGPWRUPREQ_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer10_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer10_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer11_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer11_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer12_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer12_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer13_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MTimer13_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MWatchDog0_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MWatchDog0_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_IPC2HIFI_0_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_IPC2HIFI_0_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_HIFI_NMI_INT_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_HIFI_NMI_INT_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_AP_EDMAC_NSORS_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_AP_EDMAC_NSORS_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MODEM_EDMAC_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_MODEM_EDMAC_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_SEC_IPC2HIFI_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_SEC_IPC2HIFI_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM4_mcu_wakeup_int_mask4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en0_GPIO0 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO1 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO2 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO3 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO4 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO5 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO6 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO7 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO8 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO9 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO10 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO11 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO12 : 1;
        unsigned int mcu_wakeup_int_en0_GPIO13 : 1;
        unsigned int mcu_wakeup_int_en0_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en0_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_en0_OTG_WKP : 1;
        unsigned int reserved : 1;
        unsigned int mcu_wakeup_int_en0_RTC_INT : 1;
        unsigned int mcu_wakeup_int_en0_Timer0 : 1;
        unsigned int mcu_wakeup_int_en0_Timer1 : 1;
        unsigned int mcu_wakeup_int_en0_Timer2 : 1;
        unsigned int mcu_wakeup_int_en0_Timer3 : 1;
        unsigned int mcu_wakeup_int_en0_Timer4 : 1;
        unsigned int mcu_wakeup_int_en0_Timer5 : 1;
        unsigned int mcu_wakeup_int_en0_Timer6 : 1;
        unsigned int mcu_wakeup_int_en0_Timer7 : 1;
        unsigned int mcu_wakeup_int_en0_Timer8 : 1;
        unsigned int mcu_wakeup_int_en0_Timer9 : 1;
        unsigned int mcu_wakeup_int_en0_Timer10 : 1;
        unsigned int mcu_wakeup_int_en0_Timer11 : 1;
        unsigned int mcu_wakeup_int_en0_Timer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_OTG_WKP_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_OTG_WKP_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN0_mcu_wakeup_int_en0_Timer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw0_GPIO0 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO1 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO2 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO3 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO4 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO5 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO6 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO7 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO8 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO9 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO10 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO11 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO12 : 1;
        unsigned int mcu_wakeup_int_raw0_GPIO13 : 1;
        unsigned int mcu_wakeup_int_raw0_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw0_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_raw0_OTG_WKP : 1;
        unsigned int reserved : 1;
        unsigned int mcu_wakeup_int_raw0_RTC_INT : 1;
        unsigned int mcu_wakeup_int_raw0_Timer0 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer1 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer2 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer3 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer4 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer5 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer6 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer7 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer8 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer9 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer10 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer11 : 1;
        unsigned int mcu_wakeup_int_raw0_Timer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_OTG_WKP_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_OTG_WKP_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR0_mcu_wakeup_int_raw0_Timer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask0_GPIO0 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO1 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO2 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO3 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO4 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO5 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO6 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO7 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO8 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO9 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO10 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO11 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO12 : 1;
        unsigned int mcu_wakeup_int_mask0_GPIO13 : 1;
        unsigned int mcu_wakeup_int_mask0_CSYSPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask0_CDBGPWRUPREQ : 1;
        unsigned int mcu_wakeup_int_mask0_OTG_WKP : 1;
        unsigned int reserved : 1;
        unsigned int mcu_wakeup_int_mask0_RTC_INT : 1;
        unsigned int mcu_wakeup_int_mask0_Timer0 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer1 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer2 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer3 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer4 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer5 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer6 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer7 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer8 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer9 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer10 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer11 : 1;
        unsigned int mcu_wakeup_int_mask0_Timer12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO0_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO0_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO1_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO1_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO2_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO2_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO3_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO3_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO4_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO4_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO5_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO5_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO6_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO6_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO7_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO7_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO8_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO8_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO9_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO9_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO10_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO10_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO11_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO11_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO12_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO12_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO13_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_GPIO13_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_CSYSPWRUPREQ_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_CSYSPWRUPREQ_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_CDBGPWRUPREQ_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_CDBGPWRUPREQ_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_OTG_WKP_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_OTG_WKP_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_RTC_INT_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_RTC_INT_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer0_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer0_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer1_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer1_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer3_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer3_END (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer4_START (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer4_END (23)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer5_START (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer5_END (24)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer6_START (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer6_END (25)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer7_START (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer7_END (26)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer8_START (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer8_END (27)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer9_START (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer9_END (28)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer10_START (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer10_END (29)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer11_START (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer11_END (30)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer12_START (31)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM0_mcu_wakeup_int_mask0_Timer12_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_en1_Timer13 : 1;
        unsigned int mcu_wakeup_int_en1_Timer14 : 1;
        unsigned int mcu_wakeup_int_en1_Timer15 : 1;
        unsigned int mcu_wakeup_int_en1_Timer16 : 1;
        unsigned int mcu_wakeup_int_en1_Timer17 : 1;
        unsigned int mcu_wakeup_int_en1_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_en1_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_en1_MWatchDog2 : 1;
        unsigned int mcu_wakeup_int_en1_ACPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_en1_IPC2ACPU_0 : 1;
        unsigned int mcu_wakeup_int_en1_IPF_0 : 1;
        unsigned int mcu_wakeup_int_en1_IPF_1 : 1;
        unsigned int mcu_wakeup_int_en1_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_en1_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_en1_GPIO14 : 1;
        unsigned int mcu_wakeup_int_en1_GPIO15 : 1;
        unsigned int mcu_wakeup_int_en1_GPIO16 : 1;
        unsigned int mcu_wakeup_int_en1_GPIO17 : 1;
        unsigned int mcu_wakeup_int_en1_GPIO18 : 1;
        unsigned int mcu_wakeup_int_en1_gpio19 : 1;
        unsigned int mcu_wakeup_int_en1_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_en1_SEC_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_en1 : 10;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_Timer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_WatchDog0_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_WatchDog0_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_WatchDog1_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_WatchDog1_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_MWatchDog2_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_MWatchDog2_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_ACPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_ACPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPC2ACPU_0_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPC2ACPU_0_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPF_0_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPF_0_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPF_1_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPF_1_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SOCP_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SOCP_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SOCP_1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SOCP_1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO14_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO14_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO15_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO15_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO16_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO16_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO17_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO17_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO18_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_GPIO18_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_gpio19_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_gpio19_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPC2ACPU_2_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_IPC2ACPU_2_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SEC_IPC2ACPU_2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_SEC_IPC2ACPU_2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_EN1_mcu_wakeup_int_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_raw1_Timer13 : 1;
        unsigned int mcu_wakeup_int_raw1_Timer14 : 1;
        unsigned int mcu_wakeup_int_raw1_Timer15 : 1;
        unsigned int mcu_wakeup_int_raw1_Timer16 : 1;
        unsigned int mcu_wakeup_int_raw1_Timer17 : 1;
        unsigned int mcu_wakeup_int_raw1_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_raw1_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_raw1_MWatchDog2 : 1;
        unsigned int mcu_wakeup_int_raw1_ACPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_raw1_IPC2ACPU_0 : 1;
        unsigned int mcu_wakeup_int_raw1_IPF_0 : 1;
        unsigned int mcu_wakeup_int_raw1_IPF_1 : 1;
        unsigned int mcu_wakeup_int_raw1_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_raw1_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_raw1_GPIO14 : 1;
        unsigned int mcu_wakeup_int_raw1_GPIO15 : 1;
        unsigned int mcu_wakeup_int_raw1_GPIO16 : 1;
        unsigned int mcu_wakeup_int_raw1_GPIO17 : 1;
        unsigned int mcu_wakeup_int_raw1_GPIO18 : 1;
        unsigned int mcu_wakeup_int_raw1_gpio19 : 1;
        unsigned int mcu_wakeup_int_raw1_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_raw1_SEC_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_raw1 : 10;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_Timer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_WatchDog0_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_WatchDog0_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_WatchDog1_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_WatchDog1_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_MWatchDog2_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_MWatchDog2_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_ACPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_ACPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPC2ACPU_0_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPC2ACPU_0_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPF_0_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPF_0_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPF_1_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPF_1_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SOCP_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SOCP_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SOCP_1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SOCP_1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO14_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO14_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO15_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO15_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO16_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO16_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO17_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO17_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO18_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_GPIO18_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_gpio19_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_gpio19_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPC2ACPU_2_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_IPC2ACPU_2_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SEC_IPC2ACPU_2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_SEC_IPC2ACPU_2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATR1_mcu_wakeup_int_raw1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_wakeup_int_mask1_Timer13 : 1;
        unsigned int mcu_wakeup_int_mask1_Timer14 : 1;
        unsigned int mcu_wakeup_int_mask1_Timer15 : 1;
        unsigned int mcu_wakeup_int_mask1_Timer16 : 1;
        unsigned int mcu_wakeup_int_mask1_Timer17 : 1;
        unsigned int mcu_wakeup_int_mask1_WatchDog0 : 1;
        unsigned int mcu_wakeup_int_mask1_WatchDog1 : 1;
        unsigned int mcu_wakeup_int_mask1_MWatchDog2 : 1;
        unsigned int mcu_wakeup_int_mask1_ACPU_WKUP_VOTE : 1;
        unsigned int mcu_wakeup_int_mask1_IPC2ACPU_0 : 1;
        unsigned int mcu_wakeup_int_mask1_IPF_0 : 1;
        unsigned int mcu_wakeup_int_mask1_IPF_1 : 1;
        unsigned int mcu_wakeup_int_mask1_SOCP_0 : 1;
        unsigned int mcu_wakeup_int_mask1_SOCP_1 : 1;
        unsigned int mcu_wakeup_int_mask1_GPIO14 : 1;
        unsigned int mcu_wakeup_int_mask1_GPIO15 : 1;
        unsigned int mcu_wakeup_int_mask1_GPIO16 : 1;
        unsigned int mcu_wakeup_int_mask1_GPIO17 : 1;
        unsigned int mcu_wakeup_int_mask1_GPIO18 : 1;
        unsigned int mcu_wakeup_int_mask1_gpio19 : 1;
        unsigned int mcu_wakeup_int_mask1_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_mask1_SEC_IPC2ACPU_2 : 1;
        unsigned int mcu_wakeup_int_mask1 : 10;
    } reg;
} SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer13_START (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer13_END (0)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer14_START (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer14_END (1)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer15_START (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer15_END (2)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer16_START (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer16_END (3)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer17_START (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_Timer17_END (4)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_WatchDog0_START (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_WatchDog0_END (5)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_WatchDog1_START (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_WatchDog1_END (6)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_MWatchDog2_START (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_MWatchDog2_END (7)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_ACPU_WKUP_VOTE_START (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_ACPU_WKUP_VOTE_END (8)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPC2ACPU_0_START (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPC2ACPU_0_END (9)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPF_0_START (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPF_0_END (10)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPF_1_START (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPF_1_END (11)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SOCP_0_START (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SOCP_0_END (12)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SOCP_1_START (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SOCP_1_END (13)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO14_START (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO14_END (14)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO15_START (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO15_END (15)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO16_START (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO16_END (16)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO17_START (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO17_END (17)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO18_START (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_GPIO18_END (18)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_gpio19_START (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_gpio19_END (19)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPC2ACPU_2_START (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_IPC2ACPU_2_END (20)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SEC_IPC2ACPU_2_START (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_SEC_IPC2ACPU_2_END (21)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_START (22)
#define SOC_AO_SCTRL_SC_MCU_WKUP_INT_STATM1_mcu_wakeup_int_mask1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_en_sta_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_en_sta_2hifiwd : 1;
        unsigned int sc_int_en_sta_3bakwd : 1;
        unsigned int sc_int_en_sta_4cwd : 1;
        unsigned int sc_int_en_sta_5vote0mcuei : 1;
        unsigned int sc_int_en_sta_6vote0mcudi : 1;
        unsigned int sc_int_en_sta_7vote1mcuei : 1;
        unsigned int sc_int_en_sta_8vote1mcudi : 1;
        unsigned int sc_int_en_sta_9cei : 1;
        unsigned int sc_int_en_sta_10cdi : 1;
        unsigned int sc_int_en_sta_11aei : 1;
        unsigned int sc_int_en_sta_12adi : 1;
        unsigned int sc_int_en_sta_13vote2mcudi : 1;
        unsigned int sc_int_en_sta_14vote0mcuei : 1;
        unsigned int sc_int_en_sta_15periei : 1;
        unsigned int sc_int_en_sta_16peridi : 1;
        unsigned int sc_int_en_sta_17vote0aarmei : 1;
        unsigned int sc_int_en_sta_18vote0aarmdi : 1;
        unsigned int sc_int_en_sta_19vote1aarmei : 1;
        unsigned int sc_int_en_sta_20vote1aarmdi : 1;
        unsigned int sc_int_en_sta_21vote2aarmdi : 1;
        unsigned int sc_int_en_sta_22vote0aarmei : 1;
        unsigned int sc_int_en_sta_23vote0carmei : 1;
        unsigned int sc_int_en_sta_24vote0carmdi : 1;
        unsigned int sc_int_en_sta_25vote1carmei : 1;
        unsigned int sc_int_en_sta_26vote1carmdi : 1;
        unsigned int sc_int_en_sta_27vote2hifidi : 1;
        unsigned int sc_int_en_sta_28vote0hifiei : 1;
        unsigned int sc_int_en_sta_29otgchg : 1;
        unsigned int sc_int_en_sta_30otgdat : 1;
        unsigned int sc_int_en_sta_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_EN_STAT_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_EN_STAT_sc_int_en_sta_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_statr_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_statr_2hifiwd : 1;
        unsigned int sc_int_statr_3bakwd : 1;
        unsigned int sc_int_statr_4cwd : 1;
        unsigned int sc_int_statr_5vote0mcuei : 1;
        unsigned int sc_int_statr_6vote0mcudi : 1;
        unsigned int sc_int_statr_7vote1mcuei : 1;
        unsigned int sc_int_statr_8vote1mcudi : 1;
        unsigned int sc_int_statr_9cei : 1;
        unsigned int sc_int_statr_10cdi : 1;
        unsigned int sc_int_statr_11aei : 1;
        unsigned int sc_int_statr_12adi : 1;
        unsigned int sc_int_statr_13vote2mcudi : 1;
        unsigned int sc_int_statr_14vote0mcuei : 1;
        unsigned int sc_int_statr_15periei : 1;
        unsigned int sc_int_statr_16peridi : 1;
        unsigned int sc_int_statr_17vote0aarmei : 1;
        unsigned int sc_int_statr_18vote0aarmdi : 1;
        unsigned int sc_int_statr_19vote1aarmei : 1;
        unsigned int sc_int_statr_20vote1aarmdi : 1;
        unsigned int sc_int_statr_21vote2aarmdi : 1;
        unsigned int sc_int_statr_22vote0aarmei : 1;
        unsigned int sc_int_statr_23vote0carmei : 1;
        unsigned int sc_int_statr_24vote0carmdi : 1;
        unsigned int sc_int_statr_25vote1carmei : 1;
        unsigned int sc_int_statr_26vote1carmdi : 1;
        unsigned int sc_int_statr_27vote2hifidi : 1;
        unsigned int sc_int_statr_28vote0hifiei : 1;
        unsigned int sc_int_statr_29otgchg : 1;
        unsigned int sc_int_statr_30otgdat : 1;
        unsigned int sc_int_statr_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_STATR_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_STATR_sc_int_statr_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_statm_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_statm_2hifiwd : 1;
        unsigned int sc_int_statm_3bakwd : 1;
        unsigned int sc_int_statm_4cwd : 1;
        unsigned int sc_int_statm_5vote0mcuei : 1;
        unsigned int sc_int_statm_6vote0mcudi : 1;
        unsigned int sc_int_statm_7vote1mcuei : 1;
        unsigned int sc_int_statm_8vote1mcudi : 1;
        unsigned int sc_int_statm_9cei : 1;
        unsigned int sc_int_statm_10cdi : 1;
        unsigned int sc_int_statm_11aei : 1;
        unsigned int sc_int_statm_12adi : 1;
        unsigned int sc_int_statm_13vote2mcudi : 1;
        unsigned int sc_int_statm_14vote0mcuei : 1;
        unsigned int sc_int_statm_15periei : 1;
        unsigned int sc_int_statm_16peridi : 1;
        unsigned int sc_int_statm_17vote0aarmei : 1;
        unsigned int sc_int_statm_18vote0aarmdi : 1;
        unsigned int sc_int_statm_19vote1aarmei : 1;
        unsigned int sc_int_statm_20vote1aarmdi : 1;
        unsigned int sc_int_statm_21vote2aarmdi : 1;
        unsigned int sc_int_statm_22vote0aarmei : 1;
        unsigned int sc_int_statm_23vote0carmei : 1;
        unsigned int sc_int_statm_24vote0carmdi : 1;
        unsigned int sc_int_statm_25vote1carmei : 1;
        unsigned int sc_int_statm_26vote1carmdi : 1;
        unsigned int sc_int_statm_27vote2hifidi : 1;
        unsigned int sc_int_statm_28vote0hifiei : 1;
        unsigned int sc_int_statm_29otgchg : 1;
        unsigned int sc_int_statm_30otgdat : 1;
        unsigned int sc_int_statm_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_STATM_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_STATM_sc_int_statm_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_clear_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_clear_2hifiwd : 1;
        unsigned int sc_int_clear_3bakwd : 1;
        unsigned int sc_int_clear_4cwd : 1;
        unsigned int sc_int_clear_5vote0mcuei : 1;
        unsigned int sc_int_clear_6vote0mcudi : 1;
        unsigned int sc_int_clear_7vote1mcuei : 1;
        unsigned int sc_int_clear_8vote1mcudi : 1;
        unsigned int sc_int_clear_9cei : 1;
        unsigned int sc_int_clear_10cdi : 1;
        unsigned int sc_int_clear_11aei : 1;
        unsigned int sc_int_clear_12adi : 1;
        unsigned int sc_int_clear_13vote2mcudi : 1;
        unsigned int sc_int_clear_14vote0mcuei : 1;
        unsigned int sc_int_clear_15periei : 1;
        unsigned int sc_int_clear_16peridi : 1;
        unsigned int sc_int_clear_17vote0aarmei : 1;
        unsigned int sc_int_clear_18vote0aarmdi : 1;
        unsigned int sc_int_clear_19vote1aarmei : 1;
        unsigned int sc_int_clear_20vote1aarmdi : 1;
        unsigned int sc_int_clear_21vote2aarmdi : 1;
        unsigned int sc_int_clear_22vote0aarmei : 1;
        unsigned int sc_int_clear_23vote0carmei : 1;
        unsigned int sc_int_clear_24vote0carmdi : 1;
        unsigned int sc_int_clear_25vote1carmei : 1;
        unsigned int sc_int_clear_26vote1carmdi : 1;
        unsigned int sc_int_clear_27vote2hifidi : 1;
        unsigned int sc_int_clear_28vote0hifiei : 1;
        unsigned int sc_int_clear_29otgchg : 1;
        unsigned int sc_int_clear_30otgdat : 1;
        unsigned int sc_int_clear_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_CLEAR_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_CLEAR_sc_int_clear_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_en0_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_en0_2hifiwd : 1;
        unsigned int sc_int_en0_3bakwd : 1;
        unsigned int sc_int_en0_4cwd : 1;
        unsigned int sc_int_en0_5vote0mcuei : 1;
        unsigned int sc_int_en0_6vote0mcudi : 1;
        unsigned int sc_int_en0_7vote1mcuei : 1;
        unsigned int sc_int_en0_8vote1mcudi : 1;
        unsigned int sc_int_en0_9cei : 1;
        unsigned int sc_int_en0_10cdi : 1;
        unsigned int sc_int_en0_11aei : 1;
        unsigned int sc_int_en0_12adi : 1;
        unsigned int sc_int_en0_13vote2mcudi : 1;
        unsigned int sc_int_en0_14vote0mcuei : 1;
        unsigned int sc_int_en0_15periei : 1;
        unsigned int sc_int_en0_16peridi : 1;
        unsigned int sc_int_en0_17vote0aarmei : 1;
        unsigned int sc_int_en0_18vote0aarmdi : 1;
        unsigned int sc_int_en0_19vote1aarmei : 1;
        unsigned int sc_int_en0_20vote1aarmdi : 1;
        unsigned int sc_int_en0_21vote2aarmdi : 1;
        unsigned int sc_int_en0_22vote0aarmei : 1;
        unsigned int sc_int_en0_23vote0carmei : 1;
        unsigned int sc_int_en0_24vote0carmdi : 1;
        unsigned int sc_int_en0_25vote1carmei : 1;
        unsigned int sc_int_en0_26vote1carmdi : 1;
        unsigned int sc_int_en0_27vote2hifidi : 1;
        unsigned int sc_int_en0_28vote0hifiei : 1;
        unsigned int sc_int_en0_29otgchg : 1;
        unsigned int sc_int_en0_30otgdat : 1;
        unsigned int sc_int_en0_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_EN0_sc_int_en0_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_int_dis0_0awd : 1;
        unsigned int reserved : 1;
        unsigned int sc_int_dis0_2hifiwd : 1;
        unsigned int sc_int_dis0_3bakwd : 1;
        unsigned int sc_int_dis0_4cwd : 1;
        unsigned int sc_int_dis0_5vote0mcuei : 1;
        unsigned int sc_int_dis0_6vote0mcudi : 1;
        unsigned int sc_int_dis0_7vote1mcuei : 1;
        unsigned int sc_int_dis0_8vote1mcudi : 1;
        unsigned int sc_int_dis0_9cei : 1;
        unsigned int sc_int_dis0_10cdi : 1;
        unsigned int sc_int_dis0_11aei : 1;
        unsigned int sc_int_dis0_12adi : 1;
        unsigned int sc_int_dis0_13vote2mcudi : 1;
        unsigned int sc_int_dis0_14vote0mcuei : 1;
        unsigned int sc_int_dis0_15periei : 1;
        unsigned int sc_int_dis0_16peridi : 1;
        unsigned int sc_int_dis0_17vote0aarmei : 1;
        unsigned int sc_int_dis0_18vote0aarmdi : 1;
        unsigned int sc_int_dis0_19vote1aarmei : 1;
        unsigned int sc_int_dis0_20vote1aarmdi : 1;
        unsigned int sc_int_dis0_21vote2aarmdi : 1;
        unsigned int sc_int_dis0_22vote0aarmei : 1;
        unsigned int sc_int_dis0_23vote0carmei : 1;
        unsigned int sc_int_dis0_24vote0carmdi : 1;
        unsigned int sc_int_dis0_25vote1carmei : 1;
        unsigned int sc_int_dis0_26vote1carmdi : 1;
        unsigned int sc_int_dis0_27vote2hifidi : 1;
        unsigned int sc_int_dis0_28vote0hifiei : 1;
        unsigned int sc_int_dis0_29otgchg : 1;
        unsigned int sc_int_dis0_30otgdat : 1;
        unsigned int sc_int_dis0_31otgchirpon : 1;
    } reg;
} SOC_AO_SCTRL_SC_INT_DIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_0awd_START (0)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_0awd_END (0)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_2hifiwd_START (2)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_2hifiwd_END (2)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_3bakwd_START (3)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_3bakwd_END (3)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_4cwd_START (4)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_4cwd_END (4)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_5vote0mcuei_START (5)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_5vote0mcuei_END (5)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_6vote0mcudi_START (6)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_6vote0mcudi_END (6)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_7vote1mcuei_START (7)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_7vote1mcuei_END (7)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_8vote1mcudi_START (8)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_8vote1mcudi_END (8)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_9cei_START (9)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_9cei_END (9)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_10cdi_START (10)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_10cdi_END (10)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_11aei_START (11)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_11aei_END (11)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_12adi_START (12)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_12adi_END (12)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_13vote2mcudi_START (13)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_13vote2mcudi_END (13)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_14vote0mcuei_START (14)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_14vote0mcuei_END (14)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_15periei_START (15)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_15periei_END (15)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_16peridi_START (16)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_16peridi_END (16)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_17vote0aarmei_START (17)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_17vote0aarmei_END (17)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_18vote0aarmdi_START (18)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_18vote0aarmdi_END (18)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_19vote1aarmei_START (19)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_19vote1aarmei_END (19)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_20vote1aarmdi_START (20)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_20vote1aarmdi_END (20)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_21vote2aarmdi_START (21)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_21vote2aarmdi_END (21)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_22vote0aarmei_START (22)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_22vote0aarmei_END (22)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_23vote0carmei_START (23)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_23vote0carmei_END (23)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_24vote0carmdi_START (24)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_24vote0carmdi_END (24)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_25vote1carmei_START (25)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_25vote1carmei_END (25)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_26vote1carmdi_START (26)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_26vote1carmdi_END (26)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_27vote2hifidi_START (27)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_27vote2hifidi_END (27)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_28vote0hifiei_START (28)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_28vote0hifiei_END (28)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_29otgchg_START (29)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_29otgchg_END (29)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_30otgdat_START (30)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_30otgdat_END (30)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_31otgchirpon_START (31)
#define SOC_AO_SCTRL_SC_INT_DIS0_sc_int_dis0_31otgchirpon_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdg_core_rst_x2xcrg_drst : 1;
        unsigned int brg_err_clr : 31;
    } reg;
} SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_UNION;
#endif
#define SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_wdg_core_rst_x2xcrg_drst_START (0)
#define SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_wdg_core_rst_x2xcrg_drst_END (0)
#define SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_brg_err_clr_START (1)
#define SOC_AO_SCTRL_SC_BRG_ERR_CLEAR_brg_err_clr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en0_1acpu_dualtimer0_en0 : 2;
        unsigned int timer_en0_3acpu_dualtimer0_en1 : 2;
        unsigned int timer_en0_5acpu_dualtimer1_en0 : 2;
        unsigned int timer_en0_7acpu_dualtimer1_en1 : 2;
        unsigned int timer_en0_9acpu_dualtimer2_en0 : 2;
        unsigned int timer_en0_11acpu_dualtimer2_en1 : 2;
        unsigned int timer_en0_13acpu_dualtimer3_en0 : 2;
        unsigned int timer_en0_15acpu_dualtimer3_en1 : 2;
        unsigned int timer_en0_msk_1acpu_dualtimer0_en0 : 2;
        unsigned int timer_en0_msk_3acpu_dualtimer0_en1 : 2;
        unsigned int timer_en0_msk_5acpu_dualtimer1_en0 : 2;
        unsigned int timer_en0_msk_7acpu_dualtimer1_en1 : 2;
        unsigned int timer_en0_msk_9acpu_dualtimer2_en0 : 2;
        unsigned int timer_en0_msk_11acpu_dualtimer2_en1 : 2;
        unsigned int timer_en0_msk_13acpu_dualtimer3_en0 : 2;
        unsigned int timer_en0_msk_15acpu_dualtimer3_en1 : 2;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_1acpu_dualtimer0_en0_END (1)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_START (2)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_3acpu_dualtimer0_en1_END (3)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_START (4)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_5acpu_dualtimer1_en0_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_7acpu_dualtimer1_en1_END (7)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_START (8)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_9acpu_dualtimer2_en0_END (9)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_START (10)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_11acpu_dualtimer2_en1_END (11)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_START (12)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_13acpu_dualtimer3_en0_END (13)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_START (14)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_15acpu_dualtimer3_en1_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_1acpu_dualtimer0_en0_END (17)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_START (18)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_3acpu_dualtimer0_en1_END (19)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_START (20)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_5acpu_dualtimer1_en0_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_7acpu_dualtimer1_en1_END (23)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_START (24)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_9acpu_dualtimer2_en0_END (25)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_START (26)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_11acpu_dualtimer2_en1_END (27)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_START (28)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_13acpu_dualtimer3_en0_END (29)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_START (30)
#define SOC_AO_SCTRL_SC_TIMER_EN0_timer_en0_msk_15acpu_dualtimer3_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en1_1acpu_dualtimer4_en0 : 2;
        unsigned int timer_en1_3acpu_dualtimer4_en1 : 2;
        unsigned int timer_en1_5acpu_dualtimer5_en0 : 2;
        unsigned int timer_en1_7acpu_dualtimer5_en1 : 2;
        unsigned int timer_en1_9acpu_dualtimer6_en0 : 2;
        unsigned int timer_en1_11acpu_dualtimer6_en1 : 2;
        unsigned int timer_en1_13acpu_dualtimer7_en0 : 2;
        unsigned int timer_en1_15acpu_dualtimer7_en1 : 2;
        unsigned int timer_en1_msk_1acpu_dualtimer4_en0 : 2;
        unsigned int timer_en1_msk_3acpu_dualtimer4_en1 : 2;
        unsigned int timer_en1_msk_5acpu_dualtimer5_en0 : 2;
        unsigned int timer_en1_msk_7acpu_dualtimer5_en1 : 2;
        unsigned int timer_en1_msk_9acpu_dualtimer6_en0 : 2;
        unsigned int timer_en1_msk_11acpu_dualtimer6_en1 : 2;
        unsigned int timer_en1_msk_13acpu_dualtimer7_en0 : 2;
        unsigned int timer_en1_msk_15acpu_dualtimer7_en1 : 2;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_1acpu_dualtimer4_en0_END (1)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_3acpu_dualtimer4_en1_START (2)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_3acpu_dualtimer4_en1_END (3)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_5acpu_dualtimer5_en0_START (4)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_5acpu_dualtimer5_en0_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_7acpu_dualtimer5_en1_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_7acpu_dualtimer5_en1_END (7)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_9acpu_dualtimer6_en0_START (8)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_9acpu_dualtimer6_en0_END (9)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_11acpu_dualtimer6_en1_START (10)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_11acpu_dualtimer6_en1_END (11)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_13acpu_dualtimer7_en0_START (12)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_13acpu_dualtimer7_en0_END (13)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_15acpu_dualtimer7_en1_START (14)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_15acpu_dualtimer7_en1_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_1acpu_dualtimer4_en0_END (17)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_3acpu_dualtimer4_en1_START (18)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_3acpu_dualtimer4_en1_END (19)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_5acpu_dualtimer5_en0_START (20)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_5acpu_dualtimer5_en0_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_7acpu_dualtimer5_en1_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_7acpu_dualtimer5_en1_END (23)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_9acpu_dualtimer6_en0_START (24)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_9acpu_dualtimer6_en0_END (25)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_11acpu_dualtimer6_en1_START (26)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_11acpu_dualtimer6_en1_END (27)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_13acpu_dualtimer7_en0_START (28)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_13acpu_dualtimer7_en0_END (29)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_15acpu_dualtimer7_en1_START (30)
#define SOC_AO_SCTRL_SC_TIMER_EN1_timer_en1_msk_15acpu_dualtimer7_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en2_1mcpu_dualtimer0_en0 : 2;
        unsigned int timer_en2_3mcpu_dualtimer0_en1 : 2;
        unsigned int timer_en2_5mcpu_dualtimer1_en0 : 2;
        unsigned int timer_en2_7mcpu_dualtimer1_en1 : 2;
        unsigned int timer_en2_9mcpu_dualtimer2_en0 : 2;
        unsigned int timer_en2_11mcpu_dualtimer2_en1 : 2;
        unsigned int timer_en2_13mcpu_dualtimer3_en0 : 2;
        unsigned int timer_en2_15mcpu_dualtimer3_en1 : 2;
        unsigned int timer_en2_msk_1mcpu_dualtimer0_en0 : 2;
        unsigned int timer_en2_msk_3mcpu_dualtimer0_en1 : 2;
        unsigned int timer_en2_msk_5mcpu_dualtimer1_en0 : 2;
        unsigned int timer_en2_msk_7mcpu_dualtimer1_en1 : 2;
        unsigned int timer_en2_msk_9mcpu_dualtimer2_en0 : 2;
        unsigned int timer_en2_msk_11mcpu_dualtimer2_en1 : 2;
        unsigned int timer_en2_msk_13mcpu_dualtimer3_en0 : 2;
        unsigned int timer_en2_msk_15mcpu_dualtimer3_en1 : 2;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN2_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_1mcpu_dualtimer0_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_1mcpu_dualtimer0_en0_END (1)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_3mcpu_dualtimer0_en1_START (2)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_3mcpu_dualtimer0_en1_END (3)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_5mcpu_dualtimer1_en0_START (4)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_5mcpu_dualtimer1_en0_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_7mcpu_dualtimer1_en1_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_7mcpu_dualtimer1_en1_END (7)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_9mcpu_dualtimer2_en0_START (8)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_9mcpu_dualtimer2_en0_END (9)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_11mcpu_dualtimer2_en1_START (10)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_11mcpu_dualtimer2_en1_END (11)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_13mcpu_dualtimer3_en0_START (12)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_13mcpu_dualtimer3_en0_END (13)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_15mcpu_dualtimer3_en1_START (14)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_15mcpu_dualtimer3_en1_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_1mcpu_dualtimer0_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_1mcpu_dualtimer0_en0_END (17)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_3mcpu_dualtimer0_en1_START (18)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_3mcpu_dualtimer0_en1_END (19)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_5mcpu_dualtimer1_en0_START (20)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_5mcpu_dualtimer1_en0_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_7mcpu_dualtimer1_en1_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_7mcpu_dualtimer1_en1_END (23)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_9mcpu_dualtimer2_en0_START (24)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_9mcpu_dualtimer2_en0_END (25)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_11mcpu_dualtimer2_en1_START (26)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_11mcpu_dualtimer2_en1_END (27)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_13mcpu_dualtimer3_en0_START (28)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_13mcpu_dualtimer3_en0_END (29)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_15mcpu_dualtimer3_en1_START (30)
#define SOC_AO_SCTRL_SC_TIMER_EN2_timer_en2_msk_15mcpu_dualtimer3_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en3_1mcpu_dualtimer4_en0 : 2;
        unsigned int timer_en3_3mcpu_dualtimer4_en1 : 2;
        unsigned int timer_en3_5mcpu_dualtimer5_en0 : 2;
        unsigned int timer_en3_7mcpu_dualtimer5_en1 : 2;
        unsigned int timer_en3_9mcpu_dualtimer6_en0 : 2;
        unsigned int timer_en3_11mcpu_dualtimer6_en1 : 2;
        unsigned int timer_en3_13mcpu_dualtimer7_en0 : 2;
        unsigned int timer_en3_15mcpu_dualtimer7_en1 : 2;
        unsigned int timer_en3_msk_1mcpu_dualtimer4_en0 : 2;
        unsigned int timer_en3_msk_3mcpu_dualtimer4_en1 : 2;
        unsigned int timer_en3_msk_5mcpu_dualtimer5_en0 : 2;
        unsigned int timer_en3_msk_7mcpu_dualtimer5_en1 : 2;
        unsigned int timer_en3_msk_9mcpu_dualtimer6_en0 : 2;
        unsigned int timer_en3_msk_11mcpu_dualtimer6_en1 : 2;
        unsigned int timer_en3_msk_13mcpu_dualtimer7_en0 : 2;
        unsigned int timer_en3_msk_15mcpu_dualtimer7_en1 : 2;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN3_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_1mcpu_dualtimer4_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_1mcpu_dualtimer4_en0_END (1)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_3mcpu_dualtimer4_en1_START (2)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_3mcpu_dualtimer4_en1_END (3)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_5mcpu_dualtimer5_en0_START (4)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_5mcpu_dualtimer5_en0_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_7mcpu_dualtimer5_en1_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_7mcpu_dualtimer5_en1_END (7)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_9mcpu_dualtimer6_en0_START (8)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_9mcpu_dualtimer6_en0_END (9)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_11mcpu_dualtimer6_en1_START (10)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_11mcpu_dualtimer6_en1_END (11)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_13mcpu_dualtimer7_en0_START (12)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_13mcpu_dualtimer7_en0_END (13)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_15mcpu_dualtimer7_en1_START (14)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_15mcpu_dualtimer7_en1_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_1mcpu_dualtimer4_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_1mcpu_dualtimer4_en0_END (17)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_3mcpu_dualtimer4_en1_START (18)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_3mcpu_dualtimer4_en1_END (19)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_5mcpu_dualtimer5_en0_START (20)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_5mcpu_dualtimer5_en0_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_7mcpu_dualtimer5_en1_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_7mcpu_dualtimer5_en1_END (23)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_9mcpu_dualtimer6_en0_START (24)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_9mcpu_dualtimer6_en0_END (25)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_11mcpu_dualtimer6_en1_START (26)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_11mcpu_dualtimer6_en1_END (27)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_13mcpu_dualtimer7_en0_START (28)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_13mcpu_dualtimer7_en0_END (29)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_15mcpu_dualtimer7_en1_START (30)
#define SOC_AO_SCTRL_SC_TIMER_EN3_timer_en3_msk_15mcpu_dualtimer7_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en4_acpu_dualtimer9_en0 : 2;
        unsigned int timer_en4_3acpu_dualtimer9_en1 : 2;
        unsigned int timer_en4_5acpu_dualtimer10_en0 : 2;
        unsigned int timer_en4_7acpu_dualtimer10_en1 : 2;
        unsigned int timer_en4_9mcpu_dualtimer8_en0 : 2;
        unsigned int timer_en4_11mcpu_dualtimer8_en1 : 2;
        unsigned int timer_en4_13mcpu_dualtimer9_en0 : 2;
        unsigned int timer_en4_15mcpu_dualtimer9_en1 : 2;
        unsigned int timer_en4_msk_acpu_dualtimer9_en0 : 2;
        unsigned int timer_en4_msk_3acpu_dualtimer9_en1 : 2;
        unsigned int timer_en4_msk_5acpu_dualtimer10_en0 : 2;
        unsigned int timer_en4_msk_7acpu_dualtimer10_en1 : 2;
        unsigned int timer_en4_msk_9mcpu_dualtimer8_en0 : 2;
        unsigned int timer_en4_msk_11mcpu_dualtimer8_en1 : 2;
        unsigned int timer_en4_msk_13mcpu_dualtimer9_en0 : 2;
        unsigned int timer_en4_msk_15mcpu_dualtimer9_en1 : 2;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN4_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_acpu_dualtimer9_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_acpu_dualtimer9_en0_END (1)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_3acpu_dualtimer9_en1_START (2)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_3acpu_dualtimer9_en1_END (3)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_5acpu_dualtimer10_en0_START (4)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_5acpu_dualtimer10_en0_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_7acpu_dualtimer10_en1_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_7acpu_dualtimer10_en1_END (7)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_9mcpu_dualtimer8_en0_START (8)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_9mcpu_dualtimer8_en0_END (9)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_11mcpu_dualtimer8_en1_START (10)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_11mcpu_dualtimer8_en1_END (11)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_13mcpu_dualtimer9_en0_START (12)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_13mcpu_dualtimer9_en0_END (13)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_15mcpu_dualtimer9_en1_START (14)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_15mcpu_dualtimer9_en1_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_acpu_dualtimer9_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_acpu_dualtimer9_en0_END (17)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_3acpu_dualtimer9_en1_START (18)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_3acpu_dualtimer9_en1_END (19)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_5acpu_dualtimer10_en0_START (20)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_5acpu_dualtimer10_en0_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_7acpu_dualtimer10_en1_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_7acpu_dualtimer10_en1_END (23)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_9mcpu_dualtimer8_en0_START (24)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_9mcpu_dualtimer8_en0_END (25)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_11mcpu_dualtimer8_en1_START (26)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_11mcpu_dualtimer8_en1_END (27)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_13mcpu_dualtimer9_en0_START (28)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_13mcpu_dualtimer9_en0_END (29)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_15mcpu_dualtimer9_en1_START (30)
#define SOC_AO_SCTRL_SC_TIMER_EN4_timer_en4_msk_15mcpu_dualtimer9_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer_en5_acpu_dualtimer8_en0 : 3;
        unsigned int timer_en5_acpu_dualtimer8_en1 : 3;
        unsigned int timer_en5_reserved : 10;
        unsigned int timer_en5_msk_acpu_dualtimer8_en0 : 3;
        unsigned int timer_en5_msk_acpu_dualtimer8_en1 : 3;
        unsigned int timer_en5_msk : 10;
    } reg;
} SOC_AO_SCTRL_SC_TIMER_EN5_UNION;
#endif
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_acpu_dualtimer8_en0_START (0)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_acpu_dualtimer8_en0_END (2)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_acpu_dualtimer8_en1_START (3)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_acpu_dualtimer8_en1_END (5)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_reserved_START (6)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_reserved_END (15)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_acpu_dualtimer8_en0_START (16)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_acpu_dualtimer8_en0_END (18)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_acpu_dualtimer8_en1_START (19)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_acpu_dualtimer8_en1_END (21)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_START (22)
#define SOC_AO_SCTRL_SC_TIMER_EN5_timer_en5_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time12_cm3mem : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME12_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME12_pwup_time12_cm3mem_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME12_pwup_time12_cm3mem_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int reserved_1: 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME13_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int reserved_1: 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME14_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int reserved_1: 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME15_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int reserved_1: 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME16_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 16;
        unsigned int reserved_1: 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME17_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved31 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED31_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED31_sc_reserved31_START (0)
#define SOC_AO_SCTRL_SC_RESERVED31_sc_reserved31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved32 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED32_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED32_sc_reserved32_START (0)
#define SOC_AO_SCTRL_SC_RESERVED32_sc_reserved32_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved33 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED33_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED33_sc_reserved33_START (0)
#define SOC_AO_SCTRL_SC_RESERVED33_sc_reserved33_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved34 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED34_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED34_sc_reserved34_START (0)
#define SOC_AO_SCTRL_SC_RESERVED34_sc_reserved34_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved35 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED35_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED35_sc_reserved35_START (0)
#define SOC_AO_SCTRL_SC_RESERVED35_sc_reserved35_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved36 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED36_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED36_sc_reserved36_START (0)
#define SOC_AO_SCTRL_SC_RESERVED36_sc_reserved36_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved37 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED37_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED37_sc_reserved37_START (0)
#define SOC_AO_SCTRL_SC_RESERVED37_sc_reserved37_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_reserved38 : 32;
    } reg;
} SOC_AO_SCTRL_SC_RESERVED38_UNION;
#endif
#define SOC_AO_SCTRL_SC_RESERVED38_sc_reserved38_START (0)
#define SOC_AO_SCTRL_SC_RESERVED38_sc_reserved38_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int reserved_1 : 1;
        unsigned int mcu_subsys_ctrl0 : 23;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL0_mcu_subsys_ctrl0_START (9)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL0_mcu_subsys_ctrl0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_ctrl1_dbgen_dapenable : 1;
        unsigned int mcu_subsys_ctrl1_dbgen_stcalib : 26;
        unsigned int mcu_subsys_ctrl1_ddrrmpenable : 1;
        unsigned int mcu_subsys_ctrl1 : 4;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_dbgen_dapenable_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_dbgen_dapenable_END (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_dbgen_stcalib_START (1)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_dbgen_stcalib_END (26)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_ddrrmpenable_START (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_ddrrmpenable_END (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_START (28)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL1_mcu_subsys_ctrl1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_ctrl2 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL2_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL2_mcu_subsys_ctrl2_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL2_mcu_subsys_ctrl2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 3;
        unsigned int mcu_subsys_ctrl3_pmussi : 3;
        unsigned int mcu_subsys_ctrl3_reserved : 10;
        unsigned int reserved_1 : 3;
        unsigned int mcu_subsys_ctrl3_pmussi_msk : 3;
        unsigned int mcu_subsys_ctrl3_msk : 10;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_pmussi_START (3)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_pmussi_END (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_reserved_START (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_reserved_END (15)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_pmussi_msk_START (19)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_pmussi_msk_END (21)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_msk_START (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL3_mcu_subsys_ctrl3_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coreon_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int coreon_ramctrl_s_emaw : 2;
        unsigned int coreon_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int coreon_ramctrl_s_ret1n : 1;
        unsigned int coreon_ramctrl_s_ret2n : 1;
        unsigned int coreon_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int cm3tcmoff_ramctrl_s_ema : 3;
        unsigned int reserved_3 : 1;
        unsigned int cm3tcmoff_ramctrl_s_emaw : 2;
        unsigned int cm3tcmoff_ramctrl_s_emas : 1;
        unsigned int reserved_4 : 3;
        unsigned int cm3tcmoff_ramctrl_s_ret1n : 1;
        unsigned int cm3tcmoff_ramctrl_s_ret2n : 1;
        unsigned int cm3tcmoff_ramctrl_s_pgen : 1;
        unsigned int reserved_5 : 3;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ema_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ema_END (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_emaw_START (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_emaw_END (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_emas_START (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_emas_END (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ret1n_START (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ret1n_END (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ret2n_START (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_ret2n_END (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_pgen_START (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_coreon_ramctrl_s_pgen_END (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ema_START (16)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ema_END (18)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_emaw_START (20)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_emaw_END (21)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_emas_START (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_emas_END (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ret1n_START (26)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ret1n_END (26)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ret2n_START (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_ret2n_END (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_pgen_START (28)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL4_cm3tcmoff_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 20;
        unsigned int mcu_subsys_ctrl5_apcfg0_ahb2apb_dfs : 1;
        unsigned int mcu_subsys_ctrl5_apcfg1_ahb2apb_dfs : 1;
        unsigned int mcu_subsys_ctrl5_apcfg2_ahb2apb_dfs : 1;
        unsigned int mcu_subsys_ctrl5 : 9;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg0_ahb2apb_dfs_START (20)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg0_ahb2apb_dfs_END (20)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg1_ahb2apb_dfs_START (21)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg1_ahb2apb_dfs_END (21)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg2_ahb2apb_dfs_START (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_apcfg2_ahb2apb_dfs_END (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_START (23)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL5_mcu_subsys_ctrl5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cm3tcmon_s0__ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int cm3tcmon_s0__ramctrl_s_emaw : 2;
        unsigned int cm3tcmon_s0__ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int cm3tcmon_s0__ramctrl_s_ret1n : 1;
        unsigned int cm3tcmon_s0__ramctrl_s_ret2n : 1;
        unsigned int cm3tcmon_s0__ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int cm3tcmon_s1_ramctrl_s_ema : 3;
        unsigned int reserved_3 : 1;
        unsigned int cm3tcmon_s1_ramctrl_s_emaw : 2;
        unsigned int cm3tcmon_s1_ramctrl_s_emas : 1;
        unsigned int reserved_4 : 3;
        unsigned int cm3tcmon_s1_ramctrl_s_ret1n : 1;
        unsigned int cm3tcmon_s1_ramctrl_s_ret2n : 1;
        unsigned int cm3tcmon_s1_ramctrl_s_pgen : 1;
        unsigned int reserved_5 : 3;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ema_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ema_END (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_emaw_START (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_emaw_END (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_emas_START (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_emas_END (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ret1n_START (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ret1n_END (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ret2n_START (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_ret2n_END (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_pgen_START (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s0__ramctrl_s_pgen_END (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ema_START (16)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ema_END (18)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_emaw_START (20)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_emaw_END (21)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_emas_START (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_emas_END (22)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ret1n_START (26)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ret1n_END (26)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ret2n_START (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_ret2n_END (27)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_pgen_START (28)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL6_cm3tcmon_s1_ramctrl_s_pgen_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tagmemon_ramctrl_s_ema : 3;
        unsigned int reserved_0 : 1;
        unsigned int tagmemon_ramctrl_s_emaw : 2;
        unsigned int tagmemon_ramctrl_s_emas : 1;
        unsigned int reserved_1 : 3;
        unsigned int tagmemon_ramctrl_s_ret1n : 1;
        unsigned int tagmemon_ramctrl_s_ret2n : 1;
        unsigned int tagmemon_ramctrl_s_pgen : 1;
        unsigned int reserved_2 : 3;
        unsigned int mcu_subsys_ctrl7 : 16;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ema_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ema_END (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_emaw_START (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_emaw_END (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_emas_START (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_emas_END (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ret1n_START (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ret1n_END (10)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ret2n_START (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_ret2n_END (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_pgen_START (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_tagmemon_ramctrl_s_pgen_END (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_mcu_subsys_ctrl7_START (16)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_CTRL7_mcu_subsys_ctrl7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state0_sysresetreq : 1;
        unsigned int mcu_subsys_state0_sleeping : 1;
        unsigned int mcu_subsys_state0_sleepdeep : 1;
        unsigned int mcu_subsys_state0_lockup : 1;
        unsigned int mcu_subsys_state0_currpri : 8;
        unsigned int mcu_subsys_state0_brchstat : 4;
        unsigned int mcu_subsys_state0_reserved : 16;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sysresetreq_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sysresetreq_END (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sleeping_START (1)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sleeping_END (1)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sleepdeep_START (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_sleepdeep_END (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_lockup_START (3)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_lockup_END (3)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_currpri_START (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_currpri_END (11)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_brchstat_START (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_brchstat_END (15)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_reserved_START (16)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT0_mcu_subsys_state0_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT1_mcu_subsys_state1_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT1_mcu_subsys_state1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state2 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT2_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT2_mcu_subsys_state2_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT2_mcu_subsys_state2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state3 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT3_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT3_mcu_subsys_state3_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT3_mcu_subsys_state3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state4_bank_write_port_enable : 1;
        unsigned int mcu_subsys_state4_bank_write_port_addres : 4;
        unsigned int mcu_subsys_state4_bank_read_port_A_address : 4;
        unsigned int mcu_subsys_state4_bank_read_port_B_address : 4;
        unsigned int mcu_subsys_state4 : 19;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_write_port_enable_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_write_port_enable_END (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_write_port_addres_START (1)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_write_port_addres_END (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_read_port_A_address_START (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_read_port_A_address_END (8)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_read_port_B_address_START (9)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_bank_read_port_B_address_END (12)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_START (13)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT4_mcu_subsys_state4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state5 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT5_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT5_mcu_subsys_state5_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT5_mcu_subsys_state5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state6 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT6_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT6_mcu_subsys_state6_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT6_mcu_subsys_state6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcu_subsys_state7_DAP_HTRANS : 2;
        unsigned int mcu_subsys_state7_DAP_abort : 1;
        unsigned int mcu_subsys_state7_Watchpoint : 1;
        unsigned int mcu_subsys_state7_FPB_instruction_remap_match : 1;
        unsigned int mcu_subsys_state7_FPB_literal_remap_match : 1;
        unsigned int mcu_subsys_state7_FPB_BKPT_match : 1;
        unsigned int mcu_subsys_state7_SysTick_interrupt_request : 1;
        unsigned int mcu_subsys_state7 : 24;
    } reg;
} SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_DAP_HTRANS_START (0)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_DAP_HTRANS_END (1)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_DAP_abort_START (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_DAP_abort_END (2)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_Watchpoint_START (3)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_Watchpoint_END (3)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_instruction_remap_match_START (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_instruction_remap_match_END (4)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_literal_remap_match_START (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_literal_remap_match_END (5)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_BKPT_match_START (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_FPB_BKPT_match_END (6)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_SysTick_interrupt_request_START (7)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_SysTick_interrupt_request_END (7)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_START (8)
#define SOC_AO_SCTRL_SC_MCU_SUBSYS_STAT7_mcu_subsys_state7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int alwayson_and_periph_sys_ctrl0_sci0 : 1;
        unsigned int alwayson_and_periph_sys_ctrl0_sci1 : 1;
        unsigned int reserved_1 : 2;
        unsigned int alwayson_and_periph_sys_ctrl0_func_test_soft : 3;
        unsigned int alwayson_and_periph_sys_ctrl0_reserved1 : 1;
        unsigned int reserved_2 : 8;
        unsigned int alwayson_and_periph_sys_ctrl0_msk_sci : 1;
        unsigned int alwayson_and_periph_sys_ctrl0_sci : 1;
        unsigned int alwayson_and_periph_sys_ctrl0_msk_reserved0 : 2;
        unsigned int alwayson_and_periph_sys_ctrl0_msk_func_test_soft : 3;
        unsigned int alwayson_and_periph_sys_ctrl0_msk_reserved_msk : 1;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci0_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci0_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci1_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci1_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_func_test_soft_START (12)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_func_test_soft_END (14)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_reserved1_START (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_reserved1_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_sci_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_sci_END (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci_START (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_sci_END (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_reserved0_START (26)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_reserved0_END (27)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_func_test_soft_START (28)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_func_test_soft_END (30)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_reserved_msk_START (31)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL0_alwayson_and_periph_sys_ctrl0_msk_reserved_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 5;
        unsigned int alwayson_and_periph_sys_ctrl1_cssys_ts_enable : 1;
        unsigned int reserved_2 : 24;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_alwayson_and_periph_sys_ctrl1_cssys_ts_enable_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL1_alwayson_and_periph_sys_ctrl1_cssys_ts_enable_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 31;
        unsigned int cssys_ctrl_prot : 1;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL2_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL2_cssys_ctrl_prot_START (31)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL2_cssys_ctrl_prot_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int amonitor_cpu0_en : 1;
        unsigned int amonitor_cpu1_en : 1;
        unsigned int amonitor_gpu_en : 1;
        unsigned int amonitor_img_en : 1;
        unsigned int amonitor_video_en : 1;
        unsigned int amonitor_mdm_en : 1;
        unsigned int amonitor_en6 : 1;
        unsigned int amonitor_en7 : 1;
        unsigned int amonitor_en8 : 1;
        unsigned int amonitor_en9 : 1;
        unsigned int amonitor_en10 : 1;
        unsigned int amonitor_en11 : 1;
        unsigned int amonitor_en12 : 1;
        unsigned int amonitor_en13 : 1;
        unsigned int amonitor_en14 : 1;
        unsigned int amonitor_en15 : 1;
        unsigned int amonitor_en16 : 1;
        unsigned int amonitor_en17 : 1;
        unsigned int reserved_0 : 6;
        unsigned int systemnoc_timeout_en : 1;
        unsigned int modemnoc_timeout_en : 1;
        unsigned int reserved_1 : 6;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_cpu0_en_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_cpu0_en_END (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_cpu1_en_START (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_cpu1_en_END (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_gpu_en_START (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_gpu_en_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_img_en_START (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_img_en_END (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_video_en_START (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_video_en_END (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_mdm_en_START (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_mdm_en_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en6_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en6_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en7_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en7_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en8_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en8_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en9_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en9_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en10_START (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en10_END (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en11_START (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en11_END (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en12_START (12)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en12_END (12)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en13_START (13)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en13_END (13)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en14_START (14)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en14_END (14)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en15_START (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en15_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en16_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en16_END (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en17_START (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_amonitor_en17_END (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_systemnoc_timeout_en_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_systemnoc_timeout_en_END (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_modemnoc_timeout_en_START (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL3_modemnoc_timeout_en_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gbbp_gps_restrain : 1;
        unsigned int gbbp_led_restrain : 1;
        unsigned int reserved_0 : 2;
        unsigned int ddrphy0_ret_en_i : 1;
        unsigned int ddrphy1_ret_en : 1;
        unsigned int ddrphy0_ret_en_n_i : 1;
        unsigned int ddrphy1_pro_dis : 1;
        unsigned int tcxo0_afc_high_z : 1;
        unsigned int tcxo1_afc_high_z : 1;
        unsigned int reserved_1 : 6;
        unsigned int gbbp_gps_restrain_msk : 1;
        unsigned int gbbp_led_restrain_msk : 1;
        unsigned int reserved_2 : 2;
        unsigned int ddrphy0_ret_en_i_msk : 1;
        unsigned int ddrphy1_ret_en_msk : 1;
        unsigned int ddrphy0_ret_en_n_i_msk : 1;
        unsigned int ddrphy1_pro_dis_msk : 1;
        unsigned int tcxo0_afc_high_z_msk : 1;
        unsigned int tcxo1_afc_high_z_msk : 1;
        unsigned int reserved_3 : 1;
        unsigned int alwayson_and_periph_sys_ctrl4_msk : 5;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_gps_restrain_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_gps_restrain_END (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_led_restrain_START (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_led_restrain_END (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_i_START (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_i_END (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_ret_en_START (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_ret_en_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_n_i_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_n_i_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_pro_dis_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_pro_dis_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_gps_restrain_msk_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_gps_restrain_msk_END (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_led_restrain_msk_START (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_gbbp_led_restrain_msk_END (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_i_msk_START (20)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_i_msk_END (20)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_ret_en_msk_START (21)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_ret_en_msk_END (21)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_n_i_msk_START (22)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy0_ret_en_n_i_msk_END (22)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_pro_dis_msk_START (23)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_ddrphy1_pro_dis_msk_END (23)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_msk_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_msk_END (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_msk_START (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_msk_END (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_alwayson_and_periph_sys_ctrl4_msk_START (27)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_alwayson_and_periph_sys_ctrl4_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_ctrl5_4reserved : 5;
        unsigned int alwayson_and_periph_sys_ctrl5_acpu_event_bypass : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcpu_event_bypass : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcu_event_bypass : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_reserved : 5;
        unsigned int alwayson_and_periph_sys_ctrl5_reserved20_msk : 5;
        unsigned int alwayson_and_periph_sys_ctrl5_acpu_event_bypass_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcu_event_bypass_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before_msk : 1;
        unsigned int alwayson_and_periph_sys_ctrl5_reserved_msk : 5;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_4reserved_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_4reserved_END (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_START (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before_START (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before_END (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved_START (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved20_msk_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved20_msk_END (20)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_msk_START (21)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_msk_END (21)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_msk_START (22)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_msk_END (22)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_msk_START (23)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_msk_END (23)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before_msk_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_acpu_event_bypass_before_msk_END (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before_msk_START (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcpu_event_bypass_before_msk_END (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before_msk_START (26)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_mcu_event_bypass_before_msk_END (26)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved_msk_START (27)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL5_alwayson_and_periph_sys_ctrl5_reserved_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 14;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int alwayson_and_periph_sys_ctrl6_reserved_msk : 14;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL6_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL6_alwayson_and_periph_sys_ctrl6_reserved_msk_START (18)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL6_alwayson_and_periph_sys_ctrl6_reserved_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 16;
        unsigned int alwayson_and_periph_sys_ctrl7_msk : 16;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL7_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL7_alwayson_and_periph_sys_ctrl7_msk_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL7_alwayson_and_periph_sys_ctrl7_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_ctrl8_2pico_fselv : 3;
        unsigned int alwayson_and_periph_sys_ctrl8_3reserved : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_5pico_refclksel : 2;
        unsigned int alwayson_and_periph_sys_ctrl8_6ddq : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_7pico_suspendm_sleepm : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_8pico_ogdisable : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_9pico_commononn : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_10pico_vbusvldextsel : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_11pico_vbusvldext : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_13pico_vatestenb : 2;
        unsigned int alwayson_and_periph_sys_ctrl8_14pico_suspendm : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_15pico_sleepm : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_16bc11_c : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_17bc11_b : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_18bc11_a : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_19bc11_gnd : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_20bc11_float : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_21reserved : 3;
        unsigned int alwayson_and_periph_sys_ctrl8_2otg_dm_pulldown : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_25otg_dp_pulldown : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_26otg_idpullup : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_27otg_drvbus : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_28otg_sessend : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_29otg_bvalid : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_30otg_avalid : 1;
        unsigned int alwayson_and_periph_sys_ctrl8_31ogt_vbusvalid : 1;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_2pico_fselv_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_2pico_fselv_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_3reserved_START (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_3reserved_END (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_5pico_refclksel_START (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_5pico_refclksel_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_6ddq_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_6ddq_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_7pico_suspendm_sleepm_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_7pico_suspendm_sleepm_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_8pico_ogdisable_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_8pico_ogdisable_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_9pico_commononn_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_9pico_commononn_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_10pico_vbusvldextsel_START (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_10pico_vbusvldextsel_END (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_11pico_vbusvldext_START (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_11pico_vbusvldext_END (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_13pico_vatestenb_START (12)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_13pico_vatestenb_END (13)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_14pico_suspendm_START (14)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_14pico_suspendm_END (14)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_15pico_sleepm_START (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_15pico_sleepm_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_16bc11_c_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_16bc11_c_END (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_17bc11_b_START (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_17bc11_b_END (17)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_18bc11_a_START (18)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_18bc11_a_END (18)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_19bc11_gnd_START (19)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_19bc11_gnd_END (19)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_20bc11_float_START (20)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_20bc11_float_END (20)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_21reserved_START (21)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_21reserved_END (23)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_2otg_dm_pulldown_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_2otg_dm_pulldown_END (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_25otg_dp_pulldown_START (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_25otg_dp_pulldown_END (25)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_26otg_idpullup_START (26)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_26otg_idpullup_END (26)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_27otg_drvbus_START (27)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_27otg_drvbus_END (27)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_28otg_sessend_START (28)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_28otg_sessend_END (28)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_29otg_bvalid_START (29)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_29otg_bvalid_END (29)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_30otg_avalid_START (30)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_30otg_avalid_END (30)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_31ogt_vbusvalid_START (31)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL8_alwayson_and_periph_sys_ctrl8_31ogt_vbusvalid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_ctrl9_reserved2 : 3;
        unsigned int alwayson_and_periph_sys_ctrl9_ustotg : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_acaenb : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_bc_mode : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_chrgsel : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_vdatsrcend : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_vdatdetenb : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_dcdenb : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_picophy_iddig : 1;
        unsigned int alwayson_and_periph_sys_ctrl9_reserved31 : 21;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_reserved2_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_reserved2_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_ustotg_START (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_ustotg_END (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_acaenb_START (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_acaenb_END (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_bc_mode_START (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_bc_mode_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_chrgsel_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_chrgsel_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_vdatsrcend_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_vdatsrcend_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_vdatdetenb_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_vdatdetenb_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_dcdenb_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_dcdenb_END (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_iddig_START (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_picophy_iddig_END (10)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_reserved31_START (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL9_alwayson_and_periph_sys_ctrl9_reserved31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_monitor_cfg_cnt_periodcfg : 16;
        unsigned int reserved : 15;
        unsigned int clk_monitor_cfg_cnt_en : 1;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_clk_monitor_cfg_cnt_periodcfg_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_clk_monitor_cfg_cnt_periodcfg_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_clk_monitor_cfg_cnt_en_START (31)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL10_clk_monitor_cfg_cnt_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_monitor_int_mask : 1;
        unsigned int clk_monitor_tcxo_en : 1;
        unsigned int clk_monitor_int_clr : 1;
        unsigned int alwayson_and_periph_sys_ctrl11 : 29;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_int_mask_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_int_mask_END (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_tcxo_en_START (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_tcxo_en_END (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_int_clr_START (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_clk_monitor_int_clr_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_alwayson_and_periph_sys_ctrl11_START (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL11_alwayson_and_periph_sys_ctrl11_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_state0_sec_ipc_clk_state : 3;
        unsigned int alwayson_and_periph_sys_state0_ns_ipc_clk_state : 3;
        unsigned int clk_monitor_mask_intr : 1;
        unsigned int clk_monitor_raw_intr : 1;
        unsigned int reserved : 8;
        unsigned int clk_monitor_clk_cnt : 16;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_alwayson_and_periph_sys_state0_sec_ipc_clk_state_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_alwayson_and_periph_sys_state0_sec_ipc_clk_state_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_alwayson_and_periph_sys_state0_ns_ipc_clk_state_START (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_alwayson_and_periph_sys_state0_ns_ipc_clk_state_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_mask_intr_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_mask_intr_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_raw_intr_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_raw_intr_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_clk_cnt_START (16)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT0_clk_monitor_clk_cnt_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wdrx_depth_flag_1card : 1;
        unsigned int g1_gdrx_depth_flag : 1;
        unsigned int g2_gdrx_depth_flag : 1;
        unsigned int reserved : 8;
        unsigned int alwayson_and_periph_sys_state1 : 21;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_wdrx_depth_flag_1card_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_wdrx_depth_flag_1card_END (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_g1_gdrx_depth_flag_START (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_g1_gdrx_depth_flag_END (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_g2_gdrx_depth_flag_START (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_g2_gdrx_depth_flag_END (2)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_alwayson_and_periph_sys_state1_START (11)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT1_alwayson_and_periph_sys_state1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int testdataout_picophy : 4;
        unsigned int otg_wkp_sts : 1;
        unsigned int chirpon_sts : 1;
        unsigned int datcondet_sts : 1;
        unsigned int chgdet_sts : 1;
        unsigned int chgdet_async : 1;
        unsigned int alwayson_state2_15reserved : 7;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 4;
        unsigned int alwayson_and_periph_sys_state2 : 8;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_testdataout_picophy_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_testdataout_picophy_END (3)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_otg_wkp_sts_START (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_otg_wkp_sts_END (4)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chirpon_sts_START (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chirpon_sts_END (5)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_datcondet_sts_START (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_datcondet_sts_END (6)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chgdet_sts_START (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chgdet_sts_END (7)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chgdet_async_START (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_chgdet_async_END (8)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_alwayson_state2_15reserved_START (9)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_alwayson_state2_15reserved_END (15)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_alwayson_and_periph_sys_state2_START (24)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT2_alwayson_and_periph_sys_state2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int carm_scuidle : 1;
        unsigned int alwayson_and_periph_sys_state3 : 31;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_carm_scuidle_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_carm_scuidle_END (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_alwayson_and_periph_sys_state3_START (1)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT3_alwayson_and_periph_sys_state3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_state4 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT4_alwayson_and_periph_sys_state4_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT4_alwayson_and_periph_sys_state4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_state5 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT5_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT5_alwayson_and_periph_sys_state5_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT5_alwayson_and_periph_sys_state5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_state6 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_alwayson_and_periph_sys_state6_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT6_alwayson_and_periph_sys_state6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int alwayson_and_periph_sys_state7 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_UNION;
#endif
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_alwayson_and_periph_sys_state7_START (0)
#define SOC_AO_SCTRL_SC_ALWAYSON_SYS_STAT7_alwayson_and_periph_sys_state7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken4_rtc : 1;
        unsigned int periph_clken4_timer0_pclk : 1;
        unsigned int periph_clken4_timer0 : 1;
        unsigned int periph_clken4_timer1_pclk : 1;
        unsigned int periph_clken4_timer1 : 1;
        unsigned int periph_clken4_timer2_pclk : 1;
        unsigned int periph_clken4_timer2 : 1;
        unsigned int periph_clken4_timer3_pclk : 1;
        unsigned int periph_clken4_timer3 : 1;
        unsigned int periph_clken4_timer4pclk : 1;
        unsigned int periph_clken4_timer4 : 1;
        unsigned int periph_clken4_timer5_pclk : 1;
        unsigned int periph_clken4_timer5 : 1;
        unsigned int periph_clken4_timer6_pclk : 1;
        unsigned int periph_clken4_timer6 : 1;
        unsigned int periph_clken4_timer7_pclk : 1;
        unsigned int periph_clken4_timer7 : 1;
        unsigned int periph_clken4_timer8_pclk : 1;
        unsigned int periph_clken4_timer8 : 1;
        unsigned int periph_clken4_timer0_cm3_asp_cfg_clk : 1;
        unsigned int periph_clken4_timer0_cm3 : 1;
        unsigned int periph_clken4_timer_asp_cfg_clk : 1;
        unsigned int periph_clken4_timer1_cm3 : 1;
        unsigned int periph_clken4_watchdog0_pclk : 1;
        unsigned int periph_clken4_watchdog0 : 1;
        unsigned int periph_clken4_watchdog1_pclk : 1;
        unsigned int periph_clken4_watchdog1 : 1;
        unsigned int periph_clken4_watchdog2_pclk : 1;
        unsigned int periph_clken4_watchdog2 : 1;
        unsigned int periph_clken4_watchdog0_cm3_pclk : 1;
        unsigned int periph_clken4_watchdog0_cm3 : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKEN4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_rtc_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_rtc_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_pclk_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer2_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer3_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer4_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer5_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer5_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer5_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer5_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer6_pclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer6_pclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer6_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer6_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer7_pclk_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer7_pclk_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer7_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer7_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer8_pclk_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer8_pclk_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer8_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer8_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_cm3_asp_cfg_clk_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_cm3_asp_cfg_clk_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_cm3_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer0_cm3_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer_asp_cfg_clk_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer_asp_cfg_clk_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_cm3_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_timer1_cm3_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_pclk_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_pclk_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog1_pclk_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog1_pclk_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog1_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog1_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog2_pclk_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog2_pclk_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog2_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog2_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_cm3_pclk_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_cm3_pclk_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_cm3_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_periph_clken4_watchdog0_cm3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis4_rtc : 1;
        unsigned int periph_clkdis4_timer0_pclk : 1;
        unsigned int periph_clkdis4_timer0 : 1;
        unsigned int periph_clkdis4_timer1_pclk : 1;
        unsigned int periph_clkdis4_timer1 : 1;
        unsigned int periph_clkdis4_timer2_pclk : 1;
        unsigned int periph_clkdis4_timer2 : 1;
        unsigned int periph_clkdis4_timer3_pclk : 1;
        unsigned int periph_clkdis4_timer3 : 1;
        unsigned int periph_clkdis4_timer4pclk : 1;
        unsigned int periph_clkdis4_timer4 : 1;
        unsigned int periph_clkdis4_timer5_pclk : 1;
        unsigned int periph_clkdis4_timer5 : 1;
        unsigned int periph_clkdis4_timer6_pclk : 1;
        unsigned int periph_clkdis4_timer6 : 1;
        unsigned int periph_clkdis4_timer7_pclk : 1;
        unsigned int periph_clkdis4_timer7 : 1;
        unsigned int periph_clkdis4_timer8_pclk : 1;
        unsigned int periph_clkdis4_timer8 : 1;
        unsigned int periph_clkdis4_timer0_cm3_asp_cfg_clk : 1;
        unsigned int periph_clkdis4_timer0_cm3 : 1;
        unsigned int periph_clkdis4_timer_asp_cfg_clk : 1;
        unsigned int periph_clkdis4_timer1_cm3 : 1;
        unsigned int periph_clkdis4_watchdog0_pclk : 1;
        unsigned int periph_clkdis4_watchdog0 : 1;
        unsigned int periph_clkdis4_watchdog1_pclk : 1;
        unsigned int periph_clkdis4_watchdog1 : 1;
        unsigned int periph_clkdis4_watchdog2_pclk : 1;
        unsigned int periph_clkdis4_watchdog2 : 1;
        unsigned int periph_clkdis4_watchdog0_cm3_pclk : 1;
        unsigned int periph_clkdis4_watchdog0_cm3 : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_rtc_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_rtc_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_pclk_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_pclk_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer2_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer2_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer2_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer2_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer3_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer3_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer3_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer3_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer4pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer4pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer4_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer4_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer5_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer5_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer5_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer5_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer6_pclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer6_pclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer6_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer6_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer7_pclk_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer7_pclk_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer7_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer7_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer8_pclk_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer8_pclk_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer8_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer8_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_cm3_asp_cfg_clk_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_cm3_asp_cfg_clk_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_cm3_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer0_cm3_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer_asp_cfg_clk_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer_asp_cfg_clk_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_cm3_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_timer1_cm3_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_pclk_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_pclk_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog1_pclk_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog1_pclk_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog1_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog1_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog2_pclk_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog2_pclk_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog2_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog2_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_cm3_pclk_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_cm3_pclk_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_cm3_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_periph_clkdis4_watchdog0_cm3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat4_rtc : 1;
        unsigned int periph_clkstat4_timer0_pclk : 1;
        unsigned int periph_clkstat4_timer0 : 1;
        unsigned int periph_clkstat4_timer1_pclk : 1;
        unsigned int periph_clkstat4_timer1 : 1;
        unsigned int periph_clkstat4_timer2_pclk : 1;
        unsigned int periph_clkstat4_timer2 : 1;
        unsigned int periph_clkstat4_timer3_pclk : 1;
        unsigned int periph_clkstat4_timer3 : 1;
        unsigned int periph_clkstat4_timer4pclk : 1;
        unsigned int periph_clkstat4_timer4 : 1;
        unsigned int periph_clkstat4_timer5_pclk : 1;
        unsigned int periph_clkstat4_timer5 : 1;
        unsigned int periph_clkstat4_timer6_pclk : 1;
        unsigned int periph_clkstat4_timer6 : 1;
        unsigned int periph_clkstat4_timer7_pclk : 1;
        unsigned int periph_clkstat4_timer7 : 1;
        unsigned int periph_clkstat4_timer8_pclk : 1;
        unsigned int periph_clkstat4_timer8 : 1;
        unsigned int periph_clkstat4_timer0_cm3_asp_cfg_clk : 1;
        unsigned int periph_clkstat4_timer0_cm3 : 1;
        unsigned int periph_clkstat4_timer_asp_cfg_clk : 1;
        unsigned int periph_clkstat4_timer1_cm3 : 1;
        unsigned int periph_clkstat4_watchdog0_pclk : 1;
        unsigned int periph_clkstat4_watchdog0 : 1;
        unsigned int periph_clkstat4_watchdog1_pclk : 1;
        unsigned int periph_clkstat4_watchdog1 : 1;
        unsigned int periph_clkstat4_watchdog2_pclk : 1;
        unsigned int periph_clkstat4_watchdog2 : 1;
        unsigned int periph_clkstat4_watchdog0_cm3_pclk : 1;
        unsigned int periph_clkstat4_watchdog0_cm3 : 1;
        unsigned int reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_rtc_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_rtc_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_pclk_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_pclk_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer2_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer2_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer2_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer2_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer3_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer3_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer3_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer3_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer4pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer4pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer4_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer4_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer5_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer5_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer5_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer5_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer6_pclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer6_pclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer6_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer6_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer7_pclk_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer7_pclk_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer7_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer7_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer8_pclk_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer8_pclk_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer8_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer8_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_cm3_asp_cfg_clk_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_cm3_asp_cfg_clk_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_cm3_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer0_cm3_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer_asp_cfg_clk_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer_asp_cfg_clk_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_cm3_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_timer1_cm3_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_pclk_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_pclk_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog1_pclk_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog1_pclk_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog1_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog1_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog2_pclk_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog2_pclk_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog2_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog2_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_cm3_pclk_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_cm3_pclk_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_cm3_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT4_periph_clkstat4_watchdog0_cm3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clken5_watchdog1_cm3_pclk : 1;
        unsigned int periph_clken5_watchdog1_cm3 : 1;
        unsigned int periph_clken5_pmussi : 1;
        unsigned int periph_clken5_uart0_cm3_pclk : 1;
        unsigned int periph_clken5_uart0_cm3 : 1;
        unsigned int periph_clken5_sci0_pclk : 1;
        unsigned int periph_clken5_sci0 : 1;
        unsigned int periph_clken5_sci1_pclk : 1;
        unsigned int periph_clken5_sci1 : 1;
        unsigned int periph_clken5_tzpc_pclk : 1;
        unsigned int periph_clken5_ap_sram : 1;
        unsigned int periph_clken5_clk_efusec : 1;
        unsigned int periph_clken5_mcu_sram : 1;
        unsigned int periph_clken5_mcu_stclk : 1;
        unsigned int periph_clken5_mcu_hclk : 1;
        unsigned int periph_clken5_cm3_subsys_ahb : 1;
        unsigned int periph_clken5_hclk_slow_h2h_h2p : 1;
        unsigned int periph_clken5_pclk_slow_h2h_h2p : 1;
        unsigned int periph_clken5_hclk_cm3_h2p : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clken5_clk_cs_dapb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_clken5_hclk_h2sram : 1;
        unsigned int periph_clken5_clk_mcu_dap : 1;
        unsigned int periph_clken5_clk_ipc : 1;
        unsigned int periph_clken5_hclk_h2p2_brg : 1;
        unsigned int periph_clken5_mcu_sram_off : 1;
        unsigned int periph_clken5_cm3_mem_ahb : 1;
        unsigned int periph_clken5_clk_ipc_ns : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKEN5_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_watchdog1_cm3_pclk_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_watchdog1_cm3_pclk_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_watchdog1_cm3_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_watchdog1_cm3_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pmussi_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pmussi_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_uart0_cm3_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_uart0_cm3_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_uart0_cm3_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_uart0_cm3_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci0_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci0_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci0_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci0_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci1_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci1_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci1_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_sci1_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_tzpc_pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_tzpc_pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_ap_sram_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_ap_sram_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_efusec_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_efusec_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_sram_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_sram_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_stclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_stclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_hclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_hclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_cm3_subsys_ahb_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_cm3_subsys_ahb_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_slow_h2h_h2p_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_slow_h2h_h2p_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pclk_slow_h2h_h2p_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_pclk_slow_h2h_h2p_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_cm3_h2p_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_cm3_h2p_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_cs_dapb_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_cs_dapb_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_h2sram_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_h2sram_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_mcu_dap_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_mcu_dap_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_ipc_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_ipc_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_h2p2_brg_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_hclk_h2p2_brg_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_sram_off_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_mcu_sram_off_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_cm3_mem_ahb_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_cm3_mem_ahb_END (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_ipc_ns_START (31)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN5_periph_clken5_clk_ipc_ns_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkdis5_watchdog1_cm3_pclk : 1;
        unsigned int periph_clkdis5_watchdog1_cm3 : 1;
        unsigned int periph_clkdis5_pmussi : 1;
        unsigned int periph_clkdis5_uart0_cm3_pclk : 1;
        unsigned int periph_clkdis5_uart0_cm3 : 1;
        unsigned int periph_clkdis5_sci0_pclk : 1;
        unsigned int periph_clkdis5_sci0 : 1;
        unsigned int periph_clkdis5_sci1_pclk : 1;
        unsigned int periph_clkdis5_sci1 : 1;
        unsigned int periph_clkdis5_tzpc_pclk : 1;
        unsigned int periph_clkdis5_ap_sram : 1;
        unsigned int periph_clkdis5_clk_efusec : 1;
        unsigned int periph_clkdis5_mcu_sram : 1;
        unsigned int periph_clkdis5_mcu_stclk : 1;
        unsigned int periph_clkdis5_mcu_hclk : 1;
        unsigned int periph_clkdis5_cm3_subsys_ahb : 1;
        unsigned int periph_clkdis5_hclk_slow_h2h_h2p : 1;
        unsigned int periph_clkdis5_pclk_slow_h2h_h2p : 1;
        unsigned int periph_clkdis5_hclk_cm3_h2p : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkdis5_clk_cs_dapb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_clkdis5_hclk_h2sram : 1;
        unsigned int periph_clkdis5_clk_mcu_dap : 1;
        unsigned int periph_clkdis5_clk_ipc : 1;
        unsigned int periph_clkdis5_hclk_h2p2_brg : 1;
        unsigned int periph_clkdis5_mcu_sram_off : 1;
        unsigned int periph_clkdis5_cm3_mem_ahb : 1;
        unsigned int periph_clkdis5_clk_ipc_ns : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_watchdog1_cm3_pclk_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_watchdog1_cm3_pclk_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_watchdog1_cm3_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_watchdog1_cm3_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_pmussi_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_pmussi_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_uart0_cm3_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_uart0_cm3_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_uart0_cm3_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_uart0_cm3_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci0_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci0_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci0_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci0_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci1_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci1_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci1_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_sci1_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_tzpc_pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_tzpc_pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_ap_sram_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_ap_sram_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_efusec_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_efusec_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_sram_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_sram_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_stclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_stclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_hclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_hclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_cm3_subsys_ahb_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_cm3_subsys_ahb_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_slow_h2h_h2p_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_slow_h2h_h2p_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_pclk_slow_h2h_h2p_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_pclk_slow_h2h_h2p_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_cm3_h2p_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_cm3_h2p_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_cs_dapb_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_cs_dapb_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_h2sram_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_h2sram_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_mcu_dap_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_mcu_dap_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_ipc_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_ipc_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_h2p2_brg_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_hclk_h2p2_brg_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_sram_off_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_mcu_sram_off_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_cm3_mem_ahb_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_cm3_mem_ahb_END (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_ipc_ns_START (31)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS5_periph_clkdis5_clk_ipc_ns_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int periph_clkstat5_watchdog1_cm3_pclk : 1;
        unsigned int periph_clkstat5_watchdog1_cm3 : 1;
        unsigned int periph_clkstat5_pmussi : 1;
        unsigned int periph_clkstat5_uart0_cm3_pclk : 1;
        unsigned int periph_clkstat5_uart0_cm3 : 1;
        unsigned int periph_clkstat5_sci0_pclk : 1;
        unsigned int periph_clkstat5_sci0 : 1;
        unsigned int periph_clkstat5_sci1_pclk : 1;
        unsigned int periph_clkstat5_sci1 : 1;
        unsigned int periph_clkstat5_tzpc_pclk : 1;
        unsigned int periph_clkstat5_ap_sram : 1;
        unsigned int periph_clkstat5_clk_efusec : 1;
        unsigned int periph_clkstat5_mcu_sram : 1;
        unsigned int periph_clkstat5_mcu_stclk : 1;
        unsigned int periph_clkstat5_mcu_hclk : 1;
        unsigned int periph_clkstat5_cm3_subsys_ahb : 1;
        unsigned int periph_clkstat5_hclk_slow_h2h_h2p : 1;
        unsigned int periph_clkstat5_pclk_slow_h2h_h2p : 1;
        unsigned int periph_clkstat5_hclk_cm3_h2p : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_clkstat5_clk_cs_dapb : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int periph_clkstat5_hclk_h2sram : 1;
        unsigned int periph_clkstat5_clk_mcu_dap : 1;
        unsigned int periph_clkstat5_clk_ipc : 1;
        unsigned int periph_clkstat5_hclk_h2p2_brg : 1;
        unsigned int periph_clkstat5_mcu_sram_off : 1;
        unsigned int periph_clkstat5_cm3_mem_ahb : 1;
        unsigned int periph_clkstat5_clk_ipc_ns : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_watchdog1_cm3_pclk_START (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_watchdog1_cm3_pclk_END (0)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_watchdog1_cm3_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_watchdog1_cm3_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_pmussi_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_pmussi_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_uart0_cm3_pclk_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_uart0_cm3_pclk_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_uart0_cm3_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_uart0_cm3_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci0_pclk_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci0_pclk_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci0_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci0_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci1_pclk_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci1_pclk_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci1_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_sci1_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_tzpc_pclk_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_tzpc_pclk_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_ap_sram_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_ap_sram_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_efusec_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_efusec_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_sram_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_sram_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_stclk_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_stclk_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_hclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_hclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_cm3_subsys_ahb_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_cm3_subsys_ahb_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_slow_h2h_h2p_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_slow_h2h_h2p_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_pclk_slow_h2h_h2p_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_pclk_slow_h2h_h2p_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_cm3_h2p_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_cm3_h2p_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_cs_dapb_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_cs_dapb_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_h2sram_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_h2sram_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_mcu_dap_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_mcu_dap_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_ipc_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_ipc_END (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_h2p2_brg_START (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_hclk_h2p2_brg_END (28)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_sram_off_START (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_mcu_sram_off_END (29)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_cm3_mem_ahb_START (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_cm3_mem_ahb_END (30)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_ipc_ns_START (31)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT5_periph_clkstat5_clk_ipc_ns_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_clken6_hclk_usbotg : 1;
        unsigned int periph_clken6_clk_picophy : 1;
        unsigned int periph_clken6_clk_picophy_test : 1;
        unsigned int periph_clken6_modem_timer0_pclk : 1;
        unsigned int periph_clken6_modem_timer0 : 1;
        unsigned int periph_clken6_modem_timer1_pclk : 1;
        unsigned int periph_clken6_modem_timer1 : 1;
        unsigned int periph_clken6_modem_timer2_pclk : 1;
        unsigned int periph_clken6_modem_timer2 : 1;
        unsigned int periph_clken6_modem_timer_reserved27 : 1;
        unsigned int periph_clken6_modem_timer3_pclk : 1;
        unsigned int periph_clken6_modem_timer4_pclk : 1;
        unsigned int periph_clken6_modem_timer4 : 1;
        unsigned int periph_clken6_modem_timer5_pclk : 1;
        unsigned int periph_clken6_modem_timer5 : 1;
        unsigned int periph_clken6_modem_timer6_pclk : 1;
        unsigned int periph_clken6_modem_timer6 : 1;
        unsigned int periph_clken6_modem_timer7_pclk : 1;
        unsigned int periph_clken6_modem_timer7 : 1;
        unsigned int periph_clken6_modem_timer8_pclk : 1;
        unsigned int periph_clken6_modem_timer8 : 1;
        unsigned int periph_clken6_modem_timer9_pclk : 1;
        unsigned int periph_clken6_modem_timer9 : 1;
        unsigned int periph_clken6_watchdog3_pclk : 1;
        unsigned int periph_clken6_watchdog3 : 1;
        unsigned int periph_clken6_bbp_apb_on : 1;
        unsigned int periph_clken6_bbp_tcxo_on : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKEN6_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_hclk_usbotg_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_hclk_usbotg_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_test_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_clk_picophy_test_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer0_pclk_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer0_pclk_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer1_pclk_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer1_pclk_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer1_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer1_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer2_pclk_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer2_pclk_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer2_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer2_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer_reserved27_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer_reserved27_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer3_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer3_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer4_pclk_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer4_pclk_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer4_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer4_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer5_pclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer5_pclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer5_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer5_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer6_pclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer6_pclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer6_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer6_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer7_pclk_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer7_pclk_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer7_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer7_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer8_pclk_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer8_pclk_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer8_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer8_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer9_pclk_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer9_pclk_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer9_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_modem_timer9_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_watchdog3_pclk_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_watchdog3_pclk_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_watchdog3_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_watchdog3_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_bbp_apb_on_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_bbp_apb_on_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_bbp_tcxo_on_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN6_periph_clken6_bbp_tcxo_on_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_clkdis6_hclk_usbotg : 1;
        unsigned int periph_clkdis6_clk_picophy : 1;
        unsigned int periph_clkdis6_clk_picophy_test : 1;
        unsigned int periph_clkdis6_modem_timer0_pclk : 1;
        unsigned int periph_clkdis6_modem_timer0 : 1;
        unsigned int periph_clkdis6_modem_timer1_pclk : 1;
        unsigned int periph_clkdis6_modem_timer1 : 1;
        unsigned int periph_clkdis6_modem_timer2_pclk : 1;
        unsigned int periph_clkdis6_modem_timer2 : 1;
        unsigned int periph_clkdis6_modem_timer_reserved27 : 1;
        unsigned int periph_clkdis6_modem_timer3_pclk : 1;
        unsigned int periph_clkdis6_modem_timer4_pclk : 1;
        unsigned int periph_clkdis6_modem_timer4 : 1;
        unsigned int periph_clkdis6_modem_timer5_pclk : 1;
        unsigned int periph_clkdis6_modem_timer5 : 1;
        unsigned int periph_clkdis6_modem_timer6_pclk : 1;
        unsigned int periph_clkdis6_modem_timer6 : 1;
        unsigned int periph_clkdis6_modem_timer7_pclk : 1;
        unsigned int periph_clkdis6_modem_timer7 : 1;
        unsigned int periph_clkdis6_modem_timer8_pclk : 1;
        unsigned int periph_clkdis6_modem_timer8 : 1;
        unsigned int periph_clkdis6_modem_timer9_pclk : 1;
        unsigned int periph_clkdis6_modem_timer9 : 1;
        unsigned int periph_clkdis6_watchdog3_pclk : 1;
        unsigned int periph_clkdis6_watchdog3 : 1;
        unsigned int periph_clkdis6_bbp_apb_on : 1;
        unsigned int periph_clkdis6_bbp_tcxo_on : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_hclk_usbotg_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_hclk_usbotg_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_clk_picophy_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_clk_picophy_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_clk_picophy_test_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_clk_picophy_test_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer0_pclk_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer0_pclk_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer1_pclk_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer1_pclk_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer1_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer1_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer2_pclk_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer2_pclk_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer2_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer2_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer_reserved27_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer_reserved27_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer3_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer3_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer4_pclk_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer4_pclk_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer4_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer4_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer5_pclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer5_pclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer5_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer5_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer6_pclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer6_pclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer6_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer6_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer7_pclk_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer7_pclk_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer7_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer7_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer8_pclk_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer8_pclk_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer8_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer8_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer9_pclk_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer9_pclk_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer9_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_modem_timer9_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_watchdog3_pclk_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_watchdog3_pclk_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_watchdog3_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_watchdog3_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_bbp_apb_on_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_bbp_apb_on_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_bbp_tcxo_on_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKDIS6_periph_clkdis6_bbp_tcxo_on_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_clkstat6_hclk_usbotg : 1;
        unsigned int periph_clkstat6_clk_picophy : 1;
        unsigned int periph_clkstat6_clk_picophy_test : 1;
        unsigned int periph_clkstat6_modem_timer0_pclk : 1;
        unsigned int periph_clkstat6_modem_timer0 : 1;
        unsigned int periph_clkstat6_modem_timer1_pclk : 1;
        unsigned int periph_clkstat6_modem_timer1 : 1;
        unsigned int periph_clkstat6_modem_timer2_pclk : 1;
        unsigned int periph_clkstat6_modem_timer2 : 1;
        unsigned int periph_clkstat6_modem_timer_reserved27 : 1;
        unsigned int periph_clkstat6_modem_timer3_pclk : 1;
        unsigned int periph_clkstat6_modem_timer4_pclk : 1;
        unsigned int periph_clkstat6_modem_timer4 : 1;
        unsigned int periph_clkstat6_modem_timer5_pclk : 1;
        unsigned int periph_clkstat6_modem_timer5 : 1;
        unsigned int periph_clkstat6_modem_timer6_pclk : 1;
        unsigned int periph_clkstat6_modem_timer6 : 1;
        unsigned int periph_clkstat6_modem_timer7_pclk : 1;
        unsigned int periph_clkstat6_modem_timer7 : 1;
        unsigned int periph_clkstat6_modem_timer8_pclk : 1;
        unsigned int periph_clkstat6_modem_timer8 : 1;
        unsigned int periph_clkstat6_modem_timer9_pclk : 1;
        unsigned int periph_clkstat6_modem_timer9 : 1;
        unsigned int periph_clkstat6_watchdog3_pclk : 1;
        unsigned int periph_clkstat6_watchdog3 : 1;
        unsigned int periph_clkstat6_bbp_apb_on : 1;
        unsigned int periph_clkstat6_bbp_tcxo_on : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_hclk_usbotg_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_hclk_usbotg_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_clk_picophy_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_clk_picophy_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_clk_picophy_test_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_clk_picophy_test_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer0_pclk_START (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer0_pclk_END (4)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer1_pclk_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer1_pclk_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer1_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer1_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer2_pclk_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer2_pclk_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer2_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer2_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer_reserved27_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer_reserved27_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer3_pclk_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer3_pclk_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer4_pclk_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer4_pclk_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer4_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer4_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer5_pclk_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer5_pclk_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer5_START (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer5_END (15)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer6_pclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer6_pclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer6_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer6_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer7_pclk_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer7_pclk_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer7_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer7_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer8_pclk_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer8_pclk_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer8_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer8_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer9_pclk_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer9_pclk_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer9_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_modem_timer9_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_watchdog3_pclk_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_watchdog3_pclk_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_watchdog3_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_watchdog3_END (25)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_bbp_apb_on_START (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_bbp_apb_on_END (26)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_bbp_tcxo_on_START (27)
#define SOC_AO_SCTRL_SC_PERIPH_CLKSTAT6_periph_clkstat6_bbp_tcxo_on_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKEN7_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKDIS7_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_CLKSTAT7_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_rsten4_1pmussi : 1;
        unsigned int periph_rsten4_2reset_cs_dapb_n : 1;
        unsigned int periph_rsten4_3sram_off : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rsten4_5sci0 : 1;
        unsigned int periph_rsten4_6sci1 : 1;
        unsigned int periph_rsten4_7cm3uart0 : 1;
        unsigned int periph_rsten4_8reserved : 1;
        unsigned int periph_rsten4_9hreset_slow_h2h_n : 1;
        unsigned int periph_rsten4_10reserved : 1;
        unsigned int periph_rsten4_11mcupor : 1;
        unsigned int periph_rsten4_12mcusys : 1;
        unsigned int periph_rsten4_13hreset_mcu_sys_n : 1;
        unsigned int periph_rsten4_14reset_mcu_dap_n : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rsten4_16usbotg_hclk : 1;
        unsigned int periph_rsten4_17usbotgw : 1;
        unsigned int periph_rsten4_18reset_por_picophy_n : 1;
        unsigned int periph_rsten4_19reset_port_picophy_n : 1;
        unsigned int periph_rsten4_20reset_bbp_apb_on_n : 1;
        unsigned int periph_rsten4_21reset_bbp_tcxo_on_n : 1;
        unsigned int periph_rsten4_22reset_bbp_32k_on_n : 1;
        unsigned int periph_rsten4_23reset_gbbp1_on_n : 1;
        unsigned int periph_rsten4_24reset_gbbp2_on_n : 1;
        unsigned int periph_rsten4_31reserved : 7;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTEN4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_1pmussi_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_1pmussi_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_2reset_cs_dapb_n_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_2reset_cs_dapb_n_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_3sram_off_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_3sram_off_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_5sci0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_5sci0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_6sci1_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_6sci1_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_7cm3uart0_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_7cm3uart0_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_8reserved_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_8reserved_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_9hreset_slow_h2h_n_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_9hreset_slow_h2h_n_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_10reserved_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_10reserved_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_11mcupor_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_11mcupor_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_12mcusys_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_12mcusys_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_13hreset_mcu_sys_n_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_13hreset_mcu_sys_n_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_14reset_mcu_dap_n_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_14reset_mcu_dap_n_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_16usbotg_hclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_16usbotg_hclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_17usbotgw_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_17usbotgw_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_18reset_por_picophy_n_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_18reset_por_picophy_n_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_19reset_port_picophy_n_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_19reset_port_picophy_n_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_20reset_bbp_apb_on_n_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_20reset_bbp_apb_on_n_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_21reset_bbp_tcxo_on_n_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_21reset_bbp_tcxo_on_n_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_22reset_bbp_32k_on_n_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_22reset_bbp_32k_on_n_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_23reset_gbbp1_on_n_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_23reset_gbbp1_on_n_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_24reset_gbbp2_on_n_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_24reset_gbbp2_on_n_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_31reserved_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_RSTEN4_periph_rsten4_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_rstdis4_1pmussi : 1;
        unsigned int periph_rstdis4_2reset_cs_dapb_n : 1;
        unsigned int periph_rstdis4_3sram_off : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rstdis4_5sci0 : 1;
        unsigned int periph_rstdis4_6sci1 : 1;
        unsigned int periph_rstdis4_7cm3uart0 : 1;
        unsigned int periph_rstdis4_8hreset_periph_bus_n : 1;
        unsigned int periph_rstdis4_9hreset_slow_h2h_n : 1;
        unsigned int periph_rstdis4_10reserved : 1;
        unsigned int periph_rstdis4_11mcupor : 1;
        unsigned int periph_rstdis4_12mcusys : 1;
        unsigned int periph_rstdis4_13hreset_mcu_sys_n : 1;
        unsigned int periph_rstdis4_14reset_mcu_dap_n : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rstdis4_16usbotg_hclk : 1;
        unsigned int periph_rstdis4_17usbotgw : 1;
        unsigned int periph_rstdis4_18reset_por_picophy_n : 1;
        unsigned int periph_rstdis4_19reset_port_picophy_n : 1;
        unsigned int periph_rstdis4_20reset_bbp_apb_on_n : 1;
        unsigned int periph_rstdis4_21reset_bbp_tcxo_on_n : 1;
        unsigned int periph_rstdis4_22reset_bbp_32k_on_n : 1;
        unsigned int periph_rstdis4_23reset_gbbp1_on_n : 1;
        unsigned int periph_rstdis4_24reset_gbbp2_on_n : 1;
        unsigned int periph_rstdis4_31reserved : 7;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_1pmussi_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_1pmussi_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_2reset_cs_dapb_n_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_2reset_cs_dapb_n_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_3sram_off_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_3sram_off_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_5sci0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_5sci0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_6sci1_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_6sci1_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_7cm3uart0_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_7cm3uart0_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_8hreset_periph_bus_n_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_8hreset_periph_bus_n_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_9hreset_slow_h2h_n_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_9hreset_slow_h2h_n_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_10reserved_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_10reserved_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_11mcupor_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_11mcupor_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_12mcusys_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_12mcusys_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_13hreset_mcu_sys_n_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_13hreset_mcu_sys_n_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_14reset_mcu_dap_n_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_14reset_mcu_dap_n_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_16usbotg_hclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_16usbotg_hclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_17usbotgw_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_17usbotgw_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_18reset_por_picophy_n_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_18reset_por_picophy_n_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_19reset_port_picophy_n_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_19reset_port_picophy_n_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_20reset_bbp_apb_on_n_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_20reset_bbp_apb_on_n_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_21reset_bbp_tcxo_on_n_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_21reset_bbp_tcxo_on_n_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_22reset_bbp_32k_on_n_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_22reset_bbp_32k_on_n_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_23reset_gbbp1_on_n_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_23reset_gbbp1_on_n_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_24reset_gbbp2_on_n_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_24reset_gbbp2_on_n_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_31reserved_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_RSTDIS4_periph_rstdis4_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int periph_rststat4_1pmussi : 1;
        unsigned int periph_rststat4_2reset_cs_dapb_n : 1;
        unsigned int periph_rststat4_3sram_off : 1;
        unsigned int reserved_1 : 1;
        unsigned int periph_rststat4_5sci0 : 1;
        unsigned int periph_rststat4_6sci1 : 1;
        unsigned int periph_rststat4_7cm3uart0 : 1;
        unsigned int periph_rststat4_8hreset_periph_bus_n : 1;
        unsigned int periph_rststat4_9hreset_slow_h2h_n : 1;
        unsigned int periph_rststat4_10reserved : 1;
        unsigned int periph_rststat4_11mcupor : 1;
        unsigned int periph_rststat4_12mcusys : 1;
        unsigned int periph_rststat4_13hreset_mcu_sys_n : 1;
        unsigned int periph_rststat4_14reset_mcu_dap_n : 1;
        unsigned int reserved_2 : 1;
        unsigned int periph_rststat4_16usbotg_hclk : 1;
        unsigned int periph_rststat4_17usbotgw : 1;
        unsigned int periph_rststat4_18reset_por_picophy_n : 1;
        unsigned int periph_rststat4_19reset_port_picophy_n : 1;
        unsigned int periph_rststat4_20reset_bbp_apb_on_n : 1;
        unsigned int periph_rststat4_21reset_bbp_tcxo_on_n : 1;
        unsigned int periph_rststat4_22reset_bbp_32k_on_n : 1;
        unsigned int periph_rststat4_23reset_gbbp1_on_n : 1;
        unsigned int periph_rststat4_24reset_gbbp2_on_n : 1;
        unsigned int periph_rststat4_31reserved : 7;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_1pmussi_START (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_1pmussi_END (1)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_2reset_cs_dapb_n_START (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_2reset_cs_dapb_n_END (2)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_3sram_off_START (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_3sram_off_END (3)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_5sci0_START (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_5sci0_END (5)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_6sci1_START (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_6sci1_END (6)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_7cm3uart0_START (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_7cm3uart0_END (7)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_8hreset_periph_bus_n_START (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_8hreset_periph_bus_n_END (8)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_9hreset_slow_h2h_n_START (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_9hreset_slow_h2h_n_END (9)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_10reserved_START (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_10reserved_END (10)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_11mcupor_START (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_11mcupor_END (11)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_12mcusys_START (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_12mcusys_END (12)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_13hreset_mcu_sys_n_START (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_13hreset_mcu_sys_n_END (13)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_14reset_mcu_dap_n_START (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_14reset_mcu_dap_n_END (14)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_16usbotg_hclk_START (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_16usbotg_hclk_END (16)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_17usbotgw_START (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_17usbotgw_END (17)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_18reset_por_picophy_n_START (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_18reset_por_picophy_n_END (18)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_19reset_port_picophy_n_START (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_19reset_port_picophy_n_END (19)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_20reset_bbp_apb_on_n_START (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_20reset_bbp_apb_on_n_END (20)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_21reset_bbp_tcxo_on_n_START (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_21reset_bbp_tcxo_on_n_END (21)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_22reset_bbp_32k_on_n_START (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_22reset_bbp_32k_on_n_END (22)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_23reset_gbbp1_on_n_START (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_23reset_gbbp1_on_n_END (23)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_24reset_gbbp2_on_n_START (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_24reset_gbbp2_on_n_END (24)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_31reserved_START (25)
#define SOC_AO_SCTRL_SC_PERIPH_RSTSTAT4_periph_rststat4_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTEN5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTDIS5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERIPH_RSTSTAT5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clken0_0peri : 1;
        unsigned int pw_clken0_1g3d : 1;
        unsigned int pw_clken0_2g2d : 1;
        unsigned int pw_clken0_3edc0 : 1;
        unsigned int pw_clken0_4edc1 : 1;
        unsigned int pw_clken0_5isp : 1;
        unsigned int pw_clken0_6enc : 1;
        unsigned int pw_clken0_7dec : 1;
        unsigned int pw_clken0_8hifi : 1;
        unsigned int pw_clken0_9vpp : 1;
        unsigned int pw_clken0_10dspbbe : 1;
        unsigned int pw_clken0_11ddrctrl : 1;
        unsigned int pw_clken0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_clken0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_clken0_14ltebbptop : 1;
        unsigned int pw_clken0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_clken0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_clken0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_clken0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_clken0_19abbana : 1;
        unsigned int pw_clken0_20usbphy : 1;
        unsigned int pw_clken0_21reserved : 1;
        unsigned int pw_clken0_22cs0phy : 1;
        unsigned int pw_clken0_23reserved : 1;
        unsigned int pw_clken0_24cs2phy : 1;
        unsigned int pw_clken0_25dsiphy : 1;
        unsigned int pw_clken0_26hdmiphy : 1;
        unsigned int pw_clken0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_clken0_29tsensor0 : 1;
        unsigned int pw_clken0_30tsensor1 : 1;
        unsigned int pw_clken0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLKEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clkdis0_0peri : 1;
        unsigned int pw_clkdis0_1g3d : 1;
        unsigned int pw_clkdis0_2g2d : 1;
        unsigned int pw_clkdis0_3edc0 : 1;
        unsigned int pw_clkdis0_4edc1 : 1;
        unsigned int pw_clkdis0_5isp : 1;
        unsigned int pw_clkdis0_6enc : 1;
        unsigned int pw_clkdis0_7dec : 1;
        unsigned int pw_clkdis0_8hifi : 1;
        unsigned int pw_clkdis0_9vpp : 1;
        unsigned int pw_clkdis0_10dspbbe : 1;
        unsigned int pw_clkdis0_11ddrctrl : 1;
        unsigned int pw_clkdis0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_clkdis0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_clkdis0_14ltebbptop : 1;
        unsigned int pw_clkdis0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_clkdis0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_clkdis0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_clkdis0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_clkdis0_19abbana : 1;
        unsigned int pw_clkdis0_20usbphy : 1;
        unsigned int pw_clkdis0_21reserved : 1;
        unsigned int pw_clkdis0_22cs0phy : 1;
        unsigned int pw_clkdis0_23reserved : 1;
        unsigned int pw_clkdis0_24cs2phy : 1;
        unsigned int pw_clkdis0_25dsiphy : 1;
        unsigned int pw_clkdis0_26hdmiphy : 1;
        unsigned int pw_clkdis0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_clkdis0_29tsensor0 : 1;
        unsigned int pw_clkdis0_30tsensor1 : 1;
        unsigned int pw_clkdis0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLKDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clken1_0acpu0 : 1;
        unsigned int pw_clken1_1acpu1 : 1;
        unsigned int pw_clken1_2acpu2 : 1;
        unsigned int pw_clken1_3acpu3 : 1;
        unsigned int pw_clken1_4cm3mem : 1;
        unsigned int pw_clken1_5mcpu : 1;
        unsigned int pw_clken1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLKEN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_START (6)
#define SOC_AO_SCTRL_SC_PW_CLKEN1_pw_clken1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clkdis1_0acpu0 : 1;
        unsigned int pw_clkdis1_1acpu1 : 1;
        unsigned int pw_clkdis1_2acpu2 : 1;
        unsigned int pw_clkdis1_3acpu3 : 1;
        unsigned int pw_clkdis1_4cm3mem : 1;
        unsigned int pw_clkdis1_5mcpu : 1;
        unsigned int pw_clkdis1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLKDIS1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_START (6)
#define SOC_AO_SCTRL_SC_PW_CLKDIS1_pw_clkdis1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rsten0_0peri : 1;
        unsigned int pw_rsten0_1g3d : 1;
        unsigned int pw_rsten0_2g2d : 1;
        unsigned int pw_rsten0_3edc0 : 1;
        unsigned int pw_rsten0_4edc1 : 1;
        unsigned int pw_rsten0_5isp : 1;
        unsigned int pw_rsten0_6enc : 1;
        unsigned int pw_rsten0_7dec : 1;
        unsigned int pw_rsten0_8hifi : 1;
        unsigned int pw_rsten0_9vpp : 1;
        unsigned int pw_rsten0_10dspbbe : 1;
        unsigned int pw_rsten0_11ddrctrl : 1;
        unsigned int pw_rsten0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_rsten0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_rsten0_14ltebbptop : 1;
        unsigned int pw_rsten0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_rsten0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_rsten0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_rsten0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_rsten0_19abbana : 1;
        unsigned int pw_rsten0_20usbphy : 1;
        unsigned int pw_rsten0_21reserved : 1;
        unsigned int pw_rsten0_22cs0phy : 1;
        unsigned int pw_rsten0_23reserved : 1;
        unsigned int pw_rsten0_24cs2phy : 1;
        unsigned int pw_rsten0_25dsiphy : 1;
        unsigned int pw_rsten0_26hdmiphy : 1;
        unsigned int pw_rsten0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_rsten0_29tsensor0 : 1;
        unsigned int pw_rsten0_30tsensor1 : 1;
        unsigned int pw_rsten0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_RSTEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rstdis0_0peri : 1;
        unsigned int pw_rstdis0_1g3d : 1;
        unsigned int pw_rstdis0_2g2d : 1;
        unsigned int pw_rstdis0_3edc0 : 1;
        unsigned int pw_rstdis0_4edc1 : 1;
        unsigned int pw_rstdis0_5isp : 1;
        unsigned int pw_rstdis0_6enc : 1;
        unsigned int pw_rstdis0_7dec : 1;
        unsigned int pw_rstdis0_8hifi : 1;
        unsigned int pw_rstdis0_9vpp : 1;
        unsigned int pw_rstdis0_10dspbbe : 1;
        unsigned int pw_rstdis0_11ddrctrl : 1;
        unsigned int pw_rstdis0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_rstdis0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_rstdis0_14ltebbptop : 1;
        unsigned int pw_rstdis0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_rstdis0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_rstdis0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_rstdis0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_rstdis0_19abbana : 1;
        unsigned int pw_rstdis0_20usbphy : 1;
        unsigned int pw_rstdis0_21reserved : 1;
        unsigned int pw_rstdis0_22cs0phy : 1;
        unsigned int pw_rstdis0_23reserved : 1;
        unsigned int pw_rstdis0_24cs2phy : 1;
        unsigned int pw_rstdis0_25dsiphy : 1;
        unsigned int pw_rstdis0_26hdmiphy : 1;
        unsigned int pw_rstdis0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_rstdis0_29tsensor0 : 1;
        unsigned int pw_rstdis0_30tsensor1 : 1;
        unsigned int pw_rstdis0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_RSTDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rsten1_0acpu0 : 1;
        unsigned int pw_rsten1_1acpu1 : 1;
        unsigned int pw_rsten1_2acpu2 : 1;
        unsigned int pw_rsten1_3acpu3 : 1;
        unsigned int pw_rsten1_4cm3mem : 1;
        unsigned int pw_rsten1_5mcpu : 1;
        unsigned int pw_rsten1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_RSTEN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_START (6)
#define SOC_AO_SCTRL_SC_PW_RSTEN1_pw_rsten1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rstdis1_0acpu0 : 1;
        unsigned int pw_rstdis1_1acpu1 : 1;
        unsigned int pw_rstdis1_2acpu2 : 1;
        unsigned int pw_rstdis1_3acpu3 : 1;
        unsigned int pw_rstdis1_4cm3mem : 1;
        unsigned int pw_rstdis1_5mcpu : 1;
        unsigned int pw_rstdis1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_RSTDIS1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_START (6)
#define SOC_AO_SCTRL_SC_PW_RSTDIS1_pw_rstdis1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_isoen0_0peri : 1;
        unsigned int pw_isoen0_1g3d : 1;
        unsigned int pw_isoen0_2g2d : 1;
        unsigned int pw_isoen0_3edc0 : 1;
        unsigned int pw_isoen0_4edc1 : 1;
        unsigned int pw_isoen0_5isp : 1;
        unsigned int pw_isoen0_6enc : 1;
        unsigned int pw_isoen0_7dec : 1;
        unsigned int pw_isoen0_8hifi : 1;
        unsigned int pw_isoen0_9vpp : 1;
        unsigned int pw_isoen0_10dspbbe : 1;
        unsigned int pw_isoen0_11ddrctrl : 1;
        unsigned int pw_isoen0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_isoen0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_isoen0_14ltebbptop : 1;
        unsigned int pw_isoen0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_isoen0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_isoen0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_isoen0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_isoen0_19abbana : 1;
        unsigned int pw_isoen0_20usbphy : 1;
        unsigned int pw_isoen0_21reserved : 1;
        unsigned int pw_isoen0_22cs0phy : 1;
        unsigned int pw_isoen0_23reserved : 1;
        unsigned int pw_isoen0_24cs2phy : 1;
        unsigned int pw_isoen0_25dsiphy : 1;
        unsigned int pw_isoen0_26hdmiphy : 1;
        unsigned int pw_isoen0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_isoen0_29tsensor0 : 1;
        unsigned int pw_isoen0_30tsensor1 : 1;
        unsigned int pw_isoen0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISOEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_isodis0_0peri : 1;
        unsigned int pw_isodis0_1g3d : 1;
        unsigned int pw_isodis0_2g2d : 1;
        unsigned int pw_isodis0_3edc0 : 1;
        unsigned int pw_isodis0_4edc1 : 1;
        unsigned int pw_isodis0_5isp : 1;
        unsigned int pw_isodis0_6enc : 1;
        unsigned int pw_isodis0_7dec : 1;
        unsigned int pw_isodis0_8hifi : 1;
        unsigned int pw_isodis0_9vpp : 1;
        unsigned int pw_isodis0_10dspbbe : 1;
        unsigned int pw_isodis0_11ddrctrl : 1;
        unsigned int pw_isodis0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_isodis0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_isodis0_14ltebbptop : 1;
        unsigned int pw_isodis0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_isodis0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_isodis0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_isodis0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_isodis0_19abbana : 1;
        unsigned int pw_isodis0_20usbphy : 1;
        unsigned int pw_isodis0_21reserved : 1;
        unsigned int pw_isodis0_22cs0phy : 1;
        unsigned int pw_isodis0_23reserved : 1;
        unsigned int pw_isodis0_24cs2phy : 1;
        unsigned int pw_isodis0_25dsiphy : 1;
        unsigned int pw_isodis0_26hdmiphy : 1;
        unsigned int pw_isodis0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_isodis0_29tsensor0 : 1;
        unsigned int pw_isodis0_30tsensor1 : 1;
        unsigned int pw_isodis0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISODIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_isoen1_0acpu0 : 1;
        unsigned int pw_isoen1_1acpu1 : 1;
        unsigned int pw_isoen1_2acpu2 : 1;
        unsigned int pw_isoen1_3acpu3 : 1;
        unsigned int pw_isoen1_4cm3mem : 1;
        unsigned int pw_isoen1_5mcpu : 1;
        unsigned int pw_isoen1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISOEN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_START (6)
#define SOC_AO_SCTRL_SC_PW_ISOEN1_pw_isoen1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_isodis1_0acpu0 : 1;
        unsigned int pw_isodis1_1acpu1 : 1;
        unsigned int pw_isodis1_2acpu2 : 1;
        unsigned int pw_isodis1_3acpu3 : 1;
        unsigned int pw_isodis1_4cm3mem : 1;
        unsigned int pw_isodis1_5mcpu : 1;
        unsigned int pw_isodis1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISODIS1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_START (6)
#define SOC_AO_SCTRL_SC_PW_ISODIS1_pw_isodis1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_en0_0peri : 1;
        unsigned int pw_en0_1g3d : 1;
        unsigned int pw_en0_2g2d : 1;
        unsigned int pw_en0_3edc0 : 1;
        unsigned int pw_en0_4edc1 : 1;
        unsigned int pw_en0_5isp : 1;
        unsigned int pw_en0_6enc : 1;
        unsigned int pw_en0_7dec : 1;
        unsigned int pw_en0_8hifi : 1;
        unsigned int pw_en0_9vpp : 1;
        unsigned int pw_en0_10dspbbe : 1;
        unsigned int pw_en0_11ddrctrl : 1;
        unsigned int pw_en0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_en0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_en0_14ltebbptop : 1;
        unsigned int pw_en0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_en0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_en0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_en0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_en0_19abbana : 1;
        unsigned int pw_en0_20usbphy : 1;
        unsigned int pw_en0_21reserved : 1;
        unsigned int pw_en0_22cs0phy : 1;
        unsigned int pw_en0_23reserved : 1;
        unsigned int pw_en0_24cs2phy : 1;
        unsigned int pw_en0_25dsiphy : 1;
        unsigned int pw_en0_26hdmiphy : 1;
        unsigned int pw_en0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_en0_29tsensor0 : 1;
        unsigned int pw_en0_30tsensor1 : 1;
        unsigned int pw_en0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_EN0_pw_en0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_dis0_0peri : 1;
        unsigned int pw_dis0_1g3d : 1;
        unsigned int pw_dis0_2g2d : 1;
        unsigned int pw_dis0_3edc0 : 1;
        unsigned int pw_dis0_4edc1 : 1;
        unsigned int pw_dis0_5isp : 1;
        unsigned int pw_dis0_6enc : 1;
        unsigned int pw_dis0_7dec : 1;
        unsigned int pw_dis0_8hifi : 1;
        unsigned int pw_dis0_9vpp : 1;
        unsigned int pw_dis0_10dspbbe : 1;
        unsigned int pw_dis0_11ddrctrl : 1;
        unsigned int pw_dis0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_dis0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_dis0_14ltebbptop : 1;
        unsigned int pw_dis0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_dis0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_dis0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_dis0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_dis0_19abbana : 1;
        unsigned int pw_dis0_20usbphy : 1;
        unsigned int pw_dis0_21reserved : 1;
        unsigned int pw_dis0_22cs0phy : 1;
        unsigned int pw_dis0_23reserved : 1;
        unsigned int pw_dis0_24cs2phy : 1;
        unsigned int pw_dis0_25dsiphy : 1;
        unsigned int pw_dis0_26hdmiphy : 1;
        unsigned int pw_dis0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_dis0_29tsensor0 : 1;
        unsigned int pw_dis0_30tsensor1 : 1;
        unsigned int pw_dis0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_DIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_DIS0_pw_dis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_en1_0acpu0 : 1;
        unsigned int pw_en1_1acpu1 : 1;
        unsigned int pw_en1_2acpu2 : 1;
        unsigned int pw_en1_3acpu3 : 1;
        unsigned int pw_en1_4cm3mem : 1;
        unsigned int pw_en1_5mcpu : 1;
        unsigned int pw_en1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_EN1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_START (6)
#define SOC_AO_SCTRL_SC_PW_EN1_pw_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_dis1_0acpu0 : 1;
        unsigned int pw_dis1_1acpu1 : 1;
        unsigned int pw_dis1_2acpu2 : 1;
        unsigned int pw_dis1_3acpu3 : 1;
        unsigned int pw_dis1_4cm3mem : 1;
        unsigned int pw_dis1_5mcpu : 1;
        unsigned int pw_dis1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_DIS1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_START (6)
#define SOC_AO_SCTRL_SC_PW_DIS1_pw_dis1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtcmos_ack_isoen0_3reserved : 4;
        unsigned int mtcmos_ack_isoen0_4reserved : 1;
        unsigned int mtcmos_ack_isoen0_5reserved : 1;
        unsigned int mtcmos_ack_isoen0_6reserved : 1;
        unsigned int mtcmos_ack_isoen0_7reserved : 1;
        unsigned int mtcmos_ack_isoen0_8reserved : 1;
        unsigned int mtcmos_ack_isoen0_9reserved : 1;
        unsigned int mtcmos_ack_isoen0_10reserved : 1;
        unsigned int mtcmos_ack_isoen0_11reserved : 1;
        unsigned int mtcmos_ack_isoen0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int mtcmos_ack_isoen0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int mtcmos_ack_isoen0_14ltebbptop : 1;
        unsigned int mtcmos_ack_isoen0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int mtcmos_ack_isoen0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int mtcmos_ack_isoen0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int mtcmos_ack_isoen0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int mtcmos_ack_isoen0_24reserved : 6;
        unsigned int mtcmos_ack_isoen0_25reserved : 1;
        unsigned int mtcmos_ack_isoen0_31reserved : 6;
    } reg;
} SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_3reserved_START (0)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_3reserved_END (3)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_5reserved_START (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_5reserved_END (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_6reserved_START (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_6reserved_END (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_7reserved_START (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_8reserved_START (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_8reserved_END (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_9reserved_START (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_9reserved_END (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_10reserved_START (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_10reserved_END (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_11reserved_START (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_11reserved_END (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_24reserved_START (19)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_24reserved_END (24)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_25reserved_START (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_25reserved_END (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_31reserved_START (26)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOEN0_mtcmos_ack_isoen0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtcmos_ack_isodis0_3reserved : 4;
        unsigned int mtcmos_ack_isodis0_4reserved : 1;
        unsigned int mtcmos_ack_isodis0_5reserved : 1;
        unsigned int mtcmos_ack_isodis0_6reserved : 1;
        unsigned int mtcmos_ack_isodis0_7reserved : 1;
        unsigned int mtcmos_ack_isodis0_8reserved : 1;
        unsigned int mtcmos_ack_isodis0_9reserved : 1;
        unsigned int mtcmos_ack_isodis0_10reserved : 1;
        unsigned int mtcmos_ack_isodis0_11reserved : 1;
        unsigned int mtcmos_ack_isodis0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int mtcmos_ack_isodis0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int mtcmos_ack_isodis0_14ltebbptop : 1;
        unsigned int mtcmos_ack_isodis0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int mtcmos_ack_isodis0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int mtcmos_ack_isodis0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int mtcmos_ack_isodis0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int mtcmos_ack_isodis0_24reserved : 6;
        unsigned int mtcmos_ack_isodis0_25reserved : 1;
        unsigned int mtcmos_ack_isodis0_31reserved : 6;
    } reg;
} SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_3reserved_START (0)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_3reserved_END (3)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_5reserved_START (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_5reserved_END (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_6reserved_START (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_6reserved_END (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_7reserved_START (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_8reserved_START (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_8reserved_END (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_9reserved_START (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_9reserved_END (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_10reserved_START (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_10reserved_END (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_11reserved_START (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_11reserved_END (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_24reserved_START (19)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_24reserved_END (24)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_25reserved_START (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_25reserved_END (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_31reserved_START (26)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISODIS0_mtcmos_ack_isodis0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mtcmos_ack_isostat0_3reserved : 4;
        unsigned int mtcmos_ack_isostat0_4reserved : 1;
        unsigned int mtcmos_ack_isostat0_5reserved : 1;
        unsigned int mtcmos_ack_isostat0_6reserved : 1;
        unsigned int mtcmos_ack_isostat0_7reserved : 1;
        unsigned int mtcmos_ack_isostat0_8reserved : 1;
        unsigned int mtcmos_ack_isostat0_9reserved : 1;
        unsigned int mtcmos_ack_isostat0_10reserved : 1;
        unsigned int mtcmos_ack_isostat0_11reserved : 1;
        unsigned int mtcmos_ack_isostat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int mtcmos_ack_isostat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int mtcmos_ack_isostat0_14ltebbptop : 1;
        unsigned int mtcmos_ack_isostat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int mtcmos_ack_isostat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int mtcmos_ack_isostat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int mtcmos_ack_isostat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int mtcmos_ack_isostat0_24reserved : 6;
        unsigned int mtcmos_ack_isostat0_25reserved : 1;
        unsigned int mtcmos_ack_isostat0_31reserved : 6;
    } reg;
} SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_3reserved_START (0)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_3reserved_END (3)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_5reserved_START (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_5reserved_END (5)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_6reserved_START (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_6reserved_END (6)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_7reserved_START (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_8reserved_START (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_8reserved_END (8)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_9reserved_START (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_9reserved_END (9)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_10reserved_START (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_10reserved_END (10)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_11reserved_START (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_11reserved_END (11)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_24reserved_START (19)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_24reserved_END (24)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_25reserved_START (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_25reserved_END (25)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_31reserved_START (26)
#define SOC_AO_SCTRL_SC_MTCMOS_ACK_ISOSTAT0_mtcmos_ack_isostat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_stat_3acpu0 : 4;
        unsigned int pw_stat_7acpu1 : 4;
        unsigned int pw_stat_11acpu2 : 4;
        unsigned int pw_stat_15acpu3 : 4;
        unsigned int pw_stat_19reserved : 4;
        unsigned int pw_stat_23carm : 4;
        unsigned int mcu_subsys_state0_sleepholdreq_n : 1;
        unsigned int mcu_subsys_state0_sleepholdack_n : 1;
        unsigned int reserved : 2;
        unsigned int pw_stat : 4;
    } reg;
} SOC_AO_SCTRL_SC_PW_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_3acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_3acpu0_END (3)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_7acpu1_START (4)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_7acpu1_END (7)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_11acpu2_START (8)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_11acpu2_END (11)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_15acpu3_START (12)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_15acpu3_END (15)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_19reserved_START (16)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_19reserved_END (19)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_23carm_START (20)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_23carm_END (23)
#define SOC_AO_SCTRL_SC_PW_STAT0_mcu_subsys_state0_sleepholdreq_n_START (24)
#define SOC_AO_SCTRL_SC_PW_STAT0_mcu_subsys_state0_sleepholdreq_n_END (24)
#define SOC_AO_SCTRL_SC_PW_STAT0_mcu_subsys_state0_sleepholdack_n_START (25)
#define SOC_AO_SCTRL_SC_PW_STAT0_mcu_subsys_state0_sleepholdack_n_END (25)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_START (28)
#define SOC_AO_SCTRL_SC_PW_STAT0_pw_stat_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_mtcmos_ack_stat0_0peri : 1;
        unsigned int pw_mtcmos_ack_stat0_1g3d : 1;
        unsigned int pw_mtcmos_ack_stat0_2g2d : 1;
        unsigned int pw_mtcmos_ack_stat0_3edc0 : 1;
        unsigned int pw_mtcmos_ack_stat0_4edc1 : 1;
        unsigned int pw_mtcmos_ack_stat0_5isp : 1;
        unsigned int pw_mtcmos_ack_stat0_6enc : 1;
        unsigned int pw_mtcmos_ack_stat0_7dec : 1;
        unsigned int pw_mtcmos_ack_stat0_8hifi : 1;
        unsigned int pw_mtcmos_ack_stat0_9vpp : 1;
        unsigned int pw_mtcmos_ack_stat0_10dspbbe : 1;
        unsigned int pw_mtcmos_ack_stat0_11ddrctrl : 1;
        unsigned int pw_mtcmos_ack_stat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_mtcmos_ack_stat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_mtcmos_ack_stat0_14ltebbptop : 1;
        unsigned int pw_mtcmos_ack_stat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_mtcmos_ack_stat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_mtcmos_ack_stat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_mtcmos_ack_stat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_mtcmos_ack_stat0_19abbana : 1;
        unsigned int pw_mtcmos_ack_stat0_20usbphy : 1;
        unsigned int pw_mtcmos_ack_stat0_21reserved : 1;
        unsigned int pw_mtcmos_ack_stat0_22cs0phy : 1;
        unsigned int pw_mtcmos_ack_stat0_23reserved : 1;
        unsigned int pw_mtcmos_ack_stat0_24cs2phy : 1;
        unsigned int pw_mtcmos_ack_stat0_25dsiphy : 1;
        unsigned int pw_mtcmos_ack_stat0_26hdmiphy : 1;
        unsigned int pw_mtcmos_ack_stat0_27ddrphy : 1;
        unsigned int pw_mtcmos_ack_stat0_28pll1 : 1;
        unsigned int pw_mtcmos_ack_stat0_29tsensor0 : 1;
        unsigned int pw_mtcmos_ack_stat0_30tsensor1 : 1;
        unsigned int pw_mtcmos_ack_stat0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_MTCMOS_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_0peri_START (0)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_0peri_END (0)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_5isp_START (5)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_5isp_END (5)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_6enc_START (6)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_6enc_END (6)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_7dec_START (7)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_7dec_END (7)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_28pll1_START (28)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_28pll1_END (28)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT0_pw_mtcmos_ack_stat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_mtcmos_ack_stat1_0acpu0 : 1;
        unsigned int pw_mtcmos_ack_stat1_1acpu1 : 1;
        unsigned int pw_mtcmos_ack_stat1_2acpu2 : 1;
        unsigned int pw_mtcmos_ack_stat1_3acpu3 : 1;
        unsigned int pw_mtcmos_ack_stat1_4cm3mem : 1;
        unsigned int pw_mtcmos_ack_stat1_5mcpu : 1;
        unsigned int pw_mtcmos_ack_stat1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_MTCMOS_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_START (6)
#define SOC_AO_SCTRL_SC_MTCMOS_STAT1_pw_mtcmos_ack_stat1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clk_stat0_0peri : 1;
        unsigned int pw_clk_stat0_1g3d : 1;
        unsigned int pw_clk_stat0_2g2d : 1;
        unsigned int pw_clk_stat0_3edc0 : 1;
        unsigned int pw_clk_stat0_4edc1 : 1;
        unsigned int pw_clk_stat0_5isp : 1;
        unsigned int pw_clk_stat0_6enc : 1;
        unsigned int pw_clk_stat0_7dec : 1;
        unsigned int pw_clk_stat0_8hifi : 1;
        unsigned int pw_clk_stat0_9vpp : 1;
        unsigned int pw_clk_stat0_10dspbbe : 1;
        unsigned int pw_clk_stat0_11ddrctrl : 1;
        unsigned int pw_clk_stat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_clk_stat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_clk_stat0_14ltebbptop : 1;
        unsigned int pw_clk_stat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_clk_stat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_clk_stat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_clk_stat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_clk_stat0_19abbana : 1;
        unsigned int pw_clk_stat0_20usbphy : 1;
        unsigned int pw_clk_stat0_21reserved : 1;
        unsigned int pw_clk_stat0_22cs0phy : 1;
        unsigned int pw_clk_stat0_23reserved : 1;
        unsigned int pw_clk_stat0_24cs2phy : 1;
        unsigned int pw_clk_stat0_25dsiphy : 1;
        unsigned int pw_clk_stat0_26hdmiphy : 1;
        unsigned int pw_clk_stat0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_clk_stat0_29tsensor0 : 1;
        unsigned int pw_clk_stat0_30tsensor1 : 1;
        unsigned int pw_clk_stat0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLK_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT0_pw_clk_stat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_clk_stat1_0acpu0 : 1;
        unsigned int pw_clk_stat1_1acpu1 : 1;
        unsigned int pw_clk_stat1_2acpu2 : 1;
        unsigned int pw_clk_stat1_3acpu3 : 1;
        unsigned int pw_clk_stat1_4cm3mem : 1;
        unsigned int pw_clk_stat1_5mcpu : 1;
        unsigned int pw_clk_stat1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_CLK_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_START (6)
#define SOC_AO_SCTRL_SC_PW_CLK_STAT1_pw_clk_stat1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_iso_stat0_0peri : 1;
        unsigned int pw_iso_stat0_1g3d : 1;
        unsigned int pw_iso_stat0_2g2d : 1;
        unsigned int pw_iso_stat0_3edc0 : 1;
        unsigned int pw_iso_stat0_4edc1 : 1;
        unsigned int pw_iso_stat0_5isp : 1;
        unsigned int pw_iso_stat0_6enc : 1;
        unsigned int pw_iso_stat0_7dec : 1;
        unsigned int pw_iso_stat0_8hifi : 1;
        unsigned int pw_iso_stat0_9vpp : 1;
        unsigned int pw_iso_stat0_10dspbbe : 1;
        unsigned int pw_iso_stat0_11ddrctrl : 1;
        unsigned int pw_iso_stat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_iso_stat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_iso_stat0_14ltebbptop : 1;
        unsigned int pw_iso_stat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_iso_stat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_iso_stat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_iso_stat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_iso_stat0_19abbana : 1;
        unsigned int pw_iso_stat0_20usbphy : 1;
        unsigned int pw_iso_stat0_21reserved : 1;
        unsigned int pw_iso_stat0_22cs0phy : 1;
        unsigned int pw_iso_stat0_23reserved : 1;
        unsigned int pw_iso_stat0_24cs2phy : 1;
        unsigned int pw_iso_stat0_25dsiphy : 1;
        unsigned int pw_iso_stat0_26hdmiphy : 1;
        unsigned int pw_iso_stat0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_iso_stat0_29tsensor0 : 1;
        unsigned int pw_iso_stat0_30tsensor1 : 1;
        unsigned int pw_iso_stat0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISO_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT0_pw_iso_stat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_iso_stat1_0acpu0 : 1;
        unsigned int pw_iso_stat1_1acpu1 : 1;
        unsigned int pw_iso_stat1_2acpu2 : 1;
        unsigned int pw_iso_stat1_3acpu3 : 1;
        unsigned int pw_iso_stat1_4cm3mem : 1;
        unsigned int pw_iso_stat1_5mcpu : 1;
        unsigned int pw_iso_stat1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_ISO_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_START (6)
#define SOC_AO_SCTRL_SC_PW_ISO_STAT1_pw_iso_stat1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rst_stat0_0peri : 1;
        unsigned int pw_rst_stat0_1g3d : 1;
        unsigned int pw_rst_stat0_2g2d : 1;
        unsigned int pw_rst_stat0_3edc0 : 1;
        unsigned int pw_rst_stat0_4edc1 : 1;
        unsigned int pw_rst_stat0_5isp : 1;
        unsigned int pw_rst_stat0_6enc : 1;
        unsigned int pw_rst_stat0_7dec : 1;
        unsigned int pw_rst_stat0_8hifi : 1;
        unsigned int pw_rst_stat0_9vpp : 1;
        unsigned int pw_rst_stat0_10dspbbe : 1;
        unsigned int pw_rst_stat0_11ddrctrl : 1;
        unsigned int pw_rst_stat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_rst_stat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_rst_stat0_14ltebbptop : 1;
        unsigned int pw_rst_stat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_rst_stat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_rst_stat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_rst_stat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_rst_stat0_19abbana : 1;
        unsigned int pw_rst_stat0_20usbphy : 1;
        unsigned int pw_rst_stat0_21reserved : 1;
        unsigned int pw_rst_stat0_22cs0phy : 1;
        unsigned int pw_rst_stat0_23reserved : 1;
        unsigned int pw_rst_stat0_24cs2phy : 1;
        unsigned int pw_rst_stat0_25dsiphy : 1;
        unsigned int pw_rst_stat0_26hdmiphy : 1;
        unsigned int pw_rst_stat0_27ddrphy : 1;
        unsigned int reserved : 1;
        unsigned int pw_rst_stat0_29tsensor0 : 1;
        unsigned int pw_rst_stat0_30tsensor1 : 1;
        unsigned int pw_rst_stat0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_RST_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_RST_STAT0_pw_rst_stat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_rst_stat1_0acpu0 : 1;
        unsigned int pw_rst_stat1_1acpu1 : 1;
        unsigned int pw_rst_stat1_2acpu2 : 1;
        unsigned int pw_rst_stat1_3acpu3 : 1;
        unsigned int pw_rst_stat1_4cm3mem : 1;
        unsigned int pw_rst_stat1_5mcpu : 1;
        unsigned int pw_rst_stat1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_RST_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_START (6)
#define SOC_AO_SCTRL_SC_PW_RST_STAT1_pw_rst_stat1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_mtcmos_timeout_stat0_0peri : 1;
        unsigned int pw_mtcmos_timeout_stat0_1g3d : 1;
        unsigned int pw_mtcmos_timeout_stat0_2g2d : 1;
        unsigned int pw_mtcmos_timeout_stat0_3edc0 : 1;
        unsigned int pw_mtcmos_timeout_stat0_4edc1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_5isp : 1;
        unsigned int pw_mtcmos_timeout_stat0_6enc : 1;
        unsigned int pw_mtcmos_timeout_stat0_7dec : 1;
        unsigned int pw_mtcmos_timeout_stat0_8hifi : 1;
        unsigned int pw_mtcmos_timeout_stat0_9vpp : 1;
        unsigned int pw_mtcmos_timeout_stat0_10dspbbe : 1;
        unsigned int pw_mtcmos_timeout_stat0_11ddrctrl : 1;
        unsigned int pw_mtcmos_timeout_stat0_12bbpcommtop2c_gbbp1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_13bbpcommtop2d_gbbp2 : 1;
        unsigned int pw_mtcmos_timeout_stat0_14ltebbptop : 1;
        unsigned int pw_mtcmos_timeout_stat0_15bbpcommtop2b_bbpcomm2 : 1;
        unsigned int pw_mtcmos_timeout_stat0_16bbpcommtop2a_bbpcomm1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_17bbpcommtop1b_wtdbbp2 : 1;
        unsigned int pw_mtcmos_timeout_stat0_18bbpcommtop1a_wtdbbp1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_19abbana : 1;
        unsigned int pw_mtcmos_timeout_stat0_20usbphy : 1;
        unsigned int pw_mtcmos_timeout_stat0_21reserved : 1;
        unsigned int pw_mtcmos_timeout_stat0_22cs0phy : 1;
        unsigned int pw_mtcmos_timeout_stat0_23reserved : 1;
        unsigned int pw_mtcmos_timeout_stat0_24cs2phy : 1;
        unsigned int pw_mtcmos_timeout_stat0_25dsiphy : 1;
        unsigned int pw_mtcmos_timeout_stat0_26hdmiphy : 1;
        unsigned int pw_mtcmos_timeout_stat0_27ddrphy : 1;
        unsigned int pw_mtcmos_timeout_stat0_28pll1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_29tsensor0 : 1;
        unsigned int pw_mtcmos_timeout_stat0_30tsensor1 : 1;
        unsigned int pw_mtcmos_timeout_stat0_31reserved : 1;
    } reg;
} SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_0peri_START (0)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_0peri_END (0)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_1g3d_START (1)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_1g3d_END (1)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_2g2d_START (2)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_2g2d_END (2)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_3edc0_START (3)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_3edc0_END (3)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_4edc1_START (4)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_4edc1_END (4)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_5isp_START (5)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_5isp_END (5)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_6enc_START (6)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_6enc_END (6)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_7dec_START (7)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_7dec_END (7)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_8hifi_START (8)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_8hifi_END (8)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_9vpp_START (9)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_9vpp_END (9)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_10dspbbe_START (10)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_10dspbbe_END (10)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_11ddrctrl_START (11)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_11ddrctrl_END (11)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_12bbpcommtop2c_gbbp1_START (12)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_12bbpcommtop2c_gbbp1_END (12)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_13bbpcommtop2d_gbbp2_START (13)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_13bbpcommtop2d_gbbp2_END (13)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_14ltebbptop_START (14)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_14ltebbptop_END (14)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_15bbpcommtop2b_bbpcomm2_START (15)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_15bbpcommtop2b_bbpcomm2_END (15)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_16bbpcommtop2a_bbpcomm1_START (16)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_16bbpcommtop2a_bbpcomm1_END (16)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_17bbpcommtop1b_wtdbbp2_START (17)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_17bbpcommtop1b_wtdbbp2_END (17)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_18bbpcommtop1a_wtdbbp1_START (18)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_18bbpcommtop1a_wtdbbp1_END (18)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_19abbana_START (19)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_19abbana_END (19)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_20usbphy_START (20)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_20usbphy_END (20)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_21reserved_START (21)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_21reserved_END (21)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_22cs0phy_START (22)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_22cs0phy_END (22)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_23reserved_START (23)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_23reserved_END (23)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_24cs2phy_START (24)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_24cs2phy_END (24)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_25dsiphy_START (25)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_25dsiphy_END (25)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_26hdmiphy_START (26)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_26hdmiphy_END (26)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_27ddrphy_START (27)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_27ddrphy_END (27)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_28pll1_START (28)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_28pll1_END (28)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_29tsensor0_START (29)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_29tsensor0_END (29)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_30tsensor1_START (30)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_30tsensor1_END (30)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_31reserved_START (31)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT0_pw_mtcmos_timeout_stat0_31reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pw_mtcmos_timeout_stat1_0acpu0 : 1;
        unsigned int pw_mtcmos_timeout_stat1_1acpu1 : 1;
        unsigned int pw_mtcmos_timeout_stat1_2acpu2 : 1;
        unsigned int pw_mtcmos_timeout_stat1_3acpu3 : 1;
        unsigned int pw_mtcmos_timeout_stat1_4cm3mem : 1;
        unsigned int pw_mtcmos_timeout_stat1_5mcpu : 1;
        unsigned int pw_mtcmos_timeout1 : 26;
    } reg;
} SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_4cm3mem_START (4)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_4cm3mem_END (4)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout_stat1_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout1_START (6)
#define SOC_AO_SCTRL_SC_PW_MTCMOS_TIMEOUT_STAT1_pw_mtcmos_timeout1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time0_15socperi : 16;
        unsigned int pwup_time0_31g3d : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME0_pwup_time0_15socperi_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME0_pwup_time0_15socperi_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME0_pwup_time0_31g3d_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME0_pwup_time0_31g3d_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time1_15g2d : 16;
        unsigned int pwup_time1_31edc0 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME1_pwup_time1_15g2d_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME1_pwup_time1_15g2d_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME1_pwup_time1_31edc0_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME1_pwup_time1_31edc0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time2_15edc1 : 16;
        unsigned int pwup_time2_31isp : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME2_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME2_pwup_time2_15edc1_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME2_pwup_time2_15edc1_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME2_pwup_time2_31isp_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME2_pwup_time2_31isp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time3_15enc : 16;
        unsigned int pwup_time3_31dec : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME3_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME3_pwup_time3_15enc_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME3_pwup_time3_15enc_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME3_pwup_time3_31dec_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME3_pwup_time3_31dec_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time4_15hifi : 16;
        unsigned int pwup_time4_31vpp : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME4_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME4_pwup_time4_15hifi_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME4_pwup_time4_15hifi_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME4_pwup_time4_31vpp_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME4_pwup_time4_31vpp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time5_15dspbbe : 16;
        unsigned int pwup_time5_31ddrctrl : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME5_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME5_pwup_time5_15dspbbe_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME5_pwup_time5_15dspbbe_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME5_pwup_time5_31ddrctrl_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME5_pwup_time5_31ddrctrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time6_15bbpcommtop2c_gbbp1 : 16;
        unsigned int pwup_time6_31bbpcommtop2d_gbbp2 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME6_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME6_pwup_time6_15bbpcommtop2c_gbbp1_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME6_pwup_time6_15bbpcommtop2c_gbbp1_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME6_pwup_time6_31bbpcommtop2d_gbbp2_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME6_pwup_time6_31bbpcommtop2d_gbbp2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time7_15ltebbptop : 16;
        unsigned int pwup_time7_31bbpcommtop2b_bbpcomm2 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME7_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME7_pwup_time7_15ltebbptop_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME7_pwup_time7_15ltebbptop_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME7_pwup_time7_31bbpcommtop2b_bbpcomm2_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME7_pwup_time7_31bbpcommtop2b_bbpcomm2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time8_15reserved : 16;
        unsigned int pwup_time8_31bbpcommtop1b_wtdbbp2 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME8_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME8_pwup_time8_15reserved_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME8_pwup_time8_15reserved_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME8_pwup_time8_31bbpcommtop1b_wtdbbp2_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME8_pwup_time8_31bbpcommtop1b_wtdbbp2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time9_15bbpcommtop1a_wtdbbp1 : 16;
        unsigned int pwup_time9_31acpu3 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME9_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME9_pwup_time9_15bbpcommtop1a_wtdbbp1_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME9_pwup_time9_15bbpcommtop1a_wtdbbp1_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME9_pwup_time9_31acpu3_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME9_pwup_time9_31acpu3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time10_15acpu0 : 16;
        unsigned int pwup_time10_31acpu1 : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME10_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME10_pwup_time10_15acpu0_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME10_pwup_time10_15acpu0_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME10_pwup_time10_31acpu1_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME10_pwup_time10_31acpu1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwup_time11_15acpu2 : 16;
        unsigned int pwup_time11_31mcpu : 16;
    } reg;
} SOC_AO_SCTRL_SC_PWUP_TIME11_UNION;
#endif
#define SOC_AO_SCTRL_SC_PWUP_TIME11_pwup_time11_15acpu2_START (0)
#define SOC_AO_SCTRL_SC_PWUP_TIME11_pwup_time11_15acpu2_END (15)
#define SOC_AO_SCTRL_SC_PWUP_TIME11_pwup_time11_31mcpu_START (16)
#define SOC_AO_SCTRL_SC_PWUP_TIME11_pwup_time11_31mcpu_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aarm_pwdn_harden0_0acpu0 : 1;
        unsigned int aarm_pwdn_harden0_1acpu1 : 1;
        unsigned int aarm_pwdn_harden0_2acpu2 : 1;
        unsigned int aarm_pwdn_harden0_3acpu3 : 1;
        unsigned int aarm_pwdn_harden0_4reserved : 1;
        unsigned int aarm_pwdn_harden0_5mcpu : 1;
        unsigned int aarm_pwdn_harden0 : 26;
    } reg;
} SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_START (6)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDEN0_aarm_pwdn_harden0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aarm_pwdn_harddis0_0acpu0 : 1;
        unsigned int aarm_pwdn_harddis0_1acpu1 : 1;
        unsigned int aarm_pwdn_harddis0_2acpu2 : 1;
        unsigned int aarm_pwdn_harddis0_3acpu3 : 1;
        unsigned int aarm_pwdn_harddis0_4reserved : 1;
        unsigned int aarm_pwdn_harddis0_5mcpu : 1;
        unsigned int aarm_pwdn_harddis0 : 26;
    } reg;
} SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_START (6)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDDIS0_aarm_pwdn_harddis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aarm_pwdn_hardstat0_0acpu0 : 1;
        unsigned int aarm_pwdn_hardstat0_1acpu1 : 1;
        unsigned int aarm_pwdn_hardstat0_2acpu2 : 1;
        unsigned int aarm_pwdn_hardstat0_3acpu3 : 1;
        unsigned int aarm_pwdn_hardstat0_4reserved : 1;
        unsigned int aarm_pwdn_hardstat0_5mcpu : 1;
        unsigned int aarm_pwdn_hardstat0 : 26;
    } reg;
} SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_0acpu0_START (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_0acpu0_END (0)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_1acpu1_START (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_1acpu1_END (1)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_2acpu2_START (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_2acpu2_END (2)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_3acpu3_START (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_3acpu3_END (3)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_4reserved_START (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_4reserved_END (4)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_5mcpu_START (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_5mcpu_END (5)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_START (6)
#define SOC_AO_SCTRL_SC_ARM_PWDN_HARDSTAT0_aarm_pwdn_hardstat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_pw_dn_en : 1;
        unsigned int reserved_0 : 1;
        unsigned int aarm_pw_dn_sft3 : 1;
        unsigned int aarm_pw_dn_sft2 : 1;
        unsigned int aarm_pw_dn_sft1 : 1;
        unsigned int aarm_pw_dn_sft0 : 1;
        unsigned int carm_pw_dn_sft : 1;
        unsigned int reserved_1 : 1;
        unsigned int vddp1_4_io_ret : 1;
        unsigned int m3_ram_ctrl_sftbypass : 1;
        unsigned int aarm_l2_ram_ctrl_sftbypass : 1;
        unsigned int reserved_2 : 5;
        unsigned int soc_pw_dn_en_msk : 1;
        unsigned int pw_ctrl_reserved1_msk : 1;
        unsigned int aarm_pw_dn_sft3_msk : 1;
        unsigned int aarm_pw_dn_sft2_msk : 1;
        unsigned int aarm_pw_dn_sft1_msk : 1;
        unsigned int aarm_pw_dn_sft0_msk : 1;
        unsigned int carm_pw_dn_sft_msk : 1;
        unsigned int reserved_3 : 1;
        unsigned int vddp1_4_io_ret_msk : 1;
        unsigned int m3_ram_ctrl_sftbypass_msk : 1;
        unsigned int aarm_l2_ram_ctrl_sftbypass_msk : 1;
        unsigned int reserved_4 : 5;
    } reg;
} SOC_AO_SCTRL_SC_PW_CTRL_UNION;
#endif
#define SOC_AO_SCTRL_SC_PW_CTRL_soc_pw_dn_en_START (0)
#define SOC_AO_SCTRL_SC_PW_CTRL_soc_pw_dn_en_END (0)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_START (2)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_END (2)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_START (3)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_END (3)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_START (4)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_END (4)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft0_START (5)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft0_END (5)
#define SOC_AO_SCTRL_SC_PW_CTRL_carm_pw_dn_sft_START (6)
#define SOC_AO_SCTRL_SC_PW_CTRL_carm_pw_dn_sft_END (6)
#define SOC_AO_SCTRL_SC_PW_CTRL_vddp1_4_io_ret_START (8)
#define SOC_AO_SCTRL_SC_PW_CTRL_vddp1_4_io_ret_END (8)
#define SOC_AO_SCTRL_SC_PW_CTRL_m3_ram_ctrl_sftbypass_START (9)
#define SOC_AO_SCTRL_SC_PW_CTRL_m3_ram_ctrl_sftbypass_END (9)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_l2_ram_ctrl_sftbypass_START (10)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_l2_ram_ctrl_sftbypass_END (10)
#define SOC_AO_SCTRL_SC_PW_CTRL_soc_pw_dn_en_msk_START (16)
#define SOC_AO_SCTRL_SC_PW_CTRL_soc_pw_dn_en_msk_END (16)
#define SOC_AO_SCTRL_SC_PW_CTRL_pw_ctrl_reserved1_msk_START (17)
#define SOC_AO_SCTRL_SC_PW_CTRL_pw_ctrl_reserved1_msk_END (17)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_msk_START (18)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft3_msk_END (18)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_msk_START (19)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft2_msk_END (19)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_msk_START (20)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft1_msk_END (20)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft0_msk_START (21)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_pw_dn_sft0_msk_END (21)
#define SOC_AO_SCTRL_SC_PW_CTRL_carm_pw_dn_sft_msk_START (22)
#define SOC_AO_SCTRL_SC_PW_CTRL_carm_pw_dn_sft_msk_END (22)
#define SOC_AO_SCTRL_SC_PW_CTRL_vddp1_4_io_ret_msk_START (24)
#define SOC_AO_SCTRL_SC_PW_CTRL_vddp1_4_io_ret_msk_END (24)
#define SOC_AO_SCTRL_SC_PW_CTRL_m3_ram_ctrl_sftbypass_msk_START (25)
#define SOC_AO_SCTRL_SC_PW_CTRL_m3_ram_ctrl_sftbypass_msk_END (25)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_l2_ram_ctrl_sftbypass_msk_START (26)
#define SOC_AO_SCTRL_SC_PW_CTRL_aarm_l2_ram_ctrl_sftbypass_msk_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_en0_0coresight : 1;
        unsigned int sc_mcpusleep_vote_en0_1coresight : 1;
        unsigned int sc_mcpusleep_vote_en0_2ipf : 1;
        unsigned int sc_mcpusleep_vote_en0_3socp : 1;
        unsigned int sc_mcpusleep_vote_en0_7reserved : 4;
        unsigned int sc_mcpusleep_vote_en0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTEEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_3socp_START (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_3socp_END (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_START (8)
#define SOC_AO_SCTRL_SC_MCPU_VOTEEN0_sc_mcpusleep_vote_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_dis0_0coresight : 1;
        unsigned int sc_mcpusleep_vote_dis0_1coresight : 1;
        unsigned int sc_mcpusleep_vote_dis0_2ipf : 1;
        unsigned int sc_mcpusleep_vote_dis0_3socp : 1;
        unsigned int sc_mcpusleep_vote_dis0_7reserved : 4;
        unsigned int sc_mcpusleep_vote_dis0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_3socp_START (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_3socp_END (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_START (8)
#define SOC_AO_SCTRL_SC_MCPU_VOTEDIS0_sc_mcpusleep_vote_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_stat0_0coresight : 1;
        unsigned int sc_mcpusleep_vote_stat0_1coresight : 1;
        unsigned int sc_mcpusleep_vote_stat0_2ipf : 1;
        unsigned int sc_mcpusleep_vote_stat0_3socp : 1;
        unsigned int sc_mcpusleep_vote_stat0_7reserved : 4;
        unsigned int sc_mcpusleep_vote_stat0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_3socp_START (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_3socp_END (3)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_START (8)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_sc_mcpusleep_vote_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTE_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK0_sc_mcpusleep_vote_msk0_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK0_sc_mcpusleep_vote_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTE_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK1_sc_mcpusleep_vote_msk1_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTE_MSK1_sc_mcpusleep_vote_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_MSK_sc_mcpusleep_vote_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT0_MSK_sc_mcpusleep_vote_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCPU_VOTESTAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT1_MSK_sc_mcpusleep_vote_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_MCPU_VOTESTAT1_MSK_sc_mcpusleep_vote_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_en0_0coresight : 1;
        unsigned int sc_perisleep_vote_en0_1coresight : 1;
        unsigned int sc_perisleep_vote_en0_2ipf : 1;
        unsigned int sc_perisleep_vote_en0_3socp : 1;
        unsigned int sc_perisleep_vote_en0_acpu0 : 1;
        unsigned int sc_perisleep_vote_en0_mcpu : 1;
        unsigned int sc_perisleep_vote_en0_hifi : 1;
        unsigned int sc_perisleep_vote_en0_vdec : 1;
        unsigned int sc_perisleep_vote_en0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTEEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_3socp_START (3)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_3socp_END (3)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_acpu0_START (4)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_acpu0_END (4)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_mcpu_START (5)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_mcpu_END (5)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_hifi_START (6)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_hifi_END (6)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_vdec_START (7)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_vdec_END (7)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_START (8)
#define SOC_AO_SCTRL_SC_PERI_VOTEEN0_sc_perisleep_vote_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_dis0_0coresight : 1;
        unsigned int sc_perisleep_vote_dis0_1coresight : 1;
        unsigned int sc_perisleep_vote_dis0_2ipf : 1;
        unsigned int sc_perisleep_vote_dis0_3socp : 1;
        unsigned int sc_perisleep_vote_dis0_acpu0 : 1;
        unsigned int sc_perisleep_vote_dis0_mcpu : 1;
        unsigned int sc_perisleep_vote_dis0_hifi : 1;
        unsigned int sc_perisleep_vote_dis0_vdec : 1;
        unsigned int sc_perisleep_vote_dis0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTEDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_3socp_START (3)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_3socp_END (3)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_acpu0_START (4)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_acpu0_END (4)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_mcpu_START (5)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_mcpu_END (5)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_hifi_START (6)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_hifi_END (6)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_vdec_START (7)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_vdec_END (7)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_START (8)
#define SOC_AO_SCTRL_SC_PERI_VOTEDIS0_sc_perisleep_vote_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcpusleep_vote_stat0_0coresight : 1;
        unsigned int sc_mcpusleep_vote_stat0_1coresight : 1;
        unsigned int sc_perisleep_vote_stat0_2ipf : 1;
        unsigned int sc_perisleep_vote_stat0_3socp : 1;
        unsigned int sc_perisleep_vote_stat0_acpu0 : 1;
        unsigned int sc_perisleep_vote_stat0_mcpu : 1;
        unsigned int sc_perisleep_vote_stat0_hifi : 1;
        unsigned int sc_perisleep_vote_stat0_vdec : 1;
        unsigned int sc_perisleep_vote_stat0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTESTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_mcpusleep_vote_stat0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_mcpusleep_vote_stat0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_mcpusleep_vote_stat0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_mcpusleep_vote_stat0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_3socp_START (3)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_3socp_END (3)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_acpu0_START (4)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_acpu0_END (4)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_mcpu_START (5)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_mcpu_END (5)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_hifi_START (6)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_hifi_END (6)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_vdec_START (7)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_vdec_END (7)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_START (8)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_sc_perisleep_vote_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTE_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK0_sc_perisleep_vote_msk0_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK0_sc_perisleep_vote_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTE_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK1_sc_perisleep_vote_msk1_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTE_MSK1_sc_perisleep_vote_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTESTAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_MSK_sc_perisleep_vote_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT0_MSK_sc_perisleep_vote_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_perisleep_vote_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_PERI_VOTESTAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT1_MSK_sc_perisleep_vote_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_PERI_VOTESTAT1_MSK_sc_perisleep_vote_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_en0_0coresight : 1;
        unsigned int sc_acpusleep_vote_en0_1coresight : 1;
        unsigned int sc_acpusleep_vote_en0_2ipf : 1;
        unsigned int sc_acpusleep_vote_en0_3socp : 1;
        unsigned int sc_acpusleep_vote_en0_7reserved : 4;
        unsigned int sc_acpusleep_vote_en0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTEEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_3socp_START (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_3socp_END (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_START (8)
#define SOC_AO_SCTRL_SC_ACPU_VOTEEN0_sc_acpusleep_vote_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_dis0_0coresight : 1;
        unsigned int sc_acpusleep_vote_dis0_1coresight : 1;
        unsigned int sc_acpusleep_vote_dis0_2ipf : 1;
        unsigned int sc_acpusleep_vote_dis0_3socp : 1;
        unsigned int sc_acpusleep_vote_dis0_7reserved : 4;
        unsigned int sc_acpusleep_vote_dis0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_3socp_START (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_3socp_END (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_START (8)
#define SOC_AO_SCTRL_SC_ACPU_VOTEDIS0_sc_acpusleep_vote_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_stat0_0coresight : 1;
        unsigned int sc_acpusleep_vote_stat0_1coresight : 1;
        unsigned int sc_acpusleep_vote_stat0_2ipf : 1;
        unsigned int sc_acpusleep_vote_stat0_3socp : 1;
        unsigned int sc_acpusleep_vote_stat0_7reserved : 4;
        unsigned int sc_acpusleep_vote_stat0 : 24;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_0coresight_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_0coresight_END (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_1coresight_START (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_1coresight_END (1)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_2ipf_START (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_2ipf_END (2)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_3socp_START (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_3socp_END (3)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_7reserved_START (4)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_7reserved_END (7)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_START (8)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_sc_acpusleep_vote_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTE_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK0_sc_acpusleep_vote_msk0_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK0_sc_acpusleep_vote_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTE_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK1_sc_acpusleep_vote_msk1_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTE_MSK1_sc_acpusleep_vote_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_MSK_sc_acpusleep_vote_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT0_MSK_sc_acpusleep_vote_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_acpusleep_vote_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_ACPU_VOTESTAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT1_MSK_sc_acpusleep_vote_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_ACPU_VOTESTAT1_MSK_sc_acpusleep_vote_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_en0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTEEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTEEN0_sc_mcu_vote_en0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTEEN0_sc_mcu_vote_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_dis0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTEDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTEDIS0_sc_mcu_vote_dis0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTEDIS0_sc_mcu_vote_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_stat0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTESTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_sc_mcu_vote_stat0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_sc_mcu_vote_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK0_sc_mcu_vote_msk0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK0_sc_mcu_vote_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK1_sc_mcu_vote_msk1_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE_MSK1_sc_mcu_vote_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTESTAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_MSK_sc_mcu_vote_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT0_MSK_sc_mcu_vote_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTESTAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT1_MSK_sc_mcu_vote_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTESTAT1_MSK_sc_mcu_vote_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_en0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1EN0_sc_mcu_vote1_en0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1EN0_sc_mcu_vote1_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_dis0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_sc_mcu_vote1_dis0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1DIS0_sc_mcu_vote1_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_stat0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_sc_mcu_vote1_stat0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_sc_mcu_vote1_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK0_sc_mcu_vote1_msk0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK0_sc_mcu_vote1_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK1_sc_mcu_vote1_msk1_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1_MSK1_sc_mcu_vote1_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_MSK_sc_mcu_vote1_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT0_MSK_sc_mcu_vote1_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote1_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE1STAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT1_MSK_sc_mcu_vote1_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE1STAT1_MSK_sc_mcu_vote1_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_en0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2EN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2EN0_sc_mcu_vote2_en0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2EN0_sc_mcu_vote2_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_dis0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_sc_mcu_vote2_dis0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2DIS0_sc_mcu_vote2_dis0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_stat0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_sc_mcu_vote2_stat0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_sc_mcu_vote2_stat0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_msk0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2_MSK0_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK0_sc_mcu_vote2_msk0_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK0_sc_mcu_vote2_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_msk1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2_MSK1_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK1_sc_mcu_vote2_msk1_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2_MSK1_sc_mcu_vote2_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_stat0_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_MSK_sc_mcu_vote2_stat0_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT0_MSK_sc_mcu_vote2_stat0_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_mcu_vote2_stat1_msk : 32;
    } reg;
} SOC_AO_SCTRL_SC_MCU_VOTE2STAT1_MSK_UNION;
#endif
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT1_MSK_sc_mcu_vote2_stat1_msk_START (0)
#define SOC_AO_SCTRL_SC_MCU_VOTE2STAT1_MSK_sc_mcu_vote2_stat1_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int eco_num : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SC_ECONUM_UNION;
#endif
#define SOC_AO_SCTRL_SC_ECONUM_eco_num_START (0)
#define SOC_AO_SCTRL_SC_ECONUM_eco_num_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT0_sc_slicer_count_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT0_sc_slicer_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_gbbp1_int : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT1_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT1_sc_slicer_count_gbbp1_int_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_gbbp1_int_32k : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT2_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT2_sc_slicer_count_gbbp1_int_32k_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_gbbp2_int : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT3_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT3_sc_slicer_count_gbbp2_int_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_gbbp2_int_32k : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT4_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT4_sc_slicer_count_gbbp2_int_32k_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_wbbp2_int : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT5_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT5_sc_slicer_count_wbbp2_int_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT5_sc_slicer_count_wbbp2_int_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_slicer_count_wbbp1_int_32k : 32;
    } reg;
} SOC_AO_SCTRL_SC_SLICER_COUNT6_UNION;
#endif
#define SOC_AO_SCTRL_SC_SLICER_COUNT6_sc_slicer_count_wbbp1_int_32k_START (0)
#define SOC_AO_SCTRL_SC_SLICER_COUNT6_sc_slicer_count_wbbp1_int_32k_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int systemid0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCSYSID0_UNION;
#endif
#define SOC_AO_SCTRL_SCSYSID0_systemid0_START (0)
#define SOC_AO_SCTRL_SCSYSID0_systemid0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int systemid1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCSYSID1_UNION;
#endif
#define SOC_AO_SCTRL_SCSYSID1_systemid1_START (0)
#define SOC_AO_SCTRL_SCSYSID1_systemid1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int systemid2 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCSYSID2_UNION;
#endif
#define SOC_AO_SCTRL_SCSYSID2_systemid2_START (0)
#define SOC_AO_SCTRL_SCSYSID2_systemid2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int systemid3 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCSYSID3_UNION;
#endif
#define SOC_AO_SCTRL_SCSYSID3_systemid3_START (0)
#define SOC_AO_SCTRL_SCSYSID3_systemid3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int chip_id : 16;
        unsigned int chip_designer : 16;
    } reg;
} SOC_AO_SCTRL_SCCHIPID_UNION;
#endif
#define SOC_AO_SCTRL_SCCHIPID_chip_id_START (0)
#define SOC_AO_SCTRL_SCCHIPID_chip_id_END (15)
#define SOC_AO_SCTRL_SCCHIPID_chip_designer_START (16)
#define SOC_AO_SCTRL_SCCHIPID_chip_designer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wbbp_id : 16;
        unsigned int wbbp_designer : 16;
    } reg;
} SOC_AO_SCTRL_SCWBBPID_UNION;
#endif
#define SOC_AO_SCTRL_SCWBBPID_wbbp_id_START (0)
#define SOC_AO_SCTRL_SCWBBPID_wbbp_id_END (15)
#define SOC_AO_SCTRL_SCWBBPID_wbbp_designer_START (16)
#define SOC_AO_SCTRL_SCWBBPID_wbbp_designer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gbbp_id : 16;
        unsigned int gbbp_designer : 16;
    } reg;
} SOC_AO_SCTRL_SCGBBPID_UNION;
#endif
#define SOC_AO_SCTRL_SCGBBPID_gbbp_id_START (0)
#define SOC_AO_SCTRL_SCGBBPID_gbbp_id_END (15)
#define SOC_AO_SCTRL_SCGBBPID_gbbp_designer_START (16)
#define SOC_AO_SCTRL_SCGBBPID_gbbp_designer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_id : 16;
        unsigned int soc_designer : 16;
    } reg;
} SOC_AO_SCTRL_SCSOCID_UNION;
#endif
#define SOC_AO_SCTRL_SCSOCID_soc_id_START (0)
#define SOC_AO_SCTRL_SCSOCID_soc_id_END (15)
#define SOC_AO_SCTRL_SCSOCID_soc_designer_START (16)
#define SOC_AO_SCTRL_SCSOCID_soc_designer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_fpga_rtl_def : 32;
    } reg;
} SOC_AO_SCTRL_SC_SOC_FPGA_RTL_DEF_UNION;
#endif
#define SOC_AO_SCTRL_SC_SOC_FPGA_RTL_DEF_soc_fpga_rtl_def_START (0)
#define SOC_AO_SCTRL_SC_SOC_FPGA_RTL_DEF_soc_fpga_rtl_def_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_fpga_pr_def : 32;
    } reg;
} SOC_AO_SCTRL_SC_SOC_FPGA_PR_DEF_UNION;
#endif
#define SOC_AO_SCTRL_SC_SOC_FPGA_PR_DEF_soc_fpga_pr_def_START (0)
#define SOC_AO_SCTRL_SC_SOC_FPGA_PR_DEF_soc_fpga_pr_def_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_fpga_res_def0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF0_soc_fpga_res_def0_START (0)
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF0_soc_fpga_res_def0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int soc_fpga_res_def1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF1_UNION;
#endif
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF1_soc_fpga_res_def1_START (0)
#define SOC_AO_SCTRL_SC_SOC_FPGA_RES_DEF1_soc_fpga_res_def1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcell_id0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCPCELLID0_UNION;
#endif
#define SOC_AO_SCTRL_SCPCELLID0_pcell_id0_START (0)
#define SOC_AO_SCTRL_SCPCELLID0_pcell_id0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcell_id1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCPCELLID1_UNION;
#endif
#define SOC_AO_SCTRL_SCPCELLID1_pcell_id1_START (0)
#define SOC_AO_SCTRL_SCPCELLID1_pcell_id1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcell_id2 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCPCELLID2_UNION;
#endif
#define SOC_AO_SCTRL_SCPCELLID2_pcell_id2_START (0)
#define SOC_AO_SCTRL_SCPCELLID2_pcell_id2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcell_id3 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SCPCELLID3_UNION;
#endif
#define SOC_AO_SCTRL_SCPCELLID3_pcell_id3_START (0)
#define SOC_AO_SCTRL_SCPCELLID3_pcell_id3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xtalover0 : 1;
        unsigned int xtalen0 : 1;
        unsigned int tcxo0_abb_timeout : 1;
        unsigned int tcxo0_abb_reserved2 : 1;
        unsigned int xtal_time0 : 25;
        unsigned int reserved : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL0_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtalover0_START (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtalover0_END (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtalen0_START (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtalen0_END (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_tcxo0_abb_timeout_START (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_tcxo0_abb_timeout_END (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_tcxo0_abb_reserved2_START (3)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_tcxo0_abb_reserved2_END (3)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtal_time0_START (4)
#define SOC_AO_SCTRL_SC_XTAL_CTRL0_xtal_time0_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xtalover1 : 1;
        unsigned int xtalen1 : 1;
        unsigned int tcxo1_abb_timeout : 1;
        unsigned int tcxo1_abb_reserved2 : 1;
        unsigned int xtal_time1 : 25;
        unsigned int reserved : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtalover1_START (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtalover1_END (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtalen1_START (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtalen1_END (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_tcxo1_abb_timeout_START (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_tcxo1_abb_timeout_END (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_tcxo1_abb_reserved2_START (3)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_tcxo1_abb_reserved2_END (3)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtal_time1_START (4)
#define SOC_AO_SCTRL_SC_XTAL_CTRL1_xtal_time1_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 9;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int tcxo1_en_sftcfg_pmu : 1;
        unsigned int reserved_4 : 1;
        unsigned int tcxo0_en_sftcfg_pmu : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 14;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL2_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL2_tcxo1_en_sftcfg_pmu_START (12)
#define SOC_AO_SCTRL_SC_XTAL_CTRL2_tcxo1_en_sftcfg_pmu_END (12)
#define SOC_AO_SCTRL_SC_XTAL_CTRL2_tcxo0_en_sftcfg_pmu_START (14)
#define SOC_AO_SCTRL_SC_XTAL_CTRL2_tcxo0_en_sftcfg_pmu_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xtalover0_pmu_up : 1;
        unsigned int xtalen0_pmu_up : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 25;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL3_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL3_xtalover0_pmu_up_START (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL3_xtalover0_pmu_up_END (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL3_xtalen0_pmu_up_START (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL3_xtalen0_pmu_up_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int xtalover1_pmu_up : 1;
        unsigned int xtalen1_pmu_up : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 25;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL4_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL4_xtalover1_pmu_up_START (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL4_xtalover1_pmu_up_END (0)
#define SOC_AO_SCTRL_SC_XTAL_CTRL4_xtalen1_pmu_up_START (1)
#define SOC_AO_SCTRL_SC_XTAL_CTRL4_xtalen1_pmu_up_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int tcxo0_pwdn_timeout : 1;
        unsigned int reserved_2 : 1;
        unsigned int xtal0_time_pmu_dn : 25;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL5_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL5_tcxo0_pwdn_timeout_START (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL5_tcxo0_pwdn_timeout_END (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL5_xtal0_time_pmu_dn_START (4)
#define SOC_AO_SCTRL_SC_XTAL_CTRL5_xtal0_time_pmu_dn_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int tcxo1_pwdn_timeout : 1;
        unsigned int reserved_2 : 1;
        unsigned int xtal1_time_pmu_dn : 25;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_CTRL6_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_CTRL6_tcxo1_pwdn_timeout_START (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL6_tcxo1_pwdn_timeout_END (2)
#define SOC_AO_SCTRL_SC_XTAL_CTRL6_xtal1_time_pmu_dn_START (4)
#define SOC_AO_SCTRL_SC_XTAL_CTRL6_xtal1_time_pmu_dn_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int xtal_en1_pmu_up : 1;
        unsigned int xtal_en1_abb : 1;
        unsigned int reserved_1 : 5;
        unsigned int tcxo1_curr_st : 4;
        unsigned int reserved_2 : 8;
        unsigned int soc_tcxo_sel : 1;
        unsigned int tcxo_en_hard : 1;
        unsigned int buck3_en_out : 1;
        unsigned int reserved_3 : 1;
        unsigned int tcxo0_curr_st : 4;
        unsigned int xtal_en0_pmu_dn : 1;
        unsigned int xtal_en0_pmu_up : 1;
        unsigned int xtal_en0_abb : 1;
        unsigned int reserved_4 : 1;
    } reg;
} SOC_AO_SCTRL_SC_XTAL_STAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en1_pmu_up_START (1)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en1_pmu_up_END (1)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en1_abb_START (2)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en1_abb_END (2)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo1_curr_st_START (8)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo1_curr_st_END (11)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_soc_tcxo_sel_START (20)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_soc_tcxo_sel_END (20)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo_en_hard_START (21)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo_en_hard_END (21)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_buck3_en_out_START (22)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_buck3_en_out_END (22)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo0_curr_st_START (24)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_tcxo0_curr_st_END (27)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_pmu_dn_START (28)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_pmu_dn_END (28)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_pmu_up_START (29)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_pmu_up_END (29)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_abb_START (30)
#define SOC_AO_SCTRL_SC_XTAL_STAT0_xtal_en0_abb_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int efuse_chipio0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_EFUSE_CHIPID0_UNION;
#endif
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID0_efuse_chipio0_START (0)
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID0_efuse_chipio0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int efuse_chipio1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_EFUSE_CHIPID1_UNION;
#endif
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID1_efuse_chipio1_START (0)
#define SOC_AO_SCTRL_SC_EFUSE_CHIPID1_efuse_chipio1_END (31)
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
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int aarm_spniden : 1;
        unsigned int aarm_spiden : 1;
        unsigned int aarm_niden : 1;
        unsigned int aarm_dbgen : 1;
        unsigned int carm_spniden : 1;
        unsigned int carm_spiden : 1;
        unsigned int carm_niden : 1;
        unsigned int carm_dbgen : 1;
        unsigned int cssys_spniden : 1;
        unsigned int cssys_spiden : 1;
        unsigned int cssys_niden : 1;
        unsigned int cssys_dbgen : 1;
        unsigned int cssys_device_enable : 1;
        unsigned int m3debugenable : 1;
        unsigned int hifi_jtag_en : 1;
        unsigned int bbe_jtag_en : 1;
        unsigned int g3d_ddr_isp_dbgen : 1;
        unsigned int djtag_den : 1;
        unsigned int cssys_jtag_en : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
    } reg;
} SOC_AO_SCTRL_SC_DEBUG_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_spniden_START (8)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_spniden_END (8)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_spiden_START (9)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_spiden_END (9)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_niden_START (10)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_niden_END (10)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_dbgen_START (11)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_aarm_dbgen_END (11)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_spniden_START (12)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_spniden_END (12)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_spiden_START (13)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_spiden_END (13)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_niden_START (14)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_niden_END (14)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_dbgen_START (15)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_carm_dbgen_END (15)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_spniden_START (16)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_spniden_END (16)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_spiden_START (17)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_spiden_END (17)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_niden_START (18)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_niden_END (18)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_dbgen_START (19)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_dbgen_END (19)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_device_enable_START (20)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_device_enable_END (20)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_m3debugenable_START (21)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_m3debugenable_END (21)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_hifi_jtag_en_START (22)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_hifi_jtag_en_END (22)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_bbe_jtag_en_START (23)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_bbe_jtag_en_END (23)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_g3d_ddr_isp_dbgen_START (24)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_g3d_ddr_isp_dbgen_END (24)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_djtag_den_START (25)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_djtag_den_END (25)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_jtag_en_START (26)
#define SOC_AO_SCTRL_SC_DEBUG_CTRL1_cssys_jtag_en_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sec_dbg_key_pass : 1;
        unsigned int sc_cfg_arm_dbg_wr_cnt : 1;
        unsigned int sc_arm_dbg_key_wr_en1 : 1;
        unsigned int sc_arm_dbg_key_wr_en0 : 1;
        unsigned int arm_dbg_key_cnt1 : 2;
        unsigned int arm_dbg_key_cnt0 : 2;
        unsigned int reserved : 24;
    } reg;
} SOC_AO_SCTRL_SC_DBG_STAT_UNION;
#endif
#define SOC_AO_SCTRL_SC_DBG_STAT_sec_dbg_key_pass_START (0)
#define SOC_AO_SCTRL_SC_DBG_STAT_sec_dbg_key_pass_END (0)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_cfg_arm_dbg_wr_cnt_START (1)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_cfg_arm_dbg_wr_cnt_END (1)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_arm_dbg_key_wr_en1_START (2)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_arm_dbg_key_wr_en1_END (2)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_arm_dbg_key_wr_en0_START (3)
#define SOC_AO_SCTRL_SC_DBG_STAT_sc_arm_dbg_key_wr_en0_END (3)
#define SOC_AO_SCTRL_SC_DBG_STAT_arm_dbg_key_cnt1_START (4)
#define SOC_AO_SCTRL_SC_DBG_STAT_arm_dbg_key_cnt1_END (5)
#define SOC_AO_SCTRL_SC_DBG_STAT_arm_dbg_key_cnt0_START (6)
#define SOC_AO_SCTRL_SC_DBG_STAT_arm_dbg_key_cnt0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_arm_dbg_key0 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ARM_DBG_KEY0_UNION;
#endif
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY0_sc_arm_dbg_key0_START (0)
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY0_sc_arm_dbg_key0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_arm_dbg_key1 : 32;
    } reg;
} SOC_AO_SCTRL_SC_ARM_DBG_KEY1_UNION;
#endif
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY1_sc_arm_dbg_key1_START (0)
#define SOC_AO_SCTRL_SC_ARM_DBG_KEY1_sc_arm_dbg_key1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int secure_ctrlen0_sec_1_0 : 2;
        unsigned int secure_ctrlen0_sec_2 : 1;
        unsigned int secure_ctrlen0_sec_4_3 : 2;
        unsigned int reserved_0 : 10;
        unsigned int secure_ctrlen0_sec_15 : 1;
        unsigned int secure_ctrlen0_sec_16 : 1;
        unsigned int reserved_1 : 1;
        unsigned int secure_ctrlen0_sec_18 : 1;
        unsigned int secure_ctrlen0_sec_19 : 1;
        unsigned int secure_ctrlen0_sec_20 : 1;
        unsigned int reserved_2 : 2;
        unsigned int secure_ctrlen0_sec_23 : 1;
        unsigned int reserved_3 : 8;
    } reg;
} SOC_AO_SCTRL_SC_SECURE_CTRLEN0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_1_0_START (0)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_1_0_END (1)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_2_START (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_2_END (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_4_3_START (3)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_4_3_END (4)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_15_START (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_15_END (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_16_START (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_16_END (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_18_START (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_18_END (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_19_START (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_19_END (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_20_START (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_20_END (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_23_START (23)
#define SOC_AO_SCTRL_SC_SECURE_CTRLEN0_secure_ctrlen0_sec_23_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int secure_ctrldis0_sec_1_0 : 2;
        unsigned int secure_ctrldis0_sec_2 : 1;
        unsigned int secure_ctrldis0_sec_4_3 : 2;
        unsigned int reserved_0 : 10;
        unsigned int secure_ctrldis0_sec_15 : 1;
        unsigned int secure_ctrldis0_sec_16 : 1;
        unsigned int reserved_1 : 1;
        unsigned int secure_ctrldis0_sec_18 : 1;
        unsigned int secure_ctrldis0_sec_19 : 1;
        unsigned int secure_ctrldis0_sec_20 : 1;
        unsigned int reserved_2 : 2;
        unsigned int secure_ctrldis0_sec_23 : 1;
        unsigned int reserved_3 : 8;
    } reg;
} SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_1_0_START (0)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_1_0_END (1)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_2_START (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_2_END (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_4_3_START (3)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_4_3_END (4)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_15_START (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_15_END (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_16_START (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_16_END (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_18_START (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_18_END (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_19_START (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_19_END (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_20_START (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_20_END (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_23_START (23)
#define SOC_AO_SCTRL_SC_SECURE_CTRLDIS0_secure_ctrldis0_sec_23_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int modem_sec_ind : 2;
        unsigned int secure_cssys_sec_ind : 1;
        unsigned int secure_ctrlstat0_sec_4_3 : 2;
        unsigned int reserved_0 : 10;
        unsigned int secure_ctrlstat0_sec_15 : 1;
        unsigned int secure_ctrlstat0_sec_16 : 1;
        unsigned int reserved_1 : 1;
        unsigned int secure_ctrlstat0_sec_18 : 1;
        unsigned int secure_ctrlstat0_sec_19 : 1;
        unsigned int secure_ctrlstat0_sec_20 : 1;
        unsigned int reserved_2 : 2;
        unsigned int dap_sec_ind : 1;
        unsigned int reserved_3 : 8;
    } reg;
} SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_modem_sec_ind_START (0)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_modem_sec_ind_END (1)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_cssys_sec_ind_START (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_cssys_sec_ind_END (2)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_4_3_START (3)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_4_3_END (4)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_15_START (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_15_END (15)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_16_START (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_16_END (16)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_18_START (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_18_END (18)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_19_START (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_19_END (19)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_20_START (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_secure_ctrlstat0_sec_20_END (20)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_dap_sec_ind_START (23)
#define SOC_AO_SCTRL_SC_SECURE_CTRLSTAT0_dap_sec_ind_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secure_ctrl_group0 : 1;
        unsigned int sc_secure_ctrl_group1 : 1;
        unsigned int sc_secure_ctrl_group2 : 1;
        unsigned int sc_secure_ctrl_group3 : 1;
        unsigned int sc_secure_ctrl_group4 : 1;
        unsigned int sc_secure_ctrl_group5 : 1;
        unsigned int sc_secure_ctrl_group6 : 1;
        unsigned int sc_secure_ctrl_group7 : 1;
        unsigned int sc_secure_ctrl_group8 : 1;
        unsigned int sc_secure_ctrl_group9 : 1;
        unsigned int sc_secure_ctrl_group10 : 1;
        unsigned int sc_secure_ctrl_group11 : 1;
        unsigned int sc_secure_ctrl_group12 : 1;
        unsigned int sc_secure_ctrl_group13 : 1;
        unsigned int sc_secure_ctrl_group14 : 1;
        unsigned int sc_secure_ctrl_group15 : 1;
        unsigned int sc_secure_ctrl_group16 : 1;
        unsigned int sc_secure_ctrl_group17 : 1;
        unsigned int sc_secure_ctrl_group18 : 1;
        unsigned int sc_secure_ctrl_group19 : 1;
        unsigned int sc_secure_ctrl_group20 : 1;
        unsigned int sc_secure_ctrl_group21 : 1;
        unsigned int sc_secure_ctrl_group22 : 1;
        unsigned int sc_secure_ctrl_group23 : 1;
        unsigned int sc_secure_ctrl_group24 : 1;
        unsigned int sc_secure_ctrl_group25 : 1;
        unsigned int sc_secure_ctrl_group26 : 1;
        unsigned int sc_secure_ctrl_group27 : 1;
        unsigned int sc_secure_ctrl_group28 : 1;
        unsigned int sc_secure_ctrl_group29 : 1;
        unsigned int sc_secure_ctrl_group30 : 1;
        unsigned int sc_secure_ctrl_group31 : 1;
    } reg;
} SOC_AO_SCTRL_SC_SECURITY_CTRL0_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group0_START (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group0_END (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group1_START (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group1_END (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group2_START (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group2_END (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group3_START (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group3_END (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group4_START (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group4_END (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group5_START (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group5_END (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group6_START (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group6_END (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group7_START (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group7_END (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group8_START (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group8_END (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group9_START (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group9_END (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group10_START (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group10_END (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group11_START (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group11_END (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group12_START (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group12_END (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group13_START (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group13_END (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group14_START (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group14_END (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group15_START (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group15_END (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group16_START (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group16_END (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group17_START (17)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group17_END (17)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group18_START (18)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group18_END (18)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group19_START (19)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group19_END (19)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group20_START (20)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group20_END (20)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group21_START (21)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group21_END (21)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group22_START (22)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group22_END (22)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group23_START (23)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group23_END (23)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group24_START (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group24_END (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group25_START (25)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group25_END (25)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group26_START (26)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group26_END (26)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group27_START (27)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group27_END (27)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group28_START (28)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group28_END (28)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group29_START (29)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group29_END (29)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group30_START (30)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group30_END (30)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group31_START (31)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL0_sc_secure_ctrl_group31_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secure_ctrl_bit_0rtc : 1;
        unsigned int sc_secure_ctrl_bit_1timer0 : 1;
        unsigned int sc_secure_ctrl_bit_2timer1 : 1;
        unsigned int sc_secure_ctrl_bit_3timer2 : 1;
        unsigned int sc_secure_ctrl_bit_4timer3 : 1;
        unsigned int sc_secure_ctrl_bit_5timer4 : 1;
        unsigned int sc_secure_ctrl_bit_6timer5 : 1;
        unsigned int sc_secure_ctrl_bit_7timer6 : 1;
        unsigned int sc_secure_ctrl_bit_8timer7 : 1;
        unsigned int sc_secure_ctrl_bit_9timer8 : 1;
        unsigned int sc_secure_ctrl_bit_10watchdog0 : 1;
        unsigned int sc_secure_ctrl_bit_11watchdog1 : 1;
        unsigned int sc_secure_ctrl_bit_12watchdog2 : 1;
        unsigned int sc_secure_ctrl_bit_13aarm : 1;
        unsigned int sc_secure_ctrl_bit_14carm : 1;
        unsigned int sc_secure_ctrl_bit_15hifi : 1;
        unsigned int sc_secure_ctrl_bit_16bbedsp : 1;
        unsigned int sc_secure_ctrl_bit : 15;
    } reg;
} SOC_AO_SCTRL_SC_SECURITY_CTRL1_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_0rtc_START (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_0rtc_END (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_1timer0_START (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_1timer0_END (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_2timer1_START (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_2timer1_END (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_3timer2_START (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_3timer2_END (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_4timer3_START (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_4timer3_END (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_5timer4_START (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_5timer4_END (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_6timer5_START (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_6timer5_END (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_7timer6_START (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_7timer6_END (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_8timer7_START (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_8timer7_END (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_9timer8_START (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_9timer8_END (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_10watchdog0_START (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_10watchdog0_END (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_11watchdog1_START (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_11watchdog1_END (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_12watchdog2_START (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_12watchdog2_END (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_13aarm_START (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_13aarm_END (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_14carm_START (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_14carm_END (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_15hifi_START (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_15hifi_END (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_16bbedsp_START (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_16bbedsp_END (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_START (17)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL1_sc_secure_ctrl_bit_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hifi_boot_addr : 16;
        unsigned int remap_sram_aarm : 1;
        unsigned int reserved : 7;
        unsigned int efusec_remap : 1;
        unsigned int sc_secure_ctrl_reserved : 7;
    } reg;
} SOC_AO_SCTRL_SC_SECURITY_CTRL2_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_hifi_boot_addr_START (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_hifi_boot_addr_END (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_remap_sram_aarm_START (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_remap_sram_aarm_END (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_efusec_remap_START (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_efusec_remap_END (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_sc_secure_ctrl_reserved_START (25)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL2_sc_secure_ctrl_reserved_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sc_secure_ctrl3_group0 : 1;
        unsigned int sc_secure_ctrl3_group1 : 1;
        unsigned int sc_secure_ctrl3_group2 : 1;
        unsigned int sc_secure_ctrl3_group3 : 1;
        unsigned int sc_secure_ctrl3_group4 : 1;
        unsigned int sc_secure_ctrl3_group5 : 1;
        unsigned int sc_secure_ctrl3_group6 : 1;
        unsigned int sc_secure_ctrl3_group7 : 1;
        unsigned int sc_secure_ctrl3_group8 : 1;
        unsigned int sc_secure_ctrl3_group9 : 1;
        unsigned int sc_secure_ctrl3_group10 : 1;
        unsigned int sc_secure_ctrl3_group11 : 1;
        unsigned int sc_secure_ctrl3_group12 : 1;
        unsigned int sc_secure_ctrl3_group13 : 1;
        unsigned int sc_secure_ctrl3_group14 : 1;
        unsigned int sc_secure_ctrl3_group15 : 1;
        unsigned int sc_secure_ctrl3_group16 : 1;
        unsigned int sc_secure_ctrl3_group17 : 1;
        unsigned int sc_secure_ctrl3_group18 : 1;
        unsigned int sc_secure_ctrl3_group19 : 1;
        unsigned int sc_secure_ctrl3_group20 : 1;
        unsigned int sc_secure_ctrl3_group21 : 1;
        unsigned int sc_secure_ctrl3_group22 : 1;
        unsigned int sc_secure_ctrl3_group23 : 1;
        unsigned int sc_secure_ctrl3_group24 : 1;
        unsigned int sc_secure_ctrl3_group25 : 1;
        unsigned int sc_secure_ctrl3_group26 : 1;
        unsigned int sc_secure_ctrl3_group27 : 1;
        unsigned int sc_secure_ctrl3_group28 : 1;
        unsigned int sc_secure_ctrl3_group29 : 1;
        unsigned int sc_secure_ctrl3_group30 : 1;
        unsigned int sc_secure_ctrl3_group31 : 1;
    } reg;
} SOC_AO_SCTRL_SC_SECURITY_CTRL3_UNION;
#endif
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group0_START (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group0_END (0)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group1_START (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group1_END (1)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group2_START (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group2_END (2)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group3_START (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group3_END (3)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group4_START (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group4_END (4)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group5_START (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group5_END (5)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group6_START (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group6_END (6)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group7_START (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group7_END (7)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group8_START (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group8_END (8)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group9_START (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group9_END (9)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group10_START (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group10_END (10)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group11_START (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group11_END (11)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group12_START (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group12_END (12)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group13_START (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group13_END (13)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group14_START (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group14_END (14)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group15_START (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group15_END (15)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group16_START (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group16_END (16)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group17_START (17)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group17_END (17)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group18_START (18)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group18_END (18)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group19_START (19)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group19_END (19)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group20_START (20)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group20_END (20)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group21_START (21)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group21_END (21)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group22_START (22)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group22_END (22)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group23_START (23)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group23_END (23)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group24_START (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group24_END (24)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group25_START (25)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group25_END (25)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group26_START (26)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group26_END (26)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group27_START (27)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group27_END (27)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group28_START (28)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group28_END (28)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group29_START (29)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group29_END (29)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group30_START (30)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group30_END (30)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group31_START (31)
#define SOC_AO_SCTRL_SC_SECURITY_CTRL3_sc_secure_ctrl3_group31_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

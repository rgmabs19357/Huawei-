#ifndef __SOC_PMCTRL_INTERFACE_H__
#define __SOC_PMCTRL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_PMCTRL_DSPPLLCTRL_ADDR(base) ((base) + (0x000))
#define SOC_PMCTRL_DSPPLLFREQ_ADDR(base) ((base) + (0x004))
#define SOC_PMCTRL_DDRPLLCTRL_ADDR(base) ((base) + (0x008))
#define SOC_PMCTRL_DDRPLLFREQ_ADDR(base) ((base) + (0x00C))
#define SOC_PMCTRL_PERIPLLCTRL_ADDR(base) ((base) + (0x010))
#define SOC_PMCTRL_PERIPLLFREQ_ADDR(base) ((base) + (0x014))
#define SOC_PMCTRL_HDMIPLLCTRL_ADDR(base) ((base) + (0x018))
#define SOC_PMCTRL_HDMIPLLFREQ_ADDR(base) ((base) + (0x01C))
#define SOC_PMCTRL_ACPUPLL0CTRL_ADDR(base) ((base) + (0x020))
#define SOC_PMCTRL_ACPUPLL0FREQ_ADDR(base) ((base) + (0x024))
#define SOC_PMCTRL_ACPUPLL1CTRL_ADDR(base) ((base) + (0x028))
#define SOC_PMCTRL_ACPUPLL1FREQ_ADDR(base) ((base) + (0x02C))
#define SOC_PMCTRL_G3DPLL0CTRL_ADDR(base) ((base) + (0x030))
#define SOC_PMCTRL_G3DPLL0FREQ_ADDR(base) ((base) + (0x034))
#define SOC_PMCTRL_G3DPLL1CTRL_ADDR(base) ((base) + (0x038))
#define SOC_PMCTRL_G3DPLL1FREQ_ADDR(base) ((base) + (0x03C))
#define SOC_PMCTRL_MCPUPLLCTRL_ADDR(base) ((base) + (0x040))
#define SOC_PMCTRL_MCPUPLLFREQ_ADDR(base) ((base) + (0x044))
#define SOC_PMCTRL_BBPPLLCTRL_ADDR(base) ((base) + (0x048))
#define SOC_PMCTRL_BBPPLLFREQ_ADDR(base) ((base) + (0x04C))
#define SOC_PMCTRL_BBPPLLALIAS_ADDR(base) ((base) + (0x050))
#define SOC_PMCTRL_G3DPLL1ALIAS_ADDR(base) ((base) + (0x054))
#define SOC_PMCTRL_CLKCFG4BIT0_ADDR(base) ((base) + (0x080))
#define SOC_PMCTRL_CLKCFG4BIT1_ADDR(base) ((base) + (0x084))
#define SOC_PMCTRL_CLKCFG4BIT2_ADDR(base) ((base) + (0x088))
#define SOC_PMCTRL_TIMER0CTRL_ADDR(base) ((base) + (0x0C0))
#define SOC_PMCTRL_TIMER1CTRL_ADDR(base) ((base) + (0x0C4))
#define SOC_PMCTRL_TIMER2CTRL_ADDR(base) ((base) + (0x0C8))
#define SOC_PMCTRL_TIMER3CTRL_ADDR(base) ((base) + (0x0CC))
#define SOC_PMCTRL_PMUSSICHNEN_ADDR(base) ((base) + (0x0FC))
#define SOC_PMCTRL_ACPUPLLSEL_ADDR(base) ((base) + (0x100))
#define SOC_PMCTRL_ACPUCLKDIV_ADDR(base) ((base) + (0x104))
#define SOC_PMCTRL_ACPUMEMRM_ADDR(base) ((base) + (0x108))
#define SOC_PMCTRL_ACPUCLKOFFCFG_ADDR(base) ((base) + (0x10C))
#define SOC_PMCTRL_ACPUDVFSEN_ADDR(base) ((base) + (0x110))
#define SOC_PMCTRL_ACPUCLKPROFILE0_ADDR(base) ((base) + (0x114))
#define SOC_PMCTRL_ACPUCLKPROFILE1_ADDR(base) ((base) + (0x118))
#define SOC_PMCTRL_ACPUVOLPROFILE_ADDR(base) ((base) + (0x11C))
#define SOC_PMCTRL_ACPUPLL0STAT_ADDR(base) ((base) + (0x120))
#define SOC_PMCTRL_ACPUPLL1STAT_ADDR(base) ((base) + (0x124))
#define SOC_PMCTRL_ACPUDIVTIMEOUT_ADDR(base) ((base) + (0x128))
#define SOC_PMCTRL_ACPUAVSPARAUPD_ADDR(base) ((base) + (0x180))
#define SOC_PMCTRL_ACPUAVSPARA0_ADDR(base) ((base) + (0x184))
#define SOC_PMCTRL_ACPUAVSPARA1_ADDR(base) ((base) + (0x188))
#define SOC_PMCTRL_ACPUAVSPARA2_ADDR(base) ((base) + (0x18C))
#define SOC_PMCTRL_ACPUAVSPARA3_ADDR(base) ((base) + (0x190))
#define SOC_PMCTRL_ACPUAVSPARA4_ADDR(base) ((base) + (0x194))
#define SOC_PMCTRL_ACPUAVSPARA5_ADDR(base) ((base) + (0x198))
#define SOC_PMCTRL_ACPUAVSPARA6_ADDR(base) ((base) + (0x19C))
#define SOC_PMCTRL_ACPUAVSPARA7_ADDR(base) ((base) + (0x1A0))
#define SOC_PMCTRL_L2CCAVSPARAUPD_ADDR(base) ((base) + (0x1B0))
#define SOC_PMCTRL_L2CCAVSPARA0_ADDR(base) ((base) + (0x1B4))
#define SOC_PMCTRL_L2CCAVSPARA1_ADDR(base) ((base) + (0x1B8))
#define SOC_PMCTRL_L2CCAVSPARA2_ADDR(base) ((base) + (0x1BC))
#define SOC_PMCTRL_L2CCAVSPARA3_ADDR(base) ((base) + (0x1C0))
#define SOC_PMCTRL_L2CCAVSPARA4_ADDR(base) ((base) + (0x1C4))
#define SOC_PMCTRL_L2CCAVSPARA5_ADDR(base) ((base) + (0x1C8))
#define SOC_PMCTRL_L2CCAVSPARA6_ADDR(base) ((base) + (0x1CC))
#define SOC_PMCTRL_L2CCAVSPARA7_ADDR(base) ((base) + (0x1D0))
#define SOC_PMCTRL_ACPUAVSEN_ADDR(base) ((base) + (0x1E4))
#define SOC_PMCTRL_ACPUAVSPERIOD_ADDR(base) ((base) + (0x1E8))
#define SOC_PMCTRL_AACPUAVSRUNROUND_ADDR(base) ((base) + (0x1EC))
#define SOC_PMCTRL_G3DCLKSEL_ADDR(base) ((base) + (0x200))
#define SOC_PMCTRL_G3DCLKDIV_ADDR(base) ((base) + (0x204))
#define SOC_PMCTRL_G3DMEMRM_ADDR(base) ((base) + (0x208))
#define SOC_PMCTRL_G3DCLKOFFCFG_ADDR(base) ((base) + (0x20C))
#define SOC_PMCTRL_G3DDVFSEN_ADDR(base) ((base) + (0x210))
#define SOC_PMCTRL_G3DCLKPROFILE0_ADDR(base) ((base) + (0x214))
#define SOC_PMCTRL_G3DVOLPROFILE_ADDR(base) ((base) + (0x218))
#define SOC_PMCTRL_G3DDIVTIMEOUT_ADDR(base) ((base) + (0x21C))
#define SOC_PMCTRL_G3DAVSPARAUDP_ADDR(base) ((base) + (0x280))
#define SOC_PMCTRL_G3DAVSPARA0_ADDR(base) ((base) + (0x284))
#define SOC_PMCTRL_G3DAVSPARA1_ADDR(base) ((base) + (0x288))
#define SOC_PMCTRL_G3DAVSPARA2_ADDR(base) ((base) + (0x28C))
#define SOC_PMCTRL_G3DAVSPARA3_ADDR(base) ((base) + (0x290))
#define SOC_PMCTRL_G3DAVSPARA4_ADDR(base) ((base) + (0x294))
#define SOC_PMCTRL_G3DAVSPARA5_ADDR(base) ((base) + (0x298))
#define SOC_PMCTRL_G3DAVSPARA6_ADDR(base) ((base) + (0x29C))
#define SOC_PMCTRL_G3DAVSPARA7_ADDR(base) ((base) + (0x2A0))
#define SOC_PMCTRL_G3DAVSEN_ADDR(base) ((base) + (0x2E0))
#define SOC_PMCTRL_G3DAVSPERIOD_ADDR(base) ((base) + (0x2E4))
#define SOC_PMCTRL_G3DAVSRUNROUND_ADDR(base) ((base) + (0x2E8))
#define SOC_PMCTRL_ACPUHPMCTRL_ADDR(base) ((base) + (0x300))
#define SOC_PMCTRL_ACPUHPMOPCVALID_ADDR(base) ((base) + (0x314))
#define SOC_PMCTRL_ACPU01HPMOPC_ADDR(base) ((base) + (0x318))
#define SOC_PMCTRL_ACPU23HPMOPC_ADDR(base) ((base) + (0x31C))
#define SOC_PMCTRL_L2CCHPMOPC_ADDR(base) ((base) + (0x320))
#define SOC_PMCTRL_ACPU01HPMXOPC_ADDR(base) ((base) + (0x324))
#define SOC_PMCTRL_ACPU23HPMXOPC_ADDR(base) ((base) + (0x328))
#define SOC_PMCTRL_L2CCHPMXOPC_ADDR(base) ((base) + (0x32C))
#define SOC_PMCTRL_ACPU01HPMPC_ADDR(base) ((base) + (0x330))
#define SOC_PMCTRL_ACPU23HPMPC_ADDR(base) ((base) + (0x334))
#define SOC_PMCTRL_L2CCHPMPC_ADDR(base) ((base) + (0x338))
#define SOC_PMCTRL_ACPUHPMBYPASS_ADDR(base) ((base) + (0x33C))
#define SOC_PMCTRL_ACPUPMUVOLUPTIME_ADDR(base) ((base) + (0x360))
#define SOC_PMCTRL_ACPUPMUVOLDNTIME_ADDR(base) ((base) + (0x364))
#define SOC_PMCTRL_ACPUVOLPMUADDR_ADDR(base) ((base) + (0x368))
#define SOC_PMCTRL_ACPUVOLUPSTEP_ADDR(base) ((base) + (0x36C))
#define SOC_PMCTRL_ACPUVOLDNSTEP_ADDR(base) ((base) + (0x370))
#define SOC_PMCTRL_ACPUDFTVOL_ADDR(base) ((base) + (0x374))
#define SOC_PMCTRL_ACPUDESTVOL_ADDR(base) ((base) + (0x378))
#define SOC_PMCTRL_G3DHPMCTRL_ADDR(base) ((base) + (0x380))
#define SOC_PMCTRL_G3DHPMOPCVALID_ADDR(base) ((base) + (0x394))
#define SOC_PMCTRL_G3DHPM01OPC_ADDR(base) ((base) + (0x398))
#define SOC_PMCTRL_G3DHPM23OPC_ADDR(base) ((base) + (0x39C))
#define SOC_PMCTRL_G3DHPMX01OPC_ADDR(base) ((base) + (0x3A0))
#define SOC_PMCTRL_G3DHPMX23OPC_ADDR(base) ((base) + (0x3A4))
#define SOC_PMCTRL_G3DHPM01PC_ADDR(base) ((base) + (0x3A8))
#define SOC_PMCTRL_G3DHPM23PC_ADDR(base) ((base) + (0x3AC))
#define SOC_PMCTRL_G3DHPMBYPASS_ADDR(base) ((base) + (0x3B0))
#define SOC_PMCTRL_G3DPMUVOLUPTIME_ADDR(base) ((base) + (0x3E0))
#define SOC_PMCTRL_G3DPMUVOLDNTIME_ADDR(base) ((base) + (0x3E4))
#define SOC_PMCTRL_G3DVOLPMUADDR_ADDR(base) ((base) + (0x3E8))
#define SOC_PMCTRL_G3DVOLUPSTEP_ADDR(base) ((base) + (0x3EC))
#define SOC_PMCTRL_G3DVOLDNSTEP_ADDR(base) ((base) + (0x3F0))
#define SOC_PMCTRL_G3DDFTVOL_ADDR(base) ((base) + (0x3F4))
#define SOC_PMCTRL_G3DDESTVOL_ADDR(base) ((base) + (0x3F8))
#define SOC_PMCTRL_PMCINTRAW_ADDR(base) ((base) + (0x480))
#define SOC_PMCTRL_PMCINTCLR_ADDR(base) ((base) + (0x484))
#define SOC_PMCTRL_PMCINTENMCU_ADDR(base) ((base) + (0x488))
#define SOC_PMCTRL_PMCINTSTATMCU_ADDR(base) ((base) + (0x48C))
#define SOC_PMCTRL_PMCINTENACPU_ADDR(base) ((base) + (0x490))
#define SOC_PMCTRL_PMCINTSTATACPU_ADDR(base) ((base) + (0x494))
#define SOC_PMCTRL_PMCINTENMCPU_ADDR(base) ((base) + (0x498))
#define SOC_PMCTRL_PMCINTSTATMCPU_ADDR(base) ((base) + (0x49C))
#define SOC_PMCTRL_PMCSTATUS_ADDR(base) ((base) + (0x4A0))
#define SOC_PMCTRL_DSPPLLFRAC_ADDR(base) ((base) + (0x500))
#define SOC_PMCTRL_DSPPLLSSC_ADDR(base) ((base) + (0x504))
#define SOC_PMCTRL_DDRPLLFRAC_ADDR(base) ((base) + (0x508))
#define SOC_PMCTRL_DDRPLLSSC_ADDR(base) ((base) + (0x50C))
#define SOC_PMCTRL_ACPUPLL0FRAC_ADDR(base) ((base) + (0x510))
#define SOC_PMCTRL_ACPUPLL0SSC_ADDR(base) ((base) + (0x514))
#define SOC_PMCTRL_ACPUPLL1FRAC_ADDR(base) ((base) + (0x518))
#define SOC_PMCTRL_ACPUPLL1SSC_ADDR(base) ((base) + (0x51C))
#define SOC_PMCTRL_G3DPLL0FRAC_ADDR(base) ((base) + (0x520))
#define SOC_PMCTRL_G3DPLL0SSC_ADDR(base) ((base) + (0x524))
#define SOC_PMCTRL_G3DPLL1FRAC_ADDR(base) ((base) + (0x528))
#define SOC_PMCTRL_G3DPLL1SSC_ADDR(base) ((base) + (0x52C))
#define SOC_PMCTRL_MCPUPLLFRAC_ADDR(base) ((base) + (0x530))
#define SOC_PMCTRL_MCPUPLLSSC_ADDR(base) ((base) + (0x534))
#define SOC_PMCTRL_PERIPLLFRAC_ADDR(base) ((base) + (0x538))
#define SOC_PMCTRL_HDMIPLLFRAC_ADDR(base) ((base) + (0x540))
#define SOC_PMCTRL_BBPPLLFRAC_ADDR(base) ((base) + (0x548))
#define SOC_PMCTRL_DDRCLKSEL_ADDR(base) ((base) + (0x580))
#define SOC_PMCTRL_DDRCLKDIV_ADDR(base) ((base) + (0x584))
#define SOC_PMCTRL_DDRLPCTRL_ADDR(base) ((base) + (0x588))
#define SOC_PMCTRL_DDRCCLKOFFCFG_ADDR(base) ((base) + (0x590))
#define SOC_PMCTRL_DDRCDVFSEN_ADDR(base) ((base) + (0x594))
#define SOC_PMCTRL_DDRCFSEN_ADDR(base) ((base) + (0x598))
#define SOC_PMCTRL_DDRCLKPROFILE_ADDR(base) ((base) + (0x59C))
#define SOC_PMCTRL_DDRCVOLPROFILE_ADDR(base) ((base) + (0x5A0))
#define SOC_PMCTRL_DDRDIVTIMEOUT_ADDR(base) ((base) + (0x5A4))
#define SOC_PMCTRL_DDRCAVSPARAUDP_ADDR(base) ((base) + (0x600))
#define SOC_PMCTRL_DDRCAVSPARA0_ADDR(base) ((base) + (0x604))
#define SOC_PMCTRL_DDRCAVSPARA1_ADDR(base) ((base) + (0x608))
#define SOC_PMCTRL_DDRCAVSPARA2_ADDR(base) ((base) + (0x60C))
#define SOC_PMCTRL_DDRCAVSPARA3_ADDR(base) ((base) + (0x610))
#define SOC_PMCTRL_DDRCAVSPARA4_ADDR(base) ((base) + (0x614))
#define SOC_PMCTRL_DDRCAVSPARA5_ADDR(base) ((base) + (0x618))
#define SOC_PMCTRL_DDRCAVSPARA6_ADDR(base) ((base) + (0x61C))
#define SOC_PMCTRL_DDRCAVSPARA7_ADDR(base) ((base) + (0x620))
#define SOC_PMCTRL_DDRCAVSEN_ADDR(base) ((base) + (0x624))
#define SOC_PMCTRL_DDRCAVSPERIOD_ADDR(base) ((base) + (0x628))
#define SOC_PMCTRL_DDRCAVSRUNROUND_ADDR(base) ((base) + (0x62C))
#define SOC_PMCTRL_DDRCHPMCTRL_ADDR(base) ((base) + (0x680))
#define SOC_PMCTRL_DDRCHPMOPCVALID_ADDR(base) ((base) + (0x690))
#define SOC_PMCTRL_DDRCHPM01OPC_ADDR(base) ((base) + (0x694))
#define SOC_PMCTRL_DDRCHPMX01OPC_ADDR(base) ((base) + (0x698))
#define SOC_PMCTRL_DDRCHPM01PC_ADDR(base) ((base) + (0x69C))
#define SOC_PMCTRL_DDRCHPMBYPASS_ADDR(base) ((base) + (0x6A0))
#define SOC_PMCTRL_DDRCPMUVOLUPTIME_ADDR(base) ((base) + (0x6E0))
#define SOC_PMCTRL_DDRCPMUVOLDNTIME_ADDR(base) ((base) + (0x6E4))
#define SOC_PMCTRL_DDRCVOLPMUADDR_ADDR(base) ((base) + (0x6E8))
#define SOC_PMCTRL_DDRCVOLUPSTEP_ADDR(base) ((base) + (0x6EC))
#define SOC_PMCTRL_DDRCVOLDNSTEP_ADDR(base) ((base) + (0x6F0))
#define SOC_PMCTRL_DDRCDFTVOL_ADDR(base) ((base) + (0x6F4))
#define SOC_PMCTRL_DDRCDESTVOL_ADDR(base) ((base) + (0x6F8))
#define SOC_PMCTRL_ACPUHPMMASKEN_ADDR(base) ((base) + (0xC00))
#define SOC_PMCTRL_ACPUHPMMASKDIS_ADDR(base) ((base) + (0xC04))
#define SOC_PMCTRL_ACPUHPMMASKSTAT_ADDR(base) ((base) + (0xC08))
#define SOC_PMCTRL_G3DHPMMASKEN_ADDR(base) ((base) + (0xC10))
#define SOC_PMCTRL_G3DHPMMASKDIS_ADDR(base) ((base) + (0xC14))
#define SOC_PMCTRL_G3DHPMMASKSTAT_ADDR(base) ((base) + (0xC18))
#define SOC_PMCTRL_DDRCHPMMASKEN_ADDR(base) ((base) + (0xC20))
#define SOC_PMCTRL_DDRCHPMMASKDIS_ADDR(base) ((base) + (0xC24))
#define SOC_PMCTRL_DDRCHPMMASKSTAT_ADDR(base) ((base) + (0xC28))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsppll_en_cfg : 1;
        unsigned int dsppll_en_mod : 1;
        unsigned int reserved_0 : 1;
        unsigned int dsppll_en : 1;
        unsigned int dsppll_time : 24;
        unsigned int dsppll_timeout : 1;
        unsigned int dsppll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_DSPPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_cfg_START (0)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_cfg_END (0)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_mod_START (1)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_mod_END (1)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_START (3)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_en_END (3)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_time_START (4)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_time_END (27)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_timeout_START (28)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_timeout_END (28)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_lock_START (29)
#define SOC_PMCTRL_DSPPLLCTRL_dsppll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsppll_freq : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_DSPPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_DSPPLLFREQ_dsppll_freq_START (0)
#define SOC_PMCTRL_DSPPLLFREQ_dsppll_freq_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrpll_en_cfg : 1;
        unsigned int reserved_0 : 2;
        unsigned int ddrpll_en : 1;
        unsigned int ddrpll_time : 24;
        unsigned int ddrpll_timeout : 1;
        unsigned int ddrpll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_DDRPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_en_cfg_START (0)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_en_cfg_END (0)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_en_START (3)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_en_END (3)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_time_START (4)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_time_END (27)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_timeout_START (28)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_timeout_END (28)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_lock_START (29)
#define SOC_PMCTRL_DDRPLLCTRL_ddrpll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrpll_freq_cfg : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_DDRPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_DDRPLLFREQ_ddrpll_freq_cfg_START (0)
#define SOC_PMCTRL_DDRPLLFREQ_ddrpll_freq_cfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripll_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int peripll_time : 24;
        unsigned int peripll_timeout : 1;
        unsigned int peripll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_PERIPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_PERIPLLCTRL_peripll_en_START (0)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_en_END (0)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_time_START (4)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_time_END (27)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_timeout_START (28)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_timeout_END (28)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_lock_START (29)
#define SOC_PMCTRL_PERIPLLCTRL_peripll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripll_freq : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_PERIPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_PERIPLLFREQ_peripll_freq_START (0)
#define SOC_PMCTRL_PERIPLLFREQ_peripll_freq_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdmipll_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int hdmipll_time : 24;
        unsigned int hdmipll_timeout : 1;
        unsigned int hdmipll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_HDMIPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_en_START (0)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_en_END (0)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_time_START (4)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_time_END (27)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_timeout_START (28)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_timeout_END (28)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_lock_START (29)
#define SOC_PMCTRL_HDMIPLLCTRL_hdmipll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdmipll_freq : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_HDMIPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_HDMIPLLFREQ_hdmipll_freq_START (0)
#define SOC_PMCTRL_HDMIPLLFREQ_hdmipll_freq_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll0_en_cfg : 1;
        unsigned int reserved_0 : 3;
        unsigned int acpupll0_time : 24;
        unsigned int acpupll0_timeout : 1;
        unsigned int acpupll0_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_ACPUPLL0CTRL_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_en_cfg_START (0)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_en_cfg_END (0)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_time_START (4)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_time_END (27)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_timeout_START (28)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_timeout_END (28)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_lock_START (29)
#define SOC_PMCTRL_ACPUPLL0CTRL_acpupll0_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll0_freq_cfg : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_ACPUPLL0FREQ_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL0FREQ_acpupll0_freq_cfg_START (0)
#define SOC_PMCTRL_ACPUPLL0FREQ_acpupll0_freq_cfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll1_en_cfg : 1;
        unsigned int reserved_0 : 3;
        unsigned int acpupll1_time : 24;
        unsigned int acpupll1_timeout : 1;
        unsigned int acpupll1_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_ACPUPLL1CTRL_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_en_cfg_START (0)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_en_cfg_END (0)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_time_START (4)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_time_END (27)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_timeout_START (28)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_timeout_END (28)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_lock_START (29)
#define SOC_PMCTRL_ACPUPLL1CTRL_acpupll1_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll1_freq_cfg : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_ACPUPLL1FREQ_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL1FREQ_acpupll1_freq_cfg_START (0)
#define SOC_PMCTRL_ACPUPLL1FREQ_acpupll1_freq_cfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll0_en_cfg : 1;
        unsigned int reserved_0 : 2;
        unsigned int g3dpll0_en : 1;
        unsigned int g3dpll0_time : 24;
        unsigned int g3dpll0_timeout : 1;
        unsigned int g3dpll0_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_G3DPLL0CTRL_UNION;
#endif
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_cfg_START (0)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_cfg_END (0)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_START (3)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_en_END (3)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_time_START (4)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_time_END (27)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_timeout_START (28)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_timeout_END (28)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_lock_START (29)
#define SOC_PMCTRL_G3DPLL0CTRL_g3dpll0_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll0_freq_cfg : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_G3DPLL0FREQ_UNION;
#endif
#define SOC_PMCTRL_G3DPLL0FREQ_g3dpll0_freq_cfg_START (0)
#define SOC_PMCTRL_G3DPLL0FREQ_g3dpll0_freq_cfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll1_en_cfg : 1;
        unsigned int reserved_0 : 2;
        unsigned int g3dpll1_en : 1;
        unsigned int g3dpll1_time : 24;
        unsigned int g3dpll1_timeout : 1;
        unsigned int g3dpll1_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_G3DPLL1CTRL_UNION;
#endif
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_en_cfg_START (0)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_en_cfg_END (0)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_en_START (3)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_en_END (3)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_time_START (4)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_time_END (27)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_timeout_START (28)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_timeout_END (28)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_lock_START (29)
#define SOC_PMCTRL_G3DPLL1CTRL_g3dpll1_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll1_freq_cfg : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_G3DPLL1FREQ_UNION;
#endif
#define SOC_PMCTRL_G3DPLL1FREQ_g3dpll1_freq_cfg_START (0)
#define SOC_PMCTRL_G3DPLL1FREQ_g3dpll1_freq_cfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcpupll_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int mcpupll_time : 24;
        unsigned int mcpupll_timeout : 1;
        unsigned int mcpupll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_MCPUPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_en_START (0)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_en_END (0)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_time_START (4)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_time_END (27)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_timeout_START (28)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_timeout_END (28)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_lock_START (29)
#define SOC_PMCTRL_MCPUPLLCTRL_mcpupll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcpupll_freq : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_MCPUPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_MCPUPLLFREQ_mcpupll_freq_START (0)
#define SOC_PMCTRL_MCPUPLLFREQ_mcpupll_freq_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbppll_en_cfg : 1;
        unsigned int reserved_0 : 2;
        unsigned int bbppll_en : 1;
        unsigned int bbppll_time : 24;
        unsigned int bbppll_timeout : 1;
        unsigned int bbppll_lock : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_PMCTRL_BBPPLLCTRL_UNION;
#endif
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_en_cfg_START (0)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_en_cfg_END (0)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_en_START (3)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_en_END (3)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_time_START (4)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_time_END (27)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_timeout_START (28)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_timeout_END (28)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_lock_START (29)
#define SOC_PMCTRL_BBPPLLCTRL_bbppll_lock_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbppll_freq : 28;
        unsigned int reserved : 4;
    } reg;
} SOC_PMCTRL_BBPPLLFREQ_UNION;
#endif
#define SOC_PMCTRL_BBPPLLFREQ_bbppll_freq_START (0)
#define SOC_PMCTRL_BBPPLLFREQ_bbppll_freq_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbppll_en_alias : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_BBPPLLALIAS_UNION;
#endif
#define SOC_PMCTRL_BBPPLLALIAS_bbppll_en_alias_START (0)
#define SOC_PMCTRL_BBPPLLALIAS_bbppll_en_alias_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll1_en_alias : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_G3DPLL1ALIAS_UNION;
#endif
#define SOC_PMCTRL_G3DPLL1ALIAS_g3dpll1_en_alias_START (0)
#define SOC_PMCTRL_G3DPLL1ALIAS_g3dpll1_en_alias_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_4bit_cfg0_value0 : 3;
        unsigned int clk_4bit_cfg0_vld0 : 1;
        unsigned int clk_4bit_cfg0_value1 : 3;
        unsigned int clk_4bit_cfg0_vld1 : 1;
        unsigned int clk_4bit_cfg0_value2 : 3;
        unsigned int clk_4bit_cfg0_vld2 : 1;
        unsigned int clk_4bit_cfg0_value3 : 3;
        unsigned int clk_4bit_cfg0_vld3 : 1;
        unsigned int clk_4bit_cfg0_value4 : 3;
        unsigned int clk_4bit_cfg0_vld4 : 1;
        unsigned int clk_4bit_cfg0_value5 : 3;
        unsigned int clk_4bit_cfg0_vld5 : 1;
        unsigned int clk_4bit_cfg0_value6 : 3;
        unsigned int clk_4bit_cfg0_vld6 : 1;
        unsigned int clk_4bit_cfg0_value7 : 3;
        unsigned int clk_4bit_cfg0_vld7 : 1;
    } reg;
} SOC_PMCTRL_CLKCFG4BIT0_UNION;
#endif
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value0_START (0)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value0_END (2)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld0_START (3)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld0_END (3)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value1_START (4)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value1_END (6)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld1_START (7)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld1_END (7)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value2_START (8)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value2_END (10)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld2_START (11)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld2_END (11)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value3_START (12)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value3_END (14)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld3_START (15)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld3_END (15)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value4_START (16)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value4_END (18)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld4_START (19)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld4_END (19)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value5_START (20)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value5_END (22)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld5_START (23)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld5_END (23)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value6_START (24)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value6_END (26)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld6_START (27)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld6_END (27)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value7_START (28)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_value7_END (30)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld7_START (31)
#define SOC_PMCTRL_CLKCFG4BIT0_clk_4bit_cfg0_vld7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_4bit_cfg1_value0 : 3;
        unsigned int clk_4bit_cfg1_vld0 : 1;
        unsigned int clk_4bit_cfg1_value1 : 3;
        unsigned int clk_4bit_cfg1_vld1 : 1;
        unsigned int clk_4bit_cfg1_value2 : 3;
        unsigned int clk_4bit_cfg1_vld2 : 1;
        unsigned int clk_4bit_cfg1_value3 : 3;
        unsigned int clk_4bit_cfg1_vld3 : 1;
        unsigned int clk_4bit_cfg1_value4 : 3;
        unsigned int clk_4bit_cfg1_vld4 : 1;
        unsigned int clk_4bit_cfg1_value5 : 3;
        unsigned int clk_4bit_cfg1_vld5 : 1;
        unsigned int clk_4bit_cfg1_value6 : 3;
        unsigned int clk_4bit_cfg1_vld6 : 1;
        unsigned int clk_4bit_cfg1_value7 : 3;
        unsigned int clk_4bit_cfg1_vld7 : 1;
    } reg;
} SOC_PMCTRL_CLKCFG4BIT1_UNION;
#endif
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_START (0)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value0_END (2)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_START (3)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld0_END (3)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value1_START (4)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value1_END (6)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld1_START (7)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld1_END (7)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_START (8)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value2_END (10)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_START (11)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld2_END (11)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value3_START (12)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value3_END (14)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld3_START (15)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld3_END (15)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_START (16)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value4_END (18)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_START (19)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld4_END (19)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value5_START (20)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value5_END (22)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld5_START (23)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld5_END (23)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value6_START (24)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value6_END (26)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld6_START (27)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld6_END (27)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value7_START (28)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_value7_END (30)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld7_START (31)
#define SOC_PMCTRL_CLKCFG4BIT1_clk_4bit_cfg1_vld7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clk_4bit_cfg2_value0 : 3;
        unsigned int clk_4bit_cfg2_vld0 : 1;
        unsigned int clk_4bit_cfg2_value1 : 3;
        unsigned int clk_4bit_cfg2_vld1 : 1;
        unsigned int clk_4bit_cfg2_value2 : 3;
        unsigned int clk_4bit_cfg2_vld2 : 1;
        unsigned int clk_4bit_cfg2_value3 : 3;
        unsigned int clk_4bit_cfg2_vld3 : 1;
        unsigned int clk_4bit_cfg2_value4 : 3;
        unsigned int clk_4bit_cfg2_vld4 : 1;
        unsigned int clk_4bit_cfg2_value5 : 3;
        unsigned int clk_4bit_cfg2_vld5 : 1;
        unsigned int clk_4bit_cfg2_value6 : 3;
        unsigned int clk_4bit_cfg2_vld6 : 1;
        unsigned int clk_4bit_cfg2_value7 : 3;
        unsigned int clk_4bit_cfg2_vld7 : 1;
    } reg;
} SOC_PMCTRL_CLKCFG4BIT2_UNION;
#endif
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value0_START (0)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value0_END (2)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld0_START (3)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld0_END (3)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value1_START (4)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value1_END (6)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld1_START (7)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld1_END (7)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value2_START (8)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value2_END (10)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld2_START (11)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld2_END (11)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value3_START (12)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value3_END (14)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld3_START (15)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld3_END (15)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value4_START (16)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value4_END (18)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld4_START (19)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld4_END (19)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value5_START (20)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value5_END (22)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld5_START (23)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld5_END (23)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value6_START (24)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value6_END (26)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld6_START (27)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld6_END (27)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value7_START (28)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_value7_END (30)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld7_START (31)
#define SOC_PMCTRL_CLKCFG4BIT2_clk_4bit_cfg2_vld7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer0_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timer0_val : 24;
        unsigned int timer0_timeout : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_TIMER0CTRL_UNION;
#endif
#define SOC_PMCTRL_TIMER0CTRL_timer0_en_START (0)
#define SOC_PMCTRL_TIMER0CTRL_timer0_en_END (0)
#define SOC_PMCTRL_TIMER0CTRL_timer0_val_START (4)
#define SOC_PMCTRL_TIMER0CTRL_timer0_val_END (27)
#define SOC_PMCTRL_TIMER0CTRL_timer0_timeout_START (28)
#define SOC_PMCTRL_TIMER0CTRL_timer0_timeout_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer1_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timer1_val : 24;
        unsigned int timer1_timeout : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_TIMER1CTRL_UNION;
#endif
#define SOC_PMCTRL_TIMER1CTRL_timer1_en_START (0)
#define SOC_PMCTRL_TIMER1CTRL_timer1_en_END (0)
#define SOC_PMCTRL_TIMER1CTRL_timer1_val_START (4)
#define SOC_PMCTRL_TIMER1CTRL_timer1_val_END (27)
#define SOC_PMCTRL_TIMER1CTRL_timer1_timeout_START (28)
#define SOC_PMCTRL_TIMER1CTRL_timer1_timeout_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer2_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timer2_val : 24;
        unsigned int timer2_timeout : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_TIMER2CTRL_UNION;
#endif
#define SOC_PMCTRL_TIMER2CTRL_timer2_en_START (0)
#define SOC_PMCTRL_TIMER2CTRL_timer2_en_END (0)
#define SOC_PMCTRL_TIMER2CTRL_timer2_val_START (4)
#define SOC_PMCTRL_TIMER2CTRL_timer2_val_END (27)
#define SOC_PMCTRL_TIMER2CTRL_timer2_timeout_START (28)
#define SOC_PMCTRL_TIMER2CTRL_timer2_timeout_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timer3_en : 1;
        unsigned int reserved_0 : 3;
        unsigned int timer3_val : 24;
        unsigned int timer3_timeout : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_TIMER3CTRL_UNION;
#endif
#define SOC_PMCTRL_TIMER3CTRL_timer3_en_START (0)
#define SOC_PMCTRL_TIMER3CTRL_timer3_en_END (0)
#define SOC_PMCTRL_TIMER3CTRL_timer3_val_START (4)
#define SOC_PMCTRL_TIMER3CTRL_timer3_val_END (27)
#define SOC_PMCTRL_TIMER3CTRL_timer3_timeout_START (28)
#define SOC_PMCTRL_TIMER3CTRL_timer3_timeout_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmussi_chn_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_PMUSSICHNEN_UNION;
#endif
#define SOC_PMCTRL_PMUSSICHNEN_pmussi_chn_en_START (0)
#define SOC_PMCTRL_PMUSSICHNEN_pmussi_chn_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_pllsw_cfg : 1;
        unsigned int acpu_pllsw_stat : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_ACPUPLLSEL_UNION;
#endif
#define SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_cfg_START (0)
#define SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_cfg_END (0)
#define SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_stat_START (1)
#define SOC_PMCTRL_ACPUPLLSEL_acpu_pllsw_stat_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_per_div_cfg : 4;
        unsigned int reserved_0 : 4;
        unsigned int acpu_l2_div_cfg : 2;
        unsigned int reserved_1 : 6;
        unsigned int acpu_per_div_stat : 4;
        unsigned int reserved_2 : 4;
        unsigned int acpu_l2_div_stat : 2;
        unsigned int reserved_3 : 6;
    } reg;
} SOC_PMCTRL_ACPUCLKDIV_UNION;
#endif
#define SOC_PMCTRL_ACPUCLKDIV_acpu_per_div_cfg_START (0)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_per_div_cfg_END (3)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_l2_div_cfg_START (8)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_l2_div_cfg_END (9)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_per_div_stat_START (16)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_per_div_stat_END (19)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_l2_div_stat_START (24)
#define SOC_PMCTRL_ACPUCLKDIV_acpu_l2_div_stat_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_memrm_cfg : 8;
        unsigned int l2cc_memrm_cfg : 8;
        unsigned int acpu_memrm_stat : 8;
        unsigned int l2cc_memrm_stat : 8;
    } reg;
} SOC_PMCTRL_ACPUMEMRM_UNION;
#endif
#define SOC_PMCTRL_ACPUMEMRM_acpu_memrm_cfg_START (0)
#define SOC_PMCTRL_ACPUMEMRM_acpu_memrm_cfg_END (7)
#define SOC_PMCTRL_ACPUMEMRM_l2cc_memrm_cfg_START (8)
#define SOC_PMCTRL_ACPUMEMRM_l2cc_memrm_cfg_END (15)
#define SOC_PMCTRL_ACPUMEMRM_acpu_memrm_stat_START (16)
#define SOC_PMCTRL_ACPUMEMRM_acpu_memrm_stat_END (23)
#define SOC_PMCTRL_ACPUMEMRM_l2cc_memrm_stat_START (24)
#define SOC_PMCTRL_ACPUMEMRM_l2cc_memrm_stat_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_clkoff_vol : 1;
        unsigned int acpu_clkoff_memrm : 1;
        unsigned int acpu_pllon_idle : 1;
        unsigned int reserved_0 : 1;
        unsigned int acpu_memrm_time : 5;
        unsigned int reserved_1 : 3;
        unsigned int acpu_dvfs_pwrctrl_en : 1;
        unsigned int reserved_2 : 3;
        unsigned int acpu_dvfs_ko_avs_dis : 1;
        unsigned int reserved_3 : 15;
    } reg;
} SOC_PMCTRL_ACPUCLKOFFCFG_UNION;
#endif
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_clkoff_vol_START (0)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_clkoff_vol_END (0)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_clkoff_memrm_START (1)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_clkoff_memrm_END (1)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_pllon_idle_START (2)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_pllon_idle_END (2)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_memrm_time_START (4)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_memrm_time_END (8)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_dvfs_pwrctrl_en_START (12)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_dvfs_pwrctrl_en_END (12)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_dvfs_ko_avs_dis_START (16)
#define SOC_PMCTRL_ACPUCLKOFFCFG_acpu_dvfs_ko_avs_dis_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_dvfs_start : 1;
        unsigned int acpu_profile_updn : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_ACPUDVFSEN_UNION;
#endif
#define SOC_PMCTRL_ACPUDVFSEN_acpu_dvfs_start_START (0)
#define SOC_PMCTRL_ACPUDVFSEN_acpu_dvfs_start_END (0)
#define SOC_PMCTRL_ACPUDVFSEN_acpu_profile_updn_START (1)
#define SOC_PMCTRL_ACPUDVFSEN_acpu_profile_updn_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll_freq_prof : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_PMCTRL_ACPUCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_ACPUCLKPROFILE0_acpupll_freq_prof_START (0)
#define SOC_PMCTRL_ACPUCLKPROFILE0_acpupll_freq_prof_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_per_div_prof : 4;
        unsigned int reserved_0 : 4;
        unsigned int acpu_l2_div_prof : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_PMCTRL_ACPUCLKPROFILE1_UNION;
#endif
#define SOC_PMCTRL_ACPUCLKPROFILE1_acpu_per_div_prof_START (0)
#define SOC_PMCTRL_ACPUCLKPROFILE1_acpu_per_div_prof_END (3)
#define SOC_PMCTRL_ACPUCLKPROFILE1_acpu_l2_div_prof_START (8)
#define SOC_PMCTRL_ACPUCLKPROFILE1_acpu_l2_div_prof_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_idx_prof : 7;
        unsigned int reserved_0 : 1;
        unsigned int acpu_memrm_prof : 8;
        unsigned int l2cc_memrm_prof : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_PMCTRL_ACPUVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_ACPUVOLPROFILE_acpu_vol_idx_prof_START (0)
#define SOC_PMCTRL_ACPUVOLPROFILE_acpu_vol_idx_prof_END (6)
#define SOC_PMCTRL_ACPUVOLPROFILE_acpu_memrm_prof_START (8)
#define SOC_PMCTRL_ACPUVOLPROFILE_acpu_memrm_prof_END (15)
#define SOC_PMCTRL_ACPUVOLPROFILE_l2cc_memrm_prof_START (16)
#define SOC_PMCTRL_ACPUVOLPROFILE_l2cc_memrm_prof_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll0_freq : 24;
        unsigned int acpupll0_en : 1;
        unsigned int reserved : 7;
    } reg;
} SOC_PMCTRL_ACPUPLL0STAT_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL0STAT_acpupll0_freq_START (0)
#define SOC_PMCTRL_ACPUPLL0STAT_acpupll0_freq_END (23)
#define SOC_PMCTRL_ACPUPLL0STAT_acpupll0_en_START (24)
#define SOC_PMCTRL_ACPUPLL0STAT_acpupll0_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll1_freq : 24;
        unsigned int acpupll1_en : 1;
        unsigned int reserved : 7;
    } reg;
} SOC_PMCTRL_ACPUPLL1STAT_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL1STAT_acpupll1_freq_START (0)
#define SOC_PMCTRL_ACPUPLL1STAT_acpupll1_freq_END (23)
#define SOC_PMCTRL_ACPUPLL1STAT_acpupll1_en_START (24)
#define SOC_PMCTRL_ACPUPLL1STAT_acpupll1_en_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_clkdiv_time : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_ACPUDIVTIMEOUT_UNION;
#endif
#define SOC_PMCTRL_ACPUDIVTIMEOUT_acpu_clkdiv_time_START (0)
#define SOC_PMCTRL_ACPUDIVTIMEOUT_acpu_clkdiv_time_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avspara_update : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_ACPUAVSPARAUPD_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARAUPD_acpu_avspara_update_START (0)
#define SOC_PMCTRL_ACPUAVSPARAUPD_acpu_avspara_update_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_clk_div : 6;
        unsigned int reserved_0 : 10;
        unsigned int acpu_avs_opc_mod : 2;
        unsigned int reserved_1 : 2;
        unsigned int acpu_avs_hpm_sel : 3;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_hpm_clk_div_START (0)
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_hpm_clk_div_END (5)
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_avs_opc_mod_START (16)
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_avs_opc_mod_END (17)
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_avs_hpm_sel_START (20)
#define SOC_PMCTRL_ACPUAVSPARA0_acpu_avs_hpm_sel_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_opc_offset : 10;
        unsigned int reserved_0 : 2;
        unsigned int acpu_avs_rcc : 5;
        unsigned int reserved_1 : 3;
        unsigned int acpu_avs_irgap : 5;
        unsigned int reserved_2 : 3;
        unsigned int acpu_avs_opc_shift : 3;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_opc_offset_START (0)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_opc_offset_END (9)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_rcc_START (12)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_rcc_END (16)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_irgap_START (20)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_irgap_END (24)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_opc_shift_START (28)
#define SOC_PMCTRL_ACPUAVSPARA1_acpu_avs_opc_shift_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_vol_up_gain1 : 4;
        unsigned int acpu_avs_vol_up_gain2 : 4;
        unsigned int acpu_avs_vol_up_gain3 : 4;
        unsigned int acpu_avs_vol_up_gain4 : 4;
        unsigned int acpu_avs_vol_up_gain5 : 4;
        unsigned int acpu_avs_vol_up_gain6 : 4;
        unsigned int acpu_avs_vol_up_gain7 : 4;
        unsigned int acpu_avs_vol_up_gain8 : 4;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain1_START (0)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain1_END (3)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain2_START (4)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain2_END (7)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain3_START (8)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain3_END (11)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain4_START (12)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain4_END (15)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain5_START (16)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain5_END (19)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain6_START (20)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain6_END (23)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain7_START (24)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain7_END (27)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain8_START (28)
#define SOC_PMCTRL_ACPUAVSPARA2_acpu_avs_vol_up_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_vol_up_gain9 : 4;
        unsigned int acpu_avs_vol_up_gain10 : 4;
        unsigned int acpu_avs_vol_up_gain11 : 4;
        unsigned int acpu_avs_vol_up_gain12 : 4;
        unsigned int acpu_avs_vol_up_gain13 : 4;
        unsigned int acpu_avs_vol_up_gain14 : 4;
        unsigned int acpu_avs_vol_up_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain9_START (0)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain9_END (3)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain10_START (4)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain10_END (7)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain11_START (8)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain11_END (11)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain12_START (12)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain12_END (15)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain13_START (16)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain13_END (19)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain14_START (20)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain14_END (23)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain15_START (24)
#define SOC_PMCTRL_ACPUAVSPARA3_acpu_avs_vol_up_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_vol_dn_gain1 : 4;
        unsigned int acpu_avs_vol_dn_gain2 : 4;
        unsigned int acpu_avs_vol_dn_gain3 : 4;
        unsigned int acpu_avs_vol_dn_gain4 : 4;
        unsigned int acpu_avs_vol_dn_gain5 : 4;
        unsigned int acpu_avs_vol_dn_gain6 : 4;
        unsigned int acpu_avs_vol_dn_gain7 : 4;
        unsigned int acpu_avs_vol_dn_gain8 : 4;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain1_START (0)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain1_END (3)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain2_START (4)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain2_END (7)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain3_START (8)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain3_END (11)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain4_START (12)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain4_END (15)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain5_START (16)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain5_END (19)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain6_START (20)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain6_END (23)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain7_START (24)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain7_END (27)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain8_START (28)
#define SOC_PMCTRL_ACPUAVSPARA4_acpu_avs_vol_dn_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_vol_dn_gain9 : 4;
        unsigned int acpu_avs_vol_dn_gain10 : 4;
        unsigned int acpu_avs_vol_dn_gain11 : 4;
        unsigned int acpu_avs_vol_dn_gain12 : 4;
        unsigned int acpu_avs_vol_dn_gain13 : 4;
        unsigned int acpu_avs_vol_dn_gain14 : 4;
        unsigned int acpu_avs_vol_dn_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain9_START (0)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain9_END (3)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain10_START (4)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain10_END (7)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain11_START (8)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain11_END (11)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain12_START (12)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain12_END (15)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain13_START (16)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain13_END (19)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain14_START (20)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain14_END (23)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain15_START (24)
#define SOC_PMCTRL_ACPUAVSPARA5_acpu_avs_vol_dn_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_max_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int acpu_avs_min_vol : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA6_acpu_avs_max_vol_START (0)
#define SOC_PMCTRL_ACPUAVSPARA6_acpu_avs_max_vol_END (6)
#define SOC_PMCTRL_ACPUAVSPARA6_acpu_avs_min_vol_START (8)
#define SOC_PMCTRL_ACPUAVSPARA6_acpu_avs_min_vol_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_sample_num : 22;
        unsigned int reserved_0 : 2;
        unsigned int acpu_avs_sample_shift : 5;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_ACPUAVSPARA7_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPARA7_acpu_avs_sample_num_START (0)
#define SOC_PMCTRL_ACPUAVSPARA7_acpu_avs_sample_num_END (21)
#define SOC_PMCTRL_ACPUAVSPARA7_acpu_avs_sample_shift_START (24)
#define SOC_PMCTRL_ACPUAVSPARA7_acpu_avs_sample_shift_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avspara_update : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_L2CCAVSPARAUPD_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARAUPD_l2cc_avspara_update_START (0)
#define SOC_PMCTRL_L2CCAVSPARAUPD_l2cc_avspara_update_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_hpm_clk_div : 6;
        unsigned int reserved_0 : 10;
        unsigned int l2cc_avs_opc_mod : 2;
        unsigned int reserved_1 : 2;
        unsigned int l2cc_avs_hpm_sel : 3;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_hpm_clk_div_START (0)
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_hpm_clk_div_END (5)
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_avs_opc_mod_START (16)
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_avs_opc_mod_END (17)
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_avs_hpm_sel_START (20)
#define SOC_PMCTRL_L2CCAVSPARA0_l2cc_avs_hpm_sel_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_opc_offset : 10;
        unsigned int reserved_0 : 2;
        unsigned int l2cc_avs_rcc : 5;
        unsigned int reserved_1 : 3;
        unsigned int l2cc_avs_irgap : 5;
        unsigned int reserved_2 : 3;
        unsigned int l2cc_avs_opc_shift : 3;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_opc_offset_START (0)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_opc_offset_END (9)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_rcc_START (12)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_rcc_END (16)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_irgap_START (20)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_irgap_END (24)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_opc_shift_START (28)
#define SOC_PMCTRL_L2CCAVSPARA1_l2cc_avs_opc_shift_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_vol_up_gain1 : 4;
        unsigned int l2cc_avs_vol_up_gain2 : 4;
        unsigned int l2cc_avs_vol_up_gain3 : 4;
        unsigned int l2cc_avs_vol_up_gain4 : 4;
        unsigned int l2cc_avs_vol_up_gain5 : 4;
        unsigned int l2cc_avs_vol_up_gain6 : 4;
        unsigned int l2cc_avs_vol_up_gain7 : 4;
        unsigned int l2cc_avs_vol_up_gain8 : 4;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain1_START (0)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain1_END (3)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain2_START (4)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain2_END (7)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain3_START (8)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain3_END (11)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain4_START (12)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain4_END (15)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain5_START (16)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain5_END (19)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain6_START (20)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain6_END (23)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain7_START (24)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain7_END (27)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain8_START (28)
#define SOC_PMCTRL_L2CCAVSPARA2_l2cc_avs_vol_up_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_vol_up_gain9 : 4;
        unsigned int l2cc_avs_vol_up_gain10 : 4;
        unsigned int l2cc_avs_vol_up_gain11 : 4;
        unsigned int l2cc_avs_vol_up_gain12 : 4;
        unsigned int l2cc_avs_vol_up_gain13 : 4;
        unsigned int l2cc_avs_vol_up_gain14 : 4;
        unsigned int l2cc_avs_vol_up_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain9_START (0)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain9_END (3)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain10_START (4)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain10_END (7)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain11_START (8)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain11_END (11)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain12_START (12)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain12_END (15)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain13_START (16)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain13_END (19)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain14_START (20)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain14_END (23)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain15_START (24)
#define SOC_PMCTRL_L2CCAVSPARA3_l2cc_avs_vol_up_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_vol_dn_gain1 : 4;
        unsigned int l2cc_avs_vol_dn_gain2 : 4;
        unsigned int l2cc_avs_vol_dn_gain3 : 4;
        unsigned int l2cc_avs_vol_dn_gain4 : 4;
        unsigned int l2cc_avs_vol_dn_gain5 : 4;
        unsigned int l2cc_avs_vol_dn_gain6 : 4;
        unsigned int l2cc_avs_vol_dn_gain7 : 4;
        unsigned int l2cc_avs_vol_dn_gain8 : 4;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain1_START (0)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain1_END (3)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain2_START (4)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain2_END (7)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain3_START (8)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain3_END (11)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain4_START (12)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain4_END (15)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain5_START (16)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain5_END (19)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain6_START (20)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain6_END (23)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain7_START (24)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain7_END (27)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain8_START (28)
#define SOC_PMCTRL_L2CCAVSPARA4_l2cc_avs_vol_dn_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_vol_dn_gain9 : 4;
        unsigned int l2cc_avs_vol_dn_gain10 : 4;
        unsigned int l2cc_avs_vol_dn_gain11 : 4;
        unsigned int l2cc_avs_vol_dn_gain12 : 4;
        unsigned int l2cc_avs_vol_dn_gain13 : 4;
        unsigned int l2cc_avs_vol_dn_gain14 : 4;
        unsigned int l2cc_avs_vol_dn_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain9_START (0)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain9_END (3)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain10_START (4)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain10_END (7)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain11_START (8)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain11_END (11)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain12_START (12)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain12_END (15)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain13_START (16)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain13_END (19)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain14_START (20)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain14_END (23)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain15_START (24)
#define SOC_PMCTRL_L2CCAVSPARA5_l2cc_avs_vol_dn_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_max_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int l2cc_avs_min_vol : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA6_l2cc_avs_max_vol_START (0)
#define SOC_PMCTRL_L2CCAVSPARA6_l2cc_avs_max_vol_END (6)
#define SOC_PMCTRL_L2CCAVSPARA6_l2cc_avs_min_vol_START (8)
#define SOC_PMCTRL_L2CCAVSPARA6_l2cc_avs_min_vol_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_avs_sample_num : 22;
        unsigned int reserved_0 : 2;
        unsigned int l2cc_avs_sample_shift : 5;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_L2CCAVSPARA7_UNION;
#endif
#define SOC_PMCTRL_L2CCAVSPARA7_l2cc_avs_sample_num_START (0)
#define SOC_PMCTRL_L2CCAVSPARA7_l2cc_avs_sample_num_END (21)
#define SOC_PMCTRL_L2CCAVSPARA7_l2cc_avs_sample_shift_START (24)
#define SOC_PMCTRL_L2CCAVSPARA7_l2cc_avs_sample_shift_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_en : 1;
        unsigned int acpu_avs_pwctrl_en : 1;
        unsigned int reserved_0 : 2;
        unsigned int l2cc_avs_en : 1;
        unsigned int l2cc_avs_pwctrl_en : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_PMCTRL_ACPUAVSEN_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSEN_acpu_avs_en_START (0)
#define SOC_PMCTRL_ACPUAVSEN_acpu_avs_en_END (0)
#define SOC_PMCTRL_ACPUAVSEN_acpu_avs_pwctrl_en_START (1)
#define SOC_PMCTRL_ACPUAVSEN_acpu_avs_pwctrl_en_END (1)
#define SOC_PMCTRL_ACPUAVSEN_l2cc_avs_en_START (4)
#define SOC_PMCTRL_ACPUAVSEN_l2cc_avs_en_END (4)
#define SOC_PMCTRL_ACPUAVSEN_l2cc_avs_pwctrl_en_START (5)
#define SOC_PMCTRL_ACPUAVSEN_l2cc_avs_pwctrl_en_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_period : 32;
    } reg;
} SOC_PMCTRL_ACPUAVSPERIOD_UNION;
#endif
#define SOC_PMCTRL_ACPUAVSPERIOD_acpu_avs_period_START (0)
#define SOC_PMCTRL_ACPUAVSPERIOD_acpu_avs_period_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_avs_round : 8;
        unsigned int l2cc_avs_round : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_PMCTRL_AACPUAVSRUNROUND_UNION;
#endif
#define SOC_PMCTRL_AACPUAVSRUNROUND_acpu_avs_round_START (0)
#define SOC_PMCTRL_AACPUAVSRUNROUND_acpu_avs_round_END (7)
#define SOC_PMCTRL_AACPUAVSRUNROUND_l2cc_avs_round_START (8)
#define SOC_PMCTRL_AACPUAVSRUNROUND_l2cc_avs_round_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_pllsw_cfg : 1;
        unsigned int g3d_pllsw_stat : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_G3DCLKSEL_UNION;
#endif
#define SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_START (0)
#define SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_cfg_END (0)
#define SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_START (1)
#define SOC_PMCTRL_G3DCLKSEL_g3d_pllsw_stat_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_clkdiv_cfg : 4;
        unsigned int reserved_0 : 12;
        unsigned int g3d_clkdiv_stat : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_PMCTRL_G3DCLKDIV_UNION;
#endif
#define SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_START (0)
#define SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_cfg_END (3)
#define SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_stat_START (16)
#define SOC_PMCTRL_G3DCLKDIV_g3d_clkdiv_stat_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_memrm_cfg : 8;
        unsigned int reserved_0 : 8;
        unsigned int g3d_memrm_stat : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_PMCTRL_G3DMEMRM_UNION;
#endif
#define SOC_PMCTRL_G3DMEMRM_g3d_memrm_cfg_START (0)
#define SOC_PMCTRL_G3DMEMRM_g3d_memrm_cfg_END (7)
#define SOC_PMCTRL_G3DMEMRM_g3d_memrm_stat_START (16)
#define SOC_PMCTRL_G3DMEMRM_g3d_memrm_stat_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_clkoff_vol : 1;
        unsigned int g3d_clkoff_memrm : 1;
        unsigned int g3d_pllon_idle : 1;
        unsigned int reserved_0 : 1;
        unsigned int g3d_memrm_time : 5;
        unsigned int reserved_1 : 3;
        unsigned int g3d_dvfs_pwctrl_en : 1;
        unsigned int reserved_2 : 3;
        unsigned int g3d_dvfs_ko_avs_dis : 1;
        unsigned int reserved_3 : 15;
    } reg;
} SOC_PMCTRL_G3DCLKOFFCFG_UNION;
#endif
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_clkoff_vol_START (0)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_clkoff_vol_END (0)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_clkoff_memrm_START (1)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_clkoff_memrm_END (1)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_pllon_idle_START (2)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_pllon_idle_END (2)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_memrm_time_START (4)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_memrm_time_END (8)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_dvfs_pwctrl_en_START (12)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_dvfs_pwctrl_en_END (12)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_dvfs_ko_avs_dis_START (16)
#define SOC_PMCTRL_G3DCLKOFFCFG_g3d_dvfs_ko_avs_dis_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_dvfs_start : 1;
        unsigned int g3d_profile_updn : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_G3DDVFSEN_UNION;
#endif
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_start_START (0)
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_start_END (0)
#define SOC_PMCTRL_G3DDVFSEN_g3d_profile_updn_START (1)
#define SOC_PMCTRL_G3DDVFSEN_g3d_profile_updn_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll_sel_prof : 1;
        unsigned int reserved_0 : 3;
        unsigned int g3d_clkdiv_prof : 4;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_PMCTRL_G3DCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_G3DCLKPROFILE0_g3dpll_sel_prof_START (0)
#define SOC_PMCTRL_G3DCLKPROFILE0_g3dpll_sel_prof_END (0)
#define SOC_PMCTRL_G3DCLKPROFILE0_g3d_clkdiv_prof_START (4)
#define SOC_PMCTRL_G3DCLKPROFILE0_g3d_clkdiv_prof_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_idx_prof : 7;
        unsigned int reserved_0 : 1;
        unsigned int g3d_memrm_prof : 8;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_PMCTRL_G3DVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_prof_START (0)
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_prof_END (6)
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_memrm_prof_START (8)
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_memrm_prof_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_clkdiv_time : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_G3DDIVTIMEOUT_UNION;
#endif
#define SOC_PMCTRL_G3DDIVTIMEOUT_g3d_clkdiv_time_START (0)
#define SOC_PMCTRL_G3DDIVTIMEOUT_g3d_clkdiv_time_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avspara_update : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_G3DAVSPARAUDP_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARAUDP_g3d_avspara_update_START (0)
#define SOC_PMCTRL_G3DAVSPARAUDP_g3d_avspara_update_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_clk_div : 6;
        unsigned int reserved_0 : 10;
        unsigned int g3d_avs_opc_mod : 2;
        unsigned int reserved_1 : 2;
        unsigned int g3d_avs_hpm_sel : 3;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_PMCTRL_G3DAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA0_g3d_hpm_clk_div_START (0)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_hpm_clk_div_END (5)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_START (16)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_END (17)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_START (20)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_opc_offset : 10;
        unsigned int reserved_0 : 2;
        unsigned int g3d_avs_rcc : 5;
        unsigned int reserved_1 : 3;
        unsigned int g3d_avs_irgap : 5;
        unsigned int reserved_2 : 3;
        unsigned int g3d_avs_opc_shift : 3;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_PMCTRL_G3DAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_opc_offset_START (0)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_opc_offset_END (9)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_rcc_START (12)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_rcc_END (16)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_irgap_START (20)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_irgap_END (24)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_opc_shift_START (28)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_opc_shift_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_vol_up_gain1 : 4;
        unsigned int g3d_avs_vol_up_gain2 : 4;
        unsigned int g3d_avs_vol_up_gain3 : 4;
        unsigned int g3d_avs_vol_up_gain4 : 4;
        unsigned int g3d_avs_vol_up_gain5 : 4;
        unsigned int g3d_avs_vol_up_gain6 : 4;
        unsigned int g3d_avs_vol_up_gain7 : 4;
        unsigned int g3d_avs_vol_up_gain8 : 4;
    } reg;
} SOC_PMCTRL_G3DAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain1_START (0)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain1_END (3)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain2_START (4)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain2_END (7)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain3_START (8)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain3_END (11)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain4_START (12)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain4_END (15)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain5_START (16)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain5_END (19)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain6_START (20)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain6_END (23)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain7_START (24)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain7_END (27)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain8_START (28)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_vol_up_gain9 : 4;
        unsigned int g3d_avs_vol_up_gain10 : 4;
        unsigned int g3d_avs_vol_up_gain11 : 4;
        unsigned int g3d_avs_vol_up_gain12 : 4;
        unsigned int g3d_avs_vol_up_gain13 : 4;
        unsigned int g3d_avs_vol_up_gain14 : 4;
        unsigned int g3d_avs_vol_up_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_G3DAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain9_START (0)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain9_END (3)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain10_START (4)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain10_END (7)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain11_START (8)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain11_END (11)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain12_START (12)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain12_END (15)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain13_START (16)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain13_END (19)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain14_START (20)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain14_END (23)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain15_START (24)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_up_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_vol_dn_gain1 : 4;
        unsigned int g3d_avs_vol_dn_gain2 : 4;
        unsigned int g3d_avs_vol_dn_gain3 : 4;
        unsigned int g3d_avs_vol_dn_gain4 : 4;
        unsigned int g3d_avs_vol_dn_gain5 : 4;
        unsigned int g3d_avs_vol_dn_gain6 : 4;
        unsigned int g3d_avs_vol_dn_gain7 : 4;
        unsigned int g3d_avs_vol_dn_gain8 : 4;
    } reg;
} SOC_PMCTRL_G3DAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain1_START (0)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain1_END (3)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain2_START (4)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain2_END (7)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain3_START (8)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain3_END (11)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain4_START (12)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain4_END (15)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain5_START (16)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain5_END (19)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain6_START (20)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain6_END (23)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain7_START (24)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain7_END (27)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain8_START (28)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_vol_dn_gain9 : 4;
        unsigned int g3d_avs_vol_dn_gain10 : 4;
        unsigned int g3d_avs_vol_dn_gain11 : 4;
        unsigned int g3d_avs_vol_dn_gain12 : 4;
        unsigned int g3d_avs_vol_dn_gain13 : 4;
        unsigned int g3d_avs_vol_dn_gain14 : 4;
        unsigned int g3d_avs_vol_dn_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_G3DAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain9_START (0)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain9_END (3)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain10_START (4)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain10_END (7)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain11_START (8)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain11_END (11)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain12_START (12)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain12_END (15)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain13_START (16)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain13_END (19)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain14_START (20)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain14_END (23)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain15_START (24)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_vol_dn_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_max_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int g3d_avs_min_vol : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_G3DAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_max_vol_START (0)
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_max_vol_END (6)
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_min_vol_START (8)
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_min_vol_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_sample_num : 22;
        unsigned int reserved_0 : 2;
        unsigned int g3d_avs_sample_shift : 5;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_G3DAVSPARA7_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA7_g3d_avs_sample_num_START (0)
#define SOC_PMCTRL_G3DAVSPARA7_g3d_avs_sample_num_END (21)
#define SOC_PMCTRL_G3DAVSPARA7_g3d_avs_sample_shift_START (24)
#define SOC_PMCTRL_G3DAVSPARA7_g3d_avs_sample_shift_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_en : 1;
        unsigned int g3d_avs_pwctrl_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_G3DAVSEN_UNION;
#endif
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_START (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_END (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_START (1)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_period : 32;
    } reg;
} SOC_PMCTRL_G3DAVSPERIOD_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPERIOD_g3d_avs_period_START (0)
#define SOC_PMCTRL_G3DAVSPERIOD_g3d_avs_period_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_avs_round : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_PMCTRL_G3DAVSRUNROUND_UNION;
#endif
#define SOC_PMCTRL_G3DAVSRUNROUND_g3d_avs_round_START (0)
#define SOC_PMCTRL_G3DAVSRUNROUND_g3d_avs_round_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_en : 7;
        unsigned int reserved_0 : 1;
        unsigned int acpu_hpmx_en : 7;
        unsigned int reserved_1 : 9;
        unsigned int acpu_hpm_type : 1;
        unsigned int l2cc_hpm_type : 1;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_PMCTRL_ACPUHPMCTRL_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpm_en_START (0)
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpm_en_END (6)
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpmx_en_START (8)
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpmx_en_END (14)
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpm_type_START (24)
#define SOC_PMCTRL_ACPUHPMCTRL_acpu_hpm_type_END (24)
#define SOC_PMCTRL_ACPUHPMCTRL_l2cc_hpm_type_START (25)
#define SOC_PMCTRL_ACPUHPMCTRL_l2cc_hpm_type_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_opc_vld : 7;
        unsigned int reserved_0 : 1;
        unsigned int acpu_hpmx_opc_vld : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_ACPUHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMOPCVALID_acpu_hpm_opc_vld_START (0)
#define SOC_PMCTRL_ACPUHPMOPCVALID_acpu_hpm_opc_vld_END (6)
#define SOC_PMCTRL_ACPUHPMOPCVALID_acpu_hpmx_opc_vld_START (8)
#define SOC_PMCTRL_ACPUHPMOPCVALID_acpu_hpmx_opc_vld_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu0_hpm_opc : 10;
        unsigned int acpu1_hpm_opc : 10;
        unsigned int acpu_scu_hpm_opc : 10;
        unsigned int reserved : 2;
    } reg;
} SOC_PMCTRL_ACPU01HPMOPC_UNION;
#endif
#define SOC_PMCTRL_ACPU01HPMOPC_acpu0_hpm_opc_START (0)
#define SOC_PMCTRL_ACPU01HPMOPC_acpu0_hpm_opc_END (9)
#define SOC_PMCTRL_ACPU01HPMOPC_acpu1_hpm_opc_START (10)
#define SOC_PMCTRL_ACPU01HPMOPC_acpu1_hpm_opc_END (19)
#define SOC_PMCTRL_ACPU01HPMOPC_acpu_scu_hpm_opc_START (20)
#define SOC_PMCTRL_ACPU01HPMOPC_acpu_scu_hpm_opc_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu2_hpm_opc : 10;
        unsigned int acpu3_hpm_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_ACPU23HPMOPC_UNION;
#endif
#define SOC_PMCTRL_ACPU23HPMOPC_acpu2_hpm_opc_START (0)
#define SOC_PMCTRL_ACPU23HPMOPC_acpu2_hpm_opc_END (9)
#define SOC_PMCTRL_ACPU23HPMOPC_acpu3_hpm_opc_START (10)
#define SOC_PMCTRL_ACPU23HPMOPC_acpu3_hpm_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_hpm0_opc : 10;
        unsigned int l2cc_hpm1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_L2CCHPMOPC_UNION;
#endif
#define SOC_PMCTRL_L2CCHPMOPC_l2cc_hpm0_opc_START (0)
#define SOC_PMCTRL_L2CCHPMOPC_l2cc_hpm0_opc_END (9)
#define SOC_PMCTRL_L2CCHPMOPC_l2cc_hpm1_opc_START (10)
#define SOC_PMCTRL_L2CCHPMOPC_l2cc_hpm1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu0_hpmx_opc : 10;
        unsigned int acpu1_hpmx_opc : 10;
        unsigned int acpu_scu_hpmx_opc : 10;
        unsigned int reserved : 2;
    } reg;
} SOC_PMCTRL_ACPU01HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu0_hpmx_opc_START (0)
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu0_hpmx_opc_END (9)
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu1_hpmx_opc_START (10)
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu1_hpmx_opc_END (19)
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu_scu_hpmx_opc_START (20)
#define SOC_PMCTRL_ACPU01HPMXOPC_acpu_scu_hpmx_opc_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu2_hpmx_opc : 10;
        unsigned int acpu3_hpmx_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_ACPU23HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_ACPU23HPMXOPC_acpu2_hpmx_opc_START (0)
#define SOC_PMCTRL_ACPU23HPMXOPC_acpu2_hpmx_opc_END (9)
#define SOC_PMCTRL_ACPU23HPMXOPC_acpu3_hpmx_opc_START (10)
#define SOC_PMCTRL_ACPU23HPMXOPC_acpu3_hpmx_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_hpmx0_opc : 10;
        unsigned int l2cc_hpmx1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_L2CCHPMXOPC_UNION;
#endif
#define SOC_PMCTRL_L2CCHPMXOPC_l2cc_hpmx0_opc_START (0)
#define SOC_PMCTRL_L2CCHPMXOPC_l2cc_hpmx0_opc_END (9)
#define SOC_PMCTRL_L2CCHPMXOPC_l2cc_hpmx1_opc_START (10)
#define SOC_PMCTRL_L2CCHPMXOPC_l2cc_hpmx1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu0_hpm_pc_avs : 10;
        unsigned int acpu1_hpm_pc_avs : 10;
        unsigned int acpu_scu_hpm_pc_avs : 10;
        unsigned int reserved : 2;
    } reg;
} SOC_PMCTRL_ACPU01HPMPC_UNION;
#endif
#define SOC_PMCTRL_ACPU01HPMPC_acpu0_hpm_pc_avs_START (0)
#define SOC_PMCTRL_ACPU01HPMPC_acpu0_hpm_pc_avs_END (9)
#define SOC_PMCTRL_ACPU01HPMPC_acpu1_hpm_pc_avs_START (10)
#define SOC_PMCTRL_ACPU01HPMPC_acpu1_hpm_pc_avs_END (19)
#define SOC_PMCTRL_ACPU01HPMPC_acpu_scu_hpm_pc_avs_START (20)
#define SOC_PMCTRL_ACPU01HPMPC_acpu_scu_hpm_pc_avs_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu2_hpm_pc_avs : 10;
        unsigned int acpu3_hpm_pc_avs : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_ACPU23HPMPC_UNION;
#endif
#define SOC_PMCTRL_ACPU23HPMPC_acpu2_hpm_pc_avs_START (0)
#define SOC_PMCTRL_ACPU23HPMPC_acpu2_hpm_pc_avs_END (9)
#define SOC_PMCTRL_ACPU23HPMPC_acpu3_hpm_pc_avs_START (10)
#define SOC_PMCTRL_ACPU23HPMPC_acpu3_hpm_pc_avs_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2cc_hpm0_pc_avs : 10;
        unsigned int l2cc_hpm1_pc_avs : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_L2CCHPMPC_UNION;
#endif
#define SOC_PMCTRL_L2CCHPMPC_l2cc_hpm0_pc_avs_START (0)
#define SOC_PMCTRL_L2CCHPMPC_l2cc_hpm0_pc_avs_END (9)
#define SOC_PMCTRL_L2CCHPMPC_l2cc_hpm1_pc_avs_START (10)
#define SOC_PMCTRL_L2CCHPMPC_l2cc_hpm1_pc_avs_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpmclk_bypass : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUHPMBYPASS_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMBYPASS_acpu_hpmclk_bypass_START (0)
#define SOC_PMCTRL_ACPUHPMBYPASS_acpu_hpmclk_bypass_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_up_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_ACPUPMUVOLUPTIME_UNION;
#endif
#define SOC_PMCTRL_ACPUPMUVOLUPTIME_acpu_vol_up_time_START (0)
#define SOC_PMCTRL_ACPUPMUVOLUPTIME_acpu_vol_up_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_dw_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_ACPUPMUVOLDNTIME_UNION;
#endif
#define SOC_PMCTRL_ACPUPMUVOLDNTIME_acpu_vol_dw_time_START (0)
#define SOC_PMCTRL_ACPUPMUVOLDNTIME_acpu_vol_dw_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_addr : 10;
        unsigned int reserved_0 : 6;
        unsigned int acpu_force_pmussi_en : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_PMCTRL_ACPUVOLPMUADDR_UNION;
#endif
#define SOC_PMCTRL_ACPUVOLPMUADDR_acpu_vol_addr_START (0)
#define SOC_PMCTRL_ACPUVOLPMUADDR_acpu_vol_addr_END (9)
#define SOC_PMCTRL_ACPUVOLPMUADDR_acpu_force_pmussi_en_START (16)
#define SOC_PMCTRL_ACPUVOLPMUADDR_acpu_force_pmussi_en_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_up_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUVOLUPSTEP_UNION;
#endif
#define SOC_PMCTRL_ACPUVOLUPSTEP_acpu_vol_up_step_START (0)
#define SOC_PMCTRL_ACPUVOLUPSTEP_acpu_vol_up_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_vol_dn_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUVOLDNSTEP_UNION;
#endif
#define SOC_PMCTRL_ACPUVOLDNSTEP_acpu_vol_dn_step_START (0)
#define SOC_PMCTRL_ACPUVOLDNSTEP_acpu_vol_dn_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_dft_vol : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUDFTVOL_UNION;
#endif
#define SOC_PMCTRL_ACPUDFTVOL_acpu_dft_vol_START (0)
#define SOC_PMCTRL_ACPUDFTVOL_acpu_dft_vol_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_dest_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int acpu_vol_using : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_ACPUDESTVOL_UNION;
#endif
#define SOC_PMCTRL_ACPUDESTVOL_acpu_dest_vol_START (0)
#define SOC_PMCTRL_ACPUDESTVOL_acpu_dest_vol_END (6)
#define SOC_PMCTRL_ACPUDESTVOL_acpu_vol_using_START (8)
#define SOC_PMCTRL_ACPUDESTVOL_acpu_vol_using_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_en : 4;
        unsigned int reserved_0 : 4;
        unsigned int g3d_hpmx_en : 4;
        unsigned int reserved_1 : 12;
        unsigned int g3d_hpm_type : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_PMCTRL_G3DHPMCTRL_UNION;
#endif
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpm_en_START (0)
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpm_en_END (3)
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpmx_en_START (8)
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpmx_en_END (11)
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpm_type_START (24)
#define SOC_PMCTRL_G3DHPMCTRL_g3d_hpm_type_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_opc_vld : 4;
        unsigned int reserved_0 : 4;
        unsigned int g3d_hpmx_opc_vld : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_PMCTRL_G3DHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPCVALID_g3d_hpm_opc_vld_START (0)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3d_hpm_opc_vld_END (3)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3d_hpmx_opc_vld_START (8)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3d_hpmx_opc_vld_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm0_opc : 10;
        unsigned int g3d_hpm1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPM01OPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPM01OPC_g3d_hpm0_opc_START (0)
#define SOC_PMCTRL_G3DHPM01OPC_g3d_hpm0_opc_END (9)
#define SOC_PMCTRL_G3DHPM01OPC_g3d_hpm1_opc_START (10)
#define SOC_PMCTRL_G3DHPM01OPC_g3d_hpm1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm2_opc : 10;
        unsigned int g3d_hpm3_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPM23OPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPM23OPC_g3d_hpm2_opc_START (0)
#define SOC_PMCTRL_G3DHPM23OPC_g3d_hpm2_opc_END (9)
#define SOC_PMCTRL_G3DHPM23OPC_g3d_hpm3_opc_START (10)
#define SOC_PMCTRL_G3DHPM23OPC_g3d_hpm3_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpmx0_opc : 10;
        unsigned int g3d_hpmx1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPMX01OPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMX01OPC_g3d_hpmx0_opc_START (0)
#define SOC_PMCTRL_G3DHPMX01OPC_g3d_hpmx0_opc_END (9)
#define SOC_PMCTRL_G3DHPMX01OPC_g3d_hpmx1_opc_START (10)
#define SOC_PMCTRL_G3DHPMX01OPC_g3d_hpmx1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpmx2_opc : 10;
        unsigned int g3d_hpmx3_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPMX23OPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMX23OPC_g3d_hpmx2_opc_START (0)
#define SOC_PMCTRL_G3DHPMX23OPC_g3d_hpmx2_opc_END (9)
#define SOC_PMCTRL_G3DHPMX23OPC_g3d_hpmx3_opc_START (10)
#define SOC_PMCTRL_G3DHPMX23OPC_g3d_hpmx3_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm0_pc_avs : 10;
        unsigned int g3d_hpm1_pc_avs : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPM01PC_UNION;
#endif
#define SOC_PMCTRL_G3DHPM01PC_g3d_hpm0_pc_avs_START (0)
#define SOC_PMCTRL_G3DHPM01PC_g3d_hpm0_pc_avs_END (9)
#define SOC_PMCTRL_G3DHPM01PC_g3d_hpm1_pc_avs_START (10)
#define SOC_PMCTRL_G3DHPM01PC_g3d_hpm1_pc_avs_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm2_pc_avs : 10;
        unsigned int g3d_hpm3_pc_avs : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DHPM23PC_UNION;
#endif
#define SOC_PMCTRL_G3DHPM23PC_g3d_hpm2_pc_avs_START (0)
#define SOC_PMCTRL_G3DHPM23PC_g3d_hpm2_pc_avs_END (9)
#define SOC_PMCTRL_G3DHPM23PC_g3d_hpm3_pc_avs_START (10)
#define SOC_PMCTRL_G3DHPM23PC_g3d_hpm3_pc_avs_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpmclk_bypass : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_PMCTRL_G3DHPMBYPASS_UNION;
#endif
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpmclk_bypass_START (0)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpmclk_bypass_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_up_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DPMUVOLUPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPMUVOLUPTIME_g3d_vol_up_time_START (0)
#define SOC_PMCTRL_G3DPMUVOLUPTIME_g3d_vol_up_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_dn_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_G3DPMUVOLDNTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPMUVOLDNTIME_g3d_vol_dn_time_START (0)
#define SOC_PMCTRL_G3DPMUVOLDNTIME_g3d_vol_dn_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_addr : 10;
        unsigned int reserved_0 : 6;
        unsigned int g3d_force_pmussi_en : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_PMCTRL_G3DVOLPMUADDR_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPMUADDR_g3d_vol_addr_START (0)
#define SOC_PMCTRL_G3DVOLPMUADDR_g3d_vol_addr_END (9)
#define SOC_PMCTRL_G3DVOLPMUADDR_g3d_force_pmussi_en_START (16)
#define SOC_PMCTRL_G3DVOLPMUADDR_g3d_force_pmussi_en_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_up_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_G3DVOLUPSTEP_UNION;
#endif
#define SOC_PMCTRL_G3DVOLUPSTEP_g3d_vol_up_step_START (0)
#define SOC_PMCTRL_G3DVOLUPSTEP_g3d_vol_up_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_vol_dn_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_G3DVOLDNSTEP_UNION;
#endif
#define SOC_PMCTRL_G3DVOLDNSTEP_g3d_vol_dn_step_START (0)
#define SOC_PMCTRL_G3DVOLDNSTEP_g3d_vol_dn_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_dft_vol : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_G3DDFTVOL_UNION;
#endif
#define SOC_PMCTRL_G3DDFTVOL_g3d_dft_vol_START (0)
#define SOC_PMCTRL_G3DDFTVOL_g3d_dft_vol_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_dest_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int g3d_vol_using : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_G3DDESTVOL_UNION;
#endif
#define SOC_PMCTRL_G3DDESTVOL_g3d_dest_vol_START (0)
#define SOC_PMCTRL_G3DDESTVOL_g3d_dest_vol_END (6)
#define SOC_PMCTRL_G3DDESTVOL_g3d_vol_using_START (8)
#define SOC_PMCTRL_G3DDESTVOL_g3d_vol_using_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_raw : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTRAW_UNION;
#endif
#define SOC_PMCTRL_PMCINTRAW_int_raw_START (0)
#define SOC_PMCTRL_PMCINTRAW_int_raw_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_clr : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTCLR_UNION;
#endif
#define SOC_PMCTRL_PMCINTCLR_int_clr_START (0)
#define SOC_PMCTRL_PMCINTCLR_int_clr_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mcu_en : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTENMCU_UNION;
#endif
#define SOC_PMCTRL_PMCINTENMCU_int_mcu_en_START (0)
#define SOC_PMCTRL_PMCINTENMCU_int_mcu_en_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mcu_stat : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTSTATMCU_UNION;
#endif
#define SOC_PMCTRL_PMCINTSTATMCU_int_mcu_stat_START (0)
#define SOC_PMCTRL_PMCINTSTATMCU_int_mcu_stat_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_acpu_en : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTENACPU_UNION;
#endif
#define SOC_PMCTRL_PMCINTENACPU_int_acpu_en_START (0)
#define SOC_PMCTRL_PMCINTENACPU_int_acpu_en_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_acpu_stat : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTSTATACPU_UNION;
#endif
#define SOC_PMCTRL_PMCINTSTATACPU_int_acpu_stat_START (0)
#define SOC_PMCTRL_PMCINTSTATACPU_int_acpu_stat_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mcpu_en : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTENMCPU_UNION;
#endif
#define SOC_PMCTRL_PMCINTENMCPU_int_mcpu_en_START (0)
#define SOC_PMCTRL_PMCINTENMCPU_int_mcpu_en_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int int_mcpu_stat : 23;
        unsigned int reserved : 9;
    } reg;
} SOC_PMCTRL_PMCINTSTATMCPU_UNION;
#endif
#define SOC_PMCTRL_PMCINTSTATMCPU_int_mcpu_stat_START (0)
#define SOC_PMCTRL_PMCINTSTATMCPU_int_mcpu_stat_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_dvfs_stat : 3;
        unsigned int reserved_0 : 1;
        unsigned int g3d_dvfs_stat : 3;
        unsigned int reserved_1 : 1;
        unsigned int acpu_avs_stat : 3;
        unsigned int reserved_2 : 1;
        unsigned int l2cc_avs_stat : 3;
        unsigned int reserved_3 : 1;
        unsigned int g3d_avs_stat : 3;
        unsigned int reserved_4 : 1;
        unsigned int ddrc_avs_stat : 3;
        unsigned int reserved_5 : 1;
        unsigned int ddr_dvfs_stat : 3;
        unsigned int reserved_6 : 1;
        unsigned int ddr_fs_stat : 3;
        unsigned int reserved_7 : 1;
    } reg;
} SOC_PMCTRL_PMCSTATUS_UNION;
#endif
#define SOC_PMCTRL_PMCSTATUS_acpu_dvfs_stat_START (0)
#define SOC_PMCTRL_PMCSTATUS_acpu_dvfs_stat_END (2)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_START (4)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_END (6)
#define SOC_PMCTRL_PMCSTATUS_acpu_avs_stat_START (8)
#define SOC_PMCTRL_PMCSTATUS_acpu_avs_stat_END (10)
#define SOC_PMCTRL_PMCSTATUS_l2cc_avs_stat_START (12)
#define SOC_PMCTRL_PMCSTATUS_l2cc_avs_stat_END (14)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_START (16)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_END (18)
#define SOC_PMCTRL_PMCSTATUS_ddrc_avs_stat_START (20)
#define SOC_PMCTRL_PMCSTATUS_ddrc_avs_stat_END (22)
#define SOC_PMCTRL_PMCSTATUS_ddr_dvfs_stat_START (24)
#define SOC_PMCTRL_PMCSTATUS_ddr_dvfs_stat_END (26)
#define SOC_PMCTRL_PMCSTATUS_ddr_fs_stat_START (28)
#define SOC_PMCTRL_PMCSTATUS_ddr_fs_stat_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsppll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_DSPPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_DSPPLLFRAC_dsppll_frac_START (0)
#define SOC_PMCTRL_DSPPLLFRAC_dsppll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dsppll_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_DSPPLLSSC_UNION;
#endif
#define SOC_PMCTRL_DSPPLLSSC_dsppll_ssc_START (0)
#define SOC_PMCTRL_DSPPLLSSC_dsppll_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrpll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_DDRPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_DDRPLLFRAC_ddrpll_frac_START (0)
#define SOC_PMCTRL_DDRPLLFRAC_ddrpll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrpll_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_DDRPLLSSC_UNION;
#endif
#define SOC_PMCTRL_DDRPLLSSC_ddrpll_ssc_START (0)
#define SOC_PMCTRL_DDRPLLSSC_ddrpll_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll0_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_ACPUPLL0FRAC_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL0FRAC_acpupll0_frac_START (0)
#define SOC_PMCTRL_ACPUPLL0FRAC_acpupll0_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll0_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_ACPUPLL0SSC_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL0SSC_acpupll0_ssc_START (0)
#define SOC_PMCTRL_ACPUPLL0SSC_acpupll0_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll1_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_ACPUPLL1FRAC_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL1FRAC_acpupll1_frac_START (0)
#define SOC_PMCTRL_ACPUPLL1FRAC_acpupll1_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpupll1_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_ACPUPLL1SSC_UNION;
#endif
#define SOC_PMCTRL_ACPUPLL1SSC_acpupll1_ssc_START (0)
#define SOC_PMCTRL_ACPUPLL1SSC_acpupll1_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll0_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_G3DPLL0FRAC_UNION;
#endif
#define SOC_PMCTRL_G3DPLL0FRAC_g3dpll0_frac_START (0)
#define SOC_PMCTRL_G3DPLL0FRAC_g3dpll0_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll0_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_G3DPLL0SSC_UNION;
#endif
#define SOC_PMCTRL_G3DPLL0SSC_g3dpll0_ssc_START (0)
#define SOC_PMCTRL_G3DPLL0SSC_g3dpll0_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll1_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_G3DPLL1FRAC_UNION;
#endif
#define SOC_PMCTRL_G3DPLL1FRAC_g3dpll1_frac_START (0)
#define SOC_PMCTRL_G3DPLL1FRAC_g3dpll1_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3dpll1_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_G3DPLL1SSC_UNION;
#endif
#define SOC_PMCTRL_G3DPLL1SSC_g3dpll1_ssc_START (0)
#define SOC_PMCTRL_G3DPLL1SSC_g3dpll1_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcpupll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_MCPUPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_MCPUPLLFRAC_mcpupll_frac_START (0)
#define SOC_PMCTRL_MCPUPLLFRAC_mcpupll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mcpupll_ssc : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_MCPUPLLSSC_UNION;
#endif
#define SOC_PMCTRL_MCPUPLLSSC_mcpupll_ssc_START (0)
#define SOC_PMCTRL_MCPUPLLSSC_mcpupll_ssc_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_PERIPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_PERIPLLFRAC_peripll_frac_START (0)
#define SOC_PMCTRL_PERIPLLFRAC_peripll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hdmipll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_HDMIPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_HDMIPLLFRAC_hdmipll_frac_START (0)
#define SOC_PMCTRL_HDMIPLLFRAC_hdmipll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bbppll_frac : 29;
        unsigned int reserved : 3;
    } reg;
} SOC_PMCTRL_BBPPLLFRAC_UNION;
#endif
#define SOC_PMCTRL_BBPPLLFRAC_bbppll_frac_START (0)
#define SOC_PMCTRL_BBPPLLFRAC_bbppll_frac_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr_pllsw_cfg : 2;
        unsigned int reserved_0 : 6;
        unsigned int ddr_pllsw_stat : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_PMCTRL_DDRCLKSEL_UNION;
#endif
#define SOC_PMCTRL_DDRCLKSEL_ddr_pllsw_cfg_START (0)
#define SOC_PMCTRL_DDRCLKSEL_ddr_pllsw_cfg_END (1)
#define SOC_PMCTRL_DDRCLKSEL_ddr_pllsw_stat_START (8)
#define SOC_PMCTRL_DDRCLKSEL_ddr_pllsw_stat_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrio_clk_div_cfg : 4;
        unsigned int reserved_0 : 2;
        unsigned int ddrphy_clk_div_cfg : 1;
        unsigned int reserved_1 : 1;
        unsigned int ddrc_clk_div_cfg : 1;
        unsigned int reserved_2 : 1;
        unsigned int ddrbus_clk_div_cfg : 1;
        unsigned int reserved_3 : 1;
        unsigned int ddrapb_clk_div_cfg : 3;
        unsigned int reserved_4 : 1;
        unsigned int ddrio_clk_div_stat : 4;
        unsigned int reserved_5 : 2;
        unsigned int ddrphy_clk_div_stat : 1;
        unsigned int reserved_6 : 1;
        unsigned int ddrc_clk_div_stat : 1;
        unsigned int reserved_7 : 1;
        unsigned int ddrbus_clk_div_stat : 1;
        unsigned int reserved_8 : 1;
        unsigned int ddrapb_clk_div_stat : 3;
        unsigned int reserved_9 : 1;
    } reg;
} SOC_PMCTRL_DDRCLKDIV_UNION;
#endif
#define SOC_PMCTRL_DDRCLKDIV_ddrio_clk_div_cfg_START (0)
#define SOC_PMCTRL_DDRCLKDIV_ddrio_clk_div_cfg_END (3)
#define SOC_PMCTRL_DDRCLKDIV_ddrphy_clk_div_cfg_START (6)
#define SOC_PMCTRL_DDRCLKDIV_ddrphy_clk_div_cfg_END (6)
#define SOC_PMCTRL_DDRCLKDIV_ddrc_clk_div_cfg_START (8)
#define SOC_PMCTRL_DDRCLKDIV_ddrc_clk_div_cfg_END (8)
#define SOC_PMCTRL_DDRCLKDIV_ddrbus_clk_div_cfg_START (10)
#define SOC_PMCTRL_DDRCLKDIV_ddrbus_clk_div_cfg_END (10)
#define SOC_PMCTRL_DDRCLKDIV_ddrapb_clk_div_cfg_START (12)
#define SOC_PMCTRL_DDRCLKDIV_ddrapb_clk_div_cfg_END (14)
#define SOC_PMCTRL_DDRCLKDIV_ddrio_clk_div_stat_START (16)
#define SOC_PMCTRL_DDRCLKDIV_ddrio_clk_div_stat_END (19)
#define SOC_PMCTRL_DDRCLKDIV_ddrphy_clk_div_stat_START (22)
#define SOC_PMCTRL_DDRCLKDIV_ddrphy_clk_div_stat_END (22)
#define SOC_PMCTRL_DDRCLKDIV_ddrc_clk_div_stat_START (24)
#define SOC_PMCTRL_DDRCLKDIV_ddrc_clk_div_stat_END (24)
#define SOC_PMCTRL_DDRCLKDIV_ddrbus_clk_div_stat_START (26)
#define SOC_PMCTRL_DDRCLKDIV_ddrbus_clk_div_stat_END (26)
#define SOC_PMCTRL_DDRCLKDIV_ddrapb_clk_div_stat_START (28)
#define SOC_PMCTRL_DDRCLKDIV_ddrapb_clk_div_stat_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_csysreq : 1;
        unsigned int reserved_0 : 3;
        unsigned int ddrc_csysreq_stat : 1;
        unsigned int ddrc_csysack : 1;
        unsigned int reserved_1 : 26;
    } reg;
} SOC_PMCTRL_DDRLPCTRL_UNION;
#endif
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_START (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_END (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_stat_START (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_stat_END (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysack_START (5)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysack_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrpll_on_idle : 1;
        unsigned int reserved_0 : 3;
        unsigned int ddr_dvfs_pwctrl_en : 1;
        unsigned int reserved_1 : 3;
        unsigned int ddr_dvfs_ko_avs_dis : 1;
        unsigned int reserved_2 : 23;
    } reg;
} SOC_PMCTRL_DDRCCLKOFFCFG_UNION;
#endif
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddrpll_on_idle_START (0)
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddrpll_on_idle_END (0)
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddr_dvfs_pwctrl_en_START (4)
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddr_dvfs_pwctrl_en_END (4)
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddr_dvfs_ko_avs_dis_START (8)
#define SOC_PMCTRL_DDRCCLKOFFCFG_ddr_dvfs_ko_avs_dis_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_dvfs_start : 1;
        unsigned int ddrc_profile_updn : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCDVFSEN_UNION;
#endif
#define SOC_PMCTRL_DDRCDVFSEN_ddrc_dvfs_start_START (0)
#define SOC_PMCTRL_DDRCDVFSEN_ddrc_dvfs_start_END (0)
#define SOC_PMCTRL_DDRCDVFSEN_ddrc_profile_updn_START (1)
#define SOC_PMCTRL_DDRCDVFSEN_ddrc_profile_updn_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr_fs_start : 1;
        unsigned int reserved_0 : 3;
        unsigned int ddr_fs_done : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_PMCTRL_DDRCFSEN_UNION;
#endif
#define SOC_PMCTRL_DDRCFSEN_ddr_fs_start_START (0)
#define SOC_PMCTRL_DDRCFSEN_ddr_fs_start_END (0)
#define SOC_PMCTRL_DDRCFSEN_ddr_fs_done_START (4)
#define SOC_PMCTRL_DDRCFSEN_ddr_fs_done_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrio_clk_div_prof : 4;
        unsigned int reserved_0 : 2;
        unsigned int ddrphy_clk_div_prof : 1;
        unsigned int reserved_1 : 1;
        unsigned int ddrc_clk_div_prof : 1;
        unsigned int reserved_2 : 1;
        unsigned int ddrbus_clk_div_prof : 1;
        unsigned int reserved_3 : 1;
        unsigned int ddrapb_clk_div_prof : 3;
        unsigned int reserved_4 : 1;
        unsigned int ddr_pllsw_prof : 2;
        unsigned int reserved_5 : 14;
    } reg;
} SOC_PMCTRL_DDRCLKPROFILE_UNION;
#endif
#define SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_START (0)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrio_clk_div_prof_END (3)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrphy_clk_div_prof_START (6)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrphy_clk_div_prof_END (6)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_START (8)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrc_clk_div_prof_END (8)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_START (10)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrbus_clk_div_prof_END (10)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrapb_clk_div_prof_START (12)
#define SOC_PMCTRL_DDRCLKPROFILE_ddrapb_clk_div_prof_END (14)
#define SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_START (16)
#define SOC_PMCTRL_DDRCLKPROFILE_ddr_pllsw_prof_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_idx_prof : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_DDRCVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_DDRCVOLPROFILE_ddrc_vol_idx_prof_START (0)
#define SOC_PMCTRL_DDRCVOLPROFILE_ddrc_vol_idx_prof_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddr_clkdiv_time : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_PMCTRL_DDRDIVTIMEOUT_UNION;
#endif
#define SOC_PMCTRL_DDRDIVTIMEOUT_ddr_clkdiv_time_START (0)
#define SOC_PMCTRL_DDRDIVTIMEOUT_ddr_clkdiv_time_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avspara_update : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PMCTRL_DDRCAVSPARAUDP_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARAUDP_ddrc_avspara_update_START (0)
#define SOC_PMCTRL_DDRCAVSPARAUDP_ddrc_avspara_update_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_clk_div : 6;
        unsigned int reserved_0 : 10;
        unsigned int ddrc_avs_opc_mod : 2;
        unsigned int reserved_1 : 2;
        unsigned int ddrc_avs_hpm_sel : 3;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_hpm_clk_div_START (0)
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_hpm_clk_div_END (5)
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_avs_opc_mod_START (16)
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_avs_opc_mod_END (17)
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_avs_hpm_sel_START (20)
#define SOC_PMCTRL_DDRCAVSPARA0_ddrc_avs_hpm_sel_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_opc_offset : 10;
        unsigned int reserved_0 : 2;
        unsigned int ddrc_avs_rcc : 5;
        unsigned int reserved_1 : 3;
        unsigned int ddrc_avs_irgap : 5;
        unsigned int reserved_2 : 3;
        unsigned int ddrc_avs_opc_shift : 3;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_opc_offset_START (0)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_opc_offset_END (9)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_rcc_START (12)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_rcc_END (16)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_irgap_START (20)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_irgap_END (24)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_opc_shift_START (28)
#define SOC_PMCTRL_DDRCAVSPARA1_ddrc_avs_opc_shift_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_vol_up_gain1 : 4;
        unsigned int ddrc_avs_vol_up_gain2 : 4;
        unsigned int ddrc_avs_vol_up_gain3 : 4;
        unsigned int ddrc_avs_vol_up_gain4 : 4;
        unsigned int ddrc_avs_vol_up_gain5 : 4;
        unsigned int ddrc_avs_vol_up_gain6 : 4;
        unsigned int ddrc_avs_vol_up_gain7 : 4;
        unsigned int ddrc_avs_vol_up_gain8 : 4;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain1_START (0)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain1_END (3)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain2_START (4)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain2_END (7)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain3_START (8)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain3_END (11)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain4_START (12)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain4_END (15)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain5_START (16)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain5_END (19)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain6_START (20)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain6_END (23)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain7_START (24)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain7_END (27)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain8_START (28)
#define SOC_PMCTRL_DDRCAVSPARA2_ddrc_avs_vol_up_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_vol_up_gain9 : 4;
        unsigned int ddrc_avs_vol_up_gain10 : 4;
        unsigned int ddrc_avs_vol_up_gain11 : 4;
        unsigned int ddrc_avs_vol_up_gain12 : 4;
        unsigned int ddrc_avs_vol_up_gain13 : 4;
        unsigned int ddrc_avs_vol_up_gain14 : 4;
        unsigned int ddrc_avs_vol_up_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain9_START (0)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain9_END (3)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain10_START (4)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain10_END (7)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain11_START (8)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain11_END (11)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain12_START (12)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain12_END (15)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain13_START (16)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain13_END (19)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain14_START (20)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain14_END (23)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain15_START (24)
#define SOC_PMCTRL_DDRCAVSPARA3_ddrc_avs_vol_up_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_vol_dn_gain1 : 4;
        unsigned int ddrc_avs_vol_dn_gain2 : 4;
        unsigned int ddrc_avs_vol_dn_gain3 : 4;
        unsigned int ddrc_avs_vol_dn_gain4 : 4;
        unsigned int ddrc_avs_vol_dn_gain5 : 4;
        unsigned int ddrc_avs_vol_dn_gain6 : 4;
        unsigned int ddrc_avs_vol_dn_gain7 : 4;
        unsigned int ddrc_avs_vol_dn_gain8 : 4;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain1_START (0)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain1_END (3)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain2_START (4)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain2_END (7)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain3_START (8)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain3_END (11)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain4_START (12)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain4_END (15)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain5_START (16)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain5_END (19)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain6_START (20)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain6_END (23)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain7_START (24)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain7_END (27)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain8_START (28)
#define SOC_PMCTRL_DDRCAVSPARA4_ddrc_avs_vol_dn_gain8_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_vol_dn_gain9 : 4;
        unsigned int ddrc_avs_vol_dn_gain10 : 4;
        unsigned int ddrc_avs_vol_dn_gain11 : 4;
        unsigned int ddrc_avs_vol_dn_gain12 : 4;
        unsigned int ddrc_avs_vol_dn_gain13 : 4;
        unsigned int ddrc_avs_vol_dn_gain14 : 4;
        unsigned int ddrc_avs_vol_dn_gain15 : 7;
        unsigned int reserved : 1;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain9_START (0)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain9_END (3)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain10_START (4)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain10_END (7)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain11_START (8)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain11_END (11)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain12_START (12)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain12_END (15)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain13_START (16)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain13_END (19)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain14_START (20)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain14_END (23)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain15_START (24)
#define SOC_PMCTRL_DDRCAVSPARA5_ddrc_avs_vol_dn_gain15_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_max_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int ddrc_avs_min_vol : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA6_ddrc_avs_max_vol_START (0)
#define SOC_PMCTRL_DDRCAVSPARA6_ddrc_avs_max_vol_END (6)
#define SOC_PMCTRL_DDRCAVSPARA6_ddrc_avs_min_vol_START (8)
#define SOC_PMCTRL_DDRCAVSPARA6_ddrc_avs_min_vol_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_sample_num : 22;
        unsigned int reserved_0 : 2;
        unsigned int ddrc_avs_sample_shift : 5;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_PMCTRL_DDRCAVSPARA7_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPARA7_ddrc_avs_sample_num_START (0)
#define SOC_PMCTRL_DDRCAVSPARA7_ddrc_avs_sample_num_END (21)
#define SOC_PMCTRL_DDRCAVSPARA7_ddrc_avs_sample_shift_START (24)
#define SOC_PMCTRL_DDRCAVSPARA7_ddrc_avs_sample_shift_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_en : 1;
        unsigned int ddrc_avs_pwctrl_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCAVSEN_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSEN_ddrc_avs_en_START (0)
#define SOC_PMCTRL_DDRCAVSEN_ddrc_avs_en_END (0)
#define SOC_PMCTRL_DDRCAVSEN_ddrc_avs_pwctrl_en_START (1)
#define SOC_PMCTRL_DDRCAVSEN_ddrc_avs_pwctrl_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_period : 32;
    } reg;
} SOC_PMCTRL_DDRCAVSPERIOD_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSPERIOD_ddrc_avs_period_START (0)
#define SOC_PMCTRL_DDRCAVSPERIOD_ddrc_avs_period_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_avs_round : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_PMCTRL_DDRCAVSRUNROUND_UNION;
#endif
#define SOC_PMCTRL_DDRCAVSRUNROUND_ddrc_avs_round_START (0)
#define SOC_PMCTRL_DDRCAVSRUNROUND_ddrc_avs_round_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_en : 2;
        unsigned int reserved_0 : 6;
        unsigned int ddrc_hpmx_en : 2;
        unsigned int reserved_1 : 14;
        unsigned int ddrc_hpm_type : 1;
        unsigned int reserved_2 : 7;
    } reg;
} SOC_PMCTRL_DDRCHPMCTRL_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpm_en_START (0)
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpm_en_END (1)
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpmx_en_START (8)
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpmx_en_END (9)
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpm_type_START (24)
#define SOC_PMCTRL_DDRCHPMCTRL_ddrc_hpm_type_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_opc_vld : 2;
        unsigned int reserved_0 : 6;
        unsigned int ddrc_hpmx_opc_vld : 2;
        unsigned int reserved_1 : 22;
    } reg;
} SOC_PMCTRL_DDRCHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMOPCVALID_ddrc_hpm_opc_vld_START (0)
#define SOC_PMCTRL_DDRCHPMOPCVALID_ddrc_hpm_opc_vld_END (1)
#define SOC_PMCTRL_DDRCHPMOPCVALID_ddrc_hpmx_opc_vld_START (8)
#define SOC_PMCTRL_DDRCHPMOPCVALID_ddrc_hpmx_opc_vld_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm0_opc : 10;
        unsigned int ddrc_hpm1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_DDRCHPM01OPC_UNION;
#endif
#define SOC_PMCTRL_DDRCHPM01OPC_ddrc_hpm0_opc_START (0)
#define SOC_PMCTRL_DDRCHPM01OPC_ddrc_hpm0_opc_END (9)
#define SOC_PMCTRL_DDRCHPM01OPC_ddrc_hpm1_opc_START (10)
#define SOC_PMCTRL_DDRCHPM01OPC_ddrc_hpm1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpmx0_opc : 10;
        unsigned int ddrc_hpmx1_opc : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_DDRCHPMX01OPC_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMX01OPC_ddrc_hpmx0_opc_START (0)
#define SOC_PMCTRL_DDRCHPMX01OPC_ddrc_hpmx0_opc_END (9)
#define SOC_PMCTRL_DDRCHPMX01OPC_ddrc_hpmx1_opc_START (10)
#define SOC_PMCTRL_DDRCHPMX01OPC_ddrc_hpmx1_opc_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm0_pc_avs : 10;
        unsigned int ddrc_hpm1_pc_avs : 10;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_DDRCHPM01PC_UNION;
#endif
#define SOC_PMCTRL_DDRCHPM01PC_ddrc_hpm0_pc_avs_START (0)
#define SOC_PMCTRL_DDRCHPM01PC_ddrc_hpm0_pc_avs_END (9)
#define SOC_PMCTRL_DDRCHPM01PC_ddrc_hpm1_pc_avs_START (10)
#define SOC_PMCTRL_DDRCHPM01PC_ddrc_hpm1_pc_avs_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpmclk_bypass : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCHPMBYPASS_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMBYPASS_ddrc_hpmclk_bypass_START (0)
#define SOC_PMCTRL_DDRCHPMBYPASS_ddrc_hpmclk_bypass_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_up_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_DDRCPMUVOLUPTIME_UNION;
#endif
#define SOC_PMCTRL_DDRCPMUVOLUPTIME_ddrc_vol_up_time_START (0)
#define SOC_PMCTRL_DDRCPMUVOLUPTIME_ddrc_vol_up_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_dn_time : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_PMCTRL_DDRCPMUVOLDNTIME_UNION;
#endif
#define SOC_PMCTRL_DDRCPMUVOLDNTIME_ddrc_vol_dn_time_START (0)
#define SOC_PMCTRL_DDRCPMUVOLDNTIME_ddrc_vol_dn_time_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_addr : 10;
        unsigned int reserved_0 : 6;
        unsigned int ddr_force_pmussi_en : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_PMCTRL_DDRCVOLPMUADDR_UNION;
#endif
#define SOC_PMCTRL_DDRCVOLPMUADDR_ddrc_vol_addr_START (0)
#define SOC_PMCTRL_DDRCVOLPMUADDR_ddrc_vol_addr_END (9)
#define SOC_PMCTRL_DDRCVOLPMUADDR_ddr_force_pmussi_en_START (16)
#define SOC_PMCTRL_DDRCVOLPMUADDR_ddr_force_pmussi_en_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_up_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_DDRCVOLUPSTEP_UNION;
#endif
#define SOC_PMCTRL_DDRCVOLUPSTEP_ddrc_vol_up_step_START (0)
#define SOC_PMCTRL_DDRCVOLUPSTEP_ddrc_vol_up_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_vol_dn_step : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_DDRCVOLDNSTEP_UNION;
#endif
#define SOC_PMCTRL_DDRCVOLDNSTEP_ddrc_vol_dn_step_START (0)
#define SOC_PMCTRL_DDRCVOLDNSTEP_ddrc_vol_dn_step_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_dft_vol : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_DDRCDFTVOL_UNION;
#endif
#define SOC_PMCTRL_DDRCDFTVOL_ddrc_dft_vol_START (0)
#define SOC_PMCTRL_DDRCDFTVOL_ddrc_dft_vol_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_dest_vol : 7;
        unsigned int reserved_0 : 1;
        unsigned int ddrc_vol_using : 7;
        unsigned int reserved_1 : 17;
    } reg;
} SOC_PMCTRL_DDRCDESTVOL_UNION;
#endif
#define SOC_PMCTRL_DDRCDESTVOL_ddrc_dest_vol_START (0)
#define SOC_PMCTRL_DDRCDESTVOL_ddrc_dest_vol_END (6)
#define SOC_PMCTRL_DDRCDESTVOL_ddrc_vol_using_START (8)
#define SOC_PMCTRL_DDRCDESTVOL_ddrc_vol_using_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_mask_en : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUHPMMASKEN_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMMASKEN_acpu_hpm_mask_en_START (0)
#define SOC_PMCTRL_ACPUHPMMASKEN_acpu_hpm_mask_en_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_mask_dis : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUHPMMASKDIS_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMMASKDIS_acpu_hpm_mask_dis_START (0)
#define SOC_PMCTRL_ACPUHPMMASKDIS_acpu_hpm_mask_dis_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int acpu_hpm_mask : 7;
        unsigned int reserved : 25;
    } reg;
} SOC_PMCTRL_ACPUHPMMASKSTAT_UNION;
#endif
#define SOC_PMCTRL_ACPUHPMMASKSTAT_acpu_hpm_mask_START (0)
#define SOC_PMCTRL_ACPUHPMMASKSTAT_acpu_hpm_mask_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_mask_en : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_PMCTRL_G3DHPMMASKEN_UNION;
#endif
#define SOC_PMCTRL_G3DHPMMASKEN_g3d_hpm_mask_en_START (0)
#define SOC_PMCTRL_G3DHPMMASKEN_g3d_hpm_mask_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_mask_dis : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_PMCTRL_G3DHPMMASKDIS_UNION;
#endif
#define SOC_PMCTRL_G3DHPMMASKDIS_g3d_hpm_mask_dis_START (0)
#define SOC_PMCTRL_G3DHPMMASKDIS_g3d_hpm_mask_dis_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g3d_hpm_mask : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_PMCTRL_G3DHPMMASKSTAT_UNION;
#endif
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3d_hpm_mask_START (0)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3d_hpm_mask_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_mask_en : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCHPMMASKEN_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMMASKEN_ddrc_hpm_mask_en_START (0)
#define SOC_PMCTRL_DDRCHPMMASKEN_ddrc_hpm_mask_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_mask_dis : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCHPMMASKDIS_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMMASKDIS_ddrc_hpm_mask_dis_START (0)
#define SOC_PMCTRL_DDRCHPMMASKDIS_ddrc_hpm_mask_dis_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ddrc_hpm_mask : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_PMCTRL_DDRCHPMMASKSTAT_UNION;
#endif
#define SOC_PMCTRL_DDRCHPMMASKSTAT_ddrc_hpm_mask_START (0)
#define SOC_PMCTRL_DDRCHPMMASKSTAT_ddrc_hpm_mask_END (1)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

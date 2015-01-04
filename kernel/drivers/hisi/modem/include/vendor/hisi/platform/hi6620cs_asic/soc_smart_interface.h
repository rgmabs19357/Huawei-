#ifndef __SOC_SMART_INTERFACE_H__
#define __SOC_SMART_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SMART_STATUS1_ADDR(base) ((base) + (0x001))
#define SOC_SMART_STATUS2_ADDR(base) ((base) + (0x002))
#define SOC_SMART_IRQ1_ADDR(base) ((base) + (0x003))
#define SOC_SMART_IRQ2_ADDR(base) ((base) + (0x004))
#define SOC_SMART_IRQ3_ADDR(base) ((base) + (0x005))
#define SOC_SMART_IRQ4_ADDR(base) ((base) + (0x006))
#define SOC_SMART_COUL_IRQ_ADDR(base) ((base) + (0x007))
#define SOC_SMART_IRQ1_MASK_ADDR(base) ((base) + (0x008))
#define SOC_SMART_IRQ2_MASK_ADDR(base) ((base) + (0x009))
#define SOC_SMART_IRQ3_MASK_ADDR(base) ((base) + (0x00A))
#define SOC_SMART_IRQ4_MASK_ADDR(base) ((base) + (0x00B))
#define SOC_SMART_COUL_IRQ_MASK_ADDR(base) ((base) + (0x00C))
#define SOC_SMART_SCP_RECORD1_ADDR(base) ((base) + (0x00D))
#define SOC_SMART_OCP_RECORD1_ADDR(base) ((base) + (0x00E))
#define SOC_SMART_OCP_RECORD2_ADDR(base) ((base) + (0x00F))
#define SOC_SMART_OCP_RECORD3_ADDR(base) ((base) + (0x010))
#define SOC_SMART_OCP_RECORD4_ADDR(base) ((base) + (0x011))
#define SOC_SMART_OCP_RECORD5_ADDR(base) ((base) + (0x012))
#define SOC_SMART_OCP_RECORD6_ADDR(base) ((base) + (0x013))
#define SOC_SMART_OCP_RECORD7_ADDR(base) ((base) + (0x014))
#define SOC_SMART_NP_IRQ1_RECORD_ADDR(base) ((base) + (0x015))
#define SOC_SMART_NP_IRQ2_RECORD_ADDR(base) ((base) + (0x016))
#define SOC_SMART_NP_IRQ3_RECORD_ADDR(base) ((base) + (0x017))
#define SOC_SMART_NP_SCP_RECORD1_ADDR(base) ((base) + (0x018))
#define SOC_SMART_NP_OCP_RECORD1_ADDR(base) ((base) + (0x019))
#define SOC_SMART_NP_OCP_RECORD2_ADDR(base) ((base) + (0x01A))
#define SOC_SMART_NP_OCP_RECORD3_ADDR(base) ((base) + (0x01B))
#define SOC_SMART_NP_OCP_RECORD4_ADDR(base) ((base) + (0x01C))
#define SOC_SMART_NP_OCP_RECORD5_ADDR(base) ((base) + (0x01D))
#define SOC_SMART_NP_OCP_RECORD6_ADDR(base) ((base) + (0x01E))
#define SOC_SMART_NP_OCP_RECORD7_ADDR(base) ((base) + (0x01F))
#define SOC_SMART_OCP_DEB_ADDR(base) ((base) + (0x020))
#define SOC_SMART_ONOFF8_ADDR(base) ((base) + (0x021))
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ADDR(base) ((base) + (0x022))
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ADDR(base) ((base) + (0x023))
#define SOC_SMART_OCP_MOD_CTRL3_ADDR(base) ((base) + (0x024))
#define SOC_SMART_OCP_MOD_CTRL4_ADDR(base) ((base) + (0x025))
#define SOC_SMART_OCP_MOD_CTRL5_ADDR(base) ((base) + (0x026))
#define SOC_SMART_OCP_MOD_CTRL6_ADDR(base) ((base) + (0x027))
#define SOC_SMART_OCP_MOD_CTRL7_ADDR(base) ((base) + (0x028))
#define SOC_SMART_OCP_MOD_CTRL8_ADDR(base) ((base) + (0x029))
#define SOC_SMART_OCP_MOD_CTRL9_ADDR(base) ((base) + (0x02A))
#define SOC_SMART_OCP_MOD_CTRL10_ADDR(base) ((base) + (0x02B))
#define SOC_SMART_OCP_MOD_CTRL11_ADDR(base) ((base) + (0x02C))
#define SOC_SMART_ENABLE1_ADDR(base) ((base) + (0x02D))
#define SOC_SMART_DISABLE1_ADDR(base) ((base) + (0x02E))
#define SOC_SMART_ONOFF_STATUS1_ADDR(base) ((base) + (0x02F))
#define SOC_SMART_ENABLE2_ADDR(base) ((base) + (0x030))
#define SOC_SMART_DISABLE2_ADDR(base) ((base) + (0x031))
#define SOC_SMART_ONOFF_STATUS2_ADDR(base) ((base) + (0x032))
#define SOC_SMART_ENABLE3_ADDR(base) ((base) + (0x033))
#define SOC_SMART_DISABLE3_ADDR(base) ((base) + (0x034))
#define SOC_SMART_ONOFF_STATUS3_ADDR(base) ((base) + (0x035))
#define SOC_SMART_ENABLE4_ADDR(base) ((base) + (0x036))
#define SOC_SMART_DISABLE4_ADDR(base) ((base) + (0x037))
#define SOC_SMART_ONOFF_STATUS4_ADDR(base) ((base) + (0x038))
#define SOC_SMART_ENABLE5_ADDR(base) ((base) + (0x039))
#define SOC_SMART_DISABLE5_ADDR(base) ((base) + (0x03A))
#define SOC_SMART_ONOFF_STATUS5_ADDR(base) ((base) + (0x03B))
#define SOC_SMART_ENABLE6_ADDR(base) ((base) + (0x03C))
#define SOC_SMART_DISABLE6_ADDR(base) ((base) + (0x03D))
#define SOC_SMART_ONOFF_STATUS6_ADDR(base) ((base) + (0x03E))
#define SOC_SMART_ENABLE7_ADDR(base) ((base) + (0x03F))
#define SOC_SMART_SIMCARD_EN_ADDR(base) ((base) + (0x040))
#define SOC_SMART_SIM0_CFG_ADDR(base) ((base) + (0x041))
#define SOC_SMART_SIM1_CFG_ADDR(base) ((base) + (0x042))
#define SOC_SMART_SIM_DEB_ADDR(base) ((base) + (0x043))
#define SOC_SMART_ECO_MOD_CFG1_ADDR(base) ((base) + (0x044))
#define SOC_SMART_ECO_MOD_CFG2_ADDR(base) ((base) + (0x045))
#define SOC_SMART_ECO_MOD_CFG3_ADDR(base) ((base) + (0x046))
#define SOC_SMART_ECO_MOD_CFG4_ADDR(base) ((base) + (0x047))
#define SOC_SMART_ENB3_ECO_MARK_ADDR(base) ((base) + (0x048))
#define SOC_SMART_BUCK01_REG1_ADJ_ADDR(base) ((base) + (0x049))
#define SOC_SMART_BUCK01_REG2_ADJ_ADDR(base) ((base) + (0x04A))
#define SOC_SMART_BUCK01_REG3_ADJ_ADDR(base) ((base) + (0x04B))
#define SOC_SMART_BUCK01_REG4_ADJ_ADDR(base) ((base) + (0x04C))
#define SOC_SMART_BUCK01_REG5_ADJ_ADDR(base) ((base) + (0x04D))
#define SOC_SMART_BUCK01_REG6_ADJ_ADDR(base) ((base) + (0x04E))
#define SOC_SMART_BUCK01_REG7_ADJ_ADDR(base) ((base) + (0x04F))
#define SOC_SMART_BUCK01_REG8_ADJ_ADDR(base) ((base) + (0x050))
#define SOC_SMART_BUCK01_REG9_ADJ_ADDR(base) ((base) + (0x051))
#define SOC_SMART_BUCK01_REG10_ADJ_ADDR(base) ((base) + (0x052))
#define SOC_SMART_BUCK01_REG11_ADJ_ADDR(base) ((base) + (0x053))
#define SOC_SMART_BUCK01_REG12_ADJ_ADDR(base) ((base) + (0x054))
#define SOC_SMART_BUCK01_REG13_ADJ_ADDR(base) ((base) + (0x055))
#define SOC_SMART_BUCK01_REG14_ADJ_ADDR(base) ((base) + (0x056))
#define SOC_SMART_BUCK01_REG15_ADJ_ADDR(base) ((base) + (0x057))
#define SOC_SMART_BUCK01_REG16_ADJ_ADDR(base) ((base) + (0x058))
#define SOC_SMART_BUCK01_REG17_ADJ_ADDR(base) ((base) + (0x059))
#define SOC_SMART_BUCK2_REG1_ADJ_ADDR(base) ((base) + (0x05A))
#define SOC_SMART_BUCK2_REG2_ADJ_ADDR(base) ((base) + (0x05B))
#define SOC_SMART_BUCK2_REG3_ADJ_ADDR(base) ((base) + (0x05C))
#define SOC_SMART_BUCK2_REG4_ADJ_ADDR(base) ((base) + (0x05D))
#define SOC_SMART_BUCK2_REG5_ADJ_ADDR(base) ((base) + (0x05E))
#define SOC_SMART_BUCK2_REG6_ADJ_ADDR(base) ((base) + (0x05F))
#define SOC_SMART_BUCK2_REG7_ADJ_ADDR(base) ((base) + (0x060))
#define SOC_SMART_BUCK2_REG8_ADJ_ADDR(base) ((base) + (0x061))
#define SOC_SMART_BUCK2_REG9_ADJ_ADDR(base) ((base) + (0x062))
#define SOC_SMART_BUCK2_REG10_ADJ_ADDR(base) ((base) + (0x063))
#define SOC_SMART_BUCK2_REG11_ADJ_ADDR(base) ((base) + (0x064))
#define SOC_SMART_BUCK2_REG12_ADJ_ADDR(base) ((base) + (0x065))
#define SOC_SMART_BUCK3_REG1_ADJ_ADDR(base) ((base) + (0x066))
#define SOC_SMART_BUCK3_REG2_ADJ_ADDR(base) ((base) + (0x067))
#define SOC_SMART_BUCK3_REG3_ADJ_ADDR(base) ((base) + (0x068))
#define SOC_SMART_BUCK3_REG4_ADJ_ADDR(base) ((base) + (0x069))
#define SOC_SMART_BUCK3_REG5_ADJ_ADDR(base) ((base) + (0x06A))
#define SOC_SMART_BUCK3_REG6_ADJ_ADDR(base) ((base) + (0x06B))
#define SOC_SMART_BUCK3_REG7_ADJ_ADDR(base) ((base) + (0x06C))
#define SOC_SMART_BUCK3_REG8_ADJ_ADDR(base) ((base) + (0x06D))
#define SOC_SMART_BUCK3_REG9_ADJ_ADDR(base) ((base) + (0x06E))
#define SOC_SMART_BUCK3_REG10_ADJ_ADDR(base) ((base) + (0x06F))
#define SOC_SMART_BUCK3_REG11_ADJ_ADDR(base) ((base) + (0x070))
#define SOC_SMART_BUCK3_REG12_ADJ_ADDR(base) ((base) + (0x071))
#define SOC_SMART_BUCK4_REG1_ADJ_ADDR(base) ((base) + (0x072))
#define SOC_SMART_BUCK4_REG2_ADJ_ADDR(base) ((base) + (0x073))
#define SOC_SMART_BUCK4_REG3_ADJ_ADDR(base) ((base) + (0x074))
#define SOC_SMART_BUCK4_REG4_ADJ_ADDR(base) ((base) + (0x075))
#define SOC_SMART_BUCK4_REG5_ADJ_ADDR(base) ((base) + (0x076))
#define SOC_SMART_BUCK4_REG6_ADJ_ADDR(base) ((base) + (0x077))
#define SOC_SMART_BUCK4_REG7_ADJ_ADDR(base) ((base) + (0x078))
#define SOC_SMART_BUCK4_REG8_ADJ_ADDR(base) ((base) + (0x079))
#define SOC_SMART_BUCK4_REG9_ADJ_ADDR(base) ((base) + (0x07A))
#define SOC_SMART_BUCK4_REG10_ADJ_ADDR(base) ((base) + (0x07B))
#define SOC_SMART_BUCK4_REG12_ADJ_ADDR(base) ((base) + (0x07C))
#define SOC_SMART_BUCK5_REG1_ADJ_ADDR(base) ((base) + (0x07D))
#define SOC_SMART_BUCK5_REG2_ADJ_ADDR(base) ((base) + (0x07E))
#define SOC_SMART_BUCK5_REG3_ADJ_ADDR(base) ((base) + (0x07F))
#define SOC_SMART_BUCK5_REG4_ADJ_ADDR(base) ((base) + (0x080))
#define SOC_SMART_BUCK5_REG5_ADJ_ADDR(base) ((base) + (0x081))
#define SOC_SMART_BUCK5_REG6_ADJ_ADDR(base) ((base) + (0x082))
#define SOC_SMART_BUCK5_REG7_ADJ_ADDR(base) ((base) + (0x083))
#define SOC_SMART_BUCK5_REG8_ADJ_ADDR(base) ((base) + (0x084))
#define SOC_SMART_BUCK5_REG9_ADJ_ADDR(base) ((base) + (0x085))
#define SOC_SMART_BUCK5_REG10_ADJ_ADDR(base) ((base) + (0x086))
#define SOC_SMART_BUCK5_REG12_ADJ_ADDR(base) ((base) + (0x087))
#define SOC_SMART_BUCK5_REG13_ADJ_ADDR(base) ((base) + (0x088))
#define SOC_SMART_BUCK5_REG14_ADJ_ADDR(base) ((base) + (0x089))
#define SOC_SMART_BUCK6_REG1_ADJ_ADDR(base) ((base) + (0x08A))
#define SOC_SMART_BUCK6_REG2_ADJ_ADDR(base) ((base) + (0x08B))
#define SOC_SMART_BUCK6_REG3_ADJ_ADDR(base) ((base) + (0x08C))
#define SOC_SMART_BUCK6_REG4_ADJ_ADDR(base) ((base) + (0x08D))
#define SOC_SMART_BUCK6_REG5_ADJ_ADDR(base) ((base) + (0x08E))
#define SOC_SMART_BUCK6_REG6_ADJ_ADDR(base) ((base) + (0x08F))
#define SOC_SMART_BUCK6_REG7_ADJ_ADDR(base) ((base) + (0x090))
#define SOC_SMART_BUCK6_REG8_ADJ_ADDR(base) ((base) + (0x091))
#define SOC_SMART_BUCK6_REG9_ADJ_ADDR(base) ((base) + (0x092))
#define SOC_SMART_BUCK6_REG10_ADJ_ADDR(base) ((base) + (0x093))
#define SOC_SMART_BUCK6_REG11_ADJ_ADDR(base) ((base) + (0x094))
#define SOC_SMART_BUCK6_REG12_ADJ_ADDR(base) ((base) + (0x095))
#define SOC_SMART_CHG_PUMP2_ADJ_ADDR(base) ((base) + (0x096))
#define SOC_SMART_VSET_BUCK01_ADJ_ADDR(base) ((base) + (0x097))
#define SOC_SMART_VSET_BUCK2_ADJ_ADDR(base) ((base) + (0x098))
#define SOC_SMART_VSET_BUCK3_ADJ_ADDR(base) ((base) + (0x099))
#define SOC_SMART_VSET_BUCK4_ADJ_ADDR(base) ((base) + (0x09A))
#define SOC_SMART_VSET_BUCK5_ADJ_ADDR(base) ((base) + (0x09B))
#define SOC_SMART_VSET_BUCK6_ADJ_ADDR(base) ((base) + (0x09C))
#define SOC_SMART_LDO1_REG_ADJ_ADDR(base) ((base) + (0x09D))
#define SOC_SMART_LDO2_REG_ADJ_ADDR(base) ((base) + (0x09E))
#define SOC_SMART_LDO3_REG_ADJ_ADDR(base) ((base) + (0x09F))
#define SOC_SMART_LDO4_REG_ADJ_ADDR(base) ((base) + (0x0A0))
#define SOC_SMART_LDO5_REG_ADJ_ADDR(base) ((base) + (0x0A1))
#define SOC_SMART_LDO6_REG_ADJ_ADDR(base) ((base) + (0x0A2))
#define SOC_SMART_LDO7_REG_ADJ_ADDR(base) ((base) + (0x0A3))
#define SOC_SMART_LDO8_REG_ADJ_ADDR(base) ((base) + (0x0A4))
#define SOC_SMART_LDO9_REG_ADJ_ADDR(base) ((base) + (0x0A5))
#define SOC_SMART_LDO10_REG_ADJ_ADDR(base) ((base) + (0x0A6))
#define SOC_SMART_LDO11_REG_ADJ_ADDR(base) ((base) + (0x0A7))
#define SOC_SMART_LDO12_REG_ADJ_ADDR(base) ((base) + (0x0A8))
#define SOC_SMART_LDO13_REG_ADJ_ADDR(base) ((base) + (0x0A9))
#define SOC_SMART_LDO14_REG_ADJ_ADDR(base) ((base) + (0x0AA))
#define SOC_SMART_LDO15_REG_ADJ_ADDR(base) ((base) + (0x0AB))
#define SOC_SMART_LDO16_REG_ADJ_ADDR(base) ((base) + (0x0AC))
#define SOC_SMART_LDO17_REG_ADJ_ADDR(base) ((base) + (0x0AD))
#define SOC_SMART_LDO18_REG_ADJ_ADDR(base) ((base) + (0x0AE))
#define SOC_SMART_LDO19_REG_ADJ_ADDR(base) ((base) + (0x0AF))
#define SOC_SMART_LDO20_REG_ADJ_ADDR(base) ((base) + (0x0B0))
#define SOC_SMART_LDO21_REG_ADJ_ADDR(base) ((base) + (0x0B1))
#define SOC_SMART_LDO22_REG_ADJ_ADDR(base) ((base) + (0x0B2))
#define SOC_SMART_LDO23_REG_ADJ_ADDR(base) ((base) + (0x0B3))
#define SOC_SMART_LDO24_REG_ADJ_ADDR(base) ((base) + (0x0B4))
#define SOC_SMART_PMUA_REG_ADJ_ADDR(base) ((base) + (0x0B5))
#define SOC_SMART_LVS_ADJ1_ADDR(base) ((base) + (0x0B6))
#define SOC_SMART_LVS_ADJ2_ADDR(base) ((base) + (0x0B7))
#define SOC_SMART_LVS_ADJ3_ADDR(base) ((base) + (0x0B8))
#define SOC_SMART_BOOST_ADJ0_ADDR(base) ((base) + (0x0B9))
#define SOC_SMART_BOOST_ADJ1_ADDR(base) ((base) + (0x0BA))
#define SOC_SMART_BOOST_ADJ2_ADDR(base) ((base) + (0x0BB))
#define SOC_SMART_BOOST_ADJ3_ADDR(base) ((base) + (0x0BC))
#define SOC_SMART_BOOST_ADJ4_ADDR(base) ((base) + (0x0BD))
#define SOC_SMART_BOOST_ADJ5_ADDR(base) ((base) + (0x0BE))
#define SOC_SMART_BOOST_ADJ6_ADDR(base) ((base) + (0x0BF))
#define SOC_SMART_BOOST_ADJ7_ADDR(base) ((base) + (0x0C0))
#define SOC_SMART_BOOST_ADJ8_ADDR(base) ((base) + (0x0C1))
#define SOC_SMART_BOOST_ADJ9_ADDR(base) ((base) + (0x0C2))
#define SOC_SMART_BOOST_ADJ10_ADDR(base) ((base) + (0x0C3))
#define SOC_SMART_BOOST_ADJ11_ADDR(base) ((base) + (0x0C4))
#define SOC_SMART_CLASSD_ADJ0_ADDR(base) ((base) + (0x0C5))
#define SOC_SMART_CLASSD_ADJ1_ADDR(base) ((base) + (0x0C6))
#define SOC_SMART_CLASSD_ADJ2_ADDR(base) ((base) + (0x0C7))
#define SOC_SMART_BANDGAP_THSD_ADJ1_ADDR(base) ((base) + (0x0C8))
#define SOC_SMART_BANDGAP_THSD_ADJ2_ADDR(base) ((base) + (0x0C9))
#define SOC_SMART_DR_FLA_CTRL1_ADDR(base) ((base) + (0x0CA))
#define SOC_SMART_DR_FLA_CTRL2_ADDR(base) ((base) + (0x0CB))
#define SOC_SMART_FLASH_PERIOD_ADDR(base) ((base) + (0x0CC))
#define SOC_SMART_FLASH_ON_ADDR(base) ((base) + (0x0CD))
#define SOC_SMART_DR_MODE_SEL_ADDR(base) ((base) + (0x0CE))
#define SOC_SMART_DR_BRE_CTRL_ADDR(base) ((base) + (0x0CF))
#define SOC_SMART_DR1_TIM_CONF0_ADDR(base) ((base) + (0x0D0))
#define SOC_SMART_DR1_TIM_CONF1_ADDR(base) ((base) + (0x0D1))
#define SOC_SMART_DR1_ISET_ADDR(base) ((base) + (0x0D2))
#define SOC_SMART_DR2_TIM_CONF0_ADDR(base) ((base) + (0x0D3))
#define SOC_SMART_DR2_TIM_CONF1_ADDR(base) ((base) + (0x0D4))
#define SOC_SMART_DR2_ISET_ADDR(base) ((base) + (0x0D5))
#define SOC_SMART_DR_LED_CTRL_ADDR(base) ((base) + (0x0D6))
#define SOC_SMART_DR_OUT_CTRL_ADDR(base) ((base) + (0x0D7))
#define SOC_SMART_DR3_ISET_ADDR(base) ((base) + (0x0D8))
#define SOC_SMART_DR3_START_DEL_ADDR(base) ((base) + (0x0D9))
#define SOC_SMART_DR3_TIM_CONF0_ADDR(base) ((base) + (0x0DA))
#define SOC_SMART_DR3_TIM_CONF1_ADDR(base) ((base) + (0x0DB))
#define SOC_SMART_DR4_ISET_ADDR(base) ((base) + (0x0DC))
#define SOC_SMART_DR4_START_DEL_ADDR(base) ((base) + (0x0DD))
#define SOC_SMART_DR4_TIM_CONF0_ADDR(base) ((base) + (0x0DE))
#define SOC_SMART_DR4_TIM_CONF1_ADDR(base) ((base) + (0x0DF))
#define SOC_SMART_DR5_ISET_ADDR(base) ((base) + (0x0E0))
#define SOC_SMART_DR5_START_DEL_ADDR(base) ((base) + (0x0E1))
#define SOC_SMART_DR5_TIM_CONF0_ADDR(base) ((base) + (0x0E2))
#define SOC_SMART_DR5_TIM_CONF1_ADDR(base) ((base) + (0x0E3))
#define SOC_SMART_OTP_CTRL1_ADDR(base) ((base) + (0x0E4))
#define SOC_SMART_OTP_CTRL2_ADDR(base) ((base) + (0x0E5))
#define SOC_SMART_OTP_PDIN_ADDR(base) ((base) + (0x0E6))
#define SOC_SMART_OTP_PDOB0_ADDR(base) ((base) + (0x0E7))
#define SOC_SMART_OTP_PDOB1_ADDR(base) ((base) + (0x0E8))
#define SOC_SMART_OTP_PDOB2_ADDR(base) ((base) + (0x0E9))
#define SOC_SMART_OTP_PDOB3_ADDR(base) ((base) + (0x0EA))
#define SOC_SMART_RTCCR_A0_ADDR(base) ((base) + (0x0EB))
#define SOC_SMART_RTCCR_A1_ADDR(base) ((base) + (0x0EC))
#define SOC_SMART_RTCCR_A2_ADDR(base) ((base) + (0x0ED))
#define SOC_SMART_RTCCR_A3_ADDR(base) ((base) + (0x0EE))
#define SOC_SMART_RTCLR_A0_ADDR(base) ((base) + (0x0EF))
#define SOC_SMART_RTCLR_A1_ADDR(base) ((base) + (0x0F0))
#define SOC_SMART_RTCLR_A2_ADDR(base) ((base) + (0x0F1))
#define SOC_SMART_RTCLR_A3_ADDR(base) ((base) + (0x0F2))
#define SOC_SMART_RTCCTRL_A_ADDR(base) ((base) + (0x0F3))
#define SOC_SMART_RTCMR_A_A0_ADDR(base) ((base) + (0x0F4))
#define SOC_SMART_RTCMR_A_A1_ADDR(base) ((base) + (0x0F5))
#define SOC_SMART_RTCMR_A_A2_ADDR(base) ((base) + (0x0F6))
#define SOC_SMART_RTCMR_A_A3_ADDR(base) ((base) + (0x0F7))
#define SOC_SMART_RTCMR_A_B0_ADDR(base) ((base) + (0x0F8))
#define SOC_SMART_RTCMR_A_B1_ADDR(base) ((base) + (0x0F9))
#define SOC_SMART_RTCMR_A_B2_ADDR(base) ((base) + (0x0FA))
#define SOC_SMART_RTCMR_A_B3_ADDR(base) ((base) + (0x0FB))
#define SOC_SMART_RTCMR_A_C0_ADDR(base) ((base) + (0x0FC))
#define SOC_SMART_RTCMR_A_C1_ADDR(base) ((base) + (0x0FD))
#define SOC_SMART_RTCMR_A_C2_ADDR(base) ((base) + (0x0FE))
#define SOC_SMART_RTCMR_A_C3_ADDR(base) ((base) + (0x0FF))
#define SOC_SMART_RTCMR_A_D0_ADDR(base) ((base) + (0x100))
#define SOC_SMART_RTCMR_A_D1_ADDR(base) ((base) + (0x101))
#define SOC_SMART_RTCMR_A_D2_ADDR(base) ((base) + (0x102))
#define SOC_SMART_RTCMR_A_D3_ADDR(base) ((base) + (0x103))
#define SOC_SMART_RTCMR_A_E0_ADDR(base) ((base) + (0x104))
#define SOC_SMART_RTCMR_A_E1_ADDR(base) ((base) + (0x105))
#define SOC_SMART_RTCMR_A_E2_ADDR(base) ((base) + (0x106))
#define SOC_SMART_RTCMR_A_E3_ADDR(base) ((base) + (0x107))
#define SOC_SMART_RTCMR_A_F0_ADDR(base) ((base) + (0x108))
#define SOC_SMART_RTCMR_A_F1_ADDR(base) ((base) + (0x109))
#define SOC_SMART_RTCMR_A_F2_ADDR(base) ((base) + (0x10A))
#define SOC_SMART_RTCMR_A_F3_ADDR(base) ((base) + (0x10B))
#define SOC_SMART_RTCCR_NA0_ADDR(base) ((base) + (0x10C))
#define SOC_SMART_RTCCR_NA1_ADDR(base) ((base) + (0x10D))
#define SOC_SMART_RTCCR_NA2_ADDR(base) ((base) + (0x10E))
#define SOC_SMART_RTCCR_NA3_ADDR(base) ((base) + (0x10F))
#define SOC_SMART_RTCLR_NA0_ADDR(base) ((base) + (0x110))
#define SOC_SMART_RTCLR_NA1_ADDR(base) ((base) + (0x111))
#define SOC_SMART_RTCLR_NA2_ADDR(base) ((base) + (0x112))
#define SOC_SMART_RTCLR_NA3_ADDR(base) ((base) + (0x113))
#define SOC_SMART_RTCCTRL_NA_ADDR(base) ((base) + (0x114))
#define SOC_SMART_VERSION_ADDR(base) ((base) + (0x115))
#define SOC_SMART_RESERVED0_ADDR(base) ((base) + (0x116))
#define SOC_SMART_RESERVED1_ADDR(base) ((base) + (0x117))
#define SOC_SMART_RESERVED2_ADDR(base) ((base) + (0x118))
#define SOC_SMART_RESERVED3_ADDR(base) ((base) + (0x119))
#define SOC_SMART_RESERVED4_ADDR(base) ((base) + (0x11A))
#define SOC_SMART_HTOL_MODE_ADDR(base) ((base) + (0x11B))
#define SOC_SMART_DAC_CTRL_ADDR(base) ((base) + (0x11C))
#define SOC_SMART_CHIP_SOFT_RST_ADDR(base) ((base) + (0x11D))
#define SOC_SMART_NP_REG_ADJ_ADDR(base) ((base) + (0x11E))
#define SOC_SMART_NP_REG_CHG_ADDR(base) ((base) + (0x11F))
#define SOC_SMART_NP_RSVED1_ADDR(base) ((base) + (0x120))
#define SOC_SMART_NP_RSVED2_ADDR(base) ((base) + (0x121))
#define SOC_SMART_NP_RSVED3_ADDR(base) ((base) + (0x122))
#define SOC_SMART_NP_RSVED4_ADDR(base) ((base) + (0x123))
#define SOC_SMART_RTC_ADJ1_ADDR(base) ((base) + (0x124))
#define SOC_SMART_RTC_ADJ2_ADDR(base) ((base) + (0x125))
#define SOC_SMART_CLJ_CTRL_REG_ADDR(base) ((base) + (0x133))
#define SOC_SMART_ECO_REFALSH_TIME_ADDR(base) ((base) + (0x134))
#define SOC_SMART_CL_OUT0_ADDR(base) ((base) + (0x135))
#define SOC_SMART_CL_OUT1_ADDR(base) ((base) + (0x136))
#define SOC_SMART_CL_OUT2_ADDR(base) ((base) + (0x137))
#define SOC_SMART_CL_OUT3_ADDR(base) ((base) + (0x138))
#define SOC_SMART_CL_IN0_ADDR(base) ((base) + (0x139))
#define SOC_SMART_CL_IN1_ADDR(base) ((base) + (0x13A))
#define SOC_SMART_CL_IN2_ADDR(base) ((base) + (0x13B))
#define SOC_SMART_CL_IN3_ADDR(base) ((base) + (0x13C))
#define SOC_SMART_CHG_TIMER0_ADDR(base) ((base) + (0x13D))
#define SOC_SMART_CHG_TIMER1_ADDR(base) ((base) + (0x13E))
#define SOC_SMART_CHG_TIMER2_ADDR(base) ((base) + (0x13F))
#define SOC_SMART_CHG_TIMER3_ADDR(base) ((base) + (0x140))
#define SOC_SMART_LOAD_TIMER0_ADDR(base) ((base) + (0x141))
#define SOC_SMART_LOAD_TIMER1_ADDR(base) ((base) + (0x142))
#define SOC_SMART_LOAD_TIMER2_ADDR(base) ((base) + (0x143))
#define SOC_SMART_LOAD_TIMER3_ADDR(base) ((base) + (0x144))
#define SOC_SMART_OFF_TIMER0_ADDR(base) ((base) + (0x145))
#define SOC_SMART_OFF_TIMER1_ADDR(base) ((base) + (0x146))
#define SOC_SMART_OFF_TIMER2_ADDR(base) ((base) + (0x147))
#define SOC_SMART_OFF_TIMER3_ADDR(base) ((base) + (0x148))
#define SOC_SMART_CL_INT0_ADDR(base) ((base) + (0x149))
#define SOC_SMART_CL_INT1_ADDR(base) ((base) + (0x14A))
#define SOC_SMART_CL_INT2_ADDR(base) ((base) + (0x14B))
#define SOC_SMART_CL_INT3_ADDR(base) ((base) + (0x14C))
#define SOC_SMART_V_INT0_ADDR(base) ((base) + (0x14D))
#define SOC_SMART_V_INT1_ADDR(base) ((base) + (0x14E))
#define SOC_SMART_OFFSET_CURRENT0_ADDR(base) ((base) + (0x14F))
#define SOC_SMART_OFFSET_CURRENT1_ADDR(base) ((base) + (0x150))
#define SOC_SMART_OFFSET_VOLTAGE0_ADDR(base) ((base) + (0x151))
#define SOC_SMART_OFFSET_VOLTAGE1_ADDR(base) ((base) + (0x152))
#define SOC_SMART_OCV_DATA1_ADDR(base) ((base) + (0x153))
#define SOC_SMART_OCV_DATA2_ADDR(base) ((base) + (0x154))
#define SOC_SMART_V_OUT0_PRE0_ADDR(base) ((base) + (0x155))
#define SOC_SMART_V_OUT1_PRE0_ADDR(base) ((base) + (0x156))
#define SOC_SMART_V_OUT0_PRE1_ADDR(base) ((base) + (0x157))
#define SOC_SMART_V_OUT1_PRE1_ADDR(base) ((base) + (0x158))
#define SOC_SMART_V_OUT0_PRE2_ADDR(base) ((base) + (0x159))
#define SOC_SMART_V_OUT1_PRE2_ADDR(base) ((base) + (0x15A))
#define SOC_SMART_V_OUT0_PRE3_ADDR(base) ((base) + (0x15B))
#define SOC_SMART_V_OUT1_PRE3_ADDR(base) ((base) + (0x15C))
#define SOC_SMART_V_OUT0_PRE4_ADDR(base) ((base) + (0x15D))
#define SOC_SMART_V_OUT1_PRE4_ADDR(base) ((base) + (0x15E))
#define SOC_SMART_V_OUT0_PRE5_ADDR(base) ((base) + (0x15F))
#define SOC_SMART_V_OUT1_PRE5_ADDR(base) ((base) + (0x160))
#define SOC_SMART_V_OUT0_PRE6_ADDR(base) ((base) + (0x161))
#define SOC_SMART_V_OUT1_PRE6_ADDR(base) ((base) + (0x162))
#define SOC_SMART_V_OUT0_PRE7_ADDR(base) ((base) + (0x163))
#define SOC_SMART_V_OUT1_PRE7_ADDR(base) ((base) + (0x164))
#define SOC_SMART_V_OUT0_PRE8_ADDR(base) ((base) + (0x165))
#define SOC_SMART_V_OUT1_PRE8_ADDR(base) ((base) + (0x166))
#define SOC_SMART_V_OUT0_PRE9_ADDR(base) ((base) + (0x167))
#define SOC_SMART_V_OUT1_PRE9_ADDR(base) ((base) + (0x168))
#define SOC_SMART_V_OUT0_PRE10_ADDR(base) ((base) + (0x169))
#define SOC_SMART_V_OUT1_PRE10_ADDR(base) ((base) + (0x16A))
#define SOC_SMART_V_OUT0_PRE11_ADDR(base) ((base) + (0x16B))
#define SOC_SMART_V_OUT1_PRE11_ADDR(base) ((base) + (0x16C))
#define SOC_SMART_V_OUT0_PRE12_ADDR(base) ((base) + (0x16D))
#define SOC_SMART_V_OUT1_PRE12_ADDR(base) ((base) + (0x16E))
#define SOC_SMART_V_OUT0_PRE13_ADDR(base) ((base) + (0x16F))
#define SOC_SMART_V_OUT1_PRE13_ADDR(base) ((base) + (0x170))
#define SOC_SMART_V_OUT0_PRE14_ADDR(base) ((base) + (0x171))
#define SOC_SMART_V_OUT1_PRE14_ADDR(base) ((base) + (0x172))
#define SOC_SMART_V_OUT0_PRE15_ADDR(base) ((base) + (0x173))
#define SOC_SMART_V_OUT1_PRE15_ADDR(base) ((base) + (0x174))
#define SOC_SMART_V_OUT0_PRE16_ADDR(base) ((base) + (0x175))
#define SOC_SMART_V_OUT1_PRE16_ADDR(base) ((base) + (0x176))
#define SOC_SMART_V_OUT0_PRE17_ADDR(base) ((base) + (0x177))
#define SOC_SMART_V_OUT1_PRE17_ADDR(base) ((base) + (0x178))
#define SOC_SMART_V_OUT0_PRE18_ADDR(base) ((base) + (0x179))
#define SOC_SMART_V_OUT1_PRE18_ADDR(base) ((base) + (0x17A))
#define SOC_SMART_V_OUT0_PRE19_ADDR(base) ((base) + (0x17B))
#define SOC_SMART_V_OUT1_PRE19_ADDR(base) ((base) + (0x17C))
#define SOC_SMART_CURRENT0_PRE0_ADDR(base) ((base) + (0x17D))
#define SOC_SMART_CURRENT1_PRE0_ADDR(base) ((base) + (0x17E))
#define SOC_SMART_CURRENT0_PRE1_ADDR(base) ((base) + (0x17F))
#define SOC_SMART_CURRENT1_PRE1_ADDR(base) ((base) + (0x180))
#define SOC_SMART_CURRENT0_PRE2_ADDR(base) ((base) + (0x181))
#define SOC_SMART_CURRENT1_PRE2_ADDR(base) ((base) + (0x182))
#define SOC_SMART_CURRENT0_PRE3_ADDR(base) ((base) + (0x183))
#define SOC_SMART_CURRENT1_PRE3_ADDR(base) ((base) + (0x184))
#define SOC_SMART_CURRENT0_PRE4_ADDR(base) ((base) + (0x185))
#define SOC_SMART_CURRENT1_PRE4_ADDR(base) ((base) + (0x186))
#define SOC_SMART_CURRENT0_PRE5_ADDR(base) ((base) + (0x187))
#define SOC_SMART_CURRENT1_PRE5_ADDR(base) ((base) + (0x188))
#define SOC_SMART_CURRENT0_PRE6_ADDR(base) ((base) + (0x189))
#define SOC_SMART_CURRENT1_PRE6_ADDR(base) ((base) + (0x18A))
#define SOC_SMART_CURRENT0_PRE7_ADDR(base) ((base) + (0x18B))
#define SOC_SMART_CURRENT1_PRE7_ADDR(base) ((base) + (0x18C))
#define SOC_SMART_CURRENT0_PRE8_ADDR(base) ((base) + (0x18D))
#define SOC_SMART_CURRENT1_PRE8_ADDR(base) ((base) + (0x18E))
#define SOC_SMART_CURRENT0_PRE9_ADDR(base) ((base) + (0x18F))
#define SOC_SMART_CURRENT1_PRE9_ADDR(base) ((base) + (0x190))
#define SOC_SMART_CURRENT0_PRE10_ADDR(base) ((base) + (0x191))
#define SOC_SMART_CURRENT1_PRE10_ADDR(base) ((base) + (0x192))
#define SOC_SMART_CURRENT0_PRE11_ADDR(base) ((base) + (0x193))
#define SOC_SMART_CURRENT1_PRE11_ADDR(base) ((base) + (0x194))
#define SOC_SMART_CURRENT0_PRE12_ADDR(base) ((base) + (0x195))
#define SOC_SMART_CURRENT1_PRE12_ADDR(base) ((base) + (0x196))
#define SOC_SMART_CURRENT0_PRE13_ADDR(base) ((base) + (0x197))
#define SOC_SMART_CURRENT1_PRE13_ADDR(base) ((base) + (0x198))
#define SOC_SMART_CURRENT0_PRE14_ADDR(base) ((base) + (0x199))
#define SOC_SMART_CURRENT1_PRE14_ADDR(base) ((base) + (0x19A))
#define SOC_SMART_CURRENT0_PRE15_ADDR(base) ((base) + (0x19B))
#define SOC_SMART_CURRENT1_PRE15_ADDR(base) ((base) + (0x19C))
#define SOC_SMART_CURRENT0_PRE16_ADDR(base) ((base) + (0x19D))
#define SOC_SMART_CURRENT1_PRE16_ADDR(base) ((base) + (0x19E))
#define SOC_SMART_CURRENT0_PRE17_ADDR(base) ((base) + (0x19F))
#define SOC_SMART_CURRENT1_PRE17_ADDR(base) ((base) + (0x1A0))
#define SOC_SMART_CURRENT0_PRE18_ADDR(base) ((base) + (0x1A1))
#define SOC_SMART_CURRENT1_PRE18_ADDR(base) ((base) + (0x1A2))
#define SOC_SMART_CURRENT0_PRE19_ADDR(base) ((base) + (0x1A3))
#define SOC_SMART_CURRENT1_PRE19_ADDR(base) ((base) + (0x1A4))
#define SOC_SMART_CLJ_DEBUG_ADDR(base) ((base) + (0x1A5))
#define SOC_SMART_STATE_TEST_ADDR(base) ((base) + (0x1A6))
#define SOC_SMART_CLJ_RESERVED1_ADDR(base) ((base) + (0x1A7))
#define SOC_SMART_CLJ_RESERVED2_ADDR(base) ((base) + (0x1A8))
#define SOC_SMART_CLJ_RESERVED3_ADDR(base) ((base) + (0x1A9))
#define SOC_SMART_CLJ_RESERVED4_ADDR(base) ((base) + (0x1AA))
#define SOC_SMART_CLJ_RESERVED5_ADDR(base) ((base) + (0x1AB))
#define SOC_SMART_CLJ_RESERVED6_ADDR(base) ((base) + (0x1AC))
#define SOC_SMART_CLJ_RESERVED7_ADDR(base) ((base) + (0x1AD))
#define SOC_SMART_CLJ_RESERVED8_ADDR(base) ((base) + (0x1AE))
#define SOC_SMART_ADC_CTRL_ADDR(base) ((base) + (0x00))
#define SOC_SMART_ADC_CONV_ADDR(base) ((base) + (0x01))
#define SOC_SMART_CONV_STATUS_ADDR(base) ((base) + (0x02))
#define SOC_SMART_ADC_DATA1_ADDR(base) ((base) + (0x03))
#define SOC_SMART_ADC_DATA0_ADDR(base) ((base) + (0x04))
#define SOC_SMART_ADC_CURRENT_ADDR(base) ((base) + (0x05))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otmp_d1r : 1;
        unsigned char otmp150_d1r : 1;
        unsigned char osc_state : 1;
        unsigned char vsys_uv_d2f : 1;
        unsigned char vsys_6p0_d200ur : 1;
        unsigned char pwron_d20r : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_STATUS1_UNION;
#endif
#define SOC_SMART_STATUS1_otmp_d1r_START (0)
#define SOC_SMART_STATUS1_otmp_d1r_END (0)
#define SOC_SMART_STATUS1_otmp150_d1r_START (1)
#define SOC_SMART_STATUS1_otmp150_d1r_END (1)
#define SOC_SMART_STATUS1_osc_state_START (2)
#define SOC_SMART_STATUS1_osc_state_END (2)
#define SOC_SMART_STATUS1_vsys_uv_d2f_START (3)
#define SOC_SMART_STATUS1_vsys_uv_d2f_END (3)
#define SOC_SMART_STATUS1_vsys_6p0_d200ur_START (4)
#define SOC_SMART_STATUS1_vsys_6p0_d200ur_END (4)
#define SOC_SMART_STATUS1_pwron_d20r_START (5)
#define SOC_SMART_STATUS1_pwron_d20r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char alarm_on_a : 1;
        unsigned char alarm_on_b : 1;
        unsigned char alarm_on_c : 1;
        unsigned char alarm_on_d : 1;
        unsigned char alarm_on_e : 1;
        unsigned char vbus_det_0p9_d3r : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_STATUS2_UNION;
#endif
#define SOC_SMART_STATUS2_alarm_on_a_START (0)
#define SOC_SMART_STATUS2_alarm_on_a_END (0)
#define SOC_SMART_STATUS2_alarm_on_b_START (1)
#define SOC_SMART_STATUS2_alarm_on_b_END (1)
#define SOC_SMART_STATUS2_alarm_on_c_START (2)
#define SOC_SMART_STATUS2_alarm_on_c_END (2)
#define SOC_SMART_STATUS2_alarm_on_d_START (3)
#define SOC_SMART_STATUS2_alarm_on_d_END (3)
#define SOC_SMART_STATUS2_alarm_on_e_START (4)
#define SOC_SMART_STATUS2_alarm_on_e_END (4)
#define SOC_SMART_STATUS2_vbus_det_0p9_d3r_START (5)
#define SOC_SMART_STATUS2_vbus_det_0p9_d3r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otmp_d1r : 1;
        unsigned char vsys_2p5_f : 1;
        unsigned char vsys_uv_d2f : 1;
        unsigned char vsys_6p0_d200ur : 1;
        unsigned char pwron_d4sr : 1;
        unsigned char pwron_d20f : 1;
        unsigned char pwron_d20r : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_IRQ1_UNION;
#endif
#define SOC_SMART_IRQ1_otmp_d1r_START (0)
#define SOC_SMART_IRQ1_otmp_d1r_END (0)
#define SOC_SMART_IRQ1_vsys_2p5_f_START (1)
#define SOC_SMART_IRQ1_vsys_2p5_f_END (1)
#define SOC_SMART_IRQ1_vsys_uv_d2f_START (2)
#define SOC_SMART_IRQ1_vsys_uv_d2f_END (2)
#define SOC_SMART_IRQ1_vsys_6p0_d200ur_START (3)
#define SOC_SMART_IRQ1_vsys_6p0_d200ur_END (3)
#define SOC_SMART_IRQ1_pwron_d4sr_START (4)
#define SOC_SMART_IRQ1_pwron_d4sr_END (4)
#define SOC_SMART_IRQ1_pwron_d20f_START (5)
#define SOC_SMART_IRQ1_pwron_d20f_END (5)
#define SOC_SMART_IRQ1_pwron_d20r_START (6)
#define SOC_SMART_IRQ1_pwron_d20r_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_scp_r : 1;
        unsigned char vbus_det_1p375_d90ur : 1;
        unsigned char vbus_det_0p9_d3f : 1;
        unsigned char vbus_det_0p9_d3r : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_IRQ2_UNION;
#endif
#define SOC_SMART_IRQ2_ocp_scp_r_START (0)
#define SOC_SMART_IRQ2_ocp_scp_r_END (0)
#define SOC_SMART_IRQ2_vbus_det_1p375_d90ur_START (1)
#define SOC_SMART_IRQ2_vbus_det_1p375_d90ur_END (1)
#define SOC_SMART_IRQ2_vbus_det_0p9_d3f_START (2)
#define SOC_SMART_IRQ2_vbus_det_0p9_d3f_END (2)
#define SOC_SMART_IRQ2_vbus_det_0p9_d3r_START (3)
#define SOC_SMART_IRQ2_vbus_det_0p9_d3r_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char alarm_on_a : 1;
        unsigned char alarm_on_b : 1;
        unsigned char alarm_on_c : 1;
        unsigned char alarm_on_d : 1;
        unsigned char alarm_on_e : 1;
        unsigned char alarm_on_f : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_IRQ3_UNION;
#endif
#define SOC_SMART_IRQ3_alarm_on_a_START (0)
#define SOC_SMART_IRQ3_alarm_on_a_END (0)
#define SOC_SMART_IRQ3_alarm_on_b_START (1)
#define SOC_SMART_IRQ3_alarm_on_b_END (1)
#define SOC_SMART_IRQ3_alarm_on_c_START (2)
#define SOC_SMART_IRQ3_alarm_on_c_END (2)
#define SOC_SMART_IRQ3_alarm_on_d_START (3)
#define SOC_SMART_IRQ3_alarm_on_d_END (3)
#define SOC_SMART_IRQ3_alarm_on_e_START (4)
#define SOC_SMART_IRQ3_alarm_on_e_END (4)
#define SOC_SMART_IRQ3_alarm_on_f_START (5)
#define SOC_SMART_IRQ3_alarm_on_f_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char sim0_hpd_out_f : 1;
        unsigned char sim0_hpd_out_r : 1;
        unsigned char sim0_hpd_in_f : 1;
        unsigned char sim0_hpd_in_r : 1;
        unsigned char sim1_hpd_out_f : 1;
        unsigned char sim1_hpd_out_r : 1;
        unsigned char sim1_hpd_in_f : 1;
        unsigned char sim1_hpd_in_r : 1;
    } reg;
} SOC_SMART_IRQ4_UNION;
#endif
#define SOC_SMART_IRQ4_sim0_hpd_out_f_START (0)
#define SOC_SMART_IRQ4_sim0_hpd_out_f_END (0)
#define SOC_SMART_IRQ4_sim0_hpd_out_r_START (1)
#define SOC_SMART_IRQ4_sim0_hpd_out_r_END (1)
#define SOC_SMART_IRQ4_sim0_hpd_in_f_START (2)
#define SOC_SMART_IRQ4_sim0_hpd_in_f_END (2)
#define SOC_SMART_IRQ4_sim0_hpd_in_r_START (3)
#define SOC_SMART_IRQ4_sim0_hpd_in_r_END (3)
#define SOC_SMART_IRQ4_sim1_hpd_out_f_START (4)
#define SOC_SMART_IRQ4_sim1_hpd_out_f_END (4)
#define SOC_SMART_IRQ4_sim1_hpd_out_r_START (5)
#define SOC_SMART_IRQ4_sim1_hpd_out_r_END (5)
#define SOC_SMART_IRQ4_sim1_hpd_in_f_START (6)
#define SOC_SMART_IRQ4_sim1_hpd_in_f_END (6)
#define SOC_SMART_IRQ4_sim1_hpd_in_r_START (7)
#define SOC_SMART_IRQ4_sim1_hpd_in_r_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int_i : 1;
        unsigned char cl_out_i : 1;
        unsigned char cl_in_i : 1;
        unsigned char chg_timer_i : 1;
        unsigned char load_timer_i : 1;
        unsigned char vbat_int_i : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_COUL_IRQ_UNION;
#endif
#define SOC_SMART_COUL_IRQ_cl_int_i_START (0)
#define SOC_SMART_COUL_IRQ_cl_int_i_END (0)
#define SOC_SMART_COUL_IRQ_cl_out_i_START (1)
#define SOC_SMART_COUL_IRQ_cl_out_i_END (1)
#define SOC_SMART_COUL_IRQ_cl_in_i_START (2)
#define SOC_SMART_COUL_IRQ_cl_in_i_END (2)
#define SOC_SMART_COUL_IRQ_chg_timer_i_START (3)
#define SOC_SMART_COUL_IRQ_chg_timer_i_END (3)
#define SOC_SMART_COUL_IRQ_load_timer_i_START (4)
#define SOC_SMART_COUL_IRQ_load_timer_i_END (4)
#define SOC_SMART_COUL_IRQ_vbat_int_i_START (5)
#define SOC_SMART_COUL_IRQ_vbat_int_i_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otmp_d1r_mk : 1;
        unsigned char vsys_2p5_f_mk : 1;
        unsigned char vsys_uv_d2f_mk : 1;
        unsigned char vsys_6p0_d200ur_mk : 1;
        unsigned char pwron_d4sr_mk : 1;
        unsigned char pwron_d20f_mk : 1;
        unsigned char pwron_d20r_mk : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_IRQ1_MASK_UNION;
#endif
#define SOC_SMART_IRQ1_MASK_otmp_d1r_mk_START (0)
#define SOC_SMART_IRQ1_MASK_otmp_d1r_mk_END (0)
#define SOC_SMART_IRQ1_MASK_vsys_2p5_f_mk_START (1)
#define SOC_SMART_IRQ1_MASK_vsys_2p5_f_mk_END (1)
#define SOC_SMART_IRQ1_MASK_vsys_uv_d2f_mk_START (2)
#define SOC_SMART_IRQ1_MASK_vsys_uv_d2f_mk_END (2)
#define SOC_SMART_IRQ1_MASK_vsys_6p0_d200ur_mk_START (3)
#define SOC_SMART_IRQ1_MASK_vsys_6p0_d200ur_mk_END (3)
#define SOC_SMART_IRQ1_MASK_pwron_d4sr_mk_START (4)
#define SOC_SMART_IRQ1_MASK_pwron_d4sr_mk_END (4)
#define SOC_SMART_IRQ1_MASK_pwron_d20f_mk_START (5)
#define SOC_SMART_IRQ1_MASK_pwron_d20f_mk_END (5)
#define SOC_SMART_IRQ1_MASK_pwron_d20r_mk_START (6)
#define SOC_SMART_IRQ1_MASK_pwron_d20r_mk_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_scp_r_mk : 1;
        unsigned char vbus_det_1p375_mk : 1;
        unsigned char vbus_det_0p9_d3f_mk : 1;
        unsigned char vbus_det_0p9_d3r_mk : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_IRQ2_MASK_UNION;
#endif
#define SOC_SMART_IRQ2_MASK_ocp_scp_r_mk_START (0)
#define SOC_SMART_IRQ2_MASK_ocp_scp_r_mk_END (0)
#define SOC_SMART_IRQ2_MASK_vbus_det_1p375_mk_START (1)
#define SOC_SMART_IRQ2_MASK_vbus_det_1p375_mk_END (1)
#define SOC_SMART_IRQ2_MASK_vbus_det_0p9_d3f_mk_START (2)
#define SOC_SMART_IRQ2_MASK_vbus_det_0p9_d3f_mk_END (2)
#define SOC_SMART_IRQ2_MASK_vbus_det_0p9_d3r_mk_START (3)
#define SOC_SMART_IRQ2_MASK_vbus_det_0p9_d3r_mk_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char alarm_on_a_mk : 1;
        unsigned char alarm_on_b_mk : 1;
        unsigned char alarm_on_c_mk : 1;
        unsigned char alarm_on_d_mk : 1;
        unsigned char alarm_on_e_mk : 1;
        unsigned char alarm_on_f_mk : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_IRQ3_MASK_UNION;
#endif
#define SOC_SMART_IRQ3_MASK_alarm_on_a_mk_START (0)
#define SOC_SMART_IRQ3_MASK_alarm_on_a_mk_END (0)
#define SOC_SMART_IRQ3_MASK_alarm_on_b_mk_START (1)
#define SOC_SMART_IRQ3_MASK_alarm_on_b_mk_END (1)
#define SOC_SMART_IRQ3_MASK_alarm_on_c_mk_START (2)
#define SOC_SMART_IRQ3_MASK_alarm_on_c_mk_END (2)
#define SOC_SMART_IRQ3_MASK_alarm_on_d_mk_START (3)
#define SOC_SMART_IRQ3_MASK_alarm_on_d_mk_END (3)
#define SOC_SMART_IRQ3_MASK_alarm_on_e_mk_START (4)
#define SOC_SMART_IRQ3_MASK_alarm_on_e_mk_END (4)
#define SOC_SMART_IRQ3_MASK_alarm_on_f_mk_START (5)
#define SOC_SMART_IRQ3_MASK_alarm_on_f_mk_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char sim0_hpd_out_f_mk : 1;
        unsigned char sim0_hpd_out_r_mk : 1;
        unsigned char sim0_hpd_in_f_mk : 1;
        unsigned char sim0_hpd_in_r_mk : 1;
        unsigned char sim1_hpd_out_f_mk : 1;
        unsigned char sim1_hpd_out_r_mk : 1;
        unsigned char sim1_hpd_in_f_mk : 1;
        unsigned char sim1_in_hpd_r_mk : 1;
    } reg;
} SOC_SMART_IRQ4_MASK_UNION;
#endif
#define SOC_SMART_IRQ4_MASK_sim0_hpd_out_f_mk_START (0)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_out_f_mk_END (0)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_out_r_mk_START (1)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_out_r_mk_END (1)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_in_f_mk_START (2)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_in_f_mk_END (2)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_in_r_mk_START (3)
#define SOC_SMART_IRQ4_MASK_sim0_hpd_in_r_mk_END (3)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_out_f_mk_START (4)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_out_f_mk_END (4)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_out_r_mk_START (5)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_out_r_mk_END (5)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_in_f_mk_START (6)
#define SOC_SMART_IRQ4_MASK_sim1_hpd_in_f_mk_END (6)
#define SOC_SMART_IRQ4_MASK_sim1_in_hpd_r_mk_START (7)
#define SOC_SMART_IRQ4_MASK_sim1_in_hpd_r_mk_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int_i_mk : 1;
        unsigned char cl_out_i_mk : 1;
        unsigned char cl_in_i_mk : 1;
        unsigned char chg_timer_i_mk : 1;
        unsigned char load_timer_i_mk : 1;
        unsigned char vbat_int_i_mk : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_COUL_IRQ_MASK_UNION;
#endif
#define SOC_SMART_COUL_IRQ_MASK_cl_int_i_mk_START (0)
#define SOC_SMART_COUL_IRQ_MASK_cl_int_i_mk_END (0)
#define SOC_SMART_COUL_IRQ_MASK_cl_out_i_mk_START (1)
#define SOC_SMART_COUL_IRQ_MASK_cl_out_i_mk_END (1)
#define SOC_SMART_COUL_IRQ_MASK_cl_in_i_mk_START (2)
#define SOC_SMART_COUL_IRQ_MASK_cl_in_i_mk_END (2)
#define SOC_SMART_COUL_IRQ_MASK_chg_timer_i_mk_START (3)
#define SOC_SMART_COUL_IRQ_MASK_chg_timer_i_mk_END (3)
#define SOC_SMART_COUL_IRQ_MASK_load_timer_i_mk_START (4)
#define SOC_SMART_COUL_IRQ_MASK_load_timer_i_mk_END (4)
#define SOC_SMART_COUL_IRQ_MASK_vbat_int_i_mk_START (5)
#define SOC_SMART_COUL_IRQ_MASK_vbat_int_i_mk_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char scp_buck0_1 : 1;
        unsigned char scp_buck2 : 1;
        unsigned char scp_buck3 : 1;
        unsigned char scp_buck4 : 1;
        unsigned char scp_buck5 : 1;
        unsigned char scp_buck6 : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_SCP_RECORD1_UNION;
#endif
#define SOC_SMART_SCP_RECORD1_scp_buck0_1_START (0)
#define SOC_SMART_SCP_RECORD1_scp_buck0_1_END (0)
#define SOC_SMART_SCP_RECORD1_scp_buck2_START (1)
#define SOC_SMART_SCP_RECORD1_scp_buck2_END (1)
#define SOC_SMART_SCP_RECORD1_scp_buck3_START (2)
#define SOC_SMART_SCP_RECORD1_scp_buck3_END (2)
#define SOC_SMART_SCP_RECORD1_scp_buck4_START (3)
#define SOC_SMART_SCP_RECORD1_scp_buck4_END (3)
#define SOC_SMART_SCP_RECORD1_scp_buck5_START (4)
#define SOC_SMART_SCP_RECORD1_scp_buck5_END (4)
#define SOC_SMART_SCP_RECORD1_scp_buck6_START (5)
#define SOC_SMART_SCP_RECORD1_scp_buck6_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_buck0_1 : 1;
        unsigned char ocp_buck2 : 1;
        unsigned char ocp_buck3 : 1;
        unsigned char ocp_buck4 : 1;
        unsigned char ocp_buck5 : 1;
        unsigned char ocp_buck6 : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_OCP_RECORD1_UNION;
#endif
#define SOC_SMART_OCP_RECORD1_ocp_buck0_1_START (0)
#define SOC_SMART_OCP_RECORD1_ocp_buck0_1_END (0)
#define SOC_SMART_OCP_RECORD1_ocp_buck2_START (1)
#define SOC_SMART_OCP_RECORD1_ocp_buck2_END (1)
#define SOC_SMART_OCP_RECORD1_ocp_buck3_START (2)
#define SOC_SMART_OCP_RECORD1_ocp_buck3_END (2)
#define SOC_SMART_OCP_RECORD1_ocp_buck4_START (3)
#define SOC_SMART_OCP_RECORD1_ocp_buck4_END (3)
#define SOC_SMART_OCP_RECORD1_ocp_buck5_START (4)
#define SOC_SMART_OCP_RECORD1_ocp_buck5_END (4)
#define SOC_SMART_OCP_RECORD1_ocp_buck6_START (5)
#define SOC_SMART_OCP_RECORD1_ocp_buck6_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ldo1 : 1;
        unsigned char ocp_ldo2 : 1;
        unsigned char ocp_ldo3 : 1;
        unsigned char ocp_ldo4 : 1;
        unsigned char ocp_ldo5 : 1;
        unsigned char ocp_ldo6 : 1;
        unsigned char ocp_ldo7 : 1;
        unsigned char ocp_ldo8 : 1;
    } reg;
} SOC_SMART_OCP_RECORD2_UNION;
#endif
#define SOC_SMART_OCP_RECORD2_ocp_ldo1_START (0)
#define SOC_SMART_OCP_RECORD2_ocp_ldo1_END (0)
#define SOC_SMART_OCP_RECORD2_ocp_ldo2_START (1)
#define SOC_SMART_OCP_RECORD2_ocp_ldo2_END (1)
#define SOC_SMART_OCP_RECORD2_ocp_ldo3_START (2)
#define SOC_SMART_OCP_RECORD2_ocp_ldo3_END (2)
#define SOC_SMART_OCP_RECORD2_ocp_ldo4_START (3)
#define SOC_SMART_OCP_RECORD2_ocp_ldo4_END (3)
#define SOC_SMART_OCP_RECORD2_ocp_ldo5_START (4)
#define SOC_SMART_OCP_RECORD2_ocp_ldo5_END (4)
#define SOC_SMART_OCP_RECORD2_ocp_ldo6_START (5)
#define SOC_SMART_OCP_RECORD2_ocp_ldo6_END (5)
#define SOC_SMART_OCP_RECORD2_ocp_ldo7_START (6)
#define SOC_SMART_OCP_RECORD2_ocp_ldo7_END (6)
#define SOC_SMART_OCP_RECORD2_ocp_ldo8_START (7)
#define SOC_SMART_OCP_RECORD2_ocp_ldo8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ldo9 : 1;
        unsigned char ocp_ldo10 : 1;
        unsigned char ocp_ldo11 : 1;
        unsigned char ocp_ldo12 : 1;
        unsigned char ocp_ldo13 : 1;
        unsigned char ocp_ldo14 : 1;
        unsigned char ocp_ldo15 : 1;
        unsigned char ocp_ldo16 : 1;
    } reg;
} SOC_SMART_OCP_RECORD3_UNION;
#endif
#define SOC_SMART_OCP_RECORD3_ocp_ldo9_START (0)
#define SOC_SMART_OCP_RECORD3_ocp_ldo9_END (0)
#define SOC_SMART_OCP_RECORD3_ocp_ldo10_START (1)
#define SOC_SMART_OCP_RECORD3_ocp_ldo10_END (1)
#define SOC_SMART_OCP_RECORD3_ocp_ldo11_START (2)
#define SOC_SMART_OCP_RECORD3_ocp_ldo11_END (2)
#define SOC_SMART_OCP_RECORD3_ocp_ldo12_START (3)
#define SOC_SMART_OCP_RECORD3_ocp_ldo12_END (3)
#define SOC_SMART_OCP_RECORD3_ocp_ldo13_START (4)
#define SOC_SMART_OCP_RECORD3_ocp_ldo13_END (4)
#define SOC_SMART_OCP_RECORD3_ocp_ldo14_START (5)
#define SOC_SMART_OCP_RECORD3_ocp_ldo14_END (5)
#define SOC_SMART_OCP_RECORD3_ocp_ldo15_START (6)
#define SOC_SMART_OCP_RECORD3_ocp_ldo15_END (6)
#define SOC_SMART_OCP_RECORD3_ocp_ldo16_START (7)
#define SOC_SMART_OCP_RECORD3_ocp_ldo16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ldo17 : 1;
        unsigned char ocp_ldo18 : 1;
        unsigned char ocp_ldo19 : 1;
        unsigned char ocp_ldo20 : 1;
        unsigned char ocp_ldo21 : 1;
        unsigned char ocp_ldo22 : 1;
        unsigned char ocp_ldo23 : 1;
        unsigned char ocp_ldo24 : 1;
    } reg;
} SOC_SMART_OCP_RECORD4_UNION;
#endif
#define SOC_SMART_OCP_RECORD4_ocp_ldo17_START (0)
#define SOC_SMART_OCP_RECORD4_ocp_ldo17_END (0)
#define SOC_SMART_OCP_RECORD4_ocp_ldo18_START (1)
#define SOC_SMART_OCP_RECORD4_ocp_ldo18_END (1)
#define SOC_SMART_OCP_RECORD4_ocp_ldo19_START (2)
#define SOC_SMART_OCP_RECORD4_ocp_ldo19_END (2)
#define SOC_SMART_OCP_RECORD4_ocp_ldo20_START (3)
#define SOC_SMART_OCP_RECORD4_ocp_ldo20_END (3)
#define SOC_SMART_OCP_RECORD4_ocp_ldo21_START (4)
#define SOC_SMART_OCP_RECORD4_ocp_ldo21_END (4)
#define SOC_SMART_OCP_RECORD4_ocp_ldo22_START (5)
#define SOC_SMART_OCP_RECORD4_ocp_ldo22_END (5)
#define SOC_SMART_OCP_RECORD4_ocp_ldo23_START (6)
#define SOC_SMART_OCP_RECORD4_ocp_ldo23_END (6)
#define SOC_SMART_OCP_RECORD4_ocp_ldo24_START (7)
#define SOC_SMART_OCP_RECORD4_ocp_ldo24_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_lvs2 : 1;
        unsigned char ocp_lvs3 : 1;
        unsigned char ocp_lvs4 : 1;
        unsigned char ocp_lvs5 : 1;
        unsigned char ocp_lvs7 : 1;
        unsigned char ocp_lvs6 : 1;
        unsigned char ocp_lvs8 : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_OCP_RECORD5_UNION;
#endif
#define SOC_SMART_OCP_RECORD5_ocp_lvs2_START (0)
#define SOC_SMART_OCP_RECORD5_ocp_lvs2_END (0)
#define SOC_SMART_OCP_RECORD5_ocp_lvs3_START (1)
#define SOC_SMART_OCP_RECORD5_ocp_lvs3_END (1)
#define SOC_SMART_OCP_RECORD5_ocp_lvs4_START (2)
#define SOC_SMART_OCP_RECORD5_ocp_lvs4_END (2)
#define SOC_SMART_OCP_RECORD5_ocp_lvs5_START (3)
#define SOC_SMART_OCP_RECORD5_ocp_lvs5_END (3)
#define SOC_SMART_OCP_RECORD5_ocp_lvs7_START (4)
#define SOC_SMART_OCP_RECORD5_ocp_lvs7_END (4)
#define SOC_SMART_OCP_RECORD5_ocp_lvs6_START (5)
#define SOC_SMART_OCP_RECORD5_ocp_lvs6_END (5)
#define SOC_SMART_OCP_RECORD5_ocp_lvs8_START (6)
#define SOC_SMART_OCP_RECORD5_ocp_lvs8_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_lvs9 : 1;
        unsigned char ocp_lvs10 : 1;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_OCP_RECORD6_UNION;
#endif
#define SOC_SMART_OCP_RECORD6_ocp_lvs9_START (0)
#define SOC_SMART_OCP_RECORD6_ocp_lvs9_END (0)
#define SOC_SMART_OCP_RECORD6_ocp_lvs10_START (1)
#define SOC_SMART_OCP_RECORD6_ocp_lvs10_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_boost : 1;
        unsigned char scp_boost : 1;
        unsigned char ovp_boost : 1;
        unsigned char uvp_boost : 1;
        unsigned char ocp_classd : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_OCP_RECORD7_UNION;
#endif
#define SOC_SMART_OCP_RECORD7_ocp_boost_START (0)
#define SOC_SMART_OCP_RECORD7_ocp_boost_END (0)
#define SOC_SMART_OCP_RECORD7_scp_boost_START (1)
#define SOC_SMART_OCP_RECORD7_scp_boost_END (1)
#define SOC_SMART_OCP_RECORD7_ovp_boost_START (2)
#define SOC_SMART_OCP_RECORD7_ovp_boost_END (2)
#define SOC_SMART_OCP_RECORD7_uvp_boost_START (3)
#define SOC_SMART_OCP_RECORD7_uvp_boost_END (3)
#define SOC_SMART_OCP_RECORD7_ocp_classd_START (4)
#define SOC_SMART_OCP_RECORD7_ocp_classd_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_otmp_d1r : 1;
        unsigned char np_hreset_n_f : 1;
        unsigned char np_vsys_2p5_f : 1;
        unsigned char np_vsys_uv_d2f : 1;
        unsigned char np_vsys_6p0_d200ur : 1;
        unsigned char np_pwron_d4sr : 1;
        unsigned char np_pwron_d20f : 1;
        unsigned char np_pwron_d20r : 1;
    } reg;
} SOC_SMART_NP_IRQ1_RECORD_UNION;
#endif
#define SOC_SMART_NP_IRQ1_RECORD_np_otmp_d1r_START (0)
#define SOC_SMART_NP_IRQ1_RECORD_np_otmp_d1r_END (0)
#define SOC_SMART_NP_IRQ1_RECORD_np_hreset_n_f_START (1)
#define SOC_SMART_NP_IRQ1_RECORD_np_hreset_n_f_END (1)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_2p5_f_START (2)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_2p5_f_END (2)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_uv_d2f_START (3)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_uv_d2f_END (3)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_6p0_d200ur_START (4)
#define SOC_SMART_NP_IRQ1_RECORD_np_vsys_6p0_d200ur_END (4)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d4sr_START (5)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d4sr_END (5)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d20f_START (6)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d20f_END (6)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d20r_START (7)
#define SOC_SMART_NP_IRQ1_RECORD_np_pwron_d20r_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_vbus_det_0p9_d150r : 1;
        unsigned char np_vbus_det_1p375 : 1;
        unsigned char np_vbus_det_0p9_d3f : 1;
        unsigned char np_vbus_det_0p9_d3r : 1;
        unsigned char np_pwron_restart : 1;
        unsigned char np_pwron_dnsr : 1;
        unsigned char np_pwron_d500r : 1;
        unsigned char np_otmp150_d1r : 1;
    } reg;
} SOC_SMART_NP_IRQ2_RECORD_UNION;
#endif
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d150r_START (0)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d150r_END (0)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_1p375_START (1)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_1p375_END (1)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d3f_START (2)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d3f_END (2)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d3r_START (3)
#define SOC_SMART_NP_IRQ2_RECORD_np_vbus_det_0p9_d3r_END (3)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_restart_START (4)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_restart_END (4)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_dnsr_START (5)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_dnsr_END (5)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_d500r_START (6)
#define SOC_SMART_NP_IRQ2_RECORD_np_pwron_d500r_END (6)
#define SOC_SMART_NP_IRQ2_RECORD_np_otmp150_d1r_START (7)
#define SOC_SMART_NP_IRQ2_RECORD_np_otmp150_d1r_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_alarm_on_a : 1;
        unsigned char np_alarm_on_b : 1;
        unsigned char np_alarm_on_c : 1;
        unsigned char np_alarm_on_d : 1;
        unsigned char np_alarm_on_e : 1;
        unsigned char np_alarm_on_f : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_NP_IRQ3_RECORD_UNION;
#endif
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_a_START (0)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_a_END (0)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_b_START (1)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_b_END (1)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_c_START (2)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_c_END (2)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_d_START (3)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_d_END (3)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_e_START (4)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_e_END (4)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_f_START (5)
#define SOC_SMART_NP_IRQ3_RECORD_np_alarm_on_f_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_scp_buck0_1 : 1;
        unsigned char np_scp_buck2 : 1;
        unsigned char np_scp_buck3 : 1;
        unsigned char np_scp_buck4 : 1;
        unsigned char np_scp_buck5 : 1;
        unsigned char np_scp_buck6 : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_NP_SCP_RECORD1_UNION;
#endif
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck0_1_START (0)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck0_1_END (0)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck2_START (1)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck2_END (1)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck3_START (2)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck3_END (2)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck4_START (3)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck4_END (3)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck5_START (4)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck5_END (4)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck6_START (5)
#define SOC_SMART_NP_SCP_RECORD1_np_scp_buck6_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_buck0 : 1;
        unsigned char np_ocp_buck1 : 1;
        unsigned char np_ocp_buck0_1 : 1;
        unsigned char np_ocp_buck2 : 1;
        unsigned char np_ocp_buck3 : 1;
        unsigned char np_ocp_buck4 : 1;
        unsigned char np_ocp_buck5 : 1;
        unsigned char np_ocp_buck6 : 1;
    } reg;
} SOC_SMART_NP_OCP_RECORD1_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck0_START (0)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck0_END (0)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck1_START (1)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck1_END (1)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck0_1_START (2)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck0_1_END (2)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck2_START (3)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck2_END (3)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck3_START (4)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck3_END (4)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck4_START (5)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck4_END (5)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck5_START (6)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck5_END (6)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck6_START (7)
#define SOC_SMART_NP_OCP_RECORD1_np_ocp_buck6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_ldo1 : 1;
        unsigned char np_ocp_ldo2 : 1;
        unsigned char np_ocp_ldo3 : 1;
        unsigned char np_ocp_ldo4 : 1;
        unsigned char np_ocp_ldo5 : 1;
        unsigned char np_ocp_ldo6 : 1;
        unsigned char np_ocp_ldo7 : 1;
        unsigned char np_ocp_ldo8 : 1;
    } reg;
} SOC_SMART_NP_OCP_RECORD2_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo1_START (0)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo1_END (0)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo2_START (1)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo2_END (1)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo3_START (2)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo3_END (2)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo4_START (3)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo4_END (3)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo5_START (4)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo5_END (4)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo6_START (5)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo6_END (5)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo7_START (6)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo7_END (6)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo8_START (7)
#define SOC_SMART_NP_OCP_RECORD2_np_ocp_ldo8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_ldo9 : 1;
        unsigned char np_ocp_ldo10 : 1;
        unsigned char np_ocp_ldo11 : 1;
        unsigned char np_ocp_ldo12 : 1;
        unsigned char np_ocp_ldo13 : 1;
        unsigned char np_ocp_ldo14 : 1;
        unsigned char np_ocp_ldo15 : 1;
        unsigned char np_ocp_ldo16 : 1;
    } reg;
} SOC_SMART_NP_OCP_RECORD3_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo9_START (0)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo9_END (0)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo10_START (1)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo10_END (1)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo11_START (2)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo11_END (2)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo12_START (3)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo12_END (3)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo13_START (4)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo13_END (4)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo14_START (5)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo14_END (5)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo15_START (6)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo15_END (6)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo16_START (7)
#define SOC_SMART_NP_OCP_RECORD3_np_ocp_ldo16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_ldo17 : 1;
        unsigned char np_ocp_ldo18 : 1;
        unsigned char np_ocp_ldo19 : 1;
        unsigned char np_ocp_ldo20 : 1;
        unsigned char np_ocp_ldo21 : 1;
        unsigned char np_ocp_ldo22 : 1;
        unsigned char np_ocp_ldo23 : 1;
        unsigned char np_ocp_ldo24 : 1;
    } reg;
} SOC_SMART_NP_OCP_RECORD4_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo17_START (0)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo17_END (0)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo18_START (1)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo18_END (1)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo19_START (2)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo19_END (2)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo20_START (3)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo20_END (3)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo21_START (4)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo21_END (4)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo22_START (5)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo22_END (5)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo23_START (6)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo23_END (6)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo24_START (7)
#define SOC_SMART_NP_OCP_RECORD4_np_ocp_ldo24_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_lvs2 : 1;
        unsigned char np_ocp_lvs3 : 1;
        unsigned char np_ocp_lvs4 : 1;
        unsigned char np_ocp_lvs5 : 1;
        unsigned char np_ocp_lvs7 : 1;
        unsigned char np_ocp_lvs6 : 1;
        unsigned char np_ocp_lvs8 : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_NP_OCP_RECORD5_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs2_START (0)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs2_END (0)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs3_START (1)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs3_END (1)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs4_START (2)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs4_END (2)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs5_START (3)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs5_END (3)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs7_START (4)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs7_END (4)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs6_START (5)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs6_END (5)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs8_START (6)
#define SOC_SMART_NP_OCP_RECORD5_np_ocp_lvs8_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_lvs9 : 1;
        unsigned char np_ocp_lvs10 : 1;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_NP_OCP_RECORD6_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD6_np_ocp_lvs9_START (0)
#define SOC_SMART_NP_OCP_RECORD6_np_ocp_lvs9_END (0)
#define SOC_SMART_NP_OCP_RECORD6_np_ocp_lvs10_START (1)
#define SOC_SMART_NP_OCP_RECORD6_np_ocp_lvs10_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char np_ocp_boost : 1;
        unsigned char np_scp_boost : 1;
        unsigned char np_ovp_boost : 1;
        unsigned char np_uvp_boost : 1;
        unsigned char np_ocp_classd : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_NP_OCP_RECORD7_UNION;
#endif
#define SOC_SMART_NP_OCP_RECORD7_np_ocp_boost_START (0)
#define SOC_SMART_NP_OCP_RECORD7_np_ocp_boost_END (0)
#define SOC_SMART_NP_OCP_RECORD7_np_scp_boost_START (1)
#define SOC_SMART_NP_OCP_RECORD7_np_scp_boost_END (1)
#define SOC_SMART_NP_OCP_RECORD7_np_ovp_boost_START (2)
#define SOC_SMART_NP_OCP_RECORD7_np_ovp_boost_END (2)
#define SOC_SMART_NP_OCP_RECORD7_np_uvp_boost_START (3)
#define SOC_SMART_NP_OCP_RECORD7_np_uvp_boost_END (3)
#define SOC_SMART_NP_OCP_RECORD7_np_ocp_classd_START (4)
#define SOC_SMART_NP_OCP_RECORD7_np_ocp_classd_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ldo_deb_sel : 2;
        unsigned char en_ldo_ocp_deb : 1;
        unsigned char ocp_buck_deb_sel : 2;
        unsigned char en_buck_ocp_deb : 1;
        unsigned char en_buck_scp_deb : 1;
        unsigned char en_bst_ocp_deb : 1;
    } reg;
} SOC_SMART_OCP_DEB_UNION;
#endif
#define SOC_SMART_OCP_DEB_ocp_ldo_deb_sel_START (0)
#define SOC_SMART_OCP_DEB_ocp_ldo_deb_sel_END (1)
#define SOC_SMART_OCP_DEB_en_ldo_ocp_deb_START (2)
#define SOC_SMART_OCP_DEB_en_ldo_ocp_deb_END (2)
#define SOC_SMART_OCP_DEB_ocp_buck_deb_sel_START (3)
#define SOC_SMART_OCP_DEB_ocp_buck_deb_sel_END (4)
#define SOC_SMART_OCP_DEB_en_buck_ocp_deb_START (5)
#define SOC_SMART_OCP_DEB_en_buck_ocp_deb_END (5)
#define SOC_SMART_OCP_DEB_en_buck_scp_deb_START (6)
#define SOC_SMART_OCP_DEB_en_buck_scp_deb_END (6)
#define SOC_SMART_OCP_DEB_en_bst_ocp_deb_START (7)
#define SOC_SMART_OCP_DEB_en_bst_ocp_deb_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vbus_det_0p9_ctrl : 1;
        unsigned char vsys_2p5_ctrl : 1;
        unsigned char vsys_uv_ctrl : 1;
        unsigned char vsys_6p0_ctrl : 1;
        unsigned char otmp150_ctrl : 1;
        unsigned char en_32kc : 1;
        unsigned char en_32kb : 1;
        unsigned char en_32ka : 1;
    } reg;
} SOC_SMART_ONOFF8_UNION;
#endif
#define SOC_SMART_ONOFF8_vbus_det_0p9_ctrl_START (0)
#define SOC_SMART_ONOFF8_vbus_det_0p9_ctrl_END (0)
#define SOC_SMART_ONOFF8_vsys_2p5_ctrl_START (1)
#define SOC_SMART_ONOFF8_vsys_2p5_ctrl_END (1)
#define SOC_SMART_ONOFF8_vsys_uv_ctrl_START (2)
#define SOC_SMART_ONOFF8_vsys_uv_ctrl_END (2)
#define SOC_SMART_ONOFF8_vsys_6p0_ctrl_START (3)
#define SOC_SMART_ONOFF8_vsys_6p0_ctrl_END (3)
#define SOC_SMART_ONOFF8_otmp150_ctrl_START (4)
#define SOC_SMART_ONOFF8_otmp150_ctrl_END (4)
#define SOC_SMART_ONOFF8_en_32kc_START (5)
#define SOC_SMART_ONOFF8_en_32kc_END (5)
#define SOC_SMART_ONOFF8_en_32kb_START (6)
#define SOC_SMART_ONOFF8_en_32kb_END (6)
#define SOC_SMART_ONOFF8_en_32ka_START (7)
#define SOC_SMART_ONOFF8_en_32ka_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_scp_ctrl_buck0_1 : 1;
        unsigned char ocp_scp_off_buck0_1 : 1;
        unsigned char ocp_scp_ctrl_buck2 : 1;
        unsigned char ocp_scp_off_buck2 : 1;
        unsigned char ocp_scp_ctrl_buck3 : 1;
        unsigned char ocp_scp_off_buck3 : 1;
        unsigned char ocp_scp_ctrl_buck4 : 1;
        unsigned char ocp_scp_off_buck4 : 1;
    } reg;
} SOC_SMART_OCP_SCP_MOD_CTRL1_UNION;
#endif
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck0_1_START (0)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck0_1_END (0)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck0_1_START (1)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck0_1_END (1)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck2_START (2)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck2_END (2)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck2_START (3)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck2_END (3)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck3_START (4)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck3_END (4)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck3_START (5)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck3_END (5)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck4_START (6)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_ctrl_buck4_END (6)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck4_START (7)
#define SOC_SMART_OCP_SCP_MOD_CTRL1_ocp_scp_off_buck4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_scp_ctrl_buck5 : 1;
        unsigned char ocp_scp_off_buck5 : 1;
        unsigned char ocp_scp_ctrl_buck6 : 1;
        unsigned char ocp_scp_off_buck6 : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_OCP_SCP_MOD_CTRL2_UNION;
#endif
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_ctrl_buck5_START (0)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_ctrl_buck5_END (0)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_off_buck5_START (1)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_off_buck5_END (1)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_ctrl_buck6_START (2)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_ctrl_buck6_END (2)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_off_buck6_START (3)
#define SOC_SMART_OCP_SCP_MOD_CTRL2_ocp_scp_off_buck6_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo1 : 1;
        unsigned char ocp_off_ldo1 : 1;
        unsigned char ocp_ctrl_ldo2 : 1;
        unsigned char ocp_off_ldo2 : 1;
        unsigned char ocp_ctrl_ldo3 : 1;
        unsigned char ocp_off_ldo3 : 1;
        unsigned char ocp_ctrl_ldo4 : 1;
        unsigned char ocp_off_ldo4 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL3_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo1_START (0)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo1_END (0)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo1_START (1)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo1_END (1)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo2_START (2)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo2_END (2)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo2_START (3)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo2_END (3)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo3_START (4)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo3_END (4)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo3_START (5)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo3_END (5)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo4_START (6)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_ctrl_ldo4_END (6)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo4_START (7)
#define SOC_SMART_OCP_MOD_CTRL3_ocp_off_ldo4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo5 : 1;
        unsigned char ocp_off_ldo5 : 1;
        unsigned char ocp_ctrl_ldo6 : 1;
        unsigned char ocp_off_ldo6 : 1;
        unsigned char ocp_ctrl_ldo7 : 1;
        unsigned char ocp_off_ldo7 : 1;
        unsigned char ocp_ctrl_ldo8 : 1;
        unsigned char ocp_off_ldo8 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL4_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo5_START (0)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo5_END (0)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo5_START (1)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo5_END (1)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo6_START (2)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo6_END (2)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo6_START (3)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo6_END (3)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo7_START (4)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo7_END (4)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo7_START (5)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo7_END (5)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo8_START (6)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_ctrl_ldo8_END (6)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo8_START (7)
#define SOC_SMART_OCP_MOD_CTRL4_ocp_off_ldo8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo9 : 1;
        unsigned char ocp_off_ldo9 : 1;
        unsigned char ocp_ctrl_ldo10 : 1;
        unsigned char ocp_off_ldo10 : 1;
        unsigned char ocp_ctrl_ldo11 : 1;
        unsigned char ocp_off_ldo11 : 1;
        unsigned char ocp_ctrl_ldo12 : 1;
        unsigned char ocp_off_ldo12 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL5_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo9_START (0)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo9_END (0)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo9_START (1)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo9_END (1)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo10_START (2)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo10_END (2)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo10_START (3)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo10_END (3)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo11_START (4)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo11_END (4)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo11_START (5)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo11_END (5)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo12_START (6)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_ctrl_ldo12_END (6)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo12_START (7)
#define SOC_SMART_OCP_MOD_CTRL5_ocp_off_ldo12_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo13 : 1;
        unsigned char ocp_off_ldo13 : 1;
        unsigned char ocp_ctrl_ldo14 : 1;
        unsigned char ocp_off_ldo14 : 1;
        unsigned char ocp_ctrl_ldo15 : 1;
        unsigned char ocp_off_ldo15 : 1;
        unsigned char ocp_ctrl_ldo16 : 1;
        unsigned char ocp_off_ldo16 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL6_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo13_START (0)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo13_END (0)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo13_START (1)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo13_END (1)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo14_START (2)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo14_END (2)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo14_START (3)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo14_END (3)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo15_START (4)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo15_END (4)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo15_START (5)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo15_END (5)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo16_START (6)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_ctrl_ldo16_END (6)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo16_START (7)
#define SOC_SMART_OCP_MOD_CTRL6_ocp_off_ldo16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo17 : 1;
        unsigned char ocp_off_ldo17 : 1;
        unsigned char ocp_ctrl_ldo18 : 1;
        unsigned char ocp_off_ldo18 : 1;
        unsigned char ocp_ctrl_ldo19 : 1;
        unsigned char ocp_off_ldo19 : 1;
        unsigned char ocp_ctrl_ldo20 : 1;
        unsigned char ocp_off_ldo20 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL7_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo17_START (0)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo17_END (0)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo17_START (1)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo17_END (1)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo18_START (2)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo18_END (2)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo18_START (3)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo18_END (3)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo19_START (4)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo19_END (4)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo19_START (5)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo19_END (5)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo20_START (6)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_ctrl_ldo20_END (6)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo20_START (7)
#define SOC_SMART_OCP_MOD_CTRL7_ocp_off_ldo20_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_ldo21 : 1;
        unsigned char ocp_off_ldo21 : 1;
        unsigned char ocp_ctrl_ldo22 : 1;
        unsigned char ocp_off_ldo22 : 1;
        unsigned char ocp_ctrl_ldo23 : 1;
        unsigned char ocp_off_ldo23 : 1;
        unsigned char ocp_ctrl_ldo24 : 1;
        unsigned char ocp_off_ldo24 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL8_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo21_START (0)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo21_END (0)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo21_START (1)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo21_END (1)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo22_START (2)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo22_END (2)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo22_START (3)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo22_END (3)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo23_START (4)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo23_END (4)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo23_START (5)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo23_END (5)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo24_START (6)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_ctrl_ldo24_END (6)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo24_START (7)
#define SOC_SMART_OCP_MOD_CTRL8_ocp_off_ldo24_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_lvs2 : 1;
        unsigned char ocp_off_lvs2 : 1;
        unsigned char ocp_ctrl_lvs3 : 1;
        unsigned char ocp_off_lvs3 : 1;
        unsigned char ocp_ctrl_lvs4 : 1;
        unsigned char ocp_off_lvs4 : 1;
        unsigned char ocp_ctrl_lvs5 : 1;
        unsigned char ocp_off_lvs5 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL9_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs2_START (0)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs2_END (0)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs2_START (1)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs2_END (1)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs3_START (2)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs3_END (2)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs3_START (3)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs3_END (3)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs4_START (4)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs4_END (4)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs4_START (5)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs4_END (5)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs5_START (6)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_ctrl_lvs5_END (6)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs5_START (7)
#define SOC_SMART_OCP_MOD_CTRL9_ocp_off_lvs5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_lvs7 : 1;
        unsigned char ocp_off_lvs7 : 1;
        unsigned char ocp_ctrl_lvs6 : 1;
        unsigned char ocp_off_lvs6 : 1;
        unsigned char ocp_ctrl_lvs8 : 1;
        unsigned char ocp_off_lvs8 : 1;
        unsigned char ocp_ctrl_lvs9 : 1;
        unsigned char ocp_off_lvs9 : 1;
    } reg;
} SOC_SMART_OCP_MOD_CTRL10_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs7_START (0)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs7_END (0)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs7_START (1)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs7_END (1)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs6_START (2)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs6_END (2)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs6_START (3)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs6_END (3)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs8_START (4)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs8_END (4)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs8_START (5)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs8_END (5)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs9_START (6)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_ctrl_lvs9_END (6)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs9_START (7)
#define SOC_SMART_OCP_MOD_CTRL10_ocp_off_lvs9_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocp_ctrl_lvs10 : 1;
        unsigned char ocp_off_lvs10 : 1;
        unsigned char ocp_ctrl_bst : 1;
        unsigned char ocp_off_bst : 1;
        unsigned char ocp_ctrl_classd : 1;
        unsigned char ocp_off_classd : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_OCP_MOD_CTRL11_UNION;
#endif
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_lvs10_START (0)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_lvs10_END (0)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_lvs10_START (1)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_lvs10_END (1)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_bst_START (2)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_bst_END (2)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_bst_START (3)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_bst_END (3)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_classd_START (4)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_ctrl_classd_END (4)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_classd_START (5)
#define SOC_SMART_OCP_MOD_CTRL11_ocp_off_classd_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_buck0_int : 1;
        unsigned char en_buck1_int : 1;
        unsigned char en_buck2_int : 1;
        unsigned char en_buck3_int : 1;
        unsigned char en_buck4_int : 1;
        unsigned char en_buck5_int : 1;
        unsigned char en_buck6_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_ENABLE1_UNION;
#endif
#define SOC_SMART_ENABLE1_en_buck0_int_START (0)
#define SOC_SMART_ENABLE1_en_buck0_int_END (0)
#define SOC_SMART_ENABLE1_en_buck1_int_START (1)
#define SOC_SMART_ENABLE1_en_buck1_int_END (1)
#define SOC_SMART_ENABLE1_en_buck2_int_START (2)
#define SOC_SMART_ENABLE1_en_buck2_int_END (2)
#define SOC_SMART_ENABLE1_en_buck3_int_START (3)
#define SOC_SMART_ENABLE1_en_buck3_int_END (3)
#define SOC_SMART_ENABLE1_en_buck4_int_START (4)
#define SOC_SMART_ENABLE1_en_buck4_int_END (4)
#define SOC_SMART_ENABLE1_en_buck5_int_START (5)
#define SOC_SMART_ENABLE1_en_buck5_int_END (5)
#define SOC_SMART_ENABLE1_en_buck6_int_START (6)
#define SOC_SMART_ENABLE1_en_buck6_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_buck0_int : 1;
        unsigned char dis_buck1_int : 1;
        unsigned char dis_buck2_int : 1;
        unsigned char dis_buck3_int : 1;
        unsigned char dis_buck4_int : 1;
        unsigned char dis_buck5_int : 1;
        unsigned char dis_buck6_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_DISABLE1_UNION;
#endif
#define SOC_SMART_DISABLE1_dis_buck0_int_START (0)
#define SOC_SMART_DISABLE1_dis_buck0_int_END (0)
#define SOC_SMART_DISABLE1_dis_buck1_int_START (1)
#define SOC_SMART_DISABLE1_dis_buck1_int_END (1)
#define SOC_SMART_DISABLE1_dis_buck2_int_START (2)
#define SOC_SMART_DISABLE1_dis_buck2_int_END (2)
#define SOC_SMART_DISABLE1_dis_buck3_int_START (3)
#define SOC_SMART_DISABLE1_dis_buck3_int_END (3)
#define SOC_SMART_DISABLE1_dis_buck4_int_START (4)
#define SOC_SMART_DISABLE1_dis_buck4_int_END (4)
#define SOC_SMART_DISABLE1_dis_buck5_int_START (5)
#define SOC_SMART_DISABLE1_dis_buck5_int_END (5)
#define SOC_SMART_DISABLE1_dis_buck6_int_START (6)
#define SOC_SMART_DISABLE1_dis_buck6_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_buck0_int : 1;
        unsigned char st_buck1_int : 1;
        unsigned char st_buck2_int : 1;
        unsigned char st_buck3_int : 1;
        unsigned char st_buck4_int : 1;
        unsigned char st_buck5_int : 1;
        unsigned char st_buck6_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_ONOFF_STATUS1_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS1_st_buck0_int_START (0)
#define SOC_SMART_ONOFF_STATUS1_st_buck0_int_END (0)
#define SOC_SMART_ONOFF_STATUS1_st_buck1_int_START (1)
#define SOC_SMART_ONOFF_STATUS1_st_buck1_int_END (1)
#define SOC_SMART_ONOFF_STATUS1_st_buck2_int_START (2)
#define SOC_SMART_ONOFF_STATUS1_st_buck2_int_END (2)
#define SOC_SMART_ONOFF_STATUS1_st_buck3_int_START (3)
#define SOC_SMART_ONOFF_STATUS1_st_buck3_int_END (3)
#define SOC_SMART_ONOFF_STATUS1_st_buck4_int_START (4)
#define SOC_SMART_ONOFF_STATUS1_st_buck4_int_END (4)
#define SOC_SMART_ONOFF_STATUS1_st_buck5_int_START (5)
#define SOC_SMART_ONOFF_STATUS1_st_buck5_int_END (5)
#define SOC_SMART_ONOFF_STATUS1_st_buck6_int_START (6)
#define SOC_SMART_ONOFF_STATUS1_st_buck6_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_ldo1_int : 1;
        unsigned char en_ldo2_int : 1;
        unsigned char en_ldo3_buck_int : 1;
        unsigned char en_ldo4_int : 1;
        unsigned char en_ldo5_int : 1;
        unsigned char en_ldo6_int : 1;
        unsigned char en_ldo7_int : 1;
        unsigned char en_ldo8_int : 1;
    } reg;
} SOC_SMART_ENABLE2_UNION;
#endif
#define SOC_SMART_ENABLE2_en_ldo1_int_START (0)
#define SOC_SMART_ENABLE2_en_ldo1_int_END (0)
#define SOC_SMART_ENABLE2_en_ldo2_int_START (1)
#define SOC_SMART_ENABLE2_en_ldo2_int_END (1)
#define SOC_SMART_ENABLE2_en_ldo3_buck_int_START (2)
#define SOC_SMART_ENABLE2_en_ldo3_buck_int_END (2)
#define SOC_SMART_ENABLE2_en_ldo4_int_START (3)
#define SOC_SMART_ENABLE2_en_ldo4_int_END (3)
#define SOC_SMART_ENABLE2_en_ldo5_int_START (4)
#define SOC_SMART_ENABLE2_en_ldo5_int_END (4)
#define SOC_SMART_ENABLE2_en_ldo6_int_START (5)
#define SOC_SMART_ENABLE2_en_ldo6_int_END (5)
#define SOC_SMART_ENABLE2_en_ldo7_int_START (6)
#define SOC_SMART_ENABLE2_en_ldo7_int_END (6)
#define SOC_SMART_ENABLE2_en_ldo8_int_START (7)
#define SOC_SMART_ENABLE2_en_ldo8_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_ldo1_int : 1;
        unsigned char dis_ldo2_int : 1;
        unsigned char dis_ldo3_buck_int : 1;
        unsigned char dis_ldo4_int : 1;
        unsigned char dis_ldo5_int : 1;
        unsigned char dis_ldo6_int : 1;
        unsigned char dis_ldo7_int : 1;
        unsigned char dis_ldo8_int : 1;
    } reg;
} SOC_SMART_DISABLE2_UNION;
#endif
#define SOC_SMART_DISABLE2_dis_ldo1_int_START (0)
#define SOC_SMART_DISABLE2_dis_ldo1_int_END (0)
#define SOC_SMART_DISABLE2_dis_ldo2_int_START (1)
#define SOC_SMART_DISABLE2_dis_ldo2_int_END (1)
#define SOC_SMART_DISABLE2_dis_ldo3_buck_int_START (2)
#define SOC_SMART_DISABLE2_dis_ldo3_buck_int_END (2)
#define SOC_SMART_DISABLE2_dis_ldo4_int_START (3)
#define SOC_SMART_DISABLE2_dis_ldo4_int_END (3)
#define SOC_SMART_DISABLE2_dis_ldo5_int_START (4)
#define SOC_SMART_DISABLE2_dis_ldo5_int_END (4)
#define SOC_SMART_DISABLE2_dis_ldo6_int_START (5)
#define SOC_SMART_DISABLE2_dis_ldo6_int_END (5)
#define SOC_SMART_DISABLE2_dis_ldo7_int_START (6)
#define SOC_SMART_DISABLE2_dis_ldo7_int_END (6)
#define SOC_SMART_DISABLE2_dis_ldo8_int_START (7)
#define SOC_SMART_DISABLE2_dis_ldo8_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_ldo1_int : 1;
        unsigned char st_ldo2_int : 1;
        unsigned char st_ldo3_buck_int : 1;
        unsigned char st_ldo4_int : 1;
        unsigned char st_ldo5_int : 1;
        unsigned char st_ldo6_int : 1;
        unsigned char st_ldo7_int : 1;
        unsigned char st_ldo8_int : 1;
    } reg;
} SOC_SMART_ONOFF_STATUS2_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS2_st_ldo1_int_START (0)
#define SOC_SMART_ONOFF_STATUS2_st_ldo1_int_END (0)
#define SOC_SMART_ONOFF_STATUS2_st_ldo2_int_START (1)
#define SOC_SMART_ONOFF_STATUS2_st_ldo2_int_END (1)
#define SOC_SMART_ONOFF_STATUS2_st_ldo3_buck_int_START (2)
#define SOC_SMART_ONOFF_STATUS2_st_ldo3_buck_int_END (2)
#define SOC_SMART_ONOFF_STATUS2_st_ldo4_int_START (3)
#define SOC_SMART_ONOFF_STATUS2_st_ldo4_int_END (3)
#define SOC_SMART_ONOFF_STATUS2_st_ldo5_int_START (4)
#define SOC_SMART_ONOFF_STATUS2_st_ldo5_int_END (4)
#define SOC_SMART_ONOFF_STATUS2_st_ldo6_int_START (5)
#define SOC_SMART_ONOFF_STATUS2_st_ldo6_int_END (5)
#define SOC_SMART_ONOFF_STATUS2_st_ldo7_int_START (6)
#define SOC_SMART_ONOFF_STATUS2_st_ldo7_int_END (6)
#define SOC_SMART_ONOFF_STATUS2_st_ldo8_int_START (7)
#define SOC_SMART_ONOFF_STATUS2_st_ldo8_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_ldo10_int : 1;
        unsigned char en_ldo12_int : 1;
        unsigned char en_ldo13_int : 1;
        unsigned char en_ldo14_int : 1;
        unsigned char en_ldo15_int : 1;
        unsigned char en_ldo16_int : 1;
        unsigned char en_ldo17_int : 1;
        unsigned char en_ldo18_int : 1;
    } reg;
} SOC_SMART_ENABLE3_UNION;
#endif
#define SOC_SMART_ENABLE3_en_ldo10_int_START (0)
#define SOC_SMART_ENABLE3_en_ldo10_int_END (0)
#define SOC_SMART_ENABLE3_en_ldo12_int_START (1)
#define SOC_SMART_ENABLE3_en_ldo12_int_END (1)
#define SOC_SMART_ENABLE3_en_ldo13_int_START (2)
#define SOC_SMART_ENABLE3_en_ldo13_int_END (2)
#define SOC_SMART_ENABLE3_en_ldo14_int_START (3)
#define SOC_SMART_ENABLE3_en_ldo14_int_END (3)
#define SOC_SMART_ENABLE3_en_ldo15_int_START (4)
#define SOC_SMART_ENABLE3_en_ldo15_int_END (4)
#define SOC_SMART_ENABLE3_en_ldo16_int_START (5)
#define SOC_SMART_ENABLE3_en_ldo16_int_END (5)
#define SOC_SMART_ENABLE3_en_ldo17_int_START (6)
#define SOC_SMART_ENABLE3_en_ldo17_int_END (6)
#define SOC_SMART_ENABLE3_en_ldo18_int_START (7)
#define SOC_SMART_ENABLE3_en_ldo18_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_ldo10_int : 1;
        unsigned char dis_ldo12_int : 1;
        unsigned char dis_ldo13_int : 1;
        unsigned char dis_ldo14_int : 1;
        unsigned char dis_ldo15_int : 1;
        unsigned char dis_ldo16_int : 1;
        unsigned char dis_ldo17_int : 1;
        unsigned char dis_ldo18_int : 1;
    } reg;
} SOC_SMART_DISABLE3_UNION;
#endif
#define SOC_SMART_DISABLE3_dis_ldo10_int_START (0)
#define SOC_SMART_DISABLE3_dis_ldo10_int_END (0)
#define SOC_SMART_DISABLE3_dis_ldo12_int_START (1)
#define SOC_SMART_DISABLE3_dis_ldo12_int_END (1)
#define SOC_SMART_DISABLE3_dis_ldo13_int_START (2)
#define SOC_SMART_DISABLE3_dis_ldo13_int_END (2)
#define SOC_SMART_DISABLE3_dis_ldo14_int_START (3)
#define SOC_SMART_DISABLE3_dis_ldo14_int_END (3)
#define SOC_SMART_DISABLE3_dis_ldo15_int_START (4)
#define SOC_SMART_DISABLE3_dis_ldo15_int_END (4)
#define SOC_SMART_DISABLE3_dis_ldo16_int_START (5)
#define SOC_SMART_DISABLE3_dis_ldo16_int_END (5)
#define SOC_SMART_DISABLE3_dis_ldo17_int_START (6)
#define SOC_SMART_DISABLE3_dis_ldo17_int_END (6)
#define SOC_SMART_DISABLE3_dis_ldo18_int_START (7)
#define SOC_SMART_DISABLE3_dis_ldo18_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_ldo10_int : 1;
        unsigned char st_ldo12_int : 1;
        unsigned char st_ldo13_int : 1;
        unsigned char st_ldo14_int : 1;
        unsigned char st_ldo15_int : 1;
        unsigned char st_ldo16_int : 1;
        unsigned char st_ldo17_int : 1;
        unsigned char st_ldo18_int : 1;
    } reg;
} SOC_SMART_ONOFF_STATUS3_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS3_st_ldo10_int_START (0)
#define SOC_SMART_ONOFF_STATUS3_st_ldo10_int_END (0)
#define SOC_SMART_ONOFF_STATUS3_st_ldo12_int_START (1)
#define SOC_SMART_ONOFF_STATUS3_st_ldo12_int_END (1)
#define SOC_SMART_ONOFF_STATUS3_st_ldo13_int_START (2)
#define SOC_SMART_ONOFF_STATUS3_st_ldo13_int_END (2)
#define SOC_SMART_ONOFF_STATUS3_st_ldo14_int_START (3)
#define SOC_SMART_ONOFF_STATUS3_st_ldo14_int_END (3)
#define SOC_SMART_ONOFF_STATUS3_st_ldo15_int_START (4)
#define SOC_SMART_ONOFF_STATUS3_st_ldo15_int_END (4)
#define SOC_SMART_ONOFF_STATUS3_st_ldo16_int_START (5)
#define SOC_SMART_ONOFF_STATUS3_st_ldo16_int_END (5)
#define SOC_SMART_ONOFF_STATUS3_st_ldo17_int_START (6)
#define SOC_SMART_ONOFF_STATUS3_st_ldo17_int_END (6)
#define SOC_SMART_ONOFF_STATUS3_st_ldo18_int_START (7)
#define SOC_SMART_ONOFF_STATUS3_st_ldo18_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_ldo19_int : 1;
        unsigned char en_ldo20_int : 1;
        unsigned char en_ldo21_int : 1;
        unsigned char en_ldo22_int : 1;
        unsigned char en_ldo23_int : 1;
        unsigned char en_ldo24_int : 1;
        unsigned char en_ldo3_batt_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_ENABLE4_UNION;
#endif
#define SOC_SMART_ENABLE4_en_ldo19_int_START (0)
#define SOC_SMART_ENABLE4_en_ldo19_int_END (0)
#define SOC_SMART_ENABLE4_en_ldo20_int_START (1)
#define SOC_SMART_ENABLE4_en_ldo20_int_END (1)
#define SOC_SMART_ENABLE4_en_ldo21_int_START (2)
#define SOC_SMART_ENABLE4_en_ldo21_int_END (2)
#define SOC_SMART_ENABLE4_en_ldo22_int_START (3)
#define SOC_SMART_ENABLE4_en_ldo22_int_END (3)
#define SOC_SMART_ENABLE4_en_ldo23_int_START (4)
#define SOC_SMART_ENABLE4_en_ldo23_int_END (4)
#define SOC_SMART_ENABLE4_en_ldo24_int_START (5)
#define SOC_SMART_ENABLE4_en_ldo24_int_END (5)
#define SOC_SMART_ENABLE4_en_ldo3_batt_int_START (6)
#define SOC_SMART_ENABLE4_en_ldo3_batt_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_ldo19_int : 1;
        unsigned char dis_ldo20_int : 1;
        unsigned char dis_ldo21_int : 1;
        unsigned char dis_ldo22_int : 1;
        unsigned char dis_ldo23_int : 1;
        unsigned char dis_ldo24_int : 1;
        unsigned char dis_ldo3_batt_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_DISABLE4_UNION;
#endif
#define SOC_SMART_DISABLE4_dis_ldo19_int_START (0)
#define SOC_SMART_DISABLE4_dis_ldo19_int_END (0)
#define SOC_SMART_DISABLE4_dis_ldo20_int_START (1)
#define SOC_SMART_DISABLE4_dis_ldo20_int_END (1)
#define SOC_SMART_DISABLE4_dis_ldo21_int_START (2)
#define SOC_SMART_DISABLE4_dis_ldo21_int_END (2)
#define SOC_SMART_DISABLE4_dis_ldo22_int_START (3)
#define SOC_SMART_DISABLE4_dis_ldo22_int_END (3)
#define SOC_SMART_DISABLE4_dis_ldo23_int_START (4)
#define SOC_SMART_DISABLE4_dis_ldo23_int_END (4)
#define SOC_SMART_DISABLE4_dis_ldo24_int_START (5)
#define SOC_SMART_DISABLE4_dis_ldo24_int_END (5)
#define SOC_SMART_DISABLE4_dis_ldo3_batt_int_START (6)
#define SOC_SMART_DISABLE4_dis_ldo3_batt_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_ldo19_int : 1;
        unsigned char st_ldo20_int : 1;
        unsigned char st_ldo21_int : 1;
        unsigned char st_ldo22_int : 1;
        unsigned char st_ldo23_int : 1;
        unsigned char st_ldo24_int : 1;
        unsigned char st_ldo3_batt_int : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_ONOFF_STATUS4_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS4_st_ldo19_int_START (0)
#define SOC_SMART_ONOFF_STATUS4_st_ldo19_int_END (0)
#define SOC_SMART_ONOFF_STATUS4_st_ldo20_int_START (1)
#define SOC_SMART_ONOFF_STATUS4_st_ldo20_int_END (1)
#define SOC_SMART_ONOFF_STATUS4_st_ldo21_int_START (2)
#define SOC_SMART_ONOFF_STATUS4_st_ldo21_int_END (2)
#define SOC_SMART_ONOFF_STATUS4_st_ldo22_int_START (3)
#define SOC_SMART_ONOFF_STATUS4_st_ldo22_int_END (3)
#define SOC_SMART_ONOFF_STATUS4_st_ldo23_int_START (4)
#define SOC_SMART_ONOFF_STATUS4_st_ldo23_int_END (4)
#define SOC_SMART_ONOFF_STATUS4_st_ldo24_int_START (5)
#define SOC_SMART_ONOFF_STATUS4_st_ldo24_int_END (5)
#define SOC_SMART_ONOFF_STATUS4_st_ldo3_batt_int_START (6)
#define SOC_SMART_ONOFF_STATUS4_st_ldo3_batt_int_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_lvs2_int : 1;
        unsigned char en_lvs3_int : 1;
        unsigned char en_lvs4_int : 1;
        unsigned char en_lvs5_int : 1;
        unsigned char en_lvs7_int : 1;
        unsigned char en_lvs6_int : 1;
        unsigned char en_lvs8_int : 1;
        unsigned char en_lvs9_int : 1;
    } reg;
} SOC_SMART_ENABLE5_UNION;
#endif
#define SOC_SMART_ENABLE5_en_lvs2_int_START (0)
#define SOC_SMART_ENABLE5_en_lvs2_int_END (0)
#define SOC_SMART_ENABLE5_en_lvs3_int_START (1)
#define SOC_SMART_ENABLE5_en_lvs3_int_END (1)
#define SOC_SMART_ENABLE5_en_lvs4_int_START (2)
#define SOC_SMART_ENABLE5_en_lvs4_int_END (2)
#define SOC_SMART_ENABLE5_en_lvs5_int_START (3)
#define SOC_SMART_ENABLE5_en_lvs5_int_END (3)
#define SOC_SMART_ENABLE5_en_lvs7_int_START (4)
#define SOC_SMART_ENABLE5_en_lvs7_int_END (4)
#define SOC_SMART_ENABLE5_en_lvs6_int_START (5)
#define SOC_SMART_ENABLE5_en_lvs6_int_END (5)
#define SOC_SMART_ENABLE5_en_lvs8_int_START (6)
#define SOC_SMART_ENABLE5_en_lvs8_int_END (6)
#define SOC_SMART_ENABLE5_en_lvs9_int_START (7)
#define SOC_SMART_ENABLE5_en_lvs9_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_lvs2_int : 1;
        unsigned char dis_lvs3_int : 1;
        unsigned char dis_lvs4_int : 1;
        unsigned char dis_lvs5_int : 1;
        unsigned char dis_lvs7_int : 1;
        unsigned char dis_lvs6_int : 1;
        unsigned char dis_lvs8_int : 1;
        unsigned char dis_lvs9_int : 1;
    } reg;
} SOC_SMART_DISABLE5_UNION;
#endif
#define SOC_SMART_DISABLE5_dis_lvs2_int_START (0)
#define SOC_SMART_DISABLE5_dis_lvs2_int_END (0)
#define SOC_SMART_DISABLE5_dis_lvs3_int_START (1)
#define SOC_SMART_DISABLE5_dis_lvs3_int_END (1)
#define SOC_SMART_DISABLE5_dis_lvs4_int_START (2)
#define SOC_SMART_DISABLE5_dis_lvs4_int_END (2)
#define SOC_SMART_DISABLE5_dis_lvs5_int_START (3)
#define SOC_SMART_DISABLE5_dis_lvs5_int_END (3)
#define SOC_SMART_DISABLE5_dis_lvs7_int_START (4)
#define SOC_SMART_DISABLE5_dis_lvs7_int_END (4)
#define SOC_SMART_DISABLE5_dis_lvs6_int_START (5)
#define SOC_SMART_DISABLE5_dis_lvs6_int_END (5)
#define SOC_SMART_DISABLE5_dis_lvs8_int_START (6)
#define SOC_SMART_DISABLE5_dis_lvs8_int_END (6)
#define SOC_SMART_DISABLE5_dis_lvs9_int_START (7)
#define SOC_SMART_DISABLE5_dis_lvs9_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_lvs2_int : 1;
        unsigned char st_lvs3_int : 1;
        unsigned char st_lvs4_int : 1;
        unsigned char st_lvs5_int : 1;
        unsigned char st_lvs7_int : 1;
        unsigned char st_lvs6_int : 1;
        unsigned char st_lvs8_int : 1;
        unsigned char st_lvs9_int : 1;
    } reg;
} SOC_SMART_ONOFF_STATUS5_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS5_st_lvs2_int_START (0)
#define SOC_SMART_ONOFF_STATUS5_st_lvs2_int_END (0)
#define SOC_SMART_ONOFF_STATUS5_st_lvs3_int_START (1)
#define SOC_SMART_ONOFF_STATUS5_st_lvs3_int_END (1)
#define SOC_SMART_ONOFF_STATUS5_st_lvs4_int_START (2)
#define SOC_SMART_ONOFF_STATUS5_st_lvs4_int_END (2)
#define SOC_SMART_ONOFF_STATUS5_st_lvs5_int_START (3)
#define SOC_SMART_ONOFF_STATUS5_st_lvs5_int_END (3)
#define SOC_SMART_ONOFF_STATUS5_st_lvs7_int_START (4)
#define SOC_SMART_ONOFF_STATUS5_st_lvs7_int_END (4)
#define SOC_SMART_ONOFF_STATUS5_st_lvs6_int_START (5)
#define SOC_SMART_ONOFF_STATUS5_st_lvs6_int_END (5)
#define SOC_SMART_ONOFF_STATUS5_st_lvs8_int_START (6)
#define SOC_SMART_ONOFF_STATUS5_st_lvs8_int_END (6)
#define SOC_SMART_ONOFF_STATUS5_st_lvs9_int_START (7)
#define SOC_SMART_ONOFF_STATUS5_st_lvs9_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_lvs10_int : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_ENABLE6_UNION;
#endif
#define SOC_SMART_ENABLE6_en_lvs10_int_START (0)
#define SOC_SMART_ENABLE6_en_lvs10_int_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dis_lvs10_int : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_DISABLE6_UNION;
#endif
#define SOC_SMART_DISABLE6_dis_lvs10_int_START (0)
#define SOC_SMART_DISABLE6_dis_lvs10_int_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char st_lvs10_int : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_ONOFF_STATUS6_UNION;
#endif
#define SOC_SMART_ONOFF_STATUS6_st_lvs10_int_START (0)
#define SOC_SMART_ONOFF_STATUS6_st_lvs10_int_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_cp2_int : 1;
        unsigned char cp2_always_on_int : 1;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_ENABLE7_UNION;
#endif
#define SOC_SMART_ENABLE7_en_cp2_int_START (0)
#define SOC_SMART_ENABLE7_en_cp2_int_END (0)
#define SOC_SMART_ENABLE7_cp2_always_on_int_START (1)
#define SOC_SMART_ENABLE7_cp2_always_on_int_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_ldo9_int : 1;
        unsigned char sim0_en_int : 1;
        unsigned char en_ldo11_int : 1;
        unsigned char sim1_en_int : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_SIMCARD_EN_UNION;
#endif
#define SOC_SMART_SIMCARD_EN_en_ldo9_int_START (0)
#define SOC_SMART_SIMCARD_EN_en_ldo9_int_END (0)
#define SOC_SMART_SIMCARD_EN_sim0_en_int_START (1)
#define SOC_SMART_SIMCARD_EN_sim0_en_int_END (1)
#define SOC_SMART_SIMCARD_EN_en_ldo11_int_START (2)
#define SOC_SMART_SIMCARD_EN_en_ldo11_int_END (2)
#define SOC_SMART_SIMCARD_EN_sim1_en_int_START (3)
#define SOC_SMART_SIMCARD_EN_sim1_en_int_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char simcard0_resv : 2;
        unsigned char simcard0_bbrp : 1;
        unsigned char simcard0_simrp : 1;
        unsigned char simcard0_200ns_en : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_SIM0_CFG_UNION;
#endif
#define SOC_SMART_SIM0_CFG_simcard0_resv_START (0)
#define SOC_SMART_SIM0_CFG_simcard0_resv_END (1)
#define SOC_SMART_SIM0_CFG_simcard0_bbrp_START (2)
#define SOC_SMART_SIM0_CFG_simcard0_bbrp_END (2)
#define SOC_SMART_SIM0_CFG_simcard0_simrp_START (3)
#define SOC_SMART_SIM0_CFG_simcard0_simrp_END (3)
#define SOC_SMART_SIM0_CFG_simcard0_200ns_en_START (4)
#define SOC_SMART_SIM0_CFG_simcard0_200ns_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char simcard1_resv : 2;
        unsigned char simcard1_bbrp : 1;
        unsigned char simcard1_simrp : 1;
        unsigned char simcard1_200ns_en : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_SIM1_CFG_UNION;
#endif
#define SOC_SMART_SIM1_CFG_simcard1_resv_START (0)
#define SOC_SMART_SIM1_CFG_simcard1_resv_END (1)
#define SOC_SMART_SIM1_CFG_simcard1_bbrp_START (2)
#define SOC_SMART_SIM1_CFG_simcard1_bbrp_END (2)
#define SOC_SMART_SIM1_CFG_simcard1_simrp_START (3)
#define SOC_SMART_SIM1_CFG_simcard1_simrp_END (3)
#define SOC_SMART_SIM1_CFG_simcard1_200ns_en_START (4)
#define SOC_SMART_SIM1_CFG_simcard1_200ns_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char simcard_deb_sel : 5;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_SIM_DEB_UNION;
#endif
#define SOC_SMART_SIM_DEB_simcard_deb_sel_START (0)
#define SOC_SMART_SIM_DEB_simcard_deb_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_eco_buck3_int : 1;
        unsigned char en_eco_buck4_int : 1;
        unsigned char en_eco_buck5_int : 1;
        unsigned char en_eco_buck6_int : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_ECO_MOD_CFG1_UNION;
#endif
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck3_int_START (0)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck3_int_END (0)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck4_int_START (1)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck4_int_END (1)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck5_int_START (2)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck5_int_END (2)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck6_int_START (3)
#define SOC_SMART_ECO_MOD_CFG1_en_eco_buck6_int_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_eco_ldo3_int : 1;
        unsigned char en_eco_ldo7_int : 1;
        unsigned char en_eco_ldo9_int : 1;
        unsigned char en_eco_ldo10_int : 1;
        unsigned char en_eco_ldo11_int : 1;
        unsigned char en_eco_ldo12_int : 1;
        unsigned char en_eco_ldo22_int : 1;
        unsigned char en_eco_ldo24_int : 1;
    } reg;
} SOC_SMART_ECO_MOD_CFG2_UNION;
#endif
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo3_int_START (0)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo3_int_END (0)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo7_int_START (1)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo7_int_END (1)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo9_int_START (2)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo9_int_END (2)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo10_int_START (3)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo10_int_END (3)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo11_int_START (4)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo11_int_END (4)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo12_int_START (5)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo12_int_END (5)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo22_int_START (6)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo22_int_END (6)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo24_int_START (7)
#define SOC_SMART_ECO_MOD_CFG2_en_eco_ldo24_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char force_eco_buck3_int : 1;
        unsigned char force_eco_buck4_int : 1;
        unsigned char force_eco_buck5_int : 1;
        unsigned char force_eco_buck6_int : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_ECO_MOD_CFG3_UNION;
#endif
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck3_int_START (0)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck3_int_END (0)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck4_int_START (1)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck4_int_END (1)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck5_int_START (2)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck5_int_END (2)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck6_int_START (3)
#define SOC_SMART_ECO_MOD_CFG3_force_eco_buck6_int_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char force_eco_ldo3_int : 1;
        unsigned char force_eco_ldo7_int : 1;
        unsigned char force_eco_ldo9_int : 1;
        unsigned char force_eco_ldo10_int : 1;
        unsigned char force_eco_ldo11_int : 1;
        unsigned char force_eco_ldo12_int : 1;
        unsigned char force_eco_ldo22_int : 1;
        unsigned char force_eco_ldo24_int : 1;
    } reg;
} SOC_SMART_ECO_MOD_CFG4_UNION;
#endif
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo3_int_START (0)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo3_int_END (0)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo7_int_START (1)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo7_int_END (1)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo9_int_START (2)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo9_int_END (2)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo10_int_START (3)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo10_int_END (3)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo11_int_START (4)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo11_int_END (4)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo12_int_START (5)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo12_int_END (5)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo22_int_START (6)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo22_int_END (6)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo24_int_START (7)
#define SOC_SMART_ECO_MOD_CFG4_force_eco_ldo24_int_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char eco_pwrsel : 2;
        unsigned char peri_en_ctrl_ldo12 : 1;
        unsigned char peri_en_ctrl_lvs9 : 1;
        unsigned char peri_en_ctrl_ldo8 : 1;
        unsigned char peri_en_ctrl_buck3 : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_ENB3_ECO_MARK_UNION;
#endif
#define SOC_SMART_ENB3_ECO_MARK_eco_pwrsel_START (0)
#define SOC_SMART_ENB3_ECO_MARK_eco_pwrsel_END (1)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_ldo12_START (2)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_ldo12_END (2)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_lvs9_START (3)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_lvs9_END (3)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_ldo8_START (4)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_ldo8_END (4)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_buck3_START (5)
#define SOC_SMART_ENB3_ECO_MARK_peri_en_ctrl_buck3_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_osc_d : 4;
        unsigned char buck0_pfm_vth_sel : 1;
        unsigned char buck0_sc_sel : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK01_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG1_ADJ_buck01_osc_d_START (0)
#define SOC_SMART_BUCK01_REG1_ADJ_buck01_osc_d_END (3)
#define SOC_SMART_BUCK01_REG1_ADJ_buck0_pfm_vth_sel_START (4)
#define SOC_SMART_BUCK01_REG1_ADJ_buck0_pfm_vth_sel_END (4)
#define SOC_SMART_BUCK01_REG1_ADJ_buck0_sc_sel_START (5)
#define SOC_SMART_BUCK01_REG1_ADJ_buck0_sc_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_mod_sel : 2;
        unsigned char buck0_bt_sel : 1;
        unsigned char buck0_pd_sel : 1;
        unsigned char buck0_burst_drv_ctr : 1;
        unsigned char buck01_ocp_mod_sel : 1;
        unsigned char buck01_ocp_clamp_sel : 1;
        unsigned char buck01_ocp_shied_sel : 1;
    } reg;
} SOC_SMART_BUCK01_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_mod_sel_START (0)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_mod_sel_END (1)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_bt_sel_START (2)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_bt_sel_END (2)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_pd_sel_START (3)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_pd_sel_END (3)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_burst_drv_ctr_START (4)
#define SOC_SMART_BUCK01_REG2_ADJ_buck0_burst_drv_ctr_END (4)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_mod_sel_START (5)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_mod_sel_END (5)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_clamp_sel_START (6)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_clamp_sel_END (6)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_shied_sel_START (7)
#define SOC_SMART_BUCK01_REG2_ADJ_buck01_ocp_shied_sel_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_vc_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck01_auto_pfm_ctr : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK01_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG3_ADJ_buck0_vc_sel_START (0)
#define SOC_SMART_BUCK01_REG3_ADJ_buck0_vc_sel_END (1)
#define SOC_SMART_BUCK01_REG3_ADJ_buck01_auto_pfm_ctr_START (4)
#define SOC_SMART_BUCK01_REG3_ADJ_buck01_auto_pfm_ctr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_isc_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck0_ipk_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK01_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG4_ADJ_buck0_isc_sel_START (0)
#define SOC_SMART_BUCK01_REG4_ADJ_buck0_isc_sel_END (1)
#define SOC_SMART_BUCK01_REG4_ADJ_buck0_ipk_sel_START (4)
#define SOC_SMART_BUCK01_REG4_ADJ_buck0_ipk_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_dt_sel : 2;
        unsigned char buck01_pg_dt_sel : 1;
        unsigned char buck01_ng_dt_sel : 1;
        unsigned char buck01_sft_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK01_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_dt_sel_START (0)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_dt_sel_END (1)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_pg_dt_sel_START (2)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_pg_dt_sel_END (2)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_ng_dt_sel_START (3)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_ng_dt_sel_END (3)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_sft_sel_START (4)
#define SOC_SMART_BUCK01_REG5_ADJ_buck01_sft_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_pg_p_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck01_pg_n_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK01_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG6_ADJ_buck01_pg_p_sel_START (0)
#define SOC_SMART_BUCK01_REG6_ADJ_buck01_pg_p_sel_END (1)
#define SOC_SMART_BUCK01_REG6_ADJ_buck01_pg_n_sel_START (4)
#define SOC_SMART_BUCK01_REG6_ADJ_buck01_pg_n_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_ng_p_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck01_ng_n_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK01_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG7_ADJ_buck01_ng_p_sel_START (0)
#define SOC_SMART_BUCK01_REG7_ADJ_buck01_ng_p_sel_END (1)
#define SOC_SMART_BUCK01_REG7_ADJ_buck01_ng_n_sel_START (4)
#define SOC_SMART_BUCK01_REG7_ADJ_buck01_ng_n_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_ccm_sel : 2;
        unsigned char buck1_ccm_sel : 2;
        unsigned char buck0_ccc_sel : 2;
        unsigned char buck0_cs_sel : 2;
    } reg;
} SOC_SMART_BUCK01_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_ccm_sel_START (0)
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_ccm_sel_END (1)
#define SOC_SMART_BUCK01_REG8_ADJ_buck1_ccm_sel_START (2)
#define SOC_SMART_BUCK01_REG8_ADJ_buck1_ccm_sel_END (3)
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_ccc_sel_START (4)
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_ccc_sel_END (5)
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_cs_sel_START (6)
#define SOC_SMART_BUCK01_REG8_ADJ_buck0_cs_sel_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_dmd_sel : 2;
        unsigned char buck01_ton_off : 1;
        unsigned char buck01_pfm_sleep : 1;
        unsigned char buck01_ton_on : 2;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_BUCK01_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG9_ADJ_buck0_dmd_sel_START (0)
#define SOC_SMART_BUCK01_REG9_ADJ_buck0_dmd_sel_END (1)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_ton_off_START (2)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_ton_off_END (2)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_pfm_sleep_START (3)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_pfm_sleep_END (3)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_ton_on_START (4)
#define SOC_SMART_BUCK01_REG9_ADJ_buck01_ton_on_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_new_dmd_sel : 5;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK01_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG10_ADJ_buck01_new_dmd_sel_START (0)
#define SOC_SMART_BUCK01_REG10_ADJ_buck01_new_dmd_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_ocp_sel : 4;
        unsigned char buck01_ocp_en : 1;
        unsigned char buck01_dmd_en : 1;
        unsigned char buck01_ea_sel : 1;
        unsigned char buck01_clk_sel : 1;
    } reg;
} SOC_SMART_BUCK01_REG11_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG11_ADJ_buck0_ocp_sel_START (0)
#define SOC_SMART_BUCK01_REG11_ADJ_buck0_ocp_sel_END (3)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_ocp_en_START (4)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_ocp_en_END (4)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_dmd_en_START (5)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_dmd_en_END (5)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_ea_sel_START (6)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_ea_sel_END (6)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_clk_sel_START (7)
#define SOC_SMART_BUCK01_REG11_ADJ_buck01_clk_sel_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_sleep_depth_adj : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck0_ea_comp_cap : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK01_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG12_ADJ_buck0_sleep_depth_adj_START (0)
#define SOC_SMART_BUCK01_REG12_ADJ_buck0_sleep_depth_adj_END (1)
#define SOC_SMART_BUCK01_REG12_ADJ_buck0_ea_comp_cap_START (4)
#define SOC_SMART_BUCK01_REG12_ADJ_buck0_ea_comp_cap_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_slope_gen : 3;
        unsigned char buck01_pdn_lx_det : 1;
        unsigned char buck01_sleep_dmd : 1;
        unsigned char buck01_dmd_shield_n : 1;
        unsigned char buck01_ocp_delay_sel : 1;
        unsigned char buck01_dmd_clamp : 1;
    } reg;
} SOC_SMART_BUCK01_REG13_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_slope_gen_START (0)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_slope_gen_END (2)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_pdn_lx_det_START (3)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_pdn_lx_det_END (3)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_sleep_dmd_START (4)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_sleep_dmd_END (4)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_dmd_shield_n_START (5)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_dmd_shield_n_END (5)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_ocp_delay_sel_START (6)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_ocp_delay_sel_END (6)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_dmd_clamp_START (7)
#define SOC_SMART_BUCK01_REG13_ADJ_buck01_dmd_clamp_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_slope_dc : 2;
        unsigned char buck01_unsleep : 1;
        unsigned char buck01_dmd_float : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_BUCK01_REG14_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_slope_dc_START (0)
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_slope_dc_END (1)
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_unsleep_START (2)
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_unsleep_END (2)
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_dmd_float_START (3)
#define SOC_SMART_BUCK01_REG14_ADJ_buck01_dmd_float_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_comp_adj1 : 8;
    } reg;
} SOC_SMART_BUCK01_REG15_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG15_ADJ_buck0_comp_adj1_START (0)
#define SOC_SMART_BUCK01_REG15_ADJ_buck0_comp_adj1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_reserved1 : 8;
    } reg;
} SOC_SMART_BUCK01_REG16_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG16_ADJ_buck01_reserved1_START (0)
#define SOC_SMART_BUCK01_REG16_ADJ_buck01_reserved1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck01_reserved0 : 8;
    } reg;
} SOC_SMART_BUCK01_REG17_ADJ_UNION;
#endif
#define SOC_SMART_BUCK01_REG17_ADJ_buck01_reserved0_START (0)
#define SOC_SMART_BUCK01_REG17_ADJ_buck01_reserved0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_adj_rlx : 4;
        unsigned char buck2_adj_clx : 4;
    } reg;
} SOC_SMART_BUCK2_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG1_ADJ_buck2_adj_rlx_START (0)
#define SOC_SMART_BUCK2_REG1_ADJ_buck2_adj_rlx_END (3)
#define SOC_SMART_BUCK2_REG1_ADJ_buck2_adj_clx_START (4)
#define SOC_SMART_BUCK2_REG1_ADJ_buck2_adj_clx_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_new_dmd_sel : 5;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK2_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG2_ADJ_buck2_new_dmd_sel_START (0)
#define SOC_SMART_BUCK2_REG2_ADJ_buck2_new_dmd_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_shield_i : 2;
        unsigned char buck2_en_regop_clamp : 1;
        unsigned char buck2_dmd_clamp : 1;
        unsigned char buck2_ocp_delay_sel : 1;
        unsigned char buck2_dmd_shield_n : 1;
        unsigned char buck2_sleep_dmd : 1;
        unsigned char buck2_pdn_lx_det : 1;
    } reg;
} SOC_SMART_BUCK2_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_shield_i_START (0)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_shield_i_END (1)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_en_regop_clamp_START (2)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_en_regop_clamp_END (2)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_dmd_clamp_START (3)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_dmd_clamp_END (3)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_ocp_delay_sel_START (4)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_ocp_delay_sel_END (4)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_dmd_shield_n_START (5)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_dmd_shield_n_END (5)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_sleep_dmd_START (6)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_sleep_dmd_END (6)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_pdn_lx_det_START (7)
#define SOC_SMART_BUCK2_REG3_ADJ_buck2_pdn_lx_det_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_ocp_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck2_dmd_sel : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_BUCK2_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG4_ADJ_buck2_ocp_sel_START (0)
#define SOC_SMART_BUCK2_REG4_ADJ_buck2_ocp_sel_END (1)
#define SOC_SMART_BUCK2_REG4_ADJ_buck2_dmd_sel_START (4)
#define SOC_SMART_BUCK2_REG4_ADJ_buck2_dmd_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_ng_dt_sel : 1;
        unsigned char buck2_pg_dt_sel : 1;
        unsigned char buck2_sft_sel : 1;
        unsigned char buck2_sleep : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_BUCK2_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_ng_dt_sel_START (0)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_ng_dt_sel_END (0)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_pg_dt_sel_START (1)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_pg_dt_sel_END (1)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_sft_sel_START (2)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_sft_sel_END (2)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_sleep_START (3)
#define SOC_SMART_BUCK2_REG5_ADJ_buck2_sleep_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_pg_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck2_pg_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK2_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG6_ADJ_buck2_pg_n_sel_START (0)
#define SOC_SMART_BUCK2_REG6_ADJ_buck2_pg_n_sel_END (1)
#define SOC_SMART_BUCK2_REG6_ADJ_buck2_pg_p_sel_START (4)
#define SOC_SMART_BUCK2_REG6_ADJ_buck2_pg_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_ng_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck2_ng_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK2_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG7_ADJ_buck2_ng_n_sel_START (0)
#define SOC_SMART_BUCK2_REG7_ADJ_buck2_ng_n_sel_END (1)
#define SOC_SMART_BUCK2_REG7_ADJ_buck2_ng_p_sel_START (4)
#define SOC_SMART_BUCK2_REG7_ADJ_buck2_ng_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_dbias : 2;
        unsigned char buck2_ocp_d : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck2_ton : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK2_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_dbias_START (0)
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_dbias_END (1)
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_ocp_d_START (2)
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_ocp_d_END (2)
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_ton_START (4)
#define SOC_SMART_BUCK2_REG8_ADJ_buck2_ton_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_nmos_off : 1;
        unsigned char buck2_reg_c : 1;
        unsigned char buck2_short_pdp : 1;
        unsigned char buck2_reg_ss_d : 1;
        unsigned char buck2_dt_sel : 2;
        unsigned char buck2_regop_c : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK2_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_nmos_off_START (0)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_nmos_off_END (0)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_reg_c_START (1)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_reg_c_END (1)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_short_pdp_START (2)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_short_pdp_END (2)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_reg_ss_d_START (3)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_reg_ss_d_END (3)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_dt_sel_START (4)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_dt_sel_END (5)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_regop_c_START (6)
#define SOC_SMART_BUCK2_REG9_ADJ_buck2_regop_c_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_reg_dr : 3;
        unsigned char buck2_en_reg : 1;
        unsigned char buck2_ocp_clamp_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK2_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_reg_dr_START (0)
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_reg_dr_END (2)
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_en_reg_START (3)
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_en_reg_END (3)
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_ocp_clamp_sel_START (4)
#define SOC_SMART_BUCK2_REG10_ADJ_buck2_ocp_clamp_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_reg_idr : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck2_reg_r : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK2_REG11_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG11_ADJ_buck2_reg_idr_START (0)
#define SOC_SMART_BUCK2_REG11_ADJ_buck2_reg_idr_END (1)
#define SOC_SMART_BUCK2_REG11_ADJ_buck2_reg_r_START (4)
#define SOC_SMART_BUCK2_REG11_ADJ_buck2_reg_r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_reserve : 8;
    } reg;
} SOC_SMART_BUCK2_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK2_REG12_ADJ_buck2_reserve_START (0)
#define SOC_SMART_BUCK2_REG12_ADJ_buck2_reserve_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_adj_rlx : 4;
        unsigned char buck3_adj_clx : 4;
    } reg;
} SOC_SMART_BUCK3_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG1_ADJ_buck3_adj_rlx_START (0)
#define SOC_SMART_BUCK3_REG1_ADJ_buck3_adj_rlx_END (3)
#define SOC_SMART_BUCK3_REG1_ADJ_buck3_adj_clx_START (4)
#define SOC_SMART_BUCK3_REG1_ADJ_buck3_adj_clx_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_new_dmd_sel : 5;
        unsigned char buck3_ocp_sel : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK3_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG2_ADJ_buck3_new_dmd_sel_START (0)
#define SOC_SMART_BUCK3_REG2_ADJ_buck3_new_dmd_sel_END (4)
#define SOC_SMART_BUCK3_REG2_ADJ_buck3_ocp_sel_START (5)
#define SOC_SMART_BUCK3_REG2_ADJ_buck3_ocp_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_dmd_sel : 2;
        unsigned char buck3_en_regop_clamp : 1;
        unsigned char buck3_dmd_clamp : 1;
        unsigned char buck3_ocp_delay_sel : 1;
        unsigned char buck3_dmd_shield_n : 1;
        unsigned char buck3_sleep_dmd : 1;
        unsigned char buck3_pdn_lx_det : 1;
    } reg;
} SOC_SMART_BUCK3_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_sel_START (0)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_sel_END (1)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_en_regop_clamp_START (2)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_en_regop_clamp_END (2)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_clamp_START (3)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_clamp_END (3)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_ocp_delay_sel_START (4)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_ocp_delay_sel_END (4)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_shield_n_START (5)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_dmd_shield_n_END (5)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_sleep_dmd_START (6)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_sleep_dmd_END (6)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_pdn_lx_det_START (7)
#define SOC_SMART_BUCK3_REG3_ADJ_buck3_pdn_lx_det_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_ng_dt_sel : 1;
        unsigned char buck3_pg_dt_sel : 1;
        unsigned char buck3_sft_sel : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck3_shield_i : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK3_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_ng_dt_sel_START (0)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_ng_dt_sel_END (0)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_pg_dt_sel_START (1)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_pg_dt_sel_END (1)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_sft_sel_START (2)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_sft_sel_END (2)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_shield_i_START (4)
#define SOC_SMART_BUCK3_REG4_ADJ_buck3_shield_i_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_pg_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck3_pg_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK3_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG5_ADJ_buck3_pg_n_sel_START (0)
#define SOC_SMART_BUCK3_REG5_ADJ_buck3_pg_n_sel_END (1)
#define SOC_SMART_BUCK3_REG5_ADJ_buck3_pg_p_sel_START (4)
#define SOC_SMART_BUCK3_REG5_ADJ_buck3_pg_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_ng_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck3_ng_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK3_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG6_ADJ_buck3_ng_n_sel_START (0)
#define SOC_SMART_BUCK3_REG6_ADJ_buck3_ng_n_sel_END (1)
#define SOC_SMART_BUCK3_REG6_ADJ_buck3_ng_p_sel_START (4)
#define SOC_SMART_BUCK3_REG6_ADJ_buck3_ng_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_dbias : 2;
        unsigned char buck3_ocp_d : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck3_ton : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK3_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_dbias_START (0)
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_dbias_END (1)
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_ocp_d_START (2)
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_ocp_d_END (2)
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_ton_START (4)
#define SOC_SMART_BUCK3_REG7_ADJ_buck3_ton_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_nmos_off : 1;
        unsigned char buck3_reg_c : 1;
        unsigned char buck3_short_pdp : 1;
        unsigned char buck3_reg_ss_d : 1;
        unsigned char buck3_dt_sel : 2;
        unsigned char buck3_regop_c : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK3_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_nmos_off_START (0)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_nmos_off_END (0)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_reg_c_START (1)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_reg_c_END (1)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_short_pdp_START (2)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_short_pdp_END (2)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_reg_ss_d_START (3)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_reg_ss_d_END (3)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_dt_sel_START (4)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_dt_sel_END (5)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_regop_c_START (6)
#define SOC_SMART_BUCK3_REG8_ADJ_buck3_regop_c_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_reg_dr : 3;
        unsigned char buck3_en_reg : 1;
        unsigned char buck3_ocp_clamp_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK3_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_reg_dr_START (0)
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_reg_dr_END (2)
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_en_reg_START (3)
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_en_reg_END (3)
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_ocp_clamp_sel_START (4)
#define SOC_SMART_BUCK3_REG9_ADJ_buck3_ocp_clamp_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_reg_idr : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck3_reg_r : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK3_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG10_ADJ_buck3_reg_idr_START (0)
#define SOC_SMART_BUCK3_REG10_ADJ_buck3_reg_idr_END (1)
#define SOC_SMART_BUCK3_REG10_ADJ_buck3_reg_r_START (4)
#define SOC_SMART_BUCK3_REG10_ADJ_buck3_reg_r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_mos_sel : 2;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_BUCK3_REG11_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG11_ADJ_buck3_mos_sel_START (0)
#define SOC_SMART_BUCK3_REG11_ADJ_buck3_mos_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_reserve : 8;
    } reg;
} SOC_SMART_BUCK3_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK3_REG12_ADJ_buck3_reserve_START (0)
#define SOC_SMART_BUCK3_REG12_ADJ_buck3_reserve_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_adj_rlx : 4;
        unsigned char buck4_adj_clx : 4;
    } reg;
} SOC_SMART_BUCK4_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG1_ADJ_buck4_adj_rlx_START (0)
#define SOC_SMART_BUCK4_REG1_ADJ_buck4_adj_rlx_END (3)
#define SOC_SMART_BUCK4_REG1_ADJ_buck4_adj_clx_START (4)
#define SOC_SMART_BUCK4_REG1_ADJ_buck4_adj_clx_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_new_dmd_sel : 5;
        unsigned char buck4_ocp_sel : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK4_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG2_ADJ_buck4_new_dmd_sel_START (0)
#define SOC_SMART_BUCK4_REG2_ADJ_buck4_new_dmd_sel_END (4)
#define SOC_SMART_BUCK4_REG2_ADJ_buck4_ocp_sel_START (5)
#define SOC_SMART_BUCK4_REG2_ADJ_buck4_ocp_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_dmd_sel : 2;
        unsigned char buck4_en_regop_clamp : 1;
        unsigned char buck4_dmd_clamp : 1;
        unsigned char buck4_ocp_delay_sel : 1;
        unsigned char buck4_dmd_shield_n : 1;
        unsigned char buck4_sleep_dmd : 1;
        unsigned char buck4_pdn_lx_det : 1;
    } reg;
} SOC_SMART_BUCK4_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_sel_START (0)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_sel_END (1)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_en_regop_clamp_START (2)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_en_regop_clamp_END (2)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_clamp_START (3)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_clamp_END (3)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_ocp_delay_sel_START (4)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_ocp_delay_sel_END (4)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_shield_n_START (5)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_dmd_shield_n_END (5)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_sleep_dmd_START (6)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_sleep_dmd_END (6)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_pdn_lx_det_START (7)
#define SOC_SMART_BUCK4_REG3_ADJ_buck4_pdn_lx_det_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_ng_dt_sel : 1;
        unsigned char buck4_pg_dt_sel : 1;
        unsigned char buck4_sft_sel : 1;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_BUCK4_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_ng_dt_sel_START (0)
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_ng_dt_sel_END (0)
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_pg_dt_sel_START (1)
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_pg_dt_sel_END (1)
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_sft_sel_START (2)
#define SOC_SMART_BUCK4_REG4_ADJ_buck4_sft_sel_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_pg_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck4_pg_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK4_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG5_ADJ_buck4_pg_n_sel_START (0)
#define SOC_SMART_BUCK4_REG5_ADJ_buck4_pg_n_sel_END (1)
#define SOC_SMART_BUCK4_REG5_ADJ_buck4_pg_p_sel_START (4)
#define SOC_SMART_BUCK4_REG5_ADJ_buck4_pg_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_ng_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck4_ng_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK4_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG6_ADJ_buck4_ng_n_sel_START (0)
#define SOC_SMART_BUCK4_REG6_ADJ_buck4_ng_n_sel_END (1)
#define SOC_SMART_BUCK4_REG6_ADJ_buck4_ng_p_sel_START (4)
#define SOC_SMART_BUCK4_REG6_ADJ_buck4_ng_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_dbias : 2;
        unsigned char buck4_ocp_d : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck4_ton : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK4_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_dbias_START (0)
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_dbias_END (1)
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_ocp_d_START (2)
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_ocp_d_END (2)
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_ton_START (4)
#define SOC_SMART_BUCK4_REG7_ADJ_buck4_ton_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_nmos_off : 1;
        unsigned char buck4_reg_c : 1;
        unsigned char buck4_short_pdp : 1;
        unsigned char buck4_reg_ss_d : 1;
        unsigned char buck4_dt_sel : 2;
        unsigned char buck4_regop_c : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK4_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_nmos_off_START (0)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_nmos_off_END (0)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_reg_c_START (1)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_reg_c_END (1)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_short_pdp_START (2)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_short_pdp_END (2)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_reg_ss_d_START (3)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_reg_ss_d_END (3)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_dt_sel_START (4)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_dt_sel_END (5)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_regop_c_START (6)
#define SOC_SMART_BUCK4_REG8_ADJ_buck4_regop_c_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_reg_dr : 3;
        unsigned char buck4_en_reg : 1;
        unsigned char buck4_ocp_clamp_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK4_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_reg_dr_START (0)
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_reg_dr_END (2)
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_en_reg_START (3)
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_en_reg_END (3)
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_ocp_clamp_sel_START (4)
#define SOC_SMART_BUCK4_REG9_ADJ_buck4_ocp_clamp_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_reg_idr : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck4_reg_r : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK4_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG10_ADJ_buck4_reg_idr_START (0)
#define SOC_SMART_BUCK4_REG10_ADJ_buck4_reg_idr_END (1)
#define SOC_SMART_BUCK4_REG10_ADJ_buck4_reg_r_START (4)
#define SOC_SMART_BUCK4_REG10_ADJ_buck4_reg_r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_reserve : 8;
    } reg;
} SOC_SMART_BUCK4_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK4_REG12_ADJ_buck4_reserve_START (0)
#define SOC_SMART_BUCK4_REG12_ADJ_buck4_reserve_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_adj_rlx : 4;
        unsigned char buck5_adj_clx : 4;
    } reg;
} SOC_SMART_BUCK5_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG1_ADJ_buck5_adj_rlx_START (0)
#define SOC_SMART_BUCK5_REG1_ADJ_buck5_adj_rlx_END (3)
#define SOC_SMART_BUCK5_REG1_ADJ_buck5_adj_clx_START (4)
#define SOC_SMART_BUCK5_REG1_ADJ_buck5_adj_clx_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_new_dmd_sel : 5;
        unsigned char buck5_ocp_sel : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK5_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG2_ADJ_buck5_new_dmd_sel_START (0)
#define SOC_SMART_BUCK5_REG2_ADJ_buck5_new_dmd_sel_END (4)
#define SOC_SMART_BUCK5_REG2_ADJ_buck5_ocp_sel_START (5)
#define SOC_SMART_BUCK5_REG2_ADJ_buck5_ocp_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_dmd_sel : 2;
        unsigned char buck5_en_regop_clamp : 1;
        unsigned char buck5_dmd_clamp : 1;
        unsigned char buck5_ocp_delay_sel : 1;
        unsigned char buck5_dmd_shield_n : 1;
        unsigned char buck5_sleep_dmd : 1;
        unsigned char buck5_pdn_lx_det : 1;
    } reg;
} SOC_SMART_BUCK5_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_sel_START (0)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_sel_END (1)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_en_regop_clamp_START (2)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_en_regop_clamp_END (2)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_clamp_START (3)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_clamp_END (3)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_ocp_delay_sel_START (4)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_ocp_delay_sel_END (4)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_shield_n_START (5)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_dmd_shield_n_END (5)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_sleep_dmd_START (6)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_sleep_dmd_END (6)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_pdn_lx_det_START (7)
#define SOC_SMART_BUCK5_REG3_ADJ_buck5_pdn_lx_det_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_ng_dt_sel : 1;
        unsigned char buck5_pg_dt_sel : 1;
        unsigned char buck5_sft_sel : 1;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_BUCK5_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_ng_dt_sel_START (0)
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_ng_dt_sel_END (0)
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_pg_dt_sel_START (1)
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_pg_dt_sel_END (1)
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_sft_sel_START (2)
#define SOC_SMART_BUCK5_REG4_ADJ_buck5_sft_sel_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_pg_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck5_pg_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK5_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG5_ADJ_buck5_pg_n_sel_START (0)
#define SOC_SMART_BUCK5_REG5_ADJ_buck5_pg_n_sel_END (1)
#define SOC_SMART_BUCK5_REG5_ADJ_buck5_pg_p_sel_START (4)
#define SOC_SMART_BUCK5_REG5_ADJ_buck5_pg_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_ng_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck5_ng_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK5_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG6_ADJ_buck5_ng_n_sel_START (0)
#define SOC_SMART_BUCK5_REG6_ADJ_buck5_ng_n_sel_END (1)
#define SOC_SMART_BUCK5_REG6_ADJ_buck5_ng_p_sel_START (4)
#define SOC_SMART_BUCK5_REG6_ADJ_buck5_ng_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_dbias : 2;
        unsigned char buck5_ocp_d : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck5_ton : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK5_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_dbias_START (0)
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_dbias_END (1)
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_ocp_d_START (2)
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_ocp_d_END (2)
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_ton_START (4)
#define SOC_SMART_BUCK5_REG7_ADJ_buck5_ton_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_nmos_off : 1;
        unsigned char buck5_reg_c : 1;
        unsigned char buck5_short_pdp : 1;
        unsigned char buck5_reg_ss_d : 1;
        unsigned char buck5_dt_sel : 2;
        unsigned char buck5_regop_c : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK5_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_nmos_off_START (0)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_nmos_off_END (0)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_reg_c_START (1)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_reg_c_END (1)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_short_pdp_START (2)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_short_pdp_END (2)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_reg_ss_d_START (3)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_reg_ss_d_END (3)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_dt_sel_START (4)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_dt_sel_END (5)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_regop_c_START (6)
#define SOC_SMART_BUCK5_REG8_ADJ_buck5_regop_c_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_reg_dr : 3;
        unsigned char buck5_en_reg : 1;
        unsigned char buck5_ocp_clamp_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK5_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_reg_dr_START (0)
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_reg_dr_END (2)
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_en_reg_START (3)
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_en_reg_END (3)
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_ocp_clamp_sel_START (4)
#define SOC_SMART_BUCK5_REG9_ADJ_buck5_ocp_clamp_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_reg_idr : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck5_reg_r : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK5_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG10_ADJ_buck5_reg_idr_START (0)
#define SOC_SMART_BUCK5_REG10_ADJ_buck5_reg_idr_END (1)
#define SOC_SMART_BUCK5_REG10_ADJ_buck5_reg_r_START (4)
#define SOC_SMART_BUCK5_REG10_ADJ_buck5_reg_r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_reserve0 : 8;
    } reg;
} SOC_SMART_BUCK5_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG12_ADJ_buck5_reserve0_START (0)
#define SOC_SMART_BUCK5_REG12_ADJ_buck5_reserve0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_reserve1 : 6;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_BUCK5_REG13_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG13_ADJ_buck5_reserve1_START (0)
#define SOC_SMART_BUCK5_REG13_ADJ_buck5_reserve1_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_reserve2 : 8;
    } reg;
} SOC_SMART_BUCK5_REG14_ADJ_UNION;
#endif
#define SOC_SMART_BUCK5_REG14_ADJ_buck5_reserve2_START (0)
#define SOC_SMART_BUCK5_REG14_ADJ_buck5_reserve2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_adj_rlx : 4;
        unsigned char buck6_adj_clx : 4;
    } reg;
} SOC_SMART_BUCK6_REG1_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG1_ADJ_buck6_adj_rlx_START (0)
#define SOC_SMART_BUCK6_REG1_ADJ_buck6_adj_rlx_END (3)
#define SOC_SMART_BUCK6_REG1_ADJ_buck6_adj_clx_START (4)
#define SOC_SMART_BUCK6_REG1_ADJ_buck6_adj_clx_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_new_dmd_sel : 5;
        unsigned char buck6_ocp_sel : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK6_REG2_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG2_ADJ_buck6_new_dmd_sel_START (0)
#define SOC_SMART_BUCK6_REG2_ADJ_buck6_new_dmd_sel_END (4)
#define SOC_SMART_BUCK6_REG2_ADJ_buck6_ocp_sel_START (5)
#define SOC_SMART_BUCK6_REG2_ADJ_buck6_ocp_sel_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_dmd_sel : 2;
        unsigned char buck6_en_regop_clamp : 1;
        unsigned char buck6_dmd_clamp : 1;
        unsigned char buck6_ocp_delay_sel : 1;
        unsigned char buck6_dmd_shield_n : 1;
        unsigned char buck6_sleep_dmd : 1;
        unsigned char buck6_pdn_lx_det : 1;
    } reg;
} SOC_SMART_BUCK6_REG3_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_sel_START (0)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_sel_END (1)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_en_regop_clamp_START (2)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_en_regop_clamp_END (2)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_clamp_START (3)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_clamp_END (3)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_ocp_delay_sel_START (4)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_ocp_delay_sel_END (4)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_shield_n_START (5)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_dmd_shield_n_END (5)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_sleep_dmd_START (6)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_sleep_dmd_END (6)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_pdn_lx_det_START (7)
#define SOC_SMART_BUCK6_REG3_ADJ_buck6_pdn_lx_det_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_ng_dt_sel : 1;
        unsigned char buck6_pg_dt_sel : 1;
        unsigned char buck6_sft_sel : 1;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_BUCK6_REG4_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_ng_dt_sel_START (0)
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_ng_dt_sel_END (0)
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_pg_dt_sel_START (1)
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_pg_dt_sel_END (1)
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_sft_sel_START (2)
#define SOC_SMART_BUCK6_REG4_ADJ_buck6_sft_sel_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_pg_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck6_pg_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK6_REG5_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG5_ADJ_buck6_pg_n_sel_START (0)
#define SOC_SMART_BUCK6_REG5_ADJ_buck6_pg_n_sel_END (1)
#define SOC_SMART_BUCK6_REG5_ADJ_buck6_pg_p_sel_START (4)
#define SOC_SMART_BUCK6_REG5_ADJ_buck6_pg_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_ng_n_sel : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck6_ng_p_sel : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK6_REG6_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG6_ADJ_buck6_ng_n_sel_START (0)
#define SOC_SMART_BUCK6_REG6_ADJ_buck6_ng_n_sel_END (1)
#define SOC_SMART_BUCK6_REG6_ADJ_buck6_ng_p_sel_START (4)
#define SOC_SMART_BUCK6_REG6_ADJ_buck6_ng_p_sel_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_dbias : 2;
        unsigned char buck6_ocp_d : 1;
        unsigned char reserved_0 : 1;
        unsigned char buck6_ton : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK6_REG7_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_dbias_START (0)
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_dbias_END (1)
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_ocp_d_START (2)
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_ocp_d_END (2)
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_ton_START (4)
#define SOC_SMART_BUCK6_REG7_ADJ_buck6_ton_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_nmos_off : 1;
        unsigned char buck6_reg_c : 1;
        unsigned char buck6_short_pdp : 1;
        unsigned char buck6_reg_ss_d : 1;
        unsigned char buck6_dt_sel : 2;
        unsigned char buck6_regop_c : 1;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_BUCK6_REG8_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_nmos_off_START (0)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_nmos_off_END (0)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_reg_c_START (1)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_reg_c_END (1)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_short_pdp_START (2)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_short_pdp_END (2)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_reg_ss_d_START (3)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_reg_ss_d_END (3)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_dt_sel_START (4)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_dt_sel_END (5)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_regop_c_START (6)
#define SOC_SMART_BUCK6_REG8_ADJ_buck6_regop_c_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_reg_dr : 3;
        unsigned char buck6_en_reg : 1;
        unsigned char buck6_ocp_clamp_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BUCK6_REG9_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_reg_dr_START (0)
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_reg_dr_END (2)
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_en_reg_START (3)
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_en_reg_END (3)
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_ocp_clamp_sel_START (4)
#define SOC_SMART_BUCK6_REG9_ADJ_buck6_ocp_clamp_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_reg_idr : 2;
        unsigned char reserved_0 : 2;
        unsigned char buck6_reg_r : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BUCK6_REG10_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG10_ADJ_buck6_reg_idr_START (0)
#define SOC_SMART_BUCK6_REG10_ADJ_buck6_reg_idr_END (1)
#define SOC_SMART_BUCK6_REG10_ADJ_buck6_reg_r_START (4)
#define SOC_SMART_BUCK6_REG10_ADJ_buck6_reg_r_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_mos_sel : 2;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_BUCK6_REG11_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG11_ADJ_buck6_mos_sel_START (0)
#define SOC_SMART_BUCK6_REG11_ADJ_buck6_mos_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_reserve : 8;
    } reg;
} SOC_SMART_BUCK6_REG12_ADJ_UNION;
#endif
#define SOC_SMART_BUCK6_REG12_ADJ_buck6_reserve_START (0)
#define SOC_SMART_BUCK6_REG12_ADJ_buck6_reserve_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cp2_vout_sel : 2;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_CHG_PUMP2_ADJ_UNION;
#endif
#define SOC_SMART_CHG_PUMP2_ADJ_cp2_vout_sel_START (0)
#define SOC_SMART_CHG_PUMP2_ADJ_cp2_vout_sel_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck0_vck : 6;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_VSET_BUCK01_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK01_ADJ_buck0_vck_START (0)
#define SOC_SMART_VSET_BUCK01_ADJ_buck0_vck_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck2_dv : 8;
    } reg;
} SOC_SMART_VSET_BUCK2_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_START (0)
#define SOC_SMART_VSET_BUCK2_ADJ_buck2_dv_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck3_dv : 4;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_VSET_BUCK3_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK3_ADJ_buck3_dv_START (0)
#define SOC_SMART_VSET_BUCK3_ADJ_buck3_dv_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck4_dv : 4;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_VSET_BUCK4_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK4_ADJ_buck4_dv_START (0)
#define SOC_SMART_VSET_BUCK4_ADJ_buck4_dv_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck5_dv : 8;
    } reg;
} SOC_SMART_VSET_BUCK5_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK5_ADJ_buck5_dv_START (0)
#define SOC_SMART_VSET_BUCK5_ADJ_buck5_dv_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char buck6_dv : 4;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_VSET_BUCK6_ADJ_UNION;
#endif
#define SOC_SMART_VSET_BUCK6_ADJ_buck6_dv_START (0)
#define SOC_SMART_VSET_BUCK6_ADJ_buck6_dv_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo1 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO1_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO1_REG_ADJ_vset_ldo1_START (0)
#define SOC_SMART_LDO1_REG_ADJ_vset_ldo1_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo2 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO2_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO2_REG_ADJ_vset_ldo2_START (0)
#define SOC_SMART_LDO2_REG_ADJ_vset_ldo2_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo3 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo3 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO3_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO3_REG_ADJ_vset_ldo3_START (0)
#define SOC_SMART_LDO3_REG_ADJ_vset_ldo3_END (2)
#define SOC_SMART_LDO3_REG_ADJ_vrset_ldo3_START (4)
#define SOC_SMART_LDO3_REG_ADJ_vrset_ldo3_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo4 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO4_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO4_REG_ADJ_vset_ldo4_START (0)
#define SOC_SMART_LDO4_REG_ADJ_vset_ldo4_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo5 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo5 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO5_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO5_REG_ADJ_vset_ldo5_START (0)
#define SOC_SMART_LDO5_REG_ADJ_vset_ldo5_END (2)
#define SOC_SMART_LDO5_REG_ADJ_vrset_ldo5_START (4)
#define SOC_SMART_LDO5_REG_ADJ_vrset_ldo5_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo6 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO6_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO6_REG_ADJ_vset_ldo6_START (0)
#define SOC_SMART_LDO6_REG_ADJ_vset_ldo6_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo7 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO7_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO7_REG_ADJ_vset_ldo7_START (0)
#define SOC_SMART_LDO7_REG_ADJ_vset_ldo7_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo8 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo8 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO8_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO8_REG_ADJ_vset_ldo8_START (0)
#define SOC_SMART_LDO8_REG_ADJ_vset_ldo8_END (2)
#define SOC_SMART_LDO8_REG_ADJ_vrset_ldo8_START (4)
#define SOC_SMART_LDO8_REG_ADJ_vrset_ldo8_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo9 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo9 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO9_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO9_REG_ADJ_vset_ldo9_START (0)
#define SOC_SMART_LDO9_REG_ADJ_vset_ldo9_END (2)
#define SOC_SMART_LDO9_REG_ADJ_vrset_ldo9_START (4)
#define SOC_SMART_LDO9_REG_ADJ_vrset_ldo9_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo10 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo10 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO10_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO10_REG_ADJ_vset_ldo10_START (0)
#define SOC_SMART_LDO10_REG_ADJ_vset_ldo10_END (2)
#define SOC_SMART_LDO10_REG_ADJ_vrset_ldo10_START (4)
#define SOC_SMART_LDO10_REG_ADJ_vrset_ldo10_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo11 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo11 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO11_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO11_REG_ADJ_vset_ldo11_START (0)
#define SOC_SMART_LDO11_REG_ADJ_vset_ldo11_END (2)
#define SOC_SMART_LDO11_REG_ADJ_vrset_ldo11_START (4)
#define SOC_SMART_LDO11_REG_ADJ_vrset_ldo11_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo12 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo12 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO12_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO12_REG_ADJ_vset_ldo12_START (0)
#define SOC_SMART_LDO12_REG_ADJ_vset_ldo12_END (2)
#define SOC_SMART_LDO12_REG_ADJ_vrset_ldo12_START (4)
#define SOC_SMART_LDO12_REG_ADJ_vrset_ldo12_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo13 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO13_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO13_REG_ADJ_vset_ldo13_START (0)
#define SOC_SMART_LDO13_REG_ADJ_vset_ldo13_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo14 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo14 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO14_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO14_REG_ADJ_vset_ldo14_START (0)
#define SOC_SMART_LDO14_REG_ADJ_vset_ldo14_END (2)
#define SOC_SMART_LDO14_REG_ADJ_vrset_ldo14_START (4)
#define SOC_SMART_LDO14_REG_ADJ_vrset_ldo14_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo15 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo15 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO15_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO15_REG_ADJ_vset_ldo15_START (0)
#define SOC_SMART_LDO15_REG_ADJ_vset_ldo15_END (2)
#define SOC_SMART_LDO15_REG_ADJ_vrset_ldo15_START (4)
#define SOC_SMART_LDO15_REG_ADJ_vrset_ldo15_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo16 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo16 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO16_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO16_REG_ADJ_vset_ldo16_START (0)
#define SOC_SMART_LDO16_REG_ADJ_vset_ldo16_END (2)
#define SOC_SMART_LDO16_REG_ADJ_vrset_ldo16_START (4)
#define SOC_SMART_LDO16_REG_ADJ_vrset_ldo16_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo17 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo17 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO17_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO17_REG_ADJ_vset_ldo17_START (0)
#define SOC_SMART_LDO17_REG_ADJ_vset_ldo17_END (2)
#define SOC_SMART_LDO17_REG_ADJ_vrset_ldo17_START (4)
#define SOC_SMART_LDO17_REG_ADJ_vrset_ldo17_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo18 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo18 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO18_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO18_REG_ADJ_vset_ldo18_START (0)
#define SOC_SMART_LDO18_REG_ADJ_vset_ldo18_END (2)
#define SOC_SMART_LDO18_REG_ADJ_vrset_ldo18_START (4)
#define SOC_SMART_LDO18_REG_ADJ_vrset_ldo18_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo19 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo19 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO19_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO19_REG_ADJ_vset_ldo19_START (0)
#define SOC_SMART_LDO19_REG_ADJ_vset_ldo19_END (2)
#define SOC_SMART_LDO19_REG_ADJ_vrset_ldo19_START (4)
#define SOC_SMART_LDO19_REG_ADJ_vrset_ldo19_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo20 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo20 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO20_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO20_REG_ADJ_vset_ldo20_START (0)
#define SOC_SMART_LDO20_REG_ADJ_vset_ldo20_END (2)
#define SOC_SMART_LDO20_REG_ADJ_vrset_ldo20_START (4)
#define SOC_SMART_LDO20_REG_ADJ_vrset_ldo20_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo21 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo21 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO21_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO21_REG_ADJ_vset_ldo21_START (0)
#define SOC_SMART_LDO21_REG_ADJ_vset_ldo21_END (2)
#define SOC_SMART_LDO21_REG_ADJ_vrset_ldo21_START (4)
#define SOC_SMART_LDO21_REG_ADJ_vrset_ldo21_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo22 : 3;
        unsigned char rset_sink_ldo22_3 : 1;
        unsigned char rset_sink_ldo22_2 : 1;
        unsigned char rset_sink_ldo22_1 : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_LDO22_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO22_REG_ADJ_vset_ldo22_START (0)
#define SOC_SMART_LDO22_REG_ADJ_vset_ldo22_END (2)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_3_START (3)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_3_END (3)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_2_START (4)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_2_END (4)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_1_START (5)
#define SOC_SMART_LDO22_REG_ADJ_rset_sink_ldo22_1_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo23 : 3;
        unsigned char reserved_0 : 1;
        unsigned char vrset_ldo23 : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_LDO23_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO23_REG_ADJ_vset_ldo23_START (0)
#define SOC_SMART_LDO23_REG_ADJ_vset_ldo23_END (2)
#define SOC_SMART_LDO23_REG_ADJ_vrset_ldo23_START (4)
#define SOC_SMART_LDO23_REG_ADJ_vrset_ldo23_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_ldo24 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_LDO24_REG_ADJ_UNION;
#endif
#define SOC_SMART_LDO24_REG_ADJ_vset_ldo24_START (0)
#define SOC_SMART_LDO24_REG_ADJ_vset_ldo24_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vset_pmua : 3;
        unsigned char eco_pmua : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_PMUA_REG_ADJ_UNION;
#endif
#define SOC_SMART_PMUA_REG_ADJ_vset_pmua_START (0)
#define SOC_SMART_PMUA_REG_ADJ_vset_pmua_END (2)
#define SOC_SMART_PMUA_REG_ADJ_eco_pmua_START (3)
#define SOC_SMART_PMUA_REG_ADJ_eco_pmua_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char sstset_lvs5 : 2;
        unsigned char sstset_lvs4 : 2;
        unsigned char sstset_lvs3 : 2;
        unsigned char sstset_lvs2 : 2;
    } reg;
} SOC_SMART_LVS_ADJ1_UNION;
#endif
#define SOC_SMART_LVS_ADJ1_sstset_lvs5_START (0)
#define SOC_SMART_LVS_ADJ1_sstset_lvs5_END (1)
#define SOC_SMART_LVS_ADJ1_sstset_lvs4_START (2)
#define SOC_SMART_LVS_ADJ1_sstset_lvs4_END (3)
#define SOC_SMART_LVS_ADJ1_sstset_lvs3_START (4)
#define SOC_SMART_LVS_ADJ1_sstset_lvs3_END (5)
#define SOC_SMART_LVS_ADJ1_sstset_lvs2_START (6)
#define SOC_SMART_LVS_ADJ1_sstset_lvs2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char sstset_lvs9 : 2;
        unsigned char sstset_lvs8 : 2;
        unsigned char sstset_lvs7 : 2;
        unsigned char sstset_lvs6 : 2;
    } reg;
} SOC_SMART_LVS_ADJ2_UNION;
#endif
#define SOC_SMART_LVS_ADJ2_sstset_lvs9_START (0)
#define SOC_SMART_LVS_ADJ2_sstset_lvs9_END (1)
#define SOC_SMART_LVS_ADJ2_sstset_lvs8_START (2)
#define SOC_SMART_LVS_ADJ2_sstset_lvs8_END (3)
#define SOC_SMART_LVS_ADJ2_sstset_lvs7_START (4)
#define SOC_SMART_LVS_ADJ2_sstset_lvs7_END (5)
#define SOC_SMART_LVS_ADJ2_sstset_lvs6_START (6)
#define SOC_SMART_LVS_ADJ2_sstset_lvs6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char sstset_lvs10 : 2;
        unsigned char reserved : 6;
    } reg;
} SOC_SMART_LVS_ADJ3_UNION;
#endif
#define SOC_SMART_LVS_ADJ3_sstset_lvs10_START (0)
#define SOC_SMART_LVS_ADJ3_sstset_lvs10_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_bst_int : 1;
        unsigned char bst_pm_th : 1;
        unsigned char bst_pm_cut : 1;
        unsigned char bst_reserved0 : 5;
    } reg;
} SOC_SMART_BOOST_ADJ0_UNION;
#endif
#define SOC_SMART_BOOST_ADJ0_en_bst_int_START (0)
#define SOC_SMART_BOOST_ADJ0_en_bst_int_END (0)
#define SOC_SMART_BOOST_ADJ0_bst_pm_th_START (1)
#define SOC_SMART_BOOST_ADJ0_bst_pm_th_END (1)
#define SOC_SMART_BOOST_ADJ0_bst_pm_cut_START (2)
#define SOC_SMART_BOOST_ADJ0_bst_pm_cut_END (2)
#define SOC_SMART_BOOST_ADJ0_bst_reserved0_START (3)
#define SOC_SMART_BOOST_ADJ0_bst_reserved0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_sel_scp : 1;
        unsigned char bst_sel_pd : 1;
        unsigned char bst_en_uvp : 1;
        unsigned char bst_en_scp : 1;
        unsigned char bst_en_ovp : 1;
        unsigned char bst_en_ocp : 1;
        unsigned char bst_reserved1 : 2;
    } reg;
} SOC_SMART_BOOST_ADJ1_UNION;
#endif
#define SOC_SMART_BOOST_ADJ1_bst_sel_scp_START (0)
#define SOC_SMART_BOOST_ADJ1_bst_sel_scp_END (0)
#define SOC_SMART_BOOST_ADJ1_bst_sel_pd_START (1)
#define SOC_SMART_BOOST_ADJ1_bst_sel_pd_END (1)
#define SOC_SMART_BOOST_ADJ1_bst_en_uvp_START (2)
#define SOC_SMART_BOOST_ADJ1_bst_en_uvp_END (2)
#define SOC_SMART_BOOST_ADJ1_bst_en_scp_START (3)
#define SOC_SMART_BOOST_ADJ1_bst_en_scp_END (3)
#define SOC_SMART_BOOST_ADJ1_bst_en_ovp_START (4)
#define SOC_SMART_BOOST_ADJ1_bst_en_ovp_END (4)
#define SOC_SMART_BOOST_ADJ1_bst_en_ocp_START (5)
#define SOC_SMART_BOOST_ADJ1_bst_en_ocp_END (5)
#define SOC_SMART_BOOST_ADJ1_bst_reserved1_START (6)
#define SOC_SMART_BOOST_ADJ1_bst_reserved1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_drv_mode : 1;
        unsigned char bst_loop_mode : 1;
        unsigned char bst_en_pfm : 1;
        unsigned char bst_en_nring : 1;
        unsigned char bst_en_clp_os : 1;
        unsigned char bst_en_slop : 1;
        unsigned char bst_en_dmd : 1;
        unsigned char bst_reserved2 : 1;
    } reg;
} SOC_SMART_BOOST_ADJ2_UNION;
#endif
#define SOC_SMART_BOOST_ADJ2_bst_drv_mode_START (0)
#define SOC_SMART_BOOST_ADJ2_bst_drv_mode_END (0)
#define SOC_SMART_BOOST_ADJ2_bst_loop_mode_START (1)
#define SOC_SMART_BOOST_ADJ2_bst_loop_mode_END (1)
#define SOC_SMART_BOOST_ADJ2_bst_en_pfm_START (2)
#define SOC_SMART_BOOST_ADJ2_bst_en_pfm_END (2)
#define SOC_SMART_BOOST_ADJ2_bst_en_nring_START (3)
#define SOC_SMART_BOOST_ADJ2_bst_en_nring_END (3)
#define SOC_SMART_BOOST_ADJ2_bst_en_clp_os_START (4)
#define SOC_SMART_BOOST_ADJ2_bst_en_clp_os_END (4)
#define SOC_SMART_BOOST_ADJ2_bst_en_slop_START (5)
#define SOC_SMART_BOOST_ADJ2_bst_en_slop_END (5)
#define SOC_SMART_BOOST_ADJ2_bst_en_dmd_START (6)
#define SOC_SMART_BOOST_ADJ2_bst_en_dmd_END (6)
#define SOC_SMART_BOOST_ADJ2_bst_reserved2_START (7)
#define SOC_SMART_BOOST_ADJ2_bst_reserved2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_clp : 3;
        unsigned char bst_itail : 1;
        unsigned char bst_gm : 3;
        unsigned char bst_reserved3 : 1;
    } reg;
} SOC_SMART_BOOST_ADJ3_UNION;
#endif
#define SOC_SMART_BOOST_ADJ3_bst_clp_START (0)
#define SOC_SMART_BOOST_ADJ3_bst_clp_END (2)
#define SOC_SMART_BOOST_ADJ3_bst_itail_START (3)
#define SOC_SMART_BOOST_ADJ3_bst_itail_END (3)
#define SOC_SMART_BOOST_ADJ3_bst_gm_START (4)
#define SOC_SMART_BOOST_ADJ3_bst_gm_END (6)
#define SOC_SMART_BOOST_ADJ3_bst_reserved3_START (7)
#define SOC_SMART_BOOST_ADJ3_bst_reserved3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_ccom2 : 2;
        unsigned char bst_ccom1 : 2;
        unsigned char bst_rcom : 2;
        unsigned char bst_reserved4 : 2;
    } reg;
} SOC_SMART_BOOST_ADJ4_UNION;
#endif
#define SOC_SMART_BOOST_ADJ4_bst_ccom2_START (0)
#define SOC_SMART_BOOST_ADJ4_bst_ccom2_END (1)
#define SOC_SMART_BOOST_ADJ4_bst_ccom1_START (2)
#define SOC_SMART_BOOST_ADJ4_bst_ccom1_END (3)
#define SOC_SMART_BOOST_ADJ4_bst_rcom_START (4)
#define SOC_SMART_BOOST_ADJ4_bst_rcom_END (5)
#define SOC_SMART_BOOST_ADJ4_bst_reserved4_START (6)
#define SOC_SMART_BOOST_ADJ4_bst_reserved4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_slop : 2;
        unsigned char bst_ri : 2;
        unsigned char bst_reserved5 : 4;
    } reg;
} SOC_SMART_BOOST_ADJ5_UNION;
#endif
#define SOC_SMART_BOOST_ADJ5_bst_slop_START (0)
#define SOC_SMART_BOOST_ADJ5_bst_slop_END (1)
#define SOC_SMART_BOOST_ADJ5_bst_ri_START (2)
#define SOC_SMART_BOOST_ADJ5_bst_ri_END (3)
#define SOC_SMART_BOOST_ADJ5_bst_reserved5_START (4)
#define SOC_SMART_BOOST_ADJ5_bst_reserved5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_nsn : 2;
        unsigned char bst_nsp : 2;
        unsigned char bst_psn : 2;
        unsigned char bst_psp : 2;
    } reg;
} SOC_SMART_BOOST_ADJ6_UNION;
#endif
#define SOC_SMART_BOOST_ADJ6_bst_nsn_START (0)
#define SOC_SMART_BOOST_ADJ6_bst_nsn_END (1)
#define SOC_SMART_BOOST_ADJ6_bst_nsp_START (2)
#define SOC_SMART_BOOST_ADJ6_bst_nsp_END (3)
#define SOC_SMART_BOOST_ADJ6_bst_psn_START (4)
#define SOC_SMART_BOOST_ADJ6_bst_psn_END (5)
#define SOC_SMART_BOOST_ADJ6_bst_psp_START (6)
#define SOC_SMART_BOOST_ADJ6_bst_psp_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_dt_nm : 2;
        unsigned char bst_dt_pm : 2;
        unsigned char bst_lxde : 2;
        unsigned char bst_reserved6 : 2;
    } reg;
} SOC_SMART_BOOST_ADJ7_UNION;
#endif
#define SOC_SMART_BOOST_ADJ7_bst_dt_nm_START (0)
#define SOC_SMART_BOOST_ADJ7_bst_dt_nm_END (1)
#define SOC_SMART_BOOST_ADJ7_bst_dt_pm_START (2)
#define SOC_SMART_BOOST_ADJ7_bst_dt_pm_END (3)
#define SOC_SMART_BOOST_ADJ7_bst_lxde_START (4)
#define SOC_SMART_BOOST_ADJ7_bst_lxde_END (5)
#define SOC_SMART_BOOST_ADJ7_bst_reserved6_START (6)
#define SOC_SMART_BOOST_ADJ7_bst_reserved6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_ckmin : 2;
        unsigned char bst_osc : 4;
        unsigned char bst_reserved7 : 2;
    } reg;
} SOC_SMART_BOOST_ADJ8_UNION;
#endif
#define SOC_SMART_BOOST_ADJ8_bst_ckmin_START (0)
#define SOC_SMART_BOOST_ADJ8_bst_ckmin_END (1)
#define SOC_SMART_BOOST_ADJ8_bst_osc_START (2)
#define SOC_SMART_BOOST_ADJ8_bst_osc_END (5)
#define SOC_SMART_BOOST_ADJ8_bst_reserved7_START (6)
#define SOC_SMART_BOOST_ADJ8_bst_reserved7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char vo : 3;
        unsigned char sel_ocp : 2;
        unsigned char bst_start : 3;
    } reg;
} SOC_SMART_BOOST_ADJ9_UNION;
#endif
#define SOC_SMART_BOOST_ADJ9_vo_START (0)
#define SOC_SMART_BOOST_ADJ9_vo_END (2)
#define SOC_SMART_BOOST_ADJ9_sel_ocp_START (3)
#define SOC_SMART_BOOST_ADJ9_sel_ocp_END (4)
#define SOC_SMART_BOOST_ADJ9_bst_start_START (5)
#define SOC_SMART_BOOST_ADJ9_bst_start_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_dmd_ofs : 4;
        unsigned char bst_reserved10 : 4;
    } reg;
} SOC_SMART_BOOST_ADJ10_UNION;
#endif
#define SOC_SMART_BOOST_ADJ10_bst_dmd_ofs_START (0)
#define SOC_SMART_BOOST_ADJ10_bst_dmd_ofs_END (3)
#define SOC_SMART_BOOST_ADJ10_bst_reserved10_START (4)
#define SOC_SMART_BOOST_ADJ10_bst_reserved10_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bst_v2clp : 2;
        unsigned char bst_v2div : 2;
        unsigned char bst_v2ramp : 2;
        unsigned char bst_reserved11 : 2;
    } reg;
} SOC_SMART_BOOST_ADJ11_UNION;
#endif
#define SOC_SMART_BOOST_ADJ11_bst_v2clp_START (0)
#define SOC_SMART_BOOST_ADJ11_bst_v2clp_END (1)
#define SOC_SMART_BOOST_ADJ11_bst_v2div_START (2)
#define SOC_SMART_BOOST_ADJ11_bst_v2div_END (3)
#define SOC_SMART_BOOST_ADJ11_bst_v2ramp_START (4)
#define SOC_SMART_BOOST_ADJ11_bst_v2ramp_END (5)
#define SOC_SMART_BOOST_ADJ11_bst_reserved11_START (6)
#define SOC_SMART_BOOST_ADJ11_bst_reserved11_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char classd_mute_sel : 1;
        unsigned char classd_mute : 1;
        unsigned char classd_gain : 2;
        unsigned char en_classd_int : 1;
        unsigned char classd_i_ocp : 2;
        unsigned char reserved : 1;
    } reg;
} SOC_SMART_CLASSD_ADJ0_UNION;
#endif
#define SOC_SMART_CLASSD_ADJ0_classd_mute_sel_START (0)
#define SOC_SMART_CLASSD_ADJ0_classd_mute_sel_END (0)
#define SOC_SMART_CLASSD_ADJ0_classd_mute_START (1)
#define SOC_SMART_CLASSD_ADJ0_classd_mute_END (1)
#define SOC_SMART_CLASSD_ADJ0_classd_gain_START (2)
#define SOC_SMART_CLASSD_ADJ0_classd_gain_END (3)
#define SOC_SMART_CLASSD_ADJ0_en_classd_int_START (4)
#define SOC_SMART_CLASSD_ADJ0_en_classd_int_END (4)
#define SOC_SMART_CLASSD_ADJ0_classd_i_ocp_START (5)
#define SOC_SMART_CLASSD_ADJ0_classd_i_ocp_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char classd_n_sel : 2;
        unsigned char classd_p_sel : 2;
        unsigned char classd_i_ramp : 2;
        unsigned char classd_i_pump : 2;
    } reg;
} SOC_SMART_CLASSD_ADJ1_UNION;
#endif
#define SOC_SMART_CLASSD_ADJ1_classd_n_sel_START (0)
#define SOC_SMART_CLASSD_ADJ1_classd_n_sel_END (1)
#define SOC_SMART_CLASSD_ADJ1_classd_p_sel_START (2)
#define SOC_SMART_CLASSD_ADJ1_classd_p_sel_END (3)
#define SOC_SMART_CLASSD_ADJ1_classd_i_ramp_START (4)
#define SOC_SMART_CLASSD_ADJ1_classd_i_ramp_END (5)
#define SOC_SMART_CLASSD_ADJ1_classd_i_pump_START (6)
#define SOC_SMART_CLASSD_ADJ1_classd_i_pump_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char classd_ocp_bps : 1;
        unsigned char classd_fx_bps : 1;
        unsigned char classd_dt_sel : 1;
        unsigned char classd_pls_byp : 1;
        unsigned char classd_reserved : 4;
    } reg;
} SOC_SMART_CLASSD_ADJ2_UNION;
#endif
#define SOC_SMART_CLASSD_ADJ2_classd_ocp_bps_START (0)
#define SOC_SMART_CLASSD_ADJ2_classd_ocp_bps_END (0)
#define SOC_SMART_CLASSD_ADJ2_classd_fx_bps_START (1)
#define SOC_SMART_CLASSD_ADJ2_classd_fx_bps_END (1)
#define SOC_SMART_CLASSD_ADJ2_classd_dt_sel_START (2)
#define SOC_SMART_CLASSD_ADJ2_classd_dt_sel_END (2)
#define SOC_SMART_CLASSD_ADJ2_classd_pls_byp_START (3)
#define SOC_SMART_CLASSD_ADJ2_classd_pls_byp_END (3)
#define SOC_SMART_CLASSD_ADJ2_classd_reserved_START (4)
#define SOC_SMART_CLASSD_ADJ2_classd_reserved_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char bg_test : 4;
        unsigned char bg_sleep : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_BANDGAP_THSD_ADJ1_UNION;
#endif
#define SOC_SMART_BANDGAP_THSD_ADJ1_bg_test_START (0)
#define SOC_SMART_BANDGAP_THSD_ADJ1_bg_test_END (3)
#define SOC_SMART_BANDGAP_THSD_ADJ1_bg_sleep_START (4)
#define SOC_SMART_BANDGAP_THSD_ADJ1_bg_sleep_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_tmp_int : 2;
        unsigned char reserved_0 : 2;
        unsigned char thsd_set_tmp : 2;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_BANDGAP_THSD_ADJ2_UNION;
#endif
#define SOC_SMART_BANDGAP_THSD_ADJ2_en_tmp_int_START (0)
#define SOC_SMART_BANDGAP_THSD_ADJ2_en_tmp_int_END (1)
#define SOC_SMART_BANDGAP_THSD_ADJ2_thsd_set_tmp_START (4)
#define SOC_SMART_BANDGAP_THSD_ADJ2_thsd_set_tmp_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_dr3_int : 1;
        unsigned char dr3_mode : 1;
        unsigned char en_dr4_int : 1;
        unsigned char dr4_mode : 1;
        unsigned char en_dr5_int : 1;
        unsigned char dr5_mode : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_DR_FLA_CTRL1_UNION;
#endif
#define SOC_SMART_DR_FLA_CTRL1_en_dr3_int_START (0)
#define SOC_SMART_DR_FLA_CTRL1_en_dr3_int_END (0)
#define SOC_SMART_DR_FLA_CTRL1_dr3_mode_START (1)
#define SOC_SMART_DR_FLA_CTRL1_dr3_mode_END (1)
#define SOC_SMART_DR_FLA_CTRL1_en_dr4_int_START (2)
#define SOC_SMART_DR_FLA_CTRL1_en_dr4_int_END (2)
#define SOC_SMART_DR_FLA_CTRL1_dr4_mode_START (3)
#define SOC_SMART_DR_FLA_CTRL1_dr4_mode_END (3)
#define SOC_SMART_DR_FLA_CTRL1_en_dr5_int_START (4)
#define SOC_SMART_DR_FLA_CTRL1_en_dr5_int_END (4)
#define SOC_SMART_DR_FLA_CTRL1_dr5_mode_START (5)
#define SOC_SMART_DR_FLA_CTRL1_dr5_mode_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char en_dr1_int : 1;
        unsigned char dr1_mode : 1;
        unsigned char reserved_0 : 2;
        unsigned char en_dr2_int : 1;
        unsigned char dr2_mode : 1;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_DR_FLA_CTRL2_UNION;
#endif
#define SOC_SMART_DR_FLA_CTRL2_en_dr1_int_START (0)
#define SOC_SMART_DR_FLA_CTRL2_en_dr1_int_END (0)
#define SOC_SMART_DR_FLA_CTRL2_dr1_mode_START (1)
#define SOC_SMART_DR_FLA_CTRL2_dr1_mode_END (1)
#define SOC_SMART_DR_FLA_CTRL2_en_dr2_int_START (4)
#define SOC_SMART_DR_FLA_CTRL2_en_dr2_int_END (4)
#define SOC_SMART_DR_FLA_CTRL2_dr2_mode_START (5)
#define SOC_SMART_DR_FLA_CTRL2_dr2_mode_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char flash_period : 8;
    } reg;
} SOC_SMART_FLASH_PERIOD_UNION;
#endif
#define SOC_SMART_FLASH_PERIOD_flash_period_START (0)
#define SOC_SMART_FLASH_PERIOD_flash_period_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char flash_on : 8;
    } reg;
} SOC_SMART_FLASH_ON_UNION;
#endif
#define SOC_SMART_FLASH_ON_flash_on_START (0)
#define SOC_SMART_FLASH_ON_flash_on_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr1_mode_sel : 1;
        unsigned char dr2_mode_sel : 1;
        unsigned char dr3_mode_sel : 1;
        unsigned char dr4_mode_sel : 1;
        unsigned char dr5_mode_sel : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_DR_MODE_SEL_UNION;
#endif
#define SOC_SMART_DR_MODE_SEL_dr1_mode_sel_START (0)
#define SOC_SMART_DR_MODE_SEL_dr1_mode_sel_END (0)
#define SOC_SMART_DR_MODE_SEL_dr2_mode_sel_START (1)
#define SOC_SMART_DR_MODE_SEL_dr2_mode_sel_END (1)
#define SOC_SMART_DR_MODE_SEL_dr3_mode_sel_START (2)
#define SOC_SMART_DR_MODE_SEL_dr3_mode_sel_END (2)
#define SOC_SMART_DR_MODE_SEL_dr4_mode_sel_START (3)
#define SOC_SMART_DR_MODE_SEL_dr4_mode_sel_END (3)
#define SOC_SMART_DR_MODE_SEL_dr5_mode_sel_START (4)
#define SOC_SMART_DR_MODE_SEL_dr5_mode_sel_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr1_en : 1;
        unsigned char dr1_flash_en : 1;
        unsigned char reserved_0 : 2;
        unsigned char dr2_en : 1;
        unsigned char dr2_flash_en : 1;
        unsigned char reserved_1 : 2;
    } reg;
} SOC_SMART_DR_BRE_CTRL_UNION;
#endif
#define SOC_SMART_DR_BRE_CTRL_dr1_en_START (0)
#define SOC_SMART_DR_BRE_CTRL_dr1_en_END (0)
#define SOC_SMART_DR_BRE_CTRL_dr1_flash_en_START (1)
#define SOC_SMART_DR_BRE_CTRL_dr1_flash_en_END (1)
#define SOC_SMART_DR_BRE_CTRL_dr2_en_START (4)
#define SOC_SMART_DR_BRE_CTRL_dr2_en_END (4)
#define SOC_SMART_DR_BRE_CTRL_dr2_flash_en_START (5)
#define SOC_SMART_DR_BRE_CTRL_dr2_flash_en_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr1_t_off : 3;
        unsigned char reserved_0: 1;
        unsigned char dr1_t_on : 3;
        unsigned char reserved_1: 1;
    } reg;
} SOC_SMART_DR1_TIM_CONF0_UNION;
#endif
#define SOC_SMART_DR1_TIM_CONF0_dr1_t_off_START (0)
#define SOC_SMART_DR1_TIM_CONF0_dr1_t_off_END (2)
#define SOC_SMART_DR1_TIM_CONF0_dr1_t_on_START (4)
#define SOC_SMART_DR1_TIM_CONF0_dr1_t_on_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr1_t_rise : 3;
        unsigned char reserved_0 : 1;
        unsigned char dr1_t_fall : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_DR1_TIM_CONF1_UNION;
#endif
#define SOC_SMART_DR1_TIM_CONF1_dr1_t_rise_START (0)
#define SOC_SMART_DR1_TIM_CONF1_dr1_t_rise_END (2)
#define SOC_SMART_DR1_TIM_CONF1_dr1_t_fall_START (4)
#define SOC_SMART_DR1_TIM_CONF1_dr1_t_fall_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char iset_dr1 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DR1_ISET_UNION;
#endif
#define SOC_SMART_DR1_ISET_iset_dr1_START (0)
#define SOC_SMART_DR1_ISET_iset_dr1_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr2_t_off : 3;
        unsigned char reserved_0: 1;
        unsigned char dr2_t_on : 3;
        unsigned char reserved_1: 1;
    } reg;
} SOC_SMART_DR2_TIM_CONF0_UNION;
#endif
#define SOC_SMART_DR2_TIM_CONF0_dr2_t_off_START (0)
#define SOC_SMART_DR2_TIM_CONF0_dr2_t_off_END (2)
#define SOC_SMART_DR2_TIM_CONF0_dr2_t_on_START (4)
#define SOC_SMART_DR2_TIM_CONF0_dr2_t_on_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr2_t_rise : 3;
        unsigned char reserved_0 : 1;
        unsigned char dr2_t_fall : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_DR2_TIM_CONF1_UNION;
#endif
#define SOC_SMART_DR2_TIM_CONF1_dr2_t_rise_START (0)
#define SOC_SMART_DR2_TIM_CONF1_dr2_t_rise_END (2)
#define SOC_SMART_DR2_TIM_CONF1_dr2_t_fall_START (4)
#define SOC_SMART_DR2_TIM_CONF1_dr2_t_fall_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char iset_dr2 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DR2_ISET_UNION;
#endif
#define SOC_SMART_DR2_ISET_iset_dr2_START (0)
#define SOC_SMART_DR2_ISET_iset_dr2_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr3_en : 1;
        unsigned char dr4_en : 1;
        unsigned char dr5_en : 1;
        unsigned char dr_eco_en : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_DR_LED_CTRL_UNION;
#endif
#define SOC_SMART_DR_LED_CTRL_dr3_en_START (0)
#define SOC_SMART_DR_LED_CTRL_dr3_en_END (0)
#define SOC_SMART_DR_LED_CTRL_dr4_en_START (1)
#define SOC_SMART_DR_LED_CTRL_dr4_en_END (1)
#define SOC_SMART_DR_LED_CTRL_dr5_en_START (2)
#define SOC_SMART_DR_LED_CTRL_dr5_en_END (2)
#define SOC_SMART_DR_LED_CTRL_dr_eco_en_START (3)
#define SOC_SMART_DR_LED_CTRL_dr_eco_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr3_out_ctrl : 2;
        unsigned char dr4_out_ctrl : 2;
        unsigned char dr5_out_ctrl : 2;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_DR_OUT_CTRL_UNION;
#endif
#define SOC_SMART_DR_OUT_CTRL_dr3_out_ctrl_START (0)
#define SOC_SMART_DR_OUT_CTRL_dr3_out_ctrl_END (1)
#define SOC_SMART_DR_OUT_CTRL_dr4_out_ctrl_START (2)
#define SOC_SMART_DR_OUT_CTRL_dr4_out_ctrl_END (3)
#define SOC_SMART_DR_OUT_CTRL_dr5_out_ctrl_START (4)
#define SOC_SMART_DR_OUT_CTRL_dr5_out_ctrl_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char iset_dr3 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DR3_ISET_UNION;
#endif
#define SOC_SMART_DR3_ISET_iset_dr3_START (0)
#define SOC_SMART_DR3_ISET_iset_dr3_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr3_start_delay : 8;
    } reg;
} SOC_SMART_DR3_START_DEL_UNION;
#endif
#define SOC_SMART_DR3_START_DEL_dr3_start_delay_START (0)
#define SOC_SMART_DR3_START_DEL_dr3_start_delay_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr3_t_off : 4;
        unsigned char dr3_t_on : 4;
    } reg;
} SOC_SMART_DR3_TIM_CONF0_UNION;
#endif
#define SOC_SMART_DR3_TIM_CONF0_dr3_t_off_START (0)
#define SOC_SMART_DR3_TIM_CONF0_dr3_t_off_END (3)
#define SOC_SMART_DR3_TIM_CONF0_dr3_t_on_START (4)
#define SOC_SMART_DR3_TIM_CONF0_dr3_t_on_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr3_t_rise : 3;
        unsigned char reserved_0 : 1;
        unsigned char dr3_t_fall : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_DR3_TIM_CONF1_UNION;
#endif
#define SOC_SMART_DR3_TIM_CONF1_dr3_t_rise_START (0)
#define SOC_SMART_DR3_TIM_CONF1_dr3_t_rise_END (2)
#define SOC_SMART_DR3_TIM_CONF1_dr3_t_fall_START (4)
#define SOC_SMART_DR3_TIM_CONF1_dr3_t_fall_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char iset_dr4 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DR4_ISET_UNION;
#endif
#define SOC_SMART_DR4_ISET_iset_dr4_START (0)
#define SOC_SMART_DR4_ISET_iset_dr4_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr4_start_delay : 8;
    } reg;
} SOC_SMART_DR4_START_DEL_UNION;
#endif
#define SOC_SMART_DR4_START_DEL_dr4_start_delay_START (0)
#define SOC_SMART_DR4_START_DEL_dr4_start_delay_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr4_t_off : 4;
        unsigned char dr4_t_on : 4;
    } reg;
} SOC_SMART_DR4_TIM_CONF0_UNION;
#endif
#define SOC_SMART_DR4_TIM_CONF0_dr4_t_off_START (0)
#define SOC_SMART_DR4_TIM_CONF0_dr4_t_off_END (3)
#define SOC_SMART_DR4_TIM_CONF0_dr4_t_on_START (4)
#define SOC_SMART_DR4_TIM_CONF0_dr4_t_on_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr4_t_rise : 3;
        unsigned char reserved_0 : 1;
        unsigned char dr4_t_fall : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_DR4_TIM_CONF1_UNION;
#endif
#define SOC_SMART_DR4_TIM_CONF1_dr4_t_rise_START (0)
#define SOC_SMART_DR4_TIM_CONF1_dr4_t_rise_END (2)
#define SOC_SMART_DR4_TIM_CONF1_dr4_t_fall_START (4)
#define SOC_SMART_DR4_TIM_CONF1_dr4_t_fall_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char iset_dr5 : 3;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DR5_ISET_UNION;
#endif
#define SOC_SMART_DR5_ISET_iset_dr5_START (0)
#define SOC_SMART_DR5_ISET_iset_dr5_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr5_start_delay : 8;
    } reg;
} SOC_SMART_DR5_START_DEL_UNION;
#endif
#define SOC_SMART_DR5_START_DEL_dr5_start_delay_START (0)
#define SOC_SMART_DR5_START_DEL_dr5_start_delay_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr5_t_off : 4;
        unsigned char dr5_t_on : 4;
    } reg;
} SOC_SMART_DR5_TIM_CONF0_UNION;
#endif
#define SOC_SMART_DR5_TIM_CONF0_dr5_t_off_START (0)
#define SOC_SMART_DR5_TIM_CONF0_dr5_t_off_END (3)
#define SOC_SMART_DR5_TIM_CONF0_dr5_t_on_START (4)
#define SOC_SMART_DR5_TIM_CONF0_dr5_t_on_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dr5_t_rise : 3;
        unsigned char reserved_0 : 1;
        unsigned char dr5_t_fall : 3;
        unsigned char reserved_1 : 1;
    } reg;
} SOC_SMART_DR5_TIM_CONF1_UNION;
#endif
#define SOC_SMART_DR5_TIM_CONF1_dr5_t_rise_START (0)
#define SOC_SMART_DR5_TIM_CONF1_dr5_t_rise_END (2)
#define SOC_SMART_DR5_TIM_CONF1_dr5_t_fall_START (4)
#define SOC_SMART_DR5_TIM_CONF1_dr5_t_fall_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pwe_int : 1;
        unsigned char otp_pwe_pulse : 1;
        unsigned char otp_write_mask : 1;
        unsigned char otp_por_int : 1;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_OTP_CTRL1_UNION;
#endif
#define SOC_SMART_OTP_CTRL1_otp_pwe_int_START (0)
#define SOC_SMART_OTP_CTRL1_otp_pwe_int_END (0)
#define SOC_SMART_OTP_CTRL1_otp_pwe_pulse_START (1)
#define SOC_SMART_OTP_CTRL1_otp_pwe_pulse_END (1)
#define SOC_SMART_OTP_CTRL1_otp_write_mask_START (2)
#define SOC_SMART_OTP_CTRL1_otp_write_mask_END (2)
#define SOC_SMART_OTP_CTRL1_otp_por_int_START (3)
#define SOC_SMART_OTP_CTRL1_otp_por_int_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pa : 2;
        unsigned char otp_ptm : 2;
        unsigned char otp_pprog : 1;
        unsigned char reserved : 3;
    } reg;
} SOC_SMART_OTP_CTRL2_UNION;
#endif
#define SOC_SMART_OTP_CTRL2_otp_pa_START (0)
#define SOC_SMART_OTP_CTRL2_otp_pa_END (1)
#define SOC_SMART_OTP_CTRL2_otp_ptm_START (2)
#define SOC_SMART_OTP_CTRL2_otp_ptm_END (3)
#define SOC_SMART_OTP_CTRL2_otp_pprog_START (4)
#define SOC_SMART_OTP_CTRL2_otp_pprog_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pdin : 8;
    } reg;
} SOC_SMART_OTP_PDIN_UNION;
#endif
#define SOC_SMART_OTP_PDIN_otp_pdin_START (0)
#define SOC_SMART_OTP_PDIN_otp_pdin_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pdob0 : 8;
    } reg;
} SOC_SMART_OTP_PDOB0_UNION;
#endif
#define SOC_SMART_OTP_PDOB0_otp_pdob0_START (0)
#define SOC_SMART_OTP_PDOB0_otp_pdob0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pdob1 : 8;
    } reg;
} SOC_SMART_OTP_PDOB1_UNION;
#endif
#define SOC_SMART_OTP_PDOB1_otp_pdob1_START (0)
#define SOC_SMART_OTP_PDOB1_otp_pdob1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pdob2 : 8;
    } reg;
} SOC_SMART_OTP_PDOB2_UNION;
#endif
#define SOC_SMART_OTP_PDOB2_otp_pdob2_START (0)
#define SOC_SMART_OTP_PDOB2_otp_pdob2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char otp_pdob3 : 8;
    } reg;
} SOC_SMART_OTP_PDOB3_UNION;
#endif
#define SOC_SMART_OTP_PDOB3_otp_pdob3_START (0)
#define SOC_SMART_OTP_PDOB3_otp_pdob3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_a0 : 8;
    } reg;
} SOC_SMART_RTCCR_A0_UNION;
#endif
#define SOC_SMART_RTCCR_A0_rtccr_a0_START (0)
#define SOC_SMART_RTCCR_A0_rtccr_a0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_a1 : 8;
    } reg;
} SOC_SMART_RTCCR_A1_UNION;
#endif
#define SOC_SMART_RTCCR_A1_rtccr_a1_START (0)
#define SOC_SMART_RTCCR_A1_rtccr_a1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_a2 : 8;
    } reg;
} SOC_SMART_RTCCR_A2_UNION;
#endif
#define SOC_SMART_RTCCR_A2_rtccr_a2_START (0)
#define SOC_SMART_RTCCR_A2_rtccr_a2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_a3 : 8;
    } reg;
} SOC_SMART_RTCCR_A3_UNION;
#endif
#define SOC_SMART_RTCCR_A3_rtccr_a3_START (0)
#define SOC_SMART_RTCCR_A3_rtccr_a3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_a0 : 8;
    } reg;
} SOC_SMART_RTCLR_A0_UNION;
#endif
#define SOC_SMART_RTCLR_A0_rtclr_a0_START (0)
#define SOC_SMART_RTCLR_A0_rtclr_a0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_a1 : 8;
    } reg;
} SOC_SMART_RTCLR_A1_UNION;
#endif
#define SOC_SMART_RTCLR_A1_rtclr_a1_START (0)
#define SOC_SMART_RTCLR_A1_rtclr_a1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_a2 : 8;
    } reg;
} SOC_SMART_RTCLR_A2_UNION;
#endif
#define SOC_SMART_RTCLR_A2_rtclr_a2_START (0)
#define SOC_SMART_RTCLR_A2_rtclr_a2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_a3 : 8;
    } reg;
} SOC_SMART_RTCLR_A3_UNION;
#endif
#define SOC_SMART_RTCLR_A3_rtclr_a3_START (0)
#define SOC_SMART_RTCLR_A3_rtclr_a3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_a : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_RTCCTRL_A_UNION;
#endif
#define SOC_SMART_RTCCTRL_A_rtccr_a_START (0)
#define SOC_SMART_RTCCTRL_A_rtccr_a_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_a0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_A0_UNION;
#endif
#define SOC_SMART_RTCMR_A_A0_rtcmr_a_a0_START (0)
#define SOC_SMART_RTCMR_A_A0_rtcmr_a_a0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_a1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_A1_UNION;
#endif
#define SOC_SMART_RTCMR_A_A1_rtcmr_a_a1_START (0)
#define SOC_SMART_RTCMR_A_A1_rtcmr_a_a1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_a2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_A2_UNION;
#endif
#define SOC_SMART_RTCMR_A_A2_rtcmr_a_a2_START (0)
#define SOC_SMART_RTCMR_A_A2_rtcmr_a_a2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_a3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_A3_UNION;
#endif
#define SOC_SMART_RTCMR_A_A3_rtcmr_a_a3_START (0)
#define SOC_SMART_RTCMR_A_A3_rtcmr_a_a3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_b0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_B0_UNION;
#endif
#define SOC_SMART_RTCMR_A_B0_rtcmr_a_b0_START (0)
#define SOC_SMART_RTCMR_A_B0_rtcmr_a_b0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_b1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_B1_UNION;
#endif
#define SOC_SMART_RTCMR_A_B1_rtcmr_a_b1_START (0)
#define SOC_SMART_RTCMR_A_B1_rtcmr_a_b1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_b2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_B2_UNION;
#endif
#define SOC_SMART_RTCMR_A_B2_rtcmr_a_b2_START (0)
#define SOC_SMART_RTCMR_A_B2_rtcmr_a_b2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_b3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_B3_UNION;
#endif
#define SOC_SMART_RTCMR_A_B3_rtcmr_a_b3_START (0)
#define SOC_SMART_RTCMR_A_B3_rtcmr_a_b3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_c0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_C0_UNION;
#endif
#define SOC_SMART_RTCMR_A_C0_rtcmr_a_c0_START (0)
#define SOC_SMART_RTCMR_A_C0_rtcmr_a_c0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_c1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_C1_UNION;
#endif
#define SOC_SMART_RTCMR_A_C1_rtcmr_a_c1_START (0)
#define SOC_SMART_RTCMR_A_C1_rtcmr_a_c1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_c2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_C2_UNION;
#endif
#define SOC_SMART_RTCMR_A_C2_rtcmr_a_c2_START (0)
#define SOC_SMART_RTCMR_A_C2_rtcmr_a_c2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_c3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_C3_UNION;
#endif
#define SOC_SMART_RTCMR_A_C3_rtcmr_a_c3_START (0)
#define SOC_SMART_RTCMR_A_C3_rtcmr_a_c3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_d0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_D0_UNION;
#endif
#define SOC_SMART_RTCMR_A_D0_rtcmr_a_d0_START (0)
#define SOC_SMART_RTCMR_A_D0_rtcmr_a_d0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_d1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_D1_UNION;
#endif
#define SOC_SMART_RTCMR_A_D1_rtcmr_a_d1_START (0)
#define SOC_SMART_RTCMR_A_D1_rtcmr_a_d1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_d2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_D2_UNION;
#endif
#define SOC_SMART_RTCMR_A_D2_rtcmr_a_d2_START (0)
#define SOC_SMART_RTCMR_A_D2_rtcmr_a_d2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_d3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_D3_UNION;
#endif
#define SOC_SMART_RTCMR_A_D3_rtcmr_a_d3_START (0)
#define SOC_SMART_RTCMR_A_D3_rtcmr_a_d3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_e0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_E0_UNION;
#endif
#define SOC_SMART_RTCMR_A_E0_rtcmr_a_e0_START (0)
#define SOC_SMART_RTCMR_A_E0_rtcmr_a_e0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_e1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_E1_UNION;
#endif
#define SOC_SMART_RTCMR_A_E1_rtcmr_a_e1_START (0)
#define SOC_SMART_RTCMR_A_E1_rtcmr_a_e1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_e2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_E2_UNION;
#endif
#define SOC_SMART_RTCMR_A_E2_rtcmr_a_e2_START (0)
#define SOC_SMART_RTCMR_A_E2_rtcmr_a_e2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_e3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_E3_UNION;
#endif
#define SOC_SMART_RTCMR_A_E3_rtcmr_a_e3_START (0)
#define SOC_SMART_RTCMR_A_E3_rtcmr_a_e3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_f0 : 8;
    } reg;
} SOC_SMART_RTCMR_A_F0_UNION;
#endif
#define SOC_SMART_RTCMR_A_F0_rtcmr_a_f0_START (0)
#define SOC_SMART_RTCMR_A_F0_rtcmr_a_f0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_f1 : 8;
    } reg;
} SOC_SMART_RTCMR_A_F1_UNION;
#endif
#define SOC_SMART_RTCMR_A_F1_rtcmr_a_f1_START (0)
#define SOC_SMART_RTCMR_A_F1_rtcmr_a_f1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_f2 : 8;
    } reg;
} SOC_SMART_RTCMR_A_F2_UNION;
#endif
#define SOC_SMART_RTCMR_A_F2_rtcmr_a_f2_START (0)
#define SOC_SMART_RTCMR_A_F2_rtcmr_a_f2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtcmr_a_f3 : 8;
    } reg;
} SOC_SMART_RTCMR_A_F3_UNION;
#endif
#define SOC_SMART_RTCMR_A_F3_rtcmr_a_f3_START (0)
#define SOC_SMART_RTCMR_A_F3_rtcmr_a_f3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_na0 : 8;
    } reg;
} SOC_SMART_RTCCR_NA0_UNION;
#endif
#define SOC_SMART_RTCCR_NA0_rtccr_na0_START (0)
#define SOC_SMART_RTCCR_NA0_rtccr_na0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_na1 : 8;
    } reg;
} SOC_SMART_RTCCR_NA1_UNION;
#endif
#define SOC_SMART_RTCCR_NA1_rtccr_na1_START (0)
#define SOC_SMART_RTCCR_NA1_rtccr_na1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_na2 : 8;
    } reg;
} SOC_SMART_RTCCR_NA2_UNION;
#endif
#define SOC_SMART_RTCCR_NA2_rtccr_na2_START (0)
#define SOC_SMART_RTCCR_NA2_rtccr_na2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_na3 : 8;
    } reg;
} SOC_SMART_RTCCR_NA3_UNION;
#endif
#define SOC_SMART_RTCCR_NA3_rtccr_na3_START (0)
#define SOC_SMART_RTCCR_NA3_rtccr_na3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_na0 : 8;
    } reg;
} SOC_SMART_RTCLR_NA0_UNION;
#endif
#define SOC_SMART_RTCLR_NA0_rtclr_na0_START (0)
#define SOC_SMART_RTCLR_NA0_rtclr_na0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_na1 : 8;
    } reg;
} SOC_SMART_RTCLR_NA1_UNION;
#endif
#define SOC_SMART_RTCLR_NA1_rtclr_na1_START (0)
#define SOC_SMART_RTCLR_NA1_rtclr_na1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_na2 : 8;
    } reg;
} SOC_SMART_RTCLR_NA2_UNION;
#endif
#define SOC_SMART_RTCLR_NA2_rtclr_na2_START (0)
#define SOC_SMART_RTCLR_NA2_rtclr_na2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtclr_na3 : 8;
    } reg;
} SOC_SMART_RTCLR_NA3_UNION;
#endif
#define SOC_SMART_RTCLR_NA3_rtclr_na3_START (0)
#define SOC_SMART_RTCLR_NA3_rtclr_na3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtccr_na : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_RTCCTRL_NA_UNION;
#endif
#define SOC_SMART_RTCCTRL_NA_rtccr_na_START (0)
#define SOC_SMART_RTCCTRL_NA_rtccr_na_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char version : 8;
    } reg;
} SOC_SMART_VERSION_UNION;
#endif
#define SOC_SMART_VERSION_version_START (0)
#define SOC_SMART_VERSION_version_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 8;
    } reg;
} SOC_SMART_RESERVED0_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 8;
    } reg;
} SOC_SMART_RESERVED1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 8;
    } reg;
} SOC_SMART_RESERVED2_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 8;
    } reg;
} SOC_SMART_RESERVED3_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 8;
    } reg;
} SOC_SMART_RESERVED4_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char htol_mode : 4;
        unsigned char reserved : 4;
    } reg;
} SOC_SMART_HTOL_MODE_UNION;
#endif
#define SOC_SMART_HTOL_MODE_htol_mode_START (0)
#define SOC_SMART_HTOL_MODE_htol_mode_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char dac_on_sel : 1;
        unsigned char aux_ibias_cfg : 2;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_DAC_CTRL_UNION;
#endif
#define SOC_SMART_DAC_CTRL_dac_on_sel_START (0)
#define SOC_SMART_DAC_CTRL_dac_on_sel_END (0)
#define SOC_SMART_DAC_CTRL_aux_ibias_cfg_START (1)
#define SOC_SMART_DAC_CTRL_aux_ibias_cfg_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char soft_rst : 8;
    } reg;
} SOC_SMART_CHIP_SOFT_RST_UNION;
#endif
#define SOC_SMART_CHIP_SOFT_RST_soft_rst_START (0)
#define SOC_SMART_CHIP_SOFT_RST_soft_rst_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char pdns_sel : 3;
        unsigned char pdns_mk : 1;
        unsigned char vsys_uv_adj : 1;
        unsigned char nopwr_rc_off : 1;
        unsigned char reserved : 2;
    } reg;
} SOC_SMART_NP_REG_ADJ_UNION;
#endif
#define SOC_SMART_NP_REG_ADJ_pdns_sel_START (0)
#define SOC_SMART_NP_REG_ADJ_pdns_sel_END (2)
#define SOC_SMART_NP_REG_ADJ_pdns_mk_START (3)
#define SOC_SMART_NP_REG_ADJ_pdns_mk_END (3)
#define SOC_SMART_NP_REG_ADJ_vsys_uv_adj_START (4)
#define SOC_SMART_NP_REG_ADJ_vsys_uv_adj_END (4)
#define SOC_SMART_NP_REG_ADJ_nopwr_rc_off_START (5)
#define SOC_SMART_NP_REG_ADJ_nopwr_rc_off_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char nopwr_vcoinsl : 2;
        unsigned char nopwr_en_backup_chg : 1;
        unsigned char reserved : 5;
    } reg;
} SOC_SMART_NP_REG_CHG_UNION;
#endif
#define SOC_SMART_NP_REG_CHG_nopwr_vcoinsl_START (0)
#define SOC_SMART_NP_REG_CHG_nopwr_vcoinsl_END (1)
#define SOC_SMART_NP_REG_CHG_nopwr_en_backup_chg_START (2)
#define SOC_SMART_NP_REG_CHG_nopwr_en_backup_chg_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char no_pwr_resved1 : 8;
    } reg;
} SOC_SMART_NP_RSVED1_UNION;
#endif
#define SOC_SMART_NP_RSVED1_no_pwr_resved1_START (0)
#define SOC_SMART_NP_RSVED1_no_pwr_resved1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char no_pwr_resved2 : 8;
    } reg;
} SOC_SMART_NP_RSVED2_UNION;
#endif
#define SOC_SMART_NP_RSVED2_no_pwr_resved2_START (0)
#define SOC_SMART_NP_RSVED2_no_pwr_resved2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char no_pwr_resved3 : 8;
    } reg;
} SOC_SMART_NP_RSVED3_UNION;
#endif
#define SOC_SMART_NP_RSVED3_no_pwr_resved3_START (0)
#define SOC_SMART_NP_RSVED3_no_pwr_resved3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char no_pwr_resved4 : 8;
    } reg;
} SOC_SMART_NP_RSVED4_UNION;
#endif
#define SOC_SMART_NP_RSVED4_no_pwr_resved4_START (0)
#define SOC_SMART_NP_RSVED4_no_pwr_resved4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtc_clk_step_adj1 : 8;
    } reg;
} SOC_SMART_RTC_ADJ1_UNION;
#endif
#define SOC_SMART_RTC_ADJ1_rtc_clk_step_adj1_START (0)
#define SOC_SMART_RTC_ADJ1_rtc_clk_step_adj1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char rtc_clk_step_adj2 : 8;
    } reg;
} SOC_SMART_RTC_ADJ2_UNION;
#endif
#define SOC_SMART_RTC_ADJ2_rtc_clk_step_adj2_START (0)
#define SOC_SMART_RTC_ADJ2_rtc_clk_step_adj2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char eco_ctrl : 3;
        unsigned char reflash_value_ctrl : 1;
        unsigned char eco_filter_time : 2;
        unsigned char calibration_ctrl : 1;
        unsigned char coul_ctrl_onoff_reg : 1;
    } reg;
} SOC_SMART_CLJ_CTRL_REG_UNION;
#endif
#define SOC_SMART_CLJ_CTRL_REG_eco_ctrl_START (0)
#define SOC_SMART_CLJ_CTRL_REG_eco_ctrl_END (2)
#define SOC_SMART_CLJ_CTRL_REG_reflash_value_ctrl_START (3)
#define SOC_SMART_CLJ_CTRL_REG_reflash_value_ctrl_END (3)
#define SOC_SMART_CLJ_CTRL_REG_eco_filter_time_START (4)
#define SOC_SMART_CLJ_CTRL_REG_eco_filter_time_END (5)
#define SOC_SMART_CLJ_CTRL_REG_calibration_ctrl_START (6)
#define SOC_SMART_CLJ_CTRL_REG_calibration_ctrl_END (6)
#define SOC_SMART_CLJ_CTRL_REG_coul_ctrl_onoff_reg_START (7)
#define SOC_SMART_CLJ_CTRL_REG_coul_ctrl_onoff_reg_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char eco_reflash_time : 8;
    } reg;
} SOC_SMART_ECO_REFALSH_TIME_UNION;
#endif
#define SOC_SMART_ECO_REFALSH_TIME_eco_reflash_time_START (0)
#define SOC_SMART_ECO_REFALSH_TIME_eco_reflash_time_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_out0 : 8;
    } reg;
} SOC_SMART_CL_OUT0_UNION;
#endif
#define SOC_SMART_CL_OUT0_cl_out0_START (0)
#define SOC_SMART_CL_OUT0_cl_out0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_out1 : 8;
    } reg;
} SOC_SMART_CL_OUT1_UNION;
#endif
#define SOC_SMART_CL_OUT1_cl_out1_START (0)
#define SOC_SMART_CL_OUT1_cl_out1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_out2 : 8;
    } reg;
} SOC_SMART_CL_OUT2_UNION;
#endif
#define SOC_SMART_CL_OUT2_cl_out2_START (0)
#define SOC_SMART_CL_OUT2_cl_out2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_out3 : 8;
    } reg;
} SOC_SMART_CL_OUT3_UNION;
#endif
#define SOC_SMART_CL_OUT3_cl_out3_START (0)
#define SOC_SMART_CL_OUT3_cl_out3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_in0 : 8;
    } reg;
} SOC_SMART_CL_IN0_UNION;
#endif
#define SOC_SMART_CL_IN0_cl_in0_START (0)
#define SOC_SMART_CL_IN0_cl_in0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_in1 : 8;
    } reg;
} SOC_SMART_CL_IN1_UNION;
#endif
#define SOC_SMART_CL_IN1_cl_in1_START (0)
#define SOC_SMART_CL_IN1_cl_in1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_in2 : 8;
    } reg;
} SOC_SMART_CL_IN2_UNION;
#endif
#define SOC_SMART_CL_IN2_cl_in2_START (0)
#define SOC_SMART_CL_IN2_cl_in2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_in3 : 8;
    } reg;
} SOC_SMART_CL_IN3_UNION;
#endif
#define SOC_SMART_CL_IN3_cl_in3_START (0)
#define SOC_SMART_CL_IN3_cl_in3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char chg_timer0 : 8;
    } reg;
} SOC_SMART_CHG_TIMER0_UNION;
#endif
#define SOC_SMART_CHG_TIMER0_chg_timer0_START (0)
#define SOC_SMART_CHG_TIMER0_chg_timer0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char chg_timer1 : 8;
    } reg;
} SOC_SMART_CHG_TIMER1_UNION;
#endif
#define SOC_SMART_CHG_TIMER1_chg_timer1_START (0)
#define SOC_SMART_CHG_TIMER1_chg_timer1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char chg_timer2 : 8;
    } reg;
} SOC_SMART_CHG_TIMER2_UNION;
#endif
#define SOC_SMART_CHG_TIMER2_chg_timer2_START (0)
#define SOC_SMART_CHG_TIMER2_chg_timer2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char chg_timer3 : 8;
    } reg;
} SOC_SMART_CHG_TIMER3_UNION;
#endif
#define SOC_SMART_CHG_TIMER3_chg_timer3_START (0)
#define SOC_SMART_CHG_TIMER3_chg_timer3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char load_timer0 : 8;
    } reg;
} SOC_SMART_LOAD_TIMER0_UNION;
#endif
#define SOC_SMART_LOAD_TIMER0_load_timer0_START (0)
#define SOC_SMART_LOAD_TIMER0_load_timer0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char load_timer1 : 8;
    } reg;
} SOC_SMART_LOAD_TIMER1_UNION;
#endif
#define SOC_SMART_LOAD_TIMER1_load_timer1_START (0)
#define SOC_SMART_LOAD_TIMER1_load_timer1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char load_timer2 : 8;
    } reg;
} SOC_SMART_LOAD_TIMER2_UNION;
#endif
#define SOC_SMART_LOAD_TIMER2_load_timer2_START (0)
#define SOC_SMART_LOAD_TIMER2_load_timer2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char load_timer3 : 8;
    } reg;
} SOC_SMART_LOAD_TIMER3_UNION;
#endif
#define SOC_SMART_LOAD_TIMER3_load_timer3_START (0)
#define SOC_SMART_LOAD_TIMER3_load_timer3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char off_timer0 : 8;
    } reg;
} SOC_SMART_OFF_TIMER0_UNION;
#endif
#define SOC_SMART_OFF_TIMER0_off_timer0_START (0)
#define SOC_SMART_OFF_TIMER0_off_timer0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char off_timer1 : 8;
    } reg;
} SOC_SMART_OFF_TIMER1_UNION;
#endif
#define SOC_SMART_OFF_TIMER1_off_timer1_START (0)
#define SOC_SMART_OFF_TIMER1_off_timer1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char off_timer2 : 8;
    } reg;
} SOC_SMART_OFF_TIMER2_UNION;
#endif
#define SOC_SMART_OFF_TIMER2_off_timer2_START (0)
#define SOC_SMART_OFF_TIMER2_off_timer2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char off_timer3 : 8;
    } reg;
} SOC_SMART_OFF_TIMER3_UNION;
#endif
#define SOC_SMART_OFF_TIMER3_off_timer3_START (0)
#define SOC_SMART_OFF_TIMER3_off_timer3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int0 : 8;
    } reg;
} SOC_SMART_CL_INT0_UNION;
#endif
#define SOC_SMART_CL_INT0_cl_int0_START (0)
#define SOC_SMART_CL_INT0_cl_int0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int1 : 8;
    } reg;
} SOC_SMART_CL_INT1_UNION;
#endif
#define SOC_SMART_CL_INT1_cl_int1_START (0)
#define SOC_SMART_CL_INT1_cl_int1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int2 : 8;
    } reg;
} SOC_SMART_CL_INT2_UNION;
#endif
#define SOC_SMART_CL_INT2_cl_int2_START (0)
#define SOC_SMART_CL_INT2_cl_int2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cl_int3 : 8;
    } reg;
} SOC_SMART_CL_INT3_UNION;
#endif
#define SOC_SMART_CL_INT3_cl_int3_START (0)
#define SOC_SMART_CL_INT3_cl_int3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_int0 : 8;
    } reg;
} SOC_SMART_V_INT0_UNION;
#endif
#define SOC_SMART_V_INT0_v_int0_START (0)
#define SOC_SMART_V_INT0_v_int0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_int1 : 8;
    } reg;
} SOC_SMART_V_INT1_UNION;
#endif
#define SOC_SMART_V_INT1_v_int1_START (0)
#define SOC_SMART_V_INT1_v_int1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char offset_current0 : 8;
    } reg;
} SOC_SMART_OFFSET_CURRENT0_UNION;
#endif
#define SOC_SMART_OFFSET_CURRENT0_offset_current0_START (0)
#define SOC_SMART_OFFSET_CURRENT0_offset_current0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char offset_current1 : 8;
    } reg;
} SOC_SMART_OFFSET_CURRENT1_UNION;
#endif
#define SOC_SMART_OFFSET_CURRENT1_offset_current1_START (0)
#define SOC_SMART_OFFSET_CURRENT1_offset_current1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char offset_voltage0 : 8;
    } reg;
} SOC_SMART_OFFSET_VOLTAGE0_UNION;
#endif
#define SOC_SMART_OFFSET_VOLTAGE0_offset_voltage0_START (0)
#define SOC_SMART_OFFSET_VOLTAGE0_offset_voltage0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char offset_voltage1 : 8;
    } reg;
} SOC_SMART_OFFSET_VOLTAGE1_UNION;
#endif
#define SOC_SMART_OFFSET_VOLTAGE1_offset_voltage1_START (0)
#define SOC_SMART_OFFSET_VOLTAGE1_offset_voltage1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocv_data0 : 8;
    } reg;
} SOC_SMART_OCV_DATA1_UNION;
#endif
#define SOC_SMART_OCV_DATA1_ocv_data0_START (0)
#define SOC_SMART_OCV_DATA1_ocv_data0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char ocv_data1 : 8;
    } reg;
} SOC_SMART_OCV_DATA2_UNION;
#endif
#define SOC_SMART_OCV_DATA2_ocv_data1_START (0)
#define SOC_SMART_OCV_DATA2_ocv_data1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre0 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE0_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE0_v_out0_pre0_START (0)
#define SOC_SMART_V_OUT0_PRE0_v_out0_pre0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre0 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE0_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE0_v_out1_pre0_START (0)
#define SOC_SMART_V_OUT1_PRE0_v_out1_pre0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre1 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE1_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE1_v_out0_pre1_START (0)
#define SOC_SMART_V_OUT0_PRE1_v_out0_pre1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre1 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE1_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE1_v_out1_pre1_START (0)
#define SOC_SMART_V_OUT1_PRE1_v_out1_pre1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre2 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE2_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE2_v_out0_pre2_START (0)
#define SOC_SMART_V_OUT0_PRE2_v_out0_pre2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre2 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE2_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE2_v_out1_pre2_START (0)
#define SOC_SMART_V_OUT1_PRE2_v_out1_pre2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre3 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE3_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE3_v_out0_pre3_START (0)
#define SOC_SMART_V_OUT0_PRE3_v_out0_pre3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre3 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE3_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE3_v_out1_pre3_START (0)
#define SOC_SMART_V_OUT1_PRE3_v_out1_pre3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre4 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE4_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE4_v_out0_pre4_START (0)
#define SOC_SMART_V_OUT0_PRE4_v_out0_pre4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre4 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE4_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE4_v_out1_pre4_START (0)
#define SOC_SMART_V_OUT1_PRE4_v_out1_pre4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre5 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE5_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE5_v_out0_pre5_START (0)
#define SOC_SMART_V_OUT0_PRE5_v_out0_pre5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre5 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE5_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE5_v_out1_pre5_START (0)
#define SOC_SMART_V_OUT1_PRE5_v_out1_pre5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre6 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE6_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE6_v_out0_pre6_START (0)
#define SOC_SMART_V_OUT0_PRE6_v_out0_pre6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre6 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE6_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE6_v_out1_pre6_START (0)
#define SOC_SMART_V_OUT1_PRE6_v_out1_pre6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre7 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE7_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE7_v_out0_pre7_START (0)
#define SOC_SMART_V_OUT0_PRE7_v_out0_pre7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre7 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE7_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE7_v_out1_pre7_START (0)
#define SOC_SMART_V_OUT1_PRE7_v_out1_pre7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre8 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE8_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE8_v_out0_pre8_START (0)
#define SOC_SMART_V_OUT0_PRE8_v_out0_pre8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre8 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE8_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE8_v_out1_pre8_START (0)
#define SOC_SMART_V_OUT1_PRE8_v_out1_pre8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre9 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE9_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE9_v_out0_pre9_START (0)
#define SOC_SMART_V_OUT0_PRE9_v_out0_pre9_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre9 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE9_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE9_v_out1_pre9_START (0)
#define SOC_SMART_V_OUT1_PRE9_v_out1_pre9_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre10 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE10_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE10_v_out0_pre10_START (0)
#define SOC_SMART_V_OUT0_PRE10_v_out0_pre10_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre10 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE10_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE10_v_out1_pre10_START (0)
#define SOC_SMART_V_OUT1_PRE10_v_out1_pre10_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre11 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE11_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE11_v_out0_pre11_START (0)
#define SOC_SMART_V_OUT0_PRE11_v_out0_pre11_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre11 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE11_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE11_v_out1_pre11_START (0)
#define SOC_SMART_V_OUT1_PRE11_v_out1_pre11_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre12 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE12_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE12_v_out0_pre12_START (0)
#define SOC_SMART_V_OUT0_PRE12_v_out0_pre12_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre12 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE12_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE12_v_out1_pre12_START (0)
#define SOC_SMART_V_OUT1_PRE12_v_out1_pre12_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre13 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE13_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE13_v_out0_pre13_START (0)
#define SOC_SMART_V_OUT0_PRE13_v_out0_pre13_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre13 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE13_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE13_v_out1_pre13_START (0)
#define SOC_SMART_V_OUT1_PRE13_v_out1_pre13_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre14 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE14_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE14_v_out0_pre14_START (0)
#define SOC_SMART_V_OUT0_PRE14_v_out0_pre14_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre14 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE14_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE14_v_out1_pre14_START (0)
#define SOC_SMART_V_OUT1_PRE14_v_out1_pre14_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre15 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE15_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE15_v_out0_pre15_START (0)
#define SOC_SMART_V_OUT0_PRE15_v_out0_pre15_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre15 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE15_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE15_v_out1_pre15_START (0)
#define SOC_SMART_V_OUT1_PRE15_v_out1_pre15_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre16 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE16_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE16_v_out0_pre16_START (0)
#define SOC_SMART_V_OUT0_PRE16_v_out0_pre16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre16 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE16_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE16_v_out1_pre16_START (0)
#define SOC_SMART_V_OUT1_PRE16_v_out1_pre16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre17 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE17_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE17_v_out0_pre17_START (0)
#define SOC_SMART_V_OUT0_PRE17_v_out0_pre17_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre17 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE17_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE17_v_out1_pre17_START (0)
#define SOC_SMART_V_OUT1_PRE17_v_out1_pre17_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre18 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE18_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE18_v_out0_pre18_START (0)
#define SOC_SMART_V_OUT0_PRE18_v_out0_pre18_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre18 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE18_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE18_v_out1_pre18_START (0)
#define SOC_SMART_V_OUT1_PRE18_v_out1_pre18_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out0_pre19 : 8;
    } reg;
} SOC_SMART_V_OUT0_PRE19_UNION;
#endif
#define SOC_SMART_V_OUT0_PRE19_v_out0_pre19_START (0)
#define SOC_SMART_V_OUT0_PRE19_v_out0_pre19_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_out1_pre19 : 8;
    } reg;
} SOC_SMART_V_OUT1_PRE19_UNION;
#endif
#define SOC_SMART_V_OUT1_PRE19_v_out1_pre19_START (0)
#define SOC_SMART_V_OUT1_PRE19_v_out1_pre19_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre0 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE0_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE0_current0_pre0_START (0)
#define SOC_SMART_CURRENT0_PRE0_current0_pre0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre0 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE0_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE0_current1_pre0_START (0)
#define SOC_SMART_CURRENT1_PRE0_current1_pre0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre1 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE1_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE1_current0_pre1_START (0)
#define SOC_SMART_CURRENT0_PRE1_current0_pre1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre1 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE1_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE1_current1_pre1_START (0)
#define SOC_SMART_CURRENT1_PRE1_current1_pre1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre2 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE2_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE2_current0_pre2_START (0)
#define SOC_SMART_CURRENT0_PRE2_current0_pre2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre2 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE2_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE2_current1_pre2_START (0)
#define SOC_SMART_CURRENT1_PRE2_current1_pre2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre3 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE3_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE3_current0_pre3_START (0)
#define SOC_SMART_CURRENT0_PRE3_current0_pre3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre3 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE3_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE3_current1_pre3_START (0)
#define SOC_SMART_CURRENT1_PRE3_current1_pre3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre4 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE4_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE4_current0_pre4_START (0)
#define SOC_SMART_CURRENT0_PRE4_current0_pre4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre4 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE4_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE4_current1_pre4_START (0)
#define SOC_SMART_CURRENT1_PRE4_current1_pre4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre5 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE5_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE5_current0_pre5_START (0)
#define SOC_SMART_CURRENT0_PRE5_current0_pre5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre5 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE5_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE5_current1_pre5_START (0)
#define SOC_SMART_CURRENT1_PRE5_current1_pre5_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre6 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE6_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE6_current0_pre6_START (0)
#define SOC_SMART_CURRENT0_PRE6_current0_pre6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre6 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE6_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE6_current1_pre6_START (0)
#define SOC_SMART_CURRENT1_PRE6_current1_pre6_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre7 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE7_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE7_current0_pre7_START (0)
#define SOC_SMART_CURRENT0_PRE7_current0_pre7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre7 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE7_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE7_current1_pre7_START (0)
#define SOC_SMART_CURRENT1_PRE7_current1_pre7_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre8 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE8_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE8_current0_pre8_START (0)
#define SOC_SMART_CURRENT0_PRE8_current0_pre8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre8 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE8_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE8_current1_pre8_START (0)
#define SOC_SMART_CURRENT1_PRE8_current1_pre8_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre9 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE9_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE9_current0_pre9_START (0)
#define SOC_SMART_CURRENT0_PRE9_current0_pre9_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre9 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE9_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE9_current1_pre9_START (0)
#define SOC_SMART_CURRENT1_PRE9_current1_pre9_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre10 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE10_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE10_current0_pre10_START (0)
#define SOC_SMART_CURRENT0_PRE10_current0_pre10_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre10 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE10_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE10_current1_pre10_START (0)
#define SOC_SMART_CURRENT1_PRE10_current1_pre10_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre11 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE11_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE11_current0_pre11_START (0)
#define SOC_SMART_CURRENT0_PRE11_current0_pre11_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre11 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE11_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE11_current1_pre11_START (0)
#define SOC_SMART_CURRENT1_PRE11_current1_pre11_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre12 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE12_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE12_current0_pre12_START (0)
#define SOC_SMART_CURRENT0_PRE12_current0_pre12_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre12 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE12_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE12_current1_pre12_START (0)
#define SOC_SMART_CURRENT1_PRE12_current1_pre12_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre13 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE13_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE13_current0_pre13_START (0)
#define SOC_SMART_CURRENT0_PRE13_current0_pre13_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre13 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE13_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE13_current1_pre13_START (0)
#define SOC_SMART_CURRENT1_PRE13_current1_pre13_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre14 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE14_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE14_current0_pre14_START (0)
#define SOC_SMART_CURRENT0_PRE14_current0_pre14_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre14 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE14_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE14_current1_pre14_START (0)
#define SOC_SMART_CURRENT1_PRE14_current1_pre14_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre15 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE15_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE15_current0_pre15_START (0)
#define SOC_SMART_CURRENT0_PRE15_current0_pre15_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre15 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE15_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE15_current1_pre15_START (0)
#define SOC_SMART_CURRENT1_PRE15_current1_pre15_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre16 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE16_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE16_current0_pre16_START (0)
#define SOC_SMART_CURRENT0_PRE16_current0_pre16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre16 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE16_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE16_current1_pre16_START (0)
#define SOC_SMART_CURRENT1_PRE16_current1_pre16_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre17 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE17_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE17_current0_pre17_START (0)
#define SOC_SMART_CURRENT0_PRE17_current0_pre17_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre17 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE17_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE17_current1_pre17_START (0)
#define SOC_SMART_CURRENT1_PRE17_current1_pre17_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre18 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE18_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE18_current0_pre18_START (0)
#define SOC_SMART_CURRENT0_PRE18_current0_pre18_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre18 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE18_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE18_current1_pre18_START (0)
#define SOC_SMART_CURRENT1_PRE18_current1_pre18_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current0_pre19 : 8;
    } reg;
} SOC_SMART_CURRENT0_PRE19_UNION;
#endif
#define SOC_SMART_CURRENT0_PRE19_current0_pre19_START (0)
#define SOC_SMART_CURRENT0_PRE19_current0_pre19_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char current1_pre19 : 8;
    } reg;
} SOC_SMART_CURRENT1_PRE19_UNION;
#endif
#define SOC_SMART_CURRENT1_PRE19_current1_pre19_START (0)
#define SOC_SMART_CURRENT1_PRE19_current1_pre19_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char cic_clk_inv_i : 1;
        unsigned char cic_clk_inv_v : 1;
        unsigned char adc_ana_v_output : 1;
        unsigned char adc_ana_i_output : 1;
        unsigned char cali_en_i : 1;
        unsigned char cali_en_i_force : 1;
        unsigned char cali_en_v_force : 1;
        unsigned char cali_en_v : 1;
    } reg;
} SOC_SMART_CLJ_DEBUG_UNION;
#endif
#define SOC_SMART_CLJ_DEBUG_cic_clk_inv_i_START (0)
#define SOC_SMART_CLJ_DEBUG_cic_clk_inv_i_END (0)
#define SOC_SMART_CLJ_DEBUG_cic_clk_inv_v_START (1)
#define SOC_SMART_CLJ_DEBUG_cic_clk_inv_v_END (1)
#define SOC_SMART_CLJ_DEBUG_adc_ana_v_output_START (2)
#define SOC_SMART_CLJ_DEBUG_adc_ana_v_output_END (2)
#define SOC_SMART_CLJ_DEBUG_adc_ana_i_output_START (3)
#define SOC_SMART_CLJ_DEBUG_adc_ana_i_output_END (3)
#define SOC_SMART_CLJ_DEBUG_cali_en_i_START (4)
#define SOC_SMART_CLJ_DEBUG_cali_en_i_END (4)
#define SOC_SMART_CLJ_DEBUG_cali_en_i_force_START (5)
#define SOC_SMART_CLJ_DEBUG_cali_en_i_force_END (5)
#define SOC_SMART_CLJ_DEBUG_cali_en_v_force_START (6)
#define SOC_SMART_CLJ_DEBUG_cali_en_v_force_END (6)
#define SOC_SMART_CLJ_DEBUG_cali_en_v_START (7)
#define SOC_SMART_CLJ_DEBUG_cali_en_v_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char state_test : 8;
    } reg;
} SOC_SMART_STATE_TEST_UNION;
#endif
#define SOC_SMART_STATE_TEST_state_test_START (0)
#define SOC_SMART_STATE_TEST_state_test_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reg_data_clr : 1;
        unsigned char clj_rw_inf1 : 7;
    } reg;
} SOC_SMART_CLJ_RESERVED1_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED1_reg_data_clr_START (0)
#define SOC_SMART_CLJ_RESERVED1_reg_data_clr_END (0)
#define SOC_SMART_CLJ_RESERVED1_clj_rw_inf1_START (1)
#define SOC_SMART_CLJ_RESERVED1_clj_rw_inf1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char clj_rw_inf2 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED2_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED2_clj_rw_inf2_START (0)
#define SOC_SMART_CLJ_RESERVED2_clj_rw_inf2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char clj_rw_inf3 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED3_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED3_clj_rw_inf3_START (0)
#define SOC_SMART_CLJ_RESERVED3_clj_rw_inf3_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char clj_rw_inf4 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED4_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED4_clj_rw_inf4_START (0)
#define SOC_SMART_CLJ_RESERVED4_clj_rw_inf4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char i_reserve_1 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED5_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED5_i_reserve_1_START (0)
#define SOC_SMART_CLJ_RESERVED5_i_reserve_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char i_reserve_2 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED6_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED6_i_reserve_2_START (0)
#define SOC_SMART_CLJ_RESERVED6_i_reserve_2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_reserve_1 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED7_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED7_v_reserve_1_START (0)
#define SOC_SMART_CLJ_RESERVED7_v_reserve_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char v_reserve_2 : 8;
    } reg;
} SOC_SMART_CLJ_RESERVED8_UNION;
#endif
#define SOC_SMART_CLJ_RESERVED8_v_reserve_2_START (0)
#define SOC_SMART_CLJ_RESERVED8_v_reserve_2_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char hkadc_chanl_sel : 5;
        unsigned char hkadc_fre_sel : 2;
        unsigned char hkadc_bapass : 1;
    } reg;
} SOC_SMART_ADC_CTRL_UNION;
#endif
#define SOC_SMART_ADC_CTRL_hkadc_chanl_sel_START (0)
#define SOC_SMART_ADC_CTRL_hkadc_chanl_sel_END (4)
#define SOC_SMART_ADC_CTRL_hkadc_fre_sel_START (5)
#define SOC_SMART_ADC_CTRL_hkadc_fre_sel_END (6)
#define SOC_SMART_ADC_CTRL_hkadc_bapass_START (7)
#define SOC_SMART_ADC_CTRL_hkadc_bapass_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char hkadc_start : 1;
        unsigned char hkadc_buffer_sel : 1;
        unsigned char hkadc_config : 6;
    } reg;
} SOC_SMART_ADC_CONV_UNION;
#endif
#define SOC_SMART_ADC_CONV_hkadc_start_START (0)
#define SOC_SMART_ADC_CONV_hkadc_start_END (0)
#define SOC_SMART_ADC_CONV_hkadc_buffer_sel_START (1)
#define SOC_SMART_ADC_CONV_hkadc_buffer_sel_END (1)
#define SOC_SMART_ADC_CONV_hkadc_config_START (2)
#define SOC_SMART_ADC_CONV_hkadc_config_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char hkadc_busy : 1;
        unsigned char reserved : 7;
    } reg;
} SOC_SMART_CONV_STATUS_UNION;
#endif
#define SOC_SMART_CONV_STATUS_hkadc_busy_START (0)
#define SOC_SMART_CONV_STATUS_hkadc_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char hkadc_data11_4 : 8;
    } reg;
} SOC_SMART_ADC_DATA1_UNION;
#endif
#define SOC_SMART_ADC_DATA1_hkadc_data11_4_START (0)
#define SOC_SMART_ADC_DATA1_hkadc_data11_4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char reserved : 4;
        unsigned char hkadc_data3_0 : 4;
    } reg;
} SOC_SMART_ADC_DATA0_UNION;
#endif
#define SOC_SMART_ADC_DATA0_hkadc_data3_0_START (4)
#define SOC_SMART_ADC_DATA0_hkadc_data3_0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned char value;
    struct
    {
        unsigned char hkadc_ibias_sel : 8;
    } reg;
} SOC_SMART_ADC_CURRENT_UNION;
#endif
#define SOC_SMART_ADC_CURRENT_hkadc_ibias_sel_START (0)
#define SOC_SMART_ADC_CURRENT_hkadc_ibias_sel_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif

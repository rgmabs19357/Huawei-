/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : SysCtrl_reg
  版 本 号   : 初稿
  生成日期   : 2012年8月9日
  最近修改   :
  功能描述   : edc_regctrl.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年8月9日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SYSCTRL_REG_H__
#define __SYSCTRL_REG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "hi_type.h"





/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define SYS_CTRL_BASE          			(0xF711A000)		//B050
#define SYS_CTRL_REG_SIZE			    (0x2000) 
#define AOSYS_CTRL_BASE                 (0xF7410000)
#define AOSYS_CTRL_REG_SIZE             (0x2000)
#define PM_CTRL_BASE			        (0xF711C000)		//B050
#define PM_CTRL_REG_SIZE		        (0x1000)

#define SC_PW_EN0_OFFSET                (0x830 / 4)	
#define SC_PW_CLKEN0_OFFSET				(0x800 / 4)	
#define SC_PW_ISODIS0_OFFSET            (0x824 / 4)	
#define SC_PW_RSTDIS0_OFFSET            (0x814 / 4)
#define SC_PERIPH_CLKEN1_OFFSET         (0x60C / 4)
#define SC_PERIPH_CLKEN2_OFFSET         (0x618 / 4)
#define SC_PERIPH_CLKEN11_OFFSET        (0x684 / 4)
#define SC_PERIPH_CLKEN12_OFFSET        (0x690 / 4)
#define SC_PERIPH_RSTDIS1_OFFSET		(0x6D0 / 4)
#define SC_PERIPH_RSTDIS7_OFFSET		(0x718 / 4)
										
#define SC_CLKCFG8BIT7			        (0xCC0 / 4)										

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*Add for B050,begin*/
typedef struct
{
    DWORD   pw_en0_0peri                        :1;
    DWORD   pw_en0_1g3d                         :1;
    DWORD   pw_en0_2g2d                         :1;
    DWORD   pw_en0_3edc0                        :1;
    DWORD   pw_en0_4edc1                        :1;
    DWORD   pw_en0_5isp                         :1;
    DWORD   pw_en0_6enc                         :1;
    DWORD   pw_en0_7dec                         :1;
    DWORD   pw_en0_8hifi                        :1;
    DWORD   pw_en0_9vpp                         :1;
    DWORD   pw_en0_10dspbbe                     :1;
    DWORD   pw_en0_11ddrctrl                    :1;
    DWORD   pw_en0_12bbpcommtop2c_gbbp1         :1;
    DWORD   pw_en0_13bbpcommtop2d_gbbp2         :1;
    DWORD   pw_en0_14ltebbptop                  :1;
    DWORD   pw_en0_15bbpcommtop2b_bbpcomm2      :1;
    DWORD   pw_en0_16bbpcommtop2a_bbpcomm1      :1;
    DWORD   pw_en0_17bbpcommtop1b_wtdbbp2       :1;
    DWORD   pw_en0_18bbpcommtop1a_wtdbbp1       :1;
    DWORD   pw_en0_19abbana                     :1;
    DWORD   pw_en0_20usbphy                     :1;
    DWORD   pw_en0_21reserved                   :1;
    DWORD   pw_en0_22cs0phy                     :1;
    DWORD   pw_en0_23reserved                   :1;
    DWORD   pw_en0_24cs2phy                     :1;
    DWORD   pw_en0_25dsiphy                     :1;
    DWORD   pw_en0_26hdmiphy                    :1;
    DWORD   pw_en0_27ddrphy                     :1;
    DWORD   pw_en0_28pll1                       :1;
    DWORD   pw_en0_29tsensor0                   :1;
    DWORD   pw_en0_30tsensor1                   :1;
    DWORD   pw_en0_31reserved                   :1;   
}st_SC_PW_EN0;

typedef struct
{
    DWORD   pw_isodis0_0peri                        :1;
    DWORD   pw_isodis0_1g3d                         :1;
    DWORD   pw_isodis0_2g2d                         :1;
    DWORD   pw_isodis0_3edc0                        :1;
    DWORD   pw_isodis0_4edc1                        :1;
    DWORD   pw_isodis0_5isp                         :1;
    DWORD   pw_isodis0_6enc                         :1;
    DWORD   pw_isodis0_7dec                         :1;
    DWORD   pw_isodis0_8hifi                        :1;
    DWORD   pw_isodis0_9vpp                         :1;
    DWORD   pw_isodis0_10dspbbe                     :1;
    DWORD   pw_isodis0_11ddrctrl                    :1;
    DWORD   pw_isodis0_12bbpcommtop2c_gbbp1         :1;
    DWORD   pw_isodis0_13bbpcommtop2d_gbbp2         :1;
    DWORD   pw_isodis0_14ltebbptop                  :1;
    DWORD   pw_isodis0_15bbpcommtop2b_bbpcomm2      :1;
    DWORD   pw_isodis0_16bbpcommtop2a_bbpcomm1      :1;
    DWORD   pw_isodis0_17bbpcommtop1b_wtdbbp2       :1;
    DWORD   pw_isodis0_18bbpcommtop1a_wtdbbp1       :1;
    DWORD   pw_isodis0_19abbana                     :1;
    DWORD   pw_isodis0_20usbphy                     :1;
    DWORD   pw_isodis0_21reserved                   :1;
    DWORD   pw_isodis0_22cs0phy                     :1;
    DWORD   pw_isodis0_23reserved                   :1;
    DWORD   pw_isodis0_24cs2phy                     :1;
    DWORD   pw_isodis0_25dsiphy                     :1;
    DWORD   pw_isodis0_26hdmiphy                    :1;
    DWORD   pw_isodis0_27ddrphy                     :1;
    DWORD   pw_isodis0_28pll1                       :1;
    DWORD   pw_isodis0_29tsensor0                   :1;
    DWORD   pw_isodis0_30tsensor1                   :1;
    DWORD   pw_isodis0_31reserved                   :1;   
}st_SC_PW_ISODIS0;

typedef struct
{
    DWORD   bitOther1				                :14;
    DWORD   periph_clken1_spi0_pclk                 :1;
    DWORD   periph_clken1_spi0                      :1;
    DWORD   bitOther2				                :16;
 
}st_SC_PERIPH_CLKEN1;

typedef struct
{
    DWORD   bitOther1				                      :22;
    DWORD   periph_clkstat12_mux_edc0_pix_gated           :1;
    DWORD   periph_clkstat12_dsppll_edc0_core_gated       :1;
    DWORD   bitOther2				                      :8;
 
}st_SC_PERIPH_CLKEN12;


typedef struct
{
    DWORD   periph_rstdis1_0uart0               :1;
    DWORD   periph_rstdis1_1uart1               :1;
    DWORD   periph_rstdis1_2uart2               :1;
    DWORD   periph_rstdis1_3uart3               :1;
    DWORD   periph_rstdis1_4uart4               :1;
    DWORD   periph_rstdis1_5uart5               :1;
    DWORD   periph_rstdis1_6uart6               :1;
    DWORD   periph_rstdis1_7spi0                :1;
    DWORD   periph_rstdis1_8spi1                :1;
    DWORD   periph_rstdis1_9i2c0                :1;
    DWORD   periph_rstdis1_10i2c1               :1;
    DWORD   periph_rstdis1_11i2c2               :1;
    DWORD   periph_rstdis1_12i2c3               :1;
    DWORD   periph_rstdis1_13i2c4               :1;
    DWORD   periph_rstdis1_14i2c5               :1;
    DWORD   periph_rstdis1_15catb               :1;
    DWORD   periph_rstdis1_16cctm               :1;
    DWORD   periph_rstdis1_17ctpiu              :1;
    DWORD   periph_rstdis1_18cdbgapb            :1;
    DWORD   periph_rstdis1_19pwm0               :1;
    DWORD   periph_rstdis1_20pwm1               :1;
    DWORD   periph_rstdis1_21reset_ipf_n        :1;
    DWORD   periph_rstdis1_22reset_socp_n       :1;
    DWORD   bitreserve0                         :1;
    DWORD   periph_rstdis1_24reset_admac_n      :1;
    DWORD   periph_rstdis1_25reset_seceng_n     :1;
    DWORD   periph_rstdis1_26usbotgub           :1;
    DWORD   periph_rstdis1_27usbotguw           :1;
    DWORD   bitreserve1                         :1;
    DWORD   bitreserve2                         :1;
    DWORD   periph_rstdis1_30reserved           :1;
    DWORD   periph_rstdis1_31reserved           :1;   
}st_SC_PERIPH_RSTDIS1;

typedef struct
{
    DWORD periph_rstdis7_0e0power               :1;
    DWORD periph_rstdis7_1e0axi                 :1;
    DWORD periph_rstdis7_2e0pixldi              :1;
    DWORD periph_rstdis7_3e0core                :1;
    DWORD periph_rstdis7_4e1power               :1;
    DWORD periph_rstdis7_5e1axi                 :1;
    DWORD periph_rstdis7_6e1pixldi              :1;
    DWORD periph_rstdis7_7e1core                :1;
    DWORD periph_rstdis7_8hdmiapbs              :1;
    DWORD periph_rstdis7_9hdmie                 :1;
    DWORD periph_rstdis7_10isppower             :1;
    DWORD periph_rstdis7_11ispaxi               :1;
    DWORD periph_rstdis7_12ispwork              :1;
    DWORD periph_rstdis7_13iref                 :1;
    DWORD periph_rstdis7_14vencw                :1;
    DWORD periph_rstdis7_15vdecw                :1;
    DWORD periph_rstdis7_16reserved             :1;
    DWORD periph_rstdis7_17vppw                 :1;
    DWORD periph_rstdis7_18g2dcon               :1;
    DWORD periph_rstdis7_19g2daxi               :1;
    DWORD periph_rstdis7_20g2dcore              :1;
    DWORD periph_rstdis7_21reset_mali           :1;
    DWORD periph_rstdis7_22hdmi                 :1;
    DWORD periph_rstdis7_23csi0                 :1;
    DWORD periph_rstdis7_24csi1                 :1;
    DWORD periph_rstdis7_25csi2                 :1;
    DWORD periph_rstdis7_26csi3                 :1;
    DWORD periph_rstdis7_27ispreset             :1;
    DWORD periph_rstdis7_31reserved             :4;
}st_SC_PERIPH_RSTDIS7;

typedef struct
{
    DWORD pw_rstdis0_0peri                      :1;
    DWORD pw_rstdis0_1g3d                       :1;
    DWORD pw_rstdis0_2g2d                       :1;
    DWORD pw_rstdis0_3edc0                      :1;
    DWORD pw_rstdis0_4edc1                      :1;
    DWORD pw_rstdis0_5isp                       :1;
    DWORD pw_rstdis0_6enc                       :1;
    DWORD pw_rstdis0_7dec                       :1;
    DWORD pw_rstdis0_8hifi                      :1;
    DWORD pw_rstdis0_9vpp                       :1;
    DWORD pw_rstdis0_10dspbbe                   :1;
    DWORD pw_rstdis0_11ddrctrl                  :1;
    DWORD pw_rstdis0_12bbpcommtop2c_gbbp1       :1;
    DWORD pw_rstdis0_13bbpcommtop2d_gbbp2       :1;
    DWORD pw_rstdis0_14ltebbptop                :1;
    DWORD pw_rstdis0_15bbpcommtop2b_bbpcomm2    :1;
    DWORD pw_rstdis0_16bbpcommtop2a_bbpcomm1    :1;
    DWORD pw_rstdis0_17bbpcommtop1b_wtdbbp2     :1;
    DWORD pw_rstdis0_18bbpcommtop1a_wtdbbp1     :1;
    DWORD pw_rstdis0_19abbana                   :1;
    DWORD pw_rstdis0_20usbphy                   :1;
    DWORD pw_rstdis0_21reserved                 :1;
    DWORD pw_rstdis0_22cs0phy                   :1;
    DWORD pw_rstdis0_23reserved                 :1;
    DWORD pw_rstdis0_24cs2phy                   :1;
    DWORD pw_rstdis0_25dsiphy                   :1;
    DWORD pw_rstdis0_26hdmiphy                  :1;
    DWORD pw_rstdis0_27ddrphy                   :1;
    DWORD pw_rstdis0_28pll1                     :1;
    DWORD pw_rstdis0_29tsensor0                 :1;
    DWORD pw_rstdis0_30tsensor1                 :1;
    DWORD pw_rstdis0_31reserved                 :1;    
}st_SC_PW_RSTDIS0;

typedef struct
{
    DWORD periph_clken2_pwm0_pclk                   :1;
    DWORD periph_clken2_pwm0                        :1;
    DWORD periph_clken2_pwm1_pclk                   :1;
    DWORD periph_clken2_pwm1                        :1;
    DWORD periph_clken2_clk_coresight_atb           :1;
    DWORD periph_clken2_clk_coresight_ctm           :1;
    DWORD periph_clken2_clk_coresight_tpiu          :1;
    DWORD periph_clken2_clk_coresight_debug_apb     :1;
    DWORD periph_clken2_tsensor0_clk                :1;
    DWORD periph_clken2_tsensor1_clk                :1;
    DWORD periph_clken2_ipf_axi                     :1;
    DWORD periph_clken2_ipf_hclk                    :1;
    DWORD periph_clken2_ipf                         :1;
    DWORD periph_clken2_socp_axi                    :1;
    DWORD reserve0                                  :1;
    DWORD periph_clken2_seceng_core                 :1;
    DWORD periph_clken2_seceng_axi                  :1;
    DWORD periph_clken2_ap_dmac_axi0                :1;
    DWORD periph_clken2_ap_dmac_axi1                :1;
    DWORD periph_clken2_usbotg_bus_clk              :1;
    DWORD periph_clken2_usbotg_work_clk             :1;
    DWORD reserve1                                  :1;
    DWORD reserve2                                  :1;
    DWORD reserve3                                  :1;
    DWORD reserve4                                  :1;
    DWORD reserve5                                  :1;
    DWORD reserve6                                  :1;
    DWORD reserve7                                  :1;
    DWORD reserve8                                  :1;
    DWORD periph_clken2_clk_x2sram                  :1;
    DWORD periph_clken2_x2sram_rom                  :1;
    DWORD reserve9                                  :1;
}st_SC_PERIPH_CLKEN2;

typedef struct
{
    DWORD periph_clken11_edc0_cfg_clk               :1;
    DWORD periph_clken11_aclk_edc0                  :1;
    DWORD periph_clken11_edc0_pix_ldi               :1;
    DWORD periph_clken11_edc0_core                  :1;
    DWORD periph_clken11_dsio_cfg_clk               :1;
    DWORD periph_clken11_edc1_cfg_clk               :1;
    DWORD periph_clken11_edc1_axi                   :1;
    DWORD periph_clken11_edc1_pix_ldi               :1;
    DWORD periph_clken11_edc1_core                  :1;
    DWORD periph_clken11_hdmi_master                :1;
    DWORD periph_clken11_hdmi_slave                 :1;
    DWORD periph_clken11_clk_hdmi_sck               :1;
    DWORD periph_clken11_mclk_hdmi                  :1;
    DWORD periph_clken11_hdmi_efusec_cfgclk         :1;
    DWORD periph_clken11_hdmi_efusec_work_clk       :1;
    DWORD periph_clken11_isp_cfg_clk                :1;
    DWORD periph_clken11_isp_axi                    :1;
    DWORD periph_clken11_clk_isp                    :1;
    DWORD periph_clken11_clk_isp_ref                :1;
    DWORD periph_clken11_csi_apb_mux                :1;
    DWORD periph_clken11_clk_csio_cfg               :1;
    DWORD periph_clken11_csi1_cfg_clk               :1;
    DWORD periph_clken11_csi2_cfg_clk               :1;
    DWORD periph_clken11_dphy0_clk                  :1;
    DWORD periph_clken11_dphy1_cfg                  :1;
    DWORD periph_clken11_dphy2_cfg_clk              :1;
    DWORD periph_clken11_dphy0                      :1;
    DWORD reserve0                                  :1;
    DWORD reserve1                                  :1;
    DWORD reserve2                                  :1;
    DWORD reserve3                                  :1;
    DWORD reserve4                                  :1;
}st_SC_PERIPH_CLKEN11;

typedef struct
{
    DWORD pw_clken0_0peri                           :1;
    DWORD pw_clken0_1g3d                            :1;
    DWORD pw_clken0_2g2d                            :1;
    DWORD pw_clken0_3edc0                           :1;
    DWORD pw_clken0_4edc1                           :1;
    DWORD pw_clken0_5isp                            :1;
    DWORD pw_clken0_6enc                            :1;
    DWORD pw_clken0_7dec                            :1;
    DWORD pw_clken0_8hifi                           :1;
    DWORD pw_clken0_9vpp                            :1;
    DWORD pw_clken0_10dspbbe                        :1;
    DWORD pw_clken0_11ddrctrl                       :1;
    DWORD pw_clken0_12bbpcommtop2c_gbbp1            :1;
    DWORD pw_clken0_13bbpcommtop2d_gbbp2            :1;
    DWORD pw_clken0_14ltebbptop                     :1;
    DWORD pw_clken0_15bbpcommtop2b_bbpcomm2         :1;
    DWORD pw_clken0_16bbpcommtop2a_bbpcomm1         :1;
    DWORD pw_clken0_17bbpcommtop1b_wtdbbp2          :1;
    DWORD pw_clken0_18bbpcommtop1a_wtdbbp1          :1;   
    DWORD pw_clken0_19abbana                        :1;
    DWORD pw_clken0_20usbphy                        :1;
    DWORD pw_clken0_21reserved                      :1;
    DWORD pw_clken0_22cs0phy                        :1;
    DWORD pw_clken0_23reserved                      :1;
    DWORD pw_clken0_24cs2phy                        :1;
    DWORD pw_clken0_25dsiphy                        :1;
    DWORD pw_clken0_26hdmiphy                       :1;
    DWORD pw_clken0_27ddrphy                        :1;
    DWORD pw_clken0_28pll1                          :1;
    DWORD pw_clken0_29tsensor0                      :1;
    DWORD pw_clken0_30tsensor1                      :1;
    DWORD pw_clken0_31reserved                      :1;
}st_SC_PW_CLKEN0;

/*Add for B050,end*/
typedef struct
{
	DWORD 	 bitOther1 		:9;
	DWORD	 bitEdc0CfgClk	:1;
	DWORD	 bitEdc0AxiClk	:1;
	DWORD	 bitEdc0PixClk  :1;
	DWORD	 bitEdc0CoreClk :1;
	DWORD	 bitDsi0CfgClk  :1;
	DWORD	 bitEdc1CfgClk	:1;
	DWORD	 bitEdc1AxiClk	:1;
	DWORD	 bitEdc1PixClk  :1;
	DWORD	 bitEdc1CoreClk :1;
	DWORD	 bitOther2		:14;
}st_SC_ClkEn0;


typedef struct
{
	DWORD 	 bitOther1 				:22;
	DWORD	 bitEdc0X2XMasterClk	:1;
	DWORD	 bitEdc0X2XSlaverClk	:1;
	DWORD	 bitOther2				:8;
}st_SC_ClkEn11;

typedef struct
{
	DWORD 	 bitOther1 			:6;

	DWORD	 bitEdc0CfgRstClk	:1;
	DWORD	 bitEdc0AxiRstClk	:1;
	DWORD	 bitEdc0PixRstClk  	:1;
	DWORD	 bitEdc0CoreRstClk 	:1;

	DWORD	 bitEdc1CfgRstClk	:1;
	DWORD	 bitEdc1AxiRstClk	:1;
	DWORD	 bitEdc1PixRstClk   :1;
	DWORD	 bitEdc1CoreRStClk  :1;

	DWORD	 bitOther2		    :18;
}st_SC_RstEn0;

typedef struct
{
	DWORD 	 bitOther1 			:6;

	DWORD	 bitEdc0CfgRstClk	:1;
	DWORD	 bitEdc0AxiRstClk	:1;
	DWORD	 bitEdc0PixRstClk  	:1;
	DWORD	 bitEdc0CoreRstClk 	:1;

	DWORD	 bitEdc1CfgRstClk	:1;
	DWORD	 bitEdc1AxiRstClk	:1;
	DWORD	 bitEdc1PixRstClk   :1;
	DWORD	 bitEdc1CoreRStClk  :1;

	DWORD	 bitOther2		    :18;
}st_SC_RstDis0;

typedef struct
{
	DWORD 	 bitOther1 				:25;
	DWORD	 bitEdc0X2XMasterRstClk	:1;
	DWORD	 bitEdc0X2XSlaverRstClk	:1;
	DWORD	 bitOther2				:5;
}st_SC_RstEn6;

typedef struct
{
	DWORD 	 bitOther1 				:25;
	DWORD	 bitEdc0X2XMasterRstClk	:1;
	DWORD	 bitEdc0X2XSlaverRstClk	:1;
	DWORD	 bitOther2				:5;
}st_SC_RstDis6;



typedef struct
{
	DWORD	 bitOther1				:3;
	DWORD	 bitEdc0PwEn			:1;
	DWORD	 bitEdc1PwEn			:1;
	DWORD	 bitOther2				:27;
}st_SC_PW_En0;

typedef struct
{
	DWORD	bitEdc0PixDiv			:7;
	DWORD	bitEdc0PixValid			:1;
	DWORD	bitEdc0CoreDiv			:7;
	DWORD	bitEdc0CoreValid		:1;

	DWORD	bitEdc1PixDiv			:7;
	DWORD	bitEdc1PixValid			:1;
	DWORD	bitEdc1CoreDiv			:7;
	DWORD	bitEdc1CoreValid		:1;
}st_SC_Cfg8Bit7;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of SysCtrl_reg */

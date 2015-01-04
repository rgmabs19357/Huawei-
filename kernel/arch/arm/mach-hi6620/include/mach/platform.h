#ifndef __MACH_K3V2_PLATFORM_H
#define __MACH_K3V2_PLATFORM_H

#ifndef __ASSEMBLY__
#include <asm/sizes.h>
#include <linux/mm.h>
#endif

#include "soc_baseaddr_interface.h"

#define REG_BASE_SRAM_OFF                   (SOC_SRAM_OFF_BASE_ADDR)
#define REG_SRAM_OFF_IOSIZE                 PAGE_ALIGN(SZ_256K)

#define REG_BASE_SRAM_ON                    (SOC_SRAM_ON_BASE_ADDR)
#define REG_SRAM_ON_IOSIZE                  PAGE_ALIGN(SZ_16K)

#define REG_BASE_SRAM_MDM                    (SOC_SRAM_MDM_BASE_ADDR)
#define REG_SRAM_MDM_IOSIZE                  (0x72000)

#define REG_BASE_SRAM_MCU                 (SOC_SRAM_M3_BASE_ADDR)
#define REG_SRAM_MCU_IOSIZE             PAGE_ALIGN(SZ_128K)

#define REG_BASE_DTCM_BBE16                 (SOC_Tensilica_BBE16_DTCM_BASE_ADDR)
#define REG_DTCM_BBE16_IOSIZE             	(0x50000)/*320K*/

#define REG_BASE_SC_OFF                     (SOC_SC_OFF_BASE_ADDR)
#define REG_SC_OFF_IOSIZE                   PAGE_ALIGN(SZ_8K)

#define REG_BASE_SC_ON                      (SOC_SC_ON_BASE_ADDR)
#define REG_SC_ON_IOSIZE                    PAGE_ALIGN(SZ_8K)

//todo l00215322
#define REG_BASE_PCTRL                      (SOC_SC_OFF_BASE_ADDR)
#define REG_PCTRL_IOSIZE                    PAGE_ALIGN(SZ_8K)

#define SOC_IOC_BASE_ADDR                   (SOC_IOC_OFF_BASE_ADDR)

#define REG_BASE_IOC_OFF                    (SOC_IOC_OFF_BASE_ADDR)
#define REG_IOC_OFF_IOSIZE                  PAGE_ALIGN(SZ_4K)

#define REG_BASE_IOC_ON                     (SOC_IOC_ON_BASE_ADDR)
#define REG_IOC_ON_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_RTC                        (SOC_RTC_BASE_ADDR)
#define REG_RTC_IOSIZE                      PAGE_ALIGN(SZ_4K)

#define REG_BASE_TIMER8                     (SOC_Timer8_BASE_ADDR)

#define REG_BASE_TIMER7                     (SOC_Timer7_BASE_ADDR)

#define REG_BASE_TIMER6                     (SOC_Timer6_BASE_ADDR)

#define REG_BASE_TIMER5                     (SOC_Timer5_BASE_ADDR)

#define REG_BASE_TIMER4                     (SOC_Timer4_BASE_ADDR)
#define REG_TIMER4_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_GPIO19                     (SOC_GPIO19_BASE_ADDR)

#define REG_BASE_GPIO18                     (SOC_GPIO18_BASE_ADDR)

#define REG_BASE_GPIO17                     (SOC_GPIO17_BASE_ADDR)

#define REG_BASE_GPIO16                     (SOC_GPIO16_BASE_ADDR)

#define REG_BASE_GPIO15                     (SOC_GPIO15_BASE_ADDR)

#define REG_BASE_GPIO14                     (SOC_GPIO14_BASE_ADDR)

#define REG_BASE_GPIO13                     (SOC_GPIO13_BASE_ADDR)

#define REG_BASE_GPIO12                     (SOC_GPIO12_BASE_ADDR)

#define REG_BASE_GPIO11                     (SOC_GPIO11_BASE_ADDR)

#define REG_BASE_GPIO10                     (SOC_GPIO10_BASE_ADDR)

#define REG_BASE_GPIO9                      (SOC_GPIO9_BASE_ADDR)

#define REG_BASE_GPIO8                      (SOC_GPIO8_BASE_ADDR)

#define REG_BASE_GPIO7                      (SOC_GPIO7_BASE_ADDR)

#define REG_BASE_GPIO6                      (SOC_GPIO6_BASE_ADDR)

#define REG_BASE_WD2                        (SOC_Watchdog2_BASE_ADDR)

#define REG_BASE_WD1                        (SOC_Watchdog1_BASE_ADDR)

#define REG_BASE_WD0                        (SOC_Watchdog0_BASE_ADDR)
#define REG_WD0_IOSIZE                      PAGE_ALIGN(SZ_4K)

#define REG_BASE_SCI1                       (SOC_SCI1_BASE_ADDR)

#define REG_BASE_SCI0                       (SOC_SCI0_BASE_ADDR)

#define REG_BASE_SSP1                       (SOC_SSP1_BASE_ADDR)

#define REG_BASE_SSP0                       (SOC_SSP0_BASE_ADDR)

#define REG_BASE_UART6                      (SOC_UART6_BASE_ADDR)

#define REG_BASE_UART5                      (SOC_UART5_BASE_ADDR)

#define REG_BASE_UART4                      (SOC_UART4_BASE_ADDR)

#define REG_BASE_UART3                      (SOC_UART3_BASE_ADDR)

#define REG_BASE_UART2                      (SOC_UART2_BASE_ADDR)

#define REG_BASE_UART1                      (SOC_UART1_BASE_ADDR)

#define REG_BASE_UART0                      (SOC_UART0_BASE_ADDR)

#define REG_BASE_TZPC                       (SOC_TZPC_BASE_ADDR)

#define REG_BASE_GPIO5                      (SOC_GPIO5_BASE_ADDR)

#define REG_BASE_GPIO4                      (SOC_GPIO4_BASE_ADDR)

#define REG_BASE_GPIO3                      (SOC_GPIO3_BASE_ADDR)

#define REG_BASE_GPIO2                      (SOC_GPIO2_BASE_ADDR)

#define REG_BASE_GPIO1                      (SOC_GPIO1_BASE_ADDR)

#define REG_BASE_GPIO0                      (SOC_GPIO0_BASE_ADDR)

#define REG_BASE_I2C5                       (SOC_I2C5_BASE_ADDR)
#define REG_I2C5_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_I2C4                       (SOC_I2C4_BASE_ADDR)
#define REG_I2C4_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_I2C3                       (SOC_I2C3_BASE_ADDR)
#define REG_I2C3_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_I2C2                       (SOC_I2C2_BASE_ADDR)
#define REG_I2C2_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_I2C1                       (SOC_I2C1_BASE_ADDR)
#define REG_I2C1_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_I2C0                       (SOC_I2C0_BASE_ADDR)
#define REG_I2C0_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_TIMER3                     (SOC_Timer3_BASE_ADDR)
#define REG_TIMER3_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_TIMER2                     (SOC_Timer2_BASE_ADDR)
#define REG_TIMER2_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_TIMER1                     (SOC_Timer1_BASE_ADDR)
#define REG_TIMER1_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_TIMER0                     (SOC_Timer0_BASE_ADDR)
#define REG_TIMER0_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_SLICE                      SOC_SC_ON_BASE_ADDR
#define REG_SLICE_IOSIZE                    PAGE_ALIGN(SZ_4K)
#define REG_BASE_SOCP                       (SOC_SOCP_BASE_ADDR)

#define REG_BASE_IPF                        (SOC_IPF_BASE_ADDR)
#define REG_IPF_IOSIZE                      PAGE_ALIGN(SZ_4K)

#define REG_BASE_SIO2                       (SOC_SIO2_BASE_ADDR)

#define REG_BASE_MMC2                       (SOC_SDIOMMC_BASE_ADDR)
#define REG_MMC2_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_MMC1                       (SOC_SDMMC_BASE_ADDR)
#define REG_MMC1_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_MMC0                       (SOC_eMMC_BASE_ADDR)
#define REG_MMC0_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_IPC                        (SOC_IPC_BASE_ADDR)

#define REG_BASE_USBOTG                     (SOC_USB2OTG_BASE_ADDR)
#define REG_USBOTG_IOSIZE                   PAGE_ALIGN(SZ_256K + SZ_16K)

#define REG_BASE_HSIC                       (SOC_HSIC_BASE_ADDR)

#define REG_BASE_UICC                       (SOC_UICC_BASE_ADDR)

#define REG_BASE_DDRC                       (SOC_DDRC_BASE_ADDR)

#define REG_BASE_DMAC                       (SOC_AP_DMAC_BASE_ADDR)
#define REG_DMAC_IOSIZE                     PAGE_ALIGN(SZ_4K)

#define REG_BASE_L2CC                       (SOC_L2CC_BASE_ADDR)
#define REG_L2CC_IOSIZE                     PAGE_ALIGN(SZ_1M)

#define REG_BASE_A9PRI                      (SOC_ACPU_A9_private_BASE_ADDR)
#define REG_A9PRI_IOSIZE                    PAGE_ALIGN(SZ_4M)

#define REG_BASE_CS_SYS_ROM_TABLE           (SOC_CS_SYS_ROM_TABLE_BASE_ADDR)

#define REG_BASE_ABBSSI                     (SOC_ABBSSI_BASE_ADDR)

#define REG_BASE_PMUSSI                     (SOC_PMUSSI_BASE_ADDR)
#define REG_PMUSSI_IOSIZE                   PAGE_ALIGN(SZ_4M)

//todo l00215322
#define REG_BASE_PMUSPI                     (SOC_PMUSSI_BASE_ADDR)
#define REG_PMUSPI_IOSIZE                   PAGE_ALIGN(SZ_4M)

#define REG_BASE_VENC                       (SOC_VENC_BASE_ADDR)
#define REG_VENC_IOSIZE                     PAGE_ALIGN(SZ_4K)
#define REG_BASE_VDEC                       (SOC_VDEC_BASE_ADDR)
#define REG_VDEC_IOSIZE                     PAGE_ALIGN(SZ_4K)
#define REG_BASE_PMCTRL                     (SOC_PMCTRL_BASE_ADDR)
#define REG_PMCTRL_IOSIZE                   PAGE_ALIGN(SZ_4K)

#define REG_BASE_SECENG                     (SOC_SECENG_BASE_ADDR)
#define REG_SECENG_IOSIZE                   PAGE_ALIGN(SZ_4K)
#define REG_BASE_DRAM                       (SOC_DRAM_BASE_ADDR)
#define REG_DRAM_IOSIZE                     PAGE_ALIGN(SZ_4M)

#define REG_BASE_EDC0                       (SOC_EDC0_BASE_ADDR)
#define REG_EDC0_IOSIZE                     PAGE_ALIGN(SZ_16K)
#define REG_BASE_EDC1                       (SOC_EDC1_BASE_ADDR)
#define REG_EDC1_IOSIZE                     PAGE_ALIGN(SZ_16K)
#define REG_BASE_PWM0                       (SOC_PWM0_BASE_ADDR)
#define REG_PWM0_IOSIZE                     PAGE_ALIGN(SZ_4K)
#define REG_BASE_PWM1                       (SOC_PWM1_BASE_ADDR)
#define REG_PWM1_IOSIZE                     PAGE_ALIGN(SZ_4K)
#define REG_BASE_DSI0                       (SOC_DSI_BASE_ADDR)
#define REG_DSI0_IOSIZE                     PAGE_ALIGN(SZ_4K)
#define REG_BASE_HDMI                       (SOC_HDMI_BASE_ADDR)
#define REG_BASE_ISP                        (SOC_ISP_BASE_ADDR)
#define REG_ISP_IOSIZE                      PAGE_ALIGN(SZ_512K)

#define REG_BASE_CSI                        (SOC_CSI_BASE_ADDR)
#define REG_CSI_IOSIZE                      PAGE_ALIGN(SZ_1K)
#define REG_BASE_G2D                        (SOC_G2D_BASE_ADDR)
#define REG_BASE_G3D                        (SOC_G3D_BASE_ADDR)
#define REG_BASE_VPP                        (SOC_VPP_BASE_ADDR)

/* 寄存器说明：临时分配为Hi6421 PMUSPI使用，最终更改为PMUSPI */
#define REG_BASE_PMUSPI_SFT                 (REG_BASE_SSP1)
#define REG_PMUSPI_SFT_IOSIZE               PAGE_ALIGN(SZ_4K)

#define REG_BASE_ASP                        (SOC_ASP_BASE_ADDR)
#define REG_ASP_IOSIZE                      PAGE_ALIGN(SZ_16K)

#define REG_BASE_ERROR_LOGGER_0             (0xffc00000)
#define REG_ERROR_LOGGER_0_IOSIZE           (SZ_128)

#define REG_BASE_ERROR_LOGGER_1             (0xffc10000)
#define REG_ERROR_LOGGER_1_IOSIZE           (SZ_128)

#define REG_BASE_IPC_NS                   (SOC_IPC_BASE_ADDR)
#define REG_IPC_NS_IOSIZE                 PAGE_ALIGN(SZ_4K)
#endif	/* __MACH_K3V2_PLATFORM_H */

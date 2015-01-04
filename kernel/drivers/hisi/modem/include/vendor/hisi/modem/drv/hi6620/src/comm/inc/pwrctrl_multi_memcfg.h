/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_multi_memcfg.h
  版 本 号   : 初稿
  生成日期   : 2012年12月18日
  最近修改   :
  功能描述   : pwrctrl_multi_def.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月18日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PWRCTRL_MULTI_MEMCFG_H__
#define __PWRCTRL_MULTI_MEMCFG_H__

#include "pwrctrl_multi_dfs_asm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include  "soc_baseaddr_interface.h"
#include  "global_ddr_map.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#ifndef __PWRCTRL_MULTI_MEMCFG_MCU__
#define __PWRCTRL_MULTI_MEMCFG_MCU__

/**************  SRAM  ***************/
#define     MCU_SRAM_START          (SOC_SRAM_M3_BASE_ADDR)
#define     MCU_SRAM_PD_START       (MCU_SRAM_START + 0x8000)

#define     MCU_SRAM_DATA_START       (MCU_SRAM_START + 0x1FC00) /* 127K - 128K: MCU Data memory.*/
#define     MCA_INST_DATA_MUTEX_ADDR  (MCU_SRAM_DATA_START)
#define     MCA_INST_DATA_ADDR        (MCU_SRAM_DATA_START + 4)
#define     PWC_FUNC_CFG_ADDR         (MCU_SRAM_DATA_START + 8)


/**************  DDR  ***************/
#define     MCU_DDR_START           (MCU_SYS_MEM_ADDR)
#define     MCU_DDR_REMAP_START     (0x20000)

#define     ADDR_P2V(addr)          ((addr - MCU_DDR_START) + MCU_DDR_REMAP_START)
#define     ADDR_V2P(addr)          ((addr - MCU_DDR_REMAP_START) + MCU_DDR_START)

#define     MCU_DDR_BK_SRAM         (MCU_DDR_START + 0x20000)  /*防止mcu代码溢出*/
#define     MCU_DDR_BK_SRAM_SIZE    (0x18000)       /*96k*/
#define     MCU_DDR_BK_SOC          (MCU_DDR_BK_SRAM + MCU_DDR_BK_SRAM_SIZE)
#define     MCU_DDR_BK_SOC_SIZE     (0x4000)        /*16k*/
#define     MCU_DDR_MNTN_ADDR       (MCU_DDR_BK_SOC + MCU_DDR_BK_SOC_SIZE)
#define     MCU_DDR_MNTN_ADDR_SIZE  (0x10000)        /* 共32K 需与lds同步修改 by c00220237 */
#define     MCU_DDR_BK_SOC_OFF_SRAM_ADDR  (MCU_DDR_MNTN_ADDR + MCU_DDR_MNTN_ADDR_SIZE)
#define     MCU_DDR_BK_SOC_OFF_SRAM_SIZE  (64*1024)

#define     MCU_DDR_BK_SOCP         (MCU_DDR_BK_SOC_OFF_SRAM_ADDR + MCU_DDR_BK_SOC_OFF_SRAM_SIZE)
#define     MCU_DDR_BK_SOCP_SIZE    (0x1000)        /*4k*/
/*mcu ddr Remap*/

#define     MCU_DDR_BK_NOR_V_ADDR   (ADDR_P2V(MCU_DDR_BK_SOC))
#define     MCU_DDR_BK_NOR_V_SIZE   (0x1800)
#define     MCU_DDR_BK_SPC_V_ADDR   (MCU_DDR_BK_NOR_V_ADDR + MCU_DDR_BK_NOR_V_SIZE)
#define     MCU_DDR_BK_SPC_V_SIZE   (0x400)
#define     MCU_DDR_BK_PMCTRL_ADDR  (MCU_DDR_BK_SPC_V_ADDR + MCU_DDR_BK_SPC_V_SIZE)
#define     MCU_DDR_BK_PMCTRL_SIZE  (0x400)
#define     MCU_DDR_BK_IPF_REG          (MCU_DDR_BK_PMCTRL_ADDR + MCU_DDR_BK_PMCTRL_SIZE)
#define     MCU_DDR_BK_IPF_REG_SIZE     (4 * 40)    /* 40个寄存器 */




#endif





/********************************************/
#ifndef __PWRCTRL_MULTI_MEMCFG_ACPU__
#define __PWRCTRL_MULTI_MEMCFG_ACPU__

/**************  SRAM  ***************/
/*A核 SRAM 地址*/
#define PWRCTRL_ACPU_ASM_SPACE_ADDR         (SOC_SRAM_ON_BASE_ADDR)

/*睡眠空间地址分配表*/
#define PWRCTRL_ACPU_ASM_MEM_BASE           (PWRCTRL_ACPU_ASM_SPACE_ADDR)   /*sum size: 24k*/
#define PWRCTRL_ACPU_ASM_MEM_SIZE           (0x4000)                        /*16k*/
#define PWRCTRL_ACPU_ASM_CODE_BASE          (PWRCTRL_ACPU_ASM_MEM_BASE + 0x400)
#define PWRCTRL_ACPU_ASM_DATA_BASE          (PWRCTRL_ACPU_ASM_MEM_BASE + 0x2000)
#define PWRCTRL_ACPU_ASM_DATA_SIZE          (0x2000)
/* 0x000-0x1ff core0*/
/* 0x200-0x3ff core1*/
/* 0x400-0x5ff core2*/
/* 0x600-0x7ff core3*/
/* 0x800-0xfff common*/
/********************************* phy addr ***********************************/
#define PWRCTRL_ACPU_ASM_D_C0_ADDR          (PWRCTRL_ACPU_ASM_DATA_BASE)
#define PWRCTRL_ACPU_ASM_D_C0_MMU_PARA_AD   (PWRCTRL_ACPU_ASM_DATA_BASE + 0)    /*size:0x20 - 8*4    :0x20*/
#define PWRCTRL_ACPU_ASM_D_ARM_PARA_AD      (PWRCTRL_ACPU_ASM_DATA_BASE + 0x20) /*size:0xe0 - 56*4   :0x100*/

#define PWRCTRL_ACPU_ASM_D_COMM_ADDR        (PWRCTRL_ACPU_ASM_DATA_BASE + 0x800)/*0x3800*/

/*----------A核低功耗标志区 start--------------*/
#define PWRCTRL_ACPU_REBOOT                 (PWRCTRL_ACPU_ASM_D_COMM_ADDR)                                          /*0x3800 size 0x200*/
#define PWRCTRL_ACPU_REBOOT_SIZE            (0x200)                                                                 /*for exc*/
#define PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR     (PWRCTRL_ACPU_REBOOT + PWRCTRL_ACPU_REBOOT_SIZE)                        /*0x3a00*/
#define PWRCTRL_ACPU_ASM_SLICE_BAK_SIZE     (4)
#define PWRCTRL_ACPU_ASM_DEBUG_FLAG_ADDR    (PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR + PWRCTRL_ACPU_ASM_SLICE_BAK_SIZE)     /*0x3a04*/
#define PWRCTRL_ACPU_ASM_DEBUG_FLAG_SIZE    (4)
#define EXCH_A_CORE_POWRCTRL_CONV_ADDR      (PWRCTRL_ACPU_ASM_DEBUG_FLAG_ADDR + PWRCTRL_ACPU_ASM_DEBUG_FLAG_SIZE)   /*0x3a08*/
#define EXCH_A_CORE_POWRCTRL_CONV_SIZE      (4)

/* CPU IDLE状态标志区 */
#define MEMORY_AXI_CPU_IDLE_ADDR            (EXCH_A_CORE_POWRCTRL_CONV_ADDR + EXCH_A_CORE_POWRCTRL_CONV_SIZE)
#define MEMORY_AXI_CPU_IDLE_SIZE            (4)

/* 当前频率值保存,避免频繁发消息获取 0-3字节:acpu 4-7字节:DDR 8-11字节:GPU*/
#define MEMORY_AXI_CUR_FREQ_ADDR            (MEMORY_AXI_CPU_IDLE_ADDR + MEMORY_AXI_CPU_IDLE_SIZE)
#define MEMORY_AXI_CUR_FREQ_SIZE            (12)

/*acpu freq vol*/
#define MEMORY_AXI_ACPU_FREQ_VOL_ADDR       (MEMORY_AXI_CUR_FREQ_ADDR + MEMORY_AXI_CUR_FREQ_SIZE)
#define MEMORY_AXI_ACPU_FREQ_VOL_SIZE	    (16 + 28)

/*ddr freq vol*/
#define MEMORY_AXI_DDR_FREQ_VOL_ADDR        (MEMORY_AXI_ACPU_FREQ_VOL_ADDR + MEMORY_AXI_ACPU_FREQ_VOL_SIZE)
#define MEMORY_AXI_DDR_FREQ_VOL_SIZE	    (16 + 28)

/*acpu core online info area. offset 0:core1 online. offset 4: core2 online. offset 8: core3 online*/
#define MEMORY_AXI_ACPU_FIQ_TEST_ADDR             (MEMORY_AXI_DDR_FREQ_VOL_ADDR + MEMORY_AXI_DDR_FREQ_VOL_SIZE)/*0x3a64*/
#define MEMORY_AXI_ACPU_FIQ_TEST_SIZE				(12)

/*acpu online & ready flag area.offset 0:acpu online sum&intr num. offset 0x4~0x10: core 0~3 ready flag. offset 0x14:dvfs complete flag*/
#define MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR             (MEMORY_AXI_ACPU_FIQ_TEST_ADDR + MEMORY_AXI_ACPU_FIQ_TEST_SIZE)/*0x3a70*/
#define MEMORY_AXI_ACPU_FIQ_CPU_INFO_SIZE				(24)

/*acpu dvfs debug info area.offset 0:mcu set value(0x6 or 0x10). offset 0x4~0x10:core0~core1 set value(mcu set value + 1)*/
#define MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_ADDR             (MEMORY_AXI_ACPU_FIQ_CPU_INFO_ADDR + MEMORY_AXI_ACPU_FIQ_CPU_INFO_SIZE)/*0x3a88*/
#define MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_SIZE				(20)

/*ddr dfs para,fastboot input;*/
#define MEMORY_AXI_DDR_DDL_ADDR             (MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_ADDR + MEMORY_AXI_ACPU_FIQ_DEBUG_INFO_SIZE)/*0x3a9C*/
#define MEMORY_AXI_DDR_DDL_SIZE				(0x190)

/**********z00241656 add for freqdump begin 请在MEMORY_FREQDUMP_ADDR后面开辟内存，谢谢***************/
#define MEMORY_FREQDUMP_ADDR                (MEMORY_AXI_DDR_DDL_ADDR + MEMORY_AXI_DDR_DDL_SIZE)
#define MEMORY_FREQDUMP_SIZE                (64)
/**********z00241656 add for freqdump end 请在MEMORY_FREQDUMP_ADDR后面开辟内存，谢谢******************/

/*for ccpu log addr;*/
#define MEMORY_AXI_CCPU_LOG_ADDR            (MEMORY_FREQDUMP_ADDR + MEMORY_FREQDUMP_SIZE)
#define MEMORY_AXI_CCPU_LOG_SIZE            (4)

/*for mcu log addr;*/
#define MEMORY_AXI_MCU_LOG_ADDR             (MEMORY_AXI_CCPU_LOG_ADDR + MEMORY_AXI_CCPU_LOG_SIZE)
#define MEMORY_AXI_MCU_LOG_SIZE             (4)

/*secondary core boot phy addr*/
#define MEMORY_AXI_SEC_CORE_BOOT_ADDR       (MEMORY_AXI_MCU_LOG_ADDR + MEMORY_AXI_MCU_LOG_SIZE)
#define MEMORY_AXI_SEC_CORE_BOOT_SIZE	    (4)

/*reserved*/
#define POLICY_AREA_RESERVED                      (MEMORY_AXI_SEC_CORE_BOOT_ADDR + MEMORY_AXI_SEC_CORE_BOOT_SIZE)
#define POLICY_AREA_RESERVED_SIZE             (12)

/*ddr policy param addr*/
#define DDR_POLICY_VALID_MAGIC                      (POLICY_AREA_RESERVED + POLICY_AREA_RESERVED_SIZE)
#define DDR_POLICY_VALID_MAGIC_SIZE             (4)

#define DDR_POLICY_MAX_NUM                      (DDR_POLICY_VALID_MAGIC + DDR_POLICY_VALID_MAGIC_SIZE)
#define DDR_POLICY_MAX_NUM_SIZE             (4)

#define DDR_POLICY_SUPPORT_NUM                      (DDR_POLICY_MAX_NUM + DDR_POLICY_MAX_NUM_SIZE)
#define DDR_POLICY_SUPPORT_NUM_SIZE             (4)

#define DDR_POLICY_CUR_POLICY                      (DDR_POLICY_SUPPORT_NUM + DDR_POLICY_SUPPORT_NUM_SIZE)
#define DDR_POLICY_CUR_POLICY_SIZE             (4)

#define DDR_POLICY_STROE_AREA                      (DDR_POLICY_CUR_POLICY + DDR_POLICY_CUR_POLICY_SIZE)
#define DDR_POLICY_STROE_AREA_SIZE             ((POLICY_LEN * MAX_PROFILE_NUM_DDR * SURPPORT_POLICY_NUM) + 0x8)

/*acpu policy param addr*/
#define ACPU_POLICY_VALID_MAGIC                      (DDR_POLICY_STROE_AREA + DDR_POLICY_STROE_AREA_SIZE)
#define ACPU_POLICY_VALID_MAGIC_SIZE             (4)

#define ACPU_POLICY_MAX_NUM                      (ACPU_POLICY_VALID_MAGIC + ACPU_POLICY_VALID_MAGIC_SIZE)
#define ACPU_POLICY_MAX_NUM_SIZE             (4)

#define ACPU_POLICY_SUPPORT_NUM                      (ACPU_POLICY_MAX_NUM + ACPU_POLICY_MAX_NUM_SIZE)
#define ACPU_POLICY_SUPPORT_NUM_SIZE             (4)

#define ACPU_POLICY_CUR_POLICY                      (ACPU_POLICY_SUPPORT_NUM + ACPU_POLICY_SUPPORT_NUM_SIZE)
#define ACPU_POLICY_CUR_POLICY_SIZE             (4)

#define ACPU_POLICY_STROE_AREA                      (ACPU_POLICY_CUR_POLICY + ACPU_POLICY_CUR_POLICY_SIZE)
#define ACPU_POLICY_STROE_AREA_SIZE             ((POLICY_LEN * MAX_PROFILE_NUM_CPU * SURPPORT_POLICY_NUM) + 0x8)
/*仅为产线工位判断hw_config和efuse中最高频率使用*/
#define ACPU_CHIP_MAX_FREQ                      (ACPU_POLICY_STROE_AREA + ACPU_POLICY_STROE_AREA_SIZE)
#define ACPU_CHIP_MAX_FREQ_SIZE                 (4)

#define ACPU_VIRTUAL_FREQ                       (ACPU_CHIP_MAX_FREQ+ACPU_CHIP_MAX_FREQ_SIZE)
#define ACPU_VIRTUAL_FREQ_SIZE                  (4)

#define MEMORY_AXI_CORE_BOOT_STAGE_ADDR       (ACPU_VIRTUAL_FREQ + ACPU_VIRTUAL_FREQ_SIZE)
#define MEMORY_AXI_CORE_BOOT_STAGE_SIZE	      (4)

/*新增分配，请在此之前分配，并修改MEMORY_AXI_USED_END_ADDR的地址*/
#define MEMORY_AXI_USED_END_ADDR             (MEMORY_AXI_CORE_BOOT_STAGE_ADDR + MEMORY_AXI_CORE_BOOT_STAGE_SIZE)
#define MEMORY_AXI_USED_END_SIZE	          (0)

#if ((MEMORY_AXI_USED_END_ADDR + MEMORY_AXI_USED_END_SIZE) >= (PWRCTRL_ACPU_ASM_SPACE_ADDR + PWRCTRL_ACPU_ASM_MEM_SIZE))
#error acpu_low_power_memory((ACPU_POLICY_STROE_AREA + ACPU_POLICY_STROE_AREA_SIZE)) used beyond (PWRCTRL_ACPU_ASM_MEM_SIZE)
#endif

#define MEMORY_AXI_RESERVED_ADDR            ((PWRCTRL_ACPU_ASM_DATA_BASE + PWRCTRL_ACPU_ASM_DATA_SIZE) -(MEMORY_AXI_SEC_CORE_BOOT_ADDR + MEMORY_AXI_SEC_CORE_BOOT_SIZE))



/*----------A核低功耗标志区 end--------------*/


/**************  DDR  ***************/







#endif


/********************************************/
#ifndef __PWRCTRL_MULTI_MEMCFG_CCPU__
#define __PWRCTRL_MULTI_MEMCFG_CCPU__








/**************  DDR  ***************/

/*睡眠空间地址分配表*/
#define PWRCTRL_ASM_MEM_SPACE_BASE      (0x1000)                        /*DDR 0x1000-0x3fff      -- Pw_platform*/
#define PWRCTRL_ASM_MEM_SPACE_SIZE      (0x3000)                        /*DDR 0x1000-0x3fff      -- Pw_platform*/

#define STORE_ADDR_ARM_REG              (PWRCTRL_ASM_MEM_SPACE_BASE)    /*40*4 = 160, 0xA0*/

#define PWRCTRL_ASM_DEBUG_FLAG          (PWRCTRL_ASM_MEM_SPACE_BASE + 0xA0)
#define PWRCTRL_ASM_SLICE_TIMER_ADDR    (PWRCTRL_ASM_MEM_SPACE_BASE + 0xA4)

#define STORE_ADDR_MMU_REG              (PWRCTRL_ASM_MEM_SPACE_BASE + 0xB0) /*0x10*3 = , 0xE0*/


#define EXCH_C_CORE_POWRCTRL_CONV_ADDR  (PWRCTRL_ASM_MEM_SPACE_BASE + 0xE0) /*, 0xE4*/


#define DDR_TRAINNING_ADDR_REV_SIZE     (0x400)
#define DDR_TRAINNING_ADDR_REV          ((PWRCTRL_ASM_MEM_SPACE_BASE + PWRCTRL_ASM_MEM_SPACE_SIZE) - DDR_TRAINNING_ADDR_REV_SIZE)
#endif
















/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_multi_memcfg.h */

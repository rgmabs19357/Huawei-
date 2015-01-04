/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : MemoryMap.h
  版 本 号   : 初稿
  生成日期   : 2010年06月25日
  最近修改   :
  功能描述   : Sytem Memory Map
  函数列表   :
  修改历史   :
  1.日    期   : 2010年06月25日
    修改内容   : 创建文件

******************************************************************************/
#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "MemoryLayout.h"

/* GU PS预留内存物理地址、虚拟地址转定义 */
#define ECS_MDDR_RESERVE_BASE_ADDR          (GLOBAL_MEM_GU_RESERVED_ADDR)
#define ECS_MDDR_RESERVE_BASE_ADDR_VIRT     (GU_RESERVED_MEM_VIRT_ADDR) /*平台统一分配的虚拟基地址*/

#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
/*IPF Register*/
#define IPF_PHY_BASE_ADDR                   (SOC_IPF_BASE_ADDR)
#else
/*IPF Register*/
#define IPF_PHY_BASE_ADDR                   (SOC_IPF_BASE_ADDR)
#endif

/*AXI Memory Base*/
#define AXI_PHY_BASE_ADDR                   (GLOBAL_AXI_MEM_BASE_ADDR)

/*TTF DICC Spinlock Memory*/
#define ECS_TTF_DICC_SPINLOCK_ADDR          (MEMORY_AXI_DICC_ADDR - GLOBAL_AXI_MEM_BASE_ADDR + AXI_PHY_BASE_ADDR)
#define ECS_TTF_ACPU_FREE_MEM_CNT_ADDR      (ECS_TTF_DICC_SPINLOCK_ADDR + 4)

/* 核间共享内存 */
#define PBXA9_DRAM_SHARE_PHYS               (GLOBAL_MEM_CORE_SHARE_ADDR)
#define PBXA9_DRAM_SHARE_SIZE               (GLOBAL_MEM_CORE_SHARE_SIZE)
#define PBXA9_DRAM_SHARE_VIRT               (IPC_SHARE_MEM_VIRT_ADDR)/*VIRT_ADDRESS(GLOBAL_MEM_CORE_SHARE_ADDR)
 */

/* 异常记录内存 */
#define ECS_EXCP_BASE_ADDR                  (GLOBAL_MEM_EXCP_BASE_ADDR)
#define ECS_EXCP_SIZE                       (GLOBAL_MEM_EXCP_SIZE)


/*                       GU PS预留内存

               +---------------------+-------+ --> 0x33100000
               |   TTF预留内存       |9M+704K|
               +---------------------+-------+ --> 0x33AB0000
               |   ARM/DSP内存       |2M+640K|
               +---------------------+-------+ --> 0x33D50000
               |    UPA              | 128K  |
               +---------------------+-------+ --> 0x33D70000
               |    CQI              | 13K   |
               +---------------------+-------+ --> 0x33D73400
               |    APT              | 33K   |
               +---------------------+-------+ --> 0x33D7B800
               |    ET(尚未使用)     | 18K   |
               +---------------------+-------+ --> 0x33D80000
               |   BSP_Master        | 0K    |
               +---------------------+-------+ --> 0x33D80000
               |   NV共享区          | 192K  |
               +---------------------+-------+ --> 0x33DB0000
               |   TTF DICC          | 64K   |
               +---------------------+-------+ --> 0x33DC0000
               |   未使用            | 352K  |
               +---------------------+-------+ --> 0x33E18000
*/

#define ECS_TTF_SIZE                        (0x00A00000)
#define HUTAF_HLT_MEM_SIZE                  (0x00200000)/*HUTAF使用2M*/
#define ECS_TTF_SAVE_SIZE                   (0x00000000)/*TTF裁掉,备用*/
#define ECS_ARM_DSP_BUFFER_SIZE             (0x00300000)
#define ECS_UPA_SIZE                        (0x00024000)
#define ECS_CQI_SIZE                        (0x00003400)
#define ECS_APT_SIZE                        (0x00002C00)
#define ECS_ET_SIZE                         (0x00001000)
#define ECS_BBP_MASTER_SIZE                 (0x00000000)
#define ZSP_UP_SIZE                         (0x00008000)/*monan for v9r1bbit*/
#define ECS_NV_SIZE                         (0x000B0000)
#define ECS_TTF_DICC_SIZE                   (0x00000000)
#define ECS_HARQ_SIZE                       (0x00000000)
#define ECS_GUDSP_LOAD_SIZE                 (0x000BD000)
#define ECS_ETB_SIZE                        (0x00020000)
#define ECS_MDDR_RESERVE_SIZE               (ECS_TTF_SIZE + ECS_ARM_DSP_BUFFER_SIZE + ECS_UPA_SIZE \
                                             + ECS_CQI_SIZE + ECS_APT_SIZE + ECS_ET_SIZE + ECS_BBP_MASTER_SIZE \
                                             + ECS_NV_SIZE + ECS_TTF_DICC_SIZE + ZSP_UP_SIZE  + HUTAF_HLT_MEM_SIZE + ECS_TTF_SAVE_SIZE \
                                             + ECS_HARQ_SIZE + ECS_GUDSP_LOAD_SIZE + ECS_ETB_SIZE)

#define ECS_TTF_BASE_ADDR                   (ECS_MDDR_RESERVE_BASE_ADDR)
#define HUTAF_HLT_MEM_ADDR                  (ECS_TTF_BASE_ADDR            + ECS_TTF_SIZE)
#define ECS_TTF_SAVE_ADDR                   (HUTAF_HLT_MEM_ADDR           + HUTAF_HLT_MEM_SIZE)
#define ECS_ARM_DSP_BUFFER_BASE_ADDR        (ECS_TTF_SAVE_ADDR            + ECS_TTF_SAVE_SIZE)
#define ECS_UPA_BASE_ADDR                   (ECS_ARM_DSP_BUFFER_BASE_ADDR + ECS_ARM_DSP_BUFFER_SIZE)
#define ECS_CQI_BASE_ADDR                   (ECS_UPA_BASE_ADDR            + ECS_UPA_SIZE)
#define ECS_APT_BASE_ADDR                   (ECS_CQI_BASE_ADDR            + ECS_CQI_SIZE)
#define ECS_ET_BASE_ADDR                    (ECS_APT_BASE_ADDR            + ECS_APT_SIZE)
#define ECS_BBP_MASTER_BASE_ADDR            (ECS_ET_BASE_ADDR             + ECS_ET_SIZE)
#define ZSP_UP_ADDR                         (ECS_BBP_MASTER_BASE_ADDR     + ECS_BBP_MASTER_SIZE)/*monan for v9r1bbit*/
#define ECS_NV_BASE_ADDR                    (ZSP_UP_ADDR                  + ZSP_UP_SIZE)
#define ECS_TTF_DICC_ADDR                   (ECS_NV_BASE_ADDR             + ECS_NV_SIZE)
#define ECS_HARQ_ADDR                       (ECS_TTF_DICC_ADDR            + ECS_TTF_DICC_SIZE)
#define ECS_GUDSP_LOAD_ADDR                 (ECS_HARQ_ADDR                + ECS_HARQ_SIZE)
#define ECS_ETB_ADDR                        (ECS_GUDSP_LOAD_ADDR          + ECS_GUDSP_LOAD_SIZE)

/* 异常记录内存虚地址 */
#define GLOBAL_MEM_EXCP_BASE_ADDR_VIRT      (ECS_EXCP_BASE_ADDR - ECS_MDDR_RESERVE_BASE_ADDR + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*核间共享内存虚地址*/
#define GLOBAL_MEM_CORE_SHARE_ADDR_VIRT     (IPC_SHARE_MEM_VIRT_ADDR)

/*TTF Memory Virtual Address*/
#define ECS_TTF_BASE_ADDR_VIRT              (ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*HUTAF Virtual Address*/
#define HUTAF_HLT_MEM_ADDR_VIRT             (HUTAF_HLT_MEM_ADDR - ECS_MDDR_RESERVE_BASE_ADDR + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*NV Virtual Address*/
#define ECS_NV_BASE_ADDR_VIRT               (ECS_NV_BASE_ADDR - ECS_MDDR_RESERVE_BASE_ADDR + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

/*DICC Virtual Address*/
#define ECS_TTF_DICC_ADDR_VIRT              (ECS_TTF_DICC_ADDR - ECS_MDDR_RESERVE_BASE_ADDR + ECS_MDDR_RESERVE_BASE_ADDR_VIRT)

#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
/*IPF Register Virtual Address*/
#define IPF_BASE_ADDR_VIRT                  (SOC_IPF_BASE_ADDR)           /*虚实地址统一  IO_ADDRESS(IPF_PHY_BASE_ADDR)
 */

/*AXI Memory Virtual Address*/
#define AXI_BASE_ADDR_VIRT                  (GLOBAL_AXI_MEM_BASE_ADDR)   /*虚实地址统一  IO_ADDRESS(AXI_PHY_BASE_ADDR)
 */
#else
/*IPF Register Virtual Address*/
#define IPF_BASE_ADDR_VIRT                  IO_ADDRESS(SOC_IPF_BASE_ADDR)

/*AXI Memory Virtual Address*/
#define AXI_BASE_ADDR_VIRT                  IO_ADDRESS(GLOBAL_AXI_MEM_BASE_ADDR)
#endif

/*Memory size check*/
#if (ECS_MDDR_RESERVE_SIZE > GLOBAL_MEM_GU_RESERVED_SIZE)
#error GU PS used size (ECS_MDDR_RESERVE_SIZE) beyond the reserve size (GLOBAL_MEM_GU_RESERVED_SIZE)
#endif

/* 给L模预留的内存 */
#define GLOBAL_LNV_BASE_ADDR            (GLOBAL_MEM_LPS_RESERVED_ADDR)
#define GLOBAL_LNV_BASE_SIZE            (0x00080000)

#define GLOBAL_MEM_LCS_ADDR             (GLOBAL_LNV_BASE_ADDR + GLOBAL_LNV_BASE_SIZE)
#define GLOBAL_MEM_LCS_SIZE             (0x00280000)

#define GLOBAL_MEM_SOCP_ADDR            (GLOBAL_MEM_LCS_ADDR + GLOBAL_MEM_LCS_SIZE)
#define GLOBAL_MEM_SOCP_SIZE            (0x00200000)

#define GLOBAL_MEM_MCORE_ACP_ADDR       (GLOBAL_MEM_SOCP_ADDR + GLOBAL_MEM_SOCP_SIZE)
#define GLOBAL_MEM_MCORE_ACP_SIZE       (0)

/* when T/L DSP changed,please check the vendor\hisi\build\scripts\gen_img_vrl_tbl.py */
#define GLOBAL_MEM_TDS_TABLE_ADDR       (GLOBAL_MEM_MCORE_ACP_ADDR + GLOBAL_MEM_MCORE_ACP_SIZE)
#define GLOBAL_MEM_TDS_TABLE_SIZE       (0x00080000) /* 512KByte for TDS Table Load */

/*BBE16加载DDR内存 2M*/
#define GLOBAL_MEM_LT_IMAGE_ADDR     (GLOBAL_MEM_TDS_TABLE_ADDR + GLOBAL_MEM_TDS_TABLE_SIZE)
#define GLOBAL_MEM_LT_IMAGE_SIZE     (0x200000)
/*-------------------------------------------------------------------------------
                            T/L DSP镜像内存分布配置
  -------------------------------------------------------------------------------
                    MULTI IMG
               -----------------------
          /   |  img head             |
          |   |  2+2+2+2+2+2          |                TDS TABLE DATA
          |   |  pub dtcm             |              --------------------
          |    -----------------------              |                    |
          |   |  pub itcm             |             |                    |
          |    -----------------------              |      预留给DSP     |->256k
          |   |  lte dtcm             |             |                    |
     2M  /     -----------------------              |                    |
         \    |  lte itcm             |              --------------------
          |    -----------------------              |                    |
          |   |  tds dtcm             |             |                    |
          |    -----------------------              |       TDS TBL      |->256k
          |   |  tds itcm             |             |                    |
          |    -----------------------              |                    |
          |   |                       |              --------------------
          |   |  保留                 |
          \   |                       |
               -----------------------

-------------------------------------------------------------------------------*/
#define BBE16_TDS_TABLE_DDR_ADDR        (GLOBAL_MEM_TDS_TABLE_ADDR + 0x40000)               /*tds cfg data*/
#define BBE16_TDS_TABLE_SIZE            (0x40000)                                           /*256k*/

#define BBE16_MULTI_TCM_DDR_ADDR        (GLOBAL_MEM_LT_IMAGE_ADDR)
#define BBE16_MULTI_TCM_SIZE            (GLOBAL_MEM_LT_IMAGE_SIZE)

#define BBE16_PUB_DTCM_INFO_ADDR        (BBE16_MULTI_TCM_DDR_ADDR)
#define BBE16_PUB_DTCM_INFO_SIZE        (2)
#define BBE16_PUB_ITCM_INFO_ADDR        (BBE16_PUB_DTCM_INFO_ADDR + BBE16_PUB_DTCM_INFO_SIZE)
#define BBE16_PUB_ITCM_INFO_SIZE        (2)
#define BBE16_LTE_DTCM_INFO_ADDR        (BBE16_PUB_ITCM_INFO_ADDR + BBE16_PUB_ITCM_INFO_SIZE)
#define BBE16_LTE_DTCM_INFO_SIZE        (2)
#define BBE16_LTE_ITCM_INFO_ADDR        (BBE16_LTE_DTCM_INFO_ADDR + BBE16_LTE_DTCM_INFO_SIZE)
#define BBE16_LTE_ITCM_INFO_SIZE        (2)
#define BBE16_TDS_DTCM_INFO_ADDR        (BBE16_LTE_ITCM_INFO_ADDR + BBE16_LTE_ITCM_INFO_SIZE)
#define BBE16_TDS_DTCM_INFO_SIZE        (2)
#define BBE16_TDS_ITCM_INFO_ADDR        (BBE16_TDS_DTCM_INFO_ADDR + BBE16_TDS_DTCM_INFO_SIZE)
#define BBE16_TDS_ITCM_INFO_SIZE        (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* MEMORY_MAP_H */


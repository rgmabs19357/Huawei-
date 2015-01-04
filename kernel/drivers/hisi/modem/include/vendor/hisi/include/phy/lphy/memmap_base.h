

/************************************************************
                     包含其它模块的头文件
************************************************************/
/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

#ifndef __MEM_MAP_BASE_H__
#define __MEM_MAP_BASE_H__

#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#if (defined(MS_VC6_PLATFORM))

    #define MASTER_TCM_ADDR_OFFSET  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET   MASTER_TCM_ADDR_OFFSET
    /*邮箱数组定义*/
    extern UINT32  gulArrMailxBox[];       /*400k字节大小*/
    /*HARQ缓冲区数组大小*/
    extern UINT32  gulArrHarqBuf[];        /*400k字节大小*/

    /*模拟邮箱*/
    #define LPHY_SHARE_MEM_BASE_ADDR                ((UINT32)&gulArrMailxBox[0])
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)

    /*模拟HARQ缓冲区*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           ((UINT32)&gulArrHarqBuf[0])

/* 基地址定义*/
#elif defined(BOARD_FPGA)

    #define MASTER_TCM_ADDR_OFFSET  (0x0 - 0xf000000)
    #define SLAVE_TCM_ADDR_OFFSET   (0x0 - 0xd000000)
    /*邮箱共享基地定义*/
    #define LPHY_SHARE_MEM_BASE_ADDR                (0xE0FC0000UL)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x0F000000UL)

    /*HARQ缓冲区基地址定义*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x52680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0x5270E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0x5270E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0x5270E018UL)

    /*加载地址，供BSP用*/
    #define LPHY_CORE0_BINARY_LOAD_ADDR             (0xE0FC0000UL) /*P500 bbe16 core0*/
    #define LPHY_CORE1_BINARY_LOAD_ADDR             (0xE2FC0000UL) /*P500 bbe16 core1*/

    /*映射地址，供vxworks 映射使用*/
    #define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_BINARY_LOAD_ADDR)
    #define LPHY_CORE_TCM_MAP_SIZE                  (256*1024 + 256*1024) /*256K + 256K*/

#elif defined(TL_PHY_FPGA_P531)

	#define MASTER_TCM_ADDR_OFFSET  				(0x01000000)
	#define SLAVE_TCM_ADDR_OFFSET   				(0x02000000)

	/*邮箱共享基地定义*/
	#define LPHY_SHARE_MEM_BASE_ADDR                (0x49f80000UL)
	#define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0xFF000000UL)

	/*HARQ缓冲区基地址定义*/
	#define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x20680000UL)
	#define LPHY_LMAC_TIMER_LOCK_ADDR               (0x2070E094UL)
	#define LPHY_LMAC_FRAME_ADDR                    (0x2070E014UL)
	#define LPHY_LMAC_SUB_FRAME_ADDR                (0x2070E018UL)

	/*加载地址，供BSP用*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           (0x49f80000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           (0x49f80000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (0x0003f000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR           (0x49fbf000UL) /*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/

	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR           (0x4a000000UL) /*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           (0x4afff000UL) /*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (0x00041000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           (0x4a040000UL) /*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/


	/*映射地址，供vxworks 映射使用*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (512*1024 + 512*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930ES
	#define LPHY_RFIC_HI6361
#elif (defined(BOARD_ASIC) || defined(BOARD_ASIC_BIGPACK) ||defined(BOARD_SFT))

    #define MASTER_TCM_ADDR_OFFSET  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET   MASTER_TCM_ADDR_OFFSET
    /*邮箱共享基地定义*/
    //#if defined(CHIP_BB_6920ES)
    //    #define LPHY_SHARE_MEM_BASE_ADDR                (0x27FC0000UL) /*256K*/
    //#else
    //    #define LPHY_SHARE_MEM_BASE_ADDR                (0x27FB0000UL) /*64K+256K*/
    //#endif

    //V9R1_ASIC start
    #define LPHY_SHARE_MEM_BASE_ADDR                (0xFA880000UL) /*tensilica dtcm地址 */
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)

    /*HARQ缓冲区基地址定义*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0xFD680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0xFD70E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0xFD70E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0xFD70E018UL)
	//V9R1_ASIC end

    /*加载地址，供BSP用*/
    #define LPHY_CORE0_BINARY_LOAD_ADDR             (0xFA800000UL) /*tensilica加载地址，itcm地址*/

    /*映射地址，供vxworks 映射使用*/
    #define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_BINARY_LOAD_ADDR)
    #define LPHY_CORE_TCM_MAP_SIZE                  (64*1024 + 256*1024 + 256*1024 + 128*1024) /*64K + 256K + 256K + 128K*/

#else

    #error "sorry, this is not a supported board version, please include product_config.h"

#endif

/*HARQ缓冲区地址*/
#if defined(CHIP_BB_6920ES)     /*HI6920ES*/
    #define LPHY_LMAC_HARQ_BUFF_ADDR_BY_HARQID(ucHarqId) (LPHY_LMAC_HARQ_BUFF_BASE_ADDR + (ucHarqId*0x2000))
#elif defined(CHIP_BB_6620CS) /*HI6620CS*/
    #define LPHY_LMAC_HARQ_BUFF_ADDR_BY_HARQID(ucHarqId) (LPHY_LMAC_HARQ_BUFF_BASE_ADDR + (ucHarqId*0x2000))
#elif defined(CHIP_BB_6920CS) /*HI6920CS*/
    #define LPHY_LMAC_HARQ_BUFF_ADDR_BY_HARQID(ucHarqId) (LPHY_LMAC_HARQ_BUFF_BASE_ADDR + (ucHarqId*0x4000))
#else
    #error "sorry, this is not a supported baseband version, please include product_config.h"
#endif


/* 共享邮箱大小定义*/
#define LPHY_MAILBOX_SHARE_MEM_SIZE                 (0x00000400UL)  /*1k字节，TBD*/
#define LPHY_MAILBOX_HDLC_BUF_SIZE                  (0x00001800UL)  /*6K字节, TBD*/
#define LPHY_MAILBOX_LHPA_UP_SIZE                   (0x00001000UL)  /*4K字节，PS上行邮箱大小*/
#define LPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00001800UL)  /*6k字节，PS下行邮箱大小*/
#define LPHY_MAILBOX_OM_UP_SIZE                     (0x00000000UL)  /*0k字节，OM上行邮箱大小*/
#define LPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k字节，OM下行邮箱大小*/
#define LPHY_MAILBOX_LMAC_UP_SIZE                   (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
#define LPHY_MAILBOX_LMAC_DOWN_SIZE                 (0x00000400UL)  /*1k字节，MAC专用邮箱大小*/
#define LPHY_MAILBOX_CT_UP_SIZE                     (0x00000000UL)  /*0k字节，CT上行邮箱大小*/
#define LPHY_MAILBOX_LPP_DOWN_SIZE                  (0x00000000UL)  /*0k字节，LPP 定位辅助信息邮箱大小*/
#define LPHY_MAILBOX_TOA_SIZE                       (0x00000000UL)  /*0k字节，TOA邮箱大小*/
#define LPHY_NV_CFG_SIZE                            (0x00002000UL)  /*8k字节，NV项配置区大小*/
#define TPHY_NV_CFG_SIZE                            (0x00002000UL)  /*8k字节，NV项配置区大小*/
#define LPHY_CSU_SDR_BUF_SIZE                       (0x00002800UL)  /*10k字节,CSU SDR数据区大小*/
#define TPHY_COMM_DATA_BUF_SIZE                     (0x00008000UL)  /*32k字节，TDS COMM BUF数据区大小*/
#define LPHY_RSVD_DATA_BUF_SIZE                     (0x00000400UL)  /*1k字节，TDS COMM BUF数据区大小*/

#if (defined(CHIP_BB_6920ES) || defined(BOARD_FPGA))
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE         (0x00000000UL)  /*LPHY_HI6920ES或者 fpga不保留这块内存*/
#else
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE         (0x00000000UL)  /*24K字节, 用于  pliot版本lcs计算使用*/
#endif


/*邮箱总大小*/
#define LPHY_TOTAL_RESERVED_MEM_SIZE    ( \
      LPHY_MAILBOX_SHARE_MEM_SIZE \
    + LPHY_MAILBOX_LCS_BANKA_MEM_SIZE \
    + LPHY_MAILBOX_HDLC_BUF_SIZE \
    + LPHY_MAILBOX_LHPA_UP_SIZE   \
    + LPHY_MAILBOX_LHPA_DOWN_SIZE \
    + LPHY_MAILBOX_OM_UP_SIZE    \
    + LPHY_MAILBOX_OM_DOWN_SIZE  \
    + LPHY_MAILBOX_LMAC_UP_SIZE  \
    + LPHY_MAILBOX_LMAC_DOWN_SIZE \
    + LPHY_MAILBOX_CT_UP_SIZE \
    + LPHY_MAILBOX_LPP_DOWN_SIZE \
    + LPHY_MAILBOX_TOA_SIZE \
    + LPHY_NV_CFG_SIZE\
    + TPHY_NV_CFG_SIZE\
    + LPHY_CSU_SDR_BUF_SIZE\
    + TPHY_COMM_DATA_BUF_SIZE\
    + LPHY_RSVD_DATA_BUF_SIZE)

/*邮箱基地址定义*/
#if (defined(TENSILICA_PLATFORM) || defined(MS_VC6_PLATFORM))
    #define LPHY_MAILBOX_BASE_ADDR                  (LPHY_SHARE_MEM_BASE_ADDR + LPHY_DSP_ARM_RAM_BASE_OFFSET)
#else
    #define LPHY_MAILBOX_BASE_ADDR                  (LPHY_SHARE_MEM_BASE_ADDR)
#endif

/*外部系统访问各个邮箱基地址*/
#define LPHY_MAILBOX_VERSION_ADDR                   (LPHY_MAILBOX_BASE_ADDR + 0x0200)   /*DSP版本查询地址*/
#define LPHY_MAILBOX_LOAD_MEMORY_ADDR               (LPHY_MAILBOX_BASE_ADDR + 0x020C)   /*开机初始化握手地址*/
#define LPHY_MAILBOX_RFIC_AD9361_VERSIOM_ADDR       (LPHY_MAILBOX_BASE_ADDR + 0x0210)   /*AD9361射频芯片版本查询地址*/
#define LPHY_MAILBOX_IPCM_MUTEX_DSP_SEND            (LPHY_MAILBOX_BASE_ADDR + 0x0324)   /*P500和A9IPC通讯互斥量地址*/
#define LPHY_MAILBOX_IPCM_MUTEX_DSP_RECEIVE         (LPHY_MAILBOX_BASE_ADDR + 0x0328)   /*P500和A9IPC通讯互斥量地址*/
#define LPHY_MAILBOX_SLAVE_AWAKE_ADDR               (LPHY_MAILBOX_BASE_ADDR + 0x032C)   /*从模PS IPCM任务状态地址*/
#define LPHY_MAILBOX_SLAVE_AWAKEMSP_ADDR            (LPHY_MAILBOX_BASE_ADDR + 0x0330)   /*从模MSP IPCM任务状态地址*/

#define LPHY_MAILBOX_HDLC_BUF_BASE_ADDR             (LPHY_MAILBOX_BASE_ADDR             + LPHY_MAILBOX_SHARE_MEM_SIZE)
#define LPHY_MAILBOX_LCS_BANKA_BASE_ADDR            (LPHY_MAILBOX_HDLC_BUF_BASE_ADDR    + LPHY_MAILBOX_HDLC_BUF_SIZE)
#define LPHY_MAILBOX_LHPA_UP_BASE_ADDR              (LPHY_MAILBOX_LCS_BANKA_BASE_ADDR   + LPHY_MAILBOX_LCS_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (LPHY_MAILBOX_LHPA_UP_BASE_ADDR     + LPHY_MAILBOX_LHPA_UP_SIZE)
#define LPHY_MAILBOX_OM_UP_BASE_ADDR                (LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR   + LPHY_MAILBOX_LHPA_DOWN_SIZE)
#define LPHY_MAILBOX_OM_DOWN_BASE_ADDR              (LPHY_MAILBOX_OM_UP_BASE_ADDR       + LPHY_MAILBOX_OM_UP_SIZE)
#define LPHY_MAILBOX_LMAC_UP_BASE_ADDR              (LPHY_MAILBOX_OM_DOWN_BASE_ADDR     + LPHY_MAILBOX_OM_DOWN_SIZE)
#define LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR            (LPHY_MAILBOX_LMAC_UP_BASE_ADDR     + LPHY_MAILBOX_LMAC_UP_SIZE)
#define LPHY_MAILBOX_CT_UP_MAIL_BASE_ADDR           (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR   + LPHY_MAILBOX_LMAC_DOWN_SIZE)
#define LPHY_MAILBOX_LPP_DOWN_BASE_ADDR             (LPHY_MAILBOX_CT_UP_MAIL_BASE_ADDR  + LPHY_MAILBOX_CT_UP_SIZE)
#define LPHY_MAILBOX_TOA_BASE_ADDR                  (LPHY_MAILBOX_LPP_DOWN_BASE_ADDR    + LPHY_MAILBOX_LPP_DOWN_SIZE)
#define LPHY_MAILBOX_NV_CFG_BASE_ADDR               (LPHY_MAILBOX_TOA_BASE_ADDR         + LPHY_MAILBOX_TOA_SIZE)
#define TPHY_MAILBOX_NV_CFG_BASE_ADDR               (LPHY_MAILBOX_NV_CFG_BASE_ADDR      + LPHY_NV_CFG_SIZE)
#define LPHY_CSU_SDR_BUF_ADDR                       (TPHY_MAILBOX_NV_CFG_BASE_ADDR      + TPHY_NV_CFG_SIZE) 
#define TPHY_COMM_DATA_BUF_ADDR                     (LPHY_CSU_SDR_BUF_ADDR              + LPHY_CSU_SDR_BUF_SIZE)
#define LPHY_RSVD_DATA_BUF_ADDR                     (TPHY_COMM_DATA_BUF_ADDR            + TPHY_COMM_DATA_BUF_SIZE)  /*1k字节，TDS COMM BUF数据区大小*/


/* CSU使用LCS内存  V9R1_CSU */
#define GLOBAL_MEM_CSU_SDR_DDR_BASE		        (GLOBAL_MEM_LCS_ADDR)
#define GLOBAL_MEM_CSU_SDR_DDR_END		        (GLOBAL_MEM_LCS_ADDR+GLOBAL_MEM_LCS_SIZE)
/* CSU使用LCS内存  V9R1_CSU end */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __MEM_MAP_BASE_H__ */

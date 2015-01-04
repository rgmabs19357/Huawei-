#ifndef _HI_GLOBAL_SRAM_MAP_INCLUDE_H_
#define _HI_GLOBAL_SRAM_MAP_INCLUDE_H_


#include "soc_baseaddr_interface.h"

/*******************************************
多核共享头文件
不允许包含操作系统相关头文件
*******************************************/

#define SRAM_BASE_ADDR				(SOC_SRAM_OFF_BASE_ADDR)

/*共256KB，分成两部分*/
#define SRAM_SIZE					(0x40000)

/*第一部分:64KB*/
#define SRAM_SECTION1_SIZE			(0x10000)

/*第二部分:192KB*/
#define SRAM_SECTION2_SIZE			(0x30000)

/*-------------------------------------------------------------------------------
                            SRAM划分(分时复用)
  -------------------------------------------------------------------------------
  onchiprom/fastboot启动阶段:
                          -----------------------
                         |  fastboot1的VRL       |->2KB
                          -----------------------
                         |  fastboot1镜像数据	 |----
                          -----------------------     |->58KB
                         |  onchiprom的栈        |----
                          -----------------------
                         |  软件标志区           |->4KB
                          -----------------------
                         |  安全OS               |->192KB
                          -----------------------
  linux/vxworks阶段:
                          -----------------------
                         |  IPF				     |->30KB
                          -----------------------
                         |  保留区域	 		 |->30KB
                          -----------------------
                         |  软件标志区           |->4KB
                          -----------------------
                         |  安全OS               |->192KB
                          -----------------------
                         
-------------------------------------------------------------------------------*/

/*ipf use section 30K*/
#define IPF_SRAM_ADDR				(SRAM_BASE_ADDR)
#define IPF_SRAM_SIZE				(0x000007800)

/*提供给BBE16用于TL模DRX流程中备份信息，CCPU会访问，地址为绝对地址，故放最前面*/
#define SRAM_RTT_SLEEP_FLAG_ADDR    (IPF_SRAM_ADDR + IPF_SRAM_SIZE)    /*0xFFF07800,若有改动需要通知T/L DSP*/
#define SRAM_RTT_SLEEP_FLAG_SIZE    (32)

/*保存LDSP睡眠唤醒标志*/
#define MEMORY_AXI_LDSP_AWAKE_ADDR  (SRAM_RTT_SLEEP_FLAG_ADDR + SRAM_RTT_SLEEP_FLAG_SIZE)
#define MEMORY_AXI_LDSP_AWAKE_SIZE  (4)

/*****************以上保持绝对路径，勿动*********************/
/*reserved 30K*/
#define RESERVED_SRAM_ADDR		    (MEMORY_AXI_LDSP_AWAKE_ADDR + MEMORY_AXI_LDSP_AWAKE_SIZE)
#define RESERVED_SRAM_SIZE			(0x000007800 - SRAM_RTT_SLEEP_FLAG_SIZE - MEMORY_AXI_LDSP_AWAKE_SIZE)

/*general use section 4K*/
#define GENERAL_SRAM_ADDR			(RESERVED_SRAM_ADDR + RESERVED_SRAM_SIZE)
#define GENERAL_SRAM_SIZE			(0x000001000)

/*teeos use section 192K*/
#define TEEOS_SRAM_ADDR			    (SRAM_BASE_ADDR + SRAM_SECTION1_SIZE)
#define TEEOS_SRAM_SIZE			    (SRAM_SECTION2_SIZE)

/*******************************************
MODEM的456K SRAM分配情况
*******************************************/
/*GU DSP LOAD 388K*/
#define MEMORY_AXI_DSP_LOAD_ADDR      (SOC_SRAM_MDM_BASE_ADDR)
#define MEMORY_AXI_DSP_LOAD_SIZE      (388*1024)
/*BBPMASTER 56K*/
#define MEMORY_AXI_TTF_BBP_ADDR       (MEMORY_AXI_DSP_LOAD_ADDR + MEMORY_AXI_DSP_LOAD_SIZE)
#define MEMORY_AXI_TTF_BBP_SIZE       (56*1024)
/*TL DSP 12K*/
#define MEMORY_AXI_TDL_ADDR           (MEMORY_AXI_TTF_BBP_ADDR + MEMORY_AXI_TTF_BBP_SIZE)
#define MEMORY_AXI_TDL_SIZE           (12*1024)
#endif /*_HI_GLOBAL_MEM_MAP_INCLUDE_H_*/


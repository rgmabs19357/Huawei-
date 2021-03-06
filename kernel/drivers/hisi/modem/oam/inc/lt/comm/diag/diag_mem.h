/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_mem.h
  Description     : scm_mem.h header file
  History         :
      1.w00182550       2013-7-18   Draft Enact

******************************************************************************/

#ifndef __DIAG_MEM_H__
#define __DIAG_MEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "socp_lfix_chan.h"

#pragma pack(4)

/*****************************************************************************
  2 Macro
*****************************************************************************/
#ifndef DIAG_MEMMAP
	#define DIAG_MEMMAP
#endif

#if(VOS_OS_VER == VOS_LINUX)
#define MSP_NOCACHEMAP(addr,size)   					ioremap(addr,size)
#else
#define MSP_NOCACHEMAP(addr,size)   					(addr)
#endif

extern VOS_UINT32 g_DiagMemVirt;
extern VOS_UINT32 g_BbpMemVirt;

#define SOCP_GLOBAL_MEM_ADDR                        DDR_SOCP_ADDR
#define SOCP_GLOBAL_MEM_SIZE                        DDR_SOCP_SIZE

/********************* DIAGͨ���ڴ����� **************************
* CCORE CNF BUFFER: 128K
* CCORE IND BUFFER: 384K
* ACORE CNF BUFFER: 64K
* ACORE IND BUFFER: 192K
* TOTAL SIZE: 768K
****************************************************************/
#define DIAG_MEM_ADDR_BASE                        	(SOCP_GLOBAL_MEM_ADDR)
#define DIAG_MEM_ADDR_BASE_VIRT          			(g_DiagMemVirt)
#define DIAG_MEM_TOTAL_SIZE							(DIAG_CODER_SRC_CNF_BUF_C_SIZE +\
													 DIAG_CODER_SRC_IND_BUF_C_SIZE +\
													 DIAG_CODER_SRC_CNF_BUF_A_SIZE +\
													 DIAG_CODER_SRC_IND_BUF_A_SIZE)

#define DIAG_CODER_SRC_CNF_BUF_C_ADDR          		DIAG_MEM_ADDR_BASE
#define DIAG_CODER_SRC_CNF_BUF_C_SIZE               (1024*128)

#define DIAG_CODER_SRC_IND_BUF_C_ADDR          		(DIAG_CODER_SRC_CNF_BUF_C_ADDR + DIAG_CODER_SRC_CNF_BUF_C_SIZE)
#define DIAG_CODER_SRC_IND_BUF_C_SIZE               (1024*128*3)

#define DIAG_CODER_SRC_CNF_BUF_A_ADDR          		(DIAG_CODER_SRC_IND_BUF_C_ADDR + DIAG_CODER_SRC_IND_BUF_C_SIZE)
#define DIAG_CODER_SRC_CNF_BUF_A_SIZE               (1024*64)

#define DIAG_CODER_SRC_IND_BUF_A_ADDR          		(DIAG_CODER_SRC_CNF_BUF_A_ADDR + DIAG_CODER_SRC_CNF_BUF_A_SIZE)
#define DIAG_CODER_SRC_IND_BUF_A_SIZE               (1024*64*3)


/********************* BBP DS�ڴ����� **************************
* BBP DS   :  2M
* BBP LOG 0:  64K
* BBP LOG 1:   0K
* BBP LOG 2:   8K
* BBP LOG 3:   8K
* BBP LOG 4:   8K
* BBP LOG 5:   8K
* BBP LOG 6:   8K
* BBP LOG 7:   8K
* TOTAL SIZE: 2M + 112K
****************************************************************/
#define BBP_MEM_ADDR_BASE                         	(DIAG_MEM_ADDR_BASE + DIAG_MEM_TOTAL_SIZE )
#define BBP_MEM_ADDR_BASE_VIRT                   	(DIAG_MEM_ADDR_BASE_VIRT + DIAG_MEM_TOTAL_SIZE)
#define BBP_MEM_TOTAL_SIZE                        	(1*1024*1024 + 112*1024)

#define BBP_DS_MEM_ADDR                         	(BBP_MEM_ADDR_BASE)
#define BBP_DS_MEM_SIZE                         	(1*1024*1024)

#define BBP_LOG0_MEM_ADDR                        	(BBP_DS_MEM_ADDR + BBP_DS_MEM_SIZE)
#define BBP_LOG0_MEM_SIZE                        	(64*1024)

#define BBP_LOG1_MEM_ADDR                        	(BBP_LOG0_MEM_ADDR + BBP_LOG0_MEM_SIZE)
#define BBP_LOG1_MEM_SIZE                        	(0*1024)

#define BBP_LOG2_MEM_ADDR                        	(BBP_LOG1_MEM_ADDR + BBP_LOG1_MEM_SIZE)
#define BBP_LOG2_MEM_SIZE                        	(8*1024)

#define BBP_LOG3_MEM_ADDR                        	(BBP_LOG2_MEM_ADDR + BBP_LOG2_MEM_SIZE)
#define BBP_LOG3_MEM_SIZE                        	(8*1024)

#define BBP_LOG4_MEM_ADDR                        	(BBP_LOG3_MEM_ADDR + BBP_LOG3_MEM_SIZE)
#define BBP_LOG4_MEM_SIZE                        	(8*1024)

#define BBP_LOG5_MEM_ADDR                        	(BBP_LOG4_MEM_ADDR + BBP_LOG4_MEM_SIZE)
#define BBP_LOG5_MEM_SIZE                        	(8*1024)

#define BBP_LOG6_MEM_ADDR                        	(BBP_LOG5_MEM_ADDR + BBP_LOG5_MEM_SIZE)
#define BBP_LOG6_MEM_SIZE                        	(8*1024)

#define BBP_LOG7_MEM_ADDR                        	(BBP_LOG6_MEM_ADDR + BBP_LOG6_MEM_SIZE)
#define BBP_LOG7_MEM_SIZE                        	(8*1024)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_mem.h */

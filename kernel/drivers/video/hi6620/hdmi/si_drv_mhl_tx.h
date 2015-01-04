/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

/*
   @file si_drv_mhl_tx.h
 */

#ifndef __SI_DRV_MHL_TX_H__
#define __SI_DRV_MHL_TX_H__
//#include <linux/types.h>
#include "si_mhl_main.h"

#define SiI_DEVICE_ID              0x8788
#define DEVCAP_VAL_DEV_STATE       0
#define DEVCAP_VAL_MHL_VERSION     MHL_VERSION
#define DEVCAP_VAL_DEV_CAT         (MHL_DEV_CAT_SOURCE /*| MHL_DEV_CATEGORY_POW_BIT */)
#define DEVCAP_VAL_ADOPTER_ID_H    (uint8_t)(SILICON_IMAGE_ADOPTER_ID >> 8)
#define DEVCAP_VAL_ADOPTER_ID_L    (uint8_t)(SILICON_IMAGE_ADOPTER_ID & 0xFF)
#if HDMI_FOR_CERTIFICATION
#define DEVCAP_VAL_VID_LINK_MODE   (MHL_DEV_VID_LINK_SUPPRGB444 | MHL_DEV_VID_LINK_SUPP_ISLANDS)
#else
#define DEVCAP_VAL_VID_LINK_MODE   (MHL_DEV_VID_LINK_SUPPRGB444 | \
    /*MHL_DEV_VID_LINK_SUPPYCBCR444 | MHL_DEV_VID_LINK_SUPPYCBCR422 | */\
    MHL_DEV_VID_LINK_SUPP_ISLANDS | MHL_DEV_VID_LINK_SUPP_VGA)/* | \
    MHL_DEV_VID_LINK_SUPP_PPIXEL)*/
#endif
#define DEVCAP_VAL_AUD_LINK_MODE   (MHL_DEV_AUD_LINK_2CH | MHL_DEV_AUD_LINK_8CH)
#define DEVCAP_VAL_VIDEO_TYPE      0
#define DEVCAP_VAL_LOG_DEV_MAP     MHL_LOGICAL_DEVICE_MAP
#define DEVCAP_VAL_BANDWIDTH       0
#define DEVCAP_VAL_FEATURE_FLAG    (MHL_FEATURE_RCP_SUPPORT | MHL_FEATURE_RAP_SUPPORT | \
    MHL_FEATURE_SP_SUPPORT)
#define DEVCAP_VAL_DEVICE_ID_H     (uint8_t)(SiI_DEVICE_ID >> 8)
#define DEVCAP_VAL_DEVICE_ID_L     (uint8_t)(SiI_DEVICE_ID)
#define DEVCAP_VAL_SCRATCHPAD_SIZE MHL_SCRATCHPAD_SIZE
#define DEVCAP_VAL_INT_STAT_SIZE   MHL_INT_AND_STATUS_SIZE
#define DEVCAP_VAL_RESERVED        0

#define SILICON_IMAGE_ADOPTER_ID 322
#define SIZE_AUDIO_INFOFRAME 14

#define T_ABORT_NEXT (2000)

#define WriteByteCBUS(offset, value) SiiDrvRegWrite(MHL_CBUS_BASE, (uint32_t)offset, value)
#define ReadByteCBUS(offset) SiiDrvRegRead(MHL_CBUS_BASE, (uint32_t)offset)
#define SET_BIT(offset, bitnumber) SiiDrvRegModify(offset, (1 << bitnumber), (1 << bitnumber))
#define CLR_BIT(offset, bitnumber) SiiDrvRegModify(offset, (1 << bitnumber), 0x00)

//
//	Look for interrupts on INTR4
//		7 = RSVD		    (reserved)
//		6 = RGND Rdy	    (interested)
//		5 = MHL DISCONNECT	(interested)
//		4 = CBUS LKOUT	    (interested)
//		3 = USB EST		    (interested)
//		2 = MHL EST		    (interested)
//		1 = RPWR5V Change	(ignore)
//		0 = SCDT Change	    (only if necessary)
//
#define INTR_4_DESIRED_MASK (BIT2 | BIT3 | BIT4 | BIT5 | BIT6)
#define UNMASK_INTR_4_INTERRUPTS \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR4_MASK_ADDR, INTR_4_DESIRED_MASK)
#define MASK_INTR_4_INTERRUPTS  \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR4_MASK_ADDR, 0x00)
#define CLEAR_INTR_4_INTERRUPTS \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR4_ADDR, 0xFF)

#define MASK_INTR_5_INTERRUPTS  \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR5_MASK_ADDR, 0x00)
#define CLEAR_INTR_5_INTERRUPTS \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR5_ADDR, 0xFF)

#define MASK_INTR_1_INTERRUPTS  \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_INT_UNMASK1_ADDR, 0x00)
#define CLEAR_INTR_1_INTERRUPTS \
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_INTR1_ADDR, 0xFF)

//  Look for interrupts on MSC INTR
//      BIT_CBUS_CNX_CHG            = BIT0,
//      BIT_CBUS_MSC_MT_DONE        = BIT1,(interested)
//      BIT_CBUS_HPD_CHANGE         = BIT2,(interested)
//      BIT_CBUS_MSC_MR_WRITE_STAT  = BIT3,(interested)
//      BIT_CBUS_MSC_MR_MSC_MSG     = BIT4,(interested)
//      BIT_CBUS_MSC_MR_WRITE_BURST = BIT5,(interested)
//      BIT_CBUS_MSC_MR_SET_INT     = BIT6,(interested)
//      BIT_CBUS_MSC_MT_DONE_NACK   = BIT7
#define CBUS_MSC_INT_DESIRED_MASK (BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6)
#define UNMASK_CBUS_MSC_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_MASK_ADDR, CBUS_MSC_INT_DESIRED_MASK)
#define MASK_CBUS_MSC_INTERRUPTS  \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_MASK_ADDR, 0x00)
#define CLEAR_CBUS_MSC_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_ADDR, 0xFF)

//  Look for interrupts on MSC Error INTR
//      BIT_CBUS_CEC_ABRT            = BIT1,
//      BIT_CBUS_DDC_ABRT            = BIT2, (interested)
//      BIT_CBUS_MSC_ABORT           = BIT3, (interested)
//      BIT_CBUS_MSC_SET_CAP_ID_RCVD = BIT4,
//      BIT_CBUS_RCV_VALID           = BIT5,
//      BIT_CBUS_CMD_ABORT           = BIT6, (interested)
//      BIT_CBUS_MHL_CABLE_CNX_CHG   = BIT7
#define CBUS_MSC_ERR_INT_DESIRED_MASK (BIT2 | BIT3 | BIT6)
#define UNMASK_CBUS_MSC_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_MASK_ADDR, CBUS_MSC_ERR_INT_DESIRED_MASK)
#define MASK_CBUS_MSC_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_MASK_ADDR, 0x00)
#define CLEAR_CBUS_MSC_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_ADDR, 0xFF)



// Look for interrupts on DDC Abort INTR
//   DDC max fail interrupt status             = BIT0,
//   DDC protocol error interrupt status       = BIT1,
//   DDC time out interrupt status             = BIT2,
//   DDC aborted by peer interrupt status      = BIT7

/* Avoid ddc timeout in case of plug/unplug the cable quickly.
   If it occurs, there are always interrupts .*/
#define CBUS_DDC_ABORT_INT_DESIRED_MASK (BIT1 | BIT7)
#define UNMASK_CBUS_DDC_ABORT_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_DDC_ABORT_INTR_MASK_ADDR, CBUS_DDC_ABORT_INT_DESIRED_MASK)
#define MASK_CBUS_DDC_ABORT_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_DDC_ABORT_INTR_MASK_ADDR, 0x00)
#define CLEAR_CBUS_DDC_ABORT_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_DDC_ABORT_INTR_ADDR, 0xFF)

// Look for interrupts on MSC Send Error INTR
//   BIT_CBUS_MSC_MT_ABORT_INT_MAX_FAIL             = BIT0,
//   BIT_CBUS_MSC_MT_ABORT_INT_PROTO_ERR            = BIT1,
//   BIT_CBUS_MSC_MT_ABORT_INT_TIMEOUT              = BIT2,
//   BIT_CBUS_MSC_MT_ABORT_INT_UNDEF_CMD            = BIT3,
//   BIT_CBUS_MSC_MT_ABORT_INT_MSC_MT_PEER_ABORT    = BIT7
#define CBUS_SEND_ERR_INT_DESIRED_MASK (BIT0 | BIT1 | BIT2 | BIT3 | BIT7)
#define UNMASK_CBUS_SEND_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_MASK_ADDR, CBUS_SEND_ERR_INT_DESIRED_MASK)
#define MASK_CBUS_SEND_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_MASK_ADDR, 0x00)
#define CLEAR_CBUS_SEND_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_ADDR, 0xFF)

// Look for interrupts on MSC Receive Error INTR
//   BIT_CBUS_MSC_MR_ABORT_INT_MAX_FAIL             = BIT0,
//   BIT_CBUS_MSC_MR_ABORT_INT_PROTO_ERR            = BIT1,
//   BIT_CBUS_MSC_MR_ABORT_INT_TIMEOUT              = BIT2,
//   BIT_CBUS_MSC_MR_ABORT_INT_UNDEF_CMD            = BIT3,
//   MSC received bad offset interrupt status (as responder) = BIT4,
//   MSC_MSG overflow  interrupt status (as responder) = BIT5,
//   BIT_CBUS_MSC_MR_ABORT_INT_MSC_MR_PEER_ABORT    = BIT7
#define CBUS_RCV_ERR_INT_DESIRED_MASK (BIT0 | BIT1 | BIT2 | BIT3 |BIT4 |BIT5 | BIT7)
#define UNMASK_CBUS_RCV_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_MASK_ADDR, CBUS_RCV_ERR_INT_DESIRED_MASK)
#define MASK_CBUS_RCV_ERR_INTERRUPTS  \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_MASK_ADDR, 0x00)
#define CLEAR_CBUS_RCV_ERR_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_ADDR, 0xFF)

// Look for interrupts on MHL Interrupt 1st Byte Register
//   DCAP_CHG            = BIT0,
//   DSCR_CHG            = BIT1,
//   REQ_WRT             = BIT2,
//   GRT-WRT             = BIT3,
#define CBUS_MHL_INT0_DESIRED_MASK (BIT0 | BIT1 | BIT2 | BIT3)
#define UNMASK_CBUS_MHL_INT0_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_0_MASK_ADDR, CBUS_MHL_INT0_DESIRED_MASK)
#define MASK_CBUS_MHL_INT0_INTERRUPTS  \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_0_MASK_ADDR, 0x00)
#define CLEAR_CBUS_MHL_INT0_INTERRUPTS  \
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_0_ADDR, 0xFF)

// Look for interrupts on MHL Interrupt 2nd Byte Register
//   EDID_CHG             = BIT1,
#define CBUS_MHL_INT1_DESIRED_MASK (BIT1)
#define UNMASK_CBUS_MHL_INT1_INTERRUPTS \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_1_MASK_ADDR, CBUS_MHL_INT1_DESIRED_MASK)
#define MASK_CBUS_MHL_INT1_INTERRUPTS  \
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_1_MASK_ADDR, 0x00)
#define CLEAR_CBUS_MHL_INT1_INTERRUPTS  \
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_INT_1_ADDR, 0xFF)

#if USE_HDCP
/* Look for interrupts for HDCP */
/*
 * HDCP authentication status change   --> bit7
 * HDCP V value ready                  --> bit6
 * COPP link status change             --> bit5
 * Audie error enable                  --> bit4
 * RSEN / CEC INTR                     --> bit3
 * HTPLG                               --> bit2
 * INTR1_STAT5                         --> bit1
 * INTR1_STAT6                         --> bit0
 */
#define HDCP_DESIRED_MASK (BIT5 | BIT7)
#define UNMASK_HDCP_INTERRUPTS SiiDrvWriteByteTPI(TPI_INTERRUPT_ADDR, HDCP_DESIRED_MASK)
#define CLEAR_HDCP_INTERRUPTS  SiiDrvWriteByteTPI(TPI_INTERRUPT_STATUS_ADDR, HDCP_DESIRED_MASK)
#endif /* USE_HDCP */


#define I2C_INACCESSIBLE -1
#define I2C_ACCESSIBLE 1
#define SIZE_AVI_INFOFRAME 17

#define MHL_VSIF_LENTH 0x1F
#define MHL_VSIF_BODYLENTH 5
#define VSIF_TYPE 0x81
#define VSIF_VERSION 0x01


//------------------------------------------------------------------------------
// Driver API typedefs
//------------------------------------------------------------------------------
//
// structure to hold command details from upper layer to CBUS module
//
typedef struct
{
    uint8_t reqStatus;       // CBUS_IDLE, CBUS_PENDING
    uint8_t retryCount;
    uint8_t command;         // VS_CMD or RCP opcode
    uint8_t offsetData;      // Offset of register on CBUS or RCP data
    uint8_t length;          // Only applicable to write burst. ignored otherwise.
    union
    {
        uint8_t msgData[ 16 ];   // Pointer to message data area.
	    unsigned char *pdatabytes;			// pointer for write burst or read many bytes
    }payload_u;

} cbus_req_t;

typedef struct _StateFlags_t
{
    uint8_t upStreamMuted  : 1;
    uint8_t reserved       : 7;
} StateFlags_t, *PStateFlags_t;

enum
{
    ACR_N_value_192k = 24576,
    ACR_N_value_96k  = 12288,
    ACR_N_value_48k  = 6144,
    ACR_N_value_176k = 25088,
    ACR_N_value_88k = 12544,
    ACR_N_value_44k = 6272,
    ACR_N_value_32k = 4096,
    ACR_N_value_default = 6144,
};

typedef enum
{
    COLOR_SPACE_RGB = 0,
    COLOR_SPACE_YCBCR444,
    COLOR_SPACE_YCBCR422,
    COLOR_SPACE_RGB_SOLID
} eMHLTXInputColorSpace;

typedef enum
{
    VM_VGA = 0,     //VIC 1
    VM_480P,        //VIC 2,3
    VM_576P,        //VIC 17,18
    VM_720P60,      //VIC 4
    VM_720P50,      //VIC 19
    VM_INVALID
} inVideoTypes_t;

typedef enum
{
    I2S_192 = 0,
    I2S_96,
    I2S_48,
    I2S_176,
    I2S_88,
    I2S_44,
    I2S_32,
    TDM_192,
    TDM_96,
    TDM_48,
    TDM_176,
    TDM_88,
    TDM_44,
    TDM_32,
    TDM_192_8ch,
    AUD_SPDIF,
    AUD_TYP_NUM,
    AUD_INVALID
} inAudioTypes_t;

typedef struct
{
    uint8_t regAUD_mode;    //114
    uint8_t regAUD_ctrl;    //11D
    uint8_t regAUD_freq;    //121
    uint8_t regAUD_src;     //123
    uint8_t regAUD_tdm_ctrl; //128
    uint8_t regAUD_path;    //12F
    uint8_t rsved[2];
} audioConfig_t;

// DEVCAP we will initialize to
#if HDMI_FOR_CERTIFICATION
#define MHL_LOGICAL_DEVICE_MAP (MHL_DEV_LD_GUI)
#else
#define MHL_LOGICAL_DEVICE_MAP (MHL_DEV_LD_AUDIO | MHL_DEV_LD_VIDEO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_GUI)
#endif

#define	IncrementCBusReferenceCount(func) {g_PlumTxConfig.cbusReferenceCount++; SII_DBG_PRINT("MhlTx:%s cbusReferenceCount:%d\n", #func, (int)g_PlumTxConfig.cbusReferenceCount); }
#define	DecrementCBusReferenceCount(func) {g_PlumTxConfig.cbusReferenceCount--; SII_DBG_PRINT("MhlTx:%s cbusReferenceCount:%d\n", #func, (int)g_PlumTxConfig.cbusReferenceCount); }

#define SetMiscFlag(func, x) { g_PlumTxConfig.miscFlags |= (x); SII_DBG_PRINT("MhlTx:%s set %s\n", # func, # x); }
#define ClrMiscFlag(func, x) { g_PlumTxConfig.miscFlags &= ~(x); SII_DBG_PRINT("MhlTx:%s clr %s\n", # func, # x); }
#define TestMiscFlag(x) (g_PlumTxConfig.miscFlags & (x))

extern int Int4Isr( void );
extern uint8_t CalculateGenericCheckSum(uint8_t *infoFrameData, uint8_t checkSum, uint8_t length);
extern void CbusReset (void);
extern void SiiChipInitialize ( void );
extern void SiiDeviceIsr( void );
extern bool SiiDrvCBusBusy(void);
extern void SiiDrvGetScratchPad(uint8_t startReg, uint8_t * pData, uint8_t length);
extern void SiiDrvNotifyEdidChange ( void );
extern void SiiDrvPowBitChange (bool enable);
extern void SiiDrvProcessRgndMhl( void );
extern bool SiiDrvSendCbusCommand ( cbus_req_t * pReq  );
extern void SiiDrvTmdsControl (bool enable);
extern void SiiDrvVideoMute( void );
extern void SiiDrvVideoUnmute( void );
extern uint8_t CBusProcessErrors( uint8_t int1Status );
extern void MhlCbusIsr( void );
#if USE_PP_MODE
extern uint16_t SiiMhlTxDrvGetIncomingHorzTotal(void);
extern uint16_t SiiMhlTxDrvGetIncomingVertTotal(void);
extern void SiiMhlTxDrvSet3DMode(uint8_t do3D,uint8_t three3ModeParm);
extern void SiiMhlTxDrvSetPixelClockFrequency(uint32_t pixelClockFrequencyParm);
extern void	SiiMhlTxDrvSetPackedPixelStatus( int supportPackedPixel );
extern uint8_t SiiMhlTxDrvGetPackedPixelStatus( void );
extern void SiiMhlTxDrvApplyPPModeSettings( void);
#endif
#endif  // __SI_DRV_MHL_TX_H__

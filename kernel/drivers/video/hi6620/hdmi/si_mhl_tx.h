/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,   */
/*  transcribed, or translated into any language or computer format, in any form  */
/*  or by any means without written permission of: Silicon Image, Inc.,           */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

/*
   @file si_mhl_tx.h
 */
#ifndef __SI_MHL_TX_H__
#define __SI_MHL_TX_H__
#include "si_drv_mhl_tx.h"

#define GetNextCBusTransaction(func) GetNextCBusTransactionWrapper(#func)
#define PutNextCBusTransaction(req) PutNextCBusTransactionWrapper(req)
#define PutPriorityCBusTransaction(pReq) PutPriorityCBusTransactionWrapper(pReq)

#define DEVCAP_REFRESH_COMPLETE (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex == sizeof(g_PlumTxConfig.devCapCache.aucDevCapCache))
#define PackedPixelAvailable (MHL_DEV_VID_LINK_SUPP_PPIXEL & g_PlumTxConfig.devCapCache.aucDevCapCache[DEVCAP_OFFSET_VID_LINK_MODE])
#define HDMI_VicInfoEntry(modeNum, columns, rows, FieldRate0, FieldRate1, pixelClock0, pixelClock1) {columns, rows, FieldRate0, FieldRate1, pixelClock0, pixelClock1}                    // VIC:modeNum

#define QUEUE_SIZE(x) (sizeof(x.queue) / sizeof(x.queue[0]))
#define MAX_QUEUE_DEPTH(x) (QUEUE_SIZE(x) - 1)
#define QUEUE_DEPTH(x) ((x.head <= x.tail) ? (x.tail - x.head) : (QUEUE_SIZE(x) - x.head + x.tail))
#define QUEUE_FULL(x) (QUEUE_DEPTH(x) >= MAX_QUEUE_DEPTH(x))

#define ADVANCE_QUEUE_HEAD(x) { x.head = (x.head < MAX_QUEUE_DEPTH(x)) ? (x.head + 1) : 0; }
#define ADVANCE_QUEUE_TAIL(x) { x.tail = (x.tail < MAX_QUEUE_DEPTH(x)) ? (x.tail + 1) : 0; }
#define RETREAT_QUEUE_HEAD(x) { x.head = (x.head > 0) ? (x.head - 1) : MAX_QUEUE_DEPTH(x); }

#define SCRATCHPAD_SIZE 16

#define FILL_THIS_IN    0

#define Cea861D_VicInfoEntry(modeNum, columns, rows, HBlank, VBLank, FieldRate, ImageAspectRatio, scanmode, PixelAspectRatio, flags, clocksPerPelShift, AdditionalVBlank, pixClockDiv10000) \
    {columns, rows, HBlank, VBLank, FieldRate, {ImageAspectRatio, scanmode, \
        PixelAspectRatio, flags, clocksPerPelShift, AdditionalVBlank} /*,pixClockDiv10000*/}                      // VIC:modeNum


#define MAX_VFREQ_DIFF (8)

#define	MHL_TX_EVENT_NONE				0x00	/* No event worth reporting.  */
#define	MHL_TX_EVENT_DISCONNECTION		0x01	/* MHL connection has been lost */
#define	MHL_TX_EVENT_CONNECTION			0x02	/* MHL connection has been established */
#define	MHL_TX_EVENT_RCP_READY			0x03	/* MHL connection is ready for RCP */
#define	MHL_TX_EVENT_RCP_RECEIVED		0x04	/* Received an RCP. Key Code in "eventParameter" */
#define	MHL_TX_EVENT_RCPK_RECEIVED		0x05	/* Received an RCPK message */
#define	MHL_TX_EVENT_RCPE_RECEIVED		0x06	/* Received an RCPE message .*/
#define	MHL_TX_EVENT_DCAP_CHG			0x07	/* Received DCAP_CHG interrupt */
#define	MHL_TX_EVENT_DSCR_CHG			0x08	/* Received DSCR_CHG interrupt */
#define	MHL_TX_EVENT_POW_BIT_CHG		0x09	/* Peer's power capability has changed */
#define	MHL_TX_EVENT_RGND_MHL			0x0A	/* RGND measurement has determine that the peer is an MHL device */
#define MHL_TX_EVENT_TMDS_ENABLED       0x0B    /* TMDS output enable */
#define MHL_TX_EVENT_TMDS_DISABLED      0x0C    /* TMDS output is disabled */

/*
queue implementation
 */
#define NUM_CBUS_EVENT_QUEUE_EVENTS 5
typedef struct _CBusQueue_t
{
    uint8_t    head; // queue empty condition head == tail
    uint8_t    tail;
    cbus_req_t queue[NUM_CBUS_EVENT_QUEUE_EVENTS];
} CBusQueue_t, *PCBusQueue_t;


typedef struct _HDMI_VIC_Info_t
{
    uint16_t columns;
    uint16_t rows;
    uint32_t fieldRate0InMilliHz, fieldRate1InMilliHz;
    uint32_t pixelClock0, pixelClock1;
} HDMI_VIC_Info_t, *PHDMI_VIC_Info_t;

typedef struct _BitFieldFlags_t
{
    unsigned char syncDetect  : 1;
    unsigned char upStreamHPD : 1;
    unsigned char reserved    : 6;
} BitFieldFlags_t, *PBitFieldFlags_t;


//
// structure to hold operating information of MhlTx component
//
typedef struct
{
    uint8_t status_0;           // Received status from peer is stored here
    uint8_t status_1;           // Received status from peer is stored here

    uint8_t connectedReady;                 // local MHL CONNECTED_RDY register value
    uint8_t linkMode;                       // local MHL LINK_MODE register value

    bool mscCmdInProgress;  //system is busy sending command.
    bool hdcpStartPending;    //HDCP is waiting to begin. It was delayed because that system was busy sending command.

    bool bTmdsOutputEnabled;

    bool  mhlConnectionEvent;
    uint8_t mhlConnected;

    uint8_t mhlHpdRSENflags;                   // keep track of SET_HPD/CLR_HPD
    uint8_t rapFlags;       // CONTENT ON/OFF
    // Remember FEATURE FLAG of the peer to reject app commands if unsupported
    uint8_t mscFeatureFlag;

    // mscMsgArrived == true when a MSC MSG arrives, false when it has been picked up
    bool  mscMsgArrived;
    uint8_t mscMsgSubCommand;
    uint8_t mscMsgData;

    uint8_t cbusReferenceCount;              // keep track of CBUS requests

    // Remember last command, offset that was sent.
    // Mostly for READ_DEVCAP command and other non-MSC_MSG commands
    uint8_t mscLastCommand;
    uint8_t mscLastOffset;
    uint8_t mscLastData;

    // Remember last MSC_MSG command (RCPE particularly)
    uint8_t mscMsgLastCommand;
    uint8_t mscMsgLastData;
    uint8_t mscSaveRcpKeyCode;

#define MHL2_0_SUPPORT
#ifdef MHL2_0_SUPPORT //(
    uint8_t      burstEntryCount3D_VIC;
    uint8_t      vic2Dindex;
    uint8_t      burstEntryCount3D_DTD;
    ScratchPad_u incomingScratchPad;
    uint8_t      vesaDTDindex;
    uint8_t      cea861DTDindex;
#endif //)
    uint8_t preferredClkMode;
    uint8_t ucDevCapCacheIndex;
    MHLDevCap_t devCapCache;

    uint32_t miscFlags;                      // such as SCRATCHPAD_BUSY                 //Rx scratchpad busy

    PVendorSpecificDataBlock_t    pHdmiVendorSpecificDataBlock;
    PVideoDataBlock_t             pVideoDataBlock2D;
    PVideoCapabilityDataBlock_t   pVideoCapabilityDataBlock;
    PVSDBByte13ThroughByte15_t    pByte13ThroughByte15;
    P_3D_Mask_t                   p3DMask;
    P_3DStructureAndDetailEntry_u pThreeD;
    uint8_t    *                  p3DLimit;

    AVIInfoFrame_t  currentAviInfoFrame;
    BitFieldFlags_t flags;

    Type_EDID_Descriptors EDID;

    uint8_t               cbusImpedance;
    uint8_t               rsved[3];
} mhlTx_config_t;

// bits for mhlHpdRSENflags:
typedef enum
{
    MHL_HPD  = 0x01,
    MHL_RSEN = 0x02
} MhlHpdRSEN_e;

typedef enum
{
    FLAGS_SCRATCHPAD_BUSY = 0x0001,
    FLAGS_REQ_WRT_PENDING = 0x0002,
    FLAGS_WRITE_BURST_PENDING = 0x0004,
    FLAGS_RCP_READY = 0x0008,
    FLAGS_HAVE_DEV_CATEGORY = 0x0010,
    FLAGS_HAVE_DEV_FEATURE_FLAGS = 0x0020,
    FLAGS_HAVE_COMPLETE_DEVCAP = 0x0040,
    FLAGS_SENT_DCAP_RDY = 0x0080,
    FLAGS_SENT_PATH_EN = 0x0100,
    FLAGS_SENT_3D_REQ = 0x0200,
    FLAGS_BURST_3D_VIC_DONE = 0x0400,
    FLAGS_BURST_3D_DTD_DONE = 0x0800,
    FLAGS_BURST_3D_DTD_VESA_DONE = 0x1000,
    FLAGS_BURST_3D_DONE  = 0x2000,
    FLAGS_EDID_READ_DONE = 0x4000
} MiscFlags_e;

typedef enum
{
    RAP_CONTENT_ON = 0x01
} rapFlags_e;

/*VIC Defintions*/
typedef enum
{
    vifSingleFrameRate = 0x00,
    vifDualFrameRate = 0x01
} VicInfoFlags_e;

typedef enum
{
    vsmProgressive = 0,
    vsmInterlaced = 1
} VicScanMode_e;

typedef enum
{
    par1to1,
    par16to15,
    par16to27,
    par16to45,
    par16to45_160to45,
    par1to15_10to15,
    par1to9_10to9,
    par2to15_20to15,
    par2to9,
    par2to9_20to9,
    par32to27,
    par32to45,
    par4to27_40to27,
    par4to9,
    par4to15,
    par64to45,
    par8to15,
    par8to27,
    par8to27_80to27,
    par8to45_80to45,
    par8to9
} PixelAspectRatio_e;

typedef struct _VIC_Info_Fields_t
{
    ImageAspectRatio_e imageAspectRatio        : 2;
    VicScanMode_e      interlaced              : 1;
    PixelAspectRatio_e pixelAspectRatio        : 5;

    VicInfoFlags_e frameRateInfo            : 1;
    uint8_t        clocksPerPixelShiftCount : 2;
    uint8_t        field2VBlank             : 2;
    uint8_t        reserved                 : 3;
} VIC_Info_Fields_t, *PVIC_Info_Fields_t;

typedef struct _VIC_Info_t
{
    uint16_t          columns;
    uint16_t          rows;
    uint16_t          HBlankInPixels;
    uint16_t          VBlankInPixels;
    uint32_t          fieldRateInMilliHz;
    VIC_Info_Fields_t fields;

    //    uint16_t pixClockDiv10000;
} VIC_Info_t, *PVIC_Info_t;

typedef enum
{
	MHL_TX_EVENT_STATUS_HANDLED = 0,
    MHL_TX_EVENT_STATUS_PASSTHROUGH
}MhlTxNotifyEventsStatus_e;

typedef enum
{
	SCRATCHPAD_FAIL          = -4,
    SCRATCHPAD_BAD_PARAM     = -3,
    SCRATCHPAD_NOT_SUPPORTED = -2,
    SCRATCHPAD_BUSY          = -1,
    SCRATCHPAD_SUCCESS       = 0
}ScratchPadStatus_e;


extern MhlTxNotifyEventsStatus_e AppNotifyMhlEvent(uint8_t eventCode, uint8_t eventParam);
extern uint32_t CalculatePixelClock(uint16_t columns, uint16_t rows, uint32_t verticalSyncFrequencyInMilliHz, uint8_t VIC);
extern cbus_req_t *GetNextCBusTransactionImpl(void);
extern cbus_req_t *GetNextCBusTransactionWrapper(char *pszFunction);
extern bool PutNextCBusTransactionImpl(cbus_req_t *pReq);
extern bool PutNextCBusTransactionWrapper(cbus_req_t *pReq);
extern bool PutPriorityCBusTransactionImpl(cbus_req_t *pReq);
extern bool PutPriorityCBusTransactionWrapper(cbus_req_t *pReq);
extern uint8_t QualifyPixelClockForMhl(uint32_t pixelClockFrequency, uint8_t bitsPerPixel);
extern void SiiCheck3D_DTD_Sequence_Done(PMhl2VideoFormatData_t pWriteBurstData);
extern bool SiiClrPathEn( void );
extern void SiiDisplayTimingEnumerationEnd(void);
extern uint8_t SiiDrvParse861ShortDescriptors (uint8_t *pEdidBlockData   );
extern void SiiEnumerateHdmiVsdb(void);
extern uint8_t SiiGetVICTableSize(void);
extern void SiiGotMhlIntr( uint8_t intr_0, uint8_t intr_1 );
extern void SiiGotMhlMscMsg( uint8_t subCommand, uint8_t cmdData );
extern void SiiGotMhlStatus( uint8_t status_0, uint8_t status_1 );
extern void SiiInitialize(void);
extern void SiiMhlTxResetStates( void );
extern bool SiiMhlTxCBusBusy(void);
extern void SiiMhlTxProcessEvents(void);
extern void SiiMscCommandDone( uint8_t data1 );
extern void SiiMscWriteBurstDone( uint8_t data1 );
extern void SiiNotifyConnection( bool mhlConnected );
extern void SiiNotifyDsHpdChange( uint8_t dsHpdStatus );
extern void SiiNotifyRgndMhl( void );
extern void SiiProcessWriteBurstData( void );
extern void SiiPruneDTDList(P_18ByteDescriptor_u pDesc, uint8_t limit);
extern void SiiPruneEDID(void);
extern bool SiiRcpeSend( uint8_t rcpeErrorCode );
extern bool SiiRcpkSend( uint8_t rcpKeyCode );
extern bool SiiRcpSend( uint8_t rcpKeyCode );
extern uint8_t SiiReadConnectionStatus(void);
extern bool SiiReadDevcap( uint8_t offset );
extern uint8_t QualifyPathEnable( void );
extern void SiiMhlTxDriveStates( void );
extern uint8_t SiiIsQualifiedMhlHdmiVIC(uint8_t VIC, PMhl2VideoDescriptor_t pMhl2VideoDescriptor);
extern uint8_t SiiSetPreferredPixelFormat(uint8_t clkMode);
#if USE_PP_MODE
extern uint8_t SiiMhlTxAttemptPackedPixel( void );
#endif
#endif

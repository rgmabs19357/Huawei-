/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

/*
   @file si_mhl_tx.c
 */
#include "si_drv_mhl_tx.h"  
#include "si_edid.h"
#include "si_hdcp.h"
#include "si_infoframe.h"
#include "si_mhl_defs.h"
#include "si_mhl_hw.h"
#include "si_mhl_main.h"  
#include "si_mhl_tx.h"
#include "si_reg_access.h"
#include <linux/delay.h>

extern hdmi_device hdmi;
extern uint8_t edid[HDMI_EDID_MAX_LENGTH];
extern uint8_t rcpSupportTable[]; 
extern unsigned short rcpKeyMapTable[];
extern bool mscAbortFlag;
extern VIC_Info_t vicInfo[];

CBusQueue_t CBusQueue = {0};
//
// Store global config info here. This is shared by the driver.
//
//
//
// structure to hold operating information of MhlTx component
//
mhlTx_config_t g_PlumTxConfig = {0};

char *pszSpace = "n/a";
char *pszFrameSequential = "FS ";
char *pszTopBottom = "TB ";
char *pszLeftRight = "LR ";

VIC_Info_t vicInfo[] =
{
    Cea861D_VicInfoEntry( 0,										0,         0,              0,
                          0,                                     0000, iar16to10, vsmProgressive, par1to1,
                          vifSingleFrameRate,						0,         0,             0), // place holder
    Cea861D_VicInfoEntry( 1,                                      640,       480,            160,
                          45,									60000, iar4to3,   vsmProgressive,
                          par1to1,            vifDualFrameRate,                0,              0,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 2,                                      720,       480,            138,
                          45,									60000, iar4to3,   vsmProgressive,
                          par8to9,            vifDualFrameRate,                0,              0,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 3,                                      720,       480,            138,
                          45,									60000, iar16to9,  vsmProgressive,
                          par32to27,          vifDualFrameRate,                0,              0,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 4,                                     1280,       720,            370,
                          30,									60000, iar16to9,  vsmProgressive,
                          par1to1,            vifDualFrameRate,                0,              0,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 5,                                     1920,		1080,            280,
                          22,									60000, iar16to9,  vsmInterlaced,
                          par1to1,            vifDualFrameRate,                0,              1,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 6,                                      720,       480,            276,
                          22,									60000, iar4to3,   vsmInterlaced,
                          par8to9,            vifDualFrameRate,                1,              1,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 7,                                      720,       480,            276,
                          22,									60000, iar16to9,  vsmInterlaced,
                          par32to27,          vifDualFrameRate,                1,              1,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 8,                                      720,       240,            276,
                          22,									60000, iar4to3,   vsmProgressive,
                          par4to9,            vifDualFrameRate,                1,              1,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry( 9,                                      720,       428,            276,
                          22,									60000, iar16to9,  vsmProgressive,
                          par16to27,          vifDualFrameRate,                1,              1,
                          FILL_THIS_IN),
    Cea861D_VicInfoEntry(10,                                     2880,       480,            552,
                         22,									60000, iar4to3,   vsmInterlaced,
                         par2to9_20to9,       vifDualFrameRate,                0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(11,                                     2880,       480,            552,
                         22,									60000, iar16to9,  vsmInterlaced,
                         par8to27_80to27,     vifDualFrameRate,                0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(12,                                     2880,       240,            552,
                         22,									60000, iar4to3,   vsmProgressive,
                         par1to9_10to9,       vifDualFrameRate,                0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(13,                                     2880,       240,            552,
                         22,									60000, iar16to9,  vsmProgressive,
                         par4to27_40to27,     vifDualFrameRate,                0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(14,                                     1440,       480,            276,
                         45,									60000, iar4to3,   vsmProgressive,
                         par4to9,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(15,                                     1440,       480,            276,
                         45,									60000, iar16to9,  vsmProgressive,
                         par16to27,           vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(16,                                     1920,		1080,            280,
                         45,									60000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         14850),
    Cea861D_VicInfoEntry(17,                                      720,       576,            144,
                         49,									50000, iar4to3,   vsmProgressive,
                         par16to15,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(18,                                      720,       576,            144,
                         49,									50000, iar16to9,  vsmProgressive,
                         par64to45,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(19,                                     1280,       720,            700,
                         30,									50000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(20,                                     1920,		1080,            720,
                         22,									50000, iar16to9,  vsmInterlaced,
                         par1to1,             vifSingleFrameRate,              0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(21,                                      720,       576,            288,
                         24,									50000, iar4to3,   vsmInterlaced,
                         par16to15,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(22,                                      720,       576,            288,
                         24,									50000, iar16to9,  vsmInterlaced,
                         par64to45,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(23,                                      720,       288,            288,
                         24,									50000, iar4to3,   vsmProgressive,
                         par8to15,            vifSingleFrameRate,              1,              2,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(24,                                      720,       288,            288,
                         24,									50000, iar16to9,  vsmProgressive,
                         par32to45,           vifSingleFrameRate,              1,              2,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(25,                                     2880,       576,            576,
                         24,									50000, iar4to3,   vsmInterlaced,
                         par2to15_20to15,     vifSingleFrameRate,              0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(26,                                     2880,       576,            576,
                         24,									50000, iar16to9,  vsmInterlaced,
                         par16to45_160to45,   vifSingleFrameRate,              0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(27,                                     2880,       288,            576,
                         24,									50000, iar4to3,   vsmProgressive,
                         par1to15_10to15,     vifSingleFrameRate,              0,              2,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(28,                                     2880,       288,            576,
                         24,									50000, iar16to9,  vsmProgressive,
                         par8to45_80to45,     vifSingleFrameRate,              0,              2,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(29,                                     1440,       576,            288,
                         49,									50000, iar4to3,   vsmProgressive,
                         par8to15,            vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(30,                                     1440,       576,            288,
                         49,									50000, iar16to9,  vsmProgressive,
                         par32to45,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(31,                                     1920,		1080,            720,
                         45,									50000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(32,                                     1920,		1080,            830,
                         45,									24000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(33,                                     1920,		1080,            720,
                         45,									25000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(34,                                     1920,		1080,            280,
                         45,									30000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(35,                                     2880,       480,            552,
                         45,									60000, iar4to3,   vsmProgressive,
                         par2to9,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(36,                                     2880,       480,            552,
                         45,									60000, iar16to9,  vsmProgressive,
                         par8to27,            vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(37,                                     2880,       576,            576,
                         49,									50000, iar4to3,   vsmProgressive,
                         par4to15,            vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(38,                                     2880,       576,            576,
                         49,									50000, iar16to9,  vsmProgressive,
                         par16to45,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(39,                                     1920,		1080,            384,
                         85,									50000, iar16to9,  vsmInterlaced,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),       /*1250,total*/
    Cea861D_VicInfoEntry(40,                                     1920,		1080,            720,
                         22,                                   100000, iar16to9,  vsmInterlaced,
                         par1to1,             vifSingleFrameRate,              0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(41,                                     1280,       720,            700,
                         30,                                   100000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(42,                                      720,       576,            144,
                         49,                                   100000, iar4to3,   vsmProgressive,
                         par16to15,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(43,                                      720,       576,            144,
                         49,                                   100000, iar16to9,  vsmProgressive,
                         par64to45,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(44,                                      720,       576,            288,
                         24,                                   100000, iar4to3,   vsmInterlaced,
                         par16to15,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(45,                                      720,       576,            288,
                         24,                                   100000, iar16to9,  vsmInterlaced,
                         par64to45,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(46,                                     1920,		1080,            280,
                         22,                                   120000, iar16to9,  vsmInterlaced,
                         par1to1,             vifDualFrameRate,                0,              1,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(47,                                     1280,       720,            370,
                         30,                                   120000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(48,                                      720,       480,            138,
                         45,                                   120000, iar4to3,   vsmProgressive,
                         par8to9,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(49,                                      720,       480,            138,
                         45,                                   120000, iar16to9,  vsmProgressive,
                         par32to27,           vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(50,                                      720,       480,            276,
                         22,                                   120000, iar4to3,   vsmInterlaced,
                         par8to9,             vifDualFrameRate,                1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(51,                                      720,       480,            276,
                         22,                                   120000, iar16to9,  vsmInterlaced,
                         par32to27,           vifDualFrameRate,                1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(52,                                      720,       576,            144,
                         49,                                   200000, iar4to3,   vsmProgressive,
                         par16to15,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(53,                                      720,       576,            144,
                         49,                                   200000, iar16to9,  vsmProgressive,
                         par64to45,           vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(54,                                      720,       576,            288,
                         24,                                   200000, iar4to3,   vsmInterlaced,
                         par16to15,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(55,                                      720,       576,            288,
                         24,                                   200000, iar16to9,  vsmInterlaced,
                         par64to45,           vifSingleFrameRate,              1,              1,
                         FILL_THIS_IN),       //(1440)
    Cea861D_VicInfoEntry(56,                                      720,       480,            138,
                         45,                                   240000, iar4to3,   vsmProgressive,
                         par8to9,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(57,                                      720,       480,            138,
                         45,                                   240000, iar16to9,  vsmProgressive,
                         par32to27,           vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(58,                                      720,       480,            276,
                         22,                                   240000, iar4to3,   vsmInterlaced,
                         par8to9,             vifDualFrameRate,                1,              1,
                         FILL_THIS_IN),  //(1440)
    Cea861D_VicInfoEntry(60,		1280,            720,
                   370,                                    30,
                   24000,
                   iar16to9,          vsmProgressive,
                   par1to1,
                   vifDualFrameRate,
                   0,										0,
                   FILL_THIS_IN),
    Cea861D_VicInfoEntry(61,                                     1280,       720,            370,
                         30,									25000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(62,                                     1280,       720,            370,
                         30,									30000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(63,                                     1920,		1080,            280,
                         45,                                   120000, iar16to9,  vsmProgressive,
                         par1to1,             vifDualFrameRate,                0,              0,
                         FILL_THIS_IN),
    Cea861D_VicInfoEntry(64,                                     1920,		1080,            280,
                         45,                                   100000, iar16to9,  vsmProgressive,
                         par1to1,             vifSingleFrameRate,              0,              0,
                         FILL_THIS_IN)
};

HDMI_VIC_Info_t HDMI_VicInfo[] =
{
    HDMI_VicInfoEntry( 0,    0,    0,     0,     0,			0,         0), // place holder
    HDMI_VicInfoEntry( 1, 3840, 2160, 30000, 29970, 297000000, 296703000),
    HDMI_VicInfoEntry( 2, 3840, 2160, 25000, 25000, 297000000, 297000000),
    HDMI_VicInfoEntry( 3, 3840, 2160, 24000, 23976, 297000000, 296703000),
    HDMI_VicInfoEntry( 4, 4096, 2160, 24000, 24000, 297000000, 297000000)
};

static void ExamineLocalAndPeerVidLinkMode( void );
#if WRITE_BURST
static bool SiiDoWriteBurst( uint8_t startReg, uint8_t *pData, uint8_t length );
static ScratchPadStatus_e SiiRequestWriteBurst(uint8_t startReg, uint8_t length, uint8_t *pData);
#endif
#if USE_3D
static uint8_t IsMhlTimingMode(uint16_t columns, uint16_t rows, uint32_t verticalSyncFrequencyInMilliHz,
                                 PMhl2VideoDescriptor_t pMhl2VideoDescriptorParm,
                                 uint8_t VIC);
static uint8_t IsQualifiedMhlVIC(uint8_t VIC, PMhl2VideoDescriptor_t pMhlVideoDescriptor);
static bool SiiDrvParseDetailedTimingFor3D(P_18ByteDescriptor_u pDesc, uint8_t Block, uint8_t *pIsTiming,
                                                 PMhl2VideoDescriptor_t pMhl2VideoDescriptor);
static void SiiProcess3D_DTDBurst(PMhl2VideoFormatData_t pWriteBurstData);
static void SiiProcess3D_VICBurst(PMhl2VideoFormatData_t pWriteBurstData // from 3D_REQ
  );
static void SiiSend3DReq(void);
#endif
static bool SiiMhlTxSendMscMsg ( uint8_t command, uint8_t cmdData );
static bool SiiSetPathEn(void );
static bool SiiRapkSend( uint8_t rapkErrCode );
static void SiiRefreshPeerDevCapEntries(void);
static bool SiiSendLinkMode(void);
static bool SiiSetDCapRdy( void );
static bool SiiSetInt( uint8_t regToWrite, uint8_t mask, uint8_t priorityLevel );
static bool SiiSetStatus( uint8_t regToWrite, uint8_t value );
static void SiiTmdsEnable(void);
static void sii_mhltx_rcvd_rap(void);
static void sii_mhltx_rcvd_rapk(void);
static void sii_mhltx_rcvd_rcp(void);
static void sii_mhltx_rcvd_rcpe(void);
static void sii_mhltx_rcvd_rcpk(void);

cbus_req_t *GetNextCBusTransactionImpl(void)
{
    if (0 == QUEUE_DEPTH(CBusQueue))
    {
        return NULL;
    }
    else
    {
        cbus_req_t *retVal;
        retVal = &CBusQueue.queue[CBusQueue.head];
        ADVANCE_QUEUE_HEAD(CBusQueue)
        return retVal;
    }
}

cbus_req_t *GetNextCBusTransactionWrapper(char *pszFunction)
{
    SII_DBG_PRINT("MhlTx:GetNextCBusTransaction: %s depth: %d  head: %d  tail: %d\n",
                                          pszFunction,
                                          (int)QUEUE_DEPTH(CBusQueue),
                                          (int)CBusQueue.head,
                                          (int)CBusQueue.tail);
    return GetNextCBusTransactionImpl();
}

bool PutNextCBusTransactionImpl(cbus_req_t *pReq)
{
    if (QUEUE_FULL(CBusQueue))
    {
        //queue is full
        return false;
    }

    // at least one slot available
    CBusQueue.queue[CBusQueue.tail] = *pReq;
    ADVANCE_QUEUE_TAIL(CBusQueue);
    return true;
}

// use this wrapper to do debugging output for the routine above.
bool PutNextCBusTransactionWrapper(cbus_req_t *pReq)
{
    bool retVal;
    SII_DBG_PRINT("MhlTx: PutNextCBusTransaction 0x%02X 0x%02X 0x%02X depth:%d head: %d tail:%d\n",
                                          (int)pReq->command,
                                          (int)((MHL_MSC_MSG
                                                 == pReq->command) ? pReq->payload_u.msgData[0] : pReq->offsetData),
                                          (int)((MHL_MSC_MSG
                                                 == pReq->command) ? pReq->payload_u.msgData[1] : pReq->payload_u.msgData[0]),
                                          (int)QUEUE_DEPTH(CBusQueue),
                                          (int)CBusQueue.head,
                                          (int)CBusQueue.tail
                    );
    retVal = PutNextCBusTransactionImpl(pReq);

    if (!retVal)
    {
        SII_DBG_PRINT("MhlTx: PutNextCBusTransaction queue full, when adding event 0x%02X\n",
                                              (int)pReq->command);
    }

    return retVal;
}

bool PutPriorityCBusTransactionImpl(cbus_req_t *pReq)
{
    if (QUEUE_FULL(CBusQueue))
    {
        //queue is full
        SII_DBG_PRINT("MhlTx  Queque is full\n");
        return false;
    }

    // at least one slot available
    RETREAT_QUEUE_HEAD(CBusQueue);
    CBusQueue.queue[CBusQueue.head] = *pReq;
    return true;
}

bool PutPriorityCBusTransactionWrapper(cbus_req_t *pReq)
{
    bool retVal;

    SII_DBG_PRINT("MhlTx: PutPriorityCBusTransaction 0x%02X 0x%02X 0x%02X depth:%d head: %d tail:%d\n",
                     (int)pReq->command,
                     (int)((MHL_MSC_MSG == pReq->command) ? pReq->payload_u.msgData[0] : pReq->offsetData),
                     (int)((MHL_MSC_MSG == pReq->command) ? pReq->payload_u.msgData[1] : pReq->payload_u.msgData[0]),
                     (int)QUEUE_DEPTH(CBusQueue),
                     (int)CBusQueue.head,
                     (int)CBusQueue.tail
                    );
    retVal = PutPriorityCBusTransactionImpl(pReq);
    if (!retVal)
    {
        SII_DBG_PRINT("MhlTx: PutPriorityCBusTransaction queue full, when adding event 0x%02X\n",
                         (int)pReq->command);
    }

    return retVal;
}

bool SiiMhlTxCBusBusy(void)
{
    return ((QUEUE_DEPTH(CBusQueue) > 0) || SiiDrvCBusBusy() || 
             g_PlumTxConfig.cbusReferenceCount) ? true : false;
}

/*
    QualifyPathEnable
        Support MHL 1.0 sink devices.

    return value
        1 - consider PATH_EN received
        0 - consider PATH_EN NOT received
 */
uint8_t QualifyPathEnable( void ) //UT ZHOU
{
    uint8_t retVal = 0; // return fail by default

    if (MHL_STATUS_PATH_ENABLED & g_PlumTxConfig.status_1)
    {
        SII_DBG_PRINT("\t\t\tMHL_STATUS_PATH_ENABLED\n");
        retVal = 1;
    }
    else
    {
        if (0x10 == g_PlumTxConfig.devCapCache.aucDevCapCache[DEVCAP_OFFSET_MHL_VERSION])
        {
            if (0x44 == g_PlumTxConfig.devCapCache.aucDevCapCache[DEVCAP_OFFSET_INT_STAT_SIZE])
            {
                retVal = 1;
                SII_DBG_PRINT("\t\t\tLegacy Support for MHL_STATUS_PATH_ENABLED\n");
            }
        }
    }

    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
// SiiTmdsEnable
//
// Implements conditions on enabling TMDS output stated in MHL spec section 7.6.1
//
//
static void SiiTmdsEnable(void) 
{
    if (MHL_RSEN & g_PlumTxConfig.mhlHpdRSENflags)
    {
        SII_DBG_PRINT("\tMHL_RSEN\n");
        if (MHL_HPD & g_PlumTxConfig.mhlHpdRSENflags)
        {
            SII_DBG_PRINT("\t\tMHL_HPD\n");
            if (QualifyPathEnable())
            {
                if (RAP_CONTENT_ON & g_PlumTxConfig.rapFlags)
                {
                    SII_DBG_PRINT("\t\t\t\tRAP CONTENT_ON\n");
                    SiiDrvTmdsControl( true );                 
                }
            }
        }
    }    
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiSetInt
//
// Set MHL defined INTERRUPT bits in peer's register set.
//
// This function returns true if operation was successfully performed.
//
//  regToWrite      Remote interrupt register to write
//
//  mask            the bits to write to that register
//
//  priority        0:  add to head of CBusQueue
//                  1:  add to tail of CBusQueue
//
static bool SiiSetInt( uint8_t regToWrite, uint8_t mask, uint8_t priorityLevel )
{
    cbus_req_t req;
    bool     retVal;

    // find the offset and bit position
    // and feed
    req.retryCount           = 2;
    req.command              = MHL_SET_INT;
    req.offsetData           = regToWrite;
    req.payload_u.msgData[0] = mask;
    
    if (0 == priorityLevel)
    {
        retVal = PutPriorityCBusTransaction(&req);
    }
    else
    {
        retVal = PutNextCBusTransaction(&req);
    }

    return retVal;
}
#if WRITE_BURST
///////////////////////////////////////////////////////////////////////////////
//
// SiiDoWriteBurst
//
static bool SiiDoWriteBurst( uint8_t startReg, uint8_t *pData, uint8_t length )
{
    if (FLAGS_WRITE_BURST_PENDING & g_PlumTxConfig.miscFlags)
    {
        cbus_req_t req;
        bool retVal;

        SII_DBG_PRINT("MhlTx: startReg:%d length:%d\n", (int)startReg,
                                              (int)length);

        req.retryCount           = 1;
        req.command              = MHL_WRITE_BURST;
        req.length               = length;
        req.offsetData           = startReg;
        req.payload_u.pdatabytes = pData;

        retVal = PutPriorityCBusTransaction(&req);
        ClrMiscFlag(SiiDoWriteBurst, FLAGS_WRITE_BURST_PENDING);
        return retVal;
    }

    return false;
}

/////////////////////////////////////////////////////////////////////////
// SiiRequestWriteBurst
//
static ScratchPadStatus_e SiiRequestWriteBurst(uint8_t startReg, uint8_t length, uint8_t *pData)
{
    ScratchPadStatus_e retVal = SCRATCHPAD_BUSY;

    if (!(MHL_FEATURE_SP_SUPPORT & g_PlumTxConfig.mscFeatureFlag))
    {
        SII_DBG_PRINT("MhlTx: failed SCRATCHPAD_NOT_SUPPORTED\n");

        retVal = SCRATCHPAD_NOT_SUPPORTED;
    }
    else
    {
        if ((FLAGS_SCRATCHPAD_BUSY & g_PlumTxConfig.miscFlags) ||
            SiiMhlTxCBusBusy())
        {
            SII_DBG_PRINT("MhlTx: failed FLAGS_SCRATCHPAD_BUSY \n");
        }
        else
        {
            bool temp;
            uint8_t i, reg;

            SII_DBG_PRINT("MhlTx:, request sent\n");

            for (i = 0, reg = startReg; (i < length) && (reg < SCRATCHPAD_SIZE); ++i, ++reg)
            {
                //g_PlumTxConfig.localScratchPad[reg]=pData[i];  
                pData[i] = pData[i]; //in order to remove the warning
            }

            temp   = SiiSetInt(MHL_RCHANGE_INT, MHL_INT_REQ_WRT, 1);
            retVal = temp ? SCRATCHPAD_SUCCESS : SCRATCHPAD_FAIL;
        }
    }

    return retVal;
}
#endif
///////////////////////////////////////////////////////////////////////////////
// SiiInitialize
//
// Sets the transmitter component firmware up for operation, brings up chip
// into power on state first and then back to reduced-power mode D3 to conserve
// power until an MHL cable connection has been established. If the MHL port is
// used for USB operation, the chip and firmware continue to stay in D3 mode.
// Only a small circuit in the chip observes the impedance variations to see if
// processor should be interrupted to continue MHL discovery process or not.
//
// All device events will result in call to the function SiiDeviceIsr()
// by host's hardware or software(a master interrupt handler in host software
// can call it directly). This implies that the MhlTx component shall make use
// of AppDisableInterrupts() and AppRestoreInterrupts() for any critical section
// work to prevent concurrency issues.
//
void SiiInitialize(void)
{
    SiiMhlTxResetStates();

    SiiChipInitialize();
    
#if USE_HDCP
    SiiHDCP_Init();
#endif

    return;
}

/******************************************************************************
* Function:      sii_mhltx_rcvd_rap
* Description:   Process RAP command received from the peer. 
* Input:         
* Output:        
* Return:        
*******************************************************************************/
static void sii_mhltx_rcvd_rap(void)
{
    IN_FUNCTION;
        
    // RAP is fully handled here.
    // Handle RAP sub-commands here itself
    switch (g_PlumTxConfig.mscMsgData)
    {
        case MHL_RAP_CONTENT_ON:
        {   
            g_PlumTxConfig.rapFlags |= RAP_CONTENT_ON;
            SII_DBG_PRINT("RAP CONTENT_ON\n");
            SiiTmdsEnable();
            SiiRapkSend(MHL_MSC_MSG_RAP_NO_ERROR);
            break;
        }   
        case MHL_RAP_CONTENT_OFF:
        {   
            g_PlumTxConfig.rapFlags &= ~RAP_CONTENT_ON;
            SII_DBG_PRINT("RAP CONTENT_OFF\n");
            SiiDrvTmdsControl( false );
            SiiRapkSend(MHL_MSC_MSG_RAP_NO_ERROR);
            break;
        }   
        case MHL_RAP_CMD_POLL:
        {   
            SiiRapkSend(MHL_MSC_MSG_RAP_NO_ERROR);
            break;
        }   
        default:
        {   
            SiiRapkSend(MHL_MSC_MSG_RAP_UNRECOGNIZED_ACT_CODE);
            break;
        }   
    }

    OUT_FUNCTION;
}

/******************************************************************************
* Function:      sii_mhltx_rcvd_rapk
* Description:   Process RAPK command received from the peer. 
* Input:         
* Output:        
* Return:        
*******************************************************************************/
static void sii_mhltx_rcvd_rapk(void)
{
    IN_FUNCTION;
        
    // Do nothing if RAPK comes, except decrement the reference counter
    DecrementCBusReferenceCount(SiiMhlTxProcessEvents);
    g_PlumTxConfig.mscLastCommand = 0;
    g_PlumTxConfig.mscMsgLastCommand = 0;    

    OUT_FUNCTION;
}

/******************************************************************************
* Function:      sii_mhltx_rcvd_rcpk
* Description:   Process RCPK command received from the peer. 
* Input:         
* Output:        
* Return:        
*******************************************************************************/
static void sii_mhltx_rcvd_rcpk(void)
{
    IN_FUNCTION;
        
    AppNotifyMhlEvent(MHL_TX_EVENT_RCPK_RECEIVED, g_PlumTxConfig.mscMsgData);
    DecrementCBusReferenceCount(SiiMhlTxProcessEvents);
    g_PlumTxConfig.mscLastCommand = 0;
    g_PlumTxConfig.mscMsgLastCommand = 0;

    OUT_FUNCTION;
}

/******************************************************************************
* Function:      sii_mhltx_rcvd_rcpe
* Description:   Process RCPE command received from the peer. 
* Input:         
* Output:        
* Return:        
*******************************************************************************/
static void sii_mhltx_rcvd_rcpe(void)
{
    IN_FUNCTION;
        
    AppNotifyMhlEvent(MHL_TX_EVENT_RCPE_RECEIVED, g_PlumTxConfig.mscMsgData);            

    OUT_FUNCTION;
}

/******************************************************************************
* Function:      sii_mhltx_rcvd_rcp
* Description:   Process RCP command received from the peer. 
* Input:         
* Output:        
* Return:        
*******************************************************************************/
static void sii_mhltx_rcvd_rcp(void)
{
    IN_FUNCTION;
        
    // If we get a RCP key that we do NOT support, send back RCPE
    // Do not notify app layer.
    if (MHL_LOGICAL_DEVICE_MAP & rcpSupportTable[g_PlumTxConfig.mscMsgData & 0x7F])
    {
        AppNotifyMhlEvent(MHL_TX_EVENT_RCP_RECEIVED, g_PlumTxConfig.mscMsgData);
    }
    else
    {
        // Save keycode to send a RCPK after RCPE.
        g_PlumTxConfig.mscSaveRcpKeyCode = g_PlumTxConfig.mscMsgData;     // key code
        SiiRcpeSend( RCPE_INEEFECTIVE_KEY_CODE );
        
        SII_WRN_PRINT("Recved a unsupported keycode: 0x%02x\n", 
                                   g_PlumTxConfig.mscSaveRcpKeyCode);
    }

    OUT_FUNCTION;
}


///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxProcessEvents
//
// This internal function is called at the end of interrupt processing.  It's
// purpose is to process events detected during the interrupt.  Some events are
// internally handled here but most are handled by a notification to the application
// layer.
//
void SiiMhlTxProcessEvents(void) //UT ZHOU
{
    IN_FUNCTION;
        
    // Make sure any events detected during the interrupt are processed.
    SiiMhlTxDriveStates();
    
    if (g_PlumTxConfig.mhlConnectionEvent)
    {
        SII_DBG_PRINT("mhlConnectionEvent is true.\n");

        // Consume the message
        g_PlumTxConfig.mhlConnectionEvent = false;

        // Let app know about the change of the connection state.
        AppNotifyMhlEvent(g_PlumTxConfig.mhlConnected, g_PlumTxConfig.mscFeatureFlag);

        // If connection has been lost, reset all state flags.
        if (MHL_TX_EVENT_DISCONNECTION == g_PlumTxConfig.mhlConnected)
        {
            SiiMhlTxResetStates();
        }
        else if (MHL_TX_EVENT_CONNECTION == g_PlumTxConfig.mhlConnected)
        {
            SiiSetDCapRdy();
        }
    }
    else if (g_PlumTxConfig.mscMsgArrived)
    {
        SII_DBG_PRINT("MSC MSG <0x%02X, 0x%02X>\n", (int) (g_PlumTxConfig.mscMsgSubCommand),
                                           (int) (g_PlumTxConfig.mscMsgData));

        // Consume the message
        g_PlumTxConfig.mscMsgArrived = false;

        // Map sub-command to an event id
        switch (g_PlumTxConfig.mscMsgSubCommand)
        {
            case MHL_MSC_MSG_RAP:
                sii_mhltx_rcvd_rap();
                break;
            case MHL_MSC_MSG_RCP:
                sii_mhltx_rcvd_rcp();
                break;
            case MHL_MSC_MSG_RCPK:
                sii_mhltx_rcvd_rcpk();
                break;
            case MHL_MSC_MSG_RCPE:
                sii_mhltx_rcvd_rcpe();
                break;
            case MHL_MSC_MSG_RAPK:
                sii_mhltx_rcvd_rapk();
                break;
            default:
                // Any freak value here would continue with no event to app
                SII_WRN_PRINT("unrecognized MSC CMD: 0x%02X\n", g_PlumTxConfig.mscMsgSubCommand);
                break;
        }
    }

    OUT_FUNCTION;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxDriveStates
//
// This function is called by the interrupt handler in the driver layer.
// to move the MSC engine to do the next thing before allowing the application
// to run RCP APIs.
//


void SiiMhlTxDriveStates( void ) //UT ZHOU
{
    static unsigned char uFailAccount = 0;

#if USE_PEER_ABORT
    if (mscAbortFlag)
    {
        if (HalTimerExpired(TIMER_ABORT))
        {
            mscAbortFlag = false;
            SII_DBG_PRINT("Timer Tabort_next timeout!\n");
        }
        else
        {
            return;
        }
    }
#endif    

    // process queued CBus transactions
    if (QUEUE_DEPTH(CBusQueue) > 0)
    {
        if (!SiiDrvCBusBusy())
        {
            int reQueueRequest = 0;
            cbus_req_t *pReq = GetNextCBusTransaction(SiiMhlTxDriveStates);
            if(NULL == pReq)
            {
                SII_DBG_PRINT("GetNextCBusTransaction NULL\n");
                return;
            }

            uFailAccount = 0;

            // coordinate write burst requests and grants.
            if (MHL_SET_INT == pReq->command)
            {
                if (MHL_RCHANGE_INT == pReq->offsetData)
                {
                    if (FLAGS_SCRATCHPAD_BUSY & g_PlumTxConfig.miscFlags)
                    {
                        if (MHL_INT_REQ_WRT == pReq->payload_u.msgData[0])
                        {
                            reQueueRequest = 1;
                        }
                        else if (MHL_INT_GRT_WRT == pReq->payload_u.msgData[0])
                        {
                            reQueueRequest = 0;
                        }
                    }
                    else
                    {
                        if (MHL_INT_REQ_WRT == pReq->payload_u.msgData[0])
                        {
                            IncrementCBusReferenceCount(SiiMhlTxDriveStates);
                            SetMiscFlag(SiiMhlTxDriveStates, FLAGS_SCRATCHPAD_BUSY);
                            SetMiscFlag(SiiMhlTxDriveStates, FLAGS_WRITE_BURST_PENDING);
                        }
                        else if (MHL_INT_GRT_WRT == pReq->payload_u.msgData[0])
                        {
                            SetMiscFlag(SiiMhlTxDriveStates, FLAGS_SCRATCHPAD_BUSY);
                        }
                    }
                }
            }

            if (reQueueRequest)
            {
                // send this one to the back of the line for later attempts
                if (pReq->retryCount-- > 0)
                {
                    PutNextCBusTransaction(pReq);
                }
            }
            else
            {
                if (MHL_MSC_MSG == pReq->command)
                {
                    g_PlumTxConfig.mscMsgLastCommand = pReq->payload_u.msgData[0];
                    g_PlumTxConfig.mscMsgLastData = pReq->payload_u.msgData[1];
                }
                else
                {
                    g_PlumTxConfig.mscLastOffset = pReq->offsetData;
                    g_PlumTxConfig.mscLastData = pReq->payload_u.msgData[0];
                }

                g_PlumTxConfig.mscLastCommand = pReq->command;

                IncrementCBusReferenceCount(SiiMhlTxDriveStates);
                SiiDrvSendCbusCommand( pReq  );
            }
        }
        else
        {
            uFailAccount++;
            SII_DBG_PRINT("SiiDrvCBusBusy\n");

            if (uFailAccount > 50) //If Send one Command more than 50 times, cancel sending
            {
                g_PlumTxConfig.mscCmdInProgress = false;
                DecrementCBusReferenceCount(SiiMhlTxDriveStates);

                SII_DBG_PRINT("SiiMhlTxDriveStates Cancel sending.\n");
            }
        }
    }
}

static void ExamineLocalAndPeerVidLinkMode( void )
{
    // set default values
    g_PlumTxConfig.linkMode &= ~MHL_STATUS_CLK_MODE_MASK;
    g_PlumTxConfig.linkMode |= MHL_STATUS_CLK_MODE_NORMAL;

    // when more modes than PPIXEL and normal are supported,
    //   this should become a table lookup.
    if (PackedPixelAvailable) {
        g_PlumTxConfig.linkMode &= ~MHL_STATUS_CLK_MODE_MASK;
        g_PlumTxConfig.linkMode |= g_PlumTxConfig.preferredClkMode;
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiMscCommandDone
//
// This function is called by the driver to inform of completion of last command.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
#define FLAG_OR_NOT(x) (FLAGS_HAVE_ ## x & g_PlumTxConfig.miscFlags) ? # x : ""
#define SENT_OR_NOT(x) (FLAGS_SENT_ ## x & g_PlumTxConfig.miscFlags) ? # x : ""

void    SiiMscCommandDone( uint8_t data1 ) //UT ZHOU
{
    SII_DBG_PRINT("MhlTx:SiiMscCommandDone. data1 = 0x%02X\n", (int) data1);
    DecrementCBusReferenceCount(SiiMscCommandDone)
    if (MHL_READ_DEVCAP == g_PlumTxConfig.mscLastCommand)
    {
        if (g_PlumTxConfig.mscLastOffset < DEVCAP_SIZE)
        {
            // populate the cache
            g_PlumTxConfig.devCapCache.aucDevCapCache[g_PlumTxConfig.mscLastOffset] = data1;
            SII_DBG_PRINT("MhlTx:SiiMscCommandDone peer DEV_CAP[0x%02x]:0x%02x index:0x%02x\n",
                             (int)g_PlumTxConfig.mscLastOffset, (int)data1,
                             (int)g_PlumTxConfig.devCapCache.ucDevCapCacheIndex);

            if (MHL_DEV_CATEGORY_OFFSET == g_PlumTxConfig.mscLastOffset)
            {
                uint8_t param;
                g_PlumTxConfig.miscFlags |= FLAGS_HAVE_DEV_CATEGORY;
                param = data1 & MHL_DEV_CATEGORY_POW_BIT;

                SII_DBG_PRINT("MhlTx:SiiMscCommandDone FLAGS_HAVE_DEV_CATEGORY\n");
                // Give the OEM a chance at handling power for himself
                if (MHL_TX_EVENT_STATUS_PASSTHROUGH == AppNotifyMhlEvent(MHL_TX_EVENT_POW_BIT_CHG, param))
                {
                    SiiDrvPowBitChange((bool)param );
                }
            }
            else if (MHL_DEV_FEATURE_FLAG_OFFSET == g_PlumTxConfig.mscLastOffset)
            {
                g_PlumTxConfig.miscFlags |= FLAGS_HAVE_DEV_FEATURE_FLAGS;
                SII_DBG_PRINT("MhlTx:SiiMscCommandDone FLAGS_HAVE_DEV_FEATURE_FLAGS\n");

                // Remember features of the peer
                g_PlumTxConfig.mscFeatureFlag = data1;
                SII_DBG_PRINT("MhlTx: Peer's Feature Flag = 0x%02X\n\n", (int) data1);
            }
            else if (DEVCAP_OFFSET_VID_LINK_MODE == g_PlumTxConfig.mscLastOffset)
            {
                ExamineLocalAndPeerVidLinkMode();
            }

            if (++g_PlumTxConfig.devCapCache.ucDevCapCacheIndex < DEVCAP_SIZE)
            {
                // OK to call this here, since requests always get queued and processed in the "foreground"
                SiiReadDevcap( g_PlumTxConfig.devCapCache.ucDevCapCacheIndex );
            }
            else
            {
                // this is necessary for both firmware and linux driver.
                AppNotifyMhlEvent(MHL_TX_EVENT_DCAP_CHG, 0);

                // see MHL spec section 5.9.1
                if (MHL_HPD & g_PlumTxConfig.mhlHpdRSENflags)
                {
                    SII_DBG_PRINT("HPD\n");
#if USE_3D
                    SiiSend3DReq();
#endif
                }
                else
                {
                    SII_DBG_PRINT("no HPD\n");
                }
                // These variables are used to remember if we issued a READ_DEVCAP
                //    or other MSC command
                // Since we are done, reset them.
                g_PlumTxConfig.mscLastCommand = 0;
                g_PlumTxConfig.mscLastOffset = 0;
            }
        }
    }
    else if (MHL_WRITE_STAT == g_PlumTxConfig.mscLastCommand)
    {
        SII_DBG_PRINT("MhlTx: WRITE_STAT miscFlags: 0x%02X\n\n", (int) g_PlumTxConfig.miscFlags);

        if (MHL_STATUS_REG_CONNECTED_RDY == g_PlumTxConfig.mscLastOffset)
        {
            if (MHL_STATUS_DCAP_RDY & g_PlumTxConfig.mscLastData)
            {
                g_PlumTxConfig.miscFlags |= FLAGS_SENT_DCAP_RDY;
                SII_DBG_PRINT("MhlTx:SiiMscCommandDone FLAGS_SENT_DCAP_RDY\n");

                SiiSetInt(MHL_RCHANGE_INT, MHL_INT_DCAP_CHG, 0);        // priority request
            }
        }
        else if (MHL_STATUS_REG_LINK_MODE == g_PlumTxConfig.mscLastOffset)
        {
            if (MHL_STATUS_PATH_ENABLED & g_PlumTxConfig.mscLastData)
            {
                g_PlumTxConfig.miscFlags |= FLAGS_SENT_PATH_EN;
                SII_DBG_PRINT("MhlTx:SiiMscCommandDone FLAGS_SENT_PATH_EN\n");
            }
        }

        g_PlumTxConfig.mscLastCommand = 0;
        g_PlumTxConfig.mscLastOffset = 0;
    }
    else if (MHL_MSC_MSG == g_PlumTxConfig.mscLastCommand)
    {
        if (MHL_MSC_MSG_RCPE == g_PlumTxConfig.mscMsgLastCommand)
        {
            //
            // RCPE is always followed by an RCPK with original key code that came.
            //
            if (SiiRcpkSend( g_PlumTxConfig.mscSaveRcpKeyCode ))
            {
            }
        }
        else
        {
            SII_DBG_PRINT("MhlTx:SiiMscCommandDone default\n"
                                      "\tmscLastCommand: 0x%02X \n"
                                      "\tmscMsgLastCommand: 0x%02X mscMsgLastData: 0x%02X\n"
                                      "\tcbusReferenceCount: %d\n",
                                      (int)g_PlumTxConfig.mscLastCommand,
                                      (int)g_PlumTxConfig.mscMsgLastCommand,
                                      (int)g_PlumTxConfig.mscMsgLastData,
                                      (int)g_PlumTxConfig.cbusReferenceCount
                            );
        }

        g_PlumTxConfig.mscLastCommand = 0;
    }
    else if (MHL_WRITE_BURST == g_PlumTxConfig.mscLastCommand)
    {
        SII_DBG_PRINT("MhlTx:SiiMscCommandDone MHL_WRITE_BURST\n");

        g_PlumTxConfig.mscLastCommand = 0;
        g_PlumTxConfig.mscLastOffset = 0;
        g_PlumTxConfig.mscLastData = 0;

        // all CBus request are queued, so this is OK to call here
        // use priority 0 so that other queued commands don't interfere
        SiiSetInt( MHL_RCHANGE_INT, MHL_INT_DSCR_CHG, 0 );
    }
    else if (MHL_SET_INT == g_PlumTxConfig.mscLastCommand)
    {
        SII_DBG_PRINT("MhlTx:SiiMscCommandDone MHL_SET_INT\n");
        
        switch (g_PlumTxConfig.mscLastOffset)
        {
            case MHL_RCHANGE_INT:
                SII_DBG_PRINT("MhlTx:SiiMscCommandDone MHL_RCHANGE_INT\n");
                switch (g_PlumTxConfig.mscLastData)
	            {
                  case MHL_INT_DCAP_CHG:
                      SII_DBG_PRINT("MhlTx:SiiMscCommandDone DCAP_CHG sent successfully.\n");
                      break;
	              case MHL_INT_DSCR_CHG:
	                  SII_DBG_PRINT("MhlTx:SiiMscCommandDone DSCR_CHG sent successfully.\n");
	                   //ClrMiscFlag(SiiMscCommandDone, FLAGS_SCRATCHPAD_BUSY);
	                  break;
	              case MHL_INT_REQ_WRT:
	                  SII_DBG_PRINT("MhlTx:SiiMscCommandDone REQ_WRT sent successfully.\n");
	                  break;
	              case MHL_INT_GRT_WRT:
	                  SII_DBG_PRINT("MhlTx:SiiMscCommandDone GRT_WRT sent successfully.\n");
	                  break;
	              case MHL2_INT_3D_REQ:
	                  //3D_REQ is sent successfully.
	                  SII_DBG_PRINT("MhlTx:SiiMscCommandDone 3D_REQ sent successfully.\n");
	                  break;
                  default:
			          SII_WRN_PRINT("MhlTx: MHL_RCHANGE_INT invalid mscLastOffset.\n");
			          break;
	            }
                break;
            case MHL_DCHANGE_INT:
		        SII_DBG_PRINT("MhlTx:SiiMscCommandDone MHL_DCHANGE_INT.\n");
                break;
	        default:
		        SII_WRN_PRINT("MhlTx: not  MHL_DCHANGE_INT & MHL_RCHANGE_INT.\n");
		        break;
        }
        
        // Once the command has been sent out successfully, forget this case.
        g_PlumTxConfig.mscLastCommand = 0;
        g_PlumTxConfig.mscLastOffset = 0;
        g_PlumTxConfig.mscLastData = 0;
    }
    else
    {
        /*
        SII_DBG_PRINT("MhlTx:SiiMscCommandDone default\n"
                                              "\tmscLastCommand: 0x%02X mscLastOffset: 0x%02X\n"
                                              "\tcbusReferenceCount: %d\n",
                                              (int)g_PlumTxConfig.mscLastCommand,
                                              (int)g_PlumTxConfig.mscLastOffset,
                                              (int)g_PlumTxConfig.cbusReferenceCount
                        );
        */
    }

    if (!(FLAGS_RCP_READY & g_PlumTxConfig.miscFlags))
    {
        /*
        SII_DBG_PRINT("MhlTx:SiiMscCommandDone. have(%s %s) sent(%s %s)\n",
                                              FLAG_OR_NOT(DEV_CATEGORY),
                                              FLAG_OR_NOT(DEV_FEATURE_FLAGS),
                                              SENT_OR_NOT(PATH_EN),
                                              SENT_OR_NOT(DCAP_RDY)
                        );
        */
        
        if (FLAGS_HAVE_DEV_CATEGORY & g_PlumTxConfig.miscFlags)
        {
            if (FLAGS_HAVE_DEV_FEATURE_FLAGS & g_PlumTxConfig.miscFlags)
            {
                if (FLAGS_SENT_PATH_EN & g_PlumTxConfig.miscFlags)
                {
                    if (FLAGS_SENT_DCAP_RDY & g_PlumTxConfig.miscFlags)
                    {
                        if (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex >= DEVCAP_SIZE)
                        {
                            g_PlumTxConfig.miscFlags |= FLAGS_RCP_READY;

                            // Now we can entertain App commands for RCP
                            // Let app know this state
                            g_PlumTxConfig.mhlConnectionEvent = true;
                            g_PlumTxConfig.mhlConnected = MHL_TX_EVENT_RCP_READY;
                            /* If notify here, it will be called twice in SiiMhlTxProcessEvents () */
                            //AppNotifyMhlEvent(g_PlumTxConfig.mhlConnected, 0);           //send event to up-level;
                        }
                    }
                }
            }
        }
    }
}

uint8_t QualifyPixelClockForMhl(uint32_t pixelClockFrequency, uint8_t bitsPerPixel)
{
    uint32_t pixelClockFrequencyDiv8;
    uint32_t linkClockFrequency;
    uint32_t maxLinkClockFrequency;
    uint8_t retVal;

    pixelClockFrequencyDiv8 = pixelClockFrequency / 8;

    linkClockFrequency = pixelClockFrequencyDiv8 * (uint32_t)bitsPerPixel;

    if (PackedPixelAvailable)
    {
        maxLinkClockFrequency = 300000000;
    }
    else
    {
        maxLinkClockFrequency = 225000000;
    }

    if (linkClockFrequency < maxLinkClockFrequency)
    {
        retVal = 1;
    }
    else
    {
        retVal = 0;
    }
    
    SII_DBG_PRINT("Link clock:%u Hz %12s for MHL at %d bpp (max: %u Hz)\n",
                                          linkClockFrequency,
                                          retVal ? "valid" : "unattainable",
                                          (uint16_t)bitsPerPixel,
                                          maxLinkClockFrequency);
    return retVal;
}

uint32_t CalculatePixelClock(uint16_t columns, uint16_t rows, uint32_t verticalSyncFrequencyInMilliHz, uint8_t VIC) //UT ZHOU
{
    uint32_t pixelClockFrequency;
    uint32_t verticalSyncPeriodInMicroSeconds, verticalActivePeriodInMicroSeconds, verticalBlankPeriodInMicroSeconds;
    uint32_t horizontalSyncFrequencyInHundredthsOfKHz, horizontalSyncPeriodInNanoSeconds,
             horizontalActivePeriodInNanoSeconds, horizontalBlankPeriodInNanoSeconds;
    //SII_DBG_PRINT("verticalSyncFrequencyInMilliHz: %lu\n", verticalSyncFrequencyInMilliHz);  
    verticalSyncPeriodInMicroSeconds = 1000000000 / verticalSyncFrequencyInMilliHz;
    //SII_DBG_PRINT("verticalSyncFrequencyInMilliHz:%lu verticalSyncPeriodInMicroSeconds: %lu\n",
    //                                      verticalSyncFrequencyInMilliHz, verticalSyncPeriodInMicroSeconds);        
    if (0 == VIC)
    {
        // rule of thumb:
        verticalActivePeriodInMicroSeconds = (verticalSyncPeriodInMicroSeconds * 8) / 10;
    }
    else
    {
        uint16_t vTotalInPixels;
        uint16_t vBlankInPixels;

        if (vsmInterlaced == vicInfo[VIC].fields.interlaced)
        {
            vBlankInPixels = 2 * vicInfo[VIC].VBlankInPixels + vicInfo[VIC].fields.field2VBlank;
        }
        else
        {
            // when multiple vertical blanking values present,
            //  allow for higher clocks by calculating maximum possible
            vBlankInPixels = vicInfo[VIC].VBlankInPixels + vicInfo[VIC].fields.field2VBlank;
        }

        vTotalInPixels = vicInfo[VIC].rows + vBlankInPixels;
        verticalActivePeriodInMicroSeconds = (verticalSyncPeriodInMicroSeconds * vicInfo[VIC].rows) / vTotalInPixels;
    }

    //SII_DBG_PRINT("verticalActivePeriodInMicroSeconds: %lu\n",
    //                                      verticalActivePeriodInMicroSeconds);                                           
    // rigorous calculation:
    verticalBlankPeriodInMicroSeconds = verticalSyncPeriodInMicroSeconds - verticalActivePeriodInMicroSeconds;

    //SII_DBG_PRINT("verticalBlankPeriodInMicroSeconds: %lu\n", verticalBlankPeriodInMicroSeconds); 
    horizontalSyncFrequencyInHundredthsOfKHz  = rows * 100000;
    horizontalSyncFrequencyInHundredthsOfKHz /= verticalActivePeriodInMicroSeconds;

    //SII_DBG_PRINT("horizontalSyncFrequencyInHundredthsOfKHz: %lu\n",
    //                                      horizontalSyncFrequencyInHundredthsOfKHz);                                               
    horizontalSyncPeriodInNanoSeconds = 100000000 / horizontalSyncFrequencyInHundredthsOfKHz;

    //SII_DBG_PRINT("horizontalSyncPeriodInNanoSeconds: %lu\n", horizontalSyncPeriodInNanoSeconds); 
    if (0 == VIC)
    {
        // rule of thumb:
        horizontalActivePeriodInNanoSeconds = (horizontalSyncPeriodInNanoSeconds * 8) / 10;

        //SII_DBG_PRINT("horizontalActivePeriodInNanoSeconds: %lu\n",
        //                                      horizontalActivePeriodInNanoSeconds);                                         
    }
    else
    {
        uint16_t hTotalInPixels;
        uint16_t hClocks;
        hClocks = vicInfo[VIC].columns << vicInfo[VIC].fields.clocksPerPixelShiftCount;
        hTotalInPixels = hClocks + vicInfo[VIC].HBlankInPixels;
        horizontalActivePeriodInNanoSeconds = (horizontalSyncPeriodInNanoSeconds * hClocks) / hTotalInPixels;
    }

    // rigorous calculation:
    horizontalBlankPeriodInNanoSeconds = horizontalSyncPeriodInNanoSeconds - horizontalActivePeriodInNanoSeconds;

    //SII_DBG_PRINT("horizontalBlankPeriodInNanoSeconds: %lu\n",
    //                                      horizontalBlankPeriodInNanoSeconds);                                            

    pixelClockFrequency = columns * (1000000000 / horizontalActivePeriodInNanoSeconds);

    //SII_DBG_PRINT("pixelClockFrequency: %lu\n", pixelClockFrequencys); 

    return pixelClockFrequency;
}

#if USE_3D
/*
  IsMhlTimingMode

    MHL has a maximum link clock of 75Mhz.
    For now, we use a rule of thumb regarding
        blanking intervals to calculate a pixel clock,
        then we convert it to a link clock and compare to 75MHz

 */

static uint8_t IsMhlTimingMode(uint16_t columns, uint16_t rows, uint32_t verticalSyncFrequencyInMilliHz,
                               PMhl2VideoDescriptor_t pMhl2VideoDescriptorParm,
                               uint8_t VIC)
{
    uint32_t pixelClockFrequency;
    uint8_t retVal = 0;
    Mhl2VideoDescriptor_t dummy;
    PMhl2VideoDescriptor_t pMhl2VideoDescriptor = pMhl2VideoDescriptorParm;

    if (NULL == pMhl2VideoDescriptorParm)
    {
        dummy.FrameSequential = 0;
        dummy.LeftRight = 0;
        dummy.TopBottom = 0;
        dummy.reservedHigh = 0;
        dummy.reservedLow = 0;
        pMhl2VideoDescriptor = &dummy;
    }

    pixelClockFrequency = CalculatePixelClock(columns, rows, verticalSyncFrequencyInMilliHz, VIC);

    if (QualifyPixelClockForMhl(pixelClockFrequency, 24))
    {
        //AppDisplayTimingEnumerationCallBack(columns, rows, 24, verticalSyncFrequencyInMilliHz, *pMhl2VideoDescriptor);
        retVal = 1;
    }

    if (QualifyPixelClockForMhl(pixelClockFrequency, 16))
    {
        //AppDisplayTimingEnumerationCallBack(columns, rows, 16, verticalSyncFrequencyInMilliHz, *pMhl2VideoDescriptor);
        retVal = 1;
    }

    return retVal;
}

/*
 */
static uint8_t IsQualifiedMhlVIC(uint8_t VIC, PMhl2VideoDescriptor_t pMhlVideoDescriptor)
{
    uint8_t retVal = 0;

    if (VIC > 0)
    {
        retVal = IsMhlTimingMode(vicInfo[VIC].columns, vicInfo[VIC].rows, vicInfo[VIC].fieldRateInMilliHz,
                                 pMhlVideoDescriptor, VIC);
        if (vifDualFrameRate == vicInfo[VIC].fields.frameRateInfo)
        {
            uint32_t fieldRateInMilliHz;
            switch (vicInfo[VIC].fieldRateInMilliHz)
            {
            case 24000: //23.97
                fieldRateInMilliHz = 23970;
                break;

            case 30000: //
                fieldRateInMilliHz = 29970;
                break;

            case 60000: //
                fieldRateInMilliHz = 59940;
                break;

            case 120000: //
                fieldRateInMilliHz = 119880;
                break;

            case 240000: //
                fieldRateInMilliHz = 239760;
                break;

            default: //error or unknown case
                fieldRateInMilliHz = 0;
            }

            retVal |= IsMhlTimingMode(vicInfo[VIC].columns, vicInfo[VIC].rows, fieldRateInMilliHz, pMhlVideoDescriptor,
                                      VIC);
        }
    }

    return retVal;
}

void SiiPruneDTDList(P_18ByteDescriptor_u pDesc, uint8_t limit)
{
    uint8_t i;
    uint8_t numberThatWePruned = 0;

    for (i = 0; i < limit - 1; ++i)
    {
        if ((0 != pDesc->dtd.pixelClockLow) || (0 != pDesc->dtd.pixelClockHigh))
        {
            if ((0 == pDesc->dtd.horzActive7_0) && (0 == pDesc->dtd.horzActiveBlankingHigh.horzActive11_8))
            {
                P_18ByteDescriptor_u pHolder = pDesc, pNextDesc = pDesc + 1;
                uint8_t j;
                numberThatWePruned++;
                for (j = i + 1; j < limit; ++j)
                {
                    // move the rest of the entries one by one
                    *pDesc++ = *pNextDesc++;
                }

                // re-consider the new occupant of the i'th entry on the next iteration
                i--; // i is unsigned
                pDesc = pHolder;
            }
        }
    }

    // at this point "i" holds the value of g_PlumTxConfig.svdDataBlockLength-1
    //  and pDesc points to the last entry in the list
    for (; numberThatWePruned > 0; --numberThatWePruned, --pDesc)
    {
        uint8_t *pu8Temp = (uint8_t *)pDesc;
        uint8_t size;

        for (size = sizeof(*pDesc); size > 0; --size)
        {
            *pu8Temp-- = 0;
        }
    }
}

void SiiPruneEDID(void) 
{
    PEDID_Block0_t pEdidBlock0 = (PEDID_Block0_t)&g_PlumTxConfig.EDID.edidBlockData[0];
    uint8_t dtdLimit;
    PCeaExtension_t pCeaExtension = (PCeaExtension_t)&g_PlumTxConfig.EDID.edidBlockData[EDID_BLOCK_SIZE];
    uint8_t *pbLimit = (uint8_t *)(pCeaExtension + 1);

    union
    {
        uint8_t *            pucDataBlock;
        P_18ByteDescriptor_u pLongDescriptors;
    } pData_u;

    SII_DBG_PRINT("MhlTx: SiiPruneEDID\n");
    pData_u.pucDataBlock = (uint8_t *)pCeaExtension + pCeaExtension->byteOffsetTo18ByteDescriptors;

    //DumpEdidBlock(pEdidBlock0,sizeof(*pEdidBlock0))  // no semicolon needed here
    // zero out checksums before modifying data
    pCeaExtension->checkSum = 0;
    pEdidBlock0->checkSum = 0;

    // Is there an HDMI VSDB?
    if (g_PlumTxConfig.pHdmiVendorSpecificDataBlock)
    {
        PHdmiLLCVendorSpecificDataBlockPayload_t pHdmiVendorSpecificPayload =
            &g_PlumTxConfig.pHdmiVendorSpecificDataBlock->payload_u.HdmiLLC;
        uint8_t *pNextDB = (uint8_t *)pHdmiVendorSpecificPayload
                           + g_PlumTxConfig.pHdmiVendorSpecificDataBlock->header.lengthFollowingHeader;

        // if deep color information is provided...
        if (((uint8_t *)&pHdmiVendorSpecificPayload->byte6) < pNextDB)
        {
            pHdmiVendorSpecificPayload->byte6.DC_Y444  = 0;
            pHdmiVendorSpecificPayload->byte6.DC_30bit = 0;
            pHdmiVendorSpecificPayload->byte6.DC_36bit = 0;
            pHdmiVendorSpecificPayload->byte6.DC_48bit = 0;
        }
    }

    // prune the DTDs in block 0
    dtdLimit = sizeof(pEdidBlock0->detailedTimingDescriptors) / sizeof(pEdidBlock0->detailedTimingDescriptors[0]);
    SiiPruneDTDList((P_18ByteDescriptor_u) & pEdidBlock0->detailedTimingDescriptors[0], dtdLimit);

    //DumpEdidBlock(pEdidBlock0,sizeof(*pEdidBlock0))  // no semicolon needed here

    //DumpEdidBlock(pCeaExtension,sizeof(*pCeaExtension))  // no semicolon needed here
    // prune the DTDs in the CEA-861D extension
    dtdLimit = (uint8_t)pCeaExtension->version_u.version3.miscSupport.totalNumberDetailedTimingDescriptorsInEntireEDID;
    SiiPruneDTDList(&pData_u.pLongDescriptors[0], dtdLimit);

    // adjust the mask according to which 2D VICs were set to zero
    if (g_PlumTxConfig.p3DMask)
    {
        uint8_t lowerMask;
        uint32_t mask32;
        uint8_t index = g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader - 1;
        index = (index > 15) ? 15 : index;

        mask32 = 0xFFFF00 >> (15 - index);
        lowerMask = (index > 7) ? 0x7F : (0x7F >> (7 - index));

        SII_DBG_PRINT("3d mask 15..8: 0x%02x", (uint16_t)g_PlumTxConfig.p3DMask->_3D_Mask_15_8);
        for (
            ; index >= 8
            ; mask32 >>= 1, lowerMask >>= 1, --index)
        {
            if (0 == g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC)
            {
                uint8_t lowerBits, upperBits;
                uint8_t upperMask;
                upperMask = (uint8_t)mask32;

                // preserve the lower bits
                lowerBits = lowerMask & g_PlumTxConfig.p3DMask->_3D_Mask_15_8;

                // and out the bit in question
                upperBits = upperMask & g_PlumTxConfig.p3DMask->_3D_Mask_15_8;

                // adjust the positions of the upper bits
                upperBits >>= 1;

                g_PlumTxConfig.p3DMask->_3D_Mask_15_8 = lowerBits | upperBits;
                SII_DBG_PRINT("3d mask 15..8: 0x%02x",
                                                      (uint16_t)g_PlumTxConfig.p3DMask->_3D_Mask_15_8);
            }
        }

        SII_DBG_PRINT("3d mask 7..0: 0x%02x", (uint16_t)g_PlumTxConfig.p3DMask->_3D_Mask_7_0);
        lowerMask = 0x7F >> (7 - index);
        for (
            ; index >= 0 //index >= 0 is always true 
            ; mask32 >>= 1, lowerMask >>= 1, --index)
        {
            if (0 == g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC)
            {
                uint8_t lowerBits, upperBits;
                uint8_t upperMask;
                upperMask = (uint8_t)mask32;

                // preserve the lower bits
                lowerBits = lowerMask & g_PlumTxConfig.p3DMask->_3D_Mask_7_0;

                // and out the bit in question
                upperBits = upperMask & g_PlumTxConfig.p3DMask->_3D_Mask_7_0;

                // adjust the positions of the upper bits
                upperBits >>= 1;

                g_PlumTxConfig.p3DMask->_3D_Mask_7_0 = lowerBits | upperBits;
                SII_DBG_PRINT("3d mask 7..0: 0x%02x",
                                                      (uint16_t)g_PlumTxConfig.p3DMask->_3D_Mask_7_0);
            }
        }
    }

    if (g_PlumTxConfig.pThreeD)
    {
        uint8_t num3DStructureBytesPruned = 0;
        union
        {
            P_3DStructureAndDetailEntry_u            pThreeD;
            P_3DStructureAndDetailEntrySansByte1_t   pSansByte1;
            P_3DStructureAndDetailEntryWithByte1_t   pWithByte1;
            uint8_t                                 *pAsBytes;
        } pThreeD_u;
        uint8_t indexAdjustment = 0;
        pThreeD_u.pThreeD = g_PlumTxConfig.pThreeD;
        while (pThreeD_u.pAsBytes < g_PlumTxConfig.p3DLimit)
        {
            uint8_t _2D_VIC_order = pThreeD_u.pSansByte1->byte0._2D_VIC_order;
            ThreeDStructure_e _3D_Structure = pThreeD_u.pSansByte1->byte0._3D_Structure;
            uint8_t VIC;
            VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[_2D_VIC_order].VIC;
            if (0 == VIC)
            {
                // delete this 3D_Structure/3D_Detail information
                uint8_t *pSrc, *pDest = pThreeD_u.pAsBytes;

                SII_DBG_PRINT("2D vic order: 0x%02x indexAdjustment:0x%02x",
                                                      (uint16_t)pThreeD_u.pSansByte1->byte0._2D_VIC_order,
                                                      (uint16_t)indexAdjustment);
                pThreeD_u.pSansByte1->byte0._2D_VIC_order -= ++indexAdjustment;
                SII_DBG_PRINT("2D vic order: 0x%02x indexAdjustment:0x%02x",
                                                      (uint16_t)pThreeD_u.pSansByte1->byte0._2D_VIC_order,
                                                      (uint16_t)indexAdjustment);
                if (_3D_Structure < tdsSideBySide)
                {
                    pSrc = (uint8_t *)(pThreeD_u.pSansByte1 + 1);
                }
                else
                {
                    pSrc = (uint8_t *)(pThreeD_u.pWithByte1 + 1);
                }

                while (pSrc < pbLimit)
                {
                    num3DStructureBytesPruned++;
                    *pDest++ = *pSrc++;
                }

                while (pDest < pbLimit)
                {
                    *pDest = 0;
                }
            }
            else
            {
                if (_3D_Structure < tdsSideBySide)
                {
                    pThreeD_u.pSansByte1++;
                }
                else
                {
                    pThreeD_u.pWithByte1++;
                }
            }
        }

        g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_3D_LEN -= num3DStructureBytesPruned;
        pCeaExtension->byteOffsetTo18ByteDescriptors -= num3DStructureBytesPruned;
        g_PlumTxConfig.pHdmiVendorSpecificDataBlock->header.lengthFollowingHeader -= num3DStructureBytesPruned;
    }

    // now prune the HDMI VSDB VIC list
    if (g_PlumTxConfig.pByte13ThroughByte15)
    {
        uint8_t lengthVIC = g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_VIC_LEN;

        if (0 == lengthVIC)
        {
            SII_DBG_PRINT("lengthVIC:%d \n", (uint16_t)lengthVIC);
        }
        else
        {
            uint8_t i, numHdmiVicsPruned = 0;
            uint8_t innerLoopLimit;
            uint8_t outerLoopLimit;
            innerLoopLimit = lengthVIC;
            outerLoopLimit = lengthVIC - 1;
            SII_DBG_PRINT("lengthVIC:%d innerLoopLimit: %d outerLoopLimit: %d \n",
                                                  (uint16_t)lengthVIC, (uint16_t)innerLoopLimit,
                                                  (uint16_t)outerLoopLimit);
            for (i = 0; i < outerLoopLimit;)
            {
                if (0 == g_PlumTxConfig.pByte13ThroughByte15->vicList[i])
                {
                    uint8_t j, prev;
                    for (prev = i, j = i + 1; j < innerLoopLimit; ++j, ++prev)
                    {
                        uint16_t VIC0, VIC1;

                        VIC0 = g_PlumTxConfig.pByte13ThroughByte15->vicList[prev];
                        VIC1 = g_PlumTxConfig.pByte13ThroughByte15->vicList[j];
                        SII_DBG_PRINT("replacing VIC: %3d at index: %3d with VIC:%3d from index: %3d \n",
                                         VIC0,
                                         (uint16_t)prev,
                                         VIC1,
                                         (uint16_t)j
                                        );
                        g_PlumTxConfig.pByte13ThroughByte15->vicList[prev]
                        = g_PlumTxConfig.pByte13ThroughByte15->vicList[j];
                    }

                    // we just removed one
                    numHdmiVicsPruned++;
                    innerLoopLimit--;
                    outerLoopLimit--;
                }
                else
                {
                    // this mode is doable on MHL, so move on to the next index
                    ++i;
                }
            }

            // check the last one
            if (0 == g_PlumTxConfig.pByte13ThroughByte15->vicList[outerLoopLimit])
            {
                numHdmiVicsPruned++;
            }

            //DumpEdidBlock(pCeaExtension,sizeof(*pCeaExtension))  // no semicolon needed here
            //now move all other data up
            if (numHdmiVicsPruned)
            {
                uint8_t *pbDest = (uint8_t *)&g_PlumTxConfig.pByte13ThroughByte15->vicList[innerLoopLimit];
                uint8_t *pbSrc = (uint8_t *)&g_PlumTxConfig.pByte13ThroughByte15->vicList[lengthVIC];

				if(EDID_BLOCK_SIZE != sizeof(*pCeaExtension))
				{
					
					SII_DBG_PRINT("\n\n unexpected extension size\n\n");
				}
				
                while (pbSrc < pbLimit)
                {
                    SII_DBG_PRINT("moving data up 0x%X(0x%02x) <- 0x%X(0x%02x)\n", (uint32_t)pbDest,
                                                          (uint8_t)*pbDest, (uint32_t)pbSrc, (uint8_t)*pbSrc);
                    *pbDest++ = *pbSrc++;
                }

                while (pbDest < pbLimit)
                {
                    SII_DBG_PRINT("clearing data 0x%X <- 0\n", (uint32_t)pbDest);
                    *pbDest++ = 0;
                }
            }

            g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_VIC_LEN = innerLoopLimit;
            pCeaExtension->byteOffsetTo18ByteDescriptors -= numHdmiVicsPruned;
            g_PlumTxConfig.pHdmiVendorSpecificDataBlock->header.lengthFollowingHeader -= numHdmiVicsPruned;
        }
    }

    // Now prune the SVD list and move the CEA 861-D data blocks and DTDs up
    {
        uint8_t i, numCeaVicsPruned = 0;

        //#ifdef ENABLE_TX_PRUNE_PRINT //(
        char *pszNative = "Native";
        char *pszNonNative = "";
        //#endif //)
        uint8_t innerLoopLimit = g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader;
        uint8_t outerLoopLimit = innerLoopLimit - 1;
        for (i = 0; i < outerLoopLimit;)
        {
            if (0 == g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[i].VIC)
            {
                uint8_t j, prev;
                numCeaVicsPruned++;
                for (prev = i, j = i + 1; j < innerLoopLimit; ++j, ++prev)
                {
                    uint16_t VIC0, VIC1;

                    VIC0 = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[prev].VIC;
                    VIC1 = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[j].VIC;
                    SII_DBG_PRINT("replacing SVD:%6s %3d at index: %3d with SVD:%6s %3d from index: %3d \n",
                                     g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[prev].native ? pszNative : pszNonNative,
                                     VIC0,
                                     (uint16_t)prev,
                                     g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[j].native ? pszNative : pszNonNative,
                                     VIC1,
                                     (uint16_t)j
                                    );
                    g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[prev]
                    = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[j];
                }

                // we just removed one
                innerLoopLimit--;
                outerLoopLimit--;
            }
            else
            {
                // this mode is doable on MHL, so move on to the next index
                ++i;
            }
        }

        // check the last one
        if (0 == g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[outerLoopLimit].VIC)
        {
            numCeaVicsPruned++;
            g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[outerLoopLimit].native = 0;
        }

        //DumpEdidBlock(pCeaExtension,sizeof(*pCeaExtension))  // no semicolon needed here
        //now move all other data up
        {
            uint8_t *pbDest = (uint8_t *)&g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[innerLoopLimit];
            uint8_t *pbSrc =
                (uint8_t *)&g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader];

       
			if(EDID_BLOCK_SIZE != sizeof(*pCeaExtension))
			{
				
				SII_DBG_PRINT("\n\n unexpected extension size\n\n");
			}
			
            while (pbSrc < pbLimit)
            {
                SII_DBG_PRINT( "moving data up 0x%x(0x%02x) <- 0x%x(0x%02x)\n", (uint32_t)pbDest,
                                                      (uint8_t)*pbDest, (uint32_t)pbSrc, (uint8_t)*pbSrc);
                *pbDest++ = *pbSrc++;
            }

            while (pbDest < pbLimit)
            {
                SII_DBG_PRINT("clearing data 0x%X <- 0\n", (uint32_t)pbDest);
                *pbDest++ = 0;
            }
        }
        SII_DBG_PRINT("CEA-861-D DTDs began at 0x%02x"
                                              "CEA-861-D SVD count: 0x%x\n",
                                              (uint16_t)pCeaExtension->byteOffsetTo18ByteDescriptors,
                                              (uint16_t)g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader
                        );

        pCeaExtension->byteOffsetTo18ByteDescriptors -= numCeaVicsPruned;
        g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader = innerLoopLimit;

        SII_DBG_PRINT("CEA-861-D DTDs now begin at 0x%02x"
                                              "CEA-861-D SVD count: 0x%x\n",
                                              (uint16_t)pCeaExtension->byteOffsetTo18ByteDescriptors,
                                              (uint16_t)g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader
                        );

        //DumpEdidBlock(pCeaExtension,sizeof(*pCeaExtension))  // no semicolon needed here
    }

    // re-compute the checksum(s)

	if(EDID_BLOCK_SIZE != sizeof(*pEdidBlock0))
	{
		
		SII_DBG_PRINT("\n\n unexpected size for block 0\n\n");
	}
	
	if(EDID_BLOCK_SIZE != sizeof(*pCeaExtension))
	{
		
		SII_DBG_PRINT("\n\n unexpected size for  CEA extension\n\n");
	}

    pEdidBlock0->checkSum = CalculateGenericCheckSum((uint8_t *)pEdidBlock0, 0, sizeof(*pEdidBlock0));

    pCeaExtension->checkSum = CalculateGenericCheckSum((uint8_t *)pCeaExtension, 0, sizeof(*pCeaExtension));

    //DumpEdidBlock(pCeaExtension,sizeof(*pCeaExtension))  // no semicolon needed here

    // parse the new block;
    //SiiParse861Block((uint8_t *)pCeaExtension);

    SetMiscFlag(SiiPruneEDID, FLAGS_EDID_READ_DONE)

    //SiiTmdsEnable();
}


/*
 */
uint8_t SiiIsQualifiedMhlHdmiVIC(uint8_t VIC, PMhl2VideoDescriptor_t pMhl2VideoDescriptor) 
{
    uint8_t retVal = 0;
	pMhl2VideoDescriptor= pMhl2VideoDescriptor;
    if (QualifyPixelClockForMhl(HDMI_VicInfo[VIC].pixelClock0, 24))
    {
        retVal = 1;
    }

    if (QualifyPixelClockForMhl(HDMI_VicInfo[VIC].pixelClock0, 16))
    {
        retVal = 1;
    }

    if (HDMI_VicInfo[VIC].pixelClock0 != HDMI_VicInfo[VIC].pixelClock1)
    {
        if (QualifyPixelClockForMhl(HDMI_VicInfo[VIC].pixelClock1, 24))
        {
            retVal = 1;
        }

        if (QualifyPixelClockForMhl(HDMI_VicInfo[VIC].pixelClock1, 16))
        {
            retVal = 1;
        }
    }

    return retVal;
}

void SiiEnumerateHdmiVsdb(void) 
{
    if (g_PlumTxConfig.pHdmiVendorSpecificDataBlock)
    {
        PHdmiLLCVendorSpecificDataBlockPayload_t pHdmiVendorSpecificPayload =
            &g_PlumTxConfig.pHdmiVendorSpecificDataBlock->payload_u.HdmiLLC;
        uint8_t *pNextDB = (uint8_t *)pHdmiVendorSpecificPayload
                           + g_PlumTxConfig.pHdmiVendorSpecificDataBlock->header.lengthFollowingHeader;

        // if 3D_present field is included
        if (g_PlumTxConfig.pByte13ThroughByte15)
        {
            if (((uint8_t *)&g_PlumTxConfig.pByte13ThroughByte15->byte13) < pNextDB)
            {
                uint8_t hdmi3D_present = g_PlumTxConfig.pByte13ThroughByte15->byte13._3D_present;
                uint8_t hdmi_3D_Multi_present = g_PlumTxConfig.pByte13ThroughByte15->byte13._3D_Multi_present;

                // re-visit uint8_t Image_Size              = g_PlumTxConfig.pByte13ThroughByte15->byte13.Image_Size;

                // if HDMI_VIC_LEN is present...
                if (((uint8_t *)&g_PlumTxConfig.pByte13ThroughByte15->byte14) < pNextDB)
                {
                    uint8_t lengthVIC;
                    uint8_t index;
                    Mhl2VideoDescriptor_t mhl2VideoDescriptor;
                    lengthVIC = g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_VIC_LEN;
                    mhl2VideoDescriptor.LeftRight = 0;
                    mhl2VideoDescriptor.TopBottom = 0;
                    mhl2VideoDescriptor.FrameSequential = 0;
                    for (index = 0; index < lengthVIC; ++index)
                    {
                        uint8_t VIC;

                        VIC = g_PlumTxConfig.pByte13ThroughByte15->vicList[index];
                        if (!SiiIsQualifiedMhlHdmiVIC(VIC, &mhl2VideoDescriptor))
                        {
                            // TX_PRUNE_PRINT(("'can't do HDMI VIC:%d\n",(uint16_t)VIC));
                            SII_DBG_PRINT("'can't do HDMI VIC:%d\n", (uint16_t)VIC); 
                            g_PlumTxConfig.pByte13ThroughByte15->vicList[index] = 0;
                        }
                    }

                    if (hdmi3D_present)
                    {
                        uint8_t length3D;
                        PHdmi3DSubBlock_t pThree3DSubBlock =
                            (PHdmi3DSubBlock_t)&g_PlumTxConfig.pByte13ThroughByte15->vicList[lengthVIC];
                        union
                        {
                            P_3DStructureAndDetailEntry_u            pThreeD;
                            P_3DStructureAndDetailEntrySansByte1_t   pSansByte1;
                            P_3DStructureAndDetailEntryWithByte1_t   pWithByte1;
                            uint8_t                                 *pAsBytes;
                        } pThreeD_u;
                        uint8_t limit;
                        pThreeD_u.pThreeD = NULL;
                        length3D = g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_3D_LEN;
                        limit = g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader;

                        // only do the first 16
                        limit = (limit > 16) ? 16 : limit;
                        switch (hdmi_3D_Multi_present)
                        {
                        case 0x00:

                            //3D_Structure_ALL_15..0 and 3D_MASK_15..0 fields are not present
                            pThreeD_u.pThreeD =
                                &pThree3DSubBlock->hdmi3DSubBlockSansAllAndMask._3DStructureAndDetailList[0];
                            break;
                        case 0x01:

                            /*
                                3D_Structure_ALL_15..0 is present and assigns 3D formats
                                    to all of the VICs listed in the first 16 entries in the EDID
                                3D_Mask_15..0 is not present
                             */
                        {
                            P_3D_StructureAll_t p3DStructureAll =
                                (P_3D_StructureAll_t)&g_PlumTxConfig.pByte13ThroughByte15->vicList[lengthVIC];
                            mhl2VideoDescriptor.LeftRight = p3DStructureAll->_3D_Structure_ALL_7_0.sideBySide;
                            mhl2VideoDescriptor.TopBottom = p3DStructureAll->_3D_Structure_ALL_15_8.topBottom;
                            mhl2VideoDescriptor.FrameSequential = p3DStructureAll->_3D_Structure_ALL_15_8.framePacking;
                            for (index = 0; index < limit; ++index)
                            {
                                uint8_t VIC;

                                VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC;
                                if (VIC)
                                {
                                    if (!IsQualifiedMhlVIC(VIC, &mhl2VideoDescriptor))
                                    {
                                        g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC = 0;
                                    }
                                }
                            }

                            length3D -= sizeof(*p3DStructureAll);
                        }
                            pThreeD_u.pThreeD = &pThree3DSubBlock->hdmi3DSubBlockSansMask._3DStructureAndDetailList[0];
                            break;
                        case 0x02:

                            /*
                                3D_Structure_ALL_15..0 and 3D_Mask_15..0 are present and
                                    assign 3D formats to some of the VICS listed in the first
                                    16 entries in the EDID

                             */
                        {
                            P_3D_StructureAll_t p3DStructureAll =
                                (P_3D_StructureAll_t)&g_PlumTxConfig.pByte13ThroughByte15->vicList[lengthVIC];
                            P_3D_Mask_t p3DMask = (P_3D_Mask_t)(p3DStructureAll + 1);
                            uint8_t mask;
                            mhl2VideoDescriptor.LeftRight = p3DStructureAll->_3D_Structure_ALL_7_0.sideBySide;
                            mhl2VideoDescriptor.TopBottom = p3DStructureAll->_3D_Structure_ALL_15_8.topBottom;
                            mhl2VideoDescriptor.FrameSequential = p3DStructureAll->_3D_Structure_ALL_15_8.framePacking;
                            for (mask = 1, index = 0; (mask > 0) && (index < limit); ++index, mask <<= 1)
                            {
                                uint8_t VIC;
                                Mhl2VideoDescriptor_t thisMhl2VideoDescriptor;

                                if (mask & p3DMask->_3D_Mask_7_0)
                                {
                                    thisMhl2VideoDescriptor = mhl2VideoDescriptor;
                                }
                                else
                                {
                                    thisMhl2VideoDescriptor.LeftRight = 0;
                                    thisMhl2VideoDescriptor.TopBottom = 0;
                                    thisMhl2VideoDescriptor.FrameSequential = 0;
                                }

                                VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC;
                                if (VIC)
                                {
                                    if (!IsQualifiedMhlVIC(VIC, &mhl2VideoDescriptor))
                                    {
                                        g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC = 0;
                                    }
                                }
                            }

                            for (mask = 1; (mask > 0) && (index < limit); ++index, mask <<= 1)
                            {
                                uint8_t VIC;
                                Mhl2VideoDescriptor_t thisMhl2VideoDescriptor;

                                if (mask & p3DMask->_3D_Mask_15_8)
                                {
                                    thisMhl2VideoDescriptor = mhl2VideoDescriptor;
                                }
                                else
                                {
                                    thisMhl2VideoDescriptor.LeftRight = 0;
                                    thisMhl2VideoDescriptor.TopBottom = 0;
                                    thisMhl2VideoDescriptor.FrameSequential = 0;
                                }

                                VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC;
                                if (VIC)
                                {
                                    if (!IsQualifiedMhlVIC(VIC, &mhl2VideoDescriptor))
                                    {
                                        g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[index].VIC = 0;
                                    }
                                }
                            }

                            length3D -= sizeof(*p3DStructureAll);
                            length3D -= sizeof(*p3DMask);
                        }
                            pThreeD_u.pThreeD =
                                &pThree3DSubBlock->hdmi3DSubBlockWithAllAndMask._3DStructureAndDetailList[0];
                            g_PlumTxConfig.p3DMask = &pThree3DSubBlock->hdmi3DSubBlockWithAllAndMask._3D_Mask;
                            break;
                        case 0x03:

                            /*
                                Reserved for future use.
                                3D_Structure_ALL_15..0 and 3D_Mask_15..0 are NOT present
                             */
                            pThreeD_u.pThreeD =
                                &pThree3DSubBlock->hdmi3DSubBlockSansAllAndMask._3DStructureAndDetailList[0];
                            break;
                        }

                        g_PlumTxConfig.pThreeD  = pThreeD_u.pThreeD;
                        g_PlumTxConfig.p3DLimit = &pThreeD_u.pAsBytes[length3D];
                        while (pThreeD_u.pAsBytes < g_PlumTxConfig.p3DLimit)
                        {
                            uint8_t _2D_VIC_order = pThreeD_u.pSansByte1->byte0._2D_VIC_order;
                            ThreeDStructure_e _3D_Structure = pThreeD_u.pSansByte1->byte0._3D_Structure;
                            uint8_t VIC;
                            VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[_2D_VIC_order].VIC;

                            //this VIC position might have gotten disqualified already
                            if (VIC)
                            {
                                mhl2VideoDescriptor.LeftRight = 0;
                                mhl2VideoDescriptor.TopBottom = 0;
                                mhl2VideoDescriptor.FrameSequential = 0;
                                switch (_3D_Structure)
                                {
                                case tdsSideBySide:
                                {
                                    //re-visit uint8_t _3D_Detail    = pThreeD_u.pWithByte1->byte1._3D_Detail;
                                    mhl2VideoDescriptor.LeftRight = 1;
                                }
                                    break;
                                case tdsTopAndBottom:
                                    mhl2VideoDescriptor.TopBottom = 1;
                                    break;
                                case tdsFramePacking:
                                    mhl2VideoDescriptor.FrameSequential = 1;
                                    break;
                                }

                                if (_3D_Structure < tdsSideBySide)
                                {
                                    pThreeD_u.pSansByte1++;
                                }
                                else
                                {
                                    pThreeD_u.pWithByte1++;
                                }

                                if (!IsQualifiedMhlVIC(VIC, &mhl2VideoDescriptor))
                                {
                                    g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[_2D_VIC_order].VIC = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void SiiDisplayTimingEnumerationEnd(void)
{
    // finish off with any 3D modes reported via the HDMI VSDB
    SiiEnumerateHdmiVsdb();

    // notify the app (board specific) layer
    SetMiscFlag(SiiDisplayTimingEnumerationEnd, FLAGS_BURST_3D_DONE)
    SiiPruneEDID();
}

/*
 */
static void SiiProcess3D_VICBurst(PMhl2VideoFormatData_t pWriteBurstData // from 3D_REQ
)
{
    uint8_t blockIndex = 0;
    PMhl2VideoDescriptor_t pMhlVideoDescriptor;

    //re-visit uint8_t edidLimit = g_PlumTxConfig.pByte13ThroughByte15->byte14.HDMI_3D_LEN;

    if (g_PlumTxConfig.burstEntryCount3D_VIC < g_PlumTxConfig.pVideoDataBlock2D->header.lengthFollowingHeader)
    {
        for ( // blockIndex is set to zero above
            ; (blockIndex < pWriteBurstData->numEntriesThisBurst)
            &&
            (g_PlumTxConfig.burstEntryCount3D_VIC < pWriteBurstData->totalEntries)
            ; ++blockIndex,
            ++g_PlumTxConfig.burstEntryCount3D_VIC,
            ++g_PlumTxConfig.vic2Dindex)              // each SVD is 1 byte long
        {
            uint8_t VIC;
            uint8_t thisModeDoable = 0;
            pMhlVideoDescriptor = &pWriteBurstData->videoDescriptors[blockIndex];
            VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[g_PlumTxConfig.vic2Dindex].VIC;

            if (VIC)
            {
                SII_DBG_PRINT("Short Descriptor[%bd] 3D VIC: %bd %s %s %s\n",
                                                      g_PlumTxConfig.burstEntryCount3D_VIC,
                                                      VIC,
                                                      pMhlVideoDescriptor->LeftRight      ? pszLeftRight      : pszSpace,
                                                      pMhlVideoDescriptor->TopBottom      ? pszTopBottom      : pszSpace,
                                                      pMhlVideoDescriptor->FrameSequential ? pszFrameSequential : pszSpace
                                );
                thisModeDoable = IsQualifiedMhlVIC(VIC, pMhlVideoDescriptor);
                if (!thisModeDoable)
                {
                    // prune this mode from EDID

                    SII_DBG_PRINT("'can't do CEA VIC:%d\n", (uint16_t)VIC);
                    g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[g_PlumTxConfig.vic2Dindex].VIC = 0;
                }
            }
        }
    }

    if (g_PlumTxConfig.burstEntryCount3D_VIC >= pWriteBurstData->totalEntries)
    {
        SetMiscFlag(SiiProcess3D_VICBurst, FLAGS_BURST_3D_VIC_DONE)
        if (TestMiscFlag(FLAGS_BURST_3D_DTD_DONE))
        {
            if (!TestMiscFlag(FLAGS_BURST_3D_DONE))
            {
                SiiDisplayTimingEnumerationEnd();
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvParseDetailedTimingFor3D()
//
// PURPOSE      :   Parse the detailed timing section of EDID Block 0 and
//                  print their decoded meaning to the screen.
//
// INPUT PARAMS :   Pointer to the array where the data read from EDID
//                  Block0 is stored.
//
//                  Offset to the beginning of the Detailed Timing Descriptor
//                  data.
//
//                                      Block indicator to distinguish between block #0 and blocks
//                                      #2, #3
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   true if valid timing, false if not
//
//////////////////////////////////////////////////////////////////////////////
static bool SiiDrvParseDetailedTimingFor3D(P_18ByteDescriptor_u pDesc, uint8_t Block, uint8_t *pIsTiming,
                                               PMhl2VideoDescriptor_t pMhl2VideoDescriptor)
{
    uint8_t TmpByte;
    uint16_t TmpWord;

    *pIsTiming = 0;
    TmpWord = pDesc->dtd.pixelClockLow + 256 * pDesc->dtd.pixelClockHigh;

    if (TmpWord == 0x00)            // 18 byte partition is used as either for Monitor Name or for Monitor Range Limits or it is unused
    {
        if (Block == EDID_BLOCK_0)      // if called from Block #0 and first 2 bytes are 0 => either Monitor Name or for Monitor Range Limits
        {
            if (0xFC == pDesc->name.dataTypeTag) //(edidBlockData[DetailedTimingOffset + 3] == 0xFC) // these 13 bytes are ASCII coded monitor name
            {
                uint8_t i;

                SII_DBG_PRINT("Monitor Name: ");

                for (i = 0; i < 13; i++)
                {
                    /* for easy read */
                    printk("%c", pDesc->name.asciiName[i]); // Display monitor name  
                }

                SII_DBG_PRINT( "\n"); 
            }
            else if (0xFD == pDesc->name.dataTypeTag) //(edidBlockData[DetailedTimingOffset + 3] == 0xFD) // these 13 bytes contain Monitor Range limits, binary coded
            {
                SII_DBG_PRINT("Monitor Range Limits:\n");

                SII_DBG_PRINT("Min Vertical Rate in Hz: %d\n",
                                                      (int)pDesc->rangeLimits.minVerticalRateHz);
                SII_DBG_PRINT("Max Vertical Rate in Hz: %d\n",
                                                      (int)pDesc->rangeLimits.maxVerticalRateHz);
                SII_DBG_PRINT("Min Horizontal Rate in KHz: %d\n",
                                                      (int)pDesc->rangeLimits.minHorizontalRateKHz);
                SII_DBG_PRINT("Max Horizontal Rate in KHz: %d\n",
                                                      (int)pDesc->rangeLimits.maxHorizontalRateKHz);
                SII_DBG_PRINT("Max Supported pixel clock rate in MHz/10: %d\n",
                                                      (int)pDesc->rangeLimits.maxPixelClockMHzDiv10);
                SII_DBG_PRINT("Tag for secondary timing formula (00h=not used): %d\n",
                                                    (int)pDesc->rangeLimits.tagSecondaryFormula);
            }
        }
        else if (Block == EDID_BLOCK_2_3)
        {
            // if called from block #2 or #3 and first 2 bytes are 0x00 (padding) then this
            // descriptor partition is not used and parsing should be stopped
            SII_DBG_PRINT("No More Detailed descriptors in this block\n");
            SII_DBG_PRINT("\n");
            return false;
        }
    }
    else // first 2 bytes are not 0 => this is a detailed timing descriptor from either block
    {
        uint32_t pixelClockFrequency;
        uint16_t columns, rows, verticalSyncPeriodInLines;
        uint32_t verticalRefreshRateInMilliHz, horizontalSyncFrequencyInHz, horizontalSyncPeriodInPixels;

        *pIsTiming = 1;

        pixelClockFrequency = (uint32_t)TmpWord * 10000;

        SII_DBG_PRINT("Pixel Clock: %d.%02d MHz or %ld Hz (0x%lx Hz)\n", TmpWord / 100, TmpWord
                                              % 100, pixelClockFrequency, pixelClockFrequency);

        columns = pDesc->dtd.horzActive7_0 + 256 * pDesc->dtd.horzActiveBlankingHigh.horzActive11_8;

        SII_DBG_PRINT("Horizontal Active Pixels: %d\n", columns);

        TmpWord = pDesc->dtd.horzBlanking7_0 + 256 * pDesc->dtd.horzActiveBlankingHigh.horzBlanking11_8;

        SII_DBG_PRINT("Horizontal Blanking (Pixels): %d\n", TmpWord);

        horizontalSyncPeriodInPixels = (uint32_t)columns + (uint32_t)TmpWord;
        horizontalSyncFrequencyInHz = pixelClockFrequency / horizontalSyncPeriodInPixels;

        SII_DBG_PRINT("horizontal period %lu pixels,  horizontalSyncFrequencyInHz: %lu Hz\n",
                                              horizontalSyncPeriodInPixels, horizontalSyncFrequencyInHz);

        rows = pDesc->dtd.vertActive7_0 + 256 * pDesc->dtd.vertActiveBlankingHigh.vertActive11_8;

        SII_DBG_PRINT("Vertical Active (Lines): %u\n", rows);

        TmpWord = pDesc->dtd.vertBlanking7_0 + 256 * pDesc->dtd.vertActiveBlankingHigh.vertBlanking11_8;

        SII_DBG_PRINT("Vertical Blanking (Lines): %u\n", TmpWord);

        verticalSyncPeriodInLines = rows + TmpWord;
        verticalRefreshRateInMilliHz = horizontalSyncFrequencyInHz * 1000 / (verticalSyncPeriodInLines);

        SII_DBG_PRINT("vertical period %u lines, frequency %lu MilliHz\n",
                                              verticalSyncPeriodInLines, verticalRefreshRateInMilliHz);

        TmpWord = pDesc->dtd.horzSyncOffset7_0 + 256
                  * pDesc->dtd.hsOffsetHsPulseWidthVsOffsetVsPulseWidth.horzSyncOffset9_8;

        SII_DBG_PRINT("Horizontal Sync Offset (Pixels): %d\n", TmpWord);

        TmpWord = pDesc->dtd.horzSyncPulseWidth7_0 + 256
                  * pDesc->dtd.hsOffsetHsPulseWidthVsOffsetVsPulseWidth.horzSyncPulseWidth9_8;

        SII_DBG_PRINT("Horizontal Sync Pulse Width (Pixels): %d\n", TmpWord);

        TmpWord = pDesc->dtd.vertSyncOffsetWidth.vertSyncOffset3_0 + 16
                  * pDesc->dtd.hsOffsetHsPulseWidthVsOffsetVsPulseWidth.vertSyncOffset5_4;

        SII_DBG_PRINT("Vertical Sync Offset (Lines): %d\n", TmpWord);

        TmpWord = pDesc->dtd.vertSyncOffsetWidth.vertSyncPulseWidth3_0 +                       + 16
                  * pDesc->dtd.hsOffsetHsPulseWidthVsOffsetVsPulseWidth.vertSyncPulseWidth5_4;

        SII_DBG_PRINT("Vertical Sync Pulse Width (Lines): %d\n", TmpWord);

        TmpWord = pDesc->dtd.horzImageSizemm_7_0 + 256 * pDesc->dtd.imageSizeHigh.horzImageSizemm_11_8;

        SII_DBG_PRINT("Horizontal Image Size (mm): %d\n", TmpWord);

        TmpWord = pDesc->dtd.vertImageSizemm_7_0 + 256 * pDesc->dtd.imageSizeHigh.vertImageSizemm_11_8;

        SII_DBG_PRINT("Vertical Image Size (mm): %d\n", TmpWord);

        TmpByte = pDesc->dtd.horzBorderLines;

        SII_DBG_PRINT("Horizontal Border (Pixels): %d\n", (int)TmpByte);

        TmpByte = pDesc->dtd.vertBorderPixels;

        SII_DBG_PRINT("Vertical Border (Lines): %d\n", (int)TmpByte);

        if (pDesc->dtd.flags.interlaced)
        {
            SII_DBG_PRINT("Interlaced\n");
        }
        else
        {
            SII_DBG_PRINT("Non-Interlaced\n");
        }

        switch (pDesc->dtd.flags.stereoBits2_1)
        {
        case 0:

            SII_DBG_PRINT("Normal Display, No Stereo\n");
            break;
        case 1:
            if (0 == pDesc->dtd.flags.stereoBit0)
            {
                SII_DBG_PRINT("Field sequential stereo, right image when stereo sync signal == 1\n");
            }
            else
            {
                SII_DBG_PRINT("2-way interleaved stereo, right image on even lines\n");
            }

            break;
        case 2:
            if (0 == pDesc->dtd.flags.stereoBit0)
            {
                SII_DBG_PRINT("field-sequential stereo, left image when stereo sync signal == 1\n");
            }
            else
            {
                SII_DBG_PRINT("2-way interleaved stereo, left image on even lines.\n");
            }

            break;
        case 3:
            if (0 == pDesc->dtd.flags.stereoBit0)
            {
                SII_DBG_PRINT("4-way interleaved stereo\n");
            }
            else
            {
                SII_DBG_PRINT("side-by-side interleaved stereo.\n");
            }

            break;
        }

        switch (pDesc->dtd.flags.syncSignalType)
        {
        case 0x0:

            SII_DBG_PRINT("Analog Composite\n");
            break;
        case 0x1:

            SII_DBG_PRINT("Bipolar Analog Composite\n");
            break;
        case 0x2:

            SII_DBG_PRINT("Digital Composite\n");
            break;
        case 0x3:

            SII_DBG_PRINT("Digital Separate\n");
            break;
        }

        if (pMhl2VideoDescriptor)
        {
            uint8_t thisModeDoable = 0;
            if ((thisModeDoable = QualifyPixelClockForMhl(pixelClockFrequency, 24)))
            {
            }

            if (thisModeDoable |= QualifyPixelClockForMhl(pixelClockFrequency, 16))
            {
            }

            if (!thisModeDoable)
            {
                return false;
            }
        }
    }

    return true;
}

void SiiCheck3D_DTD_Sequence_Done(PMhl2VideoFormatData_t pWriteBurstData)
{
    if (g_PlumTxConfig.burstEntryCount3D_DTD >= pWriteBurstData->totalEntries)
    {
        SetMiscFlag(SiiProcess3D_DTDBurst, FLAGS_BURST_3D_DTD_DONE)
        if (TestMiscFlag(FLAGS_BURST_3D_VIC_DONE))
        {
            if (!TestMiscFlag(FLAGS_BURST_3D_DONE))
            {
                SiiDisplayTimingEnumerationEnd();
            }
        }
    }
}

static void SiiProcess3D_DTDBurst(PMhl2VideoFormatData_t pWriteBurstData)
{
    PMhl2VideoDescriptor_t pMhlVideoDescriptor;
    int burstIndex   = 0;
    uint8_t isTiming = 0;

    if (!(FLAGS_BURST_3D_DTD_VESA_DONE & g_PlumTxConfig.miscFlags))
    {
        PEDID_Block0_t pEdidBlock0 = (PEDID_Block0_t)&g_PlumTxConfig.EDID.edidBlockData[0];

        // up to four DTDs are possible in the base VESA EDID
        //  this will be covered by a single burst.
        for (    // burstIndex is set to zero above
            ; (burstIndex < pWriteBurstData->numEntriesThisBurst)
            &&
            (g_PlumTxConfig.burstEntryCount3D_DTD < pWriteBurstData->totalEntries)
            &&
            (g_PlumTxConfig.vesaDTDindex < sizeof(pEdidBlock0->detailedTimingDescriptors)
             / sizeof(pEdidBlock0->detailedTimingDescriptors[0]))
            ; ++g_PlumTxConfig.vesaDTDindex)
        {
            P_18ByteDescriptor_u pDesc = (P_18ByteDescriptor_u)
                                         & pEdidBlock0->detailedTimingDescriptors[g_PlumTxConfig.vesaDTDindex];
            bool isValid = 0;

            pMhlVideoDescriptor = &pWriteBurstData->videoDescriptors[burstIndex];

            isValid = SiiDrvParseDetailedTimingFor3D(pDesc, EDID_BLOCK_0, &isTiming, pMhlVideoDescriptor);

            // only count it if it's a valid timing
            if (isTiming)
            {
                if (isValid)
                {
                    SII_DBG_PRINT("VESA DTD index: %d burst index:%d DTD SP index:%d %s %s %s\n",
                                     (uint16_t)g_PlumTxConfig.vesaDTDindex, (uint16_t)burstIndex,
                                     (uint16_t)g_PlumTxConfig.burstEntryCount3D_DTD,
                                     pMhlVideoDescriptor->LeftRight      ? pszLeftRight      : pszSpace,
                                     pMhlVideoDescriptor->TopBottom      ? pszTopBottom      : pszSpace,
                                     pMhlVideoDescriptor->FrameSequential ? pszFrameSequential : pszSpace
                                    );
                }
                else
                {
                    // mark this mode for pruning by setting horizontal active to zero
                    pDesc->dtd.horzActive7_0 = 0;
                    pDesc->dtd.horzActiveBlankingHigh.horzActive11_8 = 0;
                }

                burstIndex++;
                g_PlumTxConfig.burstEntryCount3D_DTD++;
            }
            else
            {
                SII_DBG_PRINT("VESA DTD index: %d (Monitor Descriptor/Name)\n",
                                                      (uint16_t)g_PlumTxConfig.vesaDTDindex);
            }
        }

        if (g_PlumTxConfig.vesaDTDindex >= sizeof(pEdidBlock0->detailedTimingDescriptors)
            / sizeof(pEdidBlock0->detailedTimingDescriptors[0]))
        {
            // we got past the VESA DTDs in this burst
            SetMiscFlag(SiiProcess3D_DTDBurst, FLAGS_BURST_3D_DTD_VESA_DONE)
        }
        else
        {
            SiiCheck3D_DTD_Sequence_Done(pWriteBurstData);

            // more VESA DTDs to process in next burst
            SII_DBG_PRINT("%s\n", TestMiscFlag(FLAGS_BURST_3D_DTD_DONE) ? "3D DTD descriptors exhausted" : "more VESA DTDs to process");
            return;
        }
    }

    {
        PCeaExtension_t pCeaExtension = (PCeaExtension_t)&g_PlumTxConfig.EDID.edidBlockData[EDID_BLOCK_SIZE];
        uint8_t dtdLimit =
            (uint8_t)pCeaExtension->version_u.version3.miscSupport.totalNumberDetailedTimingDescriptorsInEntireEDID;
        union
        {
            uint8_t *            pucDataBlock;
            P_18ByteDescriptor_u pLongDescriptors;
        } pData_u;
        pData_u.pLongDescriptors = (P_18ByteDescriptor_u)(((uint8_t *)pCeaExtension)
                                                          + pCeaExtension->byteOffsetTo18ByteDescriptors);
        SII_DBG_PRINT("continuing with CEA-861-D/E DTDs"
                                              "\n\tburstIndex: %d"
                                              "\n\tburstEntryCount3D_DTD: %d"
                                              "\n\tnumEntriesThisBurst: %d"
                                              "\n\ttotalEntries:%d"
                                              "\n\tdtdLimit:%d"
                                              "\n\toffsetTo18ByteDescriptors:0x%x\n",
                                              (uint16_t)burstIndex,
                                              (uint16_t)g_PlumTxConfig.burstEntryCount3D_DTD,
                                              (uint16_t)pWriteBurstData->numEntriesThisBurst,
                                              (uint16_t)pWriteBurstData->totalEntries,
                                              (uint16_t)dtdLimit,
                                              (uint16_t)pCeaExtension->byteOffsetTo18ByteDescriptors
                        );

        // continue with CEA-861-D/E DTDs when done with VESA DTDs
        for ( // burstIndex is set to zero above
            ; (burstIndex < pWriteBurstData->numEntriesThisBurst)
            &&
            (g_PlumTxConfig.burstEntryCount3D_DTD < pWriteBurstData->totalEntries)
            &&
            (g_PlumTxConfig.cea861DTDindex < dtdLimit)
            ; ++g_PlumTxConfig.cea861DTDindex)
        {
            P_18ByteDescriptor_u pDesc = &pData_u.pLongDescriptors[g_PlumTxConfig.cea861DTDindex];
            bool isValid = 0;
            pMhlVideoDescriptor = &pWriteBurstData->videoDescriptors[burstIndex];
            isValid = SiiDrvParseDetailedTimingFor3D(pDesc, EDID_BLOCK_2_3, &isTiming, pMhlVideoDescriptor);

            // only count it if it's a valid timing
            if (isTiming)
            {
                if (isValid)
                {
                    SII_DBG_PRINT("CEA-861 DTD index: %d burst index:%d DTD SP index:%d %s %s %s\n\n",
                                     (uint16_t)g_PlumTxConfig.cea861DTDindex, (uint16_t)burstIndex,
                                     (uint16_t)g_PlumTxConfig.burstEntryCount3D_DTD,
                                     pMhlVideoDescriptor->LeftRight      ? pszLeftRight      : pszSpace,
                                     pMhlVideoDescriptor->TopBottom      ? pszTopBottom      : pszSpace,
                                     pMhlVideoDescriptor->FrameSequential ? pszFrameSequential : pszSpace
                                    );
                }
                else
                {
                    // mark this mode for pruning by setting horizontal active to zero
                    pDesc->dtd.horzActive7_0 = 0;
                    pDesc->dtd.horzActiveBlankingHigh.horzActive11_8 = 0;
                }

                ++burstIndex;
                ++g_PlumTxConfig.burstEntryCount3D_DTD;
            }
            else
            {
                SII_DBG_PRINT("CEA-861 DTD index: %d\n", (uint16_t)g_PlumTxConfig.vesaDTDindex);
            }
        }

        SII_DBG_PRINT("DTD burst complete\n");
        SiiCheck3D_DTD_Sequence_Done(pWriteBurstData);
    }
}

static void SiiSend3DReq(void)
{
    SII_DBG_PRINT("Mhl2Tx: SiiSend3DReq\n");

    // call EDID parser to set up pointer list for MHL processing
    //result =SiiProcessEDID(edidBlockData);

    // 3D parsing will go haywire with a garbage EDID
    SII_DBG_PRINT("Mhl2Tx: outputMode: %s\n", g_PlumTxConfig.EDID.HDMI_Sink ? "HDMI" : "DVI");
    if (g_PlumTxConfig.EDID.HDMI_Sink)
    {
        SII_DBG_PRINT("Mhl2Tx: remote MHL version: 0x%02x\n",
                                            (uint16_t)g_PlumTxConfig.devCapCache.aucDevCapCache[DEVCAP_OFFSET_MHL_VERSION]);
        if (0x20 <= g_PlumTxConfig.devCapCache.aucDevCapCache[DEVCAP_OFFSET_MHL_VERSION])
        {
            SII_DBG_PRINT("MHL 2.x sink detected\n");


            // ask the sink to begin sending 3D write bursts
            SiiSetInt( MHL_RCHANGE_INT, MHL2_INT_3D_REQ, 0);

            g_PlumTxConfig.burstEntryCount3D_DTD = 0;
            g_PlumTxConfig.vesaDTDindex = 0;
            g_PlumTxConfig.burstEntryCount3D_VIC = 0;
            g_PlumTxConfig.vic2Dindex = 0;
            g_PlumTxConfig.cea861DTDindex = 0;

            SetMiscFlag(SiiSend3DReq, FLAGS_SENT_3D_REQ)
            ClrMiscFlag(SiiSend3DReq, FLAGS_BURST_3D_DONE | FLAGS_BURST_3D_DTD_DONE | FLAGS_BURST_3D_VIC_DONE
                        | FLAGS_BURST_3D_DTD_VESA_DONE)
        }
        else
        {
            SII_DBG_PRINT("MHL 1.x sink detected\n");
        }
    }
}
#endif

void SiiProcessWriteBurstData( void )
{
    SII_DBG_PRINT("SiiProcessWriteBurstData\n");
#if USE_3D
    {
        BurstId_e burstId;
        SiiDrvGetScratchPad(0, g_PlumTxConfig.incomingScratchPad.asBytes, sizeof(g_PlumTxConfig.incomingScratchPad));
        {
            uint8_t i;
            SII_DBG_PRINT("MhlTx: Write Burst Data from Peer:");

            for (i = 0; i < sizeof(g_PlumTxConfig.incomingScratchPad); ++i)
            {
                printk(" 0x%02X", (int) g_PlumTxConfig.incomingScratchPad.asBytes[i]);
            }

            printk("\n");
        }

        burstId = BURST_ID(g_PlumTxConfig.incomingScratchPad.videoFormatData.burstId);

        switch (burstId)
        {
        case burstId_3D_VIC:
            SiiProcess3D_VICBurst(&g_PlumTxConfig.incomingScratchPad.videoFormatData);
            break;
        case burstId_3D_DTD:
            SiiProcess3D_DTDBurst(&g_PlumTxConfig.incomingScratchPad.videoFormatData);
            break;
        default:
            SII_DBG_PRINT("SiiProcessWriteBurstData burstId: %d\n", (uint16_t)burstId);

			if(&g_PlumTxConfig.incomingScratchPad.videoFormatData.burstId.high
                    != &g_PlumTxConfig.incomingScratchPad.asBytes[0])
			{
				
				SII_DBG_PRINT(" high at offset 0x%x asBytes[0] at offset 0x%x\n",
					&g_PlumTxConfig.incomingScratchPad.videoFormatData.burstId.high,
			        &g_PlumTxConfig.incomingScratchPad.asBytes[0]);
			}
				if(&g_PlumTxConfig.incomingScratchPad.videoFormatData.burstId.low
                    != &g_PlumTxConfig.incomingScratchPad.asBytes[1])
			{
				
				SII_DBG_PRINT(" low  at offset 0x%x asBytes[1] at offset 0x%x\n",
                    &g_PlumTxConfig.incomingScratchPad.videoFormatData.burstId.low,
                    &g_PlumTxConfig.incomingScratchPad.asBytes[1]);
			}

            SII_DBG_PRINT("MhlTx: BurstId: 0x%04x\n", burstId);
        }
    }
#else 
    SiiDrvGetScratchPad(0, g_PlumTxConfig.incomingScratchPad.asBytes, sizeof(g_PlumTxConfig.incomingScratchPad));
#endif 
}

uint8_t SiiDrvParse861ShortDescriptors (uint8_t *pEdidBlockData   ) //UT ZHOU
{

    uint8_t i;
    PCeaExtension_t pCeaExtension = (PCeaExtension_t)pEdidBlockData;

    if (EDID_EXTENSION_TAG != pCeaExtension->tag) // (edidBlockData[EDID_TAG_ADDR] != EDID_EXTENSION_TAG)
    {
        SII_DBG_PRINT("EDID -> Extension Tag Error\n");

        return EDID_EXT_TAG_ERROR;
    }
    else
    {
        if (EDID_REV_THREE != pCeaExtension->revision) //(edidBlockData[EDID_REV_ADDR] != EDID_REV_THREE)
        {
            SII_DBG_PRINT("EDID -> Invalid EIA-861 Revision ID. Expected 0x%02X. Got 0x%02X\n",
                                                (int)EDID_REV_THREE, (int)pCeaExtension->revision);
            return EDID_REV_ADDR_ERROR;
        }
        else
        {
            //uint8_t DataIndex;
            //uint8_t LongDescriptorOffset;
            PCeaExtensionVersion3_t pCeaExtensionVersion3 = &pCeaExtension->version_u.version3;
            union
            {
                uint8_t *                 pucDataBlock;
                PCeaDataBlockCollection_t pCeaDataBlock;
            } pData_u;
            uint8_t *pucLongDescriptors;

            // block offset where long descriptors start
            pucLongDescriptors = ((uint8_t *)pCeaExtension) + pCeaExtension->byteOffsetTo18ByteDescriptors;

            // byte #3 of CEA extension version 3
            g_PlumTxConfig.EDID.UnderScan   = pCeaExtensionVersion3->miscSupport.underscanITformatsByDefault ? 1 : 0; // (edidBlockData[MISC_SUPPORT_IDX] & BIT7)?1:0;
            g_PlumTxConfig.EDID.BasicAudio  = pCeaExtensionVersion3->miscSupport.basicAudioSupport ? 1 : 0;       //(edidBlockData[MISC_SUPPORT_IDX] & BIT6)?1:0;
            g_PlumTxConfig.EDID.YCbCr_4_4_4 = pCeaExtensionVersion3->miscSupport.YCrCb444Support;    // (edidBlockData[MISC_SUPPORT_IDX] & BIT5)?1:0;
            g_PlumTxConfig.EDID.YCbCr_4_2_2 = pCeaExtensionVersion3->miscSupport.YCrCb422Support;             // (edidBlockData[MISC_SUPPORT_IDX] & BIT4)?1:0;
            SII_DBG_PRINT("misc support index-> 0x%02x\n",
                                                *((uint8_t *)&pCeaExtensionVersion3->miscSupport));                               /*edidBlockData[MISC_SUPPORT_IDX]*/


            pData_u.pucDataBlock = &pCeaExtension->version_u.version3.Offset4_u.dataBlockCollection[0];              // DataIndex = EDID_DATA_START; // 4

            while (pData_u.pucDataBlock < pucLongDescriptors)
            {
                DataBlockTagCode_e TagCode; //uint8_t TagCode;
                uint8_t DataBlockLength;
                TagCode = pData_u.pCeaDataBlock->header.tagCode;
                DataBlockLength = pData_u.pCeaDataBlock->header.lengthFollowingHeader;
                SII_DBG_PRINT("TagCode:%d DataBlockLength:%d\n", TagCode, DataBlockLength);
                if ((pData_u.pucDataBlock + DataBlockLength) > pucLongDescriptors)
                {
                    // ERROR_DEBUG_PRINT(("EDID -> V Descriptor Overflow\n"));
                    SII_DBG_PRINT("EDID -> V Descriptor Overflow\n");
                    return EDID_V_DESCR_OVERFLOW;
                }

                i = 0;                                  // num of short video descriptors in current data block

                switch (TagCode)
                {
                case dbtcVideoDataBlock:     //VIDEO_D_BLOCK:
                {
                    SII_DBG_PRINT("dbtcVideoDataBlock:\n");
                    g_PlumTxConfig.pVideoDataBlock2D = (PVideoDataBlock_t)pData_u.pucDataBlock;

                    while (i < DataBlockLength)            // each SVD is 1 byte long
                    {
                        uint8_t VIC;
                        VIC = g_PlumTxConfig.pVideoDataBlock2D->shortDescriptors[i].VIC;
                        SII_DBG_PRINT("short desc[%d]: VIC: %d\n", i, VIC);
                        i++;
                    }

                    SII_DBG_PRINT("EDID -> %d descriptors in Short Descriptor Video Block\n", i);
                }
                    break;

                case dbtcAudioDataBlock:    //AUDIO_D_BLOCK:
                {
                    PAudioDataBlock_t pAudioDataBlock = (PAudioDataBlock_t) pData_u.pucDataBlock;
                    uint8_t A_DescriptorIndex = 0;  // static to support more than one extension

                    // each SAD is 3 bytes long
                    while (i < DataBlockLength / sizeof(pAudioDataBlock->shortAudioDescriptors[0]))
                    {
                        *((PCeaShortAudioDescriptor_t)&g_PlumTxConfig.EDID.AudioDescriptor[A_DescriptorIndex])
                        = pAudioDataBlock->shortAudioDescriptors[i];
                        A_DescriptorIndex++;
                        i++;
                    }

                    SII_DBG_PRINT("EDID -> Short Descriptor Audio Block\n");
                }
                    break;

                case dbtcSpeakerAllocationDataBlock:    //SPKR_ALLOC_D_BLOCK:
                {
                    PSpeakerAllocationDataBlock_t pSpeakerAllocationDataBlock =
                        (PSpeakerAllocationDataBlock_t) pData_u.pucDataBlock;

                    *((PSpeakerAllocationFlags_t)&g_PlumTxConfig.EDID.SpkrAlloc[i++]) =
                        pSpeakerAllocationDataBlock->payload.speakerAllocFlags;
                    SII_DBG_PRINT("EDID -> Short Descriptor Speaker Allocation Block\n");
                }
                    break;

                case dbtcUsedExtendedTag:    //USE_EXTENDED_TAG:
                {
                    ExtendedTagCode_t ExtendedTagCode;
                    ExtendedTagCode = pData_u.pCeaDataBlock->payload_u.extendedTag;     //edidBlockData[DataIndex++];
                    switch (ExtendedTagCode.extendedTagCode)
                    {
                    case etcVideoCapabilityDataBlock:        //VIDEO_CAPABILITY_D_BLOCK:
                    {
                        PVideoCapabilityDataBlock_t pVideoCapabilityDataBlock =
                            (PVideoCapabilityDataBlock_t)pData_u.pucDataBlock;
                        PVideoCapabilityDataPayLoad_t pPayLoad = &pVideoCapabilityDataBlock->payload;

                        g_PlumTxConfig.EDID.VideoCapabilityFlags = *((uint8_t *)pPayLoad);
                        g_PlumTxConfig.pVideoCapabilityDataBlock = pVideoCapabilityDataBlock;
                        SII_DBG_PRINT("EDID -> Short Descriptor Video Capability Block\n");
                    }
                        break;

                    case etcColorimetryDataBlock:         // COLORIMETRY_D_BLOCK:
                    {
                        PColorimetryDataBlock_t pColorimetryDataBlock = (PColorimetryDataBlock_t)pData_u.pucDataBlock;
                        PColorimeteryDataPayLoad_t pPayLoad = &pColorimetryDataBlock->payload;
                        g_PlumTxConfig.EDID.ColorimetrySupportFlags = pPayLoad->ciData.xvYCC;
                        g_PlumTxConfig.EDID.MetadataProfile = pPayLoad->cmMetaData.metaData;
                    }

                        SII_DBG_PRINT("EDID -> Short Descriptor Colorimetry Block\n");
                        break;
                    }
                }

                    break;

                case dbtcVendorSpecificDataBlock:    //VENDOR_SPEC_D_BLOCK:
                {
                    PVendorSpecificDataBlock_t pVendorSpecificDataBlock =
                        (PVendorSpecificDataBlock_t) pData_u.pucDataBlock;
                    uint8_t *pucNextDB = ((uint8_t *)&pVendorSpecificDataBlock->header)
                                         + sizeof(pVendorSpecificDataBlock->header) + DataBlockLength;

                    if ((pVendorSpecificDataBlock->IEEE_OUI[0] == 0x03)
                        && (pVendorSpecificDataBlock->IEEE_OUI[1] == 0x0C)
                        && (pVendorSpecificDataBlock->IEEE_OUI[2] == 0x00)
                    )

                    {
                        PHdmiLLCVendorSpecificDataBlockPayload_t pHdmiVendorSpecificPayload =
                            &pVendorSpecificDataBlock->payload_u.HdmiLLC;
                        g_PlumTxConfig.pHdmiVendorSpecificDataBlock = pVendorSpecificDataBlock;

						if(5 > DataBlockLength)
						{
							
							SII_DBG_PRINT("unexpected DataBlockLength:%d\n", DataBlockLength);
						}
						
                        g_PlumTxConfig.EDID.HDMI_Sink = true;
                        *((PHdmiLLC_BA_t)&g_PlumTxConfig.EDID.CEC_A_B) = pHdmiVendorSpecificPayload->B_A;       // CEC Physical address
                        *((PHdmiLLC_DC_t)&g_PlumTxConfig.EDID.CEC_C_D) = pHdmiVendorSpecificPayload->D_C;

                        // Offset of 3D_Present bit in VSDB
                        if (pHdmiVendorSpecificPayload->byte8.LatencyFieldsPresent)
                        {
                            if (pHdmiVendorSpecificPayload->byte8.I_LatencyFieldsPresent)
                            {
                                g_PlumTxConfig.pByte13ThroughByte15 =
                                    &pHdmiVendorSpecificPayload->vsdbFieldsByte9ThroughByte15.vsdbAllFieldsByte9ThroughByte15.byte13ThroughByte15;
                            }
                            else
                            {
                                g_PlumTxConfig.pByte13ThroughByte15 =
                                    &pHdmiVendorSpecificPayload->vsdbFieldsByte9ThroughByte15.vsdbAllFieldsByte9ThroughByte15SansInterlacedLatency.byte13ThroughByte15;
                            }
                        }
                        else
                        {
                            if (pHdmiVendorSpecificPayload->byte8.I_LatencyFieldsPresent)
                            {
                                g_PlumTxConfig.pByte13ThroughByte15 =
                                    &pHdmiVendorSpecificPayload->vsdbFieldsByte9ThroughByte15.vsdbAllFieldsByte9ThroughByte15SansProgressiveLatency.byte13ThroughByte15;
                            }
                            else
                            {
                                g_PlumTxConfig.pByte13ThroughByte15 =
                                    &pHdmiVendorSpecificPayload->vsdbFieldsByte9ThroughByte15.vsdbAllFieldsByte9ThroughByte15SansAllLatency.byte13ThroughByte15;
                            }
                        }

                        if (((uint8_t *)&g_PlumTxConfig.pByte13ThroughByte15->byte13) >= pucNextDB)
                        {
                            g_PlumTxConfig.EDID._3D_Supported = false;
                        }
                        else if (g_PlumTxConfig.pByte13ThroughByte15->byte13._3D_present)
                        {
                            g_PlumTxConfig.EDID._3D_Supported = true;
                        }
                        else
                        {
                            g_PlumTxConfig.EDID._3D_Supported = false;
                        }

                        SII_DBG_PRINT( "EDID indicates %s3D support\n",
                                                            g_PlumTxConfig.EDID._3D_Supported ? "" : "NO ");
                    }
                    else
                    {
                        g_PlumTxConfig.EDID.HDMI_Sink = false;
                    }

                    SII_DBG_PRINT("EDID -> Short Descriptor Vendor Block\n\n");
                }

                    break;
                case dbtcTerminator:
                    SII_DBG_PRINT("MhlTx: SiiSiiDrvParse861ShortDescriptors found terminator tag code\n");
                    return EDID_SHORT_DESCRIPTORS_OK;
                    break;

                default:

                    SII_DBG_PRINT("EDID -> Unknown Tag Code:0x%02x\n", (uint16_t)TagCode);
                    return EDID_UNKNOWN_TAG_CODE;
                }

                pData_u.pucDataBlock += sizeof(pData_u.pCeaDataBlock->header) + DataBlockLength;   // if there are more STDs than MAX_V_DESCRIPTORS, skip the last ones. Update DataIndex
            }

            return EDID_SHORT_DESCRIPTORS_OK;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiMscWriteBurstDone
//
// This function is called by the driver to inform of completion of a write burst.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
void    SiiMscWriteBurstDone( uint8_t data1 )
{
    data1 = data1;  // make this compile for NON debug builds
    SII_DBG_PRINT("MhlTx:SiiMscWriteBurstDone(0x%02X) Incoming\n", (int)data1);
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiGotMhlMscMsg
//
// This function is called by the driver to inform of arrival of a MHL MSC_MSG
// such as RCP, RCPK, RCPE. To quickly return back to interrupt, this function
// remembers the event (to be picked up by app later in task context).
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing of its own,
//
// No printfs.
//
// Application shall not call this function.
//
void    SiiGotMhlMscMsg( uint8_t subCommand, uint8_t cmdData )
{
    // Remember the event.
    g_PlumTxConfig.mscMsgArrived = true;
    g_PlumTxConfig.mscMsgSubCommand = subCommand;
    g_PlumTxConfig.mscMsgData = cmdData;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiGotMhlIntr
//
// This function is called by the driver to inform of arrival of a MHL INTERRUPT.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
void    SiiGotMhlIntr( uint8_t intr_0, uint8_t intr_1 ) //UT ZHOU
{
    SII_DBG_PRINT("MR_SET_INT: 0x%02X, 0x%02X\n", (int) intr_0, (int) intr_1);

    //
    // Handle DCAP_CHG INTR here
    //
    if (MHL_INT_DCAP_CHG & intr_0)
    {
        if (MHL_STATUS_DCAP_RDY & g_PlumTxConfig.status_0)
        {
            SiiRefreshPeerDevCapEntries(); 
        }
    }

    if (MHL_INT_DSCR_CHG & intr_0)
    {
        SiiProcessWriteBurstData(); 

        // remote WRITE_BURST is complete
        ClrMiscFlag(SiiGotMhlIntr, FLAGS_SCRATCHPAD_BUSY);
        AppNotifyMhlEvent(MHL_TX_EVENT_DSCR_CHG, 0);
    }

    if (MHL_INT_REQ_WRT & intr_0)
    {
        // this is a request from the sink device.
        if (FLAGS_SCRATCHPAD_BUSY & g_PlumTxConfig.miscFlags)
        {
            // use priority 1 to defer sending grant until
            //  local traffic is done
            SiiSetInt( MHL_RCHANGE_INT, MHL_INT_GRT_WRT, 1);
        }
        else
        {
            SetMiscFlag(SiiGotMhlIntr, FLAGS_SCRATCHPAD_BUSY);

            // OK to call this here, since all requests are queued
            // use priority 0 to respond immediately
            SiiSetInt( MHL_RCHANGE_INT, MHL_INT_GRT_WRT, 0);
        }
    }

    if (MHL_INT_GRT_WRT & intr_0)
    {
    }

    // removed "else", since interrupts are not mutually exclusive of each other.
    if (MHL_INT_EDID_CHG & intr_1)
    {
        // force upstream source to read the EDID again.
        // Most likely by appropriate togggling of HDMI HPD
        SiiDrvNotifyEdidChange ( );
        if(g_PlumTxConfig.mhlHpdRSENflags & MHL_HPD)
        {
            mhl_read_edid();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiGotMhlStatus
//
// This function is called by the driver to inform of arrival of a MHL STATUS.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//

/********************************************
 *Status register
 *
 *DCAP_RDY
 *
 *CLK_MODE
 *
 *PATH_EN
 *
 *MUTED
 *
 */
void    SiiGotMhlStatus( uint8_t status_0, uint8_t status_1 ) //UT ZHOU
{
    //
    // Handle DCAP_RDY STATUS here itself
    //
    uint8_t StatusChangeBitMask0, StatusChangeBitMask1;
    
    SII_DBG_PRINT("MhlTx: STATUS Arrived. 0x%02X, 0x%02X\n", (int) status_0, (int) status_1);
    SII_DBG_PRINT("MhlTx: Old status: 0x%02X, 0x%02X\n", 
                     (int) g_PlumTxConfig.status_0, (int) g_PlumTxConfig.status_1);

    StatusChangeBitMask0 = status_0 ^ g_PlumTxConfig.status_0;
    StatusChangeBitMask1 = status_1 ^ g_PlumTxConfig.status_1;

    // Remember the event.   (other code checks the saved values, so save the values early, but not before the XOR operations above)
    g_PlumTxConfig.status_0 = status_0;
    g_PlumTxConfig.status_1 = status_1;

    //did DCAP_RDY change?
    if (MHL_STATUS_DCAP_RDY & StatusChangeBitMask0)
    {
        SII_DBG_PRINT("MhlTx: DCAP_RDY changed\n");
        if (MHL_STATUS_DCAP_RDY & status_0)
        {
            SiiRefreshPeerDevCapEntries();  
        }
    }

    // did PATH_EN change?
    if (MHL_STATUS_PATH_ENABLED & StatusChangeBitMask1)
    {
        SII_DBG_PRINT("MhlTx: PATH_EN changed\n");
        if (MHL_STATUS_PATH_ENABLED & status_1)
        {
            // OK to call this here since all requests are queued
            SiiSetPathEn();
        }
        else
        {
            // OK to call this here since all requests are queued
            SiiClrPathEn();   // in case of power off the monitor
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiRcpSend
//
// This function checks if the peer device supports RCP and sends rcpKeyCode. The
// function will return a value of true if it could successfully send the RCP
// subcommand and the key code. Otherwise false.
//
// The followings are not yet utilized.
//
// (MHL_FEATURE_RAP_SUPPORT & g_PlumTxConfig.mscFeatureFlag))
// (MHL_FEATURE_SP_SUPPORT & g_PlumTxConfig.mscFeatureFlag))
//
//
bool SiiRcpSend( uint8_t rcpKeyCode )
{
    bool retVal;

    //
    // If peer does not support do not send RCP or RCPK/RCPE commands
    //

    if ((0 == (MHL_FEATURE_RCP_SUPPORT & g_PlumTxConfig.mscFeatureFlag))
        ||
        (!(FLAGS_RCP_READY & g_PlumTxConfig.miscFlags))
    )
    {
        SII_DBG_PRINT("MhlTx:SiiRcpSend failed\n");
        retVal = false;
    }

    retVal = SiiMhlTxSendMscMsg ( MHL_MSC_MSG_RCP, rcpKeyCode );
    if (retVal)
    {
        SII_DBG_PRINT("MhlTx:SiiRcpSend\n");
        IncrementCBusReferenceCount(SiiRcpSend)
        SiiMhlTxDriveStates();
    }

    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiRcpkSend
//
// This function sends RCPK to the peer device.
//
bool SiiRcpkSend( uint8_t rcpKeyCode )
{
    bool retVal;

    retVal = SiiMhlTxSendMscMsg(MHL_MSC_MSG_RCPK, rcpKeyCode);
    if (retVal)
    {
        SiiMhlTxDriveStates();
    }

    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiRapkSend
//
// This function sends RAPK to the peer device.
//
static bool SiiRapkSend( uint8_t rapkErrCode )
{
    bool retVal;

    retVal = SiiMhlTxSendMscMsg( MHL_MSC_MSG_RAPK, rapkErrCode);
    if (retVal)
    {
        SiiMhlTxDriveStates();
    }

    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiRcpeSend
//
// The function will return a value of true if it could successfully send the RCPE
// subcommand. Otherwise false.
//
// When successful, MhlTx internally sends RCPK with original (last known)
// keycode.
//
bool SiiRcpeSend( uint8_t rcpeErrorCode )
{
    bool retVal;

    retVal = SiiMhlTxSendMscMsg(MHL_MSC_MSG_RCPE, rcpeErrorCode);
    if (retVal)
    {
        SiiMhlTxDriveStates();
    }

    return retVal;
}

/*
///////////////////////////////////////////////////////////////////////////////
//
// SiiRapSend
//
// This function checks if the peer device supports RAP and sends rcpKeyCode. The
// function will return a value of true if it could successfully send the RCP
// subcommand and the key code. Otherwise false.
//

bool SiiRapSend( uint8_t rapActionCode )
{
bool retVal;
    if (!(FLAGS_RCP_READY & g_PlumTxConfig.miscFlags))
    {
        SII_DBG_PRINT( ("MhlTx:SiiRapSend failed\n"));
        retVal = false;
    }
    else
    {
        retVal = SiiMhlTxSendMscMsg ( MHL_MSC_MSG_RAP, rapActionCode );
        if(retVal)
        {
            IncrementCBusReferenceCount
            SII_DBG_PRINT( ("MhlTx: SiiRapSend\n"));
        }
    }
    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiGotMhlWriteBurst
//
// This function is called by the driver to inform of arrival of a scratchpad data.
//
// It is called in interrupt context to meet some MHL specified timings, therefore,
// it should not have to call app layer and do negligible processing, no printfs.
//
// Application shall not call this function.
//
void	SiiGotMhlWriteBurst( uint8_t *spadArray )
{
}
 */

///////////////////////////////////////////////////////////////////////////////
//
// SiiSetStatus
//
// Set MHL defined STATUS bits in peer's register set.
//
// register	    MHLRegister to write
//
// value        data to write to the register
//

static bool SiiSetStatus( uint8_t regToWrite, uint8_t value )
{
    cbus_req_t req;
    bool     retVal;

    req.retryCount           = 2;
    req.command              = MHL_WRITE_STAT;
    req.offsetData           = regToWrite;
    req.payload_u.msgData[0] = value;
    
    SII_DBG_PRINT("MhlTx:SiiSetStatus\n");
    retVal = PutNextCBusTransaction(&req);

    return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiSetDCapRdy
//
static bool SiiSetDCapRdy( void )
{
    g_PlumTxConfig.connectedReady |= MHL_STATUS_DCAP_RDY;   // update local copy
    return SiiSetStatus( MHL_STATUS_REG_CONNECTED_RDY, g_PlumTxConfig.connectedReady);
}

///////////////////////////////////////////////////////////////////////////////
//
//  SiiSendLinkMode
//
static bool SiiSendLinkMode(void)
{
    return SiiSetStatus( MHL_STATUS_REG_LINK_MODE, g_PlumTxConfig.linkMode);
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiSetPathEn
//
//See 7.9.3.2 about Link Mode Status
static bool SiiSetPathEn(void )
{
    SII_DBG_PRINT("MhlTx:SiiSetPathEn\n");
    
    //Sometimes  PATH_EN  in status register comes later than HPD.
    //So TMDS can't be enabled in HPD processor.
    SiiTmdsEnable();
	
    g_PlumTxConfig.linkMode |= MHL_STATUS_PATH_ENABLED;       // update local copy
    SiiSetStatus( MHL_STATUS_REG_LINK_MODE, g_PlumTxConfig.linkMode);
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiClrPathEn
//
//See 7.9.3.2 about Link Mode Status
bool SiiClrPathEn( void )
{
    SII_DBG_PRINT("MhlTx: SiiClrPathEn\n");
    
    SiiDrvTmdsControl( false );
    g_PlumTxConfig.linkMode &= ~MHL_STATUS_PATH_ENABLED;      // update local copy
    ClrMiscFlag(SiiClrPathEn, FLAGS_RCP_READY);
    ClrMiscFlag(SiiClrPathEn, FLAGS_SENT_PATH_EN);

    return SiiSetStatus( MHL_STATUS_REG_LINK_MODE, g_PlumTxConfig.linkMode);
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiReadDevcap
//
// This function sends a READ DEVCAP MHL command to the peer.
// It  returns true if successful in doing so.
//
// The value of devcap should be obtained by making a call to SiiGetEvents()
//
// offset		Which byte in devcap register is required to be read. 0..0x0E
//
bool SiiReadDevcap( uint8_t offset )
{
    cbus_req_t req;
    
    SII_DBG_PRINT("MhlTx:SiiReadDevcap\n");
    
    //
    // Send MHL_READ_DEVCAP command
    //
    req.retryCount = 2;
    req.command = MHL_READ_DEVCAP;
    req.offsetData = offset;
    req.payload_u.msgData[0] = 0;       // do this to avoid confusion

    return PutNextCBusTransaction(&req);
}

/*
 * SiiRefreshPeerDevCapEntries
 */

static void SiiRefreshPeerDevCapEntries(void)
{
    // only issue if no existing refresh is in progress
    if (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex >= DEVCAP_SIZE)
    {
        g_PlumTxConfig.devCapCache.ucDevCapCacheIndex = 0;
        SiiReadDevcap(0);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxSendMscMsg
//
// This function sends a MSC_MSG command to the peer.
// It  returns true if successful in doing so.
//
// The value of devcap should be obtained by making a call to SiiGetEvents()
//
// offset		Which byte in devcap register is required to be read. 0..0x0E
//
static bool SiiMhlTxSendMscMsg ( uint8_t command, uint8_t cmdData )
{
    cbus_req_t req;
    uint8_t ccode;

    //
    // Send MSC_MSG command
    //
    // Remember last MSC_MSG command (RCPE particularly)
    //
    req.retryCount = 2;
    req.command = MHL_MSC_MSG;
    req.payload_u.msgData[0] = command;
    req.payload_u.msgData[1] = cmdData;
    ccode = PutNextCBusTransaction(&req);
    return ((bool) ccode);
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiNotifyConnection
//
//
void SiiNotifyConnection( bool mhlConnected )
{
    int ret = 0;

    g_PlumTxConfig.mhlConnectionEvent = true;
    SII_DBG_PRINT("MhlTx: mhlConnected 0x%01X\n", (int) mhlConnected);

    if (mhlConnected)
    {
        g_PlumTxConfig.rapFlags |= RAP_CONTENT_ON;
        SII_DBG_PRINT("RAP CONTENT_ON\n");
        g_PlumTxConfig.mhlConnected = MHL_TX_EVENT_CONNECTION;
        g_PlumTxConfig.mhlHpdRSENflags |= MHL_RSEN;
        SiiTmdsEnable();
        SiiSendLinkMode();

        ret = mhl_rcp_register_input_dev();
        if (ret)
        {
            loge("register rcp input device error %d\n", ret);
        }
    }
    else
    {
        ret = mhl_rcp_unregister_input_dev();
        if (ret)
        {
            loge("unregister rcp input device error %d\n", ret);
        }

        g_PlumTxConfig.rapFlags &= ~RAP_CONTENT_ON;
        SII_DBG_PRINT("RAP CONTENT_OFF\n");
        g_PlumTxConfig.mhlConnected = MHL_TX_EVENT_DISCONNECTION;
        g_PlumTxConfig.mhlHpdRSENflags &= ~MHL_RSEN;
    }

    SiiMhlTxProcessEvents();
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiNotifyDsHpdChange
// Driver tells about arrival of SET_HPD or CLEAR_HPD by calling this function.
//
// Turn the content off or on based on what we got.
//
void    SiiNotifyDsHpdChange( uint8_t dsHpdStatus )
{
    int ret;
    
    if (0 == dsHpdStatus)
    {
        SII_DBG_PRINT("MhlTx: Disable TMDS\n");
        SII_DBG_PRINT("MhlTx: DsHPD OFF\n");
       
        g_PlumTxConfig.mhlHpdRSENflags &= ~MHL_HPD;

        ClrMiscFlag(SiiNotifyDsHpdChange, FLAGS_EDID_READ_DONE); 
        ClrMiscFlag(SiiNotifyDsHpdChange, FLAGS_RCP_READY);
        ClrMiscFlag(SiiNotifyDsHpdChange, FLAGS_SENT_PATH_EN);
      
        SiiDrvTmdsControl( false );
        
        // Set to DVI output mode to reset HDCP
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, TMDS_OUTPUT_MODE_MASK, TMDS_OUTPUT_MODE_DVI);

        /* Clear previoud edid for showing sysfs(edid)*/
        memset(edid, 0, sizeof(edid));
        hdmi.edid_set = false;
        
        CBusQueue.head = 0;
        CBusQueue.tail = 0;
        g_PlumTxConfig.cbusReferenceCount = 0;
        g_PlumTxConfig.status_0 = 0;
        g_PlumTxConfig.status_1 = 0;
    }
    else
    {
        SII_DBG_PRINT("MhlTx: Enable TMDS\n");
        SII_DBG_PRINT("MhlTx: DsHPD ON\n");
        
        g_PlumTxConfig.mhlHpdRSENflags |= MHL_HPD;

        /* HPD is available, so begin to read EDID */
        if (!hdmi.edid_set) {
            ret = mhl_read_edid();
            if (ret) {
                SII_ERR_PRINT("failed to read EDID!\n");
            }
        }
        
        //Enable TMDS ouput. Supposed RAP_CONTENT_ON.
        g_PlumTxConfig.rapFlags |= RAP_CONTENT_ON; 
        SiiTmdsEnable();
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiMhlTxResetStates
//
// Application picks up mhl connection and rcp events at periodic intervals.
// Interrupt handler feeds these variables. Reset them on disconnection.
//
void SiiMhlTxResetStates( void )
{    
    memset(&CBusQueue, 0, sizeof(CBusQueue_t));
    memset(&g_PlumTxConfig, 0, sizeof(mhlTx_config_t));    

    g_PlumTxConfig.mhlConnectionEvent = false;
    g_PlumTxConfig.mhlConnected = MHL_TX_EVENT_DISCONNECTION;
    g_PlumTxConfig.mhlHpdRSENflags &= ~(MHL_RSEN | MHL_HPD);
    g_PlumTxConfig.rapFlags &= ~RAP_CONTENT_ON;

    //SII_DBG_PRINT("RAP CONTENT_OFF\n");
    g_PlumTxConfig.mscMsgArrived = false;
    g_PlumTxConfig.mscMsgSubCommand = 0;

    g_PlumTxConfig.status_0 = 0;
    g_PlumTxConfig.status_1 = 0;
    g_PlumTxConfig.connectedReady = 0;
    g_PlumTxConfig.linkMode = MHL_STATUS_CLK_MODE_NORMAL;   // indicate normal (24-bit) mode

    // this can be overridden by the application calling SiiSetPreferredPixelFormat()
    g_PlumTxConfig.preferredClkMode   = MHL_STATUS_CLK_MODE_NORMAL;       
    g_PlumTxConfig.cbusReferenceCount = 0;
    g_PlumTxConfig.miscFlags = 0;
    g_PlumTxConfig.mscLastCommand = 0;
    g_PlumTxConfig.mscMsgLastCommand = 0;
    g_PlumTxConfig.mscLastData = 0;
    g_PlumTxConfig.devCapCache.ucDevCapCacheIndex = 1 + sizeof(g_PlumTxConfig.devCapCache.aucDevCapCache);
}

/*
    SiiReadConnectionStatus
    returns:
    0: if not fully connected
    1: if fully connected
 */
uint8_t    SiiReadConnectionStatus(void)
{
    return (uint8_t)((g_PlumTxConfig.mhlConnected >= MHL_TX_EVENT_RCP_READY) ? 1 : 0);
}

/*
  SiiSetPreferredPixelFormat

    clkMode - the preferred pixel format for the CLK_MODE status register

    Returns: 0 -- success
             1 -- failure - bits were specified that are not within the mask
 */
uint8_t SiiSetPreferredPixelFormat(uint8_t clkMode)//UT ZHOU
{
    if (~MHL_STATUS_CLK_MODE_MASK & clkMode)
    {
        return 1;
    }
    else
    {
        g_PlumTxConfig.preferredClkMode = clkMode;

        // check to see if a refresh has happened since the last call
        //   to SiiMhlTxResetStates()
        if (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex <= sizeof(g_PlumTxConfig.devCapCache.aucDevCapCache))
        {
            // check to see if DevCap cache update has already updated this yet.
            if (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex > DEVCAP_OFFSET_VID_LINK_MODE)
            {
                ExamineLocalAndPeerVidLinkMode();
            }
        }

        return 0;
    }
}

void SiiNotifyRgndMhl( void )
{
    /* we need app to set power state to full */
    AppNotifyMhlEvent(MHL_TX_EVENT_RGND_MHL, 0);

    SiiDrvProcessRgndMhl();
}


uint8_t SiiGetVICTableSize(void)
{
    return (sizeof(vicInfo) / sizeof(VIC_Info_t));
}

void SiiReportKeyCode(unsigned short keyCode)
{
        struct input_dev *pRcpDev = hdmi.rcp_dev;

        SII_DBG_PRINT("Keycode = 0x%02X\n",keyCode);

        input_report_key(pRcpDev, keyCode, 1); /* 1 means press down the key*/
        input_sync(pRcpDev);
        msleep(200);
/*        
        if ((keyCode == KEY_FASTFORWARD) || (keyCode == KEY_REWIND))
        {
            msleep(3000);
        }
*/
        input_report_key(pRcpDev, keyCode, 0); /* 0 means release the key*/
        input_sync(pRcpDev);
}

void SiiMapRcpToKey(unsigned short rcpValue, unsigned short *pKeyCode)
{
	SII_DBG_PRINT("rcpValue = 0x%02X\n", rcpValue);
    
	if ((NULL == pKeyCode) || (rcpValue >= RCP_CMD_MAX))
	{
		SII_DBG_PRINT("bad param rcpValue = 0x%02X, pKeyCode = %p \n", rcpValue, pKeyCode);
		return ;
	}
    
	*pKeyCode = rcpKeyMapTable[rcpValue];
	
	SII_DBG_PRINT("KeyCode = 0x%02X\n",*pKeyCode);
}

///////////////////////////////////////////////////////////////////////////////
//
// AppNotifyMhlEvent
//
//  This function is invoked from the MhlTx component to notify the application
//  about detected events that may be of interest to it.
//
// Application module must provide this function.
//
MhlTxNotifyEventsStatus_e AppNotifyMhlEvent(uint8_t eventCode, uint8_t eventParam) //UT ZHOU
{
    MhlTxNotifyEventsStatus_e retVal = MHL_TX_EVENT_STATUS_PASSTHROUGH;
#if DEBUG_VERSION        
    uint8_t i;
#endif
    unsigned short keyCode = KEY_RESERVED;

    SII_DBG_PRINT("eventCode: 0x%02X, eventParam: 0x%02X.\n", eventCode, eventParam);
    
    switch (eventCode)
    {
    case MHL_TX_EVENT_RGND_MHL:        
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_RGND_MHL\n");
        break;
    case MHL_TX_EVENT_DISCONNECTION:
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_DISCONNECTION\n");
        hdmi_process_cbus_connection(false);
        break;
    case MHL_TX_EVENT_CONNECTION:
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_CONNECTION\n");
        SiiSetPreferredPixelFormat(MHL_STATUS_CLK_MODE_NORMAL);
        break;
    case MHL_TX_EVENT_TMDS_ENABLED:
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_TMDS_ENABLE\n");           
        hdmi_process_tmds_status(true);        
        break;        
    case MHL_TX_EVENT_TMDS_DISABLED:
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_TMDS_DISABLED\n");
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, AV_MUTE_MASK, AV_MUTE_MUTED);    
        hdmi_process_tmds_status(false);
        break;
    case MHL_TX_EVENT_RCP_READY:
        SII_DBG_PRINT("App: Got event = MHL_TX_EVENT_RCP_READY\n");  

        //if (g_PlumTxConfig.bTmdsOutputEnabled) {
        //    SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, AV_MUTE_MASK, AV_MUTE_NORMAL);    
        //}

        SII_DBG_PRINT("TPI_0x1A is 0x%02x\n", SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR));
        break;
    case MHL_TX_EVENT_RCP_RECEIVED:
	    SiiMapRcpToKey(eventParam, &keyCode);
        SiiReportKeyCode(keyCode); /* report the key to App */
        
        // Check if we got an RCP. Application can perform the operation here
        // and send RCPK or RCPE. For now, we send the RCPK
        SII_DBG_PRINT("App: Received an RCP key code = 0x%02X\n", (int)eventParam);
        SiiRcpkSend(eventParam);
        break;
    case MHL_TX_EVENT_RCPK_RECEIVED:
        SII_DBG_PRINT("App: Received an RCPK = 0x%02X\n", (int)eventParam);
        break;
    case MHL_TX_EVENT_RCPE_RECEIVED:
        SII_DBG_PRINT("App: Received an RCPE = 0x%02X\n", (int)eventParam);
        break;
    case MHL_TX_EVENT_DCAP_CHG:
        SII_DBG_PRINT("App: MHL_TX_EVENT_DCAP_CHG, DEV_CAP(16 bytes): \n ");
#if DEBUG_VERSION        
        /* print all of device cap if the process is finished */
        if (g_PlumTxConfig.devCapCache.ucDevCapCacheIndex == DEVCAP_SIZE) {
            for (i = 0; i < DEVCAP_SIZE; i++)
            {
                /* use printk for easy read format. */
                printk("0x%02X ", g_PlumTxConfig.devCapCache.aucDevCapCache[i]);
            }            
        }
        
        printk("\n");
#endif        
        break;
    case MHL_TX_EVENT_POW_BIT_CHG:
        // handle the LEDs here
        if (eventParam)
        {
            // POW bit 0->1 transition
            //pinSourceVbusOn = 0;
        }
        else
        {
            // POW bit 1->0 transition
            // do nothing
        }
        // Let the lower layers handle the rest.
        break;
    case MHL_TX_EVENT_DSCR_CHG:
        SII_DBG_PRINT("App: MHL_TX_EVENT_DSCR_CHG: \n");
        break;
    default:
        SII_DBG_PRINT("Unknown event: 0x%02x\n", (int)eventCode);
        break;
    }

    return retVal;
}

#if USE_PP_MODE
#define DEVCAP_REFRESH_ONCE     (g_PlumTxConfig.ucDevCapCacheIndex <= DEVCAP_SIZE)
typedef struct _TimingModeFromDataSheet_t
{
    uint16_t hTotal;
    uint16_t vTotal;
    uint32_t pixelClock;
    struct
    {
    uint8_t interlaced:1;
    uint8_t reserved:7;
    }flags;
}TimingModeFromDataSheet_t,*PTimingModeFromDataSheet_t;


TimingModeFromDataSheet_t timingModesFromDataSheet[]=
{
     { 800, 525, 25175000,{0,0}}
    ,{1088, 517, 33750000,{0,0}}
    ,{1056, 628, 40000000,{0,0}}
    ,{1344, 806, 65000000,{0,0}}
    ,{1716, 262, 27000000,{1,0}}// DS has VTOTAL for progressive
    ,{1728, 312, 27000000,{1,0}}// DS has VTOTAL for progressive
    ,{ 858, 525, 27000000,{0,0}}
    ,{ 864, 625, 27000000,{0,0}}
    ,{1650, 750, 74250000,{0,0}}
    ,{2200, 562, 74250000,{1,0}}// DS has VTOTAL for progressive
    ,{2750,1125, 74250000,{0,0}}
    ,{2640,1125,148500000,{0,0}}
    ,{2200,1125,148500000,{0,0}}
};

uint32_t SiiMhlTxFindTimingsFromTotals( void )
{
    uint32_t retVal=0;
    uint8_t i;
    uint16_t hTotal, vTotal;
    // Measure the HTOTAL and VTOTAL and look them up in a table
    hTotal = SiiMhlTxDrvGetIncomingHorzTotal();
    vTotal = SiiMhlTxDrvGetIncomingVertTotal();
    for (i = 0 ; i < sizeof(timingModesFromDataSheet)/sizeof(timingModesFromDataSheet[0]); ++i)
    {
        if (timingModesFromDataSheet[i].hTotal == hTotal)
        {
            if (timingModesFromDataSheet[i].vTotal == vTotal)
            {
                retVal = timingModesFromDataSheet[i].pixelClock;
                break;
            }
        }
    }
    SII_DBG_PRINT(("VIC was zero!!! hTotal: 0x%04x vTotal:0x%04x\n",hTotal,vTotal));
    return retVal;
}


/*
  SiiMhlTxSetPreferredPixelFormat

	clkMode - the preferred pixel format for the CLK_MODE status register

	Returns: 0 -- success
		     1 -- failure - bits were specified that are not within the mask
 */
uint8_t SiiMhlTxSetPreferredPixelFormat(uint8_t clkMode)
{
	if (~MHL_STATUS_CLK_MODE_MASK & clkMode)
	{
        // bits were specified that are not within the mask
		return 1;
	}
	else
	{
     	g_PlumTxConfig.preferredClkMode = clkMode;

		// check to see if a refresh has happened since the last call
		//   to MhlTxResetStates()
     	if (DEVCAP_REFRESH_ONCE)
     	{
           	// check to see if DevCap cache update has already updated this yet.
      		if (g_PlumTxConfig.ucDevCapCacheIndex > DEVCAP_OFFSET_VID_LINK_MODE)
      		{
              	ExamineLocalAndPeerVidLinkMode();
      		}
     	}
		return 0;
	}
}


uint8_t	SiiMhlTxAttemptPackedPixel( void )
{
    uint32_t threeDPixelClockRatio = 1;
    uint32_t pixelClockFrequency   = 0;
    uint8_t  packedPixelNeeded     = 0;
    uint8_t  retVal                = 0;

    SII_DBG_PRINT("Mhl2Tx: SiiMhlTxAttemptPackedPixel\n");
    SiiMhlTxSetPreferredPixelFormat(MHL_STATUS_CLK_MODE_NORMAL);

    if ((VideoModeDescription.HDMIVideoFormat == 0x01)
        &&(VideoModeDescription.ThreeDStructure == VMD_3D_FRAMEPACKING)) //Frame Packing 3D format present--see MHL spec 5.9.2
    {
        SII_DBG_PRINT(("MhlTx: tdsFramePacking\n"));
        threeDPixelClockRatio = 2;
        SiiMhlTxDrvSet3DMode(1,tdsFramePacking);        
    }
    else
    {
        SII_DBG_PRINT(("MhlTx: NOT tdsFramePacking\n"));
        SiiMhlTxDrvSet3DMode(0,0);
    }

    if(VideoModeDescription.VIC != 0)
    {
        SII_DBG_PRINT(("Mhl2Tx: Packed Pixel Available checking VIC:%d\n",(uint16_t)VideoModeDescription.VIC));
        // look at the incoming info frame to the the VIC code
        pixelClockFrequency = CalculatePixelClock((uint16_t)vicInfo[VideoModeDescription.VIC].columns, (uint16_t)vicInfo[VideoModeDescription.VIC].rows
                                                , (uint32_t)vicInfo[VideoModeDescription.VIC].fieldRateInMilliHz,VideoModeDescription.VIC);
    }
    else
    {
        pixelClockFrequency = SiiMhlTxFindTimingsFromTotals();
    }
     
    // make decision about packed pixel mode here
    if (0 == pixelClockFrequency)
    {
        SII_DBG_PRINT(("VIC was zero and we could not identify incoming timing mode,\n"
            "\tdefaulting to non-packed pixel\n"
            "\thTotal: %04x\n"
            "\tvTotal: %04x\n\n"
            ,SiiMhlTxDrvGetIncomingHorzTotal()
            ,SiiMhlTxDrvGetIncomingVertTotal()
            ));
        packedPixelNeeded=0;
    }
    else
    {
        pixelClockFrequency *= threeDPixelClockRatio;
        SII_DBG_PRINT(("Mhl2Tx: pixel clock:%lu\n",pixelClockFrequency));

        if (QualifyPixelClockForMhl(pixelClockFrequency, 24))
        {
            SII_DBG_PRINT(("Drv: OK for 24 bit pixels\n"));
        }
        else
        {
            if(SinkSupportYCbCr422()) 
        	{
                SII_DBG_PRINT(("Mhl2Tx: YCbCr422 support!\n"));
                if (QualifyPixelClockForMhl(pixelClockFrequency, 16))
                {
                    // enough for packed pixel
                    packedPixelNeeded=1;
                }
                else
                {
                    SII_DBG_PRINT(("Drv: We really can't do this display timing mode\n"));
                }
        	}
        }
    }
    SiiMhlTxDrvSetPixelClockFrequency(pixelClockFrequency);
    
    SiiMhlTxDrvSetPackedPixelStatus( 0 );
    if (PackedPixelAvailable)
    {
        if (packedPixelNeeded)
        {
            SII_DBG_PRINT(("setting packed pixel mode\n"));
            VideoModeDescription.OutputColorSpace = COLOR_SPACE_YCBCR422;    
            SiiMhlTxSetPreferredPixelFormat(MHL_STATUS_CLK_MODE_PACKED_PIXEL);
            SiiMhlTxDrvSetPackedPixelStatus( 1 );
        }
    }
    
    SiiMhlTxDrvApplyPPModeSettings();

    SiiSendLinkMode();
    retVal = 1;
    return retVal;
}
#endif


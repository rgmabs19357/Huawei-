/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_drv_mhl_tx.c
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/io.h>
#include "si_mhl_main.h"
#include "si_reg_access.h"
#include "si_drv_mhl_tx.h"
#include "si_mhl_tx.h"
#include "si_mhl_hw.h"
#include "si_hdcp.h"

#ifdef CONFIG_MHL_USB_SHARE
#include <linux/usb/balong/hisi_susb.h>
#endif

extern hdmi_hw_res hw_res;
extern hdmi_device hdmi;
extern mhlTx_config_t g_PlumTxConfig;
extern bool HDCP_Started;

#if USE_PP_MODE
static uint8_t packedPixelStatus = 0;
static uint32_t pixelClockFrequency = 0;
#endif

static void InitCBusRegs (void);
static void MhlTxDrvProcessConnection ( void );
static void MhlTxDrvProcessDisconnection ( void );
static void ProcessRgnd (void);
#if USE_3D
static void Send_VSIF(void);
#endif
static void WriteInitialRegisterValues ( void );
extern int mhl_phy_write_reg(u8 reg, u8 val);
extern int fsa9685_manual_detach(void);

//
// To serialize the RCP commands posted to the CBUS engine, this flag
// is maintained by the function SiiDrvSendCbusCommand()
//
// false when it is okay to send a new command
bool mscAbortFlag = false;

//
// Preserve Downstream HPD status
//
static uint8_t dsHpdStatus = 0;

uint8_t devCap[DEVCAP_SIZE] =
{
    DEVCAP_VAL_DEV_STATE,
    DEVCAP_VAL_MHL_VERSION,
    DEVCAP_VAL_DEV_CAT,
    DEVCAP_VAL_ADOPTER_ID_H,
    DEVCAP_VAL_ADOPTER_ID_L,
    DEVCAP_VAL_VID_LINK_MODE,
    DEVCAP_VAL_AUD_LINK_MODE,
    DEVCAP_VAL_VIDEO_TYPE,
    DEVCAP_VAL_LOG_DEV_MAP,
    DEVCAP_VAL_BANDWIDTH,
    DEVCAP_VAL_FEATURE_FLAG,
    DEVCAP_VAL_DEVICE_ID_H,
    DEVCAP_VAL_DEVICE_ID_L,
    DEVCAP_VAL_SCRATCHPAD_SIZE,
    DEVCAP_VAL_INT_STAT_SIZE,
    DEVCAP_VAL_RESERVED
};

/* only in HDMI mode */
void SiiDrvVideoMute( void )
{
    byte Temp;

    Temp = SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR);     // Read the current value of the register.
    if ((Temp & AV_MUTE_MASK) == AV_MUTE_MUTED)
    {
        SII_DBG_PRINT("AV has been Muted.\n");
        //Muted
        return;
    }
    else //UnMuted
    {
        Temp &= ~AV_MUTE_MASK;
        Temp |= AV_MUTE_MASK & AV_MUTE_MUTED;
        SiiDrvWriteByteTPI(TPI_SYSTEM_CTRL_ADDR, Temp);      // Write new value back to register.
        SII_DBG_PRINT("AV Muted.\n");
        return;
    }
}

void    SiiDrvVideoUnmute( void )
{
    byte Temp;

    Temp = SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR);     // Read the current value of the register.
    if ((Temp & AV_MUTE_MASK) == AV_MUTE_NORMAL)
    {
        SII_DBG_PRINT("AV has been unMuted.\n");
        //UnMuted
        return;
    }
    else //Muted
    {
        Temp &= ~AV_MUTE_MASK;
        Temp |= AV_MUTE_MASK & AV_MUTE_NORMAL;
        SiiDrvWriteByteTPI(TPI_SYSTEM_CTRL_ADDR, Temp);      // Write new value back to register.
        SII_DBG_PRINT("AV UnMuted.\n");
        return;
    }
}

/******************************************************************************
* Function:       check_registers_default_value
* Description:    check register's default value after initialization
* Input:
* Output:
* Return:         true for success, false for fail
*******************************************************************************/
static bool check_registers_default_value(void)
{
    uint8_t reg1_value = 0;
    uint8_t reg2_value = 0;

    /* After initialization the system is under hardware TPI mode */

    reg1_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_LM_DDC_ADDR);
    if ((reg1_value & 0x80) != 0) {
        SII_ERR_PRINT("page0_0xc7[7] is %d, it should be 0 in HW TPI.\n", (reg1_value & 0x80));
        goto err;
    }

    /* check whether it is hardware TPI mode */
    reg1_value = SiiDrvRegRead(MHL_TPI_SYS, TPI_DEV_ID_ADDR);
    reg2_value = SiiDrvRegRead(MHL_TPI_SYS, TPI_VENDOR_B3_ADDR);
    if ((0xB4 != reg1_value) || (0x30 != reg2_value)) {
        SII_ERR_PRINT("error: not hardware TPI mode.\n");
        SII_ERR_PRINT("TPI_DEV_ID is 0x%02x, TPI_VENDOR_B3 is 0x%02x\n", reg1_value, reg2_value);
        goto err;
    }

    /* check device ID registers in page0 */
    reg1_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_DEV_IDL_ADDR);
    reg2_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_DEV_IDH_ADDR);
    if ((0x34 != reg1_value) || (0x93 != reg2_value)) {
        SII_ERR_PRINT("page0 register(DEVICE_ID) error.\n");
        SII_ERR_PRINT("P0_DEV_IDL is 0x%02x, P0_DEV_IDH is 0x%02x\n", reg1_value, reg2_value);
        goto err;
    }

    /* check power down register in page1 */
    reg1_value = SiiDrvReadIndexedRegister(INDEXED_PAGE_1, P1_DPD_ADDR);
    if (0x17 != reg1_value) {
        SII_ERR_PRINT("page1 register(DPD) error, its value is 0x%02x.\n", reg1_value);
        goto err;
    }

    /* check XXX register in page2 */

    /* check devcap adopter id register in cbus */
    reg1_value = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_MHL_DEVCAP_0_F_ADDR + 3*4);
    reg2_value = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_MHL_DEVCAP_0_F_ADDR + 4*4);
    if ((DEVCAP_VAL_ADOPTER_ID_H != reg1_value) || (DEVCAP_VAL_ADOPTER_ID_L != reg2_value)) {
        SII_ERR_PRINT("CBUS register(devcap adopter id) error.\n");
        SII_ERR_PRINT("ADOPTER_ID_H is 0x%02x, ADOPTER_ID_L is 0x%02x\n", reg1_value, reg2_value);
        goto err;
    }

    /* check CHIP_ID register in hare28hpm phy */
#ifdef CONFIG_MACH_HI6620OEM
    reg1_value = SiiDrvRegRead(MHL_PHY_BASE, PHY_DM_TX_CHIP_ID_ADDR);
    if (0xA0 != reg1_value) {
        SII_ERR_PRINT("PHY register(chip id) error, its value is 0x%02x.\n", reg1_value);
        goto err;
    }
#endif /* CONFIG_MACH_HI6620OEM */

    return true;

err:
    return false;
}

//////////////////////////////////////////////////////////////////////////////
//
// SiiChipInitialize
//
// Chip specific initialization.
//
//////////////////////////////////////////////////////////////////////////////

void SiiChipInitialize ( void )
{
    g_PlumTxConfig.mscCmdInProgress = false;   // false when it is okay to send a new command
    dsHpdStatus                     = 0;
    mscAbortFlag                    = false;

#if USE_PP_MODE
    packedPixelStatus   = 0;
    pixelClockFrequency = 0;
#endif
    // setup device registers. Ensure RGND interrupt would happen.
    WriteInitialRegisterValues();
    InitCBusRegs();  //Write DEV_CAP

    /* only for debug to check whether the registers initialization is right */
    if (check_registers_default_value()) {
        SII_DBG_PRINT("MHL register initialization success.\n");
    }
    else {
        SII_ERR_PRINT("MHL register initialization failed.\n");
    }

    return;
}

void enable_mhl_interrupts(void)
{
    UNMASK_INTR_4_INTERRUPTS;
    UNMASK_CBUS_MSC_INTERRUPTS;
    UNMASK_CBUS_MSC_ERR_INTERRUPTS;
    UNMASK_CBUS_DDC_ABORT_INTERRUPTS;
    UNMASK_CBUS_SEND_ERR_INTERRUPTS;
    UNMASK_CBUS_RCV_ERR_INTERRUPTS;
    UNMASK_CBUS_MHL_INT0_INTERRUPTS;
    UNMASK_CBUS_MHL_INT1_INTERRUPTS;
#if USE_HDCP
    UNMASK_HDCP_INTERRUPTS;
#endif
}

void clear_mhl_interrupts(void)
{
	CLEAR_INTR_4_INTERRUPTS;
	CLEAR_CBUS_MSC_INTERRUPTS;
	CLEAR_CBUS_MSC_ERR_INTERRUPTS;
	CLEAR_CBUS_DDC_ABORT_INTERRUPTS;
	CLEAR_CBUS_SEND_ERR_INTERRUPTS;
	CLEAR_CBUS_RCV_ERR_INTERRUPTS;
	CLEAR_CBUS_MHL_INT0_INTERRUPTS;
	CLEAR_CBUS_MHL_INT1_INTERRUPTS;
#if USE_HDCP
    CLEAR_HDCP_INTERRUPTS;
#endif
}

void dump_mhl_interrupts_state(void)
{
	SII_DBG_PRINT("Intr 4 state: 0x%02x\n",
		SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P2_INTR4_ADDR));
	SII_DBG_PRINT("CBUS_0 int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_ADDR));
	SII_DBG_PRINT("CBUS_1 int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_ADDR));
	SII_DBG_PRINT("DDC abort int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_DDC_ABORT_INTR_ADDR));
	SII_DBG_PRINT("MSC_SEND_ERR int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_ADDR));
	SII_DBG_PRINT("MSC_RCV_ERR int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_ADDR));
	SII_DBG_PRINT("MHL_INT0 int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_MHL_INT_0_ADDR));
	SII_DBG_PRINT("MHL_INT1 int state: 0x%02x\n",
		SiiDrvRegRead(MHL_CBUS_BASE, CBUS_MHL_INT_1_ADDR));
}

///////////////////////////////////////////////////////////////////////////////
// SiiDeviceIsr
//
// This function must be called from a master interrupt handler or any polling
// loop in the host software if during initialization call the parameter
// interruptDriven was set to true. SiiGetEvents will not look at these
// events assuming firmware is operating in interrupt driven mode. MhlTx component
// performs a check of all its internal status registers to see if a hardware event
// such as connection or disconnection has happened or an RCP message has been
// received from the connected device. Due to the interruptDriven being true,
// MhlTx code will ensure concurrency by asking the host software and hardware to
// disable interrupts and restore when completed. Device interrupts are cleared by
// the MhlTx component before returning back to the caller. Any handling of
// programmable interrupt controller logic if present in the host will have to
// be done by the caller after this function returns back.

// This function has no parameters and returns nothing.

void SiiDeviceIsr( void )//UT XU
{
    uint8_t intMStatus, i = 0;
    
    do
    {
        if (I2C_ACCESSIBLE == Int4Isr())
        {
            MhlCbusIsr();
#if USE_HDCP
            SiiHDCP_CheckStatus();
#endif
            SiiMhlTxProcessEvents();
        }

        intMStatus = SiiDrvReadIndexedRegister(INDEXED_PAGE_0, P0_INTR_STATE_ADDR);
        SII_DBG_PRINT("ISR: i:%d, intMStatus:0x%02x \n", i, intMStatus);

		if (0xFF == intMStatus)
        {
            intMStatus = 0;
            SII_WRN_PRINT("Drv: EXITING ISR DUE TO intMStatus - 0xFF.\n");
        }

        i++;

        intMStatus &= 0x01;                 //RG mask bit 0
        if (i > 60)
        {
            SII_WRN_PRINT("force exit SiiDeviceIsr \n");
            break;
        }
        else if (i > 50)
        {
            SII_WRN_PRINT("something error in SiiDeviceIsr, and clear all interrupts! \n");
			dump_mhl_interrupts_state();
			clear_mhl_interrupts();
        }
    } while (intMStatus);
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiDrvTmdsControl
//
// Control the TMDS output. MhlTx uses this to support RAP content on and off.
//
void SiiDrvTmdsControl (bool enable)//UT XU
{
    IN_FUNCTION;

    if (enable == g_PlumTxConfig.bTmdsOutputEnabled)
    {
        SII_DBG_PRINT("TMDS output status not change, don't set.\n");
        return;
    }

    if (enable)
    {
        g_PlumTxConfig.bTmdsOutputEnabled = true;

        if (IsHDMI_Sink())
        {
            //SiiDrvWriteByteTPI(0x0a*4, 0x01);  //for YUV 4/4/4
            SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, BIT0, BIT0);     //HDMI output
            //To make sure this bit is set correctly.
            SiiDrvModifyIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR, BIT0, BIT0);
        }
        else
        {
            SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, BIT0, 0x00);                 //DVI output
        }

        SiiDrvModifyIndexedRegister(INDEXED_PAGE_0, P0_TMDS_CCTRL_ADDR, TMDS_OE, SET_BITS);
        /* P0_0x80[4] is same with TPI_0x1A[4] */

        SiiDrvHDCP_ToggleTmdsForHdcpAuthentication();
        
        SII_INF_PRINT("TMDS Output Enabled(muted).\n");        
        SII_DBG_PRINT("TPI_0x1A is 0x%02x\n", SiiDrvReadByteTPI(TPI_SYSTEM_CTRL_ADDR));

        AppNotifyMhlEvent(MHL_TX_EVENT_TMDS_ENABLED, 0);

#if USE_HDCP
        /* When MHL cable is disconnected, TPI_0x3c will be modified to 0x0 from 0xA0 
           by unknow thing. To resolving it we set it again once TMDS output is enabled. */
        UNMASK_HDCP_INTERRUPTS;
#endif
    }
    else
    {
        g_PlumTxConfig.bTmdsOutputEnabled = false;

#if USE_HDCP
        SiiDrvHDCP_Off();
#endif

        AppNotifyMhlEvent(MHL_TX_EVENT_TMDS_DISABLED, 0);

        SII_DBG_PRINT("TMDS Output Disabled\n");
    }

    OUT_FUNCTION;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiDrvNotifyEdidChange
//
// MhlTx may need to inform upstream device of an EDID change. This can be
// achieved by toggling the HDMI HPD signal or by simply calling EDID read
// function.
//
void SiiDrvNotifyEdidChange ( void )
{
    SII_DBG_PRINT("SiiDrvNotifyEdidChange\n");
}

//------------------------------------------------------------------------------
// Function:    SiiDrvSendCbusCommand
//
// Write the specified Sideband Channel command to the CBUS.
// Command can be a MSC_MSG command (RCP/RAP/RCPK/RCPE/RAPK), or another command
// such as READ_DEVCAP, SET_INT, WRITE_STAT, etc.
//
// Parameters:
//              pReq    - Pointer to a cbus_req_t structure containing the
//                        command to write
// Returns:     true    - successful write
//              false   - write failed
//------------------------------------------------------------------------------

bool SiiDrvSendCbusCommand ( cbus_req_t * pReq  )//UT zhou
{
    bool success = true;

    uint8_t i, startbit;

    // Now we are getting busy
    g_PlumTxConfig.mscCmdInProgress = true;

    SII_DBG_PRINT("Sending MSC command 0x%02X, 0x%02X, 0x%02X\n",
                       (int)pReq->command,
                       (int)((MHL_MSC_MSG == pReq->command) ?
                            pReq->payload_u.msgData[0] : pReq->offsetData),
                       (int)((MHL_MSC_MSG == pReq->command) ?
                            pReq->payload_u.msgData[1] : pReq->payload_u.msgData[0]));

    /****************************************************************************************/
    /* Setup for the command - write appropriate registers and determine the correct        */
    /*                         start bit.                                                   */
    /****************************************************************************************/

    // Set the offset and outgoing data byte right away
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_CMD_OR_OFFSET_ADDR, pReq->offsetData);                     // set offset
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_DATA1_ADDR, pReq->payload_u.msgData[0]);

    startbit = 0x00;
    switch (pReq->command)
    {
    case MHL_SET_INT:                     // Set one interrupt register = 0x60
        startbit = MSC_START_BIT_WRITE_REG;
        break;

    case MHL_WRITE_STAT:                     // Write one status register = 0x60 | 0x80
        startbit = MSC_START_BIT_WRITE_REG;
        break;

    case MHL_READ_DEVCAP:                     // Read one device capability register = 0x61
        startbit = MSC_START_BIT_READ_REG;
        break;

    case MHL_GET_STATE:                     // 0x62 -
    case MHL_GET_VENDOR_ID:                     // 0x63 - for vendor id
    case MHL_SET_HPD:                     // 0x64	- Set Hot Plug Detect in follower
    case MHL_CLR_HPD:                     // 0x65	- Clear Hot Plug Detect in follower
    case MHL_GET_SC1_ERRORCODE:                     // 0x69	- Get channel 1 command error code
    case MHL_GET_DDC_ERRORCODE:                     // 0x6A	- Get DDC channel command error code.
    case MHL_GET_MSC_ERRORCODE:                     // 0x6B	- Get MSC command error code.
    case MHL_GET_SC3_ERRORCODE:                     // 0x6D	- Get channel 3 command error code.
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_CMD_OR_OFFSET_ADDR, pReq->command );
        startbit = MSC_START_BIT_MSC_CMD;
        break;

    case MHL_MSC_MSG:
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_DATA2_ADDR, pReq->payload_u.msgData[1] );
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_CMD_OR_OFFSET_ADDR, pReq->command );
        startbit = MSC_START_BIT_VS_CMD;
        break;

    case MHL_WRITE_BURST:
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_WRITE_BURST_DATA_LEN_ADDR, pReq->length - 1 );

        // Now copy all bytes from array to local scratchpad
        if (NULL == pReq->payload_u.pdatabytes)
        {
            SII_DBG_PRINT("\nPut pointer to WRITE_BURST data in req.pdatabytes!!!\n\n");

            success = false;
        }
        else
        {
            uint8_t *pData = pReq->payload_u.pdatabytes;

            SII_DBG_PRINT("\nWriting data into scratchpad\n\n");
            for (i = 0; i < pReq->length; i++)
            {
                SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_MHL_SCRPAD_0_F_ADDR + i*4, *pData++ );
            }

            startbit = MSC_START_BIT_WRITE_BURST;
        }

        break;

    default:
        success = false;
        break;
    }

    /****************************************************************************************/
    /* Trigger the CBUS command transfer using the determined start bit.                    */
    /****************************************************************************************/

    if (success)
    {
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_CMD_START_ADDR, startbit );
    }
    else
    {
        SII_WRN_PRINT("\nSiiDrvSendCbusCommand failed\n\n");
    }

    return (success);
}

bool SiiDrvCBusBusy(void)
{
    return g_PlumTxConfig.mscCmdInProgress ? true : false;
}

/******************************************************************************
* Function:       initial_hare28hpm_phy
* Description:    Initialize hare28hpm mhl phy according the document
* Input:
* Output:
* Return:
*******************************************************************************/
static void initial_hare28hpm_phy ( void )
{
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_PLL_CTRL_ADDR, 0x4A);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_DM_TX_CTRL1_ADDR, 0x03);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_DM_TX_CTRL3_ADDR, 0x81);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_DM_TX_CTRL4_ADDR, 0x35);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_DM_TX_CTRL5_ADDR, 0x84);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_HDMI_DRV_CTRL_ADDR, 0x02);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_MHL_DRV_CTRL_ADDR, 0x10);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_MHL_CTRL2_ADDR, 0x0A);
}

/******************************************************************************
* Function:       enable_phy_rgnd_measurement
* Description:    Current ASIC platform has a bug that page2_0x4c is not the 1K
                  after received the RGND interrupt.
                  So we have to enable mhl phy to measure ground resistor again.
* Input:
* Output:
* Return:
*******************************************************************************/
static void enable_phy_rgnd_measurement(void)
{
    /* select cbus_pup_sel[1:0] of reg_0x15 and select cbus_meas_rgnd_en of reg_0x13*/
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_MEAS_RGND_CTRL2_ADDR, 0x32);

    /* disable pull up resistor */
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_DRV_CTRL_ADDR, 0x08);

    /* Set the calibration[4:2]=b'111 and then disable rgnd measurement */
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_MEAS_RGND_CTRL1_ADDR, 0x1C);

    /* Set the calibration[4:2]=b'111 and then enable rgnd measurement */
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_MEAS_RGND_CTRL1_ADDR, 0x1D);

    msleep(1);
}

/******************************************************************************
* Function:       disable_phy_rgnd_measurement
* Description:    restore mhl phy to default vaule after finishing measurement
* Input:
* Output:
* Return:
*******************************************************************************/
static void disable_phy_rgnd_measurement(void)
{
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_MEAS_RGND_CTRL2_ADDR, 0x02);
    SiiDrvRegWrite(MHL_PHY_BASE, PHY_CBUS_DRV_CTRL_ADDR, 0x0A);
}

///////////////////////////////////////////////////////////////////////////
// WriteInitialRegisterValues
//
//
///////////////////////////////////////////////////////////////////////////
static void WriteInitialRegisterValues ( void )
{
    /* enter hardware TPI mode, page0_0xC7=0x00 */
    SiiDrvRegWrite(MHL_CORE_SYS, P0_LM_DDC_ADDR, 0x00);

#ifdef CONFIG_MACH_HI6620OEM
    initial_hare28hpm_phy();
#endif

    /* enable MHL mode of plum core, p0_0xff[7]=0 */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, PO_REG_BANK0_ADDR, 0x00);
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, 0x2F*4, 0x01);    //Enable Audio

#ifdef CONFIG_MACH_HI6620SFT
    /* skip RGND detection in FPGA platform */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL2_ADDR, 0xED);
#endif

    /* cbus pull up 5k in mhl state, p2_0x44[1:0]=2'b11 */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL5_ADDR, 0x53);

    // cbus pull up 10k in idle state, p2_0x43[5:4]=2'b10
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL4_ADDR, 0xA4);

    /* enalbe MHL discovery, p2_0x40[0]=1 */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL1_ADDR, 0x27);

    /* Set DDC master frequency  =   100k */
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_0, P0_DDC_DELAY_CNT_ADDR, 0x28);

    SiiDrvVideoMute();

    /* enable int: set interested bit to 1 in mask register */
	enable_mhl_interrupts();
}

///////////////////////////////////////////////////////////////////////////
// InitCBusRegs
//
///////////////////////////////////////////////////////////////////////////
static void InitCBusRegs (void)
{
    // Setup our devcap
    // make devcap loading quicker by using block write
    SiiDrvRegWriteBlock(MHL_CBUS_BASE, CBUS_MHL_DEVCAP_0_F_ADDR, devCap, sizeof(devCap));
}

/*
    SiiDrvProcessRgndMhl
        optionally called by the MHL Tx Component after giving the OEM layer the
        first crack at handling the event.
 */
void SiiDrvProcessRgndMhl( void )
{
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL9_ADDR, BIT0, BIT0);
}

///////////////////////////////////////////////////////////////////////////
// ProcessRgnd
//
// H/W has detected impedance change and interrupted.
// We look for appropriate impedance range to call it MHL and enable the
// hardware MHL discovery logic. If not, disable MHL discovery to allow
// USB to work appropriately.
//
// In current chip a firmware driven slow wake up pulses are sent to the
// sink to wake that and setup ourselves for full D0 operation.
///////////////////////////////////////////////////////////////////////////
static void ProcessRgnd (void)
{
    uint8_t rgndImpedance_phy, rgndImpedance_ctrl;
    
    enable_phy_rgnd_measurement();

    // Impedance detection has completed - process interrupt
    rgndImpedance_phy  = 0x03 & (SiiDrvRegRead(MHL_PHY_BASE, PHY_CBUS_STAT_ADDR) >> 1);
    rgndImpedance_ctrl = 0x03 & SiiDrvReadIndexedRegister(INDEXED_PAGE_2, P2_DISC_STAT2_ADDR);

    disable_phy_rgnd_measurement();

    /* We'd better use phy's measurement */
    g_PlumTxConfig.cbusImpedance = rgndImpedance_phy;

    SII_DBG_PRINT("RGND_CTRL = 0x%02X, RGND_PHY = 0x%02X \n",
                     (int)rgndImpedance_ctrl, (int)rgndImpedance_phy);

    // 00, 01 or 11 means USB.
    // 10 means 1K impedance (MHL)
    // If 1K, then only proceed with wake up pulses
    if (0x02 == rgndImpedance_phy)
    {
        SII_DBG_PRINT("(MHL Device)\n");

        /* Must switch to MHL in this moment.
           It's too late if we switch to MHL in MHL_EST interrupt */
#ifdef CONFIG_MHL_USB_SHARE
        switch_mhl();
#endif
    }
    else if (0x03 == rgndImpedance_phy)
    {
        SII_DBG_PRINT("(USB OTG Device)\n");

        /* A new wake lock during 2 second for waiting USB_EST int in case of usb otg wakeup */
        wake_lock_timeout(&hdmi.usb_otg_lock, HZ * 2); 
    }
    else
    {
        SII_WRN_PRINT("rgndImpedance_phy is invalid: %d\n", rgndImpedance_phy);   
    }
}

////////////////////////////////////////////////////////////////////
// Int4Isr
//		7 = RSVD		    (reserved)
//		6 = RGND Rdy	    (interested)
//		5 = MHL DISCONNECT	(interested)
//		4 = CBUS LKOUT	    (interested)
//		3 = USB EST		    (interested)
//		2 = MHL EST		    (interested)
//		1 = RPWR5V Change	(ignore)
//		0 = SCDT Change	    (only if necessary)
//
////////////////////////////////////////////////////////////////////
int Int4Isr( void )//UT XU
{
    uint8_t int4Status;
    int nReturnValue = I2C_ACCESSIBLE;

    int4Status = SiiDrvReadIndexedRegister(INDEXED_PAGE_2, P2_INTR4_ADDR);
    SII_DBG_PRINT("INT4 Status = 0x%02X\n", (int) int4Status);

    // When I2C is inoperational (D3) and a previous interrupt brought us here, do nothing.
    if (!int4Status)
    {
        //do nothing
    }
    else if (0xFF == int4Status)
    {
        nReturnValue = I2C_INACCESSIBLE;
    }
    else
    {
#ifdef CONFIG_MACH_HI6620OEM
        /* process RGND interrupt */
        if ((hdmi.power_state == HDMI_POWER_MIN) && (int4Status & BIT_INTRM4_RGND_DETECTION))
        {
            SII_INF_PRINT("receive cbus int: RGND_DETECTION\n");
            ProcessRgnd();
        }
#endif

        // process MHL_EST interrupt
        if (int4Status & BIT_INTRM4_MHL_EST)
        {
            SII_INF_PRINT("receive cbus int: MHL_EST\n");

            MhlTxDrvProcessConnection();
        }
        // process USB_EST interrupt
        else if (int4Status & BIT_INTRM4_USB_EST)
        {
            SII_INF_PRINT("receive cbus int: USB_EST\n");
            
            /* We will receive USB_EST if using no powered dongle or USB OTG.
               Make the switch direct to usb only if USB OTG. */
            if (g_PlumTxConfig.cbusImpedance == 0x03) {
#ifdef CONFIG_MHL_USB_SHARE
                switch_usb();
#endif
            }
            nReturnValue = I2C_INACCESSIBLE;
        }

        if (int4Status & BIT_INTRM4_CBUS_DISCONNECT)
        {
            SII_INF_PRINT("receive cbus int: CBUS_DISCONNECT\n");
            MhlTxDrvProcessDisconnection();
            nReturnValue = I2C_INACCESSIBLE;
        }

        if (int4Status & BIT_INTRM4_CBUS_LKOUT)
        {
            SII_WRN_PRINT("receive cbus int: CBUS_LOCKOUT\n");
        }
    }

    // clear all interrupts
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR4_ADDR, int4Status);

    return nReturnValue;
}

///////////////////////////////////////////////////////////////////////////
//
// MhlTxDrvProcessConnection
//
///////////////////////////////////////////////////////////////////////////
static void MhlTxDrvProcessConnection ( void )
{
    SII_DBG_PRINT("MHL Cable Connected. CBUS_STATUS = 0x%02X\n",
                   (int)SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_CBUS_CONN_STATUS_ADDR));
    msleep(30);
    // Notify upper layer of cable connection
    SiiNotifyConnection(true);
}

///////////////////////////////////////////////////////////////////////////
//
// MhlTxDrvProcessDisconnection
//
///////////////////////////////////////////////////////////////////////////
static void MhlTxDrvProcessDisconnection ( void )
{
    uint8_t int4Status;

    int4Status = SiiDrvReadIndexedRegister(INDEXED_PAGE_2, P2_INTR4_ADDR);

    // clear all interrupts
    SiiDrvWriteIndexedRegister(INDEXED_PAGE_2, P2_INTR4_ADDR, int4Status);

    //cable disconnect implies downstream HPD low
    dsHpdStatus &= ~BIT_CBUS_HPD;
    SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_CBUS_CONN_STATUS_ADDR, dsHpdStatus);

    SiiNotifyDsHpdChange(0);

    // make CBUS float 50ms after tmds disable
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL7_ADDR, BIT6|BIT7, 0x7F);
    msleep(50);
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL7_ADDR, BIT6|BIT7, 0x00);

    // Notify upper layer of cable removal
    SiiNotifyConnection(false);

#ifdef CONFIG_MHL_USB_SHARE
    /* The switch id pin is 1 in case of MHL */
    if (id_state() == 1) {
        switch_reset();
#ifdef CONFIG_SWITCH_FSA9685
        fsa9685_manual_detach();
#endif
    }
#endif
}

///////////////////////////////////////////////////////////////////////////
//
// CbusReset
//
///////////////////////////////////////////////////////////////////////////
void CbusReset (void)
{
    uint8_t enable[4] = {0xff, 0xff, 0xff, 0xff}; // must write 0xFF to clear regardless!

    SII_DBG_PRINT("CBUS reset!!!\n");

    SiiDrvModifyIndexedRegister(INDEXED_PAGE_0, P0_SRST_ADDR, BIT3, BIT3);
    msleep(2);
    SiiDrvModifyIndexedRegister(INDEXED_PAGE_0, P0_SRST_ADDR, BIT3, 0x00);

    g_PlumTxConfig.mscCmdInProgress = false;

    SiiDrvRegWriteBlock(MHL_CBUS_BASE, CBUS_MHL_INT_0_MASK_ADDR, enable, 4);
}

///////////////////////////////////////////////////////////////////////////
//
// CBusProcessErrors
//
//
///////////////////////////////////////////////////////////////////////////
uint8_t CBusProcessErrors( uint8_t int1Status )//UT zhou
{
    uint8_t result = 0;
    uint8_t ddcAbortReason = 0;

    /* At this point, we only need to look at the abort interrupts. */
    int1Status &= (BIT_CBUS_MSC_ABORT | BIT_CBUS_DDC_ABRT | BIT_CBUS_CMD_ABORT);

    if (int1Status)
    {
        /* Chip got some incorrect DDC data.*/
        if (int1Status & BIT_CBUS_DDC_ABRT)
        {
            result = ddcAbortReason = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_DDC_ABORT_INTR_ADDR);

            SII_WRN_PRINT("receive cbus int: DDC_ABORT, reason:: 0x%02X\n", (int)(ddcAbortReason));

#if USE_PEER_ABORT
            if (ddcAbortReason & BIT_CBUS_DDC_PEER_ABORT)
            {
                //set timer 2s for Tabort_next, refer to MHL spec13.10.3
                HalTimerSet(TIMER_ABORT, T_ABORT_NEXT);
                mscAbortFlag = true;
            }
#endif
        }

        //Abort as transmitter / requester.
        if (int1Status & BIT_CBUS_CMD_ABORT)
        {
            uint8_t mscMtAbortIntStatus = 0;

            // last command sent was not successful
            SII_WRN_PRINT("receive cbus int: CMD_ABORT: last command sent was not successful.\n");

            g_PlumTxConfig.mscCmdInProgress = false;
            DecrementCBusReferenceCount(CBusProcessErrors);

            mscMtAbortIntStatus = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_ADDR);
            if (mscMtAbortIntStatus)
            {
                SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_SEND_ERROR_ADDR, mscMtAbortIntStatus);
                SII_WRN_PRINT("CBUS:: MSC ABORTED as Requester.Clear 0x%02x. \n",(int)mscMtAbortIntStatus);

                if (BIT_CBUS_MSC_MT_ABORT_INT_MAX_FAIL & mscMtAbortIntStatus)
                {
                    SII_WRN_PRINT("Requestor MAXFAIL - retry threshold exceeded\n");
                }

                if (BIT_CBUS_MSC_MT_ABORT_INT_PROTO_ERR & mscMtAbortIntStatus)
                {
                    SII_WRN_PRINT("Protocol Error\n");
                }

                if (BIT_CBUS_MSC_MT_ABORT_INT_TIMEOUT & mscMtAbortIntStatus)
                {
                    SII_WRN_PRINT("Requestor translation layer timeout\n");
                }

                if (BIT_CBUS_MSC_MT_ABORT_INT_UNDEF_CMD & mscMtAbortIntStatus)
                {
                    SII_WRN_PRINT("Undefined opcode\n");
                }

                if (BIT_CBUS_MSC_MT_ABORT_INT_MSC_MT_PEER_ABORT & mscMtAbortIntStatus)
                {
                    SII_WRN_PRINT("CBUS:: MSC Peer sent an ABORT.\n");
#if USE_PEER_ABORT
                    //set timer 2s for Tabort_next, refer to MHL spec13.10.3
                    HalTimerSet(TIMER_ABORT, T_ABORT_NEXT);
                    mscAbortFlag = true;
#endif
                }
            }
        }

        //Abort as responser.
        if (int1Status & BIT_CBUS_MSC_ABORT)
        {
            uint8_t mscMrAbortIntStatus = 0;

            SII_WRN_PRINT("receive cbus int: CBUS_MSC_ABORT\n");

            mscMrAbortIntStatus = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_ADDR);
            if (mscMrAbortIntStatus)
            {
                SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_RCV_ERROR_ADDR, mscMrAbortIntStatus);
                SII_WRN_PRINT("CBUS:: MSC ABORTED as Responser. Clear 0x%02x\n",(int)mscMrAbortIntStatus);

                if (BIT_CBUS_MSC_MR_ABORT_INT_MAX_FAIL & mscMrAbortIntStatus)
                {
                    SII_WRN_PRINT("Requestor MAXFAIL - retry threshold exceeded\n");
                }

                if (BIT_CBUS_MSC_MR_ABORT_INT_PROTO_ERR & mscMrAbortIntStatus)
                {
                    SII_WRN_PRINT("Protocol Error\n");
                }

                if (BIT_CBUS_MSC_MR_ABORT_INT_TIMEOUT & mscMrAbortIntStatus)
                {
                    SII_WRN_PRINT("Requestor translation layer timeout\n");
                }

                if (BIT_CBUS_MSC_MR_ABORT_INT_UNDEF_CMD & mscMrAbortIntStatus)
                {
                    SII_WRN_PRINT("Undefined opcode\n");
                }
                if (BIT_CBUS_MSC_MR_ABORT_INT_MSC_MR_PEER_ABORT & mscMrAbortIntStatus)
                {
                    SII_WRN_PRINT("CBUS:: MSC Peer sent an ABORT.\n");
#if USE_PEER_ABORT
                    //set timer 2s for Tabort_next, refer to MHL spec13.10.3
                    HalTimerSet(TIMER_ABORT, T_ABORT_NEXT);
                    mscAbortFlag = true;
#endif
                }
            }
        }
    }

    return (result);
}

void SiiDrvGetScratchPad(uint8_t startReg, uint8_t * pData, uint8_t length)
{
    int i;

    for (i = 0; i < length; ++i, ++startReg)
    {
        *pData++ = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_MHL_SCRPAD_0_F_ADDR + startReg*4);
    }
}

///////////////////////////////////////////////////////////////////////////
//
// MhlCbusIsr
//
// Only when MHL connection has been established. This is where we have the
// first looks on the CBUS incoming commands or returned data bytes for the
// previous outgoing command.
//
// It simply stores the event and allows application to pick up the event
// and respond at leisure.
//
///////////////////////////////////////////////////////////////////////////
void MhlCbusIsr( void )//UT zhou
{
    uint8_t cbusInt;
    uint8_t cbusStatus;

    IN_FUNCTION;

    /* read cbus interrupt stats & cbus status */
    cbusInt    = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_ADDR);
    cbusStatus = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_CBUS_CONN_STATUS_ADDR);

    if (cbusInt)
    {
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_INTR_ADDR, cbusInt);
        SII_DBG_PRINT("Drv: CBUS INTR_0: 0x%02X\n", (int) cbusInt);

        if (BIT_CBUS_HPD_CHANGE & cbusInt)
        {
            SII_DBG_PRINT("receive cbus int: HPD_CHANGE\n");

            /* Check if a SET_HPD came from the downstream device. */
            SII_DBG_PRINT("cbusStatus is 0x%02x, dsHpdStatus is 0x%02x\n", cbusStatus, dsHpdStatus);

            /* CBUS_HPD status bit: 0 ¨C CLR_HPD; 1¨C SET_HPD*/
            if (BIT_CBUS_HPD & (dsHpdStatus ^ cbusStatus))
            {
                uint8_t status = cbusStatus & BIT_CBUS_HPD;
                SII_DBG_PRINT("Drv: Downstream HPD changed to: 0x%02X\n", (int) cbusStatus);

                // Inform upper layer of change in Downstream HPD
                SiiNotifyDsHpdChange( status );

                dsHpdStatus = cbusStatus;
            }
        }

        /* MSC_REQ_DONE received. */
        if (cbusInt & BIT_CBUS_MSC_MT_DONE)
        {
            SII_DBG_PRINT("receive cbus int: MSC_MT_DONE\n");
            g_PlumTxConfig.mscCmdInProgress = false;

            /* only do this after cBusInt interrupts are cleared above */
            SiiMscCommandDone(SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_RCVD_DATA1_ADDR));
            if (g_PlumTxConfig.hdcpStartPending)
            {
                g_PlumTxConfig.hdcpStartPending = false;
                SII_DBG_PRINT("Toggle TMDS HDCP .\n");

                SiiDrvHDCP_ToggleTmdsForHdcpAuthentication();
            }
        }

        if (cbusInt & BIT_CBUS_MSC_MR_WRITE_STAT)
        {
            uint8_t status[4] = {0};
            uint8_t i;

            SII_DBG_PRINT("receive cbus int: MSC_MR_WRITE_STAT\n");
            for (i = 0; i < 4; ++i)
            {
                /* record each value */
                status[i] = SiiDrvRegRead(MHL_CBUS_BASE, (CBUS_MHL_STAT_0_3_ADDR + i*4) );

                /* clear as we go */
                SiiDrvRegWrite(MHL_CBUS_BASE, (CBUS_MHL_STAT_0_3_ADDR + i*4), 0xFF ); /* future status[i]*/
            }

			/* DCAP_RDY & PATH_EN */
            SiiGotMhlStatus( status[0], status[1] );
        }

        /* MSC_MSG (RCP/RAP) */
        if (cbusInt & BIT_CBUS_MSC_MR_MSC_MSG)
        {
            uint8_t mscMsg[2];
            SII_DBG_PRINT("receive cbus int: MSC_MR_MSC_MSG\n");

            /*Read CMD & DATA*/
            mscMsg[0] = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_MSG_RCVD_DATA1_ADDR);
            mscMsg[1] = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_MSG_RCVD_DATA2_ADDR);

            SII_DBG_PRINT("MSC MSG: 0x%02X 0x%02X\n", (int)mscMsg[0], (int)mscMsg[1]);
            SiiGotMhlMscMsg( mscMsg[0], mscMsg[1] );
        }

        /* MSC WRITE_BURST command received interrupt status */
        if (cbusInt & BIT_CBUS_MSC_MR_WRITE_BURST)
        {
            /* Received WRITE_BURST complete */
            SII_DBG_PRINT("receive cbus int: MSC_MR_WRITE_BURST\n");
        }

        if (cbusInt & BIT_CBUS_MSC_MR_SET_INT)
        {
            uint8_t intr[4] = {0};

            SII_DBG_PRINT("receive cbus int: MSC_MR_SET_INT\n");
            SiiDrvRegReadBlock(MHL_CBUS_BASE, CBUS_MHL_INT_0_ADDR, intr, 4);

            /* We are interested only in first two bytes. */
            SiiGotMhlIntr( intr[0], intr[1] );

            /* Clear all CBUS interrupts */
            SiiDrvRegWriteBlock(MHL_CBUS_BASE, CBUS_MHL_INT_0_ADDR, intr, 4);
        }
    }

    cbusInt = SiiDrvRegRead(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_ADDR);
    if (cbusInt)
    {
        //SII_WRN_PRINT("Drv: CBUS INTR_1: 0x%02X\n", (int) cbusInt);

        CBusProcessErrors(cbusInt);

        /* Clear all interrupts that were raised even if we did not process
        this interrupt register is not in plum register map, but in
        iceman and wolvrine register map. this will be fixed */
        SiiDrvRegWrite(MHL_CBUS_BASE, CBUS_REG_MSC_ERROR_INTR_ADDR, cbusInt);
    }

    OUT_FUNCTION;
}

///////////////////////////////////////////////////////////////////////////////
//
// SiiDrvPowBitChange
//
// Alert the driver that the peer's POW bit has changed so that it can take
// action if necessary.
//
void SiiDrvPowBitChange (bool enable)
{
    /* MHL peer device has it's own power */
    if (enable) {
        SiiDrvModifyIndexedRegister(INDEXED_PAGE_2, P2_DISC_CTRL8_ADDR, BIT2, BIT2);
        SII_DBG_PRINT("POW bit 0->1, set DISC_CTRL8[2] = 1\n");
    }
}

/*
    SiMhlTxDrvSetClkMode
    -- Set the hardware this this clock mode.
 */
void SiMhlTxDrvSetClkMode(uint8_t clkMode)
{
    SII_DBG_PRINT("SetClkMode:0x%02x\n", (int)clkMode);

    // nothing to do here since we only suport MHL_STATUS_CLK_MODE_NORMAL
    // if we supported SUPP_PPIXEL, this would be the place to write the register
}

#if USE_3D
static void Send_VSIF(void)
{
    uint8_t i;
    uint8_t Data[MHL_VSIF_LENTH];

    if (VideoModeDescription.HDMIVideoFormat == 0)
    {
        // clear the VSIF buffer.
        for (i = 0; i < MHL_VSIF_LENTH; i++)
        {
            Data[i] = 0;
        }
    }
    else
    {
        for (i = 0; i < MHL_VSIF_LENTH; i++)
        {
            Data[i] = 0;
        }

        // Header Bytes
        Data[0] = VSIF_TYPE;            // HB0 Packet Type 0x81
        Data[1] = VSIF_VERSION;         // HB1 Version = 0x01
        Data[2] = MHL_VSIF_BODYLENTH;
        // PB1 - PB3 contain the 24bit IEEE Registration Identifier
        Data[4] = 0x1D;                     // MHL Signature LS Byte
        Data[5] = 0xA6;                     // MHL Signature middle uint8_t
        Data[6] = 0x7C;                     // MHL Signature MS Byte

        /* PB4[0:1] - MHL_VID_FMT: 3D Format present
                 PB4[2:5] - MHL_3D_FMT_TYPE: 3D Format modes
                 See MHL 2.0 Spec 5.9.2 for detail*/
        if(VideoModeDescription.ThreeDStructure == VMD_3D_FRAMEPACKING)
        {
            Data[7] = 0x01;
        }
        else if(VideoModeDescription.ThreeDStructure == VMD_3D_SIDEBYSIDEHALF)
        {
            Data[7] = 0x05;
        }
        else if(VideoModeDescription.ThreeDStructure == VMD_3D_TOPBOTTOM)
        {
            Data[7] = 0x09;
        }
        else // Unsupported 3D format
        {
            Data[7] = 0x3D;
        }
        // Packet Bytes
        Data[3] = VSIF_TYPE +                // PB0 partial checksum
                  VSIF_VERSION +
                  Data[2];

        // Complete the checksum
        for (i = 4; i < MHL_VSIF_LENTH; i++)
        {
            Data[3] += Data[i];
        }

        Data[3] = 0x100 - Data[3];            // Final checksum
    }

    // Disable transmission of VSIF during re-configuration
    SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR, 0x06);

    SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR, 0xC6);              // Enable and Repeat Vendor Specific InfoFrames
    SiiDrvWriteBlockTPI(TPI_I_F_TYPE_ADDR, MHL_VSIF_LENTH, Data);     // Write data to VSIF registers and start transmission
    SiiDrvWriteByteTPI(0x378, 0x00);       // Set last uint8_t of VSIF for data to be sent to the sink.
}
#endif /* USE_3D */

uint8_t CalculateGenericCheckSum(uint8_t *infoFrameData, uint8_t checkSum, uint8_t length)
{
    uint8_t i;

    for (i = 0; i < length; i++)
    {
        checkSum += infoFrameData[i];
    }

    checkSum = 0x100 - checkSum;

    SII_DBG_PRINT("checkSum: 0x%02X\n", checkSum);
    return checkSum;
}

#if USE_PP_MODE
void SiiMhlTxDrvApplyPPModeSettings( void )
{
    if (packedPixelStatus)
	{
		// PackedPixel Mode
		SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_2,REG_MHLTX_CTR10,BIT_VID_MODE_m1080p_MASK,BIT_VID_MODE_m1080p_ENABLE); // Packed Pixel mode enabled.
        SII_DBG_PRINT(("Drv: Using 16-bit mode (Packed Pixel)\n"));
	}
    else
    {
		// Normal Mode, Packed Pixel mode disabled.
        SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_2,REG_MHLTX_CTR10,BIT_VID_MODE_m1080p_MASK,BIT_VID_MODE_m1080p_DISABLE);
        SII_DBG_PRINT(("Drv: Using 24-bit mode (non-Packed Pixel)\n"));
    }
    // Set input color space
    SiiDrvRegModify(REG_TPI_INPUT, BIT_TPI_INPUT_FORMAT_MASK,VideoModeDescription.InputColorSpace);
    // Set output color space
    SiiDrvRegModify(REG_TPI_OUTPUT, BIT_TPI_OUTPUT_FORMAT_MASK,VideoModeDescription.OutputColorSpace);
}

void SiiMhlTxDrvSetPixelClockFrequency(uint32_t pixelClockFrequencyParm)
{
    pixelClockFrequency = pixelClockFrequencyParm;
}

void	SiiMhlTxDrvSetPackedPixelStatus( int supportPackedPixel )
{
	SII_DBG_PRINT(("Setting Packed Pixel = %02X\n", supportPackedPixel));
    packedPixelStatus = supportPackedPixel;
}

uint8_t SiiMhlTxDrvGetPackedPixelStatus( void )
{
    return packedPixelStatus;
}

uint16_t SiiMhlTxDrvGetIncomingHorzTotal(void)
{
    uint16_t retVal;
    retVal = (((uint16_t)SiiDrvReadIndexedRegister(INDEXED_PAGE_0, REG_HRESH)) <<8) | (uint16_t)SiiDrvReadIndexedRegister(INDEXED_PAGE_0, REG_HRESL);
    return retVal;
}

uint16_t SiiMhlTxDrvGetIncomingVertTotal(void)
{
    uint16_t retVal;
    retVal = (((uint16_t)SiiDrvReadIndexedRegister(INDEXED_PAGE_0, REG_VRESH)) <<8) | (uint16_t)SiiDrvReadIndexedRegister(INDEXED_PAGE_0, REG_VRESL);
    return retVal;
}
void SiiMhlTxDrvSet3DMode(uint8_t do3D,uint8_t three3ModeParm)
{

    if (do3D)
    {
        ThreeDStructure_e three3Mode = (ThreeDStructure_e) three3ModeParm;

        if (tdsFramePacking == three3Mode)
        {
            SII_DBG_PRINT(("Drv: using frame packing\n"));
            SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_2, REG_EN_3D_CONV,BIT_VID_OVRRD_3DCONV_EN_MASK,BIT_VID_OVRRD_3DCONV_EN_FRAME_PACK);
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_2,REG_CTRL_3D_CONV,0x40);
        }
        else
        {
            SII_DBG_PRINT(("Drv: NOT using frame packing\n"));
            SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_2, REG_EN_3D_CONV,BIT_VID_OVRRD_3DCONV_EN_MASK,BIT_VID_OVRRD_3DCONV_EN_NORMAL);
            SiiDrvWriteIndexedRegister(INDEXED_PAGE_2,REG_CTRL_3D_CONV,0x00);
        }
    }
    else
    {
        SII_DBG_PRINT(("Drv: NOT using frame packing\n"));
        SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_2, REG_EN_3D_CONV,BIT_VID_OVRRD_3DCONV_EN_MASK,BIT_VID_OVRRD_3DCONV_EN_NORMAL);
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_2,REG_CTRL_3D_CONV,0x00);
    }
}
#endif


/*
 *****************************************************************************
 *
 * Copyright 2002-2009,2010, Silicon Image, Inc.  All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of: Silicon Image, Inc., 1060
 * East Arques Avenue, Sunnyvale, California 94085
 *****************************************************************************
 */

/*
 *****************************************************************************
 * @file  si_hdcp.c
 *
 * @brief Implementation of the HDCP
 *
 *****************************************************************************
 */
#include <linux/delay.h>
#include "si_edid.h" 
#include "si_reg_access.h"
#include "si_hdcp.h"
#include "si_mhl_tx.h"

/* HDCP feature switch, true: on, false: off */
bool HDCP_Switch_On = true;
bool HDCP_Started   = false;
bool HDCP_AksvValid = false;
byte HDCP_LinkProtectionLevel;

extern mhlTx_config_t g_PlumTxConfig;

#define AKSV_SIZE 5
#define NUM_OF_ONES_IN_KSV 20
#define BYTE_SIZE 0x08

#if USE_HDCP
extern void    SiiDrvVideoUnmute( void );

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiHDCP_Init()
//
// PURPOSE      :   Tests Tx and Rx support of HDCP. If found, checks if
//                  and attempts to set the security level accordingly.
//
// INPUT PARAMS :   None
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :	HDCP_TxSupports - initialized to false, set to true if supported by this device
//					HDCP_AksvValid - initialized to false, set to true if valid AKSVs are read from this device
//					HDCP_Started - initialized to false
//					HDCP_LinkProtectionLevel - initialized to (EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE)
//
// RETURNS      :   None
//
//////////////////////////////////////////////////////////////////////////////

void SiiHDCP_Init (void)
{
    SII_DBG_PRINT(">>SiiHDCP_Init()\n");
    
#if HDMI_FOR_CERTIFICATION
    HDCP_Switch_On = true;    /* This swtich is controlled by upper setting in normal mode s*/
#endif
    HDCP_AksvValid = false;
    HDCP_Started = false;
    HDCP_LinkProtectionLevel = EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE;

    // This is TX-related... need only be done once.
    if (!SiiDrvHDCP_Supported())
    {
        // The TX does not support HDCP, so authentication will never be attempted.
        // Video will be shown as soon as TMDS is enabled.
        SII_WRN_PRINT( "HDCP -> TX does not support HDCP\n");
        return;
    }

    // This is TX-related... need only be done once.
    if (!SiiDrvHDCP_AreAKSV_OK())
    {
        // The TX supports HDCP, but does not have valid AKSVs.
        // Video will not be shown.
        SII_WRN_PRINT( "HDCP -> Illegal AKSV\n");
        return;
    }

    HDCP_AksvValid = true;

    SII_INF_PRINT( "HDCP -> Supported by TX, AKSVs valid\n");
}

void SiiHDCP_CheckStatus ()
{
    byte QueryData;
    byte NewLinkProtectionLevel;
    byte InterruptStatusImage;
    
    /* Skip HDCP if TMDS is disabled. */
    if (false == g_PlumTxConfig.bTmdsOutputEnabled) {
        return;
    }
    
    /* HDCP is closed and Tmds is enabled, then unmute the video */
    if (HDCP_Switch_On == false) {
        SiiDrvVideoUnmute();
        return;
    }

    InterruptStatusImage = SiiDrvReadByteTPI(TPI_INTERRUPT_STATUS_ADDR);
    QueryData = SiiDrvReadByteTPI(TPI_QUERY_DATA_ADDR);
    
    SII_DBG_PRINT("%s: HDCP_Switch_On: %d, HDCP_AksvValid: %d, HDCP_Started: %d\n", 
                   __FUNCTION__, HDCP_Switch_On, HDCP_AksvValid, HDCP_Started);
    
    SII_DBG_PRINT("%s: HDCP_LinkProtectionLevel: 0x%02x, InterruptStatusImage: 0x%02x, QueryData: 0x%02x\n", 
                   __FUNCTION__, HDCP_LinkProtectionLevel, InterruptStatusImage, QueryData);   

    //Clear Interrupt Status.
    if (InterruptStatusImage & (~(BIT2 | BIT3)))
    {
        SiiDrvWriteByteTPI(TPI_INTERRUPT_STATUS_ADDR, InterruptStatusImage & (~(BIT2 | BIT3)));
        SII_DBG_PRINT("Drv: Clear TPI_INTERRUPT_STATUS_ADDR(0x3D):0x%02X\n",
                                                  (int) InterruptStatusImage);
    }

    /* It will mute the sink if the TX's AKSV is invalid. */
    if (HDCP_AksvValid == true)
    {
        if ((HDCP_LinkProtectionLevel == (EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE))
            && (HDCP_Started == false))
        {
            // Is sink's HDCP avaialable? 
            // MHL TX will read sink's HDCP capability once P0_0x80[4] or TPI_0x1A[4] is executed in SiiDrvTmdsControl()
            if (QueryData & PROTECTION_TYPE_MASK)   
            {
                SiiDrvHDCP_On();
            } else {
                SiiDrvVideoUnmute();
                SII_DBG_PRINT("Sink doesn't support HDCP, unmute it.\n");
                return;
            }
        }

        // Check if Link Status has changed:
        if (InterruptStatusImage & BIT_TPI_INTR_ST0_HDCP_SECURITY_CHANGE_EVENT)
        {
            switch (QueryData & LINK_STATUS_MASK)
            {
            case LINK_STATUS_NORMAL:
                SII_INF_PRINT("Link = Normal\n");
                break;

            case LINK_STATUS_LINK_LOST:
                SII_INF_PRINT("Link = Lost\n");
                SiiDrvHDCP_Restart();
                break;

            case LINK_STATUS_RENEGOTIATION_REQ:
                SII_INF_PRINT("Link = Renegotiation Required\n");
                SiiDrvHDCP_Restart();
                break;

            case LINK_STATUS_LINK_SUSPENDED:
                SII_INF_PRINT("Link = Suspended\n");

                //If stop encryption in third phase of authentication, the HDCP state will enter SUSPENDED, you need to set 1A[bit6] besides 1A[bit0]
                //to recover. Retoggling HDCP authentication 1A[bit4] is also all right, though it is not recommended.
                //But as per test, this bit doesn't make any difference.
                SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, TPI_1A_AUTO_REAUTHENTICATION_MASK,
                                         TPI_1A_AUTO_REAUTHENTICATION_ENABLE);
                SiiDrvHDCP_Restart();
                break;
            }
        }

        // Check if HDCP state has changed:
        if (InterruptStatusImage & BIT_TPI_INTR_ST0_HDCP_AUTH_STATUS_CHANGE_EVENT)
        {
            NewLinkProtectionLevel = QueryData & (EXTENDED_LINK_PROTECTION_MASK | LOCAL_LINK_PROTECTION_MASK);
            if (NewLinkProtectionLevel != HDCP_LinkProtectionLevel)
            {
                HDCP_LinkProtectionLevel = NewLinkProtectionLevel;

                switch (HDCP_LinkProtectionLevel)
                {
                case (EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE):
                    SII_INF_PRINT("Protection = None\n");
                    break;

                case LOCAL_LINK_PROTECTION_SECURE:
                    SiiDrvVideoUnmute();
                    SII_INF_PRINT("Protection = Local\n");
                    break;

                case (EXTENDED_LINK_PROTECTION_SECURE | LOCAL_LINK_PROTECTION_SECURE):
                    SiiDrvVideoUnmute();
                    SII_INF_PRINT("Protection = Extended\n");
                    break;
                default:
                    SII_INF_PRINT( "Protection = Extended but not Local?\n");
                    break;
                }
            }
        }
    } else {
        SiiDrvVideoMute();
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvHDCP_Supported()
//
// PURPOSE      :   Check Tx revision number to find if this Tx supports HDCP
//                  by reading the HDCP revision number from TPI register 0x30.
//
// INPUT PARAMS :   None
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   None
//
// RETURNS      :   true if Tx supports HDCP. false if not.
//
//////////////////////////////////////////////////////////////////////////////

bool SiiDrvHDCP_Supported(void)
{
    byte HDCP_Rev;
    bool SiiDrvHDCP_Supported;

    SiiDrvHDCP_Supported = true;

    // Check Device ID
    HDCP_Rev = SiiDrvReadByteTPI(TPI_HDCP_REVISION_ADDR);

    if (HDCP_Rev != (HDCP_MAJOR_REVISION_VALUE | HDCP_MINOR_REVISION_VALUE))
    {
        SiiDrvHDCP_Supported = false;
        SII_DBG_PRINT(">>HDCP NOT supported!\n");
    }
    else
    {
        SII_DBG_PRINT(">>HDCP supported!\n");
    }

    return SiiDrvHDCP_Supported;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvHDCP_On()
//
// PURPOSE      :   Switch hdcp on.
//
// INPUT PARAMS :   None
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   HDCP_Started set to true
//
// RETURNS      :   None
//
//////////////////////////////////////////////////////////////////////////////
void SiiDrvHDCP_On(void)
{
    unsigned char uReg_TPI_HW_DBG1 = 0;
    unsigned char uReg_TPI_HW_DBG3 = 0;
    unsigned char uTimeOut = 100;

    //Step 1: Enable HDCP. Drive hardware to read BKSV.
    if (HDCP_Started == false)
    {
        SII_DBG_PRINT("HDCP -> Started\n");
        SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, PROTECTION_LEVEL_MASK, PROTECTION_LEVEL_MAX);

        //Step 2: Tell if read BKSV successfully.
        while ((!((uReg_TPI_HW_DBG1 & BIT0) | (uReg_TPI_HW_DBG3 & BIT0))) && uTimeOut)
        {
            msleep(10);
            uReg_TPI_HW_DBG1 = SiiDrvReadByteTPI(TPI_HW_DBG1_ADDR);
            uReg_TPI_HW_DBG3 = SiiDrvReadByteTPI(TPI_HW_DBG3_ADDR);
            uTimeOut--;
        } 
        
        if (0x00 == uTimeOut)
        {
            SII_DBG_PRINT("HDCP->Read BKSV Timeout.\n");
            HDCP_Started = false;
        }
        else if (uReg_TPI_HW_DBG1 & BIT0)
        {
            SII_DBG_PRINT("HDCP->Read BKSV Done. Sink does supports HDCP.\n");
            HDCP_Started = true;
        }
        else if (uReg_TPI_HW_DBG3 & BIT0)
        {
            SII_DBG_PRINT("HDCP->Read BKSV Error. Sink Does NOT supports HDCP.\n");
            HDCP_Started = false;
        }

        if (false == HDCP_Started)
        {
            SiiDrvHDCP_Off();
            SiiDrvHDCP_ToggleTmdsForHdcpAuthentication();
            HDCP_LinkProtectionLevel = EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE;
        }
    }

    return;
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvHDCP_Off()
//
// PURPOSE      :   Switch hdcp off.
//
// INPUT PARAMS :   None
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :   HDCP_Started set to false
//
// RETURNS      :   None
//
//////////////////////////////////////////////////////////////////////////////

void SiiDrvHDCP_Off(void)
{
    if (true == HDCP_Started)
    {
        SII_DBG_PRINT(">>SiiDrvHDCP_Off()\n");

        // AV MUTE
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, AV_MUTE_MASK, AV_MUTE_MUTED);
        SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, PROTECTION_LEVEL_MASK, PROTECTION_LEVEL_MIN);
        HDCP_Started = false;
        HDCP_LinkProtectionLevel = EXTENDED_LINK_PROTECTION_NONE | LOCAL_LINK_PROTECTION_NONE;
    }    
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION     :   SiiDrvHDCP_Restart()
//
// PURPOSE      :   When auth fails, RTL need this bit to return auth_prep satus.
//
// INPUT PARAMS :   None
//
// OUTPUT PARAMS:   None
//
// GLOBALS USED :
//
// RETURNS      :   None
//
//////////////////////////////////////////////////////////////////////////////

void SiiDrvHDCP_Restart(void)
{
    SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, PROTECTION_LEVEL_MASK, PROTECTION_LEVEL_MIN);
    msleep(100);//Let TX sends one frame at least to inform RX.
    SiiDrvModifyByteTPI(TPI_CONTROL_DATA_ADDR, PROTECTION_LEVEL_MASK, PROTECTION_LEVEL_MAX);
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION      :  SiiDrvHDCP_AreAKSV_OK()
//
// PURPOSE       :  Check if AKSVs contain 20 '0' and 20 '1'
//
// INPUT PARAMS  :  None
//
// OUTPUT PARAMS :  None
//
// GLOBALS USED  :  TBD
//
// RETURNS       :  true if 20 zeros and 20 ones found in AKSV. false OTHERWISE
//
//////////////////////////////////////////////////////////////////////////////
bool SiiDrvHDCP_AreAKSV_OK(void)
{
    byte B_Data[AKSV_SIZE];
    byte NumOfOnes = 0;

    byte i;
    byte j;

    SiiDrvReadBlockTPI(TPI_AKSV_1_ADDR, AKSV_SIZE, B_Data);

    for (i = 0; i < AKSV_SIZE; i++)
    {
        for (j = 0; j < BYTE_SIZE; j++)
        {
            if (B_Data[i] & 0x01)
            {
                NumOfOnes++;
            }

            B_Data[i] >>= 1;
        }
    }

    if (NumOfOnes != NUM_OF_ONES_IN_KSV)
    {
        return false;
    }

    return true;
}
#endif /* USE_HDCP */

void    SiiDrvHDCP_ToggleTmdsForHdcpAuthentication(void)
{
    SII_DBG_PRINT("Toggle HDCP Authentication.\n");
    if (g_PlumTxConfig.mscCmdInProgress)
    {
        SII_DBG_PRINT("MSC cmd is in progress, hdcpStartPending is set to true.\n");
        g_PlumTxConfig.hdcpStartPending = true;
    }
    else
    {        
        SII_DBG_PRINT("Do the three mandatory steps.\n");
        
        // a three step process is mandatory
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, AV_MUTE_MASK, AV_MUTE_MUTED);
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, TMDS_OUTPUT_CONTROL_MASK, TMDS_OUTPUT_CONTROL_POWER_DOWN);
        SiiDrvModifyByteTPI(TPI_SYSTEM_CTRL_ADDR, TMDS_OUTPUT_CONTROL_MASK, TMDS_OUTPUT_CONTROL_ACTIVE);

        HDCP_Started = false;
    }
}


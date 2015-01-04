/*
 *****************************************************************************
 *
 * Copyright 2012, Silicon Image, Inc.  All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of: Silicon Image, Inc., 1060
 * East Arques Avenue, Sunnyvale, California 94085
 *****************************************************************************
 */

/*
 *****************************************************************************
 * @file  HDCP.h
 *
 * @brief Implementation of the Foo API.
 *
 *****************************************************************************
 */
#ifndef __SI_HDCP_H__
#define __SI_HDCP_H__

void SiiHDCP_Init (void);
void SiiHDCP_CheckStatus (void);
void SiiDrvHDCP_Off(void);
void SiiDrvHDCP_On(void);
void SiiDrvHDCP_Restart(void);
void SiiDrvHDCP_ToggleTmdsForHdcpAuthentication(void);
bool SiiDrvHDCP_AreAKSV_OK(void);
bool SiiDrvHDCP_Supported(void);
#endif

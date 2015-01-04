/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_reg_access.c
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/

#include <linux/io.h>
#include <linux/delay.h>

#include "si_reg_access.h"
#include "si_mhl_hw.h"
#include "si_mhl_main.h"  

extern hdmi_hw_res hw_res;

#if CHECK_SOFTWARE_TPI
static bool SiiDrvHardwareTPIMode(void);
static bool SiiDrvSoftwareTPIBank0(void);

/******************************************************************************
* Function:       SiiDrvHardwareTPIMode
* Description:    judge is in TPI Mode
* Input:          na
* Output:         true: is in hardware TPI mode
* Return:         bool
*******************************************************************************/
static bool SiiDrvHardwareTPIMode(void)
{
    /* TPI_DEV_ID should be 0xB4 in Hardware TPI Mode.
       TPI_VENDOR_B3 should be 0x30 in hardware TPI mode */
    if ( ( 0xB4 == SiiDrvRegRead(MHL_CORE_SYS, TPI_DEV_ID_ADDR) ) 
		&& ( 0x30 == SiiDrvRegRead(MHL_CORE_SYS, TPI_VENDOR_B3_ADDR) ) ) {
        return true;
    } else {
        SII_WRN_PRINT("Not TPI mode.\n");
        return false;
    }
}

/******************************************************************************
* Function:       SiiDrvSoftwareTPIBank0
* Description:    judge index mode page
* Input:          na
* Output:         ture: is in page 0
* Return:         bool
*******************************************************************************/
static bool SiiDrvSoftwareTPIBank0(void)
{
    /* GAMUT_HEADER1 is located in the first byte of bank1 in 
         software TPI mode. The default value is 0x0A.(00) */
    if ( 0x0A == SiiDrvRegRead(MHL_CORE_SYS, 0) ) {
        return false;
    } else {
        return true;
    }
}
#endif
/******************************************************************************
* Function:       SiiDrvRegRead
* Description:    Read 8bit reg
* Input:          reg addr and offset
* Output: 	      value off the reg
* Return: 	      uint8_t
*******************************************************************************/ 
uint8_t SiiDrvRegRead(uint32_t base, uint32_t idx)
{
    /* MHL IP's APB module has a bug that reading one register can't return correct
       value after writing one register immediately. 
       
       Resolving this bug the software can execute one read operation before the expected read. */
    uint8_t temp = __raw_readl(base);
    temp = (uint8_t)__raw_readl(base + idx);
    
    return temp;
}

/******************************************************************************
* Function:       SiiDrvRegWrite
* Description:    Wite 8bit value to reg
* Input:          reg addr ,offset and value
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvRegWrite(uint32_t base, uint32_t idx, uint8_t val)
{
    __raw_writel((uint32_t)val, base + idx);
    return;
}

/******************************************************************************
* Function:       SiiDrvRegModify
* Description:    Modify the mask value to reg
* Input:          reg addr ,offset, mask and value
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvRegModify(uint32_t base, uint32_t idx, uint8_t mask, uint8_t value)
{
    uint8_t aByte;

    aByte  = SiiDrvRegRead(base, idx);
    aByte &= (~mask);                       /* first clear all bits in mask */
    aByte |= (mask & value);                /* then set bits from value */
    SiiDrvRegWrite(base, idx, aByte);
}

/******************************************************************************
* Function:       SiiDrvRegReadBlock
* Description:    Read 8bit reg one by one
* Input:          base: base addr, idx: offset addr, *pBuffer: read buffer, count 
* Output: 	      count Entries of availability value in pBuffer
* Return: 	      void
*******************************************************************************/ 
void SiiDrvRegReadBlock(uint32_t base, uint32_t idx, uint8_t *pBuffer, uint8_t count )
{
    uint8_t i;

    for (i = 0; i < count; i++) {
        *pBuffer = SiiDrvRegRead(base, idx + i*4);
        ++pBuffer;
    }
}

/******************************************************************************
* Function:       SiiDrvRegWriteBlock
* Description:    Write 8bit reg one by one
* Input:          base: base addr, idx: offset addr, *pBuffer: write buffer, count 
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvRegWriteBlock(uint32_t base, uint32_t idx, uint8_t *pBuffer, uint8_t count )
{
    uint8_t i;

    for (i = 0; i < count; i++) {
        SiiDrvRegWrite(base, idx + i*4, *pBuffer);
        ++pBuffer;
    }
}

/******************************************************************************
* Function:       SiiDrvReadByteTPI
* Description:    Read 8bit from TPI mode reg
* Input:          reg offset
* Output: 	      value off the reg
* Return: 	      uint8_t
*******************************************************************************/ 
uint8_t SiiDrvReadByteTPI(uint32_t RegOffset)
{
    uint8_t bRegValue = 0;
#if CHECK_SOFTWARE_TPI
    /* Step 1: Make sure to be hardware TPI mode. */
    if (!SiiDrvHardwareTPIMode()) {
        if (SiiDrvSoftwareTPIBank0()) { 
			/* Bank0 */
			SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        } else { 
            /* Bank1 */
            /* Switch to Bank0 */
			SiiDrvRegModify(MHL_TPI_SYS, TPI_PAGE_INDEX_ADDR, BIT0, 0x00);
			SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        }
    }
#endif
    /* Step 2: Read out specified Byte. */
    bRegValue = SiiDrvRegRead(MHL_TPI_SYS, RegOffset);
    return (bRegValue);
}

/******************************************************************************
* Function:       SiiDrvWriteByteTPI
* Description:    Write 8bit TPI mode reg
* Input:          reg offset and value
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvWriteByteTPI (uint32_t RegOffset, uint8_t value)
{
#if CHECK_SOFTWARE_TPI
    /* Step 1: Make sure to be hardware TPI mode. */
    if (!SiiDrvHardwareTPIMode()) {
        if (SiiDrvSoftwareTPIBank0()) {
            /* Bank0 */
            SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        } else {
            /* Bank1 */
            /* Switch to Bank0 */
			SiiDrvRegModify(MHL_TPI_SYS, TPI_PAGE_INDEX_ADDR, BIT0, 0x00);
			SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        }
    }
#endif
    /* Step 2: Write Value. */
	SiiDrvRegWrite(MHL_TPI_SYS, RegOffset, value);
    return ;
}

/******************************************************************************
* Function:       SiiDrvModifyByteTPI
* Description:    Modify mask value to TPI mode reg
* Input:          reg offset, mask and value
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvModifyByteTPI(uint32_t RegOffset, uint8_t mask, uint8_t value)
{
    uint8_t temp;

    temp  = SiiDrvReadByteTPI(RegOffset);     /* Read the current value of the register. */
    temp &= ~mask;                            /* Clear the bits that are set in Mask. */
    temp |= (value & mask);                   /* OR in new value. Apply Mask to Value for safety. */
    SiiDrvWriteByteTPI(RegOffset, temp);      /* Write new value back to register. */
}

/******************************************************************************
* Function:       SiiDrvReadBlockTPI 
* Description:    Read NBytes 8bit value from TPI mode reg
* Input:          TPI_Offset, NBytes, *pData
* Output: 	      NBytes Entries of read availability value in pData
* Return: 	      void
*******************************************************************************/ 
void SiiDrvReadBlockTPI(uint32_t TPI_Offset, uint8_t NBytes, uint8_t *pData)
{
#if CHECK_SOFTWARE_TPI
    /* Step 1: Make sure to be hardware TPI mode. */
    if (!SiiDrvHardwareTPIMode()) {
		if (SiiDrvSoftwareTPIBank0()) {
            /* Bank0 */
            SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        } else {
            /* Bank1 */
            /* Switch to Bank0 */
			SiiDrvRegModify(MHL_TPI_SYS, TPI_PAGE_INDEX_ADDR, BIT0, 0x00);
			SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        }
    }
#endif
	/* Step 2: Read out specified Byte. */
	SiiDrvRegReadBlock (MHL_TPI_SYS, TPI_Offset, pData, NBytes );
}

/******************************************************************************
* Function:       SiiDrvWriteBlockTPI 
* Description:    Write NBytes 8bit value to TPI mode reg   
* Input:          TPI_Offset, NBytes, *pData
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvWriteBlockTPI(uint32_t TPI_Offset, uint8_t NBytes, uint8_t *pData)
{
#if CHECK_SOFTWARE_TPI
    /* Step 1: Make sure to be hardware TPI mode. */
    if ( !SiiDrvHardwareTPIMode() ) {
        if ( SiiDrvSoftwareTPIBank0() ) {
            /* Bank0 */
            SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        } else {
            /* Bank1 */
            /* Switch to Bank0 */
			SiiDrvRegModify(MHL_TPI_SYS, TPI_PAGE_INDEX_ADDR, BIT0, 0x00);
			SiiDrvRegModify(MHL_TPI_SYS, P0_LM_DDC_ADDR, BIT7, 0x00);
        }
    }
#endif
	/* Step 2: Read out specified Byte. */
	SiiDrvRegWriteBlock (MHL_TPI_SYS, TPI_Offset, pData, NBytes );
}

/******************************************************************************
* Function:       SiiDrvReadIndexedRegister 
* Description:    Read PageNum RegOffset reg
* Input:          PageNum, RegOffset
* Output: 	      value of the PageNum and Offset Reg
* Return: 	      uint8_t
*******************************************************************************/ 
uint8_t SiiDrvReadIndexedRegister(uint8_t PageNum, uint32_t RegOffset)
{
    SiiDrvWriteByteTPI(TPI_INDEX_REG_PAGE_ADDR, PageNum);                      /* Indexed page */
    SiiDrvWriteByteTPI(TPI_INDEX_REG_OFFSET_ADDR, (uint8_t)(RegOffset >> 2));  /* Indexed register */
    return SiiDrvReadByteTPI(TPI_INDEX_REG_VALUE_ADDR);                        /* Return read value */
}

/******************************************************************************
* Function:       SiiDrvWriteIndexedRegister 
* Description:    Write PageNum RegOffset reg
* Input:          PageNum, RegOffset, void
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvWriteIndexedRegister(uint8_t PageNum, uint32_t RegOffset, uint8_t RegValue)
{
    SiiDrvWriteByteTPI(TPI_INDEX_REG_PAGE_ADDR, PageNum);                      /* Indexed page */
    SiiDrvWriteByteTPI(TPI_INDEX_REG_OFFSET_ADDR, (uint8_t)(RegOffset >> 2));  /* Indexed register */
    SiiDrvWriteByteTPI(TPI_INDEX_REG_VALUE_ADDR, RegValue);                    /* Write value */
}

/******************************************************************************
* Function:       SiiDrvModifyIndexedRegister 
* Description:    Modify Mask value to PageNum RegOffset reg
* Input:          PageNum, RegOffset, Mask, Value
* Output: 	      na
* Return: 	      void
*******************************************************************************/ 
void SiiDrvModifyIndexedRegister(uint8_t PageNum, uint32_t RegOffset, uint8_t Mask, uint8_t Value)
{
    SiiDrvWriteByteTPI(TPI_INDEX_REG_PAGE_ADDR, PageNum);
    SiiDrvWriteByteTPI(TPI_INDEX_REG_OFFSET_ADDR, (uint8_t)(RegOffset >> 2));
	SiiDrvModifyByteTPI(TPI_INDEX_REG_VALUE_ADDR, Mask, Value);
}


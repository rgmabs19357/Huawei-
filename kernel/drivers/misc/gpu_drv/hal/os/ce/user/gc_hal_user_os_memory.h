/****************************************************************************
*
*    Copyright (c) 2005 - 2013 by Vivante Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Vivante Corporation. This is proprietary information owned by
*    Vivante Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Vivante Corporation.
*
*****************************************************************************/


#ifndef __gc_hal_user_os_memory_h_
#define __gc_hal_user_os_memory_h_

#define _ISOC99_SOURCE

#include <string.h>

/*  Fill the specified memory with 0's. */
gcmINLINE void
gcoOS_ZeroMemory(
    IN gctPOINTER Memory,
    IN gctSIZE_T Bytes
    )
{
    /* Verify the arguments. */
    gcmASSERT(Memory != gcvNULL);
    gcmASSERT(Bytes > 0);

    /* Zero the memory. */
    memset(Memory, 0, Bytes);
}

/* Perform a memory copy. */
gcmINLINE void
gcoOS_MemCopy(
    IN gctPOINTER Destination,
    IN gctCONST_POINTER Source,
    IN gctSIZE_T Bytes
    )
{
    /* Verify the arguments. */
    gcmASSERT(Destination != gcvNULL);
    gcmASSERT(Source != gcvNULL);
    gcmASSERT(Bytes > 0);

    /* Copy the memory. */
    memcpy(Destination, Source, Bytes);
}

/* Perform a memory fill. */
gcmINLINE void
gcoOS_MemFill(
    IN gctPOINTER Memory,
    IN gctUINT8 Filler,
    IN gctSIZE_T Bytes
    )
{
    /* Verify the arguments. */
    gcmASSERT(Memory != gcvNULL);
    gcmASSERT(Bytes > 0);

    /* Fill the memory. */
    memset(Memory, Filler, Bytes);
}

gcmINLINE void
gcoOS_StrLen(
    IN gctCONST_STRING String,
    OUT gctSIZE_T * Length
    )
{
    /* Verify the arguments. */
    gcmASSERT(String != gcvNULL);
    gcmASSERT(Length != gcvNULL);

    /* Get the length of the string. */
    *Length = (gctSIZE_T) strlen(String);
}



#endif


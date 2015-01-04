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


#include "gc_hal_user_hardware_precomp.h"
#include "gc_hal_user.h"
#include "gc_hal_user_brush.h"

/* Zone used for header/footer. */
#define _GC_OBJ_ZONE    gcvZONE_HARDWARE

/* Multi-sample grid selection:
**
**  0   Square grid only.
**  1   Rotated diamonds but no jitter.
**  2   Rotated diamonds in a 2x2 jitter matrix.
*/
#define gcdGRID_QUALITY 1

/******************************************************************************\
********************************* Support Code *********************************
\******************************************************************************/

#define gcmTILE_OFFSET_X(X, Y, SuperTiled, SuperTileMode) \
        ((SuperTiled) ? \
            (SuperTileMode == 2) ? \
                /* coord = 21'{ X[21-1:6], Y[5],X[5],Y[4],X[4],
                                Y[3],X[3],Y[2],X[2],Y[1:0],X[1:0] }. */ \
                (((X) &  0x03) << 0) | \
                (((Y) &  0x03) << 2) | \
                (((X) &  0x04) << 2) | \
                (((Y) &  0x04) << 3) | \
                (((X) &  0x08) << 3) | \
                (((Y) &  0x08) << 4) | \
                (((X) &  0x10) << 4) | \
                (((Y) &  0x10) << 5) | \
                (((X) &  0x20) << 5) | \
                (((Y) &  0x20) << 6) | \
                (((X) & ~0x3F) << 6)   \
            : \
                (SuperTileMode == 1) ? \
                /* coord = 21'{ X[21-1:6], Y[5:4],X[5:3],Y[3:2],
                                X[2],Y[1:0],X[1:0] }. */ \
                (((X) &  0x03) << 0) | \
                (((Y) &  0x03) << 2) | \
                (((X) &  0x04) << 2) | \
                (((Y) &  0x0C) << 3) | \
                (((X) &  0x38) << 4) | \
                (((Y) &  0x30) << 6) | \
                (((X) & ~0x3F) << 6)   \
                : \
                    /* coord = 21'{ X[21-1:6], Y[5:2],X[5:2],
					                Y[1:0],X[1:0] }. */ \
                    (((X) &  0x03) << 0) | \
                    (((Y) &  0x03) << 2) | \
                    (((X) &  0x3C) << 2) | \
                    (((Y) &  0x3C) << 6) | \
                    (((X) & ~0x3F) << 6)   \
        : \
            /* 4x4 tiled. */     \
            ((X &  0x03) << 0) | \
            ((Y &  0x03) << 2) | \
            ((X & ~0x03) << 2) \
            )

#define gcmTILE_OFFSET_Y(X, Y, SuperTiled) \
    ((SuperTiled) ? ((Y) & ~0x3F) : ((Y) & ~0x03))

static gceSTATUS _ResetDelta(
    IN gcsSTATE_DELTA_PTR StateDelta
    )
{
    /* The delta should not be attached to any context. */
    gcmASSERT(StateDelta->refCount == 0);

    /* Not attached yet, advance the ID. */
    StateDelta->id += 1;

    /* Did ID overflow? */
    if (StateDelta->id == 0)
    {
        /* Reset the map to avoid erroneous ID matches. */
        gcoOS_ZeroMemory(
            gcmUINT64_TO_PTR(StateDelta->mapEntryID), StateDelta->mapEntryIDSize
            );

        /* Increment the main ID to avoid matches after reset. */
        StateDelta->id += 1;
    }

    /* Reset the vertex element count. */
    StateDelta->elementCount = 0;

    /* Reset the record count. */
    StateDelta->recordCount = 0;

    /* Success. */
    return gcvSTATUS_OK;
}

static gceSTATUS _MergeDelta(
    IN gcsSTATE_DELTA_PTR StateDelta
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcsSTATE_DELTA_PTR prevDelta;
    gcsSTATE_DELTA_RECORD_PTR record;
    gctUINT i, count;

    /* Get the record count. */
    count = StateDelta->recordCount;

    /* Set the first record. */
    record = gcmUINT64_TO_PTR(StateDelta->recordArray);

    /* Get the previous delta. */
    prevDelta = gcmUINT64_TO_PTR(StateDelta->prev);

    /* Go through all records. */
    for (i = 0; i < count; i += 1)
    {
        /* Update the delta. */
        gcmONERROR(gcoHARDWARE_UpdateDelta(
            prevDelta, gcvFALSE, record->address, record->mask, record->data
            ));

        /* Advance to the next state. */
        record += 1;
    }

    /* Update the element count. */
    if (StateDelta->elementCount != 0)
    {
        prevDelta->elementCount = StateDelta->elementCount;
    }

OnError:
    /* Return the status. */
    return status;
}

gceSTATUS gcoHARDWARE_UpdateDelta(
    IN gcsSTATE_DELTA_PTR StateDelta,
    IN gctBOOL FixedPoint,
    IN gctUINT32 Address,
    IN gctUINT32 Mask,
    IN gctUINT32 Data
    )
{
    gcsSTATE_DELTA_RECORD_PTR recordArray;
    gcsSTATE_DELTA_RECORD_PTR recordEntry;
    gctUINT32_PTR mapEntryID;
    gctUINT32_PTR mapEntryIndex;
    gctUINT deltaID;

    /* Get the current record array. */
    recordArray = gcmUINT64_TO_PTR(StateDelta->recordArray);

    /* Get shortcuts to the fields. */
    deltaID       = StateDelta->id;
    mapEntryID    = gcmUINT64_TO_PTR(StateDelta->mapEntryID);
    mapEntryIndex = gcmUINT64_TO_PTR(StateDelta->mapEntryIndex);

    /* Has the entry been initialized? */
    if (mapEntryID[Address] != deltaID)
    {
        /* No, initialize the map entry. */
        mapEntryID    [Address] = deltaID;
        mapEntryIndex [Address] = StateDelta->recordCount;

        /* Get the current record. */
        recordEntry = &recordArray[mapEntryIndex[Address]];

        /* Add the state to the list. */
        recordEntry->address = Address;
        recordEntry->mask    = Mask;
        recordEntry->data    = Data;

        /* Update the number of valid records. */
        StateDelta->recordCount += 1;
    }

    /* Regular (not masked) states. */
    else if (Mask == 0)
    {
        /* Get the current record. */
        recordEntry = &recordArray[mapEntryIndex[Address]];

        /* Update the state record. */
        recordEntry->mask = 0;
        recordEntry->data = Data;
    }

    /* Masked states. */
    else
    {
        /* Get the current record. */
        recordEntry = &recordArray[mapEntryIndex[Address]];

        /* Update the state record. */
        recordEntry->mask |=  Mask;
        recordEntry->data &= ~Mask;
        recordEntry->data |= (Data & Mask);
    }

    /* Success. */
    return gcvSTATUS_OK;
}

static gceSTATUS _LoadStates(
    IN gctUINT32 Address,
    IN gctBOOL FixedPoint,
    IN gctSIZE_T Count,
    IN gctUINT32 Mask,
    IN gctPOINTER Data
    )
{
    gceSTATUS status;
    gctUINT32_PTR source;
    gctUINT i;
    gcoHARDWARE hardware;

    /* Define state buffer variables. */
    gcmDEFINESTATEBUFFER(reserve, stateDelta, memory, reserveSize);

    gcmHEADER_ARG("Address=%x Count=%d Data=0x%x",
                  Address, Count, Data);

    /* Verify the arguments. */
    gcmGETHARDWARE(hardware);
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Cast the pointers. */
    source = (gctUINT32_PTR) Data;

    /* Determine the size of the buffer to reserve. */
    reserveSize = gcmALIGN((1 + Count) * gcmSIZEOF(gctUINT32), 8);

    /* Reserve space in the command buffer. */
    gcmBEGINSTATEBUFFER(hardware, reserve, stateDelta, memory, reserveSize);

    {    gcmASSERT(((memory - (gctUINT32_PTR) reserve->lastReserve) & 1) == 0);    gcmVERIFYLOADSTATEDONE(reserve);    gcmSTORELOADSTATE(reserve, memory, Address, Count );    *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | (((gctUINT32) ((gctUINT32) (FixedPoint) & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (Count ) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Address) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));gcmSKIPSECUREUSER();};

    for (i = 0; i < Count; i ++)
    {
        gcmSETSTATEDATA(
            stateDelta, reserve, memory, FixedPoint, Address + i,
            *source++
            );
    }

    if ((Count & 1) == 0)
    {
        gcmSETFILLER(
            reserve, memory
            );
    }

    gcmENDSTATEBATCH(
        reserve, memory
        );

    /* Validate the state buffer. */
    gcmENDSTATEBUFFER(reserve, memory, reserveSize);

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*
 * Support loading more than 1024 states in a batch.
 */
static gceSTATUS _LoadStatesEx(
    IN gctUINT32 Address,
    IN gctBOOL FixedPoint,
    IN gctSIZE_T Count,
    IN gctUINT32 Mask,
    IN gctPOINTER Data
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gctUINT32 i = 0;
    gctUINT32 count;
    gctUINT32 limit;

    gcmHEADER_ARG("Address=%x Count=%d Data=0x%x",
                  Address, Count, Data);

    limit = 2 << (25 - 16);

    while (Count)
    {
        count = gcmMIN(Count, limit);

        gcmONERROR(
            _LoadStates(Address + i,
                        FixedPoint,
                        count,
                        Mask,
                        (gctUINT8_PTR)Data + i));

        i += count;
        Count -= count;
    }

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

static gctUINT32 _SetBitWidth(
    gctUINT32 Value,
    gctINT8 CurWidth,
    gctINT8 NewWidth
    )
{
    gctUINT32 result;
    gctINT8 widthDiff;

    /* Mask source bits. */
    Value &= ((gctUINT64) 1 << CurWidth) - 1;

    /* Init the result. */
    result = Value;

    /* Determine the difference in width. */
    widthDiff = NewWidth - CurWidth;

    /* Until the difference is not zero... */
    while (widthDiff)
    {
        /* New value is thiner then current? */
        if (widthDiff < 0)
        {
            result >>= -widthDiff;
            widthDiff = 0;
        }

        /* Full source replication? */
        else if (widthDiff >= CurWidth)
        {
            result = (CurWidth == 32) ? Value
                                      : ((result << CurWidth) | Value);
            widthDiff -= CurWidth;
        }

        /* Partial source replication. */
        else
        {
            result = (result << widthDiff) | (Value >> (CurWidth - widthDiff));
            widthDiff = 0;
        }
    }

    /* Return result. */
    return result;
}

static gceSTATUS
_ConvertComponent(
    gctUINT8* SrcPixel,
    gctUINT8* TrgPixel,
    gctUINT SrcBit,
    gctUINT TrgBit,
    gcsFORMAT_COMPONENT* SrcComponent,
    gcsFORMAT_COMPONENT* TrgComponent,
    gcsBOUNDARY_PTR SrcBoundary,
    gcsBOUNDARY_PTR TrgBoundary,
    gctUINT32 Default
    )
{
    gctUINT32 srcValue;
    gctUINT8 srcWidth;
    gctUINT8 trgWidth;
    gctUINT32 trgMask;
    gctUINT32 bits;

    /* Exit if target is beyond the boundary. */
    if ((TrgBoundary != gcvNULL) &&
        ((TrgBoundary->x < 0) || (TrgBoundary->x >= TrgBoundary->width) ||
         (TrgBoundary->y < 0) || (TrgBoundary->y >= TrgBoundary->height)))
    {
        return gcvSTATUS_SKIP;
    }

    /* Exit if target component is not present. */
    if (TrgComponent->width == gcvCOMPONENT_NOTPRESENT)
    {
        return gcvSTATUS_SKIP;
    }

    /* Extract target width. */
    trgWidth = TrgComponent->width & gcvCOMPONENT_WIDTHMASK;

    /* Extract the source. */
    if ((SrcComponent == gcvNULL) ||
        (SrcComponent->width == gcvCOMPONENT_NOTPRESENT) ||
        (SrcComponent->width &  gcvCOMPONENT_DONTCARE)   ||
        ((SrcBoundary != gcvNULL) &&
         ((SrcBoundary->x < 0) || (SrcBoundary->x >= SrcBoundary->width) ||
          (SrcBoundary->y < 0) || (SrcBoundary->y >= SrcBoundary->height))))
    {
        srcValue = Default;
        srcWidth = 32;
    }
    else
    {
        /* Extract source width. */
        srcWidth = SrcComponent->width & gcvCOMPONENT_WIDTHMASK;

        /* Compute source position. */
        SrcBit += SrcComponent->start;
        SrcPixel += SrcBit >> 3;
        SrcBit &= 7;

        /* Compute number of bits to read from source. */
        bits = SrcBit + srcWidth;

        /* Read the value. */
        srcValue = SrcPixel[0] >> SrcBit;

        if (bits > 8)
        {
            /* Read up to 16 bits. */
            srcValue |= SrcPixel[1] << (8 - SrcBit);
        }

        if (bits > 16)
        {
            /* Read up to 24 bits. */
            srcValue |= SrcPixel[2] << (16 - SrcBit);
        }

        if (bits > 24)
        {
            /* Read up to 32 bits. */
            srcValue |= SrcPixel[3] << (24 - SrcBit);
        }
    }

    /* Make the source component the same width as the target. */
    srcValue = _SetBitWidth(srcValue, srcWidth, trgWidth);

    /* Compute destination position. */
    TrgBit += TrgComponent->start;
    TrgPixel += TrgBit >> 3;
    TrgBit &= 7;

    /* Determine the target mask. */
    trgMask = (gctUINT32) (((gctUINT64) 1 << trgWidth) - 1);
    trgMask <<= TrgBit;

    /* Align the source value. */
    srcValue <<= TrgBit;

    /* Loop while there are bits to set. */
    while (trgMask != 0)
    {
        /* Set 8 bits of the pixel value. */
        if ((trgMask & 0xFF) == 0xFF)
        {
            /* Set all 8 bits. */
            *TrgPixel = (gctUINT8) srcValue;
        }
        else
        {
            /* Set the required bits. */
            *TrgPixel = (gctUINT8) ((*TrgPixel & ~trgMask) | srcValue);
        }

        /* Next 8 bits. */
        TrgPixel ++;
        trgMask  >>= 8;
        srcValue >>= 8;
    }

    return gcvSTATUS_OK;
}


/******************************************************************************\
****************************** gcoHARDWARE API code ****************************
\******************************************************************************/

/*******************************************************************************
**
**  gcoHARDWARE_Construct
**
**  Construct a new gcoHARDWARE object.
**
**  INPUT:
**
**      gcoHAL Hal
**          Pointer to an gcoHAL object.
**
**  OUTPUT:
**
**      gcoHARDWARE * Hardware
**          Pointer to a variable that will hold the gcoHARDWARE object.
*/
gceSTATUS
gcoHARDWARE_Construct(
    IN gcoHAL Hal,
    OUT gcoHARDWARE * Hardware
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware = gcvNULL;
    gcsHAL_INTERFACE iface;
    gctUINT16 data = 0xff00;
    gctPOINTER pointer;
    gctUINT i;

    gcmHEADER_ARG("Hal=0x%x", Hal);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hal, gcvOBJ_HAL);
    gcmDEBUG_VERIFY_ARGUMENT(Hardware != gcvNULL);

    /***************************************************************************
    ** Allocate and reset the gcoHARDWARE object.
    */

    gcmONERROR(gcoOS_Allocate(gcvNULL,
                              gcmSIZEOF(struct _gcoHARDWARE),
                              &pointer));
    hardware = pointer;

    /* Reset the object. */
    gcoOS_ZeroMemory(hardware, gcmSIZEOF(struct _gcoHARDWARE));

    /* Initialize the gcoHARDWARE object. */
    hardware->object.type = gcvOBJ_HARDWARE;

    hardware->buffer = gcvNULL;
    hardware->queue  = gcvNULL;

    /* Check if big endian */
    hardware->bigEndian = (*(gctUINT8 *)&data == 0xff);

    /* Don't stall before primitive. */
    hardware->stallPrimitive = gcvFALSE;



    /***********************************************************************
    ** Query chip identity.
    */

    iface.command = gcvHAL_QUERY_CHIP_IDENTITY;

    gcmONERROR(gcoOS_DeviceControl(
        gcvNULL,
        IOCTL_GCHAL_INTERFACE,
        &iface, gcmSIZEOF(iface),
        &iface, gcmSIZEOF(iface)
        ));

    hardware->chipModel              = iface.u.QueryChipIdentity.chipModel;
    hardware->chipRevision           = iface.u.QueryChipIdentity.chipRevision;
    hardware->chipFeatures           = iface.u.QueryChipIdentity.chipFeatures;
    hardware->chipMinorFeatures      = iface.u.QueryChipIdentity.chipMinorFeatures;
    hardware->chipMinorFeatures1     = iface.u.QueryChipIdentity.chipMinorFeatures1;
    hardware->chipMinorFeatures2     = iface.u.QueryChipIdentity.chipMinorFeatures2;
    hardware->chipMinorFeatures3     = iface.u.QueryChipIdentity.chipMinorFeatures3;
    hardware->pixelPipes             = iface.u.QueryChipIdentity.pixelPipes;


    /***************************************************************************
    ** Allocate the gckCONTEXT object.
    */

    iface.command = gcvHAL_ATTACH;

    gcmONERROR(gcoOS_DeviceControl(
        gcvNULL,
        IOCTL_GCHAL_INTERFACE,
        &iface, gcmSIZEOF(iface),
        &iface, gcmSIZEOF(iface)
        ));

    gcmONERROR(iface.status);

    /* Store the allocated context buffer object. */
    hardware->context = gcmINT2PTR(iface.u.Attach.context);
    gcmASSERT(hardware->context != gcvNULL);

    /* Store the number of states in the context. */
    hardware->stateCount = (gctSIZE_T) iface.u.Attach.stateCount;


    /**************************************************************************/
    /* Allocate the context and state delta buffers. **************************/

    for (i = 0; i < gcdCONTEXT_BUFFER_COUNT + 1; i += 1)
    {
        /* Allocate a state delta. */
        gcsSTATE_DELTA_PTR delta;
        gcsSTATE_DELTA_PTR prev;
        gctUINT bytes;

        /* Allocate the state delta structure. */
        gcmONERROR(gcoOS_Allocate(
            gcvNULL, gcmSIZEOF(gcsSTATE_DELTA), (gctPOINTER *) &delta
            ));

        /* Reset the context buffer structure. */
        gcoOS_ZeroMemory(delta, gcmSIZEOF(gcsSTATE_DELTA));

        /* Append to the list. */
        if (hardware->delta == gcvNULL)
        {
            delta->prev     = gcmPTR_TO_UINT64(delta);
            delta->next     = gcmPTR_TO_UINT64(delta);
            hardware->delta = delta;
        }
        else
        {
            delta->next = gcmPTR_TO_UINT64(hardware->delta);
            delta->prev = hardware->delta->prev;

            prev = gcmUINT64_TO_PTR(hardware->delta->prev);
            prev->next = gcmPTR_TO_UINT64(delta);
            hardware->delta->prev = gcmPTR_TO_UINT64(delta);

        }

        /* Set the number of delta in the order of creation. */
#if gcmIS_DEBUG(gcdDEBUG_CODE)
        delta->num = i;
#endif
        if (hardware->stateCount > 0)
        {
            /* Allocate state record array. */
            gcmONERROR(gcoOS_Allocate(
                gcvNULL,
                gcmSIZEOF(gcsSTATE_DELTA_RECORD) * hardware->stateCount,
                &pointer
                ));
            delta->recordArray = gcmPTR_TO_UINT64(pointer);

            /* Compute UINT array size. */
            bytes = gcmSIZEOF(gctUINT) * hardware->stateCount;

            /* Allocate map ID array. */
            gcmONERROR(gcoOS_Allocate(
                gcvNULL, bytes, &pointer
                ));
            delta->mapEntryID = gcmPTR_TO_UINT64(pointer);

            /* Set the map ID size. */
            delta->mapEntryIDSize = bytes;

            /* Reset the record map. */
            gcoOS_ZeroMemory(gcmUINT64_TO_PTR(delta->mapEntryID), bytes);

            /* Allocate map index array. */
            gcmONERROR(gcoOS_Allocate(
                gcvNULL, bytes, &pointer
                ));
            delta->mapEntryIndex = gcmPTR_TO_UINT64(pointer);
        }

        /* Reset the new state delta. */
        _ResetDelta(delta);
    }

    /***********************************************************************
    ** Construct the command buffer and event queue.
    */

   gcmONERROR(gcoBUFFER_Construct(
        Hal,
        hardware,
        hardware->context,
        gcdCMD_BUFFER_SIZE,
        &hardware->buffer
        ));

    gcmONERROR(gcoQUEUE_Construct(gcvNULL, &hardware->queue));

    for (i = 0; i < gcdTEMP_SURFACE_NUMBER; i += 1)
    {
        hardware->temp2DSurf[i] = gcvNULL;
    }

    hardware->hw2DEnableGDIStretch = gcvFALSE;

    /***********************************************************************
    ** Initialize filter blit states.
    */
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_UNIFIED].type  = gcvFILTER_SYNC;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_UNIFIED].kernelSize  = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_UNIFIED].scaleFactor = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_UNIFIED].kernelAddress = 0x01800;

    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_VERTICAL].type  = gcvFILTER_SYNC;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_VERTICAL].kernelSize  = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_VERTICAL].scaleFactor = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_VERTICAL].kernelAddress = 0x02A00;

    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_HORIZONTAL].type  = gcvFILTER_SYNC;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_HORIZONTAL].kernelSize  = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_HORIZONTAL].scaleFactor = 0;
    hardware->loadedKernel[gcvFILTER_BLIT_KERNEL_HORIZONTAL].kernelAddress = 0x02800;

    /***********************************************************************
    ** Reset the temporary surface.
    */

    gcoOS_ZeroMemory(&hardware->tempBuffer, sizeof(hardware->tempBuffer));

    hardware->tempBuffer.node.pool = gcvPOOL_UNKNOWN;

    /***********************************************************************
    ** Determine available features.
    */

    /* Determine whether 2D hardware is present. */
    hardware->hw2DEngine = ((((gctUINT32) (hardware->chipFeatures)) >> (0 ? 9:9) & ((gctUINT32) ((((1 ? 9:9) - (0 ? 9:9) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 9:9) - (0 ? 9:9) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 9:9) - (0 ? 9:9) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 9:9) - (0 ? 9:9) + 1)))))));

    /* Don't force software by default. */
    hardware->sw2DEngine = gcvFALSE;

    hardware->hw3DEngine = gcvFALSE;

    hardware->currentPipe = (hardware->hw2DEngine) ? gcvPIPE_2D : gcvPIPE_3D;

    /* Determine whether PE 2.0 is present. */
    hardware->hw2DPE20 = ((((gctUINT32) (hardware->chipMinorFeatures)) >> (0 ? 7:7) & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1)))))));

    /* Determine whether byte write feature is present in the chip. */
    hardware->byteWrite = ((((gctUINT32) (hardware->chipFeatures)) >> (0 ? 19:19) & ((gctUINT32) ((((1 ? 19:19) - (0 ? 19:19) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 19:19) - (0 ? 19:19) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 19:19) - (0 ? 19:19) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 19:19) - (0 ? 19:19) + 1)))))));

    /* Determine whether full rotation is present in the chip. */
    hardware->fullBitBlitRotation = hardware->fullFilterBlitRotation
        = hardware->hw2DPE20;
    if (hardware->chipRevision < 0x4310)
    {
        hardware->fullBitBlitRotation    = gcvFALSE;
        hardware->fullFilterBlitRotation = gcvFALSE;
    }
    else if (hardware->chipRevision == 0x4310)
    {
        hardware->fullBitBlitRotation    = gcvTRUE;
        hardware->fullFilterBlitRotation = gcvFALSE;
    }
    else if (hardware->chipRevision >= 0x4400)
    {
        hardware->fullBitBlitRotation    = gcvTRUE;
        hardware->fullFilterBlitRotation = gcvTRUE;
    }

    /* MASK register is missing on 4.3.1_rc0. */
    if (hardware->chipRevision == 0x4310)
    {
        hardware->shadowRotAngleReg = gcvTRUE;
        hardware->rotAngleRegShadow = 0x00000000;
    }
    else
    {
        hardware->shadowRotAngleReg = gcvFALSE;
    }

    hardware->dither2DandAlphablendFilter = ((((gctUINT32) (hardware->chipMinorFeatures1)) >> (0 ? 16:16) & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1)))))));

    hardware->mirrorExtension = ((((gctUINT32) (hardware->chipMinorFeatures1)) >> (0 ? 18:18) & ((gctUINT32) ((((1 ? 18:18) - (0 ? 18:18) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 18:18) - (0 ? 18:18) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 18:18) - (0 ? 18:18) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 18:18) - (0 ? 18:18) + 1)))))));

    /* Determine whether we support full DFB features. */
    hardware->hw2DFullDFB = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 16:16) & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1)))))));

    /* Determine whether we support one pass filter. */
    hardware->hw2DOPF = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 17:17) & ((gctUINT32) ((((1 ? 17:17) - (0 ? 17:17) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:17) - (0 ? 17:17) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 17:17) - (0 ? 17:17) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:17) - (0 ? 17:17) + 1)))))));

    /* Determine whether we support multi-source blit. */
    hardware->hw2DMultiSrcBlit = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 21:21) & ((gctUINT32) ((((1 ? 21:21) - (0 ? 21:21) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:21) - (0 ? 21:21) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 21:21) - (0 ? 21:21) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:21) - (0 ? 21:21) + 1)))))));

    hardware->hw2DNewFeature0 = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 2:2) & ((gctUINT32) ((((1 ? 2:2) - (0 ? 2:2) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:2) - (0 ? 2:2) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 2:2) - (0 ? 2:2) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:2) - (0 ? 2:2) + 1)))))));

    if (hardware->hw2DNewFeature0)
    {
        hardware->hw2DMultiSrcBlit = gcvTRUE;
    }

    hardware->hw2D420L2Cache = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 26:26) & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1)))))));

    hardware->hw2DNoIndex8_Brush = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 28:28) & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1)))))));


    if (hardware->chipModel == gcv320)
    {
        hardware->hw2DAppendCacheFlush = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 23:23) & ((gctUINT32) ((((1 ? 23:23) - (0 ? 23:23) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 23:23) - (0 ? 23:23) + 1)))))) == (0x0  & ((gctUINT32) ((((1 ? 23:23) - (0 ? 23:23) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 23:23) - (0 ? 23:23) + 1)))))));
    }

    hardware->hw2DDEEnhance1 = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 17:17) & ((gctUINT32) ((((1 ? 17:17) - (0 ? 17:17) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:17) - (0 ? 17:17) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 17:17) - (0 ? 17:17) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:17) - (0 ? 17:17) + 1)))))));

    hardware->mmuVersion
        = (((((gctUINT32) (hardware->chipMinorFeatures1)) >> (0 ? 28:28)) & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1)))))) );

	hardware->hw2DCacheFlushSurf = gcvNULL;

    gcmONERROR(gcoOS_CreateSignal(gcvNULL, gcvFALSE, &hardware->stallSignal));

    gcmTRACE_ZONE(
        gcvLEVEL_INFO, gcvZONE_SIGNAL,
        "%s(%d): stall created signal 0x%08X\n",
        __FUNCTION__, __LINE__,
        hardware->stallSignal);

	if (gcvSTATUS_TRUE == gcoOS_DetectProcessByEncryptedName(/* "com.letanginc.highwaydrive" */ "\x9c\x90\x92\xd1\x93\x9a\x8b\x9e\x91\x98\x96\x91\x9c\xd1\x97\x96\x98\x97\x88\x9e\x86\x9b\x8d\x96\x89\x9a"))
	{
	    hardware->disableRoundUV = gcvTRUE;
	}
	else
	{
	    hardware->disableRoundUV = gcvFALSE;
	}

#if gcdSYNC
    hardware->fence = gcvNULL;
#endif

    /* Return pointer to the gcoHARDWARE object. */
    *Hardware = hardware;

    /* Success. */
    gcmFOOTER_ARG("*Hardware=0x%x", *Hardware);
    return gcvSTATUS_OK;

OnError:
    if (hardware != gcvNULL)
    {
        gcmVERIFY_OK(gcoHARDWARE_Destroy(hardware));
    }

    /* Return pointer to the gcoHARDWARE object. */
    *Hardware = gcvNULL;

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Destroy
**
**  Destroy an gcoHARDWARE object.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object that needs to be destroyed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS gcoHARDWARE_Destroy(
    IN gcoHARDWARE Hardware
    )
{
    gceSTATUS status;
    gcsSTATE_DELTA_PTR deltaHead;
    gctINT i;

    gcmHEADER_ARG("Hardware=0x%x", Hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);


    if (Hardware->hw2DCacheFlushSurf)
    {
        gcmONERROR(gcoHARDWARE_Put2DTempSurface(
            Hardware->hw2DCacheFlushSurf));

        Hardware->hw2DCacheFlushSurf = gcvNULL;
    }

    /* Destroy temporary surface */
    if (Hardware->tempSurface != gcvNULL)
    {
        gcmONERROR(gcoSURF_Destroy(Hardware->tempSurface));
        Hardware->tempSurface = gcvNULL;
    }

    for (i = 0; i < gcdTEMP_SURFACE_NUMBER; i += 1)
    {
        gcsSURF_INFO_PTR surf = Hardware->temp2DSurf[i];

        if (surf != gcvNULL)
        {
            if (surf->node.valid)
            {
                gcmONERROR(gcoHARDWARE_Unlock(
                    &surf->node, gcvSURF_BITMAP
                    ));
            }

            /* Free the video memory by event. */
            if (surf->node.u.normal.node != 0)
            {
                gcmONERROR(gcoHARDWARE_ScheduleVideoMemory(
                    &Hardware->temp2DSurf[i]->node
                    ));

                surf->node.u.normal.node = 0;
            }

            gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, Hardware->temp2DSurf[i]));
        }
    }


    /* Destroy the command buffer. */
    if (Hardware->buffer != gcvNULL)
    {
        gcmONERROR(gcoBUFFER_Destroy(Hardware->buffer));
        Hardware->buffer = gcvNULL;
    }

    if (Hardware->queue != gcvNULL)
    {
        /* Commit the event queue. */
        status = gcoQUEUE_Commit(Hardware->queue);

        if (gcmIS_SUCCESS(status))
        {
            gcmONERROR(gcoHARDWARE_Stall());
        }
        else
        {
            gcmTRACE(
                gcvLEVEL_ERROR,
                "%s(%d): Failed to commit event queue (%d).\n",
                __FUNCTION__, __LINE__, status
                );
        }

        /* Destroy the event queue. */
        gcmONERROR(gcoQUEUE_Destroy(Hardware->queue));
        Hardware->queue = gcvNULL;
    }

    /* Free state deltas. */
    for (deltaHead = Hardware->delta; Hardware->delta != gcvNULL;)
    {
        /* Get a shortcut to the current delta. */
        gcsSTATE_DELTA_PTR delta = Hardware->delta;
        gctUINT_PTR mapEntryIndex = gcmUINT64_TO_PTR(delta->mapEntryIndex);
        gctUINT_PTR mapEntryID = gcmUINT64_TO_PTR(delta->mapEntryID);
        gcsSTATE_DELTA_RECORD_PTR recordArray = gcmUINT64_TO_PTR(delta->recordArray);

        /* Get the next delta. */
        gcsSTATE_DELTA_PTR next = gcmUINT64_TO_PTR(delta->next);

        /* Last item? */
        if (next == deltaHead)
        {
            next = gcvNULL;
        }

        /* Free map index array. */
        if (mapEntryIndex != gcvNULL)
        {
            gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, mapEntryIndex));
        }

        /* Allocate map ID array. */
        if (mapEntryID != gcvNULL)
        {
            gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, mapEntryID));
        }

        /* Free state record array. */
        if (recordArray != gcvNULL)
        {
            gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, recordArray));
        }

        /* Free state delta. */
        gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, delta));

        /* Remove from the list. */
        Hardware->delta = next;
    }

    /* Detach the process. */
    if (Hardware->context != gcvNULL)
    {
        gcsHAL_INTERFACE iface;
        iface.command = gcvHAL_DETACH;
        iface.u.Detach.context = gcmPTR2INT(Hardware->context);

        gcmONERROR(gcoOS_DeviceControl(
            gcvNULL,
            IOCTL_GCHAL_INTERFACE,
            &iface, gcmSIZEOF(iface),
            &iface, gcmSIZEOF(iface)
            ));

        Hardware->context = gcvNULL;
    }

    /* Free temporary buffer allocated by filter blit operation. */
    /* Is there a surface allocated? */
    if (Hardware->tempBuffer.node.pool != gcvPOOL_UNKNOWN)
    {
        /* Delete immediately. */
        gcsHAL_INTERFACE iface;

        /* Free the video memory. */
        iface.command = gcvHAL_FREE_VIDEO_MEMORY;
        iface.u.FreeVideoMemory.node = Hardware->tempBuffer.node.u.normal.node;

        /* Call kernel API. */
        gcmONERROR(gcoOS_DeviceControl(
            gcvNULL,
            IOCTL_GCHAL_INTERFACE,
            &iface, gcmSIZEOF(iface),
            &iface, gcmSIZEOF(iface)
            ));

        /* Reset the temporary surface. */
        gcoOS_ZeroMemory(&Hardware->tempBuffer, sizeof(Hardware->tempBuffer));

        Hardware->tempBuffer.node.pool = gcvPOOL_UNKNOWN;
    }

    /* Destroy the stall signal. */
    if (Hardware->stallSignal != gcvNULL)
    {
        gcmONERROR(gcoOS_DestroySignal(gcvNULL, Hardware->stallSignal));
        Hardware->stallSignal = gcvNULL;
    }

    /* Mark the gcoHARDWARE object as unknown. */
    Hardware->object.type = gcvOBJ_UNKNOWN;

    /* Free the gcoHARDWARE object. */
    gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, Hardware));

OnError:
    /* Return the status. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoHARDWARE_LoadState
**
**  Load a state buffer.
**
**  INPUT:
**
**      gctUINT32 Address
**          Starting register address of the state buffer.
**
**      gctUINT32 Count
**          Number of states in state buffer.
**
**      gctPOINTER Data
**          Pointer to state buffer.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_LoadState(
    IN gctUINT32 Address,
    IN gctSIZE_T Count,
    IN gctPOINTER Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Address=%x Count=%d Data=0x%x",
                  Address, Count, Data);

    /* Call generic function. */
    gcmONERROR(_LoadStatesEx(Address >> 2, gcvFALSE, Count, 0, Data));

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_LoadState32
**
**  Load one 32-bit state.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gctUINT32 Address
**          Register address of the state.
**
**      gctUINT32 Data
**          Value of the state.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_LoadState32(
    IN gcoHARDWARE Hardware,
    IN gctUINT32 Address,
    IN gctUINT32 Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Address=%x Data=0x%x",
                  Address, Data);

    /* Call generic function. */
    gcmONERROR(_LoadStates(Address >> 2, gcvFALSE, 1, 0, &Data));

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_LoadState32x
**
**  Load one 32-bit state, which is represented in 16.16 fixed point.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gctUINT32 Address
**          Register address of the state.
**
**      gctFIXED_POINT Data
**          Value of the state in 16.16 fixed point format.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_LoadState32x(
    IN gcoHARDWARE Hardware,
    IN gctUINT32 Address,
    IN gctFIXED_POINT Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Address=%x Data=0x%x",
                  Address, Data);

    /* Call generic function. */
    gcmONERROR(_LoadStates(Address >> 2, gcvTRUE, 1, 0, &Data));

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_LoadState64
**
**  Load one 64-bit state.
**
**  INPUT:
**
**      gctUINT32 Address
**          Register address of the state.
**
**      gctUINT64 Data
**          Value of the state.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_LoadState64(
    IN gctUINT32 Address,
    IN gctUINT64 Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Address=%x Data=0x%x",
                  Address, Data);

    /* Call generic function. */
    gcmONERROR(_LoadStates(Address >> 2, gcvFALSE, 2, 0, &Data));

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_Commit
**
**  Commit the current command buffer to the hardware.
**
**  INPUT:
**
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_Commit(
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER();

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Dump the commit. */
    gcmDUMP(gcvNULL, "@[commit]");

    /* Commit command buffer and return status. */
    status = gcoBUFFER_Commit(
        hardware->buffer,
        hardware->currentPipe,
        hardware->delta,
        hardware->queue
        );

    /* Did the delta become associated? */
    if (hardware->delta->refCount == 0)
    {
        /* No, merge with the previous. */
        _MergeDelta(hardware->delta);
    }
    else
    {
        /* The delta got associated, move to the next one. */
        hardware->delta = gcmUINT64_TO_PTR(hardware->delta->next);
        gcmASSERT(hardware->delta->refCount == 0);
    }

    /* Reset the current. */
    _ResetDelta(hardware->delta);

#if gcdSYNC
    if (!gcmIS_ERROR(status))
    {
        if (hardware->fence)
        {
            if (hardware->fence->type == gcvFENCE_OQ)
            {
                hardware->fence->u.oqFence.commitSlot = hardware->fence->u.oqFence.commandSlot;
            }
            hardware->fence->commitID = hardware->fence->fenceIDSend;
        }
    }
#endif

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Stall
**
**  Stall the thread until the hardware is finished.
**
**  INPUT:
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_Stall(
    )
{
    gcsHAL_INTERFACE iface;
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER();

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Dump the stall. */
    gcmDUMP(gcvNULL, "@[stall]");

    /* Create a signal event. */
    iface.command            = gcvHAL_SIGNAL;
    iface.u.Signal.signal    = gcmPTR_TO_UINT64(hardware->stallSignal);
    iface.u.Signal.auxSignal = 0;
    iface.u.Signal.process   = gcmPTR_TO_UINT64(gcoOS_GetCurrentProcessID());
    iface.u.Signal.fromWhere = gcvKERNEL_PIXEL;

    /* Send the event. */
    gcmONERROR(gcoHARDWARE_CallEvent(&iface));

    /* Commit the event queue. */
    gcmONERROR(gcoQUEUE_Commit(hardware->queue));

    /* Wait for the signal. */
    gcmONERROR(
        gcoOS_WaitSignal(gcvNULL, hardware->stallSignal, gcvINFINITE));

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_Lock
**
**  Lock video memory.
**
**  INPUT:
**
**      gcsSURF_NODE_PTR Node
**          Pointer to a gcsSURF_NODE structure that describes the video
**          memory to lock.
**
**  OUTPUT:
**
**      gctUINT32 * Address
**          Physical address of the surface.
**
**      gctPOINTER * Memory
**          Logical address of the surface.
*/
gceSTATUS
gcoHARDWARE_Lock(
    IN gcsSURF_NODE_PTR Node,
    OUT gctUINT32 * Address,
    OUT gctPOINTER * Memory
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Node=0x%x Address=0x%x Memory=0x%x",
                  Node, Address, Memory);

    if (!Node->valid)
    {
        gcsHAL_INTERFACE iface;

        /* User pools have to be mapped first. */
        if (Node->pool == gcvPOOL_USER)
        {
            gcmONERROR(gcvSTATUS_MEMORY_UNLOCKED);
        }

        /* Fill in the kernel call structure. */
        iface.command = gcvHAL_LOCK_VIDEO_MEMORY;
        iface.u.LockVideoMemory.node = Node->u.normal.node;
        iface.u.LockVideoMemory.cacheable = Node->u.normal.cacheable;

        /* Call the kernel. */
        gcmONERROR(gcoOS_DeviceControl(
            gcvNULL,
            IOCTL_GCHAL_INTERFACE,
            &iface, sizeof(iface),
            &iface, sizeof(iface)
            ));

        /* Success? */
        gcmONERROR(iface.status);

        /* Validate the node. */
        Node->valid = gcvTRUE;

        /* Store pointers. */
        Node->physical = iface.u.LockVideoMemory.address;
        Node->logical  = gcmUINT64_TO_PTR(iface.u.LockVideoMemory.memory);

        /* Set locked in the kernel flag. */
        Node->lockedInKernel = gcvTRUE;
        gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL, &Node->lockedHardwareType));
    }

    /* Increment the lock count. */
    Node->lockCount++;

    /* Set the result. */
    if (Address != gcvNULL)
    {
        *Address = Node->physical;
    }

    if (Memory != gcvNULL)
    {
        *Memory = Node->logical;
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Unlock
**
**  Unlock video memory.
**
**  INPUT:
**
**      gcsSURF_NODE_PTR Node
**          Pointer to a gcsSURF_NODE structure that describes the video
**          memory to unlock.
**
**      gceSURF_TYPE Type
**          Type of surface to unlock.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_Unlock(
    IN gcsSURF_NODE_PTR Node,
    IN gceSURF_TYPE Type
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcsHAL_INTERFACE iface;
    gctBOOL currentTypeChanged = gcvFALSE;
    gceHARDWARE_TYPE currentType = gcvHARDWARE_INVALID;

    gcmHEADER_ARG("Node=0x%x Type=%d",
                   Node, Type);

    /* Verify whether the node is valid. */
    if (!Node->valid || (Node->lockCount <= 0))
    {
        gcmTRACE_ZONE(
            gcvLEVEL_WARNING, gcvZONE_SURFACE,
            "gcoHARDWARE_Unlock: Node=0x%x; unlock called on an unlocked surface.",
            Node
            );
    }

    /* Locked more then once? */
    else if (--Node->lockCount == 0)
    {
        if (Node->lockedInKernel)
        {
            /* Save the current hardware type */
            gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL, &currentType));

            if (Node->lockedHardwareType != currentType)
            {
                /* Change to the locked hardware type */
                gcmVERIFY_OK(gcoHAL_SetHardwareType(gcvNULL, Node->lockedHardwareType));
                currentTypeChanged = gcvTRUE;
            }

            /* Unlock the video memory node. */
            iface.command = gcvHAL_UNLOCK_VIDEO_MEMORY;
            iface.u.UnlockVideoMemory.node = Node->u.normal.node;
            iface.u.UnlockVideoMemory.type = Type & ~gcvSURF_NO_VIDMEM;
            iface.u.UnlockVideoMemory.asynchroneous = gcvTRUE;

            /* Call the kernel. */
            gcmONERROR(gcoOS_DeviceControl(
                gcvNULL,
                IOCTL_GCHAL_INTERFACE,
                &iface, gcmSIZEOF(iface),
                &iface, gcmSIZEOF(iface)
                ));

            /* Success? */
            gcmONERROR(iface.status);

            /* Do we need to schedule an event for the unlock? */
            if (iface.u.UnlockVideoMemory.asynchroneous)
            {
                iface.u.UnlockVideoMemory.asynchroneous = gcvFALSE;
                gcmONERROR(gcoHARDWARE_CallEvent(&iface));

                if (currentTypeChanged)
                {
                    gcmONERROR(gcoHARDWARE_Commit());
                }
            }

            /* Reset locked in the kernel flag. */
            Node->lockedInKernel = gcvFALSE;

            if (currentTypeChanged)
            {
                /* Restore the current hardware type */
                gcmVERIFY_OK(gcoHAL_SetHardwareType(gcvNULL, currentType));
                currentTypeChanged = gcvFALSE;
            }
        }

        /* Reset the valid flag. */
        if ((Node->pool == gcvPOOL_CONTIGUOUS) ||
            (Node->pool == gcvPOOL_VIRTUAL))
        {
            Node->valid = gcvFALSE;
        }
    }

    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    if (currentTypeChanged)
    {
        /* Restore the current hardware type */
        gcmVERIFY_OK(gcoHAL_SetHardwareType(gcvNULL, currentType));
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_CallEvent
**
**  Send an event to the kernel and append the required synchronization code to
**  the command buffer..
**
**  INPUT:
**
**      gcsHAL_INTERFACE * Interface
**          Pointer to an gcsHAL_INTERFACE structure the defines the event to
**          send.
**
**  OUTPUT:
**
**      gcsHAL_INTERFACE * Interface
**          Pointer to an gcsHAL_INTERFACE structure the received information
**          from the kernel.
*/
gceSTATUS
gcoHARDWARE_CallEvent(
    IN OUT gcsHAL_INTERFACE * Interface
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Interface=0x%x", Interface);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(Interface != gcvNULL);

    /* Append the event to the event queue. */
    gcmONERROR(gcoQUEUE_AppendEvent(hardware->queue, Interface));

#if gcdIN_QUEUE_RECORD_LIMIT
    if (hardware->queue->recordCount >= gcdIN_QUEUE_RECORD_LIMIT)
    {
        gcmONERROR(gcoHARDWARE_Commit());
    }
#endif

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_ScheduleVideoMemory
**
**  Schedule destruction for the specified video memory node.
**
**  INPUT:
**
**      gcsSURF_NODE_PTR Node
**          Pointer to the video momory node to be destroyed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_ScheduleVideoMemory(
    IN gcsSURF_NODE_PTR Node
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Node=0x%x", Node);

    if (Node->pool != gcvPOOL_USER)
    {
        gcsHAL_INTERFACE iface;

        gcmTRACE_ZONE(gcvLEVEL_VERBOSE, gcvZONE_HARDWARE,
                      "node=0x%08x",
                      Node->u.normal.node);

        /* Free the allocated video memory asynchronously. */
        iface.command = gcvHAL_FREE_VIDEO_MEMORY;
        iface.u.FreeVideoMemory.node = Node->u.normal.node;

        /* Call kernel HAL. */
        gcmONERROR(gcoHARDWARE_CallEvent(&iface));
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_AllocateTemporarySurface
**
**  Allocates a temporary surface with specified parameters.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to a gcoHARDWARE object.
**
**      gctUINT Width, Height
**          The aligned size of the surface to be allocated.
**
**      gcsSURF_FORMAT_INFO_PTR Format
**          The format of the surface to be allocated.
**
**      gceSURF_TYPE Type
**          The type of the surface to be allocated.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_AllocateTemporarySurface(
    IN gcoHARDWARE Hardware,
    IN gctUINT Width,
    IN gctUINT Height,
    IN gcsSURF_FORMAT_INFO_PTR Format,
    IN gceSURF_TYPE Type
    )
{
    gceSTATUS status;
    gcsHAL_INTERFACE iface;

    gcmHEADER_ARG("Hardware=0x%x Width=%d Height=%d "
                    "Format=%d Type=%d",
                    Hardware, Width, Height,
                    *Format, Type);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    /* Do we have a compatible surface? */
    if ((Hardware->tempBuffer.type == Type) &&
        (Hardware->tempBuffer.format == Format->format) &&
        (Hardware->tempBuffer.rect.right == (gctINT) Width) &&
        (Hardware->tempBuffer.rect.bottom == (gctINT) Height))
    {
        status = gcvSTATUS_OK;
    }
    else
    {
        /* Delete existing buffer. */
        gcmONERROR(gcoHARDWARE_FreeTemporarySurface(gcvTRUE));

        Hardware->tempBuffer.alignedWidth  = Width;
        Hardware->tempBuffer.alignedHeight = Height;

        /* Align the width and height. */
        gcmONERROR(gcoHARDWARE_AlignToTile(
            Type,
            Format->format,
            &Hardware->tempBuffer.alignedWidth,
            &Hardware->tempBuffer.alignedHeight,
            gcvNULL
            ));

        /* Init the interface structure. */
        iface.command = gcvHAL_ALLOCATE_LINEAR_VIDEO_MEMORY;
        iface.u.AllocateLinearVideoMemory.bytes     = Hardware->tempBuffer.alignedWidth
                                                    * Format->bitsPerPixel / 8
                                                    * Hardware->tempBuffer.alignedHeight;
        iface.u.AllocateLinearVideoMemory.alignment = 64;
        iface.u.AllocateLinearVideoMemory.pool      = gcvPOOL_DEFAULT;
        iface.u.AllocateLinearVideoMemory.type      = Type;

        /* Call kernel service. */
        gcmONERROR(gcoOS_DeviceControl(
            gcvNULL, IOCTL_GCHAL_INTERFACE,
            &iface, sizeof(gcsHAL_INTERFACE),
            &iface, sizeof(gcsHAL_INTERFACE)
            ));

        /* Validate the return value. */
        gcmONERROR(iface.status);

        /* Set the new parameters. */
        Hardware->tempBuffer.type                = Type;
        Hardware->tempBuffer.format              = Format->format;
        Hardware->tempBuffer.stride              = Width * Format->bitsPerPixel / 8;
        Hardware->tempBuffer.size                = iface.u.AllocateLinearVideoMemory.bytes;
        Hardware->tempBuffer.node.valid          = gcvFALSE;
        Hardware->tempBuffer.node.lockCount      = 0;
        Hardware->tempBuffer.node.lockedInKernel = gcvFALSE;
        Hardware->tempBuffer.node.logical        = gcvNULL;
        Hardware->tempBuffer.node.physical       = ~0U;

        Hardware->tempBuffer.node.pool
            = iface.u.AllocateLinearVideoMemory.pool;
        Hardware->tempBuffer.node.u.normal.node
            =  iface.u.AllocateLinearVideoMemory.node;
        Hardware->tempBuffer.node.u.normal.cacheable = gcvFALSE;


        Hardware->tempBuffer.rect.left   = 0;
        Hardware->tempBuffer.rect.top    = 0;
        Hardware->tempBuffer.rect.right  = Width;
        Hardware->tempBuffer.rect.bottom = Height;
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_FreeTemporarySurface
**
**  Free the temporary surface.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to a gcoHARDWARE object.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_FreeTemporarySurface(
    IN gctBOOL Synchronized
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Synchronized=%d", Synchronized);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Is there a surface allocated? */
    if (hardware->tempBuffer.node.pool != gcvPOOL_UNKNOWN)
    {
        /* Schedule deletion. */
        if (Synchronized)
        {
            gcmONERROR(gcoHARDWARE_ScheduleVideoMemory(
                &hardware->tempBuffer.node
                ));
        }

        /* Not synchronized --> delete immediately. */
        else
        {
            gcsHAL_INTERFACE iface;

            /* Free the video memory. */
            iface.command = gcvHAL_FREE_VIDEO_MEMORY;
            iface.u.FreeVideoMemory.node = hardware->tempBuffer.node.u.normal.node;

            /* Call kernel API. */
            gcmONERROR(gcoHAL_Call(gcvNULL, &iface));
        }

        /* Reset the temporary surface. */
        gcoOS_ZeroMemory(&hardware->tempBuffer, sizeof(hardware->tempBuffer));

        hardware->tempBuffer.node.pool = gcvPOOL_UNKNOWN;
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Get2DTempSurface
**
**  Allocates a temporary surface with specified parameters.
**
**  INPUT:
**
**      gctUINT Width, Height
**          The aligned size of the surface to be allocated.
**
**      gceSURF_FORMAT Format
**          The format of the surface to be allocated.
**
**  OUTPUT:
**
**      gcsSURF_INFO_PTR *SurfInfo
*/
gceSTATUS
gcoHARDWARE_Get2DTempSurface(
    IN gctUINT Width,
    IN gctUINT Height,
    IN gceSURF_FORMAT Format,
    OUT gcsSURF_INFO_PTR *SurfInfo
    )
{
    gceSTATUS status;
    gcsHAL_INTERFACE iface;
    gcsSURF_INFO_PTR surf = gcvNULL;
    gcsSURF_FORMAT_INFO_PTR formatInfo[2];
    gctUINT alignedWidth, alignedHeight, size, delta = 0;
    gctINT  i, idx = -1;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Width=%d Height=%d "
                    "Format=%d",
                    Width, Height,
                    Format);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    alignedWidth = Width;
    alignedHeight = Height;

    /* Align the width and height. */
    gcmONERROR(gcoHARDWARE_AlignToTile(
        gcvSURF_BITMAP, Format, &alignedWidth, &alignedHeight, gcvNULL
        ));

    gcmONERROR(gcoSURF_QueryFormat(Format, formatInfo));

    size = alignedWidth * formatInfo[0]->bitsPerPixel  / 8 * alignedHeight;

    /* Do we have a fit surface? */
    for (i = 0; i < gcdTEMP_SURFACE_NUMBER; i += 1)
    {
        if ((hardware->temp2DSurf[i] != gcvNULL)
            && (hardware->temp2DSurf[i]->node.size >= size))
        {
            if (idx == -1)
            {
                delta = hardware->temp2DSurf[i]->node.size - size;
                idx = i;
            }
            else if (hardware->temp2DSurf[i]->node.size - size < delta)
            {
                delta = hardware->temp2DSurf[i]->node.size - size;
                idx = i;
            }
        }
    }

    if (idx != -1)
    {
        gcmASSERT((idx >= 0) && (idx < gcdTEMP_SURFACE_NUMBER));

        *SurfInfo = hardware->temp2DSurf[idx];
        hardware->temp2DSurf[idx] = gcvNULL;

        (*SurfInfo)->format              = Format;
        (*SurfInfo)->stride              = alignedWidth * formatInfo[0]->bitsPerPixel / 8;
        (*SurfInfo)->alignedWidth        = alignedWidth;
        (*SurfInfo)->alignedHeight       = alignedHeight;
        (*SurfInfo)->is16Bit             = formatInfo[0]->bitsPerPixel == 16;
        (*SurfInfo)->rotation            = gcvSURF_0_DEGREE;
        (*SurfInfo)->orientation         = gcvORIENTATION_TOP_BOTTOM;
        (*SurfInfo)->tiling              = gcvLINEAR;

        (*SurfInfo)->rect.left   = 0;
        (*SurfInfo)->rect.top    = 0;
        (*SurfInfo)->rect.right  = Width;
        (*SurfInfo)->rect.bottom = Height;
    }
    else
    {
        gcmONERROR(gcoOS_Allocate(gcvNULL, sizeof(gcsSURF_INFO), (gctPOINTER *)&surf));
        gcoOS_ZeroMemory(surf, sizeof(gcsSURF_INFO));

        surf->node.u.normal.node  = 0;
        surf->node.valid          = gcvFALSE;

        /* Init the interface structure. */
        iface.command = gcvHAL_ALLOCATE_LINEAR_VIDEO_MEMORY;
        iface.u.AllocateLinearVideoMemory.bytes     = size;
        iface.u.AllocateLinearVideoMemory.alignment = 64;
        iface.u.AllocateLinearVideoMemory.pool      = gcvPOOL_DEFAULT;
        iface.u.AllocateLinearVideoMemory.type      = gcvSURF_BITMAP;

        /* Call kernel service. */
        gcmONERROR(gcoHAL_Call(gcvNULL, &iface));

        /* Set the new parameters. */
        surf->type                = gcvSURF_BITMAP;
        surf->format              = Format;
        surf->stride              = alignedWidth * formatInfo[0]->bitsPerPixel / 8;
        surf->alignedWidth        = alignedWidth;
        surf->alignedHeight       = alignedHeight;
        surf->size                = iface.u.AllocateLinearVideoMemory.bytes;
        surf->is16Bit             = formatInfo[0]->bitsPerPixel == 16;


        surf->rotation            = gcvSURF_0_DEGREE;
        surf->orientation         = gcvORIENTATION_TOP_BOTTOM;

        surf->rect.left   = 0;
        surf->rect.top    = 0;
        surf->rect.right  = Width;
        surf->rect.bottom = Height;

        surf->node.lockCount      = 0;
        surf->node.lockedInKernel = gcvFALSE;
        surf->node.logical        = gcvNULL;
        surf->node.physical       = ~0U;
        surf->tiling              = gcvLINEAR;

        surf->node.pool
            = iface.u.AllocateLinearVideoMemory.pool;

        surf->node.u.normal.node
            = iface.u.AllocateLinearVideoMemory.node;

        surf->node.u.normal.cacheable = gcvFALSE;

        surf->node.size = iface.u.AllocateLinearVideoMemory.bytes;

        gcmONERROR(gcoHARDWARE_Lock(&surf->node, gcvNULL, gcvNULL));

        *SurfInfo = surf;
    }

OnError:
    if (gcmIS_ERROR(status) && (surf != gcvNULL))
    {
        if (surf->node.valid)
        {
            gcmVERIFY_OK(gcoHARDWARE_Unlock(
                &surf->node,
                gcvSURF_BITMAP
                ));
        }

        if (surf->node.u.normal.node != 0)
        {
            /* Free the video memory immediately. */
            iface.command = gcvHAL_FREE_VIDEO_MEMORY;
            iface.u.FreeVideoMemory.node = surf->node.u.normal.node;

            /* Call kernel API. */
            if (gcmIS_ERROR((gcoHAL_Call(gcvNULL, &iface))))
            {
                gcmTRACE_ZONE(gcvLEVEL_ERROR,
                              gcvZONE_HARDWARE,
                              "gcoHAL_Call fail.");
            }
        }

        gcmVERIFY_OK(gcmOS_SAFE_FREE(gcvNULL, surf));
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Put2DTempSurface
**
**  Put back the temporary surface.
**
**  INPUT:
**
**      gcsSURF_INFO_PTR SurfInfo
**          The info of the surface to be free'd.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_Put2DTempSurface(
    IN gcsSURF_INFO_PTR SurfInfo
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcsHAL_INTERFACE iface;
    gcsSURF_INFO_PTR surf = SurfInfo;
    gctINT i;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("SurfInfo=0x%x", SurfInfo);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmASSERT(SurfInfo != gcvNULL);

    for (i = 0; i < gcdTEMP_SURFACE_NUMBER; i++)
    {
        /* Is there an empty slot? */
        if (hardware->temp2DSurf[i] == gcvNULL)
        {
            hardware->temp2DSurf[i] = surf;
            break;
        }

        /* Swap the smaller one. */
        else if (hardware->temp2DSurf[i]->node.size < surf->node.size)
        {
            gcsSURF_INFO_PTR temp = surf;

            surf = hardware->temp2DSurf[i];
            hardware->temp2DSurf[i] = temp;
        }
    }

    if (i == gcdTEMP_SURFACE_NUMBER)
    {
        if (surf->node.valid)
        {
            gcmONERROR(gcoHARDWARE_Unlock(
                &surf->node,
                gcvSURF_BITMAP
                ));
        }

        iface.command = gcvHAL_FREE_VIDEO_MEMORY;
        iface.u.FreeVideoMemory.node = surf->node.u.normal.node;

        /* Schedule deletion. */
        gcmONERROR(gcoHARDWARE_CallEvent(&iface));
        gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, surf));
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_ConvertPixel
**
**  Convert source pixel from source format to target pixel' target format.
**  The source format class should be either identical or convertible to
**  the target format class.
**
**  INPUT:
**
**      gctPOINTER SrcPixel, TrgPixel,
**          Pointers to source and target pixels.
**
**      gctUINT SrcBitOffset, TrgBitOffset
**          Bit offsets of the source and target pixels relative to their
**          respective pointers.
**
**      gcsSURF_FORMAT_INFO_PTR SrcFormat, TrgFormat
**          Pointers to source and target pixel format descriptors.
**
**      gcsBOUNDARY_PTR SrcBoundary, TrgBoundary
**          Pointers to optional boundary structures to verify the source
**          and target position. If the source is found to be beyond the
**          defined boundary, it will be assumed to be 0. If the target
**          is found to be beyond the defined boundary, the write will
**          be ignored. If boundary checking is not needed, gcvNULL can be
**          passed.
**
**  OUTPUT:
**
**      gctPOINTER TrgPixel + TrgBitOffset
**          Converted pixel.
*/
gceSTATUS gcoHARDWARE_ConvertPixel(
    IN gctPOINTER SrcPixel,
    OUT gctPOINTER TrgPixel,
    IN gctUINT SrcBitOffset,
    IN gctUINT TrgBitOffset,
    IN gcsSURF_FORMAT_INFO_PTR SrcFormat,
    IN gcsSURF_FORMAT_INFO_PTR TrgFormat,
    IN gcsBOUNDARY_PTR SrcBoundary,
    IN gcsBOUNDARY_PTR TrgBoundary
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("SrcPixel=0x%x TrgPixel=0x%x "
                    "SrcBitOffset=%d TrgBitOffset=%d SrcFormat=0x%x "
                    "TrgFormat=0x%x SrcBoundary=0x%x TrgBoundary=0x%x",
                    SrcPixel, TrgPixel,
                    SrcBitOffset, TrgBitOffset, SrcFormat,
                    TrgFormat, SrcBoundary, TrgBoundary);

    if (SrcFormat->fmtClass == gcvFORMAT_CLASS_RGBA)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_RGBA)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.alpha,
                &TrgFormat->u.rgba.alpha,
                SrcBoundary, TrgBoundary,
                ~0U
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.red,
                &TrgFormat->u.rgba.red,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.green,
                &TrgFormat->u.rgba.green,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.blue,
                &TrgFormat->u.rgba.blue,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else if (TrgFormat->fmtClass == gcvFORMAT_CLASS_LUMINANCE)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.red,
                &TrgFormat->u.lum.value,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.rgba.alpha,
                &TrgFormat->u.lum.alpha,
                SrcBoundary, TrgBoundary,
                ~0U
                ));
        }

        else if (TrgFormat->fmtClass == gcvFORMAT_CLASS_YUV)
        {
            gctUINT8 r[4] = {0};
            gctUINT8 g[4] = {0};
            gctUINT8 b[4] = {0};
            gctUINT8 y[4] = {0};
            gctUINT8 u[4] = {0};
            gctUINT8 v[4] = {0};

            /*
                Get RGB value.
            */

            gcmONERROR(_ConvertComponent(
                SrcPixel, r, SrcBitOffset, 0,
                &SrcFormat->u.rgba.red, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, g, SrcBitOffset, 0,
                &SrcFormat->u.rgba.green, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, b, SrcBitOffset, 0,
                &SrcFormat->u.rgba.blue, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            /*
                Convert to YUV.
            */

            gcoHARDWARE_RGB2YUV(
                 r[0], g[0], b[0],
                 y, u, v
                );

            /*
                Average Us and Vs for odd pixels.
            */
            if ((TrgFormat->interleaved & gcvCOMPONENT_ODD) != 0)
            {
                gctUINT8 curU[4] = {0}, curV[4] = {0};

                gcmONERROR(_ConvertComponent(
                    TrgPixel, curU, TrgBitOffset, 0,
                    &TrgFormat->u.yuv.u, &gcvPIXEL_COMP_XXX8,
                    TrgBoundary, gcvNULL, 0
                    ));

                gcmONERROR(_ConvertComponent(
                    TrgPixel, curV, TrgBitOffset, 0,
                    &TrgFormat->u.yuv.v, &gcvPIXEL_COMP_XXX8,
                    TrgBoundary, gcvNULL, 0
                    ));


                u[0] = (gctUINT8) (((gctUINT16) u[0] + (gctUINT16) curU[0]) >> 1);
                v[0] = (gctUINT8) (((gctUINT16) v[0] + (gctUINT16) curV[0]) >> 1);
            }

            /*
                Convert to the final format.
            */

            gcmONERROR(_ConvertComponent(
                y, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.yuv.y,
                gcvNULL, TrgBoundary, 0
                ));

            gcmONERROR(_ConvertComponent(
                u, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.yuv.u,
                gcvNULL, TrgBoundary, 0
                ));

            gcmONERROR(_ConvertComponent(
                v, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.yuv.v,
                gcvNULL, TrgBoundary, 0
                ));
        }

        else
        {
            /* Not supported combination. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else if (SrcFormat->fmtClass == gcvFORMAT_CLASS_YUV)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_YUV)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.yuv.y,
                &TrgFormat->u.yuv.y,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.yuv.u,
                &TrgFormat->u.yuv.u,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.yuv.v,
                &TrgFormat->u.yuv.v,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else if (TrgFormat->fmtClass == gcvFORMAT_CLASS_RGBA)
        {
            gctUINT8 y[4]={0}, u[4]={0}, v[4]={0};
            gctUINT8 r[4], g[4], b[4];

            /*
                Get YUV value.
            */

            gcmONERROR(_ConvertComponent(
                SrcPixel, y, SrcBitOffset, 0,
                &SrcFormat->u.yuv.y, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, u, SrcBitOffset, 0,
                &SrcFormat->u.yuv.u, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, v, SrcBitOffset, 0,
                &SrcFormat->u.yuv.v, &gcvPIXEL_COMP_XXX8,
                SrcBoundary, gcvNULL, 0
                ));

            /*
                Convert to RGB.
            */

            gcoHARDWARE_YUV2RGB(
                 y[0], u[0], v[0],
                 r, g, b
                );

            /*
                Convert to the final format.
            */

            gcmONERROR(_ConvertComponent(
                gcvNULL, TrgPixel, 0, TrgBitOffset,
                gcvNULL, &TrgFormat->u.rgba.alpha,
                gcvNULL, TrgBoundary, ~0U
                ));

            gcmONERROR(_ConvertComponent(
                r, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.rgba.red,
                gcvNULL, TrgBoundary, 0
                ));

            gcmONERROR(_ConvertComponent(
                g, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.rgba.green,
                gcvNULL, TrgBoundary, 0
                ));

            gcmONERROR(_ConvertComponent(
                b, TrgPixel, 0, TrgBitOffset,
                &gcvPIXEL_COMP_XXX8, &TrgFormat->u.rgba.blue,
                gcvNULL, TrgBoundary, 0
                ));
        }

        else
        {
            /* Not supported combination. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else if (SrcFormat->fmtClass == gcvFORMAT_CLASS_INDEX)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_INDEX)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.index.value,
                &TrgFormat->u.index.value,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else
        {
            /* Not supported combination. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else if (SrcFormat->fmtClass == gcvFORMAT_CLASS_LUMINANCE)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_LUMINANCE)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.lum.alpha,
                &TrgFormat->u.lum.alpha,
                SrcBoundary, TrgBoundary,
                ~0U
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.lum.value,
                &TrgFormat->u.lum.value,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else
        {
            /* Not supported combination. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else if (SrcFormat->fmtClass == gcvFORMAT_CLASS_BUMP)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_BUMP)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.alpha,
                &TrgFormat->u.bump.alpha,
                SrcBoundary, TrgBoundary,
                ~0U
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.l,
                &TrgFormat->u.bump.l,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.v,
                &TrgFormat->u.bump.v,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.u,
                &TrgFormat->u.bump.u,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.q,
                &TrgFormat->u.bump.q,
                SrcBoundary, TrgBoundary,
                0
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.bump.w,
                &TrgFormat->u.bump.w,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else
        {
            /* Not supported combination. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else if (SrcFormat->fmtClass == gcvFORMAT_CLASS_DEPTH)
    {
        if (TrgFormat->fmtClass == gcvFORMAT_CLASS_DEPTH)
        {
            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.depth.depth,
                &TrgFormat->u.depth.depth,
                SrcBoundary, TrgBoundary,
                ~0U
                ));

            gcmONERROR(_ConvertComponent(
                SrcPixel, TrgPixel,
                SrcBitOffset, TrgBitOffset,
                &SrcFormat->u.depth.stencil,
                &TrgFormat->u.depth.stencil,
                SrcBoundary, TrgBoundary,
                0
                ));
        }

        else
        {
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }

    else
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    /* Return status. */
    gcmFOOTER();
    return gcvSTATUS_OK;

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_FlushPipe
**
**  Flush the current graphics pipe.
**
**  INPUT:
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_FlushPipe(
    )
{
    gceSTATUS status;
    gctUINT32 flush;
    gctBOOL flushFixed;
    gcoHARDWARE hardware;

    /* Define state buffer variables. */
    gcmDEFINESECUREUSER()
    gctSIZE_T reserveSize;
    gcoCMDBUF reserve;
    gctUINT32_PTR memory;

    gcmHEADER();

    gcmGETHARDWARE(hardware);

    if (hardware->currentPipe == 0x1)
    {
        /* Flush 2D cache. */
        flush = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)));
    }
    else
    {
        /* Flush Z and Color caches. */
        flush = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) |
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:1) - (0 ? 1:1) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:1) - (0 ? 1:1) + 1))))))) << (0 ? 1:1))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 1:1) - (0 ? 1:1) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:1) - (0 ? 1:1) + 1))))))) << (0 ? 1:1)));
    }

    /* RTL bug in older chips - flush leaks the next state.
       There is no actial bit for the fix. */
    flushFixed = ((((gctUINT32) (hardware->chipMinorFeatures)) >> (0 ? 31:31) & ((gctUINT32) ((((1 ? 31:31) - (0 ? 31:31) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:31) - (0 ? 31:31) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 31:31) - (0 ? 31:31) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:31) - (0 ? 31:31) + 1)))))));

    /* FLUSH_HACK */
    flushFixed = gcvFALSE;

    /* Determine the size of the buffer to reserve. */
    if (flushFixed)
    {
        reserveSize = gcmALIGN((1 + 1) * gcmSIZEOF(gctUINT32), 8);
    }
    else
    {
        reserveSize = gcmALIGN((1 + 1) * gcmSIZEOF(gctUINT32), 8) * 2;
    }

    /* Reserve space in the command buffer. */
    gcmONERROR(gcoBUFFER_Reserve(
        hardware->buffer, reserveSize, gcvTRUE, &reserve
        ));
    memory = gcmUINT64_TO_PTR(reserve->lastReserve);
    /*stateDelta = Hardware->delta;*/
    gcmBEGINSECUREUSER();

        {{    gcmASSERT(((memory - (gctUINT32_PTR) reserve->lastReserve) & 1) == 0);    gcmVERIFYLOADSTATEDONE(reserve);    gcmSTORELOADSTATE(reserve, memory, 0x0E03, 1);    *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | (((gctUINT32) ((gctUINT32) (gcvFALSE) & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x0E03) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));gcmSKIPSECUREUSER();};gcmSETCTRLSTATE(stateDelta, reserve, memory, 0x0E03, flush );gcmENDSTATEBATCH(reserve, memory);};

        if (!flushFixed)
        {
            {{    gcmASSERT(((memory - (gctUINT32_PTR) reserve->lastReserve) & 1) == 0);    gcmVERIFYLOADSTATEDONE(reserve);    gcmSTORELOADSTATE(reserve, memory, 0x0E03, 1);    *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | (((gctUINT32) ((gctUINT32) (gcvFALSE) & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x0E03) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));gcmSKIPSECUREUSER();};gcmSETCTRLSTATE(stateDelta, reserve, memory, 0x0E03, flush );gcmENDSTATEBATCH(reserve, memory);};
        }

    /* Validate the state buffer. */
    gcmENDSTATEBUFFER(reserve, memory, reserveSize);


    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_UseSoftware2D
**
**  Sets the software 2D renderer force flag.
**
**  INPUT:
**
**      gctBOOL Enable
**          gcvTRUE to enable using software for 2D or
**          gcvFALSE to use underlying hardware.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_UseSoftware2D(
    IN gctBOOL Enable
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Enable=%d", Enable);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Set the force flag. */
    hardware->sw2DEngine = Enable;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_RGB2YUV
**
**  Convert RGB8 color value to YUV color space.
**
**  INPUT:
**
**      gctUINT8 R, G, B
**          RGB color value.
**
**  OUTPUT:
**
**      gctUINT8_PTR Y, U, V
**          YUV color value.
*/
void gcoHARDWARE_RGB2YUV(
    gctUINT8 R,
    gctUINT8 G,
    gctUINT8 B,
    gctUINT8_PTR Y,
    gctUINT8_PTR U,
    gctUINT8_PTR V
    )
{
    gcmHEADER_ARG("R=%d G=%d B=%d",
                    R, G, B);

    *Y = (gctUINT8) (((66 * R + 129 * G +  25 * B + 128) >> 8) +  16);
    *U = (gctUINT8) (((-38 * R -  74 * G + 112 * B + 128) >> 8) + 128);
    *V = (gctUINT8) (((112 * R -  94 * G -  18 * B + 128) >> 8) + 128);

    gcmFOOTER_ARG("*Y=%d *U=%d *V=%d",
                    *Y, *U, *V);
}

/*******************************************************************************
**
**  gcoHARDWARE_YUV2RGB
**
**  Convert YUV color value to RGB8 color space.
**
**  INPUT:
**
**      gctUINT8 Y, U, V
**          YUV color value.
**
**  OUTPUT:
**
**      gctUINT8_PTR R, G, B
**          RGB color value.
*/
void gcoHARDWARE_YUV2RGB(
    gctUINT8 Y,
    gctUINT8 U,
    gctUINT8 V,
    gctUINT8_PTR R,
    gctUINT8_PTR G,
    gctUINT8_PTR B
    )
{
    /* Clamp the input values to the legal ranges. */
    gctINT y = (Y < 16) ? 16 : ((Y > 235) ? 235 : Y);
    gctINT u = (U < 16) ? 16 : ((U > 240) ? 240 : U);
    gctINT v = (V < 16) ? 16 : ((V > 240) ? 240 : V);

    /* Shift ranges. */
    gctINT _y = y - 16;
    gctINT _u = u - 128;
    gctINT _v = v - 128;

    /* Convert to RGB. */
    gctINT r = (298 * _y            + 409 * _v + 128) >> 8;
    gctINT g = (298 * _y - 100 * _u - 208 * _v + 128) >> 8;
    gctINT b = (298 * _y + 516 * _u            + 128) >> 8;

    gcmHEADER_ARG("Y=%d U=%d V=%d",
                    Y, U, V);

    /* Clamp the result. */
    *R = (r < 0)? 0 : (r > 255)? 255 : (gctUINT8) r;
    *G = (g < 0)? 0 : (g > 255)? 255 : (gctUINT8) g;
    *B = (b < 0)? 0 : (b > 255)? 255 : (gctUINT8) b;

    gcmFOOTER_ARG("*R=%d *G=%d *B=%d",
                    *R, *G, *B);
}


/*******************************************************************************
**
**  gcoHARDWARE_SetAutoFlushCycles
**
**  Set the GPU clock cycles after which the idle 2D engine will keep auto-flushing.
**
**  INPUT:
**
**      UINT32 Cycles
**          Source color premultiply with Source Alpha.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS gcoHARDWARE_SetAutoFlushCycles(
    IN gctUINT32 Cycles
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Cycles=%d", Cycles);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    if (hardware->hw2DEngine && !hardware->sw2DEngine)
    {
        /* LoadState timeout value. */
        gcmONERROR(gcoHARDWARE_Load2DState32(
            hardware,
            0x00670,
            Cycles
            ));
    }
    else
    {
        /* Auto-flush is not supported by the software renderer. */
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}


gceSTATUS
gcoHARDWARE_Load2DState32(
    IN gcoHARDWARE Hardware,
    IN gctUINT32 Address,
    IN gctUINT32 Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Address=0x%08x Data=0x%08x",
                  Hardware, Address, Data);

    /* Call buffered load state to do it. */
    gcmONERROR(gcoHARDWARE_Load2DState(Hardware, Address, 1, &Data));

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS
gcoHARDWARE_Load2DState(
    IN gcoHARDWARE Hardware,
    IN gctUINT32 Address,
    IN gctSIZE_T Count,
    IN gctPOINTER Data
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Address=0x%08x Count=%lu Data=0x%08x",
                  Hardware, Address, Count, Data);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

     /* Verify the arguments. */
    if (Hardware->hw2DCmdIndex & 1)
    {
        gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
    }

    if (Hardware->hw2DCmdBuffer != gcvNULL)
    {
        gctUINT32_PTR memory;

        if (Hardware->hw2DCmdSize - Hardware->hw2DCmdIndex < gcmALIGN(1 + Count, 2))
        {
            gcmONERROR(gcvSTATUS_OUT_OF_MEMORY);
        }

        memory = Hardware->hw2DCmdBuffer + Hardware->hw2DCmdIndex;

        /* LOAD_STATE(Count, Address >> 2) */
        memory[0] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                  | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (Count) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16)))
                  | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Address >> 2) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));

        /* Copy the state buffer. */
        gcoOS_MemCopy(&memory[1], Data, Count * 4);
    }

    Hardware->hw2DCmdIndex += 1 + Count;

    /* Aligned */
    if (Hardware->hw2DCmdIndex & 1)
    {
        Hardware->hw2DCmdIndex += 1;
    }

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS
gcoHARDWARE_2DAppendNop(
    IN gcoHARDWARE Hardware
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x", Hardware);

    /* Verify the arguments. */
    if (Hardware->hw2DCmdIndex & 1)
    {
        gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
    }

    if ((Hardware->hw2DCmdBuffer != gcvNULL)
        && (Hardware->hw2DCmdSize > Hardware->hw2DCmdIndex))
    {
        gctUINT32_PTR memory = Hardware->hw2DCmdBuffer + Hardware->hw2DCmdIndex;
        gctUINT32 i = 0;

        while (i < Hardware->hw2DCmdSize - Hardware->hw2DCmdIndex)
        {
            /* Append NOP. */
            memory[i++] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x03 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)));
            memory[i++] = 0xdeaddead;
        }

        Hardware->hw2DCmdIndex = Hardware->hw2DCmdSize;
    }

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}



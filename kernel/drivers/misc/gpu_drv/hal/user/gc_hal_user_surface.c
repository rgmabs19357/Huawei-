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


/**
**  @file
**  gcoSURF object for user HAL layers.
**
*/

#include "gc_hal_user_precomp.h"

#define gcmALVM         iface.u.AllocateLinearVideoMemory

#define _GC_OBJ_ZONE    gcvZONE_SURFACE

/******************************************************************************\
**************************** gcoSURF API Support Code **************************
\******************************************************************************/

static gceSTATUS
_Lock(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;
    {
        /* Lock the video memory. */
        gcmONERROR(
            gcoHARDWARE_Lock(
                         &Surface->info.node,
                         gcvNULL,
                         gcvNULL));
    }

    gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                  "Locked surface 0x%x: physical=0x%08X logical=0x%x lockCount=%d",
                  &Surface->info.node,
                  Surface->info.node.physical,
                  Surface->info.node.logical,
                  Surface->info.node.lockCount);
    /* Success. */
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    return status;
}

static gceSTATUS
_Unlock(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;
    {
        /* Unlock the surface. */
        gcmONERROR(
            gcoHARDWARE_Unlock(
                               &Surface->info.node,
                               Surface->info.type));
    }

    gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                  "Unlocked surface 0x%x: lockCount=%d",
                  &Surface->info.node,
                  Surface->info.node.lockCount);


    /* Success. */
    return gcvSTATUS_OK;

OnError:
    /* Return the errror. */
    return status;
}


static gceSTATUS
_FreeSurface(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x", Surface);

    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

#if gcdSYNC
    {
        gcsSYNC_CONTEXT_PTR ptr = Surface->info.fenceCtx;

        while(ptr)
        {
           Surface->info.fenceCtx = ptr->next;
           gcmONERROR(gcoOS_Free(gcvNULL,ptr));
           ptr = Surface->info.fenceCtx;
        }
    }
#endif

    /* We only manage valid and non-user pools. */
    if ((Surface->info.node.pool != gcvPOOL_UNKNOWN)
    &&  (Surface->info.node.pool != gcvPOOL_USER)
    )
    {
        /* Unlock the video memory. */
        gcmONERROR(_Unlock(Surface));

        if (!(Surface->info.hints & gcvSURF_NO_VIDMEM))
        {
            /* Free the video memory. */
            gcmONERROR(
                gcoHARDWARE_ScheduleVideoMemory(&Surface->info.node));

            gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                          "Freed surface 0x%x",
                          &Surface->info.node);
        }
        /* Mark the memory as freed. */
        Surface->info.node.pool = gcvPOOL_UNKNOWN;
    }


    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

#if gcdENABLE_BANK_ALIGNMENT

#if !gcdBANK_BIT_START
#error gcdBANK_BIT_START not defined.
#endif

#if !gcdBANK_BIT_END
#error gcdBANK_BIT_END not defined.
#endif

/*******************************************************************************
**  gcoSURF_GetBankOffsetBytes
**
**  Return the bytes needed to offset sub-buffers to different banks.
**
**  ARGUMENTS:
**
**      gceSURF_TYPE Type
**          Type of buffer.
**
**      gctUINT32 TopBufferSize
**          Size of the top buffer, needed to compute offset of the second buffer.
**
**  OUTPUT:
**
**      gctUINT32_PTR Bytes
**          Pointer to a variable that will receive the byte offset needed.
**
*/
gceSTATUS
gcoSURF_GetBankOffsetBytes(
    IN gcoSURF Surfce,
    IN gceSURF_TYPE Type,
    IN gctUINT32 TopBufferSize,
    OUT gctUINT32_PTR Bytes
    )
{
    gctUINT32 bank;
    /* To retrieve the bank. */
    static const gctUINT32 bankMask = (0xFFFFFFFF << gcdBANK_BIT_START)
                                    ^ (0xFFFFFFFF << (gcdBANK_BIT_END + 1));

    gcmHEADER_ARG("Type=%d TopBufferSize=%x Bytes=0x%x", Type, TopBufferSize, Bytes);

    /* Verify the arguments. */
    gcmDEBUG_VERIFY_ARGUMENT(Bytes != gcvNULL);

    switch(Type)
    {
    case gcvSURF_RENDER_TARGET:
        bank = (TopBufferSize & bankMask) >> (gcdBANK_BIT_START);

        /* Put second buffer (c1 or z1) 5 banks away. */
        if (bank <= 5)
        {
            *Bytes += (5 - bank) << (gcdBANK_BIT_START);
        }
        else
        {
            *Bytes += (8 + 5 - bank) << (gcdBANK_BIT_START);
        }

#if gcdBANK_CHANNEL_BIT
        /* Add a channel offset at the channel bit. */
        *Bytes += (1 << gcdBANK_CHANNEL_BIT);
#endif
        break;

    case gcvSURF_DEPTH:
        bank = (TopBufferSize & bankMask) >> (gcdBANK_BIT_START);

        /* Put second buffer (c1 or z1) 5 banks away. */
        if (bank <= 5)
        {
            *Bytes += (5 - bank) << (gcdBANK_BIT_START);
        }
        else
        {
            *Bytes += (8 + 5 - bank) << (gcdBANK_BIT_START);
        }

#if gcdBANK_CHANNEL_BIT
        /* Subtract the channel bit, as it's added by kernel side. */
        if (*Bytes >= (1 << gcdBANK_CHANNEL_BIT))
        {
            *Bytes -= (1 << gcdBANK_CHANNEL_BIT);
        }
#endif
        break;

    default:
        /* No alignment needed. */
        *Bytes = 0;
    }

    gcmFOOTER_ARG("*Bytes=0x%x", *Bytes);
    return gcvSTATUS_OK;
}
#endif

static gceSTATUS
_AllocateSurface(
    IN gcoSURF Surface,
    IN gctUINT Width,
    IN gctUINT Height,
    IN gctUINT Depth,
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN gcePOOL Pool
    )
{
    gceSTATUS status;
    gcsHAL_INTERFACE iface;
    /* Extra pages needed to offset sub-buffers to different banks. */
    gctUINT32 bankOffsetBytes = 0;

#if gcdANDROID_UNALIGNED_LINEAR_COMPOSITION_ADJUST
    /* Extra room for tile to bitmap flip resovle start address adjustment */
    gctUINT32 flipOffsetBytes = 0;
    gctUINT   oldHeight;

    oldHeight = Height;
#endif

    {
        /* Compute bits per pixel. */
        gcmONERROR(
            gcoHARDWARE_ConvertFormat(
                                  Format,
                                  (gctUINT32_PTR)&Surface->info.bitsPerPixel,
                                  gcvNULL));
    }

    /* Set dimensions of surface. */
    Surface->info.rect.left   = 0;
    Surface->info.rect.top    = 0;
    Surface->info.rect.right  = Width;
    Surface->info.rect.bottom = Height;

    /* Set the number of planes. */
    Surface->depth = Depth;

    /* Initialize rotation. */
    Surface->info.rotation    = gcvSURF_0_DEGREE;

    /* Obtain canonical type of surface. */
    Surface->info.type   = (gceSURF_TYPE) ((gctUINT32) Type & 0xFF);
    /* Get 'hints' of this surface. */
    Surface->info.hints  = (gceSURF_TYPE) ((gctUINT32) Type & ~0xFF);
    /* Set format of surface. */
    Surface->info.format = Format;
    Surface->info.tiling = gcvLINEAR;

    /* Set aligned surface size. */
    Surface->info.alignedWidth  = Width;
    Surface->info.alignedHeight = Height;
    Surface->info.is16Bit       = (Surface->info.bitsPerPixel == 16);


    /* Reset the node. */
    Surface->info.node.valid          = gcvFALSE;
    Surface->info.node.lockCount      = 0;
    Surface->info.node.lockedInKernel = 0;
    Surface->info.node.count          = 0;
    Surface->info.node.size           = 0;
    Surface->info.node.firstLock      = gcvTRUE;
    Surface->info.node.pool           = gcvPOOL_UNKNOWN;

    /* User pool? */
    if (Pool == gcvPOOL_USER)
    {
        /* Init the node as the user allocated. */
        Surface->info.node.pool                    = gcvPOOL_USER;
        Surface->info.node.u.wrapped.logicalMapped = gcvFALSE;
        Surface->info.node.u.wrapped.mappingInfo   = gcvNULL;
        Surface->info.node.size                    = Surface->info.alignedWidth
                                                   * (Surface->info.bitsPerPixel / 8)
                                                   * Surface->info.alignedHeight
                                                   * Surface->depth;
    }

    /* No --> allocate video memory. */
    else
    {
        {
            /* Align width and height to tiles. */
            gctUINT oldAlignedWidth, oldAlignedHeight;
            /* Save the value of Width and height. */
            oldAlignedWidth  = Surface->info.alignedWidth;
            oldAlignedHeight = Surface->info.alignedHeight;

            gcmONERROR(
                    gcoHARDWARE_AlignToTileCompatible(Surface->info.type,
                                                      Format,
                                                      &Surface->info.alignedWidth,
                                                      &Surface->info.alignedHeight,
                                                      &Surface->info.tiling,
                                                      gcvNULL));

            /*. For cube map with mip map, we should aligned the width and height without
                    considering pixel pips.*/
            if(6 == Depth)
            {
                /* Reset height and width. */
                Surface->info.alignedWidth  = oldAlignedWidth;
                Surface->info.alignedHeight = oldAlignedHeight;

                gcmONERROR(
                    gcoHARDWARE_AlignToTile(Surface->info.type,
                                            Format,
                                            &Surface->info.alignedWidth,
                                            &Surface->info.alignedHeight,
                                            gcvNULL));
            }
        }

        if (!(Type & gcvSURF_NO_VIDMEM))
        {
#if gcdENABLE_BANK_ALIGNMENT
#endif

            iface.command     = gcvHAL_ALLOCATE_LINEAR_VIDEO_MEMORY;
            gcmALVM.bytes     = Surface->info.alignedWidth * Surface->info.bitsPerPixel / 8
                              * Surface->info.alignedHeight
                              * Depth;
            gcmALVM.bytes    += bankOffsetBytes;

#if gcdANDROID_UNALIGNED_LINEAR_COMPOSITION_ADJUST
            gcmALVM.bytes    += flipOffsetBytes;
#endif

            if ((Type == gcvSURF_RENDER_TARGET)
            &&  gcoHARDWARE_IsFeatureAvailable(gcvFEATURE_TILE_FILLER)
            )
            {
                /* 256 tile alignment for fast clear fill feature. */
                gcmALVM.bytes = gcmALIGN(gcmALVM.bytes, 256 * 64);
            }

            gcmALVM.alignment = 64;
            gcmALVM.pool      = Pool;
            gcmALVM.type      = Surface->info.type;

            /* Call kernel API. */
            gcmONERROR(gcoHAL_Call(gcvNULL, &iface));

            /* Get allocated node in video memory. */
            Surface->info.node.u.normal.node = gcmALVM.node;
            Surface->info.node.pool          = gcmALVM.pool;
            Surface->info.node.size          = gcmALVM.bytes;
        }
    }

    /* Determine the surface placement parameters. */
    switch (Format)
    {
    case gcvSURF_YV12:
#if defined(ANDROID)
        /* Per google's requirement, we need u/v plane align to 16, and there is no gap between YV plane */
        Surface->info.vOffset
            = Surface->info.alignedWidth
            * Height;

        Surface->info.stride
            = Surface->info.alignedWidth;

        Surface->info.uStride =
        Surface->info.vStride
            = (Surface->info.alignedWidth / 2 + 0xf) & ~0xf;

        Surface->info.uOffset
            = Surface->info.vOffset
            + Surface->info.vStride * Height / 2;

        Surface->info.size
            = Surface->info.vOffset
            + Surface->info.vStride * Height;
#else
        /*  WxH Y plane followed by (W/2)x(H/2) V and U planes. */
        Surface->info.vOffset
            = Surface->info.alignedWidth
            * Surface->info.alignedHeight;

        Surface->info.uOffset
            = Surface->info.vOffset
            + Surface->info.vOffset / 4;

        Surface->info.stride
            = Surface->info.alignedWidth;

        Surface->info.uStride =
        Surface->info.vStride
            = Surface->info.alignedWidth / 2;

        Surface->info.size
            = Surface->info.vOffset
            + Surface->info.vOffset / 2;
#endif
        break;

    case gcvSURF_I420:
#if defined(ANDROID)
        /* Per google's requirement, we need u/v plane align to 16, and there is no gap between YV plane */
        Surface->info.uOffset
            = Surface->info.alignedWidth
            * Height;

        Surface->info.stride
            = Surface->info.alignedWidth;

        Surface->info.uStride =
        Surface->info.vStride
            = (Surface->info.alignedWidth / 2 + 0xf) & ~0xf;

        Surface->info.vOffset
            = Surface->info.uOffset
            + Surface->info.uStride * Height / 2;

        Surface->info.size
            = Surface->info.uOffset
            + Surface->info.uStride * Height;
#else
        /*  WxH Y plane followed by (W/2)x(H/2) U and V planes. */
        Surface->info.uOffset
            = Surface->info.alignedWidth
            * Surface->info.alignedHeight;

        Surface->info.vOffset
            = Surface->info.uOffset
            + Surface->info.uOffset / 4;

        Surface->info.stride
            = Surface->info.alignedWidth;

        Surface->info.uStride
            = Surface->info.vStride
            = Surface->info.alignedWidth / 2;

        Surface->info.size
            = Surface->info.uOffset
            + Surface->info.uOffset / 2;
#endif
        break;

    case gcvSURF_NV12:
    case gcvSURF_NV21:
        /*  WxH Y plane followed by (W)x(H/2) interleaved U/V plane. */
        Surface->info.uOffset
            = Surface->info.vOffset
            = Surface->info.alignedWidth
            * Surface->info.alignedHeight;

        Surface->info.stride
            = Surface->info.uStride
            = Surface->info.vStride
            = Surface->info.alignedWidth;

        Surface->info.size
            = Surface->info.uOffset
            + Surface->info.uOffset / 2;
        break;

    case gcvSURF_NV16:
    case gcvSURF_NV61:
        Surface->info.uOffset
            = Surface->info.vOffset
            = Surface->info.alignedWidth
            * Surface->info.alignedHeight;

        Surface->info.stride
            = Surface->info.uStride
            = Surface->info.vStride
            = Surface->info.alignedWidth;

        Surface->info.size
            = Surface->info.uOffset
            + Surface->info.uOffset;
        break;

    default:
        Surface->info.uOffset = Surface->info.vOffset = 0;
        Surface->info.uStride = Surface->info.vStride = 0;

        Surface->info.stride  = Surface->info.alignedWidth
                              * Surface->info.bitsPerPixel / 8;

        Surface->info.size    = Surface->info.stride
                              * Surface->info.alignedHeight;
    }

    /* Add any offset bytes added between sub-buffers. */
    Surface->info.size += bankOffsetBytes;

#if gcdANDROID_UNALIGNED_LINEAR_COMPOSITION_ADJUST
    Surface->info.size += flipOffsetBytes;
#endif

    gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                  "Allocated surface 0x%x: pool=%d size=%dx%d bytes=%u",
                  &Surface->info.node,
                  Surface->info.node.pool,
                  Surface->info.alignedWidth,
                  Surface->info.alignedHeight,
                  Surface->info.size);


    if (Pool != gcvPOOL_USER)
    {
        if (!(Type & gcvSURF_NO_VIDMEM))
        {
            /* Lock the surface. */
            gcmONERROR(_Lock(Surface));
        }
    }

    /* Success. */
    return gcvSTATUS_OK;

OnError:

    /* Free the memory allocated to the surface. */
    _FreeSurface(Surface);
    /* Return the status. */
    return status;
}

static gceSTATUS
_UnmapUserBuffer(
    IN gcoSURF Surface,
    IN gctBOOL ForceUnmap
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Surface=0x%x ForceUnmap=%d", Surface, ForceUnmap);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    do
    {
        /* Cannot be negative. */
        gcmASSERT(Surface->info.node.lockCount >= 0);

        /* Nothing is mapped? */
        if (Surface->info.node.lockCount == 0)
        {
            /* Nothing to do. */
            status = gcvSTATUS_OK;
            break;
        }

        /* Make sure the reference couner is proper. */
        if (Surface->info.node.lockCount > 1)
        {
            /* Forced unmap? */
            if (ForceUnmap)
            {
                /* Invalid reference count. */
                gcmASSERT(gcvFALSE);
            }
            else
            {
                /* Decrement. */
                Surface->info.node.lockCount -= 1;

                /* Done for now. */
                status = gcvSTATUS_OK;
                break;
            }
        }

        /* Unmap the logical memory. */
        if (Surface->info.node.u.wrapped.logicalMapped)
        {
            gcmERR_BREAK(gcoHAL_UnmapMemory(
                gcvNULL,
                gcmINT2PTR(Surface->info.node.physical),
                Surface->info.size,
                Surface->info.node.logical
                ));

            Surface->info.node.physical = ~0U;
            Surface->info.node.u.wrapped.logicalMapped = gcvFALSE;
        }

        /* Unmap the physical memory. */
        if (Surface->info.node.u.wrapped.mappingInfo != gcvNULL)
        {
            gceHARDWARE_TYPE currentType;

            /* Save the current hardware type */
            gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL, &currentType));

            if (Surface->info.node.u.wrapped.mappingHardwareType != currentType)
            {
                /* Change to the mapping hardware type */
                gcmVERIFY_OK(gcoHAL_SetHardwareType(gcvNULL,
                                                    Surface->info.node.u.wrapped.mappingHardwareType));
            }

            gcmERR_BREAK(gcoHAL_ScheduleUnmapUserMemory(
                gcvNULL,
                Surface->info.node.u.wrapped.mappingInfo,
                Surface->info.size,
                Surface->info.node.physical,
                Surface->info.node.logical
                ));

            Surface->info.node.logical = gcvNULL;
            Surface->info.node.u.wrapped.mappingInfo = gcvNULL;

            if (Surface->info.node.u.wrapped.mappingHardwareType != currentType)
            {
                /* Restore the current hardware type */
                gcmVERIFY_OK(gcoHAL_SetHardwareType(gcvNULL, currentType));
            }
        }

#if gcdSECURE_USER
        gcmERR_BREAK(gcoHAL_ScheduleUnmapUserMemory(
            gcvNULL,
            gcvNULL,
            Surface->info.size,
            0,
            Surface->info.node.logical));
#endif

        /* Reset the surface. */
        Surface->info.node.lockCount = 0;
        Surface->info.node.valid = gcvFALSE;
    }
    while (gcvFALSE);

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/******************************************************************************\
******************************** gcoSURF API Code *******************************
\******************************************************************************/

/*******************************************************************************
**
**  gcoSURF_Construct
**
**  Create a new gcoSURF object.
**
**  INPUT:
**
**      gcoHAL Hal
**          Pointer to an gcoHAL object.
**
**      gctUINT Width
**          Width of surface to create in pixels.
**
**      gctUINT Height
**          Height of surface to create in lines.
**
**      gctUINT Depth
**          Depth of surface to create in planes.
**
**      gceSURF_TYPE Type
**          Type of surface to create.
**
**      gceSURF_FORMAT Format
**          Format of surface to create.
**
**      gcePOOL Pool
**          Pool to allocate surface from.
**
**  OUTPUT:
**
**      gcoSURF * Surface
**          Pointer to the variable that will hold the gcoSURF object pointer.
*/
gceSTATUS
gcoSURF_Construct(
    IN gcoHAL Hal,
    IN gctUINT Width,
    IN gctUINT Height,
    IN gctUINT Depth,
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN gcePOOL Pool,
    OUT gcoSURF * Surface
    )
{
    gcoSURF surface = gcvNULL;
    gceSTATUS status;
    gctPOINTER pointer = gcvNULL;


    gcmHEADER_ARG("Width=%u Height=%u Depth=%u Type=%d Format=%d Pool=%d",
                  Width, Height, Depth, Type, Format, Pool);

    /* Verify the arguments. */
    gcmVERIFY_ARGUMENT(Surface != gcvNULL);

    /* Allocate the gcoSURF object. */
    gcmONERROR(
        gcoOS_Allocate(gcvNULL,
                       gcmSIZEOF(struct _gcoSURF),
                       &pointer));

    gcoOS_ZeroMemory(pointer, gcmSIZEOF(struct _gcoSURF));

    surface = pointer;

    /* Initialize the gcoSURF object.*/
    surface->object.type    = gcvOBJ_SURF;

    surface->info.dither    = gcvFALSE;

    surface->info.offset    = 0;


    if (Type & gcvSURF_CACHEABLE)
    {
        gcmASSERT(Pool != gcvPOOL_USER);
        surface->info.node.u.normal.cacheable = gcvTRUE;
        Type &= ~gcvSURF_CACHEABLE;
    }
    else if (Pool != gcvPOOL_USER)
    {
        surface->info.node.u.normal.cacheable = gcvFALSE;
    }


    /* Allocate surface. */
    gcmONERROR(
        _AllocateSurface(surface,
                         Width, Height, Depth,
                         Type,
                         Format,
                         Pool));

    surface->referenceCount = 1;

#if defined(ANDROID) && gcdDEFER_RESOLVES
    /* Create a signal for SF-app synchronization. */
    if (Type & gcvSURF_RENDER_TARGET)
    {
        gcmONERROR(gcoOS_CreateSignal(
                    gcvNULL,
                    gcvFALSE,
                    &surface->resolveSubmittedSignal
                    ));
    }
#endif

    gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                  "Created gcoSURF 0x%x",
                  surface);

#if gcdSYNC
    surface->info.fenceStatus = gcvFENCE_DISABLE;
    surface->info.fenceCtx = gcvNULL;
#endif

    /* Return pointer to the gcoSURF object. */
    *Surface = surface;

    /* Success. */
    gcmFOOTER_ARG("*Surface=0x%x", *Surface);
    return gcvSTATUS_OK;

OnError:
    /* Free the allocated memory. */
    if (surface != gcvNULL)
    {
        gcmOS_SAFE_FREE(gcvNULL, surface);
    }

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Destroy
**
**  Destroy an gcoSURF object.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object to be destroyed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Destroy(
    IN gcoSURF Surface
    )
{

    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Decrement surface reference count. */
    if (--Surface->referenceCount != 0)
    {
        /* Still references to this surface. */
        gcmFOOTER_NO();
        return gcvSTATUS_OK;
    }


    if (gcPLS.hal->dump != gcvNULL)
    {
        /* Dump the deletion. */
        gcmVERIFY_OK(
            gcoDUMP_Delete(gcPLS.hal->dump, Surface->info.node.physical));
    }

    /* User-allocated surface? */
    if (Surface->info.node.pool == gcvPOOL_USER)
    {
        gcmVERIFY_OK(
            _UnmapUserBuffer(Surface, gcvTRUE));
    }

#if defined(ANDROID) && gcdDEFER_RESOLVES
    /* Destroy signal used for SF-app synchronization. */
    if (Surface->info.type & gcvSURF_RENDER_TARGET)
    {
        gcmVERIFY_OK(gcoOS_DestroySignal(
                        gcvNULL,
                        Surface->resolveSubmittedSignal
                        ));
    }
#endif

    /* Free the video memory. */
    gcmVERIFY_OK(_FreeSurface(Surface));

    /* Mark gcoSURF object as unknown. */
    Surface->object.type = gcvOBJ_UNKNOWN;

    /* Free the gcoSURF object. */
    gcmVERIFY_OK(gcmOS_SAFE_FREE(gcvNULL, Surface));

    gcmTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_SURFACE,
                  "Destroyed gcoSURF 0x%x",
                  Surface);

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_QueryVidMemNode
**
**  Query the video memory node attributes of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**
**      gcuVIDMEM_NODE_PTR * Node
**          Pointer to a variable receiving the video memory node.
**
**      gcePOOL * Pool
**          Pointer to a variable receiving the pool the video memory node originated from.
**
**      gctUINT_PTR Bytes
**          Pointer to a variable receiving the video memory node size in bytes.
**
*/
gceSTATUS
gcoSURF_QueryVidMemNode(
    IN gcoSURF Surface,
    OUT gctUINT64 * Node,
    OUT gcePOOL * Pool,
    OUT gctUINT_PTR Bytes
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);
    gcmVERIFY_ARGUMENT(Node != gcvNULL);
    gcmVERIFY_ARGUMENT(Pool != gcvNULL);
    gcmVERIFY_ARGUMENT(Bytes != gcvNULL);

    /* Return the video memory attributes. */
    *Node = Surface->info.node.u.normal.node;
    *Pool = Surface->info.node.pool;
    *Bytes = Surface->info.node.size;

    /* Success. */
    gcmFOOTER_ARG("*Node=0x%x *Pool=%d *Bytes=%d", *Node, *Pool, *Bytes);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_SetUsage
**
**  Set usage attribute of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceSURF_USAGE Usage
**          Usage purpose for the surface.
**
**  OUTPUT:
**      None
**
*/
gceSTATUS
gcoSURF_SetUsage(
    IN gcoSURF Surface,
    IN gceSURF_USAGE Usage
    )
{
    Surface->info.usage = Usage;
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_QueryUsage
**
**  Return usage attribute of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**      gceSURF_USAGE *Usage
**          Usage purpose for the surface.
**
*/
gceSTATUS
gcoSURF_QueryUsage(
    IN gcoSURF Surface,
    OUT gceSURF_USAGE *Usage
    )
{
    if (Usage)
    {
        *Usage = Surface->info.usage;
    }

    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_MapUserSurface
**
**  Store the logical and physical pointers to the user-allocated surface in
**  the gcoSURF object and map the pointers as necessary.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object to be destroyed.
**
**      gctUINT Alignment
**          Alignment of each pixel row in bytes.
**
**      gctPOINTER Logical
**          Logical pointer to the user allocated surface or gcvNULL if no
**          logical pointer has been provided.
**
**      gctUINT32 Physical
**          Physical pointer to the user allocated surface or gcvINVALID_ADDRESS if no
**          physical pointer has been provided.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_MapUserSurface(
    IN gcoSURF Surface,
    IN gctUINT Alignment,
    IN gctPOINTER Logical,
    IN gctUINT32 Physical
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gctBOOL logicalMapped = gcvFALSE;
    gctPOINTER mappingInfo = gcvNULL;

    gctPOINTER logical = gcvNULL;
    gctUINT32 physical = 0;

    gcmHEADER_ARG("Surface=0x%x Alignment=%u Logical=0x%x Physical=%08x",
              Surface, Alignment, Logical, Physical);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    do
    {
        /* Has to be user-allocated surface. */
        if (Surface->info.node.pool != gcvPOOL_USER)
        {
            status = gcvSTATUS_NOT_SUPPORTED;
            break;
        }

        /* Already mapped? */
        if (Surface->info.node.lockCount > 0)
        {
            if ((Logical != gcvNULL) &&
                (Logical != Surface->info.node.logical))
            {
                status = gcvSTATUS_INVALID_ARGUMENT;
                break;
            }

            if ((Physical != gcvINVALID_ADDRESS) &&
                (Physical != Surface->info.node.physical))
            {
                status = gcvSTATUS_INVALID_ARGUMENT;
                break;
            }

            /* Success. */
            break;
        }
        /* Set new alignment. */
        if (Alignment != 0)
        {
            /* Compute the unaligned stride. */
            gctUINT32 stride = Surface->info.alignedWidth * Surface->info.bitsPerPixel / 8;

            /* Align the stide (Alignment can be not a power of number). */
            if (gcoMATH_ModuloUInt(stride, Alignment) != 0)
            {
                stride = gcoMATH_DivideUInt(stride, Alignment)  * Alignment
                       + Alignment;
            }

            /* Set the new stride. */
            Surface->info.stride = stride;

            /* Compute the new size. */
            Surface->info.size
                = stride * Surface->info.alignedHeight;
        }

        /* Map logical pointer if not specified. */
        if (Logical == gcvNULL)
        {
            if (Physical == gcvINVALID_ADDRESS)
            {
                status = gcvSTATUS_INVALID_ARGUMENT;
                break;
            }

            /* Map the logical pointer. */
            gcmERR_BREAK(gcoHAL_MapMemory(
                gcvNULL,
                gcmINT2PTR(Physical),
                Surface->info.size,
                &logical
                ));

            /* Mark as mapped. */
            logicalMapped = gcvTRUE;
        }
        else
        {
            /* Set the logical pointer. */
            logical = Logical;
        }

        /* Map physical pointer to GPU address. */
        gcmERR_BREAK(gcoHAL_MapUserMemory(
                Logical,
                Physical,
                Surface->info.size,
                &mappingInfo,
                &physical
                ));

        /* Validate the surface. */
        Surface->info.node.valid = gcvTRUE;

        /* Set the lock count. */
        Surface->info.node.lockCount++;

        /* Set the node parameters. */
        Surface->info.node.u.wrapped.logicalMapped = logicalMapped;
        Surface->info.node.u.wrapped.mappingInfo   = mappingInfo;
        gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL,
                                            &Surface->info.node.u.wrapped.mappingHardwareType));
        Surface->info.node.logical                 = logical;
        Surface->info.node.physical                = physical;
        Surface->info.node.count                   = 1;
    }
    while (gcvFALSE);

    /* Roll back. */
    if (gcmIS_ERROR(status))
    {
        if (logicalMapped)
        {
            gcmVERIFY_OK(gcoHAL_UnmapMemory(
                gcvNULL,
                gcmINT2PTR(physical),
                Surface->info.size,
                logical
                ));
        }

        if (mappingInfo != gcvNULL)
        {
            gcmVERIFY_OK(gcoOS_UnmapUserMemory(
                gcvNULL,
                logical,
                Surface->info.size,
                mappingInfo,
                physical
                ));
        }
    }

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_IsValid
**
**  Verify whether the surface is a valid gcoSURF object.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to a gcoSURF object.
**
**  RETURNS:
**
**      The return value of the function is set to gcvSTATUS_TRUE if the
**      surface is valid.
*/
gceSTATUS
gcoSURF_IsValid(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Set return value. */
    status = ((Surface != gcvNULL)
        && (Surface->object.type != gcvOBJ_SURF))
        ? gcvSTATUS_FALSE
        : gcvSTATUS_TRUE;

    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoSURF_GetSize
**
**  Get the size of an gcoSURF object.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      gctUINT * Width
**          Pointer to variable that will receive the width of the gcoSURF
**          object.  If 'Width' is gcvNULL, no width information shall be returned.
**
**      gctUINT * Height
**          Pointer to variable that will receive the height of the gcoSURF
**          object.  If 'Height' is gcvNULL, no height information shall be returned.
**
**      gctUINT * Depth
**          Pointer to variable that will receive the depth of the gcoSURF
**          object.  If 'Depth' is gcvNULL, no depth information shall be returned.
*/
gceSTATUS
gcoSURF_GetSize(
    IN gcoSURF Surface,
    OUT gctUINT * Width,
    OUT gctUINT * Height,
    OUT gctUINT * Depth
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    if (Width != gcvNULL)
    {
        /* Return the width. */
        *Width =
            Surface->info.rect.right;
    }

    if (Height != gcvNULL)
    {
        /* Return the height. */
        *Height =
            Surface->info.rect.bottom;
    }

    if (Depth != gcvNULL)
    {
        /* Return the depth. */
        *Depth = Surface->depth;
    }

    /* Success. */
    gcmFOOTER_ARG("*Width=%u *Height=%u *Depth=%u",
                  (Width  == gcvNULL) ? 0 : *Width,
                  (Height == gcvNULL) ? 0 : *Height,
                  (Depth  == gcvNULL) ? 0 : *Depth);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_GetAlignedSize
**
**  Get the aligned size of an gcoSURF object.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      gctUINT * Width
**          Pointer to variable that receives the aligned width of the gcoSURF
**          object.  If 'Width' is gcvNULL, no width information shall be returned.
**
**      gctUINT * Height
**          Pointer to variable that receives the aligned height of the gcoSURF
**          object.  If 'Height' is gcvNULL, no height information shall be
**          returned.
**
**      gctINT * Stride
**          Pointer to variable that receives the stride of the gcoSURF object.
**          If 'Stride' is gcvNULL, no stride information shall be returned.
*/
gceSTATUS
gcoSURF_GetAlignedSize(
    IN gcoSURF Surface,
    OUT gctUINT * Width,
    OUT gctUINT * Height,
    OUT gctINT * Stride
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    if (Width != gcvNULL)
    {
        /* Return the aligned width. */
        *Width = Surface->info.alignedWidth;
    }

    if (Height != gcvNULL)
    {
        /* Return the aligned height. */
        *Height = Surface->info.alignedHeight;
    }

    if (Stride != gcvNULL)
    {
        /* Return the stride. */
        *Stride = Surface->info.stride;
    }

    /* Success. */
    gcmFOOTER_ARG("*Width=%u *Height=%u *Stride=%d",
                  (Width  == gcvNULL) ? 0 : *Width,
                  (Height == gcvNULL) ? 0 : *Height,
                  (Stride == gcvNULL) ? 0 : *Stride);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_GetAlignment
**
**  INPUT:
**
**      gcoHAL Hal
**          Pointer to an gcoHAL object.
**
**      gceSURF_TYPE Type
**          Type of surface.
**
**      gceSURF_FORMAT Format
**          Format of surface.
**
**  OUTPUT:
**
**      gctUINT * addressAlignment
**          Pointer to the variable of address alignment.
**      gctUINT * xAlignmenet
**          Pointer to the variable of x Alignment.
**      gctUINT * yAlignment
**          Pointer to the variable of y Alignment.
*/
gceSTATUS
gcoSURF_GetAlignment(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    OUT gctUINT * AddressAlignment,
    OUT gctUINT * XAlignment,
    OUT gctUINT * YAlignment
    )
{
    gctUINT xAlign = (gcvSURF_TEXTURE == Type) ? 4 : 16;
    gctUINT yAlign = 4;

    gcmHEADER_ARG("Type=%d Format=%d", Type, Format);

    /* Compute alignment factors. */
    if (XAlignment != gcvNULL)
    {
        *XAlignment = xAlign;
    }

    if (YAlignment != gcvNULL)
    {
        *YAlignment = yAlign;
    }

    if (AddressAlignment != gcvNULL)
    {
        *AddressAlignment = 64;
    }

    gcmFOOTER_ARG("*XAlignment=0x%x  *YAlignment=0x%x *AddressAlignment=0x%x",
        gcmOPT_VALUE(XAlignment), gcmOPT_VALUE(YAlignment), gcmOPT_VALUE(AddressAlignment));
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gcoSURF_GetFormat
**
**  Get surface type and format.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      gceSURF_TYPE * Type
**          Pointer to variable that receives the type of the gcoSURF object.
**          If 'Type' is gcvNULL, no type information shall be returned.
**
**      gceSURF_FORMAT * Format
**          Pointer to variable that receives the format of the gcoSURF object.
**          If 'Format' is gcvNULL, no format information shall be returned.
*/
gceSTATUS
gcoSURF_GetFormat(
    IN gcoSURF Surface,
    OUT gceSURF_TYPE * Type,
    OUT gceSURF_FORMAT * Format
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    if (Type != gcvNULL)
    {
        /* Return the surface type. */
        *Type = Surface->info.type;
    }

    if (Format != gcvNULL)
    {
        /* Return the surface format. */
        *Format = Surface->info.format;
    }

    /* Success. */
    gcmFOOTER_ARG("*Type=%d *Format=%d",
                  (Type   == gcvNULL) ? 0 : *Type,
                  (Format == gcvNULL) ? 0 : *Format);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_GetTiling
**
**  Get surface tiling.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      gceTILING * Tiling
**          Pointer to variable that receives the tiling of the gcoSURF object.
*/
gceSTATUS
gcoSURF_GetTiling(
    IN gcoSURF Surface,
    OUT gceTILING * Tiling
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    if (Tiling != gcvNULL)
    {
        /* Return the surface tiling. */
        *Tiling = Surface->info.tiling;
    }

    /* Success. */
    gcmFOOTER_ARG("*Tiling=%d",
                  (Tiling == gcvNULL) ? 0 : *Tiling);
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gcoSURF_Lock
**
**  Lock the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      gctUINT32 * Address
**          Physical address array of the surface:
**          For YV12, Address[0] is for Y channel,
**                    Address[1] is for V channel and
**                    Address[2] is for U channel;
**          For I420, Address[0] is for Y channel,
**                    Address[1] is for U channel and
**                    Address[2] is for V channel;
**          For NV12, Address[0] is for Y channel and
**                    Address[1] is for UV channel;
**          For all other formats, only Address[0] is used to return the
**          physical address.
**
**      gctPOINTER * Memory
**          Logical address array of the surface:
**          For YV12, Memory[0] is for Y channel,
**                    Memory[1] is for V channel and
**                    Memory[2] is for U channel;
**          For I420, Memory[0] is for Y channel,
**                    Memory[1] is for U channel and
**                    Memory[2] is for V channel;
**          For NV12, Memory[0] is for Y channel and
**                    Memory[1] is for UV channel;
**          For all other formats, only Memory[0] is used to return the logical
**          address.
*/
gceSTATUS
gcoSURF_Lock(
    IN gcoSURF Surface,
    OPTIONAL OUT gctUINT32 * Address,
    OPTIONAL OUT gctPOINTER * Memory
    )
{
    gceSTATUS status;
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Lock the surface. */
    gcmONERROR(_Lock(Surface));
    /* Determine surface addresses. */
    switch (Surface->info.format)
    {
    case gcvSURF_YV12:
    case gcvSURF_I420:
        Surface->info.node.count = 3;

        Surface->info.node.logical2  = Surface->info.node.logical
                                     + Surface->info.uOffset;

        Surface->info.node.physical2 = Surface->info.node.physical
                                     + Surface->info.uOffset;

        Surface->info.node.logical3  = Surface->info.node.logical
                                     + Surface->info.vOffset;

        Surface->info.node.physical3 = Surface->info.node.physical
                                     + Surface->info.vOffset;
        break;

    case gcvSURF_NV12:
    case gcvSURF_NV21:
    case gcvSURF_NV16:
    case gcvSURF_NV61:
        Surface->info.node.count = 2;

        Surface->info.node.logical2  = Surface->info.node.logical
                                     + Surface->info.uOffset;

        Surface->info.node.physical2 = Surface->info.node.physical
                                     + Surface->info.uOffset;
        break;

    default:
        Surface->info.node.count = 1;
    }

    /* Set result. */
    if (Address != gcvNULL)
    {
        if (Surface->info.format == gcvSURF_YV12)
        {
            Address[2] = Surface->info.node.physical2;
            Address[1] = Surface->info.node.physical3;
            Address[0] = Surface->info.node.physical;
        }
        else
        {
            switch (Surface->info.node.count)
            {
            case 3:
                Address[2] = Surface->info.node.physical3;

                /* FALLTHROUGH */
            case 2:
                Address[1] = Surface->info.node.physical2;

                /* FALLTHROUGH */
            case 1:
                Address[0] = Surface->info.node.physical;

                /* FALLTHROUGH */
            default:
                break;
            }
        }
    }

    if (Memory != gcvNULL)
    {
        if (Surface->info.format == gcvSURF_YV12)
        {
            Memory[2] = Surface->info.node.logical2;
            Memory[1] = Surface->info.node.logical3;
            Memory[0] = Surface->info.node.logical;
        }
        else
        {
            switch (Surface->info.node.count)
            {
            case 3:
                Memory[2] = Surface->info.node.logical3;

                /* FALLTHROUGH */
            case 2:
                Memory[1] = Surface->info.node.logical2;

                /* FALLTHROUGH */
            case 1:
                Memory[0] = Surface->info.node.logical;

                /* FALLTHROUGH */
            default:
                break;
            }
        }
    }

    /* Success. */
    gcmFOOTER_ARG("*Address=%08X *Memory=0x%x",
                  (Address == gcvNULL) ? 0 : *Address,
                  (Memory  == gcvNULL) ? gcvNULL : *Memory);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Unlock
**
**  Unlock the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**      gctPOINTER Memory
**          Pointer to mapped memory.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Unlock(
    IN gcoSURF Surface,
    IN gctPOINTER Memory
    )
{
    gceSTATUS status;
    gcmHEADER_ARG("Surface=0x%x Memory=0x%x", Surface, Memory);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Unlock the surface. */
    gcmONERROR(_Unlock(Surface));
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
**  gcoSURF_Fill
**
**  Fill surface with specified value.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**      gcsPOINT_PTR Origin
**          Pointer to the origin of the area to be filled.
**          Assumed to (0, 0) if gcvNULL is given.
**
**      gcsSIZE_PTR Size
**          Pointer to the size of the area to be filled.
**          Assumed to the size of the surface if gcvNULL is given.
**
**      gctUINT32 Value
**          Value to be set.
**
**      gctUINT32 Mask
**          Value mask.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Fill(
    IN gcoSURF Surface,
    IN gcsPOINT_PTR Origin,
    IN gcsSIZE_PTR Size,
    IN gctUINT32 Value,
    IN gctUINT32 Mask
    )
{
    return gcvSTATUS_NOT_SUPPORTED;
}

/*******************************************************************************
**
**  gcoSURF_Blend
**
**  Alpha blend two surfaces together.
**
**  INPUT:
**
**      gcoSURF SrcSurface
**          Pointer to the source gcoSURF object.
**
**      gcoSURF DestSurface
**          Pointer to the destination gcoSURF object.
**
**      gcsPOINT_PTR SrcOrigin
**          The origin within the source.
**          If gcvNULL is specified, (0, 0) origin is assumed.
**
**      gcsPOINT_PTR DestOrigin
**          The origin within the destination.
**          If gcvNULL is specified, (0, 0) origin is assumed.
**
**      gcsSIZE_PTR Size
**          The size of the area to be blended.
**
**      gceSURF_BLEND_MODE Mode
**          One of the blending modes.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Blend(
    IN gcoSURF SrcSurface,
    IN gcoSURF DestSurface,
    IN gcsPOINT_PTR SrcOrigin,
    IN gcsPOINT_PTR DestOrigin,
    IN gcsSIZE_PTR Size,
    IN gceSURF_BLEND_MODE Mode
    )
{
    return gcvSTATUS_NOT_SUPPORTED;
}


/*******************************************************************************
**
**  gcoSURF_SetClipping
**
**  Set cipping rectangle to the size of the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetClipping(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    do
    {
        gco2D engine;
        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));
        gcmERR_BREAK(gco2D_SetClipping(engine, &Surface->info.rect));
    }
    while (gcvFALSE);

    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Clear2D
**
**  Clear one or more rectangular areas.
**
**  INPUT:
**
**      gcoSURF DestSurface
**          Pointer to the destination surface.
**
**      gctUINT32 RectCount
**          The number of rectangles to draw. The array of rectangles
**          pointed to by Rect parameter must have at least RectCount items.
**          Note, that for masked source blits only one destination rectangle
**          is supported.
**
**      gcsRECT_PTR DestRect
**          Pointer to a list of destination rectangles.
**
**      gctUINT32 LoColor
**          Low 32-bit clear color values.
**
**      gctUINT32 HiColor
**          high 32-bit clear color values.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Clear2D(
    IN gcoSURF DestSurface,
    IN gctUINT32 RectCount,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 LoColor,
    IN gctUINT32 HiColor
    )
{
    gceSTATUS status;
    gctPOINTER destMemory[3] = {gcvNULL};
    gco2D engine;

    gcmHEADER_ARG("DestSurface=0x%x RectCount=%u DestRect=0x%x LoColor=%u HiColor=%u",
              DestSurface, RectCount, DestRect, LoColor, HiColor);

    do
    {
        /* Validate the object. */
        gcmBADOBJECT_BREAK(DestSurface, gcvOBJ_SURF);

        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        /* Use surface rect if not specified. */
        if (DestRect == gcvNULL)
        {
            if (RectCount != 1)
            {
                status = gcvSTATUS_INVALID_ARGUMENT;
                break;
            }

            DestRect = &DestSurface->info.rect;
        }

        /* Lock the destination. */
        gcmERR_BREAK(gcoSURF_Lock(
            DestSurface,
            gcvNULL,
            destMemory
            ));

        /* Program the destination. */
        gcmERR_BREAK(gco2D_SetTargetEx(
            engine,
            DestSurface->info.node.physical,
            DestSurface->info.stride,
            DestSurface->info.rotation,
            DestSurface->info.alignedWidth,
            DestSurface->info.alignedHeight
            ));

        gcmERR_BREAK(gco2D_SetTransparencyAdvanced(
            engine,
            gcv2D_OPAQUE,
            gcv2D_OPAQUE,
            gcv2D_OPAQUE
            ));

        /* Form a CLEAR command. */
        gcmERR_BREAK(gco2D_Clear(
            engine,
            RectCount,
            DestRect,
            LoColor,
            gcvFALSE,
            0xCC,
            0xCC
            ));
    }
    while (gcvFALSE);

    /* Unlock the destination. */
    if (destMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(DestSurface, destMemory[0]));
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Line
**
**  Draw one or more Bresenham lines.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to an gcoSURF object.
**
**      gctUINT32 LineCount
**          The number of lines to draw. The array of line positions pointed
**          to by Position parameter must have at least LineCount items.
**
**      gcsRECT_PTR Position
**          Points to an array of positions in (x0, y0)-(x1, y1) format.
**
**      gcoBRUSH Brush
**          Brush to use for drawing.
**
**      gctUINT8 FgRop
**          Foreground ROP to use with opaque pixels.
**
**      gctUINT8 BgRop
**          Background ROP to use with transparent pixels.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Line(
    IN gcoSURF DestSurface,
    IN gctUINT32 LineCount,
    IN gcsRECT_PTR Position,
    IN gcoBRUSH Brush,
    IN gctUINT8 FgRop,
    IN gctUINT8 BgRop
    )
{
    gceSTATUS status;
    gctPOINTER destMemory[3] = {gcvNULL};
    gco2D engine;

    gcmHEADER_ARG("DestSurface=0x%x LineCount=%u Position=0x%x Brush=0x%x FgRop=%02x "
              "BgRop=%02x",
              DestSurface, LineCount, Position, Brush, FgRop, BgRop);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(DestSurface, gcvOBJ_SURF);

    do
    {
        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        /* Lock the destination. */
        gcmERR_BREAK(gcoSURF_Lock(
            DestSurface,
            gcvNULL,
            destMemory
            ));

        /* Program the destination. */
        gcmERR_BREAK(gco2D_SetTargetEx(
            engine,
            DestSurface->info.node.physical,
            DestSurface->info.stride,
            DestSurface->info.rotation,
            DestSurface->info.alignedWidth,
            DestSurface->info.alignedHeight
            ));

        gcmERR_BREAK(gco2D_SetTransparencyAdvanced(
            engine,
            gcv2D_OPAQUE,
            gcv2D_OPAQUE,
            gcv2D_OPAQUE
            ));

        /* Draw a LINE command. */
        gcmERR_BREAK(gco2D_Line(
            engine,
            LineCount,
            Position,
            Brush,
            FgRop,
            BgRop,
            DestSurface->info.format
            ));
    }
    while (gcvFALSE);

    /* Unlock the destination. */
    if (destMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(DestSurface, destMemory[0]));
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Blit
**
**  Generic rectangular blit.
**
**  INPUT:
**
**      OPTIONAL gcoSURF SrcSurface
**          Pointer to the source surface.
**
**      gcoSURF DestSurface
**          Pointer to the destination surface.
**
**      gctUINT32 RectCount
**          The number of rectangles to draw. The array of rectangles
**          pointed to by Rect parameter must have at least RectCount items.
**          Note, that for masked source blits only one destination rectangle
**          is supported.
**
**      OPTIONAL gcsRECT_PTR SrcRect
**          If RectCount is 1, SrcRect represents an sbsolute rectangle within
**          the source surface.
**          If RectCount is greater then 1, (right,bottom) members of SrcRect
**          are ignored and (left,top) members are used as the offset from
**          the origin of each destination rectangle in DestRect list to
**          determine the corresponding source rectangle. In this case the width
**          and the height of the source are assumed the same as of the
**          corresponding destination rectangle.
**
**      gcsRECT_PTR DestRect
**          Pointer to a list of destination rectangles.
**
**      OPTIONAL gcoBRUSH Brush
**          Brush to use for drawing.
**
**      gctUINT8 FgRop
**          Foreground ROP to use with opaque pixels.
**
**      gctUINT8 BgRop
**          Background ROP to use with transparent pixels.
**
**      OPTIONAL gceSURF_TRANSPARENCY Transparency
**          gcvSURF_OPAQUE - each pixel of the bitmap overwrites the destination.
**          gcvSURF_SOURCE_MATCH - source pixels compared against register value
**              to determine the transparency. In simple terms, the transaprency
**              comes down to selecting the ROP code to use. Opaque pixels use
**              foreground ROP and transparent ones use background ROP.
**          gcvSURF_SOURCE_MASK - monochrome source mask defines transparency.
**          gcvSURF_PATTERN_MASK - pattern mask defines transparency.
**
**      OPTIONAL gctUINT32 TransparencyColor
**          This value is used in gcvSURF_SOURCE_MATCH transparency mode.
**          The value is compared against each pixel to determine transparency
**          of the pixel. If the values found equal, the pixel is transparent;
**          otherwise it is opaque.
**
**      OPTIONAL gctPOINTER Mask
**          A pointer to monochrome mask for masked source blits.
**
**      OPTIONAL gceSURF_MONOPACK MaskPack
**          Determines how many horizontal pixels are there per each 32-bit
**          chunk of monochrome mask. For example, if set to gcvSURF_PACKED8,
**          each 32-bit chunk is 8-pixel wide, which also means that it defines
**          4 vertical lines of pixel mask.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Blit(
    IN OPTIONAL gcoSURF SrcSurface,
    IN gcoSURF DestSurface,
    IN gctUINT32 RectCount,
    IN OPTIONAL gcsRECT_PTR SrcRect,
    IN gcsRECT_PTR DestRect,
    IN OPTIONAL gcoBRUSH Brush,
    IN gctUINT8 FgRop,
    IN gctUINT8 BgRop,
    IN OPTIONAL gceSURF_TRANSPARENCY Transparency,
    IN OPTIONAL gctUINT32 TransparencyColor,
    IN OPTIONAL gctPOINTER Mask,
    IN OPTIONAL gceSURF_MONOPACK MaskPack
    )
{
    gceSTATUS status;

    /*gcoHARDWARE hardware;*/
    gco2D engine;

    gce2D_TRANSPARENCY srcTransparency;
    gce2D_TRANSPARENCY dstTransparency;
    gce2D_TRANSPARENCY patTransparency;

    gctBOOL useBrush;
    gctBOOL useSource;

    gctBOOL stretchBlt = gcvFALSE;
    gctBOOL relativeSource = gcvFALSE;

    gctPOINTER srcMemory[3]  = {gcvNULL};
    gctPOINTER destMemory[3] = {gcvNULL};

    gctBOOL useSoftEngine = gcvFALSE;

    gcmHEADER_ARG("SrcSurface=0x%x DestSurface=0x%x RectCount=%u SrcRect=0x%x "
              "DestRect=0x%x Brush=0x%x FgRop=%02x BgRop=%02x Transparency=%d "
              "TransparencyColor=%08x Mask=0x%x MaskPack=%d",
              SrcSurface, DestSurface, RectCount, SrcRect, DestRect, Brush,
              FgRop, BgRop, Transparency, TransparencyColor, Mask, MaskPack);

    do
    {
        gctUINT32 destFormat, destFormatSwizzle, destIsYUV;

        /* Validate the object. */
        gcmBADOBJECT_BREAK(DestSurface, gcvOBJ_SURF);

        /* Is 2D Hardware available? */
        if (!gcoHARDWARE_Is2DAvailable())
        {
            /* No, use software renderer. */
            gcmERR_BREAK(gcoHARDWARE_UseSoftware2D(gcvTRUE));
            useSoftEngine = gcvTRUE;
        }

        /* Is the destination format supported? */
        if (gcmIS_ERROR(gcoHARDWARE_TranslateDestinationFormat(
                DestSurface->info.format,
                &destFormat, &destFormatSwizzle, &destIsYUV)))
        {
            /* No, use software renderer. */
            gcmERR_BREAK(gcoHARDWARE_UseSoftware2D(gcvTRUE));
            useSoftEngine = gcvTRUE;
        }

        /* Translate the specified transparency mode. */
        gcmERR_BREAK(gcoHARDWARE_TranslateSurfTransparency(
            Transparency,
            &srcTransparency,
            &dstTransparency,
            &patTransparency
            ));

        /* Determine the resource usage. */
        gcoHARDWARE_Get2DResourceUsage(
            FgRop, BgRop,
            srcTransparency,
            &useSource, &useBrush, gcvNULL
            );

        /* Use surface rect if not specified. */
        if (DestRect == gcvNULL)
        {
            if (RectCount != 1)
            {
                status = gcvSTATUS_INVALID_ARGUMENT;
                break;
            }

            DestRect = &DestSurface->info.rect;
        }

        /* Get 2D engine. */
        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        /* Setup the brush if needed. */
        if (useBrush)
        {
            /* Flush the brush. */
            gcmERR_BREAK(gco2D_FlushBrush(
                engine,
                Brush,
                DestSurface->info.format
                ));
        }

        /* Setup the source if needed. */
        if (useSource)
        {
            /* Validate the object. */
            gcmBADOBJECT_BREAK(SrcSurface, gcvOBJ_SURF);

            /* Use surface rect if not specified. */
            if (SrcRect == gcvNULL)
            {
                SrcRect = &SrcSurface->info.rect;
            }

            /* Lock the source. */
            gcmERR_BREAK(gcoSURF_Lock(
                SrcSurface,
                gcvNULL,
                srcMemory
                ));

            /* Determine the relative flag. */
            relativeSource = (RectCount > 1) ? gcvTRUE : gcvFALSE;

            /* Program the source. */
            if (Mask == gcvNULL)
            {
                gctBOOL equal;

                /* Check whether this should be a stretch/shrink blit. */
                if ( (gcsRECT_IsOfEqualSize(SrcRect, DestRect, &equal) ==
                          gcvSTATUS_OK) &&
                     !equal )
                {
                    /* Calculate the stretch factors. */
                    gcmERR_BREAK(gco2D_SetStretchRectFactors(
                        engine,
                        SrcRect, DestRect
                        ));

                    /* Mark as stretch blit. */
                    stretchBlt = gcvTRUE;
                }

                gcmERR_BREAK(gco2D_SetColorSourceEx(
                    engine,
                    useSoftEngine ?
                        (gctUINT32)(gctUINTPTR_T)SrcSurface->info.node.logical
                        : SrcSurface->info.node.physical,
                    SrcSurface->info.stride,
                    SrcSurface->info.format,
                    SrcSurface->info.rotation,
                    SrcSurface->info.alignedWidth,
                    SrcSurface->info.alignedHeight,
                    relativeSource,
                    Transparency,
                    TransparencyColor
                    ));

                gcmERR_BREAK(gco2D_SetSource(
                    engine,
                    SrcRect
                    ));
            }
        }

        /* Lock the destination. */
        gcmERR_BREAK(gcoSURF_Lock(
            DestSurface,
            gcvNULL,
            destMemory
            ));

        gcmERR_BREAK(gco2D_SetTargetEx(
            engine,
            useSoftEngine ?
                (gctUINT32)(gctUINTPTR_T)DestSurface->info.node.logical
                : DestSurface->info.node.physical,
            DestSurface->info.stride,
            DestSurface->info.rotation,
            DestSurface->info.alignedWidth,
            DestSurface->info.alignedHeight
            ));

        /* Masked sources need to be handled differently. */
        if (useSource && (Mask != gcvNULL))
        {
            gctUINT32 streamPackHeightMask;
            gcsSURF_FORMAT_INFO_PTR srcFormat[2];
            gctUINT32 srcAlignedLeft, srcAlignedTop;
            gctINT32 tileWidth, tileHeight;
            gctUINT32 tileHeightMask;
            gctUINT32 maxHeight;
            gctUINT32 srcBaseAddress;
            gcsRECT srcSubRect;
            gcsRECT destSubRect;
            gcsRECT maskRect;
            gcsPOINT maskSize;
            gctUINT32 lines2render;
            gctUINT32 streamWidth;
            gceSURF_MONOPACK streamPack;

            /* Compute the destination size. */
            gctUINT32 destWidth  = DestRect->right  - DestRect->left;
            gctUINT32 destHeight = DestRect->bottom - DestRect->top;

            /* Query tile size. */
            gcmASSERT(SrcSurface->info.type == gcvSURF_BITMAP);
            gcoHARDWARE_QueryTileSize(
                &tileWidth, &tileHeight,
                gcvNULL, gcvNULL,
                gcvNULL
                );

            tileHeightMask = tileHeight - 1;

            /* Determine left source coordinate. */
            srcSubRect.left = SrcRect->left & 7;

            /* Assume 8-pixel packed stream. */
            streamWidth = gcmALIGN(srcSubRect.left + destWidth, 8);

            /* Do we fit? */
            if (streamWidth == 8)
            {
                streamPack = gcvSURF_PACKED8;
                streamPackHeightMask = ~3U;
            }

            /* Nope, don't fit. */
            else
            {
                /* Assume 16-pixel packed stream. */
                streamWidth = gcmALIGN(srcSubRect.left + destWidth, 16);

                /* Do we fit now? */
                if (streamWidth == 16)
                {
                    streamPack = gcvSURF_PACKED16;
                    streamPackHeightMask = ~1U;
                }

                /* Still don't. */
                else
                {
                    /* Assume unpacked stream. */
                    streamWidth = gcmALIGN(srcSubRect.left + destWidth, 32);
                    streamPack = gcvSURF_UNPACKED;
                    streamPackHeightMask = ~0U;
                }
            }

            /* Determine the maxumum stream height. */
            maxHeight  = gcoMATH_DivideUInt(gco2D_GetMaximumDataCount() << 5,
                                            streamWidth);
            maxHeight &= streamPackHeightMask;

            /* Determine the sub source rectangle. */
            srcSubRect.top    = SrcRect->top & tileHeightMask;
            srcSubRect.right  = srcSubRect.left + destWidth;
            srcSubRect.bottom = srcSubRect.top;

            /* Init destination subrectangle. */
            destSubRect.left   = DestRect->left;
            destSubRect.top    = DestRect->top;
            destSubRect.right  = DestRect->right;
            destSubRect.bottom = destSubRect.top;

            /* Determine the number of lines to render. */
            lines2render = srcSubRect.top + destHeight;

            /* Determine the aligned source coordinates. */
            srcAlignedLeft = SrcRect->left - srcSubRect.left;
            srcAlignedTop  = SrcRect->top  - srcSubRect.top;
            gcmASSERT((srcAlignedLeft % tileWidth) == 0);

            /* Get format characteristics. */
            gcmERR_BREAK(gcoSURF_QueryFormat(SrcSurface->info.format, srcFormat));

            /* Determine the initial source address. */
            srcBaseAddress
                = (useSoftEngine ?
                        (gctUINT32)(gctUINTPTR_T)SrcSurface->info.node.logical
                        : SrcSurface->info.node.physical)
                +   srcAlignedTop  * SrcSurface->info.stride
                + ((srcAlignedLeft * srcFormat[0]->bitsPerPixel) >> 3);

            /* Set initial mask coordinates. */
            maskRect.left   = srcAlignedLeft;
            maskRect.top    = srcAlignedTop;
            maskRect.right  = maskRect.left + streamWidth;
            maskRect.bottom = maskRect.top;

            /* Set mask size. */
            maskSize.x = SrcSurface->info.rect.right;
            maskSize.y = SrcSurface->info.rect.bottom;

            do
            {
                /* Determine the area to render in this pass. */
                srcSubRect.top = srcSubRect.bottom & tileHeightMask;
                srcSubRect.bottom = srcSubRect.top + lines2render;
                if (srcSubRect.bottom > (gctINT32) maxHeight)
                    srcSubRect.bottom = maxHeight & ~tileHeightMask;

                destSubRect.top = destSubRect.bottom;
                destSubRect.bottom
                    = destSubRect.top
                    + (srcSubRect.bottom - srcSubRect.top);

                maskRect.top = maskRect.bottom;
                maskRect.bottom = maskRect.top + srcSubRect.bottom;

                /* Set source rectangle size. */
                gcmERR_BREAK(gco2D_SetSource(
                    engine,
                    &srcSubRect
                    ));

                /* Configure masked source. */
                gcmERR_BREAK(gco2D_SetMaskedSource(
                    engine,
                    srcBaseAddress,
                    SrcSurface->info.stride,
                    SrcSurface->info.format,
                    relativeSource,
                    streamPack
                    ));

                /* Do the blit. */
                gcmERR_BREAK(gco2D_MonoBlit(
                    engine,
                    Mask,
                    &maskSize,
                    &maskRect,
                    MaskPack,
                    streamPack,
                    &destSubRect,
                    FgRop,
                    BgRop,
                    DestSurface->info.format
                    ));

                /* Update the source address. */
                srcBaseAddress += srcSubRect.bottom * SrcSurface->info.stride;

                /* Update the line counter. */
                lines2render -= srcSubRect.bottom;
            }
            while (lines2render);
        }
        else if (stretchBlt)
        {
            gcmERR_BREAK(gco2D_StretchBlit(
                engine,
                RectCount,
                DestRect,
                FgRop,
                BgRop,
                DestSurface->info.format
                ));
        }
        else
        {
            gcmERR_BREAK(gco2D_Blit(
                engine,
                RectCount,
                DestRect,
                FgRop,
                BgRop,
                DestSurface->info.format
                ));
        }
    }
    while (gcvFALSE);

    /* Unlock the source. */
    if (srcMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(SrcSurface, srcMemory[0]));
    }

    /* Unlock the destination. */
    if (destMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(DestSurface, destMemory[0]));
    }

    /*gcmGETHARDWARE(hardware);*/

    if (useSoftEngine)
    {
        /* Disable software renderer. */
        gcmVERIFY_OK(gcoHARDWARE_UseSoftware2D(gcvFALSE));
    }

/*OnError:*/
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_MonoBlit
**
**  Monochrome blit.
**
**  INPUT:
**
**      gcoSURF DestSurface
**          Pointer to the destination surface.
**
**      gctPOINTER Source
**          A pointer to the monochrome bitmap.
**
**      gceSURF_MONOPACK SourcePack
**          Determines how many horizontal pixels are there per each 32-bit
**          chunk of monochrome bitmap. For example, if set to gcvSURF_PACKED8,
**          each 32-bit chunk is 8-pixel wide, which also means that it defines
**          4 vertical lines of pixels.
**
**      gcsPOINT_PTR SourceSize
**          Size of the source monochrome bitmap in pixels.
**
**      gcsPOINT_PTR SourceOrigin
**          Top left coordinate of the source within the bitmap.
**
**      gcsRECT_PTR DestRect
**          Pointer to a list of destination rectangles.
**
**      OPTIONAL gcoBRUSH Brush
**          Brush to use for drawing.
**
**      gctUINT8 FgRop
**          Foreground ROP to use with opaque pixels.
**
**      gctUINT8 BgRop
**          Background ROP to use with transparent pixels.
**
**      gctBOOL ColorConvert
**          The values of FgColor and BgColor parameters are stored directly in
**          internal color registers and are used either directly as the source
**          color or converted to the format of destination before actually
**          used. The later happens if ColorConvert is not zero.
**
**      gctUINT8 MonoTransparency
**          This value is used in gcvSURF_SOURCE_MATCH transparency mode.
**          The value can be either 0 or 1 and is compared against each mono
**          pixel to determine transparency of the pixel. If the values found
**          equal, the pixel is transparent; otherwise it is opaque.
**
**      gceSURF_TRANSPARENCY Transparency
**          gcvSURF_OPAQUE - each pixel of the bitmap overwrites the destination.
**          gcvSURF_SOURCE_MATCH - source pixels compared against register value
**              to determine the transparency. In simple terms, the transaprency
**              comes down to selecting the ROP code to use. Opaque pixels use
**              foreground ROP and transparent ones use background ROP.
**          gcvSURF_SOURCE_MASK - monochrome source mask defines transparency.
**          gcvSURF_PATTERN_MASK - pattern mask defines transparency.
**
**      gctUINT32 FgColor
**          The values are used to represent foreground color
**          of the source. If the values are in destination format, set
**          ColorConvert to 0. Otherwise, provide the values in ARGB8 format
**          and set ColorConvert to 1 to instruct the hardware to convert the
**          values to the destination format before they are actually used.
**
**      gctUINT32 BgColor
**          The values are used to represent background color
**          of the source. If the values are in destination format, set
**          ColorConvert to 0. Otherwise, provide the values in ARGB8 format
**          and set ColorConvert to 1 to instruct the hardware to convert the
**          values to the destination format before they are actually used.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_MonoBlit(
    IN gcoSURF DestSurface,
    IN gctPOINTER Source,
    IN gceSURF_MONOPACK SourcePack,
    IN gcsPOINT_PTR SourceSize,
    IN gcsPOINT_PTR SourceOrigin,
    IN gcsRECT_PTR DestRect,
    IN OPTIONAL gcoBRUSH Brush,
    IN gctUINT8 FgRop,
    IN gctUINT8 BgRop,
    IN gctBOOL ColorConvert,
    IN gctUINT8 MonoTransparency,
    IN gceSURF_TRANSPARENCY Transparency,
    IN gctUINT32 FgColor,
    IN gctUINT32 BgColor
    )
{
    gceSTATUS status;

    gco2D engine;

    gce2D_TRANSPARENCY srcTransparency;
    gce2D_TRANSPARENCY dstTransparency;
    gce2D_TRANSPARENCY patTransparency;

    gctBOOL useBrush;
    gctBOOL useSource;

    gctUINT32 destWidth;
    gctUINT32 destHeight;

    gctUINT32 maxHeight;
    gctUINT32 streamPackHeightMask;
    gcsPOINT sourceOrigin;
    gcsRECT srcSubRect;
    gcsRECT destSubRect;
    gcsRECT streamRect;
    gctUINT32 lines2render;
    gctUINT32 streamWidth;
    gceSURF_MONOPACK streamPack;

    gctPOINTER destMemory[3] = {gcvNULL};

    gctBOOL useSotfEngine = gcvFALSE;

    gcmHEADER_ARG("DestSurface=0x%x Source=0x%x SourceSize=0x%x SourceOrigin=0x%x "
              "DestRect=0x%x Brush=0x%x FgRop=%02x BgRop=%02x ColorConvert=%d "
              "MonoTransparency=%u Transparency=%d FgColor=%08x BgColor=%08x",
              DestSurface, Source, SourceSize, SourceOrigin, DestRect, Brush,
              FgRop, BgRop, ColorConvert, MonoTransparency, Transparency,
              FgColor, BgColor);

    do
    {
        gctUINT32 destFormat, destFormatSwizzle, destIsYUV;

        /* Validate the object. */
        gcmBADOBJECT_BREAK(DestSurface, gcvOBJ_SURF);

        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        /* Is the destination format supported? */
        if (gcmIS_ERROR(gcoHARDWARE_TranslateDestinationFormat(
                DestSurface->info.format,
                &destFormat, &destFormatSwizzle, &destIsYUV)))
        {
            /* No, use software renderer. */
            gcmERR_BREAK(gcoHARDWARE_UseSoftware2D(gcvTRUE));
            useSotfEngine = gcvTRUE;
        }

        /* Translate the specified transparency mode. */
        gcmERR_BREAK(gcoHARDWARE_TranslateSurfTransparency(
            Transparency,
            &srcTransparency,
            &dstTransparency,
            &patTransparency
            ));

        /* Determine the resource usage. */
        gcoHARDWARE_Get2DResourceUsage(
            FgRop, BgRop,
            srcTransparency,
            &useSource, &useBrush, gcvNULL
            );

        /* Source must be used. */
        if (!useSource)
        {
            status = gcvSTATUS_INVALID_ARGUMENT;
            break;
        }

        /* Use surface rect if not specified. */
        if (DestRect == gcvNULL)
        {
            DestRect = &DestSurface->info.rect;
        }

        /* Default to 0 origin. */
        if (SourceOrigin == gcvNULL)
        {
            SourceOrigin = &sourceOrigin;
            SourceOrigin->x = 0;
            SourceOrigin->y = 0;
        }

        /* Lock the destination. */
        gcmERR_BREAK(gcoSURF_Lock(
            DestSurface,
            gcvNULL,
            destMemory
            ));

        gcmERR_BREAK(gco2D_SetTargetEx(
            engine,
            useSotfEngine ?
                (gctUINT32)(gctUINTPTR_T)DestSurface->info.node.logical
                : DestSurface->info.node.physical,
            DestSurface->info.stride,
            DestSurface->info.rotation,
            DestSurface->info.alignedWidth,
            DestSurface->info.alignedHeight
            ));

        /* Setup the brush if needed. */
        if (useBrush)
        {
            /* Flush the brush. */
            gcmERR_BREAK(gco2D_FlushBrush(
                engine,
                Brush,
                DestSurface->info.format
                ));
        }

        /* Compute the destination size. */
        destWidth  = DestRect->right  - DestRect->left;
        destHeight = DestRect->bottom - DestRect->top;

        /* Determine the number of lines to render. */
        lines2render = destHeight;

        /* Determine left source coordinate. */
        srcSubRect.left = SourceOrigin->x & 7;

        /* Assume 8-pixel packed stream. */
        streamWidth = gcmALIGN(srcSubRect.left + destWidth, 8);

        /* Do we fit? */
        if (streamWidth == 8)
        {
            streamPack = gcvSURF_PACKED8;
            streamPackHeightMask = ~3U;
        }

        /* Nope, don't fit. */
        else
        {
            /* Assume 16-pixel packed stream. */
            streamWidth = gcmALIGN(srcSubRect.left + destWidth, 16);

            /* Do we fit now? */
            if (streamWidth == 16)
            {
                streamPack = gcvSURF_PACKED16;
                streamPackHeightMask = ~1U;
            }

            /* Still don't. */
            else
            {
                /* Assume unpacked stream. */
                streamWidth = gcmALIGN(srcSubRect.left + destWidth, 32);
                streamPack = gcvSURF_UNPACKED;
                streamPackHeightMask = ~0U;
            }
        }

        /* Set the rectangle value. */
        srcSubRect.top = srcSubRect.right = srcSubRect.bottom = 0;

        /* Set source rectangle size. */
        gcmERR_BREAK(gco2D_SetSource(
            engine,
            &srcSubRect
            ));

        /* Program the source. */
        gcmERR_BREAK(gco2D_SetMonochromeSource(
            engine,
            ColorConvert,
            MonoTransparency,
            streamPack,
            gcvFALSE,
            Transparency,
            FgColor,
            BgColor
            ));

        /* Determine the maxumum stream height. */
        maxHeight  = gcoMATH_DivideUInt(gco2D_GetMaximumDataCount() << 5,
                                        streamWidth);
        maxHeight &= streamPackHeightMask;

        /* Set the stream rectangle. */
        streamRect.left   = SourceOrigin->x - srcSubRect.left;
        streamRect.top    = SourceOrigin->y;
        streamRect.right  = streamRect.left + streamWidth;
        streamRect.bottom = streamRect.top;

        /* Init destination subrectangle. */
        destSubRect.left   = DestRect->left;
        destSubRect.top    = DestRect->top;
        destSubRect.right  = DestRect->right;
        destSubRect.bottom = destSubRect.top;

        do
        {
            /* Determine the area to render in this pass. */
            gctUINT32 currLines = (lines2render > maxHeight)
                ? maxHeight
                : lines2render;

            streamRect.top     = streamRect.bottom;
            streamRect.bottom += currLines;

            destSubRect.top     = destSubRect.bottom;
            destSubRect.bottom += currLines;

            /* Do the blit. */
            gcmERR_BREAK(gco2D_MonoBlit(
                engine,
                Source,
                SourceSize,
                &streamRect,
                SourcePack,
                streamPack,
                &destSubRect,
                FgRop, BgRop,
                DestSurface->info.format
                ));

            /* Update the line counter. */
            lines2render -= currLines;
        }
        while (lines2render);
    }
    while (gcvFALSE);

    /* Unlock the destination. */
    if (destMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(DestSurface, destMemory[0]));
    }

    if (useSotfEngine)
    {
        /* Disable software renderer. */
        gcmVERIFY_OK(gcoHARDWARE_UseSoftware2D(gcvFALSE));
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_FilterBlit
**
**  Filter blit.
**
**  INPUT:
**
**      gcoSURF SrcSurface
**          Pointer to the source surface.
**
**      gcoSURF DestSurface
**          Pointer to the destination surface.
**
**      gcsRECT_PTR SrcRect
**          Coordinates of the entire source image.
**
**      gcsRECT_PTR DestRect
**          Coordinates of the entire destination image.
**
**      gcsRECT_PTR DestSubRect
**          Coordinates of a sub area within the destination to render.
**          If DestSubRect is gcvNULL, the complete image will be rendered
**          using coordinates set by DestRect.
**          If DestSubRect is not gcvNULL and DestSubRect and DestRect are
**          no equal, DestSubRect is assumed to be within DestRect and
**          will be used to reneder the sub area only.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_FilterBlit(
    IN gcoSURF SrcSurface,
    IN gcoSURF DestSurface,
    IN gcsRECT_PTR SrcRect,
    IN gcsRECT_PTR DestRect,
    IN gcsRECT_PTR DestSubRect
    )
{
    gceSTATUS status;
    gcsRECT destSubRect, srcRect, destRect;
    gctBOOL ditherBy3D = gcvFALSE;
    gctBOOL ditherNotSupported = gcvFALSE;
    gctBOOL rotateWalkaround =  gcvFALSE;
    gctBOOL enable2DDither =  gcvFALSE;

    gctPOINTER srcMemory[3] = {gcvNULL, };
    gctPOINTER destMemory[3] = {gcvNULL, };

    gcsSURF_INFO_PTR tempSurf = gcvNULL;
    gcsSURF_INFO_PTR temp2Surf = gcvNULL;

    gco2D engine = gcvNULL;

    gceSURF_ROTATION srcRotBackup = (gceSURF_ROTATION)-1, dstRotBackup = (gceSURF_ROTATION)-1;

    gcmHEADER_ARG("SrcSurface=0x%x DestSurface=0x%x SrcRect=0x%x DestRect=0x%x "
              "DestSubRect=0x%x",
              SrcSurface, DestSurface, SrcRect, DestRect, DestSubRect);

    if (SrcSurface == gcvNULL || DestSurface == gcvNULL)
    {
        status = gcvSTATUS_INVALID_ARGUMENT;
        gcmFOOTER();
        return status;
    }

    do
    {
        gcsSURF_FORMAT_INFO_PTR srcFormat[2];
        gcsSURF_FORMAT_INFO_PTR destFormat[2];

        /* Verify the surfaces. */
        gcmBADOBJECT_BREAK(SrcSurface, gcvOBJ_SURF);
        gcmBADOBJECT_BREAK(DestSurface, gcvOBJ_SURF);

        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        /* Use surface rect if not specified. */
        if (SrcRect == gcvNULL)
        {
            SrcRect = &SrcSurface->info.rect;
        }

        /* Use surface rect if not specified. */
        if (DestRect == gcvNULL)
        {
            DestRect = &DestSurface->info.rect;
        }

        /* Make sure the destination sub rectangle is set. */
        if (DestSubRect == gcvNULL)
        {
            destSubRect.left   = 0;
            destSubRect.top    = 0;
            destSubRect.right  = DestRect->right  - DestRect->left;
            destSubRect.bottom = DestRect->bottom - DestRect->top;

            DestSubRect = &destSubRect;
        }

        gcmERR_BREAK(gcoSURF_QueryFormat(SrcSurface->info.format, srcFormat));
        gcmERR_BREAK(gcoSURF_QueryFormat(DestSurface->info.format, destFormat));

        if ((SrcSurface->info.dither || DestSurface->info.dither)
            && ((srcFormat[0]->bitsPerPixel > destFormat[0]->bitsPerPixel)
            || (srcFormat[0]->fmtClass == gcvFORMAT_CLASS_YUV)))
        {
            if (gcoHARDWARE_IsFeatureAvailable(gcvFEATURE_2D_DITHER))
            {
                gcmERR_BREAK(gco2D_EnableDither(
                    engine,
                    gcvTRUE));

                enable2DDither = gcvTRUE;
            }
            else if (gcoHARDWARE_IsFeatureAvailable(gcvFEATURE_PIPE_3D))
            {
                ditherBy3D = gcvTRUE;
            }
            else
            {
                /* Hardware does not support dither. */
                ditherNotSupported = gcvTRUE;
            }
        }

        if ((SrcSurface->info.rotation != gcvSURF_0_DEGREE || DestSurface->info.rotation != gcvSURF_0_DEGREE)
            && !gcoHARDWARE_IsFeatureAvailable(gcvFEATURE_2D_FILTERBLIT_FULLROTATION))
        {
            rotateWalkaround = gcvTRUE;
        }
        else if (ditherBy3D && (((DestSubRect->right - DestSubRect->left) & 15)
            || ((DestSubRect->bottom - DestSubRect->top) & 3)))
        {
            rotateWalkaround = gcvTRUE;
        }

        /* Lock the destination. */
        gcmERR_BREAK(gcoSURF_Lock(
            DestSurface,
            gcvNULL,
            destMemory
            ));

        /* Lock the source. */
        gcmERR_BREAK(gcoSURF_Lock(
            SrcSurface,
            gcvNULL,
            srcMemory
            ));

        if (ditherBy3D || rotateWalkaround)
        {
            gcsRECT tempRect;

            srcRotBackup = SrcSurface->info.rotation;
            dstRotBackup = DestSurface->info.rotation;

            srcRect = *SrcRect;
            destRect = *DestRect;
            destSubRect = *DestSubRect;

            if (rotateWalkaround)
            {
                if (SrcSurface->info.rotation != gcvSURF_0_DEGREE)
                {
                    SrcSurface->info.rotation = gcvSURF_0_DEGREE;
                    gcmERR_BREAK(gcsRECT_RelativeRotation(srcRotBackup, &DestSurface->info.rotation));

                    gcmERR_BREAK(gcsRECT_Rotate(
                        &srcRect,
                        srcRotBackup,
                        gcvSURF_0_DEGREE,
                        SrcSurface->info.alignedWidth,
                        SrcSurface->info.alignedHeight));

                    destSubRect.left += destRect.left;
                    destSubRect.right += destRect.left;
                    destSubRect.top += destRect.top;
                    destSubRect.bottom += destRect.top;

                    gcmERR_BREAK(gcsRECT_Rotate(
                        &destSubRect,
                        dstRotBackup,
                        DestSurface->info.rotation,
                        DestSurface->info.alignedWidth,
                        DestSurface->info.alignedHeight));

                    gcmERR_BREAK(gcsRECT_Rotate(
                        &destRect,
                        dstRotBackup,
                        DestSurface->info.rotation,
                        DestSurface->info.alignedWidth,
                        DestSurface->info.alignedHeight));

                    destSubRect.left -= destRect.left;
                    destSubRect.right -= destRect.left;
                    destSubRect.top -= destRect.top;
                    destSubRect.bottom -= destRect.top;
                }

                tempRect.left = 0;
                tempRect.top = 0;
                tempRect.right = destRect.right - destRect.left;
                tempRect.bottom = destRect.bottom - destRect.top;

                gcmERR_BREAK(gcoHARDWARE_Get2DTempSurface(
                    tempRect.right,
                    tempRect.bottom,
                    ditherBy3D ? gcvSURF_A8R8G8B8 : DestSurface->info.format,
                    &tempSurf));

                tempSurf->rotation = gcvSURF_0_DEGREE;
            }

            gcmERR_BREAK(gco2D_FilterBlitEx(
                engine,
                SrcSurface->info.node.physical,
                SrcSurface->info.stride,
                SrcSurface->info.node.physical2,
                SrcSurface->info.uStride,
                SrcSurface->info.node.physical3,
                SrcSurface->info.vStride,
                SrcSurface->info.format,
                SrcSurface->info.rotation,
                SrcSurface->info.alignedWidth,
                SrcSurface->info.alignedHeight,
                &srcRect,
                tempSurf->node.physical,
                tempSurf->stride,
                tempSurf->format,
                tempSurf->rotation,
                tempSurf->alignedWidth,
                tempSurf->alignedHeight,
                &tempRect,
                &destSubRect
                ));

            tempRect = destSubRect;
            if (rotateWalkaround)
            {
                /* bitblit rorate. */
                gcsSURF_INFO * srcSurf = ditherBy3D ? temp2Surf : tempSurf;
                gceSURF_ROTATION tSrcRot = (gceSURF_ROTATION)-1, tDestRot = (gceSURF_ROTATION)-1;
                gctBOOL bMirror = gcvFALSE;

                destSubRect.left += destRect.left;
                destSubRect.right += destRect.left;
                destSubRect.top += destRect.top;
                destSubRect.bottom += destRect.top;

                if (!gcoHARDWARE_IsFeatureAvailable(gcvFEATURE_2D_BITBLIT_FULLROTATION))
                {
                    tDestRot = DestSurface->info.rotation;

                    gcmERR_BREAK(gcsRECT_RelativeRotation(srcSurf->rotation, &tDestRot));
                    switch (tDestRot)
                    {
                    case gcvSURF_0_DEGREE:
                        tSrcRot = tDestRot = gcvSURF_0_DEGREE;

                        break;

                    case gcvSURF_90_DEGREE:
                        tSrcRot = gcvSURF_0_DEGREE;
                        tDestRot = gcvSURF_90_DEGREE;

                        break;

                    case gcvSURF_180_DEGREE:
                        tSrcRot = tDestRot = gcvSURF_0_DEGREE;
                        bMirror = gcvTRUE;

                        break;

                    case gcvSURF_270_DEGREE:
                        tSrcRot = gcvSURF_90_DEGREE;
                        tDestRot = gcvSURF_0_DEGREE;

                        break;

                    default:
                        status = gcvSTATUS_NOT_SUPPORTED;

                        break;
                    }

                    gcmERR_BREAK(status);

                    gcmERR_BREAK(gcsRECT_Rotate(
                        &tempRect,
                        srcSurf->rotation,
                        tSrcRot,
                        srcSurf->alignedWidth,
                        srcSurf->alignedHeight));

                    gcmERR_BREAK(gcsRECT_Rotate(
                        &destSubRect,
                        DestSurface->info.rotation,
                        tDestRot,
                        DestSurface->info.alignedWidth,
                        DestSurface->info.alignedHeight));

                    srcSurf->rotation = tSrcRot;
                    DestSurface->info.rotation = tDestRot;

                    if (bMirror)
                    {
                        gcmERR_BREAK(gco2D_SetBitBlitMirror(
                            engine,
                            gcvTRUE,
                            gcvTRUE));
                    }
                }

                gcmERR_BREAK(gco2D_SetClipping(
                    engine,
                    &destSubRect));

                gcmERR_BREAK(gco2D_SetColorSourceEx(
                    engine,
                    srcSurf->node.physical,
                    srcSurf->stride,
                    srcSurf->format,
                    srcSurf->rotation,
                    srcSurf->alignedWidth,
                    srcSurf->alignedHeight,
                    gcvFALSE,
                    gcvSURF_OPAQUE,
                    0
                    ));

                gcmERR_BREAK(gco2D_SetSource(
                    engine,
                    &tempRect
                    ));

                gcmERR_BREAK(gco2D_SetTargetEx(
                    engine,
                    DestSurface->info.node.physical,
                    DestSurface->info.stride,
                    DestSurface->info.rotation,
                    DestSurface->info.alignedWidth,
                    DestSurface->info.alignedHeight
                    ));

                gcmERR_BREAK(gco2D_Blit(
                    engine,
                    1,
                    &destSubRect,
                    0xCC,
                    0xCC,
                    DestSurface->info.format
                    ));

                if (bMirror)
                {
                    gcmERR_BREAK(gco2D_SetBitBlitMirror(
                        engine,
                        gcvFALSE,
                        gcvFALSE));
                }
            }
        }
        else
        {
            /* Call gco2D object to complete the blit. */
            gcmERR_BREAK(gco2D_FilterBlitEx(
                engine,
                SrcSurface->info.node.physical,
                SrcSurface->info.stride,
                SrcSurface->info.node.physical2,
                SrcSurface->info.uStride,
                SrcSurface->info.node.physical3,
                SrcSurface->info.vStride,
                SrcSurface->info.format,
                SrcSurface->info.rotation,
                SrcSurface->info.alignedWidth,
                SrcSurface->info.alignedHeight,
                SrcRect,
                DestSurface->info.node.physical,
                DestSurface->info.stride,
                DestSurface->info.format,
                DestSurface->info.rotation,
                DestSurface->info.alignedWidth,
                DestSurface->info.alignedHeight,
                DestRect,
                DestSubRect
                ));
        }
    }
    while (gcvFALSE);

    if (enable2DDither)
    {
        gcmVERIFY_OK(gco2D_EnableDither(
            engine,
            gcvFALSE));
    }

    if (srcRotBackup != (gceSURF_ROTATION)-1)
    {
        SrcSurface->info.rotation = srcRotBackup;
    }

    if (dstRotBackup != (gceSURF_ROTATION)-1)
    {
        DestSurface->info.rotation = dstRotBackup;
    }

    /* Unlock the source. */
    if (srcMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(SrcSurface, srcMemory[0]));
    }

    /* Unlock the destination. */
    if (destMemory[0] != gcvNULL)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(DestSurface, destMemory[0]));
    }

    /* Free temp buffer. */
    if (tempSurf != gcvNULL)
    {
        gcmVERIFY_OK(gcoHARDWARE_Put2DTempSurface(tempSurf));
    }

    if (temp2Surf != gcvNULL)
    {
        gcmVERIFY_OK(gcoHARDWARE_Put2DTempSurface(temp2Surf));
    }

    if (ditherNotSupported)
    {
        status = gcvSTATUS_NOT_SUPPORT_DITHER;
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_EnableAlphaBlend
**
**  Enable alpha blending engine in the hardware and disengage the ROP engine.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gctUINT8 SrcGlobalAlphaValue
**          Global alpha value for the color components.
**
**      gctUINT8 DstGlobalAlphaValue
**          Global alpha value for the color components.
**
**      gceSURF_PIXEL_ALPHA_MODE SrcAlphaMode
**          Per-pixel alpha component mode.
**
**      gceSURF_PIXEL_ALPHA_MODE DstAlphaMode
**          Per-pixel alpha component mode.
**
**      gceSURF_GLOBAL_ALPHA_MODE SrcGlobalAlphaMode
**          Global/per-pixel alpha values selection.
**
**      gceSURF_GLOBAL_ALPHA_MODE DstGlobalAlphaMode
**          Global/per-pixel alpha values selection.
**
**      gceSURF_BLEND_FACTOR_MODE SrcFactorMode
**          Final blending factor mode.
**
**      gceSURF_BLEND_FACTOR_MODE DstFactorMode
**          Final blending factor mode.
**
**      gceSURF_PIXEL_COLOR_MODE SrcColorMode
**          Per-pixel color component mode.
**
**      gceSURF_PIXEL_COLOR_MODE DstColorMode
**          Per-pixel color component mode.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_EnableAlphaBlend(
    IN gcoSURF Surface,
    IN gctUINT8 SrcGlobalAlphaValue,
    IN gctUINT8 DstGlobalAlphaValue,
    IN gceSURF_PIXEL_ALPHA_MODE SrcAlphaMode,
    IN gceSURF_PIXEL_ALPHA_MODE DstAlphaMode,
    IN gceSURF_GLOBAL_ALPHA_MODE SrcGlobalAlphaMode,
    IN gceSURF_GLOBAL_ALPHA_MODE DstGlobalAlphaMode,
    IN gceSURF_BLEND_FACTOR_MODE SrcFactorMode,
    IN gceSURF_BLEND_FACTOR_MODE DstFactorMode,
    IN gceSURF_PIXEL_COLOR_MODE SrcColorMode,
    IN gceSURF_PIXEL_COLOR_MODE DstColorMode
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x SrcGlobalAlphaValue=%u DstGlobalAlphaValue=%u "
              "SrcAlphaMode=%d DstAlphaMode=%d SrcGlobalAlphaMode=%d "
              "DstGlobalAlphaMode=%d SrcFactorMode=%d DstFactorMode=%d "
              "SrcColorMode=%d DstColorMode=%d",
              Surface, SrcGlobalAlphaValue, DstGlobalAlphaValue, SrcAlphaMode,
              DstAlphaMode, SrcGlobalAlphaMode, DstGlobalAlphaMode,
              SrcFactorMode, DstFactorMode, SrcColorMode, DstColorMode);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    do {
        gco2D engine;

        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));

        gcmERR_BREAK(gco2D_EnableAlphaBlend(
                engine,
                (gctUINT32)SrcGlobalAlphaValue << 24,
                (gctUINT32)DstGlobalAlphaValue << 24,
                SrcAlphaMode,
                DstAlphaMode,
                SrcGlobalAlphaMode,
                DstGlobalAlphaMode,
                SrcFactorMode,
                DstFactorMode,
                SrcColorMode,
                DstColorMode
                ));

    } while (gcvFALSE);

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_DisableAlphaBlend
**
**  Disable alpha blending engine in the hardware and engage the ROP engine.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_DisableAlphaBlend(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    do
    {
        gco2D engine;
        gcmERR_BREAK(gcoHAL_Get2DEngine(gcvNULL, &engine));
        gcmERR_BREAK(gco2D_DisableAlphaBlend(engine));
    }
    while (gcvFALSE);

    gcmFOOTER();
    return status;
}


gceSTATUS
gcoSURF_NODE_Cache(
    IN gcsSURF_NODE_PTR Node,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes,
    IN gceCACHEOPERATION Operation
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Node=0x%x, Operation=%d, Bytes=%u", Node, Operation, Bytes);

    if (Node->pool == gcvPOOL_USER)
    {
        gcmFOOTER();
        return gcvSTATUS_OK;
    }

#if !gcdPAGED_MEMORY_CACHEABLE
    if (Node->u.normal.cacheable == gcvFALSE)
    {
        gcmFOOTER();
        return gcvSTATUS_OK;
    }
#endif

    switch (Operation)
    {
        case gcvCACHE_CLEAN:
            gcmONERROR(gcoOS_CacheClean(gcvNULL, Node->u.normal.node, Logical, Bytes));
            break;

        case gcvCACHE_INVALIDATE:
            gcmONERROR(gcoOS_CacheInvalidate(gcvNULL, Node->u.normal.node, Logical, Bytes));
            break;

        case gcvCACHE_FLUSH:
            gcmONERROR(gcoOS_CacheFlush(gcvNULL, Node->u.normal.node, Logical, Bytes));
            break;

        default:
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
            break;
    }

    gcmFOOTER();
    return gcvSTATUS_OK;

OnError:
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_CPUCacheOperation
**
**  Perform the specified CPU cache operation on the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceSURF_CPU_CACHE_OP_TYPE Operation
**          Cache operation to be performed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_CPUCacheOperation(
    IN gcoSURF Surface,
    IN gceCACHEOPERATION Operation
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gctPOINTER source[3] = {0};
    gctBOOL locked = gcvFALSE;

    gcmHEADER_ARG("Surface=0x%x, Operation=%d", Surface, Operation);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Lock the surfaces. */
    gcmONERROR(gcoSURF_Lock(Surface, gcvNULL, source));
    locked = gcvTRUE;

    gcmONERROR(gcoSURF_NODE_Cache(&Surface->info.node,
                                  source[0],
                                  Surface->info.node.size,
                                  Operation));

    /* Unlock the surfaces. */
    gcmONERROR(gcoSURF_Unlock(Surface, source[0]));
    locked = gcvFALSE;

    gcmFOOTER();
    return gcvSTATUS_OK;

OnError:
    if (locked)
    {
        gcmVERIFY_OK(gcoSURF_Unlock(Surface, source[0]));
    }

    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_Flush
**
**  Flush the caches to make sure the surface has all pixels.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_Flush(
    IN gcoSURF Surface
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Flush the current pipe. */
    status = gcoHARDWARE_FlushPipe();
    gcmFOOTER();
    return status;
}



/*******************************************************************************
**
**  gcoSURF_SetOrientation
**
**  Set the orientation of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceORIENTATION Orientation
**          The requested surface orientation.  Orientation can be one of the
**          following values:
**
**              gcvORIENTATION_TOP_BOTTOM - Surface is from top to bottom.
**              gcvORIENTATION_BOTTOM_TOP - Surface is from bottom to top.
**
**  OUTPUT:
**
*/
gceSTATUS
gcoSURF_SetOrientation(
    IN gcoSURF Surface,
    IN gceORIENTATION Orientation
    )
{
    gcmHEADER_ARG("Surface=0x%x Orientation=%d", Surface, Orientation);

    /* Verif the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Set the orientation. */
    Surface->info.orientation = Orientation;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_QueryOrientation
**
**  Query the orientation of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**
**      gceORIENTATION * Orientation
**          Pointer to a variable receiving the surface orientation.
**
*/
gceSTATUS
gcoSURF_QueryOrientation(
    IN gcoSURF Surface,
    OUT gceORIENTATION * Orientation
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);
    gcmVERIFY_ARGUMENT(Orientation != gcvNULL);

    /* Return the orientation. */
    *Orientation = Surface->info.orientation;

    /* Success. */
    gcmFOOTER_ARG("*Orientation=%d", *Orientation);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_SetColorType
**
**  Set the color type of the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceSURF_COLOR_TYPE colorType
**          color type of the surface.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetColorType(
    IN gcoSURF Surface,
    IN gceSURF_COLOR_TYPE ColorType
    )
{
    gcmHEADER_ARG("Surface=0x%x ColorType=%d", Surface, ColorType);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Set the color type. */
    Surface->info.colorType = ColorType;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_GetColorType
**
**  Get the color type of the surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**  OUTPUT:
**
**      gceSURF_COLOR_TYPE *colorType
**          pointer to the variable receiving color type of the surface.
**
*/
gceSTATUS
gcoSURF_GetColorType(
    IN gcoSURF Surface,
    OUT gceSURF_COLOR_TYPE *ColorType
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);
    gcmVERIFY_ARGUMENT(ColorType != gcvNULL);

    /* Return the color type. */
    *ColorType = Surface->info.colorType;

    /* Success. */
    gcmFOOTER_ARG("*ColorType=%d", *ColorType);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_SetRotation
**
**  Set the surface ration angle.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceSURF_ROTATION Rotation
**          Rotation angle.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetRotation(
    IN gcoSURF Surface,
    IN gceSURF_ROTATION Rotation
    )
{
    gcmHEADER_ARG("Surface=0x%x Rotation=%d", Surface, Rotation);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Support only 2D surfaces. */
    if (Surface->info.type != gcvSURF_BITMAP)
    {
        gcmFOOTER_NO();
        return gcvSTATUS_NOT_SUPPORTED;
    }

    /* Set new rotation. */
    Surface->info.rotation = Rotation;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoSURF_SetDither
**
**  Set the surface dither flag.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to the surface.
**
**      gceSURF_ROTATION Dither
**          ditherable or not.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetDither(
    IN gcoSURF Surface,
    IN gctBOOL Dither
    )
{
    gcmHEADER_ARG("Surface=0x%x Dither=%d", Surface, Dither);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Support only 2D surfaces. */
    if (Surface->info.type != gcvSURF_BITMAP)
    {
        gcmFOOTER_NO();
        return gcvSTATUS_NOT_SUPPORTED;
    }

    /* Set new rotation. */
    Surface->info.dither = Dither;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gcoSURF_ConstructWrapper
**
**  Create a new gcoSURF wrapper object.
**
**  INPUT:
**
**      gcoHAL Hal
**          Pointer to an gcoHAL object.
**
**  OUTPUT:
**
**      gcoSURF * Surface
**          Pointer to the variable that will hold the gcoSURF object pointer.
*/
gceSTATUS
gcoSURF_ConstructWrapper(
    IN gcoHAL Hal,
    OUT gcoSURF * Surface
    )
{
    gcoSURF surface;
    gceSTATUS status;
    gctPOINTER pointer = gcvNULL;

    gcmHEADER();

    /* Verify the arguments. */
    gcmVERIFY_ARGUMENT(Surface != gcvNULL);

    do
    {
        /* Allocate the gcoSURF object. */
        gcmONERROR(gcoOS_Allocate(
            gcvNULL,
            gcmSIZEOF(struct _gcoSURF),
            &pointer
            ));

        surface = pointer;

        /* Reset the object. */
        gcoOS_ZeroMemory(surface, gcmSIZEOF(struct _gcoSURF));

        /* Initialize the gcoSURF object.*/
        surface->object.type = gcvOBJ_SURF;


        /* One plane. */
        surface->depth = 1;

        /* Initialize the node. */
        surface->info.node.pool      = gcvPOOL_USER;
        surface->info.node.physical  = ~0U;
        surface->info.node.physical2 = ~0U;
        surface->info.node.physical3 = ~0U;
        surface->info.node.count     = 1;
        surface->referenceCount = 1;

        /* Return pointer to the gcoSURF object. */
        *Surface = surface;

        /* Success. */
        gcmFOOTER_ARG("*Surface=0x%x", *Surface);
        return gcvSTATUS_OK;
    }
    while (gcvFALSE);

OnError:

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoSURF_SetBuffer
**
**  Set the underlying buffer for the surface wrapper.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to gcoSURF object.
**
**      gceSURF_TYPE Type
**          Type of surface to create.
**
**      gceSURF_FORMAT Format
**          Format of surface to create.
**
**      gctINT Stride
**          Surface stride. Is set to ~0 the stride will be autocomputed.
**
**      gctPOINTER Logical
**          Logical pointer to the user allocated surface or gcvNULL if no
**          logical pointer has been provided.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetBuffer(
    IN gcoSURF Surface,
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN gctUINT Stride,
    IN gctPOINTER Logical,
    IN gctUINT32 Physical
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Surface=0x%x Type=%d Format=%d Stride=%u Logical=0x%x "
                  "Physical=%08x",
                  Surface, Type, Format, Stride, Logical, Physical);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Has to be user-allocated surface. */
    if (Surface->info.node.pool != gcvPOOL_USER)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    /* Unmap the current buffer if any. */
    gcmONERROR(_UnmapUserBuffer(Surface, gcvTRUE));

    /* Determine the stride parameters. */
    Surface->autoStride = (Stride == ~0U);

    /* Set surface parameters. */
    Surface->info.type   = Type;
    Surface->info.format = Format;
    Surface->info.stride = Stride;

    /* Set node pointers. */
    Surface->logical  = (gctUINT8_PTR) Logical;
    Surface->physical = Physical;

    {
        /* Compute bits per pixel. */
        gcmONERROR(gcoHARDWARE_ConvertFormat(Format,
                                             (gctUINT32_PTR)&Surface->info.bitsPerPixel,
                                             gcvNULL));
    }

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
**  gcoSURF_SetVideoBuffer
**
**  Set the underlying video buffer for the surface wrapper.
**  The video plane addresses should be specified invidually.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to gcoSURF object.
**
**      gceSURF_TYPE Type
**          Type of surface to create.
**
**      gceSURF_FORMAT Format
**          Format of surface to create.
**
**      gctINT Stride
**          Surface stride. Is set to ~0 the stride will be autocomputed.
**
**      gctPOINTER LogicalPlane1
**          Logical pointer to the first plane of the user allocated surface
**          or gcvNULL if no logical pointer has been provided.
**
**      gctUINT32 PhysicalPlane1
**          Physical pointer to the user allocated surface or ~0 if no
**          physical pointer has been provided.
**
**  OUTPUT:
**
**      Nothing.
*/

/*******************************************************************************
**
**  gcoSURF_SetWindow
**
**  Set the size of the surface in pixels and map the underlying buffer set by
**  gcoSURF_SetBuffer if necessary.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to gcoSURF object.
**
**      gctINT X, Y
**          The origin of the surface.
**
**      gctINT Width, Height
**          Size of the surface in pixels.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_SetWindow(
    IN gcoSURF Surface,
    IN gctUINT X,
    IN gctUINT Y,
    IN gctUINT Width,
    IN gctUINT Height
    )
{
    gceSTATUS status;
    gctUINT32 offsetX;
    gctUINT32 offsetY;
#if gcdSECURE_USER
    gcsHAL_INTERFACE iface;
#endif
    gcmHEADER_ARG("Surface=0x%x X=%u Y=%u Width=%u Height=%u",
                  Surface, X, Y, Width, Height);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    /* Unmap the current buffer if any. */
    gcmONERROR(
        _UnmapUserBuffer(Surface, gcvTRUE));

    /* Make sure at least one of the surface pointers is set. */
    if ((Surface->logical == gcvNULL) && (Surface->physical == ~0U))
    {
        gcmONERROR(gcvSTATUS_INVALID_ADDRESS);
    }

    /* Set initial aligned width and height. */
    Surface->info.alignedWidth  = Width;
    Surface->info.alignedHeight = Height;

    /* Stride is the same as the width? */
    if (Surface->autoStride)
    {
        /* Compute the stride. */
        Surface->info.stride = Width * Surface->info.bitsPerPixel / 8;
    }
    else
    {
        {
            /* Align the surface size. */
            gcmONERROR(
                gcoHARDWARE_AlignToTileCompatible(Surface->info.type,
                                                  Surface->info.format,
                                                  &Surface->info.alignedWidth,
                                                  &Surface->info.alignedHeight,
                                                  &Surface->info.tiling,
                                                  gcvNULL));
        }
    }

    /* Set the rectangle. */
    Surface->info.rect.left   = 0;
    Surface->info.rect.top    = 0;
    Surface->info.rect.right  = Width;
    Surface->info.rect.bottom = Height;

    offsetX = X * Surface->info.bitsPerPixel / 8;
    offsetY = Y * Surface->info.stride;

    /* Compute the surface size. */
    Surface->info.size
        = Surface->info.stride
        * Surface->info.alignedHeight;

    /* Need to map physical pointer? */
    if (Surface->physical == ~0U)
    {
        /* Map the physical pointer. */
        gcmONERROR(
            gcoOS_MapUserMemory(gcvNULL,
                                (gctUINT8_PTR) Surface->logical + offsetY,
                                Surface->info.size,
                                &Surface->info.node.u.wrapped.mappingInfo,
                                &Surface->info.node.physical));

        gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL,
                                            &Surface->info.node.u.wrapped.mappingHardwareType));
    }
    else
    {
        Surface->info.node.physical = Surface->physical + offsetY;
    }

    /* Need to map logical pointer? */
    if (Surface->logical == gcvNULL)
    {
        gctPOINTER pointer = gcvNULL;

        /* Map the logical pointer. */
        gcmONERROR(
            gcoHAL_MapMemory(gcvNULL,
                             gcmINT2PTR(Surface->physical + offsetY),
                             Surface->info.size,
                             &pointer));

        Surface->info.node.logical                 = pointer;
        Surface->info.node.u.wrapped.logicalMapped = gcvTRUE;
    }
    else
    {
        Surface->info.node.logical = (gctUINT8_PTR) Surface->logical + offsetY;
    }

    Surface->info.node.logical  += offsetX;
    Surface->info.node.physical += offsetX;

#if gcdSECURE_USER
    iface.command = gcvHAL_MAP_USER_MEMORY;
    iface.u.MapUserMemory.memory  = gcmPTR_TO_UINT64(Surface->info.node.logical);
    iface.u.MapUserMemory.address = Surface->info.node.physical;
    iface.u.MapUserMemory.size    = Surface->info.size;
    gcmONERROR(gcoOS_DeviceControl(gcvNULL,
                                   IOCTL_GCHAL_INTERFACE,
                                   &iface, gcmSIZEOF(iface),
                                   &iface, gcmSIZEOF(iface)));

    Surface->info.node.physical = (gctUINT32) Surface->info.node.logical;
#endif

    /* Validate the node. */
    Surface->info.node.lockCount = 1;
    Surface->info.node.valid     = gcvTRUE;

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
**  gcoSURF_ReferenceSurface
**
**  Increase reference count of a surface.
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to gcoSURF object.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoSURF_ReferenceSurface(
    IN gcoSURF Surface
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    Surface->referenceCount++;

    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gcoSURF_QueryReferenceCount
**
**  Query reference count of a surface
**
**  INPUT:
**
**      gcoSURF Surface
**          Pointer to gcoSURF object.
**
**  OUTPUT:
**
**      gctINT32 ReferenceCount
**          Reference count of a surface
*/
gceSTATUS
gcoSURF_QueryReferenceCount(
    IN gcoSURF Surface,
    OUT gctINT32 * ReferenceCount
    )
{
    gcmHEADER_ARG("Surface=0x%x", Surface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Surface, gcvOBJ_SURF);

    *ReferenceCount = Surface->referenceCount;

    gcmFOOTER_ARG("*ReferenceCount=%d", *ReferenceCount);
    return gcvSTATUS_OK;
}

gceSTATUS
gcoSURF_SetOffset(
    IN gcoSURF Surface,
    IN gctUINT Offset
    )
{
    gceSTATUS   status = gcvSTATUS_OK;

    Surface->info.offset = Offset;

    return status;
}

